InstanceWorldBoss = class("InstanceWorldBoss", InstanceInstBase)
local protocols = require('share.protocols')

InstanceWorldBoss.Name = "InstanceWorldBoss"
InstanceWorldBoss.player_auto_respan = 5

-- ��ʤ��־ (0:δ����, 1:����ʤ��, 2:����ʧ��)
InstanceWorldBoss.FLAG_WIN = 1
InstanceWorldBoss.FLAG_LOSE = 2
InstanceWorldBoss.WORLD_BOSS_NAME = "WORLD_BOSS"

-- �ж�BOSS�Ƿ���Ҫ����
function DoIfBOSSLevelUp()
	
	local num = 0
	local rooms = globalValue:GetTodayWorldBossRoom()
	for i = 1, rooms do
		if globalValue:IsWorldBossEndInLine(i) then
			num = num + 1
		end
	end

	-- BOSS��Ҫ������
	if num * 2 > rooms then
		globalValue:AddWorldBossLevel()
	end
end

function InstanceWorldBoss:ctor(  )
	
end


--��ʼ���ű�����
function InstanceWorldBoss:OnInitScript()
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	Instance_base.OnInitScript(self) --���û���
	
	self:OnTaskStart()
	self:AddCountDown()
	
	-- ˢ��BOSS ��ʱ��
	mapLib.AddTimer(self.ptr, 'OnTimer_RefreshBoss', tb_worldboss_time[ 1 ].waitCountdown * 1000)
	
	-- ˢ������ ��ʱ��
	mapLib.AddTimer(self.ptr, 'OnTimer_UpdateRank', 1000)
end

function InstanceWorldBoss:SetBossHP(val)
	self:SetUInt32(MAP_MASS_BOSS_INT_FIELD_MAX_HP, val)
end

function InstanceWorldBoss:GetBossHP()
	return self:GetUInt32(MAP_MASS_BOSS_INT_FIELD_MAX_HP)
end

-- ���ʽ��ʼ
function InstanceWorldBoss:OnTaskStart()
	local waitTime = tb_worldboss_time[ 1 ].waitCountdown
		
	self:SetUInt32(WORLDBOSS_FIELDS_BORN_TIME, waitTime)
	
	-- ����ʼʱ��
	self:SetMapStartTime(os.time() + waitTime)
		
	local timestamp = os.time() + waitTime + tb_worldboss_time[ 1 ].time_last * 60
	-- ���������ʱ��
	self:SetMapQuestEndTime(timestamp)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp)
end

--������״̬�����仯ʱ�䴥��
function InstanceWorldBoss:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceDoujiantai.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end


function InstanceWorldBoss:AddCountDown()
	local timestamp = os.time() + tb_worldboss_time[ 1 ].waitCountdown
	self:SetMapStartTime(timestamp)
	self:AddTimeOutCallback("countdown", timestamp)
end

-- ����ʱ����
function InstanceWorldBoss:countdown()
	-- ����ˢ�¶�ʱ��
	mapLib.AddTimer(self.ptr, 'OnBuffRefresh', tb_worldboss_time[ 1 ].interval * 1000)
end

-- ˢ��buff
function InstanceWorldBoss:OnBuffRefresh()
	-- ����ˢ�´���
	local times = self:GetMapReserveValue1()
	if times < tb_worldboss_time[ 1 ].times then
		self:SetMapReserveValue1(times+1)
	end
	
	-- ˢ�°�ԭ������ɾ��
	local allGameObjects = mapLib.GetAllGameObject(self.ptr)
	for _, gameobject in pairs(allGameObjects) do
		mapLib.RemoveWorldObject(self.ptr, gameobject)
	end
	
	-- ˢ���µ�
	local indice = GetRandomIndexTable(#tb_worldboss_time[ 1 ].buffRandomPos, tb_worldboss_time[ 1 ].randomCount)
	for i = 1, #indice do
		local indx = indice[ i ]
		local pos = tb_worldboss_time[ 1 ].buffRandomPos[indx]
		local buffIndx = randInt(1, #tb_worldboss_buff)
		local entry =  tb_worldboss_buff[buffIndx].gameobject_id
		mapLib.AddGameObject(self.ptr, entry, pos[ 1 ], pos[ 2 ], GO_GEAR_STATUS_END)
	end
	
	app:CallOptResult(self.ptr, OPRATE_TYPE_ATHLETICS, ATHLETICS_OPERATE_BUFF_OCCUR)
	
	return self:GetMapReserveValue1() < tb_worldboss_time[ 1 ].times
end


--ʹ����Ϸ����֮ǰ
--����1�Ļ��ͼ���ʹ����Ϸ���󣬷���0�Ļ��Ͳ�ʹ��
function InstanceWorldBoss:OnBeforeUseGameObject(user, go, go_entryid, posX, posY)
	-- ����Ѿ����� �Ͳ��ܼ���
	if unitLib.HasBuff(user, BUFF_INVINCIBLE) then
		return 0
	end
	
	if Script_Gameobject_Pick_Check(user, go_entryid, posX, posY) then
		return 1
	end
	return 0
end

--ʹ����Ϸ����
--����1�Ļ��ɹ�ʹ����Ϸ���󣬷���0�Ļ�ʹ�ò��ɹ�
function InstanceWorldBoss:OnUseGameObject(user, go, go_entryid, posX, posY)
	-- �ж϶�Ӧ��������buff
	for _, obj in ipairs(tb_worldboss_buff) do
		if obj.gameobject_id == go_entryid then
			local effectId = obj.buffEffect
			local buffId = tb_buff_effect[effectId].buff_id
			local duration = tb_buff_effect[effectId].duration
			SpelladdBuff(user, buffId, user, effectId, duration)
			break
		end
	end
	
	-- ��Ҫɾ������
	mapLib.RemoveWorldObject(self.ptr, go)
	
	return 1	
end

-- ����BOSS������
function InstanceWorldBoss:IsEnd()
	local lineNo = self:GetMapLineNo()
	return globalValue:IsWorldBossEnd() or globalValue:IsWorldBossEndInLine(lineNo)
end

-- ˢ��BOSS
function InstanceWorldBoss:OnTimer_RefreshBoss()
	if globalValue:IsWorldBossBorn() then
		-- ˢBOSS		
		local boss = mapLib.AliasCreature(self.ptr, InstanceWorldBoss.WORLD_BOSS_NAME)
		if not boss then
			local indx   = globalValue:GetTodayWorldBossID()
			local wbconfig = tb_worldboss_base[indx]
			local entry  = wbconfig.entry
			local born   = wbconfig.born
		
			local config = tb_creature_template[entry]
			local creature = mapLib.AddCreature(self.ptr, {
					templateid = entry, x = born[ 1 ], y = born[ 2 ], active_grid = true, 
					alias_name = InstanceWorldBoss.WORLD_BOSS_NAME, ainame = config.ainame, npcflag = {}
				}
			)
			
			if creature then
				local creatureInfo = UnitInfo:new{ptr = creature}
				-- ��ʶΪboss��
				creatureInfo:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
				self:SetBossHP(creatureInfo:GetMaxHealth())
			end
		end
	end

	return false
end

-- ��ʼ��������Ϣ
function InstanceWorldBoss:InitCreatureInfo(creature_ptr, bRecal, mul)
	local level = globalValue:GetWorldBossLevel()
	mul = 1 + level * 0.2
	Instance_base.InitCreatureInfo(self, creature_ptr, bRecal, mul)
end

-- ������������
function InstanceWorldBoss:OnTimer_UpdateRank()
	mapLib.NotifyAllRankUpdate(self.ptr)
	
	-- ����BOSS����
	if self:IsEnd() then
		mapLib.ResetBossDamageRank(self.ptr)
		-- ������ǰ����ʱ��
		-- self:SetMapEndTime(os.time() + 20)
		return false
	end
	
	return true
end

function InstanceWorldBoss:OnLeavePlayer(player, isOffline)
	InstanceInstBase.OnLeavePlayer(self, player, isOffline)
end
--��Ҽ����ͼ
function InstanceWorldBoss:OnJoinPlayer(player)
	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻�������ֱ�ӵ���ȥ
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		return
	end
	
	-- ����ʱ�䵽�Ͳ��ý���
	if os.time() >= self:GetMapQuestEndTime() or self:IsEnd() then
		mapLib.ExitInstance(self.ptr, player)
		return
	end
end

function InstanceWorldBoss:GetDeadTimes(playerInfo)
	local cnt = mapLib.GetDeadTimes(self.ptr, playerInfo:GetPlayerGuid())
	cnt = cnt or 0
	
	return cnt
end

-- �����������
function InstanceWorldBoss:OnPlayerDeath(player)
	local playerInfo = UnitInfo:new{ptr = player}
	mapLib.AddDeadTimes(self.ptr, playerInfo:GetPlayerGuid())
end


--AI_WorldBoss
-------------------------����boss---------------------------
AI_WorldBoss = class("AI_WorldBoss", AI_Base)
AI_WorldBoss.ainame = "AI_WorldBoss"

--����
function AI_WorldBoss:JustDied( map_ptr,owner,killer_ptr )
	outFmtDebug("============================ world BOSS was dead")
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local instanceInfo = InstanceWorldBoss:new{ptr = map_ptr}
	local mapid  = instanceInfo:GetMapId()
	local lineNo = instanceInfo:GetMapLineNo()
	
	-- ����״̬
	globalValue:SetWorldBossEndInLine(lineNo)
	instanceInfo:SetMapEndTime(os.time() + 12)
	instanceInfo:SetMapState(instanceInfo.STATE_FINISH)
	
	local exist = {}
	local allPlayers = mapLib.GetAllPlayer(map_ptr)
	for _, player in pairs(allPlayers) do
		local player_guid = GetPlayerGuid(player)
		exist[player_guid] = 1
	end
	
	-- �������� ���ʼ�
	local ranklist = mapLib.GetBossDamageRank(map_ptr)
	local indx = 1
	for i = 1, #ranklist do
		local range = tb_worldboss_rank_reward[indx].range
		-- ������������������
		if range[ 2 ] > 0 and range[ 2 ] < i then
			indx = indx + 1
		end
		
		local playerGuid = ranklist[ i ]
		--����Ӧ�÷�������
		local player = mapLib.GetPlayerByPlayerGuid(map_ptr, playerGuid)
		local vip = 0
		local level = 0
		local playerInfo = nil
		if player then
			playerInfo = UnitInfo:new {ptr = player}
			vip = playerInfo:GetVIP()
			level = playerInfo:GetLevel()
		else
			level, vip = mapLib.GetBossDamageRankPlayerInfo(map_ptr, i)
		end
		
		local rankRewardConfig = tb_worldboss_rank_reward[indx]
		local items = raiseItem(rankRewardConfig.serverRewards, tb_vip_base[vip].worldbossReward)
		local factor = rankRewardConfig.factor / 100
		
		
		local lrc = tb_worldboss_rank_level_reward[ 1 ]
		for k = 1, #tb_worldboss_rank_level_reward do
			local levelRewardConfig = tb_worldboss_rank_level_reward[ k ]
			if levelRewardConfig.levelRange[ 1 ] <= level and level <= levelRewardConfig.levelRange[ 2 ] then
				lrc = levelRewardConfig
				break
			end
		end
		
		items = string.format("%s,%d,%d", items, lrc.serverRewards[ 1 ], math.floor(factor * lrc.serverRewards[ 2 ] * (1 + tb_vip_base[vip].worldbossReward / 100)))
		
		local mailInfo = {items, rankRewardConfig.name, rankRewardConfig.desc, GIFT_PACKS_TYPE_WORLD_BOSS}
		local str = string.join("|", mailInfo)
		
		if player then
			playerLib.SendToAppdDoSomething(player, SCENED_APPD_ADD_MAIL, 0, str)
			if exist[playerInfo:GetPlayerGuid()] then
				local params = string.split(items, ',')
				local dict = {}
				for i = 1, #params, 2 do
					local entry = tonumber(params[ i ])
					local count = tonumber(params[i+1])
					if entry and count then
						dict[entry] = count
					end
				end
				local list = Change_To_Item_Reward_Info(dict, true)
				playerInfo:call_send_instance_result(instanceInfo:GetMapState(), instanceInfo.exit_time, list, INSTANCE_SUB_TYPE_WORLD_BOSS, '')
			end
		else
			playerLib.SendToAppdAddOfflineMail(playerGuid, str)
		end
	end
	
	return 0
end

function raiseItem(items, extra)
	extra = extra or 0
	if extra == 0 then
		return items
	end
	local params = string.split(items, ',')
	local list = {}
	for i = 1, #params, 2 do
		local entry = tonumber(params[ i ])
		local count = math.floor(tonumber(params[i+1]) * (1 + extra / 100))
		if entry and count then
			table.insert(list, entry)
			table.insert(list, count)
		end
	end
	
	return string.join(",", list)
end

-- �˺�����ǰ
function AI_WorldBoss:DamageTaken(owner, unit, damage)
	local bossInfo = UnitInfo:new{ptr = owner}
	local map_ptr = unitLib.GetMap(owner)
	local instanceInfo = InstanceWorldBoss:new{ptr = map_ptr}
	local mapid  = instanceInfo:GetMapId()
	local lineNo = instanceInfo:GetMapLineNo()
	
	if damage <= 0 then
		return
	end
	
	local prev = bossInfo:GetHealth()
	local maxHealth  = bossInfo:GetMaxHealth()
	if damage > prev then
		damage = prev
	end
	
	currHealth = prev - damage
	
	if prev == 0 then
		return
	end
	
	local playerGuid = ''
	local name = ''
	local unitInfo = UnitInfo:new {ptr = unit}
	-- ����ǹ�����ҹ�����
	if unitInfo:GetTypeID() == TYPEID_UNIT then
		local host = creatureLib.GetMonsterHost(unit)
		if host then
			unitInfo = UnitInfo:new {ptr = host}
			playerGuid = unitInfo:GetPlayerGuid()
			name = unitInfo:GetName()
		end
	else
		playerGuid = unitInfo:GetPlayerGuid()
		name = unitInfo:GetName()
	end
	
	-- ��������
	mapLib.AddBossDamage(map_ptr, unitInfo.ptr, damage, maxHealth, unitInfo:GetLevel(), unitInfo:GetVIP())
	return 0
end

-- �ܵ��˺���
function AI_WorldBoss:DamageDeal( owner, unit, damage)
	local map_ptr = unitLib.GetMap(owner)
	local instanceInfo = InstanceWorldBoss:new{ptr = map_ptr}
	local lineNo = instanceInfo:GetMapLineNo()
	
	if damage < 0 then
		
		return
	end
end

return InstanceWorldBoss