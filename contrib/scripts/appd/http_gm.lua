local HttpGM = {}

local APP_SECRET = "WpIMeEXaV275ADSXQtDU"
local APP_SECRET_KEY_GAME2 = "Pu9oWAT6S3HGlSzDB16ALY1KacfVvTvT"

local GAME2_LOGIN_KEY = "RK6i9SsjqVLBgCUavwbZ7tQd8cnFOXke"
local GAME2_RECHARGE_KEY = "M3PpkFr7qbovl8CiA06HSEcmXVJLIWsU"

local function getServerName( guid )
	return string.match(guid, "%w+_%w+")	
end

--保存到文件时的切割字符串
local __RECHARGE_SEPARATOR__ = '\n--------------------------------\n'

function HttpGM:GetRechargeFileName(playerGuid)
	assert(__RECHARGE_FOLDER__)
	assert(__RECHARGE_FOLDER__ ~= "")
	local file_name = __RECHARGE_FOLDER__ .. "/" .. playerGuid
	return file_name
end

--保存不在线的数据到文件
function HttpGM:writeRechargeToHDD(playerGuid, text)
	local file_name = self:GetRechargeFileName(playerGuid)
	local file = io.open(file_name, "a")
	file:write(text)
	file:write(__RECHARGE_SEPARATOR__)
	file:close()
end

--错误枚举
local RECHARGE_RESLUT_SUCCED				= 0		--成功
local RECHARGE_RESLUT_REPATED				= 1 	--重复充值
local RECHARGE_RESLUT_INSUFFICIENT			= 2 	--余额不足，扣费失败
local RECHARGE_RESLUT_EXCEPTION				= 3 	--充值过程中，游戏服代码逻辑出现异常
local RECHARGE_RESLUT_OFFLINE				= 4 	--玩家不在线
local RECHARGE_RESLUT_OFFLINE_SUCCEED		= 5 	--充值时玩家不在线，重新登录以后充值成功
local RECHARGE_RESLUT_OFFLINE_REPATED		= 6 	--充值时玩家不在线，重新登录以后发现重复充值
local RECHARGE_RESLUT_OFFLINE_INSUFFICIENT	= 7 	--充值时玩家不在线，重新登录以后余额不足，扣费失败

--post充值处理结果给中间件
function HttpGM:PostRechargeResult(id, ret, msg)
	local post_url = self:getUrl(GlobalGameConfig:GetConfSvrUrl(), "/gm_intf/update_recharge_status")
	local data = {id = id, ret = ret, msg = msg}
	local post_data = string.toQueryString(data)
	outFmtInfo("HttpGM:PostRechargeResult %s %s", post_url, post_data)
	self:async_post(post_url,post_data, function ( status_code, response )
		-- if status_code == 200 and info and info.ret == 0  then
		-- end
	end)
end

--[[
pid	运营商ID 游戏方提供	必要
sid	服务器ID – 1即是1服	必要
uid	平台运营ID	必要
oid	订单号-全局唯一	必要
money	RMB金额（支持一位小数）	必要
gold	虚拟币数额	必要
time	当前北京时间unix时间戳(允许误差±900秒)	必要
sign	auth数据的校验码，用来校验数据是否恶意修改。	必要

--]]
function HttpGM:postRechargeResultToGeMenWang(obj, account)
	local s1 = string.split(account, '_')
	local s2 = string.split(obj.ext, '_')
	
	local params = {
		{"pid", tonumber(s2[ 1 ])},
		{"sid", tonumber(s2[ 2 ])},
		{"uid",  s1[#s1]},
		{"oid", obj.payid},
		{"money", obj.money},
		{"gold", tonumber(obj.money) * 10},
		{"time", os.time()},
	}
	
	local sign = getSign(params, APP_SECRET_KEY_GAME2)
	table.insert(params, {"sign", sign})
	
	local post_url = "http://183.60.41.183:7171/pay/op/push"
	local post_data = getParamsString(params)
	self:innerPost(post_url, post_data)
end

function HttpGM:innerPost(post_url, post_data)
	outFmtInfo("HttpGM:postRechargeResultToGeMenWang %s %s", post_url, post_data)
	self:async_post(post_url,post_data, function ( status_code, response )
		if status_code == 200 and response == "1" then
			outFmtInfo(" HttpGM:postRechargeResultToGeMenWang post success")
			return
		end
		outFmtInfo(" postRechargeResultToGeMenWang callback error : status_code = %d, response = %s will retry at 5 second", status_code, response)
		app.cron:after(5, function()
			self:innerPost(post_url, post_data)
		end)
	end)
end

--写充值流水日志
function HttpGM:writeRechargeLog(playerInfo, obj, desc)
	if not obj.goodsname then
		obj.goodsname = '1-gold'
	end
	
	if not obj.payid then
		obj.payid = obj.oid
	end
	
	if not obj.orderid then
		obj.orderid = ""
	end
	
	if not obj.paytime then
		obj.paytime = obj.time
	end
	
	if not obj.goodsnum then
		obj.goodsnum = 0
	end

	WriteRechargeLog(playerInfo, obj.payid, obj.orderid, obj.paytime, obj.goodsname, obj.money, obj.goodsnum, obj.real, desc )
end

--当玩家登录时从文件中将充值数据读出来, 并为玩家充值
function HttpGM:RchhargeOnLogin(player)
	self:rechargeOnlineFor5wan(player)
	self:rechargeOnlineForGame2(player)
end

function HttpGM:rechargeOnlineFor5wan(player)
	local file_name = self:GetRechargeFileName(player:GetGuid())
	local file = io.open(file_name, "r")
	if(not file)then
		return
	end
	local str = file:read("*a");
	file:close()
	outFmtInfo("HttpGM:rechargeOnlineFor5wan read file %s %s", player:GetGuid(), str)
	os.remove(file_name)
	--开始处理数据
	local tab = lua_string_split(str, __RECHARGE_SEPARATOR__)	
	--local post_url = self:getUrl(GlobalGameConfig:GetConfSvrUrl(), "/gm_intf/query_recharge_status")
	for i = 1, #tab do
		local data = tab[i]
		if(data ~= "" and string.len(data) > 10)then
			outFmtInfo("HttpGM:rechargeOnlineFor5wan tryDecode %s '%s'", player:GetGuid(), data)
			local obj = self:tryDecode(data)
			if (obj) then
--[[				if GetOrderIdIsDealed(obj.orderid) then
					--已经处理过				
					--self:writeRechargeLog(player, obj, "player login recharge but has proceed")
					outFmtError("HttpGM:rechargeOnlineFor5wan has proceed orderid %s payid %s", obj.orderid, obj.payid)
				else--]]
				obj.goodsnum = tonumber(obj.goodsnum)
				if player:DoRecharge(obj) then
					self:writeRechargeLog(player, obj, "player login recharge and success")
				else
					obj.real = 0
					-- 记录
					self:writeRechargeLog(player, obj, "player login recharge but addmoney fail")
					--self:writeRechargeToHDD(player:GetGuid(), str)
					outFmtError("HttpGM:rechargeOnlineFor5wan addmoney error orderid %s payid %s", obj.orderid, obj.payid)
				end
--				end
			end
		end
	end
end

function HttpGM:rechargeOnlineForGame2(player)
	local file_name = self:GetRechargeFileName(player:GetAccount())
	local file = io.open(file_name, "r")
	if(not file)then
		return
	end
	local str = file:read("*a");
	file:close()
	outFmtInfo("HttpGM:rechargeOnlineForGame2 read file %s %s", player:GetAccount(), str)
	os.remove(file_name)
	--开始处理数据
	local tab = lua_string_split(str, __RECHARGE_SEPARATOR__)	
	--local post_url = self:getUrl(GlobalGameConfig:GetConfSvrUrl(), "/gm_intf/query_recharge_status")
	for i = 1, #tab do
		local data = tab[i]
		if(data ~= "" and string.len(data) > 10)then
			outFmtInfo("HttpGM:rechargeOnlineForGame2 tryDecode %s '%s'", player:GetAccount(), data)
			local obj = self:tryDecode(data)
			if (obj) then
--[[				if GetOrderIdIsDealed(obj.oid) then
					--已经处理过				
					--self:writeRechargeLog(player, obj, "player login recharge but has proceed")
					outFmtError("HttpGM:rechargeOnlineForGame2 has proceed oid %s payid %s", obj.oid, obj.payid)
				else--]]
				obj.ext = getServerInfo(obj.sid)
				if player:DoRecharge(obj) then
					self:writeRechargeLog(player, obj, "player login recharge and success")
				else
					obj.real = 0
					-- 记录
					self:writeRechargeLog(player, obj, "player login recharge but addmoney fail")
					--self:writeRechargeToHDD(player:GetGuid(), str)
					outFmtError("HttpGM:rechargeOnlineForGame2 addmoney error oid %s payid %s", obj.oid, obj.payid)
				end
--				end
			end
		end
	end
end


function HttpGM:initGMIDIPHanlder( )	
	local checkip = function(ip)
		local conf_svr_url = globalGameConfig:GetConfSvrUrl()
		local start = string.find(conf_svr_url, ip)
		if ip == "127.0.0.1" or start ~= nil then
			return true
		end
		return false
	end
	
	self:addHanlde("/external/recharge", function ( req, rep )
		outFmtInfo("/external/recharge begin")
		if not checkip(req.remote_ip) then
			outFmtError("/external/recharge invalid source request! remote: %s", req.remote_ip)
			rep.status = 500
			rep.content = json.encode({ ["ret"] = 1, ["msg"] = "invalid source!"})
			return
		end
		
		-- 验证平台正确性
		if globalGameConfig:GetPlatformID() ~= PLATFORM_5WANPK then
			rep.status = 500
			rep.content = json.encode({ ["ret"] = 1, ["msg"] = "platform is not 5wanpk"})
			return
		end
		
		local repData = {}
		local obj = self:tryDecode(req.content)
		if not obj or not obj.payid or not obj.orderid or not obj.paytime or not obj.goodsname or not obj.money or not obj.goodsnum or not obj.ext or not obj.sign then					
			rep.status = 500
			repData = { ["ret"] = 1, ["msg"] = "has empty data!"}
			rep.content = json.encode(repData)
			outFmtError("/external/recharge if not obj or not obj.account or not obj.recharge_id or not obj.type or not obj.amount or not obj.adddate then")
			return
		end
		
		outFmtInfo("/external/recharge %s %s %s %s %s %u %s %s", obj.payid, obj.orderid, obj.paytime, obj.goodsname, obj.money, obj.goodsnum, obj.ext, obj.sign)
		
		if not self:CheckSign(obj) then
			outFmtError("/external/recharge wrong sign")
			return
		end

		-- 获得订单号对应的player
		local playerGuid = GetPlayerGuidByOrderId(obj.orderid)
		-- 当前订单不存在
		if string.len(playerGuid) == 0 then
			outFmtError("/external/recharge not find orderid %s", obj.orderid)
			return
		end
		
		-- 已经处理过
		if GetOrderIdIsDealed(obj.orderid) then
			-- self:writeRechargeLog(player, obj, "recharge online but has proceed")
			rep.status = 500
			repData = { ["ret"] = RECHARGE_RESLUT_REPATED, ["msg"] = "has proceed!"}
			rep.content = json.encode(repData)
			outFmtError("/external/recharge has proceed orderid %s payid %s", obj.orderid, obj.payid)
			return
		end
		local account, name = GetPlayerAccountByOrderId(obj.orderid)
		-- 记日至
		call_opt_policed_mongo_recharge(account, playerGuid, name, obj.ext, obj.payid, obj.paytime, obj.goodsname, obj.money)
		-- 本地订单设置状态
		UpdatePlayerRechargeInfo(obj.orderid, obj.payid, obj.paytime, obj.money)
		-- 给哥们网GM管理后台
		self:postRechargeResultToGeMenWang(obj, account)
		
		local player = app.objMgr:getObj(playerGuid)
		if player then
			obj.goodsnum = tonumber(obj.goodsnum)
			if player:DoRecharge(obj) then
				self:writeRechargeLog(player, obj, "recharge online recharge success")
				rep.status = 200
				repData = { ["ret"] = RECHARGE_RESLUT_SUCCED, ["msg"] = "recharge success!"}
				rep.content = json.encode(repData)
			else
				obj.real = 0
				-- 记录
				self:writeRechargeLog(player, obj, "recharge online but addmoney fail")
				--self:writeRechargeToHDD(playerGuid, req.content)
				rep.status = 200
				repData = { ["ret"] = RECHARGE_RESLUT_INSUFFICIENT, ["msg"] = "addmoney error!"}
				rep.content = json.encode(repData)
				outFmtError("/external/recharge submoney error orderid %s payid %s", obj.orderid, obj.payid)
			end
		else
			outFmtError("/external/recharge not player %s not online ", playerGuid)
			-- self:writeRechargeLog(player, obj, "recharge not online so write local file")
			self:writeRechargeToHDD(playerGuid, req.content)
			rep.status = 200
			repData = { ["ret"] = RECHARGE_RESLUT_OFFLINE, ["msg"] = "player offline!"}
			rep.content = json.encode(repData)
		end

		outFmtInfo("/external/recharge end")
	end, function (req, rep)
		rep.status = 500
		rep.content = json.encode({["ret"] = RECHARGE_RESLUT_EXCEPTION, ["msg"] = "program exception!"})
	end)
	
	
	--充值路由
	self:addHanlde("/gm_intf/gm_recharge", function ( req, rep )
		--[[outFmtInfo("/gm_intf/gm_recharge begin")
		if not checkip(req.remote_ip) then
			outFmtError("/gm_intf/gm_recharge invalid source request! remote: %s", req.remote_ip)
			rep.status = 500
			rep.content = json.encode({ ["ret"] = 1, ["msg"] = "invalid source!"})
			return
		end
		local repData = {}
		local obj = self:tryDecode(req.content)
		if not obj or not obj.account or not obj.recharge_id or not obj.type or not obj.amount or not obj.adddate then					
			rep.status = 500
			repData = { ["ret"] = 1, ["msg"] = "has empty data!"}
			rep.content = json.encode(repData)
			outFmtError("/gm_intf/gm_recharge if not obj or not obj.account or not obj.recharge_id or not obj.type or not obj.amount or not obj.adddate then")
			return
		end

		obj.type = tonumber(obj.type)
		obj.amount = tonumber(obj.amount)
		obj.adddate = tonumber(obj.adddate)
		outFmtInfo("/gm_intf/gm_recharge %s %s %u %u %u", obj.account, obj.recharge_id, obj.type, obj.amount, obj.adddate)
		local player = app.objMgr:getByAccount(obj.account)		
		if player then
			if player:GetRechargeLastID() == obj.recharge_id then
				--已经处理过				
				self:writeRechargeLog(obj, "recharge online but has proceed")
				rep.status = 500
				repData = { ["ret"] = RECHARGE_RESLUT_REPATED, ["msg"] = "has proceed!"}
				rep.content = json.encode(repData)
				outFmtError("/gm_intf/gm_recharge has proceed %s   recharge_id is %s", obj.account, obj.recharge_id)
			elseif player:DoRecharge(obj) then
				self:writeRechargeLog(obj, "recharge online recharge success")
				rep.status = 200
				repData = { ["ret"] = RECHARGE_RESLUT_SUCCED, ["msg"] = "recharge success!"}
				rep.content = json.encode(repData)
			else
				assert(obj.type == GOLD_INGOT_RECHARGE_SUB)
				self:writeRechargeLog(obj, "recharge online but submoney fail")
				rep.status = 500
				repData = { ["ret"] = RECHARGE_RESLUT_INSUFFICIENT, ["msg"] = "submoney error!"}
				rep.content = json.encode(repData)
				outFmtError("/gm_intf/gm_recharge submoney error account is %s recharge_id is %s", obj.account, obj.recharge_id)
			end
		else
			outFmtError("/gm_intf/gm_recharge not find player %s", obj.account)			
			self:writeRechargeLog(obj, "recharge not online so write local file")
			self:writeRechargeToHDD(obj.account, req.content)
			rep.status = 200
			repData = { ["ret"] = RECHARGE_RESLUT_OFFLINE, ["msg"] = "player offline!"}
			rep.content = json.encode(repData)
		end

		
		outFmtInfo("/gm_intf/gm_recharge end")--]]
	end, function (req, rep)
		rep.status = 500
		rep.content = json.encode({["ret"] = RECHARGE_RESLUT_EXCEPTION, ["msg"] = "program exception!"})
	end)
	
	--礼包路由
	self:addHanlde("/gm_intf/gm_gift_packs", function ( req, rep )
		if not checkip(req.remote_ip) then
			outFmtError("gm_gift_packs invalid source request! %s", req.remote_ip)
			rep.status = 500
			rep.content = json.encode({ ["ret"] = 1, ["msg"] = "invalid source!"})
			return
		end
		--local obj = string.parseQueryString(req.query_string)
		local obj = self:tryDecode(req.content)		
		
		local params = string.split(obj.item_config, ',')
		if #params % 2 == 1 then
			params[#params] = nil
		end
		obj.item_config = string.join(',', params)
		local repData = {}
		outFmtInfo('/gm_intf/gm_gift_packs obj.id = %s, obj.gift_type = %s, obj.audience_type = %s, obj.start_time = %s, obj.end_time = %s, obj.gift_name = %s, obj.gift_desc = %s, obj.item_config = %s, obj.to_id = %s', obj.id, obj.gift_type, obj.audience_type, obj.start_time, obj.end_time, obj.gift_name, obj.gift_desc, obj.item_config, obj.to_id)
		if not obj or not obj.id or not obj.gift_type or not obj.audience_type or not obj.start_time or not obj.end_time 
			or not obj.gift_name or not obj.gift_desc or not obj.item_config or not obj.to_id then					
			rep.status = 500
			repData = { ["ret"] = 1, ["msg"] = "has empty data!"}
			rep.content = json.encode(repData)
			outFmtError("gm_gift_packs has empty param!")
			return
		end
		obj.id = tonumber(obj.id)
		obj.gift_type = tonumber(obj.gift_type)
		obj.audience_type = tonumber(obj.audience_type)
		obj.start_time = tonumber(obj.start_time)
		obj.end_time = tonumber(obj.end_time)
		local timenow = os.time()		-- 1449737628
		if timenow >= obj.end_time then
			--礼包已经过期了
			rep.status = 200
			rep.content = json.encode({ ["ret"] = 0, ["msg"] = "gm_gift_packs has reach endtime", ["status"] = GIFT_PACKS_STATUS_OK})
			return
		end
		if obj.audience_type == GIFT_PACKS_AUDIENCE_TYPE_ONE and obj.end_time > timenow and obj.id > 0 then
			AddGiftPacksData(obj.to_id, obj.id, obj.gift_type, obj.start_time, obj.end_time, obj.gift_name, obj.gift_desc, obj.item_config,"")
			rep.status = 200
			repData = { ["ret"] = 0, ["msg"] = "gm_gift_packs success!", ["status"] = GIFT_PACKS_STATUS_OK}
			rep.content = json.encode(repData)
		elseif obj.audience_type == GIFT_PACKS_AUDIENCE_TYPE_ALL and obj.end_time > timenow and obj.id > 0 then
			if obj.server_name then
				outFmtInfo('gm_gift_packs server_name get!!!!')
				if obj.server_name ~= globalGameConfig:GetServerID() then
					outFmtInfo('gm_gift_packs: test going server_name %s  ~= self server_name %s ', obj.server_name, GlobalGameConfig:GetServerID())
					rep.status = 200
					repData = { ["ret"] = 0, ["msg"] = "gm_gift_packs warn!", ["status"] = GIFT_PACKS_STATUS_START} 
					rep.content = json.encode(repData)
				else
					outFmtInfo('gm_gift_packs: test going  obj.id = %u', obj.id)
					--[[
					--遍历所有玩家
					app.objMgr:foreachAllPlayer(function(player)
						if player:GetCharCreateTime() < obj.start_time and player:GetPlayerGiftPacksId() < obj.id then
							player:SetPlayerGiftPacksId(obj.id)
							AddGiftPacksData(player:GetGuid(), obj.id, obj.gift_type, obj.start_time, obj.end_time, obj.gift_name, obj.gift_desc, obj.item_config,"")
						end			
					end)
					--]]
					globalSystemMail:AddSystemMailInfo(obj.gift_type, obj.start_time, obj.end_time, obj.gift_name, obj.gift_desc, obj.item_config, "")
					
					rep.status = 200
					repData = { ["ret"] = 0, ["msg"] = "gm_gift_packs success!", ["status"] = GIFT_PACKS_STATUS_START} 
					rep.content = json.encode(repData)
				end
			else
				outFmtInfo('gm_gift_packs: test false  obj.id = %u', obj.id)
				--[[
				--遍历所有玩家
				app.objMgr:foreachAllPlayer(function(player)
					if player:GetCharCreateTime() < obj.start_time and player:GetPlayerGiftPacksId() < obj.id then
						player:SetPlayerGiftPacksId(obj.id)
						AddGiftPacksData(player:GetGuid(), obj.id, obj.gift_type, obj.start_time, obj.end_time, obj.gift_name, obj.gift_desc, obj.item_config,"")
					end			
				end)
				--]]
				globalSystemMail:AddSystemMailInfo(obj.gift_type, obj.start_time, obj.end_time, obj.gift_name, obj.gift_desc, obj.item_config, "")
				
				rep.status = 200
				repData = { ["ret"] = 0, ["msg"] = "gm_gift_packs success!", ["status"] = GIFT_PACKS_STATUS_START} 
				rep.content = json.encode(repData)
			end
		elseif obj.audience_type == GIFT_PACKS_AUDIENCE_TYPE_ALL_ONLINE and obj.end_time > timenow and obj.id > 0 then
			app.objMgr:foreachAllPlayer(function(player)
				AddGiftPacksData(player:GetGuid(), obj.id, obj.gift_type, obj.start_time, obj.end_time, obj.gift_name, obj.gift_desc, obj.item_config,"")				
			end)
			rep.status = 200
			repData = { ["ret"] = 0, ["msg"] = "gm_gift_packs success!", ["status"] = GIFT_PACKS_STATUS_OK}
			rep.content = json.encode(repData)
		end
	end)
	
	--公告
	self:addHanlde("/gm_intf/gm_notice", function(req, rep)
		--[[
		local obj = self:tryDecode(req.content)
		local running_ids, end_ids = {}, {}
		for i = 1, #obj do
			local status = addSysNotice(tonumber(obj[i].id), tonumber(obj[i].u_start_time), tonumber(obj[i].u_end_time), 
				tonumber(obj[i].i_interval), obj[i].content, tonumber(obj[i].i_status))		
			if status == SYSTEM_NOTICE_STATUS_GARBAGE then
				table.insert(end_ids, tonumber(obj[i].id))
			else
				table.insert(running_ids, tonumber(obj[i].id))
			end				
		end
		
		rep.status = 200
		local repData = {["ret"] = 0, ["msg"] = "send notice success!",}
		repData.running_ids = table.concat(running_ids, ',')
		repData.end_ids = table.concat(end_ids, ',')		
		rep.content = json.encode(repData)
		--]]
	end)
	
	--内部扶持号
	self:addHanlde("/gm_intf/gm_inaccount_list", function(req, rep)
		--[[local obj = self:tryDecode(req.content)
		local success_account = {}
		for _,info in ipairs(obj) do			
			local player = app.objMgr:getByAccount(info.account)			
			if player then
				if tonumber(info.i_account_type) == 1 then					
					player:SetFlags(PLAYER_FLAG_INACCOUNT)
				elseif tonumber(info.i_account_type) == 0 then					
					player:UnSetFlags(PLAYER_FLAG_INACCOUNT)
				end
				table.insert(success_account, info.account)
			end
		end
		
		rep.status = 200
		local repData = {["ret"] = 0, ["msg"] = "ok", success_account = success_account }		
		rep.content = json.encode(repData)--]]
	end)
	
	--哥们网H5充值接口
	self:addHanlde("/recharge/h5", function(req, rep)
		outFmtInfo("/recharge/h5 begin")
		if not checkip(req.remote_ip) then
			outFmtError("/recharge/h5 invalid source request! remote: %s", req.remote_ip)
			rep.status = 500
			rep.content = "-18"
			return
		end

		local repData = {}
		local obj = self:tryDecode(req.content)
		if not obj or not obj.sid or not obj.uid or not obj.oid or not obj.money or not obj.time or not obj.productId or not obj.extend or not obj.sign then					
			rep.status = 500
			rep.content = "-19"
			outFmtError("/recharge/h5 if not obj or not obj.sid or not obj.uid or not obj.oid or not obj.money or not obj.time or not obj.productId or not obj.extend or not obj.sign")
			return
		end
		
		-- 服务器不对
		if getServerId(globalGameConfig:GetServerID()) ~= tonumber(obj.sid) then
			outFmtError("/recharge/h5 wrong serverid %s", obj.sid)
			rep.status = 500
			rep.content = "-10"
			return
		end
		
		-- 签名不对
		if not self:CheckSign(obj, GAME2_RECHARGE_KEY) then
			outFmtError("/recharge/h5 wrong sign")
			rep.status = 500
			rep.content = "-17"
			return
		end
		
		-- 验证商品是否存在
		local indx = tonumber(obj.productId)
		if not tb_shop_chongzhi[indx] then
			outFmtError("/recharge/h5 wrong productId %s", obj.productId)
			rep.status = 500
			rep.content = "-19"
			return
		end
		
		-- 金额错误
		if tb_shop_chongzhi[indx].cost ~= tonumber(obj.money) then
			outFmtError("/recharge/h5 wrong money %s for productId %s", obj.money, obj.productId)
			rep.status = 500
			rep.content = "-15"
			return
		end
		
		local orderId = obj.extend
		
		local playerGuid = GetPlayerGuidByOrderId(orderId)
		-- 当前订单不存在
		if string.len(playerGuid) == 0 then
			outFmtError("/external/recharge not find orderid %s", orderId)
			rep.status = 500
			rep.content = "-11"
			return
		end
		
		-- 已经处理过
		if GetOrderIdIsDealed(orderId) then
			rep.status = 500
			rep.content = "-12"
			outFmtError("/recharge/h5 has proceed orderId %s", orderId)
			return
		end
		
		local account, name, paytime = GetPlayerAccountByOrderId(orderId)
		
		local nowTime = os.time()
		local diff = nowTime - tonumber(obj.time)
		
		if diff < -900 or diff > 900 then
			outFmtError("/recharge/h5 wrong time error for post time %s nowTime = %d", obj.time, nowTime)
			rep.status = 500
			rep.content = "-14"
			return
		end
		
		
		-- 玩家不存在
		if getUid(account) ~= obj.uid then
			outFmtError("/recharge/h5 wrong time error for post uid %s account = %s", obj.uid, account)
			rep.status = 500
			rep.content = "-11"
			return
		end

		if ModifyGame2BookingInfo('', '', '', '', obj.oid, obj.time) == 0 then
			outFmtError("/recharge/h5 ModifyGame2BookingInfo error in for orderId = %s",  orderId)
			rep.status = 500
			rep.content = "-19"
			return
		end
		
		obj.goodsname = '1-gold'
		local serverInfo = getServerInfo(obj.sid)
		-- 记日至
		call_opt_policed_mongo_recharge(account, playerGuid, name, serverInfo, obj.oid, obj.time, obj.goodsname, obj.money)
		
		outFmtInfo("/recharge/h5 %s %s %s %s %s %s %s %s", obj.sid, obj.uid, obj.oid, obj.money, obj.time, obj.productId, obj.extend, obj.sign)
		
		local player = app.objMgr:getObj(playerGuid)
		if player then
			obj.ext = serverInfo
			if player:DoRecharge(obj) then
				self:writeRechargeLog(player, obj, "recharge online recharge success")
				rep.status = 200
				rep.content = "1"
			else
				obj.real = 0
				-- 记录
				self:writeRechargeLog(player, obj, "recharge online but addmoney fail")
				--self:writeRechargeToHDD(playerGuid, req.content)
				rep.status = 500
				rep.content = "-19"
				outFmtError("/recharge/h5 submoney error oid %s orderId = %s", obj.oid, orderId)
			end
		else
			outFmtError("/recharge/h5 not player %s not online orderId = %s", playerGuid, orderId)
			-- self:writeRechargeLog(player, obj, "recharge not online so write local file")
			self:writeRechargeToHDD(account, req.content)
			rep.status = 200
			rep.content = "1"
		end

		outFmtInfo("/recharge/h5 end")
	end, function (req, rep)
		rep.status = 500
		rep.content = json.encode({["ret"] = RECHARGE_RESLUT_EXCEPTION, ["msg"] = "program exception!"})
	end)
end

function HttpGM:CheckSign(obj, appSecret)
	appSecret = appSecret or APP_SECRET
	local sign = obj.sign
	local list = {}
	for key, value in pairs(obj) do
		if key ~= "sign" and value and value ~= "" then
			table.insert(list, {key, value})
		end
	end
	
	local mm = getSign(list, appSecret, true)

	return mm == sign
end

function getGame2RechargeSign(list)
	return getSign(list, GAME2_RECHARGE_KEY, true)
end


function getSign(list, appSecret, ascSort)
	ascSort = ascSort or false
	if ascSort then
		mi_sort(list, function (a, b)
			return a[ 1 ] < b[ 1 ] or a[ 1 ] == b[ 1 ] and a[ 2 ] < b[ 2 ]
		end)
	end
	
	local str = getParamsString(list)
	local mm = packet.md5tostr(str..appSecret)
	
	return mm
end

function getParamsString(list)
	local strList = {}
	for _, info in ipairs(list) do
		table.insert(strList, info[ 1 ]..'='..info[ 2 ])
	end
	local str = string.join('&', strList)
	
	return str;
end

function HttpGM:writeToHDD(path, content)
	local file = io.open(path, "wb")
	file:write(content)
	file:close()
end

--扩展该方法
function HttpGM.extend( self )
	for k,v in pairs(HttpGM) do self[k] = v end
end

return HttpGM