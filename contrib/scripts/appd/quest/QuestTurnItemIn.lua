local QuestTurnItemIn = class("QuestTurnItemIn", AbstractQuest)

IQuestTurnItemIn = QuestTurnItemIn:new{}

function QuestTurnItemIn:ctor()
	
end

function QuestTurnItemIn:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestTurnItemIn:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestTurnItemIn:OnUpdate(playerInfo, start, offset, params)
	
end

return QuestTurnItemIn