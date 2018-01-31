local QuestVIPLevel = class("QuestVIPLevel", AbstractQuest)

IQuestVIPLevel = QuestVIPLevel:new{}

function QuestVIPLevel:ctor()
	
end

function QuestVIPLevel:OnInit(playerInfo, start, offset)
	local level = playerInfo:GetVIP()
	self:OnUpdate(playerInfo, start, offset, {level})
end

-- ���Ŀ��ֵ
function QuestVIPLevel:GetTargetValue(targetInfo)
	return targetInfo[2]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestVIPLevel:OnUpdate(playerInfo, start, offset, params)
	
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestVIPLevel