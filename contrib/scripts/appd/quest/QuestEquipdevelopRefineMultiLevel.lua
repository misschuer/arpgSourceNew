local QuestEquipdevelopRefineMultiLevel = class("QuestEquipdevelopRefineMultiLevel", AbstractQuest)

IQuestEquipdevelopRefineMultiLevel = QuestEquipdevelopRefineMultiLevel:new{}

function QuestEquipdevelopRefineMultiLevel:ctor()
	
end

function QuestEquipdevelopRefineMultiLevel:OnInit(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {})
end

-- ���Ŀ��ֵ
function QuestEquipdevelopRefineMultiLevel:GetTargetValue(targetInfo)
	return targetInfo[2]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestEquipdevelopRefineMultiLevel:OnUpdate(playerInfo, start, offset, params)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLv = tb_quest[questId].targets[offset+1][ 3 ]
	local process = 0
	
	for i = 0 , EQUIPMENT_COUNT - 1 do
		local level = playerInfo:getSpellMgr():GetEquipDevelopRefineStar(i)
		if level >= targetLv then
			process = process + 1
		end
	end
	
	
	
	
	
	return self:OnUpdateModeValue(playerInfo, start, offset, {process})
end

return QuestEquipdevelopRefineMultiLevel