--领取首充奖励
function PlayerInfo:WelfareShouchong()
	local questMgr = self:getQuestMgr()
	if questMgr:getWelfareShouchong() == 1 then
		outFmtDebug("has get shouchong")
		return false
	end
	
	
	if self:GetRechageSum() == 0 then
		outFmtDebug("has never Rechage")
		return false
	end
	
	--[[local config = tb_welfare_shouchong[1]
	if not config then
		return
	end
	
	self:AppdAddItems(config.item,MONEY_CHANGE_SHOUCHONG,LOG_ITEM_OPER_TYPE_SHOUCHONG)--]]
	
	local config = tb_recharge_first_reward[self:GetGender()]
	if not config then
		outFmtDebug("config error ")
		return false
	end
	
	--发送邮件
	local desc = config.mail_desc
	local name = config.mail_name
	local reward = itemListToItemString(config.reward)
	AddGiftPacksData(self:GetGuid(),0,GIFT_PACKS_TYPE_RECHARGE,os.time(),os.time() + 86400*30, name, desc, reward, SYSTEM_NAME)
	
	self:CallOptResult(OPERTE_TYPE_RECEIVE_GIFT_PACKS,RECEIVE_GIFT_PACKS_FIRST_RECHARGE_GIFT,{})
	questMgr:setWelfareShouchong()
	return true
end

function PlayerInfo:WelfareSevenDayRecharge(recharge_time)
	local questMgr = self:getQuestMgr()
	local last_time = self:GetRechageLastTime()
	
	if self:GetRechageSum() == 0 then
		outFmtDebug("has never Rechage")
		return
	end
	
	if checkSameDay(last_time, recharge_time ) then
		outFmtDebug("WelfareSevenDayRecharge same day")
		return
	else
		questMgr:SetWelfareSevenDayRechargeTodayFlag()
	end
	
	
	local recharge_count = questMgr:GetWelfareSevenDayRechargeProcess()
	outFmtDebug("WelfareSevenDayRecharge count  %d",recharge_count)
	local config = tb_recharge_7day_reward[recharge_count + 1]
	if config then
		local desc = config.mail_desc
		local name = config.mail_name
		local reward = itemListToItemString(config.reward)
		AddGiftPacksData(self:GetGuid(),0,GIFT_PACKS_TYPE_RECHARGE,os.time(),os.time() + 86400*30, name, desc, reward, SYSTEM_NAME)
		
		self:CallOptResult(OPERTE_TYPE_RECEIVE_GIFT_PACKS,RECEIVE_GIFT_PACKS_DAY_RECHARGE_GIFT,{})
		questMgr:SetWelfareSevenDayRechargeProcess(recharge_count + 1)
		
	end
	
	
end

function PlayerInfo:GetSevenDayRechargeExtraReward(id)
	local config = tb_recharge_7day_extra_reward[id]
	local questMgr = self:getQuestMgr()
	
	
	
	if config then
		local flag = questMgr:GetWelfareSevenDayRechargeExtraFlag(id - 1)
		local recharge_count = questMgr:GetWelfareSevenDayRechargeProcess()
		
		if not flag and recharge_count >= config.day then
			
			self:AppdAddItems(config.reward,MONEY_CHANGE_SEVEN_DAY_RECHARGE_EXTRA,LOG_ITEM_OPER_TYPE_SEVEN_DAY_RECHARGE_EXTRA)
			
			questMgr:SetWelfareSevenDayRechargeExtraFlag(id - 1)
		end
		
		
		
	end
	
	
end


--每日签到奖励
function PlayerInfo:WelfareCheckIn(day)
	
	local questMgr = self:getQuestMgr()
	
	if questMgr:getWelfareCheckIn(day) then 
		--self:CallOptResult(OPRATE_TYPE_ACTIVITY, ACTIVITY_OPERATE_HASGET)
		return
	end
	
	local config = tb_welfare_checkin[day]
	if not config then
		return
	end
	
	local vip = self:GetVIP()
	local times = 1
	if vip >= config.vip then
		times = config.times
	end
	
	local itemdic = {}
	
	if times == 1 then
		itemdic = config.item
	else 
		for _,v in ipairs(config.item) do
			local tab = {}
			table.insert(tab,v[1])
			table.insert(tab,v[2] * times)
			
			table.insert(itemdic,tab)
		end
	end
	
	self:AppdAddItems(itemdic,MONEY_CHANGE_CHECKIN,LOG_ITEM_OPER_TYPE_CHECKIN)
	
	questMgr:setWelfareCheckIn(day)
end
--领取累积签到奖励
function PlayerInfo:WelfareCheckInAll(id)
	local questMgr = self:getQuestMgr()
	
	local config = tb_welfare_checkin_all[id]
	if not config then
		return
	end
	
	if questMgr:getWelfareCheckInAll(id) then 
		--self:CallOptResult(OPRATE_TYPE_ACTIVITY, ACTIVITY_OPERATE_HASGET)
		return
	end
	
	
	local allnum = questMgr:getWelfareCheckInDayNum()
	
	if allnum >= config.num then
		self:AppdAddItems(config.item,MONEY_CHANGE_TOTAL_CHECKIN,LOG_ITEM_OPER_TYPE_TOTAL_CHECKIN)
		questMgr:setWelfareCheckInAll(id)
	end
	
end
--领取等级奖励
function PlayerInfo:WelfareLevel(id)
	--outFmtDebug("000000000000")
	local questMgr = self:getQuestMgr()
	
	local config = tb_welfare_level[id]
	if not config then
		return
	end
	
	if questMgr:getWelfareLev(id) then 
		--self:CallOptResult(OPRATE_TYPE_ACTIVITY, ACTIVITY_OPERATE_HASGET)
		return
	end
	
	
	
	if self:GetLevel() < config.lev then
		return
	end
	
	self:AppdAddItems(config.item,MONEY_CHANGE_WELFARE_LEVEL,LOG_ITEM_OPER_TYPE_WELFARE_LEVEL)
	
	questMgr:setWelfareLev(id)
end
--福利找回奖励
function PlayerInfo:GetWelfareBackReward(type,bestGetback,backNum)
	local questMgr = self:getQuestMgr()
	--local curnum = questMgr:getWelfareBackAllNum(type)
	
	local maxNum = self:GetWelfareBackMaxNum(type)
	
	local allNum = questMgr:getWelfareBackAllNum(type)
	
	--for j=-3,-1 do
	--	local time = GetTodayStartTimestamp(j)
	--	local curnum = questMgr:getWelfareBackNum(type,time)
	--	allNum = allNum + maxNum - curnum
	--	outFmtDebug("type:%d curnum:%d",type,curnum)
	--end
	
	if allNum < backNum then
		return
	end
	
	local cost = self:GetWelfareBackRewardCost(type,bestGetback)
	
	if not self:costMoneys(MONEY_CHANGE_WELF_ACTIVE_GETBACK, cost, backNum) then
		self:CallOptResult(OPRATE_TYPE_ACHIEVE, ACHIEVE_OPERATE_NO_MONEY)
		return
	end
	
	local rewardConfig = self:GetWelfareBackRewardData(type,bestGetback)
	
	if rewardConfig then
		self:AppdAddItems(rewardConfig,MONEY_CHANGE_WELF_ACTIVE_GETBACK,LOG_ITEM_OPER_TYPE_GETBACK,backNum)
	end
	
	local lastNum = backNum
	
	for j=-3,-1 do
		
		local time = GetTodayStartTimestamp(j)
		
		
		local curNum = questMgr:getWelfareBackNum(type,time)
		local lastItemNum = maxNum - curNum
		if lastNum < lastItemNum then
			questMgr:addWelfareBackNum(type,time,lastNum)
			lastNum = 0
			break
		else 
			questMgr:addWelfareBackNum(type,time,lastItemNum)
			lastNum = lastNum - lastItemNum
		end
		
	end
	
	self:SetWelfareBackAllNum()
	
end
--一键找回所有奖励
function PlayerInfo:GetWelfareAllReward(bestGetback)
	local rewardList,costList = self:GetWelfareAllRewardListApply(bestGetback)
	
	if #rewardList == 0 or #costList == 0 then
		return
	end
	
	if not self:costMoneys(MONEY_CHANGE_WELF_ACTIVE_GETBACK, costList) then
		self:CallOptResult(OPRATE_TYPE_ACHIEVE, ACHIEVE_OPERATE_NO_MONEY)
		return
	end
	
	self:AppdAddItems(rewardList,MONEY_CHANGE_WELF_ACTIVE_GETBACK,LOG_ITEM_OPER_TYPE_GETBACK)
	
	self:ClearWelfareBackAllNum()
	
end
--一键找回资源列表
function PlayerInfo:GetWelfareAllRewardList(bestGetback)
	local rewardList,costList = self:GetWelfareAllRewardListApply(bestGetback)
	
	local rewardStr = ""

	for _,v in ipairs(rewardList) do
		local str = v[1] ..",".. v[2]..","
		rewardStr = rewardStr .. str
	end
	local costStr
	for _,v in ipairs(costList) do
		costStr = v[1] ..",".. v[2]..","
	end
	
	if #rewardList == 0 then
		rewardStr = ","
	end
	
	if #costList == 0 then
		costStr = ","
	end
	
	self:call_welfare_rewardlist_getback (rewardStr,costStr)
end

function PlayerInfo:GetWelfareAllRewardListApply(bestGetback)
	local questMgr = self:getQuestMgr()
	local typeary = self:GetWelfareBackTypeAry()
	
	local rewardList = {}
	local costList = {}
	for _,type in ipairs(typeary) do
		local allNum = questMgr:getWelfareBackAllNum(type)
		if allNum > 0 then
			local rewardConfig = self:GetWelfareBackRewardData(type,bestGetback)
			self:AddWelfareReward2List(rewardList,rewardConfig,allNum)
			
			local costConfig = tb_welfare_back[type]
			if bestGetback then
				self:AddWelfareReward2List(costList,costConfig.allcost,math.ceil(allNum * costConfig.alldc * 0.1))
			else 
				self:AddWelfareReward2List(costList,costConfig.basecost,math.ceil(allNum * costConfig.basedc * 0.1))
			end
		end
		
		
	end
	return rewardList,costList
	
end

function PlayerInfo:AddWelfareReward2List(targetTab,tab,num)
	
	for _,v in ipairs(tab) do
		local key = v[1]
		local val = v[2] * num
		local idx = self:GetWelfareRewardTargetIdx(targetTab,key)
		
		if idx == -1 then
			local item = {}
			table.insert(item,key)
			table.insert(item,val)
			
			table.insert(targetTab,item)
		else
			targetTab[idx][2] = targetTab[idx][2] + val
		end
		
	end
	
end

function PlayerInfo:GetWelfareRewardTargetIdx(targetTab,key)
	for i,v in ipairs(targetTab) do
		if v[1] == key then
			return i
		end
	end
	return -1
end

--添加可以找回的记录
function PlayerInfo:AddWelfareBackLog(type,num)
	local daytime = GetTodayStartTimestamp(0)
	local questMgr = self:getQuestMgr()
	questMgr:addWelfareBackNum(type,daytime,num)
	
	self:SetWelfareBackAllNum()
end

function PlayerInfo:AddWelfareBackGmLog(type,num,day)
	local off = -day
	local daytime = GetTodayStartTimestamp(off)
	local questMgr = self:getQuestMgr()
	questMgr:addWelfareBackNum(type,daytime,num)
	
	self:SetWelfareBackAllNum()
end

--根据日志重算所有次数
function PlayerInfo:SetWelfareBackAllNum()
	outFmtDebug("----------------------------------")
	local questMgr = self:getQuestMgr()
	--找回类型循环
	for i=0,WELFA_BACK_TYPE_COUNT do
		local type = i+1
		local maxNum = self:GetWelfareBackMaxNum(type)
		if maxNum > 0 then
			local allNum = 0
			--找回天数循环
			for j=-3,-1 do
				local time = GetTodayStartTimestamp(j)
				local curnum = questMgr:getWelfareBackNum(type,time)
				if curnum < maxNum and curnum >= 0 then
					allNum = allNum + maxNum - curnum
				end
				
				-- outFmtDebug("type:%d curnum:%d",type,curnum)
			end
			
			local time = GetTodayStartTimestamp(0)
			local curnum = questMgr:getWelfareBackNum(type,time)
			outFmtDebug("type:%d today:%d",type,curnum)
			
			questMgr:setWelfareBackAllNum(type,allNum)
			--outFmtDebug("--------")
		end
	end
end
--清理可以找回的次数
function PlayerInfo:ClearWelfareBackAllNum()

	local questMgr = self:getQuestMgr()
	--找回类型循环
	for i=0,WELFA_BACK_TYPE_COUNT do
		local type = i+1
		local maxNum = self:GetWelfareBackMaxNum(type)
		if maxNum > 0 then
			local allNum = 0
			--找回天数循环
			for j=-3,-1 do
				local time = GetTodayStartTimestamp(j)
				questMgr:setWelfareBackNum(type,time,maxNum)
			end

			questMgr:setWelfareBackAllNum(type,0)
		end
	end
end

function PlayerInfo:GetWelfareBackRewardCost(type,bestGetback)
	local config = tb_welfare_back[type]
	local cost
	if bestGetback then
		cost = GetCostMulTab(config.allcost,config.alldc/10)
	else
		cost = GetCostMulTab(config.basecost,config.basedc/10)
	end
	return cost
end

------需要根据逻辑特殊处理---------------------------------------
--所有类型列表
function PlayerInfo:GetWelfareBackTypeAry()
	return {1,2,3,4,5}
end

function PlayerInfo:GetWelfareBackMaxNum(type)
	-- 1-5 表示资源副本 	
	if type >= 1 and type <= 5 then
		return tb_instance_res[type].times
	end

	return 0
end

function PlayerInfo:GetWelfareBackRewardData(type,bestGetback)
	-- 1-5 表示资源副本 	
	if type >= 1 and type <= 5 then
		local lev = self:GetLevel()
		local id = type * 10000 + lev * 100
		local config = tb_welfare_back_data[id]
		
		if config then
			if bestGetback then
				return config.bestitem
			else
				return config.baseitem
			end
		end
	end
	return nil
end

------需要根据逻辑特殊处理-end--------------------------------------
--累计元宝充值奖励
function PlayerInfo:GetWelfareRechargeReward(id)
	if id < 1 or id > 32 then
		outFmtError("GetWelfareRechargeReward id %d error",id)
		return
	end
	local config = tb_welfare_recharge[id]
	
	if not config then
		outFmtError("GetWelfareRechargeReward config %d not exist",id)
		return
	end
	
	local questMgr = self:getQuestMgr()
	if questMgr:GetRechargeRewardFlag(id - 1) then
		outFmtError("GetWelfareRechargeReward reward %d already get",id)
		return
	end
	
	if self:GetRechageSum() < config.money then
		outFmtError("GetWelfareRechargeReward money %d not reach target",self:GetRechageSum())
		return
	end
	
	self:AppdAddItems(config.item,MONEY_CHANGE_RECHARGE_REWARD,LOG_ITEM_OPER_TYPE_RECHARGE_REWARD)
	questMgr:SetRechargeRewardFlag(id - 1)
	
end

--累计元宝消费奖励
function PlayerInfo:GetWelfareConsumeReward(id)
	if id < 1 or id > 32 then
		outFmtError("GetWelfareConsumeReward id %d error",id)
		return
	end
	
	local config = tb_welfare_consume[id]
	
	if not config then
		outFmtError("GetWelfareConsumeReward config %d not exist",id)
		return
	end
	
	local questMgr = self:getQuestMgr()
	if questMgr:GetConsumeRewardFlag(id - 1) then
		outFmtError("GetWelfareConsumeReward reward %d already get",id)
		return
	end
	
	if self:GetConsumeSum() < config.money then
		outFmtError("GetWelfareConsumeReward money %d not reach target",self:GetConsumeSum())
		return
	end
	
	self:AppdAddItems(config.item,MONEY_CHANGE_CONSUME_REWARD,LOG_ITEM_OPER_TYPE_CONSUME_REWARD)
	questMgr:SetConsumeRewardFlag(id - 1)
end


function PlayerInfo:GetWelfareSevendayReward(id)
	if id < 1 or id > 7 then
		outFmtError("GetWelfareSevendayReward id %d error",id)
		return
	end
	
	local config = tb_welfare_sevengift[id]
	
	if not config then
		outFmtError("GetWelfareSevendayReward config %d not exist",id)
		return
	end
	
	local questMgr = self:getQuestMgr()
	if questMgr:GetSevenDayFlag(id - 1) then
		outFmtError("GetWelfareSevendayReward reward %d already get",id)
		return
	end
	
	if questMgr:GetSevenDayProcess() < id then
		outFmtError("GetWelfareSevendayReward login day %d not reach target",self:GetSevenDayProcess())
		return
	end
	
	self:AppdAddItems(config.item,MONEY_CHANGE_SEVEN_DAY_GIFT,LOG_ITEM_OPER_TYPE_SEVEN_DAY_GIFT)
	questMgr:SetSevenDayFlag(id - 1)
end

--使用兑换码
function PlayerInfo:UseGiftcode(giftcode)
	outFmtInfo("UseGiftcode code = @@@%s@@@",giftcode)
	local code_config = tb_giftcode[giftcode]
	if not code_config then
		--无效兑换码
		self:CallOptResult(OPRATE_TYPE_GIFTCODE,GIFTCODE_NOTICE_TYPE_INVALID,{})
		return
	end
	
	local type_config = tb_giftcode_type[code_config.type]
	
	if not type_config then
		--无效兑换码
		self:CallOptResult(OPRATE_TYPE_GIFTCODE,GIFTCODE_NOTICE_TYPE_INVALID,{})
		return
	end
	
	if type_config.once == 1 then --一次性兑换码
		if CheckGiftcodeIsUsed(giftcode) == 1 then
			--该兑换码已经被使用过了
			self:CallOptResult(OPRATE_TYPE_GIFTCODE,GIFTCODE_NOTICE_TYPE_USED,{})
			return
		end
		
		if self:GetGiftcodeTypeFlag(code_config.type) then
			--已领取过该类型礼包
			self:CallOptResult(OPRATE_TYPE_GIFTCODE,GIFTCODE_NOTICE_TYPE_ALREADY_GET,{})
			return
		end
	
		AddUsedGiftcode(giftcode)
		
		self:SetGiftcodeTypeFlag(code_config.type)
		
		--local desc = type_config.mail_desc
		--local name = type_config.mail_name
		--local reward = type_config.reward_str
		--local giftType = GIFT_PACKS_TYPE_GIFTCODE
		--AddGiftPacksData(self:GetGuid(),0,giftType,os.time(),os.time() + 86400*30, name, desc, reward, SYSTEM_NAME)
		
		local list = {}
		for _,v in ipairs(type_config.reward) do
			--奖励通知
			local stru = item_reward_info_t .new()
			stru.item_id	= v[1]
			stru.num 		= v[2]
			table.insert(list, stru)
		end
		self:call_show_giftcode_reward_list(list)
		
		self:AppdAddItems(type_config.reward, MONEY_CHANGE_GIFTCODE, LOG_ITEM_OPER_TYPE_GIFTCODE)
		--兑换成功
		self:CallOptResult(OPRATE_TYPE_GIFTCODE,GIFTCODE_NOTICE_TYPE_SUCCESS,{type_config.name})
		
	elseif type_config.once == 0 then --通用兑换码
		
		if self:GetGiftcodeTypeFlag(code_config.type) then
			--已领取过该类型礼包
			self:CallOptResult(OPRATE_TYPE_GIFTCODE,GIFTCODE_NOTICE_TYPE_ALREADY_GET,{})
			return
		end
		
		self:SetGiftcodeTypeFlag(code_config.type)
	--[[local desc = type_config.mail_desc
		local name = type_config.mail_name
		local reward = type_config.reward_str
		local giftType = GIFT_PACKS_TYPE_GIFTCODE
		AddGiftPacksData(self:GetGuid(),0,giftType,os.time(),os.time() + 86400*30, name, desc, reward, SYSTEM_NAME)--]]
		local list = {}
		for _,v in ipairs(type_config.reward) do
			--奖励通知
			local stru = item_reward_info_t .new()
			stru.item_id	= v[1]
			stru.num 		= v[2]
			table.insert(list, stru)
		end
		self:call_show_giftcode_reward_list(list)
		
		self:AppdAddItems(type_config.reward, MONEY_CHANGE_GIFTCODE, LOG_ITEM_OPER_TYPE_GIFTCODE)
		--兑换成功
		self:CallOptResult(OPRATE_TYPE_GIFTCODE,GIFTCODE_NOTICE_TYPE_SUCCESS,{type_config.name})
	end
	
end

function PlayerInfo:SetGiftcodeTypeFlag(id)
	local index, offset = getRealOffset(id,32)
	if index < 0 or index > MAX_GIFTCODE_TYPE_FLAG_COUNT - 1 then
		outFmtError("SetGiftcodeTypeFlag id %d bigger than limit %d",id,MAX_GIFTCODE_TYPE_FLAG_COUNT * 32)
		return
	end
	
	self:SetBit(PLAYER_INT_FIELD_GIFTCODE_TYPE_FLAG_START + index, offset)
end

function PlayerInfo:GetGiftcodeTypeFlag(id)
	local index, offset = getRealOffset(id,32)
	if index < 0 or index > MAX_GIFTCODE_TYPE_FLAG_COUNT - 1 then
		outFmtError("SetGiftcodeTypeFlag id %d bigger than limit %d",id,MAX_GIFTCODE_TYPE_FLAG_COUNT * 32)
		return true
	end
	
	return self:GetBit(PLAYER_INT_FIELD_GIFTCODE_TYPE_FLAG_START + index, offset)
end