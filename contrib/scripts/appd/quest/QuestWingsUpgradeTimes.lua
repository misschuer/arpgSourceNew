local QuestWingsUpgradeTimes = class("QuestWingsUpgradeTimes", AbstractQuest)

IQuestWingsUpgradeTimes = QuestWingsUpgradeTimes:new{}

function QuestWingsUpgradeTimes:ctor()
	
end

function QuestWingsUpgradeTimes:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestWingsUpgradeTimes:GetTargetValue(targetInfo)
	return targetInfo[ 2 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestWingsUpgradeTimes:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeTimes(playerInfo, start, offset, params)
end

return QuestWingsUpgradeTimes