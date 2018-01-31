---------------------------------------------------------------------------------
--------------------------以下代码为自动生成，请勿手工改动-----------------------
---------------------------------------------------------------------------------


tb_vip_base = {
	--  id:int VIP等级
	--  massbossExtraTimes:int 全民boss挑战每日增加次数
	--  djtBuyTimes:int 斗剑台额外购买次数
	--  factiondonation:int VIP捐元宝赠次数增加
	--  factionybdonation:int VIP捐银币赠次数增加
	--  treeTimes:int 摇钱树购买次数增加
	--  groupExpBuyTimes:int 经验副本每天可购买次数
	--  groupInstanceBuyTimes:int 组队副本每天可购买次数
	--  expRate:int 打怪经验加成(百分比)
	--  offlineExpRate:int 离线经验加成(百分比)
	--  bag_size:array 背包大小
	--  chongzhi:int 充值
	--  gift:array 礼包
	--  cost:array 价格
	--  massbossBuyTimes:int 全民boss挑战额外购买次数
	--  resReward:int 资源副本结算奖励增加
	--  djtReward:int 斗剑台结算奖励增加
	--  qualifyReward:int 排位赛结算奖励增加
	--  groupReward:int 多人副本结算奖励增加
	--  worldbossReward:int 世界boss结算奖励增加
	--  trialReward:int 试炼塔扫荡奖励增加
	--  riskReward:int 世界冒险收益增加
	[0] = {id = 0, massbossExtraTimes = 0, djtBuyTimes = 0, factiondonation = 0, factionybdonation = 0, treeTimes = 2, groupExpBuyTimes = 0, groupInstanceBuyTimes = 0, expRate = 0, offlineExpRate = 0, bag_size = {{0,100},{2,100},{3,100}}, chongzhi = 0, gift = {{3,100000},{2,50}}, cost = {{1,30}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[1] = {id = 1, massbossExtraTimes = 0, djtBuyTimes = 1, factiondonation = 1, factionybdonation = 1, treeTimes = 3, groupExpBuyTimes = 0, groupInstanceBuyTimes = 0, expRate = 30, offlineExpRate = 0, bag_size = {{0,100},{2,100},{3,100}}, chongzhi = 10, gift = {{224,500},{3,500000},{2,100}}, cost = {{1,50}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[2] = {id = 2, massbossExtraTimes = 0, djtBuyTimes = 2, factiondonation = 2, factionybdonation = 2, treeTimes = 4, groupExpBuyTimes = 0, groupInstanceBuyTimes = 0, expRate = 30, offlineExpRate = 0, bag_size = {{0,100},{2,100},{3,100}}, chongzhi = 30, gift = {{1507,1},{3,1000000},{2,200}}, cost = {{1,100}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[3] = {id = 3, massbossExtraTimes = 0, djtBuyTimes = 3, factiondonation = 3, factionybdonation = 3, treeTimes = 5, groupExpBuyTimes = 0, groupInstanceBuyTimes = 0, expRate = 30, offlineExpRate = 0, bag_size = {{0,100},{2,100},{3,100}}, chongzhi = 60, gift = {{1508,1},{3,1500000},{2,300}}, cost = {{1,150}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[4] = {id = 4, massbossExtraTimes = 1, djtBuyTimes = 4, factiondonation = 4, factionybdonation = 4, treeTimes = 6, groupExpBuyTimes = 0, groupInstanceBuyTimes = 0, expRate = 30, offlineExpRate = 10, bag_size = {{0,130},{2,130},{3,130}}, chongzhi = 100, gift = {{206,10},{3,2000000},{2,400}}, cost = {{1,200}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[5] = {id = 5, massbossExtraTimes = 1, djtBuyTimes = 5, factiondonation = 5, factionybdonation = 5, treeTimes = 7, groupExpBuyTimes = 0, groupInstanceBuyTimes = 1, expRate = 30, offlineExpRate = 10, bag_size = {{0,130},{2,130},{3,130}}, chongzhi = 200, gift = {{1509,1},{3,2500000},{2,500}}, cost = {{1,250}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[6] = {id = 6, massbossExtraTimes = 1, djtBuyTimes = 6, factiondonation = 6, factionybdonation = 6, treeTimes = 8, groupExpBuyTimes = 0, groupInstanceBuyTimes = 1, expRate = 30, offlineExpRate = 10, bag_size = {{0,130},{2,130},{3,130}}, chongzhi = 500, gift = {{1510,1},{3,3000000},{2,600}}, cost = {{1,300}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[7] = {id = 7, massbossExtraTimes = 1, djtBuyTimes = 7, factiondonation = 7, factionybdonation = 7, treeTimes = 9, groupExpBuyTimes = 1, groupInstanceBuyTimes = 1, expRate = 30, offlineExpRate = 10, bag_size = {{0,130},{2,130},{3,130}}, chongzhi = 800, gift = {{1511,1},{3,3500000},{2,700}}, cost = {{1,350}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[8] = {id = 8, massbossExtraTimes = 2, djtBuyTimes = 8, factiondonation = 8, factionybdonation = 8, treeTimes = 10, groupExpBuyTimes = 1, groupInstanceBuyTimes = 1, expRate = 30, offlineExpRate = 10, bag_size = {{0,160},{2,160},{3,160}}, chongzhi = 1000, gift = {{1520,1},{3,4000000},{2,800}}, cost = {{1,400}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[9] = {id = 9, massbossExtraTimes = 2, djtBuyTimes = 9, factiondonation = 9, factionybdonation = 9, treeTimes = 11, groupExpBuyTimes = 1, groupInstanceBuyTimes = 2, expRate = 30, offlineExpRate = 10, bag_size = {{0,160},{2,160},{3,160}}, chongzhi = 2000, gift = {{1521,1},{3,4500000},{2,900}}, cost = {{1,450}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[10] = {id = 10, massbossExtraTimes = 2, djtBuyTimes = 10, factiondonation = 10, factionybdonation = 10, treeTimes = 12, groupExpBuyTimes = 1, groupInstanceBuyTimes = 2, expRate = 30, offlineExpRate = 10, bag_size = {{0,160},{2,160},{3,160}}, chongzhi = 5000, gift = {{204,10},{3,5000000},{2,1000}}, cost = {{1,500}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[11] = {id = 11, massbossExtraTimes = 2, djtBuyTimes = 11, factiondonation = 11, factionybdonation = 11, treeTimes = 13, groupExpBuyTimes = 2, groupInstanceBuyTimes = 2, expRate = 30, offlineExpRate = 10, bag_size = {{0,160},{2,160},{3,160}}, chongzhi = 8000, gift = {{233,1000},{3,5500000},{2,1100}}, cost = {{1,550}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[12] = {id = 12, massbossExtraTimes = 2, djtBuyTimes = 12, factiondonation = 12, factionybdonation = 12, treeTimes = 14, groupExpBuyTimes = 2, groupInstanceBuyTimes = 2, expRate = 30, offlineExpRate = 10, bag_size = {{0,200},{2,200},{3,200}}, chongzhi = 10000, gift = {{227,1000},{3,6000000},{2,1200}}, cost = {{1,600}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[13] = {id = 13, massbossExtraTimes = 2, djtBuyTimes = 13, factiondonation = 13, factionybdonation = 13, treeTimes = 15, groupExpBuyTimes = 2, groupInstanceBuyTimes = 3, expRate = 30, offlineExpRate = 10, bag_size = {{0,200},{2,200},{3,200}}, chongzhi = 20000, gift = {{237,188},{3,6500000},{2,1300}}, cost = {{1,650}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[14] = {id = 14, massbossExtraTimes = 2, djtBuyTimes = 14, factiondonation = 14, factionybdonation = 14, treeTimes = 16, groupExpBuyTimes = 2, groupInstanceBuyTimes = 3, expRate = 30, offlineExpRate = 10, bag_size = {{0,200},{2,200},{3,200}}, chongzhi = 30000, gift = {{226,188},{3,7000000},{2,1400}}, cost = {{1,700}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
	[15] = {id = 15, massbossExtraTimes = 3, djtBuyTimes = 15, factiondonation = 15, factionybdonation = 15, treeTimes = 17, groupExpBuyTimes = 3, groupInstanceBuyTimes = 3, expRate = 30, offlineExpRate = 10, bag_size = {{0,200},{2,200},{3,200}}, chongzhi = 50000, gift = {{1505,188},{3,7500000},{2,1500}}, cost = {{1,750}}, massbossBuyTimes = 0, resReward = 0, djtReward = 0, qualifyReward = 0, groupReward = 0, worldbossReward = 0, trialReward = 0, riskReward = 0},
}
