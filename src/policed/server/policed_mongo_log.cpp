#include "policed_mongodb.h"
#include "policed_mongo_log.h"
#include <object/SharedDef.h>
#include <comm/log.h>
#include <comm/str_util.h>
#include <comm/b64.h>
#include <comm/crypt.h>

//#include "worker_pool.h"


PolicedMongoLog::PolicedMongoLog(log_holder_t *log):log_(log)
{
	server_name_ = PolicedApp::g_app->GetConfig().server_id;
}

PolicedMongoLog::~PolicedMongoLog()
{
}

void PolicedMongoLog::Close(){
}

bool PolicedMongoLog::DecodeConnectionString(string conn_str,string& host,string& port,string& user, string& passwd, string &db_prefix, log_holder_t *logger/* = nullptr*/)
{
	Tokens	tokensCharacter;
	//�ȳ��Բ����ܿ��ܷ��ÿ����ⲻ���ٵ��ý��� 
	StrSplit(tokensCharacter, conn_str, ';');
	if(tokensCharacter.size() < 4)
	{
		//��ʼ����
		char db_conn_str[1024];
		memset(db_conn_str, 0, sizeof(db_conn_str));
		if(base64_decode(db_conn_str,sizeof(db_conn_str),conn_str.c_str(),conn_str.size()) != 0)
		{
			if(logger)
				out_error(logger,"open mongodb base64_decode fail!");
			return false;
		}
		tea_v *p_tv = (tea_v*)(db_conn_str + sizeof(int));
		int str_size = *(int*)db_conn_str;
		str_size = str_size >> 3;
		tea_k tk_dec;
		tk_dec.k[0] = 78237478;
		tk_dec.k[1] = 9978445;
		tk_dec.k[2] = 45344231;
		tk_dec.k[3] = 78943894;
		for (int i = 0; i < str_size; i++)
			tean((TEAint32*)&tk_dec, (TEAint32*)(p_tv+i), -16);
		//out_str(log_,"open mongodb conn:[%s]",db_conn_str + sizeof(int));
		//�������
		StrSplit(tokensCharacter, db_conn_str + sizeof(int), ';');

		//���ܺ������ַ�����������
		if(tokensCharacter.size() < 4)
			return false;
	}
	host = tokensCharacter[0];
	port = tokensCharacter[1];
	user = tokensCharacter[2];
	passwd = tokensCharacter[3];
	if (tokensCharacter.size() >= 6)
		db_prefix = tokensCharacter[5]; 

	return true;
}


bool PolicedMongoLog::Open(string conn_str,int log_level, string log_path)
{
	string port;
	if(!DecodeConnectionString(conn_str,db_host_,port,db_user_,db_passwd_,db_prefix_,log_))
	{
		out_error(log_,"decode connection string faild!");
		return false;
	}
	db_port_ = atoi(port.c_str());
	if(!MongoWrap3::Open(db_host_, db_port_, db_user_,db_passwd_, "admin",log_level,log_path))
	{
		out_error(log_,"open mongodb conn faild!");
		return false;
	}

	return true;
}

void PolicedMongoLog::UpdatePlayerLockStatus(string account_id,uint32 status)
{
	////�������ʺ�
	Results results;
	Map wheres,values;
	wheres["server_name"] = GetServerNameFromAccount(account_id);
	wheres["account"] = account_id;
	values["u_lock"] = toString(status);
	if(Query(GetLogNS("ht_basic_info"),wheres,results) == MONGO_RES_SUCCESS)
	{
		Update(GetLogNS("ht_basic_info"),wheres,values);
	}
}


void PolicedMongoLog::UpdatePlayerGagStatus(string player_guid,uint32 end_time)
{
	////�������ʺ�
	Results results;
	Map wheres,values;
	wheres["server_name"] = GetServerName(player_guid);
	wheres["guid"] = player_guid;
	values["u_gag"] = toString(end_time);	//����ʱ����ڵ�ǰʱ���ʾ�Ѿ�����
	if(Query(GetLogNS("ht_basic_info"),wheres,results) == MONGO_RES_SUCCESS)
	{
		Update(GetLogNS("ht_basic_info"),wheres,values);
	}
}

//��������״̬
void PolicedMongoLog::UpdateAllHTBasicOnline(bool is_online)
{
	//�Ϸ�Ҫ����
	Map wheres,values;
	set<string> vec;
	string server_name;
	for (int i = 0;;++i)
	{
		server_name = PolicedApp::g_app->GetServerID(i);
		if(server_name.empty())
			break;
		vec.insert(server_name);
	}
	for(auto server:vec)
	{	
		wheres["server_name"] = server;
		wheres["i_online"] = toString(1);
		values["i_online"] = toString(uint32(is_online));
		Update(GetLogBaseNS(toString(PolicedApp::g_app->GetPlatformID())),wheres,values);
	}
}

//��ȡbasicInfo����������б�
void PolicedMongoLog::GetBasicInfoOnlinePlayer(set<string> &vec)
{
	vec.clear();
	Map wheres;
	Results results;
	string server_name;
	wheres["i_online"] = "1";
	//��ֹ��ѭ������ôҲû��һ���һ�ɣ�
	for (int i = 0; i < 10000;++i)
	{
		wheres["server_name"] = PolicedApp::g_app->GetServerID(i);		
		if(wheres["server_name"].empty())
			break;
		if(Query(GetLogBaseNS(toString(PolicedApp::g_app->GetPlatformID())),wheres,results) == MONGO_RES_ERROR)
		{
			tea_pwarn("PolicedMongoLog::GetBasicInfoOnlinePlayer query ht_basic_info from db fail, %s", wheres["server_name"].c_str());
			continue;
		}

		for(auto it:results)
		{
			vec.insert(it["guid"]);
		}
	}
}

//����ĳ���Ϊ������
void PolicedMongoLog::UpdateHTBasicOffline(string player_guid)
{
	Map wheres,values;
	Results results;
	wheres["server_name"] = GetServerName(player_guid);
	wheres["guid"] = player_guid;
	values["i_online"] = "0";
	Update(GetLogNS("ht_basic_info"),wheres,values);
}

//������Һ�̨������Ϣ
void PolicedMongoLog::SaveHTBasicInfo(PlayerBase* player,bool online)
{
	Map wheres,values;
	Results results;

	wheres["server_name"] = GetServerName(player->GetGuid()); //��������
	wheres["guid"] = player->GetGuid();//���GUID

	wheres["guid"] = player->GetGuid();
	values["i_level"] = toString(player->GetLevel());
	values["account"] = player->GetAccount();
	values["i_quest"] = toString(player->GetMainQuestID());
	values["i_force"] = toString(player->GetForce());
	values["u_last_login"] = toString(player->GetLastLoginTime());
	values["u_last_logout"] = toString(player->GetLastLogoutTime());
	values["i_online_time"] = toString(player->GetOnlineTime());
	values["i_recharge_sum"] = toString(player->GetRechargeSum());
	values["u_gold_ingot"] = toString(int64(player->GetMoney(MONEY_TYPE_GOLD_INGOT)));
	values["u_bind_gold"] = toString(int64(player->GetMoney(MONEY_TYPE_BIND_GOLD)));
	values["u_silver"] = toString(int64(player->GetMoney(MONEY_TYPE_SILVER) + player->GetMoney(MONEY_TYPE_SILVER_WAREHOUSE)));
	values["last_login_ip"] = player->GetLastLoginIp();
	values["i_login_sum"] = toString(player->GetNumberOfLogins());
	values["i_map"] = toString(player->GetMapId());
	values["u_pos_x"] = toString(uint32(player->GetPositionX()));
	values["u_pos_y"] = toString(uint32(player->GetPositionY()));
	values["name"] = player->GetName();
	values["u_gag"] = toString(player->GetGagEndTime());
	values["u_recharge_last_time"] = toString(player->GetRechargeLastTime());
	values["i_online"] = toString(uint32(online));
	values["i_gender"] = toString((uint32)player->GetGender());
	if(Query(GetLogNS("ht_basic_info"),wheres,results) == MONGO_RES_ERROR)
	{
		tea_pdebug("query ht_basic_info from db fail, %s", server_name_.c_str());
		return;
	}
	if(results.empty())
	{
		values["server_name"] = GetServerName(player->GetGuid());//��������
		values["guid"] = player->GetGuid();//���GUID
		values["account"] = player->GetAccount();//����ʺ�
		values["create_ip"] = player->GetCreateLoginIp();//��ɫ����ip
		values["u_create_date"] = toString(player->GetCreateTime());//��ɫ����ʱ��
		Insert(GetLogBaseNS(toString(PolicedApp::g_app->GetPlatformID())),values);
	}
	else
	{
		Update(GetLogBaseNS(toString(PolicedApp::g_app->GetPlatformID())),wheres,values);
	}
}

//�����̨����������Ϣ
void PolicedMongoLog::SaveHTForgeInfo(string guid, uint32 forge_type, uint32 forge_level)
{
	Map wheres,values;
	time_t t;
	time(&t);
	struct tm *p= localtime(&t);
	string table_name = "forge" + toString((p->tm_year + 1900) * 100 + (p->tm_mon + 1));
	values["server_name"] = GetServerName(guid);

	values["guid"] = guid;
	values["u_time"] = toString(uint32(time(NULL)));
	values["i_type"] = toString(forge_type);
	values["i_level"] = toString(forge_level);

	Insert(GetForgeNS(table_name),values);

}

//�������а�
void PolicedMongoLog::SaveHTTopInfo()
{
	//PolicedApp::g_app->m_rank_info;
	Map wheres,values;
	Results results;
	wheres["server_name"] = server_name_;
	time_t t;
	time(&t);
	struct tm *p= localtime(&t);
	uint32 now_time = (p->tm_year + 1900) * 1000000 + (p->tm_mon + 1) * 10000 + p->tm_mday * 100 + p->tm_hour;
	wheres["u_version"] = toString(now_time);
	if(Query(GetLogNS("ht_top_info"),wheres,results) != MONGO_RES_NULL)
		return;
	values["server_name"] = server_name_;
	values["u_version"] = toString(now_time);
	values["force_top"] = GetTopInfoFromType(RANK_TYPE_POWER);
	values["level_top"] = GetTopInfoFromType(RANK_TYPE_LEVEL);
	values["money_top"] = GetTopInfoFromType(RANK_TYPE_MONEY);
	Insert(GetLogNS("ht_top_info"),values);
}

string PolicedMongoLog::GetServerName(string char_guid)
{
	size_t pos = char_guid.rfind('.');
	if(pos == string::npos)
		return "";

	//�õ��ʺ���
	char_guid = char_guid.substr(pos+1,char_guid.length()-pos);

	return char_guid;
}

string PolicedMongoLog::GetTopInfoFromType(uint32 top_type){
	string top_data;
	for (int i = 0; i < 20; i ++)
	{
		uint32 index = 4 + top_type * RANK_LIST_MAX_VALUES * 2 + i * 2;
		string data = PolicedApp::g_app->m_rank_info->GetStr(index);
		string data_str = PolicedApp::g_app->m_rank_info->GetStr(index+1);
		BinLogObject *binlog = new BinLogObject;
		if(data.empty())
			continue;
		binlog->FromString(data, data_str);
		if(binlog->GetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID).empty())
			continue;
		top_data += binlog->GetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID) + " " + binlog->GetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_NAME)
			+ " " + toString((uint32)binlog->GetByte(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE,0)) + " ";

		switch (top_type)
		{
		case RANK_TYPE_POWER:
			top_data += toString((int64)binlog->GetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE)) ;
			break;
		case RANK_TYPE_LEVEL:
			top_data += toString(binlog->GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL)) ;
			break;
		case RANK_TYPE_MONEY:
			top_data += toString((int64)binlog->GetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_MONEY)) ;
			break;
		}

		top_data += "|";
		delete(binlog);
	}
	return top_data;
}

string PolicedMongoLog::GetServerNameFromAccount(string account)
{
	string server_name = "";
	size_t pos = account.find('_');
	if(pos == string::npos)
		return "";
	server_name = account.substr(0,pos);
	server_name += "_";
	//�ڶ������Ŵ���sid
	size_t pos2 = account.find('_',pos+1);//����,
	if(pos2 == string::npos)
		return "";
	server_name += account.substr(pos+1,pos2-pos-1);
	return server_name;
}


//��������ʱ����¼
void PolicedMongoLog::SaveBackupInfo(string guid,string save_time,uint32 level)
{
	Map values;
	values["guid"] = guid;
	values["save_time"] = save_time;
	values["server_name"] = GetServerName(guid);
	values["i_level"] = toString(level);
	Insert(GetLogNS("hd_backup_info"),values);
}

void PolicedMongoLog::SaveFirstRechargeInfo(Map& values)
{
	Insert(GetLogNS("ht_first_recharge"),values);
}

//��¼GM����
void PolicedMongoLog::WriteGmCommand( const string & gm_id, string& gm_command )
{
	Map insertInfo;
	insertInfo["gm_id"]=gm_id;
	insertInfo["gm_command"]=gm_command;
	insertInfo["u_time"]=toString((uint32_t)time(NULL));
	insertInfo["server_name"] = server_name_;

	Insert(GetLogNS("log_gm_command"),insertInfo);
}

//����Ԫ��������Ϣ
void PolicedMongoLog::SaveGoldLog( const string &account, const string &player_id, const string &player_name, uint16 money_type, uint16 oper_type, double v,double old_value, double new_value, const string &trace_id, uint32 item_id, uint32 count, double unit_price, uint16 item_bind, uint16 item_del, uint32 level, uint32 quest)
{
	Map insertInfo;
	insertInfo["account"]=account;
	insertInfo["player_id"]=player_id;
	insertInfo["player_name"] = player_name;
	insertInfo["u_oper_time"]=toString((uint32_t)time(NULL));
	insertInfo["i_money_type"]=toString(money_type);
	insertInfo["i_oper_type"]=toString(oper_type);
	insertInfo["i_value"]=toString(v);
	insertInfo["i_old_amount"]=toString(old_value);
	insertInfo["i_new_amount"]=toString(new_value);
	insertInfo["trace_id"]=trace_id;
	insertInfo["i_item_id"]=toString(item_id);
	insertInfo["i_count"]=toString(count);
	insertInfo["i_unit_price"]=toString(unit_price);
	insertInfo["i_item_bind"]=toString(item_bind);
	insertInfo["i_item_del"]=toString(item_del);
	insertInfo["i_level"]=toString(level);
	insertInfo["i_quest"]=toString(quest);
	insertInfo["server_name"] = GetServerNameFromAccount(account);
	time_t t;
	time(&t);
	struct tm *p= localtime(&t);
	uint32 today = (p->tm_year + 1900) * 10000 + (p->tm_mon + 1) * 100 + p->tm_mday;
	insertInfo["i_create_day"] = toString(today);

	int change_type = 2;
	switch (oper_type)
	{
	case MONEY_CHANGE_TYPE_CHARGE:
		change_type = HT_MONEY_CHANGE_TYPE_RECHARGE;
		break;
	case MONEY_CHANGE_TYPE_CHARGE_3:
		change_type = HT_MONEY_CHANGE_TYPE_SUB;
		break;
	case MONEY_CHANGE_TYPE_CHARGE_4:
		change_type = HT_MONEY_CHANGE_TYPE_REWARD;
		break;
	case MONEY_CHANGE_TYPE_CHARGE_2:
		change_type = HT_MONEY_CHANGE_TYPE_REBATE;
		break;
	case MONEY_CHANGE_TYPE_STALL_SALE:
	case MONEY_CHANGE_TYPE_TRADE:
		change_type = HT_MONEY_CHANGE_TYPE_TRADING;
		break;
	default:
		if(v > 0)
			change_type = HT_MONEY_CHANGE_TYPE_REWARD;
		else
			change_type = HT_MONEY_CHANGE_TYPE_CONSUMPTION;
		break;
	}
	insertInfo["i_change_type"] = toString(change_type);
	string table_name = "gold" + toString((p->tm_year + 1900) * 100 + (p->tm_mon + 1));

	Insert(GetMoneyNS(table_name),insertInfo);
}
