-- ���ʼ�
function PlayerInfo:Handle_Read_Mail(pkt)
	local indx = pkt.indx
	-- �ж��±��Ƿ�Ϸ�
	if indx < 0 or indx >= MAX_GIFTPACKS_INFO_COUNT then
		return
	end
	
	self:Read_Mail(indx)
end

-- ��ȡ�ʼ�
function PlayerInfo:Handle_Pick_Mail(pkt)
	local indx = pkt.indx
	-- �ж��±��Ƿ�Ϸ�
	if indx < 0 or indx >= MAX_GIFTPACKS_INFO_COUNT then
		return
	end
	
	self:Pick_Mail(indx)
end

-- ɾ���ʼ�
function PlayerInfo:Handle_Remove_Mail(pkt)
	local indx = pkt.indx
	-- �ж��±��Ƿ�Ϸ�
	if indx < 0 or indx >= MAX_GIFTPACKS_INFO_COUNT then
		return
	end	
	
	self:Remove_Mail(indx)
end

-- һ����ȡ�ʼ�
function PlayerInfo:Handle_Pick_Mail_One_Step(pkt)
	
	self:Pick_Mail_One_Step()
end

-- һ��ɾ���ʼ�
function PlayerInfo:Handle_Remove_Mail_One_Step(pkt)
	
	self:Remove_Mail_One_Step()
end