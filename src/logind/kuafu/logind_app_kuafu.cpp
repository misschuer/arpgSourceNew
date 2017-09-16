#include "logind_app.h"
#include "logind_context.h"

#include <shared/log_handler.h>
#include <object/OprateResult.h>
#include <object/GlobalValueManager.h>

#include "map_manager.h"
#include "logind_mongodb.h"
#include "logind_object_manager.h"
#include "logind_script.h"
#include "logind_cache.h"
#include <comm/b64.h>
#include <comm/crypt.h>
#include <core_obj/SyncEventRecorder.h>
#include "http_handler.h"

//�����ս����
void LogindApp::GoToPkServer(const string &player_guid)
{
	//logind_player *player = ObjMgr.FindPlayer(player_guid);
	//if (!player)
	//{
	//	tea_pdebug("LogindApp::GoToPkServer player %s not find!", player_guid.c_str());
	//	return;
	//}
	//if (!player->GetSession())
	//{
	//	tea_pdebug("LogindApp::GoToPkServer player %s session is null !!!", player_guid.c_str());
	//	return;
	//}
	//if (m_matchInfo.find(player_guid) == m_matchInfo.end())
	//{//û�ҵ�ƥ����Ϣ
	//	tea_pdebug("LogindApp::GoToPkServer player %s not find match info !", player_guid.c_str());
	//	return;
	//}

	//macthing_info info = m_matchInfo[player_guid];
	//Tokens token;
	//StrSplit(token, info.battle_server_info, ';'); //ս����server_name;ս����ip;ս����port;ս����login_key;��Ϸ��ip;��Ϸ��port
	//string battle_server_name = token[0];
	////ȡ��host��port
	//string host, port;
	//m_http->GetHostPortByServerName(battle_server_name, host, port);
	//if (host.empty() || port.empty())
	//{
	//	tea_perror("LogindApp::GoToPkServer player %s not find server %s host and port!", player_guid.c_str(), battle_server_name.c_str());
	//	return;
	//}

	////����ƥ����Ϣ���ɵ�¼��
	//bool is_fcm = player->GetFCMLoginTime() != (-1);
	//char temp[1024] = {0};
	////��Ϸ��server_name|��Ϸ��ip|��Ϸ��port|�������|����id|������|�����ս����server_name|��������������������ʹ�ã�|��������������������ʹ�ã�|��������
	//sprintf(temp, "&otherdata=%s|%s|%s|%d|%u|%u|%s|%u|%u|%s",GetConfig().server_name.c_str(), token[4].c_str(), token[5].c_str(), info.kuafu_type, info.war_id,info.kuafu_number, battle_server_name.c_str(), info.reserve, info.reserve2, info.reserve_str);	
	//string session_str = LogindApp::g_app->MakeSessionKey(player->GetAccount(),is_fcm, temp, WANNENG_LOGIN_KEY);
	////����ۼ�
	//m_matchInfo.erase(player_guid);
	//player->GetSession()->SetReceiveMatchInfoFlag(false);
	////֪ͨ�ͻ��˶Ͽ���Ϸ������pk��
	//player->GetSession()->Call_World_War_CS_Player_Info(host, uint32(atol(port.c_str())), session_str);
}
