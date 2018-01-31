
local function newLogPacket(opt, log_type, account, player_id  )
	local Packet = require 'util.packet'
	local pkt = Packet.new(assert(opt))
	local tv_sec, tv_usec = gettimeofday()
	pkt:writeU32(assert(log_type))
	pkt:writeU32(tv_sec)
	pkt:writeU32(tv_usec)
	pkt:writeUTF(account or '')
	pkt:writeUTF(player_id or '')
	return pkt
end

--根据传入协议号创建一个函数
local function createWriteLogFunction( opt )	
	local function func( log_type, player_id, ... )
		local pkt = newLogPacket(opt, log_type, '', player_id)
		for _,v in ipairs({...}) do		
			if type(v) == 'number' then
				pkt:writeU32(v)
			else
				--assert(type(v) == 'string')
				pkt:writeUTF(v)
			end
		end
		app:sendToPoliced(pkt)
		pkt:delete()
	end
	return func
end

local writeLog = createWriteLogFunction(INTERNAL_OPT_WRITE_LOG)
local writeTencentLog = createWriteLogFunction(INTERNAL_OPT_TENCENT_LOG)

--道具所有行为
function WriteItemLog(player,reason,entry,isUse,count)
	local pkt = newLogPacket(INTERNAL_OPT_WRITE_LOG, LOG_FILE_TYPE_ITEM_LOG, player:GetAccount(), player:GetGuid())
	pkt:writeU32(os.time())
	pkt:writeU32(entry)
	pkt:writeU32(isUse)
	pkt:writeU32(reason)
	pkt:writeU32(count)	
	pkt:writeU32(player:GetLevel())

	app:sendToPoliced(pkt)
	pkt:delete()
end

--//TX用户充值记录日志
function WriteTXRechargeLog( account, player_id, player_name, player_level, transactionId, currency, inpourType, addcoin, money, gold, exchangeType, depay, gDepay, state, create_time, platdata )
	local pkt = newLogPacket(INTERNAL_OPT_TENCENT_LOG, LOG_FILE_TENCENT_RECHAGRE, account, player_id )
	pkt:writeUTF(player_name)
	pkt:writeU32(player_level)
	pkt:writeUTF(transactionId)
	pkt:writeUTF(currency)
	pkt:writeUTF(inpourType)
	pkt:writeU32(addcoin)
	pkt:writeDouble(money)
	pkt:writeDouble(gold)
	pkt:writeU32(exchangeType)
	pkt:writeDouble(depay)
	pkt:writeDouble(gDepay)
	pkt:writeU32(state)
	pkt:writeU32(create_time)
	pkt:writeUTF(platdata)
	app:sendToPoliced(pkt)
	pkt:delete()
end

--保存首充日志
function WriteFirstRechargeInfoLog(player,amount,addate,server_name)
	local values = {}
	local p_guid = player:GetGuid()
	values["server_name"] = server_name
	values["guid"] = p_guid
	values["name"] = player:GetName()
	values["i_level"] = tostring(player:GetLevel())
	values["i_value"] = tostring(amount)
	values["i_quest"] = tostring(player:GetMainQuestID())
	values["u_adddate"] = tostring(addate)
	
	local Packet = require 'util.packet'
	local pkt = Packet.new(assert(INTERNAL_OPT_LOGS_FIRST_RECHARGE))
	pkt:writeMap(values)
	app:sendToPoliced(pkt)
	pkt:delete()
end

-- 写聊天日志
function WriteChatLog(player_id, chat_type, target_id,target_name, msg, player_level, gm_level)
	writeLog(LOG_FILE_TYPE_CHAT, player_id, chat_type, target_id, target_name, msg, player_level, gm_level)
end

-- 记录客户端信息
function WriteClientInfoLog(player_id, client, browser, isdebug, language, version, flash_version, x, y, oss)
	writeLog(LOG_FILE_TYPE_CLIENT_INFO, player_id, client, browser, isdebug, language, version, flash_version, x, y, oss)
end

--[[
	payid: string;//5玩的交易单号
	orderid: string;//CP的订单ID，调用Pay时传入
	
	paytime: string;//支付时间
	goodsname: string;//物品名称
	money: string;//购买物品总金额（元）,保留两位小数
	goodsnum: number;//购买物品的数量
	
	ext: string;//扩展字符串，支付成功后会原封不动的传递回去
	sign: string;//签名，查看签名算法

	
	平台充值id 	payid
	充值时间戳 	paytime
	充值类型 	goodsname
	充值金额	money
	订单状态描述 desc


--]]

function WriteRechargeLog(playerInfo, payid, orderid, paytime, goodsname, money, goodsnum, real, desc)
	local pkt = newLogPacket(INTERNAL_OPT_WRITE_LOG, LOG_FILE_TYPE_RECHARGE, playerInfo:GetAccount(), playerInfo:GetGuid())
	
	pkt:writeUTF(payid)
	pkt:writeUTF(paytime)
	pkt:writeUTF(goodsname)
	pkt:writeUTF(money)
	pkt:writeDouble(goodsnum)
	pkt:writeDouble(real)
	pkt:writeUTF(desc)
	app:sendToPoliced(pkt)
	pkt:delete()
end


--记录用户接受任务的行为
function WriteAcceptTask(playerInfo,time_stamp,taskid,type,remain)
	local pkt = newLogPacket(INTERNAL_OPT_WRITE_LOG, LOG_FILE_TYPE_ACCEPT_TASK, playerInfo:GetAccount(), playerInfo:GetGuid())
	
	pkt:writeU32(time_stamp)
	pkt:writeU32(taskid)
	pkt:writeU32(type)
	pkt:writeUTF(remain)

	app:sendToPoliced(pkt)
	pkt:delete()
end

--记录用户完成任务的行为
function WriteMainTask(playerInfo,time_stamp,taskid,type,remain)
	local pkt = newLogPacket(INTERNAL_OPT_WRITE_LOG, LOG_FILE_TYPE_MAIN_TASK, playerInfo:GetAccount(), playerInfo:GetGuid())
	
	pkt:writeU32(time_stamp)
	pkt:writeU32(taskid)
	pkt:writeU32(type)
	pkt:writeUTF(remain)

	app:sendToPoliced(pkt)
	pkt:delete()
end

--记录在线人数
function WriteOnline(time_stamp, account_count, player_count, ip_count, old_player_count)
	local pkt = newLogPacket(INTERNAL_OPT_WRITE_LOG, LOG_FILE_TYPE_ONLINE, "", "")
	
	pkt:writeU32(time_stamp)
	pkt:writeU32(account_count)
	pkt:writeU32(player_count)
	pkt:writeU32(ip_count)
	pkt:writeU32(old_player_count)


	app:sendToPoliced(pkt)
	pkt:delete()
end

--0点在线日志
function WriteOnlineUser24th(playerInfo, name, create_time, last_login_time, from_last_time, ip, gender, level, force, active_value, map_id,main_quest_id, history_recharge, gold, bind_gold, money, bind_money)
	local pkt = newLogPacket(INTERNAL_OPT_WRITE_LOG, LOG_FILE_TYPE_ONLINE_USER_24TH, playerInfo:GetAccount(), playerInfo:GetGuid())
	
	pkt:writeUTF(name)
	pkt:writeU32(create_time)
	pkt:writeU32(last_login_time)
	pkt:writeU32(from_last_time)
	pkt:writeUTF(ip)
	pkt:writeU32(gender)
	pkt:writeU32(level)
	pkt:writeDouble(force)
	pkt:writeU32(active_value)
	pkt:writeU32(map_id)
	pkt:writeU32(main_quest_id)
	pkt:writeU32(history_recharge)
	pkt:writeDouble(gold)
	pkt:writeDouble(bind_gold)
	pkt:writeDouble(money)
	pkt:writeDouble(bind_money)


	app:sendToPoliced(pkt)
	pkt:delete()
end

--帮派日志
function WriteUnion(playerInfo, time_stamp, faction_id, faction_name, type, remain)
	local pkt = newLogPacket(INTERNAL_OPT_WRITE_LOG, LOG_FILE_TYPE_UNION, playerInfo:GetAccount(), playerInfo:GetGuid())
	
	pkt:writeU32(time_stamp)
	pkt:writeUTF(faction_id)
	pkt:writeUTF(faction_name)
	pkt:writeU32(type)
	pkt:writeUTF(remain)

	app:sendToPoliced(pkt)
	pkt:delete()
end