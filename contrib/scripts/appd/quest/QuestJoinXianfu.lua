local QuestJoinXianfu = class("QuestJoinXianfu", AbstractQuest)

IQuestJoinXianfu = QuestJoinXianfu:new{}

function QuestJoinXianfu:ctor()
	
end

function QuestJoinXianfu:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestJoinXianfu:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestJoinXianfu:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestJoinXianfu