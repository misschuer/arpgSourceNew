local QuestWingsStrengthTimes = class("QuestWingsStrengthTimes", AbstractQuest)

IQuestWingsStrengthTimes = QuestWingsStrengthTimes:new{}

function QuestWingsStrengthTimes:ctor()
	
end

function QuestWingsStrengthTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestWingsStrengthTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestWingsStrengthTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestWingsStrengthTimes