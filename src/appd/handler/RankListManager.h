#ifndef _RANK_LIST_MANAGER_H_
#define _RANK_LIST_MANAGER_H_
#include "appd_app.h"

class RankListManager;
class PlayerBase;
namespace core_obj{
class SyncEventRecorder;
}

//������������������
#define MAX_RANK_LIST_POOL_COUNT 5000
//ÿ���������ı�־λ���� 8 * 32
#define MAX_RAMK_LIST_POOL_MASK_LEN 8
//��������������±�
#define RANK_LIST_POLL_INT_FIELD_COUNT 0
//����ر�־λ��ʼ�±�
#define RANK_LIST_POLL_INT_FIELD_MASK_START 1

//����������а��±�
enum ERankInfoFields
{
	//��ʱû�����±�

	//���а���binlog��ʼ�±꣬ÿ�����ε�binlogռ��λ��int_str, str_str����
	RANK_INFO_STRING_FIELD_START = BINLOG_STRING_FIELD_OWNER + 1,	
};

//���а������
//��ʹ�ü̳У�������
class RankListTaskPool
{
public:
	RankListTaskPool()
	{
		//�������binlog��ֵ������
		ASSERT(AppdApp::g_app->m_rank_info_rask_pool);
		m_obj = AppdApp::g_app->m_rank_info_rask_pool;
	}
	~RankListTaskPool(){m_obj = NULL;}
public:
	//Ŀǰ�ж�������
	int GetCount(){return m_obj->GetInt32(RANK_LIST_POLL_INT_FIELD_COUNT);}
	//ĳλ���ϵ�����Ĺ���guid
	const string &GetTaskGuid(int index){return m_obj->GetStr(BINLOG_STRING_FIELD_OWNER + index + 1);}
	//����һ������
	void InsertTask(const string &guid, ERankTypes type);
	//��������
	void Clear();
	//ĳλ�����Ƿ���ĳ����
	bool HasTask(int index, ERankTypes type)
	{
		return m_obj->GetBit(RANK_LIST_POLL_INT_FIELD_MASK_START + index * MAX_RAMK_LIST_POOL_MASK_LEN, type);
	}
private:
	BinLogObject *m_obj;			//�����binlog
	map<string, int> m_guid_index;	//���������
};

//���а��Ӷ���id��һλ�ͺ��ˣ���ʵû�ã���Լ����
#define RANK_LIST_OBJECT_CURRENT_GUID "r"
//���а���binlog��ÿ���������а���ĳһ������λ����ϸ��Ϣ
class RankListCurrentObj : public BinLogObject
{
public:
	RankListCurrentObj():BinLogObject(core_obj::SYNC_NONE){}
	virtual ~RankListCurrentObj(){}
protected:
	//�Ա���������
	template <class T>
	int CompareNumber(T p1, T p2)
	{
		if(p1 > p2)
			return 1;
		if(p1 < p2)
			return -1;
		return 0;
	}

public:
	//�������������е����඼������new����
	static RankListCurrentObj *Factoy(ERankTypes type);
	//����һ����Ƚϣ�����ͬ������
	virtual int Compare(RankListCurrentObj *) = 0;
	//��ϸ��Ϣ��ֵ
	virtual bool SetData(BinLogObject *binlog) = 0;
	//������������������
	virtual ERankTypes GetType() = 0;
	//�Ƿ���Դ����а��������(����Ϊ�գ�Ĭ�ϲ�����)
	virtual bool LeaveRankList(){return GetCurrentPlayerName().empty();}
	// ����
	void encode(ByteArray& bytes) {
		// ��дint
		bytes.writeShort(this->length_uint32());
		for (uint32 value : this->uint32_values_) {
			bytes.writeUnsignedInt(value);
		}
		// ��дstring
		bytes.writeShort(this->length_str());
		for (string str : this->str_values_) {
			bytes.writeUTF(str);
		}
	}
	//��ʼ��
	void Init(const string &guid = "", BinLogObject *binlog = nullptr);
	//����
	int GetRanking(){return GetInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_RANKING) - 1;}
	void SetRanking(int v){SetInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_RANKING, v + 1);}

	//��������Ϣ�Ĺؼ�guid
	const string &GetCurrentGuid(){return GetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID);}
	void SetCurrentGuid(const string & str){SetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID, str);}

	//��������Ϣ����ҵ�guid
	const string &GetCurrentPlayerGuid(){return GetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID);}
	void SetCurrentPlayerGuid(const string & str){SetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID, str);}

	//��������Ϣ�е������
	const string &GetCurrentPlayerName(){return GetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_NAME);}
	void SetCurrentPlayerName(const string & str){SetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_NAME, str);}

	//��������Ϣ�еİ�����
	const string &GetCurrentPlayerFaction(){return GetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_FACTION_NAME);}
	void SetCurrentPlayerFaction(const string & str){SetStr(RANK_LIST_CURRENT_OBJ_STR_FIELD_FACTION_NAME, str);}

	//�����а���Ϣ�����ҪӲ���߳�
	bool IsDelete(){return m_delete;}

	//��������Ϣ����ҵ��Ա�
	uint8 GetCurrentPlayerGender(){return GetByte(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE, 0);}
	void SetCurrentPlayerGender(uint8 v){SetByte(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE, 0, v);}
	
	//��������Ϣ����ҵĳƺ�
	uint32 GetCurrentPlayerTitle(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_TITLE);}
	void SetCurrentPlayerTitle(uint32 v){SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_TITLE, v);}

	//���а��е����
	uint32 GetCurrentPlayerShow(const int &id){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW+id);}
	void SetCurrentPlayerShow(const int &id,const uint32 &v){SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW+id,v);}

	//vip
	uint8 GetCurrentPlayerVip(){return GetByte(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE, 2);}
	void SetCurrentPlayerVip(uint8 v){SetByte(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE, 2, v);}
	//���õ�����
	void SetCurrentPlayerLike(uint32 v){SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LIKE, v);}

	//���id
	uint32 GetCurrentPlayerWing(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_WING);}
	void SetCurrentPlayerWing(uint32 v){SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_WING, v);}

private:
	//�Ƿ���Դ����а�����ˣ�����Ƚ����⣬�����Ա�����Ӳ������
	bool m_delete;
};

//�ܶ�����
//���ֻ���ڴ���ģ�ȷʵ�е�ӵ�
//���������Ҫ�����ݿ⣬д����������
//��Χ��Ҫ���ŵ�ʱ�򣬿�ͨ����ά�����������ݣ���
//�Ϸ��Ժ󣬵�¼���ᷢ�Ϸ������а������
class RankListManager
{
public:
	RankListManager();
	~RankListManager();

	//���а����ݣ����һ�������й���ʹ��
	RankListCurrentObj *m_data[MAX_RANK_TYPE][RANK_LIST_MAX_VALUES + 1];
	UpdateMask m_mask;
private:
	//�Ե����а���Ϣ
	void SwitchRankInfo(ERankTypes type, int index, RankListCurrentObj *obj);
private:
	//��ȡĳ���а�ĳ�����ε���guid
	const string &GetRankGuid(ERankTypes type, int rank)
	{
		return m_data[type][rank]->GetCurrentGuid();
	}
	//��ȡ������������Ӧ������������а������±�
	inline int GetRankListInfoIntIndex(int type, int rank)
	{
		return RANK_INFO_STRING_FIELD_START + type * RANK_LIST_MAX_VALUES * 2 + rank * 2;
	}
	//��ȡ������������Ӧ������������а��ַ����±�
	inline int GetRankListInfoStrIndex(int type, int rank)
	{
		return RANK_INFO_STRING_FIELD_START + type * RANK_LIST_MAX_VALUES * 2 + rank * 2 + 1;
	}
	//�ѵ�ǰ����ͬ��������������а�
	void SyncData();
	//��ʼ����ԵĽ�������
	void Sort(ERankTypes type);
	//�������а�����
	bool MakeBinlogData(const string &guid, ERankTypes type);
	//��ȡ���а�ĳ��λ�õ�binlog
	inline RankListCurrentObj *GetRankListData(int type, uint32 rank)
	{
		ASSERT(type < MAX_RANK_TYPE);
		RankListCurrentObj *obj = m_data[type][rank];
		ASSERT(obj->GetType() == type);
		ASSERT(obj->GetRanking() == rank);
		return obj;
	}
	//�������а�ĳ��λ�õ�binlog
	inline void SetRankListData(int type, uint32 rank, RankListCurrentObj *obj)
	{
		ASSERT(type < MAX_RANK_TYPE);
		ASSERT(obj->GetType() == type);
		ASSERT(obj->GetRanking() == rank);
		m_data[type][rank] = obj;
	}
	//����ĳ�����ĳ���а����������ڵ�����
	int FindPlayerRanking(int type, const string &guid);

	uint32 GetRankingCount(int type);
public:
	//��ʼ�����а���Ϣ
	void InitRankInfo();
	//��ʼ�����а������
	void InitTaskPool();
	// �������а���Ϣ
	void UpdateRankList();

	vector<string> GetRankGuidList(ERankTypes type);
	string GetRankName(ERankTypes type, uint32 level);
	bool HasRankGuid(ERankTypes type,string &guid,int &rank);
	void UpdateRankLike(int type,const string &guid,uint32 num);
	//��������
	void Update(uint32 diff);
	//����һ������
	void InsertTask(const string &guid, ERankTypes type);
	//���ĳ���а�
	void ClearRankList(int type);
	//д��ѯ��
	int WriteQueryByteArray(core_obj::ByteArray &bytes, const string &guid, uint32 call_back_id, uint8 rank_list_type, uint16 start_index, uint16 end_index);
	//�Ϸ��Ժ�Ҫ�뱾���ϲ������а�
	void MergeResort(const string &data, const string &str_data);
	//��ѯĳ�����а�ĳ��λ�õ���GUID
	RankListCurrentObj *FindRankDataByType(int type, uint32 rank);
	//��ȡս�����а����guid
	string GetForceRankPlayerGuid(uint32 rank, uint32 force = 0);
	//��ȡ�ȼ����а����guid
	string GetLevelRankPlayerGuid(uint32 rank, uint32 level = 0);

	

public:
	//����±귢���仯
	void OnAfterUpdate(core_obj::SyncEventRecorder *data,int flags,UpdateMask& mask,UpdateMask& str_mask);
	//������а�
	void DoQaClearRankInfo();

private:
	RankListTaskPool *m_task_pool;			//�����
	TimeTrackerSmall m_timer;				//��ʱ��
	bool m_init_ok;							//��ʼ�����

};

#endif
