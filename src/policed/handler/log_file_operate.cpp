#include "policed_app.h"
#include <net/http.h>

#include <object/SharedDef.h>

#include <shared/storage_strus.h>
#include <shared/storage_loader.h>

#include "log_file_operate.h"
#include "game_police.h"
#include "platform_post.h"
#include "policed_context.h"

const char *log_file_name[MAX_LOG_FILE_TYPE] = {
	"GAME_BUY",						//��¼�û�����Ϸ�ڹ�����Ϊ
	"GAME_SELL",					//��¼�û�����Ϸ�ڳ�����Ϊ
	"RECHARGE",						//��¼�û���ֵ��Ϊ
	"SHOP_BUY",						//��¼�û����̳ǵĹ�����Ϊ
	"ITEM_USE",						//��¼�û�ʹ���̳���Ʒ��Ϊ
	"DEAL",							//��¼�û��Ľ�����Ϊ
	"YB_INCOME",					//��¼����Ԫ������
	"ITEM_INCOME",					//��¼�����������
	"YB_EXPEND",					//��¼����Ԫ������
	"LOGIN",						//��¼�û���¼��Ϊ
	"LOGOUT",						//��¼�û��ǳ���Ϊ
	"CREATE_ROLE",					//��¼�û�������ɫ��Ϊ
	"DEATH",						//��¼�û���ɫ�����¼�
	"ACCEPT_TASK",					//��¼�û������������Ϊ
	"TASK",							//��¼�û�����������Ϊ
	"UPGRADE",						//��¼�û������¼�
	"GOLD",							//��¼�û����������Ϊ
	"MAP",							//��¼�û��л���ͼ����Ϊ
	"LONGER",						//��¼�û��Ĺһ���Ϊ
	"MONSTER",						//��¼�û���ֵ���Ϊ
	"TRANSCRIPT",					//��¼�û��򸱱�����Ϊ
	"ONLINE",						//��¼��������
	"GAME_ENTER",					//��¼�û�������Ϸ������
	"ITEM_LOG",						//��¼���ߵ�������Ϊ
	"CHAT",							//��¼��������¼
	"RELIVE",						//��¼��Ҹ���
	"BIND_GOLD",					//��¼��ҵİ�Ԫ����Ϊ
	"NEW_CARD_RECEIVE",				//��¼�û���ȡ���ֿ�����Ϊ
	"STALL",						//��¼��̯��Ϊ
	"WANTED_PACKET",				//��¼��ͨ������ҵ����а���¼
	"ERROR_PACKET",					//��¼��ȡ�û���Ϣ����İ�
	"CHOOSE_FACTION",				//��¼���ѡ����Ӫ�����
	"ACTIVITY_INFO",				//��¼��Ӫ�������Ϣ
	"ABNORMAL_PACKETS",				//��¼��Ϊ�쳣�����ߵ���ҵ���Ϊ
	"CLIENT_INFO",					//��¼��ҿͻ�����Ϣ
	"GIFTMONEY_BUY",				//��¼���������ĵ���Ϊ
	"GIFTMONEY_INCOME",				//��¼�û�����õ���Ϊ
	"ATTACK_PACKET",				//��¼������
	"FORMAT_LOG",					//��¼���߰�����־
	"CLIENT_LOG",					//��¼�ͻ�����־
	"FORGE_INFO",					//������־����
	"OBJECT_LOSS",					//1001��־
};

void LogFileOperate::HandlerInit()
{
	for (uint32 i = 0; i < MAX_LOG_FILE_TYPE; i++)
	{
		m_handle_map[i] = NULL;
	}
	m_handle_map[LOG_FILE_TYPE_RECHARGE]				= &LogFileOperate::Handle_Write_Recharge;
	m_handle_map[LOG_FILE_TYPE_DEAL]					= &LogFileOperate::Handle_Write_Deal;
	m_handle_map[LOG_FILE_TYPE_YB_INCOME]				= &LogFileOperate::Handle_Write_YbIncome;
	m_handle_map[LOG_FILE_TYPE_YB_EXPEND]				= &LogFileOperate::Handle_Write_YbExpend;
	m_handle_map[LOG_FILE_TYPE_LOGIN]					= &LogFileOperate::Handle_Write_Login;
	m_handle_map[LOG_FILE_TYPE_LOGOUT]					= &LogFileOperate::Handle_Write_Logout;
	m_handle_map[LOG_FILE_TYPE_CREATE_ROLE]				= &LogFileOperate::Handle_Write_CreateRole;
	m_handle_map[LOG_FILE_TYPE_DEATH]					= &LogFileOperate::Handle_Write_Death;
	m_handle_map[LOG_FILE_TYPE_ACCEPT_TASK]				= &LogFileOperate::Handle_Write_AcceptTask;
	m_handle_map[LOG_FILE_TYPE_TASK]					= &LogFileOperate::Handle_Write_Task;
	m_handle_map[LOG_FILE_TYPE_UPGRADE]					= &LogFileOperate::Handle_Write_Upgrade;
	m_handle_map[LOG_FILE_TYPE_GOLD]					= &LogFileOperate::Handle_Write_Gold;
	m_handle_map[LOG_FILE_TYPE_MAP]						= &LogFileOperate::Handle_Write_Map;
	m_handle_map[LOG_FILE_TYPE_TRANSCRIPT]				= &LogFileOperate::Handle_Write_Transcript;
	m_handle_map[LOG_FILE_TYPE_ONLINE]					= &LogFileOperate::Handle_Write_Online;
	m_handle_map[LOG_FILE_TYPE_GAME_ENTER]				= &LogFileOperate::Handle_Write_GameEnter;
	m_handle_map[LOG_FILE_TYPE_ITEM_LOG]				= &LogFileOperate::Handle_Write_ItemLog;
	m_handle_map[LOG_FILE_TYPE_CHAT]					= &LogFileOperate::Handle_Write_Chat;
	m_handle_map[LOG_FILE_TYPE_RELIVE]					= &LogFileOperate::Handle_Write_Relive;
	m_handle_map[LOG_FILE_TYPE_BIND_GOLD]				= &LogFileOperate::Handle_Write_BindGold;
	m_handle_map[LOG_FILE_TYPE_NEW_CARD_RECEIVE]		= &LogFileOperate::Handle_Write_NewCardReceive;
	m_handle_map[LOG_FILE_TYPE_STALL]					= &LogFileOperate::Handle_Write_Stall;
	m_handle_map[LOG_FILE_TYPE_WANTED_PACKET]			= &LogFileOperate::Handle_Write_WantedPacket;	
	m_handle_map[LOG_FILE_TYPE_CHOOSE_FACTION]			= &LogFileOperate::Handle_Write_ChooseFaction;
	m_handle_map[LOG_FILE_TYPE_ACTIVITY_INFO]			= &LogFileOperate::Handle_Write_ActivityInfo;
	m_handle_map[LOG_FILE_TYPE_CLIENT_INFO]				= &LogFileOperate::Handle_Write_ClientInfo;
	m_handle_map[LOG_FILE_TYPE_ATTACK_PACKET]			= &LogFileOperate::Handle_Write_AttackPacket;
	m_handle_map[LOG_FILE_TYPE_FORMAT_LOG]				= &LogFileOperate::Handle_Write_FormatLog;
	m_handle_map[LOG_FILE_TYPE_FORGE_LOG]				= &LogFileOperate::Handle_Write_Forge_Log;
	m_handle_map[LOG_FILE_TYPE_OBJECT_LOSS]				= &LogFileOperate::Handle_Write_ObjectLoss;
}

LogFileOperate::LogFileOperate():m_today(999),m_host(999)
{
	/*struct tm *local;
	time_t t;
	t=time(NULL);
	local = localtime(&t);
	ResetMap(local);*/
		
	for (uint32 i = 1; i < item_template_db.size(); i++)
	{
		if(item_template_db[i] == NULL)
			continue;
		if(item_template_db[i]->use_result == ITEM_USE_RESULT_DISAPPEAR)
		{
			m_can_use_item.insert(item_template_db[i]->id);
		}
	}

	for(uint32 i = 1; i < goods_db.size(); i++)
	{
		if(goods_db[i] == NULL)
			continue;
		/*TODO
		if(goods_db[i]->ingotPrice > 0)
			m_gold_goods.insert(goods_db[i]->item);
		*/
	}

	m_heal.insert(3);
	m_heal.insert(4);
	m_heal.insert(28);
	m_heal.insert(29);
	m_heal.insert(30);
	m_heal.insert(31);
	m_heal.insert(32);
	m_heal.insert(33);
	m_heal.insert(34);
	m_heal.insert(35);
	m_heal.insert(36);
	m_heal.insert(37);
	m_heal.insert(38);
	m_heal.insert(39);
	m_heal.insert(40);
	m_heal.insert(41);
	m_heal.insert(1919);
	m_heal.insert(1920);
	m_heal.insert(1921);
	m_heal.insert(1922);
	m_heal.insert(1923);
	m_heal.insert(1924);

	HandlerInit();
}

LogFileOperate::~LogFileOperate()
{	
	safe_delete(m_file_map);
}

void LogFileOperate::Update(uint32 diff)
{
	struct tm *local;
	time_t t;
	t=time(NULL);
	local = localtime(&t);
	if(local->tm_yday != m_today || local->tm_hour != m_host)
		ResetMap(local);
}

void LogFileOperate::ResetMap(struct tm *local)
{
	char datetime[14];
	sprintf(datetime, "%04d-%02d-%02d-%02d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,local->tm_hour);
	if(m_file_map.empty())
	{
		ASSERT(MAX_LOG_FILE_TYPE <= sizeof(log_file_name)/sizeof(const char*));
		for (uint32 i = 0; i < MAX_LOG_FILE_TYPE; i++)
		{
			//��־�ļ�
			stringstream ss;
			ss << g_Config.log_folder << "/" << datetime << "_" << log_file_name[i] << ".log";
			LogFileStream *file = new LogFileStream(ss.str().c_str());
			m_file_map[i] = file;
			string name = log_file_name[i];			
			StringToLower(name);
		}
	}
	else
	{
		for (FildMap::iterator it = m_file_map.begin(); it != m_file_map.end(); ++it)
		{
			ASSERT(it->second != NULL);
			stringstream ss;
			ss << g_Config.log_folder << "/" << datetime << "_" << log_file_name[it->first] << ".log";
			it->second->Open(ss.str().c_str());
		}
	}
	m_today = local->tm_yday;
	m_host = local->tm_hour;
}

void LogFileOperate::ReWriteLog(TimerHolder& th)
{
	log_packet *pkt = (log_packet*)th.param;
	uint32 log_type;
	char *account;
	char *player_id;
	uint32 sec, usec;
	pkt->pkt->rpos = 0;
	*pkt->pkt >> log_type >> sec >> usec >> account >> player_id;
	time_t t = time(NULL);
	t = t - 60;
	account_info *a_info = NULL;
	PolicedContext *player = NULL;
	if(!PolicedApp::g_app->LoadInfo(account, player_id, &a_info, &player))
	{
		if(RETRY_MAX_COUNT < ++pkt->retry_count)
		{
			LogFileStream *file = m_file_map.find(LOG_FILE_TYPE_ERROR_PACKET)->second;
			(*file) << g_Config.game_id << 0 << 0 << 0 << account 
				<< player_id << "NULL" << PolicedApp::g_app->GetPlatformID() << t << log_type;
			(*file) << LOG_SINGLE_END;
		}
		else
		{
			th._next_time += 60;
		}
		return;
	}
	else
	{
		WriteLog(pkt->pkt);
	}
	internal_protocol_free_packet(pkt->pkt);
}

void LogFileOperate::WriteAbnormalPackets(account_info *a_info, PolicedContext *player, uint32 content, uint32 p1, uint32 p2, uint32 p3)
{
	LogFileStream *file_t = m_file_map.find(LOG_FILE_TYPE_ABNORMAL_PACKETS)->second;
	WriteBaseLog(LOG_FILE_TYPE_ABNORMAL_PACKETS, *file_t, time(NULL), 0, a_info, player);
	(*file_t) << content << p1 << p2 << p3 << LOG_SINGLE_END;
	file_t->Flush();
}

void LogFileOperate::WriteBaseLog(uint32 type, LogFileStream& file, time_t sec, time_t usec, account_info *a_info, PolicedContext *player)
{
	ASSERT(a_info->id != "" || type == LOG_FILE_TYPE_ONLINE);
	
	file << g_Config.game_id << (string)a_info->sid << (string)a_info->sid << (string)a_info->uid << (string)a_info->id << player->guid() << player->GetName() << player->GetPlatformId() << sec;
}

void LogFileOperate::WriteClientLog(packet *pkt)
{
	char *uid;
	char *player_id;
	char *msg;
	uint32 type;
	//���
	if(unpack_write_client_log(pkt,&type,&uid, &player_id, &msg))
	{
		tea_perror("�յ�һ���޷��⿪�Ŀͻ�����־����");
		return;
	}
	account_info *a_info = NULL;
	PolicedContext *player = NULL;
	
	//��ȡһ���������
	if(!PolicedApp::g_app->LoadInfo("", player_id, &a_info, &player, uid))
	{
		//Ҫ��������
		tea_perror("���ID%s����һ���ͻ�����Ϣ %s�������ڴ�����ݿ����Ҳ��������Ϣ", player_id, msg);
		return;
	}		
	LogFileStream *file = m_file_map.find(LOG_FILE_TYPE_CLIENT_LOG)->second;	
	//д������Ϣ
	WriteBaseLog(LOG_FILE_TYPE_CLIENT_LOG, *file, time(NULL), 0, a_info, player);	
	//д�ͻ��˴�������Ϣ
	(*file) << type << msg << LOG_SINGLE_END;	
	//OK
	file->Flush();
}

void LogFileOperate::WriteLog(packet *pkt, account_info *a_info, PolicedContext *player)
{
	uint32 log_type;
	char *account;
	char *player_id;
	uint32 sec, usec;
	pkt->rpos = 0;
	*pkt >> log_type >> sec >> usec >> account >> player_id;

	if(log_type >= m_file_map.size())
	{
		tea_perror("LogFileOperate::WriteLog log_type %u player:%s , log_type >= m_file_map.size()", log_type, player_id);
		return;
	}

	if(a_info == NULL && !PolicedApp::g_app->LoadInfo(account, player_id, &a_info, &player))
	{
		tea_pwarn("LogFileOperate::WriteLog player_id = %s , account = %s not found, retry", player_id,account);
		log_packet *_pkt = (log_packet *)malloc(sizeof(log_packet));
		_pkt->pkt = internal_protocol_new_packet(INTERNAL_OPT_WRITE_LOG);
		packet_copy_from(_pkt->pkt, pkt);
		_pkt->retry_count = 1;
		RegTimer(fastdelegate::MakeDelegate(this, &LogFileOperate::ReWriteLog), (uint32)time(NULL) + 20, _pkt);
		return;
	}

	LogFileStream *file = m_file_map.find(log_type)->second;
	WriteBaseLog(log_type, *file, sec, usec, a_info, player);
		
	if(m_handle_map[log_type])
	{
		(this->*m_handle_map[log_type])(log_type, pkt, file, sec, usec, a_info, player);
	}
	else
	{
		tea_perror("����һ����֪����ɶ��־�İ�����־ID��%u", log_type);
	}
	
	(*file) << LOG_SINGLE_END;
	file->Flush();
}

void LogFileOperate::Handle_Write_Recharge(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info *a_info, PolicedContext* player) 
{
	double balance,amount,money;
	uint32 level, order;
	*pkt >> balance >> amount >> money >> balance >> level >> order;
	(*file) << amount << money << balance << level << order;
}

void LogFileOperate::Handle_Write_Deal(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 type, buy_mapid, buy_level, buy_cp, buy_yb;
	uint32 sell_sid, sell_mapid, sell_level, sell_cp, sell_yb;
	char *sell_user;
	char *sell_roleid;
	uint32 buy_size, sell_size;
	vector<deal_goods> buy_goods, sell_goods;
	*pkt >> type >> buy_mapid >> buy_level >> buy_cp >> buy_yb >> buy_size;
	while(buy_size != 0)
	{
		deal_goods goods;
		packet_read(pkt, (char*)&goods, sizeof(deal_goods));
		buy_goods.push_back(goods);
		buy_size --;
	}
	*pkt >> sell_sid >> sell_roleid >> sell_user >> sell_mapid >> sell_level >> sell_cp >> sell_yb >> sell_size;
	while(sell_size != 0)
	{
		deal_goods goods;
		packet_read(pkt, (char*)&goods, sizeof(deal_goods));
		sell_goods.push_back(goods);
		sell_size --;
	}
	(*file) << type << buy_mapid << buy_level << buy_cp << buy_yb;
	file->WriteDealGoods(buy_goods);
	(*file) << "NULL";

	account_info *sell_a_info = NULL;
	PolicedContext *sell_info = NULL;
	bool load_succeed = PolicedApp::g_app->LoadInfo("", sell_user, &sell_a_info, &sell_info);
	if(load_succeed)
		(*file) << sell_a_info->sid;
	else
		(*file) << sell_sid;

	(*file) << sell_roleid << sell_user << sell_mapid << sell_level << sell_cp << sell_yb;
	file->WriteDealGoods(sell_goods);
	(*file) << "NULL";
	if(load_succeed)
		(*file) << sell_info->GetName();
	else
		(*file) << "NULL";
}

void LogFileOperate::Handle_Write_ItemLog(uint32 , packet *pkt, LogFileStream *file, time_t sec, time_t usec, account_info* a_info, PolicedContext* player)
{
	uint32 itemid, amount, new_amount, opid, level, bind_mode, map_id;
	double balance,money;
	*pkt >> itemid >> amount >> new_amount >> opid >> level >> bind_mode >> balance >> money >> map_id;
	const char *bind_str = (bind_mode == ITEM_BIND_NONE ? "u" : "b");

	//�����ǲ��ǳ�ҩ
	if(opid == LOG_ITEM_OPER_TYPE_USE && m_heal.find(itemid) != m_heal.end())
	{
		opid = LOG_ITEM_OPER_TYPE_HEAL;
	}
	(*file) << itemid << opid << amount << new_amount << bind_mode << level;

	switch(opid)
	{
	case LOG_ITEM_OPER_TYPE_SHOP_BUY:
		{
			LogFileStream *file_t = m_file_map.find(LOG_FILE_TYPE_SHOP_BUY)->second;
			WriteBaseLog(LOG_FILE_TYPE_SHOP_BUY, *file_t, sec, usec, a_info, player);
			(*file_t) << balance << itemid << amount << money << level << map_id << LOG_SINGLE_END;					
			file_t->Flush();
		}
		break;
	case LOG_ITEM_OPER_TYPE_NPC_BUY:
		{
			LogFileStream *file_t = m_file_map.find(LOG_FILE_TYPE_GAME_BUY)->second;
			WriteBaseLog(LOG_FILE_TYPE_GAME_BUY, *file_t, sec, usec, a_info, player);
			(*file_t) << balance << itemid << amount << money << level << map_id << LOG_SINGLE_END;
			file_t->Flush();
		}
		break;
	case LOG_ITEM_OPER_TYPE_NPC_SELL:
		{
			LogFileStream *file_t = m_file_map.find(LOG_FILE_TYPE_GAME_SELL)->second;
			WriteBaseLog(LOG_FILE_TYPE_GAME_SELL, *file_t, sec, usec, a_info, player);
			(*file_t) << balance << itemid << amount << money << level << map_id << LOG_SINGLE_END;
			file_t->Flush();
		}
		break;
	case LOG_ITEM_OPER_TYPE_USE:
		{
			if(m_gold_goods.find(itemid) != m_gold_goods.end())
			{
				uint32 can_use = m_can_use_item.find(itemid) == m_can_use_item.end() ? 2 : 1;
				LogFileStream *file_t = m_file_map.find(LOG_FILE_TYPE_ITEM_USE)->second;
				WriteBaseLog(LOG_FILE_TYPE_ITEM_USE, *file_t, sec, usec, a_info, player);
				(*file_t) << itemid << amount << new_amount 
					<< can_use << level << map_id << LOG_SINGLE_END;
				file_t->Flush();
			}
		}
		break;
	case LOG_ITEM_OPER_TYPE_BIND_SHOP_BUY:
		{
			LogFileStream *file_t = m_file_map.find(LOG_FILE_TYPE_GIFTMONEY_BUY)->second;
			WriteBaseLog(LOG_FILE_TYPE_GIFTMONEY_BUY, *file_t, sec, usec, a_info, player);
			(*file_t) << balance << itemid << amount << money << level << map_id << LOG_SINGLE_END;
			file_t->Flush();
		}
	default:
		{
			if(((opid < 200 || opid > 300) && opid != 302 && opid != 303 && opid != 304)
				&& m_gold_goods.find(itemid) != m_gold_goods.end())
			{
				LogFileStream *file_t = m_file_map.find(LOG_FILE_TYPE_ITEM_INCOME)->second;
				WriteBaseLog(LOG_FILE_TYPE_ITEM_INCOME, *file_t, sec, usec, a_info, player);
				(*file_t) << itemid << amount << level << opid << LOG_SINGLE_END;
				file_t->Flush();
			}
		}
		break;
	}
}

void LogFileOperate::Handle_Write_YbIncome(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext* player)
{
	double amount, balance,old_value,unit_price;
	uint32 level, reason,p1,p2,quest;
	string trace_id;
	uint16 item_bind,item_del;
	*pkt >> amount >> balance >> level >> reason >> old_value >> trace_id >> p1 >> p2 >> unit_price >> item_bind >> item_del >> quest;
	(*file) << amount << balance << level << reason << old_value << trace_id << p1 << p2 << unit_price << item_bind << item_del << quest;
}

void LogFileOperate::Handle_Write_YbExpend(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext* player)
{
	double amount, balance,old_value,unit_price;
	uint32 level, reason,p1,p2,quest;
	string trace_id;
	uint16 item_bind,item_del;
	*pkt >> amount >> balance >> level >> reason >> old_value >> trace_id >> p1 >> p2 >> unit_price >> item_bind >> item_del >> quest;
	(*file) << amount << balance << level << reason << old_value << trace_id << p1 << p2 << unit_price << item_bind << item_del << quest;
}

void LogFileOperate::Handle_Write_Login(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext* player)
{
	uint32 level, map_id;
	string ip, group;
	double power;
	*pkt >> level >> ip >> map_id >> group >> power;
	(*file) << level << ip << map_id << (group.size() == 0 ? "NULL" : group) << power;
	for (auto it:PolicedApp::g_app->m_platform_post)
	{
		it->UpgradePost(a_info, player, m_time, level, power);
	}

	player->ip = ip;

	if(!player->ip.empty())
	{
		uint32 a,b,c,d;
		sscanf(player->ip.c_str(),"%u.%u.%u.%u",&a,&b,&c,&d);
		player->uip = ((a << 24) | (b << 16) | (c << 8) | d);
	}
}

void LogFileOperate::Handle_Write_Logout(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext* player)
{
	uint32 level, map_id;
	string ip, group;
	*pkt >> level >> ip >> map_id >> group;
	(*file) << level << ip << map_id << (group.size() == 0 ? "NULL" : group);
}

void LogFileOperate::Handle_Write_CreateRole(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext* player)
{
	string rolename, ip;
	*pkt >> rolename >> ip;
	(*file) << rolename << ip;
}

void LogFileOperate::Handle_Write_Death(uint32 , packet *pkt, LogFileStream *file, time_t sec, time_t , account_info* , PolicedContext* player)
{
	string reason;
	uint32 level, map;
	uint32 is_player;
	*pkt >> reason >> level >> map >> is_player;
	(*file) << reason << level << map << is_player;
}

void LogFileOperate::Handle_Write_AcceptTask(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 taskid, type, map;
	*pkt >> taskid >> type >> map;
	(*file) << taskid << type << map;
}

void LogFileOperate::Handle_Write_Task(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 taskid, map_id, result;
	*pkt >> taskid >> map_id >> result;
	(*file) << taskid << map_id << result;
}

void LogFileOperate::Handle_Write_Upgrade(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext *player)
{
	uint32 level, map;
	double power;
	*pkt >> level >> map >> power;
	(*file) << level << map << power;
	for (auto it:PolicedApp::g_app->m_platform_post)
	{
		it->UpgradePost(a_info, player, m_time,level, power);
	}
}

void LogFileOperate::Handle_Write_Gold(uint32 , packet *pkt, LogFileStream *file, time_t sec, time_t usec, account_info* a_info, PolicedContext *player)
{
	uint32 status, map,quest,p1,p2;
	uint32 level = 0;
	double sum, old_value, new_value, warehouse_value,unit_price;
	string trace_id;
	uint16 item_bind,item_del;
	*pkt >> sum >> status >> map >> old_value >> new_value >> warehouse_value >> trace_id >> p1 >> p2 >> unit_price >> item_bind >> item_del >> quest >> level;
	(*file) << sum << status << map << old_value << new_value << warehouse_value << trace_id << p1 << p2 << unit_price << item_bind << item_del << quest << level;
}

void LogFileOperate::Handle_Write_Map(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 level, nonce_map, to_map;
	*pkt >> level >> nonce_map >> to_map;
	(*file) << level << nonce_map << to_map;
}

void LogFileOperate::Handle_Write_Transcript(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 starttime, timelong, num, level, map_id;
	*pkt >> starttime >> timelong >> num >> level >> map_id;
	(*file) << starttime << timelong << num << level << map_id;
}

void LogFileOperate::Handle_Write_Online(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext* player)
{
	uint32 account_count = 0;
	uint32 player_count = 0;

	*pkt >> account_count >> player_count;
	*file << account_count << player_count;
}

void LogFileOperate::Handle_Write_GameEnter(uint32 log_type, packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info , PolicedContext* player)
{
	string ip;
	*pkt >> ip;
	*file << 0 << ip;
}

void LogFileOperate::Handle_Write_Chat(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext* player)
{
	//�������ͣ����������ҵȼ������GM�ȼ�
	uint32 chattype, level, gmlevel;
	//��������
	string playerto,content,nameto;
	*pkt >> chattype >> playerto >> content >> level >> gmlevel >> nameto;	
	(*file) << chattype << playerto << nameto << content << level << gmlevel;

	for (auto it:PolicedApp::g_app->m_platform_post)
	{
		it->ChatPost(a_info, player, chattype, playerto, level, gmlevel, content,nameto);
	}
}

void LogFileOperate::Handle_Write_Relive(uint32 , packet *pkt, LogFileStream *file, time_t sec, time_t , account_info *a_info, PolicedContext *player)
{
	uint32 type, map;
	*pkt >> type >> map;
	(*file) << type << map;
}

void LogFileOperate::Handle_Write_BindGold(uint32 , packet *pkt, LogFileStream *file, time_t sec, time_t usec, account_info* a_info, PolicedContext* player)
{
	uint16 oper_type,item_bind,item_del;
	uint32 item_id, count, level, map,quest;
	string trace_id;
	double v, old_value, new_value,unit_price;
	*pkt >> oper_type >> v >> old_value >> new_value >> trace_id >> item_id >> count >> level >> map >> unit_price >> item_bind >> item_del >> quest;
	(*file) << oper_type << v << old_value << new_value << trace_id << item_id << count << level << map << unit_price << item_bind << item_del << quest;
	if(old_value < new_value)
	{
		LogFileStream *file_t = m_file_map.find(LOG_FILE_TYPE_GIFTMONEY_INCOME)->second;
		WriteBaseLog(LOG_FILE_TYPE_GIFTMONEY_INCOME, *file_t, sec, usec, a_info, player);
		(*file_t) << v << new_value << oper_type << level << map << LOG_SINGLE_END;
		file_t->Flush();
	}
}

void LogFileOperate::Handle_Write_NewCardReceive(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 map, x, y;
	char * card_id;
	*pkt >> card_id >> map >> x >> y;
	(*file) << card_id << map << x << y;
}

void LogFileOperate::Handle_Write_Stall(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 entry, amount, ingot_price, silver_price, stall_type;
	string item_guid;
	*pkt >> item_guid >> entry >> amount >> ingot_price >> silver_price >> stall_type;
	(*file) << item_guid << entry << amount << ingot_price << silver_price << stall_type;
}

void LogFileOperate::Handle_Write_WantedPacket(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 tv_sec, tv_usec;
	uint16 optcode;
	char *content;
	*pkt >> tv_sec >> tv_usec >> optcode >> content;
	(*file) << tv_sec << tv_usec << optcode << content;
}

void LogFileOperate::Handle_Write_ChooseFaction(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 oper_type, result;
	*pkt >> oper_type >> result;
	(*file) << oper_type << result;
}

void LogFileOperate::Handle_Write_ActivityInfo(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 type, version, acti_id;
	*pkt >> type >> version >> acti_id;
	static char v_id[100];
	sprintf(v_id, "%u_%u", version, acti_id);
	(*file) << type << v_id;
}

void LogFileOperate::Handle_Write_ClientInfo(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* a_info, PolicedContext* player)
{
	string client, browser, isdebug, language, version, flash_version, x, y, os, login_type;
	*pkt >> client >> browser >> isdebug >> language >> version >> flash_version >> x >> y >> os;
	(*file) << client << browser << isdebug << language << version << flash_version << x << y << os;
	login_type = client.compare("0") == 0 ? "web" : "desk";
}

void LogFileOperate::Handle_Write_AttackPacket(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	uint32 p_id, type;
	string content;
	*pkt >> p_id >> type >> content;
	(*file) << p_id << type << content;
}

void LogFileOperate::Handle_Write_FormatLog(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	string content;
	*pkt >> content;
	(*file) << content;
}

void LogFileOperate::Handle_Write_Forge_Log(uint32, packet *pkt, LogFileStream *file, time_t, time_t, account_info*, PolicedContext*)
{
	string traget_id,before_data,after_data;
	uint32 forge_type,forge_property,result_type;
	*pkt >> traget_id >> forge_type >> forge_property >> result_type >> before_data >> after_data;
	(*file) << traget_id << forge_type << forge_property << result_type << before_data << after_data;
}

//1001��־
void LogFileOperate::Handle_Write_ObjectLoss(uint32 , packet *pkt, LogFileStream *file, time_t, time_t , account_info* , PolicedContext*)
{
	string obj_guid;
	uint32 op_type;
	*pkt >> obj_guid >> op_type;
	(*file)<< obj_guid << op_type;
}