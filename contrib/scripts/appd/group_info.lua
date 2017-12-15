-- 组队管理
local GroupInfo = class('GroupInfo', BinLogObject)
local protocols = require('share.protocols')

--成员退出
function GroupInfo:groupQuit(player)
	local player_guid = player:GetGuid()
	
	if not index then
		return
	end
	
	-- IMPORTANT 移除监听
	app.objMgr:callDelWatch(player:GetSessionId(),self:GetGuid())
	player:SetGroupId('')
end

function GroupInfo:addMember(player)
	
	player:SetGroupId(self:GetGuid())
	--下发binlog给客户端
	app.objMgr:callAddWatch(player:GetSessionId(), self:GetGuid())
	
end

function GroupInfo:groupDissolution()
	app.objMgr:callRemoveObject(self:GetGuid())
end

return GroupInfo