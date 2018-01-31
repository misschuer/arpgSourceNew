local ScenedGroup = class('ScenedGroup', BinLogObject)

function ScenedGroup:ctor()

end

--[[
	GROUP_MEMBER_STR_GUID		= 0,	// Íæ¼Òguid
	MAX_GROUP_MEMBER_INFO_STR_COUNT,
	
	GROUP_STR_FIELD_MEMBER_INFO_START = 0,
	GROUP_STR_FIELD_MEMBER_INFO_END = GROUP_STR_FIELD_MEMBER_INFO_START + MAX_GROUP_MEMBER_COUNT * MAX_GROUP_MEMBER_INFO_STR_COUNT,
--]]
function ScenedGroup:GetGroupGuidList()
	local list = {}
	for memberIndex = 0, MAX_GROUP_MEMBER_COUNT-1 do
		local playerGuid = self:GetStrValue(memberIndex, GROUP_MEMBER_STR_GUID)
		if string.len(playerGuid) > 0 then
			table.insert(list, playerGuid)
		end
	end
	
	return list
end

function ScenedGroup:IsPlayerCaptain(playerGuid)
	return self:GetStr(GROUP_STR_FIELD_CAPTAIN_GUID) == playerGuid
end

function ScenedGroup:GetUIntValue(memberIndex, dataIndex)
	local intstart = GROUP_INT_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_INT_COUNT + dataIndex
	return self:GetUInt32(intstart)
end

function ScenedGroup:SetUIntValue(memberIndex, dataIndex, value)
	local intstart = GROUP_INT_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_INT_COUNT + dataIndex
	self:SetUInt32(intstart, value)
end

function ScenedGroup:GetStrValue(memberIndex, dataIndex)
	local strstart = GROUP_STR_FIELD_MEMBER_INFO_START + memberIndex * MAX_GROUP_MEMBER_INFO_STR_COUNT + dataIndex
	return self:GetStr(strstart)
end

function ScenedGroup:SetPlayerMapidAndLineNo(playerInfo, mapid, lineNo)
	local memberIndex = self:GetMemberIndex(playerInfo:GetPlayerGuid())
	if memberIndex > -1 then
		self:SetUIntValue(memberIndex, GROUP_MEMBER_INT_MAPID_LINENO, mapid * 65536 + lineNo)
	end
end

function ScenedGroup:GetMemberIndex(playerGuid)
	local strstart = GROUP_STR_FIELD_MEMBER_INFO_START
	for i = 0, MAX_GROUP_MEMBER_COUNT - 1 do
		if self:GetStr(strstart + GROUP_MEMBER_STR_GUID) == playerGuid then
			return i
		end
		strstart = strstart + MAX_GROUP_MEMBER_INFO_STR_COUNT
	end

	return -1
end

return ScenedGroup
