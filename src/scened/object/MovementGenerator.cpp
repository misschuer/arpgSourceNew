#include <shared/map_template.h>
#include "scened.h"
#include "scened_scripts.h"
#include "Grid.h"
#include "Map.h"
#include "Creature.h"
#include "Unit.h"
#include "Player.h"
#include "MovementGenerator.h"
#include "BuffManager.h"

#define EPS 1E-4

//����Ѱ·����
const uint16 FIND_NUMBER = 20;
const int FOLLOW_CHECK_OWNER_TIMER = 1000;
const float FOLLOW_DISTANCE = 8.0f;			//�����޸������
const float MAX_FOLLOW_DISTANCE = 20.0f;	//���������������
const float TELEPORT_DISTANCE = 5.0f;		//�����޴��ؾ���
const int AUTO_CHECK_RECOVER_TIME = 1000;	//�Զ����ָ�Ѫ����ʱ��
//////////////////////////////////////////////////////////////////////////
//for MovementGenerator

void MovementGenerator::RandomPos(float& nx, float& ny, const Unit *wo, float range /* = 4.0f */)
{
    RandomPos(nx, ny, wo->GetPositionX(), wo->GetPositionY(), range);
}

void MovementGenerator::RandomPos(float& nx, float& ny, float fPosX, float fPosY, float range /* = 4.0f */)
{
    const float angle = float(rand_norm() * (M_PI * 2));
    GetNewPos(nx, ny, fPosX, fPosY, range, angle);
}

void MovementGenerator::RandomPath(Unit *unit,std::deque<float>& path,uint32 ms, float x, float y)
{
	//�ȸ����ƶ��ٶ�����ƶ�����
	float dist = float(ms)/float(unit->GetMoveSpeed());	

	float oldX,oldY;
	unit->GetPosition(oldX,oldY);

	const MapTemplate *templ = const_cast<Unit*>(unit)->GetMap()->GetMapTemp();
	ASSERT(templ);

	float nx,ny;			

	//Ϊ�˷�ֹ������ѭ��,ֻѭ�����1��5��
	for (uint32 i = 0; i < ms/200; i++ )
	{
		if (x > 0.00001 && y > 0.00001 && i == 0)
		{	
			nx = x;
			ny = y;
			float range = hypotf(nx,ny);
			//����һ��������λ,����Ҫ��
			if(range < 0.5f*g_Config.nomal_attack_distance)
				range = g_Config.nomal_attack_distance;
			else if(range > 1.5f*g_Config.nomal_attack_distance)
				range = 1.5f*g_Config.nomal_attack_distance;
			dist -= range;
		}
		else
		{	//����Ҫ�ƶ��ľ��������һ���ƶ���
			float range = float(rand_norm()*dist);	
			//����һ��������λ,����Ҫ��
			if(range < 0.5f*g_Config.nomal_attack_distance)
				range = g_Config.nomal_attack_distance;
			else if(range > 1.5f*g_Config.nomal_attack_distance)
				range = 1.5f*g_Config.nomal_attack_distance;
			dist -= range;
			RandomPos(nx,ny,oldX,oldY,range);
		}		

		//��֤һ��·��,���оͼ���
		if(!templ->IsCanRun(oldX,oldY,nx,ny,false)){
			tea_pdebug("MovementGenerator::RandomPath !IsCanRun");
			continue;
		}

		path.push_back(nx);
		path.push_back(ny);

		//������һ��Ϊ������
		oldX = nx;
		oldY = ny;

		//�����������������,ֹͣ���
		if(dist < g_Config.nomal_attack_distance)
			break;
	}

	if(path.size() == 0)
	{
		path.push_back(oldX);
		path.push_back(oldY);
	}
}

//////////////////////////////////////////////////////////////////////////
//for DISAPPEAR_MOTION_TYPE
class DisappearMovementGenerator : public MovementGenerator
{
public:
    bool Update(Unit &, const uint32 &)
    {
        return false;
    }
    MovementGeneratorType GetMovementGeneratorType()
    {
        return DISAPPEAR_MOTION_TYPE;
    }

    void Finalize(Creature &creature)
    {		
        creature.GetMap()->ToDelCreature(&creature);	//������ӵ�ͼ���Ƴ�		
    }
};

//for DEADLINE_MOTION_TYPE
class DeadlineMovementGenerator : public MovementGenerator
{
public:
	IntervalTimer m_clear_timer;

	void Initialize(Unit &,uint64 = 0 , int64 t = 0)
	{
		m_clear_timer.SetInterval(t);
		m_clear_timer.SetCurrent(0);
	}

	bool Update(Unit &, const uint32 &diff)
	{
		m_clear_timer.Update(diff);
		if (m_clear_timer.Passed()) {
			return false;
		}
		return true;
	}
	MovementGeneratorType GetMovementGeneratorType()
	{
		return DEADLINE_MOTION_TYPE;
	}

	void Finalize(Unit &unit)
	{
		if (unit.GetTypeId() == TYPEID_UNIT) {
			unit.GetMap()->ToDelCreature((Creature*)&unit);	//������ӵ�ͼ���Ƴ�
		}
	}
};

//////////////////////////////////////////////////////////////////////////
//for RandomMovementGenerator
#include "Creature.h"

//����߶�
class RandomMovementGenerator : public MovementGeneratorMedium<Creature, RandomMovementGenerator>
{
public:
    RandomMovementGenerator(): m_next_move(0){}
    void Initialize(Unit &unit, uint64 param = 0, int64 t = 0) { 
		m_next_move.Reset(urand(10000, 60000));
		unit.SetOrientation(float(rand_norm() * (M_PI * 2)));
	};
    bool Update(Creature &creature, const uint32 &diff)
    {
        //�ƶ���,����Ҫ����Ŀ���
        if(creature.IsMoving())
            return false;

        m_next_move.Update(diff);

        if(m_next_move.Passed())
        {
            if(!creature.isAlive())
                return false;

            //��ģ���еõ���뾶���������λ��
            creature_template& ct = creature.GetTemplate();
            float wander_distance = (float)ct.visionradius * g_Config.monster_random_radius_percent;

			const float angle = float(rand_norm() * (M_PI * 2));
			const float range = float(rand_norm() * wander_distance);
			const float distanceX = range * cos(angle);
			const float distanceY = range * sin(angle);

			float bornX, bornY;
			creature.GetBornPos(bornX, bornY);

			float nx = bornX + distanceX;
			float ny = bornY + distanceY;

			if (creature.GetMap()->GetMapTemp()->IsCanRun(creature.GetPositionX(),creature.GetPositionY(),nx,ny, true))
			{
				creature.MoveTo(nx, ny);
			}

            m_next_move.Reset(urand(30000, 60000));
        }

        return true;
    }
    void Finalize(Creature &) {};
    void Reset(Creature &) {};

    MovementGeneratorType GetMovementGeneratorType()
    {
        return RANDOM_MOTION_TYPE;
    }

private:
    //destination m_dest;
    TimeTrackerSmall m_next_move;	
};

////////////////////////////////////////////////////////////////////////////////////////////
//Ѱ·����Ŀ��
WayFindingMovementGenerator::WayFindingMovementGenerator():targetPoxX(0), targetPoxY(0), find_type(WAYFINDINGTYPE_NONE), recallpos(0), basenumber(1)
{
}

void WayFindingMovementGenerator::Initialize(Creature &creature, uint64 param, int64 t)
{
	if(!creature.isAlive() || !creature.isCanMove())
		return;

	//�����ƶ�λ��
	Unit *target = creature.GetTarget();
	if(!target)
		return;

	const MapTemplate *mt = creature.GetMap()->GetMapTemp();
	//float angle = creature.GetAngle(target);
	//��ʼ��Ŀ�������
	GetTargetPos(creature, target, mt);

	uint16 lastx = 0, lasty = 0, cnx = 0, cny = 0;
	
	//����·���ϰ�����ȻOK
	if(mt->IsCanRun(creature.GetPositionX(), creature.GetPositionY(), targetPoxX, targetPoxY, lastx, lasty, cnx, cny, true))
	{
// 		printf("����[%s] %f:%f �ƶ��� %f:%f", creature.GetName(), creature.GetPositionX(), creature.GetPositionY(), targetPoxX, targetPoxY);
		creature.MoveTo(targetPoxX, targetPoxY);
	}
	else
	{
		//��Ѱ·���һ�����ϰ����������Ŀǰ����һ�»��߸ɴ����û�������ϰ�����
		if((lastx == (uint16)creature.GetPositionX() && lasty == (uint16)creature.GetPositionY()) || (lastx == 0 && lasty == 0))
		{
			//tea_pdebug("��%s�������ϰ�����ʼѰ·��", creature.GetName());
			if(find_type == WAYFINDINGTYPE_NONE)
			{
				//�ɵ�Ѱ·
				if(WayPointFindPath(creature, target, cnx, cny))
					return;
				/*if(ContinuousFindPath(creature, target, cnx, cny))
					return;*/
			}
			return;
			//���Ѱ·
			if(!FindPath(creature, target, cnx, cny))
			{
				//Ѱ·ʧ�ܣ�������·�������
				basenumber = 1;
				recallpos = 0;
				return;
			}
		}
		else
		{
			basenumber = 1;
			recallpos = 0;
			creature.MoveTo(lastx, lasty);
		}

		//tea_pdebug("����[%s] %f:%f �ƶ��� %f:%f", creature.GetName(), creature.GetPositionX(), creature.GetPositionY(), targetPoxX, targetPoxY);

	}

	//creature.MoveTo(targetPoxX,targetPoxY,creature.GetAttackDistance(target));
}

void WayFindingMovementGenerator::GetTargetPos(Creature &creature, Unit *target, const MapTemplate *mt)
{
	float angle = creature.GetAngle(target);		
	uint32 cguid = creature.GetUIntGuid();

	target->removePositionInfo(cguid);

	float dis = creature.GetDistance(target);
	float attackRange = creature.GetAttackDistance(NULL);
	
	if (dis <= attackRange) {
		targetPoxX = creature.GetPositionX();
		targetPoxY = creature.GetPositionY();

		point_t p;
		p.pos_x = creature.GetPositionX();
		p.pos_y = creature.GetPositionY();
		target->positionInfo[cguid] = p;
		return;
	}

	if (!target->getNearestPositionByAngleAndAttackRange(angle, attackRange, target->GetPositionX(), target->GetPositionY(), targetPoxX, targetPoxY) || !mt->IsCanRun((uint16)targetPoxX, (uint16)targetPoxY)) {
		targetPoxX = target->GetPositionX();
		targetPoxY = target->GetPositionY();
	}
	//const float offset_angle = float(rand_norm() * (M_PI * 2));
	//GetNewPos(targetPoxX, targetPoxY, target->GetPositionX(), target->GetPositionY(), range, offset_angle);
	else {
		point_t p;
		p.pos_x = targetPoxX;
		p.pos_y = targetPoxY;
		target->positionInfo[cguid] = p;
	}
}

void WayFindingMovementGenerator::Finalize(Creature &creature)
{
	creature.StopMoving();
}

bool WayFindingMovementGenerator::Update(Creature &creature, const uint32 &diff)
{
	//����������ƶ��ƶ�
	if(!creature.isCanMove())
	{
		creature.SetTarget(NULL);
		return true;        
	}

	if(!creature.GetTarget()->isAlive())
	{
		creature.SetTarget(NULL);
		return true;
	}

	//����������ƶ�״̬������Ŀ��ķ�����ͬ���ô���Ŀ���ƶ�����������Ŀ��
	float creatureX = creature.GetTarget()->GetPositionX();
	float creatureY = creature.GetTarget()->GetPositionY();

	if(targetPoxX != creatureX
		|| targetPoxY != creatureY
		|| !creature.IsMoving()/// toPoxX == uint16(creature.GetPositionX()) && toPoxY == uint16(creature.GetPositionY()))
		|| creature.GetIsBlowFly())
	{
		if(targetPoxX != creatureX || targetPoxY != creatureY)
		{
			basenumber = 1;
			recallpos = 0;
			find_type = WAYFINDINGTYPE_NONE;
		}

		//�����С�������ϰ����棬�����ٶ���һ������´���Ѱ·
		if(creature.IsMoving() 
			&& !creature.GetMap()->GetMapTemp()->IsCanRun((uint16)creature.GetPositionX(), (uint16)creature.GetPositionY()))
			return true;
		creature.StopMoving();
		Initialize(creature);
		return true;
	}
	return true;
}

MovementGeneratorType WayFindingMovementGenerator::GetMovementGeneratorType()
{
	return WAYFINDING_MOTION_TYPE;
}

bool WayFindingMovementGenerator::WayPointFindPath(Creature &creature, Unit *target, uint16 cnx, uint16 cny)
{
	if(creature.GetTarget() && creature.GetDistance(creature.GetTarget()) > 50)
	{
		//tea_pdebug("�������50������Ѱ·");
		return false;
	}
	uint16 lastx = 0, lasty = 0;
	uint16 px = uint16(creature.GetPositionX()), py = uint16(creature.GetPositionY());
	const MapTemplate *mt = creature.GetMap()->GetMapTemp();
	uint32 point = px + mt->GetMapBaseInfo().width * py;
	uint32 point2 = 0;
	uint32 point_target;
	int me_size;
	int index_creature = -1, index_target = -1;
	const mt_point_in_line *me = mt->GetMonsterLineEach(point);
	if(me == NULL)
	{
		int8 index = MapTemplate::FindAroundIndex(cnx, cny, px, py);
		point2 = px + MapTemplate::around[(index - 1) % 8][0] + mt->GetMapBaseInfo().width * (py + MapTemplate::around[(index - 1) % 8][1]);
		me = mt->GetMonsterLineEach(point2);
		if(me == NULL)
		{
			point2 = px + MapTemplate::around[(index + 1) % 8][0] + mt->GetMapBaseInfo().width * (py + MapTemplate::around[(index + 1) % 8][1]);
			me = mt->GetMonsterLineEach(point2);
			if(me == NULL)
				return false;
		}
	}

	mt->IsCanRun(targetPoxX, targetPoxY, creature.GetPositionX(), creature.GetPositionY(), lastx, lasty, cnx, cny);
	int8 index = MapTemplate::FindAroundIndex(cnx, cny, lastx == 0 ? uint16(targetPoxX) : lastx, lasty == 0 ? uint16(targetPoxY) : lasty);
	if(index == -1)
	{
		//tea_pdebug("��������ҽ����ϰ��ˡ�");
		return false;
	}
	if(index % 2 == 0)
	{
		index = (index + 9) % 8;
		uint16 nlx = lastx + MapTemplate::around[index][0];
		uint16 nly = lasty + MapTemplate::around[index][1];
		if(mt->IsCanRun(nlx,nly))
		{
			lastx = nlx;
			lasty = nly;
		}
	}
	point_target = lastx + mt->GetMapBaseInfo().width * lasty;
	const mt_point_in_line *me_t = mt->GetMonsterLineEach(point_target);
	//����ͬһ���ɵ�
	if(me_t == NULL || me_t->each != me->each)
	{
		tea_pdebug("����ͬһ���ɵ�����%d,%d��%d,%d", py, px, (uint16)targetPoxX, (uint16)targetPoxY);
		return false;
	}

	//tea_pdebug("����ɵ�");
	me_size = me->each->point_each.size();
	index_target = me_t->index;
	index_creature = me->index;

	if(index_creature == -1 || index_target == -1 || index_creature == index_target)
	{
		tea_perror("�ɵ���û���á���%d,%d��%d,%d", py, px, (uint16)targetPoxX, (uint16)targetPoxY);
		return false;
	}

	//1˳��2����
	uint8 direction = index_target > index_creature ? 1 : 2;
	if(me->each->is_join)
	{
		if(direction == 1)
			direction = index_target - index_creature < index_creature + me_size - index_target ? 1 : 2;
		else
			direction = index_creature - index_target> index_target + me_size - index_creature ? 1 : 2;
	}

	int max_i = (direction == 1 ? index_target + me_size - index_creature : index_creature + me_size - index_target) % me_size;		
	int i = point2 == 0 ? 0 : 1;
	if(point2 != 0)
	{
		find_link[0] = float(point2 % mt->GetMapBaseInfo().width);
		find_link[1] = float(point2 / mt->GetMapBaseInfo().width);
		max_i++;
	}
	int max_size = (max_i + 1) * 2;
	uint32 array_len = 0;
	index_creature += me_size;
	if(find_link.size() < uint32(max_size))
		find_link.resize(uint32(max_size));
	do
	{
		if(direction == 1)
			index_creature++;
		else
			index_creature--;
		uint32 index = index_creature % me_size;
		mt_monsterline_each *each = NULL;
		list<mt_point*>::iterator list_it = me->each->point_each.begin();
		for (uint32 t_i = 0; t_i < index; ++list_it, t_i++);			
		find_link[i * 2] = (*list_it)->pos_x;
		find_link[i * 2 + 1] = (*list_it)->pos_y;
		array_len += 2;
		if(mt->IsCanRun(find_link[i * 2], find_link[i * 2 + 1], targetPoxX, targetPoxY))
		{
			i++;
			find_link[i * 2] = targetPoxX;
			find_link[i * 2 + 1] = targetPoxY;
			array_len += 2;
			break;
		}
		i++;
		if(i > 50)
		{
			//tea_pdebug("Ѱ·����50����������");
			return false;
		}
	}
	while(i < max_i);

	for (uint32 fi = 0; fi < array_len; fi+=2)
	{
		if(fi > 2)
		{
			if(!creature.GetMap()->GetMapTemp()->IsCanRun(find_link[fi-2],find_link[fi-1],find_link[fi],find_link[fi+1]))
			{
				tea_perror("way finding err map:%u line no:%u, creature X %u, creature Y %u to target X %u,target Y %u",
					creature.GetMapId(), me->index, px, py, (uint16)targetPoxX, (uint16)targetPoxY); 
#ifdef WIN32
ASSERT(false);
#endif //windows����Ĳ���
				return false;
			}
		}
	}

	creature.MoveTo(array_len, &find_link[0]);

	find_type = WAYFINDINGTYPE_WAYPOINT;
	return true;
}
	
//����Ѱ·
bool WayFindingMovementGenerator::ContinuousFindPath(Creature &creature, Unit *target, uint16 cnx, uint16 cny)
{
	uint16 find_number = 20;
	uint16 c_r_x, c_r_y, c_l_x, c_l_y;
	uint16 last_l_x = cnx, last_l_y = cny, last_r_x = cnx, last_r_y = cny;
	int find_index = 0;
	int left_number = 0, right_number = 0;
	bool left = false, right = false;
	int i;

	c_r_x = (uint16)creature.GetPositionX();
	c_r_y = (uint16)creature.GetPositionY();
	c_l_x = c_r_x;
	c_l_y = c_r_y;
	for(; find_index < find_number; find_index++)
	{
		//̽Ѱ��һ������һ������ʼѰ·
		int8 p_l = MapTemplate::FindAroundIndex(last_l_x, last_l_y, c_l_x, c_l_y);
		int8 p_r = MapTemplate::FindAroundIndex(last_r_x, last_r_y, c_r_x, c_r_y);
		if(find_index != 0)
		{
			//������һ�³�����ΪFindAroundIndex�Ƿ�������
			p_l -= 2;
			p_r += 2;
		}
		bool left_find = false, right_find = false;

		//������һ��
		last_r_x = c_r_x;
		last_r_y = c_r_y;
		last_l_x = c_l_x;
		last_l_y = c_l_y;

		for(i = 1; i < 8; i++)
		{
			p_r ++;
			//����ͨ��
			if(!right_find && TestGo(target, c_r_x, c_r_y, p_r, right))
			{
				find_link[find_index * 2] = c_r_x;
				find_link[find_index * 2 + 1] = c_r_y;
				if(right) break; //Ѱ��ֱ���·��
				right_find = true;//����Ѱ·�ɹ�������ֻ������һ��
			}
			p_l --;
			//����ͨ��
			if(!left_find && TestGo(target, c_l_x, c_l_y, p_l, left))
			{
				find_link[(find_index + find_number) * 2] = c_l_x;
				find_link[(find_index + find_number) * 2 + 1] = c_l_y;
				if(left) break;//Ѱ��ֱ���·��
				left_find = true;//����Ѱ·�ɹ�������ֻ������һ��
			}
			if(right_find && left_find)
				break;//���Ҷ�Ѱ����
			if(i == 7)
			{
				//tea_perror("Ѱ·�����⣬һȦ��û���ڣ������Ǵ��,���߹�������ϰ���Ȼ������Ѱ·��");
				//����
				return false;
			}
		}
		if (right || left)
		{
			if(right)
				creature.MoveTo((find_index + 1) * 2, &find_link[0]);
			else
				creature.MoveTo((find_index + 1) * 2, &find_link[find_number * 2]);
			find_type = WAYFINDINGTYPE_CONTINUOUS;
			//tea_pdebug("����Ѱ·OK");
			return true;
		}
	}
	return false;
}

//����ͨ��
bool WayFindingMovementGenerator::TestGo(Unit *target, uint16 &poxX, uint16 &poxY, uint16 p, bool &complete)
{
	complete = false;
	if(target->GetMap()->GetMapTemp()->IsCanRun(poxX, poxY, target->GetPositionX(), target->GetPositionY()))
	{
		poxX = (uint16)target->GetPositionX();
		poxY = (uint16)target->GetPositionY();
		complete = true;
		return true;
	}

	uint16 index = p & 7;
	uint16 tx, ty;
	tx = uint16(poxX + MapTemplate::around[index][0] * basenumber);
	ty = uint16(poxY + MapTemplate::around[index][1] * basenumber);

	if(target->GetMap()->GetMapTemp()->IsCanRun(poxX, poxY, tx, ty, true))
	{
		poxX = tx;
		poxY = ty;
		return true;
	}

	return false;
}

bool WayFindingMovementGenerator::FindPath(Creature &creature, Unit *target, uint16 cnx, uint16 cny)
{
	int i = 1;

	//Ŀ����ͬ����Ѱ·�Ѿ������ĴΣ���ʼ�Ƚ��Ƿ��߻�ͷ·
	if(recallpos > 3)
	{
		if(recall[0][0] == recall[2][0] && recall[0][1] == recall[2][1] && recall[1][0] == recall[3][0] && recall[1][1] == recall[3][1])
		{
			//Ѿ��ͷ�ˣ�����������Χ
			recallpos = 0;
			basenumber ++;
		}
		else
		{
			//Ѿľ�л�ͷ��OK�������һ��Ѱ·
			recallpos = 0;
			basenumber = 1;
		}
	}

	//�ѹ���Ŀǰ�����ȱ�������
	uint16 toPoxX = uint16(creature.GetPositionX());
	uint16 toPoxY = uint16(creature.GetPositionY());
	int8 around_index = MapTemplate::FindAroundIndex(cnx, cny, toPoxX, toPoxY);

	for(; i < 8; i++)
	{
		//���ֱ����������ֱ���ɸ�����
		if((i & 1) == 1)
		{
			i = 0 - i;
		}
		//˳���ǣ���ǰ����ǰ�����ң�����Һ󣬺�
		around_index += i;
		i = abs(i);
		//����ͨ��
		if(TestGo(creature, target, around_index, toPoxX, toPoxY))
		{
			//�����߹���·���������±�+1
			recall[recallpos % 4][0] = toPoxX;
			recall[recallpos % 4][1] = toPoxY;
			recallpos++;
			find_type = WAYFINDINGTYPE_POINT_BY_POINT;
			creature.MoveTo(toPoxX, toPoxY);
			return true;
		}
	}

	return false;
}

//����ͨ��
bool WayFindingMovementGenerator::TestGo(Creature &creature, Unit *target, uint16 p, uint16 &toPoxX, uint16 &toPoxY)
{
	uint16 index = p & 7;
	uint16 tx, ty;
	tx = uint16(toPoxX + MapTemplate::around[index][0] * basenumber);
	ty = uint16(toPoxY + MapTemplate::around[index][1] * basenumber);

	if(target->GetMap()->GetMapTemp()->IsCanRun(toPoxX, toPoxY, tx, ty, true))
	{
		toPoxX = tx;
		toPoxY = ty;
		return true;
	}

	return false;
}

//Ѱ·׷ɱ
WayFindingAndAttackMovementGenerator::WayFindingAndAttackMovementGenerator(): 
	spell(NULL), m_is_attack_target(true), m_target_dis(4)
{
	//m_recover_timer.SetCurrent(0);
	//m_recover_timer.SetInterval(AUTO_CHECK_RECOVER_TIME);
}

void WayFindingAndAttackMovementGenerator::Initialize(Creature & creature, uint64 param, int64 t)
{
	WayFindingMovementGenerator::Initialize(creature, param,t);
}


bool WayFindingAndAttackMovementGenerator::Update(Creature &creature, const uint32 &diff)
{	
	if(creature.GetTarget() == NULL)
		return false;
	if(AttackTarge(creature, diff))
		return true;
	
	return WayFindingMovementGenerator::Update(creature,diff);
}

void WayFindingAndAttackMovementGenerator::RandSpell(Creature &creature, float dis)
{
	//����ǰû����Ҫ�ͷŵļ��ܣ���ʼ�漼��
	if(spell == NULL && creature.HasSpell())
	{
		spell = creature.RandSpell(dis);
	}
}

bool WayFindingAndAttackMovementGenerator::AttackTarge(Creature &creature, const uint32 &diff)
{
	if(m_is_attack_target)
	{
		//���ڼ����������߳���ʩ��
		if(creature.isCasing() || creature.isSpellProcess())
			return true;

		if (ms_time() < creature.GetNextSpellCD()) {
			return true;
		}

		float dis = creature.GetDistance(creature.GetTarget());
		RandSpell(creature, dis);
		
		//����ڹ����������ڣ�ֱ�ӹ����ͺò����ƶ�;
		if(spell && (spell->target_type == 0 || dis <= spell->spell_distance || fabs(dis - spell->spell_distance) <= 1E-1))
		{
			if(creature.IsMoving()) {
				//return true;
				creature.StopMoving(true);
			}

			if(creature.isCasing() &&
				(targetPoxX != creature.GetTarget()->GetPositionX()
				|| targetPoxY != creature.GetTarget()->GetPositionY()))
			{
				int ori1 = int(creature.GetOrientation() * 100 / 25);
				float ang = creature.GetAngle(creature.GetTarget());
				int ori2 = int(ang * 100 / 25);
				if(ori1 != ori2)
				{
					creature.SpellStop();
					return true;
				}
			}

			const float angle = creature.GetAngle(creature.GetTarget()->GetPositionX(), creature.GetTarget()->GetPositionY());

			if(angle != creature.GetOrientation())
			{
				//creature.MoveTurnAround(angle);
				creature.SetOrientation(angle);
			}

			//creature.MoveStop();
			if(!creature.isCasing() && !creature.isSpellProcess())
				Attack(creature, diff);
			
			return true;
		}
	
		if(IsInCastRange(creature, dis))
		{
			if(creature.IsMoving())
				creature.StopMoving(true);
			return true;
		}		
	}

	return false;
}

bool WayFindingAndAttackMovementGenerator::lessThan(float dis, float dis2) {
	return  dis < dis2 || abs(dis - dis2) <= EPS;
}

//�Ƿ��Ѿ��ڹ���������
bool WayFindingAndAttackMovementGenerator::IsInCastRange(Creature &creature, float dis)
{
	return ((spell && lessThan(dis, 0.0f + spell->spell_distance)) || lessThan(dis,0.0f+m_target_dis) || lessThan(dis, creature.GetAttackDistance(NULL)));
}

//��������
void WayFindingAndAttackMovementGenerator::Attack(Creature &creature, const uint32 &diff)
{
	if(!creature.isCasing() && !creature.isSpellProcess() && !creature.IsCantCast())
	{
		if(creature.GetTarget() && creature.GetTarget()->isAlive() && creature.GetBuffManager()->HasBuff(BUFF_INVINCIBLE) == 0) {
			creature.SetCurSpellLevel(spell->spell_level);
			creature.CastSpell(spell->spell_id, creature.GetTarget()->GetPositionX(), creature.GetTarget()->GetPositionY());
		}
		spell = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//ľżʽ�ĳ����ƶ���ʽ��������Ҳ����������ѡ���Ŀ��
vector<float> WayFindingMovementGenerator::find_link;
MercenaryMovementGenerator::MercenaryMovementGenerator() : m_canAttack(true), m_canRandomMove(false), follow_type(FOLLOW_MOVE_TYPE_FOREVER), m_revert_active_grid(false), m_owner(0), m_next_random_move(10000), m_is_random_move(false), m_timer(0)
{

}
	
void MercenaryMovementGenerator::Initialize(Creature & creature, uint64 param, int64 t)
{
	if(param == 0)
	{
		WayFindingMovementGenerator::Initialize(creature);
		return;
	}
		
	if(t < 0)
	{
		creature.SetClearTimer(abs(t));
		follow_type = FOLLOW_MOVE_TYPE_LIMIT_CLEAR;
	}
	else if(t > 0)
	{
		m_timer.SetInterval(t);
		m_timer.SetCurrent(0);
		follow_type = FOLLOW_MOVE_TYPE_LIMIT;
	}

	Unit *unit = (Unit*)param;
	m_owner = unit->GetUIntGuid();

	if(unit && unit->GetTypeId() == TYPEID_PLAYER) 		
	{
		creature.SetCanActiveGrid(true);
		m_revert_active_grid = true;
	}
}

bool MercenaryMovementGenerator::Update(Creature &creature, const uint32 &diff)
{
	//����Ѿ�����,���ø���
	if(!creature.isAlive())
		return false;
		
	//������õ�ʱ��Ϊ0��һֱ����
	if(m_timer.GetInterval() != 0 )
	{
		m_timer.Update(diff);
		//�����ʱ��,��ôȡ������
		if (m_timer.Passed())
		{
			creature.SetTarget(NULL);		//��Ȼ��޹����޷�ָ����ȥ����
			if(creature.IsMoving())
				creature.StopMoving(true);
			return false;
		}
	}

	//�ҵ�Ҫ����
	Unit *owner = creature.GetMap()->FindUnit(m_owner);
	if(!owner)
		return false;

	//���Թ���
	if(m_canAttack)
	{
		Unit *target = GetAttackTarget(creature, owner);
		if(target)
		{
			//׷ɱ������
			creature.SetTarget(target);
			m_is_attack_target = true;
			return WayFindingAndAttackMovementGenerator::Update(creature, diff);
		}
	}

	//���������Ҳ���Ҫ������Ŀ�꣬���������
	float nx, ny;
	float range = creature.GetDistance(owner);
	float angle = creature.GetAngle(owner);

	float followdis = FOLLOW_DISTANCE;
	if (creature.GetFollowDis() != 0)
	{
		followdis = creature.GetFollowDis();
	}
			
	//������벻�Ǻ�Զ���Ȱ�������        ���Ҳ����ϰ������档
	if(range < followdis && creature.GetMap()->GetMapTemp()->IsCanRun((uint16)creature.GetPositionX(), (uint16)creature.GetPositionY()))
	{
		if(creature.IsMoving() && !m_is_random_move)
			creature.StopMoving(true);

		//����������Ų�������ôż��ҲҪ��һ�£���Ȼ̫����
		if(m_canRandomMove && !owner->IsMoving() && !creature.IsMoving())
		{
			m_next_random_move.Update(diff);

			if(m_next_random_move.Passed())
			{
				RandomPos(nx, ny, &creature);
				if(creature.GetMap()->GetMapTemp()->IsCanRun(creature.GetPositionX(), creature.GetPositionY(), nx, ny))
				{
					creature.MoveTo(nx, ny);
					m_is_random_move = true;
				}
				m_next_random_move.Reset(urand(3000, 8000));
			}
		}
		return true;
	}
	else if(range > MAX_FOLLOW_DISTANCE)
	{
		//ֱ�Ӵ���
		RandomPos(nx, ny, owner, TELEPORT_DISTANCE);
		creature.Relocate(nx, ny, angle);
		creature.StopMoving();
		m_is_random_move = false;
		return true;
	}
	m_is_random_move = false;
	creature.SetTarget(owner);
	m_is_attack_target = false;
	return WayFindingAndAttackMovementGenerator::Update(creature, diff);
}

Unit *MercenaryMovementGenerator::GetAttackTarget(Creature &creature,Unit *owner)
{
	if(!creature.GetMap() || !owner->GetLastVictim())
		return NULL;

	Unit *target = NULL;
	if (owner->GetMap())
		target = owner->GetMap()->FindUnit(owner->GetLastVictim());
	
	//��������ʧ
	if(!target)
	{
		owner->SetLastVictim(0);
		return NULL;
	}
	//����������
	if(!target->isAlive())
	{
		owner->SetLastVictim(0);
		return NULL;
	}
	return target;
}

void MercenaryMovementGenerator::Finalize(Creature &creature)
{
	//���� �Ƿ񼤻�Grid ״̬
	if(m_revert_active_grid)
		creature.SetCanActiveGrid(false);
}

//////////////////////////////////////////////////////////////////////////
//��·���߶�
void WayPointMovementGenerator::Initialize(Creature &creature, uint64 param, int64 t)
{
    if(!creature.isAlive())
        return;

    //����·��
    wayid = static_cast<uint32>(param);
	const vector<mt_monsterline_t>& mt_path = creature.GetMap()->GetMapTemp()->m_monsterlines;
	if(mt_path.size() <= wayid || mt_path[wayid].path.empty())
	{
		tea_pwarn("path err");
	}
	else
	{
		if(t == 0)
			path = creature.GetMap()->GetMapTemp()->m_monsterlines[wayid].path;
		else
		{
			int size = mt_path[wayid].path.size();
			for (int i = mt_path[wayid].path.size() - 1; i >= 0; i --)
			{
				path.push_back(mt_path[wayid].path[i]);
			}
		}
	}
	point_index = 0;

    //��ʼ����׼��
    /*
    mt_point m_target = path[point_index];
    point_index++;

    creature.MoveTo(float(m_target.pos_x), float(m_target.pos_y));*/

	if(!creature.CanActiveGrid())
	{
		creature.SetCanActiveGrid(true);
		m_revert_active_grid = true;
	}
}

void WayPointMovementGenerator::Reset(Creature &creature)
{
    Initialize(creature);
}
void WayPointMovementGenerator::Finalize(Creature &creature)
{
	if(m_revert_active_grid)
		creature.SetCanActiveGrid(false);
};
bool WayPointMovementGenerator::Update(Creature &creature, const uint32 &)
{
	if(path.size() == 0)
		return false;
    //����������ƶ��ƶ�
    if(!creature.isCanMove())
    {
        if(creature.IsMoving())
            creature.StopMoving(true);

        return true;
    }

    //����Ѿ�����Ŀ��
    if(!creature.IsMoving())
    {
		if(point_index !=0 && creature.GetDistance(path[point_index-1].pos_x,path[point_index-1].pos_y) > 1.0f)
		{
			creature.MoveTo(float(path[point_index-1].pos_x), float(path[point_index-1].pos_y));
		}
		else if(point_index < path.size())
		{
			creature.MoveTo(float(path[point_index].pos_x), float(path[point_index].pos_y));
			point_index ++;
		}
		else//else if (point_index >= (path.size() + 1) >> 1)
		{
			//�޸ĳ�����λ�ã�ʡ���߻�ȥ
			creature.SetBornPos(path[point_index - 1].pos_x, path[point_index - 1].pos_y);
			//����һ������֪ͨ,���������ﴥ��
			char name[50];
			memset(name, 0, 50);
			//sprintf(name, "%u", wayid);
			OnNotifyArea(creature.GetMap(), &creature, name, path[point_index - 1].pos_x, path[point_index - 1].pos_y);
			return false;		//����·��,�ص���
		}			
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//�����߶�
class HomeMovementGenerator : public MovementGeneratorMedium<Creature, HomeMovementGenerator>
{
public:
    HomeMovementGenerator() {}
    void Initialize(Creature &creature, uint64 param = 0, int64 t = 0)
    {
        ASSERT(creature.isAlive())
    }
    void Reset(Creature &) {};
    bool Update(Creature &creature, const uint32 &)
    {
        if(!creature.isAlive())
            return false;

        //����������ƶ��ƶ�
        if(!creature.isCanMove())
        {
            if(creature.IsMoving())
                creature.StopMoving();

            return true;
        }

        //����Ѿ�ͣ������
        if(creature.IsMoving())
        {
            return true;
        }
        else
        {
            float x, y;
            creature.GetBornPos(x, y);

            if(x != creature.GetPositionX() || y != creature.GetPositionY())
            {
//                tea_pwarn("���ó��ֵ����,δ�ص��Ҿ�ͣ������!");
                creature.MoveTo(x, y);
                return true;
            }
        }

       return false;
    }
    void Finalize(Creature &) {};

    MovementGeneratorType GetMovementGeneratorType()
    {
        return HOME_MOTION_TYPE;
    }
};

//////////////////////////////////////////////////////////////////////////
//for FollowInlineMovementGenerator

//�����ĸ����߶�
class FollowInlineMovementGenerator : public MercenaryMovementGenerator
{
public:
	FollowInlineMovementGenerator()
	{
		m_canAttack = false;
		m_canRandomMove = false;
	}
};					

//////////////////////////////////////////////////////////////////////////
//for FollowMovementGenerator

//�����߶�
class FollowMovementGenerator :public MercenaryMovementGenerator
{
public:
	FollowMovementGenerator()
	{
		m_canAttack = false;
		m_canRandomMove = true;
	}
};



////////////////////////////////////////////////////////////////////////////////////////////
//Ѱ·����ָ���ص�
vector<float> WayFindingDstMovementGenerator::find_link;
WayFindingDstMovementGenerator::WayFindingDstMovementGenerator():targetPoxX(0), targetPoxY(0), find_type(WAYFINDINGTYPE_NONE), recallpos(0), basenumber(1)
{
}

void WayFindingDstMovementGenerator::Initialize(Creature &creature, uint64 param, int64 t)
{
	if(!creature.isAlive() || !creature.isCanMove())
		return;
	targetPoxX = (float)param;
	targetPoxY = (float)t;
}


void WayFindingDstMovementGenerator::Finalize(Creature &creature)
{
	creature.StopMoving();
}
bool WayFindingDstMovementGenerator::Update(Creature &creature, const uint32 &diff)
{
	if(!creature.isAlive() || !creature.isCanMove())
		return false;
	if(targetPoxX != creature.GetPositionX()
		|| targetPoxY != creature.GetPositionY()
		|| !creature.IsMoving())
	{

		return FindPath(creature);
	}
	return false;
}

MovementGeneratorType WayFindingDstMovementGenerator::GetMovementGeneratorType()
{
	return WAYFINDDST_MOTION_TYPE;
}

bool WayFindingDstMovementGenerator::FindPath(Creature &creature)
{
	if(!creature.isAlive() || !creature.isCanMove())
		return false;

	const MapTemplate *mt = creature.GetMap()->GetMapTemp();
	//float angle = creature.GetAngle(target);

	uint16 lastx = 0, lasty = 0, cnx = 0, cny = 0;

	//����·���ϰ�����ȻOK
	if(mt->IsCanRun(creature.GetPositionX(), creature.GetPositionY(), targetPoxX, targetPoxY, lastx, lasty, cnx, cny, true))
	{
		//tea_pdebug("����[%s] %f:%f �ƶ��� %f:%f", creature.GetName(), creature.GetPositionX(), creature.GetPositionY(), targetPoxX, targetPoxY);
		creature.MoveTo(targetPoxX, targetPoxY);
	}
	else
	{
		//��Ѱ·���һ�����ϰ����������Ŀǰ����һ�»��߸ɴ����û�������ϰ�����
		if((lastx == (uint16)creature.GetPositionX() && lasty == (uint16)creature.GetPositionY()) || (lastx == 0 && lasty == 0))
		{
			//tea_pdebug("��%s�������ϰ�����ʼѰ·��", creature.GetName());
			if(find_type == WAYFINDINGTYPE_NONE)
			{
				//�ɵ�Ѱ·
				if(WayPointFindPath(creature, cnx, cny))
					return true;
				/*if(ContinuousFindPath(creature, target, cnx, cny))
					return;*/
			}
		}
		else
		{
			basenumber = 1;
			recallpos = 0;
			creature.MoveTo(lastx, lasty);
		}

		//tea_pdebug("����[%s] %f:%f �ƶ��� %f:%f", creature.GetName(), creature.GetPositionX(), creature.GetPositionY(), targetPoxX, targetPoxY);

	}

	//creature.MoveTo(targetPoxX,targetPoxY,creature.GetAttackDistance(target));
	return true;
}

bool WayFindingDstMovementGenerator::WayPointFindPath(Creature &creature, uint16 cnx, uint16 cny)
{

	uint16 lastx = 0, lasty = 0;
	uint16 px = uint16(creature.GetPositionX()), py = uint16(creature.GetPositionY());
	const MapTemplate *mt = creature.GetMap()->GetMapTemp();
	uint32 point = px + mt->GetMapBaseInfo().width * py;
	uint32 point2 = 0;
	uint32 point_target;
	int me_size;
	int index_creature = -1, index_target = -1;
	const mt_point_in_line *me = mt->GetMonsterLineEach(point);
	if(me == NULL)
	{
		int8 index = MapTemplate::FindAroundIndex(cnx, cny, px, py);
		point2 = px + MapTemplate::around[(index - 1) % 8][0] + mt->GetMapBaseInfo().width * (py + MapTemplate::around[(index - 1) % 8][1]);
		me = mt->GetMonsterLineEach(point2);
		if(me == NULL)
		{
			point2 = px + MapTemplate::around[(index + 1) % 8][0] + mt->GetMapBaseInfo().width * (py + MapTemplate::around[(index + 1) % 8][1]);
			me = mt->GetMonsterLineEach(point2);
			if(me == NULL)
				return false;
		}
	}

	mt->IsCanRun(targetPoxX, targetPoxY, creature.GetPositionX(), creature.GetPositionY(), lastx, lasty, cnx, cny);
	int8 index = MapTemplate::FindAroundIndex(cnx, cny, lastx == 0 ? uint16(targetPoxX) : lastx, lasty == 0 ? uint16(targetPoxY) : lasty);
	if(index == -1)
	{
		//tea_pdebug("��������ҽ����ϰ��ˡ�");
		return false;
	}
	if(index % 2 == 0)
	{
		index = (index + 9) % 8;
		uint16 nlx = lastx + MapTemplate::around[index][0];
		uint16 nly = lasty + MapTemplate::around[index][1];
		if(mt->IsCanRun(nlx,nly))
		{
			lastx = nlx;
			lasty = nly;
		}
	}
	point_target = lastx + mt->GetMapBaseInfo().width * lasty;
	const mt_point_in_line *me_t = mt->GetMonsterLineEach(point_target);
	//����ͬһ���ɵ�
	if(me_t == NULL || me_t->each != me->each)
	{
		tea_pdebug("����ͬһ���ɵ�����%d,%d��%d,%d", py, px, (uint16)targetPoxX, (uint16)targetPoxY);
		return false;
	}

	//tea_pdebug("����ɵ�");
	me_size = me->each->point_each.size();
	index_target = me_t->index;
	index_creature = me->index;

	if(index_creature == -1 || index_target == -1 || index_creature == index_target)
	{
		tea_perror("�ɵ���û���á���%d,%d��%d,%d", py, px, (uint16)targetPoxX, (uint16)targetPoxY);
		return false;
	}

	//1˳��2����
	uint8 direction = index_target > index_creature ? 1 : 2;
	if(me->each->is_join)
	{
		if(direction == 1)
			direction = index_target - index_creature < index_creature + me_size - index_target ? 1 : 2;
		else
			direction = index_creature - index_target> index_target + me_size - index_creature ? 1 : 2;
	}

	int max_i = (direction == 1 ? index_target + me_size - index_creature : index_creature + me_size - index_target) % me_size;		
	int i = point2 == 0 ? 0 : 1;
	if(point2 != 0)
	{
		find_link[0] = float(point2 % mt->GetMapBaseInfo().width);
		find_link[1] = float(point2 / mt->GetMapBaseInfo().width);
		max_i++;
	}
	int max_size = (max_i + 1) * 2;
	uint32 array_len = 0;
	index_creature += me_size;
	if(find_link.size() < uint32(max_size))
		find_link.resize(uint32(max_size));
	do
	{
		if(direction == 1)
			index_creature++;
		else
			index_creature--;
		uint32 index = index_creature % me_size;
		mt_monsterline_each *each = NULL;
		list<mt_point*>::iterator list_it = me->each->point_each.begin();
		for (uint32 t_i = 0; t_i < index; ++list_it, t_i++);			
		find_link[i * 2] = (*list_it)->pos_x;
		find_link[i * 2 + 1] = (*list_it)->pos_y;
		array_len += 2;
		if(mt->IsCanRun(find_link[i * 2], find_link[i * 2 + 1], targetPoxX, targetPoxY))
		{
			i++;
			find_link[i * 2] = targetPoxX;
			find_link[i * 2 + 1] = targetPoxY;
			array_len += 2;
			break;
		}
		i++;
		if(i > 50)
		{
			//tea_pdebug("Ѱ·����50����������");
			return false;
		}
	}
	while(i < max_i);

	for (uint32 fi = 0; fi < array_len; fi+=2)
	{
		if(fi > 2)
		{
			if(!creature.GetMap()->GetMapTemp()->IsCanRun(find_link[fi-2],find_link[fi-1],find_link[fi],find_link[fi+1]))
			{
				tea_perror("way finding err map:%u line no:%u, creature X %u, creature Y %u to target X %u,target Y %u",
					creature.GetMapId(), me->index, px, py, (uint16)targetPoxX, (uint16)targetPoxY); 
#ifdef WIN32
ASSERT(false);
#endif //windows����Ĳ���
				return false;
			}
		}
	}

	creature.MoveTo(array_len, &find_link[0]);

	find_type = WAYFINDINGTYPE_WAYPOINT;
	return true;
}
	
//����Ѱ·
bool WayFindingDstMovementGenerator::ContinuousFindPath(Creature &creature, uint16 cnx, uint16 cny)
{
	uint16 find_number = 20;
	uint16 c_r_x, c_r_y, c_l_x, c_l_y;
	uint16 last_l_x = cnx, last_l_y = cny, last_r_x = cnx, last_r_y = cny;
	int find_index = 0;
	int left_number = 0, right_number = 0;
	bool left = false, right = false;
	int i;

	c_r_x = (uint16)creature.GetPositionX();
	c_r_y = (uint16)creature.GetPositionY();
	c_l_x = c_r_x;
	c_l_y = c_r_y;
	for(; find_index < find_number; find_index++)
	{
		//̽Ѱ��һ������һ������ʼѰ·
		int8 p_l = MapTemplate::FindAroundIndex(last_l_x, last_l_y, c_l_x, c_l_y);
		int8 p_r = MapTemplate::FindAroundIndex(last_r_x, last_r_y, c_r_x, c_r_y);
		if(find_index != 0)
		{
			//������һ�³�����ΪFindAroundIndex�Ƿ�������
			p_l -= 2;
			p_r += 2;
		}
		bool left_find = false, right_find = false;

		//������һ��
		last_r_x = c_r_x;
		last_r_y = c_r_y;
		last_l_x = c_l_x;
		last_l_y = c_l_y;

		for(i = 1; i < 8; i++)
		{
			p_r ++;
			//����ͨ��
			if(!right_find && TestGo(creature, c_r_x, c_r_y, p_r, right))
			{
				find_link[find_index * 2] = c_r_x;
				find_link[find_index * 2 + 1] = c_r_y;
				if(right) break; //Ѱ��ֱ���·��
				right_find = true;//����Ѱ·�ɹ�������ֻ������һ��
			}
			p_l --;
			//����ͨ��
			if(!left_find && TestGo(creature, c_l_x, c_l_y, p_l, left))
			{
				find_link[(find_index + find_number) * 2] = c_l_x;
				find_link[(find_index + find_number) * 2 + 1] = c_l_y;
				if(left) break;//Ѱ��ֱ���·��
				left_find = true;//����Ѱ·�ɹ�������ֻ������һ��
			}
			if(right_find && left_find)
				break;//���Ҷ�Ѱ����
			if(i == 7)
			{
				//tea_perror("Ѱ·�����⣬һȦ��û���ڣ������Ǵ��,���߹�������ϰ���Ȼ������Ѱ·��");
				//����
				return false;
			}
		}
		if (right || left)
		{
			if(right)
				creature.MoveTo((find_index + 1) * 2, &find_link[0]);
			else
				creature.MoveTo((find_index + 1) * 2, &find_link[find_number * 2]);
			find_type = WAYFINDINGTYPE_CONTINUOUS;
			//tea_pdebug("����Ѱ·OK");
			return true;
		}
	}
	return false;
}

//����ͨ��
bool WayFindingDstMovementGenerator::TestGo(Creature &creature, uint16 &poxX, uint16 &poxY, uint16 p, bool &complete)
{
	complete = false;
	if(creature.GetMap()->GetMapTemp()->IsCanRun(poxX, poxY, targetPoxX, targetPoxY))
	{
		poxX = (uint16)targetPoxX;
		poxY = (uint16)targetPoxY;
		complete = true;
		return true;
	}

	uint16 index = p & 7;
	uint16 tx, ty;
	tx = uint16(poxX + MapTemplate::around[index][0] * basenumber);
	ty = uint16(poxY + MapTemplate::around[index][1] * basenumber);

	if(creature.GetMap()->GetMapTemp()->IsCanRun(poxX, poxY, tx, ty, true))
	{
		poxX = tx;
		poxY = ty;
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
//���󹤳�

namespace Tea
{
	//INSTANTIATE_SINGLETON_1(MovementGeneratorRegistry);
    //template class Tea::Singleton<MovementGeneratorRegistry>; 
	template<> MovementGeneratorRegistry * Tea::Singleton<MovementGeneratorRegistry  >::si_instance = 0; 
	template<> bool Tea::Singleton<MovementGeneratorRegistry >::si_destroyed = false;

	MovementGenerator* SelectMovementGenerator(Creature *creature)
	{
		MovementGeneratorRegistry &mv_registry(MovementGeneratorRepository::Instance());
		//assert(creature->GetCreatureInfo() != NULL);
		//MovementGeneratorType type = creature->GetTemplate().

		//return new RandomMovementGenerator();

		const MovementGeneratorCreator *mv_factory = mv_registry.GetRegistryItem((MovementGeneratorType)creature->GetMoveType());
		return (mv_factory == NULL ? NULL : mv_factory->Create(creature));
	}

	MovementGenerator* SelectMovementGenerator(Creature *creature, MovementGeneratorType type, int param1)
	{
		MovementGeneratorRegistry &mv_registry(MovementGeneratorRepository::Instance());

		const MovementGeneratorCreator *mv_factory = mv_registry.GetRegistryItem(type);
		return (mv_factory == NULL ? NULL : mv_factory->Create(creature));
	}

	void InitializeMovement()
	{
		(new MovementGeneratorFactory<DisappearMovementGenerator>(DISAPPEAR_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<DeadlineMovementGenerator>(DEADLINE_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<IdleMovementGenerator>(IDLE_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<RandomMovementGenerator>(RANDOM_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<WayPointMovementGenerator>(WAYPOINT_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<HomeMovementGenerator>(HOME_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<FollowMovementGenerator>(FOLLOW_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<FollowInlineMovementGenerator>(FOLLOW_INLINE_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<WayFindingMovementGenerator>(WAYFINDING_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<WayFindingAndAttackMovementGenerator>(WAYFINDING_ATTACK_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<MercenaryMovementGenerator>(MERCENARY_MOTION_TYPE))->RegisterSelf();
		(new MovementGeneratorFactory<WayFindingDstMovementGenerator>(WAYFINDDST_MOTION_TYPE))->RegisterSelf();

		//�����ǳ�ʼ���������һ�¹��ܡ�
		//��ʼ��Ѱ·����
		WayFindingMovementGenerator::find_link.resize(200, 0);
		WayFindingDstMovementGenerator::find_link.resize(200, 0);
	}
}
