#ifndef _A_STAR_PATH_FNDING_
#define _A_STAR_PATH_FNDING_

#include <svrcore.h>
#include <stack>
#include <vector>
#include <shared/map_template.h>

//�Թ���ͼ�нڵ����ͱ��
enum{
	NODE_EMPTY,//����ͨ���Ľڵ�
	NODE_OBSTACLE,//�ϰ������ͨ��
	NODE_PATH//·���ϵĵ�
};

//��¼·���ϵĵ������
typedef struct tagpathNode{
	int x,y;
}PathNode;

//�ڵ����ݽṹ����
class StarNode
{
public:
	StarNode();
	~StarNode(){}
public:
	static vector<StarNode*> AllNode;
	static void FreeNode();
public:
	MainRoadPoint *main_road_point;//�ɵ���
	uint16 x,y;//��ǰ�����Թ��е�λ������
	int g;//��ʼ�㵽��ǰ��ʵ�ʴ���
	int h;//��ǰ�ڵ㵽Ŀ��ڵ����·���Ĺ��ƴ���
	int f;//���ƺ�����f = g + h��
	StarNode *father;//ָ���丸�ڵ��ָ��
	StarNode *child;//ָ���丸�ڵ��ָ��
};

//����STL���ȶ��е�����ʽ
class HeapCompare_f{
public:
	bool operator()(StarNode* x,StarNode* y) const
	{
		return x->f > y->f;//���ݹ��ۺ�������������������
	}
};

//�Թ�Ѱ·��A*�㷨
class PathFinding{
public:
	PathFinding();
	~PathFinding();
private:
	const MapTemplate *m_map;
	uint16 m_startX,m_startY;//��ʼ������
	uint16 m_endX,m_endY;//Ŀ�������

	uint32 point_start,	dis_start,	point_end, dis_end;//�ɵ�Ѱ·�õı���
	set<uint32> m_point_set;

	char s_key[30];

	StarNode *m_start_node,*m_end_node,*m_main_start_node,*m_main_end_node;//��ʼ�ڵ��Ŀ��ڵ�
	int m_steps;//���������ѵ��ܲ���

	//OPEN������C++ STL��vectorʵ�����ȼ����й���
	//ע�⣺�洢����StarNode*ָ��
	std::vector<StarNode*> m_open_table;
	//CLOSED���洢��Ҳ��StarNode*ָ��
	std::vector<StarNode*> m_close_table;
	map<string, std::vector<float>> m_path_data;
private:
	//���õ�ͼģ��
	void SetMapTemplate(uint32 mapid);
	//���ÿ�ʼ��ͽ�����
	void SetStartEndPoint(uint16 startX, uint16 startY, uint16 endX, uint16 endY);
	//����·����Ϣ
	void generatePath();
	//���Ƶ�ǰ�㵽Ŀ���ľ��룺�����پ���
	int judge(int x,int y);
	//�ͷ�
	void FreeNode();
	//��ÿɴ������
	void GetCangoPoint(uint16 &startx, uint16 &starty, StarNode *&next_node);
	//A�Ǹɵ�
	bool AstarMainRoad();
	//A�Ǽ��������ֵ
	int AstarCalculate(StarNode *node, MainRoadPoint *point);
	//Ѱ·
	bool Finding();
public:
	vector<float> m_path;
public:
	//Ѱ·������
	bool pathFinding(uint32 mapid, uint16 startX, uint16 startY, uint16 endX, uint16 endY);
public:
	static int LuaPathfindingGoto(lua_State* scriptL);	//Ѱ·ǰ��
	static int LuaRandomPos(lua_State* scriptL);		//��ȡ�������
	static int LuaIsCanRun(lua_State *scriptL);			//�ж������Ƿ�Ϸ�	
};


#endif //_A_STAR_PATH_FNDING_
