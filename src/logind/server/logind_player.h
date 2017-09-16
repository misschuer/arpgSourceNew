#ifndef _CENT_PLAYER_H_
#define _CENT_PLAYER_H_

#include "logind_app.h"
#include <object/std.h>
#include <object/PlayerBase.h>
#include <object/SharedDef.h>
#include <object/QuestDef.h>

class LogindContext;
class MobileContext;

#define INIT_MOVE_SPEED 135 //135�����ƶ�һ��

//��¼����Ҷ���
class logind_player:public PlayerBase
{
	friend class LogindContext;
public:
	
	//����һ���¶���	
	//static logind_player *CreateChar(const string &guidlow, const std::string& name,uint8 faction,uint8 gender,uint8 head_id,uint8 hair_id,uint8 race);
	logind_player();
	virtual ~logind_player();	

	LogindContext *GetSession(){return m_session;}
	MobileContext *GetMobileSession(){return m_mobile_session;}
	void SetSession(LogindContext *context){m_session = context;}	
	void SetMobileSession(MobileContext *context){m_mobile_session = context;}	

	void SendPacket(packet& pkt);
public:
	void InitNewPlayer(const std::string& name,uint8 faction,uint8 gender,uint8 head_id,uint8 hair_id,uint8 race,bool is_FCM = false);								//��ʼ�������
	bool InitDatabase();								//��ʼ�������ݿ�load��������
public:
	//////////////////////////////////////////////////////
	//������s
	void CalculFCMLogoutTime();//���㴦��������ۼ�����ʱ��
	void SetZiBao(){m_zibao = true;}	
	time_t GetAutoSaveTime(){return m_auto_save_time;}
	void SetAutoSavetime(time_t t){m_auto_save_time = t;}
protected:	
	LogindContext *m_session;					//ҳ�λỰ
	MobileContext *m_mobile_session;			//���λỰ
private:
	bool m_zibao;					//�Ƿ�@�Ա���
	time_t m_auto_save_time;		//�Զ�����ʱ���
};

#endif

