local QuestJoinQualify = class("QuestJoinQualify", AbstractQuest)

IQuestJoinQualify = QuestJoinQualify:new{}

function QuestJoinQualify:ctor()
	
end

function QuestJoinQualify:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestJoinQualify:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestJoinQualify:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestJoinQualify