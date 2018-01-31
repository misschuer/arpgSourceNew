--3v3ÿ����������
function Rank3v3kuafuWeek()
	--[[outFmtDebug("Rank3v3kuafuWeek11")
	
	local ranklist = app.kuafu_rank
	
	--local pid = globalGameConfig:GetPlatformID()
	local sid = globalGameConfig:GetServerID()
	
	outFmtDebug("Rank3v3kuafuWeek22--%s",sid)
	
	local server = string.split(sid,"_")
	
	for i,v in ipairs(ranklist) do
		--outFmtDebug("rank %d,%s,%d",i,v[1],v[5])
		local serAry = string.split(v[1],",")
		--��������
		if serAry[1] == server[1] and serAry[2] == server[2] then
			local config = Rank3v3GetWeekReward(i)
			local rewardStr = ""
			for s,d in ipairs(config.reward) do
				if s > 1 then
					rewardStr = rewardStr .. ","
				end
				rewardStr = rewardStr..d[1]..","..d[2]
			end
			AddGiftPacksData(v[6],0,GIFT_PACKS_TYPE_3V3_WEEK,os.time(),os.time() + 86400*30, config.mailname, config.maildesc, rewardStr, SYSTEM_NAME)
		end
		
	end--]]
	
end

--3v3ÿ�ܽ���ȡ�����
function Rank3v3GetWeekReward(rank)
	for _,v in ipairs(tb_kuafu3v3_week_reward) do
		if rank >= v.rank[1] and rank <= v.rank[2] then
			return v
		end
	end
end

--3v3ÿ�¶�λ����
function PlayerInfo:Rank3v3SegmentReward()
	
	--[[local kftime = globalGameConfig:GetKaiFuShiJian()
	local curtime = os.time()
	local intervalTime = 28 * 24 * 60 * 60
	
	local ktime = curtime - ((curtime - kftime)%intervalTime) 
	
	local instMgr = self:getInstanceMgr()
	local lastTime = instMgr:get3v3SegmentTime()
	if lastTime == 0 then
		lastTime = kftime
	end
	
	--outFmtDebug("Rank3v3SegmentReward %d,%d,%d",lastTime,ktime,kftime)
	
	--����
	if lastTime >= ktime then
		return
	end
	
	local curscore = self:GetKuafu3v3TotalScore()
	local flag = 0
	for i,v in ipairs(tb_kuafu3v3_month_reward) do
		if curscore >= v.score then
			flag = i
		else
			break
		end
	end
	
	
	
	local config = tb_kuafu3v3_month_reward[flag]
	
	if not config then
		return
	end
	
	if #config.reward == 0 then
		instMgr:set3v3SegmentTime(ktime)
		return
	end
	--outFmtDebug("curscore %d,%d",curscore,flag)
	local rewardStr = ""
	for s,d in ipairs(config.reward) do
		if s > 1 then
			rewardStr = rewardStr .. ","
		end
		rewardStr = rewardStr..d[1]..","..d[2]
	end
	
	AddGiftPacksData(self:GetGuid(),0,GIFT_PACKS_TYPE_3V3_MONTH,os.time(),os.time() + 86400*30, config.mailname, config.maildesc, rewardStr, SYSTEM_NAME)
	
	--����ʱ�� �������
	instMgr:set3v3SegmentTime(ktime)
	self:SetKuafu3v3TotalScore(0)--]]
	
	
end


function PlayerInfo:Reset3V3daily()
	local instMgr = self:getInstanceMgr()
	for i = 1, #tb_kuafu3v3_day_reward do
		instMgr:set3v3DayReward(i, 0)
	end
end