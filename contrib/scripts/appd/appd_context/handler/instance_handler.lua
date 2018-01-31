-- ɨ��vip����
function PlayerInfo:Handle_Sweep_Vip_Instance(pkt)
	local id = pkt.id
	
	if tb_map_vip[id] == nil then
		return
	end
	
--	self:sweepVIP(id)
end


-- ɨ��������
function PlayerInfo:Handle_Sweep_Trial(pkt)
	self:sweepTrial()
end

-- ����������
function PlayerInfo:Handle_Reset_Trial(pkt)
	self:resetTrial()
end

-- ɨ����Դ����
function PlayerInfo:Handle_Sweep_Res(pkt)
	local id = pkt.id
	if tb_instance_res[id] == nil then
		return
	end
	self:sweepResInstance(id)
end

function PlayerInfo:Handle_Buy_Mass_Boss_Times(pkt)
	--[[local cnt = pkt.cnt
	if cnt <= 0 then
		return
	end
	
	-- ����������ܳ�������
	local buyed = self:GetMassBossBuyedTimes()
	local vip = self:GetVIP()
	if buyed + cnt > #tb_mass_boss_times + tb_vip_base[vip].massbossBuyTimes then
		return
	end
	
	-- �������˲��ܹ���
	local curr = self:getMassBossTimes()
	if curr + cnt > tb_mass_boss_base[ 1 ].dailytimes then
		return
	end
		
	local cost = {}
	for i = 1, cnt do
		local config = tb_mass_boss_times[buyed+i]
		for _, rinfo in pairs(config.cost) do
			AddTempInfoIfExist(cost, rinfo[ 1 ], rinfo[ 2 ])
		end
	end
	
	if not self:costMoneys(MONEY_CHANGE_MASS_BOSS_BUY_TIMES, cost, 1) then
		return
	end
	
	self:AddMassBossBuyedTimes(cnt)
	self:AddMassBossTimes(cnt)--]]
end

function PlayerInfo:Handle_Buy_Group_Instance_Times(pkt)
	local count = pkt.count
	if count < 1 then
		return
	end
	
	self:OnBuyGroupInstanceTicket(count)
end

function PlayerInfo:Handle_Get_Risk_Reward(pkt)
	globalCounter:getRiskRank(self)
end

function PlayerInfo:Handle_Buy_Group_Exp_Times(pkt)
	local count = pkt.count
	if count < 1 then
		return
	end
	
	self:OnBuyGroupExpTicket(count)
end


function PlayerInfo:Handle_Pick_Res_Instance_First_Reward(pkt)
	local id = pkt.id
	if id < 1 or id > 40 then
		return
	end
	
	self:pickResInstanceFirstReward(id)
end