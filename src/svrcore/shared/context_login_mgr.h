#ifndef _CONTEXT_LOGIN_MGR_H_
#define _CONTEXT_LOGIN_MGR_H_

#include <comm/common_stl.h>

class SvrContext;
class ContextLoginMgr;

enum EContextLoginAction
{
	CONTEXT_LOGIN_ACTION_NONE			= 0,		//û�õģ�����������
	CONTEXT_LOGIN_ACTION_LOGIN			= 1,		//�����ĵ�¼���ø������
	CONTEXT_LOGIN_ACTION_CLOSE			= 2,		//�ǳ�����
};

//���ǻ���
class LoginActionBase
{
public:
	LoginActionBase(uint32 fd, const string &guid):m_fd(fd),m_guid(guid)
	{

	}
	~LoginActionBase(){}
public:
	virtual bool Update(uint32 diff) = 0;
	virtual EContextLoginAction GetType() = 0;
public:
	const uint32 m_fd;
	const string m_guid;
};

//�Ự��¼����
class ContextLoginMgr
{
	typedef std::queue<LoginActionBase*> ActionQueue;
	typedef std::map<string, ActionQueue> AccountActionMap;
public:
	ContextLoginMgr();
	~ContextLoginMgr();
public:
	void Update(uint32 diff);
	virtual void PushAction(const string guid, uint32 fd, EContextLoginAction type) = 0;
protected:
	AccountActionMap m_action;
};

#endif

