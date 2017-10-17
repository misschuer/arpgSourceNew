
#include <svrcore.h>
#include <protocol/external.h>
#include "logind_app.h"
#include "logind_player.h"
#include "logind_context.h"
#include "logind_mongodb.h"
#include <object/OprateResult.h>
#include "map_manager.h"
#include "logind_script.h"

#define KUAFU_1V1_MAPID 47			//���1v1��ͼid
#define KUAFU_ZBTX_CHENGCI_DITU 48	//�������³ǳص�ͼid
#define KUAFU_ZBTX_HAIWAI_DITU 49	//�������º����ͼid


MapManager::LineInfo MapManager::lineInfo;

MapManager::MapManager():BinLogObject(core_obj::SYNC_LOCAL), m_scened_size(0),m_timer(10000),m_teleport_callback_index(0)/*��ֱ��Ĭ��10���*/
{
	SetBinlogMaxSize(MAX_BINLOG_SIZE_UNLIME);
}

MapManager::~MapManager()
{
}

void MapManager::Update(uint32 diff)
{
	//��ѯ������״̬��Ϊ�����ĳ��������´������
	UpdateScenedStatus();
}

void MapManager::UpdateTeleport(LogindContext *session)
{
	if(session->GetStatus() != STATUS_LOGGEDIN)
		return;

	//����ȴ�������׼���ã������ȵ�һ�°�
	if(m_scened_collapse_time)
		return;

	logind_player *player = session->GetPlayer();
	if (!player)
		return;	

	//��Ȼû�г��������ڣ�Ҳû�����ı�Ҫ��
	if(m_scened_size == 0)
		return;

	if(session->to_mapid == 0 && player->GetTeleportMapID())
	{
		session->to_mapid = player->GetTeleportMapID();
		session->to_teleport_id = player->GetTeleportGuid();
		session->to_line_no = player->GetTeleportLineNo();

		if( player->GetMapId() <= 0)
		{
			tea_perror("LogindContext::UpdateTeleport:mapid %u instanceid %u, GetMapId():%d,GetTeleportMapId():%d",session->to_mapid,session->to_instanceid,
				player->GetMapId(),player->GetTeleportMapID());
			return;
		}
		const MapTemplate *mt = MapTemplate::GetMapTempalte(session->to_mapid);
		if (!mt || mt->IsNotValidPos(player->GetTeleportPosX(), player->GetTeleportPosY()))
		{
			//��������͵�Ŀ�ĵز�����Ч���򴫻�����
			tea_perror("LogindContext::UpdateTeleport:mapid %u instanceid %u pos (%f,%f) is not invalid! %f,%f,%u,%u"
				,session->to_mapid,session->to_instanceid,player->GetTeleportPosX(),player->GetTeleportPosY());
			session->to_mapid = 0;
			player->SetTeleportInfo(ZHUCHENG_DITU_ID, ZHUCHENG_FUHUO_X, ZHUCHENG_FUHUO_Y,0,"");
			if (player->IsKuafuPlayer())
				session->GoBackToGameSvr();			//������ֱ�Ӵ��ص���Ϸ��	
			return;
		}

		session->to_instanceid = player->GetTeleportInstanceId();
		player->SetTeleportInstanceId(0);
		tea_pdebug("LogindContext::UpdateTeleport: player %s will teleport to mapid %u instance %u t_str %s pos(%f,%f) "
			, session->GetGuid().c_str(), session->to_mapid, session->to_instanceid, session->to_teleport_id.c_str(), player->GetTeleportPosX(), player->GetTeleportPosY());
		//ִ�����´����calljoinmap,������������Ҫ�������,���������Ҵ�����Ϣ
		TeleportTo(session);
	}
	//������ϵ�GetTeleportMapIDΪ0��ʱ�򣬿϶��Ǵ��ͳɹ��ˡ�
	//������ϵ�GetTeleportMapID������session->to_mapid��ʱ����֤�����µĴ��������ˡ�
	//������ϵ�GetTeleportLineNo������session->to_line_no����֤�����µĴ��������ˡ�
	//������ϵ�GetTeleportGuid������session->to_teleport_id����֤�����µĴ��������ˡ�
	else if(session->to_mapid 
		&& (session->to_mapid != player->GetTeleportMapID() || session->to_line_no != player->GetTeleportLineNo() || session->to_teleport_id != player->GetTeleportGuid()))
	{
		//��⵽���ͳɹ���
		tea_pdebug("LogindContext::UpdateTeleport: player %s teleport to mapid %u t_str %s success!"
			,session->GetGuid().c_str(), session->to_mapid, session->to_teleport_id.c_str());
		session->to_mapid = 0;
	}	
}

void MapManager::TeleportTo(LogindContext *session)
{
	tea_pdebug("LogindContext::TeleportTo %s begin", session->GetGuid().c_str());
	logind_player *player = session->GetPlayer();
	if (!player->GetMapId())
	{//��ҵ�ǰ��ͼidΪ0����������������
		tea_perror("LogindContext::TeleportTo player %s curmapid is 0!", session->GetGuid().c_str());
		return;
	}

	const MapTemplate *to_mt = MapTemplate::GetMapTempalte(session->to_mapid);	
	const MapTemplate *from_mt = MapTemplate::GetMapTempalte(player->GetMapId());
	//�Ӹ�����ͼ�����Ǹ�����ͼ
	if (from_mt->IsInstance() && !to_mt->IsInstance())
	{
		DelRecordInstance(player);			
	}

	//�����ͼ�����ص���ʵ��
	PlayerJoin(player);
	tea_pdebug("LogindContext::TeleportTo end");
}

void MapManager::Call_Join_Map(uint32 index, logind_player *player)
{
	tea_pdebug("MapManager::Call_Join_Map player %s call join map begin", player->GetGuid().c_str());
	uint32 m_scened_conn = GetScenedConn(index);
	tea_pdebug("MapManager::Call_Join_Map m_scened_conn=%u", m_scened_conn);
	if(!m_scened_conn)
	{
		if(player->GetSession()){
			player->GetSession()->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE20,"");
		}
		return;
	}
	if (!player->GetSession())
	{
		tea_perror("Call_Join_Map ��������Ѿ��Ͽ�");
		return;
	}

	//֪ͨ����������Ҽ����ͼ	
	player->SetTeleportSign(--m_teleport_callback_index);
	//ASSERT(m_teleport_callback_index < 0);
	WorldPacket pkt_scened(INTERNAL_OPT_JOIN_MAP);
	pkt_scened << m_scened_conn << player->GetSession()->GetFD() << player->guid() << player->GetTeleportMapID() << GetInstanceID(index)
		<< player->GetTeleportPosX()<< player->GetTeleportPosY() << m_teleport_callback_index;
	LogindApp::g_app->SendToScened(pkt_scened, m_scened_conn);
	//������ϣ�����FD
	player->SetScenedFD(m_scened_conn);

	//������������1
	DoAddScenedPlayer(m_scened_conn);
	//ServerList.ScenedAddPlayer(m_scened_conn);
	tea_pdebug("MapManager::Call_Join_Map player %s call join map end", player->GetGuid().c_str());
}

void MapManager::AddPlayer(uint32 index, logind_player *player)
{
	//���������Ϣ
	BinLogObject *binlog = dynamic_cast<BinLogObject*>(ObjMgr.Get(GetInstancePlayerInfoID(GetInstanceID(index))));
	if(!binlog)
	{
		uint32 m_scened_conn = GetScenedConn(index);
		tea_perror("MapManager::AddPlayer GetInstancePlayerInfoID==NULL  %s , scened fd %u", player->GetGuid().c_str(), m_scened_conn);
		//������������ر�
		WorldPacket pkt(INTERNAL_OPT_CLOSE_SCENED);
		LogindApp::g_app->SendToScened(pkt, m_scened_conn);
		//�������ҹص�
		if(player->GetSession()){
			player->GetSession()->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE21,"");
		}
		return;
	}
	bool b = false;
	uint32 str_s = binlog->length_str();
	for (uint32 i = MAP_INSTANCE_PLAYER_INFO_START_FIELD; i < str_s; i++)
	{
		if(binlog->GetStr(i).empty())
		{
			binlog->SetStr(i, player->GetGuid());
			b = true;
			break;
		}
	}
	if(!b)//�ŵ����
	{
		uint32 i = MAP_INSTANCE_PLAYER_INFO_START_FIELD;
		if(str_s > i)
			i = str_s;
		binlog->SetStr(i, player->GetGuid());
	}

	//�����ͼ
	Call_Join_Map(index, player);	
}

int32 MapManager::DelPlayer(logind_player *player)
{
	//���ڴ�������ͬ�����⣬���Բ�����������ϵ�instanceid
	int32 index = ForEach([&](uint32 index){
		uint32 instance_id = GetInstanceID(index);
		if(instance_id == 0)
			return false;
		BinLogObject *binlog = dynamic_cast<BinLogObject*>(ObjMgr.Get(GetInstancePlayerInfoID(instance_id)));
		if(!binlog)
		{
			tea_perror("MapManager::DelPlayer instance %u binlog not find", instance_id);
			return false;
		}
		bool result = false;
		uint32 str_s = binlog->length_str();
		for (uint32 i = MAP_INSTANCE_PLAYER_INFO_START_FIELD; i < str_s; i++)
		{
			if(binlog->GetStr(i) == player->GetGuid())
			{
				binlog->SetStr(i, "");
				result = true;
				break;
			}
		}
		return result;
	});
	//������������1
	if(index >= 0)
	{
		uint32 mapid = GetMapID(index);
		uint32 instid = GetInstanceID(index);
		uint32 fd = GetScenedConn(index);
		tea_pdebug("player leave map %s %u %u.", player->guid().c_str(), mapid, instid);
		DoSubScenedPlayer(fd);
		WorldPacket pkt(INTERNAL_OPT_LEAVE_MAP);
		pkt << player->guid() << player->GetSession()->GetFD();
		LogindApp::g_app->SendToScened(pkt, fd);
	}
	else
	{
		//�Ҳ������������
		//1.��ҵ�¼���ͣ�����û�취
		//2.ObjectTypeMapPlayerInfo��ʧ
		//��������ǣ����г���������һ���뿪������
		//�����ǳ���������ͳ�ƻ�ʧЧ�������޸���
		WorldPacket pkt(INTERNAL_OPT_LEAVE_MAP);
		pkt << player->guid() << 0;
		ServerList.ForEachScened([&pkt](uint32 fd){
			LogindApp::g_app->SendToScened(pkt, fd);
			return false;
		});
	}
	return index;
}

bool MapManager::PlayerJoin(logind_player *player)
{
	uint32 mapid = player->GetTeleportMapID();
	uint32 instanceid = player->GetSession()->to_instanceid;
	uint32 lineno = player->GetTeleportLineNo();
	tea_pdebug("player %s join map %u begin, instanceid %u, lineno %u", player->GetGuid().c_str(), mapid, instanceid, lineno);
	const MapTemplate *mt = MapTemplate::GetMapTempalte(mapid);	
	ASSERT(mt);		//�����������Ѿ���֤���ˣ�����Ҫ���Ҳ�����ֱ�Ӷ��԰�
	mt = MapTemplate::GetMapTempalte(mt->GetParentMapid());
	if (!mt)
	{
		tea_perror("player %s join map %u, Parent MapTemplate not find", player->GetGuid().c_str(), mapid);
		return false;
	}
	
	int32 index = 0;
	if(instanceid)
		index = FindInstance(instanceid);				//����Ǽ�������ʵ��
	else
		index = HandleGetInstance(player, mt, lineno, mapid);

	if (index >= 0)
	{
		//��ʵ��ɾ������
		DelPlayer(player);
		AddPlayer(index, player);
		tea_pdebug("player %s join map %u end", player->GetGuid().c_str(), mapid);
		return true;
	}
	else
	{
		//����ʵ��ʧ��
		Call_operation_failed(player->GetSession()->m_delegate_sendpkt,OPRATE_TYPE_LOGIN,OPRATE_RESULT_SCENED_CLOSE,"");
		player->GetSession()->Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE22,"");
		tea_perror("player:%s teleport fail! mapid:%u,instid:%u,lineno:%u", player->GetGuid().c_str(), mapid, instanceid, lineno);
		return false;
	}
	return false;
}

//��ҵ�¼ʱ���߼�
void MapManager::PlayerLogin(logind_player *player)
{
	uint32 instanceid = 0;
	PlayerInstanceInfoMap::iterator it = m_playerInstInfo.find(player->guid());

	//�������û�гɹ���������ݱ����������޸����ݺ����·�����
	if (player->GetMapId() < 0 && player->GetTeleportMapID() > 0)
	{
		player->SetMapId(player->GetTeleportMapID());
		player->SetMapLineNo(player->GetTeleportLineNo());
		player->SetPosition(player->GetTeleportPosX(),player->GetTeleportPosY());
	}	

	//TODO: ���ɵ�ͼҲ��һ������ ����Ҫ�������͵�����ȥ
	//��ȷ�ϸ�����Ϣ����û��
	if(it != m_playerInstInfo.end()
		&& it->second.expire >= time(NULL)		//��ʱ
		&& FindInstance(it->second.instanceid) >= 0	//����Ҳ�����ʵ��,Ҳ����Ч��
		&& IsInstanceOfflineReenter(it->second.mapid) // ��������������½��Ļ�
		)
	{
		PlayerInstanceInfo &info = it->second;
		
		info.expire = 0;
		//��һ��λ�����ڱ���λ�ã��˳�������ʱ��Ҫ��
		//player->SetToDBPositon(player->GetMapId(),player->GetPositionX(),player->GetPositionY());
		instanceid = info.instanceid;
		player->SetMapId(info.mapid);
		player->SetPosition(info.x,info.y);
	}
	else
	{
		player->RelocateDBPosition();//��һ���൱�����װ����������µ�¼������ǰ�ĵ�ַ
		//��������ݿ�load�����Ǹ�����ͼ,����Ϊ����,һ�����������������쳣����
		const MapTemplate *tmp = MapTemplate::GetMapTempalte(player->GetMapId());
		if (!tmp || tmp->IsInstance() && !player->IsLastInRisk())
		{
			player->SetMapId(ZHUCHENG_DITU_ID);
			player->SetPosition(ZHUCHENG_FUHUO_X, ZHUCHENG_FUHUO_Y);
		}

		// ���������ð��С��
		if (player->IsLastInRisk()) {
			int riskMapId = 0;
			float riskMapX = 0;
			float riskMapY = 0;
			string teleportId;
			DoGetRiskTeleportInfo(player, riskMapId, riskMapX, riskMapY, teleportId);
			player->SetMapId(riskMapId);
			player->SetPosition(riskMapX, riskMapY);
			player->SetTeleportGuid(teleportId);
		}

		//������������
		if (!player->IsKuafuPlayer() && player->GetFlags(PLAYER_APPD_INT_FIELD_FLAGS_FROM_KUAFU))
		{
			int map_id;
			float x,y;
			player->GetToDBPosition(map_id, x, y);
			if (map_id > 0 && !DoIsKuafuMapID(map_id))
			{
				player->SetMapId(map_id);
				player->SetPosition(x,y);				
			}			
		}
	}
	//����,�����pk���Ļ�����ɿ��ͼid������
	if (!player->IsKuafuPlayer())
	{//��Ϸ��
		player->SetTeleportInfo(player->GetMapId(), player->GetPositionX(), player->GetPositionY(),0,player->GetTeleportGuid());	
	}
	else
	{//pk�� ���ݿ�����ͣ�m_kuafutype����ѡ���ͼid
		LogindContext *context = player->GetSession();
		ASSERT(context);
		if (!DoSelectKuafuMapid(player, context->m_warid, context->m_kuafutype, context->m_number, context->m_kuafu_reserve, context->m_kuafu_reserve_str))
		{//û���ҵ���Ӧ�ĵ�ͼid�����꣬�����Ҵ��ص���Ϸ��
			context->GoBackToGameSvr();
			return;
		}		
	}
	
	player->SetTeleportInstanceId(instanceid);
}

//��ҵǳ�ʱ���߼�
void MapManager::PlayerLogout(logind_player *player)
{
	//�Ѿ������ͼ�ĵȴ��������ͷ����ʵ��
	int index = DelPlayer(player);
	if(index >= 0 && !player->IsKuafuPlayer())
	{//��Ϸ����������߼�
		int map_id = GetMapID(index);
		if(map_id > 0)
		{
			const MapTemplate *mt = MapTemplate::GetMapTempalte(map_id);
			if(mt)
			{
				//������ڸ�����,Ϊ������10����,����������ִ�Ļ��򲻱��� TODO:����һ�±�������Ҫˢ�µ����
				if(mt->IsInstance() && map_id != BORN_MAP)
				{
					RecordInstance(player);	
					//player->RelocateDBPosition();
				}
			}
		}
	}
}

//��¼��Ҹ�����¼
void MapManager::RecordInstance(logind_player *player)
{
	const MapTemplate *mt = MapTemplate::GetMapTempalte(player->GetMapId());
	if (!DoIsRecordIntanceInfo(player, player->GetMapId(), mt->GetMapBaseInfo().is_instance, mt->GetMapBaseInfo().instance_type))
		return;

	if (!player->GetInstanceId())
	{
		return;
	}

	PlayerInstanceInfo info = {player->GetGuid(),
		uint32(time(NULL)+INSTANCE_DEL_TIME),
		player->GetInstanceId(),(int)player->GetMapId(),
		player->GetPositionX(),player->GetPositionY()
	};
	m_playerInstInfo[info.guid] = info;
}

//ɾ����Ҹ�����¼��Ϣ
void MapManager::DelRecordInstance(logind_player *player)
{
	PlayerInstanceInfoMap::iterator it = m_playerInstInfo.find(player->GetGuid());
	if(it == m_playerInstInfo.end())
		return;
	m_playerInstInfo.erase(it);
}

//���ݵ�ͼģ������͵ĸ������ͽ��п���
int32 MapManager::HandleGetInstance(logind_player *player, const MapTemplate *mt,uint32 lineno, uint32 mapid)
{
	uint16 inst_type = mt->GetMapBaseInfo().instance_type; //�������ͼ�ö��MapInstanceType
	uint32 parent_map = mt->GetParentMapid();

	//�ж�һ�´���ID
	bool need_general_id = false;
	DoIsNeedGeneralid(parent_map, need_general_id);
	if(need_general_id)
	{
		if(player->GetTeleportGuid().empty())
		{
			tea_pwarn("MapManager::HandleGetInstance player->GetTeleportGuid().empty() %s", player->guid().c_str());
			return -1;
		}
	}

	//�Ҳ����ʹ���
	int32 index;
	string general_id;			//�������Ҫgeneralid�Ǿ�Ӧ�ô���
	if (need_general_id)
		general_id = player->GetTeleportGuid();
	DoFindOrCreateMap(mapid, inst_type, general_id, lineno, index);
	return index;
}

//�����µĵ�ͼʵ��
int32 MapManager::CreateInstance(uint32 mapid, const string &general_id,uint32 lineno)
{
	const MapTemplate *mt = MapTemplate::GetMapTempalte(mapid);
	uint16 inst_typ = mt->GetMapBaseInfo().instance_type;
	uint32 parent_id = mt->GetParentMapid();
	//uint32 instance_id = GetNewInstanceID();
	uint32 instance_id = 0;
	uint32 conn = 0;
	if(parent_id != mapid)
	{
		int32 index = FindInstance(parent_id, general_id, lineno);
		if(index < 0)
		{
			index = CreateInstance(parent_id, general_id, lineno);
		}
		ASSERT(index >= 0);
		instance_id = GetInstanceID(index);
		conn = GetScenedConn(FindInstance(parent_id, general_id, lineno));
	}
	else
	{
		instance_id = GetNewInstanceID();
		conn = DoGetScenedFDByType(inst_typ, mapid);
	}

	tea_pdebug("MapManager::CreateInstance inst_typ = %u, parent_id = %u, instance_id = %u, conn = %u begin"
		, inst_typ, parent_id, instance_id, conn);
	
	if (conn == 0)
	{
		tea_pdebug("MapManager::CreateInstance find scened fail, mapid %u, gengeral_id %s, lineno %u", mapid, general_id.c_str(), lineno);
		return -1;
	}
	
	//��ʼ���ӵ�ͼ��Ϣ
	//�Ҹ���λ
	int32 result = ForEach([&](uint32 index){
		if(GetInstanceID(index) == 0)
		{
			SetMapInstanceInfo(index, instance_id, mapid, lineno, conn, general_id);
			return true;
		}
		return false;
	});
	//û�ҵ���λ���ŵ�����
	if(result < 0)
	{
		result = length_uint32() / MAX_MAP_INSTANCE_INT_TYPE;
		SetMapInstanceInfo(result, instance_id, mapid, lineno, conn, general_id);
	}
	//�����õ�ͼ�������Ϣbinlog
	const char *guid = GetInstancePlayerInfoID(instance_id);
	BinLogObject *blog = new BinLogObject(core_obj::SYNC_SLAVE | core_obj::SYNC_LOCAL);
	blog->SetBinlogMaxSize(core_obj::SyncEventRecorder::MAX_BINLOG_SIZE_UNLIME);
	blog->SetGuid(guid);
	blog->SetOwner(MAP_INSTANCE_PLAYER_INFO_OWNER_STRING);
	ObjMgr.CallPutObject(blog,[guid](bool){
		ObjMgr.InsertObjOwner(guid);
	});
	//֪ͨ������������ͼʵ��
	WorldPacket pkt_scened(INTERNAL_OPT_ADD_MAP_INSTANCE);
	pkt_scened << instance_id << mapid << lineno << general_id;
	LogindApp::g_app->SendToScened(pkt_scened, conn);

	//������ͼ���
	if (DoIsWorldMapID(mapid)) {
		MapManager::lineCreated(mapid, lineno, instance_id);
	}

	tea_pdebug("MapManager::CreateInstance end");
	return result;
}

//�ر�ĳһ��ͼ
bool MapManager::TryClose(uint32 instance_id)
{
	if(instance_id == 0)
		return false;

	//Ϊ�˸�����Ĵ�ӡ�ã���ѭ����Ų������
	int32 index = FindInstance(instance_id);
	if(index < 0)
		return true;
	int mapid = GetMapID(index);
	uint32 lineNo = GetLineNo(index);
	uint32 scened_conn = GetScenedConn(index);

	//��������û�����������
	string player_info_id = GetInstancePlayerInfoID(instance_id);
	BinLogObject *binlog = dynamic_cast<BinLogObject*>(ObjMgr.Get(player_info_id));
	if(!binlog)
	{
		tea_perror("MapManager::TryClose GetInstancePlayerInfoID==NULL  %s", player_info_id.c_str());
		return false;
	}
	uint32 str_s = binlog->length_str();
	for (uint32 i = MAP_INSTANCE_PLAYER_INFO_START_FIELD; i < str_s; i++)
	{
		if(!binlog->GetStr(i).empty())
		{
			tea_pinfo("MapManager::TryClose has player %s  %s, mapid = %d, conn = %u"
				, binlog->GetStr(i).c_str(), player_info_id.c_str(), mapid, scened_conn);
			return false;
		}
	}

	bool call_del = false;
	while(true)
	{
		//������������ӻ����ţ��رհ�
		if(!call_del && scened_conn)
		{
			CallDelMapInstance(index);
			call_del = true;
			//��������ͼ�ڵ��������
			ObjMgr.CallRemoveObject(player_info_id);
		}
		//��յ�ͼ��Ϣ
		SetMapInstanceInfo(index, 0, 0, 0, 0, "");

		index = FindInstance(instance_id);
		if(index < 0)
			break;
	}
	ASSERT(call_del);

	// ����ɾ��ɾ
	if (DoIsWorldMapID(mapid)) {
		MapManager::lineRemoved(mapid, lineNo);
	}

	tea_pdebug("MapManager::TryClose instance_id = %u, end", instance_id);
	return true;
}

void MapManager::CallDelMapInstance(uint32 index)
{
	WorldPacket pkt_scened(INTERNAL_OPT_DEL_MAP_INSTANCE);
	pkt_scened << GetMapID(index)<< GetInstanceID(index);
	uint32 m_scened_conn = GetScenedConn(index);
	LogindApp::g_app->SendToScened(pkt_scened, m_scened_conn);
}

// �������쳣��ֹ���� 
bool MapManager::OnScenedClosed(int32 scened_id)
{
	tea_pinfo("scened %u close", scened_id);
	//��������´���
	bool result = true;
	ForEach([&](uint32 index){
		if (GetScenedConn(index) == scened_id)
		{
			ClearInstanceAndTelePlayer(scened_id, index);
		}
		return false;//Ҫ�������е�ͼ��Ϣ
	});
	return result;
}

void MapManager::Close()
{
	ForEach([&](uint32 index){
		if(GetInstanceID(index))
		{
			//todo
		}
		return false;
	});
	
}

//����ʵ��ID���в��ҵ�ͼʵ��
int32 MapManager::FindInstance(uint32 instanceid)
{
	//����ʵ�����Ҹõ�ͼ
	int32 i = ForEach([&](uint32 index){
		return GetInstanceID(index) == instanceid;
	});
	return i;
}

//���ҵ�ͼʵ��
int32 MapManager::FindInstance(uint32 mapid, const string ganeral_id, uint32 lineo)
{
	//����ʵ�����Ҹõ�ͼ
	int32 i = ForEach([&](uint32 index){
	
		return GetInstanceID(index) != 0
			&& GetMapID(index) == mapid
			&& GetGeneralID(index) == ganeral_id
			&& GetLineNo(index) == lineo;
	});
	return i;
}

//����general_id����
int32 MapManager::FindInstance(const string ganeral_id)
{
	if (ganeral_id.empty())
		return -1;
	//����ʵ�����Ҹõ�ͼ
	int32 i = ForEach([&](uint32 index){
		return GetInstanceID(index) != 0 && GetGeneralID(index) == ganeral_id;			
	});
	return i;
}

//��������
int32 MapManager::ForEach(std::function<bool(uint32 index)> f)
{
	uint32 map_inst_count = length_uint32() / MAX_MAP_INSTANCE_INT_TYPE;
	for (uint32 i = 0; i < map_inst_count; i++)
	{
		if(f(i))
			return i;
	}
	return -1;
}

//��¼�������޸�
void MapManager::Restart()
{

}

//��ͼ��·��
void MapManager::HandleMapPkt(packet *pkt)
{
	uint32 to_instance_id, to_map_id, src_instance_id, src_map_id;
	string to_general_id, src_general_id;
	*pkt >> to_instance_id >> to_map_id >> to_general_id >> src_instance_id >> src_map_id >> src_general_id;
	uint32 lineo = 0;
	const MapTemplate *mt = MapTemplate::GetMapTempalte(to_map_id);
	ASSERT(mt);

	int index;
	DoFindOrCreateMap(mt->GetMapBaseInfo().mapid, mt->GetMapBaseInfo().instance_type, to_general_id, lineo, index);
	ASSERT(index >= 0);

	to_instance_id = GetInstanceID(index);
	uint32 fd = GetScenedConn(index);
	ASSERT(to_instance_id);
	memcpy(pkt->content, &to_instance_id, sizeof(to_instance_id));
	WorldPacket _pkt(*pkt);
	LogindApp::g_app->SendToScened(_pkt, fd);
}

//��鳡����״̬��Ϊ�����ĳ�����������´���
void MapManager::UpdateScenedStatus()
{
	//��ǰ֡����������
	DoGetScenedSize(m_scened_size);

	//��ǰû�г���������Ҳû�д��͵ı�Ҫ��
	if(m_scened_size == 0)
		return;
	//��������������������ǲ��ǵȴ���ʱ��
	bool scened_ready = m_scened_size >= g_Config.max_secend_count;
	if(!scened_ready)
	{
		time_t t = time(NULL);
		if(m_scened_collapse_time && t - m_scened_collapse_time >= g_Config.scened_collapse_time_out)
		{
			//tea_pwarn("MapManager::UpdateScenedStatus() timeout.");
			scened_ready = true;
		}
		if(m_scened_collapse_time == 0)
			m_scened_collapse_time = t;
	}
	if(!scened_ready)
		return;

	m_scened_collapse_time = 0;
	//��һ�µ�ͼʵ�����ڵĳ������ǲ��ǹ��ˣ�������˾ʹݻ�����
	//ÿ֡����޸�100����ͼ�ͺá���
	for (int i = 0; i < 100; i++)
	{
		//ÿ��foreach�޸�һ�ŵ�ͼ�����������ϵ���ҵ�
		if(ForEach([this](uint32 index){
				uint32 fd = GetScenedConn(index);
				if(fd && !ServerList.HasScenedFd(fd))
				{
					OnScenedClosed(fd);
					return true;
				}
				return false;
			}) == -1)
			break;
	}
}

//���´������
void MapManager::ReTelePlayer(logind_player *player, uint32 scened_id)
{
	if(!player->GetSession() || player->GetSession()->GetStatus() != STATUS_LOGGEDIN)
	{
		tea_pdebug("scened %u coolapse,but player %s is outline", scened_id, player->guid().c_str());
		return;
	}
	tea_pdebug("scened %u coolapse, player %s start tele", scened_id, player->guid().c_str());

	Call_operation_failed(player->GetSession()->m_delegate_sendpkt,OPRATE_TYPE_LOGIN ,OPRATE_RESULT_SCENED_ERROR,"");
	player->SetTeleportInfo(player->GetMapId(), player->GetPositionX(), player->GetPositionY(), 0, player->GetTeleportGuid());
}

void MapManager::ClearInstanceAndTelePlayer(uint32 scened_id, uint32 index)
{
	uint32 instance_id = GetInstanceID(index);
	const char *player_info_id = GetInstancePlayerInfoID(instance_id);
	BinLogObject *binlog = dynamic_cast<BinLogObject*>(ObjMgr.Get(player_info_id));
	if(!binlog)
	{
		tea_perror("MapManager::ClearInstanceAndTelePlayer GetInstancePlayerInfoID==NULL  %s", player_info_id);
		ObjMgr.ForEachPlayer([&](logind_player *player){
			if(player->GetInstanceId() == instance_id)
			{
				ReTelePlayer(player,scened_id);
			}
		});
	}
	else
	{
		uint32 str_s = binlog->length_str();
		tea_pdebug("scened %u coolapse, instance %u reset", scened_id, instance_id);
		//����ͼ��������ң��޸����ǵĴ����±�
		//����ҵ�update�ٴ��������͵�ʱ�򣬾ͻ����������������
		for (uint32 i = MAP_INSTANCE_PLAYER_INFO_START_FIELD; i < str_s; i++)
		{
			string player_guid = binlog->GetStr(i);
			if(player_guid.empty())
			{
				continue;
			}
			logind_player *player = LogindContext::FindPlayer(player_guid);
			if(!player)
			{
				tea_pdebug("scened %u coolapse,but player %s not find", scened_id, player_guid.c_str());
				continue;
			}
			ReTelePlayer(player, scened_id);
		}
	}
	//��������ͼ����
	SetMapInstanceInfo(index, 0, 0, 0, 0, "");
	//��������ͼ�ڵ��������
	ObjMgr.CallRemoveObject(player_info_id);
}

//������ȫ���������Ժ��������еĵ�ͼ��Ϣ��
void MapManager::ClearMapInstance()
{

}

//�����������
uint32 MapManager::PlayerCount(uint32 index)
{
	if(index == -1)
		return 0;

	string player_info_id = GetInstancePlayerInfoID(GetInstanceID(index));
	BinLogObject *binlog = dynamic_cast<BinLogObject*>(ObjMgr.Get(player_info_id));
	if(!binlog)
	{
		return 0;
	}
	uint32 str_s = binlog->length_str();
	uint32 count = 0;
	for (uint32 i = MAP_INSTANCE_PLAYER_INFO_START_FIELD; i < str_s; i++)
	{
		if(!binlog->GetStr(i).empty())
		{
			++count;
		}
	}

	return count;
}

//���ҵ�ͼʵ��
int MapManager::LuaFindInstance(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 3);
	uint32 mapid = LUA_TOINTEGER(scriptL, 1);
	string general_id = LUA_TOSTRING(scriptL, 2);
	uint32 lineno = LUA_TOINTEGER(scriptL, 3);
	lua_pushinteger(scriptL, MapMgr->FindInstance(mapid, general_id, lineno));
	return 1;
}


//������ͼʵ��
int MapManager::LuaCreateInstance(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 3);
	uint32 mapid = LUA_TOINTEGER(scriptL, 1);
	string general_id = LUA_TOSTRING(scriptL, 2);
	uint32 lineno = LUA_TOINTEGER(scriptL, 3);
	lua_pushinteger(scriptL, MapMgr->CreateInstance(mapid, general_id, lineno));
	return 1;
}

//ͳ��ĳ��ͼ���������
int MapManager::LuaMapPlayerCount(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 3);
	uint32 mapid = LUA_TOINTEGER(scriptL, 1);
	string general_id = LUA_TOSTRING(scriptL, 2);
	uint32 lineno = LUA_TOINTEGER(scriptL, 3);
	int index = MapMgr->FindInstance(mapid, general_id, lineno);
	lua_pushinteger(scriptL, MapMgr->PlayerCount(index));
	return 1;
}
