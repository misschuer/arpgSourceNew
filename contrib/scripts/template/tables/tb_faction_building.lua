---------------------------------------------------------------------------------
--------------------------以下代码为自动生成，请勿手工改动-----------------------
---------------------------------------------------------------------------------


tb_faction_building = {
	--  id:int 建筑ID
	--  type:int 建筑类别
	--  level:int 等级
	--  name:string 建筑名称
	--  unlock:int 解锁等级
	--  need_buildinglv:array 升级需求建筑前置等级{类别,等级}
	--  cost:int 消耗资金
	--  time:int 消耗时间(分钟)
	--  can_lvup:int 能否升级
	--  desc:array 描述
	--  params:array 参数
	[101] = {id = 101, type = 1, level = 1, name = "家族主殿", unlock = 1, need_buildinglv = {}, cost = 2000, time = 30, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[102] = {id = 102, type = 1, level = 2, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 2750, time = 60, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[103] = {id = 103, type = 1, level = 3, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 3600, time = 240, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[104] = {id = 104, type = 1, level = 4, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 4550, time = 420, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[105] = {id = 105, type = 1, level = 5, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 5600, time = 600, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[106] = {id = 106, type = 1, level = 6, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 6750, time = 780, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[107] = {id = 107, type = 1, level = 7, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 8000, time = 900, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[108] = {id = 108, type = 1, level = 8, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 9350, time = 1080, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[109] = {id = 109, type = 1, level = 9, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 10800, time = 1440, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[110] = {id = 110, type = 1, level = 10, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {}},
	[201] = {id = 201, type = 2, level = 1, name = "家族宝库", unlock = 1, need_buildinglv = {{1,2}}, cost = 1000, time = 15, can_lvup = 1, desc = {"说明1","说明2"}, params = {20,5,1519,50,6}},
	[202] = {id = 202, type = 2, level = 2, name = "家族宝库", unlock = 0, need_buildinglv = {{1,3}}, cost = 1226, time = 30, can_lvup = 1, desc = {"说明1","说明2"}, params = {20,5,1519,50,6}},
	[203] = {id = 203, type = 2, level = 3, name = "家族宝库", unlock = 0, need_buildinglv = {{1,4}}, cost = 1453, time = 120, can_lvup = 1, desc = {"说明1","说明2"}, params = {20,5,1519,50,6}},
	[204] = {id = 204, type = 2, level = 4, name = "家族宝库", unlock = 0, need_buildinglv = {{1,5}}, cost = 1680, time = 210, can_lvup = 1, desc = {"说明1","说明2"}, params = {30,5,1519,45,6}},
	[205] = {id = 205, type = 2, level = 5, name = "家族宝库", unlock = 0, need_buildinglv = {{1,6}}, cost = 1907, time = 300, can_lvup = 1, desc = {"说明1","说明2"}, params = {30,5,1519,45,6}},
	[206] = {id = 206, type = 2, level = 6, name = "家族宝库", unlock = 0, need_buildinglv = {{1,7}}, cost = 2134, time = 390, can_lvup = 1, desc = {"说明1","说明2"}, params = {30,5,1519,45,6}},
	[207] = {id = 207, type = 2, level = 7, name = "家族宝库", unlock = 0, need_buildinglv = {{1,8}}, cost = 2361, time = 450, can_lvup = 1, desc = {"说明1","说明2"}, params = {40,5,1519,40,6}},
	[208] = {id = 208, type = 2, level = 8, name = "家族宝库", unlock = 0, need_buildinglv = {{1,9}}, cost = 2587, time = 540, can_lvup = 1, desc = {"说明1","说明2"}, params = {40,5,1519,40,6}},
	[209] = {id = 209, type = 2, level = 9, name = "家族宝库", unlock = 0, need_buildinglv = {{1,10}}, cost = 2814, time = 720, can_lvup = 1, desc = {"说明1","说明2"}, params = {40,5,1519,40,6}},
	[210] = {id = 210, type = 2, level = 10, name = "家族宝库", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {50,5,1519,30,6}},
	[401] = {id = 401, type = 4, level = 1, name = "活动大厅", unlock = 3, need_buildinglv = {{1,2}}, cost = 800, time = 15, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[402] = {id = 402, type = 4, level = 2, name = "活动大厅", unlock = 0, need_buildinglv = {{1,3}}, cost = 1023, time = 30, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[403] = {id = 403, type = 4, level = 3, name = "活动大厅", unlock = 0, need_buildinglv = {{1,4}}, cost = 1247, time = 120, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[404] = {id = 404, type = 4, level = 4, name = "活动大厅", unlock = 0, need_buildinglv = {{1,5}}, cost = 1470, time = 210, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[405] = {id = 405, type = 4, level = 5, name = "活动大厅", unlock = 0, need_buildinglv = {{1,6}}, cost = 1694, time = 300, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[406] = {id = 406, type = 4, level = 6, name = "活动大厅", unlock = 0, need_buildinglv = {{1,7}}, cost = 1918, time = 390, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[407] = {id = 407, type = 4, level = 7, name = "活动大厅", unlock = 0, need_buildinglv = {{1,8}}, cost = 2141, time = 450, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[408] = {id = 408, type = 4, level = 8, name = "活动大厅", unlock = 0, need_buildinglv = {{1,9}}, cost = 2365, time = 540, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[409] = {id = 409, type = 4, level = 9, name = "活动大厅", unlock = 0, need_buildinglv = {{1,10}}, cost = 2588, time = 720, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[410] = {id = 410, type = 4, level = 10, name = "活动大厅", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {}},
	[501] = {id = 501, type = 5, level = 1, name = "技能大厅", unlock = 2, need_buildinglv = {{1,2}}, cost = 1000, time = 15, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[502] = {id = 502, type = 5, level = 2, name = "技能大厅", unlock = 0, need_buildinglv = {{1,3}}, cost = 1199, time = 30, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[503] = {id = 503, type = 5, level = 3, name = "技能大厅", unlock = 0, need_buildinglv = {{1,4}}, cost = 1398, time = 120, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[504] = {id = 504, type = 5, level = 4, name = "技能大厅", unlock = 0, need_buildinglv = {{1,5}}, cost = 1597, time = 210, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[505] = {id = 505, type = 5, level = 5, name = "技能大厅", unlock = 0, need_buildinglv = {{1,6}}, cost = 1796, time = 300, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[506] = {id = 506, type = 5, level = 6, name = "技能大厅", unlock = 0, need_buildinglv = {{1,7}}, cost = 1995, time = 390, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[507] = {id = 507, type = 5, level = 7, name = "技能大厅", unlock = 0, need_buildinglv = {{1,8}}, cost = 2194, time = 450, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[508] = {id = 508, type = 5, level = 8, name = "技能大厅", unlock = 0, need_buildinglv = {{1,9}}, cost = 2393, time = 540, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[509] = {id = 509, type = 5, level = 9, name = "技能大厅", unlock = 0, need_buildinglv = {{1,10}}, cost = 2592, time = 720, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[510] = {id = 510, type = 5, level = 10, name = "技能大厅", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {}},
	[601] = {id = 601, type = 6, level = 1, name = "家族商店", unlock = 1, need_buildinglv = {{1,2}}, cost = 1000, time = 15, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[602] = {id = 602, type = 6, level = 2, name = "家族商店", unlock = 0, need_buildinglv = {{1,3}}, cost = 1226, time = 30, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[603] = {id = 603, type = 6, level = 3, name = "家族商店", unlock = 0, need_buildinglv = {{1,4}}, cost = 1453, time = 120, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[604] = {id = 604, type = 6, level = 4, name = "家族商店", unlock = 0, need_buildinglv = {{1,5}}, cost = 1680, time = 210, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[605] = {id = 605, type = 6, level = 5, name = "家族商店", unlock = 0, need_buildinglv = {{1,6}}, cost = 1907, time = 300, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[606] = {id = 606, type = 6, level = 6, name = "家族商店", unlock = 0, need_buildinglv = {{1,7}}, cost = 2134, time = 390, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[607] = {id = 607, type = 6, level = 7, name = "家族商店", unlock = 0, need_buildinglv = {{1,8}}, cost = 2361, time = 450, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[608] = {id = 608, type = 6, level = 8, name = "家族商店", unlock = 0, need_buildinglv = {{1,9}}, cost = 2587, time = 540, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[609] = {id = 609, type = 6, level = 9, name = "家族商店", unlock = 0, need_buildinglv = {{1,10}}, cost = 2814, time = 720, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[610] = {id = 610, type = 6, level = 10, name = "家族商店", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {}},
}
