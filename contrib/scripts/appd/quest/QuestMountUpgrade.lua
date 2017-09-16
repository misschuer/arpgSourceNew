local QuestMountUpgrade = class("QuestMountUpgrade", AbstractQuest)

IQuestMountUpgrade = QuestMountUpgrade:new{}

function QuestMountUpgrade:ctor()
	
end

function QuestMountUpgrade:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local spellMgr = playerInfo:getSpellMgr()
	local level = spellMgr:getMountLevel()
	-- ����������
	self:OnUpdate(playerInfo, start, offset, {level})
end

-- ���Ŀ��ֵ
function QuestMountUpgrade:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestMountUpgrade:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestMountUpgrade