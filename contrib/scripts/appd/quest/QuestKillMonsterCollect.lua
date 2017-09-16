local QuestKillMonsterCollect = class("QuestKillMonsterCollect", AbstractQuest)

IQuestKillMonsterCollect = QuestKillMonsterCollect:new{}

function QuestKillMonsterCollect:ctor()
	
end

function QuestKillMonsterCollect:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
function QuestKillMonsterCollect:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- ���½���, ���Ŀ����ɷ���true
function QuestKillMonsterCollect:OnUpdate(playerInfo, start, offset, params)	
	local questMgr = playerInfo:getQuestMgr()
	local quest_ptr = questMgr.ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	-- �Ƿ��Ƕ�Ӧ��Ұ��
	local finishMode = params[ 1 ]
	local mode = tb_quest[questId].targets[offset+1][ 4 ]
	if mode ~= 0 and finishMode ~= mode then
		return false
	end
	-- �Ƿ������Ʒ
	local rate = tb_quest[questId].targets[offset+1][ 5 ]
	local ran = randInt(1, 10000)
	-- û�����
	if rate < ran then
		return false
	end
	-- �����������
	local entry = tb_quest[questId].targets[offset+1][ 2 ]
	local showname = nil
	if tb_item_template[entry] then
		showname = tb_item_template[entry].name
	end
	
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, {entry}, showname)
end

return QuestKillMonsterCollect