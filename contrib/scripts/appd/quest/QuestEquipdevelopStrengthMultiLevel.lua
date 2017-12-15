local QuestEquipdevelopStrengthMultiLevel = class("QuestEquipdevelopStrengthMultiLevel", AbstractQuest)

IQuestEquipdevelopStrengthMultiLevel = QuestEquipdevelopStrengthMultiLevel:new{}

function QuestEquipdevelopStrengthMultiLevel:ctor()
	
end

function QuestEquipdevelopStrengthMultiLevel:OnInit(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {})
end

-- 获得目标值
function QuestEquipdevelopStrengthMultiLevel:GetTargetValue(targetInfo)
	return targetInfo[2]
end

-- 更新进度, 如果目标完成返回true
function QuestEquipdevelopStrengthMultiLevel:OnUpdate(playerInfo, start, offset, params)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLv = tb_quest[questId].targets[offset+1][ 3 ]
	local process = 0
	
	for i = 0 , EQUIPMENT_COUNT - 1 do
		local level = playerInfo:getSpellMgr()():GetEquipDevelopStrengthLv(i)
		if level >= targetLv then
			process = process + 1
		end
	end
	
	
	
	
	
	return self:OnUpdateModeValue(playerInfo, start, offset, {process})
end

return QuestEquipdevelopStrengthMultiLevel