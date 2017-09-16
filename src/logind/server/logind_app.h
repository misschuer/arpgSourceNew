#ifndef _LOGIND_H_
#define _LOGIND_H_

#include <shared/storage_strus.h>
#include <protocol/external.h>
#include <server/svrcore_app.h>
#include <protocol/WorldPacket.h>
#include "logind_object_manager.h"

class DatabaseWorkerPool;
class MapManager;
class LogindContext;
class LogindObjectManager;
class LogindMongoDB;
class LogindCache;
class LogindContextLoginMgr;
class HttpHandler;
class LogindGMTable;

using core_obj::SyncEventRecorder;

//�ʺŽṹ��
typedef struct account_table_t
{
	char sid[16];
	char uid[40];
	char pid[40];
	char name[60];
	char ip[30];
	int is_FCM;
	int gmlevel;
	char platdata[200];
public:
	string ToString();
	void FromString(const string &str);
	void NewFromString(const string &str);
}account_table;

//////////////////////////////////////////////////////////////////////////
class LogindConfig:public DbSvrCoreConfig
{
public:
	string platform_id;		//ƽ̨id
	string login_key;						//��ƽ̨ͨѶ ��Կ
	string server_id;						//������ID
	string server_name;						//ƽ̨id_������id
	uint32 max_player_count;				//���������������
	uint32 login_queue_interval;			//��ѯ�ȴ�����Ƿ���Խ�����Ϸ��ʱ����
	uint32 versions_requirements_internal;	//���汾����
	uint32 reload_game_config_interval;		//���¶�ȡ��Ϸ���ü��
	bool check_session_key_time;			//У��session keyʱ��
	bool gm_open;							//gm����
	uint32 server_type;						//����������
	uint32 max_secend_count;				//�������������
	uint32 scened_collapse_time_out;		//��ͼ�������Գ���������������ʱ��
	string test_server_live_uid;			//���Է����������̶ȵ�����UID
	uint32 auto_save_time;					//�Զ���������ʱ����
	uint32 auto_backup_hdd_time;			//��������ʱ����
	uint32 Save_Player_To_DB_Count;			//ÿ����ѯ���浽���ݿ�ĸ���
	vector<string> g_cant_make_name;		//ȡ��������
	string ext_web_interface;				//�ⲿweb�ӿ�����
	string conf_svr;						//���÷�web��ַ����
	string world_server_url;				//�����url����


protected:
	virtual bool _Load(config_loader *loader);
};

typedef struct merge_info_t{
	char server_name[50];			//ԭʼ��������
	char merge_server_host[50];	//�Ϸ�����
	uint32 merge_server_port;		//�Ϸ��˿�
	char merge_server_name[50];		//�Ϸ���������
}merge_info;

//��¼��Ӧ��
class LogindApp:public SvrCoreApp<LogindApp>
{
	static const int WORLD_SLEEP_CONST = 1000/60;			//60֡
	friend class SvrCoreApp<LogindApp>;
public:
	LogindApp(SvrCoreParams& params,LogindConfig& config);
	virtual ~LogindApp();
public:
	inline LogindConfig& GetConfig()
	{
		return  dynamic_cast<LogindConfig&>(m_config);
	}
	virtual bool Open();	
	void Close();
	
	virtual void Update(uint32 diff);

	LogindMongoDB *m_db_access_mgr;	//���ݹ�����
	LogindCache *m_cache;			//����
	LogindObjectManager	*m_obj_mgr;	//���������
	LogindContextLoginMgr *m_login_queue;	//��¼����
	HttpHandler *m_http;
	LogindGMTable *m_gm_table;		//GM��̨������

	map<string, int>			m_removing_player;		//�Ƴ������е���ң���Щ����ڼ佫�޷���¼
	//��������
	void loadRightFloatCallback(int id, int status, int zone1, int zone2, int zone3, int mode, uint32 ftime, uint32 ttime,uint32 adddate,
		string subject, string content, string link);

	//����session_key
	string MakeSessionKey(string account, bool indulge, string otherdata="", string login_key="", bool is_hosting = false);
protected:
	SvrObjectManager *GetObjMgr();
	void LoginQueuePlayer(TimerHolder& th);				//��¼����
	void check_versions_requirements(TimerHolder& th);	//���汾����
	void check_merge_server_begin(TimerHolder& th);		//�ӷ��Ϸ����
	void ReloadGameConfigTable(TimerHolder& th);		//����������Ϸ���ñ�
	void SaveGlobalValue(TimerHolder& th);				//�������������ʱ��
	void BackupPlayerInfo(TimerHolder& th);				//����������ݶ�ʱ��
	void SaveChangePlayerToDB(TimerHolder& th);			//�����б仯����ҵ����ݿ�
	void SavePlayerToDB(TimerHolder& th);				//������ҵ����ݿ�
	void FreeLogoutPlayer(TimerHolder &th);				//�ͷŻ���ĵǳ����
	void SendWebConn(TimerHolder& th);					//ս������ʱ֪ͨweb��������״̬

	void data_save_player_to_merge();				//���ݱ����֪ͨ

	void SaveAllData();							//���̱�����������
private:
	const static int SERVER_TYPE = SERVER_TYPE_LOGIND;
private:
	void CollapseReset(server_packet *pkt);
	void OnDataReady();

	void CallCentdCreateIndex();							//Ϊ���ķ�������
	void GoToPkServer(const string &player_guid);			//�����ս����
	void CheckObject();										//���һЩ�����Ƿ���ڣ��������򴴽�
private:
	//////////////////////////////////////////////////////////////////////////
	//Э��
	static int on_netgd_create_conn(tcp_connection *,server_packet *pkt);
	static int on_netgd_destory_conn(tcp_connection *,server_packet *pkt);
	static int on_centd_open_time(tcp_connection *,server_packet *pkt);			//���ķ�ͬ��������ʱ�䵽������

	static int on_create_conn_get_session(tcp_connection *,server_packet *pkt);	//�ͻ�����������
	static int on_scened_del_map(tcp_connection *, server_packet *pkt);					//������Ҫ���ͷŵ�ͼʵ��
	static int on_get_online_player(tcp_connection *, server_packet *pkt);						//�������ķ��ɹ�
	static int on_gm_commands(tcp_connection *, server_packet *pkt);		//GM����
	static int on_centd_guid_object_table(tcp_connection *,server_packet *pkt);	
	static int on_offline_oper(tcp_connection *, server_packet *pkt);
	static int on_offline_oper_result(tcp_connection *, server_packet *pkt);
	static int on_save_all_data(tcp_connection *, server_packet *pkt);
	static int on_map_router_pkt(tcp_connection* coon, server_packet* pkt);	//��ͼ����ͼ����
	static int on_logind_hosting(tcp_connection* coon, server_packet* pkt);	//�йܵ�¼

	static int on_kuafu_enter(tcp_connection* coon, server_packet* pkt);	//���������Ϣ
	static int on_rename_check(tcp_connection* coon, server_packet* pkt);	//�������

	static int on_update_charname(tcp_connection* coon, server_packet* pkt);

	static int on_kuafu_back_to_game(tcp_connection* coon, server_packet* pkt);	//�����ÿ������Ϸ��

	static int on_faction_invite_result(tcp_connection* coon, server_packet* pkt);	//����������
	//////////////////////////////////////////////////////////////////////////
	//GM����
	static int on_command_reload_scripts(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_reload_template(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_dohuidang(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);		//ִ�лص�
	static int on_command_iscanhuidang(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);	//�ص����
	static int on_command_savetodb(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);	//���浽���ݿ�
public:
	void call_sync_guids_max(uint32 player_max);		//ͬ��guid�����������guid�ۼ�����������	
};

#define g_Config LogindApp::g_app->GetConfig()
#define globalValue (LogindApp::g_app->m_globalvalue)
#define Pingbi(str) LogindApp::g_app->FuckPingbi(str)
#define RegTimer(cb,t,param) LogindApp::g_app->RegisterTimer((cb),(t),(param));
#define CancleTimer(cb) LogindApp::g_app->CancleTimer((cb));
#define g_GuidMgr (LogindApp::g_app->m_guid_mgr)
#define g_DAL (*LogindApp::g_app->m_db_access_mgr)
#define g_Cache (*LogindApp::g_app->m_cache)
#define ObjMgr (*LogindApp::g_app->m_obj_mgr)
#define ServerList (*LogindApp::g_app->m_server_conn_list)
#define	MapMgr dynamic_cast<MapManager*>(LogindApp::g_app->m_map_Instance_list)
#define GmTable (*LogindApp::g_app->m_gm_table)

#if COMPILER == COMPILER_GNU
#  define tea_perror(str,...)	out_error(LogindApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pdebug(str,...)	out_debug(LogindApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pwarn(str,...)	out_warn(LogindApp::g_app->get_logger(),str,##__VA_ARGS__)
#  define tea_pinfo(str,...)	out_str(LogindApp::g_app->get_logger(),str,##__VA_ARGS__)
#else
#  define tea_perror(str,...)	out_error(LogindApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pdebug(str,...)	out_debug(LogindApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pwarn(str,...)	out_warn(LogindApp::g_app->get_logger(),str,__VA_ARGS__)
#  define tea_pinfo(str,...)	out_str(LogindApp::g_app->get_logger(),str,__VA_ARGS__)
#endif

#endif


