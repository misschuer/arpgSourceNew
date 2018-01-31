local QuestVIPLevel = class("QuestVIPLevel", AbstractQuest)

IQuestVIPLevel = QuestVIPLevel:new{}

function QuestVIPLevel:ctor()
	
end

function QuestVIPLevel:OnInit(playerInfo, start, offset)
	local level = playerInfo:GetVIP()
	self:OnUpdate(playerInfo, start, offset, {level})
end

-- 获得目标值
function QuestVIPLevel:GetTargetValue(targetInfo)
	return targetInfo[2]
end

-- 更新进度, 如果目标完成返回true
function QuestVIPLevel:OnUpdate(playerInfo, start, offset, params)
	
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestVIPLevel