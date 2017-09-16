local QuestPlayerForce = class("QuestPlayerForce", AbstractQuest)

IQuestPlayerForce = QuestPlayerForce:new{}

function QuestPlayerForce:ctor()
	
end

function QuestPlayerForce:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local force = playerInfo:GetForce()
	self:OnUpdate(playerInfo, start, offset, {force})
end

-- ���Ŀ��ֵ
function QuestPlayerForce:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestPlayerForce:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestPlayerForce