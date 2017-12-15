
--�����ϴ�����id
function PlayerInfo:SetGuideIdLast(id)
	self:SetUInt32(PLAYER_INT_FIELD_GUIDE_ID_LAST,id)
end
--����ϴ�����id
function PlayerInfo:GetGuideIdLast()
	return self:GetUInt32(PLAYER_INT_FIELD_GUIDE_ID_LAST,id)

end
--���õ�ǰ����id �����ϴ�����id
function PlayerInfo:SetGuideIdNow(id)
	if id < 1 then
		return
	end
	local now_id = self:GetGuideIdNow()
	self:SetGuideIdLast(now_id)
	self:SetUInt32(PLAYER_INT_FIELD_GUIDE_ID_NOW,id)
end
--��õ�ǰ����id
function PlayerInfo:GetGuideIdNow()
	return self:GetUInt32(PLAYER_INT_FIELD_GUIDE_ID_NOW,id)

end


function PlayerInfo:UpdateGuideIdByTaskId (task_id)
	local taskInfo = tb_quest[task_id]
	if not taskInfo then
		return
	end
	local guide_id =  taskInfo.guide_id
	if guide_id > 0 then
		self:SetGuideIdNow(guide_id)
	end
end

function PlayerInfo:UpdateFinishGuideIdByTaskId (task_id)
	local taskInfo = tb_quest[task_id]
	if not taskInfo then
		return
	end
	local guide_id =  taskInfo.finish_guide_id
	if guide_id > 0 then
		self:SetGuideIdNow(guide_id)
	end
end

function PlayerInfo:UpdateGuideIdByModuleId (module_id)
	local moduleInfo = tb_system_base[module_id]
	if not moduleInfo then
		return
	end
	-- ǿ������
	local guide_id =  moduleInfo.guide_id
	if guide_id > 0 then
		self:SetGuideIdNow(guide_id)
	end
	
	-- ��ǿ������
	if moduleInfo.optional_guide_id then
		self:AddOptionalGuideId(moduleInfo.optional_guide_id)
	end
end

-- ��ӷ�ǿ������
function PlayerInfo:AddOptionalGuideId(guide_id)

	for i = PLAYER_INT_FIELD_OPTIONAL_GUIDE_START, PLAYER_INT_FIELD_OPTIONAL_GUIDE_END-1, 2 do
		if self:GetUInt32(i) == 0 then
			self:SetUInt32(i, guide_id)
			break
		end
	end
end

-- һ����ǿ�Ƶ�ĳ�����������
function PlayerInfo:OptionalGuideClicked(guide_id, step)
	if guide_id == 0 then
		return
	end
	for i = PLAYER_INT_FIELD_OPTIONAL_GUIDE_START, PLAYER_INT_FIELD_OPTIONAL_GUIDE_END-1, 2 do
		if self:GetUInt32(i) == guide_id then
			if step >= self:GetUInt32(i+1) then
				step = math.min(step, 12)
				self:SetUInt32(i+1, step+1)
			end
			return
		end
	end
end