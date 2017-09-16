#include "logind_cache.h"
#include "map_manager.h"
#include "logind_player.h"
#include "logind_mongodb.h"
#include <shared/util.h>

#define OBJECT_END_STRING "------------------"

#define GAME_SERVER_SAVE_PLAYER_TIMEOUT 300
#define PK_SERVER_SAVE_PLAYER_TIMEOUT 3

LogindCache::LogindCache()
{
	m_storage = new core_obj::Storage([](string guid){
		//����guid������Ҫnewʲô����binlog
		BinLogObject *ptr = NULL;
		switch (GuidManager::GetPrefix(guid))
		{
		case ObjectTypePlayer:
			ptr = new logind_player;
			break;
		default:
			if(guid == GLOBAL_MAP_INSTANCE_LIST_GUID)
			{
				ASSERT(!LogindApp::g_app->m_map_Instance_list);
				LogindApp::g_app->m_map_Instance_list = new MapManager;
				ptr = LogindApp::g_app->m_map_Instance_list;
				break;
			}

			if(guid == GLOBAL_SAVE_TO_DB)
			{
				if(!LogindApp::g_app->m_save_to_db_guid_list)
					LogindApp::g_app->m_save_to_db_guid_list = new SavePlayerGuidObj;
				ptr = LogindApp::g_app->m_save_to_db_guid_list;
				break;
			}

			//�൱���Թ�
			if(guid == GLOBAL_SERVER_CONNN_LIST_GUID)
			{
				ptr = new BinLogObject;
				break;
			}

			ptr = LogindApp::g_app->CreateGlobalValues(LogindApp::g_app->m_obj_mgr, guid);
			if(!ptr)
			{
				ptr = new BinLogObject;
			}
			break;
		}
		ptr->guid(guid);
		return ptr;
	});
	//m_storage->Goto(g_Config.backup_hdd_path);
}

LogindCache::~LogindCache()
{
	for(auto it = m_accountMaps.begin();it != m_accountMaps.end();++it)
	{
		free(it->second);
	}
	m_accountMaps.clear();
	safe_delete(m_storage);
}

void LogindCache::AddAccount(account_table *info)
{
	//ASSERT(!GetAccount(info->name));
	auto account = GetAccount(info->name);
	if(account)
		safe_delete(account);
	m_accountMaps[info->name] = info;
}

account_table *LogindCache::GetAccount(const string &account)
{
	auto it = m_accountMaps.find(account);
	if(it != m_accountMaps.end())		
		return it->second;
	return NULL;
}

void LogindCache::GetCharList(const string &account,vector<char_create_info>& result)
{
	if(!LogindApp::g_app->IsGameServer())
		return;
	result.clear();

	//�ӽ�ɫ���߻���ȡ�ý�ɫ�б�
	auto it = m_charListHD.find(account);
	if(it != m_charListHD.end() && strlen(it->second.guid) > 0)
	{				
		result.push_back(it->second);
		return;
	}
}

void LogindCache::AddCharName(const string &guid, const string &name)
{
	m_charNameMaps[name] = guid;
	m_storage->Goto(g_Config.player_data_hdd_path);
	m_storage->AddContent("char_name.txt", guid + ' ' + name + '\n');
}

const string &LogindCache::FindGuidByCharName(const string &name)
{
	auto it = m_charNameMaps.find(name);
	if(it != m_charNameMaps.end())
		return it->second;
	static string null_res = "";
	return null_res;
}

//��ȡ���еĽ�ɫ��
void LogindCache::LoadAllCharName()
{
	m_storage->Goto(g_Config.player_data_hdd_path);
	m_storage->ReadFile("char_name.txt", [&](const string &str){
		Tokens tokens;
		StrSplit(tokens, str, ' ');
		if(tokens.size() < 2)
			return true;
		m_charNameMaps[tokens[1]] = tokens[0];
		return true;
	});
}

void LogindCache::AddAccountToChar(const string& account,char_create_info& info)
{
	m_charListHD[account] = info;
}

void LogindCache::AddAccountToChar(const string& account,string guid)
{
	char_create_info info;
	memset(&info, 0 ,sizeof(info));
	strcpy(info.guid,guid.c_str());	
	m_charListHD[account] = info;
}

//����Ϸ���־�ļ�
void LogindCache::SaveFileToMergeServer(const string& file_name, const string& now_time)
{
	//m_storage->SaveFile(file_name,now_time);
}


//�ͷŵǳ�����һ���
void LogindCache::FreeLogoutPlayer(bool immediately)
{
	time_t t = time(nullptr);
	for (auto it = m_logoutChar.begin(); it != m_logoutChar.end();)
	{
		if(immediately
			|| (LogindApp::g_app->IsGameServer() && t > it->second + GAME_SERVER_SAVE_PLAYER_TIMEOUT)
			|| (LogindApp::g_app->IsPKServer() && t > it->second + PK_SERVER_SAVE_PLAYER_TIMEOUT))
		{
			//�������ݣ��ͷ�����
			tea_pdebug("LogindCache::FreeLogoutPlayer %s", it->first.c_str());
			//ֻ����Ϸ������Ҫ��������
			if(LogindApp::g_app->IsGameServer())
				SavePlayerData(it->first);
			//�ͷ�
			ObjMgr.RemovePlayerData(it->first);
			it = m_logoutChar.erase(it);
			continue;
		}
		++it;
	}
}

//���һ���ǳ��������
void LogindCache::AddLogoutPlayer(const string &guid)
{
	ASSERT(!guid.empty());
	if(!ObjMgr.Get(guid))//�����������û�У��ǾͲ�����
		return;
	auto it = m_logoutChar.find(guid);
	ASSERT(it == m_logoutChar.end());
	m_logoutChar[guid] = time(nullptr);
}

//ɾ��һ���ǳ���һ���
void LogindCache::DelLogoutPlayer(const string &guid)
{
	//auto it = m_logoutChar.find(guid);
	//ASSERT(it != m_logoutChar.end());
	m_logoutChar.erase(guid);
}


//����Զ���������
void LogindCache::Update(logind_player *player)
{
	if(!LogindApp::g_app->IsGameServer())
		return;

	if(!player)
		return;
	time_t t = time(nullptr);
	if(player->GetAutoSaveTime() && player->GetAutoSaveTime() > t)
		return;
	if(player->GetAutoSaveTime() != 0)
		SavePlayerData(player->guid());
	//���һ���ӣ�����ҵı��澡����ɢ
	player->SetAutoSavetime(t + g_Config.auto_save_time + irand(-60,60));
}

//��ȡ���󼯺�
bool LogindCache::LoadDataSet(const string &guid, vector<GuidObject*> &vec)
{
	m_storage->Goto(g_Config.player_data_hdd_path);
	if(!m_storage->Load(guid, vec))
		return false;
	if(vec.empty())
		return false;
	return true;
}

//��ȡ��Ҷ���
bool LogindCache::LoadPlayer(const string &guid, logind_player **player, vector<GuidObject*> &vec)
{
	*player = nullptr;
	if(!LoadDataSet(guid, vec))
		return false;
	set<string> guid_set;//ȥ��
	for (auto it = vec.begin(); it != vec.end();)
	{
		GuidObject *obj = *it;
		//ȥ��
		if(guid_set.find(obj->guid()) != guid_set.end())
		{
			it = vec.erase(it);
			safe_delete(obj);
			continue;
		}
		guid_set.insert(obj->guid());
		//���������
		if(obj->guid() == guid)
		{
			*player = dynamic_cast<logind_player*>(obj);
		}
		++it;
	}
	ASSERT(*player);
	return true;
}

//������Ҷ���
void LogindCache::SavePlayerData(const string &guid)
{
	if(!LogindApp::g_app->IsGameServer())
		return;
	vector<GuidObject*> vec;
	ObjMgr.GetDataSetAllObject(guid, vec);
	logind_player *player = ObjMgr.FindPlayer(guid);
	ASSERT(player);
	SavePlayerData(guid, vec, player->GetLevel());
}

//ֱ�ӱ������ݵ�Ӳ��,�����ļ�
bool LogindCache::SaveData(const string &file_name, const string &content)
{
	string file = file_name + BINLOG_EXT_NAME;
	return m_storage->SaveFile(file, content);
}

//ͨ�����guid��ȡϵ�л��ַ���
string LogindCache::GetPlayerDataStr(const string &guid)
{
	vector<GuidObject*> vec;
	ObjMgr.GetDataSetAllObject(guid, vec);
	if(vec.empty())
	{
		stringstream ss;
		m_storage->ReadFile(guid + BINLOG_EXT_NAME, [&](const string &txt){
			ss << txt << "\n";
			return true;
		});
		return ss.str();
	}
	return PlayerDataToString(guid, vec);
}

//������������л����ַ���
string LogindCache::PlayerDataToString(const string &guid, vector<GuidObject*> &vec)
{
	//��������ŵ���һ��
	for (uint32 i = 0; i < vec.size(); i++)
	{
		GuidObject *obj = vec[i];
		if(obj->guid() == guid)
		{
			if(i == 0)
				break;
			vec[i] = vec[0];
			vec[0] = obj;
			break;
		}
	}

	stringstream ss;
	for (auto o:vec)
	{
		string ints,strs;
		o->ToString(ints,strs);
		ss << o->guid() << "\n" << ints << "\n" << strs << "\n";
	}
	return ss.str();
}

//������Ҷ���
void LogindCache::SavePlayerData(const string &guid, vector<GuidObject*> &vec, uint32 level)
{
	if(LogindApp::g_app->m_globalvalue && !LogindApp::g_app->IsGameServer())
		return;
	if(vec.empty())
	{
		tea_pdebug("LogindCache::SavePlayerData vec is empty %s", guid.c_str());
		return;
	}
	string data = PlayerDataToString(guid, vec);
	//��ʼ����
	m_storage->Goto(g_Config.player_data_hdd_path);
	SaveData(guid, data);

	static char temp[100];
	sprintf(temp, "%s %u\n", guid.c_str(), level);
	string guid_str = temp;
	//���汸������
	m_storage->AddContent("backuplist.txt", guid_str);
	//ÿ�ձ������ݵ����ݿ�
	time_t now = time(NULL);
	struct tm *p= localtime(&now);
	int today = (1900 + p->tm_year) * 10000 + (p->tm_mon+1) * 100 + p->tm_mday;
	sprintf(temp,"savetodb_%d.txt", today);
	m_storage->AddContent(temp, guid_str);
}

//�����������
void LogindCache::Backup(const string &gm_path/* = ""*/)
{
	if(!LogindApp::g_app->IsGameServer())
		return;
	tea_pinfo("LogindCache::Backup begin");
	//���ļ��а���Ҷ�������
	map<string, uint32> players;
	m_storage->Goto(g_Config.player_data_hdd_path);
	if(!m_storage->ReadFile("backuplist.txt", [&players](const string &txt){
		Tokens tokens;
		StrSplit(tokens, txt, ' ');
		if(tokens.empty())
			return true;
		string guid = tokens[0];
		uint32 level = 0;
		if(tokens.size() >= 2)
			level = atol(tokens[1].c_str());
		players[guid] = level;
		return true;
	}))
	{
		tea_perror("LogindCache::Backup read file fail");
		return;
	}
	//��ʼ����
	time_t t = time(nullptr);
	struct tm * temp_tm = localtime(&t);
	char temp[50];
	if(gm_path.empty())
		sprintf(temp, "%d%.2d%.2d%.2d%.2d", 1900+temp_tm->tm_year, temp_tm->tm_mon+1, temp_tm->tm_mday, temp_tm->tm_hour, temp_tm->tm_min);
	else
		strncpy(temp, gm_path.c_str(), 49);
	string topath = g_Config.backup_hdd_path + "/" + temp + "/";
	m_storage->Goto(topath);
	string frompath = g_Config.player_data_hdd_path + "/";
	for (auto it:players)
	{
		if(it.first.empty())
			continue;
		string src = frompath + it.first + BINLOG_EXT_NAME;
		string dst = topath + it.first + BINLOG_EXT_NAME;
		if(!m_storage->CopyAFile(src, dst))
			tea_perror("LogindCache::Backup fail , from %s  to %s", src.c_str(), dst.c_str());
		//֪ͨ��־��������
		WorldPacket pkt (INTERNAL_OPT_SAVE_BACKUP);
		pkt << it.first << temp << it.second;
		LogindApp::g_app->SendToPoliced(pkt);
	}
	//ɾ������txt�ļ�
	m_storage->Remove("backuplist.txt");
	tea_pinfo("LogindCache::Backup end");
}

//�����б仯����ҵ����ݿ�
void LogindCache::SaveChangePlayerToDB(bool is_merge/* = false*/)
{
	if(!LogindApp::g_app->IsGameServer())
		return;

	//����Ѿ��ڱ����ˣ��ͺ��԰�
	SavePlayerGuidObj *save_obj = dynamic_cast<SavePlayerGuidObj*>(LogindApp::g_app->m_save_to_db_guid_list);
	ASSERT(save_obj);
	if(save_obj->GetIndex() < save_obj->GetCount())
		return;

	//���д������guid����
	set<string> guid_set;
	int today;
	if(is_merge)
	{
		//�����ܴ��ֵ���Ͷ�����뱣����
		today = 999999999;
		//������Ϊʲô���ñ��棬�����������Ҳ��Ҫ��
		ObjMgr.ForEachPlayer([&guid_set](logind_player *player){
			guid_set.insert(player->guid());
		});
		save_obj->SetPost();
	}
	else
	{
		time_t now = time(NULL);
		struct tm *p= localtime(&now);
		static char temp[50];
		today = (1900 + p->tm_year) * 10000 + (p->tm_mon+1) * 100 + p->tm_mday;
		save_obj->UnSetPost();
	}
	
	vector<string> file_vec;
	//���һ�����õ�Ŀ¼,����������򴴽�
	m_storage->Goto(g_Config.player_data_hdd_path);
	m_storage->ForEachDir([&](string full_name, string file_name){
		//�������е�savetodbǰ׺�ļ���savetodb.txt�ܱ�
		if(file_name.find("savetodb") == string::npos)
			return;
		bool work = file_name == "savetodb.txt";
		if(!work)
		{
			int i = -1;
			work = (sscanf(file_name.c_str(), "savetodb_%d.txt", &i) > 0 && i > 0 && today > i);
		}
		if(!work)
			return;

		file_vec.push_back(file_name);
		m_storage->ReadFile(file_name, [&](string str){
			Tokens token;
			StrSplit(token, str, ' ');
			if(!token.empty() && !token[0].empty())
				guid_set.insert(token[0]);
			return true;
		});
	});
	//û�У��Ͳ����˰ɣ�����Ҫ�������������
	//if(guid_set.empty())
	//	return;
	//����
	guid_set.erase(GLOBAL_VALUE_OWNER_STRING);
	//����
	//guid_set.erase(LEAGUE_BINLOG_OWNER_STRING);
	
	vector<string> vec;
	vector<string> vec_2;
	//�Ϸ���ʱ���ǲ���Ҫpost���������
	if(!is_merge)
	{
		vec.push_back(GLOBAL_VALUE_OWNER_STRING);
		// ����
		//vec.push_back(LEAGUE_BINLOG_OWNER_STRING);
	}
	//���ߵ�
	for (auto it:guid_set)
	{
		if(ObjMgr.Get(it))
			vec.push_back(it);
		else
			vec_2.push_back(it);
	}
	//�����ߵ�
	for (auto it:vec_2)
	{
		string guid_server_name = MongoDB::GetServerName(it);
		if(!LogindApp::g_app->IsMyServer(guid_server_name))
		{
			tea_pinfo("LogindCache::SaveChangePlayerToDB not local data, %s", it.c_str());
			continue;
		}
		vec.push_back(it);
	}
	
	save_obj->SetToday(today);
	uint32 i = 0;
	for (auto it:vec)
	{
		save_obj->SetSavePlayerGuid(i, it);
		i++;
	}
	save_obj->SetCount(i);
	save_obj->SetIndex(0);

	//ɾ���ļ�
	for (auto it:file_vec)
	{
		m_storage->Remove(it);
	}
}

//�ӱ���Ӳ�̰������˺���Ϣ������
void LogindCache::LoadAllAccountInfo()
{
	m_storage->Goto(g_Config.player_data_hdd_path);
	stringstream ss;
	bool first_line = true;
	bool new_version = false;
	string account_file = g_Config.player_data_hdd_path + "/account.txt";
	if(!core_obj::Storage::IsHaveFile(account_file))
	{
		m_storage->AddContent("account.txt", "new version\n");
		return;
	}

	if(!m_storage->ReadFile("account.txt", [&](const string &str){
		if(first_line)
		{
			new_version = (str == "new version");
			first_line = false;
			return new_version;
		}

		account_table *info = new account_table;
		info->NewFromString(str);
		AddAccount(info);
		return true;
	}))
	{
		tea_perror("LogindCache::LoadAllAccountInfo read  txt file fail");
		return;
	}

	//��������°汾���ļ���ɾ������
	if(!new_version)
	{
		m_storage->Remove("account.txt");
		m_storage->AddContent("account.txt", "new version\n");
	}
}

//�����˺���Ϣ��Ӳ����
void LogindCache::SaveAccountInfo(account_table *info)
{
	ASSERT(info);
	string str = info->ToString();
	m_storage->Goto(g_Config.player_data_hdd_path);
	m_storage->AddContent("account.txt", str + "\n");
}

//�ӱ���Ӳ�̰������˺Ž�ɫ��Ϣ������
void LogindCache::LoadAllAccountCharInfo()
{
	m_storage->Goto(g_Config.player_data_hdd_path);
	stringstream ss;
	if(!m_storage->ReadFile("account_char.txt", [&](const string &str){
		Tokens tokens;
		StrSplit(tokens, str, ' ');		
		AddAccountToChar(tokens[0], tokens[1]);
		return true;
	}))
	{
		tea_perror("LogindCache::LoadAllAccountInfo read  txt file fail");
		return;
	}
	////ȥ��
	//m_storage->Remove("account_char.txt");
	//for (auto it:m_charListHD)
	//{
	//	SaveAccountCharInfo(it.first, it.second.guid);
	//}
}

//�����˺Ž�ɫ��Ϣ��Ӳ����
void LogindCache::SaveAccountCharInfo(const string& account,const string& guid)
{
	m_storage->Goto(g_Config.player_data_hdd_path);
	m_storage->AddContent("account_char.txt", account + ' ' + guid + '\n');
}

//�ص�ָ�����
bool LogindCache::HuidangPlayerInfos(const string player_guid, const string backupfilename)
{
	string path = g_Config.backup_hdd_path + "/" + backupfilename + "/";
	m_storage->Goto(path);

	OwnerDataSet* dataset = ObjMgr.FindDataSetByOwnerGuid(player_guid);	
	if(dataset && !dataset->GetAllData().empty())
	{
		//�����������
		vector<GuidObject*> vec;
		if(!m_storage->Load(player_guid, vec))
		{
			tea_pinfo("LogindCache::HuidangPlayerInfos load player %s data from %s failed!", player_guid.c_str(), path.c_str());
			return false;
		}
		vector<GuidObject*> need_free_vec;	//��Ҫ�ͷŵĶ���
		vector<GuidObject*> off_vec;		//��ҪΪ�������ϵĶ���
		vector<string> off_guid_vec;		//��ҪΪ�������ϵĶ����guid
		map<string, GuidObject*> data_map;	//ר��map�Բ�����Ҫ�Ƴ��Ķ���
		for (auto it:vec)
		{
			//ֻ�ϵ�һ���ظ�����
			if(data_map.find(it->guid()) != data_map.end())
			{
				need_free_vec.push_back(it);
				continue;
			}
			data_map[it->guid()] = it;

			GuidObject *obj = ObjMgr.Get(it->guid());
			if(obj)
			{
				obj->SetBinlogMaxSize(SyncEventRecorder::MAX_BINLOG_SIZE_UNLIME);
				uint32 len = obj->length_uint32() > it->length_uint32() ? obj->length_uint32() : it->length_uint32();
				for (uint32 i = 0; i < len; i++)
				{
					if(obj->GetUInt32(i) != it->GetUInt32(i))
					{
						obj->SetUInt32(i, it->GetUInt32(i));
					}
				}
				len = obj->length_str() > it->length_str() ? obj->length_str() : it->length_str();
				for (uint32 i = 0; i < len; i++)
				{
					if(obj->GetStr(i) != it->GetStr(i))
					{
						obj->SetStr(i, it->GetStr(i));
					}
				}
				obj->SetBinlogMaxSize(SyncEventRecorder::MAX_BINLOG_SIZE_2);
				need_free_vec.push_back(it);
			}
			else
			{
				off_vec.push_back(it);
				off_guid_vec.push_back(it->guid());
			}
		}
		//�Ƴ������ڵ� begin
		set<string> all_data;
		for (auto it:dataset->GetAllData())
		{
			all_data.insert(it);
		}
		for(auto it: all_data)
		{
			if(data_map.find(it) == data_map.end())
			{
				ObjMgr.CallRemoveObject(it);
			}
		}
		//�Ƴ������ڵ� end
		//��Ҫ��ӵĶ���
		if(!off_vec.empty())
		{
			ObjMgr.CallPutsObject(player_guid, off_vec, [off_guid_vec](bool b){
				//��binlog��ӵ���߹�����Ūһ��
				for (auto it:off_guid_vec)
				{
					//todo jzy  ��һ�䣬��Ϊ�˺�datad�汾�����ݵ�����
					ObjMgr.CallAddWatch(it, nullptr, false);
					ObjMgr.InsertObjOwner(it);
				}
			});
		}
		//��Ҫ�ͷŵĶ���
		for (auto it:need_free_vec)
		{
			safe_delete(it);
		}
	}
	else
	{
		//������ݲ�����,ֱ�ӿ����ͺ�
		string src = path + player_guid + BINLOG_EXT_NAME;
		string dst = g_Config.player_data_hdd_path + "/" + player_guid + BINLOG_EXT_NAME;
		m_storage->CopyAFile(src, dst);
	}

	return true;
}

//��ȡ�����������
bool LogindCache::LoadGlobalValue()
{
	vector<GuidObject*> vec;
	return LoadDataSet(GLOBAL_VALUE_OWNER_STRING, vec);
}

//��ȡ���ű�������
bool LogindCache::LoadFractionValue()
{
	vector<GuidObject*> vec;
	if (!LoadDataSet(FACTION_BINLOG_OWNER_STRING, vec))
		return false;
	
	vector<string> guid_vec;
	for (auto it : vec) {
		guid_vec.push_back(it->guid());
	}

	ObjMgr.CallPutsObject(FACTION_BINLOG_OWNER_STRING, vec, [guid_vec](bool) {
		for (auto it : guid_vec) {
			ObjMgr.InsertObjOwner(it);
		}
	});

	return true;
}

//��ȡ��������
bool LogindCache::LoadFractionData()
{
	vector<GuidObject*> vec;
	if (!LoadDataSet(FACTION_DATA_OWNER_STRING, vec))
		return false;

	vector<string> guid_vec;
	for (auto it : vec) {
		guid_vec.push_back(it->guid());
	}

	ObjMgr.CallPutsObject(FACTION_DATA_OWNER_STRING, vec, [guid_vec](bool) {
		for (auto it : guid_vec) {
			ObjMgr.InsertObjOwner(it);
		}
	});

	return true;
}
