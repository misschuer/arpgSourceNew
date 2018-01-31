InstancePrivateBoss = class("InstancePrivateBoss", InstanceInstBase)
local protocols = require('share.protocols')

InstancePrivateBoss.Name = "InstancePrivateBoss"
InstancePrivateBoss.BOSS_ALIAS_NAME = 'PRIVATE_BOSS'
InstancePrivateBoss.exit_time = 10

function InstancePrivateBoss:ctor(  )
	
end

--初始化脚本函数
function InstancePrivateBoss:OnInitScript(  )
	-- 不让重复初始化
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	InstanceInstBase.OnInitScript(self) --调用基类
	-- 解析generalid
	self:parseGeneralId()
	
	
	
	
end

function InstancePrivateBoss:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	local params = string.split(generalId, '|')
	
	local id = tonumber(params[1])
	local buffeffectId = tonumber(params[2])
	
	self:SetPrivateBossId(id)
	self:SetBuffeffectId(buffeffectId)
	
	-- 刷boss
	self:onRefreshBoss()
	
	--tb_private_boss_base[1].timeLimit = 180
	-- 挑战时间
	self:SetMapEndTime(os.time() + tb_private_boss_base[1].timeLimit + self.exit_time)
	self:SetMapQuestEndTime(os.time() + tb_private_boss_base[1].timeLimit)
	-- 副本时间超时回调
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, os.time() + tb_private_boss_base[1].timeLimit)
	
	-- 刷新任务
	local mapQuest = tb_private_boss_info[id].quest[1]
	-- 加副本任务
	InstanceInstBase.OnAddQuests(self, {mapQuest})
end

function InstancePrivateBoss:SetPrivateBossId(id)
	self:SetUInt32(MAP_PRIVATE_BOSS_INT_FIELD_ID, id)
end

function InstancePrivateBoss:GetPrivateBossId()
	return self:GetUInt32(MAP_PRIVATE_BOSS_INT_FIELD_ID)
end

function InstancePrivateBoss:SetBuffeffectId(id)
	self:SetUInt32(MAP_PRIVATE_BOSS_INT_FIELD_BUFFEFFECT_ID, id)
end

function InstancePrivateBoss:GetBuffeffectId()
	return self:GetUInt32(MAP_PRIVATE_BOSS_INT_FIELD_BUFFEFFECT_ID)
end

--[[
function InstancePrivateBoss:DoMapBuffBonus(unit)
	if GetUnitTypeID(unit) == TYPEID_PLAYER then
		local buffEffectId = self:GetBuffeffectId()
		if buffEffectId ~= 0 then
			local buff_id = tb_buff_effect[buffEffectId].buff_id
			SpelladdBuff(unit, buff_id, unit, buffEffectId, 180)
		end
	end
end--]]

function InstancePrivateBoss:onRefreshBoss()
	local id = self:GetPrivateBossId()
	local boss = mapLib.AliasCreature(self.ptr, self.BOSS_ALIAS_NAME)
	if not boss then
		local bossconfig = tb_private_boss_info[ id ]
		local entry  = bossconfig.bossEntry
		local born   = bossconfig.bossPos
		local config = tb_creature_template[entry]
		local creature = mapLib.AddCreature(self.ptr, 
			{
				templateid = entry, x = born[ 1 ], y = born[ 2 ], active_grid = true, 
				alias_name = self.BOSS_ALIAS_NAME, ainame = "AI_PrivateBoss", npcflag = {}
			}
		)
		
		if creature then
			local debuffeffect_id = self:GetBuffeffectId()
			if debuffeffect_id ~= 0 then
				local debuff_id = tb_buff_effect[debuffeffect_id].buff_id
				SpelladdBuff(creature, debuff_id, creature, debuffeffect_id, 200)
			end
			local creatureInfo = UnitInfo:new{ptr = creature}
			-- 标识为boss怪
			creatureInfo:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
		end
	end
end

-- 个人BOSS结束了
function InstancePrivateBoss:IsEnd()
	return self:GetMapQuestEndTime() > 0 and self:GetMapQuestEndTime() <= os.time()
end

--当副本状态发生变化时间触发
function InstancePrivateBoss:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		--10s后结束副本
		local timestamp = os.time() + self.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

--玩家加入地图
function InstancePrivateBoss:OnJoinPlayer(player)
	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--死亡了还进来，直接弹出去
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
		return
	end
	
	-- 结束时间到就不让进了
	if self:IsEnd() then
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
		return
	end
	
	playerInfo:ModifyHealth(playerInfo:GetMaxHealth())
	playerInfo:ChangeToFamilyMode()
end

--当玩家离开时触发
function InstancePrivateBoss:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	local buffEffectId = self:GetBuffeffectId()
	if buffEffectId ~= 0 then
		local buff_id = tb_buff_effect[buffEffectId].buff_id
		unitLib.RemoveBuff(player,buff_id)
	end
	
	local playerInfo = UnitInfo:new{ptr = player}
	
	playerInfo:SetLastInstanceParam(self:GetPrivateBossId())
end

-- 当玩家死亡后
function InstancePrivateBoss:OnPlayerDeath(player)
	-- 死亡立马复活并弹出去
	--unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
	--mapLib.ExitInstance(self.ptr, player)
	--self:SetMapState(self.STATE_FAIL)
	self:instanceFail()
end

function InstancePrivateBoss:onBossDead()
	self:SetMapState(self.STATE_FINISH)
	
	self:sendReward()
	
	
end

-- 发放奖励
function InstancePrivateBoss:sendReward()
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	for _, unit_player in ipairs(allPlayers) do
		local playerInfo = UnitInfo:new {ptr = unit_player}
		local dict = {}
		-- 获得奖励
		local id = self:GetPrivateBossId()
		local dropId = tb_private_boss_info[id]["dropid_"..getJobIndxByGender(playerInfo:GetGender())]
		DoRandomDropTable({dropId}, dict)
		PlayerAddRewards(unit_player, dict, MONEY_CHANGE_PRIVATE_BOSS, LOG_ITEM_OPER_TYPE_PRIVATE_BOSS)
		
		local list = Change_To_Item_Reward_Info(dict, true)
		
		playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, INSTANCE_SUB_TYPE_PRIVATE_BOSS, '')
		
		playerLib.SendToAppdDoSomething(unit_player, SCENED_APPD_PRIVATE_BOSS_WIN,id)
	end
end


--AI_PrivateBoss
-------------------------私人boss---------------------------
AI_PrivateBoss = class("AI_PrivateBoss", AI_Base)
AI_PrivateBoss.ainame = "AI_PrivateBoss"

--死亡
function AI_PrivateBoss:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local instanceInfo = InstancePrivateBoss:new{ptr = map_ptr}
	instanceInfo:onBossDead()
	
	-- 更新杀怪进度
	local ownerInfo = UnitInfo:new {ptr = owner}
	local entry = ownerInfo:GetEntry()
	local updated = instanceInfo:OneMonsterKilled(entry)
	
	return 0
end

return InstancePrivateBoss