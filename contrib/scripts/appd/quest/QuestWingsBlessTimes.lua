local QuestWingsBlessTimes = class("QuestWingsBlessTimes", AbstractQuest)

IQuestWingsBlessTimes = QuestWingsBlessTimes:new{}

function QuestWingsBlessTimes:ctor()
	
end

function QuestWingsBlessTimes:OnInit(playerInfo, start, offset)
	
end

-- 获得目标值
function QuestWingsBlessTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- 更新进度, 如果目标完成返回true
function QuestWingsBlessTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestWingsBlessTimes