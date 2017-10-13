#ifndef _PROTOCOL_UTIL_H_
#define _PROTOCOL_UTIL_H_

#include "robotd_app.h"
#include "encipher.h"

class ProtocolUtil
{
public:
	ProtocolUtil():m_conn(0),m_war_conn(0){}
	~ProtocolUtil(){}
public:
	static void SetWarOptCode(vector<int> &);
private:
	core_socket::TcpConnection *m_conn;
	core_socket::c2sencipher m_encipher;

	core_socket::TcpConnection *m_war_conn;
	core_socket::c2sencipher m_war_encipher;
	static UpdateMask m_war_optcode;

	ByteArray m_bytes;
public:
	void SendToServer(ByteArray &);
	void ResetConn(core_socket::TcpConnection *conn);
	void ResetWarConn(core_socket::TcpConnection *conn);
	/*��Ч����*/
	int unpack_null_action (ByteArray &bytes );
	int send_null_action ();
	/*��������״̬*/
	int unpack_ping_pong (ByteArray &bytes );
	int send_ping_pong ();
	/*�ߵ����ߵ�׼��ǿ�Ƶ�½*/
	int unpack_forced_into (ByteArray &bytes );
	int send_forced_into ();
	/*���Session����*/
	int unpack_get_session (ByteArray &bytes ,string &sessionkey,string &account,string &version);
	int send_get_session (char const*sessionkey,char const*account,char const*version);
	/*���ط����ݰ�·�ɲ���*/
	int unpack_route_trace (ByteArray &bytes ,string &val);
	int send_route_trace (char const*val);
	/*��¼�ͻ�����־*/
	int unpack_write_client_log (ByteArray &bytes ,uint32 &type,string &uid,string &guid,string &log);
	int send_write_client_log (uint32 type,char const*uid,char const*guid,char const*log);
	/*����ʧ��*/
	int unpack_operation_failed (ByteArray &bytes ,uint16 &type,uint16 &reason,string &data);
	int send_operation_failed (uint16 type,uint16 reason,char const*data);
	/*ͬ��ʱ��*/
	int unpack_sync_mstime (ByteArray &bytes ,uint32 &mstime_now,uint32 &time_now,uint32 &open_time);
	int send_sync_mstime (uint32 mstime_now,uint32 time_now,uint32 open_time);
	/*�������*/
	int unpack_ud_object (ByteArray &bytes );
	int send_ud_object ();
	/*������¿���Э��*/
	int unpack_ud_control (ByteArray &bytes );
	int send_ud_control ();
	/*������¿���Э����*/
	int unpack_ud_control_result (ByteArray &bytes );
	int send_ud_control_result ();
	/*GRID�Ķ������*/
	int unpack_grid_ud_object (ByteArray &bytes );
	int send_grid_ud_object ();
	/*GRID�Ķ������*/
	int unpack_grid_ud_object_2 (ByteArray &bytes );
	int send_grid_ud_object_2 ();
	/*���߿ͻ��ˣ�Ŀǰ�Լ����ڵ�¼���еĵڼ�λ*/
	int unpack_login_queue_index (ByteArray &bytes ,uint32 &index);
	int send_login_queue_index (uint32 index);
	/*����ԭ��*/
	int unpack_kicking_type (ByteArray &bytes ,uint32 &k_type);
	int send_kicking_type (uint32 k_type);
	/*��ȡ��ɫ�б�*/
	int unpack_get_chars_list (ByteArray &bytes );
	int send_get_chars_list ();
	/*��ɫ�б�*/
	int unpack_chars_list (ByteArray &bytes , vector< char_create_info > &list,string &faction_name,string &queen_name,uint8 &icon);
	int send_chars_list (const vector< char_create_info > &list ,char const*faction_name,char const*queen_name,uint8 icon);
	/*��������Ƿ����ʹ��*/
	int unpack_check_name (ByteArray &bytes ,string &name);
	int send_check_name (char const*name);
	/*������ֽ��*/
	int unpack_check_name_result (ByteArray &bytes ,uint8 &result);
	int send_check_name_result (uint8 result);
	/*������ɫ*/
	int unpack_char_create (ByteArray &bytes , char_create_info **info);
	int send_char_create (char_create_info *info);
	/*��ɫ�������*/
	int unpack_char_create_result (ByteArray &bytes ,uint8 &result);
	int send_char_create_result (uint8 result);
	/*ɾ����ɫ*/
	int unpack_delete_char (ByteArray &bytes ,uint32 &id);
	int send_delete_char (uint32 id);
	/*��ɫɾ�����*/
	int unpack_delete_char_result (ByteArray &bytes ,uint8 &result);
	int send_delete_char_result (uint8 result);
	/*��ҵ�¼*/
	int unpack_player_login (ByteArray &bytes ,string &guid);
	int send_player_login (char const*guid);
	/*����˳�*/
	int unpack_player_logout (ByteArray &bytes );
	int send_player_logout ();
	/*��ʱ�˺�ת����*/
	int unpack_regularise_account (ByteArray &bytes ,string &uid);
	int send_regularise_account (char const*uid);
	/*��ɫ������Ϣ*/
	int unpack_char_remotestore (ByteArray &bytes ,uint32 &key,uint32 &value);
	int send_char_remotestore (uint32 key,uint32 value);
	/*��ɫ������Ϣ*/
	int unpack_char_remotestore_str (ByteArray &bytes ,uint32 &key,string &value);
	int send_char_remotestore_str (uint32 key,char const*value);
	/*���ͣ������C->S��mapid��������ɴ��͵�ID*/
	int unpack_teleport (ByteArray &bytes ,uint32 &intGuid);
	int send_teleport (uint32 intGuid);
	/*ֹͣ�ƶ�*/
	int unpack_move_stop (ByteArray &bytes ,uint32 &guid,uint16 &pos_x,uint16 &pos_y);
	int send_move_stop (uint32 guid,uint16 pos_x,uint16 pos_y);
	/*unit�����ƶ�*/
	int unpack_unit_move (ByteArray &bytes ,uint32 &guid,uint16 &pos_x,uint16 &pos_y, vector< int8 > &path);
	int send_unit_move (uint32 guid,uint16 pos_x,uint16 pos_y,const vector< int8 > &path );
	/*ʹ����Ϸ����*/
	int unpack_use_gameobject (ByteArray &bytes ,uint32 &target);
	int send_use_gameobject (uint32 target);
	/*��������-����λ��*/
	int unpack_bag_exchange_pos (ByteArray &bytes ,uint32 &src_bag,uint32 &src_pos,uint32 &dst_bag,uint32 &dst_pos);
	int send_bag_exchange_pos (uint32 src_bag,uint32 src_pos,uint32 dst_bag,uint32 dst_pos);
	/*��������-������Ʒ*/
	int unpack_bag_destroy (ByteArray &bytes ,string &item_guid,uint32 &num,uint32 &bag_id);
	int send_bag_destroy (char const*item_guid,uint32 num,uint32 bag_id);
	/*�ָ���Ʒ*/
	int unpack_bag_item_split (ByteArray &bytes ,uint8 &bag_id,uint16 &src_pos,uint32 &count,uint16 &dst_pos,uint8 &dst_bag);
	int send_bag_item_split (uint8 bag_id,uint16 src_pos,uint32 count,uint16 dst_pos,uint8 dst_bag);
	/*ʹ����Ʒ*/
	int unpack_bag_item_user (ByteArray &bytes ,string &item_guid,uint32 &count);
	int send_bag_item_user (char const*item_guid,uint32 count);
	/*�·���Ʒ��ȴ*/
	int unpack_bag_item_cooldown (ByteArray &bytes , vector< item_cooldown_info > &list);
	int send_bag_item_cooldown (const vector< item_cooldown_info > &list );
	/*grid�е�unit�ƶ�������*/
	int unpack_grid_unit_move (ByteArray &bytes );
	int send_grid_unit_move ();
	/*grid�е�unit�ƶ�������2*/
	int unpack_grid_unit_move_2 (ByteArray &bytes );
	int send_grid_unit_move_2 ();
	/*�һ���Ʒ*/
	int unpack_exchange_item (ByteArray &bytes ,uint32 &entry,uint32 &count,uint32 &tar_entry);
	int send_exchange_item (uint32 entry,uint32 count,uint32 tar_entry);
	/*������չ*/
	int unpack_bag_extension (ByteArray &bytes ,uint8 &bag_id,uint8 &extension_type,uint32 &bag_pos);
	int send_bag_extension (uint8 bag_id,uint8 extension_type,uint32 bag_pos);
	/*����NPC��Ʒ�б�*/
	int unpack_npc_get_goods_list (ByteArray &bytes ,uint32 &npc_id);
	int send_npc_get_goods_list (uint32 npc_id);
	/*Npc��Ʒ�б�*/
	int unpack_npc_goods_list (ByteArray &bytes , vector< uint32 > &goods,uint32 &npc_id);
	int send_npc_goods_list (const vector< uint32 > &goods ,uint32 npc_id);
	/*������Ʒ*/
	int unpack_store_buy (ByteArray &bytes ,uint32 &id,uint32 &count);
	int send_store_buy (uint32 id,uint32 count);
	/*������Ʒ*/
	int unpack_npc_sell (ByteArray &bytes ,uint32 &npc_id,string &item_guid,uint32 &num);
	int send_npc_sell (uint32 npc_id,char const*item_guid,uint32 num);
	/*�ع���Ʒ*/
	int unpack_npc_repurchase (ByteArray &bytes ,string &item_id);
	int send_npc_repurchase (char const*item_id);
	/*ʱװ�Ƿ�����*/
	int unpack_avatar_fashion_enable (ByteArray &bytes ,uint8 &pos);
	int send_avatar_fashion_enable (uint8 pos);
	/*����Ի�ѡ��*/
	int unpack_questhelp_talk_option (ByteArray &bytes ,uint32 &quest_id,uint32 &option_id,int32 &value0,int32 &value1);
	int send_questhelp_talk_option (uint32 quest_id,uint32 option_id,int32 value0,int32 value1);
	/*��NPC�Ի���ô��͵��б�*/
	int unpack_taxi_hello (ByteArray &bytes ,uint32 &guid);
	int send_taxi_hello (uint32 guid);
	/*���ʹ��͵��б�*/
	int unpack_taxi_stations_list (ByteArray &bytes ,uint32 &npcid, vector< taxi_menu_info > &stations);
	int send_taxi_stations_list (uint32 npcid,const vector< taxi_menu_info > &stations );
	/*ѡ���͵�*/
	int unpack_taxi_select_station (ByteArray &bytes ,uint32 &station_id,uint32 &guid);
	int send_taxi_select_station (uint32 station_id,uint32 guid);
	/*��NPC����ѡ��ѡ��*/
	int unpack_gossip_select_option (ByteArray &bytes ,uint32 &option,uint32 &guid,string &unknow);
	int send_gossip_select_option (uint32 option,uint32 guid,char const*unknow);
	/*��NPC���Ļ�ȡѡ��*/
	int unpack_gossip_hello (ByteArray &bytes ,uint32 &guid);
	int send_gossip_hello (uint32 guid);
	/*����������Ϣ��ѡ��*/
	int unpack_gossip_message (ByteArray &bytes ,uint32 &npcid,uint32 &npc_entry,uint32 &option_id,string &option_text, vector< gossip_menu_option_info > &gossip_items);
	int send_gossip_message (uint32 npcid,uint32 npc_entry,uint32 option_id,char const*option_text,const vector< gossip_menu_option_info > &gossip_items );
	/*���񷢲���״̬��ѯ*/
	int unpack_questgiver_status_query (ByteArray &bytes ,uint32 &guid);
	int send_questgiver_status_query (uint32 guid);
	/*����NPC״̬*/
	int unpack_questgiver_status (ByteArray &bytes ,uint32 &guid,uint8 &status);
	int send_questgiver_status (uint32 guid,uint8 status);
	/*��ѯ����״̬*/
	int unpack_query_quest_status (ByteArray &bytes , vector< quest_status > &quest_array);
	int send_query_quest_status (const vector< quest_status > &quest_array );
	/*�ɽ�����*/
	int unpack_questhelp_get_canaccept_list (ByteArray &bytes );
	int send_questhelp_get_canaccept_list ();
	/*�·��ɽ������б�*/
	int unpack_questhelp_canaccept_list (ByteArray &bytes , vector< uint32 > &quests);
	int send_questhelp_canaccept_list (const vector< uint32 > &quests );
	/*����ʧ��*/
	int unpack_questupdate_faild (ByteArray &bytes ,uint8 &reason);
	int send_questupdate_faild (uint8 reason);
	/*�����������*/
	int unpack_questupdate_complete (ByteArray &bytes ,uint32 &quest_id);
	int send_questupdate_complete (uint32 quest_id);
	/*��������*/
	int unpack_questlog_remove_quest (ByteArray &bytes ,uint8 &slot,uint64 &reserve);
	int send_questlog_remove_quest (uint8 slot,uint64 reserve);
	/*�������*/
	int unpack_questgiver_complete_quest (ByteArray &bytes ,uint32 &guid,uint32 &quest_id,uint8 &reward);
	int send_questgiver_complete_quest (uint32 guid,uint32 quest_id,uint8 reward);
	/*��������֪ͨ���������¸�����*/
	int unpack_questhelp_next (ByteArray &bytes ,uint32 &current_id,uint32 &next_id,uint32 &guid);
	int send_questhelp_next (uint32 current_id,uint32 next_id,uint32 guid);
	/*����ϵͳǿ���������*/
	int unpack_questhelp_complete (ByteArray &bytes ,uint32 &quest_id,uint8 &quest_statue,uint8 &reserve);
	int send_questhelp_complete (uint32 quest_id,uint8 quest_statue,uint8 reserve);
	/*��������ɹ�*/
	int unpack_questupdate_accept (ByteArray &bytes ,uint32 &quest_id);
	int send_questupdate_accept (uint32 quest_id);
	/*�����������_�±�����*/
	int unpack_questhelp_update_status (ByteArray &bytes ,uint32 &quest_id,uint32 &slot_id,uint32 &num);
	int send_questhelp_update_status (uint32 quest_id,uint32 slot_id,uint32 num);
	/*���������*/
	int unpack_questgetter_complete (ByteArray &bytes ,uint32 &quest_id);
	int send_questgetter_complete (uint32 quest_id);
	/*������*/
	int unpack_questgiver_accept_quest (ByteArray &bytes ,uint32 &npcid,uint32 &quest_id);
	int send_questgiver_accept_quest (uint32 npcid,uint32 quest_id);
	/*����ʹ����Ʒ*/
	int unpack_questupdate_use_item (ByteArray &bytes ,uint32 &item_id);
	int send_questupdate_use_item (uint32 item_id);
	/*��ѯ��������*/
	int unpack_questhelp_query_book (ByteArray &bytes ,uint32 &dynasty);
	int send_questhelp_query_book (uint32 dynasty);
	/*�·��ɽ���������*/
	int unpack_questhelp_book_quest (ByteArray &bytes ,uint32 &quest_id);
	int send_questhelp_book_quest (uint32 quest_id);
	/*���ʹ����Ϸ�����Ժ�Ķ���*/
	int unpack_use_gameobject_action (ByteArray &bytes ,uint32 &player_id,uint32 &gameobject_id);
	int send_use_gameobject_action (uint32 player_id,uint32 gameobject_id);
	/*���ù���ģʽ*/
	int unpack_set_attack_mode (ByteArray &bytes ,uint8 &mode,uint64 &reserve);
	int send_set_attack_mode (uint8 mode,uint64 reserve);
	/*ѡ��Ŀ��*/
	int unpack_select_target (ByteArray &bytes ,uint32 &id);
	int send_select_target (uint32 id);
	/*����ս��*/
	int unpack_combat_state_update (ByteArray &bytes ,uint8 &cur_state);
	int send_combat_state_update (uint8 cur_state);
	/*�������*/
	int unpack_exp_update (ByteArray &bytes ,int32 &exp,uint8 &type,int32 &vip_exp);
	int send_exp_update (int32 exp,uint8 type,int32 vip_exp);
	/*�ͻ����ͷż���*/
	int unpack_spell_start (ByteArray &bytes ,uint32 &spell_id,uint16 &target_pos_x,uint16 &target_pos_y,uint32 &caster,uint32 &target);
	int send_spell_start (uint32 spell_id,uint16 target_pos_x,uint16 target_pos_y,uint32 caster,uint32 target);
	/*ʩ��ֹͣ*/
	int unpack_spell_stop (ByteArray &bytes ,string &guid);
	int send_spell_stop (char const*guid);
	/*��*/
	int unpack_jump (ByteArray &bytes ,uint32 &guid,float &pos_x,float &pos_y);
	int send_jump (uint32 guid,float pos_x,float pos_y);
	/*����*/
	int unpack_resurrection (ByteArray &bytes ,uint8 &type,uint64 &reserve);
	int send_resurrection (uint8 type,uint64 reserve);
	/*���׷�������*/
	int unpack_trade_request (ByteArray &bytes ,string &guid);
	int send_trade_request (char const*guid);
	/*���������*/
	int unpack_trade_reply (ByteArray &bytes ,string &guid,uint8 &reply);
	int send_trade_reply (char const*guid,uint8 reply);
	/*���׿�ʼ*/
	int unpack_trade_start (ByteArray &bytes ,string &guid);
	int send_trade_start (char const*guid);
	/*����ȷ����Ʒ*/
	int unpack_trade_decide_items (ByteArray &bytes ,const string &items, uint16 *len_1,int32 &gold_ingot,int32 &silver);
	int send_trade_decide_items (char const*items,int32 gold_ingot,int32 silver);
	/*�������*/
	int unpack_trade_finish (ByteArray &bytes );
	int send_trade_finish ();
	/*����ȡ��*/
	int unpack_trade_cancel (ByteArray &bytes );
	int send_trade_cancel ();
	/*����׼����*/
	int unpack_trade_ready (ByteArray &bytes );
	int send_trade_ready ();
	/*���ｲ��*/
	int unpack_chat_unit_talk (ByteArray &bytes ,uint32 &guid,uint32 &content,string &say);
	int send_chat_unit_talk (uint32 guid,uint32 content,char const*say);
	/*�ͽ�����*/
	int unpack_chat_near (ByteArray &bytes ,string &content);
	int send_chat_near (char const*content);
	/*˽��*/
	int unpack_chat_whisper (ByteArray &bytes ,string &guid,string &content);
	int send_chat_whisper (char const*guid,char const*content);
	/*��Ӫ����*/
	int unpack_chat_faction (ByteArray &bytes ,string &guid,string &name,string &content,uint8 &faction);
	int send_chat_faction (char const*guid,char const*name,char const*content,uint8 faction);
	/*����*/
	int unpack_chat_world (ByteArray &bytes ,string &guid,uint8 &faction,string &name,string &content);
	int send_chat_world (char const*guid,uint8 faction,char const*name,char const*content);
	/*����*/
	int unpack_chat_horn (ByteArray &bytes ,string &guid,uint8 &faction,string &name,string &content);
	int send_chat_horn (char const*guid,uint8 faction,char const*name,char const*content);
	/*����*/
	int unpack_chat_notice (ByteArray &bytes ,uint32 &id,string &content,string &data);
	int send_chat_notice (uint32 id,char const*content,char const*data);
	/*��ѯ�����Ϣ*/
	int unpack_query_player_info (ByteArray &bytes ,string &guid,uint32 &flag,uint32 &callback_id);
	int send_query_player_info (char const*guid,uint32 flag,uint32 callback_id);
	/*��ѯ��Ϣ�������*/
	int unpack_query_result_update_object (ByteArray &bytes );
	int send_query_result_update_object ();
	/*��ȡ���*/
	int unpack_receive_gift_packs (ByteArray &bytes );
	int send_receive_gift_packs ();
	/*��ͼ�������*/
	int unpack_map_update_object (ByteArray &bytes );
	int send_map_update_object ();
	/*ս����Ϣbinlog*/
	int unpack_fighting_info_update_object (ByteArray &bytes );
	int send_fighting_info_update_object ();
	/*ս����Ϣbinlog*/
	int unpack_fighting_info_update_object_2 (ByteArray &bytes );
	int send_fighting_info_update_object_2 ();
	/*���븱��*/
	int unpack_instance_enter (ByteArray &bytes ,uint32 &instance_id);
	int send_instance_enter (uint32 instance_id);
	/*�����˷��͸���������һ�׶�ָ��*/
	int unpack_instance_next_state (ByteArray &bytes ,uint16 &level,uint32 &param);
	int send_instance_next_state (uint16 level,uint32 param);
	/*�����˳�*/
	int unpack_instance_exit (ByteArray &bytes ,uint32 &reserve);
	int send_instance_exit (uint32 reserve);
	/*��ʱ���ȡ*/
	int unpack_limit_activity_receive (ByteArray &bytes ,uint32 &id,uint32 &type);
	int send_limit_activity_receive (uint32 id,uint32 type);
	/*ɱ����~~��������*/
	int unpack_kill_man (ByteArray &bytes ,string &killer,string &killer_name,string &victim,string &victim_name);
	int send_kill_man (char const*killer,char const*killer_name,char const*victim,char const*victim_name);
	/*�������*/
	int unpack_player_upgrade (ByteArray &bytes ,uint32 &guid);
	int send_player_upgrade (uint32 guid);
	/*�ֿ��Ǯ*/
	int unpack_warehouse_save_money (ByteArray &bytes ,int32 &money,int32 &money_gold,int32 &money_bills);
	int send_warehouse_save_money (int32 money,int32 money_gold,int32 money_bills);
	/*�ֿ�ȡǮ*/
	int unpack_warehouse_take_money (ByteArray &bytes ,int32 &money,int32 &money_gold,int32 &money_bills);
	int send_warehouse_take_money (int32 money,int32 money_gold,int32 money_bills);
	/*ʹ��Ԫ������ĳ��*/
	int unpack_use_gold_opt (ByteArray &bytes ,uint8 &type,string &param);
	int send_use_gold_opt (uint8 type,char const*param);
	/*ʹ��ͭǮ����ĳ��*/
	int unpack_use_silver_opt (ByteArray &bytes ,uint8 &type);
	int send_use_silver_opt (uint8 type);
	/*��̨����*/
	int unpack_gm_rightfloat (ByteArray &bytes ,uint32 &id,uint32 &end_time,uint32 &zone1,uint32 &zone2,uint32 &zone3,string &subject,string &content,string &link,uint8 &mode);
	int send_gm_rightfloat (uint32 id,uint32 end_time,uint32 zone1,uint32 zone2,uint32 zone3,char const*subject,char const*content,char const*link,uint8 mode);
	/*ɾ��ĳ����̨����*/
	int unpack_del_gm_rightfloat (ByteArray &bytes ,uint32 &id);
	int send_del_gm_rightfloat (uint32 id);
	/*Ӧ�÷�ͬ��ʱ��*/
	int unpack_sync_mstime_app (ByteArray &bytes ,uint32 &mstime_now,uint32 &time_now,uint32 &open_time);
	int send_sync_mstime_app (uint32 mstime_now,uint32 time_now,uint32 open_time);
	/*��Ҵ�ĳ������*/
	int unpack_open_window (ByteArray &bytes ,uint32 &window_type);
	int send_open_window (uint32 window_type);
	/*���Բ���*/
	int unpack_player_gag (ByteArray &bytes ,string &player_id,uint32 &end_time,string &content);
	int send_player_gag (char const*player_id,uint32 end_time,char const*content);
	/*���˲���*/
	int unpack_player_kicking (ByteArray &bytes ,string &player_id);
	int send_player_kicking (char const*player_id);
	/*�Ϸ�֪ͨ*/
	int unpack_merge_server_msg (ByteArray &bytes ,string &merge_host,uint32 &merge_port,string &merge_key,uint32 &merge_type,uint32 &reserve,uint32 &reserve2);
	int send_merge_server_msg (char const*merge_host,uint32 merge_port,char const*merge_key,uint32 merge_type,uint32 reserve,uint32 reserve2);
	/*��ȡ������Ϣ*/
	int unpack_rank_list_query (ByteArray &bytes ,uint32 &call_back_id,uint8 &rank_list_type,uint16 &start_index,uint16 &end_index);
	int send_rank_list_query (uint32 call_back_id,uint8 rank_list_type,uint16 start_index,uint16 end_index);
	/*�ͻ��˻�ȡ���а񷵻ؽ��*/
	int unpack_rank_list_query_result (ByteArray &bytes );
	int send_rank_list_query_result ();
	/*�ͻ����ȸ�����ģ����ȡuint*/
	int unpack_client_update_scened (ByteArray &bytes );
	int send_client_update_scened ();
	/*��ֵ��*/
	int unpack_num_lua (ByteArray &bytes );
	int send_num_lua ();
	/*ս��Ʒʰȡ*/
	int unpack_loot_select (ByteArray &bytes ,uint16 &x,uint16 &y);
	int send_loot_select (uint16 x,uint16 y);
	/*֪ͨ��¼������Ҵ�����Ϸ��*/
	int unpack_goback_to_game_server (ByteArray &bytes );
	int send_goback_to_game_server ();
	/*�ͻ��˰ѱ�����Ա���ݴ���������*/
	int unpack_world_war_CS_player_info (ByteArray &bytes );
	int send_world_war_CS_player_info ();
	/*��Ҽ�������뿪ĳ������*/
	int unpack_join_or_leave_server (ByteArray &bytes ,uint8 &join_or_leave,uint8 &server_type,uint32 &server_pid,uint32 &server_fd,uint32 &time);
	int send_join_or_leave_server (uint8 join_or_leave,uint8 server_type,uint32 server_pid,uint32 server_fd,uint32 time);
	/*�ͻ�����������Ա����*/
	int unpack_world_war_SC_player_info (ByteArray &bytes );
	int send_world_war_SC_player_info ();
	/*�ͻ��˶�����Ϣ*/
	int unpack_clientSubscription (ByteArray &bytes ,uint32 &guid);
	int send_clientSubscription (uint32 guid);
	/*������·�lua�ű�*/
	int unpack_lua_script (ByteArray &bytes );
	int send_lua_script ();
	/*��ɫ������Ϣ*/
	int unpack_char_update_info (ByteArray &bytes , char_create_info **info);
	int send_char_update_info (char_create_info *info);
	/*֪ͨ�ͻ��˹۲��ߵ��ӽ�*/
	int unpack_notice_watcher_map_info (ByteArray &bytes ,string &wather_guid,uint32 &map_id,uint32 &instance_id);
	int send_notice_watcher_map_info (char const*wather_guid,uint32 map_id,uint32 instance_id);
	/*�ͻ��˶��Ķ�����Ϣ*/
	int unpack_modify_watch (ByteArray &bytes ,uint8 &opt,uint32 &cid,string &key);
	int send_modify_watch (uint8 opt,uint32 cid,char const*key);
	/*�������*/
	int unpack_kuafu_chuansong (ByteArray &bytes ,string &str_data,string &watcher_guid,uint32 &reserve);
	int send_kuafu_chuansong (char const*str_data,char const*watcher_guid,uint32 reserve);
	/*��ʾ��ǰװ��*/
	int unpack_show_suit (ByteArray &bytes ,uint8 &position);
	int send_show_suit (uint8 position);
	/*��ʾ��ǰ����*/
	int unpack_show_position (ByteArray &bytes ,uint8 &channel);
	int send_show_position (uint8 channel);
	/*Ԫ������*/
	int unpack_gold_respawn (ByteArray &bytes ,uint8 &useGold);
	int send_gold_respawn (uint8 useGold);
	/*Ұ����������ʱ*/
	int unpack_field_death_cooldown (ByteArray &bytes ,uint8 &type,uint32 &value,string &killername,uint16 &cooldown,string &params);
	int send_field_death_cooldown (uint8 type,uint32 value,char const*killername,uint16 cooldown,char const*params);
	/*�̳ǹ���*/
	int unpack_mall_buy (ByteArray &bytes ,uint32 &id,uint32 &count,uint32 &time);
	int send_mall_buy (uint32 id,uint32 count,uint32 time);
	/*ǿ��*/
	int unpack_strength (ByteArray &bytes ,uint8 &part);
	int send_strength (uint8 part);
	/*ǿ���ɹ�*/
	int unpack_strength_success (ByteArray &bytes ,uint16 &level);
	int send_strength_success (uint16 level);
	/*ǿ�ƽ���*/
	int unpack_forceInto (ByteArray &bytes );
	int send_forceInto ();
	/*��������*/
	int unpack_create_faction (ByteArray &bytes ,string &name,uint8 &icon);
	int send_create_faction (char const*name,uint8 icon);
	/*��������*/
	int unpack_faction_upgrade (ByteArray &bytes );
	int send_faction_upgrade ();
	/*����������*/
	int unpack_faction_join (ByteArray &bytes ,string &id);
	int send_faction_join (char const*id);
	/*������������*/
	int unpack_raise_base_spell (ByteArray &bytes ,uint8 &raiseType,uint16 &spellId);
	int send_raise_base_spell (uint8 raiseType,uint16 spellId);
	/*�������׷�ŭ����*/
	int unpack_upgrade_anger_spell (ByteArray &bytes ,uint16 &spellId);
	int send_upgrade_anger_spell (uint16 spellId);
	/*������������*/
	int unpack_raise_mount (ByteArray &bytes );
	int send_raise_mount ();
	/*������������*/
	int unpack_upgrade_mount (ByteArray &bytes ,uint8 &useItem);
	int send_upgrade_mount (uint8 useItem);
	/*����һ����������*/
	int unpack_upgrade_mount_one_step (ByteArray &bytes ,uint8 &useItem);
	int send_upgrade_mount_one_step (uint8 useItem);
	/*��������û�����*/
	int unpack_illusion_mount_active (ByteArray &bytes ,uint16 &illuId);
	int send_illusion_mount_active (uint16 illuId);
	/*����û�����*/
	int unpack_illusion_mount (ByteArray &bytes ,uint16 &illuId);
	int send_illusion_mount (uint16 illuId);
	/*�������*/
	int unpack_ride_mount (ByteArray &bytes );
	int send_ride_mount ();
	/*grid�е�unit��Ծ*/
	int unpack_grid_unit_jump (ByteArray &bytes );
	int send_grid_unit_jump ();
	/*��ʯ*/
	int unpack_gem (ByteArray &bytes ,uint8 &part);
	int send_gem (uint8 part);
	/*�����л�ģʽ*/
	int unpack_change_battle_mode (ByteArray &bytes ,uint8 &mode);
	int send_change_battle_mode (uint8 mode);
	/*��ƽģʽCD*/
	int unpack_peace_mode_cd (ByteArray &bytes ,uint8 &mode);
	int send_peace_mode_cd (uint8 mode);
	/*�������*/
	int unpack_divine_active (ByteArray &bytes ,uint8 &id);
	int send_divine_active (uint8 id);
	/*�������*/
	int unpack_divine_uplev (ByteArray &bytes ,uint8 &id);
	int send_divine_uplev (uint8 id);
	/*�л����*/
	int unpack_divine_switch (ByteArray &bytes ,uint8 &id);
	int send_divine_switch (uint8 id);
	/*������Ծ*/
	int unpack_jump_start (ByteArray &bytes ,uint16 &pos_x,uint16 &pos_y);
	int send_jump_start (uint16 pos_x,uint16 pos_y);
	/*�������vip����*/
	int unpack_enter_vip_instance (ByteArray &bytes ,uint16 &id,uint8 &hard);
	int send_enter_vip_instance (uint16 id,uint8 hard);
	/*����ɨ��vip����*/
	int unpack_sweep_vip_instance (ByteArray &bytes ,uint16 &id);
	int send_sweep_vip_instance (uint16 id);
	/*���йһ�*/
	int unpack_hang_up (ByteArray &bytes );
	int send_hang_up ();
	/*���йһ�����*/
	int unpack_hang_up_setting (ByteArray &bytes ,uint32 &value0,uint32 &value1,uint32 &value2,uint32 &value3);
	int send_hang_up_setting (uint32 value0,uint32 value1,uint32 value2,uint32 value3);
	/*�����������������*/
	int unpack_enter_trial_instance (ByteArray &bytes );
	int send_enter_trial_instance ();
	/*ɨ������������*/
	int unpack_sweep_trial_instance (ByteArray &bytes );
	int send_sweep_trial_instance ();
	/*����������*/
	int unpack_reset_trial_instance (ByteArray &bytes );
	int send_reset_trial_instance ();
	/*ɨ����������*/
	int unpack_sweep_instance_reward (ByteArray &bytes ,uint8 &inst_sub_type,uint8 &data1,uint8 &data2,uint8 &data3, vector< item_reward_info > &list);
	int send_sweep_instance_reward (uint8 inst_sub_type,uint8 data1,uint8 data2,uint8 data3,const vector< item_reward_info > &list );
	/*�ؽ�����*/
	int unpack_reenter_instance (ByteArray &bytes );
	int send_reenter_instance ();
	/*�������Ϣ*/
	int unpack_merry_go_round (ByteArray &bytes );
	int send_merry_go_round ();
	/*��Ӻ���*/
	int unpack_social_add_friend (ByteArray &bytes ,string &guid);
	int send_social_add_friend (char const*guid);
	/*ͬ����Ӻ���*/
	int unpack_social_sureadd_friend (ByteArray &bytes ,string &guid);
	int send_social_sureadd_friend (char const*guid);
	/*��������*/
	int unpack_social_gift_friend (ByteArray &bytes ,string &guid, vector< item_reward_info > &gift);
	int send_social_gift_friend (char const*guid,const vector< item_reward_info > &gift );
	/*�Ƽ������б�*/
	int unpack_social_recommend_friend (ByteArray &bytes );
	int send_social_recommend_friend ();
	/*�Ƽ������б�*/
	int unpack_social_get_recommend_friend (ByteArray &bytes , vector< social_friend_info > &list);
	int send_social_get_recommend_friend (const vector< social_friend_info > &list );
	/*����*/
	int unpack_social_revenge_enemy (ByteArray &bytes ,string &guid);
	int send_social_revenge_enemy (char const*guid);
	/*ɾ������*/
	int unpack_social_del_friend (ByteArray &bytes ,string &guid);
	int send_social_del_friend (char const*guid);
	/*�س�*/
	int unpack_teleport_main_city (ByteArray &bytes );
	int send_teleport_main_city ();
	/*��ͬƵ������*/
	int unpack_chat_by_channel (ByteArray &bytes ,uint8 &channel,string &content);
	int send_chat_by_channel (uint8 channel,char const*content);
	/*��������*/
	int unpack_send_chat (ByteArray &bytes ,uint8 &channel,string &guid,uint8 &title,string &name,uint8 &vip,uint8 &zs,uint8 &lvl,uint8 &gender,string &content,string &to_guid,string &faction_guid);
	int send_send_chat (uint8 channel,char const*guid,uint8 title,char const*name,uint8 vip,uint8 zs,uint8 lvl,uint8 gender,char const*content,char const*to_guid,char const*faction_guid);
	/*��������б�*/
	int unpack_social_clear_apply (ByteArray &bytes );
	int send_social_clear_apply ();
	/*���þܾ�������Ϣ*/
	int unpack_msg_decline (ByteArray &bytes ,uint32 &value0,uint32 &value1);
	int send_msg_decline (uint32 value0,uint32 value1);
	/*�����б�*/
	int unpack_faction_get_list_result (ByteArray &bytes , vector< faction_info > &list,uint8 &curpag,uint8 &maxpag);
	int send_faction_get_list_result (const vector< faction_info > &list ,uint8 curpag,uint8 maxpag);
	/*��ȡ�����б�*/
	int unpack_faction_getlist (ByteArray &bytes ,uint8 &page,uint8 &num,uint8 &grep);
	int send_faction_getlist (uint8 page,uint8 num,uint8 grep);
	/*���ɹ���*/
	int unpack_faction_manager (ByteArray &bytes ,uint8 &opt_type,uint16 &reserve_int1,uint16 &reserve_int2,string &reserve_str1,string &reserve_str2);
	int send_faction_manager (uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2);
	/*���ɳ�Ա����*/
	int unpack_faction_member_operate (ByteArray &bytes ,uint8 &opt_type,uint16 &reserve_int1,uint16 &reserve_int2,string &reserve_str1,string &reserve_str2);
	int send_faction_member_operate (uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2);
	/*���ټ������*/
	int unpack_faction_fast_join (ByteArray &bytes );
	int send_faction_fast_join ();
	/*ͨ��������Ӻ���*/
	int unpack_social_add_friend_byname (ByteArray &bytes ,string &name);
	int send_social_add_friend_byname (char const*name);
	/*���ʼ�*/
	int unpack_read_mail (ByteArray &bytes ,uint16 &indx);
	int send_read_mail (uint16 indx);
	/*��ȡ�ʼ�*/
	int unpack_pick_mail (ByteArray &bytes ,uint16 &indx);
	int send_pick_mail (uint16 indx);
	/*ɾ���ʼ�*/
	int unpack_remove_mail (ByteArray &bytes ,uint16 &indx);
	int send_remove_mail (uint16 indx);
	/*һ����ȡ�ʼ�*/
	int unpack_pick_mail_one_step (ByteArray &bytes );
	int send_pick_mail_one_step ();
	/*һ��ɾ���ʼ�*/
	int unpack_remove_mail_one_step (ByteArray &bytes );
	int send_remove_mail_one_step ();
	/*����ĳ��*/
	int unpack_block_chat (ByteArray &bytes ,string &guid);
	int send_block_chat (char const*guid);
	/*ȡ������*/
	int unpack_cancel_block_chat (ByteArray &bytes ,uint8 &indx);
	int send_cancel_block_chat (uint8 indx);
	/*ʹ����Ҫ�㲥����Ϸ����*/
	int unpack_use_broadcast_gameobject (ByteArray &bytes ,uint32 &target);
	int send_use_broadcast_gameobject (uint32 target);
	/*����BOSS����*/
	int unpack_world_boss_enroll (ByteArray &bytes );
	int send_world_boss_enroll ();
	/*����BOSS��ս*/
	int unpack_world_boss_fight (ByteArray &bytes );
	int send_world_boss_fight ();
	/*����*/
	int unpack_change_line (ByteArray &bytes ,uint32 &lineNo);
	int send_change_line (uint32 lineNo);
	/*roll����BOSS����*/
	int unpack_roll_world_boss_treasure (ByteArray &bytes );
	int send_roll_world_boss_treasure ();
	/*roll����*/
	int unpack_roll_result (ByteArray &bytes ,uint8 &point,string &name,uint8 &isHighest,uint32 &timestamp,uint8 &rollid);
	int send_roll_result (uint8 point,char const*name,uint8 isHighest,uint32 timestamp,uint8 rollid);
	/*��ǰBOSS�˺�����*/
	int unpack_boss_rank (ByteArray &bytes ,uint8 &rankType, vector< rank_info > &rankList,uint8 &mine);
	int send_boss_rank (uint8 rankType,const vector< rank_info > &rankList ,uint8 mine);
	/*���а����*/
	int unpack_rank_add_like (ByteArray &bytes ,uint8 &type,string &guid);
	int send_rank_add_like (uint8 type,char const*guid);
	/*���а���޽��*/
	int unpack_rank_add_like_result (ByteArray &bytes ,uint8 &type,string &guid,uint32 &num);
	int send_rank_add_like_result (uint8 type,char const*guid,uint32 num);
	/*������Դ����*/
	int unpack_res_instance_enter (ByteArray &bytes ,uint8 &id);
	int send_res_instance_enter (uint8 id);
	/*ɨ����Դ����*/
	int unpack_res_instance_sweep (ByteArray &bytes ,uint8 &id);
	int send_res_instance_sweep (uint8 id);
	/*�鿴����ͼ�ķ��ߺ�*/
	int unpack_show_map_line (ByteArray &bytes );
	int send_show_map_line ();
	/*���ر���ͼ�ķ��ߺ���Ϣ*/
	int unpack_send_map_line (ByteArray &bytes , vector< line_info > &info);
	int send_send_map_line (const vector< line_info > &info );
	/*��ý�����ʾ*/
	int unpack_item_notice (ByteArray &bytes ,uint8 &showType, vector< item_reward_info > &list);
	int send_item_notice (uint8 showType,const vector< item_reward_info > &list );
	/*���͵�ĳ�������ͼ*/
	int unpack_teleport_map (ByteArray &bytes ,uint32 &mapid,uint32 &lineNo);
	int send_teleport_map (uint32 mapid,uint32 lineNo);
	/*���͵�Ұ��boss�Ա�*/
	int unpack_teleport_field_boss (ByteArray &bytes ,uint32 &mapid,uint32 &lineNo);
	int send_teleport_field_boss (uint32 mapid,uint32 lineNo);
	/*��Ծ�Ƚ���*/
	int unpack_get_activity_reward (ByteArray &bytes ,uint8 &id,uint8 &vip);
	int send_get_activity_reward (uint8 id,uint8 vip);
	/*�ɾͽ���*/
	int unpack_get_achieve_reward (ByteArray &bytes ,uint8 &id);
	int send_get_achieve_reward (uint8 id);
	/*�ܳɾͽ���*/
	int unpack_get_achieve_all_reward (ByteArray &bytes );
	int send_get_achieve_all_reward ();
	/*װ���ƺ�*/
	int unpack_set_title (ByteArray &bytes ,uint8 &id);
	int send_set_title (uint8 id);
	/*��ʼ���ƺ�*/
	int unpack_init_title (ByteArray &bytes ,uint8 &id);
	int send_init_title (uint8 id);
	/*��ȡ�׳佱��*/
	int unpack_welfare_shouchong_reward (ByteArray &bytes );
	int send_welfare_shouchong_reward ();
	/*ÿ��ǩ������*/
	int unpack_welfare_checkin (ByteArray &bytes );
	int send_welfare_checkin ();
	/*�ۻ�ǩ������*/
	int unpack_welfare_checkin_all (ByteArray &bytes ,uint8 &id);
	int send_welfare_checkin_all (uint8 id);
	/*��ǩ����*/
	int unpack_welfare_checkin_getback (ByteArray &bytes ,uint8 &id);
	int send_welfare_checkin_getback (uint8 id);
	/*�ȼ�����*/
	int unpack_welfare_level (ByteArray &bytes ,uint8 &id);
	int send_welfare_level (uint8 id);
	/*��һؽ���*/
	int unpack_welfare_active_getback (ByteArray &bytes ,uint8 &id,uint8 &best,uint16 &num);
	int send_welfare_active_getback (uint8 id,uint8 best,uint16 num);
	/*��ȡ������*/
	int unpack_pick_quest_reward (ByteArray &bytes ,uint8 &indx);
	int send_pick_quest_reward (uint8 indx);
	/*��npc�Ի�*/
	int unpack_talk_with_npc (ByteArray &bytes ,uint16 &entry,uint16 &questId);
	int send_talk_with_npc (uint16 entry,uint16 questId);
	/*ʹ��������Ʒ*/
	int unpack_use_virtual_item (ByteArray &bytes ,uint16 &entry);
	int send_use_virtual_item (uint16 entry);
	/*��ȡ�����½ڽ���*/
	int unpack_pick_quest_chapter_reward (ByteArray &bytes ,uint8 &indx);
	int send_pick_quest_chapter_reward (uint8 indx);
	/*3v3���ƥ��*/
	int unpack_kuafu_3v3_match (ByteArray &bytes );
	int send_kuafu_3v3_match ();
	/*�����ʼƥ��*/
	int unpack_kuafu_match_start (ByteArray &bytes ,uint8 &indx);
	int send_kuafu_match_start (uint8 indx);
	/*3v3�������*/
	int unpack_kuafu_3v3_buytimes (ByteArray &bytes ,uint8 &num);
	int send_kuafu_3v3_buytimes (uint8 num);
	/*3v3ÿ�ջ�Ծ����*/
	int unpack_kuafu_3v3_dayreward (ByteArray &bytes ,uint8 &id);
	int send_kuafu_3v3_dayreward (uint8 id);
	/*����3v3���а�*/
	int unpack_kuafu_3v3_getranlist (ByteArray &bytes );
	int send_kuafu_3v3_getranlist ();
	/*3v3���а����б�*/
	int unpack_kuafu_3v3_ranlist (ByteArray &bytes ,string &list);
	int send_kuafu_3v3_ranlist (char const*list);
	/*�������н����б�*/
	int unpack_welfare_getalllist_getback (ByteArray &bytes ,uint8 &best);
	int send_welfare_getalllist_getback (uint8 best);
	/*�����б�*/
	int unpack_welfare_rewardlist_getback (ByteArray &bytes ,string &list,string &cost);
	int send_welfare_rewardlist_getback (char const*list,char const*cost);
	/*һ����ȡ���и���*/
	int unpack_welfare_getall_getback (ByteArray &bytes ,uint8 &best);
	int send_welfare_getall_getback (uint8 best);
	/*����3v3���а��Լ�������*/
	int unpack_kuafu_3v3_getmyrank (ByteArray &bytes );
	int send_kuafu_3v3_getmyrank ();
	/*3v3���а��Լ������ν��*/
	int unpack_kuafu_3v3_myrank (ByteArray &bytes ,uint8 &rank);
	int send_kuafu_3v3_myrank (uint8 rank);
	/*��ɱ����*/
	int unpack_kuafu_3v3_kill_detail (ByteArray &bytes ,uint32 &indx1,uint32 &indx2);
	int send_kuafu_3v3_kill_detail (uint32 indx1,uint32 indx2);
	/*���ƥ��ȴ�����*/
	int unpack_kuafu_3v3_wait_info (ByteArray &bytes , vector< wait_info > &list);
	int send_kuafu_3v3_wait_info (const vector< wait_info > &list );
	/*ȡ��ƥ��*/
	int unpack_kuafu_3v3_cancel_match (ByteArray &bytes ,uint32 &type);
	int send_kuafu_3v3_cancel_match (uint32 type);
	/*ƥ�䵽��&���ܻ��߾ܾ�*/
	int unpack_kuafu_3v3_match_oper (ByteArray &bytes ,uint32 &oper);
	int send_kuafu_3v3_match_oper (uint32 oper);
	/*�ܾ�����*/
	int unpack_kuafu_3v3_decline_match (ByteArray &bytes ,uint32 &type);
	int send_kuafu_3v3_decline_match (uint32 type);
	/*�ɸ��ᱦ���ƥ��*/
	int unpack_kuafu_xianfu_match (ByteArray &bytes ,uint8 &indx);
	int send_kuafu_xianfu_match (uint8 indx);
	/*�������ƥ��ȴ�*/
	int unpack_kuafu_match_wait (ByteArray &bytes ,uint8 &type,uint8 &target,uint8 &count,uint32 &data,string &params);
	int send_kuafu_match_wait (uint8 type,uint8 target,uint8 count,uint32 data,char const*params);
	/*�ɸ��ᱦС��ͼ��Ϣ*/
	int unpack_kuafu_xianfu_minimap_info (ByteArray &bytes );
	int send_kuafu_xianfu_minimap_info ();
	/*�����ɸ�����ȯ*/
	int unpack_buy_xianfu_item (ByteArray &bytes ,uint8 &type,uint8 &indx,uint16 &count);
	int send_buy_xianfu_item (uint8 type,uint8 indx,uint16 count);
	/*�������*/
	int unpack_xianfu_random_respawn (ByteArray &bytes );
	int send_xianfu_random_respawn ();
	/*����̨��ս*/
	int unpack_doujiantai_fight (ByteArray &bytes ,uint16 &rank);
	int send_doujiantai_fight (uint16 rank);
	/*����̨�������*/
	int unpack_doujiantai_buytime (ByteArray &bytes ,uint8 &num);
	int send_doujiantai_buytime (uint8 num);
	/*����̨����CD*/
	int unpack_doujiantai_clearcd (ByteArray &bytes );
	int send_doujiantai_clearcd ();
	/*����̨��ʤ����*/
	int unpack_doujiantai_first_reward (ByteArray &bytes ,uint8 &id);
	int send_doujiantai_first_reward (uint8 id);
	/*����̨��ս������Ϣ*/
	int unpack_doujiantai_get_enemys_info (ByteArray &bytes );
	int send_doujiantai_get_enemys_info ();
	/*����̨���а�*/
	int unpack_doujiantai_get_rank (ByteArray &bytes ,uint16 &startIdx,uint16 &endIdx);
	int send_doujiantai_get_rank (uint16 startIdx,uint16 endIdx);
	/*����̨ˢ�¶���*/
	int unpack_doujiantai_refresh_enemys (ByteArray &bytes );
	int send_doujiantai_refresh_enemys ();
	/*����̨����*/
	int unpack_doujiantai_top3 (ByteArray &bytes );
	int send_doujiantai_top3 ();
	/*ʹ������*/
	int unpack_use_jump_point (ByteArray &bytes ,uint32 &id);
	int send_use_jump_point (uint32 id);
	/*������Ʒ*/
	int unpack_bag_item_sell (ByteArray &bytes ,string &item_guid,uint32 &count);
	int send_bag_item_sell (char const*item_guid,uint32 count);
	/*������Ʒ*/
	int unpack_bag_item_sort (ByteArray &bytes );
	int send_bag_item_sort ();
	/*�ύ�ճ�����*/
	int unpack_submit_quest_daily2 (ByteArray &bytes );
	int send_submit_quest_daily2 ();
	/*���Ըı�*/
	int unpack_attribute_changed (ByteArray &bytes );
	int send_attribute_changed ();
	/*�����и�ǿװ��*/
	int unpack_bag_find_equip_better (ByteArray &bytes ,uint32 &item_id,uint32 &pos);
	int send_bag_find_equip_better (uint32 item_id,uint32 pos);
	/*ģ�����*/
	int unpack_module_active (ByteArray &bytes ,uint32 &moduleId);
	int send_module_active (uint32 moduleId);
	/*��ȡ�ճ�������*/
	int unpack_pick_daily2_quest_reward (ByteArray &bytes ,uint8 &indx);
	int send_pick_daily2_quest_reward (uint8 indx);
	/*��ɵ�ǰ����*/
	int unpack_finish_now_guide (ByteArray &bytes );
	int send_finish_now_guide ();
	/*ȡ����������Ϣ*/
	int unpack_get_cultivation_info (ByteArray &bytes );
	int send_get_cultivation_info ();
	/*������������Ϣ*/
	int unpack_update_cultivation_info (ByteArray &bytes ,uint32 &start_time,uint32 &lost);
	int send_update_cultivation_info (uint32 start_time,uint32 lost);
	/*ȡ�õ�ǰ����������������Ϣ*/
	int unpack_get_cultivation_rivals_info (ByteArray &bytes );
	int send_get_cultivation_rivals_info ();
	/*����������������Ϣ*/
	int unpack_update_cultivation_rivals_info_list (ByteArray &bytes , vector< cultivation_rivals_info > &list);
	int send_update_cultivation_rivals_info_list (const vector< cultivation_rivals_info > &list );
	/*��ȡ����������*/
	int unpack_get_cultivation_reward (ByteArray &bytes );
	int send_get_cultivation_reward ();
	/*ˢ������������*/
	int unpack_refresh_cultivation_rivals (ByteArray &bytes );
	int send_refresh_cultivation_rivals ();
	/*�Ӷ�����������*/
	int unpack_plunder_cultivation_rival (ByteArray &bytes ,uint32 &index);
	int send_plunder_cultivation_rival (uint32 index);
	/*������������������*/
	int unpack_revenge_cultivation_rival (ByteArray &bytes ,uint32 &index);
	int send_revenge_cultivation_rival (uint32 index);
	/*����������ʣ����ս����*/
	int unpack_buy_cultivation_left_plunder_count (ByteArray &bytes ,uint32 &count);
	int send_buy_cultivation_left_plunder_count (uint32 count);
	/*����������ս�����*/
	int unpack_show_cultivation_result_list (ByteArray &bytes ,int32 &result,string &name, vector< item_reward_info > &list);
	int send_show_cultivation_result_list (int32 result,char const*name,const vector< item_reward_info > &list );
	/*��ȡ��¼������*/
	int unpack_get_login_activity_reward (ByteArray &bytes ,uint32 &id);
	int send_get_login_activity_reward (uint32 id);
	/*֪ͨ�ͻ����ͷ���������*/
	int unpack_cast_spell_start (ByteArray &bytes ,uint32 &caster_guid,uint32 &target_guid,uint16 &spellid,string &data);
	int send_cast_spell_start (uint32 caster_guid,uint32 target_guid,uint16 spellid,char const*data);
	/*��ɷ�ǿ�������Ĳ���*/
	int unpack_finish_optional_guide_step (ByteArray &bytes ,uint32 &guide_id,uint8 &step);
	int send_finish_optional_guide_step (uint32 guide_id,uint8 step);
	/*ִ�нӵ������Ժ������*/
	int unpack_execute_quest_cmd_after_accepted (ByteArray &bytes ,uint16 &indx);
	int send_execute_quest_cmd_after_accepted (uint16 indx);
	/*֪ͨ�ͻ�����ʾ����*/
	int unpack_show_unit_attribute (ByteArray &bytes );
	int send_show_unit_attribute ();
	/*���ؼ���*/
	int unpack_back_to_famity (ByteArray &bytes );
	int send_back_to_famity ();
	/*���ؼ���boss���*/
	int unpack_faction_boss_send_result (ByteArray &bytes ,uint32 &result,uint32 &boss_id,uint32 &money);
	int send_faction_boss_send_result (uint32 result,uint32 boss_id,uint32 money);
	/*��սboss*/
	int unpack_challange_boss (ByteArray &bytes );
	int send_challange_boss ();
	/*��ȡ���߽���*/
	int unpack_pick_offline_reward (ByteArray &bytes );
	int send_pick_offline_reward ();
	/*���߽������*/
	int unpack_offline_reward_result (ByteArray &bytes ,uint32 &reserve,uint32 &reserve2,uint32 &reserve3,uint32 &reserve4, vector< item_reward_info > &list);
	int send_offline_reward_result (uint32 reserve,uint32 reserve2,uint32 reserve3,uint32 reserve4,const vector< item_reward_info > &list );
	/*����װ��*/
	int unpack_smelting_equip (ByteArray &bytes ,string &pos_str);
	int send_smelting_equip (char const*pos_str);
	/*�Ͻ�װ��*/
	int unpack_storehouse_hand_in (ByteArray &bytes ,string &pos_str);
	int send_storehouse_hand_in (char const*pos_str);
	/*�һ�װ��*/
	int unpack_storehouse_exchange (ByteArray &bytes ,uint32 &pos);
	int send_storehouse_exchange (uint32 pos);
	/*����װ��*/
	int unpack_storehouse_destroy (ByteArray &bytes ,uint32 &pos);
	int send_storehouse_destroy (uint32 pos);
	/*��������*/
	int unpack_send_faction_gift (ByteArray &bytes , vector< item_reward_info > &list,string &msg,uint32 &msg_type);
	int send_send_faction_gift (const vector< item_reward_info > &list ,char const*msg,uint32 msg_type);
	/*��ȡ���⽱��*/
	int unpack_get_faction_gift_exreward (ByteArray &bytes ,uint32 &count_id);
	int send_get_faction_gift_exreward (uint32 count_id);
	/*��ȡ���ж��⽱��*/
	int unpack_get_all_faction_gift_exreward (ByteArray &bytes );
	int send_get_all_faction_gift_exreward ();
	/*���������б�*/
	int unpack_show_faction_gift_page (ByteArray &bytes );
	int send_show_faction_gift_page ();
	/*����������Ϣ*/
	int unpack_show_faction_gift_info (ByteArray &bytes );
	int send_show_faction_gift_info ();
	/*����Ů��δ��л����*/
	int unpack_show_faction_gift_unthank_page (ByteArray &bytes );
	int send_show_faction_gift_unthank_page ();
	/*����Ů����ʷ��¼*/
	int unpack_show_faction_gift_history_page (ByteArray &bytes );
	int send_show_faction_gift_history_page ();
	/*���������������*/
	int unpack_get_faction_gift_rank_page (ByteArray &bytes ,uint32 &page);
	int send_get_faction_gift_rank_page (uint32 page);
	/*���ؼ�����������*/
	int unpack_show_faction_gift_rank_result_list (ByteArray &bytes , vector< faction_gift_rank_info > &list, faction_gift_rank_info **info,uint32 &page);
	int send_show_faction_gift_rank_result_list (const vector< faction_gift_rank_info > &list ,faction_gift_rank_info *info,uint32 page);
	/*���ؼ����������б仯*/
	int unpack_show_faction_gift_rank_change (ByteArray &bytes ,uint32 &old_rank,uint32 &new_rank, faction_gift_rank_info **info);
	int send_show_faction_gift_rank_change (uint32 old_rank,uint32 new_rank,faction_gift_rank_info *info);
	/*���ر�������������*/
	int unpack_show_faction_gift_rank_info (ByteArray &bytes , faction_gift_rank_info **info);
	int send_show_faction_gift_rank_info (faction_gift_rank_info *info);
	/*���ǿ��*/
	int unpack_divine_forge (ByteArray &bytes ,uint32 &id,uint32 &count);
	int send_divine_forge (uint32 id,uint32 count);
	/*�������*/
	int unpack_divine_advance (ByteArray &bytes ,uint32 &id);
	int send_divine_advance (uint32 id);
	/*�������*/
	int unpack_divine_spirit (ByteArray &bytes ,uint32 &id,uint32 &protect,uint32 &improve);
	int send_divine_spirit (uint32 id,uint32 protect,uint32 improve);
	/*��ѯȫ��boss��Ϣ*/
	int unpack_query_mass_boss_info (ByteArray &bytes ,uint8 &id);
	int send_query_mass_boss_info (uint8 id);
	/*ȫ��boss��Ϣ���*/
	int unpack_mass_boss_info_ret (ByteArray &bytes ,uint32 &count,uint8 &percent);
	int send_mass_boss_info_ret (uint32 count,uint8 percent);
	/*��ѯȫ��boss���а�*/
	int unpack_query_mass_boss_rank (ByteArray &bytes ,uint8 &id);
	int send_query_mass_boss_rank (uint8 id);
	/*ȫ��boss���н��*/
	int unpack_mass_boss_rank_result (ByteArray &bytes , vector< mass_boss_rank_info > &info);
	int send_mass_boss_rank_result (const vector< mass_boss_rank_info > &info );
	/*��սȫ��boss*/
	int unpack_try_mass_boss (ByteArray &bytes ,uint8 &id);
	int send_try_mass_boss (uint8 id);
	/*������սȫ��boss����*/
	int unpack_buy_mass_boss_times (ByteArray &bytes ,uint8 &cnt);
	int send_buy_mass_boss_times (uint8 cnt);
	/*��Ӹ������ƥ��*/
	int unpack_group_instance_match (ByteArray &bytes ,uint8 &indx);
	int send_group_instance_match (uint8 indx);
	/*��Ӹ��������������*/
	int unpack_buy_group_instance_times (ByteArray &bytes ,uint8 &count);
	int send_buy_group_instance_times (uint8 count);
	/*��������*/
	int unpack_talisman_active (ByteArray &bytes ,uint32 &id);
	int send_talisman_active (uint32 id);
	/*����ע��*/
	int unpack_talisman_lvup (ByteArray &bytes ,uint32 &id);
	int send_talisman_lvup (uint32 id);
	/*���𼤻�*/
	int unpack_wings_active (ByteArray &bytes );
	int send_wings_active ();
	/*����ף��*/
	int unpack_wings_bless (ByteArray &bytes );
	int send_wings_bless ();
	/*��������*/
	int unpack_wings_rankup (ByteArray &bytes );
	int send_wings_rankup ();
	/*����ǿ��*/
	int unpack_wings_strength (ByteArray &bytes );
	int send_wings_strength ();
	/*��������*/
	int unpack_meridian_practise (ByteArray &bytes );
	int send_meridian_practise ();
	/*�Ӿ�����������ֵ*/
	int unpack_add_meridian_exp (ByteArray &bytes ,uint8 &id);
	int send_add_meridian_exp (uint8 id);
	/*��������ȼ�*/
	int unpack_raise_mount_level_base (ByteArray &bytes );
	int send_raise_mount_level_base ();
	/*��������*/
	int unpack_active_mount (ByteArray &bytes );
	int send_active_mount ();
	/*����������ս�������*/
	int unpack_show_faction_bossdefense_damage_list (ByteArray &bytes , vector< mass_boss_rank_info > &list);
	int send_show_faction_bossdefense_damage_list (const vector< mass_boss_rank_info > &list );
	/*�����޾�Զ��ɨ�����*/
	int unpack_show_faction_tower_sweep_list (ByteArray &bytes , vector< item_reward_info > &list);
	int send_show_faction_tower_sweep_list (const vector< item_reward_info > &list );
	/*�������*/
	int unpack_send_instance_result (ByteArray &bytes ,uint8 &state,uint8 &cd, vector< item_reward_info > &list,uint8 &type,string &data);
	int send_send_instance_result (uint8 state,uint8 cd,const vector< item_reward_info > &list ,uint8 type,char const*data);
	/*ƥ�䵥��pvp*/
	int unpack_match_single_pvp (ByteArray &bytes );
	int send_match_single_pvp ();
	/*������pvp����*/
	int unpack_buy_match_single_pvp_times (ByteArray &bytes ,uint8 &cnt);
	int send_buy_match_single_pvp_times (uint8 cnt);
	/*��ȡ����pvp���⽱��*/
	int unpack_pick_match_single_pvp_extra_reward (ByteArray &bytes ,uint8 &id);
	int send_pick_match_single_pvp_extra_reward (uint8 id);
	/*װ�����ɲ���*/
	int unpack_equipdevelop_operate (ByteArray &bytes ,uint8 &opt_type,uint16 &reserve_int1,uint16 &reserve_int2,string &reserve_str1,string &reserve_str2);
	int send_equipdevelop_operate (uint8 opt_type,uint16 reserve_int1,uint16 reserve_int2,char const*reserve_str1,char const*reserve_str2);
	/*�������*/
	int unpack_active_appearance (ByteArray &bytes ,uint16 &id);
	int send_active_appearance (uint16 id);
	/*װ�����*/
	int unpack_equip_appearance (ByteArray &bytes ,uint16 &id);
	int send_equip_appearance (uint16 id);
	/*ȡ��װ�����*/
	int unpack_cancel_equip_appearance (ByteArray &bytes ,uint8 &type);
	int send_cancel_equip_appearance (uint8 type);
	/*����*/
	int unpack_rename (ByteArray &bytes ,string &name);
	int send_rename (char const*name);
	/*���߽����ƺ�*/
	int unpack_unlock_title (ByteArray &bytes ,uint8 &indx);
	int send_unlock_title (uint8 indx);
	/*���򸴳����*/
	int unpack_social_buy_revenge_times (ByteArray &bytes ,uint8 &count);
	int send_social_buy_revenge_times (uint8 count);
	/*�����������ð�ո���*/
	int unpack_enter_risk_instance (ByteArray &bytes );
	int send_enter_risk_instance ();
	/*ɾ������*/
	int unpack_social_remove_enemy (ByteArray &bytes ,string &guid);
	int send_social_remove_enemy (char const*guid);
	/*�鿴�������*/
	int unpack_get_player_overview (ByteArray &bytes ,string &guid);
	int send_get_player_overview (char const*guid);
	/*�����������*/
	int unpack_show_player_overview (ByteArray &bytes ,string &guid,string &name,uint32 &force,uint32 &vip,uint32 &title,uint32 &gender,uint32 &coat,uint32 &weapon);
	int send_show_player_overview (char const*guid,char const*name,uint32 force,uint32 vip,uint32 title,uint32 gender,uint32 coat,uint32 weapon);
	/*����������*/
	int unpack_send_faction_invite (ByteArray &bytes ,string &guid);
	int send_send_faction_invite (char const*guid);
	/*��ʾ����*/
	int unpack_show_faction_invite (ByteArray &bytes ,string &guid,string &name,string &faction_guid,string &faction_name);
	int send_show_faction_invite (char const*guid,char const*name,char const*faction_guid,char const*faction_name);
	/*����vip���*/
	int unpack_buy_vipgift (ByteArray &bytes ,uint32 &id);
	int send_buy_vipgift (uint32 id);
	/*����ÿ�����*/
	int unpack_activity_opt_buy_dailygift (ByteArray &bytes ,uint32 &act_id,uint32 &index);
	int send_activity_opt_buy_dailygift (uint32 act_id,uint32 index);
	/*�齱*/
	int unpack_draw_lottery (ByteArray &bytes ,uint32 &actId,uint8 &type);
	int send_draw_lottery (uint32 actId,uint8 type);
	/*��ȡ��������н��Ƚ���*/
	int unpack_activity_opt_get_rank_process_reward (ByteArray &bytes ,uint32 &act_id,uint32 &index);
	int send_activity_opt_get_rank_process_reward (uint32 act_id,uint32 index);
	/*��ȡ��������а�*/
	int unpack_activity_opt_get_rank_list (ByteArray &bytes ,uint32 &act_id);
	int send_activity_opt_get_rank_list (uint32 act_id);
	/*���ػ�������а�*/
	int unpack_activity_opt_show_rank_list (ByteArray &bytes ,uint32 &act_id, vector< act_rank_info > &list);
	int send_activity_opt_show_rank_list (uint32 act_id,const vector< act_rank_info > &list );
	/*�����޶����*/
	int unpack_activity_opt_buy_limitgift (ByteArray &bytes ,uint32 &act_id,uint32 &index);
	int send_activity_opt_buy_limitgift (uint32 act_id,uint32 index);
	/*��ȡ�ۼƳ�ֵ����*/
	int unpack_welfare_get_recharge_reward (ByteArray &bytes ,uint8 &id);
	int send_welfare_get_recharge_reward (uint8 id);
	/*��ȡ�ۼ����ѽ���*/
	int unpack_welfare_get_consume_reward (ByteArray &bytes ,uint8 &id);
	int send_welfare_get_consume_reward (uint8 id);
	/*��ȡ���մ�����*/
	int unpack_welfare_get_sevenday_reward (ByteArray &bytes ,uint8 &id);
	int send_welfare_get_sevenday_reward (uint8 id);
	/*����������ʱ��*/
	int unpack_send_server_open_time (ByteArray &bytes ,uint32 &open_time);
	int send_send_server_open_time (uint32 open_time);
	/*��������ð�����а�*/
	int unpack_risk_get_rank (ByteArray &bytes );
	int send_risk_get_rank ();
	/*����ð�����а���Ϣ */
	int unpack_risk_get_rank_result (ByteArray &bytes , vector< act_rank_info > &list);
	int send_risk_get_rank_result (const vector< act_rank_info > &list );
	/*���ó���*/
	int unpack_set_orient (ByteArray &bytes ,uint16 &angle);
	int send_set_orient (uint16 angle);
	/*ҡ��ҡǮ��*/
	int unpack_use_moneytree (ByteArray &bytes );
	int send_use_moneytree ();
	/*��ȡҡǮ�����*/
	int unpack_get_moneytree_gift (ByteArray &bytes ,uint32 &id);
	int send_get_moneytree_gift (uint32 id);
	/*�޸Ļþ�������id*/
	int unpack_set_world_risk_last_id (ByteArray &bytes ,uint32 &id);
	int send_set_world_risk_last_id (uint32 id);
	/*�������Boss*/
	int unpack_enter_private_boss (ByteArray &bytes ,uint32 &id);
	int send_enter_private_boss (uint32 id);
};

#endif
