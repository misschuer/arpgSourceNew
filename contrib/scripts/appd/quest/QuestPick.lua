local QuestPick = class("QuestPick", AbstractQuest)

IQuestPick = QuestPick:new{}

function QuestPick:ctor()
	
end

function QuestPick:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestPick:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestPick:OnUpdate(playerInfo, start, offset, params)
	local showname = nil
	if tb_gameobject_template[params[ 1 ]] then
		showname = tb_gameobject_template[params[ 1 ]].name
	end
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params, showname)
end

return QuestPick