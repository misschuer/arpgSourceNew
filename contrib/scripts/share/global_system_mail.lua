--ϵͳ������Ϣ
local GlobalSystemMail = class('GlobalSystemMail', assert(BinLogObject))

function GlobalSystemMail:ctor()
	
end

--ϵͳ�ʼ�������1
function GlobalSystemMail:Next()
	local cur_num = self:GetMailIndex()
	if cur_num >= MAX_SYSTEM_MAIL_INFO_COUNT-1 then		--�����Ϣ��ౣ��MAX_SYSTEM_MAIL_INFO_COUNT
		self:SetMailIndex(0)	
	else
		self:AddUInt32(MAX_SYSTEM_MAIL_INFO_INT_NOW_INDEX, 1)
	end
	self:AddUInt32(SYSTEM_MAIL_COUNT, 1)
end	

--�����Ϣint��ʼ�±�
function GlobalSystemMail:Start()
	return SYSTEM_MAIL_INT_FIELD_BEGIN + self:GetMailIndex() * MAX_SYSTEM_MAIL_INFO_INT
end

--�����Ϣstring��ʼ�±�
function GlobalSystemMail:StringStart()
	return SYSTEM_MAIL_STRING_FIELD_BEGIN + self:GetMailIndex() * MAX_SYSTEM_MAIL_INFO_STRING
end

-- ���ϵͳ�ʼ�����
function GlobalSystemMail:GetMailCount()
	return self:GetUInt32(SYSTEM_MAIL_COUNT)
end

--��������Ϣ��ǰ����
function GlobalSystemMail:GetMailIndex()
	return self:GetUInt32(MAX_SYSTEM_MAIL_INFO_INT_NOW_INDEX)
end

--���������Ϣ��ǰ����
function GlobalSystemMail:SetMailIndex( val)
	self:SetUInt32(MAX_SYSTEM_MAIL_INFO_INT_NOW_INDEX, val)
end

--��ȡ���ID
function GlobalSystemMail:GetSystemMailID()
	return self:GetUInt32(self:Start() + SYSTEM_MAIL_INFO_INT_ID)
end

--�������ID
function GlobalSystemMail:SetSystemMailID(val)
	self:SetUInt32(self:Start() + SYSTEM_MAIL_INFO_INT_ID, val)
end

--��ȡ�������ʱ��
function GlobalSystemMail:GetSystemMailStartTime()
	return self:GetUInt32(self:Start() + SYSTEM_MAIL_INFO_INT_START_TIME)
end

--�����������ʱ��
function GlobalSystemMail:SetSystemMailStartTime(val)
	self:SetUInt32(self:Start() + SYSTEM_MAIL_INFO_INT_START_TIME, val)
end

--��ȡ�������ʱ��
function GlobalSystemMail:GetSystemMailEndTime()
	return self:GetUInt32(self:Start() + SYSTEM_MAIL_INFO_INT_END_TIME)
end

--�����������ʱ��
function GlobalSystemMail:SetSystemMailEndTime(val)
	self:SetUInt32(self:Start() + SYSTEM_MAIL_INFO_INT_END_TIME, val)
end

--��ȡ�������
function GlobalSystemMail:GetSystemMailType()
	return self:GetUInt32(self:Start() + SYSTEM_MAIL_INFO_INT_TYPE)
end

--�����������
function GlobalSystemMail:SetSystemMailType(val)
	self:SetUInt32(self:Start() + SYSTEM_MAIL_INFO_INT_TYPE, val)
end

--��ȡ�������
function GlobalSystemMail:GetSystemMailName()
	return self:GetStr(self:StringStart() + SYSTEM_MAIL_INFO_STRING_NAME)
end

--�����������
function GlobalSystemMail:SetSystemMailName(val)
	self:SetStr(self:StringStart() + SYSTEM_MAIL_INFO_STRING_NAME,val)
end

--��ȡ���˵��
function GlobalSystemMail:GetSystemMailDesc()
	return self:GetStr(self:StringStart() + SYSTEM_MAIL_INFO_STRING_DESC)
end

--�������˵��
function GlobalSystemMail:SetSystemMailDesc(val)
	self:SetStr(self:StringStart() + SYSTEM_MAIL_INFO_STRING_DESC,val)
end

--��ȡ�����Դ
function GlobalSystemMail:GetSystemMailFrom()
	return self:GetStr(self:StringStart() + SYSTEM_MAIL_INFO_STRING_FROM)
end

--���������Դ
function GlobalSystemMail:SetSystemMailFrom(val)
	self:SetStr(self:StringStart() + SYSTEM_MAIL_INFO_STRING_FROM,val)
end

--��ȡ�����Ʒ
function GlobalSystemMail:GetSystemMailItem(pos)
	local start
	
	if(pos == nil)then
		start = self:StringStart()
	else
		start = SYSTEM_MAIL_STRING_FIELD_BEGIN + pos * MAX_SYSTEM_MAIL_INFO_STRING
	end
	
	return self:GetStr(start + SYSTEM_MAIL_INFO_STRING_ITEM)
end

--���������Ʒ
function GlobalSystemMail:SetSystemMailItem(val)
	self:SetStr(self:StringStart() + SYSTEM_MAIL_INFO_STRING_ITEM,val)
end


--���һ��ϵͳ�ʼ�
--[[
	gift_type   : �ʼ�����
	start_time  : ����ʱ��
	end_time    : ��������
	gift_name   : �ʼ�����
	gift_desc   : �ʼ�˵��
	item_config : �ʼ�����
	item_from   : �ʼ���Դ
]]
function GlobalSystemMail:AddSystemMailInfo( gift_type, start_time, end_time, gift_name, gift_desc, item_config, item_from)
	local id = self:GetMailCount() + 1
	
	self:SetSystemMailID(id)
	self:SetSystemMailStartTime(start_time)
	self:SetSystemMailEndTime(end_time)
	self:SetSystemMailType(gift_type)

	self:SetSystemMailName(gift_name)
	self:SetSystemMailDesc(gift_desc)
	self:SetSystemMailItem(item_config)
	self:SetSystemMailFrom(item_from)
	
	self:Next()
	
	-- ���������������
	app.objMgr:foreachAllPlayer(function(playerInfo)
		-- �������к�
		playerInfo:SetSystemMailSeq(id)
		local indx = (id-1) % MAX_SYSTEM_MAIL_INFO_COUNT
		self:PickSystemMail(playerInfo, indx)
	end)
	
	return 1
end

-- �ж��Ƿ���ϵͳ�ʼ�
function GlobalSystemMail:checkIfHasSystemMail(playerInfo)
	local vist = playerInfo:GetSystemMailSeq()
	local id = self:GetMailCount()
	local range = id - vist
	if range > MAX_GIFTPACKS_INFO_COUNT then
		vist = id - MAX_GIFTPACKS_INFO_COUNT
	end
	
	-- ��ȡ����
	for g = vist, id-1 do
		local indx = g % MAX_SYSTEM_MAIL_INFO_COUNT
		self:PickSystemMail(playerInfo, indx)
	end
	
	-- �������к�
	playerInfo:SetSystemMailSeq(id)
end

-- ��ȡϵͳ���
function GlobalSystemMail:PickSystemMail(playerInfo, indx)
	print("GlobalSystemMail:PickSystemMail guid =", playerInfo:GetGuid(), "indx =", indx)
	
	local intIndx = SYSTEM_MAIL_INT_FIELD_BEGIN + indx * MAX_SYSTEM_MAIL_INFO_INT
	local strIndx = SYSTEM_MAIL_STRING_FIELD_BEGIN + indx * MAX_SYSTEM_MAIL_INFO_STRING
	
	-- ����Լ����ʼ�
	local giftPack = playerInfo:getGiftPacksInfo()
	
	local gift_type   = self:GetUInt32(intIndx + SYSTEM_MAIL_INFO_INT_TYPE)
	local start_time  = self:GetUInt32(intIndx + SYSTEM_MAIL_INFO_INT_START_TIME)
	local end_time    = self:GetUInt32(intIndx + SYSTEM_MAIL_INFO_INT_END_TIME)
	
	local gift_name   = self:GetStr(strIndx + SYSTEM_MAIL_INFO_STRING_NAME)
	local gift_desc   = self:GetStr(strIndx + SYSTEM_MAIL_INFO_STRING_DESC)
	local item_config = self:GetStr(strIndx + SYSTEM_MAIL_INFO_STRING_ITEM)
	
	print(gift_type, start_time, end_time, gift_name, gift_desc, item_config)
	
	giftPack:AddGiftPacksInfo(gift_type, start_time, end_time, gift_name, gift_desc, item_config, "")
end



return GlobalSystemMail