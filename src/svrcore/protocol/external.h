#ifndef _EXTERNAL_PROTOCOL_H_
#define _EXTERNAL_PROTOCOL_H_

#include <svrcore-internal.h>
#define EXTERNAL_PACKET_STR_ARRAY_MAX_LEN 1000




//////////////////////////////////////////////////////////////////////////
/// List of Opcodes
enum Opcodes
{
	MSG_NULL_ACTION		= 0,	/*��Ч����*/	//null_action
	MSG_PING_PONG		= 1,	/*��������״̬*/	//ping_pong
	CMSG_FORCED_INTO		= 2,	/*�ߵ����ߵ�׼��ǿ�Ƶ�½*/	//forced_into
	CMSG_GET_SESSION		= 3,	/*���Session����*/	//get_session
	MSG_ROUTE_TRACE		= 4,	/*���ط����ݰ�·�ɲ���*/	//route_trace
	CMSG_WRITE_CLIENT_LOG		= 5,	/*��¼�ͻ�����־*/	//write_client_log
	SMSG_OPERATION_FAILED		= 6,	/*����ʧ��*/	//operation_failed
	MSG_SYNC_MSTIME		= 7,	/*ͬ��ʱ��*/	//sync_mstime
	SMSG_UD_OBJECT		= 8,	/*�������*/	//ud_object
	CMSG_UD_CONTROL		= 9,	/*������¿���Э��*/	//ud_control
	SMSG_UD_CONTROL_RESULT		= 10,	/*������¿���Э����*/	//ud_control_result
	SMSG_GRID_UD_OBJECT		= 11,	/*GRID�Ķ������*/	//grid_ud_object
	SMSG_GRID_UD_OBJECT_2		= 12,	/*GRID�Ķ������*/	//grid_ud_object_2
	SMSG_LOGIN_QUEUE_INDEX		= 13,	/*���߿ͻ��ˣ�Ŀǰ�Լ����ڵ�¼���еĵڼ�λ*/	//login_queue_index
	SMSG_KICKING_TYPE		= 14,	/*����ԭ��*/	//kicking_type
	CMSG_GET_CHARS_LIST		= 15,	/*��ȡ��ɫ�б�*/	//get_chars_list
	SMSG_CHARS_LIST		= 16,	/*��ɫ�б�*/	//chars_list
	CMSG_CHECK_NAME		= 17,	/*��������Ƿ����ʹ��*/	//check_name
	SMSG_CHECK_NAME_RESULT		= 18,	/*������ֽ��*/	//check_name_result
	CMSG_CHAR_CREATE		= 19,	/*������ɫ*/	//char_create
	SMSG_CHAR_CREATE_RESULT		= 20,	/*��ɫ�������*/	//char_create_result
	CMSG_DELETE_CHAR		= 21,	/*ɾ����ɫ*/	//delete_char
	SMSG_DELETE_CHAR_RESULT		= 22,	/*��ɫɾ�����*/	//delete_char_result
	CMSG_PLAYER_LOGIN		= 23,	/*��ҵ�¼*/	//player_login
	CMSG_PLAYER_LOGOUT		= 24,	/*����˳�*/	//player_logout
	CMSG_REGULARISE_ACCOUNT		= 25,	/*��ʱ�˺�ת����*/	//regularise_account
	CMSG_CHAR_REMOTESTORE		= 26,	/*��ɫ������Ϣ*/	//char_remotestore
	CMSG_CHAR_REMOTESTORE_STR		= 27,	/*��ɫ������Ϣ*/	//char_remotestore_str
	CMSG_TELEPORT		= 28,	/*���ͣ������C->S��mapid��������ɴ��͵�ID*/	//teleport
	MSG_MOVE_STOP		= 29,	/*ֹͣ�ƶ�*/	//move_stop
	MSG_UNIT_MOVE		= 30,	/*unit�����ƶ�*/	//unit_move
	CMSG_USE_GAMEOBJECT		= 31,	/*ʹ����Ϸ����*/	//use_gameobject
	CMSG_BAG_EXCHANGE_POS		= 32,	/*��������-����λ��*/	//bag_exchange_pos
	CMSG_BAG_DESTROY		= 33,	/*��������-������Ʒ*/	//bag_destroy
	CMSG_BAG_ITEM_SPLIT		= 34,	/*�ָ���Ʒ*/	//bag_item_split
	CMSG_BAG_ITEM_USER		= 35,	/*ʹ����Ʒ*/	//bag_item_user
	SMSG_BAG_ITEM_COOLDOWN		= 36,	/*�·���Ʒ��ȴ*/	//bag_item_cooldown
	SMSG_GRID_UNIT_MOVE		= 37,	/*grid�е�unit�ƶ�������*/	//grid_unit_move
	SMSG_GRID_UNIT_MOVE_2		= 38,	/*grid�е�unit�ƶ�������2*/	//grid_unit_move_2
	CMSG_EXCHANGE_ITEM		= 39,	/*�һ���Ʒ*/	//exchange_item
	CMSG_BAG_EXTENSION		= 40,	/*������չ*/	//bag_extension
	CMSG_NPC_GET_GOODS_LIST		= 41,	/*����NPC��Ʒ�б�*/	//npc_get_goods_list
	SMSG_NPC_GOODS_LIST		= 42,	/*Npc��Ʒ�б�*/	//npc_goods_list
	CMSG_STORE_BUY		= 43,	/*������Ʒ*/	//store_buy
	CMSG_NPC_SELL		= 44,	/*������Ʒ*/	//npc_sell
	CMSG_NPC_REPURCHASE		= 45,	/*�ع���Ʒ*/	//npc_repurchase
	CMSG_AVATAR_FASHION_ENABLE		= 46,	/*ʱװ�Ƿ�����*/	//avatar_fashion_enable
	CMSG_QUESTHELP_TALK_OPTION		= 47,	/*����Ի�ѡ��*/	//questhelp_talk_option
	CMSG_TAXI_HELLO		= 48,	/*��NPC�Ի���ô��͵��б�*/	//taxi_hello
	SMSG_TAXI_STATIONS_LIST		= 49,	/*���ʹ��͵��б�*/	//taxi_stations_list
	CMSG_TAXI_SELECT_STATION		= 50,	/*ѡ���͵�*/	//taxi_select_station
	CMSG_GOSSIP_SELECT_OPTION		= 51,	/*��NPC����ѡ��ѡ��*/	//gossip_select_option
	CMSG_GOSSIP_HELLO		= 52,	/*��NPC���Ļ�ȡѡ��*/	//gossip_hello
	SMSG_GOSSIP_MESSAGE		= 53,	/*����������Ϣ��ѡ��*/	//gossip_message
	CMSG_QUESTGIVER_STATUS_QUERY		= 54,	/*���񷢲���״̬��ѯ*/	//questgiver_status_query
	SMSG_QUESTGIVER_STATUS		= 55,	/*����NPC״̬*/	//questgiver_status
	MSG_QUERY_QUEST_STATUS		= 56,	/*��ѯ����״̬*/	//query_quest_status
	CMSG_QUESTHELP_GET_CANACCEPT_LIST		= 57,	/*�ɽ�����*/	//questhelp_get_canaccept_list
	SMSG_QUESTHELP_CANACCEPT_LIST		= 58,	/*�·��ɽ������б�*/	//questhelp_canaccept_list
	SMSG_QUESTUPDATE_FAILD		= 59,	/*����ʧ��*/	//questupdate_faild
	SMSG_QUESTUPDATE_COMPLETE		= 60,	/*�����������*/	//questupdate_complete
	CMSG_QUESTLOG_REMOVE_QUEST		= 61,	/*��������*/	//questlog_remove_quest
	CMSG_QUESTGIVER_COMPLETE_QUEST		= 62,	/*�������*/	//questgiver_complete_quest
	SMSG_QUESTHELP_NEXT		= 63,	/*��������֪ͨ���������¸�����*/	//questhelp_next
	CMSG_QUESTHELP_COMPLETE		= 64,	/*����ϵͳǿ���������*/	//questhelp_complete
	SMSG_QUESTUPDATE_ACCEPT		= 65,	/*��������ɹ�*/	//questupdate_accept
	CMSG_QUESTHELP_UPDATE_STATUS		= 66,	/*�����������_�±�����*/	//questhelp_update_status
	SMSG_QUESTGETTER_COMPLETE		= 67,	/*���������*/	//questgetter_complete
	CMSG_QUESTGIVER_ACCEPT_QUEST		= 68,	/*������*/	//questgiver_accept_quest
	CMSG_QUESTUPDATE_USE_ITEM		= 69,	/*����ʹ����Ʒ*/	//questupdate_use_item
	CMSG_QUESTHELP_QUERY_BOOK		= 70,	/*��ѯ��������*/	//questhelp_query_book
	SMSG_QUESTHELP_BOOK_QUEST		= 71,	/*�·��ɽ���������*/	//questhelp_book_quest
	SMSG_USE_GAMEOBJECT_ACTION		= 72,	/*���ʹ����Ϸ�����Ժ�Ķ���*/	//use_gameobject_action
	CMSG_SET_ATTACK_MODE		= 73,	/*���ù���ģʽ*/	//set_attack_mode
	MSG_SELECT_TARGET		= 74,	/*ѡ��Ŀ��*/	//select_target
	SMSG_COMBAT_STATE_UPDATE		= 75,	/*����ս��*/	//combat_state_update
	SMSG_EXP_UPDATE		= 76,	/*�������*/	//exp_update
	MSG_SPELL_START		= 77,	/*�ͻ����ͷż���*/	//spell_start
	MSG_SPELL_STOP		= 78,	/*ʩ��ֹͣ*/	//spell_stop
	MSG_JUMP		= 79,	/*��*/	//jump
	CMSG_RESURRECTION		= 80,	/*����*/	//resurrection
	MSG_TRADE_REQUEST		= 81,	/*���׷�������*/	//trade_request
	MSG_TRADE_REPLY		= 82,	/*���������*/	//trade_reply
	SMSG_TRADE_START		= 83,	/*���׿�ʼ*/	//trade_start
	MSG_TRADE_DECIDE_ITEMS		= 84,	/*����ȷ����Ʒ*/	//trade_decide_items
	SMSG_TRADE_FINISH		= 85,	/*�������*/	//trade_finish
	MSG_TRADE_CANCEL		= 86,	/*����ȡ��*/	//trade_cancel
	MSG_TRADE_READY		= 87,	/*����׼����*/	//trade_ready
	SMSG_CHAT_UNIT_TALK		= 88,	/*���ｲ��*/	//chat_unit_talk
	CMSG_CHAT_NEAR		= 89,	/*�ͽ�����*/	//chat_near
	CMSG_CHAT_WHISPER		= 90,	/*˽��*/	//chat_whisper
	MSG_CHAT_FACTION		= 91,	/*��Ӫ����*/	//chat_faction
	MSG_CHAT_WORLD		= 92,	/*����*/	//chat_world
	MSG_CHAT_HORN		= 93,	/*����*/	//chat_horn
	MSG_CHAT_NOTICE		= 94,	/*����*/	//chat_notice
	CMSG_QUERY_PLAYER_INFO		= 95,	/*��ѯ�����Ϣ*/	//query_player_info
	SMSG_QUERY_RESULT_UPDATE_OBJECT		= 96,	/*��ѯ��Ϣ�������*/	//query_result_update_object
	CMSG_RECEIVE_GIFT_PACKS		= 97,	/*��ȡ���*/	//receive_gift_packs
	SMSG_MAP_UPDATE_OBJECT		= 98,	/*��ͼ�������*/	//map_update_object
	SMSG_FIGHTING_INFO_UPDATE_OBJECT		= 99,	/*ս����Ϣbinlog*/	//fighting_info_update_object
	SMSG_FIGHTING_INFO_UPDATE_OBJECT_2		= 100,	/*ս����Ϣbinlog*/	//fighting_info_update_object_2
	CMSG_INSTANCE_ENTER		= 101,	/*���븱��*/	//instance_enter
	CMSG_INSTANCE_NEXT_STATE		= 102,	/*�����˷��͸���������һ�׶�ָ��*/	//instance_next_state
	CMSG_INSTANCE_EXIT		= 103,	/*�����˳�*/	//instance_exit
	CMSG_LIMIT_ACTIVITY_RECEIVE		= 104,	/*��ʱ���ȡ*/	//limit_activity_receive
	SMSG_KILL_MAN		= 105,	/*ɱ����~~��������*/	//kill_man
	SMSG_PLAYER_UPGRADE		= 106,	/*�������*/	//player_upgrade
	CMSG_WAREHOUSE_SAVE_MONEY		= 107,	/*�ֿ��Ǯ*/	//warehouse_save_money
	CMSG_WAREHOUSE_TAKE_MONEY		= 108,	/*�ֿ�ȡǮ*/	//warehouse_take_money
	CMSG_USE_GOLD_OPT		= 109,	/*ʹ��Ԫ������ĳ��*/	//use_gold_opt
	CMSG_USE_SILVER_OPT		= 110,	/*ʹ��ͭǮ����ĳ��*/	//use_silver_opt
	SMSG_GM_RIGHTFLOAT		= 111,	/*��̨����*/	//gm_rightfloat
	SMSG_DEL_GM_RIGHTFLOAT		= 112,	/*ɾ��ĳ����̨����*/	//del_gm_rightfloat
	MSG_SYNC_MSTIME_APP		= 113,	/*Ӧ�÷�ͬ��ʱ��*/	//sync_mstime_app
	CMSG_OPEN_WINDOW		= 114,	/*��Ҵ�ĳ������*/	//open_window
	CMSG_PLAYER_GAG		= 115,	/*���Բ���*/	//player_gag
	CMSG_PLAYER_KICKING		= 116,	/*���˲���*/	//player_kicking
	SMSG_MERGE_SERVER_MSG		= 117,	/*�Ϸ�֪ͨ*/	//merge_server_msg
	CMSG_RANK_LIST_QUERY		= 118,	/*��ȡ������Ϣ*/	//rank_list_query
	SMSG_RANK_LIST_QUERY_RESULT		= 119,	/*�ͻ��˻�ȡ���а񷵻ؽ��*/	//rank_list_query_result
	CMSG_CLIENT_UPDATE_SCENED		= 120,	/*�ͻ����ȸ�����ģ����ȡuint*/	//client_update_scened
	SMSG_NUM_LUA		= 121,	/*��ֵ��*/	//num_lua
	CMSG_LOOT_SELECT		= 122,	/*ս��Ʒʰȡ*/	//loot_select
	CMSG_GOBACK_TO_GAME_SERVER		= 123,	/*֪ͨ��¼������Ҵ�����Ϸ��*/	//goback_to_game_server
	CMSG_WORLD_WAR_CS_PLAYER_INFO		= 124,	/*�ͻ��˰ѱ�����Ա���ݴ���������*/	//world_war_CS_player_info
	SMSG_JOIN_OR_LEAVE_SERVER		= 125,	/*��Ҽ�������뿪ĳ������*/	//join_or_leave_server
	MSG_WORLD_WAR_SC_PLAYER_INFO		= 126,	/*�ͻ�����������Ա����*/	//world_war_SC_player_info
	MSG_CLIENTSUBSCRIPTION		= 127,	/*�ͻ��˶�����Ϣ*/	//clientSubscription
	SMSG_LUA_SCRIPT		= 128,	/*������·�lua�ű�*/	//lua_script
	CMSG_CHAR_UPDATE_INFO		= 129,	/*��ɫ������Ϣ*/	//char_update_info
	SMSG_NOTICE_WATCHER_MAP_INFO		= 130,	/*֪ͨ�ͻ��˹۲��ߵ��ӽ�*/	//notice_watcher_map_info
	CMSG_MODIFY_WATCH		= 131,	/*�ͻ��˶��Ķ�����Ϣ*/	//modify_watch
	CMSG_KUAFU_CHUANSONG		= 132,	/*�������*/	//kuafu_chuansong
	CMSG_SHOW_SUIT		= 133,	/*��ʾ��ǰװ��*/	//show_suit
	CMSG_SHOW_POSITION		= 134,	/*��ʾ��ǰ����*/	//show_position
	CMSG_GOLD_RESPAWN		= 135,	/*Ԫ������*/	//gold_respawn
	SMSG_FIELD_DEATH_COOLDOWN		= 136,	/*Ұ����������ʱ*/	//field_death_cooldown
	CMSG_MALL_BUY		= 137,	/*�̳ǹ���*/	//mall_buy
	CMSG_STRENGTH		= 139,	/*ǿ��*/	//strength
	SMSG_STRENGTH_SUCCESS		= 140,	/*ǿ���ɹ�*/	//strength_success
	CMSG_FORCEINTO		= 141,	/*ǿ�ƽ���*/	//forceInto
	CMSG_CREATE_FACTION		= 142,	/*��������*/	//create_faction
	CMSG_FACTION_UPGRADE		= 143,	/*��������*/	//faction_upgrade
	CMSG_FACTION_JOIN		= 144,	/*����������*/	//faction_join
	CMSG_RAISE_BASE_SPELL		= 145,	/*������������*/	//raise_base_spell
	CMSG_UPGRADE_ANGER_SPELL		= 146,	/*�������׷�ŭ����*/	//upgrade_anger_spell
	CMSG_RAISE_MOUNT		= 147,	/*������������*/	//raise_mount
	CMSG_UPGRADE_MOUNT		= 148,	/*������������*/	//upgrade_mount
	CMSG_UPGRADE_MOUNT_ONE_STEP		= 149,	/*����һ����������*/	//upgrade_mount_one_step
	CMSG_ILLUSION_MOUNT_ACTIVE		= 150,	/*��������û�����*/	//illusion_mount_active
	CMSG_ILLUSION_MOUNT		= 151,	/*����û�����*/	//illusion_mount
	CMSG_RIDE_MOUNT		= 152,	/*�������*/	//ride_mount
	SMSG_GRID_UNIT_JUMP		= 153,	/*grid�е�unit��Ծ*/	//grid_unit_jump
	CMSG_GEM		= 154,	/*��ʯ*/	//gem
	CMSG_CHANGE_BATTLE_MODE		= 155,	/*�����л�ģʽ*/	//change_battle_mode
	SMSG_PEACE_MODE_CD		= 156,	/*��ƽģʽCD*/	//peace_mode_cd
	CMSG_DIVINE_ACTIVE		= 157,	/*�������*/	//divine_active
	CMSG_DIVINE_UPLEV		= 158,	/*�������*/	//divine_uplev
	CMSG_DIVINE_SWITCH		= 159,	/*�л����*/	//divine_switch
	CMSG_JUMP_START		= 160,	/*������Ծ*/	//jump_start
	CMSG_ENTER_VIP_INSTANCE		= 161,	/*�������vip����*/	//enter_vip_instance
	CMSG_SWEEP_VIP_INSTANCE		= 162,	/*����ɨ��vip����*/	//sweep_vip_instance
	CMSG_HANG_UP		= 163,	/*���йһ�*/	//hang_up
	CMSG_HANG_UP_SETTING		= 164,	/*���йһ�����*/	//hang_up_setting
	CMSG_ENTER_TRIAL_INSTANCE		= 165,	/*�����������������*/	//enter_trial_instance
	CMSG_SWEEP_TRIAL_INSTANCE		= 166,	/*ɨ������������*/	//sweep_trial_instance
	CMSG_RESET_TRIAL_INSTANCE		= 167,	/*����������*/	//reset_trial_instance
	SMSG_SWEEP_INSTANCE_REWARD		= 168,	/*ɨ����������*/	//sweep_instance_reward
	CMSG_REENTER_INSTANCE		= 169,	/*�ؽ�����*/	//reenter_instance
	SMSG_MERRY_GO_ROUND		= 170,	/*�������Ϣ*/	//merry_go_round
	CMSG_SOCIAL_ADD_FRIEND		= 171,	/*��Ӻ���*/	//social_add_friend
	CMSG_SOCIAL_SUREADD_FRIEND		= 172,	/*ͬ����Ӻ���*/	//social_sureadd_friend
	CMSG_SOCIAL_GIFT_FRIEND		= 173,	/*��������*/	//social_gift_friend
	CMSG_SOCIAL_RECOMMEND_FRIEND		= 174,	/*�Ƽ������б�*/	//social_recommend_friend
	SMSG_SOCIAL_GET_RECOMMEND_FRIEND		= 175,	/*�Ƽ������б�*/	//social_get_recommend_friend
	CMSG_SOCIAL_REVENGE_ENEMY		= 176,	/*����*/	//social_revenge_enemy
	CMSG_SOCIAL_DEL_FRIEND		= 177,	/*ɾ������*/	//social_del_friend
	CMSG_TELEPORT_MAIN_CITY		= 178,	/*�س�*/	//teleport_main_city
	CMSG_CHAT_BY_CHANNEL		= 179,	/*��ͬƵ������*/	//chat_by_channel
	SMSG_SEND_CHAT		= 180,	/*��������*/	//send_chat
	CMSG_SOCIAL_CLEAR_APPLY		= 181,	/*��������б�*/	//social_clear_apply
	CMSG_MSG_DECLINE		= 182,	/*���þܾ�������Ϣ*/	//msg_decline
	SMSG_FACTION_GET_LIST_RESULT		= 183,	/*�����б�*/	//faction_get_list_result
	CMSG_FACTION_GETLIST		= 184,	/*��ȡ�����б�*/	//faction_getlist
	CMSG_FACTION_MANAGER		= 185,	/*���ɹ���*/	//faction_manager
	CMSG_FACTION_MEMBER_OPERATE		= 186,	/*���ɳ�Ա����*/	//faction_member_operate
	CMSG_FACTION_FAST_JOIN		= 187,	/*���ټ������*/	//faction_fast_join
	CMSG_SOCIAL_ADD_FRIEND_BYNAME		= 188,	/*ͨ��������Ӻ���*/	//social_add_friend_byname
	CMSG_READ_MAIL		= 190,	/*���ʼ�*/	//read_mail
	CMSG_PICK_MAIL		= 191,	/*��ȡ�ʼ�*/	//pick_mail
	CMSG_REMOVE_MAIL		= 192,	/*ɾ���ʼ�*/	//remove_mail
	CMSG_PICK_MAIL_ONE_STEP		= 193,	/*һ����ȡ�ʼ�*/	//pick_mail_one_step
	CMSG_REMOVE_MAIL_ONE_STEP		= 194,	/*һ��ɾ���ʼ�*/	//remove_mail_one_step
	CMSG_BLOCK_CHAT		= 195,	/*����ĳ��*/	//block_chat
	CMSG_CANCEL_BLOCK_CHAT		= 196,	/*ȡ������*/	//cancel_block_chat
	CMSG_USE_BROADCAST_GAMEOBJECT		= 200,	/*ʹ����Ҫ�㲥����Ϸ����*/	//use_broadcast_gameobject
	CMSG_WORLD_BOSS_ENROLL		= 201,	/*����BOSS����*/	//world_boss_enroll
	CMSG_WORLD_BOSS_FIGHT		= 202,	/*����BOSS��ս*/	//world_boss_fight
	CMSG_CHANGE_LINE		= 203,	/*����*/	//change_line
	CMSG_ROLL_WORLD_BOSS_TREASURE		= 204,	/*roll����BOSS����*/	//roll_world_boss_treasure
	SMSG_ROLL_RESULT		= 205,	/*roll����*/	//roll_result
	SMSG_BOSS_RANK		= 206,	/*��ǰBOSS�˺�����*/	//boss_rank
	CMSG_RANK_ADD_LIKE		= 207,	/*���а����*/	//rank_add_like
	SMSG_RANK_ADD_LIKE_RESULT		= 208,	/*���а���޽��*/	//rank_add_like_result
	CMSG_RES_INSTANCE_ENTER		= 210,	/*������Դ����*/	//res_instance_enter
	CMSG_RES_INSTANCE_SWEEP		= 211,	/*ɨ����Դ����*/	//res_instance_sweep
	CMSG_SHOW_MAP_LINE		= 212,	/*�鿴����ͼ�ķ��ߺ�*/	//show_map_line
	SMSG_SEND_MAP_LINE		= 213,	/*���ر���ͼ�ķ��ߺ���Ϣ*/	//send_map_line
	SMSG_ITEM_NOTICE		= 214,	/*��ý�����ʾ*/	//item_notice
	CMSG_TELEPORT_MAP		= 216,	/*���͵�ĳ�������ͼ*/	//teleport_map
	CMSG_TELEPORT_FIELD_BOSS		= 217,	/*���͵�Ұ��boss�Ա�*/	//teleport_field_boss
	CMSG_GET_ACTIVITY_REWARD		= 218,	/*��Ծ�Ƚ���*/	//get_activity_reward
	CMSG_GET_ACHIEVE_REWARD		= 220,	/*�ɾͽ���*/	//get_achieve_reward
	CMSG_GET_ACHIEVE_ALL_REWARD		= 221,	/*�ܳɾͽ���*/	//get_achieve_all_reward
	CMSG_SET_TITLE		= 222,	/*װ���ƺ�*/	//set_title
	CMSG_INIT_TITLE		= 223,	/*��ʼ���ƺ�*/	//init_title
	CMSG_WELFARE_SHOUCHONG_REWARD		= 224,	/*��ȡ�׳佱��*/	//welfare_shouchong_reward
	CMSG_WELFARE_CHECKIN		= 225,	/*ÿ��ǩ������*/	//welfare_checkin
	CMSG_WELFARE_CHECKIN_ALL		= 226,	/*�ۻ�ǩ������*/	//welfare_checkin_all
	CMSG_WELFARE_CHECKIN_GETBACK		= 227,	/*��ǩ����*/	//welfare_checkin_getback
	CMSG_WELFARE_LEVEL		= 228,	/*�ȼ�����*/	//welfare_level
	CMSG_WELFARE_ACTIVE_GETBACK		= 229,	/*��һؽ���*/	//welfare_active_getback
	CMSG_PICK_QUEST_REWARD		= 230,	/*��ȡ������*/	//pick_quest_reward
	CMSG_TALK_WITH_NPC		= 231,	/*��npc�Ի�*/	//talk_with_npc
	CMSG_USE_VIRTUAL_ITEM		= 232,	/*ʹ��������Ʒ*/	//use_virtual_item
	CMSG_PICK_QUEST_CHAPTER_REWARD		= 233,	/*��ȡ�����½ڽ���*/	//pick_quest_chapter_reward
	CMSG_KUAFU_3V3_MATCH		= 234,	/*3v3���ƥ��*/	//kuafu_3v3_match
	SMSG_KUAFU_MATCH_START		= 235,	/*�����ʼƥ��*/	//kuafu_match_start
	CMSG_KUAFU_3V3_BUYTIMES		= 236,	/*3v3�������*/	//kuafu_3v3_buytimes
	CMSG_KUAFU_3V3_DAYREWARD		= 237,	/*3v3ÿ�ջ�Ծ����*/	//kuafu_3v3_dayreward
	CMSG_KUAFU_3V3_GETRANLIST		= 238,	/*����3v3���а�*/	//kuafu_3v3_getranlist
	SMSG_KUAFU_3V3_RANLIST		= 239,	/*3v3���а����б�*/	//kuafu_3v3_ranlist
	CMSG_WELFARE_GETALLLIST_GETBACK		= 240,	/*�������н����б�*/	//welfare_getalllist_getback
	SMSG_WELFARE_REWARDLIST_GETBACK		= 241,	/*�����б�*/	//welfare_rewardlist_getback
	CMSG_WELFARE_GETALL_GETBACK		= 242,	/*һ����ȡ���и���*/	//welfare_getall_getback
	CMSG_KUAFU_3V3_GETMYRANK		= 248,	/*����3v3���а��Լ�������*/	//kuafu_3v3_getmyrank
	SMSG_KUAFU_3V3_MYRANK		= 249,	/*3v3���а��Լ������ν��*/	//kuafu_3v3_myrank
	SMSG_KUAFU_3V3_KILL_DETAIL		= 250,	/*��ɱ����*/	//kuafu_3v3_kill_detail
	SMSG_KUAFU_3V3_WAIT_INFO		= 251,	/*���ƥ��ȴ�����*/	//kuafu_3v3_wait_info
	MSG_KUAFU_3V3_CANCEL_MATCH		= 252,	/*ȡ��ƥ��*/	//kuafu_3v3_cancel_match
	CMSG_KUAFU_3V3_MATCH_OPER		= 253,	/*ƥ�䵽��&���ܻ��߾ܾ�*/	//kuafu_3v3_match_oper
	SMSG_KUAFU_3V3_DECLINE_MATCH		= 254,	/*�ܾ�����*/	//kuafu_3v3_decline_match
	CMSG_KUAFU_XIANFU_MATCH		= 255,	/*�ɸ��ᱦ���ƥ��*/	//kuafu_xianfu_match
	SMSG_KUAFU_MATCH_WAIT		= 256,	/*�������ƥ��ȴ�*/	//kuafu_match_wait
	SMSG_KUAFU_XIANFU_MINIMAP_INFO		= 257,	/*�ɸ��ᱦС��ͼ��Ϣ*/	//kuafu_xianfu_minimap_info
	CMSG_BUY_XIANFU_ITEM		= 258,	/*�����ɸ�����ȯ*/	//buy_xianfu_item
	CMSG_XIANFU_RANDOM_RESPAWN		= 259,	/*�������*/	//xianfu_random_respawn
	CMSG_DOUJIANTAI_FIGHT		= 260,	/*����̨��ս*/	//doujiantai_fight
	CMSG_DOUJIANTAI_BUYTIME		= 261,	/*����̨�������*/	//doujiantai_buytime
	CMSG_DOUJIANTAI_CLEARCD		= 262,	/*����̨����CD*/	//doujiantai_clearcd
	CMSG_DOUJIANTAI_FIRST_REWARD		= 263,	/*����̨��ʤ����*/	//doujiantai_first_reward
	MSG_DOUJIANTAI_GET_ENEMYS_INFO		= 265,	/*����̨��ս������Ϣ*/	//doujiantai_get_enemys_info
	CMSG_DOUJIANTAI_GET_RANK		= 266,	/*����̨���а�*/	//doujiantai_get_rank
	CMSG_DOUJIANTAI_REFRESH_ENEMYS		= 270,	/*����̨ˢ�¶���*/	//doujiantai_refresh_enemys
	MSG_DOUJIANTAI_TOP3		= 271,	/*����̨����*/	//doujiantai_top3
	MSG_USE_JUMP_POINT		= 272,	/*ʹ������*/	//use_jump_point
	CMSG_BAG_ITEM_SELL		= 273,	/*������Ʒ*/	//bag_item_sell
	CMSG_BAG_ITEM_SORT		= 274,	/*������Ʒ*/	//bag_item_sort
	CMSG_SUBMIT_QUEST_DAILY2		= 280,	/*�ύ�ճ�����*/	//submit_quest_daily2
	SMSG_ATTRIBUTE_CHANGED		= 281,	/*���Ըı�*/	//attribute_changed
	SMSG_BAG_FIND_EQUIP_BETTER		= 282,	/*�����и�ǿװ��*/	//bag_find_equip_better
	SMSG_MODULE_ACTIVE		= 283,	/*ģ�����*/	//module_active
	CMSG_PICK_DAILY2_QUEST_REWARD		= 284,	/*��ȡ�ճ�������*/	//pick_daily2_quest_reward
	CMSG_FINISH_NOW_GUIDE		= 285,	/*��ɵ�ǰ����*/	//finish_now_guide
	CMSG_GET_CULTIVATION_INFO		= 286,	/*ȡ����������Ϣ*/	//get_cultivation_info
	SMSG_UPDATE_CULTIVATION_INFO		= 287,	/*������������Ϣ*/	//update_cultivation_info
	CMSG_GET_CULTIVATION_RIVALS_INFO		= 288,	/*ȡ�õ�ǰ����������������Ϣ*/	//get_cultivation_rivals_info
	SMSG_UPDATE_CULTIVATION_RIVALS_INFO_LIST		= 289,	/*����������������Ϣ*/	//update_cultivation_rivals_info_list
	CMSG_GET_CULTIVATION_REWARD		= 290,	/*��ȡ����������*/	//get_cultivation_reward
	CMSG_REFRESH_CULTIVATION_RIVALS		= 291,	/*ˢ������������*/	//refresh_cultivation_rivals
	CMSG_PLUNDER_CULTIVATION_RIVAL		= 292,	/*�Ӷ�����������*/	//plunder_cultivation_rival
	CMSG_REVENGE_CULTIVATION_RIVAL		= 293,	/*������������������*/	//revenge_cultivation_rival
	CMSG_BUY_CULTIVATION_LEFT_PLUNDER_COUNT		= 294,	/*����������ʣ����ս����*/	//buy_cultivation_left_plunder_count
	SMSG_SHOW_CULTIVATION_RESULT_LIST		= 295,	/*����������ս�����*/	//show_cultivation_result_list
	CMSG_GET_LOGIN_ACTIVITY_REWARD		= 296,	/*��ȡ��¼������*/	//get_login_activity_reward
	SMSG_CAST_SPELL_START		= 300,	/*֪ͨ�ͻ����ͷ���������*/	//cast_spell_start
	CMSG_FINISH_OPTIONAL_GUIDE_STEP		= 301,	/*��ɷ�ǿ�������Ĳ���*/	//finish_optional_guide_step
	CMSG_EXECUTE_QUEST_CMD_AFTER_ACCEPTED		= 302,	/*ִ�нӵ������Ժ������*/	//execute_quest_cmd_after_accepted
	SMSG_SHOW_UNIT_ATTRIBUTE		= 310,	/*֪ͨ�ͻ�����ʾ����*/	//show_unit_attribute
	CMSG_BACK_TO_FAMITY		= 320,	/*���ؼ���*/	//back_to_famity
	SMSG_FACTION_BOSS_SEND_RESULT		= 321,	/*���ؼ���boss���*/	//faction_boss_send_result
	CMSG_CHALLANGE_BOSS		= 322,	/*��սboss*/	//challange_boss
	CMSG_PICK_OFFLINE_REWARD		= 325,	/*��ȡ���߽���*/	//pick_offline_reward
	SMSG_OFFLINE_REWARD_RESULT		= 326,	/*���߽������*/	//offline_reward_result
	CMSG_SMELTING_EQUIP		= 327,	/*����װ��*/	//smelting_equip
	CMSG_STOREHOUSE_HAND_IN		= 328,	/*�Ͻ�װ��*/	//storehouse_hand_in
	CMSG_STOREHOUSE_EXCHANGE		= 329,	/*�һ�װ��*/	//storehouse_exchange
	CMSG_STOREHOUSE_DESTROY		= 330,	/*����װ��*/	//storehouse_destroy
	CMSG_SEND_FACTION_GIFT		= 331,	/*��������*/	//send_faction_gift
	CMSG_GET_FACTION_GIFT_EXREWARD		= 332,	/*��ȡ���⽱��*/	//get_faction_gift_exreward
	CMSG_GET_ALL_FACTION_GIFT_EXREWARD		= 333,	/*��ȡ���ж��⽱��*/	//get_all_faction_gift_exreward
	SMSG_SHOW_FACTION_GIFT_PAGE		= 334,	/*���������б�*/	//show_faction_gift_page
	SMSG_SHOW_FACTION_GIFT_INFO		= 335,	/*����������Ϣ*/	//show_faction_gift_info
	SMSG_SHOW_FACTION_GIFT_UNTHANK_PAGE		= 336,	/*����Ů��δ��л����*/	//show_faction_gift_unthank_page
	SMSG_SHOW_FACTION_GIFT_HISTORY_PAGE		= 337,	/*����Ů����ʷ��¼*/	//show_faction_gift_history_page
	CMSG_GET_FACTION_GIFT_RANK_PAGE		= 338,	/*���������������*/	//get_faction_gift_rank_page
	SMSG_SHOW_FACTION_GIFT_RANK_RESULT_LIST		= 339,	/*���ؼ�����������*/	//show_faction_gift_rank_result_list
	SMSG_SHOW_FACTION_GIFT_RANK_CHANGE		= 340,	/*���ؼ����������б仯*/	//show_faction_gift_rank_change
	SMSG_SHOW_FACTION_GIFT_RANK_INFO		= 341,	/*���ر�������������*/	//show_faction_gift_rank_info
	CMSG_DIVINE_FORGE		= 342,	/*���ǿ��*/	//divine_forge
	CMSG_DIVINE_ADVANCE		= 343,	/*�������*/	//divine_advance
	CMSG_DIVINE_SPIRIT		= 344,	/*�������*/	//divine_spirit
	CMSG_QUERY_MASS_BOSS_INFO		= 352,	/*��ѯȫ��boss��Ϣ*/	//query_mass_boss_info
	SMSG_MASS_BOSS_INFO_RET		= 353,	/*ȫ��boss��Ϣ���*/	//mass_boss_info_ret
	CMSG_QUERY_MASS_BOSS_RANK		= 354,	/*��ѯȫ��boss���а�*/	//query_mass_boss_rank
	SMSG_MASS_BOSS_RANK_RESULT		= 355,	/*ȫ��boss���н��*/	//mass_boss_rank_result
	CMSG_TRY_MASS_BOSS		= 356,	/*��սȫ��boss*/	//try_mass_boss
	CMSG_BUY_MASS_BOSS_TIMES		= 357,	/*������սȫ��boss����*/	//buy_mass_boss_times
	CMSG_GROUP_INSTANCE_MATCH		= 358,	/*��Ӹ������ƥ��*/	//group_instance_match
	CMSG_BUY_GROUP_INSTANCE_TIMES		= 359,	/*��Ӹ��������������*/	//buy_group_instance_times
	CMSG_TALISMAN_ACTIVE		= 360,	/*��������*/	//talisman_active
	CMSG_TALISMAN_LVUP		= 361,	/*����ע��*/	//talisman_lvup
	CMSG_WINGS_ACTIVE		= 362,	/*���𼤻�*/	//wings_active
	CMSG_WINGS_BLESS		= 363,	/*����ף��*/	//wings_bless
	CMSG_WINGS_RANKUP		= 364,	/*��������*/	//wings_rankup
	CMSG_WINGS_STRENGTH		= 365,	/*����ǿ��*/	//wings_strength
	CMSG_MERIDIAN_PRACTISE		= 366,	/*��������*/	//meridian_practise
	CMSG_ADD_MERIDIAN_EXP		= 367,	/*�Ӿ�����������ֵ*/	//add_meridian_exp
	CMSG_RAISE_MOUNT_LEVEL_BASE		= 368,	/*��������ȼ�*/	//raise_mount_level_base
	CMSG_ACTIVE_MOUNT		= 369,	/*��������*/	//active_mount
	SMSG_SHOW_FACTION_BOSSDEFENSE_DAMAGE_LIST		= 370,	/*����������ս�������*/	//show_faction_bossdefense_damage_list
	SMSG_SHOW_FACTION_TOWER_SWEEP_LIST		= 371,	/*�����޾�Զ��ɨ�����*/	//show_faction_tower_sweep_list
	SMSG_SEND_INSTANCE_RESULT		= 375,	/*�������*/	//send_instance_result
	CMSG_MATCH_SINGLE_PVP		= 376,	/*ƥ�䵥��pvp*/	//match_single_pvp
	CMSG_BUY_MATCH_SINGLE_PVP_TIMES		= 377,	/*������pvp����*/	//buy_match_single_pvp_times
	CMSG_PICK_MATCH_SINGLE_PVP_EXTRA_REWARD		= 378,	/*��ȡ����pvp���⽱��*/	//pick_match_single_pvp_extra_reward
	CMSG_EQUIPDEVELOP_OPERATE		= 380,	/*װ�����ɲ���*/	//equipdevelop_operate
	CMSG_ACTIVE_APPEARANCE		= 381,	/*�������*/	//active_appearance
	CMSG_EQUIP_APPEARANCE		= 382,	/*װ�����*/	//equip_appearance
	CMSG_CANCEL_EQUIP_APPEARANCE		= 383,	/*ȡ��װ�����*/	//cancel_equip_appearance
	CMSG_RENAME		= 384,	/*����*/	//rename
	CMSG_UNLOCK_TITLE		= 385,	/*���߽����ƺ�*/	//unlock_title
	CMSG_SOCIAL_BUY_REVENGE_TIMES		= 386,	/*���򸴳����*/	//social_buy_revenge_times
	CMSG_ENTER_RISK_INSTANCE		= 387,	/*�����������ð�ո���*/	//enter_risk_instance
	CMSG_SOCIAL_REMOVE_ENEMY		= 388,	/*ɾ������*/	//social_remove_enemy
	CMSG_GET_PLAYER_OVERVIEW		= 389,	/*�鿴�������*/	//get_player_overview
	SMSG_SHOW_PLAYER_OVERVIEW		= 390,	/*�����������*/	//show_player_overview
	CMSG_SEND_FACTION_INVITE		= 391,	/*����������*/	//send_faction_invite
	SMSG_SHOW_FACTION_INVITE		= 392,	/*��ʾ����*/	//show_faction_invite
	CMSG_BUY_VIPGIFT		= 393,	/*����vip���*/	//buy_vipgift
	CMSG_ACTIVITY_OPT_BUY_DAILYGIFT		= 394,	/*����ÿ�����*/	//activity_opt_buy_dailygift
	CMSG_DRAW_LOTTERY		= 395,	/*�齱*/	//draw_lottery
	CMSG_ACTIVITY_OPT_GET_RANK_PROCESS_REWARD		= 396,	/*��ȡ��������н��Ƚ���*/	//activity_opt_get_rank_process_reward
	CMSG_ACTIVITY_OPT_GET_RANK_LIST		= 397,	/*��ȡ��������а�*/	//activity_opt_get_rank_list
	SMSG_ACTIVITY_OPT_SHOW_RANK_LIST		= 398,	/*���ػ�������а�*/	//activity_opt_show_rank_list
	CMSG_ACTIVITY_OPT_BUY_LIMITGIFT		= 399,	/*�����޶����*/	//activity_opt_buy_limitgift
	CMSG_WELFARE_GET_RECHARGE_REWARD		= 400,	/*��ȡ�ۼƳ�ֵ����*/	//welfare_get_recharge_reward
	CMSG_WELFARE_GET_CONSUME_REWARD		= 401,	/*��ȡ�ۼ����ѽ���*/	//welfare_get_consume_reward
	CMSG_WELFARE_GET_SEVENDAY_REWARD		= 402,	/*��ȡ���մ�����*/	//welfare_get_sevenday_reward
	SMSG_SEND_SERVER_OPEN_TIME		= 403,	/*����������ʱ��*/	//send_server_open_time
	CMSG_RISK_GET_RANK		= 404,	/*��������ð�����а�*/	//risk_get_rank
	SMSG_RISK_GET_RANK_RESULT		= 405,	/*����ð�����а���Ϣ */	//risk_get_rank_result
	CMSG_SET_ORIENT		= 406,	/*���ó���*/	//set_orient
	CMSG_USE_MONEYTREE		= 407,	/*ҡ��ҡǮ��*/	//use_moneytree
	CMSG_GET_MONEYTREE_GIFT		= 408,	/*��ȡҡǮ�����*/	//get_moneytree_gift
	CMSG_SET_WORLD_RISK_LAST_ID		= 409,	/*�޸Ļþ�������id*/	//set_world_risk_last_id
	CMSG_ENTER_PRIVATE_BOSS		= 410,	/*�������Boss*/	//enter_private_boss
	CMSG_RAISE_BASE_SPELL_ALL		= 411,	/*��������ȫ������*/	//raise_base_spell_all
	CMSG_USE_RESTORE_POTION		= 413,	/*ʹ�ûظ�ҩ*/	//use_restore_potion
	NUM_MSG_TYPES
};

CPPAPI const char* GetOpcodeName(uint16 opt);

#if defined( __GNUC__ )
#	pragma pack(1)
#else
#	pragma pack(push,1)
#endif

/*����ṹ��*/

typedef struct point_t{
	float		pos_x;		/*����X*/

	float		pos_y;		/*����Y*/

}point;

/*���͵ص�ṹ��*/

typedef struct taxi_menu_info_t{
	int32		id;		/**/

	char		taxi_text[50];		/*���͵ص�����*/

	uint32		map_id;		/*��ͼID*/

	uint16		pos_x;		/*����X*/

	uint16		pos_y;		/*����Y*/

}taxi_menu_info;

/*��ҽ�ɫ����ѡ����Ϣ*/

typedef struct char_create_info_t{
	char		name[50];		/*����*/

	uint8		faction;		/*��Ӫ*/

	uint8		gender;		/*�Ա�*/

	uint16		level;		/*�ȼ�*/

	char		guid[50];		/**/

	uint32		head_id;		/*ͷ��*/

	uint32		hair_id;		/*����ID*/

	uint8		race;		/*���壬������Ů������Щ*/

	char		inviteGuid[50];		/*����İ���id*/

	char		faction_name[50];		/*�����İ�������*/

	uint8		icon;		/*�����İ��ɱ�־*/

}char_create_info;

/*����˵�*/

typedef struct quest_option_t{
	uint32		quest_id;		/*����id*/

	uint32		quest_icon;		/*ͼ��*/

	uint16		quest_level;		/*����ȼ�*/

	char		quest_title[50];		/*�������*/

	uint32		flags;		/*��ʶ*/

}quest_option;

/*�ɽ�������Ϣ*/

typedef struct quest_canaccept_info_t{
	uint32		quest_id;		/*����ID*/

	uint8		quest_type;		/*�������*/

	char		title[50];		/*����*/

	uint32		npc_id;		/*��������NPCģ��id*/

	uint32		quest_level;		/*����ȼ�*/

}quest_canaccept_info;

/*����ѡ��ṹ��*/

typedef struct gossip_menu_option_info_t{
	int32		id;		/*id*/

	int32		option_icon;		/*ѡ��iconͼ��*/

	char		option_title[200];		/*ѡ���ı�*/

}gossip_menu_option_info;

/*��Ʒ��ȴ*/

typedef struct item_cooldown_info_t{
	uint32		item;		/*��Ʒ����*/

	uint32		cooldown;		/*��ȴʱ��*/

}item_cooldown_info;

/*����״̬*/

typedef struct quest_status_t{
	uint16		quest_id;		/*����ID*/

	uint8		status;		/*����״̬*/

}quest_status;

/*���߽�����Ϣ*/

typedef struct item_reward_info_t{
	uint16		item_id;		/*����id*/

	uint32		num;		/*��������*/

}item_reward_info;

/*������Ϣ*/

typedef struct social_friend_info_t{
	char		guid[50];		/*����guid*/

	char		name[50];		/*����*/

	char		faction[50];		/*����*/

	uint16		level;		/*�ȼ�*/

	uint16		icon;		/*ͷ��*/

	uint16		vip;		/*ͷ��*/

}social_friend_info;

/*������Ϣ*/

typedef struct faction_info_t{
	char		faction_guid[50];		/*����guid*/

	char		faction_name[50];		/*����*/

	char		faction_bz[50];		/*��������*/

	char		faction_gg[108];		/*����*/

	uint16		level;		/*�ȼ�*/

	uint8		icon;		/*ͷ��*/

	uint16		player_count;		/*��������*/

	uint16		minlev;		/*�ȼ�����*/

}faction_info;

/*������Ϣ*/

typedef struct rank_info_t{
	char		name[50];		/*����*/

	float		value;		/*�˺��ٷֱ�*/

}rank_info;

/*����ṹ��*/

typedef struct line_info_t{
	uint16		lineNo;		/*���ߺ�*/

	uint8		rate;		/*��ұ���*/

}line_info;

/*�ȴ���Ϣ*/

typedef struct wait_info_t{
	char		name[50];		/*����*/

	int8		state;		/*״̬*/

}wait_info;

/*������������Ϣ*/

typedef struct cultivation_rivals_info_t{
	uint32		index;		/*���*/

	char		name[50];		/*����*/

	uint32		level;		/*�ȼ�*/

	uint32		weapon;		/*����*/

	uint32		avatar;		/*���*/

	uint32		divine;		/*���*/

	uint32		force;		/*ս��*/

	uint32		chest;		/*����*/

	uint32		gender;		/*�Ա�*/

}cultivation_rivals_info;

/*����������Ϣ*/

typedef struct faction_gift_info_t{
	uint32		rank;		/*����*/

	uint32		id;		/*id*/

	uint32		point;		/*����ֵ*/

	uint32		thank;		/*��л��ʶ*/

	uint32		reply;		/*Ů���ظ���ʶ*/

	uint32		time;		/*ʱ��*/

	uint32		count_id;		/*count_id*/

	char		guid[50];		/*������guid*/

	char		msg[50];		/*����������*/

	char		item_list[150];		/*���͵�����Ϣ*/

	char		reply_list[100];		/*�ظ���Ϣ*/

}faction_gift_info;

/*��������������Ϣ*/

typedef struct faction_gift_rank_info_t{
	uint32		rank;		/*����*/

	uint32		point;		/*����ֵ*/

	char		queen_name[50];		/*Ů������*/

	char		faction_name[50];		/*��������*/

	char		guard_name[50];		/*��ʿ����*/

	uint32		faction_flag;		/*��������*/

	uint32		queen_vip;		/*Ů��vip�ȼ�*/

	uint32		guard_vip;		/*��ʿvip�ȼ�*/

}faction_gift_rank_info;

/*ȫ��boss��Ϣ*/

typedef struct mass_boss_info_t{
	uint8		id;		/*ȫ��boss���*/

	uint8		state;		/*ȫ��boss״̬*/

	uint32		time;		/*ȫ��bossˢ��ʱ��*/

	uint8		percent;		/*bossѪ��*/

	uint16		count;		/*��սboss����*/

}mass_boss_info;

/*ȫ��boss����*/

typedef struct mass_boss_rank_info_t{
	char		name[50];		/*����*/

	double		dam;		/*�˺�*/

}mass_boss_rank_info;

/*װ����Ϣ*/

typedef struct equip_info_t{
	char		equip[50];		/*װ����Ϣ*/

	uint32		strength_lv;		/*ǿ��*/

	uint32		refine_rank;		/*�����׼�*/

	uint32		refine_star;		/*�����Ǽ�*/

	uint32		gem1_lv;		/*��ʯ1�ȼ�*/

	uint32		gem2_lv;		/*��ʯ1�ȼ�*/

	uint32		gem3_lv;		/*��ʯ1�ȼ�*/

}equip_info;

/*���������*/

typedef struct act_rank_info_t{
	char		name[50];		/*����*/

	uint32		value;		/*��ֵ*/

}act_rank_info;


#if defined( __GNUC__ )
#	pragma pack()
#else
#	pragma pack(pop)
#endif

/*TEA_SVRCORE_API int   pack_update_object(packet**dst,list_t *block_list);*/

///////////////////////////////////////////////////////////////////////////////
/*��Ч����*/
TEA_SVRCORE_API	int   pack_null_action (packet**dst );
TEA_SVRCORE_API  int   unpack_null_action (packet *src );
/*��������״̬*/
TEA_SVRCORE_API	int   pack_ping_pong (packet**dst );
TEA_SVRCORE_API  int   unpack_ping_pong (packet *src );
/*�ߵ����ߵ�׼��ǿ�Ƶ�½*/
TEA_SVRCORE_API	int   pack_forced_into (packet**dst );
TEA_SVRCORE_API  int   unpack_forced_into (packet *src );
/*���Session����*/
TEA_SVRCORE_API	int   pack_get_session (packet**dst ,char const*sessionkey,char const*account,char const*version);
TEA_SVRCORE_API  int   unpack_get_session (packet *src ,char **sessionkey,char **account,char **version);
/*���ط����ݰ�·�ɲ���*/
TEA_SVRCORE_API	int   pack_route_trace (packet**dst ,char const*val);
TEA_SVRCORE_API  int   unpack_route_trace (packet *src ,char **val);
/*��¼�ͻ�����־*/
TEA_SVRCORE_API	int   pack_write_client_log (packet**dst ,uint32 type,char const*uid,char const*guid,char const*log);
TEA_SVRCORE_API  int   unpack_write_client_log (packet *src ,uint32 *type,char **uid,char **guid,char **log);
/*����ʧ��*/
TEA_SVRCORE_API	int   pack_operation_failed (packet**dst ,uint16 type,uint16 reason,char const*data);
TEA_SVRCORE_API  int   unpack_operation_failed (packet *src ,uint16 *type,uint16 *reason,char **data);
/*ͬ��ʱ��*/
TEA_SVRCORE_API	int   pack_sync_mstime (packet**dst ,uint32 mstime_now,uint32 time_now,uint32 open_time);
TEA_SVRCORE_API  int   unpack_sync_mstime (packet *src ,uint32 *mstime_now,uint32 *time_now,uint32 *open_time);
/*�������*/
TEA_SVRCORE_API	int   pack_ud_object (packet**dst );
TEA_SVRCORE_API  int   unpack_ud_object (packet *src );
/*������¿���Э��*/
TEA_SVRCORE_API	int   pack_ud_control (packet**dst );
TEA_SVRCORE_API  int   unpack_ud_control (packet *src );
/*������¿���Э����*/
TEA_SVRCORE_API	int   pack_ud_control_result (packet**dst );
TEA_SVRCORE_API  int   unpack_ud_control_result (packet *src );
/*GRID�Ķ������*/
TEA_SVRCORE_API	int   pack_grid_ud_object (packet**dst );
TEA_SVRCORE_API  int   unpack_grid_ud_object (packet *src );
/*GRID�Ķ������*/
TEA_SVRCORE_API	int   pack_grid_ud_object_2 (packet**dst );
TEA_SVRCORE_API  int   unpack_grid_ud_object_2 (packet *src );
/*���߿ͻ��ˣ�Ŀǰ�Լ����ڵ�¼���еĵڼ�λ*/
TEA_SVRCORE_API	int   pack_login_queue_index (packet**dst ,uint32 index);
TEA_SVRCORE_API  int   unpack_login_queue_index (packet *src ,uint32 *index);
/*����ԭ��*/
TEA_SVRCORE_API	int   pack_kicking_type (packet**dst ,uint32 k_type);
TEA_SVRCORE_API  int   unpack_kicking_type (packet *src ,uint32 *k_type);
/*��ȡ��ɫ�б�*/
TEA_SVRCORE_API	int   pack_get_chars_list (packet**dst );
TEA_SVRCORE_API  int   unpack_get_chars_list (packet *src );
/*��ɫ�б�*/
TEA_SVRCORE_API	int   pack_chars_list (packet**dst , char_create_info *list , uint16 len_1,char const*faction_name,char const*queen_name,uint8 icon);
TEA_SVRCORE_API  int   unpack_chars_list (packet *src , char_create_info **list , uint16 *len_1,char **faction_name,char **queen_name,uint8 *icon);
/*��������Ƿ����ʹ��*/
TEA_SVRCORE_API	int   pack_check_name (packet**dst ,char const*name);
TEA_SVRCORE_API  int   unpack_check_name (packet *src ,char **name);
/*������ֽ��*/
TEA_SVRCORE_API	int   pack_check_name_result (packet**dst ,uint8 result);
TEA_SVRCORE_API  int   unpack_check_name_result (packet *src ,uint8 *result);
/*������ɫ*/
TEA_SVRCORE_API	int   pack_char_create (packet**dst , char_create_info *info);
TEA_SVRCORE_API  int   unpack_char_create (packet *src , char_create_info **info);
/*��ɫ�������*/
TEA_SVRCORE_API	int   pack_char_create_result (packet**dst ,uint8 result);
TEA_SVRCORE_API  int   unpack_char_create_result (packet *src ,uint8 *result);
/*ɾ����ɫ*/
TEA_SVRCORE_API	int   pack_delete_char (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_delete_char (packet *src ,uint32 *id);
/*��ɫɾ�����*/
TEA_SVRCORE_API	int   pack_delete_char_result (packet**dst ,uint8 result);
TEA_SVRCORE_API  int   unpack_delete_char_result (packet *src ,uint8 *result);
/*��ҵ�¼*/
TEA_SVRCORE_API	int   pack_player_login (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_player_login (packet *src ,char **guid);
/*����˳�*/
TEA_SVRCORE_API	int   pack_player_logout (packet**dst );
TEA_SVRCORE_API  int   unpack_player_logout (packet *src );
/*��ʱ�˺�ת����*/
TEA_SVRCORE_API	int   pack_regularise_account (packet**dst ,char const*uid);
TEA_SVRCORE_API  int   unpack_regularise_account (packet *src ,char **uid);
/*��ɫ������Ϣ*/
TEA_SVRCORE_API	int   pack_char_remotestore (packet**dst ,uint32 key,uint32 value);
TEA_SVRCORE_API  int   unpack_char_remotestore (packet *src ,uint32 *key,uint32 *value);
/*��ɫ������Ϣ*/
TEA_SVRCORE_API	int   pack_char_remotestore_str (packet**dst ,uint32 key,char const*value);
TEA_SVRCORE_API  int   unpack_char_remotestore_str (packet *src ,uint32 *key,char **value);
/*���ͣ������C->S��mapid��������ɴ��͵�ID*/
TEA_SVRCORE_API	int   pack_teleport (packet**dst ,uint32 intGuid);
TEA_SVRCORE_API  int   unpack_teleport (packet *src ,uint32 *intGuid);
/*ֹͣ�ƶ�*/
TEA_SVRCORE_API	int   pack_move_stop (packet**dst ,uint32 guid,uint16 pos_x,uint16 pos_y);
TEA_SVRCORE_API  int   unpack_move_stop (packet *src ,uint32 *guid,uint16 *pos_x,uint16 *pos_y);
/*unit�����ƶ�*/
TEA_SVRCORE_API	int   pack_unit_move (packet**dst ,uint32 guid,uint16 pos_x,uint16 pos_y, int8 *path , uint16 len_4);
TEA_SVRCORE_API  int   unpack_unit_move (packet *src ,uint32 *guid,uint16 *pos_x,uint16 *pos_y, int8 **path , uint16 *len_4);
/*ʹ����Ϸ����*/
TEA_SVRCORE_API	int   pack_use_gameobject (packet**dst ,uint32 target);
TEA_SVRCORE_API  int   unpack_use_gameobject (packet *src ,uint32 *target);
/*��������-����λ��*/
TEA_SVRCORE_API	int   pack_bag_exchange_pos (packet**dst ,uint32 src_bag,uint32 src_pos,uint32 dst_bag,uint32 dst_pos);
TEA_SVRCORE_API  int   unpack_bag_exchange_pos (packet *src ,uint32 *src_bag,uint32 *src_pos,uint32 *dst_bag,uint32 *dst_pos);
/*��������-������Ʒ*/
TEA_SVRCORE_API	int   pack_bag_destroy (packet**dst ,char const*item_guid,uint32 num,uint32 bag_id);
TEA_SVRCORE_API  int   unpack_bag_destroy (packet *src ,char **item_guid,uint32 *num,uint32 *bag_id);
/*�ָ���Ʒ*/
TEA_SVRCORE_API	int   pack_bag_item_split (packet**dst ,uint8 bag_id,uint16 src_pos,uint32 count,uint16 dst_pos,uint8 dst_bag);
TEA_SVRCORE_API  int   unpack_bag_item_split (packet *src ,uint8 *bag_id,uint16 *src_pos,uint32 *count,uint16 *dst_pos,uint8 *dst_bag);
/*ʹ����Ʒ*/
TEA_SVRCORE_API	int   pack_bag_item_user (packet**dst ,char const*item_guid,uint32 count);
TEA_SVRCORE_API  int   unpack_bag_item_user (packet *src ,char **item_guid,uint32 *count);
/*�·���Ʒ��ȴ*/
TEA_SVRCORE_API	int   pack_bag_item_cooldown (packet**dst , item_cooldown_info *list , uint16 len_1);
TEA_SVRCORE_API  int   unpack_bag_item_cooldown (packet *src , item_cooldown_info **list , uint16 *len_1);
/*grid�е�unit�ƶ�������*/
TEA_SVRCORE_API	int   pack_grid_unit_move (packet**dst );
TEA_SVRCORE_API  int   unpack_grid_unit_move (packet *src );
/*grid�е�unit�ƶ�������2*/
TEA_SVRCORE_API	int   pack_grid_unit_move_2 (packet**dst );
TEA_SVRCORE_API  int   unpack_grid_unit_move_2 (packet *src );
/*�һ���Ʒ*/
TEA_SVRCORE_API	int   pack_exchange_item (packet**dst ,uint32 entry,uint32 count,uint32 tar_entry);
TEA_SVRCORE_API  int   unpack_exchange_item (packet *src ,uint32 *entry,uint32 *count,uint32 *tar_entry);
/*������չ*/
TEA_SVRCORE_API	int   pack_bag_extension (packet**dst ,uint8 bag_id,uint8 extension_type,uint32 bag_pos);
TEA_SVRCORE_API  int   unpack_bag_extension (packet *src ,uint8 *bag_id,uint8 *extension_type,uint32 *bag_pos);
/*����NPC��Ʒ�б�*/
TEA_SVRCORE_API	int   pack_npc_get_goods_list (packet**dst ,uint32 npc_id);
TEA_SVRCORE_API  int   unpack_npc_get_goods_list (packet *src ,uint32 *npc_id);
/*Npc��Ʒ�б�*/
TEA_SVRCORE_API	int   pack_npc_goods_list (packet**dst , uint32 *goods , uint16 len_1,uint32 npc_id);
TEA_SVRCORE_API  int   unpack_npc_goods_list (packet *src , uint32 **goods , uint16 *len_1,uint32 *npc_id);
/*������Ʒ*/
TEA_SVRCORE_API	int   pack_store_buy (packet**dst ,uint32 id,uint32 count);
TEA_SVRCORE_API  int   unpack_store_buy (packet *src ,uint32 *id,uint32 *count);
/*������Ʒ*/
TEA_SVRCORE_API	int   pack_npc_sell (packet**dst ,uint32 npc_id,char const*item_guid,uint32 num);
TEA_SVRCORE_API  int   unpack_npc_sell (packet *src ,uint32 *npc_id,char **item_guid,uint32 *num);
/*�ع���Ʒ*/
TEA_SVRCORE_API	int   pack_npc_repurchase (packet**dst ,char const*item_id);
TEA_SVRCORE_API  int   unpack_npc_repurchase (packet *src ,char **item_id);
/*ʱװ�Ƿ�����*/
TEA_SVRCORE_API	int   pack_avatar_fashion_enable (packet**dst ,uint8 pos);
TEA_SVRCORE_API  int   unpack_avatar_fashion_enable (packet *src ,uint8 *pos);
/*����Ի�ѡ��*/
TEA_SVRCORE_API	int   pack_questhelp_talk_option (packet**dst ,uint32 quest_id,uint32 option_id,int32 value0,int32 value1);
TEA_SVRCORE_API  int   unpack_questhelp_talk_option (packet *src ,uint32 *quest_id,uint32 *option_id,int32 *value0,int32 *value1);
/*��NPC�Ի���ô��͵��б�*/
TEA_SVRCORE_API	int   pack_taxi_hello (packet**dst ,uint32 guid);
TEA_SVRCORE_API  int   unpack_taxi_hello (packet *src ,uint32 *guid);
/*���ʹ��͵��б�*/
TEA_SVRCORE_API	int   pack_taxi_stations_list (packet**dst ,uint32 npcid, taxi_menu_info *stations , uint16 len_2);
TEA_SVRCORE_API  int   unpack_taxi_stations_list (packet *src ,uint32 *npcid, taxi_menu_info **stations , uint16 *len_2);
/*ѡ���͵�*/
TEA_SVRCORE_API	int   pack_taxi_select_station (packet**dst ,uint32 station_id,uint32 guid);
TEA_SVRCORE_API  int   unpack_taxi_select_station (packet *src ,uint32 *station_id,uint32 *guid);
/*��NPC����ѡ��ѡ��*/
TEA_SVRCORE_API	int   pack_gossip_select_option (packet**dst ,uint32 option,uint32 guid,char const*unknow);
TEA_SVRCORE_API  int   unpack_gossip_select_option (packet *src ,uint32 *option,uint32 *guid,char **unknow);
/*��NPC���Ļ�ȡѡ��*/
TEA_SVRCORE_API	int   pack_gossip_hello (packet**dst ,uint32 guid);
TEA_SVRCORE_API  int   unpack_gossip_hello (packet *src ,uint32 *guid);
/*����������Ϣ��ѡ��*/
TEA_SVRCORE_API	int   pack_gossip_message (packet**dst ,uint32 npcid,uint32 npc_entry,uint32 option_id,char const*option_text, gossip_menu_option_info *gossip_items , uint16 len_5);
TEA_SVRCORE_API  int   unpack_gossip_message (packet *src ,uint32 *npcid,uint32 *npc_entry,uint32 *option_id,char **option_text, gossip_menu_option_info **gossip_items , uint16 *len_5);
/*���񷢲���״̬��ѯ*/
TEA_SVRCORE_API	int   pack_questgiver_status_query (packet**dst ,uint32 guid);
TEA_SVRCORE_API  int   unpack_questgiver_status_query (packet *src ,uint32 *guid);
/*����NPC״̬*/
TEA_SVRCORE_API	int   pack_questgiver_status (packet**dst ,uint32 guid,uint8 status);
TEA_SVRCORE_API  int   unpack_questgiver_status (packet *src ,uint32 *guid,uint8 *status);
/*��ѯ����״̬*/
TEA_SVRCORE_API	int   pack_query_quest_status (packet**dst , quest_status *quest_array , uint16 len_1);
TEA_SVRCORE_API  int   unpack_query_quest_status (packet *src , quest_status **quest_array , uint16 *len_1);
/*�ɽ�����*/
TEA_SVRCORE_API	int   pack_questhelp_get_canaccept_list (packet**dst );
TEA_SVRCORE_API  int   unpack_questhelp_get_canaccept_list (packet *src );
/*�·��ɽ������б�*/
TEA_SVRCORE_API	int   pack_questhelp_canaccept_list (packet**dst , uint32 *quests , uint16 len_1);
TEA_SVRCORE_API  int   unpack_questhelp_canaccept_list (packet *src , uint32 **quests , uint16 *len_1);
/*����ʧ��*/
TEA_SVRCORE_API	int   pack_questupdate_faild (packet**dst ,uint8 reason);
TEA_SVRCORE_API  int   unpack_questupdate_faild (packet *src ,uint8 *reason);
/*�����������*/
TEA_SVRCORE_API	int   pack_questupdate_complete (packet**dst ,uint32 quest_id);
TEA_SVRCORE_API  int   unpack_questupdate_complete (packet *src ,uint32 *quest_id);
/*��������*/
TEA_SVRCORE_API	int   pack_questlog_remove_quest (packet**dst ,uint8 slot,uint64 reserve);
TEA_SVRCORE_API  int   unpack_questlog_remove_quest (packet *src ,uint8 *slot,uint64 *reserve);
/*�������*/
TEA_SVRCORE_API	int   pack_questgiver_complete_quest (packet**dst ,uint32 guid,uint32 quest_id,uint8 reward);
TEA_SVRCORE_API  int   unpack_questgiver_complete_quest (packet *src ,uint32 *guid,uint32 *quest_id,uint8 *reward);
/*��������֪ͨ���������¸�����*/
TEA_SVRCORE_API	int   pack_questhelp_next (packet**dst ,uint32 current_id,uint32 next_id,uint32 guid);
TEA_SVRCORE_API  int   unpack_questhelp_next (packet *src ,uint32 *current_id,uint32 *next_id,uint32 *guid);
/*����ϵͳǿ���������*/
TEA_SVRCORE_API	int   pack_questhelp_complete (packet**dst ,uint32 quest_id,uint8 quest_statue,uint8 reserve);
TEA_SVRCORE_API  int   unpack_questhelp_complete (packet *src ,uint32 *quest_id,uint8 *quest_statue,uint8 *reserve);
/*��������ɹ�*/
TEA_SVRCORE_API	int   pack_questupdate_accept (packet**dst ,uint32 quest_id);
TEA_SVRCORE_API  int   unpack_questupdate_accept (packet *src ,uint32 *quest_id);
/*�����������_�±�����*/
TEA_SVRCORE_API	int   pack_questhelp_update_status (packet**dst ,uint32 quest_id,uint32 slot_id,uint32 num);
TEA_SVRCORE_API  int   unpack_questhelp_update_status (packet *src ,uint32 *quest_id,uint32 *slot_id,uint32 *num);
/*���������*/
TEA_SVRCORE_API	int   pack_questgetter_complete (packet**dst ,uint32 quest_id);
TEA_SVRCORE_API  int   unpack_questgetter_complete (packet *src ,uint32 *quest_id);
/*������*/
TEA_SVRCORE_API	int   pack_questgiver_accept_quest (packet**dst ,uint32 npcid,uint32 quest_id);
TEA_SVRCORE_API  int   unpack_questgiver_accept_quest (packet *src ,uint32 *npcid,uint32 *quest_id);
/*����ʹ����Ʒ*/
TEA_SVRCORE_API	int   pack_questupdate_use_item (packet**dst ,uint32 item_id);
TEA_SVRCORE_API  int   unpack_questupdate_use_item (packet *src ,uint32 *item_id);
/*��ѯ��������*/
TEA_SVRCORE_API	int   pack_questhelp_query_book (packet**dst ,uint32 dynasty);
TEA_SVRCORE_API  int   unpack_questhelp_query_book (packet *src ,uint32 *dynasty);
/*�·��ɽ���������*/
TEA_SVRCORE_API	int   pack_questhelp_book_quest (packet**dst ,uint32 quest_id);
TEA_SVRCORE_API  int   unpack_questhelp_book_quest (packet *src ,uint32 *quest_id);
/*���ʹ����Ϸ�����Ժ�Ķ���*/
TEA_SVRCORE_API	int   pack_use_gameobject_action (packet**dst ,uint32 player_id,uint32 gameobject_id);
TEA_SVRCORE_API  int   unpack_use_gameobject_action (packet *src ,uint32 *player_id,uint32 *gameobject_id);
/*���ù���ģʽ*/
TEA_SVRCORE_API	int   pack_set_attack_mode (packet**dst ,uint8 mode,uint64 reserve);
TEA_SVRCORE_API  int   unpack_set_attack_mode (packet *src ,uint8 *mode,uint64 *reserve);
/*ѡ��Ŀ��*/
TEA_SVRCORE_API	int   pack_select_target (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_select_target (packet *src ,uint32 *id);
/*����ս��*/
TEA_SVRCORE_API	int   pack_combat_state_update (packet**dst ,uint8 cur_state);
TEA_SVRCORE_API  int   unpack_combat_state_update (packet *src ,uint8 *cur_state);
/*�������*/
TEA_SVRCORE_API	int   pack_exp_update (packet**dst ,int32 exp,uint8 type,int32 vip_exp);
TEA_SVRCORE_API  int   unpack_exp_update (packet *src ,int32 *exp,uint8 *type,int32 *vip_exp);
/*�ͻ����ͷż���*/
TEA_SVRCORE_API	int   pack_spell_start (packet**dst ,uint32 spell_id,uint16 target_pos_x,uint16 target_pos_y,uint32 caster,uint32 target);
TEA_SVRCORE_API  int   unpack_spell_start (packet *src ,uint32 *spell_id,uint16 *target_pos_x,uint16 *target_pos_y,uint32 *caster,uint32 *target);
/*ʩ��ֹͣ*/
TEA_SVRCORE_API	int   pack_spell_stop (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_spell_stop (packet *src ,char **guid);
/*��*/
TEA_SVRCORE_API	int   pack_jump (packet**dst ,uint32 guid,float pos_x,float pos_y);
TEA_SVRCORE_API  int   unpack_jump (packet *src ,uint32 *guid,float *pos_x,float *pos_y);
/*����*/
TEA_SVRCORE_API	int   pack_resurrection (packet**dst ,uint8 type,uint64 reserve);
TEA_SVRCORE_API  int   unpack_resurrection (packet *src ,uint8 *type,uint64 *reserve);
/*���׷�������*/
TEA_SVRCORE_API	int   pack_trade_request (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_trade_request (packet *src ,char **guid);
/*���������*/
TEA_SVRCORE_API	int   pack_trade_reply (packet**dst ,char const*guid,uint8 reply);
TEA_SVRCORE_API  int   unpack_trade_reply (packet *src ,char **guid,uint8 *reply);
/*���׿�ʼ*/
TEA_SVRCORE_API	int   pack_trade_start (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_trade_start (packet *src ,char **guid);
/*����ȷ����Ʒ*/
TEA_SVRCORE_API	int   pack_trade_decide_items (packet**dst ,const char **items, uint16 len_1,int32 gold_ingot,int32 silver);
TEA_SVRCORE_API  int   unpack_trade_decide_items (packet *src ,const char **items, uint16 *len_1,int32 *gold_ingot,int32 *silver);
/*�������*/
TEA_SVRCORE_API	int   pack_trade_finish (packet**dst );
TEA_SVRCORE_API  int   unpack_trade_finish (packet *src );
/*����ȡ��*/
TEA_SVRCORE_API	int   pack_trade_cancel (packet**dst );
TEA_SVRCORE_API  int   unpack_trade_cancel (packet *src );
/*����׼����*/
TEA_SVRCORE_API	int   pack_trade_ready (packet**dst );
TEA_SVRCORE_API  int   unpack_trade_ready (packet *src );
/*���ｲ��*/
TEA_SVRCORE_API	int   pack_chat_unit_talk (packet**dst ,uint32 guid,uint32 content,char const*say);
TEA_SVRCORE_API  int   unpack_chat_unit_talk (packet *src ,uint32 *guid,uint32 *content,char **say);
/*�ͽ�����*/
TEA_SVRCORE_API	int   pack_chat_near (packet**dst ,char const*content);
TEA_SVRCORE_API  int   unpack_chat_near (packet *src ,char **content);
/*˽��*/
TEA_SVRCORE_API	int   pack_chat_whisper (packet**dst ,char const*guid,char const*content);
TEA_SVRCORE_API  int   unpack_chat_whisper (packet *src ,char **guid,char **content);
/*��Ӫ����*/
TEA_SVRCORE_API	int   pack_chat_faction (packet**dst ,char const*guid,char const*name,char const*content,uint8 faction);
TEA_SVRCORE_API  int   unpack_chat_faction (packet *src ,char **guid,char **name,char **content,uint8 *faction);
/*����*/
TEA_SVRCORE_API	int   pack_chat_world (packet**dst ,char const*guid,uint8 faction,char const*name,char const*content);
TEA_SVRCORE_API  int   unpack_chat_world (packet *src ,char **guid,uint8 *faction,char **name,char **content);
/*����*/
TEA_SVRCORE_API	int   pack_chat_horn (packet**dst ,char const*guid,uint8 faction,char const*name,char const*content);
TEA_SVRCORE_API  int   unpack_chat_horn (packet *src ,char **guid,uint8 *faction,char **name,char **content);
/*����*/
TEA_SVRCORE_API	int   pack_chat_notice (packet**dst ,uint32 id,char const*content,char const*data);
TEA_SVRCORE_API  int   unpack_chat_notice (packet *src ,uint32 *id,char **content,char **data);
/*��ѯ�����Ϣ*/
TEA_SVRCORE_API	int   pack_query_player_info (packet**dst ,char const*guid,uint32 flag,uint32 callback_id);
TEA_SVRCORE_API  int   unpack_query_player_info (packet *src ,char **guid,uint32 *flag,uint32 *callback_id);
/*��ѯ��Ϣ�������*/
TEA_SVRCORE_API	int   pack_query_result_update_object (packet**dst );
TEA_SVRCORE_API  int   unpack_query_result_update_object (packet *src );
/*��ȡ���*/
TEA_SVRCORE_API	int   pack_receive_gift_packs (packet**dst );
TEA_SVRCORE_API  int   unpack_receive_gift_packs (packet *src );
/*��ͼ�������*/
TEA_SVRCORE_API	int   pack_map_update_object (packet**dst );
TEA_SVRCORE_API  int   unpack_map_update_object (packet *src );
/*ս����Ϣbinlog*/
TEA_SVRCORE_API	int   pack_fighting_info_update_object (packet**dst );
TEA_SVRCORE_API  int   unpack_fighting_info_update_object (packet *src );
/*ս����Ϣbinlog*/
TEA_SVRCORE_API	int   pack_fighting_info_update_object_2 (packet**dst );
TEA_SVRCORE_API  int   unpack_fighting_info_update_object_2 (packet *src );
/*���븱��*/
TEA_SVRCORE_API	int   pack_instance_enter (packet**dst ,uint32 instance_id);
TEA_SVRCORE_API  int   unpack_instance_enter (packet *src ,uint32 *instance_id);
/*�����˷��͸���������һ�׶�ָ��*/
TEA_SVRCORE_API	int   pack_instance_next_state (packet**dst ,uint16 level,uint32 param);
TEA_SVRCORE_API  int   unpack_instance_next_state (packet *src ,uint16 *level,uint32 *param);
/*�����˳�*/
TEA_SVRCORE_API	int   pack_instance_exit (packet**dst ,uint32 reserve);
TEA_SVRCORE_API  int   unpack_instance_exit (packet *src ,uint32 *reserve);
/*��ʱ���ȡ*/
TEA_SVRCORE_API	int   pack_limit_activity_receive (packet**dst ,uint32 id,uint32 type);
TEA_SVRCORE_API  int   unpack_limit_activity_receive (packet *src ,uint32 *id,uint32 *type);
/*ɱ����~~��������*/
TEA_SVRCORE_API	int   pack_kill_man (packet**dst ,char const*killer,char const*killer_name,char const*victim,char const*victim_name);
TEA_SVRCORE_API  int   unpack_kill_man (packet *src ,char **killer,char **killer_name,char **victim,char **victim_name);
/*�������*/
TEA_SVRCORE_API	int   pack_player_upgrade (packet**dst ,uint32 guid);
TEA_SVRCORE_API  int   unpack_player_upgrade (packet *src ,uint32 *guid);
/*�ֿ��Ǯ*/
TEA_SVRCORE_API	int   pack_warehouse_save_money (packet**dst ,int32 money,int32 money_gold,int32 money_bills);
TEA_SVRCORE_API  int   unpack_warehouse_save_money (packet *src ,int32 *money,int32 *money_gold,int32 *money_bills);
/*�ֿ�ȡǮ*/
TEA_SVRCORE_API	int   pack_warehouse_take_money (packet**dst ,int32 money,int32 money_gold,int32 money_bills);
TEA_SVRCORE_API  int   unpack_warehouse_take_money (packet *src ,int32 *money,int32 *money_gold,int32 *money_bills);
/*ʹ��Ԫ������ĳ��*/
TEA_SVRCORE_API	int   pack_use_gold_opt (packet**dst ,uint8 type,char const*param);
TEA_SVRCORE_API  int   unpack_use_gold_opt (packet *src ,uint8 *type,char **param);
/*ʹ��ͭǮ����ĳ��*/
TEA_SVRCORE_API	int   pack_use_silver_opt (packet**dst ,uint8 type);
TEA_SVRCORE_API  int   unpack_use_silver_opt (packet *src ,uint8 *type);
/*��̨����*/
TEA_SVRCORE_API	int   pack_gm_rightfloat (packet**dst ,uint32 id,uint32 end_time,uint32 zone1,uint32 zone2,uint32 zone3,char const*subject,char const*content,char const*link,uint8 mode);
TEA_SVRCORE_API  int   unpack_gm_rightfloat (packet *src ,uint32 *id,uint32 *end_time,uint32 *zone1,uint32 *zone2,uint32 *zone3,char **subject,char **content,char **link,uint8 *mode);
/*ɾ��ĳ����̨����*/
TEA_SVRCORE_API	int   pack_del_gm_rightfloat (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_del_gm_rightfloat (packet *src ,uint32 *id);
/*Ӧ�÷�ͬ��ʱ��*/
TEA_SVRCORE_API	int   pack_sync_mstime_app (packet**dst ,uint32 mstime_now,uint32 time_now,uint32 open_time);
TEA_SVRCORE_API  int   unpack_sync_mstime_app (packet *src ,uint32 *mstime_now,uint32 *time_now,uint32 *open_time);
/*��Ҵ�ĳ������*/
TEA_SVRCORE_API	int   pack_open_window (packet**dst ,uint32 window_type);
TEA_SVRCORE_API  int   unpack_open_window (packet *src ,uint32 *window_type);
/*���Բ���*/
TEA_SVRCORE_API	int   pack_player_gag (packet**dst ,char const*player_id,uint32 end_time,char const*content);
TEA_SVRCORE_API  int   unpack_player_gag (packet *src ,char **player_id,uint32 *end_time,char **content);
/*���˲���*/
TEA_SVRCORE_API	int   pack_player_kicking (packet**dst ,char const*player_id);
TEA_SVRCORE_API  int   unpack_player_kicking (packet *src ,char **player_id);
/*�Ϸ�֪ͨ*/
TEA_SVRCORE_API	int   pack_merge_server_msg (packet**dst ,char const*merge_host,uint32 merge_port,char const*merge_key,uint32 merge_type,uint32 reserve,uint32 reserve2);
TEA_SVRCORE_API  int   unpack_merge_server_msg (packet *src ,char **merge_host,uint32 *merge_port,char **merge_key,uint32 *merge_type,uint32 *reserve,uint32 *reserve2);
/*��ȡ������Ϣ*/
TEA_SVRCORE_API	int   pack_rank_list_query (packet**dst ,uint32 call_back_id,uint8 rank_list_type,uint16 start_index,uint16 end_index);
TEA_SVRCORE_API  int   unpack_rank_list_query (packet *src ,uint32 *call_back_id,uint8 *rank_list_type,uint16 *start_index,uint16 *end_index);
/*�ͻ��˻�ȡ���а񷵻ؽ��*/
TEA_SVRCORE_API	int   pack_rank_list_query_result (packet**dst );
TEA_SVRCORE_API  int   unpack_rank_list_query_result (packet *src );
/*�ͻ����ȸ�����ģ����ȡuint*/
TEA_SVRCORE_API	int   pack_client_update_scened (packet**dst );
TEA_SVRCORE_API  int   unpack_client_update_scened (packet *src );
/*��ֵ��*/
TEA_SVRCORE_API	int   pack_num_lua (packet**dst );
TEA_SVRCORE_API  int   unpack_num_lua (packet *src );
/*ս��Ʒʰȡ*/
TEA_SVRCORE_API	int   pack_loot_select (packet**dst ,uint16 x,uint16 y);
TEA_SVRCORE_API  int   unpack_loot_select (packet *src ,uint16 *x,uint16 *y);
/*֪ͨ��¼������Ҵ�����Ϸ��*/
TEA_SVRCORE_API	int   pack_goback_to_game_server (packet**dst );
TEA_SVRCORE_API  int   unpack_goback_to_game_server (packet *src );
/*�ͻ��˰ѱ�����Ա���ݴ���������*/
TEA_SVRCORE_API	int   pack_world_war_CS_player_info (packet**dst );
TEA_SVRCORE_API  int   unpack_world_war_CS_player_info (packet *src );
/*��Ҽ�������뿪ĳ������*/
TEA_SVRCORE_API	int   pack_join_or_leave_server (packet**dst ,uint8 join_or_leave,uint8 server_type,uint32 server_pid,uint32 server_fd,uint32 time);
TEA_SVRCORE_API  int   unpack_join_or_leave_server (packet *src ,uint8 *join_or_leave,uint8 *server_type,uint32 *server_pid,uint32 *server_fd,uint32 *time);
/*�ͻ�����������Ա����*/
TEA_SVRCORE_API	int   pack_world_war_SC_player_info (packet**dst );
TEA_SVRCORE_API  int   unpack_world_war_SC_player_info (packet *src );
/*�ͻ��˶�����Ϣ*/
TEA_SVRCORE_API	int   pack_clientSubscription (packet**dst ,uint32 guid);
TEA_SVRCORE_API  int   unpack_clientSubscription (packet *src ,uint32 *guid);
/*������·�lua�ű�*/
TEA_SVRCORE_API	int   pack_lua_script (packet**dst );
TEA_SVRCORE_API  int   unpack_lua_script (packet *src );
/*��ɫ������Ϣ*/
TEA_SVRCORE_API	int   pack_char_update_info (packet**dst , char_create_info *info);
TEA_SVRCORE_API  int   unpack_char_update_info (packet *src , char_create_info **info);
/*֪ͨ�ͻ��˹۲��ߵ��ӽ�*/
TEA_SVRCORE_API	int   pack_notice_watcher_map_info (packet**dst ,char const*wather_guid,uint32 map_id,uint32 instance_id);
TEA_SVRCORE_API  int   unpack_notice_watcher_map_info (packet *src ,char **wather_guid,uint32 *map_id,uint32 *instance_id);
/*�ͻ��˶��Ķ�����Ϣ*/
TEA_SVRCORE_API	int   pack_modify_watch (packet**dst ,uint8 opt,uint32 cid,char const*key);
TEA_SVRCORE_API  int   unpack_modify_watch (packet *src ,uint8 *opt,uint32 *cid,char **key);
/*�������*/
TEA_SVRCORE_API	int   pack_kuafu_chuansong (packet**dst ,char const*str_data,char const*watcher_guid,uint32 reserve);
TEA_SVRCORE_API  int   unpack_kuafu_chuansong (packet *src ,char **str_data,char **watcher_guid,uint32 *reserve);
/*��ʾ��ǰװ��*/
TEA_SVRCORE_API	int   pack_show_suit (packet**dst ,uint8 position);
TEA_SVRCORE_API  int   unpack_show_suit (packet *src ,uint8 *position);
/*��ʾ��ǰ����*/
TEA_SVRCORE_API	int   pack_show_position (packet**dst ,uint8 channel);
TEA_SVRCORE_API  int   unpack_show_position (packet *src ,uint8 *channel);
/*Ԫ������*/
TEA_SVRCORE_API	int   pack_gold_respawn (packet**dst ,uint8 useGold);
TEA_SVRCORE_API  int   unpack_gold_respawn (packet *src ,uint8 *useGold);
/*Ұ����������ʱ*/
TEA_SVRCORE_API	int   pack_field_death_cooldown (packet**dst ,uint8 type,uint32 value,char const*killername,uint16 cooldown,char const*params);
TEA_SVRCORE_API  int   unpack_field_death_cooldown (packet *src ,uint8 *type,uint32 *value,char **killername,uint16 *cooldown,char **params);
/*�̳ǹ���*/
TEA_SVRCORE_API	int   pack_mall_buy (packet**dst ,uint32 id,uint32 count,uint32 time);
TEA_SVRCORE_API  int   unpack_mall_buy (packet *src ,uint32 *id,uint32 *count,uint32 *time);
/*ǿ��*/
TEA_SVRCORE_API	int   pack_strength (packet**dst ,uint8 part);
TEA_SVRCORE_API  int   unpack_strength (packet *src ,uint8 *part);
/*ǿ���ɹ�*/
TEA_SVRCORE_API	int   pack_strength_success (packet**dst ,uint16 level);
TEA_SVRCORE_API  int   unpack_strength_success (packet *src ,uint16 *level);
/*ǿ�ƽ���*/
TEA_SVRCORE_API	int   pack_forceInto (packet**dst );
TEA_SVRCORE_API  int   unpack_forceInto (packet *src );
/*��������*/
TEA_SVRCORE_API	int   pack_create_faction (packet**dst ,char const*name,uint8 icon);
TEA_SVRCORE_API  int   unpack_create_faction (packet *src ,char **name,uint8 *icon);
/*��������*/
TEA_SVRCORE_API	int   pack_faction_upgrade (packet**dst );
TEA_SVRCORE_API  int   unpack_faction_upgrade (packet *src );
/*����������*/
TEA_SVRCORE_API	int   pack_faction_join (packet**dst ,char const*id);
TEA_SVRCORE_API  int   unpack_faction_join (packet *src ,char **id);
/*������������*/
TEA_SVRCORE_API	int   pack_raise_base_spell (packet**dst ,uint8 raiseType,uint16 spellId);
TEA_SVRCORE_API  int   unpack_raise_base_spell (packet *src ,uint8 *raiseType,uint16 *spellId);
/*�������׷�ŭ����*/
TEA_SVRCORE_API	int   pack_upgrade_anger_spell (packet**dst ,uint16 spellId);
TEA_SVRCORE_API  int   unpack_upgrade_anger_spell (packet *src ,uint16 *spellId);
/*������������*/
TEA_SVRCORE_API	int   pack_raise_mount (packet**dst );
TEA_SVRCORE_API  int   unpack_raise_mount (packet *src );
/*������������*/
TEA_SVRCORE_API	int   pack_upgrade_mount (packet**dst ,uint8 useItem);
TEA_SVRCORE_API  int   unpack_upgrade_mount (packet *src ,uint8 *useItem);
/*����һ����������*/
TEA_SVRCORE_API	int   pack_upgrade_mount_one_step (packet**dst ,uint8 useItem);
TEA_SVRCORE_API  int   unpack_upgrade_mount_one_step (packet *src ,uint8 *useItem);
/*��������û�����*/
TEA_SVRCORE_API	int   pack_illusion_mount_active (packet**dst ,uint16 illuId);
TEA_SVRCORE_API  int   unpack_illusion_mount_active (packet *src ,uint16 *illuId);
/*����û�����*/
TEA_SVRCORE_API	int   pack_illusion_mount (packet**dst ,uint16 illuId);
TEA_SVRCORE_API  int   unpack_illusion_mount (packet *src ,uint16 *illuId);
/*�������*/
TEA_SVRCORE_API	int   pack_ride_mount (packet**dst );
TEA_SVRCORE_API  int   unpack_ride_mount (packet *src );
/*grid�е�unit��Ծ*/
TEA_SVRCORE_API	int   pack_grid_unit_jump (packet**dst );
TEA_SVRCORE_API  int   unpack_grid_unit_jump (packet *src );
/*��ʯ*/
TEA_SVRCORE_API	int   pack_gem (packet**dst ,uint8 part);
TEA_SVRCORE_API  int   unpack_gem (packet *src ,uint8 *part);
/*�����л�ģʽ*/
TEA_SVRCORE_API	int   pack_change_battle_mode (packet**dst ,uint8 mode);
TEA_SVRCORE_API  int   unpack_change_battle_mode (packet *src ,uint8 *mode);
/*��ƽģʽCD*/
TEA_SVRCORE_API	int   pack_peace_mode_cd (packet**dst ,uint8 mode);
TEA_SVRCORE_API  int   unpack_peace_mode_cd (packet *src ,uint8 *mode);
/*�������*/
TEA_SVRCORE_API	int   pack_divine_active (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_divine_active (packet *src ,uint8 *id);
/*�������*/
TEA_SVRCORE_API	int   pack_divine_uplev (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_divine_uplev (packet *src ,uint8 *id);
/*�л����*/
TEA_SVRCORE_API	int   pack_divine_switch (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_divine_switch (packet *src ,uint8 *id);
/*������Ծ*/
TEA_SVRCORE_API	int   pack_jump_start (packet**dst ,uint16 pos_x,uint16 pos_y);
TEA_SVRCORE_API  int   unpack_jump_start (packet *src ,uint16 *pos_x,uint16 *pos_y);
/*�������vip����*/
TEA_SVRCORE_API	int   pack_enter_vip_instance (packet**dst ,uint16 id,uint8 hard);
TEA_SVRCORE_API  int   unpack_enter_vip_instance (packet *src ,uint16 *id,uint8 *hard);
/*����ɨ��vip����*/
TEA_SVRCORE_API	int   pack_sweep_vip_instance (packet**dst ,uint16 id);
TEA_SVRCORE_API  int   unpack_sweep_vip_instance (packet *src ,uint16 *id);
/*���йһ�*/
TEA_SVRCORE_API	int   pack_hang_up (packet**dst );
TEA_SVRCORE_API  int   unpack_hang_up (packet *src );
/*���йһ�����*/
TEA_SVRCORE_API	int   pack_hang_up_setting (packet**dst ,uint32 value0,uint32 value1,uint32 value2,uint32 value3);
TEA_SVRCORE_API  int   unpack_hang_up_setting (packet *src ,uint32 *value0,uint32 *value1,uint32 *value2,uint32 *value3);
/*�����������������*/
TEA_SVRCORE_API	int   pack_enter_trial_instance (packet**dst );
TEA_SVRCORE_API  int   unpack_enter_trial_instance (packet *src );
/*ɨ������������*/
TEA_SVRCORE_API	int   pack_sweep_trial_instance (packet**dst );
TEA_SVRCORE_API  int   unpack_sweep_trial_instance (packet *src );
/*����������*/
TEA_SVRCORE_API	int   pack_reset_trial_instance (packet**dst );
TEA_SVRCORE_API  int   unpack_reset_trial_instance (packet *src );
/*ɨ����������*/
TEA_SVRCORE_API	int   pack_sweep_instance_reward (packet**dst ,uint8 inst_sub_type,uint8 data1,uint8 data2,uint8 data3, item_reward_info *list , uint16 len_5);
TEA_SVRCORE_API  int   unpack_sweep_instance_reward (packet *src ,uint8 *inst_sub_type,uint8 *data1,uint8 *data2,uint8 *data3, item_reward_info **list , uint16 *len_5);
/*�ؽ�����*/
TEA_SVRCORE_API	int   pack_reenter_instance (packet**dst );
TEA_SVRCORE_API  int   unpack_reenter_instance (packet *src );
/*�������Ϣ*/
TEA_SVRCORE_API	int   pack_merry_go_round (packet**dst );
TEA_SVRCORE_API  int   unpack_merry_go_round (packet *src );
/*��Ӻ���*/
TEA_SVRCORE_API	int   pack_social_add_friend (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_social_add_friend (packet *src ,char **guid);
/*ͬ����Ӻ���*/
TEA_SVRCORE_API	int   pack_social_sureadd_friend (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_social_sureadd_friend (packet *src ,char **guid);
/*��������*/
TEA_SVRCORE_API	int   pack_social_gift_friend (packet**dst ,char const*guid, item_reward_info *gift , uint16 len_2);
TEA_SVRCORE_API  int   unpack_social_gift_friend (packet *src ,char **guid, item_reward_info **gift , uint16 *len_2);
/*�Ƽ������б�*/
TEA_SVRCORE_API	int   pack_social_recommend_friend (packet**dst );
TEA_SVRCORE_API  int   unpack_social_recommend_friend (packet *src );
/*�Ƽ������б�*/
TEA_SVRCORE_API	int   pack_social_get_recommend_friend (packet**dst , social_friend_info *list , uint16 len_1);
TEA_SVRCORE_API  int   unpack_social_get_recommend_friend (packet *src , social_friend_info **list , uint16 *len_1);
/*����*/
TEA_SVRCORE_API	int   pack_social_revenge_enemy (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_social_revenge_enemy (packet *src ,char **guid);
/*ɾ������*/
TEA_SVRCORE_API	int   pack_social_del_friend (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_social_del_friend (packet *src ,char **guid);
/*�س�*/
TEA_SVRCORE_API	int   pack_teleport_main_city (packet**dst );
TEA_SVRCORE_API  int   unpack_teleport_main_city (packet *src );
/*��ͬƵ������*/
TEA_SVRCORE_API	int   pack_chat_by_channel (packet**dst ,uint8 channel,char const*content);
TEA_SVRCORE_API  int   unpack_chat_by_channel (packet *src ,uint8 *channel,char **content);
/*��������*/
TEA_SVRCORE_API	int   pack_send_chat (packet**dst ,uint8 channel,char const*guid,uint8 title,char const*name,uint8 vip,uint8 zs,uint8 lvl,uint8 gender,char const*content,char const*to_guid,char const*faction_guid);
TEA_SVRCORE_API  int   unpack_send_chat (packet *src ,uint8 *channel,char **guid,uint8 *title,char **name,uint8 *vip,uint8 *zs,uint8 *lvl,uint8 *gender,char **content,char **to_guid,char **faction_guid);
/*��������б�*/
TEA_SVRCORE_API	int   pack_social_clear_apply (packet**dst );
TEA_SVRCORE_API  int   unpack_social_clear_apply (packet *src );
/*���þܾ�������Ϣ*/
TEA_SVRCORE_API	int   pack_msg_decline (packet**dst ,uint32 value0,uint32 value1);
TEA_SVRCORE_API  int   unpack_msg_decline (packet *src ,uint32 *value0,uint32 *value1);
/*�����б�*/
TEA_SVRCORE_API	int   pack_faction_get_list_result (packet**dst , faction_info *list , uint16 len_1,uint8 curpag,uint8 maxpag);
TEA_SVRCORE_API  int   unpack_faction_get_list_result (packet *src , faction_info **list , uint16 *len_1,uint8 *curpag,uint8 *maxpag);
/*��ȡ�����б�*/
TEA_SVRCORE_API	int   pack_faction_getlist (packet**dst ,uint8 page,uint8 num,uint8 grep);
TEA_SVRCORE_API  int   unpack_faction_getlist (packet *src ,uint8 *page,uint8 *num,uint8 *grep);
/*���ɹ���*/
TEA_SVRCORE_API	int   pack_faction_manager (packet**dst ,uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2);
TEA_SVRCORE_API  int   unpack_faction_manager (packet *src ,uint8 *opt_type,uint16 *reserve_int1,uint16 *reserve_int2,char **reserve_str1,char **reserve_str2);
/*���ɳ�Ա����*/
TEA_SVRCORE_API	int   pack_faction_member_operate (packet**dst ,uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2);
TEA_SVRCORE_API  int   unpack_faction_member_operate (packet *src ,uint8 *opt_type,uint16 *reserve_int1,uint16 *reserve_int2,char **reserve_str1,char **reserve_str2);
/*���ټ������*/
TEA_SVRCORE_API	int   pack_faction_fast_join (packet**dst );
TEA_SVRCORE_API  int   unpack_faction_fast_join (packet *src );
/*ͨ��������Ӻ���*/
TEA_SVRCORE_API	int   pack_social_add_friend_byname (packet**dst ,char const*name);
TEA_SVRCORE_API  int   unpack_social_add_friend_byname (packet *src ,char **name);
/*���ʼ�*/
TEA_SVRCORE_API	int   pack_read_mail (packet**dst ,uint16 indx);
TEA_SVRCORE_API  int   unpack_read_mail (packet *src ,uint16 *indx);
/*��ȡ�ʼ�*/
TEA_SVRCORE_API	int   pack_pick_mail (packet**dst ,uint16 indx);
TEA_SVRCORE_API  int   unpack_pick_mail (packet *src ,uint16 *indx);
/*ɾ���ʼ�*/
TEA_SVRCORE_API	int   pack_remove_mail (packet**dst ,uint16 indx);
TEA_SVRCORE_API  int   unpack_remove_mail (packet *src ,uint16 *indx);
/*һ����ȡ�ʼ�*/
TEA_SVRCORE_API	int   pack_pick_mail_one_step (packet**dst );
TEA_SVRCORE_API  int   unpack_pick_mail_one_step (packet *src );
/*һ��ɾ���ʼ�*/
TEA_SVRCORE_API	int   pack_remove_mail_one_step (packet**dst );
TEA_SVRCORE_API  int   unpack_remove_mail_one_step (packet *src );
/*����ĳ��*/
TEA_SVRCORE_API	int   pack_block_chat (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_block_chat (packet *src ,char **guid);
/*ȡ������*/
TEA_SVRCORE_API	int   pack_cancel_block_chat (packet**dst ,uint8 indx);
TEA_SVRCORE_API  int   unpack_cancel_block_chat (packet *src ,uint8 *indx);
/*ʹ����Ҫ�㲥����Ϸ����*/
TEA_SVRCORE_API	int   pack_use_broadcast_gameobject (packet**dst ,uint32 target);
TEA_SVRCORE_API  int   unpack_use_broadcast_gameobject (packet *src ,uint32 *target);
/*����BOSS����*/
TEA_SVRCORE_API	int   pack_world_boss_enroll (packet**dst );
TEA_SVRCORE_API  int   unpack_world_boss_enroll (packet *src );
/*����BOSS��ս*/
TEA_SVRCORE_API	int   pack_world_boss_fight (packet**dst );
TEA_SVRCORE_API  int   unpack_world_boss_fight (packet *src );
/*����*/
TEA_SVRCORE_API	int   pack_change_line (packet**dst ,uint32 lineNo);
TEA_SVRCORE_API  int   unpack_change_line (packet *src ,uint32 *lineNo);
/*roll����BOSS����*/
TEA_SVRCORE_API	int   pack_roll_world_boss_treasure (packet**dst );
TEA_SVRCORE_API  int   unpack_roll_world_boss_treasure (packet *src );
/*roll����*/
TEA_SVRCORE_API	int   pack_roll_result (packet**dst ,uint8 point,char const*name,uint8 isHighest,uint32 timestamp,uint8 rollid);
TEA_SVRCORE_API  int   unpack_roll_result (packet *src ,uint8 *point,char **name,uint8 *isHighest,uint32 *timestamp,uint8 *rollid);
/*��ǰBOSS�˺�����*/
TEA_SVRCORE_API	int   pack_boss_rank (packet**dst ,uint8 rankType, rank_info *rankList , uint16 len_2,uint8 mine);
TEA_SVRCORE_API  int   unpack_boss_rank (packet *src ,uint8 *rankType, rank_info **rankList , uint16 *len_2,uint8 *mine);
/*���а����*/
TEA_SVRCORE_API	int   pack_rank_add_like (packet**dst ,uint8 type,char const*guid);
TEA_SVRCORE_API  int   unpack_rank_add_like (packet *src ,uint8 *type,char **guid);
/*���а���޽��*/
TEA_SVRCORE_API	int   pack_rank_add_like_result (packet**dst ,uint8 type,char const*guid,uint32 num);
TEA_SVRCORE_API  int   unpack_rank_add_like_result (packet *src ,uint8 *type,char **guid,uint32 *num);
/*������Դ����*/
TEA_SVRCORE_API	int   pack_res_instance_enter (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_res_instance_enter (packet *src ,uint8 *id);
/*ɨ����Դ����*/
TEA_SVRCORE_API	int   pack_res_instance_sweep (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_res_instance_sweep (packet *src ,uint8 *id);
/*�鿴����ͼ�ķ��ߺ�*/
TEA_SVRCORE_API	int   pack_show_map_line (packet**dst );
TEA_SVRCORE_API  int   unpack_show_map_line (packet *src );
/*���ر���ͼ�ķ��ߺ���Ϣ*/
TEA_SVRCORE_API	int   pack_send_map_line (packet**dst , line_info *info , uint16 len_1);
TEA_SVRCORE_API  int   unpack_send_map_line (packet *src , line_info **info , uint16 *len_1);
/*��ý�����ʾ*/
TEA_SVRCORE_API	int   pack_item_notice (packet**dst ,uint8 showType, item_reward_info *list , uint16 len_2);
TEA_SVRCORE_API  int   unpack_item_notice (packet *src ,uint8 *showType, item_reward_info **list , uint16 *len_2);
/*���͵�ĳ�������ͼ*/
TEA_SVRCORE_API	int   pack_teleport_map (packet**dst ,uint32 mapid,uint32 lineNo);
TEA_SVRCORE_API  int   unpack_teleport_map (packet *src ,uint32 *mapid,uint32 *lineNo);
/*���͵�Ұ��boss�Ա�*/
TEA_SVRCORE_API	int   pack_teleport_field_boss (packet**dst ,uint32 mapid,uint32 lineNo);
TEA_SVRCORE_API  int   unpack_teleport_field_boss (packet *src ,uint32 *mapid,uint32 *lineNo);
/*��Ծ�Ƚ���*/
TEA_SVRCORE_API	int   pack_get_activity_reward (packet**dst ,uint8 id,uint8 vip);
TEA_SVRCORE_API  int   unpack_get_activity_reward (packet *src ,uint8 *id,uint8 *vip);
/*�ɾͽ���*/
TEA_SVRCORE_API	int   pack_get_achieve_reward (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_get_achieve_reward (packet *src ,uint8 *id);
/*�ܳɾͽ���*/
TEA_SVRCORE_API	int   pack_get_achieve_all_reward (packet**dst );
TEA_SVRCORE_API  int   unpack_get_achieve_all_reward (packet *src );
/*װ���ƺ�*/
TEA_SVRCORE_API	int   pack_set_title (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_set_title (packet *src ,uint8 *id);
/*��ʼ���ƺ�*/
TEA_SVRCORE_API	int   pack_init_title (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_init_title (packet *src ,uint8 *id);
/*��ȡ�׳佱��*/
TEA_SVRCORE_API	int   pack_welfare_shouchong_reward (packet**dst );
TEA_SVRCORE_API  int   unpack_welfare_shouchong_reward (packet *src );
/*ÿ��ǩ������*/
TEA_SVRCORE_API	int   pack_welfare_checkin (packet**dst );
TEA_SVRCORE_API  int   unpack_welfare_checkin (packet *src );
/*�ۻ�ǩ������*/
TEA_SVRCORE_API	int   pack_welfare_checkin_all (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_welfare_checkin_all (packet *src ,uint8 *id);
/*��ǩ����*/
TEA_SVRCORE_API	int   pack_welfare_checkin_getback (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_welfare_checkin_getback (packet *src ,uint8 *id);
/*�ȼ�����*/
TEA_SVRCORE_API	int   pack_welfare_level (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_welfare_level (packet *src ,uint8 *id);
/*��һؽ���*/
TEA_SVRCORE_API	int   pack_welfare_active_getback (packet**dst ,uint8 id,uint8 best,uint16 num);
TEA_SVRCORE_API  int   unpack_welfare_active_getback (packet *src ,uint8 *id,uint8 *best,uint16 *num);
/*��ȡ������*/
TEA_SVRCORE_API	int   pack_pick_quest_reward (packet**dst ,uint8 indx);
TEA_SVRCORE_API  int   unpack_pick_quest_reward (packet *src ,uint8 *indx);
/*��npc�Ի�*/
TEA_SVRCORE_API	int   pack_talk_with_npc (packet**dst ,uint16 entry,uint16 questId);
TEA_SVRCORE_API  int   unpack_talk_with_npc (packet *src ,uint16 *entry,uint16 *questId);
/*ʹ��������Ʒ*/
TEA_SVRCORE_API	int   pack_use_virtual_item (packet**dst ,uint16 entry);
TEA_SVRCORE_API  int   unpack_use_virtual_item (packet *src ,uint16 *entry);
/*��ȡ�����½ڽ���*/
TEA_SVRCORE_API	int   pack_pick_quest_chapter_reward (packet**dst ,uint8 indx);
TEA_SVRCORE_API  int   unpack_pick_quest_chapter_reward (packet *src ,uint8 *indx);
/*3v3���ƥ��*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_match (packet**dst );
TEA_SVRCORE_API  int   unpack_kuafu_3v3_match (packet *src );
/*�����ʼƥ��*/
TEA_SVRCORE_API	int   pack_kuafu_match_start (packet**dst ,uint8 indx);
TEA_SVRCORE_API  int   unpack_kuafu_match_start (packet *src ,uint8 *indx);
/*3v3�������*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_buytimes (packet**dst ,uint8 num);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_buytimes (packet *src ,uint8 *num);
/*3v3ÿ�ջ�Ծ����*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_dayreward (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_dayreward (packet *src ,uint8 *id);
/*����3v3���а�*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_getranlist (packet**dst );
TEA_SVRCORE_API  int   unpack_kuafu_3v3_getranlist (packet *src );
/*3v3���а����б�*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_ranlist (packet**dst ,char const*list);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_ranlist (packet *src ,char **list);
/*�������н����б�*/
TEA_SVRCORE_API	int   pack_welfare_getalllist_getback (packet**dst ,uint8 best);
TEA_SVRCORE_API  int   unpack_welfare_getalllist_getback (packet *src ,uint8 *best);
/*�����б�*/
TEA_SVRCORE_API	int   pack_welfare_rewardlist_getback (packet**dst ,char const*list,char const*cost);
TEA_SVRCORE_API  int   unpack_welfare_rewardlist_getback (packet *src ,char **list,char **cost);
/*һ����ȡ���и���*/
TEA_SVRCORE_API	int   pack_welfare_getall_getback (packet**dst ,uint8 best);
TEA_SVRCORE_API  int   unpack_welfare_getall_getback (packet *src ,uint8 *best);
/*����3v3���а��Լ�������*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_getmyrank (packet**dst );
TEA_SVRCORE_API  int   unpack_kuafu_3v3_getmyrank (packet *src );
/*3v3���а��Լ������ν��*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_myrank (packet**dst ,uint8 rank);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_myrank (packet *src ,uint8 *rank);
/*��ɱ����*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_kill_detail (packet**dst ,uint32 indx1,uint32 indx2);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_kill_detail (packet *src ,uint32 *indx1,uint32 *indx2);
/*���ƥ��ȴ�����*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_wait_info (packet**dst , wait_info *list , uint16 len_1);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_wait_info (packet *src , wait_info **list , uint16 *len_1);
/*ȡ��ƥ��*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_cancel_match (packet**dst ,uint32 type);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_cancel_match (packet *src ,uint32 *type);
/*ƥ�䵽��&���ܻ��߾ܾ�*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_match_oper (packet**dst ,uint32 oper);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_match_oper (packet *src ,uint32 *oper);
/*�ܾ�����*/
TEA_SVRCORE_API	int   pack_kuafu_3v3_decline_match (packet**dst ,uint32 type);
TEA_SVRCORE_API  int   unpack_kuafu_3v3_decline_match (packet *src ,uint32 *type);
/*�ɸ��ᱦ���ƥ��*/
TEA_SVRCORE_API	int   pack_kuafu_xianfu_match (packet**dst ,uint8 indx);
TEA_SVRCORE_API  int   unpack_kuafu_xianfu_match (packet *src ,uint8 *indx);
/*�������ƥ��ȴ�*/
TEA_SVRCORE_API	int   pack_kuafu_match_wait (packet**dst ,uint8 type,uint8 target,uint8 count,uint32 data,char const*params);
TEA_SVRCORE_API  int   unpack_kuafu_match_wait (packet *src ,uint8 *type,uint8 *target,uint8 *count,uint32 *data,char **params);
/*�ɸ��ᱦС��ͼ��Ϣ*/
TEA_SVRCORE_API	int   pack_kuafu_xianfu_minimap_info (packet**dst );
TEA_SVRCORE_API  int   unpack_kuafu_xianfu_minimap_info (packet *src );
/*�����ɸ�����ȯ*/
TEA_SVRCORE_API	int   pack_buy_xianfu_item (packet**dst ,uint8 type,uint8 indx,uint16 count);
TEA_SVRCORE_API  int   unpack_buy_xianfu_item (packet *src ,uint8 *type,uint8 *indx,uint16 *count);
/*�������*/
TEA_SVRCORE_API	int   pack_xianfu_random_respawn (packet**dst );
TEA_SVRCORE_API  int   unpack_xianfu_random_respawn (packet *src );
/*����̨��ս*/
TEA_SVRCORE_API	int   pack_doujiantai_fight (packet**dst ,uint16 rank);
TEA_SVRCORE_API  int   unpack_doujiantai_fight (packet *src ,uint16 *rank);
/*����̨�������*/
TEA_SVRCORE_API	int   pack_doujiantai_buytime (packet**dst ,uint8 num);
TEA_SVRCORE_API  int   unpack_doujiantai_buytime (packet *src ,uint8 *num);
/*����̨����CD*/
TEA_SVRCORE_API	int   pack_doujiantai_clearcd (packet**dst );
TEA_SVRCORE_API  int   unpack_doujiantai_clearcd (packet *src );
/*����̨��ʤ����*/
TEA_SVRCORE_API	int   pack_doujiantai_first_reward (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_doujiantai_first_reward (packet *src ,uint8 *id);
/*����̨��ս������Ϣ*/
TEA_SVRCORE_API	int   pack_doujiantai_get_enemys_info (packet**dst );
TEA_SVRCORE_API  int   unpack_doujiantai_get_enemys_info (packet *src );
/*����̨���а�*/
TEA_SVRCORE_API	int   pack_doujiantai_get_rank (packet**dst ,uint16 startIdx,uint16 endIdx);
TEA_SVRCORE_API  int   unpack_doujiantai_get_rank (packet *src ,uint16 *startIdx,uint16 *endIdx);
/*����̨ˢ�¶���*/
TEA_SVRCORE_API	int   pack_doujiantai_refresh_enemys (packet**dst );
TEA_SVRCORE_API  int   unpack_doujiantai_refresh_enemys (packet *src );
/*����̨����*/
TEA_SVRCORE_API	int   pack_doujiantai_top3 (packet**dst );
TEA_SVRCORE_API  int   unpack_doujiantai_top3 (packet *src );
/*ʹ������*/
TEA_SVRCORE_API	int   pack_use_jump_point (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_use_jump_point (packet *src ,uint32 *id);
/*������Ʒ*/
TEA_SVRCORE_API	int   pack_bag_item_sell (packet**dst ,char const*item_guid,uint32 count);
TEA_SVRCORE_API  int   unpack_bag_item_sell (packet *src ,char **item_guid,uint32 *count);
/*������Ʒ*/
TEA_SVRCORE_API	int   pack_bag_item_sort (packet**dst ,uint32 bag_type);
TEA_SVRCORE_API  int   unpack_bag_item_sort (packet *src ,uint32 *bag_type);
/*�ύ�ճ�����*/
TEA_SVRCORE_API	int   pack_submit_quest_daily2 (packet**dst );
TEA_SVRCORE_API  int   unpack_submit_quest_daily2 (packet *src );
/*���Ըı�*/
TEA_SVRCORE_API	int   pack_attribute_changed (packet**dst );
TEA_SVRCORE_API  int   unpack_attribute_changed (packet *src );
/*�����и�ǿװ��*/
TEA_SVRCORE_API	int   pack_bag_find_equip_better (packet**dst ,uint32 item_id,uint32 pos);
TEA_SVRCORE_API  int   unpack_bag_find_equip_better (packet *src ,uint32 *item_id,uint32 *pos);
/*ģ�����*/
TEA_SVRCORE_API	int   pack_module_active (packet**dst ,uint32 moduleId);
TEA_SVRCORE_API  int   unpack_module_active (packet *src ,uint32 *moduleId);
/*��ȡ�ճ�������*/
TEA_SVRCORE_API	int   pack_pick_daily2_quest_reward (packet**dst ,uint8 indx);
TEA_SVRCORE_API  int   unpack_pick_daily2_quest_reward (packet *src ,uint8 *indx);
/*��ɵ�ǰ����*/
TEA_SVRCORE_API	int   pack_finish_now_guide (packet**dst );
TEA_SVRCORE_API  int   unpack_finish_now_guide (packet *src );
/*ȡ����������Ϣ*/
TEA_SVRCORE_API	int   pack_get_cultivation_info (packet**dst );
TEA_SVRCORE_API  int   unpack_get_cultivation_info (packet *src );
/*������������Ϣ*/
TEA_SVRCORE_API	int   pack_update_cultivation_info (packet**dst ,uint32 start_time,uint32 lost);
TEA_SVRCORE_API  int   unpack_update_cultivation_info (packet *src ,uint32 *start_time,uint32 *lost);
/*ȡ�õ�ǰ����������������Ϣ*/
TEA_SVRCORE_API	int   pack_get_cultivation_rivals_info (packet**dst );
TEA_SVRCORE_API  int   unpack_get_cultivation_rivals_info (packet *src );
/*����������������Ϣ*/
TEA_SVRCORE_API	int   pack_update_cultivation_rivals_info_list (packet**dst , cultivation_rivals_info *list , uint16 len_1);
TEA_SVRCORE_API  int   unpack_update_cultivation_rivals_info_list (packet *src , cultivation_rivals_info **list , uint16 *len_1);
/*��ȡ����������*/
TEA_SVRCORE_API	int   pack_get_cultivation_reward (packet**dst );
TEA_SVRCORE_API  int   unpack_get_cultivation_reward (packet *src );
/*ˢ������������*/
TEA_SVRCORE_API	int   pack_refresh_cultivation_rivals (packet**dst );
TEA_SVRCORE_API  int   unpack_refresh_cultivation_rivals (packet *src );
/*�Ӷ�����������*/
TEA_SVRCORE_API	int   pack_plunder_cultivation_rival (packet**dst ,uint32 index);
TEA_SVRCORE_API  int   unpack_plunder_cultivation_rival (packet *src ,uint32 *index);
/*������������������*/
TEA_SVRCORE_API	int   pack_revenge_cultivation_rival (packet**dst ,uint32 index);
TEA_SVRCORE_API  int   unpack_revenge_cultivation_rival (packet *src ,uint32 *index);
/*����������ʣ����ս����*/
TEA_SVRCORE_API	int   pack_buy_cultivation_left_plunder_count (packet**dst ,uint32 count);
TEA_SVRCORE_API  int   unpack_buy_cultivation_left_plunder_count (packet *src ,uint32 *count);
/*����������ս�����*/
TEA_SVRCORE_API	int   pack_show_cultivation_result_list (packet**dst ,int32 result,char const*name, item_reward_info *list , uint16 len_3);
TEA_SVRCORE_API  int   unpack_show_cultivation_result_list (packet *src ,int32 *result,char **name, item_reward_info **list , uint16 *len_3);
/*��ȡ��¼������*/
TEA_SVRCORE_API	int   pack_get_login_activity_reward (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_get_login_activity_reward (packet *src ,uint32 *id);
/*֪ͨ�ͻ����ͷ���������*/
TEA_SVRCORE_API	int   pack_cast_spell_start (packet**dst ,uint32 caster_guid,uint32 target_guid,uint16 spellid,char const*data);
TEA_SVRCORE_API  int   unpack_cast_spell_start (packet *src ,uint32 *caster_guid,uint32 *target_guid,uint16 *spellid,char **data);
/*��ɷ�ǿ�������Ĳ���*/
TEA_SVRCORE_API	int   pack_finish_optional_guide_step (packet**dst ,uint32 guide_id,uint8 step);
TEA_SVRCORE_API  int   unpack_finish_optional_guide_step (packet *src ,uint32 *guide_id,uint8 *step);
/*ִ�нӵ������Ժ������*/
TEA_SVRCORE_API	int   pack_execute_quest_cmd_after_accepted (packet**dst ,uint16 indx);
TEA_SVRCORE_API  int   unpack_execute_quest_cmd_after_accepted (packet *src ,uint16 *indx);
/*֪ͨ�ͻ�����ʾ����*/
TEA_SVRCORE_API	int   pack_show_unit_attribute (packet**dst );
TEA_SVRCORE_API  int   unpack_show_unit_attribute (packet *src );
/*���ؼ���*/
TEA_SVRCORE_API	int   pack_back_to_famity (packet**dst );
TEA_SVRCORE_API  int   unpack_back_to_famity (packet *src );
/*���ؼ���boss���*/
TEA_SVRCORE_API	int   pack_faction_boss_send_result (packet**dst ,uint32 result,uint32 boss_id,uint32 money);
TEA_SVRCORE_API  int   unpack_faction_boss_send_result (packet *src ,uint32 *result,uint32 *boss_id,uint32 *money);
/*��սboss*/
TEA_SVRCORE_API	int   pack_challange_boss (packet**dst );
TEA_SVRCORE_API  int   unpack_challange_boss (packet *src );
/*��ȡ���߽���*/
TEA_SVRCORE_API	int   pack_pick_offline_reward (packet**dst );
TEA_SVRCORE_API  int   unpack_pick_offline_reward (packet *src );
/*���߽������*/
TEA_SVRCORE_API	int   pack_offline_reward_result (packet**dst ,uint32 reserve,uint32 reserve2,uint32 reserve3,uint32 reserve4, item_reward_info *list , uint16 len_5);
TEA_SVRCORE_API  int   unpack_offline_reward_result (packet *src ,uint32 *reserve,uint32 *reserve2,uint32 *reserve3,uint32 *reserve4, item_reward_info **list , uint16 *len_5);
/*����װ��*/
TEA_SVRCORE_API	int   pack_smelting_equip (packet**dst ,char const*pos_str);
TEA_SVRCORE_API  int   unpack_smelting_equip (packet *src ,char **pos_str);
/*�Ͻ�װ��*/
TEA_SVRCORE_API	int   pack_storehouse_hand_in (packet**dst ,char const*pos_str);
TEA_SVRCORE_API  int   unpack_storehouse_hand_in (packet *src ,char **pos_str);
/*�һ�װ��*/
TEA_SVRCORE_API	int   pack_storehouse_exchange (packet**dst ,uint32 pos);
TEA_SVRCORE_API  int   unpack_storehouse_exchange (packet *src ,uint32 *pos);
/*����װ��*/
TEA_SVRCORE_API	int   pack_storehouse_destroy (packet**dst ,uint32 pos);
TEA_SVRCORE_API  int   unpack_storehouse_destroy (packet *src ,uint32 *pos);
/*��������*/
TEA_SVRCORE_API	int   pack_send_faction_gift (packet**dst , item_reward_info *list , uint16 len_1,char const*msg,uint32 msg_type);
TEA_SVRCORE_API  int   unpack_send_faction_gift (packet *src , item_reward_info **list , uint16 *len_1,char **msg,uint32 *msg_type);
/*��ȡ���⽱��*/
TEA_SVRCORE_API	int   pack_get_faction_gift_exreward (packet**dst ,uint32 count_id);
TEA_SVRCORE_API  int   unpack_get_faction_gift_exreward (packet *src ,uint32 *count_id);
/*��ȡ���ж��⽱��*/
TEA_SVRCORE_API	int   pack_get_all_faction_gift_exreward (packet**dst );
TEA_SVRCORE_API  int   unpack_get_all_faction_gift_exreward (packet *src );
/*���������б�*/
TEA_SVRCORE_API	int   pack_show_faction_gift_page (packet**dst );
TEA_SVRCORE_API  int   unpack_show_faction_gift_page (packet *src );
/*����������Ϣ*/
TEA_SVRCORE_API	int   pack_show_faction_gift_info (packet**dst );
TEA_SVRCORE_API  int   unpack_show_faction_gift_info (packet *src );
/*����Ů��δ��л����*/
TEA_SVRCORE_API	int   pack_show_faction_gift_unthank_page (packet**dst );
TEA_SVRCORE_API  int   unpack_show_faction_gift_unthank_page (packet *src );
/*����Ů����ʷ��¼*/
TEA_SVRCORE_API	int   pack_show_faction_gift_history_page (packet**dst );
TEA_SVRCORE_API  int   unpack_show_faction_gift_history_page (packet *src );
/*���������������*/
TEA_SVRCORE_API	int   pack_get_faction_gift_rank_page (packet**dst ,uint32 page);
TEA_SVRCORE_API  int   unpack_get_faction_gift_rank_page (packet *src ,uint32 *page);
/*���ؼ�����������*/
TEA_SVRCORE_API	int   pack_show_faction_gift_rank_result_list (packet**dst , faction_gift_rank_info *list , uint16 len_1, faction_gift_rank_info *info,uint32 page);
TEA_SVRCORE_API  int   unpack_show_faction_gift_rank_result_list (packet *src , faction_gift_rank_info **list , uint16 *len_1, faction_gift_rank_info **info,uint32 *page);
/*���ؼ����������б仯*/
TEA_SVRCORE_API	int   pack_show_faction_gift_rank_change (packet**dst ,uint32 old_rank,uint32 new_rank, faction_gift_rank_info *info);
TEA_SVRCORE_API  int   unpack_show_faction_gift_rank_change (packet *src ,uint32 *old_rank,uint32 *new_rank, faction_gift_rank_info **info);
/*���ر�������������*/
TEA_SVRCORE_API	int   pack_show_faction_gift_rank_info (packet**dst , faction_gift_rank_info *info);
TEA_SVRCORE_API  int   unpack_show_faction_gift_rank_info (packet *src , faction_gift_rank_info **info);
/*���ǿ��*/
TEA_SVRCORE_API	int   pack_divine_forge (packet**dst ,uint32 id,uint32 count);
TEA_SVRCORE_API  int   unpack_divine_forge (packet *src ,uint32 *id,uint32 *count);
/*�������*/
TEA_SVRCORE_API	int   pack_divine_advance (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_divine_advance (packet *src ,uint32 *id);
/*�������*/
TEA_SVRCORE_API	int   pack_divine_spirit (packet**dst ,uint32 id,uint32 protect,uint32 improve);
TEA_SVRCORE_API  int   unpack_divine_spirit (packet *src ,uint32 *id,uint32 *protect,uint32 *improve);
/*��ѯȫ��boss��Ϣ*/
TEA_SVRCORE_API	int   pack_query_mass_boss_info (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_query_mass_boss_info (packet *src ,uint8 *id);
/*ȫ��boss��Ϣ���*/
TEA_SVRCORE_API	int   pack_mass_boss_info_ret (packet**dst ,uint32 count,uint8 percent);
TEA_SVRCORE_API  int   unpack_mass_boss_info_ret (packet *src ,uint32 *count,uint8 *percent);
/*��ѯȫ��boss���а�*/
TEA_SVRCORE_API	int   pack_query_mass_boss_rank (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_query_mass_boss_rank (packet *src ,uint8 *id);
/*ȫ��boss���н��*/
TEA_SVRCORE_API	int   pack_mass_boss_rank_result (packet**dst , rank_info *info , uint16 len_1);
TEA_SVRCORE_API  int   unpack_mass_boss_rank_result (packet *src , rank_info **info , uint16 *len_1);
/*��սȫ��boss*/
TEA_SVRCORE_API	int   pack_try_mass_boss (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_try_mass_boss (packet *src ,uint8 *id);
/*������սȫ��boss����*/
TEA_SVRCORE_API	int   pack_buy_mass_boss_times (packet**dst ,uint8 cnt);
TEA_SVRCORE_API  int   unpack_buy_mass_boss_times (packet *src ,uint8 *cnt);
/*��Ӹ������ƥ��*/
TEA_SVRCORE_API	int   pack_group_instance_match (packet**dst ,uint8 indx);
TEA_SVRCORE_API  int   unpack_group_instance_match (packet *src ,uint8 *indx);
/*��Ӹ��������������*/
TEA_SVRCORE_API	int   pack_buy_group_instance_times (packet**dst ,uint8 count);
TEA_SVRCORE_API  int   unpack_buy_group_instance_times (packet *src ,uint8 *count);
/*��������*/
TEA_SVRCORE_API	int   pack_talisman_active (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_talisman_active (packet *src ,uint32 *id);
/*����ע��*/
TEA_SVRCORE_API	int   pack_talisman_lvup (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_talisman_lvup (packet *src ,uint32 *id);
/*���𼤻�*/
TEA_SVRCORE_API	int   pack_wings_active (packet**dst );
TEA_SVRCORE_API  int   unpack_wings_active (packet *src );
/*����ף��*/
TEA_SVRCORE_API	int   pack_wings_bless (packet**dst );
TEA_SVRCORE_API  int   unpack_wings_bless (packet *src );
/*��������*/
TEA_SVRCORE_API	int   pack_wings_rankup (packet**dst );
TEA_SVRCORE_API  int   unpack_wings_rankup (packet *src );
/*����ǿ��*/
TEA_SVRCORE_API	int   pack_wings_strength (packet**dst );
TEA_SVRCORE_API  int   unpack_wings_strength (packet *src );
/*��������*/
TEA_SVRCORE_API	int   pack_meridian_practise (packet**dst );
TEA_SVRCORE_API  int   unpack_meridian_practise (packet *src );
/*�Ӿ�����������ֵ*/
TEA_SVRCORE_API	int   pack_add_meridian_exp (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_add_meridian_exp (packet *src ,uint8 *id);
/*��������ȼ�*/
TEA_SVRCORE_API	int   pack_raise_mount_level_base (packet**dst );
TEA_SVRCORE_API  int   unpack_raise_mount_level_base (packet *src );
/*��������*/
TEA_SVRCORE_API	int   pack_active_mount (packet**dst );
TEA_SVRCORE_API  int   unpack_active_mount (packet *src );
/*����������ս�������*/
TEA_SVRCORE_API	int   pack_show_faction_bossdefense_damage_list (packet**dst , mass_boss_rank_info *list , uint16 len_1);
TEA_SVRCORE_API  int   unpack_show_faction_bossdefense_damage_list (packet *src , mass_boss_rank_info **list , uint16 *len_1);
/*�����޾�Զ��ɨ�����*/
TEA_SVRCORE_API	int   pack_show_faction_tower_sweep_list (packet**dst , item_reward_info *list , uint16 len_1);
TEA_SVRCORE_API  int   unpack_show_faction_tower_sweep_list (packet *src , item_reward_info **list , uint16 *len_1);
/*�������*/
TEA_SVRCORE_API	int   pack_send_instance_result (packet**dst ,uint8 state,uint8 cd, item_reward_info *list , uint16 len_3,uint8 type,char const*data);
TEA_SVRCORE_API  int   unpack_send_instance_result (packet *src ,uint8 *state,uint8 *cd, item_reward_info **list , uint16 *len_3,uint8 *type,char **data);
/*ƥ�䵥��pvp*/
TEA_SVRCORE_API	int   pack_match_single_pvp (packet**dst );
TEA_SVRCORE_API  int   unpack_match_single_pvp (packet *src );
/*������pvp����*/
TEA_SVRCORE_API	int   pack_buy_match_single_pvp_times (packet**dst ,uint8 cnt);
TEA_SVRCORE_API  int   unpack_buy_match_single_pvp_times (packet *src ,uint8 *cnt);
/*��ȡ����pvp���⽱��*/
TEA_SVRCORE_API	int   pack_pick_match_single_pvp_extra_reward (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_pick_match_single_pvp_extra_reward (packet *src ,uint8 *id);
/*װ�����ɲ���*/
TEA_SVRCORE_API	int   pack_equipdevelop_operate (packet**dst ,uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2);
TEA_SVRCORE_API  int   unpack_equipdevelop_operate (packet *src ,uint8 *opt_type,uint16 *reserve_int1,uint16 *reserve_int2,char **reserve_str1,char **reserve_str2);
/*�������*/
TEA_SVRCORE_API	int   pack_active_appearance (packet**dst ,uint16 id);
TEA_SVRCORE_API  int   unpack_active_appearance (packet *src ,uint16 *id);
/*װ�����*/
TEA_SVRCORE_API	int   pack_equip_appearance (packet**dst ,uint16 id);
TEA_SVRCORE_API  int   unpack_equip_appearance (packet *src ,uint16 *id);
/*ȡ��װ�����*/
TEA_SVRCORE_API	int   pack_cancel_equip_appearance (packet**dst ,uint8 type);
TEA_SVRCORE_API  int   unpack_cancel_equip_appearance (packet *src ,uint8 *type);
/*����*/
TEA_SVRCORE_API	int   pack_rename (packet**dst ,char const*name);
TEA_SVRCORE_API  int   unpack_rename (packet *src ,char **name);
/*���߽����ƺ�*/
TEA_SVRCORE_API	int   pack_unlock_title (packet**dst ,uint8 indx);
TEA_SVRCORE_API  int   unpack_unlock_title (packet *src ,uint8 *indx);
/*���򸴳����*/
TEA_SVRCORE_API	int   pack_social_buy_revenge_times (packet**dst ,uint8 count);
TEA_SVRCORE_API  int   unpack_social_buy_revenge_times (packet *src ,uint8 *count);
/*�����������ð�ո���*/
TEA_SVRCORE_API	int   pack_enter_risk_instance (packet**dst );
TEA_SVRCORE_API  int   unpack_enter_risk_instance (packet *src );
/*ɾ������*/
TEA_SVRCORE_API	int   pack_social_remove_enemy (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_social_remove_enemy (packet *src ,char **guid);
/*�鿴�������*/
TEA_SVRCORE_API	int   pack_get_player_overview (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_get_player_overview (packet *src ,char **guid);
/*�����������*/
TEA_SVRCORE_API	int   pack_show_player_overview (packet**dst ,char const*guid,char const*name,uint32 force,uint32 vip,uint32 title,uint32 gender,uint32 coat,uint32 weapon);
TEA_SVRCORE_API  int   unpack_show_player_overview (packet *src ,char **guid,char **name,uint32 *force,uint32 *vip,uint32 *title,uint32 *gender,uint32 *coat,uint32 *weapon);
/*����������*/
TEA_SVRCORE_API	int   pack_send_faction_invite (packet**dst ,char const*guid);
TEA_SVRCORE_API  int   unpack_send_faction_invite (packet *src ,char **guid);
/*��ʾ����*/
TEA_SVRCORE_API	int   pack_show_faction_invite (packet**dst ,char const*guid,char const*name,char const*faction_guid,char const*faction_name);
TEA_SVRCORE_API  int   unpack_show_faction_invite (packet *src ,char **guid,char **name,char **faction_guid,char **faction_name);
/*����vip���*/
TEA_SVRCORE_API	int   pack_buy_vipgift (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_buy_vipgift (packet *src ,uint32 *id);
/*����ÿ�����*/
TEA_SVRCORE_API	int   pack_activity_opt_buy_dailygift (packet**dst ,uint32 act_id,uint32 index);
TEA_SVRCORE_API  int   unpack_activity_opt_buy_dailygift (packet *src ,uint32 *act_id,uint32 *index);
/*�齱*/
TEA_SVRCORE_API	int   pack_draw_lottery (packet**dst ,uint32 actId,uint8 type);
TEA_SVRCORE_API  int   unpack_draw_lottery (packet *src ,uint32 *actId,uint8 *type);
/*��ȡ��������н��Ƚ���*/
TEA_SVRCORE_API	int   pack_activity_opt_get_rank_process_reward (packet**dst ,uint32 act_id,uint32 index);
TEA_SVRCORE_API  int   unpack_activity_opt_get_rank_process_reward (packet *src ,uint32 *act_id,uint32 *index);
/*��ȡ��������а�*/
TEA_SVRCORE_API	int   pack_activity_opt_get_rank_list (packet**dst ,uint32 act_id);
TEA_SVRCORE_API  int   unpack_activity_opt_get_rank_list (packet *src ,uint32 *act_id);
/*���ػ�������а�*/
TEA_SVRCORE_API	int   pack_activity_opt_show_rank_list (packet**dst ,uint32 act_id, act_rank_info *list , uint16 len_2);
TEA_SVRCORE_API  int   unpack_activity_opt_show_rank_list (packet *src ,uint32 *act_id, act_rank_info **list , uint16 *len_2);
/*�����޶����*/
TEA_SVRCORE_API	int   pack_activity_opt_buy_limitgift (packet**dst ,uint32 act_id,uint32 index);
TEA_SVRCORE_API  int   unpack_activity_opt_buy_limitgift (packet *src ,uint32 *act_id,uint32 *index);
/*��ȡ�ۼƳ�ֵ����*/
TEA_SVRCORE_API	int   pack_welfare_get_recharge_reward (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_welfare_get_recharge_reward (packet *src ,uint8 *id);
/*��ȡ�ۼ����ѽ���*/
TEA_SVRCORE_API	int   pack_welfare_get_consume_reward (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_welfare_get_consume_reward (packet *src ,uint8 *id);
/*��ȡ���մ�����*/
TEA_SVRCORE_API	int   pack_welfare_get_sevenday_reward (packet**dst ,uint8 id);
TEA_SVRCORE_API  int   unpack_welfare_get_sevenday_reward (packet *src ,uint8 *id);
/*����������ʱ��*/
TEA_SVRCORE_API	int   pack_send_server_open_time (packet**dst ,uint32 open_time);
TEA_SVRCORE_API  int   unpack_send_server_open_time (packet *src ,uint32 *open_time);
/*��������ð�����а�*/
TEA_SVRCORE_API	int   pack_risk_get_rank (packet**dst );
TEA_SVRCORE_API  int   unpack_risk_get_rank (packet *src );
/*����ð�����а���Ϣ */
TEA_SVRCORE_API	int   pack_risk_get_rank_result (packet**dst , act_rank_info *list , uint16 len_1);
TEA_SVRCORE_API  int   unpack_risk_get_rank_result (packet *src , act_rank_info **list , uint16 *len_1);
/*���ó���*/
TEA_SVRCORE_API	int   pack_set_orient (packet**dst ,uint16 angle);
TEA_SVRCORE_API  int   unpack_set_orient (packet *src ,uint16 *angle);
/*ҡ��ҡǮ��*/
TEA_SVRCORE_API	int   pack_use_moneytree (packet**dst );
TEA_SVRCORE_API  int   unpack_use_moneytree (packet *src );
/*��ȡҡǮ�����*/
TEA_SVRCORE_API	int   pack_get_moneytree_gift (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_get_moneytree_gift (packet *src ,uint32 *id);
/*�޸Ļþ�������id*/
TEA_SVRCORE_API	int   pack_set_world_risk_last_id (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_set_world_risk_last_id (packet *src ,uint32 *id);
/*�������Boss*/
TEA_SVRCORE_API	int   pack_enter_private_boss (packet**dst ,uint32 id);
TEA_SVRCORE_API  int   unpack_enter_private_boss (packet *src ,uint32 *id);
/*��������ȫ������*/
TEA_SVRCORE_API	int   pack_raise_base_spell_all (packet**dst ,uint8 raiseType,char const*spellIdStr);
TEA_SVRCORE_API  int   unpack_raise_base_spell_all (packet *src ,uint8 *raiseType,char **spellIdStr);
/*ʹ�ûظ�ҩ*/
TEA_SVRCORE_API	int   pack_use_restore_potion (packet**dst );
TEA_SVRCORE_API  int   unpack_use_restore_potion (packet *src );
/*rand send msg*/
TEA_SVRCORE_API	int   pack_rand_send_msg (packet**dst ,const char* msg);
#ifdef __cplusplus

#include <fastdelegate/FastDelegate.h>
TEA_SVRCORE_API packet_ptr external_protocol_new_packet(int optcode);
TEA_SVRCORE_API int external_protocol_free_packet(packet_ptr pkt);

typedef fastdelegate::FastDelegate1<packet&> Delegate_Sendpackt;

/*��Ч����*/
__INLINE__ int Call_null_action (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(MSG_NULL_ACTION);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������״̬*/
__INLINE__ int Call_ping_pong (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(MSG_PING_PONG);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ߵ����ߵ�׼��ǿ�Ƶ�½*/
__INLINE__ int Call_forced_into (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_FORCED_INTO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���Session����*/
__INLINE__ int Call_get_session (Delegate_Sendpackt SendPacket ,char const*sessionkey,char const*account,char const*version)
{
	packet *dst = external_protocol_new_packet(CMSG_GET_SESSION);
		
	packet_write_str(dst,sessionkey);		
	packet_write_str(dst,account);		
	packet_write_str(dst,version);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ط����ݰ�·�ɲ���*/
__INLINE__ int Call_route_trace (Delegate_Sendpackt SendPacket ,char const*val)
{
	packet *dst = external_protocol_new_packet(MSG_ROUTE_TRACE);
		
	packet_write_str(dst,val);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��¼�ͻ�����־*/
__INLINE__ int Call_write_client_log (Delegate_Sendpackt SendPacket ,uint32 type,char const*uid,char const*guid,char const*log)
{
	packet *dst = external_protocol_new_packet(CMSG_WRITE_CLIENT_LOG);
		
	packet_write(dst,(char *)&type,sizeof(uint32));
	packet_write_str(dst,uid);		
	packet_write_str(dst,guid);		
	packet_write_str(dst,log);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ʧ��*/
__INLINE__ int Call_operation_failed (Delegate_Sendpackt SendPacket ,uint16 type,uint16 reason,char const*data)
{
	packet *dst = external_protocol_new_packet(SMSG_OPERATION_FAILED);
		
	packet_write(dst,(char *)&type,sizeof(uint16));
	packet_write(dst,(char *)&reason,sizeof(uint16));
	packet_write_str(dst,data);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ͬ��ʱ��*/
__INLINE__ int Call_sync_mstime (Delegate_Sendpackt SendPacket ,uint32 mstime_now,uint32 time_now,uint32 open_time)
{
	packet *dst = external_protocol_new_packet(MSG_SYNC_MSTIME);
		
	packet_write(dst,(char *)&mstime_now,sizeof(uint32));
	packet_write(dst,(char *)&time_now,sizeof(uint32));
	packet_write(dst,(char *)&open_time,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_ud_object (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_UD_OBJECT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������¿���Э��*/
__INLINE__ int Call_ud_control (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_UD_CONTROL);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������¿���Э����*/
__INLINE__ int Call_ud_control_result (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_UD_CONTROL_RESULT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*GRID�Ķ������*/
__INLINE__ int Call_grid_ud_object (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_GRID_UD_OBJECT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*GRID�Ķ������*/
__INLINE__ int Call_grid_ud_object_2 (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_GRID_UD_OBJECT_2);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���߿ͻ��ˣ�Ŀǰ�Լ����ڵ�¼���еĵڼ�λ*/
__INLINE__ int Call_login_queue_index (Delegate_Sendpackt SendPacket ,uint32 index)
{
	packet *dst = external_protocol_new_packet(SMSG_LOGIN_QUEUE_INDEX);
		
	packet_write(dst,(char *)&index,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ԭ��*/
__INLINE__ int Call_kicking_type (Delegate_Sendpackt SendPacket ,uint32 k_type)
{
	packet *dst = external_protocol_new_packet(SMSG_KICKING_TYPE);
		
	packet_write(dst,(char *)&k_type,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ��ɫ�б�*/
__INLINE__ int Call_get_chars_list (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_GET_CHARS_LIST);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɫ�б�*/
__INLINE__ int Call_chars_list (Delegate_Sendpackt SendPacket ,const vector< char_create_info > &list ,char const*faction_name,char const*queen_name,uint8 icon)
{
	packet *dst = external_protocol_new_packet(SMSG_CHARS_LIST);
		
	*dst << list;
	packet_write_str(dst,faction_name);		
	packet_write_str(dst,queen_name);		
	packet_write(dst,(char *)&icon,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������Ƿ����ʹ��*/
__INLINE__ int Call_check_name (Delegate_Sendpackt SendPacket ,char const*name)
{
	packet *dst = external_protocol_new_packet(CMSG_CHECK_NAME);
		
	packet_write_str(dst,name);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������ֽ��*/
__INLINE__ int Call_check_name_result (Delegate_Sendpackt SendPacket ,uint8 result)
{
	packet *dst = external_protocol_new_packet(SMSG_CHECK_NAME_RESULT);
		
	packet_write(dst,(char *)&result,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������ɫ*/
__INLINE__ int Call_char_create (Delegate_Sendpackt SendPacket , char_create_info *info)
{
	packet *dst = external_protocol_new_packet(CMSG_CHAR_CREATE);
		
	packet_write(dst,(char*)info,sizeof(char_create_info));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɫ�������*/
__INLINE__ int Call_char_create_result (Delegate_Sendpackt SendPacket ,uint8 result)
{
	packet *dst = external_protocol_new_packet(SMSG_CHAR_CREATE_RESULT);
		
	packet_write(dst,(char *)&result,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɾ����ɫ*/
__INLINE__ int Call_delete_char (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_DELETE_CHAR);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɫɾ�����*/
__INLINE__ int Call_delete_char_result (Delegate_Sendpackt SendPacket ,uint8 result)
{
	packet *dst = external_protocol_new_packet(SMSG_DELETE_CHAR_RESULT);
		
	packet_write(dst,(char *)&result,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ҵ�¼*/
__INLINE__ int Call_player_login (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_PLAYER_LOGIN);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����˳�*/
__INLINE__ int Call_player_logout (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_PLAYER_LOGOUT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ʱ�˺�ת����*/
__INLINE__ int Call_regularise_account (Delegate_Sendpackt SendPacket ,char const*uid)
{
	packet *dst = external_protocol_new_packet(CMSG_REGULARISE_ACCOUNT);
		
	packet_write_str(dst,uid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɫ������Ϣ*/
__INLINE__ int Call_char_remotestore (Delegate_Sendpackt SendPacket ,uint32 key,uint32 value)
{
	packet *dst = external_protocol_new_packet(CMSG_CHAR_REMOTESTORE);
		
	packet_write(dst,(char *)&key,sizeof(uint32));
	packet_write(dst,(char *)&value,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɫ������Ϣ*/
__INLINE__ int Call_char_remotestore_str (Delegate_Sendpackt SendPacket ,uint32 key,char const*value)
{
	packet *dst = external_protocol_new_packet(CMSG_CHAR_REMOTESTORE_STR);
		
	packet_write(dst,(char *)&key,sizeof(uint32));
	packet_write_str(dst,value);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ͣ������C->S��mapid��������ɴ��͵�ID*/
__INLINE__ int Call_teleport (Delegate_Sendpackt SendPacket ,uint32 intGuid)
{
	packet *dst = external_protocol_new_packet(CMSG_TELEPORT);
		
	packet_write(dst,(char *)&intGuid,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ֹͣ�ƶ�*/
__INLINE__ int Call_move_stop (Delegate_Sendpackt SendPacket ,uint32 guid,uint16 pos_x,uint16 pos_y)
{
	packet *dst = external_protocol_new_packet(MSG_MOVE_STOP);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	packet_write(dst,(char *)&pos_x,sizeof(uint16));
	packet_write(dst,(char *)&pos_y,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*unit�����ƶ�*/
__INLINE__ int Call_unit_move (Delegate_Sendpackt SendPacket ,uint32 guid,uint16 pos_x,uint16 pos_y,const vector< int8 > &path )
{
	packet *dst = external_protocol_new_packet(MSG_UNIT_MOVE);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	packet_write(dst,(char *)&pos_x,sizeof(uint16));
	packet_write(dst,(char *)&pos_y,sizeof(uint16));
	*dst << path;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʹ����Ϸ����*/
__INLINE__ int Call_use_gameobject (Delegate_Sendpackt SendPacket ,uint32 target)
{
	packet *dst = external_protocol_new_packet(CMSG_USE_GAMEOBJECT);
		
	packet_write(dst,(char *)&target,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������-����λ��*/
__INLINE__ int Call_bag_exchange_pos (Delegate_Sendpackt SendPacket ,uint32 src_bag,uint32 src_pos,uint32 dst_bag,uint32 dst_pos)
{
	packet *dst = external_protocol_new_packet(CMSG_BAG_EXCHANGE_POS);
		
	packet_write(dst,(char *)&src_bag,sizeof(uint32));
	packet_write(dst,(char *)&src_pos,sizeof(uint32));
	packet_write(dst,(char *)&dst_bag,sizeof(uint32));
	packet_write(dst,(char *)&dst_pos,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������-������Ʒ*/
__INLINE__ int Call_bag_destroy (Delegate_Sendpackt SendPacket ,char const*item_guid,uint32 num,uint32 bag_id)
{
	packet *dst = external_protocol_new_packet(CMSG_BAG_DESTROY);
		
	packet_write_str(dst,item_guid);		
	packet_write(dst,(char *)&num,sizeof(uint32));
	packet_write(dst,(char *)&bag_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ָ���Ʒ*/
__INLINE__ int Call_bag_item_split (Delegate_Sendpackt SendPacket ,uint8 bag_id,uint16 src_pos,uint32 count,uint16 dst_pos,uint8 dst_bag)
{
	packet *dst = external_protocol_new_packet(CMSG_BAG_ITEM_SPLIT);
		
	packet_write(dst,(char *)&bag_id,sizeof(uint8));
	packet_write(dst,(char *)&src_pos,sizeof(uint16));
	packet_write(dst,(char *)&count,sizeof(uint32));
	packet_write(dst,(char *)&dst_pos,sizeof(uint16));
	packet_write(dst,(char *)&dst_bag,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʹ����Ʒ*/
__INLINE__ int Call_bag_item_user (Delegate_Sendpackt SendPacket ,char const*item_guid,uint32 count)
{
	packet *dst = external_protocol_new_packet(CMSG_BAG_ITEM_USER);
		
	packet_write_str(dst,item_guid);		
	packet_write(dst,(char *)&count,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�·���Ʒ��ȴ*/
__INLINE__ int Call_bag_item_cooldown (Delegate_Sendpackt SendPacket ,const vector< item_cooldown_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_BAG_ITEM_COOLDOWN);
		
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*grid�е�unit�ƶ�������*/
__INLINE__ int Call_grid_unit_move (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_GRID_UNIT_MOVE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*grid�е�unit�ƶ�������2*/
__INLINE__ int Call_grid_unit_move_2 (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_GRID_UNIT_MOVE_2);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�һ���Ʒ*/
__INLINE__ int Call_exchange_item (Delegate_Sendpackt SendPacket ,uint32 entry,uint32 count,uint32 tar_entry)
{
	packet *dst = external_protocol_new_packet(CMSG_EXCHANGE_ITEM);
		
	packet_write(dst,(char *)&entry,sizeof(uint32));
	packet_write(dst,(char *)&count,sizeof(uint32));
	packet_write(dst,(char *)&tar_entry,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������չ*/
__INLINE__ int Call_bag_extension (Delegate_Sendpackt SendPacket ,uint8 bag_id,uint8 extension_type,uint32 bag_pos)
{
	packet *dst = external_protocol_new_packet(CMSG_BAG_EXTENSION);
		
	packet_write(dst,(char *)&bag_id,sizeof(uint8));
	packet_write(dst,(char *)&extension_type,sizeof(uint8));
	packet_write(dst,(char *)&bag_pos,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����NPC��Ʒ�б�*/
__INLINE__ int Call_npc_get_goods_list (Delegate_Sendpackt SendPacket ,uint32 npc_id)
{
	packet *dst = external_protocol_new_packet(CMSG_NPC_GET_GOODS_LIST);
		
	packet_write(dst,(char *)&npc_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*Npc��Ʒ�б�*/
__INLINE__ int Call_npc_goods_list (Delegate_Sendpackt SendPacket ,const vector< uint32 > &goods ,uint32 npc_id)
{
	packet *dst = external_protocol_new_packet(SMSG_NPC_GOODS_LIST);
		
	*dst << goods;
	packet_write(dst,(char *)&npc_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������Ʒ*/
__INLINE__ int Call_store_buy (Delegate_Sendpackt SendPacket ,uint32 id,uint32 count)
{
	packet *dst = external_protocol_new_packet(CMSG_STORE_BUY);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	packet_write(dst,(char *)&count,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������Ʒ*/
__INLINE__ int Call_npc_sell (Delegate_Sendpackt SendPacket ,uint32 npc_id,char const*item_guid,uint32 num)
{
	packet *dst = external_protocol_new_packet(CMSG_NPC_SELL);
		
	packet_write(dst,(char *)&npc_id,sizeof(uint32));
	packet_write_str(dst,item_guid);		
	packet_write(dst,(char *)&num,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ع���Ʒ*/
__INLINE__ int Call_npc_repurchase (Delegate_Sendpackt SendPacket ,char const*item_id)
{
	packet *dst = external_protocol_new_packet(CMSG_NPC_REPURCHASE);
		
	packet_write_str(dst,item_id);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʱװ�Ƿ�����*/
__INLINE__ int Call_avatar_fashion_enable (Delegate_Sendpackt SendPacket ,uint8 pos)
{
	packet *dst = external_protocol_new_packet(CMSG_AVATAR_FASHION_ENABLE);
		
	packet_write(dst,(char *)&pos,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����Ի�ѡ��*/
__INLINE__ int Call_questhelp_talk_option (Delegate_Sendpackt SendPacket ,uint32 quest_id,uint32 option_id,int32 value0,int32 value1)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTHELP_TALK_OPTION);
		
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	packet_write(dst,(char *)&option_id,sizeof(uint32));
	packet_write(dst,(char *)&value0,sizeof(int32));
	packet_write(dst,(char *)&value1,sizeof(int32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��NPC�Ի���ô��͵��б�*/
__INLINE__ int Call_taxi_hello (Delegate_Sendpackt SendPacket ,uint32 guid)
{
	packet *dst = external_protocol_new_packet(CMSG_TAXI_HELLO);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ʹ��͵��б�*/
__INLINE__ int Call_taxi_stations_list (Delegate_Sendpackt SendPacket ,uint32 npcid,const vector< taxi_menu_info > &stations )
{
	packet *dst = external_protocol_new_packet(SMSG_TAXI_STATIONS_LIST);
		
	packet_write(dst,(char *)&npcid,sizeof(uint32));
	*dst << stations;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ѡ���͵�*/
__INLINE__ int Call_taxi_select_station (Delegate_Sendpackt SendPacket ,uint32 station_id,uint32 guid)
{
	packet *dst = external_protocol_new_packet(CMSG_TAXI_SELECT_STATION);
		
	packet_write(dst,(char *)&station_id,sizeof(uint32));
	packet_write(dst,(char *)&guid,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��NPC����ѡ��ѡ��*/
__INLINE__ int Call_gossip_select_option (Delegate_Sendpackt SendPacket ,uint32 option,uint32 guid,char const*unknow)
{
	packet *dst = external_protocol_new_packet(CMSG_GOSSIP_SELECT_OPTION);
		
	packet_write(dst,(char *)&option,sizeof(uint32));
	packet_write(dst,(char *)&guid,sizeof(uint32));
	packet_write_str(dst,unknow);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��NPC���Ļ�ȡѡ��*/
__INLINE__ int Call_gossip_hello (Delegate_Sendpackt SendPacket ,uint32 guid)
{
	packet *dst = external_protocol_new_packet(CMSG_GOSSIP_HELLO);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������Ϣ��ѡ��*/
__INLINE__ int Call_gossip_message (Delegate_Sendpackt SendPacket ,uint32 npcid,uint32 npc_entry,uint32 option_id,char const*option_text,const vector< gossip_menu_option_info > &gossip_items )
{
	packet *dst = external_protocol_new_packet(SMSG_GOSSIP_MESSAGE);
		
	packet_write(dst,(char *)&npcid,sizeof(uint32));
	packet_write(dst,(char *)&npc_entry,sizeof(uint32));
	packet_write(dst,(char *)&option_id,sizeof(uint32));
	packet_write_str(dst,option_text);		
	*dst << gossip_items;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���񷢲���״̬��ѯ*/
__INLINE__ int Call_questgiver_status_query (Delegate_Sendpackt SendPacket ,uint32 guid)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTGIVER_STATUS_QUERY);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����NPC״̬*/
__INLINE__ int Call_questgiver_status (Delegate_Sendpackt SendPacket ,uint32 guid,uint8 status)
{
	packet *dst = external_protocol_new_packet(SMSG_QUESTGIVER_STATUS);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	packet_write(dst,(char *)&status,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ѯ����״̬*/
__INLINE__ int Call_query_quest_status (Delegate_Sendpackt SendPacket ,const vector< quest_status > &quest_array )
{
	packet *dst = external_protocol_new_packet(MSG_QUERY_QUEST_STATUS);
		
	*dst << quest_array;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ɽ�����*/
__INLINE__ int Call_questhelp_get_canaccept_list (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTHELP_GET_CANACCEPT_LIST);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�·��ɽ������б�*/
__INLINE__ int Call_questhelp_canaccept_list (Delegate_Sendpackt SendPacket ,const vector< uint32 > &quests )
{
	packet *dst = external_protocol_new_packet(SMSG_QUESTHELP_CANACCEPT_LIST);
		
	*dst << quests;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ʧ��*/
__INLINE__ int Call_questupdate_faild (Delegate_Sendpackt SendPacket ,uint8 reason)
{
	packet *dst = external_protocol_new_packet(SMSG_QUESTUPDATE_FAILD);
		
	packet_write(dst,(char *)&reason,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����������*/
__INLINE__ int Call_questupdate_complete (Delegate_Sendpackt SendPacket ,uint32 quest_id)
{
	packet *dst = external_protocol_new_packet(SMSG_QUESTUPDATE_COMPLETE);
		
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_questlog_remove_quest (Delegate_Sendpackt SendPacket ,uint8 slot,uint64 reserve)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTLOG_REMOVE_QUEST);
		
	packet_write(dst,(char *)&slot,sizeof(uint8));
	packet_write(dst,(char *)&reserve,sizeof(uint64));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_questgiver_complete_quest (Delegate_Sendpackt SendPacket ,uint32 guid,uint32 quest_id,uint8 reward)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTGIVER_COMPLETE_QUEST);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	packet_write(dst,(char *)&reward,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������֪ͨ���������¸�����*/
__INLINE__ int Call_questhelp_next (Delegate_Sendpackt SendPacket ,uint32 current_id,uint32 next_id,uint32 guid)
{
	packet *dst = external_protocol_new_packet(SMSG_QUESTHELP_NEXT);
		
	packet_write(dst,(char *)&current_id,sizeof(uint32));
	packet_write(dst,(char *)&next_id,sizeof(uint32));
	packet_write(dst,(char *)&guid,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ϵͳǿ���������*/
__INLINE__ int Call_questhelp_complete (Delegate_Sendpackt SendPacket ,uint32 quest_id,uint8 quest_statue,uint8 reserve)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTHELP_COMPLETE);
		
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	packet_write(dst,(char *)&quest_statue,sizeof(uint8));
	packet_write(dst,(char *)&reserve,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������ɹ�*/
__INLINE__ int Call_questupdate_accept (Delegate_Sendpackt SendPacket ,uint32 quest_id)
{
	packet *dst = external_protocol_new_packet(SMSG_QUESTUPDATE_ACCEPT);
		
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����������_�±�����*/
__INLINE__ int Call_questhelp_update_status (Delegate_Sendpackt SendPacket ,uint32 quest_id,uint32 slot_id,uint32 num)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTHELP_UPDATE_STATUS);
		
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	packet_write(dst,(char *)&slot_id,sizeof(uint32));
	packet_write(dst,(char *)&num,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���������*/
__INLINE__ int Call_questgetter_complete (Delegate_Sendpackt SendPacket ,uint32 quest_id)
{
	packet *dst = external_protocol_new_packet(SMSG_QUESTGETTER_COMPLETE);
		
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������*/
__INLINE__ int Call_questgiver_accept_quest (Delegate_Sendpackt SendPacket ,uint32 npcid,uint32 quest_id)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTGIVER_ACCEPT_QUEST);
		
	packet_write(dst,(char *)&npcid,sizeof(uint32));
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ʹ����Ʒ*/
__INLINE__ int Call_questupdate_use_item (Delegate_Sendpackt SendPacket ,uint32 item_id)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTUPDATE_USE_ITEM);
		
	packet_write(dst,(char *)&item_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ѯ��������*/
__INLINE__ int Call_questhelp_query_book (Delegate_Sendpackt SendPacket ,uint32 dynasty)
{
	packet *dst = external_protocol_new_packet(CMSG_QUESTHELP_QUERY_BOOK);
		
	packet_write(dst,(char *)&dynasty,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�·��ɽ���������*/
__INLINE__ int Call_questhelp_book_quest (Delegate_Sendpackt SendPacket ,uint32 quest_id)
{
	packet *dst = external_protocol_new_packet(SMSG_QUESTHELP_BOOK_QUEST);
		
	packet_write(dst,(char *)&quest_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ʹ����Ϸ�����Ժ�Ķ���*/
__INLINE__ int Call_use_gameobject_action (Delegate_Sendpackt SendPacket ,uint32 player_id,uint32 gameobject_id)
{
	packet *dst = external_protocol_new_packet(SMSG_USE_GAMEOBJECT_ACTION);
		
	packet_write(dst,(char *)&player_id,sizeof(uint32));
	packet_write(dst,(char *)&gameobject_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ù���ģʽ*/
__INLINE__ int Call_set_attack_mode (Delegate_Sendpackt SendPacket ,uint8 mode,uint64 reserve)
{
	packet *dst = external_protocol_new_packet(CMSG_SET_ATTACK_MODE);
		
	packet_write(dst,(char *)&mode,sizeof(uint8));
	packet_write(dst,(char *)&reserve,sizeof(uint64));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ѡ��Ŀ��*/
__INLINE__ int Call_select_target (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(MSG_SELECT_TARGET);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ս��*/
__INLINE__ int Call_combat_state_update (Delegate_Sendpackt SendPacket ,uint8 cur_state)
{
	packet *dst = external_protocol_new_packet(SMSG_COMBAT_STATE_UPDATE);
		
	packet_write(dst,(char *)&cur_state,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_exp_update (Delegate_Sendpackt SendPacket ,int32 exp,uint8 type,int32 vip_exp)
{
	packet *dst = external_protocol_new_packet(SMSG_EXP_UPDATE);
		
	packet_write(dst,(char *)&exp,sizeof(int32));
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write(dst,(char *)&vip_exp,sizeof(int32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ͻ����ͷż���*/
__INLINE__ int Call_spell_start (Delegate_Sendpackt SendPacket ,uint32 spell_id,uint16 target_pos_x,uint16 target_pos_y,uint32 caster,uint32 target)
{
	packet *dst = external_protocol_new_packet(MSG_SPELL_START);
		
	packet_write(dst,(char *)&spell_id,sizeof(uint32));
	packet_write(dst,(char *)&target_pos_x,sizeof(uint16));
	packet_write(dst,(char *)&target_pos_y,sizeof(uint16));
	packet_write(dst,(char *)&caster,sizeof(uint32));
	packet_write(dst,(char *)&target,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʩ��ֹͣ*/
__INLINE__ int Call_spell_stop (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(MSG_SPELL_STOP);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��*/
__INLINE__ int Call_jump (Delegate_Sendpackt SendPacket ,uint32 guid,float pos_x,float pos_y)
{
	packet *dst = external_protocol_new_packet(MSG_JUMP);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	packet_write(dst,(char *)&pos_x,sizeof(float));
	packet_write(dst,(char *)&pos_y,sizeof(float));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����*/
__INLINE__ int Call_resurrection (Delegate_Sendpackt SendPacket ,uint8 type,uint64 reserve)
{
	packet *dst = external_protocol_new_packet(CMSG_RESURRECTION);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write(dst,(char *)&reserve,sizeof(uint64));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���׷�������*/
__INLINE__ int Call_trade_request (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(MSG_TRADE_REQUEST);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���������*/
__INLINE__ int Call_trade_reply (Delegate_Sendpackt SendPacket ,char const*guid,uint8 reply)
{
	packet *dst = external_protocol_new_packet(MSG_TRADE_REPLY);
		
	packet_write_str(dst,guid);		
	packet_write(dst,(char *)&reply,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���׿�ʼ*/
__INLINE__ int Call_trade_start (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(SMSG_TRADE_START);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ȷ����Ʒ*/
__INLINE__ int Call_trade_decide_items (Delegate_Sendpackt SendPacket ,char const*items,int32 gold_ingot,int32 silver)
{
	packet *dst = external_protocol_new_packet(MSG_TRADE_DECIDE_ITEMS);
		
	packet_write_str(dst,items);		
	packet_write(dst,(char *)&gold_ingot,sizeof(int32));
	packet_write(dst,(char *)&silver,sizeof(int32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_trade_finish (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_TRADE_FINISH);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ȡ��*/
__INLINE__ int Call_trade_cancel (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(MSG_TRADE_CANCEL);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����׼����*/
__INLINE__ int Call_trade_ready (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(MSG_TRADE_READY);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ｲ��*/
__INLINE__ int Call_chat_unit_talk (Delegate_Sendpackt SendPacket ,uint32 guid,uint32 content,char const*say)
{
	packet *dst = external_protocol_new_packet(SMSG_CHAT_UNIT_TALK);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	packet_write(dst,(char *)&content,sizeof(uint32));
	packet_write_str(dst,say);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ͽ�����*/
__INLINE__ int Call_chat_near (Delegate_Sendpackt SendPacket ,char const*content)
{
	packet *dst = external_protocol_new_packet(CMSG_CHAT_NEAR);
		
	packet_write_str(dst,content);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*˽��*/
__INLINE__ int Call_chat_whisper (Delegate_Sendpackt SendPacket ,char const*guid,char const*content)
{
	packet *dst = external_protocol_new_packet(CMSG_CHAT_WHISPER);
		
	packet_write_str(dst,guid);		
	packet_write_str(dst,content);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��Ӫ����*/
__INLINE__ int Call_chat_faction (Delegate_Sendpackt SendPacket ,char const*guid,char const*name,char const*content,uint8 faction)
{
	packet *dst = external_protocol_new_packet(MSG_CHAT_FACTION);
		
	packet_write_str(dst,guid);		
	packet_write_str(dst,name);		
	packet_write_str(dst,content);		
	packet_write(dst,(char *)&faction,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����*/
__INLINE__ int Call_chat_world (Delegate_Sendpackt SendPacket ,char const*guid,uint8 faction,char const*name,char const*content)
{
	packet *dst = external_protocol_new_packet(MSG_CHAT_WORLD);
		
	packet_write_str(dst,guid);		
	packet_write(dst,(char *)&faction,sizeof(uint8));
	packet_write_str(dst,name);		
	packet_write_str(dst,content);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����*/
__INLINE__ int Call_chat_horn (Delegate_Sendpackt SendPacket ,char const*guid,uint8 faction,char const*name,char const*content)
{
	packet *dst = external_protocol_new_packet(MSG_CHAT_HORN);
		
	packet_write_str(dst,guid);		
	packet_write(dst,(char *)&faction,sizeof(uint8));
	packet_write_str(dst,name);		
	packet_write_str(dst,content);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����*/
__INLINE__ int Call_chat_notice (Delegate_Sendpackt SendPacket ,uint32 id,char const*content,char const*data)
{
	packet *dst = external_protocol_new_packet(MSG_CHAT_NOTICE);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	packet_write_str(dst,content);		
	packet_write_str(dst,data);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ѯ�����Ϣ*/
__INLINE__ int Call_query_player_info (Delegate_Sendpackt SendPacket ,char const*guid,uint32 flag,uint32 callback_id)
{
	packet *dst = external_protocol_new_packet(CMSG_QUERY_PLAYER_INFO);
		
	packet_write_str(dst,guid);		
	packet_write(dst,(char *)&flag,sizeof(uint32));
	packet_write(dst,(char *)&callback_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ѯ��Ϣ�������*/
__INLINE__ int Call_query_result_update_object (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_QUERY_RESULT_UPDATE_OBJECT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ���*/
__INLINE__ int Call_receive_gift_packs (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_RECEIVE_GIFT_PACKS);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ͼ�������*/
__INLINE__ int Call_map_update_object (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_MAP_UPDATE_OBJECT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ս����Ϣbinlog*/
__INLINE__ int Call_fighting_info_update_object (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_FIGHTING_INFO_UPDATE_OBJECT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ս����Ϣbinlog*/
__INLINE__ int Call_fighting_info_update_object_2 (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_FIGHTING_INFO_UPDATE_OBJECT_2);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���븱��*/
__INLINE__ int Call_instance_enter (Delegate_Sendpackt SendPacket ,uint32 instance_id)
{
	packet *dst = external_protocol_new_packet(CMSG_INSTANCE_ENTER);
		
	packet_write(dst,(char *)&instance_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����˷��͸���������һ�׶�ָ��*/
__INLINE__ int Call_instance_next_state (Delegate_Sendpackt SendPacket ,uint16 level,uint32 param)
{
	packet *dst = external_protocol_new_packet(CMSG_INSTANCE_NEXT_STATE);
		
	packet_write(dst,(char *)&level,sizeof(uint16));
	packet_write(dst,(char *)&param,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����˳�*/
__INLINE__ int Call_instance_exit (Delegate_Sendpackt SendPacket ,uint32 reserve)
{
	packet *dst = external_protocol_new_packet(CMSG_INSTANCE_EXIT);
		
	packet_write(dst,(char *)&reserve,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ʱ���ȡ*/
__INLINE__ int Call_limit_activity_receive (Delegate_Sendpackt SendPacket ,uint32 id,uint32 type)
{
	packet *dst = external_protocol_new_packet(CMSG_LIMIT_ACTIVITY_RECEIVE);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	packet_write(dst,(char *)&type,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɱ����~~��������*/
__INLINE__ int Call_kill_man (Delegate_Sendpackt SendPacket ,char const*killer,char const*killer_name,char const*victim,char const*victim_name)
{
	packet *dst = external_protocol_new_packet(SMSG_KILL_MAN);
		
	packet_write_str(dst,killer);		
	packet_write_str(dst,killer_name);		
	packet_write_str(dst,victim);		
	packet_write_str(dst,victim_name);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_player_upgrade (Delegate_Sendpackt SendPacket ,uint32 guid)
{
	packet *dst = external_protocol_new_packet(SMSG_PLAYER_UPGRADE);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ֿ��Ǯ*/
__INLINE__ int Call_warehouse_save_money (Delegate_Sendpackt SendPacket ,int32 money,int32 money_gold,int32 money_bills)
{
	packet *dst = external_protocol_new_packet(CMSG_WAREHOUSE_SAVE_MONEY);
		
	packet_write(dst,(char *)&money,sizeof(int32));
	packet_write(dst,(char *)&money_gold,sizeof(int32));
	packet_write(dst,(char *)&money_bills,sizeof(int32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ֿ�ȡǮ*/
__INLINE__ int Call_warehouse_take_money (Delegate_Sendpackt SendPacket ,int32 money,int32 money_gold,int32 money_bills)
{
	packet *dst = external_protocol_new_packet(CMSG_WAREHOUSE_TAKE_MONEY);
		
	packet_write(dst,(char *)&money,sizeof(int32));
	packet_write(dst,(char *)&money_gold,sizeof(int32));
	packet_write(dst,(char *)&money_bills,sizeof(int32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʹ��Ԫ������ĳ��*/
__INLINE__ int Call_use_gold_opt (Delegate_Sendpackt SendPacket ,uint8 type,char const*param)
{
	packet *dst = external_protocol_new_packet(CMSG_USE_GOLD_OPT);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write_str(dst,param);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʹ��ͭǮ����ĳ��*/
__INLINE__ int Call_use_silver_opt (Delegate_Sendpackt SendPacket ,uint8 type)
{
	packet *dst = external_protocol_new_packet(CMSG_USE_SILVER_OPT);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��̨����*/
__INLINE__ int Call_gm_rightfloat (Delegate_Sendpackt SendPacket ,uint32 id,uint32 end_time,uint32 zone1,uint32 zone2,uint32 zone3,char const*subject,char const*content,char const*link,uint8 mode)
{
	packet *dst = external_protocol_new_packet(SMSG_GM_RIGHTFLOAT);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	packet_write(dst,(char *)&end_time,sizeof(uint32));
	packet_write(dst,(char *)&zone1,sizeof(uint32));
	packet_write(dst,(char *)&zone2,sizeof(uint32));
	packet_write(dst,(char *)&zone3,sizeof(uint32));
	packet_write_str(dst,subject);		
	packet_write_str(dst,content);		
	packet_write_str(dst,link);		
	packet_write(dst,(char *)&mode,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɾ��ĳ����̨����*/
__INLINE__ int Call_del_gm_rightfloat (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(SMSG_DEL_GM_RIGHTFLOAT);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*Ӧ�÷�ͬ��ʱ��*/
__INLINE__ int Call_sync_mstime_app (Delegate_Sendpackt SendPacket ,uint32 mstime_now,uint32 time_now,uint32 open_time)
{
	packet *dst = external_protocol_new_packet(MSG_SYNC_MSTIME_APP);
		
	packet_write(dst,(char *)&mstime_now,sizeof(uint32));
	packet_write(dst,(char *)&time_now,sizeof(uint32));
	packet_write(dst,(char *)&open_time,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��Ҵ�ĳ������*/
__INLINE__ int Call_open_window (Delegate_Sendpackt SendPacket ,uint32 window_type)
{
	packet *dst = external_protocol_new_packet(CMSG_OPEN_WINDOW);
		
	packet_write(dst,(char *)&window_type,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���Բ���*/
__INLINE__ int Call_player_gag (Delegate_Sendpackt SendPacket ,char const*player_id,uint32 end_time,char const*content)
{
	packet *dst = external_protocol_new_packet(CMSG_PLAYER_GAG);
		
	packet_write_str(dst,player_id);		
	packet_write(dst,(char *)&end_time,sizeof(uint32));
	packet_write_str(dst,content);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���˲���*/
__INLINE__ int Call_player_kicking (Delegate_Sendpackt SendPacket ,char const*player_id)
{
	packet *dst = external_protocol_new_packet(CMSG_PLAYER_KICKING);
		
	packet_write_str(dst,player_id);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�Ϸ�֪ͨ*/
__INLINE__ int Call_merge_server_msg (Delegate_Sendpackt SendPacket ,char const*merge_host,uint32 merge_port,char const*merge_key,uint32 merge_type,uint32 reserve,uint32 reserve2)
{
	packet *dst = external_protocol_new_packet(SMSG_MERGE_SERVER_MSG);
		
	packet_write_str(dst,merge_host);		
	packet_write(dst,(char *)&merge_port,sizeof(uint32));
	packet_write_str(dst,merge_key);		
	packet_write(dst,(char *)&merge_type,sizeof(uint32));
	packet_write(dst,(char *)&reserve,sizeof(uint32));
	packet_write(dst,(char *)&reserve2,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ������Ϣ*/
__INLINE__ int Call_rank_list_query (Delegate_Sendpackt SendPacket ,uint32 call_back_id,uint8 rank_list_type,uint16 start_index,uint16 end_index)
{
	packet *dst = external_protocol_new_packet(CMSG_RANK_LIST_QUERY);
		
	packet_write(dst,(char *)&call_back_id,sizeof(uint32));
	packet_write(dst,(char *)&rank_list_type,sizeof(uint8));
	packet_write(dst,(char *)&start_index,sizeof(uint16));
	packet_write(dst,(char *)&end_index,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ͻ��˻�ȡ���а񷵻ؽ��*/
__INLINE__ int Call_rank_list_query_result (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_RANK_LIST_QUERY_RESULT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ͻ����ȸ�����ģ����ȡuint*/
__INLINE__ int Call_client_update_scened (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_CLIENT_UPDATE_SCENED);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ֵ��*/
__INLINE__ int Call_num_lua (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_NUM_LUA);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ս��Ʒʰȡ*/
__INLINE__ int Call_loot_select (Delegate_Sendpackt SendPacket ,uint16 x,uint16 y)
{
	packet *dst = external_protocol_new_packet(CMSG_LOOT_SELECT);
		
	packet_write(dst,(char *)&x,sizeof(uint16));
	packet_write(dst,(char *)&y,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*֪ͨ��¼������Ҵ�����Ϸ��*/
__INLINE__ int Call_goback_to_game_server (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_GOBACK_TO_GAME_SERVER);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ͻ��˰ѱ�����Ա���ݴ���������*/
__INLINE__ int Call_world_war_CS_player_info (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WORLD_WAR_CS_PLAYER_INFO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��Ҽ�������뿪ĳ������*/
__INLINE__ int Call_join_or_leave_server (Delegate_Sendpackt SendPacket ,uint8 join_or_leave,uint8 server_type,uint32 server_pid,uint32 server_fd,uint32 time)
{
	packet *dst = external_protocol_new_packet(SMSG_JOIN_OR_LEAVE_SERVER);
		
	packet_write(dst,(char *)&join_or_leave,sizeof(uint8));
	packet_write(dst,(char *)&server_type,sizeof(uint8));
	packet_write(dst,(char *)&server_pid,sizeof(uint32));
	packet_write(dst,(char *)&server_fd,sizeof(uint32));
	packet_write(dst,(char *)&time,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ͻ�����������Ա����*/
__INLINE__ int Call_world_war_SC_player_info (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(MSG_WORLD_WAR_SC_PLAYER_INFO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ͻ��˶�����Ϣ*/
__INLINE__ int Call_clientSubscription (Delegate_Sendpackt SendPacket ,uint32 guid)
{
	packet *dst = external_protocol_new_packet(MSG_CLIENTSUBSCRIPTION);
		
	packet_write(dst,(char *)&guid,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������·�lua�ű�*/
__INLINE__ int Call_lua_script (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_LUA_SCRIPT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɫ������Ϣ*/
__INLINE__ int Call_char_update_info (Delegate_Sendpackt SendPacket , char_create_info *info)
{
	packet *dst = external_protocol_new_packet(CMSG_CHAR_UPDATE_INFO);
		
	packet_write(dst,(char*)info,sizeof(char_create_info));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*֪ͨ�ͻ��˹۲��ߵ��ӽ�*/
__INLINE__ int Call_notice_watcher_map_info (Delegate_Sendpackt SendPacket ,char const*wather_guid,uint32 map_id,uint32 instance_id)
{
	packet *dst = external_protocol_new_packet(SMSG_NOTICE_WATCHER_MAP_INFO);
		
	packet_write_str(dst,wather_guid);		
	packet_write(dst,(char *)&map_id,sizeof(uint32));
	packet_write(dst,(char *)&instance_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ͻ��˶��Ķ�����Ϣ*/
__INLINE__ int Call_modify_watch (Delegate_Sendpackt SendPacket ,uint8 opt,uint32 cid,char const*key)
{
	packet *dst = external_protocol_new_packet(CMSG_MODIFY_WATCH);
		
	packet_write(dst,(char *)&opt,sizeof(uint8));
	packet_write(dst,(char *)&cid,sizeof(uint32));
	packet_write_str(dst,key);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_kuafu_chuansong (Delegate_Sendpackt SendPacket ,char const*str_data,char const*watcher_guid,uint32 reserve)
{
	packet *dst = external_protocol_new_packet(CMSG_KUAFU_CHUANSONG);
		
	packet_write_str(dst,str_data);		
	packet_write_str(dst,watcher_guid);		
	packet_write(dst,(char *)&reserve,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ʾ��ǰװ��*/
__INLINE__ int Call_show_suit (Delegate_Sendpackt SendPacket ,uint8 position)
{
	packet *dst = external_protocol_new_packet(CMSG_SHOW_SUIT);
		
	packet_write(dst,(char *)&position,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ʾ��ǰ����*/
__INLINE__ int Call_show_position (Delegate_Sendpackt SendPacket ,uint8 channel)
{
	packet *dst = external_protocol_new_packet(CMSG_SHOW_POSITION);
		
	packet_write(dst,(char *)&channel,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*Ԫ������*/
__INLINE__ int Call_gold_respawn (Delegate_Sendpackt SendPacket ,uint8 useGold)
{
	packet *dst = external_protocol_new_packet(CMSG_GOLD_RESPAWN);
		
	packet_write(dst,(char *)&useGold,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*Ұ����������ʱ*/
__INLINE__ int Call_field_death_cooldown (Delegate_Sendpackt SendPacket ,uint8 type,uint32 value,char const*killername,uint16 cooldown,char const*params)
{
	packet *dst = external_protocol_new_packet(SMSG_FIELD_DEATH_COOLDOWN);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write(dst,(char *)&value,sizeof(uint32));
	packet_write_str(dst,killername);		
	packet_write(dst,(char *)&cooldown,sizeof(uint16));
	packet_write_str(dst,params);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�̳ǹ���*/
__INLINE__ int Call_mall_buy (Delegate_Sendpackt SendPacket ,uint32 id,uint32 count,uint32 time)
{
	packet *dst = external_protocol_new_packet(CMSG_MALL_BUY);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	packet_write(dst,(char *)&count,sizeof(uint32));
	packet_write(dst,(char *)&time,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ǿ��*/
__INLINE__ int Call_strength (Delegate_Sendpackt SendPacket ,uint8 part)
{
	packet *dst = external_protocol_new_packet(CMSG_STRENGTH);
		
	packet_write(dst,(char *)&part,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ǿ���ɹ�*/
__INLINE__ int Call_strength_success (Delegate_Sendpackt SendPacket ,uint16 level)
{
	packet *dst = external_protocol_new_packet(SMSG_STRENGTH_SUCCESS);
		
	packet_write(dst,(char *)&level,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ǿ�ƽ���*/
__INLINE__ int Call_forceInto (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_FORCEINTO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_create_faction (Delegate_Sendpackt SendPacket ,char const*name,uint8 icon)
{
	packet *dst = external_protocol_new_packet(CMSG_CREATE_FACTION);
		
	packet_write_str(dst,name);		
	packet_write(dst,(char *)&icon,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_faction_upgrade (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_FACTION_UPGRADE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������*/
__INLINE__ int Call_faction_join (Delegate_Sendpackt SendPacket ,char const*id)
{
	packet *dst = external_protocol_new_packet(CMSG_FACTION_JOIN);
		
	packet_write_str(dst,id);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������������*/
__INLINE__ int Call_raise_base_spell (Delegate_Sendpackt SendPacket ,uint8 raiseType,uint16 spellId)
{
	packet *dst = external_protocol_new_packet(CMSG_RAISE_BASE_SPELL);
		
	packet_write(dst,(char *)&raiseType,sizeof(uint8));
	packet_write(dst,(char *)&spellId,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������׷�ŭ����*/
__INLINE__ int Call_upgrade_anger_spell (Delegate_Sendpackt SendPacket ,uint16 spellId)
{
	packet *dst = external_protocol_new_packet(CMSG_UPGRADE_ANGER_SPELL);
		
	packet_write(dst,(char *)&spellId,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������������*/
__INLINE__ int Call_raise_mount (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_RAISE_MOUNT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������������*/
__INLINE__ int Call_upgrade_mount (Delegate_Sendpackt SendPacket ,uint8 useItem)
{
	packet *dst = external_protocol_new_packet(CMSG_UPGRADE_MOUNT);
		
	packet_write(dst,(char *)&useItem,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����һ����������*/
__INLINE__ int Call_upgrade_mount_one_step (Delegate_Sendpackt SendPacket ,uint8 useItem)
{
	packet *dst = external_protocol_new_packet(CMSG_UPGRADE_MOUNT_ONE_STEP);
		
	packet_write(dst,(char *)&useItem,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������û�����*/
__INLINE__ int Call_illusion_mount_active (Delegate_Sendpackt SendPacket ,uint16 illuId)
{
	packet *dst = external_protocol_new_packet(CMSG_ILLUSION_MOUNT_ACTIVE);
		
	packet_write(dst,(char *)&illuId,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����û�����*/
__INLINE__ int Call_illusion_mount (Delegate_Sendpackt SendPacket ,uint16 illuId)
{
	packet *dst = external_protocol_new_packet(CMSG_ILLUSION_MOUNT);
		
	packet_write(dst,(char *)&illuId,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_ride_mount (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_RIDE_MOUNT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*grid�е�unit��Ծ*/
__INLINE__ int Call_grid_unit_jump (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_GRID_UNIT_JUMP);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ʯ*/
__INLINE__ int Call_gem (Delegate_Sendpackt SendPacket ,uint8 part)
{
	packet *dst = external_protocol_new_packet(CMSG_GEM);
		
	packet_write(dst,(char *)&part,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����л�ģʽ*/
__INLINE__ int Call_change_battle_mode (Delegate_Sendpackt SendPacket ,uint8 mode)
{
	packet *dst = external_protocol_new_packet(CMSG_CHANGE_BATTLE_MODE);
		
	packet_write(dst,(char *)&mode,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ƽģʽCD*/
__INLINE__ int Call_peace_mode_cd (Delegate_Sendpackt SendPacket ,uint8 mode)
{
	packet *dst = external_protocol_new_packet(SMSG_PEACE_MODE_CD);
		
	packet_write(dst,(char *)&mode,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_divine_active (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_DIVINE_ACTIVE);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_divine_uplev (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_DIVINE_UPLEV);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�л����*/
__INLINE__ int Call_divine_switch (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_DIVINE_SWITCH);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������Ծ*/
__INLINE__ int Call_jump_start (Delegate_Sendpackt SendPacket ,uint16 pos_x,uint16 pos_y)
{
	packet *dst = external_protocol_new_packet(CMSG_JUMP_START);
		
	packet_write(dst,(char *)&pos_x,sizeof(uint16));
	packet_write(dst,(char *)&pos_y,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������vip����*/
__INLINE__ int Call_enter_vip_instance (Delegate_Sendpackt SendPacket ,uint16 id,uint8 hard)
{
	packet *dst = external_protocol_new_packet(CMSG_ENTER_VIP_INSTANCE);
		
	packet_write(dst,(char *)&id,sizeof(uint16));
	packet_write(dst,(char *)&hard,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ɨ��vip����*/
__INLINE__ int Call_sweep_vip_instance (Delegate_Sendpackt SendPacket ,uint16 id)
{
	packet *dst = external_protocol_new_packet(CMSG_SWEEP_VIP_INSTANCE);
		
	packet_write(dst,(char *)&id,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���йһ�*/
__INLINE__ int Call_hang_up (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_HANG_UP);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���йһ�����*/
__INLINE__ int Call_hang_up_setting (Delegate_Sendpackt SendPacket ,uint32 value0,uint32 value1,uint32 value2,uint32 value3)
{
	packet *dst = external_protocol_new_packet(CMSG_HANG_UP_SETTING);
		
	packet_write(dst,(char *)&value0,sizeof(uint32));
	packet_write(dst,(char *)&value1,sizeof(uint32));
	packet_write(dst,(char *)&value2,sizeof(uint32));
	packet_write(dst,(char *)&value3,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����������������*/
__INLINE__ int Call_enter_trial_instance (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_ENTER_TRIAL_INSTANCE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɨ������������*/
__INLINE__ int Call_sweep_trial_instance (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_SWEEP_TRIAL_INSTANCE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������*/
__INLINE__ int Call_reset_trial_instance (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_RESET_TRIAL_INSTANCE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɨ����������*/
__INLINE__ int Call_sweep_instance_reward (Delegate_Sendpackt SendPacket ,uint8 inst_sub_type,uint8 data1,uint8 data2,uint8 data3,const vector< item_reward_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_SWEEP_INSTANCE_REWARD);
		
	packet_write(dst,(char *)&inst_sub_type,sizeof(uint8));
	packet_write(dst,(char *)&data1,sizeof(uint8));
	packet_write(dst,(char *)&data2,sizeof(uint8));
	packet_write(dst,(char *)&data3,sizeof(uint8));
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ؽ�����*/
__INLINE__ int Call_reenter_instance (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_REENTER_INSTANCE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������Ϣ*/
__INLINE__ int Call_merry_go_round (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_MERRY_GO_ROUND);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��Ӻ���*/
__INLINE__ int Call_social_add_friend (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_ADD_FRIEND);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ͬ����Ӻ���*/
__INLINE__ int Call_social_sureadd_friend (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_SUREADD_FRIEND);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_social_gift_friend (Delegate_Sendpackt SendPacket ,char const*guid,const vector< item_reward_info > &gift )
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_GIFT_FRIEND);
		
	packet_write_str(dst,guid);		
	*dst << gift;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�Ƽ������б�*/
__INLINE__ int Call_social_recommend_friend (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_RECOMMEND_FRIEND);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�Ƽ������б�*/
__INLINE__ int Call_social_get_recommend_friend (Delegate_Sendpackt SendPacket ,const vector< social_friend_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_SOCIAL_GET_RECOMMEND_FRIEND);
		
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����*/
__INLINE__ int Call_social_revenge_enemy (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_REVENGE_ENEMY);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɾ������*/
__INLINE__ int Call_social_del_friend (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_DEL_FRIEND);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�س�*/
__INLINE__ int Call_teleport_main_city (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_TELEPORT_MAIN_CITY);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ͬƵ������*/
__INLINE__ int Call_chat_by_channel (Delegate_Sendpackt SendPacket ,uint8 channel,char const*content)
{
	packet *dst = external_protocol_new_packet(CMSG_CHAT_BY_CHANNEL);
		
	packet_write(dst,(char *)&channel,sizeof(uint8));
	packet_write_str(dst,content);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_send_chat (Delegate_Sendpackt SendPacket ,uint8 channel,char const*guid,uint8 title,char const*name,uint8 vip,uint8 zs,uint8 lvl,uint8 gender,char const*content,char const*to_guid,char const*faction_guid)
{
	packet *dst = external_protocol_new_packet(SMSG_SEND_CHAT);
		
	packet_write(dst,(char *)&channel,sizeof(uint8));
	packet_write_str(dst,guid);		
	packet_write(dst,(char *)&title,sizeof(uint8));
	packet_write_str(dst,name);		
	packet_write(dst,(char *)&vip,sizeof(uint8));
	packet_write(dst,(char *)&zs,sizeof(uint8));
	packet_write(dst,(char *)&lvl,sizeof(uint8));
	packet_write(dst,(char *)&gender,sizeof(uint8));
	packet_write_str(dst,content);		
	packet_write_str(dst,to_guid);		
	packet_write_str(dst,faction_guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������б�*/
__INLINE__ int Call_social_clear_apply (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_CLEAR_APPLY);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���þܾ�������Ϣ*/
__INLINE__ int Call_msg_decline (Delegate_Sendpackt SendPacket ,uint32 value0,uint32 value1)
{
	packet *dst = external_protocol_new_packet(CMSG_MSG_DECLINE);
		
	packet_write(dst,(char *)&value0,sizeof(uint32));
	packet_write(dst,(char *)&value1,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����б�*/
__INLINE__ int Call_faction_get_list_result (Delegate_Sendpackt SendPacket ,const vector< faction_info > &list ,uint8 curpag,uint8 maxpag)
{
	packet *dst = external_protocol_new_packet(SMSG_FACTION_GET_LIST_RESULT);
		
	*dst << list;
	packet_write(dst,(char *)&curpag,sizeof(uint8));
	packet_write(dst,(char *)&maxpag,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ�����б�*/
__INLINE__ int Call_faction_getlist (Delegate_Sendpackt SendPacket ,uint8 page,uint8 num,uint8 grep)
{
	packet *dst = external_protocol_new_packet(CMSG_FACTION_GETLIST);
		
	packet_write(dst,(char *)&page,sizeof(uint8));
	packet_write(dst,(char *)&num,sizeof(uint8));
	packet_write(dst,(char *)&grep,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ɹ���*/
__INLINE__ int Call_faction_manager (Delegate_Sendpackt SendPacket ,uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2)
{
	packet *dst = external_protocol_new_packet(CMSG_FACTION_MANAGER);
		
	packet_write(dst,(char *)&opt_type,sizeof(uint8));
	packet_write(dst,(char *)&reserve_int1,sizeof(uint16));
	packet_write(dst,(char *)&reserve_int2,sizeof(uint16));
	packet_write_str(dst,reserve_str1);		
	packet_write_str(dst,reserve_str2);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ɳ�Ա����*/
__INLINE__ int Call_faction_member_operate (Delegate_Sendpackt SendPacket ,uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2)
{
	packet *dst = external_protocol_new_packet(CMSG_FACTION_MEMBER_OPERATE);
		
	packet_write(dst,(char *)&opt_type,sizeof(uint8));
	packet_write(dst,(char *)&reserve_int1,sizeof(uint16));
	packet_write(dst,(char *)&reserve_int2,sizeof(uint16));
	packet_write_str(dst,reserve_str1);		
	packet_write_str(dst,reserve_str2);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ټ������*/
__INLINE__ int Call_faction_fast_join (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_FACTION_FAST_JOIN);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ͨ��������Ӻ���*/
__INLINE__ int Call_social_add_friend_byname (Delegate_Sendpackt SendPacket ,char const*name)
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_ADD_FRIEND_BYNAME);
		
	packet_write_str(dst,name);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ʼ�*/
__INLINE__ int Call_read_mail (Delegate_Sendpackt SendPacket ,uint16 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_READ_MAIL);
		
	packet_write(dst,(char *)&indx,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ�ʼ�*/
__INLINE__ int Call_pick_mail (Delegate_Sendpackt SendPacket ,uint16 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_PICK_MAIL);
		
	packet_write(dst,(char *)&indx,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɾ���ʼ�*/
__INLINE__ int Call_remove_mail (Delegate_Sendpackt SendPacket ,uint16 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_REMOVE_MAIL);
		
	packet_write(dst,(char *)&indx,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*һ����ȡ�ʼ�*/
__INLINE__ int Call_pick_mail_one_step (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_PICK_MAIL_ONE_STEP);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*һ��ɾ���ʼ�*/
__INLINE__ int Call_remove_mail_one_step (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_REMOVE_MAIL_ONE_STEP);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ĳ��*/
__INLINE__ int Call_block_chat (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_BLOCK_CHAT);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ȡ������*/
__INLINE__ int Call_cancel_block_chat (Delegate_Sendpackt SendPacket ,uint8 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_CANCEL_BLOCK_CHAT);
		
	packet_write(dst,(char *)&indx,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʹ����Ҫ�㲥����Ϸ����*/
__INLINE__ int Call_use_broadcast_gameobject (Delegate_Sendpackt SendPacket ,uint32 target)
{
	packet *dst = external_protocol_new_packet(CMSG_USE_BROADCAST_GAMEOBJECT);
		
	packet_write(dst,(char *)&target,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����BOSS����*/
__INLINE__ int Call_world_boss_enroll (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WORLD_BOSS_ENROLL);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����BOSS��ս*/
__INLINE__ int Call_world_boss_fight (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WORLD_BOSS_FIGHT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����*/
__INLINE__ int Call_change_line (Delegate_Sendpackt SendPacket ,uint32 lineNo)
{
	packet *dst = external_protocol_new_packet(CMSG_CHANGE_LINE);
		
	packet_write(dst,(char *)&lineNo,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*roll����BOSS����*/
__INLINE__ int Call_roll_world_boss_treasure (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_ROLL_WORLD_BOSS_TREASURE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*roll����*/
__INLINE__ int Call_roll_result (Delegate_Sendpackt SendPacket ,uint8 point,char const*name,uint8 isHighest,uint32 timestamp,uint8 rollid)
{
	packet *dst = external_protocol_new_packet(SMSG_ROLL_RESULT);
		
	packet_write(dst,(char *)&point,sizeof(uint8));
	packet_write_str(dst,name);		
	packet_write(dst,(char *)&isHighest,sizeof(uint8));
	packet_write(dst,(char *)&timestamp,sizeof(uint32));
	packet_write(dst,(char *)&rollid,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ǰBOSS�˺�����*/
__INLINE__ int Call_boss_rank (Delegate_Sendpackt SendPacket ,uint8 rankType,const vector< rank_info > &rankList ,uint8 mine)
{
	packet *dst = external_protocol_new_packet(SMSG_BOSS_RANK);
		
	packet_write(dst,(char *)&rankType,sizeof(uint8));
	*dst << rankList;
	packet_write(dst,(char *)&mine,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���а����*/
__INLINE__ int Call_rank_add_like (Delegate_Sendpackt SendPacket ,uint8 type,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_RANK_ADD_LIKE);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���а���޽��*/
__INLINE__ int Call_rank_add_like_result (Delegate_Sendpackt SendPacket ,uint8 type,char const*guid,uint32 num)
{
	packet *dst = external_protocol_new_packet(SMSG_RANK_ADD_LIKE_RESULT);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write_str(dst,guid);		
	packet_write(dst,(char *)&num,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������Դ����*/
__INLINE__ int Call_res_instance_enter (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_RES_INSTANCE_ENTER);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɨ����Դ����*/
__INLINE__ int Call_res_instance_sweep (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_RES_INSTANCE_SWEEP);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�鿴����ͼ�ķ��ߺ�*/
__INLINE__ int Call_show_map_line (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_SHOW_MAP_LINE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ر���ͼ�ķ��ߺ���Ϣ*/
__INLINE__ int Call_send_map_line (Delegate_Sendpackt SendPacket ,const vector< line_info > &info )
{
	packet *dst = external_protocol_new_packet(SMSG_SEND_MAP_LINE);
		
	*dst << info;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ý�����ʾ*/
__INLINE__ int Call_item_notice (Delegate_Sendpackt SendPacket ,uint8 showType,const vector< item_reward_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_ITEM_NOTICE);
		
	packet_write(dst,(char *)&showType,sizeof(uint8));
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���͵�ĳ�������ͼ*/
__INLINE__ int Call_teleport_map (Delegate_Sendpackt SendPacket ,uint32 mapid,uint32 lineNo)
{
	packet *dst = external_protocol_new_packet(CMSG_TELEPORT_MAP);
		
	packet_write(dst,(char *)&mapid,sizeof(uint32));
	packet_write(dst,(char *)&lineNo,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���͵�Ұ��boss�Ա�*/
__INLINE__ int Call_teleport_field_boss (Delegate_Sendpackt SendPacket ,uint32 mapid,uint32 lineNo)
{
	packet *dst = external_protocol_new_packet(CMSG_TELEPORT_FIELD_BOSS);
		
	packet_write(dst,(char *)&mapid,sizeof(uint32));
	packet_write(dst,(char *)&lineNo,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��Ծ�Ƚ���*/
__INLINE__ int Call_get_activity_reward (Delegate_Sendpackt SendPacket ,uint8 id,uint8 vip)
{
	packet *dst = external_protocol_new_packet(CMSG_GET_ACTIVITY_REWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	packet_write(dst,(char *)&vip,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ɾͽ���*/
__INLINE__ int Call_get_achieve_reward (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_GET_ACHIEVE_REWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ܳɾͽ���*/
__INLINE__ int Call_get_achieve_all_reward (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_GET_ACHIEVE_ALL_REWARD);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*װ���ƺ�*/
__INLINE__ int Call_set_title (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_SET_TITLE);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ʼ���ƺ�*/
__INLINE__ int Call_init_title (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_INIT_TITLE);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ�׳佱��*/
__INLINE__ int Call_welfare_shouchong_reward (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_SHOUCHONG_REWARD);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ÿ��ǩ������*/
__INLINE__ int Call_welfare_checkin (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_CHECKIN);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ۻ�ǩ������*/
__INLINE__ int Call_welfare_checkin_all (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_CHECKIN_ALL);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ǩ����*/
__INLINE__ int Call_welfare_checkin_getback (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_CHECKIN_GETBACK);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ȼ�����*/
__INLINE__ int Call_welfare_level (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_LEVEL);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��һؽ���*/
__INLINE__ int Call_welfare_active_getback (Delegate_Sendpackt SendPacket ,uint8 id,uint8 best,uint16 num)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_ACTIVE_GETBACK);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	packet_write(dst,(char *)&best,sizeof(uint8));
	packet_write(dst,(char *)&num,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ������*/
__INLINE__ int Call_pick_quest_reward (Delegate_Sendpackt SendPacket ,uint8 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_PICK_QUEST_REWARD);
		
	packet_write(dst,(char *)&indx,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��npc�Ի�*/
__INLINE__ int Call_talk_with_npc (Delegate_Sendpackt SendPacket ,uint16 entry,uint16 questId)
{
	packet *dst = external_protocol_new_packet(CMSG_TALK_WITH_NPC);
		
	packet_write(dst,(char *)&entry,sizeof(uint16));
	packet_write(dst,(char *)&questId,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʹ��������Ʒ*/
__INLINE__ int Call_use_virtual_item (Delegate_Sendpackt SendPacket ,uint16 entry)
{
	packet *dst = external_protocol_new_packet(CMSG_USE_VIRTUAL_ITEM);
		
	packet_write(dst,(char *)&entry,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ�����½ڽ���*/
__INLINE__ int Call_pick_quest_chapter_reward (Delegate_Sendpackt SendPacket ,uint8 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_PICK_QUEST_CHAPTER_REWARD);
		
	packet_write(dst,(char *)&indx,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*3v3���ƥ��*/
__INLINE__ int Call_kuafu_3v3_match (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_KUAFU_3V3_MATCH);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����ʼƥ��*/
__INLINE__ int Call_kuafu_match_start (Delegate_Sendpackt SendPacket ,uint8 indx)
{
	packet *dst = external_protocol_new_packet(SMSG_KUAFU_MATCH_START);
		
	packet_write(dst,(char *)&indx,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*3v3�������*/
__INLINE__ int Call_kuafu_3v3_buytimes (Delegate_Sendpackt SendPacket ,uint8 num)
{
	packet *dst = external_protocol_new_packet(CMSG_KUAFU_3V3_BUYTIMES);
		
	packet_write(dst,(char *)&num,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*3v3ÿ�ջ�Ծ����*/
__INLINE__ int Call_kuafu_3v3_dayreward (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_KUAFU_3V3_DAYREWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����3v3���а�*/
__INLINE__ int Call_kuafu_3v3_getranlist (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_KUAFU_3V3_GETRANLIST);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*3v3���а����б�*/
__INLINE__ int Call_kuafu_3v3_ranlist (Delegate_Sendpackt SendPacket ,char const*list)
{
	packet *dst = external_protocol_new_packet(SMSG_KUAFU_3V3_RANLIST);
		
	packet_write_str(dst,list);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������н����б�*/
__INLINE__ int Call_welfare_getalllist_getback (Delegate_Sendpackt SendPacket ,uint8 best)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_GETALLLIST_GETBACK);
		
	packet_write(dst,(char *)&best,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����б�*/
__INLINE__ int Call_welfare_rewardlist_getback (Delegate_Sendpackt SendPacket ,char const*list,char const*cost)
{
	packet *dst = external_protocol_new_packet(SMSG_WELFARE_REWARDLIST_GETBACK);
		
	packet_write_str(dst,list);		
	packet_write_str(dst,cost);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*һ����ȡ���и���*/
__INLINE__ int Call_welfare_getall_getback (Delegate_Sendpackt SendPacket ,uint8 best)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_GETALL_GETBACK);
		
	packet_write(dst,(char *)&best,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����3v3���а��Լ�������*/
__INLINE__ int Call_kuafu_3v3_getmyrank (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_KUAFU_3V3_GETMYRANK);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*3v3���а��Լ������ν��*/
__INLINE__ int Call_kuafu_3v3_myrank (Delegate_Sendpackt SendPacket ,uint8 rank)
{
	packet *dst = external_protocol_new_packet(SMSG_KUAFU_3V3_MYRANK);
		
	packet_write(dst,(char *)&rank,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɱ����*/
__INLINE__ int Call_kuafu_3v3_kill_detail (Delegate_Sendpackt SendPacket ,uint32 indx1,uint32 indx2)
{
	packet *dst = external_protocol_new_packet(SMSG_KUAFU_3V3_KILL_DETAIL);
		
	packet_write(dst,(char *)&indx1,sizeof(uint32));
	packet_write(dst,(char *)&indx2,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ƥ��ȴ�����*/
__INLINE__ int Call_kuafu_3v3_wait_info (Delegate_Sendpackt SendPacket ,const vector< wait_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_KUAFU_3V3_WAIT_INFO);
		
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ȡ��ƥ��*/
__INLINE__ int Call_kuafu_3v3_cancel_match (Delegate_Sendpackt SendPacket ,uint32 type)
{
	packet *dst = external_protocol_new_packet(MSG_KUAFU_3V3_CANCEL_MATCH);
		
	packet_write(dst,(char *)&type,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ƥ�䵽��&���ܻ��߾ܾ�*/
__INLINE__ int Call_kuafu_3v3_match_oper (Delegate_Sendpackt SendPacket ,uint32 oper)
{
	packet *dst = external_protocol_new_packet(CMSG_KUAFU_3V3_MATCH_OPER);
		
	packet_write(dst,(char *)&oper,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ܾ�����*/
__INLINE__ int Call_kuafu_3v3_decline_match (Delegate_Sendpackt SendPacket ,uint32 type)
{
	packet *dst = external_protocol_new_packet(SMSG_KUAFU_3V3_DECLINE_MATCH);
		
	packet_write(dst,(char *)&type,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ɸ��ᱦ���ƥ��*/
__INLINE__ int Call_kuafu_xianfu_match (Delegate_Sendpackt SendPacket ,uint8 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_KUAFU_XIANFU_MATCH);
		
	packet_write(dst,(char *)&indx,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������ƥ��ȴ�*/
__INLINE__ int Call_kuafu_match_wait (Delegate_Sendpackt SendPacket ,uint8 type,uint8 target,uint8 count,uint32 data,char const*params)
{
	packet *dst = external_protocol_new_packet(SMSG_KUAFU_MATCH_WAIT);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write(dst,(char *)&target,sizeof(uint8));
	packet_write(dst,(char *)&count,sizeof(uint8));
	packet_write(dst,(char *)&data,sizeof(uint32));
	packet_write_str(dst,params);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ɸ��ᱦС��ͼ��Ϣ*/
__INLINE__ int Call_kuafu_xianfu_minimap_info (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_KUAFU_XIANFU_MINIMAP_INFO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����ɸ�����ȯ*/
__INLINE__ int Call_buy_xianfu_item (Delegate_Sendpackt SendPacket ,uint8 type,uint8 indx,uint16 count)
{
	packet *dst = external_protocol_new_packet(CMSG_BUY_XIANFU_ITEM);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write(dst,(char *)&indx,sizeof(uint8));
	packet_write(dst,(char *)&count,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_xianfu_random_respawn (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_XIANFU_RANDOM_RESPAWN);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����̨��ս*/
__INLINE__ int Call_doujiantai_fight (Delegate_Sendpackt SendPacket ,uint16 rank)
{
	packet *dst = external_protocol_new_packet(CMSG_DOUJIANTAI_FIGHT);
		
	packet_write(dst,(char *)&rank,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����̨�������*/
__INLINE__ int Call_doujiantai_buytime (Delegate_Sendpackt SendPacket ,uint8 num)
{
	packet *dst = external_protocol_new_packet(CMSG_DOUJIANTAI_BUYTIME);
		
	packet_write(dst,(char *)&num,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����̨����CD*/
__INLINE__ int Call_doujiantai_clearcd (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_DOUJIANTAI_CLEARCD);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����̨��ʤ����*/
__INLINE__ int Call_doujiantai_first_reward (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_DOUJIANTAI_FIRST_REWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����̨��ս������Ϣ*/
__INLINE__ int Call_doujiantai_get_enemys_info (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(MSG_DOUJIANTAI_GET_ENEMYS_INFO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����̨���а�*/
__INLINE__ int Call_doujiantai_get_rank (Delegate_Sendpackt SendPacket ,uint16 startIdx,uint16 endIdx)
{
	packet *dst = external_protocol_new_packet(CMSG_DOUJIANTAI_GET_RANK);
		
	packet_write(dst,(char *)&startIdx,sizeof(uint16));
	packet_write(dst,(char *)&endIdx,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����̨ˢ�¶���*/
__INLINE__ int Call_doujiantai_refresh_enemys (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_DOUJIANTAI_REFRESH_ENEMYS);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����̨����*/
__INLINE__ int Call_doujiantai_top3 (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(MSG_DOUJIANTAI_TOP3);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʹ������*/
__INLINE__ int Call_use_jump_point (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(MSG_USE_JUMP_POINT);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������Ʒ*/
__INLINE__ int Call_bag_item_sell (Delegate_Sendpackt SendPacket ,char const*item_guid,uint32 count)
{
	packet *dst = external_protocol_new_packet(CMSG_BAG_ITEM_SELL);
		
	packet_write_str(dst,item_guid);		
	packet_write(dst,(char *)&count,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������Ʒ*/
__INLINE__ int Call_bag_item_sort (Delegate_Sendpackt SendPacket ,uint32 bag_type)
{
	packet *dst = external_protocol_new_packet(CMSG_BAG_ITEM_SORT);
		
	packet_write(dst,(char *)&bag_type,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�ύ�ճ�����*/
__INLINE__ int Call_submit_quest_daily2 (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_SUBMIT_QUEST_DAILY2);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���Ըı�*/
__INLINE__ int Call_attribute_changed (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_ATTRIBUTE_CHANGED);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����и�ǿװ��*/
__INLINE__ int Call_bag_find_equip_better (Delegate_Sendpackt SendPacket ,uint32 item_id,uint32 pos)
{
	packet *dst = external_protocol_new_packet(SMSG_BAG_FIND_EQUIP_BETTER);
		
	packet_write(dst,(char *)&item_id,sizeof(uint32));
	packet_write(dst,(char *)&pos,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ģ�����*/
__INLINE__ int Call_module_active (Delegate_Sendpackt SendPacket ,uint32 moduleId)
{
	packet *dst = external_protocol_new_packet(SMSG_MODULE_ACTIVE);
		
	packet_write(dst,(char *)&moduleId,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ�ճ�������*/
__INLINE__ int Call_pick_daily2_quest_reward (Delegate_Sendpackt SendPacket ,uint8 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_PICK_DAILY2_QUEST_REWARD);
		
	packet_write(dst,(char *)&indx,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɵ�ǰ����*/
__INLINE__ int Call_finish_now_guide (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_FINISH_NOW_GUIDE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ȡ����������Ϣ*/
__INLINE__ int Call_get_cultivation_info (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_GET_CULTIVATION_INFO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������������Ϣ*/
__INLINE__ int Call_update_cultivation_info (Delegate_Sendpackt SendPacket ,uint32 start_time,uint32 lost)
{
	packet *dst = external_protocol_new_packet(SMSG_UPDATE_CULTIVATION_INFO);
		
	packet_write(dst,(char *)&start_time,sizeof(uint32));
	packet_write(dst,(char *)&lost,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ȡ�õ�ǰ����������������Ϣ*/
__INLINE__ int Call_get_cultivation_rivals_info (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_GET_CULTIVATION_RIVALS_INFO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������������Ϣ*/
__INLINE__ int Call_update_cultivation_rivals_info_list (Delegate_Sendpackt SendPacket ,const vector< cultivation_rivals_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_UPDATE_CULTIVATION_RIVALS_INFO_LIST);
		
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ����������*/
__INLINE__ int Call_get_cultivation_reward (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_GET_CULTIVATION_REWARD);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ˢ������������*/
__INLINE__ int Call_refresh_cultivation_rivals (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_REFRESH_CULTIVATION_RIVALS);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�Ӷ�����������*/
__INLINE__ int Call_plunder_cultivation_rival (Delegate_Sendpackt SendPacket ,uint32 index)
{
	packet *dst = external_protocol_new_packet(CMSG_PLUNDER_CULTIVATION_RIVAL);
		
	packet_write(dst,(char *)&index,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������������������*/
__INLINE__ int Call_revenge_cultivation_rival (Delegate_Sendpackt SendPacket ,uint32 index)
{
	packet *dst = external_protocol_new_packet(CMSG_REVENGE_CULTIVATION_RIVAL);
		
	packet_write(dst,(char *)&index,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������ʣ����ս����*/
__INLINE__ int Call_buy_cultivation_left_plunder_count (Delegate_Sendpackt SendPacket ,uint32 count)
{
	packet *dst = external_protocol_new_packet(CMSG_BUY_CULTIVATION_LEFT_PLUNDER_COUNT);
		
	packet_write(dst,(char *)&count,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������ս�����*/
__INLINE__ int Call_show_cultivation_result_list (Delegate_Sendpackt SendPacket ,int32 result,char const*name,const vector< item_reward_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_CULTIVATION_RESULT_LIST);
		
	packet_write(dst,(char *)&result,sizeof(int32));
	packet_write_str(dst,name);		
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ��¼������*/
__INLINE__ int Call_get_login_activity_reward (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_GET_LOGIN_ACTIVITY_REWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*֪ͨ�ͻ����ͷ���������*/
__INLINE__ int Call_cast_spell_start (Delegate_Sendpackt SendPacket ,uint32 caster_guid,uint32 target_guid,uint16 spellid,char const*data)
{
	packet *dst = external_protocol_new_packet(SMSG_CAST_SPELL_START);
		
	packet_write(dst,(char *)&caster_guid,sizeof(uint32));
	packet_write(dst,(char *)&target_guid,sizeof(uint32));
	packet_write(dst,(char *)&spellid,sizeof(uint16));
	packet_write_str(dst,data);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ɷ�ǿ�������Ĳ���*/
__INLINE__ int Call_finish_optional_guide_step (Delegate_Sendpackt SendPacket ,uint32 guide_id,uint8 step)
{
	packet *dst = external_protocol_new_packet(CMSG_FINISH_OPTIONAL_GUIDE_STEP);
		
	packet_write(dst,(char *)&guide_id,sizeof(uint32));
	packet_write(dst,(char *)&step,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ִ�нӵ������Ժ������*/
__INLINE__ int Call_execute_quest_cmd_after_accepted (Delegate_Sendpackt SendPacket ,uint16 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_EXECUTE_QUEST_CMD_AFTER_ACCEPTED);
		
	packet_write(dst,(char *)&indx,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*֪ͨ�ͻ�����ʾ����*/
__INLINE__ int Call_show_unit_attribute (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_UNIT_ATTRIBUTE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ؼ���*/
__INLINE__ int Call_back_to_famity (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_BACK_TO_FAMITY);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ؼ���boss���*/
__INLINE__ int Call_faction_boss_send_result (Delegate_Sendpackt SendPacket ,uint32 result,uint32 boss_id,uint32 money)
{
	packet *dst = external_protocol_new_packet(SMSG_FACTION_BOSS_SEND_RESULT);
		
	packet_write(dst,(char *)&result,sizeof(uint32));
	packet_write(dst,(char *)&boss_id,sizeof(uint32));
	packet_write(dst,(char *)&money,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��սboss*/
__INLINE__ int Call_challange_boss (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_CHALLANGE_BOSS);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ���߽���*/
__INLINE__ int Call_pick_offline_reward (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_PICK_OFFLINE_REWARD);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���߽������*/
__INLINE__ int Call_offline_reward_result (Delegate_Sendpackt SendPacket ,uint32 reserve,uint32 reserve2,uint32 reserve3,uint32 reserve4,const vector< item_reward_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_OFFLINE_REWARD_RESULT);
		
	packet_write(dst,(char *)&reserve,sizeof(uint32));
	packet_write(dst,(char *)&reserve2,sizeof(uint32));
	packet_write(dst,(char *)&reserve3,sizeof(uint32));
	packet_write(dst,(char *)&reserve4,sizeof(uint32));
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����װ��*/
__INLINE__ int Call_smelting_equip (Delegate_Sendpackt SendPacket ,char const*pos_str)
{
	packet *dst = external_protocol_new_packet(CMSG_SMELTING_EQUIP);
		
	packet_write_str(dst,pos_str);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�Ͻ�װ��*/
__INLINE__ int Call_storehouse_hand_in (Delegate_Sendpackt SendPacket ,char const*pos_str)
{
	packet *dst = external_protocol_new_packet(CMSG_STOREHOUSE_HAND_IN);
		
	packet_write_str(dst,pos_str);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�һ�װ��*/
__INLINE__ int Call_storehouse_exchange (Delegate_Sendpackt SendPacket ,uint32 pos)
{
	packet *dst = external_protocol_new_packet(CMSG_STOREHOUSE_EXCHANGE);
		
	packet_write(dst,(char *)&pos,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����װ��*/
__INLINE__ int Call_storehouse_destroy (Delegate_Sendpackt SendPacket ,uint32 pos)
{
	packet *dst = external_protocol_new_packet(CMSG_STOREHOUSE_DESTROY);
		
	packet_write(dst,(char *)&pos,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_send_faction_gift (Delegate_Sendpackt SendPacket ,const vector< item_reward_info > &list ,char const*msg,uint32 msg_type)
{
	packet *dst = external_protocol_new_packet(CMSG_SEND_FACTION_GIFT);
		
	*dst << list;
	packet_write_str(dst,msg);		
	packet_write(dst,(char *)&msg_type,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ���⽱��*/
__INLINE__ int Call_get_faction_gift_exreward (Delegate_Sendpackt SendPacket ,uint32 count_id)
{
	packet *dst = external_protocol_new_packet(CMSG_GET_FACTION_GIFT_EXREWARD);
		
	packet_write(dst,(char *)&count_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ���ж��⽱��*/
__INLINE__ int Call_get_all_faction_gift_exreward (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_GET_ALL_FACTION_GIFT_EXREWARD);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���������б�*/
__INLINE__ int Call_show_faction_gift_page (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_GIFT_PAGE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������Ϣ*/
__INLINE__ int Call_show_faction_gift_info (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_GIFT_INFO);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����Ů��δ��л����*/
__INLINE__ int Call_show_faction_gift_unthank_page (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_GIFT_UNTHANK_PAGE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����Ů����ʷ��¼*/
__INLINE__ int Call_show_faction_gift_history_page (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_GIFT_HISTORY_PAGE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���������������*/
__INLINE__ int Call_get_faction_gift_rank_page (Delegate_Sendpackt SendPacket ,uint32 page)
{
	packet *dst = external_protocol_new_packet(CMSG_GET_FACTION_GIFT_RANK_PAGE);
		
	packet_write(dst,(char *)&page,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ؼ�����������*/
__INLINE__ int Call_show_faction_gift_rank_result_list (Delegate_Sendpackt SendPacket ,const vector< faction_gift_rank_info > &list , faction_gift_rank_info *info,uint32 page)
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_GIFT_RANK_RESULT_LIST);
		
	*dst << list;
	packet_write(dst,(char*)info,sizeof(faction_gift_rank_info));
	packet_write(dst,(char *)&page,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ؼ����������б仯*/
__INLINE__ int Call_show_faction_gift_rank_change (Delegate_Sendpackt SendPacket ,uint32 old_rank,uint32 new_rank, faction_gift_rank_info *info)
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_GIFT_RANK_CHANGE);
		
	packet_write(dst,(char *)&old_rank,sizeof(uint32));
	packet_write(dst,(char *)&new_rank,sizeof(uint32));
	packet_write(dst,(char*)info,sizeof(faction_gift_rank_info));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ر�������������*/
__INLINE__ int Call_show_faction_gift_rank_info (Delegate_Sendpackt SendPacket , faction_gift_rank_info *info)
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_GIFT_RANK_INFO);
		
	packet_write(dst,(char*)info,sizeof(faction_gift_rank_info));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ǿ��*/
__INLINE__ int Call_divine_forge (Delegate_Sendpackt SendPacket ,uint32 id,uint32 count)
{
	packet *dst = external_protocol_new_packet(CMSG_DIVINE_FORGE);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	packet_write(dst,(char *)&count,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_divine_advance (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_DIVINE_ADVANCE);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_divine_spirit (Delegate_Sendpackt SendPacket ,uint32 id,uint32 protect,uint32 improve)
{
	packet *dst = external_protocol_new_packet(CMSG_DIVINE_SPIRIT);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	packet_write(dst,(char *)&protect,sizeof(uint32));
	packet_write(dst,(char *)&improve,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ѯȫ��boss��Ϣ*/
__INLINE__ int Call_query_mass_boss_info (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_QUERY_MASS_BOSS_INFO);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ȫ��boss��Ϣ���*/
__INLINE__ int Call_mass_boss_info_ret (Delegate_Sendpackt SendPacket ,uint32 count,uint8 percent)
{
	packet *dst = external_protocol_new_packet(SMSG_MASS_BOSS_INFO_RET);
		
	packet_write(dst,(char *)&count,sizeof(uint32));
	packet_write(dst,(char *)&percent,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ѯȫ��boss���а�*/
__INLINE__ int Call_query_mass_boss_rank (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_QUERY_MASS_BOSS_RANK);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ȫ��boss���н��*/
__INLINE__ int Call_mass_boss_rank_result (Delegate_Sendpackt SendPacket ,const vector< rank_info > &info )
{
	packet *dst = external_protocol_new_packet(SMSG_MASS_BOSS_RANK_RESULT);
		
	*dst << info;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��սȫ��boss*/
__INLINE__ int Call_try_mass_boss (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_TRY_MASS_BOSS);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������սȫ��boss����*/
__INLINE__ int Call_buy_mass_boss_times (Delegate_Sendpackt SendPacket ,uint8 cnt)
{
	packet *dst = external_protocol_new_packet(CMSG_BUY_MASS_BOSS_TIMES);
		
	packet_write(dst,(char *)&cnt,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��Ӹ������ƥ��*/
__INLINE__ int Call_group_instance_match (Delegate_Sendpackt SendPacket ,uint8 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_GROUP_INSTANCE_MATCH);
		
	packet_write(dst,(char *)&indx,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��Ӹ��������������*/
__INLINE__ int Call_buy_group_instance_times (Delegate_Sendpackt SendPacket ,uint8 count)
{
	packet *dst = external_protocol_new_packet(CMSG_BUY_GROUP_INSTANCE_TIMES);
		
	packet_write(dst,(char *)&count,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_talisman_active (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_TALISMAN_ACTIVE);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ע��*/
__INLINE__ int Call_talisman_lvup (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_TALISMAN_LVUP);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���𼤻�*/
__INLINE__ int Call_wings_active (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WINGS_ACTIVE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ף��*/
__INLINE__ int Call_wings_bless (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WINGS_BLESS);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_wings_rankup (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WINGS_RANKUP);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ǿ��*/
__INLINE__ int Call_wings_strength (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_WINGS_STRENGTH);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_meridian_practise (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_MERIDIAN_PRACTISE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�Ӿ�����������ֵ*/
__INLINE__ int Call_add_meridian_exp (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_ADD_MERIDIAN_EXP);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������ȼ�*/
__INLINE__ int Call_raise_mount_level_base (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_RAISE_MOUNT_LEVEL_BASE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������*/
__INLINE__ int Call_active_mount (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_ACTIVE_MOUNT);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������ս�������*/
__INLINE__ int Call_show_faction_bossdefense_damage_list (Delegate_Sendpackt SendPacket ,const vector< mass_boss_rank_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_BOSSDEFENSE_DAMAGE_LIST);
		
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����޾�Զ��ɨ�����*/
__INLINE__ int Call_show_faction_tower_sweep_list (Delegate_Sendpackt SendPacket ,const vector< item_reward_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_TOWER_SWEEP_LIST);
		
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_send_instance_result (Delegate_Sendpackt SendPacket ,uint8 state,uint8 cd,const vector< item_reward_info > &list ,uint8 type,char const*data)
{
	packet *dst = external_protocol_new_packet(SMSG_SEND_INSTANCE_RESULT);
		
	packet_write(dst,(char *)&state,sizeof(uint8));
	packet_write(dst,(char *)&cd,sizeof(uint8));
	*dst << list;
	packet_write(dst,(char *)&type,sizeof(uint8));
	packet_write_str(dst,data);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ƥ�䵥��pvp*/
__INLINE__ int Call_match_single_pvp (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_MATCH_SINGLE_PVP);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*������pvp����*/
__INLINE__ int Call_buy_match_single_pvp_times (Delegate_Sendpackt SendPacket ,uint8 cnt)
{
	packet *dst = external_protocol_new_packet(CMSG_BUY_MATCH_SINGLE_PVP_TIMES);
		
	packet_write(dst,(char *)&cnt,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ����pvp���⽱��*/
__INLINE__ int Call_pick_match_single_pvp_extra_reward (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_PICK_MATCH_SINGLE_PVP_EXTRA_REWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*װ�����ɲ���*/
__INLINE__ int Call_equipdevelop_operate (Delegate_Sendpackt SendPacket ,uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2)
{
	packet *dst = external_protocol_new_packet(CMSG_EQUIPDEVELOP_OPERATE);
		
	packet_write(dst,(char *)&opt_type,sizeof(uint8));
	packet_write(dst,(char *)&reserve_int1,sizeof(uint16));
	packet_write(dst,(char *)&reserve_int2,sizeof(uint16));
	packet_write_str(dst,reserve_str1);		
	packet_write_str(dst,reserve_str2);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������*/
__INLINE__ int Call_active_appearance (Delegate_Sendpackt SendPacket ,uint16 id)
{
	packet *dst = external_protocol_new_packet(CMSG_ACTIVE_APPEARANCE);
		
	packet_write(dst,(char *)&id,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*װ�����*/
__INLINE__ int Call_equip_appearance (Delegate_Sendpackt SendPacket ,uint16 id)
{
	packet *dst = external_protocol_new_packet(CMSG_EQUIP_APPEARANCE);
		
	packet_write(dst,(char *)&id,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ȡ��װ�����*/
__INLINE__ int Call_cancel_equip_appearance (Delegate_Sendpackt SendPacket ,uint8 type)
{
	packet *dst = external_protocol_new_packet(CMSG_CANCEL_EQUIP_APPEARANCE);
		
	packet_write(dst,(char *)&type,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����*/
__INLINE__ int Call_rename (Delegate_Sendpackt SendPacket ,char const*name)
{
	packet *dst = external_protocol_new_packet(CMSG_RENAME);
		
	packet_write_str(dst,name);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���߽����ƺ�*/
__INLINE__ int Call_unlock_title (Delegate_Sendpackt SendPacket ,uint8 indx)
{
	packet *dst = external_protocol_new_packet(CMSG_UNLOCK_TITLE);
		
	packet_write(dst,(char *)&indx,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���򸴳����*/
__INLINE__ int Call_social_buy_revenge_times (Delegate_Sendpackt SendPacket ,uint8 count)
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_BUY_REVENGE_TIMES);
		
	packet_write(dst,(char *)&count,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����������ð�ո���*/
__INLINE__ int Call_enter_risk_instance (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_ENTER_RISK_INSTANCE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ɾ������*/
__INLINE__ int Call_social_remove_enemy (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_SOCIAL_REMOVE_ENEMY);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�鿴�������*/
__INLINE__ int Call_get_player_overview (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_GET_PLAYER_OVERVIEW);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����������*/
__INLINE__ int Call_show_player_overview (Delegate_Sendpackt SendPacket ,char const*guid,char const*name,uint32 force,uint32 vip,uint32 title,uint32 gender,uint32 coat,uint32 weapon)
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_PLAYER_OVERVIEW);
		
	packet_write_str(dst,guid);		
	packet_write_str(dst,name);		
	packet_write(dst,(char *)&force,sizeof(uint32));
	packet_write(dst,(char *)&vip,sizeof(uint32));
	packet_write(dst,(char *)&title,sizeof(uint32));
	packet_write(dst,(char *)&gender,sizeof(uint32));
	packet_write(dst,(char *)&coat,sizeof(uint32));
	packet_write(dst,(char *)&weapon,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������*/
__INLINE__ int Call_send_faction_invite (Delegate_Sendpackt SendPacket ,char const*guid)
{
	packet *dst = external_protocol_new_packet(CMSG_SEND_FACTION_INVITE);
		
	packet_write_str(dst,guid);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ʾ����*/
__INLINE__ int Call_show_faction_invite (Delegate_Sendpackt SendPacket ,char const*guid,char const*name,char const*faction_guid,char const*faction_name)
{
	packet *dst = external_protocol_new_packet(SMSG_SHOW_FACTION_INVITE);
		
	packet_write_str(dst,guid);		
	packet_write_str(dst,name);		
	packet_write_str(dst,faction_guid);		
	packet_write_str(dst,faction_name);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����vip���*/
__INLINE__ int Call_buy_vipgift (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_BUY_VIPGIFT);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ÿ�����*/
__INLINE__ int Call_activity_opt_buy_dailygift (Delegate_Sendpackt SendPacket ,uint32 act_id,uint32 index)
{
	packet *dst = external_protocol_new_packet(CMSG_ACTIVITY_OPT_BUY_DAILYGIFT);
		
	packet_write(dst,(char *)&act_id,sizeof(uint32));
	packet_write(dst,(char *)&index,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�齱*/
__INLINE__ int Call_draw_lottery (Delegate_Sendpackt SendPacket ,uint32 actId,uint8 type)
{
	packet *dst = external_protocol_new_packet(CMSG_DRAW_LOTTERY);
		
	packet_write(dst,(char *)&actId,sizeof(uint32));
	packet_write(dst,(char *)&type,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ��������н��Ƚ���*/
__INLINE__ int Call_activity_opt_get_rank_process_reward (Delegate_Sendpackt SendPacket ,uint32 act_id,uint32 index)
{
	packet *dst = external_protocol_new_packet(CMSG_ACTIVITY_OPT_GET_RANK_PROCESS_REWARD);
		
	packet_write(dst,(char *)&act_id,sizeof(uint32));
	packet_write(dst,(char *)&index,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ��������а�*/
__INLINE__ int Call_activity_opt_get_rank_list (Delegate_Sendpackt SendPacket ,uint32 act_id)
{
	packet *dst = external_protocol_new_packet(CMSG_ACTIVITY_OPT_GET_RANK_LIST);
		
	packet_write(dst,(char *)&act_id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ػ�������а�*/
__INLINE__ int Call_activity_opt_show_rank_list (Delegate_Sendpackt SendPacket ,uint32 act_id,const vector< act_rank_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_ACTIVITY_OPT_SHOW_RANK_LIST);
		
	packet_write(dst,(char *)&act_id,sizeof(uint32));
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�����޶����*/
__INLINE__ int Call_activity_opt_buy_limitgift (Delegate_Sendpackt SendPacket ,uint32 act_id,uint32 index)
{
	packet *dst = external_protocol_new_packet(CMSG_ACTIVITY_OPT_BUY_LIMITGIFT);
		
	packet_write(dst,(char *)&act_id,sizeof(uint32));
	packet_write(dst,(char *)&index,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ�ۼƳ�ֵ����*/
__INLINE__ int Call_welfare_get_recharge_reward (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_GET_RECHARGE_REWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ�ۼ����ѽ���*/
__INLINE__ int Call_welfare_get_consume_reward (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_GET_CONSUME_REWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡ���մ�����*/
__INLINE__ int Call_welfare_get_sevenday_reward (Delegate_Sendpackt SendPacket ,uint8 id)
{
	packet *dst = external_protocol_new_packet(CMSG_WELFARE_GET_SEVENDAY_REWARD);
		
	packet_write(dst,(char *)&id,sizeof(uint8));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����������ʱ��*/
__INLINE__ int Call_send_server_open_time (Delegate_Sendpackt SendPacket ,uint32 open_time)
{
	packet *dst = external_protocol_new_packet(SMSG_SEND_SERVER_OPEN_TIME);
		
	packet_write(dst,(char *)&open_time,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������ð�����а�*/
__INLINE__ int Call_risk_get_rank (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_RISK_GET_RANK);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*����ð�����а���Ϣ */
__INLINE__ int Call_risk_get_rank_result (Delegate_Sendpackt SendPacket ,const vector< act_rank_info > &list )
{
	packet *dst = external_protocol_new_packet(SMSG_RISK_GET_RANK_RESULT);
		
	*dst << list;
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*���ó���*/
__INLINE__ int Call_set_orient (Delegate_Sendpackt SendPacket ,uint16 angle)
{
	packet *dst = external_protocol_new_packet(CMSG_SET_ORIENT);
		
	packet_write(dst,(char *)&angle,sizeof(uint16));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ҡ��ҡǮ��*/
__INLINE__ int Call_use_moneytree (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_USE_MONEYTREE);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��ȡҡǮ�����*/
__INLINE__ int Call_get_moneytree_gift (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_GET_MONEYTREE_GIFT);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�޸Ļþ�������id*/
__INLINE__ int Call_set_world_risk_last_id (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_SET_WORLD_RISK_LAST_ID);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*�������Boss*/
__INLINE__ int Call_enter_private_boss (Delegate_Sendpackt SendPacket ,uint32 id)
{
	packet *dst = external_protocol_new_packet(CMSG_ENTER_PRIVATE_BOSS);
		
	packet_write(dst,(char *)&id,sizeof(uint32));
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*��������ȫ������*/
__INLINE__ int Call_raise_base_spell_all (Delegate_Sendpackt SendPacket ,uint8 raiseType,char const*spellIdStr)
{
	packet *dst = external_protocol_new_packet(CMSG_RAISE_BASE_SPELL_ALL);
		
	packet_write(dst,(char *)&raiseType,sizeof(uint8));
	packet_write_str(dst,spellIdStr);		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

/*ʹ�ûظ�ҩ*/
__INLINE__ int Call_use_restore_potion (Delegate_Sendpackt SendPacket )
{
	packet *dst = external_protocol_new_packet(CMSG_USE_RESTORE_POTION);
		
	update_packet_len(dst);
	
	SendPacket(*dst);
	external_protocol_free_packet(dst);
	return 0;	
}

	
#endif

#endif

