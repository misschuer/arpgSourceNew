
--�ͻ�����ɵ�ǰ����
function PlayerInfo:Hanlde_Finish_Now_Guide(pkt)
	self:SetGuideIdLast(self:GetGuideIdNow())
end

-- ��ɷ�ǿ����������
function PlayerInfo:Handle_Optional_Guide_Step(pkt)
	self:OptionalGuideClicked(pkt.guide_id, pkt.step)
end