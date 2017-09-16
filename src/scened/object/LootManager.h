#ifndef _LOOT_MGR_H_
#define _LOOT_MGR_H_

#include <comm/common_stl.h>
#include <shared/MemoryDB.h>
#include <shared/storage_strus.h>
#include <protocol/external.h>

class Unit;

class LootManager
{
public:
	static void LootAllot(Unit* player, Creature *m_obj,bool isOneOne);								//ս��Ʒ���� �����Ƿ���ս��Ʒ	

	static void GenerationQuestLoot(Player* player, Unit *go, OwnershipVec* m_ownerships);			//��������Ʒ	
	static void ConsLootPoint(Map *map, uint32 &x, uint32 &y);		//����ս��Ʒ����
	static bool ConsLootPoint(Map *map, uint32 &x, uint32 &y, int ix, int iy);//����ս��Ʒ����
	static void GenerationLoot(Player* player, Creature *m_obj, Unit* unit);			//����ս��Ʒ
	
	//��Ʒ��������
	static vector<uint32> Loot_possibility_range;		//���ʷ�Χ
};

#endif

