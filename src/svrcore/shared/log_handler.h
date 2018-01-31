#ifndef _LOG_HANDLER_H_
#define _LOG_HANDLER_H_

#include <comm/common_stl.h>
#include <net/packet.h>
#include "object/SharedDef.h"
#include "lua_helper.h"
#include <functional>

#define LOG_STRING_MAX_LEN 10000

extern std::function<bool(WorldPacket& pkt)> fp_send_to_policed;

extern void InitLogPacket(WorldPacket &pkt, uint32 log_type, const string & account, const string &player_id);

//д������log
extern void WriteChatLog(uint32 chat_type, const string & account, const string &player_from, const string &player_to, const char* content, uint32 level, int gmlevel, const string &name_to);

//��¼�û���ֵ��Ϊ
extern void WriteRecharge(const string & account, const string &player_id, double amount, double money, uint32 balance, uint32 level, const string &order);

//��¼�û��Ľ�����Ϊ
extern void WriteDeal(const string & account, const string &player_id, uint32 type, uint32 buy_mapid, uint32 buy_level, uint32 buy_cp, uint32 buy_yd, vector<deal_goods> *buy_goods,
	uint32 sell_sid, const string & sell_roleid, const string & sell_user, uint32 sell_mapid, uint32 sell_level, uint32 sell_cp, uint32 sell_yd, vector<deal_goods> *sell_goods);

//��¼�����Ԫ������
extern void WriteYbIncome(const string & account, const string &player_id, double amount, double balance, uint32 level, uint32 reason,
						  double old_value, const string &trace_id, uint32 p1, uint32 p2,
						  double unit_price,uint16 item_bind, uint16 item_del, uint32 quest);

//��¼�����Ԫ������
extern void WrtiePay(const string & account, const string &player_id, uint32 operTime, uint32 isCost, uint32 reason, double modifyValue,
					 string& relateItemIds, string& relateItemNums, uint32 level);

//��¼�û���¼��Ϊ
extern void WriteLogin(const string & account, const string &player_id, uint32 level, const char *ip, uint32 map, double force, double currGold);

//��¼�û��ǳ���Ϊ
extern void WriteLogout(const string & account, const string &player_id, uint32 createTime, uint32 logoutTime, uint32 onlineLast,
						const char *ip,	uint32 gender, uint32 level, double force, uint32 activityValue, uint32 mapId, uint32 mainQuestId,
						double rechargeGoldSum, double currGold, double currBindGold, double gameMoney, double gameBindMoney);

//��¼�û�������ɫ��Ϊ
extern void WriteCreateRole(const string & account, const string &player_id, const char *rolename, string ip, uint32 gender);

//��¼�û������¼�
extern void WriteDeath(const string & account, const string &player_id, const char *reason, uint32 level, uint32 map, uint32 is_player);

//��¼�û������������Ϊ
//extern void WriteAcceptTask(const string & account, const string &player_id, uint32 taskid, uint32 type, uint32 map);
extern void WriteAcceptTask(const string & account, const string &player_id,uint32 time_stamp, uint32 taskid, uint32 type, const string &remain);

int LuaWriteAcceptTask(lua_State *scriptL);

//��¼�û�����������Ϊ
//extern void WriteTask(const string & account, const string &player_id, uint32 taskid, uint32 map_id, uint32 result);
extern void WriteMainTask(const string & account, const string &player_id, uint32 time_stamp, uint32 taskid, uint32 type, const string &remain);

int LuaWriteTask(lua_State *scriptL);

//��¼�û�����
extern void WriteRelive(const string & account, const string &player_id, uint32 type, uint32 map);

//��¼�û������¼�
extern void WriteLvup(const string & account, const string &player_id, uint32 createTime, uint32 lvUpTime, uint32 level, uint32 levelDiffTime);

//��¼�û����������Ϊ
extern void WriteYxb(const string & account, const string &player_id, uint32 operTime, uint32 isCost, uint32 reason, 
						double modifyValue, string& relateItemIds, string& relateItemNums, uint32 level);

//��¼�û��İ�Ԫ����Ϊ
extern void WriteBindGold(const string& account, const string& player_id, uint32 operTime, uint32 isCost, uint32 reason, 
						  double modifyValue, string& relateItemIds, string& relateItemNums, uint32 level);

//��¼�û���ȡ���ֿ�����Ϊ
extern void WriteNewCardReceive(const string & account, const string &player_id, const char * card_id, uint32 map, uint32 x, uint32 y);

//��¼��̯��Ϊ
extern void WriteStall(const string & account, const string & player_id, const string & item_id, uint32 entry, uint32 amount, uint32 ingot_price, uint32 silver_price, uint32 stall_type);

//��¼ͨ����������Ϊ
extern void WritePacket(const string & account, const string &player_id, packet *pkt);

//��¼������Ʒ��־��bind_mode 1Ϊ���󶨣�2�ǰ�
extern void WriteItemLog(const string & account, const string &player_id, uint32 itemid, uint32 amount, uint32 new_amount, uint32 opid, uint32 level, int32 bind_mode, double balance = 0, double money = 0, uint32 map = 0);

//��¼�û��л���ͼ����Ϊ
extern void WriteMap(const string & account, const string &player_id, uint32 level, uint32 nonce_map, uint32 to_map);

//��¼��������
//extern void WriteOnline(uint32 account_count, uint32 player_count);
extern void WriteOnline(uint32 time_stamp, uint32 account_count, uint32 player_count, uint32 ip_count, uint32 old_player_count);



//��¼�û�������Ϸ������(δ����ɫ)
extern void WriteGameEnter(const string & account, const char *ip);

//��¼���ѡ����Ӫ�����
extern void WriteChooseFaction(const string & account, const string &player_id, uint32 oper_type, uint32 result);

//��¼��Ӫ�������Ϣ
extern void WriteActivityInfo(const string & account, const string &player_id,uint32 type, uint32 acti_version, uint32 acti_id);

//��¼�û��򸱱�����Ϊ
extern void WriteTranscript(const string & account, const string &player_id, uint32 starttime, uint32 timelong, uint32 num, uint32 level, uint32 map_id);

//��¼�ͻ�����Ϣ
extern void WriteClientInfo(const string &player_id, string& client, string& browser, string& isdebug, string& language, string& version, string& flash_version, string& x, string& y, string& os);

//��¼������
extern void WriteAttackPacker(const string & account, const string &player_id, uint32 p_id, uint32 type, const char *msg,...);

//��¼��Ф���Ѽ�¼
//extern void WriteAttackPacker(const string & account, const string &player_id, uint32 old_pro, uint32 new_pro,);

//��¼���߰�����Զ�����־
extern void WriteFormatLog(const char *msg);

//��¼�ͻ�����־
extern void WriteClientLog(const string & account, const string &player_id,const char *msg);

//��������־
int LuaWriteAttackPacker(lua_State *scriptL);

//lua��־ͳһ�ӿ�
//int LuaWriteLog(lua_State* scriptL);

//lua����������Ϊ��־
//int LuaWriteItemLog(lua_State* scriptL);

//������־
int LuaWriteFubenLog(lua_State *scriptL);

/////////////////////////////////////////////////////////
//��Ѷר�ýӿ�
//����ƽ̨���ݣ���ȡ������Ϣ
string GetPlatInfo(const string &platdata,const string &key);
//TX�û���¼��־
extern void WriteTXUserLog(const string &account,const string &player_id,const string &player_name,uint32 player_level,const string &platform,uint32 create_time);

//TX��ɫ��¼��־
extern void WriteTXPlayerLog(const string &account,const string &player_id,const string &player_name,uint32 player_level,const string &platform,uint32 create_time);


//TX�û�������¼��־
extern void WriteTXUpradeLog(const string &account,const string &player_id,const string &player_name,uint32 old_level,uint32 new_level,uint32 sucess,uint8 upgradeType,const string &params,uint32 create_time);

//TX�û�������־
extern void WriteTXNewTaskLog(const string &account,const string &player_id,const string &player_name,uint32 taskid,uint32 status,uint32 quality,uint32 create_time);

//TX�û���¼��־
extern void WriteTXLoginLog(const string &account,const string &player_id,const string &player_name,uint32 player_level,const string &siteUrl,const string &adFrom,const string &platform,const string &ip,uint32 create_time);

//TX�û�������־
extern void WriteTXOffineLog(const string &account,const string &player_id,const string &player_name,uint32 player_level,const string &siteUrl,const string &adFrom,
							 const string &platform,const string &ip,uint32 online_time,uint32 history_time,uint32 create_time);

//TX�û�������־
extern void WriteTXOnlineLog(uint32 allcount,uint32 cashcount);

//TX�û�Ԫ����־
extern void WriteTXMoneyLog(const string &account,const string &player_id,const string &player_name,uint32 rootid,uint32 type_id,double old_value, double new_value,double gold,uint32 gold_ticke,uint32 goods_id,uint32 num,uint32 create_time,const string &platform);

//1001��־
extern void WriteObjectLoss(const string &account, const string &player_id, const string &obj_guid, uint32 op_type);

//0��������־
extern void WriteOnlineUser24th(const string &account, const string &player_id, const string &name, uint32 create_time, uint32 last_login_time, uint32 from_last_time,
					const string &ip, uint32 gender, uint32 level, double force, uint32 active_value, uint32 map_id,uint32 main_quest_id,
					uint32 history_recharge, double gold,double bind_gold,double money,double bind_money);

int LuaWriteOnlineUser24th(lua_State *scriptL);


//������־
extern void WriteUnion(const string &account, const string &player_id, uint32 time_stemp, const string &faction_id, const string &faction_name, uint32 type, const string &remain);

int LuaWriteUnion(lua_State *scriptL);

/////////////////////////////////////////////////////////
#endif
