#include "logind_app.h"
#include "logind_context.h"
#include "logind_script.h"
#include "logind_mongodb.h"
#include "logind_cache.h"
#include "map_manager.h"
#include "logind_context_login_mgr.h"
#include <shared/log_handler.h>
#include <object/OprateResult.h>
#include <comm/b64.h>
#include <comm/crypt.h>

#include "mobile_context.h"

//////////////////////////////////////////////////////////////////////////
//for LogindApp

//�洢����������ID��IP�Ͷ˿�
typedef std::pair<string,uint16> host_info;
typedef std::unordered_map<uint32, host_info> HostInfoMap;
static HostInfoMap gHostInfoMap;

//�洢�����е�IP������sessionkey
static std::unordered_map<string,string> ip2sessionkey;

//�������
int LogindApp::on_centd_guid_object_table(tcp_connection *,server_packet *pkt)
{ 
	static ByteArray bytes ;
	bytes.clear();
	bytes.writeBytes(pkt->content,pkt->wpos);
	bytes.position(0);
	ObjMgr.HandlePacket(0,pkt->head->optcode,bytes);
	return 0;
}

int LogindApp::on_netgd_create_conn(tcp_connection *, server_packet *pkt)
{
	int fd = 0;
	string remote_ip;
	uint16 remote_port;
	int ret = packet_read(pkt,(char*)&fd,sizeof(int));
	*pkt >> remote_ip >> remote_port;
	if(g_app->GetStatus() != APP_STATUS_READY_OK)
	{
		tea_pwarn("on_netgd_create_conn server data loading, fd:%u,ip:%s,port:%u",fd,remote_ip.c_str(),remote_port);	
		return 0;
	}
	gHostInfoMap[fd] = std::make_pair(remote_ip, remote_port);
	tea_pdebug("on_netgd_create_conn fd:%u,ip:%s,port:%u",fd,remote_ip.c_str(),remote_port);	
	return 0;
}

int LogindApp::on_netgd_destory_conn(tcp_connection *, server_packet *pkt)
{
	int fd = 0;
	int ret = packet_read(pkt,(char*)&fd,sizeof(int));
	//fd���������λ���ҳ��
	CommonContext *context = CommonContext::FindContext(fd);	
	if(context)
	{
		tea_pdebug("on_netgd_destory_conn fd:%u,ip:%s,port:%u",fd,context->m_remote_ip.c_str(),context->m_remote_port);
		if(context->GetAccount().empty())
		{
			context->OnClosed();
			safe_delete(context);
		}
		else
		{
			g_app->m_login_queue->PushAction(context->GetGuid(), context->GetFD(), CONTEXT_LOGIN_ACTION_CLOSE);
		}
	}
	else
	{
		tea_pwarn("on_netgd_destory_conn but not found! fd:%u",fd);
	}
	gHostInfoMap.erase(fd);
	return 0;
}

//�⿪�ͻ��˴��͹�����,Ŀǰ��Ҫ�Ĳ���������
//pid,sid,uid,indulge,hosting,otherdata,time
bool ParseSessionKey(const char *session_key,std::map<string,string>& querys)
{	
	/*�����ԵȺſ�ͷ*/
	if(*session_key != '?')
		return false; 

	std::map<string,string> tmpQuerys;
	if(!parseURL(session_key+1,tmpQuerys))
		return false;

	string auth = tmpQuerys["auth"];	//auth���ݵ�У���룬����У�������Ƿ�����޸ġ�
	string sign = tmpQuerys["sign"];	//�������ݣ������û��ʺŵ���Ϣ������ͨ��base64���롣

	//auth��base64����,����
	static char tmp[1024];
	memset(tmp, 0, sizeof(tmp));

	if(base64_decode(tmp,sizeof(tmp),auth.c_str(),auth.size()+1) != 0)
	{
		tea_perror("base64_decode");
		return false;
	}

	if(!parseURL(tmp,querys))
		return false;

	//��֤key����Ч��
	//84adc98ee63b26e2063a796ac982ad77
	string auth_temp = auth + g_Config.login_key;
	const char * md5_str = MD5CryptToStr32((int8*)auth_temp.c_str(),auth_temp.size(),tmp);
	if(sign != md5_str && querys["uid"]!= g_Config.test_server_live_uid)
	{
		//��������Կ��У����
		auth_temp = auth + WANNENG_LOGIN_KEY;
		md5_str = MD5CryptToStr32((int8*)auth_temp.c_str(),auth_temp.size(),tmp);
		if(sign != md5_str)
		{
			tea_pwarn("ParseSessionKey sign:%s md5_str:%s",sign.c_str(),md5_str);
			return false;
		}
	}

	//�ǿ�ѡ�����
	if( querys["pid"].empty() || querys["sid"].empty() || querys["uid"].empty())
	{
		tea_pwarn("pid:%s sid:%s uid:%s failed",querys["pid"].c_str(),querys["sid"].c_str(),querys["uid"].c_str());	
		return false;
	}

	return true;
}

//����session��֤�Ƿ��Ѿ�����
bool CheckSessionKeyTimeout(uint32 fd,const char* session_key, uint32 key_time, uint32 gaptime)
{
	//У��ʱ��
	if(!g_Config.check_session_key_time)
		return true;

	//�����ӵ�IP
	string this_ip = gHostInfoMap[fd].first;
	if (this_ip.empty())
	{
		tea_pwarn("CheckSessionKeyTimeout this_ip is empty!");		
		return false;
	}

	//����ϴε�IP������û�б仯�򲻹���
	if (ip2sessionkey[this_ip] == session_key)
		return true;
	
	//��֤ʱЧ��,�������
	uint32 now = (uint32)time(NULL);
	//�����������Ҳ��Ƕ�������������
	if(key_time < now - gaptime || key_time > now + gaptime)
	{
		tea_pwarn("CheckSessionKeyTimeout key_time is faild");		
		return false;
	}

	return true;
}

//�ͻ�����������
int LogindApp::on_create_conn_get_session(tcp_connection *,server_packet *pkt)
{
	uint32 fd;
	char *session_key;
	char *account;
	char *version;
	*pkt >> fd >> session_key >> account >> version;

	//�����¼��δ׼����
	if(g_app->m_status != APP_STATUS_READY_OK)
	{
		LogindApp::g_app->CloseSession(fd);
		tea_pwarn("LogindApp::on_create_conn_get_session g_app->m_status != APP_STATUS_READY_OK");
		return 0;
	}

	//��������Ѿ���֤session����Ч�Բ�������һ��map����GetSession
	map<string,string> querys;
	if(!ParseSessionKey(session_key,querys))
	{
		//��������������ģ���Ϊ�����һ̨�������ƽ̨�������ƽ̨��Կ������ͬ������tea_pdebug�ͺ�
		tea_pdebug("LogindApp::on_create_conn_get_session ParseSessionKey failed");
		LogindApp::g_app->CloseSession(fd);
		return 0;
	}

	uint32 gaptime = 900;		//ҳ��Ĭ��Ϊ15����
	if (querys["mobile"] == "y")		
		gaptime = 86400*365;	//����Ĭ��Ϊ24Сʱ
	//��֤һ��session_key��ʱЧ��
	if(!CheckSessionKeyTimeout(fd,session_key,atoi(querys["time"].c_str()), gaptime))
	{
		tea_pwarn("LogindApp::on_create_conn_get_session CheckSessionKeyTimeout failed");
		LogindApp::g_app->CloseSession(fd);
		return 0;
	}

	//������Ӳ�����,����ݽ⿪��session������д�����Ӧ��sessionʵ��
	LogindContext* login_context = NULL;
	MobileContext* mobile_context = NULL;
	CommonContext* session = CommonContext::FindContext(fd);
	if (session && session->GetContextType() == CONTEXT_TYPE_YEYOU)
	{
		login_context = dynamic_cast<LogindContext*>(session);
		if(login_context && login_context->GetStatus() == STATUS_NEVER)
		{
			tea_pwarn("LogindApp::on_create_conn_get_session create_sesstion duplicate!");
			login_context->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE13,"");
			return 0;
		}
	}
	else if (session && session->GetContextType() == CONTEXT_TYPE_PHONE)
	{
		mobile_context = dynamic_cast<MobileContext*>(session);
		if (mobile_context)
		{
			tea_pwarn("LogindApp::on_create_conn_get_session create_mobile_context duplicate!");
			mobile_context->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE55,"",true);
			//TODO: ��ʱ�Ҽӵ� �����ظ��Ĳ���Ҫreturnô ��������д��
			return 0;
		}
	}

	//�����Ự
	if (querys["mobile"] == "y")
	{
		auto *mobile_session = new MobileContext(fd,LogindApp::g_app);
		mobile_session->m_remote_ip = gHostInfoMap[fd].first;
		mobile_session->m_remote_port = gHostInfoMap[fd].second;
		LogindApp::g_app->InsertContext(mobile_session);
		mobile_session->Get_Session(querys);
		return 0;
	}
	
	//Ϊ���ŷ����
	if(!login_context)
	{
		login_context = new LogindContext(fd,LogindApp::g_app);//LogindContext::CreateContext(fd);
		if(querys["remote_ip"].empty())
			login_context->m_remote_ip = gHostInfoMap[fd].first;
		else
			login_context->m_remote_ip = querys["remote_ip"];
		login_context->m_remote_port = gHostInfoMap[fd].second;
		LogindApp::g_app->InsertContext(login_context);
	}	

	//Ҫô�ɹ�,Ҫôʧ��
	if(login_context->Get_Session(querys))
	{
		ip2sessionkey[login_context->m_remote_ip] = session_key;
	}
	else
	{
		login_context->Close(0,"");
	}
	return 0;
}

int LogindApp::on_scened_del_map(tcp_connection *, server_packet *pkt)
{
	uint32 fd, instanceid;
	*pkt >> fd >> instanceid;
	MapMgr->TryClose(instanceid);
	return 0;
}

//�������ķ��ɹ�,��ȡ��������������Ժ�
int LogindApp::on_get_online_player(tcp_connection *, server_packet *pkt)
{
	//�Ȱ����ķ���������һ��
	g_app->CallCentdCreateIndex();
	//���һЩ�����Ƿ���ڣ��������򴴽�
	g_app->CheckObject();
	//�������������������޸�
	if(LogindApp::g_app->m_server_conn_list->GetServerReadyCount(SERVER_TYPE_LOGIND))
	{
		g_app->CollapseReset(pkt);
	}
	else
	{
		tea_pinfo("logind init!");
		tea_pinfo("load global value begin");
		vector<GuidObject*> vec;
		g_app->m_cache->LoadGlobalValue();
		g_app->m_db_access_mgr->Load_GlobalValue();
		tea_pinfo("load global value end");

		tea_pinfo("load league value begin");
		g_app->m_cache->LoadFractionValue();
		tea_pinfo("load league value end");

		tea_pinfo("load faction data begin");
		g_app->m_cache->LoadFractionData();
		tea_pinfo("load faction data end");

		//����ű�
		scripts_init(g_Config.script_folder.c_str());
		LoadTemplate();

		g_app->OnDataReady();
	}
	
	return 0;
}

//gm����
int LogindApp::on_gm_commands(tcp_connection *,server_packet *pkt)
{
	string lguid;
	string str;
	*pkt >> lguid;
	*pkt >> str;

	tea_pinfo("player %s send gm command : %s", lguid.c_str(), str.c_str());

	logind_player *player = LogindContext::FindPlayer(lguid);
	if(!player)
		return 0;

	Tokens tokens;
	StrSplit(tokens, str, ' ');
	if(tokens.empty() || tokens[0].empty())
		return 0;


	int gm_comand_key = GetGmCommandKey(tokens[0]);

	if(gm_comand_key == GM_COMMAND_PINGBICI)//"@���δ�")
	{
		LogindApp::g_app->LoadFuckPingbi(LogindApp::g_app->GetConfig().storage_path);
	}
	else if(gm_comand_key == GM_COMMAND_ZAIXIAN)//"@����"
	{
		if (player->GetGMLevel()<GM_LEVEL_1)
		{		
			return 0;
		}
		stringstream ss;
		ss << "player��" << ObjMgr.indexer().get(REGEX_PLAYER)->size() << ",session:" << LogindContext::SessionMaps.size();
		//TODO: Call_chat_whisper(player->GetSession()->m_delegate_sendpkt,player->GetGuid().c_str(),player->GetFaction(),player->GetName().c_str(),ss.str().c_str());
	}
	else if(gm_comand_key == GM_COMMAND_SUICIDE)//@�Ա�
	{
		if (player->GetGMLevel()< GM_LEVEL_1)
		{
			return 0;
		}
		player->SetZiBao();
		//���ͻ���˵�Ա���
		Call_operation_failed(player->GetSession()->m_delegate_sendpkt,OPRATE_TYPE_LOGIN,OPRATE_RESULT_PLAYER_ZIBAO, player->GetAccount().c_str());
		//����Ӧ�÷���ɾ����
		WorldPacket pkt(INTERNAL_OPT_DEL_CHAR);
		pkt << player->GetGuid();
		LogindApp::g_app->SendToAppd(pkt);
		//ɾ����ɫ
		g_DAL.DelChars(player->GetGuid().c_str());
		//�������ɫɾ��
		g_Cache.AddAccountToChar(player->GetAccount(),"");
		g_Cache.SaveAccountCharInfo(player->GetAccount(), "");
		//�ر�����
		player->GetSession()->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE57,"");
	}
	else if(gm_comand_key == GM_COMMAND_CHONGZHI)//@��ֵ
	{
		if (player->GetGMLevel()< GM_LEVEL_3)
		{
			return 0;
		}
		uint32 value = 0;
		if(tokens.size() >= 2)
			value = atoi(tokens[1].c_str());
		uint32 type = 1;
		if(tokens.size() >= 3)
			type = atoi(tokens[2].c_str());
		if(value > 0 && type > 0 && type < 5)
			g_DAL.SetGmRechargeNum(player->GetAccount().c_str(),value,type);
	}
	else if(gm_comand_key == GM_COMMAND_KAIFUSHIJIAN)//@����ʱ��
	{
		if (player->GetGMLevel()< GM_LEVEL_3)
		{
			return 0;
		}
		uint32 open_time = 0;
		if(tokens.size() == 2)
		{
			open_time = atoi(tokens[1].c_str());
			g_app->SetKaiFuShiJian(open_time);
			g_DAL.UpdateKaiFuShiJian(open_time);
		}
		
	}
	else if(gm_comand_key == GM_COMMAND_TEST_SHUJU)//@��������
	{
		if (player->GetGMLevel()< GM_LEVEL_3)
		{
			return 0;
		}
	}
	else if(gm_comand_key == GM_COMMAND_UPDATE_SERVER)//@���·�����
	{
		if (player->GetGMLevel()< GM_LEVEL_3)
		{
			return 0;
		}
		if(tokens.size() == 2)
		{
			uint32 server_type = atoi(tokens[1].c_str());
			g_app->m_db_access_mgr->ServerUpdate(server_type);
		}
	}
	else if(gm_comand_key == GM_COMMAND_RESESSION_OPTS)//@Э��ע��
	{
		if (player->GetGMLevel()< GM_LEVEL_3)
		{
			return 0;
		}
		g_app->RegSessionOpts(player->GetSession()->GetFD());
	}
	else if(gm_comand_key == GM_COMMAND_DEL_MAP_INFO)//@��յ�ͼ��Ϣ
	{
		if (player->GetGMLevel()< GM_LEVEL_3)
		{
			return 0;
		}
		vector<GuidObject*> vec;
		ObjMgr.GetDataSetAllObject(MAP_INSTANCE_PLAYER_INFO_OWNER_STRING, vec);
		vector<string> vec_guid;
		for (auto it:vec)
		{
			vec_guid.push_back(it->guid());
		}
		for (auto it:vec_guid)
		{
			ObjMgr.CallRemoveObject(it);
		}
	}
	else if(gm_comand_key == GM_COMMAND_BACKUP_DATA)//@��������
	{
		if(tokens.size() == 2)
		{
			string backupfilename = tokens[1].c_str();
			g_app->SaveAllData();
			g_Cache.Backup(backupfilename);
		}
	}
	else if(gm_comand_key == GM_COMMAND_RETURN_DATA)	//@�ص�����
	{
		if(tokens.size() == 2)
		{
			string data_time = tokens[1].c_str();
			g_Cache.HuidangPlayerInfos(lguid,data_time);
		}
	}
	else if(gm_comand_key == GM_COMMAND_DB)	//@���ݿ�
	{
		bool save_all = false;
		if(tokens.size() == 2 && atoi(tokens[1].c_str()) == 1)
			save_all = true;
		g_Cache.SaveChangePlayerToDB(save_all);
	}
	else if(gm_comand_key == GM_COMMAND_SUBLINE)//"@����"
	{
		if (player->GetGMLevel()<GM_LEVEL_1)
		{		
			return 0;
		}

		uint32 map_id = player->GetMapId();
		if(tokens.size() >= 2)
			map_id = atoi(tokens[1].c_str());
		string general_id = "";
		if(tokens.size() >= 3)
			general_id = tokens[2];

		stringstream ss;
		ss << "map " << map_id << std::endl;

		for(uint32 lines = 0; lines < 100; lines++)
		{
			int32 index = MapMgr->FindInstance(map_id, general_id, lines);
			if (index < 0)
			{
				continue;
			}

			ss << "line " << lines << " count " << MapMgr->PlayerCount(index) << std::endl; 
		}

		//TODO: Call_chat_whisper(player->GetSession()->m_delegate_sendpkt,player->guid().c_str(), 0, player->GetName().c_str(), ss.str().c_str());	
		
		return 0;
	}
	else
	{
		//DoGMScripts(player, str);
	}
	return 0;
}

int LogindApp::on_offline_oper(tcp_connection *, server_packet *pkt)
{
	string guid, callback_name;
	uint32 callback_id;
	*pkt >> guid >> callback_id >> callback_name;

	//У��һ���Ƿ񱾷��Ķ���
	string guid_server_name = MongoDB::GetServerName(guid);
	if(!g_app->IsMyServer(guid_server_name))
	{
		tea_pinfo("LogindApp::on_offline_oper not local data, %s %s", guid.c_str(), callback_name.c_str());
		return 0;
	}


	vector<GuidObject*> vec;
	auto fun = [guid, callback_name, callback_id](bool need_free, vector<GuidObject*> &vec){
		//û���ݣ��Ǿ����˰�
		if(vec.empty())
		{
			tea_pwarn("LogindApp::on_offline_oper player info not found, %s %s", guid.c_str(), callback_name.c_str());
			return;
		}
		//�������
		static ByteArray bytes;
		bytes.clear();
		for (auto it:vec)
		{
			it->WriteCreateBlock(bytes);
			if(need_free)
				safe_delete(it);
		}
		WorldPacket wpkt(INTERNAL_OPT_OFFLINE_OPER);
		bytes.position(0);
		ObjMgr.Compress(bytes);
		wpkt << guid << callback_id << callback_name << bytes;
		LogindApp::g_app->SendToAppd(wpkt);
	};

	bool need_free = true;
	//�������
	//��Ҳ����ߣ�ȥӲ�̻������ݿ�ȡ
	auto ds = ObjMgr.FindDataSetByOwnerGuid(guid);
	if(!ds || ds->GetAllData().empty())
	{
		logind_player *player = nullptr;
		if(!g_Cache.LoadPlayer(guid, &player, vec) )
		{
			static map<uint32, vector<GuidObject*>> obj_vec_map;
			//ASSERT(obj_vec_map.find(callback_id) == obj_vec_map.end());
			obj_vec_map[callback_id].clear();
			g_DAL.LoadPlayer("", guid, obj_vec_map[callback_id],[fun, callback_name, guid](bool load_succeed, vector<GuidObject*> &vec){
				if(!load_succeed)
				{
					tea_pwarn("LogindApp::on_offline_oper player info db err, %s %s", guid.c_str(), callback_name.c_str());
					return;
				}
				if(vec.empty())
				{
					tea_pwarn("LogindApp::on_offline_oper player info db not found, %s %s", guid.c_str(), callback_name.c_str());
					return;
				}
				logind_player *player = dynamic_cast<logind_player*>(vec[0]);
				ASSERT(player);
				//�ȴ浽����Ӳ������
				g_Cache.SavePlayerData(guid, vec, player->GetLevel());
				fun(true, vec);
			});
			return 0;
		}
	}
	else//������õ�¼������
	{
		ObjMgr.GetDataSetAllObject(guid, vec);
		need_free = false;
	}

	fun(need_free, vec);
	return 0;
}

void ApplyBlock(ByteArray &bytes)
{
	while(bytes.bytesAvailable() > 0){
		int flags = bytes.readByte();		//�ȶ�����־

		string guid;
		
		guid = bytes.readUTF();
		auto cur_obj =ObjMgr.Get(guid);	

		core_obj::BinLogStru binlog;
		int len = bytes.readUnsignedShort();				
		for(int i = 0; i < len; i++){
			binlog.ReadFrom(bytes);

			switch (binlog.opt)
			{
			case core_obj::OPT_SET:
				switch (binlog.typ)
				{
				case core_obj::TYPE_DOUBLE:
					cur_obj->SetDouble(binlog.index,binlog.double_val);
					break;
				case core_obj::TYPE_UINT32:
				case core_obj::TYPE_INT32:
					cur_obj->SetInt32(binlog.index,binlog.value);
					break;
				case core_obj::TYPE_FLOAT:
					cur_obj->SetFloat(binlog.index, binlog.float_val);
					break;
				case core_obj::TYPE_INT16:
					cur_obj->SetInt16(binlog.index,binlog.offset,binlog.int16_val);
					break;
				case core_obj::TYPE_UINT16:
					cur_obj->SetUInt16(binlog.index,binlog.offset,binlog.uint16_val);
					break;
				case core_obj::TYPE_UINT8:
					cur_obj->SetByte(binlog.index,binlog.offset,binlog.byte_val);
					break;
				case core_obj::TYPE_BIT:
					cur_obj->SetBit(binlog.index,binlog.value);
					break;
				case core_obj::TYPE_STRING:
					cur_obj->SetStr(binlog.index,binlog.str_val);
					break;
				}
				break;
			case core_obj::OPT_UNSET:
				switch (binlog.typ)
				{
				case core_obj::TYPE_BIT:
					cur_obj->UnSetBit(binlog.index,binlog.value);
					break;
				default:
					ASSERT(0);
				}
				break;
			case core_obj::OPT_ADD:
				switch (binlog.typ)
				{
				case core_obj::TYPE_DOUBLE:
					cur_obj->AddDouble(binlog.index,binlog.double_val);
					break;
				case core_obj::TYPE_UINT32:
					cur_obj->AddUInt32(binlog.index,binlog.value);
					break;
				case core_obj::TYPE_INT32:
					cur_obj->AddInt32(binlog.index,binlog.int32_val);
					break;
				case core_obj::TYPE_FLOAT:
					cur_obj->AddFloat(binlog.index,binlog.float_val);
					break;
				case core_obj::TYPE_INT16:
					cur_obj->AddInt16(binlog.index,binlog.offset,binlog.int16_val);
					break;
				case core_obj::TYPE_UINT16:
					cur_obj->AddUInt16(binlog.index,binlog.offset,binlog.uint16_val);
					break;
				case  core_obj::TYPE_UINT8:
					cur_obj->AddByte(binlog.index,binlog.offset,binlog.byte_val);
					break;
				default:
					ASSERT(0);
				}
				break;
			case core_obj::OPT_SUB:
				switch (binlog.typ)
				{
				case core_obj::TYPE_DOUBLE:
					cur_obj->SubDouble(binlog.index,binlog.double_val);
					break;
				case core_obj::TYPE_UINT32:
					cur_obj->SubUInt32(binlog.index,binlog.value);
					break;
				case core_obj::TYPE_INT32:
					cur_obj->SubInt32(binlog.index,binlog.int32_val);
					break;
				case core_obj::TYPE_FLOAT:
					cur_obj->SubFloat(binlog.index,binlog.float_val);
					break;
				case core_obj::TYPE_INT16:
					cur_obj->SubInt16(binlog.index,binlog.offset,binlog.int16_val);
					break;
				case core_obj::TYPE_UINT16:
					cur_obj->SubUInt16(binlog.index,binlog.offset,binlog.uint16_val);
					break;
				case  core_obj::TYPE_UINT8:
					cur_obj->SubByte(binlog.index,binlog.offset,binlog.byte_val);
					break;
				}
				break;
			default:
				ASSERT(0);
			}
		}

	}    
}

int LogindApp::on_offline_oper_result(tcp_connection *, server_packet *pkt)
{
	string guid;
	*pkt >> guid;
	static ByteArray bytes;
	bytes.clear();
	bytes.writeBytes(pkt->content + pkt->rpos,pkt->wpos - pkt->rpos);
	bytes.position(0);
	//˵�����Ѿ�������
	if(ObjMgr.FindPlayer(guid))
	{
		ApplyBlock(bytes);
		return 0;
	}
	//��û���ߵģ��ǾͶ�Ӳ��дӲ�̰�
	vector<GuidObject*> vec;
	logind_player *player = nullptr;
	
	static core_obj::GuidObjectTable table_(core_obj::SYNC_SLAVE);
	if(g_Cache.LoadPlayer(guid, &player, vec))
	{
		//�Ž�����
		for (auto it:vec)
		{
			table_.AttachObject(it);
		}
		//Ӧ��binlog
		table_.ApplyBlock(bytes);
		//����
		g_Cache.SavePlayerData(guid, vec, player->GetLevel());
		//�������Ƴ�,��������ͷŹ�����
		for (auto it:vec)
		{
			table_.ReleaseObject(it->guid());
		}
	}
	else
	{
		//���ʵ�ڶ��������Ǿ�����
		tea_pwarn("LogindApp::on_offline_oper_result load player fail %s", guid.c_str());
	}
	return 0;
}

int LogindApp::on_save_all_data(tcp_connection *, server_packet *pkt)
{
	//��ӡһ��
	tea_pinfo("LogindApp::on_save_all_data centd");
	//����������Ϣ
	//g_app->SaveAllData();
	return 0;
}

//��ͼ����ͼ����
int LogindApp::on_map_router_pkt(tcp_connection* coon, server_packet* pkt)
{
	MapMgr->HandleMapPkt(pkt);
	return 0;
}


//�йܵ�¼
int LogindApp::on_logind_hosting(tcp_connection* coon, server_packet* pkt)
{
	string player_guid,hosting_guid;
	*pkt >> player_guid >> hosting_guid;
	logind_player *player = LogindContext::FindPlayer(player_guid);
	string hosting_account = g_DAL.FindAccountByGuid(hosting_guid);
	//�˺���Ϣ
	account_table *accountInfo = g_Cache.GetAccount(hosting_account);
	//bool load_result = g_DAL.LoadAccount(hosting_account, &accountInfo);
	if (player && player->GetSession() && accountInfo != NULL)
	{
		//bool is_fcm = accountInfo->is_FCM != 1;
		//�йܾͲ���������
		bool is_fcm = false;
		Call_operation_failed(player->GetSession()->m_delegate_sendpkt,OPERTE_TYPE_HOSTING,HOSTING_OPERTE_LOGIN,
			LogindApp::g_app->MakeSessionKey(hosting_account,is_fcm,"","", true).c_str());
	}	
	return 0;
}

int LogindApp::on_kuafu_enter(tcp_connection* , server_packet* pkt) {
	uint32 kuafu_type, pos;
	string player_guid, war_id, battle_server, watcher_guid;
	
	*pkt >> player_guid >> war_id >> pos >> battle_server >> watcher_guid >> kuafu_type;

	logind_player *m_player = LogindContext::FindPlayer(player_guid);
	if (!m_player)
	{
		tea_pdebug("LogindContext::on_kuafu_enter m_player is null!");
		return 1;
	}

	if (!m_player->GetSession())
	{
		tea_pdebug("func on_kuafu_enter player session is null !!! guid = %s", player_guid.c_str());
		return 1;
	}

	if (kuafu_type == KUAFU_TYPE_FENGLIUZHEN || kuafu_type == KUAFU_TYPE_XIANFU || kuafu_type == KUAFU_TYPE_GROUP_INSTANCE)
	{
		//������

		// war_id = "1486557614#23#p1200.2_1003#p1197.2_1003"
		// ֱ��
		//battle_server = "2_65534;192.168.88.5;443"
		//�и��ַ���
		

		Tokens token1;
		StrSplit(token1, war_id, '#');
		uint32 room_id = atol(token1[0].c_str());			//����id

		Tokens token;
		StrSplit(token, battle_server, ';');
		if (token.size() != 3)
		{
			tea_pdebug("func on_kuafu_enter data is %s, token.size() != 3", battle_server.c_str());
			return 1;
		}

		string battle_server_name = token[0];
		string host = token[1];
		string port = token[2];

		//�����У��Ķ���У������
		if(!m_player->GetFlags(PLAYER_APPD_INT_FIELD_FLAGS_FROM_KUAFU))
			m_player->SetFlags(PLAYER_APPD_INT_FIELD_FLAGS_FROM_KUAFU);			//�ѿ����־����

		//����ƥ����Ϣ���ɵ�¼��
		bool is_fcm = m_player->GetFCMLoginTime() != (-1);
		char other_temp[1024] = {0};
		//��Ϸ��server_name|�������|����id|�����ս����server_name|int������|str������
		sprintf(other_temp, "&backsvrname=%s&kuafutype=%d&warid=%u&battlesvrname=%s&kuafureserve=%d&reservestr=%s", 
			g_Config.server_name.c_str(), kuafu_type, room_id, battle_server_name.c_str(), pos, war_id.c_str());	
		string session_str = LogindApp::g_app->MakeSessionKey(m_player->GetAccount(),is_fcm, other_temp, WANNENG_LOGIN_KEY);

		//֪ͨ�ͻ��˶Ͽ���Ϸ������pk��
		m_player->GetSession()->Call_World_War_CS_Player_Info(host, atoi(port.c_str()), session_str);
	}

	return 0;
}

int LogindApp::on_rename_check(tcp_connection* coon, server_packet* pkt) {
	string player_guid;
	string name;

	*pkt >> player_guid >> name;

	bool ret = false;
	string realName;
	logind_player *m_player = LogindContext::FindPlayer(player_guid);
	if (m_player && m_player->GetSession()) {
		account_table *accountInfo = g_Cache.GetAccount(m_player->GetAccount());
		string prefix = string(accountInfo->pid) + "," + string(accountInfo->sid) + ",";
		ret = m_player->GetSession()->Check_Name(name, realName, prefix);
	}
	uint32 available = (ret ? 1 : 0);
	// ���͸�Ӧ�÷�
	WorldPacket wpkt(INTERNAL_OPT_RENAME_CHECK_RESULT);
	wpkt << player_guid << available << realName;
	LogindApp::g_app->SendToAppd(wpkt);

	return 0;
}

int LogindApp::on_update_charname(tcp_connection* coon, server_packet* pkt) {
	string player_guid;
	string name;

	*pkt >> player_guid >> name;
	logind_player *m_player = LogindContext::FindPlayer(player_guid);
	if (m_player) {
		m_player->GetSession()->Char_Name_Update(name);
	}
	return 0;
}

//�����ÿ������Ϸ��
int LogindApp::on_kuafu_back_to_game(tcp_connection* coon, server_packet* pkt) {
	// �����հ�����
	packet pack;

	string player_guid;
	*pkt >> player_guid;
	logind_player *m_player = LogindContext::FindPlayer(player_guid);
	if (m_player) {
		m_player->GetSession()->Handle_GoBackTo_GameServer(pack);
	}
	return 0;
}

//����������
int LogindApp::on_faction_invite_result(tcp_connection* coon, server_packet* pkt) {

	string player_guid;
	string faction_id;
	uint32 mapid;
	uint32 x;
	uint32 y;
	string general_id;

	*pkt >> player_guid >> faction_id >> mapid >> x >> y >> general_id;
	logind_player *m_player = LogindContext::FindPlayer(player_guid);
	if (m_player && m_player->GetSession()) {
		m_player->GetSession()->onSetInvitedTeleportInfo(faction_id, mapid, x, y, general_id);
	}
	return 0;
}