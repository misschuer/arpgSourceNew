local QuestActiveTask = class("QuestActiveTask", AbstractQuest)

IQuestActiveTask = QuestActiveTask:new{}

function QuestActiveTask:ctor()
	
end

function QuestActiveTask:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestActiveTask:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestActiveTask:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestActiveTask