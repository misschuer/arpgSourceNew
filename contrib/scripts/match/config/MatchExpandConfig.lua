MatchExpandConfig = class('MatchExpandConfig')

-- IMatchExpandConfig instance = MatchExpandConfig:new {config = config}
--���캯��
function MatchExpandConfig:ctor()
	
end

-- ��ó���
function MatchExpandConfig:size()
	return #self.config
end

-- ���Ԫ��
function MatchExpandConfig:get(index)
	if index < 0 or index >= self:size() then
		return 0
	end
	return self.config[index+1]
end