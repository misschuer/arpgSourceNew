#ifndef _APPD_SCRIPT_H_
#define _APPD_SCRIPT_H_

#include <shared/lua_helper.h>

class AppdContext;
class Item;
class BinLogObject;

int scripts_init(const char* path);
int scripts_free();
int scripts_reload();

//读取所有数值文件，并返回字符串
extern int DoReadNumFiles(string &num_str);
//读取模版数据到内存
extern bool LoadTemplate();
//获取配置信息
extern int DoGetConfig(lua_State *);
//获得所有c++全家对象函数
extern int LuaGetCXXGlobalPtr(lua_State *);
//执行回调
extern int DoGetObjectsCallBack(vector<core_obj::GuidObject*> v, const string& callback_guid, const string &callback_string);
//屏蔽词接口
extern int LuaFuckPingBi(lua_State *scriptL);
//加载屏蔽词接口
extern int LuaLoadFuckPingBi(lua_State *scriptL);
//属性重算binlog
extern int LuaGetEquipAttrsInfo(lua_State *scriptL);
//---------------------------------------------------------------------------------------------/

//执行luaGM命令
extern int DoGMScripts(AppdContext *player, string &gm_commands);
//消费用调一下
extern int DoLimitActivityConsumption(AppdContext *player,uint32 money_type, double val);
//GM命令的KEY转换
extern int GetGmCommandKey(string &gm_str);
//玩家属性重算
extern int DoCalculAttr(AppdContext* player, BinLogObject *attr);
//处理元宝消费问题
extern int DoGlodConsumeStatistics(AppdContext* player, double val);
//私聊后做点什么
extern int DoAfterChatWhisper(AppdContext* player1, AppdContext* player2);
//10分钟存储一次修炼记录
extern int LuaSaveXiulianData(lua_State *scriptL);
//获取排行榜玩家guid
extern int LuaGetRankPlayerGuidByType(lua_State *scriptL);
// 玩家等级改变了, 修改自己在等级列表中的位置
extern int LuaLevelChanged(lua_State *scriptL);
//获取服务器运行时间
extern int LuaGetMsTime(lua_State *scriptL);
//给所有在线玩家发错误提示
extern int LuaSendOperationFailed(lua_State *scriptL);
//合服后需要应用服做的事情
extern int DoAppdMergeSomething();
//排行榜新增计划
extern int LuaRankInsertTask(lua_State *scriptL);
//清空排行榜
extern int LuaClearRankTask(lua_State *scriptL);
//更新排行榜
extern int LuaUpdateRankList(lua_State *scriptL);
//获取排行榜GuidList
extern int LuaGetRankGuidTable(lua_State *scriptL);

extern int LuaGetRankName(lua_State *scriptL);
//排行榜是否有某个GUID
extern int LuaRankHasGuid(lua_State *scriptL);
//更新排行榜like数
extern int LuaUpdateRankLike(lua_State *scriptL);
//服务器启动后，需要loadDB的一些数据
extern int DoStartServerLoadDB();
//服务器关闭前，保存lua一些数据
extern int DoCloseServerSaveDB();
//玩家充值以后执行的LUA
extern int DoAddRechargeSum(AppdContext *player, const string& recharge_id, double val, uint32 time);
//数据库插入
extern int LuaMongoInsert(lua_State *scriptL);
//数据库更新
extern int LuaMongoUpdate(lua_State *scriptL);
//数据库查询
extern int LuaMongoQuery(lua_State *scriptL);
//数据库删除
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
