require('util.functions')
local protocols = require('share.protocols')
local security = require("base/Security")
local AppdApp = class('AppdApp',require('util.app_base'))

function AppdApp:ctor( )
	super(self)
	--对象管理器最重要了
	self.objMgr = require('appd.appd_obj_manager').new()

	--应用服开启http监听
	self.http = require('appd.http').new()

	--后台公告
	self.gmNotice = require('appd.gm_notice').new()
	
	--新版数据库接口
	local isPkServer = globalGameConfig:IsPKServer()
	if not isPkServer then
		self.dbAccess = require('appd.appd_mongo_db').new(getCXXGlobalPtr('MongoWrap'),getCXXGlobalPtr('AsyncMongoDB'))
	else
	end

	--1s一次的心跳
	self.cron:every(1,function ( )
		--后台公告心跳
		self.gmNotice:update()
	end)
	
	self:InitCorn()
	
	-- 3v3组队信息 team_guid:{player_guid1, player_guid2, player_guid3}
	self.world_3v3_team_dict = {}
	-- 3v3组队中个人所在的队伍 player_guid:team_guid
	self.world_3v3_player_team = {}
	-------------------------------------------
	-- 跨服排行榜信息
	self.kuafu_rank = {}
end

-- 设置正在进行的跨服操作类型
function AppdApp:SetMatchingKuafuType(player_guid, kuafu_type)
	kuafu_type = kuafu_type or 0
	SetMatchingKuafuType(player_guid, kuafu_type)
end

-- 获得正在进行的跨服操作类型
function AppdApp:GetMatchingKuafuType(player_guid)
	return GetMatchingKuafuType(player_guid)
end

-- 是否正在进行指定跨服类型操作
function AppdApp:IsKuafuTypeMatching(player_guid, kuafu_type)
	return IsKuafuTypeMatching(player_guid, kuafu_type)
end

-- 是否在进行跨服操作
function AppdApp:IsInKuafuTypeMatching(player_guid)
	return IsKuafuTypeMatching(player_guid, 0)
end

-- 获得跨服对应的参数数据
function AppdApp:GetKuafuTypeMatchingArg(player_guid)
	return GetKuafuTypeMatchingArg(player_guid)
end

function AppdApp:update( diff )
	if self.http then
		--奔跑吧,http服务
		self.http:update()
	end
	--update函数被子类重写了,只好手工再调用
	self.super.update(self, diff)
end

-- 定时器初始化
function AppdApp:InitCorn()
	--如果是pk服，下面的都不需要了
	if(globalGameConfig:IsPKServer())then
		return
	end
	
	--0点更新活动定时器
	self.cron:addCron("更新限时活动",'0 0 * * *',function() GetTodayLimitActivityVersion() end)
	
	--0点重置
	self.cron:addCron("0点重置",'0 0 * * *',function() 
		security.call(
			--try block
			function()
				self.objMgr:foreachAllPlayer(function(player)	
					player:DoResetDaily()
					
					local name = player:GetName()
					local create_time = player:GetCharCreateTime()
					local last_login_time = player:GetUInt32(PLAYER_EXPAND_INT_LAST_LOGIN_TIME)
					local from_last_time = os.time() - create_time
					local ip = player:GetStr(PLAYER_STRING_FIELD_LAST_LOGIN_IP)
					local gender = player:GetGender()
					local level = player:GetLevel()
					local force = player:GetForce()
					local active_value = player:GetUInt32(PLAYER_INT_FIELD_ACTIVE)
					local map_id = player:GetMapId()
					local main_quest_id = player:GetMainQuestID()
					local history_recharge = player:GetRechageSum()
					local gold = player:GetMoney(MONEY_TYPE_GOLD_INGOT)
					local bind_gold = player:GetMoney(MONEY_TYPE_BIND_GOLD)
					local money = player:GetMoney(MONEY_TYPE_SILVER)
					local bind_money= 0
					
					WriteOnlineUser24th(player, name, create_time, last_login_time, from_last_time, ip, gender, level, force, active_value, map_id,main_quest_id, history_recharge, gold, bind_gold, money, bind_money)
				end)
				-- 每日排行奖励
				self:RankReward()
				
				self.objMgr:foreachAllFaction(function(faction)
					faction:ResetFaction()
				end)
				--SendFactionGiftRankReward()
				
				globalValue:CheckFactionMatchStart()
			end
		)
		
	end)
	
	--12点重置
	self.cron:addCron("12点重置",'0 12 * * *',function() 
		security.call(
		
			function()
				self.objMgr:foreachAllFaction(function(faction)
					faction:ResetAllBossDenfense()
				end)
				
				self.objMgr:foreachAllPlayer(function(player)	
					player:DoResetDaily()
				end)
			end
		)
	end)
	
	--3v3结算时间
	for _,v in ipairs(tb_kuafu3v3_base[ 1 ].activetime) do
		local ff = string.format('%d %d * * *', v[ 4 ], v[ 3 ])
		self.cron:addCron("3v3结算", ff, function()
			outFmtDebug("==###@@@@@@@@@ 3v3 xxxxxxxxxx")
			security.call(
				function()
					for _, x in ipairs(tb_kuafu3v3_base[ 1 ].day) do
						if IsTodayWeekX(x) then
							-- 排行榜里的人没人一份
							local rankGuidList = GetRankGuidTable(RANK_TYPE_3V3)
							for rank, playerGuid in ipairs(rankGuidList) do
								local config = tb_local3v3_daily_reward[#tb_local3v3_daily_reward]
								for i = 1, #tb_local3v3_daily_reward do
									local tconfig = tb_local3v3_daily_reward[ i ]
									if rank >= tconfig.rank[ 1 ] and rank <= tconfig.rank[ 2 ] then
										config = tconfig
										break
									end
								end
								
								if config then
									local desc = config.maildesc
									local name = config.mailname
									local reward = config.reward
									local giftType = 3
									AddGiftPacksData(playerGuid,0,giftType,os.time(),os.time() + 86400*30, name, desc, reward, SYSTEM_NAME)
									if rank >= 1 and rank <=3 then
										local  player_name = GetRankName(RANK_TYPE_3V3,rank)
										app:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_3V3_RANKUP,{ToShowName(player_name),rank})
									end
								end
							end
							
							-- 清空排行榜信息
							clearRankTask(RANK_TYPE_3V3)
							
							-- 给在线的每人发一份参与奖励 (通过积分判断)
							self.objMgr:foreachAllPlayer(
								function(player)
									if player:GetKuafu3v3Score() > 0 then
										player:SetKuafu3v3Score(0)
										player:Get3v3JoinReward()
									end							
								end
							)
							break
						end
					end
	
				end
			)
		end)
	end
	
	
	
	-- 每周重置
	self.cron:addCron("每周重置",'0 0 * * 2',function() 
--		Rank3v3kuafuWeek()
		security.call(
			function()
				self.objMgr:foreachAllFaction(function(faction)
					faction:ResetFactionWeek()
				end)
				
				-- 重置排位赛的名次
				clearRankTask(RANK_TYPE_SINGLE_PVP)
			end
		)
	end)
	
	--[[注释掉野外BOSS
	-- 野外boss马上刷新通知
	local fbconfig = tb_field_boss_time[ 1 ]
		
	for _, timeInfo in pairs(fbconfig.time) do
		local H = timeInfo[ 1 ]
		local M = timeInfo[ 2 ]
		
		self:InitFieldBossCorn(H, M, fbconfig.noticestarttime, fbconfig.noticebosstime)
	end
	--]]
	
	-- 世界BOSS
	local wbconfig = tb_worldboss_time[ 1 ]
	for _,day in pairs(wbconfig.day) do
		if day == -1 then
			self:InitWorldBossCorn(wbconfig.time[ 1 ], wbconfig.time[ 2 ], wbconfig.enrolllast, wbconfig.time_last, wbconfig.notice)
			break
		else
			self:InitWorldBossCornByWeekDay(wbconfig.time[ 1 ], wbconfig.time[ 2 ], wbconfig.enrolllast, wbconfig.time_last, wbconfig.notice,day + 1)
		end
	end
	--self:InitWorldBossCorn(wbconfig.time[ 1 ], wbconfig.time[ 2 ], wbconfig.enrolllast, wbconfig.time_last, wbconfig.notice)
	
	--[[
	--每隔1s检测下修炼场次数回复
	self.cron:every("修炼场次数回复",1,function()
		self.objMgr:foreachAllPlayer(function(player)	
			player:UpdateCultivation()
		end)		
	end)
	--]]
	
	--每隔1s检测下修家族建筑升级进度
	self.cron:every("1秒钟检测一次的", 1, function()
		security.call(
			function()
				self.objMgr:foreachAllFaction(function(faction)
					faction:UpdateBuildingProcess()
				end)
				
				-- 挑战全民boss次数检测
				self.objMgr:foreachAllPlayer(
					function(player)	
						--player:CheckAddMassBossTimes()
						
						player:CheckEscortTimeOut()
					end
				)
						
				for id = 1, #tb_mass_boss_info do
					if not globalValue:isMassBossAlive(id) then
						if globalValue:checkMassBossReborn(id) then
							globalValue:doMassBossStart(id)
							NoticeScene(APPD_SCENED_MASS_BOSS_REBORN, id)
						end
					end
				end
				
				-- 进行排位赛匹配
				OnProcessLocalSinglePVPMatch()
				
				OnGroupSecondMatch()
				
				CheckGroupPrepared()
				
				OnLocal3V3Matching()
				
				-- 检查活动是否开启
				globalCounter:activityUpdate()
				
				globalValue:UpdateFactionMatch()
			end
		)
	end)
	
	
	--[[
	--每隔5s检测下失效物品
	self.cron:every("失效物品检测",5,function()
		self.objMgr:foreachAllPlayer(function(player)	
			local itemMgr = player:getItemMgr()
			if itemMgr then itemMgr:delFailTimeItem() end
		end)		
	end)
	--]]
	--每隔5min刷新好友信息
	self.cron:every("好友信息刷新",300,function()
		security.call(function()
			self.objMgr:foreachAllPlayer(function(player)	
				player:RefreshFriendInfo()
			end)
		end)
	end)

	-- 每个1800秒刷新排行榜信息
	self.cron:every("刷新排行榜信息", 1800,function()
		security.call(function()
			OnUpdateRankList()
		end)
	end)
	
	--每隔60s检测下失效称号
	self.cron:every("刷新排行榜信息", 60,function()
		security.call(function()
			self.objMgr:foreachAllPlayer(function(player)
				player:removeExpireTitle()
			end)
		end)
	end)

	--每隔600s检测下在线人数
	self.cron:every("刷新在线信息", 600,function()
		security.call(function()
			local account_t = {}
			local account_count = 0
			local player_count = 0
			local ip_t = {}
			local ip_count = 0
			local old_player_count = 0

			self.objMgr:foreachAllPlayer(function(player)
				local account = player:GetAccount()
				local ip = player:GetStr(PLAYER_STRING_FIELD_LAST_LOGIN_IP)
				local create_time = player:GetCharCreateTime()
				
				if not account_t[account] then
					account_count = account_count + 1
					account_t[account] = 1
				end
				
				player_count = player_count + 1
				
				if not ip_t[ip] then
					ip_count = ip_count + 1
					ip_t[ip] = 1
				end
				
				if not checkSameDay(create_time,os.time()) then
					old_player_count = old_player_count + 1
				end
				
			end)
			WriteOnline(os.time(),account_count,player_count,ip_count,old_player_count)
		end)
	end)
	--[[
	--每隔3s查询匹配情况
	self.cron:every("查询跨服匹配", 1, function()
		self.objMgr:foreachAllPlayer(function(player)
			player:QueryKuafuMatchInfo()
		end)
	end)
	--]]
	--每隔10s跳一次挂机奖励
--[[	self.cron:every("跳一次挂机奖励", 10, function()
		self.objMgr:foreachAllPlayer(function(player)
			player:onPickRiskReward()
		end)
	end)--]]
	
	--[[
	--每隔3600s更新跨服排行榜
	self.cron:every("更新跨服排行", 3600, function()
		UpdateKuafuRank()
	end)
	--]]
	
	--[[
	--10分钟存储一次修炼记录
	self.cron:every("10分钟存储一次修炼记录", 600, function()
		-- C++中处理
		SaveXiulianData()
	end)
	--]]
end

-- 全服野外BOSS定时器初始化
function AppdApp:InitFieldBossCorn(H, M, startTime, bossTime)
	
	-- 刷新BOSS
	local crontab_str = string.format("%d %d * * *", M, H)
	outFmtDebug("============================born boss crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服野外BOSS刷新", crontab_str, function() 
		-- 通知场景服刷BOSS
		self:CallOptResult(OPERTE_TYPE_FIELD_BOSS, FIELD_BOSS_OPERTE_OCCUR, {startTime})
		NoticeScene(APPD_SCENED_REBORN_FIELD_BOSS)
	end)	
				
	-- 即将开始通知
	local TH, TM = self:ModifyTimeMinutes(H, M, -startTime)
	local crontab_str1 = string.format("%d %d * * *", TM, TH)
	outFmtDebug("------------------------------startTime crontab_str = %s", crontab_str1)
	self.cron:addCron("通知全服野外BOSS将要开启", crontab_str1, function() 
		-- 通知场景服 清理前一个BOSS的数据
		NoticeScene(APPD_SCENED_CLEAR_FIELD_BOSS)
		
		self:CallOptResult(OPERTE_TYPE_FIELD_BOSS, FIELD_BOSS_OPERTE_WILL_START, {startTime})
	end)
	
	-- 即将刷新通知
	TH, TM = self:ModifyTimeMinutes(H, M, -bossTime)
	local crontab_str2 = string.format("%d %d * * *", TM, TH)
	outFmtDebug("+++++++++++++++++++++++++bossTime crontab_str = %s", crontab_str2)
	self.cron:addCron("通知全服野外BOSS将要刷新", crontab_str2, function() 
		self:CallOptResult(OPERTE_TYPE_FIELD_BOSS, FIELD_BOSS_OPERTE_WILL_OCCUR, {bossTime})
	end)
end


-- 世界BOSS
function AppdApp:InitWorldBossCorn(sh, sm, enrollLast, time_last, noticeTime)
	noticeTime = noticeTime or 1
	
	local M, H
	H, M = sh, sm
	-- BOSS报名时间
	local crontab_str = string.format("%d %d * * *", M, H)
	outFmtDebug("WWWWWWWWWWWWWWWWWWWWWWWWWWorld boss enroll crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服世界BOSS开始报名", crontab_str, function()		
		OnEnrollWorldBoss()
		-- 通知全服世界BOSS开始报名
		self:CallOptResult(OPERTE_TYPE_WORLD_BOSS, WORLD_BOSS_OPERTE_ENROLL, {})
	end)
	
	-- 世界BOSS即将开始
	H, M = self:ModifyTimeMinutes(sh, sm, -noticeTime)
	crontab_str = string.format("%d %d * * *", M, H)
	outFmtDebug("WWWWWWWWWWWWWWWWWWWWWWWWWWorld boss will start crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服世界BOSS即将开启", crontab_str, function() 
		self:CallOptResult(OPERTE_TYPE_WORLD_BOSS, WORLD_BOSS_OPERTE_WILL_START, {})
	end)
	

	-- BOSS挑战时间
	H, M = self:ModifyTimeMinutes(sh, sm, enrollLast)
	crontab_str = string.format("%d %d * * *", M, H)
	outFmtDebug("WWWWWWWWWWWWWWWWWWWWWWWWWWorld boss fight crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服世界BOSS挑战", crontab_str, function() 
		-- 分配
		local playerDict, roomInfo = ArrangeWorldBossRoom()
		-- 通知场景服 进行初始化
		NoticeScene(APPD_SCENED_FIGHT_WORLD_BOSS, #playerDict)
		-- 进行传送
		DoWorldBossTeleport(playerDict, roomInfo)
		
		-- 通知全服世界BOSS挑战 分好房间, 把所有报名的人传送进去
		outFmtDebug("InitWorldBossCorn fight===============================")
	end)
	
	-- BOSS结束时间
	H, M = self:ModifyTimeMinutes(sh, sm, time_last)
	crontab_str = string.format("%d %d * * *", M, H)
	outFmtDebug("WWWWWWWWWWWWWWWWWWWWWWWWWWorld boss endddddddddddddddd crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服世界BOSS结束", crontab_str, function() 
		-- 通知场景服 BOSS结束
		NoticeScene(APPD_SCENED_WORLD_BOSS_END)
		-- 通知全服世界BOSS挑战 分好房间, 把所有报名的人传送进去
		outFmtDebug("InitWorldBossCorn end*****************************===============================")
	end)
	
end

function AppdApp:InitWorldBossCornByWeekDay(sh, sm, enrollLast, time_last, noticeTime, weekDay)
	noticeTime = noticeTime or 1
	
	local M, H
	H, M ,D = sh, sm , weekDay
	-- BOSS报名时间
	local crontab_str = string.format("%d %d * * %d", M, H, D)
	outFmtDebug("WWWWWWWWWWWWWWWWWWWWWWWWWWorld boss enroll crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服世界BOSS开始报名", crontab_str, function()		
		OnEnrollWorldBoss()
		-- 通知全服世界BOSS开始报名
		self:CallOptResult(OPERTE_TYPE_WORLD_BOSS, WORLD_BOSS_OPERTE_ENROLL, {})
	end)
	
	-- 世界BOSS即将开始
	H, M = self:ModifyTimeMinutes(sh, sm, -noticeTime)
	crontab_str = string.format("%d %d * * %d", M, H, D)
	outFmtDebug("WWWWWWWWWWWWWWWWWWWWWWWWWWorld boss will start crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服世界BOSS即将开启", crontab_str, function() 
		self:CallOptResult(OPERTE_TYPE_WORLD_BOSS, WORLD_BOSS_OPERTE_WILL_START, {})
	end)
	

	-- BOSS挑战时间
	H, M = self:ModifyTimeMinutes(sh, sm, enrollLast)
	crontab_str = string.format("%d %d * * %d", M, H, D)
	outFmtDebug("WWWWWWWWWWWWWWWWWWWWWWWWWWorld boss fight crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服世界BOSS挑战", crontab_str, function() 
		-- 分配
		local playerDict, roomInfo = ArrangeWorldBossRoom()
		-- 通知场景服 进行初始化
		NoticeScene(APPD_SCENED_FIGHT_WORLD_BOSS, #playerDict)
		-- 进行传送
		DoWorldBossTeleport(playerDict, roomInfo)
		
		-- 通知全服世界BOSS挑战 分好房间, 把所有报名的人传送进去
		outFmtDebug("InitWorldBossCorn fight===============================")
	end)
	
	-- BOSS结束时间
	H, M = self:ModifyTimeMinutes(sh, sm, time_last)
	crontab_str = string.format("%d %d * * %d", M, H, D)
	outFmtDebug("WWWWWWWWWWWWWWWWWWWWWWWWWWorld boss endddddddddddddddd crontab_str = %s", crontab_str)
	self.cron:addCron("通知全服世界BOSS结束", crontab_str, function() 
		-- 通知场景服 BOSS结束
		NoticeScene(APPD_SCENED_WORLD_BOSS_END)
		-- 通知全服世界BOSS挑战 分好房间, 把所有报名的人传送进去
		outFmtDebug("InitWorldBossCorn end*****************************===============================")
	end)
	
end

-- 分钟数改变后的实际时间
function AppdApp:ModifyTimeMinutes(H, M, addM)
	if(addM > 60 or addM < -60) then
		return H, M
	end
	M = M + addM
	if M < 0 then
		M = M + 60
		H = H - 1
		if H < 0 then
			H = 23
		end
	elseif M > 60 then
		M = M - 60
		H = H + 1
		if H > 23 then
			H = 0
		end
	end
	
	return H, M
end
-- 每日排行榜奖励
function AppdApp:RankReward()
	
	--RANK_TYPE_FACTION
	--FIXME
	local ranktype = {}--{RANK_TYPE_POWER,RANK_TYPE_LEVEL,RANK_TYPE_MOUNT,RANK_TYPE_WINGS,RANK_TYPE_SINGLE_PVP,RANK_TYPE_FACTION}
	local rankname = {"战力","等级","坐骑","翅膀","家族","排位赛"}
	
	for i,rt in ipairs(ranktype) do
		local tab = GetRankGuidTable(rt)
		for k,v in ipairs(tab) do
			local config = nil
			
			for idx = i * 10 + 1,i * 10 + 4 do
				config = tb_rank_reward[idx]
				
				if config and k >= config.level[1] and k <= config.level[2] then
					break
				else
					config = nil
				end
			end
			
			if config then
				local desc = config.desc
				local name = rankname[i]..config.name
				local giftType = 3
				if rt == RANK_TYPE_FACTION then
					local faction = app.objMgr:getObj(v)
					if faction then
						local guid = faction:GetBangZhuGuid()
						AddGiftPacksData(guid,0,giftType,os.time(),os.time() + 86400*30, name, desc, config.reward, SYSTEM_NAME)
					end
				else
					AddGiftPacksData(v,0,giftType,os.time(),os.time() + 86400*30, name, desc, config.reward, SYSTEM_NAME)
				end
				
			end
		end
	end
	
	
	
end


-- 通知场景服做某些事
function NoticeScene(typ, data, str)
	data = data or 0
	str = str or ""
	
	serverConnList:forEachScenedFD(function (fd)
		call_scened_appd_to_send_do_something(fd, "", typ, data, str)
	end)
	
end


--全服发送通知包
function AppdApp:CallNoticeAll(noticeId, passed, params)
	--[[
	local typ, reason = xxx(noticeId)
	if need(noticeId, passed) then
		self:(typ, reason, params)
	end
	--]]
end


--全服发送通知包
function AppdApp:CallOptResult(typ, reason, data)
	if type(data) == 'table' then
		data = string.join('|', data)
	else
		data = tostring(data) or ''
	end
	local pkt = protocols.pack_operation_failed(typ, reason, data)
	self:Broadcast(pkt)
	pkt:delete()
end

--发公告
function AppdApp:SendNotice( id, content, data )
	local data = data or ""
	local content = content or ""
	local pkt = protocols.pack_chat_notice(id, content, data)
	self:Broadcast(pkt)
	pkt:delete()
end

--广播包
function AppdApp:Broadcast(pkt)
	self.objMgr:foreachAllPlayer(function(player)
		player:SendPacket(pkt)
	end)
end


--全家族发送通知包
function AppdApp:SendFactionNotice(faction_guid,typ, reason, data)
	if type(data) == 'table' then
		data = string.join('|', data)
	else
		data = tostring(data) or ''
	end	
	local pkt = protocols.pack_operation_failed(typ, reason, data)
	local faction = app.objMgr:getObj(faction_guid)
	if not faction then
		return
	end
	for pos = 0, MAX_FACTION_APLLY_MAMBER_COUNT -1 do
		local guid = faction:GetFactionMemberGuid(pos)
		if guid ~= '' then
			local player = app.objMgr:getObj(guid)
			if player and player:isLogined() then
				player:SendPacket(pkt)
			end
		
		end
	end
	pkt:delete()
end


return AppdApp
