#ifndef _ROBOTD_CONNECTION_H_
#define _ROBOTD_CONNECTION_H_

#include "robotd_app.h"

class RobotdGameConnection;
class RobotdContext;

#define PACKET_HEAD_FIRST_PART_SIZE sizeof(uint16_t)

#define parser_head_len(data)\
	*((uint16_t*)data)

#define to_uint8_t(content)\
	*((uint8_t*)content)

#define parser_websocket_packet_len_flag(data)\
	to_uint8_t(data + 1) & 0x7F

#define parser_websocket_packet_opcode(data)\
	to_uint8_t(data) & 0xF

#define parser_websocket_mask(data)\
	to_uint8_t(data + 1) >> 7

#define parser_websocket_byte(data, offset)\
	to_uint8_t(data + offset)

#define parser_websocket_mask_info_by_offset(data, mask_offset, mask_array_offset)\
	parser_websocket_byte(data, mask_offset + mask_array_offset)

//�����˵�¼״̬
enum RobotLoginState
{
	ROBOT_LOGIN_STATE_NONE,						//��״̬
	ROBOT_LOGIN_STATE_CONN_SERVER_COUNTDOWN,	//���ӷ���������ʱ��
	ROBOT_LOGIN_STATE_CONN_SERVER_FAIL,			//���ӷ���������
	ROBOT_LOGIN_STATE_CONN_SERVER_OK,			//���ӷ������ɹ�
	ROBOT_LOGIN_STATE_SHAKING_HAND,				//������
	ROBOT_LOGIN_STATE_SHAKE_HAND_END,			//���ֽ���
	ROBOT_LOGIN_STATE_GETSESSION,				//����Get Session
	ROBOT_LOGIN_STATE_NOT_CHARS,				//Get Session�ѷ��أ���ǰδ����ɫ
	ROBOT_LOGIN_STATE_CREATE_CHARS,				//������ɫ��
	ROBOT_LOGIN_STATE_ERR_NAME,					//������ɫ�����쳣
	ROBOT_LOGIN_STATE_HAS_CHARS,				//Get Session ���� ������ɫ �ѷ��أ���ǰ���н�ɫ
	ROBOT_LOGIN_STATE_LOGIN,					//��ɫ��¼��
	ROBOT_LOGIN_STATE_LOGIN_DATA_HAS,			//���յ��������
	ROBOT_LOGIN_STATE_LOGIN_UNIT_HAS,			//���յ���������
	ROBOT_LOGIN_STATE_LOGIN_SUCCEED,			//��¼���
	ROBOT_LOGIN_STATE_FORCED_INTO,				//ǿ����������
	ROBOT_LOGIN_STATE_WAIT_CLOSE,				//�ر���
	ROBOT_LOGIN_STATE_FAILURE,					//��¼ʧ�ܴ���̫�࣬���ٵ�¼
	ROBOT_LOGIN_STATE_GAIMIN,					//������
	MAX_ROBOT_LOGIN_STATE
};


class RobotdConnection : public core_socket::TcpConnection
{
public:
	RobotdConnection(RobotdGameConnection *owner):m_owner(owner),m_open(false),isShakeHand(true)
	{
		ASSERT(m_owner);
	}

	virtual ~RobotdConnection(){}
public:
	uint32 GetFD(){return fd_;}
	RobotdGameConnection *GetOwner(){return m_owner;}
	void UnsetOwner(){m_owner = nullptr;}
	void SetOpen(bool b){m_open = b;}
	bool IsOpen()const{return m_open;}
	
	void SendFirstPacket(const char* str, int length){
		send_buf_.write(str, length);
	} 

	virtual void SendPacket(PacketType& pkt);

	//��������,�ж��Ƿ��ѳ�Ϊһ��������������Ѿ���ɣ�
	//��ô���ð��������������ݷ���ֵ�޸����ӵĵ�ǰ���ݰ�
	//���ػ�ʣ�¶��ٵ��ֽ���δ��
	virtual int ComplatePacket(uint8_t *buf,int len);
	
	virtual void ReadPacket();

	// ������Ϣͷ�ĳ���
	int get_real_head_len(PacketType *cur_pkt_);

	//�����Ϣ�ĳ���
	int get_packet_payload(PacketType *cur_pkt_);

protected:
	virtual void OnClose();

public :
	bool isShakeHand;
protected:
	RobotdGameConnection *m_owner;
	bool m_open;
};

class RobotdGameConnection
{
	struct OpcodeHandler
	{
		char 	const* name;
		void 	(RobotdContext::*handler)(uint16,PacketType&);
		OpcodeHandler():name(0),handler(0)
		{};		
	};
public:
	static void SendFirstShakeProtocol(RobotdConnection *conn_);
	RobotdGameConnection(RobotdContext *context, const string &conn_host, int conn_port)
		:m_context(context), conn_(nullptr), m_conn_host(conn_host), m_conn_port(conn_port)
		,m_login_state(ROBOT_LOGIN_STATE_NONE), m_close_count(0), closed(false)
	{
		OpcodeHandlerInitor();

		m_timer_wait_unit.SetInterval(2000);
		m_timer_login.SetInterval(30000);
		m_timer_getSession.SetInterval(30000);
		m_timer_has_player_data.SetInterval(30000);
		m_timer_forced_info.SetInterval(2000);
		m_timer_clear_close_count.SetInterval(1000);
		m_timer_GaiMing.SetInterval(3000);
	}

	~RobotdGameConnection()
	{
		//Close();
	}
public:
	const string &GetConnHost(){return m_conn_host;}
	uint32 GetConnPort(){return m_conn_port;}
	int GetFD()
	{
		if(conn_)
			return conn_->GetFD();
		return 0;
	}
	uint16 GetLoginState(){return m_login_state;}
	void SetLoginState(uint16 val);

	bool ConnToNetgd();

	void Close();
	virtual void OnClose();
	virtual bool LoginUpdate(uint32 diff);
	void OnConnToWar();
	void OnFreeWar();
protected:
	virtual void OpcodeHandlerInitor();
	virtual void CreateConn();
private:
	uint32 m_close_count;					//����Ͽ����Ӵ���
	bool closed;
protected:
	RobotdContext *m_context;
	//����·�ɱ�
	OpcodeHandler opcode_handler_[NUM_MSG_TYPES + 1];

	IntervalTimer m_timer_login;			//��¼��ʱ��
	IntervalTimer m_timer_getSession;		//getsession��ʱ��
	IntervalTimer m_timer_has_player_data;	//ȡ������ݶ�ʱ��
	IntervalTimer m_timer_forced_info;		//���˶�ʱ��
	IntervalTimer m_timer_wait_unit;		//����ȴ���ʱ��
	IntervalTimer m_timer_clear_close_count;//�������Ͽ�������ʱ��
	IntervalTimer m_timer_GaiMing;			//������ʱ��
	//���Ӻ͵�¼���
	string m_conn_host;				//��Ϸ������ip
	int m_conn_port;				//��Ϸ�������˿�
public:
	RobotdConnection *conn_;

	

	RobotLoginState m_login_state;			//��¼״̬
};

class RobotdWarConnection : public RobotdGameConnection
{
public:
	RobotdWarConnection(RobotdContext *context, const string &conn_host, int conn_port, const string &session_str)
		:RobotdGameConnection(context, conn_host, conn_port), m_session_str(session_str)
	{

	}
public:
	void OnClose();
	bool LoginUpdate(uint32 diff);
protected:
	void OpcodeHandlerInitor();
	void CreateConn();
public:
	string m_session_str;			//�������ʱָ����get session��
};

#endif
