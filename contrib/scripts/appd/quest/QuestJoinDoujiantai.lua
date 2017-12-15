local QuestJoinDoujiantai = class("QuestJoinDoujiantai", AbstractQuest)

IQuestJoinDoujiantai = QuestJoinDoujiantai:new{}

function QuestJoinDoujiantai:ctor()
	
end

function QuestJoinDoujiantai:OnInit(playerInfo, start, offset)
	local times = playerInfo:getInstanceMgr():getDoujianEnterTimes()
	
	self:OnUpdate(playerInfo, start, offset, {times})
end

-- ���Ŀ��ֵ
function QuestJoinDoujiantai:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestJoinDoujiantai:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestJoinDoujiantai