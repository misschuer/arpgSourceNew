--世界变量
local GlobalValue = class('GlobalValue', assert(BinLogObject))

local MAX_BOSS_STATE_END = 1
local MAX_BOSS_STATE_RUNNING = 0


function GlobalValue:ctor( )
end

--获取全服在线玩家数
function GlobalValue:GetQuanFuOnLinePlayerNum()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_ONLINE_PLAYER_NUM)
end

--获取当前活动版本号
function GlobalValue:GetLimitActivityVersion()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION)
end

--设置当前活动版本号
function GlobalValue:SetLimitActivityVersion(val)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION,val)
end

--获取当前活动脚本
function GlobalValue:GetLimitActivityScript()
	return self:GetStr(GLOBALVALUE_STRING_FIELD_LIMIT_ACTIVITY_SCRIPT)
end
--设置当前活动脚本
function GlobalValue:SetLimitActivityScript(val)
	self:SetStr(GLOBALVALUE_STRING_FIELD_LIMIT_ACTIVITY_SCRIPT,val)
end

--获取当前活动结束时间
function GlobalValue:GetLimitActivityEndTime()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_END_TIME)
end
--设置当前活动结束时间
function GlobalValue:SetLimitActivityEndTime(val)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_END_TIME,val)
end

--清空一些合服的时候需要清空的数据
function GlobalValue:ClearNeedClearInfo_Hefu()
	
end

-- 获得野外BOSS序号
function GlobalValue:GetFieldBossIndex(mapid, lineNo)
	local mapIndex = tb_field_boss[mapid].indx
	return mapIndex * MAX_DEFAULT_LINE_COUNT + lineNo - 1
end

-- 获得野外BOSS数据的int起始值
function GlobalValue:GetFieldBossIntStart(indx)
	return GLOBALVALUE_INT_FIELD_FIELD_BOSS_START + indx * MAX_FIELD_BOSS_INT_DATA_COUNT
end

-- 获得野外BOSS数据的str起始值
function GlobalValue:GetFieldBossStrStart(indx)
	return GLOBALVALUE_STRING_FIELD_FIELD_BOSS_START + indx * MAX_FIELD_BOSS_STR_DATA_COUNT
end


-- 重置野外boss数据
function GlobalValue:ResetFieldBoss(mapid, lineNo)
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	local strStart = self:GetFieldBossStrStart(indx)

	-- 设置倒计时
	self:SetUInt32(intStart + FIELD_BOSS_DATA_PROCESS_TYPE, FIELD_BOSS_PROCESS_START_COUNTDOWN)
	-- 即将刷新的时间
	self:SetUInt32(intStart + FIELD_BOSS_DATA_NEXT_BORN_TIME, os.time() + tb_field_boss_time[1].noticestarttime * 60)
	-- 清空优先开启时间戳
	--self:SetUInt32(intStart + FIELD_BOSS_DATA_PRIORITY_TIME, 0)
	-- 清空优先开始玩家guid
	--self:SetStr(strStart + FIELD_BOSS_DATA_MAX_DAMAGE_GUID, "")
	--self:SetStr(strStart + FIELD_BOSS_DATA_NAME, "")
end

-- 野外刷新BOSS
function GlobalValue:BornFieldBoss(mapid, lineNo)
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	
	-- 设置最近一次刷新时间
	-- 设置boss刷新
	self:SetUInt32(intStart + FIELD_BOSS_DATA_PROCESS_TYPE, FIELD_BOSS_PROCESS_BORN)
	-- 血量满
	-- self:SetDouble(intStart + FIELD_BOSS_DATA_CURR_HP, 100)
end

-- 野外BOSS受到伤害
function GlobalValue:FieldBossDamageDeal(mapid, lineNo, percent)
	--[[
	血量好像不需要存
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	
	-- 设置血量
	self:SetDouble(intStart + FIELD_BOSS_DATA_CURR_HP, percent)
	--]]
end

-- 野外BOSS死亡, 刷新箱子
function GlobalValue:FieldBossKilled(mapid, lineNo, guid, name)
	-- 一定要boss刷出来才会刷新箱子
	if not self:IsFieldBossBorn(mapid, lineNo) then
		return
	end
	
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	local strStart = self:GetFieldBossStrStart(indx)
	
	-- 血量清零
	--self:SetDouble(intStart + FIELD_BOSS_DATA_CURR_HP, 0)
	-- 设置宝箱出现
	self:SetUInt32(intStart + FIELD_BOSS_DATA_PROCESS_TYPE, FIELD_BOSS_PROCESS_TREASURE)
	-- 设置BOSS击杀次数
	self:AddUInt32(intStart + FIELD_BOSS_DATA_KILLED, 1)
	
	-- 设置优先者 和 优先时间 及其名字
	self:SetUInt32(intStart + FIELD_BOSS_DATA_PRIORITY_TIME, os.time() + 60)
	self:SetStr(strStart + FIELD_BOSS_DATA_MAX_DAMAGE_GUID, guid)
	self:SetStr(strStart + FIELD_BOSS_DATA_NAME, name)
end

function GlobalValue:GetProtectCooldown(mapid, lineNo)
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	
	local future = self:GetUInt32(intStart + FIELD_BOSS_DATA_PRIORITY_TIME)
	return future - os.time()
end


-- 箱子被领取, 活动结束
function GlobalValue:FieldBossTreasurePicked(mapid, lineNo)
	-- 一定是箱子领了才会活动结束
	if not self:IsFieldBossTreasureOccur(mapid, lineNo) then
		return
	end
	
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	
	-- 设置结束
	self:SetUInt32(intStart + FIELD_BOSS_DATA_PROCESS_TYPE, FIELD_BOSS_PROCESS_TYPE_FINISH)
end

-- 是否已经结束
function GlobalValue:IsFieldBossFinish(mapid, lineNo)
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	
	return self:GetUInt32(intStart + FIELD_BOSS_DATA_PROCESS_TYPE) == FIELD_BOSS_PROCESS_TYPE_FINISH
end

-- 是否开始倒计时
function GlobalValue:IsFieldBossCountDown(mapid, lineNo)
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	
	return self:GetUInt32(intStart + FIELD_BOSS_DATA_PROCESS_TYPE) == FIELD_BOSS_PROCESS_START_COUNTDOWN
end

-- 是否刷新BOSS
function GlobalValue:IsFieldBossBorn(mapid, lineNo)
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	
	return self:GetUInt32(intStart + FIELD_BOSS_DATA_PROCESS_TYPE) == FIELD_BOSS_PROCESS_BORN
end

-- 是否是宝箱出现
function GlobalValue:IsFieldBossTreasureOccur(mapid, lineNo)
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)
	
	return self:GetUInt32(intStart + FIELD_BOSS_DATA_PROCESS_TYPE) == FIELD_BOSS_PROCESS_TREASURE
end

-- 是否能够采集宝箱
function GlobalValue:CanPickTreasure(mapid, lineNo, guid)
	local indx = self:GetFieldBossIndex(mapid, lineNo)
	local intStart = self:GetFieldBossIntStart(indx)	
	local strStart = self:GetFieldBossStrStart(indx)
	
	-- 设置优先者 和 优先时间
	local priorityTime = self:GetUInt32(intStart + FIELD_BOSS_DATA_PRIORITY_TIME)
	local priorityGuid = self:GetStr(strStart + FIELD_BOSS_DATA_MAX_DAMAGE_GUID)
	return priorityTime < os.time() or guid == priorityGuid
end



-------------------------------世界BOSS---------------------------------

-- 获得世界BOSS的等级
function GlobalValue:GetWorldBossLevel()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_LEVEL)
end

-- 增加世界BOSS的等级
function GlobalValue:AddWorldBossLevel()
	self:AddUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_LEVEL, 1)
end

-- 获得世界BOSS的状态
function GlobalValue:GetWorldBossState()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_STATE)
end

-- 设置世界BOSS的状态
function GlobalValue:SetWorldBossState(state)
	if self:GetWorldBossState() == state then
		return
	end
	self:SetUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_STATE, state)
end

function GlobalValue:SetEnrollTime()
	if self:IsWorldBossEnroll() then
		self:SetUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_LAST_ENROLL_TIME, os.time())
	end
end

function GlobalValue:GetEnrollCountdown()
	local lastEnrollTime = self:GetUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_LAST_ENROLL_TIME)
	return tb_worldboss_time[ 1 ].enrolllast * 60 + lastEnrollTime - os.time()
end

-- 获得世界BOSS的次数
function GlobalValue:GetWorldBossTimes()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_TIMES)
end

-- 设置世界BOSS的次数
function GlobalValue:AddWorldBossTimes()
	self:AddUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_TIMES, 1)
end

-- 是否是世界BOSS结束
function GlobalValue:IsWorldBossEnd()
	return self:GetWorldBossState() == WORLD_BOSS_PROCESS_TYPE_FINISH
end

-- 是否是世界BOSS报名阶段
function GlobalValue:IsWorldBossEnroll()
	return self:GetWorldBossState() == WORLD_BOSS_PROCESS_ENROLL
end

-- 是否是世界BOSS刷新阶段
function GlobalValue:IsWorldBossBorn()
	return self:GetWorldBossState() == WORLD_BOSS_PROCESS_BORN
end

-- 世界BOSS某条线是否结束
function GlobalValue:IsWorldBossEndInLine(lineNo)
	if lineNo < 1 or lineNo >= 32 then
		return
	end
	return self:GetBit(GLOBALVALUE_INT_FIELD_WORLD_BOSS_LINE_STATE, lineNo)
end

function GlobalValue:SetWorldBossEndInLine(lineNo)
	if lineNo < 1 or lineNo >= 32 then
		return
	end
	self:SetBit(GLOBALVALUE_INT_FIELD_WORLD_BOSS_LINE_STATE, lineNo)
end

function GlobalValue:UnSetWorldBossEndInLine()
	self:SetUInt32(GLOBALVALUE_INT_FIELD_WORLD_BOSS_LINE_STATE, 0)
end

-- 设置这2天要刷的世界BOSS类型
function GlobalValue:RandomStepWorldBoss()
	outFmtDebug("RandomStepWorldBoss")
	local dict = GetRandomIndexTable(#tb_worldboss_base, 2)
	self:SetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 0, dict[ 1 ])
	self:SetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 1, dict[ 2 ])
end

-- 服务器启动的时候调用 确定有需要随机的BOSS
function GlobalValue:RandomStepWorldBossIfNeverDoes()
	local id = self:GetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 0)
	local id2 = self:GetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 1)
	if not (0 < id and id <= #tb_worldboss_base) or not (0 < id2 and id2 <= #tb_worldboss_base) then
		globalValue:RandomStepWorldBoss()
	end
	outFmtDebug("curr boss id = %d, %d", self:GetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 0), self:GetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 1))
end

-- 设置这次的BOSS ID
function GlobalValue:RandomTodayWorldBossID()
	local indx = randInt(0, 1)
	local id = self:GetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, indx)
	self:SetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 2, id)
	
	return self:GetTodayWorldBossID()
end

-- 获得今日的世界BOSSid
function GlobalValue:GetTodayWorldBossID()
	return self:GetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 2)
end

-- BOSS结束的时候调用 确定有需要随机的BOSS
function GlobalValue:RandomWorldBossIfNextStep()
	local times = self:GetWorldBossTimes()
	if times % 2 == 0 then
		globalValue:RandomStepWorldBoss()
	end
end


-- 获得今日的世界BOSS房间个数
function GlobalValue:GetTodayWorldBossRoom()
	return self:GetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 3)
end

-- 设置今日的世界BOSS房间个数
function GlobalValue:SetTodayWorldBossRoom(rooms)
	self:SetByte(GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID, 3, rooms)
end



------------------------------抽奖活动---------------------------------
--[[
#define MAX_LOTTERY_COUNT 10
#define MAX_LOTTERY_RECORD_COUNT 10

	GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START	= GLOBALVALUE_INT_FIELD_MASS_BOSS_END,		// 抽奖记录游标
	GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_END		= GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START + MAX_LOTTERY_COUNT,
	
	GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_START = GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_GUARD_NAME + 1,		// 抽奖记录数据开始
	GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_END   = GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_START + MAX_LOTTERY_COUNT * MAX_LOTTERY_RECORD_COUNT,	//
--]]

function GlobalValue:AddLotteryRecord(offset, record)
	if offset < 0 or offset >= MAX_LOTTERY_COUNT then
		return
	end
	local cursor = self:GetUInt32(GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START + offset)
	--print("GlobalValue:AddXianfuRecord", cursor, record)
	self:SetStr(cursor + GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_START + offset * MAX_LOTTERY_RECORD_COUNT, record)
	cursor = cursor + 1
	if cursor >= MAX_LOTTERY_RECORD_COUNT then
		cursor = 0
	end
	self:SetUInt32(GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START + offset, cursor)
end

------------------------------------仙府夺宝记录-----------------------------------
-- GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_START
-- MAX_XIANFU_RECORD_COUNT
-- GLOBALVALUE_INT_FIELD_XIANFU_RECORD_CURSOR

function GlobalValue:AddXianfuRecord(record)
	local cursor = self:GetUInt32(GLOBALVALUE_INT_FIELD_XIANFU_RECORD_CURSOR)
	--print("GlobalValue:AddXianfuRecord", cursor, record)
	self:SetStr(cursor + GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_START, record)
	cursor = cursor + 1
	if cursor >= MAX_XIANFU_RECORD_COUNT then
		cursor = 0
	end
	self:SetUInt32(GLOBALVALUE_INT_FIELD_XIANFU_RECORD_CURSOR, cursor)
end


function GlobalValue:doMassBossStart(id)
	local intstart = GLOBALVALUE_INT_FIELD_MASS_BOSS_START + (id - 1) * MAX_MASS_BOSS_INT_FIELD_COUNT
	self:SetUInt32(intstart + MASS_BOSS_STATE, MAX_BOSS_STATE_RUNNING)
	self:SetUInt32(intstart + MASS_BOSS_TIME ,     0)
end

function GlobalValue:doMassBossEnd(id)
	local intstart = GLOBALVALUE_INT_FIELD_MASS_BOSS_START + (id - 1) * MAX_MASS_BOSS_INT_FIELD_COUNT
	self:SetUInt32(intstart + MASS_BOSS_STATE, MAX_BOSS_STATE_END)
	local cd = tb_mass_boss_info[ id ].born * 60
	self:SetUInt32(intstart + MASS_BOSS_TIME, os.time() + cd)
end

function GlobalValue:isMassBossAlive(id)
	local intstart = GLOBALVALUE_INT_FIELD_MASS_BOSS_START + (id - 1) * MAX_MASS_BOSS_INT_FIELD_COUNT
	return self:GetUInt32(intstart + MASS_BOSS_STATE) == MAX_BOSS_STATE_RUNNING
end

function GlobalValue:checkMassBossReborn(id)
	local intstart = GLOBALVALUE_INT_FIELD_MASS_BOSS_START + (id - 1) * MAX_MASS_BOSS_INT_FIELD_COUNT
	local time = self:GetUInt32(intstart + MASS_BOSS_TIME)
	return time > 0 and os.time() >= time
end

------------------------------------------------------------------------
function GlobalValue:IsActivityRunning(actId)
	for i = GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START, GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_END-1 do
		if self:GetUInt32(i) == actId then
			return true
		end
	end
	return false
end

function GlobalValue:SetActivityRunning(actId)
	for i = GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START, GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_END-1 do
		if self:GetUInt32(i) == 0 then
			self:SetUInt32(i, actId)
			activityManagerRunning(actId)
			return
		end
	end
	globalCounter:SetActivityFinished(actId)
end

function GlobalValue:UnSetActivityRunning(actId)
	for i = GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START, GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_END-1 do
		if self:GetUInt32(i) == actId then
			self:SetUInt32(i, 0)
			return
		end
	end
end

function GlobalValue:GetActivityRunningList()
	local list = {}
	for i = GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START, GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_END-1 do
		local actId = self:GetUInt32(i)
		if actId > 0 then
			table.insert(list, actId)
		end
	end
	return list
end

--魅力排行记录信息
--[[
--上周魅力排行第一家族旗子
function GlobalValue:SetGiftRankWinerFactionFlag(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_GIFT_RANK_WINER_FACTION_FLAG ,value)
end

function GlobalValue:GetGiftRankWinerFactionFlag()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_GIFT_RANK_WINER_FACTION_FLAG)
end

--上周魅力排行第一女王名称
function GlobalValue:SetGiftRankWinerQueenName(value)
	self:SetStr(GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_QUEEN_NAME ,value)
end

function GlobalValue:GetGiftRankWinerQueenName()
	return self:GetStr(GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_QUEEN_NAME)
end

--上周魅力排行第一家族名称
function GlobalValue:SetGiftRankWinerFactionName(value)
	self:SetStr(GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_FACTION_NAME,value)
end

function GlobalValue:GetGiftRankWinerFactionName()
	return self:GetStr(GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_FACTION_NAME)
end

--上周魅力排行第一骑士名称
function GlobalValue:SetGiftRankWinerGuardName(value)
	self:SetStr(GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_GUARD_NAME,value)
end

function GlobalValue:GetGiftRankWinerGuardName()
	return self:GetStr(GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_GUARD_NAME)
end


--帮派魅力排行奖励下一结算时间
function GlobalValue:GetFactionGiftRankNextUpdateTime()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_GIFT_RANK_NEXT_UPDATE_TIME)
end

function GlobalValue:SetFactionGiftRankNextUpdateTime(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_GIFT_RANK_NEXT_UPDATE_TIME,value)
end

--帮派魅力排行当前轮数
function GlobalValue:GetFactionGiftRankCurRound()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_GIFT_RANK_CUR_ROUND)
end

function GlobalValue:SetFactionGiftRankCurRound(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_GIFT_RANK_CUR_ROUND,value)
end

function GlobalValue:AddFactionGiftRankCurRound(value)
	self:AddUInt32(GLOBALVALUE_INT_FIELD_GIFT_RANK_CUR_ROUND,value)
end




--帮派魅力排行奖励下一结算时间重置
function GlobalValue:UpdateFactionGiftRank()
	if os.time() >= self:GetFactionGiftRankNextUpdateTime() then
		local update_cycle = tb_faction_gift_rank_base[1].update_cycle
		self:SetFactionGiftRankNextUpdateTime(GetTodayStartTimestamp() + update_cycle * 86400)
		self:AddFactionGiftRankCurRound(1)
	end
end
--]]

-----------------------------------------------------------------------
--家族战过程数据

function GlobalValue:SetFactionMatchGames(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_GAMES,value)
end

function GlobalValue:GetFactionMatchGames()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_GAMES)
end

function GlobalValue:SetFactionMatchCurrentsPhase(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CURRENT_PHASE,value)
end

function GlobalValue:GetFactionMatchCurrentsPhase()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CURRENT_PHASE)
end

function GlobalValue:SetFactionMatchNextTime(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_NEXT_TIME,value)
end

function GlobalValue:GetFactionMatchNextTime()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_NEXT_TIME)
end

function GlobalValue:SetFactionMatchChampionWinstrikeCount(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_WINSTRIKE_COUNT,value)
end

function GlobalValue:GetFactionMatchChampionWinstrikeCount()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_WINSTRIKE_COUNT)
end

function GlobalValue:SetFactionMatchChampionFactionGuid(value)
	self:SetStr(GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_FACTION_GUID,value)
end

function GlobalValue:GetFactionMatchChampionFactionGuid()
	return self:GetStr(GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_FACTION_GUID)
end

function GlobalValue:SetFactionMatchChampionFactionName(value)
	self:SetStr(GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_FACTION_NAME,value)
end

function GlobalValue:GetFactionMatchChampionFactionName()
	return self:GetStr(GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_FACTION_NAME)
end

function GlobalValue:SetFactionMatchChampionBangZhuGuid(value)
	self:SetStr(GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_GUID,value)
end

function GlobalValue:GetFactionMatchChampionBangZhuGuid()
	return self:GetStr(GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_GUID)
end

function GlobalValue:SetFactionMatchChampionBangZhuName(value)
	self:SetStr(GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_NAME,value)
end

function GlobalValue:GetFactionMatchChampionBangZhuName()
	return self:GetStr(GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_NAME)
end

function GlobalValue:SetFactionMatchChampionBangZhuGender(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_GENDER,value)
end

function GlobalValue:GetFactionMatchChampionBangZhuGender()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_GENDER)
end

function GlobalValue:SetFactionMatchChampionBangZhuCoat(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_COAT,value)
end

function GlobalValue:GetFactionMatchChampionBangZhuCoat()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_COAT)
end

function GlobalValue:SetFactionMatchChampionBangZhuWeapon(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_WEAPON,value)
end

function GlobalValue:GetFactionMatchChampionBangZhuWeapon()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_WEAPON)
end

function GlobalValue:SetFactionMatchChampionBangZhuWingsId(value)
	self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_WINGSID,value)
end

function GlobalValue:GetFactionMatchChampionBangZhuWingsId()
	return self:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_WINGSID)
end


--开始本届比赛

function GlobalValue:StartFactionMatch()
	--设置轮数增加
	if  self:GetFactionMatchCurrentsPhase() ~= 0 then
		return
	end
	self:SetFactionMatchGames(self:GetFactionMatchGames() + 1)
	--设置阶段为1
	self:SetFactionMatchCurrentsPhase(1)
	
	--设置更新时间
	local time = tb_faction_match_phase[1].time
	self:SetFactionMatchNextTime(os.time() + time )
	--self:SetFactionMatchNextTime(os.time() + 60 )
	--执行阶段1
	self:HandleFactionMatchScripts(1)
end


--更新阶段阶段
function GlobalValue:UpdateFactionMatch()
	--判断时间
	local phaseId = self:GetFactionMatchCurrentsPhase()
	self:UpdateFactionMatchFlagScore(phaseId)
	
	if phaseId > 0 and os.time() > self:GetFactionMatchNextTime() then
		phaseId = phaseId + 1
		if tb_faction_match_phase[phaseId] then
			local time = tb_faction_match_phase[phaseId].time
			self:SetFactionMatchCurrentsPhase(phaseId)
			self:SetFactionMatchNextTime(os.time() + time )
			--self:SetFactionMatchNextTime(os.time() + 60 )
			self:HandleFactionMatchScripts(phaseId)
		else
			self:SetFactionMatchCurrentsPhase(0)
			self:SetFactionMatchNextTime(0)
			self:UpdateFactionMatchStartTime()
		end
	end
end

--执行脚本
function GlobalValue:HandleFactionMatchScripts(phaseId)
	local script = tb_faction_match_phase[phaseId].script
	local games = self:GetFactionMatchGames()
	outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts games %d ",games)
	if script == FACTION_MATCH_SCRIPT_TYPE_INIT then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 1 ",phaseId)
		--初始化 新排行 或 继承排行
		self:InitFactionMatchInfo()
	elseif script == FACTION_MATCH_SCRIPT_TYPE_UPDATE then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 2 ",phaseId)
		--更新排行 新排行 或 继承排行
		self:UpdateFactionMatchInfo()
	elseif script == FACTION_MATCH_SCRIPT_TYPE_DECIDE_FIRST then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 3 ",phaseId)
		--决定第一轮对战信息
		self:DecideFactionMatchFirstDetailInfo()
	elseif script == FACTION_MATCH_SCRIPT_TYPE_OPEN_FIRST then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 4 ",phaseId)
		--允许进入第一轮战场
		self:OpenFactionMatchFirstRound()
		
		local time1 = tb_faction_match_phase[phaseId].time
		self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_SATRT_TIME,os.time()+ time1)
		
		local time2 = tb_faction_match_phase[phaseId + 1].time
		self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_END_TIME,os.time()+ time1 + time2)
		
	elseif script == FACTION_MATCH_SCRIPT_TYPE_START_FIRST then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 5 ",phaseId)
		--开始第一轮比赛 判断弃权 / 轮空 情况
		self:StartFactionMatchFirstRound()
	elseif script == FACTION_MATCH_SCRIPT_TYPE_END_FIRST then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 6 ",phaseId)
		--第一轮结算 决定第二轮对战信息
		self:EndFactionMatchFirstRound()
		self:DecideFactionMatchSecondDetailInfo()
	elseif script == FACTION_MATCH_SCRIPT_TYPE_OPEN_SECOND then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 7 ",phaseId)
		--允许进入第二轮战场
		self:OpenFactionMatchSecondRound()
		
		local time1 = tb_faction_match_phase[phaseId].time
		self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_SATRT_TIME,os.time()+ time1)
		
		local time2 = tb_faction_match_phase[phaseId + 1].time
		self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_END_TIME,os.time()+ time1 + time2)
		
	elseif script == FACTION_MATCH_SCRIPT_TYPE_START_SECOND then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 8 ",phaseId)
		--开始第二轮比赛 判断弃权 / 轮空 情况
		self:StartFactionMatchSecondRound()
	elseif script == FACTION_MATCH_SCRIPT_TYPE_END_SECOND then
		outFmtDebug("@@@@@@@@@@@@@@@@@@@@@@@@HandleFactionMatchScripts phaseId %d script 9 ",phaseId)
		--第二轮结算 进行结束处理
		self:EndFactionMatchSecondRound()
		self:FinishFactionMatch()
	end
end

--清空家族战全部信息
function GlobalValue:ClearAllFactionMatch()
	self:SetFactionMatchGames(0)
	self:SetFactionMatchCurrentsPhase(0)
	self:SetFactionMatchNextTime(0)
	
	globalCounter:ClearFactionMatchInfo()
	globalCounter:ClearFactionMatchDetailInfo()
	self:ClearFactionMatchChampionInfo()
end

function GlobalValue:ClearFactionMatchChampionInfo()
	self:SetFactionMatchChampionWinstrikeCount(0)
	self:SetFactionMatchChampionFactionGuid("")
	self:SetFactionMatchChampionBangZhuGuid("")
	self:SetFactionMatchChampionFactionName("")
	self:SetFactionMatchChampionBangZhuName("")
		
	self:SetFactionMatchChampionBangZhuCoat(0)
	self:SetFactionMatchChampionBangZhuWeapon(0)
	self:SetFactionMatchChampionBangZhuGender(0)
	self:SetFactionMatchChampionBangZhuWingsId(0)

end

function GlobalValue:GetFactionMatchInfoTable()
	local phaseId = self:GetFactionMatchCurrentsPhase()
	local script = 0
	if phaseId ~= 0 then
		script = tb_faction_match_phase[phaseId].script
	else
		script = FACTION_MATCH_SCRIPT_TYPE_NONE
	end
	
	local list = {}
	if script == FACTION_MATCH_SCRIPT_TYPE_INIT or script == FACTION_MATCH_SCRIPT_TYPE_UPDATE then
		for i = 0,19 do
			local name = globalCounter:GetFactionMatchInfoName(i)
			local guid = globalCounter:GetFactionMatchInfoGuid(i)
			table.insert(list,{name,0,0,guid})
		end
		
	elseif script == FACTION_MATCH_SCRIPT_TYPE_DECIDE_FIRST or script == FACTION_MATCH_SCRIPT_TYPE_OPEN_FIRST or script == FACTION_MATCH_SCRIPT_TYPE_START_FIRST then
		for i = 0,9 do
			local matchId_1 = globalCounter:GetFactionMatchDetailInfoMatchId1(i)
			local matchId_2 = globalCounter:GetFactionMatchDetailInfoMatchId2(i)
	
			local name1 = globalCounter:GetFactionMatchInfoName(matchId_1)
			local name2 = globalCounter:GetFactionMatchInfoName(matchId_2)
			local result1 = globalCounter:GetFactionMatchDetailInfoMatchResult1(i)
			local result2 = globalCounter:GetFactionMatchDetailInfoMatchResult2(i)
			local guid1 = globalCounter:GetFactionMatchInfoGuid(matchId_1)
			local guid2 = globalCounter:GetFactionMatchInfoGuid(matchId_2)
			table.insert(list,{name1,result1,0,guid1})
			table.insert(list,{name2,result2,0,guid2})
		end
		
	elseif script == FACTION_MATCH_SCRIPT_TYPE_END_FIRST or script == FACTION_MATCH_SCRIPT_TYPE_OPEN_SECOND or script == FACTION_MATCH_SCRIPT_TYPE_START_SECOND then
		for i = 10,19 do
			local matchId_1 = globalCounter:GetFactionMatchDetailInfoMatchId1(i)
			local matchId_2 = globalCounter:GetFactionMatchDetailInfoMatchId2(i)
	
			local name1 = globalCounter:GetFactionMatchInfoName(matchId_1)
			local name2 = globalCounter:GetFactionMatchInfoName(matchId_2)
			local result1 = globalCounter:GetFactionMatchDetailInfoMatchResult1(i)
			local result2 = globalCounter:GetFactionMatchDetailInfoMatchResult2(i)
			local guid1 = globalCounter:GetFactionMatchInfoGuid(matchId_1)
			local guid2 = globalCounter:GetFactionMatchInfoGuid(matchId_2)
			table.insert(list,{name1,result1,0,guid1})
			table.insert(list,{name2,result2,0,guid2})
		end
		
	elseif script == FACTION_MATCH_SCRIPT_TYPE_END_SECOND or script == FACTION_MATCH_SCRIPT_TYPE_NONE then
		for i = 0,19 do
			local name = globalCounter:GetFactionMatchInfoName(i)
			local rank = globalCounter:GetFactionMatchInfoResultRank(i)
			local guid = globalCounter:GetFactionMatchInfoGuid(i)
			table.insert(list,{name,0,rank,guid})
		end
		
	end
	
	return list
end


--判断能否进入比赛场景 返回 detailId,teamId
function GlobalValue:CheckCanEnterFactionMatchMap(playerInfo)
	--是否处于比赛时间
	local phaseId = self:GetFactionMatchCurrentsPhase()
	if phaseId == 0 then
		return false
	end
	
	local script = tb_faction_match_phase[phaseId].script
	
	if script == FACTION_MATCH_SCRIPT_TYPE_OPEN_FIRST or script ==  FACTION_MATCH_SCRIPT_TYPE_START_FIRST then
		for i = 0,19 do
			local guid = globalCounter:GetFactionMatchInfoGuid(i)
			if guid == playerInfo:GetFactionId() then--是否在参赛帮派中
				local detailId = globalCounter:GetFactionMatchInfoFirstDetailId(i) --第一轮
				if globalCounter:GetFactionMatchDetailInfoMatchResult1(detailId) == 0 then --是否未决定胜负
					if i == globalCounter:GetFactionMatchDetailInfoMatchId1(detailId) then --队伍1 还是 队伍2
						return true, detailId,1
					else
						return true, detailId,2
					end
				end
			end
		end
	elseif script ==  FACTION_MATCH_SCRIPT_TYPE_OPEN_SECOND or script == FACTION_MATCH_SCRIPT_TYPE_START_SECOND then
		for i = 0,19 do
			local guid = globalCounter:GetFactionMatchInfoGuid(i)
			if guid == playerInfo:GetFactionId() then--是否在参赛帮派中
				local detailId = globalCounter:GetFactionMatchInfoSecondDetailId(i)  --第二轮
				if globalCounter:GetFactionMatchDetailInfoMatchResult1(detailId) == 0 then --是否未决定胜负
					if i == globalCounter:GetFactionMatchDetailInfoMatchId1(detailId) then --队伍1 还是 队伍2
						return true, detailId,1
					else
						return true, detailId,2
					end
				end
			end
		end
	end
	
	return false
end

--修改旗子归属
function GlobalValue:CheckChangeFactionMatchFlagBelong(detailId,team_id,flag_id)
	local phaseId = self:GetFactionMatchCurrentsPhase()
	if phaseId == 0 then
		return false
	end
	
	local script = tb_faction_match_phase[phaseId].script
	
	if script ==  FACTION_MATCH_SCRIPT_TYPE_START_FIRST or script == FACTION_MATCH_SCRIPT_TYPE_START_SECOND then
		if globalCounter:GetFactionMatchDetailInfoMatchResult1(detailId) == 0 then
			if not globalCounter:GetFactionMatchDetailInfoFlag1(detailId,flag_id) and not globalCounter:GetFactionMatchDetailInfoFlag2(detailId,flag_id) then	--旗子中立
				if team_id == 1 then
					globalCounter:SetFactionMatchDetailInfoFlag1(detailId,flag_id)
					globalCounter:UnSetFactionMatchDetailInfoFlag2(detailId,flag_id)
					return true
				elseif team_id == 2 then
					globalCounter:SetFactionMatchDetailInfoFlag2(detailId,flag_id)
					globalCounter:UnSetFactionMatchDetailInfoFlag1(detailId,flag_id)
					return true
				end
			elseif globalCounter:GetFactionMatchDetailInfoFlag1(detailId,flag_id) then --旗子属于队伍1
				if team_id == 2 then
					globalCounter:SetFactionMatchDetailInfoFlag2(detailId,flag_id)
					globalCounter:UnSetFactionMatchDetailInfoFlag1(detailId,flag_id)
					return true
				end
			elseif globalCounter:GetFactionMatchDetailInfoFlag2(detailId,flag_id) then --旗子属于队伍2
				if team_id == 1 then
					globalCounter:SetFactionMatchDetailInfoFlag1(detailId,flag_id)
					globalCounter:UnSetFactionMatchDetailInfoFlag2(detailId,flag_id)
					return true
				end
			end
		end
	end
end

--终结连胜奖励
function GlobalValue:SendFactionMatchTerminateWinstrikeReward(id)
	local winstrike = self:GetFactionMatchChampionWinstrikeCount()
	if winstrike > 1 then
		local guid = globalCounter:GetFactionMatchInfoGuid(id)
		if guid ~= "" then
			outFmtDebug("@@@@@11111SendFactionMatchTerminateWinstrikeReward id %d guid %s defeat champion winstrike reward",id,guid)
			local config = tb_faction_match_winstrike[winstrike]
			if not config then
				config = tb_faction_match_winstrike[30]
			end
			
			local faction = app.objMgr:getObj(guid)
			if faction then
				local mail_name = config.terminate_mail_name
				local mail_desc = config.terminate_mail_desc
				local item_str = itemListToItemString(config.terminateReward)
				for i=0, MAX_FACTION_MAMBER_COUNT - 1 do
					local Guid = faction:GetFactionMemberGuid(i)
					if Guid ~= "" and Guid ~= nil then
						AddGiftPacksData(Guid,0,4,os.time(),os.time() + 86400*30, mail_name, mail_desc,item_str, SYSTEM_NAME)
--[[					if donate > 0 then
							local pos = faction:FindPlayerIndex(Guid)
							faction:AddFactionMemberDayGongXian(pos,donate)
							faction:AddFactionMemberTotalGongXian(pos,donate)
						end--]]
					end
					
				end
			end
			
			
		end
	end
end

--连胜奖励
function GlobalValue:SendFactionMatchWinstrikeReward(guid,count)
	if guid ~= "" then
		outFmtDebug("@@@@@22222SendFactionMatchWinstrikeReward guid %s count %d winstrike",guid,count)
		local config = tb_faction_match_winstrike[count]
		if not config then
			config = tb_faction_match_winstrike[30]
		end
		
		local faction = app.objMgr:getObj(guid)
		if faction then
			local mail_name = config.win_mail_name
			local mail_desc = config.win_mail_desc
			local item_str = itemListToItemString(config.winReward)
			for i=0, MAX_FACTION_MAMBER_COUNT - 1 do
				local Guid = faction:GetFactionMemberGuid(i)
				if Guid ~= "" and Guid ~= nil then
					AddGiftPacksData(Guid,0,4,os.time(),os.time() + 86400*30, mail_name, mail_desc,item_str, SYSTEM_NAME)
--[[					if donate > 0 then
						local pos = faction:FindPlayerIndex(Guid)
						faction:AddFactionMemberDayGongXian(pos,donate)
						faction:AddFactionMemberTotalGongXian(pos,donate)
					end--]]
				end
				
			end
		end
		
	end
end

--排行奖励
function GlobalValue:SendFactionMatchRankReward(guid,rank)
	if guid ~= "" then
		outFmtDebug("@@@@@33333SendFactionMatchRankReward guid %s rank %d reward",guid,rank)
		local config = tb_faction_match_rank_reward[rank]
		if not config then
			return
		end
		
		local faction = app.objMgr:getObj(guid)
		if faction then
			local mail_name = config.mail_name
			local mail_desc = config.mail_desc
			local item_str = itemListToItemString(config.memberReward)
			for i=0, MAX_FACTION_MAMBER_COUNT - 1 do
				local Guid = faction:GetFactionMemberGuid(i)
				if Guid ~= "" and Guid ~= nil then
					AddGiftPacksData(Guid,0,4,os.time(),os.time() + 86400*30, mail_name, mail_desc,item_str, SYSTEM_NAME)
--[[					if donate > 0 then
						local pos = faction:FindPlayerIndex(Guid)
						faction:AddFactionMemberDayGongXian(pos,donate)
						faction:AddFactionMemberTotalGongXian(pos,donate)
					end--]]
				end
				
			end
			
			if rank == 1 then
				local champion_config = tb_faction_match_champion[1]
				local mail_name = champion_config.mail_name
				local mail_desc = champion_config.mail_desc
				local item_str = itemListToItemString(champion_config.championReward)
				
				local Guid = faction:GetBangZhuGuid()
				if Guid ~= "" and Guid ~= nil then
					AddGiftPacksData(Guid,0,4,os.time(),os.time() + 86400*30, mail_name, mail_desc,item_str, SYSTEM_NAME)
--[[				if donate > 0 then
						local pos = faction:FindPlayerIndex(Guid)
						faction:AddFactionMemberDayGongXian(pos,donate)
						faction:AddFactionMemberTotalGongXian(pos,donate)
					end--]]
				end
				
			end
			
			if rank == 1 then
				app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_FINISH,{getShowName(faction:GetName()),"S"})
			elseif rank == 5 then
				app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_FINISH,{getShowName(faction:GetName()),"A"})
			elseif rank == 9 then
				app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_FINISH,{getShowName(faction:GetName()),"B"})
			elseif rank == 13 then
				app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_FINISH,{getShowName(faction:GetName()),"C"})
			elseif rank == 17 then
				app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_FINISH,{getShowName(faction:GetName()),"D"})
			end
		end
		
	end
end

function GlobalValue:PrintFactionMatchInfo()
	for i = 1,20 do
			
		local guid = 	globalCounter:GetFactionMatchInfoGuid(i - 1)
		local name = 	globalCounter:GetFactionMatchInfoName(i - 1)
		local first = 	globalCounter:GetFactionMatchInfoFirstDetailId(i - 1)
		local second = 	globalCounter:GetFactionMatchInfoSecondDetailId(i - 1)
		local rank = 	globalCounter:GetFactionMatchInfoResultRank(i - 1)
			
		outFmtDebug("###########PrintFactionMatchInfo rank %d , guid %s, name %s,first %d , second %d, rank %d",i,guid,name,first,second,rank)
	end
end
		
--初始化 新排行 或 继承排行
function GlobalValue:InitFactionMatchInfo()
	local games = self:GetFactionMatchGames()
	local faction_rank_table = {}
	local tab = GetRankGuidTable(RANK_TYPE_FACTION)
	for i = 1,20 do
		local guid = tab[i]
		if guid then
			outFmtDebug("InitFactionMatchInfo %s ",guid)
			local faction = app.objMgr:getObj(guid)
			if faction then
				faction_rank_table[guid] = faction:GetName()
			else
				tab[i] = nil
			end
		end
	end
	
	if games == 1 then
		--首届比赛
		for i = 1,20 do
			if tab[i] then
				globalCounter:SetFactionMatchInfoGuid(i - 1,tab[i])
				globalCounter:SetFactionMatchInfoName(i - 1,faction_rank_table[tab[i]])
				globalCounter:SetFactionMatchInfoFirstDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoSecondDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoResultRank(i - 1,0)
				
				outFmtDebug("###########InitFactionMatchInfo add info rank %d , guid %s, name %s",i,tab[i],faction_rank_table[tab[i]])
			else
				globalCounter:SetFactionMatchInfoGuid(i - 1,"")
				globalCounter:SetFactionMatchInfoName(i - 1,"")
				globalCounter:SetFactionMatchInfoFirstDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoSecondDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoResultRank(i - 1,0)
				
				outFmtDebug("###########InitFactionMatchInfo add info rank %d , guid nil, name nil",i)
			end
		end
		
		
	else
		local match_rank = {}
		local match_rank_guid = {}
		for i = 0, 19 do
			local guid = globalCounter:GetFactionMatchInfoGuid(i)
			local rank = globalCounter:GetFactionMatchInfoResultRank(i)
			match_rank[rank] = guid
		end
		
		--升阶 降阶
		for i = 4,16,4 do
			local temp = match_rank[i]
			match_rank[i] = match_rank[i + 1]
			match_rank[i + 1] = temp
		end
		
		--继承上届 前16名
		for i = 1 ,16 do
			if match_rank[i] ~= "" then
				match_rank_guid[match_rank[i]] = i
				globalCounter:SetFactionMatchInfoGuid(i - 1,match_rank[i])
				local faction = app.objMgr:getObj(match_rank[i])
				globalCounter:SetFactionMatchInfoName(i - 1,faction:GetName())
				globalCounter:SetFactionMatchInfoFirstDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoSecondDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoResultRank(i - 1,0)
				
				outFmtDebug("###########InitFactionMatchInfo add info rank %d , guid %s, name %s",i,match_rank[i],faction:GetName())
			else
				globalCounter:SetFactionMatchInfoGuid(i - 1,"")
				globalCounter:SetFactionMatchInfoName(i - 1,"")
				globalCounter:SetFactionMatchInfoFirstDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoSecondDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoResultRank(i - 1,0)
				outFmtDebug("###########InitFactionMatchInfo add info rank %d , guid nil, name nil",i)
			end
		end
		
		--选出 前16名以外的战力前四名
		local index_update = 17
		local index_update_end = 20
		
		for i = 1,20 do
			if tab[i] then
				if match_rank_guid[tab[i]] then
					--Pass 
					outFmtDebug("###########InitFactionMatchInfo guid %s already in match rank",tab[i])
				else
					if index_update <= index_update_end then
						globalCounter:SetFactionMatchInfoGuid(index_update - 1,tab[i])
						globalCounter:SetFactionMatchInfoName(index_update - 1,faction_rank_table[tab[i]])
						globalCounter:SetFactionMatchInfoFirstDetailId(index_update - 1,0)
						globalCounter:SetFactionMatchInfoSecondDetailId(index_update - 1,0)
						globalCounter:SetFactionMatchInfoResultRank(index_update - 1,0)
						outFmtDebug("###########InitFactionMatchInfo add info rank %d , guid %s, name %s",index_update,tab[i],faction_rank_table[tab[i]])
						index_update = index_update + 1
					end
					
				end
			end
			
			
		end
		--补空位
		for i = index_update,index_update_end do
			globalCounter:SetFactionMatchInfoGuid(i - 1,"")
			globalCounter:SetFactionMatchInfoName(i - 1,"")
			globalCounter:SetFactionMatchInfoFirstDetailId(i - 1,0)
			globalCounter:SetFactionMatchInfoSecondDetailId(i - 1,0)
			globalCounter:SetFactionMatchInfoResultRank(i - 1,0)
			
			outFmtDebug("###########InitFactionMatchInfo add info rank %d , guid nil, name nil",i)
			
		end
		
	end
	
	globalCounter:ClearFactionMatchDetailInfo()
end

--更新排行 新排行 或 继承排行
function GlobalValue:UpdateFactionMatchInfo()
	local games = self:GetFactionMatchGames()
	local faction_rank_table = {}
	local tab = GetRankGuidTable(RANK_TYPE_FACTION)
	for i = 1,20 do
		local guid = tab[i]
		if guid then
			local faction = app.objMgr:getObj(guid)
			if faction then
				faction_rank_table[guid] = faction:GetName()
			else
				tab[i] = nil
			end
		end
	end
	if games == 1 then
		--首届比赛
		for i = 1,20 do
			if tab[i] then
				globalCounter:SetFactionMatchInfoGuid(i - 1,tab[i])
				globalCounter:SetFactionMatchInfoName(i - 1,faction_rank_table[tab[i]])
				globalCounter:SetFactionMatchInfoFirstDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoSecondDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoResultRank(i - 1,0)
				
				outFmtDebug("###########UpdateFactionMatchInfo add info rank %d , guid %s, name %s",i,tab[i],faction_rank_table[tab[i]])
			else
				globalCounter:SetFactionMatchInfoGuid(i - 1,"")
				globalCounter:SetFactionMatchInfoName(i - 1,"")
				globalCounter:SetFactionMatchInfoFirstDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoSecondDetailId(i - 1,0)
				globalCounter:SetFactionMatchInfoResultRank(i - 1,0)
				
				outFmtDebug("###########UpdateFactionMatchInfo add info rank %d , guid nil, name nil",i)
			end
		end
	else
		--选出 前16名以外的战力前四名
		local match_rank_guid = {}
		for i = 1 ,16 do
			local guid = globalCounter:GetFactionMatchInfoGuid(i - 1)
			if guid ~= "" then
				match_rank_guid[guid] = i
			end
		end
		
		local index_update = 17
		local index_update_end = 20
		
		for i = 1,20 do
			if tab[i] then
				if match_rank_guid[tab[i]] then
					--Pass 
					outFmtDebug("###########UpdateFactionMatchInfo guid %s already in match rank",tab[i])
				else
					if index_update <= index_update_end then
						globalCounter:SetFactionMatchInfoGuid(index_update - 1,tab[i])
						globalCounter:SetFactionMatchInfoName(index_update - 1,faction_rank_table[tab[i]])
						globalCounter:SetFactionMatchInfoFirstDetailId(index_update - 1,0)
						globalCounter:SetFactionMatchInfoSecondDetailId(index_update - 1,0)
						globalCounter:SetFactionMatchInfoResultRank(index_update - 1,0)
						outFmtDebug("###########UpdateFactionMatchInfo add info rank %d , guid %s, name %s",index_update,tab[i],faction_rank_table[tab[i]])
						index_update = index_update + 1
					end
					
				end
			end
			
			
		end
		--补空位
		for i = index_update,index_update_end do
			globalCounter:SetFactionMatchInfoGuid(i - 1,"")
			globalCounter:SetFactionMatchInfoName(i - 1,"")
			globalCounter:SetFactionMatchInfoFirstDetailId(i - 1,0)
			globalCounter:SetFactionMatchInfoSecondDetailId(i - 1,0)
			globalCounter:SetFactionMatchInfoResultRank(i - 1,0)
			
			outFmtDebug("###########UpdateFactionMatchInfo add info rank %d , guid nil, name nil",i)
			
		end
	end
end

--决定第一轮对战信息
function GlobalValue:DecideFactionMatchFirstDetailInfo()
	local index = 0
	for group = 0, 4 do
		local list = GetRandomIndexTable(4,4)
		for i = 0,1 do
			local id_1 = group * 4 + list[i * 2 + 1] - 1
			local id_2 = group * 4 + list[i * 2 + 2] - 1
			
			globalCounter:AddFactionMatchDetailInfo(index,1,id_1)
			globalCounter:AddFactionMatchDetailInfo(index,2,id_2)
			
			outFmtDebug("###########DecideFactionMatchFirstDetailInfo detail index %d , id_1 %d , id_2 %d ",index,id_1,id_2)
			
			index = index + 1
			
		end
	end
	
	app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_DECIDE_FIRST,{})
end

--允许进入第一轮战场
function GlobalValue:OpenFactionMatchFirstRound()
	self:PrintFactionMatchInfo()
	for index = 0 , 9 do
		local guid_1 ,guid_2 = globalCounter:GetFactionMatchFactionGuidByDetailIndex(index)
		if guid_1 ~= "" and guid_2 ~= "" then
			outFmtDebug("###########OpenFactionMatchFirstRound index %d , team 1 ,team 2 all exist",index)
		elseif guid_1 ~= "" then
			globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
			globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
			
			outFmtDebug("###########OpenFactionMatchFirstRound index %d , team 1 win ,team 2 not exist",index)
		elseif guid_2 ~= "" then
			globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
			globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
			
			outFmtDebug("###########OpenFactionMatchFirstRound index %d , team 2 win ,team 1 not exist",index)
		else
			globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
			globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
			
			outFmtDebug("###########OpenFactionMatchFirstRound index %d , team 1 win ,team 1 team 2 not exist",index)
		end
	end
	
	app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_OPEN_FIRST,{})
end

--开始第一轮比赛 判断弃权 / 轮空 情况
function GlobalValue:StartFactionMatchFirstRound()
	local min_member_need = tb_faction_match_base[1].min_member_need	
	
	for index = 0 , 9 do
		local guid_1 ,guid_2 = globalCounter:GetFactionMatchFactionGuidByDetailIndex(index)
		if guid_1 ~= "" and guid_2 ~= "" then
			local count_1 = globalCounter:GetFactionMatchDetailInfoMemberCount1(index)
			local count_2 = globalCounter:GetFactionMatchDetailInfoMemberCount2(index)
			
			if count_1 >= min_member_need and count_2 < min_member_need then
				globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
				globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
				outFmtDebug("###########StartFactionMatchFirstRound index %d , team 1 win ,team 2 not join enough",index)

			elseif count_2 >= min_member_need and count_1 < min_member_need then
				globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
				globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
				outFmtDebug("###########StartFactionMatchFirstRound index %d , team 2 win ,team 1 not join enough",index)

			elseif count_1 < min_member_need and count_2 < min_member_need then
				local faction_1 = app.objMgr:getObj(guid_1)
				local faction_2 = app.objMgr:getObj(guid_2)
				if faction_1:GetDouble(FACTION_INT_FIELD_TOTAL_FORCE) >= faction_2:GetDouble(FACTION_INT_FIELD_TOTAL_FORCE) then
					globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
					globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
					
					outFmtDebug("###########StartFactionMatchFirstRound index %d , team 1 win ,team 2 force lower",index)
				else
					globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
					globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
					outFmtDebug("###########StartFactionMatchFirstRound index %d , team 2 win ,team 1 force lower",index)
				end
			end
		end
	end
	
	--开始计数占点分数 分值到达2000判定输赢
	
	app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_START_FIRST,{})
end



--第一轮结算 --判断超时输赢
function GlobalValue:EndFactionMatchFirstRound()
	--停止计数占点分数
	
	--超时根据分数判断胜利
	for index = 0 , 9 do
		if globalCounter:GetFactionMatchDetailInfoMatchResult1(index) == 0 and globalCounter:GetFactionMatchDetailInfoMatchResult2(index) == 0 then
			local score_1 = globalCounter:GetFactionMatchDetailInfoScore1(index)
			local score_2 = globalCounter:GetFactionMatchDetailInfoScore2(index)
			
			if score_1 >= score_2 then
				globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
				globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
				
				outFmtDebug("###########EndFactionMatchFirstRound index %d , team 1 win ,team 2 score lower",index)

			elseif score_1 < score_2 then
				globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
				globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
				
				outFmtDebug("###########EndFactionMatchFirstRound index %d , team 2 win ,team 1 score lower",index)
			end
		end
		
	end
	
	
end

--决定第二轮对战信息
function GlobalValue:DecideFactionMatchSecondDetailInfo()
	for index = 0 , 8 , 2 do
		local matchId_1 = globalCounter:GetFactionMatchDetailInfoMatchId1(index)
		local matchId_2 = globalCounter:GetFactionMatchDetailInfoMatchId2(index)
		
		local result = globalCounter:GetFactionMatchDetailInfoMatchResult1(index)
		local win_index = 10 + index
		local lose_index = 11 + index
		if result == FACTION_MATCH_RESULT_TYPE_WIN then
			globalCounter:AddFactionMatchDetailInfo(win_index,1,matchId_1)
			globalCounter:AddFactionMatchDetailInfo(lose_index,1,matchId_2)
			
			outFmtDebug("###########DecideFactionMatchSecondDetailInfo detail win_index %d , id_1 %d ",win_index,matchId_1)
			outFmtDebug("###########DecideFactionMatchSecondDetailInfo detail lose_index %d , id_1 %d ",lose_index,matchId_2)
			
			if matchId_2 == 0 then --判断连胜终结
				self:SendFactionMatchTerminateWinstrikeReward(matchId_1)
			end
		elseif result == FACTION_MATCH_RESULT_TYPE_LOSE then
			globalCounter:AddFactionMatchDetailInfo(win_index,1,matchId_2)
			globalCounter:AddFactionMatchDetailInfo(lose_index,1,matchId_1)
			
			outFmtDebug("###########DecideFactionMatchSecondDetailInfo detail win_index %d , id_1 %d ",win_index,matchId_2)
			outFmtDebug("###########DecideFactionMatchSecondDetailInfo detail lose_index %d , id_1 %d ",lose_index,matchId_1)
			
			if matchId_1 == 0 then --判断连胜终结
				self:SendFactionMatchTerminateWinstrikeReward(matchId_2)
			end
		end
	end
	
	for index = 1 , 9 , 2 do
		local matchId_1 = globalCounter:GetFactionMatchDetailInfoMatchId1(index)
		local matchId_2 = globalCounter:GetFactionMatchDetailInfoMatchId2(index)
		
		local result = globalCounter:GetFactionMatchDetailInfoMatchResult1(index)
		local win_index = 9 + index
		local lose_index = 10 + index
		if result == FACTION_MATCH_RESULT_TYPE_WIN then
			
			globalCounter:AddFactionMatchDetailInfo(win_index,2,matchId_1)
			globalCounter:AddFactionMatchDetailInfo(lose_index,2,matchId_2)
			
			outFmtDebug("###########DecideFactionMatchSecondDetailInfo detail win_index %d , id_2 %d ",win_index,matchId_1)
			outFmtDebug("###########DecideFactionMatchSecondDetailInfo detail lose_index %d , id_2 %d ",lose_index,matchId_2)
			
			if matchId_2 == 0 then --判断连胜终结
				self:SendFactionMatchTerminateWinstrikeReward(matchId_1)
			end
		elseif result == FACTION_MATCH_RESULT_TYPE_LOSE then
			
			globalCounter:AddFactionMatchDetailInfo(win_index,2,matchId_2)
			globalCounter:AddFactionMatchDetailInfo(lose_index,2,matchId_1)
			
			outFmtDebug("###########DecideFactionMatchSecondDetailInfo detail win_index %d , id_2 %d ",win_index,matchId_2)
			outFmtDebug("###########DecideFactionMatchSecondDetailInfo detail lose_index %d , id_2 %d ",lose_index,matchId_1)
			
			if matchId_1 == 0 then --判断连胜终结
				self:SendFactionMatchTerminateWinstrikeReward(matchId_2)
			end
		end
	end
	
	app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_DECIDE_SECOND,{})
end

--允许进入第二轮战场    轮空 情况 直接判胜负
function GlobalValue:OpenFactionMatchSecondRound()
	self:PrintFactionMatchInfo()
	for index = 10 , 19 do
		local guid_1 ,guid_2 = globalCounter:GetFactionMatchFactionGuidByDetailIndex(index)
		if guid_1 ~= "" and guid_2 ~= "" then
			outFmtDebug("###########OpenFactionMatchSecondRound index %d , team 1 ,team 2 all exist",index)
		elseif guid_1 ~= "" then
			globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
			globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
			outFmtDebug("###########OpenFactionMatchSecondRound index %d , team 1 win ,team 2 not exist",index)
		elseif guid_2 ~= "" then
			globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
			globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
			
			outFmtDebug("###########OpenFactionMatchSecondRound index %d , team 2 win ,team 1 not exist",index)
		else
			globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
			globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
			
			outFmtDebug("###########OpenFactionMatchSecondRound index %d , team 1 win ,team 1 team 2 not exist",index)
		end
	end
	
	
	app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_OPEN_SECOND,{})
end

--开始第二轮比赛 判断弃权
function GlobalValue:StartFactionMatchSecondRound()
	local min_member_need = tb_faction_match_base[1].min_member_need	
	
	for index = 10 , 19 do
		local guid_1 ,guid_2 = globalCounter:GetFactionMatchFactionGuidByDetailIndex(index)
		if guid_1 ~= "" and guid_2 ~= "" then
			local count_1 = globalCounter:GetFactionMatchDetailInfoMemberCount1(index)
			local count_2 = globalCounter:GetFactionMatchDetailInfoMemberCount2(index)
			
			if count_1 >= min_member_need and count_2 < min_member_need then
				globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
				globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
				
				outFmtDebug("###########StartFactionMatchSecondRound index %d , team 1 win ,team 2 not join enough",index)
			elseif count_2 >= min_member_need and count_1 < min_member_need then
				globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
				globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
				outFmtDebug("###########StartFactionMatchSecondRound index %d , team 2 win ,team 1 not join enough",index)
			elseif count_1 < min_member_need and count_2 < min_member_need then
				local faction_1 = app.objMgr:getObj(guid_1)
				local faction_2 = app.objMgr:getObj(guid_2)
				if faction_1:GetDouble(FACTION_INT_FIELD_TOTAL_FORCE) >= faction_2:GetDouble(FACTION_INT_FIELD_TOTAL_FORCE) then
					globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
					globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
					outFmtDebug("###########StartFactionMatchSecondRound index %d , team 1 win ,team 2 force lower",index)
				else
					globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
					globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
					outFmtDebug("###########StartFactionMatchSecondRound index %d , team 2 win ,team 1 force lower",index)
				end
			end
			
			
		
		end
		
	end
	
	app:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_START_SECOND,{})
end

--第二轮结算
function GlobalValue:EndFactionMatchSecondRound()
	--超时根据分数判断胜利
	for index = 10 , 19 do
		if globalCounter:GetFactionMatchDetailInfoMatchResult1(index) == 0 and globalCounter:GetFactionMatchDetailInfoMatchResult2(index) == 0 then
			local score_1 = globalCounter:GetFactionMatchDetailInfoScore1(index)
			local score_2 = globalCounter:GetFactionMatchDetailInfoScore2(index)
			
			if score_1 >= score_2 then
				globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
				globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
				
				outFmtDebug("###########EndFactionMatchSecondRound index %d , team 1 win ,team 2 score lower",index)

			elseif score_1 < score_2 then
				globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
				globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
				outFmtDebug("###########EndFactionMatchSecondRound index %d , team 2 win ,team 1 score lower",index)

			end
		end
		
	end
end

--进行结束处理
function GlobalValue:FinishFactionMatch()
	--连胜终结奖励判断 只判断 10
	local matchId_1 = globalCounter:GetFactionMatchDetailInfoMatchId1(10)
	local matchId_2 = globalCounter:GetFactionMatchDetailInfoMatchId2(10)
	local result = globalCounter:GetFactionMatchDetailInfoMatchResult1(10)
	if result == FACTION_MATCH_RESULT_TYPE_WIN and matchId_2 == 0 then
		self:SendFactionMatchTerminateWinstrikeReward(matchId_1)
	elseif result == FACTION_MATCH_RESULT_TYPE_LOSE and matchId_1 == 0 then
		self:SendFactionMatchTerminateWinstrikeReward(matchId_2)
	end
	local rank = 1
	local rank_list = {}
	for index = 10 , 19 do
		local matchId_1 = globalCounter:GetFactionMatchDetailInfoMatchId1(index)
		local matchId_2 = globalCounter:GetFactionMatchDetailInfoMatchId2(index)
		if globalCounter:GetFactionMatchDetailInfoMatchResult1(index) == FACTION_MATCH_RESULT_TYPE_WIN then
			globalCounter:SetFactionMatchInfoResultRank(matchId_1,rank)
			globalCounter:SetFactionMatchInfoResultRank(matchId_2,rank + 1)
			rank_list[rank] = matchId_1
			rank_list[rank + 1] = matchId_2
			
			rank = rank + 2
		elseif globalCounter:GetFactionMatchDetailInfoMatchResult1(index) == FACTION_MATCH_RESULT_TYPE_LOSE then
			globalCounter:SetFactionMatchInfoResultRank(matchId_1,rank + 1)
			globalCounter:SetFactionMatchInfoResultRank(matchId_2,rank)
			rank_list[rank] = matchId_2
			rank_list[rank + 1] = matchId_1
			
			rank = rank + 2
		end
	end
	
	--排行奖励
	for rank,id in ipairs(rank_list) do
		local guid = globalCounter:GetFactionMatchInfoGuid(id)
		outFmtDebug("FinishFactionMatch rank %d , id %d, guid %s",rank,id,guid)
		
		self:SendFactionMatchRankReward(guid,rank)
		
		
	end
	
	--连胜奖励
	local id = rank_list[1]
	local guid = globalCounter:GetFactionMatchInfoGuid(id)
	if guid ~= "" then
		local faction = app.objMgr:getObj(guid)
		if faction then
			if guid == self:GetFactionMatchChampionFactionGuid() then --连胜判断
				local count = self:GetFactionMatchChampionWinstrikeCount() + 1
				self:SetFactionMatchChampionWinstrikeCount(count)
				
				self:SendFactionMatchWinstrikeReward(guid,count)--连胜奖励
				
			else
				self:SetFactionMatchChampionWinstrikeCount(1)
			end
			
			self:SetFactionMatchChampionFactionGuid(guid)
			self:SetFactionMatchChampionBangZhuGuid(faction:GetBangZhuGuid())
			self:SetFactionMatchChampionFactionName(faction:GetName())
			self:SetFactionMatchChampionBangZhuName(faction:GetBangZhuName())

			
			local data = {}
			data.name = 'Handle_Faction_Match_BangZhu'
			data.callback_guid = faction:GetBangZhuGuid()
			
			function data.fun (data, objs)
				local targetPlayer = objs[data.callback_guid]
				if not targetPlayer then return end
				
				local gender = targetPlayer:GetGender()
				local coat = targetPlayer:GetUInt16(PLAYER_INT_FIELD_APPEARANCE, 1)
				local weapon =  targetPlayer:GetUInt16(PLAYER_INT_FIELD_APPEARANCE, 0)
				local wingsId =  targetPlayer:getSpellMgr():GetWingsId()
				globalValue:SetFactionMatchChampionBangZhuCoat(coat)
				globalValue:SetFactionMatchChampionBangZhuWeapon(weapon)
				globalValue:SetFactionMatchChampionBangZhuGender(gender)
				globalValue:SetFactionMatchChampionBangZhuWingsId(wingsId)
				
				
				outFmtDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FactionMatchChampionBangZhu gender %d coat %d weapon %d wingsId %d",gender,coat,weapon,wingsId)
			end
			GetObjects(data)
			
		end
	else
		self:SetFactionMatchChampionWinstrikeCount(0)
		self:SetFactionMatchChampionFactionGuid("")
		self:SetFactionMatchChampionBangZhuGuid("")
		self:SetFactionMatchChampionFactionName("")
		self:SetFactionMatchChampionBangZhuName("")
		
		self:SetFactionMatchChampionBangZhuCoat(0)
		self:SetFactionMatchChampionBangZhuWeapon(0)
		self:SetFactionMatchChampionBangZhuGender(0)
		self:SetFactionMatchChampionBangZhuWingsId(0)
		
	end
	
end

function GlobalValue:UpdateFactionMatchFlagScore(phaseId)
	if phaseId == 0 then
		return
	end
	local script = tb_faction_match_phase[phaseId].script
	local index_start = nil
	local index_end = nil
	if script == FACTION_MATCH_SCRIPT_TYPE_START_FIRST then
		index_start = 0
		index_end = 9
	elseif script == FACTION_MATCH_SCRIPT_TYPE_START_SECOND then
		index_start = 10
		index_end = 19
	end
	
	if index_start and index_end then
		local score_per_flag = tb_faction_match_base[1].flag_score_gain_speed
		for index = index_start,index_end do
			if globalCounter:GetFactionMatchDetailInfoMatchResult1(index) == 0 and globalCounter:GetFactionMatchDetailInfoMatchResult2(index) == 0 then
				local flags_1 = 0
				local flags_2 = 0
				for offset = 0,4 do
					if globalCounter:GetFactionMatchDetailInfoFlag1(index,offset) then
						flags_1 = flags_1 + 1
					end
					
					if globalCounter:GetFactionMatchDetailInfoFlag2(index,offset) then
						flags_2 = flags_2 + 1
					end
				end
				
				self:AddFactionMatchScore(index,flags_1 * score_per_flag,flags_2 * score_per_flag)
			end
		end
	end
end

function GlobalValue:AddFactionMatchScore(index,score1,score2)
	local target_score = tb_faction_match_base[1].target_score
	
	local score_1 = globalCounter:GetFactionMatchDetailInfoScore1(index)
	local score_2 = globalCounter:GetFactionMatchDetailInfoScore2(index)
	
	local score_1_to = score_1 + score1
	local score_2_to = score_2 + score2
	
	if score_1_to >= target_score then
		score_1_to = target_score
	end
	
	if score_2_to >= target_score then
		score_2_to = target_score
	end
	
	if score_1_to >= target_score and score_2_to >= target_score then
		score_1_to = target_score
		score_2_to = target_score - 1
	end
	globalCounter:SetFactionMatchDetailInfoScore1(index,score_1_to)
	globalCounter:SetFactionMatchDetailInfoScore2(index,score_2_to)
	
	if score_1_to == target_score then
		globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_WIN)
		globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_LOSE)
		
		outFmtDebug("##########UpdateFactionMatchFlagScore index %d , team 1 win , %d : %d",index,score_1_to,score_2_to)
	elseif score_2_to == target_score then
		globalCounter:SetFactionMatchDetailInfoMatchResult2(index,FACTION_MATCH_RESULT_TYPE_WIN)
		globalCounter:SetFactionMatchDetailInfoMatchResult1(index,FACTION_MATCH_RESULT_TYPE_LOSE)
		outFmtDebug("##########UpdateFactionMatchFlagScore index %d , team 2 win , %d : %d",index,score_1_to,score_2_to)
	end
	
	
end

function GlobalValue:CheckFactionMatchStart()
	if self:GetFactionMatchGames() == 0 then
		--开服第n天
		local startTime = getTheFirstTimestampOfDay(globalGameConfig:GetKaiFuShiJian()) + 86400 * tb_faction_match_base[1].server_open_day
		
		if os.time() >= startTime - 60 then
			self:StartFactionMatch()
			
		end
	else
		if IsTodayWeekX(tb_faction_match_base[1].week_open_day) then
			self:StartFactionMatch()
			
		end
		
	end
	
	
end





--更新下次活动时间
function GlobalValue:UpdateFactionMatchStartTime()
	if self:GetFactionMatchGames() == 0 then
		local startTime = getTheFirstTimestampOfDay(globalGameConfig:GetKaiFuShiJian()) + 86400 * tb_faction_match_base[1].server_open_day
		
		self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_GAMES_NEXT_TIME,startTime)
	else
		if self:GetFactionMatchCurrentsPhase() == 0 then
			local startTime = GetNextWeekXStartTimeFromNow(tb_faction_match_base[1].week_open_day)
			self:SetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_GAMES_NEXT_TIME,startTime)
		end
	end
	
end

return GlobalValue
