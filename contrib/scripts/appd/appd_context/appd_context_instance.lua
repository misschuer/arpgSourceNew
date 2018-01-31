-- ����ܷ����VIP����
function PlayerInfo:checkVipMapTeleport(id, hard)
	-- ϵͳδ����
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_VIP)) then
		return
	end

	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterVIP(id, hard)
end

-- ͨ��VIP�ؿ�
function PlayerInfo:passVipInstance(id, hard)
	local instMgr = self:getInstanceMgr()
	instMgr:passVipInstance(id, hard)
end

-- ����ɨ��
function PlayerInfo:sweepVIP(id)
	-- ϵͳδ����
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_VIP)) then
		return
	end
	-- ÿ����Ϣ4��byte[0:�´���Ҫͨ���Ѷ�,1:��ǰ�Ѷ�,2:��ս����,3:�������]
	local config = tb_map_vip[id]
	local indx = INSTANCE_INT_FIELD_VIP_START + id - 1
	local instMgr = self:getInstanceMgr()
	
	-- �ж��Ƿ���Ҫ����
	local times = instMgr:GetByte(indx, 2)
	if times < config.times then
		outFmtError("not need to buy because of full times")
		return
	end
	
	-- ��ͨ���ѶȲ�����ս
	local hard = instMgr:GetByte(indx, 1)
	if hard == 0 then
		outFmtError("not pass any hard in id = %d", id)
		return
	end
	
	-- �����������
	local buyTimes = instMgr:GetByte(indx, 3)
	if buyTimes >= #config.cost then
		outFmtError("buy times is not enough")
		return
	end
	
	local cost = config.cost[buyTimes+1]
	
	if self:costMoneys(MONEY_CHANGE_BUY_VIP_INSTANCE, {{MONEY_TYPE_GOLD_INGOT, cost}}) then
		instMgr:AddByte(indx, 3, 1)
		instMgr:sweepVIPInstance(id, hard)
	end
	
end
---------------------------��Դ����-----------------------------
-- ����ܷ������Դ����
function PlayerInfo:checkResMapTeleport(id)
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterResInstance(id)
end

---------------------------������-----------------------------
-- ����ܷ��������������
function PlayerInfo:checkTrialMapTeleport()
	-- ϵͳδ����
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_TRIAL)) then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterTrial()
end

-- ͨ�عؿ�
function PlayerInfo:passTrialInstance(id)
	local instMgr = self:getInstanceMgr()
	instMgr:passInstance(id)
	
	-- ����������ͨ�ز���
	if self:GetUInt32(PLAYER_FIELD_TRIAL_LAYERS) < id then
		self:SetUInt32(PLAYER_FIELD_TRIAL_LAYERS, id)
	end
	-- ��������
	rankInsertTask(self:GetGuid(), RANK_TYPE_TRIAL)
	if tb_instance_trial[id].show_notice == 1 then
		self:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_TRIAL_WIN,{self:GetNoticeName(),id})
	end
	self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_TRIAL_TOWER_FLOOR, {})
end


-- һ��ɨ��
function PlayerInfo:sweepTrial()
	-- ϵͳδ����
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_TRIAL)) then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:sweepTrialInstance()
end

-- ����������
function PlayerInfo:resetTrial()
	local instMgr = self:getInstanceMgr()
	instMgr:resetTrialInstance()
end


-- ͨ�عؿ�
function PlayerInfo:passResInstance(id)
	local instMgr = self:getInstanceMgr()
	instMgr:passResInstance(id)
	
end

-- ��ȡ�״�ͨ�عؿ�����
function PlayerInfo:pickResInstanceFirstReward(id)
	local instMgr = self:getInstanceMgr()
	instMgr:onPickResInstanceFirstReward(id)
	
end

-----------ͨ������ð��-----------
function PlayerInfo:passWorldRiskInstance(id)
	local questMgr = self:getQuestMgr()
	questMgr:OnUpdate(QUEST_TARGET_TYPE_PASS_WORLD_RISK, {id})
	
	globalCounter:onRiskRank(self, id)
	
	if math.floor(tb_risk_data[id].nextId /1000) - math.floor(id/1000) > 0 then
		self:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_RISK_CHAPTER,{self:GetNoticeName(),math.floor(id/1000) - 1000})
	end
end



function PlayerInfo:sweepResInstance(id)
	local vip = self:GetVIP()
	if vip <= 0 then
		outFmtDebug("not vip cannot sweepResInstance")
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:sweepResInstance(id)
end

function makeGroupInstanceGeneralId(instSubType, param)
	local generalId = nil
	if instSubType == INSTANCE_SUB_TYPE_GROUP_EXP then
		generalId = string.format("#%d#%d", param[ 1 ], os.time())
	elseif instSubType == INSTANCE_SUB_TYPE_KUAFU_GROUP then
		generalId = string.format("|%d|%d", param[ 1 ], os.time())
	end
	
	return generalId
end


-- ����ܷ������Ӿ��鸱��
function PlayerInfo:checkGroupExpMapTeleport(generalId)
	if not self:checkGroupExpAvailable() then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterGroupExp(generalId)
end

function PlayerInfo:checkGroupExpAvailable()
	-- ϵͳδ����
	if (not self:GetOpenMenuFlag(MODULE_TEAMINSTANCE, MODULE_TEAMINSTANCE_EXP)) then
		return false
	end
	local instMgr = self:getInstanceMgr()
	
	return instMgr:GetGroupExpDailyTimes() > 0
end

function PlayerInfo:checkGroupInstanceTeleport(indx, generalId)
	if not self:checkGroupInstanceAvailable(indx) then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterGroupInstance(indx, generalId)
end

function PlayerInfo:checkGroupInstanceAvailable(indx)
	if (not self:GetOpenMenuFlag(MODULE_INSTANCE, MODULE_INSTANCE_TEAM)) then
		return false
	end
	
	local config = tb_group_instance_base[indx]
	local levelRange = config.limLev
	local level = self:GetLevel()
	if not (levelRange <= level) then
		return false
	end
	
	local instMgr = self:getInstanceMgr()
	local count = instMgr:GetGroupInstanceChallengeCount()
	if self:GetGroupInstanceClearFlag(indx) and count == 0 then
		outFmtError("checkGroupInstanceAvailable ticket not enough")
		return false
	end
	
	return true
end

-----------------------------------------------------------------------------------
--- ����ģ��ÿ������
function PlayerInfo:instanceDailyReset()
	local instMgr = self:getInstanceMgr()
	instMgr:instanceDailyReset()
end














-----------------����BOSS----------------

-- ���б���
function onEnrole(playerInfo)
	-- һ��Ҫ�Ǳ����׶�
	if not globalValue:IsWorldBossEnroll() then
		outFmtDebug("========================= not in enroll time")
		return
	end
	
	WorldBossEnroll(playerInfo:GetGuid())
	local id = globalValue:GetWorldBossTimes()
	playerInfo:SetLastJoinID(id)
	playerInfo:SetLastState(PLAYER_WORLD_BOSS_ENROLLED)
	playerInfo:SetLastLine(0)
	playerInfo:SetLastDeath(0)
	
	playerInfo:CallScenedDoSomething(APPD_SCENED_WORLD_BOSS_WAITING)
end

function ClearWorldBossEnrollData()
	ResetWorldBossEnroll()
end

-- ��ñ������������
function GetEnrolledPlayer()
	local tb = {}
	local enrollInfo = GetWorldBossEnrollInfo()
	for _, playerGuid in pairs(enrollInfo) do
		local playerInfo = app.objMgr:getObj(playerGuid)
		-- outFmtDebug(playerGuid, playerInfo)
		if playerInfo  and playerInfo:isLogined()  then
			table.insert(tb, playerInfo)
		end
	end
	
	return tb
end

-- ��������boss
function OnEnrollWorldBoss()
	-- ����BOSS��������+1
	globalValue:AddWorldBossTimes()
	-- ���ñ���״̬
	globalValue:SetWorldBossState(WORLD_BOSS_PROCESS_ENROLL)
	-- ���ñ���ʱ��
	globalValue:SetEnrollTime()
	--��������BOSS��������
	ClearWorldBossEnrollData()
end

-- ��������BOSS����
function ArrangeWorldBossRoom()
	
	local playerDict = GetEnrolledPlayer()
	local count = #playerDict
	
	if count == 0 then
		return {}, {}
	end
	
	local room = math.ceil(count / tb_worldboss_time[ 1 ].roomLimit)
	local playersPerRoom = math.floor(count / room)
	local rest = count % room
	
	-- ���ÿ���������ɵ�����
	local roomInfo = {}
	for i = 1, room do
		local num = playersPerRoom
		if rest > 0 then
			rest = rest - 1
			num = num + 1
		end
		table.insert(roomInfo, num)
	end
	
	return playerDict, roomInfo
end

-- ���д���
function DoWorldBossTeleport(playerDict, roomInfo)
	local line = 1
	for _, playerInfo in pairs(playerDict) do
		-- ���д���(��Ҫ�Ļ����з�ʱ����)
		playerInfo:CallScenedDoSomething(APPD_SCENED_WORLD_BOSS_ENTER, line)
		roomInfo[line] = roomInfo[line] - 1
		if roomInfo[line] == 0 then
			line = line + 1
		end
		-- �μ�Ұ��BOSS
		local questMgr = playerInfo:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_WORLD_BOSS)
		
		playerInfo:AddActiveItem(VITALITY_TYPE_WORLD_BOSS)
	end
end

function PlayerInfo:checkMassBossMapTeleport(bossId)
	-- ģ��û�� ���ý�
	if not self:GetOpenMenuFlag(MODULE_BOSS, MODULE_BOSS_RISK_BOSS) then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterMassBoss(bossId)
end


--------------------------------------
--����BOSS

function PlayerInfo:checkPrivateBossMapTeleport(id)
	-- ģ��û�� ���ý�
	--if not self:GetOpenMenuFlag(MODULE_BOSS, MODULE_BOSS_RISK_BOSS) then
	--	return
	--end
	
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterPrivateBoss(id)
end

function PlayerInfo:onPrivateBossWin(id)
	
	local instMgr = self:getInstanceMgr()
	instMgr:updatePrivateBossRecoverTime(id)
	
	self:AddActiveItem(VITALITY_TYPE_PRIVATE_BOSS)
	
	self:SetBit(PLAYER_INT_FIELD_PRIVATE_BOSS_FLAG,id)
end


-------------------------------
--���ظ���
function PlayerInfo:SetPassedStageInstanceId(val)
	self:SetUInt32(PLAYER_INT_FIELD_PASSED_STAGE_INSTANCE_ID,val)
end

function PlayerInfo:GetPassedStageInstanceId()
	return self:GetUInt32(PLAYER_INT_FIELD_PASSED_STAGE_INSTANCE_ID)
end

--�����봳�ظ���

function PlayerInfo:checkStageInstanceTeleport(id)
	if self:GetPassedStageInstanceId() + 1 ~= id then
		return
	end
	
	local config = tb_instance_stage[ id ]
	
	if not config then
		return
	end
	
	-- �жϵȼ��Ƿ��㹻
	if self:GetLevel() < config.limLev then
		outFmtError("checkStageInstanceTeleport no level to enter id = %s  %d < %d", id , self:GetLevel(), config.limLev)
		return
	end
	
	local x 	= config.x
	local y 	= config.y
	local mapid = config.mapid
	local buffEffectId = 0
	if self:GetForce() >= config.force then
		buffEffectId = tb_instance_stage_base[1].buffEffectId
	else
		buffEffectId = tb_instance_stage_base[1].debuffEffectId
	end
	
	
	-- ������
	call_appd_teleport(self:GetScenedFD(), self:GetGuid(), x, y, mapid, string.format("%d:%d:%s",id,buffEffectId,self:GetGuid()))
	
	--self:AddActiveItem(VITALITY_TYPE_MASS_BOSS)
	--self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_JOIN_MASS_BOSS_TIMES, {})
	
end

--ͨ�ش��ظ���
function PlayerInfo:onPassStageInstance(id)
	local config = tb_instance_stage[ id ]
	
	if config then
		if id > self:GetPassedStageInstanceId() then
			self:SetPassedStageInstanceId(id)
			self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_STAGE_INSTANCE_ID, {})
		end
	end
end

--��ȡ���عؿ����佱��
function PlayerInfo:PickStageInstanceBonus(id)
	local instMgr = self:getInstanceMgr()
	instMgr:checkPickStageInstanceBonus(id)
end

