#ifndef _BIN_LOG_OBJECT_H_
#define _BIN_LOG_OBJECT_H_

#include <svrcore-internal.h>
#include <core_obj/GuidObject.h>
#include <core_obj/UpdateMask.h>
#include "SharedDef.h"

#define REGEX_GLOBAL			"^G\\.[[:alpha:]]"
#define REGEX_PLAYER			"^p[[:digit:]]"		//��Ҷ���
#define REGEX_MAPPLAYERINFO		"^u[[:digit:]]"		//��ͼ�������Ϣ
#define REGEX_MAP				"^M[[:digit:]]"		//��ͼbinlog
#define REGEX_LIMIT				"^l[[:digit:]]"		//��ʱ�
#define REGEX_WORLD				"^w"				//�����Binlog
#define REGEX_FACRION			"^L[[:digit:]]"		//���ɶ���
struct lua_State;		//for script

#define GET_BIT(v,i) (((v)>>(i))&0x1)
#define SET_BIT(v,i) ((1<<(i))|v)
#define UNSET_BIT(v,i) (~(1<<(i))&v)

using core_obj::GuidObject;
using core_obj::UpdateMask;

class BinLogObject:public core_obj::GuidObject
{
public:
	BinLogObject(uint32_t _m = core_obj::SYNC_SLAVE):core_obj::GuidObject(_m),m_db_hashcode(0),m_debug_deleted(0)
	{
		//SetBinlogMaxSize(MAX_BINLOG_SIZE_UNLIME);
	}

	virtual ~BinLogObject()
	{
		m_debug_deleted=-1;
	}

	//������¼Ϊ��
	bool BinlogEmpty(){return binlogs_.empty();}

	//Ĭ��ʤ������,������guidʱ,��Զλ�ڵ�һ��
	const string &GetGuid() const 
	{
		return guid_;
	}
	
	//
	inline void SetGuid(string s)
	{
		guid(s);
		SetStr(BINLOG_STRING_FIELD_GUID, s);
	}

	//Ĭ��ʤ������,Nameʱ,��Զλ�ڵ�2��
	const string& GetName() const 
	{
		return GetStr(BINLOG_STRING_FIELD_NAME);
	}

	void SetName(const string &name)
	{
		SetStr(BINLOG_STRING_FIELD_NAME,name);
	}

	// �������ID
	const string &GetOwner()const
	{
		return GetStr(BINLOG_STRING_FIELD_OWNER);
	}

	void SetOwner(const string &val) 
	{
		SetStr(BINLOG_STRING_FIELD_OWNER,val);
	}

	const string &GetVersion()const
	{
		return GetStr(BINLOG_STRING_FIELD_VERSION);
	}
	
	//��һ�α��浽���ݿ�ʱ�������룬�����Ƿ���Ҫ����
	size_t m_db_hashcode;
	//û������,���ڵ���,�ڴ�	
	int m_debug_deleted;			
};

//��ByteArrayת�������ݰ�
void WriteTo(core_obj::ByteArray &src,packet& dst);
void ReadFrom(core_obj::ByteArray &dst,packet& src);

#endif
