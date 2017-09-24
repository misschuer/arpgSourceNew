
--ע������
--��Ҫ���ͼ������Ѱ·���˵�ͼ��

local ActionBase = require('robotd.action.action')
local ActionScenedFindNpc = class('ActionScenedFindNpc', ActionBase)

--��ȡ����
function ActionScenedFindNpc:GetType()
	return ROBOT_ACTION_TYPE_SCENED
end

--��ʼ������
function ActionScenedFindNpc:Initialize(object_id, mapid, x, y, callback)
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
function ActionScenedFindNpc:GetName()
	return 'ActionScenedFindNpc'
end

--����
function ActionScenedFindNpc:Update(diff)
	--�Ѿ�������ж���
	if(self.action_finish)then
		return false, 1
	end

	local mapid = self.player:GetMapID()
	local x, y = self.player:GetPos()
	--��Ѱ·
	if(self.is_goto == false)then
		--�Ѿ��������˾Ͳ�����Ѱ·��
		if(mapid == self.to_mapid and self.player.my_unit:GetDistanceByPos(self.to_x,self.to_y)<=4)then
			outFmtDebug("ActionScenedFindNpc:Update is already here")
			self.is_goto = true
			self.isClose = true
			return true
		end

		if(self.to_mapid > 0)then
			--����GO��������
			local pos_tab = mapLib.RandomPos(self.to_mapid,1,self.to_x, self.to_y,4)
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

		outFmtDebug('ActionScenedFindNpc:Update mapid = %d to_mapId = %d',mapid,self.to_mapid)

		if(mapid == self.to_mapid)then
			self:PushAction('robotd.action.scened.action_scened_goto', self.to_mapid, self.to_x, self.to_y, closeCallback)
		else
			self:PushAction('robotd.action.scened.action_scened_pathfinding', self.to_mapid, self.to_x, self.to_y, closeCallback)
		end
		self.is_goto = true
		return true
	end
	
	-- ����Ѱ·�ͷ���
	if not self.isClose then
		return true
	end
	
	--Ѱ·û�ɹ���ʹ��ʧ��
	if(mapid ~= self.to_mapid or self.player.my_unit:GetDistanceByPos(self.to_x,self.to_y)>4)then
		outFmtError("ActionScenedFindNpc:Update %s use object fail", self:ToString())
		return false, 2
	end

	local unit = self.player:FindUnitByTemplateID(self.object_id)
	if(unit == nil)then
		outFmtError("not find unit by entry %d wait 1 second\n", self.object_id)
		self:SetWaitTimeInterval(1000)
		-- outFmtDebug("ActionScenedFindNpc:Update object not find, %s, wait 1 second to retry", self:ToString())
		--return false, 3
		return true
	else
		-- ���﷢�ͺ�npc�Ի�
		if self.callback then
			self.callback()
		end
		--�ȴ�һ���Ժ��˳�
		self:SetWaitTimeInterval(1000)
		self.action_finish = true
	end
	
	return true
end


return ActionScenedFindNpc
