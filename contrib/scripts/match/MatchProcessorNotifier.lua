MatchProcessorNotifier = class('MatchProcessorNotifier')

--���캯��
function MatchProcessorNotifier:ctor()
end

function MatchProcessorNotifier:completed(task, position)
	self:notice(task)
	self:notice(position)
end

function MatchProcessorNotifier:notice(task)
	-- ֪ͨƥ�����
	task:Unmark()
end

function MatchProcessorNotifier:cancel(task)
	local  partList = task:getPartList()
	for _, teamPart in pairs(partList) do
		local userIdList = teamPart:getUserIdList()
		for _, id in pairs(userIdList) do
			-- ֪ͨȡ��ƥ��
		end
	end
	
	task:Unmark();
end