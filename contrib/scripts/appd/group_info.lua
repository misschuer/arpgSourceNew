-- ��ӹ���
local GroupInfo = class('GroupInfo', BinLogObject)
local protocols = require('share.protocols')

--��Ա�˳�
function GroupInfo:groupQuit(player)
	local player_guid = player:GetGuid()
	
	if not index then
		return
	end
	
	-- IMPORTANT �Ƴ�����
	app.objMgr:callDelWatch(player:GetSessionId(),self:GetGuid())
	player:SetGroupId('')
end

function GroupInfo:addMember(player)
	
	player:SetGroupId(self:GetGuid())
	--�·�binlog���ͻ���
	app.objMgr:callAddWatch(player:GetSessionId(), self:GetGuid())
	
end

function GroupInfo:groupDissolution()
	app.objMgr:callRemoveObject(self:GetGuid())
end

return GroupInfo