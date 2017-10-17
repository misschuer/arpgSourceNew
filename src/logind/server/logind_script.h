#ifndef _LOGIND_SCRIPT_H_
#define _LOGIND_SCRIPT_H_

#include <comm/common_stl.h>
#include <shared/lua_helper.h>

int scripts_init(const char*);
int scripts_free();
int scripts_reload();

//��ȡ������Ϣ
extern int DoGetConfig();

//��ȡģ�����ݵ��ڴ�
extern bool LoadTemplate();

//���¶�ȡ����
extern int LuaLoadConfig(lua_State* scriptL);
//GM�����KEYת��
extern int GetGmCommandKey(string &gm_str);
//����������Ϸ���ñ������
extern int DoReloadGameConfigTable(const char *key, const char *value);
//�����������ʲô
extern int DoPlayerLogout(logind_player* player);

//��ȡ����(�ַ���)
extern int DoGetCharacters(uint8 pos, string & parameter);

//�޸��������
extern int DoRepairPlayerData(const string &account, vector<GuidObject*> &data, bool &b);

//��ó������ĸ���
extern int DoGetScenedSize(uint32 &result);

//��ӳ��������������
extern int DoAddScenedPlayer(uint32 conn_id);

//���ٳ��������������
extern int DoSubScenedPlayer(uint32 conn_id);

//����һ���Ĺ����ó���������
extern int DoGetScenedFDByType(uint16 inst_type, uint32 mapid);

//������ߵ�ʱ���ж��Ƿ��¼������ڵ�ͼ����Ϣ����ౣ��10����
extern int DoIsRecordIntanceInfo(logind_player* player, uint32 map_id, uint32 isfuben, uint32 fuben_type);

//�Ϸ������ݴ���
extern int DoMergeSomething();
//pk�������ݿ������ѡ��Ҫ���͵��ĵ�ͼid
extern bool DoSelectKuafuMapid(logind_player* player, uint32 warid, uint8 kuafutype, uint32 number, uint32 reverse, string reverse_str);
//���ݵ�ͼid�ж����ڵ�ͼ�Ƿ�Ϊ�����ͼ
extern bool DoIsKuafuMapID(uint32 map_id);
//������Ҹ��ѵȼ�
extern int DoPlayerPayLevel(logind_player* player);
//�Ƿ���Ҫ�ṩ����generalid
extern int DoIsNeedGeneralid(uint32 mapid, bool &result);
extern bool IsInstanceOfflineReenter(uint32 mapid);
// ���ð�յ�ͼ�Ĵ�����Ϣ
extern int DoGetRiskTeleportInfo(logind_player* player, int &mapid, float &x, float &y, string &generalId);
// ��õ�ͼ��������
extern int OnGetMapLineCount(uint32 mapid, uint8 &result);
//���һ����½���ͼʵ��
extern int DoFindOrCreateMap(uint32 mapid, uint16 inst_type, const string &general_id, uint32 lineno, int &index);
//���ݵ�ͼid�ж����ڵ�ͼ�Ƿ�Ϊ�����ͼ
extern bool DoIsWorldMapID(uint32 map_id);
//��ȡ�´α������ݿ��ʱ��
extern int DoGetNextSaveTime(uint32 &t);
//��ʼ�������Ϣ
extern void DoSetNewPlayerInfo(logind_player* player);
// �Ƿ���ð�յ�ͼ
extern int DoIsRiskMap(uint32 mapid);
#endif	
