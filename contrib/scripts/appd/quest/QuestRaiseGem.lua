local QuestRaiseGem = class("QuestRaiseGem", AbstractQuest)

IQuestRaiseGem = QuestRaiseGem:new{}

function QuestRaiseGem:ctor()
	
end

function QuestRaiseGem:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestRaiseGem:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestRaiseGem:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestRaiseGem