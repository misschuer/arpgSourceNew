local QuestJoinResourceInstance = class("QuestJoinResourceInstance", AbstractQuest)

IQuestJoinResourceInstance = QuestJoinResourceInstance:new{}

function QuestJoinResourceInstance:ctor()
	
end

function QuestJoinResourceInstance:OnInit(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local mapId = tb_quest[questId].targets[offset+1][ 2 ]

	for res_type = 1,5 do
		local indx = INSTANCE_INT_FIELD_RES_START + res_type - 1
		local times = playerInfo:getInstanceMgr():GetByte(indx, 0)
		local config = tb_instance_res[res_type * 8 - 7]
		
		if config and config.mapid == mapId then
			self:OnUpdate(playerInfo, start, offset, {mapId,times})
		end
	end
end

-- 获得目标值
function QuestJoinResourceInstance:GetTargetValue(targetInfo)
	return targetInfo[ 3 ]
end

-- 更新进度, 如果目标完成返回true
function QuestJoinResourceInstance:OnUpdate(playerInfo, start, offset, params)
	return self:OnUpdateModeObjectTimes(playerInfo, start, offset, params)
end

return QuestJoinResourceInstance