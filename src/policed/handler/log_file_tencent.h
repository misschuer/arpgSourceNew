#ifndef _LOG_FILE_TENCENT_
#define _LOG_FILE_TENCENT_

#include <comm/common_stl.h>
#include "log_file_stream.h"

#define RETRY_MAX_COUNT 10

class LogFileTencent
{
	typedef struct log_packet_t
	{
		packet *pkt;		//��־��
		uint32 retry_count;	//���Դ���
	}log_packet;
	typedef map<uint32, LogFileStream*> FildMap;
public:
	LogFileTencent();
	~LogFileTencent();
public:
	void Update(uint32 diff);
	void WriteLog(packet *pkt, account_info *a_info = NULL, PolicedContext *player = NULL);
	void PostTXJinFen(string ext_url,string data);//ͨ���ⲿ�������ӿ�post��������
	void PostTXJinFen(string ext_url,string account,string user_guid,string pf,double modifyfee = 0,uint32 onlinetime = 0);//ͨ���ⲿ�������ӿ�post��������

private:
	void WriteBaseLog(uint32 type, LogFileStream& file, time_t sec, time_t usec, account_info *a_info, PolicedContext *player);
	void ResetMap(struct tm *local);
	void ReWriteLog(TimerHolder& th);
private:
	FildMap m_file_map;						//������־�ļ�

	char m_time[50];						//���������΢������
	uint32 m_today;							//���յ�����
	uint32 m_host;							//���յ�Сʱ
	
private:
	typedef void (LogFileTencent::*handle)(uint32 log_type, packet*, LogFileStream*, time_t, time_t, account_info*, PolicedContext*);
	handle m_tx_handle_map[MAX_LOG_FILE_TENCENT_TYPE];
	string GetLastString(string name,const char &spit);

private:
	void HandlerInit();
	void Handle_Write_Tencent_User(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Tencent_Player(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Tencent_Recharge(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Tencent_UpgradeLog(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Tencent_Newtask(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Tencent_Login(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Tencent_Offline(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Tencent_Online(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Tencent_MoneyLog(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
};

#endif
