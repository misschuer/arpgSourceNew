
#include "logind_app.h"
#include "logind_cache.h"
#include "logind_mongodb.h"
#include "logind_script.h"
#include <object/SharedDef.h>
#include "logind_context.h"
#include "logind_player.h"
#include "map_manager.h"

LogindMongoDB::LogindMongoDB(LogindObjectManager *mgr,log_holder_t *log):MongoDB(log),m_obj_mgr(mgr),is_localdb(false)
{

}

LogindMongoDB::~LogindMongoDB()
{
}

void LogindMongoDB::SaveBinlog(BinLogObject *blobj, bool fsync/* = false*/)
{
	if(!blobj)
		return;
	EObjectTypePrefix t = GuidManager::GetPrefix(blobj->guid());
	//�����
	if(t == ObjectTypePlayer)
	{
		SavePlayer(blobj, fsync);
		return;
	}
	else if(GuidManager::GetPrefix(blobj->GetOwner()) == ObjectTypePlayer)
	{
		SavePlayerOtherInfo(blobj, fsync);
		return;
	}	
	else if(t == ObjectTypeGlobalValue)
	{
		SaveGlobalValue(blobj);
		return;
	}

	//string data_name;
	////�жϱ�������
	//switch(t)
	//{
	//case ObjectTypeFaction:
	//	data_name = GetCharNS("faction_info");
	//	break;
	//case ObjectTypeFactionEvents:
	//	data_name = GetCharNS("faction_events");
	//	break;
	//default:
	//	break;
	//}
	//if(data_name.empty())
	//{
	//	return;
	//}

	//SaveBinlog(data_name,blobj, fsync);

	ASSERT(false);
}

void LogindMongoDB::SaveBinlogVec(vector<GuidObject*> vec, bool fsync /*= false*/)
{
	if(vec.empty())
		return;
	auto obj = dynamic_cast<BinLogObject*>(vec[0]);
	string guid = obj->guid();
	//�����
	EObjectTypePrefix t = GuidManager::GetPrefix(guid);
	Map wheres;
	wheres["server_name"] = GetServerName(guid);
	if(t = ObjectTypeGlobalValue)
	{
		//wheres["server_name"] = g_Config.server_name;
		//Delete(GetServerNS("global_value"),wheres);
	}
	//else if (t = ObjectTypeFaction)
	//{		
	//	Delete(GetCharNS("faction_info"),wheres);
	//	Delete(GetCharNS("faction_events"),wheres);
	//}
	else
		ASSERT(false);
	//�ٱ���
	for (auto it:vec)
	{
		BinLogObject *obj = dynamic_cast<BinLogObject*>(it);
		ASSERT(obj);
		SaveBinlog(obj);
	}
}

//����һ������
void LogindMongoDB::SaveDataset(const string &guid, bool fsync)
{
	if(GuidManager::GetPrefix(guid) == ObjectTypePlayer)
	{
		UpdatePlayerDBInfo(guid);
		return;
	}
	vector<GuidObject*> vec;
	if(guid == GLOBAL_VALUE_OWNER_STRING)
	{
		vec.push_back(LogindApp::g_app->m_rank_info);
		vec.push_back(LogindApp::g_app->m_systemmail);
		vec.push_back(LogindApp::g_app->m_asyncValue);
		vec.push_back(LogindApp::g_app->m_offlinemail);
		vec.push_back(LogindApp::g_app->m_counter);
		vec.push_back(LogindApp::g_app->m_globalvalue);
	}
	else
	{
		ObjMgr.GetDataSetAllObject(guid, vec);
	}
	SaveBinlogVec(vec, fsync);
}

//ָ�����ݿⱣ��binlogobject
void LogindMongoDB::SaveBinlog(string data_name,BinLogObject *blobj, bool fsync/* = false*/)
{
	Map result,wheres;
	Results results;
	string data,data_str;
	blobj->ToString(data,data_str);

	result["data"] = data;
	result["data_str"] = data_str;
	
	result["guid"] = blobj->guid();
	result["u_guid"] = SUB_GUID_STR_TO_INT(blobj->guid());
	result["name"] = blobj->GetName();
	result["server_name"] = GetServerName(blobj->guid());
	Insert(data_name,result, fsync);
	tea_pdebug("LogindMongoDB::SaveBinlog insert guid is %s", blobj->guid().c_str());
}

//�����������
void LogindMongoDB::SavePlayer(BinLogObject *blobj, bool fsync/* = false*/)
{
	Map result,wheres;
	Results results;
	string data,data_str;
	PlayerBase *player = dynamic_cast<PlayerBase*>(blobj);
	ASSERT(player);
	player->ToString(data,data_str);
	string server_name = GetServerName(player->guid());
	result["data"] = data;
	result["data_str"] = data_str;
	wheres["server_name"] = server_name;
	wheres["guid"] = player->guid();
	result["name"] = player->GetName();
	//��ѯ����û��
	if(player->m_db_hashcode == 1)
	{
		Mongo_Result mongo_reslut =QueryPlayerInfo("chars",GetServerName(player->guid()),wheres,results);
		if(mongo_reslut == MONGO_RES_NULL)
			player->m_db_hashcode = 0;
		if(mongo_reslut == MONGO_RES_ERROR)
			tea_pdebug("DatadMongoDB::Save_Player query chars fail guid is %s", player->guid().c_str());
	}

	//������ɫ
	if(player->m_db_hashcode == 0)
	{
		result["guid"] = player->GetGuid();
		result["u_guid"] = SUB_GUID_STR_TO_INT(player->GetGuid());
		result["u_create_date"] = toString((uint32_t)time(NULL));
		result["create_ip"] = player->GetCreateLoginIp();
		result["i_of_logins"] = toString(1);	
		result["account"] = player->GetAccount();
		result["u_delete_time"] = "0";
		result["server_name"] = GetServerName(player->GetGuid());
		Insert(GetPlayerInfo("chars",server_name),result, fsync);
		tea_pdebug("DatadMongoDB::Save_Player insert guid is %s", player->guid().c_str());
	}
	else
	{
		//����
		Update(GetPlayerInfo("chars",server_name),wheres,result, fsync);
		tea_pdebug("DatadMongoDB::Save_Player update guid is %s", player->guid().c_str());
	}
}

//�����������
void LogindMongoDB::SavePlayerOtherInfo(BinLogObject *blobj, bool fsync/* = false*/)
{
	Map result,wheres;
	Results results;
	string data,data_str;
	blobj->ToString(data,data_str);
	string server_name = GetServerName(blobj->guid());
	result["data"] = data;
	result["data_str"] = data_str;
	wheres["server_name"] = server_name;
	wheres["guid"] = blobj->guid();
	wheres["owner"] = blobj->GetOwner();
	if(blobj->m_db_hashcode == 1)
	{
		if(QueryPlayerInfo("player_other_info",server_name,wheres,results) == MONGO_RES_NULL)
			blobj->m_db_hashcode = 0;
	}

	if(blobj->m_db_hashcode == 0)
	{
		result["guid"] = blobj->guid();
		result["u_guid"] = SUB_GUID_STR_TO_INT(blobj->guid());
		result["server_name"] =server_name;
		result["owner"] = blobj->GetOwner();
		result["u_obj_type"] = toString(uint32(GuidManager::GetPrefix(blobj->GetGuid())));
		Insert(GetPlayerInfo("player_other_info",server_name),result, fsync);
		tea_pdebug("DatadMongoDB::Save_Player_Other_Info insert guid is %s", blobj->guid().c_str());
	}
	else
	{
		Update(GetPlayerInfo("player_other_info",server_name),wheres,result,fsync);
		tea_pdebug("DatadMongoDB::Save_Player_Other_Info update guid is %s", blobj->guid().c_str());
	}
}

void LogindMongoDB::SaveGlobalValue(BinLogObject *binlog)
{
	Map result,wheres;
	Results results;
	binlog->ToString(result["data"],result["data_str"]);
	wheres["server_name"] = g_Config.server_name;
	wheres["guid"] = binlog->guid();
	Upsert(GetServerNS("global_value"), wheres, result);
}

void LogindMongoDB::Load_GlobalValue(BinLogObject* binlog, const char *guid, bool load_db, std::function<void()> fun)
{
	binlog->SetGuid(guid);
	if(load_db)
	{
		Map wheres,result;
		wheres["guid"] = guid;
		wheres["server_name"] = g_Config.server_name;
		auto load_result = Load(GetServerNS("global_value"),wheres,result);
		if(load_result == MONGO_RES_SUCCESS)
		{		
			binlog->FromString(result["data"],result["data_str"]);
		}
		else if(load_result == MONGO_RES_ERROR)
		{
			tea_pinfo("LogindMongoDB::Load_GlobalValue %s fail", guid);
			ASSERT(false);
		}	
	}
	
	if(fun)
		fun();
	binlog->Clear();
	//�ڴ潻����������
	string call_put_guid = binlog->GetGuid();
	m_obj_mgr->CallPutObject(binlog,[call_put_guid](bool b){
		ASSERT(b);
		ObjMgr.InsertObjOwner(call_put_guid);
	});
	m_obj_mgr->CallSetTag(call_put_guid, GLOBAL_VALUE_OWNER_STRING);
}

void LogindMongoDB::LoadMaxGuid(BinLogObject *binlog, const char *table_name, EObjectTypePrefix type)
{
	Map wheres;
	Results results;
	wheres["server_name"] = g_Config.server_name;

	//if (type == ObjectTypeFaction)
	//{
	//	if(Query(GetCharNS(table_name),wheres,results,"u_guid", -1, 1) == MONGO_RES_ERROR)
	//	{
	//		tea_pinfo("LogindMongoDB::LoadMaxGuid fail %s", table_name);
	//		ASSERT(false);
	//	}
	//	if(results.size() && binlog->GetUInt32(type) < atol(results[0]["u_guid"].c_str()))
	//		binlog->SetUInt32(type, atol(results[0]["u_guid"].c_str()));
	//}
	if(type == ObjectTypePlayer)
	{
		uint32_t max_guid = 0;
		if(Query(GetCharNS(table_name),wheres,results,"u_guid", -1, 1) == MONGO_RES_SUCCESS)
		{
			fromString(max_guid,results[0]["u_guid"].c_str());
		}
		Results new_results;;
		if(Query(GetPlayerInfo(table_name,g_Config.server_name),wheres,new_results,"u_guid", -1, 1) == MONGO_RES_SUCCESS)
		{
			uint32_t next_max_guid = 0;
			fromString(next_max_guid,new_results[0]["u_guid"].c_str());
			if(max_guid < next_max_guid)
				max_guid = next_max_guid;
		}
		if(binlog->GetUInt32(type) < max_guid)
			binlog->SetUInt32(type, max_guid);
	}
}

void LogindMongoDB::LoadOtherMaxGuid(BinLogObject *binlog, EObjectTypePrefix type)
{
	Map wheres;
	Results results,new_results;
	wheres["server_name"] = g_Config.server_name;
	ASSERT(type != ObjectTypeNone);
	wheres["u_obj_type"] = toString(uint32(type));
	uint32 max_guid = 0;
	if(Query(GetPlayerInfo("player_other_info",g_Config.server_name),wheres,results,"u_guid", -1, 1) == MONGO_RES_ERROR)
	{
		tea_pinfo("LogindMongoDB::LoadOtherMaxGuid fail %d", type);
		ASSERT(false);
	}
	if(results.size())
		max_guid = atol(results[0]["u_guid"].c_str());
	if(Query(GetCharNS("player_other_info"),wheres,new_results,"u_guid",-1,1) == MONGO_RES_SUCCESS)
	{
		if(max_guid < atol(new_results[0]["u_guid"].c_str()))
			max_guid = atol(new_results[0]["u_guid"].c_str());
	}
	if(binlog->GetUInt32(type) < max_guid)
		binlog->SetUInt32(type, max_guid);
}

//����������������ô����ñ�
void LogindMongoDB::ReloadSeverNameByConfig()
{
	Map wheres; 
	Results results;
	wheres["merge_server"] = g_Config.server_name;
	tea_pinfo("LogindMongoDB::ReloadSeverNameByConfig this server_name is %s", g_Config.server_name.c_str());
	vector<string> server_list;
	if(Query(GetConfigNS("merge_server_list"),wheres,results) == MONGO_RES_ERROR)
	{
		ASSERT(false);
	}
	string server_name;
	uint32_t max_count = 0;
	for(auto result:results)
	{
		bool has_server = false;
		server_name = result["server_name"];
		uint32_t pos = 1;
		while (!LogindApp::g_app->GetServerID(pos).empty())
		{
			tea_pinfo("LogindMongoDB::ReloadSeverNameByConfig server_name is %s", server_name.c_str());
			if(server_name == LogindApp::g_app->GetServerID(pos))
			{
				tea_pinfo("LogindMongoDB::ReloadSeverNameByConfig server_name is %s, is old", server_name.c_str());
				has_server = true;
				break;
			}
			pos++;
		}
		if(!has_server)
		{
			server_list.push_back(server_name);
			max_count = pos;
		}
	}
	//�������ļӵ�binlog
	if(!server_list.empty())
	{
		for(auto it = server_list.begin();it != server_list.end();++it)
		{
			tea_pinfo("LogindMongoDB::ReloadSeverNameByConfig server_name is %s, is new", (*it).c_str());
			LogindApp::g_app->SetServerID(max_count,*it);
			max_count ++;
		}
	}
	tea_pinfo("LogindMongoDB::ReloadSeverNameByConfig end");
	//������������
	LogindApp::g_app->SetShowServerID();
	//�Ϸ��ˣ�Ҫ��ʼload���ݿ�
	is_localdb = false;
}

//��ȡ�Ϸ���Ϣ
bool LogindMongoDB::LoadMergeServerStatus(int32 opt_status,int32 merge_status, std::function<void(merge_info*)> cb)
{
	Map wheres;
	if(merge_status == MERGE_SERVER_TYPE_ORIGINAL)
		wheres["server_name"] = g_Config.server_name;
	else if(merge_status == MERGE_SERVER_TYPE_TARGAT)
		wheres["merge_server_name"] = g_Config.server_name;
	wheres["i_opt_status"] = toString(opt_status);

	AsyncLoad(GetConfigNS("merge_server_config"),wheres,[this,cb](AsyncMongoDBTask *task){
		if(task->result_ != MONGO_RES_SUCCESS)
		{		
			cb(nullptr);
			return;
		}

		//�첽��ѯһ�±��Ϸ��ķ�����
		Map where2;
		where2["server_name"] = task->value["merge_server_name"];
		string server = task->value["server_name"];
		AsyncLoad(GetConfigNS("server_info"),where2,[this,server,cb](AsyncMongoDBTask *task2){
		
			if(task2->result_ != MONGO_RES_SUCCESS)
			{
				cb(nullptr);
				return;
			}

			merge_info *info = (merge_info*)malloc(sizeof(merge_info));
			memset(info, 0, sizeof(info));

			//��ѯ����Ϣ
			strncpy(info->merge_server_host, task2->value["host"].c_str(),50);
			strncpy(info->merge_server_name, task2->value["server_name"].c_str(),50);
			strncpy(info->server_name, server.c_str(),50);
			fromString(info->merge_server_port,task2->value["i_port"]);

			//���ûص�
			cb(info);
		});
	});

	return false;
}

//���úϷ�״̬
void LogindMongoDB::UpdateMergeServerStatus(int32 new_status,int32 merge_status,string merge_server)
{
	Map wheres,result;
	if(merge_status == MERGE_SERVER_TYPE_ORIGINAL)
	{
		wheres["server_name"] = g_Config.server_name;
		wheres["merge_server_name"] = merge_server;
	}
	else if(merge_status == MERGE_SERVER_TYPE_TARGAT)
	{
		wheres["server_name"] = merge_server;
		wheres["merge_server_name"] = g_Config.server_name;
	}
	if(Load(GetConfigNS("merge_server_config"),wheres,result) != MONGO_RES_SUCCESS)
		return;
	Map values;
	values["i_opt_status"] = toString(new_status);
	Update(GetConfigNS("merge_server_config"),wheres,values);
}

//����server_info�Ϸ�״̬
void LogindMongoDB::UpdateSeverInfoMergeStatus()
{
	Map wheres,values;
	wheres["server_name"] = g_Config.server_name;
	values["i_merge_status"] = "1";
	Update(GetConfigNS("server_info"),wheres,values);
}

//���汾�����GUID
void LogindMongoDB::SaveServerMaxGuid()
{
	Map wheres,values;
	Results results;
	wheres["server_name"] = g_Config.server_name;
	values["i_player_max"] = toString(g_GuidMgr.m_data->GetUInt32(int32(ObjectTypePlayer)));
	if(Query(GetServerNS("server_max_guid"),wheres,results) == MONGO_RES_SUCCESS)
		Update(GetServerNS("server_max_guid"),wheres,values);
	else
	{
		values["server_name"] = g_Config.server_name;
		Insert(GetServerNS("server_max_guid"),values);
	}
}

//���汾�����GUID
void LogindMongoDB::GetServerMaxGuid(string server_name,uint32 &player_max)
{
	Map wheres,values;
	wheres["server_name"] = server_name;
	if(Load(GetServerNS("server_max_guid"),wheres,values) == MONGO_RES_SUCCESS)
	{
		fromString(player_max,values["i_player_max"]);
	}
}

//���·���������
bool LogindMongoDB::UpdateServerListInfo(string server_name)
{
	ReloadSeverNameByConfig();
	uint32 player_max = 0;
	GetServerMaxGuid(server_name,player_max);
	LogindApp::g_app->call_sync_guids_max(player_max);
	return true;
}

//���ݷ�������load���GUID
uint32 LogindMongoDB::LoadMaxGuidFromServerName(string server_name, EObjectTypePrefix type)
{
	Map wheres;
	Results results;
	wheres["server_name"] = server_name;
	string table_name;
	uint32_t max_guid  = 0;
	//if(type == ObjectTypeFaction)
	//{
	//	table_name = "corps_info";
	//	if(Query(GetCharNS(table_name),wheres,results,"u_guid", -1, 1) == MONGO_RES_SUCCESS)
	//	{
	//		fromString(max_guid,results[0]["u_guid"].c_str());
	//	}
	//}
	//else
	{
		if(type == ObjectTypePlayer)
		{
			table_name = "chars";
		}
		else
		{
			table_name = "player_other_info";
			wheres["u_obj_type"] = toString(uint32(type));
		}
		//���Դ��ܿ�õ�����ȡ���guid
		if(Query(GetCharNS(table_name),wheres,results,"u_guid", -1, 1) == MONGO_RES_SUCCESS)
		{
			fromString(max_guid,results[0]["u_guid"].c_str());
		}
		Results new_results;
		//�ٳ��Դӷֿ�����ȡ�ô��guid
		if(Query(GetPlayerInfo(table_name,server_name),wheres,new_results,"u_guid", -1, 1) == MONGO_RES_SUCCESS)
		{
			//����ȡ���
			uint32_t next_max_guid = 0;
			fromString(next_max_guid,new_results[0]["u_guid"].c_str());
			if(max_guid < next_max_guid)
				max_guid = next_max_guid;
		}
	}
	
	return max_guid;
}

//��ȡ����ʱ��
uint32 LogindMongoDB::LoadKaiFuShiJian()
{
	Map wheres,result;
	uint32 open_time = 0;
	wheres["server_name"] = g_Config.server_name;
	if(Load(GetConfigNS("server_info"),wheres,result) == MONGO_RES_SUCCESS)
	{
		fromString(open_time,result["u_open_time"]);
	}


	//TODO:����ʱ����� 20150507 11:59:59
	//if(open_time >= 1430971199 && !LogindApp::g_app->GetShowServerID())
		is_localdb = true;

	return open_time;
}

//���ÿ���ʱ��
void LogindMongoDB::UpdateKaiFuShiJian(uint32 open_time)
{
	Map wheres,values;
	wheres["server_name"] = g_Config.server_name;
	values["u_open_time"] = toString(open_time);
	Update(GetConfigNS("server_info"),wheres,values);
}

//���úϷ����ձ�
void LogindMongoDB::UpdateMergeServerList(string server_name)
{
	Map wheres,values;
	wheres["merge_server"] = g_Config.server_name;
	values["merge_server"] = server_name;
	Update(GetConfigNS("merge_server_list"),wheres,values);
}

bool LogindMongoDB::Load_GlobalValue()
{
	bool load_from_db = false;
	//��Ϸ����
	if(!LogindApp::g_app->m_gameconfig)
		LogindApp::g_app->m_gameconfig = new BinLogObject;
	Load_GlobalValue(LogindApp::g_app->m_gameconfig, GLOBAL_GAME_CONFIG, load_from_db,[&](){
		LogindApp::g_app->SetDbConnStr(g_Config.db_character);
		LogindApp::g_app->SetLogDbConnStr(g_Config.logdb_character);
		LogindApp::g_app->SetLoginKey(g_Config.login_key);
		LogindApp::g_app->SetLocalHddPath(g_Config.player_data_hdd_path);
		if(LogindApp::g_app->GetPlatformID() != g_Config.platform_id)
		{
			ASSERT(LogindApp::g_app->GetPlatformID().empty());
			LogindApp::g_app->SetPlatformID(g_Config.platform_id);
		}

		LogindApp::g_app->SetServerType(g_Config.server_type);	//���÷���������

		if (LogindApp::g_app->GetExtWebInterface() != g_Config.ext_web_interface)
			LogindApp::g_app->SetExtWebInterface(g_Config.ext_web_interface);

		if (LogindApp::g_app->GetConfSvrUrl() != g_Config.conf_svr)
			LogindApp::g_app->SetConfSvrUrl(g_Config.conf_svr);

		if (LogindApp::g_app->GetWorldServerUrl() != g_Config.world_server_url)
			LogindApp::g_app->SetWorldServerUrl(g_Config.world_server_url);

		Map wheres, result;
		LogindApp::g_app->SetServerID(0, g_Config.server_name);
		uint32 open_time = 0;
		uint32 merge_status = 0;
		wheres["server_name"] = g_Config.server_name;
		auto load_result = Load(GetConfigNS("server_info"),wheres,result);
		if(load_result == MONGO_RES_SUCCESS)
		{
			fromString(open_time,result["u_open_time"]);
			fromString(merge_status,result["i_merge_status"]);
			LogindApp::g_app->SetAddTime(merge_status);
			char *key = "server_list";
			Map wheres1;
			Results results;
			wheres1["merge_server"] = g_Config.server_name;
			if(Query(GetConfigNS("merge_server_list"),wheres1,results) == MONGO_RES_ERROR)
			{
				tea_pinfo("LogindMongoDB::Load_GlobalValue server_name = %s, merge_server_list is error", g_Config.server_name.c_str());
				ASSERT(false);
			}
			uint32 pos = 1;
			for(auto result1:results)
			{
				string server_name;
				server_name = result1["server_name"];
				if(server_name != g_Config.server_name)
				{
					LogindApp::g_app->SetServerID(pos,server_name);
					pos++;
				}				
			}
			//�����ȥ��
			while (!LogindApp::g_app->GetServerID(pos).empty())
			{
				LogindApp::g_app->SetServerID(pos,"");
				pos++;
			}
		}
		else if(load_result == MONGO_RES_ERROR)
		{
			tea_pinfo("LogindMongoDB::Load_GlobalValue %s", g_Config.server_name.c_str());
			ASSERT(false);
		}
		//������ʱ����0��ʱ�����óɵ�ǰʱ��Ϊ����ʱ��
		if(open_time == 0)
		{
			open_time = (uint32)time(NULL);
			UpdateKaiFuShiJian(open_time);
		}
		LogindApp::g_app->SetKaiFuShiJian(open_time);

	});

	//��ͼʵ��
	if(LogindApp::g_app->m_map_Instance_list)
		safe_delete(LogindApp::g_app->m_map_Instance_list);
	LogindApp::g_app->m_map_Instance_list = new MapManager();
	Load_GlobalValue(LogindApp::g_app->m_map_Instance_list,GLOBAL_MAP_INSTANCE_LIST_GUID, false);

	//ȫ�ֱ���
	if(!LogindApp::g_app->m_globalvalue)
		LogindApp::g_app->m_globalvalue = new BinLogObject();
	Load_GlobalValue(LogindApp::g_app->m_globalvalue,GLOBAL_OBJ_GUID, load_from_db,[&](){
		LogindApp::g_app->m_globalvalue->SetBinlogMaxSize(core_obj::SyncEventRecorder::MAX_BINLOG_SIZE_UNLIME);
	});

	//���а�
	if(!LogindApp::g_app->m_rank_info)
		LogindApp::g_app->m_rank_info = new BinLogObject();
	Load_GlobalValue(LogindApp::g_app->m_rank_info,GLOBAL_RANK_INFO,load_from_db);
	if(!LogindApp::g_app->m_rank_info_rask_pool)
		LogindApp::g_app->m_rank_info_rask_pool = new BinLogObject();
	Load_GlobalValue(LogindApp::g_app->m_rank_info_rask_pool,GLOBAL_RANK_INFO_RASK_POOL,load_from_db);

	//ϵͳ�ʼ�
	if(!LogindApp::g_app->m_systemmail)
		LogindApp::g_app->m_systemmail = new BinLogObject;
	Load_GlobalValue(LogindApp::g_app->m_systemmail,GLOBAL_SYSTEM_MAIL, load_from_db);

	//��������
	if(!LogindApp::g_app->m_asyncValue)
		LogindApp::g_app->m_asyncValue = new BinLogObject;
	Load_GlobalValue(LogindApp::g_app->m_asyncValue,GLOBAL_ASYNC_VALUE, load_from_db);

	//�����ʼ�
	if(!LogindApp::g_app->m_offlinemail)
		LogindApp::g_app->m_offlinemail = new BinLogObject;
	Load_GlobalValue(LogindApp::g_app->m_offlinemail,GLOBAL_OFFLINE_MAIL, load_from_db);

	//guid������
	if(!LogindApp::g_app->m_guid_mgr.m_data)
		LogindApp::g_app->m_guid_mgr.m_data = new BinLogObject();
	Load_GlobalValue(LogindApp::g_app->m_guid_mgr.m_data,GLOBAL_GUID_MANAGER_GUID, load_from_db,[&](){
		LoadMaxGuid(LogindApp::g_app->m_guid_mgr.m_data, "chars", ObjectTypePlayer);
		LogindApp::g_app->m_guid_mgr.m_data->SetBinlogMaxSize(core_obj::SyncEventRecorder::MAX_BINLOG_SIZE_UNLIME);
	});
	LogindApp::g_app->m_guid_mgr.LoadMyData();

	//����
	if(LogindApp::g_app->m_rightfloat)
		safe_delete(LogindApp::g_app->m_rightfloat);
	LogindApp::g_app->m_rightfloat = new BinLogObject;
	Load_GlobalValue(LogindApp::g_app->m_rightfloat,GLOBAL_RIGHT_FLOAT_GUID, false);
	
	//������Ϣ
	if(!LogindApp::g_app->m_notice_message)
		LogindApp::g_app->m_notice_message = new BinLogObject;
	Load_GlobalValue(LogindApp::g_app->m_notice_message,GLOBAL_NOTICE_MESSAGE, load_from_db);

	//�ͻ���������Ϣ
	if(!LogindApp::g_app->m_clientconfig)
		LogindApp::g_app->m_clientconfig = new BinLogObject;
	Load_GlobalValue(LogindApp::g_app->m_clientconfig,GLOBAL_CLIENT_GAME_CONFIG, load_from_db);

	//������
	if(!LogindApp::g_app->m_counter)
		LogindApp::g_app->m_counter = new BinLogObject;
	Load_GlobalValue(LogindApp::g_app->m_counter,GLOBAL_COUNTER, load_from_db,[&](){
		LogindApp::g_app->m_counter->SetBinlogMaxSize(core_obj::SyncEventRecorder::MAX_BINLOG_SIZE_UNLIME);
	});

	return true;
}

account_table *LogindMongoDB::UpsertAccount(string account,string pid, string sid,string uid, int is_FCM, string ip, string platdata,int gmlevel)
{
	//��֤�Ƿ�仯,�����
	bool haschange = false;
	//���Դӱ��ػ���ȡ
	auto *info =  g_Cache.GetAccount(account);
	
	//����һ���µ��ʻ���Ϣָ��	
	if(!info)
	{
		info = new account_table();
		info->gmlevel = gmlevel >= 0?gmlevel:0;
		strcpy(info->ip,ip.c_str());
		strcpy(info->name,account.c_str());
		strcpy(info->pid,pid.c_str());
		strcpy(info->platdata,platdata.c_str());
		strcpy(info->sid,sid.c_str());
		strcpy(info->uid,uid.c_str());
		info->is_FCM = is_FCM;
		g_Cache.AddAccount(info);
		//д��Ӳ��
		g_Cache.SaveAccountInfo(info);
		haschange = true;
	}
	
	//////////////////////////////////////////////////////////////////////////	
	if(is_FCM != info->is_FCM)
	{
		info->is_FCM = is_FCM;
		haschange = true;
	}
	//if(ip != info->ip)
	//{
	//	strcpy(info->ip,ip.c_str());
	//	haschange = true;
	//}
	if(!platdata.empty() && platdata != info->platdata)
	{
		strcpy(info->platdata,platdata.c_str());
		haschange = true;
	}
	if(gmlevel >= 0 && gmlevel != info->gmlevel)
	{
		info->gmlevel = gmlevel;
		haschange = true;
	}

	if(haschange)
	{
		//���²��������ݿ�
		Map result,wheres,values;
		//result["id"] = id;
		wheres["name"] = pid+'_'+sid+'_'+uid;
		wheres["server_name"] = GetServerNameFromAccount(account);

		result["pid"] = pid;
		result["sid"] = sid;
		result["s_uid"] = uid;
		result["is_fcm"] = toString(is_FCM);
		result["last_ip"] = ip;		
		result["i_gm_level"] = toString(0);	
		result["platdata"] = platdata;

		if(Load(GetServerNS("account"),wheres,values) == MONGO_RES_SUCCESS)
		{
			AsyncUpdate(GetServerNS("account"),wheres,result);
		}
		else
		{
			result["name"] = pid+'_'+sid+'_'+uid;
			result["server_name"] = GetServerNameFromAccount(account);
			uint32 now_time = (uint32)time(NULL);
			result["u_create_date"] = toString(now_time);
			AsyncInsert(GetServerNS("account"),result);
		}
	}	
	return info;
}

//////////////////////////////////////////////////////////////////////////
//��ɫ��

//��ȡ����Ҷ���
void LogindMongoDB::LoadPlayer(const string& account, const string &player_guid, vector<GuidObject*> &vec, std::function<void(bool,vector<GuidObject*>&)> fun)
{
	//�����ݿ���Ū
	Map where;
	where["guid"] = player_guid;
	where["u_delete_time"] = "0";
	where["server_name"] = GetServerName(player_guid);

	//��ʼload����
	AsyncLoad(GetPlayerInfo("chars",GetServerName(player_guid)),where,[this,player_guid,fun,&vec](AsyncMongoDBTask *task){
		if(!task || task->result_ != MONGO_RES_SUCCESS)
		{
			fun(false, vec);
			return;
		}

		//ok����load���ˣ�ʵ������Ұ�
		logind_player *p = new logind_player;
		p->FromString(task->value["data"],task->value["data_str"]);
		p->guid(player_guid);
		p->SetName(task->value["name"]);
		vec.push_back(p);

		Map wheres;
		wheres["owner"] = player_guid;
		wheres["server_name"] = GetServerName(player_guid);

		Results results;
		AsyncQuery(GetPlayerInfo("player_other_info",GetServerName(player_guid)),wheres,[this,player_guid,&vec,fun](AsyncMongoDBTask *task2){
			if(!task2 || task2->result_ == MONGO_RES_ERROR)
			{
				fun(false, vec);
				return;
			}

			for (auto it = task2->results.begin(); it != task2->results.end(); ++it)
			{
				auto& result = *it;
				BinLogObject *obj = new BinLogObject;
				if(result["guid"] == player_guid)
					continue;
				ASSERT(obj);
				obj->FromString(result["data"], result["data_str"]);
				obj->guid(result["guid"]);
				vec.push_back(obj);
			}
			fun(true, vec);
		});
	});
	
}

//��ȡ����Ҷ���
bool LogindMongoDB::LoadPlayer(const string& account, const string &player_guid, vector<GuidObject*> &vec)
{
	logind_player *player = nullptr;
	{
		Map where,result;
		where["guid"] = player_guid;
		where["u_delete_time"] = "0";
		where["server_name"] = GetServerName(player_guid);

		//Ϊ��������
		//����ʺŲ�Ϊ�գ���ȡ���µ�����,head_id����Ϊ����ʱ��
		if(!account.empty())
		{
			vector<char_create_info> char_list;
			g_Cache.GetCharList(account,char_list);
			if(!char_list.empty() && char_list[0].head_id > 0)
			{
				where["u_update_time"] = toString(char_list[0].head_id);
			}
		}

		//��ʼload����
		Mongo_Result load_res = LoadPlayerInfo("chars",GetServerName(player_guid),where,result);
		if(load_res == MONGO_RES_ERROR || load_res == MONGO_RES_NULL){
			tea_pinfo("load player %s from database, but not find", player_guid.c_str());
			return false;
		}
		//ok����load���ˣ�ʵ������Ұ�
		player = new logind_player;
		player->FromString(result["data"],result["data_str"]);
		player->guid(player_guid);
		player->SetName(result["name"]);		
		vec.push_back(player);
	}

	{
		Map where;
		where["owner"] = player_guid;
		where["server_name"] = GetServerName(player_guid);

		Results results;
		if(QueryPlayerInfo("player_other_info",GetServerName(player_guid),where,results) == MONGO_RES_ERROR)
		{
			tea_pinfo("DatadMongoDB::DbOperObjectForPlayer fail %s", player_guid.c_str());
			vec.clear();
			safe_delete(player);
			return false;
		}	
		for (auto& result:results)
		{
			BinLogObject *obj = new BinLogObject;
			if(result["guid"] == player_guid)
				continue;
			ASSERT(obj);
			obj->FromString(result["data"], result["data_str"]);
			obj->guid(result["guid"]);
			vec.push_back(obj);
		}
	}
	return true;
}

//���ݽ�ɫ���Ʒ���
string LogindMongoDB::FindGuidByName(string name, bool &has_err)
{
	//���ִ���һ��
	name = SBC2DBC(name);
	transform(name.begin(),name.end(),name.begin(),tolower);

	//�����������û��������ݿ������һ��
	string server_name = GetServerNameFromCharName(name);
	ASSERT(!server_name.empty());

	//�ж�һ�¸÷��Ƿ��Ѿ��ڻ���������
	if(std::find_if(m_loaded_servername.begin(),m_loaded_servername.end(),
		[server_name](string v){return server_name == v;}) == m_loaded_servername.end())
	{
		Results results;

		//ֻ����guid��name�����ֶ�
		Map outfield;
		outfield["name"] = "0";
		outfield["guid"] = "0";

		Map where;
		where["server_name"] = server_name;
		if(QueryPlayerInfo("chars",server_name,where,results,outfield) == MONGO_RES_ERROR)
		{
			has_err = true;
			return "";
		}

		for (auto result:results)
		{
			//���뻺��
			InsertGuidByName(result["guid"],result["name"]);
		}

		//�´ξͲ�����load���������
		m_loaded_servername.push_back(server_name);
	}
	has_err = false;
	return g_Cache.FindGuidByCharName(name);
}

void LogindMongoDB::InsertGuidByName(string guid,string name)
{
	name = SBC2DBC(name);
	transform(name.begin(),name.end(),name.begin(),tolower);
	g_Cache.AddCharName(guid, name);
}

//�����ʺŻ�ȡ��ɫ�б�
void LogindMongoDB::GetCharsList(string account, CharListDelegate  func)
{
	tea_pdebug("account %s get char list", account.c_str());

	vector<char_create_info> char_list;
	g_Cache.GetCharList(account,char_list);

	//����������������������Ҫ�ٴ�ȥ�����ݿ�
	if(!is_localdb && char_list.empty())
	{
		Map wheres;
		wheres["account"] = account;
		wheres["u_delete_time"] = "0";

		//�첽��ȡ���ݿ�Ľ�ɫ�б�
		AsyncQuery(GetPlayerInfo("chars",GetServerNameFromAccount(account)),wheres,[func,this,account](AsyncMongoDBTask *task){
			vector<char_create_info> char_list;

			if(!task)
			{
				tea_pinfo("LogindMongoDB::GetCharsList fail %s", account.c_str());
				func(false,char_list);
				return;;
			}

			uint32 last_update_date = 0;
			for (auto result:task->results)
			{
				char_create_info info;
				memset(&info,0,sizeof(info));
				fromString(info.guid,result["guid"]);
				fromString(info.name,result["name"]);

				//����ʱ�����µĿ϶��ǶԵģ�����Ϊ����ʱ��				
				fromString(info.head_id, result["u_update_time"]);	

				if(info.head_id > last_update_date)
				{					
					last_update_date = info.head_id;		
				}
				
				char_list.push_back(info);
				tea_pdebug("char %s %s", info.guid, info.name);
			}

			
			//ֻ��������ʱ������ֵ
			for (auto it = char_list.begin(); it != char_list.end();)
			{
				if(it->head_id == last_update_date)
				{
					//������û��б�����ʻ���ɫ��Ӧ��
					tea_pdebug("add char list guid %s",it->guid);
					g_Cache.AddAccountToChar(account,*it);
					g_Cache.SaveAccountCharInfo(account, it->guid);
					++it;					
				}
				else it = char_list.erase(it);
			}
			
			func(true,char_list);
		});
	}
	else
	{
		func(true,char_list);
	}	
}

//������ɫ
void LogindMongoDB::AddChars(string guid, string account, string name, string ip, string data, string data_str)
{
	Map result;
	result["guid"] = guid;
	result["u_guid"] = SUB_GUID_STR_TO_INT(guid);
	result["name"] = name;
	result["u_create_date"] = toString((uint32_t)time(NULL));
	result["create_ip"] = ip;
	result["i_of_logins"] = toString(1);	
	result["data"] = data;
	result["data_str"] = data_str;
	result["account"] = account;
	result["u_delete_time"] = "0";
	result["server_name"] = GetServerName(guid);
	Insert(GetPlayerInfo("chars",GetServerName(guid)),result);
}

//���½�ɫ����״̬
void LogindMongoDB::UpdateCharsOnline(string guid, uint8 status)
{	
	/*Map cond;
	cond["server_name"] = server_name_;
	if(guid.empty())
	{
	Delete(GetServerNS("online_chars"),cond);		
	}
	else if(status == PLAYER_ONLINE_STATE_OUTLINE)
	{
	cond["guid"] = guid;
	Delete(GetServerNS("online_chars"),cond);
	}
	else if(status == PLAYER_ONLINE_STATE_ONLINE)
	{
	Map values;
	values["guid"] = guid;
	values["server_name"] = server_name_;
	Insert(GetServerNS("online_chars"),values);
	}*/
}

//�������GUID��ȡaccount
string LogindMongoDB::FindAccountByGuid(string guid)
{
	Map wheres,result;
	wheres["guid"] = guid;
	wheres["server_name"] = GetServerName(guid);
	string account = "";
	if(LoadPlayerInfo("chars",GetServerName(guid),wheres,result) == MONGO_RES_SUCCESS)
	{
		account = result["account"];
	}
	return account;
}

//ɾ��
void LogindMongoDB::DelChars(string guid)
{
	Map wheres,result;
	wheres["guid"] = guid;
	result["u_delete_time"] = toString((uint32_t)time(NULL));
	Update(GetPlayerInfo("chars",GetServerName(guid)),wheres,result);
	Update(GetCharNS("chars"),wheres,result);
}

//��ȡ�ͻ��˰汾����
void LogindMongoDB::GetVersionsRequirements(std::function<void(uint32,const string&,const string&,uint32)> fun)
{
	Map wheres;
	wheres["server_name"] = g_Config.server_name;
	//wheres["i_module_type"] = toString(i);
	AsyncQuery(GetServerNS("versions_requirements"),wheres,[fun,this](AsyncMongoDBTask *task){
		std::set<int> all_versions;

		//������û�в鵽��¼������ִ����û�д���ִ��������
		if(task)
		{
			for (auto values:task->results)
			{
				int i_module_type = 0;
				fromString(i_module_type,values["i_module_type"]);

				string version, comment;
				uint32 create_time = 0;
				fromString(version, values["version"]);
				fromString(comment, values["comment"]);
				fromString(create_time, values["u_create_time"]);

				fun(i_module_type, version, comment, create_time);

				all_versions.insert(i_module_type);
			}		
		}
		
		for (uint32 i = 0; i < MAX_CLIENT_MODULE; i++)
		{
			if (all_versions.count(i)==0)
				fun(i, "", "", 0);
		}
	});
}

void LogindMongoDB::DbOperGameConfig(std::function<void(string,string)> fun)
{
	Results results;
	Map wheres;
	wheres["server_name"] = g_Config.server_name;
	if(Query(GetServerNS("game_config"),wheres,results) == MONGO_RES_ERROR)
	{
		//tea_pinfo("LogindMongoDB::DbOperGameConfig fail);
		return;
	}
	for (auto result:results)
	{
		fun(result["key"],result["i_value"]);
	}
}

//GM�����ֵ
void LogindMongoDB::SetGmRechargeNum(const char* account,uint32 amount, uint32 type)
{
	string recharge_id = g_GuidMgr.MAKE_NEW_GUID(ObjectTypeGMCommand,g_Config.server_name);
	Map insertInfo;
	insertInfo["_id"]=recharge_id;
	insertInfo["account"]=account;
	insertInfo["i_type"]=toString(type);
	insertInfo["i_amount"]=toString(amount);
	insertInfo["u_adddate"]=toString((uint32_t)time(NULL));
	insertInfo["i_status"]=toString(0);
	insertInfo["server_name"] = g_Config.server_name;
	AsyncInsert(GetGMIntfNs("gm_recharge"),insertInfo);

}

//�ж�����Ƿ����
bool LogindMongoDB::FindFriendByGuid(string guid, PlayerBase *player)
{
	Map wheres,result;
	wheres["guid"] = guid;
	wheres["server_name"] = GetServerName(guid);
	if(LoadPlayerInfo("chars",GetServerName(guid),wheres,result) == MONGO_RES_NULL)
		return false;
	player->FromString(result["data"],result["data_str"]);
	return true;
}

//��ȡ���а�����
void LogindMongoDB::LoadRankListInfo(string server_name, string &data, string &data_str)
{
	Map wheres,result;
	wheres["server_name"] = server_name;
	wheres["guid"] = GLOBAL_RANK_INFO;
	if(Load(GetServerNS("global_value"),wheres,result) == MONGO_RES_SUCCESS)
	{
		data = result["data"];
		data_str = result["data_str"];
	}
}

//��ȡͳ������
void LogindMongoDB::LoadCounterInfo(string server_name, string &data, string &data_str)
{
	Map wheres,result;
	wheres["server_name"] = server_name;
	wheres["guid"] = GLOBAL_COUNTER;
	if(Load(GetServerNS("global_value"),wheres,result) == MONGO_RES_SUCCESS)
	{
		data = result["data"];
		data_str = result["data_str"];
	}
}

//GM������·����
void  LogindMongoDB::ServerUpdate(uint32 server_type)
{
	Map result;
	result["plan_type"] = "update";
	result["u_plan_excu_time"] = toString(0);
	result["desc"] = "server " + g_Config.server_name + " update type is " + toString(server_type);
	result["i_plan_status"] = toString(0);
	result["param"] = "0," + toString(server_type) + ",0," + g_Config.server_name;
	AsyncInsert(GetOpertoolNS("plan_task_info"),result);
}

//ɾ��binlog
void LogindMongoDB::DeleteBinlog(const string &guid,const string &owner)
{
	EObjectTypePrefix t = GuidManager::GetPrefix(guid);
	////�ж�ɾ������
	//switch(t)
	//{
	//case ObjectTypeFaction:
	//	DelFaction(guid);
	//	break;
	//}
}

//ɾ��������Ϣ
void LogindMongoDB::DelFaction(const string &guid)
{
	Map wheres;
	wheres["guid"] =guid;
	wheres["server_name"] = GetServerName(guid);
	Delete(GetCharNS("faction_info"),wheres);
	wheres.clear();

	wheres["owner"] = guid;
	wheres["server_name"] = GetServerName(guid);
	Delete(GetCharNS("faction_events"),wheres);
}

//ȫ���������������Ϣ
void LogindMongoDB::UpdatePlayerDBInfo(const string &guid)
{
	vector<GuidObject*> vec;
	bool need_free = false;
	logind_player *player = ObjMgr.FindPlayer(guid);
	if(player)
	{
		//todo jzy�����ֵ�¼һ��������ô�죿
		ObjMgr.GetDataSetAllObject(guid, vec);
	}
	if(vec.empty())
	{
		need_free = true;
		g_Cache.LoadPlayer(guid, &player, vec);
	}
	if(vec.empty())
	{
		tea_pdebug("LogindCache::SaveChangePlayerToDB player data is empty, %s", guid.c_str());
		return;
	}
	ASSERT(player);

	if(player->GetLevel() < 10)
	{
		tea_pdebug("LogindCache::SaveChangePlayerToDB player level < 10 %s", guid.c_str());
		return;
	}
	Map wheres;
	Map result,__values;
	string server_name = GetServerName(guid);
	string data,data_str;
	//�ȱ��������
	player->ToString(data,data_str);
	wheres["guid"] = guid;
	wheres["server_name"] = server_name;	


	result["u_guid"] = SUB_GUID_STR_TO_INT(guid);
	result["name"] = player->GetName();
	result["u_create_date"] = toString(player->GetCreateTime());
	result["create_ip"] = player->GetCreateLoginIp();
	result["i_of_logins"] = toString(player->GetNumberOfLogins());	
	result["data"] = data;
	result["data_str"] = data_str;
	result["account"] = player->GetAccount();
	result["u_delete_time"] = toString(uint32(player->IsDelete()));
	//result["u_update_time"] =  toString(uint32(time(NULL)));

	if(Load(GetPlayerInfo("chars",server_name),wheres,__values) == MONGO_RES_SUCCESS)
	{
		Update(GetPlayerInfo("chars",server_name),wheres,result);
	}
	else
	{
		result["server_name"] = server_name;	
		result["guid"] = guid;
		Insert(GetPlayerInfo("chars",server_name),result);	//û�������
	}

	//���player_other_info��
	wheres.clear();
	wheres["owner"] = guid;
	wheres["server_name"] = GetServerName(guid);
	if(!Delete(GetPlayerInfo("player_other_info",GetServerName(guid)),wheres))
	{
		tea_perror("clear player other info %s fail", guid.c_str());
		return;
	}
	//��������player_other_info
	for (auto it:vec)
	{
		BinLogObject *blobj = dynamic_cast<BinLogObject*>(it);
		if(blobj == player)
			continue;
		blobj->ToString(data,data_str);
		result.clear();
		result["guid"] = blobj->guid();
		result["u_guid"] = SUB_GUID_STR_TO_INT(blobj->guid());
		result["server_name"] =server_name;
		result["owner"] = blobj->GetOwner();
		result["u_obj_type"] = toString(uint32(GuidManager::GetPrefix(blobj->GetGuid())));
		result["data"] = data;
		result["data_str"] = data_str;
		Insert(GetPlayerInfo("player_other_info",server_name),result);
	}
}
//����account��gm_level
void LogindMongoDB::UpdateAccountGMLevel(uint32 gm_level,string account,string server_name)
{
	Map wheres,result,values;
	wheres["name"] = account;
	wheres["server_name"] = server_name;
	if(Load(GetServerNS("account"),wheres,result) == MONGO_RES_NULL)
		return;
	values["i_gm_level"] = toString(gm_level);
	if(result["i_gm_level"] != toString(gm_level))
	{
		Update(GetServerNS("account"),wheres,values);
	}
}

//�������GUID��ȡaccount
string LogindMongoDB::GetAccountFromGuid(string player_id)
{
	Map wheres,result;
	wheres["guid"]=toString(player_id);
	wheres["server_name"] = GetServerName(player_id);
	if (!Load(GetPlayerInfo("chars", GetServerName(player_id)),wheres,result) == MONGO_RES_SUCCESS)
	{
		tea_perror("GetAccountFromGuid id[%u] error!",player_id.c_str());	
	}
	return result["account"];
}
