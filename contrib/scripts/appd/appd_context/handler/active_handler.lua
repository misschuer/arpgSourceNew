---获取活跃度奖励
function PlayerInfo:Handle_Avtive_Reward(pkt)
	outFmtDebug("PlayerInfo:Handle_Avtive_Reward")
	local id = pkt.id
	local vip = pkt.vip
	
	local config = tb_activity_reward[id]
	
	if config == nil then
		return 
	end
	
	if vip == 1 then
		if self:GetVIP() <=0 then
			self:CallOptResult(OPRATE_TYPE_ACTIVITY, ACTIVITY_OPERATE_NOTVIP)
			return 
		end
	end
	
	local instMgr = self:getInstanceMgr()
	local activity = instMgr:getActivity()
	if activity < config.active then
		self:CallOptResult(OPRATE_TYPE_ACTIVITY, ACTIVITY_OPERATE_NOENOUGH)
		return
	end
	
	
	local idx = id * 2
	if vip == 1 then
		idx = idx + 1
	end
	
	local hasget = instMgr:hasGetActivityReward(idx)
	
	if hasget then
		self:CallOptResult(OPRATE_TYPE_ACTIVITY, ACTIVITY_OPERATE_HASGET)
		return 
	end
	
	instMgr:SetActivityReward(idx)
	
	local tab = {}

	if vip ~= 1 then
		tab = config.reward
	else
		
		tab = config.vipreward
	end
	
	self:AppdAddItems(tab,MONEY_CHANGE_PRESTIGE,LOG_ITEM_OPER_TYPE_ACTIVITY)
	
	
end

--添加活跃度
function PlayerInfo:AddActiveItem(id)
	
	--经脉活跃度
	outFmtDebug("PlayerInfo:AddActiveItem  onAddMeridianExpSource-------------")
	self:onAddMeridianExpSource(id)
	
	--每日活跃度
	outFmtDebug("PlayerInfo:AddActiveItem-------------")
	
	local config = tb_activity_base[id]
	if config == nil then
		outFmtDebug("add active fail,no data %d",id)
		return 
	end
	
	
	
	local instMgr = self:getInstanceMgr()
	local num = instMgr:getActiveNum(id)
	
	if num  == config.nums then
		outFmtDebug("PlayerInfo:AddActiveItem id %d max nums",id)
		return
	end
	
	--判断星期  不填表示不限制
	if #config.day ~= 0 then
		local available_day = false
		for _,i in pairs(config.day) do
			if IsTodayWeekX(i) then
				available_day = true
				break
			end
			
		end
		
		--家族战特殊
		if config.server_open_day > 0 then
			local startTime = getTheFirstTimestampOfDay(globalGameConfig:GetKaiFuShiJian()) + 86400 * config.server_open_day
				
			if os.time() < startTime then
				outFmtDebug("PlayerInfo:AddActiveItem id %d server open day no reach",id)
				return
			end
			--开服后n天强制开启
			if os.time() < startTime + 86400 then
				available_day = true
			end
		end
	
		if not available_day then
			outFmtDebug("PlayerInfo:AddActiveItem id %d not available today",id)
			return
		end
	end
	
	num = num + 1
	instMgr:setActiveNum(id,num)
	instMgr:addActivity(config.active)
	
	if num  == config.nums then
		self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_ACTIVE_TASK, {})
	end
end

--添加活跃度
function PlayerInfo:DailyResetActive()
	local instMgr = self:getInstanceMgr()
	for id,_ in pairs(tb_activity_base) do
		instMgr:setActiveNum(id,0)
	end
	instMgr:setActivity(0)
	
	instMgr:SetUInt32(INSTANCE_INT_FIELD_ACTIVE_REWARD,0)
end
