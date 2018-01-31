---------------------------------------------------------------------------------
--------------------------以下代码为自动生成，请勿手工改动-----------------------
---------------------------------------------------------------------------------


tb_gameobject_template = {
	--  id:int 采集物ID
	--  name:string 名称
	--  time:int 采集时间
	--  actionState:int 采集动作2
	--  regX:int 坐标X
	--  regY:int 坐标Y
	--  isAround:int 是否允许走动2
	--  judge:int 特殊判断
	--  go_flag:int 传送点标志位
	--  quest_id0:int 任务0
	--  quest_id1:int 任务1
	--  quest_id2:int 任务2
	--  quest_id3:int 任务3
	--  trigger_width:int 感应区宽
	--  trigger_height:int 感应区高
	--  rewards:array 采集后获得的奖励
	[4] = {id = 4, name = "选中特效", time = 0, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 0, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 0, trigger_height = 0, rewards = {}},
	[5] = {id = 5, name = "跳点", time = 0, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 4, go_flag = 16, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 2, trigger_height = 2, rewards = {}},
	[6] = {id = 6, name = "传送门", time = 1, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 2, go_flag = 18, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 3, trigger_height = 3, rewards = {}},
	[7] = {id = 7, name = "大宝箱", time = 5, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 1, go_flag = 1024, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[8] = {id = 8, name = "任务大宝箱", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 2084, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[9] = {id = 9, name = "探索大宝箱", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[10] = {id = 10, name = "回血", time = 0, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 3, go_flag = 4096, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 2, trigger_height = 2, rewards = {}},
	[11] = {id = 11, name = "攻击增强", time = 0, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 3, go_flag = 4096, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 2, trigger_height = 2, rewards = {}},
	[12] = {id = 12, name = "防御增强", time = 0, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 3, go_flag = 4096, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 2, trigger_height = 2, rewards = {}},
	[13] = {id = 13, name = "暴击增强", time = 0, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 3, go_flag = 4096, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 2, trigger_height = 2, rewards = {}},
	[20] = {id = 20, name = "荧月幽莲", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[21] = {id = 21, name = "木桩", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[22] = {id = 22, name = "界碑", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[23] = {id = 23, name = "神魂石", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[24] = {id = 24, name = "兵魂石", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[25] = {id = 25, name = "佛像", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[26] = {id = 26, name = "大鼓", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[27] = {id = 27, name = "野花", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[28] = {id = 28, name = "莽苍山预留", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[31] = {id = 31, name = "清明草", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[32] = {id = 32, name = "灵植", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[33] = {id = 33, name = "野荷花", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[34] = {id = 34, name = "水桶", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[35] = {id = 35, name = "药材架子", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[36] = {id = 36, name = "慈云寺香炉1", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[37] = {id = 37, name = "慈云寺香炉2", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[38] = {id = 38, name = "慈云寺香炉3", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[39] = {id = 39, name = "慈云寺香炉4", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[40] = {id = 40, name = "风口点", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 3, trigger_height = 3, rewards = {}},
	[41] = {id = 41, name = "掉落宝箱", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 3, trigger_height = 3, rewards = {}},
	[42] = {id = 42, name = "掉落装备", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 3, trigger_height = 3, rewards = {}},
	[100] = {id = 100, name = "中立旗", time = 5, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 4096, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[101] = {id = 101, name = "红旗", time = 5, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 4096, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[102] = {id = 102, name = "蓝旗", time = 5, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 4096, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[110] = {id = 110, name = "", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 5, go_flag = 16, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[111] = {id = 111, name = "", time = 0, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 5, go_flag = 16, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[43] = {id = 43, name = "魔器鼎炉", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[44] = {id = 44, name = "坐化圣佛碑", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[45] = {id = 45, name = "香塔", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[46] = {id = 46, name = "石碑", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[47] = {id = 47, name = "丹药", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[48] = {id = 48, name = "宝箱", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[49] = {id = 49, name = "观察点", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
	[50] = {id = 50, name = "追魂草", time = 3, actionState = 0, regX = 0, regY = 0, isAround = 0, judge = 0, go_flag = 36, quest_id0 = 0, quest_id1 = 0, quest_id2 = 0, quest_id3 = 0, trigger_width = 6, trigger_height = 6, rewards = {}},
}
