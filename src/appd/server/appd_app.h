/************************************************************************
 * file	: appd_app.h
 * desc	: Ӧ�÷�
 *		��ʽ������Ӧ�ã���Ȼ��������ݿ����
 *
 *
 * author:	linbc
 * date:	20110518
 * version:
 ************************************************************************/
#ifndef _APPD_APP_H_
#define _APPD_APP_H_

#include <svrcore.h>
#include <comm/timer.h>
#include <protocol/external.h>
#include "appd_object_manager.h"
#include "AppdLoginManager.h"

class RankListManager;
class GroupManager;
class AppdMongoDB;
class AppdLogsDB;


#if COMPILER == COMPILER_GNU
#  define tea_perror(str,...)	out_error(AppdApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pdebug(str,...)	out_debug(AppdApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pwarn(str,...)	    out_warn(AppdApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pinfo(str,...)	    out_str(AppdApp::g_app->get_logger(),str,##__VA_ARGS__)
#else
#  define tea_perror(str,...)	out_error(AppdApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pdebug(str,...)	out_debug(AppdApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pwarn(str,...)	    out_warn(AppdApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pinfo(str,...)	    out_str(AppdApp::g_app->get_logger(),str,__VA_ARGS__)
#endif

//ϵͳ����ṹ��
typedef struct system_notice_t{
	uint32 notice_id;
	uint32 start;
	uint32 end;
	uint32 interval;
	char content[500];
}system_notice;

//////////////////////////////////////////////////////////////////////////
class AppConfig:public DbSvrCoreConfig
{
public:
	//������ұ�����С
	uint16 bag_init_size_main;				//��������ʼ����С
	uint16 bag_init_size_equip;				//װ��������ʼ����С
	uint16 bag_init_size_storage;			//�ֿ��ʼ����С
	uint16 bag_init_size_repurchase;		//�ع�������ʼ����С
	uint16 bag_init_size_system;			//ϵͳ������ʼ����С
	uint16 bag_init_size_stall;				//̯λ������ʼ����С

	uint16 bag_max_size_main;				//�������������
	uint16 bag_max_size_storage;			//�ֿ��������
	uint16 bag_extension_count;				//����һ����չ�ĸ�����
	uint16 bag_extension_material;			//������չ�����Ĳ���ģ��

	uint8   player_max_level;				//������ȼ�
	
	uint32 update_detection_player_info;	//Ӧ�÷���ѯʱ����
	uint32 player_chat_world_level;			//�������Ƶ����͵ȼ�����
	uint32 player_chat_whisper_level;		//˽����͵ȼ���ʱ
	uint32 laba_use_vip_level;				//����ʹ����ҪVIP�ȼ�
	uint32 laba_use_need_money;				//����ʹ����ҪԪ����
	uint32 rank_list_work_interval;			//���а������
	uint32 update_online_playerinfo_interval;	//�������������Ϣ���
	uint32 update_firend_info_interval;		//������Һ������ϼ��

	string recharge_folder;						//��ֵ���ݱ����ļ���
	string mail_folder;							//�����ʼ������ļ���
protected:
	virtual bool _Load(config_loader *loader);
};

class AppdContext;

class AppdApp:public SvrCoreApp<AppdApp>
{
	static const int WORLD_SLEEP_CONST = 1000/30;			//30֡
	friend class SvrCoreApp<AppdApp>;	
public:
	// ������ƥ���ɫ��Ϣά���б�
	typedef std::map<string, std::vector<uint32>> CultivationMap;
	static CultivationMap m_cultivationMap;

	static string XIULIAN_FILE_NAME;
	static void loadXiulian();
	static void saveXiulian();

public:

	AppdApp(SvrCoreParams& params,SvrCoreConfig& config);
	virtual ~AppdApp();

	virtual bool Open();

	inline AppConfig& GetConfig()
	{
		return static_cast<AppConfig&>(m_config);
	}

	void Close();
	void Update(uint32 diff);
	
	AppdMongoDB *m_db_access_mgr;	//���ݹ�����
	//���а�
	RankListManager *m_rank_list_mgr;
	//�������
	GroupManager *m_group_mgr;
	//���������õ�Binlog
	BinLogObject *m_equip_attrs;
	//���������
	AppdObjectManager *m_obj_mgr;
	//��¼������
	AppdLoginMgr *m_login_mgr;

	string GetRankPlayerGuidByType(int type, uint32 rank);				//��ȡ���а����guid

	void UpdateOnLInePlayerInfo(TimerHolder& th);						//�������������Ϣ
	void ResetDailyCounter(TimerHolder& th);							//ÿ��ˢ��ͳ������
	void login_account_guid(AppdContext *player);						//��¼��ӳ�����ʺ�ID�ͽ�ɫID
	string getGuidFromAccount(string account);							//����account��ȡguid
	static void send_result_back_to_world(uint16 protocolid, uint32 eventid, BinLogObject &binlog, string binlog_guid, uint8 opt_result=0, uint32 reserve=0); //���Ͳ�������������	
private:
	map<uint32,system_notice*> m_sys_notice;
protected:
	SvrObjectManager *GetObjMgr();
	void AddWatchGlobalValueOk();
	void MergeGlobalvalue(const string &str);
private:
	//////////////////////////////////////////////////////////////////////////
	//
	std::map<string,string>		m_account_guid;			//�ʺ�ID�ͽ�ɫIDӳ���;
	const static int SERVER_TYPE = SERVER_TYPE_APPD;
	static int on_player_login(tcp_connection *,server_packet *pkt);
	static int on_player_logout(tcp_connection *,server_packet *pkt);
	static int on_get_online_player(tcp_connection *,server_packet *pkt);
	static int on_centd_open_time(tcp_connection *,server_packet *pkt);			//���ķ�ͬ��������ʱ�䵽������

	static int on_centd_guid_object_table(tcp_connection *,server_packet *pkt);
	static int on_offline_opert(tcp_connection *,server_packet *pkt);

	static int on_scened_recalculation_attr(tcp_connection *, server_packet *pkt);	//��������

	static int on_del_char(tcp_connection *,server_packet *pkt);
	static int on_scened_player_addmoney(tcp_connection* coon, server_packet* pkt);	//������֪ͨӦ�÷�����money
	static int on_scened_player_submoney(tcp_connection* coon, server_packet* pkt);	//������֪ͨӦ�÷���money
	static int on_logind_sync_maxguid(tcp_connection* coon, server_packet* pkt);	//��¼��ͬ��guid����ۼ���ֵ
	static int on_logind_merge_server(tcp_connection* coon, server_packet* pkt);	//��½��֪ͨӦ�÷��Ϸ���
	static int on_modify_showhand_dairu_coin(tcp_connection* conn, server_packet* pkt);//��¼��֪ͨӦ�÷��޸Ĵ���ͭǮ
	static int on_scened_send_char_info(tcp_connection *, server_packet *pkt);			//����������������Ϣ
	static int on_logind_send_to_appd_get360gift(tcp_connection *, server_packet *pkt);	//���͸�Ӧ�÷���ȡ360��Ȩ
	//////////////////////////////////////////////////////////////////////////
	//��̨����
	static int on_command_reload_scripts(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_reload_template(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_add_item(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_top_start(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
};

#define g_Config AppdApp::g_app->GetConfig()
#define Pingbi(str) AppdApp::g_app->FuckPingbi(str)
#define RegTimer(cb,t,param) AppdApp::g_app->RegisterTimer((cb),(t),(param));
#define CancleTimer(cb) AppdApp::g_app->CancleTimer((cb));

#define g_DAL (*AppdApp::g_app->m_db_access_mgr)
#define globalValue (AppdApp::g_app->m_globalvalue)
#define g_GuidMgr (AppdApp::g_app->m_guid_mgr)
#define ObjMgr (*AppdApp::g_app->m_obj_mgr)
#define ServerList (*AppdApp::g_app->m_server_conn_list)
#define globalNoticeMessage (AppdApp::g_app->m_notice_message)
#define RankListMgr (AppdApp::g_app->m_rank_list_mgr)
#define GroupMgr (AppdApp::g_app->m_group_mgr)

#endif
