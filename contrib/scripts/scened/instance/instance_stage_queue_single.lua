InstanceStageQueueSingle = class("InstanceStageQueueSingle", InstanceStageBase)

InstanceStageQueueSingle.Name = "InstanceStageQueueSingle"
InstanceStageQueueSingle.exit_time = 10
--刷新坐标偏移值
InstanceStageQueueSingle.RefreshOffset = 1;

InstanceStageQueueSingle.MonsterRefreshInterval = 500


function InstanceStageQueueSingle:ctor(  )
	
end

function InstanceStageQueueSingle:InitRes(config)
	self:SetRandomMonsterIndex(config.refresnum)
end

--设置每波怪刷新的次序
function InstanceStageQueueSingle:SetRandomMonsterIndex(num)
	local tab = GetRandomIndexTable(num,num)
	for i=1,#tab do
		if i <= 4 then
			self:SetByte(MAP_INT_FIELD_RESERVE2,i-1,tab[i])
		elseif i <= 8 then
			self:SetByte(MAP_INT_FIELD_RESERVE3,i-5,tab[i])
		end
		--print(i-1,tab[i])
	end
end

function InstanceStageQueueSingle:GetRandomMonsterIndex(idx)
	if idx <= 3 then
		return self:GetByte(MAP_INT_FIELD_RESERVE2,idx)
	elseif idx <= 7 then
		return self:GetByte(MAP_INT_FIELD_RESERVE3,idx-4)
	end
	
	return 0
end

function InstanceStageQueueSingle:ApplyRefreshMonsterBatch(batchIdx)
	outFmtDebug("ApplyRefreshMonsterBatch base")
	local batchPos = self:GetRandomMonsterIndex(batchIdx)

	if batchPos == 0 then
		return false,0
	end
	
	local id = self:GetIndex()
	local config = tb_instance_stage[ id ]
	local entry = config.monster[batchPos]
	local plev = config.monsterlevel
	local bornPos = config.monsterInfo[batchPos]
	local cnt = config.monsternum
	
	outFmtDebug("ApplyRefreshMonsterBatch %d %d  %s ",id,entry,bornPos)
	--REFRESH_MONSTER_FIELD_ID			=	MAP_INT_FIELD_INSTANCE_TYPE + 1,	//2个short(0:当前已经刷的,1:总共需要刷多少怪
	for i = 1, cnt do
		local bornX = bornPos[ 1 ] + randInt(0, self.RefreshOffset)
		local bornY = bornPos[ 2 ] + randInt(0, self.RefreshOffset)
		local indx = REFRESH_MONSTER_FIELD_INFO_START + (i - 1) * 2
		self:SetUInt16(indx, 0, entry)
		self:SetUInt16(indx, 1, plev)
		self:SetUInt16(indx+1, 0, bornX)
		self:SetUInt16(indx+1, 1, bornY)
	end
	self:SetUInt16(REFRESH_MONSTER_FIELD_ID, 0, 0)
	self:SetUInt16(REFRESH_MONSTER_FIELD_ID, 1, cnt)
	
	mapLib.DelTimer(self.ptr, 'OnTimer_MonsterBornOneByOne')
	mapLib.AddTimer(self.ptr, 'OnTimer_MonsterBornOneByOne', self.MonsterRefreshInterval)
	
	return true,cnt
end

function InstanceStageQueueSingle:OnTimer_MonsterBornOneByOne()
	local dids = self:GetUInt16(REFRESH_MONSTER_FIELD_ID, 0)
	local need = self:GetUInt16(REFRESH_MONSTER_FIELD_ID, 1)
	if dids >= need then
		return false
	end
	
	local indx = dids * 2 + REFRESH_MONSTER_FIELD_INFO_START
	local entry = self:GetUInt16(indx  , 0)
	local level = self:GetUInt16(indx  , 1)
	local bornX = self:GetUInt16(indx+1, 0)
	local bornY = self:GetUInt16(indx+1, 1)
	--outFmtDebug("%d,%d,%d,%d",entry, bornX, bornY, level)
	local creature = mapLib.AddCreature(self.ptr, 
			{templateid = entry, x = bornX, y = bornY, level=level, active_grid = true, 
			ainame = "AI_stage", npcflag = {}, attackType = REACT_AGGRESSIVE})
	
	self:AddUInt16(REFRESH_MONSTER_FIELD_ID, 0, 1)
	
	return true
end

return InstanceStageQueueSingle