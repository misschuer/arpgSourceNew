local QuestInstanceExpTimes = class("QuestInstanceExpTimes", AbstractQuest)

IQuestInstanceExpTimes = QuestInstanceExpTimes:new{}

function QuestInstanceExpTimes:ctor()
	
end

function QuestInstanceExpTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestInstanceExpTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestInstanceExpTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestInstanceExpTimes