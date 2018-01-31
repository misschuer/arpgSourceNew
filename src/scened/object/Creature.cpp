#include "Creature.h"
#include "Map.h"
#include <shared/storage_loader.h>
#include "BuffManager.h"
#include "LootManager.h"
#include "QuestGetter.h"
#include "scened_scripts.h"

//#define UPDATE_OWNERSHIP_TIME 1500	//���¹��������ߵļ��sp

Creature::Creature() : m_threat_move_type(0),m_reactState(REACT_PASSIVE),	m_move_type(0),evade_state(false),
	m_timer_say(-1),m_timer_threat(UPDATE_THREAT_TIMER),body_miss(0),
	m_update_ownership_timer(g_Config.update_ownership_time),
	m_bornX(0.0f),m_bronY(0.0f),m_respawn_time(-1),nextSpellCD(0),
	m_clear_timer(0),m_motion_timer_diff(0),m_motion_timer(250)
{
	Unit::SetCanActiveGrid(false);

	m_script_name = "";

	//��ͨ������CD��
	m_spells_cd.push_back(0);
}

Creature::~Creature()
{
	while(!m_impl.empty())
	{
		MovementGenerator *curr = m_impl.top();
		delete curr;
		m_impl.pop();	
	}
	for_each(m_expire_impl.begin(),m_expire_impl.end(),safe_delete);
	for(SpellAIMap::iterator it = m_spells.begin(); it != m_spells.end(); ++it)
	{
		std::vector<spell_cast_probability*> elements = it->second;
		for (auto spell : elements) {
			free(spell);
		}
	}
}

bool Creature::Create(Map *map, const string &guidlow, uint32 entry,uint32 respan_tm,uint32 movetype,const char *ainame,uint32 level, uint32 attackType/* = 0*/)
{	
	//m_born_info = born_info;
	//�È������B��ID����λGUID
	uint32 midlle_guid = ScenedApp::g_app->Get_Connection_ID();
	Unit::_Create(guidlow,midlle_guid);
	SetTypeId(TYPEID_UNIT);
	//ģ�崫0����Ϊ��ֻ��������ʼ��value�ֶε�
	if (entry==0)
		return true;
	//������λID�����ų���������ID�ˣ�ENTRY��_Create���õģ�������Ҫ��������һ��
	SetEntry(entry);
	SetLevel(level);

	SetDeathState(DEATH_STATE_ALIVE);
	//���ó���Ϊ����
	SetOrientation(0.5*M_PI);
	//�ƶ�����
//	ASSERT(m_born_info);
	SetMoveType(movetype);
	// ��ʼ�ٶ�
	//SetMoveSpeed(135);
	//AI_id	
	m_respawn_time = respan_tm;	
	//AI�ű�����
	if(ainame && strlen(ainame) > 0)
		m_script_name = ainame;

	if (attackType > 0) {
		this->m_reactState = ReactStates(attackType);
	}

	//�����ʼ��
	DoInitCreatureInfo(this, map);

	return true;
}

void Creature::Initialize()
{
	//��ʼ���ƶ�����	
	MovementGenerator *curr = Tea::SelectMovementGenerator(this);
	curr->Initialize(*this);
	m_impl.push(curr);

	//���ýű���ʼ��,���ʧ�������½��ű��ÿ�
	if (!m_script_name.empty() && DoScriptInit(m_script_name.c_str(),this))		
		m_script_name = "";
		
	//tea_pdebug("%u:[%s] init ai[%s],move_type[%u],reactState[%d]",GetEntry(), GetName(), m_script_name.c_str(), m_move_type, (int)m_reactState);
	m_timer_say.Reset(urand(2000,240000));	

	//��ʼ����޹���
	//creature_template& data = GetTemplate();	
	
	m_threatMgr.Initialize(this, 0, 0);	
	creatureInit(this);
}

void Creature::SetCanActiveGrid(bool status)
{
	Unit::SetCanActiveGrid(status);
}

void Creature::Update(uint32 diff)
{
	Unit::Update( diff );	
	//����Ѿ�����,һ�ж�����˵��
	if(!isAlive())
		return;

	//ɾ��������жϷ�����ǰ��
	if(CheckCreateTimeOutDel(diff))
		return;
	//����˵��
	//UpdateSaySomething(diff);
	//����������
	UpdateOwnership(diff);
	
	if(m_threat_move_type != IDLE_MOTION_TYPE)
	{
		m_timer_threat.Update(diff);
		if(m_timer_threat.Passed())
		{
			m_threatMgr.Update(UPDATE_THREAT_TIMER);
			m_timer_threat.Reset(UPDATE_THREAT_TIMER);
		}	
	}	

	m_motion_timer_diff += diff;
	m_motion_timer.Update(diff);//���������ƶ���ʱ��
	if(m_motion_timer.Passed())
	{
		m_motion_timer.Reset();	
		UpdateMotion(m_motion_timer_diff);
		m_motion_timer_diff = 0;
	}
}

//���ɾ����Ҫ��ʱɾ���Ĺ���
bool Creature::CheckCreateTimeOutDel(uint32 diff)
{
	if(m_clear_timer.GetInterval() != 0 )
	{
		m_clear_timer.Update(diff);		
		if (m_clear_timer.Passed())
		{
			this->GetMap()->ToDelCreature(this);
			return true;
		}
	}
	return false;
}

void Creature::UpdateLiveStatus(uint32 diff)
{
	//������ʱ��
	if(isAlive())
		return;
	m_live_timer.Update(diff);

	//��ʱ��δ��
	if (!m_live_timer.Passed())
		return;

	//ʬ��״̬�±���Ϊ����״̬
	if(GetDeathState() == DEATH_STATE_CORPSE)
	{
		//�������ʱ��Ϊ0�Ļ�������Ϊ��ֻˢһ��,һ���Ǹ�����
		if (m_respawn_time == 0)
		{
			GetMap()->ToDelCreature(this);
		}
		else
		{			
			SetDeathState(DEATH_STATE_DEAD);
			m_live_timer.Reset(m_respawn_time);
		}		
	}
	else if(GetDeathState() == DEATH_STATE_DEAD)	//����
	{
		Respawn(m_bornX,m_bronY);
		m_live_timer.Reset(0);
	}
}

void Creature::UpdateSaySomething(uint32 diff)
{
	if(!isAlive() || m_script_name.empty())
		return;	
	m_timer_say.Update(diff);
	if (m_timer_say.Passed())
	{
		m_timer_say.Reset(DoSaySomething(m_script_name.c_str(),this));
	}
}

void Creature::UpdateOwnership(uint32 diff)
{
	m_update_ownership_timer.Update(diff);
	if (m_update_ownership_timer.Passed())
	{
		auto player = GetCurOwnership();
		auto *owner = GetOwnship();
		if (!owner && !player)
			SetCurOwnership(0);
		if (owner&&owner->GetUIntGuid()!=player)
			SetCurOwnership(owner->GetUIntGuid());
		m_update_ownership_timer.Reset(g_Config.update_ownership_time);
	}	
}

//ɾ��һ��������
void  Creature::DelOwnerShip(uint32 lguid)
{
	OwnershipVec::iterator iter = m_ownerships.begin();

	for(; iter != m_ownerships.end(); ++iter)
	{
		if(lguid == *iter)
		{
			m_ownerships.erase(iter);
			return;
		}
	}
}

//����һ�������� jzyjzy
void Creature::AddTheOwnership(uint32 lguid)
{
	//�����ظ��Ĺ�����
	OwnershipVec::iterator it = std::find(m_ownerships.begin(), m_ownerships.end(), lguid);

	if(it == m_ownerships.end())
		m_ownerships.push_back(lguid);
}

//��ȡ��ǰ�Ϸ�������
Player* Creature::GetOwnship()
{
	if(!GetMap())
		return NULL;
	for(OwnershipVec::iterator it = m_ownerships.begin();
		it != m_ownerships.end();)
	{
		//�����ߺϷ����жϣ�������������������������--������޴���
		Player *owner = GetMap()->FindPlayer(*it);

		if(!owner ||			
			( GetDistance(owner) >= m_threatMgr.GetActioRadius()))  //����/��޷�Χ
		{
			//it = m_ownerships.erase(it);
			++it;
			continue;
		}
		else
			return owner;
	}
	return NULL;	
}

void Creature::ResetOwnerShip()
{
	m_ownerships.clear();
}

//��ȡ��ǰ�Ϸ�������
void Creature::GetOwnshipTable(vector<Player *>& players)
{
	if(!GetMap())
		return;
	for(OwnershipVec::iterator it = m_ownerships.begin();
		it != m_ownerships.end();)
	{
		//�����ߺϷ����жϣ�������������������������--������޴���
		Player *owner = GetMap()->FindPlayer(*it);

		if(owner &&	( GetDistance(owner) <= m_threatMgr.GetActioRadius()))  //����/��޷�Χ
		{
			players.push_back(owner);
		}
		++it;
	}			
}

//��������
uint32  Creature::GetFinallyExp(Unit *unit)
{	
// 	creature_template *temp = creature_template_db[GetEntry()];
// 	if(!temp)
// 		return 0;
	return DoGetCreatureBaseExp(this, unit);
}

void Creature::SetClearTimer(time_t t)
{
	m_clear_timer.SetInterval(t);
	m_clear_timer.SetCurrent(0);
}

time_t Creature::GetClearTimer()
{
	if(m_clear_timer.Passed())
		return 0;
	return m_clear_timer.GetInterval() - m_clear_timer.GetCurrent();
}

void Creature::UpdateMotion(uint32 diff)
{
	//�Ƿ���Ҫ�ͷ�
	if(!m_expire_impl.empty())
	{
		for_each(m_expire_impl.begin(),m_expire_impl.end(),safe_delete);
		m_expire_impl.clear();
	}	
		
	if(!m_impl.top()->Update(*this,diff) && m_impl.size() > 1)
	{
		MovementGenerator *curr = m_impl.top();
		m_impl.pop();
		curr->Finalize(*this);
		m_expire_impl.push_back(curr);
	}
}

void Creature::OnKilled(Unit* killer, uint16 id)
{
	Unit::OnKilled(killer);	

	uint32 deadtime = this->body_miss;	
	if(killer)	
		this->AI_JustDied(killer, deadtime);
	if (deadtime > 0)
		m_live_timer.Reset(deadtime);	//ʬ�����ʱ��
	else {
		m_live_timer.Reset(1000);	//ʬ�����ʱ��
	}
	//�������ս��Ʒ,
	if(killer)
		LootManager::LootAllot(killer, this, isOneOne());

	this->m_threatMgr.Clear();		//�����ճ��
}

//������������
void Creature::Calcul_Attr()
{
	Unit::Calcul_Attr();
	uint32 cur_health = GetHealth(); //������ﵱǰѪ������������ȫ���ָ���ʼֵ��
	/*
	if (GetMap())
	DoInitCreatureInfo(this, GetMap(), true);
	*/
	//Ѫ
	SetHealth(cur_health);
	
	if (GetMap())
		DoMapBuffBonus(GetMap(),this);

	//BUFF����
	GetBuffManager()->AddBuffAttr();
}

//����Ŀ��
void Creature::MotionMoveTarget()
{
	MovementGenerator *curr = NULL;

	//���ջ���Ѿ��ǳ�Ŀ����,������idle(����ռλ)
	if((m_impl.top()->GetMovementGeneratorType() == m_threat_move_type) 
		|| (m_impl.top()->GetMovementGeneratorType() == IDLE_MOTION_TYPE 
			&& static_cast<IdleMovementGenerator*>(m_impl.top())->m_timer.GetInterval()>0))
		return;

	//���������ж�ջ���ǳ�ʼ���ģ���ô�Ȳ���һ���ؼҵ�
	if(m_impl.size() == 1)
	{
		curr = Tea::SelectMovementGenerator(this,HOME_MOTION_TYPE);
		curr->Initialize(*this);
		m_impl.push(curr);
	}

	//��Ŀ��Ѱ·׷ɱ
	curr = Tea::SelectMovementGenerator(this,MovementGeneratorType(m_threat_move_type));
	//curr = Tea::SelectMovementGenerator(this,TARGET_MOTION_TYPE);
	curr->Initialize(*this);	
	m_impl.push(curr);
}

void Creature::SetEvadeState(bool state)
{
	if(evade_state = state)
	{
		//SetCombatRate(COMBAT_RATE_EVA, 1000);	//������Ϊ100%
		GetBuffManager()->ClearBuff();			//���buff
	}
	else
	{		
		//SetCombatRate(COMBAT_RATE_EVA, data.eva_rate);	//��ԭ��������
		SetHealth(GetMaxHealth());				//��Ѫ
	}
}

float Creature::GetAttackDistance(Unit const* ) const
{
	return GetTemplate().attack_range==0 ? g_Config.nomal_attack_distance : (float)GetTemplate().attack_range;
}

void Creature::SetHostGUID(Unit *unit)
{
	//���ָ��Ϊ�գ���Ϊ��Ҫ������
	if(GetHostGUID())
	{
		Player *player = GetMap()->FindPlayer(GetHostGUID());
		if(player)
		{
			player->DelPet(this);
		}
	}
	if(unit)
	{
		SetOwner(unit->GetGuid());

		//��ӵ������б�
		Player *player = dynamic_cast<Player*>(unit);
		if(player)
		{
			player->AddPet(this);
		}
	}
	else
		SetOwner("");
}

Unit *Creature::GetOwnerUnit()
{
	auto guid = GetHostGUID();
	if(!guid)
		return NULL;
	auto unit = GetMap()->FindUnit(guid);
	return unit;
}

void Creature::AddTheOwnership(Unit *target,Unit *buff_giver)
{
//	ASSERT(target&&buff_giver);
	if (target == NULL || buff_giver == NULL)
	{
		tea_perror("assert error: AddTheOwnership ASSERT(target&&buff_giver)");
		return;
	}
	
	if (target->GetTypeId()==TYPEID_UNIT&&buff_giver->GetTypeId()==TYPEID_PLAYER)
	{
		auto lguid = buff_giver->GetUIntGuid();
		((Creature*)target)->AddTheOwnership(lguid);
	}
}

void Creature::RandomMove(uint32 ms,float x,float y)
{
	Unit::RandomMove(ms,x,y);
	MovementGenerator *m = Tea::SelectMovementGenerator(this,IDLE_MOTION_TYPE);
	m->Initialize(*this,0,ms);
	m_impl.push(m);
}

//�Ƿ��м������и��ʿ�ʩ�ŵ�
bool Creature::HasSpell(uint32 spell_id)
{
	for (SpellAIMap::iterator it =m_spells.begin(); it != m_spells.end(); ++it)
	{
		std::vector<spell_cast_probability*> elements = it->second;
		for (auto spell : elements) {
			if (spell_id !=0 && spell->spell_id != spell_id)
				continue;

			if(spell->spell_probability > 0)
				return true;
		}
	}
	return false;
}

//������CD���������
int Creature::GetSpellGroup()
{
	uint32 curr = ms_time();

	//�ȿ�һ�����������ļ���
	for (uint32 i = m_spells_cd.size()-1; i > 0; -- i)
	{
		uint32 cd = (uint32)m_spells_cd[ i ];
		if (curr >= cd) {
			return i;
		}
	}

	//�ðɣ�������ͨ����
	if(curr >= (uint32)m_spells_cd[ 0 ])
		return 0;
	else
		return -1;
}

//ʹ�ü������Ե�һ���ټ������
void Creature::SpellGroupWait(uint32 group_id, uint32 t /*= 0*/)
{
	ASSERT(group_id != 0);
	if(t == 0)
	{
		m_spells_cd[group_id] = ScenedApp::g_app->GetConfig().nomal_attack_time+ms_time();
	}
	else
	{
		m_spells_cd[group_id] = t+ms_time();
	}
}

//�������	
bool Creature::IsSpellCD(uint32 spellID) 
{
	for(SpellAIMap::iterator it = m_spells.begin(); it != m_spells.end(); ++it)
	{
		std::vector<spell_cast_probability*> elements = it->second;
		for (auto spell : elements) 
		{
			if(spell->spell_id == spellID)
			{
				return m_spells_cd[it->first] > ms_time();
			}
		}
	}
	//tea_perror("%dû�������%d���ﻹ������",this->GetEntry(), spellID);
	ASSERT(false);
	return false;
}

void Creature::SetSpellCD(uint32 spellID)
{
	if(spellID == 0)
	{
		//tea_pdebug("��������CDΪ%u",ScenedApp::g_app->GetConfig().nomal_attack_time);
		for (uint32 i = 0; i < m_spells_cd.size(); i++)
		{
			if(m_spells_cd[i] < ScenedApp::g_app->GetConfig().nomal_attack_time+ms_time())
				m_spells_cd[i] = ScenedApp::g_app->GetConfig().nomal_attack_time+ms_time();
		}
		return;
	}

	for(SpellAIMap::iterator it = m_spells.begin(); it != m_spells.end(); ++it)
	{
		std::vector<spell_cast_probability*> elements = it->second;
		for (auto spell : elements) 
		{
			if(spell->spell_id == spellID)
			{
				uint32 spell_group = it->first;
				ASSERT(m_spells_cd.size() > spell_group);
				uint32 cd = spell->spell_singleCD;
				if((uint32)m_spells_cd[spell_group] < cd + ms_time())
					m_spells_cd[spell_group] = cd + ms_time();
				this->nextSpellCD = ms_time() + spell->spell_nowCDtime;
				//��������ͨ������
				m_spells_cd[0] = ScenedApp::g_app->GetConfig().nomal_attack_time+ms_time();
				return;
			}
		}
	}
}

spell_cast_probability *Creature::RandSpell(float dis)
{
	spell_cast_probability *result = NULL;
	if (ms_time() < this->nextSpellCD) {
		return result;
	}

	int spell_group = GetSpellGroup();
	if(spell_group > 0)
	{
		//tea_pdebug("��%s���氡�氡�氡�氡�氡�氡�氡�氡�氡�氡�氡�氡",creature.GetName());
		auto it = m_spells.find(spell_group);
		if(it != m_spells.end())
		{
			spell_cast_probability* spell = it->second[ 0 ];
			uint32 spell_id = spell->spell_id;
			int target_type = spell->target_type;
			//float spell_distance = it->second->spell_distance + 0.0;
			if(target_type == 0 || dis <= spell->spell_distance || fabs(dis - spell->spell_distance) <= 1E-1) {
				result = spell;
			}

			if (it->second.size() > 1) {
				// �������ݷŵ����
				it->second.erase(it->second.begin());
				it->second.push_back(spell);
			}
			//tea_pinfo("��%s���浽һ�����ܣ�IDΪ%d��", creature.GetName(),it->second->spell_id);
		}
		//if(result == NULL && m_spells.size() > 1)
		//	SpellGroupWait(spell_group);
	}
	return result;
}

//�ı似��CDʱ��
void Creature::ChangeSpellCD(uint32 spellID, uint32 cd)
{
	for(SpellAIMap::iterator it = m_spells.begin(); it != m_spells.end(); ++it)
	{
		std::vector<spell_cast_probability*> elements = it->second;
		for (auto spell : elements) 
		{
			if(spell->spell_id == spellID)
			{
				spell->spell_singleCD = cd;
				return;
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//AI�ӿ�
int Creature::AI_MoveInLineOfSight(Unit *u)
{
	if(m_script_name.empty())
		return false;
	return DoMoveInLineOfSight(m_script_name.c_str(),this,u);
}

void Creature::AI_DamageTaken(Unit *u,double& damage)
{
	if(m_script_name.empty())
		return;
	DoDamageTaken(m_script_name.c_str(),this,u,damage);
}

void Creature::AI_DamageDeal(Unit *u,double damage)
{
	if(m_script_name.empty())
		return;
	DoDamageDeal(m_script_name.c_str(),this,u,damage);
}

void Creature::AI_GiveDamage(Unit *u,double& damage)
{
	if(m_script_name.empty())
		return;
	DoGiveDamage(m_script_name.c_str(),this,u,damage);
}

void Creature::AI_JustDied(Unit *killer, uint32 &deadtime)
{
	if(m_script_name.empty())
		return;
	DoJustDied(m_script_name.c_str(),this,killer,deadtime);
} 

void Creature::AI_KilledUnit(Unit *pVictim)
{
	if(m_script_name.empty())
		return;
	DoKilledUnit(m_script_name.c_str(),this,pVictim);
}

//////////////////////////////////////////////////////////////////////////
//for lua

int Creature::LuaSetMonsterHost(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Creature *creature = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit); 
	Unit *unit = (Unit*)LUA_TOUSERDATA(scriptL,2, ObjectTypeUnit); 
	if (!unit || !creature)
	{
		tea_perror("LuaSetMonsterHost��Ŀ��Ϊ��");
		return 0;
	}
	
	creature->SetHostGUID(unit);
	return 0;
}

int Creature::LuaGetMonsterHost(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Creature *creature = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit); 
	if (!creature)
	{
		tea_perror("LuaGetMonsterHost��Ŀ��Ϊ��");
		lua_pushnumber(scriptL, 0);
		return 1;
	}	
	Unit *unit = creature->GetMap()->FindUnit(creature->GetHostGUID());
	if (unit)
		lua_pushlightuserdata(scriptL,unit);
	else
		lua_pushnil(scriptL);
	return 1;
}

int Creature::LuaSetReactState(lua_State* scriptL)
{	
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Creature *creature = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit);
	if(!creature)
		return 0;
	uint32 react = (uint32)LUA_TOINTEGER(scriptL,2);
	if(react >= MAX_REACT_STATES)
		react = 0;
	if (creature->GetReactState() == REACT_PASSIVE) {
		creature->SetReactState(ReactStates(react));
	}
	return 0;
}

int Creature::LuaSetScriptAI(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Creature *creature = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit);
	if(!creature)
		return 0;
	const char* _ainame = LUA_TOSTRING(scriptL,2);
	//creature->SetScriptAI(_ainame);
	if (creature->m_script_name == "") {
		creature->m_script_name = _ainame;	

		//��ʼ���ű�
		if(DoScriptInit(_ainame,creature))
			creature->m_script_name = "";
	}
	return 0;
}


int Creature::LuaModifyThreat(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Unit *unit_self = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit);
	Unit *unit_target = (Unit*)LUA_TOUSERDATA(scriptL,2, ObjectTypeUnit);
	if(!unit_self || !unit_target)
		return 0;
	if (unit_self->GetTypeId()!=TYPEID_UNIT)
		return 0;
	int v = (int)LUA_TOINTEGER(scriptL,3);
	if(v >=0 )
		((Creature*)unit_self)->m_threatMgr.Add(unit_target,v);
	else
		((Creature*)unit_self)->m_threatMgr.Sub(unit_target,-v);
	return 0;
}

int Creature::LuaMonsterTalk(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Creature *creature = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit);
	if(!creature)
		return 0;
	const char* str = LUA_TOSTRING(scriptL,2);	

	packet *_pkt = NULL;	
	pack_chat_unit_talk(&_pkt, creature->GetUIntGuid(), 0,(char*)str);
	creature->GetMap()->Broadcast(*_pkt, creature);
	external_protocol_free_packet(_pkt);
	return 0;
}
//���������԰�
int Creature::LuaMonsterDeadTalk(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Creature *creature = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit);
	if(!creature)
		return 0;
	const char* str = LUA_TOSTRING(scriptL,2);

	packet *_pkt = NULL;	
	pack_chat_unit_talk(&_pkt, creature->GetUIntGuid(), 1,(char*)str);
	creature->GetMap()->Broadcast(*_pkt, creature);
	external_protocol_free_packet(_pkt);
	return 0;
}

int Creature::MonsterMove(MovementGeneratorType mov_typ, size_t param1, time_t t)
{
	MovementGenerator *curr = NULL;	
	/*if(mov_typ == WAYPOINT_MOTION_TYPE)
	{
		curr = Tea::SelectMovementGenerator(this, mov_typ);	
	}
	else */
	if (mov_typ == FOLLOW_MOTION_TYPE || mov_typ == FOLLOW_INLINE_MOTION_TYPE 
		|| mov_typ == MERCENARY_MOTION_TYPE)
	{
		Unit *unit = (Unit*)param1;
		if(!unit)
		{
			tea_perror("FOLLOW_MOTION_TYPE unit is NULL");
			return 0;
		}
		//param1 = (size_t)unit->GetGuid();
		//this->SetTarget(unit);
	}
	
	curr = Tea::SelectMovementGenerator(this, mov_typ);


	if(curr)
	{
		curr->Initialize(*this, param1,t);
		this->m_impl.push(curr);
	}
	return 1;
}

int Creature::LuaMonsterMove(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);	
	ASSERT(n >= 2)
	Creature *creature = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit);	
	if(!creature)
	{
		tea_pwarn("LuaMonsterMove creature is NULL");
		return 0;
	}
	MovementGeneratorType mov_typ = (MovementGeneratorType)(int)LUA_TONUMBER(scriptL,2);
	
	
	//��ʼ������
	size_t param1 = 0;
	if(n >= 3)
	{
		if(lua_islightuserdata(scriptL,3))
			param1 = (size_t)lua_touserdata(scriptL,3);		
		else
			param1 = LUA_TOINTEGER(scriptL,3);
	}

	time_t t = 0;
	if(n >= 4)
		t = (time_t)LUA_TOINTEGER(scriptL, 4);

	creature->MonsterMove(mov_typ, param1, t);
	
	return 0;
}

int Creature::LuaMonsterAddSpell(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//��ȡ�ò�������
	int n = lua_gettop(scriptL);
	ASSERT(n == 10);
	Creature *creature = (Creature*)LUA_TOUSERDATA(scriptL,1, ObjectTypeUnit);	
	if(!creature)
		return 0;
	//���Ե���һ��,��creatureָ��

	// ��Ϊ������������Ӽ��ܣ�1��spellid 2������ 3���������ͣ��������ȡ��
	// 4:��������, 5:��cd, 6:����cd, 7:Ŀ������
	int id = int(LUA_TOINTEGER(scriptL, 2));
	spell_cast_probability *scp = NULL;
	//ͬһ�����͵ļ��ܹ���cd�͸���
	uint32 spell_type = uint32(LUA_TOINTEGER(scriptL, 6));
	//����ԭ���ǲ��Ǵ��ڣ���������¸���
	auto it = creature->m_spells.find(spell_type);
	if(it != creature->m_spells.end())
	{
		std::vector<spell_cast_probability*> elements = it->second;
		for (auto spell : elements) 
		{
			if(spell->spell_id == id)
			{
				scp = spell;
				break;
			}
		}
	}
	//�����ڣ�������
	if(scp == NULL)
	{
		scp = (spell_cast_probability*)malloc(sizeof(spell_cast_probability));
		memset(scp, 0, sizeof(spell_cast_probability));

		scp->spell_id = id;
		scp->spell_nowCDtime = uint32(LUA_TOINTEGER(scriptL, 4));
		scp->spell_level = uint32(LUA_TOINTEGER(scriptL, 5));
		scp->spell_distance = uint32(LUA_TOINTEGER(scriptL, 7));
		scp->spell_groupCD = uint32(LUA_TOINTEGER(scriptL, 8));
		scp->spell_singleCD = uint32(LUA_TOINTEGER(scriptL, 9));
		scp->target_type = uint32(LUA_TOINTEGER(scriptL, 10));

		if (creature->m_spells.find(spell_type) == creature->m_spells.end()) {
			std::vector<spell_cast_probability*> elements;
			creature->m_spells[spell_type] = elements;
		}

		creature->m_spells[spell_type].push_back(scp);
	}
	//���¸���
	scp->spell_probability = int(LUA_TOINTEGER(scriptL, 3));

	// �Ѳ���Ĳ�ȫ
	for (uint32 i = creature->m_spells_cd.size(); i < spell_type; ++ i) {
		creature->m_spells_cd.push_back(0);
	} 

	if(creature->m_spells_cd.size() <= spell_type)
	{
		ASSERT(spell_type == creature->m_spells_cd.size())	
		creature->m_spells_cd.push_back(0);
	}
	
	return 0;
}

int Creature::LuaIsAIFriends(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Creature *player = (Creature *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	Creature *target = (Creature *)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit);
	if (!player || !target)
	{	
		tea_pdebug("LuaIsAIFriends creature is null");
		return 0;
	}	

	bool is_friends = false;
	for (uint32 i = 0; i < player->m_friends_creature.size();++i)
	{
		if (player->m_friends_creature[i] == target->GetEntry())
		{
			is_friends = true;
			break;
		}		
	}	

	lua_pushnumber(scriptL,is_friends?1:0);
	return 1;
}

//���������grid
int Creature::LuaActiveGrid(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Creature* creature = (Creature*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(creature)
		creature->SetCanActiveGrid(true);

	return 0;
}

//���û�뾶
int Creature::LuaSetActionRadius(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Creature* creature = (Creature*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	float radius = (float)LUA_TONUMBER(scriptL, 2);
	if(creature)
		creature->m_threatMgr.SetActioRadius(radius);
	return 0;
}

//���û�뾶
int Creature::LuaSetVisionRadius(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Creature* creature = (Creature*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	float radius = (float)LUA_TONUMBER(scriptL, 2);
	if(creature)
		creature->m_threatMgr.SetVersionRadius(radius);
	return 0;
}

//������ҵĳ����б�
int Creature::LuaGetOwnShipTable(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);

	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Creature* creature = (Creature*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(creature && creature->GetMap())
	{
		vector<Player *> players; 
		creature->GetOwnshipTable(players);
		creature->GetMap()->__LuaAddPlayer(scriptL, players);	
	}

	return 1;
}
//��ǰ�Ϸ�������
int Creature::LuaGetLootOwner(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);

	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Creature* creature = (Creature*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!creature || !creature->GetMap())
	{
		lua_pushnil(scriptL);
		return 0;
	}
	Player *player = creature->GetOwnship();
	if(player)
	{
		lua_pushlightuserdata(scriptL,player);
		return 1;
	}
	lua_pushnil(scriptL);
	return 0;
}

// �Ƴ�����
int Creature::LuaRemoveMonster(lua_State* scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Creature* creature = (Creature*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	creature->SetDeathState(DEATH_STATE_CORPSE);

	return 1;
}

//�ı�ĳ������cdʱ��
int Creature::LuaChangeSpellCD(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);

	int n = lua_gettop(scriptL);
	ASSERT(n == 3);

	Creature* creature = (Creature*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 spell_id = uint32(LUA_TOINTEGER(scriptL, 2));
	uint32 spell_cd = uint32(LUA_TOINTEGER(scriptL, 3));
	if(!creature)
		return 0;

	creature->ChangeSpellCD(spell_id, spell_cd);
	return 1;
}

