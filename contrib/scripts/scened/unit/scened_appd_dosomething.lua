local protocols = require('share.protocols')


function DoScenedDoSomething(unit, ntype, data, str)
	-- �����Ҫ����
	if unit then
		local unitInfo = UnitInfo:new {ptr = unit}
		unitInfo:DoGetAppdDoSomething(ntype, data, str)
	else
		-- ��������Ҫ���� (����ˢҰ��BOSSʲô��)
		DoScenedAppGetAppdDoSomething( ntype, data, str)
	end
end

-- Ӧ�÷�֪ͨ��������Щʲô
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
	elseif ntype == APPD_SCENED_INSPIRATION then
		self:playerInspire(data)
	elseif APPD_SCENED_RESETDAILY == ntype then
		-- ɾ�����ڴ������������BUFF�ȵ�
		local buffEffectId = tb_mass_boss_base[ 1 ].monsterForbid
		local buffEffectConfig = tb_buff_effect[buffEffectId]
		unitLib.RemoveBuff(self.ptr, buffEffectConfig.buff_id)
	end
end

-- ������Ԫ������
function UnitInfo:sceneGoldRespawn()
	local mapid = unitLib.GetMapID(self.ptr)
	local map_ptr = unitLib.GetMap(self.ptr)
	local mapInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	
	mapInfo:OnCostRespawn(self)
end


-- ��������
function UnitInfo:chatNearBy(content)
	-- ��ѯ��Ұ��Χ�ڵ����
	local faction_guid = self:GetFactionId()
	local allPlayers = playerLib.GetAllPlayerNearBy(self.ptr)
	for _, player in pairs(allPlayers) do
		local playerInfo = UnitInfo:new {ptr = player}
		if not playerInfo:isDeclineNearMsg() then
			playerInfo:call_send_chat (CHAT_TYPE_CURRENT ,self:GetPlayerGuid() ,0 ,self:GetName() ,self:GetVIP() ,0 ,self:GetLevel() ,self:GetGender() ,content, "", faction_guid)
		end
	end
end

-- �Ӿ���
function UnitInfo:AddExp(exp)
	playerLib.AddExp(self.ptr, exp)
end

-- ���͵��ȴ�����
function UnitInfo:ToWaitingRoom()
	-- ������ڵȴ���ͼ �ʹ���
	local config  = tb_worldboss_waitroom[ 1 ]
	local toMapId = config.mapid
	local toX = randInt(config.rect[ 1 ], config.rect[ 3 ])
	local toY = randInt(config.rect[ 2 ], config.rect[ 4 ])
	playerLib.Teleport(self.ptr, toMapId, toX, toY, 0, "")
end

-- ���͵�����BOSS����
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

-- ���͵�ԭ�ص�ͼ����
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
	-- ��ұ��뻹����
	if not self:IsAlive() then
		outFmtError("CheckEnterFactionBossDefense player %s is not alive!", self:GetPlayerGuid())
		return 
	end
	local mapid = unitLib.GetMapID(self.ptr)
	local toMapId = tb_script_base[ 1 ].factionBossDefense[1]
	-- �Ƿ�������
	if not self:makeEnterTest(toMapId) and isRiskMap(mapid) == 0 then
--		outFmtError("CheckEnterFactionBossDefense player %s cannot tele to vip map curmapid %d!", self:GetPlayerGuid(), mapid)
		return
	end
	
	--pvp״̬��һ�ɲ�׼��
	if self:GetPVPState() then
		self:CallOptResult(OPRATE_TYPE_TELEPORT, TELEPORT_OPRATE_PVP_STATE)
		return
	end
	
	--����Ӧ�÷����н����ж�
	playerLib.SendToAppdDoSomething(self.ptr, SCENED_APPD_ENTER_FACTION_BOSSDEFENSE_INSTANCE, data, "")
end

function UnitInfo:CheckEnterFactionBossTower()
	-- ��ұ��뻹����
	if not self:IsAlive() then
		outFmtError("CheckEnterFactionBossDefense player %s is not alive!", self:GetPlayerGuid())
		return 
	end
	local mapid = unitLib.GetMapID(self.ptr)
	local toMapId = tb_script_base[ 1 ].factionTower[1]
	-- �Ƿ�������
	if not self:makeEnterTest(toMapId) and isRiskMap(mapid) == 0 and tb_map[mapid].inst_sub_type ~= tb_map[toMapId].inst_sub_type then
--		outFmtError("CheckEnterFactionBossDefense player %s cannot tele to vip map curmapid %d!", self:GetPlayerGuid(), mapid)
		return
	end
	
	--pvp״̬��һ�ɲ�׼��
	if self:GetPVPState() then
		self:CallOptResult(OPRATE_TYPE_TELEPORT, TELEPORT_OPRATE_PVP_STATE)
		return
	end
	
	--����Ӧ�÷����н����ж�
	playerLib.SendToAppdDoSomething(self.ptr, SCENED_APPD_ENTER_FACTION_TOWER_INSTANCE, 0, "")
end

function UnitInfo:playerInspire(category)
	local mapid = unitLib.GetMapID(self.ptr)
	local map_ptr = unitLib.GetMap(self.ptr)
	local mapInfo = Select_Instance_Script(mapid):new{ptr = map_ptr}
	
	mapInfo:inspire(self, category)
end


----------------------------------------��������Ҫ����-----------------------------------------------
function DoScenedAppGetAppdDoSomething( ntype, data, str)
	-- ����������Ұ��BOSS
	if ntype == APPD_SCENED_CLEAR_FIELD_BOSS then
		OnClearFieldBoss()
	-- ������ˢ��Ұ��
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

-- ȫ�ֱ�������Ұ��BOSS
function OnClearFieldBoss()
	outFmtDebug("====================== OnClearFieldBoss")
	for mapid, _ in pairs(tb_field_boss) do
		for lineNo = 1, MAX_DEFAULT_LINE_COUNT do
			globalValue:ResetFieldBoss(mapid, lineNo)
		end
	end
end

-- ȫ�ֱ���ˢ��Ұ��BOSS
function OnRebornFieldBoss()
	outFmtDebug("******************** OnRebornFieldBoss")
	for mapid, _ in pairs(tb_field_boss) do
		for lineNo = 1, MAX_DEFAULT_LINE_COUNT do
			globalValue:BornFieldBoss(mapid, lineNo)
		end
	end
end

-- ����ս������
function OnFightWorldBoss(rooms)
	-- ���BOSS
	globalValue:RandomTodayWorldBossID()
	-- ����ս���ȴ�״̬
	globalValue:SetWorldBossState(WORLD_BOSS_PROCESS_BORN)
	-- ÿ���������ÿ�
	globalValue:UnSetWorldBossEndInLine()
	-- ���÷�����
	globalValue:SetTodayWorldBossRoom(rooms)
end

-- ����BOSS����
function OnWorldBossEnd()
	globalValue:SetWorldBossState(WORLD_BOSS_PROCESS_TYPE_FINISH)
	--------------------------- �����Ժ�Ĵ���--------------------------
	-- BOSS�Ƿ�����
	DoIfBOSSLevelUp()
	-- ÿ���������ÿ�
	globalValue:UnSetWorldBossEndInLine()
	-- �����Ƿ���Ҫ������һ�׶ε�BOSS
	globalValue:RandomWorldBossIfNextStep()
end

