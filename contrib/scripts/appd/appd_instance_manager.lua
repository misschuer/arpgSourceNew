local protocols = require('share.protocols')

local AppInstanceMgr = class("AppInstanceMgr", BinLogObject)

function AppInstanceMgr:ctor()
	
end

function AppInstanceMgr:checkIfCanEnterTrial()
	--[[INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT	= INSTANCE_INT_FIELD_VIP_END,					//(0:���տ�ɨ������,1:��ʷͨ�ز���)
	INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT	= INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT + 1,	//(0:ɨ������,1:�ɹ���ɨ������)--]]
	
	local passed = self:GetUInt16(INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT, 1)
	if passed == #tb_instance_trial then
		outFmtError("reach top layer")
		return
	end
	
	local nextId = passed + 1
	local player = self:getOwner()
	local config = tb_instance_trial[nextId]
	
	local gerneralId = string.format("%d:%d:%s", nextId, getMsTime(), player:GetGuid())
	
	call_appd_teleport(player:GetScenedFD(), player:GetGuid(), config.x, config.y, config.mapid, gerneralId)
	
	local questMgr = player:getQuestMgr()
	questMgr:OnUpdate(QUEST_TARGET_TYPE_TRIAL_INSTANCE)
	
	player:AddActiveItem(VITALITY_TYPE_TRIAL_INSTANCE)
end


-- ͨ�ز���
function AppInstanceMgr:passInstance(id)
	self:SetUInt16(INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT, 1, id)
end

-- һ��ɨ��������
function AppInstanceMgr:sweepTrialInstance()
	local prevSweepTimes = self:GetUInt16(INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT, 0)
	if prevSweepTimes == 0 then
		outFmtError("no times to sweepTrialInstance")
		return
	end
	
	local layers = self:GetUInt16(INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT, 0)
	-- ��ûͨ��û��Ҫɨ��
	if layers == 0 then
		outFmtError("please pass the 1st layer first")
		return
	end
	
	self:SetUInt16(INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT, 0, prevSweepTimes - 1)
	local player = self:getOwner()
	
	local dict = {}
	for i = 1, layers do
		local dropIdTable = tb_instance_trial[ i ].reward
		DoRandomDropTable(dropIdTable, dict)
	end
	
	local playerInfo = self:getOwner()
	local vip = playerInfo:GetVIP()
	local itemDict = {}
	for entry, count in pairs(dict) do
		count = math.floor(count * (1 + tb_vip_base[vip].trialReward / 100))
		table.insert(itemDict, {entry, count})
	end
	
	playerInfo:AppdAddItems(itemDict, MONEY_CHANGE_TRIAL_INSTANCE_REWARD, LOG_ITEM_OPER_TYPE_TRIAL_INSTANCE_REWARD)
	
	-- ɨ���Ľ������
	local list = Change_To_Item_Reward_Info(dict, true)
	playerInfo:call_sweep_instance_reward (INSTANCE_SUB_TYPE_TRIAL, 0, 0, 0, list)
	
	playerInfo:AddActiveItem(VITALITY_TYPE_TRIAL_INSTANCE)
end

function AppInstanceMgr:checkIfCanEnterVIP(id, hard)

	local config = tb_map_vip[id]

	-- �ж�VIP�Ƿ���������
	local player = self:getOwner()
	if not player:isVIP(config.vip) then
		outFmtError("vip level not satisfy")
		return
	end
	
	if not self:isEnoughForceByHard(id, hard, player:GetForce()) then
		outFmtError("no force to enter hard = %s", hard)
		return
	end
	
	-- �жϽ�������Ƿ��㹻
	-- ÿ����Ϣ4��byte[0:ͨ���Ѷ�,1:��ǰ�Ѷ�,2:��ս����,3:�������]
	
	local indx = INSTANCE_INT_FIELD_VIP_START + id - 1
	local times = self:GetByte(indx, 2)
	local x 	= config.x
	local y 	= config.y
	local mapid = config.mapid
	
	if times == config.times then
		outFmtError("try time is not fit for mapid %d", mapid)
		return
	end
	
	self:AddByte(indx, 2, 1)
	
	local gerneralId = string.format("%d:%s:%d_%d:%s", id, hard, times, getMsTime(), player:GetGuid())
	
	-- ������
	call_appd_teleport(player:GetScenedFD(), player:GetGuid(), x, y, mapid, gerneralId)
end

-- ͨ���Ѷ�
function AppInstanceMgr:passVipInstance(id, hard)
	local indx = INSTANCE_INT_FIELD_VIP_START + id - 1
	local cmp = self:GetByte(indx, 1)
	local max = cmp
	
	if max < hard then
		max = hard
	end
	
	if max > cmp then
		outFmtInfo("vip instance passed, id = %d, hard = %d ", id, hard)
		self:SetByte(indx, 1, max)
	end
end

function AppInstanceMgr:isEnoughForceByHard(id, hard, force)
	hard = tonumber(hard)
	local config = tb_map_vip[id]
	return force >= config.forces[hard]
end

-- һ��ɨ��VIP
function AppInstanceMgr:sweepVIPInstance(id, hard)

	local dict = {}
	local dropIdTable = tb_map_vip[id].rewards[hard]
	
	DoRandomDropTable(dropIdTable, dict)
	
	local itemDict = {}
	for entry, count in pairs(dict) do
		table.insert(itemDict, {entry, count})
	end
	
	local playerInfo = self:getOwner()
	playerInfo:AppdAddItems(itemDict, MONEY_CHANGE_VIP_INSTANCE_REWARD, LOG_ITEM_OPER_TYPE_VIP_INSTANCE_REWARD)
	
	-- ɨ���Ľ������
	local list = Change_To_Item_Reward_Info(dict, true)
	playerInfo:call_sweep_instance_reward (INSTANCE_SUB_TYPE_VIP, 0, 0, 0, list)
end

-------------------------------��Դ����------------------------------
function AppInstanceMgr:checkIfCanEnterResInstance(id)
	
	outFmtDebug("appd enter res %d",id)
	local config = tb_instance_res[id]
	
	
	local player = self:getOwner()
	
	
	-- �жϽ�������Ƿ��㹻
	-- ÿ����Ϣ4��byte[0:��ս����,1:Ԥ��,2:Ԥ��,3:Ԥ��]
	
	local indx = INSTANCE_INT_FIELD_RES_START + id - 1
	local times = self:GetByte(indx, 0)
	local mapid = config.mapid
	
	local allTime = config.times
	
	outFmtDebug("times %d ,mapID %d",times,mapid)
	--�жϴ���
	if times >= allTime then
		outFmtError("try time is not fit for mapid %d", mapid)
		return
	end
	--�жϵȼ�
	local lev = player:GetLevel()
	if lev < config.limLev then
		outFmtError("res instance Limit lev %d", lev)
		return
	end
	
	local x 	= config.x
	local y 	= config.y
	
	player:AddActiveItem(VITALITY_TYPE_RES_INSTANCE)
	
	local gerneralId = string.format("%d:%d:%s", id, getMsTime(), player:GetGuid())
	
	outFmtDebug("gerneralId %s",gerneralId)
	
	-- ������
	call_appd_teleport(player:GetScenedFD(), player:GetGuid(), x, y, mapid, gerneralId)
	
	local questMgr = player:getQuestMgr()
	questMgr:OnUpdate(QUEST_TARGET_TYPE_RESOURCE_INSTANCE, {mapid})
end


-- ͨ����Դ����
function AppInstanceMgr:passResInstance(id)
	--outFmtDebug("ton guan zi yuan fu ben %d *************************************",id)
	local idx =  INSTANCE_INT_FIELD_RES_START + id - 1
	self:AddByte(idx, 0, 1)
	local pas = self:GetByte(idx,1)
	if pas == 0 then
		self:SetByte(idx,1,1)
	end
end

-- ɨ����Դ����
function AppInstanceMgr:sweepResInstance(id)
	--print("AppInstanceMgr:sweepResInstance")
	local baseIdx =  INSTANCE_INT_FIELD_RES_START + id - 1
	local pas = self:GetByte(baseIdx,1)
	if pas == 1 then
		--print("begin sao dang")
		
		--tb_instance_reward
		local baseconfig = tb_instance_res[id]
		local times = self:GetByte(baseIdx, 0)
		
		local allTime = baseconfig.times
		local player = self:getOwner()
		local vip = player:GetVIP()
		
		--�жϴ���
		if times >= allTime then
			outFmtError("try time is not fit for mapid  %d",times)
			return
		end
		
		local playerInfo = self:getOwner()
		local idx = id * 1000 + playerInfo:GetLevel()
		local config = tb_instance_reward[idx]
		
		local tab = {}
		for _, rewardInfo in pairs(config.reward) do
			table.insert(tab, rewardInfo)
		end
		local randomReward = config.randomreward
		if #randomReward > 0 then
			local rewardIdx = randInt(1, #randomReward)
			table.insert(tab,randomReward[rewardIdx])
		end
		tab = rewardsAddExtraAndClone(tab, tb_vip_base[vip].resReward / 100)
		
		local list = {}
		
		for _,v in ipairs(tab) do
			--����֪ͨ
			local stru = item_reward_info_t .new()
			stru.item_id	= v[1]
			stru.num 		= v[2]
			table.insert(list, stru)
		end
		
		playerInfo:PlayerAddItems(tab,MONEY_CHANGE_VIP_INSTANCE_SWEEP,LOG_ITEM_OPER_TYPE_INSTANCE_SWEEP)
		
		--��Ӵ���
		self:AddByte(baseIdx, 0, 1)
		
		player:AddActiveItem(VITALITY_TYPE_RES_INSTANCE)
		
		protocols.call_sweep_instance_reward ( player, INSTANCE_SUB_TYPE_RES, id, 0, 0, list)
		
	else
		outFmtDebug("not first res instance")
	end
end

-- ����������
function AppInstanceMgr:resetTrialInstance()
	local prevSweepTimes	= self:GetUInt16(INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT, 0)
	local prevBuyTimes		= self:GetUInt16(INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT, 1)
	
	if prevSweepTimes > 0 then
		outFmtError("not need to resetTrialInstance")
		return
	end
	
	local passed = self:GetUInt16(INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT, 1)
	if passed == 0 then
		outFmtError("you can resetTrialInstance after pass the 1st layer")
		return
	end
	
	if prevBuyTimes == 0 then
		outFmtError("no time to buy to resetTrialInstance")
		return
	end
	
	-- �ж��ܷ�Ԫ��
	local costs = tb_instance_trial[passed].resetCosts
	local player = self:getOwner()
	if not player:useAllItems(MONEY_CHANGE_RESET_TRIAL, costs) then
		outFmtError("gold is not enough")
		return
	end
	
	-- �۹������
	self:SetUInt16(INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT, 1, prevBuyTimes - 1)
	
	-- �Ӵ���
	self:SetUInt16(INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT, 0, 1)
	
	-- �޸Ľ��տ�ɨ������
	self:SetUInt16(INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT, 0, passed)
end

-- ����ÿ������
function AppInstanceMgr:instanceDailyReset()
	-- ����VIP����
	for i = INSTANCE_INT_FIELD_VIP_START, INSTANCE_INT_FIELD_VIP_END-1 do
		local id = i - INSTANCE_INT_FIELD_VIP_START + 1
		self:SetByte(i, 2, 0)
		self:SetByte(i, 3, 0)
	end
	
	-- ����������
	self:SetUInt16(INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT, 1, 1)
	self:SetUInt16(INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT, 0, 1)
	local passed = self:GetUInt16(INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT, 1)
	self:SetUInt16(INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT, 0, passed)
	
	-- ������Դ����
	for i = INSTANCE_INT_FIELD_RES_START,INSTANCE_INT_FIELD_RES_END-1 do
		self:SetByte(i,0,0)
	end
end

-------------------------------�------------------------------
--���û����
function AppInstanceMgr:setActiveNum(id,num)
	self:SetUInt32(INSTANCE_INT_FIELD_ACTIVE_START + id - 1,num)
end

function AppInstanceMgr:getActiveNum(id)
	return self:GetUInt32(INSTANCE_INT_FIELD_ACTIVE_START + id - 1)
end

--���ӻ�Ծ��
function AppInstanceMgr:addActivity(num)
	self:AddUInt32(INSTANCE_INT_FIELD_ACTIVE,num)
end

--���û�Ծ��
function AppInstanceMgr:setActivity(num)
	self:SetUInt32(INSTANCE_INT_FIELD_ACTIVE,num)
end

--��ȡ�ܻ�Ծ��
function AppInstanceMgr:getActivity()
	return self:GetUInt32(INSTANCE_INT_FIELD_ACTIVE)
end

function AppInstanceMgr:hasGetActivityReward(offset)
	return self:GetBit(INSTANCE_INT_FIELD_ACTIVE_REWARD,offset)
end

function AppInstanceMgr:SetActivityReward(offset)
	self:SetBit(INSTANCE_INT_FIELD_ACTIVE_REWARD,offset)
end

-------------------------------�end------------------------------

-------------------------------����------------------------------
--3v3�ѲμӴ���
function AppInstanceMgr:get3v3EnterTimes()
	return self:GetUInt16(INSTANCE_INT_FIELD_3V3_TIMES,0)
end

--����3v3�μӴ���
function AppInstanceMgr:add3v3EnterTimes()
	self:AddUInt16(INSTANCE_INT_FIELD_3V3_TIMES,0,1)
end

function AppInstanceMgr:set3v3EnterTimes(num)
	self:SetUInt16(INSTANCE_INT_FIELD_3V3_TIMES,0,num)
end

--3v3�ѹ������
function AppInstanceMgr:get3v3BuyTimes()
	return self:GetUInt16(INSTANCE_INT_FIELD_3V3_TIMES,1)
end

function AppInstanceMgr:add3v3BuyTimes(num)
	self:AddUInt16(INSTANCE_INT_FIELD_3V3_TIMES,1,num)
end

--��ȡ3v3ÿ�ս���״̬
function AppInstanceMgr:get3v3DayReward(id)
	return self:GetByte(INSTANCE_INT_FIELD_3V3_DAY_REWARD,id-1)
end

--����3v3ÿ�ս���״̬
function AppInstanceMgr:set3v3DayReward(id)
	return self:SetByte(INSTANCE_INT_FIELD_3V3_DAY_REWARD,id-1,1)
end

--��ȡ3v3��λ����ʱ���
function AppInstanceMgr:get3v3SegmentTime()
	return self:GetUInt32(INSTANCE_INT_FIELD_3V3_SEGMENT_TIME)
end

--����3v3��λ����ʱ���
function AppInstanceMgr:set3v3SegmentTime(time)
	return self:SetUInt32(INSTANCE_INT_FIELD_3V3_SEGMENT_TIME,time)
end

-------------------------------����end------------------------------


-------------------------------����̨------------------------------
--����̨�ѲμӴ���
function AppInstanceMgr:getDoujianEnterTimes()
	return self:GetUInt16(INSTANCE_INT_FIELD_DOUJIAN_TIMES,0)
end

--���Ӷ���̨�μӴ���
function AppInstanceMgr:addDoujianEnterTimes()
	self:AddUInt16(INSTANCE_INT_FIELD_DOUJIAN_TIMES,0,1)
end
--���ö���̨�μӴ���
function AppInstanceMgr:setDoujianEnterTimes(num)
	self:SetUInt16(INSTANCE_INT_FIELD_DOUJIAN_TIMES,0,num)
end

--����̨�ѹ������
function AppInstanceMgr:getDoujianBuyTimes()
	return self:GetUInt16(INSTANCE_INT_FIELD_DOUJIAN_TIMES,1)
end
--���Ӷ���̨�ѹ������
function AppInstanceMgr:addDoujianBuyTimes(num)
	self:AddUInt16(INSTANCE_INT_FIELD_DOUJIAN_TIMES,1,num)
end

--����̨CDʱ���
function AppInstanceMgr:getDoujianCD()
	return self:GetUInt32(INSTANCE_INT_FIELD_DOUJIAN_FIGHT_CD)
end

--���ö���̨CDʱ���
function AppInstanceMgr:setDoujianCD(time)
	self:SetUInt32(INSTANCE_INT_FIELD_DOUJIAN_FIGHT_CD,time)
end


--���ö���̨��ʤ״̬
function AppInstanceMgr:setDoujianFirstRank(rank)
	
	for i,v in ipairs(tb_doujiantai_first) do
		if rank <= v.rank then
			if not self:GetBit(INSTANCE_INT_FIELD_DOUJIAN_FIRST_GET,i) then
				self:SetBit(INSTANCE_INT_FIELD_DOUJIAN_FIRST_GET,i)
			end
			
		end
	end
	
end

function AppInstanceMgr:getDoujianFirstRank(id)
	return self:GetBit(INSTANCE_INT_FIELD_DOUJIAN_FIRST_GET,id)
end

--����̨��ʷ�������
function AppInstanceMgr:setDoujianMaxRank(rank)
	local cur = self:GetUInt32(INSTANCE_INT_FIELD_DOUJIAN_MAX_RANK)
	if cur == 0 or cur > rank then
		self:SetUInt32(INSTANCE_INT_FIELD_DOUJIAN_MAX_RANK,rank)
	end
	
end
--����̨��ʤ������ȡ״̬
function AppInstanceMgr:getDoujianFirstReward(id)
	return self:GetBit(INSTANCE_INT_FIELD_DOUJIAN_FIRST_REWARD,id)
end
--��ȡ����̨��ʤ������ȡ״̬
function AppInstanceMgr:setDoujianFirstReward(id)
	self:SetBit(INSTANCE_INT_FIELD_DOUJIAN_FIRST_REWARD,id)
end

--���ö���̨��ʤ
function AppInstanceMgr:setDoujianCombatWin(tf)
	if tf then
		self:AddUInt16(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN,1,1)
		local cur = self:GetUInt16(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN,1)
		if self:GetUInt16(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN,0) < cur then
			self:SetUInt16(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN,0,cur)
		end
	else
		self:SetUInt16(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN,1,0)
	end
end
--��ȡ����̨��ʤ
function AppInstanceMgr:getDoujianCombatWin()
	return self:GetUInt16(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN,0)
end

-- ��ȡ��ǰ��ʤ
function AppInstanceMgr:getDoujianCurrCombatWin()
	return self:GetUInt16(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN,1)
end

--����̨��ʤ������ȡ״̬
function AppInstanceMgr:getDoujianCombatWinReward(id)
	return self:GetBit(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN_REWARD,id)
end
--��ȡ����̨��ʤ������ȡ״̬
function AppInstanceMgr:setDoujianCombatWinReward(id)
	self:SetBit(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN_REWARD,id)
end
--����̨ÿ������
function AppInstanceMgr:dayDoujianReset()
	self:SetUInt32(INSTANCE_INT_FIELD_DOUJIAN_TIMES,0)
	self:SetUInt32(INSTANCE_INT_FIELD_DOUJIAN_FIGHT_CD,0)
	self:SetUInt32(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN,0)
	self:SetUInt32(INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN_REWARD,0)
end
-------------------------------����̨end------------------------------


-----------------------------------�ɸ��ᱦ----------------------------
--����ÿ�����ս����
function AppInstanceMgr:ResetXianfuDayTimes()
	self:SetXianfuDayTimes(0)
end

-- ������ս����
function AppInstanceMgr:SetXianfuDayTimes(val)
	return self:SetUInt32(INSTANCE_INT_FIELD_XIANFU_DAY_TIMES, val)
end

-- �����ս�����Ƿ��㹻
function AppInstanceMgr:CheckXianfuDayTimes()
	local target = tb_kuafu_xianfu_base[ 1 ].dailytimes
	local used = self:GetUInt32(INSTANCE_INT_FIELD_XIANFU_DAY_TIMES)
	return used < target
end

-- ������ɵ���ս����
function AppInstanceMgr:AddXianfuDayTimes()
	self:AddUInt32(INSTANCE_INT_FIELD_XIANFU_DAY_TIMES, 1)
end

-----------------------------------------------------------------------


---------------------------------����̨--------------------------------

--- ����̨��ս��¼
function AppInstanceMgr:AddDoujiantaiRecord(record)
	local cursor = self:GetUInt32(INSTANCE_INT_FIELD_DOUJIANTAI_CURSOR)
	self:SetStr(cursor + INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_START, record)
	cursor = cursor + 1
	if cursor >= MAX_DOUJIANTAI_RECORD_COUNT then
		cursor = 0
	end
	self:SetUInt32(INSTANCE_INT_FIELD_DOUJIANTAI_CURSOR, cursor)
end

-- ���ε����Ժ������������
function AppInstanceMgr:RefreshEnemysAfterRankChanged()
	local playerInfo = self:getOwner()
	local ranges = self:GetCurrRanges()
	local myrank = playerInfo:GetDoujiantaiRank()
	
	if myrank == 0 then
		myrank = MAX_DOUJIANTAI_RANK_COUNT + 1
	end
	
	local exists = {}
	for i = INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S, INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E-1 do
		local rank = self:GetUInt32(i)
		--print("RefreshEnemysAfterRankChanged", i, rank)
		if rank > 0 then
			local vist = false
			-- �ж��Ƿ������������
			for j = 1, #ranges do
				local range = ranges[ j ]
				local l = myrank - range[ 2 ]
				local r = myrank - range[ 1 ]
				if l <= rank and rank <= r then
					exists[ j ] = 1
					vist = true
					break
				end
			end
			
			if not vist then
				self:SetUInt32(i, 0)
			end
		end
	end

	--print("RefreshEnemysAfterRankChanged*************************")
	-- ���յ����
	for j = 1, #ranges do
		if not exists[ j ] then
			local range = ranges[ j ]
			local l = myrank - range[ 2 ]
			local r = myrank - range[ 1 ]
			local rank = randInt(l, r)
			
			local emptyIndx = self:GetEmptyIndx()
			if rank > 0 and emptyIndx >= 0 then
				self:SetUInt32(emptyIndx, rank)
			end
		end
	end
end

function AppInstanceMgr:GetEmptyIndx()
	for i = INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S, INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E-1 do
		local rank = self:GetUInt32(i)
		if rank == 0 then
			return i
		end
	end
	
	return -1
end

function AppInstanceMgr:GetEnemyRank(indx)
	return self:GetUInt32(INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S + indx)
end

function AppInstanceMgr:GetEnemyRankList()
	local dict = {}
	for i = INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S, INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E-1 do
		local rank = self:GetUInt32(i)
		if rank > 0 then
			table.insert(dict, rank)
		end
	end
	
	return dict
end

function AppInstanceMgr:GetCurrRanges()
	local playerInfo = self:getOwner()
	local rank = playerInfo:GetDoujiantaiRank()
	local indx = #tb_doujiantai_fight_range
	
	for i = 1, #tb_doujiantai_fight_range do
		local config = tb_doujiantai_fight_range[i]
		if config.ra <= rank and rank <= config.rb then
			indx = i
			break
		end
	end
	
	return tb_doujiantai_fight_range[indx].chooseRange
end


-- ����������rank��, �Ժ�����Ҫ���
function AppInstanceMgr:OnbeatRank(rank)
	for i = INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S, INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E-1 do
		--print("OnbeatRank ", i, self:GetUInt32(i), rank)
		if self:GetUInt32(i) == rank then
			self:SetUInt32(i, 0)
		end
	end
	--print("RefreshEnemysAfterRankChanged")
	self:RefreshEnemysAfterRankChanged()
end

-- ÿ��ѡ�����
function AppInstanceMgr:RefreshEnemy()
	local ranges = self:GetCurrRanges()
	local dict = {}
	-- INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY1
	for _, range in pairs(ranges) do
		local rank = self:RandomEnemy(range)
		if rank > 0 then
			table.insert(dict, rank)
		end
	end
	
	
	for i = INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S, INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E-1 do
		self:SetUInt32(i, 0)
	end
	
	for i = 1, #dict do
		self:SetUInt32(INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S+i-1, dict[ i ])
	end
end

-- ������ѡ�����
-- 0: ��ʾ�Ҳ�����
function AppInstanceMgr:RandomEnemy(range)
	local playerInfo = self:getOwner()
	local rank = playerInfo:GetDoujiantaiRank()
	if rank == 0 then
		rank = MAX_DOUJIANTAI_RANK_COUNT + 1
	end
	
	local l = rank - range[ 2 ]
	local r = rank - range[ 1 ]
		
	return randInt(l, r)
end


function AppInstanceMgr:checkIfCanEnterMassBoss(id)
	local config = tb_mass_boss_info[ id ]
	local player = self:getOwner()
	
	-- �жϵȼ��Ƿ��㹻
	if player:GetLevel() < config.permitLevel then
		outFmtError("no level to enter id = %s", id)
		return
	end
	
	-- �����Ƿ��㹻
	if not player:costMassBossTimes() then
		return
	end

	local x 	= config.enterPos[ 1 ]
	local y 	= config.enterPos[ 2 ]
	local mapid = config.mapId
	
	-- ������
	call_appd_teleport(player:GetScenedFD(), player:GetGuid(), x, y, mapid, ''..id)
	
	player:AddActiveItem(VITALITY_TYPE_MASS_BOSS)
end

--��Ӹ���
--[[
--����ͨ��״̬
function AppInstanceMgr:SetGroupInstanceClearFlag(val)
	self:SetBit(INSTANCE_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG,val)
end

--���ͨ��״̬
function AppInstanceMgr:GetGroupInstanceClearFlag(val)
	return self:GetBit(INSTANCE_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG,val)
end
--]]
--������ս����
function AppInstanceMgr:SetGroupInstanceChallengeCount(val)
	self:SetUInt32(INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT,val)
end

--�����ս����
function AppInstanceMgr:GetGroupInstanceChallengeCount()
	return self:GetUInt32(INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT)
end

--������ս����
function AppInstanceMgr:AddGroupInstanceChallengeCount(val)
	self:AddUInt32(INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT,val)
end

--������ս����
function AppInstanceMgr:SubGroupInstanceChallengeCount(val)
	if self:GetGroupInstanceChallengeCount() - val > 0 then
		self:SubUInt32(INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT,val)
	else
		self:SetGroupInstanceChallengeCount(0)
	end
end

--���ù������
function AppInstanceMgr:SetGroupInstanceBuyCount(val)
	self:SetUInt32(INSTANCE_INT_FIELD_GROUP_INSTANCE_BUY_COUNT,val)
end

--��ù������
function AppInstanceMgr:GetGroupInstanceBuyCount()
	return self:GetUInt32(INSTANCE_INT_FIELD_GROUP_INSTANCE_BUY_COUNT)
end

--���ӹ������
function AppInstanceMgr:AddGroupInstanceBuyCount(val)
	self:AddUInt32(INSTANCE_INT_FIELD_GROUP_INSTANCE_BUY_COUNT,val)
end

function AppInstanceMgr:ResetGroupInstanceDayTimes()
	self:SetGroupInstanceBuyCount(0)
	self:SetGroupInstanceChallengeCount(tb_group_instance_buy[1].daily_reset)
end

--------------------------------------��λ��-----------------------------------------

-- ���ʤ������
function AppInstanceMgr:GetQualifyWins()
	return self:GetUInt32(INSTANCE_INT_FIELD_QUALIFY_WINS)
end

-- ����ʤ������
function AppInstanceMgr:AddQualifyWins(val)
	self:AddUInt32(INSTANCE_INT_FIELD_QUALIFY_WINS, val)
end

-- ����ʤ������
function AppInstanceMgr:ResetQualifyWins()
	self:SetUInt32(INSTANCE_INT_FIELD_QUALIFY_WINS, 0)
end

-- ��ù������
function AppInstanceMgr:GetQualifyBuyCount()
	return self:GetUInt32(INSTANCE_INT_FIELD_QUALIFY_BUY_TIMES)
end

-- ���ӹ������
function AppInstanceMgr:AddQualifyBuyCount(val)
	self:AddUInt32(INSTANCE_INT_FIELD_QUALIFY_BUY_TIMES, val)
end

-- ���ù������
function AppInstanceMgr:ResetQualifyBuyCount()
	self:SetUInt32(INSTANCE_INT_FIELD_QUALIFY_BUY_TIMES, 0)
end

-- ���ÿ�����
function AppInstanceMgr:GetQualifyDailyTimes()
	return self:GetUInt32(INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES)
end

-- ����ÿ�����
function AppInstanceMgr:AddQualifyDailyTimes(val)
	self:AddUInt32(INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES, val)
end

-- ����ÿ�����
function AppInstanceMgr:SubQualifyDailyTimes()
	if self:GetQualifyDailyTimes() > 0 then
		self:SubUInt32(INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES, 1)
	end
end

-- ����ÿ�����
function AppInstanceMgr:ResetQualifyDailyTimes()
	local val = tb_single_pvp_base[ 1 ].dailyTimes
	self:SetUInt32(INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES, val)
end

-- ��ö��⽱����־
function AppInstanceMgr:IsQualifyExtraObtain(id)
	return self:GetBit(INSTANCE_INT_FIELD_QUALIFY_EXTRA, id)
end

-- ���ö��⽱����־
function AppInstanceMgr:SetQualifyExtraObtain(id)
	self:SetBit(INSTANCE_INT_FIELD_QUALIFY_EXTRA, id)
end

-- ���ö��⽱����־
function AppInstanceMgr:ResetQualifyExtra()
	self:SetUInt32(INSTANCE_INT_FIELD_QUALIFY_EXTRA, 0)
end

-- ��ö��⽱����ȡ��־
function AppInstanceMgr:IsQualifyExtraPicked(id)
	return self:GetBit(INSTANCE_INT_FIELD_QUALIFY_EXTRA_PICKED, id)
end

-- ���ö��⽱����ȡ��־
function AppInstanceMgr:SetQualifyExtraPicked(id)
	self:SetBit(INSTANCE_INT_FIELD_QUALIFY_EXTRA_PICKED, id)
end

-- ���ö��⽱����ȡ��־
function AppInstanceMgr:ResetQualifyExtraPicked()
	self:SetUInt32(INSTANCE_INT_FIELD_QUALIFY_EXTRA_PICKED, 0)
end


--- ��λ����ս��¼
function AppInstanceMgr:AddQaulifyRecord(record)
	local cursor = self:GetUInt32(INSTANCE_INT_FIELD_QUALIFY_CURSOR)
	self:SetStr(cursor + INSTANCE_STR_FIELD_QUALIFY_RECORD_START, record)
	cursor = cursor + 1
	if cursor >= MAX_QUALIFY_RECORD_COUNT then
		cursor = 0
	end
	self:SetUInt32(INSTANCE_INT_FIELD_QUALIFY_CURSOR, cursor)
end

function AppInstanceMgr:ResetQualifyDaily()
	self:ResetQualifyDailyTimes()
	self:ResetQualifyBuyCount()
	self:ResetQualifyExtra()
	self:ResetQualifyExtraPicked()
	self:ResetQualifyWins()
end

-------------------------------------------------------------------------------



-- ������guid
function AppInstanceMgr:getPlayerGuid()
	--��Ʒ������guidת���guid
	if not self.owner_guid then
		self.owner_guid = guidMgr.replace(self:GetGuid(), guidMgr.ObjectTypePlayer)
	end
	return self.owner_guid
end

--��ø�����������ӵ����
function AppInstanceMgr:getOwner()
	local playerguid = self:getPlayerGuid()
	return app.objMgr:getObj(playerguid)
end

return AppInstanceMgr