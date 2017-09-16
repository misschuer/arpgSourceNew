#include "scened_context.h"
#include "Player.h"
#include "Map.h"
#include "BuffManager.h"
#include <math.h>
#include <object/GameObject.h>
#include <object/OprateResult.h>
#include <shared/log_handler.h>
#include "scened_scripts.h"
#include <shared/chat_analysis.h>
#include <shared/offset_path.h>
#include "GridUpdateMask.h"

//�ͻ���Ҫ����
void ScenedContext::Handle_Teleport(packet& pkt)
{
	uint32 intGuid;
	if (unpack_teleport(&pkt, &intGuid))
	{
		WriteAttackPacker(GetAccount(), m_lguid, CMSG_TELEPORT, ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	if(!m_player->isCanMove())
	{
		tea_perror("��Ҳ����ƶ�,���봫��!");
		return;
	}

	Map* currentMap = m_player->GetMap();
	if (!currentMap) {
		return;
	}
	//�ж�����������͵�guid
	char ch[23];
	sprintf(ch, "%c%u", ObjectTypeUnit, intGuid);
	string teleGuid = ch;
	auto it = currentMap->m_gameobjects.find(teleGuid);
	if (it == currentMap->m_gameobjects.end()) {
		return;
	}
	GameObject* tele = it->second;
	if (!tele) {
		tea_perror("why gameobject will ocurr nullptr object");
		return;
	}
	//�ж��Ƿ��ںϷ���Χ�ڴ���
	uint16 currX = (uint16)tele->GetPositionX();
	uint16 currY = (uint16)tele->GetPositionY();
	if (!DoCheckTeleport(m_player, tele->GetEntry(), currX, currY)) {
		tea_perror("not on the teleport");
		return;
	}

	// ���崫��
	uint32 map_id = tele->GetToMapId();
	uint16 pos_x = (uint16)tele->GetToPositionX();
	uint16 pos_y = (uint16)tele->GetToPositionY();

	DOWorldMapTeleportScript(m_player,map_id,pos_x,pos_y);
}

void ScenedContext::Handle_Move_Stop(packet& pkt)
{
	uint32 guid;
	uint16 x,y;
	if(unpack_move_stop(&pkt,&guid,&x,&y))
	{
		WriteAttackPacker(GetAccount(),m_lguid,MSG_MOVE_STOP,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}

	const MapTemplate* map_temp =  m_player->GetMap()->GetMapTemp();
	//	ASSERT(map_temp);
	if (map_temp == NULL)
	{
		tea_perror("assert error: Handle_Unit_Move  ASSERT(map_temp)");
		Close(PLAYER_CLOSE_OPERTE_SCREND_ONE29,"");
		return;
	}

	auto dis = m_player->GetDistance(x,y);
	if (dis > g_Config.error_distance && !IsCanDisMove(m_player->GetMapId()))
	{
		tea_pdebug("ScenedContext::Handle_Unit_Move player [%s] g_Config.error_distance  = %f, from(%f,%f) newpos(%f,%f) dist:%f", m_player->GetGuid().c_str(), g_Config.error_distance, m_player->GetPositionX(),m_player->GetPositionY(),x,y,dis);
		m_player->StopMoving(true);
		return;
	}

	if(!map_temp->IsCanRun(x,y))
	{
		tea_pinfo("ScenedContext::Handle_Unit_Move sync pos, player[%s][%s], pos %d,%d", m_player->GetGuid().c_str(), m_player->GetName().c_str(), x, y);
		//������ܱ��ĸ������Ƿ�ɴ����ĸ����򶼲��ɴ������ǿ��ͬ��
		uint16 temp_posx = x;
		uint16 temp_posy = y;
		bool isRun = false;
		for (int i = 1; i < 8; i+=2)
		{
			temp_posx += MapTemplate::around[i][0];
			temp_posy += MapTemplate::around[i][1];
			if (map_temp->IsCanRun(temp_posx, temp_posy))
			{
				isRun = true;
				break;
			}			
		}
		if (!isRun)
		{
			m_player->StopMoving(x, y);
			return;
		}
	}

	//�ж�һ�����������һ��ֱ��return��
	int now_x = uint16(m_player->GetPositionX());
	int now_y = uint16(m_player->GetPositionY());
	if(now_x == x && now_y == y)
	{
		tea_pdebug("guid = %s, igron move_stop [%d,%d]",GetGuid().c_str(),x,y);
		return;
	}

	m_player->StopMoving(x, y);
	return;
}

//�����ƶ�
void ScenedContext::Handle_Unit_Move(packet& pkt)
{
	m_player->SetLastActionPktTime();
	uint32 guid;
	uint16 x,y;
	int8 *path;
	uint16 len_6;	
	
	if (unpack_unit_move(&pkt,&guid,&x,&y,&path , &len_6))
	{
		WriteAttackPacker(GetAccount(),m_lguid,MSG_UNIT_MOVE,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}

	if (m_player->GetBuffManager()->HasBuff(BUFF_JUMP_JUMP)) {
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//��ֹ�����쳣
	//������ż��
	if (len_6%2!=0 || len_6 == 0)
	{
		tea_perror("����������������ԣ�����Ϊż������ֹͣ��������������");
		return;
	}

	if (!m_player->isAlive()) {
		m_player->StopMoving(true);
		return;
	}

	//���൱����ת������
	static offset_path of_path;
	of_path.set_origin(x,y);
	of_path.add(len_6,path);
	vector<float> new_path;
	of_path.get(new_path);

	const MapTemplate* map_temp =  m_player->GetMap()->GetMapTemp();
	//	ASSERT(map_temp);
	if (map_temp == NULL)
	{
		tea_perror("assert error: Handle_Unit_Move  ASSERT(map_temp)");
		Close(PLAYER_CLOSE_OPERTE_SCREND_ONE30,"");
		return;
	}

	//ͬ������
	//TODO:��֤,��һ���Ƿ���Ժ��ԣ������������Ͽ�����һ����Զ�ǺͿͻ�����ͬ
	//ͣ�����ĵ�Ҳ��ͬ��ֻ��˭�ȵ�������⡣dis
	//����У�������;�ƶ��ٶȷ����ı��ָ���δ���
	auto dis = m_player->GetDistance(x,y);
	if (dis > g_Config.error_distance && !IsCanDisMove(m_player->GetMapId()))
	{
		tea_pdebug("player [%s] g_Config.error_distance  = %f, from(%f,%f) newpos(%f,%f) dist:%f", m_player->GetGuid().c_str(), g_Config.error_distance, m_player->GetPositionX(),m_player->GetPositionY(),path[0],path[1],dis);
		//m_player->MoveTo(m_player->GetPositionX(),m_player->GetPositionY());
		m_player->StopMoving(true);
		return;
	}
	
	//�Ƿ������ƶ�
	if (!m_player->isCanMove())
	{
		tea_pdebug("ScenedContext::Handle_Unit_Move can not move, player[%s]", m_player->GetGuid().c_str());
		m_player->StopMoving(true);
		return;
	}	

#if PLATFORM == PLATFORM_WINDOWS
	stringstream ss;
	for (int i = 0; i < (int)new_path.size(); i += 2)
	{
		ss << new_path[i] << "," << new_path[i+1] << ";";
	}

	tea_pdebug("Handle_Unit_Move player(%s, %u)(%f,%f), path (%s)", m_player->GetGuid().c_str(), m_player->GetMapId(),
		m_player->GetPositionX(),m_player->GetPositionY(), ss.str().c_str());
#endif

	if (!map_temp->IsCanRun(x,y,new_path))
	{
		tea_pdebug("ScenedContext::Handle_Unit_Move path can not run, player[%s]", m_player->GetGuid().c_str());
		m_player->StopMoving(true);
		return;
	}

	//�����ƶ�ǰ��Ҫ������߼��������Ƴ�����buff
	if(!OnMoveTo(m_player->GetMap(), m_player))
		return;

	m_player->SetPosition(x,y);
	m_player->MoveTo(new_path.size(),&new_path[0]);
	//m_player->MoveTo(len_6-2,path+2);

//	ASSERT(status_ == STATUS_LOGGEDIN);
	if (status_ != STATUS_LOGGEDIN)
	{
		tea_perror("assert error: Handle_Unit_Move  ASSERT(status_ == STATUS_LOGGEDIN)");
		Close(PLAYER_CLOSE_OPERTE_SCREND_ONE31,"");
		return;
	}
}

//�ͽ�����
void ScenedContext::Handle_Chat_Near(packet& pkt)
{
	WriteAttackPacker(GetAccount(),m_lguid,pkt.head->optcode,ACCACK_PACKET_TYPE_DISCARD,"");
	return;
}

//��Ծ
void ScenedContext::Handle_Jump(packet& pkt)
{
	WriteAttackPacker(GetAccount(),m_lguid,pkt.head->optcode,ACCACK_PACKET_TYPE_DISCARD,"");
	return; //��������
}

void ScenedContext::On_Teleport_OK(uint32 fd, uint32 mapid, uint32 instanceid, float x, float y)
{
	ASSERT(m_player == NULL);
	//if (m_player != NULL)
	//{
	//	tea_perror("assert error: On_Teleport_OK ASSERT(m_player == NULL)");
	//	Close();
	//	return;
	//}
	ScenedApp::g_app->ChangeSessionID(this, fd);
	m_lguid = guid();
	//������Ҷ���
	m_player = new Player();
	Map *instance = Map::FindInstance(instanceid, mapid);
	//ϵ�е�ͼ�ڴ��ͣ�ʵ���ڵ��Ǵ��ӵ�ͼδ������
	ASSERT(instance);

	SetTeleportInfo(0, 0, 0, 0, GetTeleportGuid());
	SetMapId(mapid);
	SetMapLineNo(instance->GetLineNo());
	SetPosition(x, y);
	//�ı�״̬
	m_player->Create(this);
	SetStatus(STATUS_LOGGEDIN);
	//������¼��������ϵİ����ͻ���
	Call_join_or_leave_server(m_delegate_sendpkt, 0, SERVER_TYPE_SCENED, getpid(), ScenedApp::g_app->Get_Connection_ID(), uint32(time(nullptr)));
	instance->JoinPlayer(m_player);	
	//������±��ʼ������id�Ϳ������
	instance->InitWaridAndKuafuType(this);
	//������������ (�½���ɫ����Ҫ����)
	if (this->GetForce() == 0) {
		ScenedApp::g_app->call_recalculate(guid());
	}

	//// ����ð���������Ҫ��¼�뿪����Ϣ
	//if (!DoIsRiskMap(mapid)) {
	//	// ��ð�յ�ͼ���������ۼ�
	//	if (m_player->GetSession()->GetPickRiskRewardFlag() == 1) {
	//		m_player->GetSession()->SetPickRiskRewardFlag(0);
	//		m_player->GetSession()->SetLastLeaveRiskTime((uint32)time(NULL));
	//	}
	//} else {
	//	// û������Ĳ�����ȡ
	//	if(m_player->GetSession()->GetPickRiskRewardFlag() == 0) {
	//		DoPickRiskReward(m_player);
	//		m_player->GetSession()->SetLastLeaveRiskTime((uint32)time(NULL));
	//		m_player->GetSession()->SetPickRiskRewardFlag(1);
	//	}
	//}

	tea_pdebug("ScenedContext::On_Teleport_OK %s",m_player->GetGuid().c_str());
}

//����ʦʹ��
void ScenedContext::Teleport(float to_x,float to_y,int to_mapid, const string &teleport_id, uint32 line_no,uint32 instance_id)
{
	tea_pdebug("player %s teleport to %d %u %f %f", GetGuid().c_str(), to_mapid, instance_id, to_x, to_y);
	if(status_ != STATUS_LOGGEDIN)
	{
		tea_pwarn("ScenedContext::Teleport status_ != STATUS_LOGGEDIN %s %u %u", guid().c_str(), GetMapId(), to_mapid);
		//Call_operation_failed(m_delegate_sendpkt,OPERTE_TYPE_CLOSE,PLAYER_CLOSE_OPERTE_SCREND_ONE32,"");
		//Close();���ﻹ�ǲ�Ҫclose��
		return;
	}

	auto m = m_player->GetMap();
	//������δ��ȷ�ļ����ͼ�����ʱ�䴫��Ҳ��ʧ�ܵ�
	if (!m || !MapTemplate::GetMapTempalte(m->GetMapId()))
	{
		tea_perror("!m_player->GetMap()[%p] || !MapTemplate::GetMapTempalte(m_player->GetMap()->GetMapId()[%d])",m_player->GetMap(),
			m_player->GetMap()?m_player->GetMap()->GetMapId():0);	
		Close(PLAYER_CLOSE_OPERTE_SCREND_ONE33,"");
		return;
	}
	//��ͼ�ڴ���
	if(to_mapid == m->GetMapId() && teleport_id == m->GetGeneralID() && (line_no == 0 || line_no == m->GetLineNo()))
	{
		const MapTemplate *mt = MapTemplate::GetMapTempalte(to_mapid);
		if (!mt || mt->IsNotValidPos(to_x,to_y))
		{
			tea_perror("!mt || mt->IsNotValidPos(to_x,to_y) %f,%f,%u,%u",to_x,to_y,to_mapid,instance_id);
			return;
		}
		m_player->SetPosition(to_x,to_y);
		m_player->StopMoving(true);			//ͬ�����ͻ���
		m_player->SetHealth(m_player->GetHealth());
		return;
	}

	//---------------------------------------------------------------------
	//��ʽ�Ŀ�ʼ����
	WriteMap(GetAccount(), GetGuid(), GetLevel(), GetMapId(), to_mapid);
	//�����ͼID,��Ҫǰ���ĵ�ͼ������д���±꣬������
	SetTeleportInfo(to_mapid, to_x, to_y, line_no, teleport_id);
	//ͬ����������
	m_player->SyncCacheData();
	//���õ�¼״̬
	SetStatus(STATUS_DELETE);
}

void ScenedContext::LeaveScened()
{
	//�ͷ�unit begin
	ASSERT(m_player);
	m_player->GetMap()->LeavePlayer(m_player);
	//�ͷ�ǰͬ��������
	m_player->SyncCacheData();
	m_player->SyncUnitToPlayerData();
	safe_delete(m_player);
	//�ͷ�unit end

	//ȡ�������¼�
	after_update(nullptr);
	//�����뿪�����������ͻ���
	Call_join_or_leave_server(m_delegate_sendpkt, 1, SERVER_TYPE_SCENED, getpid(), ScenedApp::g_app->Get_Connection_ID(), uint32(time(nullptr)));
	//fd��Ϊ0
	ScenedApp::g_app->ChangeSessionID(this, 0);
}

void ScenedContext::Hanlde_Client_Subscription(packet& pkt)
{
	uint32 guid;
	if(packet_read(&pkt,(char*)&guid,sizeof(guid)))
	{
		WriteAttackPacker(GetAccount(),m_lguid,MSG_CLIENTSUBSCRIPTION,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}

	if(!m_player || !m_player->GetMap())
		return;

	auto* unit = m_player->GetMap()->FindUnit(guid);
	if(!unit)
	{
		tea_pwarn("Hanlde_Client_Subscription guid:%u unfound!",guid);
		return;
	}

	UpdateMask mask;
	UpdateMask& oldmask = *(gGridUpdateMask.client_subscription_mask_);
	for (int i = 0; i < oldmask.GetCount();i++)	
		if(unit->GetUInt32(i) && oldmask.GetBit(i))
			mask.SetBit(i);
	
	auto *ret_pkt = ObjMgr.GridMallocByteArray();
	ret_pkt->writeShort(MSG_CLIENTSUBSCRIPTION);
	ret_pkt->writeUnsignedInt(guid);
	mask.WriteTo(*ret_pkt);

	for (int i = 0; i < oldmask.GetCount();i++)	
		if(mask.GetBit(i))
			*ret_pkt << unit->GetUInt32(i);
	ScenedApp::g_app->SendPacket(GetFD(),ret_pkt);
	ObjMgr.GridFreeByteArray(ret_pkt);
}
