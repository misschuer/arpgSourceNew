#ifndef _CENTER_SESSION_H_
#define _CENTER_SESSION_H_

#include <comm/common_stl.h>
#include <net/netstd.h>
#include <protocol/external.h>
#include "logind_player.h"
#include "mobile_context.h"


class LogindMongoDB;

typedef map<string,uint32> SessionMap;
typedef std::deque<uint32> SessionQue;
//////////////////////////////////////////////////////////////////////////
//
class LogindContext : public CommonContext
{
public:
	//����·��,��ʼ��
	void OpcodeHandlerInitor();

	//�˺�-Session�б�
	static SessionMap SessionMaps;
	//�����Ŷӵ�����б�
	static SessionQue SessionQues;

	static inline LogindContext* FindContext(uint32 fd)
	{
		return static_cast<LogindContext*>(LogindApp::g_app->FindContext(fd));
	}

	static inline logind_player* FindPlayer(const string &lguid)
	{
		return dynamic_cast<logind_player*>(ObjMgr.Get(lguid));
	}
	static uint32 FindSessionID(const string &account);	
	static LogindContext* FindContextByGuid(string guid);		//ͨ��guid����ҳ�λỰ
	static uint32 LoginPlayerCount();
public:
	LogindContext(int fd,ContextManager *mgr);
	virtual ~LogindContext();
	//�����¿����Ϣ
	void ResetKuafuInfo();
	void Update(uint32 diff);
	//���ԹرոûỰ��Ϣ,��Ҫͬ����Ϣ�ȵ�
	void OnClosed();
	//��¼�������Ժ����³�ʼ��
	void CollapseReset(logind_player *player);

	//�첽��ʼ�������Ϣ
	void PlayerAfterLoadData(logind_player *player,vector<GuidObject *>vec,uint32 fd);
	//����ֵ��������RMB�ȼ�
	void SetPayLevel();
	void SetReceiveMatchInfoFlag(bool flag){m_bHasReceiveMatchInfo = flag;}
	bool GetReceiveMatchInfoFlag(){return m_bHasReceiveMatchInfo;}
	//���浽���ݿ�
	void SaveToDB(bool fsync = false);
public:
	void Handle_Foeced_Into(packet& pkt);				//����

	void Handle_Get_Chars_List(packet& pkt);			// ��ȡ��ɫ�б�

	void Handle_Char_Create(packet& pkt);				// ��ɫ����
	void Handle_Char_Update_Info(packet& pkt);			// ��ɫ��Ϣ���
	void Handle_Delete_Char(packet& pkt);				// ��ɫɾ��
	void Handle_Player_Login(packet& pkt);				// ��½
	void Handle_Player_Logout(packet& pkt);				// С��
	void Handle_Change_Line(packet& pkt);				// ����
	void Handle_Show_Line(packet& pkt);					// ��ѯ������Ϣ
	void Handle_Regularise_Account(packet& pkt);		//����ʽ�û�ת����ʽ�û�

	void Handle_Player_Kicking(packet& pkt);			//����

	void Handle_GoBackTo_GameServer(packet& pkt);		//�ͻ�������ش�����Ϸ��
	void Hanlde_pk_login(packet &pkt);					//ս������¼
	void Handle_World_War_CS_Player_Info(packet& pkt);	//��������������
	void Call_World_War_CS_Player_Info(const string &server_ip, uint32 port, const string &sessionkey);				//������Ҵ�����ݸ��ͻ���
	void Hanlde_Modify_Watch(packet& pkt);				//�޸ļ���
	void Hanlde_Kuafu_Enter(packet& pkt);				//������Э��
public:
	// ��ȡsessionKey����
	bool Get_Session(std::map<string,string>& querys);
	void LoginOK();					//��¼��ɣ�����������
	void onSetInvitedTeleportInfo(const string& factionId, uint32 mapid, uint32 x, uint32 y, const string& generalId);
	void onRealLoginOk(const string& factionId);	// ��֤�Ƿ������ɺ��ʵ�ʵ�¼
	void Call_Create_Connection();
	bool Check_Name(string& name, string& realName, string& prefix);				// �������
	void Char_Name_Update(string &name);							// ��������
private:
	bool m_is_save_login_log;		//�Ƿ��Ѿ��������¼��¼
	uint32 m_is_canInto;			//�Ƿ���Զ�����
	bool m_is_hosting;				//�Ƿ����йܵ�¼
	bool m_bHasReceiveMatchInfo;	//�Ƿ����յ����ƥ����Ϣ
	bool m_bHasplatdata;			//��¼sessionkey���Ƿ�Я��ƽ̨��Ϣ
	bool m_bHasfcm;					//��¼sessionkey���Ƿ�Я����������Ϣ
	bool m_isFcm;					//������
private:
	string m_watcher_guid;			//�۲���guid
	string m_general_id;			//��ͼʵ����ӦΨһid
	
private:
	void SavePlayerLoginLog();	//������ҵ�¼��¼
	void SavePlayerLogoutLog();	//������ҵǳ���¼
	bool SendToScenedAddMapWatcher();//���ڲ�Э�鵽������,����������·���Ӧ�ĵ�ͼ���ݵ�
public:
	bool GoBackToGameSvr();		//�������pk���ص���Ϸ��
public:
	//���Ͳ���
	uint32  to_mapid,to_instanceid,to_line_no;
	string to_teleport_id;
};

#endif
