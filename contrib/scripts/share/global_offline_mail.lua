--ϵͳ������Ϣ
local GlobalOfflineMail = class('GlobalOfflineMail', assert(BinLogObject))

function GlobalOfflineMail:ctor()
	
end

--�����Ϣ������1
function GlobalOfflineMail:Next()
	local cur_num = self:GetAttackStrutCount()
	if(cur_num >= MAX_OFFLINE_MAIL_INFO_COUNT-1)then		--���������ౣ��MAX_OFFLINE_MAIL_INFO_COUNT
		self:SetAttackStrutCount(0)	
	else
		self:AddUInt32(MAX_GIFTPACKS_INFO_INT_NOW_INDEX, 1)
	end
end	

--�����Ϣint��ʼ�±�
function GlobalOfflineMail:Start()
	return GIFTPACKS_INT_FIELD_BEGIN + self:GetAttackStrutCount() * MAX_GIFTPACKS_INFO_INT
end

--�����Ϣstring��ʼ�±�
function GlobalOfflineMail:StringStart()
	return GIFTPACKS_STRING_FIELD_BEGIN + self:GetAttackStrutCount() * MAX_GIFTPACKS_INFO_STRING 
end

--��������Ϣ��ǰ����
function GlobalOfflineMail:GetAttackStrutCount()
	return self:GetUInt32(MAX_GIFTPACKS_INFO_INT_NOW_INDEX)
end

--���������Ϣ��ǰ����
function GlobalOfflineMail:SetAttackStrutCount( val)
	self:SetUInt32(MAX_GIFTPACKS_INFO_INT_NOW_INDEX, val)
end

--��ȡ���ID
function GlobalOfflineMail:GetGiftPacksID()
	return self:GetUInt32(self:Start() + GIFTPACKS_INFO_INT_ID)
end

--�������ID
function GlobalOfflineMail:SetGiftPacksID(val)
	self:SetUInt32(self:Start() + GIFTPACKS_INFO_INT_ID, val)
end

--��ȡ�������ʱ��
function GlobalOfflineMail:GetGiftPacksStartTime()
	return self:GetUInt32(self:Start() + GIFTPACKS_INFO_INT_START_TIME)
end

--�����������ʱ��
function GlobalOfflineMail:SetGiftPacksStartTime(val)
	self:SetUInt32(self:Start() + GIFTPACKS_INFO_INT_START_TIME, val)
end

--��ȡ�������ʱ��
function GlobalOfflineMail:GetGiftPacksEndTime()
	return self:GetUInt32(self:Start() + GIFTPACKS_INFO_INT_END_TIME)
end

--�����������ʱ��
function GlobalOfflineMail:SetGiftPacksEndTime(val)
	self:SetUInt32(self:Start() + GIFTPACKS_INFO_INT_END_TIME, val)
end

--��ȡ�������
function GlobalOfflineMail:GetGiftPacksType()
	return self:GetByte(self:Start() + GIFTPACKS_INFO_INT_BYTE,0)
end

--�����������
function GlobalOfflineMail:SetGiftPacksType(val)
	self:SetByte(self:Start() + GIFTPACKS_INFO_INT_BYTE, 0 ,val)
end

--��ȡ�����ȡ״̬
function GlobalOfflineMail:GetGiftPacksReceive()
	return self:GetByte(self:Start() + GIFTPACKS_INFO_INT_BYTE,1)
end

--���������ȡ״̬
function GlobalOfflineMail:SetGiftPacksReceive(val)
	self:SetByte(self:Start() + GIFTPACKS_INFO_INT_BYTE, 1 ,val)
end

--��ȡ�������
function GlobalOfflineMail:GetGiftPacksName()
	return self:GetStr(self:StringStart() + GIFTPACKS_INFO_STRING_GIFT_NAME)
end

--�����������
function GlobalOfflineMail:SetGiftPacksName(val)
	self:SetStr(self:StringStart() + GIFTPACKS_INFO_STRING_GIFT_NAME,val)
end

--��ȡ���˵��
function GlobalOfflineMail:GetGiftPacksDesc()
	return self:GetStr(self:StringStart() + GIFTPACKS_INFO_STRING_GIFT_DESC)
end

--�������˵��
function GlobalOfflineMail:SetGiftPacksDesc(val)
	self:SetStr(self:StringStart() + GIFTPACKS_INFO_STRING_GIFT_DESC,val)
end

--��ȡ�������
function GlobalOfflineMail:GetGiftPacksFrom()
	return self:GetStr(self:StringStart() + GIFTPACKS_INFO_STRING_GIFT_FROM)
end

--�����������
function GlobalOfflineMail:SetGiftPacksFrom(val)
	self:SetStr(self:StringStart() + GIFTPACKS_INFO_STRING_GIFT_FROM,val)
end

--��ȡ�����Ʒ
function GlobalOfflineMail:GetGiftPacksItem(pos)
	local start
	if(pos == nil)then
		start = self:StringStart()
	else
		start = GIFTPACKS_STRING_FIELD_BEGIN + pos * MAX_GIFTPACKS_INFO_STRING
	end
	
	return self:GetStr(start + GIFTPACKS_INFO_STRING_GIFT_ITEM)
end

--���������Ʒ
function GlobalOfflineMail:SetGiftPacksItem(val)
	self:SetStr(self:StringStart() + GIFTPACKS_INFO_STRING_GIFT_ITEM,val)
end

--[[
SYSTEM_MAIL_INFO_INT_ID = 0	-- ���ID
SYSTEM_MAIL_INFO_INT_START_TIME = 1	-- ����ʱ��
SYSTEM_MAIL_INFO_INT_END_TIME = 2	-- ����ʱ��
SYSTEM_MAIL_INFO_INT_TYPE = 3	-- �������
MAX_SYSTEM_MAIL_INFO_INT = 4
SYSTEM_MAIL_INFO_STRING_NAME = 0	-- ϵͳ�ʼ�����
SYSTEM_MAIL_INFO_STRING_DESC = 1	-- ϵͳ�ʼ�˵��
SYSTEM_MAIL_INFO_STRING_FROM = 2	-- ϵͳ�ʼ����������������ʱ��д������֣�Ĭ��Ϊ�գ�ϵͳ����
SYSTEM_MAIL_INFO_STRING_ITEM = 3	-- �����Ʒ����
MAX_SYSTEM_MAIL_INFO_STRING = 4
]]

return GlobalOfflineMail