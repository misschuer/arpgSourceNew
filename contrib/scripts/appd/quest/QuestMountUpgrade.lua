local QuestMountUpgrade = class("QuestMountUpgrade", AbstractQuest)

IQuestMountUpgrade = QuestMountUpgrade:new{}

function QuestMountUpgrade:ctor()
	
end

function QuestMountUpgrade:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLv = tb_quest[questId].targets[offset+1][ 2 ]

	local spellMgr = playerInfo:getSpellMgr()
	-- ����������
	local rank = spellMgr:getMountLevel()
	local star = spellMgr:getMountStar()
	
	local level = rank * 1000 + star
	
	local process = 0
	if level >= targetLv then
		process = 1
	end
	
	self:OnUpdateModeValue(playerInfo, start, offset, {process})
end

-- ���Ŀ��ֵ
function QuestMountUpgrade:GetTargetValue(targetInfo)
	return 1
end

-- ���½���, ���Ŀ����ɷ���true
function QuestMountUpgrade:OnUpdate(playerInfo, start, offset, params)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLv = tb_quest[questId].targets[offset+1][ 2 ]

	local spellMgr = playerInfo:getSpellMgr()
	-- ����������
	local rank = spellMgr:getMountLevel()
	local star = spellMgr:getMountStar()
	
	local level = rank * 1000 + star
	
	local process = 0
	if level >= targetLv then
		process = 1
	end
	
	return self:OnUpdateModeValue(playerInfo, start, offset, {process})
end

return QuestMountUpgrade