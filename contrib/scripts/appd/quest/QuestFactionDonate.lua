local QuestFactionDonate = class("QuestFactionDonate", AbstractQuest)

IQuestFactionDonate = QuestFactionDonate:new{}

function QuestFactionDonate:ctor()
	
end

function QuestFactionDonate:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestFactionDonate:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestFactionDonate:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestFactionDonate