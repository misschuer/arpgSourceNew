local QuestSingleThxTimes = class("QuestSingleThxTimes", AbstractQuest)

IQuestSingleThxTimes = QuestSingleThxTimes:new{}

function QuestSingleThxTimes:ctor()
	
end

function QuestSingleThxTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestSingleThxTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestSingleThxTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestSingleThxTimes