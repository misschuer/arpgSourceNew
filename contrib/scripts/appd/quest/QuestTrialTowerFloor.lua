local QuestTrialTowerFloor = class("QuestTrialTowerFloor", AbstractQuest)

IQuestTrialTowerFloor = QuestTrialTowerFloor:new{}

function QuestTrialTowerFloor:ctor()
	
end

function QuestTrialTowerFloor:OnInit(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {})
end

-- 获得目标值
function QuestTrialTowerFloor:GetTargetValue(targetInfo)
	return 1
end

-- 更新进度, 如果目标完成返回true
function QuestTrialTowerFloor:OnUpdate(playerInfo, start, offset, params)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLv = tb_quest[questId].targets[offset+1][ 2 ]
	
	local level = playerInfo:GetUInt16(INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT, 1)
	
	local process = 0
	if level >= targetLv then
		process = 1
	end
	
	return self:OnUpdateModeValue(playerInfo, start, offset, {process})
end

return QuestTrialTowerFloor