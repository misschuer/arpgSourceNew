InstanceFactionBossDefense = class("InstanceFactionBossDefense", InstanceInstBase)

InstanceFactionBossDefense.Name = "InstanceFactionBossDefense"
InstanceFactionBossDefense.FACTION_BOSS_NAME = "faction_bossdefense"	--boss����
InstanceFactionBossDefense.exit_time = 10
InstanceFactionBossDefense.start_time = 5


--�����ȼ�
function InstanceFactionBossDefense:GetBuildingLv()
	return self:GetUInt32(FACTION_BOSSDEFENSE_INSTANCE_FIELD_BUILDING_LV) 
end

function InstanceFactionBossDefense:SetBuildingLv(val)
	self:SetUInt32(FACTION_BOSSDEFENSE_INSTANCE_FIELD_BUILDING_LV, val) 
end

--�����index
function InstanceFactionBossDefense:GetIndex()
	return self:GetUInt32(FACTION_BOSSDEFENSE_INSTANCE_FIELD_INDEX) 
end

function InstanceFactionBossDefense:SetIndex(val)
	self:SetUInt32(FACTION_BOSSDEFENSE_INSTANCE_FIELD_INDEX, val) 
end

--�����id
function InstanceFactionBossDefense:GetPoolId()
	return self:GetUInt32(FACTION_BOSSDEFENSE_INSTANCE_FIELD_POOL_ID) 
end

function InstanceFactionBossDefense:SetPoolId(val)
	self:SetUInt32(FACTION_BOSSDEFENSE_INSTANCE_FIELD_POOL_ID, val) 
	self:SetUInt32(MAP_INT_FIELD_RESERVE2, val)
end

--����hp
function InstanceFactionBossDefense:GetHp()
	return self:GetUInt32(FACTION_BOSSDEFENSE_INSTANCE_FIELD_HP) 
end

function InstanceFactionBossDefense:SetHp(val)
	self:SetUInt32(FACTION_BOSSDEFENSE_INSTANCE_FIELD_HP, val) 
end

--���guid
function InstanceFactionBossDefense:GetPlayerGuid()
	return self:GetStr(FACTION_BOSSDEFENSE_INSTANCE_FIELD_PLAYER_GUID) 
end

function InstanceFactionBossDefense:SetPlayerGuid(val)
	self:SetStr(FACTION_BOSSDEFENSE_INSTANCE_FIELD_PLAYER_GUID, val) 
end

--����guid
function InstanceFactionBossDefense:GetFactionGuid()
	return self:GetStr(FACTION_BOSSDEFENSE_INSTANCE_FIELD_FACTION_GUID) 
end

function InstanceFactionBossDefense:SetFactionGuid(val)
	self:SetStr(FACTION_BOSSDEFENSE_INSTANCE_FIELD_FACTION_GUID, val) 
end

function InstanceFactionBossDefense:ctor(  )
	
end

--��ʼ���ű�����
function InstanceFactionBossDefense:OnInitScript(  )
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	InstanceInstBase.OnInitScript(self)					--���û���
	self:parseGeneralId()
	
	
	--self:SetMapEndTime(os.time() + self.DURATION_TIME)	--30���Ӻ����
	
end

function InstanceFactionBossDefense:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	local params = string.split(generalId, '|')
	
	local player_guid = params[1]
	local faction_guid = params[2]
	
	local building_lv	= tonumber(params[ 3 ])
	local index 		= tonumber(params[ 4 ])
	local pool_id 		= tonumber(params[ 5 ])
	local hp 			= tonumber(params[ 6 ])
	
	local base_config = tb_faction_bossdefense_base[building_lv]
	local point_config = tb_faction_bossdefense_point[index+1]
	local pool_config = tb_faction_bossdefense_pool[pool_id]
	
	--�������
	self:SetPlayerGuid(player_guid)
	self:SetFactionGuid(faction_guid)
	self:SetBuildingLv(building_lv)
	self:SetIndex(index)
	self:SetPoolId(pool_id)
	self:SetHp(hp)
	--����boss
	local entry = pool_config.entry
	local creature = mapLib.AddCreature(self.ptr, {
			templateid = entry, x = point_config.enemy_pos[1], y = point_config.enemy_pos[2], 
			active_grid = true, alias_name = InstanceFactionBossDefense.FACTION_BOSS_NAME, ainame = "AI_faction_bossdefense", npcflag = {}
		}
	)
	local bossUnit = UnitInfo:new{ptr = creature}
	
	bossUnit:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
	
	
	local start_stamp = os.time() + InstanceFactionBossDefense.start_time
	self:SetMapStartTime(start_stamp)
	
	self:SetMapEndTime(start_stamp + point_config.time_limit + InstanceFactionBossDefense.exit_time)
	
	self:SetMapQuestEndTime(start_stamp + point_config.time_limit)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, start_stamp + point_config.time_limit)
	self:AddTimeOutCallback('OnMosterReset', os.time() + 1)
	--outFmtDebug('============================= %s', tostring(guid))
	--self:SetFactionGuid(guid)
	
	-- ˢ������
	local mapQuest = pool_config.quests[1]
	-- �Ӹ�������
	InstanceInstBase.OnAddQuests(self, {mapQuest})
end

function InstanceFactionBossDefense:DoMapBuffBonus(unit)
	if GetUnitTypeID(unit) == TYPEID_PLAYER then
		local building_lv = self:GetBuildingLv()
		local base_config = tb_faction_bossdefense_base[building_lv]
		local buffEffectId = base_config.buffeffect_id
		local buff_id = tb_buff_effect[buffEffectId].buff_id
		
		SpelladdBuff(unit, buff_id, unit, buffEffectId, 65535)
	end
end

function InstanceFactionBossDefense:instanceFail()
	self:SetMapState(self.STATE_NOTPASS)
end

--������״̬�����仯ʱ�䴥��
function InstanceFactionBossDefense:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_NOTPASS then
		--10s���������
		--ʧ�ܲ��뽱��
		if tostate == self.STATE_NOTPASS then
			local allPlayers = mapLib.GetAllPlayer(self.ptr)
			if allPlayers[1] then
				self:OnJoinReward(allPlayers[1])
			end
		end
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceFactionBossDefense.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(os.time())
	end
end

--��Ҽ����ͼ
function InstanceFactionBossDefense:OnJoinPlayer(player)
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

function InstanceFactionBossDefense:OnMosterReset()
	local boss = mapLib.AliasCreature(self.ptr, InstanceFactionBossDefense.FACTION_BOSS_NAME)
	local bossUnit = UnitInfo:new{ptr = boss}
	if bossUnit then
		--outFmtDebug("========boss hp1 %d",bossUnit:GetHealth())
		bossUnit:ModifyHealth(self:GetHp()- bossUnit:GetMaxHealth())
		--outFmtDebug("========boss hp2 %d",bossUnit:GetHealth())
		--bossUnit:SetUInt32(UNIT_FIELD_DAMAGE,1000)
		
		
	end
end

--������뿪ʱ����
function InstanceFactionBossDefense:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	self:OnBossDefenseLeave()
	unitLib.RemoveBuff(player,BUFF_ALLATTR)
	local playerInfo = UnitInfo:new{ptr = player}
	
	playerInfo:SetLastInstanceParam(self:GetIndex())
	
	if self:GetMapState() == self.STATE_START then
		if player then
			--self:OnJoinReward(player)
		end
		return
	end
end

function InstanceFactionBossDefense:OnPlayerDeath(player)
	self:SetMapState(self.STATE_NOTPASS)
end

function InstanceFactionBossDefense:CheckQuestAfterTargetUpdate(isTimeout)	
	return false
end



--���ﲻ�ܸ�����Բ�����
function InstanceFactionBossDefense:DoRespawn( player,cur_map_id,respwan_map,respwan_type,respwan_x,respwan_y )
	
end

--��ɱboss �����ɱ����
function InstanceFactionBossDefense:OnBossDefenseWin()
	local pool_id = self:GetPoolId()
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	
	if not allPlayers[1] then
		return
	end
	local player = allPlayers[1]
	
	--call_appd_faction_bossdefense_win(faction_guid,player_guid,pool_id)
	local pool_config = tb_faction_bossdefense_pool[pool_id]
	local drop_id1 = pool_config.kill_drop
	local drop_id2 = pool_config.join_drop
	--local data = self:RandomReward(player, {drop_id1,drop_id2}, {})
	--self:SetMapReward(data)
	local playerInfo = UnitInfo:new {ptr = player}
	local dict = {}
	DoRandomDropTable({drop_id1,drop_id2}, dict)
	PlayerAddRewards(player, dict, MONEY_CHANGE_FACTION_BOSSDEFENSE, LOG_ITEM_OPER_TYPE_FACTION_BOSSDEFENSE)
	-- ɨ���Ľ������
	local list = Change_To_Item_Reward_Info(dict, true)
	
	playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list,INSTANCE_SUB_TYPE_FACTION_BOSSDEFENSE,"")
end

--�뿪 ������
function InstanceFactionBossDefense:OnBossDefenseLeave()
	--call_(faction_guid,index,pool_id,hp)
	local faction_guid = self:GetFactionGuid()
	local player_guid = self:GetPlayerGuid()
	local pool_id = self:GetPoolId()
	local index = self:GetIndex()
	local hp = self:GetHp()
	call_appd_faction_bossdefense_leave(faction_guid,player_guid,index,pool_id,hp)
end

--���뽱��
function InstanceFactionBossDefense:OnJoinReward(player)
	local pool_id = self:GetPoolId()
	local pool_config = tb_faction_bossdefense_pool[pool_id]
	local drop_id = pool_config.join_drop
	--local data = self:RandomReward(player, {drop_id}, {})
	--self:SetMapReward(data)
	
	local playerInfo = UnitInfo:new {ptr = player}
	local dict = {}
	DoRandomDropTable({drop_id}, dict)
	PlayerAddRewards(player, dict, MONEY_CHANGE_FACTION_BOSSDEFENSE, LOG_ITEM_OPER_TYPE_FACTION_BOSSDEFENSE)
	-- ɨ���Ľ������
	local list = Change_To_Item_Reward_Info(dict, true)
	
	playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list,INSTANCE_SUB_TYPE_FACTION_BOSSDEFENSE,"")
end

-----------------------------------------------------------------------------
--------------------------------���ɵ���boss ai------------------------------
AI_faction_bossdefense = class("AI_faction_bossdefense", AI_Base)
AI_faction_bossdefense.ainame = "AI_faction_bossdefense"

--����
function AI_faction_bossdefense:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	local playerInfo = UnitInfo:new{ptr = killer_ptr}	
	
	local instanceInfo = InstanceFactionBossDefense:new{ptr = map_ptr}
	instanceInfo:SetMapState(instanceInfo.STATE_FINISH)
	instanceInfo:OnBossDefenseWin()
	
	
	-- ����ɱ�ֽ���
	local ownerInfo = UnitInfo:new {ptr = owner}
	local entry = ownerInfo:GetEntry()
	local updated = instanceInfo:OneMonsterKilled(entry)
	
	-- ���½���
	if updated then
		--instanceInfo:AfterProcessUpdate(killer_ptr)
	end
	
	return 0
end

-- �ܵ��˺���
function AI_faction_bossdefense:DamageDeal( owner, unit, damage)

	local bossInfo = UnitInfo:new{ptr = owner}

	local currHealth = bossInfo:GetHealth()
	local maxHealth  = bossInfo:GetMaxHealth()
	
	local map_ptr = unitLib.GetMap(owner)
	local instanceInfo = InstanceFactionBossDefense:new{ptr = map_ptr}
	
	
	if damage > 0 then
		
		instanceInfo:SetHp(currHealth)
		
	else
		--mapLib.ClearFieldBossDamage(map_ptr)
	end
end

return InstanceFactionBossDefense