--��¼����handle����

function PlayerInfo:Hanlde_Get_Login_Activity_Reward(pkt)
	local id = pkt.id
	self:GetLoginActivityReward(id)
end