#ifndef _LOGIND_OBJECT_MANAGER_H_
#define _LOGIND_OBJECT_MANAGER_H_

#include "logind_app.h"
#include <server/svr_object_manager.h>
#include <core_obj/GuidObjectTable.h>
#include <core_obj/GuidObject.h>
#include <core_obj/RemoteOperatorAdapter.h>
#include <core_obj/ByteArrayCompress.h>

class logind_player;


//���������Ķ��󰡣���ͼ�ڵ���Ϣ
#define MAP_INSTANCE_PLAYER_INFO_OWNER_STRING "map_player_info"

//GLOBAL_SAVE_TO_DB�ı�����ʼ�±�
#define SAVE_PLAYER_GUID_STR_TO_SERVER_NAME BINLOG_STRING_FIELD_OWNER + 1
#define SAVE_PLAYER_GUID_STR_BEGIN BINLOG_STRING_FIELD_OWNER + 2
//
#define SAVE_PLAYER_GUID_INT_TODAY	0		//���α�����ĵı䶯����
#define SAVE_PLAYER_GUID_INT_COUNT	1		//�������
#define SAVE_PLAYER_GUID_INT_INDEX	2		//���������
#define SAVE_PLAYER_GUID_INT_FLAG	3		//һЩ��־λ

enum ESavePlayerGuidFlag
{
	SAVE_PLAYER_GUID_FLAG_POST	= 0,		//�Ƿ�ʹ��Post�ķ�ʽ��������
	MAX_SAVE_PLAYER_GUID_INT_FLAG,
};
class SavePlayerGuidObj: public BinLogObject
{
public:
	SavePlayerGuidObj():BinLogObject(core_obj::SYNC_LOCAL){
		SetBinlogMaxSize(MAX_BINLOG_SIZE_UNLIME);
	}
	~SavePlayerGuidObj(){}
public:
	const string &GetToServerName(){return GetStr(SAVE_PLAYER_GUID_STR_TO_SERVER_NAME);}
	void SetToServerName(const string &server_name){SetStr(SAVE_PLAYER_GUID_STR_TO_SERVER_NAME, server_name);}

	const string &GetSavePlayerGuid(int i){return GetStr(SAVE_PLAYER_GUID_STR_BEGIN + i);}
	void SetSavePlayerGuid(uint32 i, const string &guid){SetStr(SAVE_PLAYER_GUID_STR_BEGIN + i, guid);}
	
	uint32 GetToday(){return GetUInt32(SAVE_PLAYER_GUID_INT_TODAY);}
	void SetToday(uint32 today){SetUInt32(SAVE_PLAYER_GUID_INT_TODAY, today);}

	uint32 GetCount(){return GetUInt32(SAVE_PLAYER_GUID_INT_COUNT);}
	void SetCount(uint32 count){SetUInt32(SAVE_PLAYER_GUID_INT_COUNT, count);}

	uint32 GetIndex(){return GetUInt32(SAVE_PLAYER_GUID_INT_INDEX);}
	void AddIndex(){AddUInt32(SAVE_PLAYER_GUID_INT_INDEX, 1);}
	void SetIndex(uint32 count){SetUInt32(SAVE_PLAYER_GUID_INT_INDEX, count);}

	void SetPost(){SetBit(SAVE_PLAYER_GUID_INT_FLAG, SAVE_PLAYER_GUID_FLAG_POST);}
	void UnSetPost(){UnSetBit(SAVE_PLAYER_GUID_INT_FLAG, SAVE_PLAYER_GUID_FLAG_POST);}
	bool GetPost(){return GetBit(SAVE_PLAYER_GUID_INT_FLAG, SAVE_PLAYER_GUID_FLAG_POST);}
};

class LogindObjectManager : public SvrObjectManager
{
public:
	LogindObjectManager(SvrCoreAppImpl *app);
	virtual ~LogindObjectManager();

	//���󹤳�
	GuidObject *ObjectFactor(const string &guid);
	//ʵ��GuidObjectTable�Ĵ��������ٷ��������ݶ����ǰ׺����ѡ����Ӧ�Ķ���
	GuidObject* CreateObject(string guid);
	void ReleaseObject(string guid);

	//��¡һ��binlog
	BinLogObject *Clone(BinLogObject *obj);

	//�������е����
	void ForEachPlayer(std::function<void(logind_player*)> func);	
	//ȡ�����
	logind_player* FindPlayer(const string& guid);
	
	void CollapseReset();
	//��ȡ��Ҷ���
	bool LoadPlayer(const string &guid, logind_player **player, vector<GuidObject*> &vec);
	//�����ķ�ɾ���������������
	void RemovePlayerData(const string &guid);
private:
	void Send(uint32_t connid,ByteArray&);

	ByteArrayCompress m_compress_tool;
};

#endif
