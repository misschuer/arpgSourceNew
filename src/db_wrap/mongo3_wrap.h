#ifndef _MONGO3_WRAP_H_
#define _MONGO3_WRAP_H_

#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <fstream>
#include <mutex>
#include "db_wrap/mongo_wrap_def.h"

using std::string;

struct MogoWrapLogImpl;
struct MongoDBPtr;

//c++��mmongo�����ӿڰ�װ
//Լ��key: i��ͷΪ���� uΪ�޷������� dΪnumber���� ����Ĭ��ȫ��Ϊ�ַ�������
class MongoWrap3
{
public:
	typedef std::map<string,string> Map;
	typedef std::vector<uint32_t> Values;
	typedef std::vector<string> StrValues;
	typedef std::vector<Map> Results;

	//bson���������֮���ת��	
public:

	MongoWrap3();
	virtual ~MongoWrap3();

	//����������
	bool Open(string host,unsigned short port,string user = "",string pwd = "",string dbname = "admin",int level=_NO_LOG, string logpath="");
//	//�ر�����
//	void Close();

	//�������ݵ�ָ���ļ�¼����
	bool Insert(string ns,Map& values,bool fsync = false);
	bool Upsert(string ns,const Map& where,Map& values);

	//�������ݵ�ָ���ļ�¼����
	bool Update(string ns,int _id,Map& values);
	bool Update(string ns,const Map& where,Map& values, bool upsert = false, bool fsync = false);

	//�����ݿ��ж�ȡ����
	Mongo_Result Load(string ns,const Map& where,Map& result);

	//��ѯ������¼
	Mongo_Result Query(string ns,const Map& where,Results& results);
	Mongo_Result Query(string ns,const Map& where,Results& results,const Map& outfield);
	Mongo_Result Query( string ns,const Map& where,Results& results,string orderKey, int32_t bySort,int32_t limitResult = 0 );

	//���ڻ�ȡ���ڻ���С��ָ��ֵ��bGrate=true,���ڵ��ڣ�bGrate=false��С�ڵ��ڡ�
	Mongo_Result Query(string ns,const Map& where,Results& results,bool bGrate,string compareKey, uint32_t uValue);

	bool Delete(string ns,const Map& where);

	bool CheckNS(const string& ns);

	//Ϊ�˼�������,���첽��ͬ����������,������������
	std::mutex mutex_;
protected:
			
	string host_;
	int port_;
	string dbname_;			//ò��ûɶ��?
	
	MongoDBPtr *mongo_;
	string user_;
	string password_;

	MogoWrapLogImpl *log_;
};

#endif
