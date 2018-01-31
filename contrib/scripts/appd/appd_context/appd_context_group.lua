		
-- ��������
function PlayerInfo:createGroup(type,min_lev,max_lev,auto_flag)
	local min_lev = min_lev or 1
	local max_lev = max_lev or 200
	local auto_flag = auto_flag or GROUP_AUTO_ACCEPT_STATE_ON
	
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	-- �Ѿ��ж�����
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) > 0 then
		outFmtDebug("player %s is already in group %s", self:GetGuid(), prevGroupGuid)
		return
	end
	
	local new_guid = guidMgr:Make_New_Guid(guidMgr.ObjectTypeGroup, guidMgr:NewIndex(guidMgr.ObjectTypeGroup), self:GetGuid())
	-- Ӧ�÷�����
	local group = app.objMgr:newAndCallPut(new_guid, GROUP_BINLOG_OWNER_STRING)
	
	if(not group)then
		outFmtDebug("################################ 1")
		return
	end
	
	-- ���Ӷ�����Ϣ
	group:SetGroupType(type)
	
	--�ȼ�ѡ��
	group:SetLevelRange(min_lev,max_lev)
	group:SetAutoAcceptFlag(auto_flag)
	
	
	-- ֪ͨ����������
	serverConnList:forEachScenedFD(function (fd)
		app.objMgr:callAddWatch(fd, new_guid)
	end)
	
	outFmtDebug("player %s create group %s success", self:GetGuid(), new_guid)
	-- �������
	group:addMember(self, true)
end

--�������
function PlayerInfo:registerGroup(groupGuid)
	
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	
	-- �Ѿ��ж�����
	local prevGroupGuid = self:GetGroupId()
	if string.len(prevGroupGuid) > 0 then
		outFmtDebug("player %s is already in group %s", self:GetGuid(), prevGroupGuid)
		return
	end
	
	-- ������ӵ�guid
	if not app.objMgr:IsGroupGuid(groupGuid) then
		return
	end
	
	local group = app.objMgr:getObj(groupGuid)
	if not group then
		self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_GROUP_NOT_EXIST,{})
		return
	end
	
	if group:GetMemeberCount() >= MAX_GROUP_MEMBER_COUNT then
		--��������
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
	
	
	--����ǰ��������Ϣ
	local guid = group:GetCaptainGuid()
	
	if guid ~= '' then
		local player = app.objMgr:getObj(guid)
		if player and player:isLogined() then
			player:call_show_group_join_request(self:GetGuid(),self:GetName(),self:GetGender(),self:GetLevel(),self:GetVIP(),self:GetForce())
		end
	end
	
	self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_JOIN_REQUEST,{})
	
	--[[
	-- ��ʱ����ͼ���
	-- �������
	if group then
		group:addMember(self)
	else
		outFmtDebug("groupGuid = %s is not exist", groupGuid)
	end
	
	--]]
end

-- �˳����
function PlayerInfo:quitGroup()
	-- ��û���ж���
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


-- �����õ� ��ɢ���
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


--����������� (guid)
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
				--�Է����ж���
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



--ͬ������ (groupId)
function PlayerInfo:agreeInviteJoinGroup(groupGuid,senderGuid)
	
	if self:GetUInt32(PLAYER_INT_FIELD_AUTO_GROUP_MATCH) > 0 then
		return
	end
	
	-- �Ѿ��ж�����
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

--�����Ӷ��� (Ŀ��)
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
					
					--todo msg Э��
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

--�޸Ķ���ѡ�� (Ŀ����� )
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



--ͬ������������ (guid)
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
			
			-- �Ѿ��ж�����
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
			--����״̬ ���� 
			--��ʾ����
			self:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_PLAYER_IS_OFFLINE,{})
		end
	end
	
	
end


--�ܾ������������ (guid)
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
				
				player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_DENIED_JOIN_REQUEST,{getShowName(self:GetName())}) -- �Է��ܾ�������Ϣ
			end
		end
		outFmtDebug("deniedRegisterJoinGroup guid %s ",guid)
	end
end

--���� (guid)
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
			-- IMPORTANT �Ƴ�����
			app.objMgr:callDelWatch(player:GetSessionId(),prevGroupGuid)
			player:SetGroupId('')
			player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_KICKED,{getShowName(self:GetName())}) -- ������Ϣ
		end
	end
end


 
--�ƽ��ӳ� (guid)
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
			player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_BECOME_CAPTAIN,{}) -- ת��Ϊ�ӳ���Ϣ
		end
	end
end

--�ܾ��������� (groupGuid)
function PlayerInfo:deniedInviteGroup(groupGuid)
	local group = app.objMgr:getObj(groupGuid)
	if not group then
		return
	end
	
	local guid = group:GetCaptainGuid()
	
	if guid ~= '' then
		local player = app.objMgr:getObj(guid)
		if player and player:isLogined() then
			
			player:CallOptResult(OPRATE_TYPE_GROUP,GROUP_NOTICE_TYPE_DENIED_INVITE,{getShowName(self:GetName())}) -- �Է��ܾ�������Ϣ
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