ACT_DAILY_GIFT = 1	-- ÿ�����
ACT_LOTTERY = 2		-- �齱
ACT_RANK	= 3		-- ����
ACT_LIMIT_GIFT = 4	-- �ڼ��޶����

ActivityBase = require("appd.activities.ActivityBase")

require("appd.activities.ActDailyGift")
require("appd.activities.ActLottery")
require("appd.activities.ActRank")
require("appd.activities.ActLimitGift")

-- ���һ��Ҫ�ŵ����
require("appd.activities.ActivityManager")


