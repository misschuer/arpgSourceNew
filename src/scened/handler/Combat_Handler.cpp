#include "scened_app.h"
#include <object/SharedDef.h>
#include "scened_context.h"
#include "Player.h"
#include "Map.h"
#include "Creature.h"
#include "scened_scripts.h"
#include <shared/log_handler.h>
#include <object/OprateResult.h>

void ScenedContext::Call_Combat_State_Update(uint8 stat)
{
	packet *pkt;
	pack_combat_state_update(&pkt,stat);
	SendPacket(*pkt);
	external_protocol_free_packet(pkt);
}

void ScenedContext::Call_Peace_Mode_CD(uint8 cd)
{
	packet *pkt;
	pack_peace_mode_cd(&pkt,cd);
	SendPacket(*pkt);
	external_protocol_free_packet(pkt);
}

//���ù���ģʽ
void ScenedContext::Handle_Set_Attack_Mode(packet& pkt)		
{
	uint8 mode;
	uint64 reserve = 0;
	if (unpack_set_attack_mode(&pkt,&mode,&reserve))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_SET_ATTACK_MODE,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	if (mode>=MAX_ATTACK_MODE)
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_SET_ATTACK_MODE,ACCACK_PACKET_TYPE_DATA,"attack type error");
		return;
	}

	if(DoSetAttackModeCallback(m_player->GetMap(), m_player, mode) != 0)
	{
		m_player->SetAttackMode(mode);
		m_player->InvalidFriendlyCache();
	}
}


void ScenedContext::Handle_Select_Target(packet& pkt)			//ѡ��Ŀ��
{
	uint32 victimid;

	if (unpack_select_target(&pkt,&victimid))
	{
		WriteAttackPacker(GetAccount(),m_lguid,pkt.head->optcode,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}

	Map * curmap = m_player->GetMap();
	
	if(!curmap){
		//tea_perror("�Ҳ������GUID:%d ��ǰ��ͼ",m_player->GetGuid());
		return;
	}

	//tea_pdebug("Handle_Select_Target :%u",victimid);
	//m_player->SetTarget(NULL);	
	//Unit *unit = curmap->FindUnit(victimid);	
	//if (!unit){
	//	//tea_pdebug("�Ҳ������GUID:%d ѡ���Ŀ��GUID %d",m_player->GetGuid(),victimid);
	//	return;
	//}	
	//m_player->SetTarget(unit);

}

void ScenedContext::Handle_Set_Orient(packet& pkt) {
	uint16 angle;
	if (unpack_set_orient(&pkt, &angle)) {
		WriteAttackPacker(GetAccount(),m_lguid,MSG_SPELL_START,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}

	if (angle >= 360) {
		return;
	}

	m_player->SetOrientation(float(angle * M_PI / 180.0));
}

//-------------------------------------------------------------------------
//��ʼ����
void ScenedContext::Handle_Spell_Start(packet& pkt)			
{
	m_player->SetLastActionPktTime();
	uint32 spell_slot; 
	uint16 x,y;
	uint32 caster;
	uint32 target;
	if (unpack_spell_start(&pkt,&spell_slot,&x,&y,&caster,&target))
	{
		WriteAttackPacker(GetAccount(),m_lguid,MSG_SPELL_START,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}
	
	Map * curmap = m_player->GetMap();
	if(!curmap){
		tea_perror("�Ҳ������GUID:%d ��ǰ��ͼ",m_player->GetUIntGuid());
		return;
	}
	/* �ж��Ƿ���ʹ�ü��� */
	if (!m_player->canUseSkill()) {
		//tea_perror("two skills in interval %d", SKILL_INTERVAL);
		return;
	}
	Unit* targetUnit = curmap->FindUnit(target);
	uint32 spell_id = 0;
	//��lua�жϿ�ʼʩ��ǰ���߼�
	if(DoHandleSpellStart(m_player, spell_slot, x, y, targetUnit, spell_id))
	{
		//����ʼ����ǰ�账����߼��������Ƴ�����buff
		if(OnStartAttack(m_player->GetMap(), m_player))
		{
			m_player->SetTarget(targetUnit);
			//���ü����ͷż��
			m_player->SetLastSpellTime();
			//ʩ��
			m_player->CastSpell(spell_id, x, y);
		}
	}
}

//���ܽ���
void ScenedContext::Handle_Spell_Stop(packet& pkt)
{
	m_player->SetLastActionPktTime();
	m_player->SpellStop(true);
}

void ScenedContext::Handle_Resurrection(packet& pkt)
{
	uint8 type;
	uint64 reserve = 0;
	if (unpack_resurrection(&pkt,&type,&reserve))
	{
		WriteAttackPacker(GetAccount(),m_lguid,CMSG_RESURRECTION,ACCACK_PACKET_TYPE_UNPACK,"");
		return;
	}

	//�����
	if (m_player->isAlive())
	{
		tea_pwarn("[%s] isAlive Handle_Resurrection but!",m_player->GetName().c_str());
		return;
	}

	// ���ͳ�����ʹ�ø��
	string str = "";
	ScenedApp::g_app->call_player_do_something(m_player->GetSession()->GetGuid(), SCENED_APPD_USE_RESPAWN_ITEM, 0, str);


	////ԭ�ظ���
	////m_player->Respawn();
	////�������ԭ�ظ������͵���������
	//uint16 x = (uint16)m_player->GetPositionX(),y = (uint16)m_player->GetPositionY();	
	//uint32 map_id = m_player->GetMapId();
	//if(RESURRECTION_SPAWNPOINT == type && !m_player->GetMap()->GetMapTemp()->GetSpwanPoint(x,y,m_player->GetFaction()))
	//{
	//	map_id = ZHUCHENG_DITU_ID;	
	//	vector<uint16> vect;
	//	DoGetRespawnPos(vect);
	//	if(vect.size() == 2)
	//	{
	//		x = vect.at(0);
	//		y = vect.at(1);
	//		//Ϊ��ֹ��Ҹ������һ��,���һ��λ��
	//		auto *mt = MapTemplate::GetMapTempalte(map_id);
	//		if(mt)
	//		{					
	//			float nx,ny;
	//			for (uint8 i=1; i<10; i++)
	//			{
	//				MovementGenerator::RandomPos(nx,ny,float(x),float(y),float(irand(1,10000)/1000));
	//				if(mt->IsCanRun(uint16(nx),uint16(ny)))
	//				{
	//					x = uint16(nx);
	//					y = uint16(ny);
	//					break;
	//				}
	//			}
	//		}
	//	}
	//	else
	//	{
	//		x = ZHUCHENG_FUHUO_X;
	//		y = ZHUCHENG_FUHUO_Y;				
	//	}		
	//}	
	//DoRespawn(m_player,m_player->GetMap(),type,map_id,x,y);
}
