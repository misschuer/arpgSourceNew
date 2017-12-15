InstanceResBase = class("InstanceResBase", InstanceInstBase)

InstanceResBase.Name = "InstanceResBase"
InstanceResBase.exit_time = 10
--ˢ������ƫ��ֵ
InstanceResBase.RefreshOffset = 3;

InstanceResBase.MonsterRefreshInterval = 500

function InstanceResBase:ctor(  )
	
end

--��ʼ���ű�����
function InstanceResBase:OnInitScript(  )
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
	local config = tb_instance_res[ id ]
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

function InstanceResBase:InitRes(config)
	self:SetRandomMonsterIndex(config.refresnum)
end

--����ÿ����ˢ�µĴ���
function InstanceResBase:SetRandomMonsterIndex(num)
	local tab = GetRandomIndexTable(num,num)
	for i=1,#tab do
		if i <= 4 then
			self:SetByte(MAP_INT_FIELD_RESERVE2,i-1,tab[i])
		elseif i <= 8 then
			self:SetByte(MAP_INT_FIELD_RESERVE3,i-5,tab[i])
		end
		--print(i-1,tab[i])
	end
end

function InstanceResBase:GetRandomMonsterIndex(idx)
	if idx <= 3 then
		return self:GetByte(MAP_INT_FIELD_RESERVE2,idx)
	elseif idx <= 7 then
		return self:GetByte(MAP_INT_FIELD_RESERVE3,idx-4)
	end
	
	return 0
end

--����ÿ���ֵ�����
function InstanceResBase:SetKillTarget(val)
	self:SetUInt16(MAP_INT_FIELD_RESERVE1,0,val);
end
function InstanceResBase:SubKillTarget()
	self:SubUInt16(MAP_INT_FIELD_RESERVE1,0,1);
end
function InstanceResBase:GetKillTarget()
	return self:GetUInt16(MAP_INT_FIELD_RESERVE1,0);
end
--���ùֵĲ���
function InstanceResBase:SetBatch(val)
	return self:SetUInt16(MAP_INT_FIELD_RESERVE1,1,val);
end

function InstanceResBase:SubBatch()
	return self:SubUInt16(MAP_INT_FIELD_RESERVE1,1,1);
end

function InstanceResBase:GetBatch()
	return self:GetUInt16(MAP_INT_FIELD_RESERVE1,1);
end


function InstanceResBase:GetIndex()
	return self:GetUInt32(RES_INSTANCE_FIELD_ID)
end

function InstanceResBase:parseGeneralId()
	
	local generalId	= self:GetMapGeneralId()
	outFmtDebug("generalId %s",generalId)
	local params = string.split(generalId, ':')
	local indx = tonumber(params[ 1 ])
	
	self:SetUInt32(RES_INSTANCE_FIELD_ID, indx)
end


--������״̬�����仯ʱ�䴥��
function InstanceResBase:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceResBase.exit_time
		
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
			playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, {}, INSTANCE_SUB_TYPE_RES, '')
		else
			self:SendResReward(player)
		end
	end
end

--[[
-- �ж��Ƿ����˳�����
function InstanceResBase:DoPlayerExitInstance(player)
	return 1	--����1�Ļ�Ϊ�����˳�������0�����˳�
end
--]]

--��Ҽ����ͼ
function InstanceResBase:OnJoinPlayer(player)
	
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
function InstanceResBase:RefreshMonsterBatch(player)
	local batchIdx = self:GetBatch() - 1
	
	local tf,cnt = self:ApplyRefreshMonsterBatch(player,batchIdx)
	if not tf then
		return
	end
	
	outFmtDebug("RefreshMonsterBatch %d",cnt)
	
	self:SetKillTarget(cnt)
	self:SubBatch()
end

function InstanceResBase:ApplyRefreshMonsterBatch(player,batchIdx)
	outFmtDebug("ApplyRefreshMonsterBatch base")
	local batchPos = self:GetRandomMonsterIndex(batchIdx)

	if batchPos == 0 then
		return false,0
	end
	
	local id = self:GetIndex()
	local config = tb_instance_res[ id ]
	local entry = config.monster[batchPos]
	local plev = player:GetLevel()
	local bornPos = config.monsterInfo[batchPos]
	local cnt = config.monsternum
	
	
	--REFRESH_MONSTER_FIELD_ID			=	MAP_INT_FIELD_INSTANCE_TYPE + 1,	//2��short(0:��ǰ�Ѿ�ˢ��,1:�ܹ���Ҫˢ���ٹ�
	for i = 1, cnt do
		local bornX = bornPos[ 1 ] + randInt(0, self.RefreshOffset)
		local bornY = bornPos[ 2 ] + randInt(0, self.RefreshOffset)
		local indx = REFRESH_MONSTER_FIELD_INFO_START + (i - 1) * 2
		self:SetUInt16(indx, 0, entry)
		self:SetUInt16(indx, 1, plev)
		self:SetUInt16(indx+1, 0, bornX)
		self:SetUInt16(indx+1, 1, bornY)
	end
	self:SetUInt16(REFRESH_MONSTER_FIELD_ID, 0, 0)
	self:SetUInt16(REFRESH_MONSTER_FIELD_ID, 1, cnt)
	
	mapLib.DelTimer(self.ptr, 'OnTimer_MonsterBornOneByOne')
	mapLib.AddTimer(self.ptr, 'OnTimer_MonsterBornOneByOne', self.MonsterRefreshInterval, player:GetPlayerGuid())
	
	return true,cnt
end

function InstanceResBase:OnTimer_MonsterBornOneByOne(playerGuid)
	local dids = self:GetUInt16(REFRESH_MONSTER_FIELD_ID, 0)
	local need = self:GetUInt16(REFRESH_MONSTER_FIELD_ID, 1)
	if dids >= need then
		return false
	end
	
	local indx = dids * 2 + REFRESH_MONSTER_FIELD_INFO_START
	local entry = self:GetUInt16(indx  , 0)
	local level = self:GetUInt16(indx  , 1)
	local bornX = self:GetUInt16(indx+1, 0)
	local bornY = self:GetUInt16(indx+1, 1)
	
	local creature = mapLib.AddCreature(self.ptr, 
			{templateid = entry, x = bornX, y = bornY, level=level, active_grid = true, 
			ainame = "AI_res", npcflag = {}, attackType = REACT_AGGRESSIVE})
	
	local player_ptr = mapLib.GetPlayerByPlayerGuid(self.ptr, playerGuid)
	if player_ptr then
		creatureLib.ModifyThreat(creature, player_ptr, self.THREAT_V)
	end
	self:AddUInt16(REFRESH_MONSTER_FIELD_ID, 0, 1)
	
	return true
end

--ˢ��
function InstanceResBase:OnRefreshMonster(player)
	
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
function InstanceResBase:OnPlayerDeath(player)
	-- ���״̬�Ѿ��ı�, ��ʹ����Ҳ���ٸ���ʱ��
	if self:GetMapState() ~= self.STATE_START then
		return
	end
	self:SetMapState(self.STATE_FAIL)
end

--������뿪ʱ����
function InstanceResBase:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	if not is_offline then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		self:RemoveTimeOutCallback(self.Leave_Callback)
		self:SetMapEndTime(os.time())
	end
	
	local playerInfo = UnitInfo:new{ptr = player}
	
	playerInfo:SetLastInstanceParam(self:GetIndex())
end

-- �����ȸ���ʱ����
function InstanceResBase:AfterProcessUpdate(player)
	-- �жϸ����Ƿ�
	if self:CheckQuestAfterTargetUpdate() then
		self:SetMapState(self.STATE_FINISH)
	end
end

-- ����ʧ���˳�
function InstanceResBase:instanceFail()
	self:SetMapState(self.STATE_FAIL)
end

function InstanceResBase:SendResReward(player)
	local id = self:GetIndex()
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
	local list = Change_To_Item_Reward_Info(dict, true)
		
	playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, INSTANCE_SUB_TYPE_RES, '')
	
	--����Ӧ�÷����н����ж�
	playerLib.SendToAppdDoSomething(player, SCENED_APPD_PASS_RES_INSTANCE, id)
end

function InstanceResBase:MonsterDie(player)
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
function InstanceResBase:RefreshBoss(player)
	local id = self:GetIndex()
	local config = tb_instance_res[ id ]
	local entry = config.boss
	local plev = player:GetLevel()
	local bornPos = config.bosspos
	
	local creature = mapLib.AddCreature(self.ptr, {templateid = entry, x = bornPos[1], y = bornPos[2], level=plev, 
		active_grid = true, alias_name = config.name, ainame = "AI_resBoss", npcflag = {}})
	creatureLib.ModifyThreat(creature, player.ptr, self.THREAT_V)
end

function InstanceResBase:SetCreaturePro(creatureInfo, pros, bRecal, mul)
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

function InstanceResBase:DoGetCreatureBaseExp(creature, owner)
	local entry = binLogLib.GetUInt16(creature, UNIT_FIELD_UINT16_0, 0)
	local level = binLogLib.GetUInt16(creature, UNIT_FIELD_UINT16_0, 1)
	local index = entry * 1000 + level
	local config = tb_creature_resource[index]
	
	if config then
		return config.exp
	end
	return tb_creature_template[entry].exp
end

-------------------------------- BOSS
AI_resBoss = class("AI_resBoss", AI_Base)
AI_resBoss.ainame = "AI_resBoss"
--����
function AI_resBoss:JustDied( map_ptr,owner,killer_ptr )	
	-- ���ж��ǲ�������������
	local mapid = mapLib.GetMapID(map_ptr)
	if tb_map[mapid].inst_sub_type ~= INSTANCE_SUB_TYPE_RES then
		return
	end
	
	--local instanceInfo = InstanceResBase:new{ptr = map_ptr}
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


----------------------------- С��----------------------------
AI_res = class("AI_res", AI_Base)
AI_res.ainame = "AI_res"
--����
function AI_res:JustDied( map_ptr,owner,killer_ptr )	
	--outFmtDebug("die die ")
	-- ���ж��ǲ�������������
	local mapid = mapLib.GetMapID(map_ptr)
	if tb_map[mapid].inst_sub_type ~= INSTANCE_SUB_TYPE_RES then
		return
	end
	
	--local instanceInfo = InstanceResBase:new{ptr = map_ptr}
	
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

return InstanceResBase