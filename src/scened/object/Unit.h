#ifndef __UNIT_H__
#define __UNIT_H__

#include <object/std.h>
#include <comm/hash_list.h>
#include <protocol/external.h>
#include <object/SharedDef.h>
#include <object/ScenedObjectManager.h>

class Map;
class BufferManager;
struct Grid;

extern vector<uint16> g_cant_attack_buff;
extern vector<uint16> g_cant_cast_buff;
extern vector<uint16> g_cant_move_buff;
extern vector<uint16> g_cant_jump_buff;
extern vector<uint16> g_cant_teleport_buff;
extern vector<uint16> g_cant_use_item_buff;
extern vector<uint16> g_cant_see_buff;
extern vector<uint16> g_invincible_buff;
extern vector<uint16> g_cant_fight_with_player;
extern vector<uint16> g_cant_attack_be_player;
extern vector<uint16> g_cant_recovery_buff;
extern vector<uint16> g_ignore_the_obstacles;


//���ڵ���������Ҫһ�����̣����ԣ�����һ�������������ӳٲ����˺�
//���ܷ�Ϊ,ʩ�����������˺�
//���ܴ�����
typedef struct spell_trigger_t
{
	//uint32 self_guid;		//�����ܵ�Unit GUID
	uint32 target_guid;	//Ŀ���Guid
	int spell_id;			//����ID
	int spell_lv;			//���ܵȼ�
	float dst_x;			//Ŀ�������x
	float dst_y;			//Ŀ�������y
	IntervalTimer timer;	//��ʱ����ʱ�䣨ms��
	int count;				//��������
	char data[500];			//Ԥ������
}spell_trigger;

typedef std::map<uint16,uint8> PassiveSpellLevelMap;
typedef std::map<uint32,uint16> PassiveSpellBinLogIndexMap;

//////////////////////////////////////////////////////////////////////////
class Unit:public BinLogObject
{		
public:
	static const uint32_t OBJECT_MODE = core_obj::SYNC_MASTER | core_obj::SYNC_UPDATEDATA;		
	typedef std::set<uint32> UnitSet;
	typedef std::unordered_map<size_t,int> FriendlyMap;
	static Unit* FindUnit(uint32_t guid);	
public:
	Unit();
	virtual ~Unit();
protected:
	void _Create (const string& guid, int entry);
public:
	void WriteCreateBlock(ByteArray &,UpdateMask *int_mask = nullptr,UpdateMask *str_mask = nullptr);
	bool WriteMovePath(ByteArray &);
public:
	void SetStatFloat( uint16 index, float value);
	void SetStatInt32( uint16 index, int32 value);

	virtual void Update( uint32 time );		
	virtual void Calcul_Attr();						//��������
	void SetCalculAttrStage(bool need)
	{
		m_recalcul_Attr = need;
	} //������������
		
	virtual void UpdateLiveStatus(uint32 diff) = 0;	//��������״̬
	bool UpdateLocate(uint32 diff);					//����λ��	
	void UpdateSpellTrigger(uint32 diff);				//���ܴ���������

	virtual void OnKilled(Unit* killer = NULL, uint16 id = 0);			//��ɱ��
	void Respawn(float x=0.0f,float y=0.0f);		//����

	const string &GetAliasName(){return GetStr(UNIT_STRING_FIELD_ALIAS_NAME);};
	void SetAliasName(const char*val){SetStr(UNIT_STRING_FIELD_ALIAS_NAME, val);}

	//���Խӿ�
	int GetEntry() const { return GetUInt16(UNIT_FIELD_UINT16_0, 0); }
	void SetEntry(uint16 entry) { SetUInt16(UNIT_FIELD_UINT16_0, 0, entry); }

	uint8 GetTypeId() const { return GetByte(UNIT_FIELD_BYTE_0, 0); }
	void SetTypeId(uint8 type) {SetByte(UNIT_FIELD_BYTE_0, 0, type);}
	uint32 GetLevel() const {return GetUInt16(UNIT_FIELD_UINT16_0, 1);}
	void  SetLevel(uint16 level){ SetUInt16(UNIT_FIELD_UINT16_0, 1,level);}
	
	//��Ӫ
	//void  SetRace(uint8 fa){SetByte(UNIT_FIELD_BYTES_0,2,fa);}
	uint8 GetGender() const { return GetByte(UNIT_FIELD_BYTE_1, 0); }
	uint8 GetFaction() const {return GetByte(UNIT_FIELD_BYTE_1, 1);}	
	void  SetFaction(uint8 fa){SetByte(UNIT_FIELD_BYTE_1,1,fa);}
	uint8 GetRace() const{return GetByte(UNIT_FIELD_BYTE_1,2);}
	uint8 GetProfession() const{return GetByte(UNIT_FIELD_BYTE_1,3);}
	uint8 GetCreatureSkin() const{return GetByte(UNIT_FIELD_BYTE_4, 2);}

	void resetAttr() {
		uint32 len = UNIT_FIELD_ATTRIBUTE_BASE_END - UNIT_FIELD_MAX_HEALTH_BASE;
		for (uint32 indx = 0; indx < len; ++ indx) {
			this->SetUInt32(indx + UNIT_FIELD_MAX_HEALTH, this->GetUInt32(indx + UNIT_FIELD_MAX_HEALTH_BASE));
		}
	}

	double GetCurrCastVampiric() {
		return GetDouble(UINT_FIELD_VAMPIRIC);
	}

	void ClearCurrCastVampiric() {
		SetDouble(UINT_FIELD_VAMPIRIC, 0);
	}

	uint32 GetRecovery() {
		return GetUInt32(UNIT_FIELD_RECOVERY);
	}

	uint32 GetRecoveryRate() {
		return GetUInt32(UNIT_FIELD_RECOVERY_RATE);
	}
	////��������
	//uint32 GetCombatRate(Combat_Rate rage);
	//void SetCombatRate(Combat_Rate rage,uint32 val);

	/*uint32 GetOutArmor() { return GetUInt32(UNIT_FIELD_OUT_RESISTANCES); }
	uint32 GetInArmor() { return GetUInt32(UNIT_FIELD_IN_RESISTANCES); }
	void SetOutArmor(uint32 val) { SetUInt32(UNIT_FIELD_OUT_RESISTANCES, val); }
	void SetInArmor(uint32 val) { SetUInt32(UNIT_FIELD_IN_RESISTANCES, val); }*/

	uint32 GetHealth()    { return GetUInt32(UNIT_FIELD_HEALTH); }
	uint32 GetMaxHealth() { return GetUInt32(UNIT_FIELD_MAX_HEALTH); }
	void SetHealth(uint32 val, bool isBroadcast = true);
	void SetMaxHealth(uint32 val);
	double ModifyHealth(double val, bool isBroadcast = true);
	//�㲥�����仯
	void BroadcastHp(uint32 hp);

	int GetSP() {return this->GetUInt32(UNIT_FIELD_ANGER);}
	void SetSP(uint32 value) {this->SetUInt32(UNIT_FIELD_ANGER, value);}

	/*uint32 GetPower(Powers power) 
	{ 
	uint32 ret = 0;
	switch (power)
	{
	case POWER_MANA:			
	break;
	case POWER_ENERGY:
	ret = GetUInt32(UNIT_FIELD_POWERS_ENERGY);
	break;		
	default:
	break;
	}
	return ret;
	}*/
	//void SetPower(Powers power, uint32 val);
	//uint32 GetMaxPower(Powers power);
	//void SetMaxPower(Powers power, uint32 val);
	//
	//double ModifyPower(Powers power, double val);
	//void ApplyPowerMod(Powers power, uint32 val, bool apply);
	//void ApplyMaxPowerMod(Powers power, uint32 val, bool apply);

	/*uint32 GetOutDamage(){return GetUInt32(UNIT_FIELD_OUT_DAMAGE);}
	void SetOutDamage(uint32 val){ SetUInt32(UNIT_FIELD_OUT_DAMAGE,val);}
	uint32 GetInDamage(){return GetUInt32(UNIT_FIELD_IN_DAMAGE);}
	void SetInDamage(uint32 val){ SetUInt32(UNIT_FIELD_IN_DAMAGE,val);}*/

	uint32 GetMoveSpeed() {return GetUInt32(UNIT_FIELD_MOVE_SPEED);}
	void SetMoveSpeed(uint32 speed);

	void SetDeathState(uint8 state){
		SetByte(UNIT_FIELD_BYTE_0, 1,state);
	}

	uint8 GetDeathState(){return GetByte(UNIT_FIELD_BYTE_0, 1);}

	//-----------------------------------------------------------------------------------------------
	/*�ƶ����*/		
	void StopMoving(bool need_send=false);	
	void StopMoving(uint16 x,uint16 y);	
	//void MoveTurnAround(float ori,bool toself=false);	//ת��
	void Jump(float x,float y,uint32 time);				//��
	
	virtual void RandomMove(uint32 ms, float x=-1, float y=-1);	
	void MoveTo(float to_x,float to_y)
	{
		float points[] = {to_x,to_y};
		MoveTo(2,points,true);
	}	
    void MoveTo(uint16 size,float *path,bool synchronous = false);	//�ƶ�·��	
	bool IsMoving(){ return m_moving_ms != 0;}						//���������������0˵�����ƶ�״̬

	//ת��Ŀ��
	void TurnToTarget(Unit *target);
	//���һ����Ծʱ��
	uint32 GetLastJump(){return m_last_jump;}
	void SetLastJump(uint32 time){m_last_jump = time;}

	//Ŀ�����
	uint32 GetTargetGuid() const {return m_target_guid;}
	void  SetTarget(Unit* target);	
	Unit* GetTarget();

	//����ҹ���������
	void SetLastVictim(uint32 target_id) 
	{
		m_last_victim_target = target_id;
	}
	uint32 GetLastVictim()const{return m_last_victim_target;}
	//��󹥻��ҵ�����

	//--------------------------------------------------------------------------------------------------------
	//�ж��ж�
	bool isCanMove();			//�ܷ��ƶ�
	bool isCanTeleport();		//�ܷ���
	bool isCanUseItem();		//�Ƿ���ʹ����Ʒ
	bool isInvincible();		//�Ƿ��޵�
	bool isCanSee();			//�Ƿ�ɼ�
	bool isCantAttackByPlayer()const;//�Ƿ�ɱ���ҹ���
	bool isCanRecovery();		//�ܷ�ָ�

	bool isIgnoreTheObstacles();//�����ϰ�
	bool isCanJump();			//�ܷ������Ծ

	//--------------------------------------------------------------------------------------------------------
	//ս����� ����+����

	//����״̬,�����г��״̬ȫ���������
	void ClearAttacker(bool destructor = false);
	//��ӹ�����
	void AddAttacker(Unit *unit);
	//ɾ��������
	void DelAttacker(uint32 unit, bool isDelOwnerShip = false);
	//ȡ�ù������б�
	const UnitSet &GetPlayerAttackSet() const
	{
		return m_attacker_player;
	}
	//ȡ�ù������б�
	const UnitSet &GetUnitAttackSet() const
	{
		return m_attacker_unit;
	}
	//��ұ����﹥��ʱ��ش���
	void DoPVEEvent(Player* target);
	int Acting(Unit* act_target);			//��ʼ����
	int StopActing();						//ֹͣ����
	BOOL isActing(){return m_isActing;}		//�Ƿ��ڱ���״̬

	//״̬����
	bool IsFriendlyTo(Unit const* unit);									//�Ƿ����Ѻõ�Ŀ��	
	void InvalidFriendlyCache(Unit *unit = nullptr);						//�Ѻû���ʧЧ,����ΪĿ���Ҫ�ؽ�,�ҵ�Ŀ��ҲҪ�ؽ�
	void InvalidFriendlyCache(Grid *grid);									//�Ѻû���ʧЧ,���еĸ�������Ķ���
	bool hasUnitState(const uint32 f) const { return ((m_state & f) !=0); }	//�Ƿ��б�ʶ,��ʱֻ����ս��
	void addUnitState(uint32 f) { m_state |= f; }							//���ӱ�ʶս��,��ʱֻ����ս��
	void clearUnitState(uint32 f) { m_state &= ~f; }						//ɾ����ʶս��,��ʱֻ����ս��
	//��������
	virtual float GetAttackDistance (Unit const* )const;

	bool isAlive() const { return (GetByte(UNIT_FIELD_BYTE_0, 1) == DEATH_STATE_ALIVE); }
	bool isCasing()const {return hasUnitState(UNIT_STAT_CAST_SPELL);}
	bool isSpellProcess()const{return hasUnitState(UNIT_STAT_SPELL_PROCESS);}

	//�������
	void CastSpell(uint32 spell_id,float x,float y);				    //��ʼʩ��
	void SpellStop(bool clear_auto_spell = true,bool to_self = true);						//ʩ��ֹͣ
	void CalSpellCastInfo();			    //���㼼���˺�
	void AfterCalSpellCastInfo();			//�˺�����Ժ�

	//��ǰ���ܹ���
	uint32 GetCurSpell() const{return m_cur_spell;}						    //��ȡ��ҵ�ǰ����
	virtual void SetCurSpell(uint32 id);
	uint32 GetCurSpellLevel() const{return m_cur_spell_lv;}
	void SetCurSpellLevel(uint32 level) {m_cur_spell_lv = level;}

	virtual bool HasSpell(uint32 ) {return true;};
	virtual bool IsSpellCD(uint32){return false;};				//�����Ƿ���CD			
	virtual void SetSpellCD(uint32 id) = 0;				//���ܽ���CD

	//����Ŀ���������
	void SetTargetPos(float x,float y){m_target_x = x; m_target_y = y;}	
	void GetTargetPos(float &x,float &y){x = m_target_x; y = m_target_y;}
	float GetTargetX(){return m_target_x;}
	float GetTargetY(){return m_target_y;}

	BufferManager *GetBuffManager(){return m_buff_manager;}

	bool GetIsBlowFly()
	{
		if(m_isBlowFly)
		{
			m_isBlowFly = false;
			return true;
		}
		return false;
	}

	//������
	void BlowFly(Unit* attacker,uint32 space, uint16 &destX, uint16 &destY);

	//----------------------------------------------------------------------//
	//���곯������ӿ�

	//�任����λ�úͳ���
	void Relocate(float x, float y, float orientation)
	{
		SetPosition(x,y);
		m_orientation = orientation;
	}

	float GetPositionX( ) const { return m_positionX; }			//��ȡX����
	float GetPositionY( ) const { return m_positionY; }			//��ȡY����

	void GetPosition( float &x, float &y ) const				//��ȡXY����
	{ x = m_positionX; y = m_positionY;}

	void SetPosition( float x, float y) 
	{ 
		ASSERT(x == x);
		ASSERT(y == y);
		m_positionX = x; 
		m_positionY = y;
	}

	//�任������
	void SetOrientation(float orientation) { m_orientation = orientation; }
	float GetOrientation( ) const { return m_orientation; }		//��ȡ����

	uint16 GetMapId()const {return GetUInt16(UNIT_FIELD_UINT16_1, 0);}
	void SetMapId(uint16 id)
	{
		SetUInt16(UNIT_FIELD_UINT16_1, 0, id);
	}

	uint32 GetInstanceId() const{return GetUInt32(UNIT_FIELD_INSTANCE_ID);}	
	void SetInstanceId(uint32 id){SetUInt32(UNIT_FIELD_INSTANCE_ID, id);}

	//�õ�����Ƕ�
	float GetAngle( const Unit* obj ) const;
	float GetAngle( const float x, const float y ) const;

	//�õ�����
	float GetDistance(const Unit *obj) const;
	float GetDistance(const float x,const float y) const;

	//��Ӽ��ܴ�����
	void AddSpellTrigger(spell_trigger str);

	Grid *GetGrid(){return m_grid;}
	void SetGrid(Grid *_g){m_grid = _g;}

	Map *GetMap()const{ return m_map;};
	void SetMap(Map* _m){m_map = _m;}

	//�Ƿ���Ե���Grid���ڻ״̬
	bool CanActiveGrid() {return m_canActiveGrid;}
	void SetCanActiveGrid(bool status) { m_canActiveGrid =  status;}

	//�ж��Ƿ����ʩ��
	bool IsCantCast();

	uint32 GetUIntGuid() const{return m_uint_guid;}
	// ��þ����±��flag��־
	bool GetUnitFlags(uint32 index){return GetBit(UNIT_FIELD_FLAGS, index);}
	// ���þ����±��flag��־
	void SetUnitFlags(uint32 index){SetBit(UNIT_FIELD_FLAGS, index);}
	// ���þ����±��flag��־
	void UnSetUnitFlags(uint32 index){UnSetBit(UNIT_FIELD_FLAGS, index);}

	hashlist_node m_hash_node;	//���ڹ�ϣ��
protected:	
	uint32 m_uint_guid;			//����guid
	float m_positionX;			//x����				
	float m_positionY;			//y����
	float m_orientation;		//����
	bool m_canActiveGrid;		//�ܼ���Grid
	Grid *m_grid;
	Map *m_map;

	uint32 m_moving_ms;					//�ƶ��굱ǰ����Ҫ����,����0ʱ���ھ�ֹ״̬	
	std::deque<float> m_moving_path;	//�ƶ�·��
	uint32 m_moving_last_diff;			//�ۼ�ʱ���,���ڼ�С�������

	uint32 m_last_victim_target;		//����ҹ���������
	UnitSet m_attacker_unit;					//���﹥����
	UnitSet m_attacker_player;					//��ҹ�����
	Unit*  m_attacking;	
	uint32 m_state;						//ս��״̬	
	uint32 m_cur_spell;					//��ǰħ��
	uint32 m_cur_spell_lv;				//��ǰħ���ȼ�
	uint32 m_auto_spell;				//�Զ�ʩ������
	float m_target_x;					//ħ���ͷ�����
	float m_target_y;
	uint32 m_last_jump;					//�ϴ���Ծʱ��

	BufferManager *m_buff_manager;		//BUFF������

	TimeTracker			m_live_timer;	//����״̬��ʱ��
	CycleTimer	m_spell_process;		//ʩ�����̶�ʱ��

	BOOL m_isActing;					//�Ƿ��ڱ���״̬
	bool m_recalcul_Attr;				//�Ƿ���Ҫ��������
	//bool m_is_del_threat;				//�Ƿ���������
	
	bool m_isBlowFly;					//�Ƿ񱻻���

	uint32 m_update_tick_num;

	uint32 m_target_guid;				//ѡ��Ŀ���guid
	bool m_need_sync_pos;				//�Ƿ���Ҫͬ�����굽�����binlog

	vector<spell_trigger> m_spell_trigger;
	FriendlyMap			m_friendly_cache;//���Թ�����Ŀ��

	PassiveSpellBinLogIndexMap m_index_spellId;	//binlogIndex��Ӧ�ı�������

	PassiveSpellLevelMap m_passive_spell_level;	//�������ܺ͵ȼ�

public:
	typedef std::map<uint32, point_t> HitMeUnitPositionInfo;
	#define RANGE 1
	HitMeUnitPositionInfo positionInfo;

	void removePositionInfo(uint32 cguid) {
		if (positionInfo.find(cguid) != positionInfo.end()) {
			positionInfo.erase(cguid);
		}
	}

	bool getNearestPositionByAngleAndAttackRange(float angle, float attackRange, float tarx, float tary, float& posx, float& posy) {
		
		angle += M_PI;
		uint32 ar = (uint32)attackRange * 2;
		// ���ѭ��
		for (uint32 i = 0; i <= 180; i += 30) {

			float offsetAngle;

			offsetAngle = float(angle + i * M_PI / 180.0);
			for (uint32 range = ar; range >= 3; -- range) {
				const float distanceX = float(range * cos(offsetAngle) / 2.0);
				const float distanceY = float(range * sin(offsetAngle) / 2.0);
				posx = tarx + distanceX;
				posy = tary + distanceY;

				if (!isExist(posx, posy)) {
					return true;
				}
			}

			offsetAngle = float(angle - i * M_PI / 180.0);
			for (uint32 range = ar; range >= 2; -- range) {
				const float distanceX = float(range * cos(offsetAngle) / 2.0);
				const float distanceY = float(range * sin(offsetAngle) / 2.0);
				posx = tarx + distanceX;
				posy = tary + distanceY;

				if (!isExist(posx, posy)) {
					return true;
				}
			}
		}

		return false;
	}

	bool isExist(float x, float y) {

		for (auto it : positionInfo) {
			if (abs(it.second.pos_x - x) <= RANGE && abs(it.second.pos_y - y) <= RANGE) {
				return true;
			}
		}

		return false;
	}

	/*int getNearestAngleIndexWithoutAngles(float angle) {

	std::map<uint8, uint8> vist;

	for (auto it : positionInfo) {
	vist[it.second] = 1;
	}

	if (vist.size() == PIECES) {
	vist.clear();
	}

	float angleInterval = float(M_PI * 2.0 / PIECES);

	int index = -1;
	float diff = 360;
	float curr = -angleInterval;
	for (int i = 0; i < PIECES; ++ i) {
	curr += angleInterval;
	if (vist.find(i) != vist.end())
	continue;

	float absAngle = fabs(curr - angle);
	if (diff > absAngle) {
	diff = absAngle;
	index = i;
	}
	}

	return index;
	}*/

	//////////////////////////////////////////////////////////////////////////
	//for lua script
public:	
	static int LuaGetTarget(lua_State* scriptL);	//ȡ����Ŀ��
	static int LuaSetTarget(lua_State* scriptL);	//��������Ŀ��
	static int LuaCastSpell(lua_State* scriptL);
	static int LuaSetCalculAttr(lua_State* scriptL);//��������

	static int LuaGetPos(lua_State* scriptL);
	static int LuaSetPos(lua_State* scriptL);
	
	static int LuaKillUnit(lua_State* scriptL);		//��ɱ����

	static int LuaIsFriendlyTo(lua_State* scriptL);
	static int LuaInvalidFriendlyCache(lua_State* scriptL);	//�ѺöȻ���ʧЧ
	static int LuaIsCanHit(lua_State* scriptL);
	
	static int LuaIsActing(lua_State* scriptL);

	static int LuaIsInvincible(lua_State* scriptL);
	static int LuaDelThreat(lua_State* scriptL);
	static int LuaSetActing(lua_State* scriptL);
	static int LuaGetMap(lua_State* scriptL);
	static int LuaGetMapID(lua_State* scriptL);

	static int LuaBlowFly(lua_State* scriptL);
	static int LuaRespawn(lua_State* scriptL);
	static int LuaRandomMove(lua_State* scriptL);
	static int LuaSpellStop(lua_State* scriptL);				//ֹͣʩ��
	static int LuaGetCurSpell(lua_State* scriptL);
	static int LuaSetCurSpell(lua_State* scriptL);
	static int LuaHasUnitState(lua_State* scriptL);
	static int LuaAddUnitState(lua_State* scriptL);
	static int LuaIsMoving(lua_State* scriptL);
	static int LuaGetMoveSpeed(lua_State* scriptL);
	static int LuaSetMoveSpeed(lua_State* scriptL);
	static int LuaGetOrientation(lua_State* scriptL);	//���������ƶ��ķ���(���Ƕ�)
	static int LuaSetOrientation(lua_State* scriptL);	//���������ƶ��ķ���(���Ƕ�)
	static int LuaStopMoving(lua_State* scriptL);		//����ֹͣ�ƶ�	
	static int LuaMoveTo(lua_State* scriptL);			//�����ƶ���
	static int LuaGetIntGuid(lua_State* scriptL);		//��þ����int guid

	static int LuaGetMoveEndPos(lua_State *scriptL);	//��ȡ�����ƶ��յ�����
	static int LuaIsCanJump(lua_State* scriptL);		//�����Ƿ������Ծ

	static int LuaAddSpellTrigger(lua_State* scriptL);	//����һ�����ܴ�����
	static int LuaDelSpellTrigger(lua_State* scriptL);	//ɾ��һ�����ܴ�����
	static int LuaSetHealth(lua_State* scriptL);	//����Ѫ��
	static int LuaModifyHealth(lua_State* scriptL);	//�ı�Ѫ��

	static int LuaCallJumpStart(lua_State* scriptL);	//�㲥��ʼ��Ծ

	static int LuaSetOwner(lua_State* scriptL);		//����ӵ���ߣ���������ʱ��Ҫ�ϱ�
};

#endif

