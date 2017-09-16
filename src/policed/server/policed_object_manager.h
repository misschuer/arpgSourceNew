#ifndef _POLICED_OBJECT_MANAGER_H_
#define _POLICED_OBJECT_MANAGER_H_

#include "policed_app.h"
#include <server/svr_object_manager.h>
#include <core_obj/GuidObjectTable.h>
#include <core_obj/GuidObject.h>
#include <core_obj/RemoteOperatorAdapter.h>
#include <core_obj/ByteArrayCompress.h>

class PolicedContext;

class PolicedObjectManager : public SvrObjectManager
{
public:
	PolicedObjectManager(SvrCoreAppImpl *app);
	virtual ~PolicedObjectManager();

	//���󹤳�
	GuidObject *ObjectFactor(const string &guid);
	//ʵ��GuidObjectTable�Ĵ��������ٷ��������ݶ����ǰ׺����ѡ����Ӧ�Ķ���
	GuidObject* CreateObject(string guid);
	void ReleaseObject(string guid);

	//�������е����
	void ForEachPlayer(std::function<void(PolicedContext*)> func);

	//ȡ�����
	PolicedContext* FindPlayer(const string& guid);
	//��������Ժ󴥷�
	void OnAfterPlayerDataUpdate(core_obj::SyncEventRecorder *,int,UpdateMask&,UpdateMask&);
public:
	PolicedContext *m_null_player;
private:
	void Send(uint32_t connid,ByteArray&);
};

#endif
