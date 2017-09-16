#ifndef _OPRATE_RESULT_H
#define _OPRATE_RESULT_H

//��������
enum ECharOprateType
{
	OPRATE_TYPE_LOGIN					= 1,		//��¼
	OPRATE_TYPE_KICKING					= 2,		//����
	OPRATE_TYPE_JUMP					= 3,		//��
	OPRATE_TYPE_ATTK_LOSE				= 4,		//����ʧ��
	OPRATE_TYPE_SPELL_LOSE				= 5,		//�����ͷ�ʧ��
	OPRATE_TYPE_INTERACTION				= 6,		//����,��ʹ��GAMEOBJ ��NPC�Ի������������
	OPRATE_TYPE_USE_GAMEOBJECT			= 7,		//ʹ����Ϸ����
	OPRATE_TYPE_BAG						= 8,		//����
	OPRATE_TYPE_TRADE					= 9,		//����
	OPRATE_TYPE_CHAT					= 10,		//����
	OPERTE_TYPE_RECEIVE_GIFT_PACKS		= 11,		//��ȡ�������
	OPERTE_TYPE_QUEST					= 12,		//����
	OPERTE_TYPE_NPCBUY					= 13,		//������Ʒ
	OPERTE_TYPE_FUBEN					= 14,		//����
	OPERTE_TYPE_KUAFU					= 15,		//���
	OPERTE_TYPE_RANK_LIST				= 16,		//���а�
	OPERTE_TYPE_CLOSE					= 17,		//���ӹر�
	OPERTE_TYPE_HOSTING					= 18,		//�й�
	OPERTE_TYPE_STRENGTH				= 19,		//ǿ��
	OPERTE_TYPE_CHANGE_BATTLE_MODE_LOSE = 20,		//�л�ս��ģʽʧ��
	OPERTE_TYPE_SOCIAL					= 21,		//�罻
	OPERTE_TYPE_FACTION					= 22,		//����
	OPERTE_TYPE_FIELD_BOSS				= 23,		//Ұ��BOSS
	OPERTE_TYPE_WORLD_BOSS				= 24,		//����BOSS
	OPRATE_TYPE_MOUNT_QICHENG			= 25,		//�������
	OPRATE_TYPE_TELEPORT				= 26,		//����
	OPRATE_TYPE_UPGRADE					= 27,		//��Ϸ�е���������
	OPRATE_TYPE_ACTIVITY				= 28,		//�
	OPRATE_TYPE_ACHIEVE					= 29,		//�ɾ�
	OPRATE_TYPE_ATHLETICS				= 30,		//����
	OPRATE_TYPE_XIANFU					= 31,		//�ɸ��ᱦ
	OPRATE_TYPE_REWARD					= 32,		//�����Ʒ
	OPRATE_TYPE_DOUJIAN					= 33,		//����̨
	OPRATE_TYPE_GEM						= 34,		//��ʯ
	OPRATE_TYPE_MONEYTREE				= 35,		//ҡǮ��
};

//��¼��ز�������
enum CHAR_OPRATE_RESULT
{
	OPRATE_RESULT_SUCCESS				= 1,	//�ɹ�
	OPRATE_RESULT_NAME_REPEAT			= 2,	//�����ظ�
	OPRATE_RESULT_NAME_ILLEGAL			= 3,	//���ƷǷ�
	OPRATE_RESULT_CHAR_CAP 				= 4,	//��ɫ�����ﵽ����
	OPRATE_RESULT_SCENED_CLOSE 			= 5,	//������δ����
	OPRATE_RESULT_SCENED_ERROR			= 6,	//���������ã���ʵ���Ǳ���һ����������һ���µ�
	OPRATE_RESULT_LOGINED_IN			= 7,	//��ɫ�ѵ�¼
	OPRATE_RESULT_OTHER_LOGINED			= 8,	//��ɫ�����ط���¼
	OPRATE_RESULT_GAME_VERSION_ERROR	= 9,	//��Ϸ�汾����
	OPRATE_RESULT_MAP_VERSION_ERROR		= 10,	//��ͼ�زİ汾����
	OPRATE_RESULT_DATA_VERSION_ERROR	= 11,	//data�زİ汾����
	OPRATE_RESULT_VERSION_FORMAT_ERROR	= 12,	//�ͻ��˷����İ汾��Ϣ��ʽ����
	OPRATE_RESULT_APPD_ERROR			= 13,	//Ӧ�÷��쳣����
	OPRATE_RESULT_LOCK_ACCOUNT			= 14,	//�ʺű���
	OPRATE_RESULT_LOCK_IP				= 15,	//IP����
	OPRATE_RESULT_APPD_CLOSE 			= 16,	//Ӧ�÷�δ����
	OPRATE_RESULT_NAME_TOO_LONG			= 17,	//����̫��
	OPRATE_RESULT_NAME_HAS_PINGBI		= 18,	//�����δ�
	OPRATE_RESULT_LOGOUT_UNFINISHED		= 19,	//�ý�ɫ��һ�εĵǳ�δ��ɣ���ȴ�
	OPRATE_RESULT_PID_OR_SID_ERROR		= 20,	//������id����ƽ̨id����
	OPRATE_RESULT_DB_RESULT_ERROR		= 21,	//���ݿ��ѯ��������
	OPRATE_RESULT_MERGE_SERVER			= 22,	//�Ϸ���
	OPRATE_RESULT_PLAYER_ZIBAO			= 23,	//�Ա�
	OPRATE_RESULT_GENDER_ILLEGAL		= 24,	//��ɫ�����쳣
};

//ϵͳ���˵�ԭ��
enum KICKING_TYPE
{
	KICKING_TYPE_GM_LOCK_IP				= 0,	//��IP
	KICKING_TYPE_GM_LOCK_ACCOUNT		= 1,	//���
	KICKING_TYPE_GM_KICKING				= 2,	//��GM���ж�ȡ������
	KICKING_TYPE_KUANGCHANG_RELIVE		= 3,	//���߿󳡷Ƿ�����
	KICKING_TYPE_FUCK_PINGBI			= 4,	//���������δ�
	KICKING_TYPE_QUEST_GET_ITEM			= 5,	//ˢ��Ʒ
	KICKING_TYPE_NOT_MONEY				= 6,	//Ǯ��������������
	KICKING_TYPE_MAX
};

//��Ծ��������
enum JUMP_OPRATE_RESULT
{
	JUMP_RESULT_NOMAL					= 1,		//�ޣ�Ĭ�Ͻ��
	JUMP_RESULT_DEAD					= 2,		//�����㻹����������թʬ
	JUMP_RESULT_ENERGY					= 3,		//��������
	JUMP_RESULT_MAP_CANT_JUMP			= 4,		//��ͼ�޷���Ծ
	JUMP_RESULT_CANT_JUMP				= 5,		//��ұ����Ʋ�����Ծ
	JUMP_RESULT_MAX_DISTANCE			= 6,		//����������
	JUMP_RESULT_WRONG_COORD				= 7,		//��Ч���꣬�ϰ���֮��
	JUMP_RESULT_SPELL_CD				= 8,		//��Ծ����cd��
	JUMP_RESULT_NOT_ACTIVE_SPELL		= 9,		//2����û�м���
};

//������������
enum Attack_Lost_Reson
{
	ATTACK_LOST_CANTATTACK				= 1,		//�����Ʋ��ܹ���
	ATTACK_LOST_TARGET_DEAD				= 2,		//Ŀ���Ѿ�����
	ATTACK_LOST_NEED_TARGET				= 3,		//������Ҫһ��Ŀ��
	ATTACK_LOST_OUT_OF_RANGE			= 4,		//����������Χ
	ATTACK_LOST_WRONG_TARGET			= 5,		//�����Ŀ��
	ATTACK_LOST_MOVING					= 6,		//�����ƶ�״̬�²��ܹ���
};

//�����ͷŲ�������
enum Spell_Lost_Reson
{
	LOST_RESON_SPELL_DOENT_EXIST		= 1,		//���ܲ�����
	LOST_RESON_NOT_HAVE_SPELL			= 2,		//��û���������
	LOST_RESON_NOT_ENOUGH_ANGER			= 3,		//ŭ��ֵ����
	LOST_RESON_SPELL_COOLDOWN			= 4,		//��ȴ
	LOST_RESON_ALREADY_CAST				= 5,		//�Ѿ���ʩ��
	LOST_RESON_TARGET_DEAD				= 6,		//Ŀ���Ѿ�����
	LOST_RESON_NEED_TARGET				= 7,		//�˼�����Ҫһ��Ŀ��
	LOST_RESON_JUMP_DENY				= 8,		//��Ծ״̬����ʩ��
	LOST_RESON_SCENE_DENY				= 9,		//������ֹʩ��
	LOST_RESON_CAN_NOT_CAST				= 10,		//�޷�ʩ��
	LOST_RESON_HAS_CONFLICT_SPELL		= 11,		//�м��ܳ�ͻ
	LOST_RESON_NOTHAS_CHUZHAN			= 12,		//��ǰû�г�ս����
	LOST_RESON_WRONG_FACTION			= 13,		//ͬһ��Ӫ���ܹ��������������ã�
	LOST_RESON_ACTIVE_SPELL_SUCCESS		= 14,		//���ܼ���ɹ�
	LOST_RESON_IN_SAFE_ZONE				= 15,		//��ȫ�����ܹ������������ã�
	LOST_RESON_YXT_WRONG_FACTION		= 16,		//ͬһ��Ӫ���ܹ�����Ӣ�����ã�
	LOST_RESON_PVP_STATE				= 17,		//PVP״̬�����ͷ�
};

//������������
enum INTERACTION_RESULT
{
	INTERACTION_TOO_FAR					= 1,	//NPC̫Զ
	INTERACTION_BOOK_DAILYNUM_FULL		= 2,	//�����ճ������������
	INTERACTION_NO_ENOUGH_ENDURANCE		= 3,	//����ֵ����
	INTERACTION_JHM_ERROR				= 4,	//���������
	INTERACTION_WORSHIP					= 5,	//����Ĥ��
	INTERACTION_JHM_HAVE				= 6,	//�����뽱������ȡ
	INTERACTION_JHM_IS_USED				= 7,	//��������ʹ��
	INTERACTION_JHM_NOT_USE_RANGE		= 8,	//����ʹ�÷�Χ��
};

//ʹ����Ϸ�����������
enum USE_GAMEOBJECT_OPEATE_RESULT
{
	USE_GAMEOBJECT_SUCCEED				= 1,		//ʹ����Ϸ����ɹ�
	USE_GAMEOBJECT_FAIL					= 2,		//ʹ����Ϸ����ʧ��
	USE_GAMEOBJECT_QUEST				= 3,		//�ɼ��ɹ�
	USE_GAMEOBJECT_TOO_FAST				= 4,		//�ɼ��ٶ�̫��
};

//������������
enum BAG_RESULT
{
	BAG_RESULT_NULL						= 1,	//·����
	BAG_RESULT_ITEM_NOT_EXIST			= 2,	//��Ʒ������
	BAG_RESULT_CHANGE_ERROR				= 3,	//����λ�ô���
	BAG_RESULT_DESTROY_BIND				= 4,	//ɾ���󶨵�
	BAG_RESULT_ITEM_NOT_SELF			= 5,	//�����Լ�����Ʒ
	BAG_RESULT_REPAIR_FULL				= 6,	//�����;���������Ʒ
	BAG_RESULT_BAG_NOT_EXIST			= 7,	//����������
	BAG_RESULT_POS_NOT_EXIST			= 8,	//����λ�ò�����
	BAG_RESULT_DESTROY_TOOMUCH			= 9,	//��������ɾ
	BAG_RESULT_BAN_FOR_TRADE			= 10,	//�����в��������
	BAG_RESULT_SPLIT_FAILURE			= 11,	//��Ʒ���ʧ��
	BAG_RESULT_LACK_USER				= 12,	//��������ɾ
	BAG_RESULT_BAG_FULL					= 13,	//�����Ų���
	BAG_RESULT_MAX_COUNT				= 14,	//�������ӵ����
	BAG_RESULT_SELL_BIND				= 15,	//����Ʒ���������
	BAG_RESULT_REPAIR_OK				= 16,	//ͭǮ���俪���ɹ�
	BAG_RESULT_REPAIR_MONEY_LACK		= 17,	//Ǯ�����޷�����
	BAG_RESULT_EXTENSION_BAG			= 18,	//������֧����չ
	BAG_RESULT_EXTENSION_MAX_SIZE		= 19,	//������С�Ѿ����
	BAG_RESULT_EXTENSION_MATERIAL_LACK	= 20,	//������չ���ϲ���
	BAG_RESULT_EXTENSION_TRADE			= 21,	//�����в����������չ
	BAG_RESULT_USE_ITEM_COUNT_MAX		= 22,	//ʹ����Ʒ�����ﵽ����
	BAG_RESULT_NOT_ITEM					= 23,	//û������Ʒ
	BAG_RESULT_ITEM_USEING				= 24,	//��Ʒʹ����
	BAG_RESULT_GET_ITEMS				= 25,	//�����Ʒ��Ԫ������
	BAG_RESULT_USE_ITEMS				= 26,	//ʹ����Ʒ��װ�����䣩
	BAG_RESULT_GET_ITEMS_ORANGE			= 27,	//������ɫװ��
	BAG_RESULT_USE_ITEMS_GENERALS		= 28,	//ʹ����Ʒ������ʹ�ã�
	BAG_RESULT_GET_ITEMS_CABX			= 29,	//��� ������
	BAG_RESULT_GET_ITEMS_CABX_BUFF		= 30,	//��� �������buff ��ʾ
	BAG_RESULT_ALREADY_KAIGUANG 		= 31,	//�豸�Ѿ�����
	BAG_RESULT_EXCHANGE_SUCCESS			= 32,	//����װ���ɹ�
	BAG_RESULT_OPEN_ITEMS_SUCCESS		= 33,	//����Ʒ�ɹ������ڸ��ʻ�ã�
	BAG_RESULT_OPEN_ITEMS_FAIL			= 34,	//����Ʒʧ�ܣ����ڸ��ʻ�ã�
	BAG_RESULT_GET_ITEMS_GENERALS_EQUIP	= 35,	//ʹ����Ʒ����佫װ��
	BAG_RESULT_GET_SHOWHAND_JIEZHI		= 36,	//��������ָ
	BAG_RESULT_USE_WUJIANG_EXP_CARD		= 37,	//ʹ���佫���鿨
	BAG_RESULT_USE_ITEMS_SUCCESS		= 38,	//��Ʒʹ�óɹ�
	BAG_RESULT_BAG_FULL_SEND_MAIL		= 39,	//�������� ����������ʾ
	BAG_RESULT_BAG_FULL_AUTO_SELL		= 40,	//���������Զ�����
	BAG_RESULT_BAG_XIULIAN_USE			= 41,	//ʹ����������þ���
	BAG_RESULT_BAG_SORT_CD				= 42,	//��������ȴ��

};

//���ײ�������
enum TRADE_RESULT_TYPE
{
	TRADE_RESULT_TYPE_NOT_TARGET		= 1,			//û�н��׶���
	TRADE_RESULT_TYPE_TRADEING			= 2,			//�Ѿ��������޷���������������
	TRADE_RESULT_TYPE_NOT_TRADE			= 3,			//�ǽ��׽�������Ч����
	TRADE_RESULT_TYPE_BAG_SIZE			= 4,			//�����ռ䲻�㽻��ʧ��
	TRADE_RESULT_TYPE_UNRECOGNISED		= 5,			//δȷ�Ͻ�����Ʒ
	TRADE_RESULT_TYPE_TARGET_CANCEL		= 6,			//�Է�����ȡ������
	TRADE_RESULT_TYPE_LACK_MONEY		= 7,			//��Ǯ����
	TRADE_RESULT_TYPE_IS_BIND			= 8,			//����Ʒ��������
};

//�����������
enum CHAT_OPRATE_RESULT
{
	CHAT_RESULT_NOT_PLAYER				= 1,	//�Ҳ������
	CHAT_RESULT_IS_GAG					= 2,	//������
	CHAT_LEVEL_WHISPER_LEVEL_NO			= 3,	//˽�ĵȼ�����
	CHAT_LEVEL_WORLD_LEVEL_NO			= 4,	//��������ȼ�����
	CHAT_RESULT_CHECK_LIMIT				= 5,	//��˵��̫���ˣ��Ͻ������ȵ�������ɡ�
	CHAT_RESULT_NO_FACTION				= 6,	//�����ް���
	CHAT_RESULT_NO_GROUP				= 7,	//�����޶���
};

//��ȡ���������������
enum RECEIVE_GIFT_PACKS_OPEATE_RESULT
{
	RECEIVE_GIFT_PACKS_NOT_FIND			= 1,		//�Ҳ��������������
	RECEIVE_GIFT_PACKS_CHAR_ERROR		= 2,		//������������
	RECEIVE_GIFT_PACKS_CHAR_CREATE		= 3,		//���ָ���ķ�����ʼʱ�������ɫ����ʱ��֮ǰ
	RECEIVE_GIFT_PACKS_RECEIVED			= 4,		//��������Ѿ���ȡ����
	RECEIVE_GIFT_PACKS_ONLINE_AWARD		= 5,		//�����������
	RECEIVE_GIFT_PACKS_ONLINE_XIANSHI	= 6,		//���������ʾ��
};

//�������ö��
enum QuestFailedReasons
{
	INVALIDREASON_QUEST_FAILED_LOW_LEVEL        = 1,        // �ȼ�̫�� You are not high enough level for that quest.
	INVALIDREASON_QUEST_FAILED_WRONG_RACE       = 2,        // ������������Ľ�ɫ�������Ч�� That quest is not available to your race.
	INVALIDREASON_QUEST_ALREADY_DONE            = 3,        // �����Ѿ���� You have completed that quest.
	INVALIDREASON_QUEST_ONLY_ONE_TIMED          = 4,       // ����ֻ����һ�� You can only be on one timed quest at a time.
	INVALIDREASON_QUEST_ALREADY_ON              = 5,       // �Ѿ��������� You are already on that quest.
	INVALIDREASON_QUEST_FAILED_EXPANSION        = 6,       // ��Ʒ̫�� This quest requires an expansion enabled account.
	INVALIDREASON_QUEST_ALREADY_ON2             = 7,       // �Ѿ��������� ? You are already on that quest.
	INVALIDREASON_QUEST_FAILED_MISSING_ITEMS    = 8,       // û�����������Ҫ����Ʒ You don't have the required items with you. Check storage.
	INVALIDREASON_QUEST_FAILED_NOT_ENOUGH_MONEY = 9,       // û���㹻�Ľ�Ǯ������� You don't have enough money for that quest.
	INVALIDREASON_DAILY_QUESTS_REMAINING        = 10,       // ���Ѿ������ÿ���25������ You have already completed 25 daily quests today.
	INVALIDREASON_QUEST_FAILED_CAIS             = 11,       // ��ƣ��ʱ���޷�������� You cannot complete quests once you have reached tired time.
	INVALIDREASON_DAILY_QUEST_COMPLETED_TODAY   = 12,       // �Ѿ���ɵ�������� You have completed that daily quest today.
	INVALIDREASON_QUEST_FINISH_ALL_RIHUAN		= 13,		//��������ջ�������

	QUEST_TYPE_PROCESS							= 14,		//�������, ����:1/1
};

//������Ʒ
enum ENpcBuy_Result
{
	NPC_BUY_ITEM_NO_EXIST						= 0,		//��Ʒ������
	NPC_BUY_ITEM_UNDER							= 1,		//�¼ܵ���Ʒ
	NPC_BUY_ITEM_NO_OPEN						= 2,		//��Ʒ��δ������ʱ��
	NPC_BUY_ITEM_OUT_TIME						= 3,		//��Ʒ�ѹ���
	NPC_BUY_BAG_OUT_SIZE						= 4,		//�����Ų�����
	NPC_BUY_MONEY_NO_ENOUGH						= 5,		//Ǯ������
	NPC_BUY_MONEY_TRANSFINITE					= 6,		//���������
	NPC_BUY_SELL_OUT							= 7,		//������Ʒ�޹�����
};

//����
enum FUBEN_OPRATE_RESULT
{
	FUBEN_OPRATE_NO_GROUP_STATE				= 0,		//��Ҳ������״̬
	FUBEN_OPRATE_NOT_TWO_PEOPLE				= 1,		//���鲻��2����
	FUBEN_OPRATE_NO_ENERGY					= 2,		//��������
	FUBEN_OPRATE_NO_MONEY					= 3,		//Ԫ������
	FUBEN_OPRATE_TEAM_NO_LEVEL				= 4,		//���ѵȼ�����
	FUBEN_OPRATE_TEAM_NO_ENERGY				= 5,		//������������
	FUBEN_OPRATE_NO_GROUP					= 6,		//�����Ѿ���ɢ
	FUBEN_OPRATE_SEND_TEAM_FRIEND			= 7,		//������ѽ�����Ӹ���
	FUBEN_OPRATE_TEAM_REFUSE_ENETR			= 8,		//���Ѿܾ�������Ӹ���
	FUBEN_OPRATE_TEAM_ON_FUBEN_MAP			= 9,		//�����ڸ�����ͼ��
	FUBEN_OPRATE_TEAM_HAVE_FLAGS			= 10,		//�����Ѿ�����������
	FUBEN_OPRATE_REFRESH_BOSS				= 11,		//����ˢ��boss
	FUBEN_OPRATE_KILLED_BOSS				= 12,		//��ҳɹ���ɱ��boss
	FUBEN_OPRATE_MORE_TIMES					= 13,		//ȫ����ɱ����������
	FUBEN_OPRATE_NO_CREATURES				= 14,		//ȫ����ɱ��ǰû�й���
};

//���
enum KUAFU_OPERATE_RESULT
{
	KUAFU_OPERATE_CONN_DISCONN					= 0,		//��Ϸ��������������ӶϿ���
	KUAFU_OPERATE_HASNOT_REGISTER				= 1,		//������û���������ע��ɹ�
};

//���а�
enum ERankListOperateResult
{
	RANK_LIST_OPERATE_SUCCEED			= 0,	//�ɹ�
	RANK_LIST_OPERATE_TYPE_ERROR		= 1,	//��ѯ���ʹ���
	RANK_LIST_OPERATE_OUT_OF_RANGE		= 2,	//��ѯ��Χ��������
	RANK_LIST_OPERATE_MAX_LIKE			= 4,	//�����ѳ���������
	RANK_LIST_OPERATE_HAS_LIKE			= 5,	//�ѵ������

};

enum ActivityOperateResult
{
	ACTIVITY_OPERATE_NOTVIP			= 0, //�㲻��vip�޷���ȡvip����
	ACTIVITY_OPERATE_NOENOUGH		= 1, //��Ծ�Ȳ����޷���ȡ
	ACTIVITY_OPERATE_HASGET			= 2, //�Ѿ���ȡ���ý���
};

enum AchieveOperateResult
{
	ACHIEVE_OPERATE_NO_FIND			= 0, //�Ҳ����ɾ�
	ACHIEVE_OPERATE_NO_GET			= 1, //��δ��ɳɾ�
	ACHIEVE_OPERATE_HASGET			= 2, //�Ѿ���ȡ���ɾͽ���
	ACHIEVE_OPERATE_NO_ALL			= 3, //�ܳɾͲ����޷���ȡ
	ACHIEVE_OPERATE_TITLE_SUC		= 4,//���óƺųɹ�
	ACHIEVE_OPERATE_TITLE_FAL		= 5,//�ƺŲ������޷�����
	ACHIEVE_OPERATE_NO_MONEY		= 6,//Ǯ�����˲����һ�
};


enum AthleticsOperateResult
{
	ATHLETICS_OPERATE_NO_LEV			= 1, //�ȼ�����{1}�����ܲμ�3v3
	ATHLETICS_OPERATE_NO_FORCE			= 2, //ս������{1}�����ܲμ�3v3
	ATHLETICS_OPERATE_NO_OPEN			= 3, //���ڻʱ�䣬���ܲμ�
	ATHLETICS_OPERATE_NO_TIME_BUY		= 4, //3v3���������꣬���Թ������
	ATHLETICS_OPERATE_NO_TIME			= 5, //3v3���������꣬����������
	ATHLETICS_OPERATE_IN_MATCH			= 6, //����ƥ����
	ATHLETICS_OPERATE_MAX_BUY			= 7, //������������
	ATHLETICS_OPERATE_NO_MONEY			= 8, //������������
	ATHLETICS_OPERATE_HAS_DAY_REWARD	= 9, //�Ѿ���ȡ�ý���
	ATHLETICS_OPERATE_NO_DAY_REWARD		= 10, //��δ�������{1}

	ATHLETICS_OPERATE_BUFF_OCCUR		= 11,	//buff����
};

enum DoujianOperateResult
{
	DOUJIAN_OPERATE_NO_LEV			= 0, //�ȼ���������Ҫ{0}���ܲ��붷��̨
	DOUJIAN_OPERATE_ZHUCHENG		= 1, //ֻ���������вμӻ
	DOUJIAN_OPERATE_NO_TIME			= 2, //��ս��������
	DOUJIAN_OPERATE_IN_CD			= 3, //��սCD��
	DOUJIAN_OPERATE_MAX_TIME		= 4, //������������
	DOUJIAN_OPERATE_NO_MONEY		= 5, //Ԫ�����㹺�򶷽�����
	DOUJIAN_OPERATE_NO_MONEY_CD		= 6, //Ԫ�����㲻������CD

	DOUJIAN_OPERATE_SELF_BATTLE		= 7,	//�Լ����ڱ�������ս
	DOUJIAN_OPERATE_OTHER_BATTLE	= 8,	//��ս�������ڱ�������ս
	DOUJIAN_OPERATE_COUNTDOWN		= 9,	//ˢ������ȴ��
};

//��Ϸ�ر���Ϣ
enum PLAYER_CLOSE_OPERTE_RESULT
{
	PLAYER_CLOSE_OPERTE_APPD_ONE1						= 1000,	//���뵥����Ʒʱ������id �������ֵ
	PLAYER_CLOSE_OPERTE_APPD_ONE2						= 1001,	//������������Ķ����ʱ�򣬷���֮ǰ�Ѿ���������
	PLAYER_CLOSE_OPERTE_APPD_ONE3						= 1002,	//�йܵ���
	PLAYER_CLOSE_OPERTE_APPD_ONE4						= 1003,	//GM���� ����
	PLAYER_CLOSE_OPERTE_APPD_ONE5						= 1004,	//GM���� �ص�����
	PLAYER_CLOSE_OPERTE_APPD_ONE6						= 1005,	// ���������
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE4						= 2001,	//�ʺ���Ϣ������
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE5						= 2002,	//Char_Create put  fail!
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE6						= 2003,	//��¼ʱ�����ҵĽ�ɫ
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE7						= 6,	//����
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE8						= 2004,	//������������ m_player ������
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE9						= 2005,	//��ʼ�����ݿ�����ʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE10					= 2006,	//������û�����������Ҫ�޸�����������
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE11					= 2007,	//����Ԫ������ ȡ����ʱʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE12					= 2008,	//����
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE13					= 2009,	//������Ӳ�����,����ݽ⿪��session������д�����Ӧ��sessionʵ��(on_create_conn_get_session create_sesstion duplicate)
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE14					= 2010,	//�ͻ�������ʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE15					= 2011,	//�������pk���ص���Ϸ��,��¼ʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE16					= 2012,	//���������Ƿ���Ե�½ -��Ҳ�����
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE17					= 2013,	//���������Ƿ���Ե�½ -��ʱ
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE18					= 2014,	//��½���� context->GetGuid().empty(��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE19					= 2015,	//�Ϸ���� ��������
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE20					= 2016,	//֪ͨ��������Ҽ����ͼ m_scened_conn������
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE21					= 2017,	//��Ҽ����ͼʵ��ʱ�����binlg������ 
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE22					= 2018,	//��Ҽ����ͼ ����ʵ��ʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE23					= 2019,	//����ѵ�¼�� !m_account.empty()
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE24					= 2020,	//�ʺ����Ƴ���
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE25					= 2021,	//��֤�Ƿ���Ե�¼������֤ʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE26					= 2022,	//�˻������ݲ�����
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE27					= 2023,	//��������߹رյ�������
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE28					= 2024,	//���ε�¼�����ǻ�û����ҽ�ɫ
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE39					= 2025,	//����׼����ϣ���ҿ�ʼ��¼ ��Ҳ�����
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE40					= 2026,	//��ȡsessionKey����,�Ѿ���¼��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE41					= 2027,	//��ȡsessionKey�����ʻ����ƣ������ж�һ���Ƿ񳬳�(������ʧ��)
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE42					= 2028,	//��ȡsessionKey����Get_Session: other_data size is wrong
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE43					= 2029,	//��ȡsessionKey������֤session_key�Ƿ���Ե�¼�����������Ϊ���ɵ�¼ʱ��Ͽ���
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE44					= 2030,	//��ȡsessionKey����LogindContext::Get_Session:%s load account fail(��ȡ�ʺű������쳣)
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE45					= 2031,	//��ȡsessionKey����LogindContext::Get_Session:%s Get_Chars_List fail����ȡ��ɫ�б������쳣��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE46					= 2032,	//�����ȡ����ʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE47					= 2033,	//�������ã���¼ʱ���������ͷ��Լ�����
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE48					= 2034,	//�Ϸ���⣬�ӷ����״̬ ��Ϊ STATUS_LOGGEDIN
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE49					= 2035,	//���
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE50					= 2036,	//����
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE51					= 2037,	//��Ҳ�����ʱ�ر����� LuaPlayerLogin %s, but not found
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE52					= 2038,	//��ɫ�������ط���½
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE53					= 2039,	//��½���޷��������
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE54					= 2040,	//��½ʱ player login call puts fail %s, fd %u
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE55					= 2041,	//on_create_conn_get_session create_mobile_context duplicate
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE56					= 2042,	//��½ʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE57					= 2045,	//Gm���� @�Ա�
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE58					= 2043,	//PK����½�����쳣
	PLAYER_CLOSE_OPERTE_LOGDIN_ONE59					= 2044,	//�����ݿ��ȡ�������ʧ��
	PLAYER_CLOSE_OPERTE_LOGDIN_2046						= 2046,	//һ����ɫ��Ӧ�����˺�	
	PLAYER_CLOSE_OPERTE_LOGDIN_2047						= 2047,	//�����ֵ�ʱ���Ҳ���account��ˢ�¾Ϳ��Թ���
	PLAYER_CLOSE_OPERTE_LOGDIN_2048						= 2048,	//session��account������player��account,����˵,������.
	PLAYER_CLOSE_OPERTE_SCREND_ONE29					= 3001,	//ֹͣ�ƶ�����ͼģ��Ϊnull
	PLAYER_CLOSE_OPERTE_SCREND_ONE30					= 3002,	//�����ƶ�����ͼģ��Ϊnull
	PLAYER_CLOSE_OPERTE_SCREND_ONE31					= 3003,	//�����ƶ���ʱ��  ״̬��Ϊ STATUS_LOGGEDIN  ʱ�� ��assert error: Handle_Unit_Move  ASSERT(status_ == STATUS_LOGGEDIN)��
	PLAYER_CLOSE_OPERTE_SCREND_ONE32					= 3004,	//������ ״̬��Ϊ STATUS_LOGGEDIN ��ScenedContext::Teleport status_ != STATUS_LOGGEDIN��
	PLAYER_CLOSE_OPERTE_SCREND_ONE33					= 3005,	//������δ��ȷ�ļ����ͼ�����ʱ�䴫��Ҳ��ʧ�ܵ�
	PLAYER_CLOSE_OPERTE_SCREND_ONE34					= 3006,	//���������ж� assert error: Handle_QuestGiver_Status_Query  ASSERT(questGetter)
	PLAYER_CLOSE_OPERTE_SCREND_ONE35					= 3007,	//��ұ�ɱ��ʱ����ͼ���ݲ����� Player::OnKilled ASSERT(GetMap())
	PLAYER_CLOSE_OPERTE_SCREND_ONE36					= 3008,	//�����ͼ���ﲻ���ڵ�ʱ��  Player::OnJoinMap ASSERT(m_pets.empty())
	PLAYER_CLOSE_OPERTE_SCREND_ONE37					= 3009,	//��������߲����ڵ�ʱ�� Player::Create ASSERT(!m_questMgr)
	PLAYER_CLOSE_OPERTE_SCREND_ONE38					= 3010,	//���ͳ�ʱ1����
	PLAYER_CLOSE_OPERTE_POLICED_4001					= 4001,	//����־���ظ���¼
};

enum FACTION_OPERTE_RESULT
{
	OPERTE_TYPE_FACTION_IS_HAVE						= 0,//���Ѿ��ڰ�����
	OPERTE_TYPE_FACTION_NAME_ERR					= 1,//�������Ƴ���6���ַ�
	OPERTE_TYPE_FACTION_NAME_HAVE_FUCK				= 2,//�����������зǷ��ַ�
	OPERTE_TYPE_FACTION_NAME_REPEAT					= 3,//���������ظ�
	OPERTE_TYPE_FACTION_CREATE_MAX					= 4,//���������ﵽ����
	OPERTE_TYPE_FACTION_CREATE_COST					= 5,//Ԫ�������޷���������
	OPERTE_TYPE_FACTION_NOT_MANAGER					= 6,//���ǰ����򸱰����޷��༭
	OPERTE_TYPE_FACTION_NOTICE_ERR					= 7,//���ɹ��泬��144���ַ�
	OPERTE_TYPE_FACTION_NOTICE_ERR_PB				= 8,//���ɹ�������Ƿ��ַ�
	OPERTE_TYPE_FACTION_LEV_LOW						= 9,//�ȼ����������ܼ������
	OPERTE_TYPE_FACTION_MEMBER_MAX_COUNT			= 10,//�������������޷�����
	OPERTE_TYPE_FACTION_JOIN_SUCESS					= 11,//��ϲ��������
	OPERTE_TYPE_FACTION_FACTION_REFUSED_JOIN		= 12,//�㱻�ܾ��������
	OPERTE_TYPE_FACTION_KICKED						= 13,//�㱻�Ƴ�����
	OPERTE_TYPE_FACTION_KICK_SUCCESS				= 14,//�߳����ɳ�Ա
	OPERTE_TYPE_FACTION_MAX_ZHIWEI					= 15,//ְλ��������
	OPERTE_TYPE_FACTION_APPOINT_SUCCESS				= 16,//�����ɹ�
	OPERTE_TYPE_FACTION_PROMOTED					= 17,//�㱻����Ϊ
	OPERTE_TYPE_FACTION_APPOINT_NOSELF				= 18,//�Լ����������Լ� 
	OPERTE_TYPE_FACTION_DONATIONMAX					= 19,//���״�������������
	OPERTE_TYPE_FACTION_DONATION_GOLD				= 20,//���������Ҳ���
	OPERTE_TYPE_FACTION_DONATION_YB					= 21,//��������Ԫ������
	OPERTE_TYPE_FACTION_SHOP_NUMLOW					= 22,//��Ʒʣ�����������޷�����
	OPERTE_TYPE_FACTION_DEVOTE						= 23,//�ﹱ����
	OPEATE_TYPE_FACTION_MONEY_ERR					= 24,//�����ʽ���
	OPEATE_TYPE_FACTION_LEVEL_UP					= 25,//���������ɹ�
	OPEATE_TYPE_FACTION_NOT_JOIN					= 26,//û�п��Լ���İ���
	OPERTE_TYPE_FACTION_PLAYER_OFFLINE				= 40,//�Է�������,�޷������Ա

	OPERTE_TYPE_FACTION_BOSS_START					= 50,//�ٻ�boss

	OPERTE_TYPE_FACTION_GIFT_THANK					= 59,//��л���
	OPERTE_TYPE_FACTION_GIFT_THANK_ALL					= 60,//ȫ����л���
	OPERTE_TYPE_FACTION_GIFT_GET_EXREWARD					= 61,//��ȡ�ɹ�
	OPERTE_TYPE_FACTION_GIFT_GET_EXREWARD_ALL					= 62,//ȫ����ȡ�ɹ�
	OPERTE_TYPE_FACTION_GIFT_SEND					= 63,//���ͳɹ�
	OPERTE_TYPE_FACTION_GIFT_SEND_FAIL					= 64,//���ͳɹ�

	OPERTE_TYPE_FACTION_GIFT_NOTICE					= 65, //����㲥

	OPERTE_TYPE_FACTION_BOSSDEFENSE_TIME_ERROR		= 66, //�Ƿ�ʱ�� �޷���սboss
	OPERTE_TYPE_FACTION_NAME_NOT_CHINESE			= 67, //�������������ַ�
};

enum SOCIAL_OPERTE_RESULT
{
	OPERTE_TYPE_SOCIAL_HAS_SEND						= 1,//����������Ϣ�ѷ���
	OPERTE_TYPE_SOCIAL_NOT_FIND						= 2,//��ɫ�����ڻ��߽�ɫ������
	OPERTE_TYPE_SOCIAL_SELF_FULL					= 3,//�Լ������б�����
	OPERTE_TYPE_SOCIAL_TARGET_FULL					= 4,//�Է������б�����
	OPERTE_TYPE_SOCIAL_ALREADY_FRIEND				= 5,//�Է��Ѿ�����ĺ���
	OPERTE_TYPE_SOCIAL_ADD_MYSELF					= 6,//�����Լ�����Լ�Ϊ����
	OPERTE_TYPE_SOCIAL_HAS_SEND_ADD					= 7,//�Ѿ���������
	OPERTE_TYPE_SOCIAL_NO_MONEY						= 8,//Ԫ�����߽�Ҳ���
	OPERTE_TYPE_SOCIAL_NOT_ENEMY					= 9,//�Է����ǳ���
	OPERTE_TYPE_SOCIAL_ENEMY_OFFLINE				= 10,//�Է�����������
	OPERTE_TYPE_SOCIAL_ENEMY_NOT_IN_FIELD			= 11,//�Է�����Ұ��
	OPERTE_TYPE_SOCIAL_REVENGE_TIMES_NOT_ENOUGH		= 12,//�����ʹ�������
	OPERTE_TYPE_SOCIAL_RENAME_SUCCESS				= 13,//�����ɹ�
	OPERTE_TYPE_SOCIAL_OTHNER_FACTION				= 14,//�Է����ڰ���
	OPERTE_TYPE_SOCIAL_SAME_FACTION					= 15,//�Է�����ͬ����

};

//�й�
enum HOSTING_OPERTE_RESULT
{
	HOSTING_OPERTE_IS_SELF							= 0,	//�޷����Լ�����
	HOSTING_OPERTE_LEVEL_NOT						= 1,	//�ȼ�����
	HOSTING_OPERTE_IS_HOSTING						= 2,	//�й���
	HOSTING_OPERTE_IS_HOSTING_APPLY					= 3,	//�й�����
	HOSTING_OPERTE_FRIEND_NOT						= 4,	//���Ѳ�����
	HOSTING_OPERTE_HAS_NOT_24H						= 5,	//��û��24Сʱ
	HOSTING_OPERTE_FRIEND_OUTLINE					= 6,	//���Ѳ�����
	HOSTING_OPERTE_FRIEND_ERR						= 7,	//�йܺ��Ѵ���
	HOSTING_OPERTE_NOT_HOSTING						= 8,	//�����й���
	HOSTING_OPERTE_FRIEND_ONLINE					= 9,	//��������
	HOSTING_OPERTE_LOGIN_HOSTING					= 10,	//�йܵ�¼��
	HOSTING_OPERTE_FRIEND_APPLY						= 11,	//���뷢��
	HOSTING_OPERTE_LOGIN							= 12,	//��¼
	HOSTING_OPERTE_SUCCESS							= 13,	//�й�����ɹ�
	HOSTING_OPERTE_CANCEL							= 14,	//ȡ���й�
	HOSTING_OPERTE_REFUSED							= 15,	//�ܾ��й�
	HOSTING_OPERTE_NOT_DUE_TO						= 16,	//�й�δ����
	HOSTING_OPERTE_FRIEND_HOSTING_LOGIN				= 17,	//�Է��йܵ�¼�У��޷�����
	HOSTING_OPERTE_FRIEND_NOT_HAS_YOU				= 18,	//�Է������б�û����
};

//ǿ��
enum STRENGTH_OPERTE_RESULT {
	STRENGTH_OPERTE_FAIL							= 0		//ǿ��ʧ��
};

//�л�ս��ģʽ
enum BATTLE_MODE_OPERTE_RESULT
{
	BATTLE_MODE_OPERTE_PEACE_MODE_DENY				= 0,	//ս���в����л���ƽģʽ
	BATTLE_MODE_OPERTE_PEACE_MODE_IN_CD				= 1,	//��ƽģʽ��CD��
};


// Ұ��BOSS
enum FIELD_BOSS_OPERTE_RESULT
{
	FIELD_BOSS_OPERTE_WILL_START = 1,	//Ұ��BOSS������{1}���Ӻ���, ���Ұ��ź�ʱ��
	FIELD_BOSS_OPERTE_WILL_OCCUR = 2,	//Ұ��boss�������֣����λ��������׼��
	FIELD_BOSS_OPERTE_OCCUR		 = 3,	//Ұ��boss�Ѿ��ڸ�����ͼˢ�£����λ��������ǰ����ɱ �鿴����
	FIELD_BOSS_OPERTE_BOSS_BORN  = 4,	//{1}�ѳ�����{2}�����λ��������ǰ����ɱ ����ǰ��
	FIELD_BOSS_OPERTE_BOSS_KILL  = 5,	//{1}�ѱ��ɹ���ɱ����ϲ{2}���{3}1���ӵ����ȿ���Ȩ��
	FIELD_BOSS_OPERTE_PROTECT	 = 6,	//�������䱣��ʱ�������������λ��������
	FIELD_BOSS_OPERTE_PICKED	 = 7,	//��ϲ{1}���տ����������䣬���XXXX
	FIELD_BOSS_OPERTE_TOO_FAR	 = 8,	//̫Զ�ˣ��㲻���ܿ����������
};

// ����BOSS
// OPERTE_TYPE_WORLD_BOSS
enum WORLD_BOSS_OPERTE_RESULT
{
	WORLD_BOSS_OPERTE_NOT_ENROLL = 0,	//���λ��δ�������޷��μ�
	WORLD_BOSS_OPERTE_WILL_START = 1,	//����boss�������������λ��������׼��
	WORLD_BOSS_OPERTE_WILL_ROLL1 = 2,	//��ϲ{1}Ӯ�ñ���ƴ�㽱����BOSS��3���ָ�����
	WORLD_BOSS_OPERTE_WILL_ROLL2 = 3,	//��ϲ{1}Ӯ�ñ���ƴ�㽱�������ڿ������뿪ս��
	WORLD_BOSS_OPERTE_ENROLL	 = 4,	//����BOSS��ʼ����
};

// �������
// OPRATE_TYPE_MOUNT_QICHENG
enum MOUNT_QICHENG_OPERTE_RESULT
{
	MOUNT_QICHENG_FIGHT			= 0,	//ս��״̬�������
	MOUNT_QICHENG_JUMP			= 1,	//��Ծ״̬�������
};


// ����
//OPRATE_TYPE_TELEPORT
enum TELEPORT_OPERTE_RESULT
{
	TELEPORT_OPRATE_PVP_STATE	= 0,	//pvp״̬���ܴ���
};

// ��������
//OPRATE_TYPE_UPGRADE
enum UPGRADE_OPRATE_RESULT
{
	UPGRADE_OPRATE_SKILL_SUCCESS	= 0,	//���������ɹ�
	UPGRADE_OPRATE_MOUNT_EXP		= 1,	//���ﾭ��+{1}
	UPGRADE_OPRATE_MOUNT_STAR		= 2,	//�����Ǽ�+1
	UPGRADE_OPRATE_MOUNT			= 3,	//���׳ɹ�
	UPGRADE_OPRATE_ANGLE_SKILL		= 4,	//ŭ�����ܽ��׳ɹ�
	UPGRADE_OPRATE_BLESS_SUCCESS		= 5 ,   //��λ�����ɹ�
	UPGRADE_OPRATE_BLESS_EXP			= 6,	//��λ����+{1}
	UPGRADE_OPRATE_GEM_SUCCESS		= 7 ,   //��ʯ����ɹ�
	UPGRADE_OPRATE_GEM_EXP			= 8,	//��ʯ����+{1}
	UPGRADE_OPRATE_TALISMAN_ACTIVE	= 9 ,   //��������ɹ�
	UPGRADE_OPRATE_TALISMAN_LVUP	= 10,	//����ע��
	UPGRADE_OPRATE_WINGS_ACTIVE = 11,		//���𼤻�ɹ�
	UPGRADE_OPRATE_WINGS_BLESS = 12,		//����ף���ɹ�
	UPGRADE_OPRATE_WINGS_RANKUP = 13,		//�������׳ɹ�
	UPGRADE_OPRATE_WINGS_STRENGTH_SUCESS = 14,	//����ǿ���ɹ�
	UPGRADE_OPRATE_WINGS_STRENGTH_FAIL = 15,	//����ǿ��ʧ��
	UPGRADE_OPRATE_EQUIPDEVELOP_STRENGTH_SUCCESS = 16, //װ����λǿ���ɹ�
	UPGRADE_OPRATE_EQUIPDEVELOP_REFINE_STAR_SUCCESS = 17, //װ����λ���ǳɹ�
	UPGRADE_OPRATE_EQUIPDEVELOP_REFINE_STAR_FAIL = 18, //װ����λ����ʧ��
	UPGRADE_OPRATE_EQUIPDEVELOP_REFINE_RANK_SUCCESS = 19, //װ����λ���׳ɹ�
	UPGRADE_OPRATE_EQUIPDEVELOP_REFINE_RANK_FAIL = 20, //װ����λ����ʧ��
	UPGRADE_OPRATE_EQUIPDEVELOP_GEM_ACTIVE_SUCCESS = 21, //װ����ʯ����ɹ�
	UPGRADE_OPRATE_EQUIPDEVELOP_GEM_LVUP_SUCCESS = 22, //װ����ʯǿ���ɹ�
	UPGRADE_OPRATE_EQUIPDEVELOP_WASHATTRS_WASH	= 23, //װ��ϴ�����
	UPGRADE_OPRATE_EQUIPDEVELOP_WASHATTRS_SAVE	= 24, //װ��ϴ������
	UPGRADE_OPRATE_EQUIPDEVELOP_BONUS_STRENGTH	= 25, //װ��ǿ������
	UPGRADE_OPRATE_EQUIPDEVELOP_BONUS_REFINE	= 26, //װ����������
	UPGRADE_OPRATE_EQUIPDEVELOP_BONUS_GEM	= 27, //װ����Ƕ����

	UPGRADE_OPRATE_FACTIONSKILL_LVUP = 28, //���弼�������ɹ�

	UPGRADE_OPRATE_MOUNT_ILLUSION_ACTIVE = 29, //����Ƥ������ɹ�
	UPGRADE_OPRATE_CLOTH_ILLUSION_ACTIVE = 30, //�·���ۼ���ɹ�
	UPGRADE_OPRATE_WEAPON_ILLUSION_ACTIVE = 31, //������ۼ���ɹ�
	UPGRADE_OPRATE_TITLE_ACTIVE = 32, //�ƺż���ɹ�
	UPGRADE_OPRATE_MOUNT_ILLUSION_SET = 33, //����û��ɹ�
	UPGRADE_OPRATE_MOUNT_ILLUSION_UNSET = 34, //����ȡ���û�
	UPGRADE_OPRATE_FASHION_ILLUSION_SET = 35, //���װ���ɹ�
	UPGRADE_OPRATE_FASHION_ILLUSION_UNSET = 36, //���ȡ��װ��
	UPGRADE_OPRATE_MOUNT_LEVEL_UP = 37, //���������ɹ�
	UPGRADE_OPRATE_MERIDIAN_LEVEL_UP = 38, //���������ɹ�
	UPGRADE_OPRATE_MERIDIAN_UPGRADE = 39, //����ͻ�Ƴɹ�
	UPGRADE_OPRATE_WINGS_BLESS_NUM	= 40, //����ף������
};

//�ɸ��ᱦ
//OPRATE_TYPE_XIANFU
enum XIANFU_TYPE
{
	XIANFU_TYPE_BOSS_OCCUR		= 0,	//{1}����{2}�����, ��ɱ�ɵ���{3}
	XIANFU_TYPE_BOSS_KILL		= 1,	//{1}��{2}��ɱ, ����{3}������
};

// ������Դ��Ӧ�Ĳ�ͬ����ʾ��Ϣ
enum REWARD_TYPE
{
	REWARD_TYPE_ACTIVITY				= 0,		//��������
	REWARD_TYPE_RECHARGE				= 1,		//��ֵ���ͻ��
	REWARD_TYPE_GIFT_PACKS				= 2,		//����������
	REWARD_TYPE_QUEST					= 3,		//������ɽ������
	REWARD_TYPE_NEWPLAYER				= 4,		//����������
	REWARD_TYPE_OPEN_ITEM				= 5,		//ʹ�õ��߻��
	REWARD_TYPE_LOOT					= 6,		//ս��Ʒ
	REWARD_TYPE_GM_COMMAND				= 7,		//GM������
	REWARD_TYPE_ITEM_BLEND				= 8,		//��Ʒ�ϳɻ��
	REWARD_TYPE_SEVEN_DAY_GIFT			= 9,		//�������	
	REWARD_TYPE_JHM_GIFT				= 10,		//���������
	REWARD_TYPE_OPEN_BOX				= 11,		//��������
	REWARD_TYPE_FUBEN_EWAIJINAGLI		= 12,		//�������⽱��
	REWARD_TYPE_CAPTURE_YAOHUN			= 13,		//��׽������
	REWARD_TYPE_FSZL_EWAIJINAGLI		= 14,		//����֮·����
	REWARD_TYPE_PRESTIGE				= 15,		//��Ծ����ȡ���
	REWARD_TYPE_TIANDILINGKUANG			= 16,		//��������ȡ���
	REWARD_TYPE_PANTAOYUAN				= 17,		//���԰����
	REWARD_TYPE_WABAO					= 18,		//�ڱ����
	REWARD_TYPE_HONGYAN					= 19,		//�����¼����
	REWARD_TYPE_FORGE_DECOMPOSE			= 20,		//����ֽ���
	REWARD_TYPE_WORLD_BOSS_ROLL			= 21,		//����BOSSroll��
	REWARD_TYPE_VIP_INSTANCE_REWARD		= 22,		//vip��������
	REWARD_TYPE_TRIAL_INSTANCE_REWARD	= 23,		//����������
	REWARD_TYPE_ACHIEVE					= 24,		//�ɾͽ���
	REWARD_TYPE_SHOUCHONG				= 25,		//�׳佱��
	REWARD_TYPE_CHECKIN					= 26,		//ÿ��ǩ������
	REWARD_TYPE_GETBACK					= 27,		//�һش�������
	REWARD_TYPE_TOTAL_CHECKIN			= 28,		//ÿ���ۻ�ǩ������
	REWARD_TYPE_WELFARE_LEVEL			= 29,		//�����ȼ�����
	REWARD_TYPE_3V3_KUAFU				= 30,		//3v3�������
	REWARD_TYPE_INSTANCE_SWEEP			= 31,		//��������ɨ������
	REWARD_TYPE_XIANFU					= 32,		//�ɸ��ᱦ�������
};

enum GEM_TYPE
{
	GEM_TYPE_CRIT				= 0,		//��ʯ����
};

enum MONEYTREE_TYPE
{
	MONEYTREE_TYPE_NORMAL				= 0,		//��ͨ
	MONEYTREE_TYPE_CRIT					= 1,		//����

};

#endif //_OPRATE_RESULT_H
