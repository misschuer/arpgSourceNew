/************************************************************************
 * file	:internal_protocol.h                                                                     
 * desc	:���ļ����������з�����֮��ͨѶ��Э��
 *			����Ҫʵ��Э�鼶���,���ݰ�����
 *
 *
 * author:	linbc
 * date:	20110418
 * version:
 ************************************************************************/
#ifndef _SVRCOER_PROTOCOL_H_
#define _SVRCOER_PROTOCOL_H_

#include <svrcore-internal.h>

//������֮���ڲ�ͨѶЭ��
enum Internal_Opcode_Type
{
	INTERNAL_OPT_NULL					= 0,
	INTERNAL_OPT_REG_SERVER				= 1,		//ע�������,���������ӵ����ط�,�ɴ�ȷ�����

	//�������������� begin
	INTERNAL_OPT_CREATE_CONN			= 2,		//�����ӽ���
	INTERNAL_OPT_DESTORY_CONN			= 3,		//�Ͽ�����
    INTERNAL_OPT_PING_PONG  			= 4,		//INTERNAL_OPT_DUPLICATE_CONN,�ظ�����
	INTERNAL_OPT_PACKET_GATE			= 5,		//��Ϣ��ת��
	INTERNAL_OPT_PACKET_GATE_LIST		= 6,		//ת�����б�	
	INTERNAL_OPT_REG_TOFD				= 7,		//ע�����ݰ���ת������
	//�������������� end

	//�ڲ�������� begin
	INTERNAL_OPT_UD_OBJECT				= 8,		//�ڲ��������	
	INTERNAL_OPT_UD_CONTROL				= 9,		//�ڲ�������¿���Э��
	INTERNAL_OPT_UD_CONTROL_RESULT		= 10,		//�ڲ�������¿���Э����
	__INTERNAL_OPT_UD_UNKOWN			= 11,		//�ڲ��������Ԥ��
	//�ڲ�������� end

	//��̨���� begin
	INTERNAL_OPT_COMMMAND				= 12,		//��̨����
	INTERNAL_OPT_COMMMAND_RESULTS		= 13,		//��̨����ִ�н��
	//��̨���� end

	INTERNAL_OPT_GET_ONLINE_PLAYER		= 14,		//�����ķ���ȡ������������б�
	INTERNAL_OPT_GET_SESSION			= 15,		//���get session
	INTERNAL_OPT_CENTD_DESTORY_CONN		= 16,		//֪ͨ���ķ��Ͽ�����

	INTERNAL_OPT_OPEN_TIME				= 17,		//ͬ��������ʱ��

	INTERNAL_OPT_SPLICE					= 18,		//�������ƴ��
	INTERNAL_OPT_PACKET_CENTD_ROUTER	= 19,		//���ķ�·�ɰ�
	INTERNAL_OPT_SAVE_ALL_DATA			= 20,		//���ķ�������¼����֪ͨ������������
	INTERNAL_OPT_GM_COMMMANDS			= 21,		//GM����
	__INTERNAL_OPT_UNKOWN1				= 23,		//����Ҵ��ͻ���Ϸ��
	INTERNAL_OPT_PLAYER_LOGIN			= 24,		//��ҵ�¼�ɹ�
	INTERNAL_OPT_UNSET_RELEASE_MYSELF	= 25,		//���ñ�����Ϊ�������ͷ��Լ���
	INTERNAL_OPT_LOAD_OBJECT			= 26,		//��������ݿ��ȡ���󼯺�
	INTERNAL_OPT_RELEASE_OBJECT			= 27,		//֪ͨ���ķ��Ƴ�û�ж��ĵĶ���
	///////////////////////////////////////////а��ķָ���////////////////////////////////////////////////
	//���ϣ�Ҫô���ķ�������Ҫô�������ط�
	//���£����Ǹ����������Լ����Ƶ�Э����
	//�����ڵ���ƣ�������·�ɰ�
	
	INTERNAL_OPT_CALLBACK,					//�ص�Э��
	INTERNAL_OPT_PLAYER_LOGOUT,				//����˳���¼�ɹ�
	INTERNAL_OPT_LOGIND_MERGE_SERVER,		//��½���·��Ϸ�֪ͨ
	
	INTERNAL_OPT_JOIN_MAP,					//����ƶ�����ͼ
	INTERNAL_OPT_LEAVE_MAP,					//����뿪��ͼ
	INTERNAL_OPT_APPD_TELEPORT,				//Ӧ�÷�������
	INTERNAL_OPT_ADD_MAP_INSTANCE,			//֪ͨ������ͼʵ��
	INTERNAL_OPT_DEL_MAP_INSTANCE,			//֪ͨɾ����ͼʵ��
	INTERNAL_OPT_ADD_TAG_WATCH,				//������ȫ

	INTERNAL_OPT_USER_ITEM,					//ʹ����Ʒ
	INTERNAL_OPT_USER_ITEM_RESULT,			//ʹ����Ʒ���	
	INTERNAL_OPT_QUEST_ADD_REW_ITEM,		//������������Ʒ
	INTERNAL_OPT_WRITE_LOG,					//֪ͨ��־��д��־
	INTERNAL_OPT_NOTICE,					//������
	INTERNAL_OPT_CHAT,						//����ӿ�
	INTERNAL_OPT_ADD_GIFT_PACKS,			//֪ͨ��½��������
	INTERNAL_OPT_UPDATE_EQUIP_INFO,			//Ӧ�÷��������װ��/�������Ե�������
	INTERNAL_OPT_RECALCULATION_ATTR,		//֪ͨӦ�÷���������	 
	INTERNAL_OPT_DEL_CHAR,					//ɾ����ɫ
	INTERNAL_OPT_USER_KILLED,				//��ұ����ɱ��
	INTERNAL_OPT_LOOT_SELECT,				//���ʰȡս��Ʒ
	INTERNAL_OPT_ADD_EXP,					//Ӧ�÷�֪ͨ���������Ӿ���
	INTERNAL_OPT_DELETE_BINLOG,				//֪ͨ���ݷ�ɾ��binlog

	INTERNAL_OPT_ADD_GOLD_LOG = 51,				//����Ԫ��������¼
	INTERNAL_OPT_ADD_FORGE_LOG,				//���������¼
	INTERNAL_OPT_SCENED_CONSUME_MONEY,		//ʹ��Ԫ��,ͭǮ֪ͨ��������Щʲô
	INTERNAL_OPT_APPD_ADD_MONEY,			//֪ͨӦ�÷�����money
	INTERNAL_OPT_APPD_SUB_MONEY,			//֪ͨӦ�÷���money
	
	INTERNAL_OPT_SYNC_GUID_MAX = 57,				//�Ϸ�ʱͬ��guid�����������ۼ�ֵ
	
	INTERNAL_OPT_HT_FORGE_UP = 62,				//������̨����������־
	
	INTERNAL_OPT_MAP_ROUTER_PKT,			//��ͼʵ��֮��İ�

	INTERNAL_OPT_CLOSE_SCENED,				//֪ͨ����������������ˣ��Լ��ص��Լ���	
	INTERNAL_OPT_OFFLINE_OPER,				//���߲���
	INTERNAL_OPT_OFFLINE_OPER_RESULT,		//���߲���,binlog���������	
	INTERNAL_OPT_SAVE_BACKUP,				//���汸�����ݼ�¼	
	INTERNAL_OPT_LOGIN_LOCK_INFO,			//֪ͨ��½�������Ϣ
	INTERNAL_OPT_TENCENT_LOG,				//֪ͨ��־��д��Ѷ��־
	INTERNAL_OPT_LOGIND_HOSTING,			//֪ͨ��½���йܵ�¼
	INTERNAL_OPT_LOGS_FIRST_RECHARGE,		//Ӧ�÷���������־�������׳��¼

	INTERNAL_OPT_ADD_MAP_WATHER = 73,			//��ӵ�ͼ�۲���

	INTERNAL_OPT_UPGRADE_LEVEL,				//�������

	INTERNAL_OPT_APPD_TO_SEND_DO_SOMETHING = 75,
	INTERNAL_OPT_SEND_TO_APPD_DO_SOMETHING = 76,
	
	INTERNAL_OPT_UPDATE_GAG_STATUS,			//֪ͨ��־�����½���״̬
	INTERNAL_OPT_UPDATE_LOCK_STATUS,		//֪ͨ��־�����·��״̬

	INTERNAL_OPT_UPDATE_SPELL_INFO			= 81,		//֪ͨ���������¼�����Ϣ
	INTERNAL_OPT_CHANGE_DIVINE_INFO			= 82,		//֪ͨ����������滻
	INTERNAL_OPT_REPLACE_EQUIPED_SPELL		= 83,		//֪ͨ������װ���ۼ����滻
	INTERNAL_OPT_ILLUSION					= 84,		//֪ͨ�����������û�
	INTERNAL_OPT_ADD_ITEMS					= 85,		//֪ͨӦ�÷��Ӷ������
	INTERNAL_OPT_LOGIND_TELEPORT			= 86,		//��¼��������

	INTERNAL_OPT_KUAFU_ENTER				= 90,		//Ӧ�÷�֪ͨ��¼�������Ϣ
	INTERNAL_OPT_KUAFU_BACK					= 91,		//��������֪ͨ��¼������һ���Ϸ��

	INTERNAL_OPT_INVITE_RET					= 92,		//����Ĵ�����

	INTERNAL_OPT_FACTION_BOSS_WIN			= 93,		//��սboss�ɹ�
	INTERNAL_OPT_FACTION_BOSS_FAIL			= 94,		//��սbossʧ��
	INTERNAL_OPT_FACTION_ADD_TOKEN_POINTS	= 95,		//��ɱҰ�ֵ���
	INTERNAL_OPT_FACTION_BOSS_DAMAGED		= 96,		//��boss����˺�
	INTERNAL_OPT_FACTION_UPDATE_BOSS_INFO	= 97,		//����boss��Ϣ
	INTERNAL_OPT_FACTION_UPDATE_TARGET_INFO	= 98,		//���±���Ŀ����Ϣ


	INTERNAL_OPT_FACTION_BOSSDEFENSE_WIN	= 99,		//����������ս�ɹ�
	INTERNAL_OPT_FACTION_BOSSDEFENSE_LEAVE	= 100,		//����������ս����뿪����
	INTERNAL_OPT_RENAME_CHECK				= 101,		//�޸����Ƽ��
	INTERNAL_OPT_RENAME_CHECK_RESULT		= 102,		//�޸����Ƽ����
	INTERNAL_OPT_UPDATE_CHAR_NAME			= 103,		//��������

	INTERNAL_OPT_SEND_TO_APPD_ADD_OFFLINE_MAIL = 104, //���������ʼ�

	MAX_INTERNAL_OPT						= 9999,//�ڲ���������
};

//����������
enum ServerType
{
	SERVER_TYPE_NETGD	= 0,		//���ط�
	SERVER_TYPE_CENTD	= 1,		//���ķ�
	SERVER_TYPE_LOGIND	= 2,		//��¼��
	SERVER_TYPE_APPD	= 3,		//Ӧ�÷�
	SERVER_TYPE_POLICED	= 4,		//��־��
//	SERVER_TYPE_ROBOTD	= 5,		//�����˷�
	SERVER_TYPE_SCENED	= 6,		//������
};

// ������������Ϣ�±�
// ǰ��16λ�����Ӵ���������16λ�ǳɹ����Ӵ���
#define SERVER_CONN_LIST_FIELD_CONN_NUM 0	// ���ַ��������Ӵ�������Ԥ����20�ַ�������
#define SERVER_CONN_LIST_FIELD_WORLD_STATUS 19		// ���������״̬
#define SERVER_CONN_LIST_FIELD_SERVER_INFO_START 20	// ��������Ϣ��ʼ�±�

//��������Ϣö��
enum EServerConnInfo
{
	SERVER_CONN_INFO_ID				= 0,	//����ID
	SERVER_CONN_INFO_TYPE			= 1,	//����������
	SERVER_CONN_INFO_LINENO			= 2,	//��·
	SERVER_CONN_INFO_COUNT			= 3,	//�������
	SERVER_CONN_INFO_PING_PONG_MS	= 4,	//��Ӧʱ��
	SERVER_CONN_INFO_SCENED_TYPE	= 5,	//���������� 0)�油��ͼ 1)��ͨ��ͼ 2)���ͼ 3)������ͼ�����Գ�������Ч
	SERVER_CONN_INFO_PID			= 6,	//Զ�̵Ľ��̺�
	SERVER_CONN_INFO_FLAG			= 7,	//һЩ��־
	MAX_SERVER_CONN_INFO,
};

//��������־λ��׼������
#define SERVER_CONN_INFO_FLAG_READY_OK 0

//����������
enum EScenedType
{
	SCENED_TYPE_NONE = 0,
	SCENED_TYPE_NO_INST = 1,
	SCENED_TYPE_ACTIVI = 2,
	SCENED_TYPE_INST = 3,
	MAX_SCENED_TYPE
};

//������ע������
enum EServerRegTypes
{
	SERVER_REG_TYPE_SINGLETON	= 0,	//ֻ����һ�����ӵķ�����
	SERVER_REG_TYPE_PLURAL		= 1,	//���Ժܶ�����Ӳ���ķ�����
};

/*************************************************************************************/
/**/
/*************************************************************************************/

/*
 *	call_packet_gate - ����ת��
 *	@dst :�����°�ָ��
 *	@pkt :��Ҫת�����ݰ�
 *
 *	@return	: 0�ɹ� -1ʧ��
 *  
 */
TEA_SVRCORE_API int pack_packet_gate(server_packet **dst,packet *pkt);

/*
 *	on_packet_gate - �� ����ת��
 *	@src :	���ݰ�
 *	@lppkt :������ת�����ݰ�
 *
 *	@return	: 0�ɹ� -1ʧ��
 *  
 */
TEA_SVRCORE_API int unpack_packet_gate(server_packet *src,packet *lppkt);

/*
 *	call_packet_gate_list - ����ת�����ݰ�
 *	@dst :�����°�ָ��
 *	@pkt :��Ҫת�����ݰ��б�
 *
 *	@return	: 0�ɹ� -1ʧ��
 *  
 */
TEA_SVRCORE_API int pack_packet_gate_list(server_packet **dst,list_t *pkt_head);

/*
 *	on_packet_gate_list - ������ת�����ݰ�
 *	@src :��Ҫ�⿪���ݰ�
 *	@pkt_head :�⿪����������
 *
 *	@return	: 0�ɹ� -1ʧ��
 *  
 */
TEA_SVRCORE_API int unpack_packet_gate_list(server_packet *src,list_t *pkt_head);

/*
 *	pack_reg_to_fd - ע�����ݰ�����
 *	@dst :�����°�ָ��
 *	@player_fd :��� �ļ�������
 *	@to_fd :ת����  �ļ�������
 *	@num:����
 *	@opts:��������
 *
 *	@return	:$return$
 *  
 */
TEA_SVRCORE_API int pack_reg_to_fd(server_packet **dst,int player_fd,int to_fd,uint16 num,const uint16 *opts);

/*
 *	unpack_reg_to_fd - 
 *	@dst :�����°�ָ��
 *	@player_fd :��� �ļ�������
 *	@to_fd :ת����  �ļ�������
 *	@num:����
 *	@opts:��������
 *
 *	@return	: 0�ɹ� -1ʧ��
 *  
 */
TEA_SVRCORE_API int unpack_reg_to_fd(server_packet *src,int *player_fd,int *to_fd,uint16 *num,uint16 **opts);

/*
 *	pack_reg_server - ע������� ���
 *	@dst : �°�
 *	@server_type : ����������
 *
 *	@return	: 0�ɹ� -1ʧ��
 *  
 *	�������������ӵ����ط��Ժ�
 *	��Ҫ�ɴ˽���ע��,�����ط�����ȷ�ϰ���ת��ȥ��
 *	Ŀǰ�Ƚϼ�,�������ķ����ʹ˰�����
 */
TEA_SVRCORE_API int pack_reg_server(server_packet **dst,int fd,int server_type,int pid, int reg_type);

/*
 *	unpacket_reg_server - ע������� ���
 *	@src :
 *	@server_type :����������	0 ���ط� 1 ���ķ� 2 ������ 3 Ӧ�÷�
 *
 *	@return	: 0�ɹ� -1ʧ��
 *  
 */

TEA_SVRCORE_API int unpacket_reg_server(server_packet *src,int* fd,int *server_type,int *pid);

//����������ʱ��
TEA_SVRCORE_API int pack_internal_open_time(packet **dst,uint32 open_time,struct timeval *tv);

TEA_SVRCORE_API int unpack_internal_open_time(packet *src,uint32 *open_time,struct timeval *tv);

//֪ͨ��־��д��־
TEA_SVRCORE_API int unpack_internal_write_log(packet *src, uint32 *log_type, time_t *sec, time_t *usec, char **user, char **roleid);


#endif

