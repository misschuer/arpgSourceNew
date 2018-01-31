
InitQueueInfo(#tb_single_pvp_grade, tb_single_pvp_base[ 1 ].matchLast)

function OnProcessLocalSinglePVPMatch()
	OnProcessMatchQueue()
end

function OnLocalSinglePVPMatched(guid, key, now)
	outFmtDebug("################# OnLocalSinglePVPMatched matched, guid = %s key = %s", guid, key)
	-- 进行进入比赛逻辑
	local generalId = string.format("%d|%s", now, key)
	local playerInfo = app.objMgr:getObj(guid)
	
	local kk = string.split(key, '|')
	local guidTable = string.split(kk[ 1 ], '#')
	local indx = 1
	for i = 1, #guidTable do
		if guid == guidTable[ i ] then
			indx = i
		end
	end
	local enterPos = tb_single_pvp_base[ 1 ].enterPos
	local x = enterPos[indx][ 1 ]
	local y = enterPos[indx][ 2 ]
	local mapid = tb_single_pvp_base[ 1 ].mapid
	-- 发起传送
	call_appd_teleport(playerInfo:GetScenedFD(), guid, x, y, mapid, generalId)
	
	app:SetMatchingKuafuType(guid, nil)
	
	local instMgr = playerInfo:getInstanceMgr()
	instMgr:SubQualifyDailyTimes()
	
	playerInfo:AddActiveItem(VITALITY_TYPE_SINGLE_PVP)
	playerInfo:onUpdatePlayerQuest(QUEST_TARGET_TYPE_JOIN_SINGLE_PVP, {})
end

-- 取消匹配组队副本
function PlayerInfo:OnCancelLocalSinglePVPMatchBeforeOffline()
	if not app:IsKuafuTypeMatching(self:GetGuid(), MATCH_TYPE_LOCAL_SINGLE_PVP) then
		return
	end
	
	local indx = self:calcQueueIndx()
	CancelMatchQueue(indx, self:GetGuid())
	
	app:SetMatchingKuafuType(self:GetGuid(), nil)
end

-- 匹配组队副本
function PlayerInfo:OnLocalSinglePVPMatch()
	-- 已经在跨服了
	if self:IsKuafuing() then
		return false
	end
	
	if app:IsInKuafuTypeMatching(self:GetGuid()) then
		return false
	end
	
	app:SetMatchingKuafuType(self:GetGuid(), MATCH_TYPE_LOCAL_SINGLE_PVP)
	
	local indx = self:calcQueueIndx()
	if self:isMatchRobot() then
		local key = string.format("%s#robot|%d", self:GetGuid(), indx)
		OnLocalSinglePVPMatched(self:GetGuid(), key, os.time())
	else
		-- 加入匹配队列
		AddMatchQueue(indx, self:GetGuid())
	end
	
	return true
end

function PlayerInfo:calcQueueIndx()
	local score = self:GetQualifyScore()
	local indx = 1
	for i = 1, #tb_single_pvp_grade do
		local range = tb_single_pvp_grade[ i ].range
		if score >= range[ 1 ] and score <= range[ 2 ] then
			indx = i
			break
		end
	end
	
	return indx
end

function PlayerInfo:isMatchRobot()
	local score = self:GetQualifyScore()
	return score <= tb_single_pvp_base[ 1 ].robotScore
end

-- 购买进入次数
function PlayerInfo:OnBuyLocalSinglePVPTicket(count)
	
end


-- 重置单人匹配副本
function PlayerInfo:OnResetLocalSinglePVPDayTimes()
	local instMgr = self:getInstanceMgr()
	instMgr:ResetQualifyDaily()
end

function PlayerInfo:OnResetLocalSinglePVPWeekInfo()
	self:SetInitQualifyScore()
end

QUALIFY_RECORD_FORMAT = '%s|%d|%d|%d' -- fightName|result|score|timestamp

function PlayerInfo:OnProcessSingleMatchResult(result, fightName)
	local indx = self:calcQueueIndx()
	local gradeConfig = tb_single_pvp_grade[indx]
	local instMgr = self:getInstanceMgr()
	local score
	
	if result == GlobalCounter.WIN then
		-- 加次数
		instMgr:AddQualifyWins(1)
		
		-- 胜利计算额外奖励
		local wins = instMgr:GetQualifyWins()
		for i = 1, #tb_single_pvp_extra do
			local config = tb_single_pvp_extra[ i ]
			if config.wins == wins then
				instMgr:SetQualifyExtraObtain(i-1)
			end
		end
		score = gradeConfig.win
		self:AddQualifyScore(score)
		
		self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_SINGLE_PVP_WINS, {})
	else
		score = gradeConfig.lose
		self:SubQualifyScore(score)
	end
	
	-- 排名
	rankInsertTask(self:GetGuid(), RANK_TYPE_SINGLE_PVP)
	
	local new_indx = self:calcQueueIndx()
	if new_indx > indx and new_indx >= 4 then --达到黄金
		
		app:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_PAIWEI_RANKUP,{self:GetNoticeName(),tb_single_pvp_grade[new_indx].name})
	end
	
	local record = string.format(QUALIFY_RECORD_FORMAT, fightName, result, score, os.time())
	instMgr:AddQaulifyRecord(record)
end


-- 获得排位赛积分
function PlayerInfo:GetQualifyScore()
	return self:GetUInt32(PLAYER_INT_FIELD_QUALIFY_SCORE)
end

-- 增加排位赛积分
function PlayerInfo:AddQualifyScore(val)
	self:AddUInt32(PLAYER_INT_FIELD_QUALIFY_SCORE, val)
end

-- 减少排位赛积分
function PlayerInfo:SubQualifyScore(val)
	local curr = self:GetQualifyScore()
	-- 已经扣到底了
	if curr == 0 then
		return
	end
	val = math.min(curr, val)
	self:SubUInt32(PLAYER_INT_FIELD_QUALIFY_SCORE, val)
end

-- 设置排位赛积分
function PlayerInfo:SetInitQualifyScore()
	-- 领取奖励
	local curr = self:GetQualifyScore()
	if curr > 0 then
		local indx = self:calcQueueIndx()
		local config = tb_single_pvp_grade[indx]
		local giftType = 3
		outFmtDebug("SetInitQualifyScore indx = %d", indx)
		-- 发邮件
		AddGiftPacksData(self:GetGuid(),0,giftType,os.time(),os.time() + 86400*30, config.name, config.desc, config.weekRewards, SYSTEM_NAME)
		--self:AppdAddItems(rewards, MONEY_CHANGE_SINGLE_PVP, LOG_ITEM_OPER_TYPE_SINGLE_PVP)
	end
	
	local val = tb_single_pvp_base[ 1 ].initScore
	self:SetUInt32(PLAYER_INT_FIELD_QUALIFY_SCORE, val)
end