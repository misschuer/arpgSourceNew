#ifndef _HTTP_HANLDER_H
#define _HTTP_HANLDER_H

namespace http{
namespace client{class client;}
namespace server{class server; struct reply; struct request;}
}

class HttpHandler
{
public:
	typedef http::server::request Request;
	typedef  http::server::reply Reply;
	typedef void (HttpHandler::*Handler)(const Request& req, Reply& rep);

	HttpHandler();
	~HttpHandler();

	void Init();

	//���ͱ��ؼ���web�ӿڸ�Զ�̷�����
	void RegisterWeb(bool force = false);
	void AddHandler(string uri, Handler handler);
	string MakeResponse(int ret, string msg);

	void Update();
private:
	http::server::server *m_server;
	http::client::client *m_client;

	//ע��״̬, 0:��ʼ�� 1:׼��ע�� 2:ע��ɹ� -1:����Ҫע��
	int m_reg_state;
};


#endif
