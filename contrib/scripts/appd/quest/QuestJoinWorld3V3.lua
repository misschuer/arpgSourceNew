local QuestJoinWorld3V3 = class("QuestJoinWorld3V3", AbstractQuest)

IQuestJoinWorld3V3 = QuestJoinWorld3V3:new{}

function QuestJoinWorld3V3:ctor()
	
end

function QuestJoinWorld3V3:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestJoinWorld3V3:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestJoinWorld3V3:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestJoinWorld3V3