#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_
#include <object/BinLogObject.h>

class logind_player;
class MapTemplate;

enum EMapInstanceType
{
	MAP_INSTANCE_INT_TYPE_INSTANCE_ID		= 0,	//��ͼʵ��ID
	MAP_INSTANCE_INT_TYPE_MAP_ID			= 1,	//��ͼ��ID
	MAP_INSTANCE_INT_TYPE_LINENO			= 2,	//�ߺ�
	MAP_INSTANCE_INT_TYPE_SCENED_CONN		= 3,	//��������������ID
	MAX_MAP_INSTANCE_INT_TYPE,

	MAP_INSTANCE_STRING_TYPE_GENERAL_ID		= 0,	//��ͼ��ҹ�����
	MAX_MAP_INSTANCE_STRING_TYPE,
};

#define MAP_INSTANCE_PLAYER_INFO_START_FIELD BINLOG_STRING_FIELD_OWNER + 1	//��ͼ�������Ϣ����ʼ�±�

//��������ʼ��ʱ����Ҫʵ�����Ļ�����ͼ��Ϣ
class InitMapInfo
{
	uint32 map_id;
	string general_id;
};

//��ͼ����
class MapManager : public BinLogObject
{
	//��Ҹ�����Ϣ,���ڱ�������˳����ݴ渱����Ϣ
	struct PlayerInstanceInfo
	{
		string guid;			//��ҵ�λguid
		uint32 expire;			//ʧЧʱ��
		uint32 instanceid;		//��Ҹ���ID
		int32 mapid;			//��ͼID
		float  x;
		float  y;
	};
	typedef std::map<string,PlayerInstanceInfo> PlayerInstanceInfoMap;

public:
	typedef std::map<uint32, std::map<uint16, uint32>> LineInfo;
	static LineInfo lineInfo;
	
	static void lineCreated(uint32 mapid, uint16 lineNo, uint32 instanceId) {
		
		std::map<uint16, uint32> ln;
		if (lineInfo.find(mapid) == lineInfo.end()) {
			lineInfo[mapid] = ln;
		}
		lineInfo[mapid][lineNo] = instanceId;
	}

	static std::map<uint16, uint32> GetMapLines(uint32 mapid) {
		return lineInfo[mapid];
	}

	static void lineRemoved(uint32 mapid, uint16 lineNo) {
		if (lineInfo.find(mapid) == lineInfo.end()) {
			return;
		}
		lineInfo[mapid].erase(lineNo);
	}

	static bool isMapLineCreated(uint32 mapid, uint16 lineNo) {
		
		auto it = lineInfo.find(mapid);
		if (it == lineInfo.end()) {
			return false;
		}

		std::map<uint16, uint32> ln = it->second;
		if (ln.find(lineNo) == ln.end()) {
			return false;
		}

		return true;
	}

public:
	MapManager();
	~MapManager();
	//����������
	void Update(uint32 diff);
	//��Ҵ�������
	void UpdateTeleport(LogindContext *session);
	//�رյ�ͼ������,һ�㷢����û�г����������
	void Close();
	//��ҵ�¼ʱ���߼�
	void PlayerLogin(logind_player *player);
	//��ҵǳ�ʱ���߼�
	void PlayerLogout(logind_player *player);
	//��¼�������޸�
	void Restart();
	//��ͼ��·��
	void HandleMapPkt(packet *pkt);
	//���Թر�ĳһ��ͼ
	bool TryClose(uint32 instance_id);
	//���ҵ�ͼʵ��
	int32 FindInstance(uint32 instanceid);
	int32 FindInstance(uint32 mapid, const string ganeral_id, uint32 lineo);
	int32 FindInstance(const string ganeral_id);
	//�����������
	uint32 PlayerCount(uint32 index);
protected:
	//ִ�д������
	void TeleportTo(LogindContext *session);
	//������ͼʵ��
	int32 CreateInstance(uint32 mapid,const string &general_id,uint32 lineno = 0);
	//���������ر�ʱ
	bool OnScenedClosed(int32 scened_id);	
	//��¼��Ҹ�����¼
	void RecordInstance(logind_player *player);
	//ɾ����Ҹ�����¼��Ϣ
	void DelRecordInstance(logind_player *player);
	//��Ҽ����ͼʵ��
	void AddPlayer(uint32 index, logind_player *player);
	//��Ҽ����ͼ
	bool PlayerJoin(logind_player *player);
	//�ӵ�ͼ��ɾ����ң����ص�ͼʵ������λ��
	int32 DelPlayer(logind_player *player);
public:
	inline uint32 GetInstanceID(int32 index)
	{
		ASSERT(index >= 0);
		return GetUInt32(index * MAX_MAP_INSTANCE_INT_TYPE + MAP_INSTANCE_INT_TYPE_INSTANCE_ID);
	}

	inline int GetMapID(int32 index)
	{
		ASSERT(index >= 0);
		return GetInt32(index * MAX_MAP_INSTANCE_INT_TYPE + MAP_INSTANCE_INT_TYPE_MAP_ID);
	}

	inline uint32 GetLineNo(int32 index)
	{
		ASSERT(index >= 0);
		return GetUInt32(index * MAX_MAP_INSTANCE_INT_TYPE + MAP_INSTANCE_INT_TYPE_LINENO);
	}

	inline uint32 GetScenedConn(int32 index)
	{
		ASSERT(index >= 0);
		return GetUInt32(index * MAX_MAP_INSTANCE_INT_TYPE + MAP_INSTANCE_INT_TYPE_SCENED_CONN);
	}

	inline const string &GetGeneralID(int32 index)const
	{
		ASSERT(index >= 0);
		return GetStr(BINLOG_STRING_FIELD_OWNER + 1 + index * MAX_MAP_INSTANCE_STRING_TYPE + MAP_INSTANCE_STRING_TYPE_GENERAL_ID);
	}

	inline void SetMapInstanceInfo(uint32 index, uint32 instance_id, int parent_id, uint32 lineno, uint32 conn, const string &general_id)
	{
		SetUInt32(index * MAX_MAP_INSTANCE_INT_TYPE + MAP_INSTANCE_INT_TYPE_INSTANCE_ID, instance_id);
		SetInt32(index * MAX_MAP_INSTANCE_INT_TYPE + MAP_INSTANCE_INT_TYPE_MAP_ID, parent_id);
		SetUInt32(index * MAX_MAP_INSTANCE_INT_TYPE + MAP_INSTANCE_INT_TYPE_LINENO, lineno);
		SetUInt32(index * MAX_MAP_INSTANCE_INT_TYPE + MAP_INSTANCE_INT_TYPE_SCENED_CONN, conn);
		SetStr(BINLOG_STRING_FIELD_OWNER + 1 + index * MAX_MAP_INSTANCE_STRING_TYPE + MAP_INSTANCE_STRING_TYPE_GENERAL_ID, general_id);
	}
private:
	//��ǰ֡��������������
	uint32 m_scened_size;
	//��һ�η��ֳ�����������ʱ��
	time_t m_scened_collapse_time;
	//��һ�γ�ʼ����̬��ͼ��ȴ�ʱ�䶨ʱ��
	TimeTrackerSmall m_timer;
	//��Ҹ�����Ϣ,���ڱ�������˳����ݴ渱����Ϣ,����������������������������ݽ���ʧ
	PlayerInstanceInfoMap	m_playerInstInfo;
	uint8 m_teleport_callback_index;

	inline uint32 GetNewInstanceID(){return g_GuidMgr.NewIndex(ObjectTypeMapInstance);}	
	inline const char *GetInstancePlayerInfoID(uint32 instance_id){return g_GuidMgr.MAKE_NEW_GUID(ObjectTypeMapPlayerInfo, instance_id, "");}
	//��Ҽ�����·ID��ĳ��ͼģ��,û���򷵻ؿ�
	int32 HandleGetInstance(logind_player *player,const MapTemplate *parent_mt,uint32 lineno = 0, uint32 mapid = 0);		
	//��������
	int32 ForEach(std::function<bool(uint32 index)>);
	//֪ͨ����������Ҽ����ͼ	
	void Call_Join_Map(uint32 index, logind_player *player);
	void CallDelMapInstance(uint32 index);
	//��鳡����״̬��Ϊ�����ĳ�����������´���
	void UpdateScenedStatus();
	//���ĳ��ͼʵ������������ҵ��µ�ͬ��ͼid��ʵ��
	void ClearInstanceAndTelePlayer(uint32 scened_id, uint32 index);
	//���´������
	void ReTelePlayer(logind_player *player, uint32 scened_id);
	//������ȫ���������Ժ��������еĵ�ͼ��Ϣ��
	void ClearMapInstance();
public:
	static int LuaFindInstance(lua_State* scriptL);				//���ҵ�ͼʵ��
	static int LuaCreateInstance(lua_State* scriptL);			//������ͼʵ��
	static int LuaMapPlayerCount(lua_State *scriptL);			//ͳ��ĳ��ͼ���������
};

#endif

