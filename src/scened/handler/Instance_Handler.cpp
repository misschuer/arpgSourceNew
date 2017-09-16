#include "scened_context.h"
#include <shared/storage_loader.h>
#include "Player.h"
#include "Map.h"
#include "scened_scripts.h"
#include <shared/log_handler.h>

//���븱��
void ScenedContext::Handle_Instance_Enter(packet& pkt)
{
	uint32 map_id ;
	if (unpack_instance_enter(&pkt,&map_id))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_INSTANCE_ENTER,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	if (m_player->IsInTheInstanceMap())//MapTemplate::GetMapTempalte(m_player->GetMapId())->IsInstance())
	{
		tea_perror("Handle_Instance_Enter�����ڸ���������븱��");
		return;
	}
	if (!m_player->isAlive()) //������˾Ͳ��÷�Э��
	{
		tea_perror("error : player is dead!!!!!!!!!");
		return;
	}

	DoInstancEnter(m_player->GetMap(), m_player, m_player->GetMapId(), map_id);

}

//�뿪����
void ScenedContext::Handle_Instance_Exit(packet& pkt)
{
	uint32 reserve;
	if(unpack_instance_exit(&pkt, &reserve))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_INSTANCE_EXIT,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	// ���ڶ��ص������� �����ж���, ֻҪ�������Ǽ�
	//ս��״̬�ж�,���ǿ����ҵĻ��Ͳ���Ҫ����
	//if (!m_player->IsInTheInstanceMap() && !IsKuafuPlayer())
	//{
	//	tea_pdebug("���ڸ�����ͼ����ô�뿪����");
	//	return;
	//}
	//���ǿ����ҵĻ��Ͳ���Ҫ����
	if(m_player->GetPVPstate() && !IsKuafuPlayer())
	{
		tea_pdebug("PVP״̬�����뿪����");
		return;
	}
	if (DoPlayerExitInstance(m_player->GetMap(), m_player, reserve) != 0)
	{
		SpecifyTeleportOrigin(m_player->GetMap(), m_player);
		((InstanceMap*)(m_player->GetMap()))->ExitInstance(m_player);	
	}	
}

void ScenedContext::Handle_Instance_Next_State(packet &pkt)
{
	uint16 level = 0;
	uint32 param = 0;
	if (unpack_instance_next_state(&pkt,&level,&param))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_INSTANCE_NEXT_STATE,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	if (!m_player->IsInTheInstanceMap())
	{
		tea_pdebug("���ڸ�����ͼ����ô���븱����һ״̬");
		return;
	}
	//ս��״̬�ж�
	if(m_player->GetPVPstate())
	{
		tea_pdebug("PVP״̬������븱����һ״̬");
		return;
	}
	OnInstanceTryToNextState(m_player, m_player->GetMap(),level,param);
}

