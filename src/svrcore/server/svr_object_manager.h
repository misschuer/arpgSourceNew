#ifndef _SVR_OBJECT_MANAGER_H_
#define _SVR_OBJECT_MANAGER_H_

#include <core_obj/GuidObjectTable.h>
#include <core_obj/GuidObject.h>
#include <core_obj/RemoteOperatorAdapter.h>
#include <core_obj/ByteArrayCompress.h>
#include <object/BinLogObject.h>
#include <shared/lua_helper.h>

using core_obj::GuidObjectTable;
using core_obj::RemoteOperatorAdapter;
using core_obj::ByteArray;
using core_obj::GuidObject;
using core_obj::ByteArrayCompress;
using core_obj::AsyncByteArrayCompress;
using core_obj::CompressCallback;

class SvrCoreAppImpl;
struct TimerHolder;

#define GLOBAL_VALUE_OWNER_STRING "global_value"
#define FACTION_BINLOG_OWNER_STRING "faction"
#define FACTION_DATA_OWNER_STRING	"faction_data"
#define WORLD_BINLOG_OWNER_STRING "world"
#define GROUP_BINLOG_OWNER_STRING "group"

//ĳ����������������
class OwnerDataSet
{
public:
public:
	OwnerDataSet(const string &owner)
		:m_owner_guid(owner)
	{
		
	}
	~OwnerDataSet(){}
public:
	const string &GetGuid() const
	{
		return m_owner_guid;
	}
	set<string> &GetAllData()
	{
		return m_all_data;
	}
private:
	//������guid
	string m_owner_guid;
	//���ж���
	set<string> m_all_data;
};

namespace objects{
	static int luaGet(lua_State *L);
	static int luaForeach(lua_State *L);
	static int luaNewAndCallPut(lua_State *L);	
	static int luaCallRemoveObject(lua_State *L);
	static int luaCallAddWatch(lua_State *L);
	static int luaCallDelWatch(lua_State *L);
}


//���ݹ���������
class SvrObjectManager : public GuidObjectTable, public RemoteOperatorAdapter
{
public:
	friend int objects::luaGet(lua_State *L);
	friend int objects::luaForeach(lua_State *L);
	friend int objects::luaNewAndCallPut(lua_State *L);	
	friend int objects::luaCallRemoveObject(lua_State *L);
	friend int objects::luaCallAddWatch(lua_State *L);
	friend int objects::luaCallDelWatch(lua_State *tolua_S);

	SvrObjectManager(SvrCoreAppImpl *app);
	virtual ~SvrObjectManager();
private:
	static SvrObjectManager *self;

	SvrCoreAppImpl *m_app;
private:
	virtual void Send(uint32_t connid,ByteArray&) = 0;

	bool AddToOwnerMap(const string &owner, GuidObject *obj);		//���һ��owner-guid
	//����һ���µ����ݼ�
	inline OwnerDataSet *NewOwnerDataSet(const string &guid);
	
public:
	virtual void Update();
	virtual void AttachObject(GuidObject* obj);
	virtual void AfterAttachObject(GuidObject *obj);
	virtual void ReleaseObject(string guid);
	//���󹤳�
	virtual GuidObject *ObjectFactor(const string &guid) = 0;
	//������binlog�����Ļص�
	virtual void AfterCreateObjOwner(BinLogObject *binlog);
	//�Ѷ�����뵽���ݼ���
	void InsertObjOwner(const string &guid);
	//�����ݼ���ɾ��ĳ������
	bool DelOwnerMap(const string owner, GuidObject *obj);
	//��ȡĳ���ݼ��������еĶ���
	void GetDataSetAllObject(const string &guid, vector<GuidObject*> &result);
	//���ָ����ҵ��������ݼ�
	OwnerDataSet *FindDataSetByOwnerGuid(const string &owner);
	//����������ʽ��ӡ�����Ķ���
	void PrintObjectByRegex(const string &regex_str, bool print_data);
	//byteArray�ڴ�ػ���
	void ByteArrayPoolClear();

	//�������ж���,keyΪ��ʱ�������� TODO:�ȷ��������okŲ������
	//ί�з��ط�0����ֹѭ��
	void ForeachIndexer(const string& key,std::function<bool(GuidObject*)> f);

	//���ش����Ķ�����ӵ�Զ�̣��ᴥ��Attach��AfterAttach�¼�
	void CallPutObjects(const string& tag,vector<GuidObject *> &objs);

public:
	bool Compress(ByteArray& bytes){return m_compress_tool.Compress(bytes);}
	bool UnCompress(ByteArray& bytes,ByteArray& out_bytes){return m_compress_tool.UnCompress(bytes,out_bytes);};
protected:
	//��binlog��owner guidΪkey��������ص���������
	std::map<string, OwnerDataSet*> m_all_obj_owner_idx;
	AsyncByteArrayCompress m_compress_tool;
};

#endif
