
local ActionBase = require('robotd.action.action')
local ActionScened = class('ActionScened', ActionBase)

local points = {}

--获取类型
function ActionScened:GetType()
	return ROBOT_ACTION_TYPE_SCENED
end

--初始化变量
function ActionScened:Initialize(...)
end

--获取类型名
function ActionScened:GetName()
	return 'ActionScened'
end

--心跳
function ActionScened:Update(diff)
	local mapId = self.player:GetMapID()
	if mapId == 0 then
		return true
	end
		
--[[	if self.player.vist then
		return true
	end
	
	local list = {}
	for id,_ in pairs(tb_test_robot_info) do
		table.insert(list,id)
	end
	
	local mapid = list[randInt(1,#list)]
	
	local config = tb_test_robot_info[mapid]
	local pos = config.pos[randInt(1,#config.pos)]
	local x = pos[1] + randInt(-2,2)
	local y = pos[2] + randInt(-2,2)
	self:PushAction('robotd.action.scened.action_scened_guaji', 0, mapid, x, y, 0)
	self.player.vist = true--]]
	
	--tb_test_robot_info
	outFmtDebug("	ActionScened:Update")
	local questOperate = self.player:DoNextQuest()
	if questOperate then
		local callback = questOperate.callback
		outFmtDebug("	questOperate.type = %d questId = %d", questOperate.type, questOperate.questId)
		-- 找NPC
		if questOperate.type == QUEST_TARGET_TYPE_TALK then
			self:PushAction('robotd.action.scened.action_scened_find_npc', questOperate.objcet_id, questOperate.mapid, questOperate.x, questOperate.y, function()
				outFmtDebug("!!!!reach QUEST_TARGET_TYPE_TALK target")
				if callback then
					callback()
				end
				self:SetWaitTimeInterval(2000)
				self.player.questStart = false
			end)
		-- 不需要寻路类
		elseif questOperate.type == QUEST_TARGET_TYPE_USE_ITEM or questOperate.type == QUEST_TARGET_TYPE_SUIT then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		elseif questOperate.type == QUEST_TARGET_TYPE_KILL_MONSTER then
			self:PushAction('robotd.action.scened.action_scened_quest_killmonster', questOperate.objcet_id, questOperate.mapid, questOperate.x, questOperate.y, questOperate.IsFinishMethod, function()
				outFmtDebug("!!!!reach QUEST_TARGET_TYPE_KILL_MONSTER target")
				if callback then
					callback()
				end
				self:SetWaitTimeInterval(2000)
				self.player.questStart = false
			end)
		elseif QUEST_TARGET_TYPE_PICK_GAME_OBJECT == questOperate.type then
			self:PushAction('robotd.action.scened.action_scened_use_game_object', questOperate.objcet_id, questOperate.mapid, questOperate.x, questOperate.y, function()
				outFmtDebug("!!!!reach QUEST_TARGET_TYPE_PICK_GAME_OBJECT target")
				if callback then
					callback()
				end
				self:SetWaitTimeInterval(2000)
				self.player.questStart = false
			end)
		elseif QUEST_TARGET_TYPE_EQUIP_DIVINE == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		elseif QUEST_TARGET_TYPE_RESOURCE_INSTANCE == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
			
		
		elseif QUEST_TARGET_TYPE_JOIN_DOUJIANTAI == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
			
		elseif QUEST_TARGET_TYPE_STRENGTH_SUIT == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
			
		elseif QUEST_TARGET_TYPE_RAISE_SKILL == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
			
		elseif QUEST_TARGET_TYPE_TRAIN_MOUNT == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		elseif QUEST_TARGET_TYPE_SMELT == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		elseif QUEST_TARGET_TYPE_PASS_WORLD_RISK == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		elseif QUEST_TARGET_TYPE_GEM_TOTAL_LEVEL == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		elseif QUEST_TARGET_TYPE_WINGS_UPDRADE_TIMES == questOperate.type then
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		end
	end
	
	self:SetWaitTimeInterval(1000)
	
	return true
end

return ActionScened
