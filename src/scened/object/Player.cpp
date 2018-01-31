#include "scened_context.h"
#include "Map.h"
#include "scened_scripts.h"
#include "BuffManager.h"
#include "QuestGetter.h"
#include <object/OprateResult.h>
#include <shared/log_handler.h>
#include "Player.h"
#include "shared/map_template.h"
#include "Grid.h"

//��PK��ͼ
const uint32 SAFEMAP[] = {1, 2};

#define  FCM_TIME  60000
#define  RED_NAME_UPDATE 3		//����״̬�������ڣ���
#define DA_ZUO_INTERVAL 3000	//��������ʱ��(����)
#define HP_RECOVERY_INTERVAL 3000 //�����Ѫ����
#define AUTO_HPMP_TIME 4000
#define  ENDURANCE_RECOVERY_TIME 60000

Player::Player():m_session(NULL),m_equip_attrs(NULL),m_questMgr(NULL),m_cur_combet_state(COMBAT_STATE_LEAVE)
	,m_exp_bonus(0),m_combat_state(0),m_PVP_state(0),daZuoStartTimestamp(0),
	m_energy_auto_recovery(g_Config.energy_auto_recovery_cycle),
	m_endurance_recovery(ENDURANCE_RECOVERY_TIME),m_auto_recovery(AUTO_HPMP_TIME)
{
	m_can_calcul_attr = true;
	SetCanActiveGrid(true);
	srand((uint32)time(NULL));							//��ʱ
	m_fcm_timer.SetInterval(FCM_TIME);					//�����Զ�ʱ����һ����һ��
	m_red_name_timer.SetInterval(RED_NAME_UPDATE*1000);	//������ʱ�� 5����һ�� ���Ȳ���̫��	
	m_counter_timer.SetInterval(1000);					//ս��ʱ�䶨ʱ�� һ��һ��
	m_dazuo_timer.SetInterval(DA_ZUO_INTERVAL);			//����ʱ�䶨ʱ�� ����һ��	
	m_hp_timer.SetInterval(HP_RECOVERY_INTERVAL);
	m_player_exp = 0;
	m_last_spell_time = 0;

	//��ʼ������ϵͳ������binlog
	m_equip_attrs = new BinLogObject;
}

Player::~Player()
{
	for(auto it = m_pets.begin(); it != m_pets.end();++it)
	{
		(*it)->SetClearTimer(1);
	}
	safe_delete(m_questMgr);
	safe_delete(m_equip_attrs);
}

void Player::Update(uint32 diff)
{
	//Unit�����������Ҫ���ƶ������ܵȵȶ�ʱ�������뿪��ͼʱ����������
	Unit::Update( diff );
	UpdateAutoRecovery(diff);
	//UpdateFCMLoginTime(diff);
	m_questMgr->Update(diff);
	
	for (auto it = m_bingzhong_spells_cd.begin(); it != m_bingzhong_spells_cd.end(); ++it)
	{
		if(it->second > 0)
			it->second -= diff;
	}
}

//��������״̬
void Player::UpdateLiveStatus(uint32 diff)
{
	//���ţ����߼��������û��Ҫ������
	if(isAlive())
		return;

	m_live_timer.Update(diff);
	if (m_live_timer.Passed())
	{
		GetMap()->AddRespanPlayer(this);				
		m_live_timer.Reset(0);			
	}	
}

//�Զ��ظ���ս��״̬����
void Player::UpdateAutoRecovery(uint32 diff)
{
	//ս��״̬��ʱ��
	m_PVP_state.Update(diff);
	if(m_PVP_state.Passed() && GetPVPstate() || !isAlive())
	{
		SetPVPstate(false);		//ȡ��pvp��־
		//����PKʱ����½ű� ��һЩӦ�øɵ���
		DosometingScript(this);
		

	}
	//����ս��״̬���ܻ��Զ��ظ���ʱ��
	m_combat_state.Update(diff);
	if (m_combat_state.Passed()&&isAlive())
	{
		//�����״̬����һ�ν���ս��ֻ��һ��ս���뿪
		if (m_cur_combet_state == COMBAT_STATE_ENTER)
		{
			//m_cur_combet_state = COMBAT_STATE_LEAVE;
			ChangeFightStatusToLeave();
			//GetSession()->Call_Combat_State_Update(COMBAT_STATE_LEAVE);
			// ���������ģʽ������, �ͱ�ɺ�ƽ
		}
	}
	//����״̬��ʱ��������״̬���ٽ�ȥ�ͺ���
	if (GetRedNameTime())
	{
		m_red_name_timer.Update(diff);
		if (m_red_name_timer.Passed())
		{
			SetRedNameTime(GetRedNameTime()-RED_NAME_UPDATE);
			m_red_name_timer.Reset();
		}
	}

	//������ʱ��
	if (daZuoStartTimestamp > 0) {
		m_dazuo_timer.Update(diff);
		if (m_dazuo_timer.Passed()) {
			//TODO: �Ӵ���Ӧ�üӵ�
			m_dazuo_timer.Reset();
		}
	}

	// �����Ѫ��ʱ��
	m_hp_timer.Update(diff);
	if (m_hp_timer.Passed()) {
		// ���ŲŻ��Ѫ
		if (this->isAlive()) {
			double recoveryValue = this->GetRecovery();
			double recoveryRate = this->GetRecoveryRate();
			double val = floor(recoveryValue + recoveryRate / 10000.0 * recoveryValue);
			// ���Ѫ�Ĳ���
			if (val > 0) {
				this->ModifyHealth(val);
			}
		}
		m_hp_timer.Reset();
	}

	//�յľͱ����
	if (!m_counter_map.empty())
	{
		m_counter_timer.Update(diff);
		if (m_counter_timer.Passed())
		{
			for(CounterMap::iterator iter = m_counter_map.begin();
				iter != m_counter_map.end();++iter)
			{
				if (iter->second>0)
					iter->second = iter->second - 1;	
			}
			m_counter_timer.Reset2();
		}
		//ʱ�䵽�ľ�ɾ������
		for(CounterMap::iterator iter = m_counter_map.begin();
			iter != m_counter_map.end();)
		{
			if (iter->second == 0)
				m_counter_map.erase(iter++);	
			else
				++iter;
		}
	}
	
	//�Զ��ҩ
	//if ( m_PVP_state.Passed() && GetMap() && GetMap()->m_can_recovry && isCanRecovery())
	//m_auto_recovery.Update(diff);
	//if (m_auto_recovery.Passed() && isInHook() && GetMap() && GetMap()->m_can_recovry && isCanRecovery())
	//{
	//	uint16 percent = GetHookHpPercents();
	//	//Ѫ���ڹһ�ֵ�һ���
	//	if ( GetMaxHealth() && GetHealth()*100/GetMaxHealth() < percent && isAlive() && GetSession())
	//	{
	//		// ֪ͨӦ�÷�ʹ����Ʒ
	//		string str = "";
	//		uint16 id = GetHookUseItemId();
	//		ScenedApp::g_app->call_player_do_something(this->GetSession()->GetGuid(), SCENED_APPD_USE_ITEM, id, str);
	//	}
	//	m_auto_recovery.Reset(AUTO_HPMP_TIME);
	//}

	////�Զ�����
	//m_energy_auto_recovery.Update(diff);
	//if (m_energy_auto_recovery.Passed()&&isAlive()&&isCanRecovery())
	//{
	//	ModifyPower(POWER_ENERGY,g_Config.energy_auto_recovery_values);
	//	m_energy_auto_recovery.Reset(g_Config.energy_auto_recovery_cycle);
	//}	
}

//�������ۼ�����ʱ������
void Player::UpdateFCMLoginTime(uint32 diff)
{
	//�Ƿ��������
	if (GetSession() && GetSession()->GetFCMLoginTime()==(uint32)-1)
	{
		m_fcm_timer.Update(diff);
		if (m_fcm_timer.Passed())
		{
			GetSession()->AddOnlineTime(1);
			GetSession()->AddDailyOnlineTime(1);
			m_fcm_timer.Reset2();
		}  
		return;
	}
	else
	{
		m_fcm_timer.Update(diff);
		if (m_fcm_timer.Passed())
		{
			if (GetSession())
			{
				GetSession()->AddOnlineTime(1);
				GetSession()->AddDailyOnlineTime(1);
				GetSession()->AddFCMLoginTime(1);
			}
			m_fcm_timer.Reset2();
		}
	}	
}

//�Ƿ��ڰ�ȫ��
bool Player::isInSafeArea() const
{	
	if(!GetMap())
		return true;
	//���Ű�ȫ��ͼ
	for (uint8 i = 0;i<sizeof(SAFEMAP)/sizeof(uint32);i++)
	{
		if (GetMapId() == SAFEMAP[i])
			return true;
	}
	//�����	
	return GetMap()->GetMapTemp()->IsInSafeArea(uint16(GetPositionX()),uint16(GetPositionY()));
}

// ����ս��
void Player::fightStatusEnter() {
	m_cur_combet_state = COMBAT_STATE_ENTER;
	SetBit(PLAYER_FIELD_FLAGS, UNIT_FIELD_FLAGS_IS_PVP);
	GetSession()->Call_Combat_State_Update(COMBAT_STATE_ENTER);
}

// �뿪ս��
void Player::ChangeFightStatusToLeave() {
	m_cur_combet_state = COMBAT_STATE_LEAVE;
	GetSession()->Call_Combat_State_Update(COMBAT_STATE_LEAVE);
	UnSetBit(PLAYER_FIELD_FLAGS, UNIT_FIELD_FLAGS_IS_PVP);
	SetSelfProtectUintGuid(0);
}


//PVP����ش���
void Player::DoPvPEvent(Player* target)
{
	/*
	//���û���
	if (target->GetRedNameTime()==0)
		SetRedNameTime(g_Config.red_name_time);
	*/
	//����ʱ�� �� ����/1000
	target->m_counter_map[GetGuid()] = g_Config.left_fighting_time/1000;
	//PKʱ����½ű� ��һЩӦ�øɵ���
	DOPlayerPvPScript(this,target);
}

//PVB����ش���
void Player::DoPvBEvent(Unit* target)
{
	//��Ҵ�bossʱ����½ű� ��һЩӦ�øɵ���
	DOPlayerPvBScript(this,target);
}

void Player::OnKilled(Unit* killer, uint16 id)
{
	//ASSERT(GetMap());
	if (GetMap() == NULL)
	{
		tea_perror("assert error: Player::OnKilled ASSERT(GetMap())");
		GetSession()->Close(PLAYER_CLOSE_OPERTE_SCREND_ONE35,"");
		return;
	}
	
	Unit::OnKilled(killer);
	//��������ս��
	if (!m_combat_state.Passed())
	{
		//GetSession()->Call_Combat_State_Update(COMBAT_STATE_LEAVE);
		//m_cur_combet_state = COMBAT_STATE_LEAVE;
		ChangeFightStatusToLeave();
	}

	//�����б����
	m_counter_map.clear();

	//�������ٻ���С��
	for(auto it = this->m_pets.begin(); it != this->m_pets.end();++it)
	{
		(*it)->SetClearTimer(1);	
	}

	//����Ǳ����ɱ��
	if (killer && killer->GetTypeId()==TYPEID_PLAYER)
	{
		Player* temp_killer = dynamic_cast<Player*>(killer);
		OnSendKilled(temp_killer, id);
		DOPlayerPvPKilledScript(temp_killer, this);
		if(temp_killer->GetQuestMgr())
			temp_killer->GetQuestMgr()->KilledLevelPlayer(GetLevel());
	}
	else
	{
		string killer_name = "";
		if(killer)
			killer_name = killer->GetName();
		OnPlayerKilledByMonster(this, killer);
		if (GetSession())
		{
			WriteDeath(GetSession()->GetAccount(), GetSession()->GetGuid(),killer_name.c_str(), GetLevel(), GetMapId(), 0);
		}
	}

	// �������
	OnPlayerDeath(this);

	//����ʧ�ܵ�
	m_questMgr->AutoFailOfflineOrDie();

	uint32 resTime = 0;
	DoGetMapSingleRespawnScript(GetMap(), this, resTime);
	resTime *= 1000;
	m_live_timer.Reset(resTime);
}

//�������ɱ,����Ӧ�÷���д��־
void Player::OnSendKilled(Player* killer, uint16 id)
{
	stringstream deal_reason;
	packet *_pkt;
	if(static_cast<Player*>(killer)->GetSession() && GetSession())
	{
		if (id == 0)
		{
			pack_kill_man(&_pkt,static_cast<Player*>(killer)->GetSession()->GetGuid().c_str(), killer->GetName().c_str(), GetSession()->GetGuid().c_str(),GetName().c_str());
		}
		else
		{//��buffŪ����
			pack_kill_man(&_pkt,static_cast<Player*>(killer)->GetSession()->GetGuid().c_str(), "", GetSession()->GetGuid().c_str(),GetName().c_str());
		}
	}

	Player *_killer = (Player*)killer;
	if (_killer->GetSession())
		_killer->GetSession()->SendPacket(*_pkt);
	if (GetSession())
		GetSession()->SendPacket(*_pkt);
	external_protocol_free_packet(_pkt);

	uint32 silver = 0;
	OnPlayerKilled(this,(Player*)killer,silver);
	deal_reason << "�����[" << killer->GetName() << "]ɱ��";
	if (GetSession())
	{
		ScenedApp::g_app->call_user_killed(GetSession()->GetGuid(), static_cast<Player*>(killer)->GetSession()->GetGuid(), silver);
		WriteDeath(GetSession()->GetAccount(), GetSession()->GetGuid(), deal_reason.str().c_str(), GetLevel(), GetMapId(), 1);
	}

}

void Player::OnJoinMap()
{
	GetBuffManager()->UpDateHasBuffId();
	//������ô����������ϵ�BUFF
	DoOnlineClearBuff(this);

	//���ʱ��
	m_live_timer.Reset(GetMap()->GetPlayerAutoRespanTime());
	if (this->isAlive() && this->GetHealth() == 0) {
		SetUInt32(UNIT_FIELD_HEALTH, this->GetMaxHealth());
		tea_pdebug("============================alived but why health == 0");
	}

	if (!m_pets.empty())
	{
		tea_perror("assert error: Player::OnJoinMap ASSERT(m_pets.empty())");
		GetSession()->Close(PLAYER_CLOSE_OPERTE_SCREND_ONE36,"");
		return;
	}

	m_questMgr->InitQuest();
	m_questMgr->OnJoinMap();

	//�������ͻ���ͬ���·�����ʱ��
	uint32 time_now = ms_time();
	packet *_pkt;
	pack_sync_mstime(&_pkt,time_now,(uint32)time(NULL),ScenedApp::g_app->m_open_time);
	m_session->SendPacket(*_pkt);
	external_protocol_free_packet(_pkt);
}

void Player::OnLeaveMap()
{
	if(IsMoving())
		StopMoving(false);
	m_questMgr->OnLeaveMap();
}

void Player::Create (ScenedContext *session)
{
	m_session = session;

	//ASSERT(!m_questMgr);
	if (m_questMgr)
	{
		tea_perror("assert error: Player::Create ASSERT(!m_questMgr)");
		GetSession()->Close(PLAYER_CLOSE_OPERTE_SCREND_ONE37,"");
		return;
	}
	
	m_questMgr = new QuestGetter(*this);	
	
	//����guid
	string lguid = Map::CreateNewCreatureID();
	sprintf(m_tmp, "%s.%s", lguid.c_str(), m_session->GetGuid().c_str());
	SetGuid(m_tmp);
	_Create(m_tmp, 0);
	SetTypeId(TYPEID_PLAYER);

	//����������һ��ms����Ĵ���ʱ��
	const uint32 KAIFU_TIME = 1429322400;
	struct timeval tmnow;	
	gettimeofday(&tmnow, NULL);	
	SetGOData((tmnow.tv_sec-KAIFU_TIME)*1000+tmnow.tv_usec/1000);

	OnAfterPlayerDataUpdate(m_session, OBJ_OPT_NEW, mask_, mask_);
	m_session->after_update(std::bind(&Player::OnAfterPlayerDataUpdate,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
}

bool Player::IsHungUp()
{
	return m_session->GetBit(PLAYER_SCENED_INT_FLAGS, PLAYER_SCENED_FLAS_HUNG_UP);
}

void Player::SetHungUp(bool is_hung_up)
{
	if(is_hung_up)
		m_session->SetBit(PLAYER_SCENED_INT_FLAGS, PLAYER_SCENED_FLAS_HUNG_UP);
	else
		m_session->UnSetBit(PLAYER_SCENED_INT_FLAGS, PLAYER_SCENED_FLAS_HUNG_UP);
}

//pvp״̬
void Player::SetPVPstate(bool flag)
{
	if (flag)
	{
		 if(!GetPVPstate())
			m_session->SetBit(PLAYER_SCENED_INT_FLAGS, PLAYER_SCENED_FLAS_PVP_STATE);
	}
	else
	{
		if (GetPVPstate())
			m_session->UnSetBit(PLAYER_SCENED_INT_FLAGS, PLAYER_SCENED_FLAS_PVP_STATE);
	}
}

//��ȡpvp״̬��bitλ
bool Player::GetPVPstate()
{
	return m_session->GetBit(PLAYER_SCENED_INT_FLAGS, PLAYER_SCENED_FLAS_PVP_STATE);
}

//��ȡ����
void Player::GainExp(double exp,uint8 type,double vip_exp)
{
	if (GetSession())
	{
		exp = (double)(floor(exp*GetCoefficient().exp_multiples/100));
		double cur_exp = m_player_exp + exp;
		double next_lv_xp = GetSession()->GetDouble(PLAYER_EXPAND_INT_NEXT_LEVEL_XP);
		// ֪ͨ
		//Call_exp_update(this->GetSession()->m_delegate_sendpkt, (int32)exp, type, (int32)vip_exp);

		bool bCalcul = false;
		//����
		uint32 temp_level = GetLevel();
		if (GetLevel()< g_Config.max_player_level)
		{
			if (cur_exp >= next_lv_xp)
				bCalcul = true;
			while(cur_exp>=next_lv_xp)
			{
				ASSERT(cur_exp == cur_exp);
				ASSERT(next_lv_xp == next_lv_xp);
				cur_exp -= next_lv_xp;
				if(!Upgrade ())
					break;	//����
				next_lv_xp = GetSession()->GetDouble(PLAYER_EXPAND_INT_NEXT_LEVEL_XP);
				/*tea_pdebug("playerguid = %s playername = %s upgrade player exp = %.0f, cur_exp = %.0f,next_lv_xp = %.0f,level = %u,max_level = %u", 
					GetGuid().c_str(), GetName().c_str(), exp,cur_exp,next_lv_xp, GetLevel(), g_Config.max_player_level); */
			}
		}
		//�ȼ������� ����Ū���ͺ�
		if(GetLevel() >= g_Config.max_player_level)
		{
			if(cur_exp>next_lv_xp)
				cur_exp = next_lv_xp;
		}

		m_player_exp = cur_exp;
		GetSession()->SetExp();

		//if (exp)
		//{
		//	//���¾���
		//	packet *pkt;
		//	pack_exp_update(&pkt,(int32)exp,type,(int32)vip_exp);
		//	GetSession()->SendPacket(*pkt);
		//	external_protocol_free_packet(pkt);	
		//}

		if (bCalcul)
		{
			Upgrade_Calculate(temp_level);
			tea_pdebug("playerguid = %s playername = %s  before upgrade player level = %u  after upgrade player level = %u,max_level = %u", 
				GetGuid().c_str(), GetName().c_str(), temp_level, GetLevel(), g_Config.max_player_level); 
		}		
	}	
}


//����
bool Player::Upgrade ()
{
	if (!GetSession())
		return false;
	if (GetLevel()+1 > g_Config.max_player_level)
		return false;

	SetLevel(GetLevel()+1);

	double next_lv_xp;
	char_level *level_info = char_level_db[GetLevel()];
	ASSERT(level_info);
	if (GetLevel()>=g_Config.max_player_level)
	{
		//�ز����治һ���������������������
		if (char_level_db.size()>g_Config.max_player_level)
		{
			next_lv_xp = level_info->next_exp;
		}	
		else
			next_lv_xp=-1;
	}
	else
		next_lv_xp = level_info->next_exp;
	m_session->SetDouble(PLAYER_EXPAND_INT_NEXT_LEVEL_XP,next_lv_xp);

	return true;
}

//����������
void Player::Upgrade_Calculate(uint32 prevLevel)
{
	char_level *level_info = char_level_db[GetLevel()];
	//Ѫ������ �������� ����Ѫ��	�����¡������ͼ�����Ļ��Ͳ�����
	if (m_can_calcul_attr)
	{
		/*TODO
		SetMaxHealth(level_info->hp);
		//SetHealth(level_info->hp);
		SetMaxPower(POWER_MANA,level_info->mp);
		SetPower(POWER_MANA,level_info->mp);
		*/
		//SetPower(POWER_ENERGY,GetMaxPower(POWER_ENERGY));
	}

	// ���������������Ѫ�����ֵ
	int32 diff = 0;
	DoGetCharDiffHp(prevLevel, GetLevel(), diff);
	uint32 currMaxHealth = this->GetMaxHealth();
	if (diff > 0) {
		currMaxHealth += diff;
	}
	this->SetMaxHealth(currMaxHealth);

	// ��������(��Ӧ�÷��������Ժ���)
	// Calcul_Attr();
	// �Ȱ�P�����Ѫ������Ҳͬ����
	this->m_session->SetDouble(PLAYER_FIELD_MAX_HEALTH, currMaxHealth);
	//������Ҫ��Ѫ ������Ҫ���⴦��
	SetHealth(GetMaxHealth());
	
	// ��ͬ��һ��Ѫ��
	this->SyncCacheData();
	/*SetPower(POWER_MANA,GetMaxPower(POWER_MANA));
	SetPower(POWER_ENERGY,GetMaxPower(POWER_ENERGY));*/

	if (GetSession())
	{
		//�㲥����
		packet *_pkt;
		pack_player_upgrade(&_pkt,GetUIntGuid());
		GetMap()->Broadcast(*_pkt,this,true);
		external_protocol_free_packet(_pkt);

		//֪ͨӦ�÷����������
		ScenedApp::g_app->call_player_upgrade(GetSession()->GetGuid(), prevLevel, GetLevel());
		// ֪ͨӦ�÷�
		// ScenedApp::g_app->call_recalculate(GetSession()->GetGuid());
	}
	//ˢ�¿ɽ������б�
	//m_questMgr->RefreshCanSeeQuests();
	//���µ�ǰ�����б����,��Щ����Ҫ��ȼ�
	//m_questMgr->Upgrade();

	if (GetMap())
	{
		OnPlayerUpgrage(GetMap(), this, prevLevel, GetLevel());
	}
	if (GetSession())
	{
		uint32 now = (uint32)time(NULL);
		uint32 prevTime = GetSession()->GetUInt32(PLAYER_INT_FIELD_LV_UP_TIMESTAMP);
		GetSession()->SetUInt32(PLAYER_INT_FIELD_LV_UP_TIMESTAMP, now);
		WriteLvup(GetSession()->GetAccount(), GetSession()->GetGuid(), GetSession()->GetCreateTime(), now,
			GetLevel(), now - prevTime);
	}
}

//���¼����������
void Player::Calcul_Attr()
{
	if (!m_can_calcul_attr)
	{
		DoRecalculationAttrs(this, false);
		GetBuffManager()->AddBuffAttr();
		return;
	}
	
	Unit::Calcul_Attr();

	//����
	DoRecalculationAttrs(this);

	//�����ͼ���Լӳ�
	if (GetMap())
	{
		SetMaxHealth(GetMaxHealth()*(100+GetMap()->m_mapAttrBonus[EQUIP_ATTR_MAX_HEALTH])/100);
	}

	//��ͼ�⻷�ӳ�
	if (GetMap())
		DoMapBuffBonus(GetMap(),this);

	//����BUFF����
	GetBuffManager()->AddBuffAttr();

	//ϵ������
	Calcul_Coefficient();

	//��ǰѪ���������Ѫ��ʱ��Ҫ����
	uint32 max_hp = GetMaxHealth();
	if (GetHealth() >max_hp)
		SetHealth(max_hp);
	/*uint32 max_mp = GetMaxPower(POWER_MANA);
	if (GetPower(POWER_MANA) >max_mp)
	SetPower(POWER_MANA,max_mp);	*/
}

bool Player::IsReasonableDistancePos(Unit *obj)
{
	if(obj->GetMapId() != GetMapId())
		return false;
	if(GetDistance(obj) > g_Config.max_npc_distance)
		return false;

	return true;
}

void Player::SetSpellCD(uint32 id)
{
	DoSetSpellCD(this, id);		//��lua
}

void Player::resetCombatStateTime()
{
	//�������ս��״̬�� ֪ͨ����ս��
	if (m_combat_state.Passed())
	{
		fightStatusEnter();
	}
	m_combat_state.Reset(g_Config.left_fighting_time);
}

void Player::SetPeaceModeCDIfEnabled() {
	if (this->GetBattleMode() == FAMILY_MODE) {
		uint32 now = (uint32)time(NULL);
		uint32 cd = now + g_Config.peace_mode_cd;
		if (this->GetPeaceModeCD() < now) {
			this->SetPeaceModeCD(cd);
		}
	}
}

void Player::lostExp(uint16 rate) {
	double gf = floor(m_player_exp * rate / 10000);

	// ֪ͨ
	if (gf > 0) {
		Call_exp_update(this->GetSession()->m_delegate_sendpkt, (int32)-gf, (uint8)0);
	}

	m_player_exp -= gf;
	m_session->SetExp();
}

void Player::DoIfNeedAddProtectBuff() {
	if (m_session->isNeedProtectedBuff()) {
		m_buff_manager->AddBuff(BUFF_DEATH_PROTECTED, BUFF_DEFAULT_EFFECT_ID_DEATH_PROTECTED, g_Config.dead_protect_CD);
		m_session->SetNeedProtectedBuff(0);
	}
}

//�Ƿ���PVP״̬��
void Player::resetPVPStateTime()
{
	m_PVP_state.Reset(g_Config.left_fighting_time);	
}

void Player::SetCurSpell(uint32 id)
{
	m_cur_spell = id;
	auto it = m_spell_level.find(id);
	if (it != m_spell_level.end()) {
		m_cur_spell_lv = it->second;
	}
}

void Player::DelPet(Creature *unit)
{
	if(m_pets.empty())
		return;
	m_pets.erase(std::remove(m_pets.begin(),m_pets.end(),unit));
}

void Player::DelPet(uint32 entry)
{
	PetVec::iterator iter = m_pets.begin();
	for (; iter != m_pets.end(); ++iter)
	{
		if ((*iter)->GetEntry() == entry)
		{
			GetMap()->ToDelCreature(*iter);
			break;
		}
	}
}

void Player::AddPet(Creature *unit)
{
	if (!unit)
	{
		tea_perror("AddPet unit is nil");
		return;
	}
	
	//ASSERT(std::count(m_pets.begin(),m_pets.end(),unit) == 0);
	if (std::count(m_pets.begin(),m_pets.end(),unit) != 0)
	{
		tea_perror("AddPet unit guid = %s", unit->GetGuid().c_str());
		return;
	}
	
	m_pets.push_back(unit);
}

Unit* Player::FindNPC(const uint32 npc_entry)
{
	for (auto grid:m_grid->notice_grid)
	{
		for (auto unit:grid->creatures)
		{
			if(unit->GetEntry() == npc_entry && static_cast<Creature*>(unit)->isServiceProvider())
				return unit;
		}		
	}
	return nullptr;
}
////////////////////////////////////////////////////////////////////////////
//FOR LUA

//��ȡ�Ự,ͬʱҲ��������������ݶ���
int Player::LuaGetSession(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 1);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!player || !player->m_session)
	{
		lua_pushnil(scriptL);
		return 1;
	}
	lua_pushlightuserdata(scriptL, player->m_session);
	return 1;
}

//��ѯĳ����״̬
int Player::LuaGetQuestStatus(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 questid = (uint32)LUA_TONUMBER(scriptL, 2);
	if(!player || !player->GetQuestMgr())
	{
		lua_pushnil(scriptL);
		return 1;
	}
	lua_pushnumber(scriptL,(uint32)player->GetQuestMgr()->GetQuestStatus(questid));
	return 1;
}

//��������
int Player::LuaAcceptQuest(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	if(n < 2)
	{
		tea_perror("LuaAcceptQuest ����Ҫ�ṩ2������");
		return 0;
	}
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);	
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaAcceptQuest player nil");
		lua_pushboolean(scriptL,FALSE);
		return 1;
	}
	uint32 questid = (uint32)LUA_TONUMBER(scriptL, 2);	
	uint16 slot = player->m_questMgr->FindQuestSlot(0);

	if(slot >= MAX_QUEST_LOG_SIZE)
	{
		tea_pdebug("LuaAcceptQuest û�������λ");
		lua_pushboolean(scriptL,FALSE);
		return 1;
	}

	//�����ѽӻ�������ģ����Ч
	slot = player->m_questMgr->FindQuestSlot(questid);
	if(slot < MAX_QUEST_LOG_SIZE || !quest_template_db[questid])
		lua_pushboolean(scriptL,FALSE);
	else
	{
		player->m_questMgr->AddQuest(quest_template_db[questid]);
		lua_pushboolean(scriptL,TRUE);
	}
	return 1;
}

//�Ƿ�������
int Player::LuaHasQuest(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	if(n != 2)
	{
		tea_perror("LuaHasQuest Ҫ�ṩ2������");
		return 0;
	}
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 questid = (uint32)LUA_TONUMBER(scriptL, 2);
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaHasQuest player nil");
		return 0;
	}
	uint16 slot = player->m_questMgr->FindQuestSlot(questid);

	lua_pushboolean(scriptL,(slot >= MAX_QUEST_LOG_SIZE)?FALSE : TRUE);
	return 1;
}

//����������������id(������)
int Player::LuaPrintSlotQuest(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (player && player->m_questMgr)
	{
		player->m_questMgr->PintSlotQuests();
	}
	
	return 0;
}

//�Ƿ���ĳ�������͵�����
int Player::LuaHasQuestType(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	if(n != 2)
	{
		tea_perror("LuaHasQuestType Ҫ�ṩ2������");
		lua_pushboolean(scriptL, FALSE);
		return 1;
	}
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaHasQuestType player nil");
		lua_pushboolean(scriptL, FALSE);
		return 1;
	}
	int32 quest_type = (int32)LUA_TONUMBER(scriptL, 2);
	
	for ( uint16 i = 0; i < MAX_QUEST_LOG_SIZE; ++i )
	{
		if ( player->m_questMgr->GetQuestSlotQuestId(i) != 0 )
		{
			quest_template const* qInfo = quest_template_db[player->m_questMgr->GetQuestSlotQuestId(i)];
			if(qInfo && qInfo->quest_type == quest_type)
			{
				lua_pushboolean(scriptL, TRUE);
				return 1;
			}
		}
	}	

	lua_pushboolean(scriptL, FALSE);
	return 1;
}

//��ɵ�ǰָ�����͵�����
int Player::LuaCompleteCurQuest(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaCompleteCurQuest player nil");
		return 0;
	}
	int32 quest_type = (int32)LUA_TONUMBER(scriptL, 2);
	uint8 all_flag = 0;
	if(n >= 3)
	{
		all_flag = (uint8)LUA_TONUMBER(scriptL, 3);
	}


	for ( uint16 i = 0; i < MAX_QUEST_LOG_SIZE; ++i )
	{
		if ( player->m_questMgr->GetQuestSlotQuestId(i) != 0 )
		{
			quest_template const* qInfo = quest_template_db[player->m_questMgr->GetQuestSlotQuestId(i)];
			if(qInfo->quest_type == quest_type)
			{
				int32 quest_id = qInfo->id;
				//���������������飬���ӣ���Ԫ��
				DoQuestRewardScript(player, quest_id, qInfo->rew_xp, qInfo->rew_silver, qInfo->rew_gift, qInfo->rew_gold, all_flag, qInfo->special_flags); 
				player->GetQuestMgr()->SetQuestSlot(i, 0);
				if(player->GetSession())
					Call_questgetter_complete(player->GetSession()->m_delegate_sendpkt, quest_id);
				break;
			}
		}
	}	
	return 0;
}

//��ɵ�ǰָ�����͵�����
int Player::LuaCompleteQuestId(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaCompleteCurQuest player nil");
		return 0;
	}
	uint32 questid = (uint32)LUA_TOINTEGER(scriptL, 2);
	uint16 slot = player->m_questMgr->FindQuestSlot(questid);
	if(slot < MAX_QUEST_LOG_SIZE)
	{
		uint32 state = player->m_questMgr->GetQuestSlotState(slot);
		if(state != QUEST_STATUS_COMPLETE)
			player->m_questMgr->CompleteQuest(questid);
	}
	return 0;
}


//ȡ������Ҫ�������
int Player::LuaGetQuestCounter(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);	
	uint16 questid = (uint16)LUA_TONUMBER(scriptL, 2);
	uint8 counter = (uint8)LUA_TONUMBER(scriptL, 3);
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaGetQuestCounter player nil");
		return 0;
	}
	uint16 slot = player->m_questMgr->FindQuestSlot(questid);

	//���񲻴���
	if(slot >= MAX_QUEST_LOG_SIZE)
	{
		tea_pwarn("LuaGetQuestCounter ���:%s,����%u������",player->GetGuid().c_str(), questid);
		lua_pushnil(scriptL);		
	}
	else
	{
		//���ṩ�Ĳ������ڵ���4��ʱ����������
		if(n >= 4)
		{
			uint16 count = (uint8)LUA_TOINTEGER(scriptL,4);
			player->m_questMgr->SetQuestSlotCounter(slot,counter,count);
			lua_pushnil(scriptL);
		}
		else
		{
			uint16 count = player->m_questMgr->GetQuestSlotCounter(slot,counter);
			lua_pushnumber(scriptL, count);
		}
	}
	return 1;

}

int Player::LuaAddQuestItem(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT( n == 3);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 entry = (uint16)LUA_TONUMBER(scriptL, 2);
	int count = (int)LUA_TOINTEGER(scriptL, 3);			//�ɼӿɼ�
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaAddQuestItem player nil");
		return 0;
	}
	player->m_questMgr->AddQuestItem(entry,count);
	return 0;
}

int Player::LuaRemoveQuestItem(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT( n == 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 entry = (uint16)LUA_TONUMBER(scriptL, 2);
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaRemoveQuestItem player nil");
		return 0;
	}
	player->m_questMgr->PopQuestItemSlot(entry);
	return 0;
}

int Player::LuaClearQuestSlotItem(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT( n == 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 quest_id = (uint16)LUA_TONUMBER(scriptL, 2);
	if(!player || !player->m_questMgr)
	{
		tea_pdebug("error : LuaClearQuestSlotItem player nil");
		return 0;
	}
	player->m_questMgr->ClearQuestSlotItem(quest_id);
	return 0;
}

int Player::LuaTalkedToCreature(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	Unit *npc = (Unit*)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit);

	if (!player || !npc)			
		return 0;	

	player->GetQuestMgr()->TalkedToCreature(npc->GetEntry(),npc->GetGuid());
	return 0;
}

//���������±����
int Player::LuaAddQuestItemBySlot(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 4);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 questid = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 sum = (uint32)LUA_TONUMBER(scriptL, 3);
	uint32 max_sum = (uint32)LUA_TONUMBER(scriptL, 4);
	if (!player)			
		return 0;	
	uint16 slot = player->GetQuestMgr()->FindQuestSlot(questid);
	if(max_sum < player->GetQuestMgr()->GetQuestSlotCounter(slot,0))
		return 0;
	if(slot >= MAX_QUEST_LOG_SIZE)
		return 0;
	player->GetQuestMgr()->AddQuestItemBySlot(questid,0,sum);
	return 0;
}

//��ȡ����cd
int Player::LuaGetSpellCD(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);
	uint32 spell_id = (uint32)LUA_TONUMBER(scriptL, 2);
	auto it = player->m_spell_cd.find(spell_id);

	uint32 cd = 0;
	if(it != player->m_spell_cd.end()) {
		cd = it->second;
	}

	if (cd == 0) {
		it = player->m_importance_spell_cd.find(spell_id);
		if (it != player->m_importance_spell_cd.end()) {
			cd = it->second;
		}
	}

	lua_pushinteger(scriptL, cd);
	return 1;
}

//���ü���cd
int Player::LuaSetSpellCD(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);
	uint32 spell_id = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 spell_cd = (uint32)LUA_TONUMBER(scriptL, 3);
	player->m_spell_cd[spell_id] = spell_cd;

	return 0;
}

//������Ҫ����cd
int Player::LuaSetImportanceSpellCD(lua_State* scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);
	uint32 spell_id = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 spell_cd = (uint32)LUA_TONUMBER(scriptL, 3);
	player->m_importance_spell_cd[spell_id] = spell_cd;
	//printf("id = %u, cd = %u\n", spell_id, spell_cd);
	return 0;
}

//��ü��ܵȼ�
int Player::LuaGetSpellLevel(lua_State* scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);
	uint32 spell_id = (uint32)LUA_TONUMBER(scriptL, 2);
	auto it = player->m_spell_level.find(spell_id);

	uint32 level = 0;
	// �Ȳ�ѯ�����ͷ�ŭ����
	if(it != player->m_spell_level.end()) {
		level = it->second;
	}

	lua_pushinteger(scriptL, level);

	return 1;
}

int Player::LuaSetSpellLevel(lua_State* scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);
	uint32 spell_id = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 level = (uint32)LUA_TONUMBER(scriptL, 3);
	player->m_spell_level[spell_id] = level;

	return 0;
}

//��ô�����ʼʱ��
int Player::LuaGetDaZuoStartTime(lua_State* scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);

	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);

	lua_pushnumber(scriptL, player->daZuoStartTimestamp);

	return 1;
}

//���ô�����ʼʱ��
int Player::LuaSetDaZuoStartTime(lua_State* scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);
	player->daZuoStartTimestamp = (double)LUA_TONUMBER(scriptL, 3);

	return 0;
}	

int Player::LuaAreaExploredOrEventHappens(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 quest_id = (uint32)LUA_TONUMBER(scriptL, 2);

	if (!player || quest_id==0)			
		return 0;	

	player->GetQuestMgr()->AreaExploredOrEventHappens(quest_id);
	return 0;
}

//�����Ʒ
int Player::LuaAddItem(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	if(n < 5)
	{
		tea_perror("LuaAddItem n<5 ");
		return 0;
	}
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!player)
	{
		tea_perror("LuaAddItem player nil ");
		return 0;
	}
	uint32 item_id = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 count = (uint32)LUA_TONUMBER(scriptL, 3);
	uint8 is_bind = (uint8)LUA_TONUMBER(scriptL, 4);
	uint8 op_type = (uint8)LUA_TOINTEGER(scriptL, 5);

	uint32 streng_level  =  0;
	if(n >= 6)
		streng_level = (uint32)LUA_TONUMBER(scriptL, 6);
	if(player->GetSession() && player->GetQuestMgr())
		player->GetQuestMgr()->quest_add_rew_item(player->GetSession()->GetGuid(),item_id,count,is_bind, streng_level,0,op_type);
	return 0;
}

//����
int Player::LuaUpgrade(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!player)
	{
		lua_pushboolean(scriptL, FALSE);
		return 1;
	}
	uint32 prevLevel = player->GetLevel();
	uint8 need_clear_exp = 0;
	if (n>1)
		need_clear_exp = (uint8)LUA_TONUMBER(scriptL, 2);
	if(!player->Upgrade())
	{
		lua_pushboolean(scriptL, FALSE);
		return 1;
	}
	if (need_clear_exp && player->GetSession())
	{
		player->m_player_exp = 0;
		player->GetSession()->SetExp();
	}
	player->Upgrade_Calculate(prevLevel);
	lua_pushboolean(scriptL, TRUE);	
	return 1;
}

int Player::LuaTeleport(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);	
	ASSERT(n >= 4);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 map_id  = (uint32)LUA_TONUMBER(scriptL, 2);
	float to_x = (float)LUA_TONUMBER(scriptL, 3);
	float to_y = (float)LUA_TONUMBER(scriptL, 4);
	uint32 lineNo = 0;	
	if(n >= 5)
		lineNo = (uint32)LUA_TOINTEGER(scriptL, 5);
	
	if (!player)
		return 0;

	if (map_id == 0 || to_x == 0 || to_y == 0)
	{
		tea_perror("LuaTeleport map_id = 0 guid = %s", player->GetGuid().c_str());
		return 0;
	}
	
	string teleport_id = "";
	if(n >= 6 )
		teleport_id = LUA_TOSTRING(scriptL, 6);
	
	if (player->isAlive() && player->GetSession())		
		player->GetSession()->Teleport(to_x,to_y,map_id,teleport_id,lineNo);
	//���ͺ����ʲô�£�����ȡ��������
	DoPlayerTeleport(player);

	return 0;
}

//��ô���id
int Player::LuaGetTeleportID(lua_State* scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);	
	ASSERT(n == 1);
	
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	lua_pushstring(scriptL, player->m_session->GetTeleportGuid().c_str());

	return 1;
}

//TODO:���Խ���ϵ������
void Player::Calcul_Coefficient()
{
	//SetMaxHealth((uint32)(GetMaxHealth()*GetCoefficient().hp_multiples/100));
	//SetMaxPower(POWER_MANA,(uint32)(GetMaxPower(POWER_MANA)*GetCoefficient().mp_multiples/100));
	/*SetOutDamage((uint32)(GetOutDamage()*GetCoefficient().attack_multiples/100));
	SetInDamage((uint32)(GetInDamage()*GetCoefficient().attack_multiples/100));
	SetOutArmor((uint32)(GetOutArmor()*GetCoefficient().def_multiples/100));
	SetInArmor((uint32)(GetInArmor()*GetCoefficient().def_multiples/100));*/
	//��ʼ�����ٺ��ƶ��ٶ�
	//SetMoveSpeed((uint8)(GetMoveSpeed()*100/GetCoefficient().speed_multiples));
	//������������
	//SetCombatRate(COMBAT_RATE_EVA,(uint32)(GetCombatRate(COMBAT_RATE_EVA)*GetCoefficient().eva_multiples/100));
	//SetCombatRate(COMBAT_RATE_CRIT,(uint32)(GetCombatRate(COMBAT_RATE_CRIT)*GetCoefficient().crit_multiples/100));
}

// �滻����
void Player::slotReplaceSpell(uint8 slot, uint16 spell, uint8 level) {

	bool vist = false;

	//ɾ����ǰ��
	if (slot > 1) {
		for(auto it = m_slot_spell.lower_bound(slot);
				it != m_slot_spell.upper_bound(slot); ++ it) {

			uint16 spellId = it->second;
			//��ɾ������������Ϣ�б�
			m_spell_level.erase(spellId);
		}
		vist = true;
	}

	//ɾ�����ܲ�����
	if (vist) {
		m_slot_spell.erase(slot);
	}
	m_slot_spell.insert(std::make_pair(slot, spell));

	// ��������
	m_spell_level[spell] = level;
}

void Player::SetPeaceModeCD(uint32 cd) {
	if (GetSession()->GetUInt32(PLAYER_FIELD_PEACE_MODE_CD) != cd) {
		GetSession()->SetUInt32(PLAYER_FIELD_PEACE_MODE_CD, cd);
		GetSession()->Call_Peace_Mode_CD((uint8)g_Config.peace_mode_cd);
	}
}

uint32 Player::GetPeaceModeCD() {
	return GetSession()->GetUInt32(PLAYER_FIELD_PEACE_MODE_CD);
}

uint16 Player::GetBattleMode() {
	return GetSession()->GetUInt16(PLAYER_FIELD_NOTORIETY, 0);
}

void Player::SetBattleMode(uint16 mode) {
	GetSession()->SetUInt16(PLAYER_FIELD_NOTORIETY, 0, mode);
}

//ϵ������
void Player::SetCoefficient(string str,uint16 multiples)
{
	if (multiples==0)
		return;	
	if (str == "Speed")//�ٶ�
	{
		//�����屶�ٶ�
		if(multiples>500 || multiples==0)
			return;
		m_coefficent.speed_multiples = multiples;
	}
	else if (str == "EXP")//����
	{
		if(multiples>10000 || multiples==0)
			return;
		m_coefficent.exp_multiples = multiples;
	}
	else if (str == "BurstRate")//����
	{
		if(multiples>10000 || multiples==0)
			return;
		m_coefficent.drop_rate_multiples = multiples;
	}
	else if (str == "Damage" || multiples==0)//����
	{
		if(multiples>10000)
			return;
		m_coefficent.attack_multiples = multiples;
	}
	else if (str == "DEF" || multiples==0)//����
	{
		if(multiples>10000)
			return;
		m_coefficent.def_multiples = multiples;
	}
	else if (str == "Hit" || multiples==0)//����
	{
		if(multiples>10000 || multiples==0)
			return;
		m_coefficent.waza_multiples = multiples;
	}
	else if (str == "Eva" || multiples==0)//����
	{
		if(multiples>10000 || multiples==0)
			return;
		m_coefficent.eva_multiples = multiples;
	}
	else if (str == "HP")//����
	{
		if(multiples>10000 || multiples==0)
			return;
		m_coefficent.hp_multiples = multiples;
	}
	else if (str == "MP")//����
	{
		if(multiples>10000 || multiples==0)
			return;
		m_coefficent.mp_multiples = multiples;
	}
	else if (str == "Crit")//����
	{
		if(multiples>10000 || multiples==0)
			return;
		m_coefficent.crit_multiples = multiples;
	}
	else if (str == "FullProperty")//ȫ����
	{
		if(multiples>10000 || multiples==0)
			return;
		m_coefficent.attack_multiples = multiples;
		m_coefficent.def_multiples = multiples;
		m_coefficent.waza_multiples = multiples;
		m_coefficent.hp_multiples = multiples;
		m_coefficent.mp_multiples = multiples;
		m_coefficent.crit_multiples = multiples;
	}
}

#include <server/internal_callback.h>

//��ȡ������
int Player::LuaGetCounters(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Player *player = (Player *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!player)
	{
		tea_pdebug("LuaGetCounters player = NULL");
		lua_pushnil(scriptL);
		return 0;
	}
	lua_newtable(scriptL);
	uint32 i = 1;
	//vector<int> playerGuid;
	for(CounterMap::iterator iter = player->m_counter_map.begin();
		iter != player->m_counter_map.end();++iter)
	{
		lua_pushnumber(scriptL, i);   /* Push the table index */
		lua_pushstring(scriptL,iter->first.c_str());
		lua_rawset(scriptL, -3);      /* Stores the pair in the table */
		//playerGuid.push_back(iter->first);
		i++;
	}
	return 1;
}

//������С��
int Player::LuaClearPets(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Player *player = (Player *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!player)
	{
		tea_perror("LuaClearPets player is null");
		return 0;
	}

	for(auto it = player->m_pets.begin(); it != player->m_pets.end();++it)
	{
		(*it)->SetClearTimer(1);
	}
	return 0;
}


int Player::LuaIsInSaveArea(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!player)
	{
		tea_perror("LuaIsInSaveArea player is null");	
		return 0;
	}
	lua_pushnumber(scriptL,player->isInSafeArea()?1:0);
	return 1;
}

bool Player::IsCounter(const Unit * unit)
{
	//����ģʽ
	if (m_counter_map.find(unit->GetGuid()) != m_counter_map.end())
		return true;
	return false;
}

int Player::LuaIsCounter(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	Player *target = (Player*)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit);
	if (!player || !target)
	{
		tea_perror("LuaIsCounter Player is null");
		return 0;
	}
	//�ж��Ƿ񷴻�ģʽ
	lua_pushnumber(scriptL,player->IsCounter(target)?1:0);	
	return 1;
}


//��ȡ��ҵ�ǰ��ս��״̬
int Player::LuaGetPlayeCurFightStatus(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!player)
	{
		tea_perror("LuaGetPlayeCurFightStatus Player is null or target is null");
		return 0;
	}
	int status = player->GetCurFightStatus();
	lua_pushnumber(scriptL, status);

	return 1;
}

//�ж�����Ƿ��Ѿ���¼������
int Player::LuaIsLogined(lua_State* scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!player)
	{
		tea_perror("LuaIsLogined Player is null");
		return 0;
	}

	lua_pushboolean(scriptL, player->GetSession()->GetStatus() == STATUS_LOGGEDIN);

	return 1;
}

//��ȡ��Ҹ�ϵͳ������
int Player::LuaGetEquipAttrs(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player->GetTypeId() == TYPEID_PLAYER);
	if (!player)
	{
		lua_pushnil(scriptL);
		return 1;
	}	
	if (player->GetEquipAttrs())
	{
		lua_pushlightuserdata(scriptL, player->GetEquipAttrs());
	}
	else
	{
		lua_pushnil(scriptL);
	}
	
	return 1;
}

//��þ���
int Player::LuaAddExp(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	//ASSERT(n == 2);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 exp = (uint32)LUA_TONUMBER(scriptL, 2);
	if (!player)
	{
		return 0;
	}
	uint8 add_type = 0;
	if ( n>2)
	{
		add_type = (uint8)LUA_TONUMBER(scriptL, 3);
	}
	if (exp > 0)
	{
		player->GainExp(exp,add_type);
	}
	
	return 0;
}

//�۾���
int Player::LuaSubExp(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);

	Player* player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!player || !player->GetSession())
	{
		tea_pdebug("error: LuaSubExp  player == null");
		lua_pushboolean(scriptL, FALSE);
		return 1;
	}
	double sub_exp = (double)LUA_TONUMBER(scriptL, 2);
	if (player->GetExp() < sub_exp)
	{
		lua_pushboolean(scriptL, FALSE);
		return 1;
	}

	player->m_player_exp -= sub_exp;
	player->GetSession()->SetExp();
	lua_pushboolean(scriptL, TRUE);

	// ֪ͨ
	if (sub_exp > 0) {
		Call_exp_update(player->GetSession()->m_delegate_sendpkt, (int32)-sub_exp, (uint8)0);
	}
	return 1;
}

//����ϵ��
int Player::LuaSetCoefficient(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 3);
	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	const char *str = LUA_TOSTRING(scriptL, 2);
	uint32 value = (uint32)LUA_TOINTEGER(scriptL, 3);
	if (!player)
	{
		return 0;
	}
	
	player->SetCoefficient(str, value);

	return 0;
}

//֪ͨӦ�÷�����money
int Player::LuaSendAddMoney(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 4);
	Player* player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint8 money_type = (uint8)LUA_TONUMBER(scriptL,2);
	uint8 opt_type = (uint8)LUA_TONUMBER(scriptL,3);
	double val = LUA_TONUMBER(scriptL, 4);

	string relateItemIds = "";
	string relateItemNums = "";
	if(n >= 5)
		relateItemIds = LUA_TOSTRING(scriptL, 5);
	if(n >= 6)
		relateItemNums = LUA_TOSTRING(scriptL, 6);

	if (player && player->GetSession()) {
		ScenedApp::g_app->call_player_addmoney(player->GetSession()->GetGuid(),money_type, opt_type, val, relateItemIds, relateItemNums);
	}

	return 0;
}

//֪ͨӦ�÷���money
int Player::LuaSendSubMoney(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 4);
	Player* player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint8 money_type = (uint8)LUA_TONUMBER(scriptL,2);
	uint8 opt_type = (uint8)LUA_TONUMBER(scriptL,3);
	int val = (int)LUA_TONUMBER(scriptL, 4);

	string relateItemIds = "";
	string relateItemNums = "";
	if(n >= 5)
		relateItemIds = LUA_TOSTRING(scriptL, 5);
	if(n >= 6)
		relateItemNums = LUA_TOSTRING(scriptL, 6);

	if (player && player->GetSession()) {
		ScenedApp::g_app->call_player_submoney(player->GetSession()->GetGuid(),money_type, opt_type, val, relateItemIds, relateItemNums);
	}

	return 0;
}

//֪ͨӦ�÷���������
int Player::LuaSendRecalculate(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Player* player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (player && player->GetSession())
	{
		ScenedApp::g_app->call_recalculate(player->GetSession()->GetGuid());	
	}
	return 0;
}

//������ҵĳ����б�
int Player::LuaGetPetTable(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);

	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	Player *player = dynamic_cast<Player*>(unit);
	if(player)
	{
		PetVec &v = player->m_pets;

		lua_newtable(scriptL);    /* We will pass a table */
		int i = 0;

		for (PetVec::iterator iter = v.begin(); iter != v.end(); ++iter)
		{
			lua_pushnumber(scriptL, i+1);   /* Push the table index */
			lua_pushlightuserdata(scriptL, *iter);	
			lua_rawset(scriptL, -3);      /* Stores the pair in the table */
			i++;
		}
	}

	return 1;
}

//�������㿪��
int Player::LuaSetCanRecalcuAttr(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);

	int t_idx = lua_gettop(scriptL);
	ASSERT(t_idx == 2);
	Player* player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	player->m_can_calcul_attr = (int)LUA_TOBOOLEAN(scriptL, 2) != 0;	

	return 0;
}

//������
int Player::LuaAddGiftPacks(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 9);
	string player_guid = (string)LUA_TOSTRING(scriptL, 1);
	uint32 id = (uint32)LUA_TOINTEGER(scriptL, 2);
	uint32 gift_type = (uint32)LUA_TOINTEGER(scriptL, 3);
	uint32 start_time = (uint32)LUA_TOINTEGER(scriptL, 4);
	uint32 end_time = (uint32)LUA_TOINTEGER(scriptL, 5);
	string gift_name = (string)LUA_TOSTRING(scriptL, 6);
	string gift_desc = (string)LUA_TOSTRING(scriptL, 7);
	string item_config = (string)LUA_TOSTRING(scriptL, 8);
	string item_from = (string)LUA_TOSTRING(scriptL, 9);
	ScenedApp::g_app->call_add_gift_packs(player_guid, id,gift_type, start_time, end_time,gift_name, gift_desc, item_config, item_from);

	return 0;
}

//��ӹ۲���
int Player::LuaAddWatcher(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);

	Player* player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	string watcher_guid = LUA_TOSTRING(scriptL, 2);
	if (!player || !player->GetSession() || watcher_guid.empty())
		return 0;

	//���ҹ۲����ڲ�����
	Player* watcher = ObjMgr.FindPlayer(watcher_guid);
	if (!watcher || !watcher->GetSession())
		return 0;	

	Map *map = watcher->GetMap();
	if (!map)
		return 0;
	
	if ( map->GetGridManager()->AddWatcher(player->GetSession()->GetFD(), watcher_guid, map->GetMapId(), map->GetInstanceID()) )
	{//���µ�ͼ������
		map->SendCreateBlock(player->GetSession());
	}

	return 0;
}


//��ȡ���һ��ʹ�õļ������еļ���id
int Player::LuaGetSpellStyle(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);

	uint32 spell_group = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 lastSpellId = 0;

	auto it = player->m_spell_style.find(spell_group);
	if(it != player->m_spell_style.end()) {
		lastSpellId = it->second;
	}

	lua_pushinteger(scriptL, lastSpellId);
	return 1;
}

//�������һ��ʹ�õļ������еļ���id
int Player::LuaSetSpellStyle(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);

	uint32 spellGroup = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 spellId = (uint32)LUA_TONUMBER(scriptL, 3);

	player->m_spell_style[spellGroup] = spellId;
	
	return 0;
}

//��ȡĳһ��λ����
int Player::LuaGetSlotSpell(lua_State* scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);
	uint32 slot = (uint32)LUA_TONUMBER(scriptL, 2);

	auto it = player->m_slot_spell.find(slot);
	uint32 spellId = 0;
	if (it != player->m_slot_spell.end()) {
		spellId = it->second;
	}

	lua_pushnumber(scriptL, spellId);

	return 1;
}

//�������
int Player::LuaSendMountJumpDown(lua_State* scriptL) {

	//CHECK_LUA_NIL_PARAMETER(scriptL);
	//int n = lua_gettop(scriptL);
	//ASSERT(n == 2);

	//Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	//ASSERT(player);

	//uint8 state = (uint8)LUA_TONUMBER(scriptL, 2);

	//// ״̬һ����û��Ҫ������
	//if (player->GetByte(UNIT_FIELD_MOUNT_LEVEL, 2) == state)
	//	return 0;

	//player->SetByte(UNIT_FIELD_MOUNT_LEVEL, 2, state);

	////TODO: �������� �����ٶ������������
	//player->Calcul_Attr();

	return 0;
}

//�������侭��
int Player::LuaLostExpOnDead(lua_State* scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);

	uint16 rate = (uint16)LUA_TONUMBER(scriptL, 2);
	player->lostExp(rate);

	return 0;
}

int Player::LuaSetNeedProtectBuff(lua_State* scriptL) {
	
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);

	player->GetSession()->SetNeedProtectedBuff(1);

	return 0;
}

//���͵����������н����߼��ж�
int Player::LuaSendToAppdDoSomething(lua_State* scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 3);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);

	uint32 type = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 id   = (uint32)LUA_TONUMBER(scriptL, 3);

	string str = "";
	if (n == 4) {
		str = (string)LUA_TOSTRING(scriptL, 4);
	}
	ScenedApp::g_app->call_player_do_something(player->GetSession()->GetGuid(), type, id, str);

	return 0;
}

int Player::LuaSendToAppdAddOfflineMail(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	string player_guid = (string)LUA_TOSTRING(scriptL, 1);
	string mail_info = (string)LUA_TOSTRING(scriptL, 2);
	ScenedApp::g_app->call_add_offline_mail(player_guid, mail_info);
	return 0;
}

//��ȡ���������
int Player::LuaGetAllPlayerNearBy(lua_State *scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Player *player = (Player*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(player);

	lua_newtable(scriptL);    /* We will pass a table */
	int i = 0;
	for (auto grid:player->GetGrid()->notice_grid) {
		
		for (auto n_player:grid->players) {

			lua_pushnumber(scriptL, i+1);   /* Push the table index */
			lua_pushlightuserdata(scriptL, n_player);	
			lua_rawset(scriptL, -3);      /* Stores the pair in the table */
			i++;
		}
	}

	return 1;
}

int Player::LuaSetPlayerEnterOrigin(lua_State *scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 4);

	Player *player = (Player *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 mapid = (uint32)LUA_TONUMBER(scriptL, 2);
	uint32 x = (uint32)LUA_TONUMBER(scriptL, 3);
	uint32 y = (uint32)LUA_TONUMBER(scriptL, 4);

	player->m_session->SetToDBPositon(mapid, (float)x, (float)y);
	return 0;
}

int Player::LuaGetPlayerGuid(lua_State* scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Player *player = (Player *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (player) {
		lua_pushstring(scriptL, player->m_session->GetGuid().c_str());
	} else {
		lua_pushnil(scriptL);
	}

	return 1;
}