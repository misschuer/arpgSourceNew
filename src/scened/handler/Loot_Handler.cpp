#include "scened_context.h"
#include "Player.h"
#include "Map.h"
#include "Creature.h"
#include "GameObject.h"
#include "LootManager.h"
#include "scened_scripts.h"
#include <object/OprateResult.h>
#include <shared/log_handler.h>
#include "BuffManager.h"

//ʹ����Ϸ����
void ScenedContext::Handle_Use_Gameobject(packet& pkt)
{
	uint32 target;
	if (unpack_use_gameobject(&pkt, &target))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_USE_GAMEOBJECT,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	if (!m_player->isAlive())	//������˾Ͳ�Ҫʹ����Ϸ����
	{
		Call_Operation_Failed(OPRATE_TYPE_USE_GAMEOBJECT, USE_GAMEOBJECT_FAIL);
		tea_perror(" player is dead ,do not handle use gameobject ");
		return;
	}
	
	auto temp_target = (target == 0 ? m_player->GetTargetGuid() : target);
	if (!temp_target)
	{
		tea_perror("����Ҫһ��Ŀ��");
		return;
	}

 	GameObject *tele = (GameObject *)(m_player->GetMap()->FindWorldObject(temp_target));
	if (!tele) {
		tea_perror("you need a target");
		return;
	}
	
	// �п��ܴ��������һ������
	if(!tele->isAlive()) {
		return;
	}

	if (!tele || tele->IsGarbage())
	{
		Call_Operation_Failed(OPRATE_TYPE_USE_GAMEOBJECT, USE_GAMEOBJECT_FAIL);
		return;
	}
	if((tele->NeedUseMode() || tele->IsGEAR()) && !m_player->CanUseGameObject())
	{
		Call_Operation_Failed(OPRATE_TYPE_USE_GAMEOBJECT, USE_GAMEOBJECT_TOO_FAST);
		return;
	}
	m_player->SetLastActionPktTime();
	if (!m_player->IsReasonableDistancePos(tele))
	{	
		Call_Operation_Failed(OPRATE_TYPE_INTERACTION,INTERACTION_TOO_FAR);
		tea_perror("ʹ��GAMEOBJ����̫Զ ��ǰ���꣨%f,%f��",m_player->GetPositionX(),m_player->GetPositionY());
		return;
	}

	//��������Ա�ʹ��
	if (!tele->CanUse())
	{
		tea_perror("player[%s],gameobject[%s],entry[%u] can't use!",
			m_player->GetGuid().c_str(),tele->GetGuid().c_str(),tele->GetEntry());
		return;
	}

	//������
	if (tele->IsGEAR())
	{
		tele->UseGear(m_player);
	}
	else if (tele->IsTeleteport()) //���͵�
	{
		return;
		//û�����ƴ��͵�buff����ͼ�ѿ������Ҳ���pvp״̬
		//if (m_player->isCanTeleport() && !m_player->GetPVPstate())
		//{
		//	Teleport(tele->GetToPositionX(),tele->GetToPositionY(),tele->GetToMapId(),"");
		//}
	}
	else if(tele->IsQuestGO())		//����
	{
		_Handle_QuestObject_Use(tele);	
	}	
	
	//�����Ҫ���ű�,���صĴ�����̲�̫һ��
	if (tele->IsExecScript() && !tele->IsGEAR())
	{
		uint32 entry = tele->GetEntry();
		if(DoBeforUseGameObjectScript(m_player,tele,entry) == 0)
			return;
		DoGameObjectScript(m_player,tele,entry);
		return;
	}
	// ��Ҫ��������creature��Onkilled����
	if (tele->IsReborn()) {
		tele->OnKilled();
	}
	//�����������ʹ�õ�������ʧ,�������Լ��е�����������Ҫ����
	else if (!tele->IsForeverUse() && !tele->IsGEAR() && !tele->CanLoot()) {
		tea_pdebug("ɾ��gameobject id = %u playerguid = %s  playername = %s", tele->GetEntry(), m_player->GetGuid().c_str(), m_player->GetName().c_str());
		tele->GetMap()->m_go_dynamic.push_back(std::make_pair(-1, tele->GetGuid()));
		tele->SetGarbage(true);
	}	
	
}


