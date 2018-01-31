#include "scened_app.h"
#include "scened_context.h"
#include "ScenedObjectManager.h"
#include "Player.h"
#include "Creature.h"
#include "Map.h"
#include "BuffManager.h"
#include "MovementGenerator.h"
#include <object/OprateResult.h>
#include <object/SharedDef.h>

#include "scened_scripts.h"
#include "object/QuestDef.h"
#include "QuestGetter.h"
#include <object/GameObject.h>

#include "object/LootManager.h"
#include <server/internal_callback.h>
#include <shared/log_handler.h>
#include <core_obj/SyncEventRecorder.h>
#include "Grid.h"

//////////////////////////////////////////////////////////////////////////
// for ScenedConfig


bool ScenedConfig::_Load(config_loader *loader)
{
	if(!GameConfig::_Load(loader))
		return false;

	nomal_attack_distance = config_loader_get_float(loader,"nomal_attack_distance",4.0f);

	//�Ƿ���������ɵ�
	char *_value = config_loader_get_char(loader, "load_creature_path", "N");
	load_creature_path = (_value[0] == 'y' || _value[0] == 'Y');
	free(_value);

	_value = config_loader_get_char(loader, "test_server_live_uid","testserverlive");
	test_server_live_uid = _value;
	free(_value);

	//��ͼ����Ӳ�̱���·��
	_value = config_loader_get_char(loader, "map_data_hdd_path","");
	map_data_hdd_path = _value;
	free(_value);
	if(map_data_hdd_path == "")
		map_data_hdd_path = log_folder + "/scenedata/";


	return true;
}

//////////////////////////////////////////////////////////////////////////
// for ScenedApp
ScenedApp::ScenedApp(SvrCoreParams &params, SvrCoreConfig &config): base(params, config),
	m_obj_mgr(NULL)
{
	m_inter_cb = new InternalCallback<packet&>();

	m_netgd_request_map[INTERNAL_OPT_UD_OBJECT] = &on_centd_guid_object_table;
	m_netgd_request_map[INTERNAL_OPT_UD_CONTROL] = &on_centd_guid_object_table;
	m_netgd_request_map[INTERNAL_OPT_UD_CONTROL_RESULT] = &on_centd_guid_object_table;

	m_netgd_request_map[INTERNAL_OPT_JOIN_MAP] = &on_join_map;		//��Ҽ����ͼ
	m_netgd_request_map[INTERNAL_OPT_LEAVE_MAP] = &on_leave_map;	//����뿪��ͼ

	m_netgd_request_map[INTERNAL_OPT_DESTORY_CONN] = &on_netgd_destory_conn;

	m_netgd_request_map[INTERNAL_OPT_CLOSE_SCENED] = &on_close_scened;	//�ر��Լ�
	m_netgd_request_map[INTERNAL_OPT_ADD_MAP_INSTANCE] = &on_create_world_map;
	m_netgd_request_map[INTERNAL_OPT_OPEN_TIME] = &on_centd_open_time;//
	m_netgd_request_map[INTERNAL_OPT_USER_ITEM] = &on_internal_user_item;
	m_netgd_request_map[INTERNAL_OPT_GM_COMMMANDS] = &on_gm_commands;
	m_netgd_request_map[INTERNAL_OPT_DEL_MAP_INSTANCE] = &on_del_map;		//���ķ�����ɾ����ͼ
	m_netgd_request_map[INTERNAL_OPT_UPDATE_EQUIP_INFO] = &on_internal_update_equip_info;	//Ӧ�÷��������װ����������
	m_netgd_request_map[INTERNAL_OPT_APPD_TELEPORT] = &on_appd_teleport;
	m_netgd_request_map[INTERNAL_OPT_LOGIND_TELEPORT] = &on_logind_teleport;

	m_netgd_request_map[INTERNAL_OPT_COMMMAND] = &on_commands;
	m_netgd_request_map[INTERNAL_OPT_ADD_EXP] = &on_scened_addexp;
	m_netgd_request_map[INTERNAL_OPT_SCENED_CONSUME_MONEY] = &on_scened_consume_money;
	m_netgd_request_map[INTERNAL_OPT_SYNC_GUID_MAX] = &on_logind_sync_maxguid;		//ͬ��guid����������ۼ�ֵ
	m_netgd_request_map[INTERNAL_OPT_LOGIND_MERGE_SERVER] = &on_logind_merge_server;//��½��֪ͨ�Ϸ�
	m_netgd_request_map[INTERNAL_OPT_MAP_ROUTER_PKT] = &on_map_router_pkt;//��ͼ����ͼ����
	m_netgd_request_map[INTERNAL_OPT_ADD_MAP_WATHER] = &on_logind_to_scened_add_map_watcher;		//֪ͨ��������ӵ�ͼ�۲���
	m_netgd_request_map[INTERNAL_OPT_UPDATE_SPELL_INFO]	= &on_update_spell_info;	//֪ͨ���������¼�����Ϣ
	m_netgd_request_map[INTERNAL_OPT_CHANGE_DIVINE_INFO] = &on_update_change_divine_info;	//֪ͨ����������滻
	m_netgd_request_map[INTERNAL_OPT_APPD_TO_SEND_DO_SOMETHING]	= &on_appd_send_scened_do_something;	//֪ͨ��������Щ����
	

	//////////////////////////////////////////////////////////////////////////
	//��̨����
	m_command_hanlders.insert(std::make_pair("hello_world",	&ScenedApp::on_command_hello_world));
	m_command_hanlders.insert(std::make_pair("reload_script",	&ScenedApp::on_command_reload_scripts));
	m_command_hanlders.insert(std::make_pair("reload_template",&ScenedApp::on_command_reload_template));
	m_command_hanlders.insert(std::make_pair("reset_daily",&ScenedApp::on_command_reset_daily));
	m_command_hanlders.insert(std::make_pair("complete_quest",&ScenedApp::on_command_complete_quest));
	m_command_hanlders.insert(std::make_pair("add_quest",&ScenedApp::on_command_add_quest));
	m_command_hanlders.insert(std::make_pair("del_quest_item",&ScenedApp::on_command_del_quest_item));
	m_command_hanlders.insert(std::make_pair("teleport",&ScenedApp::on_command_teleport));
	m_command_hanlders.insert(std::make_pair("reset_spell_cd",&ScenedApp::on_command_reset_spell_cd));
	m_command_hanlders.insert(std::make_pair("ls_session",&ScenedApp::on_command_ls_session));
	m_command_hanlders.insert(std::make_pair("print_object", &ScenedApp::on_print_object));
	m_command_hanlders.insert(std::make_pair("memory_recovery", &ScenedApp::on_command_memory_recovery));
}

ScenedApp::~ScenedApp()
{
	safe_delete(m_inter_cb);
	safe_delete(m_obj_mgr);
}

bool ScenedApp::Open()
{
	fp_send_to_policed = std::bind(&ScenedApp::SendToPoliced,this,std::placeholders::_1);	

	tea_pinfo("\n\n��ʼ�����ͼģ����Ϣ...");
	if(!MapTemplate::Load(GetConfig().map_folder))
		return false;
	if(g_Config.load_creature_path)
	{
		for(MapTemplate::MTVector::iterator it = MapTemplate::mtvec.begin(); it != MapTemplate::mtvec.end(); ++it)
		{
			if((*it) == NULL)
				continue;
			if(!(*it)->LoadObstaclePeriphery())
				return false;
		}
	}

	tea_pinfo("\n\n��ʼ����AI(InitializeMovement)...");
	Tea::InitializeMovement();


	//��ʼ�����������
	m_obj_mgr = new ScenedObjectManager(this);

	//��ȫ����뾶
	MapTemplate::safe_distance = g_Config.safe_distance;

	//���˺��ṹ��һ��id	
	Map::fighting_info_binlog.SetGuid("fighting_info_binlog");

	if(!base::Open())
		return false;

	return true;
}

void ScenedApp::Close()
{
	//�ͷ����е�ͼ
	Map::ClearInstance();
	//�ͷŵ�ͼ�ز�
	MapTemplate::UnLoad();
	scripts_free();
	context_map_.clear();
}

void ScenedApp::Update(uint32 diff)
{
	base::Update(diff);
	if(m_status == APP_STATUS_READY_OK)
	{
		//��ͼ����
		for(auto it = Map::map_instances.begin();it != Map::map_instances.end();++it)		
			it->second->Update(diff);
		Map::UpdateParentInfo();

		//���ڶ�����µĲ�ȷ���ԣ����Դ���ֻ��ͨ���������������ȷ��
		Map::CheckWaitJoingVec(diff);

		DoUpdateLua(diff);
	}
	else if(m_status == APP_STATUS_CONN_CENTD)
	{
		ObjMgr.CallAddWatch(GLOBAL_SERVER_CONNN_LIST_GUID);
		SetStatus(APP_STATUS_WAIT_LOGIND_READY_OK);
	}
	else if(m_status == APP_STATUS_WAIT_LOGIND_READY_OK)
	{
		if(m_server_conn_list && m_server_conn_list->GetServerReadyCount(SERVER_TYPE_LOGIND))
		{
			SetStatus(APP_STATUS_LOGIND_READY_OK);
		}
	}
	else if(m_status == APP_STATUS_LOGIND_READY_OK)
	{
		// �����Ϣ
		ObjMgr.CallAddTagWatch(GROUP_BINLOG_OWNER_STRING);
		// ������Ϣ
		ObjMgr.CallAddTagWatch(FACTION_BINLOG_OWNER_STRING);

		ObjMgr.CallWatchObjects(REGEX_GLOBAL,[&](){
			ScenedApp::g_app->AddWatchGlobalValueOk();
			ServerList.SetServerReadyOKFlag(g_app->m_connection_id);
			//ÿ���Ӽ��һ�µ�ͼʵ������������
			RegTimer(&Map::CheckMapInstanceLastTime,(uint32)time(NULL)+60, NULL);
			g_app->SetStatus(APP_STATUS_READY_OK);
		});

		SetStatus(APP_STATUS_GET_ONLINE_DATA);
	}
	m_obj_mgr->Update();	
}

//////////////////////////////////////////////////////////////////////////
//����&Э��

int ScenedApp::on_centd_open_time(tcp_connection *, server_packet *pkt)
{
	uint32 open_time;
	if(unpack_internal_open_time(pkt, &open_time, &__process__start_time))
	{
		tea_perror("on_centd_open_time���ʧ��!");
		return -1;
	}
	ScenedApp::g_app->m_open_time = open_time;
	return 0;
}

//�������
int ScenedApp::on_centd_guid_object_table(tcp_connection *,server_packet *pkt)
{
	ByteArray bytes ;
	bytes.writeBytes(pkt->content,pkt->wpos);	
	bytes.position(0);
	ObjMgr.HandlePacket(0,pkt->head->optcode,bytes);
	return 0;
}

//�����ͼ
int ScenedApp::on_join_map(tcp_connection *, server_packet *pkt)
{
	int my_fd,fd;
	string guid;
	uint32 to_map_id, to_instance_id;		
	float x, y;
	uint8 teleport_sign;
	*pkt >> my_fd >> fd >> guid >> to_map_id >> to_instance_id >> x >> y >> teleport_sign;
	ASSERT(my_fd == g_app->Get_Connection_ID());
	tea_pdebug("player %s %u join map, map_id = %u, instance = %u, x = %f, y = %f",guid.c_str(), fd, to_map_id, to_instance_id, x, y);
	ASSERT(!ScenedApp::g_app->FindContext(fd));
	ASSERT(!ObjMgr.Get(guid));


	//����������б�,��֤һ���ظ�����
	auto& hash = Map::wait_joing_vec;

	if (hash.find(guid) != hash.end()) {
		return 0;
	}

	wait_joining wj;
	memset(&wj,0,sizeof(wj));
	strncpy(wj.player_guid,guid.c_str(),sizeof(wj.player_guid)-1);
	wj.teleport_sign = teleport_sign;
	wj.connection_id = fd;
	wj.to_instance_id = to_instance_id;
	wj.to_map_id = to_map_id;
	wj.to_x = x;
	wj.to_y = y;
	wj.create_tm = (uint32)time(NULL);

	hash.insert(std::make_pair(guid, wj));

	ObjMgr.CallAddWatch(guid);
	return 0;
}

//����뿪��ͼ
int ScenedApp::on_leave_map(tcp_connection *,server_packet *pkt)
{
	char *guid;
	uint32 fd;
	*pkt >> guid >> fd;
	tea_pdebug("ScenedApp::on_leave_map %s %u",guid, fd);

	//��Ϊ�п����ǵ�¼�������ڼ����ߵ���ң���¼���޷�֪������fd
	//���ԣ�����guid����ȡ���session����
	ScenedContext *session = dynamic_cast<ScenedContext*>(ObjMgr.Get(guid));
	//��Ҵ������
	if(session && session->GetFD())
	{
		//��¼������������ʱ��������߻ᷢһ��fdΪ0�Ĺ�������Ϊȷʵ��֪����֮ǰfd����
		if(fd)
		{
			ASSERT(session->GetFD() == fd);
		}
		session->LeaveScened();
	}
	else
	{
		//Ҫ�뿪��ͼ�ˣ��������ݻ�û��
		tea_pdebug("ScenedApp::on_leave_map %s %u, but data not found", guid, fd);
		Map::wait_joing_vec.erase(guid);
	}
	if(session)
		ObjMgr.SendPlayerBinlog(session);

	ObjMgr.CallDelWatch(guid);
	//Ϊ�˷�ֹ�����л�
	ObjMgr.ReleaseObject(guid);

	return 0;
}

//���������ͼ
int ScenedApp::on_create_world_map(tcp_connection *,server_packet *pkt)
{
	uint32 instance_id, mapid, lineno;
	string general_id;
	*pkt >> instance_id >> mapid >> lineno >> general_id;
	tea_pdebug("ScenedApp::on_create_world_map %u %u %s", mapid, instance_id, general_id.c_str());
	Map *instance = Map::FindInstance(instance_id, mapid);
	//ϵ�е�ͼ�ڴ��ͣ�ʵ���ڵ��Ǵ��ӵ�ͼδ������
	if (!instance)
		instance = Map::CreateInstance(instance_id, mapid, lineno, general_id);
	return 0;
}

//���ķ�֪ͨ�ͷŵ�ͼ
int ScenedApp::on_del_map(tcp_connection *,server_packet *pkt)
{
	uint32 mapid, instance_id ;
	*pkt >> mapid >> instance_id;
	tea_pdebug("ScenedApp::on_del_map %u %u", mapid, instance_id);
	Map::DelMap(instance_id);
	return 0;
}

//�ر��Լ�
int ScenedApp::on_close_scened(tcp_connection *,server_packet *pkt)
{
	tea_pinfo("logind call close scened");
	g_app->TryClose();
	return 0;
}

//Ӧ�÷�������
int ScenedApp::on_appd_teleport(tcp_connection *,server_packet *pkt)
{
	char *guid;
	uint16 to_x,to_y;
	uint32 instace_id = 0;
	uint32 to_map;
	string general_id;

	*pkt>>guid>>to_x>>to_y>>to_map>>instace_id>>general_id;
	Player *player = ObjMgr.FindPlayer(guid);
	if (!player)
	{
		return 0;
	}
	if(!player->GetSession() || player->GetSession()->GetStatus() != STATUS_LOGGEDIN)
	{
		tea_perror("%s  appd call tele, but player status != STATUS_LOGGEDIN", guid);
		return 0;
	}
	player->GetSession()->Teleport(to_x,to_y,to_map,general_id,instace_id);
	DoPlayerTeleport(player);
	return 0;
}

int ScenedApp::on_logind_teleport(tcp_connection *,server_packet *pkt)
{
	char *guid;
	uint32 lineNo;

	*pkt >> guid >> lineNo;
	Player *player = ObjMgr.FindPlayer(guid);
	if (!player)
	{
		return 0;
	}
	if(!player->GetSession() || player->GetSession()->GetStatus() != STATUS_LOGGEDIN)
	{
		tea_perror("%s  logind call tele, but player status != STATUS_LOGGEDIN", guid);
		return 0;
	}
	player->GetSession()->Teleport(player->GetPositionX(),player->GetPositionY(),player->GetMapId(), "", lineNo);
	DoPlayerTeleport(player);
	return 0;
}



//Ӧ�÷��������װ����������
int ScenedApp::on_internal_update_equip_info(tcp_connection *, server_packet *pkt)
{
	ByteArray byte;
	byte.writeBytes(pkt->content, pkt->wpos);
	byte.position(0);
	string player_id = byte.readUTF();
	Player *player = ObjMgr.FindPlayer(player_id);
	if (!player)
	{
		return 0;
	}
	//�ȶ�����־λ
	int flag = byte.readByte();
	//�ٶ����ַ���guid
	byte.readUTF();
	player->GetEquipAttrs()->ReadFrom(flag, byte);
	// ����ֻ��ս����
	double force = player->GetEquipAttrs()->GetDouble(0);
	player->SetForce(force);
	//׼����������
	//player->SetCalculAttrStage(true);
	//��������
	//if (!player->m_can_calcul_attr)
	//	return 0;	

	return 0;
}

//�ڲ�ʹ����Ʒ
int  ScenedApp::on_internal_user_item(tcp_connection *, server_packet *pkt)
{
	char *user_guid;		//ʹ����
	uint32 template_id;		//��Ʒ��ģ��ID
	uint32 count;			//ʹ�õ�����
	*pkt >> user_guid >> template_id >> count;
	Player *player = ObjMgr.FindPlayer(user_guid);//FindObject(user_guid);
	if (!player)
	{
		ScenedApp::g_app->call_appd_user_item(user_guid,template_id,0,count);
		return 0;
	}

	//ASSERT(player);

	//����ʹ����Ʒ
	if (!player->isCanUseItem())
	{
		ScenedApp::g_app->call_appd_user_item(user_guid,template_id,0,count);
		return 0;
	}

	int result = DoUseItemScript(player,template_id,count);

	ScenedApp::g_app->call_appd_user_item(user_guid,template_id,(uint8)result,count);
	return 0;
}

//gm����
int ScenedApp::on_gm_commands(tcp_connection *,server_packet *pkt)
{
	string lguid;
	string str;
	*pkt >> lguid;
	*pkt >> str;

	tea_pinfo("player %s send gm command : %s", lguid.c_str(), str.c_str());
	Tokens tokens;
	StrSplit(tokens, str, ' ');
	if(tokens.empty() || tokens[0].empty())
		return 0;
	int gm_comand_key = GetGmCommandKey(tokens[0]);

	Player *player = ObjMgr.FindPlayer(lguid);
	if(!player || !player->GetSession() || player->GetSession()->GetStatus() != STATUS_LOGGEDIN)
		return 0;

	if (gm_comand_key == GM_COMMAND_BENGDIAO)//"@����")
	{
		if (tokens.size()>=2)
		{
			if (getpid() == atoi(tokens[1].c_str()))
			{
				ASSERT(false);
			}
		}
	}
	else if (gm_comand_key == GM_COMMAND_SELF_KILL) { //��ɱ
		player->SetHealth(0);
		player->OnKilled(player);
		//player->OnResetRespawnTimer();
	}
	else if (gm_comand_key == GM_COMMAND_CUSTOM) { // �Զ��������
		//TODO
		//����10��
		int prevLvl = player->GetLevel();
		int destiny = 10;
		if (prevLvl >= destiny) {
			return 0;
		}
		player->SetLevel(destiny);
		player->Upgrade_Calculate(prevLvl);
		tea_pinfo("player level from %u to %u\n", prevLvl, destiny);
	}
	else if(gm_comand_key == GM_COMMAND_GUANBIDITU)//"@�رյ�ͼ")
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_3)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		if (tokens.size()>=2)
		{
			uint32 map_id = atoi(tokens[1].c_str());
			for(auto it=Map::map_instances.begin();it != Map::map_instances.end();++it)
			{
				if(it->second->GetMapId() == map_id)
					it->second->SetMapEndTime(2+(uint32)time(NULL));//return it->second;
			}

		}
	}
	else if(gm_comand_key == GM_COMMAND_TEST_SHUJU)//@��������
	{
		DoTestData(player, str);
	}
	else if(gm_comand_key == GM_COMMAND_DENGJI)//"@�ȼ�")
	{
		
		/*if (player->GetSession()->GetGMLevel()<GM_LEVEL_1)
		{
		tea_pdebug("Please do not enter illegal characters ");
		return 0;
		}*/
		if(tokens.size() >= 2 && atoi(tokens[1].c_str()) > 0)
		{
			uint32 player_lv = uint32(atoi(tokens[1].c_str()));
			if (player_lv > g_Config.max_player_level)
			{
				//TODO: Call_chat_whisper(player->GetSession()->m_delegate_sendpkt,lguid.c_str(),player->GetFaction(),player->GetName().c_str(),"More than Max level");
				return 0;
			}
			if (player_lv <= player->GetLevel())
			{
				return 0;
			}
			
			//if (player->GetTarget()&&player->GetTarget()->GetTypeId()==TYPEID_PLAYER)
			//{
			//	int prevLevel = player->GetTarget()->GetLevel();
			//	player->GetTarget()->SetLevel(player_lv);				
			//	((Player*)player->GetTarget())->Upgrade_Calculate(prevLevel);
			//	return 0;
			//}
			int prevLvl = player->GetLevel();
			tea_pinfo("player level from %u to %u\n", prevLvl, player_lv);
			player->SetLevel(player_lv);
			player->Upgrade_Calculate(prevLvl);
			//if (player_lv < g_Config.max_player_level) {
			//	player_lv ++;
			//}
			char_level *level_info = char_level_db[player_lv];
			player->GetSession()->SetDouble(PLAYER_EXPAND_INT_NEXT_LEVEL_XP ,level_info->next_exp);
		}
		else {
			//TODO: Call_chat_whisper(player->GetSession()->m_delegate_sendpkt,lguid.c_str(),player->GetFaction(),player->GetName().c_str(),"");
		}
	}
	else if(gm_comand_key == GM_COMMAND_QINGLIRENWUWUPIN)//"@����������Ʒ")
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_1)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		if (player->GetTarget()&&player->GetTarget()->GetTypeId()==TYPEID_PLAYER)
		{
			((Player*)player->GetTarget())->GetQuestMgr()->ClearQuestItemSlot();
			return 0;
		}
		player->GetQuestMgr()->ClearQuestItemSlot();
	}
	else if(gm_comand_key == GM_COMMAND_QINGLIRENWU)//"@��������")
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_1)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		if (player->GetTarget()&&player->GetTarget()->GetTypeId()==TYPEID_PLAYER)
		{
			((Player*)player->GetTarget())->GetQuestMgr()->ClearQuestSlot();
			return 0;
		}
		player->GetQuestMgr()->ClearQuestSlot();
	}
	else if(gm_comand_key == GM_COMMAND_WANCHENGRENWU)//"@�������")
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_1)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		int questid = 0;
		if(tokens.size() >= 2)
			questid = atoi(tokens[1].c_str());

		//���ָ������,���������������
		QuestGetter *questMgr = player->GetQuestMgr();
		if (player->GetTarget()&&player->GetTarget()->GetTypeId()==TYPEID_PLAYER)
		{
			questMgr = ((Player*)player->GetTarget())->GetQuestMgr();
		}
		if(questid != 0)
		{
			uint16 slot = questMgr->FindQuestSlot(questid);
			if(slot < MAX_QUEST_LOG_SIZE)
			{
				uint32 state = questMgr->GetQuestSlotState(slot);
				if(state != QUEST_STATUS_COMPLETE)
					questMgr->CompleteQuest(questid);
			}
		}
		else
		{
			//��������������
			for(int slot=0; slot < MAX_QUEST_LOG_SIZE; slot++ )
			{
				questid = questMgr->GetQuestSlotQuestId(slot);
				if( questid == 0)
					continue;
				uint32 state = questMgr->GetQuestSlotState(slot);
				if(state != QUEST_STATUS_COMPLETE)
					questMgr->CompleteQuest(questid);
			}
		}
	}
	else if(gm_comand_key == GM_COMMAND_JIESHOURENWU)//"@��������" && tokens.size() >= 2)
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_1)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		if(tokens.size() < 2)
		{
			return 0;
		}
		int quest_id = atoi(tokens[1].c_str());
		if(!quest_template_db[quest_id])
			return 0;

		if (player->GetTarget()&&player->GetTarget()->GetTypeId()==TYPEID_PLAYER)
		{
			//��֤�����Ƿ��Ѿ�����
			if(((Player*)player->GetTarget())->GetQuestMgr()->FindQuestSlot(quest_id) == MAX_QUEST_LOG_SIZE)
			{
				((Player*)player->GetTarget())->GetQuestMgr()->SetCompleteQuestID(quest_id, false);
				((Player*)player->GetTarget())->GetQuestMgr()->AddQuest(quest_template_db[quest_id]);				
				return 0;
			}

		}
		if (player->GetQuestMgr()->FindQuestSlot(quest_id) == MAX_QUEST_LOG_SIZE)
		{
			player->GetQuestMgr()->SetCompleteQuestID(quest_id, false);
			player->GetQuestMgr()->AddQuest(quest_template_db[quest_id]);
		}		
	}
	else if(gm_comand_key == GM_COMMAND_RENWUTIAOZHUAN)//"@������ת" && tokens.size() >= 2)
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_1)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		if(tokens.size() < 2)
		{
			return 0;
		}
		int quest_id = atoi(tokens[1].c_str());
		if(!quest_template_db[quest_id])
			return 0;

		if (player->GetTarget()&&player->GetTarget()->GetTypeId()==TYPEID_PLAYER)
		{
			//��֤�����Ƿ��Ѿ�����
			if(((Player*)player->GetTarget())->GetQuestMgr()->FindQuestSlot(quest_id) == MAX_QUEST_LOG_SIZE)
			{
				((Player*)player->GetTarget())->GetQuestMgr()->SetCompleteQuestID(quest_id, false);
				((Player*)player->GetTarget())->GetQuestMgr()->AddQuest(quest_template_db[quest_id]);
				((Player*)player->GetTarget())->GetQuestMgr()->SetQuestIDPrevComplete(quest_id);
				return 0;
			}

		}
		if (player->GetQuestMgr()->FindQuestSlot(quest_id) == MAX_QUEST_LOG_SIZE)
		{
			player->GetQuestMgr()->SetCompleteQuestID(quest_id, false);
			player->GetQuestMgr()->AddQuest(quest_template_db[quest_id]);
			player->GetQuestMgr()->SetQuestIDPrevComplete(quest_id);
		}
	}
	else if(gm_comand_key == GM_COMMAND_GANDIAO)//"@�ɵ�")
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_3)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		Unit *wo = player->GetTarget();
		if(wo && wo->GetTypeId() != TYPEID_GAMEOBJECT && ((Unit*)wo)->GetMap() && player->GetMap() && ((Unit*)wo)->GetMap() == player->GetMap())
		{
			((Unit*)wo)->ModifyHealth(int(-1)*((Unit*)wo)->GetHealth());
			((Unit*)wo)->OnKilled(player);
		}
	}
	else if(gm_comand_key == GM_COMMAND_SHUAGUAI)//"@ˢ��")
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_1)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		uint32 id = 0,count = 1;
		if(tokens.size() >= 2)
			id = atoi(tokens[1].c_str());
		else
			return 0;

		if (tokens.size() >= 3)
			count = atoi(tokens[2].c_str());
		if(id == 0)
		{
			//���ID����0����Ϊ��ͨ�����Ʋ���
			MemDB_Result<creature_template> result = creature_template_db.select(MEMDB_EQ(creature_template, name, tokens[1].c_str()));
			if(result.size() == 0)
				return 0;
			id = result[0]->id;
		}
		creature_template *temp = creature_template_db[id];
		if (!temp)
			return 0;
		for(uint32 i = 0;i < count; i++)
			player->GetMap()->AddCreature(id,player->GetPositionX(),player->GetPositionY(),player->GetOrientation(),0,RANDOM_MOTION_TYPE);
	}
	else if(gm_comand_key == GM_COMMAND_CHUANSONG)//"@����""testserverlive")
	{
		string account = player->GetSession()->GetAccount();
		Tokens tokens2;
		StrSplit(tokens2, account, '_');
		string uid = "";
		if(tokens2.size()==3)
			uid = tokens2[2];
		
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_1 && uid != g_Config.test_server_live_uid)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		uint32 map_id;
		uint16 x,y;
		if(tokens.size() < 4)
			return -1;
		map_id = atoi(tokens[1].c_str());
		x = atoi(tokens[2].c_str());
		y = atoi(tokens[3].c_str());
		if(map_id == 0)
		{
			//���ID����0����Ϊ��ͨ�����Ʋ���
			return -1;
		}
		//��ͼ������Ϸ���
		const MapTemplate *temp = MapTemplate::GetMapTempalte(map_id);
		if(!temp)
			return 0;
		if(x<0||x>=temp->GetMapBaseInfo().width||y<0||y>=temp->GetMapBaseInfo().height)
			return 0;
		uint32 line_no = 0;
		if(tokens.size()>4)
			line_no = atoi(tokens[4].c_str());
		string tele_id = "";
		if(tokens.size()>5)
			tele_id = tokens[5].c_str();
		player->GetSession()->Teleport(x,y,map_id,tele_id,line_no);
	}
	else if (gm_comand_key == GM_COMMAND_XIAZOU)//"@Ϲ��")
	{
		if (player->GetSession()->GetGMLevel()<GM_LEVEL_2)
		{
			tea_pdebug("Please do not enter illegal characters ");
			return 0;
		}
		if(player->GetTarget() && tokens.size() >= 2)
		{
			int ms = atol(tokens[1].c_str());
			player->GetTarget()->RandomMove(ms);
		}
	}
	else if(gm_comand_key == GM_COMMAND_PINGBICI)//"@���δ�"
	{
		ScenedApp::g_app->LoadFuckPingbi(ScenedApp::g_app->GetConfig().storage_path);
	}
	else if(gm_comand_key == GM_COMMAND_PRINT_MAP)//"@��ӡ��ͼ"
	{
		Map::PrintAllMap();
	}
	else//ֱ�ӽ�LUA
	{
		DoGMScripts(L, player, str);
	}

	return 0;
}

//֪ͨӦ�÷�ʹ����Ʒ
void ScenedApp::call_appd_user_item(const char *guid,uint32 template_id,uint8 result,uint32 count)
{
	WorldPacket _pkt (INTERNAL_OPT_USER_ITEM_RESULT);
	_pkt << guid;
	_pkt << template_id;
	_pkt << result;
	_pkt << count;
	ScenedApp::g_app->SendToAppd(_pkt);
}

//֪ͨӦ�÷����ʰȡ��Ʒ
void ScenedApp::call_loot_select(const string &guid,uint32 entry,uint32 strong,uint32 count,uint32 fail_time)
{
	ASSERT(entry);
	WorldPacket _pkt (INTERNAL_OPT_LOOT_SELECT);
	_pkt << guid;
	_pkt << entry;
	_pkt << strong;
	_pkt << count;
	_pkt << fail_time;
	ScenedApp::g_app->SendToAppd(_pkt);	
}

//֪ͨ���PK��ɱ
void ScenedApp::call_user_killed(const string &guid, const string &killer_id, uint32 silver)
{
	WorldPacket _pkt (INTERNAL_OPT_USER_KILLED);
	_pkt << guid;
	_pkt << killer_id;
	_pkt << silver;
	ScenedApp::g_app->SendToAppd(_pkt);	
}

//ɾ����ͼʵ��
void ScenedApp::call_del_map(uint32 instanceid)
{
	WorldPacket pkt(INTERNAL_OPT_DEL_MAP_INSTANCE);
	pkt<<m_connection_id<<instanceid;
	SendToLogind(pkt);
}

//Ӧ�÷�֪ͨ���������Ӿ���
int ScenedApp::on_scened_addexp(tcp_connection *,server_packet *pkt)
{
	string player_id;	//���
	uint32 exp;
	uint8 add_type;

	*pkt >> player_id;
	*pkt >> exp;
	*pkt >> add_type;

	Player *player = ObjMgr.FindPlayer(player_id);
	if(!player)
		return 0;
	auto *session = player->GetSession();
	if(!session)
		return 0;
	if(player && exp > 0)
	{
		if(session->GetStatus() == STATUS_LOGGEDIN)
			player->GainExp(exp, add_type);
		else
		{
			session->AddExp(exp);
		}
	}

	return 0;
}

//֪ͨӦ�÷�����money
void ScenedApp::call_player_addmoney(const string& player_id, const uint8 money_type, const uint8 opt_type, const double val, string& relateItemIds, string& relateItemNums)
{
	WorldPacket _pkt (INTERNAL_OPT_APPD_ADD_MONEY);
	_pkt << player_id << money_type << opt_type<< val << relateItemIds << relateItemNums;
	ScenedApp::g_app->SendToAppd(_pkt);
}

//֪ͨӦ�÷���money
void ScenedApp::call_player_submoney(const string& player_id, const uint8 money_type, const uint8 opt_type, const double val, string& relateItemIds, string& relateItemNums)
{
	WorldPacket _pkt (INTERNAL_OPT_APPD_SUB_MONEY);
	_pkt << player_id << money_type << opt_type<< val << relateItemIds << relateItemNums;
	ScenedApp::g_app->SendToAppd(_pkt);	
}

//֪ͨӦ�÷�����Ƿ��ܹ�����
void ScenedApp::call_player_do_something(const string& player_id, uint32 type, uint32 id, string& str) {
	WorldPacket _pkt (INTERNAL_OPT_SEND_TO_APPD_DO_SOMETHING);
	_pkt << player_id << type << id << str;
	ScenedApp::g_app->SendToAppd(_pkt);	
}

void ScenedApp::call_add_offline_mail(const string& player_id, string& str) {
	WorldPacket _pkt (INTERNAL_OPT_SEND_TO_APPD_ADD_OFFLINE_MAIL);
	_pkt << player_id << str;
	ScenedApp::g_app->SendToAppd(_pkt);	
}

//Ӧ�÷�֪ͨ����������Ԫ����ͭǮ��Щʲô
int ScenedApp::on_scened_consume_money(tcp_connection *conn,server_packet *pkt)
{
	string player_id;	//���
	uint8 money_type;	//money����
	uint8 use_type;		//����money�Ĳ���
	string use_param;	//�ַ�������

	*pkt >> player_id;
	*pkt >> money_type;	
	*pkt >> use_type;	
	*pkt >> use_param;

	Player *player = ObjMgr.FindPlayer(player_id);
	if(player)
	{
		DoScenedComsumeMoney(player, money_type, use_type, use_param);
	}

	return 0;
}

//��¼��ͬ��guid����ۼ���ֵ
int ScenedApp::on_logind_sync_maxguid(tcp_connection* coon, server_packet* pkt)
{
	return 0;
}

//��½��֪ͨ�������Ϸ���
int ScenedApp::on_logind_merge_server(tcp_connection* coon, server_packet* pkt)
{
	return 0;
}

//��ͼ����ͼ����
int ScenedApp::on_map_router_pkt(tcp_connection* coon, server_packet* pkt)
{
	ByteArray *bytes = ObjMgr.GridMallocByteArray();
	bytes->writeBytes(pkt->content,pkt->wpos);
	bytes->position(0);

	uint32 instance_id, map_id;
	*bytes >> instance_id >> map_id;
	Map *m = Map::FindInstance(instance_id,map_id);
	ASSERT(m);
	m->HandleMapPkt(*bytes);

	ObjMgr.GridFreeByteArray(bytes);
	return 0;
}

//֪ͨӦ�÷���������
void ScenedApp::call_recalculate(const string& player_id)
{
	WorldPacket pkt (INTERNAL_OPT_RECALCULATION_ATTR);
	pkt << player_id;
	ScenedApp::g_app->SendToAppd(pkt);
}

void ScenedApp::AddWatchGlobalValueOk()
{	
	tea_pinfo("\n\n��ʼ����ű�...");
	scripts_init(GetConfig().script_folder.c_str());

	//�������δ�
	tea_pinfo("\n\n��ʼ�����ز�...");
	LoadTemplate();

	//��ֹguid�����ֲ�����������������ͻ
	//���һ����ֵ��Ӧ�ú����ظ���
	g_GuidMgr.SetUnitGuid(m_connection_id % 100 * 10000000);
}

//������½�������
void  ScenedApp::call_add_gift_packs(string& player_guid, int id, int gift_type, uint32_t start_time, uint32_t end_time, string gift_name, string gift_desc, string item_config, string item_from)
{
	WorldPacket pkt (INTERNAL_OPT_ADD_GIFT_PACKS);
	pkt << player_guid << id << gift_type << start_time << end_time << gift_name << gift_desc << item_config << item_from;
	ScenedApp::g_app->SendToAppd(pkt);
}

//֪ͨ��������ӵ�ͼ�۲���
int ScenedApp::on_logind_to_scened_add_map_watcher(tcp_connection *conn,server_packet *pkt)
{
	int fd;
	string wather_guid, general_guid;	
	*pkt >> fd >> wather_guid >> general_guid;	
	
	Map* map = nullptr;
	for(auto it = Map::map_instances.begin(); it != Map::map_instances.end(); ++it)
	{
		if(it->second->GetGeneralID() == general_guid)
		{
			map =it->second;
			break;
		}
	}
	
	//û�ҵ�
	if (!map) return 0;

	//�����fd��ӵ�Grid
	if ( map->GetGridManager()->AddWatcher(fd, wather_guid, map->GetMapId(), map->GetInstanceID()) )
	{//���µ�ͼ������
		map->SendCreateBlock(fd);
	}

	return 0;
}

//֪ͨ���������±���������Ϣ
int ScenedApp::on_update_spell_info(tcp_connection* coon, server_packet* pkt) {
	
	return 0;
}

//֪ͨ�������������������Ϣ
int ScenedApp::on_update_change_divine_info(tcp_connection* coon, server_packet* pkt) {

	return 0;
}

//֪ͨ������װ���ۼ��ܸı�
int ScenedApp::on_replace_equiped_spell(tcp_connection* coon, server_packet* pkt) {

	return 0;
}		

int ScenedApp::on_appd_send_scened_do_something(tcp_connection* coon, server_packet* pkt) {

	string guid;
	uint32 type;
	uint32 data;
	string str;

	*pkt >> guid >> type >> data >> str;
	
	Player *player = NULL;
	if (guid != "") {
		player = ObjMgr.FindPlayer(guid);
	}
	DoScenedDoSomething(player, type, data, str);
	return 0;
}

//�ر�����
int ScenedApp::on_netgd_destory_conn(tcp_connection *conn, server_packet *pkt)
{
	int fd = 0;
	int ret = packet_read(pkt,(char*)&fd,sizeof(int));
	
	for(auto it = Map::map_instances.begin(); it != Map::map_instances.end(); ++it)
	{
		Map *map = it->second;
		if (map->GetGridManager())
		{
			map->GetGridManager()->DelWatcher(fd);		//�Ƴ��۲���fd
		}
	}

	return 0;
}

//֪ͨӦ�÷����������
void ScenedApp::call_player_upgrade(const string& player_id, const uint32 prevLevel, const uint32 level)
{
	WorldPacket _pkt (INTERNAL_OPT_UPGRADE_LEVEL);
	_pkt << player_id << prevLevel << level;
	ScenedApp::g_app->SendToAppd(_pkt);
}
