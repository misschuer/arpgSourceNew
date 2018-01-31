#ifndef _APPD_LOCALDB_MANAGER_H_
#define _APPD_LOCALDB_MANAGER_H_
//应用服本地文件数据库封装
#include <svrcore/server/LocalFileDb.h>
#include <shared/storage_loader.h>

//#define MATCHING_INFO "matching_info"		//门徒矿山匹配信息
//#define AUCTION_INFO "auction"				//拍卖行信息
//#define PVPDROP_INFO "pvpdrop"				//pvp掉落信息
//#define GENERAL_INFO "general_lobby"		//武将大厅信息
//#define WHISHPER_INFO "whisper"				//私聊文件
//#define NEWAUCTION_INFO "newauction"		//新版拍卖行信息
//#define AUCTIONASKBUY_INFO "auctionaskbuy"	//新版拍卖行信息
//#define KUAFUAUCTION_INFO "kuafuauction"	//跨服拍卖行挂单信息
//#define KUAFUAUCTION_ORDER_INFO "kuafuauction_order"	//跨服拍卖行订单信息
//#define SLG_KUAFU_JJC_INFO "slg_kuafu_jjc_info"			//SLG武将跨服竞技场战报信息
#define RECHARGE_INFO "recharge_info"		//充值信息
#define GIFTCODE_INFO "giftcode_info"		//礼包码信息

#define SAVE_TIME 300000

class AppdLocaldbManager:public LocalFileDb
{	
public:
	AppdLocaldbManager(const string& dbpath);
	virtual ~AppdLocaldbManager();

	bool loadAll();
	void Update(uint32 diff);
	bool saveAll();

	//门徒矿山匹配信息
	//bool LoadMatchingInfo();								//加载匹配信息
	//bool UpdateMatchingInfo(matching_info* info);			//更新匹配信息
	//bool UpdateMemMatchingInfo(Map &m);						//更新内存数据库
	//bool SaveMatchingInfo();								//保存匹配信息
	//
	////拍卖行接口
	//bool LoadAuctionInfo();
	//bool InsertAuctionInfo(auction_template* info);
	//bool InsertAuctionDbInfo(Map &result);
	//bool DeleteAuctionInfo(auction_template* info);	
	//bool SaveAuctionInfo();	
	//void ToAuctionMap(const auction_template* info, Map& map);

	////新拍卖行接口
	//bool LoadNewAuctionInfo();
	//bool InsertNewAuctionInfo(newauction_template* info);
	//bool InsertNewAuctionDbInfo(Map &result);
	//bool DeleteNewAuctionInfo(newauction_template* info);	
	//bool SaveNewAuctionInfo();
	//void ToNewAuctionMap(const newauction_template* info, Map& map);
	//void GetAuctionPostDataStr(string& str);
	//bool FromAuctionMergePostDataStr(const string& src_str);

	////跨服拍卖行挂单接口
	//bool LoadKuaFuAuctionInfo();
	//bool InsertKuaFuAuctionInfo(kuafuauction_template* info);
	//bool InsertKuaFuAuctionDbInfo(Map &result);
	//bool UpdateKuaFuAuctionInfo(kuafuauction_template* info);
	//bool DeleteKuaFuAuctionInfo(kuafuauction_template* info);	
	//bool SaveKuaFuAuctionInfo();
	//void ToKuaFuAuctionMap(const kuafuauction_template* info, Map& map);
	//void GetKuaFuAuctionPostDataStr(string& str);
	//bool FromKuaFuAuctionMergePostDataStr(const string& src_str);

	////跨服拍卖行订单接口
	//bool LoadKuaFuAuctionOrderInfo();
	//bool InsertKuaFuAuctionOrderInfo(kuafuauction_template* info);
	//bool InsertKuaFuAuctionOrderDbInfo(Map &result);
	//bool UpdateKuaFuAuctionOrderInfo(kuafuauction_template* info);
	//bool DeleteKuaFuAuctionOrderInfo(kuafuauction_template* info);	
	//bool SaveKuaFuAuctionOrderInfo();
	//void GetKuaFuAuctionOrderPostDataStr(string& str);
	//bool FromKuaFuAuctionOrderMergePostDataStr(const string& src_str);


	////拍卖行求购
	//bool LoadAuctionAskbuyInfo();
	//bool InsertAuctionAskbuyInfo(newauction_template* info);
	//bool InsertAuctionAskbuyDbInfo(Map &result);
	//bool DeleteAuctionAskbuyInfo(newauction_template* info);	
	//bool SaveAuctionAskbuyInfo();
	//void ToAuctionAskbuyMap(const newauction_template* info, Map& map);
	//void GetAuctionAskbuyPostDataStr(string& str);
	//bool FromAuctionAskbuyMergePostDataStr(const string& src_str);
	//void RepairEquipRandAttr();

	////pvp掉落接口
	//bool LoadPvpDropInfo();
	//bool InsertPvpDropInfo(pvpdrop_template* info);
	//bool InsertPvpDropDbInfo(Map &result);
	//bool DeletePvpDropInfo(pvpdrop_template* info);
	//bool UpdatePvpDropInfo(pvpdrop_template* info);
	//bool SavePvpDropInfo();
	//void GetPvpDropPostDataStr(string& str);
	//bool FromPvpDropMergePostDataStr(const string& src_str);
	//void ToPvpDropMap(const pvpdrop_template* info, Map& map);
	//void RepairPvpLootRandAttr();

	//私聊相关
	//bool RemoveWhisper(const string& fname);
	//bool SaveWhisper(const string& fname, const string& content);
	//void ReadWhisper(const string&fname, std::function<bool(const string &)> fun);
	
	////slg武将跨服竞技场战报信息
	//bool LoadSlgKuafuJjcInfo();
	//bool InsertSlgKuafuJjcInfo(slg_kuafu_jjc_info* info);
	//bool InsertSlgKuafuJjcDbInfo(Map &result);
	//bool DeleteSlgKuafuJjcInfo(string &index);
	//bool SaveSlgKuafuJjcInfo();

	// 充值记录
	bool loadRechargeInfo();
	void ToRechargeMap(const recharge_info* info, Map& map);
	bool insertRechargeDbInfo(Map &result);
	void queryRechargeGuidByOrderId(string& orderid, string& guid);
	void queryRechargeAccountByOrderId(string& orderid, string& account, string& name, string& time);
	void queryRechargeNameAndPayTimeByUid(string& uid, string& guid, string& name, string& time);

	bool checkRechargeOrderIsDealed(string& orderid);
	bool checkRechargeUidIsDealed(string& uid);
	bool insertRechargeInfo(recharge_info* info);
	bool updateRechargeInfo(recharge_info* info);
	bool deleteRechargeInfo(recharge_info* info);
	bool SaveRechargeInfo();

	//礼物码记录
	bool loadGiftcodeInfo();
	void ToGiftcodeMap(const giftcode_info* info, Map& map);
	bool insertGiftcodeDbInfo(Map &result);
	bool checkGiftcodeIsUsed(string& giftcode);
	bool insertGiftcodeInfo(giftcode_info* info);
	bool SaveGiftcodeInfo();

	//{
	//	Map wheres;
	//	wheres["index"] = info->index;
	//	newauction_template_db.add_select_condition(MEMDB_EQ(newauction_template, index, wheres["index"].c_str()));
	//	MemDB_Result<newauction_template> result = newauction_template_db.select();	
	//	if (result.size() > 0)
	//		newauction_template_db.deleteDB(result[0]);
	//
	//	//添加binlog日志
	//	return AddBinlog(NEWAUCTION_INFO, OPT_TYPE_DEL, wheres);
	//}

	///保存拍卖行信息
	//bool AppdLocaldbManager::SaveNewAuctionInfo()


	//bool InsertPvpDropInfo(pvpdrop_template* info);
	//bool InsertPvpDropDbInfo(Map &result);
	//bool DeletePvpDropInfo(pvpdrop_template* info);
	//bool UpdatePvpDropInfo(pvpdrop_template* info);
	//bool SavePvpDropInfo();

	private:
		IntervalTimer m_save_timer;		//存储定时器
};
#endif
