#include "scened_app.h"
#include "scened_scripts.h"
#include "Unit.h"
#include "Player.h"
#include "scened_context.h"
#include "Map.h"
#include "Creature.h"
#include "GameObject.h"
#include "BuffManager.h"
#include "LootManager.h"
#include "shared/probability_rand.h"
#include <shared/log_handler.h>
#include <shared/storage_loader.h>
#include <shared/add_memdb_index.h>
#include <shared/lua_packet_binding.h>

LuaStack *gLuaStack = NULL;
lua_State *L = NULL;
const char *sdir = NULL;

static const struct luaL_reg mylib[] = 
{ 
	{"outString",	__outString<ScenedApp>},
	{"outDebug",	__outDebug<ScenedApp>},
	{"outError",	__outError<ScenedApp>},

	//�������
	{"randInt",	__RandInt},
	{"randIntD",	__RandIntD},
	{"randIndex",	__RandIndex},
	{"gettimeofday",			&lua_gettimeofday},

	//{"writeLog",		&LuaWriteLog},				//��־ͳһ�ӿ�
	//{"writeItemLog",	&LuaWriteItemLog},			//lua����������Ϊ��־	
	{"getFightingInfo",			&LuaGetFightingInfo},		//ս����Ϣ		
	{"callChat",			LuaCallChat},			//����������Ϣ�ӿ�
	{"spellCastScript",					LuaDoSpellCastScript},			//�ͷż���

	{"setBit",			&LuaSetBit},
	{"unSetBit",		&LuaUnSetBit},
	{"hasFlags",		&LuaHasFlag},
	{"getMsTime",		&LuaGetMsTime},				//��ȡ����������ʱ��


	{NULL, NULL} /* sentinel */ 
};

extern const struct luaL_reg LBinLog[] =
{
	LUA_BINLOG_REG_LIBNAME(BinLogObject),
	{NULL, NULL} /* sentinel */ 
};

extern const struct luaL_reg LMap[] =
{
	{"GetMapID",			&Map::LuaGetMapId},

	{"AddCreature",			&Map::LuaAddCreature},
	{"FindSatisfiedFieldBossInstance", &Map::LuaFindSatisfiedFieldBossInstance},
	{"AddGameObject",		&Map::LuaAddGameObject},
	{"RemoveWorldObject",	&Map::LuaRemoveObject},
	{"QueryCreature",		&Map::LuaQueryCreature},
	{"GetCreatureEntryCount",		&Map::LuaGetCreatureEntryCount},
	{"AliasCreature",		&Map::LuaAliasCreature},
	{"AliasCreatureTable",	&Map::LuaAliasCreatureTable},
	{"GetCircleTargets",	&Map::LuaGetCircleTargets},
	{"GetCircleTargetsByPos",&Map::LuaGetCircleTargetsByPos},
	{"GetRectTargets",		&Map::LuaGetRectTargets},
	{"GetFanshapedTargets",	&Map::LuaGetFanshapedTargets},
	{"GetObliqueRectTargets",	&Map::LuaGetObliqueRectTargets},
	{"GetPlayer",			&InstanceMap::LuaGetPlayer},
	{"ExitInstance",		&InstanceMap::LuaExitInstance},		//�뿪����

	{"AddTimer",			&Map::LuaAddTimer},
	{"AddTimeStampTimer",   &Map::LuaAddTimeStampTimer},
	{"DelTimer",			&Map::LuaDelTimer},
	{"DelTimeStampTimer",	&Map::LuaDelTimeStampTimer},
	{"RandomPos",			&Map::LuaRandomPos},
	{"GetPlayersCounts",	&Map::LuaGetPlayersCounts},
	{"GetAllPlayer",		&Map::LuaGetAllPlayer},
	{"GetAllCreature",		&Map::LuaGetAllCreature},
	{"GetAllGameObject",	&Map::LuaGetAllGameObject},
	{"GuidToPtr",			&Map::LuaGuidToPtr},
	{"IsCanRun",			&Map::LuaIsCanRun},
	{"IsInMap",				&Map::LuaIsInMap},
	{"ConsLootPoint",		&Map::LuaConsLootPoint},		//����ս��Ʒ����
	{"GetGameOject",		&Map::LuaGetGameOject},		//����ս��Ʒ����
	{"SetCanCastSpell",		&Map::LuaSetCanCastSpell},		//�����Ƿ�����ʩ��
	{"GetCanCastSpell",		&Map::LuaGetCanCastSpell},		//����Ƿ�����ʩ��

	{"SetMapAttrBonus",		&Map::LuaSetMapAttrBonus},		  //���õ�ͼ�ӳ�
	{"SetCanRecovey",		&Map::LuaSetCanRecovey},		  //���õ�ͼ�Ƿ�֧�ֻ�Ѫ
	{"GetCanRecovey",		&Map::LuaGetCanRecovey},		  //��ȡ��ͼ�Ƿ�֧�ֻ�Ѫ
	{"RandConsLootPoint",	&Map::LuaRandConsLootPoint},		//��ȡȫͼ��������
	{"ConsLootPointByPos",	&Map::LuaConsLootPointByPos},		//ͨ��������ȡ����λ��

	{"SetMapSite",			&Map::LuaSetMapSite},			//���õ�ͼ������Ƿ���Ե���
	{"GetRandPosByRadius",	&Map::LuaGetRandPosByRadius},	//��ȡ��뾶����ɵ�����

	{"GetLootObject",		&Map::LuaGetLootObject},	//���������ȡ��Ӧ��ս��Ʒָ��
	{"InsertLootIndex",		&Map::LuaInsertLootIndex},	//��������ս��Ʒλ�ò��뵽�б�
	{"ClearAllLoot",		&Map::LuaClearAllLoot},		//�����ͼ�����е�ս��Ʒ
	{"CreateMapDataHddDirectory",	&Map::LuaCreateMapDataHddDirectory},//������ͼӲ�̴洢�ļ���
	{"IsHaveFile",			&Map::LuaIsHaveFile},//�ж�ĳ�ļ��Ƿ����
	{"GetParentPtr",		&Map::LuaGetParentPtr},//��ȡ������ͼ��Ϣ
	{"ParentGetAllPlayer",	&Map::LuaParentGetAllPlayer},//��ȡϵ�е�ͼ�����������Ϣ
	{"Broadcast",			&Map::LuaBroadcast},		//grid�㲥��
	{"BroadcastMap",		&Map::LuaBroadcastMap},

	{"ClearFieldBossDamage",			&Map::LuaClearFieldBossDamage},		//��������˺�
	{"AddFiledBossDamage",				&Map::LuaAddFiledBossDamage},		//��������˺�
	{"GetMaxinumFieldBossDamage",		&Map::LuaGetMaxinumFieldBossDamage},//�������˺������playerguid

	{"OnOpenTreasure",					&Map::LuaOnOpenTreasure},//�������ڿ��������guid
	{"GetOnOpenGuid",					&Map::LuaGetOnOpenGuid },//������ڿ��������guid

	{"GetCreatureByGuid",				&Map::LuaGetCreatureByGuid},//ͨ��uintguid���creature����

	{"GetGameObjectByGuid",				&Map::LuaGetGameObjectByGuid},//ͨ��uintguid���gameobject����
	{"RemoveGameObjectByEntry",			&Map::LuaRemoveGameObjectByEntry},//ͨ��entryɾ��gameobject����
	{"GetGameObjectByEntry",			&Map::LuaGetGameObjectByEntry},//ͨ��entry���gameobject����
	
	{"GetPlayerByPlayerGuid",			&Map::LuaGetPlayerByPlayerGuid},	//ͨ��playerguid������

	{"GetPlayersAfterCreatureDead",		&Map::LuaGetPlayersAfterCreatureDead},	//Ұ������, ����������������

	{"AddBossDamage",					&Map::LuaAddBossDamage},					//����boss�˺�
	{"GetBossDamageRankCount",			&Map::LuaGetBossDamageRankCount},			
	
	{"ResetBossDamageRank",				&Map::LuaResetBossDamageRank},
	{"GetBossDamageRankPlayerInfo",		&Map::LuaGetBossDamageRankPlayerInfo},
	{"GetBossDamageRank",				&Map::LuaGetBossDamageRank},
	{"NotifyAllRankUpdate",				&Map::LuaNotifyAllRankUpdate},

	{"ShowMassBossRank",				&Map::LuaShowMassBossRank},

	{"AddBossDamage",					&Map::LuaAddBossDamage},					//����boss�˺�
	
	{"SetMassBossHpRate",					&Map::LuaSetMassBossHpRate},
	{"GetMassBossHpRate",					&Map::LuaGetMassBossHpRate},

	{"SetMassBossEnterCount",					&Map::LuaSetMassBossEnterCount},
	{"GetMassBossEnterCount",					&Map::LuaGetMassBossEnterCount},

	{"AddDeadTimes",					&Map::LuaAddDeadTimes},
	{"GetDeadTimes",					&Map::LuaGetDeadTimes},


	{NULL, NULL} /* sentinel */ 
};

extern const struct luaL_reg LUnit[] =
{
	{"GetTarget",			&Unit::LuaGetTarget},			//��ȡ���﹥��Ŀ��
	{"SetTarget",			&Unit::LuaSetTarget},			//�������﹥��Ŀ��
	{"CastSpell",			&Unit::LuaCastSpell},			//�������ͷż���
	{"SpellStop",			&Unit::LuaSpellStop},			//ֹͣ�ͷż���
	{"GetCurSpell",			&Unit::LuaGetCurSpell},			//��õ�ǰ����ʩ�ŵļ���id
	{"SetCurSpell",			&Unit::LuaSetCurSpell},			//���õ�ǰ����ʩ�ŵļ���id
	{"HasUnitState",		&Unit::LuaHasUnitState},		//�Ƿ��б�ʶ,��ʱֻ����ս��
	{"AddUnitState",		&Unit::LuaAddUnitState},		//���ӱ�ʶ,��ʱֻ����ս��
	{"GetPos",				&Unit::LuaGetPos},				//��ȡ����
	{"SetPos",				&Unit::LuaSetPos},				//��������
	{"KillUnit",			&Unit::LuaKillUnit},			//��ɱ����
	{"IsFriendlyTo",		&Unit::LuaIsFriendlyTo},		//�Ƿ��Ѻù�ϵ
	{"InvalidFriendlyCache",&Unit::LuaInvalidFriendlyCache},//�Ѻù�ϵ����ʧЧ
	{"IsCanHit",			&Unit::LuaIsCanHit},			//�Ƿ����
	{"IsActing",			&Unit::LuaIsActing},			//�Ƿ��ڱ���
	{"IsInvincible",		&Unit::LuaIsInvincible},		//�Ƿ��޵�״̬
	{"DelThreat",			&Unit::LuaDelThreat},			//������й���Ը���ҵĳ��,�ӿ����ƿ����޸�
	{"SetActing",			&Unit::LuaSetActing},			//���ñ���״̬
	{"GetMap",				&Unit::LuaGetMap},				//��ȡĿ�����ڵ�ͼ��Ϣ
	{"GetMapID",			&Unit::LuaGetMapID},			//��ȡĿ�����ڵ�ͼID
	{"BlowFly",				&Unit::LuaBlowFly},				//������
	{"Respawn",				&Unit::LuaRespawn},				//����
	{"RandomMove",			&Unit::LuaRandomMove},			//����ƶ�
	{"SetCalculAttr",		&Unit::LuaSetCalculAttr},		//�������û�������
	{"IsMoving",			&Unit::LuaIsMoving},			//�Ƿ��ƶ���
	{"GetMoveSpeed",		&Unit::LuaGetMoveSpeed},		//��ȡ�ƶ��ٶ�
	{"SetMoveSpeed",		&Unit::LuaSetMoveSpeed},		//�����ƶ��ٶ�
	{"GetOrientation",		&Unit::LuaGetOrientation},		//��ȡ���ﳯ��
	{"SetOrientation",		&Unit::LuaSetOrientation},		//�������ﳯ��
	{"StopMoving",			&Unit::LuaStopMoving},			//ֹͣ�ƶ�
	{"MoveTo",				&Unit::LuaMoveTo},				//�ƶ���
	{"GetIntGuid",			&Unit::LuaGetIntGuid},			//���int guid
	
	{"GetMoveEndPos",		&Unit::LuaGetMoveEndPos},		//����ƶ��յ������
	{"IsCanJump",			&Unit::LuaIsCanJump},			//�Ƿ������Ծ
	{"AddSpellTrigger",		&Unit::LuaAddSpellTrigger},		//��Ӽ��ܴ�����
	{"DelSpellTrigger",		&Unit::LuaDelSpellTrigger},		//ɾ�����ܴ�����
	{"SetHealth",			&Unit::LuaSetHealth},			//����Ѫ��
	{"ModifyHealth",		&Unit::LuaModifyHealth},		//�޸�Ѫ��

	{"CallJumpStart",		&Unit::LuaCallJumpStart},			//�㲥��ʼ��Ծ

	{"SetOwner",		&Unit::LuaSetOwner},		//����ӵ���ߣ�����ʱ��Ҫ�ϱ�

	
	{"SystemAddBuff",	&BufferManager::LuaSystemAddBuff},		//ϵͳ���BUFF
	{"AddBuff",			&BufferManager::LuaAddBuff},		//���BUFF
	{"RemoveBuff",		&BufferManager::LuaRemoveBuff},		//�Ƴ�BUFF
	{"HasBuff",			&BufferManager::LuaHasBuff},		//�ж��Ƿ���BUFF
	{"GetBuffLevel",	&BufferManager::LuaGetBuffLevel},	//��ȡBUFF�ĵȼ�
	{"SetBuffLevel",	&BufferManager::LuaSetBuffLevel},	//����buff�ȼ�
	{"GetBuffDuration",	&BufferManager::LuaGetBuffDuration},//��ȡBUFF������ʱ��
	{"SetBuffDuration",	&BufferManager::LuaSetBuffDuration},//����BUFF������ʱ��
	{"GetBuffGiverUnit", &BufferManager::LuaGetBuffGiverUnit},//���buff giver�Ķ���
	{"GetBuffReserve",	&BufferManager::LuaGetReserveVal},	//���buffԤ��ֵ
	{"SetBuffReserve",	&BufferManager::LuaSetReserveVal},	//����buff


	{NULL, NULL} /* sentinel */ 
};

extern const struct luaL_reg LPlayer[] =
{
	{"GetSession",					&Player::LuaGetSession},				//��ȡ�Ự,ͬʱҲ��������������ݶ���
	{"GetEquipAttrs",				&Player::LuaGetEquipAttrs},				//��ȡ��Ҹ���ϵͳ������
	{"AcceptQuest",					&Player::LuaAcceptQuest},				//��������
	{"GetQuestStatus",				&Player::LuaGetQuestStatus},			//��ѯĳ�����״̬
	{"HasQuest",					&Player::LuaHasQuest},					//�Ƿ�������
	{"HasQuestType",				&Player::LuaHasQuestType},				//�Ƿ���ĳ�������͵�����
	{"PrintSlotQuest",				&Player::LuaPrintSlotQuest},			//����������������id(������)
	{"CompleteCurQuest",			&Player::LuaCompleteCurQuest},			//��ɵ�ǰָ�����͵�����
	{"CompleteQuestId",				&Player::LuaCompleteQuestId},			//��ɵ�ǰָ��������
	{"QuestCounter",				&Player::LuaGetQuestCounter},			//ȡ������Ҫ�������
	{"AddQuestItem",				&Player::LuaAddQuestItem},				//����������
	{"RemoveQuestItem",				&Player::LuaRemoveQuestItem},			//�Ƴ�������
	{"ClearQuestSlotItem",			&Player::LuaClearQuestSlotItem},		//���ĳ�����±����
	{"AddQuestItemBySlot",			&Player::LuaAddQuestItemBySlot},		//���������±����
	{"TalkedToCreature",			&Player::LuaTalkedToCreature},			//��NPC�Ի�
	{"AreaExploredOrEventHappens",	&Player::LuaAreaExploredOrEventHappens},//
	{"Teleport",					&Player::LuaTeleport},
	{"GetTeleportID",				&Player::LuaGetTeleportID},				//��ô���id
	
	{"AddItem",						&Player::LuaAddItem},
	{"Upgrade",						&Player::LuaUpgrade},
	{"ClearPets",					&Player::LuaClearPets},
	{"GetCounters",					&Player::LuaGetCounters},
	{"IsInSaveArea",				&Player::LuaIsInSaveArea},//�Ƿ��ڰ�ȫ����
	{"IsCounter",					&Player::LuaIsCounter},	  //�Ƿ��Ƿ���ģʽ	
	{"GetPlayeCurFightStatus",		&Player::LuaGetPlayeCurFightStatus},//��ȡ����Ƿ���ս��״̬
	{"IsLogined",					&Player::LuaIsLogined},	//�Ƿ��Ѿ���¼������
	{"AddExp",						&Player::LuaAddExp},
	{"SubExp",						&Player::LuaSubExp},				//�۾���
	{"SetCoefficient",				&Player::LuaSetCoefficient},
	{"SendAddMoney",				&Player::LuaSendAddMoney},			//֪ͨӦ�÷�����money
	{"SendSubMoney",				&Player::LuaSendSubMoney},			//֪ͨӦ�÷���money������ lhs��
	{"SendRecalculate",				&Player::LuaSendRecalculate},		//֪ͨӦ�÷���������
	{"GetPetTable",					&Player::LuaGetPetTable},			//������ҵĳ����б�
	{"SetCanRecalcuAttr",			&Player::LuaSetCanRecalcuAttr},		//�����������㿪��
	{"GetSpellCD",					&Player::LuaGetSpellCD},		//��ȡ����cd
	{"SetSpellCD",					&Player::LuaSetSpellCD},		//���ü���cd

	{"SetImportanceSpellCD",		&Player::LuaSetImportanceSpellCD},		//������Ҫ����cd
	{"GetSpellLevel",				&Player::LuaGetSpellLevel},		//��ü��ܵȼ�
	{"SetSpellLevel",				&Player::LuaSetSpellLevel},		//���ü��ܵȼ�

	{"GetDaZuoStartTime",				&Player::LuaGetDaZuoStartTime},		//��ô�����ʼʱ��
	{"SetDaZuoStartTime",				&Player::LuaSetDaZuoStartTime},		//���ô�����ʼʱ��

	{"AddGiftPacks",				&Player::LuaAddGiftPacks},		//������
	{"AddWatcher",					&Player::LuaAddWatcher},	//��ӹ۲���
	{"GetSpellStyle",				&Player::LuaGetSpellStyle},		//��ȡ������ʽ
	{"SetSpellStyle",				&Player::LuaSetSpellStyle},		//���ü�����ʽ
	{"GetSlotSpell",				&Player::LuaGetSlotSpell},		//���ĳһ��λ����
	{"SendMountJumpDown",			&Player::LuaSendMountJumpDown},	//��������״̬

	{"LostExpOnDead",			&Player::LuaLostExpOnDead},	//�������侭��
	
	{"SetNeedProtectBuff",			&Player::LuaSetNeedProtectBuff},	//�����Ƿ���Ҫ��������

	{"SendToAppdDoSomething",			&Player::LuaSendToAppdDoSomething},	//���͵����������н����߼��ж�

	{"SendToAppdAddOfflineMail",			&Player::LuaSendToAppdAddOfflineMail},	//���͵����������������ʼ�����

	{"GetAllPlayerNearBy",			&Player::LuaGetAllPlayerNearBy},	//��ø������

	{"GetPlayerGuid",				&Player::LuaGetPlayerGuid},			//���guid

	{"SetPlayerEnterOrigin",	 &Player::LuaSetPlayerEnterOrigin},		//������ҽ����
	

	{NULL, NULL} /* sentinel */ 
};

extern const struct luaL_reg LLog[] = 
{
	{"WriteAttackPacker",		&LuaWriteAttackPacker},						//д��������־
	{"WriteFubenLog",			&LuaWriteFubenLog},							//д������־
	{NULL, NULL} /* sentinel */ 
};

extern const struct luaL_reg LCreature[] =
{
	{"SetMonsterHost",		&Creature::LuaSetMonsterHost},
	{"GetMonsterHost",		&Creature::LuaGetMonsterHost},
	{"SetReactState",		&Creature::LuaSetReactState},
	{"ModifyThreat",		&Creature::LuaModifyThreat},
	{"SetScriptAI",			&Creature::LuaSetScriptAI},
	{"MonsterTalk",			&Creature::LuaMonsterTalk},    
	{"MonsterDeadTalk",		&Creature::LuaMonsterDeadTalk},    //���������԰�
	{"MonsterMove",			&Creature::LuaMonsterMove},
	{"MonsterAddSpell",		&Creature::LuaMonsterAddSpell},	
	{"IsAIFriends",			&Creature::LuaIsAIFriends},			//��ȡAI�е�friendsֵ
	{"ActiveGrid",			&Creature::LuaActiveGrid},			//����grid
	{"SetActionRadius",		&Creature::LuaSetActionRadius},		//���û�뾶
	{"SetVisionRadius",		&Creature::LuaSetVisionRadius},		//���û�뾶
	{"GetOwnShipTable",		&Creature::LuaGetOwnShipTable},		//��ȡ�������б�
	{"ChangeSpellCD",		&Creature::LuaChangeSpellCD},		//�ı�ĳ������cdʱ��
	{"GetLootOwner",		&Creature::LuaGetLootOwner},		//��ǰ�Ϸ�������
	{"RemoveMonster",		&Creature::LuaRemoveMonster},		//�Զ�����
	{NULL, NULL} /* sentinel */ 
};

static const struct luaL_reg mylibname[] = 
{
	{"binLogLib",		luaopen_lib<LBinLog>},
	{"mapLib",			luaopen_lib<LMap>},
	{"unitLib",			luaopen_lib<LUnit>},
	{"playerLib",		luaopen_lib<LPlayer>},
	{"creatureLib",		luaopen_lib<LCreature>},
	{"logLib",			luaopen_lib<LLog>},
	{NULL, NULL} /* sentinel */ 
};

int scripts_init(const char *_sdir)
{
	int status;    
	char sfile[500];

	/*����һ��ָ��Lua��������ָ�롣*/
	gLuaStack = new LuaStack;
	gLuaStack->init();
	L = gLuaStack->getLuaState();

    if(_sdir != NULL)
        sdir = _sdir;

    /*��������Lua��*/
    luaL_openlibs(L);
	//�����������װ�ӿ�
	lua_open_objects_manger(L);
	//��������
	lua_open_packet_binding_init_delegate([](uint32_t cid,packet* pkt)->bool{
		//TODO:���������͸����ķ�������
		WorldPacket wPkt(*pkt);
		ScenedApp::g_app->SendToServerByFd(wPkt,cid);
		return true;
	},[](void* self, packet* pkt)->bool{		
		//TODO:����Ҫ����һ�¹���sessionָ�뼰��̳е�����
		auto *ctx = (ScenedContext*)self;
		ctx->SendPacket(*pkt);
		return true;
	});
	lua_open_packet_binding(L);
	//����http�ӿ�
	luaopen_lua_http_binding(L);

	lua_atpanic(L, &__outError<ScenedApp>);	
	sprintf(sfile,"package.path = package.path .. ';%s/?.lua;'",_sdir,_sdir);
	luaL_dostring(L,sfile);
	sprintf(sfile,"__SCRIPTS_ROOT__='%s'",_sdir);		/*���ű���·��ע���lua��*/
	luaL_dostring(L,sfile);

	sprintf(sfile,"map_data_hdd_path ='%s'", g_Config.map_data_hdd_path.c_str());		/*����ͼӲ�����ݵ�·��ע���lua��*/
	luaL_dostring(L,sfile);

	/////////////////////////////////////////////////////////////////
	//			ע��
	////////////////////////////////////////////////////////////////
	for(const luaL_reg *ptr = mylib;ptr->name != NULL;ptr++)
		lua_register(L,ptr->name,ptr->func);

	for (const luaL_reg * lib = mylibname; lib->func; lib++) {
		lua_pushcfunction(L, lib->func);
		lua_pushstring(L, lib->name);
		lua_call(L, 1, 0);
	}


	/////////////////////////////
    //		  ���ؽű�
    /////////////////////////////

    /*���ؽű�*/    
	sprintf(sfile, "%s/cow_scened.lua", sdir);
	printf("%s\n", sfile);
	if((status = luaL_dofile(L, sfile)))
	{
		tea_perror(" lua error:����ű� %s ����!", sfile);
		tea_perror(" lua error:%s!\n", LUA_TOSTRING(L, -1)); /* ע��printf��Ҫ��ӡ������Ϣ�ˣ���Ϊlua�ĳ�����Ϣ�Ѿ������� */
		lua_pop(L, 1);
		scripts_free();
		ASSERT(0);			//�ű�ʧ�ܣ������ˣ�ֱ�ӹҰ�
		return status;
	}

    DoInitSomethingScript();
	DoInitAllMapScript();
	ASSERT(lua_gettop(L) == 0);//��Ҫ�в���
    return 0;
}

int scripts_free()
{
    /*�ر� �ͷ���Դ*/
	if(gLuaStack != NULL)
	{
		delete gLuaStack;
		gLuaStack = NULL;
		L = NULL;
	}

    return 0;
}

int scripts_reload()
{
    scripts_free();
    scripts_init(g_Config.script_folder.c_str());	
	ScenedApp::g_app->RegSessionOpts();
    return 0;
}

/************************************************************************/
/*								 ������ʼ��								*/
/************************************************************************/
extern int DoInitSomethingScript()
{
	{
		LuaStackAutoPopup autoPopup(L);

		lua_getglobal(L,"config");
		if(!lua_istable(L,-1))
		{
			tea_perror(" lua error:lua�ű����Ҳ���������Ϣ");
			return -1;
		}
		lua_readvalue(L,"external_router_map",			ScenedApp::g_app->m_opts, [](lua_State *scriptL, uint16 &op_code){
			op_code = (uint16)LUA_TOINTEGER(scriptL, -1);
			ASSERT(op_code);
		});
		lua_readvalue(L,"pk_external_router_map",			ScenedApp::g_app->m_pk_opts, [](lua_State *scriptL, uint16 &op_code){
			op_code = (uint16)LUA_TOINTEGER(scriptL, -1);
			ASSERT(op_code);
		});
		lua_readvalue(L,"loot_possibility_range",		LootManager::Loot_possibility_range);	

		lua_readvalue(L,"cant_attack",					g_cant_attack_buff);
		lua_readvalue(L,"cant_cast",					g_cant_cast_buff);
		lua_readvalue(L,"cant_move",					g_cant_move_buff);
		lua_readvalue(L,"cant_recovery",				g_cant_recovery_buff);
		lua_readvalue(L,"cant_jump",					g_cant_jump_buff);
		lua_readvalue(L,"cant_teleport",				g_cant_teleport_buff);
		lua_readvalue(L,"cant_use_item",				g_cant_use_item_buff);
		lua_readvalue(L,"cant_see",						g_cant_see_buff);
		lua_readvalue(L,"invincible",					g_invincible_buff);
		lua_readvalue(L,"cant_fight_with_player",		g_cant_fight_with_player);
		lua_readvalue(L,"cant_attack_be_player",		g_cant_attack_be_player);
		lua_readvalue(L,"ignore_the_obstacles",			g_ignore_the_obstacles);
		lua_readvalue(L,"can_move_dis_map",				g_Config.can_move_dis_map);

		lua_readvalue(L,"max_player_level",				g_Config.max_player_level);
		lua_readvalue(L,"peace_mode_cd",				g_Config.peace_mode_cd);
		lua_readvalue(L,"dead_protect_CD",				g_Config.dead_protect_CD);
		lua_readvalue(L,"nomal_attack_time",			g_Config.nomal_attack_time);
		lua_readvalue(L,"nomal_move_speed",				g_Config.nomal_move_speed);
		lua_readvalue(L,"nomal_attack_distance",		g_Config.nomal_attack_distance);
		lua_readvalue(L,"update_ownership_time",		g_Config.update_ownership_time);
		lua_readvalue(L,"left_fighting_time",			g_Config.left_fighting_time);
		lua_readvalue(L,"heathy_auto_recovery_cycle",	g_Config.heathy_auto_recovery_cycle);
		lua_readvalue(L,"heathy_auto_recovery_percent",	g_Config.heathy_auto_recovery_percent);
		lua_readvalue(L,"energy_auto_recovery_cycle",	g_Config.energy_auto_recovery_cycle);
		lua_readvalue(L,"energy_auto_recovery_values",	g_Config.energy_auto_recovery_values);
		lua_readvalue(L,"endurance_auto_recovery_cycle",g_Config.endurance_auto_recovery_cycle);
		lua_readvalue(L,"endurance_auto_recovery_values",g_Config.endurance_auto_recovery_values);	
		lua_readvalue(L,"jump_cd",						g_Config.jump_cd);
		lua_readvalue(L,"jump_max_distance",			g_Config.jump_max_distance);
		lua_readvalue(L,"jump_need_energy",				g_Config.jump_need_energy);
		lua_readvalue(L,"notice_distance",				g_Config.notice_distance);
		lua_readvalue(L,"loot_area",					g_Config.loot_area);
		lua_readvalue(L,"loot_exist_timer",				g_Config.loot_exist_timer);
		lua_readvalue(L,"loot_change_owner",			g_Config.loot_change_owner);
		lua_readvalue(L,"loot_money_entry",				g_Config.loot_money_entry);
		lua_readvalue(L,"respawn_max_level",			g_Config.respawn_max_level);
		lua_readvalue(L,"sub_weapon_durability",		g_Config.sub_weapon_durability);
		lua_readvalue(L,"sub_other_durability",			g_Config.sub_other_durability);
		lua_readvalue(L,"new_bird_protect_lv",			g_Config.new_bird_protect_lv);
		lua_readvalue(L,"monster_random_radius_percent",g_Config.monster_random_radius_percent);
		lua_readvalue(L,"red_name_time",				g_Config.red_name_time);
		lua_readvalue(L,"safe_distance",				g_Config.safe_distance);	
		lua_readvalue(L,"use_gameobject_diff",			g_Config.use_gameobject_diff);
		lua_readvalue(L,"max_npc_distance",				g_Config.max_npc_distance);
		lua_readvalue(L,"error_distance",				g_Config.error_distance);
	}

	return 0;
}

/************************************************************************/
/*								  ���ܽű�								*/
/************************************************************************/

int DoSpellCastScript(Unit *caster, Unit *target, float dst_x, float dst_y, uint32 spellid, uint32 spell_lv, Unit *unit, const char *data)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "DoSpellCastScript");
    lua_pushlightuserdata(L, caster);			/*ʩ����ָ��*/
	if(target == NULL)
		lua_pushnil(L);						
	else
		lua_pushlightuserdata(L, target);			/*��ʩ����ָ��*/    
    lua_pushnumber(L, dst_x);			/*ʩ��Ŀ������X*/
    lua_pushnumber(L, dst_y);			/*ʩ��Ŀ������Y*/
    lua_pushnumber(L, spellid);			/*����ID*/
    lua_pushnumber(L, spell_lv);		/*���ܵȼ�*/
	if(unit == NULL)
		lua_pushnil(L);						
	else
		lua_pushlightuserdata(L, unit);			/*�����þ���ָ��*/
	if(data == NULL)
		lua_pushnil(L);
	else
		lua_pushstring(L, data);
	if(LUA_PCALL(L, 8, 2, 1)){		
		tea_perror(" lua error:DoSpellCastScript %s, %s,%.02f,%.02f,%u,%u", caster->GetName().c_str(), target?target->GetName().c_str():"", dst_x, dst_y, spellid, spell_lv);
		return 0;
	}
	if(!LUA_TOBOOLEAN(L, -2))
		return 0;
	spellid = (uint32)LUA_TONUMBER(L, -1);

	BinLogObject &info = Map::fighting_info_binlog;
	uint32 count = info.GetUInt32(MAX_FIGHTING_INFO_INT_NOW_INDEX);

	if (count > 0) {
		//�˺��������
		caster->CalSpellCastInfo();
		//�������������״̬�����ó����������а취�޸��˺����
		caster->AfterCalSpellCastInfo();		
		//�����˺����
		Map::BroadcastFightingInfo(caster);
	} else {
		info.SetUInt32(MAX_FIGHTING_INFO_INT_NOW_INDEX, 1);
		info.SetUInt32(MAX_FIGHTING_INFO_INT_START + FIGHTING_INFO_INT_RESERVE_3, caster->GetUIntGuid());	//Ŀ��intguid
		info.SetDouble(MAX_FIGHTING_INFO_INT_START + FIGHTING_INFO_INT_VALUES, 0);	//�˺�
		info.SetUInt32(MAX_FIGHTING_INFO_INT_START + FIGHTING_INFO_INT_HP, caster->GetHealth());	//��ǰѪ��
		info.SetUInt32(MAX_FIGHTING_INFO_INT_START + FIGHTING_INFO_INT_SPELL_ID, spellid);		//����ID

		Map::BroadcastFightingInfo(caster);
	}

	// �������Ѫ��δ����
	if (caster->GetCurrCastVampiric() > 0 && caster->isAlive()) {
		caster->ModifyHealth(caster->GetCurrCastVampiric());
		caster->ClearCurrCastVampiric();
	}

    return 0;
}


bool LoadTemplate()
{
	if(!Load_char_level(L))
		return false;

	if(!Load_skill_base(L))
		return false;

	if(!Load_creature_template(L))
		return false;
	Add_Creature_template_Index();

	if(!Load_item_template(L))
		return false;
	Add_Item_Template_Index();

	if(!Load_buff_template(L))
		return false;	

	if(!Load_quest_template(L))
		return false;
	if(!Load_quest_wo_relation(L))
		return false;

	if(!Load_quest_loot_item(L))
		return false;

	if(!Load_gameobject_template(L))
		return false;

	tea_pinfo("\n\n��ʼ����ڴ����ݿ�����...");
	Add_Quest_Index();
	Add_Telport_Index();
	Add_Quest_Loot_Item_Index();
	Add_instance_material();
	return true;
}

/************************************************************************/
/*								BUFF�����ű�							*/
/************************************************************************/
int DoBuffTriggerScript(Unit *unit, uint16 buff_id, uint32 buffEffectId)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "DoBuffTriggerScript");
    lua_pushlightuserdata(L, unit);			/*BUFF����*/
    lua_pushnumber(L, buff_id);				/*ʩ��Ŀ������X*/
    lua_pushnumber(L, buffEffectId);					/*ʩ��Ŀ������X*/
    if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:DoBuffTriggerScript %s,%u,%u",unit->GetGuid().c_str(),uint32(buff_id),uint32(buffEffectId));
		return 0;
	}
	uint32 count = Map::fighting_info_binlog.GetUInt32(MAX_FIGHTING_INFO_INT_NOW_INDEX);
	if(count != 0)
	{
		uint32 start = MAX_FIGHTING_INFO_INT_START;
		uint32 buff_id = Map::fighting_info_binlog.GetUInt32(start + FIGHTING_INFO_INT_SPELL_ID);
		uint32 giver_guid = unit->GetBuffManager()->GetBuffGiverGuidByID(buff_id);
		Unit* caster = NULL;
		if (unit->GetMap())
			caster = unit->GetMap()->FindUnit(giver_guid);	//һ��Ҫ�ҵ�buff���ͷ��ߣ��Ҳ����ͺ������buff

		tea_perror("=========DoBuffTriggerScript bufferid = %d", buff_id);
		
		if (caster /*&& unit != caster*/ && caster->GetMapId() == unit->GetMapId())
		{
			//�˺��������
			caster->CalSpellCastInfo();	
			//�������������״̬�����ó����������а취�޸��˺����
			caster->AfterCalSpellCastInfo();
			//�����˺����
			Map::BroadcastFightingInfo(caster);
		}
		else
		{
			unit->GetBuffManager()->RemoveBuff((uint16)buff_id);	//�Ҳ���buff�ͷ������Ƴ����buff
			Map::FightingInfoBinlogRest();							//����˺��ṹ
			//Map::fighting_info_binlog.Reset();
		}
	}

    return 0;
}

/************************************************************************/
/*								BUFF�����ű�							*/
/************************************************************************/
int DoBuffOverScript(Unit *unit, uint16 buff_id, uint32 buffEffectId)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "DoBuffOverScript");
    lua_pushlightuserdata(L, unit);			/*BUFF����*/
    lua_pushnumber(L, buff_id);					/*BUFF ID*/
    lua_pushnumber(L, buffEffectId);					/*BUFF ID*/
    if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:DoBuffOverScript %s,%u,%u",unit->GetGuid().c_str(),uint32(buff_id),uint32(buffEffectId));
		return 0;
	}
	
	uint32 count = Map::fighting_info_binlog.GetUInt32(MAX_FIGHTING_INFO_INT_NOW_INDEX);
	if(count != 0)
	{
		tea_perror("=========DoBuffTriggerScript bufferid = %d", buff_id);
		//�˺��������
		unit->CalSpellCastInfo();		
		//�������������״̬�����ó����������а취�޸��˺����
		unit->AfterCalSpellCastInfo();
		//�����˺����
		Map::BroadcastFightingInfo(unit);
	}

    return 0;
}

int GetBuffFrequency(uint32 buffEffectId) {
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "getBuffFrequency");
	lua_pushnumber(L, buffEffectId);					/*BUFF ID*/
	if(LUA_PCALL(L, 1, 1, 0))
	{
		tea_perror(" lua error:GetBuffFrequency %u", uint32(buffEffectId));
		return 0;
	}
	return (uint32)LUA_TONUMBER(L, -1);
}

/************************************************************************/
/*								BUFF�������Խű�							*/
/************************************************************************/
int DOComputeBuffAttr(Unit *unit, uint16 buff_id, uint32 buffEffectId)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "DOComputeBuffAttr");
    lua_pushlightuserdata(L, unit);				/*BUFF����*/
    lua_pushnumber(L, buff_id);					/*BUFF ID*/
    lua_pushnumber(L, buffEffectId);					/*BUFF ID*/
    if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:DOComputeBuffAttr %s,%u,%u",unit->GetGuid().c_str(),uint32(buff_id),uint32(buffEffectId));
		return 0;
	}
	  
	//uint32 count = Map::fighting_info_binlog.GetUInt32(MAX_FIGHTING_INFO_INT_NOW_INDEX);
	//if(count != 0)
	//{
	//	//�˺��������
	//	unit->CalSpellCastInfo();
	//	//�������������״̬�����ó����������а취�޸��˺����
	//	unit->AfterCalSpellCastInfo();
	//	//�����˺����
	//	Map::BroadcastFightingInfo(unit);
	//}

	return 0;
}

int GetFCMBonus(uint32 login_time)
{
    if(login_time == (uint32) - 1 || login_time < 180)
        return 0;
    else if(login_time < 300)
        return -50;
    else
        return -100;
}
//---------------------------------------------------------------------------------------------/
//������Ҿ���ӳ�
extern int DOComputeExpBonusScript(Player *player, Creature *creature, uint32 exp, int percent, double &vip_exp)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "DOComputeExpBonusScript");
    lua_pushlightuserdata(L, player);			/*���*/
	lua_pushlightuserdata(L, creature);
    lua_pushnumber(L, exp);
	int fcm = int(player->GetSession()->GetFCMLoginTime());
	if(fcm == -1)
		fcm = 0;
	lua_pushnumber(L, fcm);	
	lua_pushnumber(L, percent);

    if(LUA_PCALL(L, 5, 2, 0))
	{
		tea_perror(" lua error:DOComputeExpBonusScript %s,%u",player->GetGuid().c_str(),exp);
		return 0;
	}
    int pct = (int)LUA_TONUMBER(L, -2);
	vip_exp = (int)LUA_TONUMBER(L, -1);
    lua_pop(L, 1);
    return pct;
}

//---------------------------------------------------------------------------------------------/
//���һЩ��Ӧ��BUFF
int DoOnlineClearBuff(Player *player)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoOnlineClearBuff");
	lua_pushlightuserdata(L, player);			/*���*/
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror(" lua error:DoOnlineClearBuff %s",player->GetGuid().c_str());
		return 0;
	}
	return 0;
}

//---------------------------------------------------------------------------------------------/
//�������ս��֮��ɵ�ʲô����
int DosometingScript(Player *player)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DosometingScript");
	lua_pushlightuserdata(L, player);			/*���*/
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror(" lua error:DosometingScript %s,%s",player->GetGuid().c_str());
		return 0;
	}
	return 0;
}

//PVP�������
int DOPlayerPvPScript(Player *player,Player* target)
{
	if (player == target)
	{
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DOPlayerPvP");
	lua_pushlightuserdata(L, player);			/*���*/
	lua_pushlightuserdata(L, target);			/*Ŀ��*/
	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:DOPlayerPvPScript %s,%s",player->GetGuid().c_str(),target->GetGuid().c_str());
		return 0;
	}
	return 0;
}

int DOPlayerPvPKilledScript(Player *killer, Player* target) {

	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "OnPVPKilled");
	lua_pushlightuserdata(L, killer);			/*��ɱ��*/
	lua_pushlightuserdata(L, target);			/*Ŀ��*/
	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:DOPlayerPvPScript %s,%s",killer->GetGuid().c_str(),target->GetGuid().c_str());
		return 0;
	}

	return 0;
}

//PVE���﹥�����
int DOPlayerPVEScript(Unit*creature, Player* target)
{
	if (creature == NULL || target == NULL)
	{
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DOPlayerPvE");
	lua_pushlightuserdata(L, creature);			/*���*/
	lua_pushlightuserdata(L, target);			/*Ŀ��*/
	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:DOPlayerPVEScript %s,%s",creature->GetGuid().c_str(),target->GetGuid().c_str());
		return 0;
	}
	return 0;
}
//PVE��ҹ���boss
int DOPlayerPvBScript(Player* player, Unit*creature)
{
	if (creature == NULL || player == NULL)
	{
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoPlayerPVB");
	lua_pushlightuserdata(L, player);			/*���*/
	lua_pushlightuserdata(L, creature);			/*Ŀ��*/
	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:DOPlayerPVEScript %s,%s",player->GetGuid().c_str(),creature->GetGuid().c_str());
		return 0;
	}
	return 0;
}
//ִ�е�ͼ�ű��ĳ�ʼ���¼�
int DoInitMapScript(Map* map)
{
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "OnInitScript");

	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror(" lua error:OnInitScript %u", map->GetMapId());
	}	

	return 0;
}

int DoInitMapWorldObject(Map* map){
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "OnInitWorldObject");

	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror(" lua error:DoInitMapWorldObject %u", map->GetMapId());
	}	

	return 0;
}

//��õ�ͼ�ű�����������ʱ��
int DoGetMapSingleRespawnScript(Map* map, Player* player, uint32& res) {
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "GetSingleRespawnTime");
	lua_pushlightuserdata(L, player);

	if(LUA_PCALL(L, 2, 1, 0)) {
		tea_perror(" lua error:DoGetMapSingleRespawnScript %u", map->GetMapId());
		res = 120;
		return 1;
	}

	res = (uint32)LUA_TONUMBER(L, -1);
	return 0;
}

//ִ�г�ʼ����ͼӲ������
int DoInitReadHddMapData(Map* map)
{
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "ReadDataFromHdd");

	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror(" lua error:OnInitScript %u", map->GetMapId());
	}	

	return 0;
}

//��õ�ͼ��һЩ��ʼֵ
int DoGetInitMapData(Map *map)
{
	if(map->m_state_script.empty())
		return 0;
	
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, map->m_state_script.c_str());

	//��ͼ��ʼ�������һ���Ƿ�ȫͼ�㲥
	int broadcast_nogrid = 0;
	lua_readvalue(L,"broadcast_nogrid",broadcast_nogrid);
	map->m_broadcast_nogrid = broadcast_nogrid != 0;

	//�Ƿ�رճ�ʱ����
	int is_close_respawn = 0;
	lua_readvalue(L,"is_close_respawn",is_close_respawn);	
	map->m_is_close_respawn = is_close_respawn != 0;
	return 0;
}

//ִ�����е�ͼ�ű��ĳ�ʼ���¼�
int DoInitAllMapScript()
{
	for (Map::MapInstances::iterator it = Map::map_instances.begin(); it != Map::map_instances.end(); ++it)
	{
		DoInitMapScript(it->second);
	}
	return 0;
}

//---------------------------------------------------------------------------------------------/
//�Ի������Ӧ����
int DoActivityOperAttrScript(Player *player, uint32 id)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "ActivityOper");
    lua_pushlightuserdata(L, player);    
	lua_pushinteger(L, id);
    if(LUA_PCALL(L, 2, 1, 0))
	{
		tea_perror(" lua error:DoActivityOperAttrScript %s,%u",player->GetGuid().c_str(),id);
		return 0;
	}
    return 0;
}

//��ʱ���ص�����
int DOTimerTickCallBack(Map *map, const char *s_callback, Map::script_instance_var param[10])
{
	ASSERT(!map->m_state_script.empty());
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, s_callback);
	
	uint32 count = 1;
	for (int i = 0; i < 10; i++)
	{
		if(param[i].type == LUA_TNONE)
			break;
		if(param[i].type == LUA_TUSERDATA)
		{
			if(param[i].ptr == NULL)
				lua_pushnil(L);
			else
				lua_pushlightuserdata(L, param[i].ptr);
		}
		else if(param[i].type == LUA_TSTRING)
		{
			lua_pushstring(L, param[i].str);
		}
		else
			lua_pushnumber(L, param[i].l_val);
		count++;
	}
	if(LUA_PCALL(L, count, 1, 0))
	{
		tea_perror(" lua error:DOTimerTickCallBack %u,%s",map->GetMapId(),s_callback);
		return 0;
	}
	return (int)LUA_TOBOOLEAN(L, -1);
}


//���������������飬���ӣ���Ԫ��
int DoQuestRewardScript(Player *player, int32 quest_id, int32 xp,int32 silver,int32 bind_gold, int32 taolue, uint8 all_flag, uint32 special_flag)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoQuestRewardScript");
	lua_pushlightuserdata(L,player);
	lua_pushnumber(L, quest_id);
	lua_pushinteger(L,xp);
	lua_pushinteger(L,silver);
	lua_pushinteger(L,bind_gold);
	lua_pushinteger(L,taolue);
	if(all_flag)
		lua_pushinteger(L, all_flag);
	else
		lua_pushnil(L);
	lua_pushinteger(L, special_flag);
	if(LUA_PCALL(L,8,0,0))
	{
		tea_perror(" lua error:DoQuestRewardScript %s,%u,%u,%u",player->GetGuid().c_str(),xp, silver, bind_gold);
	}
	return 0;
}

/************************************************************************/
/*								ʹ����Ʒ�ű�							*/
/************************************************************************/
int DoUseItemScript(Player *player, uint32 template_id, uint32 count)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "DoUseItemScript");
    lua_pushlightuserdata(L, player);			/*ʹ����Ʒ��*/    
 	lua_pushnumber(L, template_id);				/*��ƷID*/
	lua_pushnumber(L, count);					/*��Ʒ����*/
    if(LUA_PCALL(L, 3, 1, 0))
	{
		tea_perror(" lua error:DoUseItemScript %s,%u",player->GetGuid().c_str(),template_id);
		return 0;
	}
    return LUA_TOBOOLEAN(L, -1);
}

/************************************************************************/
/*									��									*/
/************************************************************************/
extern int DoJumpScript(Unit *player)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoJump");
	lua_pushlightuserdata(L, player);			/*ʹ����Ʒ��*/
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror(" lua error:DoJumpScript ERROR");
		return 0;
	}
	return 0;
}

/***********************************************************************************************************/
/*										����AI�ű� �� ����ѡ��ű�										   */
/***********************************************************************************************************/
int DoSelect_Instance_Script(Map *m)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "Select_Instance_Script");
    lua_pushnumber(L, m->GetMapId());
    if(LUA_PCALL(L, 1, 1, 0))
	{
		tea_perror(" lua error:DoSelect_Instance_Script %u",m->GetMapId());
		return 0;
	}
	lua_readvalue(L, "Name", m->m_state_script);
	return 0;
}

int OnInstanceTryToNextState(Player *player, Map *m, uint16 level, uint32 param)
{
	ASSERT(!m->m_state_script.empty());
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnTryToNextState");
	lua_pushlightuserdata(L, player);
	lua_pushinteger(L, level);
	lua_pushinteger(L, param);
	if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:OnInstanceTryToNextState %u",m->GetMapId());
		return 0;
	}
	return 0;
}

//֪ͨ�����ű�,���򴥷�
int OnNotifyArea(Map *m, Unit *trigger, const char *name, float x,float y)
{
    if(m->m_state_script.empty())
		return 0;
    LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnEnterArea");   
	lua_pushlightuserdata(L, trigger);
	lua_pushstring(L, name);
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    if(LUA_PCALL(L, 5, 1, 0))
	{
		tea_perror(" lua error:OnNotifyArea %u,%.2f,%.2f",m->GetMapId(),x,y);
		return 0;
	}

    return LUA_TOBOOLEAN(L, -1);
}

//֪ͨ�����ű�,��ʱ��ʼ	
int OnMapTimeBegin(Map *m)
{
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnMapBegin");	
	if(LUA_PCALL(L, 1, 1, 0))
	{
		tea_perror(" lua error:OnMapTimeBegin %u",m->GetMapId());
		return 0;
	}

	return LUA_TOBOOLEAN(L, -1);
}

int OnAfterJoinPlayer(Map *m, Player *player)
{
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnAfterJoinPlayer");	
	lua_pushlightuserdata(L, player);
	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:OnAfterJoinPlayer %u,%s",m->GetMapId(),player->GetGuid().c_str());
		return 0;
	}

	return 0;

}

int OnJoinPlayer(Map *m, Player *player)
{
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnJoinPlayer");	
	lua_pushlightuserdata(L, player);
	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:OnJoinPlayer %u,%s",m->GetMapId(),player->GetGuid().c_str());
		return 0;
	}

	return 0;
}

//��ͼ�⻷
int DoMapBuffBonus(Map *m,const Unit *unit)
{
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "DoMapBuffBonus");
	lua_pushlightuserdata(L, (void*)unit);
	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:DoMapBuffBonus %u,%s",m->GetMapId(),unit->GetGuid().c_str());
		return 0;
	}

	return 0;
}

int OnLeavePlayer(Map *m, Player *player)
{
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnLeavePlayer");	
	lua_pushlightuserdata(L, player);
	if(player->GetSession() && player->GetSession()->GetStatus() == STATUS_DELETE)
		lua_pushboolean(L, FALSE);
	else
		lua_pushboolean(L, TRUE);
	if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:OnLeavePlayer %u,%s",m->GetMapId(),player->GetGuid().c_str());
		return 0;
	}

	return 0;
}

int OnPlayerKilled(Player *player, Player *killer,uint32& silver)
{
	silver = 0;
	Map *m = player->GetMap();
	if(m && player->GetMap()->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnPlayerKilled");	
	lua_pushlightuserdata(L, player);
	lua_pushlightuserdata(L, killer);
	if(LUA_PCALL(L, 3, 1, 0))
	{
		tea_perror(" lua error:OnPlayerKilled %s,%s",player->GetGuid().c_str(),killer->GetGuid().c_str());
		return 0;
	}
	silver = (uint32)LUA_TONUMBER(L, -1);

	return 0;
}

int OnPlayerKilledByMonster(Player *player, Unit *killer) {
	Map *m = player->GetMap();
	if(m && player->GetMap()->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnPlayerKilledByMonster");	
	lua_pushlightuserdata(L, player);
	lua_pushlightuserdata(L, killer);

	if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:OnPlayerKilledByMonster %s,%s",player->GetGuid().c_str(),killer->GetGuid().c_str());
		return 0;
	}

	return 0;
}

int OnPlayerHurted(Player *killer, Player *player, double damage) {
	Map *m = player->GetMap();
	if(m && player->GetMap()->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnPlayerHurt");
	lua_pushlightuserdata(L, killer);
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, damage);
	if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:OnPlayerHurted %s,%s", killer->GetGuid().c_str(), player->GetGuid().c_str());
		return 0;
	}
	return 0;
}

int OnPlayerDeath(Player *player) {

	Map *m = player->GetMap();
	if(m && player->GetMap()->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnPlayerDeath");
	lua_pushlightuserdata(L, player);

	if(LUA_PCALL(L, 2, 0, 0)) {
		tea_perror(" lua error:OnPlayerDeath %s",player->GetGuid().c_str());
		return 0;
	}

	return 0;
}

//ʹ����Ϸ����ǰ
int DoBeforUseGameObjectScript(Player *player, GameObject *go, uint32 go_templateid)
{
	Map* m = player->GetMap();
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnBeforeUseGameObject");
	lua_pushlightuserdata(L, player);			/*ʹ��GameObject����*/
	lua_pushlightuserdata(L, go);				/*go����*/
	lua_pushnumber(L, go_templateid);			//ģ��id
	lua_pushnumber(L, go->GetPositionX());		//��Ϸ�����x����
	lua_pushnumber(L, go->GetPositionY());		//��Ϸ�����y����
	if(LUA_PCALL(L, 6, 1, 0))
	{
		tea_perror(" lua error:OnBeforeUseGameObject %u",go_templateid);
		return 0;
	}

	return (int)LUA_TOINTEGER(L, -1);
}

//ʹ����Ϸ����
int DoGameObjectScript(Player *player, GameObject *go, uint32 go_templateid)
{
	Map* m = player->GetMap();
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnUseGameObject");
	lua_pushlightuserdata(L, player);			/*ʹ��GameObject����*/
	lua_pushlightuserdata(L, go);				/*go����*/
	lua_pushnumber(L, go_templateid);			//ģ��id
	lua_pushnumber(L, go->GetPositionX());		//��Ϸ�����x����
	lua_pushnumber(L, go->GetPositionY());		//��Ϸ�����y����
	if(LUA_PCALL(L, 6, 1, 0))
	{
		tea_perror(" lua error:DoGameObjectScript %u",go_templateid);
		return 0;
	}

	return (int)LUA_TOINTEGER(L, -1);
}

int OnPlayerUpgrage(Map *m, Player *player, uint32 prev, uint32 lv)
{
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnPlayerUpgrage");
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, prev);
	lua_pushnumber(L, lv);
	if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:OnPlayerUpgrage ERROR");
		return 0;
	}

	return 0;
}

int DoIsFriendly(Map *m,const Unit *me,const Unit *target) 
{
	if(m->m_state_script.empty())
		return 0;
	if (target->GetEntry() == 5416)
	{
		int a =0;
	}
	
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "DoIsFriendly");
	lua_pushlightuserdata(L, (void*)me);
	lua_pushlightuserdata(L, (void*)target);
	if(LUA_PCALL(L, 3, 1, 0))
	{
		tea_perror(" lua error:OnIsFriendly ERROR");
		return 0;
	}
	int is_frinedly = (int)LUA_TONUMBER(L,-1); 
	return is_frinedly;
}

//����ű�
int DoRespawn(Player *player,Map *m,uint32 respwan_type,uint32 respwan_map,uint16 respwan_x,uint16 respwan_y)
{
	if(m->m_state_script.empty())
		return 0;
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "DoRespawn");
	lua_pushlightuserdata(L, (void*)player);
	lua_pushnumber(L, m->GetMapId());
	lua_pushnumber(L, respwan_map);
	lua_pushnumber(L, respwan_type);
	lua_pushnumber(L, respwan_x);
	lua_pushnumber(L, respwan_y);
	if(LUA_PCALL(L, 7, 0, 0))
	{
		tea_perror(" lua error:DoRespawn ERROR");
		return 0;
	}
	return 0;
}

int DoGMScripts(lua_State *scriptL, Player *player, string &gm_commands)
{
	LuaStackAutoPopup autoPopup(scriptL);
	lua_getglobal(scriptL, "DoGMScripts");
	
	lua_pushlightuserdata(L, player);
	lua_pushstring(scriptL,gm_commands.c_str());
	lua_pushnumber(scriptL, ms_time());
	if(LUA_PCALL(L, 3, 1, 0))
	{
		tea_perror(" lua error:DoGMScripts  ERROR %s",gm_commands.c_str());
		return 0;
	}
	string result_str = LUA_TOSTRING(scriptL,-1);
	return 0;
}

//��������ִ�нű�
int DoAcceptQuest(Map *_m, Player *player, uint32 questid)
{
	if(!_m)
	{
		tea_perror(" lua error:DoAcceptQuest/!_m %s,%u",player->GetGuid().c_str(),questid);
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoAcceptQuest");
	lua_pushlightuserdata(L, _m);			//��ͼ
	lua_pushlightuserdata(L, player);		//���������
	lua_pushnumber(L, questid);				//����ID
	if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:DoAcceptQuest %u,%s,%u", _m->GetMapId(),player->GetGuid().c_str(),questid);
		return 0;
	}
	return 0;
}

//�������ִ�нű�
int DoCompleteQuest(Map *_m, Player *player, uint32 questid)
{
	if(!_m)
	{
		tea_perror(" lua error:DoCompleteQuest/!_m %s,%u",player->GetGuid().c_str(),questid);
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoCompleteQuest");
	lua_pushlightuserdata(L, _m);			//��ͼ
	lua_pushlightuserdata(L, player);		//���������	
	lua_pushnumber(L, questid);				//����ID	
	if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:DoCompleteQuest %u,%s,%u", _m->GetMapId(),player->GetGuid().c_str(),questid);
		return 0;
	}
	return 0;
}

//��ͼ��Ҫ�����ʱҪ������
int DoIsNeedTeleportWhileMapClear(Map *_m, Player *player) {
	if(!_m) {
		tea_perror(" lua error:DoIsTeleportWhileMapClear/!_m %s",player->GetGuid().c_str());
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, _m->m_state_script.c_str(), _m, "IsNeedTeleportWhileMapClear");
	lua_pushlightuserdata(L, player);	//���
	if(LUA_PCALL(L, 2, 1, 0)) {
		tea_perror(" lua error:DoIsTeleportWhileMapClear %u,%s", _m->GetMapId(),player->GetGuid().c_str());
		return 1;
	}
	return (uint32)LUA_TONUMBER(L,-1);
}

int DoIsNeedTeleportToOrigin(Map *_m) {
	if(!_m) {
		tea_perror(" lua error:DoIsNeedTeleportToOrigin/!_m");
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, _m->m_state_script.c_str(), _m, "IsNeedTeleportToOrigin");
	if(LUA_PCALL(L, 1, 1, 0)) {
		tea_perror(" lua error:DoIsNeedTeleportToOrigin %u", _m->GetMapId());
		return 1;
	}
	return LUA_TOBOOLEAN(L,-1) != FALSE;
}


//ʹ��������Ʒ
int DoQuestItemScript(Player *player, uint32 item_templateid)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "Script_Use_QuestItem");
    lua_pushlightuserdata(L, player);			/*ʹ��Item����*/
    lua_pushlightuserdata(L, player->GetMap());			/*������ʹ�õ�*/
    lua_pushnumber(L, item_templateid);
    if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:DoQuestItemScript %u",item_templateid);
		return 0;
	}
    return 0;
}

//ѡ��AI
int DoScriptInit(const char* ainame, Creature *creature)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, ainame);

    if(lua_isnil(L, -1))
    {
        tea_perror(" lua error:script_ai[%s]������", ainame);
        return -1;
    }

    //�ӽű���ȡ���Ѻù���
	lua_readvalue(L,"friends",creature->m_friends_creature);

	//��AI�л�ó���ƶ�����
	lua_readvalue(L,"threat_motion_type",creature->m_threat_move_type);

    //����script_init����
    lua_getfield(L, -1, "script_init");
    lua_remove(L, -2);
    lua_getglobal(L, ainame);
    lua_pushlightuserdata(L, creature);
    if(LUA_PCALL(L, 2, 0,0))
	{
		tea_perror(" lua error:DoScriptInit %s,%s",ainame,creature->GetName().c_str());
		return 0;
	}
    return 0;
}

int DoGossipMessage(const char* ainame, Unit *owner, Player *player, uint32 option_id, string &text, vector<gossip_menu_option_info> &gossip_menu,string &key)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, ainame);
    lua_getfield(L, -1, "GossipMessage");
    lua_remove(L, -2);
    lua_getglobal(L, ainame);
    lua_pushlightuserdata(L, owner);
    lua_pushlightuserdata(L, player);
    lua_pushnumber(L, option_id);
	lua_pushlightuserdata(L, player->GetMap());
	lua_pushstring(L,key.c_str());
    if(LUA_PCALL(L, 6, 3, 0))
	{
		tea_perror(" lua error:DoGossipMessage %s,%s,%s,%u",ainame,owner->GetName().c_str(),player->GetName().c_str(),option_id);
		return 0;
	}

	int n = lua_gettop(L);
	text = LUA_TOSTRING(L, 1); 
	int t_idx = 2;
    lua_pushnil(L);
    //��ѡ��
    uint32 i = 0;
    const int menu_info_members = 3;
    gossip_menu_option_info info;

    while(lua_next(L, t_idx))
    {
        if(i % menu_info_members == 0)
        {
            info.id = (int32)LUA_TONUMBER(L, -1);
        }
        else if(i % menu_info_members == 1)
        {
            info.option_icon = (int32)LUA_TONUMBER(L, -1);
        }
        else
        {
            const char *title = LUA_TOSTRING(L, -1);
			ASSERT(strlen(title)<sizeof(info.option_title)-1);
            //�ű��Լ���ע�ⲻҪ����
            strcpy(&info.option_title[0], title);
            gossip_menu.push_back(info);
        }

        lua_pop(L, 1);
        i++;
    }
	if (!lua_isnil(L, 3) && !(LUA_TOBOOLEAN(L, 3)))
	{//����������Ϊfalse,���·�
		return 0;
	}
	

    return 1;
}


//��ȡ����ս��Ʒ
int DoLootAllot(Player *player, Creature *owner, Unit* unit, int boss_type)
{
    //����ű�Ϊ����ֱ��ʹ�û���(AIBase)�Ļ�ȡ��ʽ
    const char *_ainame = "AI_Base";

    if(strlen(owner->GetAIName()) > 0)
        _ainame = owner->GetAIName();

    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, _ainame);
    lua_getfield(L, -1, "LootAllot");
    lua_remove(L, -2);
    lua_getglobal(L, _ainame);
	lua_pushlightuserdata(L, owner);			/*����*/
	lua_pushlightuserdata(L, player);			/*���*/
	lua_pushlightuserdata(L, unit);				/*��ɱ��*/
	lua_pushnumber(L, player->GetCoefficient().drop_rate_multiples / 100);/*����*/
	lua_pushinteger(L, boss_type);	/*�������ͣ�Ŀǰ���ڼ�������������*/
	lua_pushinteger(L, (int32)player->GetSession()->GetFCMLoginTime());
    if(LUA_PCALL(L, 7, 0, 0))
	{
		tea_perror(" lua error:DoLootAllot %s,%s,%u", player->GetGuid().c_str(), owner->GetName().c_str(), boss_type); 
		return 0;
	}
   
    return 0;
}

int DoMoveInLineOfSight(const char* ainame, Creature *self, Unit *unit)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, ainame);
    lua_getfield(L, -1, "MoveInLineOfSight");
    lua_remove(L, -2);
    lua_getglobal(L, ainame);
    lua_pushlightuserdata(L, self);
    lua_pushlightuserdata(L, unit);
    if(LUA_PCALL(L, 3, 1, 0))
	{
		tea_perror(" lua error:DoMoveInLineOfSight %s,%s,%s", ainame, self->GetTemplate().ainame, unit->GetName().c_str());
		return 0;
	}
    return (int)LUA_TOBOOLEAN(L,-1);
}

int DoDamageTaken(const char* ainame, Creature *self, Unit *unit, double& damage)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, ainame);
    lua_getfield(L, -1, "DamageTaken");
    lua_remove(L, -2);
    lua_getglobal(L, ainame);
    lua_pushlightuserdata(L, self);
    lua_pushlightuserdata(L, unit);
    lua_pushnumber(L, damage);
    if(LUA_PCALL(L, 4, 1, 0))
	{
		tea_perror(" lua error:DoDamageTaken %s,%s,%s,%u", ainame, self->GetTemplate().ainame, unit->GetName().c_str(), damage);
		return 0;
	}
	damage += (double)LUA_TONUMBER(L, -1);
    return 0;
}

int DoDamageDeal(const char* ainame, Creature *self, Unit *unit, double damage)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, ainame);
    lua_getfield(L, -1, "DamageDeal");
    lua_remove(L, -2);
    lua_getglobal(L, ainame);
    lua_pushlightuserdata(L, self);
    lua_pushlightuserdata(L, unit);
    lua_pushnumber(L, damage);
    if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:DoDamageDeal %s,%s,%s,%u", ainame, self->GetTemplate().ainame, unit->GetName().c_str(), damage);
		return 0;
	}
    return 0;
}

int DoGiveDamage(const char* ainame,Creature *self,Unit *unit,double& damage)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, ainame);
	lua_getfield(L, -1, "GiveDamage");
	lua_remove(L, -2);
	lua_getglobal(L, ainame);
	lua_pushlightuserdata(L, self);
	lua_pushlightuserdata(L, unit);
	lua_pushnumber(L, damage);
	if(LUA_PCALL(L, 4, 1, 0))
	{
		tea_perror(" lua error:DoDamageDeal %s,%s,%s,%u", ainame, self->GetTemplate().ainame, unit->GetName().c_str(), damage);
		return 0;
	}
	damage = (double)LUA_TONUMBER(L, -1);
	return 0;
}

int DoKilledUnit(const char* ainame, Creature *self, Unit *victim)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, ainame);
    lua_getfield(L, -1, "KilledUnit");
    lua_remove(L, -2);
    lua_getglobal(L, ainame);
    lua_pushlightuserdata(L, self);
    lua_pushlightuserdata(L, victim);
    if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:DoKilledUnit %s,%s,%s", ainame, self->GetTemplate().ainame, victim->GetName().c_str());
		return 0;
	}
    return 0;
}

int DoJustDied(const char* ainame, Creature *self, Unit *killer,uint32 &deadtime)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, ainame);
    lua_getfield(L, -1, "JustDied");
    lua_remove(L, -2);
    lua_getglobal(L, ainame);
	lua_pushlightuserdata(L, self->GetMap());
    lua_pushlightuserdata(L, self);
    lua_pushlightuserdata(L, killer);
	//lua_call(L, 4,0);
    if(LUA_PCALL(L, 4, 1, 0))
	{
		tea_perror(" lua error:DoJustDied %s,%s,%s", ainame, self->GetTemplate().ainame, killer->GetName().c_str());
		return 0;
	}
	deadtime = (uint32)LUA_TONUMBER(L, -1);
    return 0;
}

int DoSaySomething(const char* ainame, Creature *self)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, ainame);
    lua_getfield(L, -1, "SaySomething");
    lua_remove(L, -2);
    lua_getglobal(L, ainame);
    lua_pushlightuserdata(L, self);
    if(LUA_PCALL(L, 2, 1, 0))
	{
		tea_perror(" lua error:DoSaySomething %s,%s",ainame, self->GetTemplate().ainame);
		return 0;
	}
    return (int)LUA_TONUMBER(L, -1);
}

//�ж��ܷ���
bool DoCheckTeleport(Player *player, uint32 entry, uint16 posX, uint16 posY)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "Script_Teleport_Check");
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, entry);
	lua_pushnumber(L, posX);
	lua_pushnumber(L, posY);
	if(LUA_PCALL(L, 4, 1, 0))
	{
		tea_perror(" lua error:DoCheckTeleport %s, %d, %d", player->GetGuid().c_str(), posX, posY);
		return 0;
	}
	return LUA_TOBOOLEAN(L, -1) != FALSE;
}

int DOWorldMapTeleportScript(Player *player, uint32 map_id, float pos_x, float pos_y)
{
    LuaStackAutoPopup autoPopup(L);
    lua_getglobal(L, "Script_WorldMap_Teleport");
    lua_pushlightuserdata(L, player);
    lua_pushnumber(L, map_id);
    lua_pushnumber(L, pos_x);
    lua_pushnumber(L, pos_y);
    if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:DOWorldMapTeleportScript %s,%u,%.2f,%.2f", player->GetGuid().c_str(), map_id, pos_x, pos_y);
		return 0;
	}
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
//�ű�����

//lua����������Ϣ
int LuaCallChat(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	if(n < 3)
	{
		tea_perror(" lua error:LuaCallChat ��������");
		return 0;
	}

	uint8 type		= (uint8)LUA_TOINTEGER(scriptL, 1);	
	string guid		= LUA_TOSTRING(scriptL, 2);
	string content	= LUA_TOSTRING(scriptL, 3);
	string sendname = "";
	if(n > 3)
		sendname	= LUA_TOSTRING(scriptL, 4);
	uint8 faction	= 0;
	if(n > 4)
		faction		= (uint8)LUA_TOINTEGER(scriptL, 5);
	string to_guid	= "";
	if(n > 5)
		to_guid		= LUA_TOSTRING(scriptL, 6);
	
	WorldPacket pkt (INTERNAL_OPT_CHAT);	
	pkt << type;
	pkt << guid;
	pkt << content;
	pkt << sendname;
	pkt << faction;
	pkt << to_guid;
	ScenedApp::g_app->SendToAppd(pkt);
	return 0;
}

//ȡ��ս����Ϣbinlog
int LuaGetFightingInfo(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	if(n == 0)
	{
		lua_pushlightuserdata(scriptL, &Map::fighting_info_binlog);
		return 1;
	}
	return 0;
}

//�ƶ�֮ǰ��Ҫ���õ��߼�
bool OnMoveTo(Map *m, Player *player)
{
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnMoveTo");
	lua_pushlightuserdata(L, player);
	if(LUA_PCALL(L, 2, 1, 0))
	{
		tea_perror(" lua error:OnMoveTo ERROR ERROR map_id = %u player_id = %s", m->GetMapId(), player->GetGuid().c_str());
	}
	
	return LUA_TOBOOLEAN(L, -1) != FALSE;
}

//Ҫ��ʼ����֮ǰ���õ��߼�
bool OnStartAttack(Map *m, Player *player)
{
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, m->m_state_script.c_str(), m, "OnStartAttack");	
	lua_pushlightuserdata(L, player);
	if(LUA_PCALL(L, 2, 1, 0))
	{
		tea_perror(" lua error:OnStartAttack ERROR map_id = %u player_id = %s", m->GetMapId(), player->GetGuid().c_str());
	}

	return LUA_TOBOOLEAN(L, -1) != FALSE;
}

//GM�����KEYת��
int GetGmCommandKey(string &gm_str)
{
	//lua_State *L = itemL;
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "GetGmCommandKey");
	lua_pushstring(L, gm_str.c_str());		
	if(LUA_PCALL(L, 1, 1, 0))
	{
		tea_perror(" lua error:DoWingsBonus  ERROR");
		return 0;
	}
	return (int)LUA_TONUMBER(L,-1);
}

//��������
int DoRecalculationAttrs(Player *player, bool bRecal)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoRecalculationAttrs");
	lua_pushlightuserdata(L, player->GetEquipAttrs());
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, ms_time());
	lua_pushboolean(L, bRecal);
	if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:DoRecalculationAttrs ERROR player guid =  %s",  player->GetGuid().c_str());
	}
	return 0;
}

int DoGetCharDiffHp(uint32 prev, uint32 curr, int32& diff) {
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "CalLevelUpRaisedHp");
	lua_pushnumber(L, prev);
	lua_pushnumber(L, curr);
	if(LUA_PCALL(L, 2, 1, 0))
	{
		tea_perror(" lua error:DoGetCharDiffHp ERROR");
	}

	diff = (int32)LUA_TONUMBER(L, -1);
	return 0;
}

//������ȼ���ʼ��������Ϣ
int DoInitCreatureInfo(Creature *creature, Map *map, bool bRecal)
{
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "InitCreatureInfo");
	lua_pushlightuserdata(L, creature);
	lua_pushboolean(L, bRecal);
	if(LUA_PCALL(L, 3, 0, 0))
	{
		//�ǲ���Ӧ�ñ���
		tea_perror(" lua error:DoInitCreatureInfo ERROR ");
	}
	return 0;
}

int DoTestData(Player *player, string& str)
{
	Map* map = player->GetMap();
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "OnTest");
	lua_pushlightuserdata(L, player);
	lua_pushstring(L, str.c_str());
	if(LUA_PCALL(L, 3, 0, 0))
	{
		//�ǲ���Ӧ�ñ���
		tea_perror(" lua error:DoTestData ERROR ");
	}
	return 0;
}

bool DoCheckIfSendToAppdAfterLootSelect(Player *player, uint32 entry, uint32 count)
{
	Map* map = player->GetMap();
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "OnCheckIfSendToAppdAfterLootSelect");
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, entry);
	lua_pushnumber(L, count);
	if(LUA_PCALL(L, 4, 1, 0))
	{
		//�ǲ���Ӧ�ñ���
		tea_perror(" lua error:DoCheckIfNoSendToAppdAfterLootSelect ERROR ");
	}

	return LUA_TONUMBER(L, -1) == TRUE;
}

int creatureInit(Creature *creature) {
	int entry = creature->GetEntry();
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "creatureInit");
	lua_pushlightuserdata(L, creature);
	lua_pushinteger(L, entry);

	if(LUA_PCALL(L, 2, 0, 0)) {
		tea_perror(" lua error:creatureInit ERROR ");
		return -1;
	}

	return 0;
}

//��������˳���ͼǰ��
int DoPlayerExitInstance(Map* map, Player* player, uint32 reserve)
{
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "DoPlayerExitInstance");
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, reserve);
	if(LUA_PCALL(L, 3, 1, 0))
	{
		tea_perror(" lua error:DoPlayerExitInstance mapid = %u, playerid = %s", map->GetMapId(), player->GetGuid().c_str());
	}		

	return (int)LUA_TOINTEGER(L, -1);
}

int SpecifyTeleportOrigin(Map* map, Player* player) {
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "OnSpecifyTeleportOrigin");
	lua_pushlightuserdata(L, player);
	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:SpecifyTeleportDest mapid = %u, playerid = %s", map->GetMapId(), player->GetGuid().c_str());
	}

	return 1;
}

//�������pkģʽǰ�Ļص�
int DoSetAttackModeCallback(Map* map, Player* player, uint8 mode)
{
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "DoSetAttackModeCallback");
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, mode);

	if(LUA_PCALL(L, 3, 1, 0))
	{
		tea_perror(" lua error:DoSetAttackModeCallback mapid = %u, playerid = %s", map->GetMapId(), player->GetGuid().c_str());
	}		

	return (int)LUA_TOINTEGER(L, -1);
}

//�����ɵ�ɶ
int DoAfterRespawn(Map* map, Unit* respawner)
{
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "DoAfterRespawn");
	lua_pushlightuserdata(L, respawner);

	if(LUA_PCALL(L, 2, 1, 0))
	{
		tea_perror(" lua error:DoAfterRespawn mapid = %u, respawner = %s", map->GetMapId(), respawner->GetGuid().c_str());
	}		

	return 0;
}

//���븱��ǰ���ж�
int DoInstancEnter(Map* map, Player* player, uint32 cur_mapid, uint32 to_mapid)
{
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "DoInstancEnter");
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, cur_mapid);
	lua_pushnumber(L, to_mapid);

	if(LUA_PCALL(L, 4, 1, 0))
	{
		tea_perror(" lua error:DoAfterRespawn mapid = %u, playerid = %s", map->GetMapId(), player->GetGuid().c_str());
	}		

	return (int)LUA_TOBOOLEAN(L,-1);
}

//��ù���Ļ�������
int DoGetCreatureBaseExp(Unit* creature, Unit* owner)
{
	if (creature == NULL || owner == NULL)
	{
		return 0;
	}

	Map* map = creature->GetMap();
	if(map->m_state_script.empty())
		return 0;

	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, map->m_state_script.c_str(), map, "DoGetCreatureBaseExp");
	lua_pushlightuserdata(L, creature);			
	lua_pushlightuserdata(L, owner);
	if(LUA_PCALL(L, 3, 1, 0))
	{
		tea_perror(" lua error:DoGetCreatureBaseExp %s",owner->GetGuid().c_str());
		return 0;
	}
	
	return (int)LUA_TONUMBER(L, -1);
}

//�ж�ĳ�������Ƿ�
int DoIsEnoughConsumptionCast(Player *player, uint32 spell_id)
{
	if (player == NULL)
	{
		tea_perror(" lua error:DoIsEnoughConsumptionCast: player == null");
		return false;
	}
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, "UnitInfo", player, "IsEnoughConsumption");
	lua_pushnumber(L, spell_id);
	
	if(LUA_PCALL(L, 2, 1, 0))
	{
		tea_perror(" lua error:IsEnoughConsumption player guid: %s", player->GetGuid().c_str());
		return false;
	}

	return (int)LUA_TOBOOLEAN(L, -1);
}

//����ĳ�����ܵ�����
int DoSpellConsumption(Player *player, uint32 spell_id)
{
	if (player == NULL)
	{
		tea_perror(" lua error:DoSpellConsumption: player == null");
		return false;
	}
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, "UnitInfo", player, "SpellConsumption");
	lua_pushnumber(L, spell_id);

	if(LUA_PCALL(L, 2, 1, 0))
	{
		tea_perror(" lua error:DoSpellConsumption player guid: %s", player->GetGuid().c_str());
		return false;
	}

	return (int)LUA_TOBOOLEAN(L, -1);
}

int DoPickRiskReward(Player *player) {

	if (!player) {
		tea_perror(" lua error:DoPickRiskReward: player == null");
		return false;
	}
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, "UnitInfo", player, "onPickRiskReward");
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror(" lua error:DoPickRiskReward player guid: %s", player->GetGuid().c_str());
		return false;
	}

	return 0;
}

//���ü���cd
int DoSetSpellCD(Player* player, uint32 spell_id)
{
	if (player == NULL)
	{
		tea_perror(" lua error:DoSetSpellCD: player == null");
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	NewLuaTable(L, "UnitInfo", player, "SetSpellCD");
	lua_pushnumber(L, spell_id);
	lua_pushnumber(L, ms_time());

	if(LUA_PCALL(L, 3, 0, 0))
	{
		tea_perror(" lua error:DoSetSpellCD player guid: %s", player->GetGuid().c_str());
		return false;
	}

	return 0;
}

//��lua�жϿ�ʼʩ��ǰ���߼�,Ŀǰ���ﲻ������߼�
bool DoHandleSpellStart(Player* player, uint32 spell_slot, uint16 tar_x, uint16 tar_y, Unit* target, uint32 &spellId)
{
	if (player == NULL)
	{
		tea_perror(" lua error:DoHandleSpellStart: player == null");
		return false;
	}
	if (!player->GetMap())
	{
		tea_perror(" lua error:DoHandleSpellStart: player->GetMap() == null");
		return false;
	}
	
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoHandleSpellStart");
	lua_pushlightuserdata(L, player);
	lua_pushlightuserdata(L, player->GetMap());	
	lua_pushnumber(L, spell_slot);
	lua_pushnumber(L, tar_x);
	lua_pushnumber(L, tar_y);

	if(target == NULL)
		lua_pushnil(L);						
	else
		lua_pushlightuserdata(L, target);			/*��ʩ����ָ��*/
	lua_pushnumber(L, ms_time());

	if(LUA_PCALL(L, 7, 2, 0))
	{
		tea_perror(" lua error:DoHandleSpellStart player:%s", player->GetGuid().c_str());
		return false;
	}

	bool available = LUA_TOBOOLEAN(L, -2) ? true:false;
	if (available) {
		spellId = (uint32)LUA_TONUMBER(L, -1);
	}
	return available;
}

int DoHandlePassiveEffect(Unit* caster_ptr, Unit* target_ptr, uint32 dispatchType) {

	if (caster_ptr == NULL) {
		tea_perror(" lua error:DoHandlePassiveEffect: caster_ptr == null");
		return false;
	}

	if (target_ptr == NULL) {
		tea_perror(" lua error:DoHandlePassiveEffect: target_ptr == null");
		return false;
	}

	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "OnPassiveEffect");
	lua_pushlightuserdata(L, caster_ptr);
	lua_pushlightuserdata(L, target_ptr);	
	lua_pushnil(L);
	lua_pushnumber(L, dispatchType);

	if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:DoHandlePassiveEffect caster_ptr:%s", caster_ptr->GetGuid().c_str());
		return false;
	}

	return 0;
}

int DoOnHpChanged(Unit* caster_ptr, uint32 prev) {
	if (caster_ptr == NULL) {
		tea_perror(" lua error:DoOnHpChanged: caster_ptr == null");
		return false;
	}

	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "OnHpChanged");
	lua_pushlightuserdata(L, caster_ptr);
	lua_pushnumber(L, prev);

	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:DoOnHpChanged caster_ptr:%s", caster_ptr->GetGuid().c_str());
		return false;
	}

	return 0;
}

int DoHandlePickGameObject(Player* player, uint32 gameObjectId) {
	
	if (player == NULL) {
		tea_perror(" lua error:DoHandlePickGameObject: player == null");
		return false;
	}

	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoHandlePickGameObject");
	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, gameObjectId);

	if(LUA_PCALL(L, 2, 0, 0))
	{
		tea_perror(" lua error:DoHandlePickGameObject player:%s", player->GetGuid().c_str());
		return false;
	}

	return 0;
}

//Ӧ�÷�֪ͨ����������Ԫ����ͭǮ��Щʲô
int DoScenedComsumeMoney(Player *player, uint8 money_type, uint8 use_type,const string &param)
{
	if (!player)
	{
		tea_perror(" lua error:DoScenedComsumeMoney player == null");
		return 0;
	}
	
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoScenedComsumeMoney");

	lua_pushlightuserdata(L, player);
	lua_pushnumber(L, money_type);
	lua_pushnumber(L, use_type);
	lua_pushstring(L, param.c_str());

	if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:DoScenedComsumeMoney  plyaerguid = %s  use_type = %u ",player->GetGuid().c_str(), use_type);
		return 0;
	}
	return 0;
}

//������(�����־λ)
int LuaHasFlag(lua_State* scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n >= 2);
	uint32 flags = (uint32)LUA_TONUMBER(scriptL, 1);
	uint32 index = (uint32)LUA_TONUMBER(scriptL, 2);
	lua_pushboolean(scriptL, (flags & index));
	return 1;
}

//��ȡ����������ʱ��
int LuaGetMsTime(lua_State *scriptL)
{	
	lua_pushnumber(scriptL, ms_time());
	return 1;
}

//�ű��ͷż���
int LuaDoSpellCastScript(lua_State *scriptL)
{
	CHECK_LUA_NIL_PARAMETER(scriptL);
	int n = lua_gettop(scriptL);
	ASSERT(n==7);
	Unit *caster = (Unit *)LUA_TOUSERDATA(scriptL, 1, ObjectTypeUnit);
	if(!caster && !caster->GetMap())
	{
		tea_perror("LuaDoSpellCastScript caster is nil ");
		return 0;
	}
	const char* target_guid = LUA_TOSTRING(scriptL, 2);
	Unit *target = NULL;
	if(target_guid)
		target = caster->GetMap()->FindUnit(shortGUID(target_guid));
	float dst_x = (float)LUA_TONUMBER(scriptL, 3);
	float dst_y = (float)LUA_TONUMBER(scriptL, 4);
	uint32 spell_id = (uint32)LUA_TOINTEGER(scriptL, 5);
	uint32 spell_lv = (uint32)LUA_TOINTEGER(scriptL, 6);
	string data = (string)LUA_TOSTRING(scriptL, 7);

	DoSpellCastScript(caster, target, dst_x, dst_y, spell_id, spell_lv, caster, data.c_str());
	return 1;
}

//���ݵ�ͼid�ж����ڵ�ͼ�Ƿ�Ϊ�����ͼ
bool DoIsKuafuMapID(uint32 map_id)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "IsKuafuMapID");
	lua_pushnumber(L, map_id);
	if(LUA_PCALL(L, 1, 1, 0))
	{
		tea_perror("lua_error: DoIsKuafuMapID  ERROR!!!");
		return false;
	}

	return LUA_TOBOOLEAN(L,-1) == TRUE;
}


//��ȡ���Ǹ����
int DoGetRespawnPos(vector<uint16> &v)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "GetRespawnPos");    //table��ջ

	if(LUA_PCALL(L, 0, 1, 0))
	{
		tea_perror("lua_error: GetRespawnPos  ERROR!!!");
		return 0;
	}
	int i = lua_gettop(L);
	lua_pushnil(L);          
	//�������table
	while(lua_next(L, i))
	{
		v.push_back((uint16)LUA_TOINTEGER(L, -1));
		lua_pop(L, 1);		
	}
	return 0;
}



//��Ҵ���
int DoPlayerTeleport(Player* player)
{
	if (player == NULL)
	{
		return 0;
	}
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoPlayerTeleport");
	lua_pushlightuserdata(L, player);			/*���*/
	if(LUA_PCALL(L, 1, 0, 0))
	{
		tea_perror(" lua error:DOPlayerTeleport %s",player->GetGuid().c_str());
		return 0;
	}
	return 0;
}

int DoScenedDoSomething(Player *player, uint32 type, uint32 data, string str) {

	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "DoScenedDoSomething");
	if (player) {
		lua_pushlightuserdata(L, player);			/*���*/
	} else {
		lua_pushnil(L);
	}
	lua_pushnumber(L, type);
	lua_pushnumber(L, data);
	lua_pushstring(L, str.c_str());

	if(LUA_PCALL(L, 4, 0, 0))
	{
		tea_perror(" lua error:DoScenedDoSomething %s",player->GetGuid().c_str());
		return 0;
	}

	return 0;
}

//���ݵ�ͼid�ж����ڵ�ͼ�Ƿ�Ϊ�����ͼ
bool DoIsWorldMapID(uint32 map_id)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "IsWorldMap");
	lua_pushnumber(L, map_id);
	if(LUA_PCALL(L, 1, 1, 0))
	{
		tea_perror("lua_error: IsWorldMap  ERROR!!!");
		return false;
	}
	return LUA_TOBOOLEAN(L,-1) == TRUE;
}

//�ж�item_entry�ǲ�����Դ, ����� money_type ��Ϊuint32(-1)
bool DoGetMoneyType(uint32 item_entry, uint32 &money_type) {
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "GetMoneyType");
	lua_pushnumber(L, item_entry);
	if(LUA_PCALL(L, 1, 1, 0))
	{
		tea_perror("lua_error: DoGetMoneyType  ERROR!!!");
		return false;
	}
	int type = (int32)LUA_TONUMBER(L, -1);
	bool ret = false;
	if (type >= 0) {
		money_type = type;
		ret = true;
	}

	return ret;
}

int DoIsRiskMap(uint32 mapid) {
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "isRiskMap");
	lua_pushnumber(L, mapid);

	if(LUA_PCALL(L, 1, 1, 0)) {
		tea_perror(" lua error:DoIsRiskMap %u", mapid);
		return 0;
	}

	return (int)LUA_TONUMBER(L, -1);
}

int DoIsMassBossMap(uint32 mapid) {
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "isMassBossMap");
	lua_pushnumber(L, mapid);

	if(LUA_PCALL(L, 1, 1, 0)) {
		tea_perror(" lua error:DoIsMassBossMap %u", mapid);
		return 0;
	}

	return (int)LUA_TONUMBER(L, -1);
}

bool isMapTimeLimit(uint32 mapid) {

	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "isMapTimeLimit");
	lua_pushnumber(L, mapid);

	if(LUA_PCALL(L, 1, 1, 0)) {
		tea_perror(" lua error:isMapTimeLimit %u", mapid);
		return 0;
	}

	return (BOOL)LUA_TOBOOLEAN(L, -1) == TRUE;
}

// ���ð�յ�ͼ�Ĵ�����Ϣ
int DoScenedGetRiskTeleportInfo(Player* player, int &mapid, float &x, float &y, string &generalId) {
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "ScenedGetRiskTeleportInfo");
	lua_pushlightuserdata(L, player);

	if(LUA_PCALL(L, 1, 4, 0)) {
		tea_perror(" lua error:DoScenedGetRiskTeleportInfo %s", player->GetSession()->GetGuid().c_str());
		return 1;
	}

	generalId = (string)LUA_TOSTRING(L, -1);
	y = (float)LUA_TONUMBER(L, -2);
	x = (float)LUA_TONUMBER(L, -3);
	mapid = (int)LUA_TONUMBER(L, -4);

	return 0;
}

void DoTerminalContinuousAction(Unit* unit)
{
	if (!unit || unit->GetTypeId() != TYPEID_PLAYER) {
		return;
	}

	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "terminalContinuousAction");
	lua_pushlightuserdata(L, unit);

	if(LUA_PCALL(L, 1, 0, 0)) {
		tea_perror(" lua error:OnPlayerAfterMove %u", unit->GetMap()->GetMapId());
	}
}