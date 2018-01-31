#include "svrcore-internal.h"
#include "GameObject.h"
#include <shared/storage_loader.h>

//////////////////////////////////////////////////////////////////////////
//for GameObject
//uint32 GameObject::m_new_gameobj_id = 0;
//GAMEOBJ_GUID_MAP GameObject::GameObjGuidMap;

GameObject::GameObject():m_is_garbage(false)
{
}

GameObject::~GameObject()
{

}

bool GameObject::Create(const string &lguid, uint32 entry)
{
	//���͵�
	const gameobject_template* tpl = gameobject_template_db[entry];
	if(!tpl) return false;

	Unit::_Create(lguid, entry);
	SetTypeId(TYPEID_GAMEOBJECT);
	//��������
	SetName(tpl->name);
	SetUInt32(GO_FIELD_FLAGS,tpl->go_flag);
	m_respawn_time = 5000;

	return true;
}

void GameObject::UpdateLiveStatus(uint32 diff)
{
	//������ʱ��
	if(isAlive())
		return;
	m_live_timer.Update(diff);

	//��ʱ��δ��
	if (!m_live_timer.Passed())
		return;

	//ʬ��״̬�±���Ϊ����״̬
	if(GetDeathState() == DEATH_STATE_CORPSE) {
		SetDeathState(DEATH_STATE_DEAD);
		m_live_timer.Reset(m_respawn_time);
	}
	else if(GetDeathState() == DEATH_STATE_DEAD)	//����
	{
		Respawn();
		m_live_timer.Reset(0);
	}
}
