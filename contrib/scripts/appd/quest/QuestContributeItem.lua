local QuestContributeItem = class("QuestContributeItem", AbstractQuest)

IQuestContributeItem = QuestContributeItem:new{}

function QuestContributeItem:ctor()
	
end

function QuestContributeItem:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestContributeItem:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestContributeItem:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestContributeItem