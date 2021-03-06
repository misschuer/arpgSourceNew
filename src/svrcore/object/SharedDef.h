#ifndef _SHARED_DEF_H
#define _SHARED_DEF_H

#define MAX_MONEY 2000000000000000				//最大金额数，超过下线再上就白瞎
#define MAX_MONEY_TRUE 4000000000000000			//最大金额数.真。超过就不再往上加
#define MAX_BUFF_DURATION	65535				//无限BUFF时间

#define INIT_QUEST_ID 1				

#define ZHUCHENG_DITU_ID 1				//主城地图ID
#define ZHUCHENG_FUHUO_X 141				//主城复活点
#define ZHUCHENG_FUHUO_Y 163				//主城复活点

#define BORN_MAP 1001	//出生地图
#define BORN_X 143	//出生坐标x 
#define BORN_Y 113	//出生坐标y
#define BORN_OR 2	//出生朝向
#define BORN_LV 1	//出生等级

#define VIP_MAX_LEVEL 15	//vip最大等级


#define MAX_RMB_PLAYER_LEVEL 6			//最大的RMB等级

#define PLAYER_TALISMAN_SLOT_COUNT 5				//玩家法宝装备位上限

//服务器类型枚举
enum ESERVER_TYPE
{
	WORLD_SERVER_TYPE_GAME			= 0,	//游戏服
	WORLD_SERVER_TYPE_PK			= 1,	//pk服
};

//跨服类型枚举
enum EKUAFU_TYPE
{
	KUAFU_TYPE_NONE				= 0,
	KUAFU_TYPE_FENGLIUZHEN		= 1,	// 跨服风流镇
	KUAFU_TYPE_XIANFU			= 2,	// 跨服仙府夺宝
	KUAFU_TYPE_PLUNDER			= 3,	// 跨服家族掠夺
	KUAFU_TYPE_GROUP_INSTANCE	= 4,	// 跨服组队副本
	MATCH_TYPE_LOCAL_SINGLE_PVP	= 5,	// 本地单人PVP匹配
	MAX_KUAFU_TYPE,
};

//合服协议带的类型
enum EMergeType
{
	MERGE_TYPE_MERGE			= 0,	//从服迁移连接到主服
	MERGE_TYPE_GAME_TO_PK		= 1,	//游戏服到Pk服
	MERGE_TYPE_PK_TO_GAME		= 2,	//pk服到游戏服
};

//会话类型
enum ECOntextType
{
	CONTEXT_TYPE_YEYOU		= 0,		//页游
	CONTEXT_TYPE_PHONE		= 1,		//手游
	MAX_CONTEXT_TYPE
};

//性别
enum CHAR_GENDER
{
	CHAR_GENDER_MALE			= 0,		//男性
	CHAR_GENDER_FEMALE			= 1,		//女性
	CHAR_GENDER_NONE			= 2,		//未知
	MAX_CHAR_GENDER				= 3,		//长度		
};

//形象
enum Race_type
{
	RACE_NONE					 = 0,	//无
	RACE_STRONG					 = 1,	//壮男
	RACE_HANDSOME				 = 2,	//俊男 
	RACE_LAURIE					 = 3,	//萝莉
	RACE_BEAUTY					 = 4,	//美人
};

//头像
enum Head_type
{
	HEAD_NONE				= 0,	//无
	HEAD_STRONG				= 1,	//壮男
	HEAD_HANDSOME			= 2,	//俊男 
	HEAD_LAURIE				= 3,	//萝莉
	HEAD_BEAUTY				= 4,	//美人	
	HEAD_TOTAL				= 4,  /*头像个数*/
};

//复活类型
enum Resurrection_Type
{
	RESURRECTION_IN_SITU	= 0, //原地复活
	RESURRECTION_SPAWNPOINT = 1, //复活点复活
	RESURRPCTION_FREE		= 2, //免费复活
	RESURRPCTION_MONEY		= 3, //元宝复活
	RESURRPCTION_TIME		= 4, //超时复活
	RESURRPCTION_HUANHUNDAN	= 5, //还魂丹复活
	MAX_RESURRECTION_TYPE,
};

//GM等级
enum GM_LEVEL
{
	GM_LEVEL_0	= 0,	//普通玩家
	GM_LEVEL_1	= 1,	//普通GM
	GM_LEVEL_2	= 2,	//高级GM
	GM_LEVEL_3	= 3,	//终极GM
};

//游戏对象标志
enum GameObject_Flags
{
	GO_FLAG_DYNAMIC = 0,	//是否动态对象,由不是由地图刷出来的
	GO_FLAG_TELE	= 1,	//是否传送点对象
	GO_FLAG_QUEST	= 2,	//是否任务对象
	GO_FLAG_LOOT	= 3,	//是否战利品	
	GO_FLAG_GEAR	= 10,	//是否机关，如箱子，门等

	GO_FLAG_UNUSE	= 4,	//不可被使用
	GO_FLAG_FOREVER	= 5,	//可永久使用

	GO_FLAG_USEMODE = 8,	//使用方式,需要进度条
	GO_FLAG_CARTON	= 9,	//客户端模拟消失

	GO_FLAG_REBORN	= 11,	//是否会重生 (如果有这项, GO_FLAG_FOREVER将不管用)

	GO_FLAG_SCRIPT	= 12,	//是否使用脚本
	GO_FLAG_GET_ITEM_NOTICE = 13,		//拾起物品是否需要公告
};

//世界地图状态
enum World_Map_State
{
	WORLD_MAP_DEFAULT			= 0,	//新手村
};

//类枚举
enum TypeID
{
	TYPEID_OBJECT			= 0,		//本来0都是没用的
	TYPEID_UNIT				= 1,		//生物精灵，如怪物，NPC，宝宝等。。。
	TYPEID_PLAYER			= 2,		//玩家精灵
	TYPEID_GAMEOBJECT		= 3,		//游戏对象精灵
	MAX_CLIENT_OBJECT_TYPES
};

//物品品质
enum Item_Qual
{
	ITEM_QUAL_WHITE		= 0,		//白装
	ITEM_QUAL_GREEN		= 1,		//绿装
	ITEM_QUAL_BLUE		= 2,		//蓝装
	ITEM_QUAL_PURPLE	= 3,		//紫装
	ITEM_QUAL_ORANGE	= 4,		//橙装
	ITEM_QUAL_RED		= 5,		//红装
	MAX_QUAL
};

//攻击模式
enum Attack_Mode
{
	ATTACK_MODE_PEACE		= 0,	//和平，不用说，你懂的
	ATTACK_MODE_TEAM		= 1,	//组队，可以砍队伍以外的玩家
	ATTACK_MODE_RED			= 2,	//红名，可以砍红名
	ATTACK_MODE_ALL			= 3,	//全体，除了自己，谁都可以砍
	ATTACK_MODE_FACTION		= 4,	//帮派模式
	ATTACK_MODE_BANG		= 5,	//结义模式
	MAX_ATTACK_MODE,
};

//仇恨计算类型
enum ReactStates
{
	REACT_PASSIVE			= 0,		//被动攻击
	REACT_DEFENSIVE			= 1,		//防御
	REACT_AGGRESSIVE		= 2,		//主动攻击,
	REACT_AGGRESSIVE_UNIT	= 3,		//主动攻击怪物
	REACT_AGGRESSIVE_PLAYER = 4,		//主动攻击玩家
	MAX_REACT_STATES
};

//合服操作类型
enum MERGE_OPT_TYPE
{
	MERGE_OPT_TYPE_INIT				= 0,		//初始状态
	MERGE_OPT_TYPE_SAVE_DB			= 1,		//数据保存完成
	MERGE_OPT_TYPE_TARGET_SERVER_OK	= 2,		//目标服务器准备完成
	MERGE_OPT_TYPE_END				= 3,		//操作结束
	MERGE_OPT_TYPE_SAVE_ING			= 4,		//数据保存中
};
//合服服务器类型
enum MERGE_SERVER_TYPE
{
	MERGE_SERVER_TYPE_ORIGINAL	= 1,		//原始服务器
	MERGE_SERVER_TYPE_TARGAT	= 2,		//目标服务器
};

//回档操作类型
enum BACK_OPT_TYPE
{
	BACK_OPT_TYPE_INIT				= 0,		//初始状态
	BACK_OPT_TYPE_SUCCESS			= 1,		//成功
};

//物品绑定类型
enum ITEM_BIND_TYPE
{
	ITEM_BIND_NONE	= 0,		//非绑定
	ITEM_BIND_USE	= 1,		//使用绑定
	ITEM_BIND_GET	= 2,		//获得绑定
};

//场景服给的东西获得类型
enum ITEM_GIFT_GET_TYPE
{
	ITEM_GIFT_GET_NONE	= 0,	//非必须
	ITEM_GIFT_GET_MUST	= 1,	//必须获得的
};

//玩家在线状态
enum EPlayerOnlineState
{
	PLAYER_ONLINE_STATE_OUTLINE	= 0,	//离线
	PLAYER_ONLINE_STATE_ONLINE	= 1,	//在线
};

//生物移动模式
enum MovementGeneratorType
{
	DISAPPEAR_MOTION_TYPE			= 9999,	//消失
	IDLE_MOTION_TYPE				= 0,	//空闲
	RANDOM_MOTION_TYPE				= 1,	//随机
	WAYPOINT_MOTION_TYPE			= 2,	//沿路行走
	TARGET_MOTION_TYPE				= 3,	//目标行走
	HOME_MOTION_TYPE				= 4,	//回家
	CONFUSED_MOTION_TYPE			= 5,	//困惑
	FLEEING_MOTION_TYPE				= 6,	//逃避
	FOLLOW_MOTION_TYPE				= 7,	//跟随
	FOLLOW_INLINE_MOTION_TYPE		= 8,	//直线跟随
	WAYFINDING_MOTION_TYPE			= 9,	//寻路行走
	WAYFINDING_ATTACK_MOTION_TYPE	= 10,	//寻路追杀
	MERCENARY_MOTION_TYPE			= 11,	//佣兵
	WAYFINDDST_MOTION_TYPE			= 12,	//目的地行走
	DEADLINE_MOTION_TYPE			= 13,	//过期消失

	MAX_MOTION_TYPE
};

//技能目标类型 自己,友方,敌方,全体
enum Spell_Target_Type
{
	TARGET_TYPE_ONESELF   = 0,
	TARGET_TYPE_FRIENDLY  = 1,
	TARGET_TYPE_ENEMY     = 2,
	TARGET_TYPE_ALL		  = 3,
	TARGET_TYPE_POINT	  = 4,		//对点释放技能 
	TARGET_TYPE_SELFPOINT = 5,		//对自己的点释放
	TARGET_TYPE_CREATURE  = 6,		//对怪物有效（不包括宠物等）
	TARGET_TYPE_PLAYER	  = 7,		//对玩家有效
};

//交易状态
enum TRADE_STATE_TYPE
{
	TRADE_STATE_TYPE_FREE				= 0,	//空闲状态
	TRADE_STATE_TYPE_APPLY				= 1,	//申请状态
	TRADE_STATE_TYPE_EXECUTION			= 2,	//执行状态
	TRADE_STATE_TYPE_PUT_ITEM_END		= 3,	//确认物品完成
	TRADE_STATE_TYPE_WAIT_FINISH 		= 4,	//等待完成状态
};

//交易的类型
enum TRADE_TYPE
{
	TRADE_TYPE_TRADE	= 0,					//交易
	TRADE_TYPE_STALL	= 1,					//摆摊
};


//通过模板id移动物品到指定的包裹（相应的位置上），结果
enum MOVE_ITEM_RESULT
{
	MOVE_ITEM_FAIL		= 0,	//失败
	MOVE_ITEM_SUC		= 1,	//成功
	MOVE_ITEM_HAVE_BIND = 2,	//包含绑定的
	MOVE_ITEM_NOT_BIND	= 3,	//不包含绑定的
};

//删除物品结果
enum SUB_ITEM_RESULT
{
	SUB_ITEM_FAIL			= 0,					//失败
	SUB_ITEM_HAVE_BIND		= 1,					//包含绑定的
	SUB_ITEM_NOT_BIND 		= 2,					//不包含绑定的
	SUB_ITEM_HAVE_FAILTIME  = 3,					//包含限时
};

//物品数据处理状态
enum ITEM_SAVE_MODE
{
	ITEM_SAVE_MODE_INSERT = 0,		//插入
	ITEM_SAVE_MODE_UPDATE = 1,		//更新
};

//元宝充值类型
enum GOLD_INGOT_RECHARGE_TYPE
{
	GOLD_INGOT_RECHARGE_NORMAL	= 1,	//正常模式
	GOLD_INGOT_RECHARGE_HANDSEL	= 2,	//赠送模式
	GOLD_INGOT_RECHARGE_SUB		= 3,	//扣费模式
	GOLD_INGOT_RECHARGE_HAND	= 4,	//手动模式
	MAX_GOLD_INGOT_RECHARGE_TYPE,
};

//充值状态类型
enum RECHAGRE_STATUS_TYPE
{
	RECHARGE_STATUS_TYPE_START		= 0,		//初始化
	RECHARGE_STATUS_TYPE_RUNMING	= 1,		//发放中
	RECHARGE_STATUS_TYPE_END		= 2			//结束
};

//踢人的状态类型
enum KICKING_STATUS
{
	KICKING_STATUS_START		=0,		//初始化
	KICKING_STATUS_END			=1,		//已踢
};

//封号的状态类型
enum LOCKING_STATUS
{
	LOCKING_STATUS_START		=0,		//初始化
	LOCKING_STATUS_RUNNING		=1,		//封号中
	LOCKING_STATUS_END			=2,		//结束
};

//公告的状态类型
enum SYSTEM_NOTICE_STATUS
{
	SYSTEM_NOTICE_STATUS_START		= 0,	//初始状态
	SYSTEM_NOTICE_STATUS_RUNNING	= 1,	//运行中
	SYSTEM_NOTICE_STATUS_END		= 2,	//结束
	SYSTEM_NOTICE_STATUS_DELETE		= 3,	//将删除
	SYSTEM_NOTICE_STATUS_GARBAGE	= 4,	//已删除
};

//礼包的状态类型
enum GIFT_PACKS_STATUS
{
	GIFT_PACKS_STATUS_START		= 0,	//初始
	GIFT_PACKS_STATUS_SENDING	= 1,	//发放中
	GIFT_PACKS_STATUS_OK		= 2,	//已发放
	GIFT_PACKS_STATUS_END		= 3,	//已结束
};

//礼包发放类型
enum GIFT_PACKS_AUDIENCE_TYPE
{
	GIFT_PACKS_AUDIENCE_TYPE_ONE				= 1,		//个人礼包，如补偿礼包等
	GIFT_PACKS_AUDIENCE_TYPE_ALL				= 2,		//全体同志的礼包
	GIFT_PACKS_AUDIENCE_TYPE_ALL_ONLINE			= 3,		//全服在线玩家
};

//礼包操作类型
enum GIFT_PACKS_OPERATION_TYPE
{
	GIFT_PACKS_OPER_TYPE_RECEIVE	= 0,			//领取
	GIFT_PACKS_OPER_TYPE_READ		= 1,			//已读
	GIFT_PACKS_OPER_TYPE_DELETE		= 2,			//删除
};

//禁言状态
enum GAG_STATUS
{
	GAG_STATUS_START		= 0,		//初始化
	//GAG_STATUS_OFFLINE		= 1,		//玩家离线
	GAG_STATUS_END			= 1,		//已禁言
};

//设置GM表的状态
enum GM_LEVEL_TABLE_STATUS
{
	GM_LEVEL_TABLE_START	= 0,		//初始化
	GM_LEVEL_TABLE_END		= 1,		//已执行
};

//公告类型
enum NOTICE_TYPE
{
	NOTICE_TYPE_SCROLL		= 1,		//滚动公告
	NOTICE_TYPE_PROMPT		= 2,		//固定和世界聊天提示
	NOTICE_TYPE_FIXED		= 3,		//固定提示

	MAX_NOTICE_TYPE			= 10,		//预留10种
};

//聊天类型
enum CHAT_TYPE
{
	CHAT_TYPE_SYSTEM		= 0,		//系统
	CHAT_TYPE_WORLD			= 1,		//世界
	CHAT_TYPE_FACTION		= 2,		//帮派
	CHAT_TYPE_CURRENT		= 3, 		//当前(场景)
	CHAT_TYPE_HORM			= 4,		//喇叭
	CHAT_TYPE_GROUP			= 5,		//队伍
	CHAT_TYPE_WHISPER		= 6,		//私聊
	MAX_CHAT_TYPE
};

//平台枚举
#define PLATFORM_GAME2	   "2"		//哥们网
#define PLATFORM_5WANPK	   "5"		//5玩
#define PLATFORM_QQ        "360"	//腾讯QQ
#define PLATFORM_NULL	 "9999"		//不需要post的平台

//post的动作类型
enum EPostType
{
	POST_TYPE_NONE			= 0,
	POST_TYPE_CHAT			= 1,			//聊天
	POST_TYPE_UPGRADE		= 2,			//用户升级
	MAX_POST_TYPE
};

//记录到文件的日志类型
enum LOG_FILE_TYPE
{
	LOG_FILE_TYPE_GAME_BUY				= 0,	//记录用户在游戏内购买行为
	LOG_FILE_TYPE_GAME_SELL				= 1,	//记录用户在游戏内出售行为
	LOG_FILE_TYPE_RECHARGE				= 2,	//记录用户充值行为
	LOG_FILE_TYPE_SHOP_BUY				= 3,	//记录用户在商城的购买行为
	LOG_FILE_TYPE_ITEM_USE				= 4,	//记录用户使用商城物品行为
	LOG_FILE_TYPE_DEAL					= 5,	//记录用户的交易行为
	LOG_FILE_TYPE_YB_INCOME				= 6,	//记录额外元宝收入
	LOG_FILE_TYPE_ITEM_INCOME			= 7,	//记录额外道具收入
	LOG_FILE_TYPE_PAY					= 8,	//记录额外元宝消费
	LOG_FILE_TYPE_LOGIN					= 9,	//记录用户登录行为
	LOG_FILE_TYPE_LOGOUT				= 10,	//记录用户登出行为
	LOG_FILE_TYPE_CREATE_ROLE			= 11,	//记录用户创建角色行为
	LOG_FILE_TYPE_DEATH					= 12,	//记录用户角色死亡事件
	LOG_FILE_TYPE_ACCEPT_TASK			= 13,	//记录用户接收任务的行为
	LOG_FILE_TYPE_MAIN_TASK				= 14,	//记录用户完成任务的行为
	LOG_FILE_TYPE_LV_UP					= 15,	//记录用户升级事件
	LOG_FILE_TYPE_YXB					= 16,	//记录用户金币所得行为
	LOG_FILE_TYPE_MAP					= 17,	//记录用户切换地图的行为
	LOG_FILE_TYPE_LONGER				= 18,	//记录用户的挂机行为
	LOG_FILE_TYPE_MONSTER				= 19,	//记录用户打怪的行为
	LOG_FILE_TYPE_TRANSCRIPT			= 20,	//记录用户打副本的行为
	LOG_FILE_TYPE_ONLINE				= 21,	//记录在线人数
	LOG_FILE_TYPE_GAME_ENTER			= 22,	//记录用户进入游戏主界面
	LOG_FILE_TYPE_ITEM_LOG				= 23,	//记录道具的所有行为
	LOG_FILE_TYPE_CHAT					= 24,	//记录玩家聊天记录
	LOG_FILE_TYPE_RELIVE				= 25,	//记录玩家复活
	LOG_FILE_TYPE_BIND_GOLD				= 26,	//记录玩家的绑定元宝行为
	LOG_FILE_TYPE_NEW_CARD_RECEIVE		= 27,	//记录用户领取新手卡的行为
	LOG_FILE_TYPE_STALL					= 28,	//记录摆摊行为
	LOG_FILE_TYPE_WANTED_PACKET			= 29,	//记录被通缉的玩家的所有包记录
	LOG_FILE_TYPE_ERROR_PACKET			= 30,	//记录读取用户信息出错的包
	LOG_FILE_TYPE_CHOOSE_FACTION		= 31,	//记录玩家选择阵营的情况
	LOG_FILE_TYPE_ACTIVITY_INFO			= 32,	//记录运营活动奖励信息
	LOG_FILE_TYPE_ABNORMAL_PACKETS		= 33,	//记录因为异常包而踢掉玩家的行为
	LOG_FILE_TYPE_CLIENT_INFO			= 34,	//记录玩家客户端信息
	LOG_FILE_TYPE_GIFTMONEY_BUY			= 35,	//记录玩家礼金消耗的行为
	LOG_FILE_TYPE_GIFTMONEY_INCOME		= 36,	//记录用户礼金获得的行为
	LOG_FILE_TYPE_ATTACK_PACKET			= 37,	//记录攻击包
	LOG_FILE_TYPE_FORMAT_LOG			= 38,	//记录乱七八糟的自定义日志
	LOG_FILE_TYPE_CLIENT_LOG			= 39,	//记录客户端日志
	LOG_FILE_TYPE_FORGE_LOG				= 40,	//记录锻造日志
	LOG_FILE_TYPE_OBJECT_LOSS			= 41,	//1001日志
	LOG_FILE_TYPE_ONLINE_USER_24TH		= 42,	//0点在线用户
	LOG_FILE_TYPE_UNION					= 43,	//帮派操作

	MAX_LOG_FILE_TYPE
};

enum SkillEffectType
{
	SKILL_EFFECT_TYPE_NORMAL			= 0,	//普通效果类型
	SKILL_EFFECT_TYPE_HUIXUE1			= 1,	//敌方扣血, 自己加血
	SKILL_EFFECT_TYPE_ROAR				= 2,	//战吼
	SKILL_EFFECT_TYPE_BLADE_STORM		= 3,	//剑刃风暴 (每多少秒扣血还是怎么的?)
	SKILL_EFFECT_TYPE_HEAL				= 4,	//治疗之泉
	SKILL_EFFECT_TYPE_SNOW_STORM		= 5,	//暴风雪
	SKILL_EFFECT_TYPE_LOADED			= 99,	//蓄力时间到释放技能
};

//记录腾讯文件的日志类型
enum LOG_FILE_TENCENT_TYPE
{
	LOG_FILE_TENCENT_USER				= 0,	//用户表
	LOG_FILE_TENCENT_PLAYER				= 1,	//角色表
	LOG_FILE_TENCENT_RECHAGRE			= 2,	//充值表
	LOG_FILE_TENCENT_UPGRADELOG			= 3,	//升级日志
	LOG_FILE_TENCENT_NEWTASK			= 4,	//新手日志
	LOG_FILE_TENCENT_LOGIN				= 5,	//登陆日志
	LOG_FILE_TENCENT_OFFLINE			= 6,	//离线日志
	LOG_FILE_TENCENT_ONLINE				= 7,	//在线统计日志
	LOG_FILE_TENCENT_MONEYLOG			= 8,	//金币流量

	MAX_LOG_FILE_TENCENT_TYPE
};

// 死亡地类型
enum DEAD_PLACE_TYPE
{
	DEAD_PLACE_TYPE_FIELD			= 1,		// 野外死亡
	DEAD_PLACE_TYPE_XIANFU			= 2,		// 仙府夺宝死亡
	DEAD_PLACE_TYPE_GROUP_INSTANCE	= 3,		// 组队副本死亡
};

//攻击包异常类型
enum ACCACK_PACKET_TYPE
{
	ACCACK_PACKET_TYPE_UNPACK	= 0,	//解包失败
	ACCACK_PACKET_TYPE_DATA		= 1,	//数据异常
	ACCACK_PACKET_TYPE_ORDER	= 2,	//包顺序异常
	ACCACK_PACKET_TYPE_DISCARD	= 3,	//废弃的包号
	MAX_ACCACK_PACKET_TYPE
};

//交易物品
typedef struct deal_goods_t
{
	char guid[50];		//装备ID
	uint32 entryid;		//模版ID
	uint32 goodtype;	//类型
	uint32 num;			//数量

}deal_goods;

//额外元宝获得类型
enum LOG_YB_INCOME_TYPE
{
	LOG_YB_INCOME_TYPE_ACTIVITY		= 0,		//活动赠送
	LOG_YB_INCOME_TYPE_RECHARGE		= 1,		//充值赠送
	LOG_YB_INCOME_TYPE_USE_ITEM		= 2,		//使用道具
	LOG_YB_INCOME_TYPE_GIFT_PACKS	= 3,		//补偿礼包
};
 
//道具操作类型
//NOTICE 这个用于自定义道具的来源及客户端的提示reason是对应的
enum LOG_ITEM_OPER_TYPE
{
	//获得
	LOG_ITEM_OPER_TYPE_ACTIVITY				= 0,		//活动奖励获得
	LOG_ITEM_OPER_TYPE_RECHARGE				= 1,		//充值赠送获得
	LOG_ITEM_OPER_TYPE_GIFT_PACKS			= 2,		//补偿礼包获得
	LOG_ITEM_OPER_TYPE_QUEST				= 3,		//任务完成奖励获得
	LOG_ITEM_OPER_TYPE_NEWPLAYER			= 4,		//新手礼包获得
	LOG_ITEM_OPER_TYPE_OPEN_ITEM			= 5,		//使用道具获得
	LOG_ITEM_OPER_TYPE_LOOT					= 6,		//战利品
	LOG_ITEM_OPER_TYPE_GM_COMMAND			= 7,		//GM命令获得
	LOG_ITEM_OPER_TYPE_ITEM_BLEND			= 8,		//物品合成获得
	LOG_ITEM_OPER_TYPE_SEVEN_DAY_GIFT		= 9,		//连登礼包	
	LOG_ITEM_OPER_TYPE_JHM_GIFT				= 10,		//激活码礼包
	LOG_ITEM_OPER_TYPE_OPEN_BOX				= 11,		//开宝箱获得
	LOG_ITEM_OPER_TYPE_FUBEN_EWAIJINAGLI	= 12,		//副本额外奖励
	LOG_ITEM_OPER_TYPE_CAPTURE_YAOHUN		= 13,		//扑捉妖魂获得
	LOG_ITEM_OPER_TYPE_FSZL_EWAIJINAGLI		= 14,		//飞升之路奖励
	LOG_ITEM_OPER_TYPE_PRESTIGE				= 15,		//活跃度领取获得
	LOG_ITEM_OPER_TYPE_TIANDILINGKUANG		= 16,		//天地灵矿领取获得
	LOG_ITEM_OPER_TYPE_PANTAOYUAN			= 17,		//蟠桃园奖励
	LOG_ITEM_OPER_TYPE_WABAO				= 18,		//挖宝获得
	LOG_ITEM_OPER_TYPE_HONGYAN				= 19,		//红颜事件获得
	LOG_ITEM_OPER_TYPE_FORGE_DECOMPOSE		= 20,		//锻造分解获得
	LOG_ITEM_OPER_TYPE_WORLD_BOSS_ROLL		= 21,		//世界BOSSroll点
	LOG_ITEM_OPER_TYPE_VIP_INSTANCE_REWARD	= 22,		//vip副本奖励
	LOG_ITEM_OPER_TYPE_TRIAL_INSTANCE_REWARD= 23,		//试炼塔奖励
	LOG_ITEM_OPER_TYPE_ACHIEVE				= 24,		//成就奖励
	LOG_ITEM_OPER_TYPE_SHOUCHONG			= 25,		//首充奖励
	LOG_ITEM_OPER_TYPE_CHECKIN				= 26,		//每日签到奖励
	LOG_ITEM_OPER_TYPE_GETBACK				= 27,		//找回次数奖励
	LOG_ITEM_OPER_TYPE_TOTAL_CHECKIN		= 28,		//每日累积签到奖励
	LOG_ITEM_OPER_TYPE_WELFARE_LEVEL		= 29,		//福利等级奖励
	LOG_ITEM_OPER_TYPE_3V3_KUAFU			= 30,		//3v3跨服奖励
	LOG_ITEM_OPER_TYPE_INSTANCE_SWEEP		= 31,		//副本奖励扫荡奖励
	LOG_ITEM_OPER_TYPE_XIANFU				= 32,		//仙府夺宝跨服奖励
	LOG_ITEM_OPER_TYPE_DOUJIAN_FIRST_REWARD	= 33,		//斗剑台首胜奖励
	LOG_ITEM_OPER_TYPE_DOUJIAN_COMBAT_REWARD= 34,		//斗剑台连胜奖励
	LOG_ITEM_OPER_TYPE_CULTIVATION_REWARD	= 35,		//修炼场奖励
	LOG_ITEM_OPER_TYPE_CULTIVATION_PLUNDER_REWARD	= 36,		//修炼场掠夺奖励
	LOG_ITEM_OPER_TYPE_LOGIN_ACTIVITY_REWARD	= 37,		//登录大礼奖励
	LOG_ITEM_OPER_TYPE_GROUP_INSTANCE			= 38,		//组队副本跨服奖励

	LOG_ITEM_OPER_TYPE_XIANFU_PRACTISE		= 40,		//仙府夺宝体验奖励
	LOG_ITEM_OPER_TYPE_FACTION_BOSS			= 41,		//帮派boss奖励

	LOG_ITEM_OPER_TYPE_OFFLINE				= 42,		//离线奖励
	LOG_ITEM_OPER_TYPE_STOREHOUSE			= 43,		//帮派宝库

	LOG_ITEM_OPER_TYPE_MASS_BOSS			= 44,		//全民BOSS


	//购买
	LOG_ITEM_OPER_TYPE_SHOP_BUY				= 45,		//从商场购买获得

	LOG_ITEM_OPER_TYPE_FACTION_BOSSDEFENSE	= 46,		//家族首领挑战击杀奖励
	LOG_ITEM_OPER_TYPE_FACTION_TOWER		= 47,		//家族无尽远征奖励

	LOG_ITEM_OPER_TYPE_SINGLE_PVP			= 48,		//单人PVP
	LOG_ITEM_OPER_TYPE_ACT_LOTTERY			= 49,		//抽奖活动
	LOG_ITEM_OPER_TYPE_ACT_DAILYGIFT		= 50,		//每日礼包活动
	LOG_ITEM_OPER_TYPE_ACT_RANK				= 51,		//每日排行活动
	LOG_ITEM_OPER_TYPE_ACT_LIMITGIFT		= 52,		//限定礼包活动

	LOG_ITEM_OPER_TYPE_RECHARGE_REWARD		= 53,		//充值返利
	LOG_ITEM_OPER_TYPE_CONSUME_REWARD		= 54,		//消费返利
	LOG_ITEM_OPER_TYPE_PRIVATE_BOSS			= 55,		//个人Boss
	LOG_ITEM_OPER_TYPE_ESCORT				= 56,		//运镖
	LOG_ITEM_OPER_TYPE_ESCORT_ROB			= 57,		//劫镖
	LOG_ITEM_OPER_TYPE_REALMBREAK			= 58,		//境界突破任务
	LOG_ITEM_OPER_TYPE_STAGE_BONUS			= 59,		//闯关宝箱奖励
	LOG_ITEM_OPER_TYPE_FACTION_MATCH_DAILY_REWARD = 60,		//家族战每日成员奖励
	LOG_ITEM_OPER_TYPE_RES_INSTANCE_FIRST	 = 61,		//资源副本首次奖励
	LOG_ITEM_OPER_TYPE_SEVEN_DAY_RECHARGE_EXTRA	= 62,	//7日充值额外奖励

	LOG_ITEM_OPER_TYPE_GIFTCODE					= 63,	//兑换码奖励



	LOG_ITEM_OPER_TYPE_NPC_BUY				= 102,		//从NPC购买获得
	LOG_ITEM_OPER_TYPE_BIND_SHOP_BUY		= 103,		//从绑定商城购买获得
	LOG_ITEM_OPER_TYPE_REPURCHASE			= 104,		//从NPC回购物品获得
	LOG_ITEM_OPER_TYPE_ACTI_BUY				= 105,		//活动购买
	LOG_ITEM_OPER_TYPE_XIANFU_BUY			= 106,		//购买仙府进入券

	//消耗
	LOG_ITEM_OPER_TYPE_NPC_SELL				= 200,		//出售给NPC
	LOG_ITEM_OPER_TYPE_DEL_FAILTIME			= 201,		//清理限时物品
	LOG_ITEM_OPER_TYPE_USE					= 202,		//使用物品
	LOG_ITEM_OPER_TYPE_DISPOSE				= 203,		//销毁物品
	LOG_ITEM_OPER_TYPE_HEAL					= 204,		//吃药
	LOG_ITEM_OPER_TYPE_WASH_ATTR			= 205,		//洗练
	LOG_ITEM_OPER_TYPE_GEM_UPGRADE			= 206,		//宝石升级
	LOG_ITEM_OPER_TYPE_REFINE				= 207,		//精炼
	LOG_ITEM_OPER_TYPE_STRENGTH				= 208,		//强化
	LOG_ITEM_OPER_TYPE_MERIDIAN				= 209,		//经脉经验
	LOG_ITEM_OPER_TYPE_WING_STRENGTH		= 210,		//神羽强化
	LOG_ITEM_OPER_TYPE_WING_BLESS			= 211,		//神羽祝福
	LOG_ITEM_OPER_TYPE_TALISMAN_LVUP			= 212,		//法宝注灵
	LOG_ITEM_OPER_TYPE_TALISMAN_ACTIVE			= 213,		//法宝激活
	LOG_ITEM_OPER_TYPE_MOUNT_ILLUSION			= 214,		//坐骑幻化
	LOG_ITEM_OPER_TYPE_UNLOCK_TITLE				= 215,		//称号激活
	LOG_ITEM_OPER_TYPE_APPEARANCE_ACTIVE		= 216,		//外观幻化激活
	LOG_ITEM_OPER_TYPE_QUEST_USE_ITEM		= 217,		//任务使用道具
	LOG_ITEM_OPER_TYPE_USE_BOX				= 218,		//使用宝箱道具
	LOG_ITEM_OPER_TYPE_MOUNT_BLESS			= 219,		//升星坐骑


	//交易
	LOG_ITEM_OPER_TYPE_TRADE_GET			= 301,		//交易获得
	LOG_ITEM_OPER_TYPE_TRADE_PAY			= 302,		//交易付出
	LOG_ITEM_OPER_TYPE_STALL_OPEN			= 303,		//摆摊
	LOG_ITEM_OPER_TYPE_STALL_CLOSE			= 304,		//收摊
	LOG_ITEM_OPER_TYPE_STALL_BUY			= 305,		//摊位购买

	LOG_ITEM_OPER_TYPE_LINGDI_XUANSHANG		= 306,		//领地悬赏
	LOG_ITEM_OPER_TYPE_LINGDI_MIJING		= 307,		//领地秘境

	LOG_ITEM_OPER_TYPE_WUJIANG_ZHENGZHAN	= 308,		//武将征战

	LOG_ITEM_OPER_TYPE_KAOZHUANGYUAN		= 309,		//考状元

	LOG_ITEM_OPER_TYPE_MONEYTREE_GIFT		= 310,		//摇钱树礼包

};

//后台货币变化种类枚举
enum HT_MONEY_CHANGE_TYPE
{
	HT_MONEY_CHANGE_TYPE_RECHARGE		= 1,	//充值
	HT_MONEY_CHANGE_TYPE_CONSUMPTION	= 2,	//消费
	HT_MONEY_CHANGE_TYPE_SUB			= 3,	//管理员扣除
	HT_MONEY_CHANGE_TYPE_REWARD			= 4,	//奖励
	HT_MONEY_CHANGE_TYPE_REBATE			= 5,	//返利
	HT_MONEY_CHANGE_TYPE_TRADING		= 6,	//交易
};

//货币变化原因类型
enum MONEY_CHANGE_TYPE
{
	MONEY_CHANGE_TYPE_CHARGE						= 0,	//玩家充值
	MONEY_CHANGE_TYPE_STORE_BUY						= 1,	//商店购买
	MONEY_CHANGE_TYPE_MALL_BUY						= 2,	//商城购买
	MONEY_CHANGE_TYPE_STALL_SALE					= 3,	//摊位卖出
	MONEY_CHANGE_TYPE_TRADE							= 4,	//玩家交易
	MONEY_CHANGE_MAIL								= 5,	//邮件
	MONEY_CHANGE_QUEST								= 6,	//任务奖励
	MONEY_CHANGE_DEAD								= 7,	//死亡掉落
	MONEY_CHANGE_RIHUAN								= 8,	//日环
	MONEY_CHANGE_USE_ITEM							= 9,	//使用物品消耗
	MONEY_CHANGE_GIFT_PACKS							= 10,	//系统礼包赠送
	MONEY_CHANGE_NPC_SELL							= 11,	//NPC出售
	__MONEY_CHANGE_ITEM_REPAIR						= 12,	//预留
	__MONEY_CHANGE_ITEM_APPRAISAL					= 13,	//预留
	MONEY_CHANGE_NPC_REPURCHASE						= 14,	//NPC回购
	MONEY_CHANGE_GM_COMMAND							= 15,	//GM招财命令
	MONEY_CHANGE_CREATE_FACTION						= 16,	//创建帮派
	MONEY_CHANGE_WAREHOUSE_HANLD					= 17,	//仓库操作
	MONEY_CHANGE_SELECT_LOOT						= 18,	//战利品
	MONEY_CHANGE_ACTIVITY							= 19,	//活动奖励
	MONEY_CHANGE_TYPE_CHARGE_2						= 20,	//充值额外赠送
	MONEY_CHANGE_TYPE_CHARGE_3						= 21,	//管理员扣除
	MONEY_CHANGE_TYPE_CHARGE_4						= 22,	//手动赠送
	MONEY_CHANGE_USE_LABA							= 23,	//使用喇叭
	MONEY_CHANGE_BAG_EXTENSION						= 24,	//背包扩展
	MONEY_CHANGE_ITEM_BLEND							= 25,	//物品合成消耗铜钱
	MONEY_CHANGE_SEVEN_DAY_GIFT						= 26,	//连登礼包
	MONEY_CHANGE_CLEAR_PK_VALUE						= 27,	//使用元宝洗白
	MONEY_CHANGE_JHM_REWARD							= 28,	//激活码奖励
	MONEY_CHANGE_ONLINE_GIFT						= 29,	//每日在线奖励
	MONEY_CHANGE_SPELL_UP							= 30,   //技能升阶
	MONEY_CHANGE_USE_BOX							= 31,	//使用宝箱消耗
	MONEY_CHANGE_BOX_OPEN							= 32,	//开宝箱获得
	MONEY_CHANGE_BOX_RANDOM							= 33,	//开宝箱随机奖励
	MONEY_CHANGE_JINGJIE							= 34,	//升级境界消耗
	MONEY_CHANGE_SHENBING_BUY						= 35,	//神兵购买
	MONEY_CHANGE_ATUO_GOLD_RESPAWN					= 36,	//元宝复活
	MONEY_CHANGE_FUBEN_KILLALL						= 37,	//副本全图秒杀消耗
	MONEY_CHANGE_FUBEN_EWAI							= 38,	//副本额外奖励
	MONEY_CHANGE_FUBEN_BUY							= 39,	//购买副本次数消耗
	MONEY_CHANGE_FSZL_REWARD						= 40,	//飞升之路奖励
	MONEY_CHANGE_PRESTIGE							= 41,	//活跃度
	MONEY_CHANGE_PANTAO_CAIJI						= 42,	//采集蟠桃获得
	MONEY_CHANGE_LINGKUANG_CAIJI					= 43,	//采集灵矿获得	
	MONEY_CHANGE_QIYU_ZHUOYAO						= 44,	//扑捉妖魂消耗
	MONEY_CHANGE_RESET_FORGE_ADD					= 45,	//重置锻造加成时间
	MONEY_CHANGE_WABAO								= 46,	//挖宝获得
	MONEY_CHANGE_HONGYAN_BUY_HUOLI					= 47,	//红颜购买活力
	MONEY_CHANGE_HONGYAN_SHIJIAN					= 48,	//红颜事件获得
	MONEY_CHANGE_HONGYAN_BUY_FASHION				= 49,	//红颜购买时装
	MONEY_CHANGE_FORGE_STRENG						= 50,	//锻造强化
	MONEY_CHANGE_FORGE_GEM							= 51,	//宝石
	MONEY_CHANGE_LINGDI_ZHAOMU						= 52,	//领地招募
	MONEY_CHANGE_LINGDI_XUANSHANG					= 53,	//领地悬赏
	MONEY_CHANGE_LINGDI_MIJING						= 54,	//领地秘境
	MONEY_CHANGE_WUJIANG_REFRESH_PUB				= 55,	//元宝刷新酒馆武将
	MONEY_CHANGE_FENGLIUZHEN_PUB_AUCTION			= 56,	//风流镇酒馆竞拍
	MONEY_CHANGE_WUJIANG_QINGJIU					= 55,	//元宝清酒武将
	MONEY_CHANGE_LINGDI_ZHENGBING					= 56,	//领地征兵
	MONEY_CHANGE_FENGLIUZHEN_ZHUANPAN_ENTER			= 57,	//风流镇转盘进去房间
	MONEY_CHANGE_USE_SPELL							= 58,	//使用技能
	MONEY_CHANGE_UP_ASSISTSPELL						= 59,	//升级辅助技能
	MONEY_CHANGE_LINGDI_BUY_BINGLI					= 60,	//领地征兵购买兵力
	MONEY_CHANGE_WUJIANG_ZHENGZHAN					= 61,	//武将征战
	MONEY_CHANGE_BUY_JUNLLING						= 62,	//购买军令
	MONEY_CHANGE_SELL_WUJIANG_EQUIP					= 63,	//出售武将装备
	MONEY_CHANGE_FENGLIUZHEN_KAOZHUANGYUAN			= 64,	//考状元奖励
	MONEY_CHANGE_ZHUBO_SEND_GIFTS					= 65,	//主播送礼消耗
	MONEY_CHANGE_ZHUBO_GRAB_SOFA					= 66,	//主播抢沙发
	MONEY_CHANGE_RAISE_MOUNT						= 67,	//升级坐骑
	MONEY_CHANGE_ILLUSION							= 68,	//坐骑幻化
	MONEY_CHANGE_BIND_INGOT_NOT_ENOUGH				= 69,	//购买道具绑银不足消耗元宝
	MONEY_CHANGE_ACTIVE_SPELL						= 70,	//激活技能
	MONEY_CHANGE_BUY_VIP_INSTANCE					= 71,	//购买VIP副本进入次数
	MONEY_CHANGE_BUY_HP_ITEM						= 72,	//购买回血药品
	MONEY_CHANGE_RESET_TRIAL						= 73,	//重置试炼塔
	MONEY_CHANGE_SOCIAL_GIFT						= 74,   //好友赠送礼物
	MONEY_CHANGE_FACTION_DONATION					= 75,   //帮派捐献
	MONEY_CHANGE_FACTION_SHOP						= 76,	//帮派商店
	MONEY_CHANGE_WORLD_BOSS_ROLL					= 77,	//世界BOSSroll点
	MONEY_CHANGE_VIP_INSTANCE_REWARD				= 78,	//VIP副本奖励
	MONEY_CHANGE_TRIAL_INSTANCE_REWARD				= 79,	//试炼塔奖励
	MONEY_CHANGE_WELF_ACTIVE_GETBACK				= 80,	//福利活动找回奖励
	MONEY_CHANGE_SHOUCHONG							= 81,	//首冲奖励
	MONEY_CHANGE_CHECKIN							= 82,	//每日签到奖励
	MONEY_CHANGE_TOTAL_CHECKIN						= 83,	//每日累积签到奖励
	MONEY_CHANGE_WELFARE_LEVEL						= 84,	//等级福利奖励
	MONEY_CHANGE_ACHIEVE							= 85,	//成就奖励
	MONEY_CHANGE_3V3KUAFU							= 86,	//3v3跨服奖励
	MONEY_CHANGE_VIP_INSTANCE_SWEEP					= 87,	//副本扫荡
	MONEY_CHANGE_GIFT_PACKET						= 88,	//礼包
	MONEY_CHANGE_KUAFU_WORLD_3V3					= 89,	//跨服3v3
	MONEY_CHANGE_KUAFU_WORLD_XIANFU					= 90,	//跨服仙府夺宝
	MONEY_CHANGE_BUY_XIANFU_TICKET					= 91,	//购买仙府进入券
	MONEY_CHANGE_DOUJIAN_BUY_TIMES					= 92,	//斗剑台购买次数
	MONEY_CHANGE_DOUJIAN_CLEARCD					= 93,	//斗剑台清理CD
	MONEY_CHANGE_DOUJIAN_FIRST_REWARD				= 94,	//斗剑台首胜奖励
	MONEY_CHANGE_DOUJIAN_COMBATWIN_REWARD			= 95,	//斗剑台连胜奖励
	MONEY_CHANGE_CULTIVATION_PURCHASE				= 96,   //修炼场购买次数
	MONEY_CHANGE_CULTIVATION_REWARD					= 97,	//修练场奖励
	MONEY_CHANGE_CULTIVATION_PLUNDER_REWARD			= 98,	//修练场掠夺奖励
	MONEY_CHANGE_LOGIN_ACTIVITY_REWARD				= 99,	//登陆大礼奖励
	MONEY_CHANGE_FACTION_BOSS						= 100,	//帮派boss奖励
	MONEY_CHANGE_OFFLINE							= 101,	//离线奖励
	MONEY_CHANGE_STOREHOUSE							= 102,	//帮派宝库
	MONEY_CHANGE_MASS_BOSS							= 103,	//全民BOSS
	MONEY_CHANGE_MASS_BOSS_BUY_TIMES				= 104,	//全民BOSS挑战次数
	MONEY_CHANGE_GROUP_INSTANCE_BUY_TIMES			= 105,	//组队副本挑战次数
	MONEY_CHANGE_KUAFU_GROUP_INSTANCE				= 106,	//跨服组队副本
	MONEY_CHANGE_MERIDIAN							= 107,	//经脉修炼
	MONEY_CHANGE_FACTION_BOSSDEFENSE				= 108,	//家族首领挑战 击杀奖励
	MONEY_CHANGE_FACTION_TOWER						= 109,	//家族无尽远征 击杀奖励
	MONEY_CHANGE_SINGLE_PVP							= 110,	//单人PVP
	MONEY_CHANGE_EQUIPDEVELOP						= 111,	//装备养成消耗
	MONEY_CHANGE_APPEARANCE							= 112,	//外观
	MONEY_CHANGE_FACTIONSKILL						= 113,	//家族技能消耗
	MONEY_CHANGE_UNLOCKTITLE						= 114,	//家族技能消耗
	MONEY_CHANGE_RENAME								= 115,	//改名
	MONEY_CHANGE_RANK_LIKE							= 116,	//排行榜点赞
	MONEY_CHANGE_ACT_LOTTERY						= 117,	//抽奖活动
	MONEY_CHANGE_ACT_DAILYGIFT						= 118,	//每日礼包
	MONEY_CHANGE_ACT_RANK							= 119,	//开服排行
	MONEY_CHANGE_ACT_LIMITGIFT						= 120,	//限定礼包
	MONEY_CHANGE_RECHARGE_REWARD					= 121,	//充值返利
	MONEY_CHANGE_CONSUME_REWARD						= 122,	//消费返利
	MONEY_CHANGE_MONEYTREE_USE						= 123,	//摇动摇钱树
	MONEY_CHANGE_PRIVATE_BOSS						= 124,	//个人Boss
	MONEY_CHANGE_ADVANTURE_KILL_BY_PLAYER			= 125,	//死亡掉落令牌
	MONEY_CHANGE_ESCORT								= 126,	//运镖
	MONEY_CHANGE_ESCORT_ROB							= 127,	//劫镖
	MONEY_CHANGE_REALMBREAK							= 128,	//境界任务奖励
	MONEY_CHANGE_STAGE_BONUS						= 129,	//闯关宝箱奖励
	MONEY_CHANGE_GROUP_EXP_BUY_TIMES				= 130,	//经验副本挑战次数
	MONEY_CHANGE_GROUP_EXP_BUY_INSPIRATION			= 131,	//经验副本鼓舞
	MONEY_CHANGE_FACTION_MATCH_DAILY_REWARD			= 132,	//家族战每日成员奖励
	MONEY_CHANGE_FACTION_RES_INSTANCE_FIRST			= 133,	//资源副本首次奖励
	MONEY_CHANGE_SEVEN_DAY_RECHARGE_EXTRA			= 134,	//7日充值额外奖励
	MONEY_CHANGE_RECHARGE_LOTTERY					= 136,	//充值抽奖
	MONEY_CHANGE_CHECKIN_GETBACK					= 136,	//签到补签消耗
	MONEY_CHANGE_GIFTCODE							= 137,	//兑换码礼包

	MAX_MONEY_CHANGE_TYPE
};

//特殊包裹类型
enum Bag_Virtual_Type
{
	BAG_VIRTUAL_TYPE_STALL			= -1,	//摆摊
	BAG_VIRTUAL_TYPE_UNKNOWN		= -2,	//未知
	SPECIALL_BAG_TYPE_MAIL			= -3,	//邮件
};

//物品类型
enum ITME_TYPE
{
	ITEM_TYPE_NONE						= 0,				//无
	ITEM_TYPE_EQUIP						= 1,				//装备
	ITEM_TYPE_MATERIAL					= 3,				//材料
	ITEM_TYPE_FASHION					= 5,				//时装
	ITEM_TYPE_SHELI						= 6,				//舍利
	ITEM_TYPE_PK_MEDICINE				= 7,				//PK药品
	ITEM_TYPE_PET_MEDICINE				= 8,				//宠物药
	ITEM_TYPE_NUMBER					= 9,				//数值类型
	ITEM_TYPE_MEDICINE					= 12,				//药品
	ITEM_TYPE_PELLET					= 13,				//加次数丹药
	ITEM_TYPE_BOX						= 15,				//宝箱类（使用获得道具类型的物品）
	ITEM_TYPE_BUFF						= 25,				//获得buff型
};

// 获得道具以后的记录
enum ITEM_RECORD
{
	ITEM_RECORD_BROADCAST	=	1,			// 全服广播
	ITEM_RECORD_XIANFU		=	2,			// 仙府夺宝记录
	ITEM_RECORD_MAP			=	3,			// 地图通知
};

// masks for ITEM_INT_FIELD_FLAGS field
enum Item_Flags
{
	ITEM_FLAGS_QUEST                          = 0, // 是否任务物品
	ITEM_FLAGS_RMB							  = 1,	//是否RMB物品
	ITEM_FLAGS_APPRAISAL                      = 2, //是否鉴定
	ITEM_FLAGS_BROKEN                         = 3, // 是否损坏的,耐久0
	ITEM_FLAGS_USABLE                         = 4, // 是否可用的
	ITEM_FLAGS_LOCKED						  = 5,	// 物品锁定标志
	ITEM_FLAGS_REFUNDABLE                     = 6, // 可回购的
	ITEM_FLAGS_UNIQUE_EQUIPPED                = 7,	//是否独特装备
	ITEM_FLAGS_SPECIALUSE                     = 8, // 特殊用途
	ITEM_FLAGS_BOP_TRADEABLE                  = 9,  //是否可交易的
	ITEM_FLAGS_IS_BINDED		              = 10, //是否绑定
	ITEM_FLAGS_IS_JIPIN			              = 11, //是否极品装备
};

//物品使用对象类型
enum ItemUse
{
	ITEM_USE_SELF               	= 0,						//自己
	ITEM_USE_TARGET					= 1,						//目标
	ITEM_USE_NULL                	= 2,						//不可使用
};

//物物品使用结果类型
enum ItemUseResult
{
	ITEM_USE_RESULT_DISAPPEAR			= 0,					//消失
	ITEM_USE_RESULT_NOT_DISAPPEAR		= 1,					//不消失
	ITEM_USE_RESULT_SUB_DURABLE			= 2,					//减少耐久
	ITEM_USE_RESULT_UN_USE				= 3,					//不可使用
};

//道具返还类型
enum ItemReturnType
{
	LOG_ITEM_RETURN_TYPE_HAVE				= 0,			//返还背包得到
	LOG_ITEM_RETURN_TYPE_LOSE				= 1,			//返还背包失去
	LOG_ITEM_RETURN_TYPE_CLEAR				= 2,			//返还背包清理
	LOG_ITEM_RETURN_TYPE_GOLD				= 3,			//材料不足自动购买
};

//坐骑状态
enum Mount_State
{
	MOUNT_STATE_FREE	    = 0, //空闲
	MOUNT_STATE_WAS_RIDING  = 1, //骑乘
};

//任务状态
enum QuestStatus
{
	QUEST_STATUS_NONE           = 0,		// 
	QUEST_STATUS_COMPLETE       = 1,		//完成
	QUEST_STATUS_UNAVAILABLE    = 2,		//得不到的，没空的，不能利用的???
	QUEST_STATUS_INCOMPLETE     = 3,		//不完全,未完成
	QUEST_STATUS_AVAILABLE      = 4,		//有效，可接受
	QUEST_STATUS_FAILED         = 5,		//失败
	QUEST_STATUS_END			= 6,		//任务结束,已领奖

	QUEST_STATUS_SHOW_INCOMPLETE = 13,		//任务未完成显示用
	QUEST_STATUS_SHOW_END		 = 16,		//任务整个完成了, 显示用

	MAX_QUEST_STATUS
};

enum BookQuestStatus
{
	BOOK_STATUS_NONE           = 0,		 
	BOOK_STATUS_COMPLETE       = 1,		//完成未领奖
	BOOK_STATUS_UNAVAILABLE    = 2,		//得不到的，没空的，不能利用的
	BOOK_STATUS_INCOMPLETE     = 3,		//不完全,未完成
	BOOK_STATUS_AVAILABLE      = 4,		//有效，可接受
	BOOK_STATUS_FAILED         = 5,		//失败
	BOOK_STATUS_REWARDED       = 6,		//已领奖
};

//任务给予者状态
enum QuestGiverStatus
{
	DIALOG_STATUS_NONE                     = 0,
	DIALOG_STATUS_UNAVAILABLE              = 1,				// 任务给予者状态,忙碌
	DIALOG_STATUS_CHAT                     = 2,             // 对话,3.1 - may be changed
	DIALOG_STATUS_INCOMPLETE               = 5,				//  未完成
	DIALOG_STATUS_REWARD_REP               = 6,				// 可重复领取奖励
	DIALOG_STATUS_AVAILABLE_REP            = 7,				// 可重复接受任务
	DIALOG_STATUS_AVAILABLE                = 8,				// 有可接任务
	DIALOG_STATUS_REWARD2                  = 9,             // no yellow dot on minimap
	DIALOG_STATUS_REWARD                   = 10,            // 报酬，报答，赏金,yellow dot on minimap
	MAX_DIALOG_STATUS
};

//任务标志
enum QuestFlags
{
	// Flags used at server and sent to client	
	QUEST_FLAGS_COMMIT_NOT_NEED_NPC	= 0x00000100,            // 提交任务是否校验npc
	QUEST_FLAGS_ACCEPT_NOT_NEED_NPC	= 0x00000200,            // 接受任务是否校验npc
	QUEST_FLAGS_DAILY			= 0x00000400,                //日常任务 Used to know quest is Daily one

	QUEST_FLAGS_AUTO_FAIL_OFF	= 0x00000001,				 //离线或者死亡或者跨系列图传送后直接任务失败
	QUEST_FLAGS_AUTO_COMPLETE	= 0x00000010,                //auto complete	
	QUEST_FLAGS_AUTO_REWARDED	= 0x00000020,                //自动奖励 These quests are automatically rewarded on quest complete and they will never appear in quest log client side.
	QUEST_FLAGS_AUTO_ACCEPT		= 0x00000040,                //quests in starting areas
	QUEST_FLAGS_MANUAL			= 0x00000080,				 //手动完成	
	QUEST_FLAGS_CANREMOVE		= 0x00001000,		  		 //允许放弃
	// Mangos flags for set SpecialFlags in DB if required but used only at server
	_QUEST_FLAGS_FLAGS_REPEATABLE           = 0x010000,     //可重复接受的 Set by 1 in SpecialFlags from DB
	_QUEST_FLAGS_FLAGS_EXPLORATION_OR_EVENT = 0x020000,     //Set by 2 in SpecialFlags from DB (if required area explore, spell SPELL_EFFECT_QUEST_COMPLETE casting, table `*_script` command SCRIPT_COMMAND_QUEST_EXPLORED use, set from script DLL)
	_QUEST_FLAGS_FLAGS_DB_ALLOWED = 0xFFFF | _QUEST_FLAGS_FLAGS_REPEATABLE | _QUEST_FLAGS_FLAGS_EXPLORATION_OR_EVENT,

	// Mangos flags for internal use only
	_QUEST_FLAGS_FLAGS_DELIVER              = 0x040000,     //Internal flag computed only,需要收集物品的
	_QUEST_FLAGS_FLAGS_SPEAKTO              = 0x080000,     //Internal flag computed only,需要与NPC对话的
	_QUEST_FLAGS_FLAGS_KILL_OR_CAST         = 0x100000,     //Internal flag computed only,杀死怪物或者使用任务物品的
	_QUEST_FLAGS_FLAGS_TIMED                = 0x200000,     //定时?Internal flag computed only
	QUEST_FLAGS_FLAGS_BUY_ITEM				= 0x400000,		//购买物品的任务
	QUEST_FLAGS_FLAGS_OPT_SYS				= 0x800000,		//操作系统的任务
	QUEST_FLAGS_FLAGS_LEVEL_CREATURE		= 0x1000000,	//杀等级怪
	QUEST_FLAGS_FLAGS_LEVEL_PLAYER			= 0x2000000,	//杀等级玩家
};

enum QuestRelationType
{
	QUEST_RELATION_TYPE_START = 0,		//待接任务
	QUEST_RELATION_TYPE_END = 1			//待交任务
};

//任务更新操作
enum QuestUpdateState
{	
	QUEST_UNCHANGED = 0,	//未变化
	QUEST_CHANGED = 1,		//变化
	QUEST_NEW = 2	
};

#define MAX_ACHIEVE_COUNT 100
enum AchieveField{
	ACHIEVE_FIELD_REWARD = 0,	//0 是否已达成 1 是否已领奖 2 预留 3 预留
	ACHIEVE_FIELD_CURRENT = 1,	//成就进度
	MAX_ACHIEVE_FIELD
};

// 最多可领取任务个数
#define MAX_QUEST_COUNT 50
// 最多可领取日常任务个数
#define MAX_DAILY2_QUEST_COUNT 10
// 最多可领取冒险任务个数
#define MAX_ADVENTURE_QUEST_COUNT 20

// 最多可领取冒险任务个数
#define MAX_REALMBREAK_QUEST_COUNT 50

// 任务最多目标
#define MAX_QUEST_TARGET_COUNT 5

enum QuestTargetInfo
{
	QUEST_TARGET_INFO_SHORT0	= 0,	//0:状态, 1:目标值
	QUEST_TARGET_INFO_PROCESS	= 1,	//进度
	MAX_QUEST_TARGET_INFO_COUNT			
};

enum QuestFieldInfo
{
	QUEST_INFO_ID				= 0,					//任务id, 任务状态
	QUEST_INFO_STEP_START		= QUEST_INFO_ID + 1,	//任务目标开始
	QUEST_INFO_STEP_END			= QUEST_INFO_STEP_START + MAX_QUEST_TARGET_COUNT * MAX_QUEST_TARGET_INFO_COUNT,	//任务目标结束
	MAX_QUEST_INFO_COUNT		= QUEST_INFO_STEP_END,
};

#define MAX_TITLE_COUNT 100
enum TitleField{
	TITLE_FIELD_INFO = 0,	//0 ID 1 保留 16位
	TITLE_FIELD_TIME = 1,	//称号失效时间
	MAX_TITLE_FIELD
};
#define WELFA_BACK_TYPE_COUNT 10
enum WELFAREBACKFIELD{
	WELFA_BACK_ITEM		= 0,
	WELFA_BACK_ITEM_END = 8,
	WELFA_BACK_ITEM_NUM	= 9,
	MAX_WELFA_BACK_ITEM
};

//运镖状态
enum QuestEscortState
{	
	QUEST_ESCORT_STATE_NONE = 0,	//未开始运镖
	QUEST_ESCORT_STATE_NORMAL = 1,//正常运镖
	QUEST_ESCORT_STATE_ROB = 2,	//已被劫镖
};

//任务 成就 称号 福利 相关字段
enum EQuestFields
{
	QUEST_FIELD_ACHIEVE_START	= 0,	//成就开始
	QUEST_FIELD_ACHIEVE_END		= QUEST_FIELD_ACHIEVE_START + MAX_ACHIEVE_COUNT * MAX_ACHIEVE_FIELD,//成就结束
	QUEST_FIELD_ACHIEVE_ALL		= QUEST_FIELD_ACHIEVE_END,//总成就点
	QUEST_FIELD_ACHIEVE_REWARD	= QUEST_FIELD_ACHIEVE_ALL + 1,//成就点奖励ID

	QUEST_FIELD_QUEST_START		= QUEST_FIELD_ACHIEVE_REWARD + 1,									//任务开始
	QUEST_FIELD_QUEST_END		= QUEST_FIELD_QUEST_START + MAX_QUEST_INFO_COUNT * MAX_QUEST_COUNT,	//任务结束

	QUEST_FIELD_TITLE_START		= QUEST_FIELD_QUEST_END,									//称号开始
	QUEST_FIELD_TITLE_END		= QUEST_FIELD_TITLE_START + MAX_TITLE_COUNT * MAX_TITLE_FIELD,//称号结束

	QUEST_FIELD_WELFARE_SHOUCHONG	=	QUEST_FIELD_TITLE_END,//是否领取首冲奖励
	QUEST_FIELD_WELFARE_CHECKIN		=	QUEST_FIELD_WELFARE_SHOUCHONG + 1,//每日签到奖励领取标记 用位表示
	QUEST_FIELD_WELFARE_CHECKIN_ALL	=	QUEST_FIELD_WELFARE_CHECKIN + 1,//累积签到奖励领取标记 用位表示
	QUEST_FIELD_WELFARE_LEVEL		=	QUEST_FIELD_WELFARE_CHECKIN_ALL + 1,//升级福利奖励

	QUEST_FIELD_WELFARE_BACK_START	= QUEST_FIELD_WELFARE_LEVEL + 1,
	QUEST_FIELD_WELFARE_BACK_END	= QUEST_FIELD_WELFARE_BACK_START + MAX_WELFA_BACK_ITEM * WELFA_BACK_TYPE_COUNT,

	QUEST_FIELD_DAILY2_FINISHED		= QUEST_FIELD_WELFARE_BACK_END,		// 日常任务完成个数
	QUEST_FIELD_DAILY2_SUBMIT		= QUEST_FIELD_DAILY2_FINISHED + 1,	// 日常任务是否提交
	QUEST_FIELD_DAILY2_QUEST_START	= QUEST_FIELD_DAILY2_SUBMIT + 1,	// 日常任务开始
	QUEST_FIELD_DAILY2_QUEST_END	= QUEST_FIELD_DAILY2_QUEST_START + MAX_QUEST_INFO_COUNT * MAX_DAILY2_QUEST_COUNT,	//日常任务结束

	QUEST_FIELD_WELFARE_RECHARGE_REWARD_FLAG	= QUEST_FIELD_DAILY2_QUEST_END,			//累计充值奖励领取标记
	QUEST_FIELD_WELFARE_CONSUME_REWARD_FLAG	= QUEST_FIELD_WELFARE_RECHARGE_REWARD_FLAG + 1, //累计充值奖励领取标记

	QUEST_FIELD_WELFARE_SEVEN_DAY_PROCESS	= QUEST_FIELD_WELFARE_CONSUME_REWARD_FLAG + 1,	//七日大礼 进度
	QUEST_FIELD_WELFARE_SEVEN_DAY_FLAG		= QUEST_FIELD_WELFARE_SEVEN_DAY_PROCESS + 1,	//七日大礼 领取状态

	QUEST_FIELD_COUNT_TYPE_START			= QUEST_FIELD_WELFARE_SEVEN_DAY_FLAG+ 1,	//任务计数开始
	QUEST_FIELD_COUNT_TYPE_END				= QUEST_FIELD_COUNT_TYPE_START + 5,			//任务计数结束

	QUEST_FIELD_ADVENTURE_QUEST_START	= QUEST_FIELD_COUNT_TYPE_END + 1,	// 冒险任务开始
	QUEST_FIELD_ADVENTURE_QUEST_END	= QUEST_FIELD_ADVENTURE_QUEST_START + MAX_QUEST_INFO_COUNT * MAX_ADVENTURE_QUEST_COUNT,	//冒险任务结束

	QUEST_FIELD_ESCORT_QUEST_START	= QUEST_FIELD_ADVENTURE_QUEST_END + 1,	// 押镖任务开始
	QUEST_FIELD_ESCORT_QUEST_END	= QUEST_FIELD_ESCORT_QUEST_START + MAX_QUEST_INFO_COUNT,	//押镖任务结束
	QUEST_FIELD_ESCORT_QUEST_FINISH_TIME	= QUEST_FIELD_ESCORT_QUEST_END + 1,	//押镖任务结束时间

	QUEST_FIELD_REALMBREAK_QUEST_START	= QUEST_FIELD_ESCORT_QUEST_FINISH_TIME + 1,	// 境界突破任务开始
	QUEST_FIELD_REALMBREAK_QUEST_END	= QUEST_FIELD_REALMBREAK_QUEST_START + MAX_QUEST_INFO_COUNT * MAX_REALMBREAK_QUEST_COUNT,	//境界突破任务开始

	QUEST_FIELD_WELFARE_SEVEN_DAY_RECHARGE_PROCESS = QUEST_FIELD_REALMBREAK_QUEST_END + 1,	//充值天数
	QUEST_FIELD_WELFARE_SEVEN_DAY_RECHARGE_EXTRA_FLAG	= QUEST_FIELD_WELFARE_SEVEN_DAY_RECHARGE_PROCESS + 1,	//充值额外奖励领取标识 0~2
};

//战斗状态
enum Combat_State
{
	COMBAT_STATE_LEAVE = 0, //脱离战斗
	COMBAT_STATE_ENTER = 1, //进入战斗
};

//战斗状态
enum UnitState
{
	UNIT_STAT_DIED            = 0x0001,
	UNIT_STAT_MELEE_ATTACKING = 0x0002,                     // player is melee attacking someone
	UNIT_STAT_CAST_SPELL	  = 0x0004,                     // 引导技能
	UNIT_STAT_SPELL_PROCESS   = 0x0008,						//持续施法
	UNIT_STAT_ROAMING         = 0x0010,						//漫游
	UNIT_STAT_CHASE           = 0x0020,						//追逐
	UNIT_STAT_SEARCHING       = 0x0040,						//搜索
	UNIT_STAT_FLEEING         = 0x0080,						//逃避
	UNIT_STAT_MOVING          = (UNIT_STAT_ROAMING | UNIT_STAT_CHASE | UNIT_STAT_SEARCHING | UNIT_STAT_FLEEING),
	UNIT_STAT_IN_FLIGHT       = 0x0100,                     // player is in flight mode
	UNIT_STAT_FOLLOW          = 0x0200,						//跟随
	UNIT_STAT_ROOT            = 0x0400,						//缠绕???
	UNIT_STAT_CONFUSED        = 0x0800,						//使困惑
	UNIT_STAT_DISTRACTED      = 0x1000,						//转移,使分心
	UNIT_STAT_ISOLATED        = 0x2000,                     // 隔离,光环无法影响其他玩家 area auras do not affect other players
	UNIT_STAT_ATTACK_PLAYER   = 0x4000,						// 攻击
	UNIT_STAT_ALL_STATE       = 0xffff                      //(UNIT_STAT_STOPPED | UNIT_STAT_MOVING | UNIT_STAT_IN_COMBAT | UNIT_STAT_IN_FLIGHT)
};

//生存状态
enum DeathState
{
	DEATH_STATE_ALIVE       = 0,		//活着
	DEATH_STATE_CORPSE      = 1,		//尸体，在客户端可见尸体
	DEATH_STATE_DEAD        = 2,		//死亡，在客户端尸体消失
};

//击打信息，例如吸收，致命一击等等
enum HitInfo
{
	HITINFO_NORMALSWING         = 1,		//普通
	HITINFO_CRITHIT				= 2,		//暴击
	HITINFO_MISS                = 3,		//躲避
	HITINFO_GEDANG				= 4,		//格挡
	HITINFO_CRITICALHIT			= 5,		//会心一击
	HITINFO_BLOWFLY				= 6,		//击飞
	HITINFO_LIUXUE				= 7,		//流血
	HITINFO_CURE				= 8,		//治疗
	HITINFO_JUMP_EVA			= 9,		//跳闪
	HITINFO_POISON				= 10,		//毒
	HITINFO_ICE					= 11,		//冰
	HITINFO_FANTANSHANGHAI		= 12,		//反弹伤害
};

//移动状态
enum Move_Status
{
	MOVE_STATUS_STOP = 0 ,
	MOVE_STATUS_RUN	 = 1,
};

//NPC标识
/// Non Player Character flags
enum NPCFlags
{
	UNIT_NPC_FLAG_NONE                  = -1,

	UNIT_NPC_FLAG_GOSSIP                = 0,       // 100%闲聊NPC
	UNIT_NPC_FLAG_QUESTGIVER            = 1,       // 任务发布PCguessed, probably ok
	UNIT_NPC_FLAG_UNK1                  = 2, 		//预留
	UNIT_NPC_FLAG_UNK2                  = 3,
	UNIT_NPC_FLAG_TRAINER               = 4,      // 100%  训练师
	UNIT_NPC_FLAG_TRAINER_CLASS         = 5,       // 100%  职业训练师
	UNIT_NPC_FLAG_TRAINER_PROFESSION    = 6,       // 100%  自由职业训练师？
	UNIT_NPC_FLAG_VENDOR                = 7,       // 100%  买卖商人
	UNIT_NPC_FLAG_VENDOR_PROP           = 8,       // 100%, 道具
	UNIT_NPC_FLAG_VENDOR_WEAPON         = 9,        // 100%  武器
	UNIT_NPC_FLAG_VENDOR_POISON         = 10,       // 药品
	UNIT_NPC_FLAG_VENDOR_REAGENT        = 11,       // 100%  饰品
	UNIT_NPC_FLAG_VENDOR_EQUIPMENT      = 12,       // 100%  装备
	UNIT_NPC_FLAG_FLIGHTMASTER          = 13,       // 100% 飞行点管理员
	UNIT_NPC_FLAG_SPIRITHEALER          = 14,       // guessed 复活Npc
	UNIT_NPC_FLAG_SPIRITGUIDE           = 15,       // guessed 灵魂向导
	UNIT_NPC_FLAG_INNKEEPER             = 16,       // 100% 旅店老板
	UNIT_NPC_FLAG_WAREHOUSE             = 17,       // 100% 仓库
	UNIT_NPC_FLAG_PETITIONER            = 18,       // 100% 竞技场
	UNIT_NPC_FLAG_TABARDDESIGNER        = 19,       // 100%工会徽章设计NPC
	UNIT_NPC_FLAG_BATTLEMASTER          = 20,       // 100%战场管理员
	UNIT_NPC_FLAG_AUCTIONEER            = 21,       // 100%拍卖商
	UNIT_NPC_FLAG_STABLEMASTER          = 22,       // 100%马夫
	UNIT_NPC_FLAG_GUILD_BANKER          = 23,       // 公会银行cause client to send 997 opcode
	UNIT_NPC_FLAG_CHALLENGE             = 24,       // 神奇的挑战怪要变大变粗,UNIT_NPC_FLAG_GUARD
	UNIT_NPC_FLAG_ONE_ONE				= 25,       // 是否光棍怪,没钱，没精验，没装备，没次数
};

//所有固定的BUFF => buff id要与表buff_template的id对应
enum EBuffID
{
	BUFF_ONEPOINTFIVE_JINGYAN	= 101,		//1.5倍经验丹
	BUFF_TOW_JINGYAN			= 102,		//2倍经验丹
	BUFF_THREE_JINGYAN			= 103,		//3倍经验丹
	BUFF_FIVE_JINGYAN			= 104,		//5倍经验丹
	BUFF_FANTAN					= 105,		//反弹
	BUFF_LIANJIE				= 106,		//连接
	BUFF_BEILIANJIE				= 107,		//被连接
	BUFF_GANGCI					= 108,		//钢刺
	BUFF_DINGSHEN				= 109,		//定身
	BUFF_YUNXUAN				= 110,		//晕眩
	BUFF_YUNMIE_ELING			= 111,		//陨灭（恶灵）
	BUFF_HUIFU_HUDUN			= 112,		//恢复护盾
	BUFF_FANJI_HUDUN			= 113,		//反击护盾
	BUFF_LINGXUE				= 114,		//流血
	BUFF_ZHUOSHAO				= 115,		//灼烧
	BUFF_JUDU					= 116,		//剧毒
	BUFF_ZHONGDU				= 117,		//中毒
	BUFF_BINGJIA				= 118,		//冰甲
	BUFF_BINGDONG				= 119,		//冰冻
	BUFF_BAOZHA_DILEI			= 120,		//爆炸（地雷）
	BUFF_SHOUWEI_ZHAOHUAN		= 121,		//守卫（召唤）
	BUFF_BIAOJI					= 122,		//标记
	BUFF_KUANGBAO				= 123,		//狂暴
	BUFF_JIANSU					= 124,		//减速
	BUFF_CHENMO					= 125,		//沉默
	BUFF_XUECHI					= 126,		//血池
	BUFF_WAIGONGMIANYI			= 127,		//外攻免疫
	BUFF_NEIGONGMIAN			= 128,		//内攻免疫
	BUFF_WUDI					= 129,		//无敌
	BUFF_ZHANSHEN_FUTI			= 130,		//战神附体
	BUFF_JINGANG_BUHUAITI		= 131,		//金刚不坏体
	BUFF_KUANGBEN				= 132,		//狂奔
	BUFF_HUOBA					= 133,		//火把
	BUFF_LINGTI					= 134,		//灵体
	BUFF_HUANHUA_ZHU			= 135,		//幻化成猪
	BUFF_HUANHUA_REN			= 136,		//幻化成人
	BUFF_HUANHUA_GUI			= 137,		//幻化成鬼
	BUFF_HUANHUA_XIAN			= 138,		//幻化成仙
	BUFF_HUANHUA_XIULUO			= 139,		//幻化成修罗
	BUFF_XIULUOLI				= 140,		//修罗力
	BUFF_ZHENYING				= 141,		//阵营
	BUFF_ZHANDOU_STATE			= 142,		//战斗状态
	BUFF_JUMP_DOWN				= 144,		//身轻
	BUFF_ANXIANG_SHUYING		= 145,		//暗香疏影
	BUFF_ZHIKONG				= 146,		//滞空
	BUFF_FUKONG					= 147,		//浮空

	BUFF_JUMP_JUMP				= 143,		//跳跃

	BUFF_NEW_PLAYER_PROTECTED	= 148,		//新手保护
	BUFF_DEATH_PROTECTED		= 149,		//死亡保护
	BUFF_INVINCIBLE				= 150,		//无敌
	BUFF_INVISIBLE				= 151,		//隐身
	BUFF_YINCHANG				= 152,		//吟唱
	BUFF_ROAR					= 153,		//狂吼
	BUFF_HEAL					= 200,		//百分比回血
	BUFF_ATTACK					= 201,		//攻击增强
	BUFF_ARMOR					= 202,		//防御增强
	BUFF_CRIT					= 203,		//暴击增强
	BUFF_ALLATTR				= 204,		//全属性增强

};

enum BUFF_DEFAULT_EFFECT_ID
{
	BUFF_DEFAULT_EFFECT_ID_JUMP_JUMP = 1,					//默认的跳跃buff的效果id
	BUFF_DEFAULT_EFFECT_ID_NEW_PLAYER_PROTECTED = 2,		//默认的新手保护buff的效果id
	BUFF_DEFAULT_EFFECT_ID_DEATH_PROTECTED = 3,				//默认的死亡保护buff的效果id
};

#define MAX_2JI_SHIJIAN_UINT32 20	//红颜2级事件uint32
#define MAX_HONGYAN_DATI_COUNT 10	//红颜最大答题次数

//红颜系统操作枚举
enum HongYanOptType
{
	HONGYAN_JIESHI_MEIREN		= 	0,		//--结识美人
	HONGYAN_DIANZAN				= 	1,		//--点赞
	HONGYAN_PINGJIA				= 	2,		//--评价
	HONGYAN_SHIZHUANG_JIHUO		=	3,		//--时装激活
	HONGYAN_SHIZHUANG_CHUANDAI	= 	4,		//--时装穿戴
	HONGYAN_XIANGCE_JIHUO		= 	5,		//--相册激活
	HONGYAN_SHIJIAN_CHULI		= 	6,		//--事件处理
	HONGYAN_CHUYOU				= 	7,		//--出游
	HONGYAN_HUIFU_HUOLI			= 	8,		//--恢复活力值
	HONGYAN_ADD_NEIWU_SHIJIAN	= 	9,		//--增加内务事件
};

//红颜系统玩家属性
enum HongYanPlayerAttrsType
{
	HONGYAN_PLAYER_ATTRS_XIAYI		=	0,		//--侠义值
	HONGYAN_PLAYER_ATTRS_FENGLIU	= 	1,		//--风流
	HONGYAN_PLAYER_ATTRS_MINGSHENG	= 	2,		//--名声
	HONGYAN_PLAYER_ATTRS_WENTAO		= 	3,		//--文韬
	HONGYAN_PLAYER_ATTRS_WULUE		= 	4,		//--武略
	HONGYAN_PLAYER_ATTRS_CAIYI		= 	5,		//--才艺
	HONGYAN_PLAYER_ATTRS_QINHE		= 	6,		//--亲和
	HONGYAN_PLAYER_ATTRS_LIYI		= 	7,		//--礼仪
	HONGYAN_PLAYER_ATTRS_XIANGMAO	= 	8,		//--相貌
	HONGYAN_PLAYER_ATTRS_HUOLI		= 	9,		//--活力
	MAX_PLAYER_ATTRS	= 10,
};

//红颜系统美人属性
enum HongYanMeiRenAttrsType
{
	HONGYAN_MEIREN_ATTRS_JIESHI_BIT		= 	0,		//0:是否结识  1~31：结识条件
	HONGYAN_MEIREN_ATTRS_XINGGE_BIT		= 	1,		//性格
	HONGYAN_MEIREN_ATTRS_AIHAO_BIT		= 	2,		//爱好
	HONGYAN_MEIREN_ATTRS_CHANGJING_BIT	= 	3,		//场景
	HONGYAN_MEIREN_ATTRS_SHIZHUANG_BIT	= 	4,		//时装
	HONGYAN_MEIREN_QINMIDU_UINT16		= 	5,		//0：亲密度 1:当前穿戴的时装ID
	HONGYAN_MEIREN_XIANGCE_BIT			= 	6,		//美人激活的相册
	MAX_MEIREN_ATTRS_TYPE				=	7,
};

//红颜系统美人人气值
enum HongYanMeiRenRenQiType
{
	HONGYAN_MEIREN_DIANZAN		= 	0,		//点赞
	HONGYAN_MEIREN_MEIHAO		= 	1,		//美貌
	HONGYAN_MEIREN_JIESHI_COUNT	= 	2,		//美人结识的玩家数量
	MAX_MEIREN_RENQI_TYPE		=	3,
};

//红颜系统美人表
enum HongYanMeiRen
{
	HONGYAN_CAIXUE			= 0,	//采雪
	HONGYAN_ZHENFEI			= 1,	//珍妃
	HONGYAN_YANLIN			= 2,	//燕琳
	HONGYAN_MURONGYANYAN	= 3,	//慕容嫣嫣
	HONGYAN_YAORU			= 4,	//瑶如
	HONGYAN_XIANGJING		= 5,	//项晶
	HONGYAN_HENGXIAOZHUO	= 6,	//桓小卓
	HONGYAN_LIJI			= 7,	//俪姬
	HONGYAN_SIQI			= 8,	//思绮
	HONGYAN_YOUYOU			= 9,	//幽幽
	HONGYAN_LINCHUER		= 10,	//林楚儿
	HONGYAN_WANYAN_YUNNA	= 11,	//完颜云娜
	HONGYAN_QUANHUIQIAO		= 12,	//全慧乔
	HONGYAN_TUOBALVZHU		= 13,	//拓跋绿珠
	HONGYAN_QINGYAN			= 14,	//轻颜
	HONGYAN_SUOMOER			= 15,	//索沫儿
	HONGYAN_GUQIANQIAN		= 16,	//谷纤纤
	HONGYAN_AYIGULI			= 17,	//阿依古丽
	HONGYAN_ZUOYUYI			= 18,	//左玉怡
	HONGYAN_ZILUO			= 19,	//紫罗
	HONGYAN_QUNUO			= 20,	//曲诺
	HONGYAN_XUANYING		= 21,	//玄樱

	MAX_MEIREN = 32,
};

//所有GM命令的定义
enum Gm_Command_List
{
	GM_COMMAND_NULL					= 0,	//空命令
	GM_COMMAND_JIULONGCHAO    	 	= 1,	//@天书世界
	GM_COMMAND_SUCAI    			= 2,	//@素材
	GM_COMMAND_JIAOBEN 				= 3,	//@脚本
	GM_COMMAND_TI					= 4,	//@踢
	GM_COMMAND_ZAIXIAN  			= 5,	//@在线
	GM_COMMAND_DITURENSHU 			= 6,	//@地图人数
	GM_COMMAND_ZHAOCAI	  			= 7,	//@招财
	GM_COMMAND_ZHIZAO				= 8,	//@制造
	GM_COMMAND_QINGLI				= 9,	//@清理
	GM_COMMAND_ZHUANGBEI			= 10,	//@装备
	GM_COMMAND_PAIHANGBANG			= 12,	//@排行榜
	GM_COMMAND_YOUJIAN				= 13,	//@邮件
	GM_COMMAND_BENGDIAO				= 15,	//@崩掉
	GM_COMMAND_BANGZHU				= 16,	//@帮助
	GM_COMMAND_GONGGAO				= 17,	//@公告
	GM_COMMAND_SHIJIETISHI			= 18,	//@世界提示
	GM_COMMAND_PAIDUI				= 19,	//@排队
	GM_COMMAND_PINGBICI				= 20,	//@屏蔽词
	GM_COMMAND_GUANBIFUWUQI			= 21,	//@关闭服务器
	GM_COMMAND_CHONGZHI				= 22,	//@充值
	GM_COMMAND_GUANBIDITU			= 23,	//@关闭地图
	GM_COMMAND_DENGJI				= 24,	//@等级
	GM_COMMAND_QINGLIRENWUWUPIN		= 25,	//@清理任务物品
	GM_COMMAND_QINGLIRENWU			= 26,	//@清理任务
	GM_COMMAND_WANCHENGRENWU		= 27,	//@完成任务
	GM_COMMAND_JIESHOURENWU			= 28,	//@接受任务
	GM_COMMAND_GANDIAO				= 29,	//@干掉
	GM_COMMAND_SHUAGUAI				= 30,	//@刷怪
	GM_COMMAND_CHUANSONG			= 31,	//@传送
	GM_COMMAND_XIAZOU				= 32,	//@瞎走
	GM_COMMAND_SUICIDE				= 33,	//@自爆
	GM_COMMAND_SERVER_INFO			= 34,	//@服务器
	GM_COMMAND_DB					= 35,	//@数据库
	GM_COMMAND_KAIFUSHIJIAN			= 36,	//@开服时间
	GM_COMMAND_TEST_SHUJU			= 37,	//@测试数据
	GM_COMMAND_UPDATE_SERVER		= 38,	//@更新服务器
	GM_COMMAND_RESESSION_OPTS		= 39,	//@协议注册
	GM_COMMAND_RENWUTIAOZHUAN		= 40,	//@任务跳转
	GM_COMMAND_BACKUP_DATA			= 41,	//@备份数据
	GM_COMMAND_RETURN_DATA			= 42,	//@回档数据
	GM_COMMAND_PRINT_OBJECT			= 43,	//@打印对象
	GM_COMMAND_TEST_HEFU			= 44,	//@测试合服
	GM_COMMAND_CLEAR_PAIHANGBANG	= 45,	//@清空排行榜
	GM_COMMAND_MEMORY_RECOVERY		= 46,	//@内存回收
	GM_COMMAND_PRINT_MAP			= 47,	//@打印地图
	GM_COMMAND_DEL_MAP_INFO			= 48,	//@清空地图信息
	GM_COMMAND_RESTORE_SYSTEM		= 49,	//@后台命令
	GM_COMMAND_CALL_REMOVE_ITEM		= 50,	//@清空物品监听
	GM_COMMAND_SUBLINE				= 51,	//@分线
	GM_COMMAND_CUSTOM				= 52,	//@CUSTOM
	GM_COMMAND_VIP					= 53,	//@VIP
	GM_COMMAND_SELF_KILL			= 54,	//@自杀
};

//查询玩家信息的时候，需要附带的信息
enum EQueryPlayerInfoFlag
{
	QUERY_PLAYER_FLAG_BASE			= 0,	//玩家基础信息
	QUERY_PLAYER_FLAG_NAME			= 1,	//玩家姓名
	QUERY_PLAYER_FLAG_EQUIP			= 2,	//玩家装备形象
	QUERY_PLAYER_FLAG_PIFENG		= 3,	//披风信息
	QUERY_PLAYER_FLAG_FORCE			= 4,	//玩家战斗力
	QUERY_PLAYER_FLAG_OTHER			= 5,	//其它信息

	//下面是非玩家下标的东西
	QUERY_PLAYER_FLAG_MOUNT			= 20,	//所有坐骑
	QUERY_PLAYER_FLAG_EQUIP_BAG		= 21,	//装备包裹
	QUERY_PLAYER_FLAG_MAIN_BAG		= 22,	//背包包裹
	QUERY_PLAYER_FLAG_STORAGE_BAG	= 23,	//仓库包裹
	QUERY_PLAYER_FLAG_STALL_BAG		= 24,	//摊位包裹	
};

//任务类型定义
enum EQuestType
{											
	QUEST_TYPE_MAIN  						 = 0,		//主线任务
	QUEST_TYPE_EXTENSIONS					 = 1,		//支线任务
	QUEST_TYPE_ACTIVITY						 = 2,		//活动任务
	QUEST_TYPE_QIYU							 = 3,		//奇遇任务
	QUEST_TYPE_DAILY						 = 4,		//每日环任务
	QUEST_TYPE_DAILY2						 = 5,		//日常任务
	QUEST_TYPE_ADVENTURE					 = 6,		//冒险任务
	QUEST_TYPE_ESCORT						 = 7,		//押镖任务
	QUEST_TYPE_REALMBREAK						 = 8,		//境界突破任务
};

// 任务目标类型定义
enum QuestTargetType
{
	QUEST_TARGET_TYPE_PLAYER_LEVEL			= 1,	//人物等级
	QUEST_TARGET_TYPE_PLAYER_FORCE			= 2,	//人物战力

	QUEST_TARGET_TYPE_FACTION				= 3,	//加入或创建家族
	QUEST_TARGET_TYPE_FACTION_DONATION		= 4,	//捐赠
	QUEST_TARGET_TYPE_FACTION_ACTIVITY		= 5,	//家族活动

	QUEST_TARGET_TYPE_FIELD_BOSS			= 6,	//参加野外BOSS
	QUEST_TARGET_TYPE_WORLD_BOSS			= 7,	//参加世界BOSS

	QUEST_TARGET_TYPE_RESOURCE_INSTANCE		= 8,	//挑战资源副本
	QUEST_TARGET_TYPE_TRIAL_INSTANCE		= 9,	//挑战试练副本

	QUEST_TARGET_TYPE_OWN_DIVINE			= 10,	//获得任意神兵
	QUEST_TARGET_TYPE_EQUIP_DIVINE			= 11,	//装备任意神兵
	QUEST_TARGET_TYPE_STRENGTH_DIVINE		= 12,	//强化任意神兵

	QUEST_TARGET_TYPE_RAISE_SKILL			= 13,	//升级技能

	QUEST_TARGET_TYPE_TRAIN_MOUNT			= 14,	//培养坐骑
	QUEST_TARGET_TYPE_RAISE_MOUNT_SKILL		= 15,	//升级坐骑任意技能

	QUEST_TARGET_TYPE_FRIEND_DONATION		= 16,	//赠送好友礼物

	QUEST_TARGET_TYPE_STRENGTH_SUIT			= 17,	//强化装备
	QUEST_TARGET_TYPE_STRENGTH_GEM			= 18,	//强化宝石

	QUEST_TARGET_TYPE_TALK					= 19,	//对话

	QUEST_TARGET_TYPE_PICK_GAME_OBJECT		= 20,	//采集
	QUEST_TARGET_TYPE_CHECK_GAME_OBJECT		= 21,	//检查

	QUEST_TARGET_TYPE_KILL_MONSTER			= 22,	//击杀怪物
	QUEST_TARGET_TYPE_USE_ITEM				= 23,	//使用物品
	QUEST_TARGET_TYPE_SUIT					= 24,	//进行穿戴装备

	QUEST_TARGET_TYPE_MOUNT_LEVEL			= 25, //坐骑达到x
	QUEST_TARGET_TYPE_FRIEND_NUM			= 26, //拥有好友x
	QUEST_TARGET_TYPE_KILL_MONSTER_NUM		= 27, //击杀怪物x
	QUEST_TARGET_TYPE_DIVINE_NUM			= 28, //拥有神兵x
	QUEST_TARGET_TYPE_DIVINE_LEV			= 29, //神兵等级x
	QUEST_TARGET_TYPE_DOUJIANTAI			= 30, //斗剑台胜利x
	QUEST_TARGET_TYPE_TITLE_NUMBER			= 31,	//称号数量达到x个
	QUEST_TARGET_TYPE_FASHION_NUMBER		= 32,	//时装数量达到x个

	QUEST_TARGET_TYPE_ACHIEVE				= 40,	//成就点数达到X点
	QUEST_TARGET_TYPE_SUIT_TITLE			= 41,	//佩戴X称号
	QUEST_TARGET_TYPE_SUIT_FASHION			= 42,	//穿上时装X
	QUEST_TARGET_TYPE_JOIN_DOUJIANTAI		= 43,	//参与X次斗剑台
	QUEST_TARGET_TYPE_JOIN_KUAFU_3V3		= 44,	//参与X次3V3
	QUEST_TARGET_TYPE_WIN_KUAFU_3V3			= 45,	//3v3获胜x次
	QUEST_TARGET_TYPE_JOIN_XIANFU			= 46,	//参与X次仙府夺宝
	QUEST_TARGET_TYPE_WIN_XIANFU			= 47,	//仙府夺宝获胜X次
	QUEST_TARGET_TYPE_KILL_MONSTER_COLLECT	= 48,	//杀怪收集物品
	QUEST_TARGET_TYPE_TURN_ITEM_IN			= 49,	//上交物品
	QUEST_TARGET_TYPE_PASS_WORLD_RISK		= 50,	//世界冒险通关
	QUEST_TARGET_TYPE_SMELT					= 51,	//熔炼装备
	QUEST_TARGET_TYPE_CONTRIBUTE_TIMES		= 52,	//为女王贡献次数
	QUEST_TARGET_TYPE_CONTRIBUTE_TOTAL_TIMES= 53,	//为女王贡献总次数
	QUEST_TARGET_TYPE_CONTRIBUTE_CHARM		= 54,	//为女王贡献魅力值
	QUEST_TARGET_TYPE_CONTRIBUTE_ITEM		= 55,	//为女王贡献道具
	QUEST_TARGET_TYPE_LOOT_ITEM				= 56,	//收集某些道具
	QUEST_TARGET_TYPE_SINGLE_THX_TIMES		= 57,	//女王单任务感谢次数
	QUEST_TARGET_TYPE_TOTAL_THX_TIMES		= 58,	//女王累计感谢次数

	QUEST_TARGET_TYPE_WINGS_UPGRADE_LEVEL	= 59,	//翅膀进阶等级达到X
	QUEST_TARGET_TYPE_WINGS_UPDRADE_TIMES	= 60,	//翅膀进阶升级X次
	QUEST_TARGET_TYPE_WINGS_STRENGTH_LEVEL	= 61,	//翅膀强化等级达到X
	QUEST_TARGET_TYPE_WINGS_STRENGTH_TIMES	= 62,	//翅膀强化升级X次

	QUEST_TARGET_TYPE_TALISMAN_LEVEL		= 63,	//升级任意法宝到X级
	QUEST_TARGET_TYPE_MOUNT_STRENGTH_LEVEL	= 64,	//坐骑强化等级达到X
	QUEST_TARGET_TYPE_REFINE_SUIT			= 65,	//指定槽位装备精炼x次
	QUEST_TARGET_TYPE_WASH_SUIT				= 66,	//指定槽位装备洗炼x次
	QUEST_TARGET_TYPE_MERIDIAN_LEVEL		= 67,	//经脉升到X级
	QUEST_TARGET_TYPE_JOIN_SINGLE_PVP		= 68,	//参加排位赛X次
	QUEST_TARGET_TYPE_SINGLE_PVP_WINS		= 69,	//排位赛胜利X次
	QUEST_TARGET_TYPE_ACTIVE_TASK			= 70,	//完成X个活跃任务
	QUEST_TARGET_TYPE_DAILY_TASK			= 71,	//完成X轮日常任务
	QUEST_TARGET_TYPE_GEM_TOTAL_LEVEL		= 72,	//所有宝石总等级升到X级
	QUEST_TARGET_TYPE_WINGS_BLESS_TIMES		= 73,	//翅膀祝福X次
	QUEST_TARGET_TYPE_MONEYTREE_TIMES		= 74,	//使用摇钱树X次

	QUEST_TARGET_TYPE_JOIN_MASS_BOSS_TIMES	= 75,	//参与X次全民Boss
	QUEST_TARGET_TYPE_MAIN_SKILL_UPGRADE_LEVEL	= 76,	//升级X个主动技能到Y级
	QUEST_TARGET_TYPE_SUB_SKILL_UPGRADE_LEVEL	= 77,	//升级X个被动技能到Y级

	QUEST_TARGET_TYPE_FINISH_QUEST_COUNT_TYPE_TIMES	= 78,	//完成某计数类型任务总记达到X次

	QUEST_TARGET_TYPE_ADVENTURE_SKILL_UPGRADE_LEVEL	= 79,	//将N个神器技能升级到X级
	QUEST_TARGET_TYPE_ADVENTURE_QUEST_FINISH_TIMES	= 80,	//完成N个历练任务
	QUEST_TARGET_TYPE_EQUIPS_FIT_REQUIRE	= 81,	//身上穿X级以上，Y品质以上的装备大于等于N件
	QUEST_TARGET_TYPE_ADVENTURE_QUEST_FINISH_TODAY	= 82,	//完成1次历练任务X
	QUEST_TARGET_TYPE_ADVENTURE_SKILL_ONE_LEVEL	= 83,	//将神器技能ID X升级到Y级
	QUEST_TARGET_TYPE_STAGE_INSTANCE_ID			= 84,	//闯关副本通关达到id
	QUEST_TARGET_TYPE_FACTION_SKILL_MULTI_LEVEL			= 85,	//将N个家族技能升级到X级
	QUEST_TARGET_TYPE_FACTION_TOWER_FLOOR		= 86,	//家族爬塔通关到X层
	QUEST_TARGET_TYPE_TRIAL_TOWER_FLOOR			= 87,	//试炼塔通关到X层
	QUEST_TARGET_TYPE_EQUIPDEVELOP_STRENGTH_MULTI_LEVEL	= 88,	//N件装备强化到X级
	QUEST_TARGET_TYPE_REALMBREAK_LEVEL	= 89,	//境界达到id
	QUEST_TARGET_TYPE_INSTANCE_EXP_TIMES		= 90,	//通关经验副本X 次
	QUEST_TARGET_TYPE_INSTANCE_GROUP_TIMES		= 91,	//通关组队副本X 次
	QUEST_TARGET_TYPE_EQUIPDEVELOP_REFINE_MULTI_LEVEL = 92,	//N件装备精炼到X级
	QUEST_TARGET_TYPE_VIP_LEVEL = 93,	//VIP等级到X级
};

//货币处理类型
enum CURRENCY_HANDLE_TYPE
{
	CURRENCY_HANDLE_TYPE_ADD	= 0,	//增加
	CURRENCY_HANDLE_TYPE_SUB	= 1,	//减少
};


//技能有效时间技能ID枚举
enum SpellYouXiaoTime
{
	SPELL_VALID_TIME_POTIAN_2		= 0,		//破天二式
	SPELL_VALID_TIME_POTIAN_3		= 1,		//破天三式
	SPELL_VALID_TIME_YUNFEI_2		= 2,		//云飞玉皇·二段
	SPELL_VALID_TIME_YUNFEI_3		= 3,		//云飞玉皇·三段
	SPELL_VALID_TIME_FENGFAN_2		= 4,		//风翻云变·二段
	SPELL_VALID_TIME_ZHUXIAN_2		= 5,		//诛仙剑阵·二段
	SPELL_VALID_TIME_ZHUXIAN_3		= 6,		//诛仙剑阵·三段
	MAX_SPELL_VALID		= 15,
};



#define MAX_SPELL_SLOT 6
#define NOMAL_ATTACK_TIME 1300
#define NOMAL_MOVE_SPEED 130
#define MAX_ITEM_SPELL	3

#define MAX_BASE_ATTR_FIELD_COUNT 15	//附加属性最大条数
#define MAX_BUFF 50						//玩家身上最大buff数
#define MAX_UNIT_BUFF 16				//精灵身上最大buff数

//装备类型包括时装 从头到脚
enum Equipment_Type
{
	//普通装备
	EQUIPMENT_TYPE_OTHER    	= 0,	//其他
	EQUIPMENT_TYPE_MAIN_WEAPON	= 1,	//武器
	EQUIPMENT_TYPE_COAT			= 2,	//衣服
	EQUIPMENT_TYPE_LEG			= 3,	//护腕
	EQUIPMENT_TYPE_BELT			= 4,	//腰带
	EQUIPMENT_TYPE_SHOES		= 5,	//鞋子
	EQUIPMENT_TYPE_HELMET		= 6,	//头盔
	EQUIPMENT_TYPE_NECKLACE		= 7,	//项链
	EQUIPMENT_TYPE_PANTS		= 8,	//裤子
	EQUIPMENT_TYPE_LRING		= 9,	//左戒指
	EQUIPMENT_TYPE_BRACELET		= 10,	//玉佩
	EQUIPMENT_TYPE_CLOAK		= 11,	//披风
	EQUIPMENT_TYPE_RRING		= 12,	//右戒指
	EQUIPMENT_TYPE_FASHION		= 13,	//时装
	EQUIPMENT_TYPE_RESERVE3		= 14,	//预留
	EQUIPMENT_TYPE_RESERVE4		= 15,	//预留
	EQUIPMENT_TYPE_RESERVE5		= 16,	//预留
	EQUIPMENT_TYPE_RESERVE6		= 17,	//预留
	EQUIPMENT_TYPE_RESERVE7		= 18,	//预留
	EQUIPMENT_TYPE_RESERVE8		= 19,	//预留
	EQUIPMENT_TYPE_MAX_POS		= EQUIPMENT_TYPE_RESERVE8 +1,	//最大位置

	//时装类型接在普通装备后面 从头到脚
	FASHION_TYPE_MAIN_WEAPON	= EQUIPMENT_TYPE_MAX_POS,	//头盔 预留
	FASHION_TYPE_HELMET			= EQUIPMENT_TYPE_MAX_POS + 1,	//耳坠
	FASHION_TYPE_COAT			= EQUIPMENT_TYPE_MAX_POS + 2,	//项链
	FASHION_TYPE_BELT			= EQUIPMENT_TYPE_MAX_POS + 3,	//披风
	FASHION_TYPE_LEG			= EQUIPMENT_TYPE_MAX_POS + 4,	//护肩 预留
	FASHION_TYPE_PANTS			= EQUIPMENT_TYPE_MAX_POS + 5,	//衣服
	FASHION_TYPE_SHOES			= EQUIPMENT_TYPE_MAX_POS + 6,	//主手武器
	FASHION_TYPE_BRACELET		= EQUIPMENT_TYPE_MAX_POS + 7,	//副手武器
	FASHION_TYPE_NECKLACE		= EQUIPMENT_TYPE_MAX_POS + 8,	//手镯 
	FASHION_TYPE_RING			= EQUIPMENT_TYPE_MAX_POS + 9,	//腰带
	FASHION_TYPE_CLOAK			= EQUIPMENT_TYPE_MAX_POS + 10,	//护手
	FASHION_TYPE_RESERVE1		= EQUIPMENT_TYPE_MAX_POS + 11,	//裤子 预留
	FASHION_TYPE_RESERVE2		= EQUIPMENT_TYPE_MAX_POS + 12,	//鞋子 预留
	FASHION_TYPE_RESERVE3		= EQUIPMENT_TYPE_MAX_POS + 13,	//特殊武器时装,现作为无双方天戟下标
	FASHION_TYPE_RESERVE4		= EQUIPMENT_TYPE_MAX_POS + 14,	//指环
	FASHION_TYPE_RESERVE5		= EQUIPMENT_TYPE_MAX_POS + 15,	//玉玺
	FASHION_TYPE_RESERVE6		= EQUIPMENT_TYPE_MAX_POS + 16,	//结婚戒指
	FASHION_TYPE_RESERVE7		= EQUIPMENT_TYPE_MAX_POS + 17,	//护符左
	FASHION_TYPE_RESERVE8		= EQUIPMENT_TYPE_MAX_POS + 18,	//护符右
	FASHION_TYPE_RESERVE9		= EQUIPMENT_TYPE_MAX_POS + 19,	//预留
	MAX_EQUIPMENT_TYPE			= FASHION_TYPE_RESERVE9 + 1,	//最多可装备位置
};

//武器类型
enum Weapon_Pos
{
	WEAPON_POS_MAIN				= 0,	//主手
	WEAPON_POS_OFF				= 1,	//副手
	WEAPON_POS_SINGLE_HAND		= 2,	//单手
	WEAPON_POS_BOTH_HANDS		= 3,	//双手
	MAX_WEAPON_POS											//不是武器
};

//能量类型,用于消耗
enum Powers
{
	POWER_MANA                          = 0,			//蓝,内力	
	POWER_ENERGY                        = 1,			//能量,体力	
	MAX_POWERS					
};

//战斗计算过程中的各种百分比
enum Combat_Rate
{
	COMBAT_RATE_CRIT				= 0,				//暴击率
	COMBAT_RATE_EVA					= 1,				//闪避率
	MAX_COMBAT_RATE
};

//包裹类型
enum Bag_Type
{
	BAG_TYPE_MAIN_BAG			= 0,	//主包裹
	BAG_TYPE_EQUIP				= 1,	//穿戴的装备包裹
	BAG_TYPE_EQUIP_BAG			= 2,	//放装备的包裹
	BAG_TYPE_GEM				= 3,	//消耗品的包裹
	BAG_TYPE_GEM_BAG			= 4,	//放宝石的包裹
	MAX_BAG,							//预留20个
};

//背包扩展类型
enum Bag_Extension_Type
{
	BAG_EXTENSION_TYPE_AUTO		= 0,	//自动开启
	BAG_EXTENSION_TYPE_GOLD		= 1,	//元宝开启
};

//安全码修改类型
enum Safety_Code_Modify_Type
{
	SAFETY_CODE_MODIFY_TYPE_CODE		= 0,	//密码修改
	SAFETY_CODE_MODIFY_TYPE_QUESTION	= 1,	//安全问题修改
};

// 资源类道具
enum Item_Loot_Resource 
{
	Item_Loot_Gold_Ingot = 1,	//元宝
	Item_Loot_Bind_Gold = 2,	//绑定元宝
	Item_Loot_Silver = 3,	//银币
	
	Item_Loot_Renown = 5,	//声望
	Item_Loot_Honor = 6,	//荣誉
	Item_Loot_Exploit  = 7,	//功勋
	Item_Loot_Contrib = 8,	//家族贡献
	Item_Loot_Exp = 104,		//经验
	Item_Loot_Mount_Exp = 10,	//坐骑经验
	Item_Loot_QI = 13,	//真气
	Item_Loot_BEAST = 14,	//兽灵
	Item_Loot_GEM = 15,	//宝石精华
	Item_Loot_Realmbreak_Exp = 107	//境界经验
};

//货币类型
enum Money_Type
{
	MONEY_TYPE_GOLD_INGOT			= 1,	//元宝
	MONEY_TYPE_BIND_GOLD			= 2,	//绑定元宝
	MONEY_TYPE_SILVER				= 3,	//身上的银子
	MONEY_TYPE_SILVER_WAREHOUSE		= 4,	//仓库的银子

	MAX_MONEY_TYPE					= 22,
};

//基本属性
enum Base_Attr
{
	BASE_ATTR_HP			= 0,					//生命
	BASE_ATTR_DAMAGE		= 1,					//攻击
	BASE_ATTR_ARMOR			= 2,					//防御
	BASE_ATTR_HIT			= 3,					//命中
	BASE_ATTR_DODGE			= 4,					//闪避
	BASE_ATTR_CRIT			= 5,					//暴击
	BASE_ATTR_CRIT_RESIST	= 6,					//坚韧
	BASE_MOVE_SPEED			= 7,					//移速
	BASE_ATTACK_SPEED		= 8,					//攻速
	MAX_BASE_ATTR
};

//应用服计算出来的属性枚举
//0用来当做无属性 约定基本属性放在枚举的最后面
enum Equip_Attr_Type
{
	EQUIP_ATTR_NONE			= 0,		//空属性
	EQUIP_ATTR_MAX_HEALTH = 1,	//最大生命
	EQUIP_ATTR_DAMAGE = 2,	//攻击力
	EQUIP_ATTR_ARMOR = 3,	//防御力
	EQUIP_ATTR_HIT = 4,	//命中
	EQUIP_ATTR_MISS = 5,	//闪避
	EQUIP_ATTR_CRIT = 6,	//暴击
	EQUIP_ATTR_TOUGH = 7,	//坚韧
	EQUIP_ATTR_ATTACK_SPEED = 8,	//攻击速度
	EQUIP_ATTR_MOVE_SPEED = 9,	//移动速度
	EQUIP_ATTR_IGNORE_ARMOR = 10,	//忽视防御
	EQUIP_ATTR_IGNORE_MISS = 11,	//忽视闪避
	EQUIP_ATTR_RECOVERY = 12,	//生命值回复
	EQUIP_ATTR_DAMAGE_AMPLIFY_RATE = 13,	//伤害加深(万分比)
	EQUIP_ATTR_DAMAGE_RESIST_RATE = 14,	//伤害减免(万分比)
	EQUIP_ATTR_DAMAGE_RETURN_RATE = 15,	//反弹伤害(万分比)
	EQUIP_ATTR_VAMPIRIC_RATE = 16,	//吸血光环(万分比)
	EQUIP_ATTR_RECOVERY_RATE = 17,	//回复效率(万分比)
	EQUIP_ATTR_CRIT_RATE = 18,	//暴击率(万分比)
	EQUIP_ATTR_CRIT_RESIST_RATE = 19,	//抗暴率(万分比)
	EQUIP_ATTR_CRIT_DAM_RATE = 20,	//暴击伤害倍数(万分比)
	EQUIP_ATTR_CRIT_RESIST_DAM_RATE = 21,	//降暴伤害倍数(万分比)
	EQUIP_ATTR_HIT_RATE = 22,	//命中率(万分比)
	EQUIP_ATTR_MISS_RATE = 23,	//闪避率(万分比)
	EQUIP_ATTR_STUN_RATE = 24,	//眩晕
	EQUIP_ATTR_ROOTS_RATE = 25,	//定身
	EQUIP_ATTR_SILENCE_RATE = 26,	//沉默
	EQUIP_ATTR_CHAOS_RATE = 27,	//混乱
	EQUIP_ATTR_CHARM_RATE = 28,	//魅惑
	EQUIP_ATTR_CONTROL_ENHANCE_RATE = 29,	//控制增强
	EQUIP_ATTR_CONTROL_RESIST_RATE = 30,	//控制减免
	EQUIP_ATTR_STRENGTH_ARMOR = 31,	//强化护甲
	EQUIP_ATTR_DAO			= 32,	//境界
	EQUIP_ATTR_PVP_DAMAGE_AMPLIFY_RATE = 33,	//PVP伤害增加
	EQUIP_ATTR_PVP_DAMAGE_RESIST_RATE = 34,	//减少PVP伤害
	EQUIP_ATTR_PVE_DAMAGE_AMPLIFY_RATE = 35,	//增加PVE伤害
	EQUIP_ATTR_DAMAGE_RESIST_VALUE = 36,	//减少伤害

	MAX_EQUIP_ATTR
};

//物品其他属性枚举（物品特殊属性接在MAX_EQUIP_ATTR后面）
enum EItemOtherAttrType
{
	ITEM_OTHER_ATTR_FAIL_TIME				= MAX_EQUIP_ATTR,						//失效时间
	ITEM_OTHER_ATTR_STRONG_LV				= ITEM_OTHER_ATTR_FAIL_TIME + 1,		//强化等级
	ITEM_OTHER_ATTR_STRONG_FAIL_COUNT		= ITEM_OTHER_ATTR_STRONG_LV + 1,		//强化失败次数
	ITEM_OTHER_ATTR_FORCE					= ITEM_OTHER_ATTR_STRONG_FAIL_COUNT + 1,//战斗力
};

//技能族公共CD类型
enum Spell_CD_Type
{
	SPELL_CD_BASE = 0,
	SPELL_CD_SPECIAL = 1,
	MAX_SPELL_CD_TYPE
};

//任务槽 偏移量
enum QuestSlotOffsets
{
	QUEST_ID_OFFSET			= 0,
	QUEST_STATE_OFFSET		= 1,
	QUEST_COUNTS_OFFSET		= 2,	
	QUEST_COUNTS_OFFSET_1   = 3,
	QUEST_COUNTS_OFFSET_2   = 4,
	QUEST_COUNTS_OFFSET_3   = 5,
	QUEST_TIME_OFFSET		= 6,
	QUEST_FLAG_OFFSET		= 7,	//bit标志位 看定义QuestSlotFlags
	MAX_QUEST_OFFSET
};

enum QuestSlotFlags
{
	QUEST_SLOT_FLAGS_REWARD		= 0,	//是否领取过任务奖励
	QUEST_SLOT_FLAGS_EXPLORE	= 1,	//是否已探索
};

#define MAX_QUEST_LOG_SIZE 32			//任务槽的上限
#define QUEST_OBJECTIVES_COUNT 8		//物品数量或杀死生物的数量上限
#define QUEST_REWARD_CHOICES_COUNT 6
#define QUEST_REWARDS_COUNT 4

#define QUEST_LOW_LEVEL_HIDE_DIFF 4

#define  QUEST_ITEMS_COUNTS 10		//任务物品最大容量
#define  QUEST_COMPLETE_LIST 200	//任务已完成列表的长度


#define BINLOG_STRING_FIELD_GUID 0	//所有binlog的guid位置
#define BINLOG_STRING_FIELD_NAME 1	//所有binlog的name位置
#define BINLOG_STRING_FIELD_VERSION 2 //所有binlog的版本信息位置
#define BINLOG_STRING_FIELD_OWNER 3	//所有binlog的owner位置


//战利品下标
enum ELootStruct
{
	LOOT_PUBLIC_INT_START_POS		= 0,								//grid开始坐标
	LOOT_PUBLIC_INT_END_POS			= 1,								//grid结束坐标
	LOOT_PUBLIC_INT_BEGIN			= 2,								//战利品真正开始的下标

	LOOT_PUBLIC_INT_ENTRY			= 0,								//战利品模板
	LOOT_PUBLIC_INT_MONEY_SUM		= LOOT_PUBLIC_INT_ENTRY + 1,		//金钱数量
	MAX_LOOT_PUBLIC_INT_FIELD,

	LOOT_PUBLIC_STR_OWNER			= 0,
	MAX_LOOT_PUBLIC_STR_FIELD,

	LOOT_PRIVATE_INT_FAIL_TIME		= 0,								//拾取以后的物品失效时间
	LOOT_PRIVATE_INT_EXIST_TIME		= LOOT_PRIVATE_INT_FAIL_TIME + 1,	//战利品存活时间
	LOOT_PRIVATE_INT_OWNER_TIME		= LOOT_PRIVATE_INT_EXIST_TIME + 1,	//战利品拥有者保护时间
	LOOT_PRIVATE_INT_FLAG			= LOOT_PRIVATE_INT_OWNER_TIME + 1,	//标志位
	MAX_LOOT_PRIVATE_INT_FIELD,

	LOOT_PRIVATE_STRING_CREATE_BY	= 0,								//战利品掉落怪GUID
	LOOT_PRIVATE_STRING_CREATE_NAME	= 1,								//战利品掉落怪名称
	MAX_LOOT_PRIVATE_STRING,

	LOOT_STR_FIELD_BEGIN = BINLOG_STRING_FIELD_OWNER + 1,				//战利品字符串开始下标
};

//战利品标志位
enum ELootFlag
{
	LOOT_FLAG_GET_ITEM_NOTICE				= 0,						//拾起物品是否需要公告
	LOOT_FLAG_ITEM_BIND						= 1,						//战利品是否绑定
};

#define PLAYER_PASSIVE_SPELL_MAX_COUNT 100		// 被动技能个数

//玩家能否做某事的flag偏移定义
enum EUintCanDoOffsetType
{
	UNIT_CANDO_OFFSET_TYPE_CANT_CAST				= 0,		//限制施法
	UNIT_CANDO_OFFSET_TYPE_CANT_MOVE				= 1,		//限制移动
};

#define MAX_FABAO_PASSIVE_SPELL_CD_COUNT 10

enum EUnitFields
{	
	UNIT_FIELD_BYTE_0					= 0,											//0:类型ID，1：死亡状态，2：移动速度，3：八卦阵等级
	UNIT_FIELD_BYTE_1					= UNIT_FIELD_BYTE_0 + 1,						//0：角色类型，1：阵营，2：种族，3：职业
	UNIT_FIELD_BYTE_2					= UNIT_FIELD_BYTE_1 + 1,						//0：灰名时间，1：付费等级，2：免费复活，3：玩家称号
	UNIT_FIELD_BYTE_3					= UNIT_FIELD_BYTE_2 + 1,						//0: 头像，1：发型，2：GM等级，3：下次复活是否有保护buff
	UNIT_FIELD_BYTE_4					= UNIT_FIELD_BYTE_3 + 1,						//0：预留，1：当前坐骑模板id，2：皮肤类型 3：预留
	UNIT_FIELD_MOUNT_LEVEL				= UNIT_FIELD_BYTE_4 + 1,						//4个bytes(0:当前坐骑阶数 1:当前坐骑星级,2:无用了，3:当前幻化id)
	UNIT_FIELD_DIVINE_ID				= UNIT_FIELD_MOUNT_LEVEL + 1,					//神兵id
	UNIT_FIELD_UINT16_0					= UNIT_FIELD_DIVINE_ID + 1,						//0：精灵模板，1：精灵等级
	UNIT_FIELD_UINT16_1					= UNIT_FIELD_UINT16_0 + 1,						//0：地图ID，1：跨服1v1连胜次数
	UNIT_FIELD_UINT16_2					= UNIT_FIELD_UINT16_1 + 1,						//0:玩家报名跨服时收到匹配信息中给的编号 1:身上宝物采集阵营编号
	UNIT_FIELD_SELF_DEFENSE_GUID		= UNIT_FIELD_UINT16_2 + 1,				//自卫模式下可以攻击的玩家intguid

	UNIT_FIELD_FLAGS					= UNIT_FIELD_SELF_DEFENSE_GUID + 1,						//精灵身上的标志位
	GO_FIELD_FLAGS						= UNIT_FIELD_FLAGS + 1,							//游戏对象的一些标识位
	GO_FIELD_DATA						= GO_FIELD_FLAGS + 1,							//动态数据字段,目前保留为4个int
	UNIT_FIELD_NPC_FLAG					= GO_FIELD_DATA + 4,							//NPC标识
	UNIT_FIELD_INSTANCE_ID				= UNIT_FIELD_NPC_FLAG + 1,						//地图实例ID
	UNIT_FIELD_EQUIPMENT_COAT			= UNIT_FIELD_INSTANCE_ID + 1,						//上衣模板
	UNIT_FIELD_EQUIPMENT_MAIN_WEAPON	= UNIT_FIELD_EQUIPMENT_COAT + 1,				//主手武器
	UNIT_FIELD_BUFF						= UNIT_FIELD_EQUIPMENT_MAIN_WEAPON +1,						//BUFFID

	//注意了：创建包需要下发的下标放在 UNIT_FIELD_BUFF前面,UNIT_FIELD_BUFF_TM后面的下标走订阅
	UNIT_FIELD_BUFF_TM					= UNIT_FIELD_BUFF + 8,							//BUFF时间（掩码从这开始）
	UNIT_FIELD_BUFF_RESERVE				= UNIT_FIELD_BUFF_TM + 8,						//BUFF预留值
	UNIT_FIELD_BUFF_EFFECT_ID			= UNIT_FIELD_BUFF_RESERVE + MAX_UNIT_BUFF,		//BUFF效果id
	UNIT_FIELD_BUFF_CASTER_GUID			= UNIT_FIELD_BUFF_EFFECT_ID + MAX_UNIT_BUFF,	//buff施法者guid

	UNIT_FIELD_FORCE						= UNIT_FIELD_BUFF_CASTER_GUID + MAX_UNIT_BUFF,	//战斗力
	UNIT_FIELD_HEALTH						= UNIT_FIELD_FORCE + 2,				//当前生命	

	UNIT_FIELD_MAX_HEALTH = UNIT_FIELD_HEALTH + 1,	//最大生命
	UNIT_FIELD_DAMAGE = UNIT_FIELD_MAX_HEALTH + 1,	//攻击力
	UNIT_FIELD_ARMOR = UNIT_FIELD_DAMAGE + 1,	//防御力
	UNIT_FIELD_HIT = UNIT_FIELD_ARMOR + 1,	//命中
	UNIT_FIELD_MISS = UNIT_FIELD_HIT + 1,	//闪避
	UNIT_FIELD_CRIT = UNIT_FIELD_MISS + 1,	//暴击
	UNIT_FIELD_TOUGH = UNIT_FIELD_CRIT + 1,	//坚韧
	UNIT_FIELD_ATTACK_SPEED = UNIT_FIELD_TOUGH + 1,	//攻击速度
	UNIT_FIELD_MOVE_SPEED = UNIT_FIELD_ATTACK_SPEED + 1,	//移动速度
	UNIT_FIELD_IGNORE_ARMOR = UNIT_FIELD_MOVE_SPEED + 1,	//忽视防御
	UNIT_FIELD_IGNORE_MISS = UNIT_FIELD_IGNORE_ARMOR + 1,	//忽视闪避
	UNIT_FIELD_RECOVERY = UNIT_FIELD_IGNORE_MISS + 1,	//生命值回复
	UNIT_FIELD_DAMAGE_AMPLIFY_RATE = UNIT_FIELD_RECOVERY + 1,	//伤害加深(万分比)
	UNIT_FIELD_DAMAGE_RESIST_RATE = UNIT_FIELD_DAMAGE_AMPLIFY_RATE + 1,	//伤害减免(万分比)
	UNIT_FIELD_DAMAGE_RETURN_RATE = UNIT_FIELD_DAMAGE_RESIST_RATE + 1,	//反弹伤害(万分比)
	UNIT_FIELD_VAMPIRIC_RATE = UNIT_FIELD_DAMAGE_RETURN_RATE + 1,	//吸血光环(万分比)
	UNIT_FIELD_RECOVERY_RATE = UNIT_FIELD_VAMPIRIC_RATE + 1,	//回复效率(万分比)
	UNIT_FIELD_CRIT_RATE = UNIT_FIELD_RECOVERY_RATE + 1,	//暴击率(万分比)
	UNIT_FIELD_CRIT_RESIST_RATE = UNIT_FIELD_CRIT_RATE + 1,	//抗暴率(万分比)
	UNIT_FIELD_CRIT_DAM_RATE = UNIT_FIELD_CRIT_RESIST_RATE + 1,	//暴击伤害倍数(万分比)
	UNIT_FIELD_CRIT_RESIST_DAM_RATE = UNIT_FIELD_CRIT_DAM_RATE + 1,	//降暴伤害倍数(万分比)
	UNIT_FIELD_HIT_RATE = UNIT_FIELD_CRIT_RESIST_DAM_RATE + 1,	//命中率(万分比)
	UNIT_FIELD_MISS_RATE = UNIT_FIELD_HIT_RATE + 1,	//闪避率(万分比)
	UNIT_FIELD_STUN_RATE = UNIT_FIELD_MISS_RATE + 1,	//眩晕
	UNIT_FIELD_ROOTS_RATE = UNIT_FIELD_STUN_RATE + 1,	//定身
	UNIT_FIELD_SILENCE_RATE = UNIT_FIELD_ROOTS_RATE + 1,	//沉默
	UNIT_FIELD_CHAOS_RATE = UNIT_FIELD_SILENCE_RATE + 1,	//混乱
	UNIT_FIELD_CHARM_RATE = UNIT_FIELD_CHAOS_RATE + 1,	//魅惑
	UNIT_FIELD_CONTROL_ENHANCE_RATE = UNIT_FIELD_CHARM_RATE + 1,	//控制增强
	UNIT_FIELD_CONTROL_RESIST_RATE = UNIT_FIELD_CONTROL_ENHANCE_RATE + 1,	//控制减免
	UNIT_FIELD_STRENGTH_ARMOR = UNIT_FIELD_CONTROL_RESIST_RATE + 1,	//强化护甲
	UNIT_FIELD_DAO			= UNIT_FIELD_STRENGTH_ARMOR + 1,	//境界
	UNIT_FIELD_PVP_DAMAGE_AMPLIFY_RATE = UNIT_FIELD_DAO + 1,	//PVP伤害增加
	UNIT_FIELD_PVP_DAMAGE_RESIST_RATE = UNIT_FIELD_PVP_DAMAGE_AMPLIFY_RATE + 1,	//减少PVP伤害
	UNIT_FIELD_PVE_DAMAGE_AMPLIFY_RATE = UNIT_FIELD_PVP_DAMAGE_RESIST_RATE + 1,	//增加PVE伤害
	UNIT_FIELD_DAMAGE_RESIST_VALUE = UNIT_FIELD_PVE_DAMAGE_AMPLIFY_RATE + 1,	//减少伤害


	UNIT_FIELD_ATTRIBUTE_END				= UNIT_FIELD_DAMAGE_RESIST_VALUE + 1,	// 属性结束

	UNIT_FIELD_MAX_HEALTH_BASE = UNIT_FIELD_ATTRIBUTE_END,	//最大生命
	UNIT_FIELD_DAMAGE_BASE = UNIT_FIELD_MAX_HEALTH_BASE + 1,	//攻击力
	UNIT_FIELD_ARMOR_BASE = UNIT_FIELD_DAMAGE_BASE + 1,	//防御力
	UNIT_FIELD_HIT_BASE = UNIT_FIELD_ARMOR_BASE + 1,	//命中
	UNIT_FIELD_MISS_BASE = UNIT_FIELD_HIT_BASE + 1,	//闪避
	UNIT_FIELD_CRIT_BASE = UNIT_FIELD_MISS_BASE + 1,	//暴击
	UNIT_FIELD_TOUGH_BASE = UNIT_FIELD_CRIT_BASE + 1,	//坚韧
	UNIT_FIELD_ATTACK_SPEED_BASE = UNIT_FIELD_TOUGH_BASE + 1,	//攻击速度
	UNIT_FIELD_MOVE_SPEED_BASE = UNIT_FIELD_ATTACK_SPEED_BASE + 1,	//移动速度
	UNIT_FIELD_IGNORE_ARMOR_BASE = UNIT_FIELD_MOVE_SPEED_BASE + 1,	//忽视防御
	UNIT_FIELD_IGNORE_MISS_BASE = UNIT_FIELD_IGNORE_ARMOR_BASE + 1,	//忽视闪避
	UNIT_FIELD_RECOVERY_BASE = UNIT_FIELD_IGNORE_MISS_BASE + 1,	//生命值回复
	UNIT_FIELD_DAMAGE_AMPLIFY_RATE_BASE = UNIT_FIELD_RECOVERY_BASE + 1,	//伤害加深(万分比)
	UNIT_FIELD_DAMAGE_RESIST_RATE_BASE = UNIT_FIELD_DAMAGE_AMPLIFY_RATE_BASE + 1,	//伤害减免(万分比)
	UNIT_FIELD_DAMAGE_RETURN_RATE_BASE = UNIT_FIELD_DAMAGE_RESIST_RATE_BASE + 1,	//反弹伤害(万分比)
	UNIT_FIELD_VAMPIRIC_RATE_BASE = UNIT_FIELD_DAMAGE_RETURN_RATE_BASE + 1,	//吸血光环(万分比)
	UNIT_FIELD_RECOVERY_RATE_BASE = UNIT_FIELD_VAMPIRIC_RATE_BASE + 1,	//回复效率(万分比)
	UNIT_FIELD_CRIT_RATE_BASE = UNIT_FIELD_RECOVERY_RATE_BASE + 1,	//暴击率(万分比)
	UNIT_FIELD_CRIT_RESIST_RATE_BASE = UNIT_FIELD_CRIT_RATE_BASE + 1,	//抗暴率(万分比)
	UNIT_FIELD_CRIT_DAM_RATE_BASE = UNIT_FIELD_CRIT_RESIST_RATE_BASE + 1,	//暴击伤害倍数(万分比)
	UNIT_FIELD_CRIT_RESIST_DAM_RATE_BASE = UNIT_FIELD_CRIT_DAM_RATE_BASE + 1,	//降暴伤害倍数(万分比)
	UNIT_FIELD_HIT_RATE_BASE = UNIT_FIELD_CRIT_RESIST_DAM_RATE_BASE + 1,	//命中率(万分比)
	UNIT_FIELD_MISS_RATE_BASE = UNIT_FIELD_HIT_RATE_BASE + 1,	//闪避率(万分比)
	UNIT_FIELD_STUN_RATE_BASE = UNIT_FIELD_MISS_RATE_BASE + 1,	//眩晕
	UNIT_FIELD_ROOTS_RATE_BASE = UNIT_FIELD_STUN_RATE_BASE + 1,	//定身
	UNIT_FIELD_SILENCE_RATE_BASE = UNIT_FIELD_ROOTS_RATE_BASE + 1,	//沉默
	UNIT_FIELD_CHAOS_RATE_BASE = UNIT_FIELD_SILENCE_RATE_BASE + 1,	//混乱
	UNIT_FIELD_CHARM_RATE_BASE = UNIT_FIELD_CHAOS_RATE_BASE + 1,	//魅惑
	UNIT_FIELD_CONTROL_ENHANCE_RATE_BASE = UNIT_FIELD_CHARM_RATE_BASE + 1,	//控制增强
	UNIT_FIELD_CONTROL_RESIST_RATE_BASE = UNIT_FIELD_CONTROL_ENHANCE_RATE_BASE + 1,	//控制减免
	UNIT_FIELD_STRENGTH_ARMOR_BASE = UNIT_FIELD_CONTROL_RESIST_RATE_BASE + 1,	//强化护甲
	UNIT_FIELD_DAO_BASE					= UNIT_FIELD_STRENGTH_ARMOR_BASE + 1,	// 境界

	UNIT_FIELD_PVP_DAMAGE_AMPLIFY_RATE_BASE = UNIT_FIELD_DAO_BASE + 1,	//PVP伤害增加
	UNIT_FIELD_PVP_DAMAGE_RESIST_RATE_BASE = UNIT_FIELD_PVP_DAMAGE_AMPLIFY_RATE_BASE + 1,	//减少PVP伤害
	UNIT_FIELD_PVE_DAMAGE_AMPLIFY_RATE_BASE = UNIT_FIELD_PVP_DAMAGE_RESIST_RATE_BASE + 1,	//增加PVE伤害
	UNIT_FIELD_DAMAGE_RESIST_VALUE_BASE = UNIT_FIELD_PVE_DAMAGE_AMPLIFY_RATE_BASE + 1,	//减少伤害

	UNIT_FIELD_ATTRIBUTE_BASE_END			= UNIT_FIELD_DAMAGE_RESIST_VALUE_BASE + 1,	// 属性结束

	UNIT_FIELD_ANGER						= UNIT_FIELD_ATTRIBUTE_BASE_END,	//愤怒值
	UNIT_FIELD_USE_RESPAWN_MAPID			= UNIT_FIELD_ANGER	+ 1,				//使用复活丹的地图id

	UNIT_FIELD_PROCESS_TIME					= UNIT_FIELD_USE_RESPAWN_MAPID + 1,			// 进度条读完的时间戳
	UNIT_FIELD_PROCESS_SECONDS				= UNIT_FIELD_PROCESS_TIME + 1,  // 读条总共需要时间	
	
	UINT_FIELD_BOSS_DATA					= UNIT_FIELD_PROCESS_SECONDS + 1,			//boss数据byte 0:boss状态 1:boss前一状态 2:boss索引(云游的是这个用途)
	UINT_FIELD_BOSS_DATA1					= UINT_FIELD_BOSS_DATA + 1,		//boss数据byte 0:当前坐标x 1:当前坐标y 2:下一坐标x 3:下一坐标y(云游的是这个用途)
	UINT_FIELD_VIEW_MODE					= UINT_FIELD_BOSS_DATA1,		//是否是观看模式

	UINT_FIELD_VIRTUAL_CAMP					= UINT_FIELD_VIEW_MODE + 1,		//虚拟阵营

	UINT_FIELD_XIANFU_INFO					= UINT_FIELD_VIRTUAL_CAMP + 1,	//跨服仙府的信息4bytes (0:宝箱数量, 1:死亡次数)

	UINT_FIELD_VIP_LEVEL					= UINT_FIELD_XIANFU_INFO + 1,	//VIP等级
	UINT_FIELD_VIP_TIME_OUT					= UINT_FIELD_VIP_LEVEL + 1,		//VIP超时时间

	UINT_FIELD_VAMPIRIC						= UINT_FIELD_VIP_TIME_OUT + 1,	//当前战斗的吸血值

	UINT_INT_FIELD_ILLUSION					= UINT_FIELD_VAMPIRIC + 2,	//角色幻化

	UINT_FIELD_BOOS_CUR_SPELLID				= UINT_INT_FIELD_ILLUSION + 1,	//当前正在释放的蓄力技能idUNIT_INT_FIELD_APPEARANCE
	UINT_FIELD_BOOS_CUR_SPELL_TIME			= UINT_FIELD_BOOS_CUR_SPELLID + 1,	//前一个技能结束的时间戳
	UINT_FIELD_BOOS_CUR_SPELL_LAST_COUNT	= UINT_FIELD_BOOS_CUR_SPELL_TIME + 1,	// 持续技能数量

	UINT_INT_FIELD_PASSIVE_SPELL_START		= UINT_FIELD_BOOS_CUR_SPELL_LAST_COUNT + 1,	//被动技能开始
	UINT_INT_FIELD_PASSIVE_SPELL_END		= UINT_INT_FIELD_PASSIVE_SPELL_START + PLAYER_PASSIVE_SPELL_MAX_COUNT,	//被动技能结束

	UINT_INT_FIELD_WINGS_RANK				= UINT_INT_FIELD_PASSIVE_SPELL_END,	//神羽阶数

	UNIT_INT_FIELD_APPEARANCE				= UINT_INT_FIELD_WINGS_RANK + 1,	// 外观
	UNIT_INT_FIELD_RISK_CREATURE_ID			= UNIT_INT_FIELD_APPEARANCE + 1,	// 世界冒险怪物对应的序号

	UNIT_INT_FIELD_OPERATE_CD				= UNIT_INT_FIELD_RISK_CREATURE_ID + 1,	//场景服操作冷却

	UNIT_INT_FIELD_LAST_HURT_TIMESTAMP		= UNIT_INT_FIELD_OPERATE_CD + 1,		//最后受伤害的时间戳

	UNIT_INT_FIELD_BOSS_OWN_FLAG			= UNIT_INT_FIELD_LAST_HURT_TIMESTAMP + 1,	//是否拥有boss的flag

	UNIT_INT_FIELD_FABAO_PASSIVE_SPELL_START	= UNIT_INT_FIELD_BOSS_OWN_FLAG + 1,				//被动技能开始
	UNIT_INT_FIELD_FABAO_PASSIVE_SPELL_END		= UNIT_INT_FIELD_FABAO_PASSIVE_SPELL_START + PLAYER_TALISMAN_SLOT_COUNT,	//被动技能个数

	UNIT_INT_FIELD_FABAO_PASSIVE_SPELL_CD_START	= UNIT_INT_FIELD_FABAO_PASSIVE_SPELL_END,				//被动技能CD开始
	UNIT_INT_FIELD_FABAO_PASSIVE_SPELL_CD_END	= UNIT_INT_FIELD_FABAO_PASSIVE_SPELL_CD_START + MAX_FABAO_PASSIVE_SPELL_CD_COUNT,		//被动技能CD结束

	UNIT_INT_FIELD_MOUNT_RIDE					= UNIT_INT_FIELD_FABAO_PASSIVE_SPELL_CD_END,			//是否骑乘

	MAX_UNIT_FIELD,

	GO_STRING_FIELD_CREATED_BY		= BINLOG_STRING_FIELD_OWNER + 1,
	UNIT_STRING_FIELD_ALIAS_NAME	= GO_STRING_FIELD_CREATED_BY + 1,
	UNIT_STRING_FIELD_PICK_NAME		= UNIT_STRING_FIELD_ALIAS_NAME + 1,			//正在采集的玩家

	UNIT_STRING_FIELD_GROUP_PEACE_ID	= UNIT_STRING_FIELD_PICK_NAME + 1,			// 组队id
	UNIT_STRING_FIELD_FACTION_GUID		= UNIT_STRING_FIELD_GROUP_PEACE_ID + 1,		// 帮派id
	UNIT_STRING_FIELD_FACTION_NAME		= UNIT_STRING_FIELD_FACTION_GUID + 1,		// 帮派名字

	UNIT_STRING_FIELD_DROP_OWNER_GUID	= UNIT_STRING_FIELD_FACTION_NAME + 1,		// 掉落物所属guid
	UNIT_STRING_FIELD_DROP_OWNER_NAME	= UNIT_STRING_FIELD_DROP_OWNER_GUID + 1,	// 掉落物所属名字

	MAX_UNIT_STRING_FIELD,
};


//游戏对象类型
#define  GO_ENTRY_TELETEPORT 1		//传送点
#define  GO_ENTRY_LOOT 9			//战利品游戏对象

//游戏对象数据
enum GameObject_Data
{
	//传送点专用
	GO_TELETEPORTER_TO_MAPID	= GO_FIELD_DATA,
	GO_TELETEPORTER_TO_X		= GO_TELETEPORTER_TO_MAPID + 1,
	GO_TELETEPORTER_TO_Y		= GO_TELETEPORTER_TO_X + 1,

	//任务相关游戏对象
	GO_QUEST_ID_0				= GO_FIELD_DATA + 0,					//相关任务0
	GO_QUEST_ID_1				= GO_FIELD_DATA + 1,					//相关任务1
	GO_QUEST_ID_2				= GO_FIELD_DATA + 2,					//相关任务2
	GO_QUEST_ID_3				= GO_FIELD_DATA + 3,					//相关任务3

	GO_STRING_FIELD_CREATED_NAME	= UNIT_STRING_FIELD_ALIAS_NAME,		//战利品创建者Name

	//机关类相关的
	GO_GEAR_STATUS				= GO_FIELD_DATA,						//机关状态
	GO_GEAR_KILLER				= GO_FIELD_DATA + 1						//机关破坏者
};

//机关状态枚举
enum GO_GEAR_STATUS_TYPE
{
	GO_GEAR_STATUS_START		= 1,			//机关初始状态
	GO_GEAR_STATUS_OPEN			= 2,			//机关打开
	GO_GEAR_STATUS_CLOSE		= 3,			//机关关闭
	GO_GEAR_STATUS_END			= 4,			//机关即将消失
	GO_GEAR_STATUS_MAX
};

//精灵身上标识下标枚举
enum EUnitFlagsType
{
	UNIT_FIELD_FLAGS_CANT_CAST					= 0,		//标识是否可以施法
	UNIT_FIELD_FLAGS_CANT_MOVE					= 1,		//标识是否可以移动
	UNIT_FIELD_FLAGS_BUFF_DAZUO					= 2,		//标识是否打坐buff
	UNIT_FIELD_FLAGS_GUAJIBAOHU					= 3,		//标识是否是挂机保护
	UNIT_FIELD_FLAGS_FACTION_LINGXIU			= 4,		//帮派领袖BUFF
	UNIT_FIELD_FLAGS_FACTION_GUWU				= 5,		//帮派鼓舞BUFF
	UNIT_FIELD_FLAGS_IS_BOSS_CREATURE			= 6,		//标识是否是副本boss怪
	UNIT_FIELD_FLAGS_USE_GAMEOBJECT				= 7,		//标识是否使用游戏对象
	UNIT_FIELD_FLAGS_IS_FLZ_PUB_CREATURE		= 8,		//标识是否风流镇酒馆怪
	UNIT_FIELD_FLAGS_QUEST_FOLLOW_CREATUR		= 9,		//做任务刷出来的跟谁宠物，任务完成时删掉
	UNIT_FIELD_FLAGS_IS_PVP						= 10,		//是否是PVP
	UNIT_FIELD_FLAGS_IS_FIELD_BOSS_CREATURE		= 11,		//标识是否是野外boss怪
	UNIT_FIELD_FLAGS_IS_INVISIBLE_SPELL			= 12,		//隐藏的技能NPC
};

//场景服专用的玩家状态下标枚举
enum EPlayerScenedFlasType
{
	PLAYER_SCENED_FLAS_HUNG_UP					= 0,		//挂机状态
	PLAYER_SCENED_FLAS_PVP_STATE				= 1,		//PVP状态
	PLAYER_SCENED_FLAGS_FUBEN_HUNG_UP			= 2,		//标识是否副本连续挂机状态
};

//玩家应用服标志位，玩家选项
enum EPlayerAppdFlags
{
	PLAYER_APPD_INT_FIELD_FLAGS_IS_ZIBAO				= 0,					//玩家是否自爆
	PLAYER_APPD_INT_FIELD_FLAGS_YEYOU_ONLINE			= 1,					//页游是否在线，客户端用的
	PLAYER_APPD_INT_FIELD_FLAGS_PHONE_ONLINE			= 2,					//手游是否在线，客户端用的
	PLAYER_APPD_INT_FIELD_FLAGS_FROM_KUAFU				= 3,					//玩家是否从pk回到游戏服
	PLAYER_APPD_INT_FIELD_FLAGS_GIFT_CREATE				= 4,					//礼包是否已创建
	PLAYER_APPD_INT_FIELD_FLAGS_LIMIT_CREATE			= 5,					//限时活动是否已创建
	PLAYER_APPD_INT_FIELD_FLAGS_IS_FIRST_RECHARGE		= 6,					//是否已经首充
	PLAYER_APPD_INT_FIELD_FLAGS_NEW_PLAYER				= 7,					//是否新玩家，是新玩家则发放礼包等等。。
	PLAYER_APPD_INT_FIELD_FLAGS_SAFETY_CODE_CHECK		= 8,					//标识安全码验证是否通过
	PLAYER_APPD_INT_FIELD_FLAGS_AUTO_GROUP				= 9,					//玩家是否自动接受组队
	PLAYER_APPD_INT_FIELD_FLAGS_IS_HOSTING_LOGIN		= 10,					//是否是托管登录
	PLAYER_APPD_INT_FIELD_FLAGS_IS_HOSTING_APPLY		= 11,					//是否托管申请中
	PLAYER_APPD_INT_FIELD_FLAGS_SOCIAL_CREATE			= 12,					//社交系统是否以创建	
	PLAYER_APPD_INT_FIELD_FLAGS_ITEM_CREATE				= 13,					//物品binlog是否创建
	PLAYER_APPD_INT_FIELD_FLAGS_LOGICAL_CREATE			= 14,					//业务逻辑binlog是否创建
	PLAYER_APPD_INT_FIELD_FLAGS_SPELL_CREATE			= 15,					//技能binlog是否创建
	PLAYER_APPD_INT_FIELD_FLAGS_INSTANCE_CREATE			= 16,					//副本binlog是否创建
	PLAYER_APPD_INT_FIELD_FLAGS_QUEST_CREATE			= 17,					//任务binlog是否创建
};

//基本潜力点属性
enum QianLi_Type
{
	QIANLI_TYPE_LILIANG                     = 0,	//力量
	QIANLI_TYPE_TIZHI				        = 1,	//体质
	QIANLI_TYPE_SHENFA						= 2,	//身法
	QIANLI_TYPE_FANGYU						= 3,	//狂暴
	MAX_QIANLI_TYPE					 
};

//客户端使用的数字下标数量
#define MAX_CLIENT_UINT32_COUNT 100
//客户端使用的字符串下标数量
#define MAX_CLIENT_STRING_COUNT 20

#define MAX_ITEMS_CD_COUNT 20				//物品大cd最大数量(20个保存时间戳)
#define MAX_ITEM_USED_COUNT 5				//物品大cd使用次数(5个byte保存次数)


#define MAX_SPELL_CAPACITY 20				   //最多拥有的技能数
//技能
enum ESpellBASE
{
	SPELL_BASE_LEVEL = 0,						//技能等级
	SPELL_BASE_FORCE = 1,						//技能等级对应的战斗力
	SPELL_BASE_ID	 = 2,						//技能ID
	MAX_SPELLBASE, 
};

enum Functional_Spell
{
	FUNCTIONAL_QING_GONG 	= 1,	//轻功
	FUNCTIONAL_TI_YUN_ZONG = 2,		//梯云纵
	FUNCTIONAL_RIDE		= 3,		//骑乘
	FUNCTIONAL_DA_ZUO		= 4,	//打坐
};

#define PLAYER_SLOT_SPELL_MAX_COUNT 12			// 玩家技能槽信息上限
#define PLAYER_IMPORTANT_CD_COUNT 20			// 玩家重要技能的CD

// 玩家技能槽的技能信息
enum SLOT_SPELL_ATTR
{
	SHORT_SLOT_SPELL_ID		= 0,	//技能槽中的技能id	占一个short

	BYTE_SLOT_SPELL_LV		= 2,	//技能槽中的技能lv	占一个byte
	BYTE_SLOT				= 3		//技能槽的位置		占一个byte
};

// 技能激活方式
enum SPELL_ACTIVE_WAYS
{
	SPELL_ACTIVE_BY_LEVEL	= 0,	//等级激活
	SPELL_ACTIVE_BY_QUEST	= 1,	//任务激活
	SPELL_ACTIVE_BY_ITEM	= 2,	//道具激活
};


// 要在binlog中存CD的重要技能CD信息
enum IMPORTANCE_SPELL_CD_INFO
{
	IMPORTANT_SPELL_ID = 0,	//技能id
	IMPORTANT_SPELL_CD = 1,	//技能CD
	MAX_IMPORTANT_SPELL_ATTR_COUNT
};

// 要在binlog中存开启功能的信息
enum OPEN_MENU_INFO
{
	OPEN_MENU_MAIN_ID = 0,	//主菜单id
	OPEN_MENU_SUB_FLAG = 1,	//子菜单flag
	MAX_OPEN_MENU_ATTR_COUNT
};

enum GiftPacksType
{
	GIFT_PACKS_TYPE_ITEM_GIVE = 0,						//用GM命令生成
	GIFT_PACKS_TYPE_SYSTEM_COMPENSATION = 1,			//系统补偿
	GIFT_PACKS_TYPE_BAG_FULL = 2,						//背包满了
	GIFT_PACKS_TYPE_LEVEL_RANK = 3,						//排行榜
	GIFT_PACKS_TYPE_WORLD_BOSS = 4,						//世界BOSS
	GIFT_PACKS_TYPE_3V3_WEEK = 5,						//3v3周奖励
	GIFT_PACKS_TYPE_3V3_MONTH = 6,						//3v3月奖励（段位奖励）
	GIFT_PACKS_TYPE_DOUJIAN_DAY = 7,					//斗剑台每日奖励
	GIFT_PACKS_TYPE_FACTION_BOSS = 8,					//家族boss奖励
	GIFT_PACKS_TYPE_FACTION_GIFT_RANK = 9,				//家族魅力排行奖励
	GIFT_PACKS_TYPE_ACT_RANK = 10,						//开服排行奖励
	GIFT_PACKS_TYPE_MASS_BOSS = 11,						// 全民boss
	GIFT_PACKS_TYPE_ESCORT_ROB = 12,					// 劫镖奖励
	GIFT_PACKS_TYPE_RECHARGE = 13,					// 充值活动奖励
	GIFT_PACKS_TYPE_GIFTCODE = 14,					// 兑换码奖励
};

enum SCENED_APPD_DO_SOMETHING_TYPE
{
	SCENED_APPD_ENTER_DAILY_INSTANCE = 1,	//进入日常副本
	SCENED_APPD_ENTER_VIP_INSTANCE = 2,		//进入VIP副本
	SCENED_APPD_USE_ITEM = 3,				//使用血瓶
	SCENED_APPD_USE_RESPAWN_ITEM = 4,		//使用复活丹
	SCENED_APPD_ENTER_TRIAL_INSTANCE = 5,	//进入试炼塔副本
	SCENED_APPD_PASS_TRIAL_INSTANCE = 6,	//通关试炼塔副本
	SCENED_APPD_PASS_VIP_INSTANCE = 7,		//通关VIP副本
	SCENED_APPD_ADD_ENEMY = 8,				//增加仇人
	SCENED_APPD_ENTER_RES_INSTANCE = 9,		//进入资源副本
	SCENED_APPD_ADD_MAIL = 10,				//增加邮件
	SCENED_APPD_PASS_RES_INSTANCE = 11,		//通关资源副本

	SCENED_APPD_KILL_MONSTER	= 12,		//杀怪
	SCENED_APPD_JOIN_FIELD_BOSS	= 13,		//参加野外BOSS
	SCENED_APPD_GAMEOBJECT		= 14,		//采集物品
	SCENED_APPD_TALK			= 15,		//对话

	SCENED_APPD_RIDE			= 16,		//骑乘
	SCENED_APPD_GOLD_RESPAWN	= 17,		//元宝复活

	SCENED_APPD_DOUJIANTAI				= 18,		//斗剑台结果
	SCENED_APPD_KILL_MONSTER_COLLECT	= 19,		//杀怪收集物品
	SCENED_APPD_XIULIANCHANG			= 20,		//修练场掠夺结果
	SCENED_APPD_XIANFU_PRACTISE			= 21,		//仙府体验

	SCENED_APPD_ADD_OFFLINE_RISK_REWARD	= 22,		//离线冒险世界奖励
	SCENED_APPD_PASS_WORLD_RISK			= 23,		//通关冒险世界

	SCENED_APPD_ENTER_MASS_BOSS_INSTANCE = 24,		//进入全民boss副本

	SCENED_APPD_FACTION_TOWER_WIN		= 25,		//无尽远征 胜利

	SCENED_APPD_SINGLE_PVP_RESULT		= 26,		// 排位赛结果

	SCENED_APPD_ENTER_QUALIFY_INSTANCE = 27,	//进入排位赛

	SCENED_APPD_ENTER_FACTION_TOWER_INSTANCE	= 28,	//进入家族远征

	SCENED_APPD_PRIVATE_BOSS_WIN		= 29,	//个人Boss胜利

	SCENED_APPD_ENTER_DOUJIANTAI_INSTANCE = 30,		//进入斗剑台副本

	SCENED_APPD_WORLD_BOSS_ENROLL = 31,		//世界boss报名

	SCENED_APPD_ENTER_FACTION_BOSSDEFENSE_INSTANCE = 32,	//进入家族Boss

	SCENED_APPD_ENTER_PRIVATE_BOSS_INSTANCE		= 33,	//进入个人Boss

	SCENED_APPD_PLAYER_DEAD_PROCESS		= 34,	//玩家死亡处理

	SCENED_APPD_ENTER_STAGE_INSTANCE	= 35,	//玩家进入闯关副本
	SCENED_APPD_PASS_STAGE_INSTANCE		= 36,	//玩家通过闯关副本

	SCENED_APPD_ENTER_GROUP_EXP_INSTANCE = 40,	//玩家进入组队经验副本
	SCENED_APPD_ENTER_BUY_INSPIRATION	 = 41,	//购买鼓舞
	SCENED_APPD_ENTER_FACTION_MATCH_INSTANCE = 42,	//玩家进入家族战
	SCENED_APPD_ENTER_GROUP_INSTANCE = 43,	//玩家组队副本
	SCENED_APPD_PASS_GROUP_INSTANCE = 44,	//通关组队副本

	SCENED_APPD_PASS_MASS_BOSS_INSTANCE = 45,	//杀了一个首领

	SCENED_APPD_PASS_LOCAL_3V3	= 46,		// 结束local3v3

	SCENED_APPD_QUEST_MASS_BOSS = 47, //完成世界boss任务
};

enum APPD_SCENED_DO_SOMETHING_TYPE
{
	APPD_SCENED_SWEEP_TRIAL_INSTANCE = 1,	//扫荡试炼塔副本
	APPD_SCENED_SWEEP_VIP_INSTANCE = 2,		//扫荡VIP副本
	APPD_SCENED_RESPAWN = 3,				//元宝复活
	APPD_SCENED_NEAR_BY_CHAT = 4,			//附近聊天
	APPD_SCENED_ADD_EXP = 5,				//场景服加经验
	
	APPD_SCENED_CLEAR_FIELD_BOSS = 6,		//场景服清理野外BOSS
	APPD_SCENED_REBORN_FIELD_BOSS = 7,		//场景服刷新野外

	APPD_SCENED_WORLD_BOSS_WAITING = 8,		//进入世界BOSS等待房间
	APPD_SCENED_FIGHT_WORLD_BOSS = 9,		//可挑战开始世界BOSS
	APPD_SCENED_WORLD_BOSS_END = 10,		//世界BOSS结束
	APPD_SCENED_WORLD_BOSS_ENTER = 11,		//进入世界BOSS房间
	APPD_SCENED_REMIND_INSTANCE_ENTER = 12,	//进入原地副本房间

	APPD_SCENED_MASS_BOSS_REBORN = 13, //全民boss重生

	APPD_SCENED_TELEPORT		=	14,	//传送

	APPD_SCENED_CHECK_ENTER_FACTION_BOSSDEFENSE	=	15,	//检测进入家族boss
	APPD_SCENED_CHECK_ENTER_FACTION_TOWER		=   16,	//检测进入家族远征

	APPD_SCENED_USE_RESTORE_POTION				=   17,	//使用回复药

	APPD_SCENED_INSPIRATION						=   18,	//进行鼓舞

	APPD_SCENED_RESETDAILY						= 19,	//告诉场景服进行重置
};

enum INSTANCE_SUB_TYPE
{
	INSTANCE_SUB_TYPE_VIP					= 1,		//vip副本
	INSTANCE_SUB_TYPE_TRIAL					= 2,		//试炼塔副本
	INSTANCE_SUB_TYPE_WORLD_BOSS			= 3,		//世界BOSS
	INSTANCE_SUB_TYPE_RES					= 4,		//资源副本
	INSTANCE_SUB_TYPE_KUAFU_3V3				= 5,		//跨服3v3
	INSTANCE_SUB_TYPE_XIANFU				= 6,		//仙府夺宝
	INSTANCE_SUB_TYPE_DOUJIANTAI			= 7,		//斗剑台
	INSTANCE_SUB_TYPE_XIANFU_EXPERIENCE		= 8,		//仙府体验
	INSTANCE_SUB_TYPE_XIULIAN				= 9,		//修炼房
	INSTANCE_SUB_TYPE_PLOT					= 10,		//原地剧情副本
	INSTANCE_SUB_TYPE_MASS_BOSS				= 11,		//全民boss
	INSTANCE_SUB_TYPE_KUAFU_GROUP			= 12,		//跨服组队副本
	INSTANCE_SUB_TYPE_FACTION_BOSSDEFENSE	= 13,		//家族首领挑战
	INSTANCE_SUB_TYPE_FACTION_TOWER			= 14,		//家族无尽远征
	INSTANCE_SUB_TYPE_QUALIFY				= 15,		//排位赛
	INSTANCE_SUB_TYPE_RISK					= 16,		//世界冒险
	INSTANCE_SUB_TYPE_PRIVATE_BOSS			= 17,		//个人BOSS
	INSTANCE_SUB_TYPE_STAGE					= 18,		//闯关副本
	INSTANCE_SUB_TYPE_FACTION_MATCH			= 19,		//家族战副本

	INSTANCE_SUB_TYPE_GROUP_EXP				= 20,		//经验副本
};

// 聊天频道
enum CHAT_CHANNEL
{
	CHAT_CHANNEL_SYSTEM		= 0,	//系统频道
	CHAT_CHANNEL_WORLD		= 1,	//世界频道
	CHAT_CHANNEL_NEARBY		= 2,	//附近频道
	CHAT_CHANNEL_FAMILY		= 3,	//家族频道
	CHAT_CHANNEL_GROUP		= 4,	//队伍频道
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_CHAT_BLOCK_COUNT 30
#define MAX_RANK_LIKE 10
#define MAX_SHOP_LIMIT 20
#define MAX_WORLD_3V3_COUNT 3
#define MAX_BUYED_FACTION_SHOP 8 

#define MAX_PLAYER_OPEN_MENU_COUNT 50

#define MAX_OPTIONAL_GUIDE_COUNT 30

#define MAX_PLAYER_CULTIVATION_RIVAL_COUNT 4
#define MAX_PLAYER_CULTIVATION_PLUNDER_RECORD_COUNT 10

#define MAX_PLAYER_FACTION_SKILL_COUNT 20


//帮派成员礼物的INT信息
enum EFactionDataIntGiftType
{
	FACTION_DATA_INT_GIFT_ID = 0,		//礼物ID
	FACTION_DATA_INT_GIFT_POINT = 1,	//本次礼物总魅力值
	FACTION_DATA_INT_GIFT_FLAG_THANK = 2,		//感谢标识信息
	FACTION_DATA_INT_GIFT_TIME	= 3,	//赠送时间
	FACTION_DATA_INT_GIFT_COUNT_ID = 4, //玩家生成的礼物序号
	MAX_FACTION_DATA_INT_GIFT,
};

//帮派成员礼物的STRING信息
enum EFactionDataStringGiftType
{
	FACTION_DATA_STRING_GIFT_GUID = 0,		//赠送者guid
	FACTION_DATA_STRING_GIFT_MSG = 1,		//赠送者留言
	FACTION_DATA_STRING_GIFT_ITEM_LIST = 2,	//礼物列表详情	物品1 \2 数量1 \1 物品2 \2 数量2
	FACTION_DATA_STRING_GIFT_REPLY_LIST = 3,	//回复信息列表		玩家guid \2 信息 \2 回复类型 \2 时间 \1 玩家guid \2 信息 \2 回复类型 \2 时间
	MAX_FACTION_DATA_STRING_GIFT,
};

//帮派成员礼物回复类型枚举
enum EFactionDataReplyType
{
	FACTION_DATA_REPLY_TYPE_TEXT = 0, //文本回复
	FACTION_DATA_REPLY_TYPE_VOICE = 1, //语音回复
};

#define MAX_FACTION_DATA_GIFT_COUNT 150			//每人送礼上限
#define MAX_FACTION_DATA_GIFT_REPLY_COUNT 200	//回复上限

#define MAX_FACTION_DATA_GIFT_CACHE_COUNT 1000		//离线感谢记录上限
#define MAX_GIFTCODE_TYPE_FLAG_COUNT	10			//

//玩家下标
enum EPlayerFields
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//int 部分
	//////////////////////////////////////////////////////////////////////////
	//公共部分
	PLAYER_FIELD_FD								= 0,												//所在场景服的网络连接号
	PLAYER_FIELD_MERGE_DATA_INDEX				= PLAYER_FIELD_FD + 1,								//玩家合并数据时用来多服务器交互的下标，0.预留，1.回档，2.传送验证数据
	PLAYER_FIELD_ENTRY							= PLAYER_FIELD_MERGE_DATA_INDEX + 1,				//模板
	PLAYER_FIELD_MAP_ID							= PLAYER_FIELD_ENTRY + 1,							//地图
	PLAYER_FIELD_INSTANCE_ID					= PLAYER_FIELD_MAP_ID + 1,							//地图实例
	PLAYER_FIELD_LINE_NO						= PLAYER_FIELD_INSTANCE_ID + 1,						//地图分线号
	PLAYER_FIELD_POS_X							= PLAYER_FIELD_LINE_NO + 1,							//X坐标
	PLAYER_FIELD_POS_Y							= PLAYER_FIELD_POS_X + 1,							//Y坐标
	PLAYER_FIELD_ORIENTATION					= PLAYER_FIELD_POS_Y + 1,							//朝向
	PLAYER_FIELD_MOVESPEED						= PLAYER_FIELD_ORIENTATION + 1,						//不用了

	PLAYER_FIELD_LEVEL							= PLAYER_FIELD_MOVESPEED + 2,						//等级
	PLAYER_FIELD_BYTES_0						= PLAYER_FIELD_LEVEL + 1,							//四个字节,分别存放 0角色id,[1阵营2种族3职业]
	PLAYER_FIELD_NPC_FLAG						= PLAYER_FIELD_BYTES_0 + 1,							//NPC标识
	PLAYER_FIELD_DEATH_STATE					= PLAYER_FIELD_NPC_FLAG + 1,						//生存状态
	
	PLAYER_FIELD_HEALTH							= PLAYER_FIELD_DEATH_STATE + 1,						//当前生命
	PLAYER_FIELD_MAX_HEALTH = PLAYER_FIELD_HEALTH + 2,	//最大生命
	PLAYER_FIELD_DAMAGE = PLAYER_FIELD_MAX_HEALTH + 2,	//攻击力
	PLAYER_FIELD_ARMOR = PLAYER_FIELD_DAMAGE + 2,	//防御力
	PLAYER_FIELD_HIT = PLAYER_FIELD_ARMOR + 2,	//命中
	PLAYER_FIELD_MISS = PLAYER_FIELD_HIT + 2,	//闪避
	PLAYER_FIELD_CRIT = PLAYER_FIELD_MISS + 2,	//暴击
	PLAYER_FIELD_TOUGH = PLAYER_FIELD_CRIT + 2,	//坚韧
	PLAYER_FIELD_ATTACK_SPEED = PLAYER_FIELD_TOUGH + 2,	//攻击速度
	PLAYER_FIELD_MOVE_SPEED = PLAYER_FIELD_ATTACK_SPEED + 2,	//移动速度
	PLAYER_FIELD_IGNORE_ARMOR = PLAYER_FIELD_MOVE_SPEED + 2,	//忽视防御
	PLAYER_FIELD_IGNORE_MISS = PLAYER_FIELD_IGNORE_ARMOR + 2,	//忽视闪避
	PLAYER_FIELD_RECOVERY = PLAYER_FIELD_IGNORE_MISS + 2,	//生命值回复
	PLAYER_FIELD_DAMAGE_AMPLIFY_RATE = PLAYER_FIELD_RECOVERY + 2,	//伤害加深(万分比)
	PLAYER_FIELD_DAMAGE_RESIST_RATE = PLAYER_FIELD_DAMAGE_AMPLIFY_RATE + 2,	//伤害减免(万分比)
	PLAYER_FIELD_DAMAGE_RETURN_RATE = PLAYER_FIELD_DAMAGE_RESIST_RATE + 2,	//反弹伤害(万分比)
	PLAYER_FIELD_VAMPIRIC_RATE = PLAYER_FIELD_DAMAGE_RETURN_RATE + 2,	//吸血光环(万分比)
	PLAYER_FIELD_RECOVERY_RATE = PLAYER_FIELD_VAMPIRIC_RATE + 2,	//回复效率(万分比)
	PLAYER_FIELD_CRIT_RATE = PLAYER_FIELD_RECOVERY_RATE + 2,	//暴击率(万分比)
	PLAYER_FIELD_CRIT_RESIST_RATE = PLAYER_FIELD_CRIT_RATE + 2,	//抗暴率(万分比)
	PLAYER_FIELD_CRIT_DAM_RATE = PLAYER_FIELD_CRIT_RESIST_RATE + 2,	//暴击伤害倍数(万分比)
	PLAYER_FIELD_CRIT_RESIST_DAM_RATE = PLAYER_FIELD_CRIT_DAM_RATE + 2,	//降暴伤害倍数(万分比)
	PLAYER_FIELD_HIT_RATE = PLAYER_FIELD_CRIT_RESIST_DAM_RATE + 2,	//命中率(万分比)
	PLAYER_FIELD_MISS_RATE = PLAYER_FIELD_HIT_RATE + 2,	//闪避率(万分比)
	PLAYER_FIELD_STUN_RATE = PLAYER_FIELD_MISS_RATE + 2,	//眩晕
	PLAYER_FIELD_ROOTS_RATE = PLAYER_FIELD_STUN_RATE + 2,	//定身
	PLAYER_FIELD_SILENCE_RATE = PLAYER_FIELD_ROOTS_RATE + 2,	//沉默
	PLAYER_FIELD_CHAOS_RATE = PLAYER_FIELD_SILENCE_RATE + 2,	//混乱
	PLAYER_FIELD_CHARM_RATE = PLAYER_FIELD_CHAOS_RATE + 2,	//魅惑
	PLAYER_FIELD_CONTROL_ENHANCE_RATE = PLAYER_FIELD_CHARM_RATE + 2,	//控制增强
	PLAYER_FIELD_CONTROL_RESIST_RATE = PLAYER_FIELD_CONTROL_ENHANCE_RATE + 2,	//控制减免
	PLAYER_FIELD_STRENGTH_ARMOR = PLAYER_FIELD_CONTROL_RESIST_RATE + 2,	//强化护甲
	PLAYER_FIELD_DAO			= PLAYER_FIELD_STRENGTH_ARMOR + 2,	//境界
	PLAYER_FIELD_PVP_DAMAGE_AMPLIFY_RATE = PLAYER_FIELD_DAO + 2,	//PVP伤害增加
	PLAYER_FIELD_PVP_DAMAGE_RESIST_RATE = PLAYER_FIELD_PVP_DAMAGE_AMPLIFY_RATE + 2,	//减少PVP伤害
	PLAYER_FIELD_PVE_DAMAGE_AMPLIFY_RATE = PLAYER_FIELD_PVP_DAMAGE_RESIST_RATE + 2,	//增加PVE伤害
	PLAYER_FIELD_DAMAGE_RESIST_VALUE = PLAYER_FIELD_PVE_DAMAGE_AMPLIFY_RATE + 2,	//减少伤害


	PLAYER_FIELD_ATTR_RESERVE0			=	 PLAYER_FIELD_DAMAGE_RESIST_VALUE + 2,				//预留属性0
	PLAYER_FIELD_ATTR_RESERVE1			=	 PLAYER_FIELD_ATTR_RESERVE0 + 2,				//预留属性1
	PLAYER_FIELD_ATTR_RESERVE2			=	 PLAYER_FIELD_ATTR_RESERVE1 + 2,				//预留属性2
	PLAYER_FIELD_ATTR_RESERVE3			=	 PLAYER_FIELD_ATTR_RESERVE2 + 2,				//预留属性3
	PLAYER_FIELD_ATTR_RESERVE4			=	 PLAYER_FIELD_ATTR_RESERVE3 + 2,				//预留属性4
	PLAYER_FIELD_ATTR_RESERVE5			=	 PLAYER_FIELD_ATTR_RESERVE4 + 2,				//预留属性5
	PLAYER_FIELD_ATTR_RESERVE6			=	 PLAYER_FIELD_ATTR_RESERVE5 + 2,				//预留属性6
	PLAYER_FIELD_ATTR_RESERVE7			=	 PLAYER_FIELD_ATTR_RESERVE6 + 2,				//预留属性7

	PLAYER_FIELD_BUFF								= PLAYER_FIELD_ATTR_RESERVE7 + 2,		//BUFF
	PLAYER_FIELD_BUFF_RESERVE						= PLAYER_FIELD_BUFF + MAX_BUFF,						//BUFF保留参数	
	PLAYER_INT_FIELD_BUFF_GIVER_UINT_GUID			= PLAYER_FIELD_BUFF_RESERVE + MAX_BUFF,				//buff giver的uintGuid
	PLAYER_INT_FIELD_BUFF_EFFECT_ID_START			= PLAYER_INT_FIELD_BUFF_GIVER_UINT_GUID + MAX_BUFF,	//buff等级 (byte)
	PLAYER_INT_FIELD_BUFF_EFFECT_ID_END				= PLAYER_INT_FIELD_BUFF_EFFECT_ID_START + MAX_BUFF,	
	PLAYER_FIELD_SKIN								= PLAYER_INT_FIELD_BUFF_EFFECT_ID_END,					//生物变身
	PLAYER_FIELD_BYTES_1							= PLAYER_FIELD_SKIN+1,								//四个字节,分别存放 0怪物分类

	PLAYER_FIELD_FORCE					= PLAYER_FIELD_BYTES_1 + 1,									//战斗力
	PLAYER_FIELD_EQUIPMENT				= PLAYER_FIELD_FORCE + 2,									//装备列表，12个32位预留三个
	PLAYER_FIELD_CUR_MOUNT				= PLAYER_FIELD_EQUIPMENT + EQUIPMENT_TYPE_MAX_POS,			//当前坐骑模板id

	PLAYER_FIELD_PEACE_MODE_CD			= PLAYER_FIELD_CUR_MOUNT + 1,	//和平模式CD
	PLAYER_FIELD_NOTORIETY				= PLAYER_FIELD_PEACE_MODE_CD + 1, //2个short(0:战斗模式, 1:恶名值)
	
	PLAYER_FIELD_BYTES_2				= PLAYER_FIELD_NOTORIETY + 1,			//玩家标识,存4个byte[0灰名时间 1付费等级 2免费复活 3玩家称号]
	PLAYER_FIELD_BYTES_3				= PLAYER_FIELD_BYTES_2 + 1,					//四个字节,分别存放 0头像,[1发型2可用技能槽数量3下次复活是否有保护buff]
	PLAYER_FIELD_BYTES_4				= PLAYER_FIELD_BYTES_3 + 1,					//四个字节,分别存放 (0:频道屏蔽列表,1:预留,2:预留,3:预留)
	PLAYER_FIELD_BYTES_5				= PLAYER_FIELD_BYTES_4 + 1,					//0 GM权限, 1, 2 

	PLAYER_FIELD_AUTO_HP				= PLAYER_FIELD_BYTES_5 + 1,					//大红
	PLAYER_FIELD_AUTO_MP				= PLAYER_FIELD_AUTO_HP + 2,					//大蓝

	PLAYER_FIELD_VIP_LEVEL				= PLAYER_FIELD_AUTO_MP + 2,					//VIP 等级
	PLAYER_FIELD_VIP_TIME_OUT			= PLAYER_FIELD_VIP_LEVEL + 1,				//VIP 超时时间

	// 挂机设置
	PLAYER_FIELD_HOOK					= PLAYER_FIELD_VIP_TIME_OUT + 1,		//挂机状态
	PLAYER_FIELD_HOOK_BYTE0				= PLAYER_FIELD_HOOK + 1,				//0:槽1技能,1:槽2技能,2:槽3技能,3:槽4技能
	PLAYER_FIELD_HOOK_BYTE1				= PLAYER_FIELD_HOOK_BYTE0 + 1,			//0:神兵技能,1:怒气技能2:使用银两买药,3:银两不足用元宝买药
	PLAYER_FIELD_HOOK_SHORT				= PLAYER_FIELD_HOOK_BYTE1 + 1,			//0:自动吃药百分比,1:自动使用道具id
	PLAYER_FIELD_HOOK_BYTE3				= PLAYER_FIELD_HOOK_SHORT + 1,			//0:回程复活/原地复活,1:自动使用绑银购买复活丹,2:绑银不足用元宝,3:自动出售某种平直及以下装备
	PLAYER_FIELD_FLAGS					= PLAYER_FIELD_HOOK_BYTE3 + 1,		//主玩家下标flags
	PLAYER_FIELD_FLAGS_END				= PLAYER_FIELD_FLAGS + 8,				//预留8个32位flags

	PLAYER_FIELD_ONLINE_TIME			= PLAYER_FIELD_FLAGS_END,				//总在线时长(分钟为单位)

	PLAYER_FIELD_ANGER					= PLAYER_FIELD_ONLINE_TIME + 1,			//怒气改变

	PLAYER_FIELD_TRIAL_LAYERS					= PLAYER_FIELD_ANGER + 1,
	PLAYER_INT_FIELD_TRIAL_FINISHED_SECTIONID	= PLAYER_FIELD_TRIAL_LAYERS + 1,			//(已经通关的关卡id)
	PLAYER_INT_FIELD_TRIAL_PROCESS				= PLAYER_INT_FIELD_TRIAL_FINISHED_SECTIONID + 1,	//(0:已经杀的怪,1:总共需要杀的怪)

	PLAYER_FIELD_DECLINE_CHANNEL_BYTE0	= PLAYER_INT_FIELD_TRIAL_PROCESS + 1,			//拒绝频道A(0系统，1帮派，2组队，3世界)
	PLAYER_FIELD_DECLINE_CHANNEL_BYTE1	= PLAYER_FIELD_DECLINE_CHANNEL_BYTE0 + 1,	//拒绝频道B(0:附近)

	PLAYER_SCENED_INT_FIELD_PLAYER_JUMP_CD	= PLAYER_FIELD_DECLINE_CHANNEL_BYTE1 + 1,			//跳跃CD
	PLAYER_INT_FIELD_SYSTEM_MAIL_ID			= PLAYER_SCENED_INT_FIELD_PLAYER_JUMP_CD + 1,			//当前领取的系统邮件的id

	PLAYER_FIELD_DIVINE_NUM				= PLAYER_INT_FIELD_SYSTEM_MAIL_ID + 1,		//神兵数量
	PLAYER_FIELD_DIVINE_FORCE			= PLAYER_FIELD_DIVINE_NUM + 1,				//神兵总战斗力

	PLAYER_FIELD_MOUNT_FORCE			= PLAYER_FIELD_DIVINE_FORCE + 1,			//坐骑总战力
	PLAYER_FIELD_SKILL_FORCE			= PLAYER_FIELD_MOUNT_FORCE + 1,				//技能战力
	PLAYER_FILED_EQUIP_FORCE				= PLAYER_FIELD_SKILL_FORCE + 1,				//装备战力
	PLAYER_FIELD_EQUIPDEVELOP_FORCE			= PLAYER_FILED_EQUIP_FORCE + 1,				//炼器战力

	PLAYER_FIELD_RANK_LIKE				= PLAYER_FIELD_EQUIPDEVELOP_FORCE + 1,
	PLAYER_FIELD_USE_RANK_LIKE			= PLAYER_FIELD_RANK_LIKE + 1,

	PLAYER_FIELD_SHOP_LIMIT_START		=	PLAYER_FIELD_USE_RANK_LIKE + 1,
	PLAYER_FIELD_SHOP_LIMIT_END			=	PLAYER_FIELD_SHOP_LIMIT_START + MAX_SHOP_LIMIT,

	PLAYER_EXPAND_INT_FCM_LOGIN_TIME			= PLAYER_FIELD_SHOP_LIMIT_END,				//防沉迷，单位：分钟	-1是非防沉迷玩家
	PLAYER_EXPAND_INT_FCM_LOGOUT_TIME			= PLAYER_EXPAND_INT_FCM_LOGIN_TIME + 1,		//防沉迷离线时间
	PLAYER_EXPAND_INT_CREATE_TIME				= PLAYER_EXPAND_INT_FCM_LOGOUT_TIME + 1,	//角色创建时间
	PLAYER_EXPAND_INT_LAST_LOGIN_TIME			= PLAYER_EXPAND_INT_CREATE_TIME + 1,		//最后登录时间
	PLAYER_EXPAND_INT_LAST_LOGOUT_TIME			= PLAYER_EXPAND_INT_LAST_LOGIN_TIME + 1,	//最后离线时间
	PLAYER_EXPAND_INT_NUMBER_OF_LOGINS			= PLAYER_EXPAND_INT_LAST_LOGOUT_TIME + 1,	//累积登录次数
	PLAYER_EXPAND_INT_MONEY						= PLAYER_EXPAND_INT_NUMBER_OF_LOGINS + 1,	//各种货币
	PLAYER_EXPAND_INT_MONEY_END					= PLAYER_EXPAND_INT_MONEY + MAX_MONEY_TYPE * 2,
	PLAYER_EXPAND_INT_USE_FASHION				= PLAYER_EXPAND_INT_MONEY_END,	//是否启用时装,目前用到20个pos
	PLAYER_EXPAND_INT_XP						= PLAYER_EXPAND_INT_USE_FASHION + 1,		//当前经验，64位
	PLAYER_EXPAND_INT_NEXT_LEVEL_XP				= PLAYER_EXPAND_INT_XP + 2,					//下一级经验，64位
	PLAYER_EXPAND_INT_XP_ADDED					= PLAYER_EXPAND_INT_NEXT_LEVEL_XP + 2,		// 应用服增加的经验
	PLAYER_EXPAND_INT_XP_PICKED					= PLAYER_EXPAND_INT_XP_ADDED + 2,		// 场景服已经领取的应用服增加的经验
	PLAYER_EXPAND_INT_MAP_STATUS				= PLAYER_EXPAND_INT_XP_PICKED + 2,		// 地图开启进度
	PLAYER_EXPAND_INT_GAG_END_TIME				= PLAYER_EXPAND_INT_MAP_STATUS + 1,			//禁言结束时间
	PLAYER_EXPAND_INT_TO_MAP					= PLAYER_EXPAND_INT_GAG_END_TIME + 1,		//玩家要传送到的地图
	PLAYER_EXPAND_INT_TO_INSTANCE_ID			= PLAYER_EXPAND_INT_TO_MAP + 1,				//玩家要传送到的地图实例ID
	PLAYER_EXPAND_INT_TO_POS_X					= PLAYER_EXPAND_INT_TO_INSTANCE_ID + 1,		//玩家药传送到的坐标
	PLAYER_EXPAND_INT_TO_POS_Y					= PLAYER_EXPAND_INT_TO_POS_X + 1,
	PLAYER_EXPAND_INT_TO_LINE_NO				= PLAYER_EXPAND_INT_TO_POS_Y + 1,			//传送线号
	PLAYER_EXPAND_INT_DB_MAP					= PLAYER_EXPAND_INT_TO_LINE_NO + 1,		//玩家最后一次进入副本前的地图	
	PLAYER_EXPAND_INT_DB_POS_X					= PLAYER_EXPAND_INT_DB_MAP + 1,				//玩家最后一次进入副本前的坐标
	PLAYER_EXPAND_INT_DB_POS_Y					= PLAYER_EXPAND_INT_DB_POS_X + 1,
	PLAYER_EXPAND_INT_CLIENT_DATA				= PLAYER_EXPAND_INT_DB_POS_Y + 1,		//远程存储
	//////////////////////////////////////////////////////////////////////////
	//应用服部分	
	PLAYER_APPD_INT_FIELD_FLAG					= PLAYER_EXPAND_INT_CLIENT_DATA + MAX_CLIENT_UINT32_COUNT,	//玩家标志位
	PLAYER_APPD_INT_FIELD_FLAG_END				= PLAYER_APPD_INT_FIELD_FLAG + 7,		//结束下标

	PLAYER_APPD_INT_FIELD_DAILY_TIME			= PLAYER_APPD_INT_FIELD_FLAG_END,			// 每天在线时长（min）
	PLAYER_APPD_INT_FIELD_RESET_WEEK			= PLAYER_APPD_INT_FIELD_DAILY_TIME + 1,		// 每周重置时间
	PLAYER_APPD_INT_FIELD_RESET_DALIY			= PLAYER_APPD_INT_FIELD_RESET_WEEK + 1,				//重置的时间点每小时一次

	PLAYER_APPD_INT_FIELD_RECHARGE_SUM			= PLAYER_APPD_INT_FIELD_RESET_DALIY + 24,		//累计充值总数
	PLAYER_APPD_INT_FIELD_LAST_RECHARGE_TIME	= PLAYER_APPD_INT_FIELD_RECHARGE_SUM + 1,		//最后一笔充值时间

	PLAYER_APPD_INT_FLELD_JHM_FLAGS				= PLAYER_APPD_INT_FIELD_LAST_RECHARGE_TIME + 1,			//激活码flags
	PLAYER_APPD_INT_FLELD_JHM_FLAGS_END			= PLAYER_APPD_INT_FLELD_JHM_FLAGS + 8,					//激活码flags_end

	//主背包扩展时间戳
	PLAYER_APPD_INT_FIELD_EXTENSION_END_TIME	= PLAYER_APPD_INT_FLELD_JHM_FLAGS_END + 1,				//主包裹扩展结束时间戳
	PLAYER_APPD_INT_FIELD_EXTENSION_REMAIN_TIME	= PLAYER_APPD_INT_FIELD_EXTENSION_END_TIME + 1,			//主包裹扩展剩余多少时间

	PLAYER_INT_FIELD_BLOCK_COUNT = PLAYER_APPD_INT_FIELD_EXTENSION_REMAIN_TIME + 2,	//屏蔽列表个数

	PLAYER_INT_FIELD_WORLD_BOSS_JOIN_ID			= PLAYER_INT_FIELD_BLOCK_COUNT + 1,			//最后一次参加的世界BOSS id
	PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE		= PLAYER_INT_FIELD_WORLD_BOSS_JOIN_ID + 1,	//0:最后一次参加的世界BOSS状态, 1:进入的线数,2:死亡次数,3:预留

	//场景服扩展下标开始了
	PLAYER_SCENED_INT_FLAGS						= PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE + 1,					//玩家场景服标志位

	// 只显示装备的主动技能
	PLAYER_INT_FIELD_SPELL_START		= PLAYER_SCENED_INT_FLAGS + 8,
	PLAYER_INT_FIELD_SPELL_END			= PLAYER_INT_FIELD_SPELL_START + PLAYER_SLOT_SPELL_MAX_COUNT,

	//重要技能的CD
	PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_START	= PLAYER_INT_FIELD_SPELL_END,
	PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_END		= PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_START + MAX_IMPORTANT_SPELL_ATTR_COUNT * PLAYER_IMPORTANT_CD_COUNT,

	PLAYER_EXPAND_KILL_MONSTER					= PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_END,	//杀怪数

	//跨服
	PLAYER_APPD_INT_FIELD_KUAFU_WARID			= PLAYER_EXPAND_KILL_MONSTER + 1,					//跨服场次id
	PLAYER_INT_FIELD_KUAFU_NUMBER				= PLAYER_APPD_INT_FIELD_KUAFU_WARID + 1,				//0:玩家报名跨服时收到匹配信息中给的编号 1:跨服类型（值参照枚举：EKUAFU_TYPE）

	PLAYER_INT_FIELD_MAIN_QUEST_ID				= PLAYER_INT_FIELD_KUAFU_NUMBER + 1,					//当前主线任务
	PLAYER_INT_FIELD_QUEST_CHAPTER				= PLAYER_INT_FIELD_MAIN_QUEST_ID + 1,					//任务章节奖励领取情况

	PLAYER_INT_FIELD_MOUNT_LEVEL				= PLAYER_INT_FIELD_QUEST_CHAPTER + 1,					//4个bytes(0:当前坐骑阶数 1:当前坐骑星级, 2:这里没用，3:当前幻化id)
	
	PLAYER_INT_FIELD_DIVINE_ID					= PLAYER_INT_FIELD_MOUNT_LEVEL + 1,						//当前装备的神兵id

	PLAYER_INT_FIELD_PASSIVE_SPELL_START		= PLAYER_INT_FIELD_DIVINE_ID + 1,				//被动技能开始
	PLAYER_INT_FIELD_PASSIVE_SPELL_END			= PLAYER_INT_FIELD_PASSIVE_SPELL_START + PLAYER_PASSIVE_SPELL_MAX_COUNT,	//被动技能个数

	PLAYER_INT_FIELD_VIRTUAL_CAMP				= PLAYER_INT_FIELD_PASSIVE_SPELL_END,	//虚拟阵营
	PLAYER_INT_FIELD_WORLD_3V3_SCORE			= PLAYER_INT_FIELD_VIRTUAL_CAMP + 1,	//跨服3v3积分
	PLAYER_INT_FIELD_WORLD_3V3_TOTAL_SCORE		= PLAYER_INT_FIELD_WORLD_3V3_SCORE + 1,	//跨服3v3积分
	PLAYER_INT_FIELD_WORLD_3V3_TREND_INFO		= PLAYER_INT_FIELD_WORLD_3V3_TOTAL_SCORE + 1,	//胜负走势

	PLAYER_INT_FIELD_DOUJIANTAI_RANK			= PLAYER_INT_FIELD_WORLD_3V3_TREND_INFO + 1,	//斗剑台排名
	PLAYER_INT_FIELD_DOUJIANTAI_REFRESH_TIME	= PLAYER_INT_FIELD_DOUJIANTAI_RANK + 1,	//最后一次刷新对手时间戳

	PLAYER_INT_FIELD_ARREARS					= PLAYER_INT_FIELD_DOUJIANTAI_REFRESH_TIME + 1,	//欠费
	PLAYER_INT_FIELD_DAILY_QUEST_FINISHED		= PLAYER_INT_FIELD_ARREARS + 2,	// 每日任务完成数
	PLAYER_INT_FIELD_BAG_SORT_TIME				=PLAYER_INT_FIELD_DAILY_QUEST_FINISHED + 1, //整理背包时间戳

	//已开启功能的记录
	PLAYER_INT_FIELD_OPEN_MENU_INDEX	= PLAYER_INT_FIELD_BAG_SORT_TIME+1,
	PLAYER_INT_FIELD_OPEN_MENU_START	= PLAYER_INT_FIELD_OPEN_MENU_INDEX+1,
	PLAYER_INT_FIELD_OPEN_MENU_END		= PLAYER_INT_FIELD_OPEN_MENU_START + MAX_OPEN_MENU_ATTR_COUNT * MAX_PLAYER_OPEN_MENU_COUNT,

	//已购家族商店物品的记录
	PLAYER_INT_FIELD_BUYED_FACTION_SHOP						= PLAYER_INT_FIELD_OPEN_MENU_END + 1,//已购家族商店物品开始
	PLAYER_INT_FIELD_BUYED_FACTION_SHOP_END					= PLAYER_INT_FIELD_BUYED_FACTION_SHOP + MAX_BUYED_FACTION_SHOP,//已购家族商店物品结束

	//记录强制引导ID 
	PLAYER_INT_FIELD_GUIDE_ID_LAST							= PLAYER_INT_FIELD_BUYED_FACTION_SHOP_END + 1,	//上次完成的引导
	PLAYER_INT_FIELD_GUIDE_ID_NOW							= PLAYER_INT_FIELD_GUIDE_ID_LAST + 1, //当前进行中的引导

	//修炼场相关
	PLAYER_INT_FIELD_CULTIVATION_LAST_PLUNDER_TIME			= PLAYER_INT_FIELD_GUIDE_ID_NOW + 1,//上次挑战时间戳
	PLAYER_INT_FIELD_CULTIVATION_LAST_REFRESH_TIME			= PLAYER_INT_FIELD_CULTIVATION_LAST_PLUNDER_TIME + 1,//上次刷新对手时间戳
	PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_EXP			= PLAYER_INT_FIELD_CULTIVATION_LAST_REFRESH_TIME + 1,//当日累计掠夺经验
	PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_CHEST		= PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_EXP + 1,//当日累计掠夺宝箱数
	PLAYER_INT_FIELD_CULTIVATION_TODAY_PURCHASE_COUNT		= PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_CHEST + 1,//当日购买次数
	PLAYER_INT_FIELD_CULTIVATION_LEFT_PLUNDER_COUNT			= PLAYER_INT_FIELD_CULTIVATION_TODAY_PURCHASE_COUNT + 1,//当前剩余挑战次数
	PLAYER_INT_FIELD_CULTIVATION_PLUNDER_RECORD_INDEX		= PLAYER_INT_FIELD_CULTIVATION_LEFT_PLUNDER_COUNT + 1,//修练场修炼记录下标
	PLAYER_INT_FIELD_CULTIVATION_TOTAL_BEEN_PLUNDER_COUNT	= PLAYER_INT_FIELD_CULTIVATION_PLUNDER_RECORD_INDEX + 1,//本轮被掠夺成功次数
	PLAYER_INT_FIELD_CULTIVATION_TODAY_TOTAL_PLUNDER_COUNT	= PLAYER_INT_FIELD_CULTIVATION_TOTAL_BEEN_PLUNDER_COUNT +1,//本日总掠夺次数
	PLAYER_INT_FIELD_CULTIVATION_START_TIME					= PLAYER_INT_FIELD_CULTIVATION_TODAY_TOTAL_PLUNDER_COUNT +1,//修炼开始时间
	PLAYER_INT_FIELD_CULTIVATION_LOST_INFO					= PLAYER_INT_FIELD_CULTIVATION_START_TIME +1,//修炼宝箱丢失信息


	//登陆大礼相关
	PLAYER_INT_FIELD_LOGIN_ACTIVITY_TOTAL_DAYS						= PLAYER_INT_FIELD_CULTIVATION_LOST_INFO + 1,//登陆总天数
	PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_START				= PLAYER_INT_FIELD_LOGIN_ACTIVITY_TOTAL_DAYS + 1,//领取状态开始
	PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_END				= PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_START +2,//领取状态结束

	// 非强制引导ID
	PLAYER_INT_FIELD_OPTIONAL_GUIDE_START					= PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_END + 1,	//非强制引导开始
	PLAYER_INT_FIELD_OPTIONAL_GUIDE_END						= PLAYER_INT_FIELD_OPTIONAL_GUIDE_START + MAX_OPTIONAL_GUIDE_COUNT * 2,	// 非强制引导结束

	PLAYER_INT_FILED_LEAVE_RISK_TIME						= PLAYER_INT_FIELD_OPTIONAL_GUIDE_END,		//离开冒险世界的时间戳
	PLAYER_INT_FILED_LEAVE_RISK_SUIT_SCORE					= PLAYER_INT_FILED_LEAVE_RISK_TIME + 1,		//是否已经领取不在冒险世界的挂机奖励

	PLAYER_INT_FILED_FACTION_BUILDING_SPEEDUP_DAILY_COUNT	= PLAYER_INT_FILED_LEAVE_RISK_SUIT_SCORE + 1,	//家族建筑升级加速每日次数
	PLAYER_INT_FILED_FACTION_DONATE_GIFT_EXCHANGE_DAILY_COUNT = PLAYER_INT_FILED_FACTION_BUILDING_SPEEDUP_DAILY_COUNT + 1,	//家族宝库贡献礼物兑换每日次数

	PLAYER_INT_FILED_CHARM_POINT = PLAYER_INT_FILED_FACTION_DONATE_GIFT_EXCHANGE_DAILY_COUNT + 1, //魅力值
	PLAYER_INT_FILED_FACTION_GIFT_NEXT_COUNT_ID = PLAYER_INT_FILED_CHARM_POINT + 2,	//玩家礼物历史记录下一个count_id
	PLAYER_INT_FILED_FACTION_GIFT_START = PLAYER_INT_FILED_FACTION_GIFT_NEXT_COUNT_ID + 1, //玩家礼物历史记录开始
	PLAYER_INT_FILED_FACTION_GIFT_END = PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_GIFT_COUNT  * MAX_FACTION_DATA_INT_GIFT ,
	PLAYER_INT_FIELD_CREATE_ICON = PLAYER_INT_FILED_FACTION_GIFT_END,	//待创建的帮派icon

	
	PLAYER_INT_FIELD_FACTION_GIFT_POINT_COUNT = PLAYER_INT_FIELD_CREATE_ICON + 1,//帮派魅力赠送总记数
	PLAYER_INT_FIELD_FACTION_GIFT_SEND_COUNT = PLAYER_INT_FIELD_FACTION_GIFT_POINT_COUNT + 2,//帮派礼物赠送总记数
	PLAYER_INT_FIELD_FACTION_GIFT_BEEN_THANK_COUNT = PLAYER_INT_FIELD_FACTION_GIFT_SEND_COUNT + 1,//帮派礼物赠送被女王感谢记数

	PLAYER_INT_FIELD_MASS_BOSS_BUYED_TIMES			= PLAYER_INT_FIELD_FACTION_GIFT_BEEN_THANK_COUNT + 1,	//已经购买次数
	PLAYER_INT_FIELD_MASS_BOSS_TIMES				= PLAYER_INT_FIELD_MASS_BOSS_BUYED_TIMES + 1,			//全民boss次数
	PLAYER_INT_FIELD_MASS_BOSS_CD					= PLAYER_INT_FIELD_MASS_BOSS_TIMES + 1,					//全民boss回复cd(0:表示已满了, 只有次数不满的情况才有cd)

	PLAYER_INT_FIELD_TALISMAN_FORCE					= PLAYER_INT_FIELD_MASS_BOSS_CD + 1,					//法宝总战力
	PLAYER_INT_FIELD_WINGS_FORCE					= PLAYER_INT_FIELD_TALISMAN_FORCE + 1,					//神羽总战力

	PLAYER_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG		= PLAYER_INT_FIELD_WINGS_FORCE + 1,						//组队副本首次通关flag

	PLAYER_INT_FIELD_MERIDIAN_FORCE					= PLAYER_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG + 1,		//经脉修炼战力

	PLAYER_INT_FIELD_WINGS_RANK = PLAYER_INT_FIELD_MERIDIAN_FORCE + 1,		//神羽阶数

	PLAYER_INT_FIELD_FACTION_BOSSDEFENSE_TICKETS	= PLAYER_INT_FIELD_WINGS_RANK + 1,	//家族首领挑战剩余次数

	PLAYER_INT_FIELD_FACTION_TOWER_CLEAR_FLOOR		= PLAYER_INT_FIELD_FACTION_BOSSDEFENSE_TICKETS + 1,	//家族无尽远征 历史挑战层数
	PLAYER_INT_FIELD_FACTION_TOWER_FLAG		= PLAYER_INT_FIELD_FACTION_TOWER_CLEAR_FLOOR + 1,			//0 扫荡状态 1~15 宝箱领取状态

	PLAYER_INT_FIELD_QUALIFY_SCORE			= PLAYER_INT_FIELD_FACTION_TOWER_FLAG + 1,					// 排位赛积分

	PLAYER_INT_FIELD_FACTION_SKILL_LV_START		= PLAYER_INT_FIELD_QUALIFY_SCORE + 1,										//家族技能等级开始 0:已学习等级 uint16 1:当前生效等级
	PLAYER_INT_FIELD_FACTION_SKILL_LV_END		= PLAYER_INT_FIELD_FACTION_SKILL_LV_START + MAX_PLAYER_FACTION_SKILL_COUNT, //家族技能等级结束

	PLAYER_INT_FIELD_APPEARANCE			= PLAYER_INT_FIELD_FACTION_SKILL_LV_END,								// 外观(0:武器,1:衣服)

	PLAYER_INT_FIELD_WEAPON_FORCE		= PLAYER_INT_FIELD_APPEARANCE + 1,										// 武器外观战力
	PLAYER_INT_FIELD_CLOTH_FORCE		= PLAYER_INT_FIELD_WEAPON_FORCE + 1,									// 衣服外观战力
	PLAYER_INT_FIELD_POKEDEX_FORCE		= PLAYER_INT_FIELD_CLOTH_FORCE + 1,										// 图鉴战力

	PLAYER_INT_FIELD_TITLE_FORCE		= PLAYER_INT_FIELD_POKEDEX_FORCE + 1,									// 称号战力
	PLAYER_INT_FIELD_RENAME_TIMES		= PLAYER_INT_FIELD_TITLE_FORCE + 1,										// 改名次数

	PLAYER_INT_FIELD_REVENGE_TIMES		= PLAYER_INT_FIELD_RENAME_TIMES + 1,									//当日剩余复仇次数
	PLAYER_INT_FIELD_REVENGE_BUY_TIMES	= PLAYER_INT_FIELD_REVENGE_TIMES + 1,									//当日复仇购买次数

	PLAYER_INT_FIELD_WINGS_STAR			=  PLAYER_INT_FIELD_REVENGE_BUY_TIMES + 1,								//神羽星数

	PLAYER_INT_FIELD_VIPGIFT_FLAG		= PLAYER_INT_FIELD_WINGS_STAR + 1,										//vip礼包购买状态

	PLAYER_APPD_INT_FIELD_CONSUME_SUM	= PLAYER_INT_FIELD_VIPGIFT_FLAG + 1,									//累计消费元宝

	PLAYER_APPD_INT_FIELD_MONEYTREE_COUNT	= PLAYER_APPD_INT_FIELD_CONSUME_SUM + 1,							//摇钱树摇钱次数
	PLAYER_APPD_INT_FIELD_MONEYTREE_GIFT_FLAG = PLAYER_APPD_INT_FIELD_MONEYTREE_COUNT + 1,						//摇钱树礼包领取状态

	PLAYER_INT_FIELD_WORLD_RISK_LAST_ID		= PLAYER_APPD_INT_FIELD_MONEYTREE_GIFT_FLAG + 1,					//最后一次进入的幻境地图id

	PLAYER_INT_FIELD_LAST_INSTANCE_TYPE		= PLAYER_INT_FIELD_WORLD_RISK_LAST_ID + 1,			//上次副本子类型
	PLAYER_INT_FIELD_LAST_INSTANCE_PARAM	= PLAYER_INT_FIELD_LAST_INSTANCE_TYPE + 1,			//上次副本额外参数

	PLAYER_EXPAND_INT_LAST_IS_RISK				= PLAYER_INT_FIELD_LAST_INSTANCE_PARAM + 1,			//最后一次进的是幻境

	PLAYER_INT_FIELD_RESTORE_POTION_CD	= PLAYER_EXPAND_INT_LAST_IS_RISK + 1,		//回复药功能CD
	PLAYER_INT_FIELD_ESCORT_ROB_COUNT	= PLAYER_INT_FIELD_RESTORE_POTION_CD + 1,	//劫镖次数

	PLAYER_INT_FIELD_ADVENTURE_ROBOT_KILL_COUNT	= PLAYER_INT_FIELD_ESCORT_ROB_COUNT + 1,	//冒险击杀机器人计数

	PLAYER_INT_FIELD_REALMBREAK_LEVEL		=	PLAYER_INT_FIELD_ADVENTURE_ROBOT_KILL_COUNT + 1,	//境界突破等级
	PLAYER_INT_FIELD_REALMBREAK_EXP			=	PLAYER_INT_FIELD_REALMBREAK_LEVEL + 1,				//境界突破当前经验

	PLAYER_INT_FIELD_REALMBREAK_DAILYQUEST_STATE	=	PLAYER_INT_FIELD_REALMBREAK_EXP + 1,	//境界突破每日任务 0,uint16完成次数 1,uint16领取状态

	PLAYER_INT_FIELD_OPERATE_CD		= PLAYER_INT_FIELD_REALMBREAK_DAILYQUEST_STATE + 1,	//所有操作公用CD

	PLAYER_INT_FIELD_PASSED_STAGE_INSTANCE_ID = PLAYER_INT_FIELD_OPERATE_CD + 1,	//已通关闯关副本Id

	PLAYER_INT_FIELD_FACTION_MATCH_CHAMPION_DAILY_REWARD_FLAG = PLAYER_INT_FIELD_PASSED_STAGE_INSTANCE_ID + 1,	//家族战盟主每日奖励

	PLAYER_INT_FIELD_OFFLINE_MINUTES					= PLAYER_INT_FIELD_FACTION_MATCH_CHAMPION_DAILY_REWARD_FLAG + 1,	//剩余的离线时间

	PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_START	= PLAYER_INT_FIELD_OFFLINE_MINUTES + 1,				//被动技能开始
	PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_END	= PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_START + PLAYER_TALISMAN_SLOT_COUNT,	//被动技能个数

	PLAYER_INT_FIELD_WORLD_3V3_WINS				= PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_END,	//胜利次数

	PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_CD_START	= PLAYER_INT_FIELD_WORLD_3V3_WINS + 1,				//被动技能开始
	PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_CD_END		= PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_CD_START + MAX_FABAO_PASSIVE_SPELL_CD_COUNT,	//被动技能个数

	PLAYER_INT_FIELD_AUTO_GROUP_MATCH				= PLAYER_INT_FIELD_FABAO_PASSIVE_SPELL_CD_END,

	PLAYER_INT_FIELD_MOUNT_RIDE						= PLAYER_INT_FIELD_AUTO_GROUP_MATCH + 1,	//是否骑乘

	PLAYER_INT_FIELD_RECHARGE_LOTTERY_TIMES			= PLAYER_INT_FIELD_MOUNT_RIDE + 1,			//元宝抽奖次数
	PLAYER_INT_FIELD_REALMBREAK_FORCE			= PLAYER_INT_FIELD_RECHARGE_LOTTERY_TIMES + 1,			//境界战力
	PLAYER_INT_FIELD_ADVENTURE_SKILL_FORCE		= PLAYER_INT_FIELD_REALMBREAK_FORCE + 1,				//神剑技能战力

	PLAYER_INT_FIELD_ACTIVE						= PLAYER_INT_FIELD_ADVENTURE_SKILL_FORCE + 1,		// 玩家活跃度
	PLAYER_INT_FIELD_LV_UP_TIMESTAMP			= PLAYER_INT_FIELD_ACTIVE + 1,			// 上次升级的时间戳

	PLAYER_INT_FIELD_CHAT_CD_START				=	PLAYER_INT_FIELD_LV_UP_TIMESTAMP + 1,//聊天cd时间戳
	PLAYER_INT_FIELD_CHAT_CD_END				=	PLAYER_INT_FIELD_CHAT_CD_START + MAX_CHAT_TYPE,//

	PLAYER_INT_FIELD_SHOP_CHARGE_FLAG			=	PLAYER_INT_FIELD_CHAT_CD_END + 1,	//商城首充标记
	PLAYER_INT_FIELD_WELFARE_SHOUCHONG			=	PLAYER_INT_FIELD_SHOP_CHARGE_FLAG + 1,	//全局首充奖励标识

	PLAYER_INT_FIELD_WELFARE_CHECKIN_GETBACK_COUNT	=	PLAYER_INT_FIELD_WELFARE_SHOUCHONG + 1,	//每月补签次数
	PLAYER_INT_FIELD_WELFARE_CURRENT_MONTH			=	PLAYER_INT_FIELD_WELFARE_CHECKIN_GETBACK_COUNT + 1,	//签到月份

	PLAYER_INT_FIELD_GIFTCODE_TYPE_FLAG_START		=	PLAYER_INT_FIELD_WELFARE_CURRENT_MONTH + 1,	//已领取礼包类型开始
	PLAYER_INT_FIELD_GIFTCODE_TYPE_FLAG_END			=	PLAYER_INT_FIELD_GIFTCODE_TYPE_FLAG_START + MAX_GIFTCODE_TYPE_FLAG_COUNT, //已领取礼包类型结束

	PLAYER_INT_FIELD_PRIVATE_BOSS_FLAG				=	PLAYER_INT_FIELD_GIFTCODE_TYPE_FLAG_END + 1,	//击杀个人boss标识	


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//字符串部分

	PLAYER_STRING_FIELD_ACCOUNT					= BINLOG_STRING_FIELD_OWNER + 1,					//账号
	PLAYER_STRING_FIELD_TELEPORT_GUID			= PLAYER_STRING_FIELD_ACCOUNT + 1,					//传送GUID
	PLAYER_APPD_STRING_FIELD_CLIENT_DATA		= PLAYER_STRING_FIELD_TELEPORT_GUID + 1,			//远程存储
	PLAYER_STRING_FIELD_LAST_LOGIN_IP			=  PLAYER_APPD_STRING_FIELD_CLIENT_DATA + MAX_CLIENT_STRING_COUNT,					//玩家最后登录的IP
	PLAYER_STRING_FIELD_RECHARGE_ID				= PLAYER_STRING_FIELD_LAST_LOGIN_IP + 1,			//最后充值ID
	PLAYER_STRING_FIELD_CREATE_LOGIN_IP			= PLAYER_STRING_FIELD_RECHARGE_ID + 1,				//玩家创建IP
	PLAYER_APPD_STRING_FIELD_PINGTAI_INFO		= PLAYER_STRING_FIELD_CREATE_LOGIN_IP + 1,			//平台信息
	PLAYER_STRING_FIELD_DB_KUAFU_INFO			= PLAYER_APPD_STRING_FIELD_PINGTAI_INFO + 1,		//玩家跨服信息,是否为跨服玩家依据这个下标是不是空串
	PLAYER_STRING_FIELD_FACTION_GUID			= PLAYER_STRING_FIELD_DB_KUAFU_INFO + 1,			//帮派guid
	PLAYER_STRING_FIELD_FACTION_NAME			= PLAYER_STRING_FIELD_FACTION_GUID + 1,				//帮派名字

	//-----------------------------------
	PLAYER_STRING_FIELD_BLOCK_START				= PLAYER_STRING_FIELD_FACTION_NAME + 1,									//聊天屏蔽列表开始
	PLAYER_STRING_FIELD_BLOCK_END				= PLAYER_STRING_FIELD_BLOCK_START + MAX_CHAT_BLOCK_COUNT,				//聊天屏蔽列表开始

	PLAYER_STRING_FIELD_RANKLIKE_START			= PLAYER_STRING_FIELD_BLOCK_END,						//排行榜点赞列表开始
	PLAYER_STRING_FIELD_RANKLIKE_ENE			= PLAYER_STRING_FIELD_RANKLIKE_START + MAX_RANK_LIKE,	//排行榜点赞列表结束

	//修炼场相关
	PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_START = PLAYER_STRING_FIELD_RANKLIKE_ENE + 1,//修练场对手guid开始
	PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_END = PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_START + MAX_PLAYER_CULTIVATION_RIVAL_COUNT,//修练场对手guid结束

	PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_START = PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_END + 1,//修练场修炼记录开始
	PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_END = PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_START + MAX_PLAYER_CULTIVATION_PLUNDER_RECORD_COUNT,//修练场修炼记录结束

	PLAYER_STRING_FIELD_INVITE_FACTION_GUID	= PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_END, //邀请的帮派guid
	PLAYER_STRING_FIELD_CREATE_FACTION_NAME	= PLAYER_STRING_FIELD_INVITE_FACTION_GUID + 1,	//待创建的帮派名称

	PLAYER_STRING_FILED_FACTION_GIFT_START = PLAYER_STRING_FIELD_CREATE_FACTION_NAME + 1, //玩家礼物历史记录开始
	PLAYER_STRING_FILED_FACTION_GIFT_END = PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_GIFT_COUNT  * MAX_FACTION_DATA_STRING_GIFT ,
	
	PLAYER_STRING_FIELD_GROUP_PEACE_ID = PLAYER_STRING_FILED_FACTION_GIFT_END,	//组队模式下的组队id

	PLAYER_STRING_FIELD_LOCAL_3V3_GENERALID		= PLAYER_STRING_FIELD_GROUP_PEACE_ID + 1,	//3v3的generalid
};


#define PLAYER_BASIC_SPELL_CAPACITY 30			//玩家基础技能的上限
#define PLAYER_DIVINE_SPELL_CAPACITY 15			//玩家神兵个数的上限
#define PLAYER_TALISMAN_SPELL_CAPACITY 15			//玩家法宝个数的上限

// 玩家拥有的基本技能属性信息
enum BASIC_SPELL_ATTR
{
	SHORT_SPELL_ID		= 0,		//技能id short
	SHORT_SPELL_LV		= 1,		//技能等级 short
};

// 技能槽对应技属性
enum SPELL_SLOT_ATTR {
	SLOT_COMBO  = 1,		//连招技能槽
	SLOT_DIVINE = 5,		//神兵技能槽
	SLOT_ANGER	= 6,		//愤怒技能槽
	SPELL_SLOT_COUNT = 6	//技能槽的数量
};

// 技能类型
enum SKILL_TYPE
{
	SKILL_TYPE_DIVINE = 4,	//神兵技能
};


#define MOUNT_UPGRADE_SKILL_COUNT 10
#define MOUNT_ILLUSION_COUNT 30
#define EQUIPMENT_COUNT 10
#define DIVINE_PASSIVE_SKILL_COUNT 3
#define EQUIPDEVELOP_GEM_COUNT 10


// 幻化属性
enum IllusionAttr
{
	ILLUSION_ATTR_ID = 0,										//幻化id
	ILLUSION_ATTR_SPELL_START = ILLUSION_ATTR_ID + 1,			//幻化技能开始
	ILLUSION_ATTR_SPELL_END	= ILLUSION_ATTR_SPELL_START + 2,	//幻化技能结束
	ILLUSION_ATTR_EXPIRE	= ILLUSION_ATTR_SPELL_END,			//过期时间
	MAX_ILLUSION_ATTR_COUNT = ILLUSION_ATTR_EXPIRE + 1
};

enum EXPIRE_TYPE
{
	EXPIRE_TYPE_ILLUSION = 0,	//幻化过期
	EXPIRE_TYPE_DIVINE = 1,		//神兵过期
};


enum Strengthen
{
	STRENGTHEN_LEV_BLESS = 0,					//强化等级 祝福值
	MAX_STRENGTHEN_COUNT = STRENGTHEN_LEV_BLESS + 1
};

enum GEM
{
	GEM_LEV = 0,					//宝石等级
	GEM_CURID_BLESS = GEM_LEV + 3,	//当前宝石  1short 宝石祝福值 0short 
	MAX_GEM_COUNT = GEM_CURID_BLESS + 1
};
enum DIVINE
{
	DIVINE_ID_LEV_BLESS = 0,				//神兵 id_8 等级lev_8 祝福值bless_16
	DIVINE_TIME = DIVINE_ID_LEV_BLESS + 1,  //神兵到期时间
	DIVINE_SKILL = DIVINE_TIME + 1,
	DIVINE_PASSIVE_SKILL = DIVINE_SKILL + 1,
	DIVINE_IMPROVE = DIVINE_PASSIVE_SKILL + DIVINE_PASSIVE_SKILL_COUNT,//神兵培养 铸造 forge 0; 进阶 advance 1; 铸魂 spirit 2
	MAX_DIVINE_COUNT,
};

enum TALISMAN
{
	TALISMAN_ID_LV = 0, //法宝 id_8 等级 lev_8
	TALISMAN_FORCE = 1, //法宝 战力
	MAX_TALISMAN_COUNT,
};

enum TALISMAN_SLOT
{
	TALISMAN_SLOT_ID_STATE = 0, //法宝 id_8 开启状态 state_8
	MAX_TALISMAN_SLOT_COUNT,
};

enum TALISMAN_SLOT_STATE
{
	TALISMAN_SLOT_STATE_NONE = 0, //未开启状态
	TALISMAN_SLOT_STATE_OPEN = 1, //开启状态
	
};

enum EQUIPDEVELOP
{
	EQUIPDEVELOP_STRENGTH_LV = 0,	//0 int16 强化等级
	EQUIPDEVELOP_REFINE_LV = 1,		//0 int16 阶数 1 int16 星数
	EQUIPDEVELOP_GEM_LV_START = 2,		//宝石等级开始 int16 int16
	EQUIPDEVELOP_GEM_LV_END = EQUIPDEVELOP_GEM_LV_START + EQUIPDEVELOP_GEM_COUNT / 2 - 1, //宝石等级结束
	MAX_EQUIPDEVELOP_COUNT,
};

// 升级技能类型
enum RaiseSpellType
{
	RAISE_BASE_SKILL = 1,		//基础技能
	RAISE_MOUNT_SKILL = 2,		//坐骑技能
	RAISE_ILLUSION_SKILL = 3,	//幻化技能
	RAISE_DIVINE_SKILL = 4,		//幻化技能
};

//装备养成操作类型
enum EEquipDevelopType
{
	EQUIPDEVELOP_TYPE_STRENGTH_LVUP		= 1,
	EQUIPDEVELOP_TYPE_REFINE_STAR_LVUP	= 2,
	EQUIPDEVELOP_TYPE_REFINE_RANK_LVUP	= 3,
	EQUIPDEVELOP_TYPE_GEM_ACTIVE		= 4,
	EQUIPDEVELOP_TYPE_GEM_LVUP			= 5,
	EQUIPDEVELOP_TYPE_WASHATTRS_WASH	= 6,
	EQUIPDEVELOP_TYPE_WASHATTRS_SAVE	= 7,
	EQUIPDEVELOP_TYPE_WASHATTRS_DEL		= 8,
	EQUIPDEVELOP_TYPE_STRENGTH_ALL		= 9,

};

#define MAX_EXTERIOR_COUNT 200	// 最大外观数量

//活动数据int
enum PLAYERACTIVITTYDATAINT
{
	PLAYER_ACTIVITTY_DATA_INT_0 = 0,
	PLAYER_ACTIVITTY_DATA_INT_1 = 1,
	PLAYER_ACTIVITTY_DATA_INT_2 = 2,
	PLAYER_ACTIVITTY_DATA_INT_3 = 3,
	MAX_PLAYERACTIVITTYDATAINT_COUNT,
};

//活动数据string
enum PLAYERACTIVITTYDATASTRING
{
	PLAYER_ACTIVITTY_DATA_STRING_0 = 0,
	MAX_PLAYERACTIVITTYDATASTRING_COUNT,
};

#define MAX_PLAYERDACTIVITTYDATA_COUNT 100	//最大活动数据数量

//玩家技能信息
enum PlayerSpellInfo
{
	SPELL_BASE_COUNT					= 0,										//基础技能个数
	SPELL_INT_FIELD_BASE_SPELL_START	= SPELL_BASE_COUNT + 1,						//基础技能开始
	SPELL_INT_FIELD_BASE_SPELL_END		= SPELL_INT_FIELD_BASE_SPELL_START + PLAYER_BASIC_SPELL_CAPACITY,

	SPELL_INT_FIELD_MOUNT_LEVEL			= SPELL_INT_FIELD_BASE_SPELL_END,	//2个short (0阶数, 1星级)
	SPELL_INT_FIELD_MOUNT_TRAIN_EXP		= SPELL_INT_FIELD_MOUNT_LEVEL + 1,	//当前培养经验
	SPELL_INT_FIELD_MOUNT_LEVEL_BASE	= SPELL_INT_FIELD_MOUNT_TRAIN_EXP + 1,	//坐骑等级
	SPELL_INT_FIELD_MOUNT_SPELL_START	= SPELL_INT_FIELD_MOUNT_LEVEL_BASE + 1,	//进阶技能开始
	SPELL_INT_FIELD_MOUNT_SPELL_END		= SPELL_INT_FIELD_MOUNT_SPELL_START + MOUNT_UPGRADE_SKILL_COUNT,							//进阶技能结束
	SPELL_INT_FIELD_MOUNT_BLESS_EXP		= SPELL_INT_FIELD_MOUNT_SPELL_END,															//进阶祝福值
	SPELL_INT_FIELD_MOUNT_ILLUSION_START = SPELL_INT_FIELD_MOUNT_BLESS_EXP + 1,												//幻化开始
	SPELL_INT_FIELD_MOUNT_ILLUSION_END	 = SPELL_INT_FIELD_MOUNT_ILLUSION_START + MAX_ILLUSION_ATTR_COUNT * MOUNT_ILLUSION_COUNT,	//幻化结束

	SPELL_STRENGTHEN_START = SPELL_INT_FIELD_MOUNT_ILLUSION_END + 1,							//强化开始
	SPELL_STRENGTHEN_END = SPELL_STRENGTHEN_START + EQUIPMENT_COUNT * MAX_STRENGTHEN_COUNT,	    //强化结束
	SPELL_STRENGTHEN_ALLMUL = SPELL_STRENGTHEN_END + 1,											//全身强化标记
	
	SPELL_GEM_START = SPELL_STRENGTHEN_ALLMUL + 1,												//宝石开始
	SPELL_GEM_END = SPELL_GEM_START + EQUIPMENT_COUNT * MAX_GEM_COUNT,							//宝石结束
	SPELL_GEM_ALLMUL = SPELL_GEM_END + 1,														//全身宝石标记


	SPELL_DIVINE_COUNT = SPELL_GEM_ALLMUL + 1,													//神兵个数
	SPELL_DIVINE_START = SPELL_DIVINE_COUNT + 1,												//神兵开始
	SPELL_DIVINE_END = SPELL_DIVINE_START + PLAYER_DIVINE_SPELL_CAPACITY  * MAX_DIVINE_COUNT,	//神兵结束

	SPELL_TALISMAN_START = SPELL_DIVINE_END,//法宝开始
	SPELL_TALISMAN_END = SPELL_TALISMAN_START + PLAYER_TALISMAN_SPELL_CAPACITY  * MAX_TALISMAN_COUNT,//法宝结束

	SPELL_WINGS_ID = SPELL_TALISMAN_END,			//翅膀id  阶数*100 + 星数
	SPELL_WINGS_LEVEL = SPELL_WINGS_ID + 1,			//翅膀强化等级
	SPELL_WINGS_BLESS_EXP = SPELL_WINGS_LEVEL + 1,	//翅膀当前祝福经验

	SPELL_INT_FIELD_MERIDIAN_LEVEL			= SPELL_WINGS_BLESS_EXP + 1,			// 2shorts(0:经脉等级, 1:是否需要突破)
	SPELL_INT_FIELD_MERIDIAN_EXP			= SPELL_INT_FIELD_MERIDIAN_LEVEL + 1,	// 经脉经验

	SPELL_INT_FIELD_MERIDIAN_CNT_START		= SPELL_INT_FIELD_MERIDIAN_EXP + 1,				// 每天完成次数开始
	SPELL_INT_FIELD_MERIDIAN_CNT_END		= SPELL_INT_FIELD_MERIDIAN_CNT_START + 50,		// 每天完成次数结束

	SPELL_INT_FIELD_EQUIPDEVELOP_START		= SPELL_INT_FIELD_MERIDIAN_CNT_END,				// 装备培养开始
	SPELL_INT_FIELD_EQUIPDEVELOP_END		= SPELL_INT_FIELD_EQUIPDEVELOP_START + MAX_EQUIPDEVELOP_COUNT * EQUIPMENT_COUNT,//装备培养结束
	SPELL_INT_FIELD_EQUIPDEVELOP_BONUS_LV	= SPELL_INT_FIELD_EQUIPDEVELOP_END,				// 装备培养奖励等级 0 强化 1 精炼 2 镶嵌

	SPELL_INT_FIELD_APPEARANCE_START		= SPELL_INT_FIELD_EQUIPDEVELOP_BONUS_LV + 1,				// 外观开始
	SPELL_INT_FIELD_APPEARANCE_END			= SPELL_INT_FIELD_APPEARANCE_START + MAX_EXTERIOR_COUNT,	// 外观结束

	SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START = SPELL_INT_FIELD_APPEARANCE_END,						//活动玩家数据开始
	SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_END = SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + MAX_PLAYERACTIVITTYDATAINT_COUNT * MAX_PLAYERDACTIVITTYDATA_COUNT, //活动玩家数据结束

	SPELL_TALISMAN_SLOT_START = SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_END,				//法宝槽位开始
	SPELL_TALISMAN_SLOT_END = SPELL_TALISMAN_SLOT_START + PLAYER_TALISMAN_SLOT_COUNT * MAX_TALISMAN_SLOT_COUNT,	//法宝槽位结束
	
	SPELL_STRING_FIELD_EQUIPDEVELOP_WASHATTRS_INFO		= BINLOG_STRING_FIELD_OWNER + 1,			//洗点结果缓存
	SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_START = SPELL_STRING_FIELD_EQUIPDEVELOP_WASHATTRS_INFO + 1 ,	//活动玩家数据开始
	SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_END = SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_START + MAX_PLAYERACTIVITTYDATASTRING_COUNT * MAX_PLAYERDACTIVITTYDATA_COUNT,//活动玩家数据结束

};


#define SOCIAL_FRIEND_MAX_NUM 60 //好友数
#define SOCIAL_APPLY_MAX_NUM 10 // 申请数
#define SOCIAL_ENEMY_MAX_NUM 20 //仇人数
#define SOCIAL_START 4

enum SocialItem
{
	SOCIAL_ICON_VIP_LEV = 0, //图标 vip 等级
	SOCIAL_FAMILIAR_LEV_EXP = SOCIAL_ICON_VIP_LEV + 1,//亲密度等级 亲密度经验
	SOCIAL_FAMILIAR_FORCE = SOCIAL_FAMILIAR_LEV_EXP + 1,//战力
	MAX_FRIENT_COUNT = SOCIAL_FAMILIAR_FORCE +  2,
};
enum PlayerSocialInfo
{
	//SOCIAL_BASE_COUNT = 0,//好友个数
	SOCIAL_REVENGE_NUM = SOCIAL_START, //复仇次数
	SOCIAL_REVENGE_CD = SOCIAL_REVENGE_NUM + 1,//复仇CD
	SOCIAL_FRIEND_START = SOCIAL_REVENGE_CD + 1,	//好友开始
	SOCIAL_FRIEND_END = SOCIAL_FRIEND_START + SOCIAL_FRIEND_MAX_NUM * MAX_FRIENT_COUNT,//好友结束

	SOCIAL_ENEMY_START = SOCIAL_FRIEND_END,//仇人开始
	SOCIAL_ENEMY_END = SOCIAL_ENEMY_START + SOCIAL_ENEMY_MAX_NUM * MAX_FRIENT_COUNT,//仇人结束

	SOCIAL_APPLY_START = SOCIAL_ENEMY_END,//申请开始
	SOCIAL_APPLY_END = SOCIAL_APPLY_START + SOCIAL_APPLY_MAX_NUM * MAX_FRIENT_COUNT,//申请结束

	SOCIAL_APPLY_CLEAR_FLAG = SOCIAL_APPLY_END,//申请清除标记

	SOCIAL_ENEMY_TIME_START = SOCIAL_APPLY_CLEAR_FLAG + 1,//仇人时间戳开始
	SOCIAL_ENEMY_TIME_END = SOCIAL_ENEMY_TIME_START + SOCIAL_ENEMY_MAX_NUM,//仇人时间戳结束

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//帮派下标

//帮派事件
enum EFactionEventType
{
	FACTION_EVENT_TYPE_NULL					= 0,		//预留
	FACTION_EVENT_TYPE_ADD_MEMBER 			= 1,		//添加成员
	FACTION_EVENT_TYPE_SUB_MEMBER			= 2,		//成员离开
	FACTION_EVENT_TYPE_APPOINT				= 3,		//任免
	FACTION_EVENT_TYPE_KICK_MEMBER			= 4,		//踢出成员
	FACTION_EVENT_TYPE_JUANXIAN				= 5,		//捐献
	FACTION_EVENT_TYPE_HONGBAO				= 6,		//发红包
	FACTION_EVENT_TYPE_SHANGXIANG			= 7,		//上香

};

//帮派管理类型
enum EFactionManagerType
{
	FACTION_MANAGER_TYPE_AGREE_JOIN			= 0,		//同意加入帮派
	FACTION_MANAGER_TYPE_REFUSE_JOIN 		= 1,		//拒绝加入帮派
	FACTION_MANAGER_TYPE_KICK 				= 2,		//踢出帮派
	FACTION_MANAGER_TYPE_APPOINT 			= 3,		//职位任免
	FACTION_MANAGER_TYPE_RECRUIT 			= 4,		//招募设置
	FACTION_MANAGER_TYPE_LEVEL_UP 			= 5,		//帮派升级
	FACTION_MANAGER_TYPE_CHANGE_FLAGS		= 6,		//替换帮旗
	FACTION_MANAGER_TYPE_NOTICE				= 7,		//帮会公告
	FACTION_MANAGER_TYPE_AGREE_JOIN_ALL		= 8,		//全部同意加入帮派
	FACTION_MANAGER_TYPE_REFUSE_JOIN_ALL 	= 9,		//全部拒绝加入帮派
	FACTION_MANAGER_TYPE_QUIT			 	= 10,		//退出帮派
};

//帮众操作类型
enum EFactionPeopleType
{
	FACTION_MANAGER_TYPE_JUANXIAN		= 0,		//捐献
	FACTION_MANAGER_TYPE_FULI			= 1,		//领取福利
	FACTION_MANAGER_TYPE_FA_HONGBAO		= 2,		//发红包
	FACTION_MANAGER_TYPE_LQ_HONGBAO		= 3,		//领取红包
	FACTION_MANAGER_TYPE_SHANGXIANG		= 4,		//上香
	FACTION_MANAGER_TYPE_SHOP			= 5,		//购买
	FACTION_MANAGER_TYPE_BUY_TOKEN		= 6,		//购买令牌
	FACTION_MANAGER_TYPE_CHALLENGE_BOSS	= 7,		//挑战家族Boss
	FACTION_MANAGER_TYPE_BUILDING_UPGRADE = 8,		//建筑升级
	FACTION_MANAGER_TYPE_BUILDING_UPGRADE_SPEEDUP = 9,//建筑升级加速
	FACTION_MANAGER_TYPE_DONATE_GIFT_EXCHANGE	= 10,//贡献礼包兑换

	FACTION_MANAGER_TYPE_GIFT_SHOW_PAGE	= 11,		//查看礼物列表
	FACTION_MANAGER_TYPE_GIFT_SHOW_INFO	= 12,		//查看礼物信息
	FACTION_MANAGER_TYPE_GIFT_SHOW_UNTHANK_PAGE	= 13,//女王查看未感谢礼物
	FACTION_MANAGER_TYPE_GIFT_SHOW_HISTORY_PAGE	= 14,//女王查看历史记录
	FACTION_MANAGER_TYPE_GIFT_THANK	= 15,			//女王感谢
	FACTION_MANAGER_TYPE_GIFT_THANK_ALL	= 16,		//女王全部感谢
	FACTION_MANAGER_TYPE_GIFT_THANK_AND_REPLY	= 17,//女王感谢并回复
	FACTION_MANAGER_TYPE_GIFT_REPLY	= 18,			//所有人回复

	FACTION_MANAGER_TYPE_BOSSDEFENSE_CHALLENGE = 19,//进行首领挑战
	FACTION_MANAGER_TYPE_BOSSDEFENSE_DAMAGE_LIST = 20,//查看首领挑战输出前10

	FACTION_MANAGER_TYPE_TOWER_CHALLENGE	= 21, //无尽远征 挑战下一关
	FACTION_MANAGER_TYPE_TOWER_SWEEP		= 22, //无尽远征 扫荡
	FACTION_MANAGER_TYPE_TOWER_CHEST		= 23, //无尽远征 开宝箱

	FACTION_MANAGER_TYPE_SKILL_LVUP			= 24, //升级家族技能

};

//帮众建筑类型
enum EFactionBuildingType
{
	FACTION_BUILDING_TYPE_MAINHALL	= 1,			//主殿
	FACTION_BUILDING_TYPE_STOREHOUSE	= 2,		//宝库房
	FACTION_BUILDING_TYPE_BANK		= 3,			//金库
	FACTION_BUILDING_TYPE_EVENT		= 4,			//活动大厅
	FACTION_BUILDING_TYPE_SKILL		= 5,			//技能坊
	FACTION_BUILDING_TYPE_SHOP		= 6,			//家族商店
};

//帮派成员最多拥有的buff数
#define MAX_FACTION_MENBER_BUFF_NUM 6
//帮派最多拥有的buff数
#define MAX_FACTION_BUFF_NUM 6
//当前屏幕最大buff数
#define MAX_CUR_SCREEN_BUFF_NUM 6
//帮派申请列表最大玩家数
#define MAX_FACTION_APLLY_MAMBER_COUNT 3
//帮派最大成员数
#define MAX_FACTION_MAMBER_COUNT 50
//帮派捐献记录
#define MAX_FACTION_EVENT_COUNT  10
#define MAX_FACTION_SHOP 8
//帮派最大红包数
#define MAX_FACTION_HONGBAO_COUNT 10
//帮派最大BOSS数
#define MAX_FACTION_BOSS_COUNT 10
//帮派最大建筑数量
#define MAX_FACTION_BUILDING_COUNT 10



//帮派成员的INT信息
enum EFactionIntMemberType
{
	FACTION_INT_MEMBER_FORCE				= 0, 											//成员战斗力
	FACTION_INT_MEMBER_UINT16				= FACTION_INT_MEMBER_FORCE + 2,					//0.成员等级,1.今日贡献
	FACTION_INT_MEMBER_DONATE				= FACTION_INT_MEMBER_UINT16 + 1,				//0.金币捐献次数,1.元宝捐献次数
	FACTION_INT_MEMBER_BYTE					= FACTION_INT_MEMBER_DONATE + 1,				//0.是否在线,1.身份, 2,是否VIP，3,今日活跃度
	FACTION_INT_MEMBER_LOGOUT_TIME			= FACTION_INT_MEMBER_BYTE + 1,					//最后离线时间
	FACTION_INT_MEMBER_FLAGS				= FACTION_INT_MEMBER_LOGOUT_TIME + 1,			//成员标志位
	FACTION_INT_MEMBER_TOTAL_CONTRIBUTION	= FACTION_INT_MEMBER_FLAGS + 1,					//历史贡献 - 申请时间
	FACTION_INT_MEMBER_GENDER				= FACTION_INT_MEMBER_TOTAL_CONTRIBUTION + 1,	//个人的职业
	FACTION_INT_MEMBER_TOTAL_SEND_CHARM		= FACTION_INT_MEMBER_GENDER + 2,				//(魅力总贡献) 
	FACTION_INT_MEMBER_TOWER_TODAY_FLOOR	= FACTION_INT_MEMBER_TOTAL_SEND_CHARM + 1,		//无尽远征今日通关层数

	FACTION_INT_MEMBER_ENTER_TIME			= FACTION_INT_MEMBER_TOWER_TODAY_FLOOR + 1,		//进入家族时间
	
	MAX_FACTION_INT_MEMBER				
};

//帮派成员的STRING信息
enum EFactionStringMemberType
{
	FACTION_STRING_MEMBER_GUID				= 0, 		//成员 ID
	FACTION_STRING_MEMBER_NAME				= 1,		//成员名称
	MAX_FACTION_STRING_MEMBER,
};

enum EFactionIntEventType
{
	FACTION_INT_EVENT_TYPE_VALUE			= 0,//类型，数值
	FACTION_INT_EVENT_RESERVE				= 1,//保留字段
	MAX_FACTION_INT_EVENT
};

//帮派成员身份枚举
enum EFactionMemberIdentity
{
	FACTION_MEMBER_IDENTITY_NULL				= 0,	//空，预留
	FACTION_MEMBER_IDENTITY_BANGZHU				= 1,	//帮主
	FACTION_MEMBER_IDENTITY_FU_BANGZHU			= 2,	//副帮主
	FACTION_MEMBER_IDENTITY_TANGZHU				= 3,	//堂主
	FACTION_MEMBER_IDENTITY_JINGYING			= 4,	//精英
	FACTION_MEMBER_IDENTITY_QUNZHONG			= 5,	//群众
};

//帮派标志位
enum EFactionFlags
{
	FACTION_FLAGS_AUTO				= 0,				//帮派是否自动接受申请
	FACTION_FLAGS_IS_BOSS_ADD		= 1,				//帮派是否有人通关了boss副本
};

//帮派buff信息枚举
enum EFactionBuffInfoType
{
	FACTION_BUFF_ID				= 0,	//0：buff类型，1：预留
	FACTION_BUFF_END_TM			= 1,	//buff结束时间
	MAX_FACTION_BUFF,
};


#define MAX_GROUP_MEMBER_COUNT 3

enum GROUP_MEMBER_RESPONSE_STATE
{
	GROUP_MEMBER_RESPONSE_STATE_NONE	= 0,
	GROUP_MEMBER_RESPONSE_STATE_ACCEPT	= 1,
	GROUP_MEMBER_RESPONSE_STATE_DECLINE	= 2,
};

enum GROUP_MEMBER_STATE
{
	GROUP_MEMBER_STATE_NONE		= 0,
	GROUP_MEMBER_STATE_OFFLINE	= 1,
	GROUP_MEMBER_STATE_AWAY		= 2,
};

enum GROUP_AUTO_ACCEPT_STATE
{
	GROUP_AUTO_ACCEPT_STATE_OFF		= 0,
	GROUP_AUTO_ACCEPT_STATE_ON	= 1,
};

enum EGroupMemberInfo
{
	GROUP_MEMBER_INT_ICON				= 0,									// 头像
	GROUP_MEMBER_INT_LEVEL				= GROUP_MEMBER_INT_ICON + 1,			// 等级
	GROUP_MEMBER_INT_MAPID_LINENO		= GROUP_MEMBER_INT_LEVEL + 1,			// 所在地图及分线号
	GROUP_MEMBER_INT_STATE				= GROUP_MEMBER_INT_MAPID_LINENO + 1,	// 玩家状态
	GROUP_MEMBER_INT_RESPONSE_STATE		= GROUP_MEMBER_INT_STATE + 1,			// 响应状态
	MAX_GROUP_MEMBER_INFO_INT_COUNT,

	GROUP_MEMBER_STR_GUID				= 0,									// 玩家guid
	GROUP_MEMBER_STR_NAME				= GROUP_MEMBER_STR_GUID + 1,			// 玩家名称
	MAX_GROUP_MEMBER_INFO_STR_COUNT,
};

enum EGroupFields
{
	GROUP_INT_FIELD_TYPE			  = 0,									// 组队类型
	GROUP_INT_FIELD_LEVEL_RANGE		  = GROUP_INT_FIELD_TYPE + 1,			// 组队等级范围
	GROUP_INT_FIELD_STATE			  =	GROUP_INT_FIELD_LEVEL_RANGE + 1,	// 组队状态
	GROUP_INT_FIELD_TARGET_INST	      = GROUP_INT_FIELD_STATE + 1,			// 当前要进入的目标副本
	
	GROUP_INT_FIELD_MEMBER_INFO_START = GROUP_INT_FIELD_TARGET_INST + 1,
	GROUP_INT_FIELD_MEMBER_INFO_END   = GROUP_INT_FIELD_MEMBER_INFO_START + MAX_GROUP_MEMBER_COUNT * MAX_GROUP_MEMBER_INFO_INT_COUNT,

	GROUP_INT_FIELD_AUTO_ACCEPT_FLAG	= GROUP_INT_FIELD_MEMBER_INFO_END ,		//自动接受申请入队 0:关闭  1: 开启

	GROUP_STR_FIELD_CAPTAIN_GUID	  = BINLOG_STRING_FIELD_OWNER + 1,
	GROUP_STR_FIELD_MEMBER_INFO_START = GROUP_STR_FIELD_CAPTAIN_GUID + 1,
	GROUP_STR_FIELD_MEMBER_INFO_END   = GROUP_STR_FIELD_MEMBER_INFO_START + MAX_GROUP_MEMBER_COUNT * MAX_GROUP_MEMBER_INFO_STR_COUNT,

};

#define MAX_FACTION_STOREHOUSE_COUNT 100
#define MAX_FACTION_STOREHOUSE_RECORD_COUNT 10

//帮派成员的INT信息
enum EFactionIntBossDenfenseType
{
	FACTION_INT_BOSSDEFENSE_POOL_ID		= 0,	//怪物池id
	FACTION_INT_BOSSDEFENSE_HP			= 1,	//剩余hp
	FACTION_INT_BOSSDEFENSE_MAX_HP		= 2,	//最大hp
	FACTION_INT_BOSSDEFENSE_STATUS		= 3,	//怪物状态	0:空闲 1:战斗 2:死亡
	MAX_FACTION_BOSSDEFENSE,
};

#define MAX_FACTION_BOSSDEFENSE_COUNT 6

//帮派下标
enum EFactionFileds
{

	//UINT32 部分
	FACTION_INT_FIELD_PLAYER_NOW_INDEX			= 0,		//帮派成员空位置索引
	FACTION_INT_FIELD_FLAG						= FACTION_INT_FIELD_PLAYER_NOW_INDEX + 1,			//帮派FLAG
	FACTION_INT_FIELD_PLAYER					= FACTION_INT_FIELD_FLAG + 1,								//帮派成员开始下标
	FACTION_INT_FIELD_PLAYER_END				= FACTION_INT_FIELD_PLAYER + MAX_FACTION_INT_MEMBER * MAX_FACTION_MAMBER_COUNT,	//帮派申请索引
	FACTION_INT_FIELD_APPLY_PLAYER_COUNT_INDEX	= FACTION_INT_FIELD_PLAYER_END,
	FACTION_INT_FIELD_APPLY_PLAYER				= FACTION_INT_FIELD_APPLY_PLAYER_COUNT_INDEX + 1,						//玩家申请加入帮派列表
	FACTION_INT_FIELD_APPLY_PLAYER_END			= FACTION_INT_FIELD_APPLY_PLAYER + MAX_FACTION_INT_MEMBER * MAX_FACTION_APLLY_MAMBER_COUNT,	//帮派申请玩家列表
	FACTION_INT_FIELD_EVENT						= FACTION_INT_FIELD_APPLY_PLAYER_END,//帮派记录开始
	FACTION_INT_FIELD_EVENT_END					= FACTION_INT_FIELD_EVENT + MAX_FACTION_EVENT_COUNT * MAX_FACTION_INT_EVENT,//帮派记录结束
	FACTION_INT_FIELD_EVENT_FALG				= FACTION_INT_FIELD_EVENT_END,//帮派记录标志位
	FACTION_INT_FIELD_SHOP						= FACTION_INT_FIELD_EVENT_FALG + 1,//商店开始
	FACTION_INT_FIELD_SHOP_END					= FACTION_INT_FIELD_SHOP + MAX_FACTION_SHOP,//商店结束

	FACTION_INT_FIELD_FORCE						= FACTION_INT_FIELD_SHOP_END,	//帮派战斗力
	FACTION_INT_FIELD_MONEY						= FACTION_INT_FIELD_FORCE + 2,			//帮派资产
	FACTION_INT_FIELD_LEVEL						= FACTION_INT_FIELD_MONEY + 2,			//帮派等级
	FACTION_INT_FIELD_ACTIVITY					= FACTION_INT_FIELD_LEVEL + 1,			//帮派活跃度
	FACTION_INT_FIELD_RANK						= FACTION_INT_FIELD_ACTIVITY + 1,		//帮派排名
	FACTION_INT_FIELD_FLAGS_ID					= FACTION_INT_FIELD_RANK + 1,			//(byte)0:帮派当前选择的旗帜ID (byte)1:神明等级 (uint16)1:灵气
	FACTION_INT_FIELD_MINLEV					= FACTION_INT_FIELD_FLAGS_ID + 1,		//加入帮派最小等级

	FACTION_INT_FIELD_TOKEN_NUM = FACTION_INT_FIELD_MINLEV + 1,								//令牌数量
	FACTION_INT_FIELD_TOKEN_POINTS = FACTION_INT_FIELD_TOKEN_NUM + 1,						//令牌今日积分进度
	FACTION_INT_FIELD_TOKEN_POINTS_COUNT = FACTION_INT_FIELD_TOKEN_POINTS + 1,				//令牌今日积分完成次数
	FACTION_INT_FIELD_TOKEN_TODAY_BUY_COUNT = FACTION_INT_FIELD_TOKEN_POINTS_COUNT + 1,			//今日令牌购买次数
	FACTION_INT_FIELD_CHALLENGE_BOSS_ID_MAX = FACTION_INT_FIELD_TOKEN_TODAY_BUY_COUNT + 1,	//已挑战最大boss id
	FACTION_INT_FIELD_CHALLENGE_BOSS_ID = FACTION_INT_FIELD_CHALLENGE_BOSS_ID_MAX + 1,		//当前挑战boss id
	FACTION_INT_FIELD_CHALLENGE_BOSS_START_TIME = FACTION_INT_FIELD_CHALLENGE_BOSS_ID + 1,	//当前挑战开始时间
	FACTION_INT_FIELD_CHALLENGE_BOSS_HP_RATE = FACTION_INT_FIELD_CHALLENGE_BOSS_START_TIME + 1,				//当前boss血量万分比
	FACTION_INT_FIELD_CHALLENGE_BOSS_POS = FACTION_INT_FIELD_CHALLENGE_BOSS_HP_RATE + 1,					//当前boss位置 x,y
	FACTION_INT_FIELD_PROTECT_TARGET_HP_RATE = FACTION_INT_FIELD_CHALLENGE_BOSS_POS + 1,				//当前守护目标血量万分比
	FACTION_INT_FIELD_PROTECT_TARGET_POS = FACTION_INT_FIELD_PROTECT_TARGET_HP_RATE + 1,				//当前守护目标位置 x,y
	FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START = FACTION_INT_FIELD_PROTECT_TARGET_POS + 1,		//当前boss输出榜开始 int 输出值
	FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END = FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START + MAX_FACTION_MAMBER_COUNT,//当前boss输出榜结束
	FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START = FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END,	//总输出榜开始
	FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END = FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START + MAX_FACTION_MAMBER_COUNT,//总输出榜结束

	FACTION_INT_FIELD_STOREHOUSE_ITEM_COUNT		= FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END,	//宝库道具数量
	FACTION_INT_FIELD_STOREHOUSE_RECORD_CURSOR	= FACTION_INT_FIELD_STOREHOUSE_ITEM_COUNT + 1,		//宝库记录游标

	FACTION_INT_FIELD_BUILDING_ID_START = FACTION_INT_FIELD_STOREHOUSE_RECORD_CURSOR + 1,			//已有建筑id开始
	FACTION_INT_FIELD_BUILDING_ID_END	= FACTION_INT_FIELD_BUILDING_ID_START + MAX_FACTION_BUILDING_COUNT,//已有建筑id结束
	FACTION_INT_FIELD_BUILDING_LVUP_ID	= FACTION_INT_FIELD_BUILDING_ID_END,						//当前正在升级的建筑id
	FACTION_INT_FIELD_BUILDING_LVUP_FINISH_TIME = FACTION_INT_FIELD_BUILDING_LVUP_ID + 1,			//当前升级建筑完成时间戳
	FACTION_INT_FIELD_IS_DISSOLVED				= FACTION_INT_FIELD_BUILDING_LVUP_FINISH_TIME + 1,	//是否解散

	FACTION_INT_FIELD_GIFT_WEEK_POINT_START = FACTION_INT_FIELD_IS_DISSOLVED +1,	//礼物周榜魅力值计数开始
	FACTION_INT_FIELD_GIFT_WEEK_POINT_END = FACTION_INT_FIELD_GIFT_WEEK_POINT_START + MAX_FACTION_MAMBER_COUNT, //礼物周榜魅力值计数结束
	FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_START = FACTION_INT_FIELD_GIFT_WEEK_POINT_END, //未处理礼物计数开始 女王未感谢 成员为领取
	FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_END = FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_START + MAX_FACTION_MAMBER_COUNT,//未处理礼物计数结束
	FACTION_INT_FIELD_CHARM_POINT	= FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_END+1,//帮派女王魅力值 double
	FACTION_INT_FIELD_GIFT_SEND_COUNT_START = FACTION_INT_FIELD_CHARM_POINT + 2, //今日赠送礼物次数开始
	FACTION_INT_FIELD_GIFT_SEND_COUNT_END = FACTION_INT_FIELD_GIFT_SEND_COUNT_START + MAX_FACTION_MAMBER_COUNT,//今日赠送礼物次数结束
	FACTION_INT_FIELD_GIFT_LAST_SEND_TIME = FACTION_INT_FIELD_GIFT_SEND_COUNT_END,//最后赠送的时间

	FACTION_INT_FIELD_GIFT_QUEEN_UNCHECK_COUNT = FACTION_INT_FIELD_GIFT_LAST_SEND_TIME + 2,//女王未处理礼包数

	FACTION_INT_FIELD_BOSSDENFENSE_START = FACTION_INT_FIELD_GIFT_QUEEN_UNCHECK_COUNT + 1,	//家族首领挑战信息开始
	FACTION_INT_FIELD_BOSSDENFENSE_END = FACTION_INT_FIELD_BOSSDENFENSE_START + MAX_FACTION_BOSSDEFENSE_COUNT * MAX_FACTION_BOSSDEFENSE,//家族首领挑战信息结束

	FACTION_INT_FIELD_TOWER_TODAY_TOP_FLOOR	= FACTION_INT_FIELD_BOSSDENFENSE_END,			//无尽远征 每日最高者 层数 int32
	FACTION_INT_FIELD_TOWER_TODAY_TOP_ICON	= FACTION_INT_FIELD_TOWER_TODAY_TOP_FLOOR + 1,	//无尽远征 每日最高者 头像 int32
	FACTION_INT_FIELD_TOWER_TODAY_TOP_FORCE	= FACTION_INT_FIELD_TOWER_TODAY_TOP_ICON + 1,	//无尽远征 每日最高者 战力 double

	FACTION_INT_FIELD_TOTAL_FORCE = FACTION_INT_FIELD_TOWER_TODAY_TOP_FORCE + 2, // double 帮派成员总战力

	FACTION_INT_FIELD_MANGER_COAT	= FACTION_INT_FIELD_TOTAL_FORCE + 2, //帮主衣服
	FACTION_INT_FIELD_MANGER_WEAPON	= FACTION_INT_FIELD_MANGER_COAT + 1, //帮主武器
	FACTION_INT_FIELD_MANGER_VIP	= FACTION_INT_FIELD_MANGER_WEAPON + 1, //帮主vip
	FACTION_INT_FIELD_MANGER_GENDER	= FACTION_INT_FIELD_MANGER_VIP + 1, //帮主gender
	FACTION_INT_FIELD_MANGER_TITLE	= FACTION_INT_FIELD_MANGER_GENDER + 1, //帮主title
	FACTION_INT_FIELD_MANGER_LIKE	= FACTION_INT_FIELD_MANGER_TITLE + 1, //帮主点赞
	FACTION_INT_FIELD_MANGER_WING	= FACTION_INT_FIELD_MANGER_LIKE + 1,  //帮主神羽

	FACTION_STRING_FIELD_MANGER_NAME		= BINLOG_STRING_FIELD_OWNER + 1,//帮主名字
	FACTION_STRING_FIELD_MANGER_GUID		= FACTION_STRING_FIELD_MANGER_NAME + 1,//帮主GUID
	FACTION_STRING_FIELD_PLAYER				= FACTION_STRING_FIELD_MANGER_GUID + 1,						//帮派成员列表		
	FACTION_STRING_FIELD_PLAYER_END			= FACTION_STRING_FIELD_PLAYER + MAX_FACTION_STRING_MEMBER * MAX_FACTION_MAMBER_COUNT,	//帮派成员列表结束
	FACTION_STRING_FIELD_APPLY_PLAYER		= FACTION_STRING_FIELD_PLAYER_END,	//帮派申请玩家列表
	FACTION_STRING_FIELD_APPLY_PLAYER_END	= FACTION_STRING_FIELD_APPLY_PLAYER +  MAX_FACTION_STRING_MEMBER * MAX_FACTION_APLLY_MAMBER_COUNT, //帮派申请玩家列表结束
	FACTION_STRING_FIELD_EVENT				= FACTION_STRING_FIELD_APPLY_PLAYER_END,//帮派记录开始
	FACTION_STRING_FIELD_EVENT_END			= FACTION_STRING_FIELD_EVENT + MAX_FACTION_EVENT_COUNT,//帮派记录结束

	FACTION_STRING_FIELD_GONGGAO			= FACTION_STRING_FIELD_EVENT_END,		//帮派公告
	FACTION_STRING_FIELD_ZHAOMU_GONGGAO		= FACTION_STRING_FIELD_GONGGAO + 1,//招募公告

	FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START = FACTION_STRING_FIELD_ZHAOMU_GONGGAO + 1,		//当前boss输出榜开始 string guid
	FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END = FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START + MAX_FACTION_MAMBER_COUNT,//当前boss输出榜结束
	FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START = FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END,	//总输出榜开始
	FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END = FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START + MAX_FACTION_MAMBER_COUNT,//总输出榜结束

	FACTION_STRING_FIELD_STOREHOUSE_START		= FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END,					//家族宝库开始
	FACTION_STRING_FIELD_STOREHOUSE_END			= FACTION_STRING_FIELD_STOREHOUSE_START + MAX_FACTION_STOREHOUSE_COUNT,	//家族宝库结束

	FACTION_STRING_FIELD_STOREHOUSE_RECORD_START= FACTION_STRING_FIELD_STOREHOUSE_END,												 //宝库记录开始
	FACTION_STRING_FIELD_STOREHOUSE_RECORD_END	= FACTION_STRING_FIELD_STOREHOUSE_RECORD_START + MAX_FACTION_STOREHOUSE_RECORD_COUNT,//宝库记录结束

	FACTION_STRING_FIELD_GIFT_PLAYER_GUID_START = FACTION_STRING_FIELD_STOREHOUSE_RECORD_END,	//礼物对应玩家guid开始
	FACTION_STRING_FIELD_GIFT_PLAYER_GUID_END = FACTION_STRING_FIELD_GIFT_PLAYER_GUID_START + MAX_FACTION_MAMBER_COUNT,//礼物对应玩家guid结束

	FACTION_STRING_FIELD_TOWER_TODAY_TOP_NAME = FACTION_STRING_FIELD_GIFT_PLAYER_GUID_END,		//无尽远征 每日最高者 名称
};


enum EFactionDataFileds
{
	FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_START = 0,	//首领挑战伤害开始
	FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_END = FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_START + MAX_FACTION_BOSSDEFENSE_COUNT * MAX_FACTION_MAMBER_COUNT,			//首领挑战伤害结束
	FACTION_DATA_INT_FIELD_GIFT_START = FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_END,									//礼物记录int开始
	FACTION_DATA_INT_FIELD_GIFT_TMP1 = MAX_FACTION_DATA_GIFT_COUNT * MAX_FACTION_MAMBER_COUNT,						//临时
	FACTION_DATA_INT_FIELD_GIFT_TOTAL_LEN = FACTION_DATA_INT_FIELD_GIFT_TMP1 * MAX_FACTION_DATA_INT_GIFT,			//临时
	FACTION_DATA_INT_FIELD_GIFT_TOTAL_CACHE_LEN = MAX_FACTION_DATA_GIFT_CACHE_COUNT * MAX_FACTION_DATA_INT_GIFT,	//临时
	FACTION_DATA_INT_FIELD_GIFT_TMP2 = FACTION_DATA_INT_FIELD_GIFT_START + FACTION_DATA_INT_FIELD_GIFT_TOTAL_LEN,	//临时
	FACTION_DATA_INT_FIELD_GIFT_END = FACTION_DATA_INT_FIELD_GIFT_TMP2 + FACTION_DATA_INT_FIELD_GIFT_TOTAL_CACHE_LEN, //礼物记录结束
	FACTION_DATA_INT_FIELD_GIFT_RANK_START = FACTION_DATA_INT_FIELD_GIFT_END,	//记录排行礼物id开始
	FACTION_DATA_INT_FIELD_GIFT_RANK_END = FACTION_DATA_INT_FIELD_GIFT_RANK_START + MAX_FACTION_DATA_GIFT_COUNT * MAX_FACTION_MAMBER_COUNT, //记录排行礼物id结束

	FACTION_DATA_STRING_FIELD_GIFT_START = BINLOG_STRING_FIELD_OWNER + 1,	//礼物记录string开始
	FACTION_DATA_STRING_FIELD_GIFT_TEMP1 = MAX_FACTION_DATA_GIFT_COUNT * MAX_FACTION_MAMBER_COUNT,				//临时
	FACTION_DATA_STRING_FIELD_GIFT_TEMP2 = FACTION_DATA_STRING_FIELD_GIFT_TEMP1 * MAX_FACTION_DATA_STRING_GIFT,	//临时
	FACTION_DATA_STRING_FIELD_GIFT_TEMP3 = MAX_FACTION_DATA_GIFT_CACHE_COUNT * MAX_FACTION_DATA_STRING_GIFT,	//临时
	FACTION_DATA_STRING_FIELD_GIFT_TEMP4 = FACTION_DATA_STRING_FIELD_GIFT_TEMP2 + FACTION_DATA_STRING_FIELD_GIFT_TEMP3,//临时
	FACTION_DATA_STRING_FIELD_GIFT_END = FACTION_DATA_STRING_FIELD_GIFT_START + FACTION_DATA_STRING_FIELD_GIFT_TEMP4, //礼物记录结束
};

enum EFactionRankFileds
{
	//int
	//记录2000条记录  魅力 家族图标

	//记录排名信息 1~2000 记录index

	//上周记录

	//string  女王guid  女王名称 家族guid 家族名 骑士名
	//上周记录
};

#define MAX_TRIAL_LAYER_COUNT 256

// 试炼塔状态系数
enum TRIAL_STATE_FACTOR
{
	TRIAL_STATE_FACTOR_ACTIVE = 1,		//激活状态系数
	TRIAL_STATE_FACTOR_PASS   = 10,		//通关状态系数
	TRIAL_STATE_FACTOR_F_PASS = 100,	//首通状态系数
};
#define MAX_ACTIVE_COUNT 50
#define MAX_ACTIVT_REWARD_COUNT 6
#define MAX_DOUJIANTAI_RECORD_COUNT 10

#define MAX_QUALIFY_RECORD_COUNT 30

#define MAX_PRIVATE_BOSS_COUNT 20

#define MAX_STAGE_INSTANCE_BONUS_FLAG_COUNT 10

// 玩家副本信息
enum PLAYER_INSTANCE_INFO
{
	INSTANCE_INT_FIELD_VIP_START	= 0,									//vip副本开始	每个信息4个byte[0:预留,1:可扫荡难度,2:挑战次数,3:购买次数]
	INSTANCE_INT_FIELD_VIP_END		= INSTANCE_INT_FIELD_VIP_START + 3,	//vip副本结束

	INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT	= INSTANCE_INT_FIELD_VIP_END,					//(0:今日可扫荡层数,1:历史通关层数)
	INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT	= INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT + 1,	//(0:扫荡次数,1:可购买扫荡次数)--]]

	INSTANCE_INT_FIELD_RES_START	= INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT + 1,//资源副本开始 每个信息4个byte[0:挑战次数,1:是否通关,2:首次奖励状态,3:预留]
	INSTANCE_INT_FIELD_RES_END		= INSTANCE_INT_FIELD_RES_START + 40,//资源副本结束

	INSTANCE_INT_FIELD_ACTIVE_START = INSTANCE_INT_FIELD_RES_END,//活动开始
	INSTANCE_INT_FIELD_ACTIVE_END	= INSTANCE_INT_FIELD_ACTIVE_START + MAX_ACTIVE_COUNT,//活动结束
	INSTANCE_INT_FIELD_ACTIVE		= INSTANCE_INT_FIELD_ACTIVE_END,//活动-活跃度
	INSTANCE_INT_FIELD_ACTIVE_REWARD = INSTANCE_INT_FIELD_ACTIVE + 1,//奖励领取状态

	INSTANCE_INT_FIELD_3V3_TIMES		= INSTANCE_INT_FIELD_ACTIVE_REWARD + 1,//3v3次数 已参加次数 购买次数
	INSTANCE_INT_FIELD_3V3_DAY_REWARD	= INSTANCE_INT_FIELD_3V3_TIMES + 1,//3v3每日次数奖励 4个byte

	INSTANCE_INT_FIELD_3V3_SEGMENT_TIME = INSTANCE_INT_FIELD_3V3_DAY_REWARD + 1,//3v3段位 发放时间
	
	INSTANCE_INT_FIELD_XIANFU_DAY_TIMES = INSTANCE_INT_FIELD_3V3_SEGMENT_TIME + 1,	//每日挑战次数

	INSTANCE_INT_FIELD_DOUJIANTAI_CURSOR = INSTANCE_INT_FIELD_XIANFU_DAY_TIMES + 1,		//斗剑台信息游标
	INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S = INSTANCE_INT_FIELD_DOUJIANTAI_CURSOR + 1,	//对手名次开始
	INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E = INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S + 3,	//对手名次结束

	INSTANCE_INT_FIELD_DOUJIAN_TIMES			= INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E + 1,	//斗剑次数 已挑战次数 购买次数
	INSTANCE_INT_FIELD_DOUJIAN_FIGHT_CD			= INSTANCE_INT_FIELD_DOUJIAN_TIMES + 1,		//斗剑台挑战CD时间戳
	INSTANCE_INT_FIELD_DOUJIAN_FIRST_GET		= INSTANCE_INT_FIELD_DOUJIAN_FIGHT_CD + 1,	//首胜奖励标记
	INSTANCE_INT_FIELD_DOUJIAN_FIRST_REWARD		= INSTANCE_INT_FIELD_DOUJIAN_FIRST_GET + 1,	//首胜奖励领取标记
	INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN		= INSTANCE_INT_FIELD_DOUJIAN_FIRST_REWARD + 1,	//连胜纪录 纪录 当前
	INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN_REWARD = INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN + 1,//连胜奖励记录
	INSTANCE_INT_FIELD_DOUJIAN_MAX_RANK			= INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN_REWARD+1,//历史最高纪录

	INSTANCE_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG		= INSTANCE_INT_FIELD_DOUJIAN_MAX_RANK + 1,				//每bit记录对应组队副本id首次通关状态 false:未完成 true:已完成
	INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT = INSTANCE_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG + 1,		//组队副本剩余挑战次数
	INSTANCE_INT_FIELD_GROUP_INSTANCE_BUY_COUNT		= INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT + 1,	//当日组队副本挑战次数购买次数
	INSTANCE_INT_FIELD_QUALIFY_EXTRA				= INSTANCE_INT_FIELD_GROUP_INSTANCE_BUY_COUNT + 1,					// 排位赛胜利额外可领取奖励标志
	INSTANCE_INT_FIELD_QUALIFY_WINS					= INSTANCE_INT_FIELD_QUALIFY_EXTRA + 1,					// 排位赛赢得场次		
	INSTANCE_INT_FIELD_QUALIFY_EXTRA_PICKED			= INSTANCE_INT_FIELD_QUALIFY_WINS + 1,					// 排位赛胜利额外已领取奖励标志
	INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES			= INSTANCE_INT_FIELD_QUALIFY_EXTRA_PICKED + 1,			// 排位赛每天次数
	INSTANCE_INT_FIELD_QUALIFY_BUY_TIMES			= INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES + 1,			// 排位赛购买次数
	INSTANCE_INT_FIELD_QUALIFY_CURSOR				= INSTANCE_INT_FIELD_QUALIFY_BUY_TIMES + 1,				// 排位赛记录游标

	INSTANCE_INT_FIELD_PRIVATE_BOSS_RECOVER_TIME_START	= INSTANCE_INT_FIELD_QUALIFY_CURSOR + 1,										//个人BOSS挑战次数回复时间戳开始
	INSTANCE_INT_FIELD_PRIVATE_BOSS_RECOVER_TIME_END	= INSTANCE_INT_FIELD_PRIVATE_BOSS_RECOVER_TIME_START + MAX_PRIVATE_BOSS_COUNT,	//个人BOSS挑战次数回复时间戳结束

	INSTANCE_INT_FIELD_STAGE_INSTANCE_BONUS_FLAG_START	= INSTANCE_INT_FIELD_PRIVATE_BOSS_RECOVER_TIME_END + 1,												//闯关宝箱领取状态开始
	INSTANCE_INT_FIELD_STAGE_INSTANCE_BONUS_FLAG_END	= INSTANCE_INT_FIELD_STAGE_INSTANCE_BONUS_FLAG_START + MAX_STAGE_INSTANCE_BONUS_FLAG_COUNT,			//闯关宝箱领取状态结束

	INSTANCE_INT_FIELD_GROUP_EXP_TIMES					= INSTANCE_INT_FIELD_STAGE_INSTANCE_BONUS_FLAG_END,		//经验副本次数
	INSTANCE_INT_FIELD_GROUP_EXP_BUYED_TIMES			= INSTANCE_INT_FIELD_GROUP_EXP_TIMES + 1,				//经验副本已经购买的次数

	INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_START	= BINLOG_STRING_FIELD_OWNER + 1,//斗剑台战斗信息开始
	INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_END	= INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_START + MAX_DOUJIANTAI_RECORD_COUNT,	//斗剑台战斗信息结束

	INSTANCE_STR_FIELD_QUALIFY_RECORD_START		= INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_END,									//排位赛战斗信息开始
	INSTANCE_STR_FIELD_QUALIFY_RECORD_END		= INSTANCE_STR_FIELD_QUALIFY_RECORD_START + MAX_QUALIFY_RECORD_COUNT,		//排位赛战斗信息结束
};

// 战斗模式
enum BattleMode
{
	PEACE_MODE			= 0,	//和平模式
	FAMILY_MODE			= 1,	//家族模式
	GROUP_MODE			= 2,	//组队模式
	MAX_BATTLE_MODE,
};

//需要发内部消息同步到场景服的技能类型
enum SceneNeedSpellType
{
	TYPE_SPELL_SLOT		= 0,		//更新装备槽中的技能
	TYPE_SPELL_PASSIVE	= 1,		//更新基础被动技能
};

// 玩家主动/被动/辅助技能分类
enum SpellInitiative
{
	SPELL_SUPPORT = 0,				// 辅助

	SPELL_INITIATIVE_DAMAGE  = 1,	// 主动（伤害）
	SPELL_INITIATIVE_PROTECT = 2,	// 主动（防护）
	SPELL_INITIATIVE_CONTROL = 3,	// 主动（控制）
	SPELL_INITIATIVE_CURE 	 = 4,	// 主动（回复）
	SPELL_INITIATIVE_BUFF = 5,		// 主动（增益）

	SPELL_PASSIVE_DAMAGE = 6,		// 被动（伤害）
	SPELL_PASSIVE_PROTECT = 7,		// 被动（防护）
	SPELL_PASSIVE_CONTROL = 8,		// 被动（控制）
	SPELL_PASSIVE_CURE = 9,			// 被动（回复）
	SPELL_PASSIVE_BUFF = 10,		// 被动（增益）
};


//游戏配置专用的状态下标枚举
enum EGameConfigFieldFlagsType
{
	GAME_CONFIG_FIELD_FLAGS_SHOW_PLATFORM_NAME		= 0,		//是否显示平台名
	GAME_CONFIG_FIELD_FLAGS_SHOW_SERVER_ID			= 1,		//是否显示服务器ID
	GAME_CONFIG_FIELD_FLAGS_SHOW_POST				= 2,		//聊天是否post
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//游戏配置
enum EGameConfigField
{
	GAME_CONFIG_INT_FIELD_KAIFUSHIJIAN				= 0,												//开服时间
	GAME_CONFIG_INT_FIELD_FLAGS						= GAME_CONFIG_INT_FIELD_KAIFUSHIJIAN + 1,			//游戏配置标志位
	GAME_CONFIG_INT_FIELD_ADDTIME					= GAME_CONFIG_INT_FIELD_FLAGS + 8,					//合服时间
	GAME_CONFIG_INT_FIELD_WORLD_SVR_TYPE			= GAME_CONFIG_INT_FIELD_ADDTIME + 1,				//服务器类型(见枚举: ESERVER_TYPE)

	GAME_CONFIG_STRING_FIELD_PLATFORM_ID			= BINLOG_STRING_FIELD_OWNER + 1,					//平台ID
	GAME_CONFIG_STRING_FIELD_GM_QQ					= GAME_CONFIG_STRING_FIELD_PLATFORM_ID + 1,			//GM和QQ
	GAME_CONFIG_STRING_FIELD_DB_CONN				= GAME_CONFIG_STRING_FIELD_GM_QQ + 1,				//数据库连接串
	GAME_CONFIG_STRING_FIELD_LOGIN_KEY				= GAME_CONFIG_STRING_FIELD_DB_CONN + 1,				//登录秘钥
	GAME_CONFIG_STRING_FIELD_LOG_DB_CONN			= GAME_CONFIG_STRING_FIELD_LOGIN_KEY + 1,			//日志数据库连接串
	GAME_CONFIG_STRING_LOCAL_HDD_PATH				= GAME_CONFIG_STRING_FIELD_LOG_DB_CONN + 1,			//本地硬盘数据保存地址
	GAME_CONFIG_STRING_EXT_WEB_INTERFACE			= GAME_CONFIG_STRING_LOCAL_HDD_PATH + 1,			//web接口配置
	GAME_CONFIG_STRING_CONF_SVR_URL					= GAME_CONFIG_STRING_EXT_WEB_INTERFACE + 1,			//配置服url地址
	GAME_CONFIG_STRING_WORLD_SERVER_URL				= GAME_CONFIG_STRING_CONF_SVR_URL + 1,				//世界服url地址

	GAME_CONFIG_STRING_FIELD_SERVER					= 200,												//原始服务器
	GAME_CONFIG_STRING_FIELD_SERVER_LIST_BEGIN		= GAME_CONFIG_STRING_FIELD_SERVER + 1,				//服务器列表
};

//客户端模块枚举
enum EClientModule
{
	CLIENT_MODULE_CENTER	= 0,		//中心模块
	CLIENT_MODULE_CREATE	= 1,		//创建角色模块
	CLIENT_MODULE_SCENE		= 2,		//场景模块
	CLIENT_MODULE_UI		= 3,		//UI模块
	CLIENT_MODULE_SH		= 4,		//梭哈模块

	MAX_CLIENT_MODULE,
};

//客户端模块版本信息
enum EClientVersion
{
	CLIENT_VERSION_INT_CREATE_TIME		= 0,		//版本创建时间
	MAX_CLIENT_VERSION_INT,

	CLIENT_VERSION_STRING_VERSIONS		= 0,		//模块版本号
	CLIENT_VERSION_STRING_COMMENT		= 1,		//模块版本说明
	MAX_CLIENT_VERSION_STRING,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//客户端配置信息
enum EClientConfigField
{
	CLIENT_CONFIG_INT_FIELD_MODULE_INFO_BEGIN	= 0,
	CLIENT_CONFIG_INT_FIELD_MODULE_INFO_END		= CLIENT_CONFIG_INT_FIELD_MODULE_INFO_BEGIN + MAX_CLIENT_VERSION_INT * MAX_CLIENT_MODULE,

	CLIENT_CONFIG_STRING_FIELD_MODULE_INFO_BEGIN	= BINLOG_STRING_FIELD_OWNER + 1,
	CLIENT_CONFIG_STRING_FIELD_MODULE_INFO_END		= CLIENT_CONFIG_STRING_FIELD_MODULE_INFO_BEGIN + MAX_CLIENT_VERSION_STRING * MAX_CLIENT_MODULE,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_DEFAULT_LINE_COUNT 4	// 最大默认分线数量
#define MAX_FIELD_BOSS_COUNT  40	// 最大默认野外BOSS数量

// 野外BOSS进度类型
enum FieldBossProcessType
{
	FIELD_BOSS_PROCESS_TYPE_FINISH		= 0,			//已结束
	FIELD_BOSS_PROCESS_START_COUNTDOWN	= 1,			//开始倒计时
	FIELD_BOSS_PROCESS_BORN				= 2,			//BOSS刷新
	FIELD_BOSS_PROCESS_TREASURE			= 3,			//宝箱出现

};

// 野外BOSS int数据
enum FieldBossIntData
{
	FIELD_BOSS_DATA_NEXT_BORN_TIME									= 0,									//下一次刷新时间
	FIELD_BOSS_DATA_CURR_HP											= FIELD_BOSS_DATA_NEXT_BORN_TIME + 1,	//当前血量百分比
	FIELD_BOSS_DATA_PROCESS_TYPE									= FIELD_BOSS_DATA_CURR_HP + 2,			//进度类型
	FIELD_BOSS_DATA_PRIORITY_TIME									= FIELD_BOSS_DATA_PROCESS_TYPE + 1,		//优先拾取时间戳
	FIELD_BOSS_DATA_KILLED											= FIELD_BOSS_DATA_PRIORITY_TIME + 1,	//击杀次数

	MAX_FIELD_BOSS_INT_DATA_COUNT,			
};

// 野外BOSS str数据
enum FieldBossStrData
{
	FIELD_BOSS_DATA_MAX_DAMAGE_GUID								= 0,									//最大伤害guid
	FIELD_BOSS_DATA_NAME										= FIELD_BOSS_DATA_MAX_DAMAGE_GUID + 1,	//当前正在采集的玩家名字

	MAX_FIELD_BOSS_STR_DATA_COUNT,			
};

// 世界BOSS进度
enum WorldBossProcessType
{
	WORLD_BOSS_PROCESS_TYPE_FINISH		= 0,			//已结束
	WORLD_BOSS_PROCESS_ENROLL			= 1,			//报名
	WORLD_BOSS_PROCESS_BORN				= 2,			//BOSS刷新

};

// 人物关于世界BOSS的状态
enum PLAYER_WORLD_BOSS_STATE
{
	PLAYER_WORLD_BOSS_NONE						= 0,			//什么都没有
	PLAYER_WORLD_BOSS_ENROLLED					= 1,			//报过名
	PLAYER_WORLD_BOSS_ENTERED					= 2,			//进入过场景
};


enum MassBossInfo
{
	MASS_BOSS_STATE				= 0,					//全民boss状态
	MASS_BOSS_TIME				= MASS_BOSS_STATE + 1,	//全民boss刷新时间
	MAX_MASS_BOSS_INT_FIELD_COUNT,
};

#define MAX_XIANFU_RECORD_COUNT 10

#define MAX_MASS_BOSS_COUNT 30
#define MAX_LOTTERY_COUNT 10
#define MAX_LOTTERY_RECORD_COUNT 10

#define MAX_ACT_RANK_COUNT 10			//榜单数量
#define MAX_ACT_RANK_INFO_COUNT 10		//最大名次信息数量


//世界变量
enum GlobalValueField
{
	GLOBALVALUE_INT_FIELD_FLAGS										= 0,													//世界变量标志位
	GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION					= GLOBALVALUE_INT_FIELD_FLAGS + 8,						//活动版本号
	GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_END_TIME					= GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION + 1,		//活动结束时间
	GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM						= GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_END_TIME + 1,	//活动物品配置
	GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM_END					= GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM + 30,		//最多10个道具掉落
	GLOBALVALUE_INT_FIELD_ONLINE_PLAYER_NUM							= GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM_END,		//计录全服在线玩家数
	GLOBALVALUE_INT_FIELD_WORLD_CONNECTION_STATUS					= GLOBALVALUE_INT_FIELD_ONLINE_PLAYER_NUM + 1,			//世界服连接状态

	// 野外BOSS数据
	GLOBALVALUE_INT_FIELD_FIELD_BOSS_START							= GLOBALVALUE_INT_FIELD_WORLD_CONNECTION_STATUS + 1,	// 野外boss数据开始
	GLOBALVALUE_INT_FIELD_FIELD_BOSS_END							= GLOBALVALUE_INT_FIELD_FIELD_BOSS_START + MAX_FIELD_BOSS_COUNT * MAX_FIELD_BOSS_INT_DATA_COUNT,																									// 野外boss数据结束

	GLOBALVALUE_INT_FIELD_WORLD_BOSS_LEVEL							= GLOBALVALUE_INT_FIELD_FIELD_BOSS_END,					//世界BOSS等级
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_STATE							= GLOBALVALUE_INT_FIELD_WORLD_BOSS_LEVEL + 1,			//世界BOSS总状态
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_LINE_STATE						= GLOBALVALUE_INT_FIELD_WORLD_BOSS_STATE + 1,			//世界BOSS每个房间的状态
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_LAST_ENROLL_TIME				= GLOBALVALUE_INT_FIELD_WORLD_BOSS_LINE_STATE + 1,		// 最近一次报名时间
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_TIMES							= GLOBALVALUE_INT_FIELD_WORLD_BOSS_LAST_ENROLL_TIME + 1,//世界BOSS次数
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID								= GLOBALVALUE_INT_FIELD_WORLD_BOSS_TIMES + 1,			//0:世界BOSS类型1, 1:世界BOSS类型2,2:当前选定的类型,3:房间个数

	GLOBALVALUE_INT_FIELD_XIANFU_RECORD_CURSOR						= GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID + 1,	//仙府开启宝箱的记录游标

	GLOBALVALUE_INT_FIELD_GIFT_RANK_WINER_FACTION_FLAG				= GLOBALVALUE_INT_FIELD_XIANFU_RECORD_CURSOR + 1, //上周魅力排行第一家族旗子

	GLOBALVALUE_INT_FIELD_GIFT_RANK_NEXT_UPDATE_TIME				= GLOBALVALUE_INT_FIELD_GIFT_RANK_WINER_FACTION_FLAG + 1,//魅力排行下次更新时间
	GLOBALVALUE_INT_FIELD_GIFT_RANK_CUR_ROUND					= GLOBALVALUE_INT_FIELD_GIFT_RANK_NEXT_UPDATE_TIME + 1,///魅力排行当前轮数
	
	GLOBALVALUE_INT_FIELD_MASS_BOSS_START							= GLOBALVALUE_INT_FIELD_GIFT_RANK_CUR_ROUND + 1,	//全民boss开始
	GLOBALVALUE_INT_FIELD_MASS_BOSS_END								= GLOBALVALUE_INT_FIELD_MASS_BOSS_START + MAX_MASS_BOSS_INT_FIELD_COUNT * MAX_MASS_BOSS_COUNT,
	
	GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START	= GLOBALVALUE_INT_FIELD_MASS_BOSS_END,		// 抽奖记录游标
	GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_END		= GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START + MAX_LOTTERY_COUNT,	//

	GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START = GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_END,		 // 活动运行id 开始
	GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_END	= GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START + 30, // 活动运行id 结束


	GLOBALVALUE_INT_FIELD_FACTION_MATCH_GAMES = GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_END, //当前轮数
	GLOBALVALUE_INT_FIELD_FACTION_MATCH_CURRENT_PHASE = GLOBALVALUE_INT_FIELD_FACTION_MATCH_GAMES + 1,//当前阶段
	GLOBALVALUE_INT_FIELD_FACTION_MATCH_NEXT_TIME = GLOBALVALUE_INT_FIELD_FACTION_MATCH_CURRENT_PHASE + 1,//下一阶段时间

	GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_WINSTRIKE_COUNT = GLOBALVALUE_INT_FIELD_FACTION_MATCH_NEXT_TIME + 1,//盟主连胜计数

	GLOBALVALUE_INT_FIELD_FACTION_MATCH_GAMES_NEXT_TIME	= GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_WINSTRIKE_COUNT + 1,	//下次比赛时间

	GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_SATRT_TIME = GLOBALVALUE_INT_FIELD_FACTION_MATCH_GAMES_NEXT_TIME + 1, //战场开始战斗时间
	GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_END_TIME = GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_SATRT_TIME + 1, //战场结束战斗时间


	GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_GENDER = GLOBALVALUE_INT_FIELD_FACTION_MATCH_BATTLE_END_TIME + 1,//家族战盟主帮主角色
	GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_COAT = GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_GENDER + 1,//家族战盟主帮主外观
	GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_WEAPON = GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_COAT + 1,//家族战盟主帮主武器
	GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_WINGSID = GLOBALVALUE_INT_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_WEAPON + 1,//家族战盟主帮主翅膀

	/************************************************************************************************************************************************/
	
	/************************************************************************************************************************************************/

	GLOBALVALUE_STRING_FIELD_LIMIT_ACTIVITY_SCRIPT					= BINLOG_STRING_FIELD_OWNER + 1,					//限时活动类名

	GLOBALVALUE_STRING_FIELD_FIELD_BOSS_START						= GLOBALVALUE_STRING_FIELD_LIMIT_ACTIVITY_SCRIPT + 1,				// 野外boss优先开启宝箱的人物guid开始
	GLOBALVALUE_STRING_FIELD_FIELD_BOSS_END							= GLOBALVALUE_STRING_FIELD_FIELD_BOSS_START + MAX_FIELD_BOSS_COUNT * MAX_FIELD_BOSS_STR_DATA_COUNT, // 野外boss优先开启宝箱的人物guid结束


	GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_START					= GLOBALVALUE_STRING_FIELD_FIELD_BOSS_END,		//仙府开箱子记录开始
	GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_END						= GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_START + MAX_XIANFU_RECORD_COUNT,// 仙府开箱子记录结束

	GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_QUEEN_NAME				= GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_END,//上周魅力排行第一女王名称
	GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_FACTION_NAME			= GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_QUEEN_NAME + 1,//上周魅力排行第一家族名称
	GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_GUARD_NAME				= GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_FACTION_NAME + 1,//上周魅力排行第一骑士名称

	GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_START = GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_GUARD_NAME + 1,		// 抽奖记录数据开始
	GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_END   = GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_START + MAX_LOTTERY_COUNT * MAX_LOTTERY_RECORD_COUNT,	//

	GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_FACTION_GUID = GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_END,				//家族战盟主家族guid
	GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_FACTION_NAME	= GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_FACTION_GUID + 1,	//家族战盟主家族名称
	GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_GUID	= GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_FACTION_NAME + 1,	//家族战盟主帮主guid
	GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_NAME	= GLOBALVALUE_STRING_FIELD_FACTION_MATCH_CHAMPION_BANGZHU_GUID + 1,	//家族战盟主帮主名称
};


#define MAX_DOUJIANTAI_RANK_COUNT 1000
#define MAX_RISK_RANK_COUNT 10			//世界冒险榜单数量
#define MAX_RISK_RANK_SWAPED_COUNT 11	//世界冒险带交换的榜单数量

enum RISK_RANK_INFO
{
	RISK_RANK_INFO_SECTION_ID	= 0,
	RISK_RANK_INFO_TIME	= RISK_RANK_INFO_SECTION_ID + 1,
	MAX_RISK_RANK_INFO_COUNT,
};

#define MAX_FACTION_MATCH_COUNT 20

enum FACTION_MATCH_RESULT_TYPE
{
	FACTION_MATCH_RESULT_TYPE_NONE	= 0,
	FACTION_MATCH_RESULT_TYPE_LOSE	= 1,
	FACTION_MATCH_RESULT_TYPE_WIN	= 2,
};

enum FACTION_MATCH_SCRIPT_TYPE
{
	FACTION_MATCH_SCRIPT_TYPE_NONE		= 0,
	FACTION_MATCH_SCRIPT_TYPE_INIT		= 1,
	FACTION_MATCH_SCRIPT_TYPE_UPDATE		= 2,
	FACTION_MATCH_SCRIPT_TYPE_DECIDE_FIRST	= 3,
	FACTION_MATCH_SCRIPT_TYPE_OPEN_FIRST	= 4,
	FACTION_MATCH_SCRIPT_TYPE_START_FIRST	= 5,
	FACTION_MATCH_SCRIPT_TYPE_END_FIRST	= 6,
	FACTION_MATCH_SCRIPT_TYPE_OPEN_SECOND	= 7,
	FACTION_MATCH_SCRIPT_TYPE_START_SECOND	= 8,
	FACTION_MATCH_SCRIPT_TYPE_END_SECOND	= 9,
};

enum FACTION_MATCH_INFO_INT
{
	FACTION_MATCH_INFO_INT_FIRST_DETAIL_ID = 0,
	FACTION_MATCH_INFO_INT_SECOND_DETAIL_ID = 1,
	FACTION_MATCH_INFO_INT_RESULT_RANK	= 2,
	MAX_FACTION_MATCH_INFO_INT_COUNT,
};

enum FACTION_MATCH_INFO_STRING
{
	FACTION_MATCH_INFO_STRING_GUID = 0,
	FACTION_MATCH_INFO_STRING_NAME = 1,
	MAX_FACTION_MATCH_INFO_STRING_COUNT,
};

#define MAX_FACTION_MATCH_DETAIL_COUNT 20

enum FACTION_MATCH_DETAIL_INFO
{
	FACTION_MATCH_DETAIL_INFO_MATCH_INDEX_1 = 0,
	FACTION_MATCH_DETAIL_INFO_MATCH_RESULT_1 = 1,
	FACTION_MATCH_DETAIL_INFO_MEMBER_COUNT_1	= 2,
	FACTION_MATCH_DETAIL_INFO_SCORE_1	= 3,
	FACTION_MATCH_DETAIL_INFO_FLAG_1	= 4,
	FACTION_MATCH_DETAIL_INFO_MATCH_INDEX_2 = 5,
	FACTION_MATCH_DETAIL_INFO_MATCH_RESULT_2 = 6,
	FACTION_MATCH_DETAIL_INFO_MEMBER_COUNT_2	= 7,
	FACTION_MATCH_DETAIL_INFO_SCORE_2	= 8,
	FACTION_MATCH_DETAIL_INFO_FLAG_2	= 9,
	MAX_FACTION_MATCH_DETAIL_INFO_COUNT,
};

enum EGlobalCounter
{
	GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_START = 0,	//挑战中的标记位
	GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_END	  = GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_START + 40,

	GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_START = GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_END,		// 活动结束id flag开始
	GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_END	= GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_START + 200,	// 活动结束id flag结束

	GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_START	= GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_END,//活动排行数据开始
	GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_END	= GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_START + MAX_ACT_RANK_COUNT * MAX_ACT_RANK_INFO_COUNT,//活动排行数据结束

	GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_START = GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_END,
	GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_END = GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_START + MAX_RISK_RANK_SWAPED_COUNT * MAX_RISK_RANK_INFO_COUNT,

	GLOBALCOUNTER_INT_FIELD_FACTION_MATCH_INFO_START = GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_END,	//家族战排行信息
	GLOBALCOUNTER_INT_FIELD_FACTION_MATCH_INFO_END = GLOBALCOUNTER_INT_FIELD_FACTION_MATCH_INFO_START + MAX_FACTION_MATCH_COUNT * MAX_FACTION_MATCH_INFO_INT_COUNT,

	GLOBALCOUNTER_INT_FIELD_FACTION_MATCH_DETAIL_INFO_START = GLOBALCOUNTER_INT_FIELD_FACTION_MATCH_INFO_END,	//家族战比赛信息
	GLOBALCOUNTER_INT_FIELD_FACTION_MATCH_DETAIL_INFO_END = GLOBALCOUNTER_INT_FIELD_FACTION_MATCH_DETAIL_INFO_START + MAX_FACTION_MATCH_DETAIL_COUNT * MAX_FACTION_MATCH_DETAIL_INFO_COUNT,

	GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_START	= BINLOG_STRING_FIELD_OWNER + 1,//斗剑台排名开始
	GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_END	= GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_START + MAX_DOUJIANTAI_RANK_COUNT,//斗剑台排名结束
	GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_START = GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_END,//战斗信息记录开始
	GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_END   = GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_START + MAX_DOUJIANTAI_RANK_COUNT * MAX_DOUJIANTAI_RECORD_COUNT, //战斗信息记录结束

	GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_START = GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_END,						//活动排行数据开始
	GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_END = GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_START + MAX_ACT_RANK_COUNT * MAX_ACT_RANK_INFO_COUNT,//活动排行数据结束

	GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_START = GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_END,
	GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_END	= GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_START + MAX_RISK_RANK_SWAPED_COUNT,

	GLOBALCOUNTER_STRING_FIELD_FACTION_MATCH_INFO_START = GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_END,		//家族战排行字符串信息
	GLOBALCOUNTER_STRING_FIELD_FACTION_MATCH_INFO_END = GLOBALCOUNTER_STRING_FIELD_FACTION_MATCH_INFO_START + MAX_FACTION_MATCH_COUNT * MAX_FACTION_MATCH_INFO_STRING_COUNT,

};

//计时器世界变量计数器
enum EGlobalCounterField
{
	GLOBALCOUNTER_INT_FIELD_ONLINE_AWARD_COUNT						= 0,			//全服银子数量
	GLOBALCOUNTER_INT_FIELD_DAILY_ADD_BIND_GOLD						= GLOBALCOUNTER_INT_FIELD_ONLINE_AWARD_COUNT + 2,	//每日新增绑定元宝数量
	GLOBALCOUNTER_INT_FIELD_DAILY_SUB_BIND_GOLD						= GLOBALCOUNTER_INT_FIELD_DAILY_ADD_BIND_GOLD + 2,	//每日消耗绑定元宝数量
	GLOBALCOUNTER_INT_FIELD_DAILY_ADD_GOLD_INGOT					= GLOBALCOUNTER_INT_FIELD_DAILY_SUB_BIND_GOLD + 2,		//每日新增元宝数量
	GLOBALCOUNTER_INT_FIELD_DAILY_SUB_GOLD_INGOT					= GLOBALCOUNTER_INT_FIELD_DAILY_ADD_GOLD_INGOT + 2,	//每日消耗元宝数量
	GLOBALCOUNTER_INT_FIELD_DAILY_ADD_SILVER						= GLOBALCOUNTER_INT_FIELD_DAILY_SUB_GOLD_INGOT + 2,	//每日新增银子数量
	GLOBALCOUNTER_INT_FIELD_DAILY_SUB_SILVER						= GLOBALCOUNTER_INT_FIELD_DAILY_ADD_SILVER + 2,	//每日消耗银子数量
	
	MAX_GLOBALCOUNTER_INT_FIELD,
};

// 不同步客户端的计数器
enum GlobalAsyncValueField
{

};

// 地图类型
enum MAP_TYPE
{
	MAP_TYPE_MAIN = 0,		//主城
	MAP_TYPE_FIELD = 1,		//野外
	MAP_TYPE_INSTANCE = 2,	//副本
	MAP_TYPE_ACTIVITY = 3,	//活动
	MAP_TYPE_PVP = 4,		//PVP
};

// 副本人物类型
enum InstanceQuestType
{
	INSTANCE_QUEST_TYPE_KILL_MONSTER = 1,	//击杀怪物(creatureId, num)
	INSTANCE_QUEST_TYPE_PICK_ITEM = 2,		//收集物品
	INSTANCE_QUEST_TYPE_ACTIVE_MACHINE = 3,	//激活机关
	INSTANCE_QUEST_TYPE_PROTECT_NPC = 4,	//守护NPC
	INSTANCE_QUEST_TYPE_ESCORT_NPC = 5,		//护送NPC
	INSTANCE_QUEST_TYPE_DEFENSE = 6,		//防守
	INSTANCE_QUEST_TYPE_BREAK_THROUGH  = 7,	//闯关
};

#define MAX_INSTANCE_QUEST_COUNT 12
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//地图
enum EMapFileds
{
	MAP_INT_FIELD_MAP_ID								= 0,															//地图模板ID
	MAP_INT_FIELD_INSTANCE_ID							= MAP_INT_FIELD_MAP_ID + 1,										//实例ID
	MAP_INT_FIELD_LINE_NO								= MAP_INT_FIELD_INSTANCE_ID + 1,								//分线ID
	MAP_INT_FIELD_WARID									= MAP_INT_FIELD_INSTANCE_ID + 1,								//场次id
	MAP_INT_FIELD_KUAFU_TYPE							= MAP_INT_FIELD_WARID + 1,										//跨服类型
	MAP_INT_FIELD_STATE									= MAP_INT_FIELD_KUAFU_TYPE + 1,									//0.地图大状态,1.地图小状态,2.地图自动复活时间,3预留状态
	MAP_INT_FIELD_KILL_NUM								= MAP_INT_FIELD_STATE + 1,										//杀怪数
	MAP_INT_FIELD_RESERVE1								= MAP_INT_FIELD_KILL_NUM + 1,									//保留字段1
	MAP_INT_FIELD_RESERVE2								= MAP_INT_FIELD_RESERVE1 + 1,									//保留字段2
	MAP_INT_FIELD_RESERVE3								= MAP_INT_FIELD_RESERVE2 + 1,									//保留字段3 当前层数
	MAP_INT_FIELD_RESERVE4								= MAP_INT_FIELD_RESERVE3 + 1,									//保留字段4 判断副本是否初始化
	MAP_INT_FIELD_INSTANCE_WAVE							= MAP_INT_FIELD_RESERVE4 + 1,									//波数2shorts(0:当前波数,1:总波数)

	MAP_INT_FIELD_QUESTS_START							= MAP_INT_FIELD_INSTANCE_WAVE + 1,									//副本任务开始
	MAP_INT_FIELD_QUESTS_END							= MAP_INT_FIELD_QUESTS_START + MAX_INSTANCE_QUEST_COUNT * 2,							//副本任务结束

	MAP_INT_FIELD_QUESTS_PROCESS_START					= MAP_INT_FIELD_QUESTS_END,												//进度开始
	MAP_INT_FIELD_QUESTS_PROCESS_END					= MAP_INT_FIELD_QUESTS_PROCESS_START + MAX_INSTANCE_QUEST_COUNT / 4,	//进度结束

	MAP_INT_FIELD_CREATE_TM								= MAP_INT_FIELD_QUESTS_PROCESS_END,										//副本创建时间
	MAP_INT_FIELD_START_TM								= MAP_INT_FIELD_CREATE_TM + 1,											//副本开始时间
	MAP_INT_FIELD_QUEST_END_TM							= MAP_INT_FIELD_START_TM + 1,											//副本任务结束时间
	MAP_INT_FIELD_END_TM								= MAP_INT_FIELD_QUEST_END_TM + 1,										//副本结束时间
	MAP_INT_FIELD_WALL									= MAP_INT_FIELD_END_TM + 1,												//是否生成阻挡物
	MAP_INT_FIELD_INSTANCE_TYPE							= MAP_INT_FIELD_WALL + 1,												//副本类型
	
	//地图字符串部分
	MAP_STR_GENERAL_ID									= BINLOG_STRING_FIELD_OWNER + 1,
	MAP_STR_REWARD										= MAP_STR_GENERAL_ID + 1,		//副本奖励物品字符串
};

//小怪陆续刷
enum REFRESH_MONSTER_FIELDS
{
	REFRESH_MONSTER_FIELD_ID			=	MAP_INT_FIELD_INSTANCE_TYPE + 4,	//2个short(0:当前已经刷的,1:总共需要刷多少怪)
	REFRESH_MONSTER_FIELD_INFO_START	=	REFRESH_MONSTER_FIELD_ID + 1,		//怪物信息开始2个short(0:entry,1:level)
};

enum KUAFU_3v3_PLAYER_INFO
{
	KUAFU_3V3_PLAYER_DAMAGE		= 0,								// 伤害
	KUAFU_3V3_PLAYER_SHOW_INFO	= KUAFU_3V3_PLAYER_DAMAGE + 2,		// 2个byte, 1short(byte0:gender, byte1:hprate, short1:level)
	KUAFU_3V3_PLAYER_SETTLEMENT	= KUAFU_3V3_PLAYER_SHOW_INFO + 1,	// 计算信息, 4bytes(0:击杀数量,1:死亡状态,2:所属阵营,3:积分)
	KUAFU_3V3_PLAYER_HONOR		= KUAFU_3V3_PLAYER_SETTLEMENT + 1,	// 荣誉及全场最佳, 4bytes(0:获得荣誉, 1:全场最佳,2:保留,3:保留)
	KUAFU_3V3_PLAYER_TOTAL		= KUAFU_3V3_PLAYER_HONOR + 1,		// 当前积分
	MAX_KUAFU_3V3_INT_COUNT,										// kuafu属性数量

	KUAFU_3V3_PLAYER_NAME		= 0,								//玩家名称
	KUAFU_3V3_PLAYER_GUID		= KUAFU_3V3_PLAYER_NAME + 1,		//玩家guid
	MAX_KUAFU_3V3_STR_COUNT,
};

#define MAX_KUAFU_3V3_COUNT 6
// 跨服3v3匹配
enum KUAFU_3V3_FIELDS 
{
	KUAFU_3V3_FIELDS_INT_INFO_START	= MAP_INT_FIELD_INSTANCE_TYPE + 1,														// 跨服数据开始
	KUAFU_3V3_FIELDS_INT_INFO_END	= KUAFU_3V3_FIELDS_INT_INFO_START + MAX_KUAFU_3V3_COUNT * MAX_KUAFU_3V3_INT_COUNT,		// 3v3总共6个人
	
	KUAFU_3V3_FIELDS_STR_INFO_START	= MAP_STR_REWARD + 1,																// 字符串数据开始
	KUAFU_3V3_FIELDS_STR_INFO_END	= KUAFU_3V3_FIELDS_STR_INFO_START + MAX_KUAFU_3V3_COUNT * MAX_KUAFU_3V3_STR_COUNT,	// 字符串数据结束
};


// 仙府夺宝 玩家信息
enum KUAFU_XIANFU_PLAYER_INFO
{
	KUAFU_XIANFU_PLAYER_SETTLEMENT		= 0,									// 玩家战力
	KUAFU_XIANFU_PLAYER_MONEY			= KUAFU_XIANFU_PLAYER_SETTLEMENT + 2,	// 元宝数据
	KUAFU_XIANFU_PLAYER_MONEY_CHANGED	= KUAFU_XIANFU_PLAYER_MONEY + 2,		// 元宝改变值
	KUAFU_XIANFU_PLAYER_SHOW_INFO		= KUAFU_XIANFU_PLAYER_MONEY_CHANGED + 2,// 4个byte(byte0:宝箱数量, byte1:击杀人数, byte2:击杀BOSS数量,byte3:连杀次数)
	MAX_KUAFU_XIANFU_INT_COUNT,													// kuafu属性数量

	KUAFU_XIANFU_PLAYER_NAME			= 0,									//玩家名称
	KUAFU_XIANFU_PLAYER_GUID			= KUAFU_XIANFU_PLAYER_NAME + 1,			//玩家guid
	MAX_KUAFU_XIANFU_STR_COUNT,
};

enum KUAFU_XIANFU_BOSS_INFO
{
	KUAFU_XIANFU_BOSS_SHOW_INFO		= 0,									// 2 shorts(0:entry, 1:死亡状态)
	KUAFU_XIANFU_BOSS_BORN_INFO		= KUAFU_XIANFU_BOSS_SHOW_INFO + 1,		// 是否刷新
	KUAFU_XIANFU_BOSS_BORN_TIME		= KUAFU_XIANFU_BOSS_BORN_INFO + 1,		// 刷新时间戳
	MAX_KUAFU_XIANFU_BOSS_INT_COUNT,										//
};

#define MAX_KUAFU_XIANFU_COUNT 10

#define MAX_KUAFU_XIANFU_BOSS_COUNT 5
// 跨服仙府夺宝匹配
enum KUAFU_XIANFU_FIELDS 
{
	KUAFU_XIANFU_FIELDS_INT_INFO_START		= MAP_INT_FIELD_INSTANCE_TYPE + 1,														// 跨服数据开始
	KUAFU_XIANFU_FIELDS_INT_INFO_END		= KUAFU_XIANFU_FIELDS_INT_INFO_START + MAX_KUAFU_XIANFU_COUNT * MAX_KUAFU_XIANFU_INT_COUNT,		// 3v3总共6个人
	
	KUAFU_XIANFU_FIELDS_INT_BOSS_INDX		= KUAFU_XIANFU_FIELDS_INT_INFO_END,		//当前的bossid
	KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_START	= KUAFU_XIANFU_FIELDS_INT_BOSS_INDX + 1,	//BOSS信息开始
	KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_END	= KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_START + MAX_KUAFU_XIANFU_BOSS_INT_COUNT * MAX_KUAFU_XIANFU_BOSS_COUNT,

	KUAFU_XIANFU_FIELDS_HARD				= KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_END,	//副本难度
	XIANFU_TEST_DUMMY_COUNT					= KUAFU_XIANFU_FIELDS_HARD + 1,				//假人数量
	

	KUAFU_XIANFU_FIELDS_STR_INFO_START	= MAP_STR_REWARD + 1,																// 字符串数据开始
	KUAFU_XIANFU_FIELDS_STR_INFO_END	= KUAFU_XIANFU_FIELDS_STR_INFO_START + MAX_KUAFU_XIANFU_COUNT * MAX_KUAFU_XIANFU_STR_COUNT,	// 字符串数据结束
};


// 跨服组队玩家信息
enum KUAFU_GROUP_INSTANCE_PLAYER_INFO
{
	KUAFU_GROUP_INSTANCE_PLAYER_DAED_TIMES		= 0,									// 玩家信息(0:死亡次数)
	KUAFU_GROUP_INSTANCE_PLAYER_REBRON_CD		= KUAFU_GROUP_INSTANCE_PLAYER_DAED_TIMES + 1,	//原地复活cd
	MAX_KUAFU_GROUP_INSTANCE_PLAYER_INT_COUNT,											// kuafu属性数量

	KUAFU_GROUP_INSTANCE_PLAYER_NAME			= 0,									//玩家名称
	KUAFU_GROUP_INSTANCE_PLAYER_GUID			= KUAFU_GROUP_INSTANCE_PLAYER_NAME + 1,	//玩家guid
	KUAFU_GROUP_INSTANCE_PLAYER_REWARDS			= KUAFU_GROUP_INSTANCE_PLAYER_GUID + 1,	//玩家奖励
	MAX_KUAFU_GROUP_INSTANCE_PLAYER_STR_COUNT,
};

#define MAX_GROUP_INSTANCE_PLAYER_COUNT 3
//跨服组队
enum KUAFU_GROUP_INSTANCE_FIELDS
{
	KUAFU_GROUP_INSTANCE_FIELDS_HARD = MAP_INT_FIELD_INSTANCE_TYPE + 1,			// 难度
	KUAFU_GROUP_INSTANCE_FIELDS_PART = KUAFU_GROUP_INSTANCE_FIELDS_HARD + 1,	// 组队副本的第几部分

	KUAFU_GROUP_INSTANCE_INT_FIELDS_PLAYER_INFO_START = KUAFU_GROUP_INSTANCE_FIELDS_PART + 1,	//
	KUAFU_GROUP_INSTANCE_INT_FIELDS_PLAYER_INFO_END	  = KUAFU_GROUP_INSTANCE_INT_FIELDS_PLAYER_INFO_START + MAX_KUAFU_GROUP_INSTANCE_PLAYER_INT_COUNT * MAX_GROUP_INSTANCE_PLAYER_COUNT,

	KUAFU_GROUP_INSTANCE_STR_FIELDS_PLAYER_INFO_START = KUAFU_GROUP_INSTANCE_FIELDS_PART + 1,	//
	KUAFU_GROUP_INSTANCE_STR_FIELDS_PLAYER_INFO_END	  = KUAFU_GROUP_INSTANCE_STR_FIELDS_PLAYER_INFO_START + MAX_KUAFU_GROUP_INSTANCE_PLAYER_STR_COUNT * MAX_GROUP_INSTANCE_PLAYER_COUNT,
};


enum DOUJIANTAI_FIELDS
{
	DOUJIANTAI_FIELDS_INT_RANK	= MAP_INT_FIELD_INSTANCE_TYPE + 1,			// 2 shorts (0:自己的排名, 1:对手的排名)
	DOUJIANTAI_FIELDS_INT_COMBAT_WIN_INFO = DOUJIANTAI_FIELDS_INT_RANK + 1,	// 2 shorts (0:历史最大连胜, 1:当前连胜)
};

enum XIULIANCHANG_FIELDS
{
	XIULIANCHANG_FIELDS_INT_RANK	= MAP_INT_FIELD_INSTANCE_TYPE + 1,			// 敌人斗剑台排行
	XIULIANCHANG_FIELDS_INT_ROBOT_ID = XIULIANCHANG_FIELDS_INT_RANK + 1,	// 敌人机器人序号
	XIULIANCHANG_FIELDS_INT_LEVEL	= XIULIANCHANG_FIELDS_INT_ROBOT_ID + 1,		//敌人等级 结算经验用

	XIULIANCHANG_FIELDS_STR_INFO_GUID	= MAP_STR_REWARD + 1,				//敌人guid
	XIULIANCHANG_FIELDS_STR_INFO_CONTENT	= XIULIANCHANG_FIELDS_STR_INFO_GUID + 1,				//敌人属性content  
	XIULIANCHANG_FIELDS_STR_INFO_NAME	= XIULIANCHANG_FIELDS_STR_INFO_CONTENT + 1,				//敌人名称


};

//VIP BOSS

enum VIP_INSTANCE_FIELDS
{
	VIP_INSTANCE_FIELD_ID = MAP_INT_FIELD_INSTANCE_TYPE + 1,	// 0:VIP副本序号,1:副本难度
};

enum MAP_MASS_BOSS_FIELDS
{
	MAP_MASS_BOSS_INT_FIELD_ROOM		= MAP_INT_FIELD_INSTANCE_TYPE + 1,								// 所属房间
	MAP_MASS_BOSS_INT_FIELD_BOSS_CREATE = MAP_MASS_BOSS_INT_FIELD_ROOM + 1,								// 全民BOSS是否在地图创建
	MAP_MASS_BOSS_INT_FIELD_MAX_HP = MAP_MASS_BOSS_INT_FIELD_BOSS_CREATE + 1,							//bosshp
};

enum MAP_PRIVATE_BOSS_FIELDS
{
	MAP_PRIVATE_BOSS_INT_FIELD_ID	= MAP_INT_FIELD_INSTANCE_TYPE + 1,	//个人bossid
	MAP_PRIVATE_BOSS_INT_FIELD_BUFFEFFECT_ID	= MAP_PRIVATE_BOSS_INT_FIELD_ID + 1, //buff效果id
};

enum WORLDBOSS_ENROLL_FIELDS
{
	WORLDBOSS_FIELDS_WAIT_TIME	=	MAP_INT_FIELD_INSTANCE_TYPE + 1,	//报名等待时间戳
};

enum WORLDBOSS_FIELDS
{
	WORLDBOSS_FIELDS_BORN_TIME	=	WORLDBOSS_FIELDS_WAIT_TIME + 1,		//刷新等待时间戳
};

enum RESOURCE_INSTANCE_FIELDS
{
	RES_INSTANCE_FIELD_ID = MAP_INT_FIELD_INSTANCE_TYPE + 1,	//资源副本的索引

};

enum STAGE_INSTANCE_FIELDS
{
	STAGE_INSTANCE_BUFF_ID = RES_INSTANCE_FIELD_ID + 1,	//闯关副本场景buffid

};


//世界冒险
enum RISK_INSTANCE_FIELDS
{
	TRIAL_INSTANCE_FIELD_CURSOR		= MAP_INT_FIELD_INSTANCE_TYPE + 1,		//当前已经刷了多少波了
	TRIAL_INSTANCE_FIELD_SECTION_ID	= TRIAL_INSTANCE_FIELD_CURSOR + 1,		//关卡id
	TRIAL_INSTANCE_FIELD_ORDER		= TRIAL_INSTANCE_FIELD_SECTION_ID + 1,	//刷怪优先级序号(1个byte存一个数据)
	TRIAL_INSTANCE_FIELD_BOSS_REFRESHED = TRIAL_INSTANCE_FIELD_ORDER + 2,	//是否已经刷怪
	TRIAL_INSTANCE_FIELD_LAST_RANDOM_TIMESTAMP = TRIAL_INSTANCE_FIELD_BOSS_REFRESHED + 1,	//最近随机刷怪时间戳
};

//家族场景
enum FACTION_INSTANCE_FIELDS
{
	FACTION_INSTANCE_FIELD_GUID = MAP_STR_REWARD + 1,	// 家族GUID string
};

//家族首领挑战场景
enum FACTION_BOSSDEFENSE_INSTANCE_FIELDS
{
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_BUILDING_LV = MAP_INT_FIELD_INSTANCE_TYPE + 1,	//家族建筑等级
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_INDEX = FACTION_BOSSDEFENSE_INSTANCE_FIELD_BUILDING_LV + 1,	//boss点 index
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_POOL_ID = FACTION_BOSSDEFENSE_INSTANCE_FIELD_INDEX + 1,		//怪物池 id
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_HP = FACTION_BOSSDEFENSE_INSTANCE_FIELD_POOL_ID + 1,			//怪物剩余hp

	FACTION_BOSSDEFENSE_INSTANCE_FIELD_PLAYER_GUID = MAP_STR_REWARD + 1,	// 玩家GUID string
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_FACTION_GUID = FACTION_BOSSDEFENSE_INSTANCE_FIELD_PLAYER_GUID + 1,	// 家族GUID string
};

//家族无尽远征场景
enum FACTION_TOWER_INSTANCE_FIELDS
{
	FACTION_TOWER_INSTANCE_FIELD_FLOOR = MAP_INT_FIELD_INSTANCE_TYPE + 1,	// 当前层数
	FACTION_TOWER_INSTANCE_FIELD_BUFF = FACTION_TOWER_INSTANCE_FIELD_FLOOR + 1,	// 玩家获得的buffeffect_id
	FACTION_TOWER_INSTANCE_FIELD_DEBUFF = FACTION_TOWER_INSTANCE_FIELD_BUFF + 1, //玩家获得的debuffeffect_id
	FACTION_TOWER_INSTANCE_FIELD_MONSTER_NUM = FACTION_TOWER_INSTANCE_FIELD_DEBUFF + 1, //当前怪物数量
};

//试炼塔
enum TRIAL_INSTANCE_FIELDS
{
	TRIAL_INSTANCE_FIELD_ID = MAP_INT_FIELD_INSTANCE_TYPE + 1,	// 当前层数
};

enum GROUP_EXP_INSTANCE_PLAYER_INFO
{
	GROUP_EXP_INSTANCE_INT_EXP = 0,
	GROUP_EXP_INSTANCE_INT_MONEY_BUY = GROUP_EXP_INSTANCE_INT_EXP + 2,			// 银币购买次数
	GROUP_EXP_INSTANCE_INT_INGOT_BUY = GROUP_EXP_INSTANCE_INT_MONEY_BUY + 1,	// 绑定元宝购买
	GROUP_EXP_INSTANCE_INT_CD		 = GROUP_EXP_INSTANCE_INT_INGOT_BUY + 1,	// 复活cd
	GROUP_EXP_INSTANCE_EFFECT		 = GROUP_EXP_INSTANCE_INT_CD + 1,			// 效果
	MAX_EXP_INFO_INT_COUNT,

	GROUP_EXP_INSTANCE_STR_GUID = 0,
	MAX_EXP_INFO_STR_COUNT,
};

//组队经验副本
enum GROUP_EXP_INSTANCE_FIELDS
{
	GROUP_EXP_INSTANCE_FIELD_ID				= MAP_INT_FIELD_INSTANCE_TYPE + 1,	// 当前层数
	GROUP_EXP_INSTANCE_FIELD_CNT			= GROUP_EXP_INSTANCE_FIELD_ID + 1,	// 总杀怪数量
	GROUP_EXP_INSTANCE_FIELD_INDX			= GROUP_EXP_INSTANCE_FIELD_CNT + 1,	// 刷怪位置序号
	GROUP_EXP_INSTANCE_INT_FIELD_INFO_START = GROUP_EXP_INSTANCE_FIELD_INDX + 1,
	GROUP_EXP_INSTANCE_INT_FIELD_INFO_END	= GROUP_EXP_INSTANCE_INT_FIELD_INFO_START + MAX_GROUP_MEMBER_COUNT * MAX_EXP_INFO_INT_COUNT,

	GROUP_EXP_INSTANCE_STR_FIELD_INFO_START = MAP_STR_REWARD + 1,
	GROUP_EXP_INSTANCE_STR_FIELD_INFO_END	= GROUP_EXP_INSTANCE_STR_FIELD_INFO_START + MAX_GROUP_MEMBER_COUNT * MAX_EXP_INFO_STR_COUNT,
};

// 桃花迷阵最大刷新次数
#define TAOHUA_REFRESH_TIMES 10;
//桃花迷阵地图数据
enum TaoHuaMiZhenFileds {
	TAOHUA_INT_FIELD_REFRESH_TIMES = MAP_INT_FIELD_INSTANCE_TYPE + 1,		//桃花迷阵已经刷新次数
	TAOHUA_INT_FIELD_BOSS_CURR_HP = TAOHUA_INT_FIELD_REFRESH_TIMES + 1,		//BOSS当前血量

	TAOHUA_STR_FIELD_REAL_BOSS_GUID = MAP_STR_GENERAL_ID + 1,	//BOSS真身GUID
};

//塔的最大层数
#define TOWER_MAX_FLOOR = 2;
//塔怪每层击杀数量
enum TaGuaiKillCountFields {
	TAGUAI_INT_FIELD_FIRST_FLOOR = MAP_INT_FIELD_INSTANCE_TYPE + 1,		//第一层的信息
};


//家族战场景内数据
enum FactionMatchInstanceFields {
	FACTION_MATCH_INSTANCE_INT_FIELD_DETAIL_ID = MAP_INT_FIELD_INSTANCE_TYPE + 1,		//比赛详情Id

	FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_ID_1 = FACTION_MATCH_INSTANCE_INT_FIELD_DETAIL_ID + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_RESULT_1 = FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_ID_1 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_MEMBER_COUNT_1 = FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_RESULT_1 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_SCORE_1 = FACTION_MATCH_INSTANCE_INT_FIELD_MEMBER_COUNT_1 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_1 = FACTION_MATCH_INSTANCE_INT_FIELD_SCORE_1 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_BUFF_1 = FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_1 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_ICON_1 = FACTION_MATCH_INSTANCE_INT_FIELD_BUFF_1 + 1,

	FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_ID_2 = FACTION_MATCH_INSTANCE_INT_FIELD_ICON_1 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_RESULT_2 = FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_ID_2 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_MEMBER_COUNT_2 = FACTION_MATCH_INSTANCE_INT_FIELD_MATCH_RESULT_2 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_SCORE_2 = FACTION_MATCH_INSTANCE_INT_FIELD_MEMBER_COUNT_2 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_2 = FACTION_MATCH_INSTANCE_INT_FIELD_SCORE_2 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_BUFF_2 = FACTION_MATCH_INSTANCE_INT_FIELD_FLAG_2 + 1,
	FACTION_MATCH_INSTANCE_INT_FIELD_ICON_2 = FACTION_MATCH_INSTANCE_INT_FIELD_BUFF_2 + 1,

	FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_GUID_1 = MAP_STR_GENERAL_ID + 1,
	FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_NAME_1 = FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_GUID_1 + 1,

	FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_GUID_2 = FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_NAME_1 + 1,
	FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_NAME_2 = FACTION_MATCH_INSTANCE_STRING_FIELD_FACTION_GUID_2 + 1,


};

//战斗信息整形字符型枚举
//貌似没必要,随便留一个吧
enum FightingInfoStringType
{
	FIGHTING_INFO_STRING_CASTER		= 0,								//施法者
	FIGHTING_INFO_STRING_TARGET		= FIGHTING_INFO_STRING_CASTER + 1,		//目标
	MAX_FIGHTING_INFO_STRING,
};

//战斗信息最大数量
#define MAX_FIGHTING_INFO_COUNT 100

//战斗信息整形字段枚举
enum FightingInfoIntType
{
	FIGHTING_INFO_INT_VALUES		= 0,		//伤害或者治疗 治疗发负数
	FIGHTING_INFO_INT_UINT8			= FIGHTING_INFO_INT_VALUES + 2,	//0:是否被杀 1:施法者生物类型（玩家还是生物）2:目标生物类型（玩家还是生物） 3:伤害类型(暴击、闪避之类的)
	FIGHTING_INFO_INT_SPELL_ID		= FIGHTING_INFO_INT_UINT8 + 1,		//技能id
	FIGHTING_INFO_INT_HP			= FIGHTING_INFO_INT_SPELL_ID + 1,	//技能计算完以后，生物剩余血量
	FIGHTING_INFO_INT_RESERVE_0		= FIGHTING_INFO_INT_HP + 1,	//预留
	FIGHTING_INFO_INT_RESERVE_1		= FIGHTING_INFO_INT_RESERVE_0 + 1,	//预留	
	FIGHTING_INFO_INT_RESERVE_2		= FIGHTING_INFO_INT_RESERVE_1 + 1,	//预留
	FIGHTING_INFO_INT_RESERVE_3		= FIGHTING_INFO_INT_RESERVE_2 + 1,	//预留	
	MAX_FIGHTING_INFO_INT,
};

//战斗信息字段
enum EFightingInfoFields
{
	MAX_FIGHTING_INFO_INT_NOW_INDEX		= 0,	//当前战斗力信息下标用到第几个战斗信息了
	MAX_FIGHTING_INFO_INT_START			= MAX_FIGHTING_INFO_INT_NOW_INDEX + 1,
	MAX_FIGHTING_INFO_INT_FIELD			= MAX_FIGHTING_INFO_INT_START + MAX_FIGHTING_INFO_INT * MAX_FIGHTING_INFO_COUNT,

	FIGHTING_INFO_STRING_FIELD_START	= BINLOG_STRING_FIELD_OWNER + 1,
	MAX_FIGHTING_INFO_STRING_FIELD		= FIGHTING_INFO_STRING_FIELD_START + MAX_FIGHTING_INFO_STRING * MAX_FIGHTING_INFO_COUNT,
}; 

//查询用的玩家信息binlog
enum EQueryPlayerFileds
{
	QUERY_PLAYER_INT_UINT16			= 0,								//0 等级，1 宝石等级
	QUERY_PLAYER_INT_BYTE1			= QUERY_PLAYER_INT_UINT16 + 1,		//0 头像，1 发型，2 种族，3 性别
	QUERY_PLAYER_INT_BYTE2			= QUERY_PLAYER_INT_BYTE1 + 1,		//0 阵营，1 是否在线，2 称号,3 vip
	// 基础属性
	QUERY_PLAYER_INT_BASE_ATTR_START		= QUERY_PLAYER_INT_BYTE2 + 1,										//玩家基本属性开始
	QUERY_PLAYER_INT_BASE_ATTR_END			= QUERY_PLAYER_INT_BASE_ATTR_START + MAX_BASE_ATTR * 2,		//玩家基本属性结束
	QUERY_PLAYER_INT_FIXED_ATTR_START		= QUERY_PLAYER_INT_BASE_ATTR_END,							//玩家固定属性开始
	QUERY_PLAYER_INT_FIXED_ATTR_END			= QUERY_PLAYER_INT_FIXED_ATTR_START + MAX_BASE_ATTR * 2,		//玩家固定属性结束	
	QUERY_PLAYER_INT_LUCKY					= QUERY_PLAYER_INT_FIXED_ATTR_END,				//幸运
	QUERY_PLAYER_INT_MEILI					= QUERY_PLAYER_INT_LUCKY + 2,					//魅力
	QUERY_PLAYER_INT_BEAR					= QUERY_PLAYER_INT_MEILI + 2,					//负重
	QUERY_PLAYER_INT_POISON					= QUERY_PLAYER_INT_BEAR + 2,					//毒
	QUERY_PLAYER_INT_ICE					= QUERY_PLAYER_INT_POISON + 2,					//冰
	QUERY_PLAYER_MOVESPEED					= QUERY_PLAYER_INT_ICE + 2,						//移动速度
	QUERY_PLAYER_PHYSICAL					= QUERY_PLAYER_MOVESPEED + 2,					//体力
	QUERY_PLAYER_INT_FORCE					= QUERY_PLAYER_PHYSICAL + 2,					//战斗力
	QUERY_PLAYER_ONLINE_TIME				= QUERY_PLAYER_INT_FORCE + 2,					//总在线时长
	// 身上的装备
	QUERY_PLAYER_INT_EQUIPMENT				= QUERY_PLAYER_ONLINE_TIME + 1,
	QUERY_PLAYER_INT_EQUIPMENT_END			= QUERY_PLAYER_INT_EQUIPMENT + EQUIPMENT_TYPE_MAX_POS,

	QUERY_PLAYER_INT_FLAG				= QUERY_PLAYER_INT_EQUIPMENT_END,		//查询某些标志位
	QUERY_PLAYER_INT_FORCE_LEVEL		= QUERY_PLAYER_INT_FLAG + 1,			//等级战斗力PLAYER_INT_PIFENG_ZIZHI_FORCE
	QUERY_PLAYER_INT_FORCE_ITEM			= QUERY_PLAYER_INT_FORCE_LEVEL + 2,		//装备战斗力
	QUERY_PLAYER_INT_FORCE_FACTION		= QUERY_PLAYER_INT_FORCE_ITEM + 2,		//帮派战斗力
	QUERY_PLAYER_INT_FLAG_TYPE			= QUERY_PLAYER_INT_FORCE_FACTION + 2,	//当前玩家查询类型标志
	QUERY_PLAYER_INT_FORGING_STRENG		= QUERY_PLAYER_INT_FLAG_TYPE + 1,		//0 查询玩家强化等级，1 预留 16位


	QUERY_PLAYER_STRING_GUID				= BINLOG_STRING_FIELD_OWNER + 1,		//不要直接放到guid去，怕混乱
	QUERY_PLAYER_STRING_NAME				= QUERY_PLAYER_STRING_GUID + 1,			//玩家名字
	QUERY_PLAYER_STRING_FACTION_ID			= QUERY_PLAYER_STRING_NAME + 1,			//帮派ID
	QUERY_PLAYER_STRING_FACTION_NAME		= QUERY_PLAYER_STRING_FACTION_ID + 1,	//帮派名称

	MAX_QUERY_PLAYER_STRING_FIELD,
};

/////////////////////////////////////查看物品//////////////////////////////////////////////////////////////////////////
//查看物品下标
enum ItemQueryField
{
	////////////////////int部分///////////////////////////////////////
	ITEM_QUERY_INT_FIELD_COUNT = 0,
	////////////////////string部分///////////////////////////////////////
	ITEM_QUERY_STR_FIELD_START	= BINLOG_STRING_FIELD_OWNER + 1,
};

//礼包信息记录类型枚举
enum GiftPacksInfoType
{
	GIFTPACKS_INFO_INT_ID			= 0,	//礼包ID
	GIFTPACKS_INFO_INT_START_TIME	= 1,	//发放时间
	GIFTPACKS_INFO_INT_END_TIME		= 2,	//结束时间
	GIFTPACKS_INFO_INT_BYTE			= 3,	//0,礼包类型，1，领取状态,2 已阅读,3是否删除
	MAX_GIFTPACKS_INFO_INT,

	GIFTPACKS_INFO_STRING_GIFT_NAME	= 0,	//礼包名称
	GIFTPACKS_INFO_STRING_GIFT_DESC	= 1,	//礼包说明
	GIFTPACKS_INFO_STRING_GIFT_FROM = 2,	//礼包出处，当玩家赠送时填写玩家名字，默认为空，系统赠送
	GIFTPACKS_INFO_STRING_GIFT_ITEM = 3,	//礼包物品集合
	MAX_GIFTPACKS_INFO_STRING,
};

//礼包信息最多条数
#define MAX_GIFTPACKS_INFO_COUNT 100

//礼包信息binlog
enum GiftPacksInfoFileds
{
	MAX_GIFTPACKS_INFO_INT_NOW_INDEX			= 0,	//当前礼包信息下标索引
	GIFTPACKS_INT_FIELD_BEGIN					= MAX_GIFTPACKS_INFO_INT_NOW_INDEX + 1,		
	MAX_GIFTPACKS_INT_FIELD						= GIFTPACKS_INT_FIELD_BEGIN + MAX_GIFTPACKS_INFO_COUNT * MAX_GIFTPACKS_INFO_INT,	

	GIFTPACKS_STRING_FIELD_BEGIN				=  BINLOG_STRING_FIELD_OWNER + 1,		
	MAX_GIFTPACKS_STRING_FIELD					= GIFTPACKS_STRING_FIELD_BEGIN + MAX_GIFTPACKS_INFO_COUNT * MAX_GIFTPACKS_INFO_STRING,	
};

//排行类型
enum ERankTypes
{
	RANK_TYPE_POWER					= 0,							//战斗力排行
	RANK_TYPE_LEVEL					= 1,							//等级排行
	RANK_TYPE_MONEY					= 2,							//财富排行
	RANK_TYPE_ONLINE_TIME			= 3,							//在线时长排行
	RANK_TYPE_TRIAL					= 4,							//试炼塔排行
	RANK_TYPE_FACTION				= 5,							//家族排行
	RANK_TYPE_DIVINE				= 6,							//神兵排行
	RANK_TYPE_MOUNT					= 7,							//坐骑排行
	RANK_TYPE_SINGLE_PVP			= 8,							//单人PVP排行
	RANK_TYPE_WINGS					= 9,							//翅膀排行
	RANK_TYPE_3V3					= 10,							//本地3v3

	MAX_RANK_TYPE
};

//特殊类型排行榜
enum ERankSpecTypes
{
	RANK_TYPE_DOUJIANTAI			= MAX_RANK_TYPE+1,//斗剑台排行
};

//单个排行榜最大排名个数
#define RANK_LIST_MAX_VALUES 100
#define RANK_LIST_MAX_SHOW 4

//排行榜个体binlog下标
enum ERankListCurrentObjFiled
{
	RANK_LIST_CURRENT_OBJ_INT_FIELD_TYPE			= 0,												//排行榜类型
	RANK_LIST_CURRENT_OBJ_INT_FIELD_RANKING			= 1,												//名次
	RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE			= 2,												//byte 0，性别，数量
	RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE2			= 3,												//通用字段
	RANK_LIST_CURRENT_OBJ_INT_FIELD_TITLE			= 4,												//称号
	//排行榜
	RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE			= RANK_LIST_CURRENT_OBJ_INT_FIELD_TITLE + 1,		//战斗力
	RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL			= RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE + 2,		//等级
	RANK_LIST_CURRENT_OBJ_INT_FIELD_MONEY			= RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL + 1,	//铜钱
	RANK_LIST_CURRENT_OBJ_INT_FIELD_ONLINE_TIME		= RANK_LIST_CURRENT_OBJ_INT_FIELD_MONEY + 2,	//在线时长
	RANK_LIST_CURRENT_OBJ_INT_FIELD_TRIAL			= RANK_LIST_CURRENT_OBJ_INT_FIELD_ONLINE_TIME + 1,	//试炼塔层数
	RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW			= RANK_LIST_CURRENT_OBJ_INT_FIELD_TRIAL + 1,					//外观列表开始
	RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW_END		= RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW + RANK_LIST_MAX_SHOW,	//外观结束
	RANK_LIST_CURRENT_OBJ_INT_FIELD_LIKE			= RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW_END + 1,//点赞数
	RANK_LIST_CURRENT_OBJ_INT_FIELD_WING			= RANK_LIST_CURRENT_OBJ_INT_FIELD_LIKE + 1,		//翅膀id

	RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID			= BINLOG_STRING_FIELD_OWNER + 1,
	RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID		= RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID + 1,				//玩家guid
	RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_NAME		= RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID + 1,		//玩家名字
	RANK_LIST_CURRENT_OBJ_STR_FIELD_FACTION_NAME	= RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_NAME + 1,		//帮派名字
};
enum ERankListFactionObjFiled
{
	RANK_LIST_INT_FIELD_FACTION_LEV		= RANK_LIST_CURRENT_OBJ_INT_FIELD_RANKING + 1,//byte 0，性别
	RANK_LIST_INT_FIELD_FACTION_COUNT	= RANK_LIST_INT_FIELD_FACTION_LEV + 1,
	RANK_LIST_INT_FIELD_FACTION_BYTE	= RANK_LIST_INT_FIELD_FACTION_COUNT + 1,//icon minlev

	RANK_LIST_STR_FIELD_FACTION_GUID	= RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID,//帮派GUID
	RANK_LIST_STR_FIELD_FACTION_NAME	= RANK_LIST_STR_FIELD_FACTION_GUID + 1,//帮派名字
	RANK_LIST_STR_FIELD_FACTION_SQGG	= RANK_LIST_STR_FIELD_FACTION_NAME + 1,//帮派申请公告
};

enum ItemShowType
{
	ITEM_SHOW_TYPE_DEFAULT				= 0,	//默认显示
	ITEM_SHOW_TYPE_MINI_QUEST_BAR		= 1,	//小任务面板
	ITEM_SHOW_TYPE_MINI_QUEST_DAILY2	= 2,	//日常任务面板
};


//弹窗公告记录类型枚举
enum RightFloatInfoType
{
	RIGHTFLOAT_INFO_INT_ID				= 0,	//公告ID
	RIGHTFLOAT_INFO_INT_START_TIME		= 1,	//起始时间
	RIGHTFLOAT_INFO_INT_END_TIME		= 2,	//结束时间
	RIGHTFLOAT_INFO_INT_ZONE_1			= 3,	//0-7点
	RIGHTFLOAT_INFO_INT_ZONE_2			= 4,	//8-13点
	RIGHTFLOAT_INFO_INT_ZONE_3			= 5,	//14-23点
	RIGHTFLOAT_INFO_INT_BYTE			= 6,	//0 弹窗设置,1 公告状态,2 预留,3 预留
	RIGHTFLOAT_INFO_INT_ADD_TIME		= 7,	//添加时间
	MAX_RIGHTFLOAT_INFO_INT,			

	RIGHTFLOAT_INFO_STRING_SUBJECT		= 0,	//标题
	RIGHTFLOAT_INFO_STRING_CONTENT		= 1,	//内容
	RIGHTFLOAT_INFO_STRING_LINK			= 2,	//链接地址
	MAX_RIGHTFLOAT_INFO_STRING,
};

//弹窗信息最多条数
#define MAX_RIGHTFLOAT_INFO_COUNT 100

//弹窗公告信息binlog
enum RightFloatInfoFileds
{
	MAX_RIGHTFLOAT_INFO_INT_NOW_INDEX			= 0,	//当前弹窗公告信息下标索引
	RIGHTFLOAT_INT_FIELD_START					= MAX_RIGHTFLOAT_INFO_INT_NOW_INDEX + 1,		
	MAX_RIGHTFLOAT_INT_FIELD						= RIGHTFLOAT_INT_FIELD_START + MAX_RIGHTFLOAT_INFO_COUNT * MAX_RIGHTFLOAT_INFO_INT,	

	RIGHTFLOAT_STRING_FIELD_START				=  BINLOG_STRING_FIELD_OWNER + 1,		
	MAX_RIGHTFLOAT_STRING_FIELD					= RIGHTFLOAT_STRING_FIELD_START + MAX_RIGHTFLOAT_INFO_COUNT * MAX_RIGHTFLOAT_INFO_STRING,	
};


//限时活动binlog
enum LimitActivityInfoFileds
{
	LIMIT_ACTIVITY_INT_FIELD_VERSION				= 0,											//活动版本号
	LIMIT_ACTIVITY_INT_FIELD_START_TIME				= LIMIT_ACTIVITY_INT_FIELD_VERSION + 1,			//活动开始时间
	LIMIT_ACTIVITY_INT_FIELD_END_TIME				= LIMIT_ACTIVITY_INT_FIELD_START_TIME + 1,		//活动结束时间
	LIMIT_ACTIVITY_INT_FIELD_RECHARGE_SUM			= LIMIT_ACTIVITY_INT_FIELD_END_TIME + 1,		//充值总数
	LIMIT_ACTIVITY_INT_FIELD_RECHARGE_TIME			= LIMIT_ACTIVITY_INT_FIELD_RECHARGE_SUM + 1,	//最后充值时间
	LIMIT_ACTIVITY_INT_FIELD_REWARD_COUNT			= 100,											//活动领取计数开始
	LIMIT_ACTIVITY_INT_FIELD_REWARD_COUNT_END		= LIMIT_ACTIVITY_INT_FIELD_REWARD_COUNT + 400,	//活动领取计数结束

	LIMIT_ACTIVITY_STRING_FIELD_RECHARGE_ID			= BINLOG_STRING_FIELD_OWNER + 1,				//最后充值ID
	LIMIT_ACTIVITY_STRING_FIELD_CLIENT_CONFIG		= LIMIT_ACTIVITY_STRING_FIELD_RECHARGE_ID + 1,	//客户端配置
};

//公告信息最多条数
#define MAX_NOTICE_MESSAGE_NUMBER 100

//公告信息类型
enum NoticeMessageInfoType
{
	NOTICE_MESSAGE_INFO_TYPE_FISHING		= 0,	//钓鱼公告
	NOTICE_MESSAGE_INFO_TYPE_MINING			= 1,	//矿洞公告
	NOTICE_MESSAGE_INFO_TYPE_WORLD_BOSS		= 2,	//世界boss掉落
	NOTICE_MESSAGE_INFO_TYPE_KAIFUJIJIN		= 3,	//开服基金公告
	MAX_MESSAGE_INFO_TYPE
};

//公告信息binlog
enum NoticeMessageInfoFileds
{
	NOTICE_MESSAGE_INT_FIELD_INDEX					= 0,											//公告位置索引
	NOTICE_MESSAGE_INT_FIELD_INDEX_END				= NOTICE_MESSAGE_INT_FIELD_INDEX + MAX_MESSAGE_INFO_TYPE,	//公告索引位置结束

	NOTICE_MESSAGE_STRING_FIELD_START				= BINLOG_STRING_FIELD_OWNER + 1,				//公告信息内容开始
	NOTICH_MESSAGE_STRING_FIELD_END					= NOTICE_MESSAGE_STRING_FIELD_START + MAX_NOTICE_MESSAGE_NUMBER * MAX_MESSAGE_INFO_TYPE,		//公告信息内容结束
};

//系统邮件信息记录类型枚举
enum SystemMailInfoType
{
	SYSTEM_MAIL_INFO_INT_ID				= 0,	//礼包ID
	SYSTEM_MAIL_INFO_INT_START_TIME		= 1,	//发放时间
	SYSTEM_MAIL_INFO_INT_END_TIME		= 2,	//结束时间
	SYSTEM_MAIL_INFO_INT_TYPE			= 3,	//礼包类型
	MAX_SYSTEM_MAIL_INFO_INT,

	SYSTEM_MAIL_INFO_STRING_NAME	= 0,	//系统邮件名称
	SYSTEM_MAIL_INFO_STRING_DESC	= 1,	//系统邮件说明
	SYSTEM_MAIL_INFO_STRING_FROM	= 2,	//系统邮件出处，当玩家赠送时填写玩家名字，默认为空，系统赠送
	SYSTEM_MAIL_INFO_STRING_ITEM	= 3,	//礼包物品集合
	MAX_SYSTEM_MAIL_INFO_STRING,
};

//系统邮件信息最多条数
#define MAX_SYSTEM_MAIL_INFO_COUNT 8192

// 系统邮件(对全服都有效的)
enum SYSTEM_MAIL
{
	SYSTEM_MAIL_COUNT							= 0,				//系统邮件个数
	MAX_SYSTEM_MAIL_INFO_INT_NOW_INDEX			= 1,				//当前系统邮件信息下标索引
	SYSTEM_MAIL_INT_FIELD_BEGIN					= MAX_SYSTEM_MAIL_INFO_INT_NOW_INDEX + 1,
	SYSTEM_MAIL_INT_FIELD_END					= SYSTEM_MAIL_INT_FIELD_BEGIN + MAX_SYSTEM_MAIL_INFO_COUNT * MAX_SYSTEM_MAIL_INFO_INT,

	SYSTEM_MAIL_STRING_FIELD_BEGIN				= BINLOG_STRING_FIELD_OWNER + 1,
	SYSTEM_MAIL_STRING_FIELD_END				= SYSTEM_MAIL_STRING_FIELD_BEGIN + MAX_SYSTEM_MAIL_INFO_COUNT * MAX_SYSTEM_MAIL_INFO_STRING,
};

//离线邮件最多条数
#define MAX_OFFLINE_MAIL_INFO_COUNT 16384
// 离线邮件存储地方
enum OfflineMailStore
{
	OFFLINE_MAIL_STORE_RANK_LEVEL = 0,	//等级排行榜离线邮件存储

	MAX_OFFLINE_MAIL_STORE_COUNT
};


//托管操作
enum HostingOptType
{
	HOSTING_OPT_TYPE_APPLY			= 0,	//托管申请
	HOSTING_OPT_TYPE_AGREED			= 1,	//托管同意
	HOSTING_OPT_TYPE_CANCEL			= 2,	//托管取消
	HOSTING_OPT_TYPE_LOGIN			= 3,	//托管登录
	HOSTING_OPT_TYPE_REFUSE			= 4,	//托管拒绝
	HOSTING_OPT_TYPE_DUE_TO			= 5,	//托管到期
	HOSTING_OPT_TYPE_APPLY_DUE_TO	= 6,	//托管申请到期
};




//部位信息个数
#define MAX_EQUIP_PART_NUMBER 10

//一个部位的宝石个数
#define ONE_EQUIP_PART_GEM_NUMBER 6

// 一个装备部位信息类型
enum EquipPartOptType {
	EQUIP_PART_OPT_TYPE_STRENGTH_LEVEL_OFFSET = 0,												//强化等级偏移值
	EQUIP_PART_OPT_TYPE_GEM_INFO_OFFSET = EQUIP_PART_OPT_TYPE_STRENGTH_LEVEL_OFFSET + 1,		//宝石信息偏移值

	EQUIP_PART_OPT_TYPE_GEM_LEVEL_OFFSET = 0,													//宝石信息中宝石等级偏移值
	EQUIP_PART_OPT_TYPE_GEM_EXP_OFFSET = EQUIP_PART_OPT_TYPE_GEM_LEVEL_OFFSET + 1,				//宝石信息中宝石经验偏移值
	EQUIP_PART_OPT_TYPE_ONE_GEM_INFO_LENGTH = EQUIP_PART_OPT_TYPE_GEM_EXP_OFFSET + 1,			//一个宝石信息的长度

	EQUIP_PART_OPT_TYPE_ONE_PART_INFO_LENGTH = EQUIP_PART_OPT_TYPE_GEM_INFO_OFFSET + EQUIP_PART_OPT_TYPE_ONE_GEM_INFO_LENGTH * ONE_EQUIP_PART_GEM_NUMBER,	//一个装备部位的信息长度
	EQUIP_PART_OPT_TYPE_PARTS_INFO_LENGTH = EQUIP_PART_OPT_TYPE_ONE_PART_INFO_LENGTH * MAX_EQUIP_PART_NUMBER,												//所有装备部位总信息长度 
};

// 业务BinLog
enum AppdLogicalInfoFields {
	APPD_LOGICAL_INFO_INT_FIELD_STRENGTH_START = 0,	//部位信息的起始位置
	APPD_LOGICAL_INFO_INT_FIELD_STRENGTH_END_EXCLUDE = APPD_LOGICAL_INFO_INT_FIELD_STRENGTH_START + EQUIP_PART_OPT_TYPE_PARTS_INFO_LENGTH, //装备部位的边界
};


//文本解析类型
enum TextType
{
	TEXT_TYPE_POSITION	= 1,				//坐标
	TEXT_TYPE_SUIT		= 2,				//装备
	TEXT_TYPE_GROUP		= 3,				//加入队伍
	TEXT_TYPE_INSTANCE	= 4,				//加入副本
};

// 被动技能效果类型
enum PASSIVE_EFFECT_TYPE
{
	PASSIVE_EFFECT_TYPE_SPELL_AMPLIFY		= 1,	//增强技能效果
	PASSIVE_EFFECT_TYPE_ADD_BUFF			= 2,	//增加buff效果
	PASSIVE_EFFECT_TYPE_CHANGE_SPELL		= 3,	//替换技能效果
	PASSIVE_EFFECT_TYPE_PLAYER_ATTR			= 4,	//提高人物属性
	PASSIVE_EFFECT_TYPE_ADDITIONAL_SPELL	= 5,	//释放额外技能
	PASSIVE_EFFECT_TYPE_PLAYER_LOOT_ATTR	= 6,	//获得属性战利品
	PASSIVE_EFFECT_TYPE_PLAYER_CURE			= 7,	//自动回血
};

// 被动技能触发类型
enum PASSIVE_DISPATCH_TYPE
{
	PASSIVE_DISPATCH_TYPE_FOREVER			= 0,	//永久
	PASSIVE_DISPATCH_TYPE_ATTR_CHANGE		= 1,	//属性改变
	PASSIVE_DISPATCH_TYPE_HIT				= 2,	//攻击命中敌人
	PASSIVE_DISPATCH_TYPE_HURT				= 3,	//受到攻击
	PASSIVE_DISPATCH_TYPE_DEAD				= 4,	//死亡时触发
	PASSIVE_DISPATCH_TYPE_ENEMY_DEAD		= 5,	//敌方死亡
	PASSIVE_DISPATCH_TYPE_ON_BUFF			= 6,	//受到buff的时候触发
	PASSIVE_DISPATCH_TYPE_ENEMY_ON_BUFF		= 7,	//敌方拥有某个buff的时候触发
	PASSIVE_DISPATCH_TYPE_SECONDS			= 8,	//每过多少秒的时候触发
};

//系统模块
enum MODULE_TYPE
{
	MODULE_SETTING = 101, //设置
	MODULE_BAG = 102, //背包
	MODULE_RONGLIAN = 103, //熔炼
	MODULE_QUEST = 104, //任务
	MODULE_DAILY_TASKS = 105, //日常任务
	MODULE_CHAT = 106, //聊天
	MODULE_MAIL = 107, //邮件
	MODULE_MAP = 108, //地图
	MODULE_STRENGTH = 109, //我要变强
	MODULE_CHATPERSON = 110, //私聊
	MODULE_ACTIVE = 111, //活跃
	MODULE_MONEYTREE = 112, //摇钱树
	MODULE_FISH = 113, //我要变弱
	MODULE_REALM = 115, //境界
	MODULE_TEAM = 116, //组队
	MODULE_ROLE = 201, //角色
	MODULE_SPELL = 202, //技能
	MODULE_DIVINE = 203, //法宝
	MODULE_FASHION = 204, //时装
	MODULE_MOUNT = 205, //坐骑
	MODULE_MIX = 206, //炼器
	MODULE_WING = 207, //翅膀
	MODULE_TCM = 208, //经脉
	MODULE_GW = 209, //神器
	MODULE_SOCIAL = 301, //社交
	MODULE_FACTION = 302, //家族
	MODULE_RANK = 303, //排行榜
	MODULE_FACTIONMAIN = 304, //家族-家族主殿
	MODULE_FACTIONSKILL = 305, //家族-技能大厅
	MODULE_FACTIONACTIVE = 306, //家族-活动大厅
	MODULE_FACTIONBOX = 307, //家族-家族宝库
	MODULE_FACTIONBATTLE = 308, //家族-荣耀大厅
	MODULE_MALL = 401, //商城
	MODULE_VIP = 402, //VIP特权
	MODULE_INSTANCE = 501, //副本
	MODULE_WORLD_RISK = 502, //世界冒险
	MODULE_ARENA = 503, //竞技
	MODULE_BOSS = 504, //BOSS
	MODULE_EXP = 505, //历练任务
	MODULE_CP = 506, //闯关
	MODULE_TEAMINSTANCE = 507, //组队副本
	MODULE_WELFARE = 601, //福利
	MODULE_OPENSERVICE = 701, //开服活动
	MODULE_FIRST_RECHARGE = 801, //首冲
	MODULE_TURNTABLE = 1101, //转盘
	MODULE_TEST = 1001, //测试
	MODULE_SETTING_SYSTEM = 1, //设置
	MODULE_BAG_ITEM = 1, //背包
	MODULE_RONGLIAN_ALL = 1, //熔炼
	MODULE_QUEST_MAIN = 1, //主线
	MODULE_QUEST_EXTENSION = 2, //支线
	MODULE_QUEST_ACTIVITY = 3, //活动
	MODULE_DAILY_TASKS_ALL = 1, //日常任务
	MODULE_CHAT_ALL = 1, //聊天
	MODULE_MAIL_ALL = 1, //邮件
	MODULE_MAP_REGION = 1, //区域
	MODULE_MAP_WORLD = 2, //世界
	MODULE_STRENGTH_ALL = 1, //我要变强
	MODULE_CHATPERSON_ALL = 1, //聊天
	MODULE_ACTIVE_ALL = 1, //活跃
	MODULE_MONEYTREE_ALL = 1, //摇钱树
	MODULE_FISH_ALL = 1, //我要变弱
	MODULE_REALM_ALL = 1, //境界
	MODULE_TEAM_ALL = 1, //组队
	MODULE_ROLE_ATTR = 1, //角色属性
	MODULE_ROLE_ACHIEVE = 2, //角色成就
	MODULE_ROLE_TITLE = 3, //角色称号
	MODULE_SPELL_ALL = 1, //技能
	MODULE_DIVINE_ALL = 1, //法宝激活
	MODULE_DIVINE_USE = 2, //法宝装备
	MODULE_FASHION_CLOTHES = 1, //衣服
	MODULE_FASHION_WEAPON = 2, //武器
	MODULE_MOUNT_UPGRADE = 1, //升阶
	MODULE_MOUNT_LEVEL = 2, //升级
	MODULE_MOUNT_SKILL = 3, //技能
	MODULE_MOUNT_ILLUSION = 4, //幻化
	MODULE_MIX_STRENGTH = 1, //强化
	MODULE_MIX_POLISHED = 2, //精炼
	MODULE_MIX_GEM = 3, //宝石
	MODULE_MIX_WASH = 4, //洗练
	MODULE_WING_UPGRADE = 1, //翅膀进阶
	MODULE_WING_STRENGTH = 2, //翅膀强化
	MODULE_TCM_ALL = 1, //角色经脉
	MODULE_GW_ALL = 1, //神器
	MODULE_SOCIAL_FRIEND = 1, //好友
	MODULE_SOCIAL_ENEMY = 2, //仇人
	MODULE_FACTION_RECRUIT = 1, //家族招募
	MODULE_FACTION_CREATE = 2, //创建家族
	MODULE_FACTION_MEMBER = 3, //家族成员
	MODULE_FACTION_FUNCTION = 4, //家族功能
	MODULE_FACTION_WAR = 9, //家族战
	MODULE_RANK_LOCAL = 1, //本服排行
	MODULE_RANK_KUAFU = 2, //跨服排行
	MODULE_FACTIONMAIN_ALL = 1, //家族主殿
	MODULE_FACTIONSKILL_ALL = 1, //技能大厅
	MODULE_FACTIONACTIVE_TRIAL = 1, //家族远征
	MODULE_FACTIONACTIVE_BOSS = 2, //家族boss
	MODULE_FACTIONBOX_DEVOTE = 1, //家族宝库
	MODULE_FACTIONBOX_ITEM = 2, //家族仓库
	MODULE_FACTIONBATTLE_ALL = 1, //荣耀大厅
	MODULE_MALL_GOLD = 1, //元宝商城
	MODULE_MALL_SCORE = 2, //积分商店
	MODULE_MALL_RECHARGE = 3, //充值
	MODULE_VIP_ALL = 1, //VIP特权
	MODULE_INSTANCE_PLOT = 1, //剧情副本
	MODULE_INSTANCE_RES = 2, //资源副本
	MODULE_INSTANCE_TRIAL = 3, //试炼塔
	MODULE_INSTANCE_TEAM = 4, //多人副本
	MODULE_WORLD_RISK_MAIN = 1, //世界冒险
	MODULE_ARENA_DOUJIANTAI = 1, //斗剑台(1V1)
	MODULE_ARENA_XIANMO = 2, //仙魔道(3V3)
	MODULE_ARENA_XIANFU = 3, //仙府夺宝
	MODULE_ARENA_RANK = 4, //排位赛
	MODULE_BOSS_PERSON_BOSS = 1, //个人boss
	MODULE_BOSS_RISK_BOSS = 2, //BOSS挑战
	MODULE_BOSS_WORLD_BOSS = 3, //世界BOSS
	MODULE_EXP_QUEST = 1, //历练任务
	MODULE_EXP_ARTIFACT = 2, //神器铸造
	MODULE_CP_ALL = 1, //闯关
	MODULE_TEAMINSTANCE_EXP = 1, //经验副本
	MODULE_TEAMINSTANCE_TEAM = 2, //多人副本
	MODULE_WELFARE_MONTH = 1, //月签到
	MODULE_WELFARE_LEVEL = 2, //升级奖励
	MODULE_WELFARE_SEVEN = 3, //七日大礼
	MODULE_WELFARE_RECHARGE = 4, //充值返利
	MODULE_WELFARE_CONSUME = 5, //消费有奖
	MODULE_WELFARE_EVERYDAY = 6, //每日充值
	MODULE_OPENSERVICE_SEVEN = 1, //七日目标
	MODULE_OPENSERVICE_DRAW = 2, //开服寻宝
	MODULE_OPENSERVICE_EVERYDAY = 3, //每日礼包
	MODULE_OPENSERVICE_NEW = 4, //新手礼包
	MODULE_FIRST_RECHARGE_ALL = 1, //首冲
	MODULE_TURNTABLE_ALL = 1, //转盘
	MODULE_TEST_WORLD = 1, //世界
	MODULE_TEST_REGION = 2, //区域
	MODULE_TEST_RISK = 3, //世界冒险

};

enum MERIDIAN_EXP_SOURCE {
	MERIDIAN_EXP_SOURCE_GROUP_INSTANCE = 1, //	跨服副本
	MERIDIAN_EXP_SOURCE_TALISMAN_ZHULING = 2, //	法宝注灵
	MERIDIAN_EXP_SOURCE_WINGS_STRENGTH = 3, //	翅膀强化
};

// 活跃度类型
enum VITALITY_TYPE
{
	VITALITY_TYPE_SMELT_EQUIP = 1,		//熔炼
	VITALITY_TYPE_RES_INSTANCE = 2,		//资源副本
	VITALITY_TYPE_TRIAL_INSTANCE = 3,	//试炼塔
	VITALITY_TYPE_GROUP_INSTANCE = 4,	//多人副本
	VITALITY_TYPE_MASS_BOSS = 5,		//BOSS挑战
	VITALITY_TYPE_WORLD_BOSS = 6,		//世界BOSS
	VITALITY_TYPE_FACTION_BOSS = 7,		//家族BOSS
	VITALITY_TYPE_FACTION_TOWER = 8,	//家族远征
	VITALITY_TYPE_FACTION_DONATE = 9,	//家族贡献
	VITALITY_TYPE_DOUJIANTAI = 10,		//斗剑台
	VITALITY_TYPE_SINGLE_PVP = 11,		//排位赛
	VITALITY_TYPE_PRIVATE_BOSS = 12,	//个人boss
	VITALITY_TYPE_SHOP_BUY = 13,		//商城购买
	VITALITY_TYPE_RANK_LIKE	= 14,		//膜拜高手
	VITALITY_TYPE_DAILY_QUEST = 15,		//日常任务

	VITALITY_TYPE_EQUIPDEVELOP_STRENGTH = 16,		//装备强化
	VITALITY_TYPE_EQUIPDEVELOP_REFINE = 17,		//装备精炼
	VITALITY_TYPE_EQUIPDEVELOP_WASHATTR = 18,		//装备洗炼
	VITALITY_TYPE_WINGS_BLESS = 19,		//翅膀喂养
	VITALITY_TYPE_WINGS_STRENGTH = 20,		//翅膀强化
	VITALITY_TYPE_MOUNT_BLESS = 21,		//坐骑喂养
	VITALITY_TYPE_MOUNT_STRENGTH = 22,		//坐骑升级
	VITALITY_TYPE_MOUNT_SKILLUP = 23,		//坐骑技能升级
	VITALITY_TYPE_TALISMAN_UPGRADE = 24,		//法宝升级
	VITALITY_TYPE_ADVENTURE_QUEST = 25,		//历练任务
	VITALITY_TYPE_PLAYER_SKILLUP = 26,		//角色技能升级
	VITALITY_TYPE_ADVENTURE_SKILLUP = 27,		//神剑技能升级

	VITALITY_TYPE_EXP_INSTANCE	= 28,			//经验副本
	VITALITY_TYPE_LOCAL_3V3		= 29,			//3V3仙魔道
	VITALITY_TYPE_FACTION_MATCH		= 31,			//家族战

};

// 神剑解锁类型
enum ADVENTURE_UNLOCK
{
	ADVENTURE_UNLOCK_LIMIT_WORLDRISK = 1,		//通关挂机第N关
	ADVENTURE_UNLOCK_LIMIT_KILLMONSTER = 2,		//击杀某个怪物
	ADVENTURE_UNLOCK_LIMIT_FORCE = 3,			//战力达到N
	ADVENTURE_UNLOCK_LIMIT_LEVEL = 4,			//人物等级到N
	ADVENTURE_UNLOCK_LIMIT_WING = 5,			//翅膀到几星几阶
	ADVENTURE_UNLOCK_LIMIT_MOUNT = 6,			//坐骑到几星几阶
};
#endif