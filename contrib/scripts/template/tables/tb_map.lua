---------------------------------------------------------------------------------
--------------------------以下代码为自动生成，请勿手工改动-----------------------
---------------------------------------------------------------------------------


tb_map = {
	--  id:int 地图ID
	--  parentid:int 父级地图ID
	--  name:string 地图名称
	--  tele:array 传送到的坐标
	--  levellimit:int 等级限制
	--  type:int 地图类型
	--  isTimeLimit:int 是否时间限制
	--  allowChangeMode:int 是否允许切换模式
	--  inst_type:int 地图副本类型
	--  inst_sub_type:int 地图子类型
	--  is_need_general:int 是否需要gernealid
	--  isOfflineReenter:int 是否能离线重进
	--  is_instance:int 是否副本地图
	--  is_boss_risk:int 是否是冒险地图BOSS关
	--  shadow:int 影子方向
	--  count:int 副本人数
	--  day_limit:int 日限制
	--  week_limit:int 周限制
	--  enter_mask:int 可进入地图掩码
	--  inst_id:array 可进入此地图的副本或活动id
	--  is_cast:int 允许施法
	--  is_PK:int 允许PK
	--  is_jump:int 允许跳跃
	--  is_ride:int 允许骑乘
	--  is_sit:int 允许打坐
	--  rebornPos:array 复活点
	--  rebornTime:array 自动复活时间
	--  costGold:array 元宝复活花费
	--  rebornWaitTime:array 原地复活等待时间
	--  restore_potion:int 能否使用回复药
	--  default_mode:int 地图默认模式
	[1] = {id = 1, parentid = 1, name = "蜀山", tele = {140,170}, levellimit = 0, type = 0, isTimeLimit = 0, allowChangeMode = 0, inst_type = 0, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 0, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 31, inst_id = {}, is_cast = 0, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {125,164,154,163}, rebornTime = {30}, costGold = {50}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[1001] = {id = 1001, parentid = 1001, name = "凝碧崖", tele = {19,79}, levellimit = 1, type = 1, isTimeLimit = 0, allowChangeMode = 0, inst_type = 0, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 0, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 0, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {139,118,148,110}, rebornTime = {30}, costGold = {50}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[1002] = {id = 1002, parentid = 1002, name = "莽苍山", tele = {108,194}, levellimit = 20, type = 1, isTimeLimit = 0, allowChangeMode = 1, inst_type = 0, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 0, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 0, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {100,170,116,177}, rebornTime = {30}, costGold = {50}, rebornWaitTime = {}, restore_potion = 1, default_mode = -1},
	[1003] = {id = 1003, parentid = 1003, name = "慈云寺", tele = {18,199}, levellimit = 30, type = 1, isTimeLimit = 0, allowChangeMode = 1, inst_type = 0, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 0, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 0, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {19,189,17,205}, rebornTime = {30}, costGold = {50}, rebornWaitTime = {}, restore_potion = 1, default_mode = -1},
	[1004] = {id = 1004, parentid = 1004, name = "青螺山", tele = {86,163}, levellimit = 40, type = 1, isTimeLimit = 0, allowChangeMode = 0, inst_type = 0, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 0, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 0, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {68,158,91,180}, rebornTime = {30}, costGold = {50}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[1005] = {id = 1005, parentid = 1005, name = "开元湖畔", tele = {56,119}, levellimit = 0, type = 1, isTimeLimit = 0, allowChangeMode = 0, inst_type = 0, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 0, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 0, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {127,114,156,115}, rebornTime = {30}, costGold = {50}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[1006] = {id = 1006, parentid = 1006, name = "伏魔谷", tele = {100,100}, levellimit = 50, type = 1, isTimeLimit = 0, allowChangeMode = 0, inst_type = 0, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 0, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 0, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {87,107,87,107}, rebornTime = {30}, costGold = {50}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2001] = {id = 2001, parentid = 2001, name = "桃花迷阵", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 0, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {25,21,25,21}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2002] = {id = 2002, parentid = 2002, name = "试炼塔野", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 0, inst_id = {1}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2003] = {id = 2003, parentid = 2003, name = "VIP副本1", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 2, inst_sub_type = 1, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2004] = {id = 2004, parentid = 2004, name = "试炼塔", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 2, inst_sub_type = 2, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2005] = {id = 2005, parentid = 2005, name = "世界冒险", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 1, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2011] = {id = 2011, parentid = 2011, name = "羽毛副本", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 2, inst_sub_type = 4, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2012] = {id = 2012, parentid = 2012, name = "经脉副本", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 2, inst_sub_type = 4, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2013] = {id = 2013, parentid = 2013, name = "兽魂副本", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 2, inst_sub_type = 4, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2014] = {id = 2014, parentid = 2014, name = "银币副本", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 2, inst_sub_type = 4, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2015] = {id = 2015, parentid = 2015, name = "精炼副本", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 2, inst_sub_type = 4, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2016] = {id = 2016, parentid = 2016, name = "世界BOSS报名", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2017] = {id = 2017, parentid = 2017, name = "世界BOSS战斗", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 3, is_need_general = 0, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2018] = {id = 2018, parentid = 2018, name = "仙府夺宝体验副本", tele = {}, levellimit = 0, type = 4, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 8, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2019] = {id = 2019, parentid = 2019, name = "全民BOSS1", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2020] = {id = 2020, parentid = 2020, name = "全民BOSS2", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2021] = {id = 2021, parentid = 2021, name = "全民BOSS3", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2022] = {id = 2022, parentid = 2022, name = "全民BOSS4", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2023] = {id = 2023, parentid = 2023, name = "全民BOSS5", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2024] = {id = 2024, parentid = 2024, name = "全民BOSS6", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2025] = {id = 2025, parentid = 2025, name = "全民BOSS7", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2026] = {id = 2026, parentid = 2026, name = "全民BOSS8", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2027] = {id = 2027, parentid = 2027, name = "全民BOSS9", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2028] = {id = 2028, parentid = 2028, name = "全民BOSS10", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2501] = {id = 2501, parentid = 2501, name = "个人BOSS1", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2502] = {id = 2502, parentid = 2502, name = "个人BOSS2", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2503] = {id = 2503, parentid = 2503, name = "个人BOSS3", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2504] = {id = 2504, parentid = 2504, name = "个人BOSS4", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2505] = {id = 2505, parentid = 2505, name = "个人BOSS5", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2506] = {id = 2506, parentid = 2506, name = "个人BOSS6", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2507] = {id = 2507, parentid = 2507, name = "个人BOSS7", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2508] = {id = 2508, parentid = 2508, name = "个人BOSS8", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2509] = {id = 2509, parentid = 2509, name = "个人BOSS9", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[2510] = {id = 2510, parentid = 2510, name = "个人BOSS10", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 17, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[3001] = {id = 3001, parentid = 3001, name = "斗剑台", tele = {}, levellimit = 0, type = 4, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 7, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 0, default_mode = 0},
	[3002] = {id = 3002, parentid = 3002, name = "封魔战场", tele = {}, levellimit = 0, type = 4, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 5, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[3003] = {id = 3003, parentid = 3003, name = "仙府夺宝", tele = {}, levellimit = 0, type = 4, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 6, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[3004] = {id = 3004, parentid = 3004, name = "仙府夺宝预览", tele = {}, levellimit = 0, type = 1, isTimeLimit = 0, allowChangeMode = 0, inst_type = 0, inst_sub_type = 0, is_need_general = 0, isOfflineReenter = 0, is_instance = 0, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[3005] = {id = 3005, parentid = 3005, name = "修炼场", tele = {}, levellimit = 0, type = 4, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 9, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[3006] = {id = 3006, parentid = 3006, name = "跨服组队副本1", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3007] = {id = 3007, parentid = 3007, name = "跨服组队副本2", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3008] = {id = 3008, parentid = 3008, name = "跨服组队副本3", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3009] = {id = 3009, parentid = 3009, name = "跨服组队副本4", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3010] = {id = 3010, parentid = 3010, name = "跨服组队副本5", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3011] = {id = 3011, parentid = 3011, name = "跨服组队副本6", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3012] = {id = 3012, parentid = 3012, name = "跨服组队副本7", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3013] = {id = 3013, parentid = 3013, name = "跨服组队副本8", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3014] = {id = 3014, parentid = 3014, name = "跨服组队副本9", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3015] = {id = 3015, parentid = 3015, name = "跨服组队副本10", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 12, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {20,115,20,115}, rebornTime = {30}, costGold = {}, rebornWaitTime = {10,20,30,40,50}, restore_potion = 1, default_mode = 0},
	[3016] = {id = 3016, parentid = 3016, name = "首领挑战", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 13, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[3017] = {id = 3017, parentid = 3017, name = "无尽远征", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 14, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[3018] = {id = 3018, parentid = 3018, name = "排位赛", tele = {}, levellimit = 0, type = 4, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 15, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[4001] = {id = 4001, parentid = 4001, name = "凝碧崖（剧情）", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 10, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {139,118,148,110}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[4002] = {id = 4002, parentid = 4002, name = "莽苍山（剧情）", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 10, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {100,170,116,177}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[4003] = {id = 4003, parentid = 4003, name = "慈云寺（剧情）", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 10, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {19,189,17,205}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[4004] = {id = 4004, parentid = 4004, name = "青螺山（剧情）", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 10, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {68,158,91,180}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[4005] = {id = 4005, parentid = 4005, name = "百蛮山（剧情）", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 10, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[4006] = {id = 4006, parentid = 4006, name = "伏魔谷（剧情）", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 10, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[5001] = {id = 5001, parentid = 5001, name = "家族地图", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 1, inst_sub_type = 11, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 31, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[5002] = {id = 5002, parentid = 5002, name = "家族boss", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 13, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[5003] = {id = 5003, parentid = 5003, name = "家族爬塔", tele = {}, levellimit = 0, type = 2, isTimeLimit = 1, allowChangeMode = 0, inst_type = 1, inst_sub_type = 14, is_need_general = 1, isOfflineReenter = 0, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 1, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {}, costGold = {}, rebornWaitTime = {}, restore_potion = 1, default_mode = 0},
	[6101] = {id = 6101, parentid = 6101, name = "幻境第一章", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {10}, costGold = {}, rebornWaitTime = {5}, restore_potion = 1, default_mode = 0},
	[6201] = {id = 6201, parentid = 6201, name = "幻境第二章", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {10}, costGold = {}, rebornWaitTime = {5}, restore_potion = 1, default_mode = 0},
	[6301] = {id = 6301, parentid = 6301, name = "幻境第三章", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {10}, costGold = {}, rebornWaitTime = {5}, restore_potion = 1, default_mode = 0},
	[6401] = {id = 6401, parentid = 6401, name = "幻境第四章", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 0, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {10}, costGold = {}, rebornWaitTime = {5}, restore_potion = 1, default_mode = 0},
	[6102] = {id = 6102, parentid = 6102, name = "幻境第一章BOSS", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 1, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {10}, costGold = {}, rebornWaitTime = {5}, restore_potion = 1, default_mode = 0},
	[6202] = {id = 6202, parentid = 6202, name = "幻境第二章BOSS", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 1, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {10}, costGold = {}, rebornWaitTime = {5}, restore_potion = 1, default_mode = 0},
	[6302] = {id = 6302, parentid = 6302, name = "幻境第三章BOSS", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 1, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {10}, costGold = {}, rebornWaitTime = {5}, restore_potion = 1, default_mode = 0},
	[6402] = {id = 6402, parentid = 6402, name = "幻境第四章BOSS", tele = {}, levellimit = 0, type = 2, isTimeLimit = 0, allowChangeMode = 0, inst_type = 2, inst_sub_type = 16, is_need_general = 1, isOfflineReenter = 1, is_instance = 1, is_boss_risk = 1, shadow = 0, count = 0, day_limit = 0, week_limit = 0, enter_mask = 3, inst_id = {}, is_cast = 1, is_PK = 0, is_jump = 1, is_ride = 1, is_sit = 1, rebornPos = {26,26,26,26}, rebornTime = {10}, costGold = {}, rebornWaitTime = {5}, restore_potion = 1, default_mode = 0},
}
