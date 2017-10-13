local QuestMoneytreeTimes = class("QuestMoneytreeTimes", AbstractQuest)

IQuestMoneytreeTimes = QuestMoneytreeTimes:new{}

function QuestMoneytreeTimes:ctor()
	
end

function QuestMoneytreeTimes:OnInit(playerInfo, start, offset)
	
end

-- 获得目标值
function QuestMoneytreeTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- 更新进度, 如果目标完成返回true
function QuestMoneytreeTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestMoneytreeTimes