local QuestTalismanLevel = class("QuestTalismanLevel", AbstractQuest)

IQuestTalismanLevel = QuestTalismanLevel:new{}

function QuestTalismanLevel:ctor()
	
end

function QuestTalismanLevel:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	
	local id = tb_quest[questId].targets[offset+1][ 2 ]
	local level = playerInfo:getTalismanLevelIfNotReturnMaxLevelOfAllTalisman(id)
	
	self:OnUpdate(playerInfo, start, offset, {id, level})
end

-- ���Ŀ��ֵ
function QuestTalismanLevel:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestTalismanLevel:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectValue(playerInfo, start, offset, params)
end

return QuestTalismanLevel