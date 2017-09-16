local QuestEquipDivine = class("QuestEquipDivine", AbstractQuest)

IQuestEquipDivine = QuestEquipDivine:new{}

function QuestEquipDivine:ctor()
	
end

function QuestEquipDivine:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local divineId = tb_quest[questId].targets[offset+1][ 2 ]
	
	if playerInfo:hasEquDivine(divineId) then
		self:OnUpdate(playerInfo, start, offset, {divineId})
	end
end

-- ���Ŀ��ֵ
function QuestEquipDivine:GetTargetValue(targetInfo)
	return 1
end

-- ���½���, ���Ŀ����ɷ���true
function QuestEquipDivine:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestEquipDivine