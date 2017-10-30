#include <object/Unit.h>
#include "Unit.h"
#include "Map.h"
#include "Grid.h"
#include "scened_context.h"
#include "scened_scripts.h"
#include "BuffManager.h"
#include "LootManager.h"
#include <object/SharedDef.h>
#include <shared/log_handler.h>
#include <object/OprateResult.h>
#include <shared/offset_path.h>

vector<uint16> g_cant_attack_buff;
vector<uint16> g_cant_cast_buff;
vector<uint16> g_cant_move_buff;
vector<uint16> g_cant_jump_buff;
vector<uint16> g_cant_teleport_buff;
vector<uint16> g_cant_use_item_buff;
vector<uint16> g_cant_see_buff;
vector<uint16> g_invincible_buff;
vector<uint16> g_cant_fight_with_player;
vector<uint16> g_cant_attack_be_player;
vector<uint16> g_cant_recovery_buff;
vector<uint16> g_ignore_the_obstacles;

struct UnitHashList
{
	UnitHashList()
	{
		//��������࿪1000������,ÿ������20ֻ������20000,*2�õ�������40000ֻ
		//��Ҫ�����ڴ�32k
		hash_list_init(&list_,32768);		
	}
	~UnitHashList()
	{
		hash_list_free(list_);		
	}

	hash_list *list_;
}g_unitHashList;

Unit *Unit::FindUnit(uint32 guid)
{
	hashlist_node *node = hash_list_find(g_unitHashList.list_,guid);
	if(!node)
		return nullptr;
	return hash_list_entry(node,Unit,m_hash_node);
}

//////////////////////////////////////////////////////////////////////////
//for Unit
Unit::Unit():BinLogObject(core_obj::SyncMode(OBJECT_MODE)),
	m_positionX(0), m_positionY(0),m_orientation(0),m_canActiveGrid(false),m_grid(0),m_map(0),m_moving_ms(0),m_last_victim_target(0), 
	m_attacking(NULL), m_auto_spell(0), m_last_jump(0), m_live_timer(0),
    m_isActing(false), m_recalcul_Attr(false),m_isBlowFly(false),m_update_tick_num(0),m_target_guid(0),m_need_sync_pos(false)
{
    m_state = 0;
    m_target_x = -1.0f;
    m_target_y = -1.0f;
    m_cur_spell  = 0;
	m_cur_spell_lv = 0;
    m_buff_manager = new BufferManager(this);//..��������Ƿ���ʣ�
	m_spell_trigger.clear();
	INIT_HASH_LIST_HEAD(&m_hash_node);
}

Unit::~Unit()
{
    ClearAttacker();
    SetTarget(NULL);
	SetMap(NULL);
	safe_delete(m_buff_manager);
	m_spell_trigger.clear();
	if(HAS_HASH_LIST(&m_hash_node))
		hash_list_del(&m_hash_node);
}

void Unit::_Create(const string& guid, int entry)
{
	SetGuid(guid);
	SetEntry(entry);
	m_uint_guid = atol(SUB_GUID_STR_TO_INT(guid).c_str());
	ASSERT(!HAS_HASH_LIST(&m_hash_node));
	hash_list_insert(g_unitHashList.list_,m_uint_guid,&m_hash_node);
}

void Unit::WriteCreateBlock(ByteArray &bytes,UpdateMask *int_mask,UpdateMask *str_mask)
{
	SyncEventRecorder::WriteCreateBlock(bytes,int_mask,str_mask);
	//�ƶ���Ϣ��������Ϣ���ȥ
	WriteMovePath(bytes);
	bytes.writeFloat(m_orientation);
}

bool Unit::WriteMovePath(ByteArray &buff)
{
	static offset_path ofpath;
	ofpath.path_.clear();
	ofpath.set_origin(uint16(GetPositionX()),uint16(GetPositionY()));
#if 0		
	for (int i = 0; i < (int)m_moving_path.size(); i = i + 2)
		ofpath._add(int(m_moving_path[i]), int(m_moving_path[i+1]));
#else
	if(!CreateOffsetPath(ofpath.origin_x_,ofpath.origin_y_,m_moving_path,ofpath.path_)){
		ofpath.path_.clear();
		buff.writeShort(ofpath.origin_x_);
		buff.writeShort(ofpath.origin_y_);
		buff << ofpath.path_;
		return false;
	}
#endif

	buff.writeShort(ofpath.origin_x_);
	buff.writeShort(ofpath.origin_y_);
	buff << ofpath.path_;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//����

void Unit::SetStatFloat( uint16 index, float value)
{
	if(value < 0)
		value = 0.0f;

	SetFloat(index, value);
}

void Unit::SetStatInt32( uint16 index, int32 value)
{
	if(value < 0)
		value = 0;

	SetUInt32(index, uint32(value));
}

void Unit::SetHealth(uint32 val, bool isBroadcast/* = true*/)
{
    uint32 maxHealth = GetMaxHealth();

    if(maxHealth < val)
        val = maxHealth;


	if(GetUInt32(UNIT_FIELD_HEALTH) == val)
		return;

	SetUInt32(UNIT_FIELD_HEALTH, val);
	if (isBroadcast)
		BroadcastHp(val);
}

void Unit::SetMaxHealth(uint32 val)
{
    //double health = GetHealth();
    SetUInt32(UNIT_FIELD_MAX_HEALTH, val);

    //if(val < health)���ܼ򵥵���ô��
    //	SetHealth(val);
}

double Unit::ModifyHealth(double dVal, bool isBroadcast/* = true*/)
{
    double gain = 0;

    if(dVal == 0)
        return 0;

    double curHealth = (double)GetHealth();

    double val = dVal + curHealth;
			
    if(val <= 0)
    {
        SetHealth(0, isBroadcast);
        return -curHealth;
    }

    double maxHealth = (double)GetMaxHealth();

    if(val < maxHealth)
    {
        SetHealth((uint32)val, isBroadcast);
        gain = val - curHealth;
    }
    else if(curHealth != maxHealth)
    {
        SetHealth((uint32)maxHealth, isBroadcast);
        gain = maxHealth - curHealth;
    }
    return gain;
}

//�㲥�����仯
//hp:����������, -��ʾ��Ѫ
void Unit::BroadcastHp(uint32 hp)
{
	if(!m_grid)
		return;

	uint32 uint_guid = GetUIntGuid();

	ByteArray *buff = ObjMgr.GridMallocByteArray();
	*buff << (uint16)SMSG_FIGHTING_INFO_UPDATE_OBJECT << uint_guid << uint8(1);
	*buff << uint_guid << hp << uint8(HITINFO_CURE) << uint8(0) << double(0); //��������;
	*buff << uint32(0) << uint16(0) << uint16(0);

	m_grid->AsyncBroadcast(buff);
	ObjMgr.GridFreeByteArray(buff);

	//m_grid->fighting_blocks.push_back(buff);
}

//double Unit::ModifyPower(Powers power, double dVal)
//{
//    double gain = 0;
//    if(dVal == 0)
//        return 0;
//
//    double curPower = (double)GetPower(power);
//	double val = dVal + curPower;
//    double maxPower = (double)GetMaxPower(power);
//	if (val < 0.0f)
//		val = 0.0f;	
//	if(val < maxPower)
//    {
//        SetPower(power, (uint32)val);
//        gain = val - curPower;
//    }
//    else if(curPower != maxPower)
//    {
//        SetPower(power, (uint32)maxPower);
//        gain = maxPower - curPower;
//    }
//    return gain;
//}
//
//void Unit::SetPower(Powers power, uint32 val)
//{
//	uint32 maxPower = GetMaxPower(power);
//	if(maxPower < val)
//		val = maxPower;
//
//	switch (power)
//	{
//	case POWER_MANA:
//		break;
//	case POWER_ENERGY:
//		SetUInt32(UNIT_FIELD_POWERS_ENERGY, val);
//		break;		
//	default:
//		break;
//	}	
//}

//uint32 Unit::GetMaxPower(Powers power)
//{
//	uint32 mp = 0;
//	switch (power)
//	{
//	case POWER_MANA:
//		break;
//	case POWER_ENERGY:
//		mp = GetUInt32(UNIT_FIELD_MAXPOWERS_ENERGY);
//		break;		
//	default:
//		break;
//	}
//	return mp;
//}

//void Unit::SetMaxPower(Powers power, uint32 val)
//{
//    //uint32 cur_power = GetPower(power);
//	switch (power)
//	{
//	case POWER_MANA:
//		break;
//	case POWER_ENERGY:
//		SetUInt32(UNIT_FIELD_MAXPOWERS_ENERGY, val);
//		break;		
//	default:
//		break;
//	}
//    //���⴦��
//    //if(val < cur_power)
//    //	SetPower(power, val);
//}

//uint32 Unit::GetCombatRate(Combat_Rate rage)
//{
//	uint32 rate = 0;
//	switch (rage)
//	{
//	case COMBAT_RATE_CRIT:
//		rate = GetUInt32(UNIT_FIELD_COMBAT_RATE_CRIT);
//		break;		
//	case COMBAT_RATE_EVA:
//		rate = GetUInt32(UNIT_FIELD_COMBAT_RATE_EVA);
//		break;			
//	default:
//		break;
//	}
//	return rate;
//}

/*void Unit::SetCombatRate(Combat_Rate rage, uint32 val)
 {
 switch (rage)
 {
 case COMBAT_RATE_CRIT:
 SetUInt32(UNIT_FIELD_COMBAT_RATE_CRIT, val);
 break;		
 case COMBAT_RATE_EVA:
 SetUInt32(UNIT_FIELD_COMBAT_RATE_EVA, val);
 break;		
 default:
 break;
 }
 }*/

//�����ٶ�
void Unit::SetMoveSpeed(uint32 speed)
{    
    //���¼�����Ҫ����ʱ��
    if (IsMoving() && GetMoveSpeed() != speed)
    {
        float range = GetDistance(m_moving_path[0], m_moving_path[1]);
        m_moving_ms = uint32(range * speed);	
		ASSERT(GetTypeId()!=TYPEID_PLAYER || ((Player*)this)->GetSession()->GetStatus()!=STATUS_TRANSFER);		
    }
	SetUInt32(UNIT_FIELD_MOVE_SPEED, speed);
}

void Unit::SetTarget(Unit *target)
{
	if(target && target->GetUIntGuid() == m_target_guid)
	{
		return;		
	}
    //tea_pdebug("SetTarget %u", target ? target->GetGuid() : 0);
	
    //ħ��ֹͣ
    if (isCasing() || isSpellProcess())
    {
        SpellStop();
    }
	
    //������ΪĿ������
	m_target_guid = 0;
    if(target != NULL) {
		m_target_guid = target->GetUIntGuid();
	}

	/*if(GetTypeId() == TYPEID_PLAYER)
	{
		Player *player = dynamic_cast<Player*>(this);
		if(player && player->GetSession())
		{			
			Call_select_target(player->GetSession()->m_delegate_sendpkt, target?target->GetUIntGuid():0);
		}
	}*/
}

Unit* Unit::GetTarget()
{
	if (m_map)
	{
		return m_map->FindUnit(m_target_guid);
	}
	
	return NULL;
}

float Unit::GetAngle(const Unit* obj) const
{
	if(!obj) return 0;
	return GetAngle( obj->GetPositionX(), obj->GetPositionY() );
}

// Return angle in range 0..2*pi
float Unit::GetAngle( const float x, const float y ) const
{
	float dx = x - GetPositionX();
	float dy = y - GetPositionY();

	float ang = atan2(dy, dx);
	ang = (ang >= 0) ? ang : 2 * M_PI + ang;
	return ang;
}

float Unit::GetDistance(const Unit *obj) const
{
	if(!obj) return 0;
	return GetDistance( obj->GetPositionX(), obj->GetPositionY());
}

float Unit::GetDistance(const float x,const float y) const
{
	float dx = x - GetPositionX();
	float dy = y - GetPositionY();
	return (float)sqrt(dx*dx + dy*dy);
}

//��Ӽ��ܴ�����
void Unit::AddSpellTrigger(spell_trigger str)
{
	m_spell_trigger.push_back(str);
}

//////////////////////////////////////////////////////////////////////////
//״̬����

void Unit::Update( uint32 diff )
{
	if(m_update_tick_num == ScenedApp::g_app->m_tick_timers)
	{
		/*if (!diff)
		tea_perror("Unit�����ظ�����");*/
		return;
	}
	m_update_tick_num = ScenedApp::g_app->m_tick_timers;

	//��Ҳ��ڵ�ͼ�ͱ�Ϲ����
	if(GetGrid())
	{
		UpdateSpellTrigger(diff);				//���ܴ���������
		GetBuffManager()->Update(diff);
		//if(!ScenedApp::g_app->IsPKServer())
			UpdateLiveStatus(diff);
		UpdateLocate(diff);
	}

    //��Ҫ�����������
    if (m_recalcul_Attr)
    {
        Calcul_Attr();
		m_recalcul_Attr = false;
    }

}

bool Unit::UpdateLocate(uint32 diff)
{
    //���ƶ�״̬
    if(!IsMoving())
        return false;
	//ASSERT(GetMapId() == GetMap()->GetMapId());
	if(GetMap()->GetMapId() != GetMapId())
	{
		tea_perror("Unit::UpdateLocate GetMap()->GetMapId() != GetMapId() %u %u %u %u %s %s"
			, GetMap()->GetMapId(), GetMapId()
			, GetEntry(), GetTypeId(), GetGuid().c_str(), GetName().c_str());
		return false;
	}
    float x = 0.0f, y = 0.0f;

    //�ۼ�ʱ��
    m_moving_last_diff += diff;

    //����Ѿ���������
    if(m_moving_ms <= m_moving_last_diff)
    {
		//����Ϊ�����겢������
        SetPosition(m_moving_path[0], m_moving_path[1]);
		//printf("ͬ��Ŀ������, (%f, %f)\n", m_moving_path[0], m_moving_path[1]);
		//todo �Ż�  ������������� ͬ���³�����
		if(GetTypeId() == TYPEID_UNIT && GetEntry() >= 5400 &&  GetEntry() <= 5405)
		{
			static_cast<Creature*>(this)->SetBornPos(m_moving_path[0], m_moving_path[1]);
		}

		m_moving_path.pop_front();
		m_moving_path.pop_front();

        if (m_moving_path.size() == 0)		//�������ĵ�
        {
            //�Ѿ�����Ŀ����
            m_moving_ms = 0;
            m_moving_last_diff = 0;
			m_need_sync_pos = true;
        }
        else
        {
            //����һ����һ�������˶���ʱ��
            m_moving_last_diff -= m_moving_ms;

            //������һ������Ҫ���ĵ�ʱ��
            float angle = GetAngle(m_moving_path[0], m_moving_path[1]);
            float dist = GetDistance(m_moving_path[0], m_moving_path[1]);
            SetOrientation(angle);
            m_moving_ms = uint32(dist * 10 * 1000 / GetMoveSpeed());			
			if(!m_moving_ms)
				m_moving_ms=1;	
			ASSERT(GetTypeId()!=TYPEID_PLAYER || ((Player*)this)->GetSession()->GetStatus()!=STATUS_TRANSFER);			

			//	if(GetTypeId() == TYPEID_PLAYER)
			//	tea_pdebug("from (%f,%f) to (%f,%f) dist:%f ori:%f ms:%u",GetPositionX(),GetPositionY(),m_moving_path[0],m_moving_path[1],dist,GetOrientation(),m_moving_ms);
        }        
    }
	else
	{
		m_moving_ms -= m_moving_last_diff;    	
		ASSERT(GetTypeId()!=TYPEID_PLAYER || ((Player*)this)->GetSession()->GetStatus()!=STATUS_TRANSFER);

		//ˢ������
		float range = float(m_moving_last_diff) * float(GetMoveSpeed()) / 1000 / 10;
		float distX = range * cos(GetOrientation());
		float distY = range * sin(GetOrientation());

		x = GetPositionX() + distX;
		y = GetPositionY() + distY;

		//��֤�����Ƿ�׼ȷ
		if(!GetMap()->IsRightCoord(x, y))
		{
			tea_pdebug("ˢ�� ԭ����(%f,%f) ������(%f,%f)", GetPositionX(), GetPositionY(), x, y);
			x = GetPositionX();
			y = GetPositionY();
			if(IsMoving())
				StopMoving(true);
		}

		//if (GetTypeId()==TYPEID_PLAYER)
		//	tea_pdebug("%u,%u (%.2f,%.2f) (%.2f,%.2f) (%.0f,%.0f),ori:%f",m_moving_last_diff,m_moving_ms, m_positionX, m_positionY, x, y, m_moving_path[0], m_moving_path[1], GetOrientation());
		//printf("ͬ������, (%f, %f)\n", x, y);
		SetPosition(x, y);
		//todo �Ż�  ������������� ͬ���³�����
		if(GetTypeId() == TYPEID_UNIT && GetEntry() >= 5400 &&  GetEntry() <= 5405)
		{
			static_cast<Creature*>(this)->SetBornPos(x, y);
		}
		m_moving_last_diff = 0;
	}

	// �߶��Ժ�Ĵ���
	if (this->GetTypeId() == TYPEID_PLAYER) {
		DoTerminalContinuousAction(this);
	}

    return true;
}


float Unit::GetAttackDistance (Unit const*)const
{ 
	return g_Config.nomal_attack_distance;
}

//�ܷ��ƶ�
bool Unit::isCanMove()
{
   return !GetBit(UNIT_FIELD_FLAGS, UNIT_FIELD_FLAGS_CANT_MOVE);
}

//�ܷ�ָ�
bool Unit::isCanRecovery()
{
	for(uint16 i = 0; i < g_cant_recovery_buff.size(); i++)
	{
		if (m_buff_manager->HasBuff(g_cant_recovery_buff[i]))
			return false;
	}

	return true;
}

//�ܷ���
bool Unit::isCanTeleport()
{
    for(uint16 i = 0; i < g_cant_teleport_buff.size(); i++)
    {
        if (m_buff_manager->HasBuff(g_cant_teleport_buff[i]))
            return false;
    }

    return true;
}

//�Ƿ���ʹ����Ʒ
bool Unit::isCanUseItem()
{
    for(uint16 i = 0; i < g_cant_use_item_buff.size(); i++)
    {
        if (m_buff_manager->HasBuff(g_cant_use_item_buff[i]))
            return false;
    }

    return true;
}

//�Ƿ������ϰ�
bool Unit::isIgnoreTheObstacles()
{
	for(uint16 i = 0; i < g_ignore_the_obstacles.size(); i++)
	{
		if (m_buff_manager->HasBuff(g_ignore_the_obstacles[i]))
			return true;
	}
	return false;
}




//�Ƿ�ɼ�
bool Unit::isCanSee()
{
    for(uint16 i = 0; i < g_cant_see_buff.size(); i++)
    {
        if (m_buff_manager->HasBuff(g_cant_see_buff[i]))
            return false;
    }

    return true;
}

//�Ƿ��޵�
bool Unit::isInvincible()
{
    for(uint16 i = 0; i < g_invincible_buff.size(); i++)
    {
        if (m_buff_manager->HasBuff(g_invincible_buff[i]))
		{
			return true;
		}
    }

    return false;
    //return m_buff_manager->HasBuff(6)||m_buff_manager->HasBuff(7);
}

//�ܷ������Ծ
bool Unit::isCanJump()
{
	for(uint16 i = 0; i < g_cant_jump_buff.size(); i++)
	{
		if (m_buff_manager->HasBuff(g_cant_jump_buff[i]))
			return false;
	}

	return true;
}

//�Ƿ񲻿ɱ���ҹ���
bool Unit::isCantAttackByPlayer() const
{
    for(uint16 i = 0; i < g_cant_attack_be_player.size(); i++)
    {
        if (m_buff_manager->HasBuff(g_cant_attack_be_player[i]))
            return true;
    }

    return false;
    //return m_buff_manager->HasBuff(6)||m_buff_manager->HasBuff(7);
}

void Unit::RandomMove(uint32 ms, float x, float y)
{
	if(!ms)	return;
	StopMoving();
	MovementGenerator::RandomPath(this,m_moving_path,ms, x, y);
	MoveTo(m_moving_path.size(),&m_moving_path[0],true);	
}

//�����ڲ�����ǰ��
void Unit::MoveTo(uint16 len, float *path, bool synchronous)
{
    ASSERT(path);   
//	ASSERT(isAlive());

	if(m_moving_path.empty() || &m_moving_path[0] != path )
	{
		m_moving_path.resize(len);
		std::copy(path,path+len,m_moving_path.begin());
	}

	ASSERT(m_moving_path.size() % 2 == 0);
	ASSERT(m_moving_path.size() >= 2);
	
    //����ǰ����
    float to_x = m_moving_path[0];
    float to_y = m_moving_path[1];
    float angle = GetAngle(to_x, to_y);
    float range = GetDistance(to_x, to_y);

    m_moving_ms = uint32(range * 10 * 1000 / GetMoveSpeed());

	//��Ҵ���״̬�������ƶ�,������ǿ��ͬ�����ͻ���
	ASSERT(synchronous || GetTypeId()!=TYPEID_PLAYER || ((Player*)this)->GetSession()->GetStatus()!=STATUS_TRANSFER);	

    m_moving_last_diff = 0;
	//�����movestop���Ǿ�Ҫ���ȹ㲥��
	if(synchronous && m_moving_path[0] == GetPositionX() && m_moving_path[1] == GetPositionY())
	{
		ASSERT(m_moving_path.size() == 2);
		packet *pkt;
		pkt = external_protocol_new_packet(MSG_MOVE_STOP);
		//��ǰ���ƶ���������Ҫ�ĳ�ͬ�����ˣ����Դ���������ͺ�
		*pkt << GetUIntGuid() << uint16(m_moving_path[0]) << uint16(m_moving_path[1]);
		update_packet_len(pkt);
		GetMap()->Broadcast(*pkt, this);
		external_protocol_free_packet(pkt);
	} 
	else
	{
		ByteArray *buff = ObjMgr.GridMallocByteArray();
		*buff << m_uint_guid;
		*buff << uint8(GetTypeId() == TYPEID_PLAYER && !synchronous ? 1 : 0);
#if 0
		*buff << uint16(m_moving_path.size() + 2);		//��Ҫ������ǰ����
		*buff << uint16(GetPositionX());
		*buff << uint16(GetPositionY());
		for (std::deque<float>::iterator it = m_moving_path.begin(); it != m_moving_path.end(); ++it)
			*buff << uint16(*it);	
#else
		//���·���Ǵ�Ļ�
		if(!WriteMovePath(*buff))
		{
			ObjMgr.GridFreeByteArray(buff);
			StopMoving(true);
			return;
		}
#endif
		GetGrid()->unit_move_blocks.push_back(buff);
	}

	//����������˷��˶�״̬��˵����ͬ����
	if(!IsMoving())
		m_moving_path.clear();
	else
		SetOrientation(angle);		//����ǲ���ͬ�����Ÿ��·���
}

void Unit::StopMoving(bool need_send)
{
	m_need_sync_pos = true;
    if (need_send)
    {		
		WorldPacket pkt(MSG_MOVE_STOP);
		pkt << GetUIntGuid() << uint16(GetPositionX()) << uint16(GetPositionY());
		update_packet_len(pkt.GetPktPtr());
		GetMap()->Broadcast(pkt.GetPkt(), this);		
    }
    m_moving_ms = 0;
    m_moving_path.clear();
}

void Unit::StopMoving(uint16 x, uint16 y)
{
	if(x == uint16(m_positionX) && y == uint16(m_positionY))
		return;
	SetPosition(float(x),float(y));	
	StopMoving(true);
}

//ת��Ŀ�귽��
void Unit::TurnToTarget(Unit *target)
{
	float new_or = GetAngle(target);
	SetOrientation(new_or);
}

//��
void Unit::Jump(float x, float y, uint32 time)
{
	ASSERT(!IsMoving());
	tea_pdebug("Jump form(%f,%f) to(%f,%f)",GetPositionX(),GetPositionY(),x,y);
    SetPosition(x, y);    
    SetLastJump(time);

    if(isCasing() || isSpellProcess())
        SpellStop();

    //30%�޵�һ��,s
	DoJumpScript(this);

    packet *pkt;
    pack_jump(&pkt, GetUIntGuid(), x, y);

    if(GetTypeId() == TYPEID_PLAYER)
        GetMap()->Broadcast(*pkt, static_cast<Player *>(this), true);
    else
        GetMap()->Broadcast(*pkt, this);
    external_protocol_free_packet(pkt);
}

//���ܴ�����
void Unit::UpdateSpellTrigger(uint32 diff)
{
	if(!m_spell_trigger.empty())
	{
		for(auto it = m_spell_trigger.begin(); it != m_spell_trigger.end();)
		{
			it->timer.Update(diff);
			if(it->count > 0 && it->timer.Passed())
			{
				it->count -= 1;
				Unit *target = GetMap()->FindUnit(it->target_guid);
				DoSpellCastScript(this, target, it->dst_x, it->dst_y, it->spell_id, it->spell_lv, this, it->data);
				it->timer.Reset2();
			}
			if(it->count <= 0)
				it = m_spell_trigger.erase(it);
			else
				++it;
		}
	}
}

void Unit::OnKilled(Unit *killer, uint16 id)
{
    //ֹͣ�ƶ�
    if(IsMoving())
        StopMoving(true);

    if(isCasing() || isSpellProcess() )
        SpellStop();

    SetDeathState(DEATH_STATE_CORPSE);
    ClearAttacker();
	if(killer && killer->GetTarget() == this)
		killer->SetTarget(NULL);
}

void Unit::Respawn(float x,float y)
{
	SetDeathState(DEATH_STATE_ALIVE);
	SetHealth(GetMaxHealth());
	/*SetPower(POWER_MANA,GetMaxPower(POWER_MANA));
	SetPower(POWER_ENERGY, GetMaxPower(POWER_ENERGY));*/
	//������Ǳ���������˵�������б�
	if(!(x ==0.0f && y == 0.0f))
	{
		SetPosition(x,y);		
	}
	StopMoving(true);

	//�����ɵ�ɶ
	DoAfterRespawn(this->GetMap(), this);
}

//��������
void Unit::Calcul_Attr()
{
	
}

bool Unit::IsFriendlyTo(Unit const *unit)
{
	//��ʱ��ȫ��NPC�����Ѻõ�
	if(this->GetTypeId() == TYPEID_PLAYER && unit->GetTypeId() == TYPEID_UNIT )
	{
		//uint32 GetUInt32(UNIT_FIELD_NPC_FLAG)
		if(GetTypeId() == TYPEID_UNIT && GetEntry() == unit->GetEntry())
			return true;
		if(((Creature const *)unit)->isServiceProvider())
			return true;
	}

	// ���Լ������Ѻõ�
	if(unit == this)
		return true;

	if (GetMap())
	{
		return DoIsFriendly(GetMap(),this,unit) != 0;
		/*auto it = m_friendly_cache.find((size_t)unit);
		if(it == m_friendly_cache.end())
		{
			int result = DoIsFriendly(GetMap(),this,unit);
			m_friendly_cache.insert(std::make_pair((size_t)unit,result));
			return result!=0;		
		}
		return it->second != 0;*/
	}

    return false;
}

void Unit::InvalidFriendlyCache(Unit *unit /* = nullptr */)
{
	//����е����ṩĿ��,��ֻ������,���ܽϺ�
	if(unit)
	{
		m_friendly_cache.erase(size_t(unit));		
		unit->m_friendly_cache.erase((size_t)this);
		return;
	}
	//���е��ҵ�,�Լ���Ϊ��Ŀ��Ķ�ʧЧ
	m_friendly_cache.clear();
	for (auto it:m_grid->notice_grid)
	{
		for (auto it_unit:it->players)
		{
			it_unit->m_friendly_cache.erase((size_t)this);
		}
		for (auto it_unit:it->creatures)
		{
			it_unit->m_friendly_cache.erase((size_t)this);
		}		
	}	
}

void Unit::InvalidFriendlyCache(Grid *grid)
{
	for (auto it_unit:grid->players)
	{
		InvalidFriendlyCache(it_unit);
	}
	for (auto it_unit:grid->creatures)
	{
		InvalidFriendlyCache(it_unit);
	}
}

void Unit::ClearAttacker(bool destructor)
{
	if(destructor)//�����ڹرճ�������ʱ����գ���������û��ȫ�˳���ʱ�����
	{
		m_attacker_player.clear();
		m_attacker_unit.clear();
		return;
	}
	if(!m_map || (m_attacker_unit.empty() && m_attacker_player.empty()))
		return;

    for(auto iter = m_attacker_unit.begin(); iter != m_attacker_unit.end(); )
    {
		Creature *attacker = dynamic_cast<Creature*>(m_map->FindUnit(*iter));
		++iter;
		if(!attacker)
			continue;

		attacker->m_threatMgr.Del(this);

        //����ұ�ɱ�Ļ��Դ����ΪĿ��Ĺ������ս��Ʒ������
        if (GetTypeId() == TYPEID_PLAYER)           
            attacker->DelOwnerShip(GetUIntGuid());

        if(attacker->GetTarget() == this)
        {
            attacker->SetTarget(NULL);
        }

        attacker->DelAttacker(GetUIntGuid());
    }

	for(auto iter = m_attacker_player.begin(); iter != m_attacker_player.end(); ++iter)
	{
		Player *attacker = dynamic_cast<Player*>(m_map->FindUnit(*iter));
		if(!attacker)
			continue;
		
		if(attacker->GetTarget() == this)
		{
			attacker->SetTarget(NULL);
		}

		attacker->DelAttacker(GetUIntGuid());
	}

    m_attacker_player.clear();
	m_attacker_unit.clear();
}

//��ӹ�����
void Unit::AddAttacker(Unit *unit) 
{
	if(!unit)
		return;
	if(unit->GetTypeId() == TYPEID_PLAYER)
		m_attacker_player.insert(unit->GetUIntGuid());
	else
		m_attacker_unit.insert(unit->GetUIntGuid());
}

//ɾ��������
void Unit::DelAttacker(uint32 unit, bool isDelOwnerShip) 
{
	this->removePositionInfo(unit);

	if(m_attacker_player.find(unit) != m_attacker_player.end())
	{
		m_attacker_player.erase(unit);
		return;
	}
	if(m_attacker_unit.find(unit) != m_attacker_unit.end())
	{
		if (isDelOwnerShip)
		{
			Creature *attacker = dynamic_cast<Creature*>(m_map->FindUnit(unit));
			if (attacker && GetTypeId() == TYPEID_PLAYER)
				attacker->DelOwnerShip(GetUIntGuid());
		}		
		m_attacker_unit.erase(unit);
		return;
	}
}

//��ұ����﹥��ʱ��ش���
void Unit::DoPVEEvent(Player* target)
{
	//PKʱ����½ű� ��һЩӦ�øɵ���
	DOPlayerPVEScript(this,target);
}


//ֹͣʩ��
void Unit::SpellStop(bool clear_auto_spell,bool to_self)
{
	//packet *pkt_stop;
	//pack_spell_stop(&pkt_stop, GetGuid().c_str());
	//if (GetTypeId()==TYPEID_PLAYER)
	//	GetMap()->Broadcast(*pkt_stop,(Player*)this,to_self);
	//else
	//	GetMap()->Broadcast(*pkt_stop,this);
	//external_protocol_free_packet(pkt_stop);

    if (isCasing())
        clearUnitState(UNIT_STAT_CAST_SPELL);

    if (isSpellProcess())
        clearUnitState(UNIT_STAT_SPELL_PROCESS);

    //��յ�ǰĿ������ͼ���-
    SetTargetPos(0.0f, 0.0f);
    SetCurSpell(0);

}

void Unit::SetCurSpell(uint32 id)
{
	m_cur_spell = id;
}

void Unit::CastSpell(uint32 spell_id, float x, float y)
{
    //�㲥XX��ʼʩ��    
    SetCurSpell(spell_id);
	//����ʩ����ʶ
    addUnitState(UNIT_STAT_CAST_SPELL);
	SetTargetPos(x, y);

	if(GetMap() == NULL) {
		SpellStop();
		return;
	}
	//m_spellTimer.Update(diff);

	//if (!m_spellTimer.Passed())
	//    return;

	//�������ʩ����ֹͣʩ��
	if (IsCantCast()||!isAlive()) {
		if (isCasing())
			SpellStop();
		return;
	}

	//ʩ������

	//������ң�ֱ��ͨ��
	if(GetTypeId() == TYPEID_PLAYER && !DoIsEnoughConsumptionCast((Player*)this, GetCurSpell()))	//����
	{
		tea_perror("���Ĳ���");
		SpellStop();
		return;
	}

	//����CD
	SetSpellCD(GetCurSpell());
	//����
	if(GetTypeId() == TYPEID_PLAYER)
		DoSpellConsumption((Player*)this, GetCurSpell());
	
	int spellLevel = 1;
	if (this->GetCurSpellLevel()) {
		spellLevel = this->GetCurSpellLevel();
	}
	
	DoSpellCastScript(this, GetTarget(), x, y, GetCurSpell(), spellLevel, NULL);

	// ����Ǽ��ܷ�����õ�
	//TODO: SpellStop();
}

void Unit::CalSpellCastInfo()
{
	uint32 count = Map::fighting_info_binlog.GetUInt32(MAX_FIGHTING_INFO_INT_NOW_INDEX);
	for(uint32 i = 0; i < count; i++)
    {
		uint32 start = i * MAX_FIGHTING_INFO_INT + MAX_FIGHTING_INFO_INT_START;
		uint32 start_str = i * MAX_FIGHTING_INFO_STRING + FIGHTING_INFO_STRING_FIELD_START;
		uint32 target = shortGUID(Map::fighting_info_binlog.GetStr(start_str + FIGHTING_INFO_STRING_TARGET).c_str());
		uint32 attack_type = Map::fighting_info_binlog.GetByte(start + FIGHTING_INFO_INT_UINT8, 3);
		double damage = Map::fighting_info_binlog.GetDouble(start + FIGHTING_INFO_INT_VALUES);

		if (!target)
			continue;
		if(attack_type == HITINFO_GEDANG)
			continue;		//�񵲲������˺�	
		Unit *pVictim = GetMap()->FindUnit(target);

		if(!pVictim)
		{
			tea_perror("%s CalSpellCastInfo GetMap()->FindUnit %u,%u is NULL", GetName().c_str(), GetMapId(), target);
			continue;
		}

		uint32 prevHp = pVictim->GetHealth();
		//�����ȸ�һ�Σ�ʡ�ĺ���ûִ�п�Ѫû��
		Map::fighting_info_binlog.SetUInt32(start + FIGHTING_INFO_INT_HP, pVictim->GetHealth());

		Creature::AddTheOwnership(pVictim, this);
		
		//0��ûʲô�ô�����
		if(damage == 0)
		{	
			// ��Ҵ����MISSʱҲҪ����
			if(pVictim->GetTypeId() == TYPEID_UNIT) {
				dynamic_cast<Creature *>(pVictim)->m_threatMgr.Add(this, 1);
			}
			continue;
		}
		//Ŀ������Ҳ��Ҫ������
		if((!pVictim->isAlive() || !pVictim->GetHealth()) && damage != 0 && i != 0)
		{
			//��ʩ������գ���ͻ���Լ�������ʩ����Ϊ0���򱾴��˺���Ч��
			Map::fighting_info_binlog.SetStr(start_str + FIGHTING_INFO_STRING_TARGET, "");
			//tea_pdebug("���˾Ͳ��ô������˺������");
			continue;
		}
		if(GetTypeId() == TYPEID_UNIT)
			static_cast<Creature *>(this)->AI_GiveDamage(pVictim,damage);

		////�˺�����
		if(pVictim->GetTypeId() == TYPEID_UNIT)
		{
			// �����ܵ��˺�
			double dam = ceil(damage);
			if (pVictim->GetHealth() < dam) {
				dam = pVictim->GetHealth();
			}
			static_cast<Creature *>(pVictim)->AI_DamageTaken(this, dam);
		}		 
		else if (pVictim->GetTypeId() == TYPEID_PLAYER)
		{
			//PVP�Ĵ���
			if(GetTypeId() == TYPEID_PLAYER && this != pVictim)
			{

				((Player *)this)->DoPvPEvent((Player *)pVictim);
				((Player*)this)->resetPVPStateTime();
				((Player *)this)->SetPVPstate();
				//ֻ����������pk��ʱ��Ž���ս��״̬
				((Player *)this)->resetCombatStateTime();	
				((Player *)this)->SetPeaceModeCDIfEnabled();

				((Player*)pVictim)->resetPVPStateTime();
				((Player *)pVictim)->SetPVPstate();
				//ֻ����������pk��ʱ��Ž���ս��״̬
				((Player *)pVictim)->resetCombatStateTime();
				((Player *)pVictim)->SetPeaceModeCDIfEnabled();
			}
			// ����ܵ��˺�
			double dam = ceil(damage);
			if (pVictim->GetHealth() < dam) {
				dam = pVictim->GetHealth();
			}
			OnPlayerHurted((Player*)this, (Player*)pVictim, dam);
			//��ұ����﹥��
			if(GetTypeId() == TYPEID_UNIT)
				((Unit*)this)->DoPVEEvent((Player*)pVictim);
		}
		damage = ceil(damage);				//��߸��˺�ֵȡ����
		if(damage < 0)
			tea_pdebug("CalSpellCastInfo damage is %d",damage);
		ASSERT(damage >= 0);				//����˺�����Ϊ����
		if(pVictim->GetHealth() <= damage)
		{
			Map::fighting_info_binlog.SetByte(start + FIGHTING_INFO_INT_UINT8, 0, 1);

			if(Map::fighting_info_binlog.GetByte(start + FIGHTING_INFO_INT_UINT8, 3) == HITINFO_BLOWFLY)
				Map::fighting_info_binlog.SetByte(start + FIGHTING_INFO_INT_UINT8, 3, HITINFO_NORMALSWING);
		}

		pVictim->ModifyHealth((int)-damage, false);		
		Map::fighting_info_binlog.SetDouble(start + FIGHTING_INFO_INT_VALUES, damage);
		Map::fighting_info_binlog.SetUInt32(start + FIGHTING_INFO_INT_HP, pVictim->GetHealth());

		DoOnHpChanged(pVictim, (uint32)ceil(prevHp * 1.0 / pVictim->GetMaxHealth() * 100));
	}
}

void Unit::AfterCalSpellCastInfo()
{	
	uint32 count = Map::fighting_info_binlog.GetUInt32(MAX_FIGHTING_INFO_INT_NOW_INDEX);
	if(count == 0)
		return;
	
	for(uint32 i = 0; i < count; i++)
	{
		uint32 start = i * MAX_FIGHTING_INFO_INT + MAX_FIGHTING_INFO_INT_START;
		uint32 start_str = i * MAX_FIGHTING_INFO_STRING + FIGHTING_INFO_STRING_FIELD_START;
		uint32 casterUint = shortGUID(Map::fighting_info_binlog.GetStr(start_str + FIGHTING_INFO_STRING_CASTER).c_str());
		uint32 target = shortGUID(Map::fighting_info_binlog.GetStr(start_str + FIGHTING_INFO_STRING_TARGET).c_str());

		uint32 attack_type = Map::fighting_info_binlog.GetByte(start + FIGHTING_INFO_INT_UINT8, 3);
		if (!target)		
			continue;

		Unit *pVictim = GetMap()->FindUnit(target);
		if(!pVictim)
		{
			tea_perror("%s CalSpellCastInfo GetMap()->FindUnit %u,%u is NULL",GetName().c_str(),GetMapId(),target);
			continue;
		}

		if (!pVictim->isAlive())
		{
			continue;
		}

		if(pVictim->GetTypeId() == TYPEID_UNIT)
		{
			double damage = Map::fighting_info_binlog.GetDouble(start + FIGHTING_INFO_INT_VALUES);
			static_cast<Creature *>(pVictim)->AI_DamageDeal(this, damage);
			
			if (this->GetTypeId() == TYPEID_PLAYER) {
				this->GetMap()->PlayerHitCreature(pVictim->GetUIntGuid(), ((Player*)this)->GetSession()->GetGuid());
			}
		}
		
		if(pVictim->GetHealth())
		{
			//������󹥻�����
			if(!this->IsFriendlyTo(pVictim))
			{
				SetLastVictim(target);//����Ϊ���ŵ���ֻ,����������ˣ���movement�л����
				pVictim->AddAttacker(this);
			}
		}
		else //������������
		{
			pVictim->OnKilled(this);

			if(GetTypeId() == TYPEID_UNIT)
			{
				dynamic_cast<Creature *>(this)->m_threatMgr.Del(pVictim);
				dynamic_cast<Creature *>(this)->AI_KilledUnit(pVictim);
			}

			// ���ڷ���Ҳ��������˺�, ����Ҫ�ҵ�ʵ�ʵĸ��˺���Դunit
			Unit *caster = GetMap()->FindUnit(casterUint);
			if (caster) {
				DoHandlePassiveEffect(pVictim, caster, PASSIVE_DISPATCH_TYPE_DEAD);
				DoHandlePassiveEffect(caster, pVictim, PASSIVE_DISPATCH_TYPE_ENEMY_DEAD);
			}
		}
	}	
}

//�ж��Ƿ����ʩ��
bool Unit::IsCantCast()
{
	return GetBit(UNIT_FIELD_FLAGS, UNIT_FIELD_FLAGS_CANT_CAST);
}

//��ʼ����
int Unit::Acting(Unit *act_target)
{
    //���óɱ���״̬
    m_isActing = true;
    //SetTarget(act_target);
    return 0;
}

//ֹͣ����
int Unit::StopActing()
{
    //���óɱ���״̬
    m_isActing = false;
    //SetTarget(NULL);
    return 0;
}

//������
void Unit::BlowFly(Unit* attacker,uint32 space, uint16 &destX, uint16 &destY)
{
	float angle = attacker->GetAngle(this);
	float nowx = this->GetPositionX();
	float nowy = this->GetPositionY();
	float x = nowx + space * cos(angle);
	float y = nowy + space * sin(angle);
	//nx,ny������û�ã����Ǻ�����Ҫ
	//lx,ly����ʹ�õ�����
	uint16 lx,ly,nx,ny;
	destX = 0;
	destY = 0;
	this->StopMoving(true);
	this->GetMap()->GetMapTemp()->IsCanRun(nowx, nowy, x, y, lx, ly, nx, ny, false);
	//�пɱ����˵����
	if(lx != 0 && ly != 0)
	{
		this->SetPosition(lx, ly);
		m_isBlowFly = true;	
		destX = lx;
		destY = ly;
		tea_pdebug("����[%s] �����ɵ�%f:%f",GetName().c_str(), (float)lx,(float)ly);
	}
	else
	{
		float tempx, tempy;
		this->GetPosition(tempx, tempy);
		destX = (uint16)tempx;
		destY = (uint16)tempy;
	}
}

//////////////////////////////////////////////////////////////////////////
//for Unit static

//��ȡĿ������
int Unit::LuaGetPos(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
    //LuaStackAutoPopup autoPopup(scriptL);
    int n = lua_gettop(scriptL);
    ASSERT(n == 1);
    Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

    if (!unit)
    {
        tea_perror("��ȡ�������ͣ�Ŀ��Ϊ��");
        lua_pushnumber(scriptL, 0);
        lua_pushnumber(scriptL, 0);        
    }
	else
	{
		float pos_x, pos_y;
		unit->GetPosition(pos_x, pos_y);
		lua_pushnumber(scriptL, pos_x);
		lua_pushnumber(scriptL,	pos_y);
	}   
    return 2;
}

int Unit::LuaGetTarget(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

	if (!unit)
	{
		tea_perror("��ȡ�������ͣ�Ŀ��Ϊ��");
		//lua_pushlightuserdata(scriptL, 0);
		lua_pushnil(scriptL);
		return 1;
	}
	if (unit->GetTarget())
		lua_pushlightuserdata(scriptL, unit->GetTarget());
	else
		lua_pushnil(scriptL);
	return 1;
}

//��������Ŀ��
int Unit::LuaSetTarget(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(n == 1)
		unit->SetTarget(NULL);
	else
		unit->SetTarget((Unit *)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit));
	return 0;
}

//��������������
int Unit::LuaSetCalculAttr(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!unit)
		return 0;
	unit->SetCalculAttrStage(true);
	return 0;
}

int Unit::LuaCastSpell(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 4);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!unit)
		return 0;
	uint32 spell_id = (uint32)LUA_TONUMBER(scriptL, 2);
	float x = (float)LUA_TONUMBER(scriptL, 3);
	float y = (float)LUA_TONUMBER(scriptL, 4);
	Unit *target = NULL;
	if(n >= 5)
		target = (Unit *)LUA_TOUSERDATA(scriptL, 5, ObjectTypeUnit);
	if (target)
		unit->SetTarget(target);

	unit->CastSpell(spell_id,x,y);
	return 0;
}


//����Ŀ������
int Unit::LuaSetPos(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
    //LuaStackAutoPopup autoPopup(scriptL);
    int n = lua_gettop(scriptL);
    ASSERT(n >= 3);
    Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
    float _x = (float)LUA_TONUMBER(scriptL, 2);
    float _y = (float)LUA_TONUMBER(scriptL, 3);

    if (!unit)
    {
        tea_perror("LuaSetPos ��ȡ�������ͣ�Ŀ��Ϊ��");
        return 0;
    }

    unit->SetPosition(_x, _y);
   
	if(n == 4)
	{
		unit->StopMoving(LUA_TOBOOLEAN(scriptL, 4) != FALSE);
	}

	return 0;
}

//��ɱ����
int Unit::LuaKillUnit(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Unit *killer = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	Unit *pVictim = (Unit *)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit);

	if (!killer || !pVictim)
	{
		tea_perror("������ɱ�����ָ��Ϊ��");
		lua_pushnumber(scriptL, 0);
		return 1;
	}
	if (!pVictim->isAlive())
	{
		return 0;
	}
	
	//����ս��Ʒ������
	Creature::AddTheOwnership(pVictim, killer);

	pVictim->SetHealth(0);
	pVictim->OnKilled(killer);
	if(killer->GetTypeId() == TYPEID_UNIT)
	{
		dynamic_cast<Creature *>(killer)->m_threatMgr.Del(pVictim);
		dynamic_cast<Creature *>(killer)->AI_KilledUnit(pVictim);
	}

	return 0;
}

int Unit::LuaIsFriendlyTo(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
    //LuaStackAutoPopup autoPopup(scriptL);
    int n = lua_gettop(scriptL);
    ASSERT(n == 2);
    Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);;
    Unit *unit1 = (Unit *)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit);;

    if (!unit || !unit1)
    {
        lua_pushnumber(scriptL, -1);
        return 1;
    }

    uint8 res = (uint8)unit->IsFriendlyTo(unit1);
    lua_pushnumber(scriptL, res);
    return 1;
}

//�Ƿ��ܱ����У���ʱֻ��0��1��0�ɻ��У�1���ɻ���,-1��ʾ����
int Unit::LuaIsCanHit(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
    //LuaStackAutoPopup autoPopup(scriptL);
    int n = lua_gettop(scriptL);
    ASSERT(n == 1);
    Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

    if (!unit)
    {
        tea_perror("��ȡ�Ƿ�ɻ��У�Ŀ��Ϊ��");
        lua_pushnumber(scriptL, -1);
        return 1;
    }

    //Ŀǰֻ�������������״̬
    if (unit->GetTypeId() == TYPEID_UNIT)
    {
        //����״̬�򲻵�
        if (((Creature *)unit)->GetEvadeState())
        {
            lua_pushnumber(scriptL, 1);
            return 1;
        }
    }

    //��õ�
    lua_pushnumber(scriptL, 0);
    return 1;
}

//�Ƿ��ڱ��� 0��1��
int Unit::LuaIsActing(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
    //LuaStackAutoPopup autoPopup(scriptL);
    int n = lua_gettop(scriptL);
    ASSERT(n == 1);
    Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

    if (!unit)
    {
        tea_perror("��ȡ����״̬��Ŀ��Ϊ��");
        lua_pushnumber(scriptL, 0);
        return 1;
    }

    //	uint32 pro = unit->GetCombatRate((Combat_Rate)rate_type);
    lua_pushnumber(scriptL, (uint8)unit->isActing());
    return 1;
}

int Unit::LuaIsInvincible(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
    //LuaStackAutoPopup autoPopup(scriptL);
    int n = lua_gettop(scriptL);
    //ASSERT(n == 1);

    Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

    if (!unit)
    {
        tea_perror("��ȡ�޵�״̬��Ŀ��Ϊ��");
        lua_pushnumber(scriptL, 0);
        return 1;
    }

    uint8 a = (uint8)unit->isInvincible();
	//tea_pdebug("a=%d",a);
    lua_pushnumber(scriptL, a);
    return 1;
}

//������й����ĳ����ҵĳ��
int Unit::LuaDelThreat(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
    //LuaStackAutoPopup autoPopup(scriptL);
    int n = lua_gettop(scriptL);
    ASSERT(n == 1);

    Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

    if (!unit)
    {
        tea_perror("������й����ĳ����ҵĳ�ޣ�Ŀ��Ϊ��");
        return 0;
    }

    unit->ClearAttacker();
    return 0;
}

int Unit::LuaSetActing(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
    int n = lua_gettop(scriptL);
    ASSERT(n == 2);
    Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

    if (!unit)
    {
        tea_perror("LuaSetActing��Ŀ��Ϊ��");
        return 0;
    }

    unit->m_isActing = LUA_TOBOOLEAN(scriptL, 2);
    return 0;
}

int Unit::LuaGetMap(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!unit)
	{
		tea_perror("GetMapId��Ŀ��Ϊ��");
		lua_pushnil(scriptL);
		return 1;
	}
	if(unit->GetMap())
		lua_pushlightuserdata(scriptL, unit->GetMap());
	else
		lua_pushnil(scriptL);
	return 1;
}

int Unit::LuaGetMapID(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!unit || !unit->GetMap())
	{
		tea_perror("LuaGetMapID��Ŀ��Ϊ�ջ��ߵ�ͼΪ��");
		lua_pushnumber(scriptL,0);
		return 1;
	}
	lua_pushnumber(scriptL,unit->GetMapId());
	return 1;
}

//������
int Unit::LuaBlowFly(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Unit *attacker = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	Unit *target = (Unit *)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit);
	uint32 space = (uint32)LUA_TONUMBER(scriptL, 3);
	if (!attacker || !target)
	{
		tea_perror("LuaBlowFly��Ŀ��Ϊ��");
		return 0;
	}

	uint16 dstx, dsty;
	target->BlowFly(attacker,space,dstx, dsty);

	lua_pushinteger(scriptL, dstx);
	lua_pushinteger(scriptL, dsty);
	return 2;
}

//����
int Unit::LuaRespawn(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!unit)
	{
		tea_perror("LuaRespawn:unit is null");
		return 0;
	}
	if(unit->isAlive())
	{
		tea_perror("LuaRespawn:unit is alive");
		return 0;
	}

	uint32 respawn_type = (uint32)LUA_TOINTEGER(scriptL, 2);
	uint32 percent = 100;
	if (n>=3)
	{
		percent = (uint32)LUA_TONUMBER(scriptL, 3);
	}

	if(unit->GetTypeId() == TYPEID_PLAYER)
	{
		Player *player = (Player *)unit;
		if(respawn_type == RESURRPCTION_HUANHUNDAN)
		{
			player->GetMap()->AddRespanPlayer(player);
		}
		WriteRelive(player->GetSession()->GetAccount(), player->GetSession()->GetGuid(), respawn_type, player->GetMapId());
	}
	if(respawn_type != RESURRPCTION_HUANHUNDAN)
	{
		//����
		unit->Respawn();
		if (percent != 100)
		{
			unit->SetHealth(unit->GetMaxHealth() * percent / 100);
			/*unit->SetPower(POWER_MANA, unit->GetMaxPower(POWER_MANA) * percent / 100);
			unit->SetPower(POWER_ENERGY, unit->GetMaxPower(POWER_ENERGY) * percent / 100);*/
		}
		if (unit->GetTypeId() == TYPEID_PLAYER)
		{//�������ҵĻ����ֶ�����ͬ�������飬���⻹û���ü�ͬ�����е�ͼ��
			Player* player = dynamic_cast<Player*>(unit);
			if(player && player->GetSession())
			{
				player->SyncUnitToPlayerData();				
			}
		}	
	}
	return 0;
}

//Ϲ�� ����
int Unit::LuaRandomMove(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 duration = (uint32)LUA_TONUMBER(scriptL, 2);
	if (!unit)
	{
		tea_perror("LuaRespawn��Ŀ��Ϊ��");
		return 0;
	}
	float x = -1, y = -1;
	if (n == 4)
	{
		x = (float)LUA_TONUMBER(scriptL, 3);
		y = (float)LUA_TONUMBER(scriptL, 4);
	}
	
	unit->RandomMove(duration,x,y);
	return 0;
}

//ֹͣʩ��
int Unit::LuaSpellStop(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 1)
	for (int i = 1; i <= n; i++)
	{
		Unit *unit = (Unit*)LUA_TOUSERDATA(scriptL, i, ObjectTypeUnit);
		if(unit)
			unit->SpellStop();
	}
	return 0;
}

int Unit::LuaGetCurSpell(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(unit)
	{
		lua_pushnumber(scriptL, unit->GetCurSpell());
	}
	else
	{
		lua_pushnumber(scriptL, 0);
	}

	return 1;
}


int Unit::LuaSetCurSpell(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 spell_id = (uint32)LUA_TONUMBER(scriptL, 2);
	
	if(unit)
	{
		scriptL, unit->SetCurSpell(spell_id);
	}

	return 0;
}

int Unit::LuaHasUnitState(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 state = (uint32)LUA_TONUMBER(scriptL, 2);
	if(unit && unit->hasUnitState(state))
	{
		lua_pushboolean(scriptL, true);		
	}
	else
	{
		lua_pushnil(scriptL);		
	}	
	return 1;
}

int Unit::LuaAddUnitState(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 state = (uint32)LUA_TONUMBER(scriptL, 2);

	unit->addUnitState(state);
	return 0;
}

int Unit::LuaIsMoving(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1)
	Unit* unit = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (!unit)
	{
		lua_pushboolean(scriptL, 1);
		tea_perror("LuaGetPlayeCurFightStatus Player is null or target is null");
		return 1;
	}

	lua_pushboolean(L, unit->IsMoving());

	return 1;
}

int Unit::LuaGetMoveSpeed(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);

	if (!unit)
	{
		tea_perror("��ȡ�ƶ��ٶȣ�Ŀ��Ϊ��");
		lua_pushnumber(scriptL, -1);
		return 1;
	}

	//	uint32 pro = unit->GetCombatRate((Combat_Rate)rate_type);
	lua_pushnumber(scriptL, unit->GetMoveSpeed());
	return 1;
}

int Unit::LuaSetMoveSpeed(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 move_speed = (uint32)LUA_TONUMBER(scriptL, 2);

	if (!unit)
	{
		tea_perror("�����ƶ��ٶȣ�Ŀ��Ϊ��");
		lua_pushnumber(scriptL, 0);
		return 1;
	}

	unit->SetMoveSpeed(move_speed);

	return 0;
}

//���������ƶ��ķ���(���Ƕ�)
int Unit::LuaGetOrientation(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (unit)
	{
		lua_pushnumber(scriptL, unit->GetOrientation());
	}
	else
	{
		lua_pushnil(scriptL);
	}
	
	return 1;
}
//���������ƶ��ķ���(���Ƕ�)
int Unit::LuaSetOrientation(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	float angle = (float)LUA_TONUMBER(scriptL, 2);
	if (unit)
	{
		unit->SetOrientation(angle);
	}
	
	return 0;
}
//����ֹͣ�ƶ�
int Unit::LuaStopMoving(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint8 flag = 0;
	if (n >= 2)
		flag = (uint8)LUA_TONUMBER(scriptL, 2);

	if (unit && unit->IsMoving())
	{
		if (flag)
			unit->StopMoving(true);
		else
			unit->StopMoving();
	}
	return 0;
}

//�����ƶ���
int Unit::LuaMoveTo(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 len = (uint16)LUA_TONUMBER(scriptL, 2);
	string s_path = (string)LUA_TOSTRING(scriptL, 3);
	Tokens tokens;
	StrSplit(tokens, s_path, ',');
	if(tokens.empty())
		return 0;
	vector<float> new_path;
	for (uint16 i = 0;i< len;i = i + 2)
	{
		if(tokens[i].empty() || tokens[i+1].empty())
			continue;
		float xx = 0;//(float)LUA_TONUMBER(scriptL, i+3);
		float yy = 0;//(float)LUA_TONUMBER(scriptL, i+4);
		sscanf(tokens[i].c_str(),"%f",&xx);
		sscanf(tokens[i+1].c_str(),"%f",&yy);
		new_path.push_back(xx);
		new_path.push_back(yy);

	//	if(i == len - 2)
	//	{
	//		if(unit->GetTypeId() == TYPEID_UNIT)
	//		{
	//			static_cast<Creature*>(unit)->SetBornPos(xx,yy);
	//		}
	//	}
	}
	
	//float t_x = (float)LUA_TONUMBER(scriptL, 2);
	//float t_y = (float)LUA_TONUMBER(scriptL, 3);

	if (unit && unit->isCanMove())
		unit->MoveTo(new_path.size(),&new_path[0]);

	return 0;
}

//��þ����int guid
int Unit::LuaGetIntGuid(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if (unit)
	{
		lua_pushnumber(scriptL, unit->m_uint_guid);
	}
	else
	{
		lua_pushnil(scriptL);
	}
	return 1;
}

//��ȡ�����ƶ��յ�����
int Unit::LuaGetMoveEndPos(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n > 0);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	float x = 0, y = 0;
	if(unit && !unit->m_moving_path.empty())
	{
		x = unit->m_moving_path[unit->m_moving_path.size() - 2];
		y = unit->m_moving_path[unit->m_moving_path.size() - 1];
	}
	
	lua_pushnumber(scriptL, x);
	lua_pushnumber(scriptL, y);
	
	return 2;
}

//�����Ƿ������Ծ
int Unit::LuaIsCanJump(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Unit *unit = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	bool b = true;
	if (unit)
		b = unit->isCanJump();
	lua_pushboolean(scriptL, b);
	return 1;
}

//��Ӽ��ܶ�ʱ��
int Unit::LuaAddSpellTrigger(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 9);
	Unit *caster = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!caster)
		return 0;
	spell_trigger spell_trigger_info;
	const char *target_guid = LUA_TOSTRING(scriptL, 2);
	spell_trigger_info.target_guid = shortGUID(target_guid);
	spell_trigger_info.dst_x = (float)LUA_TONUMBER(scriptL, 3);
	spell_trigger_info.dst_y = (float)LUA_TONUMBER(scriptL, 4);
	spell_trigger_info.spell_id = (int)LUA_TOINTEGER(scriptL, 5);
	spell_trigger_info.spell_lv = (int)LUA_TOINTEGER(scriptL, 6);
	uint32 interval = (uint32)LUA_TOINTEGER(scriptL, 7);
	spell_trigger_info.count = (int)LUA_TOINTEGER(scriptL, 8);
	const char *data = LUA_TOSTRING(scriptL, 9);
	strcpy(spell_trigger_info.data, data);
	spell_trigger_info.timer.SetInterval(interval);
	spell_trigger_info.timer.SetCurrent(0);
	caster->AddSpellTrigger(spell_trigger_info);
	return 1;
}

//ɾ��һ�����ܴ�����
int Unit::LuaDelSpellTrigger(lua_State* scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Unit *caster = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!caster)
		return 0;

	uint32 spellId = (uint32)LUA_TONUMBER(scriptL, 2);
	for(auto it = caster->m_spell_trigger.begin(); it != caster->m_spell_trigger.end(); ++ it) {
		if (it->spell_id == spellId) {
			// �Ѵ��������ĳ�0, ���Լ����ͷŵ�
			it->count = 0;
			it->timer.SetCurrent(0);
		}
	}
	return 1;
}

//�ѺöȻ���ʧЧ
int Unit::LuaInvalidFriendlyCache(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	Unit *me = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	Unit *target = nullptr;
	if(n >= 2)
		target = (Unit *)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit);

	if (!me )
		return 0;

	me->InvalidFriendlyCache(target);	
	return 0;
}

int Unit::LuaSetHealth(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	Unit *me = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint32 val = (uint32)LUA_TOINTEGER(scriptL, 2);
	me->SetHealth(val);
	return 0;
}

int Unit::LuaModifyHealth(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	Unit *me = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	double val = LUA_TONUMBER(scriptL, 2);
	me->ModifyHealth(val);
	return 0;
}

// ��ʼ��Ծ
int Unit::LuaCallJumpStart(lua_State* scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);

	ASSERT(n == 3);
	Unit *me = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	uint16 dx = (uint16)LUA_TONUMBER(scriptL, 2);
	uint16 dy = (uint16)LUA_TONUMBER(scriptL, 3);

	me->SetPosition(dx, dy);
	ByteArray *pkt = ObjMgr.GridMallocByteArray();
	*pkt << me->GetUIntGuid() << dx << dy;
	me->GetGrid()->unit_jump_blocks.push_back(pkt);

	return 0;
}

//����ӵ���ߣ���������ʱ��Ҫ�ϱ�
int Unit::LuaSetOwner(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Unit *me = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	string onwer_guid = LUA_TOSTRING(scriptL, 2);
	me->SetOwner(onwer_guid);
	return 0;
}