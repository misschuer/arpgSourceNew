local ActLottery = class("ActLottery", ActivityBase)

IActLottery = ActLottery:new{}

function ActLottery:ctor()
	
end

-- ϵͳ��ʼ��
function ActLottery:init(actId)
	
end

-- ϵͳ����
function ActLottery:finish(actId)
	
end

local fieldDict = {
	[ 1 ] = "high",
	[ 2 ] = "middle",
	[ 3 ] = "low",
}

local tbDict = {
	[ 1 ] = tb_activity_lottery_high,
	[ 2 ] = tb_activity_lottery_middle,
	[ 3 ] = tb_activity_lottery_low,
}

-- ����(Ŀ��, ��ȡ״̬)
function ActLottery:update(playerInfo, actId, params)
	local opt = params[ 1 ]
	local configIndx = tb_activity_time[actId].params[ 1 ]
	local config = tb_activity_lottery_base[configIndx]
	
	-- �Ƿ�Ϸ�
	if not config.costs[opt] then
		return
	end
	
	local cnt = 1
	-- �ж�Ǯ������
	if not playerInfo:useAllItems(MONEY_CHANGE_ACT_LOTTERY, nil, {config.costs[opt]}) then
		return
	end
	
	if config.count[opt] then
		cnt = config.count[opt]
	end
	
	local offset = tb_activity_time[actId].offset-1
	local size = #config.rate
	local unequeCnt = config.unequeCnt
	local rewardDict = {}
	for i = 1, cnt do
		local dict = config.low
		local storeTB = tb_activity_lottery_low
		-- local drawd = playerInfo:GetActivityDataUInt32(actId, 0)
		-- ���˱��״���
		if i == unequeCnt then
			dict = config.middle
			storeTB = tb_activity_lottery_middle
			-- drawd = 0
		else
			local randValue = randInt(1, 10000)
			
			for i = 1, size do
				if randValue <= config.rate[ i ] then
					dict = config[fieldDict[i]]
					storeTB = tbDict[i]
					break
				end
			end
			-- drawd = drawd + 1
		end

		-- playerInfo:SetActivityDataUInt32(actId, 0, drawd)
		
		-- �������
		local indx = randInt(1, #dict)
		local storeId = dict[indx]
		local storeItemTable = storeTB[storeId].item
		for _, itemInfo in pairs(storeItemTable) do
			AddTempInfoIfExist(rewardDict, itemInfo[ 1 ], itemInfo[ 2 ])
			if tb_item_template[itemInfo[ 1 ]].quality >= config.showQuality then
				local record = string.format("%s#%d#%d", playerInfo:GetName(), itemInfo[ 1 ], itemInfo[ 2 ])
				globalValue:AddLotteryRecord(offset, record)
			end
		end
	end
	
	playerInfo:AppdAddItems(rewardDict, MONEY_CHANGE_ACT_LOTTERY, LOG_ITEM_OPER_TYPE_ACT_LOTTERY)
end

-- ���ÿ������
function ActLottery:reset(playerInfo, actId)
	
end

return ActLottery