local QuestMoneytreeTimes = class("QuestMoneytreeTimes", AbstractQuest)

IQuestMoneytreeTimes = QuestMoneytreeTimes:new{}

function QuestMoneytreeTimes:ctor()
	
end

function QuestMoneytreeTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestMoneytreeTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestMoneytreeTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestMoneytreeTimes