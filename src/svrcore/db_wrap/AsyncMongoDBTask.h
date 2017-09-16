
#ifndef _ASYNC_MONGODB_TASK_H_
#define _ASYNC_MONGODB_TASK_H_

#include "worker_pool.h"
#include "db_wrap/mongo_wrap_def.h"
#include "db_wrap/mongo_wrap.h"

//////////////////////////////////////////////////////////////////////////
//�첽��������
struct AsyncMongoDBTask
{
	typedef std::function<void(AsyncMongoDBTask*)> CB;
	typedef std::map<string,string> Map;
	typedef std::vector<Map> Results;

	AsyncMongoDBTask(string& s,const Map& w,Map& v,int type):ns_(s),where(w),value(v),operType(type),result_(MONGO_RES_NULL)
	{
	}
	AsyncMongoDBTask(string& s,Map& v, int type):ns_(s),value(v),operType(type)
	{
	}
	AsyncMongoDBTask():operType(0)
	{
	}

	string ns_;
	Map where;
	Map value;
	Results results;
	int operType;					//for Mongo_Operator_TYPE
	Mongo_Result result_;			//�������
	CB callback_;

	int limit_;						//�����query��Ч,���ؼ�¼��
	string order_field_;			//�����ֶ�
	int sort_;						//bySort 1�����򣬣�1�ǽ���
};

enum Mongo_Operator_TYPE
{
	UPDATE = 1,			//���²���
	INSERT,			//�������
	LOAD,			//��ѯ������¼
	QUERY,			//��ѯ������¼,�Ͼ�������һЩ��ѯ������������������
	UPSERT,			//���»��߲���
};

class AsyncMongoDB 
{
public:
	AsyncMongoDB(MongoWrap *db);
	virtual ~AsyncMongoDB();
	bool Start();

	void AsyncUpdate(string ns,const MongoWrap::Map& where,MongoWrap::Map& values);
	void AsyncInsert(string ns,MongoWrap::Map& values);
	void AsyncUpsert(string ns,const MongoWrap::Map& where,MongoWrap::Map& values);
	AsyncMongoDBTask *AsyncQuery(string ns,const MongoWrap::Map& wheres,AsyncMongoDBTask::CB cb,string orderKey, int32_t bySort,int32_t limitReslut);
	void AsyncLoad(string ns,const MongoWrap::Map& wheres,AsyncMongoDBTask::CB cb);
	void Update();

protected:
	void Excute(AsyncMongoDBTask *task);
	void PushResult(AsyncMongoDBTask *task);

private:
	//MongoWrap *mongodb_;
	WorkerPool<AsyncMongoDBTask> *workers_;	
	MongoWrap* db_;

	std::mutex mutex_;
	std::vector<AsyncMongoDBTask*> results_;	
};


#endif
