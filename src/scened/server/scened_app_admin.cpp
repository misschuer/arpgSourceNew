#include <comm/common_stl.h>
#include "scened_app.h"
#include "scened_context.h"
#include "QuestGetter.h"
#include "Player.h"
#include "Map.h"
#include "scened_scripts.h"

inline Player *GetPlayerObject(const string &guid)
{
	auto *ptr = ObjMgr.FindPlayer(guid);
	return ptr;
}

int ScenedApp::on_command_reload_scripts(tcp_connection *conn, server_packet *,uint32 , uint32 connectid, Tokens& tokens)
{
	//��������ű�
	if(scripts_reload() == 0)
		COMMAND_SEND_SUCCEED;
	else
		SendCommandResult(conn, connectid, "load script error");
	return 0;
}

int ScenedApp::on_command_reload_template(tcp_connection *conn, server_packet *,uint32 , uint32 connectid, Tokens& tokens)
{
	if(g_app->GetConfig().load_pingbi)
		g_app->LoadFuckPingbi(g_app->GetConfig().storage_path);
	if (!LoadTemplate())
	{
		SendCommandResult(conn, connectid, "load temlate error");
		return 1;
	}
	COMMAND_SEND_SUCCEED;
	return 0;
}

int ScenedApp::on_command_hello_world(tcp_connection *conn, server_packet *,uint32 , uint32 connectid, Tokens& tokens)
{
	SendCommandResult(conn, connectid, "scened pid:%u", getpid());
	return 0;
}

int ScenedApp::on_command_reset_daily(tcp_connection *, server_packet *,uint32 , uint32, Tokens& tokens)
{
	//TODO,��֪����ô��
	return 0;
}

int ScenedApp::on_command_complete_quest(tcp_connection *conn, server_packet *,uint32 guid, uint32 connectid, Tokens& tokens)
{
	COMMAND_CHECK_LEN(3);
	string player_id = tokens[1];
	COMMAND_FIND_PLAYER(Player, player, player_id);

	COMMAND_ATOI(uint32, 2, quest_id);
	player->m_questMgr->CompleteQuest(quest_id);
	COMMAND_SEND_SUCCEED;
	return 0;
}

int ScenedApp::on_command_add_quest(tcp_connection *conn, server_packet *,uint32 guid, uint32 connectid, Tokens& tokens)
{
	COMMAND_CHECK_LEN(3);
	string player_id = tokens[1];
	COMMAND_FIND_PLAYER(Player, player, player_id);
	COMMAND_ATOI(uint32, 2, quest_id);
	if (player->GetQuestMgr()->FindQuestSlot(quest_id) == MAX_QUEST_LOG_SIZE)
	{
		player->GetQuestMgr()->AddQuest(quest_template_db[quest_id]);
	}
	COMMAND_SEND_SUCCEED;
	return 0;
}

int ScenedApp::on_command_del_quest_item(tcp_connection *conn, server_packet *,uint32 guid, uint32 connectid, Tokens& tokens)
{
	COMMAND_CHECK_LEN(3);
	string player_id = tokens[1];
	COMMAND_FIND_PLAYER(Player, player, player_id);
	COMMAND_ATOI(uint32, 2, pos);
	if(pos >= QUEST_ITEMS_COUNTS)
	{
		SendCommandResult(conn, connectid, "%u����һ����Ч������Ʒλ��", pos);
		return 0;
	}
	//player->GetSession()->SetUInt32(PLAYER_SCENED_INT_FIELD_QUEST_ITEMS + pos, 0);
	COMMAND_SEND_SUCCEED;
	return 0;
}

int ScenedApp::on_command_teleport(tcp_connection *conn, server_packet *,uint32 guid, uint32 connectid, Tokens& tokens)
{
	COMMAND_CHECK_LEN(5);
	string player_id = tokens[1];
	COMMAND_FIND_PLAYER(Player, player, player_id);
	COMMAND_ATOI(uint32, 2, map_id);
	//��ͼ������Ϸ���
	const MapTemplate *temp = MapTemplate::GetMapTempalte(map_id);
	if(!temp)
	{
		SendCommandResult(conn, connectid, "IDΪ %s �ĵ�ͼ������", tokens[1].c_str());
		return 0;
	}
	COMMAND_ATOI(uint16, 3, x);
	COMMAND_ATOI(uint16, 4, y);
	if(x >= temp->GetMapBaseInfo().width || y >= temp->GetMapBaseInfo().height)
	{
		SendCommandResult(conn, connectid, "��ͼID %u ���� %u %u ������Ч���귶Χ", map_id, x, y);
		return 0;
	}
	player->GetSession()->Teleport(x, y, map_id,"");
	COMMAND_SEND_SUCCEED;
	return 0;
}

int ScenedApp::on_command_reset_spell_cd(tcp_connection *conn, server_packet *,uint32 guid, uint32 connectid, Tokens& tokens)
{
	COMMAND_SEND_SUCCEED;
	return 0;
}

//
int ScenedApp::on_command_ls_session(tcp_connection *conn, server_packet *,uint32 guid, uint32 connectid, Tokens& tokens)
{
	COMMAND_CHECK_LEN(1);
	COMMAND_ATOI(uint32, 1, process_id);
	//�жϽ���ID
	if(getpid()!=process_id)
	{
		return 0;
	}
	
	return 0;
}
