MatchProcessor = class('MatchProcessor')

--[[IMatchProcessor instance = MatchProcessor:new {
	config = config,
}
--]]
--���캯��
function MatchProcessor:ctor()
	if self.config:getMatchExpandConfig() then
		self.matchRangeExpander = MatchTRExpander:new {
			matchExpandConfig = config:getMatchExpandConfig()
		}
	end
	
	if self.config:getCombineExpandConfig() then
		self.combineRangeExpander = CombineTRExpander:new {
			combineExpandConfig = config:getCombineExpandConfig()
		}
	end
	
	self.totalMatched = 0
	
	self.waitAddTaskQueue = {}
	self.taskQueue = {}
end

function MatchProcessor:submitMatch(task)
	task:setMaxUser(self.config:getUserMax())
	task:setStartTime(os.time())
	table.insert(waitAddTaskQueue, task)
end

function MatchProcessor:cancelMatch(task)
	table.removeItem(self.waitAddTaskQueue, task)
	table.removeItem(self.taskQueue		  , task)
	
	--�Ѻ���ƥ���������´�ɢ�ŵ���β
	local externalPlayerTasks = task:separate()
	for _, externalTask in pairs(externalPlayerTasks) do
		table.insert(taskQueue, externalTask)
	end
	notifier:cancel(task)
end

function MatchProcessor:fillTaskQueue()
	if (#self.waitAddTaskQueue > 0) then
		for i = #self.waitAddTaskQueue, 1, -1 do
			local task = self.waitAddTaskQueue[ i ]
			table.insert(self.taskQueue, task)
			table.remove(self.waitAddTaskQueue, i)
		end
	end
end

--[[
     * �Ƶ�ĩβλ��
     */
--]]
function MatchProcessor:headToTail()
	local t = self.taskQueue[ 1 ];
	table.remove(self.taskQueue, 1)
	table.insert(self.taskQueue, t)
end

function MatchProcessor:expandMatchRange(task)
	if self.matchRangeExpander then
		if self.matchRangeExpander:isDifficutMatch(task) then
            self.matchRangeExpander:expandMatchRange(task)
		end
	end
end

function MatchProcessor:expandCombineRange(task)
	if self.combineRangeExpander then
		if self.combineRangeExpander:isDifficutMatch(task) then
            self.combineRangeExpander:expandMatchRange(task)
		end
	end
end

function MatchProcessor:matchTask(task)
	task:incrementMatchCount()
    self:expandMatchRange(task)
    
	local matchRangeRecords = task:getMatchRangeRecords()
	-- �Ƿ���������Ӫ
	local campActive = config:isCampActive()
	
	for _, record in pairs(matchRangeRecords) do
		local i = 1
		while (i <= #self.taskQueue) do
			local position = self.taskQueue[ i ]
			if not position:isActive() then
				self:timeout(position)
				table.remove(self.taskQueue, i)
			else
				local baseCondition = (position ~= task and task:playersSizeEquals(position))
				if campActive then --��������Ƕ�����Ӫ���ܳ�Ϊ���֣����ж�
                    baseCondition = baseCondition and not task:isSameCamp(position)
                end
				
				if (baseCondition) then
                    local cpr = position:compareTo(task)
                    if (math.abs(cpr) <= record) then --�ҵ����ʵĶ���
                        task:completed()
                        notifier:completed(task, position);
                        totalMatched = totalMatched + task:size() + position:size()
						table.remove(self.taskQueue, i) -- ��ɾ�����
						table.remove(self.taskQueue, 1) -- ƥ��ɹ����Ƴ�ͷ�����Ƴ�position
                        return position
                    end
				end
				i = i + 1
			end
		end
	end
	
	return nil
end

--[[
	���
--]]
function MatchProcessor:organizeTeam()
    self:fillTaskQueue()
    local task = self.taskQueue[ 1 ]
            
    if (not task) then
		return
	end
            
    if (not task:isActive()) then -- �ж�task�Ƿ�ʧЧ
		table.remove(self.taskQueue, 1)
		self:timeout(task);
		return
	end

	if (not task:isFull()) then -- ���δ���ˣ���Ѱ��ƽ��ֵ��Χ�ڵ������������
		self:expandCombineRange(task)
        self:combineTeam(task)
	end

    -- �������������δ������������飬��ƥ���������β��
	if (not task:isFull()) then --// �ڴ�ʱ�����̰߳�ȫ���⣬�����ȡ��ƥ��
        -- // һ��ȫ�ֱ����޷�����������飬��������
		local externalPlayerTasks = task:separate()
		
		for _, externalTask in pairs(externalPlayerTasks) do
			table.insert(self.taskQueue, externalTask)
		end
		self:headToTail()
		return
    end

	local result = self:matchTask(task)
	if (not result) then
		-- // δƥ��ɹ�����ͷ�Ƶ�β��
		self:headToTail()
	else
		local remain = 0
		for _, t in pairs(self.taskQueue) do
			remain = remain + t:size()
		end
		--print("Complete a team match (remain = %d, totalMatched = %d)\n", remain, totalMatched);
	end
    
end

function MatchProcessor:combineTeam(task)
	-- ѭ�������Ƚ�ƥ�䷶Χ����,��С�ķ�Χ����ķ�Χ��ʼ�Ƚ�
	local combineRangeRecords = task:getCombineRangeRecords()
			
	for _, record in pairs(combineRangeRecords) do --//��Χ���ż�¼��������С����ȡ����
		
		local i = 1
		while (i <= #self.taskQueue) do -- //ʣ������Task���������������������
			local position = self.taskQueue[ i ]
			
			if not position:isActive() then	--//�ж�position�Ƿ�ʧЧ
				self:timeout(position)
				table.remove(self.taskQueue, i)
			else
				local campActive = self.config:isCampActive() --//�Ƿ���Ҫ��Ӫ�ж�
				if (position ~= task and task:canCombine(position, campActive)) then --// �ж��Ƿ��ܹ��ϲ�������
					local cpr = position:compareTo(task)
					--����ƥ��Ҫ��
					if (math.abs(cpr) <= record) then
						task:combine(position, campActive) --// �ϲ�
						table.remove(self.taskQueue, i)
					end
					if (task:isFull()) then
						return
					end
				end
				i = i + 1
			end
		end
	end
end

function MatchProcessor:timeout(task)
	task:Unmark()
end
  
function MatchProcessor:getNotifier()
	return self.notifier
end

function MatchProcessor:setNotifier(notifier)
	self.notifier = notifier
end