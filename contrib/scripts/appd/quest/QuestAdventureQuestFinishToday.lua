local QuestAdventureQuestFinishToday = class("QuestAdventureQuestFinishToday", AbstractQuest)

IQuestAdventureQuestFinishToday = QuestAdventureQuestFinishToday:new{}

function QuestAdventureQuestFinishToday:ctor()
	
end

function QuestAdventureQuestFinishToday:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetsQuestId = tb_quest[questId].targets[offset+1][ 2 ]

	for start = QUEST_FIELD_QUEST_START, QUEST_FIELD_QUEST_END - 1, MAX_QUEST_INFO_COUNT do
		
		local questId = playerInfo:getQuestMgr():GetUInt16(start + QUEST_INFO_ID, 0)

		if questId > 0 and questId == targetsQuestId then
			if playerInfo:getQuestMgr():GetUInt16(start + QUEST_INFO_ID, 1) == QUEST_STATUS_END then
				self:OnUpdate(playerInfo, start, offset, {targetsQuestId})
				return
			end
			
		end
	end
	
end

-- 获得目标值
function QuestAdventureQuestFinishToday:GetTargetValue(targetInfo)
	return 1
end

-- 更新进度, 如果目标完成返回true
function QuestAdventureQuestFinishToday:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestAdventureQuestFinishToday