#ifndef _MAP_TEMPLATE_H_
#define _MAP_TEMPLATE_H_

#include "svrcore-internal.h"
#include <gtest/gtest.h>

using std::istream;

enum cell_flags
{
	CELL_FLAGS_OBSTACLE		    = 0X001,			/*�Ƿ��ϰ�,  00000001*/
	CELL_FLAGS_TRANS		    = 0X002,			/*�Ƿ��͸��,00000010*/
	CELL_FLAGS_TRANPORT		    = 0X004,			/*�Ƿ��͵� 00000100*/
	CELL_FLAGS_MUSIC		    = 0X008,			/*�Ƿ���Դ�� 00001000*/
	/*CELL_FLAGS_MOVIE		    = 0X010,*/			/*�Ƿ�̬�� 00010000*/
	CELL_FLAGS_RAISED			= 0X010,			/*�Ƿ񸴻�� 00010000*/
	CELL_FLAGS_NPC			    = 0X020,			/*�Ƿ�NPC��  00100000*/
	CELL_FLAGS_MONSTER		    = 0X040,			/*�Ƿ����� 01000000*/
	CELL_FLAGS_GAMEOBJECT		= 0X080,			/*�Ƿ�������Ϸ����� 10000000*/

};

enum MapInstanceType
{
	MAP_INST_TYP_NO_INSTANCE	= 0,		//���Ǹ���
	MAP_INST_TYP_ACTIVITY		= 1,		//�����,���Ǹ�����ͼ,����,ֻ�е���,�ʱ���Զ��ر�
	MAP_INST_TYP_SINGLETON		= 2,		//���˸������������ֱ�ӹر�
	MAP_INST_TYP_KUAFU			= 3,		//�����ͼ
};

/*��ͼ������Ϣ*/
typedef struct mt_baseinfo_t
{
	uint32	mapid;					/*��ͼID*/
	char	name[255];				/*��ͼ����*/
	char	create_date[16];		/*��ͼ����ʱ��*/
	uint32	px_width;				/*���ؿ�*/
	uint32	px_height;				/*���ظ�*/
	uint32	unit_width;				/*��ש��*/
	uint32	unit_height;			/*��ש��*/
	uint16	width;					/*�߼���*/
	uint16	height;					/*�߼���*/
	uint32	is_instance;			/*�Ƿ񸱱���ͼ*/
	uint32  parentID;               /*������ͼID*/
	char	music[255];		        /*��������*/
	uint32  shadow;                 /*Ӱ�ӷ���*/
	uint32	count;					/*��������*/
	uint32	day_limit;				/*������*/
	uint32	week_limit;				/*������*/
	uint16  instance_type;			/*�������� from enum MapInstanceType*/
} mt_baseinfo;

//���͵�
typedef struct mt_teleport_t
{
	uint16 x;						//X������
	uint16 y;						//Y������
	uint32 temp_id;					//ģ��id
	char name[50];					//���͵�����
	uint32 to_mapid;				//��ͼID
	uint16 to_x;
	uint16 to_y;
} mt_teleport;

//�����
typedef struct mt_raised_t
{
	uint16 x;						//X������
	uint16 y;						//Y������
	uint16 faction;					//��Ӫ
} mt_raised;

//����������Ϣ
typedef struct mt_music_t
{
	uint32 x;
	uint32 y;
	char   file[100];
} mt_music;

//����������
typedef struct mt_trans_t
{
	uint32 x;
	uint32 y;
	char  file[100];
	uint32 width;
	uint32 height;
	uint32 alpha;
} mt_trans;

//����ˢ�µ�
typedef struct mt_monsters_t
{
	uint32 templateid;					//ID
	float x;							//X������
	float y;							//Y������
	uint32 count;						//����
	uint32 respawn_time;				//����ʱ��
	uint32 spawn_type;					//0������ˢ�£�1��ʱˢ��
	uint32 spawn_time1;					//ˢ��ʱ��1
	uint32 spawn_time2;					//ˢ��ʱ��2
	uint32 spawn_time3;					//ˢ��ʱ��3
	char   script_name[50];				//�ű�
	uint32 move_type;					//�ƶ����
	uint32 line_id;                     //��·id 
	uint32 flag;                        //npc��ʶ
	float toward;						//npc����
	char  alias_name[50];				//����,���ڸ���AI�ű����Ҷ���
} mt_monsters;

//��Ϸ����ˢ�µ�
typedef struct mt_gameobject_t
{
	uint32 templateid;					//ID
	float x;							//X������
	float y;							//Y������
	uint32 count;						//����
	uint32 respawn_time;				//����ʱ��
	uint32 spawn_type;					//0������ˢ�£�1��ʱˢ��
	uint32 spawn_time1;					//ˢ��ʱ��1
	uint32 spawn_time2;					//ˢ��ʱ��2
	uint32 spawn_time3;					//ˢ��ʱ��3
	char   script_name[50];				//�ű�
	float  toward;						//����
	char  alias_name[50];				//����

} mt_gameobject;

typedef struct mt_point_t
{
	uint16 pos_x, pos_y;
	uint32 point;
} mt_point;

//����·��
typedef struct mt_monsterline_t
{
	uint32 id;                  //ID
	vector<mt_point> path;      //·�㼯��
} mt_monsterline;

//·���ܱ�·��
typedef struct mt_monsterline_each_t
{
	list<mt_point*> point_each;		//���е�ļ���
	bool is_join;					//�Ƿ���β����
} mt_monsterline_each;

typedef struct mt_point_in_line_t
{
	mt_monsterline_each *each;
	int index;
	uint32 point;
} mt_point_in_line;

//���ɵ��ڵ�
class MainRoadPoint
{
public:
	MainRoadPoint():pos_x(0),pos_y(0),point(0){}
	~MainRoadPoint(){}
public:
	uint16 pos_x;
	uint16 pos_y;
	uint32 point;
	vector<MainRoadPoint*> next_ps;	//�ҵ������ӽڵ�
};


//��ͼʵ������ʱ�� ��
#define INSTANCE_DEL_TIME		600

//���ĵ�Ԫ������
const int MAX_MAP_CELLS_MASK = 400 * 400/32;

//��������֮�����
template<typename T>
inline T GetDistance(T fromX,T fromY,T toX,T toY)
{
	float dx = static_cast<float>(toX) - static_cast<float>(fromX);
	float dy = static_cast<float>(toY) - static_cast<float>(fromY);
	return (T)sqrt(dx*dx + dy*dy);
}

//��ͼģ��
class TEA_SVRCORE_SPEC MapTemplate
{
	friend class Map;
	//��̬
public:
	FRIEND_TEST(MapTemplate, ReadToken);
	FRIEND_TEST(MapTemplate, ReadToken2);
	FRIEND_TEST(MapTemplate, LoadBaseinfo);
	FRIEND_TEST(MapTemplate, LoadObstacle);
	FRIEND_TEST(MapTemplate, _LoadTrans);
	FRIEND_TEST(MapTemplate, _LoadRaised);
	FRIEND_TEST(MapTemplate, LoadTeleport);
	FRIEND_TEST(MapTemplate, _LoadTrunk);
	FRIEND_TEST(MapTemplate, _LoadMusic);
	FRIEND_TEST(MapTemplate, _LoadLight);
	FRIEND_TEST(MapTemplate, _LoadMovie);
	FRIEND_TEST(MapTemplate, _LoadNPC);
	FRIEND_TEST(MapTemplate, LoadCreatrue);
	FRIEND_TEST(MapTemplate, LoadGameObject);
	FRIEND_TEST(MapTemplate, LoadMonsterLine);
	FRIEND_TEST(MapTemplate, IsCanRun);
	FRIEND_TEST(MapTemplate, _LoadInving);

	typedef vector<MapTemplate*> MTVector;
	static MTVector mtvec;					//���е�ͼģ��
	static uint32 m_map_version;			//��ͼ�汾��
	static float safe_distance;			//��ȫ����뾶,Ĭ��Ϊ6

	static bool _ls(string folder, string ext, vector<string>& files);	//����ָ���ļ���
	static bool Load_Version(string folder);
	static bool Load(string folder,bool only_baseinfo=false);
	static void UnLoad()
	{
		for_each(mtvec.begin(), mtvec.end(), safe_delete);
		mtvec.clear();
	}

	static const MapTemplate* GetMapTempalte(uint32 mapid)
	{
		if(mtvec.size() <= mapid)
		{
			return NULL;
		}

		return mtvec[mapid];
	}

	//�˷���
	static int8 around[8][2];
	//�жϳ���
	static int FindAroundIndex(uint16 cnx, uint16 cny, uint16 toX, uint16 toY);
public:
	MapTemplate();
	~MapTemplate();
	bool Load(istream& is,bool only_baseinfo=false);
	bool Load(const char *str,bool only_baseinfo=false);
	bool LoadObstaclePeriphery();			//�����ϰ��ܱ�·��ͼ	
	bool IsCanRun(uint16 x, uint16 y) const
	{
		if(x >= m_baseinfo.width || y >= m_baseinfo.height)
			return false;

		return !IsObstacle(x + m_baseinfo.width * y);		
	}	
	bool IsInMap(uint16 x, uint16 y) const
	{
		if(x >= m_baseinfo.width || y >= m_baseinfo.height)
			return false;
		return true;
	}
	bool IsCanRun(uint32 p) const
	{
		if(p >= uint32(m_baseinfo.width * m_baseinfo.height))
			return false;

		return !IsObstacle(p);		
	}

	// �������·�����ж��Ƿ����ͨ��
	bool IsCanRun(uint16 count, float *path) const;
	bool IsCanRun(float fromX, float fromY,const vector<float>& path) const;	
	bool IsCanRun(float fromX, float fromY, float toX, float toY, bool isStart = false) const;	
	bool IsCanRun(float fromX, float fromY, float toX, float toY, uint16 &lastX, uint16 &lastY, bool isStart = false) const;
	bool IsCanRun(float fromX, float fromY, float toX, float toY, uint16 &lastX, uint16 &lastY, uint16 &cannotx, uint16 &cannoty, bool isStart = false)  const;

	bool IsTeleportPos(uint16 x, uint16 y)
	{
		for(uint32 i = 0; i < m_teleport.size(); i++)
		{
			if(m_teleport[i].x == x && m_teleport[i].y == y)
				return true;
		}

		return false;
	}

	bool FindTeleportPos(mt_teleport& teleport, uint16 x, uint16 y) const
	{
		for(vector<mt_teleport>::const_iterator iter = m_teleport.begin();
			iter != m_teleport.end();
			++iter)
		{
			if(iter->x == x && iter->y == y)
			{
				teleport = *iter;
				return true;
			}
		}

		return false;
	}
	uint32 GetParentMapid() const
	{
		return m_baseinfo.parentID;
	}
	bool IsInstance() const
	{
		return m_baseinfo.is_instance != 0;
	}
	//����Ч����
	bool IsNotValidPos(float x,float y) const
	{
		return x != x || y != y ||
			x < 0.0f || y < 0.0f ||
			x >= float(m_baseinfo.width) || y >= float(m_baseinfo.height);
	}

	MainRoadPoint *GetMainRoadPoint(uint32 point) const;
public:
	//vector<mt_monsters>
	//��ȡ�����
	bool GetSpwanPoint(uint16 &x, uint16 &y,uint16 fation) const;
	bool IsInSafeArea(uint16 x,uint16 y) const;	

	//ͨ�������ȡ��ǰ���õĹ���·��ͼ
	const mt_point_in_line *GetMonsterLineEach(uint32 point) const
	{
		mt_point_in_line *result = NULL;
		map<uint32, mt_point_in_line*>::const_iterator it = m_all_way_point.find(point);
		if(it != m_all_way_point.end())
			result = it->second;
		return result;
	}

	const mt_baseinfo& GetMapBaseInfo() const
	{
		return m_baseinfo;
	}
protected:
	bool LoadBaseinfo(istream &is);			//���������Ϣ
	bool LoadObstacle(istream &is);			//�����ϰ���Ϣ
	bool _LoadTrans(istream &is);			//�����͸����Ϣ
	bool _LoadRaised(istream &is);			//���븴�����Ϣ
	bool LoadTeleport(istream &is);			//���봫�͵���Ϣ
	bool LoadTrunk(istream &is);			//�������ɵ�
	bool _LoadMusic(istream &is);			//����������Ϣ
	bool _LoadLight(istream &is);			//�����Դ
	bool _LoadMovie(istream &is);			//���붯̬��
	bool _LoadNPC(istream &is);				//����NPC��Ϣ
	bool LoadCreatrue(istream &is);			//���������Ϣ
	bool LoadGameObject(istream &is);		//����������Ϸ����
	bool LoadMonsterLine(istream &is);      //�������·��
	bool _LoadInving(istream &is);			//����ˮ����Ϣ
private:
	bool ReadValue(const char *str, char *value)
	{
		strcpy(value, str);
		return true;
	}
	bool ReadValue(const char *str, float& value)
	{
		sscanf(str, "%f", &value);	
		return true;
	}
	template<typename T>
	bool ReadValue(const char *str, T& value)
	{
		int32 temp_int;
		sscanf(str, "%d", &temp_int);
		value = (T)temp_int;
		return true;
	}

	bool ReadToken(istream& is, string& str, char split = ',');

	template<typename T>
	bool ReadToken(istream& is, T& value, char split = ',')
	{
		string str ;
		stringstream ss;

		if(!ReadToken(is, str, split))
			return false;
		ReadValue(str.c_str(), value);
		return true;
	}

	inline bool IsObstacle(uint16 x, uint16 y) const
	{
		return IsObstacle(x + y * m_baseinfo.width);
	}

	inline bool IsObstacle (uint32 index) const
	{
		return ( ( (uint8 *)m_obstacleMask)[ index >> 3 ] & ( 1 << ( index & 0x7 ) )) != 0;
	}
private:
	mt_baseinfo		m_baseinfo;
	vector<uint8>	m_data;			//����λ��ø������µĸ�������
	//UpdateMask 
	uint32 m_obstacleMask[MAX_MAP_CELLS_MASK];		//�ϰ�����Ϣ����
	map<uint32, mt_monsters> m_monsters;	//ˢ�ֵ�
	vector<mt_gameobject> m_gameobjects;	//ˢ��Ϸ�����
	vector<mt_raised> m_spawnpoint;		//�����	

	void *path_pointer;					//·�ߵ���ָ�룬��������ʱ�ͷ�
	void *point_in_line_pointer;		//�����ߵ���ָ�룬��������ʱ�ͷ�
	vector<mt_monsterline_each*> all_monsterline_each;	//����·�ߣ���������ʱ�ͷ�
public:
	vector<mt_teleport> m_teleport;	//���͵�
	map<uint32,MainRoadPoint*> m_main_road;//���ɵ�
	vector<mt_monsterline> m_monsterlines;	//ˢ����·��
	map<uint32, mt_point_in_line*> m_all_way_point;//���й���Ѱ·��ļ���
};

#endif
