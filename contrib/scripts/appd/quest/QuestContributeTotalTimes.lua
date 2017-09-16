local QuestContributeTotalTimes = class("QuestContributeTotalTimes", AbstractQuest)

IQuestContributeTotalTimes = QuestContributeTotalTimes:new{}

function QuestContributeTotalTimes:ctor()
	
end

function QuestContributeTotalTimes:OnInit(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {playerInfo:GetFactionGiftSendCount()})
end

-- ���Ŀ��ֵ
function QuestContributeTotalTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestContributeTotalTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestContributeTotalTimes