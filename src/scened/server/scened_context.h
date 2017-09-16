#ifndef _SCENED_CONTEXT_H_
#define _SCENED_CONTEXT_H_

#include "scened.h"
#include "scened_app.h"
#include <core_obj/ByteArray.h>
#include "Creature.h"
#include "Player.h"

struct quest_template;

using core_obj::ByteArray;

//�������Ự ��������Ϣ
class ScenedContext:public PlayerBase,public SvrContext
{
public:
	ScenedContext(int fd,ContextManager *mgr);	

	//����·��,��ʼ��
	void OpcodeHandlerInitor();

	const string &GetGuid() const {return m_lguid;}
	Player *GetPlayer(){return m_player;}
	void Teleport(float to_x,float to_y,int to_mapid, const string &teleport_id, uint32 line_no = 0,uint32 instance_id = 0);
	void On_Teleport_OK(uint32 fd, uint32 mapid, uint32 instanceid, float x, float y);
	void SetExp()
	{
		if(m_player)
			SetDouble(PLAYER_EXPAND_INT_XP, m_player->GetExp());
	}
	void AddExp(double exp)
	{
		AddDouble(PLAYER_EXPAND_INT_XP,exp);
	}
	void LeaveScened();
protected:
	void Handle_LUA(packet& pkt);
	void Handle_Teleport(packet& pkt);				//��ʼ����
	void Handle_Move_Stop(packet& pkt);				//ֹͣ�ƶ�
	void Handle_Unit_Move(packet& pkt);				//Unit�ƶ�
	void Handle_Jump(packet& pkt);					//��
	
	void Handle_Use_Gameobject(packet& pkt);		//ʹ����Ϸ����
	
	void Handle_Set_Attack_Mode(packet& pkt);		//ѡ�񹥻�ģʽ
	void Handle_Select_Target(packet& pkt);			//ѡ��Ŀ��
	void Handle_Set_Orient(packet& pkt);
	void Handle_Spell_Start(packet& pkt);			//���ܿ�ʼ
	void Handle_Spell_Stop(packet& pkt);			//����ֹͣ
	void Handle_Resurrection(packet& pkt);			//����

	void Handle_Chat_Near(packet& pkt);				//�ͽ�����
	void _Handle_GM_Command(const char *str);		//GM��������

	void Handle_Gossip_Hello(packet& pkt);				//NPC����
	void Handle_Gossip_Select_Option(packet& pkt);		//ѡ������ѡ��

	void Handle_Taxi_Hello(packet& pkt);				//����Ա��������
	void Handle_Taxi_Select_Station(packet& pkt);		//ѡ���͵ص�
	void Handle_Syns_Mstime(packet& pkt);			//ͬ��ʱ��
	//void 
	void _Handle_QuestObject_Use(Unit *go);		//ʹ���������ʱ
	void Handle_QuestGiver_Status_Query(packet& pkt);	//����NPC״̬��ѯ	
	void Handle_QuestGiver_Hello(packet& pkt);			//������NPC���к�	
	void Handle_QuestGiver_Query_Quest(packet& pkt);	//��ѯ������ϸ
	void Handle_QuestGiver_Accept_Quest(packet& pkt);	//��������
	void Handle_QuestGiver_Remove_Quest(packet& pkt);	//��������
	void Handle_QuestGiver_Request_Reward(packet& pkt);	//����
	void Handle_QuestGiver_Complete_Quest(packet& pkt);	//�������
	void Handle_Questhelp_Get_CanAccept_List(packet& pkt);	//�ɽ�����
	void Handle_QuestUpdate_Use_Item(packet& pkt);		//�����Ʒ
	void Handle_QuestHelp_Complete(packet& pkt);		//�������̵ֽ̳�ֱ���������
	void Handle_QuestHelp_Update_Status(packet& pkt);	//�������̵ֽ̳������±����
	void Handle_QuestHelp_Query_Book(packet&pkt);		//������Ҳ�ѯ��������
	void Handle_QuestHelp_Talk_Option(packet&pkt);		//��������Ի�ѡ��ִ��

	//����
	void Handle_Instance_Enter(packet& pkt);
	void Handle_Instance_Exit(packet& pkt);
	
	void Handle_Instance_Next_State(packet &pkt);	//�ͻ��˷�������������һ״ָ̬��
	void Handle_Query_Quest_Status(packet& pkt);
	void Handle_Client_Update_Scened(packet& pkt);
	void Handle_Loot_Select(packet& pkt);

	void Hanlde_Client_Subscription(packet& pkt);
public:
	void Call_Gossip_Message(uint32 npc_guid,uint32 option_id,string &key); //������������
	void Call_Taxi_Station_List(uint32 npc_guid); //������������
	
	void Call_Force_Spell_CD(vector<uint32> &cd_info);
	void Call_Combat_State_Update(uint8 stat); //t֪ͨ����ս��״̬��������ս��״̬
	void Call_Peace_Mode_CD(uint8 cd);
	void Call_Operation_Failed(uint8 type,uint8 reason);
	void Call_Get_Lottery_Bonus(uint8 reslut);
	void Call_Mount_Evolve_Reslut(uint8 reason);

	bool DelGayFormInviteList(uint32 gay);			//�������б���ɾ��
	void RefreshBookQuest();
	
	bool IsCanDisMove(uint16 map_id);

private:
	Player *m_player;
};

#endif

