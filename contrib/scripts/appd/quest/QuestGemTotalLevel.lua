local QuestGemTotalLevel = class("QuestGemTotalLevel", AbstractQuest)

IQuestGemTotalLevel = QuestGemTotalLevel:new{}

function QuestGemTotalLevel:ctor()
	
end

function QuestGemTotalLevel:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local level = playerInfo:GetGemTotalLevel()
	-- ��ó�����
	self:OnUpdate(playerInfo, start, offset, {level})
end

-- ���Ŀ��ֵ
function QuestGemTotalLevel:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestGemTotalLevel:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeValue(playerInfo, start, offset, params)
end

return QuestGemTotalLevel