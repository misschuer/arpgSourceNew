local QuestDailyTask = class("QuestDailyTask", AbstractQuest)

IQuestDailyTask = QuestDailyTask:new{}

function QuestDailyTask:ctor()
	
end

function QuestDailyTask:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestDailyTask:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestDailyTask:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestDailyTask