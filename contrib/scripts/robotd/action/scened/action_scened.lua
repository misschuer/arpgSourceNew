
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

function ActionScened:testStage(instSubType, enterFunc)
	local mapId = self.player:GetMapID()
	
	if not self.player.mapInfo then
		return true
	end
	
	if tb_map[mapId].inst_sub_type ~= instSubType then
		self.player.vist = false
	end
	
	if tb_map[mapId].inst_sub_type == instSubType then
		self.player.stage = false
	end
	
	if self.player.stage then
		return true
	end	
	
	if self.player.vist then
		return true
	end	
	
	if tb_map[mapId].inst_sub_type ~= instSubType then
		enterFunc()
		self.player.stage = true
		return true
	end
	
	if tb_map[mapId].inst_sub_type == instSubType then
		if (self.player.mapInfo:GetMapState() > 1) then
			return true
		end
	
		local x,y = self.player:GetPos()
		
		if instSubType == INSTANCE_SUB_TYPE_MASS_BOSS then
			if mapId == 10000 then
				local rd = randInt(1,4)
				
				x = tb_mass_boss_info[rd].bossPos[1]
				y = tb_mass_boss_info[rd].bossPos[2]
			elseif mapId == 10001 then
				local rd = randInt(5,8)
				x = tb_mass_boss_info[rd].bossPos[1]
				y = tb_mass_boss_info[rd].bossPos[2]
				
			end
		end
		self.player.vist = true
		
		self:PushAction('robotd.action.scened.action_scened_guaji', 0, mapId, x, y, 0, function() 
			--self.player.vist = false
			self.player.enterCount = 0
		end)
		return true
	end
	
	return true
end


local test_instance_type = {-----INSTANCE_SUB_TYPE_VIP,	-- vip副本
							-----INSTANCE_SUB_TYPE_KUAFU_3V3,	-- 跨服3v3
							-----INSTANCE_SUB_TYPE_XIANFU,	-- 仙府夺宝
							-----INSTANCE_SUB_TYPE_XIANFU_EXPERIENCE,	-- 仙府体验
							-----INSTANCE_SUB_TYPE_XIULIAN,	-- 修炼房
							-----INSTANCE_SUB_TYPE_PLOT,	-- 原地剧情副本
							-----INSTANCE_SUB_TYPE_RISK,	-- 世界冒险
							
							--INSTANCE_SUB_TYPE_FACTION_BOSSDEFENSE,	-- 家族首领挑战
							--INSTANCE_SUB_TYPE_FACTION_TOWER,	-- 家族无尽远征
							--INSTANCE_SUB_TYPE_FACTION_MATCH,	-- 家族战副本
							
							INSTANCE_SUB_TYPE_QUALIFY,	-- 排位赛
							
							
							INSTANCE_SUB_TYPE_TRIAL,-- 试炼塔副本
							INSTANCE_SUB_TYPE_WORLD_BOSS,	-- 世界BOSS
							INSTANCE_SUB_TYPE_RES,	-- 资源副本
							INSTANCE_SUB_TYPE_DOUJIANTAI,	-- 斗剑台
							INSTANCE_SUB_TYPE_MASS_BOSS,	-- 全民boss
							INSTANCE_SUB_TYPE_KUAFU_GROUP,	-- 跨服组队副本
							INSTANCE_SUB_TYPE_PRIVATE_BOSS,	-- 个人BOSS
							INSTANCE_SUB_TYPE_STAGE,	-- 闯关副本
							INSTANCE_SUB_TYPE_GROUP_EXP,	-- 经验副本
}
--心跳
function ActionScened:Update(diff)
	local mapId = self.player:GetMapID()
	
	--[[if true then
		return true
	end--]]
	
	if not tb_map[mapId] then
		self:SetWaitTimeInterval(2000)
		return true
	end
	
	
	if false then
		if self.player:GetLevel() < 100 then
			return true
		end
		
		if not self.player.enterCount then
			self.player.enterCount = 0
		end
		
		if self.player.stage and not self.player.vist then
			self.player.enterCount = self.player.enterCount + 1
		end
		
		if self.player.enterCount > 300 or not self.player.select then
			local ri = randInt(1,#test_instance_type)
			self.player.select  = test_instance_type[ri]
			outFmtDebug("!!!!!!!!!!!!!change select instance %d",self.player.select)
			self.player.enterCount = 0
			self.player.stage = false
		end
		
		self:StartEnterInstance()
		
		
	end

	--[[
	if true then
		if self.player.vist then
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
		self.player.vist = true
		return true
	end--]]

	--tb_test_robot_info
	outFmtDebug("	ActionScened:Update")
	local questOperate = self.player:DoNextQuest()
	if questOperate then
		local callback = questOperate.callback
		outFmtDebug("	questOperate.type = %d questId = %d", questOperate.type, questOperate.questId)
		-- 找NPC
		if questOperate.type == QUEST_TARGET_TYPE_TALK then
			self:PushAction('robotd.action.scened.action_scened_find_npc', questOperate.objcet_id, questOperate.mapid, questOperate.x, questOperate.y, function(uguid)
				outFmtDebug("!!!!reach QUEST_TARGET_TYPE_TALK target")
				if callback then
					callback(uguid)
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
			if not questOperate.params then
				self:PushAction('robotd.action.scened.action_scened_quest_killmonster', questOperate.objcet_id, questOperate.mapid, questOperate.x, questOperate.y, questOperate.IsFinishMethod, function()
					outFmtDebug("!!!!reach QUEST_TARGET_TYPE_KILL_MONSTER target")
					if callback then
						callback()
					end
					self:SetWaitTimeInterval(2000)
					self.player.questStart = false
				end)
			else
				if not self.player.enterCount then
					self.player.enterCount = 0
				end
				
				if self.player.stage then
					self.player.enterCount = self.player.enterCount + 1
				end
				
				if self.player.enterCount > 5 then
					self.player.enterCount = 0
					self.player.stage = false
					self.player.vist = false
				end
			
				if questOperate.params[ 1 ] == MODULE_BOSS and questOperate.params[ 2 ] == MODULE_BOSS_PERSON_BOSS then
					return self:testStage(INSTANCE_SUB_TYPE_PRIVATE_BOSS, function()
						self.player:call_enter_private_boss(1)
					end)
				end
				
			end
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
		elseif QUEST_TARGET_TYPE_STAGE_INSTANCE_ID == questOperate.type then
			if not self.player.enterCount then
				self.player.enterCount = 0
			end
			
			if self.player.stage then
				self.player.enterCount = self.player.enterCount + 1
			end
			
			if self.player.enterCount > 5 then
				self.player.enterCount = 0
				self.player.stage = false
				self.player.vist = false
			end
			self:testStage(INSTANCE_SUB_TYPE_STAGE, function()
				outFmtDebug("QUEST_TARGET_TYPE_STAGE_INSTANCE_ID stage quest enter stage")
				self.player:call_enter_stage_instance()
			end)
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		elseif QUEST_TARGET_TYPE_REALMBREAK_LEVEL == questOperate.type then
			if callback then
				if callback() then
					
				else
					if not self.player.enterCount then
						self.player.enterCount = 0
					end
					
					if self.player.stage then
						self.player.enterCount = self.player.enterCount + 1
					end
					
					if self.player.enterCount > 5 then
						self.player.enterCount = 0
						self.player.stage = false
					end
					self:testStage(INSTANCE_SUB_TYPE_STAGE, function()
						outFmtDebug("QUEST_TARGET_TYPE_REALMBREAK_LEVEL level not reach enter stage")
						self.player:call_enter_stage_instance()
					end)
				end
			end
			
			self:SetWaitTimeInterval(2000)
		elseif QUEST_TARGET_TYPE_PLAYER_LEVEL == questOperate.type then
			if callback then
				if callback() then
					outFmtDebug("QUEST_TARGET_TYPE_PLAYER_LEVEL level reached")
				else
					if not self.player.enterCount then
						self.player.enterCount = 0
					end
					
					if self.player.stage then
						self.player.enterCount = self.player.enterCount + 1
					end
					local test_instance_type = {--INSTANCE_SUB_TYPE_QUALIFY,	-- 排位赛
												INSTANCE_SUB_TYPE_TRIAL,-- 试炼塔副本
												--INSTANCE_SUB_TYPE_WORLD_BOSS,	-- 世界BOSS
												INSTANCE_SUB_TYPE_RES,	-- 资源副本
												--INSTANCE_SUB_TYPE_DOUJIANTAI,	-- 斗剑台
												--INSTANCE_SUB_TYPE_MASS_BOSS,	-- 全民boss
												--INSTANCE_SUB_TYPE_KUAFU_GROUP,	-- 跨服组队副本
												INSTANCE_SUB_TYPE_PRIVATE_BOSS,	-- 个人BOSS
												INSTANCE_SUB_TYPE_STAGE,	-- 闯关副本
												INSTANCE_SUB_TYPE_GROUP_EXP,	-- 经验副本
}
					if self.player.enterCount > 5 or not self.player.select then
						local ri = randInt(1,#test_instance_type)
						self.player.select  = test_instance_type[ri]
						outFmtDebug("!!!!!!!!!!!!!change select instance %d",self.player.select)
						self.player.enterCount = 0
						self.player.stage = false
					end
					outFmtDebug("QUEST_TARGET_TYPE_PLAYER_LEVEL level now %d not reached select %d  ",self.player:GetLevel(),self.player.select)
					self:StartEnterInstance()
				end
			end
			
			self:SetWaitTimeInterval(2000)
		else
			if callback then
				callback()
			end
			self:SetWaitTimeInterval(2000)
		end
		
		self.player:call_one_step_robot_up(randInt(1,3))
	end
	
	self:SetWaitTimeInterval(1000)
	
	
	return true
end

function ActionScened:StartEnterInstance()
	if self.player.select == INSTANCE_SUB_TYPE_STAGE then
	
		return self:testStage(self.player.select, function()
			self.player:call_enter_stage_instance()
		end)
		
	elseif self.player.select == INSTANCE_SUB_TYPE_PRIVATE_BOSS then
	
		return self:testStage(self.player.select, function()
			local id = randInt(1,#tb_private_boss_info)
			self.player:call_enter_private_boss(id)
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_VIP then
		return self:testStage(self.player.select, function()
			local id = randInt(1,#tb_map_vip)
			local hard = randInt(1,#tb_map_vip[id].force)
			--self.player:call_enter_vip_instance(id,hard)
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_TRIAL then
		return self:testStage(self.player.select, function()
			self.player:call_enter_trial_instance()
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_WORLD_BOSS then
		return self:testStage(self.player.select, function()
			self.player:call_world_boss_enroll()
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_RES then
		return self:testStage(self.player.select, function()
			local id = randInt(1,#tb_instance_res)
			self.player:call_res_instance_enter(id)
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_KUAFU_3V3 then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_XIANFU then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_DOUJIANTAI then
		return self:testStage(self.player.select, function()
			local id = randInt(0,2)
			self.player:call_doujiantai_fight(id)
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_XIANFU_EXPERIENCE then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_XIULIAN then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_PLOT then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_MASS_BOSS then
		return self:testStage(self.player.select, function()
			local id = randInt(1,#tb_mass_boss_info)
			self.player:call_try_mass_boss(id)
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_KUAFU_GROUP then
		return self:testStage(self.player.select, function()
			local id = randInt(4,10)--tb_group_instance_base
			self.player:call_group_instance_match(id,0)
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_FACTION_BOSSDEFENSE then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_FACTION_TOWER then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_QUALIFY then
		return self:testStage(self.player.select, function()
			self.player:call_match_single_pvp()
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_RISK then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_FACTION_MATCH then
		return self:testStage(self.player.select, function()
			
		end)
	elseif self.player.select == INSTANCE_SUB_TYPE_GROUP_EXP then
		return self:testStage(self.player.select, function()
			self.player:call_enter_group_exp(0)
		end)
	end
end

return ActionScened
