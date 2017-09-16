#include "appd_app.h"
#include "appd_context.h"
#include "appd_script.h"
#include "appd_object_manager.h"
#include <svrcore/server/Storage.h>
#include <shared/storage_loader.h>
#include <shared/log_handler.h>
#include <object/OprateResult.h>

void AppdContext::Logout()
{
	tea_pdebug("AppdContext::Logout %s %u", guid().c_str(), fd_);
	if(GetStatus() == STATUS_LOGGEDIN)
	{
		
		//��������Ժ�����ʲô��
		DoPlayerLogout();

		//���˺�map��ɾ��
		RemovePlayerMap();

		//״̬��Ϊ����
		SetStatus(STATUS_DELETE);

		//������Ҫ�ͷţ�������0�ͺ�
		AppdApp::g_app->ChangeSessionID(this,0);

		// ���Լ��ӵȼ��б����
		this->offline();
	}
	else
	{
		tea_pdebug("AppdContext::Logout %s status != logind", guid().c_str());
	}	
	
	//�ͷ�����
	string lguid = guid();
	ObjMgr.CallDelTagWatch(guid());
	//todo���Ƿ����ͷţ�
}

bool AppdContext::Login(uint32 fd)
{
	tea_pdebug("AppdContext::Login %s %u", guid().c_str(), fd);
	if(fd_ != 0)
	{
		//��һ����û�˳�������Ϊͬ��������ɵģ����ˣ����ʽ�С
		tea_pwarn("AppdContext::Login fd_ != 0  %s  %u  %u", guid().c_str(), fd, fd_);
		//Logout();
		contextMgr_->CloseSession(fd);
		return false;
	}
	AppdApp::g_app->ChangeSessionID(this,fd);
	m_lguid = guid();
	SetStatus(STATUS_AUTHED);		//������Ķ�����֤ͨ����

	//��ʼ����Ǯ
	for (uint32 i = 0; i < MAX_MONEY_TYPE; i++)
	{
		m_all_money[i] = GetDouble(PLAYER_EXPAND_INT_MONEY + i*2);
	}
	if(!AppdApp::g_app->IsPKServer())
	{
		NewOtherBinlog();
	}
	//�����˺���Ϣ��ѯ��
	InsertPlayerMap();

	AppdApp::g_app->RegSessionOpts(fd_);
	//��¼���
	SetStatus(STATUS_LOGGEDIN);
	//������¼Ӧ�÷���ϵİ����ͻ���
	Call_join_or_leave_server(m_delegate_sendpkt, 0, SERVER_TYPE_APPD, getpid(), AppdApp::g_app->Get_Connection_ID(), uint32(time(nullptr)));

	//��ҵ�¼�Ժ�����ʲô�� TODO: ��������Ƿ���Ҫ������������
	DoPlayerLogin();
	if(!AppdApp::g_app->IsPKServer())
	{
		AppdApp::g_app->login_account_guid(this);
	}

	// ���Լ��ӵ��ȼ��б���
	this->online();

	//ͬ��ʱ��
	packet pkt;
	Handle_Syns_Mstime(pkt);

	return true;
}


void AppdContext::firstLoginAndInitQuestGuidObject() {
	this->OnAddFirstQuest();
}

void AppdContext::firstLoginAndCopySpellInfoToGuidObject(GuidObject* obj) {
	//Ӧ���Ǳ�����ʱ���λ >6 �������⼼��
	uint32 count = 0;
	for (int i = PLAYER_INT_FIELD_SPELL_START; i <	PLAYER_INT_FIELD_SPELL_END; ++ i) {

		uint32 val = this->GetUInt32(i);
		if (val > 0) {

			uint16 id = this->GetUInt16(i, SHORT_SLOT_SPELL_ID);
			uint8  lv = this->GetByte(i, BYTE_SLOT_SPELL_LV);
			uint8  st = this->GetByte(i, BYTE_SLOT);
			if (st <= SLOT_ANGER) {

				obj->SetUInt16(count + SPELL_INT_FIELD_BASE_SPELL_START, SHORT_SPELL_ID, id);
				obj->SetUInt16(count + SPELL_INT_FIELD_BASE_SPELL_START, SHORT_SPELL_LV, lv);
				count ++;
			}
		}
	}
	obj->SetUInt32(SPELL_BASE_COUNT, count);

	this->generateTempSpellLevelInfo(obj);
}

void AppdContext::generateTempSpellLevelInfo(GuidObject* obj) {
	uint32 sizeIndex = obj->GetUInt32(SPELL_BASE_COUNT) + SPELL_INT_FIELD_BASE_SPELL_START;
	for (uint32 i = SPELL_INT_FIELD_BASE_SPELL_START; i < sizeIndex; ++ i) {
		uint16 spellId = obj->GetUInt16(i, SHORT_SPELL_ID);
		uint8 spellLv = (uint8)obj->GetUInt16(i, SHORT_SPELL_LV);
		this->m_SpellLevel[spellId] = spellLv;
		//�������ܵĸ�������
		this->mapSupportSpell(spellId, spellLv);
	}

	/************************************************************************/
	/* ����ĸ�������                                                       */
	/************************************************************************/
	// ������׼���
	for (uint32 i = SPELL_INT_FIELD_MOUNT_SPELL_START; i < SPELL_INT_FIELD_MOUNT_SPELL_END; ++ i) {
		uint16 spellId = obj->GetUInt16(i, SHORT_SPELL_ID);
		if (spellId == 0) {
			break;
		}
		uint8 spellLv = (uint8)obj->GetUInt16(i, SHORT_SPELL_LV);
		this->m_SpellLevel[spellId] = spellLv;
		this->mapSupportSpell(spellId, spellLv);
	}

	//����û�����
	for (uint32 i = SPELL_INT_FIELD_MOUNT_ILLUSION_START; i < SPELL_INT_FIELD_MOUNT_ILLUSION_END; i += MAX_ILLUSION_ATTR_COUNT) {
		
		uint32 offs = i + ILLUSION_ATTR_SPELL_START;
		uint32 offt = i + ILLUSION_ATTR_SPELL_END;
		for (uint32 j = offs; j < offt; ++ j) {

			uint16 spellId = obj->GetUInt16(j, SHORT_SPELL_ID);
			if (spellId == 0) {
				break;
			}
			uint8 spellLv = (uint8)obj->GetUInt16(j, SHORT_SPELL_LV);
			this->m_SpellLevel[spellId] = spellLv;
			this->mapSupportSpell(spellId, spellLv);
		}
	}

	// ����ĸ�������
	for (uint32 i = SPELL_DIVINE_START; i < SPELL_DIVINE_END;  i+= MAX_DIVINE_COUNT ){
		if (obj->GetByte(i,0) != 0){ 
			uint16 sid = obj->GetUInt16(i+DIVINE_SKILL,0);
			uint8 lev = (uint8)obj->GetUInt16(i+DIVINE_SKILL,1);

			if (sid != 0){
				this->m_SpellLevel[sid] = lev;
				this->mapSupportSpell(sid, lev);
			}

			for (uint32 j=0;j<3;j++){
				sid = obj->GetUInt16(i+DIVINE_PASSIVE_SKILL+j,0);
				lev = (uint8)obj->GetUInt16(i+DIVINE_PASSIVE_SKILL+j,1);
				if (sid != 0){
					this->m_SpellLevel[sid] = lev;
					this->mapSupportSpell(sid, lev);
				}
			}
		}
	}


	this->generatePassiveIndexInfo();
}

void AppdContext::mapSupportSpell(uint16 spellId, uint8 spellLv) {
	skill_base* base = skill_base_db[spellId];
	if (base && base->is_initiative == SPELL_SUPPORT) {
		this->l_supportSpell.push_back(spellId);
	}
}

void AppdContext::generatePassiveIndexInfo() {
	uint16 size = (uint16)this->uint32_values_size();
	for (uint16 i = PLAYER_INT_FIELD_PASSIVE_SPELL_START; i < size; ++ i) {
		uint16 spellId = this->GetUInt16(i, SHORT_SPELL_ID);
		if (spellId == 0) {
			continue;
		}
		uint8 spellLv = (uint8)this->GetUInt16(i, SHORT_SPELL_LV);
		this->m_PassiveIndex[spellId] = i;
		this->m_SpellLevel[spellId] = spellLv;
	}
}

void AppdContext::NewOtherBinlog()
{

	/*NewOtherBinlog(ObjectTypeSocial, PLAYER_APPD_INT_FIELD_FLAGS_SOCIAL_CREATE,[](){
		BinLogObject *binlog = new BinLogObject;
		binlog->SetBinlogMaxSize(core_obj::SyncEventRecorder::MAX_BINLOG_SIZE_4);
		return binlog;
	});*/
	NewOtherBinlog(ObjectTypeGiftPacks, PLAYER_APPD_INT_FIELD_FLAGS_GIFT_CREATE,[](){
		BinLogObject *binlog = new BinLogObject;
		binlog->SetBinlogMaxSize(core_obj::SyncEventRecorder::MAX_BINLOG_SIZE_3);
		return binlog;
	});
	// NewOtherBinlog(ObjectTypeLimit, PLAYER_APPD_INT_FIELD_FLAGS_LIMIT_CREATE);
	NewOtherBinlog(ObjectTypeItemMgr, PLAYER_APPD_INT_FIELD_FLAGS_ITEM_CREATE);
	// ����߼�
	NewOtherBinlog(ObjectTypeLogical, PLAYER_APPD_INT_FIELD_FLAGS_LOGICAL_CREATE);
	// ��Ҽ���
	NewOtherBinlog(ObjectTypeSpell, PLAYER_APPD_INT_FIELD_FLAGS_SPELL_CREATE);
	// ��Ҹ���
	NewOtherBinlog(ObjectTypeInstance, PLAYER_APPD_INT_FIELD_FLAGS_INSTANCE_CREATE);
	// �罻��ϢObjectTypeSocial
	NewOtherBinlog(ObjectTypeSocial,PLAYER_APPD_INT_FIELD_FLAGS_SOCIAL_CREATE);
	// ����
	NewOtherBinlog(ObjectTypeQuest, PLAYER_APPD_INT_FIELD_FLAGS_QUEST_CREATE);	
}

void AppdContext::CreateOtherBinlog(const string new_guid, uint32 flag, std::function<BinLogObject*()> create_fun)
{
	BinLogObject *binlog = nullptr;
	if(create_fun == nullptr)
	{
		binlog = new BinLogObject(core_obj::SYNC_SLAVE | core_obj::SYNC_LOCAL);
	}
	else
	{
		binlog = create_fun();
	}
	ASSERT(binlog);
	binlog->SetGuid(new_guid);
	binlog->SetOwner(guid());
	SetFlags(flag);
	vector<GuidObject*> vec;
	vec.push_back(binlog);
	ObjMgr.CallPutObjects(guid(), vec);

	// ����������Ǽ��ܶ����Ǿ��ü��ܲ۵Ķ��󿽱���ȥ
	if (GuidManager::GetPrefix(new_guid) == ObjectTypeSpell) {
		this->firstLoginAndCopySpellInfoToGuidObject(binlog);
		// ��һ�γ�ʼ���������
	} else if (GuidManager::GetPrefix(new_guid) == ObjectTypeQuest) {
		this->firstLoginAndInitQuestGuidObject();
	}
}

void AppdContext::NewOtherBinlog(const string new_guid, uint32 flag, std::function<BinLogObject*()> create_fun)
{
	if (!ObjMgr.Get(new_guid))//��������ڣ����½�һ��
	{
		tea_pdebug("AppdContext::NewOtherBinlog %s %s", guid().c_str(), new_guid.c_str());
		if(GetFlags(flag))
		{
			tea_pinfo("AppdContext::NewOtherBinlog err,player->GetFlags(%u), %s %s", flag, guid().c_str(), new_guid.c_str());
			string player_guid = guid();
			ObjMgr.CallAddWatch(new_guid, [player_guid, new_guid, flag, create_fun](bool b){
				AppdContext *player = ObjMgr.FindPlayer(player_guid);
				if(b)
				{
					tea_pinfo("AppdContext::NewOtherBinlog callback ok player->GetFlags(%u), %s", flag, player_guid.c_str());
					ObjMgr.CallSetTag(new_guid, player_guid);
					if(player) {
						ObjMgr.InsertObjOwner(new_guid);
						// ���ܵĻ�������ʱ����
						if (GuidManager::GetPrefix(new_guid) == ObjectTypeSpell) {
							player->generateTempSpellLevelInfo(ObjMgr.Get(new_guid));
						}
					}
					else
						ObjMgr.CallDelWatch(new_guid);
				}
				else
				{
					tea_pinfo("AppdContext::NewOtherBinlog callback err player->GetFlags(%u), %s", flag, player_guid.c_str());
					if(player && player->GetStatus() == STATUS_LOGGEDIN)
					{
						stringstream ss;
						ss << flag;
						player->Close(PLAYER_CLOSE_OPERTE_APPD_ONE2,"");
					}
				}
			});
			return;
		}
		//û��ȡ������new��
		CreateOtherBinlog(new_guid, flag, create_fun);
	} else {
		// ���ܵĻ�������ʱ����
		if (GuidManager::GetPrefix(new_guid) == ObjectTypeSpell) {
			string player_guid = guid();
			AppdContext *player = ObjMgr.FindPlayer(player_guid);
			if (player) {
				player->generateTempSpellLevelInfo(ObjMgr.Get(new_guid));
			}
		}
	}
}

void AppdContext::NewOtherBinlog(EObjectTypePrefix t, uint32 flag, std::function<BinLogObject*()> create_fun)
{
	string new_guid = GuidManager::ReplaceSuffix(guid(), t);
	NewOtherBinlog(new_guid, flag, create_fun);
}

//��ҵ�¼����ʲô
int AppdContext::DoPlayerLogin()
{
	LuaStackAutoPopup autoPopup(L);
	LuaGetObjFunc(L, GetGuid().c_str(), "Login");
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror("lua error:DoPlayerLogin %s", GetGuid().c_str());
	}
	return 0;
}

//�����������ʲô
int AppdContext::DoPlayerLogout()
{

	LuaStackAutoPopup autoPopup(L);
	LuaGetObjFunc(L, GetGuid().c_str(), "Logout");
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror("lua error:DoPlayerLogout %s", GetGuid().c_str());
	}
	return 0;
}


//ս���ı�
int AppdContext::OnForceChanged() {
	
	LuaGetObjFunc(L, this->GetGuid().c_str(), "OnForceChanged");
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror("lua error:LuaOnForceChanged player guid: %s", this->GetGuid().c_str());
		return 0;
	}

	return 0;
}
//�ȼ��ı�
int AppdContext::OnLevelChanged() {
	LuaGetObjFunc(L, this->GetGuid().c_str(), "OnLevelChanged");
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror("lua error:LuaOnLevelChanged player guid: %s", this->GetGuid().c_str());
		return 0;
	}

	return 0;
}
