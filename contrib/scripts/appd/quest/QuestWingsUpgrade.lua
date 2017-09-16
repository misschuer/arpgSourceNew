local QuestWingsUpgrade = class("QuestWingsUpgrade", AbstractQuest)

IQuestWingsUpgrade = QuestWingsUpgrade:new{}

function QuestWingsUpgrade:ctor()
	
end

function QuestWingsUpgrade:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local level = playerInfo:GetWingsUpgradeLevel()
	-- ��ó�����
	self:OnUpdate(playerInfo, start, offset, {level})
end

-- ���Ŀ��ֵ
function QuestWingsUpgrade:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestWingsUpgrade:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestWingsUpgrade