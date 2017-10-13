#ifndef _LOGIND_CACHE_H_
#define _LOGIND_CACHE_H_

#include "logind_app.h"
#include <svrcore/server/Storage.h>
#include <comm/common_stl.h>
#include <object/BinLogObject.h>
#include <object/GuidManager.h>


//��¼���˺Ž�ɫ��Ʒ�����ݵĻ���
class LogindCache
{
	typedef map<string, string> CharNameMap;
	typedef map<string, account_table*> AccountMap;
public:
	LogindCache();
	virtual ~LogindCache();
public:
	//��ȡ�˺���Ϣ
	account_table *GetAccount(const string &account);
	//����һ���˺���Ϣ
	void AddAccount(account_table *info);
	//��ȡ�˺��½�ɫ�б�
	void GetCharList(const string &account,vector<char_create_info>&);
	//ͨ��������ֻ�ȡguid
	const string &FindGuidByCharName(const string &name);
	//���һ���������
	void AddCharName(const string &guid, const string &name);
	//��ȡ���еĽ�ɫ��
	void LoadAllCharName();
	
	//�����ʺ����ɫ�Ķ�Ӧ��
	void AddAccountToChar(const string& account,char_create_info& info);
	void AddAccountToChar(const string& account,string guid);

	//����Ϸ���־�ļ�
	void SaveFileToMergeServer(const string& file_name, const string& now_time);

	//�ͷŵǳ�����һ���
	void FreeLogoutPlayer(bool immediately = false);
	//���һ���ǳ���һ���
	void AddLogoutPlayer(const string &guid);
	//ɾ��һ���ǳ���һ���
	void DelLogoutPlayer(const string &guid);
public:
	//ֱ�ӱ������ݵ�Ӳ��,�����ļ�
	bool SaveData(const string &file_name, const string &content);
	bool SaveMailData(const string &file_name, const string &content);
	//ͨ�����guid��ȡϵ�л��ַ���
	string GetPlayerDataStr(const string &guid);
	//ͨ�����guid��ȡ��������ʼ�ϵ�л��ַ���
	string GetPlayerMailDataStr(const string &guid);
	//����Զ���������
	void Update(logind_player *player);
	//��ȡ��Ҷ���
	bool LoadPlayer(const string &guid, logind_player **player, vector<GuidObject*> &vec);
	//������Ҷ���
	void SavePlayerData(const string &guid);
	//������Ҷ���
	void SavePlayerData(const string &guid, vector<GuidObject*> &vec, uint32 level);
	//�����������
	void Backup(const string &gm_path = "");
	//�����б仯����ҵ����ݿ�
	void SaveChangePlayerToDB(bool is_merge = false);
	//�ӱ���Ӳ�̰������˺���Ϣ������
	void LoadAllAccountInfo();
	//�����˺���Ϣ��Ӳ����
	void SaveAccountInfo(account_table *info);
	//�ӱ���Ӳ�̰������˺Ž�ɫ��Ϣ������
	void LoadAllAccountCharInfo();
	//�����˺Ž�ɫ��Ϣ��Ӳ����
	void SaveAccountCharInfo(const string& account,const string& guid);
	//�ص�ָ�����
	bool HuidangPlayerInfos(const string player_guid, const string backupfilename);
	//��ȡ�����������
	bool LoadGlobalValue();
	//��ȡ���ɱ�������
	bool LoadFractionValue();
	bool LoadFractionData();
protected:
	//��ȡ���󼯺�,�ǵ��ͷ��ڴ����
	bool LoadDataSet(const string &guid, vector<GuidObject*> &vec);
	//������������л����ַ���
	string PlayerDataToString(const string &guid, vector<GuidObject*> &vec);
private:
	core_obj::Storage			*m_storage;				//����Ӳ�̻���
	CharNameMap					m_charNameMaps;			//����������ȫ����Сд�Ӱ��,������ʱ��ǵ�ҲҪСд�Ӱ��
	AccountMap					m_accountMaps;			//�����˺�
	std::map<string,char_create_info>		m_charListHD;			//����Ӳ�̻���--��ɫ�б�

	std::map<string,time_t>		m_logoutChar;			//�Ѿ��ǳ��Ļ��������Ϣ
};

#endif


