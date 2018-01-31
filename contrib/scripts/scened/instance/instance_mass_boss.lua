InstanceMassBoss = class("InstanceMassBoss", InstanceInstBase)
local protocols = require('share.protocols')

InstanceMassBoss.Name = "InstanceMassBoss"

function InstanceMassBoss:ctor(  )
	
end

--��ʼ���ű�����
function InstanceMassBoss:OnInitScript(  )
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	InstanceInstBase.OnInitScript(self) --���û���

	self:parseGeneralId()

	-- ˢboss
	mapLib.AddTimer(self.ptr, 'onRefreshMassBoss', 1000)
	-- ����û��ʱ������ ���ԼӲ��ӽ���ʱ�� ����ν
	self:SetMapEndTime(os.time() + 180)
end

function InstanceMassBoss:GetRoomId()
	return self:GetUInt32(MAP_MASS_BOSS_INT_FIELD_ROOM)
end


function InstanceMassBoss:parseGeneralId()
	-- groupId#roomId
	local generalId = self:GetMapGeneralId()
	local params = string.split(generalId, '#')
	local room = tonumber(params[ 2 ])
	self:SetUInt32(MAP_MASS_BOSS_INT_FIELD_ROOM, room)
end

function InstanceMassBoss:isBossCreated(id)
	return self:GetBit(MAP_MASS_BOSS_INT_FIELD_BOSS_CREATE, id)
end

function InstanceMassBoss:bossCreate(id)
	self:SetBit(MAP_MASS_BOSS_INT_FIELD_BOSS_CREATE, id)
end

function InstanceMassBoss:bossDead(id)
	self:UnSetBit(MAP_MASS_BOSS_INT_FIELD_BOSS_CREATE, id)
end

function InstanceMassBoss:onRefreshMassBoss()
	local mapid = self:GetMapId()
	for id = 1, #tb_mass_boss_info do
		local bossconfig = tb_mass_boss_info[ id ]
		-- �ж��Ƿ����ڵ�ͼ�д���
		if globalValue:isMassBossAlive(id) and not self:isBossCreated(id) and bossconfig.mapid == mapid then
			
			local entry  = bossconfig.bossEntry
			local born   = bossconfig.bossPos
			local config = tb_creature_template[entry]
			local creature = mapLib.AddCreature(self.ptr, {
					templateid = entry, x = born[ 1 ], y = born[ 2 ], active_grid = true,
					ainame = "AI_MassBoss", npcflag = {}
				}
			)
			local creatureInfo = UnitInfo:new{ptr = creature}
			-- ��ʶΪboss��
			creatureInfo:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
			creatureInfo:SetUInt32(UNIT_INT_FIELD_RISK_CREATURE_ID, id)
			local rate = mapLib.GetMassBossHpRate(id)
			if rate == 0 then
				rate = 100
			end
			creatureInfo:SetHealth(math.ceil(creatureInfo:GetMaxHealth() * rate / 100))
			self:bossCreate(id)
			app:CallOptResult(self.ptr, OPERTE_TYPE_FIELD_BOSS, FIELD_BOSS_OPERTE_BOSS_BORN, {config.name, tb_map[mapid].name})
		end
	end
	
	return true
end

--��Ҽ����ͼ
function InstanceMassBoss:OnJoinPlayer(player)
	InstanceInstBase.OnJoinPlayer(self, player)
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻��������ȸ���
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
	end

	local room = self:GetRoomId()
	local prev = mapLib.GetMassBossEnterCount(room)
	mapLib.SetMassBossEnterCount(room, prev + 1)
	self:checkCannotAttackBoss(playerInfo)
end

--������뿪ʱ����
function InstanceMassBoss:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	local room = self:GetRoomId()
	local prev = mapLib.GetMassBossEnterCount(room)
	mapLib.SetMassBossEnterCount(room, prev - 1)
	self:ClearOwnFlag(player)
end

function InstanceMassBoss:checkCannotAttackBoss(playerInfo)
	if playerInfo:GetMassBossTimes() == 0 then
		-- ���벻�ɹ��������BUFF
		local player = playerInfo.ptr
		local buffEffectId = tb_mass_boss_base[ 1 ].monsterForbid
		local buffEffectConfig = tb_buff_effect[buffEffectId]
		SpelladdBuff(player, buffEffectConfig.buff_id, player, buffEffectId, buffEffectConfig.duration)
	end
end

function InstanceMassBoss:playerKilledOneBoss(creatureInfo, playerInfo)
	if playerInfo:GetMassBossTimes() > 0 then
		playerInfo:SubMassBossTimes()
		playerInfo:SetUInt32(UNIT_INT_FIELD_BOSS_OWN_FLAG, 0)
		
		local dict = {}
		local entry = creatureInfo:GetEntry()
		DoRandomDropTable(tb_creature_template[entry].reward_id, dict)
		
		-- �ͻ�����ʾʰȡ�ٶ���
		local destX, destY = unitLib.GetPos(creatureInfo.ptr)
		noticeClientShowPickLootAnimate(playerInfo.ptr, dict, destX, destY)
		
		PlayerAddRewards(playerInfo.ptr, dict, MONEY_CHANGE_SELECT_LOOT, LOG_ITEM_OPER_TYPE_LOOT, 0, false)
		
		self:checkCannotAttackBoss(playerInfo)
	end
end

function InstanceMassBoss:onBossDead(creatureInfo)
	local id = creatureInfo:GetUInt32(UNIT_INT_FIELD_RISK_CREATURE_ID)
	local playerGuid = creatureInfo:GetDropOwner()
	
	globalValue:doMassBossEnd(id)
	mapLib.SetMassBossHpRate(id, 0)
	self:bossDead(id)
	-- ��ҹ��� �ж�
	local player = mapLib.GetPlayerByPlayerGuid(self.ptr, playerGuid)
	if player then
		local playerInfo = UnitInfo:new {ptr = player}
		self:playerKilledOneBoss(creatureInfo, playerInfo)
	end
end

--����ұ����ɱ��ʱ����
function InstanceMassBoss:OnPlayerKilled(player, killer)
	InstanceFieldBase.OnPlayerKilled(self, player, killer)
	
	return 0
end
	
-- ����ұ�����ɱ��
function InstanceMassBoss:OnPlayerKilledByMonster(player, killer)	
	InstanceFieldBase.OnPlayerKilledByMonster(self, player, killer)
	
	return 0
end

function InstanceMassBoss:GetDropInfo(playerInfo)
	return InstanceFieldBase.GetDropInfo(self, playerInfo)
end


function InstanceMassBoss:OnPlayerDeath(player)
	self:ClearOwnFlag(player)
	local playerInfo = UnitInfo:new{ptr = player}
	self:OnSendDeathInfo(playerInfo, '', '')
end


function InstanceMassBoss:ClearOwnFlag(player)
	local playerInfo = UnitInfo:new{ptr = player}
	local allCreatures = mapLib.GetAllCreature(self.ptr)
	local id = playerInfo:GetUInt32(UNIT_INT_FIELD_BOSS_OWN_FLAG)
	playerInfo:SetUInt32(UNIT_INT_FIELD_BOSS_OWN_FLAG, 0)
	for _, creature in ipairs(allCreatures) do
		local creatureInfo = UnitInfo:new {ptr = creature}
		if creatureInfo:GetUInt32(UNIT_INT_FIELD_RISK_CREATURE_ID) == id then
			creatureInfo:clearBossDropOwner()
			return
		end
	end
end

function onMassBossReborn(id)
	mapLib.SetMassBossHpRate(id, 100)
end

--AI_MassBoss
-------------------------����boss---------------------------
AI_MassBoss = class("AI_MassBoss", AI_Base)
AI_MassBoss.ainame = "AI_MassBoss"

--����
function AI_MassBoss:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local instanceInfo = InstanceMassBoss:new{ptr = map_ptr}
	local creatureInfo = UnitInfo:new {ptr = owner}
	instanceInfo:onBossDead(creatureInfo)
	
	return 0
end

-- �˺�����ǰ
function AI_MassBoss:DamageTaken(owner, unit, damage)
	local bossInfo = UnitInfo:new{ptr = owner}
	local map_ptr = unitLib.GetMap(owner)
	local instanceInfo = InstanceMassBoss:new{ptr = map_ptr}
	local mapid  = instanceInfo:GetMapId()
	local lineNo = instanceInfo:GetMapLineNo()
	
	if damage <= 0 then
		local id = bossInfo:GetUInt32(UNIT_INT_FIELD_RISK_CREATURE_ID)
		mapLib.SetMassBossHpRate(id, 100)
		return 
	end
	
	local prev = bossInfo:GetHealth()
	local maxHealth  = bossInfo:GetMaxHealth()
	if damage > prev then damage = prev end
	
	currHealth = prev - damage
	if prev == 0 then return end

	local playerGuid = ''
	local name = ''
	local unitInfo = UnitInfo:new {ptr = unit}
	-- ����ǹ�����ҹ�����
	if unitInfo:GetTypeID() == TYPEID_UNIT then
		local host = creatureLib.GetMonsterHost(unit)
		if host then
			unitInfo = UnitInfo:new {ptr = host}
		end
	end

	local id = bossInfo:GetUInt32(UNIT_INT_FIELD_RISK_CREATURE_ID)
	local rate = math.ceil(currHealth * 100 / maxHealth)
	mapLib.SetMassBossHpRate(id, rate)
	
	local diff = tb_mass_boss_base[ 1 ].diff
	bossInfo:onHurtByPlayer(unitInfo, id, diff)
--	����ת������ ���� ӵ�й�������Ȩ����ҳ���x�벻�Թ�������˺�
	return 0
end

function InstanceMassBoss:LootAllot(owner, player, killer, drop_rate_multiples, boss_type, fcm)
	
end

return InstanceMassBoss