#include "logind_app.h"
#include "logind_cache.h"
#include "logind_mongodb.h"
#include "http_handler.h"
#include "logind_player.h"
#include "logind_context.h"
#include "logind_gm_table.h"
#include <comm/b64.h>
#include <http/server/server.hpp>
#include <http/client/http_post.h>
#include <http/server/request_handler.hpp>
#include <object/OprateResult.h>

#define MERGE_DATA_SEPARATOR "***|,.**&&&&&**(^!@***"	//�ָ��

#if 0
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

static bool getJson(const string& str, pt::ptree& tree)
{
	stringstream ss;
	ss << str;

	try
	{
		pt::read_json(ss,tree);
		return true;
	}
	catch (std::exception& e)
	{
		tea_perror("getJson %s",e.what());
		return false;	
	}
}

static string toJson(std::map<string,string>& m)
{
	if(m.empty())
		return "{}";
	pt::ptree tree;
	for (auto kv: m)
		tree.add(kv.first, kv.second);
	stringstream ss;
	pt::write_json(ss, tree);
	return ss.str();
}
#else

#include <minijson/minijson_writer.hpp>
#include <minijson/minijson_reader.hpp>

static string toJson(std::map<string,string>& m)
{
	if(m.empty())
		return "{}";

	std::stringstream ss;
	minijson::object_writer writer(ss);
	for (auto kv: m)	
		writer.write(kv.first.c_str(),kv.second);
	writer.close();
	return ss.str();
}

typedef std::vector< std::map<string,string> > JsonArray;
static bool fromJsonArray(const string& str_json,JsonArray& ar)
{
	ar.clear();
	std::map<string,string> m;
	try
	{
		stringstream ss;
		ss << str_json;
		minijson::const_buffer_context ctx(str_json.c_str(), str_json.size()); // may throw
		minijson::parse_array(ctx,[&](minijson::value v){
			m.clear();
			minijson::parse_object(ctx,[&](const char* k,minijson::value v){		
				m[k] = v.as_string();
			});
			ar.push_back(m);
		});
	}
	catch (std::exception& e)
	{
		tea_perror("fromJson :%s",e.what());
		return false;
	}	
	return true;
}

static bool fromJson(const string& str_json,std::map<string,string>& m)
{
	m.clear();
	try
	{
		minijson::const_buffer_context ctx(str_json.c_str(), str_json.size()); // may throw
		minijson::parse_object(ctx,[&](const char* k,minijson::value v){		
			m[k] = v.as_string();
		});
	}
	catch (std::exception& e)
	{
		tea_perror("fromJson :%s",e.what());
		return false;
	}	
	return true;
}

#endif

////Ϊ��һ��base64 ������
//#include <boost/archive/iterators/base64_from_binary.hpp>
//#include <boost/archive/iterators/insert_linebreaks.hpp>
//#include <boost/archive/iterators/transform_width.hpp>
//#include <boost/archive/iterators/ostream_iterator.hpp>
//
//static string toBase64(const string& input)
//{
//	using namespace boost::archive::iterators;
//	std::stringstream os;
//	typedef 
//		insert_linebreaks<         // insert line breaks every 72 characters
//		base64_from_binary<    // convert binary values to base64 characters
//		transform_width<   // retrieve 6 bit integers from a sequence of 8 bit bytes
//		const char *,
//		6,
//		8
//		>
//		> 
//		,72
//		> 
//		base64_text; // compose all the above operations in to a new iterator
//
//	std::copy(
//		base64_text(input.c_str()),
//		base64_text(input.c_str() + input.size()),
//		ostream_iterator<char>(os)
//		);
//	return os.str();
//}


namespace hs = http::server;

static string toQueryString(std::map<string,string>& m)
{
	if(m.empty())
		return "";
	stringstream ss;
	for (auto kv:m)	
		ss << kv.first << "=" << kv.second << "&";
	string dst = ss.str();
	dst.erase(dst.end()-1);	
	return dst;
}

static string getUrl(string host_port,string page)
{	
	ASSERT(!host_port.empty());
	ASSERT(!page.empty() && page[0] == '/');
	if(*(host_port.end()-1) == '/')
		host_port.erase(host_port.end()-1);
	return host_port+page;
}

//////////////////////////////////////////////////////////////////////////
//for HttpHandler
HttpHandler::HttpHandler():m_server(0),m_client(0),m_reg_state(0),m_reload_count(0)
{
	m_server = new hs::server("0.0.0.0","");
	m_client = new http::client::client;

	//��ӡһ�¼����Ķ˿�
	tea_pinfo("$> http listen on port:%d",m_server->get_port());

	Init();
}

HttpHandler::~HttpHandler()
{
	safe_delete(m_server);
	safe_delete(m_client);
}

void HttpHandler::Init()
{
	auto& h = m_server->get_request_handler();

	h.add_hanlde("/",[](const hs::request& req, hs::reply& rep){
		rep.content = "oh no, logind!";
	});

	AddHandler("/idip/4097", &HttpHandler::Handle_Query_Char_Info);				//��ѯ��ҽ�ɫ��Ϣ
	AddHandler("/merge/postdata", &HttpHandler::Handle_Merge_Postdata);			//�Ϸ������������	
	AddHandler("/merge/ok", &HttpHandler::Handle_Merge_Ok);						//�Ϸ����
	AddHandler("/gm_intf/gm_level", &HttpHandler::Handle_SetGmlevel);			//����gm�ȼ�
	AddHandler("/gm_intf/gm_kicking", &HttpHandler::Handle_Kicking);
	AddHandler("/gm_intf/gm_gag", &HttpHandler::Handle_Gag);
	AddHandler("/gm_intf/gm_qq_config", &HttpHandler::Handle_QQ_Config);
	AddHandler("/gm_intf/gm_lock_account", &HttpHandler::Handle_Lock_Account);	
}

void HttpHandler::AddHandler(string uri, Handler handler)
{
	auto& h = m_server->get_request_handler();
	h.add_hanlde(uri, std::bind(handler, this, std::placeholders::_1, std::placeholders::_2));
}

void HttpHandler::Update()
{
	m_server->poll();
	m_client->poll();

	//����ȥע��һ��
	if(m_reg_state == 0)
		RegisterWeb();
	if (m_reload_count == 0)
		ReloadWeb();
}

void HttpHandler::LoadPlayer(const string &player_guid, std::function<void(bool,const string &,vector<GuidObject*>&)> fun)
{
	if(!fun)
		return;

	logind_player *player = nullptr;
	vector<GuidObject*> vec;
	//�����������load���ģ�����Ҫ�ͷ�
	if(ObjMgr.LoadPlayer(player_guid, &player, vec))
	{
		fun(true, player_guid, vec);
		return;
	}
	//Ӳ����load���ģ�����Ҫ�ͷ�
	if(g_Cache.LoadPlayer(player_guid, &player, vec))
	{
		fun(true, player_guid, vec);
		for (auto it:vec)
			safe_delete(it);
		vec.clear();
		return;
	}
	//�����ݿ���load���ģ�������Ҫ�ͷ�
	//todo��˳���¼��Ӳ���У�
	if(g_DAL.LoadPlayer("", player_guid, vec))
	{
		fun(true, player_guid, vec);
		for (auto it:vec)
			safe_delete(it);
		vec.clear();
		return;
	}
	//����������������
	fun(false, player_guid, vec);
}

//TODO:ע��web�˿ڵ�ַ,�������Ѷ����Ҫ����ע��һ���ط�
void HttpHandler::RegisterWeb(bool force/* = false*/)
{
	//�Ƿ�ǿ��ˢ��
	if(force) m_reg_state = 0;

	//����Ѿ�ע����ˣ��򷵻�
	if(m_reg_state != 0)
		return;

	auto *g = dynamic_cast<GlobalValueManager*>(LogindApp::g_app);
	auto conf_svr_url = g->GetConfSvrUrl();//g->GetExtWebInterface();

	if(conf_svr_url.empty())
	{
		m_reg_state = -1;
		return;
	}

	//ȡ�����кϷ���
	vector<string> server_names;
	g->GetMergeServerName(server_names);
	string all_server_names;
	StrJoin(server_names,all_server_names, ';');

	//����ע�����
	std::map<string,string> data;
	data["server_names"] = all_server_names;
	data["port"] = std::to_string(m_server->get_port());
	data["type"] = "logind";

	//�������Ѷ,��Ҫ������ע��,�Ͳ��ܳɹ�����ʧ����
	if(LogindApp::g_app->GetPlatformID() == PLATFORM_QQ)
	{		
		string tencent_intf = g->GetExtWebInterface();//GetWebConfig("tencent_web_intf");
		if(!tencent_intf.empty())
		{
			string response;
			int ret = m_client->post(getUrl(tencent_intf, "/s/reg_appweb"),toQueryString(data), response);		
			tea_pinfo("PLATFORM_QQ RegisterWeb,%d,%s",ret, response.c_str());
		}
	}

	//TODO:�������ʽ���ߵ�ʱ����԰�URL��Ϊ��ʽ��ַ /cow_config/app_addr/reg
	m_client->async_post(getUrl(conf_svr_url, "/cow_config/app_addr/reg"),toQueryString(data),[this](int status_code,const string& content){
		if (status_code == 200)
			m_reg_state = 2;
		else
			m_reg_state = 0;	// ��ͷ����		
	});
	m_reg_state = 1;
}

//������ʱ������Ҫ��web��load�������ĵ���Ӧ����
void HttpHandler::ReloadWeb()
{
	auto *g = dynamic_cast<GlobalValueManager*>(LogindApp::g_app);
	auto conf_svr_url = g->GetConfSvrUrl();//g->GetExtWebInterface();

	if(conf_svr_url.empty())
		return;

	//ȡ�����кϷ���
	vector<string> server_names;
	g->GetMergeServerName(server_names);
	string all_server_names;
	StrJoin(server_names, all_server_names, ';');

	//����ע�����
	std::map<string,string> data;
	data["server_names"] = all_server_names;
	data["type"] = "logind";

	//TODO:�������ʽ���ߵ�ʱ����԰�URL��Ϊ��ʽ��ַ
	m_client->async_post(getUrl(conf_svr_url, "/gm_intf/reload"),toQueryString(data),[this](int status_code,const string& content){
		if (status_code == 200)
			tea_pdebug("HttpHandler::ReloadWeb success to ask web reload!");
	});
	++m_reload_count;
}

//��ѯ��ҽ�ɫ��Ϣ
void HttpHandler::Handle_Query_Char_Info(const Request& req, Reply& rep)
{
	std::map<string,string> values;
	if(!fromJson(req.content,values))
	{
		rep.content = "{}";
		rep.status = hs::reply::internal_server_error;
		return;
	}
	LoadPlayer(values["RoleId"],[&](bool ret,const string &,vector<GuidObject*>& vec){
		std::map<string,string> data;			

		//////////////////////////////////////////////////////////////////////////
		//����
		//"body" :
		//{
		//	"RoleId" : "",           /* ��ɫID */
		//		"RoleName" : "",         /* ��ɫ�� */
		//		"Level" : ,              /* ��ɫ�ȼ� */
		//		"Fight" : ,              /* ��ɫս�� */
		//		"Vip" : ,                /* VIP�ȼ� */
		//		"CreateTime" : "",       /* ��ɫ����ʱ�� */
		//		"LastLoginTime" : ""     /* �ϴε�¼ʱ�� */
		//}
		logind_player *player = nullptr;
		for (auto it:vec)
		{
			if(player = dynamic_cast<logind_player*>(it))
				break;
		}

		auto account = values["Account"];
		if(!player|| (!account.empty() && player->GetAccount()!=account))
		{
			data["err"] = "-101";				
			rep.content = toJson(data);
			return;
		}

		data["err"] = "0";
		data["RoleId"] = player->guid();		
		data["RoleName"] = player->GetName();
		data["Level"] = std::to_string(player->GetLevel());
		data["Fight"] = std::to_string(player->GetForce());
		//data["Vip"] = std::to_string(player->GetVIPLevel());
		data["CreateTime"] = std::to_string(player->GetCreateTime());
		data["LastLoginTime"] = std::to_string(player->GetLastLoginTime());
		rep.content = toJson(data);
	});
}

//�Ϸ������������
void HttpHandler::Handle_Merge_Postdata(const Request& req, Reply& rep)
{
	tea_pinfo("merge/postdata begin");
	Tokens token;
	StrSplit(token, req.content, MERGE_DATA_SEPARATOR);
	if(token.size() != 4)
	{
		tea_pinfo("merge/postdata err token.size() != 4");
		rep.content = "{}";
		rep.status = hs::reply::internal_server_error;
		return;
	}

	string server_name = token[0];
	string guid = token[1];
	tea_pinfo("merge/postdata %s %s %u", server_name.c_str(), guid.c_str(), token[2].length());
	if(GuidManager::GetPrefix(guid) != ObjectTypePlayer || token[2].empty())
	{
		tea_pinfo("merge/postdata err GuidManager::GetPrefix(guid) != ObjectTypePlayer || token[2].empty()");
		rep.content = "{}";
		rep.status = hs::reply::internal_server_error;
		return;
	}

	bool b = false;
	//�������Σ�����
	for (int i = 0; i <= 3; i++) {
		if(g_Cache.SaveData(guid, token[2])) {
			b = true;
			break;
		} else {
			tea_pinfo("merge/postdata save data fail %s %s %u", server_name.c_str(), guid.c_str(), i);
		}
	}
	
	if (!b) {
		tea_pinfo("merge/postdata fail %s %s", server_name.c_str(), guid.c_str());
		rep.content = "{}";
		rep.status = hs::reply::internal_server_error;
		return;
	}

	for (int i = 0; i <= 3; i ++) {

		string str = token[ 3 ];
		if (str.length() == 1) {
			str = "";
		}

		if(str.empty() || g_Cache.SaveMailData(guid, str)) {
			rep.content = "ok";
			rep.status = hs::reply::ok;
			tea_pinfo("merge/postdata end");
			return;
		} else {
			tea_pinfo("merge/postdata save mail data fail %s %s %u", server_name.c_str(), guid.c_str(), i);
		}
	}

	tea_pinfo("merge/postdata fail %s %s", server_name.c_str(), guid.c_str());
	rep.content = "{}";
	rep.status = hs::reply::internal_server_error;
}

//�Ϸ����
void HttpHandler::Handle_Merge_Ok(const Request& req, Reply& rep)
{
	tea_pinfo("merge/ok begin");
	Tokens token;
	StrSplit(token, req.content, MERGE_DATA_SEPARATOR);
	if(token.size() != 4)
	{
		tea_pinfo("merge/ok err token.size() != 4");
		rep.content = "{}";
		rep.status = hs::reply::internal_server_error;
		return;
	}

	string server_names = token[0];
	Tokens server_tokens;
	StrSplit(server_tokens, server_names, ';');
	string server_name = server_tokens[0];
	tea_pinfo("merge/ok %s", server_name.c_str());
	if(server_name.empty() || token[1].empty())
	{
		tea_pinfo("merge/ok err server_name.empty() || token[1].empty()");
		rep.content = "{}";
		rep.status = hs::reply::internal_server_error;
		return;
	}
	//��load��web
	if(LogindApp::g_app->m_http)
		LogindApp::g_app->m_http->ReloadWeb();
	//֪ͨ�����������Ϸ���
	WorldPacket pkt (INTERNAL_OPT_LOGIND_MERGE_SERVER);
	pkt << server_name;
	ServerList.ForEachScened([&](uint32 fd){
		LogindApp::g_app->SendToScened(pkt, fd);
		return false;
	});	
	LogindApp::g_app->SendToPoliced(pkt);
	pkt << token[1];
	LogindApp::g_app->SendToAppd(pkt);
	//������guid
	Tokens token_gv;
	StrSplit(token_gv, token[1], '\n');
	//uint32 isss = token_gv.size();
	//ASSERT(token_gv.size() % 3 == 0);
	for (uint32 i = 0; i + 3 <= token_gv.size(); i+=3)
	{
		string guid = token_gv[i];
		if(guid == GLOBAL_GUID_MANAGER_GUID)
		{
			BinLogObject *obj = new BinLogObject;
			obj->FromString(token_gv[i + 1], token_gv[i + 2]);
			LogindApp::g_app->call_sync_guids_max(obj->GetUInt32(ObjectTypePlayer));
			delete(obj);
			break;
		}
	}

	//TODO: token[ 2 ] ���ɻ�����Ϣ
	//������guid
	parseMergeData(token[ 2 ], FACTION_BINLOG_OWNER_STRING);
	// token[ 3 ] ����������Ϣ
	parseMergeData(token[ 3 ], FACTION_DATA_OWNER_STRING);
	// token[ 4 ] �����Ϣ
	parseMergeData(token[ 4 ], GROUP_BINLOG_OWNER_STRING);

	//�����ºϷ��������б�
	for(auto it:server_tokens)
	{
		LogindApp::g_app->AddServerID(it);
	}
	//������������
	LogindApp::g_app->SetShowServerID();
	//���ý�ɫ�б��ȡ�ô����ݿ�ȡ
	g_DAL.SetLocaldb(false);
	//�Ϸ����ˣ�web������ע��һ��
	RegisterWeb(true);
	tea_pinfo("merge/ok end");
}

void HttpHandler::Handle_SetGmlevel(const Request& req, Reply& rep)
{
	std::map<string,string> values;
	if(!fromJson(req.content, values))
	{
		rep.content = MakeResponse(1, "post data is empty!");
		rep.status = hs::reply::internal_server_error;
		return;
	}

	if (values["account"].empty() || values["gm_level"].empty())
	{
		rep.content = MakeResponse(2, "has empty data!");
		rep.status = hs::reply::internal_server_error;
		return;
	}

	uint32 sessionID = LogindContext::FindSessionID(values["account"]);
	if(!sessionID)
	{
		rep.content = MakeResponse(3, "account is invalid!");
		rep.status = hs::reply::internal_server_error;
		return;
	}
	LogindContext *session = LogindContext::FindContext(sessionID);
	if(!session)
	{
		rep.content = MakeResponse(4, "session not find!");
		rep.status = hs::reply::internal_server_error;
		return;
	}
	if(session->GetPlayer() && session->GetPlayer()->GetGmNum() != atoi(values["gm_level"].c_str()))
		session->GetPlayer()->SetGmNum(atoi(values["gm_level"].c_str()));
	
	rep.content = MakeResponse(0, "set gm_level success!");
	rep.status = hs::reply::ok;
}


//ȡ���������������Ƶĵ�¼������url
string HttpHandler::GetLogindPostUrl(const string &server_name)
{
	auto *g = dynamic_cast<GlobalValueManager*>(LogindApp::g_app);
	auto conf_svr_url = g->GetConfSvrUrl();//g->GetExtWebInterface();

	std::map<string,string> data;
	data["server_name"] = server_name;
	data["type"] = "logind";

	string response;
	int ret = m_client->post(getUrl(conf_svr_url,"/cow_config/app_addr/query"),toQueryString(data),response);

	if(ret != 200)
		return "";
	
	map<string,string> map;
	fromJson(response, map);
	return map["data"];
}

//�������ݵ�����
bool HttpHandler::PostMergeData(const string &guid, const string &to_server_name)
{
	ASSERT(GuidManager::GetPrefix(guid) == ObjectTypePlayer);
	string url = GetLogindPostUrl(to_server_name);
	ASSERT(!url.empty());
	url = getUrl(url, "/merge/postdata");
	tea_pinfo("HttpHandler::PostMergeData %s %s %s", guid.c_str(), to_server_name.c_str(), url.c_str());
	string player_data_str = g_Cache.GetPlayerDataStr(guid);
	string player_mail_str = g_Cache.GetPlayerMailDataStr(guid);
	string data = LogindApp::g_app->GetServerID() + MERGE_DATA_SEPARATOR + guid + MERGE_DATA_SEPARATOR + player_data_str + MERGE_DATA_SEPARATOR + player_mail_str;
	string reponse;
	int result_code = m_client->post(url, data, reponse);
	if(result_code != 200)
	{
		tea_pinfo("HttpHandler::PostMergeData fail, err code %d, %s", result_code, reponse.c_str());
		return false;
	}
	return reponse == "ok";
}

//���ͺϷ���ɵ�����
bool HttpHandler::PostMergeOK(const string &to_server_name)
{
	tea_pinfo("HttpHandler::PostMergeOK %s ", to_server_name.c_str());
	string url = GetLogindPostUrl(to_server_name);
	ASSERT(!url.empty());
	url = getUrl(url, "/merge/ok");
	string global_str = g_Cache.GetPlayerDataStr(GLOBAL_VALUE_OWNER_STRING);
	string faction_str = g_Cache.GetPlayerDataStr(FACTION_BINLOG_OWNER_STRING);
	string faction_data_str = g_Cache.GetPlayerDataStr(FACTION_DATA_OWNER_STRING);
	string group_str = g_Cache.GetPlayerDataStr(GROUP_BINLOG_OWNER_STRING);

	//ȡ�����кϷ���
	vector<string> server_names;
	LogindApp::g_app->GetMergeServerName(server_names);
	string all_server_names;
	StrJoin(server_names,all_server_names, ';');

	string data = all_server_names + MERGE_DATA_SEPARATOR + global_str + MERGE_DATA_SEPARATOR + faction_str + MERGE_DATA_SEPARATOR + faction_data_str + MERGE_DATA_SEPARATOR + group_str;
	string reponse;
	int result_code = m_client->post(url, data, reponse);
	if(result_code != 200)
	{
		tea_pinfo("HttpHandler::PostMergeOK fail, err code %d, %s", result_code, reponse.c_str());
		return false;
	}
	return true;
	//return reponse == "ok";
}

//��web�ӿڷ�ȡ����������Ϣ
string HttpHandler::GetWebConfig(const string& key,const string& defaultValue)
{
	auto *g = dynamic_cast<GlobalValueManager*>(LogindApp::g_app);
	auto conf_svr_url = g->GetConfSvrUrl();//g->GetExtWebInterface();
	if(conf_svr_url.empty())
		return defaultValue;

	//�����������ֱ�ӷ���
	static std::map<string,string> webConfigCache;
	if(webConfigCache.find(key) != webConfigCache.end())
		return webConfigCache[key];

	std::map<string,string> queryMap;
	queryMap["pid"] = g->GetPlatformID();
	queryMap["sid"] = g->GetServerID();
	queryMap["key"] = key;

	string response;
	int ret = m_client->post(getUrl(conf_svr_url,"/cow_config/game_config/get"),toQueryString(queryMap),response);
	
	//����200��ǿ�˵��ֵ��ȷ
	if(ret == 200 && !response.empty())
	{
		webConfigCache[key] = response;
		return response;
	}
	else 
		return defaultValue;
}

string HttpHandler::MakeResponse(int ret, string msg)
{
	stringstream ss;
	ss << ret;	
	std::map<string,string> response;
	response["ret"] = ss.str();
	response["msg"] = msg;
	return toJson(response);
}

//����
void HttpHandler::Handle_Kicking(const Request& req, Reply& rep)
{	
	std::map<string,string> values;
	if(!fromJson(req.content, values))
	{
		rep.content = MakeResponse(1, "post data is empty!");
		rep.status = hs::reply::internal_server_error;
		return;
	}
	if (values["guid"].empty())
	{
		rep.content = MakeResponse(2, "guid is empty!");
		rep.status = hs::reply::internal_server_error;
		return;
	}

	//��ȡһ���������
	string account = g_DAL.GetAccountFromGuid(values["guid"]);
	if(!account.empty())
	{
		GmTable.KickingPlayer(account, KICKING_TYPE_GM_KICKING);
		rep.content = MakeResponse(0, "kicking player success!");
		rep.status = hs::reply::ok;
	}
	else
	{
		rep.content = MakeResponse(3, "kicking player fail!");
		rep.status = hs::reply::internal_server_error;
	}
}

//���ԡ����
void HttpHandler::Handle_Gag(const Request& req, Reply& rep)
{	
	std::map<string,string> values;
	if(!fromJson(req.content, values))
	{
		rep.content = MakeResponse(1, "post data is empty!");
		rep.status = hs::reply::internal_server_error;
		return;
	}
	if (values["guid"].empty() || values["type"].empty() || values["end_time"].empty())
	{
		rep.content = MakeResponse(2, "has empty data!");
		rep.status = hs::reply::internal_server_error;
		return;
	}

	//��ȡһ���������
	string guid = values["guid"];
	logind_player *player = ObjMgr.FindPlayer(guid);
	if(player == NULL)
	{
		rep.content = MakeResponse(3, "not find player, maybe not online!");
		rep.status = hs::reply::internal_server_error;
		return;
	}
	uint32 type = atoi(values["type"].c_str());
	uint32 end = atoi(values["end_time"].c_str());

	//���ý���ʱ�� 0,���ԣ�1��������� 
	player->SetGagEndTime(type == 0 ?end:0);
	//���ڲ�Э�鵽��־�����½���״̬
	GmTable.Send2PolicedUpdateGagStauts(guid, player->GetGagEndTime());
	rep.content = MakeResponse(0, "gag player success!");
	rep.status = hs::reply::ok;
}

//����gmQQ����
void HttpHandler::Handle_QQ_Config(const Request& req, Reply& rep)
{
	JsonArray ar;
	if(!fromJsonArray(req.content, ar))
	{
		rep.content = MakeResponse(1, "post data is empty!");
		rep.status = hs::reply::internal_server_error;
		return;
	}

	for (auto iter = ar.begin(); iter != ar.end(); ++iter)
	{
		//��ȡһ���������
		string qq_data = (*iter)["qq_info"];
		string server_name = (*iter)["server_name"];
		string oldinfo = LogindApp::g_app->GetQQInfo();
		string qqInfo;
		if (oldinfo.empty())
		{
			qqInfo = "A:" + server_name + "," + qq_data;
		}
		else
		{
			//�±�����ֵ�����и�����Ǹ��»�������
			oldinfo = oldinfo.substr(2);
			Tokens token, token1;
			StrSplit(token, oldinfo, ';');
			bool bfind = false;
			for (auto it = token.begin(); it != token.end(); ++it)
			{
				token1.clear();
				StrSplit(token1, *it, ',');
				if (token1.size() != 3)
					continue;
				if (token1.at(0) == server_name)
				{//����
					*it = server_name + "," + qq_data;
					bfind = true;
					break;
				}				
			}
			if (bfind)
			{//ִ�и���
				qqInfo = "A:";
				for (auto it = token.begin(); it != token.end(); ++it)
				{
					qqInfo += *it + ";";
				}
				qqInfo = qqInfo.substr(0, qqInfo.size()-1);
			}
			else
			{//����
				qqInfo = oldinfo + ";" + server_name + "," + qq_data;
			}
		}
		LogindApp::g_app->SetQQInfo(qqInfo);
		rep.content = MakeResponse(0, "set qq_info success!");
		rep.status = hs::reply::ok;
	}
}

//���
void HttpHandler::Handle_Lock_Account(const Request& req, Reply& rep)
{	
	JsonArray ar;
	if(!fromJsonArray(req.content, ar))
	{
		rep.content = MakeResponse(1, "post data is empty!");
		rep.status = hs::reply::internal_server_error;
		return;
	}
	
	vector<string> locking_ids, end_locking_ids;
	for (auto iter = ar.begin(); iter != ar.end(); ++iter)
	{
		uint32 status = LOCKING_STATUS_END;
		status = GmTable.LockAccount((*iter)["account_id"], atol((*iter)["u_end_time"].c_str()));
		if (status == LOCKING_STATUS_END)
			end_locking_ids.push_back((*iter)["id"]);
		else
			locking_ids.push_back((*iter)["id"]);
	}

	std::map<string,string> response;
	string str;
	StrJoin(locking_ids, str, ',');	
	if (!str.empty())
		response["locking_ids"] = str;
	str.clear();
	StrJoin(end_locking_ids, str, ',');	
	if (!str.empty())
		response["end_locking_ids"] = str;
	response["ret"] = "0";
	response["msg"] = "lock account success!";
	rep.content = toJson(response);
	rep.status = hs::reply::ok;
}

//��÷�������ip/port
void HttpHandler::GetHostPortByServerName(const string& server_name, string& host, string& port)
{
	//�ȴӻ�����
	string ipport = m_serverHostportInfo[server_name];
	if (ipport.empty())
	{
		//����û�У�ȥ���÷�ȡ
		auto *g = dynamic_cast<GlobalValueManager*>(LogindApp::g_app);
		auto conf_svr_url = g->GetConfSvrUrl();
		if(conf_svr_url.empty())
			return;

		std::map<string,string> data;
		data["server_name"] = server_name;
		string response;
		m_client->post(getUrl(conf_svr_url, "/cow_config/addr_info/get"), toQueryString(data), response);
		std::map<string,string> querys;
		if(!parseURL(response,querys))
			return;
		
		if (!querys["ipport"].empty())
			m_serverHostportInfo[server_name] = querys["ipport"];		//���뻺��		
	}

	ipport = m_serverHostportInfo[server_name];
	if (!ipport.empty())
	{
		//�и��ip/port
		Tokens tokens;
		StrSplit(tokens, ipport, ":");
		if (tokens.size() == 2)
		{
			host = tokens.at(0);
			port = tokens.at(1);
		}
	}		
}

//��webע��ս������״̬
void HttpHandler::RegBattleSvrConn()
{
	auto *g = dynamic_cast<GlobalValueManager*>(LogindApp::g_app);
	auto flz_url = g->GetExtWebInterface();
	if (flz_url.empty())
		return;
	
	//ȡ��host��port
	string host, port;
	GetHostPortByServerName(g_Config.server_name.c_str(), host, port);
	char str_data[512] = {0};
	sprintf(str_data,"info=%s;%s;%s",g_Config.server_name.c_str(),host.c_str(),port.c_str());
	m_client->async_post(getUrl(flz_url, "/battble_server_reg"), str_data, [this](int status_code,const string& content){
		if (status_code == 200)
			tea_pdebug("RegBattleSvrConn success!");			
	});	
}
