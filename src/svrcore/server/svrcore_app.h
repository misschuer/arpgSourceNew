#ifndef _SVRCORE_APP_H_
#define _SVRCORE_APP_H_

#include <comm/common_stl.h>
#include <comm/configloader.h>
#include <net/netstd.h>
#include <protocol/internal.h>
#include <fastdelegate/FastDelegate.h>
#include <functional>
#include <object/BinLogObject.h>
#include <protocol/WorldPacket.h>
#include <server/svr_context_manager.h>
#include <server/svr_object_manager.h>
#include <object/GlobalValueManager.h>

extern "C" {
	#include <ahocorasick/aho_corasick.h>
}

#define NETGD_HOST	"127.0.0.1"				/*���ط���IP*/
#define NETGD_PORT	10086					/*���ط���˿�*/

#define CENTD_HOST	"127.0.0.1"				/*���ķ�IP*/
#define CENTD_PORT	10087					/*���ķ��˿�*/

const int DAY_SECONDS = 60*60*24;			//ÿ�������
const int TIME_ZONE = 8;					//ʱ��
const int CVT_DIFF_UTC = 60*60*TIME_ZONE;	//+8ʱ����UTCʱ���������

#define WANNENG_LOGIN_KEY "dc829703a6039ff5262ec2d0d520444a"		//���ܵ�¼��Կ

//////////////////////////////////////////////////////////////////////////
//�����в���
struct TEA_SVRCORE_SPEC SvrCoreParams
{

	typedef void (*usage_ptr)(const char *s);	

	bool Load(int argc,const char **argv,usage_ptr __usage);
public:
	SvrCoreParams():generic_id(0),run_test(0),centd_port(0),web_port(""),context_file_name(""){}

	string config_file;	
	int generic_id;
	int run_test;
	uint16 centd_port;
	string web_port;
	string context_file_name;
};

//////////////////////////////////////////////////////////////////////////
//������Ϣ
struct TEA_SVRCORE_SPEC SvrCoreConfig
{
	virtual ~SvrCoreConfig(){}
	
	uint16 netgd_port;		//���ط��˿�
	string netgd_host;		//���ط�����IP

	uint16 centd_port;		//���ķ��˿�
	string centd_host;		//���ķ�IP	

	string log_folder;		//��־·��
	string log_name;		//��־ģ������

	string backup_hdd_path;					//����·��
	string player_data_hdd_path;			//������ݱ���·��
	string player_data_hdd_path_recycle;	//���ݻ���վ

	int	   log_level;		//��־�ȼ�

	string storage_path;	//���ݴ洢·��
	bool	load_pingbi;	//�������δ�

	//���������ļ�
	bool Load(string file, uint32 centd_port_para);
	bool ReLoad();
protected:
	string m_config_file_path;
protected:
	virtual bool _Load(config_loader *loader);
};

//��Ϸ����
struct TEA_SVRCORE_SPEC GameConfig:public SvrCoreConfig
{
	virtual ~GameConfig(){}
	
	string script_folder;	//�ű��ļ���
	string map_folder;		//��ͼ�ļ���
	
	bool load_creature_path;//��������ɵ�
	string test_server_live_uid;//����UID
protected:
	virtual bool _Load(config_loader *loader);
};

//�����ݿ�����
struct TEA_SVRCORE_SPEC DbSvrCoreConfig:public GameConfig
{
	virtual ~DbSvrCoreConfig (){}

	string db_chars_log;		//��ɫ���ݿ���־��¼
	string db_character;		//��ɫ�������ַ���	
	string logdb_log;			//��ɫ���ݿ���־��¼
	string logdb_character;		//��ɫ�������ַ���
protected:
	virtual bool _Load(config_loader *loader);
};

//////////////////////////////////////////////////////////////////////////
//Ӧ�ó������
struct TimerHolder;
typedef fastdelegate::FastDelegate1<TimerHolder&,void> Timer_Callback;
struct TimerHolder
{
	Timer_Callback cb;	//�����ص�
	char sTimer[10];	//ÿ�촥����ʱ���,24Сʱ��,��ȷ������,���Ϊ����ֻ����һ��
	uint32 _next_time;	//����ʱ��Ҫ,��һ�δ���ʱ��,��ʼ��Ϊ0,���С��������ᱻ�Ƴ������ֹ��޸Ļ�����ֵ������Ҫע��ʱ������
	void *param;		//�ص���������	
	int deleted;
};

template<typename PARAM>
struct InternalCallback;

//������״̬
enum EAppStatus
{
	APP_STATUS_INIT						= 0,		//��ʼ��
	APP_STATUS_CONN_CENTD				= 1,		//�������ķ��ɹ�
	APP_STATUS_WAIT_LOGIND_READY_OK		= 2,		//�ȴ���¼���������
	APP_STATUS_LOGIND_READY_OK			= 3,		//��¼���������
	APP_STATUS_GET_ONLINE_DATA			= 4,		//��ȡ�������������ĵ���������

	APP_STATUS_READY_OK					= 5,		//����׼�����

	APP_STATUS_CLOSE					= 10,		//׼���ر�
};

//���ս�����ȡ����key
#define KFZ_RESULT_KEY	"suibianla..123456"

class SvrCoreAppImpl:public ContextManager, public GlobalValueManager
{
protected:
	//typedef WORLD_SLEEP_CONST 50 ;		//20֡
	typedef std::vector<TimerHolder> TimerHolderArr;	
	typedef std::function<int (tcp_connection *,server_packet *pkt,uint32 guid,uint32 connectionid,Tokens &tokens)> func_command_handler;
	typedef std::map<string,func_command_handler> Command_Handler_Map;
	typedef core_obj::EventDispatcher<bool> EventMgr;

	static void* WorldTick(void *arg);
public:
	
	typedef int (*netgd_handle_ptr)(tcp_connection *,server_packet *pkt);				
	SvrCoreAppImpl(SvrCoreParams& params,SvrCoreConfig& config);
	virtual ~SvrCoreAppImpl();

	virtual void Update(uint32 diff);
	void Wait(){WorldTick(this);};

	void SendToNetgd(server_packet *pkt);
	void SendToCentd(server_packet *pkt);

	bool SendToServerByFd(WorldPacket &pkt, uint32 fd);
	inline bool SendToScened(WorldPacket &pkt, uint32 fd){return SendToServerByFd(pkt, fd);}
	bool SendToAppd(WorldPacket &pkt);
	bool SendToPoliced(WorldPacket &pkt);
	bool SendToLogind(WorldPacket &pkt);

	inline log_holder *get_logger()
	{
		ASSERT(m_logger);
		return m_logger;
	}	

	inline tcp_connection *get_connection()
	{
		return m_netgd_connection;
	}

	void TryClose()
	{
		if(m_logger)
			out_str(m_logger,"try stop SvrCoreApp");
		SetStatus(APP_STATUS_CLOSE);
	}

	//ע�ᶨʱ���ص�
	void RegisterTimer(Timer_Callback cb,const char* t,void *param=NULL);		//���ظ�����
	void RegisterTimer(Timer_Callback cb,uint32 t,void *param=NULL)	;			//����ֻ����һ��
	void CancleTimer(Timer_Callback cb);	

	//////////////////////////////////////////////////////////////////////////
	//������ĳ���ӣ������̫����ְ�����
	typedef struct splice_pkt_t
	{
		uint32 id;
		uint32 max_size;
		time_t t;
		packet *pkt;
	}splice_pkt;
	vector<splice_pkt*> m_splice_pkt_map;
	void SendSplicePkt(tcp_connection *conn,packet *pkt);

	//////////////////////////////////////////////////////////////////////////
	//�������δ�
	bool LoadFuckPingbi(string path);
	bool FuckPingbi(char* str);

	//ע��Э����䵽��������
	void RegSessionOpts(uint32 fd);
	void RegSessionOpts(uint32 fd,uint16 optcode,uint32 session_fd = 0);
	void RegSessionOpts();

	uint32 Get_Connection_ID(){return m_connection_id;}
	EAppStatus GetStatus(){	return m_status;}

	//�����ص�
	EventMgr::EventID AddCallback(std::function<void(bool)> func);
	//�����ص�
	void DispatchCallback(EventMgr::EventID id, bool result);
	//��������ս�����
	string Md5WorldWarResult(string guid, uint32 type1, uint32 type2, uint32 result, uint32 data1, uint32 data2, uint32 data3, uint32 data4, time_t t);
public:
	uint32 m_open_time;						//����������ʱ��
	uint32 m_tick_timers;					//��������
	InternalCallback<packet&> *m_inter_cb;

	vector<uint16> m_opts;					//��Ϸ����Ҫ��Э���
	vector<uint16> m_pk_opts;					//pk����Ҫ��Э���
protected:
	uint32 WORLD_SLEEP_CONST_;
	//Ӧ�ó��������в���
	SvrCoreParams& m_params;
	//Ӧ�ó���������Ϣ
	SvrCoreConfig& m_config;
	//������״̬
	EAppStatus m_status;

	//��־
	log_holder *m_logger;	
	//���ط�����
	tcp_connection *m_netgd_connection;
	//���ķ�����
	tcp_connection *m_centd_connection;

	//��ǰ������������ID
	int m_connection_id;

	//׼���������ط�������
	//list_t m_to_send_list;
	//�յ��Ŀͻ������ݰ�����
	list_t m_recv_pkt_list;
	netgd_handle_ptr m_netgd_request_map[MAX_INTERNAL_OPT * 2];

	Command_Handler_Map m_command_hanlders;

	inline reactor *get_reactor()
	{
		ASSERT(m_rea);
		return m_rea;
	}

	void SetStatus(EAppStatus status)
	{
		out_str(m_logger, "set server status, from %u to %u", m_status, status);
		m_status = status;
	}

	void UpdateTimer(uint32 diff);
	reactor *m_rea;		

	static void sig_handler(int sig);
	uint32 m_gid;
	uint32 m_sid;
	uint32 m_oldsid;

	AC_AUTOMATA *m_aca;					//���δ����
	char *m_fuck_pingbi;				//�������δ�
	TimerHolderArr m_timerHolder;		//���Ӷ�ʱ���ش�����
	TimerHolderArr m_timerHolder_toadd;	//������Ķ�ʱ��
	TimeTracker m_callback_timer;		//ÿ���Ӵ���һ��
	int m_signal_no ;		

	uint32 m_pingpont;					//�´η�ping����ʱ��

	EventMgr m_event_mgr;				//�ص�������
};

template<class T>
class SvrCoreApp:public SvrCoreAppImpl
{
public:
	typedef SvrCoreApp<T> base;
	SvrCoreApp(SvrCoreParams& params,SvrCoreConfig& config);

	virtual bool Open();

	//////////////////////////////////////////////////////////////////////////
	//�ź�	
	static void HookSignals();
	static void UnHookSinals();
	static void OnSignal(int s);	

	static T *g_app;

	static void SendToCentd(WorldPacket& pkt)
	{
		((SvrCoreAppImpl*)(g_app))->SendToCentd(pkt.GetPktPtr());
	}
protected:
	virtual SvrObjectManager *GetObjMgr() = 0;
protected:
	static int netgd_handle_accept(struct _io_watcher_t *ev,EV_FLAGS flag);
	static int netgd_handle_close(io_watcher* ev,EV_FLAGS flag);				//�����ط��رյ�ʱ��
	static int centd_handle_close(io_watcher* ev,EV_FLAGS flag);				//�����ķ��رյ�ʱ��
	static int netgd_handle_request(tcp_connection *,server_packet *pkt);	

	//////////////////////////////////////////////////////////////////////////
	//���ط�Э�鴦����	
	static int on_netgd_lua(tcp_connection *,server_packet *);
	static int on_netgd_packet_gate(tcp_connection *,server_packet *pkt);
	static int on_netgd_packet_gate_list(tcp_connection *,server_packet *pkt);	
	static int on_netgd_reg_server(tcp_connection *, server_packet *pkt);
	static int on_netgd_ping_pong(tcp_connection *, server_packet *pkt);
	static int on_commands(tcp_connection *, server_packet *pkt);
	static int on_splice(tcp_connection *, server_packet *pkt);
	static int on_call_back_result(tcp_connection *, server_packet *pkt);

	static int on_print_object(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
	static int on_command_memory_recovery(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens);
};

void SendCommandResult(tcp_connection *conn, uint32 connectid, const char *result,...);

#include <server/svrcore_app.h.inl>


#endif
