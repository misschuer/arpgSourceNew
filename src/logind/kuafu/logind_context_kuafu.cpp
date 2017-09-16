#include "logind_context.h"
#include <comm/log.h>
#include <object/SharedDef.h>
#include <object/OprateResult.h>
#include <time.h>
#include "logind_app.h"
#include <shared/log_handler.h>
#include <shared/chat_analysis.h>
#include "logind_mongodb.h"
#include "logind_cache.h"
#include "map_manager.h"
#include "logind_script.h"
#include "logind_mongodb.h"
#include "logind_object_manager.h"
#include "logind_mongodb.h"
#include "logind_context_login_mgr.h"
#include <net/http.h>
#include <comm/b64.h>
#include <comm/crypt.h>
#include "http_handler.h"

bool Encode(ByteArray &bytes)
{
	return true;
}

bool Decode(ByteArray &bytes)
{
	////��Կ
	//{
	//	string auth_str;
	//	uint32 rpos = pkt.rpos;
	//	uint32 wpos = pkt.wpos;

	//	//������
	//	pkt >> auth_str;

	//	int8 output[33];
	//	memset(output,0,sizeof(output));

	//	//��ȡУ�����,�������ݻ���
	//	pkt.wpos = rpos;
	//	packet_write_str(&pkt,/*g_Config.kuafu_battle_key.c_str()*/"��Կ");

	//	MD5CryptToStr32((int8*)pkt.content,pkt.wpos,output);

	//	if(auth_str != output)
	//	{
	//		tea_perror("CentdContext::Handle_World_War_CS_Player_Info: auth_str != output,[%s,%s]",m_account.c_str(),output);
	//		Close();		
	//		return;
	//	}

	//	//�ָ��ֳ�
	//	pkt.wpos = wpos;			
	//}
	return true;
}

bool KuaFuCanCarry(GuidObject *obj)
{
	EObjectTypePrefix t = GuidManager::GetPrefix(obj->guid());
	//�ж�ɾ������
	switch(t)
	{
	case ObjectTypePlayer:
	case ObjectTypeItemMgr:
		return true;
	}
	return false;
}

//��ͻ��˷��Ϳ������
void LogindContext::Call_World_War_CS_Player_Info(const string &server_ip, uint32 port, const string &sessionkey)
{
	tea_pdebug("LogindContext::Call_World_War_CS_Player_Info  %s  %s  %u  %s", m_lguid.c_str(), server_ip.c_str(), port, sessionkey.c_str());
	packet *pkt = external_protocol_new_packet(MSG_WORLD_WAR_SC_PLAYER_INFO);
	//ս����IP,ս�����˿ڣ�session key, �ȵ�
	*pkt << server_ip << port << sessionkey;

	ByteArray bytes;
	vector<GuidObject*> vec;
	ObjMgr.GetDataSetAllObject(m_lguid,vec);
	for (auto* obj: vec)
	{
		if(KuaFuCanCarry(obj))
			obj->WriteCreateBlock(bytes);
	}
	bytes.position(0);
	ObjMgr.Compress(bytes);

	Encode(bytes);

	*pkt << uint16(bytes.length()) ;
	packet_write(pkt,bytes.data(),bytes.length());

	string end_string = "end";
	*pkt << end_string;
	update_packet_len(pkt);
	SendPacket(*pkt);
	external_protocol_free_packet(pkt);

	Call_merge_server_msg(m_delegate_sendpkt,server_ip.c_str(), port, sessionkey.c_str(),MERGE_TYPE_GAME_TO_PK,1,0);	
}


//Pk����¼
void LogindContext::Hanlde_pk_login(packet& pkt)
{
	logind_player* player = nullptr;
	string server_ip, sessionkey;
	uint32 port;
	pkt >> server_ip >> port >> sessionkey;

	vector<string> guid_vec;
	//try
	//{
	//��ȡһ��bytearray���ڽ⿪����
	{
		ByteArray bytes;
		uint16 byte_len ;
		pkt >> byte_len;
		bytes.writeBytes(pkt.content + pkt.rpos, byte_len);
		pkt.rpos += byte_len;
		string end_string;
		pkt >> end_string;

		Decode(bytes);
		ByteArray out_bytes;
		bytes.position(0);
		ObjMgr.UnCompress(bytes,out_bytes);
		out_bytes.position(0);
		while (out_bytes.bytesAvailable())
		{
			int flag = out_bytes.readByte();
			string guid = out_bytes.readUTF();
			BinLogObject *obj;
			if(GuidManager::GetPrefix(guid) == ObjectTypePlayer)
			{
				player = new logind_player;
				obj = player;
				if(m_lguid.empty())
				{
					m_lguid = guid;
				}
				else
				{
					//�����������⣬�ص���
					tea_pdebug("LogindContext::Hanlde_pk_login  !m_lguid.empty() %s  %s", m_lguid.c_str(), guid.c_str());
					Close(PLAYER_CLOSE_OPERTE_LOGDIN_ONE58,"");
					return;
				}
			}
			else
			{
				obj = new BinLogObject;
			}
			obj->ReadFrom(flag,out_bytes);
			obj->guid(guid);
			m_temp_vec.push_back(obj);
			guid_vec.push_back(guid);
		}
	}		
	//}
	//catch (...)
	//{
	//	tea_perror("Handle_World_War_CS_Player_Info: Unpack the failure! %s",m_account.c_str());
	//	Close();	
	//	return;
	//}
	SetStatus(STATUS_TRANSFER2);
	
	if (m_watcher_guid.empty())
		LogindApp::g_app->m_login_queue->PushAction(m_lguid, fd_, CONTEXT_LOGIN_ACTION_LOGIN);
	else
	{//�۲���,ֱ���·���Ҷ�����ͻ��������ͻ��˽����ս,�������Ǻ��� todo lhs��
		if (player)
		{
			ByteArray byte;
			player->WriteCreateBlock(byte);
			byte.position(0);
			ObjMgr.Compress(byte);
			byte.position(0);
			packet *spkt = external_protocol_new_packet(SMSG_UD_OBJECT);
			packet_write(spkt,(char*)byte.cur_data(),byte.bytesAvailable());
			update_packet_len(spkt);
			SendPacket(*spkt);
			external_protocol_free_packet(spkt);
		}
		//�ͷ��ڴ�
		for(auto it:m_temp_vec)
			safe_delete(it);
		m_temp_vec.clear();
	}
}

//�ͻ�������ش�����Ϸ��
void LogindContext::Handle_GoBackTo_GameServer(packet& pkt)
{
	if (!m_watcher_guid.empty())
	{//�۲��߻ص���Ϸ��
		string host, port;
		LogindApp::g_app->m_http->GetHostPortByServerName(m_backsvrname, host, port);
		string session_str = LogindApp::g_app->MakeSessionKey(m_account,m_isFcm, "", WANNENG_LOGIN_KEY);
		//֪ͨ�ͻ��˶Ͽ���Ϸ������pk��
		Call_merge_server_msg(m_delegate_sendpkt, host.c_str(), atol(port.c_str()),session_str.c_str(),MERGE_TYPE_PK_TO_GAME,1,0);
		return;
	}
	else
	{
		if (!m_player 
			||!m_player->IsKuafuPlayer() 
			||LogindApp::g_app->IsGameServer())
		{
			tea_pdebug("player %s want to go back to game server, but this is the game server!!!", GetGuid().c_str());
			return ;
		}
		m_player->GetSession()->GoBackToGameSvr();
	}	
}

//�������pk���ص���Ϸ��
bool LogindContext::GoBackToGameSvr()
{
	string host, port;
	LogindApp::g_app->m_http->GetHostPortByServerName(m_backsvrname, host, port);
	//�����������	
	bool is_fcm = m_player->GetFCMLoginTime() != (-1);
	string session_str = LogindApp::g_app->MakeSessionKey(m_player->GetAccount(),is_fcm, "", WANNENG_LOGIN_KEY);
	//֪ͨ�ͻ��˶Ͽ�pk��������Ϸ��
	Call_merge_server_msg(m_delegate_sendpkt, host.c_str(), atol(port.c_str()),session_str.c_str(),MERGE_TYPE_PK_TO_GAME,1,0);

	return true;
}

//�����¿����Ϣ
void LogindContext::ResetKuafuInfo()
{
	if (!m_player->IsKuafuPlayer())
		return;

	m_warid = m_player->GetKuafuWarId();
	m_kuafutype = m_player->GetKuafuType();
	m_number = m_player->GetKuafuNumber();
	m_backsvrname = m_player->GetDBKuafuInfo();
}

//������Э��
// ��appd���������ڲ�������pk����¼��Ϣ
void LogindContext::Hanlde_Kuafu_Enter(packet& pkt)
{
	if(LogindApp::g_app->IsPKServer())
	{
		tea_perror("func Hanlde_Kuafu_Enter, this server is not game server !");
		return ;		//����Pk������ô�ᷢ��������
	}
	uint32 kuafu_type;
	char *str_data, *watcher_guid;
	if(unpack_kuafu_chuansong(&pkt, &str_data, &watcher_guid, &kuafu_type))
	{
		tea_pwarn("LogindContext::Hanlde_Kuafu_Enter fail");
		return;
	}
	if (!m_player)
	{
		tea_pdebug("LogindContext::Hanlde_Kuafu_Enter m_player is null!");
		return;
	}
	string player_guid = GetGuid();
	if (!m_player->GetSession())
	{
		tea_pdebug("func Hanlde_Kuafu_Enter player session is null !!! guid = %s", player_guid.c_str());
		return;
	}

	if (kuafu_type == KUAFU_TYPE_FENGLIUZHEN)
	{//������
		if (strlen(str_data) == 0)
		{
			tea_pdebug("func Hanlde_Kuafu_Enter str_data is empty!!! guid = %s", player_guid.c_str());
			return;
		}
		//�и��ַ���
		std::map<string,string> querys;
		if(!parseURL(str_data,querys))
		{
			tea_pdebug("func Hanlde_Kuafu_Enter str_data is %s !parseURL(str_data,querys)", str_data);
			WriteAttackPacker(GetAccount(), GetGuid(), pkt.head->optcode, ACCACK_PACKET_TYPE_DATA,"");
			return;
		}
		//�Ƿ�ɹ�
		if (querys["type"] != "normal")
		{
			tea_pdebug("func Hanlde_Kuafu_Enter response is != normal !");
			return;
		}

		Tokens token;
		StrSplit(token, querys["data"], ';');
		if (token.size() != 4)
		{
			tea_pdebug("func Hanlde_Kuafu_Enter data is %s, token.size() != 4", querys["data"].c_str());
			return;
		}

		uint32 room_id = atol(token[0].c_str());			//����id
		string battle_server_name = token[1];
		string host = token[2];
		string port = token[3];

		//�����У��Ķ���У������
		if(!m_player->GetFlags(PLAYER_APPD_INT_FIELD_FLAGS_FROM_KUAFU))
			m_player->SetFlags(PLAYER_APPD_INT_FIELD_FLAGS_FROM_KUAFU);			//�ѿ����־����
		
		//����ƥ����Ϣ���ɵ�¼��
		bool is_fcm = m_player->GetFCMLoginTime() != (-1);
		char other_temp[1024] = {0};
		//��Ϸ��server_name|�������|����id|�����ս����server_name
		sprintf(other_temp, "&backsvrname=%s&kuafutype=%d&warid=%u&battlesvrname=%s", 
				g_Config.server_name.c_str(), kuafu_type, room_id, battle_server_name.c_str());	
		string session_str = LogindApp::g_app->MakeSessionKey(m_player->GetAccount(),is_fcm, other_temp, WANNENG_LOGIN_KEY);	

		//֪ͨ�ͻ��˶Ͽ���Ϸ������pk��
		m_player->GetSession()->Call_World_War_CS_Player_Info(host, atoi(port.c_str()), session_str);
	}
}

