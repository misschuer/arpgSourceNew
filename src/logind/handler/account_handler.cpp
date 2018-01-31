
#include "logind_app.h"
#include "logind_context.h"
#include "logind_context_login_mgr.h"
#include <shared/log_handler.h>
#include <object/OprateResult.h>

#include "logind_mongodb.h"
#include "logind_cache.h"
#include "logind_script.h"
#include "map_manager.h"
#include "http_handler.h"

/*��ȡsessionKey����*/
bool LogindContext::Get_Session(std::map<string,string>& querys)
{
	 //����Ѿ���¼����
    if(!m_account.empty() || m_player)
    {
    	tea_perror("account[%s] re get session", m_account.c_str());	
		//Call_operation_failed(m_delegate_sendpkt,OPERTE_TYPE_CLOSE,PLAYER_CLOSE_OPERTE_LOGDIN_ONE40,"");
    	return false;
    }

	//����URL
	string pid = querys["pid"],sid = querys["sid"],uid = querys["uid"],fcm = querys["indulge"], platdata = querys["platdata"];
	//����Ƿ��йܵĵ�¼
	m_is_hosting = querys["hosting"]=="y";
	bool indulge = fcm=="y";
	m_isFcm = indulge;
	if (!fcm.empty())
		m_bHasfcm = true;
	if (!platdata.empty())
		m_bHasplatdata = true;
	
	m_watcher_guid = querys["watcher"];
	//�ǹ۲���
	if (!m_watcher_guid.empty())
	{
		//���ڲ�Э�鵽������,����������·���Ӧ�ĵ�ͼ���ݵ�
		m_general_id = querys["generalid"];
		if(!SendToScenedAddMapWatcher())
			return false;
	}
	//�ʻ����ƣ������ж�һ���Ƿ񳬳�
	m_account = pid+"_"+sid+"_"+uid;
	if(m_account.size() >= sizeof((account_table*)NULL)->name)
	{
		tea_perror("m_account_string:%s too long!",m_account.c_str());
		Call_operation_failed(m_delegate_sendpkt,OPERTE_TYPE_CLOSE,PLAYER_CLOSE_OPERTE_LOGDIN_ONE41,"");
		return false;
	}

	//ȡ�������Ϣ
	m_backsvrname = querys["backsvrname"];
	m_kuafutype = (uint8)atol(querys["kuafutype"].c_str());
	m_warid = atol(querys["warid"].c_str());
	m_kuafu_svrname = querys["battlesvrname"];
	m_number = atol(querys["kuafunumber"].c_str());
	m_kuafu_reserve = atol(querys["kuafureserve"].c_str());
	m_kuafu_reserve_str = querys["reservestr"];
	string invited = querys["factionguid"];

	//���ݹ��������û�����,����������Ⱦ͹ر�����
	m_from_server_name = pid+"_"+sid;
	string svr_name = m_from_server_name;
	if (!m_kuafu_svrname.empty())
		svr_name = m_kuafu_svrname;

	//��֤session_key�Ƿ���Ե�¼���������
	if(!Get_Server_List(svr_name))
	{
		//�����ض����ķ��Ĳ���ʽ�������ӡ��ǳ���������ӡ�ȼ�����Ҫ��
		tea_pdebug("m_from_server_name:%s is't in this server",m_from_server_name.c_str());
		//Call_operation_failed(m_delegate_sendpkt,OPRATE_TYPE_LOGIN,OPRATE_RESULT_PID_OR_SID_ERROR, "");
		//Call_operation_failed(m_delegate_sendpkt,OPERTE_TYPE_CLOSE,PLAYER_CLOSE_OPERTE_LOGDIN_ONE43,"");
		return false;
	}

	tea_pdebug("account %s getsession!", m_account.c_str());

	//״̬�����֤ͨ��	
	SetStatus(STATUS_AUTHED);

	uint32 old_fd = LogindContext::FindSessionID(m_account);
	//��ǰ�Ѿ����� ���� ��session�������ҵ���ԱҲ��Ϊ���Ѿ��н�ɫ����
	if (old_fd)
	{
		//����������Ϣ
		tea_pwarn("LogindContext::Get_Session %s, but char online", m_account.c_str());

		//֪ͨ���ط�,���԰Ѷ��˵�Э��ת���������������а취����������	
		LogindApp::g_app->RegSessionOpts(GetFD(),CMSG_FORCED_INTO);			
		//m_is_canInto = true;

		//֪ͨ��ɫ�Ѿ���¼
		Call_operation_failed(m_delegate_sendpkt,OPRATE_TYPE_LOGIN,OPRATE_RESULT_LOGINED_IN, m_account.c_str());

		//֪ͨ�Ѿ���¼�Ŀͻ���
		auto old_context = LogindContext::FindContext(old_fd);
		if(old_context)
			Call_operation_failed(old_context->m_delegate_sendpkt,OPRATE_TYPE_LOGIN,OPRATE_RESULT_OTHER_LOGINED, m_account.c_str());

		return true;
	}


	//������ǿ��
	if(m_kuafu_svrname.empty())
	{
		//�����ƽ̨�ʻ����ε�¼				
		account_table *info = g_DAL.UpsertAccount(m_account,pid,sid,uid,indulge,m_remote_ip,platdata);
		ASSERT(info);

		int fd = GetFD();
		g_DAL.GetCharsList(m_account,[fd,this,invited](bool sucess,vector<char_create_info> chars) {
			auto *session = LogindContext::FindContext(fd);
			if(!session) return;
			string faction_name;
			string queen_name;
			uint8 icon = 0;
			// ����Ǳ��������Ҫ��ʾ��ǰ������Ϣ
			if (chars.size() == 0 && !invited.empty()) {
				// ��ѯ������Ϣ
				BinLogObject *factionInfo = (BinLogObject*)ObjMgr.Get(invited);
				if (factionInfo) {
					faction_name = factionInfo->GetStr(BINLOG_STRING_FIELD_NAME);
					queen_name = factionInfo->GetStr(FACTION_STRING_FIELD_MANGER_NAME);
					icon = factionInfo->GetByte(FACTION_INT_FIELD_FLAGS_ID, 0);
				}
			}
			Call_chars_list(session->m_delegate_sendpkt, chars, faction_name.c_str(), queen_name.c_str(), icon);
		});
	}
	else
	{
		string faction_name;
		string queen_name;
		//�ǿ���Ļ���ֱ�Ӹ����ս�ɫ�б�Ϳ�����
		vector<char_create_info> char_list;
		Call_chars_list(m_delegate_sendpkt, char_list, faction_name.c_str(), queen_name.c_str(), 0);
	}

	//������Э��ע��һ��
	LogindApp::g_app->RegSessionOpts(fd_);
	SessionMaps[m_account] = GetFD();					//���ڲ�������Session			

	//ͨ���˰�����Э��ע������ķ�������ΪĬ������	
	LogindApp::g_app->RegSessionOpts(GetFD(),CMSG_GET_SESSION,ServerList.GetCentdFd());

	//Ϊ�ͻ��˼��������µ�ģ����Ϣ
	ObjMgr.CallAddWatch(fd_, GLOBAL_CLIENT_GAME_CONFIG);	

	return true;
}



uint16 __CheckName1(string name)
{

	if (Pingbi((char*)name.c_str()))
	{
		tea_pdebug("error: has pingbi !!!");
		return OPRATE_RESULT_NAME_HAS_PINGBI;
	}

	if (name == "")
	{
		tea_pdebug("error: name is null !!!");
		return OPRATE_RESULT_NAME_ILLEGAL;
	}
	auto& vec = g_Config.g_cant_make_name;
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		if(name.find(*it) != string::npos)
		{
			tea_pdebug("error: has illegal char");
			return OPRATE_RESULT_NAME_ILLEGAL;
		}
	}
	return OPRATE_RESULT_SUCCESS;
}

uint16 __CheckName2(string name, int additionSize)
{
	if (name.size() > uint32(20 + additionSize))
	{
		tea_pdebug("error:name is too long!!!");
		return OPRATE_RESULT_NAME_TOO_LONG;
	}

	bool has_err;
	string guid = g_DAL.FindGuidByName(name, has_err);
	if(has_err)
	{
		tea_pinfo("g_DAL.FindGuidByName(name, has_err); %s ", name.c_str());
		return OPRATE_RESULT_DB_RESULT_ERROR;
	}

	if (!guid.empty())
	{
		tea_pdebug("error: name repeat : %s",name.c_str());
		return OPRATE_RESULT_NAME_REPEAT;		
	}

	return OPRATE_RESULT_SUCCESS;
}

void LogindContext::Handle_Foeced_Into(packet &)
{
	//if (!m_is_canInto)
	//{
	//	WriteAttackPacker(m_account,"",CMSG_FORCED_INTO,ACCACK_PACKET_TYPE_DATA,"ûȨ��");
	//	return;
	//}
	//m_is_canInto = false;
	uint32 sessionid = LogindContext::FindSessionID(m_account);

	if(sessionid)
	{
		LogindContext *session = dynamic_cast<LogindContext*>(CommonContext::FindContext(sessionid));
		tea_pdebug("forced_into session,%s",m_account.c_str());
		//֪ͨ��ɫ�Ѿ��ڱ𴦵�¼
		Call_operation_failed(session->m_delegate_sendpkt,OPRATE_TYPE_LOGIN,OPRATE_RESULT_OTHER_LOGINED,"");
		session->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE52,"",true);
	}
	m_account = "";
}

/*��ȡ��ɫ�б�*/
void LogindContext::Handle_Get_Chars_List(packet &)
{
	//Get_Chars_List();
}

/*�������*/
bool  LogindContext::Check_Name(string& name, string& realName, string& prefix)
{
	////�ڴ�����ɫ���û����м���ƽ̨ID,������ID����
	string charName = string(name);
	//û������֮ǰ��У��
	uint16 check_reslut = __CheckName1(charName);
	if(check_reslut != OPRATE_RESULT_SUCCESS) {
		Call_operation_failed(m_delegate_sendpkt, OPRATE_TYPE_LOGIN, check_reslut, "");
		return false;
	}
	////���չ���ƴ���û���
	// prefix = accountInfo->pid + "," + accountInfo->sid + ",";
	charName = prefix;
	int additionSize = prefix.size();
	charName += string(name);
	//���������Ժ��У��
	check_reslut = __CheckName2(charName, additionSize);
	if(check_reslut == OPRATE_RESULT_DB_RESULT_ERROR) {
		//���ݿ��쳣�޷�����
		return false;
	}
	if(check_reslut != OPRATE_RESULT_SUCCESS) {
		Call_operation_failed(m_delegate_sendpkt, OPRATE_TYPE_LOGIN, check_reslut, "");
		return false;
	}
	realName = charName;

	return true;
}

// ��������
void LogindContext::Char_Name_Update(string &name) {
	logind_player *player = GetPlayer();
	player->SetName(name);
	g_DAL.InsertGuidByName(player->guid(), name);
}			

/*��ɫ����*/
void LogindContext::Handle_Char_Create(packet &pkt)
{
	//������Ϸ�����ܴ�����ɫ
	if(!LogindApp::g_app->IsGameServer())
	{
		return;
	}
	
    char_create_info *info;

    if(unpack_char_create(&pkt, &info))
	{
		WriteAttackPacker(m_account,"",CMSG_CHAR_CREATE,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}

	// �������ֻ��1-6
	if (info->gender < 1 || info->gender > 6) {
		Call_operation_failed(m_delegate_sendpkt, OPRATE_TYPE_LOGIN, OPRATE_RESULT_GENDER_ILLEGAL, "");
		return;
	}

	const uint32 MAX_CHAR_COUNT = 1;

	//������Ӫһ����0��
	info->faction = 0;

	//�˺���Ϣ
	account_table *accountInfo = g_Cache.GetAccount(m_account);
	ASSERT(accountInfo);
	////�ڴ�����ɫ���û����м���ƽ̨ID,������ID����
	string charName = info->name;
	string realName;
	string prefix = string(accountInfo->pid) + "," + string(accountInfo->sid) + ",";
	if (!this->Check_Name(charName, realName, prefix)) {
		return;
	}
	//�˺����
	int login_time = 0;			
	if(!accountInfo->is_FCM)
		login_time = -1;
	else
		login_time = 0;

    //�����µ�GUID
	uint32 lguid = g_GuidMgr.NewIndex(ObjectTypePlayer);
    string guid = g_GuidMgr.MAKE_NEW_GUID(ObjectTypePlayer,lguid,m_from_server_name.c_str());

    //��ʼ���½�ɫ����
    logind_player *new_player = new logind_player;	
	new_player->SetGuid(guid);
	new_player->SetOwner(guid);
	new_player->SetAccount(m_account.c_str());
	new_player->InitNewPlayer(realName, info->faction, info->gender, info->head_id, info->hair_id,info->race,login_time == 0);
	new_player->SetCreateLoginIp(m_remote_ip);
	new_player->SetPlatData(accountInfo->platdata);
	new_player->SetFactionId("");
	new_player->SetUInt32(PLAYER_INT_FIELD_LV_UP_TIMESTAMP, (uint32)time(NULL));
	
	/**
	new_player->SetStr(PLAYER_STRING_FIELD_INVITE_FACTION_GUID, info->inviteGuid);
	string invited = string(info->inviteGuid);
	// ��Ů�Խ�ɫ�Ҳ��������
	if ((info->gender & 1) == 0 && invited.empty()) {
		string faction_name = string(info->faction_name);
		if (!faction_name.empty()) {
			new_player->SetStr(PLAYER_STRING_FIELD_CREATE_FACTION_NAME, faction_name);
			new_player->SetUInt32(PLAYER_INT_FIELD_CREATE_ICON, 1);
		}
	}
	*/
	//��һ����־
	//g_DAL.InsertGuidByName(guid,charName);	
	WriteCreateRole(m_account, new_player->GetGuid(), new_player->GetName().c_str(), m_remote_ip, new_player->GetGender());
	//��Ѷ��־
	if(LogindApp::g_app->GetPlatformID() == PLATFORM_QQ)
		WriteTXUserLog(m_account,new_player->GetGuid(), new_player->GetName().c_str(),1,GetPlatInfo(accountInfo->platdata,"pf"),(uint32)time(NULL));
	//�����Ż�棬��Ȼ��Զ����
	new_player->m_db_hashcode = new_player->GetHashCode();

	//�����½�ɫ	
	string data,data_str;
	new_player->ToString(data,data_str);
	g_DAL.AddChars(new_player->GetGuid(), m_account, realName, m_remote_ip, data, data_str);
	g_Cache.AddAccountToChar(m_account, new_player->GetGuid());
	g_Cache.SaveAccountCharInfo(m_account, new_player->GetGuid());
	g_DAL.InsertGuidByName(guid, realName);
	//g_LOG.AddHtBaiscInfo(new_player->GetGuid(), m_account, info->name, m_remote_ip);

	//put�����ķ������ص�
	m_temp_vec.push_back(new_player);

	m_lguid = guid;
	SetStatus(STATUS_TRANSFER2);
	LogindContext::SessionQues.push_back(fd_);
	string serverId = string(accountInfo->pid) + "_" + string(accountInfo->sid);
	Call_after_create_role(m_delegate_sendpkt, serverId.c_str(), guid.c_str(), realName.c_str());
}

void LogindContext::Handle_Char_Update_Info(packet &pkt)
{
	char_create_info *info;

	if(unpack_char_create(&pkt, &info))
	{
		WriteAttackPacker(m_account,"",CMSG_CHAR_UPDATE_INFO,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	logind_player *player = GetPlayer();
	//�Ƿ���������
	if(player->GetName() != "")
		return;

	//�����׳�л��߿��У���ֻ��������
	if ((info->race == RACE_STRONG || info->race == RACE_HANDSOME)&&info->gender != CHAR_GENDER_MALE)
	{
		Call_operation_failed(m_delegate_sendpkt, OPRATE_TYPE_LOGIN, OPRATE_RESULT_NAME_ILLEGAL, "");
		return;
	}
	//��������������Ů����ֻ����Ů��
	if ((info->race == RACE_LAURIE || info->race == RACE_BEAUTY)&&info->gender != CHAR_GENDER_FEMALE)
	{
		Call_operation_failed(m_delegate_sendpkt, OPRATE_TYPE_LOGIN, OPRATE_RESULT_NAME_ILLEGAL, "");
		return;
	}
	//�˺���Ϣ
	account_table *accountInfo = g_Cache.GetAccount(m_account);
	if(!accountInfo)
	{
		Close(PLAYER_CLOSE_OPERTE_LOGDIN_2047, "");
		return;
	}
	//�ڴ�����ɫ���û����м���ƽ̨ID,������ID����
	string charName = info->name;
	string realName;
	string prefix = string(accountInfo->pid) + "," + string(accountInfo->sid) + ",";
	if (!this->Check_Name(charName, realName, prefix)) {
		return;
	}
	
	player->SetGender(info->gender);
	player->SetRace(info->race);
	player->SetHair(info->hair_id);
	player->SetHead(info->head_id);

	this->Char_Name_Update(realName);	
	Call_operation_failed(m_delegate_sendpkt,OPRATE_TYPE_LOGIN,OPRATE_RESULT_SUCCESS,"");
}

/*��ɫɾ��*/
void  LogindContext::Handle_Delete_Char(packet &pkt)
{
	//12J��û���������
}

/*�����ʻ�����*/
void LogindContext::Handle_Regularise_Account(packet &pkt)
{
	//12J��û���������
}

//���ڲ�Э�鵽������,����������·���Ӧ�ĵ�ͼ���ݵ�
bool LogindContext::SendToScenedAddMapWatcher()
{
	if (m_general_id.empty())
		return false;

	int32 index = MapMgr->FindInstance(m_general_id);
	if (index < 0)
		return false;		//û���ҵ�
	uint32 scened_conn = MapMgr->GetScenedConn(index);
	if (!scened_conn)
		return false;	

	WorldPacket spkt(INTERNAL_OPT_ADD_MAP_WATHER);
	spkt << GetFD() << m_watcher_guid << m_general_id;
	LogindApp::g_app->SendToScened(spkt, scened_conn);
	return true;
}

