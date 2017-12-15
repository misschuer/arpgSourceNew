		
-- 创建队伍
function PlayerInfo:createGroup()
	local new_guid = guidMgr:Make_New_Guid(guidMgr.ObjectTypeGroup, guidMgr:NewIndex(guidMgr.ObjectTypeGroup), self:GetGuid())
	-- 应用服监听
	local group = app.objMgr:newAndCallPut(new_guid, GROUP_BINLOG_OWNER_STRING)
	
	if(not group)then
		outFmtDebug("################################ 1")
		return
	end
	
	group:addMember(self)

	-- 通知场景服监听
	serverConnList:forEachScenedFD(function (fd)
		app.objMgr:callAddWatch(fd, new_guid)
	end)
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


--创建组队

--申请组队

--同意组队

--退出组队

--踢人

--移交队长


