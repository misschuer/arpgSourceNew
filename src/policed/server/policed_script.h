#ifndef _LOGIND_SCRIPT_H_
#define _LOGIND_SCRIPT_H_

#include <comm/common_stl.h>
#include <shared/lua_helper.h>

int scripts_init(const char*);
int scripts_free();
int scripts_reload();

//��ȡ������Ϣ
extern int DoGetConfig();

extern int DoSendSms(const char* tele_no,const char* context);

extern bool GetPlatFormGameCode();

//GM�����KEYת��
extern int GetGmCommandKey(string &gm_str);

extern int GetPlatfromPostType(vector<string> &vec);
extern int DoGetPostUrl(const string &plat_id, map<uint32,string> &m);
//��ȡģ�����ݵ��ڴ�
extern bool LoadTemplate();
#endif
