local QuestRaiseSkill = class("QuestRaiseSkill", AbstractQuest)

IQuestRaiseSkill = QuestRaiseSkill:new{}

function QuestRaiseSkill:ctor()
	
end

function QuestRaiseSkill:OnInit(playerInfo, start, offset)
	--[[
	ԭ�����������������ټ�
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local spellId = tb_quest[questId].targets[offset+1][ 2 ]
	
	local level = playerLib.GetDesignatedSkillLevel(playerInfo.ptr, spellId)
	self:OnUpdate(quest_ptr, start, offset, {spellId, level})
	--]]
end

-- ���Ŀ��ֵ
function QuestRaiseSkill:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestRaiseSkill:OnUpdate(playerInfo, start, offset, params)
--	return self:OnUpdateModeObjectValue(quest_ptr, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestRaiseSkill