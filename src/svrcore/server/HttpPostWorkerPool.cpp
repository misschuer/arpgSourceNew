#include "HttpPostWorkerPool.h"
#include <net/http.h>

//////////////////////////////////////////////////////////////////////////
AsyncPostQuest::AsyncPostQuest(const char* url,const char* data):url_(0), data_(0), response_(0),result_(0),index_(0)
{
	url_ = (char *)malloc(strlen(url)+1);
	data_ = (char *)malloc(strlen(data)+1);
	strcpy(url_,url);
	strcpy(data_,data);
}

AsyncPostQuest::~AsyncPostQuest	()
{
	if(url_) free(url_);
	if(data_) free(data_);
	if(response_) free(response_);
}

//////////////////////////////////////////////////////////////////////////
//for HttpPostWorkerPool
HttpPostWorkerPool::HttpPostWorkerPool():callback_index_(0),run_callback_index_(0)
{
}

HttpPostWorkerPool::~HttpPostWorkerPool()
{
	for (auto it = callbacks_.begin();it!=callbacks_.end();++it)
	{
		auto *ptr = it->second;
		delete ptr;
	}
	callbacks_.clear();
}

void HttpPostWorkerPool::start(int worker_num)
{
	Start([this](AsyncPostQuest *quest){
		char *response = NULL;
		quest->result_ = http_post(quest->url_, quest->data_, &quest->response_);
		//������������񷵻ص�׼���ص����б�
		std::unique_lock<std::mutex > lck(mutex_callbacks_);
		callbacks_[quest->index_] = quest;
	},worker_num);
}

void HttpPostWorkerPool::asyn_post(const char *url,const char *data,bool isok)
{
	auto *quest = new AsyncPostQuest(url,data);	
	quest->index_ = ++callback_index_;			//�ص����

	if(isok){
		//������������񷵻ص�׼���ص����б�
		std::unique_lock<std::mutex > lck(mutex_callbacks_);
		callbacks_[quest->index_] = quest;
	}else
		Push(quest);
}

void HttpPostWorkerPool::do_callback(std::function<void(AsyncPostQuest&)> cb)
{
	//��ص���������
	std::unique_lock<std::mutex > lck(mutex_callbacks_);

	auto it = callbacks_.find(run_callback_index_+1);
	while(it != callbacks_.end())
	{
		auto quest = it->second;	
		if(cb)
			cb(*quest);
		//��ִ�еĻص���ſ�����
		run_callback_index_ ++;
		//��������ɾ�� 
		callbacks_.erase(it);
		//�ͷ��ڴ�
		delete quest;

		//�����һ�λص��Ѿ�׼�����ˣ����Լ���
		it = callbacks_.find(run_callback_index_+1);
	}
}
