-- ���ʼ�
function PlayerInfo:Read_Mail(indx)
	
	local giftPacksInfo = self:getGiftPacksInfo()
	giftPacksInfo:mailRead(indx)
end

-- ��ȡ�ʼ�
function PlayerInfo:Pick_Mail(indx)

	local giftPacksInfo = self:getGiftPacksInfo()
	giftPacksInfo:pickMail(self, indx)
end

-- ɾ���ʼ�
function PlayerInfo:Remove_Mail(indx)
	--[[
	local giftPacksInfo = self:getGiftPacksInfo()
	giftPacksInfo:removeMail(indx)
	--]]
end

-- һ����ȡ�ʼ�
function PlayerInfo:Pick_Mail_One_Step()
	
	local giftPacksInfo = self:getGiftPacksInfo()
	giftPacksInfo:pickMailOneStep(self)
end

-- һ��ɾ���ʼ�
function PlayerInfo:Remove_Mail_One_Step()
	
	local giftPacksInfo = self:getGiftPacksInfo()
	giftPacksInfo:removeMailOneStep() 
end