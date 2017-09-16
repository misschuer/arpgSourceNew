#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <stack>
#include "MovementGenerator.h"
#include "Unit.h"
#include "ThreatManager.h"

//��޹�����¶�ʱ��
#define UPDATE_THREAT_TIMER 1200
class Map;
class Player;
class Unit;
class LootManager;

//enum Friendly_To_Type
//{
//	FRIENDLY_TO_PLAYER
//	FRIENDLY_TO_MONSTER
//	FRIENDLY_TO_ALL
//	FRIENDLY_TO_NONE
//};

//��������
enum BossFlag
{
	BOSS_FLAG_GENERAL		= 0,		//һ�����
	BOSS_FLAG_PINK			= 1,		//��ɫ����
	BOSS_FLAG_GREEN			= 2,		//��ɫ����
	BOSS_FLAG_VIOLET		= 3,		//��ɫ����
	BOSS_FLAG_RED			= 4,		//��ɫ����
	MAX_BOSS_FLAG
};

//���﷨������
typedef struct spell_cast_probability_t
{
	uint32 spell_id;				//����ID
	uint32 spell_probability;	//ʩ������
	uint32 spell_distance;		//ʩ������
	uint32 spell_groupCD;		//��CD
	uint32 spell_singleCD;		//CDʱ��
	uint32 spell_nowCDtime;		//�ͷż�����Ҫ�ȴ���ʱ��
	uint32 target_type;			//Ŀ������
	uint32 spell_level;			//���ܵȼ�
} spell_cast_probability;

//��������б������ID
typedef std::vector<uint32>	OwnershipVec;

typedef std::map<uint32, std::vector<spell_cast_probability*>> SpellAIMap;

//������,�������е�NPC�Լ�����
class Creature:public Unit
{
	friend class ThreatManager;
	typedef std::stack<MovementGenerator *> MotionImpl;
	typedef std::vector<MovementGenerator *> MotionExpirezList;

public:
	Creature();
	virtual ~Creature();

	void Update(uint32 p_time);
	void OnKilled(Unit* killer, uint16 id = 0);
	void Calcul_Attr();		
	bool Create(Map *map, const string &guidlow, uint32 tempid,uint32 respan_tm =0,uint32 movetype=0,const char *ainame = 0,uint32 level = 0, uint32 attackType = 0);
	void Initialize();
	void SetCanActiveGrid(bool status);
	
	void UpdateLiveStatus(uint32 diff);			//��������״̬
	void UpdateSaySomething(uint32 diff);		//���˵��ʲô
	void UpdateOwnership(uint32 diff);			//���¹���������
	void UpdateMotion(uint32 diff);				//���¹�����Ϊ
	bool CheckCreateTimeOutDel(uint32 diff);	//���ɾ����Ҫ��ʱɾ���Ĺ���
	
	void MotionMoveTarget();							//�ߵ�Ŀ���	

//	void SetScriptAI(const char *scriptName){m_script_name = scriptName;}	
	void SetReactState(ReactStates st) { m_reactState = st; }	//����� ��޷�Ӧ����
	ReactStates GetReactState() { return m_reactState; }
	void SetMoveType(uint32 type){m_move_type = type;}
	uint32 GetMoveType(){return m_move_type;}
	void GetBornPos(float& x,float& y){x = m_bornX;y = m_bronY;}	//����������
	void SetBornPos(float x,float y){m_bornX = x;m_bronY = y;}	

	inline creature_template& GetTemplate() const
	{
		ASSERT(GetEntry()!=0);
		ASSERT(creature_template_db[GetEntry()]);
		ASSERT(creature_template_db[GetEntry()]->id == (int)GetEntry());
		return *creature_template_db[GetEntry()];
	}
	
	bool isVendor()       const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_VENDOR ); }
	bool isTrainer()      const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_TRAINER ); }
	bool isQuestGiver()   const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_QUESTGIVER ); }
	bool isGossip()       const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_GOSSIP ); }
	bool isTaxi()         const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_FLIGHTMASTER ); }
	bool isGuildMaster()  const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_PETITIONER ); }
	bool isBattleMaster() const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_BATTLEMASTER ); }
	bool isBanker()       const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_WAREHOUSE ); }
	bool isInnkeeper()    const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_INNKEEPER ); }
	bool isSpiritHealer() const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_SPIRITHEALER ); }
	bool isSpiritGuide()  const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_SPIRITGUIDE ); }
	bool isTabardDesigner()const{ return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_TABARDDESIGNER ); }
	bool isAuctioner()    const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_AUCTIONEER ); }
	bool isArmorer()      const { return GetBit( UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_VENDOR_EQUIPMENT ); }
	bool isServiceProvider() const
	{
		return GetUInt32(UNIT_FIELD_NPC_FLAG) > 0;
		/*return (GetUInt32(UNIT_FIELD_NPC_FLAG) & 
			(UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_VENDOR | UNIT_NPC_FLAG_TRAINER | UNIT_NPC_FLAG_FLIGHTMASTER |
			UNIT_NPC_FLAG_PETITIONER | UNIT_NPC_FLAG_BATTLEMASTER | UNIT_NPC_FLAG_WAREHOUSE |
			UNIT_NPC_FLAG_INNKEEPER | UNIT_NPC_FLAG_SPIRITHEALER |
			UNIT_NPC_FLAG_SPIRITGUIDE | UNIT_NPC_FLAG_TABARDDESIGNER | UNIT_NPC_FLAG_AUCTIONEER)) != 0;*/
	}

	//�Ƿ���ս��
	bool isChallenge() const  { return GetBit(UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_CHALLENGE); }	
	//�Ƿ���11,�޾��飬ûǮ��ûװ����û����ɱ����
	bool isOneOne() const {return GetBit(UNIT_FIELD_NPC_FLAG, UNIT_NPC_FLAG_ONE_ONE); }

	uint32 GetCurOwnership(){return m_cur_ownership;}				//��ȡ��ǰ�����������±�
	void SetCurOwnership(uint32 owner){m_cur_ownership = owner;}		//���ù���������
	float GetFollowDis(){return 0;}

	void RandomMove(uint32 ms,float x=-1,float y=-1);	
	int MonsterMove(MovementGeneratorType mov_typ, size_t param1, time_t t);//�����ƶ�����

	//////////////////////////////////////////////////////////////////////////
	//AI�ӿ�	
	int AI_MoveInLineOfSight(Unit *u);				//����Unit��������Ұ
	void AI_DamageTaken(Unit *u,double& damage);		//���˺�����ʱ
	void AI_DamageDeal(Unit *u,double damage);		//���˺������
	void AI_GiveDamage(Unit *u,double& damage);		//�������˺�ʱ
	void AI_KilledUnit(Unit *pVictim);				//��ɱ��ĳ��λʱ
	void AI_JustDied(Unit *killer, uint32 &deadtime);					//����ɱ��ʱ

public:		
	MotionImpl	m_impl;
	MotionExpirezList m_expire_impl;

	ThreatManager m_threatMgr;			//��޹���
	OwnershipVec m_ownerships;						//�����б�
	vector<uint32> m_friends_creature;				//�Ѿ���ģ��ID
	
	bool HasSpell(uint32 spell_id = 0);									//�Ƿ��м������и��ʿ�ʩ�ŵ�	
	int GetSpellGroup();								//������CD���������	
	void SpellGroupWait(uint32 group_id, uint32 t = 0);	//ʹ�ü������Ե�һ���ټ������
	spell_cast_probability *RandSpell(float dis);
	void ChangeSpellCD(uint32 spellID, uint32 cd);		////�ı似��CDʱ��

	//�������	
	bool IsSpellCD(uint32 spellID);				
	void SetSpellCD(uint32 spellID);

public:
	//�Զ��������жϾ����Ƿ�����BUFF  
	static void AddTheOwnership(Unit *target,Unit *buff_giver);
	//TODO �����ĳ�����Ϊ����������޵�ͬʱ��������ҹ�����			

	void SetEvadeState(bool state);					//��������״̬
	bool GetEvadeState() {return evade_state;}	
	const char* GetAIName(){return m_script_name.c_str();}
	float GetAttackDistance(Unit const* ) const;

	//TODO:������GUID
	uint32 GetHostGUID()const{return shortGUID(GetOwner().c_str());}
	void SetHostGUID(Unit *unit);
	Unit *GetOwnerUnit();

	//����Ʒ���
	void DelOwnerShip(uint32 lguid);				//ɾ��һ��������
	void AddTheOwnership(uint32 lguid);				//V����һ����ҵ������б�
	Player *GetOwnship();							//��ȡ��ǰ�Ϸ�������
	void ResetOwnerShip();
	void GetOwnshipTable(vector<Player *> &players);						//��ȡ��ǰ�Ϸ��������б�

	//����
	uint32 GetFinallyExp(Unit *unit);				//��ֻ�ֻ�������	


	//����Ϊ��ʱ��
	void SetClearTimer(time_t t);
	time_t GetClearTimer();

	uint32 GetBallisticSpellId(){return  GetUInt32(GO_FIELD_DATA);};
	uint32 GetBallisticDamage(){return  GetUInt32(GO_FIELD_DATA+1);};

	uint32 m_threat_move_type;						//�������ƶ�����

	uint32 GetNextSpellCD() {
		return nextSpellCD;
	}
private:	
	//for AI
	ReactStates m_reactState;                       // for AI, not charmInfo
	uint32 m_move_type;	
	string m_script_name;							//scriptai 
	bool evade_state ;								//����״̬
	TimeTracker m_timer_say;
	TimeTracker m_timer_threat;						//��޸��¼�ʱ��
	TimeTrackerSmall m_update_ownership_timer;
	float m_bornX,m_bronY;							//��������
	uint32 m_respawn_time;							//����ʱ��
	vector<uint32> m_spells_cd;					//����CD
	SpellAIMap m_spells;

	//�¸����ܶ�����CD
	uint32 nextSpellCD;
	
	IntervalTimer m_clear_timer;			//��ʧʱ��
	uint32 m_cur_ownership;					//�������󱬳���ս��Ʒӵ����
	//////////////////////////////////////////////////////////////////////////
	//for motion
	IntervalTimer m_motion_timer;
	uint32 m_motion_timer_diff;
public:	
	static int LuaSetMonsterHost(lua_State *scriptL);	//��������
	static int LuaGetMonsterHost(lua_State *scriptL);	//��ȡ����
	static int LuaSetReactState(lua_State* scriptL);
	static int LuaSetScriptAI(lua_State* scriptL);

	static int LuaModifyThreat(lua_State* scriptL);	
	static int LuaMonsterTalk(lua_State* scriptL);
	static int LuaMonsterDeadTalk(lua_State* scriptL);			//���������԰�
	static int LuaMonsterMove(lua_State* scriptL);
	static int LuaMonsterAddSpell(lua_State* scriptL);
	static int LuaIsAIFriends(lua_State* scriptL);				//��ȡAI�е�Friends
	static int LuaActiveGrid(lua_State *scriptL);			//���������grid
	static int LuaSetActionRadius(lua_State* scriptL);	//���û�뾶
	static int LuaSetVisionRadius(lua_State* scriptL);	//���û�뾶
	static int LuaGetOwnShipTable(lua_State* scriptL);	//��ù������б�
	static int LuaChangeSpellCD(lua_State* scriptL);	//�ı�ĳ������cdʱ��
	static int LuaGetLootOwner(lua_State* scriptL);		//��ǰ�Ϸ�������
	static int LuaRemoveMonster(lua_State* scriptL);	//�Ƴ�����

};

#endif
