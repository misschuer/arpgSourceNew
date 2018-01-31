InstanceResGold = class("InstanceResGold", InstanceResBase)

InstanceResGold.Name = "InstanceResGold"
InstanceResGold.exit_time = 10
InstanceResGold.broadcast_nogrid = 1

function InstanceResGold:ctor(  )
	
end


function InstanceResGold:InitRes(config)
	outFmtDebug("gold-----------------------")
end


function InstanceResGold:ApplyRefreshMonsterBatch(batchIdx)
	outFmtDebug("gold shua guai ************")
	
	
	local id = self:GetIndex()
	local config = tb_instance_res[ id ]
	local plev = config.level
	local cnt = config.monsternum
	local entry = config.monster[1]
	local monsterposlist = config.monsterInfo
	
	
	for i = 1, cnt do
		--randInt(0, self.RefreshOffset)
		local bornPos = monsterposlist[1]
		local bornPos2 = monsterposlist[2]
		
		
		local bornX = randInt(bornPos[ 1 ],bornPos2[1])
		local bornY = randInt(bornPos[ 2 ],bornPos2[2])

		local creature = mapLib.AddCreature(self.ptr, 
			{templateid = entry, x = bornX, y = bornY, level=plev, active_grid = true, alias_name = config.name, 
			ainame = "AI_res", attackType = REACT_AGGRESSIVE, npcflag = {}})
		
	end
	
	return true,cnt
end

return InstanceResGold