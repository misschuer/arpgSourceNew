#ifndef _SCENED_SCRIPTS_H_
#define _SCENED_SCRIPTS_H_

#include "Map.h"
#include <comm/common_stl.h>
#include <protocol/external.h>
#include <shared/lua_helper.h>

class Unit;
class Player;
class GameObject;
class Creature;
class Map;

int scripts_init(const char*);
int scripts_free();
int scripts_reload();

//��ȡģ�����ݵ��ڴ�
extern bool LoadTemplate();
//---------------------------------------------------------------------------------------------/
//ȫ�ֱ�����ʼ���ű�
extern int DoInitSomethingScript();
//---------------------------------------------------------------------------------------------/
//ʹ�ü���
extern int DoSpellCastScript(Unit *caster,Unit *target,float dst_x,float dst_y,uint32 spellid,uint32 spell_lv, Unit *unit, const char *data = NULL);

//---------------------------------------------------------------------------------------------/
//ʹ����Ʒ
extern int DoUseItemScript(Player *player,uint32 template_id,uint32 count);

//---------------------------------------------------------------------------------------------/
//��
extern int DoJumpScript(Unit *player);

//---------------------------------------------------------------------------------------------/
//����AI �� NPC���Ľű�
extern int DoSelect_Instance_Script(Map *m);
extern int OnSetInstanceState(Map *m,int fromstate,int tostate);
extern int OnInstanceTryToNextState(Player *player, Map *m, uint16 level = 0, uint32 param = 0);
extern int OnNotifyArea(Map *m, Unit *trigger, const char *name, float x,float y);
extern int OnMapTimeBegin(Map *m);
extern int OnAfterJoinPlayer(Map *m, Player *player);
extern int OnJoinPlayer(Map *m, Player *player);
extern int OnLeavePlayer(Map *m, Player *player);
extern int OnPlayerKilled(Player *player, Player *killer, uint32& silver);
extern int OnPlayerKilledByMonster(Player *player, Unit *killer);
extern int OnPlayerHurted(Player *killer, Player *player, double damage);
extern int OnPlayerDeath(Player *player);
extern int OnPlayerUpgrage(Map *m, Player *player, uint32 prev, uint32 lv);
extern int DoIsFriendly(Map *m,const Unit *player,const Unit *target);
extern int DoMapBuffBonus(Map *m,const Unit *unit);//��ͼ�⻷

extern int DoCompleteQuest(Map *_m, Player *player, uint32 questid);	//�������ִ�нű�
extern int DoIsNeedTeleportWhileMapClear(Map *_m, Player *player);			//��ͼ��Ҫ�����ʱҪ������
extern int DoIsNeedTeleportToOrigin(Map *_m);							// �Ƿ���Ҫ�ص�����ĵط�
extern int DoAcceptQuest(Map *_m, Player *player, uint32 questid);	//��������ִ�нű�
extern int DoBeforUseGameObjectScript(Player *player, GameObject *go, uint32 go_templateid);
extern int DoGameObjectScript(Player *player,GameObject *go,uint32 go_templateid);
extern int DoQuestItemScript(Player *player,uint32 item_templateid);
extern int DoScriptInit(const char* ainame,Creature *creature);


extern int DoGossipMessage(const char* ainame,Unit *owner,Player *player,uint32 option_id,string &text,vector<gossip_menu_option_info> &gossip_menu,string &key);
extern int DoMoveInLineOfSight(const char* ainame,Creature *self,Unit *unit);
extern int DoDamageTaken(const char* ainame,Creature *self,Unit *unit,double& damage);
extern int DoDamageDeal(const char* ainame,Creature *self,Unit *unit,double damage);
extern int DoGiveDamage(const char* ainame,Creature *self,Unit *unit,double& damage);
extern int DoKilledUnit(const char* ainame,Creature *self,Unit *victim);
extern int DoJustDied(const char* ainame,Creature *self,Unit *killer,uint32 &deadtime);
extern int DoSaySomething(const char* ainame,Creature *self);


//---------------------------------------------------------------------------------------------/
//����ű�
extern int DoRespawn(Player *player,Map *map,uint32 respwan_type,uint32 respwan_map,uint16 respwan_x,uint16 respwan_y);

//����ʱ����Ϸ���
extern bool DoCheckTeleport(Player *player, uint32 entry, uint16 posX, uint16 posY);
//---------------------------------------------------------------------------------------------/

//��������ͼ����ʱ����
extern int DOWorldMapTeleportScript(Player *player,uint32 map_id,float pos_x,float pos_y);
//---------------------------------------------------------------------------------------------/

//��ȡ����ս��Ʒ
extern int DoLootAllot(Player *player,Creature *owner,  Unit *unit, int boss_type);

//---------------------------------------------------------------------------------------------/
//BUFF������������BUFF����
extern int DoBuffTriggerScript(Unit *unit,uint16 buff_id,uint32 buffEffectId);


//---------------------------------------------------------------------------------------------/
//BUFF����,������BUFF����
extern int DoBuffOverScript(Unit *unit,uint16 buff_id,uint32 buffEffectId);

extern int GetBuffFrequency(uint32 buffEffectId);

//---------------------------------------------------------------------------------------------/
//װ�������仯�����¼���BUFF���ӵĶ�������
extern int DOComputeBuffAttr(Unit *unit,uint16 buff_id,uint32 buffEffectId);

//---------------------------------------------------------------------------------------------/
//���һЩ��Ӧ��BUFF
int DoOnlineClearBuff(Player *player);

//---------------------------------------------------------------------------------------------/
//�������ս��֮��ɵ�ʲô����
extern int DosometingScript(Player *player);
//PVP�������
extern int DOPlayerPvPScript(Player *player,Player* target);
//PVP�����������
extern int DOPlayerPvPKilledScript(Player *killer, Player* target);
//��ұ����﹥��
extern int DOPlayerPVEScript(Unit* creature, Player* target);
//PVE��ҹ���boss
extern int DOPlayerPvBScript(Player* player, Unit*creature);
//---------------------------------------------------------------------------------------------/
//������һ�þ���ӳ�
extern int DOComputeExpBonusScript(Player *player, Creature *creature, uint32 exp,int percent,double &vip_exp);

//---------------------------------------------------------------------------------------------/
//ִ�е�ͼ�ű��ĳ�ʼ���¼�
extern int DoInitMapScript(Map* map);
//ִ�е�ͼ����������ʼ�� ���ᱻ���¼�������
extern int DoInitMapWorldObject(Map* map);
//ִ�е�ͼӲ�����ݳ�ʼ��
extern int DoInitReadHddMapData(Map* map);
//ִ�����е�ͼ�ű��ĳ�ʼ���¼�
extern int DoInitAllMapScript();
//�Ի������Ӧ����
extern int DoActivityOperAttrScript(Player *player, uint32 id);
//��õ�ͼ�ű�����������ʱ��
extern int DoGetMapSingleRespawnScript(Map* map, Player* player, uint32& res);
//---------------------------------------------------------------------------------------------/

//��ʱ���ص�����
extern int DOTimerTickCallBack(Map *map, const char *s_callback, Map::script_instance_var param[10]);

//���������������飬���ӣ���Ԫ��
extern int DoQuestRewardScript(Player *player, int32 quest_id = 0, int32 xp = 0,int32 silver = 0,int32 bind_gold = 0, int32 taolue = 0, uint8 all_flag = 0, uint32 special_flag = 0);

int LuaCallChat(lua_State *scriptL);				//lua����������Ϣ

//ȡ��ս����Ϣbinlog
extern int LuaGetFightingInfo(lua_State *scriptL);
//ִ��luaGM����
extern int DoGMScripts(lua_State *scriptL, Player *player, string &gm_commands);

//�ƶ�֮ǰ����Ҫ������߼�
extern bool OnMoveTo(Map *m, Player *player);
//Ҫ��ʼ����֮ǰ��Ҫ������߼�
extern bool OnStartAttack(Map *m, Player *player);

//GM�����KEYת��
extern int GetGmCommandKey(string &gm_str);

//��������
extern int DoRecalculationAttrs(Player *player, bool bRecal = true);
//�������������2���ȼ���ӦѪ���Ĳ�ֵ
extern int DoGetCharDiffHp(uint32 prev, uint32 curr, int32& diff);
//�����ʼ��ǰ
extern int DoBeforeInitCreature(Creature *creature, Map *map);
//������ȼ���ʼ��������Ϣ
extern int DoInitCreatureInfo(Creature *creature, Map *m, bool bRecal = false);
//�����ʼ��
extern int creatureInit(Creature *creature); 
//��������
extern int DoTestData(Player *player, string& str); 
//�ж�ս��Ʒ�Ƿ���Ҫ������
extern bool DoCheckIfSendToAppdAfterLootSelect(Player *player, uint32 entry, uint32 count); 
//��������˳���ͼǰ��
extern int DoPlayerExitInstance(Map* map, Player* player, uint32 reserve);
// ָ����Ҵ��͵�Ŀ�ĵ�
extern int SpecifyTeleportOrigin(Map* map, Player* player);
//�������pkģʽǰ�Ļص�
extern int DoSetAttackModeCallback(Map* map, Player* player, uint8 mode);
//���븱��ǰ���ж�
extern int DoInstancEnter(Map* map, Player* player, uint32 cur_mapid, uint32 to_mapid);
//��ù����
extern int DoGetCreatureBaseExp(Unit* creature, Unit* owner);
//�ж�ĳ�������Ƿ�
extern int DoIsEnoughConsumptionCast(Player *player, uint32 spell_id);
//����ĳ�����ܵ�����
extern int DoSpellConsumption(Player *player, uint32 spell_id);
extern int DoPickRiskReward(Player *player);
//���ü���cd
extern int DoSetSpellCD(Player* player, uint32 spell_id);
//��lua�жϿ�ʼʩ��ǰ���߼�
extern bool DoHandleSpellStart(Player* player, uint32 spell_slot, uint16 tar_x, uint16 tar_y, Unit* target, uint32 &spellId);
//������������
extern int DoHandlePassiveEffect(Unit* caster_ptr, Unit* target_ptr, uint32 dispatchType);
//��Ѫ�������ı�
extern int DoOnHpChanged(Unit* caster_ptr, uint32 prev);
//��lua�жϲɼ�����߼�
extern int DoHandlePickGameObject(Player* player, uint32 gameObjectId);
//��õ�ͼ��һЩ��ʼֵ
extern int DoGetInitMapData(Map *map);
//Ӧ�÷�֪ͨ����������Ԫ����ͭǮ��Щʲô
extern int DoScenedComsumeMoney(Player *player, uint8 money_type, uint8 use_type,const string &param);
//�����ɵ�ɶ
extern int DoAfterRespawn(Map* map, Unit* respawner);
//������(�����־λ)
extern int LuaHasFlag(lua_State* scriptL);
//��ȡ����������ʱ��
extern int LuaGetMsTime(lua_State *scriptL);
//lua�ű��ͷż���
extern int LuaDoSpellCastScript(lua_State *scriptL);
//���ݵ�ͼid�ж����ڵ�ͼ�Ƿ�Ϊ�����ͼ
extern bool DoIsKuafuMapID(uint32 map_id);
//��ȡ���Ǹ����
extern int DoGetRespawnPos(vector<uint16> &v);
//��Ҵ���
extern int DoPlayerTeleport(Player* player);
//�������ɵ�ʲô
extern int DoScenedDoSomething(Player *player, uint32 type, uint32 data, string str);
//���ݵ�ͼid�ж����ڵ�ͼ�Ƿ�Ϊ�����ͼ
extern bool DoIsWorldMapID(uint32 map_id);
//�ж�item_entry�ǲ�����Դ, ����� money_type ��Ϊuint32(-1)
extern bool DoGetMoneyType(uint32 item_entry, uint32 &money_type);
// �Ƿ���ð�յ�ͼ
extern int DoIsRiskMap(uint32 mapid);
// ���ð�յ�ͼ�Ĵ�����Ϣ
extern int DoScenedGetRiskTeleportInfo(Player* player, int &mapid, float &x, float &y, string &generalId);
// ��ͼ�Ƿ���ʱ������
extern bool isMapTimeLimit(uint32 mapid);

extern void DoTerminalContinuousAction(Unit* unit);
#endif

