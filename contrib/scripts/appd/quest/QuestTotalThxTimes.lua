local QuestTotalThxTimes = class("QuestTotalThxTimes", AbstractQuest)

IQuestTotalThxTimes = QuestTotalThxTimes:new{}

function QuestTotalThxTimes:ctor()
	
end

function QuestTotalThxTimes:OnInit(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {playerInfo:GetFactionGiftBeenThankCount()})
end

-- ���Ŀ��ֵ
function QuestTotalThxTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestTotalThxTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestTotalThxTimes