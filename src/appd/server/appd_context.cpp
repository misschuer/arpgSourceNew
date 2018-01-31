#include "appd_app.h"
#include "appd_context.h"
#include "appd_script.h"
#include "appd_object_manager.h"
#include "RankListManager.h"
#include <shared/log_handler.h>
#include <shared/chat_analysis.h>
#include <shared/lua_packet_binding.h>
#include <object/OprateResult.h>
#include <comm/b64.h>
#include <comm/crypt.h>
#include "appd_mongodb.h"

//////////////////////////////////////////////////////////////////////////
//for ScenedContext static

//////////////////////////////////////////////////////////////////////////
//for ScenedOpcodeHandler
void AppdContext::OpcodeHandlerInitor()
{
	for (uint32 i = 0; i <= NUM_MSG_TYPES; i++)
	{
		opcode_handler_[i].handler = std::bind(&AppdContext::Handle_LUA, this, std::placeholders::_1);
	}

	opcode_handler_[CMSG_RANK_LIST_QUERY].handler = std::bind(&AppdContext::Handle_Rank_List_Query, this, std::placeholders::_1);
	opcode_handler_[CMSG_RANK_LIST_QUERY].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_RANK_LIST_QUERY].cooldown = 0;

	opcode_handler_[CMSG_BOOKING_MONEY].handler = std::bind(&AppdContext::Handle_Booking_Money, this, std::placeholders::_1);
	opcode_handler_[CMSG_BOOKING_MONEY].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_BOOKING_MONEY].cooldown = 0;

	opcode_handler_[CMSG_CHAR_REMOTESTORE].handler = std::bind(&AppdContext::Handle_Char_Remotestore, this, std::placeholders::_1);
	opcode_handler_[CMSG_CHAR_REMOTESTORE].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_CHAR_REMOTESTORE].cooldown = 0;

	opcode_handler_[CMSG_CHAR_REMOTESTORE_STR].handler = std::bind(&AppdContext::Handle_Char_Remotestore_Str, this, std::placeholders::_1);
	opcode_handler_[CMSG_CHAR_REMOTESTORE_STR].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_CHAR_REMOTESTORE_STR].cooldown = 0;

	opcode_handler_[MSG_SYNC_MSTIME_APP].handler = std::bind(&AppdContext::Handle_Syns_Mstime, this, std::placeholders::_1);
	opcode_handler_[MSG_SYNC_MSTIME_APP].status = STATUS_NEVER;
	
	opcode_handler_[CMSG_USE_GOLD_OPT].cooldown = 500; //ʹ��Ԫ����ʲô
	opcode_handler_[CMSG_USE_SILVER_OPT].cooldown = 500; //ʹ��ͭǮ��ʲô
	opcode_handler_[CMSG_RECEIVE_GIFT_PACKS].cooldown = 500;//�����ȡ
	opcode_handler_[CMSG_QUERY_PLAYER_INFO].cooldown = 0;//��ѯ�����Ϣ
	opcode_handler_[CMSG_BAG_EXCHANGE_POS].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_BAG_EXCHANGE_POS].cooldown = 0;
	opcode_handler_[CMSG_BAG_ITEM_SPLIT].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_BAG_ITEM_SPLIT].cooldown = 200;
	opcode_handler_[CMSG_BAG_ITEM_USER].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_BAG_ITEM_USER].cooldown = 200;
	opcode_handler_[CMSG_STORE_BUY].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_STORE_BUY].cooldown = 300;
	opcode_handler_[CMSG_NPC_SELL].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_NPC_SELL].cooldown = 0;
	opcode_handler_[CMSG_NPC_REPURCHASE].status = STATUS_LOGGEDIN;
	opcode_handler_[CMSG_NPC_REPURCHASE].cooldown = 300;
}




AppdContext *AppdContext::FindPlayer(const string &lguid)
{
	AppdContext *result = dynamic_cast<AppdContext*>(ObjMgr.Get(lguid));
	if(result && result->GetStatus() != STATUS_LOGGEDIN)
		result = nullptr;
	return result;
}

AppdContext *AppdContext::FindAccount(const string &account)
{
	ContextStrMap::iterator it = AccountMaps.find(account);
	if(it != AccountMaps.end())
		return it->second;
	return NULL;
}

// ��̬�������й���
AppdContext::ContextStrMap AppdContext::AccountMaps;

AppdContext::RecommendMap AppdContext::m_recommend;

void AppdContext::GetRecommendFriendGuid(vector<string>& ret, const string& guid) {
	AppdContext *context = AppdContext::FindPlayer(guid);
	if (!context) return;
	
	uint32 level = context->GetLevel();
	uint8 id = uint8(level - 1);
	uint8 limitCount = 5;
	uint8 count = 0;

	std::list<uint8> levelList;
	vector<string> tmp;
	
	for (int i = 0; i < g_Config.player_max_level; ++ i) {
		levelList.clear();

		// ����ƫ�Ƶȼ�
		if (i + level <= g_Config.player_max_level) {
			levelList.push_back(level+i);
		}

		if (level - i > 0 && i > 0 && level - i <= g_Config.player_max_level) {
			levelList.push_back(level-i);
		}

		for (uint8 lv : levelList) {
			uint8 indx = lv - 1;
			if (m_recommend.find(indx) != m_recommend.end()) {
				std::set<string> ss = m_recommend[indx];
				for (string fguid : ss) {
					// �������Լ�
					if (fguid == guid) continue;
					if (context->isFriend(fguid)) continue;
					tmp.push_back(fguid);
					count ++;
				}
			}
		}
		if (count >= limitCount) break;
	}

	if (tmp.size() <= limitCount) {
		for (auto iter = tmp.begin(); iter != tmp.end(); ++ iter) {
			ret.push_back(*iter);
		}

	} else {
		for (int i = 0; i < limitCount; ++ i) {
			int indx = irand(0, tmp.size()-1);
			string fguid = tmp[indx];
			ret.push_back(fguid);
			auto iter = find(tmp.begin(), tmp.end(), fguid);
			if (iter != tmp.end()) {
				tmp.erase(iter);
			}
		}
	}
}

void AppdContext::LevelChanged(const string& guid, uint32 prevLevel, uint32 currLevel) {
	if (prevLevel > 0) {
		RemoveOld(guid, prevLevel);
	}

	AddNew(guid, currLevel);
}

void AppdContext::AddNew(const string& guid, uint32 currLevel) {
	uint8 indx = uint8(currLevel - 1);
	
	auto it = m_recommend.find(indx);
	if (it == m_recommend.end()) {
		std::set<string> s;
		m_recommend[indx] = s;
	}

	m_recommend[indx].insert(guid);
}

void AppdContext::RemoveOld(const string& guid, uint32 prevLevel) {
	uint8 indx = uint8(prevLevel - 1);
	auto it = m_recommend.find(indx);
	if (it != m_recommend.end()) {
		it->second.erase(guid);
	}
}

//������ƥ���ɫ��ؽӿ�


//////////////////////////////////////////////////////////////////////////
//fro scened_context

AppdContext::AppdContext(int fd,ContextManager *mgr):SvrContext(fd,mgr)
{
	m_isCanRecalcul = false;
	
	m_all_money.resize(MAX_MONEY_TYPE, 0);

	SetBinlogMaxSize(MAX_BINLOG_SIZE_3);
	OpcodeHandlerInitor();
}

AppdContext::~AppdContext()
{
	
}

//�ӵ�һ������
void AppdContext::OnAddFirstQuest() {

	LuaStackAutoPopup autoPopup(L);
	LuaGetObjFunc(L, GetGuid().c_str(), "AddFirstQuest");
	if(LUA_PCALL(L, 1, 0, 0)) {
		tea_perror("lua error:OnAddFirstQuest %s", GetGuid().c_str());
	}
}

//�Ƿ��Ǻ���
bool AppdContext::isFriend(const string& fguid) {

	LuaStackAutoPopup autoPopup(L);
	LuaGetObjFunc(L, GetGuid().c_str(), "isFriend");
	lua_pushstring(L, fguid.c_str());
	if(LUA_PCALL(L, 2, 1, 0)) {

		tea_perror("lua error:DoPlayerLogin %s", GetGuid().c_str());
	}
	return LUA_TOBOOLEAN(L, -1) != FALSE;
}


void AppdContext::online() {
	string guid  = this->GetGuid ();
	uint32 level = this->GetLevel();
	AppdContext::AddNew(guid, level);
}

void AppdContext::offline() {
	string guid  = this->GetGuid ();
	uint32 level = this->GetLevel();
	AppdContext::RemoveOld(guid, level);
}

void AppdContext::InsertPlayerMap()
{
	ASSERT(!GetGuid().empty());
	AccountMaps[GetAccount()] = this;	
}

void AppdContext::RemovePlayerMap()
{
	ASSERT(!GetGuid().empty());

	auto it = AccountMaps.find(GetAccount());
	if(it != AccountMaps.end())
	{
		AccountMaps.erase(it);
	}
	else
	{
		tea_pdebug("player %s logout, but accountmap not find", GetGuid().c_str());
		//ASSERT(status_ != STATUS_LOGGEDIN);
	}
}

void AppdContext::Update(uint32 diff)
{
	if (!GetScenedFD())
		return;
	
	if (m_isCanRecalcul)
	{
		SendEquipAttrs();
		m_isCanRecalcul = false;
	}
}

//��ȡ��Ǯ��ֻ�ϱ��������ڲ��Ľ�Ǯ����
//��Ϊbinlog����ͬ�����⡣
double AppdContext::GetMoney(uint16 type)
{
	ASSERT(m_all_money.size() > type);
	return m_all_money[type];
}

void AppdContext::addMoney(uint8 money_type, uint8 oper_type, double val, string& relateItemIds, string& relateItemNums)
{
	if(val <= 0) return;

	if(money_type >= MAX_MONEY_TYPE)
	{
		tea_perror("cent_player::addMoney money_type:%u error player:%s,oper_type:%u,val:%u,relateItemIds:%s,relateItemNums:%u"
			, money_type,GetGuid().c_str(),oper_type,val,relateItemIds.c_str(),relateItemIds.c_str());
		return;
	}

	//TODO:����ǷǮ�Ĵ���
	double old_value = GetMoney(money_type);
	double new_money = old_value + val;
	if (new_money >= MAX_MONEY_TRUE)
		new_money = MAX_MONEY_TRUE;
	m_all_money[money_type] = new_money;

	SetDouble(PLAYER_EXPAND_INT_MONEY + money_type * 2, new_money);
	uint32 now = (uint32)time(NULL);

	switch(money_type)
	{
	case MONEY_TYPE_GOLD_INGOT:
		{
			SaveGoldLog(GetAccount(), GetGuid(), GetName(), money_type, oper_type, val, old_value, new_money, "", 0, 0, 
				val, 0, 0, GetLevel(), 0/*��������ID*/);

			WrtiePay(GetAccount(), GetGuid(), now, 0, oper_type, val, relateItemIds, relateItemNums, GetLevel());


			//��Ѷ��־
			/*if(AppdApp::g_app->GetPlatformID() == PLATFORM_QQ)
				WriteTXMoneyLog(GetAccount(),GetGuid(),GetName(),oper_type,0,old_value,new_money,val,0,p1,p2,(uint32)time(NULL),GetPlatInfo(GetPlatData(),"pf"));*/
			break;	
		}
	case MONEY_TYPE_BIND_GOLD:
		{
			WriteBindGold(GetAccount(), GetGuid(), now, 0, oper_type, val, relateItemIds, relateItemNums, GetLevel());
			break;
		}
	case MONEY_TYPE_SILVER:
		{
			RankListMgr->InsertTask(GetGuid(),RANK_TYPE_MONEY);
			WriteYxb(GetAccount(), GetGuid(), now, 0, oper_type, val, relateItemIds, relateItemNums, GetLevel());
			break;
		}
	default:
		return;		
	}
}

bool AppdContext::subMoney(uint8 money_type, uint8 oper_type, double val, string& relateItemIds, string& relateItemNums)
{
	if(val <= 0)
		return false;
	if(money_type >= MAX_MONEY_TYPE)
	{
		tea_perror("cent_player::subMoney money_type:%u error player:%s,oper_type:%u,val:%u,relateItemIds:%s,relateItemNums:%u"
			, money_type,GetGuid().c_str(),oper_type,val,relateItemIds.c_str(),relateItemIds.c_str());
		return false;
	}

	double money = GetMoney(money_type);
	if(money >= val)
	{
		double old_value = GetMoney(money_type);
		double new_money = old_value - val;
		m_all_money[money_type] = new_money;
		SetDouble(PLAYER_EXPAND_INT_MONEY + money_type * 2, new_money);
		uint32 now = (uint32)time(NULL);

		switch(money_type)
		{
		case MONEY_TYPE_GOLD_INGOT:
			{
				//����Ԫ��
				DoGlodConsumeStatistics(this, val);
				SaveGoldLog(GetAccount(), GetGuid(), GetName(), money_type, oper_type, -1 * val, old_value, new_money, "", 0, 0, 
					val, 0, 0, GetLevel(), 0/*��������ID*/);

				WrtiePay(GetAccount(), GetGuid(), now, 1, oper_type, val, relateItemIds, relateItemNums, GetLevel());

				////��Ѷ��־
				//if(AppdApp::g_app->GetPlatformID() == PLATFORM_QQ)
				//	WriteTXMoneyLog(GetAccount(),GetGuid(),GetName(),oper_type,0,old_value,new_money,val,0,p1,p2,(uint32)time(NULL),GetPlatInfo(GetPlatData(),"pf"));
				break;
			}
		case MONEY_TYPE_BIND_GOLD:
			{
				WriteBindGold(GetAccount(), GetGuid(), now, 1, oper_type, val, relateItemIds, relateItemNums, GetLevel());
				break;
			}
		case MONEY_TYPE_SILVER:
			{
				RankListMgr->InsertTask(GetGuid(),RANK_TYPE_MONEY);
				WriteYxb(GetAccount(), GetGuid(), now, 1, oper_type, val, relateItemIds, relateItemNums, GetLevel());
				break;
			}
		}
		//����Ԫ��ʱ����ʱ���Ҫ��¼
		if((money_type == MONEY_TYPE_GOLD_INGOT || money_type == MONEY_TYPE_BIND_GOLD ) && oper_type != MONEY_CHANGE_WAREHOUSE_HANLD)
			DoLimitActivityConsumption(this,money_type,val);
		return true;
	}
	return false;
}

//����Ԫ��������Ϣ
void AppdContext::SaveGoldLog(const string &account, const string &player_id, const string &player_name, uint16 money_type, uint16 oper_type,
				 double v,double old_value, double new_value, const string &trace_id, uint32 p1, uint32 p2,
				 double unit_price,uint16 item_bind, uint16 item_del, uint32 level, uint32 quest)
{
	WorldPacket pkt(INTERNAL_OPT_ADD_GOLD_LOG);
	pkt << account << player_id << player_name << money_type << oper_type << v << old_value << new_value << trace_id << p1 << p2 
		<< unit_price << item_bind << item_del << level << quest;
	AppdApp::g_app->SendToPoliced(pkt);
}

//////////////////////////////////////////////////////////////////////////

//����ʧ��
void AppdContext::Call_Operation_Failed(uint16 type,uint16 reason, string data)
{
	packet *_pkt;
	pack_operation_failed(&_pkt,type,reason,data.c_str());
	update_packet_len(_pkt);
	SendPacket(*_pkt);
	external_protocol_free_packet(_pkt);
}

//���㲢�·�װ��/�������ԡ����ܡ�BUFF
void AppdContext::SendEquipAttrs()
{
	//�������²���
	if(AppdApp::g_app->IsPKServer()) {
		return;
	}
	AppdApp::g_app->m_equip_attrs->Reset();
	AppdApp::g_app->m_equip_attrs->SetGuid("equip_attrs");//������Id��һ��
	//������������
	DoCalculAttr(this, AppdApp::g_app->m_equip_attrs);
	AppdApp::g_app->m_equip_attrs->Clear();

	//�·���������
	WorldPacket pkt(INTERNAL_OPT_UPDATE_EQUIP_INFO);
	pkt << GetGuid();
	ByteArray bytes;
	AppdApp::g_app->m_equip_attrs->WriteCreateBlock(bytes);
	bytes.position(0);
	pkt << bytes;
	AppdApp::g_app->SendToScened(pkt, GetScenedFD());
}


void AppdContext::Handle_LUA(packet& pkt)
{	
	do_on_external_packet(this,&pkt);
}

//����ͻ���������Ϣ
void AppdContext::Handle_Char_Remotestore(packet& pkt)
{
	uint32 key;
	uint32 value;
	if(unpack_char_remotestore(&pkt,&key,&value))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_CHAR_REMOTESTORE,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	if(key > MAX_CLIENT_UINT32_COUNT)
	{
		WriteAttackPacker(GetAccount(),m_lguid,pkt.head->optcode,ACCACK_PACKET_TYPE_DATA,"");
		return;
	}
	SetUInt32(PLAYER_EXPAND_INT_CLIENT_DATA + key, value);	
}

//��¼���򶩵�
void AppdContext::Handle_Booking_Money(packet& pkt) {
	char *orderid;
	char *goodsname;
	char *money1;
	uint32 goodsnum;

	if(unpack_booking_money(&pkt, &orderid, &goodsname, &money1, &goodsnum)) {
		WriteAttackPacker(GetAccount(),GetGuid(),pkt.head->optcode,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	// 5��ͨ��
	if (AppdApp::g_app->GetPlatformID() != PLATFORM_5WANPK) {
		return;
	}

	recharge_info reInfo;
	memset(&reInfo, 0, sizeof(recharge_info));
	strncpy(reInfo.guid, this->GetGuid().c_str(), 49);
	strncpy(reInfo.orderid, orderid, 49);
	strncpy(reInfo.goodsname, goodsname, 49);
	strncpy(reInfo.money1, money1, 49);
	strncpy(reInfo.account, this->GetAccount().c_str(), 49);
	strncpy(reInfo.name, this->GetName().c_str(), 49);
	reInfo.goodsnum = goodsnum;

	uint8 ret = 0;
	if (LocalDBMgr.insertRechargeInfo(&reInfo)) {
		ret = 1;
	}
	
	packet *_pkt;
	pack_booking_money_result(&_pkt, orderid, ret);
	update_packet_len(_pkt);
	SendPacket(*_pkt);
	external_protocol_free_packet(_pkt);
}

//����ͻ���������Ϣ
void AppdContext::Handle_Char_Remotestore_Str(packet& pkt)
{
	uint32 key;
	char *value;
	if(unpack_char_remotestore_str(&pkt,&key,&value))
	{
		WriteAttackPacker(GetAccount(),m_lguid,pkt.head->optcode,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	if(key > MAX_CLIENT_STRING_COUNT)
	{
		WriteAttackPacker(GetAccount(),m_lguid,pkt.head->optcode,ACCACK_PACKET_TYPE_DATA,"");
		return;
	}
	SetStr(PLAYER_APPD_STRING_FIELD_CLIENT_DATA + key, value);	
}

//ͬ��ʱ��
void AppdContext::Handle_Syns_Mstime(packet& pkt)
{
	uint32 time_now = ms_time();
	packet *_pkt;
	pack_sync_mstime_app(&_pkt,time_now,(uint32)time(NULL),AppdApp::g_app->m_open_time);
	SendPacket(*_pkt);
	external_protocol_free_packet(_pkt);
}
