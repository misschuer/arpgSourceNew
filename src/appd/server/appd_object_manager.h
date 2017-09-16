#ifndef _APPD_OBJECT_MANAGER_H_
#define _APPD_OBJECT_MANAGER_H_

#include "appd_app.h"
#include <server/svr_object_manager.h>
#include <core_obj/GuidObjectTable.h>
#include <core_obj/GuidObject.h>
#include <core_obj/RemoteOperatorAdapter.h>
#include <core_obj/ByteArrayCompress.h>

using core_obj::GuidObjectTable;
using core_obj::RemoteOperatorAdapter;
using core_obj::ByteArray;
using core_obj::GuidObject;
using core_obj::ByteArrayCompress;

class AppdContext;
class Item;

class AppdObjectManager : public SvrObjectManager
{
public:
	AppdObjectManager(SvrCoreAppImpl *app);
	virtual ~AppdObjectManager();

	//���󹤳�
	GuidObject *ObjectFactor(const string &guid);

	//ʵ��GuidObjectTable�Ĵ��������ٷ��������ݶ����ǰ׺����ѡ����Ӧ�Ķ���
	GuidObject* CreateObject(string guid);
	void AfterAttachObject(GuidObject *obj);
	void ReleaseObject(string guid);

	//��¡һ��binlog
	BinLogObject *Clone(BinLogObject *obj);

	//�������е����
	void ForEachPlayer(std::function<void(AppdContext*)> func);
	//ȡ�����
	AppdContext* FindPlayer(const string& guid);


	void OnAfterUpdateTop(core_obj::SyncEventRecorder *data,int flags,UpdateMask& mask,UpdateMask& str_mask);

private:
	void Send(uint32_t connid,ByteArray&);
};

#endif
