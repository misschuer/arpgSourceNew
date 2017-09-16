#ifndef _GLOBAL_VALUE_MANAGER_H_
#define _GLOBAL_VALUE_MANAGER_H_

#include "BinLogObject.h"
#include "ServerConnList.h"
#include "GuidManager.h"
#include <core_obj/GuidObjectTable.h>

#define GLOBAL_OBJ_GUID					"G.globalvalue"			//ȫ�ֶ���
#define GLOBAL_GAME_CONFIG				"G.gameconfig"			//��Ϸ����
#define GLOBAL_CLIENT_GAME_CONFIG		"G.ClientGameConfig"	//�ͻ���������Ϣ
#define GLOBAL_GUID_MANAGER_GUID		"G.guidmanager"			//guid��������
#define GLOBAL_RANK_INFO				"G.rankinfo"			//���а�����
#define GLOBAL_RANK_INFO_RASK_POOL		"G.rankinforaskpool"	//���а������
#define GLOBAL_RIGHT_FLOAT_GUID			"G.rightfloat"			//��������
#define GLOBAL_SYSTEM_MAIL				"G.systemMail"			//ϵͳ�ʼ�
#define GLOBAL_OFFLINE_MAIL				"G.offlineMail"			//�����ʼ�
#define GLOBAL_NOTICE_MESSAGE			"G.noticemessage"		//������Ϣ
#define GLOBAL_SAVE_TO_DB				"G.SaveToDbGuidList"	//����Ҫ���浽���ݿ���������
#define GLOBAL_COUNTER					"G.counter"				//������������������������
#define GLOBAL_ASYNC_VALUE				"G.asyncValue"			//��ͬ���ͻ��˵�ȫ������

class GlobalValueManager
{
public:
	GlobalValueManager()
		:m_globalvalue(NULL),m_map_Instance_list(NULL),m_rank_info(NULL)
		,m_rank_info_rask_pool(NULL),m_server_conn_list(NULL),m_systemmail(NULL),m_offlinemail(NULL)
		,m_rightfloat(NULL),m_gameconfig(NULL),m_clientconfig(NULL)
		,m_notice_message(NULL),m_save_to_db_guid_list(NULL),m_counter(NULL),m_asyncValue(NULL)
	{

	}

	~GlobalValueManager()
	{
	}
public:
	GuidManager	m_guid_mgr;					//���е�id������

	BinLogObject *m_globalvalue;			//�������
	BinLogObject *m_map_Instance_list;		//��ͼʵ���б�
	BinLogObject *m_rank_info;				//���а�����
	BinLogObject *m_rank_info_rask_pool;	//���а������
	ServerConnList *m_server_conn_list;		//�ڲ��������б�
	BinLogObject *m_rightfloat;				//��������
	BinLogObject *m_systemmail;				//ϵͳ�ʼ�
	BinLogObject *m_offlinemail;			//�����ʼ�
	BinLogObject *m_gameconfig;				//��Ϸ����
	BinLogObject *m_clientconfig;			//�ͻ���������Ϣ
	BinLogObject *m_notice_message;			//������Ϣ
	BinLogObject *m_save_to_db_guid_list;	//����Ҫ���浽���ݿ���������
	BinLogObject *m_counter;				//������
	BinLogObject *m_asyncValue;				//��ͬ���ͻ��˵�ȫ������

public:
	BinLogObject *CreateGlobalValues(core_obj::GuidObjectTable *objMgr, const string &guid);
public:
	//ƽ̨id
	const string &GetPlatformID(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_FIELD_PLATFORM_ID);}
	void SetPlatformID(const string &pid){m_gameconfig->SetStr(GAME_CONFIG_STRING_FIELD_PLATFORM_ID, pid);}
	//������id
	const string &GetServerID(uint32 i = 0){return m_gameconfig->GetStr(GAME_CONFIG_STRING_FIELD_SERVER + i);}
	void SetServerID(uint32 i, const string &server_name){m_gameconfig->SetStr(GAME_CONFIG_STRING_FIELD_SERVER + i, server_name);}
	void AddServerID(const string &server_name);
	//����ʱ��
	uint32 GetKaiFuShiJian(){return m_gameconfig->GetUInt32(GAME_CONFIG_INT_FIELD_KAIFUSHIJIAN);}
	void SetKaiFuShiJian(uint32 t){
		m_gameconfig->SetUInt32(GAME_CONFIG_INT_FIELD_KAIFUSHIJIAN, t);
	}
	//���ݿ����Ӵ�
	const string &GetDbConnStr(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_FIELD_DB_CONN);}
	void SetDbConnStr(const string &str){m_gameconfig->SetStr(GAME_CONFIG_STRING_FIELD_DB_CONN, str);}
	//��־���ݿ����Ӵ�
	const string &GetLogDbConnStr(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_FIELD_LOG_DB_CONN);}
	void SetLogDbConnStr(const string &str){m_gameconfig->SetStr(GAME_CONFIG_STRING_FIELD_LOG_DB_CONN, str);}
	//��¼��Կ
	const string &GetLoginKey(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_FIELD_LOGIN_KEY);}
	void SetLoginKey(const string &str){m_gameconfig->SetStr(GAME_CONFIG_STRING_FIELD_LOGIN_KEY, str);}
	//����Ӳ�����ݱ����ַ
	const string &GetLocalHddPath(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_LOCAL_HDD_PATH);}
	void SetLocalHddPath(const string &str){m_gameconfig->SetStr(GAME_CONFIG_STRING_LOCAL_HDD_PATH, str);}
	//�ⲿweb�ӿ�����
	const string &GetExtWebInterface(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_EXT_WEB_INTERFACE);}
	void SetExtWebInterface(const string &str){m_gameconfig->SetStr(GAME_CONFIG_STRING_EXT_WEB_INTERFACE, str);}
	//���÷�url��ַ
	const string &GetConfSvrUrl(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_CONF_SVR_URL);}
	void SetConfSvrUrl(const string &str){m_gameconfig->SetStr(GAME_CONFIG_STRING_CONF_SVR_URL, str);}
	//�����url����
	const string &GetWorldServerUrl(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_WORLD_SERVER_URL);}
	void SetWorldServerUrl(const string &str){m_gameconfig->SetStr(GAME_CONFIG_STRING_WORLD_SERVER_URL, str);}
	//����QQ��Ϣ
	void SetQQInfo(const string &str)
	{
		if(str != m_gameconfig->GetStr(GAME_CONFIG_STRING_FIELD_GM_QQ))
			m_gameconfig->SetStr(GAME_CONFIG_STRING_FIELD_GM_QQ,str);
	}
	//���QQ��Ϣ
	const string& GetQQInfo(){return m_gameconfig->GetStr(GAME_CONFIG_STRING_FIELD_GM_QQ);}
	//��汾��
	uint32 GetActivityVersion(){return m_globalvalue->GetUInt32(GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION);}
	const string &GetActivityScript(){return m_globalvalue->GetStr(GLOBALVALUE_STRING_FIELD_LIMIT_ACTIVITY_SCRIPT);}
	//�Ϸ�ʱ��
	uint32 GetAddTime(){return m_gameconfig->GetUInt32(GAME_CONFIG_INT_FIELD_ADDTIME);}
	void SetAddTime(uint32 i){m_gameconfig->SetUInt32(GAME_CONFIG_INT_FIELD_ADDTIME, i);}
	//���а�
	const string &GetRankInfoData(uint32 index){return m_rank_info->GetStr(index);}
	void SetRankInfoData(uint32 index, const string &data){m_rank_info->SetStr(index, data);}
	//�ͻ����Ƿ���ʾ������id
	void SetShowServerID(){m_gameconfig->SetBit(GAME_CONFIG_INT_FIELD_FLAGS,GAME_CONFIG_FIELD_FLAGS_SHOW_SERVER_ID);}
	bool GetShowServerID(){return m_gameconfig->GetBit(GAME_CONFIG_INT_FIELD_FLAGS,GAME_CONFIG_FIELD_FLAGS_SHOW_SERVER_ID);}
	//�������������
	void SetServerType(uint32 t){m_gameconfig->SetUInt32(GAME_CONFIG_INT_FIELD_WORLD_SVR_TYPE, t);}
	uint32 GetServerType(){return m_gameconfig->GetUInt32(GAME_CONFIG_INT_FIELD_WORLD_SVR_TYPE);}
	bool IsGameServer(){return GetServerType() == WORLD_SERVER_TYPE_GAME;}
	bool IsPKServer(){return GetServerType() == WORLD_SERVER_TYPE_PK;}	
	//��ȡ��汾��
	uint32 GetLimitActivityVersion(){return m_globalvalue->GetUInt32(GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION);}
	//������������״̬
	uint32 GetServerConnWorldStatus(){return m_globalvalue->GetUInt32(GLOBALVALUE_INT_FIELD_WORLD_CONNECTION_STATUS);}
	void SetServerConnWorldStatus(uint32 status){m_globalvalue->SetUInt32(GLOBALVALUE_INT_FIELD_WORLD_CONNECTION_STATUS, status);}
	//��ȡ���кϷ�server_name
	void GetMergeServerName(vector<string>& server_names);
	bool IsMyServer(const string &server_name);
	//����ÿ�հ�Ԫ�����
	void SetDailyAddBindGold(double val){m_counter->SetDouble(GLOBALCOUNTER_INT_FIELD_DAILY_ADD_BIND_GOLD,val);}
	//����ÿ�հ�Ԫ������
	void SetDailySubBindGold(double val){m_counter->SetDouble(GLOBALCOUNTER_INT_FIELD_DAILY_SUB_BIND_GOLD,val);}
	//����ÿ��Ԫ�����
	void SetDailyAddGoldIngot(double val){m_counter->SetDouble(GLOBALCOUNTER_INT_FIELD_DAILY_ADD_GOLD_INGOT,val);}
	//����ÿ��Ԫ������
	void SetDailySubGoldIngot(double val){m_counter->SetDouble(GLOBALCOUNTER_INT_FIELD_DAILY_SUB_GOLD_INGOT,val);}
	//����ÿ�����ӻ��
	void SetDailyAddSilver(double val){m_counter->SetDouble(GLOBALCOUNTER_INT_FIELD_DAILY_ADD_SILVER,val);}
	//����ÿ����������
	void SetDailySubSilver(double val){m_counter->SetDouble(GLOBALCOUNTER_INT_FIELD_DAILY_SUB_SILVER,val);}

protected:
	virtual void AfterCreateGlobalValue(BinLogObject *binlog);
	BinLogObject *CreateObject(const string &guid, BinLogObject **ptr, std::function<BinLogObject*(const string &)> fun = nullptr);
};

#endif
