#ifndef _HTTP_POST_WORKDER_POOL_H_
#define _HTTP_POST_WORKDER_POOL_H_

#include <worker_pool.h>
#include <map>
#include <functional>

//�첽����post
struct AsyncPostQuest
{
	AsyncPostQuest():url_(0), data_(0), response_(0),result_(0),index_(0)
	{
	}
	AsyncPostQuest(const char* url,const char* data);
	~AsyncPostQuest();
	char *url_;
	char *data_;
	char *response_;
	int result_;
	uint64_t index_;
};

class HttpPostWorkerPool:public WorkerPool<AsyncPostQuest>
{
public:
	HttpPostWorkerPool();
	virtual ~HttpPostWorkerPool();

	//��ʼ������
	void start(int worker_num);

	//�����첽����,�Ƿ�����ɣ�����Ѿ����ֱ�ӻص�������ѹ��
	void asyn_post(const char *url,const char *data,bool isok = false);	

	//ִ�лص������
	void do_callback(std::function<void(AsyncPostQuest&)> cb);

protected:
	//��ǰ���е����
	uint64_t callback_index(){return callback_index_;}	

	//�Ѿ�ִ�еĻص����
	uint64_t run_callback_index(){return run_callback_index_;}

	//������׼�����ص��������б�
	std::map<uint64_t,AsyncPostQuest*> callbacks_;
	std::mutex mutex_callbacks_;

	//���һ��������еĻص���
	uint64_t callback_index_;
	//����ɵĻص���
	uint64_t run_callback_index_;
};

#endif
