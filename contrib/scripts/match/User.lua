User = class('User')

-- IUser instance = User:new {id = id, score = score}
--���캯��
function User:ctor()
	
end

function User:getScore()
	return self.score
end

function User:getId()
	return self.id
end