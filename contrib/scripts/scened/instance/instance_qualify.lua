InstanceQualify = class("InstanceQualify", InstanceInstBase)

InstanceQualify.Name = "InstanceQualify"
InstanceQualify.exit_time = 10
InstanceQualify.broadcast_nogrid = 1
InstanceQualify.AI_ALIAS_NAME = 'qualifyAI'


function InstanceQualify:ctor(  )
	
end

--��ʼ���ű�����
function InstanceQualify:OnInitScript()
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()

	InstanceInstBase.OnInitScript(self) --���û���
	
	-- ����generalid
	self:parseGeneralId()
	self:OnTaskStart()
end

function InstanceQualify:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	local params = string.split(generalId, '|')
	-- û��ƥ�䵽��
	if #params == 3 then
		local id = tonumber(params[ 3 ])
		self:OnCreateCreature(id)
	end
end

function InstanceQualify:OnCreateCreature(id)
	local range = tb_single_pvp_grade[id].robots
	local robotId = randInt(range[ 1 ], range[ 2 ])
	local config = tb_single_pvp_robot[robotId]
	
	local x = tb_single_pvp_base[ 1 ].enterPos[ 2 ][ 1 ]
	local y = tb_single_pvp_base[ 1 ].enterPos[ 2 ][ 2 ]
	local image = self:GetImageInfo(config)
	self:AddImageBody(image, x, y, "AI_Qualify", nil, nil, nil, self.AI_ALIAS_NAME)	
end

-- ���ʽ��ʼ
function InstanceQualify:OnTaskStart()
	local timestamp = os.time() + tb_single_pvp_base[ 1 ].startcd
	self:SetMapStartTime(timestamp)
	-- ������ʱ��
	self:SetMapQuestEndTime(timestamp + tb_single_pvp_base[ 1 ].time)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp + tb_single_pvp_base[ 1 ].time)
end

-- ����ʧ���˳�
function InstanceQualify:instanceFail()
	self:SetMapState(self.STATE_FAIL)
	-- ����Ѫ���ٷֱ��������ж�ʤ�����
	-- ��ͬѪ���ٷֱȶ���
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	if #allPlayers == 0 then
		return
	end
	
	local playerA = allPlayers[ 1 ]
	local playerB
	if #allPlayers == 2 then
		playerB = allPlayers[ 2 ]
	else
		playerB = mapLib.AliasCreature(self.ptr, self.AI_ALIAS_NAME)
	end
	
	sa, sb = self:sortUnitObject(playerA, playerB)
	-- Ѫ��
	if not sa then
		self:OnFightResult(playerA, GlobalCounter.LOSE, GetUnitName(playerB))
		self:OnFightResult(playerB, GlobalCounter.LOSE, GetUnitName(playerA))
	else
		self:OnFightResult(sa     , GlobalCounter.WIN , GetUnitName(sb))
		self:OnFightResult(sb     , GlobalCounter.LOSE, GetUnitName(sa))
	end
	
	return false
end

-- ����Ѫ���ٷֱ����ȼ������ж�, ��ͬ��
function InstanceQualify:sortUnitObject(unitA, unitB)
	local unitInfoA = UnitInfo:new {ptr = unitA}
	local unitInfoB = UnitInfo:new {ptr = unitB}
	
	local currA		= unitInfoA:GetHealth()
	local currAMax	= unitInfoA:GetMaxHealth()
	local currB		= unitInfoB:GetHealth()
	local currBMax	= unitInfoB:GetMaxHealth()
	if currA * currBMax == currB * currAMax then
		return
	end
	
	if currA * currBMax > currB * currAMax then
		return unitA, unitB
	end
	
	return unitB, unitA
end

--������״̬�����仯ʱ�䴥��
function InstanceQualify:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceQualify.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

--��Ҽ����ͼ
function InstanceQualify:OnJoinPlayer(player)
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
	playerInfo:SetUInt32(PLAYER_INT_FIELD_VIRTUAL_CAMP, playerInfo:GetIntGuid())
	--playerInfo:SetToGroupMode(playerInfo:GetPlayerGuid())
end

function InstanceQualify:DoIsMate(killer_ptr, target_ptr)
	if not killer_ptr or not target_ptr then
		return false
	end
	return GetVirtualCamp(killer_ptr) == GetVirtualCamp(target_ptr)
end

--������뿪ʱ����
function InstanceQualify:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	-- Ѫ����
	local maxHealth = binLogLib.GetUInt32(player, UNIT_FIELD_MAX_HEALTH)
	unitLib.SetHealth(player, maxHealth)
	
	-- �����˳��Ĳ���
	if self:GetMapState() ~= self.STATE_START then
		return
	end
	
	self:SetMapState(self.STATE_FAIL)
	local enemy = self:GetEnemy(player)
	
	-- �˳��������
	self:OnFightResult(player, GlobalCounter.LOSE, GetUnitName(enemy))

	-- ����һ����һ�ʤ
	self:OnFightResult(enemy , GlobalCounter.WIN , GetUnitName(player))
end

function InstanceQualify:GetEnemy(player)
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	for _, exitPlayer in ipairs(allPlayers) do
		if player ~= exitPlayer then
			return exitPlayer
		end
	end
	
	return mapLib.AliasCreature(self.ptr, self.AI_ALIAS_NAME)
end

--����ұ����ɱ��ʱ����
function InstanceQualify:OnPlayerKilled(player, killer)
	self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
	self:SetMapState(self.STATE_FINISH)
	self:OnFightResult(killer, GlobalCounter.WIN , GetUnitName(player))
	self:OnFightResult(player, GlobalCounter.LOSE, GetUnitName(killer))
end

-- ����ұ�����ɱ��
function InstanceQualify:OnPlayerKilledByMonster(player, killer)
	self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
	self:SetMapState(self.STATE_FINISH)
	self:OnFightResult(player, GlobalCounter.LOSE, GetUnitName(killer))
end

function InstanceQualify:OnPlayerWin(player, fightName)
	self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
	self:SetMapState(self.STATE_FINISH)
	self:OnFightResult(player, GlobalCounter.WIN, fightName)
end

-- ������
function InstanceQualify:OnFightResult(player, result, fightName)
	-- ������ҵĲ�������
	if GetUnitTypeID(player) ~= TYPEID_PLAYER then
		return
	end
	
	local dict = {}
	local playerInfo = UnitInfo:new {ptr = player}
	local vip = playerInfo:GetVIP()
	local indx = playerInfo:unitCalcQueueIndx()
	local gradeConfig = tb_single_pvp_grade[indx]
	local modfiyScore = 0
	local instanceRet
	if result == GlobalCounter.WIN then
		instanceRet = self.STATE_FINISH
		for i = 1, #gradeConfig.itemWinKeys do
			local entry = gradeConfig.itemWinKeys[ i ]
			local count = math.floor(gradeConfig.itemWinValues[ i ] * (1 + tb_vip_base[vip].qualifyReward / 100))
			dict[entry] = count
		end
		modfiyScore = gradeConfig.win
	else
		instanceRet = self.STATE_FAIL
		for i = 1, #gradeConfig.itemLoseKeys do
			local entry = gradeConfig.itemLoseKeys[ i ]
			local count = math.floor(gradeConfig.itemLoseValues[ i ] * (1 + tb_vip_base[vip].qualifyReward / 100))
			dict[entry] = count
		end
		modfiyScore = -gradeConfig.lose
	end
	
	-- ��ý���
	PlayerAddRewards(player, dict, MONEY_CHANGE_SINGLE_PVP, LOG_ITEM_OPER_TYPE_SINGLE_PVP)
	-- ɨ���Ľ������
	local list = Change_To_Item_Reward_Info(dict, true)
	
	local score = playerInfo:unitGetQualifyScore()
	
	playerInfo:call_send_instance_result(instanceRet, self.exit_time, list, INSTANCE_SUB_TYPE_QUALIFY, string.format('%d|%d', modfiyScore, score+modfiyScore))
	-- ֪ͨӦ�÷����
	playerLib.SendToAppdDoSomething(player, SCENED_APPD_SINGLE_PVP_RESULT, result, fightName)
end

AI_Qualify = class("AI_Qualify", AI_Base)
AI_Qualify.ainame = "AI_Qualify"

--����
function AI_Qualify:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)

	local instanceInfo = InstanceQualify:new{ptr = map_ptr}
	if GetUnitTypeID(killer_ptr) == TYPEID_UNIT then
		killer_ptr = creatureLib.GetMonsterHost(killer_ptr)
	end
	instanceInfo:OnPlayerWin(killer_ptr, GetUnitName(owner))
	
	return 0
end

return InstanceQualify