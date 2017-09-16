InstanceVIP = class("InstanceVIP", InstanceInstBase)

InstanceVIP.Name = "InstanceVIP"
InstanceVIP.exit_time = 10
InstanceVIP.BOSS_NAME = "VIP_BOSS"

function InstanceVIP:ctor(  )
	
end

--��ʼ���ű�����
function InstanceVIP:OnInitScript(  )
	InstanceInstBase.OnInitScript(self) --���û���
	
	if self:GetMapQuestEndTime() > 0 then
		return
	end
	
	self:parseGeneralId()
	
	local id	= self:getIndex()
	local hard	= self:getHard()
	local time	= tb_map_vip[ id ].time
	local questTable = tb_map_vip[ id ].quests[hard]
	-- �Ӹ�������
	InstanceInstBase.OnAddQuests(self, questTable)
	-- ����������ʱ��
	local timestamp = os.time() + time
	
	self:SetMapQuestEndTime(timestamp)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp)
end

function InstanceVIP:getIndex()
	return self:GetUInt16(VIP_INSTANCE_FIELD_ID, 0)
end

function InstanceVIP:getHard()
	return self:GetUInt16(VIP_INSTANCE_FIELD_ID, 1)
end

function InstanceVIP:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	local params = string.split(generalId, ':')
	local indx = tonumber(params[ 1 ])
	local hard = tonumber(params[ 2 ])
	
	self:SetUInt16(VIP_INSTANCE_FIELD_ID, 0, indx)
	self:SetUInt16(VIP_INSTANCE_FIELD_ID, 1, hard)
end

--������״̬�����仯ʱ�䴥��
function InstanceVIP:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceVIP.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

-- �ж��Ƿ����˳�����
function InstanceVIP:DoPlayerExitInstance(player)
	return 1	--����1�Ļ�Ϊ�����˳�������0�����˳�
end

--��Ҽ����ͼ
function InstanceVIP:OnJoinPlayer(player)
	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻�������ֱ�ӵ���ȥ
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
	end
	
	-- ˢ��BOSS
	self:OnRefreshBoss(player)
	
end

--ˢ��
function InstanceVIP:OnRefreshBoss(player)
	
	-- �����ǽ�������ˢ��, �ж��������ʱ��ȿ�ʼʱ�俪ʼʱ�䳬��2��������ˢ��
	-- ��ҪΪ�˽����������������
	local time = os.time()
	local startTime = self:GetMapCreateTime()
	if time - startTime > 2 then
		return
	end
	
	-- ��ʵ�����û��Ҫ�ж���
	local boss = mapLib.AliasCreature(self.ptr, InstanceVIP.BOSS_NAME)
	if boss then
		return
	end
	
	local hard		= self:getHard()
	local id		= self:getIndex()
	local entry		= tb_map_vip[id].creatures[hard]
	
	local config	= tb_creature_template[entry]
	local bornX		= tb_map_vip[id].bossx
	local bornY		= tb_map_vip[id].bossy

	local creature = mapLib.AddCreature(self.ptr, {
			templateid = entry, x = bornX, y = bornY, 
			active_grid = true, alias_name = InstanceVIP.BOSS_NAME, ainame = config.ainame, npcflag = {}
		}
	)
	creatureLib.ModifyThreat(creature, player, self.THREAT_V)
end

--����������󴥷�()
function InstanceVIP:OnPlayerDeath(player)
	-- ���״̬�Ѿ��ı�, ��ʹ����Ҳ���ٸ���ʱ��
	if self:GetMapState() ~= self.STATE_START then
		return
	end
	self:SetMapState(self.STATE_FAIL)
end

--������뿪ʱ����
function InstanceVIP:OnLeavePlayer( player, is_offline)
	if not is_offline then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		self:RemoveTimeOutCallback(self.Leave_Callback)
		self:SetMapEndTime(os.time())
	end
end

-- �����ȸ���ʱ����
function InstanceVIP:AfterProcessUpdate(player)
	-- �жϸ����Ƿ�
	if self:CheckQuestAfterTargetUpdate() then
		-- ����������dropIdTable
		local id  = self:getIndex()
		local hard   = self:getHard()
		local playerInfo = UnitInfo:new{ptr = player}
		local dropId = GetRewardIfGenderSensitive(tb_map_vip[id].rewards[hard], playerInfo:GetGender())

		local dict = self:RandomReward(player, {dropId})
		
		-- ɨ���Ľ������
		local list = Change_To_Item_Reward_Info(dict, true)
			
		playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, INSTANCE_SUB_TYPE_VIP, '')
		
		
		-- ����״̬
		self:SetMapState(self.STATE_FINISH)
		
		--����Ӧ�÷����н����ж�
		playerLib.SendToAppdDoSomething(player, SCENED_APPD_PASS_VIP_INSTANCE, id, ""..hard)
	end
end

-------------------------------- BOSS
AI_vipboss = class("AI_vipboss", AI_Base)
AI_vipboss.ainame = "AI_vipboss"
--����
function AI_vipboss:JustDied( map_ptr,owner,killer_ptr )	
	
	-- ���ж��ǲ���VIP����	
	local mapid = mapLib.GetMapID(map_ptr)
	if tb_map[mapid].inst_sub_type ~= 1 then
		return
	end
	
	local instanceInfo = InstanceVIP:new{ptr = map_ptr}
	
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

return InstanceVIP