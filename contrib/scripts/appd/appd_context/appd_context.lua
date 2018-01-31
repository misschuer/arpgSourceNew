----------------------------------------------------------------------------------------------------------------------------------------------
--玩家封装
PlayerInfo = class('PlayerInfo', BinLogObject)
local security = require("base/Security")

local guidMgr = require 'share.guid_manager'

local SPLIT_THINGS = "\1"	--分割多条物品
local SPLIT_THING_DETAIL = "\2"	--分割物品详细信息

--将所有的发包及解包功能附加到该类
require('share.protocols'):extend(PlayerInfo)

--构造函数
function PlayerInfo:ctor( offlineObjects )
	--如果是离线数据,则使用这东西，会把所有机关数据引用到这个地方
	self.offlineObjects = offlineObjects
end

--获得会话id
function PlayerInfo:GetSessionId()
	return playerLib.GetFD(self.ptr)
end

--最重要的操作结果
function PlayerInfo:CallOptResult( typed, reason, data )
	--碰上字符串数组自动拼接	
	if type(data) == 'table' then
		data = string.join('|', data)
	else
		data = tostring(data) or ''
	end
	self:call_operation_failed(typed, reason, data)
end

--获得玩家所在的场景fd
function PlayerInfo:GetScenedFD()
	return self:GetUInt32(PLAYER_FIELD_FD)
end

-- 获得屏蔽人员个数
function PlayerInfo:GetBlockCounts()
	return self:GetUInt32(PLAYER_INT_FIELD_BLOCK_COUNT)
end

-- 增加屏蔽人员个数
function PlayerInfo:AddBlockCounts()
	return self:AddUInt32(PLAYER_INT_FIELD_BLOCK_COUNT, 1)
end

-- 减少屏蔽人员个数
function PlayerInfo:SubBlockCounts()
	return self:SubUInt32(PLAYER_INT_FIELD_BLOCK_COUNT, 1)
end

-- 设置屏蔽列表的str
function PlayerInfo:SetBlockGuids(val)
	self:SetStr(PLAYER_STRING_FIELD_BLOCK_GUIDS, val)
end

-- 是否有坐骑
function PlayerInfo:IsMountActived()
	local level = self:GetByte(PLAYER_INT_FIELD_MOUNT_LEVEL, 0)
	return level > 0
end

function PlayerInfo:SetMountLevel(level)
	self:SetByte(PLAYER_INT_FIELD_MOUNT_LEVEL, 0, level)
end

function PlayerInfo:SetMountStar(star)
	self:SetByte(PLAYER_INT_FIELD_MOUNT_LEVEL, 1, star)
end

--[[
rewardDict :  {{itemId, count},{itemId1, count1}}
--]]
function PlayerInfo:AppdAddItems(rewardDict, money_oper_type, item_oper_type, times, deadline, showType, bagFullCategory, isNotice)
	times = times or 1
	deadline = deadline or 0
	showType = showType or 0
	if isNotice == nil then
		isNotice = true
	end
	
	-- 获得信息
	if isNotice then
		local dict = changeTableStruct(rewardDict)
		local list = Change_To_Item_Reward_Info(dict)
		self:call_item_notice (showType, list)
	end
	self:PlayerAddItems(rewardDict, money_oper_type, item_oper_type, times, deadline, bagFullCategory)

end

--[[
有可能场景服发来的增加道具的接口也是这个
rewardDict :  {{itemId, count},{itemId1, count1}}
@param : bagFullCategory 0:满了存邮件, 1:满了丢弃, 2: 满了提示背包已满 (外面必须判断是否可以放下, 处理过程和1一样),3:满了自动出售
--]]
function PlayerInfo:PlayerAddItems(rewardDict, money_oper_type, item_oper_type, times, deadline, bagFullCategory)
	times = times or 1
	money_oper_type = money_oper_type or MONEY_CHANGE_SELECT_LOOT
	item_oper_type  = item_oper_type  or LOG_ITEM_OPER_TYPE_LOOT
	deadline	= deadline or 0
	bagFullCategory = bagFullCategory or 0
	
	local itemDict = {}
	-- 先把资源和经验加了, 放背包的道具第二步算
	for _, itemInfo in pairs(rewardDict) do
		
		local itemId = itemInfo[ 1 ]
		local count  = itemInfo[ 2 ] * times
		if IsResource(itemId) then
			-- 加人物资源
			local moneyType = GetMoneyType(itemId)
			self:AddMoney(moneyType, money_oper_type, count)
		elseif itemId == Item_Loot_Exp then
			-- 应用服加个临时经验
			self:AddAppdExp(count)
			-- 加经验 发送到场景服
			-- self:CallScenedDoSomething(APPD_SCENED_ADD_EXP, count)
		elseif itemId == Item_Loot_Realmbreak_Exp then
			self:AddRealmbreakExp(count)
		else
			if tb_item_template[itemId] then
				table.insert(itemDict, {itemId, count})
			end
		end
	end

	-- 加道具的时候判断是否背包满了
	if #itemDict > 0 then
		-- 贡献道具个数
		local questMgr = self:getQuestMgr()
		for i = 1, #itemDict do
			local entry = itemDict[ i ][ 1 ]
			local count = itemDict[ i ][ 2 ]
			questMgr:OnUpdate(QUEST_TARGET_TYPE_LOOT_ITEM, {entry, count})
		end
		
		local indx = -1
		local itemMgr = self:getItemMgr()
		-- 放得下的先放
		for i = 1, #itemDict do
			local entry = itemDict[ i ][ 1 ]
			local count = itemDict[ i ][ 2 ]
			local bagType = tb_item_template[entry].belong_bag
			
			-- 如果配错了直接返回
			if bagType == -1 then
				return
			end
			-- 判断背包是否放的下
			if not itemMgr:canHold(bagType, entry, count, 1, 0) then
				indx = i
				break
			end
			local bind = tb_item_template[entry].bind_type
			--AddItemByEntry(entry, count, money_log, item_log, item_bind, isAppaisal, isSystem, strong_lv, fail_time, bag_type, pos)
			self:AddItemByEntry(entry, count, nil, item_oper_type, bind, true, true, 0, deadline, bagType)
		end
		
		-- 放不下的存邮件
		if bagFullCategory == 0 and indx > 0 then
			local mailItem = {}
			for i = indx, #itemDict do
				table.insert(mailItem, itemDict[ i ][ 1 ])
				table.insert(mailItem, itemDict[ i ][ 2 ])
			end
			
			local itemConfig = string.join(",", mailItem)
			local data = GetMailEntryId(GIFT_PACKS_TYPE_BAG_FULL, 0)
			local desc = tb_mail[data].desc
			local name = tb_mail[data].name
			local giftType = tb_mail[data].source
			AddGiftPacksData(self:GetGuid(),0,giftType,os.time(),os.time() + 86400*30, name, desc, itemConfig, SYSTEM_NAME)
			self:CallOptResult(OPRATE_TYPE_BAG,BAG_RESULT_BAG_FULL_SEND_MAIL)
		end
		
		-- 出售
		if bagFullCategory == 3 and indx > 0 then
			local selled = {}
			for i = indx, #itemDict do
				local entry = itemDict[ i ][ 1 ]
				local count = itemDict[ i ][ 2 ]
				local sellReward = tb_item_template[entry].sell_reward
				for _, rewardInfo in ipairs(sellReward) do
					if not selled[rewardInfo[ 1 ]] then
						selled[rewardInfo[ 1 ]] = 0
					end
					selled[rewardInfo[ 1 ]] = selled[rewardInfo[ 1 ]] + rewardInfo[ 2 ] * count
				end
			end
			
			local sellRewardDict = {}
			for entry, count in pairs(selled) do
				table.insert(sellRewardDict, {entry, count})
			end
			
			if #sellRewardDict > 0 then
				self:AppdAddItems(sellRewardDict, MONEY_CHANGE_NPC_SELL, nil, nil, nil, nil, 1)
			end
		end
	end
end

-- 骑乘状态
function PlayerInfo:rideFlag()
	return self:GetUInt32(PLAYER_INT_FIELD_MOUNT_RIDE)
end

-- 设置骑乘状态
function PlayerInfo:SetRideState(val)
	self:SetUInt32(PLAYER_INT_FIELD_MOUNT_RIDE, val)
	--[[
	local spellMgr = self:getSpellMgr()
	local speed = GetPlayerSpeed(self:GetLevel(), spellMgr:getMountLevel(), self:GetCurrIllusionId(), self:isRide(), self:GetGender())
	self:SetMoveSpeed(speed)
	--]]
end

-- 幻化id
function PlayerInfo:GetCurrIllusionId()
	return self:GetByte(PLAYER_INT_FIELD_MOUNT_LEVEL, 3)
end

-- 设置幻化id
function PlayerInfo:SetCurrIllusionId(illuId)
	self:SetByte(PLAYER_INT_FIELD_MOUNT_LEVEL, 3, illuId)
end

-- 是否骑乘
function PlayerInfo:isRide()
	return self:IsMountActived() and self:rideFlag() > 0
end

-- 设置VIP等级
function PlayerInfo:SetVIP(vipLevel, time)
	
	if vipLevel > VIP_MAX_LEVEL then
		return
	end
	
	local prevVIP = self:GetVIP()
	if vipLevel > prevVIP then
		self:OnVipRaised(prevVIP,vipLevel)
		
		self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_VIP_LEVEL, {vipLevel})
	end
	self:SetUInt32(PLAYER_FIELD_VIP_LEVEL, vipLevel)
	self:SetUInt32(PLAYER_FIELD_VIP_TIME_OUT, time)
	self:UpdateFactionBangZhuInfo()
	self:UpdateBagSize(vipLevel)
end

-- 是否达到该vip等级
function PlayerInfo:isVIP(vipLevel)
	return self:GetUInt32(PLAYER_FIELD_VIP_LEVEL) >= vipLevel and self:GetUInt32(PLAYER_FIELD_VIP_TIME_OUT) >= os.time()
end

-- 获得vip等级
function PlayerInfo:GetVIP()
	local vipLevel = self:GetUInt32(PLAYER_FIELD_VIP_LEVEL)
	local time = self:GetUInt32(PLAYER_FIELD_VIP_TIME_OUT)
	if time < os.time() and time > 0 then
		vipLevel = 0
	end
	return vipLevel
end

--vip 提升时 补充增加的次数
function PlayerInfo:OnVipRaised(prev,now)
	local prev_config = tb_vip_base[prev]
	local now_config = tb_vip_base[now]
	
	local added = now_config.massbossExtraTimes - prev_config.massbossExtraTimes
	if added > 0 then
		self:AddUInt32(PLAYER_INT_FIELD_MASS_BOSS_TIMES, added)
		self:CallScenedDoSomething(APPD_SCENED_RESETDAILY, 0)
	end
end

-- 玩家是否还活着
function PlayerInfo:IsAlive ()
	return self:GetUInt32(PLAYER_FIELD_DEATH_STATE) == DEATH_STATE_ALIVE
end
	
--获得玩家主下标的flag标志
function PlayerInfo:GetPlayerFlags (index)
	return self:GetBit(PLAYER_FIELD_FLAGS, index)
end

--设置玩家主下标的flag标志
function PlayerInfo:SetPlayerFlags ( index)
	self:SetBit(PLAYER_FIELD_FLAGS, index)
end

-- 获得帮派guid
function PlayerInfo:GetFactionId ()
	return self:GetStr(PLAYER_STRING_FIELD_FACTION_GUID)
end

--设置帮派guid
function PlayerInfo:SetFactionId (factionId)
	self:SetStr(PLAYER_STRING_FIELD_FACTION_GUID, factionId)
end

-- 获得帮派名字
function PlayerInfo:GetFactionName ()
	return self:GetStr(PLAYER_STRING_FIELD_FACTION_NAME)
end

--设置帮派名字
function PlayerInfo:SetFactionName (name)
	self:SetStr(PLAYER_STRING_FIELD_FACTION_NAME, name)
end



--设置玩家主下标的flag标志
function PlayerInfo:UnSetPlayerFlags (index)
	self:UnSetBit(PLAYER_FIELD_FLAGS, index)
end

--把某玩家标志位变成1
function PlayerInfo:SetFlags ( index)
	self:SetBit(PLAYER_APPD_INT_FIELD_FLAG, index)
end

--把某玩家标志位变成0
function PlayerInfo:UnSetFlags ( index)
	self:UnSetBit(PLAYER_APPD_INT_FIELD_FLAG, index)
end

--获取某玩家标志位
function PlayerInfo:GetFlags ( index)
	return self:GetBit(PLAYER_APPD_INT_FIELD_FLAG, index)
end

--设置显示用装备的模板下标
function PlayerInfo:SetEquipment ( pos, val)
	if(self:GetEquipment(pos) ~= val)then
		self:SetUInt32(PLAYER_FIELD_EQUIPMENT + pos, val)
	end
end

--获得显示用装备的模板下标
function PlayerInfo:GetEquipment ( pos)
	return self:GetUInt32(PLAYER_FIELD_EQUIPMENT + pos)
end

--获取MaxHp
function PlayerInfo:GetMaxHp ()
	return self:GetDouble(PLAYER_FIELD_MAX_HEALTH)
end


function PlayerInfo:GetMoveSpd ()
	return self:GetDouble(PLAYER_FIELD_MOVESPEED)
end

--获取Hp
function PlayerInfo:GetHp ()
	return self:GetDouble(PLAYER_FIELD_HEALTH)
end

--获取MapId
function PlayerInfo:GetMapId ()
	return self:GetUInt32(PLAYER_FIELD_MAP_ID)
end

--获取Position
function PlayerInfo:GetPosition ()
	return self:GetFloat(PLAYER_FIELD_POS_X), self:GetFloat(PLAYER_FIELD_POS_Y)
end

--获取性别
function PlayerInfo:GetGender ()
	return self:GetByte(PLAYER_FIELD_BYTES_0, 0)
end

--获得在线时长
function PlayerInfo:GetOnlineTime ()
	return self:GetUInt32(PLAYER_FIELD_ONLINE_TIME)
end

--设置在线时长
function PlayerInfo:SetOnlineTime ( val)
	self:SetUInt32(PLAYER_FIELD_ONLINE_TIME, val)
end

--获取阵营
function PlayerInfo:GetFaction ()
	return self:GetByte(PLAYER_FIELD_BYTES_0, 1)
end

function PlayerInfo:GetRace ()
	return self:GetByte(PLAYER_FIELD_BYTES_0,2)
end

--获取头像
function PlayerInfo:GetHead ()
	return self:GetByte(PLAYER_FIELD_BYTES_3, 0)
end

--获得头发
function PlayerInfo:GetHair ()
	return self:GetByte(PLAYER_FIELD_BYTES_3,1)
end

--获取攻击模式
function PlayerInfo:GetAttackMode ()
	return self:GetByte(PLAYER_FIELD_BYTES_3, 3)
end

--获得pvp状态
function PlayerInfo:GetPVPState ()
	return self:GetBit(PLAYER_SCENED_INT_FLAGS, PLAYER_SCENED_FLAS_PVP_STATE)
end

--获取是否挂机
function PlayerInfo:GetHungUp ()
	return self:GetBit(PLAYER_SCENED_INT_FLAGS, PLAYER_SCENED_FLAS_HUNG_UP)
end

--获取等级
function PlayerInfo:GetLevel ()
	return self:GetUInt32(PLAYER_FIELD_LEVEL)
end

--设置等级
function PlayerInfo:SetLevel (value)
	self:SetUInt32(PLAYER_FIELD_LEVEL, value)
end

--获取经验
function PlayerInfo:GetExp ()
	return self:GetDouble(PLAYER_EXPAND_INT_XP)
end

--获取战斗力
function PlayerInfo:GetForce ()
	return self:GetDouble(PLAYER_FIELD_FORCE)
end

--获取付费等级
function PlayerInfo:GetPayLevel ()
	return self:GetByte(PLAYER_FIELD_BYTES_2, 1)
end

--设置付费等级
function PlayerInfo:SetPayLevel (val)
	return self:SetByte(PLAYER_FIELD_BYTES_2, 1, val)
end

--获取免费复活次数
function PlayerInfo:GetFreeReliveCount ()
	return self:GetByte(PLAYER_FIELD_BYTES_2, 2)
end

--设置免费复活次数
function PlayerInfo:SetFreeReliveCount (val)
	return self:SetByte(PLAYER_FIELD_BYTES_2, 2, val)
end

--获取称号
function PlayerInfo:GetTitle ()
	return self:GetByte(PLAYER_FIELD_BYTES_2, 3)
end

--获取平台信息
function PlayerInfo:GetPingTaiInfo ()
	return self:GetStr(PLAYER_APPD_STRING_FIELD_PINGTAI_INFO)
end

-- 判断钱是否足够
function PlayerInfo:checkMoneyEnough(moneyType, cost)
	local value = self:GetMoney(moneyType)
	return value >= cost and cost >= 0
end
--获取玩家身上的money
function PlayerInfo:GetMoney(type)
	if(type < MAX_MONEY_TYPE)then
		return self:GetDouble(PLAYER_EXPAND_INT_MONEY + type*2)
	end
	return 0
end

--重置玩家身上的money
function PlayerInfo:ResetMoney(type)
	if(type < MAX_MONEY_TYPE)then
		self:SetDouble(PLAYER_EXPAND_INT_MONEY + type*2, 0)
	end
end

-- 判断钱是否足够
function PlayerInfo:checkMoneyEnoughs(costTable, times)
	times = times or 1
	
	local bool, _ = self:checkMoneyEnoughIfUseGoldIngot(costTable, times)
	return bool
end


-- 判断钱是否足够(绑定元宝不够用元宝)
-- 返回
-- true, costTable
-- false, nil
function PlayerInfo:checkMoneyEnoughIfUseGoldIngot(costTable, times)
	times = times or 1
	
	-- 判断重复
	local reps = {} 	
	for _, res in pairs(costTable) do
		if reps[res[ 1 ]] ~= nil then
			outFmtError("designer has type invalid data")
			return false, nil
		end
		reps[res[ 1 ]] = 1
	end
	
	
	-- 先把不能扣的绑定元宝转成元宝
	local cost2 = {}
	-- 检测是否可扣
	for _, res in pairs(costTable) do
		-- 不能有负的
		if res[ 2 ] < 0 then
			return false, nil
		end
		if not self:checkMoneyEnough(res[ 1 ], res[ 2 ] * times) then
			if res[ 1 ] ~= MONEY_TYPE_BIND_GOLD then
				return false, nil
			end
			local prev = self:GetMoney(res[ 1 ])
			local need = res[ 2 ] * times - prev
			-- 加元宝的
			AddTempInfoIfExist(cost2, MONEY_TYPE_GOLD_INGOT, need)
			-- 加绑定元宝
			if prev > 0 then
				AddTempInfoIfExist(cost2, MONEY_TYPE_BIND_GOLD , prev)
			end
		else
			AddTempInfoIfExist(cost2, res[ 1 ], res[ 2 ] * times)
		end
	end
	
	
	-- 检测是否可扣
	for _, res in pairs(cost2) do
		if not self:checkMoneyEnough(res[ 1 ], res[ 2 ]) then
			return false, nil
		end
	end
	
	return true, cost2
end


-- 扣除钱
function PlayerInfo:costMoneys(oper_type, costTable, times, relateItemIds, relateItemNums)
	times = times or 1
	relateItemIds = relateItemIds or ''
	relateItemNums = relateItemNums or ''
	if times < 1 then
		return false
	end
	
	local bool, realCostTable = self:checkMoneyEnoughIfUseGoldIngot(costTable, times)
	if bool then
		-- 实际扣除
		for _, res in pairs(realCostTable) do
			self:SubMoney(res[ 1 ], oper_type, res[ 2 ], relateItemIds, relateItemNums)
		end
	end
	
	return bool
end

--获取金钱数量
function PlayerInfo:GetMoney ( money_type)
	return playerLib.GetMoney(self.ptr,money_type)
end

--金钱减少
function PlayerInfo:SubMoney ( money_type, oper_type, val, relateItemIds, relateItemNums)
	if(val <= 0)then
		return false
	end
	val = -1 * val
	relateItemIds = relateItemIds or ''
	relateItemNums = relateItemNums or ''
	
	return playerLib.ModifyMoney(self.ptr, money_type, oper_type, val, relateItemIds, relateItemNums)
end

--金钱增加
function PlayerInfo:AddMoney ( money_type, oper_type, val, relateItemIds, relateItemNums)
	if(val <= 0)then
		return false
	end
	
	relateItemIds = relateItemIds or ''
	relateItemNums = relateItemNums or ''
	
	return playerLib.ModifyMoney(self.ptr, money_type, oper_type, val, relateItemIds, relateItemNums)
end

--获取元宝和绑元数量
function PlayerInfo:GetGoldMoney ()
	return self:GetMoney(MONEY_TYPE_GOLD_INGOT) + self:GetMoney(MONEY_TYPE_BIND_GOLD)
end

--[[--消耗元宝和绑元
function PlayerInfo:SubGoldMoney (log_type,val)
	if(self:GetMoney(MONEY_TYPE_BIND_GOLD) >= val)then
		return self:SubMoney(MONEY_TYPE_BIND_GOLD,log_type,val)
	else
		local money = val - self:GetMoney(MONEY_TYPE_BIND_GOLD)
		if(self:GetMoney(MONEY_TYPE_BIND_GOLD) > 0 and self:SubMoney(MONEY_TYPE_BIND_GOLD,log_type,self:GetMoney(MONEY_TYPE_BIND_GOLD)) == false)then
			return false
		end
		return self:SubMoney(MONEY_TYPE_GOLD_INGOT,log_type,money)
	end
	return false
end--]]

--玩家消费行为
function PlayerInfo:OnConsumption(money_type,val)
	local limit_acti = self:getLimitActivityInfo()
	if limit_acti then
		return limit_acti:OnConsumption(self, money_type, val)
	end
end

-- 处理消费元宝统计
function PlayerInfo:DoGlodConsumeStatistics ( val)
	
-- 累计消费
--	local cur_tm = os.time()
--	if cur_tm <= DoHowLongKaiFuTime(7) then
	local count = self:GetConsumeSum()
	count = count + val
	if count > MAX_UINT32_NUM then
		count = MAX_UINT32_NUM
	end
	self:SetConsumeSum(count)
	
	outFmtDebug("DoGlodConsumeStatistics  cur %d", self:GetConsumeSum())
--	end
end

--获得角色创建时间
function PlayerInfo:GetCharCreateTime ()
	return self:GetUInt32(PLAYER_EXPAND_INT_CREATE_TIME)
end

--返回在线时长
function PlayerInfo:GetDailyOnlineTime ()
	return self:GetUInt32(PLAYER_APPD_INT_FIELD_DAILY_TIME)
end

--设置在线时长
function PlayerInfo:SetDailyOnlineTime ( val)
	self:SetUInt32(PLAYER_APPD_INT_FIELD_DAILY_TIME, val)
end

-- 获得系统邮件的序号
function PlayerInfo:GetSystemMailSeq()
	return self:GetUInt32(PLAYER_INT_FIELD_SYSTEM_MAIL_ID)
end

-- 设置系统邮件的序号
function PlayerInfo:SetSystemMailSeq(val)
	return self:SetUInt32(PLAYER_INT_FIELD_SYSTEM_MAIL_ID, val)
end

--玩家登录做点什么,或者场景服启动做点什么？
function PlayerInfo:Login()
	local isPkServer = globalGameConfig:IsPKServer()
	if isPkServer then
		--战斗服登录
		self:LoginPk()
		return
	end
	
	--活动数据初始化
	DoActivityDataInitOnLogin(self)
	
	--0点重置	
	self:DoResetDaily()

	local current_time = os.time()

	--登入时重设装备下标
	self:UpdatePlayerEquipment()

	--是否新手玩家
	if(self:GetFlags(PLAYER_APPD_INT_FIELD_FLAGS_NEW_PLAYER) == false)then
		--置为老玩家
		self:SetFlags(PLAYER_APPD_INT_FIELD_FLAGS_NEW_PLAYER)
		
		--发送玩家属性到场景服
		playerLib.SendAttr(self.ptr)
	end
	
	self:socialLogIn()
	self:factionLogin()
	
	self:GetOfflineMail()
	globalSystemMail:checkIfHasSystemMail(self)
	
	--检查礼物离线更新
	--self:LoginUpdateGiftInfo()
	--同步魅力值
	--self:LoginUpdateCharmPoint()
	-- 检查奖励
	self:CheckMatchReward()	
	
	-- 同步斗剑台信息
	globalCounter:Login(self)
	
	--同步修炼信息
	-- self:LoginRestoreCultivation()
	
	--初始化登陆大礼
	self:InitLoginActivity()
	
	-- 把跨服的信息清空
	self:KuafuUnMarked()
	
	--初始化家族技能
	self:UpdateFactionSkill()
	
	-- 发送开服时间
	self:call_send_server_open_time(globalGameConfig:GetKaiFuShiJian())
	
	-- 
	local logoutTime = self:GetUInt32(PLAYER_EXPAND_INT_LAST_LOGOUT_TIME)
	if logoutTime > 0 then
		local times = math.floor((os.time() - logoutTime) / 60)
		self:onPickedOfflineRiskReward(times)
	end
	
	self:ResetLastInstanceInfo()
	
	local groupId = self:GetGroupId()
	if string.len(groupId) > 0 then
		local groupObj = app.objMgr:getObj(groupId)
		if not groupObj or not app.objMgr:IsGroupGuid(groupId) or not groupObj:groupOnline(self) then
			self:SetGroupId('')
		end
		
		-- 如果是正在匹配然后推掉的 下次进来清空记号
		if groupObj and groupObj:IsPlayerCaptain(self:GetGuid()) then
			groupObj:SetUInt32(GROUP_INT_FIELD_TARGET_INST, 0)
		end
	end
	
	-- 3v3参与奖励获得
	local timestamp = GetTodayStartTimestamp()
	if self:GetKuafu3v3Score() > 0 and (self:GetKuafu3v3TotalScore() ~= timestamp or not isLocal3V3Open(self)) then
		self:SetKuafu3v3Score(0)
		self:Get3v3JoinReward()
	end
	
	self:SetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH, 0)
	OnGroupMatchRemove(self:GetGuid())
	
	
	-- 检测充值信息
	app.http:RchhargeOnLogin(self)
	
	--重置每月签到
	
	self:CheckClearCheckInData()
	self:ResetActRankData()
	self:LoginUpdateModuleUnlock()
end

function PlayerInfo:Get3v3JoinReward()
	local config = tb_kuafu3v3_base[ 1 ]
	local desc = config.maildesc
	local name = config.mailname
	local reward = config.joinReward
	local giftType = 3
	AddGiftPacksData(self:GetGuid(),0,giftType,os.time(),os.time() + 86400*30, name, desc, reward, SYSTEM_NAME)
end

--pk服玩家登陆做点啥
function PlayerInfo:LoginPk()
end 

--玩家下线后
function PlayerInfo:Logout ()
	local isPkServer = globalGameConfig:IsPKServer()
	if isPkServer then
		return
	end
	
	--清空好友申请列表
	self:socialLogOut()
	self:factionLogOut()
	-- 取消跨服匹配
	self:OnCancelKuafuMatch()
	-- 同步斗剑台最新玩家数据
	globalCounter:SyncPlayerInfo(self)
	
	--备份修炼信息
	self:LogoutBackupCultivation()
	
	-- 如果有队伍 退出队伍
	local groupId = self:GetGroupId()
	if string.len(groupId) > 0 then
		local group = app.objMgr:getObj(groupId)
		if group then
			group:groupOffline(self)
		end
	end	
end

--有多少个物品
function PlayerInfo:CountItem (entry, bag_id, bind_type, fail_time)
	local itemMgr = self:getItemMgr()
	if(bag_id == nil)then
		bag_id = BAG_TYPE_MAIN_BAG
	end
	
	return itemMgr:countItem(bag_id, entry, bind_type, fail_time)	
end

--根据物品模板扣除物品
function PlayerInfo:SubItemByEntry( entry, count )
	local itemMgr = self:getItemMgr()
	return itemMgr:delItem(entry, count) ~= SUB_ITEM_FAIL
end
	
--所有包裹共有多少个物品
function PlayerInfo:CountAllItem(entry, bind_type)
	local itemMgr = self:getItemMgr()
	return itemMgr:countAllItem(entry, bind_type)
end


--获取充值总数
function PlayerInfo:GetRechageSum ()
	return self:GetUInt32(PLAYER_APPD_INT_FIELD_RECHARGE_SUM)
end

--消费总数
function PlayerInfo:GetConsumeSum ()
	return self:GetUInt32(PLAYER_APPD_INT_FIELD_CONSUME_SUM)
end

function PlayerInfo:SetConsumeSum (val)
	self:SetUInt32(PLAYER_APPD_INT_FIELD_CONSUME_SUM,val)
end

--获取最后充值ID
function PlayerInfo:GetRechageID ()
	return self:GetStr(PLAYER_STRING_FIELD_RECHARGE_ID)
end

--设置最后充值ID
function PlayerInfo:SetRechageID (val)
	self:SetStr(PLAYER_STRING_FIELD_RECHARGE_ID,val)
end

--获取最后一笔充值时间
function PlayerInfo:GetRechageLastTime ()
	return self:GetUInt32(PLAYER_APPD_INT_FIELD_LAST_RECHARGE_TIME)
end

--设置最后一笔充值时间
function PlayerInfo:SetRechageLastTime ( val)
	self:SetUInt32(PLAYER_APPD_INT_FIELD_LAST_RECHARGE_TIME, val)
end

--充值后
function PlayerInfo:DoAddRechargeSum (recharge_id,rmbval,recharge_time, callback)
	if  rmbval == 0 then
		return
	end
	if(self:GetRechageLastTime() <= recharge_time and self:GetRechageID() ~= recharge_id)then
		self:AddUInt32(PLAYER_APPD_INT_FIELD_RECHARGE_SUM,rmbval)
		
		--首充
		local isFirst = self:WelfareShouchong()
		if isFirst and callback then
			callback()
		end
		--7日充值
		self:WelfareSevenDayRecharge(recharge_time)
		
		
		self:SetRechageLastTime(recharge_time)
		self:SetRechageID(recharge_id)
		--self:AddUInt32(PLAYER_HT_INT_FIELD_RECHARGE_COUNT,1)

		--限时活动充值
		local limit_acti = self:getLimitActivityInfo()
		if limit_acti then
			limit_acti:OnRecharge(self, rmbval, recharge_id, recharge_time)
		end

		--设置下付费等级
		local pay_table = {0,5000,20000,50000,100000,200000,500000,800000,1000000,1500000,2000000}
		local rechage = self:GetRechageSum()
		local pay_level = #pay_table - 1
		for i = 1,#pay_table do
			if(rechage < pay_table[i])then
				pay_level = i - 2
				break
			end
		end
		if(pay_level ~= self:GetPayLevel())then
			self:SetPayLevel(pay_level)
		end
		
		local vipLev = 0
		for k,v in ipairs(tb_vip_base) do
			local cz = v.chongzhi
			if rechage >= cz then
				vipLev = v.id
			else
				break
			end
		end
		
		-- 充值转盘
		local lotteryTimes = 0
		for k, v in ipairs(tb_recharge_wheel) do
			local cz = v.recharges
			if rechage >= cz then
				lotteryTimes = v.id
			else
				break
			end
		end
		self:SetRechargeLotteryTimes(lotteryTimes)
		
		if vipLev > 0 then
			self:SetVIP(vipLev, 0)
		end
		
	end
end

--私聊后做点什么
function PlayerInfo:DoAfterChatWhisper ( friendGuid)
	
end

--获取玩家账号
function PlayerInfo:GetAccount ()
	return self:GetStr(PLAYER_STRING_FIELD_ACCOUNT)
end

--背包扩展
function PlayerInfo:DoBagExtension(bag_id,extension_type,bag_pos)
	-- local itemMgr = self:getItemMgr()
	-- if(bag_id == BAG_TYPE_MAIN_BAG)then
		-- --获取背包大小
		-- local bag_size = itemMgr:getBagSize(bag_id)
		-- if(bag_size == nil or bag_size >= MAX_BAG_MAIN_SIZE_EXTENSION)then
			-- return
		-- end
		-- if(bag_size >= bag_pos and extension_type == BAG_EXTENSION_TYPE_GOLD)then
			-- return
		-- end
		-- local bag_game_set = tb_game_set[1]
		-- if(bag_game_set == nil)then
			-- return
		-- end
		-- --程序格式：背包格子所需时长=背包开启时长系数*（当前已开启的背包格子-初始开启格子数-1）*（当前已开启的背包格子-初始开启格子数）+背包开启时间参数
		-- local config = bag_game_set.value
		-- local next_time = math.floor(config[3] * (bag_pos - (config[1]-1)) * (bag_pos - config[1])) + config[4]
		-- --元宝开启
		-- if(extension_type == BAG_EXTENSION_TYPE_GOLD)then
			-- local all_time = self:GetExtensionEndTime() - os.time()
			-- for i = bag_size + 2,bag_pos do
				-- all_time = all_time +  math.floor(config[3] * (i - (config[1]-1)) * (i - config[1])) + config[4]
			-- end
			-- local money = math.ceil((all_time/60 + 1)*config[5])
			-- if(self:GetMoney(MONEY_TYPE_GOLD_INGOT) >= money)then
				-- self:SubMoney(MONEY_TYPE_GOLD_INGOT,MONEY_CHANGE_BAG_EXTENSION,money)					
				-- self:SetExtensionEndTime(os.time() + next_time)
				-- itemMgr:setBagSize(bag_id,bag_pos)
			-- end
		-- elseif(self:GetExtensionEndTime() <= os.time())then	--自动开启
			-- self:SetExtensionEndTime(os.time() + math.floor(config[3] * (bag_size+1 - (config[1]-1)) * (bag_size+1 - config[1])) + config[4])
			-- itemMgr:setBagSize(bag_id,bag_size+1)
		-- end
	-- end
end

--添加物品根据模板来
function PlayerInfo:AddItemByEntry(entry, count, money_log, item_log, item_bind, isAppaisal, isSystem, strong_lv, fail_time, bag_type, pos)
	local itemMgr = self:getItemMgr()						
	itemMgr:addItem(entry, count, item_bind, isAppaisal, isSystem, strong_lv, fail_time, bag_type, pos)
	-- 判断获得物品以后的提示逻辑
	local config = tb_item_template[entry]
	for _, record in pairs(config.records) do
		-- 全服
		if record == ITEM_RECORD_BROADCAST then
			local itemName = GetColordItemName(entry)
			app:CallOptResult(OPRATE_TYPE_REWARD, item_log, {ToShowName(self:GetName()), itemName})
			
			--if config.quality >= 4 and config.type == ITEM_TYPE_EQUIP then
			--	app:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_PAIWEI_RANKUP, {ToShowName(self:GetName()), itemName})
			--end
		end
		
		--[[
		-- 仙府宝箱
		if record == ITEM_RECORD_XIANFU then
			local str = string.format("%s|%d|%d", self:GetName(), entry, count)
			globalValue:AddXianfuRecord(str)
		end
		--]]
	end
	WriteItemLog(self, item_log, entry, 0, count)
end

--使用多个物品
function PlayerInfo:useAllItems(moneyLog, itemLog, costItemTable, multiple, relateItemIds, relateItemNums)
	local resources, items, _ = AllItemsSplitResourceAndItemAndExp(costItemTable, multiple)
	
	if not self:checkMoneyEnoughs(resources, multiple) then
		return false
	end
	
	if not self:hasMulItem(items, multiple) then
		return false
	end
	-- moneyLog 为nil
	if not moneyLog and #resources > 0 then
		return false
	end
	self:costMoneys(moneyLog, resources, multiple, relateItemIds, relateItemNums)
	-- itemLog 为nil
	if not itemLog and #items > 0 then
		return false
	end
	self:useMulItem(itemLog, items, multiple)
	
	return true
end

--检测多个物品
function PlayerInfo:hasAllItems(costItemTable, multiple)
	local resources, items, _ = AllItemsSplitResourceAndItemAndExp(costItemTable, multiple)
	
	if not self:checkMoneyEnoughs(resources, multiple) then
		return false
	end
	
	if not self:hasMulItem(items, multiple) then
		return false
	end
	
	return true
end


--使用多个物品
function PlayerInfo:useMulItem(itemLog, costItemTable,multiple)
	if not itemLog then
		return false
	end
	local itemMgr = self:getItemMgr()						
	return itemMgr:useMulItem(itemLog, costItemTable,multiple)
end

--判断是否同时拥有多个物品
function PlayerInfo:hasMulItem(costItemTable,multiple)
	local itemMgr = self:getItemMgr()						
	return itemMgr:hasMulItem(costItemTable,multiple)
end

-- 扣除多个物品 不够用钱换
function PlayerInfo:useMulItemIfCostMoneyEnabled(itemLog, costItemTable, multiple)
	multiple = multiple or 1
	
	local ret, items, res = self:checkItemEnoughIfCostMoneyEnabled(costItemTable, multiple)
	if not ret then
		return false
	end
	if not self:useMulItem(itemLog, items) then
		return false
	end
	if not self:costMoneys(MONEY_CHANGE_USE_ITEM, res) then
		return false
	end
	
	return true
end

-- 判断材料不够花元宝能否满足条件
-- 返回
--	true, realCostItemTable, costMoneyTable
-- false, nil, nil
function PlayerInfo:checkItemEnoughIfCostMoneyEnabled(costItemTable, multiple)
	local itemMgr = self:getItemMgr()	
	
	-- 找一种扣除方案
	local ret, costItem, costIngot = itemMgr:costMoneyEnabledSolution(costItemTable, multiple)
	if not ret then
		return false, nil, nil
	end
	
	-- 如果需要扣钱
	local costResouce = {}
	if costIngot > 0 then
		-- 返回实际的扣除资源值
		ret, costResouce = self:checkMoneyEnoughIfUseGoldIngot({{MONEY_TYPE_BIND_GOLD, costIngot}})
		if not ret then
			return false, nil, nil
		end
	end
	
	return true, costItem, costResouce
end


-- 获取GM等级
function PlayerInfo:GetGmNum()
	return self:GetByte(PLAYER_FIELD_BYTES_5, 0)
end

-- 获取禁言时间
function PlayerInfo:GetGagEndTime()
	return self:GetUInt32(PLAYER_EXPAND_INT_GAG_END_TIME)
end

-- 获取是否禁言中
function PlayerInfo:IsGag()
	return self:GetGagEndTime() > os.time()
end
--//有GM命令权限
function PlayerInfo:GetGMLevel()
	return math.fmod(self:GetGmNum(), 10)
end
--//客服GM权限 
function PlayerInfo:GetFalseGM()
	return math.floor(math.fmod(self:GetGmNum(), 100) / 10)
end
--//美女主播权限 2表示不如排行榜
function PlayerInfo:GetGirlGM()
	return math.floor(self:GetGmNum() / 100)
end

-- 移除失效幻化
function PlayerInfo:OnRemoveExpireIllusion()
	local spellMgr = self:getSpellMgr()
	local expiredTable = spellMgr:checkIfIllusionExpired()
	
	-- 移除p对象中和过期幻化有关的数据
	self:PlayerRemoveExpiredIllusion(expiredTable)
end

-- 移除失效神兵
function PlayerInfo:OnRemoveExpireDivine()
	
end

-- 是否自动购买血瓶
function PlayerInfo:isAutoBuyHpItem()
	return self:GetByte(PLAYER_FIELD_HOOK_BYTE1, 2) > 0
end

-- 自动购买血瓶时银两不够是否用元宝
function PlayerInfo:isAutoBuyHpItemUseGold()
	return self:GetByte(PLAYER_FIELD_HOOK_BYTE1, 3) > 0
end

-- 是否 自动使用绑银购买复活丹
function PlayerInfo:isBuyRespawnByBindGold()
	return self:GetByte(PLAYER_FIELD_HOOK_BYTE3, 1) > 0
end

-- 自动购买复活丹时, 绑银不足用元宝
function PlayerInfo:isBuyRespawnByGold()
	return self:GetByte(PLAYER_FIELD_HOOK_BYTE3, 2) > 0
end

-- 是否拒绝接受系统消息
function PlayerInfo:isDeclineSystemMsg()
	return self:GetByte(PLAYER_FIELD_DECLINE_CHANNEL_BYTE0, 0) > 0
end

-- 是否拒绝接受帮派消息
function PlayerInfo:isDeclineFactionMsg()
	return self:GetByte(PLAYER_FIELD_DECLINE_CHANNEL_BYTE0, 1) > 0
end

-- 是否拒绝接受组队消息
function PlayerInfo:isDeclineGroupMsg()
	return self:GetByte(PLAYER_FIELD_DECLINE_CHANNEL_BYTE0, 2) > 0
end

-- 是否拒绝接受世界消息
function PlayerInfo:isDeclineWorldMsg()
	return self:GetByte(PLAYER_FIELD_DECLINE_CHANNEL_BYTE0, 3) > 0
end


-- 获得最后一次参加世界BOSS的id
function PlayerInfo:GetLastJoinID()
	return self:GetUInt32(PLAYER_INT_FIELD_WORLD_BOSS_JOIN_ID)
end

-- 设置最后一次参加世界BOSS的id
function PlayerInfo:SetLastJoinID(id)
	if self:GetLastJoinID() == id then
		return
	end
	self:SetUInt32(PLAYER_INT_FIELD_WORLD_BOSS_JOIN_ID, id)
end

-- 获得最后一次参加世界BOSS的状态
function PlayerInfo:GetLastState()
	return self:GetByte(PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE, 0)
end

-- 设置最后一次参加世界BOSS的状态
function PlayerInfo:SetLastState(state)
	if self:GetLastState() == state then
		return
	end
	self:SetByte(PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE, 0, state)
end

-- 获得最后一次参加世界BOSS的分线
function PlayerInfo:GetLastLine()
	return self:GetByte(PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE, 1)
end

-- 设置最后一次参加世界BOSS的分线
function PlayerInfo:SetLastLine(line)
	if self:GetLastLine() == line then
		return
	end
	self:SetByte(PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE, 1, line)
end

-- 获得最后一次参加世界BOSS的自身死亡次数
function PlayerInfo:GetLastDeath()
	return self:GetByte(PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE, 2)
end

-- 增加最后一次参加世界BOSS的自身死亡次数
function PlayerInfo:SetLastDeath(count)
	if self:GetLastDeath() == count then
		return
	end
	self:AddByte(PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE, 2, count)
end
--设置角色神兵数量
function PlayerInfo:SetDivineNum(val)
	self:SetUInt32(PLAYER_FIELD_DIVINE_NUM,val)
end
--设置神兵总战力
function PlayerInfo:SetDivineForce(val)
	local old = self:GetUInt32(PLAYER_FIELD_DIVINE_FORCE)
	if old ~= val then
		self:SetUInt32(PLAYER_FIELD_DIVINE_FORCE,val)
	end
end

--设置最好的坐骑信息
function PlayerInfo:SetMountBest(id,lev,start)
	self:SetByte(PLAYER_FIELD_MOUNT_BEST,0,id)
	self:SetByte(PLAYER_FIELD_MOUNT_BEST,1,lev)
	self:SetByte(PLAYER_FIELD_MOUNT_BEST,2,start)
end

--设置坐骑总战力
function PlayerInfo:SetMountForce(val)
	self:SetUInt32(PLAYER_FIELD_MOUNT_FORCE,val)
end

-- 设置技能战力
function PlayerInfo:SetSkillForce(val)
	self:SetUInt32(PLAYER_FIELD_SKILL_FORCE, val)
end
--[[
	PLAYER_FIELD_SKILL_FORCE			= PLAYER_FIELD_MOUNT_FORCE + 1,				//技能战力
	PLAYER_FILED_EQUIP_FORCE				= PLAYER_FIELD_SKILL_FORCE + 1,				//装备战力
	PLAYER_FIELD_EQUIPDEVELOP_FORCE			= PLAYER_FILED_GEM_FORCE + 1,				//炼器战力
	PLAYER_INT_FIELD_REALMBREAK_FORCE	//境界战力
--]]

function PlayerInfo:SetEquipForce(val)
	self:SetUInt32(PLAYER_FILED_EQUIP_FORCE, val)
end

function PlayerInfo:SetEquipDevelopForce(val)
	self:SetUInt32(PLAYER_FIELD_EQUIPDEVELOP_FORCE, val)
end

function PlayerInfo:SetRealmbreakForce(val)
	self:SetUInt32(PLAYER_INT_FIELD_REALMBREAK_FORCE, val)
end

function PlayerInfo:SetAdventureSkillForce(val)
	self:SetUInt32(PLAYER_INT_FIELD_ADVENTURE_SKILL_FORCE, val)
end


--设置神兵总战力
function PlayerInfo:SetAllTalismanForce(val)
	local old = self:GetUInt32(PLAYER_INT_FIELD_TALISMAN_FORCE)
	if old ~= val then
		self:SetUInt32(PLAYER_INT_FIELD_TALISMAN_FORCE,val)
	end
end

--设置神羽战力
function PlayerInfo:SetWingsForce(val)
	local old = self:GetUInt32(PLAYER_INT_FIELD_WINGS_FORCE)
	if old ~= val then
		self:SetUInt32(PLAYER_INT_FIELD_WINGS_FORCE,val)
	end
end

--设置称号战力
function PlayerInfo:SetTitleForce(val)
	local old = self:GetUInt32(PLAYER_INT_FIELD_TITLE_FORCE)
	if old ~= val then
		self:SetUInt32(PLAYER_INT_FIELD_TITLE_FORCE,val)
	end
end

local OFFLINE_MAIL_PATH_FORMAT = __OFFLINE_MAIL_FOLDER__.."/%s.mail"
local OFFLINE_MAIL_INFO = "%u|%u|%u|%s|%s|%s|%s\n"

-- 添加邮件
function AddGiftPacksData(guid, id, gift_type,start_time,end_time,gift_name,gift_desc,item_config,item_from)
	if(guid == "")then
		return
	end
	
	local player = app.objMgr:getObj(guid)
	-- 没有就加离线文件
	if not player or not player:isLogined() then 
		local path = string.format(OFFLINE_MAIL_PATH_FORMAT, guid)
		local fp, err = io.open(path, "a")
		if err then
			outFmtError("save offline mail fail for path = %s", path)
			return
		end
		fp:write(string.format(OFFLINE_MAIL_INFO, gift_type, start_time, end_time, gift_name, gift_desc, item_config, item_from))
		fp:close()
		return 
	end
	
	-- 玩家自己加邮件
	local giftPack = player:getGiftPacksInfo()
	giftPack:AddGiftPacksInfo(gift_type, start_time, end_time, gift_name, gift_desc, item_config, item_from)
end

-- 玩家上线读离线文件
function PlayerInfo:GetOfflineMail()
	local path = string.format(OFFLINE_MAIL_PATH_FORMAT, self:GetGuid())
	local fp, err = io.open(path, "r+")
	if err then
		--outFmtDebug("err for : %s at path %s", err, path)
		return
	end
	
	local giftPack = self:getGiftPacksInfo()
	
	while (true) do
		local content = fp:read("*l")
		if not content or content == "" then
			break
		end
		local values = string.split(content, "|")
		local gift_type, start_time, end_time, gift_name, gift_desc, item_config, item_from
		gift_type = tonumber(values[ 1 ])
		start_time = tonumber(values[ 2 ])
		end_time = tonumber(values[ 3 ])
		gift_name = values[ 4 ]
		gift_desc = values[ 5 ]
		item_config = values[ 6 ]
		item_from = values[ 7 ]
		
		giftPack:AddGiftPacksInfo(gift_type, start_time, end_time, gift_name, gift_desc, item_config, item_from)
	end
	fp:close()
	
	-- 清空文件
	local fp, err = io.open(path, "w+")
	if err then
		--outFmtDebug("clear file err for : %s at path %s", err, path)
		return
	end
	fp:close()
end

-- 等级改变了
function PlayerInfo:OnLevelChanged()
	outFmtDebug("level changed")
	self:factionUpLevel()
	
	-- 成就
	self:SetAchieve(QUEST_TARGET_TYPE_PLAYER_LEVEL, self:GetLevel())
	-- 加任务
	local questMgr = self:getQuestMgr()
	questMgr:OnUpdate(QUEST_TARGET_TYPE_PLAYER_LEVEL, {self:GetLevel()})
	questMgr:OnCheckMainQuestActive(self:GetLevel())
	questMgr:OnCheckRealmQuestActive(self:GetLevel())
end

-- 战力改变了
function PlayerInfo:OnForceChanged()
	outFmtDebug("force changed")
	self:factionUpForce()
	-- 成就
	self:SetAchieve(QUEST_TARGET_TYPE_PLAYER_FORCE, self:GetForce())
	-- 加任务
	local questMgr = self:getQuestMgr()
	questMgr:OnUpdate(QUEST_TARGET_TYPE_PLAYER_FORCE, {self:GetForce()})
end

-- 增加主线任务
function PlayerInfo:AddFirstQuest()
	local level = self:GetLevel()
	self:AddLevelActiveQuest(level)
	self:UnlockModuleByLevel(0, level)
end

-- 增加等级解锁的任务
function PlayerInfo:AddLevelActiveQuest(level)
	if not tb_char_level[level] then
		return
	end
	
	local quests = tb_char_level[level].activeQuests
	local questMgr = self:getQuestMgr()
	
	for _, questId in pairs(quests) do
		if questId > 0 and tb_quest[questId] then
			if tb_quest[questId].type == QUEST_TYPE_DAILY2 then
				questMgr:OnAddFirstDaily2Quest(tb_quest_daily2_base[ 1 ].npcQuest)
			elseif tb_quest[questId].type == QUEST_TYPE_DAILY then
				questMgr:OnAddFirstCircleQuest(tb_quest_daily_base[ 1 ].npcQuest)
			else
				local binstart = nil
				local binend = nil
				if tb_quest[questId].type == QUEST_TYPE_ADVENTURE then
					binstart = QUEST_FIELD_ADVENTURE_QUEST_START
					binend = QUEST_FIELD_ADVENTURE_QUEST_END
				elseif tb_quest[questId].type == QUEST_TYPE_REALMBREAK then
					binstart = QUEST_FIELD_REALMBREAK_QUEST_START
					binend = QUEST_FIELD_REALMBREAK_QUEST_END
				end 
				questMgr:OnAddQuest(questId, binstart, binend)
			end
		else
			outFmtDebug("!!!!!!!!!!!!!!!!AddLevelActiveQuest quest id %d not exist",questId)
		end
	end
end

-- 获得当前主线任务id
function PlayerInfo:GetMainQuestID()
	return self:GetUInt32(PLAYER_INT_FIELD_MAIN_QUEST_ID)
end

-- 设置当前主线任务id
function PlayerInfo:SetMainQuestID(value)
	self:SetUInt32(PLAYER_INT_FIELD_MAIN_QUEST_ID, value)
end

-- 章节奖励是否领取
function PlayerInfo:IsQuestChapterPicked(indx)
	return self:GetBit(PLAYER_INT_FIELD_QUEST_CHAPTER, indx)
end

-- 设置章节奖励领取
function PlayerInfo:SetQuestChapterPicked(indx)
	self:SetBit(PLAYER_INT_FIELD_QUEST_CHAPTER, indx)
end

-- 获得3v3匹配值
function PlayerInfo:GetWorld3v3MatchValue()
	local value = self:GetForce() + self:GetKuafu3v3TrendInfo() * 50
	return value
end


-- 获得跨服3v3积分
function PlayerInfo:GetKuafu3v3Score()
	return self:GetUInt32(PLAYER_INT_FIELD_WORLD_3V3_SCORE)
end

-- 设置跨服3v3积分
function PlayerInfo:SetKuafu3v3Score(val)
	self:SetUInt32(PLAYER_INT_FIELD_WORLD_3V3_SCORE, val)
	if val == 0 then
		self:SetKuafu3v3TrendInfo(0)
		self:SetUInt32(PLAYER_INT_FIELD_WORLD_3V3_WINS, 0)
	end
end

-- 增加跨服3v3积分
function PlayerInfo:AddKuafu3v3Score(val)
	-- 加临时积分
	local ret = val + self:GetKuafu3v3Score()
	ret = math.max(ret, 0)
	self:SetKuafu3v3Score(ret)
	
	local timestamp = GetTodayStartTimestamp()
	self:SetKuafu3v3TotalScore(timestamp)

	-- 更新排名
	rankInsertTask(self:GetGuid(), RANK_TYPE_3V3)
end

function PlayerInfo:On3v3RankChanged(rank)
	--[[if rank >=1 and rank <= 10 then
		app:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_3V3_RANKUP,{self:GetNoticeName(),rank})
	end--]]
end


-- 获得参与时间
function PlayerInfo:GetKuafu3v3TotalScore()
	return self:GetUInt32(PLAYER_INT_FIELD_WORLD_3V3_TOTAL_SCORE)
end

-- 设置参与时间
function PlayerInfo:SetKuafu3v3TotalScore(val)
	self:SetUInt32(PLAYER_INT_FIELD_WORLD_3V3_TOTAL_SCORE, val)
end

-- 获得当作总局数
function PlayerInfo:GetKuafu3v3TrendInfo()
	return self:GetUInt32(PLAYER_INT_FIELD_WORLD_3V3_TREND_INFO)
end

-- 设置当作总局数
function PlayerInfo:SetKuafu3v3TrendInfo(value)
	self:SetUInt32(PLAYER_INT_FIELD_WORLD_3V3_TREND_INFO, value)
end

function PlayerInfo:AddKuafu3v3TrendInfo()
	self:AddUInt32(PLAYER_INT_FIELD_WORLD_3V3_TREND_INFO, 1)
end

-- 增加跨服3v3胜负趋势
function PlayerInfo:Kuafu3v3Win()
	self:AddUInt32(PLAYER_INT_FIELD_WORLD_3V3_WINS, 1)
	-- 胜利场数+1
	self:AddKuafu3v3TrendInfo()
end

-- 减少跨服3v3胜负趋势
function PlayerInfo:Kuafu3v3Lose()
	self:AddKuafu3v3TrendInfo()
end

-- 获得斗剑台排名
function PlayerInfo:GetDoujiantaiRank()
	return self:GetUInt32(PLAYER_INT_FIELD_DOUJIANTAI_RANK)
end

-- 设置斗剑台排名
function PlayerInfo:SetDoujiantaiRank(rank)
	if rank > 0 and rank <= 10 and rank < self:GetDoujiantaiRank() then
		app:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_DOUJIANTAI_RANKUP,{self:GetNoticeName(),rank})
	end
	
	self:SetUInt32(PLAYER_INT_FIELD_DOUJIANTAI_RANK, rank)
end

-- 获得斗剑台最新一次刷新时间戳
function PlayerInfo:GetDoujiantaiLastRefreshTime()
	return self:GetUInt32(PLAYER_INT_FIELD_DOUJIANTAI_REFRESH_TIME)
end

-- 设置斗剑台最新一次刷新时间戳
function PlayerInfo:SetDoujiantaiLastRefreshTime(val)
	self:SetUInt32(PLAYER_INT_FIELD_DOUJIANTAI_REFRESH_TIME, val)
end


-- 获得玩家属性列表
function PlayerInfo:GetAttrs()
	local attrs = {}
	
	for attr_id, playerField in pairs(attrKeys) do
		local value = self:GetDouble(playerField)
		table.insert(attrs, {attr_id, value})
	end
	
	return attrs
end

function PlayerInfo:GetSpells()
	local spells = {}
	
	--local total_slot_1_cd = 0
	for i = PLAYER_INT_FIELD_SPELL_START, PLAYER_INT_FIELD_SPELL_END-1 do
		local id = self:GetUInt16(i, 0)
		if id > 0 then
			local config = tb_skill_base[id]
			if 1 <= config.skill_slot and config.skill_slot <= 5 then
				local level = self:GetByte(i, 2)
				local slot  = self:GetByte(i, 3)
				local groupCD = config.groupCD
				local rate = 0
				table.insert(spells, {id, rate, groupCD, level, slot})
			end
		end
	end
	
	rates = {4000, 3000, 3000}
	local rlen = #spells - 3	

	for i = 1, rlen do
		table.insert(rates, 10000)
	end
	
	for i = 1, #spells do
		spells[ i ][ 2 ] = rates[ i ]
	end
	
	return spells
end

function PlayerInfo:passiveSpellInRange(ps, a, b)
	for i = a, b do
		local spellID	= self:GetUInt16(i, 0)
		local level		= self:GetUInt16(i, 1)
		if spellID > 0 then
			table.insert(ps, {spellID, level})
		end
	end
end

function PlayerInfo:GetPassivespells()
	local ps = {}
	self:passiveSpellInRange(ps, PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_START, PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_END-1)
	return ps
end

function PlayerInfo:GetDummyInfo()
	local config = {}
	config.name   = self:GetName()
	config.gender = self:GetGender()
	config.level  = self:GetLevel()
	config.attrs  = self:GetAttrs()
	config.weapon = self:GetWeapon()
	config.avatar = self:GetAvatar()
	config.divine = self:GetDivine()
	config.spells = self:GetSpells()
	config.passivespells = self:GetPassivespells()
	config.force  = self:GetForce()
	config.vip    = self:GetVIP()
	config.reverse1 = 0
	config.reverse2 = 0
	config.reverse3 = 0
	config.reverse4 = 0
	config.reverse5 = 0
	
	return config
end

-- 获得avatar
function PlayerInfo:GetAvatar()
	return self:GetUInt16(PLAYER_INT_FIELD_APPEARANCE, 1)
end

-- 获得武器
function PlayerInfo:GetWeapon()
	return self:GetUInt32(PLAYER_FIELD_EQUIPMENT + EQUIPMENT_TYPE_MAIN_WEAPON)
end

-- 获得神兵
function PlayerInfo:GetDivine()
	return self:GetUInt16(PLAYER_INT_FIELD_APPEARANCE, 0)
end

-- 获得欠款
function PlayerInfo:GetArrears()
	return self:GetDouble(PLAYER_INT_FIELD_ARREARS)
end

-- 增加欠款
function PlayerInfo:AddArrears(val)
	self:AddDouble(PLAYER_INT_FIELD_ARREARS, val)
end

-- 清空欠款
function PlayerInfo:ClearArrears()
	self:SetDouble(PLAYER_INT_FIELD_ARREARS, 0)
end

-- 每日任务完成数
function PlayerInfo:GetDailyQuestFinished()
	return self:GetUInt32(PLAYER_INT_FIELD_DAILY_QUEST_FINISHED)
end

-- 获得每日任务完成数
function PlayerInfo:GetDailyQuestFinished()
	return self:GetUInt32(PLAYER_INT_FIELD_DAILY_QUEST_FINISHED)
end

-- 增加每日任务完成数
function PlayerInfo:AddDailyQuestFinished()
	self:AddUInt32(PLAYER_INT_FIELD_DAILY_QUEST_FINISHED, 1)
end

-- 清空每日任务完成数
function PlayerInfo:ClearDailyQuestFinished()
	self:SetUInt32(PLAYER_INT_FIELD_DAILY_QUEST_FINISHED, 0)
end

-- 获得整理背包时间戳
function PlayerInfo:GetBagSortTime()
	return self:GetUInt32(PLAYER_INT_FIELD_BAG_SORT_TIME)
end

-- 设置整理背包时间戳
function PlayerInfo:SetBagSortTime(val)
	self:SetUInt32(PLAYER_INT_FIELD_BAG_SORT_TIME, val)
end

--获取帮派商店已购买商品index 和 num
function PlayerInfo:GetBuyedFactionShopItem(item)
	for i=PLAYER_INT_FIELD_BUYED_FACTION_SHOP,PLAYER_INT_FIELD_BUYED_FACTION_SHOP_END-1 do
		local id = self:GetUInt16(i,0)
		if id == item then
			return i,self:GetUInt16(i,1)
		end
	end
	return -1,0
end

--添加帮派商店已购买商品index 和 num
function PlayerInfo:AddBuyedFactionShopItem(item_id,item_num)
	for i=PLAYER_INT_FIELD_BUYED_FACTION_SHOP,PLAYER_INT_FIELD_BUYED_FACTION_SHOP_END-1 do
		local id = self:GetUInt16(i,0)
		local num = self:GetUInt16(i,1)
		if id == 0 then
			self:SetUInt16(i,0,item_id)
			self:SetUInt16(i,1,item_num)
			return
		elseif id == item_id then
			self:SetUInt16(i,1,num + item_num)
			return
		end
	end
end

--清理帮派商店已购买商品index 和 num
function PlayerInfo:ClearBuyedFactionShopItem()
	for i=PLAYER_INT_FIELD_BUYED_FACTION_SHOP,PLAYER_INT_FIELD_BUYED_FACTION_SHOP_END-1 do
		self:SetUInt16(i,0,0)
		self:SetUInt16(i,1,0)
	end
end



--家族建筑升级每日次数限制
function PlayerInfo:SetFactionBuildingSpeedUpDailyCount(value)
	self:SetUInt32(PLAYER_INT_FILED_FACTION_BUILDING_SPEEDUP_DAILY_COUNT,value)
end
function PlayerInfo:GetFactionBuildingSpeedUpDailyCount()
	return self:GetUInt32(PLAYER_INT_FILED_FACTION_BUILDING_SPEEDUP_DAILY_COUNT)
end
function PlayerInfo:AddFactionBuildingSpeedUpDailyCount(value)
	self:AddUInt32(PLAYER_INT_FILED_FACTION_BUILDING_SPEEDUP_DAILY_COUNT,value)
end

function PlayerInfo:DailyResetFactionBuildingSpeedUpDailyCount()
	self:SetFactionBuildingSpeedUpDailyCount(0)
end


--家族贡献礼物兑换每日次数限制
function PlayerInfo:SetFactionDonateGiftExchangeDailyCount(value)
	self:SetUInt32(PLAYER_INT_FILED_FACTION_DONATE_GIFT_EXCHANGE_DAILY_COUNT,value)
end
function PlayerInfo:GetFactionDonateGiftExchangeDailyCount()
	return self:GetUInt32(PLAYER_INT_FILED_FACTION_DONATE_GIFT_EXCHANGE_DAILY_COUNT)
end
function PlayerInfo:AddFactionDonateGiftExchangeDailyCount(value)
	self:AddUInt32(PLAYER_INT_FILED_FACTION_DONATE_GIFT_EXCHANGE_DAILY_COUNT,value)
end

function PlayerInfo:DailyResetFactionDonateGiftExchangeDailyCount()
	self:SetFactionDonateGiftExchangeDailyCount(0)
end

--删除家族礼物功能
--[[
--玩家魅力值
function PlayerInfo:SetPlayerCharmPoint(value)
	self:SetDouble(PLAYER_INT_FILED_CHARM_POINT,value)
end

function PlayerInfo:AddPlayerCharmPoint(value)
	self:AddDouble(PLAYER_INT_FILED_CHARM_POINT,value)
end

function PlayerInfo:GetPlayerCharmPoint()
	return self:GetDouble(PLAYER_INT_FILED_CHARM_POINT)
end

--玩家礼物历史记录
--礼物count_id
function PlayerInfo:SetPlayerGiftCountID(value)
	self:SetUInt32(PLAYER_INT_FILED_FACTION_GIFT_NEXT_COUNT_ID,value)
end

function PlayerInfo:AddPlayerGiftCountID(value)
	self:AddUInt32(PLAYER_INT_FILED_FACTION_GIFT_NEXT_COUNT_ID,value)
end

function PlayerInfo:GetPlayerGiftCountID()
	return self:GetUInt32(PLAYER_INT_FILED_FACTION_GIFT_NEXT_COUNT_ID)
end


-- 礼物ID 
function PlayerInfo:SetGiftID(index,value)
	self:SetUInt32(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_ID,value)
end

function PlayerInfo:GetGiftID(index)
	return self:GetUInt32(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_ID)
end

-- 本次礼物总魅力值
function PlayerInfo:SetGiftPoint(index,value)
	self:SetUInt32(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_POINT,value)
end

function PlayerInfo:GetGiftPoint(index)
	return self:GetUInt32(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_POINT)
end

-- 感谢标识信息
function PlayerInfo:SetGiftFlagThank(index,value)
	if value == 1 then
		self:SetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,1)
	elseif value == 0 then
		self:UnSetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,1)
	end
end

function PlayerInfo:GetGiftFlagThank(index)
	local result = self:GetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,1)
	if result then
		return 1
	else
		return 0
	end
end

-- 女王回复标识信息
function PlayerInfo:SetGiftFlagReply(index,value)
	if value == 1 then
		self:SetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,2)
	elseif value == 0 then
		self:UnSetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,2)
	end
end

function PlayerInfo:GetGiftFlagReply(index)
	local result = self:GetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,2)
	if result then
		return 1
	else
		return 0
	end
end

-- 奖励领取标识信息
function PlayerInfo:SetGiftFlagReward(index,value)
	if value == 1 then
		self:SetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,3)
	elseif value == 0 then
		self:UnSetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,3)
	end
end

function PlayerInfo:GetGiftFlagReward(index)
	local result = self:GetBit(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_FLAG_THANK,3)
	if result then
		return 1
	else
		return 0
	end
end

-- 赠送时间
function PlayerInfo:SetGiftTime(index,value)
	self:SetUInt32(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_TIME,value)
end

function PlayerInfo:GetGiftTime(index)
	return self:GetUInt32(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_TIME)
end

-- 赠送者生成的礼物序号
function PlayerInfo:SetGiftCountID(index,value)
	self:SetUInt32(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_COUNT_ID,value)
end

function PlayerInfo:GetGiftCountID(index)
	return self:GetUInt32(PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_INT_GIFT * index + FACTION_DATA_INT_GIFT_COUNT_ID)
end

-- 赠送者guid
function PlayerInfo:SetGiftGuid(index,value)
	self:SetStr(PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_STRING_GIFT * index + FACTION_DATA_STRING_GIFT_GUID,value)
end

function PlayerInfo:GetGiftGuid(index)
	return self:GetStr(PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_STRING_GIFT * index + FACTION_DATA_STRING_GIFT_GUID)
end

-- 赠送者留言
function PlayerInfo:SetGiftMsg(index,value)
	self:SetStr(PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_STRING_GIFT * index + FACTION_DATA_STRING_GIFT_MSG,value)
end

function PlayerInfo:GetGiftMsg(index)
	return self:GetStr(PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_STRING_GIFT * index + FACTION_DATA_STRING_GIFT_MSG)
end

-- 礼物列表详情	物品1 \2 数量1 \1 物品2 \2 数量2
function PlayerInfo:SetGiftItemList(index,value)
	self:SetStr(PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_STRING_GIFT * index + FACTION_DATA_STRING_GIFT_ITEM_LIST,value)
end

function PlayerInfo:GetGiftItemList(index)
	return self:GetStr(PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_STRING_GIFT * index + FACTION_DATA_STRING_GIFT_ITEM_LIST)
end

-- 回复信息列表		玩家guid \2 信息 \2 回复类型 \2 时间 \1 玩家guid \2 信息 \2 回复类型 \2 时间
function PlayerInfo:SetGiftReplyList(index,value)
	self:SetStr(PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_STRING_GIFT * index + FACTION_DATA_STRING_GIFT_REPLY_LIST,value)
end

function PlayerInfo:GetGiftReplyList(index)
	return self:GetStr(PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_STRING_GIFT * index + FACTION_DATA_STRING_GIFT_REPLY_LIST)
end


function PlayerInfo:GetGiftEmptyIndex()
	local oldest_time = os.time()
	local oldest_index = 0
	
	for index = 0, MAX_FACTION_DATA_GIFT_COUNT - 1 do
		if self:GetGiftGuid(index) == "" or string.len (self:GetGiftGuid(index)) == 0 then
			return index
		elseif self:GetGiftTime(index) < oldest_time then
			oldest_time = self:GetGiftTime(index)
			oldest_index = index
		end
	end
	return oldest_index
end

function PlayerInfo:GetGiftIndexByCountID(count_id)
	for index = 0, MAX_FACTION_DATA_GIFT_COUNT - 1 do
		if self:GetGiftCountID(index) == count_id then
			return index
		end
	end
	return nil
end


--添加记录
function PlayerInfo:AddGiftInfo(id,point,item_list,count_id,msg)
	local index = self:GetGiftEmptyIndex()
	
	self:SetGiftGuid(index,self:GetGuid())
	self:SetGiftMsg(index,msg)
	self:SetGiftItemList(index,item_list)
	self:SetGiftReplyList(index,"")
	self:SetGiftID(index,id)
	self:SetGiftPoint(index,point)
	self:SetGiftFlagThank(index,0)
	self:SetGiftFlagReply(index,0)
	self:SetGiftFlagReward(index,0)
	self:SetGiftTime(index,os.time())
	self:SetGiftCountID(index,count_id)
end



--上线更新记录

function PlayerInfo:LoginUpdateGiftInfo()
	local faction = app.objMgr:getObj(self:GetFactionId())
	if faction == nil then
		return
	end
	
	-- 获取帮派数据的guid
	local data_guid = guidMgr.replace(self:GetFactionId(), guidMgr.ObjectTypeFactionData)
	local factionData = app.objMgr:getObj(data_guid)
	if(not factionData)then
		return
	end
	
	local gift_table = factionData:GetGiftCacheByGuid(self:GetGuid())
	for _,info in ipairs(gift_table) do
		local index = self:GetGiftIndexByCountID(info.count_id)
		if index then
			self:SetGiftFlagThank(index,info.thank)
			self:SetGiftReplyList(index,info.msg)
		end
	end
	
end

--领取奖励

function PlayerInfo:GetFactionGiftExreward(count_id)
	local index = self:GetGiftIndexByCountID(count_id)
	if not index then
		outFmtError("find GetFactionGiftExreward fail")
		return
	end
	
	if self:GetGiftFlagThank(index) == 0 then
		outFmtError("find GetFactionGiftExreward gift not thank!!")
		return
	end
	
	if self:GetGiftFlagReward(index) == 1 then
		
		outFmtError("find GetFactionGiftExreward gift reward already get ")
		return
	end
	
	--修改礼包奖励标识
	self:SetGiftFlagReward(index,1)
	
	
	--取得道具列表 获得奖励结果
	local item_list = self:GetGiftItemList(index)
	local item_table = {}
	local tokens = string.split(item_list,SPLIT_THINGS)
	for _,token in pairs(tokens) do
		local info_tokens = string.split(token,SPLIT_THING_DETAIL)
		table.insert(item_table,{tonumber(info_tokens[1]),tonumber(info_tokens[2])})
	end
	
	local reward_table = {}
	for _,v in pairs(item_table) do
		if tb_faction_gift[v[1] ] then
			for _,reward_info in pairs(tb_faction_gift[v[1] ].ex_reward) do
				table.insert(reward_table, {tonumber(reward_info[1]),reward_info[2]*v[2]})
			end
		end
	end
	
	
	--发送奖励
	self:AppdAddItems(reward_table,MONEY_CHANGE_FACTION_GIFT,LOG_ITEM_OPER_TYPE_FACTION_GIFT)
	
	--修改统计数值  未领取数量
	local faction = app.objMgr:getObj(self:GetFactionId())
	if faction == nil then
		return
	end
	
	local index_sender = faction:GetGiftPlayerGuidIndex(self:GetGuid())
	if not index_sender  then 
		outFmtError("get index_sender GetGiftPlayerGuidIndex fail")
		return
	end
	
	faction:SubGiftUncheckCount(index_sender,1)
	
	self:AddFactionGiftBeenThankCount(1)
	
	if self:GetGuid() ~= self:GetGiftGuid(index) then
		self:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_GIFT_GET_EXREWARD)
	end
	outFmtDebug("============GetFactionGiftExreward finish ")
end

--领取所有额外奖励
function PlayerInfo:GetAllFactionGiftExreward(factionData,player)
	for index=0, MAX_FACTION_DATA_GIFT_COUNT-1 do
		local count_id = self:GetGiftCountID(index)
		self:GetFactionGiftExreward(count_id)
	end
	
	outFmtDebug("============GetAllFactionGiftExreward finish ")
	
end

--上线同步魅力值
function PlayerInfo:LoginUpdateCharmPoint()
	local faction = app.objMgr:getObj(self:GetFactionId())
	if not faction then
		return
	end
	
	if self:GetGuid() == faction:GetBangZhuGuid() then
		self:SetPlayerCharmPoint(faction:GetFactionCharmPoint())
	else
		local pos = faction:FindPlayerIndex(self:GetGuid())
		if pos then
			self:SetPlayerCharmPoint(faction:GetFactionMemberCharm(pos))
		end
	end

end

--魅力值礼物赠送次数统计
function PlayerInfo:GetFactionGiftSendCount()
	return self:GetUInt32(PLAYER_INT_FIELD_FACTION_GIFT_SEND_COUNT)
end

function PlayerInfo:AddFactionGiftSendCount(value)
	self:AddUInt32(PLAYER_INT_FIELD_FACTION_GIFT_SEND_COUNT,value)
	-- 加任务
	local questMgr = self:getQuestMgr()
	-- 贡献次数
	questMgr:OnUpdate(QUEST_TARGET_TYPE_CONTRIBUTE_TIMES, {value})
	-- 总贡献次数
	questMgr:OnUpdate(QUEST_TARGET_TYPE_CONTRIBUTE_TOTAL_TIMES, {value})
end

--魅力值礼物赠送魅力统计
function PlayerInfo:GetFactionGiftPointCount()
	return self:GetDouble(PLAYER_INT_FIELD_FACTION_GIFT_POINT_COUNT)
end

function PlayerInfo:AddFactionGiftPointCount(value)
	self:AddDouble(PLAYER_INT_FIELD_FACTION_GIFT_POINT_COUNT,value)
	local questMgr = self:getQuestMgr()
	-- 总贡献魅力
	questMgr:OnUpdate(QUEST_TARGET_TYPE_CONTRIBUTE_CHARM, {value})
end

--魅力值礼物赠送被女王感谢统计
function PlayerInfo:GetFactionGiftBeenThankCount()
	return self:GetUInt32(PLAYER_INT_FIELD_FACTION_GIFT_BEEN_THANK_COUNT)
end

function PlayerInfo:AddFactionGiftBeenThankCount(value)
	-- 加任务
	local questMgr = self:getQuestMgr()
	questMgr:OnUpdate(QUEST_TARGET_TYPE_SINGLE_THX_TIMES, {value})
	questMgr:OnUpdate(QUEST_TARGET_TYPE_TOTAL_THX_TIMES, {value})
	
	self:AddUInt32(PLAYER_INT_FIELD_FACTION_GIFT_BEEN_THANK_COUNT,value)
end
--]]

---------------------------------全民boss---------------------------------------
function PlayerInfo:costMassBossTimes()	
	return false
end

function PlayerInfo:getMassBossTimes()
	return self:GetUInt32(PLAYER_INT_FIELD_MASS_BOSS_TIMES)
end

function PlayerInfo:SetMassBossTimes(times)
	times = times or 1
	self:SetUInt32(PLAYER_INT_FIELD_MASS_BOSS_TIMES, times)
end

function PlayerInfo:AddMassBossTimes(times)
	times = times or 1
	self:AddUInt32(PLAYER_INT_FIELD_MASS_BOSS_TIMES, times)
	local curr = self:getMassBossTimes()
	if curr >= tb_mass_boss_base[ 1 ].dailytimes then
		self:SetMassBossCD(0)
	end
end

function PlayerInfo:SetMassBossBuyedTimes(times)
	self:SetUInt32(PLAYER_INT_FIELD_MASS_BOSS_BUYED_TIMES, times)
end

function PlayerInfo:AddMassBossBuyedTimes(times)
	self:AddUInt32(PLAYER_INT_FIELD_MASS_BOSS_BUYED_TIMES, times)
end

function PlayerInfo:GetMassBossBuyedTimes()
	return self:GetUInt32(PLAYER_INT_FIELD_MASS_BOSS_BUYED_TIMES)
end

function PlayerInfo:SetMassBossCD(cd)
	self:SetUInt32(PLAYER_INT_FIELD_MASS_BOSS_CD, cd)
end

function PlayerInfo:GetMassBossCD()
	return self:GetUInt32(PLAYER_INT_FIELD_MASS_BOSS_CD)
end

function PlayerInfo:CheckAddMassBossTimes()
	--[[if self:getMassBossTimes() >= tb_mass_boss_base[ 1 ].dailytimes then
		return
	end
	
	-- 时间是否到了
	if os.time() >= self:GetMassBossCD() then
		self:AddMassBossTimes()
		local curr = self:getMassBossTimes()
		-- 是否还有下次回复时间
		if curr < tb_mass_boss_base[ 1 ].dailytimes then
			self:SetMassBossCD(os.time() + 60 * tb_mass_boss_base[ 1 ].cd)
		end
	end--]]
end

-- 重置全民boss的次数
function PlayerInfo:ResetMassBossTimes()
	local vipLevel = self:GetVIP()
	self:SetMassBossTimes(tb_mass_boss_base[ 1 ].dailytimes + tb_vip_base[vipLevel].massbossExtraTimes)
	--self:SetMassBossCD(0)
	-- self:SetMassBossBuyedTimes(0)
	
	self:CallScenedDoSomething(APPD_SCENED_RESETDAILY, 0)
end

--组队副本
--设置通关状态
function PlayerInfo:SetGroupInstanceClearFlag(val)
	self:SetBit(PLAYER_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG,val)
end

--获得通关状态
function PlayerInfo:GetGroupInstanceClearFlag(val)
	return self:GetBit(PLAYER_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG,val)
end

--家族首领挑战tickets
function PlayerInfo:SetFactionBossDefenseTickets(value)
	self:SetUInt32(PLAYER_INT_FIELD_FACTION_BOSSDEFENSE_TICKETS,value)
end

function PlayerInfo:GetFactionBossDefenseTickets()
	return self:GetUInt32(PLAYER_INT_FIELD_FACTION_BOSSDEFENSE_TICKETS)
end

function PlayerInfo:SubFactionBossDefenseTickets(value)
	if self:GetFactionBossDefenseTickets() > value then
		self:SubUInt32(PLAYER_INT_FIELD_FACTION_BOSSDEFENSE_TICKETS,value)
	else
		self:SetFactionBossDefenseTickets(0)
	end
end

function PlayerInfo:ResetFactionBossDefenseTickets()
	local default = tb_faction_bossdefense_base[1].challenge_times
	local faction = app.objMgr:getObj(self:GetFactionId())
	if not faction then
		self:SetFactionBossDefenseTickets(default)
		return
	end
	local building_lv = faction:GetBuildingLvByType(FACTION_BUILDING_TYPE_EVENT)
	if building_lv == 0 then
		outFmtDebug("ResetFactionBossDefenseTickets building lv is 0")
		self:SetFactionBossDefenseTickets(default)
		return
	end
	local base_config = tb_faction_bossdefense_base[building_lv]
	if not base_config then
		outFmtDebug("ResetFactionBossDefenseTickets building lv:%d config not exist",building_lv)
		self:SetFactionBossDefenseTickets(default)
		return
	end
	self:SetFactionBossDefenseTickets(base_config.challenge_times)
end

-------无尽远征
--历史挑战层数
function PlayerInfo:SetFactionTowerClearFloor(value)
	self:SetUInt32(PLAYER_INT_FIELD_FACTION_TOWER_CLEAR_FLOOR,value)
end

function PlayerInfo:GetFactionTowerClearFloor()
	return self:GetUInt32(PLAYER_INT_FIELD_FACTION_TOWER_CLEAR_FLOOR)
end

--扫荡flag
function PlayerInfo:SetFactionTowerSweepFlag()
	self:SetBit(PLAYER_INT_FIELD_FACTION_TOWER_FLAG,0)
end

function PlayerInfo:UnSetFactionTowerSweepFlag()
	self:UnSetBit(PLAYER_INT_FIELD_FACTION_TOWER_FLAG,0)
end

function PlayerInfo:GetFactionTowerSweepFlag()
	return self:GetBit(PLAYER_INT_FIELD_FACTION_TOWER_FLAG,0)
end

--奖励领取flag
function PlayerInfo:SetFactionTowerChestFlag(index)
	if index > 0 and index < 32 then
		self:SetBit(PLAYER_INT_FIELD_FACTION_TOWER_FLAG,index)
	end
end

function PlayerInfo:UnSetFactionTowerChestFlag(index)
	if index > 0 and index < 32 then
		self:UnSetBit(PLAYER_INT_FIELD_FACTION_TOWER_FLAG,index)
	end
end

function PlayerInfo:GetFactionTowerChestFlag(index)
	if index > 0 and index < 32 then
		return self:GetBit(PLAYER_INT_FIELD_FACTION_TOWER_FLAG,index)
	end
	
	return false
end

function PlayerInfo:DailyResetTowerFlag()
	self:SetUInt32(PLAYER_INT_FIELD_FACTION_TOWER_FLAG,0)
end


------------------------------------------

function PlayerInfo:GetRenameCost()
	local times = self:GetUInt32(PLAYER_INT_FIELD_RENAME_TIMES) + 1
	local indx = #tb_rename_info
	for i = 1, #tb_rename_info do
		local range = tb_rename_info[ i ].range
		if times >= range[ 1 ] and (times <= range[ 2 ] or range[ 2 ] == -1) then
			indx = i
			break
		end
	end
	return tb_rename_info[indx].costs
end

function PlayerInfo:AddRenameTimes()
	self:AddUInt32(PLAYER_INT_FIELD_RENAME_TIMES, 1)
end


---------------------家族技能等级---------------------
--已学习等级
function PlayerInfo:GetFactionSkillLearnLv(id)
	return self:GetUInt16(PLAYER_INT_FIELD_FACTION_SKILL_LV_START + id - 1,0)
end

function PlayerInfo:SetFactionSkillLearnLv(id,val)
	self:SetUInt16(PLAYER_INT_FIELD_FACTION_SKILL_LV_START + id - 1, 0, val)
end

--当前生效等级
function PlayerInfo:GetFactionSkillNowLv(id)
	return self:GetUInt16(PLAYER_INT_FIELD_FACTION_SKILL_LV_START + id - 1,1)
end

function PlayerInfo:SetFactionSkillNowLv(id,val)
	self:SetUInt16(PLAYER_INT_FIELD_FACTION_SKILL_LV_START + id - 1, 1, val)
end

--更新家族技能等级变化
function PlayerInfo:UpdateFactionSkill()
	local faction = app.objMgr:getObj(self:GetFactionId())
	if faction == nil then
		self:OnFactionSkillBuildingLvChange(0)
		return
	end
	local building_lv = faction:GetBuildingLvByType(FACTION_BUILDING_TYPE_SKILL)
	self:OnFactionSkillBuildingLvChange(building_lv)
end

--建筑等级改变 (建筑升级 成员加入 退出家族)
--更新成员技能生效等级(building_lv)
function PlayerInfo:OnFactionSkillBuildingLvChange(building_lv)
	local level_limit = 0
	if building_lv ~= 0 then
		level_limit = tb_faction_skill_building[building_lv].level_limit
	end
	for id,config in pairs(tb_faction_skill_base) do
		local learn_lv = self:GetFactionSkillLearnLv(id)
		if config.unlock_level > building_lv then
			self:SetFactionSkillNowLv(id,0)
			self:updatePassive(config.skill_id,0)
			self:RecalcAttrAndBattlePoint()
			--outFmtDebug("OnFactionSkillBuildingLvChange 1 skill %d lv %d",config.skill_id,0)
		else
			if learn_lv > level_limit then
				self:SetFactionSkillNowLv(id,level_limit)
				self:updatePassive(config.skill_id,level_limit)
				self:RecalcAttrAndBattlePoint()
				--outFmtDebug("OnFactionSkillBuildingLvChange 2 skill %d lv %d",config.skill_id,level_limit)
			else
				self:SetFactionSkillNowLv(id,learn_lv)
				self:updatePassive(config.skill_id,learn_lv)
				self:RecalcAttrAndBattlePoint()
				--outFmtDebug("OnFactionSkillBuildingLvChange 3 skill %d lv %d",config.skill_id,learn_lv)
			end
		end
	end
end
------------------------------------------

--复仇次数
function PlayerInfo:GetRevengeTimes()
	return self:GetUInt32(PLAYER_INT_FIELD_REVENGE_TIMES)
end

function PlayerInfo:SetRevengeTimes(val)
	self:SetUInt32(PLAYER_INT_FIELD_REVENGE_TIMES, val)
end

--复仇次数
function PlayerInfo:GetRevengeBuyTimes()
	return self:GetUInt32(PLAYER_INT_FIELD_REVENGE_BUY_TIMES)
end

function PlayerInfo:SetRevengeBuyTimes(val)
	self:SetUInt32(PLAYER_INT_FIELD_REVENGE_BUY_TIMES, val)
end

--每日重置次数
function PlayerInfo:DailyResetRevengeTimes()
	self:SetRevengeTimes(tb_enemy_revenge_base[1].daily_revenge_times)
	self:SetRevengeBuyTimes(0)
end


--购买次数
function PlayerInfo:BuyRevengeTimes(count)
	if count <= 0 then
		return
	end
	
	local buy_count = self:GetRevengeBuyTimes()
	local total_cost_table = {}
	for i = buy_count + 1, buy_count + count do
		local config = tb_enemy_revenge_buy[i]
		if not config then
			config = tb_enemy_revenge_buy[#tb_enemy_revenge_buy]
		end
		local cost = config.cost
		for _,v in pairs(cost) do
			if total_cost_table[v[1]] then
				total_cost_table[v[1]] = total_cost_table[v[1]] + v[2]
			else
				total_cost_table[v[1]] = v[2]
			end
		end
		
	end
	
	local total_cost = {}
	for k,v in pairs(total_cost_table) do
		table.insert(total_cost,{k,v})
	end
	
	if not self:hasAllItems(total_cost) then
		return
	end
	
	if self:useAllItems(MONEY_CHANGE_TYPE_STORE_BUY, nil, total_cost) then
		self:SetRevengeTimes(self:GetRevengeTimes() + count)
		self:SetRevengeBuyTimes(self:GetRevengeBuyTimes() + count)
	end
end

--复仇
function PlayerInfo:TeleportToRevenge(guid)
	--检测复仇对象是否有效
	local socialMgr = self:getSocialMgr()
	if socialMgr:getEnemyIndex(guid) == -1 then
		self:CallOptResult(OPERTE_TYPE_SOCIAL,OPERTE_TYPE_SOCIAL_NOT_ENEMY)
		return
	end
	--检测是否在线
	local player = app.objMgr:getObj(guid)
	if not player or not player:isLogined() then
		self:CallOptResult(OPERTE_TYPE_SOCIAL,OPERTE_TYPE_SOCIAL_ENEMY_OFFLINE)
		return
	end
	
	--检测是否可传送过去
	local map_id = player:GetMapId()
	local lineNo = player:GetUInt32(PLAYER_FIELD_LINE_NO)
	local config = tb_map[map_id]
	if config and config.type == MAP_TYPE_FIELD then
		local times = self:GetRevengeTimes()
		if times > 0 then
			self:SetRevengeTimes(times - 1)
			local x, y = player:GetPosition()
			--call_appd_teleport(self:GetScenedFD(),self:GetGuid(),x,y,map_id)
			
			local params = ''..map_id..'|'..x..'|'..y..'|'..lineNo
			self:CallScenedDoSomething(APPD_SCENED_TELEPORT, 0,params)
		else
			--次数不足
				self:CallOptResult(OPERTE_TYPE_SOCIAL,OPERTE_TYPE_SOCIAL_REVENGE_TIMES_NOT_ENOUGH)
			return
		end
		
		
	else
		self:CallOptResult(OPERTE_TYPE_SOCIAL,OPERTE_TYPE_SOCIAL_ENEMY_NOT_IN_FIELD)
		return
	end
	
end

------------------------------------------

--vip礼包购买状态
function PlayerInfo:GetVipGiftFlag(id)
	return self:GetBit(PLAYER_INT_FIELD_VIPGIFT_FLAG,id)
end

function PlayerInfo:SetVipGiftFlag(id)
	self:SetBit(PLAYER_INT_FIELD_VIPGIFT_FLAG, id)
end

--VIP礼包
function PlayerInfo:BuyVipGift(id)
	local config = tb_vip_base[id]
	if not config then
		return
	end
	if self:GetVipGiftFlag(id) then
		self:CallOptResult(OPERTE_TYPE_NPCBUY,NPC_BUY_SELL_OUT)
		return
	end
	
	if self:GetVIP() < id then
		return
	end
	
	
	if not self:hasAllItems(config.cost) then
		self:CallOptResult(OPERTE_TYPE_NPCBUY,NPC_BUY_MONEY_NO_ENOUGH)
		return
	end
	
	if self:useAllItems(MONEY_CHANGE_TYPE_STORE_BUY, nil, config.cost) then
		self:AppdAddItems(config.gift, MONEY_CHANGE_TYPE_STORE_BUY,LOG_ITEM_OPER_TYPE_SHOP_BUY)
		
		self:SetVipGiftFlag(id)
		
	end
	
end

------------------------------------------
--玩家活动激活时数据清理
function PlayerInfo:ActiveActivity(act_id)
	local config = tb_activity_time[act_id]
	
	local spellMgr = self:getSpellMgr()
	local category = config.category
	
	local prev = self:GetActivityDataActId(category)
	if prev == act_id then
		return
	end
	
	outFmtDebug("#########player ActiveActivity id = %d", act_id)
	
	self:SetActivityDataActId(category,act_id)
	for offset = 0,2 do
		self:SetActivityDataUInt32(act_id,offset,0)
	end
	
	spellMgr:SetStr(SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_START + category * MAX_PLAYERACTIVITTYDATASTRING_COUNT + PLAYER_ACTIVITTY_DATA_STRING_0,"")
	
end

------------------------------玩家活动uint32数据
function PlayerInfo:SetActivityDataUInt32(act_id,offset,value)
	local config = tb_activity_time[act_id]
	
	local spellMgr = self:getSpellMgr()
	local category = config.category
	if offset < 0  or offset > 2 then
		outFmtError("SetActivityDataUInt32 error offset %d",offset)
		return
	end
	spellMgr:SetUInt32(SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + category * MAX_PLAYERACTIVITTYDATAINT_COUNT + offset + 1,value)
end

function PlayerInfo:GetActivityDataUInt32(act_id,offset)
	local config = tb_activity_time[act_id]
	
	local spellMgr = self:getSpellMgr()
	local category = config.category
	if offset < 0  or offset > 2 then
		outFmtError("GetActivityDataUInt32 error offset %d",offset)
		return
	end
	return spellMgr:GetUInt32(SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + category * MAX_PLAYERACTIVITTYDATAINT_COUNT + offset + 1)
end

function PlayerInfo:GetActivityDataActId(category)
	local spellMgr = self:getSpellMgr()
	return spellMgr:GetUInt32(SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + category * MAX_PLAYERACTIVITTYDATAINT_COUNT )
end

function PlayerInfo:SetActivityDataActId(category,val)
	local spellMgr = self:getSpellMgr()
	spellMgr:SetUInt32(SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + category * MAX_PLAYERACTIVITTYDATAINT_COUNT ,val)
end


------------------------------玩家活动bit数据
function PlayerInfo:SetActivityDataBit(act_id,offset,bit_offset)
	local config = tb_activity_time[act_id]
	
	local spellMgr = self:getSpellMgr()
	local category = config.category
	if offset < 0  or offset > 2 then
		outFmtError("SetActivityDataBit error offset %d",offset)
		return
	end
	if bit_offset < 0  or bit_offset > 31 then
		outFmtError("SetActivityDataBit error bit_offset %d",offset)
		return
	end
	
	spellMgr:SetBit(SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + category * MAX_PLAYERACTIVITTYDATAINT_COUNT + offset + 1,bit_offset)
end

function PlayerInfo:UnSetActivityDataBit(act_id,offset,bit_offset)
	local config = tb_activity_time[act_id]
	
	local spellMgr = self:getSpellMgr()
	local category = config.category
	if offset < 0  or offset > 2 then
		outFmtError("UnSetActivityDataBit error offset %d",offset)
		return
	end
	if bit_offset < 0  or bit_offset > 31 then
		outFmtError("UnSetActivityDataBit error bit_offset %d",offset)
		return
	end
	
	spellMgr:UnSetBit(SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + category * MAX_PLAYERACTIVITTYDATAINT_COUNT + offset + 1,bit_offset)
end

function PlayerInfo:GetActivityDataBit(act_id,offset,bit_offset)
	local config = tb_activity_time[act_id]
	
	local spellMgr = self:getSpellMgr()
	local category = config.category
	if offset < 0  or offset > 2 then
		outFmtError("GetActivityDataBit error offset %d",offset)
		return
	end
	return spellMgr:GetBit(SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + category * MAX_PLAYERACTIVITTYDATAINT_COUNT + offset + 1,bit_offset)
end


------------------------------------------

-------------------应用服经验------------
function PlayerInfo:AddAppdExp(val)
	if val <= 0 then
		return
	end
	
	self:AddDouble(PLAYER_EXPAND_INT_XP_ADDED, val)
end

------------------------------------------
--七日大礼进度更新
function PlayerInfo:LoginUpdateSevenDayProcess()
	local questMgr = self:getQuestMgr()
	if questMgr:GetSevenDayProcess() < 7 then
		questMgr:AddSevenDayProcess(1)
		outFmtDebug("LoginUpdateSevenDayProcess login days %d",questMgr:GetSevenDayProcess())
	end
end

--每日充值标识重置
function PlayerInfo:ClearWelfareSevenDayRechargeTodayFlag()
	local questMgr = self:getQuestMgr()
	questMgr:UnSetWelfareSevenDayRechargeTodayFlag()
end

------------------------------------------
function PlayerInfo:getLastPassedSectionId()
	return self:GetUInt32(PLAYER_INT_FIELD_TRIAL_FINISHED_SECTIONID)
end

function PlayerInfo:getRiskSuitScore()
	return self:GetUInt32(PLAYER_INT_FILED_LEAVE_RISK_SUIT_SCORE)
end

function PlayerInfo:setRiskSuitScore(val)
	self:SetUInt32(PLAYER_INT_FILED_LEAVE_RISK_SUIT_SCORE, val)
end


function PlayerInfo:onPickedOfflineRiskReward(times)
	-- 系统未激活
	--[[
	if (not self:GetOpenMenuFlag(MODULE_WORLD_RISK, MODULE_WORLD_RISK_MAIN)) then
		return
	end
	--]]
	
	if (not self:GetOpenMenuFlag(MODULE_ACTIVE, MODULE_ACTIVE_ALL)) then
		return
	end
	if times < tb_offline_exp_base[ 1 ].offlineMins then
		return
	end
	
	local level = self:GetLevel()
	local rewardDict, ccnt, sell, exp, minutes = self:onCalRiskReward(times)
	if rewardDict then
		local allxp = self:GetExp() + exp
		local topLevel = level
		for i = level, 1000 do
			if not tb_char_level[i+1] or allxp < tb_char_level[ i ].next_exp then
				break
			end
			allxp = allxp - tb_char_level[ i ].next_exp
			topLevel = topLevel + 1
		end
		self:AppdAddItems(rewardDict, MONEY_CHANGE_OFFLINE, LOG_ITEM_OPER_TYPE_OFFLINE, nil, nil, nil, 3)
--		local list = Change_List_To_Item_Reward_Info(rewardDict, sell, true)
		local list = {}
		self:call_offline_reward_result (ccnt * 65536 + sell, minutes, exp, level, topLevel, list)
	end
end

-- 领取世界冒险奖励
function PlayerInfo:onPickRiskReward()

	--[[-- 系统未激活
	if (not self:GetOpenMenuFlag(MODULE_WORLD_RISK, MODULE_WORLD_RISK_MAIN)) then
		return
	end
	
	local rewardDict, sell = self:onCalRiskReward(1)
	if rewardDict then
		self:AppdAddItems(rewardDict, MONEY_CHANGE_OFFLINE, LOG_ITEM_OPER_TYPE_OFFLINE, nil, nil, nil, 3)
		if sell > 0 then
			self:CallOptResult(OPRATE_TYPE_BAG, BAG_RESULT_BAG_FULL_AUTO_SELL, sell)
		end
	end--]]
end


function PlayerInfo:onCalRiskReward(times)
	-- 最大次数
	local limit = self:GetRestOfflineMinutes()
	if times > limit then
		times = limit
	end
	
	-- 扣时间
	self:ModifyRestOfflineMinutes(-times)
	
	local rate = 100
	local config = tb_offline_exp_data[self:GetLevel()]	
	local dict = {}
	local vip = self:GetVIP()
	local vipFactor = tb_vip_base[vip].offlineExpRate
	local exp = math.floor(config. expReward[ 2 ] * times * rate / 100 * (1 + vipFactor / 100))
	local factor = math.floor(self:GetForce() * 100 / config.standardForce)
	
	local a = tb_offline_exp_base[ 1 ].factorRange[ 1 ]
	local b = tb_offline_exp_base[ 1 ].factorRange[ 2 ]
	factor = math.max(a, math.min(b, factor))
	exp = math.floor(exp * factor / 100)
	
	dict[config. expReward[ 1 ]] = exp
	
	local score = math.floor(config.suitScore * times * rate / 100 * (1 + vipFactor / 100))
	local prevScore = self:getRiskSuitScore()
	score = score + prevScore
	
	-- 随机装备
	-- 先计算装备积分
	local suitCount = math.floor(score / config.suitScoreChange)
	self:setRiskSuitScore(score - suitCount * config.suitScoreChange)
	
	local dropid = config.dropid
	for i = 1, suitCount do
		DoRandomDrop(dropid, dict)
	end
	
	local ccnt = 0
	local sell = 0
	local itemMgr = self:getItemMgr()
	local empty_count = itemMgr:getEmptyCount(BAG_TYPE_EQUIP_BAG)	--取出剩余位置个数
	local rewardDict = {}
	for entry, count in pairs(dict) do
		if tb_item_template[entry].pos == 0 then
			table.insert(rewardDict, {entry, count})
		end
	end
	
	for entry, count in pairs(dict) do
		if tb_item_template[entry].pos > 0 then
			empty_count = empty_count - count
			ccnt = ccnt + count
			for k = 1, count do
				table.insert(rewardDict, {entry, 1})
			end
		end
	end
	
	if empty_count < 0 then
		sell = -empty_count
	end
	
	return rewardDict, ccnt, sell, exp, times
end

function PlayerInfo:onUpdatePlayerQuest(type,params)
	params = params or {}
	local questMgr = self:getQuestMgr()
	questMgr:OnUpdate(type, params)
end

function PlayerInfo:UpdateFactionBangZhuInfo()
	local faction = app.objMgr:getObj(self:GetFactionId())
	if faction then
		if faction:GetBangZhuGuid() == self:GetGuid() then
			faction:SetBangZhuName(self:GetName())
			faction:SetBangZhuInfo(self)
			
		end
	end
end


------------------------------------------
--摇钱树
--次数
function PlayerInfo:GetMoneytreeCount()
	return self:GetUInt32(PLAYER_APPD_INT_FIELD_MONEYTREE_COUNT)
end

function PlayerInfo:SetMoneytreeCount(value)
	self:SetUInt32(PLAYER_APPD_INT_FIELD_MONEYTREE_COUNT,value)
end

function PlayerInfo:AddMoneytreeCount(value)
	self:AddUInt32(PLAYER_APPD_INT_FIELD_MONEYTREE_COUNT,value)
end

--礼包状态
function PlayerInfo:GetMoneytreeGiftFlag(index)
	return self:GetBit(PLAYER_APPD_INT_FIELD_MONEYTREE_GIFT_FLAG,index)
end

function PlayerInfo:SetMoneytreeGiftFlag(index)
	self:SetBit(PLAYER_APPD_INT_FIELD_MONEYTREE_GIFT_FLAG,index)
end

function PlayerInfo:ClearMoneytreeGiftFlag()
	self:SetUInt32(PLAYER_APPD_INT_FIELD_MONEYTREE_GIFT_FLAG,0)
end

--重置摇钱树
function PlayerInfo:DailyResetMoneytree()
	self:ClearMoneytreeGiftFlag()
	self:SetMoneytreeCount(0)
end

--使用摇钱树
function PlayerInfo:UseMoneytree()
	
	local count = self:GetMoneytreeCount()
	local base_config = tb_moneytree_base[count + 1]
	local lv_config = tb_moneytree_lv[self:GetLevel()]
	local crit_config = tb_moneytree_crit[1]
	
	if not base_config or not lv_config or not crit_config then
		outFmtDebug("UseMoneytree config error")
		return
	end
	
	--上限检测 vip相关
	--todo
	if count >= tb_vip_base[self:GetVIP()].treeTimes then
		return
	end
	
	if self:useAllItems(MONEY_CHANGE_MONEYTREE_USE, nil, base_config.cost) then
		local random = randInt(1, 10000)
		local total_chance = 0
		local result = 0
		for index,chance in ipairs(crit_config.chance) do
			if random <= total_chance + chance then
				result = index
				break
			else
				total_chance = total_chance + chance
			end
		end
		
		local rate = crit_config.rate[result] / 10000
		if not rate then
			outFmtDebug("UseMoneytree crit_config chance error!! result not exist")
			return
		end
		
		local rewards = {{lv_config.reward[1],math.floor(lv_config.reward[2] * rate * base_config.rate/10000)}}
		
		self:AddMoneytreeCount(1)
		self:AppdAddItems(rewards,MONEY_CHANGE_MONEYTREE_USE)
		if rate == 1 then
			self:CallOptResult(OPRATE_TYPE_MONEYTREE,MONEYTREE_TYPE_NORMAL,{lv_config.reward[2] * rate,rate})
		else
			self:CallOptResult(OPRATE_TYPE_MONEYTREE,MONEYTREE_TYPE_CRIT,{lv_config.reward[2] * rate,rate})
		end
		
		self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_MONEYTREE_TIMES)
	end
end

function PlayerInfo:GetMoneytreeGift(id)
	local config = tb_moneytree_gift[id]
	
	if not config then
		outFmtDebug("GetMoneytreeGift config error  id:%d",id)
		return
	end
	
	local count = self:GetMoneytreeCount()
	
	if count < config.count then
		outFmtDebug("GetMoneytreeGift count not enough %d < %d",count , config.count)
		return
	end
	
	if self:GetMoneytreeGiftFlag(id - 1) then
		outFmtDebug("GetMoneytreeGift gift already get id:%d",id )
		return
	end
	
	self:SetMoneytreeGiftFlag(id - 1)
	
	local reward = {tb_moneytree_lv[self:GetLevel()]["gift_"..id]}
	self:AppdAddItems(reward,nil,LOG_ITEM_OPER_TYPE_MONEYTREE_GIFT)
	
end


------------------------------------------


--更新背包大小
function PlayerInfo:UpdateBagSize(vipLevel)
	local config = tb_vip_base[vipLevel].bag_size
	
	local itemMgr = self:getItemMgr()
	for _,info in pairs(config) do
		itemMgr:setBagSize(info[1],info[2])
	end
end

--清除关于上次所处场景的信息
function PlayerInfo:ResetLastInstanceInfo()
	self:SetUInt32(PLAYER_INT_FIELD_LAST_INSTANCE_TYPE,0)
	self:SetUInt32(PLAYER_INT_FIELD_LAST_INSTANCE_PARAM,0)
end

function PlayerInfo:SetWorldRiskLastId(val)
	self:SetUInt32(PLAYER_INT_FIELD_WORLD_RISK_LAST_ID,val)
end

--运镖状态 p对象同步u对象
function PlayerInfo:SetEscortState(value)
	self:SetUInt32(PLAYER_FIELD_ANGER,value)
end

function PlayerInfo:GetEscortState()
	return self:GetUInt32(PLAYER_FIELD_ANGER)
end

--劫镖次数
function PlayerInfo:GetEscortRobCount()
	return self:GetUInt32(PLAYER_INT_FIELD_ESCORT_ROB_COUNT)
end

function PlayerInfo:SetEscortRobCount(value)
	self:SetUInt32(PLAYER_INT_FIELD_ESCORT_ROB_COUNT,value)
end

function PlayerInfo:DailyResetEscortRobCount()
	self:SetEscortRobCount(0)
	self:SetUInt32(PLAYER_INT_FIELD_ADVENTURE_ROBOT_KILL_COUNT,0)
end

function PlayerInfo:CheckEscortTimeOut()
	local questMgr = self:getQuestMgr()
	local itemMgr = self:getItemMgr()
	
	if not questMgr or not itemMgr then
		return
	end
	local finish_time =  questMgr:GetQuestEscortFinishTime() 
	
	if finish_time > 0 and os.time() >= finish_time then
		questMgr:SetQuestEscortFinishTime(0)
		questMgr:OnRemoveQuest(QUEST_FIELD_ESCORT_QUEST_START)
		
		local config = tb_escort_base[1]
		local count = self:CountItem(config.quest_item_id)
		itemMgr:delItem(config.quest_item_id,count)
		
		self:SetEscortState(QUEST_ESCORT_STATE_NONE)
		
	end
end


------------------------------------------------------------------------------------------
--境界突破

function PlayerInfo:GetRealmbreakLevel()
	return self:GetUInt32(PLAYER_INT_FIELD_REALMBREAK_LEVEL)
end

function PlayerInfo:SetRealmbreakLevel(val)
	self:SetUInt32(PLAYER_INT_FIELD_REALMBREAK_LEVEL,val)
end

function PlayerInfo:GetRealmbreakExp()
	return self:GetUInt32(PLAYER_INT_FIELD_REALMBREAK_EXP)
end

function PlayerInfo:SetRealmbreakExp(val)
	self:SetUInt32(PLAYER_INT_FIELD_REALMBREAK_EXP,val)
end

function PlayerInfo:AddRealmbreakExp(val)
	local level = self:GetRealmbreakLevel()
	local now_exp = self:GetRealmbreakExp()
	local uplevel = 0
	
	local config = tb_realmbreak_base[level]
	while (config and now_exp + val >= config.exp and tb_realmbreak_base[level + uplevel + 1] and self:GetLevel() >= tb_realmbreak_base[level + uplevel+ 1].level) do
		uplevel = uplevel + 1
		config = tb_realmbreak_base[level + uplevel]
	end
	
	if uplevel > 0 then
		self:SetRealmbreakLevel(level + uplevel)
		--重算属性
		self:RecalcAttrAndBattlePoint()
		
		--其他处理
		self:OnRealmbreakLevUp(level,level + uplevel)
		
		self:onUpdatePlayerQuest( QUEST_TARGET_TYPE_REALMBREAK_LEVEL,{})
	end
	
	self:AddUInt32(PLAYER_INT_FIELD_REALMBREAK_EXP,val)
end

function PlayerInfo:OnRealmbreakLevUp(from,to)
	for level = from + 1, to do
		local config = tb_realmbreak_base[level]
		if not config then
			return
		end
		
		local unlocks_config = tb_char_skill[self:GetGender()].realmbreak_unlocks
		for _, skillInfo in ipairs(unlocks_config) do
			
			if level == skillInfo[1] then
				self:activeBaseSpell(skillInfo[2], SPELL_ACTIVE_BY_LEVEL)
			end
		end
		
		self:UnlockTalismanSlotByRealmbreakLv(level)
	end
end
function PlayerInfo:calculRealmbreakAttr(attrs)
	outFmtDebug("calculRealmbreakAttr")
	
	local player_level = self:GetLevel()
	local realmbreak_level = self:GetRealmbreakLevel()
	local config = tb_realmbreak_base[realmbreak_level]
	while config do
		if player_level >= config.level then
			outFmtDebug("calculRealmbreakAttr level %d", realmbreak_level)
			mergeAttrs(attrs,config.props)
			
			break
		else
			realmbreak_level = realmbreak_level - 1
			config = tb_realmbreak_base[realmbreak_level]
		end
	end
	local level = math.max(realmbreak_level, 0)
	attrs[EQUIP_ATTR_DAO] = level
	local force = tb_realmbreak_base[level].force
	self:SetRealmbreakForce(force)
	
	
	return force
end

function PlayerInfo:GetRealmbreakDailyQuestCount()
	return self:GetUInt16(PLAYER_INT_FIELD_REALMBREAK_DAILYQUEST_STATE,0)
end

function PlayerInfo:SetRealmbreakDailyQuestCount(val)
	self:SetUInt16(PLAYER_INT_FIELD_REALMBREAK_DAILYQUEST_STATE,0,val)
end

function PlayerInfo:AddRealmbreakDailyQuestCount(val)
	self:AddUInt16(PLAYER_INT_FIELD_REALMBREAK_DAILYQUEST_STATE,0,val)
end

function PlayerInfo:GetRealmbreakDailyQuestFlag()
	return self:GetUInt16(PLAYER_INT_FIELD_REALMBREAK_DAILYQUEST_STATE,1)
end

function PlayerInfo:SetRealmbreakDailyQuestFlag(val)
	self:SetUInt16(PLAYER_INT_FIELD_REALMBREAK_DAILYQUEST_STATE,1,val)
end

function PlayerInfo:DailyResetRealmbreakDailyQuestState()
	self:SetRealmbreakDailyQuestCount(0)
	self:SetRealmbreakDailyQuestFlag(0)
end

--领取每日任务完成奖励
function PlayerInfo:PickRealmbreakDailyReward()
	local config = tb_realmbreak_dailyquest_base[1]
	
	if self:GetLevel() < config.daily_quest_level_limit then
		outFmtDebug("PickRealmbreakDailyReward player level not enough" )
		return
	end
	
	if self:GetRealmbreakDailyQuestFlag() == 1 then
		outFmtDebug("PickRealmbreakDailyReward reward already picked" )
		return
	end
	
	if self:GetRealmbreakDailyQuestCount() < config.daily_quest_count then
		outFmtDebug("PickRealmbreakDailyReward daily quest not finish" )
		return
	end
	
	self:AppdAddItems(config.daily_quest_reward, MONEY_CHANGE_REALMBREAK,LOG_ITEM_OPER_TYPE_REALMBREAK)
	self:SetRealmbreakDailyQuestFlag(1)
end

function PlayerInfo:OnPickRealmbreakQuest(indx)
	local questMgr = self:getQuestMgr()
	questMgr:OnPickRealmbreakQuest(indx)
end


-----------------------------------------------------------------------------------------
--客户端操作CD

function PlayerInfo:SetOperateCD (val)
	self:SetUInt32(PLAYER_INT_FIELD_OPERATE_CD,val)
end

function PlayerInfo:GetOperateCD()
	return self:GetUInt32(PLAYER_INT_FIELD_OPERATE_CD)
end

--应用服协议具有CD
app_operate_need_cd = {
	--[CMSG_BAG_EXCHANGE_POS] = 0,
	[CMSG_BAG_ITEM_USER] = 0,
	[CMSG_BAG_ITEM_SELL] = 0,
	[CMSG_BAG_ITEM_SORT] = 0,
	--[CMSG_FINISH_NOW_GUIDE] = 0,
	--[CMSG_GET_CULTIVATION_INFO] = 0,
	--[CMSG_GET_CULTIVATION_RIVALS_INFO] = 0,
	--[CMSG_GET_CULTIVATION_REWARD] = 0,
	--[CMSG_REFRESH_CULTIVATION_RIVALS] = 0,
	--[CMSG_PLUNDER_CULTIVATION_RIVAL] = 0,
	--[CMSG_REVENGE_CULTIVATION_RIVAL] = 0,
--		[CMSG_BUY_CULTIVATION_LEFT_PLUNDER_COUNT] = 0,
	[CMSG_GET_LOGIN_ACTIVITY_REWARD] = 0,
	[CMSG_SMELTING_EQUIP] = 0,
	[CMSG_SOCIAL_BUY_REVENGE_TIMES] = 0,
	[CMSG_SOCIAL_REMOVE_ENEMY] = 0,
	[CMSG_GET_PLAYER_OVERVIEW] = 0,
	[CMSG_SEND_FACTION_INVITE] = 0,
	[CMSG_BUY_VIPGIFT] = 0,
	[CMSG_ACTIVITY_OPT_BUY_DAILYGIFT] = 0,
	[CMSG_ACTIVITY_OPT_GET_RANK_PROCESS_REWARD] = 0,
	[CMSG_ACTIVITY_OPT_GET_RANK_LIST] = 0,
	[CMSG_ACTIVITY_OPT_BUY_LIMITGIFT] = 0,
	[CMSG_WELFARE_GET_RECHARGE_REWARD] = 0,
	[CMSG_WELFARE_GET_CONSUME_REWARD] = 0,
	[CMSG_WELFARE_GET_SEVENDAY_REWARD] = 0,
	--[CMSG_TALISMAN_ACTIVE] = 0,
	[CMSG_TALISMAN_LVUP] = 0,
	--[CMSG_WINGS_ACTIVE] = 0,
	--[CMSG_WINGS_BLESS] = 0,
	[CMSG_WINGS_RANKUP] = 0,
	[CMSG_WINGS_STRENGTH] = 0,
	[CMSG_EQUIPDEVELOP_OPERATE] = 0,
	[CMSG_UNLOCK_TITLE] = 0,
	[CMSG_USE_MONEYTREE] = 0,
	[CMSG_GET_MONEYTREE_GIFT] = 0,
	[CMSG_SET_WORLD_RISK_LAST_ID] = 0,
	[CMSG_RAISE_BASE_SPELL_ALL] = 0,
	[CMSG_PICK_QUEST_ADVENTURE] = 0,
	[CMSG_RAISE_ADVENTURESPELL] = 0,
	--[CMSG_PICK_QUEST_REALMBREAK] = 0,
	[CMSG_PICK_REALMBREAK_DAILY_REWARD] = 0,
	[CMSG_PICK_STAGE_INSTANCE_BONUS] = 0,
	[CMSG_PICK_FACTION_MATCH_CHAMPION_DAILY_REWARD] = 0,
	[CMSG_QUERY_FACTION_MATCH_INFO] = 0,
	[CMSG_PICK_RES_INSTANCE_FIRST_REWARD] = 0,
	[CMSG_RANK_LIST_QUERY] = 0,
	[CMSG_QUERY_PLAYER_INFO] = 0,--查询玩家信息
	[CMSG_CHAT_WHISPER] = 0,--私聊
	[MSG_SYNC_MSTIME_APP] = 0,
	[CMSG_MALL_BUY] = 0,
	[CMSG_CREATE_FACTION] = 0,
	[CMSG_FACTION_JOIN] = 0,
	[CMSG_RAISE_BASE_SPELL] = 0,
	[CMSG_UPGRADE_ANGER_SPELL] = 0,
	--[CMSG_RAISE_MOUNT] = 0,
	--[CMSG_UPGRADE_MOUNT] = 0,
	[CMSG_UPGRADE_MOUNT_ONE_STEP] = 0,
	[CMSG_ILLUSION_MOUNT_ACTIVE] = 0,
	[CMSG_ILLUSION_MOUNT] = 0,
	[CMSG_SWEEP_VIP_INSTANCE] = 0,
	[CMSG_HANG_UP] = 0,				-- /*进行挂机*/	
	[CMSG_HANG_UP_SETTING] = 0,		-- /*进行挂机设置*/
	[CMSG_SWEEP_TRIAL_INSTANCE] = 0,
	[CMSG_RESET_TRIAL_INSTANCE] = 0,
	[CMSG_SOCIAL_ADD_FRIEND] = 0,
	[CMSG_SOCIAL_SUREADD_FRIEND] = 0,
	[CMSG_SOCIAL_GIFT_FRIEND] = 0,
	[CMSG_SOCIAL_RECOMMEND_FRIEND] = 0,
	[CMSG_SOCIAL_REVENGE_ENEMY] = 0,
	[CMSG_SOCIAL_DEL_FRIEND] = 0,
	[CMSG_SOCIAL_CLEAR_APPLY] = 0,
	[CMSG_SOCIAL_ADD_FRIEND_BYNAME] = 0,
	-- [CMSG_CHAT_BY_CHANNEL] = 0,
	[CMSG_MSG_DECLINE] = 0,
	[CMSG_BLOCK_CHAT] = 0, 	--屏蔽某人
	[CMSG_FACTION_GETLIST] = 0,
	[CMSG_FACTION_MANAGER] = 0,
	[CMSG_FACTION_MEMBER_OPERATE] = 0,
	[CMSG_FACTION_FAST_JOIN] = 0,
	-----------------------------
	[CMSG_READ_MAIL] = 0,
	[CMSG_PICK_MAIL] = 0,
	[CMSG_PICK_MAIL_ONE_STEP] = 0,
	[CMSG_REMOVE_MAIL_ONE_STEP] = 0,
	[CMSG_CANCEL_BLOCK_CHAT] = 0,	
	-----------------------------
	[CMSG_RANK_ADD_LIKE] = 0,
	-------------------------------
	[CMSG_RES_INSTANCE_SWEEP] = 0,
	--------------------------
	[CMSG_GET_ACTIVITY_REWARD] = 0,
	--------------------------
	[CMSG_GET_ACHIEVE_REWARD] = 0,
	[CMSG_GET_ACHIEVE_ALL_REWARD] = 0,
	[CMSG_SET_TITLE] = 0,
	[CMSG_INIT_TITLE] = 0,
	[CMSG_WELFARE_SHOUCHONG_REWARD] = 0,
	[CMSG_WELFARE_CHECKIN] = 0,
	[CMSG_WELFARE_CHECKIN_ALL] = 0,
	[CMSG_WELFARE_CHECKIN_GETBACK] = 0,
	[CMSG_WELFARE_LEVEL] = 0,
	[CMSG_WELFARE_ACTIVE_GETBACK] = 0,
	[CMSG_WELFARE_GETALLLIST_GETBACK] = 0,
	[CMSG_WELFARE_GETALL_GETBACK] = 0,
	[CMSG_PICK_QUEST_REWARD] = 0,
	[CMSG_USE_VIRTUAL_ITEM] = 0,
	[CMSG_PICK_QUEST_CHAPTER_REWARD] = 0,
	[MSG_KUAFU_3V3_CANCEL_MATCH] = 0,
	[CMSG_KUAFU_XIANFU_MATCH] = 0,
	[CMSG_BUY_XIANFU_ITEM] = 0,
	[CMSG_DOUJIANTAI_BUYTIME] = 0,
	[CMSG_DOUJIANTAI_CLEARCD] = 0,
	[CMSG_DOUJIANTAI_FIRST_REWARD] = 0,
	
	[MSG_DOUJIANTAI_GET_ENEMYS_INFO] = 0,
	[CMSG_DOUJIANTAI_GET_RANK] = 0,
	[CMSG_DOUJIANTAI_REFRESH_ENEMYS] = 0,
	
	[MSG_DOUJIANTAI_TOP3] = 0,
	
	[CMSG_SUBMIT_QUEST_DAILY2] = 0,
	[CMSG_PICK_DAILY2_QUEST_REWARD] = 0,
	
	[CMSG_FINISH_OPTIONAL_GUIDE_STEP] = 0,
	[CMSG_EXECUTE_QUEST_CMD_AFTER_ACCEPTED] = 0,
	
	[CMSG_STOREHOUSE_HAND_IN] = 0,	--/*上交装备*/
	[CMSG_STOREHOUSE_EXCHANGE] = 0,	--/*兑换装备*/
	[CMSG_STOREHOUSE_DESTROY] = 0,	--/*销毁装备*/
	
	[CMSG_BUY_MASS_BOSS_TIMES] = 0,
	[CMSG_GROUP_INSTANCE_MATCH] = 0,
	[CMSG_BUY_GROUP_INSTANCE_TIMES] = 0,
	
	[CMSG_MERIDIAN_PRACTISE] = 0,		-- /*经脉修炼*/	
	[CMSG_ADD_MERIDIAN_EXP] = 0,		-- /*加经脉修炼经验值*/
	[CMSG_RAISE_MOUNT_LEVEL_BASE] = 0,	-- 升级坐骑等级
	--[CMSG_ACTIVE_MOUNT] = 0,				-- 激活坐骑
	[CMSG_MATCH_SINGLE_PVP] = 0,
	[CMSG_BUY_MATCH_SINGLE_PVP_TIMES] = 0, -- /*购买单人pvp次数*/	
	[CMSG_PICK_MATCH_SINGLE_PVP_EXTRA_REWARD] = 0, -- /*领取单人pvp额外奖励*/
	
	[CMSG_ACTIVE_APPEARANCE] = 0,		-- /*激活外观*/	
	[CMSG_EQUIP_APPEARANCE] = 0,		-- /*装备外观*/	
	[CMSG_CANCEL_EQUIP_APPEARANCE] = 0,
	[CMSG_DRAW_LOTTERY] = 0,			-- 抽奖
	[CMSG_RENAME] = 0,				--改名
	[CMSG_RISK_GET_RANK] = 0,
	
	[CMSG_GROUP_CREATE] = 0,			-- /*创建队伍*/	
	[CMSG_GROUP_JOIN_REQUEST] = 0,	-- /*申请加入队伍*/	
	[CMSG_GROUP_JOIN_ACCEPT] = 0,		-- /*同意加入队伍*/	
	[CMSG_GROUP_QUIT] = 0,			-- /*退出队伍*/	
	[CMSG_GROUP_GIVE_CAPTAIN] = 0,	--移交队伍队长
	[CMSG_GROUP_KICK] = 0,			--踢队员
	
	[CMSG_GROUP_SEND_INVITE] = 0,		--发送组队邀请
	[CMSG_GROUP_AGREE_INVITE] = 0,	--同意组队邀请
	
	[CMSG_GET_GROUP_SEARCH_INFO_LIST] = 0,--便捷组队队伍列表
	
	[CMSG_GROUP_CHANGE_CONFIG] = 0,	--修改组队设置
	[CMSG_GROUP_JOIN_DENIED] = 0,		--拒绝加入队伍
	[CMSG_GROUP_INVITE_DENIED] = 0,	--拒绝邀请
	
	[CMSG_SELECT_GROUP_ENTER] = 0,	-- 队伍决定
	[CMSG_BUY_GROUP_EXP_TIMES] = 0, 	-- 经验副本都买次数
	[CMSG_TALISMAN_EQUIP] = 0,		-- 装备法宝
	[CMSG_TALISMAN_UNEQUIP] = 0,		-- 卸下法宝
	
	--[CMSG_AUTO_GROUP_MATCH] = 0,
	--[CMSG_CANCEL_AUTO_GROUP_MATCH] = 0,
	
	[CMSG_KUAFU_3V3_GROUP_MATCH] = 0,	-- /*组队3v3跨服匹配*/
	[CMSG_ONE_STEP_ROBOT_UP] = 0,	-- /*机器人*/
	[MSG_PING_PONG] = 0,	-- /*测试连接*/
	[CMSG_USE_GIFTCODE] = 0,	-- /*使用兑换码*/
	
		
}	-- dict

function PlayerInfo:CheckOperateCD(operate_id)
	if app_operate_need_cd[operate_id] then
		local now = os.time()
		if now >= self:GetOperateCD() then
			self:SetOperateCD(now + 1)
			outFmtDebug("PlayerInfo:CheckOperateCD opt: %d true start cding",operate_id)
			return true
		end
		
		outFmtDebug("PlayerInfo:CheckOperateCD opt: %d false now cd",operate_id)
		return false
	end
	
	return true
end

-----------------------------------------------------------------------------------------
--家族战操作
--进入战场

function PlayerInfo:EnterFactionMatchMap()
	local ret, detailId, teamId = globalValue:CheckCanEnterFactionMatchMap(self)
	if ret then
		local faction = app.objMgr:getObj(self:GetFactionId())
		if not faction then
			return
		end
		local Faction_Pos = faction:FindPlayerIndex(self:GetGuid())
		if Faction_Pos == nil then
			return
		end		
		local enterFactionTime = tb_faction_match_base[1].enterFactionTime
		if os.time() - faction:GetFactionMemberEnterTime(Faction_Pos) < enterFactionTime then
			self:CallOptResult(OPERTE_TYPE_FACTION, OPERTE_TYPE_FACTION_MATCH_CANNOT_JOIN,{}) -- 提示
			return
		end
		
		local config = tb_faction_match_base[1]
		local x = 0
		local y = 0
		local map_id = config.map_id
		if teamId == 1 then
			x = config.born_1[1]
			y = config.born_1[2]
		elseif teamId == 2 then
			x = config.born_2[1]
			y = config.born_2[2]
		end
		local generalId =   string.format("%d|%d",detailId,globalValue:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_SATRT_TIME))
		call_appd_teleport(self:GetScenedFD(),self:GetGuid(),x,y,map_id,generalId)
		
		
		self:AddActiveItem(VITALITY_TYPE_FACTION_MATCH)
		outFmtDebug("!!!!!!!!!!!!!!!!PlayerInfo:EnterFactionMatchMap join success detailId %d teamId %d",detailId,teamId)
	else
		outFmtDebug("!!!!!!!!!!!!!!!!PlayerInfo:EnterFactionMatchMap can not join FactionMatch now")
	end
end

function PlayerInfo:SetFactionMatchChampionDailyRewardFlag()
	self:SetBit(PLAYER_INT_FIELD_FACTION_MATCH_CHAMPION_DAILY_REWARD_FLAG,0)
end

function PlayerInfo:GetFactionMatchChampionDailyRewardFlag()
	return self:GetBit(PLAYER_INT_FIELD_FACTION_MATCH_CHAMPION_DAILY_REWARD_FLAG,0)
end

function PlayerInfo:UnSetFactionMatchChampionDailyRewardFlag()
	self:UnSetBit(PLAYER_INT_FIELD_FACTION_MATCH_CHAMPION_DAILY_REWARD_FLAG,0)
end

--领取每日奖励
function PlayerInfo:PickFactionMatchChampionDailyReward()
	local guid = self:GetFactionId()
	if guid == "" then
		return
	end
	
	if guid ~= globalValue:GetFactionMatchChampionFactionGuid() then
		return
	end
	
	if self:GetFactionMatchChampionDailyRewardFlag() then
		return
	end
	
	self:AppdAddItems(tb_faction_match_champion[1].dailyReward, MONEY_CHANGE_FACTION_MATCH_DAILY_REWARD,LOG_ITEM_OPER_TYPE_FACTION_MATCH_DAILY_REWARD)
	
	--发送奖励
	outFmtDebug("PlayerInfo:PickFactionMatchChampionDailyReward pick reward")
	
	self:SetFactionMatchChampionDailyRewardFlag()
end

--请求榜单
function PlayerInfo:QueryFactionMatchInfo()
	local rank_table = globalValue:GetFactionMatchInfoTable()
	
	local list = {}
	for _,v in ipairs(rank_table) do
	--奖励通知
		local stru = faction_match_info_t .new()
		stru.name		= v[1]
		stru.result 	= v[2]
		stru.rank		= v[3]
		stru.guid		= v[4]
		table.insert(list, stru)
	end
	
	self:call_show_faction_match_info_list(list)
end


------------------------------------------------------------------------------------------
--广播显示的名字
function PlayerInfo:GetNoticeName()
	local tokens = string.split(self:GetName(),',')
	return tokens[3]
	
end
-- 跨服回来进行清空标志
function PlayerInfo:KuafuUnMarked()
	self:KuafuMarked(0)
end

-- 当前正在进行的跨服类型
function PlayerInfo:KuafuMarked(kuafuType)
	self:SetUInt32(PLAYER_INT_FIELD_KUAFU_NUMBER, kuafuType)
end

-- 是否正在跨服
function PlayerInfo:IsKuafuing()
	return self:GetUInt32(PLAYER_INT_FIELD_KUAFU_NUMBER) > 0
end

function PlayerInfo:GetWingsUpgradeLevel()
	return self:GetUInt32(PLAYER_INT_FIELD_WINGS_RANK)
end

function PlayerInfo:SetGroupId(groupId)
	self:SetStr(PLAYER_STRING_FIELD_GROUP_PEACE_ID, groupId)
end

function PlayerInfo:GetGroupId()
	return self:GetStr(PLAYER_STRING_FIELD_GROUP_PEACE_ID)
end

function PlayerInfo:GetGemTotalLevel()
	local spellMgr = self:getSpellMgr()
	local count = 0
	for index = 0,EQUIPMENT_COUNT - 1 do
		local gem_part_config = tb_equipdevelop_gem_part[index + 1]
		local gem_count = #(gem_part_config.gem_array)
		for gem_index = 0,gem_count -1 do
			
			local level = spellMgr:GetEquipDevelopGemLv(index,gem_index)
			
			count = count + level
			
		end
	end
	
	return count
end


function PlayerInfo:GetRestOfflineMinutes()
	return self:GetUInt32(PLAYER_INT_FIELD_OFFLINE_MINUTES)
end

function PlayerInfo:ModifyRestOfflineMinutes(minutes)
	minutes = minutes or 0
	local val = self:GetRestOfflineMinutes() + minutes
	local limit = tb_offline_exp_base[ 1 ].limitMins
	val = math.max(0, math.min(val, limit))
	self:SetUInt32(PLAYER_INT_FIELD_OFFLINE_MINUTES, val)
end

-- 充值接口
function PlayerInfo:DoRecharge(obj)
	local ret = true
	
	security.call(
		--try block
		function()
			-- 这里计算实际获得的值
			obj.real = math.floor(tonumber(obj.money) * 10)
			
			--添加每档首次奖励
			--tb_shop_chongzhi
			for i,info in pairs(tb_shop_chongzhi) do
				if tonumber(obj.money) == info.cost then
					if self:GetShopChargeFlag(i) then
						obj.real = obj.real + info.non_first_extra_gold
					else
						if info.first_reward == 1 then
							obj.real = obj.real * info.rate
							self:SetShopChargeFlag(i)
						else
							obj.real = obj.real + info.non_first_extra_gold
						end
					end
					break
				end
			end
			
			self:AppdAddItems({{MONEY_TYPE_GOLD_INGOT, obj.real}}, MONEY_CHANGE_TYPE_CHARGE, nil, nil, nil, nil, 1)
			local payId = obj.payid
			if not payId then
				payId = obj.oid
			end
			self:DoAddRechargeSum(payId, math.floor(tonumber(obj.money)), os.time(), function()
				-- 记录首冲日志
				WriteFirstRechargeInfoLog(self, obj.money, os.time(), obj.ext)
			end)
			outFmtInfo("============== guid = %s has charged gold = %d", self:GetGuid(), obj.real)
		end,
		function(errors)
			ret = false
			outFmtError("%s", errors)
		end
	)
	
	return ret
end

function PlayerInfo:SetShopChargeFlag(index)
	self:SetBit(PLAYER_INT_FIELD_SHOP_CHARGE_FLAG,index)
end


function PlayerInfo:GetShopChargeFlag(index)
	return self:GetBit(PLAYER_INT_FIELD_SHOP_CHARGE_FLAG,index)
end

function PlayerInfo:isLogined()
	return playerLib.CppCheckPlayerIsLogined(self.ptr) == 1
end

function PlayerInfo:SetRechargeLotteryTimes(val)
	self:SetUInt16(PLAYER_INT_FIELD_RECHARGE_LOTTERY_TIMES, 1, val)	
end

function PlayerInfo:CheckRechargeLotteryTimes()
	local used = self:GetUInt16(PLAYER_INT_FIELD_RECHARGE_LOTTERY_TIMES, 0)
	local hasd = self:GetUInt16(PLAYER_INT_FIELD_RECHARGE_LOTTERY_TIMES, 1)
	if used >= hasd then
		return 0
	end
	return used + 1
end

function PlayerInfo:AddRechargeLotteryTimesUsed()
	self:AddUInt16(PLAYER_INT_FIELD_RECHARGE_LOTTERY_TIMES, 0, 1)
end


function PlayerInfo:CheckClearCheckInData()
	local month = self:GetUInt32(PLAYER_INT_FIELD_WELFARE_CURRENT_MONTH)
	
	local curmonth = os.date("*t", os.time()).month
	
	if curmonth ~= month then
		self:SetUInt32(PLAYER_INT_FIELD_WELFARE_CURRENT_MONTH,curmonth)
		
		self:getQuestMgr():SetUInt32(QUEST_FIELD_WELFARE_CHECKIN,0)
		self:getQuestMgr():SetUInt32(QUEST_FIELD_WELFARE_CHECKIN_ALL,0)
		self:SetUInt32(PLAYER_INT_FIELD_WELFARE_CHECKIN_GETBACK_COUNT,0)
		
	end
end

function PlayerInfo:ResetActRankData()
	for i = 1, 9 do
		DoActivitySystemDataUpdateByScriptId(ACT_RANK,{i,self})
	end
end
-- 关闭连接
function PlayerInfo:CloseSession(fd, is_force)
	if is_force == nil then is_force = false end
	is_force = is_force and 1 or 0
	call_opt_cent_destory_conn(fd, is_force)
end
-- 关闭连接
function PlayerInfo:Close(c_type, c_str, is_force)
	if c_str == nil then c_str = "" end
	if is_force == nil then is_force = false end
	if(c_type)then
		self:CallOptResult(OPERTE_TYPE_CLOSE, c_type, c_str)
	end
	self:CloseSession(self:GetSessionId(), is_force)
end

require("appd/appd_context/appd_context_usemoney_opt")
require("appd/appd_context/appd_context_calculAttr")
require("appd/appd_context/appd_context_resetdaily")
require("appd/appd_context/appd_context_scened_dosomething")
require("appd/appd_context/appd_context_other_binlog")
require("appd/appd_context/appd_context_chat")
require("appd/appd_context/appd_context_instance")
require("appd/appd_context/appd_context_equip_part_opt")
require("appd/appd_context/appd_context_spell")
require("appd/appd_context/appd_context_social")
require("appd/appd_context/appd_context_shop")
require("appd/appd_context/appd_context_giftpacks")
require("appd/appd_context/appd_context_achieve_title")
require("appd/appd_context/appd_context_welfare")
require("appd/appd_context/appd_context_rank_gift")
require("appd/appd_context/appd_context_group")

require("appd/appd_context/appd_context_xianfu_test")
require("appd/appd_context/appd_context_kuafu")
require("appd/appd_context/appd_context_world3v3")
require("appd/appd_context/appd_context_xianfu")
require("appd/appd_context/appd_context_group_instance")
require("appd/appd_context/appd_context_local_single_pvp")
require("appd/appd_context/appd_context_doujiantai")
require("appd/appd_context/appd_context_module_unlock")
require("appd/appd_context/appd_context_guide")
require("appd/appd_context/appd_context_cultivation")
require("appd/appd_context/appd_context_after_quest_doing")
require("appd/appd_context/appd_context_login_activity")

require("appd/appd_context/handler/faction_handler")
require("appd/appd_context/handler/GiftPacksHandler")
require("appd/appd_context/handler/chat_handler")
require("appd/appd_context/handler/equip_part_opt_handler")
require("appd/appd_context/handler/spell_handler")
require("appd/appd_context/handler/instance_handler")
require("appd/appd_context/handler/social_handler")
require("appd/appd_context/handler/shop_handler")
require("appd/appd_context/handler/rank_handler")
require("appd/appd_context/handler/kuafu_handler")
require("appd/appd_context/handler/active_handler")
require("appd/appd_context/handler/activity_handler")
require("appd/appd_context/handler/achieve_title_handler")
require("appd/appd_context/handler/welfare_handler")
require("appd/appd_context/handler/guide_handler")
require("appd/appd_context/handler/cultivation_handler")
require("appd/appd_context/handler/login_activity_handler")
require("appd/appd_context/handler/group_handler")
require("appd/appd_context/handler/recharge_handler")

require("appd/appd_context/appd_context_hanlder")

return PlayerInfo
