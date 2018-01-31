local QuestMainSkillUpgradeLevel = class("QuestMainSkillUpgradeLevel", AbstractQuest)

IQuestMainSkillUpgradeLevel = QuestMainSkillUpgradeLevel:new{}

function QuestMainSkillUpgradeLevel:ctor()
	
end

function QuestMainSkillUpgradeLevel:OnInit(playerInfo, start, offset)
	--local cnt = self:GetProcessValue(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {})
end

function QuestMainSkillUpgradeLevel:GetProcessValue(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLevel = tb_quest[questId].targets[offset+1][ 3 ]
	
	local cnt = 0
	for i = PLAYER_INT_FIELD_SPELL_START, PLAYER_INT_FIELD_SPELL_END-1 do
		local id = playerInfo:GetUInt16(i, 0)
		if id > 0 then
			local config = tb_skill_base[id]
			if 1 <= config.skill_slot and config.skill_slot <= 5 and config.pre == 0 then
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
function QuestMainSkillUpgradeLevel:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- 更新进度, 如果目标完成返回true
function QuestMainSkillUpgradeLevel:OnUpdate(playerInfo, start, offset, params)
	local cnt = self:GetProcessValue(playerInfo, start, offset)
	return self:OnUpdateModeValue(playerInfo, start, offset, {cnt})
end

return QuestMainSkillUpgradeLevel