#include "logind_player.h"
#include "logind_context.h"
#include "map_manager.h"
#include "logind_script.h"
#include "logind_mongodb.h"
#include "logind_cache.h"
#include <object/SharedDef.h>
#include <shared/log_handler.h>
#include <shared/util.h>
#include <cstdlib>

logind_player::logind_player():PlayerBase(),m_session(0),m_mobile_session(0),m_zibao(false),m_auto_save_time(0)
{
}

logind_player::~logind_player()
{

}

void logind_player::InitNewPlayer(const std::string& name,uint8 faction,uint8 gender,uint8 head_id,uint8 hair_id,uint8 race,bool is_FCM)
{
	//������������
	SetName(name);
	SetOwner(GetGuid());
	SetGender(gender);
	SetRace(race);
	SetHead(head_id);
	SetLevel(BORN_LV);	
	SetHair(hair_id);	
	SetCreateTime((uint32)time(NULL));

	//��ʼ��������������
	/**
	this->SetDouble(PLAYER_EXPAND_INT_MONEY + MONEY_TYPE_SILVER * 2, 1000000);
	this->SetDouble(PLAYER_EXPAND_INT_MONEY + MONEY_TYPE_GOLD_INGOT * 2, 1000000);
	*/
	this->SetByte(PLAYER_FIELD_HOOK_BYTE0, 0, 1);
	this->SetByte(PLAYER_FIELD_HOOK_BYTE0, 1, 1);
	this->SetByte(PLAYER_FIELD_HOOK_BYTE0, 2, 1);
	this->SetByte(PLAYER_FIELD_HOOK_BYTE0, 3, 1);
	this->SetByte(PLAYER_FIELD_HOOK_BYTE1, 0, 1);
	this->SetByte(PLAYER_FIELD_HOOK_BYTE1, 1, 1);
	this->SetUInt16(PLAYER_FIELD_HOOK_SHORT, 0, 50);

	//���곯��
	//���ִ���΢���һ�£���Ȼ�൱��������
	// TODO: ����Ҫ��΢����
	const MapTemplate *mt = MapTemplate::GetMapTempalte(BORN_MAP);
	ASSERT(mt);		//���ִ嶼û�У���ƨ��
	uint16 born_x = BORN_X + irand(-8,8);
	uint16 born_y = BORN_Y + irand(-8,8);
	if(!mt->IsCanRun(born_x,born_y))
	{
		born_x = BORN_X;
		born_y = BORN_Y;
	}
	SetMapId(BORN_MAP);//��ͼ
	Relocate(born_x,born_y,BORN_OR);

	SetByte(PLAYER_FIELD_BYTES_3,3,ATTACK_MODE_PEACE);			//��ʼ����ģʽ	
	SetUInt32(PLAYER_FIELD_LEVEL, 1);							//�ȼ�	
	
	SetDouble(PLAYER_FIELD_MOVESPEED, INIT_MOVE_SPEED);			//�ƶ��ٶ�
	//Ĭ������ʱװ
	SetBit(PLAYER_EXPAND_INT_USE_FASHION,EQUIPMENT_TYPE_COAT);			//������
	SetBit(PLAYER_EXPAND_INT_USE_FASHION,EQUIPMENT_TYPE_MAIN_WEAPON);	//�·�
	//��lua��ʼ���������
	DoSetNewPlayerInfo(this);

	//������
	SetFCMLoginTime(is_FCM ? 0 : -1);
}

bool logind_player::InitDatabase()
{
	SetScenedFD(0);
	if (GetDouble(PLAYER_EXPAND_INT_MONEY + MONEY_TYPE_SILVER*2) > MAX_MONEY)
		SetDouble(PLAYER_EXPAND_INT_MONEY + MONEY_TYPE_SILVER*2, MAX_MONEY);

	//SetUInt32(PLAYER_FIELD_ANGER, 0);

	//У���µȼ�
	uint32 lv = GetLevel();
	char_level *level_info =  char_level_db[lv];
	if (!level_info)
	{
		tea_perror("player %s data invalid  player_level %u", guid().c_str(), lv);
		return false;
	}
	
	//���װ����ʶ
	for (uint16 index = PLAYER_FIELD_EQUIPMENT; index < PLAYER_FIELD_EQUIPMENT + EQUIPMENT_TYPE_MAX_POS; index++)
		SetUInt32(index, 0);

	return true;
}

//����������ۼ�����ʱ��
void logind_player::CalculFCMLogoutTime()
{
	//�Ƿ��������ֱ�Ӳ�����
	if (GetFCMLoginTime()==(uint32)-1)
		return;
	uint32 time_now = (uint32)time(NULL);
	//��ε�½-�ϴ��˳�+ԭ�ۼ��˳�ʱ�� = ���ۼ�����ʱ��
	uint32 cur_logouttime = time_now - GetLastLogoutTime() + GetFCMLogoutTime();
	//�ۼ��������Сʱ������ۼ����ߺ��ۼ�����
	if (cur_logouttime>=18000)
	{
		SetFCMLoginTime(0);
		cur_logouttime = 0;
	}
	SetFCMLogoutTime(cur_logouttime);
}

void logind_player::SendPacket(packet& pkt)
{
	if (GetSession())
		GetSession()->SendPacket(pkt);
	else
		tea_pdebug("��� ID��%s Session��������ͼ����",GetGuid().c_str());
}

