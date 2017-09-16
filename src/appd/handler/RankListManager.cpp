#include "RankListManager.h"
#include "appd_context.h"
#include "appd_object_manager.h"
#include <shared/log_handler.h>
#include <object/OprateResult.h>
/////////////////////////////////////////////////////////////////////////////////////////////////

void RankListCurrentObj::Init(const string &guid , BinLogObject *binlog)
{
    Reset();
    SetGuid(RANK_LIST_OBJECT_CURRENT_GUID);
    SetInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_TYPE, GetType());
    SetRanking(RANK_LIST_MAX_VALUES);		
    SetCurrentGuid(guid);

	if (binlog) {
		//�������ң�����Ҫ�����Ƿ���ɾ��
		if (GuidManager::GetPrefix(guid) == ObjectTypePlayer) {
			m_delete =  dynamic_cast<PlayerBase*>(binlog)->IsDelete();
		// ���ɽ�ɢ
		} else if (GuidManager::GetPrefix(guid) == ObjectTypeFaction) {
			m_delete = binlog->GetUInt32(FACTION_INT_FIELD_IS_DISSOLVED) == 1;
		}
	} else {
		// ��Ϊ�� ȴû��binlog ˵��������󱻻�����
		if (!guid.empty()) {
			m_delete = true;
		}
	}
}

//�������а���Ϣ
void AppdContext::Handle_Rank_List_Query(packet& pkt)
{
	uint32 call_back_id;
	uint8 rank_list_type;
	uint16 start_index;
	uint16 end_index;
	if(unpack_rank_list_query(&pkt, &call_back_id, &rank_list_type, &start_index, &end_index))
	{
		WriteAttackPacker(GetAccount(),GetGuid(),pkt.head->optcode,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	static ByteArray bytes;
	string guid = GetGuid();
	if (rank_list_type == RANK_TYPE_FACTION) {
		guid = GetFactionId();
	}
	int result = AppdApp::g_app->m_rank_list_mgr->WriteQueryByteArray(bytes, guid, call_back_id, rank_list_type, start_index, end_index);
	if(result != RANK_LIST_OPERATE_SUCCEED)
	{
		Call_Operation_Failed(OPERTE_TYPE_RANK_LIST, result);
		return;
	}
	bytes.position(0);
	packet *_pkt = external_protocol_new_packet(SMSG_RANK_LIST_QUERY_RESULT);
	packet_write(_pkt,(char*)bytes.cur_data(),bytes.bytesAvailable());
	update_packet_len(_pkt);
	SendPacket(*_pkt);
	external_protocol_free_packet(_pkt);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//RankListTaskPool

//����һ������
void RankListTaskPool::InsertTask(const string &guid, ERankTypes type)
{
	//������guidû���ֹ����Ǿ�����һ���µĸ���
	//������У��Ǿ���ԭ�ȵ�λ��
	//Ȼ���type��flag��һ��
	int index = -1;
	auto it = m_guid_index.find(guid);
	if(it == m_guid_index.end())
	{
		index = GetCount();
		m_obj->AddInt32(RANK_LIST_POLL_INT_FIELD_COUNT, 1);
		m_obj->SetStr(BINLOG_STRING_FIELD_OWNER + index + 1, guid);
		m_guid_index.insert(make_pair(guid, index));

	}
	else
	{
		index = it->second;
	}
	if(!m_obj->GetBit(RANK_LIST_POLL_INT_FIELD_MASK_START + index * MAX_RAMK_LIST_POOL_MASK_LEN, type))
		m_obj->SetBit(RANK_LIST_POLL_INT_FIELD_MASK_START + index * MAX_RAMK_LIST_POOL_MASK_LEN, type);
}

//��������
void RankListTaskPool::Clear()
{
	int max_index = GetCount();
	for (int i = 0; i < max_index; i++)
	{
		m_obj->SetStr(BINLOG_STRING_FIELD_OWNER + i + 1, "");
		for (int j = 0; j < MAX_RAMK_LIST_POOL_MASK_LEN; j++)
		{
			if(m_obj->GetInt32(RANK_LIST_POLL_INT_FIELD_MASK_START + i * MAX_RAMK_LIST_POOL_MASK_LEN + j) != 0)
				m_obj->SetInt32(RANK_LIST_POLL_INT_FIELD_MASK_START + i * MAX_RAMK_LIST_POOL_MASK_LEN + j, 0);
		}
	}
	m_obj->SetInt32(RANK_LIST_POLL_INT_FIELD_COUNT, 0);
	m_guid_index.clear();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//RankListManager

RankListManager::RankListManager():m_task_pool(0), m_timer(0), m_init_ok(false)
{
	memset(m_data, NULL, sizeof(m_data));
}

RankListManager::~RankListManager()
{
	safe_delete(m_task_pool);
	for (int i = 0; i < MAX_RANK_TYPE; i++)
	{
		for (int j = 0; j <= RANK_LIST_MAX_VALUES; j++)
		{
			safe_delete(m_data[i][j]);
		}
	}
}

//�Ϸ��Ժ�Ҫ�뱾���ϲ������а�
void RankListManager::MergeResort(const string &data, const string &str_data)
{
	BinLogObject *obj = new BinLogObject;
	obj->FromString(data, str_data);
	for (int i = 0; i < MAX_RANK_TYPE; i++)
	{
		for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
		{
			string data = AppdApp::g_app->GetRankInfoData(GetRankListInfoIntIndex(i, j));
			string data_str = AppdApp::g_app->GetRankInfoData(GetRankListInfoStrIndex(i, j));
			RankListCurrentObj *binlog = GetRankListData(i, RANK_LIST_MAX_VALUES);
			binlog->Reset();
			binlog->FromString(data, data_str);
			binlog->SetRanking(RANK_LIST_MAX_VALUES);//Ҫ�ȸ�һ�£�������ȡ�����ж���
			if(FindPlayerRanking(i, binlog->GetCurrentPlayerGuid()) >= 0)
				continue;
			Sort(binlog->GetType());
		}
	}
}

//��ѯĳ�����а�ĳ��λ�õ���GUID
RankListCurrentObj *RankListManager::FindRankDataByType(int type, uint32 rank)
{
	RankListCurrentObj *obj = GetRankListData(type, rank);
	return obj;
}

//��ʼ�����а���Ϣ
void RankListManager::InitRankInfo()
{
	//���������������ݶ�����
	//���һ��һ��������binlog
	//����ÿ������Ԥ��һ����Ϊ�½�����Ĺ�����
	for (int i = 0; i < MAX_RANK_TYPE; i++)
	{
		ERankTypes type = (ERankTypes)i;
		for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
		{
			string data = AppdApp::g_app->GetRankInfoData(GetRankListInfoIntIndex(i, j));
			string data_str = AppdApp::g_app->GetRankInfoData(GetRankListInfoStrIndex(i, j));
			RankListCurrentObj *binlog = RankListCurrentObj::Factoy(type);
			if(!data.empty())
			{
				binlog->FromString(data, data_str);
			}
			else
			{
				binlog->Init();
				binlog->SetRanking(j);
			}
			SetRankListData(type, j, binlog);
		}
		//��ʱ����
		RankListCurrentObj *binlog = RankListCurrentObj::Factoy(type);
		binlog->SetRanking(RANK_LIST_MAX_VALUES);
		SetRankListData(type, RANK_LIST_MAX_VALUES, binlog);
	}
	m_init_ok = true;
}


void RankListManager::UpdateRankList() 
{
	for (int i = 0; i < MAX_RANK_TYPE; i++)
	{
		ERankTypes type = (ERankTypes)i;
		for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
		{
			RankListCurrentObj* binlog = GetRankListData(i, j);
			string guid = binlog->GetCurrentGuid();
			if(guid == "") {
				break;
			}
			BinLogObject *player = (BinLogObject*)ObjMgr.Get(guid);
			binlog->SetData(player);
		}
	}
}

vector<string> RankListManager::GetRankGuidList(ERankTypes type)
{
	vector<string> ary;
	for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
	{
		RankListCurrentObj* binlog = GetRankListData(type, j);
		string guid = binlog->GetCurrentGuid();
		if(guid != "") {
			ary.push_back(guid);
		}
	}
	return ary;
}

bool RankListManager::HasRankGuid(ERankTypes type,string &guid,int &rank)
{
	for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
	{
		RankListCurrentObj* binlog = GetRankListData(type, j);
		string pguid = binlog->GetCurrentGuid();
		if (pguid == guid)
		{
			rank = j;
			return true;
		}else if(pguid == "") {
			return false;
		}
	}
	return false;
}



void RankListManager::UpdateRankLike(int type,const string &guid,uint32 num)
{
	//TODO: 2017-05-25��
	if (type == RANK_TYPE_FACTION)//����������Ҫ�Ұ���
	{
		for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
		{

			RankListCurrentObj* binlog = GetRankListData(type, j);
			string pguid = binlog->GetStr(FACTION_STRING_FIELD_MANGER_GUID);
			if (pguid == guid)
			{
				binlog->SetCurrentPlayerLike(num);
				return;
			}
			if(pguid == "") {
				break;
			}
			
		}
	}else{
		for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
		{
			RankListCurrentObj* binlog = GetRankListData(type, j);
			string pguid = binlog->GetCurrentGuid();
			if (pguid == guid)
			{
				binlog->SetCurrentPlayerLike(num);
				return;
			}
			if(pguid == "") {
				break;
			}
		}
	}
	
}

//��ʼ�����а������
void RankListManager::InitTaskPool()
{
	m_task_pool = new RankListTaskPool;
}

//�ѵ�ǰ����ͬ��������������а�
void RankListManager::SyncData()
{
	for (int i = 0; i < MAX_RANK_TYPE; i++)
	{
		for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
		{
			//ֻȡ�б仯��
			if(!m_mask.GetBit(i * RANK_LIST_MAX_VALUES + j))
				continue;
			string data, data_str;
			GetRankListData(i, j)->ToString(data, data_str);
			AppdApp::g_app->SetRankInfoData(GetRankListInfoIntIndex(i, j), data);
			AppdApp::g_app->SetRankInfoData(GetRankListInfoStrIndex(i, j), data_str);
		}
	}
	m_mask.Clear();
}

void RankListManager::Update(uint32 diff)
{
	if(!m_init_ok)
		return;

	m_timer.Update(diff);
	if(!m_timer.Passed())
		return;
	m_timer.Reset(g_Config.rank_list_work_interval);
	if(m_task_pool->GetCount())
	{
		for (int i = 0; i < m_task_pool->GetCount(); i++)
		{
			for (int j = 0; j < MAX_RANK_TYPE; j++)
			{
				const string guid = m_task_pool->GetTaskGuid(i);
				ERankTypes t = ERankTypes(j);
				//��⵽������
				if(m_task_pool->HasTask(i, t))
				{
					//tea_pdebug("rank list resort , guid : %s, type : %u", guid.c_str(), t);
					//�Ȱ�����ȡ����
					//���ȡ����ʧ���ˣ���û�취������
					//���磬��@�Ա���
					if(!MakeBinlogData(guid, t))
						continue;
					Sort(t);
				}
			}
		}
		m_task_pool->Clear();
		SyncData();
	}
}

//�Ե����а���Ϣ
void RankListManager::SwitchRankInfo(ERankTypes type, int index, RankListCurrentObj *obj)
{
	RankListCurrentObj *temp = GetRankListData(type, index);
	ASSERT(temp != obj);
	temp->SetRanking(obj->GetRanking());
	SetRankListData(type, obj->GetRanking(), temp);
	if(temp->GetRanking() < RANK_LIST_MAX_VALUES)
		m_mask.SetBit(type * RANK_LIST_MAX_VALUES + obj->GetRanking());

	//tea_pdebug("SwitchRankInfo guid %s %u move to %u .", temp->GetCurrentGuid().c_str(), index, temp->GetRanking());
	//tea_pdebug("SwitchRankInfo guid %s %u move to %u .", obj->GetCurrentGuid().c_str(), obj->GetRanking(), index);

	obj->SetRanking(index);
	SetRankListData(type, index, obj);
	if(obj->GetRanking() < RANK_LIST_MAX_VALUES)
		m_mask.SetBit(type * RANK_LIST_MAX_VALUES + index);
}

//��ʼ����ԵĽ�������
void RankListManager::Sort(ERankTypes type)
{
	bool full = true;
	RankListCurrentObj *current_obj = GetRankListData(type, RANK_LIST_MAX_VALUES);
	//����һ���Լ�֮ǰ���ڵ�λ�ã����滻������
	//���֮ǰ���ڣ��������а�û��Ա���ǾͲ��뵽δ��Աǰ�����һ����
	for (int i = 0; i < RANK_LIST_MAX_VALUES; i++)
	{
		const string g = GetRankGuid(type, i);
		if(current_obj->GetCurrentGuid() == g)
		{
			SwitchRankInfo(type, i, current_obj);
			break;
		}
		if(g.empty())//������а�û��Ա
		{
			SwitchRankInfo(type, i, current_obj);//��������
			full = false;
			break;
		}
	}

	//�����ǲ����Ѿ����뿪�����а���
	if(current_obj->IsDelete() || current_obj->LeaveRankList())
	{
		for (int i = current_obj->GetRanking(); i < RANK_LIST_MAX_VALUES; i++)
		{
			//����Ų
			SwitchRankInfo(type, i + 1, current_obj);
		}
		current_obj->Init();
		return;
	}

	//�����ֿ��ܣ�һ�������ϱȽϣ�һ�������±Ƚ�
	if(!full																//���а�δ���������Ҽ������ˣ�һ�������ϱȽ� 
		|| current_obj->GetRanking() == RANK_LIST_MAX_VALUES				//�����а���δ�ҵ��Լ������ݣ���һ��Ҳ��Ҫ���Ž����
		|| current_obj->Compare(GetRankListData(type, RANK_LIST_MAX_VALUES)) > 0)	//���ߺ��Լ�ԭ�������ݱ������ӵ�
	{
		for (int i = current_obj->GetRanking(); i > 0; i--)
		{
			int next_i = i - 1;
			//��ǰһ���Ƚ�һ�£��������������൱���Ǿ�������
			if(current_obj->Compare(GetRankListData(type, next_i)) <= 0)
				break;

			//������������ǰŲ
			SwitchRankInfo(type, next_i, current_obj);
		}
	}
	else//�ҵ����������ˣ������ҵ����ο��ܵ���
	{
		for (int i = current_obj->GetRanking(); i < RANK_LIST_MAX_VALUES; i++)
		{
			int next_i = i + 1;
			//���Ѿ���ͷ�ˣ����Լ��������һ��
			if(next_i == RANK_LIST_MAX_VALUES)
				break;
			//����һ���Ƚ�һ�£�������ǿ�����൱���Ǿ�������
			if(current_obj->Compare(GetRankListData(type, next_i)) >= 0)
				break;
			//������������Ų
			SwitchRankInfo(type, next_i, current_obj);
		}
	}
}

//�������а�����
bool RankListManager::MakeBinlogData(const string &guid, ERankTypes type)
{
	//��Ԥ�����Ǹ�����
	RankListCurrentObj *current_obj = GetRankListData(type, RANK_LIST_MAX_VALUES);
	BinLogObject *binlog = dynamic_cast<BinLogObject*>(ObjMgr.Get(guid));
	if(!binlog) {
		tea_pwarn("RankListManager::MakeBinlogData, guid %s ,type %u not found.", guid.c_str(), type);
	}
	current_obj->Init(guid, binlog);

	return current_obj->SetData(binlog);
}

//���ĳ���а�
void RankListManager::ClearRankList(int type)
{
	for (int i = 0; i < RANK_LIST_MAX_VALUES; i++)
	{
		RankListCurrentObj *current_obj = GetRankListData(type, i);
		current_obj->Init();
		current_obj->SetRanking(i);
		m_mask.SetBit(type * RANK_LIST_MAX_VALUES + i);
	}
	SyncData();
}

//����������
void RankListManager::InsertTask(const string &guid, ERankTypes type)
{
	if(!m_init_ok)
		return;

	m_task_pool->InsertTask(guid, type);
}

//����ĳ�����ĳ���а����������ڵ�����
int RankListManager::FindPlayerRanking(int type, const string &guid)
{
	int rank = -1;
	for (int i = 0; i < RANK_LIST_MAX_VALUES; i++)
	{
		if(GetRankListData(type, i)->GetCurrentPlayerGuid() == guid)
		{
			rank = i + 1;
			break;
		}
	}
	return rank;
}

uint32 RankListManager::GetRankingCount(int type) {

	uint32 count = 0;
	for (int i = 0; i < RANK_LIST_MAX_VALUES; i++)
	{
		if(GetRankListData(type, i)->GetCurrentGuid() == "")
		{
			break;
		}
		count ++;
	}

	return count;
}

//д��ѯ��
int RankListManager::WriteQueryByteArray(ByteArray &bytes, const string &guid, uint32 call_back_id, uint8 rank_list_type, uint16 start_index, uint16 end_index)
{
	if(rank_list_type >= MAX_RANK_TYPE)
		return RANK_LIST_OPERATE_TYPE_ERROR;
	if(start_index > end_index || start_index > RANK_LIST_MAX_VALUES || end_index > RANK_LIST_MAX_VALUES || start_index < 1)
		return RANK_LIST_OPERATE_OUT_OF_RANGE;

	bytes.clear();
	//д�ص���
	bytes.writeUnsignedInt(call_back_id);
	//д���Լ�������
	bytes.writeInt(FindPlayerRanking(rank_list_type, guid));
	// ���а�����
	bytes.writeUnsignedInt(GetRankingCount(rank_list_type));
	// ����
	bytes.writeShort(end_index-start_index+1);
	//д���ѯ��������Ϣ
	for (int i = start_index - 1; i < end_index; i++)
	{
		//tea_pdebug("RankListManager::WriteQueryByteArray %u %u %u %u",rank_list_type,i, GetRankListData(rank_list_type,i)->GetUInt32(0),GetRankListData(rank_list_type, i)->GetUInt32(1));
		GetRankListData(rank_list_type,i)->encode(bytes);
	}

	return RANK_LIST_OPERATE_SUCCEED;
}

void RankListManager::OnAfterUpdate(core_obj::SyncEventRecorder *data,int flags,UpdateMask& mask,UpdateMask& str_mask)
{
	AppdContext *player = dynamic_cast<AppdContext*>(data);
	if(!player)
		return;
	if(player->GetStatus() != STATUS_LOGGEDIN)
		return;
	if(mask.GetBit(PLAYER_FIELD_FORCE)) {
		InsertTask(data->guid(), RANK_TYPE_POWER);
		// ����lua�ӿ� ս��������
		player->OnForceChanged();
	}
	if(mask.GetBit(PLAYER_FIELD_LEVEL)) {
		InsertTask(data->guid(),RANK_TYPE_LEVEL);
		// ����lua�ӿ� �ȼ�������
		player->OnLevelChanged();
	}
	if (mask.GetBit(PLAYER_FIELD_ONLINE_TIME))
		InsertTask(data->guid(),RANK_TYPE_ONLINE_TIME);
	if (mask.GetBit(PLAYER_FIELD_DIVINE_FORCE))
		InsertTask(data->guid(),RANK_TYPE_DIVINE);
	if (mask.GetBit(PLAYER_FIELD_MOUNT_FORCE))
		InsertTask(data->guid(),RANK_TYPE_MOUNT);
	// ���а�ĵ��޴�������
	if (mask.GetBit(PLAYER_FIELD_RANK_LIKE)){
		uint32 likenum = player->GetUInt32(PLAYER_FIELD_RANK_LIKE);
		UpdateRankLike(RANK_TYPE_POWER,data->guid(),likenum);
		UpdateRankLike(RANK_TYPE_LEVEL,data->guid(),likenum);
		UpdateRankLike(RANK_TYPE_MONEY,data->guid(),likenum);
		UpdateRankLike(RANK_TYPE_FACTION,data->guid(),likenum);
		UpdateRankLike(RANK_TYPE_SINGLE_PVP,data->guid(),likenum);
		UpdateRankLike(RANK_TYPE_DIVINE,data->guid(),likenum);
		UpdateRankLike(RANK_TYPE_MOUNT,data->guid(),likenum);
		UpdateRankLike(RANK_TYPE_WINGS,data->guid(),likenum);
	}
}

//������а�
void RankListManager::DoQaClearRankInfo()
{
	for (int i = 0; i < MAX_RANK_TYPE; i++)
	{
		for (int j = 0; j < RANK_LIST_MAX_VALUES; j++)
		{
			AppdApp::g_app->SetRankInfoData(GetRankListInfoIntIndex(i, j), "");
			AppdApp::g_app->SetRankInfoData(GetRankListInfoStrIndex(i, j), "");
		}
	}
	InitRankInfo();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//���е����а��������
//ս����
class RankListForceObj : public RankListCurrentObj
{
public:
	ERankTypes GetType()
	{
		return RANK_TYPE_POWER;
	}

	int Compare(RankListCurrentObj *obj)
	{
		RankListForceObj *f_obj = dynamic_cast<RankListForceObj*>(obj);
		ASSERT(f_obj);
		return CompareNumber(this->GetForce(), f_obj->GetForce());
	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog)
			return false;
		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerFaction(player->GetFactionName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerShow(0,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,1));
		SetCurrentPlayerShow(1,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,0));
		SetCurrentPlayerVip(player->GetVIP());
		SetCurrentPlayerLike(player->GetUInt32(PLAYER_FIELD_RANK_LIKE));
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetForce(player->GetForce());

		return true;
	}
public:
	double GetForce(){return GetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE);}
	void SetForce(double v){return SetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE, v);}
};

//�ȼ�
class RankListLevelObj : public RankListCurrentObj
{
public:
	ERankTypes GetType()
	{
		return RANK_TYPE_LEVEL;
	}

	int Compare(RankListCurrentObj *obj)
	{
		RankListLevelObj *f_obj = dynamic_cast<RankListLevelObj*>(obj);
		ASSERT(f_obj);
		return CompareNumber(this->GetLevel(), f_obj->GetLevel());
	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog)
			return false;
		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerFaction(player->GetFactionName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerShow(0,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,1));
		SetCurrentPlayerShow(1,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,0));
		SetCurrentPlayerVip(player->GetVIP());
		SetCurrentPlayerLike(player->GetUInt32(PLAYER_FIELD_RANK_LIKE));
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetLevel(player->GetLevel());
		
		return true;
	}
public:
	uint32 GetLevel(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL);}
	void SetLevel(uint32 v){return SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL, v);}
};

//ͭǮ
class RankListMoneyObj : public RankListCurrentObj
{
public:
	ERankTypes GetType()
	{
		return RANK_TYPE_MONEY;
	}

	int Compare(RankListCurrentObj *obj)
	{
		RankListMoneyObj *f_obj = dynamic_cast<RankListMoneyObj*>(obj);
		ASSERT(f_obj);
		return CompareNumber(this->GetMoney(), f_obj->GetMoney());
	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog)
			return false;
		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerFaction(player->GetFactionName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerShow(0,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,1));
		SetCurrentPlayerShow(1,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,0));
		SetCurrentPlayerVip(player->GetVIP());
		SetCurrentPlayerLike(player->GetUInt32(PLAYER_FIELD_RANK_LIKE));
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetMoney(player->GetMoney(MONEY_TYPE_SILVER));
		
		return true;
	}
public:
	double GetMoney(){return GetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_MONEY);}
	void SetMoney(double v){return SetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_MONEY, v);}
};

//����ʱ��
class RankListOnlineTimeObj : public RankListCurrentObj
{
public:
	ERankTypes GetType()
	{
		return RANK_TYPE_ONLINE_TIME;
	}

	int Compare(RankListCurrentObj *obj)
	{
		RankListOnlineTimeObj *f_obj = dynamic_cast<RankListOnlineTimeObj*>(obj);
		ASSERT(f_obj);
		return CompareNumber(this->GetOnlineTime(), f_obj->GetOnlineTime());
	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog)
			return false;
		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerFaction(player->GetFactionName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetOnlineTime(player->GetOnlineTime());

		return true;
	}
public:
	uint32 GetOnlineTime(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_ONLINE_TIME);}
	void SetOnlineTime(uint32 v){return SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_ONLINE_TIME, v);}
};

//����������
class RankListTrialObj : public RankListCurrentObj
{
public:
	ERankTypes GetType()
	{
		return RANK_TYPE_TRIAL;
	}

	int Compare(RankListCurrentObj *obj)
	{
		RankListTrialObj *f_obj = dynamic_cast<RankListTrialObj*>(obj);
		ASSERT(f_obj);
		return CompareNumber(this->GetLayers(), f_obj->GetLayers());
	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog)
			return false;
		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetLayers(player->GetTrialLayers());

		return true;
	}
public:
	uint32 GetLayers(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_TRIAL);}
	void SetLayers(uint32 v){return SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_TRIAL, v);}
};
//������а�
class RankListDivineObj: public RankListCurrentObj
{
public:
	ERankTypes GetType()
	{
		return RANK_TYPE_DIVINE;
	}

	int Compare(RankListCurrentObj *obj)
	{
		RankListDivineObj *f_obj = dynamic_cast<RankListDivineObj*>(obj);
		ASSERT(f_obj);
		return CompareNumber(this->GetDivineForce(), f_obj->GetDivineForce());
	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog)
			return false;
		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerShow(0,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,1));
		SetCurrentPlayerShow(1,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,0));
		SetCurrentPlayerVip(player->GetVIP());
		SetCurrentPlayerLike(player->GetUInt32(PLAYER_FIELD_RANK_LIKE));
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetDivineForce(player->GetUInt32(PLAYER_FIELD_DIVINE_FORCE));
		SetDivineNum(player->GetUInt32(PLAYER_FIELD_DIVINE_NUM));

		return true;
	}
public:
	double GetDivineForce(){return GetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE);}
	void SetDivineForce(double v){return SetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE, v);}

	uint8 GetDivineNum(){return GetByte(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE,2);}
	void SetDivineNum(uint8 v){return SetByte(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE,2, v);}
};

//�������а�
class RankListMonutObj: public RankListCurrentObj{
public:
	ERankTypes GetType()
	{
		return RANK_TYPE_MOUNT;
	}

	int Compare(RankListCurrentObj *obj)
	{
		RankListMonutObj *f_obj = dynamic_cast<RankListMonutObj*>(obj);
		ASSERT(f_obj);
		return CompareNumber(this->GetMountForce(), f_obj->GetMountForce());
	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog)
			return false;
		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerShow(0,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,1));
		SetCurrentPlayerShow(1,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,0));
		SetCurrentPlayerVip(player->GetVIP());
		SetCurrentPlayerLike(player->GetUInt32(PLAYER_FIELD_RANK_LIKE));
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetMountForce(player->GetByte(PLAYER_INT_FIELD_MOUNT_LEVEL, 0) * 100 + player->GetByte(PLAYER_INT_FIELD_MOUNT_LEVEL, 1));
		SetMountInfo(player->GetUInt32(PLAYER_INT_FIELD_MOUNT_LEVEL));

		return true;
	}
public:
	double GetMountForce(){return GetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE);}
	void SetMountForce(double v){return SetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE, v);}

	void SetMountInfo(uint32 v){return SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE2, v);}
};

//�������а�
class RankListFactionObj : public RankListCurrentObj{
public :
	ERankTypes GetType()
	{
		return RANK_TYPE_FACTION;
	}

public :
	int Compare(RankListCurrentObj *obj)
	{
		RankListFactionObj *f_obj = dynamic_cast<RankListFactionObj*>(obj);
		ASSERT(f_obj);
		int ss = CompareNumber(this->GetFactionForce(), f_obj->GetFactionForce());
		return ss;
		
	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog) {
			// ���ɽ�ɢ�Ƚ����� ��ΪҪ�°� ����Ҫ����true
			return true;
		}
		SetFactionLev(binlog->GetUInt32(FACTION_INT_FIELD_LEVEL));
		SetCurrentPlayerName(binlog->GetStr(FACTION_STRING_FIELD_MANGER_NAME));
		SetCurrentPlayerGuid(binlog->GetGuid());
		SetCurrentPlayerFaction(binlog->GetName());
		SetFactionActive(binlog->GetUInt32(FACTION_INT_FIELD_ACTIVITY));
		SetFactionForce(binlog->GetDouble(FACTION_INT_FIELD_TOTAL_FORCE));
		SetIcon(binlog->GetByte(FACTION_INT_FIELD_FLAGS_ID,0));

		SetCurrentPlayerShow(0,binlog->GetUInt32(FACTION_INT_FIELD_MANGER_COAT));
		SetCurrentPlayerShow(1,binlog->GetUInt32(FACTION_INT_FIELD_MANGER_WEAPON));
		SetCurrentPlayerVip(binlog->GetUInt32(FACTION_INT_FIELD_MANGER_VIP));
		SetCurrentPlayerGender(binlog->GetUInt32(FACTION_INT_FIELD_MANGER_GENDER));
		tea_pdebug("RankListFactionObj::SetData gender %d",binlog->GetUInt32(FACTION_INT_FIELD_MANGER_GENDER));
		SetCurrentPlayerTitle(binlog->GetUInt32(FACTION_INT_FIELD_MANGER_TITLE));
		SetCurrentPlayerLike(binlog->GetUInt32(FACTION_INT_FIELD_MANGER_LIKE));
		SetCurrentPlayerWing(binlog->GetUInt32(FACTION_INT_FIELD_MANGER_WING));

		return true;
	}
public:
	uint32 GetFactionLev(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL);}
	void SetFactionLev(uint32 v){SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL, v);}

	void SetIcon(uint16 t){SetUInt16(RANK_LIST_INT_FIELD_FACTION_BYTE,0,t);}
	uint16 GetIcon(){return GetUInt16(RANK_LIST_INT_FIELD_FACTION_BYTE,0);}

	uint32 GetFactionActive(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE2);}
	void SetFactionActive(uint32 v){SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE2, v);}

	double GetFactionForce(){return GetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE);}
	void SetFactionForce(double v){SetDouble(RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE, v);}
};


//����PVP���а�
class RankListSinglePVPObj : public RankListCurrentObj{
public :
	ERankTypes GetType()
	{
		return RANK_TYPE_SINGLE_PVP;
	}

public :
	int Compare(RankListCurrentObj *obj)
	{
		RankListSinglePVPObj *f_obj = dynamic_cast<RankListSinglePVPObj*>(obj);
		ASSERT(f_obj);
		int ss = CompareNumber(this->GetScore(), f_obj->GetScore());
		return ss;

	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog) {
			// ���ɽ�ɢ�Ƚ����� ��ΪҪ�°� ����Ҫ����true
			return true;
		}

		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerShow(0,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,1));
		SetCurrentPlayerShow(1,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,0));
		SetCurrentPlayerVip(player->GetVIP());
		SetCurrentPlayerLike(player->GetUInt32(PLAYER_FIELD_RANK_LIKE));
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetScore(player->GetUInt32(PLAYER_INT_FIELD_QUALIFY_SCORE));
		return true;
	}
public:
	uint32 GetScore(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL);}
	void SetScore(uint32 v){SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL, v);}
};


//������а�
class RankListWingsObj : public RankListCurrentObj{
public :
	ERankTypes GetType()
	{
		return RANK_TYPE_WINGS;
	}

public :
	int Compare(RankListCurrentObj *obj)
	{
		RankListWingsObj *f_obj = dynamic_cast<RankListWingsObj*>(obj);
		ASSERT(f_obj);
		int ss = CompareNumber(this->GetWingsLv(), f_obj->GetWingsLv());
		return ss;

	}

	bool SetData(BinLogObject *binlog)
	{
		if(!binlog) {
			// ���ɽ�ɢ�Ƚ����� ��ΪҪ�°� ����Ҫ����true
			return true;
		}

		AppdContext *player = dynamic_cast<AppdContext*>(binlog);
		ASSERT(player);
		SetCurrentPlayerGuid(player->GetGuid());
		SetCurrentPlayerName(player->GetName());
		SetCurrentPlayerGender(player->GetGender());
		SetCurrentPlayerTitle(player->GetTitle());
		SetCurrentPlayerShow(0,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,1));
		SetCurrentPlayerShow(1,player->GetUInt16(PLAYER_INT_FIELD_APPEARANCE,0));
		SetCurrentPlayerVip(player->GetVIP());
		SetCurrentPlayerLike(player->GetUInt32(PLAYER_FIELD_RANK_LIKE));
		SetCurrentPlayerWing(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100 + player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		SetWingsLv(player->GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)*100+ player->GetUInt32(PLAYER_INT_FIELD_WINGS_STAR));
		return true;
	}
public:
	uint32 GetWingsLv(){return GetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL);}
	void SetWingsLv(uint32 v){SetUInt32(RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL, v);}
};

RankListCurrentObj *RankListCurrentObj::Factoy(ERankTypes type)
{
	RankListCurrentObj *obj = nullptr;
	switch (type)
	{
	case RANK_TYPE_POWER:
		obj = new RankListForceObj;
		break;
	case RANK_TYPE_LEVEL:
		obj = new RankListLevelObj;
		break;
	case RANK_TYPE_MONEY:
		obj = new RankListMoneyObj;
		break;
	case RANK_TYPE_ONLINE_TIME:
		obj = new RankListOnlineTimeObj;
		break;
	case RANK_TYPE_TRIAL:
		obj = new RankListTrialObj;
		break;
	case RANK_TYPE_FACTION:
		obj = new RankListFactionObj;
		break;
	case RANK_TYPE_DIVINE:
		obj = new RankListDivineObj;
		break;
	case RANK_TYPE_MOUNT:
		obj = new RankListMonutObj;
		break; 
	case RANK_TYPE_SINGLE_PVP:
		obj = new RankListSinglePVPObj;
		break;
	case RANK_TYPE_WINGS:
		obj = new RankListWingsObj;
		break;
	case MAX_RANK_TYPE:
		break;
	default:
		break;
	}
	ASSERT(obj);
	obj->Init();
	return obj;
}

//��ȡս�����а����guid�������ս�����У�
string RankListManager::GetForceRankPlayerGuid(uint32 rank, uint32 force)
{
	RankListCurrentObj *obj = FindRankDataByType(RANK_TYPE_POWER,rank);
	string player_guid = "";
	if(obj)
	{
		RankListForceObj *force_obj = dynamic_cast<RankListForceObj*>(obj);
		if(force_obj && force_obj->GetForce() >= force)
		{
			player_guid = obj->GetCurrentPlayerGuid();
		}
	}
	return player_guid;
}

//��ȡ�ȼ����а����guid��������ȼ����У�
string RankListManager::GetLevelRankPlayerGuid(uint32 rank, uint32 level)
{
	RankListCurrentObj *obj = FindRankDataByType(RANK_TYPE_LEVEL,rank);
	string player_guid = "";
	if(obj)
	{
		RankListLevelObj *level_obj = dynamic_cast<RankListLevelObj*>(obj);
		if(level_obj && level_obj->GetLevel() >= level)
		{
			player_guid = obj->GetCurrentPlayerGuid();
		}
	}
	return player_guid;
}
