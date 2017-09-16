local try		= require("base/try")
local catch		= require("base/catch")
local finally	= require("base/finally")

local security = {}

-- ʹ��try-catch-finally ��ȫ���ú���
-- try_block ������,
-- catch_block Ĭ�ϴ�ӡ����
function security.call(try_block, catch_block, finally_block)
	assert(try_block)
	catch_block = catch_block or function(errors)
		outFmtError(errors)
	end
	
	return try {
		-- try �����
		function ()
			return try_block()
		end,

		-- catch �����
		catch 
		{
			-- �����쳣�󣬱�ִ��
			function (errors)
				if catch_block then
					catch_block(errors)
				end
			end
		},

		-- finally �����
		finally 
		{
			-- ��󶼻�ִ�е�����
			-- ���try{}�д����쳣��okΪtrue��errorsΪ������Ϣ������Ϊfalse��errorsΪtry�еķ���ֵ
			function (ok, errors)
				if finally_block then
					finally_block(ok, errors)
				end
			end
		}
	}
end

return security

