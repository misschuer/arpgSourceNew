#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scened_app.h"
#include <object/SharedDef.h>
#include "Unit.h"
#include <object/PlayerBase.h>

class ScenedContext;
class Map;
class QuestGetter;

typedef std::map<uint16,uint32> ImportanceSpellCDMap;
typedef std::map<uint16,uint8> SpellLevelMap;
typedef std::map<uint16,uint32> SpellCDMap;
typedef std::multimap<uint8, uint16> SlotMultiSpellMap;
typedef std::vector<Creature*> PetVec;
typedef vector<uint32> AttrsVec;
typedef vector<AttrsVec> All_AttrsVec;
typedef std::map<string,uint32> CounterMap;	
typedef std::map<uint32,uint32> SpellStyleMap;

typedef struct buff_info_t
{
	uint32 buff_id;
	uint32 duration;
	uint32 lv;
} BuffInfo;

//ϵ�������ڵ���GM�������Ϸ�е�һЩϵ��
struct Coefficient 
{
	Coefficient()
	{
		speed_multiples = 100;
		exp_multiples = 100;
		drop_rate_multiples = 100;
		attack_multiples = 100;
		def_multiples = 100;
		hp_multiples = 100;
		mp_multiples = 100;		
		waza_multiples = 100;
		eva_multiples = 100;
		crit_multiples = 100;
	}
	float speed_multiples;			//�ٶȱ��ʣ����֧��5��
	float exp_multiples;			//���鱶�ʣ����֧��100��
	float drop_rate_multiples;		//������ʱ��� ���100��
	float attack_multiples;			//�������ʡ�֧��100�� ��ͬ
	float def_multiples;			//�������ʡ�
	float hp_multiples;				//HP���ʡ�
	float mp_multiples;				//MP���ʡ�
	float waza_multiples;			//���б��ʡ�
	float eva_multiples;			//���㱶�ʡ�
	float crit_multiples;			//�������ʡ�
};

#define SKILL_INTERVAL 300

class Player:public Unit
{
	friend class ScenedContext;
public:
	Player();
	virtual ~Player();
public:
	//Ū��һ��vlaues����
	void Create (ScenedContext *session);

	void Update(uint32 p_time);					//��ʱ��	
	void UpdateAutoRecovery(uint32 diff);		//�Զ��ظ��Լ�ս��״̬����,	
	void UpdateLiveStatus(uint32 diff);			//��������״̬
	void UpdateFCMLoginTime(uint32 diff);		//�����ۻ�����ʱ��	

	void OnKilled(Unit* killer, uint16 id = 0);
	void OnSendKilled(Player* killer, uint16 id);	//�������ɱ,����Ӧ�÷���д��־
	void OnJoinMap();
	void OnLeaveMap();

	//��������Ժ󴥷�
	void OnAfterPlayerDataUpdate(SyncEventRecorder *,int,UpdateMask&,UpdateMask&);

	//��׼ʱ��ת����������ʱ��
	uint32 TimestampToServerRuntime(uint32 value);

	//����������ʱ��ת��׼ʱ��
	uint32 ServerRuntimeToTimestamp(uint32 value);

	//ͬ��
	void SyncUnitToPlayerData();
public:
	ScenedContext *GetSession(){ return m_session;}	
	void SetSession(ScenedContext *_s){m_session = _s;}
	QuestGetter *GetQuestMgr(){return m_questMgr;}

	//��ȡ����
	void GainExp(double exp,uint8 type = 0,double vip_exp = 0);

	//����	
	bool Upgrade ();
	//����������
	void Upgrade_Calculate(uint32 prevLevel);
	//��ȡ���ѵȼ�
	uint8 GetPayLevel(){return GetByte(UNIT_FIELD_BYTE_2, 1);}

	//ս����
	double GetForce() {return GetDouble(UNIT_FIELD_FORCE);}
	void SetForce(double f)
	{
		SetDouble(UNIT_FIELD_FORCE,f);
	}

	//��ȡ����ģʽ
	uint8 GetAttackMode() const{return GetByte(UNIT_FIELD_BYTE_3,3);}
	//���ù���ģʽ
	void SetAttackMode(uint8 mode){SetByte(UNIT_FIELD_BYTE_3,3,mode);}
	//PVP��һЩ��ش���
	void DoPvPEvent(Player* target);
	//PVB����ش�����Ҵ�boss��
	void DoPvBEvent(Unit* target);

	//��ȡ����ʱ��
	uint8 GetRedNameTime()const{return GetByte(UNIT_FIELD_BYTE_2,0);}
	void  SetRedNameTime(uint8 time){SetByte(UNIT_FIELD_BYTE_2,0,time);}

	//�һ�״̬
	bool IsHungUp();
	void SetHungUp(bool is_hung_up);
	//pvp״̬
	void SetPVPstate(bool flag = true);
	//��ȡpvp״̬��bitλ
	bool GetPVPstate();
	//�Ƿ��ڰ�ȫ��
	bool isInSafeArea()const;
	
	//�Ƿ��ڸ�����ͼ��
	bool IsInTheInstanceMap()
	{
		return MapTemplate::GetMapTempalte(GetMapId())->IsInstance();
	}
	//���ĳ��־λ
	bool GetPlayerFlags(int offset)
	{
		return GetBit(UNIT_FIELD_FLAGS, offset);
	}

	// ���þ���ı����±�
	void SetGOData(uint32 data){SetUInt32(GO_FIELD_DATA+3,data);}

public:
	//-----------------------------------------------------------------------------------------
	void Calcul_Attr();					//���¼����������
	Coefficient &GetCoefficient(){return m_coefficent;}
	void SetCoefficient(string str,uint16 multiples);
	void Calcul_Coefficient();			//���Խ���ϵ������
	bool IsReasonableDistancePos(Unit *obj);			//�Ƿ�������
public:
	//�������	
	virtual void SetSpellCD(uint32 id);	

public:
	bool isFighting(){return !m_combat_state.Passed();}
	void resetCombatStateTime();
	
	void SetPeaceModeCDIfEnabled();

	bool isPVP(){return !m_PVP_state.Passed();}	//�Ƿ���PVPս����
	void resetPVPStateTime();				//����PVP��ʱ��

	//�ж��Ƿ񷴻�
	bool IsCounter(const Unit * unit);
public:
	BinLogObject *GetEquipAttrs(){return m_equip_attrs;}
	//---------------------------------------------------------------------------
	QuestGetter		*m_questMgr;											//���������
	
	SpellCDMap m_spell_cd;						//����cd����
	ImportanceSpellCDMap m_importance_spell_cd;	//��Ҫ����cd����
	SlotMultiSpellMap m_slot_spell;				//���ܲ۶�Ӧ�ļ���
	SpellStyleMap m_spell_style;				//������ʽ

	SpellLevelMap m_spell_level;				//�ڼ��ܲ��еļ��ܺ͵ȼ�

	// �滻����
	void slotReplaceSpell(uint8 slot, uint16 spell, uint8 level);

	void SetCurSpell(uint32 id);

	bool m_can_calcul_attr;		   //�Ƿ�������������

	//�������һ�ν��ն�������ʱ��
	void SetLastActionPktTime()
	{
		m_last_action_pkt_time = ms_time();
	}

	void SetLastSpellTime() {
		m_last_spell_time = ms_time();
		//printf("set last spell time = %u\n", m_last_spell_time);
	}

	/************************************************************************/
	/* �Ƿ����ʹ�ü���(���SKILL_INTERVAL����)                                                                     */
	/************************************************************************/
	bool canUseSkill() {
		uint32 now = ms_time();
		//printf("compare now = %u, last = %u, diff = %d", now, m_last_spell_time, now - m_last_spell_time);
		return now >= m_last_spell_time + SKILL_INTERVAL;
	}

	//�鿴�����Ƿ����ʹ��GO
	bool CanUseGameObject()
	{
		uint32 now = ms_time();
		uint32 diff =  get_time_diff(m_last_action_pkt_time,now);
		//��һ���µ�ʱ���
		//m_last_action_pkt_time = now;
		return diff > g_Config.use_gameobject_diff;
	}
	
	//��ȡ��ǰս��״̬
	uint8 GetCurFightStatus()
	{
		return m_cur_combet_state;
	}

	void SetPeaceModeCD(uint32 cd);

	uint32 GetPeaceModeCD();

	uint16 GetBattleMode();

	void SetBattleMode(uint16 mode);

	uint32 GetSelfProtectUintGuid() {
		return GetUInt32(UNIT_FIELD_SELF_DEFENSE_GUID);
	}

	void SetSelfProtectUintGuid(uint32 guid) {
		SetUInt32(UNIT_FIELD_SELF_DEFENSE_GUID, guid);
	}

	// ��ùһ��Զ���ҩ�ٷֱ�
	uint16 GetHookHpPercents() {
		return GetUInt16(PLAYER_FIELD_HOOK_SHORT, 0);
	}

	// ��ùһ��Զ���ҩ��id
	uint16 GetHookUseItemId() {
		return GetUInt16(PLAYER_FIELD_HOOK_SHORT, 1);
	}

	// ��ùһ�״̬
	bool isInHook() {
		return GetUInt32(PLAYER_FIELD_HOOK) > 0;
	}

	// ����ս��
	void fightStatusEnter();

	// �뿪ս��
	void ChangeFightStatusToLeave();
	
	void DelPet(Creature *unit);
	void DelPet(uint32 entry);
	void AddPet(Creature *unit);
	void ClearPet(){m_pets.clear();}//ֻ�����ڵ�ͼ�ͷŵ�ʱ��ʹ��

	//ͨ��ģ�����npc�� ��ͬһ�ŵ�ͼҪ�ǳ�������һģһ����npc�ǾͲ��ð��ˣ��������ã���ѯlhs��
	Unit* FindNPC(const uint32 npc_entry);

	double GetExp()
	{
		return m_player_exp;
	}

	void lostExp(uint16 rate);

	void DoIfNeedAddProtectBuff();

protected:
	void UnitToPlayerUint32(uint32 index, uint32 player_index);
	void UnitToPlayerDouble(uint32 index, uint32 player_index);
	void UnitToPlayerString(uint32 index, uint32 player_index);
	void UnitByteToPlayerUInt32(uint32 index, uint8 offset, uint32 player_index);
	void UnitUInt16ToPlayerUInt32(uint32 index, uint8 offset, uint32 player_index);
	void UnitUInt32ToPlayerDouble(uint32 index, uint32 player_index);
	void UnitByteToPlayerByte(uint32 index, uint8 offset, uint32 player_index, uint8 player_offset);
	void UnitByteToPlayerDouble(uint32 index,uint8 offset, uint32 player_index);
	void UnitUInt16ToPlayerDouble(uint32 index,uint8 offset, uint32 player_index);

	void SyncCacheData();		//ͬ����������
private:
	ScenedContext	*m_session;
	BinLogObject *m_equip_attrs;//���װ�����ԣ���������ϵͳ�����Լӳ�
	CounterMap m_counter_map;			//�����б�

	uint8 m_gm_level;
	Coefficient m_coefficent;			//ϵ��
	uint8 m_cur_combet_state;			//��ǰս��״̬
	uint32 m_exp_bonus;					//��װ����ӳ�
	uint32 m_last_action_pkt_time;		//���Ķ���������ʱ��
	uint32 m_last_spell_time;			//���ļ��ܰ�����ʱ��
	double daZuoStartTimestamp;			//�����Ŀ�ʼʱ���
	double m_player_exp;				//��Ҿ���
	static char m_tmp[128];					//����IDת���õ�

	TimeTrackerSmall	m_combat_state;			//ս��״̬��ʱ��
	TimeTrackerSmall	m_PVP_state;			//�Ƿ���PVP��
	TimeTrackerSmall	m_auto_recovery;		//�Զ��ô����趨ʱ��
	TimeTrackerSmall	m_energy_auto_recovery ;//�Զ����嶨ʱ��
	TimeTrackerSmall    m_endurance_recovery;	//�Զ��ؾ�����ʱ��

	IntervalTimer		m_fcm_timer;			//�����Զ�ʱ��	
	IntervalTimer		m_red_name_timer;		//����ʱ�䶨ʱ��	
	IntervalTimer		m_counter_timer;		//����ʱ�䶨ʱ��
	IntervalTimer		m_dazuo_timer;			//������Ѫ������ʱ��
	IntervalTimer		m_hp_timer;				//��������Ѫ��ʱ��

	PetVec				m_pets;
	map<uint32, int32>	m_bingzhong_spells_cd;			//���ּ���CD
	//////////////////////////////////////////////////////////////////////////
	//for lua script
public:

	static int LuaGetPlayerGuid(lua_State* scriptL);
	static int LuaGetSession(lua_State* scriptL);				//��ȡ�Ự,ͬʱҲ��������������ݶ���
	//����ӿ�
	static int LuaGetQuestStatus(lua_State* scriptL);			//���ָ�������״̬
	static int LuaAcceptQuest(lua_State* scriptL);				//��ҽ�������
	static int LuaHasQuest(lua_State* scriptL);					//�Ƿ����������
	static int LuaPrintSlotQuest(lua_State* scriptL);			//����������������id(������)
	static int LuaHasQuestType(lua_State* scriptL);				//�Ƿ���ĳ�������͵�����
	static int LuaCompleteCurQuest(lua_State *scriptL);			//��ɵ�ǰָ�����͵�����
	static int LuaCompleteQuestId(lua_State *scriptL);			//��ɵ�ǰָ��������
	static int LuaGetQuestCounter(lua_State* scriptL);			//�Ƿ����������		
	static int LuaAddQuestItem(lua_State* scriptL);				//���������Ʒ
	static int LuaRemoveQuestItem(lua_State* scriptL);			//ɾ��������Ʒ
	static int LuaClearQuestSlotItem(lua_State* scriptL);		//��������±���Ʒ
	static int LuaTalkedToCreature(lua_State* scriptL);			//������Ի�
	static int LuaAreaExploredOrEventHappens(lua_State* scriptL);//�¼�����
	static int LuaAddQuestItemBySlot(lua_State* scriptL);		//���������±����

	static int LuaGetSpellCD(lua_State* scriptL);		//��ȡ����cd
	static int LuaSetSpellCD(lua_State* scriptL);		//���ü���cd
	static int LuaSetImportanceSpellCD(lua_State* scriptL);		//������Ҫ����cd
	static int LuaGetSpellLevel(lua_State* scriptL);	//��ü��ܵȼ�
	static int LuaSetSpellLevel(lua_State* scriptL);	//���ü��ܵȼ�

	static int LuaGetDaZuoStartTime(lua_State* scriptL);	//��ô�����ʼʱ��
	static int LuaSetDaZuoStartTime(lua_State* scriptL);	//���ô�����ʼʱ��

	//��ô���id
	static int LuaGetTeleportID(lua_State* scriptL);

	//����
	static int LuaTeleport(lua_State* scriptL);
	
	//�����Ʒ
	static int LuaAddItem(lua_State* scriptL);

	//����
	static int LuaUpgrade(lua_State* scriptL);

	//������С��
	static int LuaClearPets(lua_State *scriptL);

	static int LuaIsInSaveArea(lua_State* scriptL);			//�Ƿ��ڰ�ȫ����

	static int LuaGetCounters(lua_State* scriptL);			//��ȡ������
	static int LuaIsCounter(lua_State* scriptL);			//����Ƿ񷴻�ģʽ
	
	static int LuaGetPlayeCurFightStatus(lua_State* scriptL);	//��ȡ��ҵ�ǰ��ս��״̬

	static int LuaIsLogined(lua_State* scriptL);	//�ж�����Ƿ��Ѿ���¼������

	static int LuaGetEquipAttrs(lua_State* scriptL);	//��ȡ��Ҹ�ϵͳ������
	//��þ���
	static int LuaAddExp(lua_State* scriptL);
	//�۾���
	static int LuaSubExp(lua_State* scriptL);
	//����ϵ��
	static int LuaSetCoefficient(lua_State *scriptL);
	//֪ͨӦ�÷�����money
	static int LuaSendAddMoney(lua_State* scriptL);		
	//֪ͨӦ�÷���money
	static int LuaSendSubMoney(lua_State* scriptL);
	//֪ͨӦ�÷���������
	static int LuaSendRecalculate(lua_State* scriptL);		
	static int LuaGetPetTable(lua_State* scriptL);	//������ҵĳ����б�
	//�������㿪��
	static int LuaSetCanRecalcuAttr(lua_State* scriptL);
	//������
	static int LuaAddGiftPacks(lua_State* scriptL);
	//��ӹ۲���
	static int LuaAddWatcher(lua_State* scriptL);
	static int LuaGetSpellStyle(lua_State* scriptL);		//��ȡ���һ��ʹ�õļ������еļ���id
	static int LuaSetSpellStyle(lua_State* scriptL);		//�������һ��ʹ�õļ������еļ���id

	static int LuaGetSlotSpell(lua_State* scriptL);		//���ĳһ��λ����

	static int LuaSendMountJumpDown(lua_State* scriptL);		//�������

	static int LuaLostExpOnDead(lua_State* scriptL);		//�������侭��

	static int LuaSetNeedProtectBuff(lua_State* scriptL);		//�����Ƿ���Ҫ��������

	static int LuaSendToAppdDoSomething(lua_State* scriptL);	//���͵����������н����߼��ж�

	static int LuaSendToAppdAddOfflineMail(lua_State* scriptL);

	static int LuaGetAllPlayerNearBy(lua_State *scriptL);	//��ȡ���������

	static int LuaSetPlayerEnterOrigin(lua_State *scriptL);	// ������ҵĽ��븱����λ��
};

extern uint16 AttrTypePos[MAX_EQUIP_ATTR];

#endif

