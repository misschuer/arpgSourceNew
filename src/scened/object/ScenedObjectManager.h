/************************************************************************
* file	:object_manager.h                                                                     
* desc	:���ļ�����Ķ�������,��������Ĵ��� ���� ���� 
*		������½��,���ڸ�����ͼ���еĹ����GUID�����ǲ���Ӧ����һ�ֲ���
*		����ʱ����
*
* author:	linbc
* date:	20110518
* version:
************************************************************************/
#ifndef _SCENED_OBJECT_MANAGER_H_
#define _SCENED_OBJECT_MANAGER_H_

#include <server/svr_object_manager.h>
#include <core_obj/GuidObjectTable.h>
#include <core_obj/GuidObject.h>
#include <core_obj/RemoteOperatorAdapter.h>
#include <core_obj/ByteArrayCompress.h>

class ScenedContext;
class Player;
struct lua_State;

class ScenedObjectManager : public SvrObjectManager
{
public:
	ScenedObjectManager(SvrCoreAppImpl *app);
	virtual ~ScenedObjectManager();

	void Update();
	//���󹤳�
	GuidObject *ObjectFactor(const string &guid);
	//ʵ��GuidObjectTable�Ĵ��������ٷ��������ݶ����ǰ׺����ѡ����Ӧ�Ķ���
	GuidObject* CreateObject(string guid);
	void ReleaseObject(string guid);
	void AsyncCompress(ByteArray& bytes, CompressCallback callback){m_compress_tool.AsyncCompress(bytes, callback);}
	void AsyncSend(uint32 cid,ByteArray *pkt){m_compress_tool.AsyncSend(cid, pkt);}

	void Send(uint32_t connid,ByteArray& bytes);
	
	//�����Ҳ�����־�����ķ�
	void SendPlayerBinlog(ScenedContext *player);
	//ȡ�����unit
	Player *FindPlayer(string guid);
		
	ByteArray *GridMallocByteArray(){return &MallocByteArray();}
	void GridFreeByteArray(ByteArray *bytes){Free(*bytes);}
};

#endif

