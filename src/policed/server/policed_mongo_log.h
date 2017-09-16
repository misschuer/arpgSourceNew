#ifndef __POLICED_MONGO_LOG__
#define __POLICED_MONGO_LOG__

#include "policed_app.h"
#include "policed_context.h"
#include "policed_app.h"
#include "policed_object_manager.h"
#include "object/PlayerBase.h"

#ifdef WIN32
#include "db_wrap/mongo_wrap.h"
#define MongoWrap3 MongoWrap
#else
#include <db_wrap/mongo3_wrap.h>
#endif // WIN32


class PolicedMongoLog:public MongoWrap3{
public:
	PolicedMongoLog(log_holder_t *log);
	virtual ~PolicedMongoLog();

	string GetLogNS(string ns){return "logs."+ns;};
	string GetDailyNS(string ns){return "ht_daily_info.ht_daily_info"+ns;};
	string GetForgeNS(string ns){return "ht_forge_info."+ns;};
	string GetMoneyNS(string ns){return "log_gold_ingot."+ns;};
	string GetLogBaseNS(string ns){return "logs.ht_basic_info_"+ns;};
	string GetLogSystemNS(string ns){return "logs.ht_system_info_"+ns;};
	string GetServerName(string char_guid);

	virtual void Close();

	bool DecodeConnectionString(string conn_str,string& host,string& port,string& user, string& passwd, string &db_prefix, log_holder_t *logger/* = nullptr*/);
	bool Open(string conn_str,int log_level, string log_path);

	//�������GUID��ȡaccount
	string GetServerNameFromAccount(string account);
	
	void UpdatePlayerLockStatus(string account_id,uint32 status);

	void UpdatePlayerGagStatus(string player_guid,uint32 end_time);

	//������������״̬
	void UpdateAllHTBasicOnline(bool is_online);
	//��ȡbasicInfo����������б�
	void GetBasicInfoOnlinePlayer(set<string> &);
	//����ĳ���Ϊ������
	void UpdateHTBasicOffline(string player_guid);
	//������Һ�̨������Ϣ
	void  SaveHTBasicInfo(PlayerBase* player,bool online);
	//�����̨����������Ϣ
	void  SaveHTForgeInfo(string guid, uint32 forge_type, uint32 forge_level);

	//������Ҹ���ϵͳ������Ϣ
	void  SaveHTSystemInfo(PlayerBase* player);

	//��������̨������Ϣ
	void SaveHTCorpsInfo(BinLogObject* corps, string manager_guid, string manager_name, uint32 count);

	//�������а�
	void  SaveHTTopInfo();
	//��ȡ������а�����
	string GetTopInfoFromType(uint32 top_type);
	//��������׳��¼
	void SaveFirstRechargeInfo(map<string,string>& values);
	//��¼GM����
	void WriteGmCommand( const string & gm_id, string& gm_command );

	string GetCharNS(string ns){return "char."+ns;};

	void SaveBackupInfo(string guid,string save_time,uint32 level);
	//����Ԫ��������Ϣ
	void SaveGoldLog( const string &account, const string &player_id, const string &player_name, uint16 money_type, uint16 oper_type, double v,double old_value, double new_value, const string &trace_id, uint32 item_id, uint32 count, double unit_price, uint16 item_bind, uint16 item_del, uint32 level, uint32 quest);

	template<typename T>
	string toString(T t)
	{
		stringstream ss;
		ss << std::fixed << t;
		return ss.str();
	}

	template<typename T>
	void fromString(T& t,string v)
	{
		stringstream ss;
		ss << v;
		ss >> t;
	}	
private:
	log_holder_t *log_;
	string server_name_;
	string host_;
	int port_;
	string user_;
	string password_;
//	AsyncMongoDB *async_db_;
	string db_host_;
	int db_port_;
	string db_user_;
	string db_passwd_;	
	string db_prefix_;
	
};

#endif