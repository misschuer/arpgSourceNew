		
-- ��������
function PlayerInfo:createGroup()
	local new_guid = guidMgr:Make_New_Guid(guidMgr.ObjectTypeGroup, guidMgr:NewIndex(guidMgr.ObjectTypeGroup), self:GetGuid())
	-- Ӧ�÷�����
	local group = app.objMgr:newAndCallPut(new_guid, GROUP_BINLOG_OWNER_STRING)
	
	if(not group)then
		outFmtDebug("################################ 1")
		return
	end
	
	group:addMember(self)

	-- ֪ͨ����������
	serverConnList:forEachScenedFD(function (fd)
		app.objMgr:callAddWatch(fd, new_guid)
	end)
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


--�������

--�������

--ͬ�����

--�˳����

--����

--�ƽ��ӳ�


