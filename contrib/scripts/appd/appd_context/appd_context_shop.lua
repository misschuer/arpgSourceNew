--[[
-- �̵깺����Ʒ
function PlayerInfo:storeBuyItem(itemId, count)
	local itemMgr = self:getItemMgr()
	-- �жϱ����Ƿ��㹻
	if not itemMgr:canHold(BAG_TYPE_MAIN_BAG, itemId, count, 1, 0) then
		self:CallOptResult(OPRATE_TYPE_BAG, BAG_RESULT_BAG_FULL)
		return
	end
	
	local costTable = tb_store[itemId].costResource
	if not self:costMoneys(MONEY_CHANGE_TYPE_STORE_BUY, costTable, count) then
		-- ����������ʾ
		return
	end

	-- �ӵ���
	itemMgr:addItem(itemId,count,1,true,true,0,0)
end
--]]

-- �̳ǹ�����Ʒ
function PlayerInfo:shopBuyItem(id, count, timeid)

	local itemMgr = self:getItemMgr()
	
	local config = tb_shop[id]
	if not config then
		return
	end
	
	local entry = config.itemId
	local added = count * config.count
	if not IsResource(entry) then
		-- �жϱ����Ƿ��㹻
		if not itemMgr:canHold(BAG_TYPE_MAIN_BAG, entry, added, 1, 0) then
			self:CallOptResult(OPRATE_TYPE_BAG, BAG_RESULT_BAG_FULL)
			return
		end
	end
	
	--�޹�
	local limtype = config.limtype
	
	if limtype ~= 0 then--�޹�
		local hasShopNum = self:getShopLimtNum(config.id)
		outFmtDebug("hasShopNum %d",hasShopNum)
		hasShopNum = hasShopNum + count
		if hasShopNum > config.limdata then
			self:CallOptResult(OPERTE_TYPE_NPCBUY, NPC_BUY_SELL_OUT)
			return
		end
	end
	
	--������ʱ��
	local limtime = config.time
	if #limtime ~= 0 then
		
		local begintab = {year=limtime[1], month=limtime[2], day=limtime[3], hour=0,min=0,sec=0,isdst=false}
		local begintime = os.time(begintab);
		
		local endtab = {year=limtime[4], month=limtime[5], day=limtime[6], hour=0,min=0,sec=0,isdst=false}
		local endtime = os.time(endtab);
		
		local ctime = os.time()
		if ctime < begintime then
			self:CallOptResult(OPERTE_TYPE_NPCBUY, NPC_BUY_ITEM_NO_OPEN)
			return
		end
		
		if ctime >= endtime then
			self:CallOptResult(OPERTE_TYPE_NPCBUY, NPC_BUY_ITEM_OUT_TIME)
			return
		end
		
	end
	
	local baseCostTable = config.costResource
	local itemendtime = 0
--[[	if #config.timeCostResource > 0 and timeid > 0 then
		
		if not config.timeCostResource[timeid] then
			return
		end
		baseCostTable = {}
		
		local timeitemtab = {}
		table.insert(timeitemtab,config.timeCostResource[timeid][1]) 
		table.insert(timeitemtab,config.timeCostResource[timeid][2]) 
		
		table.insert(baseCostTable,timeitemtab)
		
		itemendtime = os.time() + config.timeCostResource[timeid][3] * 24 * 60 * 60
	else--]]
	if timeid ~= 0 then
		return
	end
	
	
	--�ۿ�
	local discount = config.discount / 10.0	
	local costTable = {}
	if discount ~= 1 then
		for k,v in ipairs(baseCostTable) do
			--table.insert(costTable,)
			local itemtab = {}
			table.insert(itemtab,v[1]) 
			table.insert(itemtab,math.ceil(v[2]*discount)) 
			
			table.insert(costTable,itemtab)
		end
	else
		costTable = baseCostTable
	end
	
	if not self:costMoneys(MONEY_CHANGE_TYPE_MALL_BUY, costTable, count) then
		self:CallOptResult(OPERTE_TYPE_NPCBUY, NPC_BUY_MONEY_NO_ENOUGH)
		return
	end
	
	local buyDic = {{entry,added}}
	
	self:AppdAddItems(buyDic,MONEY_CHANGE_TYPE_MALL_BUY,LOG_ITEM_OPER_TYPE_SHOP_BUY,1,itemendtime)
	
	self:AddActiveItem(VITALITY_TYPE_SHOP_BUY)
	
	if limtype ~= 0 then--�޹�
		self:addShopLimtNum(config.id,count)
	end
	
end
--��ȡ��Ӧid���ѹ������
function PlayerInfo:getShopLimtNum(id)
	for i=PLAYER_FIELD_SHOP_LIMIT_START,PLAYER_FIELD_SHOP_LIMIT_END-1 do
		local tid = self:GetUInt16(i,0)
		if tid == id then
			return self:GetUInt16(i,1)
		end
	end
	return 0
end
--����޹�����
function PlayerInfo:addShopLimtNum(id,num)
	for i=PLAYER_FIELD_SHOP_LIMIT_START,PLAYER_FIELD_SHOP_LIMIT_END-1 do
		local tid = self:GetUInt16(i,0)
		if tid == id then
			local tnum = self:GetUInt16(i,1)
			tnum = tnum + num
			self:SetUInt16(i,1,tnum)
			return
		end
	end
	
	for i=PLAYER_FIELD_SHOP_LIMIT_START,PLAYER_FIELD_SHOP_LIMIT_END-1 do
		local tid = self:GetUInt16(i,0)
		if tid == 0 then
			self:SetUInt16(i,0,id)
			self:SetUInt16(i,1,num)
			return
		end
	end
	
end
--����ÿ���޹�
function PlayerInfo:resetDailyShop()
	for i=PLAYER_FIELD_SHOP_LIMIT_START,PLAYER_FIELD_SHOP_LIMIT_END-1 do
		local tid = self:GetUInt16(i,0)
		if tid ~= 0 then
			local config = tb_shop[tid]
			if config and config.limtype == 1 then
				self:SetUInt16(i,0,0)
				self:SetUInt16(i,1,0)
			end
		end
	end
end
--����ÿ���޹� 
function PlayerInfo:resetWeekShop() --FIXME ��δ����
	for i=PLAYER_FIELD_SHOP_LIMIT_START,PLAYER_FIELD_SHOP_LIMIT_END-1 do
		local tid = self:GetUInt16(i,0)
		if tid ~= 0 then
			local config = tb_shop[tid]
			if config.limtype == 2 then
				self:SetUInt16(i,0,0)
				self:SetUInt16(i,1,0)
			end
		end
	end
end

--[[
-- Ԫ������
function PlayerInfo:goldRespawn(useGold)
	local resItemId = tb_hook_hp_item[ 2 ].items[ 1 ]
	local id = GetShopId(MONEY_TYPE_GOLD_INGOT, resItemId)
	
	if not tb_shop[id] then
		return
	end
	
	-- ����ͻ���
	if self:IsAlive() then
		return
	end
		
	local cost = tb_shop[id].costResource[ 1 ][ 2 ]
	if useGold then
		if not self:SubGoldMoney (MONEY_CHANGE_BUY_ATUO_RESPAWN, cost) then
			return
		end
	else
		if not self:SubMoney(MONEY_TYPE_BIND_GOLD, MONEY_CHANGE_BUY_ATUO_RESPAWN, cost) then
			return
		end
	end
	
	
	local itemMgr = self:getItemMgr()
	--����cd
	itemMgr:handleCoolDown(resItemId)
	
	-- ���͵�������
	self:CallScenedDoSomething(APPD_SCENED_RESPAWN, resItemId)
end

--]]
