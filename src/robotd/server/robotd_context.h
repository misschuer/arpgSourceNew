#ifndef _ROBOTD_CONTEXT_H_
#define _ROBOTD_CONTEXT_H_

#include "robotd_app.h"
#include "robotd_conn.h"
#include "ProtocolUtil.h"
#include <stack>
#include <object/SharedDef.h>
#include <object/PlayerBase.h>


class BinLogObject;
class RobotdObjectManager;
class RobotdGameConnection;
class RobotdUnit;

//Ӧ�÷��Ự ��������Ϣ
class RobotdContext : public PlayerBase, public ProtocolUtil
{
public:
	RobotdContext(const string &pid, const string &sid, const string &uid, const string &remote_ip, const string &login_key, const string &conn_host, uint32 conn_port, const string &params);
	virtual ~RobotdContext();

	RobotdGameConnection *GetConn();
	
	void Close()
	{
		if(conn_)
			conn_->Close();
	}
	uint32 GetFD()
	{
		if(!conn_)
			return 0;
		return conn_->GetFD();
	}
public:
	void OnGameServerLogin(const string& login_host, uint32 login_port);
	void Update(uint32 diff);
	void Reset();
	void OnClose();
	void OnWarClose();
public:
	RobotdUnit *GetMyUnit(){return unit_;}
	void SetMyUnit(RobotdUnit *u);
	void OnAfterUpdate(SyncEventRecorder *data,int flags,UpdateMask& mask,UpdateMask& str_mask);	
	string MakeSessionKey(bool indulge, bool mobile = false);
public:
	void Handle_Lua(uint16 optcode, PacketType &pkt);
	void Handle_Ud_Object(uint16 optcode, PacketType &pkt);
	void Handle_Chars_List(uint16 optcode, PacketType &pkt);
	void Handle_Grid_Unit_Move(uint16 optcode, PacketType &pkt);						//Unit�ƶ�
	void Handle_Unit_Move_Stop(uint16 optcode, PacketType &pkt);						//Unit move stop
	void Handle_Operation_failed(uint16 optcode, PacketType &pkt);
	void Handle_Grid_Ud_Object(uint16 optcode, PacketType &pkt);						//grid���¾���
	void Handle_Sync_Mstime(uint16 optcode, PacketType &pkt);							//��������ͬ��������ʱ��
	void Handle_Merge_Server_Msg(uint16 optcode, PacketType &pkt);						//�Ϸ�֪ͨ
	void Handle_Map_Info_Update(uint16 optcode, PacketType &pkt);						//��ͼ�������
	void Handle_join_or_leave_server(uint16 optcode, PacketType &bytes);				//�����ȡ�뿪���߼�������
	void Handle_Fighting_Info_Update_Object(uint16 optcode, PacketType &bytes);			//ս�����ܰ�
	void Handle_Fighting_Info_Update_Object_2(uint16 optcode, PacketType &bytes);		//ս�����ܰ�
	void Handle_World_War_SC_Player_info(uint16 optcode, PacketType &bytes);			//����������
	void Handle_Strength_Success(uint16 optcode, PacketType &bytes);
	void Handle_World3v3_WaitInfo(uint16 optcode, PacketType &bytes);					//3v3׼���б�

public:
	void OnRobotRespawn();

public:
	const string &GetPlatformId() const {return m_pid;}
	const string &GetServerId() const {return m_sid;}
	const string &GetUserId() const {return m_uid;}
	const string &GetRemoteIP() const {return m_remote_ip;}
	string GetAccount(){return m_pid + '_' + m_sid + '_' + m_uid;}
	bool IsLoginOk();
	const string &GetConnHost(){return conn_->GetConnHost();}
	uint32 GetConnPort(){return conn_->GetConnPort();}
	bool GetSwitch(uint8 type)
	{
		ASSERT(type < 32);
		return GET_BIT(m_action_switch, type);
	}
	int send_world_war_SC_player_info___ ();
public:
	RobotdObjectManager	*m_obj_mgr;		//���������
/*
	uint32 m_updatemask_time[65535];
	uint32 m_updatemask_time_str[65535];*/

private:
	//��Ϸ��tcp����
	RobotdGameConnection *conn_;

	//ս����tcp����
	RobotdWarConnection *war_conn_;
	//�����¼�������Ϣ
	ByteArray m_war_bytes;

	RobotdUnit *unit_;

	const string m_pid;								//ƽ̨id
	const string m_sid;								//������id
	const string m_uid;								//�����˵�¼�ʺ�id
	const string m_remote_ip;						//session key�д���remote_ip��Ϣ
	const string m_login_key;						//��Ϸ��¼ʱ��ʹ�õ���Կ

	string m_params;								//�����˲���
	uint32 m_action_switch;							//�����˹��ܿ���

public:
	static int LuaClose(lua_State *scriptL);
	static int LuaIsLoginOk(lua_State *scriptL);
};

#endif
