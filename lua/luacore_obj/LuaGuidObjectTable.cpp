#include "LuaGuidObjectTable.h"
#include <tolua++.h>
#include <tolua_fix.h>

namespace core_obj {


//////////////////////////////////////////////////////////////////////////
//for GuidObjectTable
LuaGuidObjectTable::LuaGuidObjectTable():GuidObjectTable(SYNC_SLAVE),lua_create_object_callback_index_(0),lua_attach_object_callback_index_(0),lua_release_object_callback_index_(0),tolua_S_(0)
{
}

LuaGuidObjectTable::~LuaGuidObjectTable(){
	if (tolua_S_ && lua_create_object_callback_index_)
	{
		toluafix_remove_function_by_refid(tolua_S_,lua_create_object_callback_index_);
		lua_create_object_callback_index_ = 0;
	}
	objs_.clear();	//�ڴ���lua���й���
};

void LuaGuidObjectTable::RegisterCreateObject(lua_State *tolua_S,unsigned int callback_idx)
{
	tolua_S_ = tolua_S;
	lua_create_object_callback_index_ = callback_idx;
}

void LuaGuidObjectTable::RegisterAttachObject(lua_State *tolua_S,unsigned int callback_idx)
{
	tolua_S_ = tolua_S;
	lua_attach_object_callback_index_ = callback_idx;
}

void LuaGuidObjectTable::RegisterReleaseObject(lua_State *tolua_S,unsigned int callback_idx)
{	
	tolua_S_ = tolua_S;
	lua_release_object_callback_index_ = callback_idx;
} 

GuidObject* LuaGuidObjectTable::CreateObject(string guid) 
{     
	GuidObject *obj = nullptr; 
	if(tolua_S_ && lua_create_object_callback_index_){
		int statePos = lua_gettop(tolua_S_);
		toluafix_get_function_by_refid(tolua_S_,lua_create_object_callback_index_);
		if(lua_isfunction(tolua_S_,-1)){ 
			//ֻ��һ�������ǰ�
			tolua_pushusertype(tolua_S_,(void*)this,"core_obj::LuaGuidObjectTable");
			tolua_pushcppstring(tolua_S_,guid);

			//TODO:����Ӧ��ʹ�ð�ȫ����
			lua_call(tolua_S_,2,1); 
			obj = (GuidObject *)tolua_tousertype(tolua_S_,-1,NULL);
			if (obj)
			{
				obj->guid(guid);
				AttachObject(obj);
			}
		}
		//��ջ��ԭ��
		lua_settop(tolua_S_,statePos);	
	}		

	return obj;
}

void LuaGuidObjectTable::AttachObject(GuidObject* obj)
{
	GuidObjectTable::AttachObject(obj);
	if(tolua_S_ && lua_create_object_callback_index_){
		int statePos = lua_gettop( tolua_S_ );
		toluafix_get_function_by_refid(tolua_S_,lua_attach_object_callback_index_);
		if(lua_isfunction(tolua_S_,-1)){
			//TODO:����Ӧ��ʹ�ð�ȫ����	
			tolua_pushusertype(tolua_S_,(void*)this,"core_obj::LuaGuidObjectTable");
			tolua_pushusertype(tolua_S_,(void*)obj,"core_obj::GuidObject");
			lua_call(tolua_S_,2,0);
		}
		lua_settop(tolua_S_,statePos);
	}	
}

void LuaGuidObjectTable::ReleaseObject(string guid)
{ 
	if(tolua_S_ && lua_release_object_callback_index_){
		int statePos = lua_gettop( tolua_S_ );
		toluafix_get_function_by_refid(tolua_S_,lua_release_object_callback_index_);
		if(lua_isfunction(tolua_S_,-1)){
			//TODO:����Ӧ��ʹ�ð�ȫ����	
			tolua_pushusertype(tolua_S_,(void*)this,"core_obj::LuaGuidObjectTable");
			tolua_pushcppstring(tolua_S_,guid);
			lua_call(tolua_S_,2,0);
		}
		//��ջ��ԭ�� 
		lua_settop(tolua_S_,statePos);		 
	}
	//GuidObjectTable::ReleaseObject(guid);
	//�ӿ���ڴ滹�ǽ���lua�������
	auto *p = Get(guid);
	if(!p)
		return;
	DetachObject(p);
}


//�������ж���
void LuaGuidObjectTable::ForeachIndexer(const string& key,std::function<bool(GuidObject*)> f)
{
	//���keyΪ��,��򵥱������ж���
	if(key.empty())
	{
		for (auto it = objs_.begin();it != objs_.end();++it)
		{
			if(f(it->second))
				return;		
		}
		return;
	}

	auto idx = indexer_.get(key);
	if(idx)
	{
		for (auto it = idx->begin();it != idx->end();++it)
		{
			if(f(it->second))
				return;
		}
	}
	else if(objs_.count(key) == 1)
	{
		f(Get(key));
	}
	else
	{		
		Regex e(key);	
		for (ValueHashMap::iterator it = objs_.begin();it != objs_.end();++it)
		{
			if(e.Search(it->first) && f(Get(it->first)))
				return;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//for LuaGuidObject
LuaGuidObject::LuaGuidObject(SyncMode m_,const string& key ):GuidObject(SYNC_SLAVE),tolua_S_(0),after_update_hanlder(0)
{
}
LuaGuidObject::~LuaGuidObject()
{
	for (auto it = scriptHanlders_.begin();it != scriptHanlders_.end();++it) {
		toluafix_remove_function_by_refid(tolua_S_,it->second);
	}
	scriptHanlders_.clear();
	if (after_update_hanlder) {
		toluafix_remove_function_by_refid(tolua_S_,after_update_hanlder);
		after_update_hanlder = 0;
	}
}	

bool LuaGuidObject::DoCallback(uint32_t cb_idx,BinLogStru *binlog)
{
	bool ret = false;
	int statePos = lua_gettop( tolua_S_ );
	toluafix_get_function_by_refid(tolua_S_,cb_idx);
	if(lua_isfunction(tolua_S_,-1)){
		//ֻ��һ�������ǰ�
		tolua_pushusertype(tolua_S_,(void*)binlog,"core_obj::BinLogStru");
		//TODO:����Ӧ��ʹ�ð�ȫ����
		lua_call(tolua_S_,1,1);
		ret = lua_toboolean(tolua_S_,-1)!=0;
	}
	//��ջ��ԭ��
	lua_settop(tolua_S_,statePos);	
	return ret;
}

//ע��ص�
void LuaGuidObject::RegisterHanlder(lua_State *tolua_S, int index, uint32_t callback_idx)
{
	ASSERT(tolua_S_ == nullptr || tolua_S_ == tolua_S);
	auto f = [this](core_obj::BinLogStru *binlog){
		int index = binlog->index;
		//������ַ�����ת�ɸ���
		if(binlog->typ == TYPE_STRING)
			index *= -1;
		auto it = scriptHanlders_.lower_bound(index);
		auto end = scriptHanlders_.upper_bound(index);
		while (it != end)
		{
			//���ִ�еĽ������true���Ƴ�
			if(DoCallback(it->second,binlog)){
				toluafix_remove_function_by_refid(tolua_S_,it->second);
				scriptHanlders_.erase(it++);
			}else ++it;
		}			
	};

	//����ǵ�һ�μ�������±�ĸ�������Ҫ����ص���������Ҫ
	if(scriptHanlders_.count(index) == 0){
		if(index < 0 )
			events_str_value_.AddCallback(-1*index,f);
		else
			events_value_.AddCallback(index,f);
	}
	scriptHanlders_.insert(std::make_pair(index,callback_idx));
}

void  LuaGuidObject::UnRegisterHanlder(uint32_t callback_idx)
{		
	auto it = scriptHanlders_.begin();
	auto end = scriptHanlders_.end();
	while (it != end) {
		//���ִ�еĽ������true���Ƴ�
		if(it->second == callback_idx) {				
			toluafix_remove_function_by_refid(tolua_S_,it->second);
			//��������һ����ɾ��
			if(scriptHanlders_.count(it->first) == 1){
				if(it->first < 0 )
					events_str_value_.DelCallback(-1*it->first);
				else
					events_value_.DelCallback(it->first);
			}				
			scriptHanlders_.erase(it++);
			break;
		}else ++it;
	}
}

//ȥ���ص�,���index����
void LuaGuidObject::UnRegisterHanlderByIndex(int index)
{
	//���index����0��ɾ��callback_idx		
	auto it = scriptHanlders_.lower_bound(index);
	auto end = scriptHanlders_.upper_bound(index);
	while (it != end) {
		//���ִ�еĽ������true���Ƴ�				
		toluafix_remove_function_by_refid(tolua_S_,it->second);	
		scriptHanlders_.erase(it++);
	}
	if(index<0)
		events_str_value_.DelCallback(-1*index);
	else
		events_value_.DelCallback(index);
}

void LuaGuidObject::RegisterAfterUpdate(lua_State *tolua_S,uint32_t callback_idx)
{
	ASSERT(tolua_S_ == nullptr || tolua_S_ == tolua_S);
	tolua_S_ = tolua_S;

	//���callback_idx����0����Ϊɾ��
	if(callback_idx == 0){
		if (after_update_hanlder) {
			toluafix_remove_function_by_refid(tolua_S_,after_update_hanlder);
			after_update_hanlder = 0;
		}
		after_update(nullptr);
		return;
	}

	after_update_hanlder = callback_idx;
	this->after_update([this](core_obj::SyncEventRecorder* obj,int flags,core_obj::UpdateMask& intMask,core_obj::UpdateMask& strMask){
		int statePos = lua_gettop( tolua_S_ );
		toluafix_get_function_by_refid(tolua_S_,after_update_hanlder);
		if(lua_isfunction(tolua_S_,-1)){ 
			tolua_pushusertype(tolua_S_,(void*)obj,"core_obj::LuaGuidObject");
			tolua_pushnumber(tolua_S_, flags);
			tolua_pushusertype(tolua_S_,(void*)&intMask,"core_obj::UpdateMask");
			tolua_pushusertype(tolua_S_,(void*)&strMask,"core_obj::UpdateMask");
			//TODO:����Ӧ��ʹ�ð�ȫ����
			lua_call(tolua_S_,4,0);
		}
		//��ջ��ԭ��
		lua_settop(tolua_S_,statePos);
	});		
}


}
