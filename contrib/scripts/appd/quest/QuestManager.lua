QUEST_UPDATE_CALLBACK = {
	[QUEST_TARGET_TYPE_PLAYER_LEVEL] 		= IQuestPlayerLevel,
	[QUEST_TARGET_TYPE_PLAYER_FORCE] 		= IQuestPlayerForce,
	[QUEST_TARGET_TYPE_FACTION] 			= IQuestJoinFaction,
	[QUEST_TARGET_TYPE_FACTION_DONATION] 	= IQuestFactionDonate,
	[QUEST_TARGET_TYPE_FACTION_ACTIVITY] 	= IQuestJoinFactionActivity,
	[QUEST_TARGET_TYPE_FIELD_BOSS] 			= IQuestJoinFieldBoss,
	[QUEST_TARGET_TYPE_WORLD_BOSS] 			= IQuestJoinWorldBoss,
	[QUEST_TARGET_TYPE_RESOURCE_INSTANCE] 	= IQuestJoinResourceInstance,
	[QUEST_TARGET_TYPE_TRIAL_INSTANCE] 		= IQuestJoinTrialInstance,
	[QUEST_TARGET_TYPE_OWN_DIVINE] 			= IQuestOwnDivine,
	[QUEST_TARGET_TYPE_EQUIP_DIVINE] 		= IQuestEquipDivine,
	[QUEST_TARGET_TYPE_STRENGTH_DIVINE] 	= IQuestStrengthDivine,
	[QUEST_TARGET_TYPE_RAISE_SKILL] 		= IQuestRaiseSkill,
	[QUEST_TARGET_TYPE_TRAIN_MOUNT] 		= IQuestTrainMount,
	[QUEST_TARGET_TYPE_RAISE_MOUNT_SKILL] 	= IQuestRaiseMountSkill,
	[QUEST_TARGET_TYPE_FRIEND_DONATION] 	= IQuestFriendDonate,
	[QUEST_TARGET_TYPE_STRENGTH_SUIT]		= IQuestStrengthSuit,
	[QUEST_TARGET_TYPE_STRENGTH_GEM] 		= IQuestRaiseGem,
	[QUEST_TARGET_TYPE_TALK] 				= IQuestNPCTalk,
	[QUEST_TARGET_TYPE_PICK_GAME_OBJECT] 	= IQuestPick,
	[QUEST_TARGET_TYPE_CHECK_GAME_OBJECT] 	= IQuestInspect,
	[QUEST_TARGET_TYPE_KILL_MONSTER] 		= IQuestKillMonster,
	[QUEST_TARGET_TYPE_USE_ITEM] 			= IQuestUseItem,
	[QUEST_TARGET_TYPE_SUIT]				= IQuestSuit,
	[QUEST_TARGET_TYPE_MOUNT_LEVEL]			= IQuestMountUpgrade,
	[QUEST_TARGET_TYPE_DOUJIANTAI]			= IQuestDoujiantaiWin,
	[QUEST_TARGET_TYPE_ACHIEVE]				= IQuestAchieve,
	[QUEST_TARGET_TYPE_SUIT_TITLE]			= IQuestSuitTitle,
	[QUEST_TARGET_TYPE_SUIT_FASHION]		= IQuestSuitFashion,
	[QUEST_TARGET_TYPE_JOIN_DOUJIANTAI]		= IQuestJoinDoujiantai,
	[QUEST_TARGET_TYPE_JOIN_KUAFU_3V3]		= IQuestJoinWorld3V3,
	[QUEST_TARGET_TYPE_WIN_KUAFU_3V3]		= IQuestWorld3v3Win,
	[QUEST_TARGET_TYPE_JOIN_XIANFU]			= IQuestJoinXianfu,
	[QUEST_TARGET_TYPE_KILL_MONSTER_COLLECT]= IQuestKillMonsterCollect,
	[QUEST_TARGET_TYPE_TURN_ITEM_IN]		= IQuestTurnItemIn,
	
	[QUEST_TARGET_TYPE_PASS_WORLD_RISK]			= IQuestWorldRisk,
	[QUEST_TARGET_TYPE_SMELT]					= IQuestSmelt,
	[QUEST_TARGET_TYPE_CONTRIBUTE_TIMES]		= IQuestContributeTimes,
	[QUEST_TARGET_TYPE_CONTRIBUTE_TOTAL_TIMES]	= IQuestContributeTotalTimes,
	[QUEST_TARGET_TYPE_CONTRIBUTE_CHARM]		= IQuestContributeCharm,
	[QUEST_TARGET_TYPE_CONTRIBUTE_ITEM]			= IQuestContributeItem,
	[QUEST_TARGET_TYPE_LOOT_ITEM]				= IQuestLootItem,
	
	[QUEST_TARGET_TYPE_SINGLE_THX_TIMES]		= IQuestSingleThxTimes,
	[QUEST_TARGET_TYPE_TOTAL_THX_TIMES]			= IQuestTotalThxTimes,
	[QUEST_TARGET_TYPE_WINGS_UPGRADE_LEVEL]		= IQuestWingsUpgrade,
	[QUEST_TARGET_TYPE_WINGS_UPDRADE_TIMES]		= IQuestWingsUpgradeTimes,
	[QUEST_TARGET_TYPE_WINGS_STRENGTH_LEVEL]	= IQuestWingsStrengthLevel,
	[QUEST_TARGET_TYPE_WINGS_STRENGTH_TIMES] 	= IQuestWingsStrengthTimes,
	[QUEST_TARGET_TYPE_TALISMAN_LEVEL]			= IQuestTalismanLevel,
	[QUEST_TARGET_TYPE_MOUNT_STRENGTH_LEVEL]	= IQuestMountStrengthLevel,
	[QUEST_TARGET_TYPE_REFINE_SUIT]				= IQuestRefineSuit,
	[QUEST_TARGET_TYPE_WASH_SUIT]				= IQuestWashSuit,
	[QUEST_TARGET_TYPE_MERIDIAN_LEVEL]			= IQuestMeridianLevel,
	[QUEST_TARGET_TYPE_JOIN_SINGLE_PVP]			= IQuestJoinQualify,
	[QUEST_TARGET_TYPE_SINGLE_PVP_WINS]			= IQuestQualifyWin,
	[QUEST_TARGET_TYPE_ACTIVE_TASK]				= IQuestActiveTask,
	[QUEST_TARGET_TYPE_DAILY_TASK]				= IQuestDailyTask,
	[QUEST_TARGET_TYPE_GEM_TOTAL_LEVEL]			= IQuestGemTotalLevel,
	[QUEST_TARGET_TYPE_WINGS_BLESS_TIMES]		= IQuestWingsBlessTimes,
	[QUEST_TARGET_TYPE_MONEYTREE_TIMES]			= IQuestMoneytreeTimes,
	[QUEST_TARGET_TYPE_JOIN_MASS_BOSS_TIMES]	= IQuestJoinMassBossTimes,
	[QUEST_TARGET_TYPE_MAIN_SKILL_UPGRADE_LEVEL]	= IQuestMainSkillUpgradeLevel,
	[QUEST_TARGET_TYPE_SUB_SKILL_UPGRADE_LEVEL]	= IQuestSubSkillUpgradeLevel,
	
	[QUEST_TARGET_TYPE_FINISH_QUEST_COUNT_TYPE_TIMES]	= IQuestFinishQuestCountTypeTimes,
	
	[QUEST_TARGET_TYPE_ADVENTURE_SKILL_UPGRADE_LEVEL]	= IQuestAdventureSkillUpgradeLevel,
	[QUEST_TARGET_TYPE_ADVENTURE_QUEST_FINISH_TIMES]	= IQuestAdventureQuestFinishTimes,
	[QUEST_TARGET_TYPE_EQUIPS_FIT_REQUIRE]	= IQuestEquipsFitRequire,
	[QUEST_TARGET_TYPE_ADVENTURE_QUEST_FINISH_TODAY]	= IQuestAdventureQuestFinishToday,
	[QUEST_TARGET_TYPE_ADVENTURE_SKILL_ONE_LEVEL]	= IQuestAdventureSkillOneLevel,
	[QUEST_TARGET_TYPE_STAGE_INSTANCE_ID]	= IQuestStageInstanceId,
	[QUEST_TARGET_TYPE_FACTION_SKILL_MULTI_LEVEL]	= IQuestFactionSkillMultiLevel,
	[QUEST_TARGET_TYPE_FACTION_TOWER_FLOOR]	= IQuestFactionTowerFloor,
	[QUEST_TARGET_TYPE_TRIAL_TOWER_FLOOR]	= IQuestTrialTowerFloor,
	[QUEST_TARGET_TYPE_EQUIPDEVELOP_STRENGTH_MULTI_LEVEL]	= IQuestEquipdevelopStrengthMultiLevel,
	
}