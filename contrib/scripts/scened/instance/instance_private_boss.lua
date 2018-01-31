InstancePrivateBoss = class("InstancePrivateBoss", InstanceInstBase)
local protocols = require('share.protocols')

InstancePrivateBoss.Name = "InstancePrivateBoss"
InstancePrivateBoss.BOSS_ALIAS_NAME = 'PRIVATE_BOSS'
InstancePrivateBoss.exit_time = 10

function InstancePrivateBoss:ctor(  )
	
end

--��ʼ���ű�����
function InstancePrivateBoss:OnInitScript(  )
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	InstanceInstBase.OnInitScript(self) --���û���
	-- ����generalid
	self:parseGeneralId()
	
	
	
	
end

function InstancePrivateBoss:parseGeneralId()
	local generalId	= self:GetMapGeneralId()
	local params = string.split(generalId, '|')
	
	local id = tonumber(params[1])
	local buffeffectId = tonumber(params[2])
	
	self:SetPrivateBossId(id)
	self:SetBuffeffectId(buffeffectId)
	
	-- ˢboss
	self:onRefreshBoss()
	
	--tb_private_boss_base[1].timeLimit = 180
	-- ��սʱ��
	self:SetMapEndTime(os.time() + tb_private_boss_base[1].timeLimit + self.exit_time)
	self:SetMapQuestEndTime(os.time() + tb_private_boss_base[1].timeLimit)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, os.time() + tb_private_boss_base[1].timeLimit)
	
	-- ˢ������
	local mapQuest = tb_private_boss_info[id].quest[1]
	-- �Ӹ�������
	InstanceInstBase.OnAddQuests(self, {mapQuest})
end

function InstancePrivateBoss:SetPrivateBossId(id)
	self:SetUInt32(MAP_PRIVATE_BOSS_INT_FIELD_ID, id)
end

function InstancePrivateBoss:GetPrivateBossId()
	return self:GetUInt32(MAP_PRIVATE_BOSS_INT_FIELD_ID)
end

function InstancePrivateBoss:SetBuffeffectId(id)
	self:SetUInt32(MAP_PRIVATE_BOSS_INT_FIELD_BUFFEFFECT_ID, id)
end

function InstancePrivateBoss:GetBuffeffectId()
	return self:GetUInt32(MAP_PRIVATE_BOSS_INT_FIELD_BUFFEFFECT_ID)
end

--[[
function InstancePrivateBoss:DoMapBuffBonus(unit)
	if GetUnitTypeID(unit) == TYPEID_PLAYER then
		local buffEffectId = self:GetBuffeffectId()
		if buffEffectId ~= 0 then
			local buff_id = tb_buff_effect[buffEffectId].buff_id
			SpelladdBuff(unit, buff_id, unit, buffEffectId, 180)
		end
	end
end--]]

function InstancePrivateBoss:onRefreshBoss()
	local id = self:GetPrivateBossId()
	local boss = mapLib.AliasCreature(self.ptr, self.BOSS_ALIAS_NAME)
	if not boss then
		local bossconfig = tb_private_boss_info[ id ]
		local entry  = bossconfig.bossEntry
		local born   = bossconfig.bossPos
		local config = tb_creature_template[entry]
		local creature = mapLib.AddCreature(self.ptr, 
			{
				templateid = entry, x = born[ 1 ], y = born[ 2 ], active_grid = true, 
				alias_name = self.BOSS_ALIAS_NAME, ainame = "AI_PrivateBoss", npcflag = {}
			}
		)
		
		if creature then
			local debuffeffect_id = self:GetBuffeffectId()
			if debuffeffect_id ~= 0 then
				local debuff_id = tb_buff_effect[debuffeffect_id].buff_id
				SpelladdBuff(creature, debuff_id, creature, debuffeffect_id, 200)
			end
			local creatureInfo = UnitInfo:new{ptr = creature}
			-- ��ʶΪboss��
			creatureInfo:SetUnitFlags(UNIT_FIELD_FLAGS_IS_BOSS_CREATURE)
		end
	end
end

-- ����BOSS������
function InstancePrivateBoss:IsEnd()
	return self:GetMapQuestEndTime() > 0 and self:GetMapQuestEndTime() <= os.time()
end

--������״̬�����仯ʱ�䴥��
function InstancePrivateBoss:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH or tostate == self.STATE_FAIL then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		--10s���������
		local timestamp = os.time() + self.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

--��Ҽ����ͼ
function InstancePrivateBoss:OnJoinPlayer(player)
	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻�������ֱ�ӵ���ȥ
		unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
		return
	end
	
	-- ����ʱ�䵽�Ͳ��ý���
	if self:IsEnd() then
		mapLib.ExitInstance(self.ptr, player)
		self:SetMapState(self.STATE_FAIL)
		return
	end
	
	playerInfo:ModifyHealth(playerInfo:GetMaxHealth())
	playerInfo:ChangeToFamilyMode()
end

--������뿪ʱ����
function InstancePrivateBoss:OnLeavePlayer( player, is_offline)
	InstanceInstBase.OnLeavePlayer(self, player, is_offline)
	local buffEffectId = self:GetBuffeffectId()
	if buffEffectId ~= 0 then
		local buff_id = tb_buff_effect[buffEffectId].buff_id
		unitLib.RemoveBuff(player,buff_id)
	end
	
	local playerInfo = UnitInfo:new{ptr = player}
	
	playerInfo:SetLastInstanceParam(self:GetPrivateBossId())
end

-- �����������
function InstancePrivateBoss:OnPlayerDeath(player)
	-- �������������ȥ
	--unitLib.Respawn(player, RESURRECTION_SPAWNPOINT, 100)
	--mapLib.ExitInstance(self.ptr, player)
	--self:SetMapState(self.STATE_FAIL)
	self:instanceFail()
end

function InstancePrivateBoss:onBossDead()
	self:SetMapState(self.STATE_FINISH)
	
	self:sendReward()
	
	
end

-- ���Ž���
function InstancePrivateBoss:sendReward()
	local allPlayers = mapLib.GetAllPlayer(self.ptr)
	for _, unit_player in ipairs(allPlayers) do
		local playerInfo = UnitInfo:new {ptr = unit_player}
		local dict = {}
		-- ��ý���
		local id = self:GetPrivateBossId()
		local dropId = tb_private_boss_info[id]["dropid_"..getJobIndxByGender(playerInfo:GetGender())]
		DoRandomDropTable({dropId}, dict)
		PlayerAddRewards(unit_player, dict, MONEY_CHANGE_PRIVATE_BOSS, LOG_ITEM_OPER_TYPE_PRIVATE_BOSS)
		
		local list = Change_To_Item_Reward_Info(dict, true)
		
		playerInfo:call_send_instance_result(self:GetMapState(), self.exit_time, list, INSTANCE_SUB_TYPE_PRIVATE_BOSS, '')
		
		playerLib.SendToAppdDoSomething(unit_player, SCENED_APPD_PRIVATE_BOSS_WIN,id)
	end
end


--AI_PrivateBoss
-------------------------˽��boss---------------------------
AI_PrivateBoss = class("AI_PrivateBoss", AI_Base)
AI_PrivateBoss.ainame = "AI_PrivateBoss"

--����
function AI_PrivateBoss:JustDied( map_ptr,owner,killer_ptr )
	AI_Base.JustDied(self,map_ptr,owner,killer_ptr)
	
	local instanceInfo = InstancePrivateBoss:new{ptr = map_ptr}
	instanceInfo:onBossDead()
	
	-- ����ɱ�ֽ���
	local ownerInfo = UnitInfo:new {ptr = owner}
	local entry = ownerInfo:GetEntry()
	local updated = instanceInfo:OneMonsterKilled(entry)
	
	return 0
end

return InstancePrivateBoss