#include "appd_localdb_manager.h"
#include <memdb/mem_db.h>
//#include "ItemManager.h"
#include "appd_script.h"

template<typename T>
void fromString(T& t,string v)
{
	std::stringstream ss;
	ss << v;
	ss >> t;
}
 
template<typename T>
string toString(T t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

AppdLocaldbManager::AppdLocaldbManager(const string& dbpath):LocalFileDb(dbpath)
{
	m_save_timer.SetInterval(SAVE_TIME);
}


AppdLocaldbManager::~AppdLocaldbManager()
{
}

bool AppdLocaldbManager::loadAll() {
	if (!this->loadRechargeInfo()) {
		return false;
	}

	if (!this->loadGiftcodeInfo()) {
		return false;
	}

	return true;
}

bool AppdLocaldbManager::saveAll() {
	if (!this->SaveRechargeInfo()) {
		return false;
	}

	if (!this->SaveGiftcodeInfo()) {
		return false;
	}

	return true;
}

void AppdLocaldbManager::Update(uint32 diff) {
	m_save_timer.Update(diff);
	if (m_save_timer.Passed()) {
		this->saveAll();
		m_save_timer.Reset2();
	}
}

//
////加载匹配信息
//bool AppdLocaldbManager::LoadMatchingInfo()
//{
//	Results results;
//	//先从data load
//	Load(MATCHING_INFO, results);
//	for (auto iter = results.begin(); iter != results.end(); ++iter)
//	{//把数据先放到内存数据库
//		Map &m = *iter;
//		if (m["s_guid"].empty())
//			continue;
//		UpdateMemMatchingInfo(m);
//	}
//
//	//从binlog中load	
//	ReadBinlog(MATCHING_INFO,[&](const OPT_TYPE opt_type, Map& m){
//		switch (opt_type)
//		{	
//			//匹配信息，入口只有update
//		case OPT_TYPE_UPDATE:
//			UpdateMemMatchingInfo(m);
//			break;
//		default:
//			break;
//		}	
//	});
//
//	return true;
//}
//
////更新匹配信息
//bool AppdLocaldbManager::UpdateMatchingInfo(matching_info* info)
//{
//	Map values;
//	values["s_guid"]			= info->s_guid;
//	values["i_player_lv"]		= toString(info->i_player_lv);
//	values["i_player_force"]	= toString((uint64)info->i_player_force);
//	values["i_station_lv"]		= toString(info->i_station_lv);
//	values["i_general_force"]	= toString(info->i_general_force);
//
//	if(values["s_guid"].empty())
//		return false;
//
//	//先添加binlog日志
//	if (AddBinlog(MATCHING_INFO, OPT_TYPE_UPDATE, values))
//	{
//		//更新内存数据库
//		UpdateMemMatchingInfo(values);
//		return true;
//	}
//
//	return false;
//}
//
////更新匹配信息
//bool AppdLocaldbManager::UpdateMemMatchingInfo(Map &m)
//{
//	//更新内存数据库
//	matching_info_db.add_select_condition(MEMDB_EQ(matching_info, s_guid, m["s_guid"].c_str()));
//	MemDB_Result<matching_info> result = matching_info_db.select();	
//	matching_info *info = nullptr;
//	if (result.size() <= 0)
//	{//插入		
//		info = new matching_info;
//		strncpy(info->s_guid, m["s_guid"].c_str(), 64);
//		matching_info_db.insertDB(info);
//	}
//	else
//	{
//		info = result[0];
//	}
//	if (!info)
//		return false;
//
//	fromString(info->i_player_lv, m["i_player_lv"]);
//	fromString(info->i_player_force, m["i_player_force"]);	
//	fromString(info->i_station_lv, m["i_station_lv"]);	
//	fromString(info->i_general_force, m["i_general_force"]);
//
//	return true;
//}
//
////保存匹配信息
//bool AppdLocaldbManager::SaveMatchingInfo()
//{
//	MemDB_Result<matching_info> result = matching_info_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		m["s_guid"]	= result[i]->s_guid;
//		m["i_player_lv"] = toString(result[i]->i_player_lv);
//		m["i_player_force"]	= toString((uint64)result[i]->i_player_force);	
//		m["i_station_lv"] = toString(result[i]->i_station_lv);
//		m["i_general_force"] = toString(result[i]->i_general_force);
//		values.push_back(m);
//	}
//
//	//保存成功后，重命名
//	if (!values.empty() && Save(MATCHING_INFO, values) && Rename(MATCHING_INFO))
//	{
//		//重命名成功后，删掉binlog文件
//		Remove(MATCHING_INFO);	
//	}
//
//	return true;
//}
//
////拍卖行接口
//bool AppdLocaldbManager::LoadAuctionInfo()
//{
//	Results load_result;
//	Load(AUCTION_INFO,load_result);
//	for (auto it = load_result.begin(); it != load_result.end(); ++it)
//		InsertAuctionDbInfo(*it);
//
//	//从binlog中load	
//	ReadBinlog(AUCTION_INFO,[&](const OPT_TYPE opt_type, Map& m){
//		switch (opt_type)
//		{
//		case OPT_TYPE_ADD:
//			{
//				InsertAuctionDbInfo(m);
//				break;
//			}
//		case OPT_TYPE_DEL:
//			{
//				//更新内存数据库
//				auction_template_db.add_select_condition(MEMDB_EQ(auction_template, s_index, m["s_index"].c_str()));
//				MemDB_Result<auction_template> result = auction_template_db.select();	
//				if (result.size() > 0)
//					auction_template_db.deleteDB(result[0]);
//				break;
//			}		
//		case OPT_TYPE_UPDATE:
//			{
//				//更新内存数据库
//				auction_template_db.add_select_condition(MEMDB_EQ(auction_template, s_index, m["s_index"].c_str()));
//				MemDB_Result<auction_template> result = auction_template_db.select();	
//				if (result.size() > 0)
//				{
//					fromString(result[0]->i_item_count, m["i_item_count"]);
//					fromString(result[0]->i_item_total_price, m["i_item_total_price"]);	
//					result[0]->s_item_ints = m["s_item_ints"];
//					result[0]->s_item_strs = m["s_item_strs"];
//				}
//				break;
//			}
//		default:
//			break;
//		}	
//	});
//
//	return true;
//}
//
//
//bool AppdLocaldbManager::LoadNewAuctionInfo()
//{
//	Results load_result;
//	Load(NEWAUCTION_INFO,load_result);
//	for (auto it = load_result.begin(); it != load_result.end(); ++it)
//		InsertNewAuctionDbInfo(*it);
//
//	//从binlog中load	
//	ReadBinlog(NEWAUCTION_INFO,[&](const OPT_TYPE opt_type, Map& m){
//		switch (opt_type)
//		{
//		case OPT_TYPE_ADD:
//			{
//				InsertNewAuctionDbInfo(m);
//				break;
//			}
//		case OPT_TYPE_DEL:
//			{
//				//更新内存数据库
//				newauction_template_db.add_select_condition(MEMDB_EQ(newauction_template, index, m["index"].c_str()));
//				MemDB_Result<newauction_template> result = newauction_template_db.select();	
//				if (result.size() > 0)
//					newauction_template_db.deleteDB(result[0]);
//				break;
//			}		
//		case OPT_TYPE_UPDATE:
//			{
//				//更新内存数据库
//				newauction_template_db.add_select_condition(MEMDB_EQ(newauction_template, index, m["index"].c_str()));
//				MemDB_Result<newauction_template> result = newauction_template_db.select();	
//				if (result.size() > 0)
//				{
//					fromString(result[0]->item_count, m["item_count"]);					
//					result[0]->item_ints = m["item_ints"];
//					result[0]->item_strs = m["item_strs"];
//				}
//				break;
//			}
//		default:
//			break;
//		}	
//	});
//
//	return true;
//}
//
//bool AppdLocaldbManager::InsertAuctionInfo(auction_template* info)
//{
//	Map values;
//	ToAuctionMap(info, values);
//	
//	//添加binlog日志
//	if (AddBinlog(AUCTION_INFO, OPT_TYPE_ADD, values))
//	{
//		InsertAuctionDbInfo(values);
//		return true;
//	}
//	return false;
//}
//
//bool AppdLocaldbManager::InsertNewAuctionInfo(newauction_template* info)
//{
//	Map values;
//	ToNewAuctionMap(info, values);
//
//	//添加binlog日志
//	if (AddBinlog(NEWAUCTION_INFO, OPT_TYPE_ADD, values))
//	{
//		InsertNewAuctionDbInfo(values);
//		return true;
//	}
//	return false;
//}
//
//bool AppdLocaldbManager::InsertAuctionDbInfo(Map &result)
//{
//	//插入之前查询是否已经有了，确保唯一
//	auction_template_db.add_select_condition(MEMDB_EQ(auction_template, s_index, result["s_index"].c_str()));
//	MemDB_Result<auction_template> results = auction_template_db.select();
//	if (results.size() > 0)
//		return false;
//
//	auction_template* info = new auction_template();
//	strncpy(info->s_index, result["s_index"].c_str(), 64);
//	fromString(info->i_create_time, result["i_create_time"]);	
//	fromString(info->i_return_time, result["i_return_time"]);
//	strncpy(info->s_seller_guid, result["s_seller_guid"].c_str(), 32);
//	info->s_seller_name = result["s_seller_name"];
//	info->s_item_guid = result["s_item_guid"];
//	fromString(info->i_item_id, result["i_item_id"]);
//	fromString(info->i_item_count, result["i_item_count"]);
//	fromString(info->i_item_single_price, result["i_item_single_price"]);
//	fromString(info->i_item_total_price, result["i_item_total_price"]);
//	fromString(info->i_item_type, result["i_item_type"]);
//	fromString(info->i_item_sub_type, result["i_item_sub_type"]);
//	fromString(info->i_item_quality, result["i_item_quality"]);
//	fromString(info->i_item_need_level, result["i_item_need_level"]);
//	fromString(info->i_auction_type, result["i_auction_type"]);
//	fromString(info->i_auction_sub_type, result["i_auction_sub_type"]);
//	info->s_item_ints = result["s_item_ints"];
//	info->s_item_strs = result["s_item_strs"];
//
//	auction_template_db.insertDB(info);
//
//	return true;
//}
//
//bool AppdLocaldbManager::InsertNewAuctionDbInfo(Map &result)
//{
//	//插入之前查询是否已经有了，确保唯一
//	newauction_template_db.add_select_condition(MEMDB_EQ(newauction_template, index, result["index"].c_str()));
//	MemDB_Result<newauction_template> results = newauction_template_db.select();
//	if (results.size() > 0)
//		return false;
//
//	newauction_template* info = new newauction_template();
//	strncpy(info->index, result["index"].c_str(), 64);
//	fromString(info->create_time, result["create_time"]);	
//	fromString(info->return_time, result["return_time"]);
//	strncpy(info->seller_guid, result["seller_guid"].c_str(), 50);
//	info->seller_name = result["seller_name"];	
//	strncpy(info->item_name, result["item_name"].c_str(), 64);
//	fromString(info->item_id, result["item_id"]);
//	fromString(info->item_count, result["item_count"]);
//	fromString(info->item_total_price, result["item_total_price"]);	
//	fromString(info->item_type, result["item_type"]);
//	fromString(info->item_sub_type, result["item_sub_type"]);
//	fromString(info->item_quality, result["item_quality"]);
//	fromString(info->item_need_level, result["item_need_level"]);
//	fromString(info->gender, result["gender"]);
//	fromString(info->menpai, result["menpai"]);
//	fromString(info->auction_type, result["auction_type"]);
//	fromString(info->auction_sub_type, result["auction_sub_type"]);
//	info->item_ints = result["item_ints"];
//	info->item_strs = result["item_strs"];
//	newauction_template_db.insertDB(info);
//
//	return true;
//}
//
//bool AppdLocaldbManager::DeleteAuctionInfo(auction_template* info)
//{
//	Map wheres;
//	wheres["s_index"] = info->s_index;
//	auction_template_db.add_select_condition(MEMDB_EQ(auction_template, s_index, wheres["s_index"].c_str()));
//	MemDB_Result<auction_template> result = auction_template_db.select();	
//	if (result.size() > 0)
//		auction_template_db.deleteDB(result[0]);
//
//	//添加binlog日志
//	return AddBinlog(AUCTION_INFO, OPT_TYPE_DEL, wheres);
//
//}
//
//bool AppdLocaldbManager::DeleteNewAuctionInfo(newauction_template* info)
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
//
////保存拍卖行信息
//bool AppdLocaldbManager::SaveAuctionInfo()
//{
//	MemDB_Result<auction_template> result = auction_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToAuctionMap(result[i], m);		
//		values.push_back(m);
//	}
//
//	//保存成功后，重命名
//	if (!values.empty() && Save(AUCTION_INFO, values) && Rename(AUCTION_INFO))
//	{
//		//重命名成功后，删掉binlog文件
//		Remove(AUCTION_INFO);	
//	}
//
//	return true;
//}
//
////保存拍卖行信息
//bool AppdLocaldbManager::SaveNewAuctionInfo()
//{
//	MemDB_Result<newauction_template> result = newauction_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToNewAuctionMap(result[i], m);		
//		values.push_back(m);
//	}
//
//	//保存成功后，重命名
//	if (!values.empty() && Save(NEWAUCTION_INFO, values) && Rename(NEWAUCTION_INFO))
//	{
//		//重命名成功后，删掉binlog文件
//		Remove(NEWAUCTION_INFO);	
//	}
//
//	return true;
//}
//
//void AppdLocaldbManager::GetAuctionPostDataStr(string& str)
//{
//	//先获得keymap串
//	GetKeyMapStr(NEWAUCTION_INFO, str);
//	if (str.empty())
//	{
//		tea_perror("GetAuctionPostDataStr:get keymap empty!");
//		return;
//	}
//	//再获得具体数据
//	MemDB_Result<newauction_template> result = newauction_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		string index = result[i]->index;
//		if (strstr(index.c_str(),"robotd") )
//		{
//			continue;
//		}
//		
//		Map m;
//		ToNewAuctionMap(result[i], m);
//		values.push_back(m);
//	}
//
//	string map_str;
//	ToMapString(NEWAUCTION_INFO, values, map_str);
//	if (map_str.empty())
//		str.clear();
//	else
//		str += MERGE_DATA_SEPARATOR + map_str;	//用合服分割串连接
//}
//
//bool AppdLocaldbManager::FromAuctionMergePostDataStr(const string& src_str)
//{
//	if (src_str.empty()) return false;
//
//	Tokens src_token;
//	StrSplit(src_token, src_str, MERGE_DATA_SEPARATOR);
//	
//	if (src_token.size() < 2)
//		return false;		//大小不对
//
//	Values values;
//	FromMapString(src_token.at(0), src_token.at(1), values);
//	for (auto iter = values.begin(); iter != values.end(); ++iter)
//		InsertNewAuctionDbInfo(*iter);
//	//保存到本地文件库,ps:这里如果要万无一失得存下日志
//	SaveNewAuctionInfo();
//
//	return true;
//}


//void AppdLocaldbManager::ToAuctionMap(const auction_template* info, Map& map)
//{
//	map["s_index"]				= info->s_index;
//	map["i_create_time"]		= toString(info->i_create_time);
//	map["i_return_time"]		= toString(info->i_return_time);
//	map["s_seller_guid"]		= info->s_seller_guid;
//	map["s_seller_name"]		= info->s_seller_name;
//	map["s_item_guid"]			= info->s_item_guid;
//	map["i_item_id"]			= toString(info->i_item_id);
//	map["i_item_count"]			= toString(info->i_item_count);
//	map["i_item_single_price"]	= toString(info->i_item_single_price);
//	map["i_item_total_price"]	= toString(info->i_item_total_price);
//	map["i_item_type"]			= toString(info->i_item_type);
//	map["i_item_sub_type"]		= toString(info->i_item_sub_type);
//	map["i_item_quality"]		= toString(info->i_item_quality);
//	map["i_item_need_level"]	= toString(info->i_item_need_level);
//	map["i_auction_type"]		= toString(info->i_auction_type);
//	map["i_auction_sub_type"]	= toString(info->i_auction_sub_type);
//	map["s_item_ints"]			= info->s_item_ints;
//	map["s_item_strs"]			= info->s_item_strs;	
//}
//
//void AppdLocaldbManager::ToNewAuctionMap(const newauction_template* info, Map& map)
//{
//	map["index"]				= info->index;
//	map["create_time"]			= toString(info->create_time);
//	map["return_time"]			= toString(info->return_time);
//	map["seller_guid"]			= info->seller_guid;
//	map["seller_name"]			= info->seller_name;
//	map["item_name"]			= info->item_name;
//	map["item_id"]				= toString(info->item_id);
//	map["item_count"]			= toString(info->item_count);
//	map["item_total_price"]		= toString(info->item_total_price);	
//	map["item_type"]			= toString(info->item_type);
//	map["item_sub_type"]		= toString(info->item_sub_type);
//	map["item_quality"]			= toString(info->item_quality);
//	map["item_need_level"]		= toString(info->item_need_level);
//	map["gender"]				= toString(info->gender);
//	map["menpai"]				= toString(info->menpai);
//	map["auction_type"]			= toString(info->auction_type);
//	map["auction_sub_type"]		= toString(info->auction_sub_type);
//	map["item_ints"]			= info->item_ints;
//	map["item_strs"]			= info->item_strs;	
//}
//
////跨服拍卖行接口
//bool AppdLocaldbManager::LoadKuaFuAuctionInfo()
//{
//	Results load_result;
//	Load(KUAFUAUCTION_INFO,load_result);
//	for (auto it = load_result.begin(); it != load_result.end(); ++it)
//		InsertKuaFuAuctionDbInfo(*it);
//
//	//从binlog中load	
//	ReadBinlog(KUAFUAUCTION_INFO,[&](const OPT_TYPE opt_type, Map& m){
//		switch (opt_type)
//		{
//		case OPT_TYPE_ADD:
//			{
//				InsertKuaFuAuctionDbInfo(m);
//				break;
//			}
//		case OPT_TYPE_DEL:
//			{
//				//更新内存数据库
//				kuafuauction_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, m["index"].c_str()));
//				MemDB_Result<kuafuauction_template> result = kuafuauction_template_db.select();	
//				if (result.size() > 0)
//					kuafuauction_template_db.deleteDB(result[0]);
//				break;
//			}		
//		case OPT_TYPE_UPDATE:
//			{
//				//更新内存数据库
//				kuafuauction_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, m["index"].c_str()));
//				MemDB_Result<kuafuauction_template> result = kuafuauction_template_db.select();	
//				if (result.size() > 0)
//				{
//					fromString(result[0]->status, m["status"]);
//					fromString(result[0]->close_status, m["close_status"]);
//					result[0]->buyer_guid = m["buyer_guid"];
//					result[0]->buyer_name = m["buyer_name"];
//				}
//				break;
//			}
//		default:
//			break;
//		}	
//	});
//
//	return true;
//}
//bool AppdLocaldbManager::InsertKuaFuAuctionInfo(kuafuauction_template* info)
//{
//	Map values;
//	ToKuaFuAuctionMap(info, values);
//
//	//添加binlog日志
//	if (AddBinlog(KUAFUAUCTION_INFO, OPT_TYPE_ADD, values))
//	{
//		InsertKuaFuAuctionDbInfo(values);
//		return true;
//	}
//	return false;
//}
//bool AppdLocaldbManager::InsertKuaFuAuctionDbInfo(Map &result)
//{
//	//插入之前查询是否已经有了，确保唯一
//	kuafuauction_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, result["index"].c_str()));
//	MemDB_Result<kuafuauction_template> results = kuafuauction_template_db.select();
//	if (results.size() > 0)
//		return false;
//
//	kuafuauction_template* info = new kuafuauction_template();
//	strncpy(info->index, result["index"].c_str(), 64);
//	fromString(info->create_time, result["create_time"]);	
//	fromString(info->return_time, result["return_time"]);
//	strncpy(info->seller_guid, result["seller_guid"].c_str(), 64);
//	info->seller_name = result["seller_name"];	
//	strncpy(info->item_name, result["item_name"].c_str(), 64);
//	fromString(info->item_id, result["item_id"]);
//	fromString(info->item_count, result["item_count"]);
//	fromString(info->item_total_price, result["item_total_price"]);	
//	fromString(info->item_type, result["item_type"]);
//	fromString(info->item_sub_type, result["item_sub_type"]);
//	fromString(info->item_quality, result["item_quality"]);
//	fromString(info->item_need_level, result["item_need_level"]);
//	fromString(info->gender, result["gender"]);
//	fromString(info->menpai, result["menpai"]);
//	fromString(info->auction_type, result["auction_type"]);
//	fromString(info->auction_sub_type, result["auction_sub_type"]);
//	info->item_ints = result["item_ints"];
//	info->item_strs = result["item_strs"];
//	info->buyer_guid = result["buyer_guid"];
//	info->buyer_name = result["buyer_name"];
//	fromString(info->status, result["status"]);
//	info->server_name = result["server_name"];
//	fromString(info->server_group, result["server_group"]);
//	fromString(info->last_oper_time, result["last_oper_time"]);
//	fromString(info->close_status, result["close_status"]);
//	kuafuauction_template_db.insertDB(info);
//
//	return true;
//}
//
//bool AppdLocaldbManager::UpdateKuaFuAuctionInfo(kuafuauction_template* info)
//{
//	Map values;
//	values["index"] = info->index;
//	values["buyer_guid"] = info->buyer_guid;
//	values["buyer_name"] = info->buyer_name;
//	values["status"] = toString(info->status);
//	values["close_status"] = toString(info->close_status);
//	//先添加binlog日志
//	if (AddBinlog(KUAFUAUCTION_INFO, OPT_TYPE_UPDATE, values))
//	{
//		//更新内存数据库
//		kuafuauction_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, values["index"].c_str()));
//		MemDB_Result<kuafuauction_template> result = kuafuauction_template_db.select();	
//		if (result.size() > 0)
//		{
//			result[0]->status = info->status;
//			result[0]->close_status = info->close_status;
//			result[0]->buyer_guid = info->buyer_guid;
//			result[0]->buyer_name = info->buyer_name;
//		}
//		return true;
//	}
//	return false;
//}
//
//bool AppdLocaldbManager::DeleteKuaFuAuctionInfo(kuafuauction_template* info)
//{
//	Map wheres;
//	wheres["index"] = info->index;
//	kuafuauction_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, wheres["index"].c_str()));
//	MemDB_Result<kuafuauction_template> result = kuafuauction_template_db.select();	
//	if (result.size() > 0)
//	{
//		kuafuauction_template_db.deleteDB(result[0]);
//		AddBinlog(KUAFUAUCTION_INFO, OPT_TYPE_DEL, wheres);
//		return true;
//	}
//
//	//添加binlog日志
//	return false;
//}
//bool AppdLocaldbManager::SaveKuaFuAuctionInfo()
//{
//	MemDB_Result<kuafuauction_template> result = kuafuauction_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToKuaFuAuctionMap(result[i], m);		
//		values.push_back(m);
//	}
//
//	//保存成功后，重命名
//	if (!values.empty() && Save(KUAFUAUCTION_INFO, values) && Rename(KUAFUAUCTION_INFO))
//	{
//		//重命名成功后，删掉binlog文件
//		Remove(KUAFUAUCTION_INFO);	
//	}
//
//	return true;
//}
//void AppdLocaldbManager::ToKuaFuAuctionMap(const kuafuauction_template* info, Map& map)
//{
//	map["index"]				= info->index;
//	map["create_time"]			= toString(info->create_time);
//	map["return_time"]			= toString(info->return_time);
//	map["seller_guid"]			= info->seller_guid;
//	map["seller_name"]			= info->seller_name;
//	map["item_name"]			= info->item_name;
//	map["item_id"]				= toString(info->item_id);
//	map["item_count"]			= toString(info->item_count);
//	map["item_total_price"]		= toString(info->item_total_price);	
//	map["item_type"]			= toString(info->item_type);
//	map["item_sub_type"]		= toString(info->item_sub_type);
//	map["item_quality"]			= toString(info->item_quality);
//	map["item_need_level"]		= toString(info->item_need_level);
//	map["gender"]				= toString(info->gender);
//	map["menpai"]				= toString(info->menpai);
//	map["auction_type"]			= toString(info->auction_type);
//	map["auction_sub_type"]		= toString(info->auction_sub_type);
//	map["item_ints"]			= info->item_ints;
//	map["item_strs"]			= info->item_strs;	
//	map["buyer_guid"]			= info->buyer_guid;	
//	map["buyer_name"]			= info->buyer_name;	
//	map["status"]				= toString(info->status);
//	map["server_name"]			= info->server_name;
//	map["server_group"]			= toString(info->server_group);	
//	map["last_oper_time"]		= toString(info->last_oper_time);
//	map["close_status"]			= toString(info->close_status);
//
//}
//void AppdLocaldbManager::GetKuaFuAuctionPostDataStr(string& str)
//{
//	//先获得keymap串
//	GetKeyMapStr(KUAFUAUCTION_INFO, str);
//	if (str.empty())
//	{
//		tea_perror("GetKuaFuAuctionPostDataStr:get keymap empty!");
//		return;
//	}
//	//再获得具体数据
//	MemDB_Result<kuafuauction_template> result = kuafuauction_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToKuaFuAuctionMap(result[i], m);
//		values.push_back(m);
//	}
//
//	string map_str;
//	ToMapString(KUAFUAUCTION_INFO, values, map_str);
//	if (map_str.empty())
//		str.clear();
//	else
//		str += MERGE_DATA_SEPARATOR + map_str;	//用合服分割串连接
//}
//bool AppdLocaldbManager::FromKuaFuAuctionMergePostDataStr(const string& src_str)
//{
//	if (src_str.empty()) return false;
//
//	Tokens src_token;
//	StrSplit(src_token, src_str, MERGE_DATA_SEPARATOR);
//
//	if (src_token.size() < 2)
//		return false;		//大小不对
//
//	Values values;
//	FromMapString(src_token.at(0), src_token.at(1), values);
//	for (auto iter = values.begin(); iter != values.end(); ++iter)
//		InsertKuaFuAuctionDbInfo(*iter);
//	//保存到本地文件库,ps:这里如果要万无一失得存下日志
//	SaveKuaFuAuctionInfo();
//
//	return true;
//}
//
//
////跨服拍卖行订单接口
//bool AppdLocaldbManager::LoadKuaFuAuctionOrderInfo()
//{
//	Results load_result;
//	Load(KUAFUAUCTION_ORDER_INFO,load_result);
//	for (auto it = load_result.begin(); it != load_result.end(); ++it)
//		InsertKuaFuAuctionOrderDbInfo(*it);
//
//	//从binlog中load	
//	ReadBinlog(KUAFUAUCTION_ORDER_INFO,[&](const OPT_TYPE opt_type, Map& m){
//		switch (opt_type)
//		{
//		case OPT_TYPE_ADD:
//			{
//				InsertKuaFuAuctionOrderDbInfo(m);
//				break;
//			}
//		case OPT_TYPE_DEL:
//			{
//				//更新内存数据库
//				kuafuauction_order_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, m["index"].c_str()));
//				MemDB_Result<kuafuauction_template> result = kuafuauction_order_template_db.select();	
//				if (result.size() > 0)
//					kuafuauction_order_template_db.deleteDB(result[0]);
//				break;
//			}		
//		case OPT_TYPE_UPDATE:
//			{
//				//更新内存数据库
//				kuafuauction_order_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, m["index"].c_str()));
//				MemDB_Result<kuafuauction_template> result = kuafuauction_order_template_db.select();	
//				if (result.size() > 0)
//				{
//					fromString(result[0]->status, m["status"]);
//				}
//				break;
//			}
//		default:
//			break;
//		}	
//	});
//
//	return true;
//}
//bool AppdLocaldbManager::InsertKuaFuAuctionOrderInfo(kuafuauction_template* info)
//{
//	Map values;
//	ToKuaFuAuctionMap(info, values);
//
//	//添加binlog日志
//	if (AddBinlog(KUAFUAUCTION_ORDER_INFO, OPT_TYPE_ADD, values))
//	{
//		InsertKuaFuAuctionOrderDbInfo(values);
//		return true;
//	}
//	return false;
//}
//bool AppdLocaldbManager::InsertKuaFuAuctionOrderDbInfo(Map &result)
//{
//	//插入之前查询是否已经有了，确保唯一
//	kuafuauction_order_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, result["index"].c_str()));
//	MemDB_Result<kuafuauction_template> results = kuafuauction_order_template_db.select();
//	if (results.size() > 0)
//		return false;
//
//	kuafuauction_template* info = new kuafuauction_template();
//	strncpy(info->index, result["index"].c_str(), 64);
//	fromString(info->create_time, result["create_time"]);	
//	fromString(info->return_time, result["return_time"]);
//	strncpy(info->seller_guid, result["seller_guid"].c_str(), 64);
//	info->seller_name = result["seller_name"];	
//	strncpy(info->item_name, result["item_name"].c_str(), 64);
//	fromString(info->item_id, result["item_id"]);
//	fromString(info->item_count, result["item_count"]);
//	fromString(info->item_total_price, result["item_total_price"]);	
//	fromString(info->item_type, result["item_type"]);
//	fromString(info->item_sub_type, result["item_sub_type"]);
//	fromString(info->item_quality, result["item_quality"]);
//	fromString(info->item_need_level, result["item_need_level"]);
//	fromString(info->gender, result["gender"]);
//	fromString(info->menpai, result["menpai"]);
//	fromString(info->auction_type, result["auction_type"]);
//	fromString(info->auction_sub_type, result["auction_sub_type"]);
//	info->item_ints = result["item_ints"];
//	info->item_strs = result["item_strs"];
//	info->buyer_guid = result["buyer_guid"];
//	info->buyer_name = result["buyer_name"];
//	fromString(info->status, result["status"]);
//	info->server_name = result["server_name"];
//	fromString(info->server_group, result["server_group"]);
//	fromString(info->last_oper_time, result["last_oper_time"]);
//	fromString(info->close_status, result["close_status"]);
//	kuafuauction_order_template_db.insertDB(info);
//
//	return true;
//}
//
//bool AppdLocaldbManager::UpdateKuaFuAuctionOrderInfo(kuafuauction_template* info)
//{
//	Map values;
//	values["index"] = info->index;
//	values["status"] = toString(info->status);
//
//	//先添加binlog日志
//	if (AddBinlog(KUAFUAUCTION_ORDER_INFO, OPT_TYPE_UPDATE, values))
//	{
//		//更新内存数据库
//		kuafuauction_order_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, values["index"].c_str()));
//		MemDB_Result<kuafuauction_template> result = kuafuauction_order_template_db.select();	
//		if (result.size() > 0)
//		{
//			result[0]->status = info->status;
//		}
//		return true;
//	}
//	return false;
//}
//
//bool AppdLocaldbManager::DeleteKuaFuAuctionOrderInfo(kuafuauction_template* info)
//{
//	Map wheres;
//	wheres["index"] = info->index;
//	kuafuauction_order_template_db.add_select_condition(MEMDB_EQ(kuafuauction_template, index, wheres["index"].c_str()));
//	MemDB_Result<kuafuauction_template> result = kuafuauction_order_template_db.select();	
//	if (result.size() > 0)
//	{
//		kuafuauction_order_template_db.deleteDB(result[0]);
//		//添加binlog日志
//		return AddBinlog(KUAFUAUCTION_ORDER_INFO, OPT_TYPE_DEL, wheres);
//	}
//
//	return false;
//}
//bool AppdLocaldbManager::SaveKuaFuAuctionOrderInfo()
//{
//	MemDB_Result<kuafuauction_template> result = kuafuauction_order_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToKuaFuAuctionMap(result[i], m);		
//		values.push_back(m);
//	}
//
//	//保存成功后，重命名
//	if (!values.empty() && Save(KUAFUAUCTION_ORDER_INFO, values) && Rename(KUAFUAUCTION_ORDER_INFO))
//	{
//		//重命名成功后，删掉binlog文件
//		Remove(KUAFUAUCTION_ORDER_INFO);	
//	}
//
//	return true;
//}
//
//void AppdLocaldbManager::GetKuaFuAuctionOrderPostDataStr(string& str)
//{
//	//先获得keymap串
//	GetKeyMapStr(KUAFUAUCTION_ORDER_INFO, str);
//	if (str.empty())
//	{
//		tea_perror("GetKuaFuAuctionOrderPostDataStr:get keymap empty!");
//		return;
//	}
//	//再获得具体数据
//	MemDB_Result<kuafuauction_template> result = kuafuauction_order_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToKuaFuAuctionMap(result[i], m);
//		values.push_back(m);
//	}
//
//	string map_str;
//	ToMapString(KUAFUAUCTION_ORDER_INFO, values, map_str);
//	if (map_str.empty())
//		str.clear();
//	else
//		str += MERGE_DATA_SEPARATOR + map_str;	//用合服分割串连接
//}
//bool AppdLocaldbManager::FromKuaFuAuctionOrderMergePostDataStr(const string& src_str)
//{
//	if (src_str.empty()) return false;
//
//	Tokens src_token;
//	StrSplit(src_token, src_str, MERGE_DATA_SEPARATOR);
//
//	if (src_token.size() < 2)
//		return false;		//大小不对
//
//	Values values;
//	FromMapString(src_token.at(0), src_token.at(1), values);
//	for (auto iter = values.begin(); iter != values.end(); ++iter)
//		InsertKuaFuAuctionOrderDbInfo(*iter);
//	//保存到本地文件库,ps:这里如果要万无一失得存下日志
//	SaveKuaFuAuctionOrderInfo();
//
//	return true;
//}
//
//
////pvp掉落接口
//bool AppdLocaldbManager::LoadPvpDropInfo()
//{
//	Results load_result;
//	Load(PVPDROP_INFO,load_result);
//	for (auto it = load_result.begin(); it != load_result.end(); ++it)
//		InsertPvpDropDbInfo(*it);
//	
//	//从binlog中load	
//	ReadBinlog(PVPDROP_INFO,[&](const OPT_TYPE opt_type, Map& m){
//		switch (opt_type)
//		{
//		case OPT_TYPE_ADD:
//			{
//				InsertPvpDropDbInfo(m);
//				break;
//			}
//		case OPT_TYPE_DEL:
//			{
//				//更新内存数据库
//				pvpdrop_template_db.add_select_condition(MEMDB_EQ(pvpdrop_template, s_item_guid, m["s_item_guid"].c_str()));
//				MemDB_Result<pvpdrop_template> result = pvpdrop_template_db.select();	
//				if (result.size() > 0)
//					pvpdrop_template_db.deleteDB(result[0]);
//				break;
//			}			
//		case OPT_TYPE_UPDATE:
//			{
//				//更新内存数据库
//				pvpdrop_template_db.add_select_condition(MEMDB_EQ(pvpdrop_template, s_item_guid, m["s_item_guid"].c_str()));
//				MemDB_Result<pvpdrop_template> result = pvpdrop_template_db.select();	
//				if (result.size() > 0)
//				{
//					strncpy(result[0]->s_picker_guid, m["s_picker_guid"].c_str(), 64);
//					result[0]->s_picker_name = m["s_picker_name"];	
//				}
//				break;
//			}
//		default:
//			break;
//		}	
//	});
//	return true;
//}
//
//bool AppdLocaldbManager::InsertPvpDropInfo(pvpdrop_template* info)
//{
//	Map values;
//	ToPvpDropMap(info, values);
//
//	//添加binlog日志
//	if (AddBinlog(PVPDROP_INFO, OPT_TYPE_ADD, values))
//	{
//		InsertPvpDropDbInfo(values);
//		return true;
//	}
//	return false;
//}
//
//bool AppdLocaldbManager::InsertPvpDropDbInfo(Map &result)
//{
//	pvpdrop_template_db.add_select_condition(MEMDB_EQ(pvpdrop_template, s_item_guid, result["s_item_guid"].c_str()));
//	MemDB_Result<pvpdrop_template> results = pvpdrop_template_db.select();	
//	if (results.size() > 0)
//		return false;
//
//	pvpdrop_template* info = new pvpdrop_template();
//	fromString(info->i_redeem_time, result["i_redeem_time"]);
//	fromString(info->i_create_time, result["i_create_time"]);
//	fromString(info->i_item_id, result["i_item_id"]);
//	fromString(info->i_redeem_gold, result["i_redeem_gold"]);
//	strncpy(info->s_item_guid, result["s_item_guid"].c_str(), 64);
//	info->s_item_name = result["s_item_name"];
//	fromString(info->i_item_icon, result["i_item_icon"]);
//	fromString(info->i_item_count, result["i_item_count"]);
//	strncpy(info->s_droper_guid, result["s_droper_guid"].c_str(), 64);
//	info->s_droper_name = result["s_droper_name"];
//	strncpy(info->s_picker_guid, result["s_picker_guid"].c_str(), 64);
//	info->s_picker_name = result["s_picker_name"];			
//	info->s_killer_guid = result["s_killer_guid"];
//	info->s_killer_name = result["s_killer_name"];
//	info->s_item_ints = result["s_item_ints"];
//	info->s_item_strs = result["s_item_strs"];
//	fromString(info->i_lev_cnt, result["i_lev_cnt"]);
//
//	pvpdrop_template_db.insertDB(info);
//
//	return true;
//}
//
//bool AppdLocaldbManager::DeletePvpDropInfo(pvpdrop_template* info)
//{
//	Map wheres;
//	wheres["s_item_guid"] = info->s_item_guid;
//
//	pvpdrop_template_db.add_select_condition(MEMDB_EQ(pvpdrop_template, s_item_guid, wheres["s_item_guid"].c_str()));
//	MemDB_Result<pvpdrop_template> result = pvpdrop_template_db.select();	
//	if (result.size() > 0)
//	{
//		pvpdrop_template_db.deleteDB(result[0]);
//		AddBinlog(PVPDROP_INFO, OPT_TYPE_DEL, wheres);
//		return true;
//	}
//
//	//添加binlog日志
//	return false;
//}
//
//bool AppdLocaldbManager::UpdatePvpDropInfo(pvpdrop_template* info)
//{
//	Map values;
//	values["s_item_guid"] = info->s_item_guid;
//	values["s_picker_guid"] = info->s_picker_guid;
//	values["s_picker_name"] = info->s_picker_name;
//
//	//先添加binlog日志
//	if (AddBinlog(PVPDROP_INFO, OPT_TYPE_UPDATE, values))
//	{
//		//更新内存数据库
//		pvpdrop_template_db.add_select_condition(MEMDB_EQ(pvpdrop_template, s_item_guid, values["s_item_guid"].c_str()));
//		MemDB_Result<pvpdrop_template> result = pvpdrop_template_db.select();	
//		if (result.size() > 0)
//		{
//			strncpy(result[0]->s_picker_guid, info->s_picker_guid, 64);
//			result[0]->s_picker_name = info->s_picker_name;
//		}
//		return true;
//	}
//	return false;
//}
//
//bool AppdLocaldbManager::SavePvpDropInfo()
//{
//	MemDB_Result<pvpdrop_template> result = pvpdrop_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToPvpDropMap(result[i], m);
//		values.push_back(m);
//	}
//
//	//保存成功后，重命名
//	if (!values.empty() && Save(PVPDROP_INFO, values) && Rename(PVPDROP_INFO))
//	{
//		//重命名成功后，删掉binlog文件
//		Remove(PVPDROP_INFO);
//	}
//	return true;
//}
//
//void AppdLocaldbManager::GetPvpDropPostDataStr(string& str)
//{
//	//先获得keymap串
//	GetKeyMapStr(PVPDROP_INFO, str);
//	if (str.empty())
//	{
//		tea_perror("GetPvpDropPostDataStr:get keymap empty!");
//		return;
//	}
//	//再获得具体数据
//	MemDB_Result<pvpdrop_template> result = pvpdrop_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToPvpDropMap(result[i], m);
//		values.push_back(m);
//	}
//	string map_str;
//	ToMapString(PVPDROP_INFO, values, map_str);
//	if (map_str.empty())
//		str.clear();
//	else
//		str += MERGE_DATA_SEPARATOR + map_str;	//用合服分割串连接
//}
//
//bool AppdLocaldbManager::FromPvpDropMergePostDataStr(const string& src_str)
//{
//	if (src_str.empty()) return false;
//
//	Tokens src_token;
//	StrSplit(src_token, src_str, MERGE_DATA_SEPARATOR);
//
//	if (src_token.size() < 2)
//		return false;		//大小不对
//
//	Values values;
//	FromMapString(src_token.at(0), src_token.at(1), values);
//	for (auto iter = values.begin(); iter != values.end(); ++iter)
//		InsertPvpDropDbInfo(*iter);
//	//保存到本地文件库
//	SavePvpDropInfo();
//	return true;
//}
//
//void AppdLocaldbManager::ToPvpDropMap(const pvpdrop_template* info, Map& map)
//{
//	map["i_redeem_time"]			= toString(info->i_redeem_time);
//	map["i_create_time"]			= toString(info->i_create_time);
//	map["i_item_id"]				= toString(info->i_item_id);
//	map["i_redeem_gold"]			= toString(info->i_redeem_gold);
//	map["s_item_guid"]				= info->s_item_guid;
//	map["s_item_name"]				= info->s_item_name;
//	map["i_item_icon"]				= toString(info->i_item_icon);	
//	map["i_item_count"]				= toString(info->i_item_count);	
//	map["s_droper_guid"]			= info->s_droper_guid;
//	map["s_droper_name"]			= info->s_droper_name;
//	map["s_picker_guid"]			= info->s_picker_guid;
//	map["s_picker_name"]			= info->s_picker_name;				
//	map["s_killer_guid"]			= info->s_killer_guid;
//	map["s_killer_name"]			= info->s_killer_name;
//	map["s_item_ints"]				= info->s_item_ints;
//	map["s_item_strs"]				= info->s_item_strs;	
//	map["i_lev_cnt"]				= toString(info->i_lev_cnt);
//}
//
////私聊相关
//bool AppdLocaldbManager::RemoveWhisper(const string& fname)
//{
//	 return GetStorage()->Remove(GetWhisperDataFN(fname));
//}
//
//bool AppdLocaldbManager::SaveWhisper(const string& fname, const string& content)
//{
//	return GetStorage()->SaveFile(GetWhisperDataFN(fname), content);
//}
//
//void AppdLocaldbManager::ReadWhisper(const string&fname, std::function<bool(const string &)> fun)
//{
//	GetStorage()->ReadFile(GetWhisperDataFN(fname), fun);
//}
//
//bool AppdLocaldbManager::LoadAuctionAskbuyInfo()
//{
//	Results load_result;
//	Load(AUCTIONASKBUY_INFO,load_result);
//	for (auto it = load_result.begin(); it != load_result.end(); ++it)
//		InsertAuctionAskbuyDbInfo(*it);
//
//	//从binlog中load	
//	ReadBinlog(AUCTIONASKBUY_INFO,[&](const OPT_TYPE opt_type, Map& m){
//		switch (opt_type)
//		{
//		case OPT_TYPE_ADD:
//			{
//				InsertAuctionAskbuyDbInfo(m);
//				break;
//			}
//		case OPT_TYPE_DEL:
//			{
//				//更新内存数据库
//				auction_askbuy_template_db.add_select_condition(MEMDB_EQ(newauction_template, index, m["index"].c_str()));
//				MemDB_Result<newauction_template> result = auction_askbuy_template_db.select();	
//				if (result.size() > 0)
//					auction_askbuy_template_db.deleteDB(result[0]);
//				break;
//			}		
//		case OPT_TYPE_UPDATE:
//			{
//				//更新内存数据库
//				auction_askbuy_template_db.add_select_condition(MEMDB_EQ(newauction_template, index, m["index"].c_str()));
//				MemDB_Result<newauction_template> result = auction_askbuy_template_db.select();	
//				if (result.size() > 0)
//				{
//					fromString(result[0]->item_count, m["item_count"]);
//					fromString(result[0]->item_total_price, m["item_total_price"]);	
//				}
//				break;
//			}
//		default:
//			break;
//		}	
//	});
//
//	return true;
//}
//
//bool AppdLocaldbManager::InsertAuctionAskbuyInfo(newauction_template* info)
//{
//	Map values;
//	ToAuctionAskbuyMap(info, values);
//
//	//添加binlog日志
//	if (AddBinlog(AUCTIONASKBUY_INFO, OPT_TYPE_ADD, values))
//	{
//		InsertAuctionAskbuyDbInfo(values);
//		return true;
//	}
//	return false;
//}
//
//bool AppdLocaldbManager::InsertAuctionAskbuyDbInfo(Map &result)
//{
//	//插入之前查询是否已经有了，确保唯一
//	auction_askbuy_template_db.add_select_condition(MEMDB_EQ(newauction_template, index, result["index"].c_str()));
//	MemDB_Result<newauction_template> results = auction_askbuy_template_db.select();
//	if (results.size() > 0)
//		return false;
//
//	newauction_template* info = new newauction_template();
//	strncpy(info->index, result["index"].c_str(), 64);
//	fromString(info->create_time, result["create_time"]);	
//	fromString(info->return_time, result["return_time"]);
//	strncpy(info->seller_guid, result["seller_guid"].c_str(), 50);
//	info->seller_name = result["seller_name"];	
//	strncpy(info->item_name, result["item_name"].c_str(), 64);
//	fromString(info->item_id, result["item_id"]);
//	fromString(info->item_count, result["item_count"]);
//	fromString(info->item_total_price, result["item_total_price"]);	
//	fromString(info->item_type, result["item_type"]);
//	fromString(info->item_sub_type, result["item_sub_type"]);
//	fromString(info->item_quality, result["item_quality"]);
//	fromString(info->item_need_level, result["item_need_level"]);
//	fromString(info->gender, result["gender"]);
//	fromString(info->menpai, result["menpai"]);
//	fromString(info->auction_type, result["auction_type"]);
//	fromString(info->auction_sub_type, result["auction_sub_type"]);
//	info->item_ints = result["item_ints"];
//	info->item_strs = result["item_strs"];
//	auction_askbuy_template_db.insertDB(info);
//
//	return true;
//}
//
//bool AppdLocaldbManager::DeleteAuctionAskbuyInfo(newauction_template* info)
//{
//	Map wheres;
//	wheres["index"] = info->index;
//	auction_askbuy_template_db.add_select_condition(MEMDB_EQ(newauction_template, index, wheres["index"].c_str()));
//	MemDB_Result<newauction_template> result = auction_askbuy_template_db.select();	
//	if (result.size() > 0)
//		auction_askbuy_template_db.deleteDB(result[0]);
//
//	//添加binlog日志
//	return AddBinlog(AUCTIONASKBUY_INFO, OPT_TYPE_DEL, wheres);
//}
//
//bool AppdLocaldbManager::SaveAuctionAskbuyInfo()
//{
//	MemDB_Result<newauction_template> result = auction_askbuy_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToAuctionAskbuyMap(result[i], m);		
//		values.push_back(m);
//	}
//
//	//保存成功后，重命名
//	if (!values.empty() && Save(AUCTIONASKBUY_INFO, values) && Rename(AUCTIONASKBUY_INFO))
//	{
//		//重命名成功后，删掉binlog文件
//		Remove(AUCTIONASKBUY_INFO);	
//	}
//
//	return true;
//}
//
//void AppdLocaldbManager::ToAuctionAskbuyMap(const newauction_template* info, Map& map)
//{
//	map["index"]				= info->index;
//	map["create_time"]			= toString(info->create_time);
//	map["return_time"]			= toString(info->return_time);
//	map["seller_guid"]			= info->seller_guid;
//	map["seller_name"]			= info->seller_name;
//	map["item_name"]			= info->item_name;
//	map["item_id"]				= toString(info->item_id);
//	map["item_count"]			= toString(info->item_count);
//	map["item_total_price"]		= toString(info->item_total_price);	
//	map["item_type"]			= toString(info->item_type);
//	map["item_sub_type"]		= toString(info->item_sub_type);
//	map["item_quality"]			= toString(info->item_quality);
//	map["item_need_level"]		= toString(info->item_need_level);
//	map["gender"]				= toString(info->gender);
//	map["menpai"]				= toString(info->menpai);
//	map["auction_type"]			= toString(info->auction_type);
//	map["auction_sub_type"]		= toString(info->auction_sub_type);
//	map["item_ints"]			= info->item_ints;
//	map["item_strs"]			= info->item_strs;	
//}
//
//void AppdLocaldbManager::GetAuctionAskbuyPostDataStr(string& str)
//{
//	//先获得keymap串
//	GetKeyMapStr(AUCTIONASKBUY_INFO, str);
//	if (str.empty())
//	{
//		tea_perror("GetAuctionAskbuyPostDataStr:get keymap empty!");
//		return;
//	}
//	//再获得具体数据
//	MemDB_Result<newauction_template> result = auction_askbuy_template_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		ToAuctionAskbuyMap(result[i], m);
//		values.push_back(m);
//	}
//
//	string map_str;
//	ToMapString(AUCTIONASKBUY_INFO, values, map_str);
//	if (map_str.empty())
//		str.clear();
//	else
//		str += MERGE_DATA_SEPARATOR + map_str;	//用合服分割串连接
//}
//
//bool AppdLocaldbManager::FromAuctionAskbuyMergePostDataStr(const string& src_str)
//{
//	if (src_str.empty()) return false;
//
//	Tokens src_token;
//	StrSplit(src_token, src_str, MERGE_DATA_SEPARATOR);
//
//	if (src_token.size() < 2)
//		return false;		//大小不对
//
//	Values values;
//	FromMapString(src_token.at(0), src_token.at(1), values);
//	for (auto iter = values.begin(); iter != values.end(); ++iter)
//		InsertAuctionAskbuyDbInfo(*iter);
//	//保存到本地文件库,ps:这里如果要万无一失得存下日志
//	SaveAuctionAskbuyInfo();
//
//	return true;
//}
//
//void AppdLocaldbManager::RepairEquipRandAttr()
//{	
//	//建立索引
//	newauction_template_db.add_select_condition(MEMDB_EQ(newauction_template, auction_type, 1));
//	MemDB_Result<newauction_template> result = newauction_template_db.select();
//	Item *item = new Item;
//	for (uint32 i = 0; i < result.size(); ++i)
//	{
//		newauction_template *info = result[i];
//		if (info == NULL)
//			continue;	
//
//		item->FromString(info->item_ints,info->item_strs);
//		item->SetGuid(item->GetStr(BINLOG_STRING_FIELD_GUID));
//		DoOrangeEquipAttrUp(item);
//		//DoRepairEquipRandAttr(item);
//		item->Clear();
//		item->ToString(info->item_ints, info->item_strs);
//	}
//	safe_delete(item);
//	SaveNewAuctionInfo();
//	return ;
//}
//
//void AppdLocaldbManager::RepairPvpLootRandAttr()
//{	
//	MemDB_Result<pvpdrop_template> result = pvpdrop_template_db.select();
//	Item *item = new Item;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		pvpdrop_template *info = result[i];
//		if (info == NULL)
//			continue;	
//
//		item->FromString(info->s_item_ints,info->s_item_strs);
//		item->SetGuid(item->GetStr(BINLOG_STRING_FIELD_GUID));
//		DoOrangeEquipAttrUp(item);
//		//DoRepairEquipRandAttr(item);
//		item->Clear();
//		item->ToString(info->s_item_ints, info->s_item_strs);
//	}
//	safe_delete(item);
//	SavePvpDropInfo();
//	return ;
//}




////加载slg武将跨服竞技场战报信息
//bool AppdLocaldbManager::LoadSlgKuafuJjcInfo()
//{
//	Results load_result;
//	Load(SLG_KUAFU_JJC_INFO,load_result);
//	for (auto it = load_result.begin(); it != load_result.end(); ++it)
//		InsertSlgKuafuJjcDbInfo(*it);
//
//	//从binlog中load	
//	ReadBinlog(SLG_KUAFU_JJC_INFO,[&](const OPT_TYPE opt_type, Map& m){
//		switch (opt_type)
//		{
//		case OPT_TYPE_ADD:
//			{
//				InsertSlgKuafuJjcDbInfo(m);
//				break;
//			}
//		case OPT_TYPE_DEL:
//			{
//				//更新内存数据库
//				slg_kuafu_jjc_info_db.add_select_condition(MEMDB_EQ(slg_kuafu_jjc_info, index, m["index"].c_str()));
//				MemDB_Result<slg_kuafu_jjc_info> result = slg_kuafu_jjc_info_db.select();	
//				if (result.size() > 0)
//					slg_kuafu_jjc_info_db.deleteDB(result[0]);
//				break;
//			}
//		default:
//			break;
//		}	
//	});
//
//	return true;
//}
//
////插入slg武将跨服竞技场战报信息
//bool AppdLocaldbManager::InsertSlgKuafuJjcInfo(slg_kuafu_jjc_info* info)
//{
//	Map values;
//	values["index"]				= info->index;
//	values["attacker_guid"]		= info->attacker_guid;
//	values["attacker_name"]		= info->attacker_name;
//	values["defender_guid"]		= info->defender_guid;
//	values["defender_name"]		= info->defender_name;
//	values["fight_result"]		= toString(info->fight_result);
//	values["old_rank"]			= toString(info->old_rank);
//	values["new_rank"]			= toString(info->new_rank);
//	values["fight_time"]		= toString(info->fight_time);
//
//	//添加binlog日志
//	if (AddBinlog(SLG_KUAFU_JJC_INFO, OPT_TYPE_ADD, values))
//	{
//		InsertSlgKuafuJjcDbInfo(values);
//		return true;
//	}
//	return false;
//}
//
////插入缓存数据库slg武将跨服竞技场战报信息
//bool AppdLocaldbManager::InsertSlgKuafuJjcDbInfo(Map &result)
//{
//	//插入之前查询是否已经有了，确保唯一
//	slg_kuafu_jjc_info_db.add_select_condition(MEMDB_EQ(slg_kuafu_jjc_info, index, result["index"].c_str()));
//	MemDB_Result<slg_kuafu_jjc_info> results = slg_kuafu_jjc_info_db.select();
//	if (results.size() > 0)
//		return false;
//
//	slg_kuafu_jjc_info* info = new slg_kuafu_jjc_info();
//
//	strncpy(info->index,			result["index"].c_str(), 64);
//	strncpy(info->attacker_guid,	result["attacker_guid"].c_str(), 64);
//	info->attacker_name				= result["attacker_name"];
//	strncpy(info->defender_guid,	result["defender_guid"].c_str(), 64);
//	info->defender_name				= result["defender_name"];
//	fromString(info->fight_result,	result["fight_result"]);
//	fromString(info->old_rank,		result["old_rank"]);
//	fromString(info->new_rank,		result["new_rank"]);
//	fromString(info->fight_time,	result["fight_time"]);
//
//	slg_kuafu_jjc_info_db.insertDB(info);
//
//	return true;
//}
//
////保存slg武将跨服竞技场战报
//bool AppdLocaldbManager::SaveSlgKuafuJjcInfo()
//{
//	MemDB_Result<slg_kuafu_jjc_info> result = slg_kuafu_jjc_info_db.select();
//	Values values;
//	for (uint32 i = 0; i < result.size(); i++)
//	{
//		Map m;
//		m["index"]				= result[i]->index;
//		m["attacker_guid"]		= result[i]->attacker_guid;
//		m["attacker_name"]		= result[i]->attacker_name;
//		m["defender_guid"]		= result[i]->defender_guid;
//		m["defender_name"]		= result[i]->defender_name;
//		m["fight_result"]		= toString(result[i]->fight_result);
//		m["old_rank"]			= toString(result[i]->old_rank);
//		m["new_rank"]			= toString(result[i]->new_rank);
//		m["fight_time"]			= toString(result[i]->fight_time);
//		values.push_back(m);
//	}
//
//	//保存成功后，重命名
//	if (!values.empty() && Save(SLG_KUAFU_JJC_INFO, values) && Rename(SLG_KUAFU_JJC_INFO))
//	{
//		//重命名成功后，删掉binlog文件
//		Remove(SLG_KUAFU_JJC_INFO);	
//	}
//
//	return true;
//}
//
////删除slg武将跨服竞技场战报
//bool AppdLocaldbManager::DeleteSlgKuafuJjcInfo(string &index)
//{
//	Map wheres;
//	wheres["index"] = index;
//
//	slg_kuafu_jjc_info_db.add_select_condition(MEMDB_EQ(slg_kuafu_jjc_info, index, wheres["index"].c_str()));
//	MemDB_Result<slg_kuafu_jjc_info> result = slg_kuafu_jjc_info_db.select();	
//	if (result.size() > 0)
//	{
//		slg_kuafu_jjc_info_db.deleteDB(result[0]);
//		AddBinlog(SLG_KUAFU_JJC_INFO, OPT_TYPE_DEL, wheres);
//		return true;
//	}
//	return false;
//}

bool AppdLocaldbManager::loadRechargeInfo() {

	Results load_result;
	Load(RECHARGE_INFO, load_result);

	char oldpayid[50];
	for (auto it = load_result.begin(); it != load_result.end(); ++it) {
		Map map = *it;
		strncpy(oldpayid, map["payid"].c_str(), 49);
		if (oldpayid[ 0 ] == 0) {
			insertRechargeDbInfo(map);
		}
	}
	
	//从binlog中load	
	ReadBinlog(RECHARGE_INFO,[&](const OPT_TYPE opt_type, Map& m) {
		switch (opt_type) {

			case OPT_TYPE_ADD:
				{
					insertRechargeDbInfo(m);
					break;
				}

			case OPT_TYPE_DEL:
				{
					//更新内存数据库
					recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, orderid, m["orderid"].c_str()));
					MemDB_Result<recharge_info> result = recharge_info_db.select();	
					if (result.size() > 0)
						recharge_info_db.deleteDB(result[0]);
					break;
				}

			case OPT_TYPE_UPDATE:
				{
					//更新内存数据库
					recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, orderid, m["orderid"].c_str()));
					MemDB_Result<recharge_info> result = recharge_info_db.select();	
					if (result.size() > 0) {
						strncpy(result[0]->payid,		m["payid"].c_str(), 49);
						strncpy(result[0]->paytime,		m["paytime"].c_str(), 49);
						strncpy(result[0]->goodsname,	m["goodsname"].c_str(), 49);
						strncpy(result[0]->money2,		m["money2"].c_str(), 49);
					}
					break;
				}

			default:
				break;
		}
	});

	return true;
}

bool AppdLocaldbManager::insertRechargeDbInfo(Map &result) {
	//插入之前查询是否已经有了，确保唯一
	recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, orderid, result["orderid"].c_str()));
	MemDB_Result<recharge_info> results = recharge_info_db.select();
	if (results.size() > 0) {
		tea_perror("insertRechargeDbInfo orderid = %s repeated", results[0]->orderid);
		return false;
	}

	recharge_info* info = new recharge_info();
	strncpy(info->guid, result["guid"].c_str(), 49);
	strncpy(info->orderid, result["orderid"].c_str(), 49);
	strncpy(info->goodsname, result["goodsname"].c_str(), 49);
	strncpy(info->money1, result["money1"].c_str(), 49);
	fromString(info->goodsnum, result["goodsnum"]);

	strncpy(info->payid, result["payid"].c_str(), 49);
	strncpy(info->paytime, result["paytime"].c_str(), 49);
	strncpy(info->money2, result["money2"].c_str(), 49);
	strncpy(info->account, result["account"].c_str(), 49);
	strncpy(info->name,	result["name"].c_str(), 49);

	recharge_info_db.insertDB(info);

	return true;
}

void AppdLocaldbManager::ToRechargeMap(const recharge_info* info, Map& map)
{
	map["guid"]				= info->guid;
	map["orderid"]			= info->orderid;
	map["goodsname"]		= info->goodsname;
	map["money1"]			= info->money1;
	map["goodsnum"]			= toString(info->goodsnum);
	map["payid"]			= info->payid;
	map["paytime"]			= info->paytime;
	map["money2"]			= info->money2;
	map["account"]			= info->account;
	map["name"]				= info->name;
}

bool AppdLocaldbManager::insertRechargeInfo(recharge_info* info) {
	Map values;
	ToRechargeMap(info, values);

	//添加binlog日志
	if (insertRechargeDbInfo(values) && AddBinlog(RECHARGE_INFO, OPT_TYPE_ADD, values)) {
		return true;
	}
	return false;
}

void AppdLocaldbManager::queryRechargeGuidByOrderId(string& orderid, string& guid) {
	Map values;
	values["orderid"] = orderid;
	recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, orderid, values["orderid"].c_str()));
	MemDB_Result<recharge_info> result = recharge_info_db.select();
	if (result.size() > 0) {
		char vv[50];
		strncpy(vv, result[0]->guid, 49);
		guid = string(vv);
	}
}

void AppdLocaldbManager::queryRechargeAccountByOrderId(string& orderid, string& account, string& name, string& time) {
	Map values;
	values["orderid"] = orderid;
	recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, orderid, values["orderid"].c_str()));
	MemDB_Result<recharge_info> result = recharge_info_db.select();
	if (result.size() > 0) {
		char vv[50];
		strncpy(vv, result[0]->account, 49);
		account = string(vv);

		strncpy(vv, result[0]->name, 49);
		name = string(vv);

		strncpy(vv, result[0]->paytime, 49);
		time = string(vv);
	}
}

void AppdLocaldbManager::queryRechargeNameAndPayTimeByUid(string& uid, string& guid, string& name, string& time) {
	Map values;
	values["account"] = uid;
	recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, account, values["account"].c_str()));
	MemDB_Result<recharge_info> result = recharge_info_db.select();
	if (result.size() > 0) {
		char vv[50];
		strncpy(vv, result[0]->name, 49);
		name = string(vv);
		strncpy(vv, result[0]->paytime, 49);
		time = string(vv);
		strncpy(vv, result[0]->guid, 49);
		guid = string(vv);
	}
}

bool AppdLocaldbManager::checkRechargeOrderIsDealed(string& orderid) {
	Map values;
	values["orderid"] = orderid;
	recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, orderid, values["orderid"].c_str()));
	MemDB_Result<recharge_info> result = recharge_info_db.select();
	if (result.size() == 0 || result[0]->payid[ 0 ] == 0) {
		return false;
	}

	return true;
}

bool AppdLocaldbManager::checkRechargeUidIsDealed(string& uid) {
	Map values;
	values["account"] = uid;
	recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, account, values["account"].c_str()));
	MemDB_Result<recharge_info> result = recharge_info_db.select();
	if (result.size() == 0 || result[0]->payid[ 0 ] == 0) {
		return false;
	}

	return true;
}


bool AppdLocaldbManager::updateRechargeInfo(recharge_info* info) {
	Map values;
	values["orderid"] = info->orderid;
	values["payid"] = info->payid;
	values["paytime"] = info->paytime;
	values["money2"] = info->money2;

	//先添加binlog日志
	if (AddBinlog(RECHARGE_INFO, OPT_TYPE_UPDATE, values)) {
		//更新内存数据库
		recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, orderid, values["orderid"].c_str()));
		MemDB_Result<recharge_info> result = recharge_info_db.select();	
		if (result.size() > 0) {
			strncpy(result[0]->payid, info->payid, 49);
			strncpy(result[0]->paytime, info->paytime, 49);
			strncpy(result[0]->money2, info->money2, 49);
		}
		return true;
	}
	return false;
}

bool AppdLocaldbManager::deleteRechargeInfo(recharge_info* info) {
	Map wheres;
	wheres["orderid"] = info->orderid;
	recharge_info_db.add_select_condition(MEMDB_EQ(recharge_info, orderid, wheres["orderid"].c_str()));
	MemDB_Result<recharge_info> result = recharge_info_db.select();	
	if (result.size() > 0) {
		recharge_info_db.deleteDB(result[0]);
	}
	//添加binlog日志
	return AddBinlog(RECHARGE_INFO, OPT_TYPE_DEL, wheres);
}

bool AppdLocaldbManager::SaveRechargeInfo() {
	MemDB_Result<recharge_info> result = recharge_info_db.select();
	Values values;
	for (uint32 i = 0; i < result.size(); i++) {
		Map m;
		ToRechargeMap(result[i], m);
		values.push_back(m);
	}

	//保存成功后，重命名
	if (!values.empty() && Save(RECHARGE_INFO, values) && Rename(RECHARGE_INFO)) {
		//重命名成功后，删掉binlog文件
		Remove(RECHARGE_INFO);
	}

	return true;
}









bool AppdLocaldbManager::loadGiftcodeInfo(){
	Results load_result;
	Load(GIFTCODE_INFO, load_result);

	for (auto it = load_result.begin(); it != load_result.end(); ++it) {
		insertGiftcodeDbInfo(*it);
	}

	//从binlog中load	
	ReadBinlog(GIFTCODE_INFO,[&](const OPT_TYPE opt_type, Map& m) {
		switch (opt_type) {

		case OPT_TYPE_ADD:
			{
				insertGiftcodeDbInfo(m);
				break;
			}

		default:
			break;
		}
	});

	return true;
}

void AppdLocaldbManager::ToGiftcodeMap(const giftcode_info* info, Map& map){
	map["giftcode"]				= info->giftcode;
}

bool AppdLocaldbManager::insertGiftcodeDbInfo(Map &result){
	//插入之前查询是否已经有了，确保唯一
	giftcode_info_db.add_select_condition(MEMDB_EQ(giftcode_info, giftcode, result["giftcode"].c_str()));
	MemDB_Result<giftcode_info> results = giftcode_info_db.select();
	if (results.size() > 0) {
		tea_perror("insertGiftcodeDbInfo giftcode = %s repeated", results[0]->giftcode);
		return false;
	}

	giftcode_info* info = new giftcode_info();
	strncpy(info->giftcode, result["giftcode"].c_str(), 49);

	giftcode_info_db.insertDB(info);

	return true;
}

bool AppdLocaldbManager::checkGiftcodeIsUsed(string& giftcode){
	Map values;
	values["giftcode"] = giftcode;
	giftcode_info_db.add_select_condition(MEMDB_EQ(giftcode_info, giftcode, values["giftcode"].c_str()));
	MemDB_Result<giftcode_info> result = giftcode_info_db.select();
	if (result.size() == 0) {
		return false;
	}

	return true;

}
bool AppdLocaldbManager::insertGiftcodeInfo(giftcode_info* info){
	Map values;
	ToGiftcodeMap(info, values);

	//添加binlog日志
	if (insertGiftcodeDbInfo(values) && AddBinlog(GIFTCODE_INFO, OPT_TYPE_ADD, values)) {
		return true;
	}
	return false;
}
bool AppdLocaldbManager::SaveGiftcodeInfo(){
	MemDB_Result<giftcode_info> result = giftcode_info_db.select();
	Values values;
	for (uint32 i = 0; i < result.size(); i++) {
		Map m;
		ToGiftcodeMap(result[i], m);
		values.push_back(m);
	}

	//保存成功后，重命名
	if (!values.empty() && Save(GIFTCODE_INFO, values) && Rename(GIFTCODE_INFO)) {
		//重命名成功后，删掉binlog文件
		Remove(GIFTCODE_INFO);
	}

	return true;

}

