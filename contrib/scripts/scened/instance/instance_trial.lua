InstanceTrial = class("InstanceTrial", InstanceInstBase)

InstanceTrial.Name = "InstanceTrial"
InstanceTrial.exit_time = 10

function InstanceTrial:ctor(  )
	
end

--��ʼ���ű�����
function InstanceTrial:OnInitScript(  )
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	InstanceInstBase.OnInitScript(self) --���û���
	
	self:parseGeneralId()
	
	local id = self:GetIndex()
	local time	= tb_instance_trial[ id ].time	
	local questTable = tb_instance_trial[ id ].quests
	-- �Ӹ�������
	self:OnAddQuests(questTable)
	-- ����������ʱ��
	local timestamp = os.time() + time
	
	self:SetMapQuestEndTime(timestamp)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp)
end

-- �˳�����ʱ����׼���˳�
function InstanceTrial:prepareToLeave()
	local id = self:GetIndex()
	-- û����һ�ػ���ʧ��Ҳ�˳�
	if self:GetMapState() == self.STATE_FAIL or not tb_instance_trial[id+1] then
		mapLib.ExitInstance(self.ptr)
	else
		local allPlayers = mapLib.GetAllPlayer(self.ptr)
		for _, player in pairs(allPlayers) do
			--����Ӧ�÷����н����ж�
			playerLib.SendToAppdDoSomething(player, SCENED_APPD_ENTER_TRIAL_INSTANCE, 0)
		end
	end
end

function InstanceTrial:GetIndex()
	return self:GetUInt32(TRIAL_INSTANCE_FIELD_ID)
end

function InstanceTrial:parseGeneralId()
	
	local generalId	= self:GetMapGeneralId()
	local params = string.split(generalId, ':')
	local indx = tonumber(params[ 1 ])
	
	self:SetUInt32(TRIAL_INSTANCE_FIELD_ID, indx)
end


--������״̬�����仯ʱ�䴥��
function InstanceTrial:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceTrial.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

-- �ж��Ƿ����˳�����
function InstanceTrial:DoPlayerExitInstance(player)
	return 1	--����1�Ļ�Ϊ�����˳�������0�����˳�
end

--��Ҽ����ͼ
function InstanceTrial:OnJoinPlayer(player)
	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻�������ֱ�ӵ���ȥ
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
		return
	end
	
	-- ˢ�¹���
	self:OnRefreshMonster(player)
	
end

--ˢ��
function InstanceTrial:OnRefreshMonster(player)
	
	-- �����ǽ�������ˢ��, �ж��������ʱ��ȿ�ʼʱ�俪ʼʱ�䳬��2��������ˢ��
	-- ��ҪΪ�˽����������������
	local time = os.time()
	local startTime = self:GetMapCreateTime()
	if time - startTime > 2 then
		-- ���¸�����ӳ�޶�
		local creatureTable = mapLib.GetAllCreature(self.ptr)
		for _, creature in pairs(creatureTable) do
			creatureLib.ModifyThreat(creature, player, self.THREAT_V)
		end
		return
	end
	
	local id		= self:GetIndex()
	local config	= tb_instance_trial[ id ]
	
	local entry
	local bornX
	local bornY
	
	if #config.monsterInfo > 0 then
		-- ���ĵ������
		local cx	= config.monsterInfo[ 1 ]
		local cy	= config.monsterInfo[ 2 ]
		
		entry 		= config.monsterInfo[ 3 ]
		local offs	= config.monsterInfo[ 4 ]
		local num	= config.monsterInfo[ 5 ]
		local width = offs * 2 + 1
		local grids = width * width
		local cent	= (grids - 1) / 2
		
		-- ���Ͻǵ������
		local lx = cx - offs
		local ly = cy - offs
		
		
		local idTable = GetRandomIndexTable(grids, num)
		for _, indx in pairs(idTable) do
			local id = indx - 1
			local offx = id % width
			local offy = id / width
			bornX = lx + offx
			bornY = ly + offy
			
			local creature = mapLib.AddCreature(self.ptr, {
				templateid = entry, x = bornX, y = bornY, 
				active_grid = true, alias_name = "", ainame = tb_creature_template[entry].ainame, npcflag = {}
			})
			
			creatureLib.ModifyThreat(creature, player, self.THREAT_V)
		end
	end
	
	if #config.bossInfo > 0 then
		entry = config.bossInfo[ 3 ]
		bornX = config.bossInfo[ 1 ]
		bornY = config.bossInfo[ 2 ]
		local creature = mapLib.AddCreature(self.ptr, {
				templateid = entry, x = bornX, y = bornY, 
				active_grid = true, alias_name = "TrialBoss", ainame = tb_creature_template[entry].ainame, npcflag = {}
			}
		)
		creatureLib.ModifyThreat(creature, player, self.THREAT_V)
	end
end

--����Ҽ���󴥷�
function InstanceTrial:OnAfterJoinPlayer(player)
	InstanceInstBase.OnAfterJoinPlayer(self, player)
end

--����������󴥷�()
function InstanceTrial:OnPlayerDeath(player)
	-- ���״̬�Ѿ��ı�, ��ʹ����Ҳ���ٸ���ʱ��
	if self:GetMapState() ~= self.STATE_START then
		return
	end
	self:SetMapState(self.STATE_FAIL)
	
	local playerInfo = UnitInfo:new{ptr = player}
	playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, {}, INSTANCE_SUB_TYPE_TRIAL, '')
end

--������뿪ʱ����
function InstanceTrial:OnLeavePlayer( player, is_offline)
	if not is_offline then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		self:RemoveTimeOutCallback(self.Leave_Callback)
		self:SetMapEndTime(os.time())
	end
end

-- �����ȸ���ʱ����
function InstanceTrial:AfterProcessUpdate(player)
	-- �жϸ����Ƿ�
	if self:CheckQuestAfterTargetUpdate() then
		-- ����״̬
		self:SetMapState(self.STATE_FINISH)
		
		local id = self:GetIndex()
		-- ����������dropIdTable
--		local dropIdTable = tb_instance_trial[ id ].reward
		local dict = self:RandomReward(player, {}, tb_instance_trial[ id ].firstReward)
		
		-- ɨ���Ľ������
		local list = Change_To_Item_Reward_Info(dict, true)
		local playerInfo = UnitInfo:new{ptr = player}
		playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, INSTANCE_SUB_TYPE_TRIAL, '')
		
		--����Ӧ�÷����н����ж�
		playerLib.SendToAppdDoSomething(player, SCENED_APPD_PASS_TRIAL_INSTANCE, id)
	end
end

-------------------------------- BOSS
AI_trialboss = class("AI_trialboss", AI_Base)
AI_trialboss.ainame = "AI_trialboss"
--����
function AI_trialboss:JustDied( map_ptr,owner,killer_ptr )	
	-- ���ж��ǲ�������������
	local mapid = mapLib.GetMapID(map_ptr)
	if tb_map[mapid].inst_sub_type ~= 2 then
		return
	end
	
	local instanceInfo = InstanceTrial:new{ptr = map_ptr}
	
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
AI_trial = class("AI_trial", AI_Base)
AI_trial.ainame = "AI_trial"
--����
function AI_trial:JustDied( map_ptr,owner,killer_ptr )	
	
	-- ���ж��ǲ�������������
	local mapid = mapLib.GetMapID(map_ptr)
	if tb_map[mapid].inst_sub_type ~= 2 then
		return
	end
	
	local instanceInfo = InstanceTrial:new{ptr = map_ptr}
	
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

return InstanceTrial