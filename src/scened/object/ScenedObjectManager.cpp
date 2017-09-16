#include "scened_app.h"
#include "ScenedObjectManager.h"
#include "Player.h"
#include "Map.h"
#include "scened_context.h"

ScenedObjectManager::ScenedObjectManager(SvrCoreAppImpl *app):SvrObjectManager(app)
{	
	//�����������ҵ�����
	indexer_.CreateIndex(REGEX_PLAYER);
	m_compress_tool.set_send_delegate([&](uint32_t cid,ByteArray *pkt){
		ScenedApp::g_app->SendPacket(cid,pkt);
		Free(*pkt);
	});
}

ScenedObjectManager::~ScenedObjectManager()
{

}

void ScenedObjectManager::Update()
{
	SvrObjectManager::Update();
}

//���󹤳�
GuidObject *ScenedObjectManager::ObjectFactor(const string &guid)
{
	GuidObject *ptr = NULL;
	switch (GuidManager::GetPrefix(guid))
	{
	case ObjectTypePlayer:
		{
			ptr = new ScenedContext(0, ScenedApp::g_app);
		}
		break;
	case ObjectTypeUnit:
		ASSERT(false);
		break;
	default:
		ptr = ScenedApp::g_app->CreateGlobalValues(this, guid);
		if(!ptr)
			ptr = new BinLogObject;
		break;
	}
	return ptr;
}

GuidObject *ScenedObjectManager::CreateObject(string guid)
{
	tea_pdebug("ScenedObjectManager::CreateObject guid = '%s' ", guid.c_str());
	GuidObject *ptr = ObjectFactor(guid);
	ASSERT(ptr);	
	ptr->guid(guid);
	AttachObject(ptr);
	return ptr;
}

void ScenedObjectManager::ReleaseObject(string guid)
{
	BinLogObject *binlog = dynamic_cast<BinLogObject *>(Get(guid));
	if (binlog)
	{
		tea_pdebug("ScenedObjectManager::ReleaseObject guid = '%s' ", guid.c_str());
		DelOwnerMap(binlog->GetOwner(), binlog);
		if (binlog->GetOwner() == binlog->guid()) {
			ScenedContext *session = dynamic_cast<ScenedContext *>(binlog);
			if (session) {
				ASSERT(!session->GetPlayer());
			}
		}
	}

	SvrObjectManager::ReleaseObject(guid);
}

//��������ֱ�ӵ����ķ�
void ScenedObjectManager::Send(uint32_t connid,ByteArray& bytes)
{
	bytes.position(0);
	WorldPacket pkt(0);
	WriteTo(bytes,pkt.GetPkt());
	ScenedApp::SendToCentd(pkt);
}

//�����Ҳ�����־�����ķ�
void ScenedObjectManager::SendPlayerBinlog(ScenedContext *player)
{
	//�ӿ�϶������������
	ByteArray& bytes = MallocByteArray(opt_update_data_);
	player->WriteUpdateBlock(bytes);
	//�������ݰ�
	if(bytes.length() > sizeof(OptionID))
		CallUpdateObject(connection_id(),bytes);
	//�ͷ����ݰ�
	Free(bytes);
	player->Clear();
}

//ȡ�����unit
Player *ScenedObjectManager::FindPlayer(string guid)
{
	//����������Ҫ��֤һ���Ƿ���ڻỰ����
	ASSERT(GuidManager::GetPrefix(guid) == ObjectTypePlayer);
	
	ScenedContext *player_data = dynamic_cast<ScenedContext*>(Get(guid));
	if(!player_data)
		return NULL;
	return player_data->GetPlayer();
}
