InstanceMainBase = class("InstanceMainBase", Instance_base)

InstanceMainBase.Name = "InstanceMainBase"
InstanceMainBase.player_auto_respan = 1

function InstanceMainBase:ctor(  )
	
end

--��ʼ���ű�����
function InstanceMainBase:OnInitScript(  )
	Instance_base.OnInitScript(self) --���û���
end

--��Ҽ����ͼ
function InstanceMainBase:OnJoinPlayer(player)
	Instance_base.OnJoinPlayer(self, player)
	local playerInfo = UnitInfo:new{ptr = player}
	-- �����޸�ģʽ
	playerInfo:ChangeToPeaceModeAfterTeleport()
end