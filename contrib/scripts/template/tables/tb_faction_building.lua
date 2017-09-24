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
	[101] = {id = 101, type = 1, level = 1, name = "家族主殿", unlock = 1, need_buildinglv = {}, cost = 3479, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[102] = {id = 102, type = 1, level = 2, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 8676, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[103] = {id = 103, type = 1, level = 3, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 14640, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[104] = {id = 104, type = 1, level = 4, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 23496, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[105] = {id = 105, type = 1, level = 5, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 51692, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[106] = {id = 106, type = 1, level = 6, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 68320, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[107] = {id = 107, type = 1, level = 7, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 82237, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[108] = {id = 108, type = 1, level = 8, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 104378, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[109] = {id = 109, type = 1, level = 9, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 130133, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[110] = {id = 110, type = 1, level = 10, name = "家族主殿", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {}},
	[201] = {id = 201, type = 2, level = 1, name = "家族宝库", unlock = 1, need_buildinglv = {{1,2}}, cost = 696, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {20,5,1503,30,6}},
	[202] = {id = 202, type = 2, level = 2, name = "家族宝库", unlock = 0, need_buildinglv = {{1,3}}, cost = 1735, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {21,5,1503,28,6}},
	[203] = {id = 203, type = 2, level = 3, name = "家族宝库", unlock = 0, need_buildinglv = {{1,4}}, cost = 2928, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {22,5,1503,26,6}},
	[204] = {id = 204, type = 2, level = 4, name = "家族宝库", unlock = 0, need_buildinglv = {{1,5}}, cost = 4699, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {23,5,1503,24,6}},
	[205] = {id = 205, type = 2, level = 5, name = "家族宝库", unlock = 0, need_buildinglv = {{1,6}}, cost = 10338, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {24,5,1503,22,6}},
	[206] = {id = 206, type = 2, level = 6, name = "家族宝库", unlock = 0, need_buildinglv = {{1,7}}, cost = 13664, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {25,5,1503,20,6}},
	[207] = {id = 207, type = 2, level = 7, name = "家族宝库", unlock = 0, need_buildinglv = {{1,8}}, cost = 16447, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {26,5,1503,18,6}},
	[208] = {id = 208, type = 2, level = 8, name = "家族宝库", unlock = 0, need_buildinglv = {{1,9}}, cost = 20876, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {27,5,1503,16,6}},
	[209] = {id = 209, type = 2, level = 9, name = "家族宝库", unlock = 0, need_buildinglv = {{1,10}}, cost = 26027, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {28,5,1503,14,6}},
	[210] = {id = 210, type = 2, level = 10, name = "家族宝库", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {30,5,1503,10,6}},
	[401] = {id = 401, type = 4, level = 1, name = "活动大厅", unlock = 3, need_buildinglv = {{1,2}}, cost = 696, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[402] = {id = 402, type = 4, level = 2, name = "活动大厅", unlock = 0, need_buildinglv = {{1,3}}, cost = 1735, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[403] = {id = 403, type = 4, level = 3, name = "活动大厅", unlock = 0, need_buildinglv = {{1,4}}, cost = 2928, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[404] = {id = 404, type = 4, level = 4, name = "活动大厅", unlock = 0, need_buildinglv = {{1,5}}, cost = 4699, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[405] = {id = 405, type = 4, level = 5, name = "活动大厅", unlock = 0, need_buildinglv = {{1,6}}, cost = 10338, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[406] = {id = 406, type = 4, level = 6, name = "活动大厅", unlock = 0, need_buildinglv = {{1,7}}, cost = 13664, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[407] = {id = 407, type = 4, level = 7, name = "活动大厅", unlock = 0, need_buildinglv = {{1,8}}, cost = 16447, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[408] = {id = 408, type = 4, level = 8, name = "活动大厅", unlock = 0, need_buildinglv = {{1,9}}, cost = 20876, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[409] = {id = 409, type = 4, level = 9, name = "活动大厅", unlock = 0, need_buildinglv = {{1,10}}, cost = 26027, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[410] = {id = 410, type = 4, level = 10, name = "活动大厅", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {}},
	[501] = {id = 501, type = 5, level = 1, name = "技能大厅", unlock = 2, need_buildinglv = {{1,2}}, cost = 696, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[502] = {id = 502, type = 5, level = 2, name = "技能大厅", unlock = 0, need_buildinglv = {{1,3}}, cost = 1735, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[503] = {id = 503, type = 5, level = 3, name = "技能大厅", unlock = 0, need_buildinglv = {{1,4}}, cost = 2928, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[504] = {id = 504, type = 5, level = 4, name = "技能大厅", unlock = 0, need_buildinglv = {{1,5}}, cost = 4699, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[505] = {id = 505, type = 5, level = 5, name = "技能大厅", unlock = 0, need_buildinglv = {{1,6}}, cost = 10338, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[506] = {id = 506, type = 5, level = 6, name = "技能大厅", unlock = 0, need_buildinglv = {{1,7}}, cost = 13664, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[507] = {id = 507, type = 5, level = 7, name = "技能大厅", unlock = 0, need_buildinglv = {{1,8}}, cost = 16447, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[508] = {id = 508, type = 5, level = 8, name = "技能大厅", unlock = 0, need_buildinglv = {{1,9}}, cost = 20876, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[509] = {id = 509, type = 5, level = 9, name = "技能大厅", unlock = 0, need_buildinglv = {{1,10}}, cost = 26027, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[510] = {id = 510, type = 5, level = 10, name = "技能大厅", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {}},
	[601] = {id = 601, type = 6, level = 1, name = "家族商店", unlock = 1, need_buildinglv = {{1,2}}, cost = 696, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[602] = {id = 602, type = 6, level = 2, name = "家族商店", unlock = 0, need_buildinglv = {{1,3}}, cost = 1735, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[603] = {id = 603, type = 6, level = 3, name = "家族商店", unlock = 0, need_buildinglv = {{1,4}}, cost = 2928, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[604] = {id = 604, type = 6, level = 4, name = "家族商店", unlock = 0, need_buildinglv = {{1,5}}, cost = 4699, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[605] = {id = 605, type = 6, level = 5, name = "家族商店", unlock = 0, need_buildinglv = {{1,6}}, cost = 10338, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[606] = {id = 606, type = 6, level = 6, name = "家族商店", unlock = 0, need_buildinglv = {{1,7}}, cost = 13664, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[607] = {id = 607, type = 6, level = 7, name = "家族商店", unlock = 0, need_buildinglv = {{1,8}}, cost = 16447, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[608] = {id = 608, type = 6, level = 8, name = "家族商店", unlock = 0, need_buildinglv = {{1,9}}, cost = 20876, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[609] = {id = 609, type = 6, level = 9, name = "家族商店", unlock = 0, need_buildinglv = {{1,10}}, cost = 26027, time = 5, can_lvup = 1, desc = {"说明1","说明2"}, params = {}},
	[610] = {id = 610, type = 6, level = 10, name = "家族商店", unlock = 0, need_buildinglv = {}, cost = 0, time = 0, can_lvup = 0, desc = {"说明1","说明2"}, params = {}},
}
