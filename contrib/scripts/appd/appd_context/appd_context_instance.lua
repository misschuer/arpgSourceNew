-- 检测能否进入VIP副本
function PlayerInfo:checkVipMapTeleport(id, hard)
	-- 系统未激活
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_VIP)) then
		return
	end

	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterVIP(id, hard)
end

-- 通关VIP关卡
function PlayerInfo:passVipInstance(id, hard)
	local instMgr = self:getInstanceMgr()
	instMgr:passVipInstance(id, hard)
end

-- 进行扫荡
function PlayerInfo:sweepVIP(id)
	-- 系统未激活
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_VIP)) then
		return
	end
	-- 每个信息4个byte[0:下次需要通关难度,1:当前难度,2:挑战次数,3:购买次数]
	local config = tb_map_vip[id]
	local indx = INSTANCE_INT_FIELD_VIP_START + id - 1
	local instMgr = self:getInstanceMgr()
	
	-- 判断是否需要购买
	local times = instMgr:GetByte(indx, 2)
	if times < config.times then
		outFmtError("not need to buy because of full times")
		return
	end
	
	-- 有通关难度才让挑战
	local hard = instMgr:GetByte(indx, 1)
	if hard == 0 then
		outFmtError("not pass any hard in id = %d", id)
		return
	end
	
	-- 购买次数已满
	local buyTimes = instMgr:GetByte(indx, 3)
	if buyTimes >= #config.cost then
		outFmtError("buy times is not enough")
		return
	end
	
	local cost = config.cost[buyTimes+1]
	
	if self:costMoneys(MONEY_CHANGE_BUY_VIP_INSTANCE, {{MONEY_TYPE_GOLD_INGOT, cost}}) then
		instMgr:AddByte(indx, 3, 1)
		instMgr:sweepVIPInstance(id, hard)
	end
	
end
---------------------------资源副本-----------------------------
-- 检测能否进入资源副本
function PlayerInfo:checkResMapTeleport(id)
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterResInstance(id)
end

---------------------------试炼塔-----------------------------
-- 检测能否进入试炼塔副本
function PlayerInfo:checkTrialMapTeleport()
	-- 系统未激活
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_TRIAL)) then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterTrial()
end

-- 通关关卡
function PlayerInfo:passTrialInstance(id)
	local instMgr = self:getInstanceMgr()
	instMgr:passInstance(id)
	
	-- 设置试炼塔通关层数
	if self:GetUInt32(PLAYER_FIELD_TRIAL_LAYERS) < id then
		self:SetUInt32(PLAYER_FIELD_TRIAL_LAYERS, id)
	end
	-- 更新排名
	rankInsertTask(self:GetGuid(), RANK_TYPE_TRIAL)
	
	self:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_TRIAL_WIN,{self:GetNoticeName(),id})
	self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_TRIAL_TOWER_FLOOR, {})
end


-- 一键扫荡
function PlayerInfo:sweepTrial()
	-- 系统未激活
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_TRIAL)) then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:sweepTrialInstance()
end

-- 重置试炼塔
function PlayerInfo:resetTrial()
	local instMgr = self:getInstanceMgr()
	instMgr:resetTrialInstance()
end


-- 通关关卡
function PlayerInfo:passResInstance(id)
	local instMgr = self:getInstanceMgr()
	instMgr:passResInstance(id)
	
end

-----------通关世界冒险-----------
function PlayerInfo:passWorldRiskInstance(id)
	local questMgr = self:getQuestMgr()
	questMgr:OnUpdate(QUEST_TARGET_TYPE_PASS_WORLD_RISK, {id})
	
	globalCounter:onRiskRank(self, id)
	
	if math.floor(tb_risk_data[id].nextId /1000) - math.floor(id/1000) > 0 then
		self:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_RISK_CHAPTER,{self:GetNoticeName(),math.floor(id/1000) - 1000})
	end
end



function PlayerInfo:sweepResInstance(id)
	local vip = self:GetVIP()
	if vip <= 0 then
		outFmtDebug("not vip cannot sweepResInstance")
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:sweepResInstance(id)
end


-----------------------------------------------------------------------------------
--- 副本模块每日重置
function PlayerInfo:instanceDailyReset()
	local instMgr = self:getInstanceMgr()
	instMgr:instanceDailyReset()
end














-----------------世界BOSS----------------

-- 进行报名
function onEnrole(playerInfo)
	-- 一定要是报名阶段
	if not globalValue:IsWorldBossEnroll() then
		outFmtDebug("========================= not in enroll time")
		return
	end
	
	WorldBossEnroll(playerInfo:GetGuid())
	local id = globalValue:GetWorldBossTimes()
	playerInfo:SetLastJoinID(id)
	playerInfo:SetLastState(PLAYER_WORLD_BOSS_ENROLLED)
	playerInfo:SetLastLine(0)
	playerInfo:SetLastDeath(0)
	
	playerInfo:CallScenedDoSomething(APPD_SCENED_WORLD_BOSS_WAITING)
end

function ClearWorldBossEnrollData()
	ResetWorldBossEnroll()
end

-- 获得报名的所有玩家
function GetEnrolledPlayer()
	local tb = {}
	local enrollInfo = GetWorldBossEnrollInfo()
	for _, playerGuid in pairs(enrollInfo) do
		local playerInfo = app.objMgr:getObj(playerGuid)
		-- outFmtDebug(playerGuid, playerInfo)
		if playerInfo  and playerInfo:isLogined()  then
			table.insert(tb, playerInfo)
		end
	end
	
	return tb
end

-- 报名世界boss
function OnEnrollWorldBoss()
	-- 世界BOSS开启次数+1
	globalValue:AddWorldBossTimes()
	-- 设置报名状态
	globalValue:SetWorldBossState(WORLD_BOSS_PROCESS_ENROLL)
	-- 设置报名时间
	globalValue:SetEnrollTime()
	--清理世界BOSS报名数据
	ClearWorldBossEnrollData()
end

-- 安排世界BOSS房间
function ArrangeWorldBossRoom()
	
	local playerDict = GetEnrolledPlayer()
	local count = #playerDict
	
	if count == 0 then
		return {}, {}
	end
	
	local room = math.ceil(count / tb_worldboss_time[ 1 ].roomLimit)
	local playersPerRoom = math.floor(count / room)
	local rest = count % room
	
	-- 算出每个房间容纳的人数
	local roomInfo = {}
	for i = 1, room do
		local num = playersPerRoom
		if rest > 0 then
			rest = rest - 1
			num = num + 1
		end
		table.insert(roomInfo, num)
	end
	
	return playerDict, roomInfo
end

-- 进行传送
function DoWorldBossTeleport(playerDict, roomInfo)
	local line = 1
	for _, playerInfo in pairs(playerDict) do
		-- 进行传送(必要的话进行分时传送)
		playerInfo:CallScenedDoSomething(APPD_SCENED_WORLD_BOSS_ENTER, line)
		roomInfo[line] = roomInfo[line] - 1
		if roomInfo[line] == 0 then
			line = line + 1
		end
		-- 参加野外BOSS
		local questMgr = playerInfo:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_WORLD_BOSS)
		
		playerInfo:AddActiveItem(VITALITY_TYPE_WORLD_BOSS)
	end
end

function PlayerInfo:checkMassBossMapTeleport(id)
	-- 模块没开 不让进
	if not self:GetOpenMenuFlag(MODULE_BOSS, MODULE_BOSS_RISK_BOSS) then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterMassBoss(id)
end


--------------------------------------
--个人BOSS

function PlayerInfo:checkPrivateBossMapTeleport(id)
	-- 模块没开 不让进
	--if not self:GetOpenMenuFlag(MODULE_BOSS, MODULE_BOSS_RISK_BOSS) then
	--	return
	--end
	
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterPrivateBoss(id)
end

function PlayerInfo:onPrivateBossWin(id)
	
	local instMgr = self:getInstanceMgr()
	instMgr:updatePrivateBossRecoverTime(id)
	
	self:AddActiveItem(VITALITY_TYPE_PRIVATE_BOSS)
end


-------------------------------
--闯关副本
function PlayerInfo:SetPassedStageInstanceId(val)
	self:SetUInt32(PLAYER_INT_FIELD_PASSED_STAGE_INSTANCE_ID,val)
end

function PlayerInfo:GetPassedStageInstanceId()
	return self:GetUInt32(PLAYER_INT_FIELD_PASSED_STAGE_INSTANCE_ID)
end

--检测进入闯关副本

function PlayerInfo:checkStageInstanceTeleport(id)
	if self:GetPassedStageInstanceId() + 1 ~= id then
		return
	end
	
	local config = tb_instance_stage[ id ]
	
	if not config then
		return
	end
	
	-- 判断等级是否足够
	if self:GetLevel() < config.limLev then
		outFmtError("checkStageInstanceTeleport no level to enter id = %s", id)
		return
	end
	
	local x 	= config.x
	local y 	= config.y
	local mapid = config.mapid
	local buffEffectId = 0
	if self:GetForce() >= config.force then
		buffEffectId = tb_instance_stage_base[1].buffEffectId
	else
		buffEffectId = tb_instance_stage_base[1].debuffEffectId
	end
	
	
	-- 发起传送
	call_appd_teleport(self:GetScenedFD(), self:GetGuid(), x, y, mapid, string.format("%d:%d:%s",id,buffEffectId,self:GetGuid()))
	
	--self:AddActiveItem(VITALITY_TYPE_MASS_BOSS)
	--self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_JOIN_MASS_BOSS_TIMES, {})
	
end

--通关闯关副本
function PlayerInfo:onPassStageInstance(id)
	local config = tb_instance_stage[ id ]
	
	if config then
		if id > self:GetPassedStageInstanceId() then
			self:SetPassedStageInstanceId(id)
			self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_STAGE_INSTANCE_ID, {})
		end
	end
end

--领取闯关关卡宝箱奖励
function PlayerInfo:PickStageInstanceBonus(id)
	local instMgr = self:getInstanceMgr()
	instMgr:checkPickStageInstanceBonus(id)
end
