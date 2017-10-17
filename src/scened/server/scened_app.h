/************************************************************************
 * file	: scened_app.h                                                                     
 * desc	: ��������Ӧ�ó���
 *		�����������ŵ�ͼʵ������,������ҪӦ���ķ�Ҫ�����Щ��ͼ���й���
 *
 *
 * author:	linbc
 * date:	20110518
 * version:
 ************************************************************************/
#ifndef _SCENED_APP_H_
#define _SCENED_APP_H_

#include <svrcore.h>
#include <comm/timer.h>
#include <protocol/external.h>
#include "ScenedObjectManager.h"

class Player;
class Creature;

//��Ϸ����
struct TEA_SVRCORE_SPEC ScenedConfig:public GameConfig
{
	virtual ~ScenedConfig(){}
	float error_distance;					//�ͻ��˷���������ƫ����루��ͨ�ٶ���������������ֵ��

	//�������ݴ�lua�ű�����
	uint32 max_player_level;				//���ȼ�
	uint32 peace_mode_cd;					//��ƽģʽCD(��)
	uint32 dead_protect_CD;					//��������ʱ��(��)
	uint32 nomal_attack_time; 				//Ĭ�Ϲ���ʱ��
	uint32 nomal_move_speed; 				//Ĭ���ƶ��ٶ�	
	uint32 update_ownership_time;			//���¹��������ߵļ��
	uint32 left_fighting_time;				//����ս��ʱ��
	uint32 heathy_auto_recovery_cycle;		//�Զ���Ѫ��ʱ��
	uint32 heathy_auto_recovery_percent; 	//�Զ���Ѫ������
	uint32 energy_auto_recovery_cycle;		//�Զ�����ʱ��
	uint32 energy_auto_recovery_values;		//�Զ�������ֵ
	uint32 endurance_auto_recovery_cycle;	//�Զ��ؾ���ʱ��
	uint32 endurance_auto_recovery_values;	//�Զ��ؾ���ֵ	
	uint32 jump_cd; 						//��cd
	float jump_max_distance;				//�����Ծ����
	int jump_need_energy;					//��Ծ��������
	float notice_distance; 					//��ͼ������֪ͨ����
	float nomal_attack_distance;			//Ĭ�Ϲ�������
	uint32 loot_area;						//ս��Ʒռ������ı߳�
	uint32 loot_exist_timer;				//ս��Ʒ��ͼ����ʱ��
	uint32 loot_change_owner;				//ս��Ʒ�ı������ߵĶ�ʱ��
	uint32 loot_money_entry;				//ս��ƷǮ��gameobjectģ��ID
	uint32 respawn_max_level;				//ԭ�ظ���ȼ�,С�ڸõȼ�����ԭ�ظ���

	uint32 sub_weapon_durability;			//ÿ�ο۳��������;õĻ�����λ
	uint32 sub_other_durability;			//ÿ�ο۳���װ��(���������������;�װ��)�;õĻ�����λ
	uint32 new_bird_protect_lv;				//���ֱ����ȼ�

	float monster_random_radius_percent;	//��������ƶ��뾶
	uint32 gear_exist_time;					//����ֹͣ����ʧʱ��
	uint8  red_name_time;					//���˺���ʱ��
	float safe_distance;					//�����İ�ȫ�뾶
	uint32 use_gameobject_diff;				//ʹ����Ҫ������GO�����ʱ���
	uint32 max_npc_distance;				//������������
	vector<uint16> can_move_dis_map;		//�������겻ͬ���ĵ�ͼ
	string map_data_hdd_path;				//��ͼ����Ӳ�̱���·��
protected:
	virtual bool _Load(config_loader *loader);
}; 


#if COMPILER == COMPILER_GNU
#  define tea_perror(str,...)	out_error(ScenedApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pdebug(str,...)	out_debug(ScenedApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pwarn(str,...)	    out_warn(ScenedApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pinfo(str,...)	    out_str(ScenedApp::g_app->get_logger(),str,##__VA_ARGS__)
#else
#  define tea_perror(str,...)	out_error(ScenedApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pdebug(str,...)	out_debug(ScenedApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pwarn(str,...)	    out_warn(ScenedApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pinfo(str,...)	    out_str(ScenedApp::g_app->get_logger(),str,__VA_ARGS__)
#endif


class ScenedApp:public SvrCoreApp<ScenedApp>
{
	friend class SvrCoreApp<ScenedApp>;
	static const int WORLD_SLEEP_CONST = 1000/8;			//8֡
public:
	ScenedApp(SvrCoreParams& params,SvrCoreConfig& config);
	virtual ~ScenedApp();

	virtual bool Open();
	void Close();

	ScenedConfig& GetConfig()
	{
		return dynamic_cast<ScenedConfig&>(m_config);
	}	

	void Update(uint32 diff);

	ScenedObjectManager	*m_obj_mgr;				//���������
	void AddWatchGlobalValueOk();

protected:
	SvrObjectManager *GetObjMgr()
	{
		return dynamic_cast<SvrObjectManager *>(m_obj_mgr);
	}

private:
	//////////////////////////////////////////////////////////////////////////
	//	
	const static int SERVER_TYPE = SERVER_TYPE_SCENED;

	static int on_centd_open_time(tcp_connection *,server_packet *pkt);			//���ķ�ͬ��������ʱ�䵽������
	static int on_centd_guid_object_table(tcp_connection *,server_packet *pkt);
	static int on_join_map(tcp_connection *,server_packet *pkt);			//��Ҽ����ͼ
	static int on_leave_map(tcp_connection *,server_packet *pkt);			//����뿪��ͼ
	static int on_create_world_map(tcp_connection *,server_packet *pkt);	//������ͼ
	static int on_del_map(tcp_connection *,server_packet *pkt);				//֪ͨ�ͷŵ�ͼ	
	static int on_close_scened(tcp_connection *,server_packet *pkt);			//�ر��Լ�
	static int on_internal_user_item(tcp_connection *,server_packet *pkt);		//ʹ����Ʒ
	static int on_internal_quest_load_result(tcp_connection *,server_packet *pkt);	//������������
		
	static int on_gm_commands(tcp_connection *,server_packet *pkt);		//GM����
	
	static int on_appd_teleport(tcp_connection *,server_packet *pkt);	//Ӧ�÷�������
	static int on_logind_teleport(tcp_connection *,server_packet *pkt);	//��¼��������
	static int on_internal_update_equip_info(tcp_connection *, server_packet *pkt); //Ӧ�÷��������װ����������
	static int on_scened_addexp(tcp_connection *,server_packet *pkt);	//Ӧ�÷�֪ͨ���������Ӿ���
	static int on_scened_consume_money(tcp_connection *conn,server_packet *pkt);	//Ӧ�÷�֪ͨ����������Ԫ����ͭǮ��Щʲô	
	static int on_logind_sync_maxguid(tcp_connection* coon, server_packet* pkt);	//��¼��ͬ��guid����ۼ���ֵ
	static int on_logind_merge_server(tcp_connection* coon, server_packet* pkt);	//��½��֪ͨ�������Ϸ���
	static int on_map_router_pkt(tcp_connection* coon, server_packet* pkt);			//��ͼ����ͼ����
	static int on_logind_to_scened_add_map_watcher(tcp_connection *conn,server_packet *pkt);	//֪ͨ��������ӵ�ͼ�۲���
	static int on_netgd_destory_conn(tcp_connection *conn, server_packet *pkt);			//�ر�����

	static int on_update_spell_info(tcp_connection* coon, server_packet* pkt);		//֪ͨ���������¼�����Ϣ
	static int on_update_change_divine_info(tcp_connection* coon, server_packet* pkt);		//֪ͨ����������װ���ļ�����Ϣ
	static int on_replace_equiped_spell(tcp_connection* coon, server_packet* pkt);			//֪ͨ������װ���ۼ��ܸı�
	static int on_appd_send_scened_do_something(tcp_connection* coon, server_packet* pkt);	//֪ͨ��������Щ����

public:	
	void call_appd_user_item(const char *guid,uint32 template_id,uint8 result,uint32 count);
	void call_user_killed(const string &guid, const string &killer_id, uint32 silver);
	void call_loot_select(const string &guid,uint32 entry,uint32 strong,uint32 count,uint32 fail_time = 0);	//֪ͨ���ʰȡ��Ʒ
	void call_del_map(uint32 instanceid);								//ɾ��ʵ��
	void call_player_addmoney(const string& player_id, const uint8 money_type, const uint8 opt_type, const double val, string &p1, int32 p2, int32 p3, uint8 p4, uint8 p5);//֪ͨӦ�÷�����money
	void call_player_submoney(const string& player_id, const uint8 money_type, const uint8 opt_type, const double val, string &p1, int32 p2, int32 p3, uint8 p4, uint8 p5);//֪ͨӦ�÷���money	
	void call_player_do_something(const string& player_id, uint32 type, uint32 id, string& str);//֪ͨӦ�÷���ʲЩ����
	void call_add_offline_mail(const string& player_id, string& str);//֪ͨӦ�÷����������ʼ�
	void call_recalculate(const string& player_id);	//֪ͨӦ�÷���������
	void call_add_gift_packs(string& player, int id, int gift_type, uint32_t start_time, uint32_t end_time, string gift_name, string gift_desc, string item_config, string item_from);//�����
	void call_player_upgrade(const string& player_id, const uint32 prevLevel, const uint32 level);//֪ͨӦ�÷����������
	//////////////////////////////////////////////////////////////////////////
	//��̨����
	static int on_command_reload_scripts(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_reload_template(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_reset_daily(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_hello_world(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_complete_quest(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_add_quest(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_del_quest_item(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_teleport(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_reset_spell_cd(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);

	static int on_command_ls_session(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);

};

#define g_Config ScenedApp::g_app->GetConfig()
#define Pingbi(str) ScenedApp::g_app->FuckPingbi(str)
#define RegTimer(cb,t,param) ScenedApp::g_app->RegisterTimer((cb),(t),(param));
#define CancleTimer(cb) ScenedApp::g_app->CancleTimer((cb));
#define globalValue (ScenedApp::g_app->m_globalvalue)
#define g_GuidMgr (ScenedApp::g_app->m_guid_mgr)
#define ObjMgr (*ScenedApp::g_app->m_obj_mgr)
#define ServerList (*ScenedApp::g_app->m_server_conn_list)
#define globalNoticeMessage (ScenedApp::g_app->m_notice_message)
//#define globalCounter (ScenedApp::g_app->m_counter)

#endif
