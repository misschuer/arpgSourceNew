local QuestAdventureSkillUpgradeLevel = class("QuestAdventureSkillUpgradeLevel", AbstractQuest)

IQuestAdventureSkillUpgradeLevel = QuestAdventureSkillUpgradeLevel:new{}

function QuestAdventureSkillUpgradeLevel:ctor()
	
end

function QuestAdventureSkillUpgradeLevel:OnInit(playerInfo, start, offset)
	local cnt = self:GetProcessValue(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {cnt})
end

function QuestAdventureSkillUpgradeLevel:GetProcessValue(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLevel = tb_quest[questId].targets[offset+1][ 3 ]
	
	local cnt = 0
	for i = PLAYER_INT_FIELD_PASSIVE_SPELL_START, PLAYER_INT_FIELD_PASSIVE_SPELL_END-1 do
		local id = playerInfo:GetUInt16(i, 0)
		if id > 0 then
			local config = tb_adventure_skill_base[id]
			if config then
				local level = playerInfo:GetByte(i, 2)
				if level >= targetLevel then
					cnt = cnt + 1
				end
			end
		end
	end
	
	return cnt
end

-- 获得目标值
function QuestAdventureSkillUpgradeLevel:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- 更新进度, 如果目标完成返回true
function QuestAdventureSkillUpgradeLevel:OnUpdate(playerInfo, start, offset, params)
	local cnt = self:GetProcessValue(playerInfo, start, offset)
	return self:OnUpdateModeValue(playerInfo, start, offset, {cnt})
end

return QuestAdventureSkillUpgradeLevel