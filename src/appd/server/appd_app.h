/************************************************************************
 * file	: appd_app.h
 * desc	: 应用服
 *		各式各样的应用，当然，最近数据库操作
 *
 *
 * author:	linbc
 * date:	20110518
 * version:
 ************************************************************************/
#ifndef _APPD_APP_H_
#define _APPD_APP_H_

#include <svrcore.h>
#include "appd_script.h"
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

//系统公告结构体
typedef struct system_notice_t{
	uint32 notice_id;
	uint32 start;
	uint32 end;
	uint32 interval;
	char content[500];
}system_notice;

// pvp匹配信息
typedef struct pvp_match_info_t {
	char guid[50];
	uint8 times;
	uint32 match_time;
} PvpMatchInfo;

typedef vector<PvpMatchInfo> PvpMatchInfoVec;

//////////////////////////////////////////////////////////////////////////
class AppConfig:public DbSvrCoreConfig
{
public:
	//设置玩家背包大小
	uint16 bag_init_size_main;				//主包裹初始化大小
	uint16 bag_init_size_equip;				//装备包裹初始化大小
	uint16 bag_init_size_storage;			//仓库初始化大小
	uint16 bag_init_size_repurchase;		//回购包裹初始化大小
	uint16 bag_init_size_system;			//系统包裹初始化大小
	uint16 bag_init_size_stall;				//摊位包裹初始化大小

	uint16 bag_max_size_main;				//主包裹最大容量
	uint16 bag_max_size_storage;			//仓库最大容量
	uint16 bag_extension_count;				//包裹一次扩展的格子数
	uint16 bag_extension_material;			//包裹扩展的消耗材料模版

	uint8   player_max_level;				//玩家最大等级
	
	uint32 update_detection_player_info;	//应用服轮询时间间隔
	uint32 player_chat_world_level;			//玩家世界频道最低等级发言
	uint32 player_chat_whisper_level;		//私聊最低等级限时
	uint32 laba_use_vip_level;				//喇叭使用需要VIP等级
	uint32 laba_use_need_money;				//喇叭使用需要元宝数
	uint32 rank_list_work_interval;			//排行榜工作间隔
	uint32 update_online_playerinfo_interval;	//更新在线玩家信息间隔
	uint32 update_firend_info_interval;		//更新玩家好友资料间隔

	string recharge_folder;						//充值数据保存文件夹
	string mail_folder;							//离线邮件保存文件夹
protected:
	virtual bool _Load(config_loader *loader);
};

class AppdContext;

class AppdApp:public SvrCoreApp<AppdApp>
{
	static const int WORLD_SLEEP_CONST = 1000/30;			//30帧
	friend class SvrCoreApp<AppdApp>;	
public:
	// 修炼场匹配角色信息维护列表
	typedef std::map<string, std::vector<uint32>> CultivationMap;
	static CultivationMap m_cultivationMap;

	static string XIULIAN_FILE_NAME;
	static void loadXiulian();
	static void saveXiulian();

	// 世界BOSS报名
	static std::set<string> enrollSet;
	static void onWorldBossEnroll(string& playerGuid) {
		enrollSet.insert(playerGuid);
	}

	static void resetEnroll() {
		enrollSet.clear();
	}

	// PVP匹配信息
	static vector<PvpMatchInfoVec> pvpMatchInfos;
	static uint32 matchLast;
	// 未初始化的进行初始化
	static void initPvpMatchInfo(uint32 size, uint32 match_Last) {
		if (pvpMatchInfos.size() != size) {
			for (uint32 i = pvpMatchInfos.size(); i < size; ++ i) {
				PvpMatchInfoVec pvpMatchInfoVec;
				pvpMatchInfos.push_back(pvpMatchInfoVec);
			}
			matchLast = match_Last;
		}
	}

	static void addMatchQueue(uint8 indx, string& guid) {
		PvpMatchInfo pvpMatchInfo;
		memset(&pvpMatchInfo, 0, sizeof(PvpMatchInfo));
		pvpMatchInfo.match_time = (uint32)time(NULL);
		pvpMatchInfo.times = 0;
		strcpy(pvpMatchInfo.guid, guid.c_str());
		pvpMatchInfos[indx].push_back(pvpMatchInfo);
	}

	static void onCancelMatch(uint8 indx, string& guid) {
		for (auto it = pvpMatchInfos[indx].begin(); it != pvpMatchInfos[indx].end(); ++ it) {
			if (it->guid == guid) {
				pvpMatchInfos[indx].erase(it);
				break;
			}
		}
	}

	static void OnProcessLocalSinglePVPMatch() {
		uint32 now = (uint32)time(NULL);

		//先把能匹配的匹配下来
		for (int i = pvpMatchInfos.size()-1; i >= 0; -- i) {
			int size = pvpMatchInfos[ i ].size();
			PvpMatchInfo last;
			memset(&last, 0, sizeof(PvpMatchInfo));
			if ((size & 1) == 1) {
				last = pvpMatchInfos[ i ][size-1];
				size --;
			}

			for (int j = 0; j < size; j += 2) {
				PvpMatchInfo fa = pvpMatchInfos[ i ][ j ];
				PvpMatchInfo fb = pvpMatchInfos[ i ][j+1];
				char key[50];
				sprintf(key, "%s#%s", fa.guid, fb.guid);
				OnLocalSinglePVPMatched(fa.guid, key, now);
				OnLocalSinglePVPMatched(fb.guid, key, now);
			}
			pvpMatchInfos[ i ].clear();
			// 把最后一个存进队列
			if (!((string)last.guid).empty()) {
				pvpMatchInfos[ i ].push_back(last);
			}
		}

		// 现在每个阶段的队列最多只有1个人
		for (int i = pvpMatchInfos.size()-1; i >= 0; -- i) {
			if (pvpMatchInfos[ i ].size() > 0) {
				// 第一次匹配超过时间了
				if (pvpMatchInfos[ i ][ 0 ].times == 0 && now >= pvpMatchInfos[ i ][ 0 ].match_time) {
					pvpMatchInfos[ i ][ 0 ].times = 1;
					pvpMatchInfos[ i ][ 0 ].match_time = now + matchLast;
				}

				if (pvpMatchInfos[ i ][ 0 ].times == 1) {
					if (now >= pvpMatchInfos[ i ][ 0 ].match_time) {
						// 和机器人比赛
						char key[50];
						sprintf(key, "%s#robot|%d", pvpMatchInfos[ i ][ 0 ].guid, i);
						OnLocalSinglePVPMatched(pvpMatchInfos[ i ][ 0 ].guid, key, now);
						pvpMatchInfos[ i ].clear();
					} else {
						// 匹配比他段位低的
						for (int j = i - 1; j >= 0; -- j) {
							if (pvpMatchInfos[ j ].size() > 0) {
								PvpMatchInfo fa = pvpMatchInfos[ i ][ 0 ];
								PvpMatchInfo fb = pvpMatchInfos[ j ][ 0 ];
								char key[50];
								sprintf(key, "%s#%s", fa.guid, fb.guid);
								OnLocalSinglePVPMatched(fa.guid, key, now);
								OnLocalSinglePVPMatched(fb.guid, key, now);
								pvpMatchInfos[ i ].clear();
								pvpMatchInfos[ j ].clear();
								// 匹配到就跳出来
								break;
							}
						}
					}
				}
			}
		}
	}

	static void OnLocalSinglePVPMatched(const char guid[50], const char key[50], const uint32 time) {
		OnSinglePVPMatched(guid, key, time);
	}

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
	
	AppdMongoDB *m_db_access_mgr;	//数据管理器
	//排行榜
	RankListManager *m_rank_list_mgr;
	//队伍管理
	GroupManager *m_group_mgr;
	//属性重算用的Binlog
	BinLogObject *m_equip_attrs;
	//对象管理器
	AppdObjectManager *m_obj_mgr;
	//登录管理器
	AppdLoginMgr *m_login_mgr;

	string GetRankPlayerGuidByType(int type, uint32 rank);				//获取排行榜玩家guid

	void UpdateOnLInePlayerInfo(TimerHolder& th);						//更新在线玩家信息
	void ResetDailyCounter(TimerHolder& th);							//每日刷新统计数据
	void login_account_guid(AppdContext *player);						//登录后映射下帐号ID和角色ID
	string getGuidFromAccount(string account);							//根据account获取guid
	static void send_result_back_to_world(uint16 protocolid, uint32 eventid, BinLogObject &binlog, string binlog_guid, uint8 opt_result=0, uint32 reserve=0); //发送操作结果回世界服	
private:
	map<uint32,system_notice*> m_sys_notice;
protected:
	SvrObjectManager *GetObjMgr();
	void AddWatchGlobalValueOk();
	void MergeGlobalvalue(const string &str);
private:
	//////////////////////////////////////////////////////////////////////////
	//
	std::map<string,string>		m_account_guid;			//帐号ID和角色ID映射表;
	const static int SERVER_TYPE = SERVER_TYPE_APPD;
	static int on_player_login(tcp_connection *,server_packet *pkt);
	static int on_player_logout(tcp_connection *,server_packet *pkt);
	static int on_get_online_player(tcp_connection *,server_packet *pkt);
	static int on_centd_open_time(tcp_connection *,server_packet *pkt);			//中心服同步服务器时间到场景服

	static int on_centd_guid_object_table(tcp_connection *,server_packet *pkt);
	static int on_offline_opert(tcp_connection *,server_packet *pkt);

	static int on_scened_recalculation_attr(tcp_connection *, server_packet *pkt);	//重算属性

	static int on_del_char(tcp_connection *,server_packet *pkt);
	static int on_scened_player_addmoney(tcp_connection* coon, server_packet* pkt);	//场景服通知应用服增加money
	static int on_scened_player_submoney(tcp_connection* coon, server_packet* pkt);	//场景服通知应用服扣money
	static int on_logind_sync_maxguid(tcp_connection* coon, server_packet* pkt);	//登录服同步guid最大累加数值
	static int on_logind_merge_server(tcp_connection* coon, server_packet* pkt);	//登陆服通知应用服合服了
	static int on_modify_showhand_dairu_coin(tcp_connection* conn, server_packet* pkt);//登录服通知应用服修改带入铜钱
	static int on_scened_send_char_info(tcp_connection *, server_packet *pkt);			//场景服发送聊天信息
	static int on_logind_send_to_appd_get360gift(tcp_connection *, server_packet *pkt);	//发送给应用服领取360特权
	//////////////////////////////////////////////////////////////////////////
	//后台命令
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
