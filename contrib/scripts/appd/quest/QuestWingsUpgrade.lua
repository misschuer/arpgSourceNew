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
	-- 获得翅膀阶数
	self:OnUpdate(playerInfo, start, offset, {process})
end

-- 获得目标值
function QuestWingsUpgrade:GetTargetValue(targetInfo)
	return 1
end

-- 更新进度, 如果目标完成返回true
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