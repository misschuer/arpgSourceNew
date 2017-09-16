local QuestWingsStrengthLevel = class("QuestWingsStrengthLevel", AbstractQuest)

IQuestWingsStrengthLevel = QuestWingsStrengthLevel:new{}

function QuestWingsStrengthLevel:ctor()
	
end

function QuestWingsStrengthLevel:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local spellMgr = playerInfo:getSpellMgr()
	local level = spellMgr:GetWingsLevel()
	-- ��ó��ǿ����
	self:OnUpdate(playerInfo, start, offset, {level})
end

-- ���Ŀ��ֵ
function QuestWingsStrengthLevel:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestWingsStrengthLevel:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestWingsStrengthLevel