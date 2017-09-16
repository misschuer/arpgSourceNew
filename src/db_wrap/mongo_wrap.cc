//
//#define MONGO_USE__INT64
//#define MONGO_USE_LONG_LONG_INT
//#define MONGO_HAVE_STDINT
//#define MONGO_STATIC_BUILD
//
//#include <comm/common_stl.h>
//#include "mongo_wrap.h"
////#include "mongo.h"
//extern "C"{
//  #include <libmongoclient/mongo.h>
//};
//#include <sstream>
//#include "MogoWrapLogImpl.h"
//
////static std::stringstream  tmp_ss;
////////////////////////////////////////////////////////////////////////////
////for MongoWrap
//MongoWrap::MongoWrap():port_(0),connect_count_(0)
//{	
//	conn_ = (mongo *)malloc(sizeof(mongo));
//	mongo_init(conn_);
//
//	log_ = new MogoWrapLogImpl;
//}
//
//MongoWrap::~MongoWrap()
//{
//	if(conn_)
//	{
//		mongo_destroy(conn_);
//		free(conn_);
//		conn_ = nullptr;
//	}	
//
//	if(log_)
//	{
//		delete log_;
//		log_ = nullptr;
//	}
//	
//}
//
//bool MongoWrap::Open(string host,unsigned short port,string user,string pwd,string dbname,int level, string logpath)
//{
//	//����־
//
//	host_ = host;
//	port_ = port == 0 ? 27017 : port;
//	dbname_ = dbname.empty()?"admin":dbname;
//	user_ = user;
//	password_ = pwd;
//
//	uint32_t before=ms_time();
//	mongo_set_op_timeout( conn_, 1000 );
//	if( mongo_client( conn_, host_.c_str(), port_ ) != MONGO_OK )
//	{
//		return false;
//	}
//	//todo dingjd ����д��
//	if(!user.empty() && mongo_cmd_authenticate(conn_,dbname_.c_str(),user_.c_str(),password_.c_str()) != MONGO_OK)
//	{
//		return false;
//	}
//	connect_count_++;
//
//	log_->Open(level,logpath);
//	log_->WriteLog(_DEBUG_L,before,"Open();From="+dbname_+";host="+host+";port="+toString(port));
//	
//	return true;
//}
///*
//bool MongoWrap::CheckStatus()
//{
//	//�����������״̬
//	if(mongo_check_connection( conn_ ) == MONGO_ERROR){
//		mongo_reconnect( conn_ );
//		//��������Ҳ��ҪȨ����֤
//		if(!user_.empty() && mongo_cmd_authenticate(conn_,dbname_.c_str(),user_.c_str(),password_.c_str()) != MONGO_OK)				
//			return false;
//		if( mongo_simple_int_command( conn_, "admin", "ping", 1, NULL ) == MONGO_OK)
//			connect_count_++;
//		else 
//			return false;
//	}
//	return true;
//}
//*/
//
//bool MongoWrap::CheckNS(const string& ns)
//{
//	//�����|��'\'ǰ��ȥ�����ɼ��ַ�	
//	for (auto it = ns.begin(); it != ns.end(); ++it)
//	{
//		char c = *it;
//		if( c >= 'a' && c <= 'z')		//97-122
//			continue;
//		if (c == '_' || c == '.')		//95, 46
//			continue;		
//		if( c >= '0' && c <='9')		//48-57
//			continue;		
//		if(c >= 'A' && c <= 'Z')		//65-90
//			continue;
//
//		//ֻ����_�߼�.��ǰӢ�ļ�����
//		return false;
//	}	
//	
//	return true;
//}
//
//Mongo_Result MongoWrap::Query( string ns,const Map& where,Results& results ,int limit )
//{	
//	if(!CheckNS(ns)) return MONGO_RES_ERROR;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//	uint32_t before=ms_time();
//	bson bsonWhere;
//	ToBson(where,bsonWhere);
//	DataQueryBsonToMap(ns.c_str(), &bsonWhere, nullptr, results,limit);
//	log_->WriteLog(_DEBUG_L,before,"Query();From="+ns,where,"where");
//
//	bson_destroy(&bsonWhere);
//	if (results.size() == 0)
//	{
//		return MONGO_RES_NULL;
//	}
//	
//	return MONGO_RES_SUCCESS;
//}
//
//Mongo_Result MongoWrap::Query( string ns,const Map& where,Results& results,string orderKey, int32_t bySort,int32_t limitResult )
//{
//	if(!CheckNS(ns)) return MONGO_RES_ERROR;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//	uint32_t before=ms_time();
////	char hex_oid[25];
//	bson bsonWhere;
//	mongo_cursor cursor[1];
//	bson_init( &bsonWhere );
//	{
//		//query����
//		bson_append_start_object( &bsonWhere, "$query" );
//		DataTranslateMapToBson(where,bsonWhere);
//		bson_append_finish_object( &bsonWhere );
//
//		//add orderby 
//		if(!orderKey.empty())
//		{
//			bson_append_start_object( &bsonWhere, "$orderby" );
//			bson_append_int( &bsonWhere, orderKey.c_str(), bySort);
//			bson_append_finish_object( &bsonWhere );		
//		}
//
//	}	
//	bson_finish( &bsonWhere );
//
//	mongo_cursor_init( cursor, conn_, ns.c_str() );
//	mongo_cursor_set_query( cursor, &bsonWhere );
//	if(limitResult > 0)
//		mongo_cursor_set_limit(cursor, limitResult);
//
//	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
//		Map reslutMap;
//		ToMap(*mongo_cursor_bson( cursor ), reslutMap);
//		results.push_back(reslutMap);
//	}
//
//	log_->WriteLog(_DEBUG_L,before,
//		"Query();From="+ns+";limitResult="+toString(limitResult),
//		where,"where",orderKey,"orderby",bySort);	
//
//	mongo_cursor_destroy( cursor );
//	bson_destroy(&bsonWhere);
//	if (results.size() == 0)
//	{
//		return MONGO_RES_NULL;
//	}
//	
//	return MONGO_RES_SUCCESS;
//}
////
////Mongo_Result MongoWrap::Query( string ns,const Map& where,Results& results, bool bGrate,string compareKey, uint32_t uValue )
////{
////	uint32_t before=ms_time();
////	bson bsonWhere;
////	bson_init( &bsonWhere );
////	if (bGrate)
////	{//���ڵ���
////		bson_append_start_object( &bsonWhere, compareKey.c_str() );
////		bson_append_long( &bsonWhere, "$gte", uValue );
////		bson_append_finish_object( &bsonWhere );
////	}
////	else
////	{//С��
////		bson_append_start_object( &bsonWhere, compareKey.c_str() );
////		bson_append_long( &bsonWhere, "$lt", uValue );
////		bson_append_finish_object( &bsonWhere );
////	}
////	bson_finish( &bsonWhere );
////
////	std::unique_lock<std::mutex> lock(mutex_);				//����
////	DataQueryBsonToMap(ns.c_str(), &bsonWhere, nullptr, results);
////
////	log_->WriteLog(_DEBUG_L,before,"Query();From="+ns,where,"where",
////		bGrate? "compareKey[>]" : "compareKey[<]","compareKey",uValue);
////
////	bson_destroy(&bsonWhere);
////	if (results.size() == 0)
////	{
////		return MONGO_RES_NULL;
////	}
////	
////	return MONGO_RES_SUCCESS;
////}
//
//Mongo_Result MongoWrap::Query( string ns,const Map& where,Results& results,const Map& outfield )
//{
//	if(!CheckNS(ns)) return MONGO_RES_ERROR;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonWhere,bsonOutField;
//	ToBson(where,bsonWhere);
//	ToBson(outfield, bsonOutField);
//	
//	DataQueryBsonToMap(ns.c_str(), &bsonWhere, &bsonOutField, results);
//
//	log_->WriteLog(_DEBUG_L,before,"Query();From="+ns,where,"where");
//	
//
//	bson_destroy(&bsonWhere);
//	bson_destroy(&bsonOutField);
//	if (results.size() == 0)
//	{
//		return MONGO_RES_NULL;
//	}
//	return MONGO_RES_SUCCESS;
//
//}
//
//bool MongoWrap::Insert(string ns,Map& values,bool fsync)
//{
//	if(!CheckNS(ns)) return false;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//
//	mongo_write_concern wc;
//	memset( &wc, 0, sizeof( wc ));
//	mongo_write_concern_set_fsync( &wc, fsync?1:0 );		//�Ƿ�ʹ��ǿ��ͬ��
//
//	bson bsonValues;
//	ToBson(values,bsonValues);
//	
//	//ns = dbname_+ns;
//	bool ret = false;
//	if(mongo_insert(conn_,ns.c_str(),&bsonValues, fsync ? &wc :NULL) == MONGO_OK)
//		ret = true;
//	log_->WriteLog(_DEBUG_L,before,"Insert();From="+ns,values,"values");
//	
//	bson_destroy(&bsonValues);
//	return ret;
//}
//
//bool MongoWrap::Insert(string ns,Map& values,string iKey,const Values& uints,string sKey,const StrValues& strs)
//{
//	if(!CheckNS(ns)) return false;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonValues;
//	bson_init( &bsonValues );
//	//mapӳ�䵽bson��
//	DataTranslateMapToBson(values,bsonValues);
//
//	//������ֵ���鵽bson
//	bson_append_start_array( &bsonValues, iKey.c_str() );
//	for (auto iter:uints) 
//	{
//		bson_append_long( &bsonValues, "", iter );
//	}
//	bson_append_finish_object( &bsonValues );
//	//�����ַ������鵽bson
//	bson_append_start_array( &bsonValues, sKey.c_str() );
//	for (auto iter:strs) 
//	{
//		bson_append_string( &bsonValues, "", iter.c_str() );
//	}
//	bson_append_finish_object( &bsonValues );
//	bson_finish( &bsonValues );
//	
//	//ns = dbname_+ns;
//	bool ret = false;
//	if(mongo_insert(conn_,ns.c_str(),&bsonValues,NULL) == MONGO_OK)
//		ret = true;
//	if (log_->log_level == _DEBUG_L)
//	{
// 		
//		string msg="Insert();From="+ns+";values:";
//		for (auto it: values)
//		{
//			msg+=it.first+"="+it.second+"?";
//		}
//		for (auto it:uints)
//		{
//			msg+=iKey+"="+toString(it)+"?";
//		}
//		for (auto it:strs)
//		{
//			msg+=sKey+"="+it+"?";
//		}
//
//		msg=msg.substr(0,msg.length()-1);
//		log_->DoLog(msg,before);
//	}
//	bson_destroy(&bsonValues);
//	return ret;
//}
//
////map�ṹת����bson��bson�ѳ�ʼ�������ڲ�bson���죬����ƴ��ʹ��
//void MongoWrap::DataTranslateMapToBson(const Map& from,bson& to)
//{
//	for (auto it: from)
//	{
//		string keyStr = it.first;
//		string valueStr = it.second;
//		char markType = keyStr.at(0);
//		switch (markType)
//		{
//		case 'i':
//			{
//				int nValue = 0;
//				fromString(nValue,valueStr);
//
//				bson_append_int(&to, keyStr.c_str(), nValue);
//				break;
//			}
//		case 'u':
//			{
//				int64_t u = 0;
//				fromString(u,valueStr);
//
//				bson_append_long(&to, keyStr.c_str(), u);
//				break;
//			}
//		case 'b':
//			{
//				if (keyStr.length()>4)
//				{
//					string subStr = keyStr.substr(0,4);
//					if (subStr.compare("bin_")==0)
//					{
//						bson_append_binary(&to,keyStr.c_str(), BSON_BIN_BINARY, valueStr.c_str(),valueStr.length());
//						break;
//					}
//				}
//			}
////��ʱȥ����û��ʹ�õ���������������ͻ��
//// 		case 'd':
//// 			{
//// 				double d = 0;
//// 				tmp_ss.str("");
//// 				tmp_ss << valueStr;			
//// 				tmp_ss >> d;
//// 
//// 				bson_append_double(&to, keyStr.c_str(), d);
//// 				break;
//// 			}
//		default:
//			{
//				bson_append_string(&to, keyStr.c_str(), valueStr.c_str());
//				break;
//			}
//		}
//	}
//}
//
////���浥����¼����������������ֵ
//bool MongoWrap::Update(string ns,const Map& where,Map& values,bool fsync)
//{
//	if(!CheckNS(ns)) return false;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonWhere,bsonValues;
//	ToBson(where,bsonWhere);
//
//	bson_init( &bsonValues );
//	bson_append_start_object( &bsonValues, "$set" );
//	DataTranslateMapToBson(values,bsonValues);
//	bson_append_finish_object( &bsonValues );
//	bson_finish( &bsonValues );
//
//	mongo_write_concern wc;
//	memset( &wc, 0, sizeof( wc ));
//	mongo_write_concern_set_fsync( &wc, fsync?1:0 );		//�Ƿ�ʹ��ǿ��ͬ��
//	
//	bool ret = false;
//	if(mongo_update(conn_,ns.c_str(),&bsonWhere,&bsonValues,MONGO_UPDATE_MULTI,&wc) == MONGO_OK)
//		ret = true;
//	else
//	{
//		string msg;
//		int errorcode = mongo_get_err(conn_);
//		msg ="error_code:" + toString(errorcode);
//		string errormsg = mongo_get_server_err_string(conn_);
//		msg += ";error_server_msg:"+ errormsg;
//		log_->WriteLog(_ERROR_L,before,"Update();From="+ns,where,"where",msg,"Fail");		
//	}
//
//	log_->WriteLog(_DEBUG_L,before,"Update();From="+ns,where,"where",values,"values");
//	bson_destroy(&bsonWhere);
//	bson_destroy(&bsonValues);
//	mongo_write_concern_destroy( &wc );
//	return ret;
//}
//
//bool MongoWrap::Update(string ns,int _id,Map& values,bool fsync)
//{
//	if(!CheckNS(ns)) return false;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	string id = "_id";
//	bson bsonWhere,bsonValues;
//	bson_init( &bsonWhere );
//	bson_append_int(&bsonWhere, id.c_str(), _id);
//	bson_finish( &bsonWhere );
//	Map where;
//	where["_id"] = toString(_id);
//	bson_init( &bsonValues );
//	bson_append_start_object( &bsonValues, "$set" );
//	DataTranslateMapToBson(values,bsonValues);
//	bson_append_finish_object( &bsonValues );
//	bson_finish( &bsonValues );
//
//	mongo_write_concern wc;
//	memset( &wc, 0, sizeof( wc ));
//	mongo_write_concern_set_fsync( &wc,fsync? 1 :0);
//	
//	bool ret = false;	
//	if(mongo_update(conn_,ns.c_str(),&bsonWhere,&bsonValues,MONGO_UPDATE_MULTI,&wc) == MONGO_OK)
//		ret = true;
//	else
//	{		
//		string msg;
//		int errorcode = mongo_get_err(conn_);
//		msg ="error_code:" + toString(errorcode);
//		string errormsg = mongo_get_server_err_string(conn_);
//		msg += ";error_server_msg:"+ errormsg;
//		log_->WriteLog(_ERROR_L,before,"Update();From="+ns,where,"where",msg,"Fail");
//
//	}
//	log_->WriteLog(_DEBUG_L,before,"Update();From="+ns,where,"where",values,"values");
//	
//	bson_destroy(&bsonWhere);
//	bson_destroy(&bsonValues);
//	mongo_write_concern_destroy( &wc );
//	return ret;
//}
//
//
//bool MongoWrap::Update( string ns,const Map& where,string key,const Values& uints,bool fsync )
//{
//	if(!CheckNS(ns)) return false;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonWhere,bsonValues;
//	ToBson(where,bsonWhere);
//	//ToBson(uints,key.c_str(), bsonValues);
//	//ns = dbname_+ns;
//	bson_init( &bsonValues );
//	bson_append_start_object( &bsonValues, "$set" );
//	bson_append_start_array( &bsonValues, key.c_str() );
//	for (auto iter:uints) 
//	{
//		bson_append_long( &bsonValues, "", iter );
//	}
//	bson_append_finish_object( &bsonValues );
//	bson_append_finish_object( &bsonValues );
//	bson_finish( &bsonValues );
//
//	mongo_write_concern wc;
//	memset( &wc, 0, sizeof( wc ));
//	mongo_write_concern_set_fsync( &wc, fsync?1:0 );
//
//	bool ret = false;
//	if(mongo_update(conn_,ns.c_str(),&bsonWhere,&bsonValues,MONGO_UPDATE_MULTI,&wc) == MONGO_OK)
//		ret = true;
//	else
//	{
//	
//		string msg;
//		int errorcode = mongo_get_err(conn_);
//		msg ="error_code:" + toString(errorcode);
//		string errormsg = mongo_get_server_err_string(conn_);
//		msg += ";error_server_msg:"+ errormsg;
//		log_->WriteLog(_ERROR_L,before,"Update();From="+ns,where,"where",msg,"Fail");
//		
//	}
//	if (log_->log_level == _DEBUG_L)
//	{
//		string msg;
//		for (auto it:uints)
//		{
//			msg+=key+"="+toString(it)+"?";
//		}
//		msg=msg.substr(0,msg.length()-1);
//		log_->WriteLog(_DEBUG_L,before,"Update();From="+ns,where,"where",msg,"values");
//	}
//
//	bson_destroy(&bsonWhere);
//	bson_destroy(&bsonValues);
//	mongo_write_concern_destroy( &wc );
//	return ret;
//}
//
//bool MongoWrap::Update( string ns,const Map& where,string key,const StrValues& strs,bool fsync )
//{
//	if(!CheckNS(ns)) return false;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonWhere,bsonValues;
//	ToBson(where,bsonWhere);
//	//ToBson(strs,key.c_str(), bsonValues);
//	//ns = dbname_+ns;
//	bson_init( &bsonValues );
//	bson_append_start_object( &bsonValues, "$set" );
//	bson_append_start_array( &bsonValues, key.c_str() );
//	for (auto iter:strs) 
//	{
//		bson_append_string( &bsonValues, "", iter.c_str() );
//	}
//	bson_append_finish_object( &bsonValues );
//	bson_append_finish_object( &bsonValues );
//	bson_finish( &bsonValues );
//
//	mongo_write_concern wc;
//	memset( &wc, 0, sizeof( wc ));
//	mongo_write_concern_set_fsync( &wc, fsync?1:0 );
//
//	bool ret = false;
// 	if(mongo_update(conn_,ns.c_str(),&bsonWhere,&bsonValues,MONGO_UPDATE_MULTI,&wc) == MONGO_OK)
//		ret = true;
//	else
//	{
//		
//		string msg;
//		int errorcode = mongo_get_err(conn_);
//		msg ="error_code:" + toString(errorcode);
//		string errormsg = mongo_get_server_err_string(conn_);
//		msg += ";error_server_msg:"+ errormsg;
//		log_->WriteLog(_ERROR_L,before,"Update();From="+ns,where,"where",msg,"Fail");
//	}
//
//	if (log_->log_level == _DEBUG_L)
//	{
//		string msg;
//		for (auto it:strs)
//		{
//			msg+=key+"="+it+"?";
//		}
//		msg=msg.substr(0,msg.length()-1);
//		log_->WriteLog(_DEBUG_L,before,"Update();From="+ns,where,"where",msg,"values");
//	}
//
//	bson_destroy(&bsonWhere);
//	bson_destroy(&bsonValues);
//	mongo_write_concern_destroy( &wc );
//	return ret;
//}
//
//bool MongoWrap::Upsert(string ns,const Map& where,Map& values)
//{
//	if(!CheckNS(ns)) return false;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonWhere,bsonValues;
//	ToBson(where,bsonWhere);
//
//	bson_init( &bsonValues );
//	bson_append_start_object( &bsonValues, "$set" );
//	DataTranslateMapToBson(values,bsonValues);
//	bson_append_finish_object( &bsonValues );
//	bson_finish( &bsonValues );
//
//	bool ret = false;
//	if(mongo_update(conn_,ns.c_str(),&bsonWhere,&bsonValues,MONGO_UPDATE_UPSERT,NULL) == MONGO_OK)
//		ret = true;
//	else
//	{
//		string msg;
//		int errorcode = mongo_get_err(conn_);
//		msg ="error_code:" + toString(errorcode);
//		string errormsg = mongo_get_server_err_string(conn_);
//		msg += ";error_server_msg:"+ errormsg;
//		log_->WriteLog(_ERROR_L,before,"Update();From="+ns,where,"where",msg,"Fail");		
//	}
//
//	log_->WriteLog(_DEBUG_L,before,"Update();From="+ns,where,"where",values,"values");
//	bson_destroy(&bsonWhere);
//	bson_destroy(&bsonValues);
//	return ret;
//}
//
//bool MongoWrap::Delete(string ns,const Map& where)
//{
//	if(!CheckNS(ns)) return false;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonWhere;
//	ToBson(where,bsonWhere);
//	//ns = dbname_+ns;	
//	bool ret = false;
//	if(mongo_remove(conn_,ns.c_str(),&bsonWhere,NULL) == MONGO_OK)
//		ret = true;
//	
//	log_->WriteLog(_DEBUG_L,before,"Delete();From="+ns,where,"where");
//	bson_destroy(&bsonWhere);
//	return ret;
//}
//
//void MongoWrap::ToMap( const bson& from,Map& to )
//{
//	to.clear();
//
//	bson_iterator it;
//	bson_type type = BSON_STRING;
//	bson_iterator_init( &it, &from );
//	while( bson_iterator_next( &it ) ) 
//	{
//		type = bson_iterator_type(&it);
//		const char* key = bson_iterator_key( &it );
//		//���ڿ��ܱ�ת�ɿ�ѧ������,��������u��ͷ�ģ�ֱ��ת������
//		if(key[0] == 'u' && type == BSON_DOUBLE)
//			type = BSON_LONG;
//		switch (type)
//		{
//		case BSON_STRING:
//			{
//				to.insert(std::map<string,string>::value_type(key, bson_iterator_string( &it )));
//				break;
//			}
//		case BSON_INT:
//			{
//				to.insert(std::map<string,string>::value_type(key, toString(bson_iterator_int(&it))));
//				break;
//			}
//		case BSON_DOUBLE:
//			{
//				to.insert(std::map<string,string>::value_type(key, toString(bson_iterator_double(&it))));
//				break;
//			}
//		case BSON_LONG:
//			{
//				to.insert(std::map<string,string>::value_type(key, toString(bson_iterator_long(&it))));
//				break;
//			}
//		case BSON_BINDATA:
//			{
//				to.insert(std::map<string,string>::value_type(key, toString(bson_iterator_bin_data(&it))));
//				break;
//			}
//		//������������ת�������
//		case BSON_UNDEFINED:
//		case BSON_EOO:
//		case BSON_OBJECT:
//		case BSON_ARRAY:
//		case BSON_OID:
//		case BSON_BOOL:
//		case BSON_DATE:
//		case BSON_NULL:
//		case BSON_REGEX:
//		case BSON_DBREF:
//		case BSON_CODE:
//		case BSON_SYMBOL:
//		case BSON_CODEWSCOPE:
//		case BSON_TIMESTAMP:
//		case BSON_MAXKEY:
//		case BSON_MINKEY:
//			{
//				break;
//			}
//		default:
//			break;
//		}
//	}
//
//}
//
//bool MongoWrap::FromBson(const bson& src,const char* key,Values& uints)
//{
//	uints.clear();
//
//	bson_iterator it,it2;
//	bson_iterator_init( &it, &src );
//	while( bson_iterator_next( &it ) ) 
//	{
//		string keyStr =bson_iterator_key( &it );
//		if(keyStr.compare(key) != 0)
//			continue;
//
//		//����±�ר������ints�������飬��Ȼ����
//		bson_type type = bson_iterator_type(&it);
//		if(type != BSON_ARRAY)
//			return false;
//		
//		bson_iterator_subiterator( &it, &it2 );
//
//		uint32_t u;
//		while( bson_iterator_next( &it2 ) ) 
//		{
//			bson_type type = bson_iterator_type(&it2);
//			if(type != BSON_LONG)
//				return false;	
//
//			u = (uint32_t)bson_iterator_long(&it2);			
//			uints.push_back(u);			
//		}
//	}
//	return true;
//}
//
//bool MongoWrap::FromBson( const bson& src,const char* key,StrValues& strs )
//{
//	strs.clear();
//
//	bson_iterator it,it2;
//	bson_iterator_init( &it, &src );
//	while( bson_iterator_next( &it ) ) 
//	{
//		string keyStr =bson_iterator_key( &it );
//		if(keyStr.compare(key) != 0)
//			continue;
//
//		bson_type type = bson_iterator_type(&it);
//		if(type != BSON_ARRAY)
//			 return false;
//
//		bson_iterator_subiterator( &it, &it2 );
//		while( bson_iterator_next( &it2 ) ) 
//		{
//			bson_type type = bson_iterator_type(&it2);
//			if(type != BSON_STRING)
//				return false;	
//
//			strs.push_back(bson_iterator_string(&it2));			
//		}
//	}
//	return true;
//}
//
//void MongoWrap::ToBson( const Map& m,bson& to )
//{
//	bson_init( &to );
//
//	for (auto it: m)
//	{
//		string keyStr = it.first;
//		string valueStr = it.second;
//		char markType = keyStr.at(0);
//		switch (markType)
//		{
//		case 'i':
//			{
//				int nValue = 0;
//				fromString(nValue, valueStr);
//				bson_append_int(&to, keyStr.c_str(), nValue);
//				break;
//			}
//		case 'u':
//			{
//				int64_t u = 0;
//				fromString(u, valueStr);
//
//				bson_append_long(&to, keyStr.c_str(), u);
//				break;
//			}
//		case 'b':
//			{
//				if (keyStr.length()>4)
//				{
//					string subStr = keyStr.substr(0,4);
//					if (subStr.compare("bin_")==0)
//					{
//						bson_append_binary(&to,keyStr.c_str(), BSON_BIN_BINARY, valueStr.c_str(),valueStr.length());
//						break;
//					}
//				}
//			}
//
////��ʱȥ����û��ʹ�õ���������������ͻ��
//// 		case 'd':
//// 			{
//// 				double d = 0;
//// 				tmp_ss.str("");
//// 				tmp_ss << valueStr;			
//// 				tmp_ss >> d;
//// 
//// 				bson_append_double(&to, keyStr.c_str(), d);
//// 				break;
//// 			}
//		default:
//			{
//				bson_append_string(&to, keyStr.c_str(), valueStr.c_str());
//				break;
//			}
//		}
//	}
//	bson_finish( &to );
//}
//
//void MongoWrap::ToBson( const Values& m,const char* key,bson& to )
//{
//	bson_init( &to );
//	bson_append_start_array( &to, key );
//
//	for (auto iter:m) 
//	{
//		bson_append_long( &to, "", iter );
//	}
//	bson_append_finish_object( &to );
//	bson_finish( &to );
//
//}
//
//void MongoWrap::ToBson( const StrValues& m,const char* key,bson& to )
//{
//	bson_init( &to );
//	bson_append_start_array( &to, key );
//
//	for (auto iter:m) 
//	{
//		bson_append_string( &to, "", iter.c_str() );
//	}
//	bson_append_finish_object( &to );
//	bson_finish( &to );
//}
//
//Mongo_Result MongoWrap::Load( string ns,const Map& where,Map& result )
//{	
//	if(!CheckNS(ns)) return MONGO_RES_ERROR;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonWhere,out;
//	ToBson(where,bsonWhere);
//	//ns = dbname_+ns;
//	Mongo_Result ret = MONGO_RES_SUCCESS;
//	if( mongo_find_one( conn_, ns.c_str(), &bsonWhere, bson_shared_empty( ), &out ) == MONGO_ERROR)
//		ret = MONGO_RES_NULL;
//	else 
//		ToMap(out, result);
//	
//	log_->WriteLog(_DEBUG_L,before,"Load();From="+ns,where,"where");
//
//	bson_destroy(&bsonWhere);
//	bson_destroy(&out);
// 	return ret;
//}
//
//int MongoWrap::Count( string ns,const Map& where )
//{
//	if(!CheckNS(ns)) return MONGO_RES_ERROR;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	uint32_t before=ms_time();
//	bson bsonWhere;
//	
//	//���ns	
//	auto pos = ns.find('.');
//	if(pos == string::npos)
//		return MONGO_ERROR;
//	string strDB = ns.substr(0,pos);
//	string table_name = ns.substr(pos+1,ns.length());
//
//	ToBson(where,bsonWhere);
//	int c = (int)mongo_count(conn_,strDB.c_str(), table_name.c_str(),&bsonWhere);	
//	log_->WriteLog(_DEBUG_L,before,"Count();From="+ns,where,"where");
//	if(c == MONGO_ERROR){
//		string msg;
//		int errorcode = mongo_get_err(conn_);
//		msg ="error_code:" + toString(errorcode);
//		string errormsg = mongo_get_server_err_string(conn_);
//		msg += ";error_server_msg:"+ errormsg;
//		log_->WriteLog(_ERROR_L,before,"Count();From="+ns,where,"where",msg,"Fail");
//	}
//	
//	bson_destroy(&bsonWhere);	
//	return c;
//}
//
//void MongoWrap::DataQueryBsonToMap( const char* ns, const bson *from,const bson *outfield, Results& to,int limit,int skip,int options )
//{
//	//char hex_oid[25];
//	mongo_cursor cursor[1];
//
//	mongo_cursor_init( cursor, conn_, ns );
//	mongo_cursor_set_query( cursor, from );
//	if(outfield)
//		mongo_cursor_set_fields(cursor, outfield);
//	if(limit)
//		mongo_cursor_set_limit( cursor, limit );
//	if (skip)
//		mongo_cursor_set_skip( cursor, skip );
//	if (options)
//		mongo_cursor_set_options( cursor, options );
//
//	Map reslutMap;
//	while( mongo_cursor_next( cursor ) == MONGO_OK ) {		
//		ToMap(*mongo_cursor_bson( cursor ), reslutMap);
//		to.push_back(reslutMap);
//	}
//	mongo_cursor_destroy( cursor );
//}
//
//void MongoWrap::Drop( string ns )
//{
//	//if(!CheckNS(ns)) return MONGO_RES_ERROR;				//��֤��������Ƿ�Ϸ�
//	std::unique_lock<std::mutex> lock(mutex_);				//����
//
//	size_t pos = ns.find('.');
//	if(pos == string::npos)
//		return;
//
//	uint32_t before=ms_time();
//	string db = ns.substr(0,pos);
//	string tbl = ns.substr(pos+1,ns.length()-pos);	
//	mongo_cmd_drop_collection( conn_,db.c_str(),tbl.c_str(), NULL );	
//	
//	log_->WriteLog(_DEBUG_L,before,"Drop();From="+ns);	
//}
