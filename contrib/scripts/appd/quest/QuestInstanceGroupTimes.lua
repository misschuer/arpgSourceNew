local QuestInstanceGroupTimes = class("QuestInstanceGroupTimes", AbstractQuest)

IQuestInstanceGroupTimes = QuestInstanceGroupTimes:new{}

function QuestInstanceGroupTimes:ctor()
	
end

function QuestInstanceGroupTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestInstanceGroupTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestInstanceGroupTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestInstanceGroupTimes