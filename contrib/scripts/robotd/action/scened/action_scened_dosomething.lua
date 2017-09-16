
--ע������
--��֧�ֿ��ͼʹ����Ϸ������Ҫ���ͼ������Ѱ·���˵�ͼ��

local ActionBase = require('robotd.action.action')
local ActionScenedDoSomething = class('ActionScenedDoSomething', ActionBase)

--��ȡ����
function ActionScenedDoSomething:GetType()
	return ROBOT_ACTION_TYPE_SCENED
end

--��ʼ������
function ActionScenedDoSomething:Initialize(mapid, x, y, callback)	
	self.to_mapid = mapid
	self.to_x = x
	self.to_y = y
	self.is_goto = false
	self.action_finish = false
	self.callback = callback
	self.isClose = false
end

--��ȡ������
function ActionScenedDoSomething:GetName()
	return 'ActionScenedDoSomething'
end

--����
function ActionScenedDoSomething:Update(diff)
	--�Ѿ�������ж���
	if(self.action_finish)then
		return false, 1
	end

	local mapid = self.player:GetMapID()
	local x, y = self.player:GetPos()
	--��Ѱ·
	if(self.is_goto == false)then
		--�Ѿ��������˾Ͳ�����Ѱ·��
		if(mapid == self.to_mapid and self.player.my_unit:GetDistanceByPos(self.to_x,self.to_y)<=2)then
			--outFmtDebug("ActionScenedDoSomething:Update %s use object fail", self:ToString())
			outFmtDebug("ActionScenedDoSomething:Update is already here")
			self.is_goto = true
			self.isClose = true
			return true
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
	if(mapid ~= self.to_mapid or self.player.my_unit:GetDistanceByPos(self.to_x,self.to_y)>2)then
		outFmtDebug("ActionScenedDoSomething:Update %s dosomething fail", self:ToString())
		return false, 2
	end

	if self.callback then
		self.callback()
	end
	--�ȴ�һ���Ժ��˳�
	self:SetWaitTimeInterval(1000)
	self.action_finish = true
	
	return true
end


return ActionScenedDoSomething
