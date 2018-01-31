InstanceWorldBoss = class("InstanceWorldBoss", InstanceInstBase)
local protocols = require('share.protocols')

InstanceWorldBoss.Name = "InstanceWorldBoss"
InstanceWorldBoss.player_auto_respan = 5

-- 获胜标志 (0:未结束, 1:结束胜利, 2:结束失败)
InstanceWorldBoss.FLAG_WIN = 1
InstanceWorldBoss.FLAG_LOSE = 2
InstanceWorldBoss.WORLD_BOSS_NAME = "WORLD_BOSS"

-- 判断BOSS是否需要升级
function DoIfBOSSLevelUp()
	
	local num = 0
	local rooms = globalValue:GetTodayWorldBossRoom()
	for i = 1, rooms do
		if globalValue:IsWorldBossEndInLine(i) then
			num = num + 1
		end
	end

	-- BOSS需要升级了
	if num * 2 > rooms then
		globalValue:AddWorldBossLevel()
	end
end

function InstanceWorldBoss:ctor(  )
	
end


--初始化脚本函数
function InstanceWorldBoss:OnInitScript()
	-- 不让重复初始化
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	Instance_base.OnInitScript(self) --调用基类
	
	self:OnTaskStart()
	self:AddCountDown()
	
	-- 刷新BOSS 计时器
	mapLib.AddTimer(self.ptr, 'OnTimer_RefreshBoss', tb_worldboss_time[ 1 ].waitCountdown * 1000)
	
	-- 刷新排名 计时器
	mapLib.AddTimer(self.ptr, 'OnTimer_UpdateRank', 1000)
end

function InstanceWorldBoss:SetBossHP(val)
	self:SetUInt32(MAP_MASS_BOSS_INT_FIELD_MAX_HP, val)
end

function InstanceWorldBoss:GetBossHP()
	return self:GetUInt32(MAP_MASS_BOSS_INT_FIELD_MAX_HP)
end

-- 活动正式开始
function InstanceWorldBoss:OnTaskStart()
	local waitTime = tb_worldboss_time[ 1 ].waitCountdown
		
	self:SetUInt32(WORLDBOSS_FIELDS_BORN_TIME, waitTime)
	
	-- 任务开始时间
	self:SetMapStartTime(os.time() + waitTime)
		
	local timestamp = os.time() + waitTime + tb_worldboss_time[ 1 ].time_last * 60
	-- 加任务结束时间
	self:SetMapQuestEndTime(timestamp)
	-- 副本时间超时回调
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp)
end

--当副本状态发生变化时间触发
function InstanceWorldBoss:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s后结束副本
		local timestamp = os.time() + InstanceDoujiantai.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end


function InstanceWorldBoss:AddCountDown()
	local timestamp = os.time() + tb_worldboss_time[ 1 ].waitCountdown
	self:SetMapStartTime(timestamp)
	self:AddTimeOutCallback("countdown", timestamp)
end

-- 倒计时结束
function InstanceWorldBoss:countdown()
	-- 符点刷新定时器
	mapLib.AddTimer(self.ptr, 'OnBuffRefresh', tb_worldboss_time[ 1 ].interval * 1000)
end

-- 刷新buff
function InstanceWorldBoss:OnBuffRefresh()
	-- 处理刷新次数
	local times = self:GetMapReserveValue1()
	if times < tb_worldboss_time[ 1 ].times then
		self:SetMapReserveValue1(times+1)
	end
	
	-- 刷新把原来的先删掉
	local allGameObjects = mapLib.GetAllGameObject(self.ptr)
	for _, gameobject in pairs(allGameObjects) do
		mapLib.RemoveWorldObject(self.ptr, gameobject)
	end
	
	-- 刷新新的
	local indice = GetRandomIndexTable(#tb_worldboss_time[ 1 ].buffRandomPos, tb_worldboss_time[ 1 ].randomCount)
	for i = 1, #indice do
		local indx = indice[ i ]
		local pos = tb_worldboss_time[ 1 ].buffRandomPos[indx]
		local buffIndx = randInt(1, #tb_worldboss_buff)
		local entry =  tb_worldboss_buff[buffIndx].gameobject_id
		mapLib.AddGameObject(self.ptr, entry, pos[ 1 ], pos[ 2 ], GO_GEAR_STATUS_END)
	end
	
	app:CallOptResult(self.ptr, OPRATE_TYPE_ATHLETICS, ATHLETICS_OPERATE_BUFF_OCCUR)
	
	return self:GetMapReserveValue1() < tb_worldboss_time[ 1 ].times
end


--使用游戏对象之前
--返回1的话就继续使用游戏对象，返回0的话就不使用
function InstanceWorldBoss:OnBeforeUseGameObject(user, go, go_entryid, posX, posY)
	-- 如果已经死了 就不能捡了
	if unitLib.HasBuff(user, BUFF_INVINCIBLE) then
		return 0
	end
	
	if Script_Gameobject_Pick_Check(user, go_entryid, posX, posY) then
		return 1
	end
	return 0
end

--使用游戏对象
--返回1的话成功使用游戏对象，返回0的话使用不成功
function InstanceWorldBoss:OnUseGameObject(user, go, go_entryid, posX, posY)
	-- 判断对应的是那种buff
	for _, obj in ipairs(tb_worldboss_buff) do
		if obj.gameobject_id == go_entryid then
			local effectId = obj.buffEffect
			local buffId = tb_buff_effect[effectId].buff_id
			local duration = tb_buff_effect[effectId].duration
			SpelladdBuff(user, buffId, user, effectId, duration)
			break
		end
	end
	
	-- 需要删除对象
	mapLib.RemoveWorldObject(self.ptr, go)
	
	return 1	
end

-- 世界BOSS结束了
function InstanceWorldBoss:IsEnd()
	local lineNo = self:GetMapLineNo()
	return globalValue:IsWorldBossEnd() or globalValue:IsWorldBossEndInLine(lineNo)
end

-- 刷新BOSS
function InstanceWorldBoss:OnTimer_RefreshBoss()
	if globalValue:IsWorldBossBorn() then
		-- 刷BOSS		
		local boss = mapLib.AliasCreature(self.ptr, InstanceWorldBoss.WORLD_BOSS_NAME)
		if not boss then
			local indx   = globalValue:GetTodayWorldBossID()
			local wbconfig = tb_worldboss_base[indx]
			local entry  = wbconfig.entry
			local born   = wbconfig.born
		
			local config = tb_creature_template[entry]
			local creature = mapLib.AddCreature(self.ptr, {
					templateid = entry, x = born[ 1 ], y = born[ 2 ], active_grid = true, 
					alias_name = InstanceWorldBoss.WORLD_BOSS_NAME, ainame = config.ainame, npcflag = {}
				}
			)
			
			if creature then
				local creatureInfo = UnitInfo:new{ptr = creature}
				-- 标识为boss怪
				creatureInfo:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
				self:SetBossHP(creatureInfo:GetMaxHealth())
			end
		end
	end

	return false
end

--[[
10000 <= 命中率 <= 16500
500 <= 闪避率 <= 5000
500 <= 暴击率 <= 6000
--]]
local rangedAttr = {
	[EQUIP_ATTR_CRIT_RATE] = {500, 6000},
	[EQUIP_ATTR_HIT_RATE]  = {10000, 16500},
	[EQUIP_ATTR_MISS_RATE] = {500, 5000},
}
function InstanceWorldBoss:SetCreaturePro(creatureInfo, pros, bRecal, mul)
	local level = globalValue:GetWorldBossLevel()
	local newPro = rewardsAddExtraAndClone(pros, level * 0.2)
	
	for _, info in ipairs(newPro) do
		local attrId = info[ 1 ]
		if rangedAttr[attrId] then
			info[ 2 ] = math.min(math.max(info[ 2 ], rangedAttr[attrId][ 1 ]), rangedAttr[attrId][ 2 ])
		end
	end

	Instance_base.SetCreaturePro(self, creatureInfo, newPro, bRecal, 1)
end

-- 进行排名更新
function InstanceWorldBoss:OnTimer_UpdateRank()
	mapLib.NotifyAllRankUpdate(self.ptr)
	
	-- 世界BOSS结束
	if self:IsEnd() then
		mapLib.ResetBossDamageRank(self.ptr)
		-- 设置提前结束时间
		-- self:SetMapEndTime(os.time() + 20)
		return false
	end
	
	return true
end

function InstanceWorldBoss:OnLeavePlayer(player, isOffline)
	InstanceInstBase.OnLeavePlayer(self, player, isOffline)
end
--玩家加入地图
function InstanceWorldBoss:OnJoinPlayer(player)
	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--死亡了还进来，直接弹出去
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		return
	end
	
	-- 结束时间到就不让进了
	if os.time() >= self:GetMapQuestEndTime() or self:IsEnd() then
		mapLib.ExitInstance(self.ptr, player)
		return
	end
end

function InstanceWorldBoss:GetDeadTimes(playerInfo)
	local cnt = mapLib.GetDeadTimes(self.ptr, playerInfo:GetPlayerGuid())
	cnt = cnt or 0
	
	return cnt
end

-- 当玩家死亡后
function InstanceWorldBoss:OnPlayerDeath(player)
	local playerInfo = UnitInfo:new{ptr = player}
	mapLib.AddDeadTimes(self.ptr, playerInfo:GetPlayerGuid())
end


--AI_WorldBoss
-------------------------世界boss---------------------------
AI_WorldBoss = class("AI_WorldBoss", AI_Base)
AI_WorldBoss.ainame = "AI_WorldBoss"

--死亡
function AI_WorldBoss:JustDied( map_ptr,owner,killer_ptr )
	outFmtDebug("============================ world BOSS was dead")
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local instanceInfo = InstanceWorldBoss:new{ptr = map_ptr}
	local mapid  = instanceInfo:GetMapId()
	local lineNo = instanceInfo:GetMapLineNo()
	
	-- 设置状态
	globalValue:SetWorldBossEndInLine(lineNo)
	instanceInfo:SetMapEndTime(os.time() + 12)
	instanceInfo:SetMapState(instanceInfo.STATE_FINISH)
	
	local exist = {}
	local allPlayers = mapLib.GetAllPlayer(map_ptr)
	for _, player in pairs(allPlayers) do
		local player_guid = GetPlayerGuid(player)
		exist[player_guid] = 1
	end
	
	-- 根据排名 发邮件
	local ranklist = mapLib.GetBossDamageRank(map_ptr)
	local indx = 1
	for i = 1, #ranklist do
		local range = tb_worldboss_rank_reward[indx].range
		-- 不满足条件的往后移
		if range[ 2 ] > 0 and range[ 2 ] < i then
			indx = indx + 1
		end
		
		local playerGuid = ranklist[ i ]
		--发到应用服发宝箱
		local player = mapLib.GetPlayerByPlayerGuid(map_ptr, playerGuid)
		local vip = 0
		local level = 0
		local playerInfo = nil
		if player then
			playerInfo = UnitInfo:new {ptr = player}
			vip = playerInfo:GetVIP()
			level = playerInfo:GetLevel()
		else
			level, vip = mapLib.GetBossDamageRankPlayerInfo(map_ptr, i)
		end
		
		local rankRewardConfig = tb_worldboss_rank_reward[indx]
		local items = raiseItem(rankRewardConfig.serverRewards, tb_vip_base[vip].worldbossReward)
		local factor = rankRewardConfig.factor / 100
		
		
		local lrc = tb_worldboss_rank_level_reward[ 1 ]
		for k = 1, #tb_worldboss_rank_level_reward do
			local levelRewardConfig = tb_worldboss_rank_level_reward[ k ]
			if levelRewardConfig.levelRange[ 1 ] <= level and level <= levelRewardConfig.levelRange[ 2 ] then
				lrc = levelRewardConfig
				break
			end
		end
		
		items = string.format("%s,%d,%d", items, lrc.serverRewards[ 1 ], math.floor(factor * lrc.serverRewards[ 2 ] * (1 + tb_vip_base[vip].worldbossReward / 100)))
		
		local mailInfo = {items, rankRewardConfig.name, rankRewardConfig.desc, GIFT_PACKS_TYPE_WORLD_BOSS}
		local str = string.join("|", mailInfo)
		
		if player then
			playerLib.SendToAppdDoSomething(player, SCENED_APPD_ADD_MAIL, 0, str)
			if exist[playerInfo:GetPlayerGuid()] then
				local params = string.split(items, ',')
				local dict = {}
				for i = 1, #params, 2 do
					local entry = tonumber(params[ i ])
					local count = tonumber(params[i+1])
					if entry and count then
						dict[entry] = count
					end
				end
				local list = Change_To_Item_Reward_Info(dict, true)
				playerInfo:call_send_instance_result(instanceInfo:GetMapState(), instanceInfo.exit_time, list, INSTANCE_SUB_TYPE_WORLD_BOSS, '')
			end
		else
			playerLib.SendToAppdAddOfflineMail(playerGuid, str)
		end
	end
	
	return 0
end

function raiseItem(items, extra)
	extra = extra or 0
	if extra == 0 then
		return items
	end
	local params = string.split(items, ',')
	local list = {}
	for i = 1, #params, 2 do
		local entry = tonumber(params[ i ])
		local count = math.floor(tonumber(params[i+1]) * (1 + extra / 100))
		if entry and count then
			table.insert(list, entry)
			table.insert(list, count)
		end
	end
	
	return string.join(",", list)
end

-- 伤害发生前
function AI_WorldBoss:DamageTaken(owner, unit, damage)
	local bossInfo = UnitInfo:new{ptr = owner}
	local map_ptr = unitLib.GetMap(owner)
	local instanceInfo = InstanceWorldBoss:new{ptr = map_ptr}
	local mapid  = instanceInfo:GetMapId()
	local lineNo = instanceInfo:GetMapLineNo()
	
	if damage <= 0 then
		return
	end
	
	local prev = bossInfo:GetHealth()
	local maxHealth  = bossInfo:GetMaxHealth()
	if damage > prev then
		damage = prev
	end
	
	currHealth = prev - damage
	
	if prev == 0 then
		return
	end
	
	local playerGuid = ''
	local name = ''
	local unitInfo = UnitInfo:new {ptr = unit}
	-- 如果是怪物就找归属者
	if unitInfo:GetTypeID() == TYPEID_UNIT then
		local host = creatureLib.GetMonsterHost(unit)
		if host then
			unitInfo = UnitInfo:new {ptr = host}
			playerGuid = unitInfo:GetPlayerGuid()
			name = unitInfo:GetName()
		end
	else
		playerGuid = unitInfo:GetPlayerGuid()
		name = unitInfo:GetName()
	end
	
	-- 进行排名
	mapLib.AddBossDamage(map_ptr, unitInfo.ptr, damage, maxHealth, unitInfo:GetLevel(), unitInfo:GetVIP())
	return 0
end

-- 受到伤害后
function AI_WorldBoss:DamageDeal( owner, unit, damage)
	local map_ptr = unitLib.GetMap(owner)
	local instanceInfo = InstanceWorldBoss:new{ptr = map_ptr}
	local lineNo = instanceInfo:GetMapLineNo()
	
	if damage < 0 then
		
		return
	end
end

return InstanceWorldBoss