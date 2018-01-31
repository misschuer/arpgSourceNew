local QuestEquipsFitRequire = class("QuestEquipsFitRequire", AbstractQuest)

IQuestEquipsFitRequire = QuestEquipsFitRequire:new{}

function QuestEquipsFitRequire:ctor()
	
end

function QuestEquipsFitRequire:OnInit(playerInfo, start, offset)
	local cnt = self:GetProcessValue(playerInfo, start, offset)
	self:OnUpdate(playerInfo, start, offset, {cnt})
end

function QuestEquipsFitRequire:GetProcessValue(playerInfo, start, offset)
	local quest_ptr = playerInfo:getQuestMgr().ptr
	local questId = binLogLib.GetUInt16(quest_ptr, start + QUEST_INFO_ID, 0)
	local targetLevel = tb_quest[questId].targets[offset+1][ 2 ]
	local targetRank = tb_quest[questId].targets[offset+1][ 3 ]
	
	local cnt = 0
	local func = function( ptr )
		local item = require("appd.appd_item").new(ptr)	
		local entry = item:getEntry()
		
		local config = tb_item_template[entry]
		if config then
			if config.level >= targetLevel and config.quality >= targetRank then
				cnt = cnt + 1
			end
		end
	end
	playerInfo:getItemMgr().itemMgr:ForEachBagItem(BAG_TYPE_EQUIP, func)
	
	return cnt
end

-- 获得目标值
function QuestEquipsFitRequire:GetTargetValue(targetInfo)
	return targetInfo[ 4 ]
end

-- 更新进度, 如果目标完成返回true
function QuestEquipsFitRequire:OnUpdate(playerInfo, start, offset, params)
	local cnt = self:GetProcessValue(playerInfo, start, offset)
	return self:OnUpdateModeValue(playerInfo, start, offset, {cnt})
end

return QuestEquipsFitRequire