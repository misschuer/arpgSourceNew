CombineExpandConfig = class('CombineExpandConfig')

-- ICombineExpandConfig instance = CombineExpandConfig:new {config = config}
--���캯��
function CombineExpandConfig:ctor()
	
end

-- ��ó���
function CombineExpandConfig:size()
	return #self.config
end

-- ���Ԫ��
function CombineExpandConfig:get(index)
	if index < 0 or index >= self:size() then
		return 0
	end
	return self.config[index+1]
end