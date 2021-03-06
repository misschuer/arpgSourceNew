CombineTRExpander = class('CombineTRExpander')

-- ICombineTRExpander instance = CombineTRExpander:new {combineExpandConfig = combineExpandConfig}
--���캯��
function CombineTRExpander:ctor()
	
end

function CombineTRExpander:isDifficutMatch(task)
	return #(task:getCombineRangeRecords()) <= self.combineExpandConfig:size()
end

function CombineTRExpander:expandMatchRange(task)
	local records = task:getCombineRangeRecords()
	table.insert(records, self.combineExpandConfig:get(#records))
end