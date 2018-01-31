#include "logind_gm_table.h"
#include <shared/log_handler.h>
#include "logind_script.h"
#include <object/OprateResult.h>
#include "logind_app.h"
#include "logind_context.h"


LogindGMTable::LogindGMTable()
{

};
LogindGMTable::~LogindGMTable()
{

};

//���͵���־�����½���״̬
void LogindGMTable::Send2PolicedUpdateGagStauts(const string& guid, uint32 end_time)
{
	WorldPacket pkt(INTERNAL_OPT_UPDATE_GAG_STATUS);
	pkt<<guid<<end_time;
	LogindApp::g_app->SendToPoliced(pkt);
}

//���͵���־�����·��״̬
void LogindGMTable::Send2PolicedUpdateLockStauts(const string& account, uint32 end_time)
{
	WorldPacket pkt(INTERNAL_OPT_UPDATE_LOCK_STATUS);
	pkt<<account<<end_time;
	LogindApp::g_app->SendToPoliced(pkt);
}

//���÷����Ϣ
void LogindGMTable::SetLockInfo(string account,uint32 end_time)
{
	m_lockInfo[account] = end_time;
}

//��ȡ�����Ϣ
uint32 LogindGMTable::GetLockInfo(string account)
{
	if(m_lockInfo.find(account) == m_lockInfo.end())
		return 0;
	return m_lockInfo[account];
}

LogindContext *LogindGMTable::Ready_kicking_player(const char* account, const char *content)
{
	uint32 sessionID = LogindContext::FindSessionID(account);
	LogindContext *session = dynamic_cast<LogindContext*>(CommonContext::FindContext(sessionID));
	if(session != NULL)
	{
		session->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE50,content ? content : "");
	}

	return session;
}

//T��
void LogindGMTable::KickingPlayer(const string& account, uint8 kicking_type)
{
	string str;
	DoGetCharacters(kicking_type, str);
	if(account == "0")
	{
		tea_pinfo("on_logd_kicking: Log clothing requires all players to kick off the assembly line");
		ObjMgr.ForEachPlayer([&](logind_player *player){
			if(player->GetSession())
			{
				Ready_kicking_player(player->GetSession()->GetAccount().c_str(), str.c_str());
			}
		});	

	}
	else
	{
		LogindContext *session = Ready_kicking_player(account.c_str(), str.c_str());
	}
}

//���
uint32 LogindGMTable::LockAccount(const string& account, uint32 end_time)
{
	uint32 now = (uint32)time(NULL);
	uint32 status = LOCKING_STATUS_START;
	SetLockInfo(account, end_time);		//���������ȸ��·������
	if (now > end_time)
	{//���Ѿ����˷��ʱ��
		status = LOCKING_STATUS_END;
		//֪ͨ��־�����·��״̬
		Send2PolicedUpdateLockStauts(account, 0);
	}
	else
	{
		//֪ͨ��־�����·��״̬
		Send2PolicedUpdateLockStauts(account, end_time);
		KickingPlayer(account, KICKING_TYPE_GM_LOCK_ACCOUNT);
		status = LOCKING_STATUS_RUNNING;
	}

	return status;
}


//ÿʮ���ӷ���һ��������������־��
void LogindGMTable::SendOnilne(TimerHolder& th)
{
	uint32 account_count = 0;
	uint32 player_count = 0;
	for (SessionMap::iterator it = LogindContext::SessionMaps.begin(); it != LogindContext::SessionMaps.end(); ++it)
	{
		account_count ++;
		if(LogindContext::FindContext(it->second))
			player_count++;
	}
	//WriteOnline(account_count, player_count);
	globalValue->SetUInt32(GLOBALVALUE_INT_FIELD_ONLINE_PLAYER_NUM,player_count);
	th._next_time += 600;
}
