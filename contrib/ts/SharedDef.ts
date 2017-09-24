//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////以下代码为自动生成，请勿手工改动//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SharedDef
	{

		public static MAX_MONEY:number = 2e+015;	// 最大金额数，超过下线再上就白瞎
		public static MAX_MONEY_TRUE:number = 4e+015;	// 最大金额数.真。超过就不再往上加
		public static MAX_BUFF_DURATION			:number = 65535;	// 无限BUFF时间
		public static INIT_QUEST_ID			:number = 1;
		public static ZHUCHENG_DITU_ID			:number = 1;	// 主城地图ID
		public static ZHUCHENG_FUHUO_X			:number = 141;	// 主城复活点
		public static ZHUCHENG_FUHUO_Y			:number = 163;	// 主城复活点
		public static BORN_MAP			:number = 1001;	// 出生地图
		public static BORN_X			:number = 143;	// 出生坐标x 
		public static BORN_Y			:number = 113;	// 出生坐标y
		public static BORN_OR			:number = 2;	// 出生朝向
		public static BORN_LV			:number = 1;	// 出生等级
		public static VIP_MAX_LEVEL			:number = 10;	// vip最大等级
		public static MAX_RMB_PLAYER_LEVEL			:number = 6;	// 最大的RMB等级
		// 服务器类型枚举
		public static WORLD_SERVER_TYPE_GAME			:number = 0;	// 游戏服
		public static WORLD_SERVER_TYPE_PK			:number = 1;	// pk服
		// 跨服类型枚举
		public static KUAFU_TYPE_NONE			:number = 0;
		public static KUAFU_TYPE_FENGLIUZHEN			:number = 1;	//  跨服风流镇
		public static KUAFU_TYPE_XIANFU			:number = 2;	//  跨服仙府夺宝
		public static KUAFU_TYPE_PLUNDER			:number = 3;	//  跨服家族掠夺
		public static KUAFU_TYPE_GROUP_INSTANCE			:number = 4;	//  跨服组队副本
		public static MATCH_TYPE_LOCAL_SINGLE_PVP			:number = 5;	//  本地单人PVP匹配
		public static MAX_KUAFU_TYPE			:number = 6;
		// 合服协议带的类型
		public static MERGE_TYPE_MERGE			:number = 0;	// 从服迁移连接到主服
		public static MERGE_TYPE_GAME_TO_PK			:number = 1;	// 游戏服到Pk服
		public static MERGE_TYPE_PK_TO_GAME			:number = 2;	// pk服到游戏服
		// 会话类型
		public static CONTEXT_TYPE_YEYOU			:number = 0;	// 页游
		public static CONTEXT_TYPE_PHONE			:number = 1;	// 手游
		public static MAX_CONTEXT_TYPE			:number = 2;
		// 性别
		public static CHAR_GENDER_MALE			:number = 0;	// 男性
		public static CHAR_GENDER_FEMALE			:number = 1;	// 女性
		public static CHAR_GENDER_NONE			:number = 2;	// 未知
		public static MAX_CHAR_GENDER			:number = 3;	// 长度		
		// 形象
		public static RACE_NONE			:number = 0;	// 无
		public static RACE_STRONG			:number = 1;	// 壮男
		public static RACE_HANDSOME			:number = 2;	// 俊男 
		public static RACE_LAURIE			:number = 3;	// 萝莉
		public static RACE_BEAUTY			:number = 4;	// 美人
		// 头像
		public static HEAD_NONE			:number = 0;	// 无
		public static HEAD_STRONG			:number = 1;	// 壮男
		public static HEAD_HANDSOME			:number = 2;	// 俊男 
		public static HEAD_LAURIE			:number = 3;	// 萝莉
		public static HEAD_BEAUTY			:number = 4;	// 美人	
		public static HEAD_TOTAL			:number = 4;
		// 复活类型
		public static RESURRECTION_IN_SITU			:number = 0;	// 原地复活
		public static RESURRECTION_SPAWNPOINT			:number = 1;	// 复活点复活
		public static RESURRPCTION_FREE			:number = 2;	// 免费复活
		public static RESURRPCTION_MONEY			:number = 3;	// 元宝复活
		public static RESURRPCTION_TIME			:number = 4;	// 超时复活
		public static RESURRPCTION_HUANHUNDAN			:number = 5;	// 还魂丹复活
		public static MAX_RESURRECTION_TYPE			:number = 6;
		// GM等级
		public static GM_LEVEL_0			:number = 0;	// 普通玩家
		public static GM_LEVEL_1			:number = 1;	// 普通GM
		public static GM_LEVEL_2			:number = 2;	// 高级GM
		public static GM_LEVEL_3			:number = 3;	// 终极GM
		// 游戏对象标志
		public static GO_FLAG_DYNAMIC			:number = 0;	// 是否动态对象,由不是由地图刷出来的
		public static GO_FLAG_TELE			:number = 1;	// 是否传送点对象
		public static GO_FLAG_QUEST			:number = 2;	// 是否任务对象
		public static GO_FLAG_LOOT			:number = 3;	// 是否战利品	
		public static GO_FLAG_GEAR			:number = 10;	// 是否机关，如箱子，门等
		public static GO_FLAG_UNUSE			:number = 4;	// 不可被使用
		public static GO_FLAG_FOREVER			:number = 5;	// 可永久使用
		public static GO_FLAG_USEMODE			:number = 8;	// 使用方式,需要进度条
		public static GO_FLAG_CARTON			:number = 9;	// 客户端模拟消失
		public static GO_FLAG_REBORN			:number = 11;	// 是否会重生 (如果有这项, GO_FLAG_FOREVER将不管用)
		public static GO_FLAG_SCRIPT			:number = 12;	// 是否使用脚本
		public static GO_FLAG_GET_ITEM_NOTICE			:number = 13;	// 拾起物品是否需要公告
		// 世界地图状态
		public static WORLD_MAP_DEFAULT			:number = 0;	// 新手村
		// 类枚举
		public static TYPEID_OBJECT			:number = 0;	// 本来0都是没用的
		public static TYPEID_UNIT			:number = 1;	// 生物精灵，如怪物，NPC，宝宝等。。。
		public static TYPEID_PLAYER			:number = 2;	// 玩家精灵
		public static TYPEID_GAMEOBJECT			:number = 3;	// 游戏对象精灵
		public static MAX_CLIENT_OBJECT_TYPES			:number = 4;
		// 物品品质
		public static ITEM_QUAL_WHITE			:number = 0;	// 白装
		public static ITEM_QUAL_GREEN			:number = 1;	// 绿装
		public static ITEM_QUAL_BLUE			:number = 2;	// 蓝装
		public static ITEM_QUAL_PURPLE			:number = 3;	// 紫装
		public static ITEM_QUAL_ORANGE			:number = 4;	// 橙装
		public static ITEM_QUAL_RED			:number = 5;	// 红装
		public static MAX_QUAL			:number = 6;
		// 攻击模式
		public static ATTACK_MODE_PEACE			:number = 0;	// 和平，不用说，你懂的
		public static ATTACK_MODE_TEAM			:number = 1;	// 组队，可以砍队伍以外的玩家
		public static ATTACK_MODE_RED			:number = 2;	// 红名，可以砍红名
		public static ATTACK_MODE_ALL			:number = 3;	// 全体，除了自己，谁都可以砍
		public static ATTACK_MODE_FACTION			:number = 4;	// 帮派模式
		public static ATTACK_MODE_BANG			:number = 5;	// 结义模式
		public static MAX_ATTACK_MODE			:number = 6;
		// 仇恨计算类型
		public static REACT_PASSIVE			:number = 0;	// 被动攻击
		public static REACT_DEFENSIVE			:number = 1;	// 防御
		public static REACT_AGGRESSIVE			:number = 2;	// 主动攻击,
		public static REACT_AGGRESSIVE_UNIT			:number = 3;	// 主动攻击怪物
		public static REACT_AGGRESSIVE_PLAYER			:number = 4;	// 主动攻击玩家
		public static MAX_REACT_STATES			:number = 5;
		// 合服操作类型
		public static MERGE_OPT_TYPE_INIT			:number = 0;	// 初始状态
		public static MERGE_OPT_TYPE_SAVE_DB			:number = 1;	// 数据保存完成
		public static MERGE_OPT_TYPE_TARGET_SERVER_OK			:number = 2;	// 目标服务器准备完成
		public static MERGE_OPT_TYPE_END			:number = 3;	// 操作结束
		public static MERGE_OPT_TYPE_SAVE_ING			:number = 4;	// 数据保存中
		// 合服服务器类型
		public static MERGE_SERVER_TYPE_ORIGINAL			:number = 1;	// 原始服务器
		public static MERGE_SERVER_TYPE_TARGAT			:number = 2;	// 目标服务器
		// 回档操作类型
		public static BACK_OPT_TYPE_INIT			:number = 0;	// 初始状态
		public static BACK_OPT_TYPE_SUCCESS			:number = 1;	// 成功
		// 物品绑定类型
		public static ITEM_BIND_NONE			:number = 0;	// 非绑定
		public static ITEM_BIND_USE			:number = 1;	// 使用绑定
		public static ITEM_BIND_GET			:number = 2;	// 获得绑定
		// 场景服给的东西获得类型
		public static ITEM_GIFT_GET_NONE			:number = 0;	// 非必须
		public static ITEM_GIFT_GET_MUST			:number = 1;	// 必须获得的
		// 玩家在线状态
		public static PLAYER_ONLINE_STATE_OUTLINE			:number = 0;	// 离线
		public static PLAYER_ONLINE_STATE_ONLINE			:number = 1;	// 在线
		// 生物移动模式
		public static DISAPPEAR_MOTION_TYPE			:number = 9999;	// 消失
		public static IDLE_MOTION_TYPE			:number = 0;	// 空闲
		public static RANDOM_MOTION_TYPE			:number = 1;	// 随机
		public static WAYPOINT_MOTION_TYPE			:number = 2;	// 沿路行走
		public static TARGET_MOTION_TYPE			:number = 3;	// 目标行走
		public static HOME_MOTION_TYPE			:number = 4;	// 回家
		public static CONFUSED_MOTION_TYPE			:number = 5;	// 困惑
		public static FLEEING_MOTION_TYPE			:number = 6;	// 逃避
		public static FOLLOW_MOTION_TYPE			:number = 7;	// 跟随
		public static FOLLOW_INLINE_MOTION_TYPE			:number = 8;	// 直线跟随
		public static WAYFINDING_MOTION_TYPE			:number = 9;	// 寻路行走
		public static WAYFINDING_ATTACK_MOTION_TYPE			:number = 10;	// 寻路追杀
		public static MERCENARY_MOTION_TYPE			:number = 11;	// 佣兵
		public static WAYFINDDST_MOTION_TYPE			:number = 12;	// 目的地行走
		public static DEADLINE_MOTION_TYPE			:number = 13;	// 过期消失
		public static MAX_MOTION_TYPE			:number = 14;
		// 技能目标类型 自己,友方,敌方,全体
		public static TARGET_TYPE_ONESELF			:number = 0;
		public static TARGET_TYPE_FRIENDLY			:number = 1;
		public static TARGET_TYPE_ENEMY			:number = 2;
		public static TARGET_TYPE_ALL			:number = 3;
		public static TARGET_TYPE_POINT			:number = 4;	// 对点释放技能 
		public static TARGET_TYPE_SELFPOINT			:number = 5;	// 对自己的点释放
		public static TARGET_TYPE_CREATURE			:number = 6;	// 对怪物有效（不包括宠物等）
		public static TARGET_TYPE_PLAYER			:number = 7;	// 对玩家有效
		// 交易状态
		public static TRADE_STATE_TYPE_FREE			:number = 0;	// 空闲状态
		public static TRADE_STATE_TYPE_APPLY			:number = 1;	// 申请状态
		public static TRADE_STATE_TYPE_EXECUTION			:number = 2;	// 执行状态
		public static TRADE_STATE_TYPE_PUT_ITEM_END			:number = 3;	// 确认物品完成
		public static TRADE_STATE_TYPE_WAIT_FINISH			:number = 4;	// 等待完成状态
		// 交易的类型
		public static TRADE_TYPE_TRADE			:number = 0;	// 交易
		public static TRADE_TYPE_STALL			:number = 1;	// 摆摊
		// 通过模板id移动物品到指定的包裹（相应的位置上），结果
		public static MOVE_ITEM_FAIL			:number = 0;	// 失败
		public static MOVE_ITEM_SUC			:number = 1;	// 成功
		public static MOVE_ITEM_HAVE_BIND			:number = 2;	// 包含绑定的
		public static MOVE_ITEM_NOT_BIND			:number = 3;	// 不包含绑定的
		// 删除物品结果
		public static SUB_ITEM_FAIL			:number = 0;	// 失败
		public static SUB_ITEM_HAVE_BIND			:number = 1;	// 包含绑定的
		public static SUB_ITEM_NOT_BIND			:number = 2;	// 不包含绑定的
		public static SUB_ITEM_HAVE_FAILTIME			:number = 3;	// 包含限时
		// 物品数据处理状态
		public static ITEM_SAVE_MODE_INSERT			:number = 0;	// 插入
		public static ITEM_SAVE_MODE_UPDATE			:number = 1;	// 更新
		// 元宝充值类型
		public static GOLD_INGOT_RECHARGE_NORMAL			:number = 1;	// 正常模式
		public static GOLD_INGOT_RECHARGE_HANDSEL			:number = 2;	// 赠送模式
		public static GOLD_INGOT_RECHARGE_SUB			:number = 3;	// 扣费模式
		public static GOLD_INGOT_RECHARGE_HAND			:number = 4;	// 手动模式
		public static MAX_GOLD_INGOT_RECHARGE_TYPE			:number = 5;
		// 充值状态类型
		public static RECHARGE_STATUS_TYPE_START			:number = 0;	// 初始化
		public static RECHARGE_STATUS_TYPE_RUNMING			:number = 1;	// 发放中
		public static RECHARGE_STATUS_TYPE_END			:number = 2;	// 结束
		// 踢人的状态类型
		public static KICKING_STATUS_START			:number = 0;	// 初始化
		public static KICKING_STATUS_END			:number = 1;	// 已踢
		// 封号的状态类型
		public static LOCKING_STATUS_START			:number = 0;	// 初始化
		public static LOCKING_STATUS_RUNNING			:number = 1;	// 封号中
		public static LOCKING_STATUS_END			:number = 2;	// 结束
		// 公告的状态类型
		public static SYSTEM_NOTICE_STATUS_START			:number = 0;	// 初始状态
		public static SYSTEM_NOTICE_STATUS_RUNNING			:number = 1;	// 运行中
		public static SYSTEM_NOTICE_STATUS_END			:number = 2;	// 结束
		public static SYSTEM_NOTICE_STATUS_DELETE			:number = 3;	// 将删除
		public static SYSTEM_NOTICE_STATUS_GARBAGE			:number = 4;	// 已删除
		// 礼包的状态类型
		public static GIFT_PACKS_STATUS_START			:number = 0;	// 初始
		public static GIFT_PACKS_STATUS_SENDING			:number = 1;	// 发放中
		public static GIFT_PACKS_STATUS_OK			:number = 2;	// 已发放
		public static GIFT_PACKS_STATUS_END			:number = 3;	// 已结束
		// 礼包发放类型
		public static GIFT_PACKS_AUDIENCE_TYPE_ONE			:number = 1;	// 个人礼包，如补偿礼包等
		public static GIFT_PACKS_AUDIENCE_TYPE_ALL			:number = 2;	// 全体同志的礼包
		public static GIFT_PACKS_AUDIENCE_TYPE_ALL_ONLINE			:number = 3;	// 全服在线玩家
		// 礼包操作类型
		public static GIFT_PACKS_OPER_TYPE_RECEIVE			:number = 0;	// 领取
		public static GIFT_PACKS_OPER_TYPE_READ			:number = 1;	// 已读
		public static GIFT_PACKS_OPER_TYPE_DELETE			:number = 2;	// 删除
		// 禁言状态
		public static GAG_STATUS_START			:number = 0;	// 初始化
		public static GAG_STATUS_OFFLINE			:number = 1;	// GAG_STATUS_OFFLINE		= 1,		//玩家离线
		public static GAG_STATUS_END			:number = 1;	// 已禁言
		// 设置GM表的状态
		public static GM_LEVEL_TABLE_START			:number = 0;	// 初始化
		public static GM_LEVEL_TABLE_END			:number = 1;	// 已执行
		// 公告类型
		public static NOTICE_TYPE_SCROLL			:number = 1;	// 滚动公告
		public static NOTICE_TYPE_PROMPT			:number = 2;	// 固定和世界聊天提示
		public static NOTICE_TYPE_FIXED			:number = 3;	// 固定提示
		public static MAX_NOTICE_TYPE			:number = 10;	// 预留10种
		// 聊天类型
		public static CHAT_TYPE_SYSTEM			:number = 0;	// 系统
		public static CHAT_TYPE_WORLD			:number = 1;	// 世界
		public static CHAT_TYPE_FACTION			:number = 2;	// 帮派
		public static CHAT_TYPE_CURRENT			:number = 3;	// 当前(场景)
		public static CHAT_TYPE_HORM			:number = 4;	// 喇叭
		public static CHAT_TYPE_GROUP			:number = 5;	// 队伍
		public static CHAT_TYPE_WHISPER			:number = 6;	// 私聊
		public static MAX_CHAT_TYPE			:number = 7;
		// 平台枚举
		public static PLATFORM_GAME2			:string = "2";	// 哥们网
		public static PLATFORM_QQ			:string = "360";	// 腾讯QQ
		public static PLATFORM_NULL			:string = "9999";	// 不需要post的平台
		// post的动作类型
		public static POST_TYPE_NONE			:number = 0;
		public static POST_TYPE_CHAT			:number = 1;	// 聊天
		public static POST_TYPE_UPGRADE			:number = 2;	// 用户升级
		public static MAX_POST_TYPE			:number = 3;
		// 记录到文件的日志类型
		public static LOG_FILE_TYPE_GAME_BUY			:number = 0;	// 记录用户在游戏内购买行为
		public static LOG_FILE_TYPE_GAME_SELL			:number = 1;	// 记录用户在游戏内出售行为
		public static LOG_FILE_TYPE_RECHARGE			:number = 2;	// 记录用户充值行为
		public static LOG_FILE_TYPE_SHOP_BUY			:number = 3;	// 记录用户在商城的购买行为
		public static LOG_FILE_TYPE_ITEM_USE			:number = 4;	// 记录用户使用商城物品行为
		public static LOG_FILE_TYPE_DEAL			:number = 5;	// 记录用户的交易行为
		public static LOG_FILE_TYPE_YB_INCOME			:number = 6;	// 记录额外元宝收入
		public static LOG_FILE_TYPE_ITEM_INCOME			:number = 7;	// 记录额外道具收入
		public static LOG_FILE_TYPE_YB_EXPEND			:number = 8;	// 记录额外元宝消费
		public static LOG_FILE_TYPE_LOGIN			:number = 9;	// 记录用户登录行为
		public static LOG_FILE_TYPE_LOGOUT			:number = 10;	// 记录用户登出行为
		public static LOG_FILE_TYPE_CREATE_ROLE			:number = 11;	// 记录用户创建角色行为
		public static LOG_FILE_TYPE_DEATH			:number = 12;	// 记录用户角色死亡事件
		public static LOG_FILE_TYPE_ACCEPT_TASK			:number = 13;	// 记录用户接收任务的行为
		public static LOG_FILE_TYPE_TASK			:number = 14;	// 记录用户完成任务的行为
		public static LOG_FILE_TYPE_UPGRADE			:number = 15;	// 记录用户升级事件
		public static LOG_FILE_TYPE_GOLD			:number = 16;	// 记录用户金币所得行为
		public static LOG_FILE_TYPE_MAP			:number = 17;	// 记录用户切换地图的行为
		public static LOG_FILE_TYPE_LONGER			:number = 18;	// 记录用户的挂机行为
		public static LOG_FILE_TYPE_MONSTER			:number = 19;	// 记录用户打怪的行为
		public static LOG_FILE_TYPE_TRANSCRIPT			:number = 20;	// 记录用户打副本的行为
		public static LOG_FILE_TYPE_ONLINE			:number = 21;	// 记录在线人数
		public static LOG_FILE_TYPE_GAME_ENTER			:number = 22;	// 记录用户进入游戏主界面
		public static LOG_FILE_TYPE_ITEM_LOG			:number = 23;	// 记录道具的所有行为
		public static LOG_FILE_TYPE_CHAT			:number = 24;	// 记录玩家聊天记录
		public static LOG_FILE_TYPE_RELIVE			:number = 25;	// 记录玩家复活
		public static LOG_FILE_TYPE_BIND_GOLD			:number = 26;	// 记录玩家的绑定元宝行为
		public static LOG_FILE_TYPE_NEW_CARD_RECEIVE			:number = 27;	// 记录用户领取新手卡的行为
		public static LOG_FILE_TYPE_STALL			:number = 28;	// 记录摆摊行为
		public static LOG_FILE_TYPE_WANTED_PACKET			:number = 29;	// 记录被通缉的玩家的所有包记录
		public static LOG_FILE_TYPE_ERROR_PACKET			:number = 30;	// 记录读取用户信息出错的包
		public static LOG_FILE_TYPE_CHOOSE_FACTION			:number = 31;	// 记录玩家选择阵营的情况
		public static LOG_FILE_TYPE_ACTIVITY_INFO			:number = 32;	// 记录运营活动奖励信息
		public static LOG_FILE_TYPE_ABNORMAL_PACKETS			:number = 33;	// 记录因为异常包而踢掉玩家的行为
		public static LOG_FILE_TYPE_CLIENT_INFO			:number = 34;	// 记录玩家客户端信息
		public static LOG_FILE_TYPE_GIFTMONEY_BUY			:number = 35;	// 记录玩家礼金消耗的行为
		public static LOG_FILE_TYPE_GIFTMONEY_INCOME			:number = 36;	// 记录用户礼金获得的行为
		public static LOG_FILE_TYPE_ATTACK_PACKET			:number = 37;	// 记录攻击包
		public static LOG_FILE_TYPE_FORMAT_LOG			:number = 38;	// 记录乱七八糟的自定义日志
		public static LOG_FILE_TYPE_CLIENT_LOG			:number = 39;	// 记录客户端日志
		public static LOG_FILE_TYPE_FORGE_LOG			:number = 40;	// 记录锻造日志
		public static LOG_FILE_TYPE_OBJECT_LOSS			:number = 41;	// 1001日志
		public static MAX_LOG_FILE_TYPE			:number = 42;
		public static SKILL_EFFECT_TYPE_NORMAL			:number = 0;	// 普通效果类型
		public static SKILL_EFFECT_TYPE_HUIXUE1			:number = 1;	// 敌方扣血, 自己加血
		public static SKILL_EFFECT_TYPE_ROAR			:number = 2;	// 战吼
		public static SKILL_EFFECT_TYPE_BLADE_STORM			:number = 3;	// 剑刃风暴 (每多少秒扣血还是怎么的?)
		public static SKILL_EFFECT_TYPE_HEAL			:number = 4;	// 治疗之泉
		public static SKILL_EFFECT_TYPE_SNOW_STORM			:number = 5;	// 暴风雪
		public static SKILL_EFFECT_TYPE_LOADED			:number = 99;	// 蓄力时间到释放技能
		// 记录腾讯文件的日志类型
		public static LOG_FILE_TENCENT_USER			:number = 0;	// 用户表
		public static LOG_FILE_TENCENT_PLAYER			:number = 1;	// 角色表
		public static LOG_FILE_TENCENT_RECHAGRE			:number = 2;	// 充值表
		public static LOG_FILE_TENCENT_UPGRADELOG			:number = 3;	// 升级日志
		public static LOG_FILE_TENCENT_NEWTASK			:number = 4;	// 新手日志
		public static LOG_FILE_TENCENT_LOGIN			:number = 5;	// 登陆日志
		public static LOG_FILE_TENCENT_OFFLINE			:number = 6;	// 离线日志
		public static LOG_FILE_TENCENT_ONLINE			:number = 7;	// 在线统计日志
		public static LOG_FILE_TENCENT_MONEYLOG			:number = 8;	// 金币流量
		public static MAX_LOG_FILE_TENCENT_TYPE			:number = 9;
		//  死亡地类型
		public static DEAD_PLACE_TYPE_FIELD			:number = 1;	//  野外死亡
		public static DEAD_PLACE_TYPE_XIANFU			:number = 2;	//  仙府夺宝死亡
		public static DEAD_PLACE_TYPE_GROUP_INSTANCE			:number = 3;	//  组队副本死亡
		// 攻击包异常类型
		public static ACCACK_PACKET_TYPE_UNPACK			:number = 0;	// 解包失败
		public static ACCACK_PACKET_TYPE_DATA			:number = 1;	// 数据异常
		public static ACCACK_PACKET_TYPE_ORDER			:number = 2;	// 包顺序异常
		public static ACCACK_PACKET_TYPE_DISCARD			:number = 3;	// 废弃的包号
		public static MAX_ACCACK_PACKET_TYPE			:number = 4;
		// 交易物品
		// 装备ID
		// 模版ID
		// 类型
		// 数量
		// 额外元宝获得类型
		public static LOG_YB_INCOME_TYPE_ACTIVITY			:number = 0;	// 活动赠送
		public static LOG_YB_INCOME_TYPE_RECHARGE			:number = 1;	// 充值赠送
		public static LOG_YB_INCOME_TYPE_USE_ITEM			:number = 2;	// 使用道具
		public static LOG_YB_INCOME_TYPE_GIFT_PACKS			:number = 3;	// 补偿礼包
		// 道具操作类型
		// NOTICE 这个用于自定义道具的来源及客户端的提示reason是对应的
		// 获得
		public static LOG_ITEM_OPER_TYPE_ACTIVITY			:number = 0;	// 活动奖励获得
		public static LOG_ITEM_OPER_TYPE_RECHARGE			:number = 1;	// 充值赠送获得
		public static LOG_ITEM_OPER_TYPE_GIFT_PACKS			:number = 2;	// 补偿礼包获得
		public static LOG_ITEM_OPER_TYPE_QUEST			:number = 3;	// 任务完成奖励获得
		public static LOG_ITEM_OPER_TYPE_NEWPLAYER			:number = 4;	// 新手礼包获得
		public static LOG_ITEM_OPER_TYPE_OPEN_ITEM			:number = 5;	// 使用道具获得
		public static LOG_ITEM_OPER_TYPE_LOOT			:number = 6;	// 战利品
		public static LOG_ITEM_OPER_TYPE_GM_COMMAND			:number = 7;	// GM命令获得
		public static LOG_ITEM_OPER_TYPE_ITEM_BLEND			:number = 8;	// 物品合成获得
		public static LOG_ITEM_OPER_TYPE_SEVEN_DAY_GIFT			:number = 9;	// 连登礼包	
		public static LOG_ITEM_OPER_TYPE_JHM_GIFT			:number = 10;	// 激活码礼包
		public static LOG_ITEM_OPER_TYPE_OPEN_BOX			:number = 11;	// 开宝箱获得
		public static LOG_ITEM_OPER_TYPE_FUBEN_EWAIJINAGLI			:number = 12;	// 副本额外奖励
		public static LOG_ITEM_OPER_TYPE_CAPTURE_YAOHUN			:number = 13;	// 扑捉妖魂获得
		public static LOG_ITEM_OPER_TYPE_FSZL_EWAIJINAGLI			:number = 14;	// 飞升之路奖励
		public static LOG_ITEM_OPER_TYPE_PRESTIGE			:number = 15;	// 活跃度领取获得
		public static LOG_ITEM_OPER_TYPE_TIANDILINGKUANG			:number = 16;	// 天地灵矿领取获得
		public static LOG_ITEM_OPER_TYPE_PANTAOYUAN			:number = 17;	// 蟠桃园奖励
		public static LOG_ITEM_OPER_TYPE_WABAO			:number = 18;	// 挖宝获得
		public static LOG_ITEM_OPER_TYPE_HONGYAN			:number = 19;	// 红颜事件获得
		public static LOG_ITEM_OPER_TYPE_FORGE_DECOMPOSE			:number = 20;	// 锻造分解获得
		public static LOG_ITEM_OPER_TYPE_WORLD_BOSS_ROLL			:number = 21;	// 世界BOSSroll点
		public static LOG_ITEM_OPER_TYPE_VIP_INSTANCE_REWARD			:number = 22;	// vip副本奖励
		public static LOG_ITEM_OPER_TYPE_TRIAL_INSTANCE_REWARD			:number = 23;	// 试炼塔奖励
		public static LOG_ITEM_OPER_TYPE_ACHIEVE			:number = 24;	// 成就奖励
		public static LOG_ITEM_OPER_TYPE_SHOUCHONG			:number = 25;	// 首充奖励
		public static LOG_ITEM_OPER_TYPE_CHECKIN			:number = 26;	// 每日签到奖励
		public static LOG_ITEM_OPER_TYPE_GETBACK			:number = 27;	// 找回次数奖励
		public static LOG_ITEM_OPER_TYPE_TOTAL_CHECKIN			:number = 28;	// 每日累积签到奖励
		public static LOG_ITEM_OPER_TYPE_WELFARE_LEVEL			:number = 29;	// 福利等级奖励
		public static LOG_ITEM_OPER_TYPE_3V3_KUAFU			:number = 30;	// 3v3跨服奖励
		public static LOG_ITEM_OPER_TYPE_INSTANCE_SWEEP			:number = 31;	// 副本奖励扫荡奖励
		public static LOG_ITEM_OPER_TYPE_XIANFU			:number = 32;	// 仙府夺宝跨服奖励
		public static LOG_ITEM_OPER_TYPE_DOUJIAN_FIRST_REWARD			:number = 33;	// 斗剑台首胜奖励
		public static LOG_ITEM_OPER_TYPE_DOUJIAN_COMBAT_REWARD			:number = 34;	// 斗剑台连胜奖励
		public static LOG_ITEM_OPER_TYPE_CULTIVATION_REWARD			:number = 35;	// 修炼场奖励
		public static LOG_ITEM_OPER_TYPE_CULTIVATION_PLUNDER_REWARD			:number = 36;	// 修炼场掠夺奖励
		public static LOG_ITEM_OPER_TYPE_LOGIN_ACTIVITY_REWARD			:number = 37;	// 登录大礼奖励
		public static LOG_ITEM_OPER_TYPE_GROUP_INSTANCE			:number = 38;	// 组队副本跨服奖励
		public static LOG_ITEM_OPER_TYPE_XIANFU_PRACTISE			:number = 40;	// 仙府夺宝体验奖励
		public static LOG_ITEM_OPER_TYPE_FACTION_BOSS			:number = 41;	// 帮派boss奖励
		public static LOG_ITEM_OPER_TYPE_OFFLINE			:number = 42;	// 离线奖励
		public static LOG_ITEM_OPER_TYPE_STOREHOUSE			:number = 43;	// 帮派宝库
		public static LOG_ITEM_OPER_TYPE_MASS_BOSS			:number = 44;	// 全民BOSS
		// 购买
		public static LOG_ITEM_OPER_TYPE_SHOP_BUY			:number = 45;	// 从商场购买获得
		public static LOG_ITEM_OPER_TYPE_FACTION_BOSSDEFENSE			:number = 46;	// 家族首领挑战击杀奖励
		public static LOG_ITEM_OPER_TYPE_FACTION_TOWER			:number = 47;	// 家族无尽远征奖励
		public static LOG_ITEM_OPER_TYPE_SINGLE_PVP			:number = 48;	// 单人PVP
		public static LOG_ITEM_OPER_TYPE_ACT_LOTTERY			:number = 49;	// 抽奖活动
		public static LOG_ITEM_OPER_TYPE_ACT_DAILYGIFT			:number = 50;	// 每日礼包活动
		public static LOG_ITEM_OPER_TYPE_ACT_RANK			:number = 51;	// 每日排行活动
		public static LOG_ITEM_OPER_TYPE_ACT_LIMITGIFT			:number = 52;	// 限定礼包活动
		public static LOG_ITEM_OPER_TYPE_RECHARGE_REWARD			:number = 53;	// 充值返利
		public static LOG_ITEM_OPER_TYPE_CONSUME_REWARD			:number = 54;	// 消费返利
		public static LOG_ITEM_OPER_TYPE_NPC_BUY			:number = 102;	// 从NPC购买获得
		public static LOG_ITEM_OPER_TYPE_BIND_SHOP_BUY			:number = 103;	// 从绑定商城购买获得
		public static LOG_ITEM_OPER_TYPE_REPURCHASE			:number = 104;	// 从NPC回购物品获得
		public static LOG_ITEM_OPER_TYPE_ACTI_BUY			:number = 105;	// 活动购买
		public static LOG_ITEM_OPER_TYPE_XIANFU_BUY			:number = 106;	// 购买仙府进入券
		// 消耗
		public static LOG_ITEM_OPER_TYPE_NPC_SELL			:number = 200;	// 出售给NPC
		public static LOG_ITEM_OPER_TYPE_DEL_FAILTIME			:number = 201;	// 清理限时物品
		public static LOG_ITEM_OPER_TYPE_USE			:number = 202;	// 使用物品
		public static LOG_ITEM_OPER_TYPE_DISPOSE			:number = 203;	// 销毁物品
		public static LOG_ITEM_OPER_TYPE_HEAL			:number = 204;	// 吃药
		// 交易
		public static LOG_ITEM_OPER_TYPE_TRADE_GET			:number = 301;	// 交易获得
		public static LOG_ITEM_OPER_TYPE_TRADE_PAY			:number = 302;	// 交易付出
		public static LOG_ITEM_OPER_TYPE_STALL_OPEN			:number = 303;	// 摆摊
		public static LOG_ITEM_OPER_TYPE_STALL_CLOSE			:number = 304;	// 收摊
		public static LOG_ITEM_OPER_TYPE_STALL_BUY			:number = 305;	// 摊位购买
		public static LOG_ITEM_OPER_TYPE_LINGDI_XUANSHANG			:number = 306;	// 领地悬赏
		public static LOG_ITEM_OPER_TYPE_LINGDI_MIJING			:number = 307;	// 领地秘境
		public static LOG_ITEM_OPER_TYPE_WUJIANG_ZHENGZHAN			:number = 308;	// 武将征战
		public static LOG_ITEM_OPER_TYPE_KAOZHUANGYUAN			:number = 309;	// 考状元
		public static LOG_ITEM_OPER_TYPE_MONEYTREE_GIFT			:number = 310;	// 摇钱树礼包
		// 后台货币变化种类枚举
		public static HT_MONEY_CHANGE_TYPE_RECHARGE			:number = 1;	// 充值
		public static HT_MONEY_CHANGE_TYPE_CONSUMPTION			:number = 2;	// 消费
		public static HT_MONEY_CHANGE_TYPE_SUB			:number = 3;	// 管理员扣除
		public static HT_MONEY_CHANGE_TYPE_REWARD			:number = 4;	// 奖励
		public static HT_MONEY_CHANGE_TYPE_REBATE			:number = 5;	// 返利
		public static HT_MONEY_CHANGE_TYPE_TRADING			:number = 6;	// 交易
		// 货币变化原因类型
		public static MONEY_CHANGE_TYPE_CHARGE			:number = 0;	// 玩家充值
		public static MONEY_CHANGE_TYPE_STORE_BUY			:number = 1;	// 商店购买
		public static MONEY_CHANGE_TYPE_MALL_BUY			:number = 2;	// 商城购买
		public static MONEY_CHANGE_TYPE_STALL_SALE			:number = 3;	// 摊位卖出
		public static MONEY_CHANGE_TYPE_TRADE			:number = 4;	// 玩家交易
		public static MONEY_CHANGE_MAIL			:number = 5;	// 邮件
		public static MONEY_CHANGE_QUEST			:number = 6;	// 任务奖励
		public static MONEY_CHANGE_DEAD			:number = 7;	// 死亡掉落
		public static MONEY_CHANGE_RIHUAN			:number = 8;	// 日环
		public static MONEY_CHANGE_USE_ITEM			:number = 9;	// 使用物品消耗
		public static MONEY_CHANGE_GIFT_PACKS			:number = 10;	// 系统礼包赠送
		public static MONEY_CHANGE_NPC_SELL			:number = 11;	// NPC出售
		public static MONEY_CHANGE_ITEM_REPAIR			:number = 12;	// 预留
		public static MONEY_CHANGE_ITEM_APPRAISAL			:number = 13;	// 预留
		public static MONEY_CHANGE_NPC_REPURCHASE			:number = 14;	// NPC回购
		public static MONEY_CHANGE_GM_COMMAND			:number = 15;	// GM招财命令
		public static MONEY_CHANGE_CREATE_FACTION			:number = 16;	// 创建帮派
		public static MONEY_CHANGE_WAREHOUSE_HANLD			:number = 17;	// 仓库操作
		public static MONEY_CHANGE_SELECT_LOOT			:number = 18;	// 战利品
		public static MONEY_CHANGE_ACTIVITY			:number = 19;	// 活动奖励
		public static MONEY_CHANGE_TYPE_CHARGE_2			:number = 20;	// 充值额外赠送
		public static MONEY_CHANGE_TYPE_CHARGE_3			:number = 21;	// 管理员扣除
		public static MONEY_CHANGE_TYPE_CHARGE_4			:number = 22;	// 手动赠送
		public static MONEY_CHANGE_USE_LABA			:number = 23;	// 使用喇叭
		public static MONEY_CHANGE_BAG_EXTENSION			:number = 24;	// 背包扩展
		public static MONEY_CHANGE_ITEM_BLEND			:number = 25;	// 物品合成消耗铜钱
		public static MONEY_CHANGE_SEVEN_DAY_GIFT			:number = 26;	// 连登礼包
		public static MONEY_CHANGE_CLEAR_PK_VALUE			:number = 27;	// 使用元宝洗白
		public static MONEY_CHANGE_JHM_REWARD			:number = 28;	// 激活码奖励
		public static MONEY_CHANGE_ONLINE_GIFT			:number = 29;	// 每日在线奖励
		public static MONEY_CHANGE_SPELL_UP			:number = 30;	// 技能升阶
		public static MONEY_CHANGE_USE_BOX			:number = 31;	// 使用宝箱消耗
		public static MONEY_CHANGE_BOX_OPEN			:number = 32;	// 开宝箱获得
		public static MONEY_CHANGE_BOX_RANDOM			:number = 33;	// 开宝箱随机奖励
		public static MONEY_CHANGE_JINGJIE			:number = 34;	// 升级境界消耗
		public static MONEY_CHANGE_SHENBING_BUY			:number = 35;	// 神兵购买
		public static MONEY_CHANGE_ATUO_GOLD_RESPAWN			:number = 36;	// 元宝复活
		public static MONEY_CHANGE_FUBEN_KILLALL			:number = 37;	// 副本全图秒杀消耗
		public static MONEY_CHANGE_FUBEN_EWAI			:number = 38;	// 副本额外奖励
		public static MONEY_CHANGE_FUBEN_BUY			:number = 39;	// 购买副本次数消耗
		public static MONEY_CHANGE_FSZL_REWARD			:number = 40;	// 飞升之路奖励
		public static MONEY_CHANGE_PRESTIGE			:number = 41;	// 活跃度
		public static MONEY_CHANGE_PANTAO_CAIJI			:number = 42;	// 采集蟠桃获得
		public static MONEY_CHANGE_LINGKUANG_CAIJI			:number = 43;	// 采集灵矿获得	
		public static MONEY_CHANGE_QIYU_ZHUOYAO			:number = 44;	// 扑捉妖魂消耗
		public static MONEY_CHANGE_RESET_FORGE_ADD			:number = 45;	// 重置锻造加成时间
		public static MONEY_CHANGE_WABAO			:number = 46;	// 挖宝获得
		public static MONEY_CHANGE_HONGYAN_BUY_HUOLI			:number = 47;	// 红颜购买活力
		public static MONEY_CHANGE_HONGYAN_SHIJIAN			:number = 48;	// 红颜事件获得
		public static MONEY_CHANGE_HONGYAN_BUY_FASHION			:number = 49;	// 红颜购买时装
		public static MONEY_CHANGE_FORGE_STRENG			:number = 50;	// 锻造强化
		public static MONEY_CHANGE_FORGE_GEM			:number = 51;	// 宝石
		public static MONEY_CHANGE_LINGDI_ZHAOMU			:number = 52;	// 领地招募
		public static MONEY_CHANGE_LINGDI_XUANSHANG			:number = 53;	// 领地悬赏
		public static MONEY_CHANGE_LINGDI_MIJING			:number = 54;	// 领地秘境
		public static MONEY_CHANGE_WUJIANG_REFRESH_PUB			:number = 55;	// 元宝刷新酒馆武将
		public static MONEY_CHANGE_FENGLIUZHEN_PUB_AUCTION			:number = 56;	// 风流镇酒馆竞拍
		public static MONEY_CHANGE_WUJIANG_QINGJIU			:number = 55;	// 元宝清酒武将
		public static MONEY_CHANGE_LINGDI_ZHENGBING			:number = 56;	// 领地征兵
		public static MONEY_CHANGE_FENGLIUZHEN_ZHUANPAN_ENTER			:number = 57;	// 风流镇转盘进去房间
		public static MONEY_CHANGE_USE_SPELL			:number = 58;	// 使用技能
		public static MONEY_CHANGE_UP_ASSISTSPELL			:number = 59;	// 升级辅助技能
		public static MONEY_CHANGE_LINGDI_BUY_BINGLI			:number = 60;	// 领地征兵购买兵力
		public static MONEY_CHANGE_WUJIANG_ZHENGZHAN			:number = 61;	// 武将征战
		public static MONEY_CHANGE_BUY_JUNLLING			:number = 62;	// 购买军令
		public static MONEY_CHANGE_SELL_WUJIANG_EQUIP			:number = 63;	// 出售武将装备
		public static MONEY_CHANGE_FENGLIUZHEN_KAOZHUANGYUAN			:number = 64;	// 考状元奖励
		public static MONEY_CHANGE_ZHUBO_SEND_GIFTS			:number = 65;	// 主播送礼消耗
		public static MONEY_CHANGE_ZHUBO_GRAB_SOFA			:number = 66;	// 主播抢沙发
		public static MONEY_CHANGE_RAISE_MOUNT			:number = 67;	// 升级坐骑
		public static MONEY_CHANGE_ILLUSION			:number = 68;	// 坐骑幻化
		public static MONEY_CHANGE_BIND_INGOT_NOT_ENOUGH			:number = 69;	// 购买道具绑银不足消耗元宝
		public static MONEY_CHANGE_ACTIVE_SPELL			:number = 70;	// 激活技能
		public static MONEY_CHANGE_BUY_VIP_INSTANCE			:number = 71;	// 购买VIP副本进入次数
		public static MONEY_CHANGE_BUY_HP_ITEM			:number = 72;	// 购买回血药品
		public static MONEY_CHANGE_RESET_TRIAL			:number = 73;	// 重置试炼塔
		public static MONEY_CHANGE_SOCIAL_GIFT			:number = 74;	// 好友赠送礼物
		public static MONEY_CHANGE_FACTION_DONATION			:number = 75;	// 帮派捐献
		public static MONEY_CHANGE_FACTION_SHOP			:number = 76;	// 帮派商店
		public static MONEY_CHANGE_WORLD_BOSS_ROLL			:number = 77;	// 世界BOSSroll点
		public static MONEY_CHANGE_VIP_INSTANCE_REWARD			:number = 78;	// VIP副本奖励
		public static MONEY_CHANGE_TRIAL_INSTANCE_REWARD			:number = 79;	// 试炼塔奖励
		public static MONEY_CHANGE_WELF_ACTIVE_GETBACK			:number = 80;	// 福利活动找回奖励
		public static MONEY_CHANGE_SHOUCHONG			:number = 81;	// 首冲奖励
		public static MONEY_CHANGE_CHECKIN			:number = 82;	// 每日签到奖励
		public static MONEY_CHANGE_TOTAL_CHECKIN			:number = 83;	// 每日累积签到奖励
		public static MONEY_CHANGE_WELFARE_LEVEL			:number = 84;	// 等级福利奖励
		public static MONEY_CHANGE_ACHIEVE			:number = 85;	// 成就奖励
		public static MONEY_CHANGE_3V3KUAFU			:number = 86;	// 3v3跨服奖励
		public static MONEY_CHANGE_VIP_INSTANCE_SWEEP			:number = 87;	// 副本扫荡
		public static MONEY_CHANGE_GIFT_PACKET			:number = 88;	// 礼包
		public static MONEY_CHANGE_KUAFU_WORLD_3V3			:number = 89;	// 跨服3v3
		public static MONEY_CHANGE_KUAFU_WORLD_XIANFU			:number = 90;	// 跨服仙府夺宝
		public static MONEY_CHANGE_BUY_XIANFU_TICKET			:number = 91;	// 购买仙府进入券
		public static MONEY_CHANGE_DOUJIAN_BUY_TIMES			:number = 92;	// 斗剑台购买次数
		public static MONEY_CHANGE_DOUJIAN_CLEARCD			:number = 93;	// 斗剑台清理CD
		public static MONEY_CHANGE_DOUJIAN_FIRST_REWARD			:number = 94;	// 斗剑台首胜奖励
		public static MONEY_CHANGE_DOUJIAN_COMBATWIN_REWARD			:number = 95;	// 斗剑台连胜奖励
		public static MONEY_CHANGE_CULTIVATION_PURCHASE			:number = 96;	// 修炼场购买次数
		public static MONEY_CHANGE_CULTIVATION_REWARD			:number = 97;	// 修练场奖励
		public static MONEY_CHANGE_CULTIVATION_PLUNDER_REWARD			:number = 98;	// 修练场掠夺奖励
		public static MONEY_CHANGE_LOGIN_ACTIVITY_REWARD			:number = 99;	// 登陆大礼奖励
		public static MONEY_CHANGE_FACTION_BOSS			:number = 100;	// 帮派boss奖励
		public static MONEY_CHANGE_OFFLINE			:number = 101;	// 离线奖励
		public static MONEY_CHANGE_STOREHOUSE			:number = 102;	// 帮派宝库
		public static MONEY_CHANGE_MASS_BOSS			:number = 103;	// 全民BOSS
		public static MONEY_CHANGE_MASS_BOSS_BUY_TIMES			:number = 104;	// 全民BOSS挑战次数
		public static MONEY_CHANGE_GROUP_INSTANCE_BUY_TIMES			:number = 105;	// 组队副本挑战次数
		public static MONEY_CHANGE_KUAFU_GROUP_INSTANCE			:number = 106;	// 跨服组队副本
		public static MONEY_CHANGE_MERIDIAN			:number = 107;	// 经脉修炼
		public static MONEY_CHANGE_FACTION_BOSSDEFENSE			:number = 108;	// 家族首领挑战 击杀奖励
		public static MONEY_CHANGE_FACTION_TOWER			:number = 109;	// 家族无尽远征 击杀奖励
		public static MONEY_CHANGE_SINGLE_PVP			:number = 110;	// 单人PVP
		public static MONEY_CHANGE_EQUIPDEVELOP			:number = 111;	// 装备养成消耗
		public static MONEY_CHANGE_APPEARANCE			:number = 112;	// 外观
		public static MONEY_CHANGE_FACTIONSKILL			:number = 113;	// 家族技能消耗
		public static MONEY_CHANGE_UNLOCKTITLE			:number = 114;	// 家族技能消耗
		public static MONEY_CHANGE_RENAME			:number = 115;	// 改名
		public static MONEY_CHANGE_RANK_LIKE			:number = 116;	// 排行榜点赞
		public static MONEY_CHANGE_ACT_LOTTERY			:number = 117;	// 抽奖活动
		public static MONEY_CHANGE_ACT_DAILYGIFT			:number = 118;	// 每日礼包
		public static MONEY_CHANGE_ACT_RANK			:number = 119;	// 开服排行
		public static MONEY_CHANGE_ACT_LIMITGIFT			:number = 120;	// 限定礼包
		public static MONEY_CHANGE_RECHARGE_REWARD			:number = 121;	// 充值返利
		public static MONEY_CHANGE_CONSUME_REWARD			:number = 122;	// 消费返利
		public static MONEY_CHANGE_MONEYTREE_USE			:number = 123;	// 摇动摇钱树
		public static MAX_MONEY_CHANGE_TYPE			:number = 124;
		// 特殊包裹类型
		public static BAG_VIRTUAL_TYPE_STALL			:number = -1;	// 摆摊
		public static BAG_VIRTUAL_TYPE_UNKNOWN			:number = -2;	// 未知
		public static SPECIALL_BAG_TYPE_MAIL			:number = -3;	// 邮件
		// 物品类型
		public static ITEM_TYPE_NONE			:number = 0;	// 无
		public static ITEM_TYPE_EQUIP			:number = 1;	// 装备
		public static ITEM_TYPE_BOX			:number = 15;	// 宝箱类（使用获得道具类型的物品）
		public static ITEM_TYPE_MATERIAL			:number = 3;	// 材料
		public static ITEM_TYPE_MEDICINE			:number = 12;	// 药品
		public static ITEM_TYPE_FASHION			:number = 5;	// 时装
		public static ITEM_TYPE_BUFF			:number = 25;	// 获得buff型
		public static ITEM_TYPE_SHELI			:number = 6;	// 舍利
		public static ITEM_TYPE_PK_MEDICINE			:number = 7;	// PK药品
		public static ITEM_TYPE_PET_MEDICINE			:number = 8;	// 宠物药
		public static ITEM_TYPE_NUMBER			:number = 9;	// 数值类型
		//  获得道具以后的记录
		public static ITEM_RECORD_BROADCAST			:number = 1;	//  全服广播
		public static ITEM_RECORD_XIANFU			:number = 2;	//  仙府夺宝记录
		public static ITEM_RECORD_MAP			:number = 3;	//  地图通知
		//  masks for ITEM_INT_FIELD_FLAGS field
		public static ITEM_FLAGS_QUEST			:number = 0;	//  是否任务物品
		public static ITEM_FLAGS_RMB			:number = 1;	// 是否RMB物品
		public static ITEM_FLAGS_APPRAISAL			:number = 2;	// 是否鉴定
		public static ITEM_FLAGS_BROKEN			:number = 3;	//  是否损坏的,耐久0
		public static ITEM_FLAGS_USABLE			:number = 4;	//  是否可用的
		public static ITEM_FLAGS_LOCKED			:number = 5;	//  物品锁定标志
		public static ITEM_FLAGS_REFUNDABLE			:number = 6;	//  可回购的
		public static ITEM_FLAGS_UNIQUE_EQUIPPED			:number = 7;	// 是否独特装备
		public static ITEM_FLAGS_SPECIALUSE			:number = 8;	//  特殊用途
		public static ITEM_FLAGS_BOP_TRADEABLE			:number = 9;	// 是否可交易的
		public static ITEM_FLAGS_IS_BINDED			:number = 10;	// 是否绑定
		public static ITEM_FLAGS_IS_JIPIN			:number = 11;	// 是否极品装备
		// 物品使用对象类型
		public static ITEM_USE_SELF			:number = 0;	// 自己
		public static ITEM_USE_TARGET			:number = 1;	// 目标
		public static ITEM_USE_NULL			:number = 2;	// 不可使用
		// 物物品使用结果类型
		public static ITEM_USE_RESULT_DISAPPEAR			:number = 0;	// 消失
		public static ITEM_USE_RESULT_NOT_DISAPPEAR			:number = 1;	// 不消失
		public static ITEM_USE_RESULT_SUB_DURABLE			:number = 2;	// 减少耐久
		public static ITEM_USE_RESULT_UN_USE			:number = 3;	// 不可使用
		// 道具返还类型
		public static LOG_ITEM_RETURN_TYPE_HAVE			:number = 0;	// 返还背包得到
		public static LOG_ITEM_RETURN_TYPE_LOSE			:number = 1;	// 返还背包失去
		public static LOG_ITEM_RETURN_TYPE_CLEAR			:number = 2;	// 返还背包清理
		public static LOG_ITEM_RETURN_TYPE_GOLD			:number = 3;	// 材料不足自动购买
		// 坐骑状态
		public static MOUNT_STATE_FREE			:number = 0;	// 空闲
		public static MOUNT_STATE_WAS_RIDING			:number = 1;	// 骑乘
		// 任务状态
		public static QUEST_STATUS_NONE			:number = 0;	//  
		public static QUEST_STATUS_COMPLETE			:number = 1;	// 完成
		public static QUEST_STATUS_UNAVAILABLE			:number = 2;	// 得不到的，没空的，不能利用的???
		public static QUEST_STATUS_INCOMPLETE			:number = 3;	// 不完全,未完成
		public static QUEST_STATUS_AVAILABLE			:number = 4;	// 有效，可接受
		public static QUEST_STATUS_FAILED			:number = 5;	// 失败
		public static QUEST_STATUS_END			:number = 6;	// 任务结束,已领奖
		public static QUEST_STATUS_SHOW_INCOMPLETE			:number = 13;	// 任务未完成显示用
		public static QUEST_STATUS_SHOW_END			:number = 16;	// 任务整个完成了, 显示用
		public static MAX_QUEST_STATUS			:number = 17;
		public static BOOK_STATUS_NONE			:number = 0;
		public static BOOK_STATUS_COMPLETE			:number = 1;	// 完成未领奖
		public static BOOK_STATUS_UNAVAILABLE			:number = 2;	// 得不到的，没空的，不能利用的
		public static BOOK_STATUS_INCOMPLETE			:number = 3;	// 不完全,未完成
		public static BOOK_STATUS_AVAILABLE			:number = 4;	// 有效，可接受
		public static BOOK_STATUS_FAILED			:number = 5;	// 失败
		public static BOOK_STATUS_REWARDED			:number = 6;	// 已领奖
		// 任务给予者状态
		public static DIALOG_STATUS_NONE			:number = 0;
		public static DIALOG_STATUS_UNAVAILABLE			:number = 1;	//  任务给予者状态,忙碌
		public static DIALOG_STATUS_CHAT			:number = 2;	//  对话,3.1 - may be changed
		public static DIALOG_STATUS_INCOMPLETE			:number = 5;	//   未完成
		public static DIALOG_STATUS_REWARD_REP			:number = 6;	//  可重复领取奖励
		public static DIALOG_STATUS_AVAILABLE_REP			:number = 7;	//  可重复接受任务
		public static DIALOG_STATUS_AVAILABLE			:number = 8;	//  有可接任务
		public static DIALOG_STATUS_REWARD2			:number = 9;	//  no yellow dot on minimap
		public static DIALOG_STATUS_REWARD			:number = 10;	//  报酬，报答，赏金,yellow dot on minimap
		public static MAX_DIALOG_STATUS			:number = 11;
		// 任务标志
		//  Flags used at server and sent to client	
		public static QUEST_FLAGS_COMMIT_NOT_NEED_NPC			:number = 256;	//  提交任务是否校验npc
		public static QUEST_FLAGS_ACCEPT_NOT_NEED_NPC			:number = 512;	//  接受任务是否校验npc
		public static QUEST_FLAGS_DAILY			:number = 1024;	// 日常任务 Used to know quest is Daily one
		public static QUEST_FLAGS_AUTO_FAIL_OFF			:number = 1;	// 离线或者死亡或者跨系列图传送后直接任务失败
		public static QUEST_FLAGS_AUTO_COMPLETE			:number = 16;	// auto complete	
		public static QUEST_FLAGS_AUTO_REWARDED			:number = 32;	// 自动奖励 These quests are automatically rewarded on quest complete and they will never appear in quest log client side.
		public static QUEST_FLAGS_AUTO_ACCEPT			:number = 64;	// quests in starting areas
		public static QUEST_FLAGS_MANUAL			:number = 128;	// 手动完成	
		public static QUEST_FLAGS_CANREMOVE			:number = 4096;	// 允许放弃
		//  Mangos flags for set SpecialFlags in DB if required but used only at server
		public static QUEST_FLAGS_FLAGS_REPEATABLE			:number = 65536;	// 可重复接受的 Set by 1 in SpecialFlags from DB
		public static QUEST_FLAGS_FLAGS_EXPLORATION_OR_EVENT			:number = 131072;	// Set by 2 in SpecialFlags from DB (if required area explore, spell SPELL_EFFECT_QUEST_COMPLETE casting, table `*_script` command SCRIPT_COMMAND_QUEST_EXPLORED use, set from script DLL)
		public static QUEST_FLAGS_FLAGS_DB_ALLOWED			:number = 65535;
		//  Mangos flags for internal use only
		public static QUEST_FLAGS_FLAGS_DELIVER			:number = 262144;	// Internal flag computed only,需要收集物品的
		public static QUEST_FLAGS_FLAGS_SPEAKTO			:number = 524288;	// Internal flag computed only,需要与NPC对话的
		public static QUEST_FLAGS_FLAGS_KILL_OR_CAST			:number = 1048576;	// Internal flag computed only,杀死怪物或者使用任务物品的
		public static QUEST_FLAGS_FLAGS_TIMED			:number = 2097152;	// 定时?Internal flag computed only
		public static QUEST_FLAGS_FLAGS_BUY_ITEM			:number = 4194304;	// 购买物品的任务
		public static QUEST_FLAGS_FLAGS_OPT_SYS			:number = 8388608;	// 操作系统的任务
		public static QUEST_FLAGS_FLAGS_LEVEL_CREATURE			:number = 16777216;	// 杀等级怪
		public static QUEST_FLAGS_FLAGS_LEVEL_PLAYER			:number = 33554432;	// 杀等级玩家
		public static QUEST_RELATION_TYPE_START			:number = 0;	// 待接任务
		public static QUEST_RELATION_TYPE_END			:number = 1;	// 待交任务
		// 任务更新操作
		public static QUEST_UNCHANGED			:number = 0;	// 未变化
		public static QUEST_CHANGED			:number = 1;	// 变化
		public static QUEST_NEW			:number = 2;
		public static MAX_ACHIEVE_COUNT			:number = 100;
		public static ACHIEVE_FIELD_REWARD			:number = 0;	// 0 是否已达成 1 是否已领奖 2 预留 3 预留
		public static ACHIEVE_FIELD_CURRENT			:number = 1;	// 成就进度
		public static MAX_ACHIEVE_FIELD			:number = 2;
		//  最多可领取任务个数
		public static MAX_QUEST_COUNT			:number = 50;
		//  最多可领取日常任务个数
		public static MAX_DAILY2_QUEST_COUNT			:number = 10;
		//  任务最多目标
		public static MAX_QUEST_TARGET_COUNT			:number = 5;
		public static QUEST_TARGET_INFO_SHORT0			:number = 0;	// 0:状态, 1:目标值
		public static QUEST_TARGET_INFO_PROCESS			:number = 1;	// 进度
		public static MAX_QUEST_TARGET_INFO_COUNT			:number = 2;
		public static QUEST_INFO_ID			:number = 0;	// 任务id, 任务状态
		public static QUEST_INFO_STEP_START			:number = 1;	// 任务目标开始
		public static QUEST_INFO_STEP_END			:number = 11;	// 任务目标结束
		public static MAX_QUEST_INFO_COUNT			:number = 11;
		public static MAX_TITLE_COUNT			:number = 100;
		public static TITLE_FIELD_INFO			:number = 0;	// 0 ID 1 保留 16位
		public static TITLE_FIELD_TIME			:number = 1;	// 称号失效时间
		public static MAX_TITLE_FIELD			:number = 2;
		public static WELFA_BACK_TYPE_COUNT			:number = 10;
		public static WELFA_BACK_ITEM			:number = 0;
		public static WELFA_BACK_ITEM_END			:number = 8;
		public static WELFA_BACK_ITEM_NUM			:number = 9;
		public static MAX_WELFA_BACK_ITEM			:number = 10;
		// 任务 成就 称号 福利 相关字段
		public static QUEST_FIELD_ACHIEVE_START			:number = 0;	// 成就开始
		public static QUEST_FIELD_ACHIEVE_END			:number = 200;	// 成就结束
		public static QUEST_FIELD_ACHIEVE_ALL			:number = 200;	// 总成就点
		public static QUEST_FIELD_ACHIEVE_REWARD			:number = 201;	// 成就点奖励ID
		public static QUEST_FIELD_QUEST_START			:number = 202;	// 任务开始
		public static QUEST_FIELD_QUEST_END			:number = 752;	// 任务结束
		public static QUEST_FIELD_TITLE_START			:number = 752;	// 称号开始
		public static QUEST_FIELD_TITLE_END			:number = 952;	// 称号结束
		public static QUEST_FIELD_WELFARE_SHOUCHONG			:number = 952;	// 是否领取首冲奖励
		public static QUEST_FIELD_WELFARE_CHECKIN			:number = 953;	// 每日签到奖励领取标记 用位表示
		public static QUEST_FIELD_WELFARE_CHECKIN_ALL			:number = 954;	// 累积签到奖励领取标记 用位表示
		public static QUEST_FIELD_WELFARE_LEVEL			:number = 955;	// 升级福利奖励
		public static QUEST_FIELD_WELFARE_BACK_START			:number = 956;
		public static QUEST_FIELD_WELFARE_BACK_END			:number = 1056;
		public static QUEST_FIELD_DAILY2_FINISHED			:number = 1056;	//  日常任务完成个数
		public static QUEST_FIELD_DAILY2_SUBMIT			:number = 1057;	//  日常任务是否提交
		public static QUEST_FIELD_DAILY2_QUEST_START			:number = 1058;	//  日常任务开始
		public static QUEST_FIELD_DAILY2_QUEST_END			:number = 1168;	// 日常任务结束
		public static QUEST_FIELD_WELFARE_RECHARGE_REWARD_FLAG			:number = 1168;	// 累计充值奖励领取标记
		public static QUEST_FIELD_WELFARE_CONSUME_REWARD_FLAG			:number = 1169;	// 累计充值奖励领取标记
		public static QUEST_FIELD_WELFARE_SEVEN_DAY_PROCESS			:number = 1170;	// 七日大礼 进度
		public static QUEST_FIELD_WELFARE_SEVEN_DAY_FLAG			:number = 1171;	// 七日大礼 领取状态
		// 战斗状态
		public static COMBAT_STATE_LEAVE			:number = 0;	// 脱离战斗
		public static COMBAT_STATE_ENTER			:number = 1;	// 进入战斗
		// 战斗状态
		public static UNIT_STAT_DIED			:number = 1;
		public static UNIT_STAT_MELEE_ATTACKING			:number = 2;	//  player is melee attacking someone
		public static UNIT_STAT_CAST_SPELL			:number = 4;	//  引导技能
		public static UNIT_STAT_SPELL_PROCESS			:number = 8;	// 持续施法
		public static UNIT_STAT_ROAMING			:number = 16;	// 漫游
		public static UNIT_STAT_CHASE			:number = 32;	// 追逐
		public static UNIT_STAT_SEARCHING			:number = 64;	// 搜索
		public static UNIT_STAT_FLEEING			:number = 128;	// 逃避
		public static UNIT_STAT_IN_FLIGHT			:number = 256;	//  player is in flight mode
		public static UNIT_STAT_FOLLOW			:number = 512;	// 跟随
		public static UNIT_STAT_ROOT			:number = 1024;	// 缠绕???
		public static UNIT_STAT_CONFUSED			:number = 2048;	// 使困惑
		public static UNIT_STAT_DISTRACTED			:number = 4096;	// 转移,使分心
		public static UNIT_STAT_ISOLATED			:number = 8192;	//  隔离,光环无法影响其他玩家 area auras do not affect other players
		public static UNIT_STAT_ATTACK_PLAYER			:number = 16384;	//  攻击
		public static UNIT_STAT_ALL_STATE			:number = 65535;	// (UNIT_STAT_STOPPED | UNIT_STAT_MOVING | UNIT_STAT_IN_COMBAT | UNIT_STAT_IN_FLIGHT)
		// 生存状态
		public static DEATH_STATE_ALIVE			:number = 0;	// 活着
		public static DEATH_STATE_CORPSE			:number = 1;	// 尸体，在客户端可见尸体
		public static DEATH_STATE_DEAD			:number = 2;	// 死亡，在客户端尸体消失
		// 击打信息，例如吸收，致命一击等等
		public static HITINFO_NORMALSWING			:number = 1;	// 普通
		public static HITINFO_CRITHIT			:number = 2;	// 暴击
		public static HITINFO_MISS			:number = 3;	// 躲避
		public static HITINFO_GEDANG			:number = 4;	// 格挡
		public static HITINFO_CRITICALHIT			:number = 5;	// 会心一击
		public static HITINFO_BLOWFLY			:number = 6;	// 击飞
		public static HITINFO_LIUXUE			:number = 7;	// 流血
		public static HITINFO_CURE			:number = 8;	// 治疗
		public static HITINFO_JUMP_EVA			:number = 9;	// 跳闪
		public static HITINFO_POISON			:number = 10;	// 毒
		public static HITINFO_ICE			:number = 11;	// 冰
		public static HITINFO_FANTANSHANGHAI			:number = 12;	// 反弹伤害
		// 移动状态
		public static MOVE_STATUS_STOP			:number = 0;
		public static MOVE_STATUS_RUN			:number = 1;
		// NPC标识
		// / Non Player Character flags
		public static UNIT_NPC_FLAG_NONE			:number = -1;
		public static UNIT_NPC_FLAG_GOSSIP			:number = 0;	//  100%闲聊NPC
		public static UNIT_NPC_FLAG_QUESTGIVER			:number = 1;	//  任务发布PCguessed, probably ok
		public static UNIT_NPC_FLAG_UNK1			:number = 2;	// 预留
		public static UNIT_NPC_FLAG_UNK2			:number = 3;
		public static UNIT_NPC_FLAG_TRAINER			:number = 4;	//  100%  训练师
		public static UNIT_NPC_FLAG_TRAINER_CLASS			:number = 5;	//  100%  职业训练师
		public static UNIT_NPC_FLAG_TRAINER_PROFESSION			:number = 6;	//  100%  自由职业训练师？
		public static UNIT_NPC_FLAG_VENDOR			:number = 7;	//  100%  买卖商人
		public static UNIT_NPC_FLAG_VENDOR_PROP			:number = 8;	//  100%, 道具
		public static UNIT_NPC_FLAG_VENDOR_WEAPON			:number = 9;	//  100%  武器
		public static UNIT_NPC_FLAG_VENDOR_POISON			:number = 10;	//  药品
		public static UNIT_NPC_FLAG_VENDOR_REAGENT			:number = 11;	//  100%  饰品
		public static UNIT_NPC_FLAG_VENDOR_EQUIPMENT			:number = 12;	//  100%  装备
		public static UNIT_NPC_FLAG_FLIGHTMASTER			:number = 13;	//  100% 飞行点管理员
		public static UNIT_NPC_FLAG_SPIRITHEALER			:number = 14;	//  guessed 复活Npc
		public static UNIT_NPC_FLAG_SPIRITGUIDE			:number = 15;	//  guessed 灵魂向导
		public static UNIT_NPC_FLAG_INNKEEPER			:number = 16;	//  100% 旅店老板
		public static UNIT_NPC_FLAG_WAREHOUSE			:number = 17;	//  100% 仓库
		public static UNIT_NPC_FLAG_PETITIONER			:number = 18;	//  100% 竞技场
		public static UNIT_NPC_FLAG_TABARDDESIGNER			:number = 19;	//  100%工会徽章设计NPC
		public static UNIT_NPC_FLAG_BATTLEMASTER			:number = 20;	//  100%战场管理员
		public static UNIT_NPC_FLAG_AUCTIONEER			:number = 21;	//  100%拍卖商
		public static UNIT_NPC_FLAG_STABLEMASTER			:number = 22;	//  100%马夫
		public static UNIT_NPC_FLAG_GUILD_BANKER			:number = 23;	//  公会银行cause client to send 997 opcode
		public static UNIT_NPC_FLAG_CHALLENGE			:number = 24;	//  神奇的挑战怪要变大变粗,UNIT_NPC_FLAG_GUARD
		public static UNIT_NPC_FLAG_ONE_ONE			:number = 25;	//  是否光棍怪,没钱，没精验，没装备，没次数
		// 所有固定的BUFF => buff id要与表buff_template的id对应
		public static BUFF_ONEPOINTFIVE_JINGYAN			:number = 101;	// 1.5倍经验丹
		public static BUFF_TOW_JINGYAN			:number = 102;	// 2倍经验丹
		public static BUFF_THREE_JINGYAN			:number = 103;	// 3倍经验丹
		public static BUFF_FIVE_JINGYAN			:number = 104;	// 5倍经验丹
		public static BUFF_FANTAN			:number = 105;	// 反弹
		public static BUFF_LIANJIE			:number = 106;	// 连接
		public static BUFF_BEILIANJIE			:number = 107;	// 被连接
		public static BUFF_GANGCI			:number = 108;	// 钢刺
		public static BUFF_DINGSHEN			:number = 109;	// 定身
		public static BUFF_YUNXUAN			:number = 110;	// 晕眩
		public static BUFF_YUNMIE_ELING			:number = 111;	// 陨灭（恶灵）
		public static BUFF_HUIFU_HUDUN			:number = 112;	// 恢复护盾
		public static BUFF_FANJI_HUDUN			:number = 113;	// 反击护盾
		public static BUFF_LINGXUE			:number = 114;	// 流血
		public static BUFF_ZHUOSHAO			:number = 115;	// 灼烧
		public static BUFF_JUDU			:number = 116;	// 剧毒
		public static BUFF_ZHONGDU			:number = 117;	// 中毒
		public static BUFF_BINGJIA			:number = 118;	// 冰甲
		public static BUFF_BINGDONG			:number = 119;	// 冰冻
		public static BUFF_BAOZHA_DILEI			:number = 120;	// 爆炸（地雷）
		public static BUFF_SHOUWEI_ZHAOHUAN			:number = 121;	// 守卫（召唤）
		public static BUFF_BIAOJI			:number = 122;	// 标记
		public static BUFF_KUANGBAO			:number = 123;	// 狂暴
		public static BUFF_JIANSU			:number = 124;	// 减速
		public static BUFF_CHENMO			:number = 125;	// 沉默
		public static BUFF_XUECHI			:number = 126;	// 血池
		public static BUFF_WAIGONGMIANYI			:number = 127;	// 外攻免疫
		public static BUFF_NEIGONGMIAN			:number = 128;	// 内攻免疫
		public static BUFF_WUDI			:number = 129;	// 无敌
		public static BUFF_ZHANSHEN_FUTI			:number = 130;	// 战神附体
		public static BUFF_JINGANG_BUHUAITI			:number = 131;	// 金刚不坏体
		public static BUFF_KUANGBEN			:number = 132;	// 狂奔
		public static BUFF_HUOBA			:number = 133;	// 火把
		public static BUFF_LINGTI			:number = 134;	// 灵体
		public static BUFF_HUANHUA_ZHU			:number = 135;	// 幻化成猪
		public static BUFF_HUANHUA_REN			:number = 136;	// 幻化成人
		public static BUFF_HUANHUA_GUI			:number = 137;	// 幻化成鬼
		public static BUFF_HUANHUA_XIAN			:number = 138;	// 幻化成仙
		public static BUFF_HUANHUA_XIULUO			:number = 139;	// 幻化成修罗
		public static BUFF_XIULUOLI			:number = 140;	// 修罗力
		public static BUFF_ZHENYING			:number = 141;	// 阵营
		public static BUFF_ZHANDOU_STATE			:number = 142;	// 战斗状态
		public static BUFF_JUMP_DOWN			:number = 144;	// 身轻
		public static BUFF_ANXIANG_SHUYING			:number = 145;	// 暗香疏影
		public static BUFF_ZHIKONG			:number = 146;	// 滞空
		public static BUFF_FUKONG			:number = 147;	// 浮空
		public static BUFF_JUMP_JUMP			:number = 143;	// 跳跃
		public static BUFF_NEW_PLAYER_PROTECTED			:number = 148;	// 新手保护
		public static BUFF_DEATH_PROTECTED			:number = 149;	// 死亡保护
		public static BUFF_INVINCIBLE			:number = 150;	// 无敌
		public static BUFF_INVISIBLE			:number = 151;	// 隐身
		public static BUFF_YINCHANG			:number = 152;	// 吟唱
		public static BUFF_ROAR			:number = 153;	// 狂吼
		public static BUFF_HEAL			:number = 200;	// 百分比回血
		public static BUFF_ATTACK			:number = 201;	// 攻击增强
		public static BUFF_ARMOR			:number = 202;	// 防御增强
		public static BUFF_CRIT			:number = 203;	// 暴击增强
		public static BUFF_ALLATTR			:number = 204;	// 全属性增强
		public static BUFF_DEFAULT_EFFECT_ID_JUMP_JUMP			:number = 1;	// 默认的跳跃buff的效果id
		public static BUFF_DEFAULT_EFFECT_ID_NEW_PLAYER_PROTECTED			:number = 2;	// 默认的新手保护buff的效果id
		public static BUFF_DEFAULT_EFFECT_ID_DEATH_PROTECTED			:number = 3;	// 默认的死亡保护buff的效果id
		public static MAX_2JI_SHIJIAN_UINT32			:number = 20;	// 红颜2级事件uint32
		public static MAX_HONGYAN_DATI_COUNT			:number = 10;	// 红颜最大答题次数
		// 红颜系统操作枚举
		public static HONGYAN_JIESHI_MEIREN			:number = 0;	// --结识美人
		public static HONGYAN_DIANZAN			:number = 1;	// --点赞
		public static HONGYAN_PINGJIA			:number = 2;	// --评价
		public static HONGYAN_SHIZHUANG_JIHUO			:number = 3;	// --时装激活
		public static HONGYAN_SHIZHUANG_CHUANDAI			:number = 4;	// --时装穿戴
		public static HONGYAN_XIANGCE_JIHUO			:number = 5;	// --相册激活
		public static HONGYAN_SHIJIAN_CHULI			:number = 6;	// --事件处理
		public static HONGYAN_CHUYOU			:number = 7;	// --出游
		public static HONGYAN_HUIFU_HUOLI			:number = 8;	// --恢复活力值
		public static HONGYAN_ADD_NEIWU_SHIJIAN			:number = 9;	// --增加内务事件
		// 红颜系统玩家属性
		public static HONGYAN_PLAYER_ATTRS_XIAYI			:number = 0;	// --侠义值
		public static HONGYAN_PLAYER_ATTRS_FENGLIU			:number = 1;	// --风流
		public static HONGYAN_PLAYER_ATTRS_MINGSHENG			:number = 2;	// --名声
		public static HONGYAN_PLAYER_ATTRS_WENTAO			:number = 3;	// --文韬
		public static HONGYAN_PLAYER_ATTRS_WULUE			:number = 4;	// --武略
		public static HONGYAN_PLAYER_ATTRS_CAIYI			:number = 5;	// --才艺
		public static HONGYAN_PLAYER_ATTRS_QINHE			:number = 6;	// --亲和
		public static HONGYAN_PLAYER_ATTRS_LIYI			:number = 7;	// --礼仪
		public static HONGYAN_PLAYER_ATTRS_XIANGMAO			:number = 8;	// --相貌
		public static HONGYAN_PLAYER_ATTRS_HUOLI			:number = 9;	// --活力
		public static MAX_PLAYER_ATTRS			:number = 10;
		// 红颜系统美人属性
		public static HONGYAN_MEIREN_ATTRS_JIESHI_BIT			:number = 0;	// 0:是否结识  1~31：结识条件
		public static HONGYAN_MEIREN_ATTRS_XINGGE_BIT			:number = 1;	// 性格
		public static HONGYAN_MEIREN_ATTRS_AIHAO_BIT			:number = 2;	// 爱好
		public static HONGYAN_MEIREN_ATTRS_CHANGJING_BIT			:number = 3;	// 场景
		public static HONGYAN_MEIREN_ATTRS_SHIZHUANG_BIT			:number = 4;	// 时装
		public static HONGYAN_MEIREN_QINMIDU_UINT16			:number = 5;	// 0：亲密度 1:当前穿戴的时装ID
		public static HONGYAN_MEIREN_XIANGCE_BIT			:number = 6;	// 美人激活的相册
		public static MAX_MEIREN_ATTRS_TYPE			:number = 7;
		// 红颜系统美人人气值
		public static HONGYAN_MEIREN_DIANZAN			:number = 0;	// 点赞
		public static HONGYAN_MEIREN_MEIHAO			:number = 1;	// 美貌
		public static HONGYAN_MEIREN_JIESHI_COUNT			:number = 2;	// 美人结识的玩家数量
		public static MAX_MEIREN_RENQI_TYPE			:number = 3;
		// 红颜系统美人表
		public static HONGYAN_CAIXUE			:number = 0;	// 采雪
		public static HONGYAN_ZHENFEI			:number = 1;	// 珍妃
		public static HONGYAN_YANLIN			:number = 2;	// 燕琳
		public static HONGYAN_MURONGYANYAN			:number = 3;	// 慕容嫣嫣
		public static HONGYAN_YAORU			:number = 4;	// 瑶如
		public static HONGYAN_XIANGJING			:number = 5;	// 项晶
		public static HONGYAN_HENGXIAOZHUO			:number = 6;	// 桓小卓
		public static HONGYAN_LIJI			:number = 7;	// 俪姬
		public static HONGYAN_SIQI			:number = 8;	// 思绮
		public static HONGYAN_YOUYOU			:number = 9;	// 幽幽
		public static HONGYAN_LINCHUER			:number = 10;	// 林楚儿
		public static HONGYAN_WANYAN_YUNNA			:number = 11;	// 完颜云娜
		public static HONGYAN_QUANHUIQIAO			:number = 12;	// 全慧乔
		public static HONGYAN_TUOBALVZHU			:number = 13;	// 拓跋绿珠
		public static HONGYAN_QINGYAN			:number = 14;	// 轻颜
		public static HONGYAN_SUOMOER			:number = 15;	// 索沫儿
		public static HONGYAN_GUQIANQIAN			:number = 16;	// 谷纤纤
		public static HONGYAN_AYIGULI			:number = 17;	// 阿依古丽
		public static HONGYAN_ZUOYUYI			:number = 18;	// 左玉怡
		public static HONGYAN_ZILUO			:number = 19;	// 紫罗
		public static HONGYAN_QUNUO			:number = 20;	// 曲诺
		public static HONGYAN_XUANYING			:number = 21;	// 玄樱
		public static MAX_MEIREN			:number = 32;
		// 所有GM命令的定义
		public static GM_COMMAND_NULL			:number = 0;	// 空命令
		public static GM_COMMAND_JIULONGCHAO			:number = 1;	// @天书世界
		public static GM_COMMAND_SUCAI			:number = 2;	// @素材
		public static GM_COMMAND_JIAOBEN			:number = 3;	// @脚本
		public static GM_COMMAND_TI			:number = 4;	// @踢
		public static GM_COMMAND_ZAIXIAN			:number = 5;	// @在线
		public static GM_COMMAND_DITURENSHU			:number = 6;	// @地图人数
		public static GM_COMMAND_ZHAOCAI			:number = 7;	// @招财
		public static GM_COMMAND_ZHIZAO			:number = 8;	// @制造
		public static GM_COMMAND_QINGLI			:number = 9;	// @清理
		public static GM_COMMAND_ZHUANGBEI			:number = 10;	// @装备
		public static GM_COMMAND_PAIHANGBANG			:number = 12;	// @排行榜
		public static GM_COMMAND_YOUJIAN			:number = 13;	// @邮件
		public static GM_COMMAND_BENGDIAO			:number = 15;	// @崩掉
		public static GM_COMMAND_BANGZHU			:number = 16;	// @帮助
		public static GM_COMMAND_GONGGAO			:number = 17;	// @公告
		public static GM_COMMAND_SHIJIETISHI			:number = 18;	// @世界提示
		public static GM_COMMAND_PAIDUI			:number = 19;	// @排队
		public static GM_COMMAND_PINGBICI			:number = 20;	// @屏蔽词
		public static GM_COMMAND_GUANBIFUWUQI			:number = 21;	// @关闭服务器
		public static GM_COMMAND_CHONGZHI			:number = 22;	// @充值
		public static GM_COMMAND_GUANBIDITU			:number = 23;	// @关闭地图
		public static GM_COMMAND_DENGJI			:number = 24;	// @等级
		public static GM_COMMAND_QINGLIRENWUWUPIN			:number = 25;	// @清理任务物品
		public static GM_COMMAND_QINGLIRENWU			:number = 26;	// @清理任务
		public static GM_COMMAND_WANCHENGRENWU			:number = 27;	// @完成任务
		public static GM_COMMAND_JIESHOURENWU			:number = 28;	// @接受任务
		public static GM_COMMAND_GANDIAO			:number = 29;	// @干掉
		public static GM_COMMAND_SHUAGUAI			:number = 30;	// @刷怪
		public static GM_COMMAND_CHUANSONG			:number = 31;	// @传送
		public static GM_COMMAND_XIAZOU			:number = 32;	// @瞎走
		public static GM_COMMAND_SUICIDE			:number = 33;	// @自爆
		public static GM_COMMAND_SERVER_INFO			:number = 34;	// @服务器
		public static GM_COMMAND_DB			:number = 35;	// @数据库
		public static GM_COMMAND_KAIFUSHIJIAN			:number = 36;	// @开服时间
		public static GM_COMMAND_TEST_SHUJU			:number = 37;	// @测试数据
		public static GM_COMMAND_UPDATE_SERVER			:number = 38;	// @更新服务器
		public static GM_COMMAND_RESESSION_OPTS			:number = 39;	// @协议注册
		public static GM_COMMAND_RENWUTIAOZHUAN			:number = 40;	// @任务跳转
		public static GM_COMMAND_BACKUP_DATA			:number = 41;	// @备份数据
		public static GM_COMMAND_RETURN_DATA			:number = 42;	// @回档数据
		public static GM_COMMAND_PRINT_OBJECT			:number = 43;	// @打印对象
		public static GM_COMMAND_TEST_HEFU			:number = 44;	// @测试合服
		public static GM_COMMAND_CLEAR_PAIHANGBANG			:number = 45;	// @清空排行榜
		public static GM_COMMAND_MEMORY_RECOVERY			:number = 46;	// @内存回收
		public static GM_COMMAND_PRINT_MAP			:number = 47;	// @打印地图
		public static GM_COMMAND_DEL_MAP_INFO			:number = 48;	// @清空地图信息
		public static GM_COMMAND_RESTORE_SYSTEM			:number = 49;	// @后台命令
		public static GM_COMMAND_CALL_REMOVE_ITEM			:number = 50;	// @清空物品监听
		public static GM_COMMAND_SUBLINE			:number = 51;	// @分线
		public static GM_COMMAND_CUSTOM			:number = 52;	// @CUSTOM
		public static GM_COMMAND_VIP			:number = 53;	// @VIP
		public static GM_COMMAND_SELF_KILL			:number = 54;	// @自杀
		// 查询玩家信息的时候，需要附带的信息
		public static QUERY_PLAYER_FLAG_BASE			:number = 0;	// 玩家基础信息
		public static QUERY_PLAYER_FLAG_NAME			:number = 1;	// 玩家姓名
		public static QUERY_PLAYER_FLAG_EQUIP			:number = 2;	// 玩家装备形象
		public static QUERY_PLAYER_FLAG_PIFENG			:number = 3;	// 披风信息
		public static QUERY_PLAYER_FLAG_FORCE			:number = 4;	// 玩家战斗力
		public static QUERY_PLAYER_FLAG_OTHER			:number = 5;	// 其它信息
		// 下面是非玩家下标的东西
		public static QUERY_PLAYER_FLAG_MOUNT			:number = 20;	// 所有坐骑
		public static QUERY_PLAYER_FLAG_EQUIP_BAG			:number = 21;	// 装备包裹
		public static QUERY_PLAYER_FLAG_MAIN_BAG			:number = 22;	// 背包包裹
		public static QUERY_PLAYER_FLAG_STORAGE_BAG			:number = 23;	// 仓库包裹
		public static QUERY_PLAYER_FLAG_STALL_BAG			:number = 24;	// 摊位包裹	
		// 任务类型定义
		public static QUEST_TYPE_MAIN			:number = 0;	// 主线任务
		public static QUEST_TYPE_EXTENSIONS			:number = 1;	// 支线任务
		public static QUEST_TYPE_ACTIVITY			:number = 2;	// 活动任务
		public static QUEST_TYPE_QIYU			:number = 3;	// 奇遇任务
		public static QUEST_TYPE_DAILY			:number = 4;	// 每日环任务
		public static QUEST_TYPE_DAILY2			:number = 5;	// 日常任务
		//  任务目标类型定义
		public static QUEST_TARGET_TYPE_PLAYER_LEVEL			:number = 1;	// 人物等级
		public static QUEST_TARGET_TYPE_PLAYER_FORCE			:number = 2;	// 人物战力
		public static QUEST_TARGET_TYPE_FACTION			:number = 3;	// 加入或创建家族
		public static QUEST_TARGET_TYPE_FACTION_DONATION			:number = 4;	// 捐赠
		public static QUEST_TARGET_TYPE_FACTION_ACTIVITY			:number = 5;	// 家族活动
		public static QUEST_TARGET_TYPE_FIELD_BOSS			:number = 6;	// 参加野外BOSS
		public static QUEST_TARGET_TYPE_WORLD_BOSS			:number = 7;	// 参加世界BOSS
		public static QUEST_TARGET_TYPE_RESOURCE_INSTANCE			:number = 8;	// 挑战资源副本
		public static QUEST_TARGET_TYPE_TRIAL_INSTANCE			:number = 9;	// 挑战试练副本
		public static QUEST_TARGET_TYPE_OWN_DIVINE			:number = 10;	// 获得任意神兵
		public static QUEST_TARGET_TYPE_EQUIP_DIVINE			:number = 11;	// 装备任意神兵
		public static QUEST_TARGET_TYPE_STRENGTH_DIVINE			:number = 12;	// 强化任意神兵
		public static QUEST_TARGET_TYPE_RAISE_SKILL			:number = 13;	// 升级技能
		public static QUEST_TARGET_TYPE_TRAIN_MOUNT			:number = 14;	// 培养坐骑
		public static QUEST_TARGET_TYPE_RAISE_MOUNT_SKILL			:number = 15;	// 升级坐骑任意技能
		public static QUEST_TARGET_TYPE_FRIEND_DONATION			:number = 16;	// 赠送好友礼物
		public static QUEST_TARGET_TYPE_STRENGTH_SUIT			:number = 17;	// 强化装备
		public static QUEST_TARGET_TYPE_STRENGTH_GEM			:number = 18;	// 强化宝石
		public static QUEST_TARGET_TYPE_TALK			:number = 19;	// 对话
		public static QUEST_TARGET_TYPE_PICK_GAME_OBJECT			:number = 20;	// 采集
		public static QUEST_TARGET_TYPE_CHECK_GAME_OBJECT			:number = 21;	// 检查
		public static QUEST_TARGET_TYPE_KILL_MONSTER			:number = 22;	// 击杀怪物
		public static QUEST_TARGET_TYPE_USE_ITEM			:number = 23;	// 使用物品
		public static QUEST_TARGET_TYPE_SUIT			:number = 24;	// 进行穿戴装备
		public static QUEST_TARGET_TYPE_MOUNT_LEVEL			:number = 25;	// 坐骑达到x
		public static QUEST_TARGET_TYPE_FRIEND_NUM			:number = 26;	// 拥有好友x
		public static QUEST_TARGET_TYPE_KILL_MONSTER_NUM			:number = 27;	// 击杀怪物x
		public static QUEST_TARGET_TYPE_DIVINE_NUM			:number = 28;	// 拥有神兵x
		public static QUEST_TARGET_TYPE_DIVINE_LEV			:number = 29;	// 神兵等级x
		public static QUEST_TARGET_TYPE_DOUJIANTAI			:number = 30;	// 斗剑台胜利x
		public static QUEST_TARGET_TYPE_TITLE_NUMBER			:number = 31;	// 称号数量达到x个
		public static QUEST_TARGET_TYPE_FASHION_NUMBER			:number = 32;	// 时装数量达到x个
		public static QUEST_TARGET_TYPE_ACHIEVE			:number = 40;	// 成就点数达到X点
		public static QUEST_TARGET_TYPE_SUIT_TITLE			:number = 41;	// 佩戴X称号
		public static QUEST_TARGET_TYPE_SUIT_FASHION			:number = 42;	// 穿上时装X
		public static QUEST_TARGET_TYPE_JOIN_DOUJIANTAI			:number = 43;	// 参与X次斗剑台
		public static QUEST_TARGET_TYPE_JOIN_KUAFU_3V3			:number = 44;	// 参与X次3V3
		public static QUEST_TARGET_TYPE_WIN_KUAFU_3V3			:number = 45;	// 3v3获胜x次
		public static QUEST_TARGET_TYPE_JOIN_XIANFU			:number = 46;	// 参与X次仙府夺宝
		public static QUEST_TARGET_TYPE_WIN_XIANFU			:number = 47;	// 仙府夺宝获胜X次
		public static QUEST_TARGET_TYPE_KILL_MONSTER_COLLECT			:number = 48;	// 杀怪收集物品
		public static QUEST_TARGET_TYPE_TURN_ITEM_IN			:number = 49;	// 上交物品
		public static QUEST_TARGET_TYPE_PASS_WORLD_RISK			:number = 50;	// 世界冒险通关
		public static QUEST_TARGET_TYPE_SMELT			:number = 51;	// 熔炼装备
		public static QUEST_TARGET_TYPE_CONTRIBUTE_TIMES			:number = 52;	// 为女王贡献次数
		public static QUEST_TARGET_TYPE_CONTRIBUTE_TOTAL_TIMES			:number = 53;	// 为女王贡献总次数
		public static QUEST_TARGET_TYPE_CONTRIBUTE_CHARM			:number = 54;	// 为女王贡献魅力值
		public static QUEST_TARGET_TYPE_CONTRIBUTE_ITEM			:number = 55;	// 为女王贡献道具
		public static QUEST_TARGET_TYPE_LOOT_ITEM			:number = 56;	// 收集某些道具
		public static QUEST_TARGET_TYPE_SINGLE_THX_TIMES			:number = 57;	// 女王单任务感谢次数
		public static QUEST_TARGET_TYPE_TOTAL_THX_TIMES			:number = 58;	// 女王累计感谢次数
		public static QUEST_TARGET_TYPE_WINGS_UPGRADE_LEVEL			:number = 59;	// 翅膀进阶等级达到X
		public static QUEST_TARGET_TYPE_WINGS_UPDRADE_TIMES			:number = 60;	// 翅膀进阶升级X次
		public static QUEST_TARGET_TYPE_WINGS_STRENGTH_LEVEL			:number = 61;	// 翅膀强化等级达到X
		public static QUEST_TARGET_TYPE_WINGS_STRENGTH_TIMES			:number = 62;	// 翅膀强化升级X次
		public static QUEST_TARGET_TYPE_TALISMAN_LEVEL			:number = 63;	// 升级任意法宝到X级
		public static QUEST_TARGET_TYPE_MOUNT_STRENGTH_LEVEL			:number = 64;	// 坐骑强化等级达到X
		public static QUEST_TARGET_TYPE_REFINE_SUIT			:number = 65;	// 指定槽位装备精炼x次
		public static QUEST_TARGET_TYPE_WASH_SUIT			:number = 66;	// 指定槽位装备洗炼x次
		public static QUEST_TARGET_TYPE_MERIDIAN_LEVEL			:number = 67;	// 经脉升到X级
		public static QUEST_TARGET_TYPE_JOIN_SINGLE_PVP			:number = 68;	// 参加排位赛X次
		public static QUEST_TARGET_TYPE_SINGLE_PVP_WINS			:number = 69;	// 排位赛胜利X次
		public static QUEST_TARGET_TYPE_ACTIVE_TASK			:number = 70;	// 完成X个活跃任务
		public static QUEST_TARGET_TYPE_DAILY_TASK			:number = 71;	// 完成X轮日常任务
		public static QUEST_TARGET_TYPE_GEM_TOTAL_LEVEL			:number = 72;	// 所有宝石总等级升到X级
		public static QUEST_TARGET_TYPE_WINGS_BLESS_TIMES			:number = 73;	// 翅膀祝福X次
		// 货币处理类型
		public static CURRENCY_HANDLE_TYPE_ADD			:number = 0;	// 增加
		public static CURRENCY_HANDLE_TYPE_SUB			:number = 1;	// 减少
		// 技能有效时间技能ID枚举
		public static SPELL_VALID_TIME_POTIAN_2			:number = 0;	// 破天二式
		public static SPELL_VALID_TIME_POTIAN_3			:number = 1;	// 破天三式
		public static SPELL_VALID_TIME_YUNFEI_2			:number = 2;	// 云飞玉皇·二段
		public static SPELL_VALID_TIME_YUNFEI_3			:number = 3;	// 云飞玉皇·三段
		public static SPELL_VALID_TIME_FENGFAN_2			:number = 4;	// 风翻云变·二段
		public static SPELL_VALID_TIME_ZHUXIAN_2			:number = 5;	// 诛仙剑阵·二段
		public static SPELL_VALID_TIME_ZHUXIAN_3			:number = 6;	// 诛仙剑阵·三段
		public static MAX_SPELL_VALID			:number = 15;
		public static MAX_SPELL_SLOT			:number = 6;
		public static NOMAL_ATTACK_TIME			:number = 1300;
		public static NOMAL_MOVE_SPEED			:number = 130;
		public static MAX_ITEM_SPELL			:number = 3;
		public static MAX_BASE_ATTR_FIELD_COUNT			:number = 15;	// 附加属性最大条数
		public static MAX_BUFF			:number = 50;	// 玩家身上最大buff数
		public static MAX_UNIT_BUFF			:number = 16;	// 精灵身上最大buff数
		// 装备类型包括时装 从头到脚
		// 普通装备
		public static EQUIPMENT_TYPE_OTHER			:number = 0;	// 其他
		public static EQUIPMENT_TYPE_MAIN_WEAPON			:number = 1;	// 武器
		public static EQUIPMENT_TYPE_COAT			:number = 2;	// 衣服
		public static EQUIPMENT_TYPE_LEG			:number = 3;	// 护腕
		public static EQUIPMENT_TYPE_BELT			:number = 4;	// 腰带
		public static EQUIPMENT_TYPE_SHOES			:number = 5;	// 鞋子
		public static EQUIPMENT_TYPE_HELMET			:number = 6;	// 头盔
		public static EQUIPMENT_TYPE_NECKLACE			:number = 7;	// 项链
		public static EQUIPMENT_TYPE_PANTS			:number = 8;	// 裤子
		public static EQUIPMENT_TYPE_LRING			:number = 9;	// 左戒指
		public static EQUIPMENT_TYPE_BRACELET			:number = 10;	// 玉佩
		public static EQUIPMENT_TYPE_CLOAK			:number = 11;	// 披风
		public static EQUIPMENT_TYPE_RRING			:number = 12;	// 右戒指
		public static EQUIPMENT_TYPE_FASHION			:number = 13;	// 时装
		public static EQUIPMENT_TYPE_RESERVE3			:number = 14;	// 预留
		public static EQUIPMENT_TYPE_RESERVE4			:number = 15;	// 预留
		public static EQUIPMENT_TYPE_RESERVE5			:number = 16;	// 预留
		public static EQUIPMENT_TYPE_RESERVE6			:number = 17;	// 预留
		public static EQUIPMENT_TYPE_RESERVE7			:number = 18;	// 预留
		public static EQUIPMENT_TYPE_RESERVE8			:number = 19;	// 预留
		public static EQUIPMENT_TYPE_MAX_POS			:number = 20;	// 最大位置
		// 时装类型接在普通装备后面 从头到脚
		public static FASHION_TYPE_MAIN_WEAPON			:number = 20;	// 头盔 预留
		public static FASHION_TYPE_HELMET			:number = 21;	// 耳坠
		public static FASHION_TYPE_COAT			:number = 22;	// 项链
		public static FASHION_TYPE_BELT			:number = 23;	// 披风
		public static FASHION_TYPE_LEG			:number = 24;	// 护肩 预留
		public static FASHION_TYPE_PANTS			:number = 25;	// 衣服
		public static FASHION_TYPE_SHOES			:number = 26;	// 主手武器
		public static FASHION_TYPE_BRACELET			:number = 27;	// 副手武器
		public static FASHION_TYPE_NECKLACE			:number = 28;	// 手镯 
		public static FASHION_TYPE_RING			:number = 29;	// 腰带
		public static FASHION_TYPE_CLOAK			:number = 30;	// 护手
		public static FASHION_TYPE_RESERVE1			:number = 31;	// 裤子 预留
		public static FASHION_TYPE_RESERVE2			:number = 32;	// 鞋子 预留
		public static FASHION_TYPE_RESERVE3			:number = 33;	// 特殊武器时装,现作为无双方天戟下标
		public static FASHION_TYPE_RESERVE4			:number = 34;	// 指环
		public static FASHION_TYPE_RESERVE5			:number = 35;	// 玉玺
		public static FASHION_TYPE_RESERVE6			:number = 36;	// 结婚戒指
		public static FASHION_TYPE_RESERVE7			:number = 37;	// 护符左
		public static FASHION_TYPE_RESERVE8			:number = 38;	// 护符右
		public static FASHION_TYPE_RESERVE9			:number = 39;	// 预留
		public static MAX_EQUIPMENT_TYPE			:number = 40;	// 最多可装备位置
		// 武器类型
		public static WEAPON_POS_MAIN			:number = 0;	// 主手
		public static WEAPON_POS_OFF			:number = 1;	// 副手
		public static WEAPON_POS_SINGLE_HAND			:number = 2;	// 单手
		public static WEAPON_POS_BOTH_HANDS			:number = 3;	// 双手
		public static MAX_WEAPON_POS			:number = 4;	// 不是武器
		// 能量类型,用于消耗
		public static POWER_MANA			:number = 0;	// 蓝,内力	
		public static POWER_ENERGY			:number = 1;	// 能量,体力	
		public static MAX_POWERS			:number = 2;
		// 战斗计算过程中的各种百分比
		public static COMBAT_RATE_CRIT			:number = 0;	// 暴击率
		public static COMBAT_RATE_EVA			:number = 1;	// 闪避率
		public static MAX_COMBAT_RATE			:number = 2;
		// 包裹类型
		public static BAG_TYPE_MAIN_BAG			:number = 0;	// 主包裹
		public static BAG_TYPE_EQUIP			:number = 1;	// 穿戴的装备包裹
		public static BAG_TYPE_EQUIP_BAG			:number = 2;	// 放装备的包裹
		public static BAG_TYPE_GEM			:number = 3;	// 消耗品的包裹
		public static BAG_TYPE_GEM_BAG			:number = 4;	// 放宝石的包裹
		public static MAX_BAG			:number = 20;	// 预留20个
		// 背包扩展类型
		public static BAG_EXTENSION_TYPE_AUTO			:number = 0;	// 自动开启
		public static BAG_EXTENSION_TYPE_GOLD			:number = 1;	// 元宝开启
		// 安全码修改类型
		public static SAFETY_CODE_MODIFY_TYPE_CODE			:number = 0;	// 密码修改
		public static SAFETY_CODE_MODIFY_TYPE_QUESTION			:number = 1;	// 安全问题修改
		//  资源类道具
		public static Item_Loot_Gold_Ingot			:number = 1;	// 元宝
		public static Item_Loot_Bind_Gold			:number = 2;	// 绑定元宝
		public static Item_Loot_Silver			:number = 3;	// 银币
		public static Item_Loot_Renown			:number = 5;	// 声望
		public static Item_Loot_Honor			:number = 6;	// 荣誉
		public static Item_Loot_Exploit			:number = 7;	// 功勋
		public static Item_Loot_Contrib			:number = 8;	// 家族贡献
		public static Item_Loot_Exp			:number = 104;	// 经验
		public static Item_Loot_Mount_Exp			:number = 10;	// 坐骑经验
		public static Item_Loot_QI			:number = 13;	// 真气
		public static Item_Loot_BEAST			:number = 14;	// 兽灵
		public static Item_Loot_GEM			:number = 15;	// 宝石精华
		// 货币类型
		public static MONEY_TYPE_GOLD_INGOT			:number = 1;	// 元宝
		public static MONEY_TYPE_BIND_GOLD			:number = 2;	// 绑定元宝
		public static MONEY_TYPE_SILVER			:number = 3;	// 身上的银子
		public static MONEY_TYPE_SILVER_WAREHOUSE			:number = 4;	// 仓库的银子
		public static MAX_MONEY_TYPE			:number = 22;
		// 基本属性
		public static BASE_ATTR_HP			:number = 0;	// 生命
		public static BASE_ATTR_DAMAGE			:number = 1;	// 攻击
		public static BASE_ATTR_ARMOR			:number = 2;	// 防御
		public static BASE_ATTR_HIT			:number = 3;	// 命中
		public static BASE_ATTR_DODGE			:number = 4;	// 闪避
		public static BASE_ATTR_CRIT			:number = 5;	// 暴击
		public static BASE_ATTR_CRIT_RESIST			:number = 6;	// 坚韧
		public static BASE_MOVE_SPEED			:number = 7;	// 移速
		public static BASE_ATTACK_SPEED			:number = 8;	// 攻速
		public static MAX_BASE_ATTR			:number = 9;
		// 应用服计算出来的属性枚举
		// 0用来当做无属性 约定基本属性放在枚举的最后面
		public static EQUIP_ATTR_NONE			:number = 0;	// 空属性
		public static EQUIP_ATTR_MAX_HEALTH			:number = 1;	// 最大生命
		public static EQUIP_ATTR_DAMAGE			:number = 2;	// 攻击力
		public static EQUIP_ATTR_ARMOR			:number = 3;	// 防御力
		public static EQUIP_ATTR_HIT			:number = 4;	// 命中
		public static EQUIP_ATTR_MISS			:number = 5;	// 闪避
		public static EQUIP_ATTR_CRIT			:number = 6;	// 暴击
		public static EQUIP_ATTR_TOUGH			:number = 7;	// 坚韧
		public static EQUIP_ATTR_ATTACK_SPEED			:number = 8;	// 攻击速度
		public static EQUIP_ATTR_MOVE_SPEED			:number = 9;	// 移动速度
		public static EQUIP_ATTR_IGNORE_ARMOR			:number = 10;	// 忽视防御
		public static EQUIP_ATTR_IGNORE_MISS			:number = 11;	// 忽视闪避
		public static EQUIP_ATTR_RECOVERY			:number = 12;	// 生命值回复
		public static EQUIP_ATTR_DAMAGE_AMPLIFY_RATE			:number = 13;	// 伤害加深(万分比)
		public static EQUIP_ATTR_DAMAGE_RESIST_RATE			:number = 14;	// 伤害减免(万分比)
		public static EQUIP_ATTR_DAMAGE_RETURN_RATE			:number = 15;	// 反弹伤害(万分比)
		public static EQUIP_ATTR_VAMPIRIC_RATE			:number = 16;	// 吸血光环(万分比)
		public static EQUIP_ATTR_RECOVERY_RATE			:number = 17;	// 回复效率(万分比)
		public static EQUIP_ATTR_CRIT_RATE			:number = 18;	// 暴击率(万分比)
		public static EQUIP_ATTR_CRIT_RESIST_RATE			:number = 19;	// 抗暴率(万分比)
		public static EQUIP_ATTR_CRIT_DAM_RATE			:number = 20;	// 暴击伤害倍数(万分比)
		public static EQUIP_ATTR_CRIT_RESIST_DAM_RATE			:number = 21;	// 降暴伤害倍数(万分比)
		public static EQUIP_ATTR_HIT_RATE			:number = 22;	// 命中率(万分比)
		public static EQUIP_ATTR_MISS_RATE			:number = 23;	// 闪避率(万分比)
		public static EQUIP_ATTR_STUN_RATE			:number = 24;	// 眩晕
		public static EQUIP_ATTR_ROOTS_RATE			:number = 25;	// 定身
		public static EQUIP_ATTR_SILENCE_RATE			:number = 26;	// 沉默
		public static EQUIP_ATTR_CHAOS_RATE			:number = 27;	// 混乱
		public static EQUIP_ATTR_CHARM_RATE			:number = 28;	// 魅惑
		public static EQUIP_ATTR_CONTROL_ENHANCE_RATE			:number = 29;	// 控制增强
		public static EQUIP_ATTR_CONTROL_RESIST_RATE			:number = 30;	// 控制减免
		public static EQUIP_ATTR_STRENGTH_ARMOR			:number = 31;	// 强化护甲
		public static MAX_EQUIP_ATTR			:number = 32;
		// 物品其他属性枚举（物品特殊属性接在MAX_EQUIP_ATTR后面）
		public static ITEM_OTHER_ATTR_FAIL_TIME			:number = 32;	// 失效时间
		public static ITEM_OTHER_ATTR_STRONG_LV			:number = 33;	// 强化等级
		public static ITEM_OTHER_ATTR_STRONG_FAIL_COUNT			:number = 34;	// 强化失败次数
		public static ITEM_OTHER_ATTR_FORCE			:number = 35;	// 战斗力
		// 技能族公共CD类型
		public static SPELL_CD_BASE			:number = 0;
		public static SPELL_CD_SPECIAL			:number = 1;
		public static MAX_SPELL_CD_TYPE			:number = 2;
		// 任务槽 偏移量
		public static QUEST_ID_OFFSET			:number = 0;
		public static QUEST_STATE_OFFSET			:number = 1;
		public static QUEST_COUNTS_OFFSET			:number = 2;
		public static QUEST_COUNTS_OFFSET_1			:number = 3;
		public static QUEST_COUNTS_OFFSET_2			:number = 4;
		public static QUEST_COUNTS_OFFSET_3			:number = 5;
		public static QUEST_TIME_OFFSET			:number = 6;
		public static QUEST_FLAG_OFFSET			:number = 7;	// bit标志位 看定义QuestSlotFlags
		public static MAX_QUEST_OFFSET			:number = 8;
		public static QUEST_SLOT_FLAGS_REWARD			:number = 0;	// 是否领取过任务奖励
		public static QUEST_SLOT_FLAGS_EXPLORE			:number = 1;	// 是否已探索
		public static MAX_QUEST_LOG_SIZE			:number = 32;	// 任务槽的上限
		public static QUEST_OBJECTIVES_COUNT			:number = 8;	// 物品数量或杀死生物的数量上限
		public static QUEST_REWARD_CHOICES_COUNT			:number = 6;
		public static QUEST_REWARDS_COUNT			:number = 4;
		public static QUEST_LOW_LEVEL_HIDE_DIFF			:number = 4;
		public static QUEST_ITEMS_COUNTS			:number = 10;	// 任务物品最大容量
		public static QUEST_COMPLETE_LIST			:number = 200;	// 任务已完成列表的长度
		public static BINLOG_STRING_FIELD_GUID			:number = 0;	// 所有binlog的guid位置
		public static BINLOG_STRING_FIELD_NAME			:number = 1;	// 所有binlog的name位置
		public static BINLOG_STRING_FIELD_VERSION			:number = 2;	// 所有binlog的版本信息位置
		public static BINLOG_STRING_FIELD_OWNER			:number = 3;	// 所有binlog的owner位置
		// 战利品下标
		public static LOOT_PUBLIC_INT_START_POS			:number = 0;	// grid开始坐标
		public static LOOT_PUBLIC_INT_END_POS			:number = 1;	// grid结束坐标
		public static LOOT_PUBLIC_INT_BEGIN			:number = 2;	// 战利品真正开始的下标
		public static LOOT_PUBLIC_INT_ENTRY			:number = 0;	// 战利品模板
		public static LOOT_PUBLIC_INT_MONEY_SUM			:number = 1;	// 金钱数量
		public static MAX_LOOT_PUBLIC_INT_FIELD			:number = 2;
		public static LOOT_PUBLIC_STR_OWNER			:number = 0;
		public static MAX_LOOT_PUBLIC_STR_FIELD			:number = 1;
		public static LOOT_PRIVATE_INT_FAIL_TIME			:number = 0;	// 拾取以后的物品失效时间
		public static LOOT_PRIVATE_INT_EXIST_TIME			:number = 1;	// 战利品存活时间
		public static LOOT_PRIVATE_INT_OWNER_TIME			:number = 2;	// 战利品拥有者保护时间
		public static LOOT_PRIVATE_INT_FLAG			:number = 3;	// 标志位
		public static MAX_LOOT_PRIVATE_INT_FIELD			:number = 4;
		public static LOOT_PRIVATE_STRING_CREATE_BY			:number = 0;	// 战利品掉落怪GUID
		public static LOOT_PRIVATE_STRING_CREATE_NAME			:number = 1;	// 战利品掉落怪名称
		public static MAX_LOOT_PRIVATE_STRING			:number = 2;
		public static LOOT_STR_FIELD_BEGIN			:number = 4;	// 战利品字符串开始下标
		// 战利品标志位
		public static LOOT_FLAG_GET_ITEM_NOTICE			:number = 0;	// 拾起物品是否需要公告
		public static LOOT_FLAG_ITEM_BIND			:number = 1;	// 战利品是否绑定
		public static PLAYER_PASSIVE_SPELL_MAX_COUNT			:number = 100;	//  被动技能个数
		// 玩家能否做某事的flag偏移定义
		public static UNIT_CANDO_OFFSET_TYPE_CANT_CAST			:number = 0;	// 限制施法
		public static UNIT_CANDO_OFFSET_TYPE_CANT_MOVE			:number = 1;	// 限制移动
		public static UNIT_FIELD_BYTE_0			:number = 0;	// 0:类型ID，1：死亡状态，2：移动速度，3：八卦阵等级
		public static UNIT_FIELD_BYTE_1			:number = 1;	// 0：角色类型，1：阵营，2：种族，3：职业
		public static UNIT_FIELD_BYTE_2			:number = 2;	// 0：灰名时间，1：付费等级，2：免费复活，3：玩家称号
		public static UNIT_FIELD_BYTE_3			:number = 3;	// 0: 头像，1：发型，2：GM等级，3：下次复活是否有保护buff
		public static UNIT_FIELD_BYTE_4			:number = 4;	// 0：预留，1：当前坐骑模板id，2：皮肤类型 3：预留
		public static UNIT_FIELD_MOUNT_LEVEL			:number = 5;	// 4个bytes(0:当前坐骑阶数 1:当前坐骑星级,2:当前坐骑是否骑乘，3:当前幻化id)
		public static UNIT_FIELD_DIVINE_ID			:number = 6;	// 神兵id
		public static UNIT_FIELD_UINT16_0			:number = 7;	// 0：精灵模板，1：精灵等级
		public static UNIT_FIELD_UINT16_1			:number = 8;	// 0：地图ID，1：跨服1v1连胜次数
		public static UNIT_FIELD_UINT16_2			:number = 9;	// 0:玩家报名跨服时收到匹配信息中给的编号 1:身上宝物采集阵营编号
		public static UNIT_FIELD_SELF_DEFENSE_GUID			:number = 10;	// 自卫模式下可以攻击的玩家intguid
		public static UNIT_FIELD_FLAGS			:number = 11;	// 精灵身上的标志位
		public static GO_FIELD_FLAGS			:number = 12;	// 游戏对象的一些标识位
		public static GO_FIELD_DATA			:number = 13;	// 动态数据字段,目前保留为4个int
		public static UNIT_FIELD_NPC_FLAG			:number = 17;	// NPC标识
		public static UNIT_FIELD_INSTANCE_ID			:number = 18;	// 地图实例ID
		public static UNIT_FIELD_EQUIPMENT_COAT			:number = 19;	// 上衣模板
		public static UNIT_FIELD_EQUIPMENT_MAIN_WEAPON			:number = 20;	// 主手武器
		public static UNIT_FIELD_BUFF			:number = 21;	// BUFFID
		// 注意了：创建包需要下发的下标放在 UNIT_FIELD_BUFF前面,UNIT_FIELD_BUFF_TM后面的下标走订阅
		public static UNIT_FIELD_BUFF_TM			:number = 29;	// BUFF时间（掩码从这开始）
		public static UNIT_FIELD_BUFF_RESERVE			:number = 37;	// BUFF预留值
		public static UNIT_FIELD_BUFF_EFFECT_ID			:number = 53;	// BUFF效果id
		public static UNIT_FIELD_BUFF_CASTER_GUID			:number = 69;	// buff施法者guid
		public static UNIT_FIELD_FORCE			:number = 85;	// 战斗力
		public static UNIT_FIELD_HEALTH			:number = 87;	// 当前生命	
		public static UNIT_FIELD_MAX_HEALTH			:number = 88;	// 最大生命
		public static UNIT_FIELD_DAMAGE			:number = 89;	// 攻击力
		public static UNIT_FIELD_ARMOR			:number = 90;	// 防御力
		public static UNIT_FIELD_HIT			:number = 91;	// 命中
		public static UNIT_FIELD_MISS			:number = 92;	// 闪避
		public static UNIT_FIELD_CRIT			:number = 93;	// 暴击
		public static UNIT_FIELD_TOUGH			:number = 94;	// 坚韧
		public static UNIT_FIELD_ATTACK_SPEED			:number = 95;	// 攻击速度
		public static UNIT_FIELD_MOVE_SPEED			:number = 96;	// 移动速度
		public static UNIT_FIELD_IGNORE_ARMOR			:number = 97;	// 忽视防御
		public static UNIT_FIELD_IGNORE_MISS			:number = 98;	// 忽视闪避
		public static UNIT_FIELD_RECOVERY			:number = 99;	// 生命值回复
		public static UNIT_FIELD_DAMAGE_AMPLIFY_RATE			:number = 100;	// 伤害加深(万分比)
		public static UNIT_FIELD_DAMAGE_RESIST_RATE			:number = 101;	// 伤害减免(万分比)
		public static UNIT_FIELD_DAMAGE_RETURN_RATE			:number = 102;	// 反弹伤害(万分比)
		public static UNIT_FIELD_VAMPIRIC_RATE			:number = 103;	// 吸血光环(万分比)
		public static UNIT_FIELD_RECOVERY_RATE			:number = 104;	// 回复效率(万分比)
		public static UNIT_FIELD_CRIT_RATE			:number = 105;	// 暴击率(万分比)
		public static UNIT_FIELD_CRIT_RESIST_RATE			:number = 106;	// 抗暴率(万分比)
		public static UNIT_FIELD_CRIT_DAM_RATE			:number = 107;	// 暴击伤害倍数(万分比)
		public static UNIT_FIELD_CRIT_RESIST_DAM_RATE			:number = 108;	// 降暴伤害倍数(万分比)
		public static UNIT_FIELD_HIT_RATE			:number = 109;	// 命中率(万分比)
		public static UNIT_FIELD_MISS_RATE			:number = 110;	// 闪避率(万分比)
		public static UNIT_FIELD_STUN_RATE			:number = 111;	// 眩晕
		public static UNIT_FIELD_ROOTS_RATE			:number = 112;	// 定身
		public static UNIT_FIELD_SILENCE_RATE			:number = 113;	// 沉默
		public static UNIT_FIELD_CHAOS_RATE			:number = 114;	// 混乱
		public static UNIT_FIELD_CHARM_RATE			:number = 115;	// 魅惑
		public static UNIT_FIELD_CONTROL_ENHANCE_RATE			:number = 116;	// 控制增强
		public static UNIT_FIELD_CONTROL_RESIST_RATE			:number = 117;	// 控制减免
		public static UNIT_FIELD_STRENGTH_ARMOR			:number = 118;	// 强化护甲
		public static UNIT_FIELD_ATTRIBUTE_END			:number = 119;	//  属性结束
		public static UNIT_FIELD_ANGER			:number = 119;	// 愤怒值
		public static UNIT_FIELD_USE_RESPAWN_MAPID			:number = 120;	// 使用复活丹的地图id
		public static UNIT_FIELD_PROCESS_TIME			:number = 121;	//  进度条读完的时间戳
		public static UNIT_FIELD_PROCESS_SECONDS			:number = 122;	//  读条总共需要时间	
		public static UINT_FIELD_BOSS_DATA			:number = 123;	// boss数据byte 0:boss状态 1:boss前一状态 2:boss索引(云游的是这个用途)
		public static UINT_FIELD_BOSS_DATA1			:number = 124;	// boss数据byte 0:当前坐标x 1:当前坐标y 2:下一坐标x 3:下一坐标y(云游的是这个用途)
		public static UINT_FIELD_VIEW_MODE			:number = 124;	// 是否是观看模式
		public static UINT_FIELD_VIRTUAL_CAMP			:number = 125;	// 虚拟阵营
		public static UINT_FIELD_XIANFU_INFO			:number = 126;	// 跨服仙府的信息4bytes (0:宝箱数量, 1:死亡次数)
		public static UINT_FIELD_VIP_LEVEL			:number = 127;	// VIP等级
		public static UINT_FIELD_VIP_TIME_OUT			:number = 128;	// VIP超时时间
		public static UINT_FIELD_VAMPIRIC			:number = 129;	// 当前战斗的吸血值
		public static UINT_INT_FIELD_ILLUSION			:number = 131;	// 角色幻化
		public static UINT_FIELD_BOOS_CUR_SPELLID			:number = 132;	// 当前正在释放的蓄力技能idUNIT_INT_FIELD_APPEARANCE
		public static UINT_FIELD_BOOS_CUR_SPELL_TIME			:number = 133;	// 前一个技能结束的时间戳
		public static UINT_FIELD_BOOS_CUR_SPELL_LAST_COUNT			:number = 134;	//  持续技能数量
		public static UINT_INT_FIELD_PASSIVE_SPELL_START			:number = 135;	// 被动技能开始
		public static UINT_INT_FIELD_PASSIVE_SPELL_END			:number = 235;	// 被动技能结束
		public static UINT_INT_FIELD_WINGS_RANK			:number = 235;	// 神羽阶数
		public static UNIT_INT_FIELD_APPEARANCE			:number = 236;	//  外观
		public static MAX_UNIT_FIELD			:number = 237;
		public static GO_STRING_FIELD_CREATED_BY			:number = 4;
		public static UNIT_STRING_FIELD_ALIAS_NAME			:number = 5;
		public static UNIT_STRING_FIELD_PICK_NAME			:number = 6;	// 正在采集的玩家
		public static UNIT_STRING_FIELD_GROUP_PEACE_ID			:number = 7;	//  组队id
		public static UNIT_STRING_FIELD_FACTION_GUID			:number = 8;	//  帮派id
		public static MAX_UNIT_STRING_FIELD			:number = 9;
		// 游戏对象类型
		public static GO_ENTRY_TELETEPORT			:number = 1;	// 传送点
		public static GO_ENTRY_LOOT			:number = 9;	// 战利品游戏对象
		// 游戏对象数据
		// 传送点专用
		public static GO_TELETEPORTER_TO_MAPID			:number = 13;
		public static GO_TELETEPORTER_TO_X			:number = 14;
		public static GO_TELETEPORTER_TO_Y			:number = 15;
		// 任务相关游戏对象
		public static GO_QUEST_ID_0			:number = 13;	// 相关任务0
		public static GO_QUEST_ID_1			:number = 14;	// 相关任务1
		public static GO_QUEST_ID_2			:number = 15;	// 相关任务2
		public static GO_QUEST_ID_3			:number = 16;	// 相关任务3
		public static GO_STRING_FIELD_CREATED_NAME			:number = 5;	// 战利品创建者Name
		// 机关类相关的
		public static GO_GEAR_STATUS			:number = 13;	// 机关状态
		public static GO_GEAR_KILLER			:number = 14;	// 机关破坏者
		// 机关状态枚举
		public static GO_GEAR_STATUS_START			:number = 1;	// 机关初始状态
		public static GO_GEAR_STATUS_OPEN			:number = 2;	// 机关打开
		public static GO_GEAR_STATUS_CLOSE			:number = 3;	// 机关关闭
		public static GO_GEAR_STATUS_END			:number = 4;	// 机关即将消失
		// 精灵身上标识下标枚举
		public static UNIT_FIELD_FLAGS_CANT_CAST			:number = 0;	// 标识是否可以施法
		public static UNIT_FIELD_FLAGS_CANT_MOVE			:number = 1;	// 标识是否可以移动
		public static UNIT_FIELD_FLAGS_BUFF_DAZUO			:number = 2;	// 标识是否打坐buff
		public static UNIT_FIELD_FLAGS_GUAJIBAOHU			:number = 3;	// 标识是否是挂机保护
		public static UNIT_FIELD_FLAGS_FACTION_LINGXIU			:number = 4;	// 帮派领袖BUFF
		public static UNIT_FIELD_FLAGS_FACTION_GUWU			:number = 5;	// 帮派鼓舞BUFF
		public static UNIT_FIELD_FLAGS_IS_BOSS_CREATURE			:number = 6;	// 标识是否是副本boss怪
		public static UNIT_FIELD_FLAGS_USE_GAMEOBJECT			:number = 7;	// 标识是否使用游戏对象
		public static UNIT_FIELD_FLAGS_IS_FLZ_PUB_CREATURE			:number = 8;	// 标识是否风流镇酒馆怪
		public static UNIT_FIELD_FLAGS_QUEST_FOLLOW_CREATUR			:number = 9;	// 做任务刷出来的跟谁宠物，任务完成时删掉
		public static UNIT_FIELD_FLAGS_IS_PVP			:number = 10;	// 是否是PVP
		public static UNIT_FIELD_FLAGS_IS_FIELD_BOSS_CREATURE			:number = 11;	// 标识是否是野外boss怪
		public static UNIT_FIELD_FLAGS_IS_INVISIBLE_SPELL			:number = 12;	// 隐藏的技能NPC
		// 场景服专用的玩家状态下标枚举
		public static PLAYER_SCENED_FLAS_HUNG_UP			:number = 0;	// 挂机状态
		public static PLAYER_SCENED_FLAS_PVP_STATE			:number = 1;	// PVP状态
		public static PLAYER_SCENED_FLAGS_FUBEN_HUNG_UP			:number = 2;	// 标识是否副本连续挂机状态
		// 玩家应用服标志位，玩家选项
		public static PLAYER_APPD_INT_FIELD_FLAGS_IS_ZIBAO			:number = 0;	// 玩家是否自爆
		public static PLAYER_APPD_INT_FIELD_FLAGS_YEYOU_ONLINE			:number = 1;	// 页游是否在线，客户端用的
		public static PLAYER_APPD_INT_FIELD_FLAGS_PHONE_ONLINE			:number = 2;	// 手游是否在线，客户端用的
		public static PLAYER_APPD_INT_FIELD_FLAGS_FROM_KUAFU			:number = 3;	// 玩家是否从pk回到游戏服
		public static PLAYER_APPD_INT_FIELD_FLAGS_GIFT_CREATE			:number = 4;	// 礼包是否已创建
		public static PLAYER_APPD_INT_FIELD_FLAGS_LIMIT_CREATE			:number = 5;	// 限时活动是否已创建
		public static PLAYER_APPD_INT_FIELD_FLAGS_IS_FIRST_RECHARGE			:number = 6;	// 是否已经首充
		public static PLAYER_APPD_INT_FIELD_FLAGS_NEW_PLAYER			:number = 7;	// 是否新玩家，是新玩家则发放礼包等等。。
		public static PLAYER_APPD_INT_FIELD_FLAGS_SAFETY_CODE_CHECK			:number = 8;	// 标识安全码验证是否通过
		public static PLAYER_APPD_INT_FIELD_FLAGS_AUTO_GROUP			:number = 9;	// 玩家是否自动接受组队
		public static PLAYER_APPD_INT_FIELD_FLAGS_IS_HOSTING_LOGIN			:number = 10;	// 是否是托管登录
		public static PLAYER_APPD_INT_FIELD_FLAGS_IS_HOSTING_APPLY			:number = 11;	// 是否托管申请中
		public static PLAYER_APPD_INT_FIELD_FLAGS_SOCIAL_CREATE			:number = 12;	// 社交系统是否以创建	
		public static PLAYER_APPD_INT_FIELD_FLAGS_ITEM_CREATE			:number = 13;	// 物品binlog是否创建
		public static PLAYER_APPD_INT_FIELD_FLAGS_LOGICAL_CREATE			:number = 14;	// 业务逻辑binlog是否创建
		public static PLAYER_APPD_INT_FIELD_FLAGS_SPELL_CREATE			:number = 15;	// 技能binlog是否创建
		public static PLAYER_APPD_INT_FIELD_FLAGS_INSTANCE_CREATE			:number = 16;	// 副本binlog是否创建
		public static PLAYER_APPD_INT_FIELD_FLAGS_QUEST_CREATE			:number = 17;	// 任务binlog是否创建
		// 基本潜力点属性
		public static QIANLI_TYPE_LILIANG			:number = 0;	// 力量
		public static QIANLI_TYPE_TIZHI			:number = 1;	// 体质
		public static QIANLI_TYPE_SHENFA			:number = 2;	// 身法
		public static QIANLI_TYPE_FANGYU			:number = 3;	// 狂暴
		public static MAX_QIANLI_TYPE			:number = 4;
		// 客户端使用的数字下标数量
		public static MAX_CLIENT_UINT32_COUNT			:number = 100;
		// 客户端使用的字符串下标数量
		public static MAX_CLIENT_STRING_COUNT			:number = 20;
		public static MAX_ITEMS_CD_COUNT			:number = 20;	// 物品大cd最大数量(20个保存时间戳)
		public static MAX_ITEM_USED_COUNT			:number = 5;	// 物品大cd使用次数(5个byte保存次数)
		public static MAX_SPELL_CAPACITY			:number = 20;	// 最多拥有的技能数
		// 技能
		public static SPELL_BASE_LEVEL			:number = 0;	// 技能等级
		public static SPELL_BASE_FORCE			:number = 1;	// 技能等级对应的战斗力
		public static SPELL_BASE_ID			:number = 2;	// 技能ID
		public static MAX_SPELLBASE			:number = 3;
		public static FUNCTIONAL_QING_GONG			:number = 1;	// 轻功
		public static FUNCTIONAL_TI_YUN_ZONG			:number = 2;	// 梯云纵
		public static FUNCTIONAL_RIDE			:number = 3;	// 骑乘
		public static FUNCTIONAL_DA_ZUO			:number = 4;	// 打坐
		public static PLAYER_SLOT_SPELL_MAX_COUNT			:number = 12;	//  玩家技能槽信息上限
		public static PLAYER_IMPORTANT_CD_COUNT			:number = 20;	//  玩家重要技能的CD
		//  玩家技能槽的技能信息
		public static SHORT_SLOT_SPELL_ID			:number = 0;	// 技能槽中的技能id	占一个short
		public static BYTE_SLOT_SPELL_LV			:number = 2;	// 技能槽中的技能lv	占一个byte
		public static BYTE_SLOT			:number = 3;	// 技能槽的位置		占一个byte
		//  技能激活方式
		public static SPELL_ACTIVE_BY_LEVEL			:number = 0;	// 等级激活
		public static SPELL_ACTIVE_BY_QUEST			:number = 1;	// 任务激活
		public static SPELL_ACTIVE_BY_ITEM			:number = 2;	// 道具激活
		//  要在binlog中存CD的重要技能CD信息
		public static IMPORTANT_SPELL_ID			:number = 0;	// 技能id
		public static IMPORTANT_SPELL_CD			:number = 1;	// 技能CD
		public static MAX_IMPORTANT_SPELL_ATTR_COUNT			:number = 2;
		//  要在binlog中存开启功能的信息
		public static OPEN_MENU_MAIN_ID			:number = 0;	// 主菜单id
		public static OPEN_MENU_SUB_FLAG			:number = 1;	// 子菜单flag
		public static MAX_OPEN_MENU_ATTR_COUNT			:number = 2;
		public static GIFT_PACKS_TYPE_ITEM_GIVE			:number = 0;	// 用GM命令生成
		public static GIFT_PACKS_TYPE_SYSTEM_COMPENSATION			:number = 1;	// 系统补偿
		public static GIFT_PACKS_TYPE_BAG_FULL			:number = 2;	// 背包满了
		public static GIFT_PACKS_TYPE_LEVEL_RANK			:number = 3;	// 排行榜
		public static GIFT_PACKS_TYPE_WORLD_BOSS			:number = 4;	// 世界BOSS
		public static GIFT_PACKS_TYPE_3V3_WEEK			:number = 5;	// 3v3周奖励
		public static GIFT_PACKS_TYPE_3V3_MONTH			:number = 6;	// 3v3月奖励（段位奖励）
		public static GIFT_PACKS_TYPE_DOUJIAN_DAY			:number = 7;	// 斗剑台每日奖励
		public static GIFT_PACKS_TYPE_FACTION_BOSS			:number = 8;	// 家族boss奖励
		public static GIFT_PACKS_TYPE_FACTION_GIFT_RANK			:number = 9;	// 家族魅力排行奖励
		public static GIFT_PACKS_TYPE_ACT_RANK			:number = 10;	// 开服排行奖励
		public static SCENED_APPD_ENTER_DAILY_INSTANCE			:number = 1;	// 进入日常副本
		public static SCENED_APPD_ENTER_VIP_INSTANCE			:number = 2;	// 进入VIP副本
		public static SCENED_APPD_USE_ITEM			:number = 3;	// 使用血瓶
		public static SCENED_APPD_USE_RESPAWN_ITEM			:number = 4;	// 使用复活丹
		public static SCENED_APPD_ENTER_TRIAL_INSTANCE			:number = 5;	// 进入试炼塔副本
		public static SCENED_APPD_PASS_TRIAL_INSTANCE			:number = 6;	// 通关试炼塔副本
		public static SCENED_APPD_PASS_VIP_INSTANCE			:number = 7;	// 通关VIP副本
		public static SCENED_APPD_ADD_ENEMY			:number = 8;	// 增加仇人
		public static SCENED_APPD_ENTER_RES_INSTANCE			:number = 9;	// 进入资源副本
		public static SCENED_APPD_ADD_MAIL			:number = 10;	// 增加邮件
		public static SCENED_APPD_PASS_RES_INSTANCE			:number = 11;	// 通关资源副本
		public static SCENED_APPD_KILL_MONSTER			:number = 12;	// 杀怪
		public static SCENED_APPD_JOIN_FIELD_BOSS			:number = 13;	// 参加野外BOSS
		public static SCENED_APPD_GAMEOBJECT			:number = 14;	// 采集物品
		public static SCENED_APPD_TALK			:number = 15;	// 对话
		public static SCENED_APPD_RIDE			:number = 16;	// 骑乘
		public static SCENED_APPD_GOLD_RESPAWN			:number = 17;	// 元宝复活
		public static SCENED_APPD_DOUJIANTAI			:number = 18;	// 斗剑台结果
		public static SCENED_APPD_KILL_MONSTER_COLLECT			:number = 19;	// 杀怪收集物品
		public static SCENED_APPD_XIULIANCHANG			:number = 20;	// 修练场掠夺结果
		public static SCENED_APPD_XIANFU_PRACTISE			:number = 21;	// 仙府体验
		public static SCENED_APPD_ADD_OFFLINE_RISK_REWARD			:number = 22;	// 离线冒险世界奖励
		public static SCENED_APPD_PASS_WORLD_RISK			:number = 23;	// 通关冒险世界
		public static SCENED_APPD_ENTER_MASS_BOSS_INSTANCE			:number = 24;	// 进入全民boss副本
		public static SCENED_APPD_FACTION_TOWER_WIN			:number = 25;	// 无尽远征 胜利
		public static SCENED_APPD_SINGLE_PVP_RESULT			:number = 26;	//  排位赛结果
		public static SCENED_APPD_ENTER_QUALIFY_INSTANCE			:number = 27;	// 进入排位赛
		public static SCENED_APPD_ENTER_FACTION_TOWER_INSTANCE			:number = 28;	// 进入家族远征
		public static APPD_SCENED_SWEEP_TRIAL_INSTANCE			:number = 1;	// 扫荡试炼塔副本
		public static APPD_SCENED_SWEEP_VIP_INSTANCE			:number = 2;	// 扫荡VIP副本
		public static APPD_SCENED_RESPAWN			:number = 3;	// 元宝复活
		public static APPD_SCENED_NEAR_BY_CHAT			:number = 4;	// 附近聊天
		public static APPD_SCENED_ADD_EXP			:number = 5;	// 场景服加经验
		public static APPD_SCENED_CLEAR_FIELD_BOSS			:number = 6;	// 场景服清理野外BOSS
		public static APPD_SCENED_REBORN_FIELD_BOSS			:number = 7;	// 场景服刷新野外
		public static APPD_SCENED_WORLD_BOSS_WAITING			:number = 8;	// 进入世界BOSS等待房间
		public static APPD_SCENED_FIGHT_WORLD_BOSS			:number = 9;	// 可挑战开始世界BOSS
		public static APPD_SCENED_WORLD_BOSS_END			:number = 10;	// 世界BOSS结束
		public static APPD_SCENED_WORLD_BOSS_ENTER			:number = 11;	// 进入世界BOSS房间
		public static APPD_SCENED_REMIND_INSTANCE_ENTER			:number = 12;	// 进入原地副本房间
		public static APPD_SCENED_MASS_BOSS_REBORN			:number = 13;	// 全民boss重生
		public static INSTANCE_SUB_TYPE_VIP			:number = 1;	// vip副本
		public static INSTANCE_SUB_TYPE_TRIAL			:number = 2;	// 试炼塔副本
		public static INSTANCE_SUB_TYPE_WORLD_BOSS			:number = 3;	// 世界BOSS
		public static INSTANCE_SUB_TYPE_RES			:number = 4;	// 资源副本
		public static INSTANCE_SUB_TYPE_KUAFU_3V3			:number = 5;	// 跨服3v3
		public static INSTANCE_SUB_TYPE_XIANFU			:number = 6;	// 仙府夺宝
		public static INSTANCE_SUB_TYPE_DOUJIANTAI			:number = 7;	// 斗剑台
		public static INSTANCE_SUB_TYPE_XIANFU_EXPERIENCE			:number = 8;	// 仙府体验
		public static INSTANCE_SUB_TYPE_XIULIAN			:number = 9;	// 修炼房
		public static INSTANCE_SUB_TYPE_PLOT			:number = 10;	// 原地剧情副本
		public static INSTANCE_SUB_TYPE_MASS_BOSS			:number = 11;	// 全民boss
		public static INSTANCE_SUB_TYPE_KUAFU_GROUP			:number = 12;	// 跨服组队副本
		public static INSTANCE_SUB_TYPE_FACTION_BOSSDEFENSE			:number = 13;	// 家族首领挑战
		public static INSTANCE_SUB_TYPE_FACTION_TOWER			:number = 14;	// 家族无尽远征
		public static INSTANCE_SUB_TYPE_QUALIFY			:number = 15;	// 排位赛
		public static INSTANCE_SUB_TYPE_RISK			:number = 16;	// 世界冒险
		//  聊天频道
		public static CHAT_CHANNEL_SYSTEM			:number = 0;	// 系统频道
		public static CHAT_CHANNEL_WORLD			:number = 1;	// 世界频道
		public static CHAT_CHANNEL_NEARBY			:number = 2;	// 附近频道
		public static CHAT_CHANNEL_FAMILY			:number = 3;	// 家族频道
		public static CHAT_CHANNEL_GROUP			:number = 4;	// 队伍频道
		// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public static MAX_CHAT_BLOCK_COUNT			:number = 30;
		public static MAX_RANK_LIKE			:number = 10;
		public static MAX_SHOP_LIMIT			:number = 20;
		public static MAX_WORLD_3V3_COUNT			:number = 3;
		public static MAX_BUYED_FACTION_SHOP			:number = 8;
		public static MAX_PLAYER_OPEN_MENU_COUNT			:number = 50;
		public static MAX_OPTIONAL_GUIDE_COUNT			:number = 30;
		public static MAX_PLAYER_CULTIVATION_RIVAL_COUNT			:number = 4;
		public static MAX_PLAYER_CULTIVATION_PLUNDER_RECORD_COUNT			:number = 10;
		public static MAX_PLAYER_FACTION_SKILL_COUNT			:number = 20;
		// 帮派成员礼物的INT信息
		public static FACTION_DATA_INT_GIFT_ID			:number = 0;	// 礼物ID
		public static FACTION_DATA_INT_GIFT_POINT			:number = 1;	// 本次礼物总魅力值
		public static FACTION_DATA_INT_GIFT_FLAG_THANK			:number = 2;	// 感谢标识信息
		public static FACTION_DATA_INT_GIFT_TIME			:number = 3;	// 赠送时间
		public static FACTION_DATA_INT_GIFT_COUNT_ID			:number = 4;	// 玩家生成的礼物序号
		public static MAX_FACTION_DATA_INT_GIFT			:number = 5;
		// 帮派成员礼物的STRING信息
		public static FACTION_DATA_STRING_GIFT_GUID			:number = 0;	// 赠送者guid
		public static FACTION_DATA_STRING_GIFT_MSG			:number = 1;	// 赠送者留言
		public static FACTION_DATA_STRING_GIFT_ITEM_LIST			:number = 2;	// 礼物列表详情	物品1 \2 数量1 \1 物品2 \2 数量2
		public static FACTION_DATA_STRING_GIFT_REPLY_LIST			:number = 3;	// 回复信息列表		玩家guid \2 信息 \2 回复类型 \2 时间 \1 玩家guid \2 信息 \2 回复类型 \2 时间
		public static MAX_FACTION_DATA_STRING_GIFT			:number = 4;
		// 帮派成员礼物回复类型枚举
		public static FACTION_DATA_REPLY_TYPE_TEXT			:number = 0;	// 文本回复
		public static FACTION_DATA_REPLY_TYPE_VOICE			:number = 1;	// 语音回复
		public static MAX_FACTION_DATA_GIFT_COUNT			:number = 150;	// 每人送礼上限
		public static MAX_FACTION_DATA_GIFT_REPLY_COUNT			:number = 200;	// 回复上限
		public static MAX_FACTION_DATA_GIFT_CACHE_COUNT			:number = 1000;	// 离线感谢记录上限
		// 玩家下标
		// //////////////////////////////////////////////////////////////////////////////////////////////////
		// int 部分
		// ////////////////////////////////////////////////////////////////////////
		// 公共部分
		public static PLAYER_FIELD_FD			:number = 0;	// 所在场景服的网络连接号
		public static PLAYER_FIELD_MERGE_DATA_INDEX			:number = 1;	// 玩家合并数据时用来多服务器交互的下标，0.预留，1.回档，2.传送验证数据
		public static PLAYER_FIELD_ENTRY			:number = 2;	// 模板
		public static PLAYER_FIELD_MAP_ID			:number = 3;	// 地图
		public static PLAYER_FIELD_INSTANCE_ID			:number = 4;	// 地图实例
		public static PLAYER_FIELD_LINE_NO			:number = 5;	// 地图分线号
		public static PLAYER_FIELD_POS_X			:number = 6;	// X坐标
		public static PLAYER_FIELD_POS_Y			:number = 7;	// Y坐标
		public static PLAYER_FIELD_ORIENTATION			:number = 8;	// 朝向
		public static PLAYER_FIELD_MOVESPEED			:number = 9;	// 不用了
		public static PLAYER_FIELD_LEVEL			:number = 11;	// 等级
		public static PLAYER_FIELD_BYTES_0			:number = 12;	// 四个字节,分别存放 0角色id,[1阵营2种族3职业]
		public static PLAYER_FIELD_NPC_FLAG			:number = 13;	// NPC标识
		public static PLAYER_FIELD_DEATH_STATE			:number = 14;	// 生存状态
		public static PLAYER_FIELD_HEALTH			:number = 15;	// 当前生命
		public static PLAYER_FIELD_MAX_HEALTH			:number = 17;	// 最大生命
		public static PLAYER_FIELD_DAMAGE			:number = 19;	// 攻击力
		public static PLAYER_FIELD_ARMOR			:number = 21;	// 防御力
		public static PLAYER_FIELD_HIT			:number = 23;	// 命中
		public static PLAYER_FIELD_MISS			:number = 25;	// 闪避
		public static PLAYER_FIELD_CRIT			:number = 27;	// 暴击
		public static PLAYER_FIELD_TOUGH			:number = 29;	// 坚韧
		public static PLAYER_FIELD_ATTACK_SPEED			:number = 31;	// 攻击速度
		public static PLAYER_FIELD_MOVE_SPEED			:number = 33;	// 移动速度
		public static PLAYER_FIELD_IGNORE_ARMOR			:number = 35;	// 忽视防御
		public static PLAYER_FIELD_IGNORE_MISS			:number = 37;	// 忽视闪避
		public static PLAYER_FIELD_RECOVERY			:number = 39;	// 生命值回复
		public static PLAYER_FIELD_DAMAGE_AMPLIFY_RATE			:number = 41;	// 伤害加深(万分比)
		public static PLAYER_FIELD_DAMAGE_RESIST_RATE			:number = 43;	// 伤害减免(万分比)
		public static PLAYER_FIELD_DAMAGE_RETURN_RATE			:number = 45;	// 反弹伤害(万分比)
		public static PLAYER_FIELD_VAMPIRIC_RATE			:number = 47;	// 吸血光环(万分比)
		public static PLAYER_FIELD_RECOVERY_RATE			:number = 49;	// 回复效率(万分比)
		public static PLAYER_FIELD_CRIT_RATE			:number = 51;	// 暴击率(万分比)
		public static PLAYER_FIELD_CRIT_RESIST_RATE			:number = 53;	// 抗暴率(万分比)
		public static PLAYER_FIELD_CRIT_DAM_RATE			:number = 55;	// 暴击伤害倍数(万分比)
		public static PLAYER_FIELD_CRIT_RESIST_DAM_RATE			:number = 57;	// 降暴伤害倍数(万分比)
		public static PLAYER_FIELD_HIT_RATE			:number = 59;	// 命中率(万分比)
		public static PLAYER_FIELD_MISS_RATE			:number = 61;	// 闪避率(万分比)
		public static PLAYER_FIELD_STUN_RATE			:number = 63;	// 眩晕
		public static PLAYER_FIELD_ROOTS_RATE			:number = 65;	// 定身
		public static PLAYER_FIELD_SILENCE_RATE			:number = 67;	// 沉默
		public static PLAYER_FIELD_CHAOS_RATE			:number = 69;	// 混乱
		public static PLAYER_FIELD_CHARM_RATE			:number = 71;	// 魅惑
		public static PLAYER_FIELD_CONTROL_ENHANCE_RATE			:number = 73;	// 控制增强
		public static PLAYER_FIELD_CONTROL_RESIST_RATE			:number = 75;	// 控制减免
		public static PLAYER_FIELD_STRENGTH_ARMOR			:number = 77;	// 强化护甲
		public static PLAYER_FIELD_ATTR_RESERVE0			:number = 79;	// 预留属性0
		public static PLAYER_FIELD_ATTR_RESERVE1			:number = 81;	// 预留属性1
		public static PLAYER_FIELD_ATTR_RESERVE2			:number = 83;	// 预留属性2
		public static PLAYER_FIELD_ATTR_RESERVE3			:number = 85;	// 预留属性3
		public static PLAYER_FIELD_ATTR_RESERVE4			:number = 87;	// 预留属性4
		public static PLAYER_FIELD_ATTR_RESERVE5			:number = 89;	// 预留属性5
		public static PLAYER_FIELD_ATTR_RESERVE6			:number = 91;	// 预留属性6
		public static PLAYER_FIELD_ATTR_RESERVE7			:number = 93;	// 预留属性7
		public static PLAYER_FIELD_BUFF			:number = 95;	// BUFF
		public static PLAYER_FIELD_BUFF_RESERVE			:number = 145;	// BUFF保留参数	
		public static PLAYER_INT_FIELD_BUFF_GIVER_UINT_GUID			:number = 195;	// buff giver的uintGuid
		public static PLAYER_INT_FIELD_BUFF_EFFECT_ID_START			:number = 245;	// buff等级 (byte)
		public static PLAYER_INT_FIELD_BUFF_EFFECT_ID_END			:number = 295;
		public static PLAYER_FIELD_SKIN			:number = 295;	// 生物变身
		public static PLAYER_FIELD_BYTES_1			:number = 296;	// 四个字节,分别存放 0怪物分类
		public static PLAYER_FIELD_FORCE			:number = 297;	// 战斗力
		public static PLAYER_FIELD_EQUIPMENT			:number = 299;	// 装备列表，12个32位预留三个
		public static PLAYER_FIELD_CUR_MOUNT			:number = 319;	// 当前坐骑模板id
		public static PLAYER_FIELD_PEACE_MODE_CD			:number = 320;	// 和平模式CD
		public static PLAYER_FIELD_NOTORIETY			:number = 321;	// 2个short(0:战斗模式, 1:恶名值)
		public static PLAYER_FIELD_BYTES_2			:number = 322;	// 玩家标识,存4个byte[0灰名时间 1付费等级 2免费复活 3玩家称号]
		public static PLAYER_FIELD_BYTES_3			:number = 323;	// 四个字节,分别存放 0头像,[1发型2可用技能槽数量3下次复活是否有保护buff]
		public static PLAYER_FIELD_BYTES_4			:number = 324;	// 四个字节,分别存放 (0:频道屏蔽列表,1:预留,2:预留,3:预留)
		public static PLAYER_FIELD_BYTES_5			:number = 325;	// 0 GM权限, 1, 2 
		public static PLAYER_FIELD_AUTO_HP			:number = 326;	// 大红
		public static PLAYER_FIELD_AUTO_MP			:number = 328;	// 大蓝
		public static PLAYER_FIELD_VIP_LEVEL			:number = 330;	// VIP 等级
		public static PLAYER_FIELD_VIP_TIME_OUT			:number = 331;	// VIP 超时时间
		//  挂机设置
		public static PLAYER_FIELD_HOOK			:number = 332;	// 挂机状态
		public static PLAYER_FIELD_HOOK_BYTE0			:number = 333;	// 0:槽1技能,1:槽2技能,2:槽3技能,3:槽4技能
		public static PLAYER_FIELD_HOOK_BYTE1			:number = 334;	// 0:神兵技能,1:怒气技能2:使用银两买药,3:银两不足用元宝买药
		public static PLAYER_FIELD_HOOK_SHORT			:number = 335;	// 0:自动吃药百分比,1:自动使用道具id
		public static PLAYER_FIELD_HOOK_BYTE3			:number = 336;	// 0:回程复活/原地复活,1:自动使用绑银购买复活丹,2:绑银不足用元宝,3:自动出售某种平直及以下装备
		public static PLAYER_FIELD_FLAGS			:number = 337;	// 主玩家下标flags
		public static PLAYER_FIELD_FLAGS_END			:number = 345;	// 预留8个32位flags
		public static PLAYER_FIELD_ONLINE_TIME			:number = 345;	// 总在线时长(分钟为单位)
		public static PLAYER_FIELD_ANGER			:number = 346;	// 怒气改变
		public static PLAYER_FIELD_TRIAL_LAYERS			:number = 347;
		public static PLAYER_INT_FIELD_TRIAL_FINISHED_SECTIONID			:number = 348;	// (已经通关的关卡id)
		public static PLAYER_INT_FIELD_TRIAL_PROCESS			:number = 349;	// (0:已经杀的怪,1:总共需要杀的怪)
		public static PLAYER_FIELD_DECLINE_CHANNEL_BYTE0			:number = 350;	// 拒绝频道A(0系统，1帮派，2组队，3世界)
		public static PLAYER_FIELD_DECLINE_CHANNEL_BYTE1			:number = 351;	// 拒绝频道B(0:附近)
		public static PLAYER_SCENED_INT_FIELD_PLAYER_JUMP_CD			:number = 352;	// 跳跃CD
		public static PLAYER_INT_FIELD_SYSTEM_MAIL_ID			:number = 353;	// 当前领取的系统邮件的id
		public static PLAYER_FIELD_DIVINE_NUM			:number = 354;	// 神兵数量
		public static PLAYER_FIELD_DIVINE_FORCE			:number = 355;	// 神兵总战斗力
		public static PLAYER_FIELD_MOUNT_FORCE			:number = 356;	// 坐骑总战力
		public static PLAYER_FIELD_SKILL_FORCE			:number = 357;	// 技能战力
		public static PLAYER_FILED_GEM_FORCE			:number = 358;	// 宝石战力
		public static PLAYER_FIELD_STRENGTH_FORCE			:number = 359;	// 强化战力
		public static PLAYER_FIELD_RANK_LIKE			:number = 360;
		public static PLAYER_FIELD_USE_RANK_LIKE			:number = 361;
		public static PLAYER_FIELD_SHOP_LIMIT_START			:number = 362;
		public static PLAYER_FIELD_SHOP_LIMIT_END			:number = 382;
		public static PLAYER_EXPAND_INT_FCM_LOGIN_TIME			:number = 382;	// 防沉迷，单位：分钟	-1是非防沉迷玩家
		public static PLAYER_EXPAND_INT_FCM_LOGOUT_TIME			:number = 383;	// 防沉迷离线时间
		public static PLAYER_EXPAND_INT_CREATE_TIME			:number = 384;	// 角色创建时间
		public static PLAYER_EXPAND_INT_LAST_LOGIN_TIME			:number = 385;	// 最后登录时间
		public static PLAYER_EXPAND_INT_LAST_LOGOUT_TIME			:number = 386;	// 最后离线时间
		public static PLAYER_EXPAND_INT_NUMBER_OF_LOGINS			:number = 387;	// 累积登录次数
		public static PLAYER_EXPAND_INT_MONEY			:number = 388;	// 各种货币
		public static PLAYER_EXPAND_INT_MONEY_END			:number = 432;
		public static PLAYER_EXPAND_INT_USE_FASHION			:number = 432;	// 是否启用时装,目前用到20个pos
		public static PLAYER_EXPAND_INT_XP			:number = 433;	// 当前经验，64位
		public static PLAYER_EXPAND_INT_NEXT_LEVEL_XP			:number = 435;	// 下一级经验，64位
		public static PLAYER_EXPAND_INT_XP_ADDED			:number = 437;	//  应用服增加的经验
		public static PLAYER_EXPAND_INT_XP_PICKED			:number = 439;	//  场景服已经领取的应用服增加的经验
		public static PLAYER_EXPAND_INT_MAP_STATUS			:number = 441;	//  地图开启进度
		public static PLAYER_EXPAND_INT_GAG_END_TIME			:number = 442;	// 禁言结束时间
		public static PLAYER_EXPAND_INT_TO_MAP			:number = 443;	// 玩家要传送到的地图
		public static PLAYER_EXPAND_INT_TO_INSTANCE_ID			:number = 444;	// 玩家要传送到的地图实例ID
		public static PLAYER_EXPAND_INT_TO_POS_X			:number = 445;	// 玩家药传送到的坐标
		public static PLAYER_EXPAND_INT_TO_POS_Y			:number = 446;
		public static PLAYER_EXPAND_INT_TO_LINE_NO			:number = 447;	// 传送线号
		public static PLAYER_EXPAND_INT_DB_MAP			:number = 448;	// 玩家最后一次进入副本前的地图	
		public static PLAYER_EXPAND_INT_DB_POS_X			:number = 449;	// 玩家最后一次进入副本前的坐标
		public static PLAYER_EXPAND_INT_DB_POS_Y			:number = 450;
		public static PLAYER_EXPAND_INT_CLIENT_DATA			:number = 451;	// 远程存储
		// ////////////////////////////////////////////////////////////////////////
		// 应用服部分	
		public static PLAYER_APPD_INT_FIELD_FLAG			:number = 551;	// 玩家标志位
		public static PLAYER_APPD_INT_FIELD_FLAG_END			:number = 558;	// 结束下标
		public static PLAYER_APPD_INT_FIELD_DAILY_TIME			:number = 558;	//  每天在线时长（min）
		public static PLAYER_APPD_INT_FIELD_RESET_WEEK			:number = 559;	//  每周重置时间
		public static PLAYER_APPD_INT_FIELD_RESET_DALIY			:number = 560;	// 重置的时间点每小时一次
		public static PLAYER_APPD_INT_FIELD_RECHARGE_SUM			:number = 584;	// 累计充值总数
		public static PLAYER_APPD_INT_FIELD_LAST_RECHARGE_TIME			:number = 585;	// 最后一笔充值时间
		public static PLAYER_APPD_INT_FLELD_JHM_FLAGS			:number = 586;	// 激活码flags
		public static PLAYER_APPD_INT_FLELD_JHM_FLAGS_END			:number = 594;	// 激活码flags_end
		// 主背包扩展时间戳
		public static PLAYER_APPD_INT_FIELD_EXTENSION_END_TIME			:number = 595;	// 主包裹扩展结束时间戳
		public static PLAYER_APPD_INT_FIELD_EXTENSION_REMAIN_TIME			:number = 596;	// 主包裹扩展剩余多少时间
		public static PLAYER_INT_FIELD_BLOCK_COUNT			:number = 598;	// 屏蔽列表个数
		public static PLAYER_INT_FIELD_WORLD_BOSS_JOIN_ID			:number = 599;	// 最后一次参加的世界BOSS id
		public static PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE			:number = 600;	// 0:最后一次参加的世界BOSS状态, 1:进入的线数,2:死亡次数,3:预留
		// 场景服扩展下标开始了
		public static PLAYER_SCENED_INT_FLAGS			:number = 601;	// 玩家场景服标志位
		//  只显示装备的主动技能
		public static PLAYER_INT_FIELD_SPELL_START			:number = 609;
		public static PLAYER_INT_FIELD_SPELL_END			:number = 621;
		// 重要技能的CD
		public static PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_START			:number = 621;
		public static PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_END			:number = 661;
		public static PLAYER_EXPAND_KILL_MONSTER			:number = 661;	// 杀怪数
		// 跨服
		public static PLAYER_APPD_INT_FIELD_KUAFU_WARID			:number = 662;	// 跨服场次id
		public static PLAYER_INT_FIELD_KUAFU_NUMBER			:number = 663;	// 0:玩家报名跨服时收到匹配信息中给的编号 1:跨服类型（值参照枚举：EKUAFU_TYPE）
		public static PLAYER_INT_FIELD_MAIN_QUEST_ID			:number = 664;	// 当前主线任务
		public static PLAYER_INT_FIELD_QUEST_CHAPTER			:number = 665;	// 任务章节奖励领取情况
		public static PLAYER_INT_FIELD_MOUNT_LEVEL			:number = 666;	// 4个bytes(0:当前坐骑阶数 1:当前坐骑星级,2:当前坐骑是否骑乘，3:当前幻化id)
		public static PLAYER_INT_FIELD_DIVINE_ID			:number = 667;	// 当前装备的神兵id
		public static PLAYER_INT_FIELD_PASSIVE_SPELL_START			:number = 668;	// 被动技能开始
		public static PLAYER_INT_FIELD_PASSIVE_SPELL_END			:number = 768;	// 被动技能个数
		public static PLAYER_INT_FIELD_VIRTUAL_CAMP			:number = 768;	// 虚拟阵营
		public static PLAYER_INT_FIELD_WORLD_3V3_SCORE			:number = 769;	// 跨服3v3积分
		public static PLAYER_INT_FIELD_WORLD_3V3_TOTAL_SCORE			:number = 770;	// 跨服3v3积分
		public static PLAYER_INT_FIELD_WORLD_3V3_TREND_INFO			:number = 771;	// 胜负走势
		public static PLAYER_INT_FIELD_DOUJIANTAI_RANK			:number = 772;	// 斗剑台排名
		public static PLAYER_INT_FIELD_DOUJIANTAI_REFRESH_TIME			:number = 773;	// 最后一次刷新对手时间戳
		public static PLAYER_INT_FIELD_ARREARS			:number = 774;	// 欠费
		public static PLAYER_INT_FIELD_DAILY_QUEST_FINISHED			:number = 776;	//  每日任务完成数
		public static PLAYER_INT_FIELD_BAG_SORT_TIME			:number = 777;	// 整理背包时间戳
		// 已开启功能的记录
		public static PLAYER_INT_FIELD_OPEN_MENU_INDEX			:number = 778;
		public static PLAYER_INT_FIELD_OPEN_MENU_START			:number = 779;
		public static PLAYER_INT_FIELD_OPEN_MENU_END			:number = 879;
		// 已购家族商店物品的记录
		public static PLAYER_INT_FIELD_BUYED_FACTION_SHOP			:number = 880;	// 已购家族商店物品开始
		public static PLAYER_INT_FIELD_BUYED_FACTION_SHOP_END			:number = 888;	// 已购家族商店物品结束
		// 记录强制引导ID 
		public static PLAYER_INT_FIELD_GUIDE_ID_LAST			:number = 889;	// 上次完成的引导
		public static PLAYER_INT_FIELD_GUIDE_ID_NOW			:number = 890;	// 当前进行中的引导
		// 修炼场相关
		public static PLAYER_INT_FIELD_CULTIVATION_LAST_PLUNDER_TIME			:number = 891;	// 上次挑战时间戳
		public static PLAYER_INT_FIELD_CULTIVATION_LAST_REFRESH_TIME			:number = 892;	// 上次刷新对手时间戳
		public static PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_EXP			:number = 893;	// 当日累计掠夺经验
		public static PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_CHEST			:number = 894;	// 当日累计掠夺宝箱数
		public static PLAYER_INT_FIELD_CULTIVATION_TODAY_PURCHASE_COUNT			:number = 895;	// 当日购买次数
		public static PLAYER_INT_FIELD_CULTIVATION_LEFT_PLUNDER_COUNT			:number = 896;	// 当前剩余挑战次数
		public static PLAYER_INT_FIELD_CULTIVATION_PLUNDER_RECORD_INDEX			:number = 897;	// 修练场修炼记录下标
		public static PLAYER_INT_FIELD_CULTIVATION_TOTAL_BEEN_PLUNDER_COUNT			:number = 898;	// 本轮被掠夺成功次数
		public static PLAYER_INT_FIELD_CULTIVATION_TODAY_TOTAL_PLUNDER_COUNT			:number = 899;	// 本日总掠夺次数
		public static PLAYER_INT_FIELD_CULTIVATION_START_TIME			:number = 900;	// 修炼开始时间
		public static PLAYER_INT_FIELD_CULTIVATION_LOST_INFO			:number = 901;	// 修炼宝箱丢失信息
		// 登陆大礼相关
		public static PLAYER_INT_FIELD_LOGIN_ACTIVITY_TOTAL_DAYS			:number = 902;	// 登陆总天数
		public static PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_START			:number = 903;	// 领取状态开始
		public static PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_END			:number = 905;	// 领取状态结束
		//  非强制引导ID
		public static PLAYER_INT_FIELD_OPTIONAL_GUIDE_START			:number = 906;	// 非强制引导开始
		public static PLAYER_INT_FIELD_OPTIONAL_GUIDE_END			:number = 966;	//  非强制引导结束
		public static PLAYER_INT_FILED_LEAVE_RISK_TIME			:number = 966;	// 离开冒险世界的时间戳
		public static PLAYER_INT_FILED_LEAVE_RISK_SUIT_SCORE			:number = 967;	// 是否已经领取不在冒险世界的挂机奖励
		public static PLAYER_INT_FILED_FACTION_BUILDING_SPEEDUP_DAILY_COUNT			:number = 968;	// 家族建筑升级加速每日次数
		public static PLAYER_INT_FILED_FACTION_DONATE_GIFT_EXCHANGE_DAILY_COUNT			:number = 969;	// 家族宝库贡献礼物兑换每日次数
		public static PLAYER_INT_FILED_CHARM_POINT			:number = 970;	// 魅力值
		public static PLAYER_INT_FILED_FACTION_GIFT_NEXT_COUNT_ID			:number = 972;	// 玩家礼物历史记录下一个count_id
		public static PLAYER_INT_FILED_FACTION_GIFT_START			:number = 973;	// 玩家礼物历史记录开始
		public static PLAYER_INT_FILED_FACTION_GIFT_END			:number = 1723;
		public static PLAYER_INT_FIELD_CREATE_ICON			:number = 1723;	// 待创建的帮派icon
		public static PLAYER_INT_FIELD_FACTION_GIFT_POINT_COUNT			:number = 1724;	// 帮派魅力赠送总记数
		public static PLAYER_INT_FIELD_FACTION_GIFT_SEND_COUNT			:number = 1726;	// 帮派礼物赠送总记数
		public static PLAYER_INT_FIELD_FACTION_GIFT_BEEN_THANK_COUNT			:number = 1727;	// 帮派礼物赠送被女王感谢记数
		public static PLAYER_INT_FIELD_MASS_BOSS_BUYED_TIMES			:number = 1728;	// 已经购买次数
		public static PLAYER_INT_FIELD_MASS_BOSS_TIMES			:number = 1729;	// 全民boss次数
		public static PLAYER_INT_FIELD_MASS_BOSS_CD			:number = 1730;	// 全民boss回复cd(0:表示已满了, 只有次数不满的情况才有cd)
		public static PLAYER_INT_FIELD_TALISMAN_FORCE			:number = 1731;	// 法宝总战力
		public static PLAYER_INT_FIELD_WINGS_FORCE			:number = 1732;	// 神羽总战力
		public static PLAYER_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG			:number = 1733;	// 组队副本首次通关flag
		public static PLAYER_INT_FIELD_MERIDIAN_FORCE			:number = 1734;	// 经脉修炼战力
		public static PLAYER_INT_FIELD_WINGS_RANK			:number = 1735;	// 神羽阶数
		public static PLAYER_INT_FIELD_FACTION_BOSSDEFENSE_TICKETS			:number = 1736;	// 家族首领挑战剩余次数
		public static PLAYER_INT_FIELD_FACTION_TOWER_CLEAR_FLOOR			:number = 1737;	// 家族无尽远征 历史挑战层数
		public static PLAYER_INT_FIELD_FACTION_TOWER_FLAG			:number = 1738;	// 0 扫荡状态 1~15 宝箱领取状态
		public static PLAYER_INT_FIELD_QUALIFY_SCORE			:number = 1739;	//  排位赛积分
		public static PLAYER_INT_FIELD_FACTION_SKILL_LV_START			:number = 1740;	// 家族技能等级开始 0:已学习等级 uint16 1:当前生效等级
		public static PLAYER_INT_FIELD_FACTION_SKILL_LV_END			:number = 1760;	// 家族技能等级结束
		public static PLAYER_INT_FIELD_APPEARANCE			:number = 1760;	//  外观(0:武器,1:衣服)
		public static PLAYER_INT_FIELD_WEAPON_FORCE			:number = 1761;	//  武器外观战力
		public static PLAYER_INT_FIELD_CLOTH_FORCE			:number = 1762;	//  衣服外观战力
		public static PLAYER_INT_FIELD_POKEDEX_FORCE			:number = 1763;	//  图鉴战力
		public static PLAYER_INT_FIELD_TITLE_FORCE			:number = 1764;	//  称号战力
		public static PLAYER_INT_FIELD_RENAME_TIMES			:number = 1765;	//  改名次数
		public static PLAYER_INT_FIELD_REVENGE_TIMES			:number = 1766;	// 当日剩余复仇次数
		public static PLAYER_INT_FIELD_REVENGE_BUY_TIMES			:number = 1767;	// 当日复仇购买次数
		public static PLAYER_INT_FIELD_WINGS_STAR			:number = 1768;	// 神羽星数
		public static PLAYER_INT_FIELD_VIPGIFT_FLAG			:number = 1769;	// vip礼包购买状态
		public static PLAYER_APPD_INT_FIELD_CONSUME_SUM			:number = 1770;	// 累计消费元宝
		public static PLAYER_APPD_INT_FIELD_MONEYTREE_COUNT			:number = 1771;	// 摇钱树摇钱次数
		public static PLAYER_APPD_INT_FIELD_MONEYTREE_GIFT_FLAG			:number = 1772;	// 摇钱树礼包领取状态
		// ////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 字符串部分
		public static PLAYER_STRING_FIELD_ACCOUNT			:number = 4;	// 账号
		public static PLAYER_STRING_FIELD_TELEPORT_GUID			:number = 5;	// 传送GUID
		public static PLAYER_APPD_STRING_FIELD_CLIENT_DATA			:number = 6;	// 远程存储
		public static PLAYER_STRING_FIELD_LAST_LOGIN_IP			:number = 26;	// 玩家最后登录的IP
		public static PLAYER_STRING_FIELD_RECHARGE_ID			:number = 27;	// 最后充值ID
		public static PLAYER_STRING_FIELD_CREATE_LOGIN_IP			:number = 28;	// 玩家创建IP
		public static PLAYER_APPD_STRING_FIELD_PINGTAI_INFO			:number = 29;	// 平台信息
		public static PLAYER_STRING_FIELD_DB_KUAFU_INFO			:number = 30;	// 玩家跨服信息,是否为跨服玩家依据这个下标是不是空串
		public static PLAYER_STRING_FIELD_FACTION_GUID			:number = 31;	// 帮派guid
		public static PLAYER_STRING_FIELD_FACTION_NAME			:number = 32;	// 帮派名字
		// -----------------------------------
		public static PLAYER_STRING_FIELD_BLOCK_START			:number = 33;	// 聊天屏蔽列表开始
		public static PLAYER_STRING_FIELD_BLOCK_END			:number = 63;	// 聊天屏蔽列表开始
		public static PLAYER_STRING_FIELD_RANKLIKE_START			:number = 63;	// 排行榜点赞列表开始
		public static PLAYER_STRING_FIELD_RANKLIKE_ENE			:number = 73;	// 排行榜点赞列表结束
		// 修炼场相关
		public static PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_START			:number = 74;	// 修练场对手guid开始
		public static PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_END			:number = 78;	// 修练场对手guid结束
		public static PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_START			:number = 79;	// 修练场修炼记录开始
		public static PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_END			:number = 89;	// 修练场修炼记录结束
		public static PLAYER_STRING_FIELD_INVITE_FACTION_GUID			:number = 89;	// 邀请的帮派guid
		public static PLAYER_STRING_FIELD_CREATE_FACTION_NAME			:number = 90;	// 待创建的帮派名称
		public static PLAYER_STRING_FILED_FACTION_GIFT_START			:number = 91;	// 玩家礼物历史记录开始
		public static PLAYER_STRING_FILED_FACTION_GIFT_END			:number = 691;
		public static PLAYER_STRING_FIELD_GROUP_PEACE_ID			:number = 691;	// 组队模式下的组队id
		public static PLAYER_BASIC_SPELL_CAPACITY			:number = 30;	// 玩家基础技能的上限
		public static PLAYER_DIVINE_SPELL_CAPACITY			:number = 15;	// 玩家神兵个数的上限
		public static PLAYER_TALISMAN_SPELL_CAPACITY			:number = 15;	// 玩家法宝个数的上限
		//  玩家拥有的基本技能属性信息
		public static SHORT_SPELL_ID			:number = 0;	// 技能id short
		public static SHORT_SPELL_LV			:number = 1;	// 技能等级 short
		//  技能槽对应技属性
		public static SLOT_COMBO			:number = 1;	// 连招技能槽
		public static SLOT_DIVINE			:number = 5;	// 神兵技能槽
		public static SLOT_ANGER			:number = 6;	// 愤怒技能槽
		public static SPELL_SLOT_COUNT			:number = 6;	// 技能槽的数量
		//  技能类型
		public static SKILL_TYPE_DIVINE			:number = 4;	// 神兵技能
		public static MOUNT_UPGRADE_SKILL_COUNT			:number = 10;
		public static MOUNT_ILLUSION_COUNT			:number = 30;
		public static EQUIPMENT_COUNT			:number = 10;
		public static DIVINE_PASSIVE_SKILL_COUNT			:number = 3;
		public static EQUIPDEVELOP_GEM_COUNT			:number = 10;
		//  幻化属性
		public static ILLUSION_ATTR_ID			:number = 0;	// 幻化id
		public static ILLUSION_ATTR_SPELL_START			:number = 1;	// 幻化技能开始
		public static ILLUSION_ATTR_SPELL_END			:number = 3;	// 幻化技能结束
		public static ILLUSION_ATTR_EXPIRE			:number = 3;	// 过期时间
		public static MAX_ILLUSION_ATTR_COUNT			:number = 4;
		public static EXPIRE_TYPE_ILLUSION			:number = 0;	// 幻化过期
		public static EXPIRE_TYPE_DIVINE			:number = 1;	// 神兵过期
		public static STRENGTHEN_LEV_BLESS			:number = 0;	// 强化等级 祝福值
		public static MAX_STRENGTHEN_COUNT			:number = 1;
		public static GEM_LEV			:number = 0;	// 宝石等级
		public static GEM_CURID_BLESS			:number = 3;	// 当前宝石  1short 宝石祝福值 0short 
		public static MAX_GEM_COUNT			:number = 4;
		public static DIVINE_ID_LEV_BLESS			:number = 0;	// 神兵 id_8 等级lev_8 祝福值bless_16
		public static DIVINE_TIME			:number = 1;	// 神兵到期时间
		public static DIVINE_SKILL			:number = 2;
		public static DIVINE_PASSIVE_SKILL			:number = 3;
		public static DIVINE_IMPROVE			:number = 6;	// 神兵培养 铸造 forge 0; 进阶 advance 1; 铸魂 spirit 2
		public static MAX_DIVINE_COUNT			:number = 7;
		public static TALISMAN_ID_LV			:number = 0;	// 法宝 id_8 等级 lev_8
		public static TALISMAN_FORCE			:number = 1;	// 法宝 战力
		public static MAX_TALISMAN_COUNT			:number = 2;
		public static EQUIPDEVELOP_STRENGTH_LV			:number = 0;	// 0 int16 强化等级
		public static EQUIPDEVELOP_REFINE_LV			:number = 1;	// 0 int16 阶数 1 int16 星数
		public static EQUIPDEVELOP_GEM_LV_START			:number = 2;	// 宝石等级开始 int16 int16
		public static EQUIPDEVELOP_GEM_LV_END			:number = 7;	// 宝石等级结束
		public static MAX_EQUIPDEVELOP_COUNT			:number = 8;
		//  升级技能类型
		public static RAISE_BASE_SKILL			:number = 1;	// 基础技能
		public static RAISE_MOUNT_SKILL			:number = 2;	// 坐骑技能
		public static RAISE_ILLUSION_SKILL			:number = 3;	// 幻化技能
		public static RAISE_DIVINE_SKILL			:number = 4;	// 幻化技能
		// 装备养成操作类型
		public static EQUIPDEVELOP_TYPE_STRENGTH_LVUP			:number = 1;
		public static EQUIPDEVELOP_TYPE_REFINE_STAR_LVUP			:number = 2;
		public static EQUIPDEVELOP_TYPE_REFINE_RANK_LVUP			:number = 3;
		public static EQUIPDEVELOP_TYPE_GEM_ACTIVE			:number = 4;
		public static EQUIPDEVELOP_TYPE_GEM_LVUP			:number = 5;
		public static EQUIPDEVELOP_TYPE_WASHATTRS_WASH			:number = 6;
		public static EQUIPDEVELOP_TYPE_WASHATTRS_SAVE			:number = 7;
		public static EQUIPDEVELOP_TYPE_WASHATTRS_DEL			:number = 8;
		public static MAX_EXTERIOR_COUNT			:number = 200;	//  最大外观数量
		// 活动数据int
		public static PLAYER_ACTIVITTY_DATA_INT_0			:number = 0;
		public static PLAYER_ACTIVITTY_DATA_INT_1			:number = 1;
		public static PLAYER_ACTIVITTY_DATA_INT_2			:number = 2;
		public static PLAYER_ACTIVITTY_DATA_INT_3			:number = 3;
		public static MAX_PLAYERACTIVITTYDATAINT_COUNT			:number = 4;
		// 活动数据string
		public static PLAYER_ACTIVITTY_DATA_STRING_0			:number = 0;
		public static MAX_PLAYERACTIVITTYDATASTRING_COUNT			:number = 1;
		public static MAX_PLAYERDACTIVITTYDATA_COUNT			:number = 100;	// 最大活动数据数量
		// 玩家技能信息
		public static SPELL_BASE_COUNT			:number = 0;	// 基础技能个数
		public static SPELL_INT_FIELD_BASE_SPELL_START			:number = 1;	// 基础技能开始
		public static SPELL_INT_FIELD_BASE_SPELL_END			:number = 31;
		public static SPELL_INT_FIELD_MOUNT_LEVEL			:number = 31;	// 2个short (0阶数, 1星级)
		public static SPELL_INT_FIELD_MOUNT_TRAIN_EXP			:number = 32;	// 当前培养经验
		public static SPELL_INT_FIELD_MOUNT_LEVEL_BASE			:number = 33;	// 坐骑等级
		public static SPELL_INT_FIELD_MOUNT_SPELL_START			:number = 34;	// 进阶技能开始
		public static SPELL_INT_FIELD_MOUNT_SPELL_END			:number = 44;	// 进阶技能结束
		public static SPELL_INT_FIELD_MOUNT_BLESS_EXP			:number = 44;	// 进阶祝福值
		public static SPELL_INT_FIELD_MOUNT_ILLUSION_START			:number = 45;	// 幻化开始
		public static SPELL_INT_FIELD_MOUNT_ILLUSION_END			:number = 165;	// 幻化结束
		public static SPELL_STRENGTHEN_START			:number = 166;	// 强化开始
		public static SPELL_STRENGTHEN_END			:number = 176;	// 强化结束
		public static SPELL_STRENGTHEN_ALLMUL			:number = 177;	// 全身强化标记
		public static SPELL_GEM_START			:number = 178;	// 宝石开始
		public static SPELL_GEM_END			:number = 218;	// 宝石结束
		public static SPELL_GEM_ALLMUL			:number = 219;	// 全身宝石标记
		public static SPELL_DIVINE_COUNT			:number = 220;	// 神兵个数
		public static SPELL_DIVINE_START			:number = 221;	// 神兵开始
		public static SPELL_DIVINE_END			:number = 326;	// 神兵结束
		public static SPELL_TALISMAN_START			:number = 326;	// 法宝开始
		public static SPELL_TALISMAN_END			:number = 356;	// 法宝结束
		public static SPELL_WINGS_ID			:number = 356;	// 翅膀id  阶数*100 + 星数
		public static SPELL_WINGS_LEVEL			:number = 357;	// 翅膀强化等级
		public static SPELL_WINGS_BLESS_EXP			:number = 358;	// 翅膀当前祝福经验
		public static SPELL_INT_FIELD_MERIDIAN_LEVEL			:number = 359;	//  2shorts(0:经脉等级, 1:是否需要突破)
		public static SPELL_INT_FIELD_MERIDIAN_EXP			:number = 360;	//  经脉经验
		public static SPELL_INT_FIELD_MERIDIAN_CNT_START			:number = 361;	//  每天完成次数开始
		public static SPELL_INT_FIELD_MERIDIAN_CNT_END			:number = 374;	//  每天完成次数结束
		public static SPELL_INT_FIELD_EQUIPDEVELOP_START			:number = 374;	//  装备培养开始
		public static SPELL_INT_FIELD_EQUIPDEVELOP_END			:number = 454;	// 装备培养结束
		public static SPELL_INT_FIELD_EQUIPDEVELOP_BONUS_LV			:number = 454;	//  装备培养奖励等级 0 强化 1 精炼 2 镶嵌
		public static SPELL_INT_FIELD_APPEARANCE_START			:number = 455;	//  外观开始
		public static SPELL_INT_FIELD_APPEARANCE_END			:number = 655;	//  外观结束
		public static SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START			:number = 655;	// 活动玩家数据开始
		public static SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_END			:number = 1055;	// 活动玩家数据结束
		public static SPELL_STRING_FIELD_EQUIPDEVELOP_WASHATTRS_INFO			:number = 4;	// 洗点结果缓存
		public static SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_START			:number = 5;	// 活动玩家数据开始
		public static SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_END			:number = 105;	// 活动玩家数据结束
		public static SOCIAL_FRIEND_MAX_NUM			:number = 60;	// 好友数
		public static SOCIAL_APPLY_MAX_NUM			:number = 10;	//  申请数
		public static SOCIAL_ENEMY_MAX_NUM			:number = 20;	// 仇人数
		public static SOCIAL_START			:number = 4;
		public static SOCIAL_ICON_VIP_LEV			:number = 0;	// 图标 vip 等级
		public static SOCIAL_FAMILIAR_LEV_EXP			:number = 1;	// 亲密度等级 亲密度经验
		public static SOCIAL_FAMILIAR_FORCE			:number = 2;	// 战力
		public static MAX_FRIENT_COUNT			:number = 4;
		public static SOCIAL_BASE_COUNT			:number = 0;	// SOCIAL_BASE_COUNT = 0,//好友个数
		public static SOCIAL_REVENGE_NUM			:number = 4;	// 复仇次数
		public static SOCIAL_REVENGE_CD			:number = 5;	// 复仇CD
		public static SOCIAL_FRIEND_START			:number = 6;	// 好友开始
		public static SOCIAL_FRIEND_END			:number = 246;	// 好友结束
		public static SOCIAL_ENEMY_START			:number = 246;	// 仇人开始
		public static SOCIAL_ENEMY_END			:number = 326;	// 仇人结束
		public static SOCIAL_APPLY_START			:number = 326;	// 申请开始
		public static SOCIAL_APPLY_END			:number = 366;	// 申请结束
		public static SOCIAL_APPLY_CLEAR_FLAG			:number = 366;	// 申请清除标记
		public static SOCIAL_ENEMY_TIME_START			:number = 367;	// 仇人时间戳开始
		public static SOCIAL_ENEMY_TIME_END			:number = 387;	// 仇人时间戳结束
		// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 帮派下标
		// 帮派事件
		public static FACTION_EVENT_TYPE_NULL			:number = 0;	// 预留
		public static FACTION_EVENT_TYPE_ADD_MEMBER			:number = 1;	// 添加成员
		public static FACTION_EVENT_TYPE_SUB_MEMBER			:number = 2;	// 成员离开
		public static FACTION_EVENT_TYPE_APPOINT			:number = 3;	// 任免
		public static FACTION_EVENT_TYPE_KICK_MEMBER			:number = 4;	// 踢出成员
		public static FACTION_EVENT_TYPE_JUANXIAN			:number = 5;	// 捐献
		public static FACTION_EVENT_TYPE_HONGBAO			:number = 6;	// 发红包
		public static FACTION_EVENT_TYPE_SHANGXIANG			:number = 7;	// 上香
		// 帮派管理类型
		public static FACTION_MANAGER_TYPE_AGREE_JOIN			:number = 0;	// 同意加入帮派
		public static FACTION_MANAGER_TYPE_REFUSE_JOIN			:number = 1;	// 拒绝加入帮派
		public static FACTION_MANAGER_TYPE_KICK			:number = 2;	// 踢出帮派
		public static FACTION_MANAGER_TYPE_APPOINT			:number = 3;	// 职位任免
		public static FACTION_MANAGER_TYPE_RECRUIT			:number = 4;	// 招募设置
		public static FACTION_MANAGER_TYPE_LEVEL_UP			:number = 5;	// 帮派升级
		public static FACTION_MANAGER_TYPE_CHANGE_FLAGS			:number = 6;	// 替换帮旗
		public static FACTION_MANAGER_TYPE_NOTICE			:number = 7;	// 帮会公告
		public static FACTION_MANAGER_TYPE_AGREE_JOIN_ALL			:number = 8;	// 全部同意加入帮派
		public static FACTION_MANAGER_TYPE_REFUSE_JOIN_ALL			:number = 9;	// 全部拒绝加入帮派
		public static FACTION_MANAGER_TYPE_QUIT			:number = 10;	// 退出帮派
		// 帮众操作类型
		public static FACTION_MANAGER_TYPE_JUANXIAN			:number = 0;	// 捐献
		public static FACTION_MANAGER_TYPE_FULI			:number = 1;	// 领取福利
		public static FACTION_MANAGER_TYPE_FA_HONGBAO			:number = 2;	// 发红包
		public static FACTION_MANAGER_TYPE_LQ_HONGBAO			:number = 3;	// 领取红包
		public static FACTION_MANAGER_TYPE_SHANGXIANG			:number = 4;	// 上香
		public static FACTION_MANAGER_TYPE_SHOP			:number = 5;	// 购买
		public static FACTION_MANAGER_TYPE_BUY_TOKEN			:number = 6;	// 购买令牌
		public static FACTION_MANAGER_TYPE_CHALLENGE_BOSS			:number = 7;	// 挑战家族Boss
		public static FACTION_MANAGER_TYPE_BUILDING_UPGRADE			:number = 8;	// 建筑升级
		public static FACTION_MANAGER_TYPE_BUILDING_UPGRADE_SPEEDUP			:number = 9;	// 建筑升级加速
		public static FACTION_MANAGER_TYPE_DONATE_GIFT_EXCHANGE			:number = 10;	// 贡献礼包兑换
		public static FACTION_MANAGER_TYPE_GIFT_SHOW_PAGE			:number = 11;	// 查看礼物列表
		public static FACTION_MANAGER_TYPE_GIFT_SHOW_INFO			:number = 12;	// 查看礼物信息
		public static FACTION_MANAGER_TYPE_GIFT_SHOW_UNTHANK_PAGE			:number = 13;	// 女王查看未感谢礼物
		public static FACTION_MANAGER_TYPE_GIFT_SHOW_HISTORY_PAGE			:number = 14;	// 女王查看历史记录
		public static FACTION_MANAGER_TYPE_GIFT_THANK			:number = 15;	// 女王感谢
		public static FACTION_MANAGER_TYPE_GIFT_THANK_ALL			:number = 16;	// 女王全部感谢
		public static FACTION_MANAGER_TYPE_GIFT_THANK_AND_REPLY			:number = 17;	// 女王感谢并回复
		public static FACTION_MANAGER_TYPE_GIFT_REPLY			:number = 18;	// 所有人回复
		public static FACTION_MANAGER_TYPE_BOSSDEFENSE_CHALLENGE			:number = 19;	// 进行首领挑战
		public static FACTION_MANAGER_TYPE_BOSSDEFENSE_DAMAGE_LIST			:number = 20;	// 查看首领挑战输出前10
		public static FACTION_MANAGER_TYPE_TOWER_CHALLENGE			:number = 21;	// 无尽远征 挑战下一关
		public static FACTION_MANAGER_TYPE_TOWER_SWEEP			:number = 22;	// 无尽远征 扫荡
		public static FACTION_MANAGER_TYPE_TOWER_CHEST			:number = 23;	// 无尽远征 开宝箱
		public static FACTION_MANAGER_TYPE_SKILL_LVUP			:number = 24;	// 升级家族技能
		// 帮众建筑类型
		public static FACTION_BUILDING_TYPE_MAINHALL			:number = 1;	// 主殿
		public static FACTION_BUILDING_TYPE_STOREHOUSE			:number = 2;	// 宝库房
		public static FACTION_BUILDING_TYPE_BANK			:number = 3;	// 金库
		public static FACTION_BUILDING_TYPE_EVENT			:number = 4;	// 活动大厅
		public static FACTION_BUILDING_TYPE_SKILL			:number = 5;	// 技能坊
		public static FACTION_BUILDING_TYPE_SHOP			:number = 6;	// 家族商店
		// 帮派成员最多拥有的buff数
		public static MAX_FACTION_MENBER_BUFF_NUM			:number = 6;
		// 帮派最多拥有的buff数
		public static MAX_FACTION_BUFF_NUM			:number = 6;
		// 当前屏幕最大buff数
		public static MAX_CUR_SCREEN_BUFF_NUM			:number = 6;
		// 帮派申请列表最大玩家数
		public static MAX_FACTION_APLLY_MAMBER_COUNT			:number = 3;
		// 帮派最大成员数
		public static MAX_FACTION_MAMBER_COUNT			:number = 50;
		// 帮派捐献记录
		public static MAX_FACTION_EVENT_COUNT			:number = 10;
		public static MAX_FACTION_SHOP			:number = 8;
		// 帮派最大红包数
		public static MAX_FACTION_HONGBAO_COUNT			:number = 10;
		// 帮派最大BOSS数
		public static MAX_FACTION_BOSS_COUNT			:number = 10;
		// 帮派最大建筑数量
		public static MAX_FACTION_BUILDING_COUNT			:number = 10;
		// 帮派成员的INT信息
		public static FACTION_INT_MEMBER_FORCE			:number = 0;	// 成员战斗力
		public static FACTION_INT_MEMBER_UINT16			:number = 2;	// 0.成员等级,1.今日贡献
		public static FACTION_INT_MEMBER_BYTE			:number = 3;	// 0.是否在线,1.身份, 2,是否VIP，3,今日活跃度
		public static FACTION_INT_MEMBER_LOGOUT_TIME			:number = 4;	// 最后离线时间
		public static FACTION_INT_MEMBER_FLAGS			:number = 5;	// 成员标志位
		public static FACTION_INT_MEMBER_TOTAL_CONTRIBUTION			:number = 6;	// 历史贡献 - 申请时间
		public static FACTION_INT_MEMBER_CHARM			:number = 7;	// 个人的魅力值
		public static FACTION_INT_MEMBER_TOTAL_SEND_CHARM			:number = 9;	// (魅力总贡献) 
		public static FACTION_INT_MEMBER_TOWER_TODAY_FLOOR			:number = 10;	// 无尽远征今日通关层数
		public static MAX_FACTION_INT_MEMBER			:number = 11;
		// 帮派成员的STRING信息
		public static FACTION_STRING_MEMBER_GUID			:number = 0;	// 成员 ID
		public static FACTION_STRING_MEMBER_NAME			:number = 1;	// 成员名称
		public static MAX_FACTION_STRING_MEMBER			:number = 2;
		public static FACTION_INT_EVENT_TYPE_VALUE			:number = 0;	// 类型，数值
		public static FACTION_INT_EVENT_RESERVE			:number = 1;	// 保留字段
		public static MAX_FACTION_INT_EVENT			:number = 2;
		// 帮派成员身份枚举
		public static FACTION_MEMBER_IDENTITY_NULL			:number = 0;	// 空，预留
		public static FACTION_MEMBER_IDENTITY_BANGZHU			:number = 1;	// 帮主
		public static FACTION_MEMBER_IDENTITY_FU_BANGZHU			:number = 2;	// 副帮主
		public static FACTION_MEMBER_IDENTITY_TANGZHU			:number = 3;	// 堂主
		public static FACTION_MEMBER_IDENTITY_JINGYING			:number = 4;	// 精英
		public static FACTION_MEMBER_IDENTITY_QUNZHONG			:number = 5;	// 群众
		// 帮派标志位
		public static FACTION_FLAGS_AUTO			:number = 0;	// 帮派是否自动接受申请
		public static FACTION_FLAGS_IS_BOSS_ADD			:number = 1;	// 帮派是否有人通关了boss副本
		// 帮派buff信息枚举
		public static FACTION_BUFF_ID			:number = 0;	// 0：buff类型，1：预留
		public static FACTION_BUFF_END_TM			:number = 1;	// buff结束时间
		public static MAX_FACTION_BUFF			:number = 2;
		public static MAX_FACTION_STOREHOUSE_COUNT			:number = 100;
		public static MAX_FACTION_STOREHOUSE_RECORD_COUNT			:number = 10;
		// 帮派成员的INT信息
		public static FACTION_INT_BOSSDEFENSE_POOL_ID			:number = 0;	// 怪物池id
		public static FACTION_INT_BOSSDEFENSE_HP			:number = 1;	// 剩余hp
		public static FACTION_INT_BOSSDEFENSE_MAX_HP			:number = 2;	// 最大hp
		public static FACTION_INT_BOSSDEFENSE_STATUS			:number = 3;	// 怪物状态	0:空闲 1:战斗 2:死亡
		public static MAX_FACTION_BOSSDEFENSE			:number = 4;
		public static MAX_FACTION_BOSSDEFENSE_COUNT			:number = 6;
		// 帮派下标
		// UINT32 部分
		public static FACTION_INT_FIELD_PLAYER_NOW_INDEX			:number = 0;	// 帮派成员空位置索引
		public static FACTION_INT_FIELD_FLAG			:number = 1;	// 帮派FLAG
		public static FACTION_INT_FIELD_PLAYER			:number = 2;	// 帮派成员开始下标
		public static FACTION_INT_FIELD_PLAYER_END			:number = 552;	// 帮派申请索引
		public static FACTION_INT_FIELD_APPLY_PLAYER_COUNT_INDEX			:number = 552;
		public static FACTION_INT_FIELD_APPLY_PLAYER			:number = 553;	// 玩家申请加入帮派列表
		public static FACTION_INT_FIELD_APPLY_PLAYER_END			:number = 586;	// 帮派申请玩家列表
		public static FACTION_INT_FIELD_EVENT			:number = 586;	// 帮派记录开始
		public static FACTION_INT_FIELD_EVENT_END			:number = 606;	// 帮派记录结束
		public static FACTION_INT_FIELD_EVENT_FALG			:number = 606;	// 帮派记录标志位
		public static FACTION_INT_FIELD_SHOP			:number = 607;	// 商店开始
		public static FACTION_INT_FIELD_SHOP_END			:number = 615;	// 商店结束
		public static FACTION_INT_FIELD_FORCE			:number = 615;	// 帮派战斗力
		public static FACTION_INT_FIELD_MONEY			:number = 617;	// 帮派资产
		public static FACTION_INT_FIELD_LEVEL			:number = 619;	// 帮派等级
		public static FACTION_INT_FIELD_ACTIVITY			:number = 620;	// 帮派活跃度
		public static FACTION_INT_FIELD_RANK			:number = 621;	// 帮派排名
		public static FACTION_INT_FIELD_FLAGS_ID			:number = 622;	// (byte)0:帮派当前选择的旗帜ID (byte)1:神明等级 (uint16)1:灵气
		public static FACTION_INT_FIELD_MINLEV			:number = 623;	// 加入帮派最小等级
		public static FACTION_INT_FIELD_TOKEN_NUM			:number = 624;	// 令牌数量
		public static FACTION_INT_FIELD_TOKEN_POINTS			:number = 625;	// 令牌今日积分进度
		public static FACTION_INT_FIELD_TOKEN_POINTS_COUNT			:number = 626;	// 令牌今日积分完成次数
		public static FACTION_INT_FIELD_TOKEN_TODAY_BUY_COUNT			:number = 627;	// 今日令牌购买次数
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_ID_MAX			:number = 628;	// 已挑战最大boss id
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_ID			:number = 629;	// 当前挑战boss id
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_START_TIME			:number = 630;	// 当前挑战开始时间
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_HP_RATE			:number = 631;	// 当前boss血量万分比
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_POS			:number = 632;	// 当前boss位置 x,y
		public static FACTION_INT_FIELD_PROTECT_TARGET_HP_RATE			:number = 633;	// 当前守护目标血量万分比
		public static FACTION_INT_FIELD_PROTECT_TARGET_POS			:number = 634;	// 当前守护目标位置 x,y
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START			:number = 635;	// 当前boss输出榜开始 int 输出值
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END			:number = 685;	// 当前boss输出榜结束
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START			:number = 685;	// 总输出榜开始
		public static FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END			:number = 735;	// 总输出榜结束
		public static FACTION_INT_FIELD_STOREHOUSE_ITEM_COUNT			:number = 735;	// 宝库道具数量
		public static FACTION_INT_FIELD_STOREHOUSE_RECORD_CURSOR			:number = 736;	// 宝库记录游标
		public static FACTION_INT_FIELD_BUILDING_ID_START			:number = 737;	// 已有建筑id开始
		public static FACTION_INT_FIELD_BUILDING_ID_END			:number = 747;	// 已有建筑id结束
		public static FACTION_INT_FIELD_BUILDING_LVUP_ID			:number = 747;	// 当前正在升级的建筑id
		public static FACTION_INT_FIELD_BUILDING_LVUP_FINISH_TIME			:number = 748;	// 当前升级建筑完成时间戳
		public static FACTION_INT_FIELD_IS_DISSOLVED			:number = 749;	// 是否解散
		public static FACTION_INT_FIELD_GIFT_WEEK_POINT_START			:number = 750;	// 礼物周榜魅力值计数开始
		public static FACTION_INT_FIELD_GIFT_WEEK_POINT_END			:number = 800;	// 礼物周榜魅力值计数结束
		public static FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_START			:number = 800;	// 未处理礼物计数开始 女王未感谢 成员为领取
		public static FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_END			:number = 850;	// 未处理礼物计数结束
		public static FACTION_INT_FIELD_CHARM_POINT			:number = 851;	// 帮派女王魅力值 double
		public static FACTION_INT_FIELD_GIFT_SEND_COUNT_START			:number = 853;	// 今日赠送礼物次数开始
		public static FACTION_INT_FIELD_GIFT_SEND_COUNT_END			:number = 903;	// 今日赠送礼物次数结束
		public static FACTION_INT_FIELD_GIFT_LAST_SEND_TIME			:number = 903;	// 最后赠送的时间
		public static FACTION_INT_FIELD_GIFT_QUEEN_UNCHECK_COUNT			:number = 905;	// 女王未处理礼包数
		public static FACTION_INT_FIELD_BOSSDENFENSE_START			:number = 906;	// 家族首领挑战信息开始
		public static FACTION_INT_FIELD_BOSSDENFENSE_END			:number = 930;	// 家族首领挑战信息结束
		public static FACTION_INT_FIELD_TOWER_TODAY_TOP_FLOOR			:number = 930;	// 无尽远征 每日最高者 层数 int32
		public static FACTION_INT_FIELD_TOWER_TODAY_TOP_ICON			:number = 931;	// 无尽远征 每日最高者 头像 int32
		public static FACTION_INT_FIELD_TOWER_TODAY_TOP_FORCE			:number = 932;	// 无尽远征 每日最高者 战力 double
		public static FACTION_INT_FIELD_TOTAL_FORCE			:number = 934;	//  double 帮派成员总战力
		public static FACTION_INT_FIELD_MANGER_COAT			:number = 936;	// 帮主衣服
		public static FACTION_INT_FIELD_MANGER_WEAPON			:number = 937;	// 帮主武器
		public static FACTION_INT_FIELD_MANGER_VIP			:number = 938;	// 帮主vip
		public static FACTION_INT_FIELD_MANGER_GENDER			:number = 939;	// 帮主gender
		public static FACTION_INT_FIELD_MANGER_TITLE			:number = 940;	// 帮主title
		public static FACTION_INT_FIELD_MANGER_LIKE			:number = 941;	// 帮主点赞
		public static FACTION_INT_FIELD_MANGER_WING			:number = 942;	// 帮主神羽
		public static FACTION_STRING_FIELD_MANGER_NAME			:number = 4;	// 帮主名字
		public static FACTION_STRING_FIELD_MANGER_GUID			:number = 5;	// 帮主GUID
		public static FACTION_STRING_FIELD_PLAYER			:number = 6;	// 帮派成员列表		
		public static FACTION_STRING_FIELD_PLAYER_END			:number = 106;	// 帮派成员列表结束
		public static FACTION_STRING_FIELD_APPLY_PLAYER			:number = 106;	// 帮派申请玩家列表
		public static FACTION_STRING_FIELD_APPLY_PLAYER_END			:number = 112;	// 帮派申请玩家列表结束
		public static FACTION_STRING_FIELD_EVENT			:number = 112;	// 帮派记录开始
		public static FACTION_STRING_FIELD_EVENT_END			:number = 122;	// 帮派记录结束
		public static FACTION_STRING_FIELD_GONGGAO			:number = 122;	// 帮派公告
		public static FACTION_STRING_FIELD_ZHAOMU_GONGGAO			:number = 123;	// 招募公告
		public static FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START			:number = 124;	// 当前boss输出榜开始 string guid
		public static FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END			:number = 174;	// 当前boss输出榜结束
		public static FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START			:number = 174;	// 总输出榜开始
		public static FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END			:number = 224;	// 总输出榜结束
		public static FACTION_STRING_FIELD_STOREHOUSE_START			:number = 224;	// 家族宝库开始
		public static FACTION_STRING_FIELD_STOREHOUSE_END			:number = 324;	// 家族宝库结束
		public static FACTION_STRING_FIELD_STOREHOUSE_RECORD_START			:number = 324;	// 宝库记录开始
		public static FACTION_STRING_FIELD_STOREHOUSE_RECORD_END			:number = 334;	// 宝库记录结束
		public static FACTION_STRING_FIELD_GIFT_PLAYER_GUID_START			:number = 334;	// 礼物对应玩家guid开始
		public static FACTION_STRING_FIELD_GIFT_PLAYER_GUID_END			:number = 384;	// 礼物对应玩家guid结束
		public static FACTION_STRING_FIELD_TOWER_TODAY_TOP_NAME			:number = 384;	// 无尽远征 每日最高者 名称
		public static FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_START			:number = 0;	// 首领挑战伤害开始
		public static FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_END			:number = 300;	// 首领挑战伤害结束
		public static FACTION_DATA_INT_FIELD_GIFT_START			:number = 300;	// 礼物记录int开始
		public static FACTION_DATA_INT_FIELD_GIFT_TMP1			:number = 7500;	// 临时
		public static FACTION_DATA_INT_FIELD_GIFT_TOTAL_LEN			:number = 37500;	// 临时
		public static FACTION_DATA_INT_FIELD_GIFT_TOTAL_CACHE_LEN			:number = 5000;	// 临时
		public static FACTION_DATA_INT_FIELD_GIFT_TMP2			:number = 37800;	// 临时
		public static FACTION_DATA_INT_FIELD_GIFT_END			:number = 42800;	// 礼物记录结束
		public static FACTION_DATA_INT_FIELD_GIFT_RANK_START			:number = 42800;	// 记录排行礼物id开始
		public static FACTION_DATA_INT_FIELD_GIFT_RANK_END			:number = 50300;	// 记录排行礼物id结束
		public static FACTION_DATA_STRING_FIELD_GIFT_START			:number = 4;	// 礼物记录string开始
		public static FACTION_DATA_STRING_FIELD_GIFT_TEMP1			:number = 7500;	// 临时
		public static FACTION_DATA_STRING_FIELD_GIFT_TEMP2			:number = 30000;	// 临时
		public static FACTION_DATA_STRING_FIELD_GIFT_TEMP3			:number = 4000;	// 临时
		public static FACTION_DATA_STRING_FIELD_GIFT_TEMP4			:number = 34000;	// 临时
		public static FACTION_DATA_STRING_FIELD_GIFT_END			:number = 34004;	// 礼物记录结束
		// int
		// 记录2000条记录  魅力 家族图标
		// 记录排名信息 1~2000 记录index
		// 上周记录
		// string  女王guid  女王名称 家族guid 家族名 骑士名
		// 上周记录
		public static MAX_TRIAL_LAYER_COUNT			:number = 256;
		//  试炼塔状态系数
		public static TRIAL_STATE_FACTOR_ACTIVE			:number = 1;	// 激活状态系数
		public static TRIAL_STATE_FACTOR_PASS			:number = 10;	// 通关状态系数
		public static TRIAL_STATE_FACTOR_F_PASS			:number = 100;	// 首通状态系数
		public static MAX_ACTIVE_COUNT			:number = 50;
		public static MAX_ACTIVT_REWARD_COUNT			:number = 6;
		public static MAX_DOUJIANTAI_RECORD_COUNT			:number = 10;
		public static MAX_QUALIFY_RECORD_COUNT			:number = 30;
		//  玩家副本信息
		public static INSTANCE_INT_FIELD_VIP_START			:number = 0;	// vip副本开始	每个信息4个byte[0:预留,1:可扫荡难度,2:挑战次数,3:购买次数]
		public static INSTANCE_INT_FIELD_VIP_END			:number = 3;	// vip副本结束
		public static INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT			:number = 3;	// (0:今日可扫荡层数,1:历史通关层数)
		public static INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT			:number = 4;	// (0:扫荡次数,1:可购买扫荡次数)--]]
		public static INSTANCE_INT_FIELD_RES_START			:number = 5;	// 资源副本开始 每个信息4个byte[0:挑战次数,1:是否通关,2:预留,3:预留]
		public static INSTANCE_INT_FIELD_RES_END			:number = 10;	// 资源副本结束
		public static INSTANCE_INT_FIELD_ACTIVE_START			:number = 10;	// 活动开始
		public static INSTANCE_INT_FIELD_ACTIVE_END			:number = 60;	// 活动结束
		public static INSTANCE_INT_FIELD_ACTIVE			:number = 60;	// 活动-活跃度
		public static INSTANCE_INT_FIELD_ACTIVE_REWARD			:number = 61;	// 奖励领取状态
		public static INSTANCE_INT_FIELD_3V3_TIMES			:number = 62;	// 3v3次数 已参加次数 购买次数
		public static INSTANCE_INT_FIELD_3V3_DAY_REWARD			:number = 63;	// 3v3每日次数奖励 4个byte
		public static INSTANCE_INT_FIELD_3V3_SEGMENT_TIME			:number = 64;	// 3v3段位 发放时间
		public static INSTANCE_INT_FIELD_XIANFU_DAY_TIMES			:number = 65;	// 每日挑战次数
		public static INSTANCE_INT_FIELD_DOUJIANTAI_CURSOR			:number = 66;	// 斗剑台信息游标
		public static INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S			:number = 67;	// 对手名次开始
		public static INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E			:number = 70;	// 对手名次结束
		public static INSTANCE_INT_FIELD_DOUJIAN_TIMES			:number = 71;	// 斗剑次数 已挑战次数 购买次数
		public static INSTANCE_INT_FIELD_DOUJIAN_FIGHT_CD			:number = 72;	// 斗剑台挑战CD时间戳
		public static INSTANCE_INT_FIELD_DOUJIAN_FIRST_GET			:number = 73;	// 首胜奖励标记
		public static INSTANCE_INT_FIELD_DOUJIAN_FIRST_REWARD			:number = 74;	// 首胜奖励领取标记
		public static INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN			:number = 75;	// 连胜纪录 纪录 当前
		public static INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN_REWARD			:number = 76;	// 连胜奖励记录
		public static INSTANCE_INT_FIELD_DOUJIAN_MAX_RANK			:number = 77;	// 历史最高纪录
		public static INSTANCE_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG			:number = 78;	// 每bit记录对应组队副本id首次通关状态 false:未完成 true:已完成
		public static INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT			:number = 79;	// 组队副本剩余挑战次数
		public static INSTANCE_INT_FIELD_GROUP_INSTANCE_BUY_COUNT			:number = 80;	// 当日组队副本挑战次数购买次数
		public static INSTANCE_INT_FIELD_QUALIFY_EXTRA			:number = 81;	//  排位赛胜利额外可领取奖励标志
		public static INSTANCE_INT_FIELD_QUALIFY_WINS			:number = 82;	//  排位赛赢得场次		
		public static INSTANCE_INT_FIELD_QUALIFY_EXTRA_PICKED			:number = 83;	//  排位赛胜利额外已领取奖励标志
		public static INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES			:number = 84;	//  排位赛每天次数
		public static INSTANCE_INT_FIELD_QUALIFY_BUY_TIMES			:number = 85;	//  排位赛购买次数
		public static INSTANCE_INT_FIELD_QUALIFY_CURSOR			:number = 86;	//  排位赛记录游标
		public static INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_START			:number = 4;	// 斗剑台战斗信息开始
		public static INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_END			:number = 14;	// 斗剑台战斗信息结束
		public static INSTANCE_STR_FIELD_QUALIFY_RECORD_START			:number = 14;	// 排位赛战斗信息开始
		public static INSTANCE_STR_FIELD_QUALIFY_RECORD_END			:number = 44;	// 排位赛战斗信息结束
		//  战斗模式
		public static PEACE_MODE			:number = 0;	// 和平模式
		public static FAMILY_MODE			:number = 1;	// 家族模式
		public static GROUP_MODE			:number = 2;	// 组队模式
		public static MAX_BATTLE_MODE			:number = 3;
		// 需要发内部消息同步到场景服的技能类型
		public static TYPE_SPELL_SLOT			:number = 0;	// 更新装备槽中的技能
		public static TYPE_SPELL_PASSIVE			:number = 1;	// 更新基础被动技能
		//  玩家主动/被动/辅助技能分类
		public static SPELL_SUPPORT			:number = 0;	//  辅助
		public static SPELL_INITIATIVE_DAMAGE			:number = 1;	//  主动（伤害）
		public static SPELL_INITIATIVE_PROTECT			:number = 2;	//  主动（防护）
		public static SPELL_INITIATIVE_CONTROL			:number = 3;	//  主动（控制）
		public static SPELL_INITIATIVE_CURE			:number = 4;	//  主动（回复）
		public static SPELL_INITIATIVE_BUFF			:number = 5;	//  主动（增益）
		public static SPELL_PASSIVE_DAMAGE			:number = 6;	//  被动（伤害）
		public static SPELL_PASSIVE_PROTECT			:number = 7;	//  被动（防护）
		public static SPELL_PASSIVE_CONTROL			:number = 8;	//  被动（控制）
		public static SPELL_PASSIVE_CURE			:number = 9;	//  被动（回复）
		public static SPELL_PASSIVE_BUFF			:number = 10;	//  被动（增益）
		// 游戏配置专用的状态下标枚举
		public static GAME_CONFIG_FIELD_FLAGS_SHOW_PLATFORM_NAME			:number = 0;	// 是否显示平台名
		public static GAME_CONFIG_FIELD_FLAGS_SHOW_SERVER_ID			:number = 1;	// 是否显示服务器ID
		public static GAME_CONFIG_FIELD_FLAGS_SHOW_POST			:number = 2;	// 聊天是否post
		// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 游戏配置
		public static GAME_CONFIG_INT_FIELD_KAIFUSHIJIAN			:number = 0;	// 开服时间
		public static GAME_CONFIG_INT_FIELD_FLAGS			:number = 1;	// 游戏配置标志位
		public static GAME_CONFIG_INT_FIELD_ADDTIME			:number = 9;	// 合服时间
		public static GAME_CONFIG_INT_FIELD_WORLD_SVR_TYPE			:number = 10;	// 服务器类型(见枚举: ESERVER_TYPE)
		public static GAME_CONFIG_STRING_FIELD_PLATFORM_ID			:number = 4;	// 平台ID
		public static GAME_CONFIG_STRING_FIELD_GM_QQ			:number = 5;	// GM和QQ
		public static GAME_CONFIG_STRING_FIELD_DB_CONN			:number = 6;	// 数据库连接串
		public static GAME_CONFIG_STRING_FIELD_LOGIN_KEY			:number = 7;	// 登录秘钥
		public static GAME_CONFIG_STRING_FIELD_LOG_DB_CONN			:number = 8;	// 日志数据库连接串
		public static GAME_CONFIG_STRING_LOCAL_HDD_PATH			:number = 9;	// 本地硬盘数据保存地址
		public static GAME_CONFIG_STRING_EXT_WEB_INTERFACE			:number = 10;	// web接口配置
		public static GAME_CONFIG_STRING_CONF_SVR_URL			:number = 11;	// 配置服url地址
		public static GAME_CONFIG_STRING_WORLD_SERVER_URL			:number = 12;	// 世界服url地址
		public static GAME_CONFIG_STRING_FIELD_SERVER			:number = 200;	// 原始服务器
		public static GAME_CONFIG_STRING_FIELD_SERVER_LIST_BEGIN			:number = 201;	// 服务器列表
		// 客户端模块枚举
		public static CLIENT_MODULE_CENTER			:number = 0;	// 中心模块
		public static CLIENT_MODULE_CREATE			:number = 1;	// 创建角色模块
		public static CLIENT_MODULE_SCENE			:number = 2;	// 场景模块
		public static CLIENT_MODULE_UI			:number = 3;	// UI模块
		public static CLIENT_MODULE_SH			:number = 4;	// 梭哈模块
		public static MAX_CLIENT_MODULE			:number = 5;
		// 客户端模块版本信息
		public static CLIENT_VERSION_INT_CREATE_TIME			:number = 0;	// 版本创建时间
		public static MAX_CLIENT_VERSION_INT			:number = 1;
		public static CLIENT_VERSION_STRING_VERSIONS			:number = 0;	// 模块版本号
		public static CLIENT_VERSION_STRING_COMMENT			:number = 1;	// 模块版本说明
		public static MAX_CLIENT_VERSION_STRING			:number = 2;
		// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 客户端配置信息
		public static CLIENT_CONFIG_INT_FIELD_MODULE_INFO_BEGIN			:number = 0;
		public static CLIENT_CONFIG_INT_FIELD_MODULE_INFO_END			:number = 5;
		public static CLIENT_CONFIG_STRING_FIELD_MODULE_INFO_BEGIN			:number = 4;
		public static CLIENT_CONFIG_STRING_FIELD_MODULE_INFO_END			:number = 14;
		// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public static MAX_DEFAULT_LINE_COUNT			:number = 4;	//  最大默认分线数量
		public static MAX_FIELD_BOSS_COUNT			:number = 40;	//  最大默认野外BOSS数量
		//  野外BOSS进度类型
		public static FIELD_BOSS_PROCESS_TYPE_FINISH			:number = 0;	// 已结束
		public static FIELD_BOSS_PROCESS_START_COUNTDOWN			:number = 1;	// 开始倒计时
		public static FIELD_BOSS_PROCESS_BORN			:number = 2;	// BOSS刷新
		public static FIELD_BOSS_PROCESS_TREASURE			:number = 3;	// 宝箱出现
		//  野外BOSS int数据
		public static FIELD_BOSS_DATA_NEXT_BORN_TIME			:number = 0;	// 下一次刷新时间
		public static FIELD_BOSS_DATA_CURR_HP			:number = 1;	// 当前血量百分比
		public static FIELD_BOSS_DATA_PROCESS_TYPE			:number = 3;	// 进度类型
		public static FIELD_BOSS_DATA_PRIORITY_TIME			:number = 4;	// 优先拾取时间戳
		public static FIELD_BOSS_DATA_KILLED			:number = 5;	// 击杀次数
		public static MAX_FIELD_BOSS_INT_DATA_COUNT			:number = 6;
		//  野外BOSS str数据
		public static FIELD_BOSS_DATA_MAX_DAMAGE_GUID			:number = 0;	// 最大伤害guid
		public static FIELD_BOSS_DATA_NAME			:number = 1;	// 当前正在采集的玩家名字
		public static MAX_FIELD_BOSS_STR_DATA_COUNT			:number = 2;
		//  世界BOSS进度
		public static WORLD_BOSS_PROCESS_TYPE_FINISH			:number = 0;	// 已结束
		public static WORLD_BOSS_PROCESS_ENROLL			:number = 1;	// 报名
		public static WORLD_BOSS_PROCESS_BORN			:number = 2;	// BOSS刷新
		//  人物关于世界BOSS的状态
		public static PLAYER_WORLD_BOSS_NONE			:number = 0;	// 什么都没有
		public static PLAYER_WORLD_BOSS_ENROLLED			:number = 1;	// 报过名
		public static PLAYER_WORLD_BOSS_ENTERED			:number = 2;	// 进入过场景
		public static MASS_BOSS_STATE			:number = 0;	// 全民boss状态
		public static MASS_BOSS_TIME			:number = 1;	// 全民boss刷新时间
		public static MAX_MASS_BOSS_INT_FIELD_COUNT			:number = 2;
		public static MAX_XIANFU_RECORD_COUNT			:number = 10;
		public static MAX_MASS_BOSS_COUNT			:number = 10;
		public static MAX_LOTTERY_COUNT			:number = 10;
		public static MAX_LOTTERY_RECORD_COUNT			:number = 10;
		public static MAX_ACT_RANK_COUNT			:number = 10;	// 榜单数量
		public static MAX_ACT_RANK_INFO_COUNT			:number = 10;	// 最大名次信息数量
		// 世界变量
		public static GLOBALVALUE_INT_FIELD_FLAGS			:number = 0;	// 世界变量标志位
		public static GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION			:number = 8;	// 活动版本号
		public static GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_END_TIME			:number = 9;	// 活动结束时间
		public static GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM			:number = 10;	// 活动物品配置
		public static GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM_END			:number = 40;	// 最多10个道具掉落
		public static GLOBALVALUE_INT_FIELD_ONLINE_PLAYER_NUM			:number = 40;	// 计录全服在线玩家数
		public static GLOBALVALUE_INT_FIELD_WORLD_CONNECTION_STATUS			:number = 41;	// 世界服连接状态
		//  野外BOSS数据
		public static GLOBALVALUE_INT_FIELD_FIELD_BOSS_START			:number = 42;	//  野外boss数据开始
		public static GLOBALVALUE_INT_FIELD_FIELD_BOSS_END			:number = 282;	//  野外boss数据结束
		public static GLOBALVALUE_INT_FIELD_WORLD_BOSS_LEVEL			:number = 282;	// 世界BOSS等级
		public static GLOBALVALUE_INT_FIELD_WORLD_BOSS_STATE			:number = 283;	// 世界BOSS总状态
		public static GLOBALVALUE_INT_FIELD_WORLD_BOSS_LINE_STATE			:number = 284;	// 世界BOSS每个房间的状态
		public static GLOBALVALUE_INT_FIELD_WORLD_BOSS_LAST_ENROLL_TIME			:number = 285;	//  最近一次报名时间
		public static GLOBALVALUE_INT_FIELD_WORLD_BOSS_TIMES			:number = 286;	// 世界BOSS次数
		public static GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID			:number = 287;	// 0:世界BOSS类型1, 1:世界BOSS类型2,2:当前选定的类型,3:房间个数
		public static GLOBALVALUE_INT_FIELD_XIANFU_RECORD_CURSOR			:number = 288;	// 仙府开启宝箱的记录游标
		public static GLOBALVALUE_INT_FIELD_GIFT_RANK_WINER_FACTION_FLAG			:number = 289;	// 上周魅力排行第一家族旗子
		public static GLOBALVALUE_INT_FIELD_GIFT_RANK_NEXT_UPDATE_TIME			:number = 290;	// 魅力排行下次更新时间
		public static GLOBALVALUE_INT_FIELD_GIFT_RANK_CUR_ROUND			:number = 291;	// /魅力排行当前轮数
		public static GLOBALVALUE_INT_FIELD_MASS_BOSS_START			:number = 292;	// 全民boss开始
		public static GLOBALVALUE_INT_FIELD_MASS_BOSS_END			:number = 312;
		public static GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START			:number = 312;	//  抽奖记录游标
		public static GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_END			:number = 322;
		public static GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START			:number = 322;	//  活动运行id 开始
		public static GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_END			:number = 352;	//  活动运行id 结束
		public static GLOBALVALUE_STRING_FIELD_LIMIT_ACTIVITY_SCRIPT			:number = 4;	// 限时活动类名
		public static GLOBALVALUE_STRING_FIELD_FIELD_BOSS_START			:number = 5;	//  野外boss优先开启宝箱的人物guid开始
		public static GLOBALVALUE_STRING_FIELD_FIELD_BOSS_END			:number = 85;	//  野外boss优先开启宝箱的人物guid结束
		public static GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_START			:number = 85;	// 仙府开箱子记录开始
		public static GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_END			:number = 95;	//  仙府开箱子记录结束
		public static GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_QUEEN_NAME			:number = 95;	// 上周魅力排行第一女王名称
		public static GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_FACTION_NAME			:number = 96;	// 上周魅力排行第一家族名称
		public static GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_GUARD_NAME			:number = 97;	// 上周魅力排行第一骑士名称
		public static GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_START			:number = 98;	//  抽奖记录数据开始
		public static GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_END			:number = 198;
		public static MAX_DOUJIANTAI_RANK_COUNT			:number = 1000;
		public static MAX_RISK_RANK_COUNT			:number = 10;	// 世界冒险榜单数量
		public static MAX_RISK_RANK_SWAPED_COUNT			:number = 11;	// 世界冒险带交换的榜单数量
		public static RISK_RANK_INFO_SECTION_ID			:number = 0;
		public static RISK_RANK_INFO_TIME			:number = 1;
		public static MAX_RISK_RANK_INFO_COUNT			:number = 2;
		public static GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_START			:number = 0;	// 挑战中的标记位
		public static GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_END			:number = 40;
		public static GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_START			:number = 40;	//  活动结束id flag开始
		public static GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_END			:number = 240;	//  活动结束id flag结束
		public static GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_START			:number = 240;	// 活动排行数据开始
		public static GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_END			:number = 340;	// 活动排行数据结束
		public static GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_START			:number = 340;
		public static GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_END			:number = 362;
		public static GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_START			:number = 4;	// 斗剑台排名开始
		public static GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_END			:number = 1004;	// 斗剑台排名结束
		public static GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_START			:number = 1004;	// 战斗信息记录开始
		public static GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_END			:number = 11004;	// 战斗信息记录结束
		public static GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_START			:number = 11004;	// 活动排行数据开始
		public static GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_END			:number = 11104;	// 活动排行数据结束
		public static GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_START			:number = 11104;
		public static GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_END			:number = 11115;
		// 计时器世界变量计数器
		public static GLOBALCOUNTER_INT_FIELD_ONLINE_AWARD_COUNT			:number = 0;	// 全服银子数量
		public static GLOBALCOUNTER_INT_FIELD_DAILY_ADD_BIND_GOLD			:number = 2;	// 每日新增绑定元宝数量
		public static GLOBALCOUNTER_INT_FIELD_DAILY_SUB_BIND_GOLD			:number = 4;	// 每日消耗绑定元宝数量
		public static GLOBALCOUNTER_INT_FIELD_DAILY_ADD_GOLD_INGOT			:number = 6;	// 每日新增元宝数量
		public static GLOBALCOUNTER_INT_FIELD_DAILY_SUB_GOLD_INGOT			:number = 8;	// 每日消耗元宝数量
		public static GLOBALCOUNTER_INT_FIELD_DAILY_ADD_SILVER			:number = 10;	// 每日新增银子数量
		public static GLOBALCOUNTER_INT_FIELD_DAILY_SUB_SILVER			:number = 12;	// 每日消耗银子数量
		public static MAX_GLOBALCOUNTER_INT_FIELD			:number = 13;
		//  不同步客户端的计数器
		//  地图类型
		public static MAP_TYPE_MAIN			:number = 0;	// 主城
		public static MAP_TYPE_FIELD			:number = 1;	// 野外
		public static MAP_TYPE_INSTANCE			:number = 2;	// 副本
		public static MAP_TYPE_ACTIVITY			:number = 3;	// 活动
		public static MAP_TYPE_PVP			:number = 4;	// PVP
		//  副本人物类型
		public static INSTANCE_QUEST_TYPE_KILL_MONSTER			:number = 1;	// 击杀怪物(creatureId, num)
		public static INSTANCE_QUEST_TYPE_PICK_ITEM			:number = 2;	// 收集物品
		public static INSTANCE_QUEST_TYPE_ACTIVE_MACHINE			:number = 3;	// 激活机关
		public static INSTANCE_QUEST_TYPE_PROTECT_NPC			:number = 4;	// 守护NPC
		public static INSTANCE_QUEST_TYPE_ESCORT_NPC			:number = 5;	// 护送NPC
		public static INSTANCE_QUEST_TYPE_DEFENSE			:number = 6;	// 防守
		public static INSTANCE_QUEST_TYPE_BREAK_THROUGH			:number = 7;	// 闯关
		public static MAX_INSTANCE_QUEST_COUNT			:number = 12;
		// //////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 地图
		public static MAP_INT_FIELD_MAP_ID			:number = 0;	// 地图模板ID
		public static MAP_INT_FIELD_INSTANCE_ID			:number = 1;	// 实例ID
		public static MAP_INT_FIELD_LINE_NO			:number = 2;	// 分线ID
		public static MAP_INT_FIELD_WARID			:number = 2;	// 场次id
		public static MAP_INT_FIELD_KUAFU_TYPE			:number = 3;	// 跨服类型
		public static MAP_INT_FIELD_STATE			:number = 4;	// 0.地图大状态,1.地图小状态,2.地图自动复活时间,3预留状态
		public static MAP_INT_FIELD_KILL_NUM			:number = 5;	// 杀怪数
		public static MAP_INT_FIELD_RESERVE1			:number = 6;	// 保留字段1
		public static MAP_INT_FIELD_RESERVE2			:number = 7;	// 保留字段2
		public static MAP_INT_FIELD_RESERVE3			:number = 8;	// 保留字段3 当前层数
		public static MAP_INT_FIELD_RESERVE4			:number = 9;	// 保留字段4 判断副本是否初始化
		public static MAP_INT_FIELD_INSTANCE_WAVE			:number = 10;	// 波数2shorts(0:当前波数,1:总波数)
		public static MAP_INT_FIELD_QUESTS_START			:number = 11;	// 副本任务开始
		public static MAP_INT_FIELD_QUESTS_END			:number = 35;	// 副本任务结束
		public static MAP_INT_FIELD_QUESTS_PROCESS_START			:number = 35;	// 进度开始
		public static MAP_INT_FIELD_QUESTS_PROCESS_END			:number = 38;	// 进度结束
		public static MAP_INT_FIELD_CREATE_TM			:number = 38;	// 副本创建时间
		public static MAP_INT_FIELD_START_TM			:number = 39;	// 副本开始时间
		public static MAP_INT_FIELD_QUEST_END_TM			:number = 40;	// 副本任务结束时间
		public static MAP_INT_FIELD_END_TM			:number = 41;	// 副本结束时间
		public static MAP_INT_FIELD_INSTANCE_TYPE			:number = 42;	// 副本类型
		// 地图字符串部分
		public static MAP_STR_GENERAL_ID			:number = 4;
		public static MAP_STR_REWARD			:number = 5;	// 副本奖励物品字符串
		// 小怪陆续刷
		public static REFRESH_MONSTER_FIELD_ID			:number = 46;	// 2个short(0:当前已经刷的,1:总共需要刷多少怪)
		public static REFRESH_MONSTER_FIELD_INFO_START			:number = 47;	// 怪物信息开始2个short(0:entry,1:level)
		public static KUAFU_3V3_PLAYER_DAMAGE			:number = 0;	//  伤害
		public static KUAFU_3V3_PLAYER_SHOW_INFO			:number = 2;	//  2个byte, 1short(byte0:gender, byte1:hprate, short1:level)
		public static KUAFU_3V3_PLAYER_SETTLEMENT			:number = 3;	//  计算信息, 4bytes(0:击杀数量,1:死亡状态,2:所属阵营,3:积分)
		public static KUAFU_3V3_PLAYER_HONOR			:number = 4;	//  荣誉及全场最佳, 4bytes(0:获得荣誉, 1:全场最佳,2:保留,3:保留)
		public static MAX_KUAFU_3V3_INT_COUNT			:number = 5;	//  kuafu属性数量
		public static KUAFU_3V3_PLAYER_NAME			:number = 0;	// 玩家名称
		public static KUAFU_3V3_PLAYER_GUID			:number = 1;	// 玩家guid
		public static MAX_KUAFU_3V3_STR_COUNT			:number = 2;
		public static MAX_KUAFU_3V3_COUNT			:number = 6;
		//  跨服3v3匹配
		public static KUAFU_3V3_FIELDS_INT_INFO_START			:number = 43;	//  跨服数据开始
		public static KUAFU_3V3_FIELDS_INT_INFO_END			:number = 73;	//  3v3总共6个人
		public static KUAFU_3V3_FIELDS_STR_INFO_START			:number = 6;	//  字符串数据开始
		public static KUAFU_3V3_FIELDS_STR_INFO_END			:number = 18;	//  字符串数据结束
		//  仙府夺宝 玩家信息
		public static KUAFU_XIANFU_PLAYER_SETTLEMENT			:number = 0;	//  玩家战力
		public static KUAFU_XIANFU_PLAYER_MONEY			:number = 2;	//  元宝数据
		public static KUAFU_XIANFU_PLAYER_MONEY_CHANGED			:number = 4;	//  元宝改变值
		public static KUAFU_XIANFU_PLAYER_SHOW_INFO			:number = 6;	//  4个byte(byte0:宝箱数量, byte1:击杀人数, byte2:击杀BOSS数量,byte3:连杀次数)
		public static MAX_KUAFU_XIANFU_INT_COUNT			:number = 7;	//  kuafu属性数量
		public static KUAFU_XIANFU_PLAYER_NAME			:number = 0;	// 玩家名称
		public static KUAFU_XIANFU_PLAYER_GUID			:number = 1;	// 玩家guid
		public static MAX_KUAFU_XIANFU_STR_COUNT			:number = 2;
		public static KUAFU_XIANFU_BOSS_SHOW_INFO			:number = 0;	//  2 shorts(0:entry, 1:死亡状态)
		public static KUAFU_XIANFU_BOSS_BORN_INFO			:number = 1;	//  是否刷新
		public static KUAFU_XIANFU_BOSS_BORN_TIME			:number = 2;	//  刷新时间戳
		public static MAX_KUAFU_XIANFU_BOSS_INT_COUNT			:number = 3;
		public static MAX_KUAFU_XIANFU_COUNT			:number = 10;
		public static MAX_KUAFU_XIANFU_BOSS_COUNT			:number = 5;
		//  跨服仙府夺宝匹配
		public static KUAFU_XIANFU_FIELDS_INT_INFO_START			:number = 43;	//  跨服数据开始
		public static KUAFU_XIANFU_FIELDS_INT_INFO_END			:number = 113;	//  3v3总共6个人
		public static KUAFU_XIANFU_FIELDS_INT_BOSS_INDX			:number = 113;	// 当前的bossid
		public static KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_START			:number = 114;	// BOSS信息开始
		public static KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_END			:number = 129;
		public static KUAFU_XIANFU_FIELDS_HARD			:number = 129;	// 副本难度
		public static XIANFU_TEST_DUMMY_COUNT			:number = 130;	// 假人数量
		public static KUAFU_XIANFU_FIELDS_STR_INFO_START			:number = 6;	//  字符串数据开始
		public static KUAFU_XIANFU_FIELDS_STR_INFO_END			:number = 26;	//  字符串数据结束
		//  跨服组队玩家信息
		public static KUAFU_GROUP_INSTANCE_PLAYER_DAED_TIMES			:number = 0;	//  玩家信息(0:死亡次数)
		public static KUAFU_GROUP_INSTANCE_PLAYER_REBRON_CD			:number = 1;	// 原地复活cd
		public static MAX_KUAFU_GROUP_INSTANCE_PLAYER_INT_COUNT			:number = 2;	//  kuafu属性数量
		public static KUAFU_GROUP_INSTANCE_PLAYER_NAME			:number = 0;	// 玩家名称
		public static KUAFU_GROUP_INSTANCE_PLAYER_GUID			:number = 1;	// 玩家guid
		public static KUAFU_GROUP_INSTANCE_PLAYER_REWARDS			:number = 2;	// 玩家奖励
		public static MAX_KUAFU_GROUP_INSTANCE_PLAYER_STR_COUNT			:number = 3;
		public static MAX_GROUP_INSTANCE_PLAYER_COUNT			:number = 3;
		// 跨服组队
		public static KUAFU_GROUP_INSTANCE_FIELDS_HARD			:number = 43;	//  难度
		public static KUAFU_GROUP_INSTANCE_FIELDS_PART			:number = 44;	//  组队副本的第几部分
		public static KUAFU_GROUP_INSTANCE_INT_FIELDS_PLAYER_INFO_START			:number = 45;
		public static KUAFU_GROUP_INSTANCE_INT_FIELDS_PLAYER_INFO_END			:number = 51;
		public static KUAFU_GROUP_INSTANCE_STR_FIELDS_PLAYER_INFO_START			:number = 45;
		public static KUAFU_GROUP_INSTANCE_STR_FIELDS_PLAYER_INFO_END			:number = 54;
		public static DOUJIANTAI_FIELDS_INT_RANK			:number = 43;	//  2 shorts (0:自己的排名, 1:对手的排名)
		public static DOUJIANTAI_FIELDS_INT_COMBAT_WIN_INFO			:number = 44;	//  2 shorts (0:历史最大连胜, 1:当前连胜)
		public static XIULIANCHANG_FIELDS_INT_RANK			:number = 43;	//  敌人斗剑台排行
		public static XIULIANCHANG_FIELDS_INT_ROBOT_ID			:number = 44;	//  敌人机器人序号
		public static XIULIANCHANG_FIELDS_INT_LEVEL			:number = 45;	// 敌人等级 结算经验用
		public static XIULIANCHANG_FIELDS_STR_INFO_GUID			:number = 6;	// 敌人guid
		public static XIULIANCHANG_FIELDS_STR_INFO_CONTENT			:number = 7;	// 敌人属性content  
		public static XIULIANCHANG_FIELDS_STR_INFO_NAME			:number = 8;	// 敌人名称
		// VIP BOSS
		public static VIP_INSTANCE_FIELD_ID			:number = 43;	//  0:VIP副本序号,1:副本难度
		public static MAP_MASS_BOSS_INT_FIELD_ID			:number = 43;	// 全民bossid
		public static WORLDBOSS_FIELDS_WAIT_TIME			:number = 43;	// 报名等待时间戳
		public static WORLDBOSS_FIELDS_BORN_TIME			:number = 44;	// 刷新等待时间戳
		public static RES_INSTANCE_FIELD_ID			:number = 43;	// 资源副本的索引
		// 世界冒险
		public static TRIAL_INSTANCE_FIELD_CURSOR			:number = 43;	// 当前已经刷了多少波了
		public static TRIAL_INSTANCE_FIELD_SECTION_ID			:number = 44;	// 关卡id
		public static TRIAL_INSTANCE_FIELD_ORDER			:number = 45;	// 刷怪优先级序号(1个byte存一个数据)
		public static TRIAL_INSTANCE_FIELD_BOSS_REFRESHED			:number = 47;	// 是否已经刷怪
		public static TRIAL_INSTANCE_FIELD_LAST_RANDOM_TIMESTAMP			:number = 48;	// 最近随机刷怪时间戳
		// 家族场景
		public static FACTION_INSTANCE_FIELD_GUID			:number = 6;	//  家族GUID string
		// 家族首领挑战场景
		public static FACTION_BOSSDEFENSE_INSTANCE_FIELD_BUILDING_LV			:number = 43;	// 家族建筑等级
		public static FACTION_BOSSDEFENSE_INSTANCE_FIELD_INDEX			:number = 44;	// boss点 index
		public static FACTION_BOSSDEFENSE_INSTANCE_FIELD_POOL_ID			:number = 45;	// 怪物池 id
		public static FACTION_BOSSDEFENSE_INSTANCE_FIELD_HP			:number = 46;	// 怪物剩余hp
		public static FACTION_BOSSDEFENSE_INSTANCE_FIELD_PLAYER_GUID			:number = 6;	//  玩家GUID string
		public static FACTION_BOSSDEFENSE_INSTANCE_FIELD_FACTION_GUID			:number = 7;	//  家族GUID string
		// 家族无尽远征场景
		public static FACTION_TOWER_INSTANCE_FIELD_FLOOR			:number = 43;	//  当前层数
		public static FACTION_TOWER_INSTANCE_FIELD_BUFF			:number = 44;	//  玩家获得的buffeffect_id
		public static FACTION_TOWER_INSTANCE_FIELD_DEBUFF			:number = 45;	// 玩家获得的debuffeffect_id
		public static FACTION_TOWER_INSTANCE_FIELD_MONSTER_NUM			:number = 46;	// 当前怪物数量
		// 试炼塔
		public static TRIAL_INSTANCE_FIELD_ID			:number = 43;	//  当前层数
		//  桃花迷阵最大刷新次数
		public static TAOHUA_REFRESH_TIMES			:number = 10;
		// 桃花迷阵地图数据
		public static TAOHUA_INT_FIELD_REFRESH_TIMES			:number = 43;	// 桃花迷阵已经刷新次数
		public static TAOHUA_INT_FIELD_BOSS_CURR_HP			:number = 44;	// BOSS当前血量
		public static TAOHUA_STR_FIELD_REAL_BOSS_GUID			:number = 5;	// BOSS真身GUID
		// 塔的最大层数
		public static TOWER_MAX_FLOOR			:number = 2;
		// 塔怪每层击杀数量
		public static TAGUAI_INT_FIELD_FIRST_FLOOR			:number = 43;	// 第一层的信息
		// 战斗信息整形字符型枚举
		// 貌似没必要,随便留一个吧
		public static FIGHTING_INFO_STRING_CASTER			:number = 0;	// 施法者
		public static FIGHTING_INFO_STRING_TARGET			:number = 1;	// 目标
		public static MAX_FIGHTING_INFO_STRING			:number = 2;
		// 战斗信息最大数量
		public static MAX_FIGHTING_INFO_COUNT			:number = 100;
		// 战斗信息整形字段枚举
		public static FIGHTING_INFO_INT_VALUES			:number = 0;	// 伤害或者治疗 治疗发负数
		public static FIGHTING_INFO_INT_UINT8			:number = 2;	// 0:是否被杀 1:施法者生物类型（玩家还是生物）2:目标生物类型（玩家还是生物） 3:伤害类型(暴击、闪避之类的)
		public static FIGHTING_INFO_INT_SPELL_ID			:number = 3;	// 技能id
		public static FIGHTING_INFO_INT_HP			:number = 4;	// 技能计算完以后，生物剩余血量
		public static FIGHTING_INFO_INT_RESERVE_0			:number = 5;	// 预留
		public static FIGHTING_INFO_INT_RESERVE_1			:number = 6;	// 预留	
		public static FIGHTING_INFO_INT_RESERVE_2			:number = 7;	// 预留
		public static FIGHTING_INFO_INT_RESERVE_3			:number = 8;	// 预留	
		public static MAX_FIGHTING_INFO_INT			:number = 9;
		// 战斗信息字段
		public static MAX_FIGHTING_INFO_INT_NOW_INDEX			:number = 0;	// 当前战斗力信息下标用到第几个战斗信息了
		public static MAX_FIGHTING_INFO_INT_START			:number = 1;
		public static MAX_FIGHTING_INFO_INT_FIELD			:number = 901;
		public static FIGHTING_INFO_STRING_FIELD_START			:number = 4;
		public static MAX_FIGHTING_INFO_STRING_FIELD			:number = 204;
		// 查询用的玩家信息binlog
		public static QUERY_PLAYER_INT_UINT16			:number = 0;	// 0 等级，1 宝石等级
		public static QUERY_PLAYER_INT_BYTE1			:number = 1;	// 0 头像，1 发型，2 种族，3 性别
		public static QUERY_PLAYER_INT_BYTE2			:number = 2;	// 0 阵营，1 是否在线，2 称号,3 vip
		//  基础属性
		public static QUERY_PLAYER_INT_BASE_ATTR_START			:number = 3;	// 玩家基本属性开始
		public static QUERY_PLAYER_INT_BASE_ATTR_END			:number = 21;	// 玩家基本属性结束
		public static QUERY_PLAYER_INT_FIXED_ATTR_START			:number = 21;	// 玩家固定属性开始
		public static QUERY_PLAYER_INT_FIXED_ATTR_END			:number = 39;	// 玩家固定属性结束	
		public static QUERY_PLAYER_INT_LUCKY			:number = 39;	// 幸运
		public static QUERY_PLAYER_INT_MEILI			:number = 41;	// 魅力
		public static QUERY_PLAYER_INT_BEAR			:number = 43;	// 负重
		public static QUERY_PLAYER_INT_POISON			:number = 45;	// 毒
		public static QUERY_PLAYER_INT_ICE			:number = 47;	// 冰
		public static QUERY_PLAYER_MOVESPEED			:number = 49;	// 移动速度
		public static QUERY_PLAYER_PHYSICAL			:number = 51;	// 体力
		public static QUERY_PLAYER_INT_FORCE			:number = 53;	// 战斗力
		public static QUERY_PLAYER_ONLINE_TIME			:number = 55;	// 总在线时长
		//  身上的装备
		public static QUERY_PLAYER_INT_EQUIPMENT			:number = 56;
		public static QUERY_PLAYER_INT_EQUIPMENT_END			:number = 76;
		public static QUERY_PLAYER_INT_FLAG			:number = 76;	// 查询某些标志位
		public static QUERY_PLAYER_INT_FORCE_LEVEL			:number = 77;	// 等级战斗力PLAYER_INT_PIFENG_ZIZHI_FORCE
		public static QUERY_PLAYER_INT_FORCE_ITEM			:number = 79;	// 装备战斗力
		public static QUERY_PLAYER_INT_FORCE_FACTION			:number = 81;	// 帮派战斗力
		public static QUERY_PLAYER_INT_FLAG_TYPE			:number = 83;	// 当前玩家查询类型标志
		public static QUERY_PLAYER_INT_FORGING_STRENG			:number = 84;	// 0 查询玩家强化等级，1 预留 16位
		public static QUERY_PLAYER_STRING_GUID			:number = 4;	// 不要直接放到guid去，怕混乱
		public static QUERY_PLAYER_STRING_NAME			:number = 5;	// 玩家名字
		public static QUERY_PLAYER_STRING_FACTION_ID			:number = 6;	// 帮派ID
		public static QUERY_PLAYER_STRING_FACTION_NAME			:number = 7;	// 帮派名称
		public static MAX_QUERY_PLAYER_STRING_FIELD			:number = 8;
		// ///////////////////////////////////查看物品//////////////////////////////////////////////////////////////////////////
		// 查看物品下标
		// //////////////////int部分///////////////////////////////////////
		public static ITEM_QUERY_INT_FIELD_COUNT			:number = 0;
		// //////////////////string部分///////////////////////////////////////
		public static ITEM_QUERY_STR_FIELD_START			:number = 4;
		// 礼包信息记录类型枚举
		public static GIFTPACKS_INFO_INT_ID			:number = 0;	// 礼包ID
		public static GIFTPACKS_INFO_INT_START_TIME			:number = 1;	// 发放时间
		public static GIFTPACKS_INFO_INT_END_TIME			:number = 2;	// 结束时间
		public static GIFTPACKS_INFO_INT_BYTE			:number = 3;	// 0,礼包类型，1，领取状态,2 已阅读,3是否删除
		public static MAX_GIFTPACKS_INFO_INT			:number = 4;
		public static GIFTPACKS_INFO_STRING_GIFT_NAME			:number = 0;	// 礼包名称
		public static GIFTPACKS_INFO_STRING_GIFT_DESC			:number = 1;	// 礼包说明
		public static GIFTPACKS_INFO_STRING_GIFT_FROM			:number = 2;	// 礼包出处，当玩家赠送时填写玩家名字，默认为空，系统赠送
		public static GIFTPACKS_INFO_STRING_GIFT_ITEM			:number = 3;	// 礼包物品集合
		public static MAX_GIFTPACKS_INFO_STRING			:number = 4;
		// 礼包信息最多条数
		public static MAX_GIFTPACKS_INFO_COUNT			:number = 100;
		// 礼包信息binlog
		public static MAX_GIFTPACKS_INFO_INT_NOW_INDEX			:number = 0;	// 当前礼包信息下标索引
		public static GIFTPACKS_INT_FIELD_BEGIN			:number = 1;
		public static MAX_GIFTPACKS_INT_FIELD			:number = 401;
		public static GIFTPACKS_STRING_FIELD_BEGIN			:number = 4;
		public static MAX_GIFTPACKS_STRING_FIELD			:number = 404;
		// 排行类型
		public static RANK_TYPE_POWER			:number = 0;	// 战斗力排行
		public static RANK_TYPE_LEVEL			:number = 1;	// 等级排行
		public static RANK_TYPE_MONEY			:number = 2;	// 财富排行
		public static RANK_TYPE_ONLINE_TIME			:number = 3;	// 在线时长排行
		public static RANK_TYPE_TRIAL			:number = 4;	// 试炼塔排行
		public static RANK_TYPE_FACTION			:number = 5;	// 家族排行
		public static RANK_TYPE_DIVINE			:number = 6;	// 神兵排行
		public static RANK_TYPE_MOUNT			:number = 7;	// 坐骑排行
		public static RANK_TYPE_SINGLE_PVP			:number = 8;	// 单人PVP排行
		public static RANK_TYPE_WINGS			:number = 9;	// 翅膀排行
		public static MAX_RANK_TYPE			:number = 10;
		// 特殊类型排行榜
		public static RANK_TYPE_DOUJIANTAI			:number = 11;	// 斗剑台排行
		// 单个排行榜最大排名个数
		public static RANK_LIST_MAX_VALUES			:number = 100;
		public static RANK_LIST_MAX_SHOW			:number = 4;
		// 排行榜个体binlog下标
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_TYPE			:number = 0;	// 排行榜类型
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_RANKING			:number = 1;	// 名次
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE			:number = 2;	// byte 0，性别，数量
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE2			:number = 3;	// 通用字段
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_TITLE			:number = 4;	// 称号
		// 排行榜
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE			:number = 5;	// 战斗力
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL			:number = 7;	// 等级
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_MONEY			:number = 8;	// 铜钱
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_ONLINE_TIME			:number = 10;	// 在线时长
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_TRIAL			:number = 11;	// 试炼塔层数
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW			:number = 12;	// 外观列表开始
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW_END			:number = 16;	// 外观结束
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_LIKE			:number = 17;	// 点赞数
		public static RANK_LIST_CURRENT_OBJ_INT_FIELD_WING			:number = 18;	// 翅膀id
		public static RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID			:number = 4;
		public static RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID			:number = 5;	// 玩家guid
		public static RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_NAME			:number = 6;	// 玩家名字
		public static RANK_LIST_CURRENT_OBJ_STR_FIELD_FACTION_NAME			:number = 7;	// 帮派名字
		public static RANK_LIST_INT_FIELD_FACTION_LEV			:number = 2;	// byte 0，性别
		public static RANK_LIST_INT_FIELD_FACTION_COUNT			:number = 3;
		public static RANK_LIST_INT_FIELD_FACTION_BYTE			:number = 4;	// icon minlev
		public static RANK_LIST_STR_FIELD_FACTION_GUID			:number = 4;	// 帮派GUID
		public static RANK_LIST_STR_FIELD_FACTION_NAME			:number = 5;	// 帮派名字
		public static RANK_LIST_STR_FIELD_FACTION_SQGG			:number = 6;	// 帮派申请公告
		public static ITEM_SHOW_TYPE_DEFAULT			:number = 0;	// 默认显示
		public static ITEM_SHOW_TYPE_MINI_QUEST_BAR			:number = 1;	// 小任务面板
		public static ITEM_SHOW_TYPE_MINI_QUEST_DAILY2			:number = 2;	// 日常任务面板
		// 弹窗公告记录类型枚举
		public static RIGHTFLOAT_INFO_INT_ID			:number = 0;	// 公告ID
		public static RIGHTFLOAT_INFO_INT_START_TIME			:number = 1;	// 起始时间
		public static RIGHTFLOAT_INFO_INT_END_TIME			:number = 2;	// 结束时间
		public static RIGHTFLOAT_INFO_INT_ZONE_1			:number = 3;	// 0-7点
		public static RIGHTFLOAT_INFO_INT_ZONE_2			:number = 4;	// 8-13点
		public static RIGHTFLOAT_INFO_INT_ZONE_3			:number = 5;	// 14-23点
		public static RIGHTFLOAT_INFO_INT_BYTE			:number = 6;	// 0 弹窗设置,1 公告状态,2 预留,3 预留
		public static RIGHTFLOAT_INFO_INT_ADD_TIME			:number = 7;	// 添加时间
		public static MAX_RIGHTFLOAT_INFO_INT			:number = 8;
		public static RIGHTFLOAT_INFO_STRING_SUBJECT			:number = 0;	// 标题
		public static RIGHTFLOAT_INFO_STRING_CONTENT			:number = 1;	// 内容
		public static RIGHTFLOAT_INFO_STRING_LINK			:number = 2;	// 链接地址
		public static MAX_RIGHTFLOAT_INFO_STRING			:number = 3;
		// 弹窗信息最多条数
		public static MAX_RIGHTFLOAT_INFO_COUNT			:number = 100;
		// 弹窗公告信息binlog
		public static MAX_RIGHTFLOAT_INFO_INT_NOW_INDEX			:number = 0;	// 当前弹窗公告信息下标索引
		public static RIGHTFLOAT_INT_FIELD_START			:number = 1;
		public static MAX_RIGHTFLOAT_INT_FIELD			:number = 801;
		public static RIGHTFLOAT_STRING_FIELD_START			:number = 4;
		public static MAX_RIGHTFLOAT_STRING_FIELD			:number = 304;
		// 限时活动binlog
		public static LIMIT_ACTIVITY_INT_FIELD_VERSION			:number = 0;	// 活动版本号
		public static LIMIT_ACTIVITY_INT_FIELD_START_TIME			:number = 1;	// 活动开始时间
		public static LIMIT_ACTIVITY_INT_FIELD_END_TIME			:number = 2;	// 活动结束时间
		public static LIMIT_ACTIVITY_INT_FIELD_RECHARGE_SUM			:number = 3;	// 充值总数
		public static LIMIT_ACTIVITY_INT_FIELD_RECHARGE_TIME			:number = 4;	// 最后充值时间
		public static LIMIT_ACTIVITY_INT_FIELD_REWARD_COUNT			:number = 100;	// 活动领取计数开始
		public static LIMIT_ACTIVITY_INT_FIELD_REWARD_COUNT_END			:number = 500;	// 活动领取计数结束
		public static LIMIT_ACTIVITY_STRING_FIELD_RECHARGE_ID			:number = 4;	// 最后充值ID
		public static LIMIT_ACTIVITY_STRING_FIELD_CLIENT_CONFIG			:number = 5;	// 客户端配置
		// 公告信息最多条数
		public static MAX_NOTICE_MESSAGE_NUMBER			:number = 100;
		// 公告信息类型
		public static NOTICE_MESSAGE_INFO_TYPE_FISHING			:number = 0;	// 钓鱼公告
		public static NOTICE_MESSAGE_INFO_TYPE_MINING			:number = 1;	// 矿洞公告
		public static NOTICE_MESSAGE_INFO_TYPE_WORLD_BOSS			:number = 2;	// 世界boss掉落
		public static NOTICE_MESSAGE_INFO_TYPE_KAIFUJIJIN			:number = 3;	// 开服基金公告
		public static MAX_MESSAGE_INFO_TYPE			:number = 4;
		// 公告信息binlog
		public static NOTICE_MESSAGE_INT_FIELD_INDEX			:number = 0;	// 公告位置索引
		public static NOTICE_MESSAGE_INT_FIELD_INDEX_END			:number = 4;	// 公告索引位置结束
		public static NOTICE_MESSAGE_STRING_FIELD_START			:number = 4;	// 公告信息内容开始
		public static NOTICH_MESSAGE_STRING_FIELD_END			:number = 404;	// 公告信息内容结束
		// 系统邮件信息记录类型枚举
		public static SYSTEM_MAIL_INFO_INT_ID			:number = 0;	// 礼包ID
		public static SYSTEM_MAIL_INFO_INT_START_TIME			:number = 1;	// 发放时间
		public static SYSTEM_MAIL_INFO_INT_END_TIME			:number = 2;	// 结束时间
		public static SYSTEM_MAIL_INFO_INT_TYPE			:number = 3;	// 礼包类型
		public static MAX_SYSTEM_MAIL_INFO_INT			:number = 4;
		public static SYSTEM_MAIL_INFO_STRING_NAME			:number = 0;	// 系统邮件名称
		public static SYSTEM_MAIL_INFO_STRING_DESC			:number = 1;	// 系统邮件说明
		public static SYSTEM_MAIL_INFO_STRING_FROM			:number = 2;	// 系统邮件出处，当玩家赠送时填写玩家名字，默认为空，系统赠送
		public static SYSTEM_MAIL_INFO_STRING_ITEM			:number = 3;	// 礼包物品集合
		public static MAX_SYSTEM_MAIL_INFO_STRING			:number = 4;
		// 系统邮件信息最多条数
		public static MAX_SYSTEM_MAIL_INFO_COUNT			:number = 8192;
		//  系统邮件(对全服都有效的)
		public static SYSTEM_MAIL_COUNT			:number = 0;	// 系统邮件个数
		public static MAX_SYSTEM_MAIL_INFO_INT_NOW_INDEX			:number = 1;	// 当前系统邮件信息下标索引
		public static SYSTEM_MAIL_INT_FIELD_BEGIN			:number = 2;
		public static SYSTEM_MAIL_INT_FIELD_END			:number = 32770;
		public static SYSTEM_MAIL_STRING_FIELD_BEGIN			:number = 4;
		public static SYSTEM_MAIL_STRING_FIELD_END			:number = 32772;
		// 离线邮件最多条数
		public static MAX_OFFLINE_MAIL_INFO_COUNT			:number = 16384;
		//  离线邮件存储地方
		public static OFFLINE_MAIL_STORE_RANK_LEVEL			:number = 0;	// 等级排行榜离线邮件存储
		public static MAX_OFFLINE_MAIL_STORE_COUNT			:number = 1;
		// 托管操作
		public static HOSTING_OPT_TYPE_APPLY			:number = 0;	// 托管申请
		public static HOSTING_OPT_TYPE_AGREED			:number = 1;	// 托管同意
		public static HOSTING_OPT_TYPE_CANCEL			:number = 2;	// 托管取消
		public static HOSTING_OPT_TYPE_LOGIN			:number = 3;	// 托管登录
		public static HOSTING_OPT_TYPE_REFUSE			:number = 4;	// 托管拒绝
		public static HOSTING_OPT_TYPE_DUE_TO			:number = 5;	// 托管到期
		public static HOSTING_OPT_TYPE_APPLY_DUE_TO			:number = 6;	// 托管申请到期
		// 部位信息个数
		public static MAX_EQUIP_PART_NUMBER			:number = 10;
		// 一个部位的宝石个数
		public static ONE_EQUIP_PART_GEM_NUMBER			:number = 6;
		//  一个装备部位信息类型
		public static EQUIP_PART_OPT_TYPE_STRENGTH_LEVEL_OFFSET			:number = 0;	// 强化等级偏移值
		public static EQUIP_PART_OPT_TYPE_GEM_INFO_OFFSET			:number = 1;	// 宝石信息偏移值
		public static EQUIP_PART_OPT_TYPE_GEM_LEVEL_OFFSET			:number = 0;	// 宝石信息中宝石等级偏移值
		public static EQUIP_PART_OPT_TYPE_GEM_EXP_OFFSET			:number = 1;	// 宝石信息中宝石经验偏移值
		public static EQUIP_PART_OPT_TYPE_ONE_GEM_INFO_LENGTH			:number = 2;	// 一个宝石信息的长度
		public static EQUIP_PART_OPT_TYPE_ONE_PART_INFO_LENGTH			:number = 13;	// 一个装备部位的信息长度
		public static EQUIP_PART_OPT_TYPE_PARTS_INFO_LENGTH			:number = 130;	// 所有装备部位总信息长度 
		//  业务BinLog
		public static APPD_LOGICAL_INFO_INT_FIELD_STRENGTH_START			:number = 0;	// 部位信息的起始位置
		public static APPD_LOGICAL_INFO_INT_FIELD_STRENGTH_END_EXCLUDE			:number = 130;	// 装备部位的边界
		// 文本解析类型
		public static TEXT_TYPE_POSITION			:number = 1;	// 坐标
		public static TEXT_TYPE_SUIT			:number = 2;	// 装备
		public static TEXT_TYPE_GROUP			:number = 3;	// 加入队伍
		public static TEXT_TYPE_INSTANCE			:number = 4;	// 加入副本
		//  被动技能效果类型
		public static PASSIVE_EFFECT_TYPE_SPELL_AMPLIFY			:number = 1;	// 增强技能效果
		public static PASSIVE_EFFECT_TYPE_ADD_BUFF			:number = 2;	// 增加buff效果
		public static PASSIVE_EFFECT_TYPE_CHANGE_SPELL			:number = 3;	// 替换技能效果
		public static PASSIVE_EFFECT_TYPE_PLAYER_ATTR			:number = 4;	// 提高人物属性
		public static PASSIVE_EFFECT_TYPE_ADDITIONAL_SPELL			:number = 5;	// 释放额外技能
		public static PASSIVE_EFFECT_TYPE_PLAYER_LOOT_ATTR			:number = 6;	// 获得属性战利品
		//  被动技能触发类型
		public static PASSIVE_DISPATCH_TYPE_FOREVER			:number = 0;	// 永久
		public static PASSIVE_DISPATCH_TYPE_ATTR_CHANGE			:number = 1;	// 属性改变
		public static PASSIVE_DISPATCH_TYPE_HIT			:number = 2;	// 攻击命中敌人
		public static PASSIVE_DISPATCH_TYPE_HURT			:number = 3;	// 受到攻击
		public static PASSIVE_DISPATCH_TYPE_DEAD			:number = 4;	// 死亡时触发
		public static PASSIVE_DISPATCH_TYPE_ENEMY_DEAD			:number = 5;	// 敌方死亡
		public static PASSIVE_DISPATCH_TYPE_ON_BUFF			:number = 6;	// 受到buff的时候触发
		public static PASSIVE_DISPATCH_TYPE_ENEMY_ON_BUFF			:number = 7;	// 敌方拥有某个buff的时候触发
		// 系统模块
		public static MODULE_SETTING			:number = 101;	// 设置
		public static MODULE_BAG			:number = 102;	// 背包
		public static MODULE_RONGLIAN			:number = 103;	// 熔炼
		public static MODULE_QUEST			:number = 104;	// 任务
		public static MODULE_DAILY_TASKS			:number = 105;	// 日常任务
		public static MODULE_CHAT			:number = 106;	// 聊天
		public static MODULE_MAIL			:number = 107;	// 邮件
		public static MODULE_MAP			:number = 108;	// 地图
		public static MODULE_STRENGTH			:number = 109;	// 我要变强
		public static MODULE_CHATPERSON			:number = 110;	// 私聊
		public static MODULE_ACTIVE			:number = 111;	// 活跃
		public static MODULE_MONEYTREE			:number = 112;	// 摇钱树
		public static MODULE_ROLE			:number = 201;	// 角色
		public static MODULE_SPELL			:number = 202;	// 技能
		public static MODULE_DIVINE			:number = 203;	// 法宝
		public static MODULE_FASHION			:number = 204;	// 时装
		public static MODULE_MOUNT			:number = 205;	// 坐骑
		public static MODULE_MIX			:number = 206;	// 炼器
		public static MODULE_WING			:number = 207;	// 翅膀
		public static MODULE_TCM			:number = 208;	// 经脉
		public static MODULE_SOCIAL			:number = 301;	// 社交
		public static MODULE_FACTION			:number = 302;	// 家族
		public static MODULE_RANK			:number = 303;	// 排行榜
		public static MODULE_FACTIONMAIN			:number = 304;	// 家族-家族主殿
		public static MODULE_FACTIONSKILL			:number = 305;	// 家族-技能大厅
		public static MODULE_FACTIONACTIVE			:number = 306;	// 家族-活动大厅
		public static MODULE_FACTIONBOX			:number = 307;	// 家族-家族宝库
		public static MODULE_MALL			:number = 401;	// 商城
		public static MODULE_VIP			:number = 402;	// VIP特权
		public static MODULE_INSTANCE			:number = 501;	// 副本
		public static MODULE_WORLD_RISK			:number = 502;	// 世界冒险
		public static MODULE_ARENA			:number = 503;	// 竞技
		public static MODULE_BOSS			:number = 504;	// BOSS
		public static MODULE_WELFARE			:number = 601;	// 福利
		public static MODULE_OPENSERVICE			:number = 701;	// 开服活动
		public static MODULE_FIRST_RECHARGE			:number = 801;	// 首冲
		public static MODULE_SETTING_SYSTEM			:number = 1;	// 设置
		public static MODULE_BAG_ITEM			:number = 1;	// 背包
		public static MODULE_RONGLIAN_ALL			:number = 1;	// 熔炼
		public static MODULE_QUEST_MAIN			:number = 1;	// 主线
		public static MODULE_QUEST_EXTENSION			:number = 2;	// 支线
		public static MODULE_QUEST_ACTIVITY			:number = 3;	// 活动
		public static MODULE_DAILY_TASKS_ALL			:number = 1;	// 日常任务
		public static MODULE_CHAT_ALL			:number = 1;	// 聊天
		public static MODULE_MAIL_ALL			:number = 1;	// 邮件
		public static MODULE_MAP_REGION			:number = 1;	// 区域
		public static MODULE_MAP_WORLD			:number = 2;	// 世界
		public static MODULE_STRENGTH_ALL			:number = 1;	// 我要变强
		public static MODULE_CHATPERSON_ALL			:number = 1;	// 聊天
		public static MODULE_ACTIVE_ALL			:number = 1;	// 活跃
		public static MODULE_MONEYTREE_ALL			:number = 1;	// 摇钱树
		public static MODULE_ROLE_ATTR			:number = 1;	// 角色属性
		public static MODULE_ROLE_ACHIEVE			:number = 2;	// 角色成就
		public static MODULE_ROLE_TITLE			:number = 3;	// 角色称号
		public static MODULE_SPELL_ALL			:number = 1;	// 技能
		public static MODULE_DIVINE_ALL			:number = 1;	// 法宝
		public static MODULE_FASHION_CLOTHES			:number = 1;	// 衣服
		public static MODULE_FASHION_WEAPON			:number = 2;	// 武器
		public static MODULE_MOUNT_UPGRADE			:number = 1;	// 升阶
		public static MODULE_MOUNT_LEVEL			:number = 2;	// 升级
		public static MODULE_MOUNT_SKILL			:number = 3;	// 技能
		public static MODULE_MOUNT_ILLUSION			:number = 4;	// 幻化
		public static MODULE_MIX_STRENGTH			:number = 1;	// 强化
		public static MODULE_MIX_POLISHED			:number = 2;	// 精炼
		public static MODULE_MIX_GEM			:number = 3;	// 宝石
		public static MODULE_MIX_WASH			:number = 4;	// 洗练
		public static MODULE_WING_UPGRADE			:number = 1;	// 翅膀进阶
		public static MODULE_WING_STRENGTH			:number = 2;	// 翅膀强化
		public static MODULE_TCM_ALL			:number = 1;	// 角色经脉
		public static MODULE_SOCIAL_FRIEND			:number = 1;	// 好友
		public static MODULE_SOCIAL_ENEMY			:number = 2;	// 仇人
		public static MODULE_FACTION_RECRUIT			:number = 1;	// 家族招募
		public static MODULE_FACTION_CREATE			:number = 2;	// 创建家族
		public static MODULE_FACTION_MEMBER			:number = 3;	// 家族成员
		public static MODULE_FACTION_FUNCTION			:number = 4;	// 家族功能
		public static MODULE_RANK_LOCAL			:number = 1;	// 本服排行
		public static MODULE_RANK_KUAFU			:number = 2;	// 跨服排行
		public static MODULE_FACTIONMAIN_ALL			:number = 1;	// 家族主殿
		public static MODULE_FACTIONSKILL_ALL			:number = 1;	// 技能大厅
		public static MODULE_FACTIONACTIVE_TRIAL			:number = 1;	// 家族远征
		public static MODULE_FACTIONACTIVE_BOSS			:number = 2;	// 家族boss
		public static MODULE_FACTIONBOX_DEVOTE			:number = 1;	// 家族宝库
		public static MODULE_FACTIONBOX_ITEM			:number = 2;	// 家族仓库
		public static MODULE_MALL_GOLD			:number = 1;	// 元宝商城
		public static MODULE_MALL_SCORE			:number = 2;	// 积分商店
		public static MODULE_MALL_RECHARGE			:number = 3;	// 充值
		public static MODULE_VIP_ALL			:number = 1;	// VIP特权
		public static MODULE_INSTANCE_PLOT			:number = 1;	// 剧情副本
		public static MODULE_INSTANCE_RES			:number = 2;	// 资源副本
		public static MODULE_INSTANCE_TRIAL			:number = 3;	// 试炼塔
		public static MODULE_INSTANCE_TEAM			:number = 4;	// 多人副本
		public static MODULE_WORLD_RISK_MAIN			:number = 1;	// 世界冒险
		public static MODULE_ARENA_DOUJIANTAI			:number = 1;	// 斗剑台(1V1)
		public static MODULE_ARENA_XIANMO			:number = 2;	// 仙魔道(3V3)
		public static MODULE_ARENA_XIANFU			:number = 3;	// 仙府夺宝
		public static MODULE_ARENA_RANK			:number = 4;	// 排位赛
		public static MODULE_BOSS_WORLD_BOSS			:number = 2;	// 世界BOSS
		public static MODULE_BOSS_RISK_BOSS			:number = 2;	// BOSS挑战
		public static MODULE_WELFARE_MONTH			:number = 1;	// 月签到
		public static MODULE_WELFARE_LEVEL			:number = 2;	// 升级奖励
		public static MODULE_WELFARE_SEVEN			:number = 3;	// 七日大礼
		public static MODULE_WELFARE_RECHARGE			:number = 4;	// 充值返利
		public static MODULE_WELFARE_CONSUME			:number = 5;	// 消费有奖
		public static MODULE_OPENSERVICE_SEVEN			:number = 1;	// 七日目标
		public static MODULE_OPENSERVICE_DRAW			:number = 2;	// 开服寻宝
		public static MODULE_OPENSERVICE_EVERYDAY			:number = 3;	// 每日礼包
		public static MODULE_OPENSERVICE_NEW			:number = 4;	// 新手礼包
		public static MODULE_FIRST_RECHARGE_ALL			:number = 1;	// 首冲
		public static MERIDIAN_EXP_SOURCE_GROUP_INSTANCE			:number = 1;	// 	跨服副本
		public static MERIDIAN_EXP_SOURCE_TALISMAN_ZHULING			:number = 2;	// 	法宝注灵
		public static MERIDIAN_EXP_SOURCE_WINGS_STRENGTH			:number = 3;	// 	翅膀强化
		//  活跃度类型
		public static VITALITY_TYPE_SMELT_EQUIP			:number = 1;	// 熔炼
		public static VITALITY_TYPE_RES_INSTANCE			:number = 2;	// 资源副本
		public static VITALITY_TYPE_TRIAL_INSTANCE			:number = 3;	// 试炼塔
		public static VITALITY_TYPE_GROUP_INSTANCE			:number = 4;	// 多人副本
		public static VITALITY_TYPE_MASS_BOSS			:number = 5;	// BOSS挑战
		public static VITALITY_TYPE_WORLD_BOSS			:number = 6;	// 世界BOSS
		public static VITALITY_TYPE_FACTION_BOSS			:number = 7;	// 家族BOSS
		public static VITALITY_TYPE_FACTION_TOWER			:number = 8;	// 家族远征
		public static VITALITY_TYPE_FACTION_DONATE			:number = 9;	// 家族贡献
		public static VITALITY_TYPE_DOUJIANTAI			:number = 10;	// 斗剑台
		public static VITALITY_TYPE_SINGLE_PVP			:number = 11;	// 排位赛
	}
