
local XIULIANCHANG_MAP_ID = 3005
local ROBOT_CHEST_NUM = 3
--C++�ӿ�
function PlayerInfo:LogoutBackupCultivation()
	playerLib.SetCultivation(self:GetGuid(), self:GetCultivationStartTime(),self:GetCultivationLostInfo(),self:GetWeapon(),self:GetAvatar(),self:GetDivine(),self:GetVIP())
end

function PlayerInfo:LoginRestoreCultivation()
	local info = playerLib.GetCultivation(self:GetGuid(),-1)
	if info ~= nil and info[1] ~= 0  then
		outFmtDebug("LoginRestoreCultivation : tiem:%d , lost: %d",info[1],info[2])
		self:SetCultivation(info[1],info[2])
	end
end


--�����Լ�����������Ϣ
function PlayerInfo:SetCultivation(time,lost)
	--playerLib.SetCultivation(self:GetGuid(), time,lost,self:GetWeapon(),self:GetAvatar(),self:GetDivine(),self:GetVIP())
	self:SetCultivationStartTime(time)
	self:SetCultivationLostInfo(lost)
end

function PlayerInfo:SetCultivationStartTime(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_START_TIME,value)
end

function PlayerInfo:GetCultivationStartTime()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_START_TIME)
end

function PlayerInfo:SetCultivationLostInfo(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_LOST_INFO,value)
end
function PlayerInfo:GetCultivationLostInfo()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_LOST_INFO)
end

--����guid��Ӧ��ɫ��������Ϣ��ĳ�� index[0~5] 0:time 1:lost 2:weapon 3:avatar 4:divine 5:vip
function PlayerInfo:SetCultivationIndex(guid,index,value)
	--playerLib.SetCultivationByIndexValue(guid,index,value)
	local player = app.objMgr:getObj(guid)
	-- û�оͼ������ļ�
	if not player or not player:isLogined() then 
		playerLib.SetCultivationByIndexValue(guid,index,value)
	else
		if index ==0 then
			player:SetCultivationStartTime(value)
		elseif index == 1 then
			player:SetCultivationLostInfo(value)
		end
	end
	
end
--��ȡguid��Ӧ��ɫ��������Ϣ ��ʱû����
function PlayerInfo:GetCultivation(guid)
	--local info = playerLib.GetCultivation(guid, -1)
	--return info
end
--��ȡguid��Ӧ��ɫ��������Ϣ��ĳ��
function PlayerInfo:GetCultivationIndex(guid,index)
	--[[
	local info = playerLib.GetCultivation(guid, index)
	if info ~= nil then
		return info[1]
	else
		return 0 --δ�������� �������˴Ӷ���̨�鵽�� ����Ϊ0
	end
	--]]
	local player = app.objMgr:getObj(guid)
	-- û�оͼ������ļ�
	if not player  or not player:isLogined()  then 
		local info = playerLib.GetCultivation(guid,index)
		if info ~= nil then
			return info[1]
		else
			return 0 --δ�������� �������˴Ӷ���̨�鵽�� ����Ϊ0
		end
	else
		if index ==0 then
			return player:GetCultivationStartTime()
		elseif index == 1 then
			return player:GetCultivationLostInfo()
		elseif index ==5 then
			return player:GetVIP()
		end
	end
	
end


--binlog�ӿ�
--10��������¼(guid, ���, �Ƿ��Ӷ�,ʱ��) ��ǰ4������(guid)  �����ۼ��Ӷᾭ�� �����ۼ��Ӷᱦ����  ��ǰʣ����ս���� ���չ������ �ϴ���������սʱ���  �ϴ�ˢ�¶���ʱ�� ���ֱ��Ӷ�ɹ����� �������Ӷ���� 

--�ϴ���սʱ���
function PlayerInfo:SetCultivationLastPlunderTime(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_LAST_PLUNDER_TIME,value)
end

function PlayerInfo:GetCultivationLastPlunderTime()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_LAST_PLUNDER_TIME)
end

--�ϴ�ˢ�¶���ʱ��
function PlayerInfo:SetCultivationLastRefreshTime(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_LAST_REFRESH_TIME,value)
end

function PlayerInfo:GetCultivationLastRefreshTime()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_LAST_REFRESH_TIME)
end

--�����ۼ��Ӷᾭ��
function PlayerInfo:SetCultivationTodayPlunderExp(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_EXP,value)
end

function PlayerInfo:GetCultivationTodayPlunderExp()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_EXP)
end

function PlayerInfo:AddCultivationTodayPlunderExp(value)
	return self:AddUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_EXP,value)
end

--�����ۼ��Ӷᱦ����
function PlayerInfo:SetCultivationTodayPlunderChest(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_CHEST,value)
end

function PlayerInfo:GetCultivationTodayPlunderChest()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_CHEST)
end

function PlayerInfo:AddCultivationTodayPlunderChest(value)
	return self:AddUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_CHEST,value)
end

--���չ������
function PlayerInfo:SetCultivationTodayPurchaseCount(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PURCHASE_COUNT,value)
end

function PlayerInfo:GetCultivationTodayPurchaseCount()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PURCHASE_COUNT)
end

function PlayerInfo:AddCultivationTodayPurchaseCount(value)
	return self:AddUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_PURCHASE_COUNT,value)
end

--��ǰʣ����ս����
function PlayerInfo:SetCultivationLeftPlunderCount(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_LEFT_PLUNDER_COUNT,value)
end

function PlayerInfo:GetCultivationLeftPlunderCount()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_LEFT_PLUNDER_COUNT)
end

function PlayerInfo:AddCultivationLeftPlunderCount(value)
	return self:AddUInt32(PLAYER_INT_FIELD_CULTIVATION_LEFT_PLUNDER_COUNT,value)
end

--10��������¼�±�
function PlayerInfo:SetCultivationPlunderRecordIndex(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_PLUNDER_RECORD_INDEX,value)
end

function PlayerInfo:GetCultivationPlunderRecordIndex()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_PLUNDER_RECORD_INDEX)
end

function PlayerInfo:AddCultivationPlunderRecordIndex(value)
	return self:AddUInt32(PLAYER_INT_FIELD_CULTIVATION_PLUNDER_RECORD_INDEX,value)
end
--���ֱ��Ӷ�ɹ�����

function PlayerInfo:SetCultivationTotalBeenPlunderCount(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_TOTAL_BEEN_PLUNDER_COUNT,value)
end

function PlayerInfo:GetCultivationTotalBeenPlunderCount()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_TOTAL_BEEN_PLUNDER_COUNT)
end

function PlayerInfo:AddCultivationTotalBeenPlunderCount(value)
	return self:AddUInt32(PLAYER_INT_FIELD_CULTIVATION_TOTAL_BEEN_PLUNDER_COUNT,value)
end

--�������Ӷ����
function PlayerInfo:SetCultivationTodayTotalPlunderCount(value)
	self:SetUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_TOTAL_PLUNDER_COUNT,value)
end

function PlayerInfo:GetCultivationTodayTotalPlunderCount()
	return self:GetUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_TOTAL_PLUNDER_COUNT)
end

function PlayerInfo:AddCultivationTodayTotalPlunderCount(value)
	return self:AddUInt32(PLAYER_INT_FIELD_CULTIVATION_TODAY_TOTAL_PLUNDER_COUNT,value)
end

--��ǰ4������guid
function PlayerInfo:SetCultivationRivalGuid(index,value)
	if index <0 or index >= MAX_PLAYER_CULTIVATION_RIVAL_COUNT then
		return
	end
	self:SetStr(PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_START+index,value)
end

function PlayerInfo:GetCultivationRivalGuid(index)
	if  index >=0 and index < MAX_PLAYER_CULTIVATION_RIVAL_COUNT then
		return self:GetStr(PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_START+index)
	else
		return nil
	end
end

--10��������¼
function PlayerInfo:SetCultivationPlunderRecord(index, value)
	
	self:SetStr(PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_START + index,value)
end


--������1
function PlayerInfo:CultivationPlunderRecordNext()
	local cur_num = self:GetCultivationPlunderRecordIndex()
	if(cur_num >= MAX_PLAYER_CULTIVATION_PLUNDER_RECORD_COUNT-1)then		--��ౣ��MAX_PLAYER_CULTIVATION_PLUNDER_RECORD_COUNT
		self:SetCultivationPlunderRecordIndex(0)	
	else
		self:AddCultivationPlunderRecordIndex(1)
	end
end	

--���һ����¼��Ϣ guid |���� |���(0:����ս��ʤ��-���� 1:����ս��ʧ��-����) |���(0:δ���Ӷ� 1~n:n�ű��䱻�Ӷ�) |ʱ��� |������ʶ(0:δ���� 1:�ѷ���)
function PlayerInfo:AddCultivationPlunderRecord(guid,robot_id, name, lv, result, flag, time, revenge)
	local info = guid..'|'..robot_id..'|'..name..'|'..lv..'|'..result..'|'..flag..'|'..time..'|'..revenge
	local index = self:GetCultivationPlunderRecordIndex()
	self:SetCultivationPlunderRecord(index, info)
	self:CultivationPlunderRecordNext()
	
	outFmtDebug("AddCultivationPlunderRecord:%s",info)
	return 1
end

--ȡ��һ����¼��Ϣ
function PlayerInfo:GetCultivationPlunderRecord(index)
	if  index >=0 and index < MAX_PLAYER_CULTIVATION_PLUNDER_RECORD_COUNT then
		local info = self:GetStr(PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_START + index)
		return info
	else
		return nil
	end
end

--�޸ļ�¼������Ϊ1
function PlayerInfo:SetCultivationPlunderRecordAfterRevenge(index)
	local info = self:GetCultivationPlunderRecord(index)
	local values = string.split(info, "|")

	local new_info = values[1]..'|'..values[2]..'|'..values[3]..'|'..values[4]..'|'..values[5]..'|'..values[6]..'|'..values[7]..'|'..'1'
	
	self:SetCultivationPlunderRecord(index,new_info)
	
end




--ҵ��ӿ�

--�жϸù���ģ���Ƿ���  ����ˢ�¶���ʱ���ж�
function PlayerInfo:IsCultivationUnlocked()
	if self:GetCultivationLastRefreshTime() == 0 then
		return false
	else
		return true
	end
end

--ģ�����ʱ��ʼ��
function PlayerInfo:InitCultivation()
	local now_time = os.time()
	--ˢ�¶���
	self:SetCultivationLastRefreshTime(1)
	self:RefreshCultivationRivals()
	--���ÿ��ô���Ϊ���
	local max_count = tb_xiulianchang_base[1].max_plunder_recover_count
	self:SetCultivationLeftPlunderCount(max_count)
	--����c++���� ��ʼ����ʱ�� ����δ��ǿ��
	self:SetCultivation(now_time,0)
end

--ÿ������ ��ս���� ���ռ�¼
function PlayerInfo:DailyResetCultivation()
	if not self:IsCultivationUnlocked() then
		return
	end
	--��ձ����������
	self:SetCultivationTodayPlunderExp(0)
	self:SetCultivationTodayPlunderChest(0)
	self:SetCultivationTodayPurchaseCount(0)
	self:SetCultivationTodayTotalPlunderCount(0)
end


--ÿ1s����/����ʱ���� ��ս��������
function PlayerInfo:UpdateCultivation()
	if not self:IsCultivationUnlocked() then
		
		return
	end
	--���ʱ�� �������������ӿ����Ӷ����
	local start_time =  self:GetCultivationLastPlunderTime()
	local current_count = self:GetCultivationLeftPlunderCount()
	local recover_time = tb_xiulianchang_base[1].plunder_recover_time
	local max_recover_count = tb_xiulianchang_base[1].max_plunder_recover_count
	local now_time = os.time()
	if current_count >= max_recover_count then
		return
	end
	local recover = 0
	while (now_time - start_time >= recover_time) do
		recover = recover + 1
		start_time = start_time + recover_time
		current_count = current_count + 1
		if current_count >= max_recover_count then
			self:AddCultivationLeftPlunderCount(recover)
			self:SetCultivationLastPlunderTime(start_time)
			return
		end
	end
	if recover > 0 then
		self:AddCultivationLeftPlunderCount(recover)
		self:SetCultivationLastPlunderTime(start_time)
	end
	
end

--��ȡ��������״̬ ���ؿͻ���  (������ʼʱ��,������״̬)
function PlayerInfo:GetCultivationInfo()
	if not self:IsCultivationUnlocked() then
		return
	end
	local start_time = self:GetCultivationIndex(self:GetGuid(),0)
	local lost_info = self:GetCultivationIndex(self:GetGuid(),1)
	self:call_update_cultivation_info(start_time, lost_info)
end
--��ȡƥ����ֽ�ɫ��Ϣ ���ؿͻ��� �Զ���ṹrival_info:(index  ���� �ȼ� ��� ���� ��� ս�� ��������)
function PlayerInfo:GetCultivationRivalsInfo()
	if not self:IsCultivationUnlocked() then
		return
	end
	local list = {}
	for i=0,3 do
		local info = 	self:GetCultivationRivalGuid(i)
		local temp = string.split(info,'@')
		if #temp ~= 2 then
			return
		end
		local token = string.split(temp[1],'|')
		if #token ~= 2 then
			return
		end
		local rank = 0
		local guid = token[1]
		local robot_id = tonumber(token[2])
		local content = temp[2]

		if rank ~= 0 then --����̨���ж�Ӧ���� --��if����������
			local config = globalCounter:GetRankInfo(rank)
			local stru = cultivation_rivals_info_t .new()
			stru.index	= i
			stru.name 	= config.name
			stru.level	= config.level
			stru.weapon	= config.weapon
			stru.avatar	= config.avatar
			stru.divine	= config.divine
			stru.force	= config.force
			if string.len(config.guid) <= 0 then
				stru.chest = ROBOT_CHEST_NUM
			else
				local vip = config.vip
				local start_time = self:GetCultivationIndex(config.guid,0)  --��δ���� �����ɼ���
				local lost_info = self:GetCultivationIndex(config.guid,1)
				if start_time == 0 and lost_info == 0 then
					stru.chest = 1
				else
					local lost_list = self:LostInfoToList(lost_info)
					local vip_info = tb_xiulianchang_vip[vip]
					local time_limit = vip_info.time_limit
					--��������ʱ��
					local cultivation_time = os.time() - start_time
					
					if cultivation_time < tb_xiulianchang_base[1].get_reward_time_limit then
						stru.chest	= 0
					else
						if cultivation_time > time_limit then
							cultivation_time = time_limit
						end
						local count = 0
						for index,info in ipairs(tb_xiulianchang_reward) do
							if cultivation_time >= info.time and not IsKeyInTable(index,lost_list) then
								count = count + 1
								
							end
						end
						stru.chest = count 
					end
				end
				
				
			end
			stru.gender = config.gender
			table.insert(list, stru)
			
		elseif robot_id ~= 0 then --������������
			local config = tb_xiulianchang_dummy[robot_id]
			local stru = cultivation_rivals_info_t .new()
			stru.index	= i
			stru.name 	= config.name
			stru.level	= config.level
			stru.weapon	= config.weapon
			stru.avatar	= config.avatar
			stru.divine	= config.divine
			stru.force	= config.force
			stru.chest	= ROBOT_CHEST_NUM 
			stru.gender	= config.gender
			table.insert(list, stru)
		else --��content�л�ȡ
			local config = GetDummyInfoFromContent(content)
			local tempcontent = ''
			if string.len(config.guid) > 0 then --������������
				local data = {}
				data.name = 'Handle_GetCultivationRivalsInfo'
				data.callback_guid = config.guid
				data.my_guid = self:GetGuid()
				function data.fun (data, objs)
					outFmtDebug("callbacked ===================")
					local targetPlayer = objs[data.callback_guid]
					if not targetPlayer then return end
					outFmtDebug("target player = %s", targetPlayer:GetGuid())
					
					local tempconfig = targetPlayer:GetDummyInfo()
					tempcontent =  JoinDummyInfoIntoContent(data.callback_guid,tempconfig)
				end
				GetObjects(data)
			end
			if tempcontent ~= '' then
				config = GetDummyInfoFromContent(tempcontent)
			end
			local stru = cultivation_rivals_info_t .new()
			stru.index	= i
			stru.name 	= config.name
			stru.level	= config.level
			stru.weapon	= config.weapon
			stru.avatar	= config.avatar
			stru.divine	= config.divine
			stru.force	= config.force
			if string.len(config.guid) <= 0 then
				stru.chest = ROBOT_CHEST_NUM
			else
				local vip = config.vip
				local start_time = self:GetCultivationIndex(config.guid,0)  --��δ���� �����ɼ���
				local lost_info = self:GetCultivationIndex(config.guid,1)
				if start_time == 0 and lost_info == 0 then
					stru.chest = 1
				else
					local lost_list = self:LostInfoToList(lost_info)
					local vip_info = tb_xiulianchang_vip[vip]
					local time_limit = vip_info.time_limit
					--��������ʱ��
					local cultivation_time = os.time() - start_time
					
					if cultivation_time < tb_xiulianchang_base[1].get_reward_time_limit then
						stru.chest	= 0
					else
						if cultivation_time > time_limit then
							cultivation_time = time_limit
						end
						local count = 0
						for index,info in ipairs(tb_xiulianchang_reward) do
							if cultivation_time >= info.time and not IsKeyInTable(index,lost_list) then
								count = count + 1
								
							end
						end
						stru.chest = count 
					end
				end
				
				
			end
			stru.gender = config.gender
			table.insert(list, stru)
		end
	end

	self:call_update_cultivation_rivals_info_list(list)
end

--��ȡ��������
function PlayerInfo:GetCultivationReward()
	if not self:IsCultivationUnlocked() then
		return
	end
	--ȡ��������ʼʱ�� ����״̬
	local start_time = self:GetCultivationIndex(self:GetGuid(),0)
	local lost_info = self:GetCultivationIndex(self:GetGuid(),1)
	local lost_list = self:LostInfoToList(lost_info)
	
	--IsKeyInTable(1,lost_list)
	--�ж�����ʱ���Ƿ��㹻������ȡ
	--���ݽ�ɫ�ȼ� vip�ȼ� ����ʱ�� ���Ӷ���� �������  ��������
	local vip = self:GetVIP()
	local vip_info = tb_xiulianchang_vip[vip]
	local time_limit = vip_info.time_limit
	
	

	--��������ʱ��
	local cultivation_time = os.time() - start_time
	if cultivation_time < tb_xiulianchang_base[1].get_reward_time_limit then
		return
	end

	if cultivation_time > time_limit then
		cultivation_time = time_limit
	end
	
	local next_exp = tb_char_level[self:GetLevel()].next_exp
	local extend_exp_reward  = vip_info.extend_exp_reward
	local base_exp_reward = tb_xiulianchang_base[1].base_exp_reward
	local base_exp_time_unit = tb_xiulianchang_base[1].base_exp_time_unit
	local plunder_exp_lost = tb_xiulianchang_base[1].plunder_exp_lost
	local been_plunder_count = self:GetCultivationTotalBeenPlunderCount()
	local max_been_plunder_count = tb_xiulianchang_base[1].max_been_plunder_count
	if been_plunder_count > max_been_plunder_count then
		been_plunder_count = max_been_plunder_count
	end
	
	local exp_reward = math.floor(math.floor(cultivation_time / base_exp_time_unit)* math.floor(next_exp * (base_exp_reward/10000))*(extend_exp_reward/100 + 1)*(1 - been_plunder_count * plunder_exp_lost / 10000))
	
	local rewards = {}
	table.insert(rewards,{Item_Loot_Exp,exp_reward}) --�Ӿ���
	for index,info in ipairs(tb_xiulianchang_reward) do
		if cultivation_time >= info.time and not IsKeyInTable(index,lost_list) then
			for k,v in ipairs(info.reward) do
				table.insert(rewards,v)
			end
			
		end
	end
	self:AppdAddItems(rewards,MONEY_CHANGE_CULTIVATION_REWARD,LOG_ITEM_OPER_TYPE_CULTIVATION_REWARD)
	
	--����������ʼʱ��
	--����c++���� ��ʼ����ʱ�� ����δ��ǿ��
	self:SetCultivation(os.time(),0)
	--���㱻�Ӷ�ɹ�����
	self:SetCultivationTotalBeenPlunderCount(0)
	
	self:GetCultivationInfo()
	
end

function PlayerInfo:LostInfoToList(info)
	local list = {}
	local i = 1
	while info ~= 0 do
		local flag  = info % 2
		info = math.floor(info / 2)
		if flag == 1 then
			list[i] = flag
		end
		i = i + 1
	end
	return list
end

function PlayerInfo:ListToLostInfo(list)
	local info = 0
	for i,flag in pairs(list) do
		info = info + flag * 2^(i-1)
	end
	return info
end

function PlayerInfo:CanRefreshCultivationRivals()
	local last_time = self:GetCultivationLastRefreshTime()
	if os.time() - last_time > tb_xiulianchang_base[1].rival_refresh_cd then
		return true
	else
		return false
	end
end

--ˢ��ƥ�����
function PlayerInfo:RefreshCultivationRivals()
	if not self:IsCultivationUnlocked() then
		return
	end
	if not self:CanRefreshCultivationRivals() then
		return
	end
	--ƥ���ȡ ���guid�������id 
	local player_rank = self:GetDoujiantaiRank()
	local indx = #tb_xiulianchang_fight_range
	
	for i = 1, #tb_xiulianchang_fight_range do
		local config = tb_xiulianchang_fight_range[i]
		if config.ra <= player_rank and player_rank <= config.rb then
			indx = i
			break
		end
	end
	ranges = tb_xiulianchang_fight_range[indx].chooseRange
	robot_count = tb_xiulianchang_fight_range[indx].robot_count
	
	local dict = {}
	for _, range in pairs(ranges) do
		local rank = player_rank
		if rank == 0 then
			rank = MAX_DOUJIANTAI_RANK_COUNT + 1
		end
		
		local l = rank - range[ 2 ]
		local r = rank - range[ 1 ]
		if l <=0 then
			l = 1
		end
		if r >= MAX_DOUJIANTAI_RANK_COUNT +1 then
			r = MAX_DOUJIANTAI_RANK_COUNT
		end
		
		local rank = randInt(l, r)
		--rank = 924 --���Թ̶�rank����
		
		if  rank == player_rank then
			outFmtDebug('RefreshCultivationRivals: error rank == player_rank')
			return
		end
		if rank > 0 then
			local config = globalCounter:GetRankInfo(rank)
			if string.len(config.guid) > 0 then
				local content =  JoinDummyInfoIntoContent(config.guid,config)
				table.insert(dict, config.guid .. '|0@'..content ) --��һ�μ�¼����̨����guid �ڶ���Ϊ0 ������Ϊ���content
			else
				local content =  JoinDummyInfoIntoContent('',config)
				table.insert(dict,'|0@'..content ) --��һ�μ�¼�մ� �ڶ���Ϊ0 ������Ϊ������content
			end
			
		end
	end
	
	robot_ranges = {{1,250},{251,500},{501,750},{751,1000}}
	for i = 1, robot_count do
		local robot_range = robot_ranges[i]
		local robot_index = randInt(robot_range[1], robot_range[2])
		table.insert(dict, '|' .. robot_index..'@') --��һ��Ϊ�մ� �ڶ���Ϊ����������id ������Ϊ�մ�
	end
	
	
	--dict[1] = '966|0' --���Թ̶�rank����
	for i = 1, #dict do
		outFmtDebug("RefreshCultivationRivals: new rival_%d guid : %s",i,dict[i])
		self:SetCultivationRivalGuid(i-1,dict[i])  
	end
	self:SetCultivationLastRefreshTime(os.time())
	self:GetCultivationRivalsInfo()
end

--�����Ӷ�
function PlayerInfo:PlunderCultivationRival(index)
	if not self:IsCultivationUnlocked() then
		return
	end
	
	--���ʣ����� ������ 
	--����������ʱ��ս,���ÿ�ʼ�ظ�
	if self:GetCultivationLeftPlunderCount() <= 0 then
		return
	end
	if self:GetCultivationLeftPlunderCount() == tb_xiulianchang_base[1].max_plunder_recover_count then
		self:SetCultivationLastPlunderTime(os.time())

	end
	self:AddCultivationLeftPlunderCount(-1)
	--ȡ�ö���guid ��ȡ��ɫ��Ϣ
	--��ս����ش���
	local info = self:GetCultivationRivalGuid(index)
	local temp = string.split(info,'@')
	if #temp ~= 2 then
		return
	end
	local token = string.split(temp[1],'|')
	
	if #token ~= 2 then
		return
	end
	local rank = 0
	local guid = token[1]
	local robot_id = tonumber(token[2])
	local content = temp[2]
	local generalId = string.format("%d|%s|%d|%d|%s@%s", os.time(), self:GetGuid(), rank, robot_id,guid,content)
	local x = tb_xiulianchang_base[ 1 ].bornPos[ 1 ][ 1 ]
	local y = tb_xiulianchang_base[ 1 ].bornPos[ 1 ][ 2 ]
	-- ������
	call_appd_teleport(self:GetScenedFD(), self:GetGuid(), x, y, XIULIANCHANG_MAP_ID, generalId)
	--ˢ�¶���
	self:RefreshCultivationRivals()
end

--���и���
function PlayerInfo:RevengeCultivationRival(index)
	if not self:IsCultivationUnlocked() then
		return
	end
	--����ܷ񸴳�
	local info = self:GetCultivationPlunderRecord(index)
	local token = string.split(info,'|')
	if #token ~= 8 then
		return
	end
	local guid = (token[1])
	local robot_id = tonumber(token[2])
	local revenge = tonumber(token[8])
	if revenge == 1 then
		return
	end
	
	self:SetCultivationPlunderRecordAfterRevenge(index)
	
	local content = ''
	if string.len(guid) > 0 then
		local data = {}
		data.name = 'Handle_RevengeCultivationRival'
		data.callback_guid = guid
		data.my_guid = self:GetGuid()
		function data.fun (data, objs)
			outFmtDebug("callbacked ===================")
			local targetPlayer = objs[data.callback_guid]
			if not targetPlayer then return end
			outFmtDebug("target player = %s", targetPlayer:GetGuid())
			
			local config = targetPlayer:GetDummyInfo()
			content =  JoinDummyInfoIntoContent(guid,config)
		end
		GetObjects(data)
	end
	
	
	
	
	local generalId = string.format("%d|%s|%d|%d|%s@%s", os.time(), self:GetGuid(), 0, robot_id, guid,content)
	local x = tb_xiulianchang_base[ 1 ].bornPos[ 1 ][ 1 ]
	local y = tb_xiulianchang_base[ 1 ].bornPos[ 1 ][ 2 ]
	-- ������
	call_appd_teleport(self:GetScenedFD(), self:GetGuid(), x, y, XIULIANCHANG_MAP_ID, generalId)
	--ȡ�ö���guid ��ȡ��ɫ��Ϣ
	--��ս����ش���
end

--������ս����
function PlayerInfo:BuyCultivationLeftPlunderCount(count)
	if not self:IsCultivationUnlocked() then
		return
	end
	--print('BuyCultivationLeftPlunderCount')
	--��⹺������ vip�ȼ� �����������
	local vip = self:GetVIP()
	local vip_info = tb_xiulianchang_vip[vip]
	if vip_info == nil then
		return
	end
	local buy_limit = vip_info.buy_limit
	local buy_price = vip_info.buy_price
	local current_buy_count = self:GetCultivationTodayPurchaseCount()
	
	if current_buy_count + count > buy_limit then
		return
	end
	
	--���� ����
	if self:costMoneys(MONEY_CHANGE_CULTIVATION_PURCHASE,buy_price,1) then
		self:AddCultivationTodayPurchaseCount(count)
		self:AddCultivationLeftPlunderCount(count)
	end
	
end


function PlayerInfo:PlunderFinish(data, info)
	local token = string.split(info,'|')
	local guid = token[1]
	local robot_id = tonumber(token[2])
	local level = tonumber(token[3]) 
	local result = tonumber(token[4]) 
	local enemy_name = token[5]
	
	if result == GlobalCounter.WIN then
		
		
		if string.len(guid) > 0 then--սʤ���
			local start_time = self:GetCultivationIndex(guid,0)
			local lost_info = self:GetCultivationIndex(guid,1)
			
			local vip = self:GetCultivationIndex(guid,5)
			local vip_info = tb_xiulianchang_vip[vip]
			local time_limit = vip_info.time_limit
			local lost_list = self:LostInfoToList(lost_info)
			
			local next_exp = tb_char_level[level].next_exp
			local plunder_exp_reward = tb_xiulianchang_base[1].plunder_exp_reward
			
			
			local exp_reward = math.floor(next_exp * plunder_exp_reward / 10000)
			
			local rewards = {}
			local lost_chest = 0
			table.insert(rewards,{Item_Loot_Exp,exp_reward}) --�Ӿ���
			
			--��������ʱ��
			local cultivation_time = os.time() - start_time
			
			if cultivation_time > time_limit then
				cultivation_time = time_limit
			end
			if cultivation_time < tb_xiulianchang_base[1].get_reward_time_limit then
				--no chest
			else
				
				for i = #tb_xiulianchang_reward,1,-1 do
					local info = tb_xiulianchang_reward[i]
					if cultivation_time >= info.time and not IsKeyInTable(i,lost_list) then
						local random = randInt(1,10000)
						if random <= info.lost_rate then
							lost_chest = i
							lost_list[i] = 1
							if start_time ~= 0 then-- �Է��ѿ������� �Ų���Ӱ��
								self:SetCultivationIndex(guid,1, self:ListToLostInfo(lost_list))
							end
							for k,v in ipairs(info.reward) do
								table.insert(rewards,v)
							end
							break
						end
							
					end
				end
			end
			
			self:AppdAddItems(rewards,MONEY_CHANGE_CULTIVATION_PLUNDER_REWARD,LOG_ITEM_OPER_TYPE_CULTIVATION_PLUNDER_REWARD)
			
			--���ͽ��
			local list = {}
			for _,v in ipairs(rewards) do
			--����֪ͨ
				local stru = item_reward_info_t .new()
				stru.item_id	= v[1]
				stru.num 		= v[2]
				table.insert(list, stru)
			end
			self:call_show_cultivation_result_list(result,enemy_name,list)
			
			
			self:AddCultivationTodayPlunderExp(exp_reward)
			if lost_chest > 0 then
				self:AddCultivationTodayPlunderChest(1)
			end
			
			if start_time ~= 0 then-- �Է��ѿ������� �Ų���ӡ��
				
			
				local data = {}
				data.name = 'Handle_PlunderFinish'
				data.callback_guid = guid
				data.my_guid = self:GetGuid()
				function data.fun (data, objs)
					outFmtDebug("callbacked ===================")
					local targetPlayer = objs[data.callback_guid]
					if not targetPlayer then return end
					outFmtDebug("target player = %s", targetPlayer:GetGuid())
					
					targetPlayer:AddCultivationTotalBeenPlunderCount(1)
					
					targetPlayer:AddCultivationPlunderRecord(self:GetGuid(),0, self:GetName(), self:GetLevel(), result, lost_chest, os.time(), 0)
					
					
				end
				GetObjects(data)
			end
		else --սʤ������
			local next_exp = tb_char_level[level].next_exp
			local plunder_exp_reward = tb_xiulianchang_base[1].plunder_exp_reward
			
			
			local exp_reward = math.floor(next_exp * plunder_exp_reward / 10000)
			
			local rewards = {}
			local lost_chest = 0
			table.insert(rewards,{Item_Loot_Exp,exp_reward}) --�Ӿ���
			
			for i = ROBOT_CHEST_NUM,1,-1 do
				local info = tb_xiulianchang_reward[i]
				
				local random = randInt(1,10000)
				if random <= info.lost_rate then
					lost_chest = i
					for k,v in ipairs(info.reward) do
						table.insert(rewards,v)
					end
					break
				end

			end
			
			
			self:AppdAddItems(rewards,MONEY_CHANGE_CULTIVATION_PLUNDER_REWARD,LOG_ITEM_OPER_TYPE_CULTIVATION_PLUNDER_REWARD)
			
			--���ͽ��
			local list = {}
			for _,v in ipairs(rewards) do
			--����֪ͨ
				local stru = item_reward_info_t .new()
				stru.item_id	= v[1]
				stru.num 		= v[2]
				table.insert(list, stru)
			end
			self:call_show_cultivation_result_list(result,enemy_name,list)
			
			self:AddCultivationTodayPlunderExp(exp_reward)
			if lost_chest > 0 then
				self:AddCultivationTodayPlunderChest(1)
			end
		end
		
	elseif result == GlobalCounter.LOSE then
		local list = {}
		self:call_show_cultivation_result_list(result,enemy_name,list)
		if string.len(guid) > 0 then--���Է������Ӽ�¼
			local data = {}
			data.name = 'Handle_PlunderFinish'
			data.callback_guid = guid
			data.my_guid = self:GetGuid()
			function data.fun (data, objs)
				outFmtDebug("PlunderFinish callbacked ===================")
				local targetPlayer = objs[data.callback_guid]
				if not targetPlayer then return end
				outFmtDebug("PlunderFinish target player = %s", targetPlayer:GetGuid())
				
				targetPlayer:AddCultivationPlunderRecord(self:GetGuid(),0, self:GetName(), self:GetLevel(), result, 0, os.time(), 0)
			end
			GetObjects(data)
		end
		
	end
end

