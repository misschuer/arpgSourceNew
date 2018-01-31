InstanceGroupExp = class("InstanceGroupExp", InstanceInstBase)

InstanceGroupExp.Name = "InstanceGroupExp"
InstanceGroupExp.exit_time = 10
--InstanceGroupExp.broadcast_nogrid = 1
InstanceGroupExp.player_auto_respan = 3

function InstanceGroupExp:ctor(  )
	
end

--初始化脚本函数
function InstanceGroupExp:OnInitScript(  )
	-- 不让重复初始化
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	InstanceInstBase.OnInitScript(self) --调用基类
	
	local level = self:parseGeneralId()
	self:onInitTime(level)
end

function InstanceGroupExp:onInitTime(level)
	local timestamp = os.time()
	local countDown = tb_instance_group_exp[ 1 ].countDown
	local timeLast  = tb_instance_group_exp[ 1 ].timeLast
	
	-- 加倒计时
	self:SetMapStartTime(timestamp + countDown)
	-- 加结束时间
	local endTime = timestamp + timeLast + countDown
	self:SetMapQuestEndTime(endTime)
	self:SetMapEndTime(endTime + self.exit_time)
	
	mapLib.AddTimeStampTimer(self.ptr, 'refresh', timestamp + countDown, level, tb_instance_group_exp[ 1 ].count)
	-- mapLib.AddTimer(self.ptr, , countDown * 1000, level, tb_instance_group_exp[ 1 ].monsters[ 4 ])
	-- 副本时间超时回调
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, endTime)
end

function InstanceGroupExp:instanceFail()
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	for _, unit_player in ipairs(allPlayers) do
		local playerInfo = UnitInfo:new {ptr = unit_player}
		if not playerInfo:IsAlive() then
			unitLib.Respawn(unit_player, RESURRECTION_SPAWNPOINT, 100)
		end
		self:OnSendResult(unit_player)
	end
	self:SetMapState(self.STATE_NOTPASS)
end

function InstanceGroupExp:parseGeneralId()
	-- groupId#level#time
	local generalId = self:GetMapGeneralId()
	local params = string.split(generalId, '#')
	local level = tonumber(params[ 2 ])
	
	return level
end

--当副本状态发生变化时间触发
function InstanceGroupExp:OnSetState(fromstate,tostate)
	if tostate == self.STATE_NOTPASS  then
		--10s后结束副本
		local timestamp = os.time() + self.exit_time
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapQuestEndTime(os.time())
		self:SetMapEndTime(timestamp)
	end
end

-- 判断是否能退出副本
function InstanceGroupExp:DoPlayerExitInstance(player)
	return 1
end

--玩家加入地图
function InstanceGroupExp:OnJoinPlayer(player)
	local isReenter = false
	local playerInfo = UnitInfo:new{ptr = player}
	local emptyIndex = self:findIndexByName(playerInfo:GetPlayerGuid())
	if emptyIndex > -1 then
		isReenter = true
	end

	InstanceInstBase.OnJoinPlayer(self, player, isReenter)
	if not playerInfo:IsAlive() and not isReenter then
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
	end

	-- 记录玩家信息
	local emptyIndex = self:findIndexByName(playerInfo:GetPlayerGuid())
	if emptyIndex == -1 then
		emptyIndex = self:findIndexByName()
		if emptyIndex > -1 then
			local intstart = GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_INT_COUNT
			local strstart = GROUP_EXP_INSTANCE_STR_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_STR_COUNT
			self:SetStr(strstart + GROUP_EXP_INSTANCE_STR_GUID, playerInfo:GetPlayerGuid())
			self:SetDouble(intstart + GROUP_EXP_INSTANCE_INT_EXP, 0)
		end
	else
		self:onAddInspireBuff(player, emptyIndex)
	end
end

-- 获得名字对应的位置, ''表示用来查询空位位置
function InstanceGroupExp:findIndexByName(name)
	name = name or ''
	local strstart = GROUP_EXP_INSTANCE_STR_FIELD_INFO_START
	for i = 0, MAX_GROUP_MEMBER_COUNT-1 do
		if self:GetStr(strstart + GROUP_EXP_INSTANCE_STR_GUID) == name then
			return i
		end
		strstart = strstart + MAX_EXP_INFO_STR_COUNT
	end
	
	return -1
end

function InstanceGroupExp:onAddInspireBuff(player, emptyIndex)
	local intstart = GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_INT_COUNT
	local a = self:GetUInt32(intstart + GROUP_EXP_INSTANCE_INT_MONEY_BUY)
	local b = self:GetUInt32(intstart + GROUP_EXP_INSTANCE_INT_INGOT_BUY)
	a = a + b
	if a > 0 then
		local buffEffectList = tb_instance_group_exp[ 1 ].buffEffectId
		a = math.min(a, #buffEffectList)
		local buffEffectId = buffEffectList[ a ]
		local buffEffectConfig = tb_buff_effect[buffEffectId]
		SpelladdBuff(player, buffEffectConfig.buff_id, player, buffEffectId, buffEffectConfig.duration)
		self:SetUInt32(intstart + GROUP_EXP_INSTANCE_EFFECT, math.abs(buffEffectConfig.value))
	end
end

function InstanceGroupExp:inspire(playerInfo, category)
	local emptyIndex = self:findIndexByName(playerInfo:GetPlayerGuid())
	if emptyIndex == -1 then
		return
	end
	
	-- 可增加次数
	if self:CheckAvailable(emptyIndex, category) then
		local intstart = GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_INT_COUNT
		if category == 0 then
			self:AddUInt32(intstart + GROUP_EXP_INSTANCE_INT_MONEY_BUY, 1)
		else
			self:AddUInt32(intstart + GROUP_EXP_INSTANCE_INT_INGOT_BUY, 1)
		end
		-- 进行buff计算
		self:onAddInspireBuff(playerInfo.ptr, emptyIndex)
	end
end

function InstanceGroupExp:checkCanInspire(playerInfo, category)
	local emptyIndex = self:findIndexByName(playerInfo:GetPlayerGuid())
	if emptyIndex == -1 then
		return
	end

	return self:CheckAvailable(emptyIndex, category)
end

function InstanceGroupExp:CheckAvailable(emptyIndex, category)
	local intstart = GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_INT_COUNT
	local a = self:GetUInt32(intstart + GROUP_EXP_INSTANCE_INT_MONEY_BUY)
	if category == 0 then
		-- money购买次数满了
		if a >= tb_instance_group_exp[ 1 ].goldTimes then
			return false
		end
	end
	
	local b = self:GetUInt32(intstart + GROUP_EXP_INSTANCE_INT_INGOT_BUY)
	-- 效果id只支持这么多
	if a + b >= #tb_instance_group_exp[ 1 ].buffEffectId then
		return false
	end
	
	return true
end

function InstanceGroupExp:SetCreaturePro(creatureInfo, pros, bRecal, mul)
	local config = tb_creature_group_exp[creatureInfo:GetLevel()]
	if config then
		Instance_base.SetCreaturePro(self, creatureInfo, config.pro, bRecal, mul)
	else
		Instance_base.SetCreaturePro(self, creatureInfo, pros, bRecal, mul)
	end
end

function InstanceGroupExp:DoGetCreatureBaseExp(creature, owner)
	local creatureInfo = UnitInfo:new {ptr = creature}
	local level = creatureInfo:GetLevel()
	local config = tb_creature_group_exp[level]
	
	if config then
		return config.exp
	end
	return 0
end

function InstanceGroupExp:refresh(level, cnts)
	for i = 1, cnts do
		local prev = self:GetUInt32(GROUP_EXP_INSTANCE_FIELD_INDX) + 1
		if prev > #tb_instance_group_exp[ 1 ].monsters then
			prev = 1
		end
		self:SetUInt32(GROUP_EXP_INSTANCE_FIELD_INDX, prev)
		local entry = tb_creature_group_exp[level].entry
		
		local pos = tb_instance_group_exp[ 1 ].monsters[prev]
		local bornX = pos[ 1 ] + randInt(-1, 1)
		local bornY = pos[ 2 ] + randInt(-1, 1)
		
		local creature = mapLib.AddCreature(self.ptr, {
			templateid = entry, x = bornX, y = bornY, respan_time = tb_creature_template[entry].rebornTime,
			active_grid = false, ainame = "AI_groupInst", npcflag = {}, level = level,
		})
	end
end

function InstanceGroupExp:OnPlayerAddExp(playerInfo, exp)
	local emptyIndex = self:findIndexByName(playerInfo:GetPlayerGuid())
	if emptyIndex > -1 then
		local intstart = GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_INT_COUNT
		self:AddDouble(intstart + GROUP_EXP_INSTANCE_INT_EXP, exp)
	end
end

function InstanceGroupExp:OnSendResult(player)
	local playerInfo = UnitInfo:new {ptr = player}
	local emptyIndex = self:findIndexByName(playerInfo:GetPlayerGuid())
	if emptyIndex > -1 then
		local intstart = GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_INT_COUNT
		local exp = self:GetDouble(intstart + GROUP_EXP_INSTANCE_INT_EXP)
		local dict = {[Item_Loot_Exp] = exp}
		local list = Change_To_Item_Reward_Info(dict, true)
		local mapid = self:GetMapId()
		local type = tb_map[mapid].inst_sub_type
		playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, type, '')
	end
end

--当玩家离开前触发
function InstanceGroupExp:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	if not is_offline then
		-- 结算信息
		if self:GetMapState() ~= self.STATE_NOTPASS then
			self:OnSendResult(player)
		end
		
		-- 如果一个人都没了就设置副本结束
		local allPlayers = mapLib.GetAllPlayer(self.ptr)
		if #allPlayers == 1 then
			if self:GetMapState() ~= self.STATE_NOTPASS then
				self:SetMapState(self.STATE_NOTPASS)
			end
		end
	end
end

function InstanceGroupExp:AddMonsterCnt()
	self:AddUInt32(GROUP_EXP_INSTANCE_FIELD_CNT, 1)
	self:refreshAnotherMonster()
end

function InstanceGroupExp:refreshAnotherMonster()
	local level = 0
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	for _, unit_player in ipairs(allPlayers) do
		local playerInfo = UnitInfo:new {ptr = unit_player}
		level = level + playerInfo:GetLevel()
	end
	level = math.ceil(level / #allPlayers)
	mapLib.AddTimeStampTimer(self.ptr, 'refresh', os.time() + 1, level, 1)
end

--当玩家死亡后触发()
function InstanceGroupExp:OnPlayerDeath(player)
	local playerInfo = UnitInfo:new {ptr = player}
	local emptyIndex = self:findIndexByName(playerInfo:GetPlayerGuid())
	if emptyIndex > -1 then
		local mapid = self:GetMapId()
		local waitTimeList = tb_map[mapid].rebornWaitTime
		local sec = waitTimeList[ 1 ]
		if sec then
			local intstart = GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_INT_COUNT
			self:SetUInt32(intstart + GROUP_EXP_INSTANCE_INT_CD, os.time() + sec)
		end
	end
	
	self:OnSendDeathInfo(playerInfo, '', '')
end


function InstanceGroupExp:GetCostTimeCD(playerInfo)
	local emptyIndex = self:findIndexByName(playerInfo:GetPlayerGuid())
	if emptyIndex > -1 then
		local intstart = GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + emptyIndex * MAX_EXP_INFO_INT_COUNT
		return self:GetUInt32(intstart + GROUP_EXP_INSTANCE_INT_CD)
	end
	return 60
end

----------------------------- 小怪----------------------------
AI_groupInst = class("AI_groupInst", AI_Base)
AI_groupInst.ainame = "AI_groupInst"
--死亡
function AI_groupInst:JustDied( map_ptr,owner,killer_ptr )	
	
	--AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local mapid = mapLib.GetMapID(map_ptr)
	local instanceInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	instanceInfo:AddMonsterCnt()
	
	return 0
end

return InstanceGroupExp