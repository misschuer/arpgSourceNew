---------------------------------------------------------------------------------
--------------------------以下代码为自动生成，请勿手工改动-----------------------
---------------------------------------------------------------------------------


tb_faction_match_base = {
	--  id:int 序号
	--  map_id:int 地图id
	--  born_1:array 1队出生点x
	--  born_2:array 2队出生点x
	--  flag_id:array 旗子采集物id (中立 红 蓝)
	--  flag_pos:array 旗子采集物位置(x,y,0~360)
	--  wall_id:array 阻挡物id (红 蓝)
	--  wall_pos:array 阻挡物位置 (红 蓝) (x,y,0~360)
	--  min_member_need:int 最少参与人数需求
	--  enterFactionTime:int 成员加入家族时间要求 秒数
	--  flag_score_gain_speed:int 占点分数每秒上升
	--  kill_score_gain:int 击杀分数
	--  target_score:int 目标分数
	--  server_open_day:int 开服后几天开启
	--  week_open_day:int 每周几开启(0~6表示周日到周六)
	[1] = {id = 1, map_id = 7001, born_1 = {327,106}, born_2 = {7,103}, flag_id = {100,101,102}, flag_pos = {{85,104,0},{173,15,0},{173,105,0},{173,193,0},{262,104,0}}, wall_id = {110,110}, wall_pos = {{32,105,0},{316,107,0}}, min_member_need = 0, enterFactionTime = 60, flag_score_gain_speed = 5, kill_score_gain = 1, target_score = 2000, server_open_day = 2, week_open_day = 0},
}
