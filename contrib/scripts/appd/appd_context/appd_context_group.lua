		
-- 创建队伍
function PlayerInfo:createGroup(type,min_lev,max_lev,auto_flag)
	local min_lev = min_lev or 1
	local max_lev = max_lev or 200
	local auto_flag = auto_flag or GROUP_AUTO_ACCEPT_STATE_ON
	
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	-- 已经有队伍了
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) > 0 then
		outFmtDebug("player %s is already in group %s", self:GetGuid(), prevGroupGuid)
		return
	end
	
	local new_guid = guidMgr:Make_New_Guid(guidMgr.ObjectTypeGroup, guidMgr:NewIndex(guidMgr.ObjectTypeGroup), self:GetGuid())
	-- 应用服监听
	local group = app.objMgr:newAndCallPut(new_guid, GROUP_BINLOG_OWNER_STRING)
	
	if(not group)then
		outFmtDebug("################################ 1")
		return
	end
	
	-- 增加队伍信息
	group:SetGroupType(type)
	
	--等级选项
	group:SetLevelRange(min_lev,max_lev)
	group:SetAutoAcceptFlag(auto_flag)
	
	
	-- 通知场景服监听
	serverConnList:forEachScenedFD(function (fd)
		app.objMgr:callAddWatch(fd, new_guid)
	end)
	
	outFmtDebug("player %s create group %s success", self:GetGuid(), new_guid)
	-- 加入队伍
	group:addMember(self, true)
end

--申请组队
function PlayerInfo:registerGroup(groupGuid)
	
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	
	-- 已经有队伍了
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) > 0 then
		outFmtDebug("player %s is already in group %s", self:GetGuid(), prevGroupGuid)
		return
	end
	
	-- 不是组队的guid
	if not app.objMgr:IsGroupGuid(groupGuid) then
		return
	end
	
	local group = app.objMgr:getObj(groupGuid)
	if not group then
		self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_GROUP_NOT_EXIST,{})
		return
	end
	
	if group:GetMemeberCount() >= MAX_GROUP_MEMBER_COUNT then
		--队伍已满
		self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_MEMBER_FULL,{})
		return
	end
	
	if not group:IsInLevelRange(self:GetLevel()) then
		--
		return
	end
	if group:GetAutoAcceptFlag() > 0 then
		group:addMember(self)
		return
	end
	
	
	--发送前端申请信息
	local guid = group:GetCaptainGuid()
	
	if guid ~= '' then
		local player = app.objMgr:getObj(guid)
		if player and player:isLogined() then
			player:call_show_group_join_request(self:GetGuid(),self:GetName(),self:GetGender(),self:GetLevel(),self:GetVIP(),self:GetForce())
		end
	end
	
	self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_JOIN_REQUEST,{})
	
	--[[
	-- 暂时申请就加入
	-- 加入队伍
	if group then
		group:addMember(self)
	else
		outFmtDebug("groupGuid = %s is not exist", groupGuid)
	end
	
	--]]
end

-- 退出组队
function PlayerInfo:quitGroup()
	-- 还没有有队伍
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		outFmtDebug("player %s has no group %s", self:GetGuid())
		return
	end
	
	local group = app.objMgr:getObj(prevGroupGuid)
	if group then
		group:groupQuit(self)
	end
end


-- 测试用的 解散组队
function PlayerInfo:testDissolutionGroup()
	local new_guid = self:GetGroupId()
	if string.len(new_guid) == 0 or not app.objMgr:IsGroupGuid(new_guid) then
		return
	end
	
	local group = app.objMgr:getObj(new_guid)
	if group then
		group:groupQuit(self)
		group:groupDissolution()
	end
end


--发送邀请加入 (guid)
function PlayerInfo:sendInviteJoinGroup(guid)
	
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		outFmtDebug("sendInviteJoinGroup fail  auto matching")
		return
	end
	
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		outFmtDebug("player %s has no group %s", self:GetGuid())
		return
	end
	
	local group = app.objMgr:getObj(prevGroupGuid)
	if not group then
		outFmtDebug("sendInviteJoinGroup fail no group")
		return
	end
	
	--if not group:IsPlayerCaptain(self:GetGuid()) or group:IsFullMember() then
	--	return
	--end
	
	if guid ~= '' then
		local player = app.objMgr:getObj(guid)
		if player and player:isLogined() then
			if string.len(player:GetGroupId()) ~= 0 then
				--对方已有队伍
				outFmtDebug("sendInviteJoinGroup had group")
				self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_ALREADY_HAVE_GROUP,{})
				return
			end
			outFmtDebug("sendInviteJoinGroup send success")
			player:call_show_group_invite(prevGroupGuid,self:GetName(),group:GetGroupType(),self:GetLevel(),self:GetForce(),self:GetGuid())
		else
			outFmtDebug("sendInviteJoinGroup player not find")
		end
		
	end
	
	outFmtDebug("sendInviteJoinGroup guid %s",guid)
end



--同意邀请 (groupId)
function PlayerInfo:agreeInviteJoinGroup(groupGuid,senderGuid)
	
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	
	-- 已经有队伍了
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) > 0 then
		outFmtDebug("player %s is already in group %s", self:GetGuid(), prevGroupGuid)
		return
	end
	
	local group = app.objMgr:getObj(groupGuid)
	if not group then
		self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_GROUP_NOT_EXIST,{})
		return
	end
	
	if group:IsFullMember() then
		self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_MEMBER_FULL,{})
		return
	end
	if not group:IsPlayerCaptain(senderGuid) then
		self:registerGroup(groupGuid)
	else
		group:addMember(self)
	end
	
end

--便捷组队队伍 (目标)
function PlayerInfo:searchGroupList(group_type)
	local list = {}
	--outFmtDebug("!!!!!!!!!!!!!!!!!!!!!!!!searchGroupList start ")
	app.objMgr:foreachAllGroup(function(groupInfo)
		if #list >= 20 then
			return
		end
		if groupInfo:GetGroupType() == group_type then
			if groupInfo:IsInLevelRange(self:GetLevel()) then
				local group_guid = groupInfo:GetGuid()
				local captain_guid = groupInfo:GetCaptainGuid()
				local captain_index = groupInfo:GetMemberIndex(captain_guid)
				local captain_name = groupInfo:GetStrValue(captain_index,GROUP_MEMBER_STR_NAME)
				local member_count = groupInfo:GetMemeberCount()
				
				if member_count ~= MAX_GROUP_MEMBER_COUNT then
					
					--todo msg 协议
					local stru = group_search_info_t .new()
					stru.guid		= group_guid
					stru.cap_guid 	= captain_guid
					stru.cap_name	= captain_name
					stru.members	= member_count
					table.insert(list, stru)
					
					--outFmtDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!searchGroupList %s ",group_guid)
				end
				
				
			end
		end
	end)
	--outFmtDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!searchGroupList end ")
	self:call_show_group_search_info_list(list)
end

--修改队伍选项 (目标参数 )
function PlayerInfo:changeGroupConfig(type,min_lev,max_lev,auto_flag)
	
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		outFmtDebug("player %s has no group", self:GetGuid())
		return
	end
	
	local group = app.objMgr:getObj(prevGroupGuid)
	if not group then
		return
	end
	
	if not group:IsPlayerCaptain(self:GetGuid()) then
		return
	end
	if type ~= 0 then
		group:SetGroupType(type)
	end
	if min_lev ~= 0 and min_lev ~= 0 then
		group:SetLevelRange(min_lev,max_lev)
	end
	group:SetAutoAcceptFlag(auto_flag)
	
end



--同意队伍加入申请 (guid)
function PlayerInfo:agreeRegisterJoinGroup(guid)
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		outFmtDebug("player %s has no group %s", self:GetGuid())
		return
	end
	
	local group = app.objMgr:getObj(prevGroupGuid)
	if not group then
		return
	end
	
	if not group:IsPlayerCaptain(self:GetGuid()) then
		return
	end
	
	if group:IsFullMember() then
		return
	end
	
	if guid ~= '' then
		local player = app.objMgr:getObj(guid)
		if player and player:isLogined() then
			
			-- 已经有队伍了
			local playerGroupGuid = player:GetGroupId()
			if string.len(playerGroupGuid) > 0 then
				outFmtDebug("player %s is already in group %s", player:GetGuid(), playerGroupGuid)
				player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_ALREADY_HAVE_GROUP,{})
				return
			end
			group:addMember(player)
			if group:IsFullMember() then
				OnGroupMatchRemove(group:GetGuid())
				group:SetUInt32(GROUP_INT_FIELD_STATE, 0)
			end
			player:SetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH,0)
			OnGroupMatchRemove(player:GetGuid())
		else
			--下线状态 不加 
			--提示离线
			self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_PLAYER_IS_OFFLINE,{})
		end
	end
	
	
end


--拒绝队伍加入申请 (guid)
function PlayerInfo:deniedRegisterJoinGroup(guids)
	
	
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		outFmtDebug("player %s has no group %s", self:GetGuid())
		return
	end
	
	local group = app.objMgr:getObj(prevGroupGuid)
	if not group then
		return
	end
	
	if not group:IsPlayerCaptain(self:GetGuid()) then
		return
	end
	
	local tokens = string.split(guids,'|')
	for _,guid in ipairs(tokens) do
		if guid ~= '' then
			local player = app.objMgr:getObj(guid)
			if player and player:isLogined() then
				
				player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_DENIED_JOIN_REQUEST,{getShowName(self:GetName())}) -- 对方拒绝申请消息
			end
		end
		outFmtDebug("deniedRegisterJoinGroup guid %s ",guid)
	end
end

--踢人 (guid)
function PlayerInfo:kickGroupMember(memberIndex)
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		outFmtDebug("player %s has no group %s", self:GetGuid())
		return
	end
	
	local group = app.objMgr:getObj(prevGroupGuid)
	if not group then
		return
	end
	
	if not group:IsPlayerCaptain(self:GetGuid()) then
		return
	end
	
	if memberIndex >= MAX_GROUP_MEMBER_COUNT then
		return
	end
	
	local guid = group:GetStrValue(memberIndex,GROUP_MEMBER_STR_GUID)
	
	if group:IsPlayerCaptain(guid) then
		return
	end
	
	group:ClearMember(memberIndex)
	
	
	if guid ~= '' then
		local player = app.objMgr:getObj(guid)
		if player and player:isLogined() then
			-- IMPORTANT 移除监听
			app.objMgr:callDelWatch(player:GetSessionId(),prevGroupGuid)
			player:SetGroupId('')
			player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_KICKED,{getShowName(self:GetName())}) -- 被踢消息
		end
	end
end


 
--移交队长 (guid)
function PlayerInfo:changeGroupChaption(memberIndex)
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		outFmtDebug("player %s has no group %s", self:GetGuid())
		return
	end
	
	local group = app.objMgr:getObj(prevGroupGuid)
	if not group then
		return
	end
	
	if not group:IsPlayerCaptain(self:GetGuid()) then
		return
	end
	
	if memberIndex >= MAX_GROUP_MEMBER_COUNT then
		return
	end
	
	local guid = group:GetStrValue(memberIndex,GROUP_MEMBER_STR_GUID)
	
	if group:IsPlayerCaptain(guid) then
		return
	end
	
	if guid ~= '' then
		local player = app.objMgr:getObj(guid)
		if player and player:isLogined() then
			
			group:onGroupChangeCaptain(memberIndex)
			player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_BECOME_CAPTAIN,{}) -- 转交为队长消息
		end
	end
end

--拒绝队伍邀请 (groupGuid)
function PlayerInfo:deniedInviteGroup(groupGuid)
	local group = app.objMgr:getObj(groupGuid)
	if not group then
		return
	end
	
	local guid = group:GetCaptainGuid()
	
	if guid ~= '' then
		local player = app.objMgr:getObj(guid)
		if player and player:isLogined() then
			
			player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_DENIED_INVITE,{getShowName(self:GetName())}) -- 对方拒绝邀请消息
		end
	end
end

function PlayerInfo:UpdateGroupInfo()
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		--outFmtDebug("player %s has no group %s", self:GetGuid())
		return
	end
	local group = app.objMgr:getObj(prevGroupGuid)
	if not group then
		return
	end
	
	group:UpdateMemberInfo(self)
end