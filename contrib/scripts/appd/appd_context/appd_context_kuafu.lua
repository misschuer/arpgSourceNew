local security = require("base/Security")
		
-- ��ʱ���ļ����ƥ�����
function PlayerInfo:QueryKuafuMatchInfo()
	self:OnCheckWorld3v3Match()
	self:OnCheckWorldXianfuMatch()
	self:OnCheckGroupInstanceMatch()
end

-- ��������ȡ������ƥ��
function PlayerInfo:OnCancelKuafuMatch()
	self:OnCancelWorld3v3MatchBeforeOffline()
	self:OnCancelWorldXianfuMatchBeforeOffline()
	self:OnCancelGroupInstanceMatchBeforeOffline()
end

-- ���н������
function PlayerInfo:CheckMatchReward()
	-- ��������
	local isPkServer = globalGameConfig:IsPKServer()
	if isPkServer then
		return
	end
	
	--self:CheckWorld3v3Reward()
	--[[
	self:CheckWorldXianfuReward()
	self:OnSyncMoney()
	--]]
	self:CheckGroupInstanceReward()
end

-- ƥ��ȡ��
function PlayerInfo:OnCancelMatch(kuafu_type)
	if app:IsKuafuTypeMatching(self:GetGuid(), kuafu_type) then
		app:SetMatchingKuafuType(self:GetGuid(), nil)
		self:call_kuafu_3v3_cancel_match(kuafu_type)
	end
end
