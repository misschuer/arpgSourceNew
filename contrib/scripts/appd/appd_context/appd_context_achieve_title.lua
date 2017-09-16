-- ����ĳ�����͵ĳɾ�
function PlayerInfo:SetAchieve(type,num)
	local list = tb_achieve_type_list[type]
	
	if not list then
		return
	end
	
	for _,v in ipairs(list) do
		self:SetAchieveID(v,num)
	end
	
end
-- ����ĳ�����͵ĳɾ�
function PlayerInfo:AddAchieve(type,num)
	local list = tb_achieve_type_list[type]
	if not list then return end
	for _,v in ipairs(list) do
		self:AddAchieveID(v,num)
	end
end
-- ����ĳ���ɾ�
function PlayerInfo:SetAchieveID(id,num)
	local questMgr = self:getQuestMgr()
	
	local config = tb_achieve_base[id]
	if config == nil then
		return
	end
	
	--�ж��Ƿ������
	if questMgr:getHasAchieve(id) == 1 then
		return
	end
	
	if num >= config.maxnum then
		questMgr:setAchieve(id,config.maxnum)
		questMgr:setHasAchieve(id)
		questMgr:addAchieveAll(config.achval)
		
		-- ����
		local questMgr = self:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_ACHIEVE, {questMgr:getAchieveAll()})
		return
	end
	
	questMgr:setAchieve(id,num)
	
end

-- ���ĳ���ɾ�
function PlayerInfo:AddAchieveID(id,num)
	local questMgr = self:getQuestMgr()
	local cur = questMgr:getAchieve(id)
	cur = cur + num
	self:SetAchieveID(id,cur)
end

--��ȡ�ɾ�ֵ
function PlayerInfo:GetAchieve(id)
	local questMgr = self:getQuestMgr()
	return questMgr:getAchieve(id)
end

--��ȡ�ɾͽ���
function PlayerInfo:AchieveReward(id)
	local questMgr = self:getQuestMgr()
	
	if questMgr:getHasAchieve(id) == 0 then
		self:CallOptResult(OPRATE_TYPE_ACHIEVE, ACHIEVE_OPERATE_NO_GET)
		return
	end
	
	if questMgr:getAchieveReward(id) == 1 then
		self:CallOptResult(OPRATE_TYPE_ACHIEVE, ACHIEVE_OPERATE_HASGET)
		return
	end
	
	local config = tb_achieve_base[id]
	if config == nil then
		return
	end
	
	self:AppdAddItems(config.reward,MONEY_CHANGE_ACHIEVE,LOG_ITEM_OPER_TYPE_ACHIEVE)
	
	questMgr:setAchieveReward(id)
	
	--��ӳƺ�
	if config.title > 0 then
		self:AddTitle(config.title)
	end
	
end

--�ܳɾͽ���
function PlayerInfo:GetAchieveAll()
	local questMgr = self:getQuestMgr()
	return questMgr:getAchieveAll()
end

--��ȡ�ܳɾͽ���
function PlayerInfo:AchieveAllReward()
	local questMgr = self:getQuestMgr()
	local allnum = questMgr:getAchieveAll()
	
	local rewardID = questMgr:getAchieveAllReward()
	
	local targetReward = rewardID + 1
	
	local config = tb_achieve_progress[targetReward]
	if config == nil then
		return
	end
	
	outFmtDebug("rewardID %d %d %d",targetReward,allnum,config.achval)
	
	if allnum >= config.achval then
		self:AppdAddItems(config.reward,MONEY_CHANGE_ACHIEVE,LOG_ITEM_OPER_TYPE_ACHIEVE)
		questMgr:addAchieveAllReward()
	else 
		self:CallOptResult(OPRATE_TYPE_ACHIEVE, ACHIEVE_OPERATE_NO_ALL)
	end
	
end

--�Ƿ�ӵ�гƺ�
function PlayerInfo:HasTitle(id)
	local questMgr = self:getQuestMgr()
	local tf,idx = questMgr:hasTitle(id)
	return tf
end
--�Ƿ�װ��ƺ�
function PlayerInfo:HasEquTitle(id)
	local cur = self:GetByte(PLAYER_FIELD_BYTES_2,3)
	if id == 0 then
		if cur > 0 then
			return true
		end
	else 
		if cur == id then
			return true
		end
	end
	return false
end
--��ӳƺ�
function PlayerInfo:AddTitle(id)
	local questMgr = self:getQuestMgr()
	questMgr:addTitle(id)
	
	self:CallOptResult(OPRATE_TYPE_UPGRADE, UPGRADE_OPRATE_TITLE_ACTIVE)
end
--���óƺ�
function PlayerInfo:SetTitle(id)
	local questMgr = self:getQuestMgr()
	local has,idx = questMgr:hasTitle(id)
	
	if has and id ~=0 then
		questMgr:initTitle(idx)
	end
	
	if id == 0 then
		has = true
	end

	if has then
		self:SetByte(PLAYER_FIELD_BYTES_2,3,id)
		self:CallOptResult(OPRATE_TYPE_ACHIEVE, ACHIEVE_OPERATE_TITLE_SUC)
		
		self:UpdateFactionBangZhuInfo()
		-- ����
		local questMgr = self:getQuestMgr()
		questMgr:OnUpdate(QUEST_TARGET_TYPE_SUIT_TITLE, {id})
	else
		self:CallOptResult(OPRATE_TYPE_ACHIEVE, ACHIEVE_OPERATE_TITLE_FAL)
	end
	self:RecalcAttrAndBattlePoint()
end
--��ʼ���ƺ�
function PlayerInfo:InitTitle(id)
	local questMgr = self:getQuestMgr()
	local has,idx = questMgr:hasTitle(id)
	
	if has and id ~=0 then
		questMgr:initTitle(idx)
	end
end
--�ƺ�װ������
function PlayerInfo:calculTitleAttr(attrs)
	local questMgr = self:getQuestMgr()
	questMgr:calculTitleAttr(attrs)
end
--�Ƴ�ʧЧ�ƺ�
function PlayerInfo:removeExpireTitle()
	local questMgr = self:getQuestMgr()
	questMgr:removeExpireTitle()
end


function PlayerInfo:pickQuest(indx)
	local questMgr = self:getQuestMgr()
	questMgr:OnPickQuest(indx)
end

function PlayerInfo:executeQuestCmdAfterAccepted(indx)
	local questMgr = self:getQuestMgr()
	questMgr:OnExecuteQuestCmdAfterAccepted(indx)
end

function PlayerInfo:OnPickDaily2Quest(indx)
	local questMgr = self:getQuestMgr()
	questMgr:OnPickDailyQuest(indx)
end

function PlayerInfo:SubmitQuestDaily2()
	local questMgr = self:getQuestMgr()
	questMgr:OnSubmitQuestDaily2()
end


--- ÿ����������
function PlayerInfo:DailyQuestReset()
	local questMgr = self:getQuestMgr()
	questMgr:OnDailyQuestReset()
end

--ʹ�õ��߽����ƺ�
function PlayerInfo:ItemUnlockTitle(id)
	if self:HasTitle(id) then
		outFmtDebug("ItemUnlockTitle title unlocked, can not unlock twice")
		return
	end
	
	local config = tb_title_base[id]
	if not config then
		outFmtDebug("ItemUnlockTitle title config error")
		return
	end
	
	if config.unlock_type ~= 2 then
		outFmtDebug("ItemUnlockTitle title unlock type not itemunlock")
		return
	end
	
	if not self:hasAllItems(config.unlock_cost) then
		outFmtDebug("ItemUnlockTitle resouse not enough")
		return
	end
	
	if self:useAllItems(MONEY_CHANGE_UNLOCKTITLE,config.unlock_cost) then
		self:AddTitle(id)
		
		outFmtInfo("ItemUnlockTitle title unlock success")
	end
end