#ifndef _SCENED_MAP_H
#define _SCENED_MAP_H

#include <shared/lua_helper.h>
#include <object/ScenedObjectManager.h>
#include <object/SharedDef.h>
#include <object/BinLogObject.h>

class MapTemplate;
class ScenedContext;
class Unit;
class Creature;
class GridManager;
class Player;
class GameObject;
struct TimerHolder;

//��ͼ��������
enum EMapPktTypes
{
	MAP_PKT_TYPES_CREATURE_TELEPORT			= 0, //���ﴫ��
};

//����ͬ��������,������Ҫ����������⣨ʵ��ID�Ƿ���ڻص���ţ����ж����ݵ���
typedef struct wait_joiningt
{
	uint8	teleport_sign;		//�ص����
	char	player_guid[50];
	uint32	connection_id;
	int		to_map_id;
	int		to_instance_id;
	float	to_x;
	float	to_y;
	uint32	create_tm;			//��ʼ����ʱ��,���ڵ���
}wait_joining;

typedef UNORDERED_MAP<string,Creature*>  CreaturesMap;
typedef std::list<std::pair<int32,string> > GameObjectRespawnList;
typedef std::list<uint32> PlayerRespawnList;
typedef std::multimap<std::string,Unit*> AliasObjectMMap; 	//�����
typedef std::vector<Unit*>	WorldObjectVec;
typedef std::set<Creature*>	CreatureSet;
typedef UNORDERED_MAP<string,GameObject*> GameObjectMap;
typedef std::map<string, Player*> PlayerMap;
typedef std::map<uint32, std::set<string>> HitMap;
typedef vector<wait_joining> WaitJoiningVec;

class Map
{
public:
	static map<uint32, BinLogObject*> all_parent_map_info;		//������ͼ����
	static void UpdateParentInfo();
	static BinLogObject fighting_info_binlog;					//ս����Ϣbinlog�����˺������ʩ��������Ϣ��buff������Ϣ�ȵ�
	static void BroadcastFightingInfo(Unit *unit);
	// ����ս��binlog��Ϣ
	static void FightingInfoBinlogRest() {
		string guid = fighting_info_binlog.GetGuid();
		fighting_info_binlog.Reset();
		fighting_info_binlog.SetGuid(guid);
	}
public:	
	typedef std::multimap<uint32,Map*> MapInstances;	//���е�ͼϵ�м���
	static MapInstances map_instances;
	static WaitJoiningVec wait_joing_vec;				//�ȴ����ͽ����ͼ

	static Map *CreateInstance(uint32 instanceid,uint32 mapid,uint32 lineno,const string &general_id);	//������ͼʵ��
	static void DelMap(uint32 instanceid); 						//ɾ����ͼʵ��
	static Map *FindInstance(uint32 instance_id,uint32 map_id);	//����ʵ��IDȡ�õ�ͼʵ��,��������ڷ��ؿ�
	static std::vector<Map *> FindFieldBossInstance(std::set<uint32> s_mapid);	// ����һϵ�е�mapid��ö�Ӧ��һϵ�еĵ�ͼʵ������
	//static Map *FindInstance(uint32 map_id, uint8 lineNo=1);	//���ݵ�ͼIDȡ�õ�ͼʵ��,��������ڷ��ؿգ�����ǧ������Ŷ������Ŷ
	static void ClearInstance();
	static void CheckMapInstanceLastTime(TimerHolder& th);		//ÿ���Ӽ�⸱��ʵ���Ƿ�ر�	
	static void CheckWaitJoingVec(uint32 diff);					//�����Ҵ����Ƿ���������չ�
	static void PrintAllMap();									//��ӡ�ڴ������еĵ�ͼ��Ϣ
	//lua����
	typedef struct script_instance_var{
		uint32	type;				//ֵ������ ��ӦLUA_DATA_TYPEö��
		union
		{
			lua_Integer	value;		//ֵ
			lua_Number l_val;		//����ֵ
			void * ptr;				//ĳָ��
			char str[50];			//ĳ�ַ���
		};		
	}script_instance_var;

	//�ű���ʱ��
	struct script_timer_callback{
		int id;							//�ص�����
		char s_callback[50];			//������
		script_instance_var param1[10];	//�ص���������
		IntervalTimer timer;			//��ʱ��
		int invalid;					//�Ƿ�ʧЧ
		int is_new;						//�Ƿ�������ʱ��
	};
	typedef list<script_timer_callback*> ScriptCBList;

	//�ű�ʱ�����ʱ��
	struct script_timestamp_timer_callback{
		int id;							//�ص�����
		char s_callback[50];			//������
		script_instance_var param1[10];	//�ص���������
		uint32 timestamp;				//��ʱ��
		int invalid;					//�Ƿ�ʧЧ
		int is_new;						//�Ƿ�������ʱ��
	};
	typedef list<script_timestamp_timer_callback*> ScriptTimeStampList;

	//��Ա
public:
	Map(uint32 mapid, uint32 instanceid, uint32 lineno, const string &generalid);
	virtual ~Map();

	//���ݵ�ͼID��ģ��ԭ�ͱ��������ͼ
	bool Load();
	virtual void Update(uint32 diff);
	void UpdateRespan(uint32 diff);		//����������������

	//��ͼID
	uint32 GetMapId(){return m_mapid;}
	const string &GetParentGuid(){return m_parent_map_info->guid();}
	//ʵ��id
	uint32 GetInstanceID(){return m_parent_map_info->GetUInt32(MAP_INT_FIELD_INSTANCE_ID);}
	//�ߺ�
	uint32 GetLineNo(){return m_parent_map_info->GetUInt32(MAP_INT_FIELD_LINE_NO);}
	//ʶ��id
	const string &GetGeneralID(){return m_parent_map_info->GetStr(MAP_STR_GENERAL_ID);}
	void SetGeneralID(const string &generalid){m_parent_map_info->SetStr(MAP_STR_GENERAL_ID, generalid);}
	//��õ�ͼ����ʱ��
	uint32 GetMapCreateTime(){return m_parent_map_info->GetUInt32(MAP_INT_FIELD_CREATE_TM);}
	//��õ�ͼ����ʱ��
	uint32 GetMapEndTime(){return m_parent_map_info->GetUInt32(MAP_INT_FIELD_END_TM);}
	void SetMapEndTime(uint32 val){	m_parent_map_info->SetUInt32(MAP_INT_FIELD_END_TM, val);}
	uint32 GetPlayerAutoRespanTime(){return 1000 * m_parent_map_info->GetByte(MAP_INT_FIELD_STATE, 2);}
	//��ó���id
	uint32 GetWarId(){return m_parent_map_info->GetUInt32(MAP_INT_FIELD_WARID);}
	//��ÿ������
	uint32 GetKuafuType(){return m_parent_map_info->GetUInt32(MAP_INT_FIELD_KUAFU_TYPE);}
	//��ʼ������id�Ϳ��id
	void InitWaridAndKuafuType(ScenedContext* session);

	void JoinPlayer(Player *player);	//��Ҽ���
	void LeavePlayer(Player *player);		//����뿪
	void LeaveCreature(Creature *creature);	//�����뿪��ͼ,�������뿪,�ڴ治����

	uint32 GetPlayerCount(){return m_players.size();}
	PlayerMap& GetPlayers(){return m_players;}

	void AddGameObject(GameObject *go);		//������Ϸ����
	void DeleteGameObject(GameObject *go);	//ɾ����Ϸ����
	void ReSpawnWorldObject(GameObject* wo);//��������ˢ���б�
	void SetMapSite(float x, float y);		//ս��Ʒ��������Ϊ����
	void UnSetMapSite(float x, float y);	//ս��Ʒ��������Ϊδ��

	bool AddCreature(Creature *creature);
	Creature *AddCreature(uint32,float,float,float toward = 0.0f,uint32 respan_time = 0, uint32 movetype=0, uint32 npcflag = 0, const char *alias_name = NULL,bool active_grid = false, uint8 faction = 0,const char *ainame = NULL,uint32 level = 0, uint32 attackType = 0, uint32 riskId = 0); 
	Creature * AddCreatureTravelers(string &data,float x,float y, uint32 movetype=0,const char *alias_name = NULL);		//���ͼ�������Ĺ���

	void ToDelCreature(Creature *creature);

	//�㲥���ݰ�,�Ƿ�����Լ�
	void Broadcast(packet& pkt,Unit *wo) const;
	void Broadcast(packet& pkt,Player *player,bool self = false) const;

	void BroadcastMap(packet& pkt) const;

	//�ڵ�ͼ��Ѱ��Unit���� �Ҵ��͵����Ƚ����� ��Ҫ�õ���Ҷ���
	GameObject *FindWorldObject(uint32 guid);
	Unit *FindUnit(uint32 guid);
	Player *FindPlayer(uint32 guid);
	Player *FindPlayer(const char* guid);
	Creature* FindCreature(uint32 guid);

	bool IsCanRun(float x,float y);	
	bool IsRightCoord(float x,float y);
	bool IsRightCoordNoCanRun(float x,float y);

	//���������Gameobject�ĵ�λGUI
	static const string CreateNewCreatureID();

	//��ͼģ��
	const MapTemplate *GetMapTemp(){return m_template;}

	//�����Զ��������
	void AddRespanPlayer(Player* player);

	//�Ƿ��λ�����Է���ս��Ʒ
	bool IsEnpty(uint32 x,uint32 y)
	{
		if(x >= m_loot_site_width || y >= m_loot_site_hight)
			return false;		
		return m_all_site.GetBit(x + m_loot_site_width * y) == 0;
	}

	//�Ƿ��λ�����Է���ս��Ʒ
	bool IsEnpty(uint32 p)
	{
		if(p >= m_loot_site_width * m_loot_site_hight)
			return false;		
		return m_all_site.GetBit(p) == 0;
	}

	bool HaveEnpty()
	{
		//�����������10���ո�������ѭ��		
		return m_all_enpty_count > 10;
	}
	//��ͼ�Ƿ����Ծ
	bool isCanJumpMap(){return m_is_can_jump;}
	void SetMapIsCanJump(bool is_can ){m_is_can_jump = is_can;}
	
	void SendCreateBlock(ScenedContext *player);
	void SendCreateBlock(uint32 fd);
	void SendDeleteBlock(ScenedContext *player);
	void SendDeleteBlock(uint32 fd);
	
	void SendGridUnitFromPlayer(Player* player);	//�ȸ�ʱ�·�unit���ͻ�����

	void SendMapPkt(uint32 mapid, const string &general_id, uint8 typ, std::function<void(ByteArray&)>);
	void HandleMapPkt(ByteArray &bytes);
	//�����ﴫ������һ����ͼ
	void TeleportCreature(const string &guid, uint32 mapid, float x,float y, const string &general_id);
	void OnTeleportCreature(ByteArray &bytes);
	GridManager *GetGridManager(){return m_grids;}	
	void GetAllGameObjectByEntry(vector<GameObject *> &vect, uint32 entry = 0);		//��ȡ������Ϸ����

public:
	/** <playerGuid, damage> */
	typedef std::map<string, double> PlayerDamage;
	PlayerDamage m_fieldBossDamage;
	static int LuaClearFieldBossDamage(lua_State *scriptL);			//��������˺�
	static int LuaAddFiledBossDamage(lua_State *scriptL);			//��������˺�
	static int LuaGetMaxinumFieldBossDamage(lua_State *scriptL);	//�������˺������playerguid

	string openGuid;	// ���ڿ��������guid
	static int LuaOnOpenTreasure(lua_State *scriptL);	//�������ڿ��������guid
	static int LuaGetOnOpenGuid(lua_State *scriptL);	//������ڿ��������guid

public:
	GameObjectMap				m_gameobjects;	
	GameObjectRespawnList		m_go_dynamic;		//��̬��Ϸ����,��һ����ʱ����Ҫ��ʧ
	PlayerRespawnList			m_player_respawn;	//��ҵ��Զ�����	
	string m_state_script;							//��ͼʵ���ű����
	UpdateMask m_all_site;							//��ʶ��ͼ�����������ʹ��״̬

	PlayerMap m_players;		//����б�
	CreaturesMap m_alive_creatures;		//���ŵĹ����б�

	HitMap creatureHitHash;	//�����б�

	bool m_is_can_jump;			//�Ƿ�����Ծ

	bool m_can_recovry;			//�Ƿ�֧�ָֻ�������ԴȪ�ȣ�
	bool m_can_castspell;		//�Ƿ�����ʩ��(��ʱ��Ҫ�������ƿ��׼��ʱ���ڲ�������)
	uint32 m_mapAttrBonus[MAX_EQUIP_ATTR];//��ͼ���Լӳ�
	
	GameObject *GetGameObjectByGuid(uint32 target);

public:
	void ClearCreatureHitHash(uint32 uintguid);
	void PlayerHitCreature(uint32 creatureUintGuid, string playerGuid);	//ĳ���˹�����Ұ��

protected:
	void AddAliasCreature(Unit *unit);
	void DelAliasCreature(Unit *unit);
protected:
	uint32 m_mapid;						//��ͼģ��ID
	BinLogObject *m_parent_map_info;	//����ͼ��Ϣ

	const MapTemplate *m_template;	//��ͼģ��
	GridManager *m_grids;		//���������
		
	CreatureSet	m_to_del_creature;		//��Ҫ�ӵ�ͼɾ��������(���۰�)
	
	int			 m_script_callback_key;	
	ScriptCBList m_script_callbacks;	//�ű��ص�
	ScriptTimeStampList m_script_timestamp_callbacks;	//ʱ�����ʱ���ص�

	std::multimap<int, script_instance_var>  m_luaVar;//lua�ű���������

	uint32 m_loot_area;				//ս��Ʒռ������ı߳�
	uint32 m_loot_site_width;			//����ս��Ʒռ�ر߳���С��ĵ�ͼ���
	uint32 m_loot_site_hight;			//����ս��Ʒռ�ر߳���С��ĵ�ͼ�߶�
	uint32 m_all_enpty_count;			//���п�λ����

	AliasObjectMMap m_aliasObjs; 	//���ݱ������Ҷ���
	WorldObjectVec m_worldObject_toadd;	//�������
	Map* m_parent;					//������ͼ	

	ByteArray m_byte_buf;

	uint32 m_end_time;
public:
	bool m_broadcast_nogrid;		//�޸���ʽ��ȫͼ�㲥
	bool m_is_close_respawn;		//�Ƿ�رո���
	//////////////////////////////////////////////////////////////////////////
	//static for lua script
	static int LuaGetMapId(lua_State *scriptL);					//��ȡ��ͼģ��ID
	
	static int LuaSetMapAttrBonus(lua_State *scriptL);			//���õ�ͼ�ӳ�
	static int LuaSetCanRecovey(lua_State *scriptL);			//���õ�ͼ�Ƿ�֧�ֻ�Ѫ
	static int LuaGetCanRecovey(lua_State *scriptL);			//��ȡ��ͼ�Ƿ�֧�ֻ�Ѫ
	static int LuaSetCanCastSpell(lua_State *scriptL);			//�����Ƿ����ʩ��
	static int LuaGetCanCastSpell(lua_State *scriptL);			//����Ƿ����ʩ��

	static int LuaFindSatisfiedFieldBossInstance(lua_State *scriptL);	//��û�ø���ʵ��

	static int LuaAddCreature(lua_State *scriptL);
	
	static int LuaAddGameObject(lua_State *scriptL);
	static int LuaConsLootPoint(lua_State *scriptL);			//����ս��Ʒ��
	static int LuaConsLootPointByPos(lua_State *scriptL);		//ͨ��������ȡ��������
	static int LuaRandConsLootPoint(lua_State *scriptL);		//��ȡȫͼ��������
	static int LuaRemoveObject(lua_State *scriptL);
	static int LuaQueryCreature(lua_State *scriptL);		//����ģ��ID�ҵ���Ӧ����
	static int LuaGetCreatureEntryCount(lua_State *scriptL);//��ù��ﲻͬentry������
	static int LuaAliasCreature(lua_State *scriptL); 		//��������ı������Ҷ���
	static int LuaAliasCreatureTable(lua_State *scriptL);	//��������ı������Ҷ���,����һ����
	
	static int LuaGetCircleTargets(lua_State *scriptL);		//ȡԲ������Ŀ�� center_x,center_y,radius
	static int LuaGetCircleTargetsByPos(lua_State *scriptL);		//ȡԲ������Ŀ��2
	static int LuaGetRectTargets(lua_State *scriptL);		//ȡ��������Ŀ�� leftdown_x,leftdown_y,rightup_x,rightup_y
	static int LuaGetFanshapedTargets(lua_State *scriptL);	//ȡ��������Ŀ�� center_x,center_y,radius,radian,orientation
	static int LuaGetObliqueRectTargets(lua_State *scriptL);	//��ȡб���ε�Ŀ��
	static float __GetAngle(const float x1, const float y1, const float x2, const float y2);
	static int __LuaAddUnit(lua_State *scriptL, vector<Unit *>&units);
	static int __LuaAddUnit2(lua_State *scriptL, vector<Unit *>&units);
	static int	__LuaAddPlayer(lua_State *scriptL, vector<Player *>&players);
	static void GetCircleTargets(float center_x, float center_y, float radius, Unit* unit, vector<Unit *> &units, Spell_Target_Type = TARGET_TYPE_ALL, bool dis_sort = false);
	static void GetCircleTargetsByPos(Map *map,float center_x, float center_y, float radius,vector<Unit *> &units, Spell_Target_Type = TARGET_TYPE_ALL);
	static void GetRectTargets(Unit* unit,float start_x, float start_y, float end_x, float end_y, vector<Unit *> &units, Spell_Target_Type TargetType); 	//��ȡ����Ŀ��
	static int LuaGetPlayersCounts(lua_State *scriptL);	//��ȡ��ͼ����
	static int LuaAddTimer(lua_State *scriptL);
	static int LuaAddTimeStampTimer(lua_State *scriptL);
	static int LuaDelTimer(lua_State *scriptL);
	static int LuaDelTimeStampTimer(lua_State *scriptL);
	static int LuaRandomPos(lua_State *scriptL);			//�ڵ�ͼ�����
	static int LuaGuidToPtr(lua_State *scriptL);
	static int LuaGetAllPlayer(lua_State *scriptL);	//��ȡ�������
	static int LuaGetAllCreature(lua_State *scriptL);	//��ȡ���й���
	static int LuaGetGameOject(lua_State *scriptL);		//���ָ��ģ�����Ϸ����
	static int LuaGetAllGameObject(lua_State *scriptL);	//��ȡ������Ϸ����
	static int LuaIsCanRun(lua_State *scriptL);				//�ж������Ƿ�Ϸ�
	static int LuaIsInMap(lua_State *scriptL);				//�ǲ����ڵ�ͼ֮��
	static int LuaSetMapSite(lua_State* scriptL);		// ���õ�ͼ������Ƿ���Ե���
	static int LuaGetRandPosByRadius(lua_State *scriptL);		////��ȡ��뾶����ɵ�����

	static int LuaGetLootObject(lua_State *scriptL);		//���������ȡ��Ӧ��ս��Ʒָ��
	static int LuaInsertLootIndex(lua_State *scriptL);		//��������ս��Ʒλ�ò��뵽�б�
	static int LuaClearAllLoot(lua_State *scriptL);			//��յ�ͼ������ս��Ʒ
	static int LuaCreateMapDataHddDirectory(lua_State *scriptL);//������ͼӲ�����ݱ����ļ���
	static int LuaIsHaveFile(lua_State *scriptL);			//�ж�ĳ�ļ��Ƿ����
	static int LuaGetParentPtr(lua_State *scriptL);			//��ȡ������ͼ��Ϣ
	static int LuaParentGetAllPlayer(lua_State *scriptL);	//��ȡϵ�е�ͼ�����������Ϣ
	static int LuaBroadcast(lua_State *scriptL);	//grid�㲥��
	static int LuaBroadcastMap(lua_State *scriptL);	//MAP�㲥��

	static int LuaGetGameObjectByGuid(lua_State *scriptL);		//ͨ��uintguid��ȡ��Ϸ����
	static int LuaGetGameObjectByEntry(lua_State *scriptL);	//ͨ��entry�����Ϸ����
	static int LuaRemoveGameObjectByEntry(lua_State *scriptL);	//ͨ��entryɾ����Ϸ����

	static int LuaGetPlayerByPlayerGuid(lua_State *scriptL);

	static int LuaIsMapLineCreated(lua_State *scriptL);

	static int LuaGetPlayersAfterCreatureDead(lua_State *scriptL);	//Ұ������, ����������������
};


class InstanceMap :public Map
{
public:
	InstanceMap(uint32 mapid, uint32 instanceid, uint32 lineno, const string &generalid);
	virtual	~InstanceMap();
public:
	void InheritOldMap(InstanceMap *old_map);				//�̳�һ��������
	void ExitInstance(Player *player = NULL);				//�뿪����,���û�и���������˳�ȫ��
	
private:
	uint8 m_score;											//��������
	void OnePlayerExitInstance(Player *player);				//ĳ������뿪����

public:
	static int LuaGetPlayer(lua_State *scriptL);			//��ø�����ҡ���ʱΪ����
	static int LuaExitInstance(lua_State *scriptL);			//�뿪����
};
#endif

