
local security = require("base/Security")

local sub = "group_instance"
function PlayerInfo:OnCheckGroupInstanceMatch()
	-- ƥ��Ĳ�����Ӹ���
	if not app:IsKuafuTypeMatching(self:GetGuid(), KUAFU_TYPE_GROUP_INSTANCE) then
		return
	end
	
	local url = string.format("%s%s/check_match", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	local indx = app:GetKuafuTypeMatchingArg(self:GetGuid())
	-- ��������Ӹ�������ƥ�����Ϣ
	data.player_guid = self:GetGuid()
	data.indx = indx
	outFmtDebug("$$$$$$$$$$$$$$$$$$$$$$ %d", data.indx)
	data.open_time = 1
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("OnCheckGroupInstanceMatch response = %s", response)
		end
		local dict = nil
		security.call(
			--try block
			function()
				dict = json.decode(response)
			end
		)
		
		
		if dict then
			outFmtDebug("OnCheckGroupInstanceMatch result %d %s", dict.ret, dict.msg)
			-- ƥ�䵽��
			if dict.ret == 0 then
				local login_fd = serverConnList:getLogindFD()
				local guid = self:GetGuid()
				-- dict.enter_info = json.decode(dict.enter_info)
				local enter_info = dict.enter_info
				if type(enter_info) == "string" then
					enter_info = json.decode(enter_info)
				end
				
				-- �Ѿ�ƥ�䵽��
				app:SetMatchingKuafuType(self:GetGuid(), nil)
				
				-- ��ʱ���ܿ۽���ȯ�Ͳ��ý�
				--local config = tb_kuafu_xianfu_condition[indx]
				--if not self:useMulItem(config.ticket) then
				--	return
				--end
				
				-- ���ӽ������
				--local instMgr = self:getInstanceMgr()
				--instMgr:AddXianfuDayTimes()
				
				-- ��web��Ǯ(��Ȼ�п������ݱȽ�������)
				--self:OnSaveMoney()
				
				local pos = enter_info.pos
				local war_id = enter_info.war_id
				local battle_server = enter_info.battle_server
				outFmtInfo("$$$$ on xianfu matched guid = %s war_id = %s battle_server = %s", self:GetGuid(), war_id, battle_server)
				call_appd_login_to_send_kuafu_info(login_fd, guid, war_id, indx, battle_server, '', KUAFU_TYPE_GROUP_INSTANCE)
				-- �������ڽ��п����־
				self:KuafuMarked(KUAFU_TYPE_GROUP_INSTANCE)
				
			-- timeoutȡ��ƥ��
			elseif dict.ret == 1 then
				local target = dict.target
				local count = dict.count
				outFmtDebug("taget = %d, count = %d", target, count)
				self:call_kuafu_match_wait(KUAFU_TYPE_GROUP_INSTANCE, target ,count, indx, '')
			elseif dict.ret == 2 then
				outFmtDebug("== player on cancel match, %s", self:GetGuid())
				self:OnCancelMatch(KUAFU_TYPE_GROUP_INSTANCE)
			end
		end
	end)
end


-- ȡ��ƥ����Ӹ���
function PlayerInfo:OnCancelGroupInstanceMatchBeforeOffline()
	
	if not app:IsKuafuTypeMatching(self:GetGuid(), KUAFU_TYPE_GROUP_INSTANCE) then
		return
	end
	
	local url = string.format("%s%s/cancel_match", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	data.player_guid = self:GetGuid()
	data.indx = app:GetKuafuTypeMatchingArg(self:GetGuid())
	outFmtDebug("OnCancelGroupInstanceMatchBeforeOffline %d", data.indx)
	data.open_time = 1
	self:OnCancelMatch(KUAFU_TYPE_GROUP_INSTANCE)
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("OnCancelGroupInstanceMatchBeforeOffline response = %s", response)
		end
	end)
end


-- ƥ����Ӹ���
function PlayerInfo:OnGroupInstanceMatch(indx)
	-- �Ѿ��ڿ����
	if self:IsKuafuing() then
		return false
	end
	
	if app:IsInKuafuTypeMatching(self:GetGuid()) then
		return false
	end
	
	outFmtInfo("###OnGroupInstanceMatch guid = %s", self:GetGuid())
	local url = string.format("%s%s/match", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	data.player_guid = self:GetGuid()
	data.open_time = 1
	data.indx = indx
	
	app:SetMatchingKuafuType(self:GetGuid(), KUAFU_TYPE_GROUP_INSTANCE + indx * 65536)
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("OnGroupInstanceMatch response = %s", response)
		end
		local dict = nil
		security.call(
			--try block
			function()
				dict = json.decode(response)
			end
		)
		
		if dict then
			outFmtDebug("OnGroupInstanceMatch %d %s", dict.ret, dict.msg)
		end
	end)
	
	return true
end


-- �������Ӹ�������
function PlayerInfo:CheckGroupInstanceReward()
	local url = string.format("%s%s/check_match_result", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	data.player_guid = self:GetGuid()
	data.open_time = 1
	
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("CheckGroupInstanceReward response = %s", response)
		end
		local dict = nil
		security.call(
			--try block
			function()
				dict = json.decode(response)
			end
		)
		if dict then
			outFmtDebug("%d %s %s", dict.ret, dict.msg, self:GetGuid())
			
			if dict.ret == 0 then
				local id = tonumber(dict.details)
				
				-- ѡȡͨ�ؽ���
				local config = tb_group_instance_base[id]
				local itemKeys = config.fpRewardId
				local itemVals = config.fpRewardCnt
				if self:GetGroupInstanceClearFlag(id) then
					itemKeys = config.passRewardId
					itemVals = config.passRewardCnt
					
					-- �۴���
					local instMgr = self:getInstanceMgr()
					instMgr:SubGroupInstanceChallengeCount(1)
				end
				self:SetGroupInstanceClearFlag(id)
				local vip = self:GetVIP()
				local rewardDict = {}
				for i = 1, #itemKeys do
					local itemId = itemKeys[ i ]
					local count  = math.floor(itemVals[ i ] * (1 + tb_vip_base[vip].groupReward / 100))
					table.insert(rewardDict, {itemId, count})
				end
				
				self:AppdAddItems(rewardDict, MONEY_CHANGE_KUAFU_GROUP_INSTANCE, LOG_ITEM_OPER_TYPE_GROUP_INSTANCE)
				
				self:onAddMeridianExpSource(MERIDIAN_EXP_SOURCE_GROUP_INSTANCE)
				
				self:AddActiveItem(VITALITY_TYPE_GROUP_INSTANCE)
			end
		end
		
	end)
end


-- ����������
function PlayerInfo:OnBuyGroupInstanceTicket(count)
	local buy_type = tb_group_instance_buy[1].buy_type
	local buy_price = tb_group_instance_buy[1].buy_price
	local instMgr = self:getInstanceMgr()
	local buy_count = instMgr:GetGroupInstanceBuyCount()
	
	if buy_count + count > #buy_type then
		outFmtError("OnBuyGroupInstanceTicket buy more than limit")
		return
	end
	
	local cost_table = {}
	
	for i = buy_count + 1,buy_count+ count do
		if cost_table[buy_type[i]] then
			cost_table[buy_type[i]] = cost_table[buy_type[i]] + buy_price[i]
		else
			cost_table[buy_type[i]] = buy_price[i]
		end
	end
	
	local cost = {}
	for k,v in pairs(cost_table) do
		table.insert(cost, {k,v})
	end
	
	if self:costMoneys(MONEY_CHANGE_GROUP_INSTANCE_BUY_TIMES, cost, 1) then
		instMgr:AddGroupInstanceChallengeCount(count)
		instMgr:AddGroupInstanceBuyCount(count)
		
		outFmtDebug("OnBuyGroupInstanceTicket ticket :%d",instMgr:GetGroupInstanceChallengeCount())
		outFmtDebug("OnBuyGroupInstanceTicket buy count :%d",instMgr:GetGroupInstanceBuyCount())
	else
		outFmtError("OnBuyGroupInstanceTicket resource not enough")
	end
	
end

-- ������Ӹ���
function PlayerInfo:OnResetGroupInstanceDayTimes()
	local instMgr = self:getInstanceMgr()
	instMgr:ResetGroupInstanceDayTimes()
end

--��ս����
function PlayerInfo:MatchGroupInstance(id)
	local config = tb_group_instance_base[id]
	if not config then
		outFmtError("OnChallengeGroupInstance id:%d not exist",id)
		return
	end
	
	if self:GetLevel() < config.limLev then
		outFmtError("OnChallengeGroupInstance level not enough")
		return
	end
	local instMgr = self:getInstanceMgr()
	local count = instMgr:GetGroupInstanceChallengeCount()
	if count == 0 then
		outFmtError("OnChallengeGroupInstance ticket not enough")
		return
	end
	
	--��ʼƥ��
	outFmtDebug("MatchGroupInstance begin match")
end

