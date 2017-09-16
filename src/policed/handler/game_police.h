#ifndef _GAME_PATROL_
#define _GAME_PATROL_

#define SMS_KEY "@xTr66s^0n:l>U=Uod*g"
#define SMS_PID "3"

enum GAME_POLIC_ALARM_TYPE
{
	GAME_POLIC_ALARM_CHAT					= 1,		//���쾯��
	GAME_POLIC_ALARM_CHECK_GOLD				= 2,		//У��Ԫ�������ֵ�ĳ�ͻ
	GAME_POLIC_ALARM_DEAL_GOLD_5000			= 3,		//�ȼ���50������ֵΪ0�����׻��Ԫ������5ǧ
	GAME_POLIC_ALARM_DEAL_SILVER_1000		= 4,		//�ȼ���50������ֵΪ0�����׻����������1000��
	GAME_POLIC_ALARM_DEAL_SILVER_10000		= 5,		//���׻����������1��
	GAME_POLIC_ALARM_STALL_GOLD_5000		= 6,		//�ȼ���50������ֵΪ0��̯�ӻ��Ԫ������5ǧ
	GAME_POLIC_ALARM_STALL_SILVER_1000		= 7,		//�ȼ���50������ֵΪ0��̯�ӻ����������1000��
	GAME_POLIC_ALARM_STALL_SILVER_10000		= 8,		//̯�ӻ����������1��
};

enum GAME_POLIC_ALARM_CHAT_TYPE
{
	GAME_POLIC_ALARM_CHAT_15				= 1,		//�ȼ�С�ڵ���15������3�����˽��
};

////���˵���������
//static const string kicking_type_content[] = {
//	"�Բ����������ķǷ������ѱ����IP���������ʿ���ѯ���߿ͷ���",
//	"�Բ����������ķǷ������ѱ���ţ��������ʿ���ѯ���߿ͷ���",
//	"�Բ����������ķǷ������ѱ����ߣ��������ʿ���ѯ���߿ͷ���",
//	"�Բ�������ʹ�÷�������ʽ�ڿ󳡸��",
//	"�Բ�������ɢ��������ϢӰ������������Ϸ��",
//	"�Բ�������ʹ�÷������ֶν�����Ϸ��",
//	"�Բ���ϵͳ��⵽����ǰ�˺��쳣����ˢ�º����½�����Ϸ���ɻָ�������"
//};

//У�������Ϊ
//�������ʲ���ʵ�ʳ�ֵ�Ĳ���
class GamePolice
{
public:
	GamePolice();
	~GamePolice(){};
private:
	char m_field_data[10000];
	set<string> m_exclude_account;
	bool m_send_msg;
	vector<string> m_phone_no;
	char m_post_data[1000];
	char m_sms_key_no[1000];
	
	uint32 m_lock_db_update_tm;
public:
	void SaveHTInfo(TimerHolder& th);		//�����̨��Ϣ
	void SaveTopInfo(TimerHolder& th);		//�������а���Ϣ
	
};

#endif
