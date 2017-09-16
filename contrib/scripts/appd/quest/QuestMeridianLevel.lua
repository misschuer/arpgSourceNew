local QuestMeridianLevel = class("QuestMeridianLevel", AbstractQuest)

IQuestMeridianLevel = QuestMeridianLevel:new{}

function QuestMeridianLevel:ctor()
	
end

function QuestMeridianLevel:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local spellMgr = playerInfo:getSpellMgr()
	local level = spellMgr:getMeridianLevel()
	-- ��þ����ȼ�
	self:OnUpdate(playerInfo, start, offset, {level})
end

-- ���Ŀ��ֵ
function QuestMeridianLevel:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestMeridianLevel:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestMeridianLevel