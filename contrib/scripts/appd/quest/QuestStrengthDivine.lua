local QuestStrengthDivine = class("QuestStrengthDivine", AbstractQuest)

IQuestStrengthDivine = QuestStrengthDivine:new{}

function QuestStrengthDivine:ctor()
	
end

function QuestStrengthDivine:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestStrengthDivine:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestStrengthDivine:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestStrengthDivine