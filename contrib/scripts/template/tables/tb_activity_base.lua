---------------------------------------------------------------------------------
--------------------------以下代码为自动生成，请勿手工改动-----------------------
---------------------------------------------------------------------------------


tb_activity_base = {
	--  id:int 活跃类型ID
	--  nums:int 活动次数上限
	--  active:int 单次活跃度
	--  time:array 活动时间
	--  day:array 有效星期(0~6 日~六) -1 全星期
	--  server_open_day:int 开服后几天强制开启 0无效 
	--  limtype:int 限制类型
	--  limdata:int 限制数据
	--  basereward:array 基础奖励
	--  reward:array 额外奖励
	[1] = {id = 1, nums = 2, active = 5, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 1, basereward = {{1401,1},{1201,10},{1202,1},{1301,10}}, reward = {{1301,1},{1201,10},{1202,1},{1301,10}}},
	[2] = {id = 2, nums = 4, active = 5, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 55, basereward = {{1301,1},{1201,10},{1202,1},{1301,11}}, reward = {{1301,1},{1201,10},{1202,1},{1301,11}}},
	[3] = {id = 3, nums = 1, active = 10, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 70, basereward = {{1301,1},{1201,10},{1202,1},{1301,12}}, reward = {{1301,1},{1201,10},{1202,1},{1301,12}}},
	[4] = {id = 4, nums = 2, active = 10, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 60, basereward = {{1301,1},{1201,10},{1202,1},{1301,13}}, reward = {{1301,1},{1201,10},{1202,1},{1301,13}}},
	[5] = {id = 5, nums = 1, active = 10, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 50, basereward = {{1301,1},{1201,10},{1202,1},{1301,16}}, reward = {{1301,1},{1201,10},{1202,1},{1301,16}}},
	[7] = {id = 7, nums = 1, active = 10, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 23, basereward = {{1301,1},{1201,10},{1202,1},{1301,11}}, reward = {{1301,1},{1201,10},{1202,1},{1301,11}}},
	[8] = {id = 8, nums = 1, active = 5, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 23, basereward = {{1301,1},{1201,10},{1202,1},{1301,13}}, reward = {{1301,1},{1201,10},{1202,1},{1301,13}}},
	[9] = {id = 9, nums = 2, active = 5, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 23, basereward = {{1301,1},{1201,10},{1202,1},{1301,16}}, reward = {{1301,1},{1201,10},{1202,1},{1301,16}}},
	[10] = {id = 10, nums = 2, active = 10, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 65, basereward = {{1401,1},{1201,10},{1202,1},{1301,10}}, reward = {{1301,1},{1201,10},{1202,1},{1301,10}}},
	[11] = {id = 11, nums = 1, active = 10, time = {{13,0,14,0},{20,0,21,0}}, day = {}, server_open_day = 0, limtype = 1, limdata = 120, basereward = {{1301,1},{1201,10},{1202,1},{1301,11}}, reward = {{1301,1},{1201,10},{1202,1},{1301,11}}},
	[12] = {id = 12, nums = 2, active = 10, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 35, basereward = {{1401,1},{1201,10},{1202,1},{1301,10}}, reward = {{1301,1},{1201,10},{1202,1},{1301,10}}},
	[13] = {id = 13, nums = 1, active = 10, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 10, basereward = {{1301,1},{1201,10},{1202,1},{1301,11}}, reward = {{1301,1},{1201,10},{1202,1},{1301,11}}},
	[14] = {id = 14, nums = 1, active = 5, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 50, basereward = {{1401,1},{1201,10},{1202,1},{1301,10}}, reward = {{1301,1},{1201,10},{1202,1},{1301,10}}},
	[28] = {id = 28, nums = 2, active = 5, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 40, basereward = {{1401,1},{1201,10},{1202,1},{1301,10}}, reward = {{1301,1},{1201,10},{1202,1},{1301,10}}},
	[29] = {id = 29, nums = 2, active = 10, time = {{19,0,20,0}}, day = {1,3,5}, server_open_day = 0, limtype = 1, limdata = 135, basereward = {}, reward = {}},
	[6] = {id = 6, nums = 1, active = 10, time = {{19,0,20,0}}, day = {2,4,6}, server_open_day = 0, limtype = 1, limdata = 100, basereward = {}, reward = {}},
	[31] = {id = 31, nums = 1, active = 10, time = {}, day = {0}, server_open_day = 3, limtype = 1, limdata = 23, basereward = {}, reward = {}},
	[15] = {id = 15, nums = 20, active = 1, time = {}, day = {}, server_open_day = 0, limtype = 1, limdata = 30, basereward = {}, reward = {}},
}
