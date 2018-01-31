InstanceDoujiantai = class("InstanceDoujiantai", InstanceInstBase)

InstanceDoujiantai.Name = "InstanceDoujiantai"
InstanceDoujiantai.exit_time = 10
InstanceDoujiantai.broadcast_nogrid = 1

function InstanceDoujiantai:ctor(  )
	
end

--��ʼ���ű�����
function InstanceDoujiantai:OnInitScript()
	InstanceInstBase.OnInitScript(self) --���û���
	
	-- ����generalid
	self:parseGeneralId()
	self:OnCreateCreature()
	self:OnTaskStart()
	
	local timestamp = os.time() + tb_doujiantai_base[ 1 ].cd
	self:SetMapStartTime(timestamp)
end

function InstanceDoujiantai:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	
	local params = string.split(generalId, '|')
	local myRank 	= tonumber(params[ 3 ])
	local otherRank = tonumber(params[ 4 ])
	local history	= tonumber(params[ 5 ])
	local curr		= tonumber(params[ 6 ])
	
	self:SetMyRank(myRank)
	self:SetOtherRank(otherRank)
	self:SetHistory(history)
	self:SetCurrWins(curr)
end


function InstanceDoujiantai:SetMyRank(val)
	self:SetUInt16(DOUJIANTAI_FIELDS_INT_RANK, 0, val)
end
function InstanceDoujiantai:SetOtherRank(val)
	self:SetUInt16(DOUJIANTAI_FIELDS_INT_RANK, 1, val)
end

function InstanceDoujiantai:GetMyRank()
	return self:GetUInt16(DOUJIANTAI_FIELDS_INT_RANK, 0)
end

function InstanceDoujiantai:GetOtherRank()
	return self:GetUInt16(DOUJIANTAI_FIELDS_INT_RANK, 1)
end

function InstanceDoujiantai:SetHistory(val)
	self:SetUInt16(DOUJIANTAI_FIELDS_INT_COMBAT_WIN_INFO, 0, val)
end

function InstanceDoujiantai:SetCurrWins(val)
	self:SetUInt16(DOUJIANTAI_FIELDS_INT_COMBAT_WIN_INFO, 1, val)
end

function InstanceDoujiantai:GetHistory()
	return self:GetUInt16(DOUJIANTAI_FIELDS_INT_COMBAT_WIN_INFO, 0)
end

function InstanceDoujiantai:GetCurrWins()
	return self:GetUInt16(DOUJIANTAI_FIELDS_INT_COMBAT_WIN_INFO, 1)
end

function InstanceDoujiantai:OnCreateCreature()
	local rank = self:GetOtherRank()
	local config = globalCounter:GetRankInfo(rank)
	
	local enemy = nil
	if string.len(config.guid) > 0 then
		enemy = mapLib.GetPlayerByPlayerGuid(self.ptr, config.guid)
	end
	
	-- �������
	if enemy then
		local enemyInfo = UnitInfo:new {ptr = enemy}
		config = enemyInfo:GetDummyInfo()
	end
	
	local x = tb_doujiantai_base[ 1 ].bornPos[ 2 ][ 1 ]
	local y = tb_doujiantai_base[ 1 ].bornPos[ 2 ][ 2 ]
	local image = self:GetImageInfo(config)
	self:AddImageBody(image, x, y, "AI_Image", nil, nil, nil)
	
end

-- ���ʽ��ʼ
function InstanceDoujiantai:OnTaskStart()
	-- print("==================OnTaskStart====", tb_doujiantai_base[ 1 ].last + tb_doujiantai_base[ 1 ].cd)
	local timestamp = os.time() +  tb_doujiantai_base[ 1 ].last + tb_doujiantai_base[ 1 ].cd
	-- print("=========", timestamp)
	-- ������ʱ��
	self:SetMapQuestEndTime(timestamp)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp)
end

-- ����ʧ���˳�
function InstanceDoujiantai:instanceFail()
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
function InstanceDoujiantai:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceDoujiantai.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
		
		local allPlayers = mapLib.GetAllPlayer(self.ptr)
		local player = allPlayers[ 1 ]
		if player then
			local playerInfo = UnitInfo:new {ptr = player}
			local vip = playerInfo:GetVIP()
			local dict = {}
			for _, info in pairs(tb_doujiantai_base[ 1 ].tryReward) do
				local count = math.floor(info[ 2 ] * (1 + tb_vip_base[vip].djtReward / 100))
				MergeSameTable(dict, info[ 1 ], count)
			end
			if tostate == self.STATE_FINISH then
				if self:GetCurrWins() + 1 > self:GetHistory() then
					local config = tb_doujiantai_combat_win[self:GetCurrWins()+1]
					if config then
						for _, info in pairs(config.reward) do
							local count = math.floor(info[ 2 ] * (1 + tb_vip_base[vip].djtReward / 100))
							MergeSameTable(dict, info[ 1 ], count)
						end
					end
				end
			end
			local list = Change_To_Item_Reward_Info(dict, true)
			
			playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, INSTANCE_SUB_TYPE_DOUJIANTAI, '')
		end
	end
end

--��Ҽ����ͼ
function InstanceDoujiantai:OnJoinPlayer(player)
	InstanceInstBase.OnJoinPlayer(self, player)
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() or self:GetMapState() ~= self.STATE_START then
		--�����˻�������ֱ�ӵ���ȥ
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
		return
	end
	
	local maxHealth = binLogLib.GetUInt32(player, UNIT_FIELD_MAX_HEALTH)
	unitLib.SetHealth(player, maxHealth)
end

--������뿪ʱ����
function InstanceDoujiantai:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	
	if is_offline then
		-- ֪ͨ��������������
		local rank1 = self:GetMyRank()
		local rank2 = self:GetOtherRank()
		call_opt_doujiantai_force_unlock(rank1, rank2)
	end
	
	self:RemoveTimeOutCallback(self.Leave_Callback)
	if self:GetMapState() == self.STATE_START then
		self:OnFightResult(player, GlobalCounter.LOSE)
		self:SetMapState(self.STATE_FAIL)
	end
end

--����������󴥷�()
function InstanceDoujiantai:OnPlayerDeath(player)
	-- AI win	
	self:OnFightResult(player, GlobalCounter.LOSE)
	self:SetMapState(self.STATE_FAIL)
end

-- ������
function InstanceDoujiantai:OnFightResult(player, result)
	self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
	playerLib.SendToAppdDoSomething(player, SCENED_APPD_DOUJIANTAI, self:GetOtherRank(), ''..result)
end


-------------------------�ɸ��ᱦboss---------------------------
AI_Image = class("AI_Image", AI_Base)
AI_Image.ainame = "AI_Image"

--����
function AI_Image:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)

	local instanceInfo = InstanceDoujiantai:new{ptr = map_ptr}
	
	instanceInfo:OnFightResult(killer_ptr, GlobalCounter.WIN)
	instanceInfo:SetMapState(instanceInfo.STATE_FINISH)
	
	return 0
end


return InstanceDoujiantai