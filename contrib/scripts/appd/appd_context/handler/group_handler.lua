
--创建组队
function PlayerInfo:Handle_Group_Create(pkt)
	local type = pkt.type
	local min_lev = pkt.min_lev
	local max_lev = pkt.max_lev
	local auto_flag = pkt.auto_flag
	
	self:createGroup(type,min_lev,max_lev,auto_flag)
end

--申请组队
function PlayerInfo:Handle_Group_Join_Request(pkt)
	local groupGuid = pkt.guid
	self:registerGroup(groupGuid)
end

--同意组队
function PlayerInfo:Handle_Group_Join_Accept(pkt)
	local guid = pkt.guid
	self:agreeRegisterJoinGroup(guid)
end

--退出组队
function PlayerInfo:Handle_Group_Quit(pkt)
	self:quitGroup()
end

--踢人 
function PlayerInfo:Handle_Group_Kick(pkt)
	local index = pkt.index
	self:kickGroupMember(index)
end

--移交队长 
function PlayerInfo:Handle_Group_Give_Captain(pkt)
	local index = pkt.index
	self:changeGroupChaption(index)
end

--发送组队邀请 
function PlayerInfo:Handle_Group_Send_Invite(pkt)
	local guid = pkt.guid
	self:sendInviteJoinGroup(guid)
end

--同意组队邀请 
function PlayerInfo:Handle_Group_Agree_Invite(pkt)
	local groupGuid = pkt.guid
	local senderGuid = pkt.senderGuid
	
	self:agreeInviteJoinGroup(groupGuid,senderGuid)
end

--便捷组队队伍列表 
function PlayerInfo:Handle_Get_Group_Search_Info_List(pkt)
	local type = pkt.type
	
	self:searchGroupList(type)
end

--修改组队设置 
function PlayerInfo:Handle_Group_Change_Config(pkt)
	local type = pkt.type
	local min_lev = pkt.min_lev
	local max_lev = pkt.max_lev
	local auto_flag = pkt.auto_flag
	
	self:changeGroupConfig(type,min_lev,max_lev,auto_flag)
end

--拒绝加入队伍 
function PlayerInfo:Handle_Group_Join_Denied(pkt)
	local guid = pkt.guid
	self:deniedRegisterJoinGroup(guid)
end

--拒绝组队邀请 
function PlayerInfo:Handle_Group_Invite_Denied(pkt)
	local groupGuid = pkt.guid
	self:deniedInviteGroup(groupGuid)
end

-- 队伍决定
function PlayerInfo:msgGroupSelect(pkt)
	local choise	  = pkt.choise
	
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) == 0 then
		outFmtDebug("player %s has no group %s", self:GetGuid())
		return
	end
	
	local group = app.objMgr:getObj(prevGroupGuid)
	if group then
		group:playerChoise(self, choise)
	end
end


function PlayerInfo:Handle_Auto_Group_Match(pkt)
	local targetType = pkt.targetType
	local guid = self:GetGuid()
	local groupId = self:GetGroupId()
	
	local isGroup = false
	if string.len(groupId) > 0 then
		local groupObj = app.objMgr:getObj(groupId)
		if groupObj then
			-- 有队伍 看看是不是队长
			if not groupObj:IsPlayerCaptain(guid) then
				return
			end
			if groupObj:IsFullMember() then
				return
			end
			guid = groupId
			targetType = groupObj:GetGroupType()
			isGroup = true
			groupObj:SetUInt32(GROUP_INT_FIELD_STATE, 1)
		end
	end
	
	if not isGroup then
		self:SetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH, targetType)
	end
	
	OnGroupMatchPush(targetType, guid)
end

function PlayerInfo:Handle_Cancel_Auto_Group_Match(pkt)
	local guid = self:GetGuid()
	local groupId = self:GetGroupId()
	
	local isGroup = false
	if string.len(groupId) > 0 then
		local groupObj = app.objMgr:getObj(groupId)
		if groupObj then
			-- 有队伍 看看是不是队长
			if not groupObj:IsPlayerCaptain(guid) then
				return
			end
			guid = groupId
			isGroup = true
			groupObj:SetUInt32(GROUP_INT_FIELD_STATE, 0)
		end
	end
	
	if not isGroup then
		self:SetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH, 0)
	end
	
	OnGroupMatchRemove(guid)
end