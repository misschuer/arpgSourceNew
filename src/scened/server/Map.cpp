#include "scened.h"
#include "scened_context.h"
#include "Map.h"
#include "Grid.h"
#include <object/GameObject.h>
#include "Player.h"
#include "LootManager.h"
#include "LootMgr.h"
#include "scened_scripts.h"
#include <object/SharedDef.h>
#include "QuestGetter.h"
#include <memdb/mem_db.h>
#include <server/internal_callback.h>
#include <shared/log_handler.h>
#include <object/OprateResult.h>
#include <svrcore/server/Storage.h>

//const float NOTICE_DISTANCE = 6.0f;

//////////////////////////////////////////////////////////////////////////
//for Map static
Map::MapInstances Map::map_instances;
WaitJoiningVec Map::wait_joing_vec;

Map *Map::CreateInstance(uint32 instanceid,uint32 mapid,uint32 lineno,const string &general_id)
{
	ASSERT(Map::FindInstance(instanceid,mapid)==NULL);
	Map *m = NULL;
	//�жϸ�����ͼ�Ƿ����
	const MapTemplate *mt = MapTemplate::GetMapTempalte(mapid);
	if(mt->GetParentMapid() == mapid)	//����Ǹ���ֱ�Ӵ���
	{
		//����Ǹ����򴴽���ͬ�Ķ���ʵ��
		m = mt->IsInstance() ? new InstanceMap(mapid, instanceid, lineno, general_id) : new Map(mapid, instanceid, lineno, general_id);
	}
	else
	{
		mt = MapTemplate::GetMapTempalte(mt->GetParentMapid());
		Map* parent = Map::FindInstance(instanceid,mt->GetParentMapid());
		if(!parent)
			parent = CreateInstance(instanceid,mt->GetParentMapid(),lineno,general_id);

		//����Ǹ����򴴽���ͬ�Ķ���ʵ��
		m = mt->IsInstance() ? new InstanceMap(mapid, instanceid, lineno, general_id) : new Map(mapid, instanceid, lineno, general_id);
		m->m_parent = parent;		//���ø�����ͼʵ��
	}
	ASSERT(m);
	map_instances.insert(make_pair(instanceid,m));

	return m;
}

//ɾ����ͼʵ��
void Map::DelMap(uint32 instanceid)
{
	for(auto it=map_instances.lower_bound(instanceid);
		it != map_instances.upper_bound(instanceid);++it)
	{
		Map *m = it->second;
		//��ͼʵ��ɾ��ʱ����ұ���Ϊ��
		//�����ط��ص���ʱ�������Ȼ���ǿյģ�����Ҳ������ɾ����
		if(!m->m_players.empty() || !ScenedApp::g_app->get_connection())
		{
			stringstream ss;
			for (auto it:m->m_players)
			{
				ss << it.second->guid() << ";";
			}
			tea_pinfo("Map::DelMap map id %u,    %s", m->GetMapId(), ss.str().c_str());
		}
		safe_delete(m);
	}
	map_instances.erase(instanceid);
	auto it = all_parent_map_info.find(instanceid);
	ASSERT(it != all_parent_map_info.end());
	safe_delete(it->second);
	all_parent_map_info.erase(instanceid);
}

Map *Map::FindInstance(uint32 instance_id,uint32 map_id)
{
	for(auto it=map_instances.lower_bound(instance_id);
		it != map_instances.upper_bound(instance_id);++it)
	{
		if(it->second->GetMapId() == map_id)
			return it->second;
	}
	return NULL;
}
// ����һϵ�е�mapid��ö�Ӧ��һϵ�еĵ�ͼʵ������
std::vector<Map *> Map::FindFieldBossInstance(std::set<uint32> s_mapid) {

	std::vector<Map *> v_mapinstance;

	for(auto it=map_instances.begin();it != map_instances.end();++it) {

		uint32 mapid  = it->second->GetMapId();
		uint32 lineNo = it->second->GetLineNo();
		if (v_mapinstance[mapid] && lineNo <= MAX_DEFAULT_LINE_COUNT) {
			v_mapinstance.push_back(it->second);
		}
	}

	return v_mapinstance;
}

//���ݵ�ͼID�ͷ���IDȡ�õ�ͼʵ��,��������ڷ��ؿգ�����ǧ������Ŷ
//Map *Map::FindInstance(uint32 map_id, uint8 lineNo)
//{
//	ASSERT(!MapTemplate::GetMapTempalte(map_id)->IsInstance() 
//		|| MapTemplate::GetMapTempalte(map_id)->m_baseinfo.instance_type == MAP_INST_TYP_ACTIVITY);
//	for(auto it=map_instances.begin();it != map_instances.end();++it)
//	{
//		if(it->second->GetMapId() == map_id && it->second->GetLineNo() == (uint32)lineNo)
//			return it->second;
//	}
//	return NULL;
//}

void Map::ClearInstance()
{
	std::for_each(map_instances.begin(),map_instances.end(),
		[](MapInstances::value_type& it){safe_delete(it.second);});
	map_instances.clear();
}

//��⸱������������
void Map::CheckMapInstanceLastTime(TimerHolder& th)
{
	//����ͳ�ƣ�������ʵ����������ID�ܳ���
	map<uint32,uint32> all_inst_player_num;
	for (auto it = map_instances.begin();it != map_instances.end(); ++it)			
		all_inst_player_num[it->second->GetInstanceID()] += it->second->GetPlayerCount();
	
	//��ͨ�Ǹ�����ͼ,���ô���
	//���˸��������Ϊ�յ�����±���ʮ���ӣ����������뿪����������
	//���ͼ��ʱ�䵽�˽���Ҵ��ͳ�ȥ���ҹرյ�ͼ
	uint32 t = (uint32)time(nullptr);
	for (auto it = map_instances.begin();it != map_instances.end(); ++it)
	{
		//ȡ����Ӧ��ͼģ��,������ȡ������ͼ��Ϣ
		const MapTemplate *mt = MapTemplate::GetMapTempalte(it->second->GetMapId());
		//��������
		const uint16 inst_type = mt->GetMapBaseInfo().instance_type;
		//��̬��ͼ�Ͳ����ͷ���
		if(inst_type == MAP_INST_TYP_NO_INSTANCE)
			continue;

		//ʵ������������
		auto player_num = all_inst_player_num[it->second->GetInstanceID()];

		InstanceMap *inst = dynamic_cast<InstanceMap*>(it->second);

		ASSERT(inst);
		//m_end_time��һ���ܿؿ��أ����������й���֮��
		//��û�˵�ʱ�򣬵�ͼʮ���Ӿ��ͷ�
		if(inst->m_end_time == 0)
		{
			if(player_num == 0)
				inst->m_end_time = t + 600;
		}
		else
		{
			if(player_num != 0)
			{
				inst->m_end_time = 0;
			}
			else if(inst->m_end_time < t)
			{
				ScenedApp::g_app->call_del_map(inst->GetInstanceID());
				continue;
			}
		}

		if(inst_type == MAP_INST_TYP_SINGLETON || inst_type == MAP_INST_TYP_ACTIVITY)		//����Ǹ���
		{
			uint32 inst_mapid = inst->GetMapId();	

			// ����һ��(����ĳ������д����ʱ��, �����ڴ�й©)
			if (inst->GetMapCreateTime() + 180 < t && inst->GetMapEndTime() == 0) {
				inst->SetMapEndTime(t-1);
			} 
			
			if(inst->GetMapEndTime() != 0 && inst->GetMapEndTime() < t)
			{
				if(player_num != 0) {
					if (isMapTimeLimit(inst->GetMapId())) {
						inst->ExitInstance();		//�ȵ�����ң���һ�ν�����ɾ��ʵ��
					}
				}
				else {
					// ɢ�˹һ���ͼ�ͼ������ û��Ҳɾ��
					ScenedApp::g_app->call_del_map(inst->GetInstanceID());
				}
				continue;
			}
		}
		/**
		else if(inst_type == MAP_INST_TYP_ACTIVITY)		//������Ļ���GM��Ч
		{
			if(inst->GetMapEndTime() != 0 && inst->GetMapEndTime() < t)
			{
				//������Ϊ����رյ�ͼ,������Ҵ���Ϊ��
				if(player_num == 0)
				{
					ScenedApp::g_app->call_del_map(inst->GetInstanceID());
					continue;
				}
				else
				{
					inst->ExitInstance();
					continue;
				}
			}
		}
		*/
	}
	th._next_time += 60;		//һ���Ӻ�������
}

void Map::CheckWaitJoingVec(uint32 /*diff*/)
{
	uint32 now = (uint32)time(NULL);
	for (auto it = wait_joing_vec.begin(); it != wait_joing_vec.end();)
	{
		//TODO: ���������p����
		auto *context = dynamic_cast<ScenedContext*>(ObjMgr.Get(it->player_guid));
		//�������ʵ��ID��ص�������˵�������Ѿ�����,��֮
		if(context && context->GetTeleportSign() == it->teleport_sign)
		{
			tea_pdebug("player %s join map [%u] BEGIN",it->player_guid, it->to_map_id);
			context->On_Teleport_OK(it->connection_id, it->to_map_id, it->to_instance_id, it->to_x, it->to_y);
			//֪ͨ���ط�
			ScenedApp::g_app->RegSessionOpts(it->connection_id);
			tea_pdebug("player %s join map [%u]END",it->player_guid, it->to_map_id);				

			it = wait_joing_vec.erase(it);
		}
		else if(now - it->create_tm > 60)
		{
			//�����Ӧ���ͳ���1����,�����䴫��ʧЧ
			tea_pwarn("CheckWaitJoingVec timeout, guid:%s, fd:%u, mapid:%d instanceid:%u",it->player_guid, it->connection_id, it->to_map_id, it->to_instance_id);
			if(context){
				context->Close(PLAYER_CLOSE_OPERTE_SCREND_ONE38,"");
			}
			it = wait_joing_vec.erase(it);
		}
		else
			++it;
	}
}

//��ӡ�ڴ������еĵ�ͼ��Ϣ
void Map::PrintAllMap()
{
	tea_pinfo("-----------------------------------------------------------------");
	tea_pinfo("map count %u", map_instances.size());
	for (auto it = map_instances.begin();it != map_instances.end(); ++it)
	{
		Map *m = it->second;
		tea_pinfo("instance id %u, map id %u , player count %u,",m->GetInstanceID(), m->GetMapId(), m->m_players.size());		
	}
	tea_pinfo("-----------------------------------------------------------------");
}

//////////////////////////////////////////////////////////////////////////
//for Map

map<uint32, BinLogObject*> Map::all_parent_map_info;		//������ͼ����
void Map::UpdateParentInfo()
{
	for (auto it_mi:all_parent_map_info)
	{
		static ByteArray byte_buf;
		byte_buf.clear();
		if(it_mi.second->WriteUpdateBlock(byte_buf))
		{
			byte_buf.position(0);
			ObjMgr.Compress(byte_buf);
			byte_buf.position(0);
			packet *pkt_compress = external_protocol_new_packet(SMSG_MAP_UPDATE_OBJECT);
			packet_write(pkt_compress,(char*)byte_buf.cur_data(),byte_buf.bytesAvailable());
			byte_buf.clear();
			update_packet_len(pkt_compress);

			for(auto it=map_instances.lower_bound(it_mi.first);
				it != map_instances.upper_bound(it_mi.first);++it)
			{
				Map *m = it->second;
				for (auto it_player:m->m_players)
				{
					if(it_player.second && it_player.second->GetSession())
					{
						it_player.second->GetSession()->SendPacket(*pkt_compress);
					}
				}
			}

			//�ⲿ�����ͺÿ��Ի�����
			external_protocol_free_packet(pkt_compress);
			it_mi.second->Clear();
		}
	}
}

BinLogObject Map::fighting_info_binlog(core_obj::SYNC_NONE);
void Map::BroadcastFightingInfo(Unit *unit)
{
	Map *map = unit->GetMap();
	if(!map) return;

	uint32 caster = unit->GetUIntGuid();
	auto& info =  Map::fighting_info_binlog;
	
	uint32 spellid = 0;

	ByteArray *buff = ObjMgr.GridMallocByteArray();
	uint32 count = info.GetUInt32(MAX_FIGHTING_INFO_INT_NOW_INDEX);
	uint16 dstx = 0;
	uint16 dsty = 0;
	//д��ʩ���ߣ�д�뼼��id, ��������������
	*buff << (uint16)SMSG_FIGHTING_INFO_UPDATE_OBJECT << caster << uint8(count);

	for(uint32 i = 0; i < count; i++)
	{
		uint32 start = i * MAX_FIGHTING_INFO_INT + MAX_FIGHTING_INFO_INT_START;		
		
		uint32 target = info.GetUInt32(start + FIGHTING_INFO_INT_RESERVE_3);		//Ŀ��ID
		uint32 lastHP = info.GetUInt32(start + FIGHTING_INFO_INT_HP);				//ʣ��Ѫ��
		double damage = info.GetDouble(start + FIGHTING_INFO_INT_VALUES);			//�˺���ֵ
		
		uint8 attack_type = info.GetByte(start + FIGHTING_INFO_INT_UINT8, 3);		//����
		uint32 newSpellid = info.GetUInt32(start + FIGHTING_INFO_INT_SPELL_ID);		//����ID
		if (dstx == 0 && dsty == 0) {
			dstx = info.GetUInt16(start + FIGHTING_INFO_INT_RESERVE_0, 0);		//���������x
			dsty = info.GetUInt16(start + FIGHTING_INFO_INT_RESERVE_0, 1);		//���������y
		}
		if(spellid ==0){
			//��ʼ��spellidֵ
			spellid = newSpellid;
		//�������id�Ѿ���ʼ���ˣ��������ѭ������id��һ�£������
		}
		//д��isKill��1bit
		uint8 killBit = info.GetByte(start + FIGHTING_INFO_INT_UINT8, 0);			//�Ƿ�ɱ��

		*buff << target << lastHP << attack_type << killBit << damage;
	}
	*buff << spellid << dstx << dsty;

	//info.Reset();
	Map::FightingInfoBinlogRest();

	unit->GetGrid()->AsyncBroadcast(buff);
	ObjMgr.GridFreeByteArray(buff);
	//unit->GetGrid()->fighting_blocks.push_back(buff);
}

Map::Map(uint32 mapid, uint32 instanceid, uint32 lineno, const string &generalid):
	m_parent_map_info(0),m_template(NULL),m_grids(NULL),m_is_can_jump(true)
	,m_can_recovry(true),m_script_callback_key(0),m_parent(0),m_end_time(0)
	,m_broadcast_nogrid(false),m_is_close_respawn(false),m_can_castspell(true)
{
	m_mapid = mapid;

	m_template = MapTemplate::GetMapTempalte(mapid);
	ASSERT(m_template);	

	auto it = all_parent_map_info.find(instanceid);
	if(it == all_parent_map_info.end())
	{
		m_parent_map_info = new BinLogObject(core_obj::SYNC_MASTER | core_obj::SYNC_UPDATEDATA);
		m_parent_map_info->SetGuid(g_GuidMgr.MAKE_NEW_GUID(ObjectTypeMap, instanceid, ""));
		m_parent_map_info->SetUInt32(MAP_INT_FIELD_MAP_ID, m_template->GetParentMapid());
		m_parent_map_info->SetUInt32(MAP_INT_FIELD_INSTANCE_ID, instanceid);
		m_parent_map_info->SetUInt32(MAP_INT_FIELD_LINE_NO, lineno);
		m_parent_map_info->SetUInt32(MAP_INT_FIELD_CREATE_TM, uint32(time(nullptr)));
		m_parent_map_info->SetUInt32(MAP_INT_FIELD_INSTANCE_TYPE, m_template->m_baseinfo.instance_type);
		m_parent_map_info->SetStr(MAP_STR_GENERAL_ID, generalid);
		m_parent_map_info->SetBinlogMaxSize(core_obj::SyncEventRecorder::MAX_BINLOG_SIZE_5);//�ܳ���һ֡��һ����ͬʱ�뿪�˰ɡ�����
		m_parent_map_info->Clear();
		all_parent_map_info[instanceid] = m_parent_map_info;
	}
	else
	{
		m_parent_map_info = it->second;
	}

	m_parent = this;
	for (uint8 i = 0;i<MAX_EQUIP_ATTR;i++)
	{
		m_mapAttrBonus[i] = 0;
	}
	Load();
}

Map::~Map()
{
	for (CreaturesMap::iterator it = m_alive_creatures.begin();
		it != m_alive_creatures.end();++it)
	{
		it->second->ClearAttacker(true);
		delete it->second;
	}
	m_alive_creatures.clear();

	for (PlayerMap::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		it->second->ClearAttacker(true);
		it->second->ClearPet();
	}

	//�ͷ�GameObject
	for (GameObjectMap::iterator it = m_gameobjects.begin();
		it != m_gameobjects.end();++it)
	{	
		delete it->second;		
	}
	m_gameobjects.clear();

	//�ͷŶ�ʱ��
	for(ScriptCBList::iterator it = m_script_callbacks.begin(); it != m_script_callbacks.end();)
	{
		script_timer_callback *stc = *it;
		m_script_callbacks.erase(it++);
		free(stc);
	}
	//�ͷ�ʱ�����ʱ��
	for(ScriptTimeStampList::iterator it = m_script_timestamp_callbacks.begin(); it != m_script_timestamp_callbacks.end();)
	{
		script_timestamp_timer_callback *stc = *it;
		m_script_timestamp_callbacks.erase(it++);
		free(stc);
	}

	//�ͷ��ڴ�
	safe_delete(m_grids);
}

bool Map::Load()
{
	//��ʼ����ͼ�����ʹ��״̬
	uint32 mapsize, width = m_template->GetMapBaseInfo().width;
	uint32 start;
	//��ʼ������
	m_loot_area = g_Config.loot_area;
	m_loot_site_width = width / m_loot_area;
	m_loot_site_hight = m_template->GetMapBaseInfo().height / m_loot_area;
	mapsize = m_loot_site_width * (m_loot_site_hight+1);
	m_all_enpty_count = mapsize;
	//��ʼ�����з���ս��Ʒ�ĸ��ӣ�������֮
	m_all_site.SetCount(mapsize);
	for (uint32 i = 0;i < mapsize; i++)
	{
		//Ѱ�Ҷ�Ӧ�ľ���������ʼ��
		if(i < m_loot_site_width || m_loot_area == 1)
		{
			start = i * m_loot_area;
		}
		else
		{
			start = (uint32(i / m_loot_site_width) * width + i % m_loot_site_width) * m_loot_area;
		}
		//�ж�ս��Ʒ����ڣ��Ƿ��п��ø���
		bool can_use = true;		
		//�����С����
		for(uint32 x = 0; x < m_loot_area; x++)//ѭ��X��
		{
			for(uint32 y = 0; y < m_loot_area; y++)//ѭ��Y��
			{
				//�����ã���Ϊtrue��������ѭ��
				if(!m_template->IsCanRun(start + x * width + y))
				{
					can_use = false;
					break;
				}
			}
			if(!can_use)
			{
				break;
			}
		}
		//�������ã��ɵ���
		if(!can_use)
		{
			m_all_site.SetBit(i);
			m_all_enpty_count--;
		}
	}

	//���õ�ͼ�ű�
	DoSelect_Instance_Script(this);
	//��ʼ����Ƿ�ȫͼ�㲥����
	DoGetInitMapData(this);
	//��ʼ������
	ASSERT(m_grids==NULL);
	if(m_broadcast_nogrid)
		m_grids = new GridManager(this,m_template->m_baseinfo.width,m_template->m_baseinfo.height,65535);	//grid�����൱��ȫͼ�㲥
	else
		m_grids = new GridManager(this,m_template->m_baseinfo.width,m_template->m_baseinfo.height);

	//m_teleports
	for (auto iter_t = m_template->m_teleport.begin()
		;iter_t!=m_template->m_teleport.end();++iter_t)
	{		
		GameObject *tele = new GameObject;		
		tele->Create(Map::CreateNewCreatureID(),iter_t->temp_id);
		ASSERT(tele->IsTeleteport());			

		tele->SetName(iter_t->name);
		tele->SetMapId(GetMapId());
		tele->SetInstanceId(GetInstanceID());
		tele->SetPosition((float)iter_t->x,(float)iter_t->y);

		tele->SetToPositionX(float(iter_t->to_x));
		tele->SetToPositionY(float(iter_t->to_y));
		tele->SetToMapId(iter_t->to_mapid);

		AddGameObject(tele);
	}

	//ˢ��	
	for (auto iter = m_template->m_monsters.begin();
		iter!=m_template->m_monsters.end();++iter)
	{
		AddCreature(iter->second.templateid,
			float(iter->second.x),float(iter->second.y),float(iter->second.toward),
			iter->second.respawn_time,
			iter->second.move_type,
			iter->second.flag,
			iter->second.alias_name);
	}

	//ˢ��Ϸ����	
	for (auto iter = m_template->m_gameobjects.begin();
		iter != m_template->m_gameobjects.end();++iter)
	{
		GameObject *go = new GameObject;		
		bool b = go->Create(Map::CreateNewCreatureID(),iter->templateid);
		if(b){
			go->SetPosition(float(iter->x),float(iter->y));	
			go->SetOrientation(iter->toward);
			AddGameObject(go);
		}
		else
		{
			delete go;
		}
	}	

	//Ϊ�˱��ڽű�ȡ�������,��һ֡��ֱ�Ӵ����������
	UpdateRespan(0);

	//��ʼ����ͼ�ű��������õ�ͼ�籾	
	DoInitMapScript(this);
	// ��ʼ����ͼ����
	DoInitMapWorldObject(this);
	//��ʼ����ͼӲ������
	DoInitReadHddMapData(this);
	return true;
}

void Map::Update(uint32 diff)
{	
	ASSERT(m_grids);
	m_grids->Update(diff);

	UpdateRespan(diff);	

	//�ܶ�ʱ��
	if(diff < 1000 && !m_script_callbacks.empty() && !m_state_script.empty())
	{
		for(ScriptCBList::iterator it = m_script_callbacks.begin(); it != m_script_callbacks.end();)
		{
			script_timer_callback *stc = *it;

			if(stc->invalid == 1)//�ѱ�ɾ��
			{
				m_script_callbacks.erase(it++);
				free(stc);
				continue;
			}
			if(stc->is_new == 1)//��һ֡��ִ��
			{
				stc->is_new = 0;
			}
			else
			{
				stc->timer.Update(diff);
				if(stc->timer.Passed())
				{
					if(DOTimerTickCallBack(this, stc->s_callback, stc->param1) == 0)
						stc->invalid = 1;
					stc->timer.Reset2();
				}
			}
			++it;
		}
	}

	//�ܶ�ʱ��
	if(!m_script_timestamp_callbacks.empty())
	{
		for(ScriptTimeStampList::iterator it = m_script_timestamp_callbacks.begin(); it != m_script_timestamp_callbacks.end();)
		{
			script_timestamp_timer_callback *stc = *it;

			if(stc->invalid == 1)//�ѱ�ɾ��
			{
				m_script_timestamp_callbacks.erase(it++);
				free(stc);
				continue;
			}
			if(stc->is_new == 1)//��һ֡��ִ��
			{
				stc->is_new = 0;
			}
			else
			{	
				if(stc->timestamp > 0 && (uint32)time(NULL) >= stc->timestamp)
				{
					DOTimerTickCallBack(this, stc->s_callback, stc->param1);
					stc->invalid = 1;					
				}
				else if (stc->timestamp == 0)
				{
					stc->invalid = 1;
				}
			}
			++it;
		}
	}

	//������Ҫ�������Ϸ����������������� �ô�����Ҫ�Ŀ��Բ�������
	for (PlayerRespawnList::iterator it_p = m_player_respawn.begin();
		it_p != m_player_respawn.end();)
	{
		Player *player = FindPlayer(*it_p);
		if (player && !player->isAlive())
		{
			//TODO:������Ը��ݲ߻�Ҫ��д�����߼�
			player->Respawn();
			player->DoIfNeedAddProtectBuff();
		}
		if (player && player->isAlive())
			it_p = m_player_respawn.erase(it_p);
		else
			++it_p;
	}

	//TODO: ���Ч�ʲ�����˵ => ������Ҫgameobject
	for (GameObjectMap::iterator iter = m_gameobjects.begin();iter != m_gameobjects.end();++iter)
	{
		if (!iter->second) {
			return;
		}
		iter->second->UpdateLiveStatus(diff);
	}
}

void Map::UpdateRespan(uint32 diff)	
{
	//��������grid��
	if(!m_worldObject_toadd.empty())
	{	
		Unit *wo;
		for (auto it = m_worldObject_toadd.begin();it != m_worldObject_toadd.end();++it)
		{
			wo = *it;
			//�������Ƿ�,ֱ�Ӳ������ͼ
			if(!IsRightCoordNoCanRun(wo->GetPositionX(),wo->GetPositionY()))
			{
				tea_perror("����Ƿ�����[%s] :%u,%.2f,%.2f",wo->GetName().c_str(),GetMapId(),wo->GetPositionX(),wo->GetPositionY());
				continue;
			}

			wo->SetMap(this);
			wo->SetMapId(GetMapId());
			wo->SetInstanceId(GetInstanceID());
			if(wo->GetTypeId() == TYPEID_UNIT)
			{
				m_alive_creatures[wo->GetGuid()] = static_cast<Creature*>(wo);
			}		
			//�������,����AI�ű����Ҷ���
			if(!wo->GetAliasName().empty())
				AddAliasCreature(wo);	
			//����grid
			m_grids->AddWorldObject(wo);
		}
		m_worldObject_toadd.clear();
	}	

	//����ֻˢһ�ε��������
	if(!m_to_del_creature.empty())
	{
		for (CreatureSet::iterator it = m_to_del_creature.begin();
			it != m_to_del_creature.end();++it)
		{
			/*m_grids->DelWorldObject(*it);		
			m_alive_creatures.erase((*it)->GetGuid());			
			if(!(*it)->m_alias_name.empty())
				DelAliasCreature(*it);*/
			LeaveCreature(*it);		

			delete *it;
		}
		m_to_del_creature.clear();	
	}	

	//������Ҫɾ������Ϸ����,��̬����ȫ���ɴ˹���,��ʱֻ��ս��Ʒ
	for (GameObjectRespawnList::iterator it = m_go_dynamic.begin();
		it != m_go_dynamic.end();)
	{
		it->first -= diff;
		GameObjectMap::iterator it_go = m_gameobjects.find(it->second);
		if(it_go == m_gameobjects.end())
		{
			it = m_go_dynamic.erase(it);
			continue;
		}
		GameObject *go = it_go->second;

		//��ʱ��
		if (it->first < 0	|| (!go->IsGEAR()))		
		{
			//			
			DeleteGameObject(go);			
			it = m_go_dynamic.erase(it);
		}
		else ++it;		
	}
}

void Map::AddRespanPlayer(Player* player)
{
	//��������رճ�ʱ�����������
	if(m_is_close_respawn) return;
	m_player_respawn.push_back(player->GetUIntGuid());
}

void Map::SendCreateBlock(ScenedContext *player)
{
	SendCreateBlock(player->GetFD());
}

void Map::SendCreateBlock(uint32 fd)
{
	if (!fd)
		return;
	
	m_parent_map_info->WriteCreateBlock(m_byte_buf);
	m_byte_buf.position(0);
	ObjMgr.Compress(m_byte_buf);
	m_byte_buf.position(0);
	packet *pkt_compress = external_protocol_new_packet(SMSG_MAP_UPDATE_OBJECT);
	packet_write(pkt_compress,(char*)m_byte_buf.cur_data(),m_byte_buf.bytesAvailable());
	m_byte_buf.clear();
	update_packet_len(pkt_compress);
	pkt_compress->cid = fd;
	server_packet *dst = NULL;
	pack_packet_gate(&dst, pkt_compress);
	ScenedApp::g_app->SendToNetgd(dst);
	internal_protocol_free_packet(dst);	
	external_protocol_free_packet(pkt_compress);	
}

void Map::SendDeleteBlock(ScenedContext *player)
{
	SendDeleteBlock(player->GetFD());
}

void Map::SendDeleteBlock(uint32 fd)
{
	if (!fd)
		return;

	m_parent_map_info->WriteReleaseBlock(m_byte_buf);
	m_byte_buf.position(0);
	ObjMgr.Compress(m_byte_buf);
	m_byte_buf.position(0);
	packet *pkt_compress = external_protocol_new_packet(SMSG_MAP_UPDATE_OBJECT);
	packet_write(pkt_compress,(char*)m_byte_buf.cur_data(),m_byte_buf.bytesAvailable());
	m_byte_buf.clear();
	update_packet_len(pkt_compress);
	pkt_compress->cid = fd;
	server_packet *dst = NULL;
	pack_packet_gate(&dst, pkt_compress);
	ScenedApp::g_app->SendToNetgd(dst);
	internal_protocol_free_packet(dst);
	external_protocol_free_packet(pkt_compress);	
}

const string Map::CreateNewCreatureID()
{
	string guid = g_GuidMgr.MAKE_NEW_GUID(ObjectTypeUnit);
	return guid;
};

bool Map::IsCanRun(float x, float y)
{
	////����������
	if(x < 0.00f || y < 0.00f) return false;
	uint16 integer_x = uint16(x); 
	uint16 integer_y = uint16(y);
	//���Ȳ��ܳ�����ͼ��Χ
	if( x < 0.0f || x >= float(m_template->m_baseinfo.width))
		return false;
	if( y < 0.0f || y >= float(m_template->m_baseinfo.height))
		return false;
	////Ҳ�������ϰ���
	return m_template->IsCanRun(integer_x,integer_y);
}

bool Map::IsRightCoord(float x,float y)
{
	//���Ȳ��ܳ�����ͼ��Χ
	if( x < 0.0f || x >= float(m_template->m_baseinfo.width))
		return false;
	if( y < 0.0f || y >= float(m_template->m_baseinfo.height))
		return false;
	return true;
}

bool Map::IsRightCoordNoCanRun(float x,float y)
{
	////����������
	if(x < 0.00f || y < 0.00f) return false;
	uint16 integer_x = uint16(x); 
	uint16 integer_y = uint16(y);
	//���Ȳ��ܳ�����ͼ��Χ
	if( x < 0.0f || x >= float(m_template->m_baseinfo.width))
		return false;
	if( y < 0.0f || y >= float(m_template->m_baseinfo.height))
		return false;
	return true;
}

void Map::JoinPlayer(Player *player)
{
	ASSERT(player->GetInstanceId() == 0);
	//ASSERT(player->GetSession()->GetInstanceId() == 0);
	player->SetInstanceId(GetInstanceID());
	player->GetSession()->SetInstanceId(GetInstanceID());
	player->SetMap(this);
	m_grids->AddPlayer(player);
	m_players.insert(make_pair(player->GetGuid(), player));

	ASSERT(player->GetInstanceId() == GetInstanceID());
	ASSERT(player->GetMapId() == GetMapId());

	//����ű���Ϊ����ִ��
	if(!m_state_script.empty())
		OnJoinPlayer(this,player);
	

	player->OnJoinMap();		//��������ű�

	if(!m_state_script.empty())
		OnAfterJoinPlayer(this, player);

	if(player->GetSession())
		SendCreateBlock(player->GetSession());
}

void Map::AddGameObject(GameObject *go)
{
	ASSERT(go);	
	go->SetMap(this);
	go->SetMapId(GetMapId());
	go->SetInstanceId(GetInstanceID());

	//�ж��Ƿ��ظ�ADD
	ASSERT(m_gameobjects.find(go->GetGuid()) == m_gameobjects.end() || m_gameobjects.find(go->GetGuid())->second != go);
	//�ж�GUID�Ƿ��ظ�
	ASSERT(m_gameobjects.find(go->GetGuid()) == m_gameobjects.end());

	m_grids->AddWorldObject(go);
	m_gameobjects[go->GetGuid()] = go;

	//if (go->IsDynamic())
	//{
	//	m_go_dynamic.push_back(std::make_pair(g_Config.loot_exist_timer + go->GetInt32(GO_LOOT_EXIST_TIME_FLOAT) * 1000, go->GetGuid()));
	//}	
}

//����ս��Ʒ����
void Map::SetMapSite(float x, float y)
{
	int set_bit = int(y / m_loot_area) * m_loot_site_width + int(x / m_loot_area);
	ASSERT(set_bit < m_all_site.GetCount());
	if(m_all_site.GetBit(set_bit) == false)
	{
		m_all_site.SetBit(set_bit);
		ASSERT(m_all_enpty_count != 0);
		m_all_enpty_count--;
	}
}

//ս��Ʒ��������Ϊδ��
void Map::UnSetMapSite(float x, float y)
{
	m_all_site.UnSetBit(uint32(y / m_loot_area) * m_loot_site_width + uint32(x / m_loot_area));
	m_all_enpty_count++;
}

void Map::DeleteGameObject(GameObject *go)
{		
	ASSERT(go && go->GetMap()==this );
	//ASSERT(go->GetGrid());

	m_gameobjects.erase(go->GetGuid());	

	//��Ϊ������Ҫ���������п���δ�ɹ����뻹û��grid��Ϣ
	if(go->GetGrid())
		m_grids->DelWorldObject(go);

	//����ս��Ʒ����
	if(go->CanLoot())
	{
		UnSetMapSite(go->GetPositionX(), go->GetPositionY());
	}

	ASSERT(m_gameobjects.find(go->GetGuid()) == m_gameobjects.end());

	delete go;
}

bool Map::AddCreature(Creature *creature)
{
	if(!IsRightCoordNoCanRun(creature->GetPositionX(),creature->GetPositionY()))
		return false;
	m_worldObject_toadd.push_back(creature);
	return true;
}

Creature *Map::AddCreature(uint32 templateid,float x,float y,float toward/* = 0*/,uint32 respan_time /*= 0*/,uint32 movetype/*=0*/, uint32 npcflag/* = 0*/,const char *alias_name /*= NULL*/,bool active_grid /*= false*/,uint8 faction/*= 0*/,const char* ainame/* = 0*/, uint32 level/* = 0*/, uint32 attackType/* = 0*/)
{
	string lguid = CreateNewCreatureID();
	Creature *new_creature = new Creature;

	//��Ҫȷ����ͼ����ˢ�µ㲻ɾ��		
	if(!new_creature->Create(this,lguid,templateid,respan_time,movetype,ainame,level, attackType))
	{
		safe_delete(new_creature);
		return NULL;
	}
	new_creature->SetBornPos(x,y);
	new_creature->SetPosition(x,y);
	new_creature->SetOrientation((float)toward);

	if(alias_name != NULL && strlen(alias_name) != 0)
		new_creature->SetAliasName(alias_name);
	new_creature->SetFaction(faction);
	new_creature->Initialize();
	//����grid
	if(active_grid)
		new_creature->SetCanActiveGrid(true);
	//�¶�����������°�
	new_creature->Clear();
	//������ʧ�ܷ��ؿ�
	if(!AddCreature(new_creature))
	{
		safe_delete(new_creature);
		return NULL;
	}
	return new_creature;
}

Creature *Map::AddCreatureTravelers(string &data,float x,float y, uint32 movetype,const char *alias_name)
{

	Creature *new_creature = new Creature;

	//��Ҫȷ����ͼ����ˢ�µ㲻ɾ��		
	new_creature->Create(0,0,0);
	string int_str = data.c_str();
	string str_str = "";
	new_creature->FromString(int_str, str_str);
	new_creature->SetBornPos(x,y);
	new_creature->SetPosition(x,y);

	new_creature->SetMap(this);
	new_creature->SetMapId(GetMapId());
	new_creature->SetInstanceId(GetInstanceID());

	new_creature->Initialize();	

	//�������,����AI�ű����Ҷ���
	if(alias_name != NULL && strlen(alias_name)>0)	
		new_creature->SetAliasName(alias_name);

	//������ʧ��
	if(!AddCreature(new_creature))
		safe_delete(new_creature);

	return new_creature;
}

void Map::ToDelCreature(Creature *creature)
{	
	//Ҫ������ָ�뻹����ͼ����
	if(creature->GetHostGUID())			
		creature->SetHostGUID(NULL);	
	m_to_del_creature.insert(creature);
}

Creature* Map::FindCreature(uint32 guid)	
{	
	auto *unit = Unit::FindUnit(guid);
	if(!unit)
		return NULL;
	if(unit->GetTypeId() != TYPEID_UNIT)
		return NULL;
	return static_cast<Creature*>(unit);	
}

GameObject* Map::FindWorldObject(uint32 guid)
{
	auto *unit = Unit::FindUnit(guid);
	if(!unit)
		return NULL;
	if(unit->GetTypeId() != TYPEID_GAMEOBJECT)
		return NULL;
	return static_cast<GameObject*>(unit);
}

Unit* Map::FindUnit(uint32 guid)
{		
	Unit *unit = Unit::FindUnit(guid);
	if (!unit)
		return NULL;

	if(unit->GetMap() == this)
		return unit;

	return NULL;
}

Player* Map::FindPlayer(uint32 guid)
{
	auto *unit = Unit::FindUnit(guid);
	if(!unit)
		return NULL;
	if(unit->GetTypeId() != TYPEID_PLAYER)
		return NULL;
	return static_cast<Player*>(unit);
}

Player* Map::FindPlayer(const char* guid)
{
	ScenedContext* session = dynamic_cast<ScenedContext*>(ObjMgr.Get(guid));	
	return session?session->GetPlayer():nullptr;
}

void Map::LeavePlayer(Player *player)
{
	//������뿪��ͼʱ,����г��� Ӧ��ҲҪ����һ���¼�
	tea_pdebug("player(%s) leave mapid %u,instanceid %u",player->GetGuid().c_str(),GetMapId(),GetInstanceID());
	OnLeavePlayer(this,player);

	player->OnLeaveMap();	
	if(m_grids)
	{
		m_grids->DelPlayer(player);
	}
	else
	{
		tea_pdebug("player(%s) leave mapid , not m_grids",player->GetGuid().c_str());
	}
	//�Ƴ�
	m_players.erase(player->GetGuid());
	player->SyncUnitToPlayerData();
	ASSERT(!player->IsMoving());
	if(player->GetSession())
		SendDeleteBlock(player->GetSession());
	//��ͼ��Ϊ��
	player->SetMap(nullptr);	
	//�������뿪�ĵ�ͼ���Ǹ���,���¼Ϊ���ݿ�����
	if (player->isAlive()) {
		if(!GetMapTemp()->IsInstance() && !player->GetSession()->IsKuafuPlayer())
			player->GetSession()->SetToDBPositon(player->GetMapId(),player->GetPositionX(),player->GetPositionY());
	} else {
		//TODO: �ж��������뿪�費��Ҫ�س�
		float nx,ny;
		float x = ZHUCHENG_FUHUO_X, y = ZHUCHENG_FUHUO_Y;
		auto *mt = MapTemplate::GetMapTempalte(ZHUCHENG_DITU_ID);
		for (uint8 i=1; i<10; i++)
		{
			MovementGenerator::RandomPos(nx,ny,float(x),float(y),float(irand(1,10000)/1000));
			if(mt->IsCanRun(uint16(nx),uint16(ny)))
			{
				x = nx;
				y = ny;
				break;
			}
		}
		player->GetSession()->SetToDBPositon(ZHUCHENG_DITU_ID, x, y);
	}
}

void Map::LeaveCreature(Creature *creature)
{
	ASSERT(creature);
	if(creature->GetGrid())
		m_grids->DelWorldObject(creature);		
	m_alive_creatures.erase(creature->GetGuid());	
	
	if(!creature->GetAliasName().empty())
		DelAliasCreature(creature);	
}

//��ʼ������id�Ϳ��id
void Map::InitWaridAndKuafuType(ScenedContext* session)
{
	if(session->GetDBKuafuInfo().empty())
		return;

	m_parent_map_info->SetUInt32(MAP_INT_FIELD_KUAFU_TYPE, session->GetKuafuType());
	m_parent_map_info->SetUInt32(MAP_INT_FIELD_WARID, session->GetKuafuWarId());
}

//�㲥���ݰ�
void Map::Broadcast(packet& pkt,Unit *wo) const
{
	ASSERT(wo);
	if(!wo->GetGrid())
		return;

	wo->GetGrid()->Broadcast(pkt);
	//m_grids->Broadcast(pkt,wo->GetGrid());
}

void Map::Broadcast(packet& pkt,Player *player,bool self /*= false*/) const
{
	ASSERT(player);
	if(!player->GetGrid())
		return;

	//ȫͼ�㲥
	//if(m_broadcast_nogrid)
	//{
	//	for (PlayerSet::iterator it = m_players.begin();
	//		it != m_players.end();++it)
	//	{
	//		if(*it == player && self == false)
	//			continue;
	//		(*it)->GetSession()->SendPacket(pkt);
	//	}
	//	
	//}
	//else
	player->GetGrid()->Broadcast(pkt,player,self);
}

void Map::BroadcastMap(packet& pkt) const {
	for (auto it : m_players) {
		it.second->GetSession()->SendPacket(pkt);
	}
}

void Map::AddAliasCreature(Unit *unit)
{
	ASSERT(!unit->GetAliasName().empty());
	m_aliasObjs.insert(std::make_pair(unit->GetAliasName(),unit));
}
void Map::DelAliasCreature(Unit *unit)
{
	ASSERT(!unit->GetAliasName().empty());
	AliasObjectMMap::iterator it = m_aliasObjs.lower_bound(unit->GetAliasName());
	AliasObjectMMap::iterator end = m_aliasObjs.upper_bound(unit->GetAliasName());
	for(; it != end; ++it)
	{
		if(it->second == unit)
		{
			m_aliasObjs.erase(it);
			return;
		}
	}
}

// �ڹ��ﶪʧĿ�� �������˵�ʱ��Ż�����
void Map::ClearCreatureHitHash(uint32 uintguid) {
	this->creatureHitHash.erase(uintguid);
}

void Map::SendGridUnitFromPlayer(Player* player)
{

	Grid& grid = m_grids->GridCoord(player->GetPositionX(),player->GetPositionY());

	//��������������������Ϣ������
	grid.SendAllNoticeGridToNewPlayer(m_grids, player);
}

void Map::SendMapPkt(uint32 mapid, const string &general_id, uint8 typ, std::function<void(ByteArray&)> fun)
{
	ByteArray *bytes = ObjMgr.GridMallocByteArray();
	*bytes << 0u << mapid << general_id<< GetInstanceID() << GetMapId() << GetGeneralID() << typ ;
	if(fun)
		fun(*bytes);
	WorldPacket pkt(INTERNAL_OPT_MAP_ROUTER_PKT);
	bytes->position(0);
	packet_write(pkt.GetPktPtr(),(char*)bytes->cur_data(),bytes->bytesAvailable());
	ObjMgr.GridFreeByteArray(bytes);
	ScenedApp::g_app->SendToLogind(pkt);
}

void Map::HandleMapPkt(ByteArray &bytes)
{
	uint32 src_map_id, src_instance_id;
	string general_id, src_general_id;
	uint8 typ;
	bytes >> general_id >> src_instance_id >> src_map_id >> src_general_id >> typ;
	switch (typ)
	{
	case MAP_PKT_TYPES_CREATURE_TELEPORT:
		OnTeleportCreature(bytes);
		break;
	default:
		ASSERT(false);
		break;
	}
}

void Map::TeleportCreature(const string &guid, uint32 mapid, float x,float y, const string &general_id)
{
	uint32 uguid = atol(SUB_GUID_STR_TO_INT(guid).c_str());
	Creature *creature = dynamic_cast<Creature*>(FindCreature(uguid));
	ASSERT(creature);
	SendMapPkt(mapid, general_id, MAP_PKT_TYPES_CREATURE_TELEPORT, [creature, x, y](ByteArray &bytes){
		creature->WriteCreateBlock(bytes);
		bytes << x << y << uint8(creature->CanActiveGrid() ? 1 : 0);
	});
	ToDelCreature(creature);
}

void Map::OnTeleportCreature(ByteArray &bytes)
{
	string guid;
	uint8 flag;
	bytes >> flag >> guid;
	Creature *new_creature = new Creature;
	new_creature->ReadFrom(flag, bytes);
	string lguid = CreateNewCreatureID();
	new_creature->SetGuid(lguid);

	//��λ����Ϣ��ʼ��λ����Ϣ��������û�õ�
	uint16 path_len = bytes.readUnsignedShort();
	for (int i = 0; i < path_len; i++)
	{
		bytes.readUnsignedShort();
	}
	bytes.readFloat();
	bytes.readFloat();
	bytes.readFloat();
	//��λ����Ϣ����

	//λ����Ϣ
	new_creature->SetPosition(bytes.readFloat(), bytes.readFloat());
	//�Ƿ񼤻�grid
	new_creature->SetCanActiveGrid(bytes.readByte() != 0);
	//��ʼ������
	new_creature->Initialize();
	//�����ͼ
	AddCreature(new_creature);
}

//��ȡ������Ϸ����
void Map::GetAllGameObjectByEntry(vector<GameObject *> &vect, uint32 entry)
{
	for (GameObjectMap::iterator iter = m_gameobjects.begin();iter != m_gameobjects.end();++iter)
	{
		if (!iter->second)
			continue;
		if(entry != 0 && iter->second->GetEntry() != entry)
			continue;
		
		vect.push_back(iter->second);
	}
}

GameObject *Map::GetGameObjectByGuid(uint32 target) {
	char ch[23];
	sprintf(ch, "%c%u", ObjectTypeUnit, target);
	string teleGuid = ch;
	auto it = m_gameobjects.find(teleGuid);
	if (it == m_gameobjects.end()) {
		return nullptr;
	}
	GameObject* tele = m_gameobjects[teleGuid];

	return tele;
}


//////////////////////////////////////////////////////////////////////////
//for Map static

//��ȡ��ͼģ��ID
int Map::LuaGetMapId(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);	
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	uint32 id = 0;
	if(_m)
		id = _m->GetMapId();
	lua_pushinteger(scriptL, id);
	return 1;
}

//���õ�ͼ�ӳ�
int Map::LuaSetMapAttrBonus(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaSetMapAttrBonus map is NULL");
		return 0;
	}
	uint16 type = (uint16)LUA_TONUMBER(scriptL,2);
	uint32 mulite = (uint32)LUA_TONUMBER(scriptL,3);
	_m->m_mapAttrBonus[type] = mulite;
	return 0;
}

//���õ�ͼ�Ƿ�֧�ֻ�Ѫ
int Map::LuaSetCanRecovey(lua_State *scriptL) 
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaSetCanRecovey map is NULL");
		return 0;
	}
	_m->m_can_recovry = LUA_TOBOOLEAN(scriptL,2)?true:false;
	return 0;
}

//��ȡ��ͼ�Ƿ�֧�ֻ�Ѫ
int Map::LuaGetCanRecovey(lua_State *scriptL) 
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaSetCanRecovey map is NULL");
		return 0;
	}
	lua_pushboolean(scriptL, _m->m_can_recovry);
	return 1;
}

//�����Ƿ����ʩ��
int Map::LuaSetCanCastSpell(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaSetCanCastSpell map is NULL");
		return 0;
	}
	
	_m->m_can_castspell = LUA_TOBOOLEAN(scriptL,2)?true:false;
	return 0;
}

//����Ƿ����ʩ��
int Map::LuaGetCanCastSpell(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaGetCanCastSpell map is NULL");		
		return 0;
	}

	lua_pushboolean(scriptL, _m->m_can_castspell? 1:0);	
	return 1;
}

int Map::LuaFindSatisfiedFieldBossInstance(lua_State *scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	std::set<uint32> s_mapid;
	if (!lua_istable(scriptL, 1))
		return 0;

	int t_idx = lua_gettop(scriptL);
	lua_pushnil(scriptL);
	while(lua_next(scriptL, t_idx))
	{
		uint32 key   = (uint32)LUA_TONUMBER(scriptL, -2);
		uint32 value = (uint32)LUA_TONUMBER(scriptL, -1);
		s_mapid.insert(key);
		lua_pop(scriptL, 1);
	}

	// ���͵�lua��
	std::vector<Map *> v_map_instance = Map::FindFieldBossInstance(s_mapid);
	lua_newtable(scriptL);    /* We will pass a table */
	int i = 0;
	std::for_each(v_map_instance.begin(),v_map_instance.end(),[&i,scriptL](Map* it) {
		lua_pushnumber(scriptL, i+1);   /* Push the table index */
		lua_pushlightuserdata(scriptL, it);	
		lua_rawset(scriptL, -3);      /* Stores the pair in the table */
		i++;
	});

	return 1;
}

int Map::LuaAddCreature(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	uint32 templateid;
	float x,y,toward = 0.0f;
	uint32 respan_time = 0,movetype = 0,npcflag = 0,level = 0,attackType=0;
	vector<uint32> npcflags;
	const char *alias_name = NULL;
	bool active_grid = false;
	uint8 faction = 0;
	const char* ainame = NULL;

	//��ȡ��
	int n = lua_gettop(scriptL);	
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaAddCreature map is NULL");
		return 0;
	}

	if(lua_istable(scriptL,2))
	{
		//lua_pushnil(scriptL);
		//lua_gettable(scriptL,2);

		lua_readvalue(scriptL,"templateid",templateid);
		lua_readvalue(scriptL,"x",x);
		lua_readvalue(scriptL,"y",y);
		lua_readvalue(scriptL,"toward",toward);
		lua_readvalue(scriptL,"respan_time",respan_time);
		lua_readvalue(scriptL,"movetype",movetype);
		lua_readvalue(scriptL,"npcflag",npcflags);
		for (vector<uint32>::iterator it = npcflags.begin(); it != npcflags.end(); ++it)
		{
			npcflag = SET_BIT(npcflag, *it);
		}		
		lua_readvalue(scriptL,"alias_name",alias_name);
		lua_readvalue(scriptL,"active_grid",active_grid);
		lua_readvalue(scriptL,"faction",faction);		
		lua_readvalue(scriptL,"ainame",ainame);
		lua_readvalue(scriptL,"level",level);
		lua_readvalue(scriptL,"attackType",attackType);
	}
	else
	{
		ASSERT(n >= 4);
		templateid = (uint32)LUA_TONUMBER(scriptL,2);
		x = (float)LUA_TONUMBER(scriptL,3);
		y = (float)LUA_TONUMBER(scriptL,4);

		if( n >= 5)
			toward = (float)LUA_TONUMBER(scriptL,5);
		if(n >= 6)
			respan_time = (uint32)LUA_TONUMBER(scriptL,6);
		if(n >= 7)
			movetype = (uint32)LUA_TONUMBER(scriptL,7);
		if(n >= 8)
			npcflag = (uint32)LUA_TONUMBER(scriptL,8);
		if(n >= 9)
			alias_name = LUA_TOSTRING(scriptL,9);
		if(n >= 10)
			active_grid = LUA_TOBOOLEAN(scriptL,10)!=0;
		if(n >= 11)
			faction = (uint8)LUA_TOINTEGER(scriptL, 11);
		if(n >= 12)
			ainame = LUA_TOSTRING(scriptL,12);
	}

#ifdef DEBUG
	if(!templateid)
	{
		tea_perror("LuaAddCreature templateid==0");
		return 0;
	}
	if (!_m->IsCanRun(x,y))
	{
		tea_perror("LuaAddCreature %f,%f",x,y);
		return 0;
	}	
#endif // DEBUG

	Creature *creature = _m->AddCreature(templateid,x,y,toward,respan_time,movetype,npcflag,alias_name,active_grid,faction,ainame,level,attackType);
	if(!creature)
	{
		tea_perror("Map::LuaAddCreature creature is NULL");
		lua_pushnil(scriptL);
		return 1;
	}

	//TODO:��Ϊ���ʱ��ű�����������ƶ����ͣ���Ҫ�õ�mapָ��,���ԣ�����������һ��mapָ��	
	creature->SetMap(_m);
	lua_pushlightuserdata(scriptL,creature);

	return 1;
}

int Map::LuaAddGameObject(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	uint32 templateid;
	float x,y;

	int n = lua_gettop(scriptL);
	ASSERT(n >= 4);
	Map *_m = NULL;
	if(lua_islightuserdata(scriptL,1))
		_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	else
	{
		/*uint32 map_id = uint32(LUA_TOINTEGER(scriptL,1));
		_m = FindInstance(map_id);*/
	}
	if(!_m)
	{
		tea_perror("LuaAddGameObject map is NULL");
		return 1;
	}

	templateid = (uint32)LUA_TONUMBER(scriptL,2);
	x = (float)LUA_TONUMBER(scriptL,3);
	y = (float)LUA_TONUMBER(scriptL,4);

#ifdef DEBUG
	if (!_m->IsCanRun(x,y))
	{
		tea_perror("LuaAddGameObject %f,%f",x,y);
		return 0;
	}	
#endif // DEBUG

	//���ֱ�Ӹ����︴�ú���	
	GameObject *go = new GameObject;		
	if (!go->Create(Map::CreateNewCreatureID(),templateid))
	{
		safe_delete(go);
		lua_pushnil(scriptL);
		return 1;
	}
	go->SetPosition(x,y);

	int i =5;
	if(n >= 5)
	{
		uint32 value = uint32(LUA_TOINTEGER(scriptL, 5));
		if(go->IsGEAR())
		{
			ASSERT(value < GO_GEAR_STATUS_MAX)		
		}
		go->SetInt32(GO_FIELD_DATA, value);
	}
	if(n>=6)
	{
		uint32 value = uint32(LUA_TOINTEGER(scriptL, 6));
		go->SetInt32(GO_FIELD_DATA + 1, value);
	}
	if(n>=7)
	{
		ASSERT(!go->IsGEAR())
			uint32 value = uint32(LUA_TOINTEGER(scriptL, 7));
		go->SetInt32(GO_FIELD_DATA + 2, value);
	}
	if(n>=8)
	{
		uint32 value = uint32(LUA_TOINTEGER(scriptL, 8));
		go->SetInt32(GO_FIELD_DATA + 3, value);
	}
	if(n>=9)
	{
		uint32 value = uint32(LUA_TOINTEGER(scriptL, 9));
		go->SetBit(GO_FIELD_FLAGS,value);
	}	
	if(n>=10)
	{
		string guid = LUA_TOSTRING(scriptL, 10);
		go->SetStr(GO_STRING_FIELD_CREATED_BY, guid);
	}
	if(n>=11)
	{
		string name = LUA_TOSTRING(scriptL, 11);
		go->SetStr(GO_STRING_FIELD_CREATED_NAME, name);
	}
	_m->AddGameObject(go);
	lua_pushlightuserdata(scriptL, go);
	return 1;
}

int Map::LuaRemoveObject(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scrciiptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Map *_m = NULL;
	ASSERT(!lua_isnil(scriptL,1));
	if(lua_islightuserdata(scriptL,1))
		_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	else
	{
		/*uint32 map_id = uint32(LUA_TOINTEGER(scriptL,1));
		_m = FindInstance(map_id);*/
	}
	if(!_m)
	{
		tea_perror("LuaRemoveObject map is NULL");
		return 0;
	}
	Unit *wo = (Unit*)LUA_TOUSERDATA(scriptL,2, ObjectTypeUnit);
	if (!wo)
		return 0;

	if(wo->GetTypeId() == TYPEID_UNIT)
		_m->ToDelCreature(static_cast<Creature*>(wo));
	else if (wo->GetTypeId() == TYPEID_GAMEOBJECT)
	{
		tea_pdebug("to do delete GameObject");
		_m->DeleteGameObject(static_cast<GameObject*>(wo));
	}
	else
		tea_pwarn("LuaRemoveObject typeid is %u",wo->GetTypeId());	

	return 0;
}

int Map::LuaQueryCreature(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaQueryCreature map is NULL");
		return 0;
	}

	int entry = (int)LUA_TONUMBER(scriptL,2);

	//����ֵ
	vector<Unit *> units;	

	//�����Բ��ṩ,��ȫͼ����
	if(n >= 4)
	{
		uint16 x = (uint16)LUA_TONUMBER(scriptL,3);
		uint16 y = (uint16)LUA_TONUMBER(scriptL,4);

		//��ָ��������Χȡ������ģ��ID���ڸ���ֵ
		Grid& grid = _m->m_grids->GridCoord(x,y);		
		for (Grid::GridPtrVec::iterator it_grid = grid.notice_grid.begin();
			it_grid != grid.notice_grid.end();++it_grid)
		{
			for (Grid::CreatureList::iterator it_creature = (*it_grid)->creatures.begin();
				it_creature != (*it_grid)->creatures.end();++it_creature)
			{
				if((*it_creature)->GetEntry() == entry)
					units.push_back(*it_creature);
			}
		}
	}
	else
	{
		//ȫͼ������
		for (CreaturesMap::iterator it = _m->m_alive_creatures.begin();
			it != _m->m_alive_creatures.end();++it)
		{
			if (it->second->GetEntry() == entry)			
				units.push_back(it->second);			
		}		
	}

	return __LuaAddUnit2(scriptL,units);
}

//��ù��ﲻͬentry������
int Map::LuaGetCreatureEntryCount(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Map *_m = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);

	std::set<uint32> hash;
	int entry = 0;
	// ȫͼ������
	for (CreaturesMap::iterator it = _m->m_alive_creatures.begin();
		it != _m->m_alive_creatures.end();++it) {
			if (it->second->isAlive()) {
				hash.insert(it->second->GetEntry());
				entry = it->second->GetEntry();
			}
	}
	// �ڴ����б��
	for (Unit* addit : _m->m_worldObject_toadd) {
		if (addit->GetTypeId() == TYPEID_UNIT) {
			hash.insert(addit->GetEntry());
			entry = addit->GetEntry();
		}
	}

	lua_pushnumber(scriptL, hash.size());
	lua_pushnumber(scriptL, entry);
	return 2;
}

int Map::LuaAliasCreature(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaAliasCreature map is NULL");
		return 0;
	}
	string alias_name = LUA_TOSTRING(scriptL,2);
	if(alias_name.empty())
	{
		tea_perror("LuaAliasCreature alias_name is empty");
		return 0;
	}
	//����ֵ
	vector<Unit *> units;	
	AliasObjectMMap::iterator it = _m->m_aliasObjs.lower_bound(alias_name);
	AliasObjectMMap::iterator end = _m->m_aliasObjs.upper_bound(alias_name);
	for(; it != end; ++it)
		units.push_back(it->second);
	return __LuaAddUnit(scriptL,units);	
}

int Map::LuaAliasCreatureTable(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaAliasCreatureTable map is NULL");
		return 0;
	}
	string alias_name = LUA_TOSTRING(scriptL,2);
	if(alias_name.empty())
	{
		tea_perror("LuaAliasCreatureTable alias_name is empty");
		return 0;
	}
	//����ֵ
	vector<Unit *> units;	
	AliasObjectMMap::iterator it = _m->m_aliasObjs.lower_bound(alias_name);
	AliasObjectMMap::iterator end = _m->m_aliasObjs.upper_bound(alias_name);
	for(; it != end; ++it)
		units.push_back(it->second);
	return __LuaAddUnit2(scriptL,units);	
}

int Map::__LuaAddUnit2(lua_State *scriptL, vector<Unit *>&units)
{
	lua_newtable(scriptL);    /* We will pass a table */
	int i = 0;
	std::for_each(units.begin(),units.end(),[&i,scriptL](Unit* it){
		if(it->GetMap())
		{
			lua_pushnumber(scriptL, i+1);   /* Push the table index */
			lua_pushlightuserdata(scriptL,it);	
			lua_rawset(scriptL, -3);      /* Stores the pair in the table */
			i++;
		}
	});
	return 1;
}

int Map::__LuaAddUnit(lua_State *scriptL, vector<Unit *>&units)
{
	int i = 0;
	for(vector<Unit *>::iterator iter = units.begin(); iter != units.end(); ++iter)
	{		
		lua_pushlightuserdata(scriptL,*iter);
		i++;
	}
	ASSERT(units.size() < 32);
	return (int32)units.size();
}

void Map::GetCircleTargetsByPos(Map *map,float center_x, float center_y, float radius,vector<Unit *> &units, Spell_Target_Type TargetType)
{
	float radius2	= radius * radius;
	units.clear();
	if (!map->IsRightCoord(center_x,center_y))
		return;
	Grid * grid = &(map->m_grids->GridCoord(center_x,center_y));//unit->GetGrid(), *t_grid = NULL;	
	Grid* t_grid = NULL;
	Grid::GridPtrVec::size_type s = grid->notice_grid.size();
	uint8 mark[9];
	memset(mark, 0, sizeof(mark));
	float tx = 0, ty = 0;
	for(uint32 c = 0; c < s; ++c)
	{
		t_grid =  grid->notice_grid[c];
		//grid ��Բ�����
		if(center_x > t_grid->end_x)
		{
			tx = center_x - t_grid->end_x;
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				ty = center_y - t_grid->end_y;
				if(tx*tx + ty*ty  < radius2)
				{
					mark[c] = 1;
				}
			}
			else if(center_y > t_grid->start_y)  // Բ����grid�м�
			{
				if(tx < radius)
				{
					mark[c] = 1;
				}
			}
			else //grid ��Բ���²�
			{
				ty = t_grid->start_y - center_y;
				if(tx*tx + ty*ty  < radius2)
				{
					mark[c] = 1;
				}
			}
		}
		else if(center_x >= t_grid->start_x) //Բ�� grid ���м�
		{
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				if(center_y - t_grid->end_y < radius) mark[c] = 1;
			}
			else if(center_y > t_grid->start_y)  // Բ����grid�м�
			{
				mark[c] = 1;
			}
			else
			{
				if(t_grid->start_y - center_y < radius) mark[c] = 1;
			}
		}
		else// grid ��Բ���Ҳ�
		{
			tx = t_grid->start_x - center_x;
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				ty = center_y - t_grid->end_y;
				if(tx*tx + ty*ty  < radius2)
				{
					mark[c] = 1;
				}
			}
			else if(center_y > t_grid->start_y)  // Բ����grid�м�
			{
				if(tx < radius) mark[c] = 1;
			}
			else 
			{
				ty = t_grid->start_y - center_y;
				if(tx*tx + ty*ty  < radius2)
				{
					mark[c] = 1;
				}
				break;
			}
		}
	}
	//units.clear();
	for(int i = 0; i < 9; ++i)
	{
		if(mark[i])
		{
			t_grid = grid->notice_grid[i];
			if(TargetType==TARGET_TYPE_ALL || TargetType==TARGET_TYPE_PLAYER)
			{
				PlayerSet::iterator piter = t_grid->players.begin();
				while(piter != t_grid->players.end())
				{
					if(	(*piter)->isAlive() &&
						(*piter)->GetDistance(center_x, center_y) < radius)
					{
						units.push_back(*piter);
					}
					++piter;
				}
			}
			if(TargetType==TARGET_TYPE_ALL || TargetType==TARGET_TYPE_CREATURE)
			{
				Grid::CreatureList::iterator citer = t_grid->creatures.begin();
				while(citer != t_grid->creatures.end())
				{
					if((*citer)->isAlive() 
						&& (*citer)->GetDistance(center_x, center_y) < radius
						&& !(*citer)->isServiceProvider())
					{
						units.push_back(*citer);
					}
					++citer;
				}				
			}
		}
	}
}

void Map::GetCircleTargets(float center_x, float center_y, float radius, Unit* unit, vector<Unit *> &units, Spell_Target_Type TargetType, bool dis_sort)
{
	float radius2	= radius * radius;
	Grid* grid = unit->GetGrid(), *t_grid = NULL;	
	Grid::GridPtrVec::size_type s = grid->notice_grid.size();
	uint8 mark[9];
	memset(mark, 0, sizeof(mark));
	float tx = 0, ty = 0;
	for(uint32 c = 0; c < s; ++c)
	{
		t_grid =  grid->notice_grid[c];
		//grid ��Բ�����
		if(center_x > t_grid->end_x)
		{
			tx = center_x - t_grid->end_x;
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				ty = center_y - t_grid->end_y;
				if(tx*tx + ty*ty  < radius2)
				{
					mark[c] = 1;
				}
			}
			else if(center_y > t_grid->start_y)  // Բ����grid�м�
			{
				if(tx < radius)
				{
					mark[c] = 1;
				}
			}
			else //grid ��Բ���²�
			{
				ty = t_grid->start_y - center_y;
				if(tx*tx + ty*ty  < radius2)
				{
					mark[c] = 1;
				}
			}
		}
		else if(center_x >= t_grid->start_x) //Բ�� grid ���м�
		{
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				if(center_y - t_grid->end_y < radius) mark[c] = 1;
			}
			else if(center_y > t_grid->start_y)  // Բ����grid�м�
			{
				mark[c] = 1;
			}
			else
			{
				if(t_grid->start_y - center_y < radius) mark[c] = 1;
			}
		}
		else// grid ��Բ���Ҳ�
		{
			tx = t_grid->start_x - center_x;
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				ty = center_y - t_grid->end_y;
				if(tx*tx + ty*ty  < radius2)
				{
					mark[c] = 1;
				}
			}
			else if(center_y > t_grid->start_y)  // Բ����grid�м�
			{
				if(tx < radius) mark[c] = 1;
			}
			else 
			{
				ty = t_grid->start_y - center_y;
				if(tx*tx + ty*ty  < radius2)
				{
					mark[c] = 1;
				}
				break;
			}
		}
	}
	units.clear();
	for(int i = 0; i < 9; ++i)
	{
		if(mark[i])
		{
			t_grid = grid->notice_grid[i];
			PlayerSet::iterator piter = t_grid->players.begin();
			while(piter != t_grid->players.end())
			{
				if(	(*piter)->isAlive() &&
					(*piter)->GetDistance(center_x, center_y) < radius)
				{
					switch(TargetType)
					{
					case TARGET_TYPE_ALL:
						units.push_back(*piter);
						break;
					case TARGET_TYPE_FRIENDLY:
						if(unit->IsFriendlyTo(*piter)) units.push_back(*piter);
						break;
					case TARGET_TYPE_ENEMY:
						if(!unit->IsFriendlyTo(*piter)) units.push_back(*piter);
						break;
					default:
						break;
					}
				}
				++piter;
			}
			Grid::CreatureList::iterator citer = t_grid->creatures.begin();
			while(citer != t_grid->creatures.end())
			{
				if((*citer)->isAlive() && (*citer)->GetDistance(center_x, center_y) < radius)
				{
					switch(TargetType)
					{
					case TARGET_TYPE_ALL:
						units.push_back(*citer);
						break;
					case TARGET_TYPE_FRIENDLY:
						if(unit->IsFriendlyTo(*citer)) units.push_back(*citer);
						break;
					case TARGET_TYPE_ENEMY:
						if(!unit->IsFriendlyTo(*citer)) units.push_back(*citer);
						break;
					default:
						break;
					}
				}
				++citer;
			}
		}
	}
	if(dis_sort)
	{
		//����������
		std::sort(units.begin(), units.end(),[&unit](const Unit *left, const Unit *rigth){
			float left_dis = unit->GetDistance(left);
			float right_dis = unit->GetDistance(rigth);
			return left_dis < right_dis;
		});
	}
}

//��ȡ����Ŀ��
void Map::GetRectTargets(Unit* unit,float start_x, float start_y, float end_x, float end_y, vector<Unit *> &units, Spell_Target_Type TargetType)
{
	Grid* grid = unit->GetGrid(), *t_grid = NULL;	
	Grid::GridPtrVec::size_type s = grid->notice_grid.size();
	uint8 mark[9];
	memset(mark, 0, sizeof(mark));
	for(uint32 c = 0; c < s; ++c)
	{
		t_grid =  grid->notice_grid[c];
		//���ϵ���grid��
		if(!t_grid->IsNotInThisGrid((int)start_x, (int)start_y))
		{
			mark[c] = 1;
		}
		else if(!t_grid->IsNotInThisGrid((int)start_x, (int)end_y))
		{
			mark[c] = 1;
		}
		else if(!t_grid->IsNotInThisGrid((int)end_x, (int)start_y))
		{
			mark[c] = 1;
		}
		else if(!t_grid->IsNotInThisGrid((int)end_x, (int)end_y))
		{
			mark[c] = 1;
			break;
		}
	}
	float dx = 0;
	float dy = 0;
	for(int i = 0; i < 9; ++i)
	{
		if(mark[i])
		{
			t_grid = grid->notice_grid[i];
			PlayerSet::iterator piter = t_grid->players.begin();
			while(piter != t_grid->players.end())
			{
				if((*piter)->isAlive())
				{
					dx = (*piter)->GetPositionX();
					dy = (*piter)->GetPositionY();
					if(dx < end_x && dx >= start_x && dy < end_y && dy >= start_y)
					{
						switch(TargetType)
						{
						case TARGET_TYPE_ALL:
							units.push_back(*piter);
							break;
						case TARGET_TYPE_FRIENDLY:
							if(unit->IsFriendlyTo(*piter)) units.push_back(*piter);
							break;
						case TARGET_TYPE_ENEMY:
							if(!unit->IsFriendlyTo(*piter)) units.push_back(*piter);
							break;
						default:
							break;
						}
					}
				}
				++piter;
			}
			Grid::CreatureList::iterator citer = t_grid->creatures.begin();
			while(citer != t_grid->creatures.end())
			{
				if((*citer)->isAlive())
				{
					dx = (*citer)->GetPositionX();
					dy = (*citer)->GetPositionY();
					if(dx < end_x && dx >= start_x && dy < end_y && dy >= start_y)
					{
						switch(TargetType)
						{
						case TARGET_TYPE_ALL:
							units.push_back(*citer);
							break;
						case TARGET_TYPE_FRIENDLY:
							if(unit->IsFriendlyTo(*citer)) units.push_back(*citer);
							break;
						case TARGET_TYPE_ENEMY:
							if(!unit->IsFriendlyTo(*citer)) units.push_back(*citer);
							break;
						default:
							break;
						}
					}
				}
				++citer;
			}
		}
	}
}
//���һ����ʱ������ͼ����
int Map::LuaAddTimer(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//��ȡ�ò���
	int n = lua_gettop(scriptL);
	ASSERT(n >= 3);
	Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	ASSERT(map);
	const char *callback_name = LUA_TOSTRING(scriptL, 2); 
	time_t interval = time_t(LUA_TONUMBER(scriptL,3));
	uint64 param1 = 0;


	script_timer_callback *stc;
	stc = (script_timer_callback*)malloc(sizeof(script_timer_callback));
	//memset(stc, 0, sizeof(script_timer_callback));
	stc->invalid = 0;
	strcpy(stc->s_callback, callback_name);
	stc->timer.SetInterval(interval);
	stc->timer.SetCurrent(0);
	stc->is_new = 1;
	for (int i = 0; i < 10; i ++)
	{
		if(n > 3 + i)
		{
			uint32 index = 4 + i;
			if(lua_islightuserdata(scriptL, index) || lua_isnil(scriptL, index))
			{
				if(lua_isnil(scriptL, index))
					stc->param1[i].ptr = NULL;
				else
					stc->param1[i].ptr = lua_touserdata(scriptL,index);
				stc->param1[i].type = LUA_TUSERDATA;
			}
			else if(lua_type(scriptL, index) == LUA_TSTRING)
			{
				strcpy(stc->param1[i].str, LUA_TOSTRING(scriptL, index));
				stc->param1[i].type = LUA_TSTRING;
			}
			else
			{
				stc->param1[i].l_val = LUA_TONUMBER(scriptL, index);
				stc->param1[i].type = LUA_TNUMBER;
			}
		}
		else
		{
			stc->param1[i].value = 0;
			stc->param1[i].type = LUA_TNONE;
		}
	}
	stc->id = ++map->m_script_callback_key;			//���ص���������
	map->m_script_callbacks.push_back(stc);
	lua_pushinteger(scriptL,stc->id);				//����key
	return 1;
}

//���һ��ʱ�����ʱ������ͼ����
int Map::LuaAddTimeStampTimer(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//��ȡ�ò���
	int n = lua_gettop(scriptL);
	ASSERT(n >= 3);
	Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	ASSERT(map);
	const char *callback_name = LUA_TOSTRING(scriptL, 2); 
	uint32 timestamp = (uint32)LUA_TONUMBER(scriptL,3);
	uint64 param1 = 0;


	script_timestamp_timer_callback *stc;
	stc = (script_timestamp_timer_callback*)malloc(sizeof(script_timestamp_timer_callback));
	//memset(stc, 0, sizeof(script_timer_callback));
	stc->invalid = 0;
	strcpy(stc->s_callback, callback_name);
	stc->timestamp = timestamp;
	stc->is_new = 1;
	for (int i = 0; i < 10; i ++)
	{
		if(n > 3 + i)
		{
			uint32 index = 4 + i;
			if(lua_islightuserdata(scriptL, index) || lua_isnil(scriptL, index))
			{
				if(lua_isnil(scriptL, index))
					stc->param1[i].ptr = NULL;
				else
					stc->param1[i].ptr = lua_touserdata(scriptL,index);
				stc->param1[i].type = LUA_TUSERDATA;
			}
			else
			{
				stc->param1[i].l_val = LUA_TONUMBER(scriptL, index);
				stc->param1[i].type = LUA_TNUMBER;
			}
		}
		else
		{
			stc->param1[i].value = 0;
			stc->param1[i].type = LUA_TNONE;
		}
	}
	stc->id = ++map->m_script_callback_key;			//���ص���������
	map->m_script_timestamp_callbacks.push_back(stc);
	lua_pushinteger(scriptL,stc->id);				//����key
	return 1;
}

//ɾ��һ����ʱ��
int Map::LuaDelTimer(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);	
	if(!map)
	{
		tea_perror("LuaDelTimer map is NULL");
		return 0;
	}
	//����ص���������
	if(lua_isstring(scriptL, 2))
	{
		//���е��ڸûص����Ƶ�ȫ���ؿ�
		const char *callback_name = LUA_TOSTRING(scriptL, 2); 
		std::for_each(map->m_script_callbacks.begin(),map->m_script_callbacks.end(),
			[callback_name](script_timer_callback *stc){
				if(strcmp(stc->s_callback,callback_name) == 0)
					stc->invalid = 1;
		});
	}
	else
	{
		int id = (int)LUA_TOINTEGER(scriptL,2);
		for (auto it = map->m_script_callbacks.begin(); it != map->m_script_callbacks.end(); ++it)
		{
			if((*it)->id == id)
			{
				(*it)->invalid = 1;
				break;
			}
		}		
	}
	return 0;
}

//ɾ��һ��ʱ�����ʱ��
int Map::LuaDelTimeStampTimer(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);	
	if(!map)
	{
		tea_perror("LuaDelTimeStampTimer map is NULL");
		return 0;
	}
	//����ص���������
	if(lua_isstring(scriptL, 2))
	{
		//���е��ڸûص����Ƶ�ȫ���ؿ�
		const char *callback_name = LUA_TOSTRING(scriptL, 2); 
		std::for_each(map->m_script_timestamp_callbacks.begin(),map->m_script_timestamp_callbacks.end(),
			[callback_name](script_timestamp_timer_callback *stc){
				if(strcmp(stc->s_callback,callback_name) == 0)
					stc->invalid = 1;
		});
	}
	else
	{
		int id = (int)LUA_TOINTEGER(scriptL,2);
		for (auto it = map->m_script_timestamp_callbacks.begin(); it != map->m_script_timestamp_callbacks.end(); ++it)
		{
			if((*it)->id == id)
			{
				(*it)->invalid = 1;
				break;
			}
		}		
	}
	return 0;
}


//��ȡ��ͼ����
int Map::LuaGetPlayersCounts(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);	
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);	
	if(!_m)
	{
		tea_perror("LuaGetPlayersCounts map is NULL");
		return 0;
	}
	uint32 count = _m->GetPlayerCount();
	lua_pushnumber(scriptL,count);
	return 1;
}

//���
int Map::LuaRandomPos(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);

	const MapTemplate *mt = NULL;
	if(lua_islightuserdata(scriptL,1))
	{
		Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
		if(_m) mt = _m->GetMapTemp();
	}
	else
	{
		uint32 mapid = (uint32)LUA_TOINTEGER(scriptL,1);
		mt = MapTemplate::GetMapTempalte(mapid);
	}

	if(!mt)
	{
		tea_perror("LuaRandomPos map is NULL");
		return 0;
	}

	//��Ҫ����ĵ�����
	int pos_num = 1;
	if(n > 1)
		pos_num = (int)LUA_TOINTEGER(scriptL,2);	

	//�ڴ����긽��
	bool need_check_pos = (n >= 5);
	uint16 fPosX,fPosY,fDist;
	if(need_check_pos)
	{
		fPosX = (uint16)LUA_TONUMBER(scriptL,3);
		fPosY = (uint16)LUA_TONUMBER(scriptL,4);
		fDist = (uint16)LUA_TONUMBER(scriptL,5);		
	}else ASSERT(0);
		
	vector<uint16> points;

	//�����ʼ�ĵ㲻��·�Ͼ��������Ȼ�Ļ���ֻ�ܰ�ԭ�㻹������
	if(mt->IsCanRun(uint16(fPosX),uint16(fPosY)))
	{
		int num = 0;
		for(int i=0; num < pos_num; i++)
		{
			ASSERT(i<10000);		//��û�и��,ѭ��һ��λ�û�������

			//����������Χ�����3����
			uint16 x,y;
			//MovementGenerator::RandomPos(x,y,fPosX,fPosY,fDist);
			x = fPosX+irand(-1*fDist,fDist);
			y = fPosY+irand(-1*fDist,fDist);

			//��֤һ�¸õ��в���
			if(!mt->IsCanRun(float(fPosX),float(fPosY),uint16(x),uint16(y)))
				continue;

			//���ɵĵ�֮����벻����̫��
			bool be_close_to = false;
			for (auto it = points.begin();it != points.end();it = it + 2)
			{
				if(GetDistance(*it,*(it+1),x,y) < 1.0f)
				{
					be_close_to = true;
					break;
				}
			}

			//tea_pdebug("new pos:%f,%f",x,y);
			if(!be_close_to)
			{
				ASSERT(mt->IsCanRun(uint16(x),uint16(y)));
				points.push_back(x);
				points.push_back(y);
				num++;
			}				
		}	
	}
	else
	{
		for(int i=0; i < pos_num; i++)
		{
			points.push_back(fPosX);
			points.push_back(fPosY);
		}
	}


	lua_newtable(scriptL);    /* We will pass a table */
	for(uint32 i=0; i < points.size(); i++)
	{
		lua_pushnumber(scriptL, i+1);   /* Push the table index */
		lua_pushnumber(scriptL,points[i]);	
		lua_rawset(scriptL, -3);      /* Stores the pair in the table */
	}
	return 1;
}


//��ȡ��ͼ�ڵ��������
int Map::LuaGetAllPlayer(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);	
	if(!_m)
	{
		tea_perror("LuaGetAllPlayer map is NULL");
		return 0;
	}
	lua_newtable(scriptL);    /* We will pass a table */
	PlayerMap players = _m->GetPlayers();

	uint32 i = 1; 
	for (PlayerMap::iterator iter = players.begin();iter != players.end();++iter)
	{
		if (!iter->second)
			continue;
		lua_pushnumber(scriptL, i);   /* Push the table index */
		lua_pushlightuserdata(scriptL,iter->second);	
		lua_rawset(scriptL, -3);   
		i++;
	}
	return 1;
}


//��ȡ���й���
int Map::LuaGetAllCreature(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaGetAllCreature map is NULL");
		return 0;
	}
	int entry  = 0;
	if(n >= 2)
		entry = (int)LUA_TONUMBER(scriptL,2);

	//����ֵ
	vector<Unit *> units;	

	//�����Բ��ṩ,��ȫͼ����
	if(n >= 4)
	{
		uint16 x = (uint16)LUA_TONUMBER(scriptL,3);
		uint16 y = (uint16)LUA_TONUMBER(scriptL,4);

		//��ָ��������Χȡ������ģ��ID���ڸ���ֵ
		Grid& grid = _m->m_grids->GridCoord(x,y);		
		for (Grid::GridPtrVec::iterator it_grid = grid.notice_grid.begin();
			it_grid != grid.notice_grid.end();++it_grid)
		{
			for (Grid::CreatureList::iterator it_creature = (*it_grid)->creatures.begin();
				it_creature != (*it_grid)->creatures.end();++it_creature)
			{
				if((*it_creature)->GetEntry() == entry && (*it_creature)->isAlive())
					units.push_back(*it_creature);
			}
		}
	}
	else
	{
		//ȫͼ������
		for (CreaturesMap::iterator it = _m->m_alive_creatures.begin();
			it != _m->m_alive_creatures.end();++it)
		{
			if (it->second->isAlive())	
			{
				if(entry != 0)
				{
					if (it->second->GetEntry() == entry)
						units.push_back(it->second);
				}
				else
				{
					units.push_back(it->second);	
				}
			}
		}		
	}

	return __LuaAddUnit2(scriptL,units);	
}

//�����Ϸ����
int Map::LuaGetGameOject(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 1);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaGetGameOject map is NULL");
		return 0;
	}

	if(n==2)//���ĳ��ģ��ս��Ʒ
	{
		uint32 entry = (uint32)LUA_TONUMBER(scriptL,2);
		//ȫͼ������
		for (GameObjectMap::iterator it = _m->m_gameobjects.begin();
			it != _m->m_gameobjects.end();++it)
		{
			if (it->second->GetEntry() == entry)	
			{
				lua_pushlightuserdata(scriptL, it->second);
				return 1;
			}
		}
	}
	else//���ȫͼ����ս��Ʒ
	{
		lua_newtable(scriptL);    /* We will pass a table */
		//ȫͼ������
		uint32 i = 1; 
		for (GameObjectMap::iterator iter = _m->m_gameobjects.begin();iter != _m->m_gameobjects.end();++iter)
		{
			if (!iter->second)
				continue;
			lua_pushnumber(scriptL, i);   /* Push the table index */
			lua_pushlightuserdata(scriptL,iter->second);	
			lua_rawset(scriptL, -3);   
			i++;
		}
		return 1;
	}

	lua_pushnil(scriptL);
	return 1; 
}

//���������Ϸ����
int Map::LuaGetAllGameObject(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 1);
	Map *_m = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	if(!_m)
	{
		tea_perror("LuaGetAllGameObject map is NULL");
		return 0;
	}
	//ȫͼ������
	uint32 i = 1; 
	uint32 entry = 0;
	if(n==2)//���ĳ��ģ��ս��Ʒ
	{
		 entry = (uint32)LUA_TONUMBER(scriptL,2);
	}
	lua_newtable(scriptL);    /* We will pass a table */
		
	for (GameObjectMap::iterator iter = _m->m_gameobjects.begin();iter != _m->m_gameobjects.end();++iter)
	{
		if (!iter->second)
			continue;
		if(entry != 0 && iter->second->GetEntry() != entry)  continue;
		lua_pushnumber(scriptL, i);   /* Push the table index */
		lua_pushlightuserdata(scriptL,iter->second);	
		lua_rawset(scriptL, -3);   
		i++;
	}

	return 1; 
}


int Map::LuaGetCircleTargets(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 5);
	bool dis_sort = false;
	//Բ�ļӰ뾶
	float center_x	= (float)LUA_TONUMBER(scriptL,1);
	float center_y	= (float)LUA_TONUMBER(scriptL,2);
	float radius	= (float)LUA_TONUMBER(scriptL,3);
	vector<Unit *> units;
	Unit* unit = (Unit*)LUA_TOUSERDATA(scriptL, 4, ObjectTypeUnit);
	if (!unit)
	{
		tea_pdebug("LuaGetCircleTargets unit is NULL");
		return 0;
	}
	Spell_Target_Type type = (Spell_Target_Type)(int)LUA_TONUMBER(scriptL,5);
	if(n >= 6)
	{
		dis_sort = LUA_TOBOOLEAN(scriptL, 6) != FALSE;
	}
	Map::GetCircleTargets(center_x, center_y, radius, unit, units, type, dis_sort);
	return __LuaAddUnit2(scriptL, units);
}

int Map::LuaGetCircleTargetsByPos(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	ASSERT(lua_gettop(scriptL) == 5);
	Map* map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	if (!map)
	{
		tea_pdebug("LuaGetCircleTargetsByPos ERROR");
		return 0;
	}
	//Բ�ļӰ뾶
	float center_x	= (float)LUA_TONUMBER(scriptL,2);
	float center_y	= (float)LUA_TONUMBER(scriptL,3);
	float radius	= (float)LUA_TONUMBER(scriptL,4);
	Spell_Target_Type type = (Spell_Target_Type)(int)LUA_TONUMBER(scriptL,5);
	std::vector<Unit *> units;
	Map::GetCircleTargetsByPos(map,center_x, center_y, radius, units, type);

	//ȥ��У��
	std::sort(units.begin(),units.end());
	auto it_unique = std::unique(units.begin(),units.end());
	if(it_unique != units.end())
	{
		tea_perror("grid find unit have repeat");
		units.erase(it_unique,units.end());
	}

	return __LuaAddUnit2(scriptL, units);	
}


int Map::LuaGetRectTargets(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	ASSERT(lua_gettop(scriptL) == 6);
	//���ε����º�����(start_x < end_x start_y < end_y)
	float start_x	= (float)LUA_TONUMBER(scriptL,1);
	float end_y		= (float)LUA_TONUMBER(scriptL,2);
	float end_x		= (float)LUA_TONUMBER(scriptL,3);
	float start_y	= (float)LUA_TONUMBER(scriptL,4);

	Unit* unit = (Unit*)LUA_TOUSERDATA(scriptL,5, ObjectTypeUnit);
	if (!unit)
	{
		tea_perror("error: LuaGetRectTargets unit = null");
		return 0;
	}
	Spell_Target_Type TargetType = (Spell_Target_Type)(int)LUA_TONUMBER(scriptL,6);
	vector<Unit *> units;
	//���ε����Ϻ�����(start_x < end_x start_y < end_y)
	Map::GetRectTargets(unit, start_x, start_y, end_x, end_y, units, TargetType);
	
	return __LuaAddUnit2(scriptL, units);
}

//��ȡб���ε�Ŀ��
int Map::LuaGetObliqueRectTargets(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	ASSERT(lua_gettop(scriptL) == 7);
	//���ε����º�����
	float cas_x = (float)LUA_TONUMBER(scriptL,1);
	float cas_y = (float)LUA_TONUMBER(scriptL,2);
	float dst_x	= (float)LUA_TONUMBER(scriptL,3);
	float dst_y	= (float)LUA_TONUMBER(scriptL,4);
	Unit* unit = (Unit*)LUA_TOUSERDATA(scriptL,5, ObjectTypeUnit);
	if (!unit)
	{
		tea_perror("error: LuaGetRectTargets unit = null");
		return 0;
	}
	Spell_Target_Type TargetType = (Spell_Target_Type)(int)LUA_TONUMBER(scriptL,6);
	float d = (float)LUA_TONUMBER(scriptL,7);		// ƽ�о���
	vector<Unit *> units;
	if(cas_x == dst_x)
	{
		//���ε����Ϻ�����(start_x < end_x start_y < end_y)
		if(cas_y < dst_y)
			Map::GetRectTargets(unit, cas_x-d, cas_y, dst_x+d, dst_y, units, TargetType);
		else
			Map::GetRectTargets(unit, cas_x-d, dst_y, dst_x+d, cas_y, units, TargetType);
		return __LuaAddUnit2(scriptL, units);
	}
	else if(cas_y == dst_y)
	{
		//���ε����Ϻ�����(start_x < end_x start_y < end_y)
		if(cas_x < dst_x)
			Map::GetRectTargets(unit, cas_x, cas_y-d, dst_x, dst_y+d, units, TargetType);
		else
			Map::GetRectTargets(unit, dst_x, cas_y-d, cas_x, dst_y+d, units, TargetType);
		return __LuaAddUnit2(scriptL, units);
	}
	//�����б��
	float k = (cas_y-dst_y)/(cas_x-dst_x);
	float b = dst_y-(cas_y-dst_y)*dst_x/(cas_x-dst_x);
	// �����4��������
	float x1 = sqrt(d*d/(k*k+1));
	float x2 = -x1;
	float y1 = k*x1;
	float y2 = k*x2;
	float b1 = b+x1;
	float b2 = b+x2;	//k*x-y+c=0
	float c1 = 1/k*dst_x+dst_y;
	float c2 = 1/k*cas_x+cas_y;	//1/k*x+y-c=0
	if(b1 < b2)
	{
		float tb = b1;
		b1 = b2;
		b2 = tb;
	}
	if(c1 > c2)
	{
		float tc = c1;
		c1 = c2;
		c2 = tc;
	}
	vector<float> posx;  
	posx.push_back(dst_x+x1);  
	posx.push_back(dst_x+x2);
	posx.push_back(cas_x+x1);
	posx.push_back(cas_x+x2);
	sort(posx.begin(), posx.end());
	vector<float> posy;  
	posy.push_back(dst_y+y1);  
	posy.push_back(dst_y+y2);
	posy.push_back(cas_y+y1);
	posy.push_back(cas_y+y2);
	sort(posy.begin(), posy.end());
	float start_x = posx[0];
	float start_y = posy[0];
	float end_x	= posx[3];
	float end_y	= posy[3];

	Grid* grid = unit->GetGrid(), *t_grid = NULL;	
	Grid::GridPtrVec::size_type s = grid->notice_grid.size();
	uint8 mark[9];
	memset(mark, 0, sizeof(mark));
	for(uint32 c = 0; c < s; ++c)
	{
		t_grid =  grid->notice_grid[c];
		//���ϵ���grid��
		if(!t_grid->IsNotInThisGrid((int)start_x, (int)start_y))
		{
			mark[c] = 1;
		}
		else if(!t_grid->IsNotInThisGrid((int)start_x, (int)end_y))
		{
			mark[c] = 1;
		}
		else if(!t_grid->IsNotInThisGrid((int)end_x, (int)start_y))
		{
			mark[c] = 1;
		}
		else if(!t_grid->IsNotInThisGrid((int)end_x, (int)end_y))
		{
			mark[c] = 1;
			break;
		}
	}
	float dx = 0;
	float dy = 0;
	float n1 = 0;
	float n2 = 0;
	float n3 = 0;
	float n4 = 0;
	for(int i = 0; i < 9; ++i)
	{
		if(mark[i])
		{
			t_grid = grid->notice_grid[i];
			PlayerSet::iterator piter = t_grid->players.begin();
			while(piter != t_grid->players.end())
			{
				if((*piter)->isAlive())
				{
					dx = (*piter)->GetPositionX();
					dy = (*piter)->GetPositionY();
					n1 = k*dx-dy+b1;
					n2 = k*dx-dy+b2;
					n3 = 1/k*dx+dy-c1;
					n4 = 1/k*dx+dy-c2;
					if(n1 >= 0 && n2 <= 0 && n3 >= 0 && n4 <= 0)
					{
						switch(TargetType)
						{
						case TARGET_TYPE_ALL:
							units.push_back(*piter);
							break;
						case TARGET_TYPE_FRIENDLY:
							if(unit->IsFriendlyTo(*piter)) units.push_back(*piter);
							break;
						case TARGET_TYPE_ENEMY:
							if(!unit->IsFriendlyTo(*piter)) units.push_back(*piter);
							break;
						default:
							break;
						}
					}
				}
				++piter;
			}
			Grid::CreatureList::iterator citer = t_grid->creatures.begin();
			while(citer != t_grid->creatures.end())
			{
				if((*citer)->isAlive())
				{
					dx = (*citer)->GetPositionX();
					dy = (*citer)->GetPositionY();
					n1 = k*dx-dy+b1;
					n2 = k*dx-dy+b2;
					n3 = 1/k*dx+dy-c1;
					n4 = 1/k*dx+dy-c2;
					if(n1 >= 0 && n2 <= 0 && n3 >= 0 && n4 <= 0)
					{
						switch(TargetType)
						{
						case TARGET_TYPE_ALL:
							units.push_back(*citer);
							break;
						case TARGET_TYPE_FRIENDLY:
							if(unit->IsFriendlyTo(*citer)) units.push_back(*citer);
							break;
						case TARGET_TYPE_ENEMY:
							if(!unit->IsFriendlyTo(*citer)) units.push_back(*citer);
							break;
						default:
							break;
						}
					}
				}
				++citer;
			}
		}
	}
	return __LuaAddUnit2(scriptL, units);
}

float Map::__GetAngle(const float x1, const float y1, const float x2, const float y2)
{
	float ang = atan2(y2-y1, x2-x1);
	ang = (ang >= 0) ? ang : 2 * M_PI + ang;
	return ang;
}

int Map::LuaGetFanshapedTargets(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	//LuaStackAutoPopup autoPopup(scriptL);
	ASSERT(lua_gettop(scriptL) == 7);
	//Բ�ģ�����
	float center_x	= (float)LUA_TONUMBER(scriptL,1);
	float center_y	= (float)LUA_TONUMBER(scriptL,2);
	float radius	= (float)LUA_TONUMBER(scriptL,3);
	float radian	= (float)LUA_TONUMBER(scriptL,4);
	float orientation	= (float)LUA_TONUMBER(scriptL,5);
	Unit* unit = (Unit*)LUA_TOUSERDATA(scriptL,6, ObjectTypeUnit);
	Spell_Target_Type TargetType = (Spell_Target_Type)(int)LUA_TONUMBER(scriptL,7);

	float start_radian = orientation - radian/2;
	float end_radian = start_radian + radian;
	Grid* grid = unit->GetGrid(), *t_grid = NULL;	
	Grid::GridPtrVec::size_type s = grid->notice_grid.size();
	uint8 mark[9];
	float ang;
	float tx = 0, ty = 0;
	float radius2	= radius * radius;
	float _s = 0;

	memset(mark, 0, sizeof(mark));

	for(uint32 c = 0; c < s; ++c)
	{
		t_grid = grid->notice_grid[c];
		//grid ��Բ�����
		if(center_x > t_grid->end_x)
		{
			tx = center_x - t_grid->end_x;
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->end_x, (float)t_grid->end_y);
				ty = center_y - t_grid->end_y;
				if(ang >= start_radian && ang <= end_radian)
				{
					if(tx * tx + ty * ty <  radius2)
					{
						mark[c] = 1;
					}
				}
				else if(ang < start_radian)
				{
					_s = fabs(cos(start_radian));
					if(_s && tx/_s < radius)
					{
						mark[c] = 1;
					}
				}
				else
				{
					_s = fabs(cos(end_radian));
					if(_s && ty/_s < radius)
					{
						mark[c] = 1;
					}
				}
			}
			else if(center_y >= t_grid->start_y)
			{
				if(tx >= radius) continue;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->end_x, (float)t_grid->start_y);
				if(ang <=  start_radian) continue;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->end_x, (float)t_grid->end_y);
				if(ang <  end_radian) mark[c] = 1;
			}
			else
			{
				ty = t_grid->start_y - center_y;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->end_x, (float)t_grid->start_y);
				if(ang >= start_radian && ang <= end_radian)
				{
					if(tx * tx + ty * ty <  radius2)
					{
						mark[c] = 1;
					}
				}
				else if(ang < start_radian)
				{
					_s = fabs(cos(start_radian));
					if(_s && ty/_s < radius)
					{
						mark[c] = 1;
					}
				}
				else
				{
					_s = fabs(cos(end_radian));
					if(_s && tx/_s < radius)
					{
						mark[c] = 1;
					}
				}
			}
		}
		else if(center_x >= t_grid->start_x) //Բ�� grid ���м�
		{
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				ty = center_y - t_grid->end_y; 
				if(ty >= radius) continue;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->start_x, (float)t_grid->end_y);
				if(ang >= end_radian) continue;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->end_x, (float)t_grid->end_y);
				if(ang > start_radian) mark[c] = 1;
			}
			else if(center_y > t_grid->start_y)  // Բ����grid�м�
			{
				mark[c] = 1;
			}
			else
			{
				ty = t_grid->start_y - center_y; 
				if(ty >= radius) continue;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->start_x, (float)t_grid->start_y);
				if(ang <= start_radian) continue;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->end_x, (float)t_grid->start_y);
				if(ang < end_radian) mark[c] = 1;
			}
		}
		else// grid ��Բ���Ҳ�
		{
			tx = t_grid->start_x - center_x;
			if(center_y >= t_grid->end_y) //grid ��Բ���ϲ�
			{
				ty = center_y - t_grid->end_y;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->start_x, (float)t_grid->end_y);
				if(ang >= start_radian && ang <= end_radian)
				{
					if(tx * tx + ty * ty <  radius2)
					{
						mark[c] = 1;
					}
				}
				else if(ang > end_radian)
				{
					_s = fabs(cos(end_radian));
					if(_s && tx/_s < radius)
					{
						mark[c] = 1;
					}
				}
				else
				{
					_s = fabs(cos(start_radian));
					if(_s && ty/_s < radius)
					{
						mark[c] = 1;
					}

				}
			}
			else if(center_y > t_grid->start_y)  // Բ����grid�м�
			{
				if(tx >= radius) continue;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->start_x, (float)t_grid->start_y);
				if(ang >  end_radian) break;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->start_x, (float)t_grid->end_y);
				if(ang <  start_radian) mark[c] = 1;
			}
			else 
			{
				ty = t_grid->start_y - center_y;
				ang = Map::__GetAngle(center_x, center_y, (float)t_grid->start_x, (float)t_grid->start_y);
				if(ang >= start_radian && ang <= end_radian)
				{
					if(tx * tx + ty * ty <  radius2)
					{
						mark[c] = 1;
					}
				}
				else if(ang > end_radian)
				{
					_s = fabs(cos(end_radian));
					if(_s && ty/_s < radius)
					{
						mark[c] = 1;
					}
				}
				else
				{
					_s = fabs(cos(start_radian));
					if(_s && tx/_s < radius)
					{
						mark[c] = 1;
					}
				}
				break;
			}
		}// endf if
	}//end for
	vector<Unit *> units;
	for(int i = 0; i < 9; ++i)
	{
		if(mark[i])
		{
			t_grid = grid->notice_grid[i];
			PlayerSet::iterator piter = t_grid->players.begin();
			while(piter != t_grid->players.end())
			{
				if( (*piter)->isAlive() &&
					(*piter)->GetDistance(center_x, center_y) < radius)
				{
					ang = Map::__GetAngle(center_x, center_y, (float)(*piter)->GetPositionX(), (float)(*piter)->GetPositionY());
					if(ang >= start_radian && ang <= end_radian)
					{
						switch(TargetType)
						{
						case TARGET_TYPE_ALL:
							units.push_back(*piter);
							break;
						case TARGET_TYPE_FRIENDLY:
							if(unit->IsFriendlyTo(*piter)) units.push_back(*piter);
							break;
						case TARGET_TYPE_ENEMY:
							if(!unit->IsFriendlyTo(*piter)) units.push_back(*piter);
							break;
						default:
							break;
						}
					}
				}
				++piter;
			}
			Grid::CreatureList::iterator citer = t_grid->creatures.begin();
			while(citer != t_grid->creatures.end())
			{
				if((*citer)->isAlive() && (*citer)->GetDistance(center_x, center_y) < radius)
				{
					ang = Map::__GetAngle(center_x, center_y, (float)(*citer)->GetPositionX(), (float)(*citer)->GetPositionY());
					if(ang >= start_radian && ang <= end_radian)
					{
						switch(TargetType)
						{
						case TARGET_TYPE_ALL:
							units.push_back(*citer);
							break;
						case TARGET_TYPE_FRIENDLY:
							if(unit->IsFriendlyTo(*citer)) units.push_back(*citer);
							break;
						case TARGET_TYPE_ENEMY:
							if(!unit->IsFriendlyTo(*citer)) units.push_back(*citer);
							break;
						default:
							break;
						}
					}
				}
				++citer;
			}
		}
	}
	return __LuaAddUnit2(scriptL, units);
}

//GUIDת��ָ��
int Map::LuaGuidToPtr(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	Map *_map = (Map *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	const char *guid = LUA_TOSTRING(scriptL,2);
	if (!_map || !guid)
	{
		tea_pdebug("LuaGUIDToPtr !_map ");		
		return 0;
	}
	uint32 uint_guid = 0;
	if (GuidManager::GetPrefix(guid) == ObjectTypePlayer)
	{
		ScenedContext* player = dynamic_cast<ScenedContext*>(ObjMgr.Get(guid));
		if(player && player->GetPlayer())
			uint_guid = player->GetPlayer()->GetUIntGuid();
	}
	else
		uint_guid = shortGUID(guid);
	Unit *wo = _map->FindUnit(uint_guid);
	if (wo)
		lua_pushlightuserdata(scriptL,wo);
	else
		lua_pushnil(scriptL);

	return 1;
}

int Map::LuaIsCanRun(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	Map *map = (Map *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	float x = (float)LUA_TONUMBER(scriptL,2);
	float y = (float)LUA_TONUMBER(scriptL,3);
	if (!map)
	{
		lua_pushnumber(scriptL,0);
		return 1;
	}
	uint32 is_can = map->GetMapTemp()->IsCanRun(uint16(x),uint16(y))?1:0;
	lua_pushnumber(scriptL,is_can);
	return 1;
}

int Map::LuaIsInMap(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	Map *map = (Map *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	float x = (float)LUA_TONUMBER(scriptL,2);
	float y = (float)LUA_TONUMBER(scriptL,3);
	if (!map)
	{
		lua_pushnumber(scriptL,0);
		return 1;
	}
	//�ų�С��������
	uint32 is_can = map->GetMapTemp()->IsInMap(uint16(x+1),uint16(y+1))?1:0;
	lua_pushnumber(scriptL,is_can);
	return 1;
}

int Map::LuaConsLootPoint(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);		
	Map *map = (Map *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	Unit *wo = (Unit*)LUA_TOUSERDATA(scriptL,2, ObjectTypeUnit);
	uint32 x = 0;
	uint32 y = 0;
	bool succeed = false;
	if(map && wo)
	{
		if(map->HaveEnpty())
		{
			x = uint32(wo->GetPositionX()/g_Config.loot_area);
			y = uint32(wo->GetPositionY()/g_Config.loot_area);
			LootManager::ConsLootPoint(map, x,y);
			succeed = true;
		}
	}
	else
	{
		tea_perror("LuaConsLootPoint map is %p, wo is %p",map,wo);
	}
	lua_pushinteger(scriptL,x);
	lua_pushinteger(scriptL,y);
	lua_pushboolean(scriptL, succeed);
	return 3;
}
//ͨ��������ȡ��������
int Map::LuaConsLootPointByPos(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Map *map = (Map *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	float posx = (float)LUA_TONUMBER(scriptL,2);
	float posy = (float)LUA_TONUMBER(scriptL,3);
	uint32 x = 0;
	uint32 y = 0;
	bool succeed = false;
	if(map)
	{
		if(map->HaveEnpty())
		{
			x = uint32(posx/g_Config.loot_area);
			y = uint32(posy/g_Config.loot_area);
			LootManager::ConsLootPoint(map, x,y);
			succeed = true;
		}
	}
	
	lua_pushinteger(scriptL,x);
	lua_pushinteger(scriptL,y);
	lua_pushboolean(scriptL, succeed);
	return 3;
}

//��ȡȫͼ��������
int Map::LuaRandConsLootPoint(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);		
	Map *map = (Map *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	uint32 randx = 0;
	uint32 randy = 0;
	if (map && map->GetMapTemp() && map->HaveEnpty())
	{
		mt_baseinfo mapBaseInfo = map->GetMapTemp()->GetMapBaseInfo();
		uint32 map_width = mapBaseInfo.width-1;
		uint32 map_height = mapBaseInfo.height-1;
		uint32 count = 0;
		while(true)
		{
			randx = urand(1, map_width);
			randy = urand(1, map_height);
			if(LootManager::ConsLootPoint(map, randx, randy, randx, randy))
				break;
			count = count + 1;
			if(count > 10000)
				break;
		}
	}

	lua_pushinteger(scriptL,randx);
	lua_pushinteger(scriptL,randy);
	return 2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FOR InstanceMap

InstanceMap::InstanceMap(uint32 mapid, uint32 instanceid, uint32 lineno, const string &generalid):Map(mapid, instanceid, lineno, generalid),m_score(0)
{

}
InstanceMap::~InstanceMap()
{

}

///////////////////////////////////////////////////////////////////////////////////
//�̳�һ��������
void InstanceMap::InheritOldMap(InstanceMap *old_map)
{

}

//����뿪����
void InstanceMap::ExitInstance(Player *player)
{
	if(player == NULL)
	{
		
		for (auto iter = m_players.begin(); iter != m_players.end(); ++iter)
		{
			Player *p = iter->second;
			ASSERT(p);
			if(!p->GetSession())
				continue;

			// need_teleport_while_map_clear
			if (DoIsNeedTeleportWhileMapClear(this, p) == 1) {
				this->OnePlayerExitInstance(p);
			}
		}
	}
	else
	{
		if (!player->GetSession())
			return;
		
		////�����Ҳ����ڸ�����ͼ����ô�Ͳ������˳�������
		//const MapTemplate *_mt = MapTemplate::GetMapTempalte(player->GetMapId());
		//if (_mt && _mt->GetMapBaseInfo().instance_type == 0)
		//	return;

		this->OnePlayerExitInstance(player);
	}	
}

void InstanceMap::OnePlayerExitInstance(Player *player) {
	int map_id;
	float x,y;
	string generalId = "";
	player->GetSession()->GetToDBPosition(map_id, x, y);
	//tea_perror("{guid:%s,mapid%d}�˳�������õĵ�ͼID����ԭͼ",player->GetGuid().c_str(),map_id);
	player->GetSession()->Teleport(x,y,map_id,generalId);
}

int InstanceMap::LuaGetPlayer(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1 || n == 2);
	InstanceMap *_map = (InstanceMap *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);

	if(n == 1)
	{
		if(_map->GetPlayers().size())
		{
			Player *player = _map->GetPlayers().begin()->second;
			lua_pushlightuserdata(scriptL,player);
		}
		else
			lua_pushnil(scriptL);
	}
	else
	{
		const char* playerid = LUA_TOSTRING(scriptL, 2);
        if( !playerid )
        {
            lua_pushnil(scriptL);
            return 1;
        }
		uint32 uint_guid = shortGUID(playerid);
		Player* player = _map->FindPlayer(uint_guid);
		if (player)
		{
			lua_pushlightuserdata(scriptL, player);
		}
		else
		{
			player = _map->FindPlayer(playerid);
			if (player)
				lua_pushlightuserdata(scriptL, player);
			else
				lua_pushnil(scriptL);
		}
	}	

	return 1;
}


//�뿪����
int InstanceMap::LuaExitInstance(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	InstanceMap *_map = (InstanceMap *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	if (!_map)
	{
		return 0;
	}
	Player *player = NULL;
	if (n>=2)
	{
		player = (Player *)LUA_TOUSERDATA(scriptL, 2, ObjectTypeUnit);
	}
	_map->ExitInstance(player);
	return 0;
}

int Map::__LuaAddPlayer(lua_State *scriptL, vector<Player *>&players)
{
	lua_newtable(scriptL);    /* We will pass a table */
	int i = 0;
	std::for_each(players.begin(),players.end(),[&i,scriptL](Player* it){
		if(it->GetMap())
		{
			lua_pushnumber(scriptL, i+1);   /* Push the table index */
			lua_pushlightuserdata(scriptL,it);	
			lua_rawset(scriptL, -3);      /* Stores the pair in the table */
			i++;
		}
	});
	return 1;
}

// ���õ�ͼ������Ƿ���Ե���
int Map::LuaSetMapSite(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Map *map = (Map *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	float x = (float)LUA_TONUMBER(scriptL, 2);
	float y = (float)LUA_TONUMBER(scriptL, 3);
	if(!map)
		return 0;
	map->SetMapSite(x, y);
	return 1;
}
//��ȡ��뾶����ɵ�����
int Map::LuaGetRandPosByRadius(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 4);
	uint32 mapid = (uint32)LUA_TONUMBER(scriptL, 1);
	float x = (float)LUA_TONUMBER(scriptL,2);
	float y = (float)LUA_TONUMBER(scriptL,3);
	float r = (float)LUA_TONUMBER(scriptL,4);
	if (!mapid)
	{
		lua_pushnumber(scriptL,x);
		lua_pushnumber(scriptL,y);
		return 2;
	}
	MapTemplate *_mt = MapTemplate::mtvec[mapid];
	if(!_mt)
	{
		lua_pushnumber(scriptL,x);
		lua_pushnumber(scriptL,y);
		return 2;
	}
	float pos_x = x;
	float pos_y = y;
	uint16 beishu = 10000;
	for(uint16 i=0; i< 10; ++i)
	{
		int rand_r = urand(0, uint32(r*beishu));
		int rand_x = irand(-rand_r, rand_r);
		double rand_y = sqrt(pow(rand_r, 2) - pow(rand_x, 2));
		pos_x = x + float(rand_x/beishu);
		if(urand(1, 100) <= 50)
			pos_y = y - float(rand_y/beishu);
		else
			pos_y = y + float(rand_y/beishu);
		if(_mt->IsCanRun(uint16(pos_x),uint16(pos_y)))
			break;
	}
	lua_pushnumber(scriptL,pos_x);
	lua_pushnumber(scriptL,pos_y);
	return 2;
}

//���������ȡ��Ӧ��ս��Ʒָ��
int Map::LuaGetLootObject(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);
	Map *m = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	int x = (int)LUA_TOINTEGER(scriptL,2);
	int y = (int)LUA_TOINTEGER(scriptL,3);
	Grid &grid = m->m_grids->GridCoord(x, y);
	m->m_grids->InitLoot(grid);
	lua_pushlightuserdata(scriptL, grid.loot);
	lua_pushlightuserdata(scriptL, grid.loot->GetPrivateObj());
	lua_pushinteger(scriptL, grid.loot->GetLootIndex(x, y));
	return 3;
}

//��������ս��Ʒλ�ò��뵽�б�
int Map::LuaInsertLootIndex(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	LootObject *loot = (LootObject*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeGridLoot);
	uint32 index = (uint32)LUA_TOINTEGER(scriptL, 2);
	loot->m_has_loot.insert(index);
	return 0;
}

//��յ�ͼ������ս��Ʒ
int Map::LuaClearAllLoot(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);
	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	if(map && map->GetGridManager())
		map->GetGridManager()->ClearAllLoot();
	
	return 0;
}

//������ͼӲ�����ݱ����ļ���
int Map::LuaCreateMapDataHddDirectory(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	ASSERT(map);
	string path = (string)LUA_TOSTRING(scriptL,2);
	core_obj::Storage::CreatDir(path);
	return 0;
}

//�ж�ĳ�ļ��Ƿ����
int Map::LuaIsHaveFile(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 3);
	Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	ASSERT(map);
	string path = (string)LUA_TOSTRING(scriptL,2);
	bool need_create = (uint32)LUA_TOINTEGER(scriptL,3) == 1;
	int succ = 0;
	if(core_obj::Storage::IsHaveFile(path))
		succ = 1;

	//���������  ������Ҫ����
	if(need_create)
	{
		core_obj::Storage::CreatDir(path);
	}

	lua_pushinteger(scriptL,succ);

	return 1;
}

//��ȡ������ͼ��Ϣ
 int Map::LuaGetParentPtr(lua_State *scriptL)
 {
	 CHECK_LUA_NIL_PARAMETER(scriptL);
	 int n = lua_gettop(scriptL);
	 ASSERT(n >= 1);
	 Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	 ASSERT(map);
	 lua_pushlightuserdata(scriptL, map->m_parent_map_info);
	 return 1;
 }

 //��ȡϵ�е�ͼ�����������Ϣ
 int Map::LuaParentGetAllPlayer(lua_State *scriptL)
 {
	 CHECK_LUA_NIL_PARAMETER(scriptL);
	 int n = lua_gettop(scriptL);
	 ASSERT(n >= 1);
	 Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	 ASSERT(map);
	 uint32 instanceid = map->GetInstanceID();
	 lua_newtable(scriptL);
	 for(auto it=map_instances.lower_bound(instanceid);
		 it != map_instances.upper_bound(instanceid);++it)
	 {
		 Map *m = it->second;
		 for (auto it_player:m->m_players)
		 {
			 if(!it_player.second || !it_player.second->GetSession())
				 continue;

			 lua_pushstring(scriptL, it_player.second->GetSession()->guid().c_str());
			 lua_pushlightuserdata(scriptL,it_player.second);
			 lua_rawset(scriptL, -3);
		 }
	 }
	 return 1;
 }

 //grid�㲥��
 int Map::LuaBroadcast(lua_State *scriptL)
 {
	 CHECK_LUA_NIL_PARAMETER(scriptL);
	 int n = lua_gettop(scriptL);
	 ASSERT(n == 2);
	 Unit *unit = (Unit*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	 if (!unit)
		 return 0;
	 Map *map = unit->GetMap();
	 if(!map)
		 return 0;
	  
	 packet *pkt = (packet*)lua_touserdata(L,2);
	 update_packet_len(pkt);
	 map->Broadcast(*pkt, unit);
	 return 0;
 }

int Map::LuaBroadcastMap(lua_State *scriptL) {
 
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	if (!map) {
		return 0;
	}
	packet *pkt = (packet*)lua_touserdata(L, 2);

	update_packet_len(pkt);
	map->BroadcastMap(*pkt);

	return 0;
}

//��������˺�
int Map::LuaClearFieldBossDamage(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL,1,ObjectTypeNone);
	ASSERT(map);
	
	map->m_fieldBossDamage.clear();

	return 0;
}

//��������˺�
int Map::LuaAddFiledBossDamage(lua_State *scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 3);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);
	string guid = (string)LUA_TOSTRING(scriptL, 2);
	double dama = (double)LUA_TONUMBER(scriptL,3);


	if (!map->m_fieldBossDamage[guid]) {
		map->m_fieldBossDamage[guid] = 0;
	}
	map->m_fieldBossDamage[guid] += dama;

	return 0;
}

//�������˺������playerguid
int Map::LuaGetMaxinumFieldBossDamage(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);

	double damage = 0;
	string guid = "";

	for (auto it : map->m_fieldBossDamage) {
		if (damage < it.second) {
			damage = it.second;
			guid = it.first;
		}
	}

	lua_pushstring(scriptL, guid.c_str());
	return 1;
}

//ͨ��uintguid��ȡ��Ϸ����
int Map::LuaGetGameObjectByGuid(lua_State *scriptL) {

	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);
	uint32 guid = (uint32)LUA_TONUMBER(scriptL, 2);

	GameObject* tele = map->GetGameObjectByGuid(guid);
	if (tele) {
		lua_pushlightuserdata(scriptL, tele);
	} else {
		lua_pushnil(scriptL);
	}

	return 1;
}

//ͨ��entryɾ����Ϸ����
int Map::LuaRemoveGameObjectByEntry(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);
	uint32 entry = (uint32)LUA_TONUMBER(scriptL, 2);

	//ȫͼ������
	std::list<Unit *> removeList;
	for (GameObjectMap::iterator it = map->m_gameobjects.begin();
		it != map->m_gameobjects.end();++it) {

		if (it->second->GetEntry() == entry) {
			removeList.push_back(it->second);
		}
	}

	// ɾ��
	for (auto wo : removeList) {
		map->DeleteGameObject(static_cast<GameObject*>(wo));
	}
	removeList.clear();


	return 0;
}

//ͨ��entry�����Ϸ����
int Map::LuaGetGameObjectByEntry(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);
	uint32 entry = (uint32)LUA_TONUMBER(scriptL, 2);

	//ȫͼ������
	for (GameObjectMap::iterator it = map->m_gameobjects.begin();
		it != map->m_gameobjects.end();++it) {

			if (it->second->GetEntry() == entry) {
				lua_pushlightuserdata(scriptL, it->second);
				return 1;
			}
	}

	lua_pushnil(scriptL);

	return 1;
}

//�������ڿ��������guid
int Map::LuaOnOpenTreasure(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);
	string guid = (string)LUA_TOSTRING(scriptL, 2);

	map->openGuid = guid;

	return 0;
}

//������ڿ��������guid
int Map::LuaGetOnOpenGuid(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 1);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);

	lua_pushstring(scriptL, map->openGuid.c_str());

	return 1;
}

int Map::LuaGetPlayerByPlayerGuid(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);

	string playerGuid = (string)LUA_TOSTRING(scriptL, 2);

	Player* player = map->FindPlayer(playerGuid.c_str());

	if (player) {
		lua_pushlightuserdata(scriptL, player);
	} else {
		lua_pushnil(scriptL);
	}

	return 1;
}

//ĳ���˹�����Ұ��
void Map::PlayerHitCreature(uint32 creatureUintGuid, string playerGuid) {
	// û�еĻ�����
	if (creatureHitHash.find(creatureUintGuid) == creatureHitHash.end()) {
		std::set<string> players;
		creatureHitHash[creatureUintGuid] = players;
	}
	creatureHitHash[creatureUintGuid].insert(playerGuid);
}

//Ұ������, ����������������
int Map::LuaGetPlayersAfterCreatureDead(lua_State *scriptL) {
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n == 2);

	Map *map = (Map*)LUA_TOUSERDATA(scriptL, 1, ObjectTypeNone);
	ASSERT(map);
	uint32 creatureUintGuid = (uint32)LUA_TONUMBER(scriptL, 2);

	std::set<string> players = map->creatureHitHash[creatureUintGuid];
	vector<Unit*> units;
	for (string player_guid : players) {
		Player* player = map->FindPlayer(player_guid.c_str());
		if (player) {
			units.push_back(player);
		}
	}
	map->ClearCreatureHitHash(creatureUintGuid);
	return __LuaAddUnit2(scriptL, units);
}