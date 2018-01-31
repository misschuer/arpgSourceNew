InstanceResZhenQi = class("InstanceResZhenQi", InstanceResBase)

InstanceResZhenQi.Name = "InstanceResZhenQi"
InstanceResZhenQi.exit_time = 10
--ˢ������ƫ��ֵ
InstanceResZhenQi.RefreshOffset = 3;
InstanceResZhenQi.broadcast_nogrid = 1

function InstanceResZhenQi:ctor(  )
	
end


function InstanceResZhenQi:InitRes(config)
	outFmtDebug("zhenqi-----------------------")
end


function InstanceResZhenQi:ApplyRefreshMonsterBatch(batchIdx)
	outFmtDebug("zhen qi shua guai ************")
	--local batchPos = self:GetRandomMonsterIndex(batchIdx)

	--if batchPos == 0 then
	--	return false,0
	--end
	
	local id = self:GetIndex()
	local config = tb_instance_res[ id ]
	local plev = config.level
	local cnt = config.monsternum
	local monsterlist = config.monster
	local monsterposlist = config.monsterInfo

	local ds = 0
	for i = 1, cnt do

		for j = 1,#monsterlist do
			
			local bornPos = monsterposlist[j]
			local bornX = bornPos[ 1 ] + randInt(0, self.RefreshOffset)
			local bornY = bornPos[ 2 ] + randInt(0, self.RefreshOffset)
			local entry = monsterlist[j]

			local indx = REFRESH_MONSTER_FIELD_INFO_START + ds * 2
			self:SetUInt16(indx, 0, entry)
			self:SetUInt16(indx, 1, plev)
			self:SetUInt16(indx+1, 0, bornX)
			self:SetUInt16(indx+1, 1, bornY)
			ds = ds + 1
		end
		
	end
	cnt = cnt * #monsterlist
	
	self:SetUInt16(REFRESH_MONSTER_FIELD_ID, 0, 0)
	self:SetUInt16(REFRESH_MONSTER_FIELD_ID, 1, cnt)
	
	mapLib.DelTimer(self.ptr, 'OnTimer_MonsterBornOneByOne')
	mapLib.AddTimer(self.ptr, 'OnTimer_MonsterBornOneByOne', self.MonsterRefreshInterval)
	
	return true,cnt
end

function InstanceResZhenQi:OnTimer_MonsterBornOneByOne()
	local dids = self:GetUInt16(REFRESH_MONSTER_FIELD_ID, 0)
	local need = self:GetUInt16(REFRESH_MONSTER_FIELD_ID, 1)
	if dids >= need then
		return false
	end
	
	
	local indx = dids * 2 + REFRESH_MONSTER_FIELD_INFO_START
	self:CreateMonster(indx)

	indx = indx + 2
	self:CreateMonster( indx)
	
	self:AddUInt16(REFRESH_MONSTER_FIELD_ID, 0, 2)
	
	return true
end

function InstanceResZhenQi:CreateMonster( indx)
	local entry = self:GetUInt16(indx  , 0)
	local level = self:GetUInt16(indx  , 1)
	local bornX = self:GetUInt16(indx+1, 0)
	local bornY = self:GetUInt16(indx+1, 1)
	
	local creature = mapLib.AddCreature(self.ptr, 
			{templateid = entry, x = bornX, y = bornY, level=level, active_grid = true, 
			ainame = "AI_res", npcflag = {}, attackType = REACT_AGGRESSIVE})
	
end

return InstanceResZhenQi