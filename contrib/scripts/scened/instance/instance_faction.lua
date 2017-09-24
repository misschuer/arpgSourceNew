InstanceFaction = class("InstanceFaction", Instance_base)
--[[
InstanceFaction.Name = "InstanceFaction"
InstanceFaction.REFRESH_CREATURE_INTERNAL = 1000	--1s���һ��
InstanceFaction.RESPAWN_TIME = 10000				--10�븴��ʱ��
InstanceFaction.DURATION_TIME = 1800				--��������ʱ��
InstanceFaction.FACTION_BOSS_NAME = "faction_boss"	--����boss����
InstanceFaction.FACTION_MONSTER_NAME = "faction_monster"	--���ɹ�������
InstanceFaction.FACTION_TARGET_NAME = "faction_target"	--���ɱ���Ŀ������


InstanceFaction.FAIL_TYPE_TARGET_LOSE = 1	--Ŀ�걣��ʧ��
InstanceFaction.FAIL_TYPE_TIME_OUT = 2		--��ս��ʱʧ��

--���� Guid        = self:GetMapGeneralId()



--��ȡ����guid
function InstanceFaction:GetFactionGuid()
	return self:GetStr(FACTION_INSTANCE_FIELD_GUID) 
end
--���ü���guid
function InstanceFaction:SetFactionGuid(val)
	self:SetStr(FACTION_INSTANCE_FIELD_GUID, val) 
end

function InstanceFaction:ctor(  )
	
end

--��ʼ���ű�����
function InstanceFaction:OnInitScript(  )
	Instance_base.OnInitScript(self)					--���û���
	--self:SetMapEndTime(os.time() + self.DURATION_TIME)	--30���Ӻ����
	
	--�������guid
	self:parseGeneralId()
	
	--���Bossˢ�¼���
	mapLib.DelTimer(self.ptr, 'OnTimer_CheckRefreshBoss')
	mapLib.AddTimer(self.ptr, 'OnTimer_CheckRefreshBoss', self.REFRESH_CREATURE_INTERNAL)
	
	self:OnRefreshMonster()
	
	-- �ӽ���ʱ��
	local timestamp = os.time() + 180
	self:SetMapQuestEndTime(timestamp)
	self:SetMapEndTime(timestamp)
end

function InstanceFaction:parseGeneralId()
	local guid	= self:GetMapGeneralId()
	--outFmtInfo('============================= %s', tostring(guid))
	self:SetFactionGuid(guid)
end

-- �ж��Ƿ����˳�����
function InstanceFaction:DoPlayerExitInstance(player)
	return 0
end

--������״̬�����仯ʱ�䴥��
function InstanceFaction:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		--10s���������
		--self:SetMapEndTime(os.time() + 5)
	end
end

--��Ҽ����ͼ
function InstanceFaction:OnJoinPlayer(player)
	Instance_base.OnJoinPlayer(self, player)
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻�������ֱ�ӵ���ȥ
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
	end
end

--��ʱ���bossˢ��
function InstanceFaction:OnTimer_CheckRefreshBoss()
	local timenow = os.time()
	local faction = app.objMgr:getObj(self:GetFactionGuid())
	
	if not faction then
		--outFmtDebug('OnTimer_CheckRefreshBoss faction is nil')
		return true
	end

	local faction_lv = faction:GetFactionLevel()
	--boss���
	local boss_id = faction:GetChallengeBossId()
	local start_time = faction:GetChallengeBossStartTime()
	local boss_hp_rate = faction:GetChallengeBossHpRate()
	local boss_x,boss_y = faction:GetChallengeBossPos()
	local target_hp_rate = faction:GetProtectTargetHpRate()
	local target_x,target_y = faction:GetProtectTargetPos()
	
	if boss_id ~= 0 then
		local factionBossInfo = tb_faction_boss[boss_id]
		if factionBossInfo then
			if timenow >= start_time + factionBossInfo.wait_time and timenow <= start_time + factionBossInfo.wait_time + factionBossInfo.time then
				--ˢ��/��ԭboss hpΪ0��ˢ     targethp==0 �Ѿ�ʤ��
				local bossPtr = nil
				local targetPtr = nil
				if boss_hp_rate > 0 then
					local bossName = InstanceFaction.FACTION_BOSS_NAME
					local boss = mapLib.AliasCreature(self.ptr, bossName)
					if not boss then
						local bossConfig = tb_faction_boss[boss_id]
						local entry = bossConfig.entry
						local config = tb_creature_template[entry]
						local creature = mapLib.AddCreature(self.ptr, {
								templateid = entry, x = boss_x, y = boss_y, 
								active_grid = true, alias_name = bossName, ainame = "AI_faction_boss", npcflag = {}
							}
						)
						
						bossPtr = creature
						local bossUnit = UnitInfo:new{ptr = creature}
						if bossUnit and boss_hp_rate < 10000 then
							bossUnit:SetHealth(math.ceil(bossUnit:GetMaxHealth() * boss_hp_rate / 10000))
						end
						bossUnit:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
					else
						bossPtr = nil
						local bossUnit= UnitInfo:new{ptr = boss}
						if bossUnit then
							local currHealth = bossUnit:GetHealth()
							local maxHealth  = bossUnit:GetMaxHealth()
							local currX,currY = unitLib.GetPos(boss)
							bossUnit:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
							self:OnUpdateBossInfo(math.ceil(currHealth/maxHealth*10000),currX,currY)
						end
					end
				else
					--nothing
				end
				
				--����Ŀ���������/��ԭ
				if target_hp_rate > 0 then
					local targetName = InstanceFaction.FACTION_TARGET_NAME
					local target = mapLib.AliasCreature(self.ptr, targetName)
					if not target then
						local targetConfig = tb_faction_boss[boss_id]
						local entry = targetConfig.target_entry
						local config = tb_creature_template[entry]
						local creature = mapLib.AddCreature(self.ptr, {
								templateid = entry, x = target_x, y = target_y, 
								active_grid = true, alias_name = targetName, ainame = "AI_faction_target", npcflag = {}
							}
						)
						targetPtr = creature
						local targetUnit= UnitInfo:new{ptr = creature}
						if targetUnit and target_hp_rate < 10000 then
							targetUnit:SetHealth(math.ceil(targetUnit:GetMaxHealth() * target_hp_rate / 10000))
						end
						
						--creatureLib.SetMonsterHost(target, player)
					else
						targetPtr = target
						local targetUnit= UnitInfo:new{ptr = target}
						if targetUnit then
							local currHealth = targetUnit:GetHealth()
							local maxHealth  = targetUnit:GetMaxHealth()
							local currX,currY = unitLib.GetPos(target)
							self:OnUpdateTargetInfo(math.ceil(currHealth/maxHealth*10000),currX,currY)
						end
						--creatureLib.SetMonsterHost(target, player)
					end
				else
					--nothing
				end
				
				if bossPtr and targetPtr then
					--creatureLib.ModifyThreat(bossPtr, targetPtr, self.THREAT_V)
					creatureLib.ModifyThreat(bossPtr, targetPtr, self.THREAT_V)
				end
				
			elseif timenow > start_time + factionBossInfo.wait_time + factionBossInfo.time then
				--��սʧ�ܽ��� bosshp > 0      targethp==0  �Ѿ�ʤ��
				if boss_hp_rate > 0 then
					local bossName = InstanceFaction.FACTION_BOSS_NAME
					local boss = mapLib.AliasCreature(self.ptr, bossName)
					if boss then
						
						mapLib.RemoveWorldObject(self.ptr,boss)
					end
					local targetName = InstanceFaction.FACTION_TARGET_NAME
					local target = mapLib.AliasCreature(self.ptr, targetName)
					if target then
						
						mapLib.RemoveWorldObject(self.ptr,target)
					end
					
					--����
					self:OnChallengeFail(InstanceFaction.FAIL_TYPE_TIME_OUT)
				else
					--nothing
				end
				
			end
		end
	else
		local bossName = InstanceFaction.FACTION_BOSS_NAME
		local boss = mapLib.AliasCreature(self.ptr, bossName)
		if boss then
			
			mapLib.RemoveWorldObject(self.ptr,boss)
		end
		local targetName = InstanceFaction.FACTION_TARGET_NAME
		local target = mapLib.AliasCreature(self.ptr, targetName)
		if target then
			
			mapLib.RemoveWorldObject(self.ptr,target)
		end
	end
	
	
	
	return true
end
	
--ˢ��
function InstanceFaction:OnRefreshMonster()
	--Ұ�����
	local timenow = os.time()
	local faction = app.objMgr:getObj(self:GetFactionGuid())
	if not faction then
		return
	end
	local faction_lv = faction:GetFactionLevel()
	local startTime = self:GetMapCreateTime()
	if timenow - startTime > 2 then
		return
	end
	for id,config in pairs(tb_faction_monster) do

		local bornX = config.born_pos[1]
		local bornY = config.born_pos[2]
		local entry = config.monster_table[faction_lv][2]
		--local point = config.monster_table[faction_lv][3]
		local entryInfo	= tb_creature_template[entry]
		local born_time = 5
		
		local creature = mapLib.AddCreature(self.ptr, {
			templateid = entry, x = bornX, y = bornY, 
			active_grid = true,respan_time = born_time, alias_name = InstanceFaction.FACTION_MONSTER_NAME, ainame = "AI_faction_monster", npcflag = {}
		}
	)
		
	end
	local config = tb_bangpai_boss[self:GetFactionMapID()]
	if config == nil then 
		--ֱ�ӽ�������
		self:SetMapState(self.STATE_FAIL)
		return false
	end
	
	local boss = mapLib.AliasCreature(self.ptr, self.FACTION_BOSS_NAME)
	if not boss then
		local creature = mapLib.AddCreature(self.ptr, {templateid = config.boss_id, x = config.boss_point[1], y = config.boss_point[2], active_grid = true, alias_name = self.FACTION_BOSS_NAME, ainame = "AI_faction_boss", npcflag = {}})
		if creature then
			local creatureInfo = UnitInfo:new{ptr = creature}
			-- ��ʶΪboss��
			creatureInfo:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
			return false
		end	
	end
	return true
end

--��ս�ɹ�����
function InstanceFaction:OnChallengeWin()
	local faction_guid = self:GetFactionGuid()
	call_appd_faction_challenge_boss_win(faction_guid)
end

--��սʧ�ܴ���
function InstanceFaction:OnChallengeFail(fail_type)
	local faction_guid = self:GetFactionGuid()
	call_appd_faction_challenge_boss_fail(faction_guid,fail_type)
end

--������ƻ���
function InstanceFaction:OnAddTokenPoints(player_guid,points)
	local faction_guid = self:GetFactionGuid()
	call_appd_faction_add_token_points(faction_guid,player_guid,points)
end

--��boss����˺�
function InstanceFaction:OnBossDamaged(player_guid,damage)
	local faction_guid = self:GetFactionGuid()
	call_appd_faction_challenge_boss_damaged(faction_guid,player_guid,damage)
end

--ͬ��boss��Ϣ�����ɶ���
function InstanceFaction:OnUpdateBossInfo(hp_rate,x,y)
	local faction_guid = self:GetFactionGuid()
	call_appd_faction_update_boss_info(faction_guid,hp_rate,x,y)
end

--ͬ������Ŀ����Ϣ�����ɶ���
function InstanceFaction:OnUpdateTargetInfo(hp_rate,x,y)
	local faction_guid = self:GetFactionGuid()
	call_appd_faction_update_target_info(faction_guid,hp_rate,x,y)
end


--������뿪ʱ����
function InstanceFaction:OnLeavePlayer( player, is_offline)
	--self:SetMapEndTime(os.time())
	--RemoveNormalBuff(player,4)
	--RemoveNormalBuff(player,5)
end

function InstanceFaction:DoIsFriendly(killer_ptr, target_ptr)
	local killer_typeId = GetUnitTypeID(killer_ptr)
	local target_typeId = GetUnitTypeID(target_ptr)
	-- �����������
	if killer_typeId == TYPEID_PLAYER then
		if target_typeId == TYPEID_PLAYER or binLogLib.GetStr(target_ptr,UNIT_STRING_FIELD_ALIAS_NAME) == InstanceFaction.FACTION_TARGET_NAME then
			return 1
		end
		return 0
	end

	-- ������������
	if target_typeId == TYPEID_UNIT then
		if target_typeId == TYPEID_UNIT and binLogLib.GetStr(target_ptr,UNIT_STRING_FIELD_ALIAS_NAME) ~= InstanceFaction.FACTION_TARGET_NAME then
			return 1
		end
	end

	return 0
end
-----------------------------------------------------------------------------
--------------------------------���ɶ���boss ai------------------------------
AI_faction_boss = class("AI_faction_boss", AI_Base)
AI_faction_boss.ainame = "AI_faction_boss"

--����
function AI_faction_boss:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	--local playerInfo = UnitInfo:new{ptr = killer_ptr}	
	--local lv = playerInfo:GetFactionFbCount()
	--playerInfo:SetFactionFbCount(lv + 1)
	--local mapInfo = InstanceFaction:new{ptr = map_ptr}
	--mapInfo:SetMapState(mapInfo.STATE_FINISH)
	
	--��ս�ɹ�����
	local instanceInfo = InstanceFaction:new{ptr = map_ptr}
	instanceInfo:OnChallengeWin()
	return 0
end

-- �ܵ��˺���
function AI_faction_boss:DamageDeal( owner, unit, damage)

	local bossInfo = UnitInfo:new{ptr = owner}

	local currHealth = bossInfo:GetHealth()
	local maxHealth  = bossInfo:GetMaxHealth()
	
	local map_ptr = unitLib.GetMap(owner)
	local instanceInfo = InstanceFaction:new{ptr = map_ptr}
	local factionGuid = instanceInfo:GetFactionGuid()
	
	if damage > 0 then
		-- ����ǹ�����ҹ�����
		if GetUnitTypeID(unit) == TYPEID_UNIT then
			unit = creatureLib.GetMonsterHost(unit)
		end
		if unit then
			local unitInfo = UnitInfo:new {ptr = unit}
			local guid = unitInfo:GetPlayerGuid()
			

			instanceInfo:OnBossDamaged(guid,damage)

			--mapLib.AddFiledBossDamage(map_ptr, guid, damage)
			-- �μ�Ұ��BOSS
			--playerLib.SendToAppdDoSomething(unit, SCENED_APPD_JOIN_FIELD_BOSS, mapid)
		end
	else
		--mapLib.ClearFieldBossDamage(map_ptr)
	end
end


AI_faction_monster = class("AI_faction_monster", AI_Base)
AI_faction_monster.ainame = "AI_faction_monster"

--����
function AI_faction_monster:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	local creatureInfo = UnitInfo:new {ptr = owner}
	local entry = creatureInfo:GetEntry()
	local points = tb_creature_template[entry].faction_points

	
	--���ֽ���
	local playerInfo = UnitInfo:new{ptr = killer_ptr}
	local player_guid = playerInfo:GetPlayerGuid()
	
	local instanceInfo = InstanceFaction:new{ptr = map_ptr}
	instanceInfo:OnAddTokenPoints(player_guid,points)
	
	return 0
end

AI_faction_target = class("AI_faction_target", AI_Base)
AI_faction_target.ainame = "AI_faction_target"

--����
function AI_faction_target:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	--��սʧ�ܽ���
	local instanceInfo = InstanceFaction:new{ptr = map_ptr}
	instanceInfo:OnChallengeFail(InstanceFaction.FAIL_TYPE_TARGET_LOSE)
	
	return 0
end


--]]

return InstanceFaction