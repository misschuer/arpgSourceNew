function PlayerInfo:Handle_Booking_Game2_Money(pkt)
	local serverName	= pkt.serverName
	local cpOrderId		= pkt.cpOrderId
	local productName	= pkt.productName
	local productId		= pkt.productId
	local productDesc	= pkt.productDesc
	
	-- 核对平台id
	-- PLATFORM_GAME2
	--[[
	local platformId = globalGameConfig:GetPlatformID()
	if platformId ~= PLATFORM_GAME2 then
		return
	end
	--]]
	-- 验证商品是否存在
	local indx = tonumber(productId)
	if not tb_shop_chongzhi[indx] then
		return
	end
	
	local timestamp = os.time()
	local time = ""..timestamp
	-- 生成订单
	if ModifyGame2BookingInfo(self:GetGuid(), self:GetName(), self:GetAccount(), cpOrderId, "", time) == 0 then
		return
	end
	local serverId = getServerId(globalGameConfig:GetServerID())
	local amount = ""..tb_shop_chongzhi[indx].cost
	local _extend = cpOrderId
	
	list = {
		{"serverName", serverName},
		{"cpOrderId", cpOrderId},
		{"productName", productName},
		{"productId", productId},
		{"productDesc", productDesc},
		{"serverId", serverId},
		{"amount", amount},
		{"extend", _extend},
		{"time", time},
	}
	local sign = getGame2RechargeSign(list)
	
	self:call_booking_game2_money_result(1 ,serverId ,serverName ,cpOrderId ,productName ,productId ,productDesc ,amount ,_extend ,time ,sign)
end