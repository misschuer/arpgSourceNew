#ifndef _APPD_LOCALDB_MANAGER_H_
#define _APPD_LOCALDB_MANAGER_H_
//Ӧ�÷������ļ����ݿ��װ
#include <svrcore/server/LocalFileDb.h>
#include <shared/storage_loader.h>

//#define MATCHING_INFO "matching_info"		//��ͽ��ɽƥ����Ϣ
//#define AUCTION_INFO "auction"				//��������Ϣ
//#define PVPDROP_INFO "pvpdrop"				//pvp������Ϣ
//#define GENERAL_INFO "general_lobby"		//�佫������Ϣ
//#define WHISHPER_INFO "whisper"				//˽���ļ�
//#define NEWAUCTION_INFO "newauction"		//�°���������Ϣ
//#define AUCTIONASKBUY_INFO "auctionaskbuy"	//�°���������Ϣ
//#define KUAFUAUCTION_INFO "kuafuauction"	//��������йҵ���Ϣ
//#define KUAFUAUCTION_ORDER_INFO "kuafuauction_order"	//��������ж�����Ϣ
//#define SLG_KUAFU_JJC_INFO "slg_kuafu_jjc_info"			//SLG�佫���������ս����Ϣ
#define RECHARGE_INFO "recharge_info"		//��ֵ��Ϣ
#define GIFTCODE_INFO "giftcode_info"		//�������Ϣ

#define SAVE_TIME 300000

class AppdLocaldbManager:public LocalFileDb
{	
public:
	AppdLocaldbManager(const string& dbpath);
	virtual ~AppdLocaldbManager();

	bool loadAll();
	void Update(uint32 diff);
	bool saveAll();

	//��ͽ��ɽƥ����Ϣ
	//bool LoadMatchingInfo();								//����ƥ����Ϣ
	//bool UpdateMatchingInfo(matching_info* info);			//����ƥ����Ϣ
	//bool UpdateMemMatchingInfo(Map &m);						//�����ڴ����ݿ�
	//bool SaveMatchingInfo();								//����ƥ����Ϣ
	//
	////�����нӿ�
	//bool LoadAuctionInfo();
	//bool InsertAuctionInfo(auction_template* info);
	//bool InsertAuctionDbInfo(Map &result);
	//bool DeleteAuctionInfo(auction_template* info);	
	//bool SaveAuctionInfo();	
	//void ToAuctionMap(const auction_template* info, Map& map);

	////�������нӿ�
	//bool LoadNewAuctionInfo();
	//bool InsertNewAuctionInfo(newauction_template* info);
	//bool InsertNewAuctionDbInfo(Map &result);
	//bool DeleteNewAuctionInfo(newauction_template* info);	
	//bool SaveNewAuctionInfo();
	//void ToNewAuctionMap(const newauction_template* info, Map& map);
	//void GetAuctionPostDataStr(string& str);
	//bool FromAuctionMergePostDataStr(const string& src_str);

	////��������йҵ��ӿ�
	//bool LoadKuaFuAuctionInfo();
	//bool InsertKuaFuAuctionInfo(kuafuauction_template* info);
	//bool InsertKuaFuAuctionDbInfo(Map &result);
	//bool UpdateKuaFuAuctionInfo(kuafuauction_template* info);
	//bool DeleteKuaFuAuctionInfo(kuafuauction_template* info);	
	//bool SaveKuaFuAuctionInfo();
	//void ToKuaFuAuctionMap(const kuafuauction_template* info, Map& map);
	//void GetKuaFuAuctionPostDataStr(string& str);
	//bool FromKuaFuAuctionMergePostDataStr(const string& src_str);

	////��������ж����ӿ�
	//bool LoadKuaFuAuctionOrderInfo();
	//bool InsertKuaFuAuctionOrderInfo(kuafuauction_template* info);
	//bool InsertKuaFuAuctionOrderDbInfo(Map &result);
	//bool UpdateKuaFuAuctionOrderInfo(kuafuauction_template* info);
	//bool DeleteKuaFuAuctionOrderInfo(kuafuauction_template* info);	
	//bool SaveKuaFuAuctionOrderInfo();
	//void GetKuaFuAuctionOrderPostDataStr(string& str);
	//bool FromKuaFuAuctionOrderMergePostDataStr(const string& src_str);


	////��������
	//bool LoadAuctionAskbuyInfo();
	//bool InsertAuctionAskbuyInfo(newauction_template* info);
	//bool InsertAuctionAskbuyDbInfo(Map &result);
	//bool DeleteAuctionAskbuyInfo(newauction_template* info);	
	//bool SaveAuctionAskbuyInfo();
	//void ToAuctionAskbuyMap(const newauction_template* info, Map& map);
	//void GetAuctionAskbuyPostDataStr(string& str);
	//bool FromAuctionAskbuyMergePostDataStr(const string& src_str);
	//void RepairEquipRandAttr();

	////pvp����ӿ�
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

	//˽�����
	//bool RemoveWhisper(const string& fname);
	//bool SaveWhisper(const string& fname, const string& content);
	//void ReadWhisper(const string&fname, std::function<bool(const string &)> fun);
	
	////slg�佫���������ս����Ϣ
	//bool LoadSlgKuafuJjcInfo();
	//bool InsertSlgKuafuJjcInfo(slg_kuafu_jjc_info* info);
	//bool InsertSlgKuafuJjcDbInfo(Map &result);
	//bool DeleteSlgKuafuJjcInfo(string &index);
	//bool SaveSlgKuafuJjcInfo();

	// ��ֵ��¼
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

	//�������¼
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
	//	//���binlog��־
	//	return AddBinlog(NEWAUCTION_INFO, OPT_TYPE_DEL, wheres);
	//}

	///������������Ϣ
	//bool AppdLocaldbManager::SaveNewAuctionInfo()


	//bool InsertPvpDropInfo(pvpdrop_template* info);
	//bool InsertPvpDropDbInfo(Map &result);
	//bool DeletePvpDropInfo(pvpdrop_template* info);
	//bool UpdatePvpDropInfo(pvpdrop_template* info);
	//bool SavePvpDropInfo();

	private:
		IntervalTimer m_save_timer;		//�洢��ʱ��
};
#endif
