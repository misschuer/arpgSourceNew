local QuestXianfuWin = class("QuestXianfuWin", AbstractQuest)

IQuestXianfuWin = QuestXianfuWin:new{}

function QuestXianfuWin:ctor()
	
end

function QuestXianfuWin:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestXianfuWin:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestXianfuWin:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestXianfuWin