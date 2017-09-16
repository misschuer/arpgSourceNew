#ifndef _GRID_H_
#define _GRID_H_

#include <object/std.h>
#include "scened_app.h"

//grid�ĸ�������
const int GRID_WIDTH = 15;
const int NOTICE_GRID_SIZE = 9;

class Unit;
class Player;
class Creature;
struct Update_Func;
class GridManager;
class LootObject;
class Map;
namespace core_obj{
class ByteArray;
}

typedef std::set<Player*> PlayerSet;

struct Grid
{	
	typedef vector<Creature*> CreatureList;	
	typedef vector<Unit*> WOList;
	typedef std::set<ByteArray*> BlockSet;
	typedef vector<Grid*> GridPtrVec;
	
	Grid();

	~Grid();

	bool active;
	int x,y;
	//������ͼʵ��
	Map *map_inst;
	//�ڵ�ͼ�ĵڼ���λ��
	int index;

	//grid���µ�ս��Ʒ
	LootObject *loot;

	//��Ҷ���ϵ��	
	PlayerSet players;

	//�������ϵͳ
	CreatureList creatures;

	//������ͼ����
	WOList worldobjs;

	//���ڵ�grid
	GridPtrVec notice_grid;

	//��grid�����귶Χ
	int start_x,end_x;
	int start_y,end_y;

	BlockSet update_blocks;			//���¿�	
	BlockSet create_blocks;			//������
	vector<ByteArray*> out_area_blocks;		//�뿪��Ұ
	vector<ByteArray*> fighting_blocks;		//ս�������
	vector<ByteArray*> unit_move_blocks;	//�����ƶ���
	vector<ByteArray*> unit_jump_blocks;	//������Ծ��

	void ObjectAccess();	

	void SendObjectUpdate();
	void ClearBlock();
	void SendAllNoticeGridToNewPlayer(GridManager *mgr, Player* player);
	void GetCreateBlocForNewPlayer(vector<ByteArray*>& ar, GridManager *mgr = nullptr);
	void GetOutAreaBlockForPlayer(vector<ByteArray*>& ar);
	bool IsNotInThisGrid(int lx,int ly)
	{
		return lx >= end_x || lx < start_x
			|| ly >= end_y || ly < start_y;
	}

	void Broadcast(packet& pkt,Player *player = nullptr,bool self = false) const;
	void AsyncBroadcast(core_obj::ByteArray *pkt,Player *player = nullptr,bool self = false) const;

	template <typename T>
	void ForEachThesePlayer(T func)
	{
		for (GridPtrVec::iterator it = notice_grid.begin();
			it != notice_grid.end(); ++ it)
		{
			for_each(players.begin(),players.end(),func);
		}		
	}

	void AddUpdateBlock(ByteArray* buf);
	void AddCreateBlock(ByteArray* buf);
	void AddOutArea(Unit *wo);
};

//���ӹ���
class GridManager
{
public:
	friend struct Update_Func;
	typedef vector<Grid> GridVec;
	typedef std::set<Grid*> GridPtrSet;

	GridManager(Map *m_,int width,int height,int grid_width = GRID_WIDTH);
	~GridManager();

	void Update(uint32 diff);

	bool AddWatcher(uint32 fd, const string& owner_guid, uint32 map_id, uint32 instance_id);
	void DelWatcher(uint32 fd);

	void AddPlayer(Player *player);
	void DelPlayer(Player *player);//{m_out_area_player.push_back(player);};

	void AddWorldObject(Unit* wo);
	void DelWorldObject(Unit* wo);
	Unit* FindWorldObject(Unit* wo,const string &w_guid);

	void InitLoot(Grid &grid);
	void ClearAllLoot();		//�������ս��Ʒ
	inline Grid *GetGrid(int x,int y)
	{
		ASSERT(x >= 0 && x < m_gwidth);
		ASSERT(y >= 0 && y < m_gheight);
		return &m_grids[y*m_gwidth+x];
	}
	inline Grid& GridCoord(float x,float y)
	{
		return GridCoord(int(x),int(y));
	}
	inline Grid& GridCoord(int x,int y)
	{
		int gx = 0,gy = 0;
		gx = x/m_grid_width;
		gy = y/m_grid_width; 
		return *GetGrid(gx,gy);
	}
	Grid* GridCoordPtr(int x,int y);
	inline void PushNeedFree(ByteArray *bytes)
	{
		m_need_free.insert(bytes);
	}
	void BroadcastToWatcher(packet& pkt);			//�㲥���۲���
	void BroadcastToWatcher(ByteArray& pkt);			
	void SendUpdateDate(uint32 fd, vector<ByteArray*>& ud);
private:	

	void SendFightingBlocks(Grid*);
	void CalcNoticeGrid(Grid* grid);
	void RefreshGrid(Unit* wo);
	void RefreshGridIdle(Grid& grid);
	void RefreshGridStatus(Grid& grid);
	void SetGridIdleStatus(Grid& grid,bool active);
	
	GridVec m_grids;

	GridPtrSet m_active_grid;

	vector<Unit*> m_wo_need_refresh_grid;
	Grid::BlockSet m_need_free;

	int m_width,m_height;		//�߼�������
	int m_gwidth,m_gheight;		//grid���	
	int m_grid_width;
	set<uint32> m_watchers;
};

#endif

