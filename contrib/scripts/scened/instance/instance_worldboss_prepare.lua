InstanceWorldBossP = class("InstanceWorldBossP", Instance_base)

InstanceWorldBossP.Name = "InstanceWorldBossP"


function InstanceWorldBossP:ctor(  )
	
end

--��Ҽ����ͼ
function InstanceWorldBossP:OnJoinPlayer(player)
	InstanceInstBase.OnJoinPlayer(self, player)
	local playerInfo = UnitInfo:new{ptr = player}
	if not playerInfo:IsAlive() or os.time() >= self:GetMapQuestEndTime() then
		--�����˻�������ֱ�ӵ���ȥ
		mapLib.ExitInstance(self.ptr, player)
		return
	end
end

--������뿪ʱ����
function InstanceWorldBossP:OnLeavePlayer( player, is_offline)
	
end

--��ʼ���ű�����
function InstanceWorldBossP:OnInitScript(  )
	-- �����ظ���ʼ��
	if self:isInstanceInit() then
		return
	end
	self:SetInstanceInited()
	
	Instance_base.OnInitScript(self) --���û���
	
	local endTime = os.time() + globalValue:GetEnrollCountdown()
	
	self:SetMapQuestEndTime(endTime)
	-- ���ý���ʱ��
	self:SetMapEndTime(endTime + 10)
end

return InstanceWorldBossP