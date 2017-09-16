local security = require("base/Security")


local sub = "world_3v3"

function PlayerInfo:OnCheckWorld3v3Match()
	-- ƥ��Ĳ���3v3
	if not app:IsKuafuTypeMatching(self:GetGuid(), KUAFU_TYPE_FENGLIUZHEN) then
		return
	end
	
	local url = string.format("%s%s/check_match", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	-- ������3v3����ƥ�����Ϣ
	data.player_guid = self:GetPlayerMatchKey()
	data.open_time = 1
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("%s OnCheckWorld3v3Match response = %s", self:GetGuid(), response)
		end
		
		local dict = nil
		security.call(
			--try block
			function()
				dict = json.decode(response)
			end
		)
		
		
		if dict then
			outFmtDebug("%s OnCheckWorld3v3Match result %d %s", self:GetGuid(), dict.ret, dict.msg)
			-- ƥ�䵽��
			if dict.ret == 0 then
				local login_fd = serverConnList:getLogindFD()
				local guid = self:GetGuid()
				-- dict.enter_info = json.decode(dict.enter_info)
				local enter_info = dict.enter_info
				if type(enter_info) == "string" then
					enter_info = json.decode(enter_info)
				end
				local pos = enter_info.pos
				local war_id = enter_info.war_id
				local battle_server = enter_info.battle_server
				call_appd_login_to_send_kuafu_info(login_fd, guid, war_id, pos, battle_server)
				-- �Ѿ�ƥ�䵽��
				app:SetMatchingKuafuType(self:GetGuid(), nil)
				-- �������ڽ��п����־
				self:KuafuMarked(KUAFU_TYPE_FENGLIUZHEN)
				
				-- ���ӽ������
				local instMgr = self:getInstanceMgr()
				instMgr:add3v3EnterTimes()
			-- timeoutȡ��ƥ��
			elseif dict.ret == 2 then
				outFmtDebug("== player on cancel match %s", self:GetGuid())
				self:OnCancelMatch(KUAFU_TYPE_FENGLIUZHEN)
			-- ����δ׼����
			elseif dict.ret == 3 then
				self:SomeOneDeclineMatch()
			-- ׼�����
			elseif dict.ret == 4 then
				local wait_info = dict.wait_info
				if type(wait_info) == "string" then
					wait_info = json.decode(wait_info)
				end
				self:OnSendWaitInfo(wait_info)
			end
		end
	end)
end


-- ȡ��ƥ��3v3
function PlayerInfo:OnCancelWorld3v3MatchBeforeOffline()
	-- ƥ��Ĳ���3v3
	if not app:IsKuafuTypeMatching(self:GetGuid(), KUAFU_TYPE_FENGLIUZHEN) then
		return
	end
	
	local url = string.format("%s%s/cancel_match", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	data.player_guid = self:GetPlayerMatchKey()
	data.open_time = 1
	self:OnCancelMatch(KUAFU_TYPE_FENGLIUZHEN)
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("cancel_match response = %s", response)
		end
	end)
end


-- ����ƥ��3v3
function PlayerInfo:OnWorld3v3Match()
	outFmtDebug("PlayerInfo:OnWorld3v3Match")
	-- �Ѿ���ƥ��������
	if app:IsInKuafuTypeMatching(self:GetGuid()) then
		outFmtDebug("OnWorld3v3Match IsInKuafuTypeMatching")
		return false
	end
	app.world_3v3_team_dict[self:GetGuid()] = {self:GetGuid()}
	app.world_3v3_player_team[self:GetGuid()] = self:GetGuid()
	return self:OnWorld3v3GroupMatch()
end

-- ����ƥ��3v3
function PlayerInfo:OnWorld3v3GroupMatch()
	outFmtDebug("PlayerInfo:OnWorld3v3GroupMatch")
	-- �ӳ����ܽ���ƥ��, ���ǵĲ��ý�
	local group_guid = self:GetGuid()
	if app.world_3v3_player_team[self:GetGuid()] ~= group_guid then
		outFmtDebug("OnWorld3v3GroupMatch is not captain")
		return false
	end
	
	-- �Ѿ��ڿ����
	if self:IsKuafuing() then
		outFmtDebug("OnWorld3v3GroupMatch is IsKuafuing")
		return false
	end
	
	-- �Ѿ���ƥ��������
	if app:IsInKuafuTypeMatching(self:GetGuid()) then
		outFmtDebug("OnWorld3v3GroupMatch IsInKuafuTypeMatching")
		return false
	end
	
	local teamdict = {}
	table.insert(teamdict, string.format("%s,%d", self:GetGuid(), self:GetWorld3v3MatchValue()))
	
	local group_info = app.world_3v3_team_dict[group_guid]
	for i = 2, #group_info do
		local player_guid = group_info[ i ]
		local player = app.objMgr:getObj(player_guid)
		table.insert(teamdict, string.format("%s,%d", player:GetGuid(), player:GetWorld3v3MatchValue()))
	end
	
	local url = string.format("%s%s/match", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	data.group_guid = self:GetPlayerMatchKey()
	data.open_time = 1
	data.team_info = string.join(",", teamdict)
	
	app:SetMatchingKuafuType(self:GetGuid(), KUAFU_TYPE_FENGLIUZHEN)
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("%s OnWorld3v3GroupMatch response = %s", self:GetGuid(), response)
		end
		
		local dict = nil
		security.call(
			--try block
			function()
				dict = json.decode(response)
			end
		)
		
		if dict then
			outFmtDebug("OnWorld3v3GroupMatch result %d %s %s", dict.ret, dict.msg, self:GetGuid())
		end
	end)
	
	return true
end


-- �����3v3����
function PlayerInfo:CheckWorld3v3Reward()
	local url = string.format("%s%s/check_match_result", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	data.player_guid = self:GetGuid()
	data.open_time = 1
	
	local askguid = self:GetGuid()
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("CheckWorld3v3Reward response = %s", response)
		end
		
		local dict = nil
		security.call(
			--try block
			function()
				dict = json.decode(response)
			end
		)
		if dict then
			outFmtDebug("%d %s %s", dict.ret, dict.msg, askguid)
			
			if dict.ret == 0 then
				local data = dict.details
				if type(data) == "string" then
					data = json.decode(data)
				end
				self:AddKuafu3v3Score(data.score)
				
				-- ����
				local questMgr = self:getQuestMgr()
				questMgr:OnUpdate(QUEST_TARGET_TYPE_JOIN_KUAFU_3V3)
				-- data.honor
				if data.result == 1 then
					self:Kuafu3v3Win()
					questMgr:OnUpdate(QUEST_TARGET_TYPE_WIN_KUAFU_3V3)
				elseif data.result == -1 then
					self:Kuafu3v3Lose()
				else
					self:SetKuafu3v3TrendInfo(0)
				end
				
				-- ������
				self:AddMoney(MONEY_TYPE_HONOR, MONEY_CHANGE_KUAFU_WORLD_3V3, data.honor)
			end
		end
		
	end)
end




function PlayerInfo:World3v3Rank()
	local url = string.format("%s%s/rank", globalGameConfig:GetExtWebInterface(), sub)
	local data = {}
	data.player_guid = self:GetGuid()
	data.player_name = self:GetName()
	data.avatar = self:GetAvatar()
	data.weapon = self:GetWeapon()
	data.divine = self:GetDivine()
	data.score = self:GetKuafu3v3Score()
	data.force = self:GetForce()
	data.gender = self:GetGender()
	
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("World3v3Rank response = %s", response)
		end		
	end)
end

-- ��������
function UpdateKuafuRank()
	local url = string.format("%s%s/check_rank", globalGameConfig:GetExtWebInterface(), sub)
	outFmtDebug("appd call UpdateKuafuRank url = %s", url)
	local data = {}
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("UpdateKuafuRank response = %s", response)
		end
		
		local dict = nil
		security.call(
			--try block
			function()
				dict = json.decode(response)
			end
		)
		
		if dict and dict.ret and dict.msg then
			outFmtDebug("%d %s", dict.ret, dict.msg)
			if type(dict.details) == "string" and string.len(dict.details) > 0 then
				dict.details = json.decode(dict.details)
			end
			if type(dict.details) == "table" then
				app.kuafu_rank = dict.details
			end
		end
		
	end)
end

-- ׼������
function PlayerInfo:OnPrepareMatch(oper)
	outFmtDebug("OnPrepareMatch %d", oper)
	
	local url = string.format("%s%s/prepare_match", globalGameConfig:GetExtWebInterface(), sub)
	
	local data = {}
	data.player_guid = self:GetPlayerMatchKey()
	data.oper = oper
	
	app.http:async_post(url, string.toQueryString(data), function (status_code, response)
		if response then
			outFmtDebug("OnPrepareMatch response = %s", response)
		end
		
		local dict = nil
		security.call(
			--try block
			function()
				dict = json.decode(response)
			end
		)
		
		if dict then
			outFmtDebug("%d %s", dict.ret, dict.msg)
		
			if dict.ret == 0 then
				local wait_info = dict.wait_info
				if type(wait_info) == "string" then
					wait_info = json.decode(wait_info)
				end
				self:OnSendWaitInfo(wait_info)
			-- ȡ���ȴ�
			elseif dict.ret == 2 then
				self:OnCancelMatch(KUAFU_TYPE_FENGLIUZHEN)
			end
		end
		
	end)
end

-- ���͵ȴ��б�
function PlayerInfo:OnSendWaitInfo(wait_info)

	local wait_info_list = {}
	for _, info in ipairs(wait_info) do
		local stru = wait_info_t .new()
		stru.name = info[ 2 ]
		stru.state = info[ 1 ]
		table.insert(wait_info_list, stru)
	end
	
	self:call_kuafu_3v3_wait_info(wait_info_list)
end


-- ����δ׼����
function PlayerInfo:SomeOneDeclineMatch()
	app:SetMatchingKuafuType(self:GetGuid(), nil)
	self:call_kuafu_3v3_decline_match(KUAFU_TYPE_FENGLIUZHEN)
end

function PlayerInfo:GetPlayerMatchKey()
	return self:GetGuid()
end