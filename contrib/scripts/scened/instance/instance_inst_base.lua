InstanceInstBase = class("InstanceInstBase", Instance_base)

InstanceInstBase.Name = "InstanceInstBase"

InstanceInstBase.Time_Out_Fail_Callback = "instanceFail"

InstanceInstBase.Leave_Callback = "prepareToLeave"
InstanceInstBase.player_auto_respan = 9
InstanceInstBase.exit_time = 10

function InstanceInstBase:ctor(  )
	
end

--��ʼ���ű�����
function InstanceInstBase:OnInitScript(  )
	Instance_base.OnInitScript(self) --���û���
end

-- �ж��Ƿ����˳�����
function InstanceInstBase:DoPlayerExitInstance(player)
	local playerInfo = UnitInfo:new {ptr = player}
	-- ����������
	if not playerInfo:IsAlive() then
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
	end
	return 1	--����1�Ļ�Ϊ�����˳�������0�����˳�
end


-- �˳�����ʱ����׼���˳�
function InstanceInstBase:prepareToLeave()
	mapLib.ExitInstance(self.ptr)
end

-- �����ܵĲ���
function InstanceInstBase:GetCurrFinishWave()
	return self:GetUInt16(MAP_INT_FIELD_INSTANCE_WAVE, 0)
end

-- �����ܵĲ���
function InstanceInstBase:SetWaves(val)
	self:SetUInt16(MAP_INT_FIELD_INSTANCE_WAVE, 1, val)
end

-- ���ӵ�ǰ����
function InstanceInstBase:toNextWave()
	self:AddUInt16(MAP_INT_FIELD_INSTANCE_WAVE, 0, 1)
end

-- �жϲ����Ƿ����
function InstanceInstBase:isWaveFinish()
	local curr = self:GetUInt16(MAP_INT_FIELD_INSTANCE_WAVE, 0)
	local alls = self:GetUInt16(MAP_INT_FIELD_INSTANCE_WAVE, 1)
	
	return curr >= alls and alls > 0
end

-- ����ʧ���˳�
function InstanceInstBase:instanceFail()
	self:SetMapState(self.STATE_FAIL)
	local mapid = self:GetMapId()
	local type = tb_map[mapid].inst_sub_type
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	for _, unit_player in ipairs(allPlayers) do
		local playerInfo = UnitInfo:new {ptr = unit_player}
		playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, {}, type, '')
	end
end

--��������
function InstanceInstBase:OnAddQuests(questTable)
	self:ClearQuestMemory()
	for _, quest in pairs(questTable) do
		local instQuestType = quest[ 1 ]
		if Quest_Func_Table[instQuestType] then
			Quest_Func_Table[instQuestType](self, quest)
		end
	end
end

-- ��������λ��
function InstanceInstBase:GetEmptySlot()
	for i = MAP_INT_FIELD_QUESTS_START, MAP_INT_FIELD_QUESTS_END-1, 2 do
		if self:GetByte(i, 0) == 0 then
			return i
		end
	end
	
	return -1
end

function InstanceInstBase:ClearQuestMemory()
	for i = MAP_INT_FIELD_QUESTS_START, MAP_INT_FIELD_QUESTS_END-1 do
		self:SetUInt32(i, 0)
	end
	
	for i = MAP_INT_FIELD_QUESTS_PROCESS_START, MAP_INT_FIELD_QUESTS_PROCESS_END-1 do
		self:SetUInt32(i, 0)
	end
end

----------------------------------------�������� ------------------------------------------
--���ӻ�ɱ��������
function InstanceInstBase:OnAddKillMonsterQuest(quest)
	if(#quest ~= 3) then
		return -1
	end
	
	local indx = self:GetEmptySlot()
	
	if indx < 0 then
		return -1
	end
	
	self:SetByte(indx, 0, quest[ 1 ])
	self:SetByte(indx, 1, quest[ 2 ])
	self:SetUInt16(indx, 1, quest[ 3 ])
	
	return indx
end

--�����ռ���Ʒ����
function InstanceInstBase:OnAddPickItemQuest(quest)
	
end

--���Ӽ����������
function InstanceInstBase:OnAddActiveMachineQuest(quest)
	
end

--�����ػ�NPC����
function InstanceInstBase:OnAddProtectNPCQuest(quest)
	-- ���ӽṹͬ��ɱ��������һ��
	local indx = self:OnAddKillMonsterQuest(quest)
	if indx > 0 then
		local offset = (indx - MAP_INT_FIELD_QUESTS_START) / 2
		local index = 0
		index,offset = getRealOffset(offset,4)
		self:SetByte(MAP_INT_FIELD_QUESTS_PROCESS_START + index, offset, 100)
	end
end

--���ӻ���NPC����
function InstanceInstBase:OnAddEscortNPCQuest(quest)
	
end

--���ӷ�������
function InstanceInstBase:OnAddDefenseQuest(quest)
	
end

--���Ӵ�������
function InstanceInstBase:OnAddBreakThroughQuest(quest)
	
end



--[[
 = 1	-- ��ɱ����
 = 2	-- �ռ���Ʒ
 = 3	-- �������
 = 4	-- �ػ�NPC
 = 5	-- ����NPC
 = 6	-- ����
 = 7	-- ����
]]
Quest_Func_Table = {}
Quest_Func_Table[INSTANCE_QUEST_TYPE_KILL_MONSTER]	= InstanceInstBase.OnAddKillMonsterQuest
Quest_Func_Table[INSTANCE_QUEST_TYPE_PICK_ITEM]		= InstanceInstBase.OnAddPickItemQuest
Quest_Func_Table[INSTANCE_QUEST_TYPE_ACTIVE_MACHINE]= InstanceInstBase.OnAddActiveMachineQuest
Quest_Func_Table[INSTANCE_QUEST_TYPE_PROTECT_NPC]	= InstanceInstBase.OnAddProtectNPCQuest
Quest_Func_Table[INSTANCE_QUEST_TYPE_ESCORT_NPC]	= InstanceInstBase.OnAddEscortNPCQuest
Quest_Func_Table[INSTANCE_QUEST_TYPE_DEFENSE]		= InstanceInstBase.OnAddDefenseQuest
Quest_Func_Table[INSTANCE_QUEST_TYPE_BREAK_THROUGH]	= InstanceInstBase.OnAddBreakThroughQuest


----------------------------------------������ȸ������ ------------------------------------------

-- (1) һ�����ﱻ���ɱ��
function InstanceInstBase:OneMonsterKilled(entry)
	for i = MAP_INT_FIELD_QUESTS_START, MAP_INT_FIELD_QUESTS_END-1, 2 do
		if self:GetByte(i, 0) == INSTANCE_QUEST_TYPE_KILL_MONSTER and self:IsFitForKillMonsterQuest(self:GetUInt16(i, 1), entry) then
			local offset = (i - MAP_INT_FIELD_QUESTS_START) / 2
			local prev = self:GetByte(MAP_INT_FIELD_QUESTS_PROCESS_START, offset)
			
			local index = 0
			index,offset = getRealOffset(offset,4)
			self:SetByte(MAP_INT_FIELD_QUESTS_PROCESS_START + index, offset, prev + 1)
			return true
		end
	end
	
	return false
end

-- �Ƿ������ɱĿ�����
function InstanceInstBase:IsFitForKillMonsterQuest(dest, entry)
	return dest == entry or dest == 0 and tb_creature_template[entry].monster_type == 0
end


-- (4) �ػ��ı�����ɱ��
function InstanceInstBase:ProtectorHit(entry, hpRate)
	for i = MAP_INT_FIELD_QUESTS_START, MAP_INT_FIELD_QUESTS_END-1, 2 do
		if self:GetByte(i, 0) == INSTANCE_QUEST_TYPE_PROTECT_NPC and self:GetUInt16(i, 1) == entry then
			local offset = (i - MAP_INT_FIELD_QUESTS_START) / 2
			hpRate = math.floor(hpRate)
			
			local index = 0
			index,offset = getRealOffset(offset,4)
			self:SetByte(MAP_INT_FIELD_QUESTS_PROCESS_START + index, offset, hpRate)
			return true
		end
	end
	
	return false
end

-- ���м���TODO




----------------------------------------������������� ------------------------------------------

-- ����ʱ�䵽���Ժ���߽��ȸ��º��������Ƿ����
function InstanceInstBase:CheckQuestAfterTargetUpdate(isTimeout)	
	isTimeout = isTimeout or false
	
	local ret = true
	
	for i = MAP_INT_FIELD_QUESTS_START, MAP_INT_FIELD_QUESTS_END-1, 2 do
		local targetType = self:GetByte(i, 0)
		if targetType > 0 then
			if Quest_Check_Func_Table[targetType] then
				local vist = Quest_Check_Func_Table[targetType](self, (i-MAP_INT_FIELD_QUESTS_START)/2, isTimeout)
				if not vist then ret = false end
			end
		end
	end
	
	return ret
end

--����ɱ��������
function InstanceInstBase:OnCheckKillMonsterQuest(indx, isTimeout)
	local offset = MAP_INT_FIELD_QUESTS_START + indx * 2
	local process = self:GetByte(MAP_INT_FIELD_QUESTS_PROCESS_START, indx)
	local target = self:GetByte(offset, 1)
	
	return process >= target
end

--����ռ���Ʒ����
function InstanceInstBase:OnCheckPickItemQuest(indx, isTimeout)
	return false
end

--��鼤���������
function InstanceInstBase:OnCheckActiveMachineQuest(indx, isTimeout)
	return false
end

--����ػ�NPC����
function InstanceInstBase:OnCheckProtectNPCQuest(indx, isTimeout)
	local offset = MAP_INT_FIELD_QUESTS_START + indx * 2
	--local process = self:GetByte(MAP_INT_FIELD_QUESTS_PROCESS_START, indx)
	
	local target = self:GetByte(offset, 1)
	local entry = self:GetUInt16(offset, 1)
	
	local ret = true
	local entryList = mapLib.QueryCreature(self.ptr, entry)
	for _, creature_ptr in pairs(entryList) do
		local creatureInfo = UnitInfo:new {ptr = creature_ptr}
		-- Ŀ��δ�ﵽ
		if creatureInfo:GetHealth() * 100 < creatureInfo:GetMaxHealth() * target then
			ret = false
			break
		end
	end
	-- û��Ŀ��NPC
	if #entryList == 0 then
		ret = false
	end
	
	return ret
end

--��黤��NPC����
function InstanceInstBase:OnCheckEscortNPCQuest(indx, isTimeout)
	return false
end

--����������
function InstanceInstBase:OnCheckDefenseQuest(indx, isTimeout)
	return false
end

--��鴳������
function InstanceInstBase:OnCheckBreakThroughQuest(indx, isTimeout)
	return false
end

--[[
 = 1	-- ��ɱ����
 = 2	-- �ռ���Ʒ
 = 3	-- �������
 = 4	-- �ػ�NPC
 = 5	-- ����NPC
 = 6	-- ����
 = 7	-- ����
]]
Quest_Check_Func_Table = {}
Quest_Check_Func_Table[INSTANCE_QUEST_TYPE_KILL_MONSTER]	= InstanceInstBase.OnCheckKillMonsterQuest
Quest_Check_Func_Table[INSTANCE_QUEST_TYPE_PICK_ITEM]		= InstanceInstBase.OnCheckPickItemQuest
Quest_Check_Func_Table[INSTANCE_QUEST_TYPE_ACTIVE_MACHINE]= InstanceInstBase.OnCheckActiveMachineQuest
Quest_Check_Func_Table[INSTANCE_QUEST_TYPE_PROTECT_NPC]	= InstanceInstBase.OnCheckProtectNPCQuest
Quest_Check_Func_Table[INSTANCE_QUEST_TYPE_ESCORT_NPC]	= InstanceInstBase.OnCheckEscortNPCQuest
Quest_Check_Func_Table[INSTANCE_QUEST_TYPE_DEFENSE]		= InstanceInstBase.OnCheckDefenseQuest
Quest_Check_Func_Table[INSTANCE_QUEST_TYPE_BREAK_THROUGH]	= InstanceInstBase.OnCheckBreakThroughQuest


--����������󴥷�()
function InstanceInstBase:OnPlayerDeath(player)
	local playerInfo = UnitInfo:new{ptr = player}	
	local timestamp = os.time() + 10
	self:AddTimeOutCallback(self.Leave_Callback, timestamp)
end

-------------------------------------------------------------------------------------------

--��Ҽ����ͼ
function InstanceInstBase:OnJoinPlayer(player)
	Instance_base.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	
	--playerInfo:ChangeToPeaceModeAfterTeleport()
	playerInfo:ModifyHealth(playerInfo:GetMaxHealth())
end

--������뿪ʱ����
function InstanceInstBase:OnLeavePlayer( player, is_offline)
	Instance_base.OnLeavePlayer(self, player, is_offline)
	
	--local playerInfo = UnitInfo:new{ptr = player}
	--playerInfo:ChangeToPeaceModeAfterTeleport()
end

return InstanceInstBase