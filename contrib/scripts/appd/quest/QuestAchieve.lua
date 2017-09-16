local QuestAchieve = class("QuestAchieve", AbstractQuest)

IQuestAchieve = QuestAchieve:new{}

function QuestAchieve:ctor()
	
end

function QuestAchieve:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local achievePoint = playerInfo:GetAchieveAll()
	self:OnUpdate(playerInfo, start, offset, {achievePoint})
end

-- ���Ŀ��ֵ
function QuestAchieve:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestAchieve:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestAchieve