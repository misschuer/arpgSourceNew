local QuestWingsBlessTimes = class("QuestWingsBlessTimes", AbstractQuest)

IQuestWingsBlessTimes = QuestWingsBlessTimes:new{}

function QuestWingsBlessTimes:ctor()
	
end

function QuestWingsBlessTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestWingsBlessTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestWingsBlessTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestWingsBlessTimes