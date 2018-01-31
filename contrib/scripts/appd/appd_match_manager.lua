
local HALF_3V3 = 3

function OnLocal3V3MatchPush(guid)
	if not app.objMgr:IsPlayerGuid(guid) and not app.objMgr:IsGroupGuid(guid) then
		return
	end
	
	if app.objMgr:IsGroupGuid(guid) then
		local guidObj = app.objMgr:getObj(guid)
		if guidObj then
			if not guidObj:IsFullMatch() then
				return false
			end
		end
	end
	Local3v3MatchPush(guid)
	
	return true
end

function OnLocal3V3MatchRemove(guid)
	Local3v3MatchRemove(guid)
end

function OnLocal3V3Matching()
	checkPreparation()
	
	local matchList = GetLocal3v3MatchList()
	local groupMatchInfo = {}
	local playerMatchInfo = {}
	
	for _, matchInfo in ipairs(matchList) do
		local timestamp = matchInfo[ 1 ]
		local guid = matchInfo[ 2 ]
		if app.objMgr:IsPlayerGuid(guid) then
			local guidObj = app.objMgr:getObj(guid)
			if guidObj and guidObj:isLogined() then
				table.insert(playerMatchInfo, {guidObj, timestamp})
			else
				OnLocal3V3MatchRemove(guid)
			end
		elseif app.objMgr:IsGroupGuid(guid) then
			local guidObj = app.objMgr:getObj(guid)
			if guidObj and guidObj:IsFullMatch() then
				table.insert(groupMatchInfo, {guidObj, timestamp})
			else
				OnLocal3V3MatchRemove(guid)
			end
		else
			-- 不存在删掉
			OnLocal3V3MatchRemove(guid)
		end
	end
	
	----------------- 进行排序 -----------------
	mi_sort(groupMatchInfo, function(a, b)
		return a[ 2 ] < b[ 2 ]
	end)
	
	mi_sort(playerMatchInfo, function(a, b)
		return a[ 2 ] < b[ 2 ]
	end)
	
	local teamCount = 2
	-- 队伍之间优先匹配
	while #groupMatchInfo >= teamCount do
		local playerList = {}
		for i = teamCount, 1, -1 do
			local groupInfo = groupMatchInfo[ i ][ 1 ]
			local list = groupInfo:GetGroupPlayerList()
			table.insertTo(playerList, list)
			OnLocal3V3MatchRemove(groupInfo:GetGuid())
		end
		
		for i = teamCount, 1, -1 do
			table.remove(groupMatchInfo, i)
		end
		
		onMatched(playerList)
	end
	
	-- 队伍和人匹配
	-- 只有在队伍匹配操作10秒后才能匹配人
	local now = os.time()
	local last = 10
	local half = HALF_3V3
	if #groupMatchInfo > 0 then
		local g = groupMatchInfo[ 1 ]
		-- 过了匹配时间且有3个人
		if now > last + g[ 2 ] and #playerMatchInfo >= half then
			local playerList = {}
			local groupInfo = g[ 1 ]
			local list = groupInfo:GetGroupPlayerList()
			table.insertTo(playerList, list)
			OnLocal3V3MatchRemove(groupInfo:GetGuid())
			
			for i = half, 1, -1 do
				local playerInfo = playerMatchInfo[ i ][ 1 ]
				table.insert(playerList, playerInfo)
				OnLocal3V3MatchRemove(playerInfo:GetGuid())
			end
			
			for i = half, 1, -1 do
				table.remove(playerMatchInfo, i)
			end
			
			onMatched(playerList)
		end
	end
	
	
	local count = half * 2
	-- 匹配个人
	while #playerMatchInfo >= count do
		local playerList = {}

		for i = count, 1, -1 do
			local playerInfo = playerMatchInfo[ i ][ 1 ]
			table.insert(playerList, playerInfo)
			OnLocal3V3MatchRemove(playerInfo:GetGuid())
		end
		
		for i = count, 1, -1 do
			table.remove(playerMatchInfo, i)
		end
		
		onMatched(playerList)
	end
end

local MATCH_STATE_DECLINE		= 255
local MATCH_STATE_NONE			= 0
local MATCH_STATE_ACCEPT		= 1

local prepareList = {}

function has3v3Prepared(key)
	return getPreparedCuInfo(key) ~= nil
end

function getPreparedCuInfo(key)
	local cuInfo = GetLocal3v3PrepareCuInfo(key)
	return cuInfo
end

function setPreparedCuInfo(key, cuInfo)
	if cuInfo then
		for _, playerData in ipairs(cuInfo) do
			preparedOnePlayerInfo(key, playerData)
		end
	else
		Local3v3PrepareCancel(key)
	end
end

function preparedOnePlayerInfo(key, playerData)
	Local3v3PreparePush(key, playerData[ 2 ], playerData[ 1 ])
end

function getAllPreparedCuInfo()
	local preparedQueue = GetLocal3v3PrepareList()
	return preparedQueue
end

function onPrepareLeave(key, state)
	if not has3v3Prepared(key) then
		return
	end
	
	local cuInfo = getPreparedCuInfo(key)
	setPreparedCuInfo(key, nil)
	for _, playerData in ipairs(cuInfo) do
		local guid = playerData[ 2 ]
		local playerInfo = app.objMgr:getObj(guid)
		if playerInfo and playerInfo:isLogined() then
			playerInfo:SetStr(PLAYER_STRING_FIELD_LOCAL_3V3_GENERALID, '')
			if state ~= MATCH_STATE_ACCEPT then
				playerInfo:SomeOneDeclineMatch()
			end
		end
	end
end

-- 匹配
function on3v3Match(guid, key)
--	local key = playerInfo:GetStr(PLAYER_STRING_FIELD_LOCAL_3V3_GENERALID)
	if string.len(key) > 0 and has3v3Prepared(key) then
		return false
	end
	OnLocal3V3MatchPush(guid)
	return true
end

-- 取消匹配
function on3v3CancelMatch(playerInfo, guid)
	OnLocal3V3MatchRemove(guid)
	playerInfo:call_kuafu_3v3_cancel_match(KUAFU_TYPE_FENGLIUZHEN)
end

-- oper, 0:decline, 1:accept
function onPrepareOperate(playerInfo, oper)
	local key = playerInfo:GetStr(PLAYER_STRING_FIELD_LOCAL_3V3_GENERALID)
	if not has3v3Prepared(key) then
		return
	end
	
	local cuInfo = getPreparedCuInfo(key)
	for _, playerData in ipairs(cuInfo) do
		local guid = playerData[ 2 ]
		if playerInfo:GetGuid() == guid then
			local state = MATCH_STATE_DECLINE
			if oper == 1 then
				state = MATCH_STATE_ACCEPT
			end
			playerData[ 1 ] = state
			-- 设置回去
			preparedOnePlayerInfo(key, playerData)
		end
	end
	
	if not sendCuPreparation(key, cuInfo) then
		onPrepareLeave(key)
	end
end

function onMatched(playerInfoList)
	outFmtDebug("########  onMatched")
	-- 匹配到了 进行准备
	local cuInfo = {}
	local general_id = string.format("flz_%s%d", playerInfoList[ 1 ]:GetGuid(), os.time())
	for _, playerInfo in ipairs(playerInfoList) do
		playerInfo:SetStr(PLAYER_STRING_FIELD_LOCAL_3V3_GENERALID, general_id)
		table.insert(cuInfo, {MATCH_STATE_NONE, playerInfo:GetGuid()})
	end
	cuInfo.timestamp = os.time()
	
	setPreparedCuInfo(general_id, cuInfo)
end

function checkPreparation()
	local removeList = {}
	local now = os.time()
	local wait = 30
	local prepareQueue = getAllPreparedCuInfo()
	for key, cuInfo in pairs(prepareQueue) do
		-- 其中一个离线了或者超过等待时限
		if not sendCuPreparation(key, cuInfo) or cuInfo.timestamp + wait < now then
			table.insert(removeList, {key})
		else
			local state = checkCuAllPrepared(cuInfo)
			-- 全部点同意了
			if state == MATCH_STATE_ACCEPT then
				enter3V3Scene(cuInfo)
			end

			if state == MATCH_STATE_DECLINE or state == MATCH_STATE_ACCEPT then
				table.insert(removeList, {key, state})
			end
		end
	end

	for _, info in ipairs(removeList) do
		onPrepareLeave(info[1], info[2])
	end
end

-- 进入场景
function enter3V3Scene(cuInfo)
	local config = tb_kuafu3v3_base[ 1 ].bornPos
	for i = 1, #cuInfo do
		local camp = 1
		if i > HALF_3V3 then
			camp = 2
		end
		local playerData = cuInfo[ i ]
		local state = playerData[ 1 ]
		local guid = playerData[ 2 ]
		local playerInfo = app.objMgr:getObj(guid)
		if playerInfo and playerInfo:isLogined() then
			playerInfo:SetUInt32(PLAYER_INT_FIELD_VIRTUAL_CAMP, camp)
			local pos = config[camp]
			-- 设置玩家的虚拟阵营
			local x = randInt(-3, 3) + pos[ 1 ]
			local y = randInt(-3, 3) + pos[ 2 ]
			local mapid = tb_kuafu3v3_base[ 1 ].mapid
			local gerneralId = playerInfo:GetStr(PLAYER_STRING_FIELD_LOCAL_3V3_GENERALID)
			--outFmtDebug("========= guid = %s (%d, %d) mapid = %d general_id = %s",  playerInfo:GetGuid(), x, y, mapid, gerneralId)
			
			playerInfo:AddActiveItem(VITALITY_TYPE_LOCAL_3V3)
			call_appd_teleport(playerInfo:GetScenedFD(), playerInfo:GetGuid(), x, y, mapid, gerneralId)
		end
	end
end

function sendCuPreparation(key, cuInfo)
	local playerInfoList = {}
	local wait_info = {}
	for _, playerData in ipairs(cuInfo) do
		local state = playerData[ 1 ]
		local guid = playerData[ 2 ]
		local playerInfo = app.objMgr:getObj(guid)
		if playerInfo and playerInfo:isLogined() then
			table.insert(wait_info, {state, playerInfo:GetName()})
			table.insert(playerInfoList, playerInfo)
		else
			return false
		end
	end
	
	broadcastPrepareInfo(playerInfoList, wait_info)
	
	return true
end

function checkCuAllPrepared(cuInfo)
	local ret = MATCH_STATE_ACCEPT
	for _, playerData in ipairs(cuInfo) do
		local state = playerData[ 1 ]
		if state ~= MATCH_STATE_ACCEPT then
			if ret ~= MATCH_STATE_DECLINE then
				ret = state
			end
		end
	end
	
	return ret
end

function broadcastPrepareInfo(playerInfoList, wait_info)
	for _, playerInfo in ipairs(playerInfoList) do
		playerInfo:OnSendWaitInfo(wait_info)
	end
end