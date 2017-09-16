#include "BuffManager.h"
#include "scened_app.h"
#include "Unit.h"
#include "scened_scripts.h"
#include "Creature.h"
#include "Player.h"
#include <object/SharedDef.h>


#define INFINITE_BUFF_TIME 65535 
#define BUFF_SUB_TIME 1000

BufferManager::BufferManager(Unit* buff_owner):m_buffOwner(buff_owner),m_buff_timer(BUFF_SUB_TIME),m_last_time(0),
	m_update_tick_num(0),m_ms_last_time(0)
{
	m_has_buffid.clear();

}

BufferManager::~BufferManager()
{

}

//--------------------------------------------------------
//BUFFER ����������
void BufferManager::Update(uint32 diff)
{
	if(m_update_tick_num == ScenedApp::g_app->m_tick_timers)
	{
		//tea_perror("BUFF�����ظ�����");
		return;
	}
	m_update_tick_num = ScenedApp::g_app->m_tick_timers;

	m_buff_timer.Update(diff);
	//BUFF�Ƚ����⣬����һ���ӽ�һ��
	if (m_buff_timer.Passed())
	{
		UpdateBuff();
		m_buff_timer.Reset(BUFF_SUB_TIME);
	}
}

//--------------------------------------------------------
//BUFFˢ��
void BufferManager::UpdateBuff()
{
	uint32 time_now = ms_time();
	if (time_now-m_last_time<950)
	{
		//ASSERT(false);
		//tea_perror("����һ��BUFF����Ϊɶ�ֽ��ˣ���"); ����ʱ��ͽ��ˡ�
		return ;
	}
	m_last_time = time_now;
	
	for (auto iter = m_has_buffid.begin();iter!=m_has_buffid.end();iter++)
	{
		m_diff_need_del_buff.push_back(iter->second);
	}
	for(auto iter = m_diff_need_del_buff.begin();iter!=m_diff_need_del_buff.end();iter++)
	{
		uint8 i = *iter;
		uint16 buff_id = GetBuff(i);	
		if(buff_id >= 0 && buff_id <= 100)
			continue;
		
		buff_template *b = buff_template_db[buff_id];
		if(!b)
		{
			tea_perror(" BufferManager::UpdateBuff %s,%u",m_buffOwner->GetName().c_str(),buff_id);
			SetBuff(i,0, 0);
			continue;
		}

		//������
		if (IsBuffTrigger(i))
		{
			if(!m_buffOwner->isAlive())
				return;
			
			DoBuffTriggerScript(m_buffOwner, buff_id,GetBuffEffectId(i));			
		}
		//����ʱ�����
		ReduceBuffTime(i);
		if(IsBuffOver(i))
		{
			//�ȼ���BUFF������ɾ��BUFF
			DoBuffOverScript(m_buffOwner, buff_id,GetBuffEffectId(i));
			RemoveBuff(i);
		}
	}
	
	m_diff_need_del_buff.clear();
}

//--------------------------------------------------------
//��ȡBUFF����ʱ��
uint16 BufferManager::GetBuffDurationByID(uint16 buff_id)
{
	for(uint8 i = 0;i<MAX_UNIT_BUFF;i++)
	{
		uint16 cur_buff = GetBuff(i);
		if(buff_id==cur_buff)
		{
			return GetBuffDuration(i);			
		}
	}
	return 0;
}

//--------------------------------------------------------
//����BUFF����ʱ��
void BufferManager::SetBuffDurationByID(uint16 buff_id,uint16 duration)
{
	for(uint8 i = 0;i<MAX_UNIT_BUFF;i++)
	{
		uint16 cur_buff = GetBuff(i);
		if(buff_id==cur_buff)
		{
			SetBuffDuration(i,duration);
			break;
		}
	}
}

uint32 BufferManager::GetReserveVal(uint16 buff_id)
{
	for(uint8 i = 0;i<MAX_UNIT_BUFF;i++)
	{
		uint16 cur_buff = GetBuff(i);
		if(buff_id == cur_buff)
		{
			return m_buffOwner->GetUInt32(UNIT_FIELD_BUFF_RESERVE + i);			
		}
	}
	return 0;
}
//����ID����BUFFԤ��ֵ
void BufferManager::SetReserveVal(uint16 buff_id, uint32 reserve)
{
	for(uint8 i = 0; i < MAX_UNIT_BUFF; i++)
	{
		uint16 cur_buff = GetBuff(i);

		if (cur_buff==buff_id)
		{
			return SetBuffReserve(i, reserve);
		}	
	}
}
//--------------------------------------------------------
//��ȡBUFF����ʱ��
uint32 BufferManager::GetBuffDuration(uint8 pos)
{ 
	return m_buffOwner->GetUInt16(UNIT_FIELD_BUFF_TM+pos/2,pos%2); 
}	

//--------------------------------------------------------
//����BUFF����
void BufferManager::SetBuffDuration(uint8 pos,uint32 time)
{
	m_buffOwner->SetUInt16(UNIT_FIELD_BUFF_TM+pos/2,pos%2,time);
}		

//--------------------------------------------------------
//����BUFF����ʱ��
void BufferManager::ReduceBuffTime(uint8 pos)
{
	//����ʱ���BUFF
	uint16 buff_tm = GetBuffDuration(pos);
	if (buff_tm==INFINITE_BUFF_TIME)
		return;
	
	if(buff_tm >= 1)
		SetBuffDuration(pos,buff_tm-1);
}

//--------------------------------------------------------
//��ȡBUFF ID 
uint16 BufferManager::GetBuff(uint8 pos)
{
	ASSERT(pos < MAX_UNIT_BUFF);
	return m_buffOwner->GetUInt16(UNIT_FIELD_BUFF + pos/2, pos%2);
}

//-------------------------------------	-------------------
//��ȡBUFF ID ��0~11��
void  BufferManager::SetBuff(uint8 pos,uint16 buff_id,uint32 buffEffectId)
{
	ASSERT(buff_id != 65535);
	m_buffOwner->SetUInt16(UNIT_FIELD_BUFF + pos/2, pos%2, buff_id);
	SetBuffLevel(pos,buffEffectId);
}

//����Ԥ��ֵ
void BufferManager::SetBuffReserve(uint8 pos, uint32 val)
{
	m_buffOwner->SetUInt32(UNIT_FIELD_BUFF_RESERVE + pos, val);
}

//����buff giver��Guid
void BufferManager::SetBuffGiverGuid(uint8 pos, uint32 guid)
{
	ASSERT(pos < MAX_UNIT_BUFF);
	m_buffOwner->SetUInt32(UNIT_FIELD_BUFF_CASTER_GUID + pos, guid);
}

//���buff giver��Guid
uint32 BufferManager::GetBuffGiverGuid(uint8 pos)
{
	ASSERT(pos < MAX_UNIT_BUFF);
	return m_buffOwner->GetUInt32(UNIT_FIELD_BUFF_CASTER_GUID + pos);
}



//���buff giver��Guid
uint32 BufferManager::GetBuffGiverGuidByID(uint16 buff_id)
{
	for(uint8 i = 0; i < MAX_UNIT_BUFF; i++)
	{
		uint16 cur_buff = GetBuff(i);

		if(0 == cur_buff)
			continue;
		if (cur_buff==buff_id)
		{
			return GetBuffGiverGuid(i);			
		}	
	}
	return 0;
}
//--------------------------------------------------------
//����λ�û�ȡBUFF�ȼ�
uint32 BufferManager::GetBuffEffectId(uint8 pos)
{
	ASSERT(pos < MAX_UNIT_BUFF);
	return m_buffOwner->GetUInt32(UNIT_FIELD_BUFF_EFFECT_ID + pos);
}
//����ID���BUFF�ȼ�
uint32 BufferManager::GetBuffEffectId(uint16 buff_id)
{
	for(uint8 i = 0; i < MAX_UNIT_BUFF; i++)
	{
		uint16 cur_buff = GetBuff(i);

		if(0 == cur_buff)
			continue;
		if (cur_buff==buff_id)
		{
			return GetBuffEffectId(i);
		}	
	}
	return 0;
}

//����BUFF�ȼ�
void BufferManager::SetBuffLevelByID(uint16 buff_id, uint32 buffEffectId)
{
	for(uint8 i = 0; i < MAX_UNIT_BUFF; i++)
	{
		if(GetBuff(i) == buff_id) 
		{
			SetBuffLevel(i, buffEffectId);
			m_buffOwner->SetCalculAttrStage(true);
			break;
		}
	}
}

//--------------------------------------------------------
//����BUFF�ȼ�
void BufferManager::SetBuffLevel(uint8 pos, uint32 buffEffectId)
{
	ASSERT(pos < MAX_UNIT_BUFF);
	m_buffOwner->SetUInt32(UNIT_FIELD_BUFF_EFFECT_ID + pos, buffEffectId);
}

//--------------------------------------------------------
//BUFF�Ƿ񴥷�
bool BufferManager::IsBuffTrigger(uint8 pos)
{
	uint32 duration	= GetBuffDuration(pos);
	uint32 buffEffectId = this->GetBuffEffectId(pos);
	uint32 frequency = GetBuffFrequency(buffEffectId);
	if (frequency == 1) {
		//��ֹÿ��ִ�е�ʱ����ִ��һ��
		if (duration != 0 && 0 == duration % frequency)
			return true;
	} else {
		if (frequency > 0 && 0 == duration % frequency)
			return true;
	}
	return false;
}

//--------------------------------------------------------
//BUFF�Ƿ����
bool BufferManager::IsBuffOver(uint8 pos)
{
	return GetBuffDuration(pos)==0;
}

//--------------------------------------------------------
//����BUFF
void BufferManager::AddBuff(uint16 buff_id,uint32 buffEffectId,int32 bonus_time, const char* name, const char* guid, uint32 reserve)
{
	ASSERT(buff_id > 100 && buff_template_db[buff_id]);
	for(uint8 i = 0; i < MAX_UNIT_BUFF; i++)
	{
		uint16 cur_buff = GetBuff(i);

		if(0 != cur_buff)
			continue;
		
		//ASSERT();
		SetBuff(i, buff_id, buffEffectId);
		uint32 du = bonus_time >= MAX_BUFF_DURATION ? MAX_BUFF_DURATION : bonus_time;
		SetBuffDuration(i,du);
		SetBuffGiverGuid(i,shortGUID(guid));
		SetBuffReserve(i, reserve);
		if (guid != nullptr) {
			m_buffOwner->SetCalculAttrStage(true);
		}
		auto iter = m_has_buffid.find(buff_id);
		//��¼λ�õĻ� ��ҪС��λ�ñ䶯�� ����жϰ�ȫ
		if(iter == m_has_buffid.end()||(iter != m_has_buffid.end()&&m_has_buffid[buff_id]!=i))
			m_has_buffid[buff_id]=i;

		break;
	}
}

//--------------------------------------------------------
//����BUFF����		
void BufferManager::AddBuffAttr()
{
	for(uint8 i = 0; i < MAX_UNIT_BUFF; i++)
	{
		uint16 cur_buff = GetBuff(i);
		
		if(0 == cur_buff)
			continue;
		
		DOComputeBuffAttr(m_buffOwner,cur_buff,GetBuffEffectId(i));
	}
}

//--------------------------------------------------------
//�Ƴ�BUFF ͨ��λ��
void BufferManager::RemoveBuff(uint8 pos)
{
	ASSERT(pos < MAX_UNIT_BUFF);
	uint16 buff_id = GetBuff(pos);
	SetBuff(pos, 0, 0);
	SetBuffReserve(pos, 0);
	SetBuffDuration(pos, 0);
	SetBuffGiverGuid(pos, 0);
	m_buffOwner->SetCalculAttrStage(true);
	auto iter = m_has_buffid.find(buff_id);
	if(iter != m_has_buffid.end())
		m_has_buffid.erase(iter);
}

//--------------------------------------------------------
//�Ƴ�BUFF ͨ��buffid
bool BufferManager::RemoveBuff(uint16 buff_id)
{
	for(uint8 i = 0;i<MAX_UNIT_BUFF;i++)
	{
		uint16 buff = GetBuff(i);
		if(buff_id==buff)
		{
			RemoveBuff(i);
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------
//�Ƿ���ָ��BUFF
uint8  BufferManager::HasBuff(uint16 buffidd)
{
	auto iter = m_has_buffid.find(buffidd);
	if(iter != m_has_buffid.end())
		return 1;
	return 0;
}


//--------------------------------------------------------
//���BUFF
void BufferManager::ClearBuff()
{
	for(uint8 i = 0;i<MAX_UNIT_BUFF;i++)
	{
		if(GetBuff(i))
			RemoveBuff(i);
	}
}

//������buffid
void BufferManager::UpDateHasBuffId()
{
	m_has_buffid.clear();
	for(uint8 i = 0;i<MAX_UNIT_BUFF;i++)
	{
		uint16 cur_buff = GetBuff(i);
		if(cur_buff>0)
		{
			m_has_buffid[cur_buff] =i;
		}
	}
}
//--------------------------------------------------------

int BufferManager::LuaSystemAddBuff(lua_State* scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 4);
	Unit *unit = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	ASSERT(unit);

	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	uint32 buffEffectId = (uint32)LUA_TONUMBER(scriptL, 3);
	int32 bonus_time = (int32)LUA_TONUMBER(scriptL, 4);

	if (!unit->GetBuffManager()->HasBuff(buff_id)) {
		unit->GetBuffManager()->AddBuff(buff_id, buffEffectId, bonus_time);
	}
	return 0;
};

//FOR LUA
//--------------------------------------------------------
int BufferManager::LuaAddBuff(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 5);
	Unit *unit = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	Unit *buff_giver = (Unit*)LUA_TOUSERDATA(scriptL, 3, ObjectTypeUnit);//BUFF������
	uint32 buffEffectId = (uint32)LUA_TONUMBER(scriptL, 4);
	int32 bonus_time = (int32)LUA_TONUMBER(scriptL, 5);
	uint32 reserve = 0;
	if (n >= 6)
	{
		reserve = (uint32)LUA_TONUMBER(scriptL, 6);
	}
	
	if (!unit)
	{
		tea_pdebug("LuaAddBuffĿ��Ϊ��");
		return 0;
	}
	//����BUFF
	if(!unit->isAlive())
		return 0;
	
	if (buff_giver)
	{
		unit->GetBuffManager()->AddBuff(buff_id,buffEffectId,bonus_time,buff_giver->GetName().c_str(), buff_giver->GetGuid().c_str(), reserve);
	}
	else
	{
		unit->GetBuffManager()->AddBuff(buff_id,buffEffectId,bonus_time);
		return 0;
	}

	//�������ҶԹ����BUFF ��ô���ӹ�����
	Creature::AddTheOwnership(unit,buff_giver);

	//�����˼�BUFF~����ս��״̬
	if (unit!=buff_giver &&!buff_giver->IsFriendlyTo(unit))
	{
		//����PVP״̬
		if (unit->GetTypeId() == TYPEID_PLAYER && buff_giver->GetTypeId() == TYPEID_PLAYER)
		{
			((Player*)unit)->resetPVPStateTime();
			((Player *)unit)->SetPVPstate();
			((Player*)buff_giver)->resetPVPStateTime();
			((Player *)buff_giver)->SetPVPstate();
			((Player*)unit)->resetCombatStateTime();	
			((Player*)buff_giver)->resetCombatStateTime();
		}
	}
	
	//TODO:��ħ���йش���Ӧ�ڽű������ ��ʩ������Ӷ�ʩ���ߵĳ��ֵ
	if(unit->GetTypeId() == TYPEID_UNIT && unit != buff_giver)
		dynamic_cast<Creature *>(unit)->m_threatMgr.Add(buff_giver,1);

	return 0;
}

int BufferManager::LuaRemoveBuff(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL,2);
	if (!unit)
	{
		tea_pdebug("LuaRemoveBuffĿ��Ϊ��");
		return 0;
	}
	
	lua_pushboolean(scriptL, unit->GetBuffManager()->RemoveBuff(buff_id));
	
	return 1;
}

int BufferManager::LuaHasBuff(lua_State *scriptL)
{
 	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	if (!unit)
	{
		tea_pdebug("LuaHasBuff unit nullptr!");
		return 0;
	}
	lua_pushboolean(scriptL, unit->GetBuffManager()->HasBuff(buff_id));
	return 1;
}

int BufferManager::LuaGetBuffLevel(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	if (!unit)
	{
		tea_pdebug("LuaGetBuffLevelĿ��Ϊ��");
		lua_pushnumber(scriptL,-1);
		return 1;
	}
	lua_pushnumber(scriptL, unit->GetBuffManager()->GetBuffEffectId(buff_id));//
	return 1;
}

int BufferManager::LuaSetBuffLevel(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	uint8 buff_lv = (uint8)LUA_TONUMBER(scriptL, 3);
	if (unit)
	{
		//unit->GetBuffManager()->SetBuffLevelByID(buff_id, buff_lv);		
	}
	return 0;
}
//���ָ��id��reserveֵ
int BufferManager::LuaGetReserveVal(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	if (unit)
	{
		lua_pushnumber(scriptL, unit->GetBuffManager()->GetReserveVal(buff_id));		
	}
	else
	{
		lua_pushnumber(scriptL, 0);
	}
	return 1;
}

//����ָ��id��reserveֵ
int BufferManager::LuaSetReserveVal(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	uint32 reserve = (uint32)LUA_TONUMBER(scriptL, 3);
	if (unit && unit->GetBuffManager())
	{
		if(unit->GetBuffManager()->HasBuff(buff_id))
			unit->GetBuffManager()->SetReserveVal(buff_id, reserve);		
	}

	return 1;
}

int BufferManager::LuaGetBuffDuration(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	if (!unit)
	{
		tea_pdebug("LuaHasBuffĿ��Ϊ��");
		lua_pushnumber(scriptL,-1);
		return 1;
	}
	lua_pushnumber(scriptL, unit->GetBuffManager()->GetBuffDurationByID(buff_id));//
	return 1;
}

int BufferManager::LuaSetBuffDuration(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	uint16 duration = (uint16)LUA_TONUMBER(scriptL, 3);
	if (!unit)
	{
		tea_pdebug("error:LuaSetBuffDuration unit == null");
		return 0;
	}
	unit->GetBuffManager()->SetBuffDurationByID(buff_id,duration);
	return 0;
}

//���buff��giver����
int BufferManager::LuaGetBuffGiverUnit(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit	   = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 buff_id = (uint16)LUA_TONUMBER(scriptL, 2);
	if (!unit)
	{
		tea_pdebug("error:LuaGetBuffGiverUnit unit == null");
		return 0;
	}
	uint32 buffgiver_guid = unit->GetBuffManager()->GetBuffGiverGuidByID(buff_id);
	Unit *giver = NULL;
	if (unit->GetMap())
		giver = unit->GetMap()->FindUnit(buffgiver_guid);
	if (giver)
		lua_pushlightuserdata(scriptL, giver);
	else
		lua_pushnil(scriptL);
	return 1;
}

