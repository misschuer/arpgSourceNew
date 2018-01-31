local QuestInstanceExpTimes = class("QuestInstanceExpTimes", AbstractQuest)

IQuestInstanceExpTimes = QuestInstanceExpTimes:new{}

function QuestInstanceExpTimes:ctor()
	
end

function QuestInstanceExpTimes:OnInit(playerInfo, start, offset)
	
end

-- 获得目标值
function QuestInstanceExpTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- 更新进度, 如果目标完成返回true
function QuestInstanceExpTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestInstanceExpTimes