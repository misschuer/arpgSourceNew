--[[
随机获得类似 {{值1, 万分比概率1},{值2, 万分比概率2},...}的值
]]
function GetRandomExp(expTable)
	local index = GetRandomIndex(expTable)
	if index > 0 then
		return expTable[index][ 1 ]
	end
	
	return 0
end

SHOP_ID_FACTOR = 100000
-- 通过货币类型和道具id获得商城道具序列号
function GetShopId(money_type, itemId)
	return money_type * SHOP_ID_FACTOR + itemId
end

function GetItemIdByShopId(id)
	return id % SHOP_ID_FACTOR
end

--[[
随机获得类似 {{值1, 万分比概率1},{值2, 万分比概率2},...}的下标
]]
function GetRandomIndex(randTable)
	local rd = randInt(1, 10000)
	local bs = 0
	
	for i = 1, #randTable do
		bs = bs + randTable[ i ][ 2 ]
		if rd <= bs then
			return i
		end
	end
	
	return 0
end

function GetRandomIndexByRateList(randTable)
	local rd = randInt(1, 10000)
	local bs = 0
	
	for i = 1, #randTable do
		bs = bs + randTable[ i ]
		if rd <= bs then
			return i
		end
	end
	
	return 0
end

-- 从连续的size个数里面随机count个数, 保证惟一
function GetRandomIndexTable(size, count)
	if (size < count) then
		return {}
	end
	
	local ret = {}
	
	local dict = {}
	for i = 1, size do
		table.insert(dict, i)
	end
	
	for i = 1, count do
		local indx = randInt(1, #dict)
		table.insert(ret, dict[indx])
		-- 替换到最后个并置空
		local last = dict[#dict]
		if indx ~= #dict then
			dict[indx] = last
		end
		dict[#dict] = nil
	end
	
	return ret
end

function mergeListToList(dict1,dict2)
	for _,info in pairs(dict2) do
		AddTempInfoIfExist(dict1,info[1],info[2])
	end
end

--合并类似{{key1, value1}, {key2, value2}...}的table
function AddTempInfoIfExist(map, key, value)
	for _, info in pairs(map) do
		if info[ 1 ] == key then
			info[ 2 ] = info[ 2 ] + value
			return
		end
	end
	table.insert(map, {key, value})
end

-- 合并 {[key] = value}的table
function MergeSameTable(map, key, value)
	if not map[key] then
		map[key] = 0
	end
	map[key] = map[key] + value
end

-- 合并属性
function mergeAttrs(attrs, pros)
	for _, attrInfo in ipairs(pros) do
		local attrId = attrInfo[ 1 ]
		if not attrs[attrId] then
			attrs[attrId] = 0
		end
		attrs[attrId] = attrs[attrId] + attrInfo[ 2 ]
	end
end

function TPrint(map)
	local out = "{"
	for i = 1, #map do
		if i > 1 then
			out = out .. ", "
		end
		out = out.."{"..map[ i ][ 1 ]..", "..map[ i ][ 2 ].."}"
	end
	out = out.."}"
end

function Ttab( tab )
	local out = "{"
	for i,v in ipairs(tab) do
		out = out .."{" .. i .. "," .. v .."}"
	end
	out = out.."}"
	outFmtInfo(out)
end

-- 是否是资源
function IsResource(itemId)
	if (not tb_item_template[itemId]) then
		print(debug.traceback())
	end
	return tb_item_template[itemId] and tb_item_template[itemId].money_type > 0
end

-- 获得资源类型
function GetMoneyType(itemId)
	if not tb_item_template[itemId] then
		print("item = ", itemId)
		print(debug.traceback())
		return -1
	end
	local money_type = tb_item_template[itemId].money_type
	return money_type
end

-- 判断字符串匹配正则的结果
function DoFind(str, regex, rep)
	local ret = {}
    local indx = 1
    local size = #str
    while (indx <= size) do
        local a, b = string.find(str, regex, indx)
        if not a then
            break
        end
        indx = b+1
		local substr = string.sub(str, a, b)
		substr, _ = string.gsub(substr, regex, rep)
		table.insert(ret, {a, b, substr})
    end
	
	return ret
end


function DoRandomDropTable(dropTable, dict)
	for _, dropId in pairs(dropTable) do
		DoRandomDrop(dropId, dict)
	end
end

-- 随机奖励 并合并到dict中
function DoRandomDrop(dropId, dict)
	local config = tb_drop_reward[dropId]
	if not config then return end
	
	for _, packetInfo in pairs(config.reward) do
		local packetId = packetInfo[ 1 ]
		local rate = packetInfo[ 2 ]
		local rd = randInt(1, 10000)
		if rd <= rate then
			local packConfig = tb_drop_packet[packetId]
			if not packConfig then
				outFmtError("============= DoRandomDrop packetId = %d is not exist", packetId)
				return
			end
			local indx = GetRandomIndexByRateList(packConfig.itemRates)
			if indx > 0 then
				local itemId = packConfig.itemKeys[indx]
				local count = packConfig.counts[indx]
				if not tb_item_template[itemId] then
					outFmtError("================ itemId = %d in packetId = %d", itemId, packetId)
					return
				end
				if dict[itemId] == nil then
					dict[itemId] = 0
				end
				dict[itemId] = dict[itemId] + count
			end
		end
	end
end

--[[
dict = {[itemId] = num}
]]
function Change_To_Item_Reward_Info(dict, exp)
	exp = exp or true
	-- 扫荡的结果发送
	local list = {}
	for item_id, num in pairs(dict) do
		if (item_id ~= Item_Loot_Exp or exp) then
			local stru = item_reward_info_t .new()
			stru.item_id	= item_id
			stru.num 		= num
			table.insert(list, stru)
		end
	end
	
	return list
end

function Change_List_To_Item_Reward_Info(rewardDict, lost, exp)
	exp = exp or true
	-- 扫荡的结果发送
	local list = {}
	local size = #rewardDict - lost
	for i = 1, size do
		local itemInfo = rewardDict[ i ]
		local item_id = itemInfo[ 1 ]
		local num = itemInfo[ 2 ]
		if (item_id ~= Item_Loot_Exp or exp) then
			local stru = item_reward_info_t .new()
			stru.item_id	= item_id
			stru.num 		= num
			table.insert(list, stru)
		end
	end
	
	return list
end

--[[
	{{key1, value1}, {key2, value2}}  => {[key] = value}
]]
function changeTableStruct(dict)
	local ret = {}
	
	for _, info in pairs(dict) do
		ret[info[ 1 ]] = info[ 2 ]
	end
	
	return ret
end


function changeTableToList(dict)
	local list = {}
	for key, value in pairs(dict) do
		table.insert(list, {key, value})
	end
	
	return list
end

-- 计算战斗力
function DoAnyOneCalcForce(attrDict, gender, rate)
	rate = rate or 0.01
	local jobIndx = getJobIndxByGender(gender)
	local battlePoint = 0
	for attrId, value in pairs(attrDict) do
		battlePoint = battlePoint + value * tb_battle_force[attrId]["rate"..jobIndx]
	end
	
	return math.floor(battlePoint / 10000 * rate)
end

function DoAnyOneCalcForceByAry(attrAy, gender, rate)
	rate = rate or 0.01
	local jobIndx = getJobIndxByGender(gender)
	local battlePoint = 0
	for k, v in pairs(attrAy) do
		battlePoint = battlePoint + v[2] * tb_battle_force[v[1]]["rate"..jobIndx]
	end
	
	return math.floor(battlePoint / 10000 * rate)
end

-- 获得邮件模版id
function GetMailEntryId(gift_type, level)
	return gift_type * 65536 + level
end


function ToShowName(playerName)
	outFmtDebug("playerName=%s", playerName)
	local A = string.byte("A")
	local dict = string.split(playerName, ",")
--	local str = string.format("%s%s.%s", string.char((tonumber(dict[2]) - 1001) + A), dict[ 1 ], dict[ 3 ])
	local str = dict[ 3 ]
	return str
end

-- 获得今天刚开始的时间戳
-- x [0-6] {Sunday-Saturday}
function IsTodayWeekX(x)
	local date = os.date('*t', os.time())
	return date.wday == x + 1
end

-- 获得今天刚开始的时间戳
function GetTodayStartTimestamp(days)
	return getTheFirstTimestampOfDay(os.time(), days)
end

-- 获得时间戳对应的当天0点时间戳
function getTheFirstTimestampOfDay(time, days)
	time = time or os.time()
	days = days or 0
	local cur_date = os.date('*t', time)
	cur_date.hour = 0
	cur_date.sec = 0
	cur_date.min = 0
	return os.time(cur_date) + days * 86400
end

function checkSameDay(time1, time2)
	if time1 == 0 or time2 == 0 then
		return false
	end
	return getTheFirstTimestampOfDay(time1) == getTheFirstTimestampOfDay(time2)
end

--获得今日指定时分秒的时间戳
function GetTodayHMSTimestamp(h,m,s)
	local cur_date = os.date('*t', os.time())
	cur_date.hour = h
	cur_date.sec = s
	cur_date.min = m
	return os.time(cur_date)
end

-- 价格打折
function GetCostMulTab(baseTab,mul)
	
	if mul == 1 then
		return baseTab
	else 
		local resultdic = {}
		for _,v in ipairs(baseTab) do
			local tab = {}
			table.insert(tab,v[1])
			table.insert(tab,math.ceil(v[2] * mul))
			
			table.insert(resultdic,tab)
		end
		return resultdic
	end

end

-- 获得玩家的当前速度
function GetPlayerSpeed(playerLevel, mountLevel, illusionId, isRidable, gender)
	local speed = 0
	
	-- 未骑乘的取玩家速度
	if not isRidable then
		local config = tb_char_level[playerLevel]
		if config then
			local jobIndx = getJobIndxByGender(gender)
			local baseprop = config["prop"..jobIndx]
			for _, val in ipairs(baseprop) do
				local indx = val[ 1 ]
				if indx == EQUIP_ATTR_MOVE_SPEED then
					return val[ 2 ]
				end
			end
		end
		outFmtError("player level = %d has no speed attr", playerLevel)
		return 60
	end

	if tb_mount_base[mountLevel] then
		speed = tb_mount_base[mountLevel].speed
	end
	if illusionId > 0 then
		if speed < tb_mount_illusion[illusionId].speed then
			speed = tb_mount_illusion[illusionId].speed
		end
	end
	
	return speed
end


local weektimes = 604800
-- 从当前时间开始算 下一个星期x开始的时间戳
function GetNextWeekXStartTimeFromNow(x)
	-- 确保在0-6之间
	if x < 0 or x >= 7 then
		x = ((x % 7) + 7) % 7
	end
	
	return GetNextWeekXStartTimeFromTimestamp(x, os.time())
end

-- 从指定时间开始算 下一个星期x开始的时间戳
function GetNextWeekXStartTimeFromTimestamp(x, timestamp)
	local date = os.date('*t', timestamp)
	local weekend = date.wday
	date.hour = 0
	date.sec = 0
	date.min = 0
	date.wday = x+1 -- 周日为1
	local real_time = os.time(date)
	if real_time < timestamp then
		real_time = real_time + weektimes
	end
	
	return real_time
end

-- 获得带颜色的道具名称
function GetColordItemName(entry)
	local quality = tb_item_template[entry].quality
	local color = "ffffff"
	if tb_item_quality_color[quality] then
		color = tb_item_quality_color[quality].color
	end
	return string.format("[%s]%s", color, tb_item_template[entry].name)
end

-- print(GetNextWeekXStartTimeFromNow(1))
-- print(GetNextWeekXStartTimeFromTimestamp(1, 1488211200-weektimes))

function mi_sort(list, comp, onSwapCallback)
	comp = comp or function (a, b) return a < b end
	if not list or #list == 0 then
		return
	end
	_sort(list, 1, #list, comp, onSwapCallback)
end

function _sort(list, lt, rt, comp, callback)
	local i = lt
	local j = rt
	local mid = math.floor((i + j) / 2)
	local midValue = list[mid]
	--outFmtDebug("========= sort lt = %d, rt = %d", lt, rt)
	--printCompareValue(midValue)
	while (i <= j) do
		--outFmtDebug("========= i = %d, j = %d", i, j)
		while (i < rt and comp(list[ i ], midValue)) do
			--outFmtDebug("========= i = %d great than mid", i)
			--printCompareValue(list[ i ])
			i = i + 1
		end
		while (lt < j and comp(midValue, list[ j ])) do
			--outFmtDebug("========= j = %d small than mid", j)
			--printCompareValue(list[ j ])
			j = j - 1
		end
		--outFmtDebug("##################after check i = %d, j = %d", i, j)
		--printCompareValue(list[ i ])
		--printCompareValue(list[ j ])
		if i <= j then
			if callback and i < j then
				callback(list[ i ], list[ j ])
			end
			local tmp = list[ i ]
			list[ i ] = list[ j ]
			list[ j ] = tmp
			i = i + 1
			j = j - 1
		end
	end
	
	if i < rt then
		_sort(list, i, rt, comp, callback)
	end
	
	if j > lt then
		_sort(list, lt, j, comp, callback)
	end
end

function printCompareValue(obj)
	outFmtDebug("printCompareValue pos=%d,value = %d,value1=%d,value2=%d,value3=%d,value3_1=%d,value4=%d,value5=%d,value6=%d,value7=%d", 
obj.pos,obj.value,obj.value1,obj.value2,obj.value3,obj.value3_1,obj.value4,obj.value5,obj.value6,obj.value7)
end

function IsKeyInTable(key, tbl)
	for k,v in pairs(tbl) do
		if k == key then
			return true;
		end
	end
	return false;
end

--[[
	delimiter1: 第一层的分隔符
	delimiter2: 第二层的分隔符
--]]
function Join2dDictString(dict, delimiter1, delimiter2)
	delimiter1 = delimiter1 or GlobalCounter.delimiter1
	delimiter2 = delimiter2 or GlobalCounter.delimiter2
	
	local f = {}
	
	for _, element in ipairs(dict) do
		table.insert(f, string.join(delimiter2, element))
	end
		
	if #f == 0 then
		return ''
	end
	return string.join(delimiter1, f)
end

--[[
	content	  : 加密的内容
	delimiter1: 第一层的分隔符
	delimiter2: 第二层的分隔符
--]]
function SplitStringTo2dDict(content, delimiter1, delimiter2)
	local f = {}
	
	if string.len(content) == 0 then
		return f
	end
	
	delimiter1 = delimiter1 or GlobalCounter.delimiter1
	delimiter2 = delimiter2 or GlobalCounter.delimiter2
	
	local subs = string.split(content, delimiter1)
	for _, sub in pairs(subs) do
		local params = string.split(sub, delimiter2)
		table.insert(f, {tonumber(params[ 1 ]), tonumber(params[ 2 ]), tonumber(params[ 3 ]), tonumber(params[ 4 ]), tonumber(params[ 5 ])})
	end
	
	return f
end

-- 组装内容
function JoinDummyInfoIntoContent(guid, config)
	local content = string.format("%s|%s|%d|%d|%s|%d|%d|%d|%s|%s|%d|%d|%d|%d|%d|%d|%d",
		guid,
		config.name, 
		config.gender,
		config.level,
		Join2dDictString(config.attrs),
		config.weapon,
		config.avatar,
		config.divine,
		Join2dDictString(config.spells),
		Join2dDictString(config.passivespells),
		config.force,
		config.vip,
		config.reverse1,
		config.reverse2,
		config.reverse3,
		config.reverse4,
		config.reverse5
	)
	
	return content
end

-- 解析内容
function GetDummyInfoFromContent(content)
	
	local elements = string.split(content, '|')
	
	local config  = {}
	config.guid   = elements[ 1 ]
	config.name   = elements[ 2 ]
	config.gender = tonumber(elements[ 3 ])
	config.level  = tonumber(elements[ 4 ])
	config.attrs  = SplitStringTo2dDict(elements[ 5 ])
	config.weapon = tonumber(elements[ 6 ])
	config.avatar = tonumber(elements[ 7 ])
	config.divine = tonumber(elements[ 8 ])
	config.spells = SplitStringTo2dDict(elements[ 9 ])
	config.passivespells = SplitStringTo2dDict(elements[ 10 ])
	config.force  = tonumber(elements[ 11 ])
	config.vip    = tonumber(elements[ 12 ])
	config.reverse1 = tonumber(elements[ 13 ])
	config.reverse2 = tonumber(elements[ 14 ])
	config.reverse3 = tonumber(elements[ 15 ])
	config.reverse4 = tonumber(elements[ 16 ])
	config.reverse5 = tonumber(elements[ 17 ])
	
	return config
end

-- 获得性别敏感的奖励
function GetRewardIfGenderSensitive(rewards, gender)
	return rewards[gender] or rewards[ 1 ]
end

-- 计算攻击速度缩短的时间
function OnAttackSpeedChangeToShortenInterval(attackSpeed, interval)
	local count = math.min(attackSpeed / 200, 99.9)
	return math.floor(interval * (1 - 0.01 * count))
end

-- 用于斗剑台获得玩家属性
attrKeys = {
	[EQUIP_ATTR_MAX_HEALTH] = PLAYER_FIELD_MAX_HEALTH,	--最大生命
	[EQUIP_ATTR_DAMAGE] = PLAYER_FIELD_DAMAGE,	--攻击力
	[EQUIP_ATTR_ARMOR] = PLAYER_FIELD_ARMOR,	--防御力
	[EQUIP_ATTR_HIT] = PLAYER_FIELD_HIT,	--命中
	[EQUIP_ATTR_MISS] = PLAYER_FIELD_MISS,	--闪避
	[EQUIP_ATTR_CRIT] = PLAYER_FIELD_CRIT,	--暴击
	[EQUIP_ATTR_TOUGH] = PLAYER_FIELD_TOUGH,	--坚韧
	[EQUIP_ATTR_ATTACK_SPEED] = PLAYER_FIELD_ATTACK_SPEED,	--攻击速度
	[EQUIP_ATTR_MOVE_SPEED] = PLAYER_FIELD_MOVE_SPEED,	--移动速度
	[EQUIP_ATTR_IGNORE_ARMOR] = PLAYER_FIELD_IGNORE_ARMOR,	--忽视防御
	[EQUIP_ATTR_IGNORE_MISS] = PLAYER_FIELD_IGNORE_MISS,	--忽视闪避
	[EQUIP_ATTR_RECOVERY] = PLAYER_FIELD_RECOVERY,	--生命值回复
	[EQUIP_ATTR_DAMAGE_AMPLIFY_RATE] = PLAYER_FIELD_DAMAGE_AMPLIFY_RATE,	--伤害加深(万分比)
	[EQUIP_ATTR_DAMAGE_RESIST_RATE] = PLAYER_FIELD_DAMAGE_RESIST_RATE,	--伤害减免(万分比)
	[EQUIP_ATTR_DAMAGE_RETURN_RATE] = PLAYER_FIELD_DAMAGE_RETURN_RATE,	--反弹伤害(万分比)
	[EQUIP_ATTR_VAMPIRIC_RATE] = PLAYER_FIELD_VAMPIRIC_RATE,	--吸血光环(万分比)
	[EQUIP_ATTR_RECOVERY_RATE] = PLAYER_FIELD_RECOVERY_RATE,	--回复效率(万分比)
	[EQUIP_ATTR_CRIT_RATE] = PLAYER_FIELD_CRIT_RATE,	--暴击率(万分比)
	[EQUIP_ATTR_CRIT_RESIST_RATE] = PLAYER_FIELD_CRIT_RESIST_RATE,	--抗暴率(万分比)
	[EQUIP_ATTR_CRIT_DAM_RATE] = PLAYER_FIELD_CRIT_DAM_RATE,	--暴击伤害倍数(万分比)
	[EQUIP_ATTR_CRIT_RESIST_DAM_RATE] = PLAYER_FIELD_CRIT_RESIST_DAM_RATE,	--降暴伤害倍数(万分比)
	[EQUIP_ATTR_HIT_RATE] = PLAYER_FIELD_HIT_RATE,	--命中率(万分比)
	[EQUIP_ATTR_MISS_RATE] = PLAYER_FIELD_MISS_RATE,	--闪避率(万分比)
	[EQUIP_ATTR_STUN_RATE] = PLAYER_FIELD_STUN_RATE,	--眩晕
	[EQUIP_ATTR_ROOTS_RATE] = PLAYER_FIELD_ROOTS_RATE,	--定身
	[EQUIP_ATTR_SILENCE_RATE] = PLAYER_FIELD_SILENCE_RATE,	--沉默
	[EQUIP_ATTR_CHAOS_RATE] = PLAYER_FIELD_CHAOS_RATE,	--混乱
	[EQUIP_ATTR_CHARM_RATE] = PLAYER_FIELD_CHARM_RATE,	--魅惑
	[EQUIP_ATTR_CONTROL_ENHANCE_RATE] = PLAYER_FIELD_CONTROL_ENHANCE_RATE,	--控制增强
	[EQUIP_ATTR_CONTROL_RESIST_RATE] = PLAYER_FIELD_CONTROL_RESIST_RATE,	--控制减免
	[EQUIP_ATTR_STRENGTH_ARMOR] = PLAYER_FIELD_STRENGTH_ARMOR,	--强化护甲
	[EQUIP_ATTR_DAO] = PLAYER_FIELD_DAO,						--境界
	[EQUIP_ATTR_PVP_DAMAGE_AMPLIFY_RATE] = PLAYER_FIELD_PVP_DAMAGE_AMPLIFY_RATE,	--PVP伤害增加
	[EQUIP_ATTR_PVP_DAMAGE_RESIST_RATE] = PLAYER_FIELD_PVP_DAMAGE_RESIST_RATE,	--减少PVP伤害
	[EQUIP_ATTR_PVE_DAMAGE_AMPLIFY_RATE] = PLAYER_FIELD_PVE_DAMAGE_AMPLIFY_RATE,	--增加PVE伤害
	[EQUIP_ATTR_DAMAGE_RESIST_VALUE] = PLAYER_FIELD_DAMAGE_RESIST_VALUE,	--减少伤害
}

-- 得到属性对应的区间所所表示的颜色
function GetAttrQuality(val, a, b)
	local qualitySize = 5
	local attrQuality = {a}
	
	local diff = (b - a) / qualitySize
	for i = 1, qualitySize-1 do
		table.insert(attrQuality, attrQuality[ i ] + diff)
	end
	
	-- 取整
	for i = 1, #attrQuality do
		attrQuality[ i ] = math.round(attrQuality[ i ])
	end
	
	-- 选择
	local ret = 0
	for i = #attrQuality, 1, -1 do
		local vv = attrQuality[ i ]
		if val >= vv then
			ret = i - 1
			break
		end
	end
	
	return ret
end


function onGetAvailableSectionId(passedSectionId)
	local sectionId = passedSectionId
	if sectionId == 0 then
		sectionId = tb_risk_base[ 1 ].firstSection
	else
		local nextId = tb_risk_data[sectionId].nextId
		if nextId > 0 then
			sectionId = nextId
		end
	end
	return sectionId
end

function onGetRiskTeleportInfo(playerGuid, passedSectionId)
	local sectionId = onGetAvailableSectionId(passedSectionId)
	local config = tb_risk_data[sectionId]
	local mapid = config.mapid
	local x		= config.born[ 1 ]
	local y		= config.born[ 2 ]
	local generalId = string.format("%s#%d", playerGuid, sectionId)
	
	return mapid, x, y, generalId
end

-- 是否是冒险关卡小关
function isRiskMap(mapId)
	if tb_map[mapId].inst_sub_type == INSTANCE_SUB_TYPE_RISK then-- and tb_map[mapId].is_boss_risk == 0 then
		return 1
	end
	return 0
end

function isMassBossMap(mapId)
	if tb_map[mapId].inst_sub_type == INSTANCE_SUB_TYPE_MASS_BOSS then
		return 1
	end
	return 0
end

--按key值从小到大排序的迭代器
function pairsByKeys(t)
    local a = {}
    for n in pairs(t) do
        a[#a+1] = n
    end
    table.sort(a)
    local i = 0
    return function()
        i = i + 1
        return a[i], t[a[i]]
    end
end

function AllItemsSplitResourceAndItemAndExp(itemTable)
	local resources = {}
	local items		= {}
	local exp		= 0
	
	for _, itemInfo in pairs(itemTable) do
		
		local itemId = itemInfo[ 1 ]
		local count  = itemInfo[ 2 ]
		if IsResource(itemId) then
			local moneyType = GetMoneyType(itemId)
			table.insert(resources, {moneyType, count})
		elseif itemId == Item_Loot_Exp then
			exp = count
		else
			if tb_item_template[itemId] then
				table.insert(items, {itemId, count})
			end
		end
	end
	
	return resources, items, exp
end


function MergeAttrKeysAndValues(attrKeys, attrValues)
	local ret = {}
	for i = 1, #attrKeys do
		table.insert(ret, {attrKeys[ i ], attrValues[ i ]})
	end
	
	return ret
end

function swap(a, b)
	return b, a
end

function string.ljust(str, len, char)
	char = char or ' '
	for i = len-#str, 1, -1 do
		str = char.. str
	end
	
	return str
end

function getJobIndxByGender(gender)
	return math.floor((gender - 1) / 2)
end

--[[
100111000000000
[228, 184, 128]
1001111110100101
[233, 190, 165]
128 - 191
--]]
-- 判断是否是基础中文
function checkStrIsChinese(str)
	-- 只允许基础中文(1个中文字3个byte)
	if #str % 3 ~= 0 then
		return false
	end
	
	for i = 1, #str, 3 do
		if not checkBytesIsChinese({string.byte(str, i), string.byte(str, i+1), string.byte(str, i+2)}) then
			return false
		end
	end
	
	return true
end

function checkBytesIsChinese(list)
	if #list ~= 3 then
		return false
	end
	
	local value = changeToUnitcodeIfEnabled(list)
	return checkInRange(value, {19968, 40869})
end

function changeToUnitcodeIfEnabled(list)
	if #list ~= 3 then
		return -1
	end
	
	if not checkInRange(list[ 1 ], {228, 233}) then
		return -1
	end
	
	if not checkInRange(list[ 2 ], {128, 191}) then
		return -1
	end
	
	if not checkInRange(list[ 3 ], {128, 191}) then
		return -1
	end
	
	local a = list[ 1 ] - 224
	local b = list[ 2 ] - 128
	local c = list[ 3 ] - 128
	return a * 4096 + b * 64 + c
end

function checkInRange(value, range)
	return value >= range[ 1 ] and value <= range[ 2 ]
end

function rewardsAddExtraAndClone(rewards, extra)
	extra = extra or 0
	local list = {}
	
	for _, info in ipairs(rewards) do
		local count = math.floor(info[ 2 ] * (1 + extra))
		table.insert(list, {info[ 1 ], count})
	end
	
	return list
end

--获取实际下标和偏移量
function getRealOffset(offset,seg)
	local index = math.floor(offset/seg)
	offset = offset % seg
	return index,offset
end

function print2DList(list)
	outFmtDebug("{")
	for _, element in ipairs(list) do
		outFmtDebug("%s", list1DToString(element))
	end
	outFmtDebug("}")
end

function list1DToString(list)
	local str = "{"
	if #list > 0 then
		str = str .. tostring(list[ 1 ])
	end
	for i = 2, #list do
		str = ", " .. str .. tostring(list[ i ])
	end
	str = str .. "}"
	return str
end

function getShowName(sName)
	if sName ~= "" then
		local tName = lua_string_split(sName,",")
		sName = tName[#tName]
	end
	return sName
end

function itemListToItemString(list)
	local str = ""
	if #list > 0 then
		str = str .. tostring(list[ 1 ][1]) .. ",".. tostring(list[ 1 ][2])
	end
	for i = 2, #list do
		str = str .. ", " .. tostring(list[ i ][1]) .. ",".. tostring(list[ i ][2])
	end
	
	return str
end

function GetPlayerInfo (guid)
	--
end

function isLocal3V3Open(playerInfo, show)
	local config = tb_kuafu3v3_base[ 1 ]
	-- 今天是否开活动了
	local today = false
	for _, x in ipairs(config.day) do
		if IsTodayWeekX(x) then
			today = true
			break
		end
	end
	if not today then
		if show then
			playerInfo:CallOptResult(OPRATE_TYPE_ATHLETICS, ATHLETICS_OPERATE_NO_OPEN)
		end
		return false
	end
	
	-- 是否在活动时间
	local curtime = os.time()
	local intime = false
	for _,v in ipairs(config.activetime) do
		local t1 = GetTodayHMSTimestamp(v[1],v[2],0)
		local t2 = GetTodayHMSTimestamp(v[3],v[4],0)
		if curtime >= t1 and curtime <= t2 then
			intime = true
			break
		end
	end
	if not intime then
		if show then
			playerInfo:CallOptResult(OPRATE_TYPE_ATHLETICS, ATHLETICS_OPERATE_NO_OPEN)
		end
		return false
	end
	
	return true
end

local equip_pos_name = {"武器", "衣服", "护手", "腰带", "鞋子", "头饰", "项链", "手镯", "戒指", "腰坠"}
function getPosName(pos)
	if equip_pos_name[pos] then
		return equip_pos_name[pos]
	else
		return ""
	end
	
end


function getUid(account)
	local s1 = string.split(account, '_')
	return s1[#s1]
end

function getServerId(serverInfo)
	local s1 = string.split(serverInfo, '_')
	return tonumber(s1[#s1])
end

function getServerInfo(serverId)
	local platformId = globalGameConfig:GetPlatformID()
	return platformId.."_"..serverId
end