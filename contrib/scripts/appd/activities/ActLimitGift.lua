local ActLimitGift = class("ActLimitGift", ActivityBase)

IActLimitGift = ActLimitGift:new{}


function ActLimitGift:ctor()
	
end

-- ϵͳ��ʼ��
function ActLimitGift:init(actId)
	
end

-- ϵͳ����
function ActLimitGift:finish(actId)
	
end


-- ����(Ŀ��, ��ȡ״̬)
function ActLimitGift:update(playerInfo, actId, params)
	if params[1] == 1 then
		self:OnBuyLimitGift(playerInfo,actId,params[2])
	end
end

-- ���ÿ������
function ActLimitGift:reset(playerInfo, actId)
	
end

function ActLimitGift:OnBuyLimitGift(playerInfo,actId,index)
	local act_config = tb_activity_time[actId]
	local base_config = tb_activity_limit_gift_base[act_config.params[1]]
	
	if not base_config.gift_list[index] or index < 1 or index > 32  then
		--index error
		outFmtError("OnBuyLimitGift index error %d",index)
		return
	end
	
	local config = tb_activity_limit_gift[base_config.gift_list[index]]
	
	if not config then
		--config error
		outFmtError("OnBuyLimitGift tb_activity_daily_gift config error %d",index)
		return
	end
	
	if playerInfo:GetActivityDataBit(actId,0,index - 1) then
		--�ѹ���
		outFmtError("OnBuyLimitGift buy flag true ")
		return
	end
	
	if not playerInfo:hasAllItems(config.cost) then
		--����
		outFmtError("OnBuyLimitGift resource not enough")
		return
	end
	
	if playerInfo:useAllItems(MONEY_CHANGE_ACT_LIMITGIFT,config.cost) then
		playerInfo:AppdAddItems(config.item, MONEY_CHANGE_ACT_LIMITGIFT,LOG_ITEM_OPER_TYPE_ACT_LIMITGIFT)
		playerInfo:SetActivityDataBit(actId,0,index - 1)
	end
end

-- ϵͳ����
function ActLimitGift:systemUpdate(actId, params)
	
end

return ActLimitGift