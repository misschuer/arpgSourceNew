#ifndef _ROBOTD_SCRIPT_H_
#define _ROBOTD_SCRIPT_H_

#include <shared/lua_helper.h>
#include "robotd_context.h"

int scripts_init(const char* path);
int scripts_free();
int scripts_reload();

//ȡ�������
extern int GetRandName(string &name);

//�����˵�¼
extern int DoRobotLoginOk(const string &account, uint32 fd, RobotdContext *robot);

//�����˸����Ժ�
extern int DoRobotRespawn(RobotdContext *robot);

//�����˵ǳ�
extern int DoRobotLogout(const string &account, uint32 fd);

//���������ӿ���ɹ�
extern int DoRobotWarConn(const string &account, uint32 fd);

//�����˶Ͽ��������
extern int DoRobotWarClose(const string &account, uint32 fd);

//���������
extern int DoPacketHandle(const string &account, uint32 fd, packet *pkt);

//����������
extern int DoRobotUpdate(uint32 diff);

//ȡջ��Ϣ
extern int DoGetStack(const string &account,string &info);


extern int LuaGetMsTime(lua_State *scriptL);

#endif
