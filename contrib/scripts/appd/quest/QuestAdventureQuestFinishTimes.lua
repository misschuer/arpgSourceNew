local QuestAdventureQuestFinishTimes = class("QuestAdventureQuestFinishTimes", AbstractQuest)

IQuestAdventureQuestFinishTimes = QuestAdventureQuestFinishTimes:new{}

function QuestAdventureQuestFinishTimes:ctor()
	
end

function QuestAdventureQuestFinishTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestAdventureQuestFinishTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestAdventureQuestFinishTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestAdventureQuestFinishTimes