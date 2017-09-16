InstanceKuafu3v3 = class("InstanceKuafu3v3", InstanceInstBase)

InstanceKuafu3v3.Name = "InstanceKuafu3v3"
InstanceKuafu3v3.exit_time = 30
InstanceKuafu3v3.Time_Out_Fail_Callback = "timeoutCallback"
-- ȫͼ�ɼ�
InstanceKuafu3v3.broadcast_nogrid = 1

function InstanceKuafu3v3:ctor(  )
	
end

--��ʼ���ű�����
function InstanceKuafu3v3:OnInitScript()
	InstanceInstBase.OnInitScript(self) --���û���
	
	-- �ȸ���һ����ʼ�Ľ���ʱ��, Ϊ�˱�֤�����в����ͷŵ�
	-- self:SetMapEndTime(os.time() + 600)
	
	self:OnTaskStart()
	self:AddCountDown()
end

function InstanceKuafu3v3:AddCountDown()
	local timestamp = os.time() + tb_kuafu3v3_base[ 1 ].cd
	self:SetMapStartTime(timestamp)
	self:AddTimeOutCallback("countdown", timestamp)
end

-- ����ʱ����
function InstanceKuafu3v3:countdown()
	-- ����ˢ�¶�ʱ��
	mapLib.AddTimer(self.ptr, 'OnBuffRefresh', tb_kuafu3v3_base[ 1 ].interval * 1000)
end

-- ���ʽ��ʼ
function InstanceKuafu3v3:OnTaskStart()
	local timestamp = os.time() +  tb_kuafu3v3_base[ 1 ].last + tb_kuafu3v3_base[ 1 ].cd
	-- ������ʱ��
	self:SetMapQuestEndTime(timestamp)
	-- ����ʱ�䳬ʱ�ص�
	self:AddTimeOutCallback(self.Time_Out_Fail_Callback, timestamp)
end

-- ˢ��buff
function InstanceKuafu3v3:OnBuffRefresh()
	-- ����ˢ�´���
	local times = self:GetMapReserveValue1()
	if times < tb_kuafu3v3_base[ 1 ].times then
		self:SetMapReserveValue1(times+1)
	end
	
	-- ˢ�°�ԭ������ɾ��
	local allGameObjects = mapLib.GetAllGameObject(self.ptr)
	for _, gameobject in pairs(allGameObjects) do
		mapLib.RemoveWorldObject(self.ptr, gameobject)
	end
	
	-- ˢ���µ�
	local indice = GetRandomIndexTable(#tb_buff_kuafu3v3, #tb_kuafu3v3_base[ 1 ].buffPos)
	for i = 1, #indice do
		local pos = tb_kuafu3v3_base[ 1 ].buffPos[ i ]
		local indx = indice[ i ]
		local entry = tb_buff_kuafu3v3[indx].gameobject_id
		mapLib.AddGameObject(self.ptr, entry, pos[ 1 ], pos[ 2 ], GO_GEAR_STATUS_END)
	end
	
	app:CallOptResult(self.ptr, OPRATE_TYPE_ATHLETICS, ATHLETICS_OPERATE_BUFF_OCCUR)
	
	return self:GetMapReserveValue1() < tb_kuafu3v3_base[ 1 ].times
end

-- ����ʧ���˳�
function InstanceKuafu3v3:timeoutCallback()
	self:SyncResultToWeb()
	self:SetMapState(self.STATE_FINISH)
	return false
end

--������״̬�����仯ʱ�䴥��
function InstanceKuafu3v3:OnSetState(fromstate,tostate)
	if tostate == self.STATE_FINISH then
		self:RemoveTimeOutCallback(self.Time_Out_Fail_Callback)
		
		--10s���������
		local timestamp = os.time() + InstanceKuafu3v3.exit_time
		
		self:AddTimeOutCallback(self.Leave_Callback, timestamp)
		self:SetMapEndTime(timestamp)
	end
end

-- �ж��Ƿ����˳�����
function InstanceKuafu3v3:DoPlayerExitInstance(player)
	-- ֱ�ӻ�ԭ��
	local playerInfo = UnitInfo:new {ptr = player}
	local login_fd = serverConnList:getLogindFD()
	call_scene_login_to_kuafu_back(login_fd, playerInfo:GetPlayerGuid())
	return 0	--����1�Ļ�Ϊ�����˳�������0�����˳�
end

--��Ҽ����ͼ
function InstanceKuafu3v3:OnJoinPlayer(player)
	
	InstanceInstBase.OnJoinPlayer(self, player)
	
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() then
		--�����˻�������ֱ�ӵ���ȥ
		local login_fd = serverConnList:getLogindFD()
		call_scene_login_to_kuafu_back(login_fd, playerInfo:GetPlayerGuid())
		return
	end
	
	-- �����ظ�����
	if self:findIndexByName(playerInfo:GetName()) > -1 then
		local login_fd = serverConnList:getLogindFD()
		call_scene_login_to_kuafu_back(login_fd, playerInfo:GetPlayerGuid())
		return
	end
	
	-- ��������
	local emptyIndex = self:findIndexByName()
	if emptyIndex > -1 then
		local strStart = KUAFU_3V3_FIELDS_STR_INFO_START + emptyIndex * MAX_KUAFU_3V3_STR_COUNT
		local intStart = KUAFU_3V3_FIELDS_INT_INFO_START + emptyIndex * MAX_KUAFU_3V3_INT_COUNT
		
		self:SetStr(strStart + KUAFU_3V3_PLAYER_NAME, playerInfo:GetName())
		self:SetStr(strStart + KUAFU_3V3_PLAYER_GUID, playerInfo:GetPlayerGuid())
		
		self:SetByte(intStart + KUAFU_3V3_PLAYER_SHOW_INFO, 0, playerInfo:GetGender())
		self:SetByte(intStart + KUAFU_3V3_PLAYER_SHOW_INFO, 1, 100)
		self:SetUInt16(intStart + KUAFU_3V3_PLAYER_SHOW_INFO, 1, playerInfo:GetLevel())
		self:SetByte(intStart + KUAFU_3V3_PLAYER_SETTLEMENT, 2, playerInfo:GetVirtualCamp())
		playerInfo:SetToGroupMode(''..playerInfo:GetVirtualCamp())
	end
end

-- ������ֶ�Ӧ��λ��, ''��ʾ������ѯ��λλ��
function InstanceKuafu3v3:findIndexByName(name)
	name = name or ''
	local start = KUAFU_3V3_FIELDS_STR_INFO_START
	for i = 0, MAX_KUAFU_3V3_COUNT-1 do
		if self:GetStr(start+KUAFU_3V3_PLAYER_NAME) == name then
			return i
		end
		start = start + MAX_KUAFU_3V3_STR_COUNT
	end
	
	return -1
end

-- �Ƿ�ĳ����Ӫȫ������
function InstanceKuafu3v3:IsOneCmapAllDead()
	return self:GetWinCmap() > 0
end

-- ���ʤ������Ӫ
function InstanceKuafu3v3:GetWinCmap()
	local ret = {}
	
	local tmp = {}
	local start = KUAFU_3V3_FIELDS_INT_INFO_START
	for i = 0, MAX_KUAFU_3V3_COUNT-1 do
		if self:GetByte(start + KUAFU_3V3_PLAYER_SETTLEMENT, 1) == 0 then
			local camp = self:GetByte(start + KUAFU_3V3_PLAYER_SETTLEMENT, 2)
			if camp > 0 and not tmp[camp] then
				tmp[camp] = 1
				table.insert(ret, camp)
			end
		end
		start = start + MAX_KUAFU_3V3_INT_COUNT
	end
	
	-- ƽ��
	if #ret == 2 or #ret == 0 then
		return 0
	end
	-- ʤ��
	return ret[ 1 ]
end

--����������󴥷�()
function InstanceKuafu3v3:OnPlayerDeath(player)
	-- ���״̬�Ѿ��ı�, ��ʹ����Ҳ���ٸ���ʱ��
	if self:GetMapState() ~= self.STATE_START then
		return
	end
	
	-- ��������״̬
	local playerInfo = UnitInfo:new{ptr = player}
	local indx = self:findIndexByName(playerInfo:GetName())
	local intStart = KUAFU_3V3_FIELDS_INT_INFO_START + indx * MAX_KUAFU_3V3_INT_COUNT
	self:SetByte(intStart + KUAFU_3V3_PLAYER_SETTLEMENT, 1, 1)
	
	-- �ж�ĳ����Ӫȫ������
	if self:IsOneCmapAllDead() then
		self:SyncResultToWeb()
		self:SetMapState(self.STATE_FINISH)
	end
end

-- ͬ�����ݵ�������
function InstanceKuafu3v3:SyncResultToWeb()
	local sendInfo = {}
	
	-- ��ʤ����Ӫ (0:��ʾƽ��)
	local win_camp = self:GetWinCmap()
	-- ȫ����ѵ��±�
	local bestIndx = self:GetTheBest()
	-- ˫����Ӫ������
	local topThree = {self:GetTopThree(1), self:GetTopThree(2)}
	
	-- �˺���Ӧ�Ļ���
	local damageScoreConfig = tb_kuafu3v3_base[ 1 ].damageScore
	
	local info = {}
	local intstart = KUAFU_3V3_FIELDS_INT_INFO_START
	local strstart = KUAFU_3V3_FIELDS_STR_INFO_START
	for i = 0, MAX_KUAFU_3V3_COUNT-1 do
		local camp = self:GetByte(intstart + KUAFU_3V3_PLAYER_SETTLEMENT, 2)
		
		-- ȡ��ʤ������
		local score = tb_kuafu3v3_base[ 1 ].resultScore[ 2 ]
		if camp == win_camp then
			score = tb_kuafu3v3_base[ 1 ].resultScore[ 1 ]
		end
		
		-- ��ɱ����
		local killed = self:GetByte(intstart + KUAFU_3V3_PLAYER_SETTLEMENT, 0)
		local scorePerKill = tb_kuafu3v3_base[ 1 ].scorePerKill
		score = score + killed * scorePerKill
		
		-- �˺�����
		local config = topThree[camp]
		if config and config[ i ] then
			score = score + damageScoreConfig[config[ i ]]
		end
		
		-- ��ʤ����
		local player_guid = self:GetStr(strstart + KUAFU_3V3_PLAYER_GUID)
		local player = mapLib.GetPlayerByPlayerGuid(self.ptr, player_guid)
		if player then
			local playerInfo = UnitInfo:new {ptr = player}
			local prev = playerInfo:GetKuafu3v3TrendInfo()
			if prev > 0 and camp == win_camp then
				score = score + tb_kuafu3v3_base[ 1 ].winStreakScore
			end
		end
		
		-- �Ƿ�ȫ�����
		if i == bestIndx then
			self:SetByte(intstart + KUAFU_3V3_PLAYER_HONOR, 1, 1)
			score = score + tb_kuafu3v3_base[ 1 ].bestScore
		end
		
		-- ��������
		local honor = tb_kuafu3v3_base[ 1 ].resultHonor[ 2 ]
		if camp == win_camp then
			honor = tb_kuafu3v3_base[ 1 ].resultHonor[ 1 ]
		end
		self:SetByte(intstart + KUAFU_3V3_PLAYER_HONOR, 0, honor)
		
		-- ���û���
		self:SetByte(intstart + KUAFU_3V3_PLAYER_SETTLEMENT, 3, score)
		
		local result = 0
		-- Ϊƽ��
		if win_camp > 0 then
			if camp == win_camp then
				result = 1
			else
				result = -1
			end
		end
		
		-- �����Ҵ���
		if player_guid and string.len(player_guid) > 0 then
			-- result(0:ƽ��, 1:ʤ��, -1:ʧ��)
			table.insert(sendInfo, {player_guid, score, honor, result})
		end
		
		intstart = intstart + MAX_KUAFU_3V3_INT_COUNT
		strstart = strstart + MAX_KUAFU_3V3_STR_COUNT
	end
	
	local retInfo = {}
	-- Ȼ��ͬ����web
	for _, info in pairs(sendInfo) do
		table.insert(retInfo, string.join(",", info))
	end
	
	
	local url = globalGameConfig:GetExtWebInterface().."world_3v3/match_result"
	local data = {}
	-- ������3v3����ƥ�����Ϣ
	data.ret = string.join(";", retInfo)
	data.open_time = 1
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		outFmtDebug("response = %s", tostring(response))
	end)
end

-- ͨ����Ӫ������ǰ3�����
function InstanceKuafu3v3:GetTopThree(win_camp)
	win_camp = win_camp or 0
	
	local info = {}
	local intstart = KUAFU_3V3_FIELDS_INT_INFO_START
	for i = 0, MAX_KUAFU_3V3_COUNT-1 do
		local damage = self:GetDouble(intstart + KUAFU_3V3_PLAYER_DAMAGE)
		local camp = self:GetByte(intstart + KUAFU_3V3_PLAYER_SETTLEMENT, 2)
		if win_camp == 0 or win_camp == camp then
			table.insert(info, {indx = i, damage=damage})
		end

		intstart = intstart + MAX_KUAFU_3V3_INT_COUNT
	end
	
	table.sort(info, function(a, b)
		return a.damage > b.damage
	end)
	
	-- �±��Ӧ������
	local ret = {}
	-- �˺�Ϊ0�Ĳ���
	for i = 1, #info do
		if info[ i ].damage == 0 then
			break
		end
		ret[info[ i ].indx] = i
	end
	
	return ret
end

-- ���ȫ�����
function InstanceKuafu3v3:GetTheBest(win_camp)
	win_camp = win_camp or 0
	local info = {}
	local intstart = KUAFU_3V3_FIELDS_INT_INFO_START
	local strstart = KUAFU_3V3_FIELDS_STR_INFO_START
	for i = 0, MAX_KUAFU_3V3_COUNT-1 do
		local killed = self:GetByte(intstart + KUAFU_3V3_PLAYER_SETTLEMENT, 0)
		local damage = self:GetDouble(intstart + KUAFU_3V3_PLAYER_DAMAGE)
		local player_guid = self:GetStr(strstart + KUAFU_3V3_PLAYER_GUID)
		local camp = self:GetByte(intstart + KUAFU_3V3_PLAYER_SETTLEMENT, 2)
		local player = mapLib.GetPlayerByPlayerGuid(self.ptr, player_guid)
		local force = 1000000000000
		if player then
			local playerInfo = UnitInfo:new {ptr = player}
			force = playerInfo:GetForce()
		end
		if win_camp == 0 or win_camp == camp then
			table.insert(info, {indx = i, killed=killed, damage=damage, force=force})
		end

		intstart = intstart + MAX_KUAFU_3V3_INT_COUNT
		strstart = strstart + MAX_KUAFU_3V3_STR_COUNT
	end
	
	table.sort(info, function(a, b)
		if a.killed == b.killed then
			if a.damage == b.damage then
				return a.force < b.force
			end
			return a.damage > b.damage
		end
		return a.killed > b.killed
	end)
	
	return info[ 1 ].indx
end

-- �����
function InstanceKuafu3v3:DoAfterRespawn(unit_ptr)
	local unitInfo = UnitInfo:new{ptr = unit_ptr}
	-- ���޵�����buff
	unitLib.AddBuff(unit_ptr, BUFF_INVINCIBLE, unit_ptr, 1, MAX_BUFF_DURATION)
	unitLib.AddBuff(unit_ptr, BUFF_INVISIBLE, unit_ptr, 1, MAX_BUFF_DURATION)
end

-- ����ܵ�ʵ���˺�(������ʾ��Ѫ)
function InstanceKuafu3v3:OnPlayerHurt(killer, player, damage)
	local killerInfo = UnitInfo:new{ptr = killer}
	local targetInfo = UnitInfo:new{ptr = player}
	
	-- �������Ѫ��
	local indx = self:findIndexByName(targetInfo:GetName())
	local rate = math.floor((targetInfo:GetHealth() - damage) * 100 / targetInfo:GetMaxHealth())
	local intStart = KUAFU_3V3_FIELDS_INT_INFO_START + indx * MAX_KUAFU_3V3_INT_COUNT
	rate = math.min(rate, 100)
	self:SetByte(intStart + KUAFU_3V3_PLAYER_SHOW_INFO, 1, rate)
	-- ��������˺�
	if damage > 0 then
		indx = self:findIndexByName(killerInfo:GetName())
		intStart = KUAFU_3V3_FIELDS_INT_INFO_START + indx * MAX_KUAFU_3V3_INT_COUNT
		self:AddDouble(intStart + KUAFU_3V3_PLAYER_DAMAGE, damage)
	end
	
	return 0
end

function InstanceKuafu3v3:OnPlayerKilled(player, killer)
	local killerInfo = UnitInfo:new{ptr = killer}
	local playerInfo = UnitInfo:new{ptr = player}
	
	-- ��ɱ�߼ӻ�ɱ��
	local indx1 = self:findIndexByName(killerInfo:GetName())
	local intStart = KUAFU_3V3_FIELDS_INT_INFO_START + indx1 * MAX_KUAFU_3V3_INT_COUNT
	self:AddByte(intStart + KUAFU_3V3_PLAYER_SETTLEMENT, 0, 1)
	
	-- ��ɱ���±�
	local indx2 = self:findIndexByName(playerInfo:GetName())
	
	-- ֪ͨ�����˻�ɱ��Ϣ
	local strstart = KUAFU_3V3_FIELDS_STR_INFO_START
	for i = 0, MAX_KUAFU_3V3_COUNT-1 do
		local player_guid = self:GetStr(strstart + KUAFU_3V3_PLAYER_GUID)
		local player = mapLib.GetPlayerByPlayerGuid(self.ptr, player_guid)
		if player then
			local playerInfo = UnitInfo:new {ptr = player}
			playerInfo:call_kuafu_3v3_kill_detail(indx1, indx2)
		end
		
		strstart = strstart + MAX_KUAFU_3V3_STR_COUNT
	end
	
	-- self:SetUInt16(KUAFU_3V3_FIELDS_INT_LAST_KILL, 0, indx1)
	-- self:SetUInt16(KUAFU_3V3_FIELDS_INT_LAST_KILL, 1, indx2)
	
	return 0
end

--������뿪ʱ����
function InstanceKuafu3v3:OnLeavePlayer( player, is_offline)
	-- ����������˾Ͳ����д���
	if self:GetMapState() == self.STATE_FINISH then
		return
	end
	-- ��������״̬
	local playerInfo = UnitInfo:new{ptr = player}
	local indx = self:findIndexByName(playerInfo:GetName())
	local intStart = KUAFU_3V3_FIELDS_INT_INFO_START + indx * MAX_KUAFU_3V3_INT_COUNT
	if self:GetByte(intStart + KUAFU_3V3_PLAYER_SETTLEMENT, 1) == 0 then
		self:SetByte(intStart + KUAFU_3V3_PLAYER_SETTLEMENT, 1, 1)
	end
	
	-- �ж�ĳ����Ӫȫ������
	if self:IsOneCmapAllDead() then
		self:SyncResultToWeb()
		self:SetMapState(self.STATE_FINISH)
	end
end

--ʹ����Ϸ����֮ǰ
--����1�Ļ��ͼ���ʹ����Ϸ���󣬷���0�Ļ��Ͳ�ʹ��
function InstanceKuafu3v3:OnBeforeUseGameObject(user, go, go_entryid, posX, posY)
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
function InstanceKuafu3v3:OnUseGameObject(user, go, go_entryid, posX, posY)
	-- �ж϶�Ӧ��������buff
	for _, obj in ipairs(tb_buff_kuafu3v3) do
		if obj.gameobject_id == go_entryid then
			local effects = obj.type_effect
			for _, effect in pairs(effects) do
				local buffId = effect[ 1 ]
				local lv = effect[ 2 ]
				local duration = tb_buff_template[buffId].duration
				--SpelladdBuff(user, buffId, user, lv, duration)
			end
			break
		end
	end
	
	-- ��Ҫɾ������
	mapLib.RemoveWorldObject(self.ptr, go)
	
	return 1	
end


-- ��ͼ��Ҫ�����ʱҪ������
function InstanceKuafu3v3:IsNeedTeleportWhileMapClear(player)
	local playerInfo = UnitInfo:new {ptr = player}
	local login_fd = serverConnList:getLogindFD()
	call_scene_login_to_kuafu_back(login_fd, playerInfo:GetPlayerGuid())
	return 0
end

return InstanceKuafu3v3