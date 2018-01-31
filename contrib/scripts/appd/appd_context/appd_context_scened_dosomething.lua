function PlayerInfo:CallScenedDoSomething(typ, data, str)
	call_scened_appd_to_send_do_something(self:GetScenedFD(), self:GetGuid(), typ, data, str)
end

-- 场景服发过来要应用服做点事
function PlayerInfo:DoGetScenedDoSomething  ( ntype, data, str)
	if SCENED_APPD_ENTER_VIP_INSTANCE == ntype then
		self:checkVipMapTeleport(data, str)
	elseif SCENED_APPD_ENTER_TRIAL_INSTANCE == ntype then
		self:checkTrialMapTeleport()
	elseif SCENED_APPD_ENTER_RES_INSTANCE == ntype then
		--进入资源副本
		self:checkResMapTeleport(data)
	elseif SCENED_APPD_ENTER_DOUJIANTAI_INSTANCE == ntype then
		self:OnDoujiantaiFight(data)
	elseif SCENED_APPD_WORLD_BOSS_ENROLL == ntype then
		onEnrole(self)
	elseif SCENED_APPD_PASS_RES_INSTANCE == ntype then
		--通关资源副本
		self:passResInstance(data)
	elseif SCENED_APPD_PASS_WORLD_RISK == ntype then
		self:passWorldRiskInstance(data)
	elseif SCENED_APPD_PASS_TRIAL_INSTANCE == ntype then
		self:passTrialInstance(data)
	elseif SCENED_APPD_PASS_VIP_INSTANCE == ntype then
		self:passVipInstance(data, tonumber(str))
	elseif SCENED_APPD_USE_ITEM == ntype then
		-- 判断如果道具不是药品就不使用了
		if tb_item_template[data].type == ITEM_TYPE_MEDICINE then
			UseHpItem(self, data, 1)
		end
	elseif SCENED_APPD_USE_RESPAWN_ITEM == ntype then
		useRespawn(self)
	elseif SCENED_APPD_ADD_ENEMY == ntype then
		self:AddEnemy(str, data)
	elseif SCENED_APPD_ADD_MAIL == ntype then
		local mailInfo = string.split(str, '|')
		local rewards = mailInfo[ 1 ]
		local name = mailInfo[ 2 ]
		local desc = mailInfo[ 3 ]
		local giftType = tonumber(mailInfo[ 4 ])
		AddGiftPacksData(self:GetGuid(),0,giftType,os.time(),os.time() + 86400*30, name, desc, rewards, SYSTEM_NAME)
	elseif SCENED_APPD_KILL_MONSTER == ntype then
		-- 成就
		self:AddAchieve(QUEST_TARGET_TYPE_KILL_MONSTER_NUM, 1)
		local questMgr = self:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_KILL_MONSTER, {data})
	elseif SCENED_APPD_KILL_MONSTER_COLLECT == ntype then
		local questMgr = self:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_KILL_MONSTER_COLLECT, {data})
	elseif SCENED_APPD_JOIN_FIELD_BOSS == ntype then
		-- 参加野外BOSS
		local questMgr = self:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_FIELD_BOSS, {data})
	elseif SCENED_APPD_GAMEOBJECT == ntype then
		-- 采集物品
		local questMgr = self:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_PICK_GAME_OBJECT, {data})
	elseif SCENED_APPD_TALK == ntype then
		-- 对话
		local questId = tonumber(str)
		-- 加任务
		local questMgr = self:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_TALK, {data, questId})
		
		-- 如果是接镖NPC, 判断是否可接
		local escort_config = tb_escort_base[1]
		if escort_config.npc == data then
			if questMgr:GetQuestEscortFinishTime() < os.time() then
				local quest_index_list = {}
				for index = 1,#escort_config.quest_id do
					if self:GetLevel() >= escort_config.level[index] then
						table.insert(quest_index_list,index)
					end
				end
				if #quest_index_list == 0 then
					return
				end
				local indx = quest_index_list[randInt(1,#quest_index_list)]
				local quest_id = escort_config.quest_id[indx]
				local item_id = escort_config.quest_item_id
				local item_count = escort_config.quest_item_num[indx]
				local time_limit = escort_config.time_limit
				
				self:AppdAddItems({{item_id,item_count}},MONEY_CHANGE_ESCORT,LOG_ITEM_OPER_TYPE_ESCORT)
				questMgr:OnAddQuest(quest_id,QUEST_FIELD_ESCORT_QUEST_START,QUEST_FIELD_ESCORT_QUEST_END)
				questMgr:SetQuestEscortFinishTime(os.time() + time_limit*60)
				self:SetEscortState(QUEST_ESCORT_STATE_NORMAL)
			end
		end
		
		
		
	elseif SCENED_APPD_RIDE == ntype then
		self:SetRideState(data)
		
	elseif SCENED_APPD_GOLD_RESPAWN == ntype then
		if self:costMoneys(MONEY_CHANGE_ATUO_GOLD_RESPAWN, {{MONEY_TYPE_BIND_GOLD, data}}) then
			-- 通知场景服复活
			self:CallScenedDoSomething(APPD_SCENED_RESPAWN)
		end
	elseif SCENED_APPD_DOUJIANTAI == ntype then
		-- 斗剑台结果
		globalCounter:BattleFinish(self, data, tonumber(str))
		-- 加倒计时
		local instMgr = self:getInstanceMgr()
		local curtime = instMgr:getDoujianEnterTimes()
		local config = tb_doujiantai_base[ 1 ]
		local bcd = config.battleCountdown
		local cdSeconds
		if curtime >= #bcd then
			cdSeconds = bcd[#bcd]
		else
			cdSeconds = bcd[curtime]
		end
		
		instMgr:setDoujianCD(cdSeconds + os.time())
	
	elseif SCENED_APPD_XIULIANCHANG == ntype then
		-- 修练场掠夺结果
		self:PlunderFinish(data, str)
	elseif SCENED_APPD_XIANFU_PRACTISE == ntype then
		self:AppdAddItems({{data, tonumber(str)}}, nil, LOG_ITEM_OPER_TYPE_XIANFU_PRACTISE)
	elseif SCENED_APPD_ADD_OFFLINE_RISK_REWARD == ntype then
		--[[local items = string.split(str, "|")
		local sell = 0
		local itemMgr = self:getItemMgr()
		local empty_count = itemMgr:getEmptyCount(BAG_TYPE_EQUIP_BAG)	--取出剩余位置个数
		local rewardDict = {}
		local dict = {}
		for _, item in ipairs(items) do
			local itemInfo = string.split(item, ',')
			local entry = tonumber(itemInfo[ 1 ])
			local count = tonumber(itemInfo[ 2 ])
			dict[entry] = count
			if tb_item_template[entry].pos > 0 then
				-- 已经满了
				if empty_count <= 0 then
					dict[entry] = nil
				end
				-- 当前会超过
				if empty_count > 0 and empty_count < count then
					dict[entry] = empty_count
				end

				empty_count = empty_count - count
				for k = 1, count do
					table.insert(rewardDict, {entry, 1})
				end
			else
				table.insert(rewardDict, {entry, count})
			end
		end
		
		if empty_count < 0 then
			sell = -empty_count
		end
		
		self:AppdAddItems(rewardDict, MONEY_CHANGE_OFFLINE, LOG_ITEM_OPER_TYPE_OFFLINE, nil, nil, nil, 3)
		
		local list = Change_To_Item_Reward_Info(dict)
		self:call_offline_reward_result (sell, data, 0, 0, list)--]]
	elseif SCENED_APPD_ENTER_MASS_BOSS_INSTANCE == ntype then
		self:checkMassBossMapTeleport(data)
	elseif SCENED_APPD_FACTION_TOWER_WIN == ntype then
		local faction = app.objMgr:getObj(self:GetFactionId())
		if faction then
			faction:OnTowerTodayFloorUpdate(self,data)
		end
	elseif SCENED_APPD_SINGLE_PVP_RESULT == ntype then
		self:OnProcessSingleMatchResult(data, str)
	elseif SCENED_APPD_ENTER_FACTION_BOSSDEFENSE_INSTANCE == ntype then
		local faction_guid = self:GetFactionId()
		if faction_guid == "" then
			return
		end
		
		if not app.objMgr:IsFactionGuid(faction_guid) then
			return
		end
		
		local faction = app.objMgr:getObj(faction_guid)
		if faction == nil then
			return
		end
		faction:BossDenfenseChallenge(self,data)
	elseif SCENED_APPD_ENTER_FACTION_TOWER_INSTANCE == ntype then
		local faction_guid = self:GetFactionId()
		if faction_guid == "" then
			return
		end
		
		if not app.objMgr:IsFactionGuid(faction_guid) then
			return
		end
		
		local faction = app.objMgr:getObj(faction_guid)
		if faction == nil then
			return
		end
		faction:TowerChallenge(self)
		
	elseif SCENED_APPD_ENTER_PRIVATE_BOSS_INSTANCE == ntype then
		self:checkPrivateBossMapTeleport(data)
	elseif SCENED_APPD_PRIVATE_BOSS_WIN == ntype then
		self:onPrivateBossWin(data)
	elseif SCENED_APPD_PLAYER_DEAD_PROCESS == ntype then
		if data == 1 then
			local drop_dict = {}
			for item_id,info in pairs(tb_adventure_death_drop) do
				local item_num = self:GetMoney(item_id)
				if item_num > info.limit then
					local drop_num = math.min(item_num - info.limit,math.ceil(item_num * info.percent /100))
					table.insert(drop_dict,{item_id,drop_num})
				end
				
			end
			
			outFmtDebug("SCENED_APPD_PLAYER_DEAD_PROCESS  GetEscortState is %d ",self:GetEscortState())
			if self:GetEscortState() == QUEST_ESCORT_STATE_NORMAL then
				outFmtDebug("QUEST_ESCORT_STATE_NORMAL to QUEST_ESCORT_STATE_ROB")
				self:SetEscortState(QUEST_ESCORT_STATE_ROB)
				local config = tb_escort_base[1]
				local item_id = config.quest_item_id
				local rob_lost = config.rob_lost
				local count = math.floor(self:CountItem(item_id) * rob_lost / 100)
				table.insert(drop_dict,{item_id,count})
				outFmtDebug("SCENED_APPD_PLAYER_DEAD_PROCESS drop id %d num %d",item_id,count)
			end
			self:useAllItems(MONEY_CHANGE_ADVANTURE_KILL_BY_PLAYER, nil, drop_dict)
			
			local drop_info = ''
			for _,info in ipairs(drop_dict) do
				drop_info = drop_info..tb_item_template[info[1]].name..'X'..info[2]..' '
			end
			if #drop_info > 0 then
				app:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_ADVENTURE_ROB,{str,self:GetNoticeName(),drop_info})
				self:CallOptResult(OPRATE_TYPE_NEED_NOTICE,NEED_NOTICE_TYPE_ADVENTURE_ROBED,{str,drop_info})
				
			end
		end
		
	elseif SCENED_APPD_ENTER_STAGE_INSTANCE == ntype then
		self:checkStageInstanceTeleport(data)
	elseif SCENED_APPD_ENTER_GROUP_EXP_INSTANCE == ntype then
		-- 是单人进入, 需要进行操作
		if data == 0 then
			local generalId = makeGroupInstanceGeneralId(INSTANCE_SUB_TYPE_GROUP_EXP, {self:GetLevel()})
			self:checkGroupExpMapTeleport(generalId)
		else
			-- 需要所有人同意进入
			local groupId = self:GetGroupId()
			if string.len(groupId) > 0 then
				local groupObj = app.objMgr:getObj(groupId)
				if groupObj then
					groupObj:captainSendChoiseToPlayer(self, INSTANCE_SUB_TYPE_GROUP_EXP, function(playerInfo)
						-- 判断是否激活 是否有次数
						return playerInfo:checkGroupExpAvailable()
					end)
				end
			end
		end
	elseif SCENED_APPD_PASS_STAGE_INSTANCE == ntype then
		self:onPassStageInstance(data)
		
	elseif SCENED_APPD_ENTER_BUY_INSPIRATION == ntype then
		local cost = tb_instance_group_exp[ 1 ].moneyCost
		if data > 0 then
			cost = tb_instance_group_exp[ 1 ].goldCost
		end
		
		if self:costMoneys(MONEY_CHANGE_GROUP_EXP_BUY_INSPIRATION, cost, 1) then
			-- 通知场景服鼓舞
			self:CallScenedDoSomething(APPD_SCENED_INSPIRATION, data)
		end
	elseif SCENED_APPD_ENTER_FACTION_MATCH_INSTANCE ==  ntype then
		self:EnterFactionMatchMap()
	elseif SCENED_APPD_ENTER_GROUP_INSTANCE == ntype then
		local indx = tonumber(str)
		-- 是单人进入, 需要进行操作
		if data == 0 then
			local generalId = makeGroupInstanceGeneralId(INSTANCE_SUB_TYPE_KUAFU_GROUP, {indx})
			self:checkGroupInstanceTeleport(indx, generalId)
		else
			-- 需要所有人同意进入
			local groupId = self:GetGroupId()
			if string.len(groupId) > 0 then
				local groupObj = app.objMgr:getObj(groupId)
				if groupObj then
					groupObj:captainSendChoiseToPlayer(self, indx * 65536 + INSTANCE_SUB_TYPE_KUAFU_GROUP, function(playerInfo)
						-- 判断是否激活 是否有次数
						return playerInfo:checkGroupInstanceAvailable(indx)
					end)
				end
			end
		end
	elseif SCENED_APPD_PASS_GROUP_INSTANCE == ntype then
		
		local id = data
		local first = tonumber(str)
		if first == 0 then
			local instMgr = self:getInstanceMgr()
			instMgr:SubGroupInstanceChallengeCount(1)
		end
		self:SetGroupInstanceClearFlag(id)
		self:AddActiveItem(VITALITY_TYPE_GROUP_INSTANCE)
	elseif SCENED_APPD_PASS_MASS_BOSS_INSTANCE == ntype then
		if self:GetUInt32(PLAYER_INT_FIELD_MASS_BOSS_TIMES) > 0 then
			self:SubUInt32(PLAYER_INT_FIELD_MASS_BOSS_TIMES, 1)
		end
	
	elseif SCENED_APPD_PASS_LOCAL_3V3 == ntype then
		local score = data
		local params = string.split(str, '#')
		local honor  = tonumber(params[ 1 ])
		local result = tonumber(params[ 2 ])
		
		-- 任务
		local questMgr = self:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_JOIN_KUAFU_3V3)
		if isLocal3V3Open(self) then
			self:AddKuafu3v3Score(score)
			if result == 1 then
				self:Kuafu3v3Win()
				questMgr:OnUpdate(QUEST_TARGET_TYPE_WIN_KUAFU_3V3)
			elseif result == -1 then
				self:Kuafu3v3Lose()
			else
				self:AddKuafu3v3TrendInfo()
			end
		end
		
		-- 加荣誉
--		self:AddMoney(MONEY_TYPE_HONOR, MONEY_CHANGE_KUAFU_WORLD_3V3, honor)
	elseif SCENED_APPD_QUEST_MASS_BOSS == ntype then
		self:onUpdatePlayerQuest(QUEST_TARGET_TYPE_JOIN_MASS_BOSS_TIMES, {})
	end
end
