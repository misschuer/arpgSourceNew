local Packet = require 'util.packet'
--������Ʒ���
--[[
@player:��Ҷ���
@item_id:��Ʒid
@count:ʹ����Ʒ����
]]
function SellItem(player, item_guid, count)
	if count <= 0 then return end		--��������С�ڵ���0
	local itemMgr = player:getItemMgr()	
	local item = itemMgr:getItemByGuid(item_guid)		--ֻ������������Ʒ���ܳ���
	--outFmtError("SellItem:  item_guid %s ,count %d", item_guid,count)
	if not item then
		outFmtError("SellItem: not find item_id %s ", item_guid)
		--û�ҵ������Ʒ
		player:CallOptResult(OPRATE_TYPE_BAG,BAG_RESULT_ITEM_NOT_EXIST)
		return
	end
	--������Ʒ����������
	if count > item:getCount() then
		outFmtError("SellItem: item entry %d use count %d > has count %d", item:getEntry(), count, item:getCount())
		player:CallOptResult(OPRATE_TYPE_BAG,BAG_RESULT_LACK_USER)
		return
	end
	
	local item_entry = item:getEntry()
	local item_template = tb_item_template[item_entry]
	if not item_template then
		--ģ������û��
		outFmtError("SellItem: tb_item_template not find %d ! ",item_entry)
		return
	end
	if item_template.price == 0 then
		--��Ʒ���ɳ���
		outFmtError("SellItem: item price = 0 can not sell! ")
		return
	end
	
	local sell_reward = tb_item_template[item:getEntry()].sell_reward
	local all_rewards = {}
	for _,reward in pairs(sell_reward) do
		table.insert(all_rewards,{reward[1],reward[2]*count})
	end
	
	if itemMgr:delItemObj(item,count) then
		player:AppdAddItems(all_rewards,MONEY_CHANGE_NPC_SELL,nil)
--		player:AddMoney(MONEY_TYPE_SILVER, MONEY_CHANGE_NPC_SELL, price*count)
		--print("")
	end
	
end

--������������Ʒ���
--[[
@player:��Ҷ���
@flag:ǿ������
]]
function SortItem(player,flag,bagType)
	local nowtime = os.time()
	local lasttime = player:GetBagSortTime()
	
	if not flag and nowtime - lasttime < tb_item_sort_cd[1].cd then
		--outFmtError("SortItem: less than 10s from last sort!")
		player:CallOptResult(OPRATE_TYPE_BAG,BAG_RESULT_BAG_SORT_CD)
		return
	end
	if not flag then
		player:SetBagSortTime(nowtime)
	end
	bagType = bagType or -1 
	local bags = {}
	if bagType == -1 then
		bags = {BAG_TYPE_MAIN_BAG,BAG_TYPE_EQUIP_BAG}
	else
		bags = {bagType}
	end
	
	
	for _,bag_type in pairs(bags) do
		
		local itemMgr = player:getItemMgr()
		local items = itemMgr:getBagAllItem(bag_type)
		local index = 0
		for pos, item in pairsByKeys(items) do      
			--outFmtInfo("pos:%d item:%s",pos,item) 
			if pos == index then
				index = index + 1
			else
				itemMgr:exchangePos(bag_type,pos,bag_type,index)
				index = index + 1
			end
		end
		local items = itemMgr:getBagAllItem(bag_type)
		local tempTable = {}
		for pos, item in pairsByKeys(items) do
			
			local value1 = tb_item_template[item:getEntry()].rank --�ȼ�(����) Ʒ��(����)  ����(����) λ��(����) ս��(����)  ��ȡʱ��(����)  entry(����) ����(����)
			local value2 = tb_item_template[item:getEntry()].quality
			local value3 = tb_item_template[item:getEntry()].type_c
			local value3_1 = tb_item_template[item:getEntry()].pos
			local value4 = item:getForce()
			local value5 = 0
			local value6 = item:getEntry()
			local value7 = item:getCount()
			local value99 = pos
			-- 
			local value = value4 + (99 - value3_1) * 100000+ (99-value3) * 10000000 + value2 * 1000000000+ value1 * 10000000000
			--outFmtDebug("======= value4 = %d", value4)
			table.insert(tempTable,{pos=pos,value = value,value1=value1,value2=value2,value3=value3,value3_1=value3_1,value4=value4,value5=value5,value6=value6,value7=value7,value99=value99})
		end

		--print("------------------------------")	
		--printTable(tempTable)
		
		--quickSort(itemMgr,tempTable,function(a,b)
		mi_sort(tempTable, function(a,b)
			
						
			if a.value1 ~= b.value1 then
				return a.value1 > b.value1
			end
			
			if a.value2 ~= b.value2 then
				return a.value2 > b.value2
			end
			
			if a.value3 ~= b.value3 then
				return a.value3 < b.value3
			end
			
			if a.value3_1 ~= b.value3_1 then
				return a.value3_1 < b.value3_1
			end
			
			if a.value4 ~= b.value4 then
				return a.value4 > b.value4
			end
			
			if a.value5 ~= b.value5 then
				return a.value5 > b.value5
			end
			
			if a.value6 ~= b.value6 then
				return a.value6 < b.value6
			end
			
			if a.value7 ~= b.value7 then
				return a.value7 > b.value7
			end
			
			return a.value99 < b.value99
		end
		,function(a,b)
			itemMgr:exchangePos(bag_type,a.pos,bag_type,b.pos)
			local temp = a.pos
			a.pos = b.pos
			b.pos = temp
		end)
		
		--�ϲ���ͬ����
		local items = itemMgr:getBagAllItem(bag_type)
		for pos,_ in pairsByKeys(items) do
			local src_item = itemMgr:getBagItemByPos(bag_type,pos)
			if src_item then
				local src_temp = tb_item_template[src_item:getEntry()]	
				if src_item:getCount() < src_temp.max_overlap then
					for dst_pos = pos + 1,#items + 1 do
						local dst_item = itemMgr:getBagItemByPos(bag_type,dst_pos)
						if dst_item then
							if src_item:canOverlay(dst_item) then
								local can_over_lay = src_temp.max_overlap - src_item:getCount()
								if can_over_lay < dst_item:getCount() then
									src_item:setCount(src_item:getCount() + can_over_lay)
									dst_item:setCount(dst_item:getCount() - can_over_lay)
									itemMgr.itemMgr:SavePtr(dst_item.item)
									itemMgr.itemMgr:SavePtr(src_item.item)
								else
									src_item:setCount(src_item:getCount() + dst_item:getCount())
									itemMgr.itemMgr:SavePtr(src_item.item)
									--ɾ��Դ��Ʒ
									itemMgr:delItemObj(dst_item)
								end
							end
						end
					end
				end
				
			end
		end
		
		--outFmtDebug("**************************")
		local items = itemMgr:getBagAllItem(bag_type)
		local index = 0
		for pos, item in pairsByKeys(items) do      
			--outFmtInfo("pos:%d item:%s",pos,item) 
			if pos == index then
				index = index + 1
			else
				itemMgr:exchangePos(bag_type,pos,bag_type,index)
				index = index + 1
			end
		end
	end

	
end

function printTable(obj)
	local value = dfs(obj)
	print(value)
end

function dfs(obj)
	local list = {}
	for key, val in pairs(obj) do
		local show = val
		if type(show) == 'table' then
			show = printTable(show)
		end
		
		table.insert(list, string.format("'%s' = %s", key, tostring(show)))
	end
	
	return string.join(",", list)
end




