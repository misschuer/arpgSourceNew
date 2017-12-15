InstanceWorldRisk = class("InstanceWorldRisk", InstanceInstBase)

InstanceWorldRisk.Name = "InstanceWorldRisk"
InstanceWorldRisk.exit_time = 10
InstanceWorldRisk.broadcast_nogrid = 1
InstanceWorldRisk.player_auto_respan = 3

function InstanceWorldRisk:ctor(  )
	
end

--��ʼ���ű�����
function InstanceWorldRisk:OnInitScript(  )
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	InstanceInstBase.OnInitScript(self) --���û���
	
	self:parseGeneralId()

	-- �ӽ���ʱ��
	local timestamp = os.time() + 180
	self:SetMapQuestEndTime(timestamp)
	self:SetMapEndTime(timestamp)
end


function InstanceWorldRisk:parseGeneralId()
	local generalId = self:GetMapGeneralId()
	local params = string.split(generalId, '#')
	self:SetUInt32(TRIAL_INSTANCE_FIELD_SECTION_ID, tonumber(params[ 2 ]))
	
	outFmtDebug("InstanceWorldRisk:parseGeneralId generalId %d",tonumber(params[ 2 ]))
end

-- �˳�����ʱ����׼���˳�
function InstanceWorldRisk:prepareToLeave()
	local seciontId = self:getSectionId()

	if tb_risk_data[seciontId].is_boss_section == 0 then
		mapLib.ExitInstance(self.ptr)
	else
		local allPlayers = mapLib.GetAllPlayer(self.ptr)
		for _, player in pairs(allPlayers) do
			local playerInfo = UnitInfo:new {ptr = player}
			playerInfo:teleportWorldRisk()
		end
	end
end


function InstanceWorldRisk:getSectionId()
	return self:GetUInt32(TRIAL_INSTANCE_FIELD_SECTION_ID)
end


--������״̬�����仯ʱ�䴥��
function InstanceWorldRisk:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		--10s���������
		local timestamp = os.time() + InstanceWorldRisk.exit_time
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

-- �ж��Ƿ����˳�����
function InstanceWorldRisk:DoPlayerExitInstance(player)
	return 1
end

--��Ҽ����ͼ
function InstanceWorldRisk:OnJoinPlayer(player)
	InstanceInstBase.OnJoinPlayer(self, player)
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
	end

	-- ˢ�¹���
	local seciontId = self:getSectionId()
	if tb_risk_data[seciontId].is_boss_section == 0 then
		self:OnRefreshMonsterInit(player)
	else
		self:refreshBoss()
	end
end

function InstanceWorldRisk:hasNextMonster()
	local seciontId = self:getSectionId()
	local count = #tb_risk_data[seciontId].monsters
	if self:getRefreshCount() >= count then
		self:resetRefreshCursor()
	end
	return true
end

function InstanceWorldRisk:nextMonsterInfoIndx()
	local cursor = self:getRefreshCount()
	self:oneRefreshed()
	--return self:GetByte(TRIAL_INSTANCE_FIELD_ORDER, cursor)
	return cursor+1
end

function InstanceWorldRisk:oneRefreshed()
	self:AddUInt32(TRIAL_INSTANCE_FIELD_CURSOR, 1)
end

function InstanceWorldRisk:resetRefreshCursor()
	self:SetUInt32(TRIAL_INSTANCE_FIELD_CURSOR, 0)
end

function InstanceWorldRisk:getRefreshCount()
	return self:GetUInt32(TRIAL_INSTANCE_FIELD_CURSOR)
end

function InstanceWorldRisk:isSettedOrder()
	return self:GetByte(TRIAL_INSTANCE_FIELD_ORDER, 0) > 0
end

function InstanceWorldRisk:onSetOrder(player_ptr)
	if not self:isSettedOrder() then
		local seciontId = self:getSectionId()
		local count = #tb_risk_data[seciontId].monsters
		
		local playerInfo = UnitInfo:new {ptr = player_ptr}
		if tb_risk_data[seciontId].is_boss_section == 0 and playerInfo:GetRiskMonsterCount() == 0 then
			playerInfo:SetRiskMonsterCount(tb_risk_data[seciontId].count)
		end
	end
end

--ˢ��
function InstanceWorldRisk:OnRefreshMonsterInit(player)
	self:onSetOrder(player)
	self:refresh()
end

function InstanceWorldRisk:SetCreaturePro(creatureInfo, pros, bRecal, mul)
	local idx = creatureInfo:GetUInt32(UNIT_INT_FIELD_RISK_CREATURE_ID)
	local config = tb_creature_worldrisk[idx]
	if config then
		Instance_base.SetCreaturePro(self, creatureInfo, config.pro, bRecal, mul)
	else
		Instance_base.SetCreaturePro(self, creatureInfo, pros, bRecal, mul)
	end
end

function InstanceWorldRisk:DoGetCreatureBaseExp(creature, owner)
	local idx = binLogLib.GetUInt32(creature, UNIT_INT_FIELD_RISK_CREATURE_ID)
	local config = tb_creature_worldrisk[idx]
	
	return config.exp
end

function InstanceWorldRisk:refreshBoss()
	if self:GetUInt32(TRIAL_INSTANCE_FIELD_BOSS_REFRESHED) > 0 then
		return
	end
	self:SetUInt32(TRIAL_INSTANCE_FIELD_BOSS_REFRESHED, 1)
	
	local seciontId = self:getSectionId()
	local monsters = tb_risk_data[seciontId].monsters
	local info = monsters[ 1 ]
	
	local cx = info[ 3 ]
	local cy = info[ 4 ]
	local riskCreatureId = info[ 1 ]
	local entry = tb_creature_worldrisk[riskCreatureId].entry
	
	local creature = mapLib.AddCreature(self.ptr, {
		templateid = entry, x = cx, y = cy,
		active_grid = true, ainame = 'AI_worldRiskBoss', npcflag = {},
		riskId = riskCreatureId
	})
end

function InstanceWorldRisk:refresh()
	--�޸�Ϊ����riskCreatureId ����
	local curr, currEntry = mapLib.GetCreatureEntryCount(self.ptr)
	local offs = tb_risk_base[ 1 ].pos_offset
	
	while (curr < 2) do
		if self:hasNextMonster() then
			local indx = self:nextMonsterInfoIndx()
			local seciontId = self:getSectionId()
			local monsters = tb_risk_data[seciontId].monsters
			local info = monsters[indx]
			
			local cx = info[ 3 ]
			local cy = info[ 4 ]
			local riskCreatureId = info[ 1 ]
			local entry = tb_creature_worldrisk[riskCreatureId].entry
			local num = info[ 2 ]

			local width = offs * 2 + 1
			local grids = width * width
			
			-- ���Ͻǵ������
			local lx = cx - offs
			local ly = cy - offs
			
			if currEntry ~= riskCreatureId then
				local idTable = GetRandomIndexTable(grids, num)
				for _, indx in pairs(idTable) do
					local id = indx - 1
					local offx = id % width
					local offy = id / width
					local bornX = lx + offx
					local bornY = ly + offy
					
					local creature = mapLib.AddCreature(self.ptr, {
						templateid = entry, x = bornX, y = bornY,
						active_grid = true, ainame = "AI_worldRisk", npcflag = {},
						riskId = riskCreatureId
					})
				end
				curr = curr + 1
			else
				--outFmtError("############# InstanceWorldRisk:refresh every wave cannot be same entry")
			end
		end
	end
end

function InstanceWorldRisk:oneTrialMonsterKilled(player_ptr,dict)
	local playerInfo = UnitInfo:new {ptr = player_ptr}
	if playerInfo:GetTypeID() == TYPEID_PLAYER then
		playerInfo:AddRiskMonsterKilledCount()
		PlayerAddRewards(player_ptr, dict, MONEY_CHANGE_TRIAL_INSTANCE_REWARD, LOG_ITEM_OPER_TYPE_TRIAL_INSTANCE_REWARD, 0)
	else
		outFmtInfo("##### entry %d kill one monster", playerInfo:GetEntry())
	end
	-- �ж��Ƿ���Ҫˢ��һ��
	self:refresh()
end

function InstanceWorldRisk:onBossLoot(player_ptr, dict)
	local playerInfo = UnitInfo:new {ptr = player_ptr}
	local seciontId = self:getSectionId()
	playerInfo:passSection(seciontId)

	PlayerAddRewards(player_ptr, dict, MONEY_CHANGE_TRIAL_INSTANCE_REWARD, LOG_ITEM_OPER_TYPE_TRIAL_INSTANCE_REWARD, 0)

	-- ѹ���ַ���
	local reward = {}
	for itemId, count in pairs(dict) do
		table.insert(reward, itemId..":"..count)
	end
	local data = string.join(",", reward)
	
	self:SetMapReward(data)
	
	-- �������
	self:SetMapState(self.STATE_FINISH)
	
	-- ɨ���Ľ������
	local list = Change_To_Item_Reward_Info(dict, true)
	playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, INSTANCE_SUB_TYPE_RISK, '')
end

--������뿪ʱ����
function InstanceWorldRisk:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	if not is_offline then
		self:RemoveTimeOutCallback(self.Leave_Callback)
	end
	self:SetMapEndTime(os.time())
end

--����������󴥷�()
function InstanceWorldRisk:OnPlayerDeath(player)
	local seciontId = self:getSectionId()
	local playerInfo = UnitInfo:new {ptr = player}
	
	if tb_risk_data[seciontId].is_boss_section == 1 then
		self:SetMapState(self.STATE_FAIL)
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, {}, INSTANCE_SUB_TYPE_RISK, '')
		return
	end
	
	local mapid = self:GetMapId()
	local waitTimeList = tb_map[mapid].rebornWaitTime
	local sec = waitTimeList[ 1 ]
	self:SetUInt32(TRIAL_INSTANCE_FIELD_LAST_RANDOM_TIMESTAMP, os.time() + sec)
	self:OnSendDeathInfo(playerInfo, '', '')
end

-- �����ȸ���ʱ����
function InstanceWorldRisk:AfterProcessUpdate(player)
	
end

function InstanceWorldRisk:GetCostTimeCD(playerInfo)
	return self:GetUInt32(TRIAL_INSTANCE_FIELD_LAST_RANDOM_TIMESTAMP)
end

-------------------------------- BOSS
AI_worldRiskBoss = class("AI_worldRiskBoss", AI_Base)
AI_worldRiskBoss.ainame = "AI_worldRiskBoss"
--[[
--����
function AI_worldRiskBoss:JustDied( map_ptr,owner,killer_ptr )	

	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	local mapid = mapLib.GetMapID(map_ptr)
	local instanceInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	
	--instanceInfo:onBossDied(killer_ptr)
	
	return 0
end
--]]

--����ս��Ʒ
function AI_worldRiskBoss:LootAllot(owner, player, killer, drop_rate_multiples, boss_type, fcm)
	local map_ptr = unitLib.GetMap(owner)
	local mapid = mapLib.GetMapID(map_ptr)
	local instanceInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	
	local idx = binLogLib.GetUInt32(owner, UNIT_INT_FIELD_RISK_CREATURE_ID)
	local info = tb_creature_worldrisk[idx]
	local drop_ids = info.droprid
	local dict = {}
	if #drop_ids > 0 then
		for i = 1, #drop_ids do
			local dropId = drop_ids[i]
			DoRandomDrop(dropId, dict)
		end	
	end
	
	instanceInfo:onBossLoot(player, dict)
end


----------------------------- С��----------------------------
AI_worldRisk = class("AI_worldRisk", AI_Base)
AI_worldRisk.ainame = "AI_worldRisk"
--����
function AI_worldRisk:JustDied( map_ptr,owner,killer_ptr )	
	
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local mapid = mapLib.GetMapID(map_ptr)
	local instanceInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	local idx = binLogLib.GetUInt32(owner, UNIT_INT_FIELD_RISK_CREATURE_ID)
	local info = tb_creature_worldrisk[idx]
	
	local dict = {}
	for _,item_info in ipairs(info.reward) do
		dict[item_info[1]] = item_info[2]
	end
	instanceInfo:oneTrialMonsterKilled(killer_ptr,dict)
	
	return 0
end

--����ս��Ʒ
function AI_worldRisk:LootAllot(owner, player, killer, drop_rate_multiples, boss_type, fcm)
	local map_ptr = unitLib.GetMap(owner)
	local mapid = mapLib.GetMapID(map_ptr)
	local instanceInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	
	local idx = binLogLib.GetUInt32(owner, UNIT_INT_FIELD_RISK_CREATURE_ID)
	local info = tb_creature_worldrisk[idx]
	local drop_ids = info.droprid
	local dict = {}
	if #drop_ids > 0 then
		for i = 1, #drop_ids do
			local dropId = drop_ids[i]
			DoRandomDrop(dropId, dict)
		end	
	end
	
	PlayerAddRewards(player, dict, MONEY_CHANGE_TRIAL_INSTANCE_REWARD, LOG_ITEM_OPER_TYPE_TRIAL_INSTANCE_REWARD, 1)
end

return InstanceWorldRisk