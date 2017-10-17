local protocols = require('share.protocols')


function DoScenedDoSomething(unit, ntype, data, str)
	-- 玩家需要做的
	if unit then
		local unitInfo = UnitInfo:new {ptr = unit}
		unitInfo:DoGetAppdDoSomething(ntype, data, str)
	else
		-- 场景服需要做的 (比如刷野外BOSS什么的)
		DoScenedAppGetAppdDoSomething( ntype, data, str)
	end
end

-- 应用服通知场景服干些什么
function UnitInfo:DoGetAppdDoSomething( ntype, data, str)
	if ntype == APPD_SCENED_RESPAWN then
		self:sceneGoldRespawn()
	elseif ntype == APPD_SCENED_NEAR_BY_CHAT then
		self:chatNearBy(str)
	elseif ntype == APPD_SCENED_ADD_EXP then
		self:AddExp(data)
	elseif ntype == APPD_SCENED_WORLD_BOSS_WAITING then
		self:ToWaitingRoom()
	elseif ntype == APPD_SCENED_WORLD_BOSS_ENTER then
		self:ToWorldBossRoom(data)
	elseif ntype == APPD_SCENED_REMIND_INSTANCE_ENTER then
		self:ToRemindRoom(data, str)
	elseif ntype == APPD_SCENED_TELEPORT then
		self:ToTeleport(str)
	elseif ntype == APPD_SCENED_CHECK_ENTER_FACTION_BOSSDEFENSE then
		self:CheckEnterFactionBossDefense(data)
	elseif ntype == APPD_SCENED_CHECK_ENTER_FACTION_TOWER then
		self:CheckEnterFactionBossTower()
		
	end
end

-- 场景服元宝复活
function UnitInfo:sceneGoldRespawn()
	local mapid = unitLib.GetMapID(self.ptr)
	local map_ptr = unitLib.GetMap(self.ptr)
	local mapInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	
	mapInfo:OnCostRespawn(self)
end


-- 附近聊天
function UnitInfo:chatNearBy(content)
	-- 查询视野范围内的玩家
	local faction_guid = self:GetFactionId()
	local allPlayers = playerLib.GetAllPlayerNearBy(self.ptr)
	for _, player in pairs(allPlayers) do
		local playerInfo = UnitInfo:new {ptr = player}
		if not playerInfo:isDeclineNearMsg() then
			playerInfo:call_send_chat (CHAT_TYPE_CURRENT ,self:GetPlayerGuid() ,0 ,self:GetName() ,self:GetVIP() ,0 ,self:GetLevel() ,self:GetGender() ,content, "", faction_guid)
		end
	end
end

-- 加经验
function UnitInfo:AddExp(exp)
	playerLib.AddExp(self.ptr, exp)
end

-- 传送到等待房间
function UnitInfo:ToWaitingRoom()
	-- 如果不在等待地图 就传送
	local config  = tb_worldboss_waitroom[ 1 ]
	local toMapId = config.mapid
	local toX = randInt(config.rect[ 1 ], config.rect[ 3 ])
	local toY = randInt(config.rect[ 2 ], config.rect[ 4 ])
	playerLib.Teleport(self.ptr, toMapId, toX, toY, 0, "")
end

-- 传送到世界BOSS房间
function UnitInfo:ToWorldBossRoom(line)
	local indx = globalValue:GetTodayWorldBossID()
	print("ToWorldBossRoom", indx)
	local config = tb_worldboss_base[indx]
	local toMapId = config.mapid
	local toX = randInt(config.rect[ 1 ], config.rect[ 3 ])
	local toY = randInt(config.rect[ 2 ], config.rect[ 4 ])
	self:SetLastLine(line)
	
	outFmtDebug("ToWorldBossRoom playerguid = %s, line = %d", self:GetPlayerGuid(), line)
	
	playerLib.Teleport(self.ptr, toMapId, toX, toY, line, "")
end

-- 传送到原地地图房间
function UnitInfo:ToRemindRoom(mapid, gerneralId)
	local posInfo = string.split(gerneralId, "|")
	local toX = tonumber(posInfo[ 4 ])
	local toY = tonumber(posInfo[ 5 ])
	local map_ptr = unitLib.GetMap(self.ptr)
	local mapInfo = Select_Instance_Script(map_id):new{ptr = map_ptr}
	local lineNo = mapInfo:GetMapLineNo()
	gerneralId = gerneralId .. '|' .. lineNo
	playerLib.Teleport(self.ptr, mapid, toX, toY, lineNo, gerneralId)
end

function UnitInfo:ToTeleport(str)
	local tokens = string.split(str,'|')
	
	local mapid = tonumber(tokens[1])
	local x = tonumber(tokens[2])
	local y = tonumber(tokens[3])
	local lineNo = tonumber(tokens[4])
	
	playerLib.Teleport(self.ptr, mapid, x, y, lineNo)
end

function UnitInfo:CheckEnterFactionBossDefense(data)
	-- 玩家必须还活着
	if not self:IsAlive() then
		outFmtError("CheckEnterFactionBossDefense player %s is not alive!", self:GetPlayerGuid())
		return 
	end
	local mapid = unitLib.GetMapID(self.ptr)
	local toMapId = tb_script_base[ 1 ].factionBossDefense[1]
	-- 是否允许传送
	if not self:makeEnterTest(toMapId) and isRiskMap(mapid) == 0 then
--		outFmtError("CheckEnterFactionBossDefense player %s cannot tele to vip map curmapid %d!", self:GetPlayerGuid(), mapid)
		return
	end
	
	--pvp状态下一律不准进
	if self:GetPVPState() then
		self:CallOptResult(OPRATE_TYPE_TELEPORT, TELEPORT_OPRATE_PVP_STATE)
		return
	end
	
	--发到应用服进行进入判断
	playerLib.SendToAppdDoSomething(self.ptr, SCENED_APPD_ENTER_FACTION_BOSSDEFENSE_INSTANCE, data, "")
end

function UnitInfo:CheckEnterFactionBossTower()
	-- 玩家必须还活着
	if not self:IsAlive() then
		outFmtError("CheckEnterFactionBossDefense player %s is not alive!", self:GetPlayerGuid())
		return 
	end
	local mapid = unitLib.GetMapID(self.ptr)
	local toMapId = tb_script_base[ 1 ].factionTower[1]
	-- 是否允许传送
	if not self:makeEnterTest(toMapId) and isRiskMap(mapid) == 0 and tb_map[mapid].inst_sub_type ~= tb_map[toMapId].inst_sub_type then
--		outFmtError("CheckEnterFactionBossDefense player %s cannot tele to vip map curmapid %d!", self:GetPlayerGuid(), mapid)
		return
	end
	
	--pvp状态下一律不准进
	if self:GetPVPState() then
		self:CallOptResult(OPRATE_TYPE_TELEPORT, TELEPORT_OPRATE_PVP_STATE)
		return
	end
	
	--发到应用服进行进入判断
	playerLib.SendToAppdDoSomething(self.ptr, SCENED_APPD_ENTER_FACTION_TOWER_INSTANCE, 0, "")
end



----------------------------------------场景服需要做的-----------------------------------------------
function DoScenedAppGetAppdDoSomething( ntype, data, str)
	-- 场景服清理野外BOSS
	if ntype == APPD_SCENED_CLEAR_FIELD_BOSS then
		OnClearFieldBoss()
	-- 场景服刷新野外
	elseif ntype == APPD_SCENED_REBORN_FIELD_BOSS then
		OnRebornFieldBoss()
	elseif ntype == APPD_SCENED_FIGHT_WORLD_BOSS then
		OnFightWorldBoss(data)
	elseif ntype == APPD_SCENED_WORLD_BOSS_END then
		OnWorldBossEnd()
	elseif ntype == APPD_SCENED_MASS_BOSS_REBORN then
		onMassBossReborn(data)
	end
end

-- 全局变量清理野外BOSS
function OnClearFieldBoss()
	outFmtInfo("====================== OnClearFieldBoss")
	for mapid, _ in pairs(tb_field_boss) do
		for lineNo = 1, MAX_DEFAULT_LINE_COUNT do
			globalValue:ResetFieldBoss(mapid, lineNo)
		end
	end
end

-- 全局变量刷新野外BOSS
function OnRebornFieldBoss()
	outFmtInfo("******************** OnRebornFieldBoss")
	for mapid, _ in pairs(tb_field_boss) do
		for lineNo = 1, MAX_DEFAULT_LINE_COUNT do
			globalValue:BornFieldBoss(mapid, lineNo)
		end
	end
end

-- 进入战斗房间
function OnFightWorldBoss(rooms)
	-- 随机BOSS
	globalValue:RandomTodayWorldBossID()
	-- 设置战斗等待状态
	globalValue:SetWorldBossState(WORLD_BOSS_PROCESS_BORN)
	-- 每个房间先置空
	globalValue:UnSetWorldBossEndInLine()
	-- 设置房间数
	globalValue:SetTodayWorldBossRoom(rooms)
end

-- 世界BOSS结束
function OnWorldBossEnd()
	globalValue:SetWorldBossState(WORLD_BOSS_PROCESS_TYPE_FINISH)
	--------------------------- 结束以后的处理--------------------------
	-- BOSS是否升级
	DoIfBOSSLevelUp()
	-- 每个房间先置空
	globalValue:UnSetWorldBossEndInLine()
	-- 看看是否需要生成下一阶段的BOSS
	globalValue:RandomWorldBossIfNextStep()
end

