local QuestLootItem = class("QuestLootItem", AbstractQuest)

IQuestLootItem = QuestLootItem:new{}

function QuestLootItem:ctor()
	
end

function QuestLootItem:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestLootItem:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestLootItem:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestLootItem