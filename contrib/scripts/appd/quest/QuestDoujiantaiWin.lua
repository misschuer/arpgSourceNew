local QuestDoujiantaiWin = class("QuestDoujiantaiWin", AbstractQuest)

IQuestDoujiantaiWin = QuestDoujiantaiWin:new{}

function QuestDoujiantaiWin:ctor()
	
end

function QuestDoujiantaiWin:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestDoujiantaiWin:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestDoujiantaiWin:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestDoujiantaiWin