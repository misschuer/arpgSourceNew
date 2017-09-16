local QuestMountStrengthLevel = class("QuestMountStrengthLevel", AbstractQuest)

IQuestMountStrengthLevel = QuestMountStrengthLevel:new{}

function QuestMountStrengthLevel:ctor()
	
end

function QuestMountStrengthLevel:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local spellMgr = playerInfo:getSpellMgr()
	local level = spellMgr:getMountLevelBase()
	-- �������ǿ����
	self:OnUpdate(playerInfo, start, offset, {level})
end

-- ���Ŀ��ֵ
function QuestMountStrengthLevel:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestMountStrengthLevel:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestMountStrengthLevel