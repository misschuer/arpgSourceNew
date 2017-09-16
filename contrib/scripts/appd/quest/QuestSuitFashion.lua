local QuestSuitFashion = class("QuestSuitFashion", AbstractQuest)

IQuestSuitFashion = QuestSuitFashion:new{}

function QuestSuitFashion:ctor()
	
end

function QuestSuitFashion:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local fashionId = tb_quest[questId].targets[offset+1][ 2 ]
	
	if false then
		self:OnUpdate(playerInfo, start, offset, {fashionId})
	end
end

-- ���Ŀ��ֵ
function QuestSuitFashion:GetTargetValue(targetInfo)
	return 1
end

-- ���½���, ���Ŀ����ɷ���true
function QuestSuitFashion:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestSuitFashion