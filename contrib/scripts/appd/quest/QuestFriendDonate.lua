local QuestFriendDonate = class("QuestFriendDonate", AbstractQuest)

IQuestFriendDonate = QuestFriendDonate:new{}

function QuestFriendDonate:ctor()
	
end

function QuestFriendDonate:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestFriendDonate:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestFriendDonate:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestFriendDonate