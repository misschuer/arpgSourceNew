#include "common_context.h"
#include "logind_cache.h"
#include "logind_app.h"
#include "logind_player.h"
#include "logind_context.h"
#include "logind_mongodb.h"
#include <object/OprateResult.h>
#include <shared/log_handler.h>

CommonContext* CommonContext::FindContext(uint32 fd)
{
    return dynamic_cast<CommonContext*>(LogindApp::g_app->FindContext(fd));
}

////////////////////////////////////////
//for CommonContext
CommonContext::CommonContext(uint32 fd,ContextManager *mgr,int type/* = CONTEXT_TYPE_YEYOU*/):
	SvrContext(fd, mgr)
	,m_context_type(type),m_player(nullptr)
{
	m_number = 0;
	m_warid = 0;
	m_kuafutype = 0;
	m_remote_port = 0;
	m_kuafu_reserve = 0;
	m_kuafu_reserve2 = 0;
}

CommonContext::~CommonContext()
{
}

bool CommonContext::SetPlayer(logind_player *player)
{
    if(m_lguid.empty())
        m_lguid = player->GetGuid();
	else
		ASSERT(m_lguid == player->guid());

	if(m_account.empty())
	{
		m_account = player->GetAccount();
	}
	else
	{
		if(m_account != player->GetAccount())
		{
			Close(PLAYER_CLOSE_OPERTE_LOGDIN_2048,"");
			return false;
		}
	}

    m_player = player;
	return true;
}

/*��֤��¼�������Ƿ���ȷ*/
bool CommonContext::Get_Server_List(string login_server)
{
	if(LogindApp::g_app->GetServerID() == login_server)
	{
		if(LogindApp::g_app->GetAddTime() != 0)
		{
			tea_pwarn("server is merge %u",LogindApp::g_app->GetKaiFuShiJian());
			return false;
		}
		return true;
	}

	//�ж����Ƿ񿪷���
	if(LogindApp::g_app->GetKaiFuShiJian() > (uint32)time(NULL))
	{
		tea_pwarn("server is not open,open_time %u",LogindApp::g_app->GetKaiFuShiJian());
		return false;
	}
	if(LogindApp::g_app->GetAddTime() != 0)
	{
		tea_pwarn("server is merge",LogindApp::g_app->GetKaiFuShiJian());
		return false;
	}
	//�ж����Ƿ�������б�������
	for (int i = 0;;++i)
	{
		//Ĭ��Ϊ�վͲ�����ѭ����ȥ��
		if(LogindApp::g_app->GetServerID(i).empty())
			break;
		if(LogindApp::g_app->GetServerID(i) == login_server)
			return true;
	}
	return false;
}


void CommonContext::PlayerLoadData()
{
	SetStatus(STATUS_TRANSFER);
	logind_player *player;
	//�ȴ�Ӳ��load��û���ٴ����ݿ�load
	if(ObjMgr.LoadPlayer(m_lguid, &player, m_temp_vec)
		|| g_Cache.LoadPlayer(m_lguid, &player, m_temp_vec))
	{
		ASSERT(player);
		g_Cache.DelLogoutPlayer(m_lguid);
		SetStatus(STATUS_TRANSFER2);
		return;
	}
	else
	{
		safe_delete(player);
		for(auto it:m_temp_vec)
			safe_delete(it);
		m_temp_vec.clear();
	}

	uint32 fd = fd_;
	string guid = m_lguid;
	static map<uint32, vector<GuidObject*>> obj_vec_map;
	ASSERT(obj_vec_map.find(fd_) == obj_vec_map.end());

	g_DAL.LoadPlayer(m_account, m_lguid, obj_vec_map[fd_], [this, fd, guid](bool load_succeed, vector<GuidObject*> &vec){
		auto session = LogindContext::FindContext(fd);
		if(!session)
		{
			for (auto it:vec)
			{
				safe_delete(it);
			}
			vec.clear();
			return;
		}
		if(!load_succeed)
		{
			session->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE59, "");
			return;
		}

		for (auto it:vec)
		{
			session->m_temp_vec.push_back(it);
		}
		SetStatus(STATUS_TRANSFER2);
	});
}

void CommonContext::PutData()
{
	//�������У�����put��
	if(ObjMgr.Get(m_lguid))
	{
		SetStatus(STATUS_PUT_OK);
		return;
	}
	//������Ͳ��ǻ�����ȡ�������
	//�����ķ��ύ��Ҷ���
	uint32 fd = fd_;
	string guid = m_lguid;
	vector<string> temp_vec;
	for (auto it:m_temp_vec)
	{
		temp_vec.push_back(it->guid());
	}
	SetStatus(STATUS_PUT);
	ObjMgr.CallPutsObject(guid, m_temp_vec, [this, fd, guid, temp_vec](bool b){
		if(!b)
		{
			tea_pdebug("player login call puts fail %s, fd %u", guid.c_str(), fd);
			LogindContext *session = LogindContext::FindContext(fd);
			if(session)
				session->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE54,"");
			return;
		}
		//��binlog��ӵ���߹�����Ūһ��
		for (auto it:temp_vec)
		{
			//todo jzy  ��һ�䣬��Ϊ�˺�datad�汾�����ݵ�����
			ObjMgr.CallAddWatch(it, nullptr, false);
			ObjMgr.InsertObjOwner(it);
		}

		LogindContext *session = LogindContext::FindContext(fd);
		if(!session)
		{
			tea_pdebug("player login call puts ok, but logout, %s %u", guid.c_str(), fd);
			return;
		}

		tea_pdebug("LogindContext::Login player login call puts ok, %s %u", guid.c_str(), fd);
		SetStatus(STATUS_PUT_OK);
	});
}
