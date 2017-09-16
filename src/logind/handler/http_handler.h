#ifndef _HTTP_HANLDER_H
#define _HTTP_HANLDER_H

#include "logind_app.h"

namespace http{
namespace client{class client;}
namespace server{ class server; struct reply; struct request;}
}

class HttpHandler
{
public:
	typedef http::server::request Request;
	typedef  http::server::reply Reply;
	typedef map<string, string> ServerNameHostPortMap;
	typedef void (HttpHandler::*Handler)(const Request& req, Reply& rep);

	HttpHandler();
	~HttpHandler();

	void Init();

	//���ͱ��ؼ���web�ӿڸ�Զ�̷�����
	void RegisterWeb(bool force = false);
	void ReloadWeb();						//����Ҫ��web�����·��������ĵ�����
	void AddHandler(string uri, Handler handler);
	string MakeResponse(int ret, string msg);

	void Update();

	//G2G �������ݵ�����
	bool PostMergeData(const string &guid, const string &to_server_name);
	//G2G ���ͺϷ���ɵ�����
	bool PostMergeOK(const string &to_server_name);

	//G2W ��Զ��Webȡ��������Ϣ
	string GetWebConfig(const string& key,const string& defaultValue = "");

	void Handle_Query_Char_Info(const Request& req, Reply& rep);		//��ѯ��ҽ�ɫ��Ϣ
	void Handle_Merge_Postdata(const Request& req, Reply& rep);			//�Ϸ������������
	void Handle_Merge_Ok(const Request& req, Reply& rep);				//�Ϸ����
	void Handle_SetGmlevel(const Request& req, Reply& rep);				//����gm�ȼ�
	void Handle_Kicking(const Request& req, Reply& rep);				//����
	void Handle_Gag(const Request& req, Reply& rep);					//���ԡ����
	void Handle_QQ_Config(const Request& req, Reply& rep);				//����gmQQ����
	void Handle_Lock_Account(const Request& req, Reply& rep);			//���

public:
	void GetHostPortByServerName(const string& server_name, string& host, string& port);		//��÷�������ip/port
	void RegBattleSvrConn();																	//��webע��ս������״̬
protected:
	void LoadPlayer(const string &player_guid, std::function<void(bool,const string &,vector<GuidObject*>&)> fun);
	string GetLogindPostUrl(const string &server_name);
private:
	http::server::server *m_server;
	http::client::client *m_client;

	//ע��״̬, 0:��ʼ�� 1:׼��ע�� 2:ע��ɹ� -1:����Ҫע��
	int m_reg_state;
	//��load����
	int m_reload_count;
	ServerNameHostPortMap m_serverHostportInfo;	//��������ip/port����
};


#endif
