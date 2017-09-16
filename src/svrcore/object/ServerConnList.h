#ifndef _SERVER_CONN_LIST_H_
#define _SERVER_CONN_LIST_H_

#include <protocol/internal.h>
#include <object/BinLogObject.h>

#define GLOBAL_SERVER_CONNN_LIST_GUID	"G.serverconnlist"		//�ڲ��������б�
#define GLOBAL_MAP_INSTANCE_LIST_GUID	"G.mapInstanceList"		//��ͼʵ���б�

//�������б�binlog
class ServerConnList : public BinLogObject
{
public:
	ServerConnList(core_obj::SyncMode _m = core_obj::SYNC_SLAVE):BinLogObject(_m)
	{

	}
	void SetServerReadyOKFlag(uint32 conn_id);
	bool GetServerReadyOKFlag(uint32 conn_id);
	//�����ͷ�����һ��������׼���ü�����
	uint32 GetServerReadyCount(int type)
	{
		return GetUInt32(SERVER_CONN_LIST_FIELD_CONN_NUM + type);
	}
	uint32 GetServerConnWorldStatus()
	{
		return GetUInt32(SERVER_CONN_LIST_FIELD_WORLD_STATUS);
	}
	void SetServerConnWorldStatus(uint32 status)
	{
		SetUInt32(SERVER_CONN_LIST_FIELD_WORLD_STATUS, status);
	}
	uint32 GetServerFd(uint32 server_type, bool readok = true);
	uint32 GetCentdFd(){return GetServerFd(SERVER_TYPE_CENTD);}
	uint32 GetAppdFd(){return GetServerFd(SERVER_TYPE_APPD);}
	uint32 GetLogindFd(bool must_readok = true){return GetServerFd(SERVER_TYPE_LOGIND, must_readok);}
	uint32 GetPolicedFd(){return GetServerFd(SERVER_TYPE_POLICED);}

	//����һ���Ĺ����ó���������(����ƽ��)
	uint32 GetScenedFDByType(int inst_typ);
	uint32 ScenedSize();
	void ScenedAddPlayer(uint32 conn_id);
	void ScenedSubPlayer(uint32 conn_id);
	bool HasScenedFd(uint32 connn_id);
	int32 ForEach(std::function<bool(uint32, uint32)> f);
	int32 ForEachScened(std::function<bool(uint32)> f);		//����������
};
#endif

