InstanceFactionTower = class("InstanceFactionTower", InstanceInstBase)

InstanceFactionTower.Name = "InstanceFactionTower"
InstanceFactionTower.FACTION_BOSS_NAME = "faction_boss_tower"	--boss����
InstanceFactionTower.exit_time = 10
InstanceFactionTower.RefreshOffset = 3;

--��ǰ����
function InstanceFactionTower:GetFloor()
	return self:GetInstanceLayer()
end

function InstanceFactionTower:SetFloor(val)
	self:SetInstanceLayer(val)
end

--���buff
function InstanceFactionTower:GetBuff()
	return self:GetUInt32(FACTION_TOWER_INSTANCE_FIELD_BUFF) 
end

function InstanceFactionTower:SetBuff(val)
	self:SetUInt32(FACTION_TOWER_INSTANCE_FIELD_BUFF, val) 
end

--����buff
function InstanceFactionTower:GetDebuff()
	return self:GetUInt32(FACTION_TOWER_INSTANCE_FIELD_DEBUFF) 
end

function InstanceFactionTower:SetDebuff(val)
	self:SetUInt32(FACTION_TOWER_INSTANCE_FIELD_DEBUFF, val) 
end

--����buff
function InstanceFactionTower:GetMonsterNum()
	return self:GetUInt32(FACTION_TOWER_INSTANCE_FIELD_MONSTER_NUM) 
end

function InstanceFactionTower:SetMonsterNum(val)
	self:SetUInt32(FACTION_TOWER_INSTANCE_FIELD_MONSTER_NUM, val) 
end

function InstanceFactionTower:AddMonsterNum(val)
	self:AddUInt32(FACTION_TOWER_INSTANCE_FIELD_MONSTER_NUM, val) 
end

function InstanceFactionTower:SubMonsterNum(val)
	if self:GetMonsterNum() > val then
		self:SubUInt32(FACTION_TOWER_INSTANCE_FIELD_MONSTER_NUM, val) 
	else
		self:SetMonsterNum(0)
	end
end


function InstanceFactionTower:ctor(  )
	
end

--��ʼ���ű�����
function InstanceFactionTower:OnInitScript(  )
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	InstanceInstBase.OnInitScript(self)					--���û���
	self:parseGeneralId()
	
end

-- �˳�����ʱ���˼�����ս��һ��
function InstanceFactionTower:prepareToLeave()
	if self:GetMapState() == self.STATE_FAIL or not tb_faction_tower_floor[self:GetFloor()+1]then
		mapLib.ExitInstance(self.ptr)
	else
		local allPlayers = mapLib.GetAllPlayer(self.ptr)
		for _, player in pairs(allPlayers) do
			--����Ӧ�÷����н����ж�
			playerLib.SendToAppdDoSomething(player, SCENED_APPD_ENTER_FACTION_TOWER_INSTANCE, 0)
		end
	end
end

function InstanceFactionTower:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	local params = string.split(generalId, '|')
	
	local floor		= tonumber(params[ 1 ])
	local buffeffect_id	= tonumber(params[ 2 ])
	local debuffeffect_id	= tonumber(params[ 3 ])
	
	
	self:SetFloor(floor)
	self:SetBuff(buffeffect_id)
	self:SetDebuff(debuffeffect_id)
	self:SetMonsterNum(0)
	
	local floor_config = tb_faction_tower_floor[floor]
	local monsters = floor_config.monsters
	local debuff_id = 0
	if debuffeffect_id ~= 0 then
		debuff_id = tb_buff_effect[debuffeffect_id].buff_id
	end
	
	for _,v in pairs(monsters) do
		local entry = v[1]
		local count = v[2]
		local born_x = v[3]
		local born_y = v[4]
		local boss_flag = v[5]
		
		for i = 1,count do
			local x = born_x + randInt(0, self.RefreshOffset)
			local y = born_y + randInt(0, self.RefreshOffset)
			
			local creature = mapLib.AddCreature(self.ptr, 
							{templateid = entry, x = x, y = y, active_grid = true, alias_name = self.FACTION_BOSS_NAME, ainame = "AI_faction_tower", npcflag = {}})
			--creature
			if debuffeffect_id ~= 0 then
				SpelladdBuff(creature, debuff_id, creature, debuffeffect_id, 65535)
			end
			
			local bossUnit = UnitInfo:new{ptr = creature}
			if boss_flag == 1 then
				bossUnit:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
			end
			self:AddMonsterNum(1)
		end
		
	end
	
	self:SetMapEndTime(os.time() + floor_config.time_limit + self.exit_time)
	
	self:SetMapQuestEndTime(os.time() + floor_config.time_limit)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, os.time() + floor_config.time_limit)
	
	-- �Ӹ�������
	InstanceInstBase.OnAddQuests(self, floor_config.quests)
	
end

function InstanceFactionTower:DoMapBuffBonus(unit)
	if GetUnitTypeID(unit) == TYPEID_PLAYER then
		local buffEffectId = self:GetBuff()
		local buff_id = tb_buff_effect[buffEffectId].buff_id
		
		SpelladdBuff(unit, buff_id, unit, buffEffectId, 65535)
	end
end

--������״̬�����仯ʱ�䴥��
function InstanceFactionTower:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + self.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

--��Ҽ����ͼ
function InstanceFactionTower:OnJoinPlayer(player)
	InstanceInstBase.OnJoinPlayer(self, player)
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() or self:GetMapState() ~= self.STATE_START then
		--�����˻�������ֱ�ӵ���ȥ
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
	end
	
	playerInfo:ModifyHealth(playerInfo:GetMaxHealth())
	playerInfo:ChangeToFamilyMode()
end

--������뿪ʱ����
function InstanceFactionTower:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	unitLib.RemoveBuff(player,BUFF_ALLATTR)
end

function InstanceFactionTower:OnPlayerDeath(player)
	self:SetMapState(self.STATE_FAIL)
end

function InstanceFactionTower:CheckQuestAfterTargetUpdate(isTimeout)	
	return false
end

--���ﲻ�ܸ�����Բ�����
function InstanceFactionTower:DoRespawn( player,cur_map_id,respwan_map,respwan_type,respwan_x,respwan_y )
	
end

function InstanceFactionTower:OnMonsterDie()
	self:SubMonsterNum(1)
	if self:GetMonsterNum() == 0 then
		local floor = self:GetFloor()
		
		local floor_config = tb_faction_tower_floor[floor]
		local reward = floor_config.firstpass_reward
		
		local dict = {}
		for _,v in pairs(reward) do
			if dict[v[1]] then
				dict[v[1]] = dict[v[1]] + v[2]
			else
				dict[v[1]] = v[2]
			end
		end
		
		local allPlayers = mapLib.GetAllPlayer(self.ptr)
		if allPlayers[1] then
			PlayerAddRewards(allPlayers[1], dict, MONEY_CHANGE_FACTION_TOWER, LOG_ITEM_OPER_TYPE_FACTION_TOWER)
			local list = Change_To_Item_Reward_Info(dict, true)
			local playerInfo = UnitInfo:new {ptr = allPlayers[1]}
			playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list,INSTANCE_SUB_TYPE_FACTION_TOWER,"")
			
			playerLib.SendToAppdDoSomething(allPlayers[1], SCENED_APPD_FACTION_TOWER_WIN, floor)
		end
		
		self:SetMapState(self.STATE_FINISH)
	end
end

-----------------------------------------------------------------------------
--------------------------------�����޾�Զ�� ai------------------------------
AI_faction_tower = class("AI_faction_tower", AI_Base)
AI_faction_tower.ainame = "AI_faction_tower"

--����
function AI_faction_tower:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local instanceInfo = InstanceFactionTower:new{ptr = map_ptr}
	instanceInfo:OnMonsterDie()
	
	
	-- ����ɱ�ֽ���
	local ownerInfo = UnitInfo:new {ptr = owner}
	local entry = ownerInfo:GetEntry()
	local updated = instanceInfo:OneMonsterKilled(entry)
	
	-- ���½���
	if updated then
		--outFmtDebug("################OneMonsterKilled scuuess :%d",entry)
		--instanceInfo:AfterProcessUpdate(killer_ptr)
	else
		--outFmtDebug("===================OneMonsterKilled fail :%d",entry)
	end
	
	
	return 0
end

return InstanceFactionTower