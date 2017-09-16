InstanceXiulianchang = class("InstanceXiulianchang", InstanceInstBase)

InstanceXiulianchang.Name = "InstanceXiulianchang"
InstanceXiulianchang.exit_time = 10
InstanceXiulianchang.broadcast_nogrid = 1

function InstanceXiulianchang:ctor(  )
	
end

--��ʼ���ű�����
function InstanceXiulianchang:OnInitScript()
	InstanceInstBase.OnInitScript(self) --���û���
	
	-- ����generalid
	self:parseGeneralId()
	self:OnCreateCreature()
	self:OnTaskStart()
	
	local timestamp = os.time() + tb_xiulianchang_base[ 1 ].cd
	self:SetMapStartTime(timestamp)
end

function InstanceXiulianchang:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	
	local params = string.split(generalId, '@')
	
	local params1 = string.split(params[1], '|')
	local enemy_content = params[2]
	local enemy_rank 	= tonumber(params1[ 3 ])
	local enemy_robotId = tonumber(params1[ 4 ])
	local enemy_guid = (params1[ 5 ])
	
	self:SetRank(enemy_rank)
	self:SetRobotId(enemy_robotId)
	self:SetGuid(enemy_guid)
	self:SetContent(enemy_content)
end


function InstanceXiulianchang:SetRank(val)
	self:SetUInt32(XIULIANCHANG_FIELDS_INT_RANK, val)
end

function InstanceXiulianchang:GetRank()
	return self:GetUInt32(XIULIANCHANG_FIELDS_INT_RANK)
end

function InstanceXiulianchang:SetRobotId(val)
	self:SetUInt32(XIULIANCHANG_FIELDS_INT_ROBOT_ID, val)
end

function InstanceXiulianchang:GetRobotId()
	return self:GetUInt32(XIULIANCHANG_FIELDS_INT_ROBOT_ID)
end

function InstanceXiulianchang:SetLevel(val)
	self:SetUInt32(XIULIANCHANG_FIELDS_INT_LEVEL, val)
end

function InstanceXiulianchang:GetLevel()
	return self:GetUInt32(XIULIANCHANG_FIELDS_INT_LEVEL)
end

function InstanceXiulianchang:SetGuid(val)
	self:SetStr(XIULIANCHANG_FIELDS_STR_INFO_GUID, val)
end

function InstanceXiulianchang:GetGuid()
	return self:GetStr(XIULIANCHANG_FIELDS_STR_INFO_GUID)
end

function InstanceXiulianchang:SetContent(val)
	self:SetStr(XIULIANCHANG_FIELDS_STR_INFO_CONTENT, val)
end

function InstanceXiulianchang:GetContent()
	return self:GetStr(XIULIANCHANG_FIELDS_STR_INFO_CONTENT)
end

function InstanceXiulianchang:SetName(val)
	self:SetStr(XIULIANCHANG_FIELDS_STR_INFO_NAME, val)
end

function InstanceXiulianchang:GetName()
	return self:GetStr(XIULIANCHANG_FIELDS_STR_INFO_NAME)
end



function InstanceXiulianchang:OnCreateCreature()
	local rank = self:GetRank()
	local robot_id = self:GetRobotId()
	local guid = self:GetGuid()
	
	local config = {}
	if rank ~= 0 then --��ս�����еĽ�ɫ --��Ч
		config = globalCounter:GetRankInfo(rank)
		
		local enemy = nil
		if string.len(config.guid) > 0 then
			enemy = mapLib.GetPlayerByPlayerGuid(self.ptr, config.guid)
			self:SetGuid(config.guid)
		end
		
		-- �������
		if enemy then
			local enemyInfo = UnitInfo:new {ptr = enemy}
			config = enemyInfo:GetDummyInfo()
		end
		
	elseif robot_id ~= 0 then --��ս����������
		config = tb_xiulianchang_dummy[robot_id]
	
	elseif string.len(guid) > 0 then --�Ӷ�/�������
		config = {}
		local enemy = nil
		enemy = mapLib.GetPlayerByPlayerGuid(self.ptr, guid)
		
		-- �������
		if enemy then
			local enemyInfo = UnitInfo:new {ptr = enemy}
			config = enemyInfo:GetDummyInfo()
		else 
			local content = self:GetContent()
			config = GetDummyInfoFromContent(content)
		end
		
	else --�Ӷᶷ��̨������
		local content = self:GetContent()
		config = GetDummyInfoFromContent(content)
		--outFmtDebug('InstanceXiulianchang:OnCreateCreature rank == 0 robot_id == 0 guid == empty !!')
	end
	self:SetLevel(config.level)
	self:SetName(config.name)
	local x = tb_xiulianchang_base[ 1 ].bornPos[ 2 ][ 1 ]
	local y = tb_xiulianchang_base[ 1 ].bornPos[ 2 ][ 2 ]
	local image = self:GetImageInfo(config)
	self:AddImageBody(image, x, y, "AI_Xiulianchang", nil, nil, nil)
	
end

-- ���ʽ��ʼ
function InstanceXiulianchang:OnTaskStart()
	-- print("==================OnTaskStart====", tb_xiulianchang_base[ 1 ].last + tb_xiulianchang_base[ 1 ].cd)
	local timestamp = os.time() +  tb_xiulianchang_base[ 1 ].last + tb_xiulianchang_base[ 1 ].cd
	-- print("=========", timestamp)
	-- ������ʱ��
	self:SetMapQuestEndTime(timestamp)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp)
end

-- ����ʧ���˳�
function InstanceXiulianchang:instanceFail()
	self:SetMapState(self.STATE_FAIL)
	-- ���player
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	local player = allPlayers[ 1 ]
	if player then
		self:OnFightResult(player, GlobalCounter.LOSE)
	end
	return false
end

--������״̬�����仯ʱ�䴥��
function InstanceXiulianchang:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceXiulianchang.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

--��Ҽ����ͼ
function InstanceXiulianchang:OnJoinPlayer(player)
	InstanceInstBase.OnJoinPlayer(self, player)
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() or self:GetMapState() ~= self.STATE_START then
		--�����˻�������ֱ�ӵ���ȥ
		local login_fd = serverConnList:getLogindFD()
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
		return
	end
	
	local maxHealth = binLogLib.GetUInt32(player, UNIT_FIELD_MAX_HEALTH)
	unitLib.SetHealth(player, maxHealth)
end

--������뿪ʱ����
function InstanceXiulianchang:OnLeavePlayer( player, is_offline)
	self:RemoveTimeOutCallback(self.Leave_Callback)
	if self:GetMapState() == self.STATE_START then
		self:OnFightResult(player, GlobalCounter.LOSE)
		self:SetMapState(self.STATE_FAIL)
	end
	
	local maxHealth = binLogLib.GetUInt32(player, UNIT_FIELD_MAX_HEALTH)
	unitLib.SetHealth(player, maxHealth)
end

--����������󴥷�()
function InstanceXiulianchang:OnPlayerDeath(player)
	-- AI win	
	self:OnFightResult(player, GlobalCounter.LOSE)
	self:SetMapState(self.STATE_FAIL)
end

-- ������
function InstanceXiulianchang:OnFightResult(player, result)
	self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
	playerLib.SendToAppdDoSomething(player, SCENED_APPD_XIULIANCHANG, 0, self:GetGuid()..'|'..self:GetRobotId()..'|'..self:GetLevel()..'|'..result..'|'..self:GetName())
end


-------------------------�ɸ��ᱦboss---------------------------
AI_Xiulianchang = class("AI_Xiulianchang", AI_Base)
AI_Xiulianchang.ainame = "AI_Xiulianchang"

--����
function AI_Xiulianchang:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)

	local instanceInfo = InstanceXiulianchang:new{ptr = map_ptr}
	
	instanceInfo:OnFightResult(killer_ptr, GlobalCounter.WIN)
	instanceInfo:SetMapState(instanceInfo.STATE_FINISH)
	
	return 0
end


return InstanceXiulianchang