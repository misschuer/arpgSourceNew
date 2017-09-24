#ifndef _SHARED_DEF_H
#define _SHARED_DEF_H

#define MAX_MONEY 2000000000000000				//��������������������ϾͰ�Ϲ
#define MAX_MONEY_TRUE 4000000000000000			//�������.�档�����Ͳ������ϼ�
#define MAX_BUFF_DURATION	65535				//����BUFFʱ��

#define INIT_QUEST_ID 1				

#define ZHUCHENG_DITU_ID 1				//���ǵ�ͼID
#define ZHUCHENG_FUHUO_X 141				//���Ǹ����
#define ZHUCHENG_FUHUO_Y 163				//���Ǹ����

#define BORN_MAP 1001	//������ͼ
#define BORN_X 143	//��������x 
#define BORN_Y 113	//��������y
#define BORN_OR 2	//��������
#define BORN_LV 1	//�����ȼ�
#define VIP_MAX_LEVEL 10	//vip���ȼ�


#define MAX_RMB_PLAYER_LEVEL 6			//����RMB�ȼ�

//����������ö��
enum ESERVER_TYPE
{
	WORLD_SERVER_TYPE_GAME			= 0,	//��Ϸ��
	WORLD_SERVER_TYPE_PK			= 1,	//pk��
};

//�������ö��
enum EKUAFU_TYPE
{
	KUAFU_TYPE_NONE				= 0,
	KUAFU_TYPE_FENGLIUZHEN		= 1,	// ���������
	KUAFU_TYPE_XIANFU			= 2,	// ����ɸ��ᱦ
	KUAFU_TYPE_PLUNDER			= 3,	// ��������Ӷ�
	KUAFU_TYPE_GROUP_INSTANCE	= 4,	// �����Ӹ���
	MATCH_TYPE_LOCAL_SINGLE_PVP	= 5,	// ���ص���PVPƥ��
	MAX_KUAFU_TYPE,
};

//�Ϸ�Э���������
enum EMergeType
{
	MERGE_TYPE_MERGE			= 0,	//�ӷ�Ǩ�����ӵ�����
	MERGE_TYPE_GAME_TO_PK		= 1,	//��Ϸ����Pk��
	MERGE_TYPE_PK_TO_GAME		= 2,	//pk������Ϸ��
};

//�Ự����
enum ECOntextType
{
	CONTEXT_TYPE_YEYOU		= 0,		//ҳ��
	CONTEXT_TYPE_PHONE		= 1,		//����
	MAX_CONTEXT_TYPE
};

//�Ա�
enum CHAR_GENDER
{
	CHAR_GENDER_MALE			= 0,		//����
	CHAR_GENDER_FEMALE			= 1,		//Ů��
	CHAR_GENDER_NONE			= 2,		//δ֪
	MAX_CHAR_GENDER				= 3,		//����		
};

//����
enum Race_type
{
	RACE_NONE					 = 0,	//��
	RACE_STRONG					 = 1,	//׳��
	RACE_HANDSOME				 = 2,	//���� 
	RACE_LAURIE					 = 3,	//����
	RACE_BEAUTY					 = 4,	//����
};

//ͷ��
enum Head_type
{
	HEAD_NONE				= 0,	//��
	HEAD_STRONG				= 1,	//׳��
	HEAD_HANDSOME			= 2,	//���� 
	HEAD_LAURIE				= 3,	//����
	HEAD_BEAUTY				= 4,	//����	
	HEAD_TOTAL				= 4,  /*ͷ�����*/
};

//��������
enum Resurrection_Type
{
	RESURRECTION_IN_SITU	= 0, //ԭ�ظ���
	RESURRECTION_SPAWNPOINT = 1, //����㸴��
	RESURRPCTION_FREE		= 2, //��Ѹ���
	RESURRPCTION_MONEY		= 3, //Ԫ������
	RESURRPCTION_TIME		= 4, //��ʱ����
	RESURRPCTION_HUANHUNDAN	= 5, //���굤����
	MAX_RESURRECTION_TYPE,
};

//GM�ȼ�
enum GM_LEVEL
{
	GM_LEVEL_0	= 0,	//��ͨ���
	GM_LEVEL_1	= 1,	//��ͨGM
	GM_LEVEL_2	= 2,	//�߼�GM
	GM_LEVEL_3	= 3,	//�ռ�GM
};

//��Ϸ�����־
enum GameObject_Flags
{
	GO_FLAG_DYNAMIC = 0,	//�Ƿ�̬����,�ɲ����ɵ�ͼˢ������
	GO_FLAG_TELE	= 1,	//�Ƿ��͵����
	GO_FLAG_QUEST	= 2,	//�Ƿ��������
	GO_FLAG_LOOT	= 3,	//�Ƿ�ս��Ʒ	
	GO_FLAG_GEAR	= 10,	//�Ƿ���أ������ӣ��ŵ�

	GO_FLAG_UNUSE	= 4,	//���ɱ�ʹ��
	GO_FLAG_FOREVER	= 5,	//������ʹ��

	GO_FLAG_USEMODE = 8,	//ʹ�÷�ʽ,��Ҫ������
	GO_FLAG_CARTON	= 9,	//�ͻ���ģ����ʧ

	GO_FLAG_REBORN	= 11,	//�Ƿ������ (���������, GO_FLAG_FOREVER��������)

	GO_FLAG_SCRIPT	= 12,	//�Ƿ�ʹ�ýű�
	GO_FLAG_GET_ITEM_NOTICE = 13,		//ʰ����Ʒ�Ƿ���Ҫ����
};

//�����ͼ״̬
enum World_Map_State
{
	WORLD_MAP_DEFAULT			= 0,	//���ִ�
};

//��ö��
enum TypeID
{
	TYPEID_OBJECT			= 0,		//����0����û�õ�
	TYPEID_UNIT				= 1,		//���ﾫ�飬����NPC�������ȡ�����
	TYPEID_PLAYER			= 2,		//��Ҿ���
	TYPEID_GAMEOBJECT		= 3,		//��Ϸ������
	MAX_CLIENT_OBJECT_TYPES
};

//��ƷƷ��
enum Item_Qual
{
	ITEM_QUAL_WHITE		= 0,		//��װ
	ITEM_QUAL_GREEN		= 1,		//��װ
	ITEM_QUAL_BLUE		= 2,		//��װ
	ITEM_QUAL_PURPLE	= 3,		//��װ
	ITEM_QUAL_ORANGE	= 4,		//��װ
	ITEM_QUAL_RED		= 5,		//��װ
	MAX_QUAL
};

//����ģʽ
enum Attack_Mode
{
	ATTACK_MODE_PEACE		= 0,	//��ƽ������˵���㶮��
	ATTACK_MODE_TEAM		= 1,	//��ӣ����Կ�������������
	ATTACK_MODE_RED			= 2,	//���������Կ�����
	ATTACK_MODE_ALL			= 3,	//ȫ�壬�����Լ���˭�����Կ�
	ATTACK_MODE_FACTION		= 4,	//����ģʽ
	ATTACK_MODE_BANG		= 5,	//����ģʽ
	MAX_ATTACK_MODE,
};

//��޼�������
enum ReactStates
{
	REACT_PASSIVE			= 0,		//��������
	REACT_DEFENSIVE			= 1,		//����
	REACT_AGGRESSIVE		= 2,		//��������,
	REACT_AGGRESSIVE_UNIT	= 3,		//������������
	REACT_AGGRESSIVE_PLAYER = 4,		//�����������
	MAX_REACT_STATES
};

//�Ϸ���������
enum MERGE_OPT_TYPE
{
	MERGE_OPT_TYPE_INIT				= 0,		//��ʼ״̬
	MERGE_OPT_TYPE_SAVE_DB			= 1,		//���ݱ������
	MERGE_OPT_TYPE_TARGET_SERVER_OK	= 2,		//Ŀ�������׼�����
	MERGE_OPT_TYPE_END				= 3,		//��������
	MERGE_OPT_TYPE_SAVE_ING			= 4,		//���ݱ�����
};
//�Ϸ�����������
enum MERGE_SERVER_TYPE
{
	MERGE_SERVER_TYPE_ORIGINAL	= 1,		//ԭʼ������
	MERGE_SERVER_TYPE_TARGAT	= 2,		//Ŀ�������
};

//�ص���������
enum BACK_OPT_TYPE
{
	BACK_OPT_TYPE_INIT				= 0,		//��ʼ״̬
	BACK_OPT_TYPE_SUCCESS			= 1,		//�ɹ�
};

//��Ʒ������
enum ITEM_BIND_TYPE
{
	ITEM_BIND_NONE	= 0,		//�ǰ�
	ITEM_BIND_USE	= 1,		//ʹ�ð�
	ITEM_BIND_GET	= 2,		//��ð�
};

//���������Ķ����������
enum ITEM_GIFT_GET_TYPE
{
	ITEM_GIFT_GET_NONE	= 0,	//�Ǳ���
	ITEM_GIFT_GET_MUST	= 1,	//�����õ�
};

//�������״̬
enum EPlayerOnlineState
{
	PLAYER_ONLINE_STATE_OUTLINE	= 0,	//����
	PLAYER_ONLINE_STATE_ONLINE	= 1,	//����
};

//�����ƶ�ģʽ
enum MovementGeneratorType
{
	DISAPPEAR_MOTION_TYPE			= 9999,	//��ʧ
	IDLE_MOTION_TYPE				= 0,	//����
	RANDOM_MOTION_TYPE				= 1,	//���
	WAYPOINT_MOTION_TYPE			= 2,	//��·����
	TARGET_MOTION_TYPE				= 3,	//Ŀ������
	HOME_MOTION_TYPE				= 4,	//�ؼ�
	CONFUSED_MOTION_TYPE			= 5,	//����
	FLEEING_MOTION_TYPE				= 6,	//�ӱ�
	FOLLOW_MOTION_TYPE				= 7,	//����
	FOLLOW_INLINE_MOTION_TYPE		= 8,	//ֱ�߸���
	WAYFINDING_MOTION_TYPE			= 9,	//Ѱ·����
	WAYFINDING_ATTACK_MOTION_TYPE	= 10,	//Ѱ·׷ɱ
	MERCENARY_MOTION_TYPE			= 11,	//Ӷ��
	WAYFINDDST_MOTION_TYPE			= 12,	//Ŀ�ĵ�����
	DEADLINE_MOTION_TYPE			= 13,	//������ʧ

	MAX_MOTION_TYPE
};

//����Ŀ������ �Լ�,�ѷ�,�з�,ȫ��
enum Spell_Target_Type
{
	TARGET_TYPE_ONESELF   = 0,
	TARGET_TYPE_FRIENDLY  = 1,
	TARGET_TYPE_ENEMY     = 2,
	TARGET_TYPE_ALL		  = 3,
	TARGET_TYPE_POINT	  = 4,		//�Ե��ͷż��� 
	TARGET_TYPE_SELFPOINT = 5,		//���Լ��ĵ��ͷ�
	TARGET_TYPE_CREATURE  = 6,		//�Թ�����Ч������������ȣ�
	TARGET_TYPE_PLAYER	  = 7,		//�������Ч
};

//����״̬
enum TRADE_STATE_TYPE
{
	TRADE_STATE_TYPE_FREE				= 0,	//����״̬
	TRADE_STATE_TYPE_APPLY				= 1,	//����״̬
	TRADE_STATE_TYPE_EXECUTION			= 2,	//ִ��״̬
	TRADE_STATE_TYPE_PUT_ITEM_END		= 3,	//ȷ����Ʒ���
	TRADE_STATE_TYPE_WAIT_FINISH 		= 4,	//�ȴ����״̬
};

//���׵�����
enum TRADE_TYPE
{
	TRADE_TYPE_TRADE	= 0,					//����
	TRADE_TYPE_STALL	= 1,					//��̯
};


//ͨ��ģ��id�ƶ���Ʒ��ָ���İ�������Ӧ��λ���ϣ������
enum MOVE_ITEM_RESULT
{
	MOVE_ITEM_FAIL		= 0,	//ʧ��
	MOVE_ITEM_SUC		= 1,	//�ɹ�
	MOVE_ITEM_HAVE_BIND = 2,	//�����󶨵�
	MOVE_ITEM_NOT_BIND	= 3,	//�������󶨵�
};

//ɾ����Ʒ���
enum SUB_ITEM_RESULT
{
	SUB_ITEM_FAIL			= 0,					//ʧ��
	SUB_ITEM_HAVE_BIND		= 1,					//�����󶨵�
	SUB_ITEM_NOT_BIND 		= 2,					//�������󶨵�
	SUB_ITEM_HAVE_FAILTIME  = 3,					//������ʱ
};

//��Ʒ���ݴ���״̬
enum ITEM_SAVE_MODE
{
	ITEM_SAVE_MODE_INSERT = 0,		//����
	ITEM_SAVE_MODE_UPDATE = 1,		//����
};

//Ԫ����ֵ����
enum GOLD_INGOT_RECHARGE_TYPE
{
	GOLD_INGOT_RECHARGE_NORMAL	= 1,	//����ģʽ
	GOLD_INGOT_RECHARGE_HANDSEL	= 2,	//����ģʽ
	GOLD_INGOT_RECHARGE_SUB		= 3,	//�۷�ģʽ
	GOLD_INGOT_RECHARGE_HAND	= 4,	//�ֶ�ģʽ
	MAX_GOLD_INGOT_RECHARGE_TYPE,
};

//��ֵ״̬����
enum RECHAGRE_STATUS_TYPE
{
	RECHARGE_STATUS_TYPE_START		= 0,		//��ʼ��
	RECHARGE_STATUS_TYPE_RUNMING	= 1,		//������
	RECHARGE_STATUS_TYPE_END		= 2			//����
};

//���˵�״̬����
enum KICKING_STATUS
{
	KICKING_STATUS_START		=0,		//��ʼ��
	KICKING_STATUS_END			=1,		//����
};

//��ŵ�״̬����
enum LOCKING_STATUS
{
	LOCKING_STATUS_START		=0,		//��ʼ��
	LOCKING_STATUS_RUNNING		=1,		//�����
	LOCKING_STATUS_END			=2,		//����
};

//�����״̬����
enum SYSTEM_NOTICE_STATUS
{
	SYSTEM_NOTICE_STATUS_START		= 0,	//��ʼ״̬
	SYSTEM_NOTICE_STATUS_RUNNING	= 1,	//������
	SYSTEM_NOTICE_STATUS_END		= 2,	//����
	SYSTEM_NOTICE_STATUS_DELETE		= 3,	//��ɾ��
	SYSTEM_NOTICE_STATUS_GARBAGE	= 4,	//��ɾ��
};

//�����״̬����
enum GIFT_PACKS_STATUS
{
	GIFT_PACKS_STATUS_START		= 0,	//��ʼ
	GIFT_PACKS_STATUS_SENDING	= 1,	//������
	GIFT_PACKS_STATUS_OK		= 2,	//�ѷ���
	GIFT_PACKS_STATUS_END		= 3,	//�ѽ���
};

//�����������
enum GIFT_PACKS_AUDIENCE_TYPE
{
	GIFT_PACKS_AUDIENCE_TYPE_ONE				= 1,		//����������粹�������
	GIFT_PACKS_AUDIENCE_TYPE_ALL				= 2,		//ȫ��ͬ־�����
	GIFT_PACKS_AUDIENCE_TYPE_ALL_ONLINE			= 3,		//ȫ���������
};

//�����������
enum GIFT_PACKS_OPERATION_TYPE
{
	GIFT_PACKS_OPER_TYPE_RECEIVE	= 0,			//��ȡ
	GIFT_PACKS_OPER_TYPE_READ		= 1,			//�Ѷ�
	GIFT_PACKS_OPER_TYPE_DELETE		= 2,			//ɾ��
};

//����״̬
enum GAG_STATUS
{
	GAG_STATUS_START		= 0,		//��ʼ��
	//GAG_STATUS_OFFLINE		= 1,		//�������
	GAG_STATUS_END			= 1,		//�ѽ���
};

//����GM���״̬
enum GM_LEVEL_TABLE_STATUS
{
	GM_LEVEL_TABLE_START	= 0,		//��ʼ��
	GM_LEVEL_TABLE_END		= 1,		//��ִ��
};

//��������
enum NOTICE_TYPE
{
	NOTICE_TYPE_SCROLL		= 1,		//��������
	NOTICE_TYPE_PROMPT		= 2,		//�̶�������������ʾ
	NOTICE_TYPE_FIXED		= 3,		//�̶���ʾ

	MAX_NOTICE_TYPE			= 10,		//Ԥ��10��
};

//��������
enum CHAT_TYPE
{
	CHAT_TYPE_SYSTEM		= 0,		//ϵͳ
	CHAT_TYPE_WORLD			= 1,		//����
	CHAT_TYPE_FACTION		= 2,		//����
	CHAT_TYPE_CURRENT		= 3, 		//��ǰ(����)
	CHAT_TYPE_HORM			= 4,		//����
	CHAT_TYPE_GROUP			= 5,		//����
	CHAT_TYPE_WHISPER		= 6,		//˽��
	MAX_CHAT_TYPE
};

//ƽ̨ö��
#define PLATFORM_GAME2	   "2"	//������
#define PLATFORM_QQ        "360"  //��ѶQQ
#define PLATFORM_NULL	 "9999"		//����Ҫpost��ƽ̨

//post�Ķ�������
enum EPostType
{
	POST_TYPE_NONE			= 0,
	POST_TYPE_CHAT			= 1,			//����
	POST_TYPE_UPGRADE		= 2,			//�û�����
	MAX_POST_TYPE
};

//��¼���ļ�����־����
enum LOG_FILE_TYPE
{
	LOG_FILE_TYPE_GAME_BUY				= 0,	//��¼�û�����Ϸ�ڹ�����Ϊ
	LOG_FILE_TYPE_GAME_SELL				= 1,	//��¼�û�����Ϸ�ڳ�����Ϊ
	LOG_FILE_TYPE_RECHARGE				= 2,	//��¼�û���ֵ��Ϊ
	LOG_FILE_TYPE_SHOP_BUY				= 3,	//��¼�û����̳ǵĹ�����Ϊ
	LOG_FILE_TYPE_ITEM_USE				= 4,	//��¼�û�ʹ���̳���Ʒ��Ϊ
	LOG_FILE_TYPE_DEAL					= 5,	//��¼�û��Ľ�����Ϊ
	LOG_FILE_TYPE_YB_INCOME				= 6,	//��¼����Ԫ������
	LOG_FILE_TYPE_ITEM_INCOME			= 7,	//��¼�����������
	LOG_FILE_TYPE_YB_EXPEND				= 8,	//��¼����Ԫ������
	LOG_FILE_TYPE_LOGIN					= 9,	//��¼�û���¼��Ϊ
	LOG_FILE_TYPE_LOGOUT				= 10,	//��¼�û��ǳ���Ϊ
	LOG_FILE_TYPE_CREATE_ROLE			= 11,	//��¼�û�������ɫ��Ϊ
	LOG_FILE_TYPE_DEATH					= 12,	//��¼�û���ɫ�����¼�
	LOG_FILE_TYPE_ACCEPT_TASK			= 13,	//��¼�û������������Ϊ
	LOG_FILE_TYPE_TASK					= 14,	//��¼�û�����������Ϊ
	LOG_FILE_TYPE_UPGRADE				= 15,	//��¼�û������¼�
	LOG_FILE_TYPE_GOLD					= 16,	//��¼�û����������Ϊ
	LOG_FILE_TYPE_MAP					= 17,	//��¼�û��л���ͼ����Ϊ
	LOG_FILE_TYPE_LONGER				= 18,	//��¼�û��Ĺһ���Ϊ
	LOG_FILE_TYPE_MONSTER				= 19,	//��¼�û���ֵ���Ϊ
	LOG_FILE_TYPE_TRANSCRIPT			= 20,	//��¼�û��򸱱�����Ϊ
	LOG_FILE_TYPE_ONLINE				= 21,	//��¼��������
	LOG_FILE_TYPE_GAME_ENTER			= 22,	//��¼�û�������Ϸ������
	LOG_FILE_TYPE_ITEM_LOG				= 23,	//��¼���ߵ�������Ϊ
	LOG_FILE_TYPE_CHAT					= 24,	//��¼��������¼
	LOG_FILE_TYPE_RELIVE				= 25,	//��¼��Ҹ���
	LOG_FILE_TYPE_BIND_GOLD				= 26,	//��¼��ҵİ�Ԫ����Ϊ
	LOG_FILE_TYPE_NEW_CARD_RECEIVE		= 27,	//��¼�û���ȡ���ֿ�����Ϊ
	LOG_FILE_TYPE_STALL					= 28,	//��¼��̯��Ϊ
	LOG_FILE_TYPE_WANTED_PACKET			= 29,	//��¼��ͨ������ҵ����а���¼
	LOG_FILE_TYPE_ERROR_PACKET			= 30,	//��¼��ȡ�û���Ϣ����İ�
	LOG_FILE_TYPE_CHOOSE_FACTION		= 31,	//��¼���ѡ����Ӫ�����
	LOG_FILE_TYPE_ACTIVITY_INFO			= 32,	//��¼��Ӫ�������Ϣ
	LOG_FILE_TYPE_ABNORMAL_PACKETS		= 33,	//��¼��Ϊ�쳣�����ߵ���ҵ���Ϊ
	LOG_FILE_TYPE_CLIENT_INFO			= 34,	//��¼��ҿͻ�����Ϣ
	LOG_FILE_TYPE_GIFTMONEY_BUY			= 35,	//��¼���������ĵ���Ϊ
	LOG_FILE_TYPE_GIFTMONEY_INCOME		= 36,	//��¼�û�����õ���Ϊ
	LOG_FILE_TYPE_ATTACK_PACKET			= 37,	//��¼������
	LOG_FILE_TYPE_FORMAT_LOG			= 38,	//��¼���߰�����Զ�����־
	LOG_FILE_TYPE_CLIENT_LOG			= 39,	//��¼�ͻ�����־
	LOG_FILE_TYPE_FORGE_LOG				= 40,	//��¼������־
	LOG_FILE_TYPE_OBJECT_LOSS			= 41,	//1001��־
	MAX_LOG_FILE_TYPE
};

enum SkillEffectType
{
	SKILL_EFFECT_TYPE_NORMAL			= 0,	//��ͨЧ������
	SKILL_EFFECT_TYPE_HUIXUE1			= 1,	//�з���Ѫ, �Լ���Ѫ
	SKILL_EFFECT_TYPE_ROAR				= 2,	//ս��
	SKILL_EFFECT_TYPE_BLADE_STORM		= 3,	//���з籩 (ÿ�������Ѫ������ô��?)
	SKILL_EFFECT_TYPE_HEAL				= 4,	//����֮Ȫ
	SKILL_EFFECT_TYPE_SNOW_STORM		= 5,	//����ѩ
	SKILL_EFFECT_TYPE_LOADED			= 99,	//����ʱ�䵽�ͷż���
};

//��¼��Ѷ�ļ�����־����
enum LOG_FILE_TENCENT_TYPE
{
	LOG_FILE_TENCENT_USER				= 0,	//�û���
	LOG_FILE_TENCENT_PLAYER				= 1,	//��ɫ��
	LOG_FILE_TENCENT_RECHAGRE			= 2,	//��ֵ��
	LOG_FILE_TENCENT_UPGRADELOG			= 3,	//������־
	LOG_FILE_TENCENT_NEWTASK			= 4,	//������־
	LOG_FILE_TENCENT_LOGIN				= 5,	//��½��־
	LOG_FILE_TENCENT_OFFLINE			= 6,	//������־
	LOG_FILE_TENCENT_ONLINE				= 7,	//����ͳ����־
	LOG_FILE_TENCENT_MONEYLOG			= 8,	//�������

	MAX_LOG_FILE_TENCENT_TYPE
};

// ����������
enum DEAD_PLACE_TYPE
{
	DEAD_PLACE_TYPE_FIELD			= 1,		// Ұ������
	DEAD_PLACE_TYPE_XIANFU			= 2,		// �ɸ��ᱦ����
	DEAD_PLACE_TYPE_GROUP_INSTANCE	= 3,		// ��Ӹ�������
};

//�������쳣����
enum ACCACK_PACKET_TYPE
{
	ACCACK_PACKET_TYPE_UNPACK	= 0,	//���ʧ��
	ACCACK_PACKET_TYPE_DATA		= 1,	//�����쳣
	ACCACK_PACKET_TYPE_ORDER	= 2,	//��˳���쳣
	ACCACK_PACKET_TYPE_DISCARD	= 3,	//�����İ���
	MAX_ACCACK_PACKET_TYPE
};

//������Ʒ
typedef struct deal_goods_t
{
	char guid[50];		//װ��ID
	uint32 entryid;		//ģ��ID
	uint32 goodtype;	//����
	uint32 num;			//����

}deal_goods;

//����Ԫ���������
enum LOG_YB_INCOME_TYPE
{
	LOG_YB_INCOME_TYPE_ACTIVITY		= 0,		//�����
	LOG_YB_INCOME_TYPE_RECHARGE		= 1,		//��ֵ����
	LOG_YB_INCOME_TYPE_USE_ITEM		= 2,		//ʹ�õ���
	LOG_YB_INCOME_TYPE_GIFT_PACKS	= 3,		//�������
};
 
//���߲�������
//NOTICE ��������Զ�����ߵ���Դ���ͻ��˵���ʾreason�Ƕ�Ӧ��
enum LOG_ITEM_OPER_TYPE
{
	//���
	LOG_ITEM_OPER_TYPE_ACTIVITY				= 0,		//��������
	LOG_ITEM_OPER_TYPE_RECHARGE				= 1,		//��ֵ���ͻ��
	LOG_ITEM_OPER_TYPE_GIFT_PACKS			= 2,		//����������
	LOG_ITEM_OPER_TYPE_QUEST				= 3,		//������ɽ������
	LOG_ITEM_OPER_TYPE_NEWPLAYER			= 4,		//����������
	LOG_ITEM_OPER_TYPE_OPEN_ITEM			= 5,		//ʹ�õ��߻��
	LOG_ITEM_OPER_TYPE_LOOT					= 6,		//ս��Ʒ
	LOG_ITEM_OPER_TYPE_GM_COMMAND			= 7,		//GM������
	LOG_ITEM_OPER_TYPE_ITEM_BLEND			= 8,		//��Ʒ�ϳɻ��
	LOG_ITEM_OPER_TYPE_SEVEN_DAY_GIFT		= 9,		//�������	
	LOG_ITEM_OPER_TYPE_JHM_GIFT				= 10,		//���������
	LOG_ITEM_OPER_TYPE_OPEN_BOX				= 11,		//��������
	LOG_ITEM_OPER_TYPE_FUBEN_EWAIJINAGLI	= 12,		//�������⽱��
	LOG_ITEM_OPER_TYPE_CAPTURE_YAOHUN		= 13,		//��׽������
	LOG_ITEM_OPER_TYPE_FSZL_EWAIJINAGLI		= 14,		//����֮·����
	LOG_ITEM_OPER_TYPE_PRESTIGE				= 15,		//��Ծ����ȡ���
	LOG_ITEM_OPER_TYPE_TIANDILINGKUANG		= 16,		//��������ȡ���
	LOG_ITEM_OPER_TYPE_PANTAOYUAN			= 17,		//���԰����
	LOG_ITEM_OPER_TYPE_WABAO				= 18,		//�ڱ����
	LOG_ITEM_OPER_TYPE_HONGYAN				= 19,		//�����¼����
	LOG_ITEM_OPER_TYPE_FORGE_DECOMPOSE		= 20,		//����ֽ���
	LOG_ITEM_OPER_TYPE_WORLD_BOSS_ROLL		= 21,		//����BOSSroll��
	LOG_ITEM_OPER_TYPE_VIP_INSTANCE_REWARD	= 22,		//vip��������
	LOG_ITEM_OPER_TYPE_TRIAL_INSTANCE_REWARD= 23,		//����������
	LOG_ITEM_OPER_TYPE_ACHIEVE				= 24,		//�ɾͽ���
	LOG_ITEM_OPER_TYPE_SHOUCHONG			= 25,		//�׳佱��
	LOG_ITEM_OPER_TYPE_CHECKIN				= 26,		//ÿ��ǩ������
	LOG_ITEM_OPER_TYPE_GETBACK				= 27,		//�һش�������
	LOG_ITEM_OPER_TYPE_TOTAL_CHECKIN		= 28,		//ÿ���ۻ�ǩ������
	LOG_ITEM_OPER_TYPE_WELFARE_LEVEL		= 29,		//�����ȼ�����
	LOG_ITEM_OPER_TYPE_3V3_KUAFU			= 30,		//3v3�������
	LOG_ITEM_OPER_TYPE_INSTANCE_SWEEP		= 31,		//��������ɨ������
	LOG_ITEM_OPER_TYPE_XIANFU				= 32,		//�ɸ��ᱦ�������
	LOG_ITEM_OPER_TYPE_DOUJIAN_FIRST_REWARD	= 33,		//����̨��ʤ����
	LOG_ITEM_OPER_TYPE_DOUJIAN_COMBAT_REWARD= 34,		//����̨��ʤ����
	LOG_ITEM_OPER_TYPE_CULTIVATION_REWARD	= 35,		//����������
	LOG_ITEM_OPER_TYPE_CULTIVATION_PLUNDER_REWARD	= 36,		//�������Ӷά��
	LOG_ITEM_OPER_TYPE_LOGIN_ACTIVITY_REWARD	= 37,		//��¼������
	LOG_ITEM_OPER_TYPE_GROUP_INSTANCE			= 38,		//��Ӹ����������

	LOG_ITEM_OPER_TYPE_XIANFU_PRACTISE		= 40,		//�ɸ��ᱦ���齱��
	LOG_ITEM_OPER_TYPE_FACTION_BOSS			= 41,		//����boss����

	LOG_ITEM_OPER_TYPE_OFFLINE				= 42,		//���߽���
	LOG_ITEM_OPER_TYPE_STOREHOUSE			= 43,		//���ɱ���

	LOG_ITEM_OPER_TYPE_MASS_BOSS			= 44,		//ȫ��BOSS

	//����
	LOG_ITEM_OPER_TYPE_SHOP_BUY				= 45,		//���̳�������

	LOG_ITEM_OPER_TYPE_FACTION_BOSSDEFENSE	= 46,		//����������ս��ɱ����
	LOG_ITEM_OPER_TYPE_FACTION_TOWER		= 47,		//�����޾�Զ������

	LOG_ITEM_OPER_TYPE_SINGLE_PVP			= 48,		//����PVP
	LOG_ITEM_OPER_TYPE_ACT_LOTTERY			= 49,		//�齱�
	LOG_ITEM_OPER_TYPE_ACT_DAILYGIFT		= 50,		//ÿ������
	LOG_ITEM_OPER_TYPE_ACT_RANK				= 51,		//ÿ�����л
	LOG_ITEM_OPER_TYPE_ACT_LIMITGIFT		= 52,		//�޶�����

	LOG_ITEM_OPER_TYPE_RECHARGE_REWARD		= 53,		//��ֵ����
	LOG_ITEM_OPER_TYPE_CONSUME_REWARD		= 54,		//���ѷ���


	LOG_ITEM_OPER_TYPE_NPC_BUY				= 102,		//��NPC������
	LOG_ITEM_OPER_TYPE_BIND_SHOP_BUY		= 103,		//�Ӱ��̳ǹ�����
	LOG_ITEM_OPER_TYPE_REPURCHASE			= 104,		//��NPC�ع���Ʒ���
	LOG_ITEM_OPER_TYPE_ACTI_BUY				= 105,		//�����
	LOG_ITEM_OPER_TYPE_XIANFU_BUY			= 106,		//�����ɸ�����ȯ

	//����
	LOG_ITEM_OPER_TYPE_NPC_SELL				= 200,		//���۸�NPC
	LOG_ITEM_OPER_TYPE_DEL_FAILTIME			= 201,		//������ʱ��Ʒ
	LOG_ITEM_OPER_TYPE_USE					= 202,		//ʹ����Ʒ
	LOG_ITEM_OPER_TYPE_DISPOSE				= 203,		//������Ʒ
	LOG_ITEM_OPER_TYPE_HEAL					= 204,		//��ҩ

	//����
	LOG_ITEM_OPER_TYPE_TRADE_GET			= 301,		//���׻��
	LOG_ITEM_OPER_TYPE_TRADE_PAY			= 302,		//���׸���
	LOG_ITEM_OPER_TYPE_STALL_OPEN			= 303,		//��̯
	LOG_ITEM_OPER_TYPE_STALL_CLOSE			= 304,		//��̯
	LOG_ITEM_OPER_TYPE_STALL_BUY			= 305,		//̯λ����

	LOG_ITEM_OPER_TYPE_LINGDI_XUANSHANG		= 306,		//�������
	LOG_ITEM_OPER_TYPE_LINGDI_MIJING		= 307,		//����ؾ�

	LOG_ITEM_OPER_TYPE_WUJIANG_ZHENGZHAN	= 308,		//�佫��ս

	LOG_ITEM_OPER_TYPE_KAOZHUANGYUAN		= 309,		//��״Ԫ

	LOG_ITEM_OPER_TYPE_MONEYTREE_GIFT		= 310,		//ҡǮ�����

};

//��̨���ұ仯����ö��
enum HT_MONEY_CHANGE_TYPE
{
	HT_MONEY_CHANGE_TYPE_RECHARGE		= 1,	//��ֵ
	HT_MONEY_CHANGE_TYPE_CONSUMPTION	= 2,	//����
	HT_MONEY_CHANGE_TYPE_SUB			= 3,	//����Ա�۳�
	HT_MONEY_CHANGE_TYPE_REWARD			= 4,	//����
	HT_MONEY_CHANGE_TYPE_REBATE			= 5,	//����
	HT_MONEY_CHANGE_TYPE_TRADING		= 6,	//����
};

//���ұ仯ԭ������
enum MONEY_CHANGE_TYPE
{
	MONEY_CHANGE_TYPE_CHARGE						= 0,	//��ҳ�ֵ
	MONEY_CHANGE_TYPE_STORE_BUY						= 1,	//�̵깺��
	MONEY_CHANGE_TYPE_MALL_BUY						= 2,	//�̳ǹ���
	MONEY_CHANGE_TYPE_STALL_SALE					= 3,	//̯λ����
	MONEY_CHANGE_TYPE_TRADE							= 4,	//��ҽ���
	MONEY_CHANGE_MAIL								= 5,	//�ʼ�
	MONEY_CHANGE_QUEST								= 6,	//������
	MONEY_CHANGE_DEAD								= 7,	//��������
	MONEY_CHANGE_RIHUAN								= 8,	//�ջ�
	MONEY_CHANGE_USE_ITEM							= 9,	//ʹ����Ʒ����
	MONEY_CHANGE_GIFT_PACKS							= 10,	//ϵͳ�������
	MONEY_CHANGE_NPC_SELL							= 11,	//NPC����
	__MONEY_CHANGE_ITEM_REPAIR						= 12,	//Ԥ��
	__MONEY_CHANGE_ITEM_APPRAISAL					= 13,	//Ԥ��
	MONEY_CHANGE_NPC_REPURCHASE						= 14,	//NPC�ع�
	MONEY_CHANGE_GM_COMMAND							= 15,	//GM�в�����
	MONEY_CHANGE_CREATE_FACTION						= 16,	//��������
	MONEY_CHANGE_WAREHOUSE_HANLD					= 17,	//�ֿ����
	MONEY_CHANGE_SELECT_LOOT						= 18,	//ս��Ʒ
	MONEY_CHANGE_ACTIVITY							= 19,	//�����
	MONEY_CHANGE_TYPE_CHARGE_2						= 20,	//��ֵ��������
	MONEY_CHANGE_TYPE_CHARGE_3						= 21,	//����Ա�۳�
	MONEY_CHANGE_TYPE_CHARGE_4						= 22,	//�ֶ�����
	MONEY_CHANGE_USE_LABA							= 23,	//ʹ������
	MONEY_CHANGE_BAG_EXTENSION						= 24,	//������չ
	MONEY_CHANGE_ITEM_BLEND							= 25,	//��Ʒ�ϳ�����ͭǮ
	MONEY_CHANGE_SEVEN_DAY_GIFT						= 26,	//�������
	MONEY_CHANGE_CLEAR_PK_VALUE						= 27,	//ʹ��Ԫ��ϴ��
	MONEY_CHANGE_JHM_REWARD							= 28,	//�����뽱��
	MONEY_CHANGE_ONLINE_GIFT						= 29,	//ÿ�����߽���
	MONEY_CHANGE_SPELL_UP							= 30,   //��������
	MONEY_CHANGE_USE_BOX							= 31,	//ʹ�ñ�������
	MONEY_CHANGE_BOX_OPEN							= 32,	//��������
	MONEY_CHANGE_BOX_RANDOM							= 33,	//�������������
	MONEY_CHANGE_JINGJIE							= 34,	//������������
	MONEY_CHANGE_SHENBING_BUY						= 35,	//�������
	MONEY_CHANGE_ATUO_GOLD_RESPAWN					= 36,	//Ԫ������
	MONEY_CHANGE_FUBEN_KILLALL						= 37,	//����ȫͼ��ɱ����
	MONEY_CHANGE_FUBEN_EWAI							= 38,	//�������⽱��
	MONEY_CHANGE_FUBEN_BUY							= 39,	//���򸱱���������
	MONEY_CHANGE_FSZL_REWARD						= 40,	//����֮·����
	MONEY_CHANGE_PRESTIGE							= 41,	//��Ծ��
	MONEY_CHANGE_PANTAO_CAIJI						= 42,	//�ɼ���һ��
	MONEY_CHANGE_LINGKUANG_CAIJI					= 43,	//�ɼ������	
	MONEY_CHANGE_QIYU_ZHUOYAO						= 44,	//��׽��������
	MONEY_CHANGE_RESET_FORGE_ADD					= 45,	//���ö���ӳ�ʱ��
	MONEY_CHANGE_WABAO								= 46,	//�ڱ����
	MONEY_CHANGE_HONGYAN_BUY_HUOLI					= 47,	//���չ������
	MONEY_CHANGE_HONGYAN_SHIJIAN					= 48,	//�����¼����
	MONEY_CHANGE_HONGYAN_BUY_FASHION				= 49,	//���չ���ʱװ
	MONEY_CHANGE_FORGE_STRENG						= 50,	//����ǿ��
	MONEY_CHANGE_FORGE_GEM							= 51,	//��ʯ
	MONEY_CHANGE_LINGDI_ZHAOMU						= 52,	//�����ļ
	MONEY_CHANGE_LINGDI_XUANSHANG					= 53,	//�������
	MONEY_CHANGE_LINGDI_MIJING						= 54,	//����ؾ�
	MONEY_CHANGE_WUJIANG_REFRESH_PUB				= 55,	//Ԫ��ˢ�¾ƹ��佫
	MONEY_CHANGE_FENGLIUZHEN_PUB_AUCTION			= 56,	//������ƹݾ���
	MONEY_CHANGE_WUJIANG_QINGJIU					= 55,	//Ԫ������佫
	MONEY_CHANGE_LINGDI_ZHENGBING					= 56,	//�������
	MONEY_CHANGE_FENGLIUZHEN_ZHUANPAN_ENTER			= 57,	//������ת�̽�ȥ����
	MONEY_CHANGE_USE_SPELL							= 58,	//ʹ�ü���
	MONEY_CHANGE_UP_ASSISTSPELL						= 59,	//������������
	MONEY_CHANGE_LINGDI_BUY_BINGLI					= 60,	//��������������
	MONEY_CHANGE_WUJIANG_ZHENGZHAN					= 61,	//�佫��ս
	MONEY_CHANGE_BUY_JUNLLING						= 62,	//�������
	MONEY_CHANGE_SELL_WUJIANG_EQUIP					= 63,	//�����佫װ��
	MONEY_CHANGE_FENGLIUZHEN_KAOZHUANGYUAN			= 64,	//��״Ԫ����
	MONEY_CHANGE_ZHUBO_SEND_GIFTS					= 65,	//������������
	MONEY_CHANGE_ZHUBO_GRAB_SOFA					= 66,	//������ɳ��
	MONEY_CHANGE_RAISE_MOUNT						= 67,	//��������
	MONEY_CHANGE_ILLUSION							= 68,	//����û�
	MONEY_CHANGE_BIND_INGOT_NOT_ENOUGH				= 69,	//������߰�����������Ԫ��
	MONEY_CHANGE_ACTIVE_SPELL						= 70,	//�����
	MONEY_CHANGE_BUY_VIP_INSTANCE					= 71,	//����VIP�����������
	MONEY_CHANGE_BUY_HP_ITEM						= 72,	//�����ѪҩƷ
	MONEY_CHANGE_RESET_TRIAL						= 73,	//����������
	MONEY_CHANGE_SOCIAL_GIFT						= 74,   //������������
	MONEY_CHANGE_FACTION_DONATION					= 75,   //���ɾ���
	MONEY_CHANGE_FACTION_SHOP						= 76,	//�����̵�
	MONEY_CHANGE_WORLD_BOSS_ROLL					= 77,	//����BOSSroll��
	MONEY_CHANGE_VIP_INSTANCE_REWARD				= 78,	//VIP��������
	MONEY_CHANGE_TRIAL_INSTANCE_REWARD				= 79,	//����������
	MONEY_CHANGE_WELF_ACTIVE_GETBACK				= 80,	//������һؽ���
	MONEY_CHANGE_SHOUCHONG							= 81,	//�׳影��
	MONEY_CHANGE_CHECKIN							= 82,	//ÿ��ǩ������
	MONEY_CHANGE_TOTAL_CHECKIN						= 83,	//ÿ���ۻ�ǩ������
	MONEY_CHANGE_WELFARE_LEVEL						= 84,	//�ȼ���������
	MONEY_CHANGE_ACHIEVE							= 85,	//�ɾͽ���
	MONEY_CHANGE_3V3KUAFU							= 86,	//3v3�������
	MONEY_CHANGE_VIP_INSTANCE_SWEEP					= 87,	//����ɨ��
	MONEY_CHANGE_GIFT_PACKET						= 88,	//���
	MONEY_CHANGE_KUAFU_WORLD_3V3					= 89,	//���3v3
	MONEY_CHANGE_KUAFU_WORLD_XIANFU					= 90,	//����ɸ��ᱦ
	MONEY_CHANGE_BUY_XIANFU_TICKET					= 91,	//�����ɸ�����ȯ
	MONEY_CHANGE_DOUJIAN_BUY_TIMES					= 92,	//����̨�������
	MONEY_CHANGE_DOUJIAN_CLEARCD					= 93,	//����̨����CD
	MONEY_CHANGE_DOUJIAN_FIRST_REWARD				= 94,	//����̨��ʤ����
	MONEY_CHANGE_DOUJIAN_COMBATWIN_REWARD			= 95,	//����̨��ʤ����
	MONEY_CHANGE_CULTIVATION_PURCHASE				= 96,   //�������������
	MONEY_CHANGE_CULTIVATION_REWARD					= 97,	//����������
	MONEY_CHANGE_CULTIVATION_PLUNDER_REWARD			= 98,	//�������Ӷά��
	MONEY_CHANGE_LOGIN_ACTIVITY_REWARD				= 99,	//��½������
	MONEY_CHANGE_FACTION_BOSS						= 100,	//����boss����
	MONEY_CHANGE_OFFLINE							= 101,	//���߽���
	MONEY_CHANGE_STOREHOUSE							= 102,	//���ɱ���
	MONEY_CHANGE_MASS_BOSS							= 103,	//ȫ��BOSS
	MONEY_CHANGE_MASS_BOSS_BUY_TIMES				= 104,	//ȫ��BOSS��ս����
	MONEY_CHANGE_GROUP_INSTANCE_BUY_TIMES			= 105,	//��Ӹ�����ս����
	MONEY_CHANGE_KUAFU_GROUP_INSTANCE				= 106,	//�����Ӹ���
	MONEY_CHANGE_MERIDIAN							= 107,	//��������
	MONEY_CHANGE_FACTION_BOSSDEFENSE				= 108,	//����������ս ��ɱ����
	MONEY_CHANGE_FACTION_TOWER						= 109,	//�����޾�Զ�� ��ɱ����
	MONEY_CHANGE_SINGLE_PVP							= 110,	//����PVP
	MONEY_CHANGE_EQUIPDEVELOP						= 111,	//װ����������
	MONEY_CHANGE_APPEARANCE							= 112,	//���
	MONEY_CHANGE_FACTIONSKILL						= 113,	//���弼������
	MONEY_CHANGE_UNLOCKTITLE						= 114,	//���弼������
	MONEY_CHANGE_RENAME								= 115,	//����
	MONEY_CHANGE_RANK_LIKE							= 116,	//���а����
	MONEY_CHANGE_ACT_LOTTERY						= 117,	//�齱�
	MONEY_CHANGE_ACT_DAILYGIFT						= 118,	//ÿ�����
	MONEY_CHANGE_ACT_RANK							= 119,	//��������
	MONEY_CHANGE_ACT_LIMITGIFT						= 120,	//�޶����
	MONEY_CHANGE_RECHARGE_REWARD					= 121,	//��ֵ����
	MONEY_CHANGE_CONSUME_REWARD						= 122,	//���ѷ���
	MONEY_CHANGE_MONEYTREE_USE						= 123,	//ҡ��ҡǮ��
	MAX_MONEY_CHANGE_TYPE
};

//�����������
enum Bag_Virtual_Type
{
	BAG_VIRTUAL_TYPE_STALL			= -1,	//��̯
	BAG_VIRTUAL_TYPE_UNKNOWN		= -2,	//δ֪
	SPECIALL_BAG_TYPE_MAIL			= -3,	//�ʼ�
};

//��Ʒ����
enum ITME_TYPE
{
	ITEM_TYPE_NONE						= 0,	//��
	ITEM_TYPE_EQUIP						= 1,				//װ��
	ITEM_TYPE_BOX						= 15,				//�����ࣨʹ�û�õ������͵���Ʒ��
	ITEM_TYPE_MATERIAL					= 3,				//����
	ITEM_TYPE_MEDICINE					= 12,				//ҩƷ
	ITEM_TYPE_FASHION					= 5,				//ʱװ
	ITEM_TYPE_BUFF						= 25,				//���buff��
	ITEM_TYPE_SHELI						= 6,				//����
	ITEM_TYPE_PK_MEDICINE				= 7,				//PKҩƷ
	ITEM_TYPE_PET_MEDICINE				= 8,				//����ҩ
	ITEM_TYPE_NUMBER					= 9,				//��ֵ����
};

// ��õ����Ժ�ļ�¼
enum ITEM_RECORD
{
	ITEM_RECORD_BROADCAST	=	1,			// ȫ���㲥
	ITEM_RECORD_XIANFU		=	2,			// �ɸ��ᱦ��¼
	ITEM_RECORD_MAP			=	3,			// ��ͼ֪ͨ
};

// masks for ITEM_INT_FIELD_FLAGS field
enum Item_Flags
{
	ITEM_FLAGS_QUEST                          = 0, // �Ƿ�������Ʒ
	ITEM_FLAGS_RMB							  = 1,	//�Ƿ�RMB��Ʒ
	ITEM_FLAGS_APPRAISAL                      = 2, //�Ƿ����
	ITEM_FLAGS_BROKEN                         = 3, // �Ƿ��𻵵�,�;�0
	ITEM_FLAGS_USABLE                         = 4, // �Ƿ���õ�
	ITEM_FLAGS_LOCKED						  = 5,	// ��Ʒ������־
	ITEM_FLAGS_REFUNDABLE                     = 6, // �ɻع���
	ITEM_FLAGS_UNIQUE_EQUIPPED                = 7,	//�Ƿ����װ��
	ITEM_FLAGS_SPECIALUSE                     = 8, // ������;
	ITEM_FLAGS_BOP_TRADEABLE                  = 9,  //�Ƿ�ɽ��׵�
	ITEM_FLAGS_IS_BINDED		              = 10, //�Ƿ��
	ITEM_FLAGS_IS_JIPIN			              = 11, //�Ƿ�Ʒװ��
};

//��Ʒʹ�ö�������
enum ItemUse
{
	ITEM_USE_SELF               	= 0,						//�Լ�
	ITEM_USE_TARGET					= 1,						//Ŀ��
	ITEM_USE_NULL                	= 2,						//����ʹ��
};

//����Ʒʹ�ý������
enum ItemUseResult
{
	ITEM_USE_RESULT_DISAPPEAR			= 0,					//��ʧ
	ITEM_USE_RESULT_NOT_DISAPPEAR		= 1,					//����ʧ
	ITEM_USE_RESULT_SUB_DURABLE			= 2,					//�����;�
	ITEM_USE_RESULT_UN_USE				= 3,					//����ʹ��
};

//���߷�������
enum ItemReturnType
{
	LOG_ITEM_RETURN_TYPE_HAVE				= 0,			//���������õ�
	LOG_ITEM_RETURN_TYPE_LOSE				= 1,			//��������ʧȥ
	LOG_ITEM_RETURN_TYPE_CLEAR				= 2,			//������������
	LOG_ITEM_RETURN_TYPE_GOLD				= 3,			//���ϲ����Զ�����
};

//����״̬
enum Mount_State
{
	MOUNT_STATE_FREE	    = 0, //����
	MOUNT_STATE_WAS_RIDING  = 1, //���
};

//����״̬
enum QuestStatus
{
	QUEST_STATUS_NONE           = 0,		// 
	QUEST_STATUS_COMPLETE       = 1,		//���
	QUEST_STATUS_UNAVAILABLE    = 2,		//�ò����ģ�û�յģ��������õ�???
	QUEST_STATUS_INCOMPLETE     = 3,		//����ȫ,δ���
	QUEST_STATUS_AVAILABLE      = 4,		//��Ч���ɽ���
	QUEST_STATUS_FAILED         = 5,		//ʧ��
	QUEST_STATUS_END			= 6,		//�������,���콱

	QUEST_STATUS_SHOW_INCOMPLETE = 13,		//����δ�����ʾ��
	QUEST_STATUS_SHOW_END		 = 16,		//�������������, ��ʾ��

	MAX_QUEST_STATUS
};

enum BookQuestStatus
{
	BOOK_STATUS_NONE           = 0,		 
	BOOK_STATUS_COMPLETE       = 1,		//���δ�콱
	BOOK_STATUS_UNAVAILABLE    = 2,		//�ò����ģ�û�յģ��������õ�
	BOOK_STATUS_INCOMPLETE     = 3,		//����ȫ,δ���
	BOOK_STATUS_AVAILABLE      = 4,		//��Ч���ɽ���
	BOOK_STATUS_FAILED         = 5,		//ʧ��
	BOOK_STATUS_REWARDED       = 6,		//���콱
};

//���������״̬
enum QuestGiverStatus
{
	DIALOG_STATUS_NONE                     = 0,
	DIALOG_STATUS_UNAVAILABLE              = 1,				// ���������״̬,æµ
	DIALOG_STATUS_CHAT                     = 2,             // �Ի�,3.1 - may be changed
	DIALOG_STATUS_INCOMPLETE               = 5,				//  δ���
	DIALOG_STATUS_REWARD_REP               = 6,				// ���ظ���ȡ����
	DIALOG_STATUS_AVAILABLE_REP            = 7,				// ���ظ���������
	DIALOG_STATUS_AVAILABLE                = 8,				// �пɽ�����
	DIALOG_STATUS_REWARD2                  = 9,             // no yellow dot on minimap
	DIALOG_STATUS_REWARD                   = 10,            // ���꣬�����ͽ�,yellow dot on minimap
	MAX_DIALOG_STATUS
};

//�����־
enum QuestFlags
{
	// Flags used at server and sent to client	
	QUEST_FLAGS_COMMIT_NOT_NEED_NPC	= 0x00000100,            // �ύ�����Ƿ�У��npc
	QUEST_FLAGS_ACCEPT_NOT_NEED_NPC	= 0x00000200,            // ���������Ƿ�У��npc
	QUEST_FLAGS_DAILY			= 0x00000400,                //�ճ����� Used to know quest is Daily one

	QUEST_FLAGS_AUTO_FAIL_OFF	= 0x00000001,				 //���߻����������߿�ϵ��ͼ���ͺ�ֱ������ʧ��
	QUEST_FLAGS_AUTO_COMPLETE	= 0x00000010,                //auto complete	
	QUEST_FLAGS_AUTO_REWARDED	= 0x00000020,                //�Զ����� These quests are automatically rewarded on quest complete and they will never appear in quest log client side.
	QUEST_FLAGS_AUTO_ACCEPT		= 0x00000040,                //quests in starting areas
	QUEST_FLAGS_MANUAL			= 0x00000080,				 //�ֶ����	
	QUEST_FLAGS_CANREMOVE		= 0x00001000,		  		 //�������
	// Mangos flags for set SpecialFlags in DB if required but used only at server
	_QUEST_FLAGS_FLAGS_REPEATABLE           = 0x010000,     //���ظ����ܵ� Set by 1 in SpecialFlags from DB
	_QUEST_FLAGS_FLAGS_EXPLORATION_OR_EVENT = 0x020000,     //Set by 2 in SpecialFlags from DB (if required area explore, spell SPELL_EFFECT_QUEST_COMPLETE casting, table `*_script` command SCRIPT_COMMAND_QUEST_EXPLORED use, set from script DLL)
	_QUEST_FLAGS_FLAGS_DB_ALLOWED = 0xFFFF | _QUEST_FLAGS_FLAGS_REPEATABLE | _QUEST_FLAGS_FLAGS_EXPLORATION_OR_EVENT,

	// Mangos flags for internal use only
	_QUEST_FLAGS_FLAGS_DELIVER              = 0x040000,     //Internal flag computed only,��Ҫ�ռ���Ʒ��
	_QUEST_FLAGS_FLAGS_SPEAKTO              = 0x080000,     //Internal flag computed only,��Ҫ��NPC�Ի���
	_QUEST_FLAGS_FLAGS_KILL_OR_CAST         = 0x100000,     //Internal flag computed only,ɱ���������ʹ��������Ʒ��
	_QUEST_FLAGS_FLAGS_TIMED                = 0x200000,     //��ʱ?Internal flag computed only
	QUEST_FLAGS_FLAGS_BUY_ITEM				= 0x400000,		//������Ʒ������
	QUEST_FLAGS_FLAGS_OPT_SYS				= 0x800000,		//����ϵͳ������
	QUEST_FLAGS_FLAGS_LEVEL_CREATURE		= 0x1000000,	//ɱ�ȼ���
	QUEST_FLAGS_FLAGS_LEVEL_PLAYER			= 0x2000000,	//ɱ�ȼ����
};

enum QuestRelationType
{
	QUEST_RELATION_TYPE_START = 0,		//��������
	QUEST_RELATION_TYPE_END = 1			//��������
};

//������²���
enum QuestUpdateState
{	
	QUEST_UNCHANGED = 0,	//δ�仯
	QUEST_CHANGED = 1,		//�仯
	QUEST_NEW = 2	
};

#define MAX_ACHIEVE_COUNT 100
enum AchieveField{
	ACHIEVE_FIELD_REWARD = 0,	//0 �Ƿ��Ѵ�� 1 �Ƿ����콱 2 Ԥ�� 3 Ԥ��
	ACHIEVE_FIELD_CURRENT = 1,	//�ɾͽ���
	MAX_ACHIEVE_FIELD
};

// ������ȡ�������
#define MAX_QUEST_COUNT 50
// ������ȡ�ճ��������
#define MAX_DAILY2_QUEST_COUNT 10
// �������Ŀ��
#define MAX_QUEST_TARGET_COUNT 5

enum QuestTargetInfo
{
	QUEST_TARGET_INFO_SHORT0	= 0,	//0:״̬, 1:Ŀ��ֵ
	QUEST_TARGET_INFO_PROCESS	= 1,	//����
	MAX_QUEST_TARGET_INFO_COUNT			
};

enum QuestFieldInfo
{
	QUEST_INFO_ID				= 0,					//����id, ����״̬
	QUEST_INFO_STEP_START		= QUEST_INFO_ID + 1,	//����Ŀ�꿪ʼ
	QUEST_INFO_STEP_END			= QUEST_INFO_STEP_START + MAX_QUEST_TARGET_COUNT * MAX_QUEST_TARGET_INFO_COUNT,	//����Ŀ�����
	MAX_QUEST_INFO_COUNT		= QUEST_INFO_STEP_END,
};

#define MAX_TITLE_COUNT 100
enum TitleField{
	TITLE_FIELD_INFO = 0,	//0 ID 1 ���� 16λ
	TITLE_FIELD_TIME = 1,	//�ƺ�ʧЧʱ��
	MAX_TITLE_FIELD
};
#define WELFA_BACK_TYPE_COUNT 10
enum WELFAREBACKFIELD{
	WELFA_BACK_ITEM		= 0,
	WELFA_BACK_ITEM_END = 8,
	WELFA_BACK_ITEM_NUM	= 9,
	MAX_WELFA_BACK_ITEM
};

//���� �ɾ� �ƺ� ���� ����ֶ�
enum EQuestFields
{
	QUEST_FIELD_ACHIEVE_START	= 0,	//�ɾͿ�ʼ
	QUEST_FIELD_ACHIEVE_END		= QUEST_FIELD_ACHIEVE_START + MAX_ACHIEVE_COUNT * MAX_ACHIEVE_FIELD,//�ɾͽ���
	QUEST_FIELD_ACHIEVE_ALL		= QUEST_FIELD_ACHIEVE_END,//�ܳɾ͵�
	QUEST_FIELD_ACHIEVE_REWARD	= QUEST_FIELD_ACHIEVE_ALL + 1,//�ɾ͵㽱��ID

	QUEST_FIELD_QUEST_START		= QUEST_FIELD_ACHIEVE_REWARD + 1,									//����ʼ
	QUEST_FIELD_QUEST_END		= QUEST_FIELD_QUEST_START + MAX_QUEST_INFO_COUNT * MAX_QUEST_COUNT,	//�������

	QUEST_FIELD_TITLE_START		= QUEST_FIELD_QUEST_END,									//�ƺſ�ʼ
	QUEST_FIELD_TITLE_END		= QUEST_FIELD_TITLE_START + MAX_TITLE_COUNT * MAX_TITLE_FIELD,//�ƺŽ���

	QUEST_FIELD_WELFARE_SHOUCHONG	=	QUEST_FIELD_TITLE_END,//�Ƿ���ȡ�׳影��
	QUEST_FIELD_WELFARE_CHECKIN		=	QUEST_FIELD_WELFARE_SHOUCHONG + 1,//ÿ��ǩ��������ȡ��� ��λ��ʾ
	QUEST_FIELD_WELFARE_CHECKIN_ALL	=	QUEST_FIELD_WELFARE_CHECKIN + 1,//�ۻ�ǩ��������ȡ��� ��λ��ʾ
	QUEST_FIELD_WELFARE_LEVEL		=	QUEST_FIELD_WELFARE_CHECKIN_ALL + 1,//������������

	QUEST_FIELD_WELFARE_BACK_START	= QUEST_FIELD_WELFARE_LEVEL + 1,
	QUEST_FIELD_WELFARE_BACK_END	= QUEST_FIELD_WELFARE_BACK_START + MAX_WELFA_BACK_ITEM * WELFA_BACK_TYPE_COUNT,

	QUEST_FIELD_DAILY2_FINISHED		= QUEST_FIELD_WELFARE_BACK_END,		// �ճ�������ɸ���
	QUEST_FIELD_DAILY2_SUBMIT		= QUEST_FIELD_DAILY2_FINISHED + 1,	// �ճ������Ƿ��ύ
	QUEST_FIELD_DAILY2_QUEST_START	= QUEST_FIELD_DAILY2_SUBMIT + 1,	// �ճ�����ʼ
	QUEST_FIELD_DAILY2_QUEST_END	= QUEST_FIELD_DAILY2_QUEST_START + MAX_QUEST_INFO_COUNT * MAX_DAILY2_QUEST_COUNT,	//�ճ��������

	QUEST_FIELD_WELFARE_RECHARGE_REWARD_FLAG	= QUEST_FIELD_DAILY2_QUEST_END,			//�ۼƳ�ֵ������ȡ���
	QUEST_FIELD_WELFARE_CONSUME_REWARD_FLAG	= QUEST_FIELD_WELFARE_RECHARGE_REWARD_FLAG + 1, //�ۼƳ�ֵ������ȡ���

	QUEST_FIELD_WELFARE_SEVEN_DAY_PROCESS	= QUEST_FIELD_WELFARE_CONSUME_REWARD_FLAG + 1,	//���մ��� ����
	QUEST_FIELD_WELFARE_SEVEN_DAY_FLAG		= QUEST_FIELD_WELFARE_SEVEN_DAY_PROCESS + 1,	//���մ��� ��ȡ״̬
};

//ս��״̬
enum Combat_State
{
	COMBAT_STATE_LEAVE = 0, //����ս��
	COMBAT_STATE_ENTER = 1, //����ս��
};

//ս��״̬
enum UnitState
{
	UNIT_STAT_DIED            = 0x0001,
	UNIT_STAT_MELEE_ATTACKING = 0x0002,                     // player is melee attacking someone
	UNIT_STAT_CAST_SPELL	  = 0x0004,                     // ��������
	UNIT_STAT_SPELL_PROCESS   = 0x0008,						//����ʩ��
	UNIT_STAT_ROAMING         = 0x0010,						//����
	UNIT_STAT_CHASE           = 0x0020,						//׷��
	UNIT_STAT_SEARCHING       = 0x0040,						//����
	UNIT_STAT_FLEEING         = 0x0080,						//�ӱ�
	UNIT_STAT_MOVING          = (UNIT_STAT_ROAMING | UNIT_STAT_CHASE | UNIT_STAT_SEARCHING | UNIT_STAT_FLEEING),
	UNIT_STAT_IN_FLIGHT       = 0x0100,                     // player is in flight mode
	UNIT_STAT_FOLLOW          = 0x0200,						//����
	UNIT_STAT_ROOT            = 0x0400,						//����???
	UNIT_STAT_CONFUSED        = 0x0800,						//ʹ����
	UNIT_STAT_DISTRACTED      = 0x1000,						//ת��,ʹ����
	UNIT_STAT_ISOLATED        = 0x2000,                     // ����,�⻷�޷�Ӱ��������� area auras do not affect other players
	UNIT_STAT_ATTACK_PLAYER   = 0x4000,						// ����
	UNIT_STAT_ALL_STATE       = 0xffff                      //(UNIT_STAT_STOPPED | UNIT_STAT_MOVING | UNIT_STAT_IN_COMBAT | UNIT_STAT_IN_FLIGHT)
};

//����״̬
enum DeathState
{
	DEATH_STATE_ALIVE       = 0,		//����
	DEATH_STATE_CORPSE      = 1,		//ʬ�壬�ڿͻ��˿ɼ�ʬ��
	DEATH_STATE_DEAD        = 2,		//�������ڿͻ���ʬ����ʧ
};

//������Ϣ���������գ�����һ���ȵ�
enum HitInfo
{
	HITINFO_NORMALSWING         = 1,		//��ͨ
	HITINFO_CRITHIT				= 2,		//����
	HITINFO_MISS                = 3,		//���
	HITINFO_GEDANG				= 4,		//��
	HITINFO_CRITICALHIT			= 5,		//����һ��
	HITINFO_BLOWFLY				= 6,		//����
	HITINFO_LIUXUE				= 7,		//��Ѫ
	HITINFO_CURE				= 8,		//����
	HITINFO_JUMP_EVA			= 9,		//����
	HITINFO_POISON				= 10,		//��
	HITINFO_ICE					= 11,		//��
	HITINFO_FANTANSHANGHAI		= 12,		//�����˺�
};

//�ƶ�״̬
enum Move_Status
{
	MOVE_STATUS_STOP = 0 ,
	MOVE_STATUS_RUN	 = 1,
};

//NPC��ʶ
/// Non Player Character flags
enum NPCFlags
{
	UNIT_NPC_FLAG_NONE                  = -1,

	UNIT_NPC_FLAG_GOSSIP                = 0,       // 100%����NPC
	UNIT_NPC_FLAG_QUESTGIVER            = 1,       // ���񷢲�PCguessed, probably ok
	UNIT_NPC_FLAG_UNK1                  = 2, 		//Ԥ��
	UNIT_NPC_FLAG_UNK2                  = 3,
	UNIT_NPC_FLAG_TRAINER               = 4,      // 100%  ѵ��ʦ
	UNIT_NPC_FLAG_TRAINER_CLASS         = 5,       // 100%  ְҵѵ��ʦ
	UNIT_NPC_FLAG_TRAINER_PROFESSION    = 6,       // 100%  ����ְҵѵ��ʦ��
	UNIT_NPC_FLAG_VENDOR                = 7,       // 100%  ��������
	UNIT_NPC_FLAG_VENDOR_PROP           = 8,       // 100%, ����
	UNIT_NPC_FLAG_VENDOR_WEAPON         = 9,        // 100%  ����
	UNIT_NPC_FLAG_VENDOR_POISON         = 10,       // ҩƷ
	UNIT_NPC_FLAG_VENDOR_REAGENT        = 11,       // 100%  ��Ʒ
	UNIT_NPC_FLAG_VENDOR_EQUIPMENT      = 12,       // 100%  װ��
	UNIT_NPC_FLAG_FLIGHTMASTER          = 13,       // 100% ���е����Ա
	UNIT_NPC_FLAG_SPIRITHEALER          = 14,       // guessed ����Npc
	UNIT_NPC_FLAG_SPIRITGUIDE           = 15,       // guessed �����
	UNIT_NPC_FLAG_INNKEEPER             = 16,       // 100% �õ��ϰ�
	UNIT_NPC_FLAG_WAREHOUSE             = 17,       // 100% �ֿ�
	UNIT_NPC_FLAG_PETITIONER            = 18,       // 100% ������
	UNIT_NPC_FLAG_TABARDDESIGNER        = 19,       // 100%����������NPC
	UNIT_NPC_FLAG_BATTLEMASTER          = 20,       // 100%ս������Ա
	UNIT_NPC_FLAG_AUCTIONEER            = 21,       // 100%������
	UNIT_NPC_FLAG_STABLEMASTER          = 22,       // 100%���
	UNIT_NPC_FLAG_GUILD_BANKER          = 23,       // ��������cause client to send 997 opcode
	UNIT_NPC_FLAG_CHALLENGE             = 24,       // �������ս��Ҫ�����,UNIT_NPC_FLAG_GUARD
	UNIT_NPC_FLAG_ONE_ONE				= 25,       // �Ƿ�����,ûǮ��û���飬ûװ����û����
};

//���й̶���BUFF => buff idҪ���buff_template��id��Ӧ
enum EBuffID
{
	BUFF_ONEPOINTFIVE_JINGYAN	= 101,		//1.5�����鵤
	BUFF_TOW_JINGYAN			= 102,		//2�����鵤
	BUFF_THREE_JINGYAN			= 103,		//3�����鵤
	BUFF_FIVE_JINGYAN			= 104,		//5�����鵤
	BUFF_FANTAN					= 105,		//����
	BUFF_LIANJIE				= 106,		//����
	BUFF_BEILIANJIE				= 107,		//������
	BUFF_GANGCI					= 108,		//�ִ�
	BUFF_DINGSHEN				= 109,		//����
	BUFF_YUNXUAN				= 110,		//��ѣ
	BUFF_YUNMIE_ELING			= 111,		//���𣨶��飩
	BUFF_HUIFU_HUDUN			= 112,		//�ָ�����
	BUFF_FANJI_HUDUN			= 113,		//��������
	BUFF_LINGXUE				= 114,		//��Ѫ
	BUFF_ZHUOSHAO				= 115,		//����
	BUFF_JUDU					= 116,		//�綾
	BUFF_ZHONGDU				= 117,		//�ж�
	BUFF_BINGJIA				= 118,		//����
	BUFF_BINGDONG				= 119,		//����
	BUFF_BAOZHA_DILEI			= 120,		//��ը�����ף�
	BUFF_SHOUWEI_ZHAOHUAN		= 121,		//�������ٻ���
	BUFF_BIAOJI					= 122,		//���
	BUFF_KUANGBAO				= 123,		//��
	BUFF_JIANSU					= 124,		//����
	BUFF_CHENMO					= 125,		//��Ĭ
	BUFF_XUECHI					= 126,		//Ѫ��
	BUFF_WAIGONGMIANYI			= 127,		//�⹥����
	BUFF_NEIGONGMIAN			= 128,		//�ڹ�����
	BUFF_WUDI					= 129,		//�޵�
	BUFF_ZHANSHEN_FUTI			= 130,		//ս����
	BUFF_JINGANG_BUHUAITI		= 131,		//��ղ�����
	BUFF_KUANGBEN				= 132,		//��
	BUFF_HUOBA					= 133,		//���
	BUFF_LINGTI					= 134,		//����
	BUFF_HUANHUA_ZHU			= 135,		//�û�����
	BUFF_HUANHUA_REN			= 136,		//�û�����
	BUFF_HUANHUA_GUI			= 137,		//�û��ɹ�
	BUFF_HUANHUA_XIAN			= 138,		//�û�����
	BUFF_HUANHUA_XIULUO			= 139,		//�û�������
	BUFF_XIULUOLI				= 140,		//������
	BUFF_ZHENYING				= 141,		//��Ӫ
	BUFF_ZHANDOU_STATE			= 142,		//ս��״̬
	BUFF_JUMP_DOWN				= 144,		//����
	BUFF_ANXIANG_SHUYING		= 145,		//������Ӱ
	BUFF_ZHIKONG				= 146,		//�Ϳ�
	BUFF_FUKONG					= 147,		//����

	BUFF_JUMP_JUMP				= 143,		//��Ծ

	BUFF_NEW_PLAYER_PROTECTED	= 148,		//���ֱ���
	BUFF_DEATH_PROTECTED		= 149,		//��������
	BUFF_INVINCIBLE				= 150,		//�޵�
	BUFF_INVISIBLE				= 151,		//����
	BUFF_YINCHANG				= 152,		//����
	BUFF_ROAR					= 153,		//���
	BUFF_HEAL					= 200,		//�ٷֱȻ�Ѫ
	BUFF_ATTACK					= 201,		//������ǿ
	BUFF_ARMOR					= 202,		//������ǿ
	BUFF_CRIT					= 203,		//������ǿ
	BUFF_ALLATTR				= 204,		//ȫ������ǿ

};

enum BUFF_DEFAULT_EFFECT_ID
{
	BUFF_DEFAULT_EFFECT_ID_JUMP_JUMP = 1,					//Ĭ�ϵ���Ծbuff��Ч��id
	BUFF_DEFAULT_EFFECT_ID_NEW_PLAYER_PROTECTED = 2,		//Ĭ�ϵ����ֱ���buff��Ч��id
	BUFF_DEFAULT_EFFECT_ID_DEATH_PROTECTED = 3,				//Ĭ�ϵ���������buff��Ч��id
};

#define MAX_2JI_SHIJIAN_UINT32 20	//����2���¼�uint32
#define MAX_HONGYAN_DATI_COUNT 10	//�������������

//����ϵͳ����ö��
enum HongYanOptType
{
	HONGYAN_JIESHI_MEIREN		= 	0,		//--��ʶ����
	HONGYAN_DIANZAN				= 	1,		//--����
	HONGYAN_PINGJIA				= 	2,		//--����
	HONGYAN_SHIZHUANG_JIHUO		=	3,		//--ʱװ����
	HONGYAN_SHIZHUANG_CHUANDAI	= 	4,		//--ʱװ����
	HONGYAN_XIANGCE_JIHUO		= 	5,		//--��ἤ��
	HONGYAN_SHIJIAN_CHULI		= 	6,		//--�¼�����
	HONGYAN_CHUYOU				= 	7,		//--����
	HONGYAN_HUIFU_HUOLI			= 	8,		//--�ָ�����ֵ
	HONGYAN_ADD_NEIWU_SHIJIAN	= 	9,		//--���������¼�
};

//����ϵͳ�������
enum HongYanPlayerAttrsType
{
	HONGYAN_PLAYER_ATTRS_XIAYI		=	0,		//--����ֵ
	HONGYAN_PLAYER_ATTRS_FENGLIU	= 	1,		//--����
	HONGYAN_PLAYER_ATTRS_MINGSHENG	= 	2,		//--����
	HONGYAN_PLAYER_ATTRS_WENTAO		= 	3,		//--���
	HONGYAN_PLAYER_ATTRS_WULUE		= 	4,		//--����
	HONGYAN_PLAYER_ATTRS_CAIYI		= 	5,		//--����
	HONGYAN_PLAYER_ATTRS_QINHE		= 	6,		//--�׺�
	HONGYAN_PLAYER_ATTRS_LIYI		= 	7,		//--����
	HONGYAN_PLAYER_ATTRS_XIANGMAO	= 	8,		//--��ò
	HONGYAN_PLAYER_ATTRS_HUOLI		= 	9,		//--����
	MAX_PLAYER_ATTRS	= 10,
};

//����ϵͳ��������
enum HongYanMeiRenAttrsType
{
	HONGYAN_MEIREN_ATTRS_JIESHI_BIT		= 	0,		//0:�Ƿ��ʶ  1~31����ʶ����
	HONGYAN_MEIREN_ATTRS_XINGGE_BIT		= 	1,		//�Ը�
	HONGYAN_MEIREN_ATTRS_AIHAO_BIT		= 	2,		//����
	HONGYAN_MEIREN_ATTRS_CHANGJING_BIT	= 	3,		//����
	HONGYAN_MEIREN_ATTRS_SHIZHUANG_BIT	= 	4,		//ʱװ
	HONGYAN_MEIREN_QINMIDU_UINT16		= 	5,		//0�����ܶ� 1:��ǰ������ʱװID
	HONGYAN_MEIREN_XIANGCE_BIT			= 	6,		//���˼�������
	MAX_MEIREN_ATTRS_TYPE				=	7,
};

//����ϵͳ��������ֵ
enum HongYanMeiRenRenQiType
{
	HONGYAN_MEIREN_DIANZAN		= 	0,		//����
	HONGYAN_MEIREN_MEIHAO		= 	1,		//��ò
	HONGYAN_MEIREN_JIESHI_COUNT	= 	2,		//���˽�ʶ���������
	MAX_MEIREN_RENQI_TYPE		=	3,
};

//����ϵͳ���˱�
enum HongYanMeiRen
{
	HONGYAN_CAIXUE			= 0,	//��ѩ
	HONGYAN_ZHENFEI			= 1,	//����
	HONGYAN_YANLIN			= 2,	//����
	HONGYAN_MURONGYANYAN	= 3,	//Ľ������
	HONGYAN_YAORU			= 4,	//����
	HONGYAN_XIANGJING		= 5,	//�
	HONGYAN_HENGXIAOZHUO	= 6,	//��С׿
	HONGYAN_LIJI			= 7,	//ٳ��
	HONGYAN_SIQI			= 8,	//˼�
	HONGYAN_YOUYOU			= 9,	//����
	HONGYAN_LINCHUER		= 10,	//�ֳ���
	HONGYAN_WANYAN_YUNNA	= 11,	//��������
	HONGYAN_QUANHUIQIAO		= 12,	//ȫ����
	HONGYAN_TUOBALVZHU		= 13,	//�ذ�����
	HONGYAN_QINGYAN			= 14,	//����
	HONGYAN_SUOMOER			= 15,	//��ĭ��
	HONGYAN_GUQIANQIAN		= 16,	//������
	HONGYAN_AYIGULI			= 17,	//��������
	HONGYAN_ZUOYUYI			= 18,	//������
	HONGYAN_ZILUO			= 19,	//����
	HONGYAN_QUNUO			= 20,	//��ŵ
	HONGYAN_XUANYING		= 21,	//��ӣ

	MAX_MEIREN = 32,
};

//����GM����Ķ���
enum Gm_Command_List
{
	GM_COMMAND_NULL					= 0,	//������
	GM_COMMAND_JIULONGCHAO    	 	= 1,	//@��������
	GM_COMMAND_SUCAI    			= 2,	//@�ز�
	GM_COMMAND_JIAOBEN 				= 3,	//@�ű�
	GM_COMMAND_TI					= 4,	//@��
	GM_COMMAND_ZAIXIAN  			= 5,	//@����
	GM_COMMAND_DITURENSHU 			= 6,	//@��ͼ����
	GM_COMMAND_ZHAOCAI	  			= 7,	//@�в�
	GM_COMMAND_ZHIZAO				= 8,	//@����
	GM_COMMAND_QINGLI				= 9,	//@����
	GM_COMMAND_ZHUANGBEI			= 10,	//@װ��
	GM_COMMAND_PAIHANGBANG			= 12,	//@���а�
	GM_COMMAND_YOUJIAN				= 13,	//@�ʼ�
	GM_COMMAND_BENGDIAO				= 15,	//@����
	GM_COMMAND_BANGZHU				= 16,	//@����
	GM_COMMAND_GONGGAO				= 17,	//@����
	GM_COMMAND_SHIJIETISHI			= 18,	//@������ʾ
	GM_COMMAND_PAIDUI				= 19,	//@�Ŷ�
	GM_COMMAND_PINGBICI				= 20,	//@���δ�
	GM_COMMAND_GUANBIFUWUQI			= 21,	//@�رշ�����
	GM_COMMAND_CHONGZHI				= 22,	//@��ֵ
	GM_COMMAND_GUANBIDITU			= 23,	//@�رյ�ͼ
	GM_COMMAND_DENGJI				= 24,	//@�ȼ�
	GM_COMMAND_QINGLIRENWUWUPIN		= 25,	//@����������Ʒ
	GM_COMMAND_QINGLIRENWU			= 26,	//@��������
	GM_COMMAND_WANCHENGRENWU		= 27,	//@�������
	GM_COMMAND_JIESHOURENWU			= 28,	//@��������
	GM_COMMAND_GANDIAO				= 29,	//@�ɵ�
	GM_COMMAND_SHUAGUAI				= 30,	//@ˢ��
	GM_COMMAND_CHUANSONG			= 31,	//@����
	GM_COMMAND_XIAZOU				= 32,	//@Ϲ��
	GM_COMMAND_SUICIDE				= 33,	//@�Ա�
	GM_COMMAND_SERVER_INFO			= 34,	//@������
	GM_COMMAND_DB					= 35,	//@���ݿ�
	GM_COMMAND_KAIFUSHIJIAN			= 36,	//@����ʱ��
	GM_COMMAND_TEST_SHUJU			= 37,	//@��������
	GM_COMMAND_UPDATE_SERVER		= 38,	//@���·�����
	GM_COMMAND_RESESSION_OPTS		= 39,	//@Э��ע��
	GM_COMMAND_RENWUTIAOZHUAN		= 40,	//@������ת
	GM_COMMAND_BACKUP_DATA			= 41,	//@��������
	GM_COMMAND_RETURN_DATA			= 42,	//@�ص�����
	GM_COMMAND_PRINT_OBJECT			= 43,	//@��ӡ����
	GM_COMMAND_TEST_HEFU			= 44,	//@���ԺϷ�
	GM_COMMAND_CLEAR_PAIHANGBANG	= 45,	//@������а�
	GM_COMMAND_MEMORY_RECOVERY		= 46,	//@�ڴ����
	GM_COMMAND_PRINT_MAP			= 47,	//@��ӡ��ͼ
	GM_COMMAND_DEL_MAP_INFO			= 48,	//@��յ�ͼ��Ϣ
	GM_COMMAND_RESTORE_SYSTEM		= 49,	//@��̨����
	GM_COMMAND_CALL_REMOVE_ITEM		= 50,	//@�����Ʒ����
	GM_COMMAND_SUBLINE				= 51,	//@����
	GM_COMMAND_CUSTOM				= 52,	//@CUSTOM
	GM_COMMAND_VIP					= 53,	//@VIP
	GM_COMMAND_SELF_KILL			= 54,	//@��ɱ
};

//��ѯ�����Ϣ��ʱ����Ҫ��������Ϣ
enum EQueryPlayerInfoFlag
{
	QUERY_PLAYER_FLAG_BASE			= 0,	//��һ�����Ϣ
	QUERY_PLAYER_FLAG_NAME			= 1,	//�������
	QUERY_PLAYER_FLAG_EQUIP			= 2,	//���װ������
	QUERY_PLAYER_FLAG_PIFENG		= 3,	//������Ϣ
	QUERY_PLAYER_FLAG_FORCE			= 4,	//���ս����
	QUERY_PLAYER_FLAG_OTHER			= 5,	//������Ϣ

	//�����Ƿ�����±�Ķ���
	QUERY_PLAYER_FLAG_MOUNT			= 20,	//��������
	QUERY_PLAYER_FLAG_EQUIP_BAG		= 21,	//װ������
	QUERY_PLAYER_FLAG_MAIN_BAG		= 22,	//��������
	QUERY_PLAYER_FLAG_STORAGE_BAG	= 23,	//�ֿ����
	QUERY_PLAYER_FLAG_STALL_BAG		= 24,	//̯λ����	
};

//�������Ͷ���
enum EQuestType
{											
	QUEST_TYPE_MAIN  						 = 0,		//��������
	QUEST_TYPE_EXTENSIONS					 = 1,		//֧������
	QUEST_TYPE_ACTIVITY						 = 2,		//�����
	QUEST_TYPE_QIYU							 = 3,		//��������
	QUEST_TYPE_DAILY						 = 4,		//ÿ�ջ�����
	QUEST_TYPE_DAILY2						 = 5,		//�ճ�����
};

// ����Ŀ�����Ͷ���
enum QuestTargetType
{
	QUEST_TARGET_TYPE_PLAYER_LEVEL			= 1,	//����ȼ�
	QUEST_TARGET_TYPE_PLAYER_FORCE			= 2,	//����ս��

	QUEST_TARGET_TYPE_FACTION				= 3,	//����򴴽�����
	QUEST_TARGET_TYPE_FACTION_DONATION		= 4,	//����
	QUEST_TARGET_TYPE_FACTION_ACTIVITY		= 5,	//����

	QUEST_TARGET_TYPE_FIELD_BOSS			= 6,	//�μ�Ұ��BOSS
	QUEST_TARGET_TYPE_WORLD_BOSS			= 7,	//�μ�����BOSS

	QUEST_TARGET_TYPE_RESOURCE_INSTANCE		= 8,	//��ս��Դ����
	QUEST_TARGET_TYPE_TRIAL_INSTANCE		= 9,	//��ս��������

	QUEST_TARGET_TYPE_OWN_DIVINE			= 10,	//����������
	QUEST_TARGET_TYPE_EQUIP_DIVINE			= 11,	//װ���������
	QUEST_TARGET_TYPE_STRENGTH_DIVINE		= 12,	//ǿ���������

	QUEST_TARGET_TYPE_RAISE_SKILL			= 13,	//��������

	QUEST_TARGET_TYPE_TRAIN_MOUNT			= 14,	//��������
	QUEST_TARGET_TYPE_RAISE_MOUNT_SKILL		= 15,	//�����������⼼��

	QUEST_TARGET_TYPE_FRIEND_DONATION		= 16,	//���ͺ�������

	QUEST_TARGET_TYPE_STRENGTH_SUIT			= 17,	//ǿ��װ��
	QUEST_TARGET_TYPE_STRENGTH_GEM			= 18,	//ǿ����ʯ

	QUEST_TARGET_TYPE_TALK					= 19,	//�Ի�

	QUEST_TARGET_TYPE_PICK_GAME_OBJECT		= 20,	//�ɼ�
	QUEST_TARGET_TYPE_CHECK_GAME_OBJECT		= 21,	//���

	QUEST_TARGET_TYPE_KILL_MONSTER			= 22,	//��ɱ����
	QUEST_TARGET_TYPE_USE_ITEM				= 23,	//ʹ����Ʒ
	QUEST_TARGET_TYPE_SUIT					= 24,	//���д���װ��

	QUEST_TARGET_TYPE_MOUNT_LEVEL			= 25, //����ﵽx
	QUEST_TARGET_TYPE_FRIEND_NUM			= 26, //ӵ�к���x
	QUEST_TARGET_TYPE_KILL_MONSTER_NUM		= 27, //��ɱ����x
	QUEST_TARGET_TYPE_DIVINE_NUM			= 28, //ӵ�����x
	QUEST_TARGET_TYPE_DIVINE_LEV			= 29, //����ȼ�x
	QUEST_TARGET_TYPE_DOUJIANTAI			= 30, //����̨ʤ��x
	QUEST_TARGET_TYPE_TITLE_NUMBER			= 31,	//�ƺ������ﵽx��
	QUEST_TARGET_TYPE_FASHION_NUMBER		= 32,	//ʱװ�����ﵽx��

	QUEST_TARGET_TYPE_ACHIEVE				= 40,	//�ɾ͵����ﵽX��
	QUEST_TARGET_TYPE_SUIT_TITLE			= 41,	//���X�ƺ�
	QUEST_TARGET_TYPE_SUIT_FASHION			= 42,	//����ʱװX
	QUEST_TARGET_TYPE_JOIN_DOUJIANTAI		= 43,	//����X�ζ���̨
	QUEST_TARGET_TYPE_JOIN_KUAFU_3V3		= 44,	//����X��3V3
	QUEST_TARGET_TYPE_WIN_KUAFU_3V3			= 45,	//3v3��ʤx��
	QUEST_TARGET_TYPE_JOIN_XIANFU			= 46,	//����X���ɸ��ᱦ
	QUEST_TARGET_TYPE_WIN_XIANFU			= 47,	//�ɸ��ᱦ��ʤX��
	QUEST_TARGET_TYPE_KILL_MONSTER_COLLECT	= 48,	//ɱ���ռ���Ʒ
	QUEST_TARGET_TYPE_TURN_ITEM_IN			= 49,	//�Ͻ���Ʒ
	QUEST_TARGET_TYPE_PASS_WORLD_RISK		= 50,	//����ð��ͨ��
	QUEST_TARGET_TYPE_SMELT					= 51,	//����װ��
	QUEST_TARGET_TYPE_CONTRIBUTE_TIMES		= 52,	//ΪŮ�����״���
	QUEST_TARGET_TYPE_CONTRIBUTE_TOTAL_TIMES= 53,	//ΪŮ�������ܴ���
	QUEST_TARGET_TYPE_CONTRIBUTE_CHARM		= 54,	//ΪŮ����������ֵ
	QUEST_TARGET_TYPE_CONTRIBUTE_ITEM		= 55,	//ΪŮ�����׵���
	QUEST_TARGET_TYPE_LOOT_ITEM				= 56,	//�ռ�ĳЩ����
	QUEST_TARGET_TYPE_SINGLE_THX_TIMES		= 57,	//Ů���������л����
	QUEST_TARGET_TYPE_TOTAL_THX_TIMES		= 58,	//Ů���ۼƸ�л����

	QUEST_TARGET_TYPE_WINGS_UPGRADE_LEVEL	= 59,	//�����׵ȼ��ﵽX
	QUEST_TARGET_TYPE_WINGS_UPDRADE_TIMES	= 60,	//����������X��
	QUEST_TARGET_TYPE_WINGS_STRENGTH_LEVEL	= 61,	//���ǿ���ȼ��ﵽX
	QUEST_TARGET_TYPE_WINGS_STRENGTH_TIMES	= 62,	//���ǿ������X��

	QUEST_TARGET_TYPE_TALISMAN_LEVEL		= 63,	//�������ⷨ����X��
	QUEST_TARGET_TYPE_MOUNT_STRENGTH_LEVEL	= 64,	//����ǿ���ȼ��ﵽX
	QUEST_TARGET_TYPE_REFINE_SUIT			= 65,	//ָ����λװ������x��
	QUEST_TARGET_TYPE_WASH_SUIT				= 66,	//ָ����λװ��ϴ��x��
	QUEST_TARGET_TYPE_MERIDIAN_LEVEL		= 67,	//��������X��
	QUEST_TARGET_TYPE_JOIN_SINGLE_PVP		= 68,	//�μ���λ��X��
	QUEST_TARGET_TYPE_SINGLE_PVP_WINS		= 69,	//��λ��ʤ��X��
	QUEST_TARGET_TYPE_ACTIVE_TASK			= 70,	//���X����Ծ����
	QUEST_TARGET_TYPE_DAILY_TASK			= 71,	//���X���ճ�����
	QUEST_TARGET_TYPE_GEM_TOTAL_LEVEL		= 72,	//���б�ʯ�ܵȼ�����X��
	QUEST_TARGET_TYPE_WINGS_BLESS_TIMES		= 73,	//���ף��X��


};

//���Ҵ�������
enum CURRENCY_HANDLE_TYPE
{
	CURRENCY_HANDLE_TYPE_ADD	= 0,	//����
	CURRENCY_HANDLE_TYPE_SUB	= 1,	//����
};


//������Чʱ�似��IDö��
enum SpellYouXiaoTime
{
	SPELL_VALID_TIME_POTIAN_2		= 0,		//�����ʽ
	SPELL_VALID_TIME_POTIAN_3		= 1,		//������ʽ
	SPELL_VALID_TIME_YUNFEI_2		= 2,		//�Ʒ���ʡ�����
	SPELL_VALID_TIME_YUNFEI_3		= 3,		//�Ʒ���ʡ�����
	SPELL_VALID_TIME_FENGFAN_2		= 4,		//�緭�Ʊ䡤����
	SPELL_VALID_TIME_ZHUXIAN_2		= 5,		//���ɽ��󡤶���
	SPELL_VALID_TIME_ZHUXIAN_3		= 6,		//���ɽ�������
	MAX_SPELL_VALID		= 15,
};



#define MAX_SPELL_SLOT 6
#define NOMAL_ATTACK_TIME 1300
#define NOMAL_MOVE_SPEED 130
#define MAX_ITEM_SPELL	3

#define MAX_BASE_ATTR_FIELD_COUNT 15	//���������������
#define MAX_BUFF 50						//����������buff��
#define MAX_UNIT_BUFF 16				//�����������buff��

//װ�����Ͱ���ʱװ ��ͷ����
enum Equipment_Type
{
	//��ͨװ��
	EQUIPMENT_TYPE_OTHER    	= 0,	//����
	EQUIPMENT_TYPE_MAIN_WEAPON	= 1,	//����
	EQUIPMENT_TYPE_COAT			= 2,	//�·�
	EQUIPMENT_TYPE_LEG			= 3,	//����
	EQUIPMENT_TYPE_BELT			= 4,	//����
	EQUIPMENT_TYPE_SHOES		= 5,	//Ь��
	EQUIPMENT_TYPE_HELMET		= 6,	//ͷ��
	EQUIPMENT_TYPE_NECKLACE		= 7,	//����
	EQUIPMENT_TYPE_PANTS		= 8,	//����
	EQUIPMENT_TYPE_LRING		= 9,	//���ָ
	EQUIPMENT_TYPE_BRACELET		= 10,	//����
	EQUIPMENT_TYPE_CLOAK		= 11,	//����
	EQUIPMENT_TYPE_RRING		= 12,	//�ҽ�ָ
	EQUIPMENT_TYPE_FASHION		= 13,	//ʱװ
	EQUIPMENT_TYPE_RESERVE3		= 14,	//Ԥ��
	EQUIPMENT_TYPE_RESERVE4		= 15,	//Ԥ��
	EQUIPMENT_TYPE_RESERVE5		= 16,	//Ԥ��
	EQUIPMENT_TYPE_RESERVE6		= 17,	//Ԥ��
	EQUIPMENT_TYPE_RESERVE7		= 18,	//Ԥ��
	EQUIPMENT_TYPE_RESERVE8		= 19,	//Ԥ��
	EQUIPMENT_TYPE_MAX_POS		= EQUIPMENT_TYPE_RESERVE8 +1,	//���λ��

	//ʱװ���ͽ�����ͨװ������ ��ͷ����
	FASHION_TYPE_MAIN_WEAPON	= EQUIPMENT_TYPE_MAX_POS,	//ͷ�� Ԥ��
	FASHION_TYPE_HELMET			= EQUIPMENT_TYPE_MAX_POS + 1,	//��׹
	FASHION_TYPE_COAT			= EQUIPMENT_TYPE_MAX_POS + 2,	//����
	FASHION_TYPE_BELT			= EQUIPMENT_TYPE_MAX_POS + 3,	//����
	FASHION_TYPE_LEG			= EQUIPMENT_TYPE_MAX_POS + 4,	//���� Ԥ��
	FASHION_TYPE_PANTS			= EQUIPMENT_TYPE_MAX_POS + 5,	//�·�
	FASHION_TYPE_SHOES			= EQUIPMENT_TYPE_MAX_POS + 6,	//��������
	FASHION_TYPE_BRACELET		= EQUIPMENT_TYPE_MAX_POS + 7,	//��������
	FASHION_TYPE_NECKLACE		= EQUIPMENT_TYPE_MAX_POS + 8,	//���� 
	FASHION_TYPE_RING			= EQUIPMENT_TYPE_MAX_POS + 9,	//����
	FASHION_TYPE_CLOAK			= EQUIPMENT_TYPE_MAX_POS + 10,	//����
	FASHION_TYPE_RESERVE1		= EQUIPMENT_TYPE_MAX_POS + 11,	//���� Ԥ��
	FASHION_TYPE_RESERVE2		= EQUIPMENT_TYPE_MAX_POS + 12,	//Ь�� Ԥ��
	FASHION_TYPE_RESERVE3		= EQUIPMENT_TYPE_MAX_POS + 13,	//��������ʱװ,����Ϊ��˫������±�
	FASHION_TYPE_RESERVE4		= EQUIPMENT_TYPE_MAX_POS + 14,	//ָ��
	FASHION_TYPE_RESERVE5		= EQUIPMENT_TYPE_MAX_POS + 15,	//����
	FASHION_TYPE_RESERVE6		= EQUIPMENT_TYPE_MAX_POS + 16,	//����ָ
	FASHION_TYPE_RESERVE7		= EQUIPMENT_TYPE_MAX_POS + 17,	//������
	FASHION_TYPE_RESERVE8		= EQUIPMENT_TYPE_MAX_POS + 18,	//������
	FASHION_TYPE_RESERVE9		= EQUIPMENT_TYPE_MAX_POS + 19,	//Ԥ��
	MAX_EQUIPMENT_TYPE			= FASHION_TYPE_RESERVE9 + 1,	//����װ��λ��
};

//��������
enum Weapon_Pos
{
	WEAPON_POS_MAIN				= 0,	//����
	WEAPON_POS_OFF				= 1,	//����
	WEAPON_POS_SINGLE_HAND		= 2,	//����
	WEAPON_POS_BOTH_HANDS		= 3,	//˫��
	MAX_WEAPON_POS											//��������
};

//��������,��������
enum Powers
{
	POWER_MANA                          = 0,			//��,����	
	POWER_ENERGY                        = 1,			//����,����	
	MAX_POWERS					
};

//ս����������еĸ��ְٷֱ�
enum Combat_Rate
{
	COMBAT_RATE_CRIT				= 0,				//������
	COMBAT_RATE_EVA					= 1,				//������
	MAX_COMBAT_RATE
};

//��������
enum Bag_Type
{
	BAG_TYPE_MAIN_BAG			= 0,	//������
	BAG_TYPE_EQUIP				= 1,	//������װ������
	BAG_TYPE_EQUIP_BAG			= 2,	//��װ���İ���
	BAG_TYPE_GEM				= 3,	//����Ʒ�İ���
	BAG_TYPE_GEM_BAG			= 4,	//�ű�ʯ�İ���

	MAX_BAG						= 20,	//Ԥ��20��
};

//������չ����
enum Bag_Extension_Type
{
	BAG_EXTENSION_TYPE_AUTO		= 0,	//�Զ�����
	BAG_EXTENSION_TYPE_GOLD		= 1,	//Ԫ������
};

//��ȫ���޸�����
enum Safety_Code_Modify_Type
{
	SAFETY_CODE_MODIFY_TYPE_CODE		= 0,	//�����޸�
	SAFETY_CODE_MODIFY_TYPE_QUESTION	= 1,	//��ȫ�����޸�
};

// ��Դ�����
enum Item_Loot_Resource 
{
	Item_Loot_Gold_Ingot = 1,	//Ԫ��
	Item_Loot_Bind_Gold = 2,	//��Ԫ��
	Item_Loot_Silver = 3,	//����
	
	Item_Loot_Renown = 5,	//����
	Item_Loot_Honor = 6,	//����
	Item_Loot_Exploit  = 7,	//��ѫ
	Item_Loot_Contrib = 8,	//���幱��
	Item_Loot_Exp = 104,		//����
	Item_Loot_Mount_Exp = 10,	//���ﾭ��
	Item_Loot_QI = 13,	//����
	Item_Loot_BEAST = 14,	//����
	Item_Loot_GEM = 15,	//��ʯ����
};

//��������
enum Money_Type
{
	MONEY_TYPE_GOLD_INGOT			= 1,	//Ԫ��
	MONEY_TYPE_BIND_GOLD			= 2,	//��Ԫ��
	MONEY_TYPE_SILVER				= 3,	//���ϵ�����
	MONEY_TYPE_SILVER_WAREHOUSE		= 4,	//�ֿ������

	MAX_MONEY_TYPE					= 22,
};

//��������
enum Base_Attr
{
	BASE_ATTR_HP			= 0,					//����
	BASE_ATTR_DAMAGE		= 1,					//����
	BASE_ATTR_ARMOR			= 2,					//����
	BASE_ATTR_HIT			= 3,					//����
	BASE_ATTR_DODGE			= 4,					//����
	BASE_ATTR_CRIT			= 5,					//����
	BASE_ATTR_CRIT_RESIST	= 6,					//����
	BASE_MOVE_SPEED			= 7,					//����
	BASE_ATTACK_SPEED		= 8,					//����
	MAX_BASE_ATTR
};

//Ӧ�÷��������������ö��
//0�������������� Լ���������Է���ö�ٵ������
enum Equip_Attr_Type
{
	EQUIP_ATTR_NONE			= 0,		//������
	EQUIP_ATTR_MAX_HEALTH = 1,	//�������
	EQUIP_ATTR_DAMAGE = 2,	//������
	EQUIP_ATTR_ARMOR = 3,	//������
	EQUIP_ATTR_HIT = 4,	//����
	EQUIP_ATTR_MISS = 5,	//����
	EQUIP_ATTR_CRIT = 6,	//����
	EQUIP_ATTR_TOUGH = 7,	//����
	EQUIP_ATTR_ATTACK_SPEED = 8,	//�����ٶ�
	EQUIP_ATTR_MOVE_SPEED = 9,	//�ƶ��ٶ�
	EQUIP_ATTR_IGNORE_ARMOR = 10,	//���ӷ���
	EQUIP_ATTR_IGNORE_MISS = 11,	//��������
	EQUIP_ATTR_RECOVERY = 12,	//����ֵ�ظ�
	EQUIP_ATTR_DAMAGE_AMPLIFY_RATE = 13,	//�˺�����(��ֱ�)
	EQUIP_ATTR_DAMAGE_RESIST_RATE = 14,	//�˺�����(��ֱ�)
	EQUIP_ATTR_DAMAGE_RETURN_RATE = 15,	//�����˺�(��ֱ�)
	EQUIP_ATTR_VAMPIRIC_RATE = 16,	//��Ѫ�⻷(��ֱ�)
	EQUIP_ATTR_RECOVERY_RATE = 17,	//�ظ�Ч��(��ֱ�)
	EQUIP_ATTR_CRIT_RATE = 18,	//������(��ֱ�)
	EQUIP_ATTR_CRIT_RESIST_RATE = 19,	//������(��ֱ�)
	EQUIP_ATTR_CRIT_DAM_RATE = 20,	//�����˺�����(��ֱ�)
	EQUIP_ATTR_CRIT_RESIST_DAM_RATE = 21,	//�����˺�����(��ֱ�)
	EQUIP_ATTR_HIT_RATE = 22,	//������(��ֱ�)
	EQUIP_ATTR_MISS_RATE = 23,	//������(��ֱ�)
	EQUIP_ATTR_STUN_RATE = 24,	//ѣ��
	EQUIP_ATTR_ROOTS_RATE = 25,	//����
	EQUIP_ATTR_SILENCE_RATE = 26,	//��Ĭ
	EQUIP_ATTR_CHAOS_RATE = 27,	//����
	EQUIP_ATTR_CHARM_RATE = 28,	//�Ȼ�
	EQUIP_ATTR_CONTROL_ENHANCE_RATE = 29,	//������ǿ
	EQUIP_ATTR_CONTROL_RESIST_RATE = 30,	//���Ƽ���
	EQUIP_ATTR_STRENGTH_ARMOR = 31,	//ǿ������

	MAX_EQUIP_ATTR
};

//��Ʒ��������ö�٣���Ʒ�������Խ���MAX_EQUIP_ATTR���棩
enum EItemOtherAttrType
{
	ITEM_OTHER_ATTR_FAIL_TIME				= MAX_EQUIP_ATTR,						//ʧЧʱ��
	ITEM_OTHER_ATTR_STRONG_LV				= ITEM_OTHER_ATTR_FAIL_TIME + 1,		//ǿ���ȼ�
	ITEM_OTHER_ATTR_STRONG_FAIL_COUNT		= ITEM_OTHER_ATTR_STRONG_LV + 1,		//ǿ��ʧ�ܴ���
	ITEM_OTHER_ATTR_FORCE					= ITEM_OTHER_ATTR_STRONG_FAIL_COUNT + 1,//ս����
};

//�����幫��CD����
enum Spell_CD_Type
{
	SPELL_CD_BASE = 0,
	SPELL_CD_SPECIAL = 1,
	MAX_SPELL_CD_TYPE
};

//����� ƫ����
enum QuestSlotOffsets
{
	QUEST_ID_OFFSET			= 0,
	QUEST_STATE_OFFSET		= 1,
	QUEST_COUNTS_OFFSET		= 2,	
	QUEST_COUNTS_OFFSET_1   = 3,
	QUEST_COUNTS_OFFSET_2   = 4,
	QUEST_COUNTS_OFFSET_3   = 5,
	QUEST_TIME_OFFSET		= 6,
	QUEST_FLAG_OFFSET		= 7,	//bit��־λ ������QuestSlotFlags
	MAX_QUEST_OFFSET
};

enum QuestSlotFlags
{
	QUEST_SLOT_FLAGS_REWARD		= 0,	//�Ƿ���ȡ��������
	QUEST_SLOT_FLAGS_EXPLORE	= 1,	//�Ƿ���̽��
};

#define MAX_QUEST_LOG_SIZE 32			//����۵�����
#define QUEST_OBJECTIVES_COUNT 8		//��Ʒ������ɱ���������������
#define QUEST_REWARD_CHOICES_COUNT 6
#define QUEST_REWARDS_COUNT 4

#define QUEST_LOW_LEVEL_HIDE_DIFF 4

#define  QUEST_ITEMS_COUNTS 10		//������Ʒ�������
#define  QUEST_COMPLETE_LIST 200	//����������б�ĳ���


#define BINLOG_STRING_FIELD_GUID 0	//����binlog��guidλ��
#define BINLOG_STRING_FIELD_NAME 1	//����binlog��nameλ��
#define BINLOG_STRING_FIELD_VERSION 2 //����binlog�İ汾��Ϣλ��
#define BINLOG_STRING_FIELD_OWNER 3	//����binlog��ownerλ��


//ս��Ʒ�±�
enum ELootStruct
{
	LOOT_PUBLIC_INT_START_POS		= 0,								//grid��ʼ����
	LOOT_PUBLIC_INT_END_POS			= 1,								//grid��������
	LOOT_PUBLIC_INT_BEGIN			= 2,								//ս��Ʒ������ʼ���±�

	LOOT_PUBLIC_INT_ENTRY			= 0,								//ս��Ʒģ��
	LOOT_PUBLIC_INT_MONEY_SUM		= LOOT_PUBLIC_INT_ENTRY + 1,		//��Ǯ����
	MAX_LOOT_PUBLIC_INT_FIELD,

	LOOT_PUBLIC_STR_OWNER			= 0,
	MAX_LOOT_PUBLIC_STR_FIELD,

	LOOT_PRIVATE_INT_FAIL_TIME		= 0,								//ʰȡ�Ժ����ƷʧЧʱ��
	LOOT_PRIVATE_INT_EXIST_TIME		= LOOT_PRIVATE_INT_FAIL_TIME + 1,	//ս��Ʒ���ʱ��
	LOOT_PRIVATE_INT_OWNER_TIME		= LOOT_PRIVATE_INT_EXIST_TIME + 1,	//ս��Ʒӵ���߱���ʱ��
	LOOT_PRIVATE_INT_FLAG			= LOOT_PRIVATE_INT_OWNER_TIME + 1,	//��־λ
	MAX_LOOT_PRIVATE_INT_FIELD,

	LOOT_PRIVATE_STRING_CREATE_BY	= 0,								//ս��Ʒ�����GUID
	LOOT_PRIVATE_STRING_CREATE_NAME	= 1,								//ս��Ʒ���������
	MAX_LOOT_PRIVATE_STRING,

	LOOT_STR_FIELD_BEGIN = BINLOG_STRING_FIELD_OWNER + 1,				//ս��Ʒ�ַ�����ʼ�±�
};

//ս��Ʒ��־λ
enum ELootFlag
{
	LOOT_FLAG_GET_ITEM_NOTICE				= 0,						//ʰ����Ʒ�Ƿ���Ҫ����
	LOOT_FLAG_ITEM_BIND						= 1,						//ս��Ʒ�Ƿ��
};

#define PLAYER_PASSIVE_SPELL_MAX_COUNT 100		// �������ܸ���

//����ܷ���ĳ�µ�flagƫ�ƶ���
enum EUintCanDoOffsetType
{
	UNIT_CANDO_OFFSET_TYPE_CANT_CAST				= 0,		//����ʩ��
	UNIT_CANDO_OFFSET_TYPE_CANT_MOVE				= 1,		//�����ƶ�
};


enum EUnitFields
{	
	UNIT_FIELD_BYTE_0					= 0,											//0:����ID��1������״̬��2���ƶ��ٶȣ�3��������ȼ�
	UNIT_FIELD_BYTE_1					= UNIT_FIELD_BYTE_0 + 1,						//0����ɫ���ͣ�1����Ӫ��2�����壬3��ְҵ
	UNIT_FIELD_BYTE_2					= UNIT_FIELD_BYTE_1 + 1,						//0������ʱ�䣬1�����ѵȼ���2����Ѹ��3����ҳƺ�
	UNIT_FIELD_BYTE_3					= UNIT_FIELD_BYTE_2 + 1,						//0: ͷ��1�����ͣ�2��GM�ȼ���3���´θ����Ƿ��б���buff
	UNIT_FIELD_BYTE_4					= UNIT_FIELD_BYTE_3 + 1,						//0��Ԥ����1����ǰ����ģ��id��2��Ƥ������ 3��Ԥ��
	UNIT_FIELD_MOUNT_LEVEL				= UNIT_FIELD_BYTE_4 + 1,						//4��bytes(0:��ǰ������� 1:��ǰ�����Ǽ�,2:��ǰ�����Ƿ���ˣ�3:��ǰ�û�id)
	UNIT_FIELD_DIVINE_ID				= UNIT_FIELD_MOUNT_LEVEL + 1,					//���id
	UNIT_FIELD_UINT16_0					= UNIT_FIELD_DIVINE_ID + 1,						//0������ģ�壬1������ȼ�
	UNIT_FIELD_UINT16_1					= UNIT_FIELD_UINT16_0 + 1,						//0����ͼID��1�����1v1��ʤ����
	UNIT_FIELD_UINT16_2					= UNIT_FIELD_UINT16_1 + 1,						//0:��ұ������ʱ�յ�ƥ����Ϣ�и��ı�� 1:���ϱ���ɼ���Ӫ���
	UNIT_FIELD_SELF_DEFENSE_GUID		= UNIT_FIELD_UINT16_2 + 1,				//����ģʽ�¿��Թ��������intguid

	UNIT_FIELD_FLAGS					= UNIT_FIELD_SELF_DEFENSE_GUID + 1,						//�������ϵı�־λ
	GO_FIELD_FLAGS						= UNIT_FIELD_FLAGS + 1,							//��Ϸ�����һЩ��ʶλ
	GO_FIELD_DATA						= GO_FIELD_FLAGS + 1,							//��̬�����ֶ�,Ŀǰ����Ϊ4��int
	UNIT_FIELD_NPC_FLAG					= GO_FIELD_DATA + 4,							//NPC��ʶ
	UNIT_FIELD_INSTANCE_ID				= UNIT_FIELD_NPC_FLAG + 1,						//��ͼʵ��ID
	UNIT_FIELD_EQUIPMENT_COAT			= UNIT_FIELD_INSTANCE_ID + 1,						//����ģ��
	UNIT_FIELD_EQUIPMENT_MAIN_WEAPON	= UNIT_FIELD_EQUIPMENT_COAT + 1,				//��������
	UNIT_FIELD_BUFF						= UNIT_FIELD_EQUIPMENT_MAIN_WEAPON +1,						//BUFFID

	//ע���ˣ���������Ҫ�·����±���� UNIT_FIELD_BUFFǰ��,UNIT_FIELD_BUFF_TM������±��߶���
	UNIT_FIELD_BUFF_TM					= UNIT_FIELD_BUFF + 8,							//BUFFʱ�䣨������⿪ʼ��
	UNIT_FIELD_BUFF_RESERVE				= UNIT_FIELD_BUFF_TM + 8,						//BUFFԤ��ֵ
	UNIT_FIELD_BUFF_EFFECT_ID			= UNIT_FIELD_BUFF_RESERVE + MAX_UNIT_BUFF,		//BUFFЧ��id
	UNIT_FIELD_BUFF_CASTER_GUID			= UNIT_FIELD_BUFF_EFFECT_ID + MAX_UNIT_BUFF,	//buffʩ����guid

	UNIT_FIELD_FORCE						= UNIT_FIELD_BUFF_CASTER_GUID + MAX_UNIT_BUFF,	//ս����
	UNIT_FIELD_HEALTH						= UNIT_FIELD_FORCE + 2,				//��ǰ����	

	UNIT_FIELD_MAX_HEALTH = UNIT_FIELD_HEALTH + 1,	//�������
	UNIT_FIELD_DAMAGE = UNIT_FIELD_MAX_HEALTH + 1,	//������
	UNIT_FIELD_ARMOR = UNIT_FIELD_DAMAGE + 1,	//������
	UNIT_FIELD_HIT = UNIT_FIELD_ARMOR + 1,	//����
	UNIT_FIELD_MISS = UNIT_FIELD_HIT + 1,	//����
	UNIT_FIELD_CRIT = UNIT_FIELD_MISS + 1,	//����
	UNIT_FIELD_TOUGH = UNIT_FIELD_CRIT + 1,	//����
	UNIT_FIELD_ATTACK_SPEED = UNIT_FIELD_TOUGH + 1,	//�����ٶ�
	UNIT_FIELD_MOVE_SPEED = UNIT_FIELD_ATTACK_SPEED + 1,	//�ƶ��ٶ�
	UNIT_FIELD_IGNORE_ARMOR = UNIT_FIELD_MOVE_SPEED + 1,	//���ӷ���
	UNIT_FIELD_IGNORE_MISS = UNIT_FIELD_IGNORE_ARMOR + 1,	//��������
	UNIT_FIELD_RECOVERY = UNIT_FIELD_IGNORE_MISS + 1,	//����ֵ�ظ�
	UNIT_FIELD_DAMAGE_AMPLIFY_RATE = UNIT_FIELD_RECOVERY + 1,	//�˺�����(��ֱ�)
	UNIT_FIELD_DAMAGE_RESIST_RATE = UNIT_FIELD_DAMAGE_AMPLIFY_RATE + 1,	//�˺�����(��ֱ�)
	UNIT_FIELD_DAMAGE_RETURN_RATE = UNIT_FIELD_DAMAGE_RESIST_RATE + 1,	//�����˺�(��ֱ�)
	UNIT_FIELD_VAMPIRIC_RATE = UNIT_FIELD_DAMAGE_RETURN_RATE + 1,	//��Ѫ�⻷(��ֱ�)
	UNIT_FIELD_RECOVERY_RATE = UNIT_FIELD_VAMPIRIC_RATE + 1,	//�ظ�Ч��(��ֱ�)
	UNIT_FIELD_CRIT_RATE = UNIT_FIELD_RECOVERY_RATE + 1,	//������(��ֱ�)
	UNIT_FIELD_CRIT_RESIST_RATE = UNIT_FIELD_CRIT_RATE + 1,	//������(��ֱ�)
	UNIT_FIELD_CRIT_DAM_RATE = UNIT_FIELD_CRIT_RESIST_RATE + 1,	//�����˺�����(��ֱ�)
	UNIT_FIELD_CRIT_RESIST_DAM_RATE = UNIT_FIELD_CRIT_DAM_RATE + 1,	//�����˺�����(��ֱ�)
	UNIT_FIELD_HIT_RATE = UNIT_FIELD_CRIT_RESIST_DAM_RATE + 1,	//������(��ֱ�)
	UNIT_FIELD_MISS_RATE = UNIT_FIELD_HIT_RATE + 1,	//������(��ֱ�)
	UNIT_FIELD_STUN_RATE = UNIT_FIELD_MISS_RATE + 1,	//ѣ��
	UNIT_FIELD_ROOTS_RATE = UNIT_FIELD_STUN_RATE + 1,	//����
	UNIT_FIELD_SILENCE_RATE = UNIT_FIELD_ROOTS_RATE + 1,	//��Ĭ
	UNIT_FIELD_CHAOS_RATE = UNIT_FIELD_SILENCE_RATE + 1,	//����
	UNIT_FIELD_CHARM_RATE = UNIT_FIELD_CHAOS_RATE + 1,	//�Ȼ�
	UNIT_FIELD_CONTROL_ENHANCE_RATE = UNIT_FIELD_CHARM_RATE + 1,	//������ǿ
	UNIT_FIELD_CONTROL_RESIST_RATE = UNIT_FIELD_CONTROL_ENHANCE_RATE + 1,	//���Ƽ���
	UNIT_FIELD_STRENGTH_ARMOR = UNIT_FIELD_CONTROL_RESIST_RATE + 1,	//ǿ������

	UNIT_FIELD_ATTRIBUTE_END				= UNIT_FIELD_STRENGTH_ARMOR + 1,	// ���Խ���
	UNIT_FIELD_ANGER						= UNIT_FIELD_ATTRIBUTE_END,	//��ŭֵ
	UNIT_FIELD_USE_RESPAWN_MAPID			= UNIT_FIELD_ANGER	+ 1,				//ʹ�ø���ĵ�ͼid

	UNIT_FIELD_PROCESS_TIME					= UNIT_FIELD_USE_RESPAWN_MAPID + 1,			// �����������ʱ���
	UNIT_FIELD_PROCESS_SECONDS				= UNIT_FIELD_PROCESS_TIME + 1,  // �����ܹ���Ҫʱ��	
	
	UINT_FIELD_BOSS_DATA					= UNIT_FIELD_PROCESS_SECONDS + 1,			//boss����byte 0:boss״̬ 1:bossǰһ״̬ 2:boss����(���ε��������;)
	UINT_FIELD_BOSS_DATA1					= UINT_FIELD_BOSS_DATA + 1,		//boss����byte 0:��ǰ����x 1:��ǰ����y 2:��һ����x 3:��һ����y(���ε��������;)
	UINT_FIELD_VIEW_MODE					= UINT_FIELD_BOSS_DATA1,		//�Ƿ��ǹۿ�ģʽ

	UINT_FIELD_VIRTUAL_CAMP					= UINT_FIELD_VIEW_MODE + 1,		//������Ӫ

	UINT_FIELD_XIANFU_INFO					= UINT_FIELD_VIRTUAL_CAMP + 1,	//����ɸ�����Ϣ4bytes (0:��������, 1:��������)

	UINT_FIELD_VIP_LEVEL					= UINT_FIELD_XIANFU_INFO + 1,	//VIP�ȼ�
	UINT_FIELD_VIP_TIME_OUT					= UINT_FIELD_VIP_LEVEL + 1,		//VIP��ʱʱ��

	UINT_FIELD_VAMPIRIC						= UINT_FIELD_VIP_TIME_OUT + 1,	//��ǰս������Ѫֵ

	UINT_INT_FIELD_ILLUSION					= UINT_FIELD_VAMPIRIC + 2,	//��ɫ�û�

	UINT_FIELD_BOOS_CUR_SPELLID				= UINT_INT_FIELD_ILLUSION + 1,	//��ǰ�����ͷŵ���������idUNIT_INT_FIELD_APPEARANCE
	UINT_FIELD_BOOS_CUR_SPELL_TIME			= UINT_FIELD_BOOS_CUR_SPELLID + 1,	//ǰһ�����ܽ�����ʱ���
	UINT_FIELD_BOOS_CUR_SPELL_LAST_COUNT	= UINT_FIELD_BOOS_CUR_SPELL_TIME + 1,	// ������������

	UINT_INT_FIELD_PASSIVE_SPELL_START		= UINT_FIELD_BOOS_CUR_SPELL_LAST_COUNT + 1,	//�������ܿ�ʼ
	UINT_INT_FIELD_PASSIVE_SPELL_END		= UINT_INT_FIELD_PASSIVE_SPELL_START + PLAYER_PASSIVE_SPELL_MAX_COUNT,	//�������ܽ���

	UINT_INT_FIELD_WINGS_RANK				= UINT_INT_FIELD_PASSIVE_SPELL_END,	//�������

	UNIT_INT_FIELD_APPEARANCE				= UINT_INT_FIELD_WINGS_RANK + 1,	// ���

	MAX_UNIT_FIELD,

	GO_STRING_FIELD_CREATED_BY		= BINLOG_STRING_FIELD_OWNER + 1,
	UNIT_STRING_FIELD_ALIAS_NAME	= GO_STRING_FIELD_CREATED_BY + 1,
	UNIT_STRING_FIELD_PICK_NAME		= UNIT_STRING_FIELD_ALIAS_NAME + 1,			//���ڲɼ������

	UNIT_STRING_FIELD_GROUP_PEACE_ID	= UNIT_STRING_FIELD_PICK_NAME + 1,			// ���id
	UNIT_STRING_FIELD_FACTION_GUID		= UNIT_STRING_FIELD_GROUP_PEACE_ID + 1,		// ����id

	MAX_UNIT_STRING_FIELD,
};


//��Ϸ��������
#define  GO_ENTRY_TELETEPORT 1		//���͵�
#define  GO_ENTRY_LOOT 9			//ս��Ʒ��Ϸ����

//��Ϸ��������
enum GameObject_Data
{
	//���͵�ר��
	GO_TELETEPORTER_TO_MAPID	= GO_FIELD_DATA,
	GO_TELETEPORTER_TO_X		= GO_TELETEPORTER_TO_MAPID + 1,
	GO_TELETEPORTER_TO_Y		= GO_TELETEPORTER_TO_X + 1,

	//���������Ϸ����
	GO_QUEST_ID_0				= GO_FIELD_DATA + 0,					//�������0
	GO_QUEST_ID_1				= GO_FIELD_DATA + 1,					//�������1
	GO_QUEST_ID_2				= GO_FIELD_DATA + 2,					//�������2
	GO_QUEST_ID_3				= GO_FIELD_DATA + 3,					//�������3

	GO_STRING_FIELD_CREATED_NAME	= UNIT_STRING_FIELD_ALIAS_NAME,		//ս��Ʒ������Name

	//��������ص�
	GO_GEAR_STATUS				= GO_FIELD_DATA,						//����״̬
	GO_GEAR_KILLER				= GO_FIELD_DATA + 1						//�����ƻ���
};

//����״̬ö��
enum GO_GEAR_STATUS_TYPE
{
	GO_GEAR_STATUS_START		= 1,			//���س�ʼ״̬
	GO_GEAR_STATUS_OPEN			= 2,			//���ش�
	GO_GEAR_STATUS_CLOSE		= 3,			//���عر�
	GO_GEAR_STATUS_END			= 4,			//���ؼ�����ʧ
	GO_GEAR_STATUS_MAX
};

//�������ϱ�ʶ�±�ö��
enum EUnitFlagsType
{
	UNIT_FIELD_FLAGS_CANT_CAST					= 0,		//��ʶ�Ƿ����ʩ��
	UNIT_FIELD_FLAGS_CANT_MOVE					= 1,		//��ʶ�Ƿ�����ƶ�
	UNIT_FIELD_FLAGS_BUFF_DAZUO					= 2,		//��ʶ�Ƿ����buff
	UNIT_FIELD_FLAGS_GUAJIBAOHU					= 3,		//��ʶ�Ƿ��ǹһ�����
	UNIT_FIELD_FLAGS_FACTION_LINGXIU			= 4,		//��������BUFF
	UNIT_FIELD_FLAGS_FACTION_GUWU				= 5,		//���ɹ���BUFF
	UNIT_FIELD_FLAGS_IS_BOSS_CREATURE			= 6,		//��ʶ�Ƿ��Ǹ���boss��
	UNIT_FIELD_FLAGS_USE_GAMEOBJECT				= 7,		//��ʶ�Ƿ�ʹ����Ϸ����
	UNIT_FIELD_FLAGS_IS_FLZ_PUB_CREATURE		= 8,		//��ʶ�Ƿ������ƹݹ�
	UNIT_FIELD_FLAGS_QUEST_FOLLOW_CREATUR		= 9,		//������ˢ�����ĸ�˭����������ʱɾ��
	UNIT_FIELD_FLAGS_IS_PVP						= 10,		//�Ƿ���PVP
	UNIT_FIELD_FLAGS_IS_FIELD_BOSS_CREATURE		= 11,		//��ʶ�Ƿ���Ұ��boss��
	UNIT_FIELD_FLAGS_IS_INVISIBLE_SPELL			= 12,		//���صļ���NPC
};

//������ר�õ����״̬�±�ö��
enum EPlayerScenedFlasType
{
	PLAYER_SCENED_FLAS_HUNG_UP					= 0,		//�һ�״̬
	PLAYER_SCENED_FLAS_PVP_STATE				= 1,		//PVP״̬
	PLAYER_SCENED_FLAGS_FUBEN_HUNG_UP			= 2,		//��ʶ�Ƿ񸱱������һ�״̬
};

//���Ӧ�÷���־λ�����ѡ��
enum EPlayerAppdFlags
{
	PLAYER_APPD_INT_FIELD_FLAGS_IS_ZIBAO				= 0,					//����Ƿ��Ա�
	PLAYER_APPD_INT_FIELD_FLAGS_YEYOU_ONLINE			= 1,					//ҳ���Ƿ����ߣ��ͻ����õ�
	PLAYER_APPD_INT_FIELD_FLAGS_PHONE_ONLINE			= 2,					//�����Ƿ����ߣ��ͻ����õ�
	PLAYER_APPD_INT_FIELD_FLAGS_FROM_KUAFU				= 3,					//����Ƿ��pk�ص���Ϸ��
	PLAYER_APPD_INT_FIELD_FLAGS_GIFT_CREATE				= 4,					//����Ƿ��Ѵ���
	PLAYER_APPD_INT_FIELD_FLAGS_LIMIT_CREATE			= 5,					//��ʱ��Ƿ��Ѵ���
	PLAYER_APPD_INT_FIELD_FLAGS_IS_FIRST_RECHARGE		= 6,					//�Ƿ��Ѿ��׳�
	PLAYER_APPD_INT_FIELD_FLAGS_NEW_PLAYER				= 7,					//�Ƿ�����ң���������򷢷�����ȵȡ���
	PLAYER_APPD_INT_FIELD_FLAGS_SAFETY_CODE_CHECK		= 8,					//��ʶ��ȫ����֤�Ƿ�ͨ��
	PLAYER_APPD_INT_FIELD_FLAGS_AUTO_GROUP				= 9,					//����Ƿ��Զ��������
	PLAYER_APPD_INT_FIELD_FLAGS_IS_HOSTING_LOGIN		= 10,					//�Ƿ����йܵ�¼
	PLAYER_APPD_INT_FIELD_FLAGS_IS_HOSTING_APPLY		= 11,					//�Ƿ��й�������
	PLAYER_APPD_INT_FIELD_FLAGS_SOCIAL_CREATE			= 12,					//�罻ϵͳ�Ƿ��Դ���	
	PLAYER_APPD_INT_FIELD_FLAGS_ITEM_CREATE				= 13,					//��Ʒbinlog�Ƿ񴴽�
	PLAYER_APPD_INT_FIELD_FLAGS_LOGICAL_CREATE			= 14,					//ҵ���߼�binlog�Ƿ񴴽�
	PLAYER_APPD_INT_FIELD_FLAGS_SPELL_CREATE			= 15,					//����binlog�Ƿ񴴽�
	PLAYER_APPD_INT_FIELD_FLAGS_INSTANCE_CREATE			= 16,					//����binlog�Ƿ񴴽�
	PLAYER_APPD_INT_FIELD_FLAGS_QUEST_CREATE			= 17,					//����binlog�Ƿ񴴽�
};

//����Ǳ��������
enum QianLi_Type
{
	QIANLI_TYPE_LILIANG                     = 0,	//����
	QIANLI_TYPE_TIZHI				        = 1,	//����
	QIANLI_TYPE_SHENFA						= 2,	//��
	QIANLI_TYPE_FANGYU						= 3,	//��
	MAX_QIANLI_TYPE					 
};

//�ͻ���ʹ�õ������±�����
#define MAX_CLIENT_UINT32_COUNT 100
//�ͻ���ʹ�õ��ַ����±�����
#define MAX_CLIENT_STRING_COUNT 20

#define MAX_ITEMS_CD_COUNT 20				//��Ʒ��cd�������(20������ʱ���)
#define MAX_ITEM_USED_COUNT 5				//��Ʒ��cdʹ�ô���(5��byte�������)


#define MAX_SPELL_CAPACITY 20				   //���ӵ�еļ�����
//����
enum ESpellBASE
{
	SPELL_BASE_LEVEL = 0,						//���ܵȼ�
	SPELL_BASE_FORCE = 1,						//���ܵȼ���Ӧ��ս����
	SPELL_BASE_ID	 = 2,						//����ID
	MAX_SPELLBASE, 
};

enum Functional_Spell
{
	FUNCTIONAL_QING_GONG 	= 1,	//�Ṧ
	FUNCTIONAL_TI_YUN_ZONG = 2,		//������
	FUNCTIONAL_RIDE		= 3,		//���
	FUNCTIONAL_DA_ZUO		= 4,	//����
};

#define PLAYER_SLOT_SPELL_MAX_COUNT 12			// ��Ҽ��ܲ���Ϣ����
#define PLAYER_IMPORTANT_CD_COUNT 20			// �����Ҫ���ܵ�CD

// ��Ҽ��ܲ۵ļ�����Ϣ
enum SLOT_SPELL_ATTR
{
	SHORT_SLOT_SPELL_ID		= 0,	//���ܲ��еļ���id	ռһ��short

	BYTE_SLOT_SPELL_LV		= 2,	//���ܲ��еļ���lv	ռһ��byte
	BYTE_SLOT				= 3		//���ܲ۵�λ��		ռһ��byte
};

// ���ܼ��ʽ
enum SPELL_ACTIVE_WAYS
{
	SPELL_ACTIVE_BY_LEVEL	= 0,	//�ȼ�����
	SPELL_ACTIVE_BY_QUEST	= 1,	//���񼤻�
	SPELL_ACTIVE_BY_ITEM	= 2,	//���߼���
};


// Ҫ��binlog�д�CD����Ҫ����CD��Ϣ
enum IMPORTANCE_SPELL_CD_INFO
{
	IMPORTANT_SPELL_ID = 0,	//����id
	IMPORTANT_SPELL_CD = 1,	//����CD
	MAX_IMPORTANT_SPELL_ATTR_COUNT
};

// Ҫ��binlog�д濪�����ܵ���Ϣ
enum OPEN_MENU_INFO
{
	OPEN_MENU_MAIN_ID = 0,	//���˵�id
	OPEN_MENU_SUB_FLAG = 1,	//�Ӳ˵�flag
	MAX_OPEN_MENU_ATTR_COUNT
};

enum GiftPacksType
{
	GIFT_PACKS_TYPE_ITEM_GIVE = 0,						//��GM��������
	GIFT_PACKS_TYPE_SYSTEM_COMPENSATION = 1,			//ϵͳ����
	GIFT_PACKS_TYPE_BAG_FULL = 2,						//��������
	GIFT_PACKS_TYPE_LEVEL_RANK = 3,						//���а�
	GIFT_PACKS_TYPE_WORLD_BOSS = 4,						//����BOSS
	GIFT_PACKS_TYPE_3V3_WEEK = 5,						//3v3�ܽ���
	GIFT_PACKS_TYPE_3V3_MONTH = 6,						//3v3�½�������λ������
	GIFT_PACKS_TYPE_DOUJIAN_DAY = 7,						//����̨ÿ�ս���
	GIFT_PACKS_TYPE_FACTION_BOSS = 8,					//����boss����
	GIFT_PACKS_TYPE_FACTION_GIFT_RANK = 9,				//�����������н���
	GIFT_PACKS_TYPE_ACT_RANK = 10,				//�������н���
};

enum SCENED_APPD_DO_SOMETHING_TYPE
{
	SCENED_APPD_ENTER_DAILY_INSTANCE = 1,	//�����ճ�����
	SCENED_APPD_ENTER_VIP_INSTANCE = 2,		//����VIP����
	SCENED_APPD_USE_ITEM = 3,				//ʹ��Ѫƿ
	SCENED_APPD_USE_RESPAWN_ITEM = 4,		//ʹ�ø��
	SCENED_APPD_ENTER_TRIAL_INSTANCE = 5,	//��������������
	SCENED_APPD_PASS_TRIAL_INSTANCE = 6,	//ͨ������������
	SCENED_APPD_PASS_VIP_INSTANCE = 7,		//ͨ��VIP����
	SCENED_APPD_ADD_ENEMY = 8,				//���ӳ���
	SCENED_APPD_ENTER_RES_INSTANCE = 9,		//������Դ����
	SCENED_APPD_ADD_MAIL = 10,				//�����ʼ�
	SCENED_APPD_PASS_RES_INSTANCE = 11,		//ͨ����Դ����

	SCENED_APPD_KILL_MONSTER	= 12,		//ɱ��
	SCENED_APPD_JOIN_FIELD_BOSS	= 13,		//�μ�Ұ��BOSS
	SCENED_APPD_GAMEOBJECT		= 14,		//�ɼ���Ʒ
	SCENED_APPD_TALK			= 15,		//�Ի�

	SCENED_APPD_RIDE			= 16,		//���
	SCENED_APPD_GOLD_RESPAWN	= 17,		//Ԫ������

	SCENED_APPD_DOUJIANTAI				= 18,		//����̨���
	SCENED_APPD_KILL_MONSTER_COLLECT	= 19,		//ɱ���ռ���Ʒ
	SCENED_APPD_XIULIANCHANG			= 20,		//�������Ӷ���
	SCENED_APPD_XIANFU_PRACTISE			= 21,		//�ɸ�����

	SCENED_APPD_ADD_OFFLINE_RISK_REWARD	= 22,		//����ð�����罱��
	SCENED_APPD_PASS_WORLD_RISK			= 23,		//ͨ��ð������

	SCENED_APPD_ENTER_MASS_BOSS_INSTANCE = 24,		//����ȫ��boss����

	SCENED_APPD_FACTION_TOWER_WIN		= 25,		//�޾�Զ�� ʤ��

	SCENED_APPD_SINGLE_PVP_RESULT		= 26,		// ��λ�����

	SCENED_APPD_ENTER_QUALIFY_INSTANCE = 27,	//������λ��

	SCENED_APPD_ENTER_FACTION_TOWER_INSTANCE	= 28,	//�������Զ��
};

enum APPD_SCENED_DO_SOMETHING_TYPE
{
	APPD_SCENED_SWEEP_TRIAL_INSTANCE = 1,	//ɨ������������
	APPD_SCENED_SWEEP_VIP_INSTANCE = 2,		//ɨ��VIP����
	APPD_SCENED_RESPAWN = 3,				//Ԫ������
	APPD_SCENED_NEAR_BY_CHAT = 4,			//��������
	APPD_SCENED_ADD_EXP = 5,				//�������Ӿ���
	
	APPD_SCENED_CLEAR_FIELD_BOSS = 6,		//����������Ұ��BOSS
	APPD_SCENED_REBORN_FIELD_BOSS = 7,		//������ˢ��Ұ��

	APPD_SCENED_WORLD_BOSS_WAITING = 8,		//��������BOSS�ȴ�����
	APPD_SCENED_FIGHT_WORLD_BOSS = 9,		//����ս��ʼ����BOSS
	APPD_SCENED_WORLD_BOSS_END = 10,		//����BOSS����
	APPD_SCENED_WORLD_BOSS_ENTER = 11,		//��������BOSS����
	APPD_SCENED_REMIND_INSTANCE_ENTER = 12,	//����ԭ�ظ�������

	APPD_SCENED_MASS_BOSS_REBORN = 13, //ȫ��boss����
};

enum INSTANCE_SUB_TYPE
{
	INSTANCE_SUB_TYPE_VIP					= 1,		//vip����
	INSTANCE_SUB_TYPE_TRIAL					= 2,		//����������
	INSTANCE_SUB_TYPE_WORLD_BOSS			= 3,		//����BOSS
	INSTANCE_SUB_TYPE_RES					= 4,		//��Դ����
	INSTANCE_SUB_TYPE_KUAFU_3V3				= 5,		//���3v3
	INSTANCE_SUB_TYPE_XIANFU				= 6,		//�ɸ��ᱦ
	INSTANCE_SUB_TYPE_DOUJIANTAI			= 7,		//����̨
	INSTANCE_SUB_TYPE_XIANFU_EXPERIENCE		= 8,		//�ɸ�����
	INSTANCE_SUB_TYPE_XIULIAN				= 9,		//������
	INSTANCE_SUB_TYPE_PLOT					= 10,		//ԭ�ؾ��鸱��
	INSTANCE_SUB_TYPE_MASS_BOSS				= 11,		//ȫ��boss
	INSTANCE_SUB_TYPE_KUAFU_GROUP			= 12,		//�����Ӹ���
	INSTANCE_SUB_TYPE_FACTION_BOSSDEFENSE	= 13,		//����������ս
	INSTANCE_SUB_TYPE_FACTION_TOWER			= 14,		//�����޾�Զ��
	INSTANCE_SUB_TYPE_QUALIFY				= 15,		//��λ��
	INSTANCE_SUB_TYPE_RISK					= 16,		//����ð��
};

// ����Ƶ��
enum CHAT_CHANNEL
{
	CHAT_CHANNEL_SYSTEM		= 0,	//ϵͳƵ��
	CHAT_CHANNEL_WORLD		= 1,	//����Ƶ��
	CHAT_CHANNEL_NEARBY		= 2,	//����Ƶ��
	CHAT_CHANNEL_FAMILY		= 3,	//����Ƶ��
	CHAT_CHANNEL_GROUP		= 4,	//����Ƶ��
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


//���ɳ�Ա�����INT��Ϣ
enum EFactionDataIntGiftType
{
	FACTION_DATA_INT_GIFT_ID = 0,		//����ID
	FACTION_DATA_INT_GIFT_POINT = 1,	//��������������ֵ
	FACTION_DATA_INT_GIFT_FLAG_THANK = 2,		//��л��ʶ��Ϣ
	FACTION_DATA_INT_GIFT_TIME	= 3,	//����ʱ��
	FACTION_DATA_INT_GIFT_COUNT_ID = 4, //������ɵ��������
	MAX_FACTION_DATA_INT_GIFT,
};

//���ɳ�Ա�����STRING��Ϣ
enum EFactionDataStringGiftType
{
	FACTION_DATA_STRING_GIFT_GUID = 0,		//������guid
	FACTION_DATA_STRING_GIFT_MSG = 1,		//����������
	FACTION_DATA_STRING_GIFT_ITEM_LIST = 2,	//�����б�����	��Ʒ1 \2 ����1 \1 ��Ʒ2 \2 ����2
	FACTION_DATA_STRING_GIFT_REPLY_LIST = 3,	//�ظ���Ϣ�б�		���guid \2 ��Ϣ \2 �ظ����� \2 ʱ�� \1 ���guid \2 ��Ϣ \2 �ظ����� \2 ʱ��
	MAX_FACTION_DATA_STRING_GIFT,
};

//���ɳ�Ա����ظ�����ö��
enum EFactionDataReplyType
{
	FACTION_DATA_REPLY_TYPE_TEXT = 0, //�ı��ظ�
	FACTION_DATA_REPLY_TYPE_VOICE = 1, //�����ظ�
};

#define MAX_FACTION_DATA_GIFT_COUNT 150			//ÿ����������
#define MAX_FACTION_DATA_GIFT_REPLY_COUNT 200	//�ظ�����

#define MAX_FACTION_DATA_GIFT_CACHE_COUNT 1000		//���߸�л��¼����

//����±�
enum EPlayerFields
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//int ����
	//////////////////////////////////////////////////////////////////////////
	//��������
	PLAYER_FIELD_FD								= 0,												//���ڳ��������������Ӻ�
	PLAYER_FIELD_MERGE_DATA_INDEX				= PLAYER_FIELD_FD + 1,								//��Һϲ�����ʱ������������������±꣬0.Ԥ����1.�ص���2.������֤����
	PLAYER_FIELD_ENTRY							= PLAYER_FIELD_MERGE_DATA_INDEX + 1,				//ģ��
	PLAYER_FIELD_MAP_ID							= PLAYER_FIELD_ENTRY + 1,							//��ͼ
	PLAYER_FIELD_INSTANCE_ID					= PLAYER_FIELD_MAP_ID + 1,							//��ͼʵ��
	PLAYER_FIELD_LINE_NO						= PLAYER_FIELD_INSTANCE_ID + 1,						//��ͼ���ߺ�
	PLAYER_FIELD_POS_X							= PLAYER_FIELD_LINE_NO + 1,							//X����
	PLAYER_FIELD_POS_Y							= PLAYER_FIELD_POS_X + 1,							//Y����
	PLAYER_FIELD_ORIENTATION					= PLAYER_FIELD_POS_Y + 1,							//����
	PLAYER_FIELD_MOVESPEED						= PLAYER_FIELD_ORIENTATION + 1,						//������

	PLAYER_FIELD_LEVEL							= PLAYER_FIELD_MOVESPEED + 2,						//�ȼ�
	PLAYER_FIELD_BYTES_0						= PLAYER_FIELD_LEVEL + 1,							//�ĸ��ֽ�,�ֱ��� 0��ɫid,[1��Ӫ2����3ְҵ]
	PLAYER_FIELD_NPC_FLAG						= PLAYER_FIELD_BYTES_0 + 1,							//NPC��ʶ
	PLAYER_FIELD_DEATH_STATE					= PLAYER_FIELD_NPC_FLAG + 1,						//����״̬
	
	PLAYER_FIELD_HEALTH							= PLAYER_FIELD_DEATH_STATE + 1,						//��ǰ����
	PLAYER_FIELD_MAX_HEALTH = PLAYER_FIELD_HEALTH + 2,	//�������
	PLAYER_FIELD_DAMAGE = PLAYER_FIELD_MAX_HEALTH + 2,	//������
	PLAYER_FIELD_ARMOR = PLAYER_FIELD_DAMAGE + 2,	//������
	PLAYER_FIELD_HIT = PLAYER_FIELD_ARMOR + 2,	//����
	PLAYER_FIELD_MISS = PLAYER_FIELD_HIT + 2,	//����
	PLAYER_FIELD_CRIT = PLAYER_FIELD_MISS + 2,	//����
	PLAYER_FIELD_TOUGH = PLAYER_FIELD_CRIT + 2,	//����
	PLAYER_FIELD_ATTACK_SPEED = PLAYER_FIELD_TOUGH + 2,	//�����ٶ�
	PLAYER_FIELD_MOVE_SPEED = PLAYER_FIELD_ATTACK_SPEED + 2,	//�ƶ��ٶ�
	PLAYER_FIELD_IGNORE_ARMOR = PLAYER_FIELD_MOVE_SPEED + 2,	//���ӷ���
	PLAYER_FIELD_IGNORE_MISS = PLAYER_FIELD_IGNORE_ARMOR + 2,	//��������
	PLAYER_FIELD_RECOVERY = PLAYER_FIELD_IGNORE_MISS + 2,	//����ֵ�ظ�
	PLAYER_FIELD_DAMAGE_AMPLIFY_RATE = PLAYER_FIELD_RECOVERY + 2,	//�˺�����(��ֱ�)
	PLAYER_FIELD_DAMAGE_RESIST_RATE = PLAYER_FIELD_DAMAGE_AMPLIFY_RATE + 2,	//�˺�����(��ֱ�)
	PLAYER_FIELD_DAMAGE_RETURN_RATE = PLAYER_FIELD_DAMAGE_RESIST_RATE + 2,	//�����˺�(��ֱ�)
	PLAYER_FIELD_VAMPIRIC_RATE = PLAYER_FIELD_DAMAGE_RETURN_RATE + 2,	//��Ѫ�⻷(��ֱ�)
	PLAYER_FIELD_RECOVERY_RATE = PLAYER_FIELD_VAMPIRIC_RATE + 2,	//�ظ�Ч��(��ֱ�)
	PLAYER_FIELD_CRIT_RATE = PLAYER_FIELD_RECOVERY_RATE + 2,	//������(��ֱ�)
	PLAYER_FIELD_CRIT_RESIST_RATE = PLAYER_FIELD_CRIT_RATE + 2,	//������(��ֱ�)
	PLAYER_FIELD_CRIT_DAM_RATE = PLAYER_FIELD_CRIT_RESIST_RATE + 2,	//�����˺�����(��ֱ�)
	PLAYER_FIELD_CRIT_RESIST_DAM_RATE = PLAYER_FIELD_CRIT_DAM_RATE + 2,	//�����˺�����(��ֱ�)
	PLAYER_FIELD_HIT_RATE = PLAYER_FIELD_CRIT_RESIST_DAM_RATE + 2,	//������(��ֱ�)
	PLAYER_FIELD_MISS_RATE = PLAYER_FIELD_HIT_RATE + 2,	//������(��ֱ�)
	PLAYER_FIELD_STUN_RATE = PLAYER_FIELD_MISS_RATE + 2,	//ѣ��
	PLAYER_FIELD_ROOTS_RATE = PLAYER_FIELD_STUN_RATE + 2,	//����
	PLAYER_FIELD_SILENCE_RATE = PLAYER_FIELD_ROOTS_RATE + 2,	//��Ĭ
	PLAYER_FIELD_CHAOS_RATE = PLAYER_FIELD_SILENCE_RATE + 2,	//����
	PLAYER_FIELD_CHARM_RATE = PLAYER_FIELD_CHAOS_RATE + 2,	//�Ȼ�
	PLAYER_FIELD_CONTROL_ENHANCE_RATE = PLAYER_FIELD_CHARM_RATE + 2,	//������ǿ
	PLAYER_FIELD_CONTROL_RESIST_RATE = PLAYER_FIELD_CONTROL_ENHANCE_RATE + 2,	//���Ƽ���
	PLAYER_FIELD_STRENGTH_ARMOR = PLAYER_FIELD_CONTROL_RESIST_RATE + 2,	//ǿ������

	PLAYER_FIELD_ATTR_RESERVE0			=	 PLAYER_FIELD_STRENGTH_ARMOR + 2,				//Ԥ������0
	PLAYER_FIELD_ATTR_RESERVE1			=	 PLAYER_FIELD_ATTR_RESERVE0 + 2,				//Ԥ������1
	PLAYER_FIELD_ATTR_RESERVE2			=	 PLAYER_FIELD_ATTR_RESERVE1 + 2,				//Ԥ������2
	PLAYER_FIELD_ATTR_RESERVE3			=	 PLAYER_FIELD_ATTR_RESERVE2 + 2,				//Ԥ������3
	PLAYER_FIELD_ATTR_RESERVE4			=	 PLAYER_FIELD_ATTR_RESERVE3 + 2,				//Ԥ������4
	PLAYER_FIELD_ATTR_RESERVE5			=	 PLAYER_FIELD_ATTR_RESERVE4 + 2,				//Ԥ������5
	PLAYER_FIELD_ATTR_RESERVE6			=	 PLAYER_FIELD_ATTR_RESERVE5 + 2,				//Ԥ������6
	PLAYER_FIELD_ATTR_RESERVE7			=	 PLAYER_FIELD_ATTR_RESERVE6 + 2,				//Ԥ������7

	PLAYER_FIELD_BUFF								= PLAYER_FIELD_ATTR_RESERVE7 + 2,		//BUFF
	PLAYER_FIELD_BUFF_RESERVE						= PLAYER_FIELD_BUFF + MAX_BUFF,						//BUFF��������	
	PLAYER_INT_FIELD_BUFF_GIVER_UINT_GUID			= PLAYER_FIELD_BUFF_RESERVE + MAX_BUFF,				//buff giver��uintGuid
	PLAYER_INT_FIELD_BUFF_EFFECT_ID_START			= PLAYER_INT_FIELD_BUFF_GIVER_UINT_GUID + MAX_BUFF,	//buff�ȼ� (byte)
	PLAYER_INT_FIELD_BUFF_EFFECT_ID_END				= PLAYER_INT_FIELD_BUFF_EFFECT_ID_START + MAX_BUFF,	
	PLAYER_FIELD_SKIN								= PLAYER_INT_FIELD_BUFF_EFFECT_ID_END,					//�������
	PLAYER_FIELD_BYTES_1							= PLAYER_FIELD_SKIN+1,								//�ĸ��ֽ�,�ֱ��� 0�������

	PLAYER_FIELD_FORCE					= PLAYER_FIELD_BYTES_1 + 1,									//ս����
	PLAYER_FIELD_EQUIPMENT				= PLAYER_FIELD_FORCE + 2,									//װ���б�12��32λԤ������
	PLAYER_FIELD_CUR_MOUNT				= PLAYER_FIELD_EQUIPMENT + EQUIPMENT_TYPE_MAX_POS,			//��ǰ����ģ��id

	PLAYER_FIELD_PEACE_MODE_CD			= PLAYER_FIELD_CUR_MOUNT + 1,	//��ƽģʽCD
	PLAYER_FIELD_NOTORIETY				= PLAYER_FIELD_PEACE_MODE_CD + 1, //2��short(0:ս��ģʽ, 1:����ֵ)
	
	PLAYER_FIELD_BYTES_2				= PLAYER_FIELD_NOTORIETY + 1,			//��ұ�ʶ,��4��byte[0����ʱ�� 1���ѵȼ� 2��Ѹ��� 3��ҳƺ�]
	PLAYER_FIELD_BYTES_3				= PLAYER_FIELD_BYTES_2 + 1,					//�ĸ��ֽ�,�ֱ��� 0ͷ��,[1����2���ü��ܲ�����3�´θ����Ƿ��б���buff]
	PLAYER_FIELD_BYTES_4				= PLAYER_FIELD_BYTES_3 + 1,					//�ĸ��ֽ�,�ֱ��� (0:Ƶ�������б�,1:Ԥ��,2:Ԥ��,3:Ԥ��)
	PLAYER_FIELD_BYTES_5				= PLAYER_FIELD_BYTES_4 + 1,					//0 GMȨ��, 1, 2 

	PLAYER_FIELD_AUTO_HP				= PLAYER_FIELD_BYTES_5 + 1,					//���
	PLAYER_FIELD_AUTO_MP				= PLAYER_FIELD_AUTO_HP + 2,					//����

	PLAYER_FIELD_VIP_LEVEL				= PLAYER_FIELD_AUTO_MP + 2,					//VIP �ȼ�
	PLAYER_FIELD_VIP_TIME_OUT			= PLAYER_FIELD_VIP_LEVEL + 1,				//VIP ��ʱʱ��

	// �һ�����
	PLAYER_FIELD_HOOK					= PLAYER_FIELD_VIP_TIME_OUT + 1,		//�һ�״̬
	PLAYER_FIELD_HOOK_BYTE0				= PLAYER_FIELD_HOOK + 1,				//0:��1����,1:��2����,2:��3����,3:��4����
	PLAYER_FIELD_HOOK_BYTE1				= PLAYER_FIELD_HOOK_BYTE0 + 1,			//0:�������,1:ŭ������2:ʹ��������ҩ,3:����������Ԫ����ҩ
	PLAYER_FIELD_HOOK_SHORT				= PLAYER_FIELD_HOOK_BYTE1 + 1,			//0:�Զ���ҩ�ٷֱ�,1:�Զ�ʹ�õ���id
	PLAYER_FIELD_HOOK_BYTE3				= PLAYER_FIELD_HOOK_SHORT + 1,			//0:�س̸���/ԭ�ظ���,1:�Զ�ʹ�ð������򸴻,2:����������Ԫ��,3:�Զ�����ĳ��ƽֱ������װ��
	PLAYER_FIELD_FLAGS					= PLAYER_FIELD_HOOK_BYTE3 + 1,		//������±�flags
	PLAYER_FIELD_FLAGS_END				= PLAYER_FIELD_FLAGS + 8,				//Ԥ��8��32λflags

	PLAYER_FIELD_ONLINE_TIME			= PLAYER_FIELD_FLAGS_END,				//������ʱ��(����Ϊ��λ)

	PLAYER_FIELD_ANGER					= PLAYER_FIELD_ONLINE_TIME + 1,			//ŭ���ı�

	PLAYER_FIELD_TRIAL_LAYERS					= PLAYER_FIELD_ANGER + 1,
	PLAYER_INT_FIELD_TRIAL_FINISHED_SECTIONID	= PLAYER_FIELD_TRIAL_LAYERS + 1,			//(�Ѿ�ͨ�صĹؿ�id)
	PLAYER_INT_FIELD_TRIAL_PROCESS				= PLAYER_INT_FIELD_TRIAL_FINISHED_SECTIONID + 1,	//(0:�Ѿ�ɱ�Ĺ�,1:�ܹ���Ҫɱ�Ĺ�)

	PLAYER_FIELD_DECLINE_CHANNEL_BYTE0	= PLAYER_INT_FIELD_TRIAL_PROCESS + 1,			//�ܾ�Ƶ��A(0ϵͳ��1���ɣ�2��ӣ�3����)
	PLAYER_FIELD_DECLINE_CHANNEL_BYTE1	= PLAYER_FIELD_DECLINE_CHANNEL_BYTE0 + 1,	//�ܾ�Ƶ��B(0:����)

	PLAYER_SCENED_INT_FIELD_PLAYER_JUMP_CD	= PLAYER_FIELD_DECLINE_CHANNEL_BYTE1 + 1,			//��ԾCD
	PLAYER_INT_FIELD_SYSTEM_MAIL_ID			= PLAYER_SCENED_INT_FIELD_PLAYER_JUMP_CD + 1,			//��ǰ��ȡ��ϵͳ�ʼ���id

	PLAYER_FIELD_DIVINE_NUM				= PLAYER_INT_FIELD_SYSTEM_MAIL_ID + 1,		//�������
	PLAYER_FIELD_DIVINE_FORCE			= PLAYER_FIELD_DIVINE_NUM + 1,				//�����ս����

	PLAYER_FIELD_MOUNT_FORCE			= PLAYER_FIELD_DIVINE_FORCE + 1,			//������ս��
	PLAYER_FIELD_SKILL_FORCE			= PLAYER_FIELD_MOUNT_FORCE + 1,				//����ս��
	PLAYER_FILED_GEM_FORCE				= PLAYER_FIELD_SKILL_FORCE + 1,				//��ʯս��
	PLAYER_FIELD_STRENGTH_FORCE			= PLAYER_FILED_GEM_FORCE + 1,				//ǿ��ս��

	PLAYER_FIELD_RANK_LIKE				= PLAYER_FIELD_STRENGTH_FORCE + 1,
	PLAYER_FIELD_USE_RANK_LIKE			= PLAYER_FIELD_RANK_LIKE + 1,

	PLAYER_FIELD_SHOP_LIMIT_START		=	PLAYER_FIELD_USE_RANK_LIKE + 1,
	PLAYER_FIELD_SHOP_LIMIT_END			=	PLAYER_FIELD_SHOP_LIMIT_START + MAX_SHOP_LIMIT,

	PLAYER_EXPAND_INT_FCM_LOGIN_TIME			= PLAYER_FIELD_SHOP_LIMIT_END,				//�����ԣ���λ������	-1�ǷǷ��������
	PLAYER_EXPAND_INT_FCM_LOGOUT_TIME			= PLAYER_EXPAND_INT_FCM_LOGIN_TIME + 1,		//����������ʱ��
	PLAYER_EXPAND_INT_CREATE_TIME				= PLAYER_EXPAND_INT_FCM_LOGOUT_TIME + 1,	//��ɫ����ʱ��
	PLAYER_EXPAND_INT_LAST_LOGIN_TIME			= PLAYER_EXPAND_INT_CREATE_TIME + 1,		//����¼ʱ��
	PLAYER_EXPAND_INT_LAST_LOGOUT_TIME			= PLAYER_EXPAND_INT_LAST_LOGIN_TIME + 1,	//�������ʱ��
	PLAYER_EXPAND_INT_NUMBER_OF_LOGINS			= PLAYER_EXPAND_INT_LAST_LOGOUT_TIME + 1,	//�ۻ���¼����
	PLAYER_EXPAND_INT_MONEY						= PLAYER_EXPAND_INT_NUMBER_OF_LOGINS + 1,	//���ֻ���
	PLAYER_EXPAND_INT_MONEY_END					= PLAYER_EXPAND_INT_MONEY + MAX_MONEY_TYPE * 2,
	PLAYER_EXPAND_INT_USE_FASHION				= PLAYER_EXPAND_INT_MONEY_END,	//�Ƿ�����ʱװ,Ŀǰ�õ�20��pos
	PLAYER_EXPAND_INT_XP						= PLAYER_EXPAND_INT_USE_FASHION + 1,		//��ǰ���飬64λ
	PLAYER_EXPAND_INT_NEXT_LEVEL_XP				= PLAYER_EXPAND_INT_XP + 2,					//��һ�����飬64λ
	PLAYER_EXPAND_INT_XP_ADDED					= PLAYER_EXPAND_INT_NEXT_LEVEL_XP + 2,		// Ӧ�÷����ӵľ���
	PLAYER_EXPAND_INT_XP_PICKED					= PLAYER_EXPAND_INT_XP_ADDED + 2,		// �������Ѿ���ȡ��Ӧ�÷����ӵľ���
	PLAYER_EXPAND_INT_MAP_STATUS				= PLAYER_EXPAND_INT_XP_PICKED + 2,		// ��ͼ��������
	PLAYER_EXPAND_INT_GAG_END_TIME				= PLAYER_EXPAND_INT_MAP_STATUS + 1,			//���Խ���ʱ��
	PLAYER_EXPAND_INT_TO_MAP					= PLAYER_EXPAND_INT_GAG_END_TIME + 1,		//���Ҫ���͵��ĵ�ͼ
	PLAYER_EXPAND_INT_TO_INSTANCE_ID			= PLAYER_EXPAND_INT_TO_MAP + 1,				//���Ҫ���͵��ĵ�ͼʵ��ID
	PLAYER_EXPAND_INT_TO_POS_X					= PLAYER_EXPAND_INT_TO_INSTANCE_ID + 1,		//���ҩ���͵�������
	PLAYER_EXPAND_INT_TO_POS_Y					= PLAYER_EXPAND_INT_TO_POS_X + 1,
	PLAYER_EXPAND_INT_TO_LINE_NO				= PLAYER_EXPAND_INT_TO_POS_Y + 1,			//�����ߺ�
	PLAYER_EXPAND_INT_DB_MAP					= PLAYER_EXPAND_INT_TO_LINE_NO + 1,		//������һ�ν��븱��ǰ�ĵ�ͼ	
	PLAYER_EXPAND_INT_DB_POS_X					= PLAYER_EXPAND_INT_DB_MAP + 1,				//������һ�ν��븱��ǰ������
	PLAYER_EXPAND_INT_DB_POS_Y					= PLAYER_EXPAND_INT_DB_POS_X + 1,
	PLAYER_EXPAND_INT_CLIENT_DATA				= PLAYER_EXPAND_INT_DB_POS_Y + 1,			//Զ�̴洢
	//////////////////////////////////////////////////////////////////////////
	//Ӧ�÷�����	
	PLAYER_APPD_INT_FIELD_FLAG					= PLAYER_EXPAND_INT_CLIENT_DATA + MAX_CLIENT_UINT32_COUNT,	//��ұ�־λ
	PLAYER_APPD_INT_FIELD_FLAG_END				= PLAYER_APPD_INT_FIELD_FLAG + 7,		//�����±�

	PLAYER_APPD_INT_FIELD_DAILY_TIME			= PLAYER_APPD_INT_FIELD_FLAG_END,			// ÿ������ʱ����min��
	PLAYER_APPD_INT_FIELD_RESET_WEEK			= PLAYER_APPD_INT_FIELD_DAILY_TIME + 1,		// ÿ������ʱ��
	PLAYER_APPD_INT_FIELD_RESET_DALIY			= PLAYER_APPD_INT_FIELD_RESET_WEEK + 1,				//���õ�ʱ���ÿСʱһ��

	PLAYER_APPD_INT_FIELD_RECHARGE_SUM			= PLAYER_APPD_INT_FIELD_RESET_DALIY + 24,		//�ۼƳ�ֵ����
	PLAYER_APPD_INT_FIELD_LAST_RECHARGE_TIME	= PLAYER_APPD_INT_FIELD_RECHARGE_SUM + 1,		//���һ�ʳ�ֵʱ��

	PLAYER_APPD_INT_FLELD_JHM_FLAGS				= PLAYER_APPD_INT_FIELD_LAST_RECHARGE_TIME + 1,			//������flags
	PLAYER_APPD_INT_FLELD_JHM_FLAGS_END			= PLAYER_APPD_INT_FLELD_JHM_FLAGS + 8,					//������flags_end

	//��������չʱ���
	PLAYER_APPD_INT_FIELD_EXTENSION_END_TIME	= PLAYER_APPD_INT_FLELD_JHM_FLAGS_END + 1,				//��������չ����ʱ���
	PLAYER_APPD_INT_FIELD_EXTENSION_REMAIN_TIME	= PLAYER_APPD_INT_FIELD_EXTENSION_END_TIME + 1,			//��������չʣ�����ʱ��

	PLAYER_INT_FIELD_BLOCK_COUNT = PLAYER_APPD_INT_FIELD_EXTENSION_REMAIN_TIME + 2,	//�����б����

	PLAYER_INT_FIELD_WORLD_BOSS_JOIN_ID			= PLAYER_INT_FIELD_BLOCK_COUNT + 1,			//���һ�βμӵ�����BOSS id
	PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE		= PLAYER_INT_FIELD_WORLD_BOSS_JOIN_ID + 1,	//0:���һ�βμӵ�����BOSS״̬, 1:���������,2:��������,3:Ԥ��

	//��������չ�±꿪ʼ��
	PLAYER_SCENED_INT_FLAGS						= PLAYER_INT_FIELD_WORLD_BOSS_JOIN_STATE + 1,					//��ҳ�������־λ

	// ֻ��ʾװ������������
	PLAYER_INT_FIELD_SPELL_START		= PLAYER_SCENED_INT_FLAGS + 8,
	PLAYER_INT_FIELD_SPELL_END			= PLAYER_INT_FIELD_SPELL_START + PLAYER_SLOT_SPELL_MAX_COUNT,

	//��Ҫ���ܵ�CD
	PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_START	= PLAYER_INT_FIELD_SPELL_END,
	PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_END		= PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_START + MAX_IMPORTANT_SPELL_ATTR_COUNT * PLAYER_IMPORTANT_CD_COUNT,

	PLAYER_EXPAND_KILL_MONSTER					= PLAYER_INT_FIELD_IMPORTANT_SPELL_CD_END,	//ɱ����

	//���
	PLAYER_APPD_INT_FIELD_KUAFU_WARID			= PLAYER_EXPAND_KILL_MONSTER + 1,					//�������id
	PLAYER_INT_FIELD_KUAFU_NUMBER				= PLAYER_APPD_INT_FIELD_KUAFU_WARID + 1,				//0:��ұ������ʱ�յ�ƥ����Ϣ�и��ı�� 1:������ͣ�ֵ����ö�٣�EKUAFU_TYPE��

	PLAYER_INT_FIELD_MAIN_QUEST_ID				= PLAYER_INT_FIELD_KUAFU_NUMBER + 1,					//��ǰ��������
	PLAYER_INT_FIELD_QUEST_CHAPTER				= PLAYER_INT_FIELD_MAIN_QUEST_ID + 1,					//�����½ڽ�����ȡ���

	PLAYER_INT_FIELD_MOUNT_LEVEL				= PLAYER_INT_FIELD_QUEST_CHAPTER + 1,					//4��bytes(0:��ǰ������� 1:��ǰ�����Ǽ�,2:��ǰ�����Ƿ���ˣ�3:��ǰ�û�id)
	
	PLAYER_INT_FIELD_DIVINE_ID					= PLAYER_INT_FIELD_MOUNT_LEVEL + 1,						//��ǰװ�������id

	PLAYER_INT_FIELD_PASSIVE_SPELL_START		= PLAYER_INT_FIELD_DIVINE_ID + 1,				//�������ܿ�ʼ
	PLAYER_INT_FIELD_PASSIVE_SPELL_END			= PLAYER_INT_FIELD_PASSIVE_SPELL_START + PLAYER_PASSIVE_SPELL_MAX_COUNT,	//�������ܸ���
	PLAYER_INT_FIELD_VIRTUAL_CAMP				= PLAYER_INT_FIELD_PASSIVE_SPELL_END,	//������Ӫ
	PLAYER_INT_FIELD_WORLD_3V3_SCORE			= PLAYER_INT_FIELD_VIRTUAL_CAMP + 1,	//���3v3����
	PLAYER_INT_FIELD_WORLD_3V3_TOTAL_SCORE		= PLAYER_INT_FIELD_WORLD_3V3_SCORE + 1,	//���3v3����
	PLAYER_INT_FIELD_WORLD_3V3_TREND_INFO		= PLAYER_INT_FIELD_WORLD_3V3_TOTAL_SCORE + 1,	//ʤ������

	PLAYER_INT_FIELD_DOUJIANTAI_RANK			= PLAYER_INT_FIELD_WORLD_3V3_TREND_INFO + 1,	//����̨����
	PLAYER_INT_FIELD_DOUJIANTAI_REFRESH_TIME	= PLAYER_INT_FIELD_DOUJIANTAI_RANK + 1,	//���һ��ˢ�¶���ʱ���

	PLAYER_INT_FIELD_ARREARS					= PLAYER_INT_FIELD_DOUJIANTAI_REFRESH_TIME + 1,	//Ƿ��
	PLAYER_INT_FIELD_DAILY_QUEST_FINISHED		= PLAYER_INT_FIELD_ARREARS + 2,	// ÿ�����������
	PLAYER_INT_FIELD_BAG_SORT_TIME				=PLAYER_INT_FIELD_DAILY_QUEST_FINISHED + 1, //������ʱ���

	//�ѿ������ܵļ�¼
	PLAYER_INT_FIELD_OPEN_MENU_INDEX	= PLAYER_INT_FIELD_BAG_SORT_TIME+1,
	PLAYER_INT_FIELD_OPEN_MENU_START	= PLAYER_INT_FIELD_OPEN_MENU_INDEX+1,
	PLAYER_INT_FIELD_OPEN_MENU_END		= PLAYER_INT_FIELD_OPEN_MENU_START + MAX_OPEN_MENU_ATTR_COUNT * MAX_PLAYER_OPEN_MENU_COUNT,

	//�ѹ������̵���Ʒ�ļ�¼
	PLAYER_INT_FIELD_BUYED_FACTION_SHOP						= PLAYER_INT_FIELD_OPEN_MENU_END + 1,//�ѹ������̵���Ʒ��ʼ
	PLAYER_INT_FIELD_BUYED_FACTION_SHOP_END					= PLAYER_INT_FIELD_BUYED_FACTION_SHOP + MAX_BUYED_FACTION_SHOP,//�ѹ������̵���Ʒ����

	//��¼ǿ������ID 
	PLAYER_INT_FIELD_GUIDE_ID_LAST							= PLAYER_INT_FIELD_BUYED_FACTION_SHOP_END + 1,	//�ϴ���ɵ�����
	PLAYER_INT_FIELD_GUIDE_ID_NOW							= PLAYER_INT_FIELD_GUIDE_ID_LAST + 1, //��ǰ�����е�����

	//���������
	PLAYER_INT_FIELD_CULTIVATION_LAST_PLUNDER_TIME			= PLAYER_INT_FIELD_GUIDE_ID_NOW + 1,//�ϴ���սʱ���
	PLAYER_INT_FIELD_CULTIVATION_LAST_REFRESH_TIME			= PLAYER_INT_FIELD_CULTIVATION_LAST_PLUNDER_TIME + 1,//�ϴ�ˢ�¶���ʱ���
	PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_EXP			= PLAYER_INT_FIELD_CULTIVATION_LAST_REFRESH_TIME + 1,//�����ۼ��Ӷᾭ��
	PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_CHEST		= PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_EXP + 1,//�����ۼ��Ӷᱦ����
	PLAYER_INT_FIELD_CULTIVATION_TODAY_PURCHASE_COUNT		= PLAYER_INT_FIELD_CULTIVATION_TODAY_PLUNDER_CHEST + 1,//���չ������
	PLAYER_INT_FIELD_CULTIVATION_LEFT_PLUNDER_COUNT			= PLAYER_INT_FIELD_CULTIVATION_TODAY_PURCHASE_COUNT + 1,//��ǰʣ����ս����
	PLAYER_INT_FIELD_CULTIVATION_PLUNDER_RECORD_INDEX		= PLAYER_INT_FIELD_CULTIVATION_LEFT_PLUNDER_COUNT + 1,//������������¼�±�
	PLAYER_INT_FIELD_CULTIVATION_TOTAL_BEEN_PLUNDER_COUNT	= PLAYER_INT_FIELD_CULTIVATION_PLUNDER_RECORD_INDEX + 1,//���ֱ��Ӷ�ɹ�����
	PLAYER_INT_FIELD_CULTIVATION_TODAY_TOTAL_PLUNDER_COUNT	= PLAYER_INT_FIELD_CULTIVATION_TOTAL_BEEN_PLUNDER_COUNT +1,//�������Ӷ����
	PLAYER_INT_FIELD_CULTIVATION_START_TIME					= PLAYER_INT_FIELD_CULTIVATION_TODAY_TOTAL_PLUNDER_COUNT +1,//������ʼʱ��
	PLAYER_INT_FIELD_CULTIVATION_LOST_INFO					= PLAYER_INT_FIELD_CULTIVATION_START_TIME +1,//�������䶪ʧ��Ϣ


	//��½�������
	PLAYER_INT_FIELD_LOGIN_ACTIVITY_TOTAL_DAYS						= PLAYER_INT_FIELD_CULTIVATION_LOST_INFO + 1,//��½������
	PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_START				= PLAYER_INT_FIELD_LOGIN_ACTIVITY_TOTAL_DAYS + 1,//��ȡ״̬��ʼ
	PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_END				= PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_START +2,//��ȡ״̬����

	// ��ǿ������ID
	PLAYER_INT_FIELD_OPTIONAL_GUIDE_START					= PLAYER_INT_FIELD_LOGIN_ACTIVITY_REWARD_STATUS_END + 1,	//��ǿ��������ʼ
	PLAYER_INT_FIELD_OPTIONAL_GUIDE_END						= PLAYER_INT_FIELD_OPTIONAL_GUIDE_START + MAX_OPTIONAL_GUIDE_COUNT * 2,	// ��ǿ����������

	PLAYER_INT_FILED_LEAVE_RISK_TIME						= PLAYER_INT_FIELD_OPTIONAL_GUIDE_END,		//�뿪ð�������ʱ���
	PLAYER_INT_FILED_LEAVE_RISK_SUIT_SCORE					= PLAYER_INT_FILED_LEAVE_RISK_TIME + 1,		//�Ƿ��Ѿ���ȡ����ð������Ĺһ�����

	PLAYER_INT_FILED_FACTION_BUILDING_SPEEDUP_DAILY_COUNT	= PLAYER_INT_FILED_LEAVE_RISK_SUIT_SCORE + 1,	//���彨����������ÿ�մ���
	PLAYER_INT_FILED_FACTION_DONATE_GIFT_EXCHANGE_DAILY_COUNT = PLAYER_INT_FILED_FACTION_BUILDING_SPEEDUP_DAILY_COUNT + 1,	//���屦�⹱������һ�ÿ�մ���

	PLAYER_INT_FILED_CHARM_POINT = PLAYER_INT_FILED_FACTION_DONATE_GIFT_EXCHANGE_DAILY_COUNT + 1, //����ֵ
	PLAYER_INT_FILED_FACTION_GIFT_NEXT_COUNT_ID = PLAYER_INT_FILED_CHARM_POINT + 2,	//���������ʷ��¼��һ��count_id
	PLAYER_INT_FILED_FACTION_GIFT_START = PLAYER_INT_FILED_FACTION_GIFT_NEXT_COUNT_ID + 1, //���������ʷ��¼��ʼ
	PLAYER_INT_FILED_FACTION_GIFT_END = PLAYER_INT_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_GIFT_COUNT  * MAX_FACTION_DATA_INT_GIFT ,
	PLAYER_INT_FIELD_CREATE_ICON = PLAYER_INT_FILED_FACTION_GIFT_END,	//�������İ���icon

	
	PLAYER_INT_FIELD_FACTION_GIFT_POINT_COUNT = PLAYER_INT_FIELD_CREATE_ICON + 1,//�������������ܼ���
	PLAYER_INT_FIELD_FACTION_GIFT_SEND_COUNT = PLAYER_INT_FIELD_FACTION_GIFT_POINT_COUNT + 2,//�������������ܼ���
	PLAYER_INT_FIELD_FACTION_GIFT_BEEN_THANK_COUNT = PLAYER_INT_FIELD_FACTION_GIFT_SEND_COUNT + 1,//�����������ͱ�Ů����л����

	PLAYER_INT_FIELD_MASS_BOSS_BUYED_TIMES			= PLAYER_INT_FIELD_FACTION_GIFT_BEEN_THANK_COUNT + 1,	//�Ѿ��������
	PLAYER_INT_FIELD_MASS_BOSS_TIMES				= PLAYER_INT_FIELD_MASS_BOSS_BUYED_TIMES + 1,			//ȫ��boss����
	PLAYER_INT_FIELD_MASS_BOSS_CD					= PLAYER_INT_FIELD_MASS_BOSS_TIMES + 1,					//ȫ��boss�ظ�cd(0:��ʾ������, ֻ�д����������������cd)

	PLAYER_INT_FIELD_TALISMAN_FORCE					= PLAYER_INT_FIELD_MASS_BOSS_CD + 1,					//������ս��
	PLAYER_INT_FIELD_WINGS_FORCE					= PLAYER_INT_FIELD_TALISMAN_FORCE + 1,					//������ս��

	PLAYER_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG		= PLAYER_INT_FIELD_WINGS_FORCE + 1,						//��Ӹ����״�ͨ��flag

	PLAYER_INT_FIELD_MERIDIAN_FORCE					= PLAYER_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG + 1,		//��������ս��

	PLAYER_INT_FIELD_WINGS_RANK = PLAYER_INT_FIELD_MERIDIAN_FORCE + 1,		//�������

	PLAYER_INT_FIELD_FACTION_BOSSDEFENSE_TICKETS	= PLAYER_INT_FIELD_WINGS_RANK + 1,	//����������սʣ�����

	PLAYER_INT_FIELD_FACTION_TOWER_CLEAR_FLOOR		= PLAYER_INT_FIELD_FACTION_BOSSDEFENSE_TICKETS + 1,	//�����޾�Զ�� ��ʷ��ս����
	PLAYER_INT_FIELD_FACTION_TOWER_FLAG		= PLAYER_INT_FIELD_FACTION_TOWER_CLEAR_FLOOR + 1,			//0 ɨ��״̬ 1~15 ������ȡ״̬

	PLAYER_INT_FIELD_QUALIFY_SCORE			= PLAYER_INT_FIELD_FACTION_TOWER_FLAG + 1,					// ��λ������

	PLAYER_INT_FIELD_FACTION_SKILL_LV_START		= PLAYER_INT_FIELD_QUALIFY_SCORE + 1,										//���弼�ܵȼ���ʼ 0:��ѧϰ�ȼ� uint16 1:��ǰ��Ч�ȼ�
	PLAYER_INT_FIELD_FACTION_SKILL_LV_END		= PLAYER_INT_FIELD_FACTION_SKILL_LV_START + MAX_PLAYER_FACTION_SKILL_COUNT, //���弼�ܵȼ�����

	PLAYER_INT_FIELD_APPEARANCE			= PLAYER_INT_FIELD_FACTION_SKILL_LV_END,								// ���(0:����,1:�·�)

	PLAYER_INT_FIELD_WEAPON_FORCE		= PLAYER_INT_FIELD_APPEARANCE + 1,										// �������ս��
	PLAYER_INT_FIELD_CLOTH_FORCE		= PLAYER_INT_FIELD_WEAPON_FORCE + 1,									// �·����ս��
	PLAYER_INT_FIELD_POKEDEX_FORCE		= PLAYER_INT_FIELD_CLOTH_FORCE + 1,										// ͼ��ս��

	PLAYER_INT_FIELD_TITLE_FORCE		= PLAYER_INT_FIELD_POKEDEX_FORCE + 1,									// �ƺ�ս��
	PLAYER_INT_FIELD_RENAME_TIMES		= PLAYER_INT_FIELD_TITLE_FORCE + 1,										// ��������

	PLAYER_INT_FIELD_REVENGE_TIMES		= PLAYER_INT_FIELD_RENAME_TIMES + 1,									//����ʣ�ิ�����
	PLAYER_INT_FIELD_REVENGE_BUY_TIMES	= PLAYER_INT_FIELD_REVENGE_TIMES + 1,									//���ո��������

	PLAYER_INT_FIELD_WINGS_STAR			=  PLAYER_INT_FIELD_REVENGE_BUY_TIMES + 1,								//��������

	PLAYER_INT_FIELD_VIPGIFT_FLAG		= PLAYER_INT_FIELD_WINGS_STAR + 1,										//vip�������״̬

	PLAYER_APPD_INT_FIELD_CONSUME_SUM	= PLAYER_INT_FIELD_VIPGIFT_FLAG + 1,									//�ۼ�����Ԫ��

	PLAYER_APPD_INT_FIELD_MONEYTREE_COUNT	= PLAYER_APPD_INT_FIELD_CONSUME_SUM + 1,							//ҡǮ��ҡǮ����
	PLAYER_APPD_INT_FIELD_MONEYTREE_GIFT_FLAG = PLAYER_APPD_INT_FIELD_MONEYTREE_COUNT + 1,						//ҡǮ�������ȡ״̬
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�ַ�������

	PLAYER_STRING_FIELD_ACCOUNT					= BINLOG_STRING_FIELD_OWNER + 1,					//�˺�
	PLAYER_STRING_FIELD_TELEPORT_GUID			= PLAYER_STRING_FIELD_ACCOUNT + 1,					//����GUID
	PLAYER_APPD_STRING_FIELD_CLIENT_DATA		= PLAYER_STRING_FIELD_TELEPORT_GUID + 1,			//Զ�̴洢
	PLAYER_STRING_FIELD_LAST_LOGIN_IP			=  PLAYER_APPD_STRING_FIELD_CLIENT_DATA + MAX_CLIENT_STRING_COUNT,					//�������¼��IP
	PLAYER_STRING_FIELD_RECHARGE_ID				= PLAYER_STRING_FIELD_LAST_LOGIN_IP + 1,			//����ֵID
	PLAYER_STRING_FIELD_CREATE_LOGIN_IP			= PLAYER_STRING_FIELD_RECHARGE_ID + 1,				//��Ҵ���IP
	PLAYER_APPD_STRING_FIELD_PINGTAI_INFO		= PLAYER_STRING_FIELD_CREATE_LOGIN_IP + 1,			//ƽ̨��Ϣ
	PLAYER_STRING_FIELD_DB_KUAFU_INFO			= PLAYER_APPD_STRING_FIELD_PINGTAI_INFO + 1,		//��ҿ����Ϣ,�Ƿ�Ϊ��������������±��ǲ��ǿմ�
	PLAYER_STRING_FIELD_FACTION_GUID			= PLAYER_STRING_FIELD_DB_KUAFU_INFO + 1,			//����guid
	PLAYER_STRING_FIELD_FACTION_NAME			= PLAYER_STRING_FIELD_FACTION_GUID + 1,				//��������

	//-----------------------------------
	PLAYER_STRING_FIELD_BLOCK_START				= PLAYER_STRING_FIELD_FACTION_NAME + 1,									//���������б�ʼ
	PLAYER_STRING_FIELD_BLOCK_END				= PLAYER_STRING_FIELD_BLOCK_START + MAX_CHAT_BLOCK_COUNT,				//���������б�ʼ

	PLAYER_STRING_FIELD_RANKLIKE_START			= PLAYER_STRING_FIELD_BLOCK_END,						//���а�����б�ʼ
	PLAYER_STRING_FIELD_RANKLIKE_ENE			= PLAYER_STRING_FIELD_RANKLIKE_START + MAX_RANK_LIKE,	//���а�����б����

	//���������
	PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_START = PLAYER_STRING_FIELD_RANKLIKE_ENE + 1,//����������guid��ʼ
	PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_END = PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_START + MAX_PLAYER_CULTIVATION_RIVAL_COUNT,//����������guid����

	PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_START = PLAYER_STRING_INT_FIELD_CULTIVATION_RIVAL_GUID_END + 1,//������������¼��ʼ
	PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_END = PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_START + MAX_PLAYER_CULTIVATION_PLUNDER_RECORD_COUNT,//������������¼����

	PLAYER_STRING_FIELD_INVITE_FACTION_GUID	= PLAYER_STRING_INT_FIELD_CULTIVATION_PLUNDER_RECORD_END, //����İ���guid
	PLAYER_STRING_FIELD_CREATE_FACTION_NAME	= PLAYER_STRING_FIELD_INVITE_FACTION_GUID + 1,	//�������İ�������

	PLAYER_STRING_FILED_FACTION_GIFT_START = PLAYER_STRING_FIELD_CREATE_FACTION_NAME + 1, //���������ʷ��¼��ʼ
	PLAYER_STRING_FILED_FACTION_GIFT_END = PLAYER_STRING_FILED_FACTION_GIFT_START + MAX_FACTION_DATA_GIFT_COUNT  * MAX_FACTION_DATA_STRING_GIFT ,
	
	PLAYER_STRING_FIELD_GROUP_PEACE_ID = PLAYER_STRING_FILED_FACTION_GIFT_END,	//���ģʽ�µ����id
};


#define PLAYER_BASIC_SPELL_CAPACITY 30			//��һ������ܵ�����
#define PLAYER_DIVINE_SPELL_CAPACITY 15			//����������������
#define PLAYER_TALISMAN_SPELL_CAPACITY 15			//��ҷ�������������

// ���ӵ�еĻ�������������Ϣ
enum BASIC_SPELL_ATTR
{
	SHORT_SPELL_ID		= 0,		//����id short
	SHORT_SPELL_LV		= 1,		//���ܵȼ� short
};

// ���ܲ۶�Ӧ������
enum SPELL_SLOT_ATTR {
	SLOT_COMBO  = 1,		//���м��ܲ�
	SLOT_DIVINE = 5,		//������ܲ�
	SLOT_ANGER	= 6,		//��ŭ���ܲ�
	SPELL_SLOT_COUNT = 6	//���ܲ۵�����
};

// ��������
enum SKILL_TYPE
{
	SKILL_TYPE_DIVINE = 4,	//�������
};


#define MOUNT_UPGRADE_SKILL_COUNT 10
#define MOUNT_ILLUSION_COUNT 30
#define EQUIPMENT_COUNT 10
#define DIVINE_PASSIVE_SKILL_COUNT 3
#define EQUIPDEVELOP_GEM_COUNT 10


// �û�����
enum IllusionAttr
{
	ILLUSION_ATTR_ID = 0,										//�û�id
	ILLUSION_ATTR_SPELL_START = ILLUSION_ATTR_ID + 1,			//�û����ܿ�ʼ
	ILLUSION_ATTR_SPELL_END	= ILLUSION_ATTR_SPELL_START + 2,	//�û����ܽ���
	ILLUSION_ATTR_EXPIRE	= ILLUSION_ATTR_SPELL_END,			//����ʱ��
	MAX_ILLUSION_ATTR_COUNT = ILLUSION_ATTR_EXPIRE + 1
};

enum EXPIRE_TYPE
{
	EXPIRE_TYPE_ILLUSION = 0,	//�û�����
	EXPIRE_TYPE_DIVINE = 1,		//�������
};


enum Strengthen
{
	STRENGTHEN_LEV_BLESS = 0,					//ǿ���ȼ� ף��ֵ
	MAX_STRENGTHEN_COUNT = STRENGTHEN_LEV_BLESS + 1
};

enum GEM
{
	GEM_LEV = 0,					//��ʯ�ȼ�
	GEM_CURID_BLESS = GEM_LEV + 3,	//��ǰ��ʯ  1short ��ʯף��ֵ 0short 
	MAX_GEM_COUNT = GEM_CURID_BLESS + 1
};
enum DIVINE
{
	DIVINE_ID_LEV_BLESS = 0,				//��� id_8 �ȼ�lev_8 ף��ֵbless_16
	DIVINE_TIME = DIVINE_ID_LEV_BLESS + 1,  //�������ʱ��
	DIVINE_SKILL = DIVINE_TIME + 1,
	DIVINE_PASSIVE_SKILL = DIVINE_SKILL + 1,
	DIVINE_IMPROVE = DIVINE_PASSIVE_SKILL + DIVINE_PASSIVE_SKILL_COUNT,//������� ���� forge 0; ���� advance 1; ���� spirit 2
	MAX_DIVINE_COUNT,
};

enum TALISMAN
{
	TALISMAN_ID_LV = 0, //���� id_8 �ȼ� lev_8
	TALISMAN_FORCE = 1, //���� ս��
	MAX_TALISMAN_COUNT,
};

enum EQUIPDEVELOP
{
	EQUIPDEVELOP_STRENGTH_LV = 0,	//0 int16 ǿ���ȼ�
	EQUIPDEVELOP_REFINE_LV = 1,		//0 int16 ���� 1 int16 ����
	EQUIPDEVELOP_GEM_LV_START = 2,		//��ʯ�ȼ���ʼ int16 int16
	EQUIPDEVELOP_GEM_LV_END = EQUIPDEVELOP_GEM_LV_START + EQUIPDEVELOP_GEM_COUNT / 2 - 1, //��ʯ�ȼ�����
	MAX_EQUIPDEVELOP_COUNT,
};

// ������������
enum RaiseSpellType
{
	RAISE_BASE_SKILL = 1,		//��������
	RAISE_MOUNT_SKILL = 2,		//���＼��
	RAISE_ILLUSION_SKILL = 3,	//�û�����
	RAISE_DIVINE_SKILL = 4,		//�û�����
};

//װ�����ɲ�������
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

};

#define MAX_EXTERIOR_COUNT 200	// ����������

//�����int
enum PLAYERACTIVITTYDATAINT
{
	PLAYER_ACTIVITTY_DATA_INT_0 = 0,
	PLAYER_ACTIVITTY_DATA_INT_1 = 1,
	PLAYER_ACTIVITTY_DATA_INT_2 = 2,
	PLAYER_ACTIVITTY_DATA_INT_3 = 3,
	MAX_PLAYERACTIVITTYDATAINT_COUNT,
};

//�����string
enum PLAYERACTIVITTYDATASTRING
{
	PLAYER_ACTIVITTY_DATA_STRING_0 = 0,
	MAX_PLAYERACTIVITTYDATASTRING_COUNT,
};

#define MAX_PLAYERDACTIVITTYDATA_COUNT 100	//�����������

//��Ҽ�����Ϣ
enum PlayerSpellInfo
{
	SPELL_BASE_COUNT					= 0,										//�������ܸ���
	SPELL_INT_FIELD_BASE_SPELL_START	= SPELL_BASE_COUNT + 1,						//�������ܿ�ʼ
	SPELL_INT_FIELD_BASE_SPELL_END		= SPELL_INT_FIELD_BASE_SPELL_START + PLAYER_BASIC_SPELL_CAPACITY,

	SPELL_INT_FIELD_MOUNT_LEVEL			= SPELL_INT_FIELD_BASE_SPELL_END,	//2��short (0����, 1�Ǽ�)
	SPELL_INT_FIELD_MOUNT_TRAIN_EXP		= SPELL_INT_FIELD_MOUNT_LEVEL + 1,	//��ǰ��������
	SPELL_INT_FIELD_MOUNT_LEVEL_BASE	= SPELL_INT_FIELD_MOUNT_TRAIN_EXP + 1,	//����ȼ�
	SPELL_INT_FIELD_MOUNT_SPELL_START	= SPELL_INT_FIELD_MOUNT_LEVEL_BASE + 1,	//���׼��ܿ�ʼ
	SPELL_INT_FIELD_MOUNT_SPELL_END		= SPELL_INT_FIELD_MOUNT_SPELL_START + MOUNT_UPGRADE_SKILL_COUNT,							//���׼��ܽ���
	SPELL_INT_FIELD_MOUNT_BLESS_EXP		= SPELL_INT_FIELD_MOUNT_SPELL_END,															//����ף��ֵ
	SPELL_INT_FIELD_MOUNT_ILLUSION_START = SPELL_INT_FIELD_MOUNT_BLESS_EXP + 1,												//�û���ʼ
	SPELL_INT_FIELD_MOUNT_ILLUSION_END	 = SPELL_INT_FIELD_MOUNT_ILLUSION_START + MAX_ILLUSION_ATTR_COUNT * MOUNT_ILLUSION_COUNT,	//�û�����

	SPELL_STRENGTHEN_START = SPELL_INT_FIELD_MOUNT_ILLUSION_END + 1,							//ǿ����ʼ
	SPELL_STRENGTHEN_END = SPELL_STRENGTHEN_START + EQUIPMENT_COUNT * MAX_STRENGTHEN_COUNT,	    //ǿ������
	SPELL_STRENGTHEN_ALLMUL = SPELL_STRENGTHEN_END + 1,											//ȫ��ǿ�����
	
	SPELL_GEM_START = SPELL_STRENGTHEN_ALLMUL + 1,												//��ʯ��ʼ
	SPELL_GEM_END = SPELL_GEM_START + EQUIPMENT_COUNT * MAX_GEM_COUNT,							//��ʯ����
	SPELL_GEM_ALLMUL = SPELL_GEM_END + 1,														//ȫ��ʯ���


	SPELL_DIVINE_COUNT = SPELL_GEM_ALLMUL + 1,													//�������
	SPELL_DIVINE_START = SPELL_DIVINE_COUNT + 1,												//�����ʼ
	SPELL_DIVINE_END = SPELL_DIVINE_START + PLAYER_DIVINE_SPELL_CAPACITY  * MAX_DIVINE_COUNT,	//�������

	SPELL_TALISMAN_START = SPELL_DIVINE_END,//������ʼ
	SPELL_TALISMAN_END = SPELL_TALISMAN_START + PLAYER_TALISMAN_SPELL_CAPACITY  * MAX_TALISMAN_COUNT,//��������

	SPELL_WINGS_ID = SPELL_TALISMAN_END,			//���id  ����*100 + ����
	SPELL_WINGS_LEVEL = SPELL_WINGS_ID + 1,			//���ǿ���ȼ�
	SPELL_WINGS_BLESS_EXP = SPELL_WINGS_LEVEL + 1,	//���ǰף������

	SPELL_INT_FIELD_MERIDIAN_LEVEL			= SPELL_WINGS_BLESS_EXP + 1,			// 2shorts(0:�����ȼ�, 1:�Ƿ���Ҫͻ��)
	SPELL_INT_FIELD_MERIDIAN_EXP			= SPELL_INT_FIELD_MERIDIAN_LEVEL + 1,	// ��������

	SPELL_INT_FIELD_MERIDIAN_CNT_START		= SPELL_INT_FIELD_MERIDIAN_EXP + 1,				// ÿ����ɴ�����ʼ
	SPELL_INT_FIELD_MERIDIAN_CNT_END		= SPELL_INT_FIELD_MERIDIAN_CNT_START + 13,		// ÿ����ɴ�������

	SPELL_INT_FIELD_EQUIPDEVELOP_START		= SPELL_INT_FIELD_MERIDIAN_CNT_END,				// װ��������ʼ
	SPELL_INT_FIELD_EQUIPDEVELOP_END		= SPELL_INT_FIELD_EQUIPDEVELOP_START + MAX_EQUIPDEVELOP_COUNT * EQUIPMENT_COUNT,//װ����������
	SPELL_INT_FIELD_EQUIPDEVELOP_BONUS_LV	= SPELL_INT_FIELD_EQUIPDEVELOP_END,				// װ�����������ȼ� 0 ǿ�� 1 ���� 2 ��Ƕ

	SPELL_INT_FIELD_APPEARANCE_START		= SPELL_INT_FIELD_EQUIPDEVELOP_BONUS_LV + 1,				// ��ۿ�ʼ
	SPELL_INT_FIELD_APPEARANCE_END			= SPELL_INT_FIELD_APPEARANCE_START + MAX_EXTERIOR_COUNT,	// ��۽���

	SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START = SPELL_INT_FIELD_APPEARANCE_END,						//�������ݿ�ʼ
	SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_END = SPELL_INT_FIELD_PLAYER_ACTIVITY_DATA_START + MAX_PLAYERACTIVITTYDATAINT_COUNT * MAX_PLAYERDACTIVITTYDATA_COUNT, //�������ݽ���

	
	SPELL_STRING_FIELD_EQUIPDEVELOP_WASHATTRS_INFO		= BINLOG_STRING_FIELD_OWNER + 1,			//ϴ��������
	SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_START = SPELL_STRING_FIELD_EQUIPDEVELOP_WASHATTRS_INFO + 1 ,	//�������ݿ�ʼ
	SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_END = SPELL_STRING_FIELD_PLAYER_ACTIVITY_DATA_START + MAX_PLAYERACTIVITTYDATASTRING_COUNT * MAX_PLAYERDACTIVITTYDATA_COUNT,//�������ݽ���

};


#define SOCIAL_FRIEND_MAX_NUM 60 //������
#define SOCIAL_APPLY_MAX_NUM 10 // ������
#define SOCIAL_ENEMY_MAX_NUM 20 //������
#define SOCIAL_START 4

enum SocialItem
{
	SOCIAL_ICON_VIP_LEV = 0, //ͼ�� vip �ȼ�
	SOCIAL_FAMILIAR_LEV_EXP = SOCIAL_ICON_VIP_LEV + 1,//���ܶȵȼ� ���ܶȾ���
	SOCIAL_FAMILIAR_FORCE = SOCIAL_FAMILIAR_LEV_EXP + 1,//ս��
	MAX_FRIENT_COUNT = SOCIAL_FAMILIAR_FORCE +  2,
};
enum PlayerSocialInfo
{
	//SOCIAL_BASE_COUNT = 0,//���Ѹ���
	SOCIAL_REVENGE_NUM = SOCIAL_START, //�������
	SOCIAL_REVENGE_CD = SOCIAL_REVENGE_NUM + 1,//����CD
	SOCIAL_FRIEND_START = SOCIAL_REVENGE_CD + 1,	//���ѿ�ʼ
	SOCIAL_FRIEND_END = SOCIAL_FRIEND_START + SOCIAL_FRIEND_MAX_NUM * MAX_FRIENT_COUNT,//���ѽ���

	SOCIAL_ENEMY_START = SOCIAL_FRIEND_END,//���˿�ʼ
	SOCIAL_ENEMY_END = SOCIAL_ENEMY_START + SOCIAL_ENEMY_MAX_NUM * MAX_FRIENT_COUNT,//���˽���

	SOCIAL_APPLY_START = SOCIAL_ENEMY_END,//���뿪ʼ
	SOCIAL_APPLY_END = SOCIAL_APPLY_START + SOCIAL_APPLY_MAX_NUM * MAX_FRIENT_COUNT,//�������

	SOCIAL_APPLY_CLEAR_FLAG = SOCIAL_APPLY_END,//����������

	SOCIAL_ENEMY_TIME_START = SOCIAL_APPLY_CLEAR_FLAG + 1,//����ʱ�����ʼ
	SOCIAL_ENEMY_TIME_END = SOCIAL_ENEMY_TIME_START + SOCIAL_ENEMY_MAX_NUM,//����ʱ�������

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����±�

//�����¼�
enum EFactionEventType
{
	FACTION_EVENT_TYPE_NULL					= 0,		//Ԥ��
	FACTION_EVENT_TYPE_ADD_MEMBER 			= 1,		//��ӳ�Ա
	FACTION_EVENT_TYPE_SUB_MEMBER			= 2,		//��Ա�뿪
	FACTION_EVENT_TYPE_APPOINT				= 3,		//����
	FACTION_EVENT_TYPE_KICK_MEMBER			= 4,		//�߳���Ա
	FACTION_EVENT_TYPE_JUANXIAN				= 5,		//����
	FACTION_EVENT_TYPE_HONGBAO				= 6,		//�����
	FACTION_EVENT_TYPE_SHANGXIANG			= 7,		//����

};

//���ɹ�������
enum EFactionManagerType
{
	FACTION_MANAGER_TYPE_AGREE_JOIN			= 0,		//ͬ��������
	FACTION_MANAGER_TYPE_REFUSE_JOIN 		= 1,		//�ܾ��������
	FACTION_MANAGER_TYPE_KICK 				= 2,		//�߳�����
	FACTION_MANAGER_TYPE_APPOINT 			= 3,		//ְλ����
	FACTION_MANAGER_TYPE_RECRUIT 			= 4,		//��ļ����
	FACTION_MANAGER_TYPE_LEVEL_UP 			= 5,		//��������
	FACTION_MANAGER_TYPE_CHANGE_FLAGS		= 6,		//�滻����
	FACTION_MANAGER_TYPE_NOTICE				= 7,		//��ṫ��
	FACTION_MANAGER_TYPE_AGREE_JOIN_ALL		= 8,		//ȫ��ͬ��������
	FACTION_MANAGER_TYPE_REFUSE_JOIN_ALL 	= 9,		//ȫ���ܾ��������
	FACTION_MANAGER_TYPE_QUIT			 	= 10,		//�˳�����
};

//���ڲ�������
enum EFactionPeopleType
{
	FACTION_MANAGER_TYPE_JUANXIAN		= 0,		//����
	FACTION_MANAGER_TYPE_FULI			= 1,		//��ȡ����
	FACTION_MANAGER_TYPE_FA_HONGBAO		= 2,		//�����
	FACTION_MANAGER_TYPE_LQ_HONGBAO		= 3,		//��ȡ���
	FACTION_MANAGER_TYPE_SHANGXIANG		= 4,		//����
	FACTION_MANAGER_TYPE_SHOP			= 5,		//����
	FACTION_MANAGER_TYPE_BUY_TOKEN		= 6,		//��������
	FACTION_MANAGER_TYPE_CHALLENGE_BOSS	= 7,		//��ս����Boss
	FACTION_MANAGER_TYPE_BUILDING_UPGRADE = 8,		//��������
	FACTION_MANAGER_TYPE_BUILDING_UPGRADE_SPEEDUP = 9,//������������
	FACTION_MANAGER_TYPE_DONATE_GIFT_EXCHANGE	= 10,//��������һ�

	FACTION_MANAGER_TYPE_GIFT_SHOW_PAGE	= 11,		//�鿴�����б�
	FACTION_MANAGER_TYPE_GIFT_SHOW_INFO	= 12,		//�鿴������Ϣ
	FACTION_MANAGER_TYPE_GIFT_SHOW_UNTHANK_PAGE	= 13,//Ů���鿴δ��л����
	FACTION_MANAGER_TYPE_GIFT_SHOW_HISTORY_PAGE	= 14,//Ů���鿴��ʷ��¼
	FACTION_MANAGER_TYPE_GIFT_THANK	= 15,			//Ů����л
	FACTION_MANAGER_TYPE_GIFT_THANK_ALL	= 16,		//Ů��ȫ����л
	FACTION_MANAGER_TYPE_GIFT_THANK_AND_REPLY	= 17,//Ů����л���ظ�
	FACTION_MANAGER_TYPE_GIFT_REPLY	= 18,			//�����˻ظ�

	FACTION_MANAGER_TYPE_BOSSDEFENSE_CHALLENGE = 19,//����������ս
	FACTION_MANAGER_TYPE_BOSSDEFENSE_DAMAGE_LIST = 20,//�鿴������ս���ǰ10

	FACTION_MANAGER_TYPE_TOWER_CHALLENGE	= 21, //�޾�Զ�� ��ս��һ��
	FACTION_MANAGER_TYPE_TOWER_SWEEP		= 22, //�޾�Զ�� ɨ��
	FACTION_MANAGER_TYPE_TOWER_CHEST		= 23, //�޾�Զ�� ������

	FACTION_MANAGER_TYPE_SKILL_LVUP			= 24, //�������弼��

};

//���ڽ�������
enum EFactionBuildingType
{
	FACTION_BUILDING_TYPE_MAINHALL	= 1,			//����
	FACTION_BUILDING_TYPE_STOREHOUSE	= 2,		//���ⷿ
	FACTION_BUILDING_TYPE_BANK		= 3,			//���
	FACTION_BUILDING_TYPE_EVENT		= 4,			//�����
	FACTION_BUILDING_TYPE_SKILL		= 5,			//���ܷ�
	FACTION_BUILDING_TYPE_SHOP		= 6,			//�����̵�
};

//���ɳ�Ա���ӵ�е�buff��
#define MAX_FACTION_MENBER_BUFF_NUM 6
//�������ӵ�е�buff��
#define MAX_FACTION_BUFF_NUM 6
//��ǰ��Ļ���buff��
#define MAX_CUR_SCREEN_BUFF_NUM 6
//���������б���������
#define MAX_FACTION_APLLY_MAMBER_COUNT 3
//��������Ա��
#define MAX_FACTION_MAMBER_COUNT 50
//���ɾ��׼�¼
#define MAX_FACTION_EVENT_COUNT  10
#define MAX_FACTION_SHOP 8
//�����������
#define MAX_FACTION_HONGBAO_COUNT 10
//�������BOSS��
#define MAX_FACTION_BOSS_COUNT 10
//�������������
#define MAX_FACTION_BUILDING_COUNT 10



//���ɳ�Ա��INT��Ϣ
enum EFactionIntMemberType
{
	FACTION_INT_MEMBER_FORCE				= 0, 			//��Աս����
	FACTION_INT_MEMBER_UINT16				= 2,			//0.��Ա�ȼ�,1.���չ���
	FACTION_INT_MEMBER_BYTE					= 3,			//0.�Ƿ�����,1.���, 2,�Ƿ�VIP��3,���ջ�Ծ��
	FACTION_INT_MEMBER_LOGOUT_TIME			= 4,			//�������ʱ��
	FACTION_INT_MEMBER_FLAGS				= 5,			//��Ա��־λ
	FACTION_INT_MEMBER_TOTAL_CONTRIBUTION	= 6,			//��ʷ���� - ����ʱ��
	FACTION_INT_MEMBER_CHARM				= 7,			//���˵�����ֵ
	FACTION_INT_MEMBER_TOTAL_SEND_CHARM		= 9,			//(�����ܹ���) 
	FACTION_INT_MEMBER_TOWER_TODAY_FLOOR	= 10,			//�޾�Զ������ͨ�ز���
	
	MAX_FACTION_INT_MEMBER				
};

//���ɳ�Ա��STRING��Ϣ
enum EFactionStringMemberType
{
	FACTION_STRING_MEMBER_GUID				= 0, 		//��Ա ID
	FACTION_STRING_MEMBER_NAME				= 1,		//��Ա����
	MAX_FACTION_STRING_MEMBER,
};

enum EFactionIntEventType
{
	FACTION_INT_EVENT_TYPE_VALUE			= 0,//���ͣ���ֵ
	FACTION_INT_EVENT_RESERVE				= 1,//�����ֶ�
	MAX_FACTION_INT_EVENT
};

//���ɳ�Ա���ö��
enum EFactionMemberIdentity
{
	FACTION_MEMBER_IDENTITY_NULL				= 0,	//�գ�Ԥ��
	FACTION_MEMBER_IDENTITY_BANGZHU				= 1,	//����
	FACTION_MEMBER_IDENTITY_FU_BANGZHU			= 2,	//������
	FACTION_MEMBER_IDENTITY_TANGZHU				= 3,	//����
	FACTION_MEMBER_IDENTITY_JINGYING			= 4,	//��Ӣ
	FACTION_MEMBER_IDENTITY_QUNZHONG			= 5,	//Ⱥ��
};

//���ɱ�־λ
enum EFactionFlags
{
	FACTION_FLAGS_AUTO				= 0,				//�����Ƿ��Զ���������
	FACTION_FLAGS_IS_BOSS_ADD		= 1,				//�����Ƿ�����ͨ����boss����
};

//����buff��Ϣö��
enum EFactionBuffInfoType
{
	FACTION_BUFF_ID				= 0,	//0��buff���ͣ�1��Ԥ��
	FACTION_BUFF_END_TM			= 1,	//buff����ʱ��
	MAX_FACTION_BUFF,
};

#define MAX_FACTION_STOREHOUSE_COUNT 100
#define MAX_FACTION_STOREHOUSE_RECORD_COUNT 10

//���ɳ�Ա��INT��Ϣ
enum EFactionIntBossDenfenseType
{
	FACTION_INT_BOSSDEFENSE_POOL_ID		= 0,	//�����id
	FACTION_INT_BOSSDEFENSE_HP			= 1,	//ʣ��hp
	FACTION_INT_BOSSDEFENSE_MAX_HP		= 2,	//���hp
	FACTION_INT_BOSSDEFENSE_STATUS		= 3,	//����״̬	0:���� 1:ս�� 2:����
	MAX_FACTION_BOSSDEFENSE,
};

#define MAX_FACTION_BOSSDEFENSE_COUNT 6

//�����±�
enum EFactionFileds
{

	//UINT32 ����
	FACTION_INT_FIELD_PLAYER_NOW_INDEX			= 0,		//���ɳ�Ա��λ������
	FACTION_INT_FIELD_FLAG						= FACTION_INT_FIELD_PLAYER_NOW_INDEX + 1,			//����FLAG
	FACTION_INT_FIELD_PLAYER					= FACTION_INT_FIELD_FLAG + 1,								//���ɳ�Ա��ʼ�±�
	FACTION_INT_FIELD_PLAYER_END				= FACTION_INT_FIELD_PLAYER + MAX_FACTION_INT_MEMBER * MAX_FACTION_MAMBER_COUNT,	//������������
	FACTION_INT_FIELD_APPLY_PLAYER_COUNT_INDEX	= FACTION_INT_FIELD_PLAYER_END,
	FACTION_INT_FIELD_APPLY_PLAYER				= FACTION_INT_FIELD_APPLY_PLAYER_COUNT_INDEX + 1,						//��������������б�
	FACTION_INT_FIELD_APPLY_PLAYER_END			= FACTION_INT_FIELD_APPLY_PLAYER + MAX_FACTION_INT_MEMBER * MAX_FACTION_APLLY_MAMBER_COUNT,	//������������б�
	FACTION_INT_FIELD_EVENT						= FACTION_INT_FIELD_APPLY_PLAYER_END,//���ɼ�¼��ʼ
	FACTION_INT_FIELD_EVENT_END					= FACTION_INT_FIELD_EVENT + MAX_FACTION_EVENT_COUNT * MAX_FACTION_INT_EVENT,//���ɼ�¼����
	FACTION_INT_FIELD_EVENT_FALG				= FACTION_INT_FIELD_EVENT_END,//���ɼ�¼��־λ
	FACTION_INT_FIELD_SHOP						= FACTION_INT_FIELD_EVENT_FALG + 1,//�̵꿪ʼ
	FACTION_INT_FIELD_SHOP_END					= FACTION_INT_FIELD_SHOP + MAX_FACTION_SHOP,//�̵����

	FACTION_INT_FIELD_FORCE						= FACTION_INT_FIELD_SHOP_END,	//����ս����
	FACTION_INT_FIELD_MONEY						= FACTION_INT_FIELD_FORCE + 2,			//�����ʲ�
	FACTION_INT_FIELD_LEVEL						= FACTION_INT_FIELD_MONEY + 2,			//���ɵȼ�
	FACTION_INT_FIELD_ACTIVITY					= FACTION_INT_FIELD_LEVEL + 1,			//���ɻ�Ծ��
	FACTION_INT_FIELD_RANK						= FACTION_INT_FIELD_ACTIVITY + 1,		//��������
	FACTION_INT_FIELD_FLAGS_ID					= FACTION_INT_FIELD_RANK + 1,			//(byte)0:���ɵ�ǰѡ�������ID (byte)1:�����ȼ� (uint16)1:����
	FACTION_INT_FIELD_MINLEV					= FACTION_INT_FIELD_FLAGS_ID + 1,		//���������С�ȼ�

	FACTION_INT_FIELD_TOKEN_NUM = FACTION_INT_FIELD_MINLEV + 1,								//��������
	FACTION_INT_FIELD_TOKEN_POINTS = FACTION_INT_FIELD_TOKEN_NUM + 1,						//���ƽ��ջ��ֽ���
	FACTION_INT_FIELD_TOKEN_POINTS_COUNT = FACTION_INT_FIELD_TOKEN_POINTS + 1,				//���ƽ��ջ�����ɴ���
	FACTION_INT_FIELD_TOKEN_TODAY_BUY_COUNT = FACTION_INT_FIELD_TOKEN_POINTS_COUNT + 1,			//�������ƹ������
	FACTION_INT_FIELD_CHALLENGE_BOSS_ID_MAX = FACTION_INT_FIELD_TOKEN_TODAY_BUY_COUNT + 1,	//����ս���boss id
	FACTION_INT_FIELD_CHALLENGE_BOSS_ID = FACTION_INT_FIELD_CHALLENGE_BOSS_ID_MAX + 1,		//��ǰ��սboss id
	FACTION_INT_FIELD_CHALLENGE_BOSS_START_TIME = FACTION_INT_FIELD_CHALLENGE_BOSS_ID + 1,	//��ǰ��ս��ʼʱ��
	FACTION_INT_FIELD_CHALLENGE_BOSS_HP_RATE = FACTION_INT_FIELD_CHALLENGE_BOSS_START_TIME + 1,				//��ǰbossѪ����ֱ�
	FACTION_INT_FIELD_CHALLENGE_BOSS_POS = FACTION_INT_FIELD_CHALLENGE_BOSS_HP_RATE + 1,					//��ǰbossλ�� x,y
	FACTION_INT_FIELD_PROTECT_TARGET_HP_RATE = FACTION_INT_FIELD_CHALLENGE_BOSS_POS + 1,				//��ǰ�ػ�Ŀ��Ѫ����ֱ�
	FACTION_INT_FIELD_PROTECT_TARGET_POS = FACTION_INT_FIELD_PROTECT_TARGET_HP_RATE + 1,				//��ǰ�ػ�Ŀ��λ�� x,y
	FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START = FACTION_INT_FIELD_PROTECT_TARGET_POS + 1,		//��ǰboss�����ʼ int ���ֵ
	FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END = FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START + MAX_FACTION_MAMBER_COUNT,//��ǰboss��������
	FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START = FACTION_INT_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END,	//�������ʼ
	FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END = FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START + MAX_FACTION_MAMBER_COUNT,//����������

	FACTION_INT_FIELD_STOREHOUSE_ITEM_COUNT		= FACTION_INT_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END,	//�����������
	FACTION_INT_FIELD_STOREHOUSE_RECORD_CURSOR	= FACTION_INT_FIELD_STOREHOUSE_ITEM_COUNT + 1,		//�����¼�α�

	FACTION_INT_FIELD_BUILDING_ID_START = FACTION_INT_FIELD_STOREHOUSE_RECORD_CURSOR + 1,			//���н���id��ʼ
	FACTION_INT_FIELD_BUILDING_ID_END	= FACTION_INT_FIELD_BUILDING_ID_START + MAX_FACTION_BUILDING_COUNT,//���н���id����
	FACTION_INT_FIELD_BUILDING_LVUP_ID	= FACTION_INT_FIELD_BUILDING_ID_END,						//��ǰ���������Ľ���id
	FACTION_INT_FIELD_BUILDING_LVUP_FINISH_TIME = FACTION_INT_FIELD_BUILDING_LVUP_ID + 1,			//��ǰ�����������ʱ���
	FACTION_INT_FIELD_IS_DISSOLVED				= FACTION_INT_FIELD_BUILDING_LVUP_FINISH_TIME + 1,	//�Ƿ��ɢ

	FACTION_INT_FIELD_GIFT_WEEK_POINT_START = FACTION_INT_FIELD_IS_DISSOLVED +1,	//�����ܰ�����ֵ������ʼ
	FACTION_INT_FIELD_GIFT_WEEK_POINT_END = FACTION_INT_FIELD_GIFT_WEEK_POINT_START + MAX_FACTION_MAMBER_COUNT, //�����ܰ�����ֵ��������
	FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_START = FACTION_INT_FIELD_GIFT_WEEK_POINT_END, //δ�������������ʼ Ů��δ��л ��ԱΪ��ȡ
	FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_END = FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_START + MAX_FACTION_MAMBER_COUNT,//δ���������������
	FACTION_INT_FIELD_CHARM_POINT	= FACTION_INT_FIELD_GIFT_UNCHECK_COUNT_END+1,//����Ů������ֵ double
	FACTION_INT_FIELD_GIFT_SEND_COUNT_START = FACTION_INT_FIELD_CHARM_POINT + 2, //�����������������ʼ
	FACTION_INT_FIELD_GIFT_SEND_COUNT_END = FACTION_INT_FIELD_GIFT_SEND_COUNT_START + MAX_FACTION_MAMBER_COUNT,//�������������������
	FACTION_INT_FIELD_GIFT_LAST_SEND_TIME = FACTION_INT_FIELD_GIFT_SEND_COUNT_END,//������͵�ʱ��

	FACTION_INT_FIELD_GIFT_QUEEN_UNCHECK_COUNT = FACTION_INT_FIELD_GIFT_LAST_SEND_TIME + 2,//Ů��δ���������

	FACTION_INT_FIELD_BOSSDENFENSE_START = FACTION_INT_FIELD_GIFT_QUEEN_UNCHECK_COUNT + 1,	//����������ս��Ϣ��ʼ
	FACTION_INT_FIELD_BOSSDENFENSE_END = FACTION_INT_FIELD_BOSSDENFENSE_START + MAX_FACTION_BOSSDEFENSE_COUNT * MAX_FACTION_BOSSDEFENSE,//����������ս��Ϣ����

	FACTION_INT_FIELD_TOWER_TODAY_TOP_FLOOR	= FACTION_INT_FIELD_BOSSDENFENSE_END,			//�޾�Զ�� ÿ������� ���� int32
	FACTION_INT_FIELD_TOWER_TODAY_TOP_ICON	= FACTION_INT_FIELD_TOWER_TODAY_TOP_FLOOR + 1,	//�޾�Զ�� ÿ������� ͷ�� int32
	FACTION_INT_FIELD_TOWER_TODAY_TOP_FORCE	= FACTION_INT_FIELD_TOWER_TODAY_TOP_ICON + 1,	//�޾�Զ�� ÿ������� ս�� double

	FACTION_INT_FIELD_TOTAL_FORCE = FACTION_INT_FIELD_TOWER_TODAY_TOP_FORCE + 2, // double ���ɳ�Ա��ս��

	FACTION_INT_FIELD_MANGER_COAT	= FACTION_INT_FIELD_TOTAL_FORCE + 2, //�����·�
	FACTION_INT_FIELD_MANGER_WEAPON	= FACTION_INT_FIELD_MANGER_COAT + 1, //��������
	FACTION_INT_FIELD_MANGER_VIP	= FACTION_INT_FIELD_MANGER_WEAPON + 1, //����vip
	FACTION_INT_FIELD_MANGER_GENDER	= FACTION_INT_FIELD_MANGER_VIP + 1, //����gender
	FACTION_INT_FIELD_MANGER_TITLE	= FACTION_INT_FIELD_MANGER_GENDER + 1, //����title
	FACTION_INT_FIELD_MANGER_LIKE	= FACTION_INT_FIELD_MANGER_TITLE + 1, //��������
	FACTION_INT_FIELD_MANGER_WING	= FACTION_INT_FIELD_MANGER_LIKE + 1,  //��������

	FACTION_STRING_FIELD_MANGER_NAME		= BINLOG_STRING_FIELD_OWNER + 1,//��������
	FACTION_STRING_FIELD_MANGER_GUID		= FACTION_STRING_FIELD_MANGER_NAME + 1,//����GUID
	FACTION_STRING_FIELD_PLAYER				= FACTION_STRING_FIELD_MANGER_GUID + 1,						//���ɳ�Ա�б�		
	FACTION_STRING_FIELD_PLAYER_END			= FACTION_STRING_FIELD_PLAYER + MAX_FACTION_STRING_MEMBER * MAX_FACTION_MAMBER_COUNT,	//���ɳ�Ա�б����
	FACTION_STRING_FIELD_APPLY_PLAYER		= FACTION_STRING_FIELD_PLAYER_END,	//������������б�
	FACTION_STRING_FIELD_APPLY_PLAYER_END	= FACTION_STRING_FIELD_APPLY_PLAYER +  MAX_FACTION_STRING_MEMBER * MAX_FACTION_APLLY_MAMBER_COUNT, //������������б����
	FACTION_STRING_FIELD_EVENT				= FACTION_STRING_FIELD_APPLY_PLAYER_END,//���ɼ�¼��ʼ
	FACTION_STRING_FIELD_EVENT_END			= FACTION_STRING_FIELD_EVENT + MAX_FACTION_EVENT_COUNT,//���ɼ�¼����

	FACTION_STRING_FIELD_GONGGAO			= FACTION_STRING_FIELD_EVENT_END,		//���ɹ���
	FACTION_STRING_FIELD_ZHAOMU_GONGGAO		= FACTION_STRING_FIELD_GONGGAO + 1,//��ļ����

	FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START = FACTION_STRING_FIELD_ZHAOMU_GONGGAO + 1,		//��ǰboss�����ʼ string guid
	FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END = FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_START + MAX_FACTION_MAMBER_COUNT,//��ǰboss��������
	FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START = FACTION_STRING_FIELD_CHALLENGE_BOSS_DAMAGE_RANK_END,	//�������ʼ
	FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END = FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_START + MAX_FACTION_MAMBER_COUNT,//����������

	FACTION_STRING_FIELD_STOREHOUSE_START		= FACTION_STRING_FIELD_CHALLENGE_BOSS_TOTAL_RANK_END,					//���屦�⿪ʼ
	FACTION_STRING_FIELD_STOREHOUSE_END			= FACTION_STRING_FIELD_STOREHOUSE_START + MAX_FACTION_STOREHOUSE_COUNT,	//���屦�����

	FACTION_STRING_FIELD_STOREHOUSE_RECORD_START= FACTION_STRING_FIELD_STOREHOUSE_END,												 //�����¼��ʼ
	FACTION_STRING_FIELD_STOREHOUSE_RECORD_END	= FACTION_STRING_FIELD_STOREHOUSE_RECORD_START + MAX_FACTION_STOREHOUSE_RECORD_COUNT,//�����¼����

	FACTION_STRING_FIELD_GIFT_PLAYER_GUID_START = FACTION_STRING_FIELD_STOREHOUSE_RECORD_END,	//�����Ӧ���guid��ʼ
	FACTION_STRING_FIELD_GIFT_PLAYER_GUID_END = FACTION_STRING_FIELD_GIFT_PLAYER_GUID_START + MAX_FACTION_MAMBER_COUNT,//�����Ӧ���guid����

	FACTION_STRING_FIELD_TOWER_TODAY_TOP_NAME = FACTION_STRING_FIELD_GIFT_PLAYER_GUID_END,		//�޾�Զ�� ÿ������� ����
};


enum EFactionDataFileds
{
	FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_START = 0,	//������ս�˺���ʼ
	FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_END = FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_START + MAX_FACTION_BOSSDEFENSE_COUNT * MAX_FACTION_MAMBER_COUNT,			//������ս�˺�����
	FACTION_DATA_INT_FIELD_GIFT_START = FACTION_DATA_INT_FIELD_BOSSDEFENSE_DAMAGE_END,									//�����¼int��ʼ
	FACTION_DATA_INT_FIELD_GIFT_TMP1 = MAX_FACTION_DATA_GIFT_COUNT * MAX_FACTION_MAMBER_COUNT,						//��ʱ
	FACTION_DATA_INT_FIELD_GIFT_TOTAL_LEN = FACTION_DATA_INT_FIELD_GIFT_TMP1 * MAX_FACTION_DATA_INT_GIFT,			//��ʱ
	FACTION_DATA_INT_FIELD_GIFT_TOTAL_CACHE_LEN = MAX_FACTION_DATA_GIFT_CACHE_COUNT * MAX_FACTION_DATA_INT_GIFT,	//��ʱ
	FACTION_DATA_INT_FIELD_GIFT_TMP2 = FACTION_DATA_INT_FIELD_GIFT_START + FACTION_DATA_INT_FIELD_GIFT_TOTAL_LEN,	//��ʱ
	FACTION_DATA_INT_FIELD_GIFT_END = FACTION_DATA_INT_FIELD_GIFT_TMP2 + FACTION_DATA_INT_FIELD_GIFT_TOTAL_CACHE_LEN, //�����¼����
	FACTION_DATA_INT_FIELD_GIFT_RANK_START = FACTION_DATA_INT_FIELD_GIFT_END,	//��¼��������id��ʼ
	FACTION_DATA_INT_FIELD_GIFT_RANK_END = FACTION_DATA_INT_FIELD_GIFT_RANK_START + MAX_FACTION_DATA_GIFT_COUNT * MAX_FACTION_MAMBER_COUNT, //��¼��������id����

	FACTION_DATA_STRING_FIELD_GIFT_START = BINLOG_STRING_FIELD_OWNER + 1,	//�����¼string��ʼ
	FACTION_DATA_STRING_FIELD_GIFT_TEMP1 = MAX_FACTION_DATA_GIFT_COUNT * MAX_FACTION_MAMBER_COUNT,				//��ʱ
	FACTION_DATA_STRING_FIELD_GIFT_TEMP2 = FACTION_DATA_STRING_FIELD_GIFT_TEMP1 * MAX_FACTION_DATA_STRING_GIFT,	//��ʱ
	FACTION_DATA_STRING_FIELD_GIFT_TEMP3 = MAX_FACTION_DATA_GIFT_CACHE_COUNT * MAX_FACTION_DATA_STRING_GIFT,	//��ʱ
	FACTION_DATA_STRING_FIELD_GIFT_TEMP4 = FACTION_DATA_STRING_FIELD_GIFT_TEMP2 + FACTION_DATA_STRING_FIELD_GIFT_TEMP3,//��ʱ
	FACTION_DATA_STRING_FIELD_GIFT_END = FACTION_DATA_STRING_FIELD_GIFT_START + FACTION_DATA_STRING_FIELD_GIFT_TEMP4, //�����¼����
};

enum EFactionRankFileds
{
	//int
	//��¼2000����¼  ���� ����ͼ��

	//��¼������Ϣ 1~2000 ��¼index

	//���ܼ�¼

	//string  Ů��guid  Ů������ ����guid ������ ��ʿ��
	//���ܼ�¼
};

#define MAX_TRIAL_LAYER_COUNT 256

// ������״̬ϵ��
enum TRIAL_STATE_FACTOR
{
	TRIAL_STATE_FACTOR_ACTIVE = 1,		//����״̬ϵ��
	TRIAL_STATE_FACTOR_PASS   = 10,		//ͨ��״̬ϵ��
	TRIAL_STATE_FACTOR_F_PASS = 100,	//��ͨ״̬ϵ��
};
#define MAX_ACTIVE_COUNT 50
#define MAX_ACTIVT_REWARD_COUNT 6
#define MAX_DOUJIANTAI_RECORD_COUNT 10

#define MAX_QUALIFY_RECORD_COUNT 30
// ��Ҹ�����Ϣ
enum PLAYER_INSTANCE_INFO
{
	INSTANCE_INT_FIELD_VIP_START	= 0,									//vip������ʼ	ÿ����Ϣ4��byte[0:Ԥ��,1:��ɨ���Ѷ�,2:��ս����,3:�������]
	INSTANCE_INT_FIELD_VIP_END		= INSTANCE_INT_FIELD_VIP_START + 3,	//vip��������

	INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT	= INSTANCE_INT_FIELD_VIP_END,					//(0:���տ�ɨ������,1:��ʷͨ�ز���)
	INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT	= INSTANCE_INT_FIELD_TRIAL_PASSED_SHORT + 1,	//(0:ɨ������,1:�ɹ���ɨ������)--]]

	INSTANCE_INT_FIELD_RES_START	= INSTANCE_INT_FIELD_TRIAL_SWEEP_SHORT + 1,//��Դ������ʼ ÿ����Ϣ4��byte[0:��ս����,1:�Ƿ�ͨ��,2:Ԥ��,3:Ԥ��]
	INSTANCE_INT_FIELD_RES_END		= INSTANCE_INT_FIELD_RES_START + 5,//��Դ��������

	INSTANCE_INT_FIELD_ACTIVE_START = INSTANCE_INT_FIELD_RES_END,//���ʼ
	INSTANCE_INT_FIELD_ACTIVE_END	= INSTANCE_INT_FIELD_ACTIVE_START + MAX_ACTIVE_COUNT,//�����
	INSTANCE_INT_FIELD_ACTIVE		= INSTANCE_INT_FIELD_ACTIVE_END,//�-��Ծ��
	INSTANCE_INT_FIELD_ACTIVE_REWARD = INSTANCE_INT_FIELD_ACTIVE + 1,//������ȡ״̬

	INSTANCE_INT_FIELD_3V3_TIMES		= INSTANCE_INT_FIELD_ACTIVE_REWARD + 1,//3v3���� �ѲμӴ��� �������
	INSTANCE_INT_FIELD_3V3_DAY_REWARD	= INSTANCE_INT_FIELD_3V3_TIMES + 1,//3v3ÿ�մ������� 4��byte

	INSTANCE_INT_FIELD_3V3_SEGMENT_TIME = INSTANCE_INT_FIELD_3V3_DAY_REWARD + 1,//3v3��λ ����ʱ��
	
	INSTANCE_INT_FIELD_XIANFU_DAY_TIMES = INSTANCE_INT_FIELD_3V3_SEGMENT_TIME + 1,	//ÿ����ս����

	INSTANCE_INT_FIELD_DOUJIANTAI_CURSOR = INSTANCE_INT_FIELD_XIANFU_DAY_TIMES + 1,		//����̨��Ϣ�α�
	INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S = INSTANCE_INT_FIELD_DOUJIANTAI_CURSOR + 1,	//�������ο�ʼ
	INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E = INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_S + 3,	//�������ν���

	INSTANCE_INT_FIELD_DOUJIAN_TIMES			= INSTANCE_INT_FIELD_DOUJIANTAI_ENEMY_E + 1,	//�������� ����ս���� �������
	INSTANCE_INT_FIELD_DOUJIAN_FIGHT_CD			= INSTANCE_INT_FIELD_DOUJIAN_TIMES + 1,		//����̨��սCDʱ���
	INSTANCE_INT_FIELD_DOUJIAN_FIRST_GET		= INSTANCE_INT_FIELD_DOUJIAN_FIGHT_CD + 1,	//��ʤ�������
	INSTANCE_INT_FIELD_DOUJIAN_FIRST_REWARD		= INSTANCE_INT_FIELD_DOUJIAN_FIRST_GET + 1,	//��ʤ������ȡ���
	INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN		= INSTANCE_INT_FIELD_DOUJIAN_FIRST_REWARD + 1,	//��ʤ��¼ ��¼ ��ǰ
	INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN_REWARD = INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN + 1,//��ʤ������¼
	INSTANCE_INT_FIELD_DOUJIAN_MAX_RANK			= INSTANCE_INT_FIELD_DOUJIAN_COMBATWIN_REWARD+1,//��ʷ��߼�¼

	INSTANCE_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG		= INSTANCE_INT_FIELD_DOUJIAN_MAX_RANK + 1,				//ÿbit��¼��Ӧ��Ӹ���id�״�ͨ��״̬ false:δ��� true:�����
	INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT = INSTANCE_INT_FIELD_GROUP_INSTANCE_CLEAR_FLAG + 1,		//��Ӹ���ʣ����ս����
	INSTANCE_INT_FIELD_GROUP_INSTANCE_BUY_COUNT		= INSTANCE_INT_FIELD_GROUP_INSTANCE_CHALLENGE_COUNT + 1,	//������Ӹ�����ս�����������
	INSTANCE_INT_FIELD_QUALIFY_EXTRA				= INSTANCE_INT_FIELD_GROUP_INSTANCE_BUY_COUNT + 1,					// ��λ��ʤ���������ȡ������־
	INSTANCE_INT_FIELD_QUALIFY_WINS					= INSTANCE_INT_FIELD_QUALIFY_EXTRA + 1,					// ��λ��Ӯ�ó���		
	INSTANCE_INT_FIELD_QUALIFY_EXTRA_PICKED			= INSTANCE_INT_FIELD_QUALIFY_WINS + 1,					// ��λ��ʤ����������ȡ������־
	INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES			= INSTANCE_INT_FIELD_QUALIFY_EXTRA_PICKED + 1,			// ��λ��ÿ�����
	INSTANCE_INT_FIELD_QUALIFY_BUY_TIMES			= INSTANCE_INT_FIELD_QUALIFY_DAILY_TIMES + 1,			// ��λ���������
	INSTANCE_INT_FIELD_QUALIFY_CURSOR				= INSTANCE_INT_FIELD_QUALIFY_BUY_TIMES + 1,				// ��λ����¼�α�

	INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_START	= BINLOG_STRING_FIELD_OWNER + 1,//����̨ս����Ϣ��ʼ
	INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_END	= INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_START + MAX_DOUJIANTAI_RECORD_COUNT,	//����̨ս����Ϣ����

	INSTANCE_STR_FIELD_QUALIFY_RECORD_START		= INSTANCE_STR_FIELD_DOUJIANTAI_RECORD_END,									//��λ��ս����Ϣ��ʼ
	INSTANCE_STR_FIELD_QUALIFY_RECORD_END		= INSTANCE_STR_FIELD_QUALIFY_RECORD_START + MAX_QUALIFY_RECORD_COUNT,		//��λ��ս����Ϣ����
};

// ս��ģʽ
enum BattleMode
{
	PEACE_MODE			= 0,	//��ƽģʽ
	FAMILY_MODE			= 1,	//����ģʽ
	GROUP_MODE			= 2,	//���ģʽ
	MAX_BATTLE_MODE,
};

//��Ҫ���ڲ���Ϣͬ�����������ļ�������
enum SceneNeedSpellType
{
	TYPE_SPELL_SLOT		= 0,		//����װ�����еļ���
	TYPE_SPELL_PASSIVE	= 1,		//���»�����������
};

// �������/����/�������ܷ���
enum SpellInitiative
{
	SPELL_SUPPORT = 0,				// ����

	SPELL_INITIATIVE_DAMAGE  = 1,	// �������˺���
	SPELL_INITIATIVE_PROTECT = 2,	// ������������
	SPELL_INITIATIVE_CONTROL = 3,	// ���������ƣ�
	SPELL_INITIATIVE_CURE 	 = 4,	// �������ظ���
	SPELL_INITIATIVE_BUFF = 5,		// ���������棩

	SPELL_PASSIVE_DAMAGE = 6,		// �������˺���
	SPELL_PASSIVE_PROTECT = 7,		// ������������
	SPELL_PASSIVE_CONTROL = 8,		// ���������ƣ�
	SPELL_PASSIVE_CURE = 9,			// �������ظ���
	SPELL_PASSIVE_BUFF = 10,		// ���������棩
};


//��Ϸ����ר�õ�״̬�±�ö��
enum EGameConfigFieldFlagsType
{
	GAME_CONFIG_FIELD_FLAGS_SHOW_PLATFORM_NAME		= 0,		//�Ƿ���ʾƽ̨��
	GAME_CONFIG_FIELD_FLAGS_SHOW_SERVER_ID			= 1,		//�Ƿ���ʾ������ID
	GAME_CONFIG_FIELD_FLAGS_SHOW_POST				= 2,		//�����Ƿ�post
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��Ϸ����
enum EGameConfigField
{
	GAME_CONFIG_INT_FIELD_KAIFUSHIJIAN				= 0,												//����ʱ��
	GAME_CONFIG_INT_FIELD_FLAGS						= GAME_CONFIG_INT_FIELD_KAIFUSHIJIAN + 1,			//��Ϸ���ñ�־λ
	GAME_CONFIG_INT_FIELD_ADDTIME					= GAME_CONFIG_INT_FIELD_FLAGS + 8,					//�Ϸ�ʱ��
	GAME_CONFIG_INT_FIELD_WORLD_SVR_TYPE			= GAME_CONFIG_INT_FIELD_ADDTIME + 1,				//����������(��ö��: ESERVER_TYPE)

	GAME_CONFIG_STRING_FIELD_PLATFORM_ID			= BINLOG_STRING_FIELD_OWNER + 1,					//ƽ̨ID
	GAME_CONFIG_STRING_FIELD_GM_QQ					= GAME_CONFIG_STRING_FIELD_PLATFORM_ID + 1,			//GM��QQ
	GAME_CONFIG_STRING_FIELD_DB_CONN				= GAME_CONFIG_STRING_FIELD_GM_QQ + 1,				//���ݿ����Ӵ�
	GAME_CONFIG_STRING_FIELD_LOGIN_KEY				= GAME_CONFIG_STRING_FIELD_DB_CONN + 1,				//��¼��Կ
	GAME_CONFIG_STRING_FIELD_LOG_DB_CONN			= GAME_CONFIG_STRING_FIELD_LOGIN_KEY + 1,			//��־���ݿ����Ӵ�
	GAME_CONFIG_STRING_LOCAL_HDD_PATH				= GAME_CONFIG_STRING_FIELD_LOG_DB_CONN + 1,			//����Ӳ�����ݱ����ַ
	GAME_CONFIG_STRING_EXT_WEB_INTERFACE			= GAME_CONFIG_STRING_LOCAL_HDD_PATH + 1,			//web�ӿ�����
	GAME_CONFIG_STRING_CONF_SVR_URL					= GAME_CONFIG_STRING_EXT_WEB_INTERFACE + 1,			//���÷�url��ַ
	GAME_CONFIG_STRING_WORLD_SERVER_URL				= GAME_CONFIG_STRING_CONF_SVR_URL + 1,				//�����url��ַ

	GAME_CONFIG_STRING_FIELD_SERVER					= 200,												//ԭʼ������
	GAME_CONFIG_STRING_FIELD_SERVER_LIST_BEGIN		= GAME_CONFIG_STRING_FIELD_SERVER + 1,				//�������б�
};

//�ͻ���ģ��ö��
enum EClientModule
{
	CLIENT_MODULE_CENTER	= 0,		//����ģ��
	CLIENT_MODULE_CREATE	= 1,		//������ɫģ��
	CLIENT_MODULE_SCENE		= 2,		//����ģ��
	CLIENT_MODULE_UI		= 3,		//UIģ��
	CLIENT_MODULE_SH		= 4,		//���ģ��

	MAX_CLIENT_MODULE,
};

//�ͻ���ģ��汾��Ϣ
enum EClientVersion
{
	CLIENT_VERSION_INT_CREATE_TIME		= 0,		//�汾����ʱ��
	MAX_CLIENT_VERSION_INT,

	CLIENT_VERSION_STRING_VERSIONS		= 0,		//ģ��汾��
	CLIENT_VERSION_STRING_COMMENT		= 1,		//ģ��汾˵��
	MAX_CLIENT_VERSION_STRING,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ͻ���������Ϣ
enum EClientConfigField
{
	CLIENT_CONFIG_INT_FIELD_MODULE_INFO_BEGIN	= 0,
	CLIENT_CONFIG_INT_FIELD_MODULE_INFO_END		= CLIENT_CONFIG_INT_FIELD_MODULE_INFO_BEGIN + MAX_CLIENT_VERSION_INT * MAX_CLIENT_MODULE,

	CLIENT_CONFIG_STRING_FIELD_MODULE_INFO_BEGIN	= BINLOG_STRING_FIELD_OWNER + 1,
	CLIENT_CONFIG_STRING_FIELD_MODULE_INFO_END		= CLIENT_CONFIG_STRING_FIELD_MODULE_INFO_BEGIN + MAX_CLIENT_VERSION_STRING * MAX_CLIENT_MODULE,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_DEFAULT_LINE_COUNT 4	// ���Ĭ�Ϸ�������
#define MAX_FIELD_BOSS_COUNT  40	// ���Ĭ��Ұ��BOSS����

// Ұ��BOSS��������
enum FieldBossProcessType
{
	FIELD_BOSS_PROCESS_TYPE_FINISH		= 0,			//�ѽ���
	FIELD_BOSS_PROCESS_START_COUNTDOWN	= 1,			//��ʼ����ʱ
	FIELD_BOSS_PROCESS_BORN				= 2,			//BOSSˢ��
	FIELD_BOSS_PROCESS_TREASURE			= 3,			//�������

};

// Ұ��BOSS int����
enum FieldBossIntData
{
	FIELD_BOSS_DATA_NEXT_BORN_TIME									= 0,									//��һ��ˢ��ʱ��
	FIELD_BOSS_DATA_CURR_HP											= FIELD_BOSS_DATA_NEXT_BORN_TIME + 1,	//��ǰѪ���ٷֱ�
	FIELD_BOSS_DATA_PROCESS_TYPE									= FIELD_BOSS_DATA_CURR_HP + 2,			//��������
	FIELD_BOSS_DATA_PRIORITY_TIME									= FIELD_BOSS_DATA_PROCESS_TYPE + 1,		//����ʰȡʱ���
	FIELD_BOSS_DATA_KILLED											= FIELD_BOSS_DATA_PRIORITY_TIME + 1,	//��ɱ����

	MAX_FIELD_BOSS_INT_DATA_COUNT,			
};

// Ұ��BOSS str����
enum FieldBossStrData
{
	FIELD_BOSS_DATA_MAX_DAMAGE_GUID								= 0,									//����˺�guid
	FIELD_BOSS_DATA_NAME										= FIELD_BOSS_DATA_MAX_DAMAGE_GUID + 1,	//��ǰ���ڲɼ����������

	MAX_FIELD_BOSS_STR_DATA_COUNT,			
};

// ����BOSS����
enum WorldBossProcessType
{
	WORLD_BOSS_PROCESS_TYPE_FINISH		= 0,			//�ѽ���
	WORLD_BOSS_PROCESS_ENROLL			= 1,			//����
	WORLD_BOSS_PROCESS_BORN				= 2,			//BOSSˢ��

};

// �����������BOSS��״̬
enum PLAYER_WORLD_BOSS_STATE
{
	PLAYER_WORLD_BOSS_NONE						= 0,			//ʲô��û��
	PLAYER_WORLD_BOSS_ENROLLED					= 1,			//������
	PLAYER_WORLD_BOSS_ENTERED					= 2,			//���������
};


enum MassBossInfo
{
	MASS_BOSS_STATE				= 0,					//ȫ��boss״̬
	MASS_BOSS_TIME				= MASS_BOSS_STATE + 1,	//ȫ��bossˢ��ʱ��
	MAX_MASS_BOSS_INT_FIELD_COUNT,
};

#define MAX_XIANFU_RECORD_COUNT 10

#define MAX_MASS_BOSS_COUNT 10
#define MAX_LOTTERY_COUNT 10
#define MAX_LOTTERY_RECORD_COUNT 10

#define MAX_ACT_RANK_COUNT 10			//������
#define MAX_ACT_RANK_INFO_COUNT 10		//���������Ϣ����


//�������
enum GlobalValueField
{
	GLOBALVALUE_INT_FIELD_FLAGS										= 0,													//���������־λ
	GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION					= GLOBALVALUE_INT_FIELD_FLAGS + 8,						//��汾��
	GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_END_TIME					= GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_VERSION + 1,		//�����ʱ��
	GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM						= GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_END_TIME + 1,	//���Ʒ����
	GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM_END					= GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM + 30,		//���10�����ߵ���
	GLOBALVALUE_INT_FIELD_ONLINE_PLAYER_NUM							= GLOBALVALUE_INT_FIELD_LIMIT_ACTIVITY_ITEM_END,		//��¼ȫ�����������
	GLOBALVALUE_INT_FIELD_WORLD_CONNECTION_STATUS					= GLOBALVALUE_INT_FIELD_ONLINE_PLAYER_NUM + 1,			//���������״̬

	// Ұ��BOSS����
	GLOBALVALUE_INT_FIELD_FIELD_BOSS_START							= GLOBALVALUE_INT_FIELD_WORLD_CONNECTION_STATUS + 1,	// Ұ��boss���ݿ�ʼ
	GLOBALVALUE_INT_FIELD_FIELD_BOSS_END							= GLOBALVALUE_INT_FIELD_FIELD_BOSS_START + MAX_FIELD_BOSS_COUNT * MAX_FIELD_BOSS_INT_DATA_COUNT,																									// Ұ��boss���ݽ���

	GLOBALVALUE_INT_FIELD_WORLD_BOSS_LEVEL							= GLOBALVALUE_INT_FIELD_FIELD_BOSS_END,					//����BOSS�ȼ�
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_STATE							= GLOBALVALUE_INT_FIELD_WORLD_BOSS_LEVEL + 1,			//����BOSS��״̬
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_LINE_STATE						= GLOBALVALUE_INT_FIELD_WORLD_BOSS_STATE + 1,			//����BOSSÿ�������״̬
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_LAST_ENROLL_TIME				= GLOBALVALUE_INT_FIELD_WORLD_BOSS_LINE_STATE + 1,		// ���һ�α���ʱ��
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_TIMES							= GLOBALVALUE_INT_FIELD_WORLD_BOSS_LAST_ENROLL_TIME + 1,//����BOSS����
	GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID								= GLOBALVALUE_INT_FIELD_WORLD_BOSS_TIMES + 1,			//0:����BOSS����1, 1:����BOSS����2,2:��ǰѡ��������,3:�������

	GLOBALVALUE_INT_FIELD_XIANFU_RECORD_CURSOR						= GLOBALVALUE_INT_FIELD_WORLD_BOSS_ID + 1,	//�ɸ���������ļ�¼�α�

	GLOBALVALUE_INT_FIELD_GIFT_RANK_WINER_FACTION_FLAG				= GLOBALVALUE_INT_FIELD_XIANFU_RECORD_CURSOR + 1, //�����������е�һ��������

	GLOBALVALUE_INT_FIELD_GIFT_RANK_NEXT_UPDATE_TIME				= GLOBALVALUE_INT_FIELD_GIFT_RANK_WINER_FACTION_FLAG + 1,//���������´θ���ʱ��
	GLOBALVALUE_INT_FIELD_GIFT_RANK_CUR_ROUND					= GLOBALVALUE_INT_FIELD_GIFT_RANK_NEXT_UPDATE_TIME + 1,///�������е�ǰ����
	
	GLOBALVALUE_INT_FIELD_MASS_BOSS_START							= GLOBALVALUE_INT_FIELD_GIFT_RANK_CUR_ROUND + 1,	//ȫ��boss��ʼ
	GLOBALVALUE_INT_FIELD_MASS_BOSS_END								= GLOBALVALUE_INT_FIELD_MASS_BOSS_START + MAX_MASS_BOSS_INT_FIELD_COUNT * MAX_MASS_BOSS_COUNT,
	
	GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START	= GLOBALVALUE_INT_FIELD_MASS_BOSS_END,		// �齱��¼�α�
	GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_END		= GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_START + MAX_LOTTERY_COUNT,	//

	GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START = GLOBALVALUE_INT_FIELD_LOTTERY_RECORD_CURSOR_END,		 // �����id ��ʼ
	GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_END	= GLOBALVALUE_INT_FIELD_ACTIVITIES_RUNNING_START + 30, // �����id ����

	/************************************************************************************************************************************************/
	
	/************************************************************************************************************************************************/

	GLOBALVALUE_STRING_FIELD_LIMIT_ACTIVITY_SCRIPT					= BINLOG_STRING_FIELD_OWNER + 1,					//��ʱ�����

	GLOBALVALUE_STRING_FIELD_FIELD_BOSS_START						= GLOBALVALUE_STRING_FIELD_LIMIT_ACTIVITY_SCRIPT + 1,				// Ұ��boss���ȿ������������guid��ʼ
	GLOBALVALUE_STRING_FIELD_FIELD_BOSS_END							= GLOBALVALUE_STRING_FIELD_FIELD_BOSS_START + MAX_FIELD_BOSS_COUNT * MAX_FIELD_BOSS_STR_DATA_COUNT, // Ұ��boss���ȿ������������guid����


	GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_START					= GLOBALVALUE_STRING_FIELD_FIELD_BOSS_END,		//�ɸ������Ӽ�¼��ʼ
	GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_END						= GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_START + MAX_XIANFU_RECORD_COUNT,// �ɸ������Ӽ�¼����

	GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_QUEEN_NAME				= GLOBALVALUE_STRING_FIELD_XIANFU_RECORD_END,//�����������е�һŮ������
	GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_FACTION_NAME			= GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_QUEEN_NAME + 1,//�����������е�һ��������
	GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_GUARD_NAME				= GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_FACTION_NAME + 1,//�����������е�һ��ʿ����

	GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_START = GLOBALVALUE_STRING_FIELD_GIFT_RANK_WINER_GUARD_NAME + 1,		// �齱��¼���ݿ�ʼ
	GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_END   = GLOBALVALUE_STRING_FIELD_LOTTERY_RECORD_START + MAX_LOTTERY_COUNT * MAX_LOTTERY_RECORD_COUNT,	//

	
};


#define MAX_DOUJIANTAI_RANK_COUNT 1000
#define MAX_RISK_RANK_COUNT 10			//����ð�հ�����
#define MAX_RISK_RANK_SWAPED_COUNT 11	//����ð�մ������İ�����

enum RISK_RANK_INFO
{
	RISK_RANK_INFO_SECTION_ID	= 0,
	RISK_RANK_INFO_TIME	= RISK_RANK_INFO_SECTION_ID + 1,
	MAX_RISK_RANK_INFO_COUNT,
};

enum EGlobalCounter
{
	GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_START = 0,	//��ս�еı��λ
	GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_END	  = GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_START + 40,

	GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_START = GLOBALCOUNTER_INT_FIELD_DOUJIANTAI_FLAG_END,		// �����id flag��ʼ
	GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_END	= GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_START + 200,	// �����id flag����

	GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_START	= GLOBALCOUNTER_INT_FIELD_ACTIVITIES_FINISH_END,//��������ݿ�ʼ
	GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_END	= GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_START + MAX_ACT_RANK_COUNT * MAX_ACT_RANK_INFO_COUNT,//��������ݽ���

	GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_START = GLOBALCOUNTER_INT_FIELD_ACT_RANK_INFO_END,
	GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_END = GLOBALCOUNTER_INT_FIELD_RISK_RANK_INFO_START + MAX_RISK_RANK_SWAPED_COUNT * MAX_RISK_RANK_INFO_COUNT,

	GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_START	= BINLOG_STRING_FIELD_OWNER + 1,//����̨������ʼ
	GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_END	= GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_START + MAX_DOUJIANTAI_RANK_COUNT,//����̨��������
	GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_START = GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_END,//ս����Ϣ��¼��ʼ
	GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_END   = GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_START + MAX_DOUJIANTAI_RANK_COUNT * MAX_DOUJIANTAI_RECORD_COUNT, //ս����Ϣ��¼����

	GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_START = GLOBALCOUNTER_STRING_FIELD_DOUJIANTAI_RECORD_END,						//��������ݿ�ʼ
	GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_END = GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_START + MAX_ACT_RANK_COUNT * MAX_ACT_RANK_INFO_COUNT,//��������ݽ���

	GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_START = GLOBALCOUNTER_STRING_FIELD_ACT_RANK_INFO_END,
	GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_END	= GLOBALCOUNTER_STRING_FIELD_RISK_RANK_NAME_START + MAX_RISK_RANK_SWAPED_COUNT,
};

//��ʱ���������������
enum EGlobalCounterField
{
	GLOBALCOUNTER_INT_FIELD_ONLINE_AWARD_COUNT						= 0,			//ȫ����������
	GLOBALCOUNTER_INT_FIELD_DAILY_ADD_BIND_GOLD						= GLOBALCOUNTER_INT_FIELD_ONLINE_AWARD_COUNT + 2,	//ÿ��������Ԫ������
	GLOBALCOUNTER_INT_FIELD_DAILY_SUB_BIND_GOLD						= GLOBALCOUNTER_INT_FIELD_DAILY_ADD_BIND_GOLD + 2,	//ÿ�����İ�Ԫ������
	GLOBALCOUNTER_INT_FIELD_DAILY_ADD_GOLD_INGOT					= GLOBALCOUNTER_INT_FIELD_DAILY_SUB_BIND_GOLD + 2,		//ÿ������Ԫ������
	GLOBALCOUNTER_INT_FIELD_DAILY_SUB_GOLD_INGOT					= GLOBALCOUNTER_INT_FIELD_DAILY_ADD_GOLD_INGOT + 2,	//ÿ������Ԫ������
	GLOBALCOUNTER_INT_FIELD_DAILY_ADD_SILVER						= GLOBALCOUNTER_INT_FIELD_DAILY_SUB_GOLD_INGOT + 2,	//ÿ��������������
	GLOBALCOUNTER_INT_FIELD_DAILY_SUB_SILVER						= GLOBALCOUNTER_INT_FIELD_DAILY_ADD_SILVER + 2,	//ÿ��������������
	
	MAX_GLOBALCOUNTER_INT_FIELD,
};

// ��ͬ���ͻ��˵ļ�����
enum GlobalAsyncValueField
{

};

// ��ͼ����
enum MAP_TYPE
{
	MAP_TYPE_MAIN = 0,		//����
	MAP_TYPE_FIELD = 1,		//Ұ��
	MAP_TYPE_INSTANCE = 2,	//����
	MAP_TYPE_ACTIVITY = 3,	//�
	MAP_TYPE_PVP = 4,		//PVP
};

// ������������
enum InstanceQuestType
{
	INSTANCE_QUEST_TYPE_KILL_MONSTER = 1,	//��ɱ����(creatureId, num)
	INSTANCE_QUEST_TYPE_PICK_ITEM = 2,		//�ռ���Ʒ
	INSTANCE_QUEST_TYPE_ACTIVE_MACHINE = 3,	//�������
	INSTANCE_QUEST_TYPE_PROTECT_NPC = 4,	//�ػ�NPC
	INSTANCE_QUEST_TYPE_ESCORT_NPC = 5,		//����NPC
	INSTANCE_QUEST_TYPE_DEFENSE = 6,		//����
	INSTANCE_QUEST_TYPE_BREAK_THROUGH  = 7,	//����
};

#define MAX_INSTANCE_QUEST_COUNT 12
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ͼ
enum EMapFileds
{
	MAP_INT_FIELD_MAP_ID								= 0,															//��ͼģ��ID
	MAP_INT_FIELD_INSTANCE_ID							= MAP_INT_FIELD_MAP_ID + 1,										//ʵ��ID
	MAP_INT_FIELD_LINE_NO								= MAP_INT_FIELD_INSTANCE_ID + 1,								//����ID
	MAP_INT_FIELD_WARID									= MAP_INT_FIELD_INSTANCE_ID + 1,								//����id
	MAP_INT_FIELD_KUAFU_TYPE							= MAP_INT_FIELD_WARID + 1,										//�������
	MAP_INT_FIELD_STATE									= MAP_INT_FIELD_KUAFU_TYPE + 1,									//0.��ͼ��״̬,1.��ͼС״̬,2.��ͼ�Զ�����ʱ��,3Ԥ��״̬
	MAP_INT_FIELD_KILL_NUM								= MAP_INT_FIELD_STATE + 1,										//ɱ����
	MAP_INT_FIELD_RESERVE1								= MAP_INT_FIELD_KILL_NUM + 1,									//�����ֶ�1
	MAP_INT_FIELD_RESERVE2								= MAP_INT_FIELD_RESERVE1 + 1,									//�����ֶ�2
	MAP_INT_FIELD_RESERVE3								= MAP_INT_FIELD_RESERVE2 + 1,									//�����ֶ�3 ��ǰ����
	MAP_INT_FIELD_RESERVE4								= MAP_INT_FIELD_RESERVE3 + 1,									//�����ֶ�4 �жϸ����Ƿ��ʼ��
	MAP_INT_FIELD_INSTANCE_WAVE							= MAP_INT_FIELD_RESERVE4 + 1,									//����2shorts(0:��ǰ����,1:�ܲ���)

	MAP_INT_FIELD_QUESTS_START							= MAP_INT_FIELD_INSTANCE_WAVE + 1,									//��������ʼ
	MAP_INT_FIELD_QUESTS_END							= MAP_INT_FIELD_QUESTS_START + MAX_INSTANCE_QUEST_COUNT * 2,							//�����������

	MAP_INT_FIELD_QUESTS_PROCESS_START					= MAP_INT_FIELD_QUESTS_END,												//���ȿ�ʼ
	MAP_INT_FIELD_QUESTS_PROCESS_END					= MAP_INT_FIELD_QUESTS_PROCESS_START + MAX_INSTANCE_QUEST_COUNT / 4,	//���Ƚ���

	MAP_INT_FIELD_CREATE_TM								= MAP_INT_FIELD_QUESTS_PROCESS_END,										//��������ʱ��
	MAP_INT_FIELD_START_TM								= MAP_INT_FIELD_CREATE_TM + 1,											//������ʼʱ��
	MAP_INT_FIELD_QUEST_END_TM							= MAP_INT_FIELD_START_TM + 1,											//�����������ʱ��
	MAP_INT_FIELD_END_TM								= MAP_INT_FIELD_QUEST_END_TM + 1,										//��������ʱ��
	MAP_INT_FIELD_INSTANCE_TYPE							= MAP_INT_FIELD_END_TM + 1,												//��������
	
	//��ͼ�ַ�������
	MAP_STR_GENERAL_ID									= BINLOG_STRING_FIELD_OWNER + 1,
	MAP_STR_REWARD										= MAP_STR_GENERAL_ID + 1,		//����������Ʒ�ַ���
};

//С��½��ˢ
enum REFRESH_MONSTER_FIELDS
{
	REFRESH_MONSTER_FIELD_ID			=	MAP_INT_FIELD_INSTANCE_TYPE + 4,	//2��short(0:��ǰ�Ѿ�ˢ��,1:�ܹ���Ҫˢ���ٹ�)
	REFRESH_MONSTER_FIELD_INFO_START	=	REFRESH_MONSTER_FIELD_ID + 1,		//������Ϣ��ʼ2��short(0:entry,1:level)
};

enum KUAFU_3v3_PLAYER_INFO
{
	KUAFU_3V3_PLAYER_DAMAGE		= 0,								// �˺�
	KUAFU_3V3_PLAYER_SHOW_INFO	= KUAFU_3V3_PLAYER_DAMAGE + 2,		// 2��byte, 1short(byte0:gender, byte1:hprate, short1:level)
	KUAFU_3V3_PLAYER_SETTLEMENT	= KUAFU_3V3_PLAYER_SHOW_INFO + 1,	// ������Ϣ, 4bytes(0:��ɱ����,1:����״̬,2:������Ӫ,3:����)
	KUAFU_3V3_PLAYER_HONOR		= KUAFU_3V3_PLAYER_SETTLEMENT + 1,	// ������ȫ�����, 4bytes(0:�������, 1:ȫ�����,2:����,3:����)
	MAX_KUAFU_3V3_INT_COUNT,										// kuafu��������

	KUAFU_3V3_PLAYER_NAME		= 0,								//�������
	KUAFU_3V3_PLAYER_GUID		= KUAFU_3V3_PLAYER_NAME + 1,		//���guid
	MAX_KUAFU_3V3_STR_COUNT,
};

#define MAX_KUAFU_3V3_COUNT 6
// ���3v3ƥ��
enum KUAFU_3V3_FIELDS 
{
	KUAFU_3V3_FIELDS_INT_INFO_START	= MAP_INT_FIELD_INSTANCE_TYPE + 1,														// ������ݿ�ʼ
	KUAFU_3V3_FIELDS_INT_INFO_END	= KUAFU_3V3_FIELDS_INT_INFO_START + MAX_KUAFU_3V3_COUNT * MAX_KUAFU_3V3_INT_COUNT,		// 3v3�ܹ�6����
	
	KUAFU_3V3_FIELDS_STR_INFO_START	= MAP_STR_REWARD + 1,																// �ַ������ݿ�ʼ
	KUAFU_3V3_FIELDS_STR_INFO_END	= KUAFU_3V3_FIELDS_STR_INFO_START + MAX_KUAFU_3V3_COUNT * MAX_KUAFU_3V3_STR_COUNT,	// �ַ������ݽ���
};


// �ɸ��ᱦ �����Ϣ
enum KUAFU_XIANFU_PLAYER_INFO
{
	KUAFU_XIANFU_PLAYER_SETTLEMENT		= 0,									// ���ս��
	KUAFU_XIANFU_PLAYER_MONEY			= KUAFU_XIANFU_PLAYER_SETTLEMENT + 2,	// Ԫ������
	KUAFU_XIANFU_PLAYER_MONEY_CHANGED	= KUAFU_XIANFU_PLAYER_MONEY + 2,		// Ԫ���ı�ֵ
	KUAFU_XIANFU_PLAYER_SHOW_INFO		= KUAFU_XIANFU_PLAYER_MONEY_CHANGED + 2,// 4��byte(byte0:��������, byte1:��ɱ����, byte2:��ɱBOSS����,byte3:��ɱ����)
	MAX_KUAFU_XIANFU_INT_COUNT,													// kuafu��������

	KUAFU_XIANFU_PLAYER_NAME			= 0,									//�������
	KUAFU_XIANFU_PLAYER_GUID			= KUAFU_XIANFU_PLAYER_NAME + 1,			//���guid
	MAX_KUAFU_XIANFU_STR_COUNT,
};

enum KUAFU_XIANFU_BOSS_INFO
{
	KUAFU_XIANFU_BOSS_SHOW_INFO		= 0,									// 2 shorts(0:entry, 1:����״̬)
	KUAFU_XIANFU_BOSS_BORN_INFO		= KUAFU_XIANFU_BOSS_SHOW_INFO + 1,		// �Ƿ�ˢ��
	KUAFU_XIANFU_BOSS_BORN_TIME		= KUAFU_XIANFU_BOSS_BORN_INFO + 1,		// ˢ��ʱ���
	MAX_KUAFU_XIANFU_BOSS_INT_COUNT,										//
};

#define MAX_KUAFU_XIANFU_COUNT 10

#define MAX_KUAFU_XIANFU_BOSS_COUNT 5
// ����ɸ��ᱦƥ��
enum KUAFU_XIANFU_FIELDS 
{
	KUAFU_XIANFU_FIELDS_INT_INFO_START		= MAP_INT_FIELD_INSTANCE_TYPE + 1,														// ������ݿ�ʼ
	KUAFU_XIANFU_FIELDS_INT_INFO_END		= KUAFU_XIANFU_FIELDS_INT_INFO_START + MAX_KUAFU_XIANFU_COUNT * MAX_KUAFU_XIANFU_INT_COUNT,		// 3v3�ܹ�6����
	
	KUAFU_XIANFU_FIELDS_INT_BOSS_INDX		= KUAFU_XIANFU_FIELDS_INT_INFO_END,		//��ǰ��bossid
	KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_START	= KUAFU_XIANFU_FIELDS_INT_BOSS_INDX + 1,	//BOSS��Ϣ��ʼ
	KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_END	= KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_START + MAX_KUAFU_XIANFU_BOSS_INT_COUNT * MAX_KUAFU_XIANFU_BOSS_COUNT,

	KUAFU_XIANFU_FIELDS_HARD				= KUAFU_XIANFU_FIELDS_INT_BOSS_INFO_END,	//�����Ѷ�
	XIANFU_TEST_DUMMY_COUNT					= KUAFU_XIANFU_FIELDS_HARD + 1,				//��������
	

	KUAFU_XIANFU_FIELDS_STR_INFO_START	= MAP_STR_REWARD + 1,																// �ַ������ݿ�ʼ
	KUAFU_XIANFU_FIELDS_STR_INFO_END	= KUAFU_XIANFU_FIELDS_STR_INFO_START + MAX_KUAFU_XIANFU_COUNT * MAX_KUAFU_XIANFU_STR_COUNT,	// �ַ������ݽ���
};


// �����������Ϣ
enum KUAFU_GROUP_INSTANCE_PLAYER_INFO
{
	KUAFU_GROUP_INSTANCE_PLAYER_DAED_TIMES		= 0,									// �����Ϣ(0:��������)
	KUAFU_GROUP_INSTANCE_PLAYER_REBRON_CD		= KUAFU_GROUP_INSTANCE_PLAYER_DAED_TIMES + 1,	//ԭ�ظ���cd
	MAX_KUAFU_GROUP_INSTANCE_PLAYER_INT_COUNT,											// kuafu��������

	KUAFU_GROUP_INSTANCE_PLAYER_NAME			= 0,									//�������
	KUAFU_GROUP_INSTANCE_PLAYER_GUID			= KUAFU_GROUP_INSTANCE_PLAYER_NAME + 1,	//���guid
	KUAFU_GROUP_INSTANCE_PLAYER_REWARDS			= KUAFU_GROUP_INSTANCE_PLAYER_GUID + 1,	//��ҽ���
	MAX_KUAFU_GROUP_INSTANCE_PLAYER_STR_COUNT,
};

#define MAX_GROUP_INSTANCE_PLAYER_COUNT 3
//������
enum KUAFU_GROUP_INSTANCE_FIELDS
{
	KUAFU_GROUP_INSTANCE_FIELDS_HARD = MAP_INT_FIELD_INSTANCE_TYPE + 1,			// �Ѷ�
	KUAFU_GROUP_INSTANCE_FIELDS_PART = KUAFU_GROUP_INSTANCE_FIELDS_HARD + 1,	// ��Ӹ����ĵڼ�����

	KUAFU_GROUP_INSTANCE_INT_FIELDS_PLAYER_INFO_START = KUAFU_GROUP_INSTANCE_FIELDS_PART + 1,	//
	KUAFU_GROUP_INSTANCE_INT_FIELDS_PLAYER_INFO_END	  = KUAFU_GROUP_INSTANCE_INT_FIELDS_PLAYER_INFO_START + MAX_KUAFU_GROUP_INSTANCE_PLAYER_INT_COUNT * MAX_GROUP_INSTANCE_PLAYER_COUNT,

	KUAFU_GROUP_INSTANCE_STR_FIELDS_PLAYER_INFO_START = KUAFU_GROUP_INSTANCE_FIELDS_PART + 1,	//
	KUAFU_GROUP_INSTANCE_STR_FIELDS_PLAYER_INFO_END	  = KUAFU_GROUP_INSTANCE_STR_FIELDS_PLAYER_INFO_START + MAX_KUAFU_GROUP_INSTANCE_PLAYER_STR_COUNT * MAX_GROUP_INSTANCE_PLAYER_COUNT,
};


enum DOUJIANTAI_FIELDS
{
	DOUJIANTAI_FIELDS_INT_RANK	= MAP_INT_FIELD_INSTANCE_TYPE + 1,			// 2 shorts (0:�Լ�������, 1:���ֵ�����)
	DOUJIANTAI_FIELDS_INT_COMBAT_WIN_INFO = DOUJIANTAI_FIELDS_INT_RANK + 1,	// 2 shorts (0:��ʷ�����ʤ, 1:��ǰ��ʤ)
};

enum XIULIANCHANG_FIELDS
{
	XIULIANCHANG_FIELDS_INT_RANK	= MAP_INT_FIELD_INSTANCE_TYPE + 1,			// ���˶���̨����
	XIULIANCHANG_FIELDS_INT_ROBOT_ID = XIULIANCHANG_FIELDS_INT_RANK + 1,	// ���˻��������
	XIULIANCHANG_FIELDS_INT_LEVEL	= XIULIANCHANG_FIELDS_INT_ROBOT_ID + 1,		//���˵ȼ� ���㾭����

	XIULIANCHANG_FIELDS_STR_INFO_GUID	= MAP_STR_REWARD + 1,				//����guid
	XIULIANCHANG_FIELDS_STR_INFO_CONTENT	= XIULIANCHANG_FIELDS_STR_INFO_GUID + 1,				//��������content  
	XIULIANCHANG_FIELDS_STR_INFO_NAME	= XIULIANCHANG_FIELDS_STR_INFO_CONTENT + 1,				//��������


};

//VIP BOSS

enum VIP_INSTANCE_FIELDS
{
	VIP_INSTANCE_FIELD_ID = MAP_INT_FIELD_INSTANCE_TYPE + 1,	// 0:VIP�������,1:�����Ѷ�
};

enum MAP_MASS_BOSS_FIELDS
{
	MAP_MASS_BOSS_INT_FIELD_ID	= MAP_INT_FIELD_INSTANCE_TYPE + 1,	//ȫ��bossid
};

enum WORLDBOSS_ENROLL_FIELDS
{
	WORLDBOSS_FIELDS_WAIT_TIME	=	MAP_INT_FIELD_INSTANCE_TYPE + 1,	//�����ȴ�ʱ���
};

enum WORLDBOSS_FIELDS
{
	WORLDBOSS_FIELDS_BORN_TIME	=	WORLDBOSS_FIELDS_WAIT_TIME + 1,		//ˢ�µȴ�ʱ���
};

enum RESOURCE_INSTANCE_FIELDS
{
	RES_INSTANCE_FIELD_ID = MAP_INT_FIELD_INSTANCE_TYPE + 1,	//��Դ����������
};


//����ð��
enum RISK_INSTANCE_FIELDS
{
	TRIAL_INSTANCE_FIELD_CURSOR		= MAP_INT_FIELD_INSTANCE_TYPE + 1,		//��ǰ�Ѿ�ˢ�˶��ٲ���
	TRIAL_INSTANCE_FIELD_SECTION_ID	= TRIAL_INSTANCE_FIELD_CURSOR + 1,		//�ؿ�id
	TRIAL_INSTANCE_FIELD_ORDER		= TRIAL_INSTANCE_FIELD_SECTION_ID + 1,	//ˢ�����ȼ����(1��byte��һ������)
	TRIAL_INSTANCE_FIELD_BOSS_REFRESHED = TRIAL_INSTANCE_FIELD_ORDER + 2,	//�Ƿ��Ѿ�ˢ��
	TRIAL_INSTANCE_FIELD_LAST_RANDOM_TIMESTAMP = TRIAL_INSTANCE_FIELD_BOSS_REFRESHED + 1,	//������ˢ��ʱ���
};

//���峡��
enum FACTION_INSTANCE_FIELDS
{
	FACTION_INSTANCE_FIELD_GUID = MAP_STR_REWARD + 1,	// ����GUID string
};

//����������ս����
enum FACTION_BOSSDEFENSE_INSTANCE_FIELDS
{
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_BUILDING_LV = MAP_INT_FIELD_INSTANCE_TYPE + 1,	//���彨���ȼ�
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_INDEX = FACTION_BOSSDEFENSE_INSTANCE_FIELD_BUILDING_LV + 1,	//boss�� index
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_POOL_ID = FACTION_BOSSDEFENSE_INSTANCE_FIELD_INDEX + 1,		//����� id
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_HP = FACTION_BOSSDEFENSE_INSTANCE_FIELD_POOL_ID + 1,			//����ʣ��hp

	FACTION_BOSSDEFENSE_INSTANCE_FIELD_PLAYER_GUID = MAP_STR_REWARD + 1,	// ���GUID string
	FACTION_BOSSDEFENSE_INSTANCE_FIELD_FACTION_GUID = FACTION_BOSSDEFENSE_INSTANCE_FIELD_PLAYER_GUID + 1,	// ����GUID string
};

//�����޾�Զ������
enum FACTION_TOWER_INSTANCE_FIELDS
{
	FACTION_TOWER_INSTANCE_FIELD_FLOOR = MAP_INT_FIELD_INSTANCE_TYPE + 1,	// ��ǰ����
	FACTION_TOWER_INSTANCE_FIELD_BUFF = FACTION_TOWER_INSTANCE_FIELD_FLOOR + 1,	// ��һ�õ�buffeffect_id
	FACTION_TOWER_INSTANCE_FIELD_DEBUFF = FACTION_TOWER_INSTANCE_FIELD_BUFF + 1, //��һ�õ�debuffeffect_id
	FACTION_TOWER_INSTANCE_FIELD_MONSTER_NUM = FACTION_TOWER_INSTANCE_FIELD_DEBUFF + 1, //��ǰ��������
};

//������
enum TRIAL_INSTANCE_FIELDS
{
	TRIAL_INSTANCE_FIELD_ID = MAP_INT_FIELD_INSTANCE_TYPE + 1,	// ��ǰ����
};

// �һ��������ˢ�´���
#define TAOHUA_REFRESH_TIMES 10;
//�һ������ͼ����
enum TaoHuaMiZhenFileds {
	TAOHUA_INT_FIELD_REFRESH_TIMES = MAP_INT_FIELD_INSTANCE_TYPE + 1,		//�һ������Ѿ�ˢ�´���
	TAOHUA_INT_FIELD_BOSS_CURR_HP = TAOHUA_INT_FIELD_REFRESH_TIMES + 1,		//BOSS��ǰѪ��

	TAOHUA_STR_FIELD_REAL_BOSS_GUID = MAP_STR_GENERAL_ID + 1,	//BOSS����GUID
};

//����������
#define TOWER_MAX_FLOOR = 2;
//����ÿ���ɱ����
enum TaGuaiKillCountFields {
	TAGUAI_INT_FIELD_FIRST_FLOOR = MAP_INT_FIELD_INSTANCE_TYPE + 1,		//��һ�����Ϣ
};

//ս����Ϣ�����ַ���ö��
//ò��û��Ҫ,�����һ����
enum FightingInfoStringType
{
	FIGHTING_INFO_STRING_CASTER		= 0,								//ʩ����
	FIGHTING_INFO_STRING_TARGET		= FIGHTING_INFO_STRING_CASTER + 1,		//Ŀ��
	MAX_FIGHTING_INFO_STRING,
};

//ս����Ϣ�������
#define MAX_FIGHTING_INFO_COUNT 100

//ս����Ϣ�����ֶ�ö��
enum FightingInfoIntType
{
	FIGHTING_INFO_INT_VALUES		= 0,		//�˺��������� ���Ʒ�����
	FIGHTING_INFO_INT_UINT8			= FIGHTING_INFO_INT_VALUES + 2,	//0:�Ƿ�ɱ 1:ʩ�����������ͣ���һ������2:Ŀ���������ͣ���һ������ 3:�˺�����(����������֮���)
	FIGHTING_INFO_INT_SPELL_ID		= FIGHTING_INFO_INT_UINT8 + 1,		//����id
	FIGHTING_INFO_INT_HP			= FIGHTING_INFO_INT_SPELL_ID + 1,	//���ܼ������Ժ�����ʣ��Ѫ��
	FIGHTING_INFO_INT_RESERVE_0		= FIGHTING_INFO_INT_HP + 1,	//Ԥ��
	FIGHTING_INFO_INT_RESERVE_1		= FIGHTING_INFO_INT_RESERVE_0 + 1,	//Ԥ��	
	FIGHTING_INFO_INT_RESERVE_2		= FIGHTING_INFO_INT_RESERVE_1 + 1,	//Ԥ��
	FIGHTING_INFO_INT_RESERVE_3		= FIGHTING_INFO_INT_RESERVE_2 + 1,	//Ԥ��	
	MAX_FIGHTING_INFO_INT,
};

//ս����Ϣ�ֶ�
enum EFightingInfoFields
{
	MAX_FIGHTING_INFO_INT_NOW_INDEX		= 0,	//��ǰս������Ϣ�±��õ��ڼ���ս����Ϣ��
	MAX_FIGHTING_INFO_INT_START			= MAX_FIGHTING_INFO_INT_NOW_INDEX + 1,
	MAX_FIGHTING_INFO_INT_FIELD			= MAX_FIGHTING_INFO_INT_START + MAX_FIGHTING_INFO_INT * MAX_FIGHTING_INFO_COUNT,

	FIGHTING_INFO_STRING_FIELD_START	= BINLOG_STRING_FIELD_OWNER + 1,
	MAX_FIGHTING_INFO_STRING_FIELD		= FIGHTING_INFO_STRING_FIELD_START + MAX_FIGHTING_INFO_STRING * MAX_FIGHTING_INFO_COUNT,
}; 

//��ѯ�õ������Ϣbinlog
enum EQueryPlayerFileds
{
	QUERY_PLAYER_INT_UINT16			= 0,								//0 �ȼ���1 ��ʯ�ȼ�
	QUERY_PLAYER_INT_BYTE1			= QUERY_PLAYER_INT_UINT16 + 1,		//0 ͷ��1 ���ͣ�2 ���壬3 �Ա�
	QUERY_PLAYER_INT_BYTE2			= QUERY_PLAYER_INT_BYTE1 + 1,		//0 ��Ӫ��1 �Ƿ����ߣ�2 �ƺ�,3 vip
	// ��������
	QUERY_PLAYER_INT_BASE_ATTR_START		= QUERY_PLAYER_INT_BYTE2 + 1,										//��һ������Կ�ʼ
	QUERY_PLAYER_INT_BASE_ATTR_END			= QUERY_PLAYER_INT_BASE_ATTR_START + MAX_BASE_ATTR * 2,		//��һ������Խ���
	QUERY_PLAYER_INT_FIXED_ATTR_START		= QUERY_PLAYER_INT_BASE_ATTR_END,							//��ҹ̶����Կ�ʼ
	QUERY_PLAYER_INT_FIXED_ATTR_END			= QUERY_PLAYER_INT_FIXED_ATTR_START + MAX_BASE_ATTR * 2,		//��ҹ̶����Խ���	
	QUERY_PLAYER_INT_LUCKY					= QUERY_PLAYER_INT_FIXED_ATTR_END,				//����
	QUERY_PLAYER_INT_MEILI					= QUERY_PLAYER_INT_LUCKY + 2,					//����
	QUERY_PLAYER_INT_BEAR					= QUERY_PLAYER_INT_MEILI + 2,					//����
	QUERY_PLAYER_INT_POISON					= QUERY_PLAYER_INT_BEAR + 2,					//��
	QUERY_PLAYER_INT_ICE					= QUERY_PLAYER_INT_POISON + 2,					//��
	QUERY_PLAYER_MOVESPEED					= QUERY_PLAYER_INT_ICE + 2,						//�ƶ��ٶ�
	QUERY_PLAYER_PHYSICAL					= QUERY_PLAYER_MOVESPEED + 2,					//����
	QUERY_PLAYER_INT_FORCE					= QUERY_PLAYER_PHYSICAL + 2,					//ս����
	QUERY_PLAYER_ONLINE_TIME				= QUERY_PLAYER_INT_FORCE + 2,					//������ʱ��
	// ���ϵ�װ��
	QUERY_PLAYER_INT_EQUIPMENT				= QUERY_PLAYER_ONLINE_TIME + 1,
	QUERY_PLAYER_INT_EQUIPMENT_END			= QUERY_PLAYER_INT_EQUIPMENT + EQUIPMENT_TYPE_MAX_POS,

	QUERY_PLAYER_INT_FLAG				= QUERY_PLAYER_INT_EQUIPMENT_END,		//��ѯĳЩ��־λ
	QUERY_PLAYER_INT_FORCE_LEVEL		= QUERY_PLAYER_INT_FLAG + 1,			//�ȼ�ս����PLAYER_INT_PIFENG_ZIZHI_FORCE
	QUERY_PLAYER_INT_FORCE_ITEM			= QUERY_PLAYER_INT_FORCE_LEVEL + 2,		//װ��ս����
	QUERY_PLAYER_INT_FORCE_FACTION		= QUERY_PLAYER_INT_FORCE_ITEM + 2,		//����ս����
	QUERY_PLAYER_INT_FLAG_TYPE			= QUERY_PLAYER_INT_FORCE_FACTION + 2,	//��ǰ��Ҳ�ѯ���ͱ�־
	QUERY_PLAYER_INT_FORGING_STRENG		= QUERY_PLAYER_INT_FLAG_TYPE + 1,		//0 ��ѯ���ǿ���ȼ���1 Ԥ�� 16λ


	QUERY_PLAYER_STRING_GUID				= BINLOG_STRING_FIELD_OWNER + 1,		//��Ҫֱ�ӷŵ�guidȥ���»���
	QUERY_PLAYER_STRING_NAME				= QUERY_PLAYER_STRING_GUID + 1,			//�������
	QUERY_PLAYER_STRING_FACTION_ID			= QUERY_PLAYER_STRING_NAME + 1,			//����ID
	QUERY_PLAYER_STRING_FACTION_NAME		= QUERY_PLAYER_STRING_FACTION_ID + 1,	//��������

	MAX_QUERY_PLAYER_STRING_FIELD,
};

/////////////////////////////////////�鿴��Ʒ//////////////////////////////////////////////////////////////////////////
//�鿴��Ʒ�±�
enum ItemQueryField
{
	////////////////////int����///////////////////////////////////////
	ITEM_QUERY_INT_FIELD_COUNT = 0,
	////////////////////string����///////////////////////////////////////
	ITEM_QUERY_STR_FIELD_START	= BINLOG_STRING_FIELD_OWNER + 1,
};

//�����Ϣ��¼����ö��
enum GiftPacksInfoType
{
	GIFTPACKS_INFO_INT_ID			= 0,	//���ID
	GIFTPACKS_INFO_INT_START_TIME	= 1,	//����ʱ��
	GIFTPACKS_INFO_INT_END_TIME		= 2,	//����ʱ��
	GIFTPACKS_INFO_INT_BYTE			= 3,	//0,������ͣ�1����ȡ״̬,2 ���Ķ�,3�Ƿ�ɾ��
	MAX_GIFTPACKS_INFO_INT,

	GIFTPACKS_INFO_STRING_GIFT_NAME	= 0,	//�������
	GIFTPACKS_INFO_STRING_GIFT_DESC	= 1,	//���˵��
	GIFTPACKS_INFO_STRING_GIFT_FROM = 2,	//������������������ʱ��д������֣�Ĭ��Ϊ�գ�ϵͳ����
	GIFTPACKS_INFO_STRING_GIFT_ITEM = 3,	//�����Ʒ����
	MAX_GIFTPACKS_INFO_STRING,
};

//�����Ϣ�������
#define MAX_GIFTPACKS_INFO_COUNT 100

//�����Ϣbinlog
enum GiftPacksInfoFileds
{
	MAX_GIFTPACKS_INFO_INT_NOW_INDEX			= 0,	//��ǰ�����Ϣ�±�����
	GIFTPACKS_INT_FIELD_BEGIN					= MAX_GIFTPACKS_INFO_INT_NOW_INDEX + 1,		
	MAX_GIFTPACKS_INT_FIELD						= GIFTPACKS_INT_FIELD_BEGIN + MAX_GIFTPACKS_INFO_COUNT * MAX_GIFTPACKS_INFO_INT,	

	GIFTPACKS_STRING_FIELD_BEGIN				=  BINLOG_STRING_FIELD_OWNER + 1,		
	MAX_GIFTPACKS_STRING_FIELD					= GIFTPACKS_STRING_FIELD_BEGIN + MAX_GIFTPACKS_INFO_COUNT * MAX_GIFTPACKS_INFO_STRING,	
};

//��������
enum ERankTypes
{
	RANK_TYPE_POWER					= 0,							//ս��������
	RANK_TYPE_LEVEL					= 1,							//�ȼ�����
	RANK_TYPE_MONEY					= 2,							//�Ƹ�����
	RANK_TYPE_ONLINE_TIME			= 3,							//����ʱ������
	RANK_TYPE_TRIAL					= 4,							//����������
	RANK_TYPE_FACTION				= 5,							//��������
	RANK_TYPE_DIVINE				= 6,							//�������
	RANK_TYPE_MOUNT					= 7,							//��������
	RANK_TYPE_SINGLE_PVP			= 8,							//����PVP����
	RANK_TYPE_WINGS					= 9,							//�������

	MAX_RANK_TYPE
};

//�����������а�
enum ERankSpecTypes
{
	RANK_TYPE_DOUJIANTAI			= MAX_RANK_TYPE+1,//����̨����
};

//�������а������������
#define RANK_LIST_MAX_VALUES 100
#define RANK_LIST_MAX_SHOW 4

//���а����binlog�±�
enum ERankListCurrentObjFiled
{
	RANK_LIST_CURRENT_OBJ_INT_FIELD_TYPE			= 0,												//���а�����
	RANK_LIST_CURRENT_OBJ_INT_FIELD_RANKING			= 1,												//����
	RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE			= 2,												//byte 0���Ա�����
	RANK_LIST_CURRENT_OBJ_INT_FIELD_BYTE2			= 3,												//ͨ���ֶ�
	RANK_LIST_CURRENT_OBJ_INT_FIELD_TITLE			= 4,												//�ƺ�
	//���а�
	RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE			= RANK_LIST_CURRENT_OBJ_INT_FIELD_TITLE + 1,		//ս����
	RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL			= RANK_LIST_CURRENT_OBJ_INT_FIELD_FORCE + 2,		//�ȼ�
	RANK_LIST_CURRENT_OBJ_INT_FIELD_MONEY			= RANK_LIST_CURRENT_OBJ_INT_FIELD_LEVEL + 1,	//ͭǮ
	RANK_LIST_CURRENT_OBJ_INT_FIELD_ONLINE_TIME		= RANK_LIST_CURRENT_OBJ_INT_FIELD_MONEY + 2,	//����ʱ��
	RANK_LIST_CURRENT_OBJ_INT_FIELD_TRIAL			= RANK_LIST_CURRENT_OBJ_INT_FIELD_ONLINE_TIME + 1,	//����������
	RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW			= RANK_LIST_CURRENT_OBJ_INT_FIELD_TRIAL + 1,					//����б�ʼ
	RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW_END		= RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW + RANK_LIST_MAX_SHOW,	//��۽���
	RANK_LIST_CURRENT_OBJ_INT_FIELD_LIKE			= RANK_LIST_CURRENT_OBJ_INT_FIELD_SHOW_END + 1,//������
	RANK_LIST_CURRENT_OBJ_INT_FIELD_WING			= RANK_LIST_CURRENT_OBJ_INT_FIELD_LIKE + 1,		//���id

	RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID			= BINLOG_STRING_FIELD_OWNER + 1,
	RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID		= RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID + 1,				//���guid
	RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_NAME		= RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_GUID + 1,		//�������
	RANK_LIST_CURRENT_OBJ_STR_FIELD_FACTION_NAME	= RANK_LIST_CURRENT_OBJ_STR_FIELD_PLAYER_NAME + 1,		//��������
};
enum ERankListFactionObjFiled
{
	RANK_LIST_INT_FIELD_FACTION_LEV		= RANK_LIST_CURRENT_OBJ_INT_FIELD_RANKING + 1,//byte 0���Ա�
	RANK_LIST_INT_FIELD_FACTION_COUNT	= RANK_LIST_INT_FIELD_FACTION_LEV + 1,
	RANK_LIST_INT_FIELD_FACTION_BYTE	= RANK_LIST_INT_FIELD_FACTION_COUNT + 1,//icon minlev

	RANK_LIST_STR_FIELD_FACTION_GUID	= RANK_LIST_CURRENT_OBJ_STR_FIELD_GUID,//����GUID
	RANK_LIST_STR_FIELD_FACTION_NAME	= RANK_LIST_STR_FIELD_FACTION_GUID + 1,//��������
	RANK_LIST_STR_FIELD_FACTION_SQGG	= RANK_LIST_STR_FIELD_FACTION_NAME + 1,//�������빫��
};

enum ItemShowType
{
	ITEM_SHOW_TYPE_DEFAULT				= 0,	//Ĭ����ʾ
	ITEM_SHOW_TYPE_MINI_QUEST_BAR		= 1,	//С�������
	ITEM_SHOW_TYPE_MINI_QUEST_DAILY2	= 2,	//�ճ��������
};


//���������¼����ö��
enum RightFloatInfoType
{
	RIGHTFLOAT_INFO_INT_ID				= 0,	//����ID
	RIGHTFLOAT_INFO_INT_START_TIME		= 1,	//��ʼʱ��
	RIGHTFLOAT_INFO_INT_END_TIME		= 2,	//����ʱ��
	RIGHTFLOAT_INFO_INT_ZONE_1			= 3,	//0-7��
	RIGHTFLOAT_INFO_INT_ZONE_2			= 4,	//8-13��
	RIGHTFLOAT_INFO_INT_ZONE_3			= 5,	//14-23��
	RIGHTFLOAT_INFO_INT_BYTE			= 6,	//0 ��������,1 ����״̬,2 Ԥ��,3 Ԥ��
	RIGHTFLOAT_INFO_INT_ADD_TIME		= 7,	//���ʱ��
	MAX_RIGHTFLOAT_INFO_INT,			

	RIGHTFLOAT_INFO_STRING_SUBJECT		= 0,	//����
	RIGHTFLOAT_INFO_STRING_CONTENT		= 1,	//����
	RIGHTFLOAT_INFO_STRING_LINK			= 2,	//���ӵ�ַ
	MAX_RIGHTFLOAT_INFO_STRING,
};

//������Ϣ�������
#define MAX_RIGHTFLOAT_INFO_COUNT 100

//����������Ϣbinlog
enum RightFloatInfoFileds
{
	MAX_RIGHTFLOAT_INFO_INT_NOW_INDEX			= 0,	//��ǰ����������Ϣ�±�����
	RIGHTFLOAT_INT_FIELD_START					= MAX_RIGHTFLOAT_INFO_INT_NOW_INDEX + 1,		
	MAX_RIGHTFLOAT_INT_FIELD						= RIGHTFLOAT_INT_FIELD_START + MAX_RIGHTFLOAT_INFO_COUNT * MAX_RIGHTFLOAT_INFO_INT,	

	RIGHTFLOAT_STRING_FIELD_START				=  BINLOG_STRING_FIELD_OWNER + 1,		
	MAX_RIGHTFLOAT_STRING_FIELD					= RIGHTFLOAT_STRING_FIELD_START + MAX_RIGHTFLOAT_INFO_COUNT * MAX_RIGHTFLOAT_INFO_STRING,	
};


//��ʱ�binlog
enum LimitActivityInfoFileds
{
	LIMIT_ACTIVITY_INT_FIELD_VERSION				= 0,											//��汾��
	LIMIT_ACTIVITY_INT_FIELD_START_TIME				= LIMIT_ACTIVITY_INT_FIELD_VERSION + 1,			//���ʼʱ��
	LIMIT_ACTIVITY_INT_FIELD_END_TIME				= LIMIT_ACTIVITY_INT_FIELD_START_TIME + 1,		//�����ʱ��
	LIMIT_ACTIVITY_INT_FIELD_RECHARGE_SUM			= LIMIT_ACTIVITY_INT_FIELD_END_TIME + 1,		//��ֵ����
	LIMIT_ACTIVITY_INT_FIELD_RECHARGE_TIME			= LIMIT_ACTIVITY_INT_FIELD_RECHARGE_SUM + 1,	//����ֵʱ��
	LIMIT_ACTIVITY_INT_FIELD_REWARD_COUNT			= 100,											//���ȡ������ʼ
	LIMIT_ACTIVITY_INT_FIELD_REWARD_COUNT_END		= LIMIT_ACTIVITY_INT_FIELD_REWARD_COUNT + 400,	//���ȡ��������

	LIMIT_ACTIVITY_STRING_FIELD_RECHARGE_ID			= BINLOG_STRING_FIELD_OWNER + 1,				//����ֵID
	LIMIT_ACTIVITY_STRING_FIELD_CLIENT_CONFIG		= LIMIT_ACTIVITY_STRING_FIELD_RECHARGE_ID + 1,	//�ͻ�������
};

//������Ϣ�������
#define MAX_NOTICE_MESSAGE_NUMBER 100

//������Ϣ����
enum NoticeMessageInfoType
{
	NOTICE_MESSAGE_INFO_TYPE_FISHING		= 0,	//���㹫��
	NOTICE_MESSAGE_INFO_TYPE_MINING			= 1,	//�󶴹���
	NOTICE_MESSAGE_INFO_TYPE_WORLD_BOSS		= 2,	//����boss����
	NOTICE_MESSAGE_INFO_TYPE_KAIFUJIJIN		= 3,	//�������𹫸�
	MAX_MESSAGE_INFO_TYPE
};

//������Ϣbinlog
enum NoticeMessageInfoFileds
{
	NOTICE_MESSAGE_INT_FIELD_INDEX					= 0,											//����λ������
	NOTICE_MESSAGE_INT_FIELD_INDEX_END				= NOTICE_MESSAGE_INT_FIELD_INDEX + MAX_MESSAGE_INFO_TYPE,	//��������λ�ý���

	NOTICE_MESSAGE_STRING_FIELD_START				= BINLOG_STRING_FIELD_OWNER + 1,				//������Ϣ���ݿ�ʼ
	NOTICH_MESSAGE_STRING_FIELD_END					= NOTICE_MESSAGE_STRING_FIELD_START + MAX_NOTICE_MESSAGE_NUMBER * MAX_MESSAGE_INFO_TYPE,		//������Ϣ���ݽ���
};

//ϵͳ�ʼ���Ϣ��¼����ö��
enum SystemMailInfoType
{
	SYSTEM_MAIL_INFO_INT_ID				= 0,	//���ID
	SYSTEM_MAIL_INFO_INT_START_TIME		= 1,	//����ʱ��
	SYSTEM_MAIL_INFO_INT_END_TIME		= 2,	//����ʱ��
	SYSTEM_MAIL_INFO_INT_TYPE			= 3,	//�������
	MAX_SYSTEM_MAIL_INFO_INT,

	SYSTEM_MAIL_INFO_STRING_NAME	= 0,	//ϵͳ�ʼ�����
	SYSTEM_MAIL_INFO_STRING_DESC	= 1,	//ϵͳ�ʼ�˵��
	SYSTEM_MAIL_INFO_STRING_FROM	= 2,	//ϵͳ�ʼ����������������ʱ��д������֣�Ĭ��Ϊ�գ�ϵͳ����
	SYSTEM_MAIL_INFO_STRING_ITEM	= 3,	//�����Ʒ����
	MAX_SYSTEM_MAIL_INFO_STRING,
};

//ϵͳ�ʼ���Ϣ�������
#define MAX_SYSTEM_MAIL_INFO_COUNT 8192

// ϵͳ�ʼ�(��ȫ������Ч��)
enum SYSTEM_MAIL
{
	SYSTEM_MAIL_COUNT							= 0,				//ϵͳ�ʼ�����
	MAX_SYSTEM_MAIL_INFO_INT_NOW_INDEX			= 1,				//��ǰϵͳ�ʼ���Ϣ�±�����
	SYSTEM_MAIL_INT_FIELD_BEGIN					= MAX_SYSTEM_MAIL_INFO_INT_NOW_INDEX + 1,
	SYSTEM_MAIL_INT_FIELD_END					= SYSTEM_MAIL_INT_FIELD_BEGIN + MAX_SYSTEM_MAIL_INFO_COUNT * MAX_SYSTEM_MAIL_INFO_INT,

	SYSTEM_MAIL_STRING_FIELD_BEGIN				= BINLOG_STRING_FIELD_OWNER + 1,
	SYSTEM_MAIL_STRING_FIELD_END				= SYSTEM_MAIL_STRING_FIELD_BEGIN + MAX_SYSTEM_MAIL_INFO_COUNT * MAX_SYSTEM_MAIL_INFO_STRING,
};

//�����ʼ��������
#define MAX_OFFLINE_MAIL_INFO_COUNT 16384
// �����ʼ��洢�ط�
enum OfflineMailStore
{
	OFFLINE_MAIL_STORE_RANK_LEVEL = 0,	//�ȼ����а������ʼ��洢

	MAX_OFFLINE_MAIL_STORE_COUNT
};


//�йܲ���
enum HostingOptType
{
	HOSTING_OPT_TYPE_APPLY			= 0,	//�й�����
	HOSTING_OPT_TYPE_AGREED			= 1,	//�й�ͬ��
	HOSTING_OPT_TYPE_CANCEL			= 2,	//�й�ȡ��
	HOSTING_OPT_TYPE_LOGIN			= 3,	//�йܵ�¼
	HOSTING_OPT_TYPE_REFUSE			= 4,	//�йܾܾ�
	HOSTING_OPT_TYPE_DUE_TO			= 5,	//�йܵ���
	HOSTING_OPT_TYPE_APPLY_DUE_TO	= 6,	//�й����뵽��
};




//��λ��Ϣ����
#define MAX_EQUIP_PART_NUMBER 10

//һ����λ�ı�ʯ����
#define ONE_EQUIP_PART_GEM_NUMBER 6

// һ��װ����λ��Ϣ����
enum EquipPartOptType {
	EQUIP_PART_OPT_TYPE_STRENGTH_LEVEL_OFFSET = 0,												//ǿ���ȼ�ƫ��ֵ
	EQUIP_PART_OPT_TYPE_GEM_INFO_OFFSET = EQUIP_PART_OPT_TYPE_STRENGTH_LEVEL_OFFSET + 1,		//��ʯ��Ϣƫ��ֵ

	EQUIP_PART_OPT_TYPE_GEM_LEVEL_OFFSET = 0,													//��ʯ��Ϣ�б�ʯ�ȼ�ƫ��ֵ
	EQUIP_PART_OPT_TYPE_GEM_EXP_OFFSET = EQUIP_PART_OPT_TYPE_GEM_LEVEL_OFFSET + 1,				//��ʯ��Ϣ�б�ʯ����ƫ��ֵ
	EQUIP_PART_OPT_TYPE_ONE_GEM_INFO_LENGTH = EQUIP_PART_OPT_TYPE_GEM_EXP_OFFSET + 1,			//һ����ʯ��Ϣ�ĳ���

	EQUIP_PART_OPT_TYPE_ONE_PART_INFO_LENGTH = EQUIP_PART_OPT_TYPE_GEM_INFO_OFFSET + EQUIP_PART_OPT_TYPE_ONE_GEM_INFO_LENGTH * ONE_EQUIP_PART_GEM_NUMBER,	//һ��װ����λ����Ϣ����
	EQUIP_PART_OPT_TYPE_PARTS_INFO_LENGTH = EQUIP_PART_OPT_TYPE_ONE_PART_INFO_LENGTH * MAX_EQUIP_PART_NUMBER,												//����װ����λ����Ϣ���� 
};

// ҵ��BinLog
enum AppdLogicalInfoFields {
	APPD_LOGICAL_INFO_INT_FIELD_STRENGTH_START = 0,	//��λ��Ϣ����ʼλ��
	APPD_LOGICAL_INFO_INT_FIELD_STRENGTH_END_EXCLUDE = APPD_LOGICAL_INFO_INT_FIELD_STRENGTH_START + EQUIP_PART_OPT_TYPE_PARTS_INFO_LENGTH, //װ����λ�ı߽�
};


//�ı���������
enum TextType
{
	TEXT_TYPE_POSITION	= 1,				//����
	TEXT_TYPE_SUIT		= 2,				//װ��
	TEXT_TYPE_GROUP		= 3,				//�������
	TEXT_TYPE_INSTANCE	= 4,				//���븱��
};

// ��������Ч������
enum PASSIVE_EFFECT_TYPE
{
	PASSIVE_EFFECT_TYPE_SPELL_AMPLIFY		= 1,	//��ǿ����Ч��
	PASSIVE_EFFECT_TYPE_ADD_BUFF			= 2,	//����buffЧ��
	PASSIVE_EFFECT_TYPE_CHANGE_SPELL		= 3,	//�滻����Ч��
	PASSIVE_EFFECT_TYPE_PLAYER_ATTR			= 4,	//�����������
	PASSIVE_EFFECT_TYPE_ADDITIONAL_SPELL	= 5,	//�ͷŶ��⼼��
	PASSIVE_EFFECT_TYPE_PLAYER_LOOT_ATTR	= 6,	//�������ս��Ʒ
};

// �������ܴ�������
enum PASSIVE_DISPATCH_TYPE
{
	PASSIVE_DISPATCH_TYPE_FOREVER			= 0,	//����
	PASSIVE_DISPATCH_TYPE_ATTR_CHANGE		= 1,	//���Ըı�
	PASSIVE_DISPATCH_TYPE_HIT				= 2,	//�������е���
	PASSIVE_DISPATCH_TYPE_HURT				= 3,	//�ܵ�����
	PASSIVE_DISPATCH_TYPE_DEAD				= 4,	//����ʱ����
	PASSIVE_DISPATCH_TYPE_ENEMY_DEAD		= 5,	//�з�����
	PASSIVE_DISPATCH_TYPE_ON_BUFF			= 6,	//�ܵ�buff��ʱ�򴥷�
	PASSIVE_DISPATCH_TYPE_ENEMY_ON_BUFF		= 7,	//�з�ӵ��ĳ��buff��ʱ�򴥷�
};

//ϵͳģ��
enum MODULE_TYPE
{
	MODULE_SETTING = 101, //����
	MODULE_BAG = 102, //����
	MODULE_RONGLIAN = 103, //����
	MODULE_QUEST = 104, //����
	MODULE_DAILY_TASKS = 105, //�ճ�����
	MODULE_CHAT = 106, //����
	MODULE_MAIL = 107, //�ʼ�
	MODULE_MAP = 108, //��ͼ
	MODULE_STRENGTH = 109, //��Ҫ��ǿ
	MODULE_CHATPERSON = 110, //˽��
	MODULE_ACTIVE = 111, //��Ծ
	MODULE_MONEYTREE = 112, //ҡǮ��
	MODULE_ROLE = 201, //��ɫ
	MODULE_SPELL = 202, //����
	MODULE_DIVINE = 203, //����
	MODULE_FASHION = 204, //ʱװ
	MODULE_MOUNT = 205, //����
	MODULE_MIX = 206, //����
	MODULE_WING = 207, //���
	MODULE_TCM = 208, //����
	MODULE_SOCIAL = 301, //�罻
	MODULE_FACTION = 302, //����
	MODULE_RANK = 303, //���а�
	MODULE_FACTIONMAIN = 304, //����-��������
	MODULE_FACTIONSKILL = 305, //����-���ܴ���
	MODULE_FACTIONACTIVE = 306, //����-�����
	MODULE_FACTIONBOX = 307, //����-���屦��
	MODULE_MALL = 401, //�̳�
	MODULE_VIP = 402, //VIP��Ȩ
	MODULE_INSTANCE = 501, //����
	MODULE_WORLD_RISK = 502, //����ð��
	MODULE_ARENA = 503, //����
	MODULE_BOSS = 504, //BOSS
	MODULE_WELFARE = 601, //����
	MODULE_OPENSERVICE = 701, //�����
	MODULE_FIRST_RECHARGE = 801, //�׳�
	MODULE_SETTING_SYSTEM = 1, //����
	MODULE_BAG_ITEM = 1, //����
	MODULE_RONGLIAN_ALL = 1, //����
	MODULE_QUEST_MAIN = 1, //����
	MODULE_QUEST_EXTENSION = 2, //֧��
	MODULE_QUEST_ACTIVITY = 3, //�
	MODULE_DAILY_TASKS_ALL = 1, //�ճ�����
	MODULE_CHAT_ALL = 1, //����
	MODULE_MAIL_ALL = 1, //�ʼ�
	MODULE_MAP_REGION = 1, //����
	MODULE_MAP_WORLD = 2, //����
	MODULE_STRENGTH_ALL = 1, //��Ҫ��ǿ
	MODULE_CHATPERSON_ALL = 1, //����
	MODULE_ACTIVE_ALL = 1, //��Ծ
	MODULE_MONEYTREE_ALL = 1, //ҡǮ��
	MODULE_ROLE_ATTR = 1, //��ɫ����
	MODULE_ROLE_ACHIEVE = 2, //��ɫ�ɾ�
	MODULE_ROLE_TITLE = 3, //��ɫ�ƺ�
	MODULE_SPELL_ALL = 1, //����
	MODULE_DIVINE_ALL = 1, //����
	MODULE_FASHION_CLOTHES = 1, //�·�
	MODULE_FASHION_WEAPON = 2, //����
	MODULE_MOUNT_UPGRADE = 1, //����
	MODULE_MOUNT_LEVEL = 2, //����
	MODULE_MOUNT_SKILL = 3, //����
	MODULE_MOUNT_ILLUSION = 4, //�û�
	MODULE_MIX_STRENGTH = 1, //ǿ��
	MODULE_MIX_POLISHED = 2, //����
	MODULE_MIX_GEM = 3, //��ʯ
	MODULE_MIX_WASH = 4, //ϴ��
	MODULE_WING_UPGRADE = 1, //������
	MODULE_WING_STRENGTH = 2, //���ǿ��
	MODULE_TCM_ALL = 1, //��ɫ����
	MODULE_SOCIAL_FRIEND = 1, //����
	MODULE_SOCIAL_ENEMY = 2, //����
	MODULE_FACTION_RECRUIT = 1, //������ļ
	MODULE_FACTION_CREATE = 2, //��������
	MODULE_FACTION_MEMBER = 3, //�����Ա
	MODULE_FACTION_FUNCTION = 4, //���幦��
	MODULE_RANK_LOCAL = 1, //��������
	MODULE_RANK_KUAFU = 2, //�������
	MODULE_FACTIONMAIN_ALL = 1, //��������
	MODULE_FACTIONSKILL_ALL = 1, //���ܴ���
	MODULE_FACTIONACTIVE_TRIAL = 1, //����Զ��
	MODULE_FACTIONACTIVE_BOSS = 2, //����boss
	MODULE_FACTIONBOX_DEVOTE = 1, //���屦��
	MODULE_FACTIONBOX_ITEM = 2, //����ֿ�
	MODULE_MALL_GOLD = 1, //Ԫ���̳�
	MODULE_MALL_SCORE = 2, //�����̵�
	MODULE_MALL_RECHARGE = 3, //��ֵ
	MODULE_VIP_ALL = 1, //VIP��Ȩ
	MODULE_INSTANCE_PLOT = 1, //���鸱��
	MODULE_INSTANCE_RES = 2, //��Դ����
	MODULE_INSTANCE_TRIAL = 3, //������
	MODULE_INSTANCE_TEAM = 4, //���˸���
	MODULE_WORLD_RISK_MAIN = 1, //����ð��
	MODULE_ARENA_DOUJIANTAI = 1, //����̨(1V1)
	MODULE_ARENA_XIANMO = 2, //��ħ��(3V3)
	MODULE_ARENA_XIANFU = 3, //�ɸ��ᱦ
	MODULE_ARENA_RANK = 4, //��λ��
	MODULE_BOSS_WORLD_BOSS = 2, //����BOSS
	MODULE_BOSS_RISK_BOSS = 2, //BOSS��ս
	MODULE_WELFARE_MONTH = 1, //��ǩ��
	MODULE_WELFARE_LEVEL = 2, //��������
	MODULE_WELFARE_SEVEN = 3, //���մ���
	MODULE_WELFARE_RECHARGE = 4, //��ֵ����
	MODULE_WELFARE_CONSUME = 5, //�����н�
	MODULE_OPENSERVICE_SEVEN = 1, //����Ŀ��
	MODULE_OPENSERVICE_DRAW = 2, //����Ѱ��
	MODULE_OPENSERVICE_EVERYDAY = 3, //ÿ�����
	MODULE_OPENSERVICE_NEW = 4, //�������
	MODULE_FIRST_RECHARGE_ALL = 1, //�׳�
};

enum MERIDIAN_EXP_SOURCE {
	MERIDIAN_EXP_SOURCE_GROUP_INSTANCE = 1, //	�������
	MERIDIAN_EXP_SOURCE_TALISMAN_ZHULING = 2, //	����ע��
	MERIDIAN_EXP_SOURCE_WINGS_STRENGTH = 3, //	���ǿ��
};

// ��Ծ������
enum VITALITY_TYPE
{
	VITALITY_TYPE_SMELT_EQUIP = 1,		//����
	VITALITY_TYPE_RES_INSTANCE = 2,		//��Դ����
	VITALITY_TYPE_TRIAL_INSTANCE = 3,	//������
	VITALITY_TYPE_GROUP_INSTANCE = 4,	//���˸���
	VITALITY_TYPE_MASS_BOSS = 5,		//BOSS��ս
	VITALITY_TYPE_WORLD_BOSS = 6,		//����BOSS
	VITALITY_TYPE_FACTION_BOSS = 7,		//����BOSS
	VITALITY_TYPE_FACTION_TOWER = 8,	//����Զ��
	VITALITY_TYPE_FACTION_DONATE = 9,	//���幱��
	VITALITY_TYPE_DOUJIANTAI = 10,		//����̨
	VITALITY_TYPE_SINGLE_PVP = 11,		//��λ��
};

#endif