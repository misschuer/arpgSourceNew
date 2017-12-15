local QuestAdventureSkillOneLevel = class("QuestAdventureSkillOneLevel", AbstractQuest)

IQuestAdventureSkillOneLevel = QuestAdventureSkillOneLevel:new{}

function QuestAdventureSkillOneLevel:ctor()
	
end

function QuestAdventureSkillOneLevel:OnInit(playerInfo, start, offset)
	local cnt = self:GetProcessValue(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {cnt})
end

function QuestAdventureSkillOneLevel:GetProcessValue(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetId =  tb_quest[questId].targets[offset+1][ 2 ]
	local targetLevel = tb_quest[questId].targets[offset+1][ 3 ]
	
	local cnt = 0
	for i = PLAYER_INT_FIELD_PASSIVE_SPELL_START, PLAYER_INT_FIELD_PASSIVE_SPELL_END-1 do
		local id = playerInfo:GetUInt16(i, 0)
		if id > 0 and id == targetId then
			local config = tb_adventure_skill_base[id]
			if config then
				local level = playerInfo:GetByte(i, 2)
				cnt = level
			end
		end
	end
	
	return cnt
end

-- 获得目标值
function QuestAdventureSkillOneLevel:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- 更新进度, 如果目标完成返回true
function QuestAdventureSkillOneLevel:OnUpdate(playerInfo, start, offset, params)
	local cnt = self:GetProcessValue(playerInfo, start, offset)
	return self:OnUpdateModeValue(playerInfo, start, offset, {cnt})
end

return QuestAdventureSkillOneLevel