local QuestJoinMassBossTimes = class("QuestJoinMassBossTimes", AbstractQuest)

IQuestJoinMassBossTimes = QuestJoinMassBossTimes:new{}

function QuestJoinMassBossTimes:ctor()
	
end

function QuestJoinMassBossTimes:OnInit(playerInfo, start, offset)
	
end

-- 获得目标值
function QuestJoinMassBossTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- 更新进度, 如果目标完成返回true
function QuestJoinMassBossTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestJoinMassBossTimes