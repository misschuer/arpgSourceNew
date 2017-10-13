local AbstractQuest = class("AbstractQuest")

function AbstractQuest:ctor()
	
end

function AbstractQuest:OnInit(playerInfo, start, offset)
	
end

-- ���Ŀ��ֵ
-- ������Ҫ��д Ĭ��return 1
function AbstractQuest:GetTargetValue(targetInfo)
	return 1
end

-- ���½���, ���Ŀ����ɷ���true
-- ������Ҫ��д Ĭ��return false
function AbstractQuest:OnUpdate(playerInfo, start, offset, params)
	return false
end

-- (����, ����)��ĸ���
function AbstractQuest:OnUpdateModeObjectTimes(playerInfo, start, offset, params, showname)
	local finishMode = params[ 1 ]
	local cnt = params[ 2 ] or 1
	
	local questMgr = playerInfo:getQuestMgr()
	local quest_ptr = questMgr.ptr
	
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local qtIndx = GetOneQuestTargetStartIndx(start, offset)
	local dest = binLogLib.GetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 1)
	local process = binLogLib.GetUInt32(quest_ptr, qtIndx + QUEST_TARGET_INFO_PROCESS)
	
	local mode = tb_quest[questId].targets[offset+1][ 2 ]
	if mode ~= 0 and finishMode ~= mode then
		return false
	end
	
	process = math.min(process + cnt, dest)
	if showname then
		if process >= dest then
			showname = "[00FF00]"..showname
		end
		playerInfo:CallOptResult(OPERTE_TYPE_QUEST, QUEST_TYPE_PROCESS,{showname, process, dest})
	end
	binLogLib.SetUInt32(quest_ptr, qtIndx + QUEST_TARGET_INFO_PROCESS, process)
	if process >= dest then
		binLogLib.SetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 0, 1)
		return true
	end
	
	return false
end

-- (����)��ĸ���
function AbstractQuest:OnUpdateModeTimes(playerInfo, start, offset, params)
	params = params or {}
	local questMgr = playerInfo:getQuestMgr()
	local quest_ptr = questMgr.ptr
	local cnt = params[ 1 ] or 1
	
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local qtIndx = GetOneQuestTargetStartIndx(start, offset)
	local dest = binLogLib.GetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 1)
	local process = binLogLib.GetUInt32(quest_ptr, qtIndx + QUEST_TARGET_INFO_PROCESS)
	
	process = math.min(process + cnt, dest)
	binLogLib.SetUInt32(quest_ptr, qtIndx + QUEST_TARGET_INFO_PROCESS, process)
	if process >= dest then
		binLogLib.SetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 0, 1)
		return true
	end
	
	return false
end

-- (��ֵ)��ĸ���
function AbstractQuest:OnUpdateModeValue(playerInfo, start, offset, params)
	local value = params[ 1 ]
	
	local questMgr = playerInfo:getQuestMgr()
	local quest_ptr = questMgr.ptr
	
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local qtIndx = GetOneQuestTargetStartIndx(start, offset)
	local dest = binLogLib.GetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 1)
	
	local process = math.min(value, dest)
	binLogLib.SetUInt32(quest_ptr, qtIndx + QUEST_TARGET_INFO_PROCESS, process)
	if process >= dest then
		binLogLib.SetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 0, 1)
		return true
	end
	return false
end

-- (����, ��ֵ)��ĸ���
function AbstractQuest:OnUpdateModeObjectValue(playerInfo, start, offset, params)
	local finishMode = params[ 1 ]
	local value = params[ 2 ]
	
	local questMgr = playerInfo:getQuestMgr()
	local quest_ptr = questMgr.ptr
	
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local qtIndx = GetOneQuestTargetStartIndx(start, offset)
	local dest = binLogLib.GetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 1)
	
	local mode = tb_quest[questId].targets[offset+1][ 2 ]
	if mode ~= 0 and finishMode ~= mode then
		return false
	end
	
	process = math.min(value, dest)
	binLogLib.SetUInt32(quest_ptr, qtIndx + QUEST_TARGET_INFO_PROCESS, process)
	if process >= dest then
		binLogLib.SetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 0, 1)
		return true
	end
	
	return false
end

-- (����, ����)��ĸ���
function AbstractQuest:OnUpdateDoubleModeObject(playerInfo, start, offset, params)
	local finishMode  = params[ 1 ]
	local finishMode2 = params[ 2 ]
	
	local questMgr = playerInfo:getQuestMgr()
	local quest_ptr = questMgr.ptr
	
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local qtIndx = GetOneQuestTargetStartIndx(start, offset)
	local dest = binLogLib.GetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 1)
	local process = binLogLib.GetUInt32(quest_ptr, qtIndx + QUEST_TARGET_INFO_PROCESS)
	
	local mode = tb_quest[questId].targets[offset+1][ 2 ]
	if mode ~= 0 and finishMode ~= mode then
		return false
	end
	
	local mode2 = tb_quest[questId].targets[offset+1][ 3 ]
	if mode2 ~= 0 and finishMode2 ~= mode2 then
		return false
	end
	
	binLogLib.SetUInt32(quest_ptr, qtIndx + QUEST_TARGET_INFO_PROCESS, 1)
	binLogLib.SetUInt16(quest_ptr, qtIndx + QUEST_TARGET_INFO_SHORT0, 0, 1)
	return true
end

-- ���һ��Ŀ��binlog�ĳ�ʼλ��
function GetOneQuestTargetStartIndx(start, offset)
	return start + QUEST_INFO_STEP_START + offset * MAX_QUEST_TARGET_INFO_COUNT
end

return AbstractQuest