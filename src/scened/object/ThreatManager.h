#ifndef _THREAT_MANAGER_H
#define _THREAT_MANAGER_H

#include <comm/common_stl.h>
#include "Unit.h"

class Unit;
class Creature;

class ThreatManager
{
public:
	ThreatManager()
		:me(0), actionradius(0.0f),visionradius(0.0f),bornX(0.0f),bornY(0.0f),m_targetMap()
	{
	}

	~ThreatManager(){m_targetMap.clear();};

	void Initialize(Creature *unit, uint32 _visionradius, uint32 _actionradius);

	//���ӹ������
	void Add(Unit *target,uint32 v);

	//���ٹ������
	void Sub(Unit *target,uint32 v)
	{ 
		TargetMap::iterator iter = m_targetMap.find(target->GetUIntGuid());
		if(iter != m_targetMap.end())
		{
			if(iter->second.first  > v) iter->second.first  -= v;
			else m_targetMap.erase(iter);/*iter->second.first = 0;*/
		}
	}
	void SetActioRadius(float radius)
	{
		actionradius = radius;
	}
	float GetActioRadius()
	{
		return actionradius;
	}
	void SetVersionRadius(float radius)
	{
		visionradius = radius;
	}
	//ɾ�����
	void Del(Unit *target, bool isDelOwnerShip = false);

	void ApplyPctModify(Unit *target,float f)
	{
		ASSERT(f >= 0 );
		TargetMap::iterator iter = m_targetMap.find(target->GetUIntGuid());
		if(iter != m_targetMap.end())
		{
			iter->second.first = (uint32)(iter->second.first * f);
		}
	}
	
	//���
	void Clear();

	//
	Unit *GetTarget();
	
	void Update(uint32 diff);

protected:
	void CaluThreatByDistance(Unit *_target);
	void UpdateThreatMap();

	//�жϾ���õ����ֵ
	inline  uint32 getThreat(const float &distance)
	{
		ASSERT(visionradius >= distance);
		return uint32(visionradius - distance) + 1;
	}

private:
	//���ֵ(������ޣ������ޣ�
	typedef std::pair<uint32, uint32> ThreatValue;
	typedef UNORDERED_MAP<uint32, ThreatValue> TargetMap;
	Creature *me;
	//��뾶	
	float actionradius;
	//��Ұ�뾶	
	float visionradius;

	float bornX;
	float bornY;
	TargetMap m_targetMap;
};

#endif

