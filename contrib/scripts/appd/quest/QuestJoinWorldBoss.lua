local QuestJoinWorldBoss = class("QuestJoinWorldBoss", AbstractQuest)

IQuestJoinWorldBoss = QuestJoinWorldBoss:new{}

function QuestJoinWorldBoss:ctor()
	
end

function QuestJoinWorldBoss:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestJoinWorldBoss:GetTargetValue(targetInfo)
	return 1
end

-- ���½���, ���Ŀ����ɷ���true
function QuestJoinWorldBoss:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestJoinWorldBoss