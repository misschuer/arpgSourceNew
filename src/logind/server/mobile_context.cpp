#include "mobile_context.h"
#include <shared/log_handler.h>
#include <object/OprateResult.h>
#include "logind_player.h"
#include "logind_context.h"
#include "logind_cache.h"
#include "logind_context_login_mgr.h"

//////////////////////////////////////////////////////////////////////////
MobileSessionMap MobileContext::MobileSessionMaps;

//���������ֻ��Ự
void MobileContext::ForEachMobileContext(std::function<void(std::string, std::string)> func)
{
	for (auto it: MobileContext::MobileSessionMaps)
	{
		MobileContext* mobile_session = dynamic_cast<MobileContext*>(CommonContext::FindContext(it.second));
		if (mobile_session)
		{
			func(mobile_session->GetGuid(), mobile_session->m_remote_ip);
		}
	}	
}

//���������ֻ��Ự
void MobileContext::ForEach(std::function<void(MobileContext*)> func)
{
	for (auto it: MobileContext::MobileSessionMaps)
	{
		MobileContext* mobile_session = FindContext(it.second);
		if (mobile_session) 
			func(mobile_session);		
	}	
}

//ͨ��guid�������λỰ
MobileContext* MobileContext::FindContextByGuid(string guid)
{
	for (auto it: MobileContext::MobileSessionMaps)
	{
		MobileContext* mobile_session = dynamic_cast<MobileContext*>(CommonContext::FindContext(it.second));
		if (mobile_session && mobile_session->GetGuid() == guid)
		{
			return mobile_session;
		}
	}	
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//for MobileContext
MobileContext::MobileContext(uint32 fd,ContextManager *mgr):CommonContext(fd,mgr,CONTEXT_TYPE_PHONE)
{
	OpcodeHandlerInitor();
}

MobileContext::~MobileContext()
{
}

//����·��,��ʼ��
void MobileContext::OpcodeHandlerInitor()
{

}

uint32 MobileContext::FindSessionID(const string &account)
{
	auto iter = MobileContext::MobileSessionMaps.find(account);
	if (iter == MobileContext::MobileSessionMaps.end())
	{
		return 0;
	}
	return iter->second;
}

void MobileContext::Get_Session(std::map<string,string>& querys)
{
	//����Ѿ���¼����
	if(!m_account.empty())
	{
		tea_perror("MobileContext::Get_Session account[%s] re get session", m_account.c_str());
		Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE23,"");
		return;
	}

	//����URL
	string pid = querys["pid"],sid = querys["sid"],uid = querys["uid"];
	//�ʻ����ƣ������ж�һ���Ƿ񳬳�
	m_account = pid+"_"+sid+"_"+uid;	
	if(m_account.size() >= sizeof((account_table*)NULL)->name)
	{
		tea_perror("MobileContext::Get_Session m_account_string:%s too long!",m_account.c_str());
		Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE24,"");
		return;
	}
	m_from_server_name = pid+"_"+sid;
	//��֤�Ƿ���Ե�¼����
	if(!Get_Server_List(m_from_server_name))
	{
		tea_perror("MobileContext::Get_Session m_from_server_name:%s is't in this server",m_from_server_name.c_str());
		Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE25,"");
		return;
	}

	tea_pdebug("MobileContext::Get_Session account %s getsession!", m_account.c_str());
	account_table *info = g_DAL.UpsertAccount(m_account,pid,sid,uid,false,m_remote_ip,"");
	ASSERT(info);
	
	//״̬�����֤ͨ��	
	SetStatus(STATUS_AUTHED);
	
	//������Э��ע��һ��
	LogindApp::g_app->RegSessionOpts(fd_);

	uint32 old_fd = MobileContext::FindSessionID(m_account);
	//��ǰ�Ѿ�����,��ֱ�ӹص��õ�
	if (old_fd)
	{	
		MobileContext* context = dynamic_cast<MobileContext*>(CommonContext::FindContext(old_fd));
		if (context)
		{
			context->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE27,"",true);
			Call_operation_failed(m_delegate_sendpkt,OPRATE_TYPE_LOGIN,OPRATE_RESULT_LOGINED_IN, m_account.c_str());
			Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE27,"");
			return;
		}
	}

	int fd = fd_;
	g_DAL.GetCharsList(m_account,[fd,this](bool sucess,vector<char_create_info>& char_list){
		auto *session = MobileContext::FindContext(fd);
		if(!session) return;		//��ֹ�ص�Ұָ��
		if(!char_list.empty())
		{
			session->m_lguid = char_list[0].guid;

			MobileSessionMaps[m_account] = GetFD();					//���ڲ�������Session			

			//ͨ���˰�����Э��ע������ķ�������ΪĬ������	
			LogindApp::g_app->RegSessionOpts(GetFD(),CMSG_GET_SESSION,ServerList.GetCentdFd());
			LogindApp::g_app->m_login_queue->PushAction(session->GetGuid(), session->GetFD(), CONTEXT_LOGIN_ACTION_LOGIN);
		}
		else
		{
			tea_perror("MobileContext::Get_Session: %s Get_Chars_List fail", m_account.c_str());
			Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE28,"");
			return;
		}
	});
}

void MobileContext::LoginOK()
{
	//������Ҷ���
	m_player = ObjMgr.FindPlayer(m_lguid);
	ASSERT(m_player);
	m_player->SetMobileSession(this);

	//��Ӷ�������ж���ļ���
	ObjMgr.CallAddTagWatch(GetFD(), m_player->GetGuid());

	//����ҳ�������������
	if (LogindContext::FindSessionID(m_account) != 0)
	{
		if (!m_player->GetFlags(PLAYER_APPD_INT_FIELD_FLAGS_YEYOU_ONLINE))
			m_player->SetFlags(PLAYER_APPD_INT_FIELD_FLAGS_YEYOU_ONLINE);
		if (!m_player->GetFlags(PLAYER_APPD_INT_FIELD_FLAGS_PHONE_ONLINE))
			m_player->SetFlags(PLAYER_APPD_INT_FIELD_FLAGS_PHONE_ONLINE);
	}
	else
	{
		if (m_player->GetFlags(PLAYER_APPD_INT_FIELD_FLAGS_YEYOU_ONLINE))
			m_player->UnSetFlags(PLAYER_APPD_INT_FIELD_FLAGS_YEYOU_ONLINE);
		if (!m_player->GetFlags(PLAYER_APPD_INT_FIELD_FLAGS_PHONE_ONLINE))
			m_player->SetFlags(PLAYER_APPD_INT_FIELD_FLAGS_PHONE_ONLINE);
	}
	SetStatus(STATUS_LOGGEDIN);
	//֪ͨ����������Ϊ����ҽ����Ự��Ϣ	
	Call_Create_Connection();
}

void MobileContext::OnClosed()
{
	tea_pwarn("MobileContext::OnClosed: fd %d account %s playerguid %s outline!", fd_, m_account.c_str(), m_lguid.c_str());
	LogindApp::g_app->RomoveContext(fd_);   
	if (fd_ && fd_ == MobileContext::FindSessionID(m_account))
	{
		//���˺�ӳ���ɾ��
		MobileContext::MobileSessionMaps.erase(m_account);		
	}
	
	//˵�����ǵǵ��������,���εĻ�m_lguid������Ϊ��
	if (m_lguid.empty())
		return;
	
}

void MobileContext::CollapseReset(logind_player *player)
{
	m_player = player;
	if (m_lguid.empty())
		m_lguid = player->GetGuid();	
	player->SetMobileSession(this);
	m_account = player->GetAccount();
	MobileSessionMaps[m_account] = fd_;
	SetStatus(STATUS_LOGGEDIN);
	LogindApp::g_app->RegSessionOpts(fd_);
}

void MobileContext::Call_Create_Connection()
{
	if (!m_player)
	{
		return;
	}

	WorldPacket pkt(INTERNAL_OPT_PLAYER_LOGIN);
	pkt << fd_ << m_player->GetGuid() << uint8(CONTEXT_TYPE_PHONE);

	//֪ͨ���ķ���������
	LogindApp::g_app->SendToCentd(pkt);
}