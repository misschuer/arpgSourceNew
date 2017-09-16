#ifndef _LOGIND_MONGODB_H_
#define _LOGIND_MONGODB_H_

#include <db_wrap/mongo_db.h>

class LogindObjectManager;
class LogindConfig;
class PlayerBase;

class LogindMongoDB:public MongoDB
{
	friend class GuidManager;
public:
	LogindMongoDB(LogindObjectManager *mgr,log_holder_t *log);
	virtual ~LogindMongoDB();

	void SetLocaldb(bool b){is_localdb = b;}
	//////////////////////////////////////////////////////////////////////////
	//����һ������
	void SaveBinlog(BinLogObject *obj, bool fsync = false);
	//����һ������
	void SaveDataset(const string &guid, bool fsync);
	/////////////////////////////////////////////////////////////////////////
	//�������
	bool Load_GlobalValue();
	//////////////////////////////////////////////////////////////////////////
	//�˻���
	//�������˻���LOAD���ڴ�
	//����һ���µ��˻�
	account_table *UpsertAccount(string account,string pid, string sid,string uid, int is_FCM, string ip, string platdata = "",int gmlevel = -1);		

	//////////////////////////////////////////////////////////////////////////
	//��ɫ��
	//��ȡ����Ҷ���
	void LoadPlayer(const string& account, const string &player_guid, vector<GuidObject*> &vec, std::function<void(bool,vector<GuidObject*>&)> fun);
	//��ͬ���ķ�ʽloadȡ�������,������web�ӿڷ�ʽ����,���ӿڲ����������ط����ã������򲻵��ѣ���Ҫlinbcǩ�ֻ�Ѻ����ʹ�á�
	bool LoadPlayer(const string& account, const string &player_guid, vector<GuidObject*> &vec);

	//���ݽ�ɫ����ȡ�����guid
	string FindGuidByName(string name, bool &has_err);
	//�����ɫ����
	void InsertGuidByName(string guid,string name);

	typedef std::function<void(bool,vector<char_create_info>&)> CharListDelegate;
	//�����ʺŻ�ȡ��ɫ�б�
	void GetCharsList(string account, CharListDelegate  func);

	//������ɫ
	void AddChars(string guid, string account, string name, string ip, string data, string data_str);	
	//���½�ɫ����״̬
	//���guidΪ��,�����ȫ��
	void UpdateCharsOnline(string guid, uint8 status);
	//ɾ��
	void DelChars(string guid);
	//���ݷ�����load��ɫ��
	void LoadNameFromServer(string server_name);

	//�������GUID��ȡaccount
	string FindAccountByGuid(string guid);

	//����������������ô����ñ�
	void ReloadSeverNameByConfig();

	//��ȡ�Ϸ�״̬
	bool LoadMergeServerStatus(int32 opt_status,int32 merge_status,std::function<void(merge_info*)> cb);
	//���úϷ�״̬
	void UpdateMergeServerStatus(int32 new_status,int32 merge_status,string merge_server);
	//����server_info�Ϸ�״̬
	void UpdateSeverInfoMergeStatus();
	//���汾�����GUID
	void SaveServerMaxGuid();
	//��ȡ���������GUID
	void GetServerMaxGuid(string server_name,uint32 &player_max);

	//���ݷ����������·������б�
	bool UpdateServerListInfo(string server_name);

	//���ݷ�������load���GUID
	uint32 LoadMaxGuidFromServerName(string server_name, EObjectTypePrefix type);
	
	//��ȡ����ʱ��
	uint32 LoadKaiFuShiJian();
	//���ÿ���ʱ��
	void UpdateKaiFuShiJian(uint32 open_time);
	//���úϷ����ձ�
	void UpdateMergeServerList(string server_name);
	//////////////////////////////////////////////////////////////////////////
	//��ȡ�ͻ��˰汾����
	void GetVersionsRequirements(std::function<void(uint32,const string&,const string&,uint32)>);
		
	void DbOperGameConfig(std::function<void(string,string)> fun);
	//////////////////////////////////////////////////////////////////////////
	//GM�����ֵ
	void SetGmRechargeNum(const char* account,uint32 amount, uint32 type);

	//�ж�����Ƿ����
	bool FindFriendByGuid(string guid, PlayerBase *player);

	//GM������·����
	void ServerUpdate(uint32 server_type);

	//��ȡ���а�����
	void LoadRankListInfo(string server_name, string &data, string &data_str);
	//ȫ���������������Ϣ
	void UpdatePlayerDBInfo(const string &guid);
	//����account��gm_level
	void UpdateAccountGMLevel(uint32 gm_level,string account,string server_name);

	//��ȡͳ������
	void LoadCounterInfo(string server_name, string &data, string &data_str);

	//ɾ��binlog
	void DeleteBinlog(const string &guid,const string &owner);
	//�������GUID��ȡaccount
	string GetAccountFromGuid(string str);
protected:
	//����һ������
	void SaveBinlogVec(vector<GuidObject*> vec, bool fsync = false);
	//�����������
	void SavePlayer(BinLogObject *player, bool fsync = false);
	//�����������
	void SavePlayerOtherInfo(BinLogObject *blobj, bool fsync = false);
	//�����������
	void SaveGlobalValue(BinLogObject *binlog);
	//ָ�����ݿⱣ��binlogobject
	void SaveBinlog(string data_name,BinLogObject *blobj, bool fsync = false);
	//ɾ��������Ϣ
	void DelFaction(const string &guid);
	//�Ƿ�ӵ����������
	bool is_localdb;									
private:
	void LoadMaxGuid(BinLogObject *binlog, const char *table_name, EObjectTypePrefix type);
	void LoadOtherMaxGuid(BinLogObject *binlog, EObjectTypePrefix type);
	void Load_GlobalValue(BinLogObject* binlog, const char *guid, bool load_db = true, std::function<void()> = nullptr);

	LogindObjectManager *m_obj_mgr;
	vector<string>				m_loaded_servername;	//�Ѿ�����������Ƶķ�����	
};


#endif // !_LOGIND_MONGODB_H_

