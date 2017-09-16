#include "policed_app.h"
#include "policed_object_manager.h"
#include "policed_context.h"
#include "log_file_operate.h"
#include "policed_mongodb.h"
#include "game_police.h"
#include <core_obj/SyncEventRecorder.h>
#include "platform_post.h"

PolicedObjectManager::PolicedObjectManager(SvrCoreAppImpl *app):SvrObjectManager(app),m_null_player(nullptr)
{
	//�����������Ϊ�˱����ȽϷ���
	indexer_.CreateIndex(REGEX_PLAYER);
	indexer_.CreateIndex(REGEX_LIMIT);
	m_null_player = new PolicedContext(PolicedApp::g_app);
}

PolicedObjectManager::~PolicedObjectManager()
{
	safe_delete(m_null_player);
}

//���󹤳�
GuidObject *PolicedObjectManager::ObjectFactor(const string &guid)
{
	BinLogObject *ptr = NULL;
	auto t = GuidManager::GetPrefix(guid);
	switch (t)
	{
	case ObjectTypePlayer:
		ptr = new PolicedContext(PolicedApp::g_app);
		ptr->after_update(std::bind(&PolicedObjectManager::OnAfterPlayerDataUpdate,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
		break;
	default:
		ptr = PolicedApp::g_app->CreateGlobalValues(this, guid);
		if(!ptr)
		{
			ptr = new BinLogObject;
		}
		break;
	}
	return ptr;
}

GuidObject* PolicedObjectManager::CreateObject(string guid)
{
	tea_pdebug("PolicedObjectManager::CreateObject guid = '%s' ", guid.c_str());
	BinLogObject *ptr = dynamic_cast<BinLogObject*>(ObjectFactor(guid));
	ASSERT(ptr);	
	ptr->guid(guid);

	if(GuidManager::GetPrefix(guid) == ObjectTypePlayer)
	{
		//��ʼ��һ�·�����id
		dynamic_cast<PolicedContext*>(ptr)->SetServerId();
	}

	AttachObject(ptr);
	return ptr;
}

void PolicedObjectManager::ReleaseObject(string guid)
{
	tea_pdebug("PolicedObjectManager::ReleaseObject guid = '%s' ", guid.c_str());
	BinLogObject *binlog = dynamic_cast<BinLogObject *>(Get(guid));
	if (binlog)
	{
		DelOwnerMap(binlog->GetOwner(), binlog);
	}

	return SvrObjectManager::ReleaseObject(guid);
}

//��������ֱ�ӵ����ķ�
void PolicedObjectManager::Send(uint32_t connid,ByteArray& bytes)
{
	bytes.position(0);	
	WorldPacket pkt(0);
	WriteTo(bytes, pkt.GetPkt());
	PolicedApp::g_app->SendToCentd(pkt);
}

PolicedContext *PolicedObjectManager::FindPlayer(const string& guid)
{
	if(guid.empty())
		return m_null_player;
	return dynamic_cast<PolicedContext*>(Get(guid));
}

//�������е����
void PolicedObjectManager::ForEachPlayer(std::function<void(PolicedContext*)> func)
{
	auto *idx = indexer().get(REGEX_PLAYER);	
	for (auto it = idx->begin();it != idx->end();++it)	
		func(dynamic_cast<PolicedContext*>(it->second));
}

void PolicedObjectManager::OnAfterPlayerDataUpdate(core_obj::SyncEventRecorder *data,int flags,UpdateMask& mask,UpdateMask& str_mask)
{
	PolicedContext *player = dynamic_cast<PolicedContext*>(data);
	if(!player)
		return;
	bool is_new = (flags & core_obj::SyncEventRecorder::OBJ_OPT_NEW) != 0;

	//����Ǵ�����,ֻҪ��3���ӵľͷ�
	//���°�Ҫ�ж��ǲ�������ʱ����һ���±귢������
	if(mask.GetBit(PLAYER_FIELD_ONLINE_TIME) || is_new)
	{
		uint32 onlineTime =  player->GetOnlineTime();
		if (onlineTime != 3)
		{
			return;
		}
		account_info *a_info = PolicedApp::g_app->LoadAccountInfo(player->GetAccount().c_str(), "");
		for (auto it:PolicedApp::g_app->m_platform_post)
		{
			it->Online3MinsPost(a_info, player);
		}
	}
}