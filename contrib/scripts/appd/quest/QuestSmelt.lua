local QuestSmelt = class("QuestSmelt", AbstractQuest)

IQuestSmelt = QuestSmelt:new{}

function QuestSmelt:ctor()
	
end

function QuestSmelt:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestSmelt:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestSmelt:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestSmelt