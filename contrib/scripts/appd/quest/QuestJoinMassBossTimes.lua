local QuestJoinMassBossTimes = class("QuestJoinMassBossTimes", AbstractQuest)

IQuestJoinMassBossTimes = QuestJoinMassBossTimes:new{}

function QuestJoinMassBossTimes:ctor()
	
end

function QuestJoinMassBossTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestJoinMassBossTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestJoinMassBossTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestJoinMassBossTimes