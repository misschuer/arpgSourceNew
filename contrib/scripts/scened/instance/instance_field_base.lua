InstanceFieldBase = class("InstanceFieldBase", Instance_base)

InstanceFieldBase.Name = "InstanceFieldBase"
InstanceFieldBase.player_auto_respan = 10
InstanceFieldBase.REFRESH_CREATURE_INTERNAL = 5000	--5s���һ��
InstanceFieldBase.Treasure_Entry = 7

function InstanceFieldBase:ctor(  )
	
end

--��ʼ���ű�����
function InstanceFieldBase:OnInitScript(  )
	Instance_base.OnInitScript(self) --���û���
	
	--���bossˢ����
	if self:IsFieldBossMap() then
		mapLib.DelTimer(self.ptr, 'OnTimer_CheckRefresh')
		mapLib.AddTimer(self.ptr, 'OnTimer_CheckRefresh', self.REFRESH_CREATURE_INTERNAL)
	end
end

-- �Ƿ���Ұ��bossˢ�µ�ͼ
function InstanceFieldBase:IsFieldBossMap()
	local mapid = self:GetMapId()
	local lineNo = self:GetMapLineNo()
	
	return tb_field_boss[mapid] and lineNo > 0 and lineNo <= MAX_DEFAULT_LINE_COUNT
end


--����BOSS�ͱ���
function InstanceFieldBase:OnClear()
	-- �Ƴ�boss�����
	local bossName = self:GetBossAliasName()
	self:RemoveIfExist(bossName)
	
	-- �Ƴ����������
	mapLib.RemoveGameObjectByEntry(self.ptr, self.Treasure_Entry)
end

-- �Ƴ�
function InstanceFieldBase:RemoveIfExist(aliasName)
	local creature = mapLib.AliasCreature(self.ptr, aliasName)
	if creature then
		creatureLib.RemoveMonster(creature)
	end
end

-- �õ���������
function InstanceFieldBase:GetTreaAliasName()
	local mapid = self:GetMapId()
	local lineNo = self:GetMapLineNo()
	
	return string.format("FBT%d_%d", mapid, lineNo)
end

-- �õ�BOSS����
function InstanceFieldBase:GetBossAliasName()
	local mapid = self:GetMapId()
	local lineNo = self:GetMapLineNo()
	
	return string.format("BOSS%d_%d", mapid, lineNo)
end

--��ʱ���ˢ��
function InstanceFieldBase:OnTimer_CheckRefresh()
	local timenow = os.time()
	
	local mapid = self:GetMapId()
	local lineNo = self:GetMapLineNo()
	
	-- �Ƿ��Ѿ�����
	if globalValue:IsFieldBossFinish(mapid, lineNo) then
		return true
	end
	
	-- �Ƿ�ʼ����ʱ
	if globalValue:IsFieldBossCountDown(mapid, lineNo) then
		self:OnClear()
		return true
	end

	-- �Ƿ�ˢ��BOSS
	if globalValue:IsFieldBossBorn(mapid, lineNo) then
		-- �ж�ʱ�䵽��û��
		local bossName = self:GetBossAliasName()
		local boss = mapLib.AliasCreature(self.ptr, bossName)
		if not boss then
			local bossConfig = tb_field_boss[mapid]
			local entry = bossConfig.entry
			local config = tb_creature_template[entry]
			local creature = mapLib.AddCreature(self.ptr, {
					templateid = entry, x = bossConfig.bossPosi[ 1 ], y = bossConfig.bossPosi[ 2 ], 
					active_grid = true, alias_name = bossName, ainame = "AI_FieldBoss", npcflag = {}
				}
			)
			
			if creature then
				local creatureInfo = UnitInfo:new{ptr = creature}
				-- ��ʶΪboss��
				creatureInfo:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
			end
			app:CallOptResult(self.ptr, OPERTE_TYPE_FIELD_BOSS, FIELD_BOSS_OPERTE_BOSS_BORN, {config.name, tb_map[mapid].name})
		end
		
		return true
	end

	-- �Ƿ��Ǳ������
	if globalValue:IsFieldBossTreasureOccur(mapid, lineNo) then
		local posx = tb_field_boss[mapid].bossPosi[ 1 ]
		local posy = tb_field_boss[mapid].bossPosi[ 2 ]
		self:AddTreasure(posx, posy)
		
		return true
	end
	
	return true
end


-- �ӱ���
function InstanceFieldBase:OnTimer_AddTreasure(x, y)
	local gameObject = mapLib.GetGameObjectByEntry(self.ptr, self.Treasure_Entry)
	if not gameObject then
		mapLib.AddGameObject(self.ptr, self.Treasure_Entry, x, y, GO_GEAR_STATUS_END)
	end
	-- false��ʾ��ʱˢ��������
	return false
end



-- �ӱ���
function InstanceFieldBase:AddTreasure(x, y, last)
	last = last or 0
	local gameObject = mapLib.GetGameObjectByEntry(self.ptr, self.Treasure_Entry)
	if not gameObject then
		-- �ӱ���
		if last <= 0 then
			self:OnTimer_AddTreasure(x, y)
		else
			-- ���Լ��Ӹ��ӳ�
			mapLib.AddTimer(self.ptr, 'OnTimer_AddTreasure', last, x, y)
		end
		
			
		local mapid = self:GetMapId()
		local lineNo = self:GetMapLineNo()
		local countdown = globalValue:GetProtectCooldown(mapid, lineNo)
		
		if countdown > 0 then
			-- ���䱣������ʱ
			mapLib.AddTimer(self.ptr, 'OnTimer_Priority', countdown * 1000)
		end
	end
end

function InstanceFieldBase:OnTimer_Priority()
	app:CallOptResult(self.ptr, OPERTE_TYPE_FIELD_BOSS, FIELD_BOSS_OPERTE_PROTECT, {tb_gameobject_template[self.Treasure_Entry].name})
	return false
end

--����ұ����ɱ��ʱ����
function InstanceFieldBase:OnPlayerKilled(player, killer)
	local playerInfo = UnitInfo:new {ptr = player}
	local killername = binLogLib.GetStr(killer, BINLOG_STRING_FIELD_NAME)
	self:OnSendDeathInfo(playerInfo, killername, '')
	
	return 0
end
	
-- ����ұ�����ɱ��
function InstanceFieldBase:OnPlayerKilledByMonster(player, killer)
	local playerInfo = UnitInfo:new {ptr = player}
	local killername = binLogLib.GetStr(killer, BINLOG_STRING_FIELD_NAME)
	self:OnSendDeathInfo(playerInfo, killername, '')
	
	return 0
end

--����������󴥷�()
function InstanceFieldBase:OnPlayerDeath(player)
	
end

-- ʹ����Ҫ���������㲥����Ϸ����
function InstanceFieldBase:OnUseBroadCastGameObject(playerInfo, gameObjectInfo)
	
	local entry = gameObjectInfo:GetEntry()
	if entry ~= self.Treasure_Entry then
		return
	end
	
	local mapid  = self:GetMapId()
	local lineNo = self:GetMapLineNo()
	
	-- �����Ѿ�������
	if not globalValue:IsFieldBossTreasureOccur(mapid, lineNo) then
		return
	end
	
	-- �����ȱ����в��ܲɼ�
	if not globalValue:CanPickTreasure(mapid, lineNo, playerInfo:GetPlayerGuid()) then
		return
	end
	
	-- �Ѿ������ڲɼ�
	local openguid = mapLib.GetOnOpenGuid(self.ptr)
	if openguid ~= "" then
		-- �������ڱ����˲ɼ�
		return
	end
	
	local seconds = tb_gameobject_template[entry].time
	-- ���òɼ�������
	self:OnProcess(playerInfo, seconds, 'OnTimer_PickingTreasure')
	mapLib.OnOpenTreasure(self.ptr, playerInfo:GetPlayerGuid())
end


-- �ɼ���
function InstanceFieldBase:OnProcess(playerInfo, seconds, callback)
	local gameObject = mapLib.GetGameObjectByEntry(self.ptr, self.Treasure_Entry)
	local gameObjectInfo = UnitInfo:new {ptr = gameObject}
	gameObjectInfo:SetProcessTime(os.time() + seconds)
	gameObjectInfo:SetProcessSeconds(seconds)
	gameObjectInfo:SetPickedName(playerInfo:GetName())
	mapLib.AddTimer(self.ptr, callback, seconds * 1000, playerInfo.ptr)
end

-- ���ӿ������
function InstanceFieldBase:OnTimer_PickingTreasure(player)
	local mapid  = self:GetMapId()
	local lineNo = self:GetMapLineNo()
	globalValue:FieldBossTreasurePicked(mapid, lineNo)
	
	local openguid = mapLib.GetOnOpenGuid(self.ptr)	
	mapLib.OnOpenTreasure(self.ptr, "")
	-- �Ƴ���ʱ��
	mapLib.DelTimer(self.ptr, 'OnTimer_Priority')
	
	-- ɾ������
	mapLib.RemoveGameObjectByEntry(self.ptr, self.Treasure_Entry)
	
	-- ������Ϣ
	-- ʰȡ����
	local playerInfo = UnitInfo:new {ptr = player}
	local dropId = GetRewardIfGenderSensitive(tb_field_boss[mapid].dropTable, playerInfo:GetGender())
	local dict = {}
	DoRandomDropTable({dropId}, dict)
	PlayerAddRewards(player, dict)
	local rewards = {}
	for entry, _ in pairs(dict) do
		local itemConfig = tb_item_template[entry]
		for _, record in pairs(itemConfig.records) do
			if record == ITEM_RECORD_MAP then
				local itemName = GetColordItemName(entry)
				table.insert(rewards, itemName)
			end
		end
	end
	
	local reward = string.join(",", rewards)
	local playerInfo = UnitInfo:new {ptr = player}
	local playerName = ToShowName(playerInfo:GetName())
	app:CallOptResult(self.ptr, OPERTE_TYPE_FIELD_BOSS, FIELD_BOSS_OPERTE_PICKED, {playerName, tb_gameobject_template[self.Treasure_Entry].name, reward})
	
	return false
end

-- ���ӿ������
function InstanceFieldBase:OnDisruptPicking()
	mapLib.DelTimer(self.ptr, 'OnTimer_PickingTreasure')
	mapLib.OnOpenTreasure(self.ptr, "")
	
	local gameObject = mapLib.GetGameObjectByEntry(self.ptr, self.Treasure_Entry)
	local gameObjectInfo = UnitInfo:new {ptr = gameObject}
	-- �óɹ�ȥʱ��
	gameObjectInfo:SetProcessTime(os.time() - 2)
	gameObjectInfo:SetPickedName("")
end

-- �����
function InstanceFieldBase:OnDisrupt(killer)
	self:OnDisruptPicking()
end

-- ������ƶ���
function InstanceFieldBase:OnPlayerAfterMove(player)
	self:OnPlayerCancelPicking(player)
end

--��Ծǰ��Ҫ������߼�
function InstanceFieldBase:OnStartJump(playerInfo)
	self:OnPlayerCancelPicking(playerInfo.ptr)
end

--�ͷż�����Ҫ������߼�
function InstanceFieldBase:OnSpell(player)
	self:OnPlayerCancelPicking(player)
end

-- �Զ�ȡ���ɼ�
function InstanceFieldBase:OnPlayerCancelPicking(player)
	local openguid = mapLib.GetOnOpenGuid(self.ptr)
	local myguid = playerLib.GetPlayerGuid(player)
	if myguid and openguid ~= myguid then
		return
	end
	self:OnDisruptPicking()
end

--������뿪ʱ����
function InstanceFieldBase:OnLeavePlayer( player, is_offline)
	
	-- �뿪���
	local openguid = mapLib.GetOnOpenGuid(self.ptr)
	local playerInfo = UnitInfo:new{ptr = player}
	if playerInfo:GetPlayerGuid() == openguid then
		self:OnDisruptPicking(playerInfo)
	end
end

-------------------------Ұ��boss---------------------------
AI_FieldBoss = class("AI_FieldBoss", AI_Base)
AI_FieldBoss.ainame = "AI_FieldBoss"

--����
function AI_FieldBoss:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local bossInfo = UnitInfo:new{ptr = owner}
	local unitInfo = UnitInfo:new{ptr = killer_ptr}
	
	local instanceInfo = InstanceFieldBase:new{ptr = map_ptr}
	local mapid  = instanceInfo:GetMapId()
	local lineNo = instanceInfo:GetMapLineNo()
	local entry = bossInfo:GetEntry()
	
	globalValue:FieldBossDamageDeal(mapid, lineNo, 0)
	-- ����˺���ߵ�guid
	local guid = mapLib.GetMaxinumFieldBossDamage(map_ptr)
	-- ���BOSS�˺�
	mapLib.ClearFieldBossDamage(map_ptr)
	
	-- ����ǹ�����ҹ�����
	if unitInfo:GetTypeID() == TYPEID_UNIT then
		local host = creatureLib.GetMonsterHost(killer_ptr)
		if host then
			unitInfo = UnitInfo:new {ptr = host}
		end
	end
	
	-- BOSS����
	globalValue:FieldBossKilled(mapid, lineNo, guid, unitInfo:GetName())
	local playerName = ToShowName(unitInfo:GetName())
	app:CallOptResult(instanceInfo.ptr, OPERTE_TYPE_FIELD_BOSS, FIELD_BOSS_OPERTE_BOSS_KILL, {tb_creature_template[entry].name, playerName, tb_gameobject_template[InstanceFieldBase.Treasure_Entry].name})
	
	-- �ӱ���
	local posx, posy = unitLib.GetPos(owner)
	instanceInfo:AddTreasure(posx, posy, 500)
	
	return 0
end

-- TODO:��Ҫ�޸�, DamageTaken �ž�ȷ
-- �ܵ��˺���
function AI_FieldBoss:DamageDeal( owner, unit, damage)
	local bossInfo = UnitInfo:new{ptr = owner}

	local currHealth = bossInfo:GetHealth()
	local maxHealth  = bossInfo:GetMaxHealth()
	
	local map_ptr = unitLib.GetMap(owner)
	local instanceInfo = InstanceFieldBase:new{ptr = map_ptr}
	local mapid  = instanceInfo:GetMapId()
	local lineNo = instanceInfo:GetMapLineNo()
	
	globalValue:FieldBossDamageDeal(mapid, lineNo, currHealth * 100 / maxHealth)
	
	if damage > 0 then
		-- ����ǹ�����ҹ�����
		if GetUnitTypeID(unit) == TYPEID_UNIT then
			unit = creatureLib.GetMonsterHost(unit)
		end
		if unit then
			local unitInfo = UnitInfo:new {ptr = unit}
			local guid = unitInfo:GetPlayerGuid()
			mapLib.AddFiledBossDamage(map_ptr, guid, damage)
			-- �μ�Ұ��BOSS
			playerLib.SendToAppdDoSomething(unit, SCENED_APPD_JOIN_FIELD_BOSS, mapid)
		end
	else
		mapLib.ClearFieldBossDamage(map_ptr)
	end
end

return InstanceFieldBase