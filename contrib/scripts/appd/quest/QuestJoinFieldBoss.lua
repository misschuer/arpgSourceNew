local QuestJoinFieldBoss = class("QuestJoinFieldBoss", AbstractQuest)

IQuestJoinFieldBoss = QuestJoinFieldBoss:new{}

function QuestJoinFieldBoss:ctor()
	
end

function QuestJoinFieldBoss:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestJoinFieldBoss:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestJoinFieldBoss:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestJoinFieldBoss