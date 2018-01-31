#ifndef _LOG_FILE_OPERATE_
#define _LOG_FILE_OPERATE_

#include <comm/common_stl.h>
#include "log_file_stream.h"

#define RETRY_MAX_COUNT 10

class LogFileOperate
{
	typedef struct log_packet_t
	{
		packet *pkt;		//��־��
		uint32 retry_count;	//���Դ���
	}log_packet;
	typedef map<uint32, LogFileStream*> FildMap;
public:
	LogFileOperate();
	~LogFileOperate();
public:
	void Update(uint32 diff);
	void WriteLog(packet *pkt, account_info *a_info = NULL, PolicedContext *player = NULL);
	void WriteClientLog(packet *pkt);
	void WriteAbnormalPackets(account_info *a_info, PolicedContext *player, uint32 content, uint32 p1 = 0, uint32 p2 = 0, uint32 p3 = 0);

private:
	void WriteBaseLog(uint32 type, LogFileStream& file, time_t sec, time_t usec, account_info *a_info, PolicedContext *player);
	void ResetMap(struct tm *local);
	void ReWriteLog(TimerHolder& th);
private:
	FildMap m_file_map;						//������־�ļ�

	char m_time[50];						//���������΢������
	uint32 m_today;							//���յ�����
	uint32 m_host;							//���յ�Сʱ
	
	//�����������ݵ�һЩ����
	set<uint32> m_can_use_item;
	set<uint32> m_gold_goods;
	set<uint32> m_heal;
private:
	typedef void (LogFileOperate::*handle)(uint32 log_type, packet*, LogFileStream*, time_t, time_t, account_info*, PolicedContext*);
	handle m_handle_map[MAX_LOG_FILE_TYPE];
private:
	void HandlerInit();
	void Handle_Write_Recharge(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Deal(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_ItemLog(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_YbIncome(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Pay(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Login(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Logout(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_CreateRole(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Death(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_AcceptTask(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Task(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Lvup(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Yxb(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Map(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Transcript(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Online(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_GameEnter(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Chat(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Relive(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_BindGold(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_NewCardReceive(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Stall(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_WantedPacket(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);	
	void Handle_Write_ChooseFaction(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_ActivityInfo(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);	
	void Handle_Write_ClientInfo(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_AttackPacket(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_FormatLog(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);
	void Handle_Write_Forge_Log(uint32, packet *, LogFileStream *, time_t, time_t, account_info*, PolicedContext*);

	//1001��־
	void Handle_Write_ObjectLoss(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*);
	void Handle_Write_OnlineUser24th(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*);
	void Handle_Write_Union(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*);
};

#endif
