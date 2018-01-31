#ifndef _APPD_SCRIPT_H_
#define _APPD_SCRIPT_H_

#include <shared/lua_helper.h>

class AppdContext;
class Item;
class BinLogObject;

int scripts_init(const char* path);
int scripts_free();
int scripts_reload();

//��ȡ������ֵ�ļ����������ַ���
extern int DoReadNumFiles(string &num_str);
//��ȡģ�����ݵ��ڴ�
extern bool LoadTemplate();
//��ȡ������Ϣ
extern int DoGetConfig(lua_State *);
//�������c++ȫ�Ҷ�����
extern int LuaGetCXXGlobalPtr(lua_State *);
//ִ�лص�
extern int DoGetObjectsCallBack(vector<core_obj::GuidObject*> v, const string& callback_guid, const string &callback_string);
//���δʽӿ�
extern int LuaFuckPingBi(lua_State *scriptL);
//�������δʽӿ�
extern int LuaLoadFuckPingBi(lua_State *scriptL);
//��������binlog
extern int LuaGetEquipAttrsInfo(lua_State *scriptL);
//---------------------------------------------------------------------------------------------/

//ִ��luaGM����
extern int DoGMScripts(AppdContext *player, string &gm_commands);
//�����õ�һ��
extern int DoLimitActivityConsumption(AppdContext *player,uint32 money_type, double val);
//GM�����KEYת��
extern int GetGmCommandKey(string &gm_str);
//�����������
extern int DoCalculAttr(AppdContext* player, BinLogObject *attr);
//����Ԫ����������
extern int DoGlodConsumeStatistics(AppdContext* player, double val);
//˽�ĺ�����ʲô
extern int DoAfterChatWhisper(AppdContext* player1, AppdContext* player2);
//10���Ӵ洢һ��������¼
extern int LuaSaveXiulianData(lua_State *scriptL);
//��ȡ���а����guid
extern int LuaGetRankPlayerGuidByType(lua_State *scriptL);
// ��ҵȼ��ı���, �޸��Լ��ڵȼ��б��е�λ��
extern int LuaLevelChanged(lua_State *scriptL);
//��ȡ����������ʱ��
extern int LuaGetMsTime(lua_State *scriptL);
//������������ҷ�������ʾ
extern int LuaSendOperationFailed(lua_State *scriptL);
//�Ϸ�����ҪӦ�÷���������
extern int DoAppdMergeSomething();
//���а������ƻ�
extern int LuaRankInsertTask(lua_State *scriptL);
//������а�
extern int LuaClearRankTask(lua_State *scriptL);
//�������а�
extern int LuaUpdateRankList(lua_State *scriptL);
//��ȡ���а�GuidList
extern int LuaGetRankGuidTable(lua_State *scriptL);

extern int LuaGetRankName(lua_State *scriptL);
//���а��Ƿ���ĳ��GUID
extern int LuaRankHasGuid(lua_State *scriptL);
//�������а�like��
extern int LuaUpdateRankLike(lua_State *scriptL);
//��������������ҪloadDB��һЩ����
extern int DoStartServerLoadDB();
//�������ر�ǰ������luaһЩ����
extern int DoCloseServerSaveDB();
//��ҳ�ֵ�Ժ�ִ�е�LUA
extern int DoAddRechargeSum(AppdContext *player, const string& recharge_id, double val, uint32 time);
//���ݿ����
extern int LuaMongoInsert(lua_State *scriptL);
//���ݿ����
extern int LuaMongoUpdate(lua_State *scriptL);
//���ݿ��ѯ
extern int LuaMongoQuery(lua_State *scriptL);
//���ݿ�ɾ��
extern int LuaMongoDelete(lua_State *scriptL);

extern int LuaWorldBossEnroll(lua_State *scriptL);
extern int LuaResetWorldBossEnroll(lua_State *scriptL);
extern int LuaGetWorldBossEnrollInfo(lua_State *scriptL);

extern int OnSinglePVPMatched(const char guid[50], const char key[50], const uint32 time);

extern int LuaInitQueueInfo(lua_State *scriptL);

extern int LuaAddMatchQueue(lua_State *scriptL);

extern int LuaCancelMatchQueue(lua_State *scriptL);

extern int LuaOnProcessMatchQueue(lua_State *scriptL);


extern int LuaSetMatchingKuafuType(lua_State *scriptL);
extern int LuaGetMatchingKuafuType(lua_State *scriptL);
extern int LuaIsKuafuTypeMatching(lua_State *scriptL);
extern int LuaGetKuafuTypeMatchingArg(lua_State *scriptL);


extern int LuaGroupMatchPush(lua_State *scriptL);
extern int LuaGroupMatchRemove(lua_State *scriptL);
extern int LuaGetGroupMatchList(lua_State *scriptL);

extern int LuaLocal3v3MatchPush(lua_State *scriptL);
extern int LuaLocal3v3MatchRemove(lua_State *scriptL);
extern int LuaGetLocal3v3MatchList(lua_State *scriptL);

extern int LuaInstancePreparePush(lua_State *scriptL);
extern int LuaInstancePrepareCancel(lua_State *scriptL);
extern int LuaGetInstancePrepareInfo(lua_State *scriptL);

extern int LuaLocal3v3PreparePush(lua_State *scriptL);
extern int LuaLocal3v3PrepareCancel(lua_State *scriptL);
extern int LuaGetLocal3v3PrepareCuInfo(lua_State *scriptL);
extern int LuaGetLocal3v3PrepareList(lua_State *scriptL);

extern int LuaGetPlayerGuidByOrderId(lua_State *scriptL);

extern int LuaUpdatePlayerRechargeInfo(lua_State *scriptL);

extern int LuaGetOrderIdIsDealed(lua_State *scriptL);

extern int LuaGetPlayerAccountByOrderId(lua_State *scriptL);

extern int LuaCheckGiftcodeIsUsed(lua_State *scriptL);
extern int LuaAddUsedGiftcode(lua_State *scriptL);

extern int LuaModifyGame2BookingInfo(lua_State *scriptL);

extern int LuaGetPlayerNameAndPayTimeByUId(lua_State *scriptL);
extern int LuaCheckUidIsDealed(lua_State *scriptL);

#endif
