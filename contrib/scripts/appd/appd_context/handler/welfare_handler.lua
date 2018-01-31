
--领取首冲奖励
function PlayerInfo:Handle_Welfare_Shouchong(pkt)
	--local questMgr = self:getQuestMgr()
	--self:WelfareShouchong()
end

function PlayerInfo:Handle_Get_Seven_Day_Recharge_Extra_Reward(pkt)
	local id = pkt.id
	local questMgr = self:getQuestMgr()
	self:GetSevenDayRechargeExtraReward(id)
end

--领取签到奖励
function PlayerInfo:Handle_Welfare_CheckIn(pkt)
	local day = tonumber(os.date("%d", os.time()))
	self:WelfareCheckIn(day)
end

--领取累积签到奖励
function PlayerInfo:Handle_Welfare_CheckInAll(pkt)
	local id = pkt.id
	self:WelfareCheckInAll(id)
end
--补签奖励
function PlayerInfo:Handle_Welfare_CheckIn_Getback(pkt)

	local day = pkt.id
	--outFmtDebug("day get back %d",day)
	local curday = tonumber(os.date("%d", os.time()))
	if day >= curday then
		return
	end
	--if self:GetVIP() == 0 then
		--return
	--end
	
	if self:getQuestMgr():getWelfareCheckIn(day) then 
		--self:CallOptResult(OPRATE_TYPE_ACTIVITY, ACTIVITY_OPERATE_HASGET)
		return
	end
	local count = self:GetUInt32(PLAYER_INT_FIELD_WELFARE_CHECKIN_GETBACK_COUNT)
	local config = tb_welfare_checkin[count + 1]
	
	if config and self:useAllItems(MONEY_CHANGE_CHECKIN_GETBACK, nil, config.getback_cost) then
		self:AddUInt32(PLAYER_INT_FIELD_WELFARE_CHECKIN_GETBACK_COUNT,1)
		self:WelfareCheckIn(day)
	end
end

--领取等级奖励
function PlayerInfo:Handle_Welfare_Level(pkt)
	local id = pkt.id
	self:WelfareLevel(id)
end

--领取找回奖励
function PlayerInfo:Handle_Welfare_ActiveGetback(pkt)
	local type = pkt.id
	if type < 1 or type > 5 then
		return
	end
	local best
	if pkt.best == 1 then
		best = true
	else 
		best = false
	end
	local num = pkt.num
	
	if num < 1 then
		return
	end
	self:GetWelfareBackReward(type,best,num)
end
--一键找回奖励列表
function PlayerInfo:Handle_Welfare_List_Getback(pkt)
	local best
	if pkt.best == 1 then
		best = true
	else 
		best = false
	end
	self:GetWelfareAllRewardList(best)
end
--一键领取找回奖励
function PlayerInfo:Handle_Welfare_All_Getback(pkt)
	local best
	if pkt.best == 1 then
		best = true
	else 
		best = false
	end
	self:GetWelfareAllReward(best)
end

function PlayerInfo:Handle_Welfare_Get_Recharge_Reward(pkt)
	local id = pkt.id
	self:GetWelfareRechargeReward(id)
end

function PlayerInfo:Handle_Welfare_Get_Consume_Reward(pkt)
	local id = pkt.id
	self:GetWelfareConsumeReward(id)
end

function PlayerInfo:Handle_Welfare_Get_Sevenday_Reward(pkt)
	local id = pkt.id
	self:GetWelfareSevendayReward(id)
end


function PlayerInfo:Handle_Use_Giftcode(pkt)
	local giftcode = pkt.giftcode
	self:UseGiftcode(giftcode)
end