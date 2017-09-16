#include "scened_app.h"
#include "scened_context.h"
#include "Player.h"
#include "Creature.h"
#include "Map.h"
#include "QuestGetter.h"
#include "scened_scripts.h"
#include "LootManager.h"
#include "GameObject.h"
#include <shared/log_handler.h>
#include <object/OprateResult.h>

void ScenedContext::_Handle_QuestObject_Use(Unit *go)
{
    //	ASSERT(go->GetEntry() == GO_TYPE_QUEST);
    GameObject *goQuest = static_cast<GameObject*>(go);
    ASSERT(goQuest->IsQuestGO());
    ASSERT(goQuest->CanUse());

	// �ɼ��Ժ�Ĵ���
	DoHandlePickGameObject(this->GetPlayer(), go->GetEntry());

 //   m_player->GetQuestMgr()->CastedCreatureOrGO(goQuest, 0);

	////���GameObject
 //   LootManager::GenerationQuestLoot(m_player, goQuest, NULL);	
	//Call_Operation_Failed(OPRATE_TYPE_USE_GAMEOBJECT, USE_GAMEOBJECT_QUEST);    
}

void ScenedContext::Handle_QuestGiver_Status_Query(packet& pkt)
{
    uint32 guid;

    if(unpack_questgiver_status_query(&pkt, &guid))
    {
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTGIVER_STATUS_QUERY,ACCACK_PACKET_TYPE_UNPACK,"");
        return;
    }

    //TODO:��ֻ��������
    Creature *questGiver = (Creature*)m_player->GetMap()->FindCreature(guid);

    if(!questGiver)
    {
        tea_perror("player:%s Handle_QuestGiver_Status_Query not find", m_player->GetName().c_str());
        return;
    }

    //û�������־
    if(!questGiver->isQuestGiver())
        return;

    //������������ģ��ID
    quest_wo_relation_db.add_select_condition(MEMDB_EQ(quest_wo_relation, wo_entry, questGiver->GetEntry()));
    MemDB_Result<quest_wo_relation> result = quest_wo_relation_db.select();

    //�������еĸ����� ��������
    QuestGetter *questGetter = m_player->GetQuestMgr();
    //ASSERT(questGetter);
	if (questGetter == NULL)
	{
		tea_perror("assert error: Handle_QuestGiver_Status_Query  ASSERT(questGetter)");
		Close(PLAYER_CLOSE_OPERTE_SCREND_ONE34,"");
		return;
	}
	

    //NPC״̬
    uint8 status_result1 = DIALOG_STATUS_NONE;
    uint8 status_result2 = DIALOG_STATUS_NONE;

    for(uint32 i = 0; i < result.size(); i++)
    {
        status_result2 = questGetter->GetGiverStatus(result[i]);

        if(status_result2 > status_result1)
            status_result1 = status_result2;
    }

	Call_questgiver_status(m_delegate_sendpkt,questGiver->GetUIntGuid(), status_result1);
}

//
void ScenedContext::Handle_Questhelp_Get_CanAccept_List(packet& pkt)
{
    //TODO:����ÿ�ζ�ˢ��
    m_player->GetQuestMgr()->RefreshCanSeeQuests();
}

void ScenedContext::Handle_QuestGiver_Accept_Quest(packet& pkt)
{
    uint32 guid;
    uint32 quest_id;

    if(unpack_questgiver_accept_quest(&pkt, &guid, &quest_id))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTGIVER_ACCEPT_QUEST,ACCACK_PACKET_TYPE_UNPACK,"");
        return ;
	}
    quest_template const *pQuest = quest_template_db[quest_id];

    if(!pQuest)
    {
        tea_perror("Handle_QuestGiver_Accept_Quest GUID[%s] quest:[%u] not find", m_player->GetGuid().c_str(), quest_id);
        return;
    }

	if(!m_player->m_questMgr->CanTakeQuest(pQuest,true))
	{
		tea_perror("player:[%s] repeat quest:%u!", m_player->GetGuid().c_str(), pQuest->id);
		return;
	}			
	
    Creature *questGiver = (Creature*)m_player->GetMap()->FindCreature(guid);
	if (questGiver)
	{
		if (!m_player->IsReasonableDistancePos(questGiver))
		{
			Call_Operation_Failed(OPRATE_TYPE_INTERACTION,INTERACTION_TOO_FAR);			
			tea_perror("player:[%s] npc:[%u] Too far away��%f,%f��",
				m_player->GetGuid().c_str(),questGiver->GetEntry(),
				m_player->GetPositionX(),m_player->GetPositionY());
			return;
		}
	}

	m_player->GetQuestMgr()->AddQuest(quest_template_db[quest_id]);

    //���ܵ�ʱ���ж��ܲ���������񣬿���ֱ�����
    if(IsAutoComplete(pQuest))
        m_player->GetQuestMgr()->CompleteQuest(quest_id);
	//�ȼ���֤
	else if (pQuest->req_level>0 && m_player->GetQuestMgr()->CanCompleteQuest(quest_id))
	{
		m_player->GetQuestMgr()->CompleteQuest( quest_id );
	}
	//ս������֤,�����Ƿ��ֶ��Ĳ����������ɵ�
	else if (pQuest->suggested_players>0 && m_player->GetQuestMgr()->CanCompleteQuest(quest_id) && !IsManualComplete(pQuest))
	{
		m_player->GetQuestMgr()->CompleteQuest( quest_id );
	}	
}

void ScenedContext::Handle_QuestGiver_Remove_Quest(packet& pkt)
{
    uint8 slot;
	uint64 reserve;
    if(unpack_questlog_remove_quest(&pkt, &slot,&reserve))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTLOG_REMOVE_QUEST,ACCACK_PACKET_TYPE_UNPACK,"");
        return ;
	}
    if(slot < MAX_QUEST_LOG_SIZE)
    {
        uint32 quest_id = m_player->GetQuestMgr()->GetQuestSlotQuestId(slot);

        quest_template *pQuest = quest_template_db[quest_id];

        if(!pQuest)
        {
            return;
        }

		//�ǿɷ��������񲻸�����
		if (!CanRemove(pQuest))
		{
			WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTLOG_REMOVE_QUEST,ACCACK_PACKET_TYPE_UNPACK,"");
			return ;
		}
		

        //���������������и������Ļ�Ҫ���յ�ม���
        uint32 itemid, item_count ;

        for(int j = 0; j < QUEST_OBJECTIVES_COUNT; j++)
        {
            itemid = (uint32)pQuest->src_item_id[j];
            item_count = (uint32)pQuest->src_item_count[j];

            if(itemid == 0 || item_count == 0)
                break;

            if(!item_template_db[itemid])
            {
                tea_perror("player:%s questid:%u src_item:%u not find",m_player->GetGuid().c_str(), pQuest->id, itemid);
                continue;
            }

            //ֱ���Ƴ�������������˵
            for(uint32 k = 0; k < item_count; k++)
                m_player->GetQuestMgr()->PopQuestItemSlot(itemid);
        }

		//��¼����������־
		WriteTask(GetAccount(),GetGuid(), quest_id, m_player->GetMapId(),1);
       
		m_player->GetQuestMgr()->SetQuestSlot(slot, 0);
    }  
}

void ScenedContext::Handle_QuestGiver_Complete_Quest(packet& pkt)
{
    uint32 npc_guid;
    uint32 quest_id;
    uint8 reward = 0;			//ѡ����������Ʒ
    bool must_reward = false;	//�п�ѡ����
    if(unpack_questgiver_complete_quest(&pkt, &npc_guid, &quest_id, &reward))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTGIVER_COMPLETE_QUEST,ACCACK_PACKET_TYPE_UNPACK,"");
        return;
	}
    //��֤��������
    if(reward >= QUEST_REWARD_CHOICES_COUNT)
    {
        tea_perror("Error in CMSG_QUESTGIVER_COMPLETE_QUEST :player %s (guid %s) tried to get invalid reward (%u) (probably packet hacking)",
                   m_player->GetName().c_str(), m_player->GetGuid().c_str(), reward);
        return;
    }

	if (!m_player->GetMap())
	{
		tea_perror("error: m_player->GetMap() == NULL!!!");
		return;
	}
	quest_template const *pQuest = quest_template_db[quest_id];
	if(!pQuest)
		return;

	QuestGetter *qGetter = m_player->GetQuestMgr();
	if (!qGetter)
		return;
	Creature *npc = nullptr;
	bool isneednpc = IsCheckCommitNPC(pQuest);
	if(isneednpc)
	{
		npc = (Creature*)m_player->GetMap()->FindCreature(npc_guid);		
	}
	else
	{
		uint32 npc_entry = qGetter->FindCommitNpcEntry(quest_id);
		if (npc_entry)
			npc = (Creature*)m_player->FindNPC(npc_entry);
	}
	
	//�ҵ�npc��У��
	if (npc)
	{
		if (!m_player->IsReasonableDistancePos(npc))
		{
			Call_Operation_Failed(OPRATE_TYPE_INTERACTION,INTERACTION_TOO_FAR);
			tea_perror("���������̫Զ����ǰ���꣨%f,%f��",m_player->GetPositionX(),m_player->GetPositionY());
			return;
		}

		//У��һ����������Ƿ������ｻ�� begin
		quest_wo_relation_db.add_select_condition(MEMDB_EQ(quest_wo_relation, quest_id, pQuest->id));
		quest_wo_relation_db.add_select_condition(MEMDB_EQ(quest_wo_relation, wo_entry, npc->GetEntry()));
		MemDB_Result<quest_wo_relation> result = quest_wo_relation_db.select();
		quest_wo_relation *wo_result = nullptr;

		for(uint32 i = 0; i < result.size(); i++)
		{
			if(result[i]->relatetion_type == QUEST_RELATION_TYPE_END)
			{
				wo_result = result[i];
				break;
			}
		}
		if(!wo_result)
		{
			tea_perror("Error in CMSG_QUESTGIVER_COMPLETE_QUEST :player %s (guid %s) tried to complete quest %u from npc %s",
				m_player->GetName().c_str(), m_player->GetGuid().c_str(), pQuest->id, npc->GetName().c_str());
			return;
		}
		//У��һ����������Ƿ������ｻ�� end 
	}

    //�Ƿ������ɣ�������������
    if(qGetter->CanCompleteQuest(pQuest->id))
        qGetter->CompleteQuest(pQuest->id);

    //���δ���
    if(qGetter->GetQuestStatus(quest_id) != QUEST_STATUS_COMPLETE)
    {
        tea_perror("���[%s],δ�������[%u],ƾʲô������ɰ�", m_player->GetGuid().c_str(), quest_id);
		return;
    }
    
	//��ʼ������
    for(int i = 0; i < QUEST_REWARD_CHOICES_COUNT; i++)
    {
        if(pQuest->rew_choice_item_id[i] != 0)
        {
            must_reward = true;
            break;
        }
    }

    //����п�ѡ������û��ѡ
    if(must_reward && pQuest->rew_choice_item_id[reward] == 0)
        tea_pwarn("�п�ѡ��������û��ѡ��");

    //�����
    if(qGetter->CanRewardQuest(pQuest, true))
	{
        qGetter->RewardQuest(pQuest, reward);
		//ִ����ɽű�
		DoCompleteQuest(m_player->GetMap(), m_player, pQuest->id);

		//֪ͨ�ͻ��˲����������Ч��
		Call_questgetter_complete(m_delegate_sendpkt, pQuest->id);

		//�������������������������ʾ��ϸ
		if (npc)
			qGetter->SendNextChainQuest(npc, pQuest->id);

		//ˢ�¿ɽ��б�
		m_player->GetQuestMgr()->RefreshCanSeeQuests();
	}
}

//ʹ��������Ʒ
void ScenedContext::Handle_QuestUpdate_Use_Item(packet& pkt)
{
    uint32 item_id;

    if(unpack_questupdate_use_item(&pkt, &item_id))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTUPDATE_USE_ITEM,ACCACK_PACKET_TYPE_UNPACK,"");
        return;
	}
    DoQuestItemScript(m_player, item_id);
}

//�������̵ֽ̳�ֱ�������������ջ�����������
void ScenedContext::Handle_QuestHelp_Complete(packet& pkt)
{
    uint32 quest_id;
    uint8 status;		//�Ƿ��Զ�����
	uint8 reserve;		//��1Ϊ��ȡ�ջ�����

    if(unpack_questhelp_complete(&pkt, &quest_id, &status,&reserve))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTHELP_COMPLETE,ACCACK_PACKET_TYPE_UNPACK,"");
        return;
	}

    quest_template const *pQuest = quest_template_db[quest_id];

    if(!pQuest)
        return;

    //�����ֶ����
    if(!IsManualComplete(pQuest))
    {
        tea_pwarn("�����ֶ��������guid(%s),questid(%u)", m_player->GetGuid().c_str(), quest_id);
        return;
    }

	if (!m_player || !m_player->GetQuestMgr())
	{
		tea_pwarn("�ֶ��������ʱ�Ҳ�����һ������������guid(%s),questid(%u)", m_player->GetGuid().c_str(), quest_id);
		return;
	}

    QuestGetter *qGetter = m_player->GetQuestMgr();

    uint16 slot = qGetter->FindQuestSlot(quest_id);

    if(slot < MAX_QUEST_LOG_SIZE)
    {	
		if(qGetter->GetQuestStatus(quest_id) != QUEST_STATUS_COMPLETE)
			qGetter->CompleteQuest(quest_id);
    }
}

//�������̵ֽ̳������±����
void ScenedContext::Handle_QuestHelp_Update_Status(packet& pkt)
{
	uint32 quest_id;
	uint32 slot_id;
	uint32 num;

	if(unpack_questhelp_update_status(&pkt, &quest_id, &slot_id, &num))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTHELP_UPDATE_STATUS,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	quest_template const *pQuest = quest_template_db[quest_id];

	if(!pQuest)
		return;

	//�����ֶ����
	if(!IsManualComplete(pQuest))
	{
		tea_pwarn("�����ֶ��������guid(%s),questid(%u)", m_player->GetGuid().c_str(), quest_id);
		return;
	}

	QuestGetter *qGetter = m_player->GetQuestMgr();

	uint16 slot = qGetter->FindQuestSlot(quest_id);
	if(slot < MAX_QUEST_LOG_SIZE)
	{
		if(qGetter->GetQuestStatus(quest_id) != QUEST_STATUS_COMPLETE)
			qGetter->AddQuestItemBySlot(quest_id,slot_id,num);
	}

}

//����Ի�ѡ��
void ScenedContext:: Handle_QuestHelp_Talk_Option(packet&pkt)
{
	uint32 quest_id;
	uint32 option_id;
	int32 value0;
	int32 value1;

	if(unpack_questhelp_talk_option(&pkt,&quest_id,&option_id,&value0,&value1))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTHELP_TALK_OPTION,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
}

//��ѯ��������
void ScenedContext:: Handle_QuestHelp_Query_Book(packet&pkt)
{
	uint32 dynasty_id;

	if(unpack_questhelp_query_book(&pkt,&dynasty_id))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_QUESTHELP_QUERY_BOOK,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	QuestGetter *qGetter = m_player->GetQuestMgr();
	qGetter->SendBookQuest(dynasty_id);
}

void ScenedContext::Handle_Query_Quest_Status(packet& pkt)
{
	if(!m_player || !m_player->GetQuestMgr())
		return;

	uint16 len;
	quest_status *quest_s;
	if(unpack_query_quest_status(&pkt, &quest_s, &len))
	{
		WriteAttackPacker(GetAccount(),m_lguid,MSG_QUERY_QUEST_STATUS,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	for (uint16 i = 0; i < len; i++)
	{
		(quest_s + i)->status = m_player->GetQuestMgr()->GetQuestStatus((quest_s + i)->quest_id);
	}
	packet *_pkt;
	pack_query_quest_status(&_pkt, quest_s, len);
	SendPacket(*_pkt);	
	external_protocol_free_packet(_pkt);
}
