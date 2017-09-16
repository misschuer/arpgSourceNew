#include "PlayerBase.h"
#include "shared/lua_helper.h"

//////////////////////////////////////////////////////////////////////////
//��ʼ��
PlayerBase::PlayerBase(core_obj::SyncMode _m):BinLogObject(_m)
{	
}

PlayerBase::~PlayerBase()
{
}

//����ʱװ
void PlayerBase::SetUseFashion(uint16 pos)
{
	if(GetBit(PLAYER_EXPAND_INT_USE_FASHION, pos))
	{
		UnSetBit(PLAYER_EXPAND_INT_USE_FASHION, pos);
	}
	else
	{
		SetBit(PLAYER_EXPAND_INT_USE_FASHION, pos);
	}
}
