function PlayerInfo:AfterQuestDoing(doing)
	-- ����Ҫ��
	if #doing == 0 then
		return
	end
	local type = doing[ 1 ]
	
	-- �����ɸ����鸱��
	if type == 1 then
		self:EnterXianfuTest()
	-- �������߾��鸱��
	elseif type == 2 then
		self:EnterRemindInstance(doing[ 2 ], doing[ 3 ], doing[ 4 ], doing[ 5 ], doing[ 6 ], doing[ 7 ], doing[ 8 ])
	end
end