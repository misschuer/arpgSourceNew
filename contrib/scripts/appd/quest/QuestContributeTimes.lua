local QuestContributeTimes = class("QuestContributeTimes", AbstractQuest)

IQuestContributeTimes = QuestContributeTimes:new{}

function QuestContributeTimes:ctor()
	
end

function QuestContributeTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestContributeTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestContributeTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestContributeTimes