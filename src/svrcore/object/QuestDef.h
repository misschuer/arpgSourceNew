#ifndef _QUEST_DEF_H_
#define _QUEST_DEF_H_

#include <comm/common_stl.h>
#include <shared/storage_strus.h>
#include <object/SharedDef.h>

//�Ƿ��Զ�ʧ��
static inline bool IsAutoFailOff(quest_template const *quest) 
{
	return (quest->quest_flags & QUEST_FLAGS_AUTO_FAIL_OFF) != 0;
}

//�Ƿ��Զ��������
static inline bool IsAutoComplete(quest_template const *quest) 
{
	ASSERT(quest);
#if 0
	return quest->method ? false : true;
#else
	return (quest->quest_flags & QUEST_FLAGS_AUTO_COMPLETE) != 0;
#endif	
}

//�Ƿ�ÿ������
static inline bool IsDaily(quest_template const *quest)
{
	ASSERT(quest);
	return (quest->quest_flags & QUEST_FLAGS_DAILY) != 0 ;
}

//�Ƿ��Զ�����
static inline bool IsAutoAccept(quest_template const *quest)
{
	ASSERT(quest);
	return (quest->quest_flags & QUEST_FLAGS_AUTO_ACCEPT) != 0;
}

//�Ƿ��ֶ����
static inline bool IsManualComplete(quest_template const *quest)
{
	ASSERT(quest);
	return (quest->quest_flags & QUEST_FLAGS_MANUAL) != 0;
}

//�Ƿ��Զ�����
static inline bool IsAutoReward(quest_template const *quest)
{
	ASSERT(quest);
	return (quest->quest_flags & QUEST_FLAGS_AUTO_REWARDED) != 0 ;
}

//�ύ�����ʱ���Ƿ�У���ύ����npc�������������������ҪУ��
//1������������У�� 2���������񡢵����й�ѡ����ҪУ���־
static inline bool IsCheckCommitNPC(quest_template const *quest)
{
	ASSERT(quest);
	return !(quest->quest_type != QUEST_TYPE_MAIN || (quest->quest_type == QUEST_TYPE_MAIN && (quest->quest_flags & QUEST_FLAGS_COMMIT_NOT_NEED_NPC)!=0 ));
}

//��������ʱ�Ƿ���ҪУ���������npc
static inline bool IsCheckAcceptNPC(quest_template const *quest)
{
	ASSERT(quest);
	return !(quest->quest_type != QUEST_TYPE_MAIN || (quest->quest_type == QUEST_TYPE_MAIN && (quest->quest_flags & QUEST_FLAGS_ACCEPT_NOT_NEED_NPC)!=0 ));
}

//�Ƿ�ɷ���
static inline bool CanRemove(quest_template const *quest) 
{
	ASSERT(quest);
	return (quest->quest_flags & QUEST_FLAGS_CANREMOVE) != 0;
}

static inline bool HasFlag(quest_template const *quest,uint32 flags)
{
	ASSERT(quest);
	return (quest->special_flags & flags) != 0 ;
}

//����״̬
struct QuestStatusData
{
	QuestStatusData()
		: m_status(QUEST_STATUS_NONE),m_rewarded(false),
		m_explored(false), m_timer(0), uState(QUEST_NEW)
	{
		memset(m_itemcount, 0, QUEST_OBJECTIVES_COUNT * sizeof(uint32));
		memset(m_creatureOrGOcount, 0, QUEST_OBJECTIVES_COUNT * sizeof(uint32));
	}

	uint32 quest_id;			//����id
	QuestStatus m_status;		//����״̬
	bool m_rewarded;			//�Ƿ�ȡ��������
	bool m_explored;			//�Ƿ���̽��
	uint32 m_timer;
	QuestUpdateState uState;	//������²���

	uint32 m_itemcount[ QUEST_OBJECTIVES_COUNT ];			//��Ʒ���� ����(һ�����������Դ�������Ʒ)
	uint32 m_creatureOrGOcount[ QUEST_OBJECTIVES_COUNT ];	//ɱ����������ƻ���ͼ����(ͬ��)
};

typedef std::map<uint32, QuestStatusData> QuestStatusMap;


#endif

