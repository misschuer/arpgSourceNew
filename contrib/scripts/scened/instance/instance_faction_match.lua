InstanceFactionMatch = class("InstanceFactionMatch", InstanceInstBase)

InstanceFactionMatch.Name = "InstanceFactionMatch"
InstanceFactionMatch.exit_time = 10

function InstanceFactionMatch:ctor(  )
	
end

function InstanceFactionMatch:SetDetailId(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_DETAIL_ID,value)
end

function InstanceFactionMatch:GetDetailId()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_DETAIL_ID)
end

function InstanceFactionMatch:SetWall(value)
	self:SetUInt32(MAP_INT_FIELD_WALL,value)
end

function InstanceFactionMatch:GetWall()
	return self:GetUInt32(MAP_INT_FIELD_WALL)
end

function InstanceFactionMatch:SetMatchId1(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_ID_1,value)
end

function InstanceFactionMatch:GetMatchId1()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_ID_1)
end

function InstanceFactionMatch:SetMatchResult1(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_RESULT_1,value)
end

function InstanceFactionMatch:GetMatchResult1()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_RESULT_1)
end

function InstanceFactionMatch:SetMemberCount1(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MEMBER_COUNT_1,value)
end

function InstanceFactionMatch:GetMemberCount1()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MEMBER_COUNT_1)
end

function InstanceFactionMatch:SetScore1(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_SCORE_1,value)
end

function InstanceFactionMatch:GetScore1()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_SCORE_1)
end

function InstanceFactionMatch:SetBuff1(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_BUFF_1,value)
end

function InstanceFactionMatch:GetBuff1()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_BUFF_1)
end

function InstanceFactionMatch:SetFlag1(offset)
	self:SetBit(FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_1,offset)
end

function InstanceFactionMatch:UnSetFlag1(offset)
	self:UnSetBit(FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_1,offset)
end

function InstanceFactionMatch:GetFlag1(offset)
	return self:GetBit(FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_1,offset)
end

function InstanceFactionMatch:SetFactionIcon1(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_ICON_1,value)
end

function InstanceFactionMatch:SetFactionGuid1(value)
	self:SetStr(FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_GUID_1,value)
end

function InstanceFactionMatch:GetFactionGuid1()
	return self:GetStr(FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_GUID_1)
end

function InstanceFactionMatch:SetFactionName1(value)
	self:SetStr(FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_NAME_1,value)
end

function InstanceFactionMatch:GetFactionName1()
	return self:GetStr(FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_NAME_1)
end

function InstanceFactionMatch:SetMatchId2(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_ID_2,value)
end

function InstanceFactionMatch:GetMatchId2()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_ID_2)
end

function InstanceFactionMatch:SetMatchResult2(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_RESULT_2,value)
end

function InstanceFactionMatch:GetMatchResult2()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_RESULT_2)
end

function InstanceFactionMatch:SetMemberCount2(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MEMBER_COUNT_2,value)
end

function InstanceFactionMatch:GetMemberCount2()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_MEMBER_COUNT_2)
end

function InstanceFactionMatch:SetScore2(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_SCORE_2,value)
end

function InstanceFactionMatch:GetScore2()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_SCORE_2)
end

function InstanceFactionMatch:SetBuff2(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_BUFF_2,value)
end

function InstanceFactionMatch:GetBuff2()
	return self:GetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_BUFF_2)
end

function InstanceFactionMatch:SetFlag2(offset)
	self:SetBit(FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_2,offset)
end

function InstanceFactionMatch:UnSetFlag2(offset)
	self:UnSetBit(FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_2,offset)
end

function InstanceFactionMatch:GetFlag2(offset)
	return self:GetBit(FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_2,offset)
end

function InstanceFactionMatch:SetFactionIcon2(value)
	self:SetUInt32(FACTION_MATCH_INSTANCE_INT_FIELD_ICON_2,value)
end

function InstanceFactionMatch:SetFactionGuid2(value)
	self:SetStr(FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_GUID_2,value)
end

function InstanceFactionMatch:GetFactionGuid2()
	return self:GetStr(FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_GUID_2)
end

function InstanceFactionMatch:SetFactionName2(value)
	self:SetStr(FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_NAME_2,value)
end

function InstanceFactionMatch:GetFactionName2()
	return self:GetStr(FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_NAME_2)
end

--��ʼ���ű�����
function InstanceFactionMatch:OnInitScript()
	
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	
	InstanceInstBase.OnInitScript(self) --���û���
	
	--self:OnTaskStart()
	--self:AddCountDown()
	
	-- ����generalid
	self:parseGeneralId()
	
	
	local timestamp1 = globalValue:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_SATRT_TIME)
	--self:SetMapStartTime(os.time())
	self:SetMapStartTime(timestamp1)
	
	
	local timestamp2 = globalValue:GetUInt32(GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_END_TIME)
	self:SetMapEndTime(timestamp2 + InstanceFactionMatch.exit_time)
	
	self:SetMapQuestEndTime(timestamp2)
	--��Ӷ�ʱ�� ÿ�� ���³�����Ϣ
	
	
	if os.time() < timestamp1 then
		--
		--�����赲��Ч
		local config = tb_faction_match_base[1]
		for i = 1 ,#config.wall_pos do
			local x = config.wall_pos[i][1]
			local y = config.wall_pos[i][2]
			local entry = config.wall_id[i]
			local orient = config.wall_pos[i][3]
			
			local gameObject = mapLib.AddGameObject(self.ptr, entry, x, y, GO_GEAR_STATUS_END)
			
			unitLib.SetOrientation(gameObject, orient)
			
			outFmtDebug("gameObject = %s %d", tostring(gameObject), entry)
			mapLib.AddTimeStampTimer(self.ptr, 'removeWallCallback', timestamp1, gameObject)
		end
		self:SetWall(1)
	end
	mapLib.AddTimer(self.ptr, 'OnTimer_UpdateMatchInfo', 1000)
end

function InstanceFactionMatch:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	local token = string.split(generalId,'|')
	local detailId = tonumber(token[1])
	outFmtDebug("InstanceFactionMatch:parseGeneralId detailId %d ",detailId)
	self:SetDetailId(detailId)
	
	self:SetMatchId1(globalCounter:GetFactionMatchDetailInfoMatchId1(detailId))
	local guid1 = globalCounter:GetFactionMatchInfoGuid(self:GetMatchId1())
	self:SetFactionGuid1(guid1)
	self:SetFactionName1(globalCounter:GetFactionMatchInfoName(self:GetMatchId1()))
	local faction1 = app.objMgr:getObj(guid1)
	if faction1 then
		self:SetFactionIcon1(faction1:GetFactionFlagsId())
	end
	
	self:SetMatchId2(globalCounter:GetFactionMatchDetailInfoMatchId2(detailId))
	local guid2 = globalCounter:GetFactionMatchInfoGuid(self:GetMatchId2())
	self:SetFactionGuid2(guid2)
	self:SetFactionName2(globalCounter:GetFactionMatchInfoName(self:GetMatchId2()))
	
	local faction2 = app.objMgr:getObj(guid2)
	if faction2 then
		self:SetFactionIcon2(faction2:GetFactionFlagsId())
	end
	
	--�����Ƿ�����ʤbuff
	local winstrike = globalValue:GetFactionMatchChampionWinstrikeCount()
	local buffEffectId = 0
	if winstrike <= 1 then
		buffEffectId = 0
	elseif tb_faction_match_winstrike[winstrike] then
		buffEffectId = tb_faction_match_winstrike[winstrike].buffEffectId
	else
		buffEffectId = tb_faction_match_winstrike[30].buffEffectId
	end
	
	if detailId >= 0 and detailId <= 10 then --��һ�� �� �ڶ��־���
		if self:GetMatchId1() == 0 then
			self:SetBuff2(buffEffectId)
		elseif self:GetMatchId2() == 0 then
			self:SetBuff1(buffEffectId)
		end
	end
	
	--��������
	local config = tb_faction_match_base[1]
	for i = 1 ,#config.flag_pos do
		local x = config.flag_pos[i][1]
		local y = config.flag_pos[i][2]
		local entry = config.flag_id[1]
		local orient = config.flag_pos[i][3] * math.pi / 180
		
		local gameObject = mapLib.AddGameObject(self.ptr, entry, x, y, GO_GEAR_STATUS_END,i)
		
		
		unitLib.SetOrientation(gameObject, orient)
	end
end

function InstanceFactionMatch:removeWallCallback(gameObject)
	outFmtDebug("removeWallCallback remove wall")
	mapLib.RemoveWorldObject(self.ptr, gameObject)
	self:SetWall(0)
end

function InstanceFactionMatch:OnTimer_UpdateMatchInfo()
	local detailId = self:GetDetailId()
	self:SetMatchResult1(globalCounter:GetFactionMatchDetailInfoMatchResult1(detailId))
	self:SetMemberCount1(globalCounter:GetFactionMatchDetailInfoMemberCount1(detailId))
	self:SetScore1(globalCounter:GetFactionMatchDetailInfoScore1(detailId))
	for i = 0,4 do
		if globalCounter:GetFactionMatchDetailInfoFlag1(detailId,i) then
			self:SetFlag1(i)
		else
			self:UnSetFlag1(i)
		end
	end
	
	
	self:SetMatchResult2(globalCounter:GetFactionMatchDetailInfoMatchResult2(detailId))
	self:SetMemberCount2(globalCounter:GetFactionMatchDetailInfoMemberCount2(detailId))
	self:SetScore2(globalCounter:GetFactionMatchDetailInfoScore2(detailId))
	for i = 0,4 do
		if globalCounter:GetFactionMatchDetailInfoFlag2(detailId,i) then
			self:SetFlag2(i)
		else
			self:UnSetFlag2(i)
		end
	end
	
	--self:UpdateFlagObject()
	if self:GetMatchResult1() ~= 0 or self:GetMatchResult2() ~= 0 then
		self:SetMapState(self.STATE_FINISH)
		return false
	end
	
	return true
end

-- ����ʧ���˳�
function InstanceFactionMatch:timeoutCallback()
	-- ��ý���
	--self:SetMapState(self.STATE_FINISH)
	return false
end

--������״̬�����仯ʱ�䴥��
function InstanceFactionMatch:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH then
		
		--10s���������
		local timestamp = os.time() + InstanceFactionMatch.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

-- �ж��Ƿ����˳�����
function InstanceFactionMatch:DoPlayerExitInstance(player)
	return 1	--����1�Ļ�Ϊ�����˳�������0�����˳�
end

--��Ҽ����ͼ
function InstanceFactionMatch:OnJoinPlayer(player)	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻�������ֱ�ӵ���ȥ
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		return
	end
	
	local factionId = playerInfo:GetFactionId()
	local count1 = globalCounter:GetFactionMatchDetailInfoMemberCount1(self:GetDetailId())
	local count2 = globalCounter:GetFactionMatchDetailInfoMemberCount2(self:GetDetailId())
	if factionId == self:GetFactionGuid1() then
		globalCounter:SetFactionMatchDetailInfoMemberCount1(self:GetDetailId(),count1 + 1)
	elseif factionId == self:GetFactionGuid2() then
		globalCounter:SetFactionMatchDetailInfoMemberCount2(self:GetDetailId(),count2 + 1)
	end
end

--������뿪ʱ����
function InstanceFactionMatch:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	-- ����������˾Ͳ����д���
	if self:GetMapState() == self.STATE_FINISH then
		return
	end
	
	local playerInfo = UnitInfo:new{ptr = player}
	
	local factionId = playerInfo:GetFactionId()
	local count1 = globalCounter:GetFactionMatchDetailInfoMemberCount1(self:GetDetailId())
	local count2 = globalCounter:GetFactionMatchDetailInfoMemberCount2(self:GetDetailId())

	if factionId == self:GetFactionGuid1() then
		globalCounter:SetFactionMatchDetailInfoMemberCount1(self:GetDetailId(),math.max(count1 - 1,0))
		
		if self:GetBuff1() > 0 then
			local buff_id = tb_buff_effect[self:GetBuff1()].buff_id
			unitLib.RemoveBuff(player,buff_id)
		end
	elseif factionId == self:GetFactionGuid2() then
		globalCounter:SetFactionMatchDetailInfoMemberCount2(self:GetDetailId(),math.max(count2 - 1,0))
		if self:GetBuff2() > 0 then
			local buff_id = tb_buff_effect[self:GetBuff2()].buff_id
			unitLib.RemoveBuff(player,buff_id)
		end
	end
	
end


function InstanceFactionMatch:DoMapBuffBonus(unit)
	if GetUnitTypeID(unit) == TYPEID_PLAYER then
		local playerInfo = UnitInfo:new{ptr = unit}
		
		local factionId = playerInfo:GetFactionId()
		
		local buffEffectId = 0
		if factionId == self:GetFactionGuid1() then
			buffEffectId = self:GetBuff1()
		elseif factionId == self:GetFactionGuid2() then
			buffEffectId = self:GetBuff2()
		end
		
		if buffEffectId > 0 then
			local buff_id = tb_buff_effect[buffEffectId].buff_id
			SpelladdBuff(unit, buff_id, unit, buffEffectId, 65535)
		end
	end
end

--����������󴥷�()
function InstanceFactionMatch:OnPlayerDeath(player)
	-- ���״̬�Ѿ��ı�, ��ʹ����Ҳ���ٸ���ʱ��
	if self:GetMapState() ~= self.STATE_START then
		return
	end
	
	local phaseId = globalValue:GetFactionMatchCurrentsPhase()
	
	if phaseId == 0 then
		return
	end
	local script = tb_faction_match_phase[phaseId].script
	
	if script ~= FACTION_MATCH_SCRIPT_TYPE_START_FIRST and script ~= FACTION_MATCH_SCRIPT_TYPE_START_SECOND then
		return
	end
	
	local playerInfo = UnitInfo:new{ptr = player}
	
	local factionId = playerInfo:GetFactionId()
	
	local kill_score_gain = tb_faction_match_base[1].kill_score_gain
	local score1 = 0
	local score2 = 0
	if factionId == self:GetFactionGuid1() then
		score2 = kill_score_gain
		
	elseif factionId == self:GetFactionGuid2() then
		score1 = kill_score_gain
	end
	
	globalValue:AddFactionMatchScore(self:GetDetailId(),score1,score2)
end


-- �����
function InstanceFactionMatch:DoAfterRespawn(unit_ptr)
	local unitInfo = UnitInfo:new{ptr = unit_ptr}
	-- ���޵�buff
	unitLib.AddBuff(unit_ptr, BUFF_INVINCIBLE, unit_ptr, 1, 3)
	
	local unitInfo = UnitInfo:new {ptr = unit_ptr}
	if unitInfo:GetTypeID() == TYPEID_PLAYER then
		-- ������� �˳����
		if unitInfo:GetUseRespawnMapId() > 0 then
			if unitInfo:GetUseRespawnMapId() ~= self:GetMapId() then
				mapLib.ExitInstance(self.ptr, unit_ptr)
			end
		else
			self:FindAPlaceToRespawn(unit_ptr)
		end
		unitInfo:SetUseRespawnMapId(0)
	end
end

function InstanceFactionMatch:FindAPlaceToRespawn(unit_ptr)
	local toX = randInt(-3,3)
	local toY = randInt(-3,3)
	
	local unitInfo = UnitInfo:new {ptr = unit_ptr}
	local death_pos_x, death_pos_y = unitLib.GetPos(unit_ptr)
	local factionId = unitInfo:GetFactionId()
	
	local config = tb_faction_match_base[1]
	local index = 0
	local near_dis = 999999
	if factionId == self:GetFactionGuid1() then
		for i = 1,5 do
			if self:GetFlag1(i-1) then
				local flag_pos_x = config.flag_pos[i][1]
				local flag_pos_y = config.flag_pos[i][2]
				
				local dist = math.pow(flag_pos_x-death_pos_x,2) + math.pow(flag_pos_y-death_pos_y,2)
				
				if dist < near_dis then
					near_dis = dist
					index = i
				end
			end
		end
		if index == 0 then
			toX = toX + config.born_1[1]
			toY = toY + config.born_1[2]
		else
			toX = toX + config.flag_pos[index][1]
			toY = toY + config.flag_pos[index][2]
		end
	elseif factionId == self:GetFactionGuid2() then
		for i = 1,5 do
			if self:GetFlag2(i-1) then
				local flag_pos_x = config.flag_pos[i][1]
				local flag_pos_y = config.flag_pos[i][2]
				
				local dist = math.pow(flag_pos_x-death_pos_x,2) + math.pow(flag_pos_y-death_pos_y,2)
				
				if dist < near_dis then
					near_dis = dist
					index = i
				end
			end
		end
		
		if index == 0 then
			toX = toX + config.born_2[1]
			toY = toY + config.born_2[2]
		else
			toX = toX + config.flag_pos[index][1]
			toY = toY + config.flag_pos[index][2]
		end
	else
		mapLib.ExitInstance(self.ptr, unit_ptr)
	end
	
	local toMapId = tb_faction_match_base[1].map_id
	local lineNo = self:GetMapLineNo()
	local generalId	= self:GetMapGeneralId()
	playerLib.Teleport(unit_ptr, toMapId, toX, toY, lineNo, generalId)
	
	outFmtDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FindAPlaceToRespawn death x %d y %d  to  x %d y %d  flag index %d",death_pos_x,death_pos_y,toX,toY,index)
end

--ʹ����Ϸ����֮ǰ
--����1�Ļ��ͼ���ʹ����Ϸ���󣬷���0�Ļ��Ͳ�ʹ��
function InstanceFactionMatch:OnBeforeUseGameObject(user, go, go_entryid, posX, posY)
	-- ����Ѿ����� �Ͳ��ܼ���
	if unitLib.HasBuff(user, BUFF_INVINCIBLE) then
		return 0
	end
	
	if Script_Gameobject_Pick_Check(user, go_entryid, posX, posY) then
		return 1
	end
	return 0
end

--ʹ����Ϸ����
--����1�Ļ��ɹ�ʹ����Ϸ���󣬷���0�Ļ�ʹ�ò��ɹ�
function InstanceFactionMatch:OnUseGameObject(user, go, go_entryid, posX, posY)
	-- �ж϶�Ӧ��������buff
--[[
for _, obj in ipairs(tb_buff_xianfu) do
		if obj.gameobject_id == go_entryid then
			local effects = obj.type_effect
			for _, effect in pairs(effects) do
				local buffId = effect[ 1 ]
				local lv = effect[ 2 ]
				local duration = tb_buff_template[buffId].duration
				--SpelladdBuff(user, buffId, user, lv, duration)
			end
			break
		end
	end
--]]
	--outFmtDebug("###################OnUseGameObject go_entryid  %d",go_entryid)
	local phaseId = globalValue:GetFactionMatchCurrentsPhase()
	
	if phaseId == 0 then
		return
	end
	local script = tb_faction_match_phase[phaseId].script
	
	if script ~= FACTION_MATCH_SCRIPT_TYPE_START_FIRST and script ~= FACTION_MATCH_SCRIPT_TYPE_START_SECOND then
		return
	end
	
	local x, y = unitLib.GetPos(go)
	local goInfo = UnitInfo:new{ptr = go}
	local index = goInfo:GetInt32(GO_FIELD_DATA + 1)
	
	
	outFmtDebug("###################OnUseGameObject go_entryid  %d index %d",go_entryid,index)
	
	local playerInfo = UnitInfo:new{ptr = user}
	
	local factionId = playerInfo:GetFactionId()
	
	local config = tb_faction_match_base[1]
	local entry = config.flag_id[2]
	local orient = config.flag_pos[index][3] * math.pi / 180
	local team_id = 1
	if factionId == self:GetFactionGuid2() then
		entry = config.flag_id[3]
		team_id = 2
	end
	
	if entry == goInfo:GetEntry() then
		outFmtDebug("###################OnUseGameObject go_entryid  %d index %d is entry %d do nothing",go_entryid,index,entry)
		return
	end
	
	outFmtDebug("###################OnUseGameObject go_entryid  %d index %d replace by entry %d",go_entryid,index,entry)
	
	mapLib.RemoveWorldObject(self.ptr, go)
	local gameObject = mapLib.AddGameObject(self.ptr, entry, x, y, GO_GEAR_STATUS_END,index)
	
	unitLib.SetOrientation(gameObject, orient)
	
	globalValue:CheckChangeFactionMatchFlagBelong(self:GetDetailId(),team_id,index - 1)
	
	return 1	
end


-- �ж��Ƿ�Ǯ��Ԫ������
function InstanceFactionMatch:OnCheckIfCanCostRespawn(player)
	
	local unitInfo = UnitInfo:new {ptr = player}
	if unitInfo:IsAlive() then
		return
	end
	
	self:OnCostRespawn(unitInfo)
end

return InstanceFactionMatch