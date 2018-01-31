-- 组队管理
local GroupInfo = class('GroupInfo', BinLogObject)
local protocols = require('share.protocols')



--------------------这里进行匹配操作-------------------
function OnGroupMatchPush(groupType, guid)
	outFmtDebug("OnGroupMatchPush groupType = %d, guid = %s", groupType, guid)
	GroupMatchPush(groupType, guid)
end

function OnGroupMatchRemove(guid)
	outFmtDebug("OnGroupMatchRemove guid = %s", guid)
	GroupMatchRemove(guid)
end

function OnGroupSecondMatch()
	local matchList = GetGroupMatchList()
	local groupMatchInfo = {}
	local playerMatchInfo = {}
	
	for _, matchInfo in ipairs(matchList) do
		local groupType = matchInfo[ 1 ]
		local timestamp = matchInfo[ 2 ]
		local guid = matchInfo[ 3 ]
		--outFmtDebug("==== OnGroupSecondMatch groupType = %d timestamp = %d guid = %s", groupType, timestamp, guid)
		if app.objMgr:IsPlayerGuid(guid) then
			if not playerMatchInfo[groupType] then
				playerMatchInfo[groupType] = {}
			end
			local guidObj = app.objMgr:getObj(guid)
			if guidObj then
				local groupId = guidObj:GetGroupId()
				if string.len(groupId) == 0 then
					table.insert(playerMatchInfo[groupType], {guidObj, timestamp})
				else
					guidObj:SetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH, 0)
					OnGroupMatchRemove(guid)
				end
			else
				OnGroupMatchRemove(guid)
			end
		elseif app.objMgr:IsGroupGuid(guid) then
			if not groupMatchInfo[groupType] then
				groupMatchInfo[groupType] = {}
			end
			local guidObj = app.objMgr:getObj(guid)
			if guidObj then
				if not guidObj:IsFullMember() then
					table.insert(groupMatchInfo[groupType], {guidObj, timestamp})
				else
					guidObj:SetUInt32(GROUP_INT_FIELD_STATE, 0)
					OnGroupMatchRemove(guid)
				end
			else
				OnGroupMatchRemove(guid)
			end
		else
			-- 不存在删掉
			OnGroupMatchRemove(guid)
		end
	end
	
	-- 进行排序
	for _, info in pairs(groupMatchInfo) do
		mi_sort(info, function(a, b)
			return a[ 2 ] < b[ 2 ]
		end)
	end
	
	for _, info in pairs(playerMatchInfo) do
		mi_sort(info, function(a, b)
			return a[ 2 ] < b[ 2 ]
		end)
	end
	
	-- 进行匹配 (个人找队伍)
	for groupType, playerQueue in pairs(playerMatchInfo) do
		local groupQueue = groupMatchInfo[groupType]
		-- 有队伍
		if groupQueue and #groupQueue > 0 then
			local pi = 1
			while (pi <= #playerQueue) do
				local matched = false
				local playerInfo = playerQueue[pi][ 1 ]
				
				local pq = 1
				while (pq <= #groupQueue) do 
					local groupInfo = groupQueue[pq][ 1 ]
					-- 判断是否满足目标
					if groupInfo:IsInLevelRange(playerInfo:GetLevel()) then
						-- 加队伍
						groupInfo:addMember(playerInfo)
						playerInfo:SetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH, 0)
						-- 删除个人在匹配队列中的数据
						OnGroupMatchRemove(playerInfo:GetGuid())
						-- 如果队伍匹配满了, 也删除列表
						if groupInfo:IsFullMember() then
							OnGroupMatchRemove(groupInfo:GetGuid())
							groupInfo:SetUInt32(GROUP_INT_FIELD_STATE, 0)
							table.remove(groupQueue, pq)
						end
						matched = true
						break
					end
					pq = pq + 1
				end
				
				if matched then
					table.remove(playerQueue, pi)
				else
					pi = pi + 1
				end
			end
		end
	end
end
-------------------------------------

function GroupInfo:IsFullMember()
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) == 0 then
			return false
		end
	end
	return true
end


function GroupInfo:IsFullMatch()
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) == 0 then
			return false
		end
		
		local state = self:GetUIntValue(memberIndex, GROUP_MEMBER_INT_STATE)
		if state == GROUP_MEMBER_STATE_OFFLINE then
			return false
		end
	end
	
	return true
end


function GroupInfo:GetMemeberCount()
	local count = 0
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) > 0 then
			count = count + 1
		end
	end
	return count
end

function GroupInfo:IsInLevelRange(level)
	local a = self:GetUInt16(GROUP_INT_FIELD_LEVEL_RANGE, 0)
	local b = self:GetUInt16(GROUP_INT_FIELD_LEVEL_RANGE, 1)
	return a <= level and level <= b
end

function GroupInfo:SetLevelRange(min_lev,max_lev)
	if min_lev <= max_lev and min_lev >= 1 and max_lev <= 200 then
		self:SetUInt16(GROUP_INT_FIELD_LEVEL_RANGE, 0,min_lev)
		self:SetUInt16(GROUP_INT_FIELD_LEVEL_RANGE, 1,max_lev)
	else
		self:SetUInt16(GROUP_INT_FIELD_LEVEL_RANGE, 0,1)
		self:SetUInt16(GROUP_INT_FIELD_LEVEL_RANGE, 1,200)
	end
end

function GroupInfo:doGroupExpEnter(playerInfoList, indx)
	local level = 0
	for _, playerInfo in ipairs(playerInfoList) do
		level = level + playerInfo:GetLevel()
	end
	
	level = math.ceil(level / #playerInfoList)
	local generalId = makeGroupInstanceGeneralId(INSTANCE_SUB_TYPE_GROUP_EXP, {level})
	
	for _, playerInfo in ipairs(playerInfoList) do
		playerInfo:checkGroupExpMapTeleport(generalId)
	end
end

function GroupInfo:doGroupInstanceEnter(playerInfoList, indx)
	local generalId = makeGroupInstanceGeneralId(INSTANCE_SUB_TYPE_KUAFU_GROUP, {indx})
	for _, playerInfo in ipairs(playerInfoList) do
		playerInfo:checkGroupInstanceTeleport(indx, generalId)
	end
end

-----------------------------------------------
--[[
回调的方法必须放后面
--]]
GroupInfo.acceptCallback = {
	[INSTANCE_SUB_TYPE_GROUP_EXP] = GroupInfo.doGroupExpEnter,
	[INSTANCE_SUB_TYPE_KUAFU_GROUP] = GroupInfo.doGroupInstanceEnter,
}

--成员退出
function GroupInfo:groupQuit(playerInfo)
	local playerGuid = playerInfo:GetGuid()
	
	local memberIndex = self:GetMemberIndex(playerGuid)
	if memberIndex < 0 then
		return
	end
	
	local isCaptain = self:IsPlayerCaptain(playerGuid)
	self:ClearMember(memberIndex)
	-- IMPORTANT 移除监听
	app.objMgr:callDelWatch(playerInfo:GetSessionId(),self:GetGuid())
	playerInfo:SetGroupId('')
	
	outFmtDebug("player %s is quit group %s ", playerGuid, self:GetGuid())
	-- 如果退出的是队长
	if isCaptain then
		local others = self:GetGroupMemberIndex()
		-- 如果队伍还有人
		if #others > 0 then
			-- 转移队长
			self:onGroupChangeCaptain(others[ 1 ])
		else
			self:groupDissolution()
		end
	end
end

function GroupInfo:groupOffline(playerInfo)
	local playerGuid = playerInfo:GetGuid()
	
	local memberIndex = self:GetMemberIndex(playerGuid)
	if memberIndex < 0 then
		return
	end
	
	local isCaptain = self:IsPlayerCaptain(playerGuid)
	self:SetUIntValue(memberIndex, GROUP_MEMBER_INT_STATE, GROUP_MEMBER_STATE_OFFLINE)
	-- 如果退出的是队长
	if isCaptain then
		local others = self:GetGroupMemberIndex(memberIndex)
		-- 如果队伍还有人
		if #others > 0 then
			-- 转移队长
			self:onGroupChangeCaptain(others[ 1 ])
		else
			self:groupDissolution()
		end
	end
end

function GroupInfo:groupOnline(playerInfo)
	local memberIndex = self:GetMemberIndex(playerInfo:GetGuid())
	if memberIndex < 0 then
		return false
	end
	self:SetUIntValue(memberIndex, GROUP_MEMBER_INT_STATE, GROUP_MEMBER_STATE_NONE)
	app.objMgr:callAddWatch(playerInfo:GetSessionId(), self:GetGuid())
	return true
end


function GroupInfo:onGroupChangeCaptain(memberIndex)
	local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
	self:SetCaptainGuid(playerGuid)
end

function GroupInfo:GetGroupMemberIndex(exclude)
	exclude = exclude or -1
	local list = {}
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) > 0 then
			local state = self:GetUIntValue(memberIndex, GROUP_MEMBER_INT_STATE)
			if state ~= GROUP_MEMBER_STATE_OFFLINE and exclude ~= memberIndex then
				table.insert(list, memberIndex)
			end
		end
	end
	
	return list
end
--[[
	GROUP_MEMBER_STR_GUID		= 0,	// 玩家guid
	MAX_GROUP_MEMBER_INFO_STR_COUNT,
	
	GROUP_STR_FIELD_MEMBER_INFO_START = 0,
	GROUP_STR_FIELD_MEMBER_INFO_END = GROUP_STR_FIELD_MEMBER_INFO_START + MAX_GROUP_MEMBER_COUNT * MAX_GROUP_MEMBER_INFO_STR_COUNT,
--]]

function GroupInfo:ClearMember(memberIndex)
	outFmtDebug("======== ClearMember %d", memberIndex)
	for i = 0, MAX_GROUP_MEMBER_INFO_INT_COUNT-1 do
		self:SetUIntValue(memberIndex, i, 0)
	end

	for i = 0, MAX_GROUP_MEMBER_INFO_STR_COUNT-1 do
		self:SetStrValue(memberIndex, i, '')
	end
end

function preparePush(guid)
	InstancePreparePush(guid)
end

function prepareCancel(guid)
	InstancePrepareCancel(guid)
end

function getPrepareList()
	return GetInstancePrepareInfo()
end

function GroupInfo:captainSendChoiseToPlayer(captainInfo, instSubType, availableCallback)
	local list = {}
	local cnt = 0
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) > 0 then
			local playerInfo = app.objMgr:getObj(playerGuid)
			local name = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_NAME)
			if not playerInfo then
				captainInfo:CallOptResult(OPRATE_TYPE_GROUP, GROUP_NOTICE_TYPE_MEMBER_IS_OFFLINE, {ToShowName(name)})
				return
			end
			
			local mapid = playerInfo:GetMapId()
			if tb_map[mapid].is_instance == 1 then
				-- 通知队长有队员在副本中
				captainInfo:CallOptResult(OPRATE_TYPE_GROUP, GROUP_NOTICE_TYPE_MEMBER_IN_INSTANCE, {ToShowName(name)})
				return
			end
			
			-- 还要考虑次数不足/没有开启的情况
			if availableCallback and not availableCallback(playerInfo) then
				captainInfo:CallOptResult(OPRATE_TYPE_GROUP, GROUP_NOTICE_TYPE_MEMBER_NO_TIMES, {ToShowName(name)})
				return
			end
			
			table.insert(list, playerInfo)
--			level = level + playerInfo:GetLevel()
			cnt = cnt + 1
		end
	end
	
	self:ClearMemberPreparingFlag()
	
	-- 目标副本
	self:SetUInt32(GROUP_INT_FIELD_TARGET_INST, instSubType)
	
	preparePush(self:GetGuid())
	--[[
	-- 给每个玩家发通知
	for _, playerInfo in ipairs(list) do
		playerInfo:call_check_for_group_enter(instSubType)
	end
	--]]
end

function CheckGroupPrepared()
	local now = os.time()
	local last = 15
	local preparedQueue = getPrepareList()
	for guid, timestamp in pairs(preparedQueue) do
		if now >= last + timestamp then
			local groupInfo = app.objMgr:getObj(guid)
			if groupInfo and groupInfo:memberAutoAccept() then
				groupInfo:checkIfAllAccepted()
			else
				prepareCancel(guid)
			end
			
			if groupInfo then
				groupInfo:SetUInt32(GROUP_INT_FIELD_TARGET_INST, 0)
			end
		end
	end
end

function GroupInfo:playerChoise(playerInfo, choise)
	local memberIndex = self:GetMemberIndex(playerInfo:GetGuid())
	if memberIndex < 0 then
		return
	end
	
	if self:CheckResponsed(memberIndex) then
		return
	end
	
	local instSubType = self:GetUInt32(GROUP_INT_FIELD_TARGET_INST)
	if instSubType == 0 then
		return
	end
	
	if choise == 0 then
		local cg = self:GetCaptainGuid()
		local captainInfo = app.objMgr:getObj(cg)
		if captainInfo then
			self:SetUInt32(GROUP_INT_FIELD_TARGET_INST, 0)
			self:GroupSetResponseState(memberIndex, GROUP_MEMBER_RESPONSE_STATE_DECLINE)
			prepareCancel(self:GetGuid())
			-- 有人拒绝加入
			-- captainInfo:CallOptResult(OPRATE_TYPE_GROUP, GROUP_NOTICE_TYPE_MEMBER_DECLINE, {ToShowName(playerInfo:GetName())})
		end
		return
	end
	
	-- 设置状态
	self:GroupSetResponseState(memberIndex, GROUP_MEMBER_RESPONSE_STATE_ACCEPT)
	-- 判断是否全部同意
	self:checkIfAllAccepted()
end

function GroupInfo:memberAutoAccept()
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) > 0 then
			local playerInfo = app.objMgr:getObj(playerGuid)
			if playerInfo and playerInfo:isLogined() then
				if not self:CheckResponsed(memberIndex) then
					self:GroupSetResponseState(memberIndex, GROUP_MEMBER_RESPONSE_STATE_ACCEPT)
				end
			else
				return false
			end
		end
	end
	
	return true
end

-- 判断是否全部同意
function GroupInfo:checkIfAllAccepted()
	local list = {}
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) > 0 then
			if not self:CheckResponseIsAccepted(memberIndex) then
				return
			end
			local playerInfo = app.objMgr:getObj(playerGuid)
			table.insert(list, playerInfo)
		end
	end
	
	-- 这里处理具体进入逻辑
	local indx = math.floor(self:GetUInt32(GROUP_INT_FIELD_TARGET_INST) / 65536)
	local instSubType = self:GetUInt32(GROUP_INT_FIELD_TARGET_INST) % 65536
	self.acceptCallback[instSubType](self, list, indx)
	self:SetUInt32(GROUP_INT_FIELD_TARGET_INST, 0)
	self:GetGuid(self:GetGuid())
	prepareCancel(self:GetGuid())
end

function GroupInfo:GetGroupGuidList()
	local list = {}
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) > 0 then
			table.insert(list, playerGuid)
		end
	end
	
	return list
end

function GroupInfo:GetGroupPlayerList()
	local list = {}
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) > 0 then
			local playerInfo = app.objMgr:getObj(playerGuid)
			if playerInfo and playerInfo:isLogined() then
				table.insert(list, playerInfo)
			end
		end
	end
	
	return list
end


function GroupInfo:ClearMemberPreparingFlag()
	local intstart = GROUP_INT_FIELD_MEMBER_INFO_START
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT - 1 do
		self:SetUInt32(intstart + GROUP_MEMBER_INT_RESPONSE_STATE, GROUP_MEMBER_RESPONSE_STATE_NONE)
		intstart = intstart + MAX_GROUP_MEMBER_INFO_INT_COUNT
	end
end

function GroupInfo:GroupSetResponseState(memberIndex, state)
	local intstart = GROUP_INT_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_INT_COUNT
	self:SetUInt32(intstart + GROUP_MEMBER_INT_RESPONSE_STATE, state)
end

function GroupInfo:CheckResponsed(memberIndex)
	local intstart = GROUP_INT_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_INT_COUNT
	return self:GetUInt32(intstart + GROUP_MEMBER_INT_RESPONSE_STATE) ~= GROUP_MEMBER_RESPONSE_STATE_NONE
end


function GroupInfo:CheckResponseIsAccepted(memberIndex)
	local intstart = GROUP_INT_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_INT_COUNT
	return self:GetUInt32(intstart + GROUP_MEMBER_INT_RESPONSE_STATE) == GROUP_MEMBER_RESPONSE_STATE_ACCEPT
end

function GroupInfo:SetGroupType(type)
	self:SetUInt32(GROUP_INT_FIELD_TYPE, type)
end

function GroupInfo:GetGroupType()
	return self:GetUInt32(GROUP_INT_FIELD_TYPE)
end

function GroupInfo:SetCaptainGuid(playerGuid)
	self:SetStr(GROUP_STR_FIELD_CAPTAIN_GUID, playerGuid)
end

function GroupInfo:GetCaptainGuid()
	return self:GetStr(GROUP_STR_FIELD_CAPTAIN_GUID)
end

function GroupInfo:IsPlayerCaptain(playerGuid)
	return self:GetCaptainGuid() == playerGuid
end

function GroupInfo:GetUIntValue(memberIndex, dataIndex)
	local intstart = GROUP_INT_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_INT_COUNT + dataIndex
	return self:GetUInt32(intstart)
end

function GroupInfo:GetStrValue(memberIndex, dataIndex)
	local strstart = GROUP_STR_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_STR_COUNT + dataIndex
	return self:GetStr(strstart)
end

function GroupInfo:SetUIntValue(memberIndex, dataIndex, value)
	local intstart = GROUP_INT_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_INT_COUNT + dataIndex
	self:SetUInt32(intstart, value)
end

function GroupInfo:SetStrValue(memberIndex, dataIndex, value)
	local strstart = GROUP_STR_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_STR_COUNT + dataIndex
	self:SetStr(strstart, value)
end

function GroupInfo:findEmptySlotAndAddPlayerGuid(playerGuid)
	local memberIndex = self:GetMemberIndex('')
	if memberIndex == -1 then
		outFmtDebug(debug.traceback())
	end
	self:SetStrValue(memberIndex, GROUP_MEMBER_STR_GUID, playerGuid)
	return memberIndex
end

function GroupInfo:GetMemberIndex(playerGuid)
	local strstart = GROUP_STR_FIELD_MEMBER_INFO_START
	for i = 0, MAX_GROUP_MEMBER_COUNT - 1 do
		if self:GetStr(strstart + GROUP_MEMBER_STR_GUID) == playerGuid then
			return i
		end
		strstart = strstart + MAX_GROUP_MEMBER_INFO_STR_COUNT
	end

	return -1
end

function GroupInfo:addMember(playerInfo, isCaptain)
	isCaptain = isCaptain or false
	-- 设置信息
	local memberIndex = self:findEmptySlotAndAddPlayerGuid(playerInfo:GetGuid())
	outFmtDebug("addMember playerguid = %s, memberIndex = %d", playerInfo:GetGuid(), memberIndex)
	if isCaptain then
		self:SetCaptainGuid(playerInfo:GetGuid())
	else
		playerInfo:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_JOIN_SUCCESS,{})
	end

	playerInfo:SetGroupId(self:GetGuid())
	
	self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_ICON,playerInfo:GetGender())
	self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_LEVEL,playerInfo:GetLevel())
	self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_MAPID_LINENO,playerInfo:GetMapId()*65536+ playerInfo:GetUInt32(PLAYER_FIELD_LINE_NO))
	self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_STATE,GROUP_MEMBER_STATE_NONE)
	self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_RESPONSE_STATE,GROUP_AUTO_ACCEPT_STATE_OFF)
	
	self:SetStrValue(memberIndex,GROUP_MEMBER_STR_GUID,playerInfo:GetGuid())
	self:SetStrValue(memberIndex,GROUP_MEMBER_STR_NAME,playerInfo:GetName())
	
	

	
	--下发binlog给客户端
	app.objMgr:callAddWatch(playerInfo:GetSessionId(), self:GetGuid())
	
	outFmtDebug("player %s add group %s success", playerInfo:GetGuid(), self:GetGuid())
end

function GroupInfo:groupDissolution()
	app.objMgr:callRemoveObject(self:GetGuid())
	outFmtDebug("group %s is dissolution successful", self:GetGuid())
end


function GroupInfo:SetAutoAcceptFlag(value)
	self:SetUInt32(GROUP_INT_FIELD_AUTO_ACCEPT_FLAG,value)
end

function GroupInfo:GetAutoAcceptFlag()
	return self:GetUInt32(GROUP_INT_FIELD_AUTO_ACCEPT_FLAG)
end

function GroupInfo:UpdateMemberInfo(playerInfo)
	local memberIndex = self:GetMemberIndex(playerInfo:GetGuid())
	if memberIndex > -1 then
		--self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_ICON,playerInfo:GetGender())
		self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_LEVEL,playerInfo:GetLevel())
		--self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_MAPID_LINENO,playerInfo:GetMapId()*65536+ playerInfo:GetUInt32(PLAYER_FIELD_LINE_NO))
		--self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_STATE,GROUP_MEMBER_STATE_NONE)
		--self:SetUIntValue(memberIndex,GROUP_MEMBER_INT_RESPONSE_STATE,GROUP_AUTO_ACCEPT_STATE_OFF)
		
		--self:SetStrValue(memberIndex,GROUP_MEMBER_STR_GUID,playerInfo:GetGuid())
		self:SetStrValue(memberIndex,GROUP_MEMBER_STR_NAME,playerInfo:GetName())
	end
	
end

return GroupInfo