#ifndef _LOGD_CONTEXT_H_
#define _LOGD_CONTEXT_H_

#include "policed_app.h"
#include <object/PlayerBase.h>

typedef struct account_info_t account_info;

class PolicedContext:public SvrContext,public PlayerBase
{
public:
	PolicedContext(ContextManager *mgr);
	virtual ~PolicedContext(){};

	//����·��,��ʼ��
	void OpcodeHandlerInitor();	

	void Login(uint32 fd);
	void Logout();
	void SetServerId();

	const string &GetServerId(){return m_sid;}
	const string &GetPlatformId(){return m_pid;}
public:
	account_info *a_info;
	string ip;			//���IP
	uint32 uip;				//���IP����������
public:
	void Handle_write_client_log(packet& pkt);
	void Handle_Player_Gag(packet& pkt);				//����
private:
	string m_sid;		//������id
	string m_pid;		//ƽ̨id
};

#endif
