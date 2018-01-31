#include "scened_app.h"
#include <object/SharedDef.h>
#include <shared/probability_rand.h>
#include <shared/storage_loader.h>
#include <math.h>
#include <object/PlayerBase.h>

#include "Creature.h"
#include "GameObject.h"
#include "LootManager.h"
#include "Map.h"
#include "Player.h"
#include "scened_context.h"
#include "QuestGetter.h"
#include "scened_scripts.h"



//��Ʒ��������
vector<uint32> LootManager::Loot_possibility_range;			//���ʷ�Χ

//-------------------------------For ownerships -------------------------------------------------
//��������Ʒ
void LootManager::GenerationQuestLoot(Player *player, Unit *go, OwnershipVec* m_ownerquests)
{
//    ASSERT(player);
	if (player == NULL)
	{
		tea_perror("assert error: GenerationQuestLoot ASSERT(player)");
		return;
	}
	

    int entry = go->GetEntry();

    if(go->GetTypeId() == TYPEID_GAMEOBJECT)
        entry *= -1;

    //����������Ʒ
	quest_loot_item_db.add_select_condition(MEMDB_EQ(quest_loot_item, creature_id, entry));
	MemDB_Result<quest_loot_item> result1 = quest_loot_item_db.select();

    for(uint32 i = 0; i < result1.size(); i++)
    {
        if(!result1[i]->quest_id)
            continue;

        if(urand(0, Loot_possibility_range[1]) < result1[i]->possibility * player->GetCoefficient().drop_rate_multiples / 100)
        {
            if(m_ownerquests == NULL)
            {
                //�жϹ������Ƿ���������
                if(player->GetQuestMgr()->GetQuestStatus(result1[i]->quest_id) == QUEST_STATUS_INCOMPLETE)
                    player->GetQuestMgr()->AddQuestItem(result1[i]->entry, result1[i]->count);
            }
            else
            {
				//����Ʒ�����з�
                for(OwnershipVec::iterator it = m_ownerquests->begin();
                        it != m_ownerquests->end();)
                {
                    //�����ߺϷ����жϣ�������������������������--������޴���
                    Player* owner = go->GetMap()->FindPlayer(*it);

                    if(owner && owner->GetMap() == go->GetMap()												//�Ƿ񱾵�ͼ
                            && owner->GetQuestMgr()->GetQuestStatus(result1[i]->quest_id) == QUEST_STATUS_INCOMPLETE) //�������Ƿ���������
                    {
                        owner->GetQuestMgr()->AddQuestItem(result1[i]->entry, result1[i]->count);
                    }

                    it++;
                }
            }
        }
    }
}


//����ս��Ʒ����,�ж�IX��IY�Ƿ����
bool LootManager::ConsLootPoint(Map *map, uint32 &x, uint32 &y, int ix, int iy)
{
    if(map->IsEnpty(ix, iy))
    {
		//���Ա߳�����ԭΪ������ս��Ʒ����
        x = ix * g_Config.loot_area;
        y = iy * g_Config.loot_area;
        return true;
    }

    return false;
}

//����ս��Ʒ����
void LootManager::ConsLootPoint(Map *map, uint32 &xm, uint32 &ym)
{
	if(ConsLootPoint(map, xm, ym, xm, ym))
	{
		return;
	}
	/**
	for(int w = 1; ; ++ w)
	{
		// ��
		for (int dx = -w; dx <= w; ++ dx) {
			if(ConsLootPoint(map, xm, ym, xm + dx, ym - w)) {
				return;
			}
		}

		// ��
		for (int dy = -w; dy <= w; ++ dy) {
			if(ConsLootPoint(map, xm, ym, xm + w, ym + dy)) {
				return;
			}
		}

		// ��
		for (int dx = w; dx >= -w; -- dx) {
			if(ConsLootPoint(map, xm, ym, xm + dx, ym + w)) {
				return;
			}
		}

		// ��
		for (int dy = w; dy >= -w; -- dy) {
			if(ConsLootPoint(map, xm, ym, xm - w, ym + dy)) {
				return;
			}
		}
	}
	*/
	for(int w = 1; ; w++)
	{
		for(int h = w; h >= -w; h--)
		{
			if(ConsLootPoint(map, xm, ym, xm - w, ym - h))
			{
				return;
			}
			if(ConsLootPoint(map, xm, ym, xm + w, ym - h))
			{
				return;
			}
			if(ConsLootPoint(map, xm, ym, xm + h, ym - w))
			{
				return;
			}
			if(ConsLootPoint(map, xm, ym, xm + h, ym + w))
			{
				return;
			}
		}
	}
}

//����ս��Ʒ
void LootManager::GenerationLoot(Player* player, Creature *m_obj, Unit* unit)
{
	if(!m_obj->GetMap()->HaveEnpty())
	{
		return;
	}
    //ASSERT(player);
	if (player == NULL)
	{
		tea_perror("assert error: GenerationLoot ASSERT(player)");
		return;
	}

    //����ս��Ʒ���ɽű�
    auto *creatrue_template = creature_template_db[m_obj->GetEntry()];
	if(creatrue_template)
		DoLootAllot(player, (Creature*)m_obj, unit, creatrue_template->monster_type);	
}

//ս��Ʒ����
void LootManager::LootAllot(Unit* unit, Creature *m_obj, bool isOneOne)
{
    //������� ս��Ʒ�����·�
	Player *killer = NULL;	//���һ����ɱ���
	if(unit->GetTypeId() == TYPEID_PLAYER)
	{
		killer = dynamic_cast<Player*>(unit);
	}

	if(!killer || !killer->GetSession())	//���һ���������
		return;
	double vip_exp = 0;
    //����ӿ�
    if(m_obj->GetTypeId() == TYPEID_UNIT)
    {
		//����Ʒ�����з�
		for(OwnershipVec::iterator it = m_obj->m_ownerships.begin();
			it != m_obj->m_ownerships.end();)
		{
			//�����ߺϷ����жϣ�������������������������--������޴���
			Player* t_owner = m_obj->GetMap()->FindPlayer(*it);

			if(t_owner && t_owner->GetMap() == m_obj->GetMap())												//�Ƿ񱾵�ͼ
				//&& t_owner->GetQuestMgr()->GetQuestStatus(result1[i]->quest_id) == QUEST_STATUS_INCOMPLETE) //�������Ƿ���������
			{
				creature_template const *temp = creature_template_db[m_obj->GetEntry()];
				t_owner->GetQuestMgr()->KilledMonster(temp);
				t_owner->GetQuestMgr()->KilledLevelMonster(temp->level);
				if(t_owner != killer)
				{
					//���в����ɱ�������ҿɻ��50%�Ĺ��ﾭ��			
					double exp =DOComputeExpBonusScript(t_owner, m_obj, m_obj->GetFinallyExp(t_owner), 50,vip_exp); //�����������ᱻreturn
					t_owner->GainExp(exp,0,vip_exp);
				}
			}

			it++;
		}
	}
	//����ɱ����
	killer->GetSession()->AddKillMonster();

	//��ͨ����
	GenerationQuestLoot(killer, m_obj, &m_obj->m_ownerships);
	
    //����ս��Ʒ
	if(!isOneOne)
	{
		GenerationLoot(killer, m_obj, unit);
		//����ս��Ʒ������������б�
		m_obj->m_ownerships.clear();

		if(m_obj->GetTypeId() == TYPEID_UNIT)
		{
			// ����ӳ�,���һ��ɱ���������ҿɻ�øù���100%�ľ���
			// �������killer���ڶ���ľ�������Ϣ
			double exp =DOComputeExpBonusScript(killer, m_obj, m_obj->GetFinallyExp(killer),100,vip_exp); //�����������ᱻreturn
			// �������lua�д�����
			//killer->GainExp(exp,0, vip_exp);
		}
	}
}

//��Ҵ�������
void GameObject::UseGear(Player *player)
{
	if(this->GetGearStatus() > GO_GEAR_STATUS_END)
	{
		tea_perror("����״̬�쳣��״̬Ϊ%u������Ӧ���޸���", this->GetGearStatus());
		this->SetGearStatus(GO_GEAR_STATUS_START);
		return;
	}
	if(this->GetGearStatus() == GO_GEAR_STATUS_END)
	{
		tea_perror("�����Ѿ��ҵ��ˣ�Ϊʲô�ͻ��˻��ϴ�����");
		return;
	}
	if(player->GetMap() != this->GetMap())
	{
		tea_perror("��Һͻ��ز���ͬһ����ͼ.");
		return ;
	}

	//�ű��������������״̬��
	if(this->IsExecScript())
	{
		DoGameObjectScript(player, this, this->GetEntry());
	}
	else
	{
		//���ǿ�ʹ�õĻ��أ������״̬+1������ֱ�ӵ���
		if(this->CanUse())
			this->SetGearStatus(this->GetGearStatus() + 1);
		else
			this->SetGearStatus(GO_GEAR_STATUS_END);
	}

	//�㲥һ�¶�����
	this->BroadcastAction(player->GetUIntGuid());

	//���������ƣ���ս��Ʒ����ʧ������
	if(this->GetGearStatus() == GO_GEAR_STATUS_END)
	{
		//����ܳ�ս��Ʒ
		if(this->CanLoot())
		{
			
		}
	
		//������״̬�����ˣ����һ��ز��ǳ��ڴ��ڵ����ͣ���ɵ�
		if(!this->IsForeverUse())
		{
			this->GetMap()->m_go_dynamic.push_back(std::make_pair(g_Config.gear_exist_time, this->GetGuid()));
			this->SetGarbage(true);
		}
	}
}

//ʹ��֮�󣬹㲥������
bool GameObject::BroadcastAction(uint32 player_id)
{
	const gameobject_template* tpl = gameobject_template_db[this->GetEntry()];
	if(tpl->actionState != 0)
	{
		packet *pck;
		pack_use_gameobject_action(&pck, player_id, GetUIntGuid());
		this->GetMap()->Broadcast(*pck, this);
		return true;
	}
	return false;
}

