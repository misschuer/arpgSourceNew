local QuestWashSuit = class("QuestWashSuit", AbstractQuest)

IQuestWashSuit = QuestWashSuit:new{}

function QuestWashSuit:ctor()
	
end

function QuestWashSuit:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestWashSuit:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestWashSuit:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestWashSuit