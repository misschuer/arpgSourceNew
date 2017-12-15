local QuestAdventureQuestFinishTimes = class("QuestAdventureQuestFinishTimes", AbstractQuest)

IQuestAdventureQuestFinishTimes = QuestAdventureQuestFinishTimes:new{}

function QuestAdventureQuestFinishTimes:ctor()
	
end

function QuestAdventureQuestFinishTimes:OnInit(playerInfo, start, offset)
	
end

-- 获得目标值
function QuestAdventureQuestFinishTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- 更新进度, 如果目标完成返回true
function QuestAdventureQuestFinishTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestAdventureQuestFinishTimes