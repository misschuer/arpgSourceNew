#include "appd_app.h"
#include "appd_context.h"
#include "appd_object_manager.h"
#include "appd_script.h"

//��������ߣ���ӻ�������ȡ
inline AppdContext *GetPlayerObject(const string &guid)
{
	auto *p = AppdContext::FindPlayer(guid);
	return p;
}

int AppdApp::on_command_reload_scripts(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens)
{
	//��������ű�
	scripts_reload();
	return 0;
}

int AppdApp::on_command_reload_template(tcp_connection *conn, server_packet *,uint32 guid, uint32 connectid, Tokens& tokens)
{
	//�������δ�
	if(g_app->GetConfig().load_pingbi)
		g_app->LoadFuckPingbi(g_app->GetConfig().storage_path);
	
	if(LoadTemplate())
		COMMAND_SEND_SUCCEED;
	else
		SendCommandResult(conn, connectid, "load template error");
	return 0;
}

int AppdApp::on_command_add_item(tcp_connection *, server_packet *,uint32 guid, uint32, Tokens& tokens)
{
	return 0;
}

int AppdApp::on_command_top_start(tcp_connection *conn, server_packet *,uint32 guid, uint32 connectid, Tokens& tokens)
{
	//g_app->m_topMgr->EnforceStart();
	COMMAND_SEND_SUCCEED;
	return 0;
}
