InstanceStageBase = class("InstanceStageBase", InstanceInstBase)

InstanceStageBase.Name = "InstanceStageBase"
InstanceStageBase.exit_time = 10
--ˢ������ƫ��ֵ
InstanceStageBase.RefreshOffset = 3;

InstanceStageBase.MonsterRefreshInterval = 500

function InstanceStageBase:ctor(  )
	
end

--��ʼ���ű�����
function InstanceStageBase:OnInitScript(  )
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	InstanceInstBase.OnInitScript(self) --���û���
	
	if self:GetMapQuestEndTime() > 0 then
		return
	end
	
	self:parseGeneralId()
	
	local id = self:GetIndex()
	local config = tb_instance_stage[ id ]
	local time	= config.time	
	local questTable = config.quests
	
	self:InitRes(config)
	
	self:SetBatch(config.refresnum)

	-- �Ӹ�������
	self:OnAddQuests(questTable)
	-- ����������ʱ��
	local timestamp = os.time() + time
	
	self:SetMapQuestEndTime(timestamp)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp)
end

function InstanceStageBase:InitRes(config)
	--self:SetRandomMonsterIndex(config.refresnum)
end

--����ÿ���ֵ�����
function InstanceStageBase:SetKillTarget(val)
	self:SetUInt16(MAP_INT_FIELD_RESERVE1,0,val);
end
function InstanceStageBase:SubKillTarget()
	self:SubUInt16(MAP_INT_FIELD_RESERVE1,0,1);
end
function InstanceStageBase:GetKillTarget()
	return self:GetUInt16(MAP_INT_FIELD_RESERVE1,0);
end
--���ùֵĲ���
function InstanceStageBase:SetBatch(val)
	return self:SetUInt16(MAP_INT_FIELD_RESERVE1,1,val);
end

function InstanceStageBase:SubBatch()
	return self:SubUInt16(MAP_INT_FIELD_RESERVE1,1,1);
end

function InstanceStageBase:GetBatch()
	return self:GetUInt16(MAP_INT_FIELD_RESERVE1,1);
end


function InstanceStageBase:GetIndex()
	return self:GetUInt32(RES_INSTANCE_FIELD_ID)
end


function InstanceStageBase:SetBuffEffectId(val)
	self:SetUInt32(STAGE_INSTANCE_BUFF_ID,val)
end

function InstanceStageBase:GetBuffEffectId()
	return self:GetUInt32(STAGE_INSTANCE_BUFF_ID)
end

function InstanceStageBase:parseGeneralId()
	
	local generalId	= self:GetMapGeneralId()
	outFmtDebug("generalId %s",generalId)
	local params = string.split(generalId, ':')
	local indx = tonumber(params[ 1 ])
	local buffEffectId = tonumber(params[ 2 ])
	
	self:SetUInt32(RES_INSTANCE_FIELD_ID, indx)
	self:SetBuffEffectId(buffEffectId)
end


--������״̬�����仯ʱ�䴥��
function InstanceStageBase:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceStageBase.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
		
		local allPlayers = mapLib.GetAllPlayer(self.ptr)
		local player = allPlayers[ 1 ]
		if not player then
			return
		end
		local playerInfo = UnitInfo:new {ptr = player}

		if tostate == self.STATE_FAIL then
			-- ʧ����
			playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, {}, INSTANCE_SUB_TYPE_STAGE, '')
		else
			--self:SendResReward(player)
		end
	end
end

--[[
-- �ж��Ƿ����˳�����
function InstanceStageBase:DoPlayerExitInstance(player)
	return 1	--����1�Ļ�Ϊ�����˳�������0�����˳�
end
--]]

--��Ҽ����ͼ
function InstanceStageBase:OnJoinPlayer(player)
	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻�������ֱ�ӵ���ȥ
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
	end
	
	-- ˢ�¹���
	self:OnRefreshMonster(playerInfo)
	
end

--ˢһ����
function InstanceStageBase:RefreshMonsterBatch(player)
	local batchIdx = self:GetBatch() - 1
	
	local tf,cnt = self:ApplyRefreshMonsterBatch(player,batchIdx)
	if not tf then
		return
	end
	
	outFmtDebug("RefreshMonsterBatch %d",cnt)
	
	self:SetKillTarget(cnt)
	self:SubBatch()
end

function InstanceStageBase:ApplyRefreshMonsterBatch(player,batchIdx)
	outFmtDebug("ApplyRefreshMonsterBatch base need todo by child")
	return false,0
end

--ˢ��
function InstanceStageBase:OnRefreshMonster(player)
	
	-- �����ǽ�������ˢ��, �ж��������ʱ��ȿ�ʼʱ�俪ʼʱ�䳬��2��������ˢ��
	-- ��ҪΪ�˽����������������
	local time = os.time()
	local startTime = self:GetMapCreateTime()
	if time - startTime > 2 then
		-- ���¸�����ӳ�޶�
		local creatureTable = mapLib.GetAllCreature(self.ptr)
		for _, creature in pairs(creatureTable) do
			creatureLib.ModifyThreat(creature, player.ptr, self.THREAT_V)
		end
		return
	end
	
	self:RefreshMonsterBatch(player)

end

--����������󴥷�()
function InstanceStageBase:OnPlayerDeath(player)
	-- ���״̬�Ѿ��ı�, ��ʹ����Ҳ���ٸ���ʱ��
	if self:GetMapState() ~= self.STATE_START then
		return
	end
	self:SetMapState(self.STATE_FAIL)
end

--������뿪ʱ����
function InstanceStageBase:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	if not is_offline then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		self:RemoveTimeOutCallback(self.Leave_Callback)
		self:SetMapEndTime(os.time())
	end
	
	local buffEffectId = self:GetBuffEffectId()
	if buffEffectId ~= 0 then
		local buff_id = tb_buff_effect[buffEffectId].buff_id
		unitLib.RemoveBuff(player,buff_id)
	end
	
	local playerInfo = UnitInfo:new{ptr = player}
	
	playerInfo:SetLastInstanceParam(self:GetIndex())
end

-- �����ȸ���ʱ����
function InstanceStageBase:AfterProcessUpdate(player)
	-- �жϸ����Ƿ�
	if self:CheckQuestAfterTargetUpdate() then
		self:SetMapState(self.STATE_FINISH)
	end
end

-- ����ʧ���˳�
function InstanceStageBase:instanceFail()
	self:SetMapState(self.STATE_FAIL)
end

function InstanceStageBase:SendStageReward(player,dict)
	--[[local id = self:GetIndex()
	-- ����������dropIdTable
--		local dropIdTable = tb_instance_trial[ id ].reward
	local playerInfo = UnitInfo:new{ptr = player}
	local idx = id * 1000 + playerInfo:GetLevel()
	--outFmtDebug("tb_instance_reward idx %d",idx)
	local config = tb_instance_reward[idx]
	local tab = {}
	for _, rewardInfo in pairs(config.basereward) do
		table.insert(tab, rewardInfo)
	end
	local randomReward = config.randomreward
	if #randomReward > 0 then
		local rewardIdx = randInt(1, #randomReward)
		table.insert(tab,randomReward[rewardIdx])
	end
	local vip = playerInfo:GetVIP()
	tab = rewardsAddExtraAndClone(tab, tb_vip_base[vip].resReward / 100)
	local dict = self:RandomReward(player, {}, tab)
	
	-- ɨ���Ľ������
	--]]
	local id = self:GetIndex()
	local playerInfo = UnitInfo:new{ptr = player}
	outFmtDebug("InstanceStageBase:SendResReward reward send!!!!!!!!!")
	local list = Change_To_Item_Reward_Info(dict, true)
		
	playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, INSTANCE_SUB_TYPE_STAGE, '')
	
	--����Ӧ�÷�����ͨ�ؽ���
	playerLib.SendToAppdDoSomething(player, SCENED_APPD_PASS_STAGE_INSTANCE, id)
end

function InstanceStageBase:MonsterDie(player)
	local playerInfo = UnitInfo:new{ptr = player}
	self:SubKillTarget()
	local num = self:GetKillTarget()
	if num == 0 then
		local batchNum = self:GetBatch()
		outFmtDebug("batchNum-----------------------%d",batchNum)
		if batchNum > 0 then
			outFmtDebug("shua xiao guai")
			self:RefreshMonsterBatch(playerInfo)
		else 
			--outFmtDebug("shua boss")
			self:RefreshBoss(playerInfo)
		end
	end
end
--ˢ��boss
function InstanceStageBase:RefreshBoss(player)
	local id = self:GetIndex()
	local config = tb_instance_stage[ id ]
	local entry = config.boss
	local plev = config.monsterlevel
	local bornPos = config.bosspos
	
	local creature = mapLib.AddCreature(self.ptr, {templateid = entry, x = bornPos[1], y = bornPos[2], level=plev, 
		active_grid = true, alias_name = config.name, ainame = "AI_stageBoss", npcflag = {}})
	creatureLib.ModifyThreat(creature, player.ptr, self.THREAT_V)
end

function InstanceStageBase:SetCreaturePro(creatureInfo, pros, bRecal, mul)
	--outFmtDebug("SetBaseAttrs -- ai res ")
	--creature:SetBaseAttrs(pros, bRecal, mul)
	local entry = creatureInfo:GetEntry()
	local lev = creatureInfo:GetLevel()
	local idx = entry * 1000 + lev
	--outFmtDebug("SetBaseAttrs -- ai res %d--%d--%d",entry,lev,idx)
	local config = tb_creature_resource[idx]
	if config then
		--outFmtDebug("shu xing")
		Instance_base.SetCreaturePro(self, creatureInfo, config.pro, bRecal, mul)
	else 
		Instance_base.SetCreaturePro(self, creatureInfo, pros, bRecal, mul)
	end
	
end

function InstanceStageBase:DoGetCreatureBaseExp(creature, owner)
	local entry = binLogLib.GetUInt16(creature, UNIT_FIELD_UINT16_0, 0)
	local level = binLogLib.GetUInt16(creature, UNIT_FIELD_UINT16_0, 1)
	local index = entry * 1000 + level
	local config = tb_creature_resource[index]
	
	if config then
		return config.exp
	end
	return tb_creature_template[entry].exp
end


function InstanceStageBase:DoMapBuffBonus(unit)
	
	if GetUnitTypeID(unit) == TYPEID_PLAYER then
		local buffEffectId = self:GetBuffEffectId()
		if buffEffectId ~= 0 then
			local buff_id = tb_buff_effect[buffEffectId].buff_id
			SpelladdBuff(unit, buff_id, unit, buffEffectId, 180)
		end
	end
end

-------------------------------- BOSS
AI_stageBoss = class("AI_stageBoss", AI_Base)
AI_stageBoss.ainame = "AI_stageBoss"
--����
function AI_stageBoss:JustDied( map_ptr,owner,killer_ptr )	
	-- ���ж��ǲ�������������
	local mapid = mapLib.GetMapID(map_ptr)
	if tb_map[mapid].inst_sub_type ~= INSTANCE_SUB_TYPE_STAGE then
		return
	end
	
	--local instanceInfo = InstanceStageBase:new{ptr = map_ptr}
	local instanceInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	
	-- ���ʱ�䵽��ʧ���� ��ʹ�����ɱ��BOSS��û��
	if instanceInfo:GetMapState() ~= instanceInfo.STATE_START then
		return
	end
	
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	-- ����ɱ�ֽ���
	local ownerInfo = UnitInfo:new {ptr = owner}
	local entry = ownerInfo:GetEntry()
	local updated = instanceInfo:OneMonsterKilled(entry)
	
	-- ���½���
	if updated then
		instanceInfo:AfterProcessUpdate(killer_ptr)
	end
	
	return 0
end

--����ս��Ʒ
function AI_stageBoss:LootAllot(owner, player, killer, drop_rate_multiples, boss_type, fcm)
	--[[local map_ptr = unitLib.GetMap(owner)
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
	
	instanceInfo:onBossLoot(player, dict)--]]
	local ownerInfo = UnitInfo:new{ptr = owner}
	local entry = ownerInfo:GetEntry()
	
	local map_ptr = unitLib.GetMap(owner)
	local mapid = mapLib.GetMapID(map_ptr)
	local instanceInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	local dict = {}
	DoRandomDropTable(tb_creature_template[entry].reward_id, dict)
	DoRandomDropTable(tb_creature_template[7001].reward_id, dict)
	
	-- �ͻ�����ʾʰȡ�ٶ���
	local destX, destY = unitLib.GetPos(owner)
	noticeClientShowPickLootAnimate(player, dict, destX, destY)
	
	PlayerAddRewards(player, dict, MONEY_CHANGE_SELECT_LOOT, LOG_ITEM_OPER_TYPE_LOOT, 1, false)
	
	instanceInfo:SendStageReward(player,dict)
end


----------------------------- С��----------------------------
AI_stage = class("AI_stage", AI_Base)
AI_stage.ainame = "AI_stage"
--����
function AI_stage:JustDied( map_ptr,owner,killer_ptr )	
	--outFmtDebug("die die ")
	-- ���ж��ǲ�������������
	local mapid = mapLib.GetMapID(map_ptr)
	if tb_map[mapid].inst_sub_type ~= INSTANCE_SUB_TYPE_STAGE then
		return
	end
	
	--local instanceInfo = InstanceStageBase:new{ptr = map_ptr}
	
	local instanceInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	
	-- ���ʱ�䵽��ʧ���� ��ʹ�����ɱ��BOSS��û��
	if instanceInfo:GetMapState() ~= instanceInfo.STATE_START then
		return
	end
	
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	-- ����ɱ�ֽ���
	local ownerInfo = UnitInfo:new {ptr = owner}
	local entry = ownerInfo:GetEntry()
	local updated = instanceInfo:OneMonsterKilled(entry)
	
	-- ���½���
	if updated then
		instanceInfo:AfterProcessUpdate(killer_ptr)
	end
	instanceInfo:MonsterDie(killer_ptr)
	--outFmtDebug("die die ****************** ")
	return 0
end

return InstanceStageBase