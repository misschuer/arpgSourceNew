
#include "map_template.h"
#include <fstream>
#include <iosfwd>
#include <math.h>
#include <iostream>
#include <core_obj/UpdateMask.h>

using core_obj::UpdateMask;

//////////////////////////////////////////////////////////////////////////
//for map_template static
MapTemplate::MTVector MapTemplate::mtvec;
uint32 MapTemplate::m_map_version;
stringstream temp_strline_stream;		//�м����
float MapTemplate::safe_distance = 6.0f;

#if PLATFORM == PLATFORM_WINDOWS

bool MapTemplate::_ls(string folder, string ext, vector<string>& files)
{
    string searchstr = folder + "/*." + ext;

    HANDLE handle;
    WIN32_FIND_DATA ffd;

    if((handle = FindFirstFile(searchstr.c_str(), &ffd)) == INVALID_HANDLE_VALUE)
        return false;

    do
    {
        files.push_back(folder + "/" + ffd.cFileName);
    }
    while(FindNextFile(handle, &ffd));

    FindClose(handle);
    return true;
}
#else

#include <sys/dir.h>
#include <sys/stat.h>

//�ж��Ƿ�ΪĿ¼

int IS_DIR(const char* path)
{
    struct stat st;
    lstat(path, &st);
    return S_ISDIR(st.st_mode);
}

bool MapTemplate::_ls(string folder, string ext, vector<string>& files)
{
    DIR *pdir;
    struct dirent *pdirent;
    string temp;

    if((pdir = opendir(folder.c_str())))
    {
        while((pdirent = readdir(pdir)))
        {
            //����"."��".."
            if(strcmp(pdirent->d_name, ".") == 0
                    || strcmp(pdirent->d_name, "..") == 0)
                continue;

            temp = folder + "/" + pdirent->d_name;

            //�����Ը���չ����β
            if(temp.substr(temp.size() - ext.size(), ext.size()) != ext)
                continue;

            files.push_back(temp);

            //��tempΪĿ¼����recursiveΪ1��ʱ��ݹ鴦����Ŀ¼
            if(IS_DIR(temp.c_str()))
                continue;

            //_ls(temp, ext,files);

        }
    }
    else
    {
        printf("opendir error:%s\n", folder.c_str());
        return false;
    }

    closedir(pdir);
    return true;
}

#endif

//���ذ汾
bool MapTemplate::Load_Version(string folder)
{
	//���زİ汾��
	string map_index_file = folder  + "index.map";
	std::ifstream ifsversion(map_index_file.c_str(), std::ios::in);
	string version;
	if(!getline(ifsversion, version))
		return false;
	//��ͼID
	Tokens tokens;
	StrSplit(tokens,version,',');
	if (!tokens.size())
	{
		return false;
	}
	MapTemplate::m_map_version = atoi(tokens[0].c_str());
	return true;
	//if(!ReadToken(is,m_map_version))
	//	return false;
}

bool MapTemplate::Load(string folder,bool only_baseinfo)
{
    vector<string> files;
    if(!_ls(folder, "txt", files) || files.size() == 0)
        return false;
	
	if (!Load_Version(folder))
	{
		//tea_perror
		return false;
	}
	
    for(vector<string>::const_iterator it = files.begin();
            it != files.end();
            ++it)
    {
        std::ifstream ifs(it->c_str(), std::ios::in);	

        MapTemplate *mt = new MapTemplate();

        if(!mt->Load(ifs,only_baseinfo))
        {
            delete mt;
            return false;
        }

        if(mtvec.size() <= mt->m_baseinfo.mapid)
            mtvec.resize(mt->m_baseinfo.mapid + 1, 0);

        mtvec[mt->m_baseinfo.mapid] = mt;
        ifs.close();
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//for map_template

MapTemplate::MapTemplate():path_pointer(NULL), point_in_line_pointer(NULL)
{
    memset(&m_baseinfo, 0, sizeof(m_baseinfo));
}

MapTemplate::~MapTemplate()
{
	if(path_pointer != NULL)
	{
		for(vector<mt_monsterline_each*>::iterator it = all_monsterline_each.begin(); it != all_monsterline_each.end(); ++it)
		{
			delete *it;
		}
		free(point_in_line_pointer);
		free(path_pointer);
	}
	safe_delete(m_main_road);
}


// �������·�����ж��Ƿ����ͨ��
bool MapTemplate::IsCanRun(float fromX,float fromY,const vector<float>& path) const
{
	if(path.empty())
		return IsCanRun((uint16)fromX,(uint16)fromY);

	//��һ��,�����ϰ�
	if(!IsCanRun((uint16)fromX, (uint16)fromY))
		return true;
	
    if(!IsCanRun((float)fromX, (float)fromY, (float)path[0], (float)path[1], true))    
        return false;    
	
	//����жϣ�����ͨ����������
	for (int i = 0; i < (int)path.size(); i = i + 2)
	{
		if(!IsCanRun((float)fromX,(float)fromY, (float)path[i],(float)path[i+1]))
		{
#if PLATFORM == PLATFORM_WINDOWS
			printf("MapTemplate::IsCanRun can not run %f,%f to %f,%f", fromX,fromY, path[i],path[i+1]);
#endif
			return false;
		}
		fromX = path[i];
		fromY = path[i+1];
	}  
    return true;
}

// �������·�����ж��Ƿ����ͨ��
bool MapTemplate::IsCanRun(uint16 count, float *path) const
{
    float *tpath, x0, y0, x1, y1;
    tpath = path;

    if(count > 1)
    {
        x1 = *tpath;
        tpath++;
        y1 = *tpath;
        tpath++;
        bool isStart = true;
        x0 = x1;
        y0 = y1;
        x1 = *tpath;
        tpath++;
        y1 = *tpath;
        tpath++;

		/*if(isStart && x1 == x0 && y0 == y1)
		{
		isStart = false;
		}*/

        if(!IsCanRun(x0, y0, x1, y1, isStart))
        {
#if PLATFORM == PLATFORM_WINDOWS
			printf("MapTemplate::IsCanRun can not run %f,%f to %f,%f", x0, y0, x1, y1);
#endif
            return false;
        }

        //����жϣ�����ͨ����������
        for(uint16 i = 4; i < count; i += 2)
        {
            x0 = x1;
            y0 = y1;
            x1 = *tpath;
            tpath++;
            y1 = *tpath;
            tpath++;

            if(! IsCanRun(x0, y0, x1, y1, isStart))
            {
#if PLATFORM == PLATFORM_WINDOWS
				printf("MapTemplate::IsCanRun can not run %f,%f to %f,%f", x0, y0, x1, y1);
#endif
                return false;
            }

            isStart = false;
        }
    }
    else
    {
        x0 = *tpath;
        tpath++;
        y0 = *tpath;
        return IsCanRun((uint16)x0, (uint16)y0);
    }

    return true;
}

//���������յ㣬�ж��ǿ���ͨ��
bool MapTemplate::IsCanRun(float fromx, float fromy, float tox, float toy, bool isStart) const
{
	int32 x0 = (int32)fromx, y0 = (int32)fromy, x1 = (int32)tox, y1 = (int32)toy;
	int32 dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int32 dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int32 err = dx + dy, e2; /* error value e_xy */	

	for(;;)
	{
		/* loop */
		if(!IsCanRun(x0, y0) && !isStart)
		{
			//#if PLATFORM == PLATFORM_WINDOWS
			//			printf("�޷�ͨ����·��(%f,%f)(%f,%f)���꣺(%d,%d)\n", fromx, fromy, tox, toy, x0, y0);
			//#endif
			return false;
		}

		isStart = false;

		if(x0 == x1 && y0 == y1) break;

		e2 = 2 * err;

		if(e2 >= dy)
		{
			err += dy;    /* e_xy+e_x > 0 */
			x0 += sx;
		}

		if(e2 <= dx)
		{
			err += dx;    /* e_xy+e_y < 0 */
			y0 += sy;
		}
	}

	return true;
}

bool MapTemplate::IsCanRun(float fromX, float fromY, float toX, float toY, uint16 &lastX, uint16 &lastY, bool isStart) const
{
	uint16 nx = 0, ny = 0;
	return IsCanRun(fromX, fromY, toX, toY, lastX, lastY, nx, ny, isStart);
}

bool MapTemplate::IsCanRun(float fromx, float fromy, float tox, float toy, uint16 &lastX, uint16 &lastY, uint16 &cannotx, uint16 &cannoty, bool isStart) const
{
	int32 x0 = (int32)fromx, y0 = (int32)fromy, x1 = (int32)tox, y1 = (int32)toy;
	int32 dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int32 dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int32 err = dx + dy, e2; /* error value e_xy */
	lastX = 0;
	lastY = 0;

	for(;;)
	{
		/* loop */
		if(!IsCanRun(x0, y0) && !isStart)
		{
			cannotx = x0;
			cannoty = y0;
//#if PLATFORM == PLATFORM_WINDOWS
//			printf("�޷�ͨ����·��(%f,%f)(%f,%f)���꣺(%d,%d)\n", fromx, fromy, tox, toy, x0, y0);
//#endif
			return false;
		}

		lastX = x0;
		lastY = y0;
		isStart = false;

		if(x0 == x1 && y0 == y1) break;

		e2 = 2 * err;

		if(e2 >= dy)
		{
			err += dy;    /* e_xy+e_x > 0 */
			x0 += sx;
		}

		if(e2 <= dx)
		{
			err += dx;    /* e_xy+e_y < 0 */
			y0 += sy;
		}
	}

	return true;
}

bool MapTemplate::Load(istream& is,bool only_baseinfo)
{
    //�����������Ϣ
    if(!LoadBaseinfo(is))
        return false;

	//���ֻ���������Ϣ��ֱ�ӷ���
	if(only_baseinfo)
		return true;

    //�����ϰ���Ϣ
    if(!LoadObstacle(is))
        return false;


    //����͸����
    if(!_LoadTrans(is))
        return false;

    //���븴�����Ϣ
    if(!_LoadRaised(is))
        return false;

    //���봫�͵���Ϣ
    if(!LoadTeleport(is))
        return false;

    //�������ɵ���Ϣ
    if(!LoadTrunk(is))
        return false;

    //����������Ϣ
    if(!_LoadMusic(is))
        return false;

    //�����Դ��Ϣ
    if(!_LoadLight(is))
        return false;

    //���붯̬��
    if(!_LoadMovie(is))
        return false;

    //���������Ϣ
    if(!LoadCreatrue(is))
        return false;

    //������Ϸ����
    if(!LoadGameObject(is))
        return false;

    //�����ƶ���·
    if(!LoadMonsterLine(is))
        return false;

    return true;
}

//���������Ϣ
bool MapTemplate::LoadBaseinfo(istream &_is)
{
    string str;		

    if(!getline(_is, str))
        return false;

	//string gbk_str;
	//utf8ToConsole(str,gbk_str);

    stringstream is(str);
    std::cout << "LoadBaseinfoing" << std::endl;

    //��ͼID
    if(!ReadToken(is, m_baseinfo.mapid))
        return false;

	 std::cout << "mapid = " << m_baseinfo.mapid << std::endl;

    //��ͼ����
    if(!ReadToken(is, m_baseinfo.name))
        return false;

    //��ͼ����ʱ��
    if(!ReadToken(is, m_baseinfo.create_date))
        return false;

    //���ؿ�
    if(!ReadToken(is, m_baseinfo.px_width))
        return false;

    //���ظ�
    if(!ReadToken(is, m_baseinfo.px_height))
        return false;

    //��ש��
    if(!ReadToken(is, m_baseinfo.unit_width))
        return false;

    //��ש��
    if(!ReadToken(is, m_baseinfo.unit_height))
        return false;

    //�߼���
    if(!ReadToken(is, m_baseinfo.width))
        return false;

    //�߼���
    if(!ReadToken(is, m_baseinfo.height))
        return false;

    //�Ƿ񸱱���ͼ
    if(!ReadToken(is, m_baseinfo.is_instance))
        return false;

    //������ͼID
    if(!ReadToken(is, m_baseinfo.parentID))
        return false;

    //��������
    if(!ReadToken(is, m_baseinfo.music))
        return false;

    //Ӱ�ӷ���
    if(!ReadToken(is, m_baseinfo.shadow))
        return false;

    //��������
    if(!ReadToken(is, m_baseinfo.count))
        return false;

    //������
    if(!ReadToken(is, m_baseinfo.day_limit))
        return false;

    //������
    if(!ReadToken(is, m_baseinfo.week_limit))
        return false;

	//��������
	if(!ReadToken(is, m_baseinfo.instance_type))
        return false;

    //��ʼ���߼���������
    //m_obstacleMask.SetCount(m_baseinfo.width * m_baseinfo.height);	
	ASSERT(m_baseinfo.width * m_baseinfo.height <= MAX_MAP_CELLS_MASK*32);
    std::cout << "LoadBaseinfoed OK" << std::endl;

    return true;
}

bool MapTemplate::LoadObstacle(istream &_is)
{
    string str;

    if(!getline(_is, str))
        return false;

    if(str.empty())
        return true;

	char m_temp_str[100000];
	char *token[100000];
	uint32 len;
	strcpy(m_temp_str, str.c_str());
	str_split(m_temp_str, ",", token, &len, true, true, 100000);
	
	memset(m_obstacleMask,0,sizeof(m_obstacleMask));
    //�ϰ���
    uint32 obs, i = 0;

    while(i < len)
    {
		ReadValue(token[i], obs);
		ASSERT(m_obstacleMask);
		m_obstacleMask[i] = obs;
        i++;
    }

    return true;
}


int8 MapTemplate::around[8][2] = {{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};
//�жϳ���
int MapTemplate::FindAroundIndex(uint16 fromX, uint16 fromY, uint16 toX, uint16 toY)
{
	int diffx, diffy;
	int around_index;
	//������죬������ȡ����
	diffx = fromX - uint16(toX);
	diffy = fromY - uint16(toY);
	//ͨ�����췢�ַ���
	for(around_index = 0; around_index < 8 && (around[around_index][0] != diffx || around[around_index][1] != diffy); around_index++);

	//û�ҵ��������Գ��������⡣
	if(around_index >= 8)
	{
		//tea_pdebug("�����ٽ��ĵ㣬�޷��õ�����");
		return -1;
	}
	//Ϊ���ð˷��������γ�Բ��ѭ�����ֱ��Ӹ��˱Ƚ�ˬ
	return around_index + 8;
}

//�����ϰ��ܱ�·��ͼ
bool MapTemplate::LoadObstaclePeriphery()
{
	clock_t cstart;
	cstart = clock();
	uint32 map_size = m_baseinfo.width * m_baseinfo.height, sum = 0, monster_point_sum;
	uint32 insert_sum = 0;
	UpdateMask all_site;
	map<uint32, mt_monsterline_each*> monsterline_each;

	//��Ū�������ϰ��Աߵĵ�
	all_site.SetCount(map_size);
	for(uint16 x = 0; x < m_baseinfo.width; ++x)
	{
		for (uint16 y = 0; y < m_baseinfo.height; ++y)
		{
			//������ϰ��㣬�Ϳ����ܱ���û�з��ϰ���
			if(IsObstacle(x,y))
			{
				//ֻ�����������ĸ�������Ϊб�ǵĲ���Ҫ�У�������߲���45�Ƚǵ��ϰ�
				for(uint8 i = 1; i < 8; i += 2)
				{
					if((x == 0 && around[i][0] == -1)
						||(y == 0 && around[i][1] == -1)
						||(x == m_baseinfo.width - 1 && around[i][0] == 1)
						||(y == m_baseinfo.height - 1 && around[i][1] == 1))
						continue;
					uint16 x1 = x + around[i][0], y1 = y + around[i][1];
					uint32 point = x1 + m_baseinfo.width * y1;
					if(!IsObstacle(point) && all_site.GetBit(point) == 0)
					{
						all_site.SetBit(point);
						sum++;
					}
				}
			}			
		}
	}
	monster_point_sum = sum;
	path_pointer = malloc(sizeof(mt_point) * monster_point_sum);
	point_in_line_pointer = malloc(sizeof(mt_point_in_line) * monster_point_sum);
	uint32 load_index = 0;
	//��ʼ�ѵ�������	
	while(sum > 0)
	{
		int index;
		uint16 x, y, nx, ny;
		uint32 all_site_index = 0;
		list<mt_point_in_line*> plList;//���ɵ����еĵ�������Ϣ
		mt_monsterline_each *eachPoint = new mt_monsterline_each;//���ɵ�
		all_monsterline_each.push_back(eachPoint);
		//�ҵ���һ�����õ�
		for(; all_site_index < map_size && all_site.GetBit(all_site_index) == 0 ; all_site_index++);
		uint32 point = all_site_index;
		all_site.UnSetBit(all_site_index);
		sum--;
		x = point % m_baseinfo.width;
		y = point / m_baseinfo.width;
		//���ɵ�����
		mt_point_in_line *pl = (mt_point_in_line*)point_in_line_pointer + load_index;
		pl->each = eachPoint;
		pl->point = point;
		plList.push_back(pl);
		//���ɵ�
		mt_point *mp = (mt_point*)path_pointer + load_index++;
		mp->point = point;
		mp->pos_x = x;
		mp->pos_y = y;
		eachPoint->point_each.push_back(mp);
		eachPoint->is_join = true;
		monsterline_each[point] = eachPoint;
		while(sum > 0)
		{
			bool found = false;
			uint32 point_next = 0;
			for(uint8 i = 0; i < 8; i++)
			{
				nx = x + around[i][0];
				ny = y + around[i][1];
				point_next = nx + m_baseinfo.width * (ny);
				if(point_next >= map_size || all_site.GetBit(point_next) == 0)
					continue;
				index = FindAroundIndex(nx,ny,x,y);
				if(index != -1)
				{
					//�����б�ǣ�����Ҫ��߻����ұ���һ����ͬ���ϰ���
					//��������ڵĵ㣬����Ҫ��ͬһ����������ͬ���ϰ���
					//�ø���
					if	(
							(
								//�����б�ǣ�����Ҫ��߻����ұ���һ����ͬ���ϰ���
								index % 2 == 0 
								&& 
								(
									IsObstacle(nx - around[(index - 1) % 8][0], ny - around[(index - 1) % 8][1])
									|| IsObstacle(nx - around[(index + 1) % 8][0], ny - around[(index + 1) % 8][1])
								)
							)
							|| 
							(
								//��������ڵĵ㣬����Ҫ��ͬһ����������ͬ���ϰ���
								index % 2 == 1 
								&& 
								(
									(IsObstacle(nx - around[(index - 1) % 8][0], ny - around[(index - 1) % 8][1]) && IsObstacle(nx - around[(index - 2) % 8][0], ny - around[(index - 2) % 8][1]))
									|| (IsObstacle(nx - around[(index + 1) % 8][0], ny - around[(index + 1) % 8][1]) && IsObstacle(nx - around[(index + 2) % 8][0], ny - around[(index + 2) % 8][1]))
								)
							)
						)
					{
						//���ɵ�����
						mt_point_in_line *pl = (mt_point_in_line*)point_in_line_pointer + load_index;
						pl->each = eachPoint;
						pl->point = point_next;
						//���ɵ�
						mt_point *p = (mt_point*)path_pointer + load_index++;
						p->point = point_next;
						p->pos_x = nx;
						p->pos_y = ny;
						//�ֲ����뼯��
						if(eachPoint->is_join)
						{
							plList.push_back(pl);
							eachPoint->point_each.push_back(p);
						}
						else
						{
							plList.push_front(pl);
							eachPoint->point_each.push_front(p);
							insert_sum++;
						}
						point = point_next;
						monsterline_each[point] = eachPoint;
						x = nx;
						y = ny;
						all_site.UnSetBit(point_next);
						sum--;
						found = true;
						break;
					}
				}
			}
			if(!found)
			{
				if(!eachPoint->is_join)
					break;
				point_next = eachPoint->point_each.front()->point;
				if(eachPoint->point_each.size() != 2)//̫�����ɺ��ˣ��ڶ���
				{
					if(point_next == point)
						break;	//����ͼ����Ҳ̫�����˰ɣ�һ���ϰ�����һ�����վ���ĵط���������
					else
					{
						nx = point_next % m_baseinfo.width;
						ny = point_next / m_baseinfo.width;
						index = FindAroundIndex(nx,ny,x,y);
						if(index != -1)
							break;
					}
				}
				point = eachPoint->point_each.front()->point;
				x = eachPoint->point_each.front()->pos_x;
				y = eachPoint->point_each.front()->pos_y;
				eachPoint->is_join = false;
			}
		}

		//OK���������ɵ������еĵ�ŵ�����Ѱ·��ļ�����
		uint32 pl_index = 0;
		for (list<mt_point_in_line*>::iterator pl_it = plList.begin(); pl_it != plList.end(); ++pl_it, pl_index++)
		{
			(*pl_it)->index = pl_index;
			m_all_way_point[(*pl_it)->point] = (*pl_it);
		}
		
	}
	printf("��ͼ��%2d��:��%4d�����㣬��%4d�����ɵ�����ʱ��%4d�����롣\n",m_baseinfo.mapid, monster_point_sum, int(all_monsterline_each.size()), int(clock() - cstart));
	return true;
}

bool MapTemplate::_LoadTrans(istream &_is)
{
    string str;

    if(!getline(_is, str))
        return false;

    return true;
}

bool MapTemplate::_LoadRaised(istream &_is)
{
    //fuhuodian
    string str;

    if(!getline(_is, str))
        return false;

    if(str.empty())
        return true;

    stringstream is(str);

    uint32 x;

	mt_raised raised;
    while(ReadToken(is, x))
    {
        memset(&raised, 0, sizeof(raised));
        raised.x = x;

        if(!ReadToken(is, raised.y))
            return false;

		if(!ReadToken(is, raised.faction))
            return false;

        m_spawnpoint.push_back(raised);
    }

    return true;
}


bool MapTemplate::LoadTeleport(istream &_is)
{
    string str;

    if(!getline(_is, str))
        return false;

    if(str.empty())
        return true;

    stringstream is(str);
    uint32 x = 0;
    mt_teleport teleport;

    while(ReadToken(is, x))
    {
        memset(&teleport, 0, sizeof(teleport));
        teleport.x = x;

        if(!ReadToken(is, teleport.y))
            return false;

        if(!ReadToken(is, teleport.temp_id))
            return false;

        if(!ReadToken(is, teleport.name))
            return false;	
		
        if(!ReadToken(is, teleport.to_mapid))
            return false;

        if(!ReadToken(is, teleport.to_x))
            return false;

        if(!ReadToken(is, teleport.to_y))
            return false;

        m_teleport.push_back(teleport);
    }

    return true;
}

bool MapTemplate::LoadTrunk(istream &_is)
{
    string str;

    if(!getline(_is, str))
        return false;

	stringstream is(str);
	uint16 x = 0, n_x = 0, n_y = 0;
	map<MainRoadPoint *, vector<uint32>> next_ps;
	while(ReadToken(is, x))
	{
		MainRoadPoint *point = new MainRoadPoint;
		point->pos_x = x;
		ReadToken(is, point->pos_y);
		point->point = point->pos_x + m_baseinfo.width * point->pos_y;
		uint32 len = 0;
		ReadToken(is, len);
		vector<uint32> next_v;
		next_v.resize(len);
		for (uint32 i = 0; i < len; i++)
		{
			ReadToken(is, n_x);
			ReadToken(is, n_y);
			next_v[i] = n_x + m_baseinfo.width * n_y;
		}
		next_ps[point] = next_v;
		this->m_main_road[point->point] = point;
	}
	for (auto it:next_ps)
	{
		MainRoadPoint *point = it.first;
		for (auto p:it.second)
		{
			auto it_point = this->m_main_road.find(p);
			ASSERT(it_point != this->m_main_road.end());
			point->next_ps.push_back(it_point->second);
		}
	}
    return true;
}

bool MapTemplate::_LoadMusic(istream &is)
{
    string str;

    if(!getline(is, str))
        return false;

    return true;
}

bool MapTemplate::_LoadLight(istream &is)
{
    string str;

    if(!getline(is, str))
        return false;

    return true;
}

bool MapTemplate::_LoadMovie(istream &is)
{
    string str;

    if(!getline(is, str))
        return false;

    return true;
}

bool MapTemplate::LoadCreatrue(istream &_is)
{
    string str;

    if(!getline(_is, str))
        return false;

    if(str.empty())
        return true;

	char m_temp_str[100000];
	char *token[100000];
	uint32 len;
	strcpy(m_temp_str, str.c_str());
	str_split(m_temp_str, ",", token, &len, true, true, 100000);


    uint32 temp_id = 0, i = 0;
    mt_monsters monsters;

    while(i < len)
    {
		ReadValue(token[i++], temp_id);

        memset(&monsters, 0, sizeof(monsters));
        monsters.templateid = temp_id;

        if(!ReadValue(token[i++], monsters.x))
            return false;

        if(!ReadValue(token[i++], monsters.y))
            return false;

        if(!ReadValue(token[i++], monsters.count))
            return false;

        if(!ReadValue(token[i++], monsters.spawn_type))
            return false;

        if(!ReadValue(token[i++], monsters.respawn_time))
            return false;

        if(!ReadValue(token[i++], monsters.spawn_time1))
            return false;

        if(!ReadValue(token[i++], monsters.spawn_time2))
            return false;

        if(!ReadValue(token[i++], monsters.spawn_time3))
            return false;

        if(!ReadValue(token[i++], monsters.script_name))
            return false;

        if(!ReadValue(token[i++], monsters.move_type))
            return false;

        if(!ReadValue(token[i++], monsters.line_id))
            return false;

        if(!ReadValue(token[i++], monsters.flag))
            return false;

        if(!ReadValue(token[i++], monsters.toward))
            return false;

		if(!ReadValue(token[i++], monsters.alias_name))
            return false;

        monsters.toward = monsters.toward * M_PI;
        uint32 pos = (uint32)monsters.x + m_baseinfo.width * (uint32)monsters.y;

        m_monsters[pos] = monsters;
    }

    return true;
}

bool MapTemplate::LoadGameObject(istream &_is)
{
    string str;

    if(!getline(_is, str))
        return false;

    if(str.empty())
        return true;

    stringstream is(str);

    uint32 temp_id = 0;
    mt_gameobject gameobject;

    while(ReadToken(is, temp_id))
    {
        memset(&gameobject, 0, sizeof(gameobject));
        gameobject.templateid = temp_id;

        if(!ReadToken(is, gameobject.x))
            return false;

        if(!ReadToken(is, gameobject.y))
            return false;

        if(!ReadToken(is, gameobject.count))
            return false;

        if(!ReadToken(is, gameobject.spawn_type))
            return false;

        if(!ReadToken(is, gameobject.respawn_time))
            return false;

        if(!ReadToken(is, gameobject.spawn_time1))
            return false;

        if(!ReadToken(is, gameobject.spawn_time2))
            return false;

        if(!ReadToken(is, gameobject.spawn_time3))
            return false;

        if(!ReadToken(is, gameobject.script_name))
            return false;

        if(!ReadToken(is, gameobject.toward))
            return false;

		if(!ReadToken(is, gameobject.alias_name))
            return false;

        gameobject.toward = gameobject.toward * M_PI;
        m_gameobjects.push_back(gameobject);
    }

    return true;
}

bool MapTemplate::LoadMonsterLine(istream &_is)
{
    string str;
    getline(_is, str);

    if(str.empty())
        return true;

    stringstream is(str);

    uint32 temp_id = 0;
    int32 point_len;
    mt_point point1;
    mt_monsterline monsterline;

    while(ReadToken(is, temp_id))
    {
        monsterline.path.clear();
        monsterline.id = temp_id;

        if(!ReadToken(is, point_len))
            return false;

        for(int j = 0; j < point_len; j++)
        {
            if(!ReadToken(is, point1.pos_x))
                return false;

            if(!ReadToken(is, point1.pos_y))
                return false;

            monsterline.path.push_back(point1);
        }

        if(m_monsterlines.size() <= monsterline.id)
            m_monsterlines.resize(monsterline.id + 1);

        m_monsterlines[monsterline.id] = monsterline;
    }

    return true;
}

bool MapTemplate::_LoadInving(istream &is)
{
    string str;

    if(!getline(is, str))
        return false;

    return true;
}

bool MapTemplate::ReadToken(std::istream &is,  std::string &str , char split)
{
    //���
    str.clear();

    char c = 0;

    while(is.good())
    {
        c = is.get();

        if(split != c && is.good())
            str.push_back(c);
        else
            return true;

    }

    //������
    if(str.empty())
        return false;

    //
    return true;
}

bool MapTemplate::GetSpwanPoint(uint16 &x, uint16 &y,uint16 fation) const
{
    if(m_spawnpoint.empty())
        return false;

	uint16 min_dist = uint16(-1);		//�������
	uint16 fX = x,fY = y;
	for (auto it = m_spawnpoint.begin();it != m_spawnpoint.end();++it)
	{
		if(it->faction == 0 || it->faction == fation)
		{
			auto dist = GetDistance(fX,fY,it->x,it->y);
			if(dist < min_dist)
			{
				min_dist = dist;
				x = it->x;
				y = it->y;
				return true;
			}
		}		
	}
	
    return false;
}

bool MapTemplate::IsInSafeArea(uint16 x,uint16 y) const
{
	for (auto iter = m_spawnpoint.begin();iter!=m_spawnpoint.end();++iter)
	{
		if(GetDistance(x,y,iter->x,iter->y) < safe_distance && !IsInstance())
			return true;
	}
	return false;
}

MainRoadPoint *MapTemplate::GetMainRoadPoint(uint32 point) const
{
	map<uint32, MainRoadPoint*>::const_iterator it = m_main_road.find(point);
	ASSERT(it != m_main_road.end());
	return it->second;
}
