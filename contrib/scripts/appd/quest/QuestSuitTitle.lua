local QuestSuitTitle = class("QuestSuitTitle", AbstractQuest)

IQuestSuitTitle = QuestSuitTitle:new{}

function QuestSuitTitle:ctor()
	
end

function QuestSuitTitle:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local titleId = tb_quest[questId].targets[offset+1][ 2 ]
	
	if playerInfo:HasEquTitle(titleId) then
		self:OnUpdate(playerInfo, start, offset, {titleId})
	end
end

-- ���Ŀ��ֵ
function QuestSuitTitle:GetTargetValue(targetInfo)
	return 1
end

-- ���½���, ���Ŀ����ɷ���true
function QuestSuitTitle:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestSuitTitle