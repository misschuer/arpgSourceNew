local QuestQualifyWin = class("QuestQualifyWin", AbstractQuest)

IQuestQualifyWin = QuestQualifyWin:new{}

function QuestQualifyWin:ctor()
	
end

function QuestQualifyWin:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestQualifyWin:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestQualifyWin:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestQualifyWin