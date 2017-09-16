#ifndef _COMMON_CONTEXT_H_
#define _COMMON_CONTEXT_H_

#include <comm/common_stl.h>
#include <net/netstd.h>
#include <protocol/external.h>
#include <server/svr_context_manager.h>

class logind_player;
namespace core_obj{ class GuidObject; }
using core_obj::GuidObject;

//ҳ�����λỰ�ĳ�����
class CommonContext : public SvrContext
{
public:
	CommonContext(uint32 fd,ContextManager *mgr,int type = 0/*CONTEXT_TYPE_YEYOU*/);
	virtual ~CommonContext();

public:
	static CommonContext* FindContext(uint32 fd);
	uint8 GetContextType(){return m_context_type;}
	virtual void OnClosed() = 0;										//�Ự�ر�
	virtual void CollapseReset(logind_player *player) = 0;				//��¼�������Ժ����³�ʼ��
	virtual void Call_Create_Connection() = 0;							//֪ͨ��������������
	
	bool Get_Server_List(string login_server);							//��֤��¼�������Ƿ���ȷ
	bool IsKuafuPlayer()
	{
		//�Ƿ������
		if (!m_backsvrname.empty())
			return true;
		else
			return false;
	}

	const string &GetFromServerName()const {return m_from_server_name;}
	bool SetPlayer(logind_player *player);
	logind_player *GetPlayer(){return m_player;}
	const string &GetGuid()const{return m_lguid;}
	const string &GetAccount()const{return m_account;}
	//��ʼ�������Ϣ
	virtual void PlayerLoadData();
	void PutData();
	virtual void LoginOK() = 0;
private:
	uint8 m_context_type;			//�Ự����
protected:
	vector<GuidObject*> m_temp_vec;	//��¼�����е���ʱ����
	logind_player *m_player;		//��������Ҷ���
	string m_account;				//�˺�
	string m_from_server_name;		//���Է�����
	string m_backsvrname;			//Ҫ���ص���Ϸ��server_name	
	string m_kuafu_svrname;			//�����ս����server_name	
	uint32 m_kuafu_reserve2;		//������������������÷���������������
public:
	uint32 m_warid;					//����id
	uint8 m_kuafutype;				//�������
	string m_remote_ip;
	uint16 m_remote_port;	
	uint32 m_number;				//�����ұ��
	uint32 m_kuafu_reserve;			//������������������÷���������������
	string m_kuafu_reserve_str;		//����ַ���Ԥ��
};

#endif // !_COMMON_CONTEXT_H_


