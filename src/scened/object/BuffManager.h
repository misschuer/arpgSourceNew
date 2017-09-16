#ifndef _BUFF_MANAGER_H_
#define _BUFF_MANAGER_H_

#include <object/std.h>
class Unit;

class BufferManager
{
public:
	BufferManager(Unit* buff_owner);
	~BufferManager();

public:
	static int LuaAddBuff(lua_State* scriptL);
	static int LuaSystemAddBuff(lua_State* scriptL);
	static int LuaRemoveBuff(lua_State* scriptL);
	static int LuaHasBuff(lua_State* scriptL);
	static int LuaGetBuffLevel(lua_State* scriptL);
	static int LuaSetBuffLevel(lua_State* scriptL);
	static int LuaGetReserveVal(lua_State* scriptL);
	static int LuaSetReserveVal(lua_State* scriptL);
	static int LuaGetBuffDuration(lua_State* scriptL);
	static int LuaSetBuffDuration(lua_State* scriptL);
	static int LuaGetBuffGiverUnit(lua_State* scriptL);		//���buff giver�Ķ���

public:
	void Update(uint32 diff);								//����						
	void UpdateBuff();										//BUFF��ʱ��
	inline uint16 GetBuff(uint8 pos);								//��ȡBUFF

	void AddBuffAttr();										//����BUFF����		
	bool RemoveBuff(uint16 buff_id);						//�Ƴ�BUFF			
	void AddBuff(uint16 buff_id, uint32 buffEffectId=0,int32 bonus_time = 0, const char* name = NULL, const char* guid = NULL, uint32 reserve = 0);							//����BUFF
	uint8 HasBuff(uint16 buff_id);							//�Ƿ���BUFF

	uint16 GetBuffDurationByID(uint16 buff_id);					//��ȡBUFF����ʱ��
	void SetBuffDurationByID(uint16 buff_id,uint16 duration);	//����BUFF����ʱ��

	uint32 GetReserveVal(uint16 buff_id);					//��ȡbuffԤ��ֵ
	void SetReserveVal(uint16 buff_id, uint32 reserve);		//����buffԤ��ֵ

	void ClearBuff();										//���BUFF	
	void UpDateHasBuffId();									//����buffid
	uint32 GetBuffEffectId(uint16 buff_id);						//��ȡBUFFЧ��id
	void SetBuffLevelByID(uint16 buff_id, uint32 buffEffectId);		//����BUFFЧ��id
	uint32 GetBuffGiverGuidByID(uint16 buff_id);					//����buffid���giver guid
private:
	inline bool IsBuffTrigger(uint8 pos);		//BUFF�Ƿ񴥷�	
	inline uint32 GetBuffDuration(uint8 pos);						//��ȡBUFF����ʱ�� ��0~11��
	inline void SetBuffDuration(uint8 pos,uint32 time);				//����BUFF����ʱ��
	inline void ReduceBuffTime(uint8 pos);							//����BUFF����ʱ��


	inline void SetBuff(uint8 pos,uint16 buff_id,uint32 buffEffectId);		//��ȡBUFF ID ��0~11��
	inline void SetBuffReserve(uint8 pos,uint32 val);				//����Ԥ��ֵ
	inline uint32 GetBuffEffectId(uint8 pos);							//��ȡBUFF�ȼ�
	inline void SetBuffLevel(uint8 pos,uint32 buffEffectId);		//����BUFFЧ��id	
	inline bool IsBuffOver(uint8 pos);								//buff�Ƿ����
	inline void RemoveBuff(uint8 pos);								//�Ƴ�BUFF
	inline void SetBuffGiverGuid(uint8 pos, uint32 guid);			//����buff giver��Guid	
	uint32 GetBuffGiverGuid(uint8 pos);							//���buff giver��Guid
private:
	Unit* m_buffOwner;
	TimeTracker m_buff_timer;	
	uint32 m_last_time;
	uint32 m_update_tick_num;
	uint32 m_ms_last_time;
	std::map<uint16,uint8> m_has_buffid;			//����ӵ�е�buffid
	vector<uint8> m_diff_need_del_buff;				//����������ʱ����Ҫɾ����BUFFλ��
};

#endif

