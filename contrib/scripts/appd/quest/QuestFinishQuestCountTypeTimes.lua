local QuestFinishQuestCountTypeTimes = class("QuestFinishQuestCountTypeTimes", AbstractQuest)

IQuestFinishQuestCountTypeTimes = QuestFinishQuestCountTypeTimes:new{}

function QuestFinishQuestCountTypeTimes:ctor()
	
end

function QuestFinishQuestCountTypeTimes:OnInit(playerInfo, start, offset)
	
	local info = self:GetCountTypeInfo(playerInfo, start, offset)
	if not info then
		return false
	end
	self:OnUpdate(playerInfo, start, offset, info)
end

function QuestFinishQuestCountTypeTimes:GetCountTypeInfo(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local quest_count_type = tb_quest[questId].targets[offset+1][ 2 ]
	if quest_count_type < 1 or quest_count_type > 5 then 
		return
	end
	local count = playerInfo:getQuestMgr():GetQuestCountType(quest_count_type - 1)
	return {quest_count_type,count}
end

-- 获得目标值
function QuestFinishQuestCountTypeTimes:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- 更新进度, 如果目标完成返回true
function QuestFinishQuestCountTypeTimes:OnUpdate(playerInfo, start, offset, params)
	local info = self:GetCountTypeInfo(playerInfo, start, offset)
	if not info then
		return false
	end
	return self:OnUpdateModeObjectValue(playerInfo, start, offset, info)
end

return QuestFinishQuestCountTypeTimes