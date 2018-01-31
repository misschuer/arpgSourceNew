local QuestInstanceGroupTimes = class("QuestInstanceGroupTimes", AbstractQuest)

IQuestInstanceGroupTimes = QuestInstanceGroupTimes:new{}

function QuestInstanceGroupTimes:ctor()
	
end

function QuestInstanceGroupTimes:OnInit(playerInfo, start, offset)
	
end

-- 获得目标值
function QuestInstanceGroupTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- 更新进度, 如果目标完成返回true
function QuestInstanceGroupTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestInstanceGroupTimes