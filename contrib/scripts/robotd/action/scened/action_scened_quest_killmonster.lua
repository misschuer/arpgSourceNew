
local ActionBase = require('robotd.action.action')
local ActionScenedQuestKillMonster = class('ActionScenedQuestKillMonster', ActionBase)

local STATUS_NONE			= 0	--��ʼ��״̬
local STATUS_GOTO			= 1	--Ѱ·����ʼ�һ���
local STATUS_FIND_CREATE	= 2	--Ѱ������
local STATUS_ATTACK_CREATE	= 3 --��������

--��ȡ����
function ActionScenedQuestKillMonster:GetType()
	return ROBOT_ACTION_TYPE_SCENED
end

--��ʼ������
function ActionScenedQuestKillMonster:Initialize(object_id, mapid, x, y, IsFinishMethod, callback)
	self.object_id = object_id
	self.mapid = mapid
	self.to_x = x
	self.to_y = y
	self.IsFinishMethod = IsFinishMethod
	self.status = STATUS_NONE
	self.callback = callback
	
	self.is_goto = false
end

--��ȡ������
function ActionScenedQuestKillMonster:GetName()
	return 'ActionScenedQuestKillMonster'
end

--Ѱ·���һ���
function ActionScenedQuestKillMonster:GoTo()
	--��Ѱ·
	if(self.status == STATUS_NONE)then
		local closeCallback = function ()
			self.is_goto = false
			self.status = STATUS_GOTO
		end
		self:PushAction('robotd.action.scened.action_scened_pathfinding', self.mapid, self.to_x, self.to_y, closeCallback)
		
		return true
	end
	
	local mapid = self.player:GetMapID()
	local x, y = self.player:GetPos()
	--Ѱ·û�ɹ���ʹ��ʧ��
	if(mapid ~= self.mapid or self.player.my_unit:GetDistanceByPos(self.to_x,self.to_y)>4)then
		outFmtError("ActionScenedQuestKillMonster:Update %s goto destination fail,from: %s %s %s", self:ToString(), mapid, x, y)
		return false
	else
		self.status = STATUS_FIND_CREATE
		return true
	end
end

--��������
function ActionScenedQuestKillMonster:AttectCreate(slot, attack_create)
	local x, y = attack_create:GetPos()
	local caster = self.player.my_unit:GetUIntGuid()
	local target = attack_create:GetUIntGuid()
	self.player:CastSpell(slot, x, y, caster, target)
end

local oldtime = 0

--����
function ActionScenedQuestKillMonster:Update(diff)
	--ɱ��������
	if self.IsFinishMethod() then
		if self.callback then
			self.callback()
		end
		return false, 1
	end
	
	--Ѱ·���һ���
	if(self.status <= STATUS_GOTO)then
		-- ��Ѱ·�оͲ���ҪѰ·��
		if self.is_goto then
			return true
		end
		self.is_goto = true
	
		return self:GoTo(), 4
	end
	
	--�������ˣ��Ǿ�У��һ�µ�ͼ��
	local mapid = self.player:GetMapID()
	--����Ŀ���ͼ�ˣ�һ�ж����Լ����ˣ����ιһ����˰�
	if(mapid ~= self.mapid)then
		outFmtError("ActionScenedQuestKillMonster:Update mapid ~= self.mapid, guid = %s currmapid = %d, tomapid = %d", self.player:GetGuid(), mapid, self.mapid)
		return false, 2
	end
	
	--����һ�´���ֻ��
	if(self.status == STATUS_FIND_CREATE)then
		--object_id
		local unit = self.player:FindUnitByTemplateID(self.object_id)
		if(unit == nil)then
			outFmtInfo("there is no unit for entry %d wait 1 second", self.object_id)
			self:SetWaitTimeInterval(1000)
			self.status = STATUS_GOTO
			self.is_goto = false
			return true
		end
		self.attack_create_guid = unit:GetGuid()
		self.status = STATUS_ATTACK_CREATE
		return true
	end
	
	--���ݱ����guid���������������Ҳ������߾�������������ִ���
	local attack_create = self.player:FindUnitByGuid(self.attack_create_guid)
	if(attack_create == nil or attack_create:IsDie())then
		self.attack_create_guid = ""
		self.status = STATUS_FIND_CREATE
		return true
	end
	
	-- ���м򵥵���ͨ����
	local skillId, skillLevel = self.player:GetCastSkillInfo()
	local skillLevelIndx = tb_skill_base[skillId].uplevel_id[ 1 ] + skillLevel - 1
	local range = tb_skill_uplevel[skillLevelIndx].distance
	--�Ѿ���������Χ�ڣ�����
	if(self.player.my_unit:GetDistance(attack_create) <= range)then
		--self:SkillMoveToTail()
		self:AttectCreate(tb_skill_base[skillId].skill_slot, attack_create)
		self:SetWaitTimeInterval(900)
		return true
	end
	
	--�ƶ��о��Ȳ�����λ����
	if(self.player.my_unit:IsMoving())then
		return true
	end
	
	--�����ƶ�ջ��
	--���ˣ�ֱ�������ƶ���
	local x, y = attack_create:GetPos()

	--�ж�������ϰ���Ļ������10��
	local is_canRun = mapLib.IsCanRun(attack_create:GetMapID(),x,y)
	if(is_canRun == false)then
		outFmtDebug("ActionScenedQuestKillMonster:Update create pos can't run %u %u %u", attack_create:GetMapID(),x,y)
		local pos_tab = mapLib.RandomPos(attack_create:GetMapID(),1,x,y,3)
		is_canRun = mapLib.IsCanRun(attack_create:GetMapID(),pos_tab[1].x,pos_tab[1].y)
		if(is_canRun)then
			x = pos_tab[1].x
			y = pos_tab[1].y
		end
	end

	--��Ȼ���ϰ���
	if(is_canRun == false)then
		outFmtError("%s  -----Can`t Run %f %u %u %u %u", self:ToString(), self.player.my_unit:GetDistance(attack_create), x, y, self.player:GetPos())
		assert(false)
		
		return false,4
	end

	local p_x,p_y = self.player:GetPos()
	--���Ŀ�������ͬ������Ͳ���������
	if(x == math.floor(p_x) and y == math.floor(p_y))then
		return true
	end

	local result = mapLib.PathfindingGoto(self.player.ptr, self.player.my_unit.ptr, x, y)
	if(result == false)then
		outFmtInfo("%s  -----  %f %u %u %u %u", self:ToString(), self.player.my_unit:GetDistance(attack_create), x, y, self.player:GetPos())
		if(result == false)then
			PathfindingGotoFailure(self.player,mapid)
			self:SetWaitTimeInterval(1000)
		end
	end	
	return true
end


return ActionScenedQuestKillMonster
