local QuestJoinResourceInstance = class("QuestJoinResourceInstance", AbstractQuest)

IQuestJoinResourceInstance = QuestJoinResourceInstance:new{}

function QuestJoinResourceInstance:ctor()
	
end

function QuestJoinResourceInstance:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestJoinResourceInstance:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestJoinResourceInstance:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestJoinResourceInstance