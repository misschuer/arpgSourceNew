local QuestRefineSuit = class("QuestRefineSuit", AbstractQuest)

IQuestRefineSuit = QuestRefineSuit:new{}

function QuestRefineSuit:ctor()
	
end

function QuestRefineSuit:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestRefineSuit:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestRefineSuit:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestRefineSuit