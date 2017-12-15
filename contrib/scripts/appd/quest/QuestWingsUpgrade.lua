local QuestWingsUpgrade = class("QuestWingsUpgrade", AbstractQuest)

IQuestWingsUpgrade = QuestWingsUpgrade:new{}

function QuestWingsUpgrade:ctor()
	
end

function QuestWingsUpgrade:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLv = tb_quest[questId].targets[offset+1][ 2 ]
	
	local level = playerInfo:getSpellMgr():GetWingsId()
	
	local process = 0
	if level >= targetLv then
		process = 1
	end
	-- ��ó�����
	self:OnUpdate(playerInfo, start, offset, {process})
end

-- ���Ŀ��ֵ
function QuestWingsUpgrade:GetTargetValue(targetInfo)
	return 1
end

-- ���½���, ���Ŀ����ɷ���true
function QuestWingsUpgrade:OnUpdate(playerInfo, start, offset, params)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLv = tb_quest[questId].targets[offset+1][ 2 ]
	
	local level = playerInfo:getSpellMgr():GetWingsId()
	
	local process = 0
	if level >= targetLv then
		process = 1
	end
	
	return self:OnUpdateModeValue(playerInfo, start, offset, {process})
end

return QuestWingsUpgrade