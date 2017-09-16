#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Unit.h"

class LootManager;

//typedef UNORDERED_MAP<uint32,uint32> GAMEOBJ_GUID_MAP;
class GameObject : public Unit
{
public:
    GameObject();
    virtual ~GameObject();
    bool Create(const string &lguid, uint32 entry);
	void UpdateLiveStatus(uint32 diff);
	void SetSpellCD(uint32 id){};
	uint32 m_respawn_time;							//����ʱ��
private:
	bool m_is_garbage;
public:
	bool IsGarbage(){return m_is_garbage;}
	void SetGarbage(bool value){m_is_garbage = value;}
public:
    bool IsTeleteport()
    {
        return GetBit(GO_FIELD_FLAGS, GO_FLAG_TELE);
    }
    bool IsQuestGO()
    {
        return GetBit(GO_FIELD_FLAGS, GO_FLAG_QUEST);
    }

    bool CanUse()
    {
        return !GetBit(GO_FIELD_FLAGS, GO_FLAG_UNUSE);
    }
    bool CanLoot()
    {
        return GetBit(GO_FIELD_FLAGS, GO_FLAG_LOOT);
    }

	//��ν�Ķ�̬����ˢ���ö����һ��ʱ�����Լ���ʧ
    bool IsDynamic()
    {
        return GetBit(GO_FIELD_FLAGS, GO_FLAG_DYNAMIC);
    }
    void SetDynamic()
    {
        GetBit(GO_FIELD_FLAGS, GO_FLAG_DYNAMIC);
    }

	//��Ҫ����
	bool NeedUseMode()
	{
		return GetBit(GO_FIELD_FLAGS, GO_FLAG_USEMODE);
	}

	//ʹ�ú��Ƿ����ʧ�������Ļ��������Ӻ����ˢ
    bool IsForeverUse()
    {
        return GetBit(GO_FIELD_FLAGS, GO_FLAG_FOREVER);
    }

	// �Ƿ������
	bool IsReborn()
	{
		return GetBit(GO_FIELD_FLAGS, GO_FLAG_REBORN);
	}

	//�Ƿ����
	bool IsGEAR()
	{
		return GetBit(GO_FIELD_FLAGS, GO_FLAG_GEAR);
	}

	void UseGear(Player *player); //��������

    void LootSelect(Player *player);//���ʰȡ��Ʒ//, uint32 entry, uint8 count);

    //�Ƿ�ʹ�ýű�
    bool IsExecScript()
    {
        return GetBit(GO_FIELD_FLAGS, GO_FLAG_SCRIPT);
    }
	//ʰ���Ƿ���Ҫ����
	bool IsGetItemNotice()
	{
		return GetBit(GO_FIELD_FLAGS, GO_FLAG_GET_ITEM_NOTICE);
	}
	//����ս��Ʒ�Ĺֵ�ID
	const string &GetLootCreateBy() const
	{
		return GetStr(GO_STRING_FIELD_CREATED_BY);
	}

	void SetLootCreateBy(const string &val)
	{
		SetStr(GO_STRING_FIELD_CREATED_BY,val);
	}

    //////////////////////////////////////////////////////////////////////////
    //for ���͵�
    //Ŀ���ͼID
    uint32 GetToMapId()
    {
        return GetUInt32(GO_TELETEPORTER_TO_MAPID);
    }
    void SetToMapId(uint32 id)
    {
        SetUInt32(GO_TELETEPORTER_TO_MAPID, id);
    }

    //Ŀ��X����
    float GetToPositionX()
    {
        return GetFloat(GO_TELETEPORTER_TO_X);
    }
    void SetToPositionX(float x)
    {
        SetFloat(GO_TELETEPORTER_TO_X, x);
    }

    //Ŀ��Y����
    float GetToPositionY()
    {
        return GetFloat(GO_TELETEPORTER_TO_Y);
    }
    void SetToPositionY(float y)
    {
        SetFloat(GO_TELETEPORTER_TO_Y, y);
    }

    //////////////////////////////////////////////////////////////////////////
    //for ����
    uint32 GetQuestID_0()
    {
        return GetUInt32(GO_QUEST_ID_0);
    }
    uint32 GetQuestID_1()
    {
        return GetUInt32(GO_QUEST_ID_1);
    }
    uint32 GetQuestID_2()
    {
        return GetUInt32(GO_QUEST_ID_2);
    }
    uint32 GetQuestID_3()
    {
        return GetUInt32(GO_QUEST_ID_3);
    }
	//����״̬
	uint32 GetGearStatus()
	{
		return (GO_GEAR_STATUS_TYPE)GetUInt32(GO_GEAR_STATUS);
	}
	void SetGearStatus(uint32 val)
	{
		SetUInt32(GO_GEAR_STATUS, val);
	}

	//ʹ��֮�󣬹㲥������
	bool BroadcastAction(uint32 player_id);
};


#endif

