
--ע������
--��֧�ֿ��ͼʹ����Ϸ������Ҫ���ͼ������Ѱ·���˵�ͼ��

local ActionBase = require('robotd.action.action')
local ActionScenedUseTeleport = class('ActionScenedUseTeleport', ActionBase)

--��ȡ����
function ActionScenedUseTeleport:GetType()
	return ROBOT_ACTION_TYPE_SCENED
end

--��ʼ������
function ActionScenedUseTeleport:Initialize(object_id, mapid, x, y, callback)	
	self.to_mapid = mapid
	self.to_x = x
	self.to_y = y
	self.object_id = object_id
	self.is_goto = false
	self.action_finish = false
	self.callback = callback
	self.isClose = false
end

--��ȡ������
function ActionScenedUseTeleport:GetName()
	return 'ActionScenedUseTeleport'
end

--����
function ActionScenedUseTeleport:Update(diff)
	--�Ѿ�������ж���
	if(self.action_finish)then
		-- ����Ŀ�ĵ�
		if self.callback then
			self.callback()
		end
		return false, 1
	end

	local mapid = self.player:GetMapID()
	local x, y = self.player:GetPos()
	--��Ѱ·
	if(self.is_goto == false)then
		--�Ѿ��������˾Ͳ�����Ѱ·��
		if(mapid == self.to_mapid and self.player.my_unit:GetDistanceByPos(self.to_x,self.to_y)<=3)then
			--outFmtDebug("ActionScenedUseTeleport:Update %s use object fail", self:ToString())
			outFmtDebug("ActionScenedUseTeleport:Update is already here")
			self.is_goto = true
			self.isClose = true
			return true
		end

		if(self.to_mapid > 0)then
			--����GO��������
			local pos_tab = mapLib.RandomPos(self.to_mapid,1,self.to_x, self.to_y,1)
			local is_canRun = mapLib.IsCanRun(self.to_mapid,pos_tab[1].x,pos_tab[1].y)
			if(is_canRun)then
				self.to_x = pos_tab[1].x
				self.to_y = pos_tab[1].y
			end
		end
		
		-- ����Ŀ�ĵص�callback
		local closeCallback = function()
			self.isClose = true
		end

		if(mapid == self.to_mapid)then
			self:PushAction('robotd.action.scened.action_scened_goto', self.to_mapid, self.to_x, self.to_y, closeCallback)
		else
			self:PushAction('robotd.action.scened.action_scened_pathfinding', self.to_mapid, self.to_x, self.to_y, closeCallback)
		end
		self.is_goto = true
		return true
	end
	
	if not self.isClose then
		return true
	end
	
	--Ѱ·û�ɹ���ʹ��ʧ��
	if(mapid ~= self.to_mapid or self.player.my_unit:GetDistanceByPos(self.to_x,self.to_y)>3)then
		outFmtDebug("ActionScenedUseTeleport:Update %s use object fail", self:ToString())
		return false, 2
	end

	local unit = self.player:FindGameObject(self.object_id)
	if(unit == nil)then
		--outFmtDebug("ActionScenedUseTeleport:Update object not find, %s", self:ToString())
		--return false, 3
		outFmtDebug("ActionScenedUseTeleport:Update wait 1 second for teleport occur")
		return true
	else
		self.player:call_teleport(unit:GetUIntGuid())
		--�ȴ�һ���Ժ��˳�
		self:SetWaitTimeInterval(4000)
		self.action_finish = true
	end
	
	return true
end


return ActionScenedUseTeleport
