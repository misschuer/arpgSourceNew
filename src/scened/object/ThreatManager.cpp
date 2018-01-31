#include "scened_app.h"
#include "ThreatManager.h"
#include "Unit.h"
#include "Player.h"
#include "Grid.h"
#include "Creature.h"
#include "LootManager.h"
#include "Map.h"

//////////////////////////////////////////////////////////////////////////
//for ThreatManager

void ThreatManager::Initialize(Creature *unit, uint32 _visionradius, uint32 _actionradius)
{
	me = unit;
	
	actionradius = float(_actionradius);
	visionradius = float(_visionradius);
	me->GetBornPos(bornX, bornY);
}

Unit *ThreatManager::GetTarget()
{
	Unit *target = NULL;
	uint32 threat = 0;
	for(TargetMap::iterator iter = m_targetMap.begin(); iter != m_targetMap.end(); ++iter)
	{
		if(threat < iter->second.first + iter->second.second) 
		{
			Unit *unit = me->GetMap()->FindUnit(iter->first);
			if (!unit)
				continue;
			target = unit;
			threat = iter->second.first + iter->second.second;
		}
	}
	return target;
}

//���ӹ������
void ThreatManager::Add(Unit *target,uint32 v)
{ 
	if(me->GetEvadeState()) return;
	TargetMap::iterator iter = m_targetMap.find(target->GetUIntGuid());
	if(iter != m_targetMap.end())
	{
		iter->second.first += v;
	}
	else
	{
		if (!me->IsFriendlyTo(target))
			m_targetMap.insert(TargetMap::value_type(target->GetUIntGuid(), ThreatValue(v, 0)));
		//tea_pdebug("me[%s] ��[%s] ���ӳ�� ",me->GetName(),target->GetName());
		//target->AddAttacker(me);

		//���γ�������Ұ
		me->AI_MoveInLineOfSight(target);
	}
}

void ThreatManager::Del(Unit *target, bool isDelOwnerShip)
{
	TargetMap::iterator iter = m_targetMap.find(target->GetUIntGuid());
	if(iter != m_targetMap.end()) 
	{
		m_targetMap.erase(iter);
		target->DelAttacker(me->GetUIntGuid(), isDelOwnerShip);
	}
}

void ThreatManager::Clear()
{
	for(TargetMap::iterator iter = m_targetMap.begin(); iter != m_targetMap.end(); ++iter)
	{
		//g_obj_mgr->FindObject();
	 	Unit *unit = me->GetMap()->FindUnit(iter->first);
		if (!unit)
			continue;
		unit->DelAttacker(me->GetUIntGuid());
	}
	m_targetMap.clear();

	me->SetTarget(NULL);
}

void ThreatManager::Update(uint32 )
{
	ASSERT(me);	
	ASSERT(me->isAlive());
	//Ŀǰû������ģʽ
	//if(me->GetEvadeState()) return;
	
	//����Ƿ�����
	if(me->GetReactState() == REACT_DEFENSIVE)
		return;

	float x,y;
	me->GetBornPos(x,y);

	//�������Χֱ�ӷ���
	if((uint32)me->GetDistance(x,y) > actionradius) 
	{
		Clear();
		//���������
		me->ResetOwnerShip();
		//�д���ȶ
		//me->ClearAttacker();
		return;
	}
	//���¾ɵĳ���б�
	UpdateThreatMap();

	//����������������������������
	if(me->GetReactState() == REACT_AGGRESSIVE || me->GetReactState() == REACT_AGGRESSIVE_UNIT )
	{
		Grid *grid = me->GetGrid();
		//����Χ�Ŵ�����������
		Grid::CreatureList::iterator iter;
		Grid::GridPtrVec::iterator viter;
		for(viter = grid->notice_grid.begin(); viter != grid->notice_grid.end(); ++viter)
			for(iter = (*viter)->creatures.begin(); iter != (*viter)->creatures.end(); ++iter)
				CaluThreatByDistance(*iter);
	}

	if(me->GetReactState() == REACT_AGGRESSIVE || me->GetReactState() == REACT_AGGRESSIVE_PLAYER )
	{
		//�����������������ҵ�����
		Grid *grid = me->GetGrid();
		//����Χ�Ŵ�����������
		PlayerSet::iterator iter;
		Grid::GridPtrVec::iterator viter;
		for(viter = grid->notice_grid.begin(); viter != grid->notice_grid.end(); ++viter)
			for(iter = (*viter)->players.begin(); iter != (*viter)->players.end(); ++iter)
				CaluThreatByDistance(*iter);
	}

	//���������Ŀ��
	Unit *threatTarget = GetTarget();
	if (threatTarget != me->GetTarget())
	{
		me->SetTarget(threatTarget);
		if (threatTarget)
			me->MotionMoveTarget();//�ƶ���Ŀ��
	}

	// ����Ҳ���Ŀ�� ����չ����б�
	if (threatTarget == NULL) {
		if (me->GetHealth() < me->GetMaxHealth()) {
			// ��չ�����ϵ�б�
			me->GetMap()->ClearCreatureHitHash(me->GetUIntGuid());
		}
	}
}

void ThreatManager::CaluThreatByDistance(Unit *_target)
{
	//�������Ѿ����ڳ������Ҫ�ٴ����Ӿ�����	
	if(m_targetMap.count(_target->GetUIntGuid())>0)
		return;
	float x,y;
	me->GetBornPos(x,y);

	//�������Ұ��Χ�ڣ������ڹ�����Χ��
	float distance = 0.0f;
	if( _target->isAlive() && 
		!me->IsFriendlyTo(_target) &&
		_target->GetDistance(x, y) < actionradius && 
		(distance = me->GetDistance(_target)) < visionradius&&
		_target->isCanSee())
	{
		//���γ�������Ұ
		if(me->AI_MoveInLineOfSight(_target) != 0)
		{
			m_targetMap.insert(TargetMap::value_type(_target->GetUIntGuid(), ThreatValue(0,  getThreat(distance))));
		}
	}
}

//���¾ɵĳ���б�
void ThreatManager::UpdateThreatMap()
{
	Unit *threater = 0;
	Unit *tagert = me->GetTarget();
	float x,y;
	me->GetBornPos(x,y);
	float distance =  0.0f;
	TargetMap::iterator iter = m_targetMap.begin();
	while(iter != m_targetMap.end())
	{
		threater = me->GetMap()->FindUnit(iter->first);
		if (!threater )
		{
			me->DelOwnerShip(iter->first);
			iter = m_targetMap.erase(iter);
			continue;
		}
		if(	threater->isAlive() &&
			threater->GetDistance(x,y) < actionradius)
		{						
			distance = me->GetDistance(threater);
			if(distance < visionradius)
				iter->second.second = getThreat(distance);
			else 
				iter->second.second = 0;
			++iter;
			continue;
		}
		m_targetMap.erase(iter++);
		threater->DelAttacker(me->GetUIntGuid());
		if (threater->GetTypeId() == TYPEID_PLAYER)
			me->DelOwnerShip(threater->GetUIntGuid());
		//TODO:������ܳ�����ѭ�����޸�ʱҪע��
		if(tagert == threater) me->SetTarget(NULL);
	}

	// ����б�����û��Ŀ��
	if (m_targetMap.size() == 0) {
		string prev = me->GetStr(UNIT_STRING_FIELD_DROP_OWNER_GUID);
		if (prev != "") {
			Player* player = me->GetMap()->FindPlayer(prev.c_str());
			if (player) {
				player->SetUInt32(UNIT_INT_FIELD_BOSS_OWN_FLAG, 0);
			}
			me->SetStr(UNIT_STRING_FIELD_DROP_OWNER_GUID, "");
			me->SetStr(UNIT_STRING_FIELD_DROP_OWNER_NAME, "");
		}
		creature_template *temp = creature_template_db[me->GetEntry()];
		if (temp && !temp->recure) {
			me->ModifyHealth(me->GetMaxHealth());
		}
	}
}
