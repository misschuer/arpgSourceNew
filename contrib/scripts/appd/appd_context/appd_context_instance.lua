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

-----------ͨ������ð��-----------
function PlayerInfo:passWorldRiskInstance(id)
	local questMgr = self:getQuestMgr()
	questMgr:OnUpdate(QUEST_TARGET_TYPE_PASS_WORLD_RISK, {id})
	
	globalCounter:onRiskRank(self, id)
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

function PlayerInfo:checkMassBossMapTeleport(id)
	-- ģ��û�� ���ý�
	if not self:GetOpenMenuFlag(MODULE_BOSS, MODULE_BOSS_RISK_BOSS) then
		return
	end
	local instMgr = self:getInstanceMgr()
	instMgr:checkIfCanEnterMassBoss(id)
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
end