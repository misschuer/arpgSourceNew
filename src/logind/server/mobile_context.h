#ifndef _MOBILE_CONTEXT_H_
#define _MOBILE_CONTEXT_H_

#include <comm/common_stl.h>
#include <net/netstd.h>
#include <protocol/external.h>
#include "common_context.h"
#include "logind_app.h"
#include "logind_mongodb.h"

typedef map<string,uint32> MobileSessionMap;

class MobileContext : public CommonContext
{
public:
	//�˺�-fd
	static MobileSessionMap MobileSessionMaps;
	//�ص���һ������Ϊguid,�ڶ�����ip
	static void ForEachMobileContext(std::function<void(std::string, std::string)> func);	//���������ֻ��Ự	
	static void ForEach(std::function<void(MobileContext*)> func);				//���������ֻ��Ự	

	static MobileContext* FindContextByGuid(string guid);		//ͨ��guid�������λỰ	
	static inline MobileContext* FindContext(uint32 fd)
	{
		return static_cast<MobileContext*>(LogindApp::g_app->FindContext(fd));
	}

public:
	MobileContext(uint32 fd,ContextManager *mgr);
	virtual ~MobileContext();

	//����·��,��ʼ��
	void OpcodeHandlerInitor();

	void Update(uint32)
	{

	};
	const string &GetGuid()const{return m_lguid;}
	const string &GetAccount()const{return m_account;}
	
	void Get_Session(std::map<string,string>& querys);
	static uint32 FindSessionID(const string &account);
	
	void OnClosed();
	//��¼�������Ժ����³�ʼ��
	void CollapseReset(logind_player *player);
	void Call_Create_Connection();
	void LoginOK();
};

#endif // !_MOBILE_CONTEXT_H_


