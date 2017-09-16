#include "appd_app.h"
#include "AppdLoginManager.h"
#include "appd_context.h"
#include <object/OprateResult.h>

class AppdLoginActionLogin : public LoginActionBase
{
public:
	AppdLoginActionLogin(uint32 fd, const string guid) : LoginActionBase(fd, guid), m_add_watch(false)
	{

	}
	~AppdLoginActionLogin(){}
public:
	bool Update(uint32 diff)
	{
		//��û���ͼ�������ô�����ɡ�����
		if(!m_add_watch)
		{
			auto player = ObjMgr.FindPlayer(m_guid);
			if(player)
			{
				//�п�������˳���ʱ��Ӧ�÷��������������δ��ȷ�˳�
				AppdApp::g_app->m_login_mgr->InsertCloseAction(m_guid);
				return true;
			}
			
			ObjMgr.CallAddTagWatch(m_guid);
			m_add_watch = true;
			return true;
		}

		//�ȴ�����ĵ���
		auto player = ObjMgr.FindPlayer(m_guid);
		if(!player)
			return true;

		player->Login(m_fd);
		return false;
	}
	EContextLoginAction GetType()
	{
		return CONTEXT_LOGIN_ACTION_LOGIN;
	}

private:
	bool m_add_watch;	//�Ƿ��Ѿ������������
};

class AppdLoginActionClose : public LoginActionBase
{
public:
	AppdLoginActionClose(uint32 fd, const string guid) : LoginActionBase(fd, guid), m_del_watch(false)
	{

	}
	~AppdLoginActionClose(){}
public:
	bool Update(uint32 diff)
	{
		if(!m_del_watch)
		{
			AppdContext *player = ObjMgr.FindPlayer(m_guid);
			if(!player)
			{
				tea_pwarn("AppdLoginActionClose:Update player not found, %s %u", m_guid.c_str(), m_fd);
				return false;
			}
			player->Logout();
			m_del_watch = true;
			return true;
		}

		//һֱ���Ƴ���ϲ��������˳����
		return ObjMgr.Get(m_guid) != nullptr;
	}
	EContextLoginAction GetType()
	{
		return CONTEXT_LOGIN_ACTION_CLOSE;
	}
private:
	bool m_del_watch;
};

void AppdLoginMgr::PushAction(const string guid, uint32 fd, EContextLoginAction type)
{
	tea_pdebug("AppdLoginMgr::PushAction %s %u %u", guid.c_str(), fd, type);
	LoginActionBase *action = nullptr;
	switch (type)
	{
	case CONTEXT_LOGIN_ACTION_LOGIN:
		{
			action = new AppdLoginActionLogin(fd, guid);
		}
		break;
	case CONTEXT_LOGIN_ACTION_CLOSE:
		{
			action = new AppdLoginActionClose(fd, guid);
		}
		break;
	default:
		break;
	}
	ASSERT(action);
	ASSERT(!guid.empty());
	m_action[guid].push(action);
}

void AppdLoginMgr::InsertCloseAction(const string guid)
{
	auto action = new AppdLoginActionClose(0, guid);	
	vector<LoginActionBase*> vec;
	while(!m_action[guid].empty())
	{
		vec.push_back(m_action[guid].front());
		m_action[guid].pop();
	}
	m_action[guid].push(action);
	for (auto it:vec)
	{
		m_action[guid].push(action);
	}
}
