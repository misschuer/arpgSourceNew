require("math")
--------------------------------------

--------------------------------------------------------------------------------------------------------------
-- 传送的时候该做点什么事
function DoPlayerTeleport(player)
	local playerInfo = UnitInfo:new{ptr = player}
	playerInfo:RemoveUseGameObjectFlag()
end


--玩家脱离战斗之后干点什么事情
function DosometingScript(player)
	
end

-- PVP战斗死亡的逻辑
function OnPVPKilled(killer, target)
	local killerInfo = UnitInfo:new{ptr = killer}
	-- 加仇人列表
	playerLib.SendToAppdDoSomething(target, SCENED_APPD_ADD_ENEMY, 1, killerInfo:GetPlayerGuid())
end

--玩家PVP时目标方的一些处理
function DOPlayerPvP(player,target)
	--[[
		1、取消骑乘状态并锁定为不可使用
		2、取消打坐状态并锁定为不可使用
		3、取消采集状态
		
		假如当前为和平模式，则切换为自卫模式
	]]
	
	local targetInfo = UnitInfo:new {ptr = target}
	if targetInfo:isPeaceMode() then
		targetInfo:ChangeToFamilyMode()
	end
	
	local mapid = unitLib.GetMapID(target)
	local map_ptr = unitLib.GetMap(target)
	local openguid = mapLib.GetOnOpenGuid(map_ptr)
	local myguid = playerLib.GetPlayerGuid(target)
	if openguid ~= myguid then
		return
	end
	
	local mapInfo = Select_Instance_Script(mapid):new {ptr = map_ptr}
	mapInfo:OnDisrupt(player)
	
	--取消打坐	
	--[[if playerInfo:GetDaZuoTime() > 0 then
		playerInfo:ReceiveDaZuo()
	end--]]
end

-- 怪物攻击玩家时的一些处理
function DOPlayerPvE(creature, target)
	
	local mapid = unitLib.GetMapID(target)
	local map_ptr = unitLib.GetMap(target)
	local openguid = mapLib.GetOnOpenGuid(map_ptr)
	local myguid = playerLib.GetPlayerGuid(target)
	if openguid ~= myguid then
		return
	end
	
	local mapInfo = Select_Instance_Script(mapid):new {ptr = map_ptr}
	mapInfo:OnDisrupt(player)
	
	--取消打坐
	--[[
	if playerInfo:GetDaZuoTime() > 0 then
		playerInfo:ReceiveDaZuo()
	end
	]]
end

--上线清除一些BUFF
function DoOnlineClearBuff(player)
	local playerInfo = UnitInfo:new{ptr = player}
	playerInfo:UnSetUnitFlags(UNIT_FIELD_FLAGS_CANT_CAST)
end

function DOTiaozhanBonus(player,lv)	
	-- local bonus = {}
	-- bonus[EQUIP_ATTR_HP] = 0
	-- bonus[EQUIP_ATTR_DAMAGE] = 0
	-- bonus[EQUIP_ATTR_DEF] =    0
	-- bonus[EQUIP_ATTR_HIT] =    0
	-- bonus[EQUIP_ATTR_CRIT] =   0
	-- bonus[EQUIP_ATTR_MANA] =   0

	-- for i = 1,80,1
	-- do
		-- if(hasAchievementsBonus(player,i-1,SERIES_CHALLENGE)==1 and hasAchievements(player,i-1,SERIES_CHALLENGE)==1)then
			-- --生命	攻击	防御	命中	重击
			-- bonus[EQUIP_ATTR_HP] = bonus[EQUIP_ATTR_HP] + ChallengeAttrBonus[i][1]
			-- bonus[EQUIP_ATTR_DAMAGE] = bonus[EQUIP_ATTR_DAMAGE] + ChallengeAttrBonus[i][2]
			-- bonus[EQUIP_ATTR_DEF] = bonus[EQUIP_ATTR_DEF] +ChallengeAttrBonus[i][3]
			-- bonus[EQUIP_ATTR_HIT] = bonus[EQUIP_ATTR_HIT] + ChallengeAttrBonus[i][4]
			-- bonus[EQUIP_ATTR_CRIT] = bonus[EQUIP_ATTR_CRIT] + ChallengeAttrBonus[i][5]
			-- bonus[EQUIP_ATTR_MANA] = bonus[EQUIP_ATTR_MANA] + ChallengeAttrBonus[i][6]
		-- end
	-- end

	-- return (bonus[EQUIP_ATTR_HP]/25.72 + bonus[EQUIP_ATTR_MANA]/102.88 + bonus[EQUIP_ATTR_DAMAGE]/1.55 + bonus[EQUIP_ATTR_DEF]/4.34 +bonus[EQUIP_ATTR_HIT]/1.03 + bonus[EQUIP_ATTR_CRIT]/1.37)*2.12

end



----------------------------------计算战斗公式----------------------------------
-- 命中率=85%+命中*0.0033%
-- 闪避率=闪避*0.0017%
-- 是否命中=命中率*（1-闪避率）		
-- 所有属性都是*100的值 所以这里得还原
-- @param attackInfo: 攻击方
-- @param hurtInfo: 防守方
-- return
--		是否命中
function isHit(attackInfo, hurtInfo)
	local hit = attackInfo:GetHit() / 100

	local A = 0
	if attackInfo:GetTypeID() == TYPEID_PLAYER then
		A = 1
		local diff = attackInfo:GetLevel() - hurtInfo:GetLevel()
		if diff < 0 then
			A = 1 + diff * 0.015
		end
		A = math.max(math.min(1, A), 0.85)
	end
	local hitRate  = A + hit * 0.0033 / 100 + attackInfo:GetHitRate() / 10000
	
	
	local miss = hurtInfo:GetMiss() / 100
	local missRate = miss * 0.0017 / 100 + hurtInfo:GetMissRate() / 10000
	
	local limit = 100
	local p = math.floor(hitRate * (1 - missRate) * limit)
	local val = randInt(1, limit)
	
	return val <= p
end

-- 实际受到伤害=（攻击*技能加成比+技能附加）*（1-总免伤）*K暴击修正*（1+伤害加深-伤害减免）
-- 总免伤=基础免伤+强化免伤
-- 基础免伤=基础护甲/（基础护甲+25.5*lv+400）
-- 强化免伤=强化护甲*职业系数

-- @param attackInfo: 攻击方
-- @param hurtInfo: 防守方
-- @param skillLevel: 攻击方技能等级
-- @param skillDamFactor: 攻击方技能伤害修正系数(填表的)
-- @param skillDamVal: 攻击方技能伤害附加值(填表的)
-- return
--		伤害
function getCastDamage(attackInfo, hurtInfo, skillDamFactor, skillDamVal, mult)
	local armor = hurtInfo:GetArmor() / 100
	local jobIndx = -1
	if hurtInfo:GetGender() > 0 then
		jobIndx = getJobIndxByGender(hurtInfo:GetGender())
	end
	local factor = tb_job_info[jobIndx].rate / 1000000
	local damageResist = armor / (armor + 25.5 * attackInfo:GetLevel() + 400) + hurtInfo:GetStrengthArmor() / 100 * factor 
	
	local damAmp = attackInfo:GetDamageAmplifyRate() / 10000
	local damRes = hurtInfo:GetDamageResistRate() / 10000
	local attackDamage = attackInfo:GetDamage() / 100
	
	local dam = (attackDamage * skillDamFactor + skillDamVal) * (1 - damageResist) * mult * (1 + damAmp - damRes)
	return dam
end

-- 伤害随机区间：[85%, 115%]
-- return
--		随机伤害比率
function getDamRange()
	return randInt(85, 115) / 100
end

-- 技能伤害=(攻击*技能伤害系数+技能附加伤害)*伤害随机区间
-- 伤害随机区间：[85%,115%]
function getSkillDam(damage, skillDamFactor, skillDamVal)
	-- 伤害随机区间
	local damRange = getDamRange()
	return (damage * skillDamFactor + skillDamVal) * damRange
end

--[[
暴击率=10%+暴击*0.0017%	
抗暴击率=抗暴*0.0027%	
是否暴击=暴击率*（1-抗暴率）

-- 所有属性都是*100的值 所以这里得还原
	@param attackInfo: 攻击方
	@param hurtInfo: 防守方
	return
		是否暴击
--]]

function isCrit(attackInfo, hurtInfo)
	local crit = attackInfo:GetCrit() / 100
	local critRate = 0.1 + crit * 0.0017 / 100 + attackInfo:GetCritRate() / 10000
	
	local tough = hurtInfo:GetTough() / 100
	local resistCritRate = tough * 0.0027 / 100 + hurtInfo:GetCritResistRate() / 10000
	
	local p = math.floor(critRate * (1 - resistCritRate) * 10000)
	local val = randInt(1, 10000)

	return val <= p
end

-- 未暴击，K暴击修正=0								
-- 暴击时，K暴击修正=1.5+(暴击伤害-暴伤减免)*0.0033%							150%<=K暴击修正<=300%	
-- 所有属性都是*100的值 所以这里得还原
-- @param attackInfo: 攻击方
-- @param hurtInfo: 防守方
-- return
--		暴击倍数
function critMult(attackInfo, hurtInfo)
	local critDamRate = attackInfo:GetCritDamRate() / 100
	local critResistDamRate = hurtInfo:GetCritResistDamRate() / 100
	local ret = 1.5 + (critDamRate - critResistDamRate) * 0.0033 / 100
	ret = math.max(1.5, math.min(ret, 3.0))
	return ret
end

-- 暴击伤害=暴击伤害倍数*普通伤害
-- @param normalDam: 普通伤害
-- @param mult: 暴击倍数
-- return
--		暴击伤害
function critDamage(normalDam, mult)
	return math.floor(normalDam * mult)
end

-- 攻击方受到的反弹伤害=攻击方对防守方造成最终伤害*防守方反弹伤害
-- @param damage: 最终伤害
-- @param hurtInfo: 防守方
-- return
--		反弹伤害
function damageReturned(damage, hurtInfo)
	return math.floor(damage * hurtInfo:GetDamageReturnRate() / 10000)
end

-- 吸血
-- @param damage: 最终伤害
-- @param casterInfo: 攻击方
-- return
--		吸血值
function damageVampiric(damage, casterInfo)
	return math.floor(damage * casterInfo:GetVampiricRate() / 10000)
end


-- 玩家组队经验
--[[
怪物经验计算程式：
杀怪经验获得=(怪物标准经验*(1+VIP经验加层+经验药水双倍)/队伍人数)*A*（1+factorA%%*(队伍人数-1)）
当：|角色等级-怪物等级|≤5,时
A=1
当：|角色等级-怪物等级|>5,时	
A=math.max(0, 1-|角色等级-怪物等级|*factorB%%)
PS:最终取值向上取整
--]]

function getFinalExp(targetBaseExp, targetLevel, killerLevel, vipRate, itemRate, groupCnt)
	-- 计算A值
	local diff = math.abs(killerLevel - targetLevel)
	local A = 1
	if diff > 10 then
		A = 1 - diff * tb_group_exp[ 1 ].factorB / 10000
	end
	A = math.max(0, A)
	
	local ret = targetBaseExp * (1 + vipRate / 100 + itemRate / 100) / groupCnt * A * (1 + tb_group_exp[ 1 ].factorA / 10000 * (groupCnt - 1))
	return math.ceil(ret)
end
