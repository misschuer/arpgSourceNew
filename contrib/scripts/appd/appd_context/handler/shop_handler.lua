--[[
-- �̵깺����Ʒ
function PlayerInfo:Handle_Store_Buy(pkt)
	local itemId	= pkt.id
	local count		= pkt.count
	local timeID 	= pkt.time
	
	-- �жϵ����Ƿ����
	if not tb_store[itemId] then
		return
	end
	
	-- �ж�һ�ι�������
	if count < 1 or count > tb_store[itemId].limit then
		return
	end
	
	self:storeBuyItem(itemId, count)
	
end
--]]

-- �̳ǹ�����Ʒ
function PlayerInfo:Handle_Mall_Buy(pkt)
	local id	= pkt.id
	local count	= pkt.count
	local timeid = pkt.time
	
	-- �жϵ����Ƿ����
	if not tb_shop[id] then
		return
	end
	
	-- �ж�һ�ι�������
	if count < 1 or count > tb_shop[id].limit then
		return
	end
	
	self:shopBuyItem(id, count,timeid)
	
end


--[[
-- Ԫ������
function PlayerInfo:Handle_Gold_Respawn(pkt)
	local useGold = pkt.useGold
	self:goldRespawn(useGold)
end
--]]