#include <net/http.h>
#include <comm/b64.h>
#include <comm/crypt.h>
#include <object/OprateResult.h>
#include <object/SharedDef.h>
#include "policed_app.h"
#include "policed_mongodb.h"
#include "policed_mongo_log.h"
#include "log_file_operate.h"
#include "game_police.h"
#include "policed_context.h"

GamePolice::GamePolice() : m_lock_db_update_tm(0)
{

}

//��ʱ�����̨��Ϣ
void GamePolice::SaveHTInfo(TimerHolder& th)
{
	//����һ�������쳣����
	set<string> players;
	g_LOG.GetBasicInfoOnlinePlayer(players);
	for (auto it:players)
	{
		auto player = ObjMgr.FindPlayer(it);
		if(!player || player->GetStatus() != STATUS_LOGGEDIN)
		{
			tea_pdebug("GamePolice::SaveHTInfo update player %s offline", it.c_str());
			g_LOG.UpdateHTBasicOffline(it);
		}
	}
	//�����������
	ObjMgr.ForEachPlayer([](PolicedContext* player){
		g_LOG.SaveHTBasicInfo(player, player->GetStatus() == STATUS_LOGGEDIN);
		g_LOG.SaveHTDailyInfo(player);
	});
	th._next_time += 300;
}

//�������а���Ϣ
void GamePolice::SaveTopInfo(TimerHolder& th)
{
	g_LOG.SaveHTTopInfo();
	uint32 t = (uint32)time(NULL);
	//������һСʱ����ʱ���
	uint32 next_time = t - t % 3600 + 3600 + irand(0, 300);
	th._next_time = next_time;
}


