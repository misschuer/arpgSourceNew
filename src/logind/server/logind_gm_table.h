#ifndef _LOGIND_GM_TABLE_
#define _LOGIND_GM_TABLE_

#include "logind_app.h"
#include <object/std.h>
#include <object/PlayerBase.h>
#include <object/SharedDef.h>

class LogindContext;

class LogindGMTable
{
public:
	LogindGMTable();
	~LogindGMTable();

public:
	void Send2PolicedUpdateGagStauts(const string& guid, uint32 end_time);	//���͵���־�����½���״̬
	void Send2PolicedUpdateLockStauts(const string& account, uint32 end_time);	//���͵���־�����·��״̬
	void KickingPlayer(const string& account, uint8 kicking_type);		//T��
	uint32 LockAccount(const string& account, uint32 end_time);		//���
	void SendOnilne(TimerHolder& th);					//������־
	uint32 GetLockInfo(string account);					//��ȡ�����Ϣ
private:
	void SetLockInfo(string account,uint32 end_time);	//���÷����Ϣ
	LogindContext *Ready_kicking_player(const char* account, const char *content);

private:
	map<string,uint32>	m_lockInfo;				//�����Ϣ����
};
#endif