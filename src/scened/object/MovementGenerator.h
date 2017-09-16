#ifndef _MOVEMENT_GENERATOR_H_
#define _MOVEMENT_GENERATOR_H_

#include <comm/timer.h>
#include <shared/FactoryHolder.h>
#include "Unit.h"
#include "GameObject.h"

//#define TRAVELLER_UPDATE_INTERVAL  100

class Creature;

enum WayfindingType
{
	WAYFINDINGTYPE_NONE = 0,								//��Ѱ·��ʽ
	WAYFINDINGTYPE_WAYPOINT = 1,							//�ɵ�Ѱ·
	WAYFINDINGTYPE_CONTINUOUS = 2,							//����Ѱ·
	WAYFINDINGTYPE_POINT_BY_POINT = 3,						//���Ѱ·
	WAYFINDINGTYPE_MAX
};

enum FOLLOW_MOVE_TYPE
{
	FOLLOW_MOVE_TYPE_FOREVER		= 0,	//��Զ����
	FOLLOW_MOVE_TYPE_LIMIT			= 1,	//��ʱ����
	FOLLOW_MOVE_TYPE_LIMIT_CLEAR	= 2,	//��ʱ���棬ʱ�䵽�Ժ���ʧ
	FOLLOW_MOVE_TYPE_MAX,
};

//////////////////////////////////////////////////////////////////////////
//
typedef struct war_robot_distance_threat_t
{
	Unit *unit;
	float dis_threat;
}war_robot_distance_threat;

class MovementGenerator
{
public:
	virtual ~MovementGenerator(){};

	virtual void Initialize(Unit &,uint64  = 0, int64 = 0){};
	virtual void Finalize(Unit &) {};
	virtual void Reset(Unit &) {};
	virtual bool Update(Unit &, const uint32 &time_diff) = 0;
	virtual MovementGeneratorType GetMovementGeneratorType() = 0;
	virtual void unitSpeedChanged() { }
	virtual bool GetDestination(float& /*x*/, float& /*y*/) const { return false; }
		
	static void RandomPath(Unit *unit,std::deque<float>& path,uint32 ms,float x,float y);		//���·��
	static void RandomPos(float& nx,float& ny,float fPosX,float fPosY,float range = 4.0f);	
protected:
	static void RandomPos(float& nx,float& ny,const Unit *wo,float range = 4.0f);	

	static inline void GetNewPos(float& nx,float& ny,float fPosX,float fPosY,float range,float angle)
	{
		const float distanceX = range * cos(angle);
		const float distanceY = range * sin(angle);

		nx = fPosX + distanceX;
		ny = fPosY + distanceY;
	}
};


//////////////////////////////////////////////////////////////////////////
//for ��ֹ,
class IdleMovementGenerator : public MovementGenerator
{
public:
	//�����ֹ̫������,����Ҳ�Ƕ�ʱ��ֹ
	IntervalTimer m_timer;

	void Initialize(Unit &,uint64 = 0 , int64 t = 0)
	{
		m_timer.SetInterval(t);
		m_timer.SetCurrent(0);
	}

	bool Update(Unit &unit, const uint32 &diff)
	{
		//������õ�ʱ��Ϊ0��һֱ��ֹ
		if(m_timer.GetInterval()==0)
			return true;

		//�����ʱ��,��ô����
		m_timer.Update(diff);
		if (m_timer.Passed())
		{
			unit.SetTarget(NULL);		//��Ȼ��޹����޷�ָ����ȥ����
			return false;
		}
		return true;
	}
	MovementGeneratorType GetMovementGeneratorType()
	{
		return IDLE_MOTION_TYPE;
	}
};

template<class T, class D>
class MovementGeneratorMedium : public MovementGenerator
{
public:
	void Initialize(Unit &u,uint64 param = 0, int64 t = 0)
	{
		//u->AssertIsType<T>();
		(static_cast<D*>(this))->Initialize(*((T*)&u),param,t);
	}
	void Finalize(Unit &u)
	{
		//u->AssertIsType<T>();
		(static_cast<D*>(this))->Finalize(*((T*)&u));
	}
	void Reset(Unit &u)
	{
		//u->AssertIsType<T>();
		(static_cast<D*>(this))->Reset(*((T*)&u));
	}
	bool Update(Unit &u, const uint32 &time_diff)
	{
		//u->AssertIsType<T>();
		return (static_cast<D*>(this))->Update(*((T*)&u), time_diff);
	}
public:
	// will not link if not overridden in the generators
	void Initialize(T &u,uint64 = 0, int64 t = 0);
	void Finalize(T &u);
	void Reset(T &u);
	bool Update(T &u, const uint32 &time_diff);
};

//////////////////////////////////////////////////////////////////////////
//��·���߶�
class WayPointMovementGenerator : public MovementGeneratorMedium<Creature,WayPointMovementGenerator>
{
public:
	WayPointMovementGenerator(){}
	void Initialize(Creature &,uint64 param = 0,int64 t = 0);
	void Reset(Creature &);
	bool Update(Creature &, const uint32 &);
	void Finalize(Creature &);

	MovementGeneratorType GetMovementGeneratorType() { return WAYPOINT_MOTION_TYPE; }
	vector<mt_point> path;
private:	
	uint32 wayid;
	uint32 point_index;	
	//�Ƿ���Ҫ����״̬
	bool m_revert_active_grid;;
};

//Ѱ·����Ŀ��
class WayFindingMovementGenerator : public MovementGeneratorMedium<Creature,WayFindingMovementGenerator>
{
public:
	WayFindingMovementGenerator();

	virtual void Initialize(Creature &creature, uint64 param = 0, int64 t = 0);
	virtual void Reset(Creature &) {};
	virtual void Finalize(Creature &creature);
	virtual bool Update(Creature &creature, const uint32 &diff);

	virtual MovementGeneratorType GetMovementGeneratorType();
	static vector<float> find_link;		//Ѱ·�õ���·��ͼ
protected:
	float targetPoxX, targetPoxY;		//Ŀ������
	WayfindingType find_type;			//Ѱ·����
	float recall[4][2];					//��¼ÿһ��Ѱ·���Ĵ�һ�飬��������ͬ������������Χ
	int recallpos;						//recall�ĵ�ǰָ��
	uint16 basenumber;					//������Χ
	uint32 offset_angle,offset_radius;	//Ϊ���ùַ�ɢһ��
	bool WayPointFindPath(Creature &creature, Unit *target, uint16 cnx, uint16 cny);	
	//����Ѱ·
	bool ContinuousFindPath(Creature &creature, Unit *target, uint16 cnx, uint16 cny);
	//����ͨ��
	bool TestGo(Unit *target, uint16 &poxX, uint16 &poxY, uint16 p, bool &complete);
	bool FindPath(Creature &creature, Unit *target, uint16 cnx, uint16 cny);
	//����ͨ��
	bool TestGo(Creature &creature, Unit *target, uint16 p, uint16 &toPoxX, uint16 &toPoxY);
	virtual void GetTargetPos(Creature &creature, Unit *target, const MapTemplate *mt);
};

//Ѱ·׷ɱ
class WayFindingAndAttackMovementGenerator:public WayFindingMovementGenerator
{
public:
	WayFindingAndAttackMovementGenerator();

	virtual void Initialize(Creature & creature, uint64 param = 0, int64 t = 0);
    virtual bool Update(Creature &creature, const uint32 &diff);
	virtual MovementGeneratorType GetMovementGeneratorType()
	{
		return WAYFINDING_ATTACK_MOTION_TYPE;
	}
protected:
	bool m_is_attack_target;
	uint32 m_target_dis;						//׷ɱʱ������Ŀ����������
	//IntervalTimer m_recover_timer;				//�Զ��ָ���ʱ��
private:
	struct spell_cast_probability_t *spell;		//Ŀǰ������ļ��ܣ������NULL��������ͨ����
	bool AttackTarge(Creature &creature, const uint32 &diff);

	//��������
	void Attack(Creature &creature, const uint32 &diff);

	void RandSpell(Creature &creature, float dis);
	bool IsInCastRange(Creature &creature, float dis);
	bool lessThan(float dis, float dis2);
};

//ľżʽ�ĳ����ƶ���ʽ��������Ҳ����������ѡ���Ŀ��
class MercenaryMovementGenerator : public WayFindingAndAttackMovementGenerator
{
public:
	MercenaryMovementGenerator();
	virtual void Initialize(Creature &,uint64 param = 0,int64 t = 0);
	virtual void Reset(Creature &creature){ Initialize(creature);}
	virtual bool Update(Creature &, const uint32 &);
	virtual void Finalize(Creature &creature);
	MovementGeneratorType GetMovementGeneratorType()
	{
		return MERCENARY_MOTION_TYPE;
	}
protected:
	virtual Unit *GetAttackTarget(Creature &creature,Unit *owner);
protected:
	//�Ƿ�ṥ��Ŀ��
	bool m_canAttack;
	//ֹͣ�������Ƿ������ƶ�
	bool m_canRandomMove;
	uint8 follow_type;
	//�Ƿ���Ҫ����״̬
	bool m_revert_active_grid;
	//����Ķ���
	uint32 m_owner;	
	//����ƶ���ʱ��
	TimeTrackerSmall m_next_random_move;
	//�Ƿ�����ƶ���
	bool m_is_random_move;	
	//����ʱ��
	IntervalTimer m_timer;
};

//Ѱ·����ָ���ص�
class WayFindingDstMovementGenerator : public MovementGeneratorMedium<Creature,WayFindingDstMovementGenerator>
{
public:
	WayFindingDstMovementGenerator();

	virtual void Initialize(Creature &creature, uint64 param = 0, int64 t = 0);
	virtual void Reset(Creature &) {};
	virtual void Finalize(Creature &creature);
	 virtual bool Update(Creature &creature, const uint32 &diff);
	virtual MovementGeneratorType GetMovementGeneratorType();
	static vector<float> find_link;		//Ѱ·�õ���·��ͼ
protected:
	float targetPoxX, targetPoxY;		//Ŀ������
	WayfindingType find_type;			//Ѱ·����
	float recall[4][2];					//��¼ÿһ��Ѱ·���Ĵ�һ�飬��������ͬ������������Χ
	int recallpos;						//recall�ĵ�ǰָ��
	uint16 basenumber;					//������Χ
	uint32 offset_angle,offset_radius;	//Ϊ���ùַ�ɢһ��
	bool WayPointFindPath(Creature &creature, uint16 cnx, uint16 cny);	
	//����Ѱ·
	bool ContinuousFindPath(Creature &creature, uint16 cnx, uint16 cny);
	//����ͨ��
	bool TestGo(Creature &creature, uint16 &poxX, uint16 &poxY, uint16 p, bool &complete);
	bool FindPath(Creature &creature);
};

//////////////////////////////////////////////////////////////////////////
//���󹤳�

namespace Tea
{

struct SelectableMovement : public FactoryHolder<MovementGenerator,MovementGeneratorType>
{
	SelectableMovement(MovementGeneratorType mgt) : FactoryHolder<MovementGenerator,MovementGeneratorType>(mgt) {}
};

template<class REAL_MOVEMENT>
struct MovementGeneratorFactory : public SelectableMovement
{
	MovementGeneratorFactory(MovementGeneratorType mgt) : SelectableMovement(mgt) {}

	MovementGenerator* Create(void *) const
	{
		return (new REAL_MOVEMENT());
	}
};

typedef FactoryHolder<MovementGenerator,MovementGeneratorType> MovementGeneratorCreator;
typedef FactoryHolder<MovementGenerator,MovementGeneratorType>::FactoryHolderRegistry MovementGeneratorRegistry;
typedef FactoryHolder<MovementGenerator,MovementGeneratorType>::FactoryHolderRepository MovementGeneratorRepository;

MovementGenerator* SelectMovementGenerator(Creature *);
MovementGenerator* SelectMovementGenerator(Creature *,MovementGeneratorType type,int param1 = 0);

void InitializeMovement();

}

#endif

