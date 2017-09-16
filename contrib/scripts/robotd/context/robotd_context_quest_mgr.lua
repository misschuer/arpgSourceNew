
-- ������һ������
function PlayerInfo:DoNextQuest()
	
	if not self.quest then
		outFmtDebug("		quest binlogObject not init")
		return
	end
	
	-- ���ճ�����
	local questInfo = self.quest:GetQuestInfo()
	if not questInfo then
		outFmtDebug("		no available quest")
		return
	end
	
	if self.questStart then
		outFmtDebug("		self.questStart true")
		return
	end
	
	local config = tb_quest[questInfo.questId]
	local targets = config.targets
	-- ������Ŀ��
	for indx, target in ipairs(targets) do
		local targetType = target[ 1 ]
		local stepInfo	 = questInfo.steps[indx]
		if stepInfo.stepState == 0 and Quest_Function[targetType] then
			return Quest_Function[targetType](self, questInfo.questId, indx)
		end
	end
	
	if questInfo.state == QUEST_STATUS_COMPLETE then
		outFmtDebug("		send for finish questId = %d", questInfo.questId)
		self:AutoSendFinishQuest(questInfo.questId)
		return
	end
	
	outFmtDebug("		no deal target for questId = %d", questInfo.questId)

	return 
end

-- װ�����
function PlayerInfo:RobotEquipDivine(questId, indx)
	if not self.spellMgr then
		outFmtDebug("spellMgr not attach")
		return
	end
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type = config.targets[indx][ 1 ]
	questOperate.questId = questId
	
	local divineId = config.targets[indx][ 2 ]
	local divineDict = self.spellMgr:getDivineIdList()
	
	local need = 0
	
	for _, divId in ipairs(divineDict) do
		if divineId == 0 or divId == divineId then
			need = divId
			break
		end
	end
	
	-- ������� װ��
	if need > 0 then
		--divine_active ( id :number )
		questOperate.callback = function()
			outFmtDebug("call_divine_switch divineId = %d", need)
			self:call_divine_switch(divineId)
			-- ���������������
			self:AutoSendFinishQuest(questId)
		end
	else
		-- �ж��Ƿ�Ҫ����
		if divineId == 0 then
			-- û������
			outFmtDebug("not divineId to buy for questId = %d", questId)
			return
		else
			-- �������
			outFmtDebug("call_divine_active divineId = %d", need)
			self:call_divine_active (divineId)
			return
		end
	end
	
	return questOperate
end

-- ��NPC����
function PlayerInfo:TalkWithNPC(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type 		= config.targets[indx][ 1 ]
	questOperate.mapid		= stepParams[ 2 ]
	questOperate.x			= stepParams[ 3 ]
	questOperate.y			= stepParams[ 4 ]
	questOperate.objcet_id	= stepParams[ 5 ]
	questOperate.questId = questId

	local entry = questOperate.objcet_id
	questOperate.callback 	= function()
		outFmtDebug("call_talk_with_npc entry = %d, questId = %d", entry, questId)
		self:call_talk_with_npc (questOperate.objcet_id ,questId)
	end

	-- Ѱ·
	self.questStart = true

	return questOperate
end

-- ʹ�òɼ���
function PlayerInfo:RobotUseGameObject(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type 		= config.targets[indx][ 1 ]
	questOperate.mapid		= stepParams[ 2 ]
	questOperate.x			= stepParams[ 3 ]
	questOperate.y			= stepParams[ 4 ]
	questOperate.objcet_id	= stepParams[ 5 ]
	questOperate.questId = questId
	
	-- Ѱ·
	self.questStart = true
	
	return questOperate
end

-- ɱ��
function PlayerInfo:RobotKillMonster(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local targetPosType = stepParams[ 1 ]
	local questOperate = nil
	
	if targetPosType == 1 or targetPosType == 7 then
		questOperate = {}
		questOperate.type 		= config.targets[indx][ 1 ]
		questOperate.objcet_id	= config.targets[indx][ 2 ]
		questOperate.mapid		= stepParams[ 2 ]
		questOperate.x			= stepParams[ 3 ]
		questOperate.y			= stepParams[ 4 ]
		questOperate.questId = questId
		
		-- �ж������Ƿ����
		questOperate.IsFinishMethod = function()
			local questIndx = self.quest:GetQuestIndxById(questId)
			local vist = not questIndx
			if not vist then
				local intstart = QUEST_FIELD_QUEST_START + questIndx * MAX_QUEST_INFO_COUNT
				local stepstart = intstart + QUEST_INFO_STEP_START + (indx-1) * MAX_QUEST_TARGET_INFO_COUNT
				vist =  self.quest:GetUInt16(stepstart + QUEST_TARGET_INFO_SHORT0, 0) == 1
			end
			return vist
		end
		
		-- Ѱ·
		self.questStart = true
	elseif targetPosType == 8 then
		local afterInfo = config.afterAccept
		if self:GetMapID() == afterInfo[ 2 ] then
		--	2,4002,126,30,7404,129,36,1002
			questOperate = {}
			questOperate.type 		= config.targets[indx][ 1 ]
			questOperate.objcet_id	= config.targets[indx][ 2 ]
			questOperate.mapid		= afterInfo[ 2 ]
			questOperate.x			= afterInfo[ 6 ]
			questOperate.y			= afterInfo[ 7 ]
			questOperate.questId = questId
			
			-- �ж������Ƿ����
			questOperate.IsFinishMethod = function()
				local questIndx = self.quest:GetQuestIndxById(questId)
				local vist = not questIndx
				if not vist then
					local intstart = QUEST_FIELD_QUEST_START + questIndx * MAX_QUEST_INFO_COUNT
					local stepstart = intstart + QUEST_INFO_STEP_START + (indx-1) * MAX_QUEST_TARGET_INFO_COUNT
					vist =  self.quest:GetUInt16(stepstart + QUEST_TARGET_INFO_SHORT0, 0) == 1
				end
				return vist
			end
		else
			local questIndx = self.quest:GetQuestIndxById(questId)
			self:call_execute_quest_cmd_after_accepted(questIndx)
		end
	end
	
	return questOperate
end

-- ʹ����Ʒ
function PlayerInfo:RobotUseItem(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
		
	local questOperate = {}
	questOperate.type = config.targets[indx][ 1 ]
	questOperate.questId = questId
	
	local entry = config.targets[indx][ 2 ]
	local item_guid = self.itemMgr:GetItemGuidByEntry(entry)

	questOperate.callback 	= function()
		if item_guid then
			outFmtDebug("call_bag_item_user entry = %d, item_guid = %s, questId = %d", entry, item_guid, questId)
			self:call_bag_item_user (item_guid, 1)
			-- ���������������
			self:AutoSendFinishQuest(questId)
		else
			outFmtDebug("not find entry %d in bag", entry)
		end
	end
	
	return questOperate
end

-- ����װ��
function PlayerInfo:RobotSuit(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type = config.targets[indx][ 1 ]
	questOperate.questId = questId
	
	local suitPos = config.targets[indx][ 2 ]
	local suitEntry = config.targets[indx][ 3 ]
	local entry, src_pos = self.itemMgr:GetSuitEntryAndBagPosBySuitPos(suitPos, suitEntry)
	questOperate.callback = function()
		if src_pos then
			local dst_pos = tb_item_template[entry].pos
			outFmtDebug("call_bag_exchange_pos entry = %d, %d, %d, %d", BAG_TYPE_MAIN_BAG, src_pos, BAG_TYPE_EQUIP, dst_pos)
			self:call_bag_exchange_pos (BAG_TYPE_MAIN_BAG, src_pos, BAG_TYPE_EQUIP, dst_pos)
			-- ���������������
			self:AutoSendFinishQuest(questId)
		else
			outFmtDebug("not find suitPos %d, suitEntry %d in bag", suitPos, suitEntry)
		end
	end
	
	return questOperate
end

--��ս��Դ����
function PlayerInfo:RobotJoinResourceInstance(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type = config.targets[indx][ 1 ]
	questOperate.questId = questId
	
	local instanceId = config.targets[indx][ 2 ]
	local instanceCount = config.targets[indx][ 3 ]
	
	questOperate.callback = function()
		outFmtDebug("RobotJoinResourceInstance callback")

		self:call_res_instance_enter(4) -- ���Ҹ���
		--self:call_instance_exit(0)
		self:AutoSendFinishQuest(questId)
	end
	
	return questOperate
end


--��ս����̨����
function PlayerInfo:RobotJoinDoujiantai(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type = config.targets[indx][ 1 ]
	questOperate.questId = questId
	
	local count = config.targets[indx][ 2 ]
	
	questOperate.callback = function()
		outFmtDebug("RobotJoinDoujiantai callback")

		self:call_doujiantai_fight(0) -- ����̨
		--self:call_instance_exit(0)
		self:AutoSendFinishQuest(questId)
	end
	
	return questOperate
end

--����װ����λ
function PlayerInfo:RobotStrengthSuit(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type = config.targets[indx][ 1 ]
	questOperate.questId = questId
	
	local part = config.targets[indx][ 2 ]
	local count = config.targets[indx][ 3 ]

	
	questOperate.callback = function()
		outFmtDebug("RobotStrengthSuit callback")

		self:call_strength(1) -- ��λ
		self:AutoSendFinishQuest(questId)
	end
	
	return questOperate
end


--��������
function PlayerInfo:RobotRaiseSkill(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type = config.targets[indx][ 1 ]
	questOperate.questId = questId
	
	local part = config.targets[indx][ 2 ]
	local count = config.targets[indx][ 3 ]

	
	questOperate.callback = function()
		outFmtDebug("RobotRaiseSkill callback")
		self:call_raise_base_spell(RAISE_BASE_SKILL,10005)
		self:call_raise_base_spell(RAISE_BASE_SKILL,10008)
		
		self:AutoSendFinishQuest(questId)
	end
	
	return questOperate
end

--��������
function PlayerInfo:RobotTrainMount(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local questOperate = {}
	questOperate.type = config.targets[indx][ 1 ]
	questOperate.questId = questId
	
	local count = config.targets[indx][ 2 ]

	
	questOperate.callback = function()
		outFmtDebug("RobotRaiseSkill callback")
		self:call_raise_mount()
		
		self:AutoSendFinishQuest(questId)
	end
	
	return questOperate
end


--��lv
function PlayerInfo:RobotLvUp(questId, indx)
	local config = tb_quest[questId]
	local stepParams = config.targetsPosition[indx]
	
	local lv = config.targets[indx][ 2 ]
	
	local cmd = "@Rank "..lv
	self:call_chat_by_channel(CHAT_TYPE_WORLD, cmd)
	
	return
end

function PlayerInfo:AutoSendFinishQuest(questId)
	local config = tb_quest[questId]
	-- ���������������
	if config.popup ~= 0 then
		local questIndx = self.quest:GetQuestIndxById(questId)
		if questIndx then
			outFmtDebug("	call_pick_quest_reward questIndx = %d", questIndx)
			self:call_pick_quest_reward(questIndx)
		end
	end
end

Quest_Function = {
	[QUEST_TARGET_TYPE_PLAYER_LEVEL] 		= PlayerInfo.RobotLvUp,
--	[QUEST_TARGET_TYPE_PLAYER_FORCE] 		= IQuestPlayerForce,
--	[QUEST_TARGET_TYPE_FACTION] 			= IQuestJoinFaction,
--	[QUEST_TARGET_TYPE_FACTION_DONATION] 	= IQuestFactionDonate,
--	[QUEST_TARGET_TYPE_FACTION_ACTIVITY] 	= IQuestJoinFactionActivity,
--	[QUEST_TARGET_TYPE_FIELD_BOSS] 			= IQuestJoinFieldBoss,
--	[QUEST_TARGET_TYPE_WORLD_BOSS] 			= IQuestJoinWorldBoss,
	[QUEST_TARGET_TYPE_RESOURCE_INSTANCE] 	= PlayerInfo.RobotJoinResourceInstance,
--	[QUEST_TARGET_TYPE_TRIAL_INSTANCE] 		= IQuestJoinTrialInstance,
--	[QUEST_TARGET_TYPE_OWN_DIVINE] 			= IQuestOwnDivine,
	[QUEST_TARGET_TYPE_EQUIP_DIVINE] 		= PlayerInfo.RobotEquipDivine,
--	[QUEST_TARGET_TYPE_STRENGTH_DIVINE] 	= IQuestStrengthDivine,
	[QUEST_TARGET_TYPE_RAISE_SKILL] 		= PlayerInfo.RobotRaiseSkill,
	[QUEST_TARGET_TYPE_TRAIN_MOUNT] 		= PlayerInfo.RobotTrainMount,
--	[QUEST_TARGET_TYPE_RAISE_MOUNT_SKILL] 	= IQuestRaiseMountSkill,
--	[QUEST_TARGET_TYPE_FRIEND_DONATION] 	= IQuestFriendDonate,
	[QUEST_TARGET_TYPE_STRENGTH_SUIT]		= PlayerInfo.RobotStrengthSuit,
--	[QUEST_TARGET_TYPE_STRENGTH_GEM] 		= IQuestStrengthGem,
	[QUEST_TARGET_TYPE_TALK] 				= PlayerInfo.TalkWithNPC,
	[QUEST_TARGET_TYPE_PICK_GAME_OBJECT] 	= PlayerInfo.RobotUseGameObject,
--	[QUEST_TARGET_TYPE_CHECK_GAME_OBJECT] 	= IQuestInspect,
	[QUEST_TARGET_TYPE_KILL_MONSTER] 		= PlayerInfo.RobotKillMonster,
	[QUEST_TARGET_TYPE_USE_ITEM] 			= PlayerInfo.RobotUseItem,
	[QUEST_TARGET_TYPE_SUIT]				= PlayerInfo.RobotSuit,
--	QUEST_TARGET_TYPE_MOUNT_LEVEL = 25	-- ����ﵽx
--	QUEST_TARGET_TYPE_FRIEND_NUM = 26	-- ӵ�к���x
--	QUEST_TARGET_TYPE_KILL_MONSTER_NUM = 27	-- ��ɱ����x
--	QUEST_TARGET_TYPE_DIVINE_NUM = 28	-- ӵ�����x
--	QUEST_TARGET_TYPE_DIVINE_LEV = 29	-- ����ȼ�x
--	QUEST_TARGET_TYPE_DOUJIANTAI = 30	-- ����̨ʤ��x
--	QUEST_TARGET_TYPE_TITLE_NUMBER = 31	-- �ƺ������ﵽx��
--	QUEST_TARGET_TYPE_FASHION_NUMBER = 32	-- ʱװ�����ﵽx��
--	QUEST_TARGET_TYPE_ACHIEVE = 40	-- �ɾ͵����ﵽX��
--	QUEST_TARGET_TYPE_SUIT_TITLE = 41	-- ���X�ƺ�
--	QUEST_TARGET_TYPE_SUIT_FASHION = 42	-- ����ʱװX
	[QUEST_TARGET_TYPE_JOIN_DOUJIANTAI]		= PlayerInfo.RobotJoinDoujiantai,
--	QUEST_TARGET_TYPE_JOIN_KUAFU_3V3 = 44	-- ����X��3V3
--	QUEST_TARGET_TYPE_WIN_KUAFU_3V3 = 45	-- 3v3��ʤx��
--	QUEST_TARGET_TYPE_JOIN_XIANFU = 46	-- ����X���ɸ��ᱦ
--	QUEST_TARGET_TYPE_WIN_XIANFU = 47	-- �ɸ��ᱦ��ʤX��
--	QUEST_TARGET_TYPE_KILL_MONSTER_COLLECT = 48	-- ɱ���ռ���Ʒ
--	QUEST_TARGET_TYPE_TURN_ITEM_IN = 49	-- �Ͻ���Ʒ
}