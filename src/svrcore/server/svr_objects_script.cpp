#include <shared/lua_helper.h>
#include "tolua++.h"
#include "tolua_fix.h"
#include "svr_object_manager.h"
#include <object/BinLogObject.h>

//////////////////////////////////////////////////////////////////////////
//LUA call c

namespace objects
{


//��������guid���ض���
static int luaGet(lua_State *L)
{
	const char *guid = luaL_checkstring(L,1);
	GuidObject *ptr = SvrObjectManager::self->Get(guid);
	if (ptr)
		lua_pushlightuserdata(L, (void*)ptr);
	else
		lua_pushnil(L);
	return 1;
}

//�������������ѯ���ʽ��������
static int luaForeach(lua_State *tolua_S)
{
	tolua_Error tolua_err; 
	
	if (!tolua_isstring(tolua_S,1, 0, &tolua_err) 
		|| !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
	{
		 tolua_error(tolua_S,"#ferror in function 'luaForeach'.",&tolua_err);
		 return 0;
	}

	const char* key = luaL_checkstring(tolua_S, 1);
	int f = toluafix_ref_function(tolua_S,2,0);
	SvrObjectManager::self->ForeachIndexer(key,[&](core_obj::GuidObject *obj){
		int statePos = lua_gettop( tolua_S );
		toluafix_get_function_by_refid(tolua_S,f);
		//tolua_pushusertype(tolua_S,(void*)self,"core_obj::LuaGuidObjectTable");
		tolua_pushcppstring(tolua_S, obj->guid());
		lua_pushlightuserdata(tolua_S,(void*)obj);
		lua_call(tolua_S,2,1); 
		bool result = tolua_toboolean(tolua_S,-1,0) != 0;
		lua_settop(tolua_S,statePos);		//�ָ�ջ��
		return result;
	});
	//ȥ���ú���������
	toluafix_remove_function_by_refid(tolua_S,f);
	return 0;
}

static int gAttachObjectt_delegate_index = 0;

// ���󴴽�ʱ����
static int luaRegisterAttachObject(lua_State *tolua_S)
{
	tolua_Error tolua_err; 
    if(!toluafix_isfunction(tolua_S, 1, "LUA_FUNCTION", 0, &tolua_err))
    {
		tolua_error(tolua_S,"#ferror in function 'RegisterAttachObjectt'.",&tolua_err);
        return 0;
    }
	if (gAttachObjectt_delegate_index)
		toluafix_remove_function_by_refid(tolua_S, gAttachObjectt_delegate_index);
	gAttachObjectt_delegate_index = toluafix_ref_function(tolua_S,1,0);
	ASSERT(gAttachObjectt_delegate_index);
    return 0;
}

static int gAfterAttachObjectt_delegate_index = 0;

// ȡ�ö���󸽼ӵ�������Ժ�ʱ����
static int luaRegisterAfterAttachObject(lua_State *tolua_S)
{
	tolua_Error tolua_err; 
	if(!toluafix_isfunction(tolua_S, 1, "LUA_FUNCTION", 0, &tolua_err))
	{
		tolua_error(tolua_S,"#ferror in function 'RegisterAttachObjectt'.",&tolua_err);
		return 0;
	}
	if (gAfterAttachObjectt_delegate_index)
		toluafix_remove_function_by_refid(tolua_S, gAfterAttachObjectt_delegate_index);
	gAfterAttachObjectt_delegate_index = toluafix_ref_function(tolua_S,1,0);
	ASSERT(gAfterAttachObjectt_delegate_index);
	return 0;
}

//�ͷŶ���ص�ί��
static int gReleaseObject_delegate_index = 0;

//�������ͷ�ʱ����
static int luaRegisterReleaseObject(lua_State *tolua_S)
{
	tolua_Error tolua_err; 
    if(!toluafix_isfunction(tolua_S, 1, "LUA_FUNCTION", 0, &tolua_err))
    {
		tolua_error(tolua_S,"#ferror in function 'RegisterReleaseObject'.",&tolua_err);
        return 0;
    }
	if (gReleaseObject_delegate_index)
		toluafix_remove_function_by_refid(tolua_S, gReleaseObject_delegate_index);
	gReleaseObject_delegate_index = toluafix_ref_function(tolua_S,1,0);
	ASSERT(gReleaseObject_delegate_index);
    return 0;
}

//����һ���¶���,����֪ͨԶ�̴���
static int luaNewAndCallPut(lua_State *tolua_S)
{
	tolua_Error tolua_err;
	if (!tolua_isstring(tolua_S,1, 0, &tolua_err))
	{
		tolua_error(tolua_S,"#ferror in function 'luaCreateObject'.",&tolua_err);
		return 0;
	}

	const char *guid = luaL_checkstring(tolua_S,1);
	const char *owner = luaL_checkstring(tolua_S,2);
	GuidObject *ptr = SvrObjectManager::self->Get(guid);
	if (ptr)
		return 0;			//�����ظ�����
	if (strlen(owner) == 0)
		return 0;			//owner����Ϊ��,��Ϊ���̵Ĵ洢�ǻ�����owner���з���
	
	BinLogObject* obj = new BinLogObject;
	obj->SetGuid(guid);
	obj->SetOwner(owner);
	SvrObjectManager::self->CallPutObject(obj);
	SvrObjectManager::self->CallSetTag(guid, owner);
	SvrObjectManager::self->InsertObjOwner(guid);		//���ش����Ķ���ֱ�ӷŽ�ȥ
	return 0;
}

//֪ͨԶ��ɾ������
static int luaCallRemoveObject(lua_State *tolua_S)
{
	tolua_Error tolua_err;
	if (!tolua_isstring(tolua_S,1, 0, &tolua_err))
	{
		tolua_error(tolua_S,"#ferror in function 'luaCallRemoveObject'.",&tolua_err);
		return 0;
	}

	const char *guid = luaL_checkstring(tolua_S,1);
	SvrObjectManager::self->CallRemoveObject(guid);
	return 0;
}

//��Ӽ���
static int luaCallAddWatch(lua_State *tolua_S)
{
	tolua_Error tolua_err;
	if (!tolua_isnumber(tolua_S, 1, 0, &tolua_err) || !tolua_isstring(tolua_S, 2, 0, &tolua_err))
	{
		tolua_error(tolua_S,"#ferror in function 'luaCallAddWatch'.",&tolua_err);
		return 0;
	}

	int fd = (int)tolua_tonumber(tolua_S, 1, 0);
	const char *guid = luaL_checkstring(tolua_S,2);
	SvrObjectManager::self->CallAddWatch(fd, guid);
	return 0;
}
	
//ɾ������
static int luaCallDelWatch(lua_State *tolua_S)
{
	tolua_Error tolua_err;
	if (!tolua_isnumber(tolua_S, 1, 0, &tolua_err) || !tolua_isstring(tolua_S, 2, 0, &tolua_err))
	{
		tolua_error(tolua_S,"#ferror in function 'luaCallDelWatch'.",&tolua_err);
		return 0;
	}

	int fd = (int)tolua_tonumber(tolua_S, 1, 0);
	const char *guid = luaL_checkstring(tolua_S,2);
	SvrObjectManager::self->CallDelWatch(fd, guid);
	return 0;
}

};

//////////////////////////////////////////////////////////////////////////
// C call Lua

using namespace objects;

//�����󸽼��Ǵ���
void DoOnAttachObject(GuidObject *obj)
{	
    if(L && gAttachObjectt_delegate_index != 0)
    {
		LuaStackAutoPopup autoPopup(L);
        toluafix_get_function_by_refid(L, gAttachObjectt_delegate_index );
        //TODO:��֤�����Ƿ���Ч
		tolua_pushcppstring(L, obj->guid());
        lua_pushlightuserdata(L, (void*)obj);
        lua_call(L, 2, 0);
    }
}

//�����󸽼��Ǵ���
void DoOnAttachObject(const string &account, GuidObject *obj)
{	
	if(L && gAttachObjectt_delegate_index != 0)
	{
		LuaStackAutoPopup autoPopup(L);
		toluafix_get_function_by_refid(L, gAttachObjectt_delegate_index );
		//TODO:��֤�����Ƿ���Ч
		tolua_pushstring(L, account.c_str());
		tolua_pushcppstring(L, obj->guid());
		lua_pushlightuserdata(L, (void*)obj);
		lua_call(L, 3, 0);
	}
}

//�����󸽼Ӻ󴥷�
void DoOnAfterAttachObject(const string &account, GuidObject *obj)
{	
	if(L && gAfterAttachObjectt_delegate_index != 0)
	{
		LuaStackAutoPopup autoPopup(L);
		toluafix_get_function_by_refid(L, gAfterAttachObjectt_delegate_index );
		//TODO:��֤�����Ƿ���Ч
		tolua_pushstring(L, account.c_str());
		lua_pushlightuserdata(L, (void*)obj);
		lua_call(L, 2, 0);
	}
}

//�����󸽼Ӻ󴥷�
void DoOnAfterAttachObject(GuidObject *obj)
{	
    if(L && gAfterAttachObjectt_delegate_index != 0)
    {
		LuaStackAutoPopup autoPopup(L);
        toluafix_get_function_by_refid(L, gAfterAttachObjectt_delegate_index );
        //TODO:��֤�����Ƿ���Ч
        lua_pushlightuserdata(L, (void*)obj);
        lua_call(L, 1, 0);
    }
}


//�������ͷ�ʱ�����ص�
void DoOnReleaseObject(GuidObject *obj)
{	
    if(L && gReleaseObject_delegate_index != 0)
    {
		LuaStackAutoPopup autoPopup(L);
        toluafix_get_function_by_refid(L, gReleaseObject_delegate_index);
        tolua_pushcppstring(L, obj->guid());
        lua_pushlightuserdata(L, (void*)obj);
        lua_call(L, 2, 0);
    }
}

//�������ͷ�ʱ�����ص�
void DoOnReleaseObject(const string &account, GuidObject *obj)
{	
	if(L && gReleaseObject_delegate_index != 0)
	{
		LuaStackAutoPopup autoPopup(L);
		toluafix_get_function_by_refid(L, gReleaseObject_delegate_index);
		tolua_pushstring(L, account.c_str());
		tolua_pushcppstring(L, obj->guid());
		lua_pushlightuserdata(L, (void*)obj);
		lua_call(L, 3, 0);
	}
}

//ע��������lua�ӿ�
void lua_open_objects_manger(lua_State *L)
{
	int startPos = lua_gettop(L);
    luaL_Reg l[] = {
        {"get", luaGet},
        {"foreach",                 luaForeach},
        {"registerAttachObject",    luaRegisterAttachObject},
		{"registerAfterAttachObject",luaRegisterAfterAttachObject},
        {"registerReleaseObject",   luaRegisterReleaseObject},
		{"newAndCallPut",			luaNewAndCallPut},		
		{"callRemoveObject",		luaCallRemoveObject},
		{"callAddWatch",			luaCallAddWatch},
		{"callDelWatch",			luaCallDelWatch},
        {NULL, NULL}
    };
    luaL_register(L, "objects", l);	
	lua_settop(L,startPos);
}


