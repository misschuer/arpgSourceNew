#ifndef _LUA_HELPER_
#define _LUA_HELPER_

#include <comm/common_stl.h>
#include <comm/log.h>
#include <lua.hpp>
#include <core_obj/GuidObject.h>

#include <CCLuaStack.h>
#include <tolua/tolua++.h>

#include <object/BinLogObject.h>
#include <object/GuidManager.h>

extern "C" {
	int luaopen_robert_debugger(lua_State * L);
}
extern void lua_open_objects_manger(lua_State *L);
extern int luaopen_lua_http_binding (lua_State* tolua_S);
extern int luaopen_lua_item_binding(lua_State* tolua_S);

extern lua_State  *L;

/////////////////////////////////////////////////////////////////////////
//У��lua�����һЩ�궨��

int windows_lua_pcall(lua_State *L,  int nargs, int nresults, int p);
void check_lua_print_error(lua_State *L);
void check_lua_nil_parameter(lua_State *L);
lua_Number lua_check_tonumber(lua_State *L, int n);
lua_Integer lua_check_tointeger(lua_State *L, int n);
int lua_check_toboolean(lua_State *L, int n);
const char *lua_check_tolstring(lua_State *L, int n, size_t *len);
const char *lua_check_tostring(lua_State *L, int n);
void *lua_check_touserdata(lua_State *L, int n, EObjectTypePrefix t);

#if PLATFORM == PLATFORM_WINDOWS
#define LUA_PCALL(p1,p2,p3,p4) windows_lua_pcall(p1,p2,p3,p4)
#define CHECK_LUA_NIL_PARAMETER(L) check_lua_nil_parameter(L)
#define LUA_TONUMBER(L, n) lua_check_tonumber(L, n)
#define LUA_TOINTEGER(L, n) lua_check_tointeger(L, n)
#define LUA_TOBOOLEAN(L, n) lua_check_toboolean(L, n)
#define LUA_TOLSTRING(L, n, l) lua_check_tolstring(L, n, l)
#define LUA_TOSTRING(L, n) lua_check_tostring(L, n)
#define LUA_TOUSERDATA(L, n, t) lua_check_touserdata(L, n, t)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//lua obj to c binlog object

#else
#define LUA_PCALL(p1,p2,p3,p4) lua_pcall(p1,p2,p3,p4)
#define CHECK_LUA_NIL_PARAMETER(L)
#define LUA_TONUMBER(L, n) lua_tonumber(L, n)
#define LUA_TOINTEGER(L, n) lua_tointeger(L, n)
#define LUA_TOBOOLEAN(L, n) lua_toboolean(L, n)
#define LUA_TOLSTRING(L, n) lua_tolstring(L, n)
#define LUA_TOSTRING(L, n) lua_tostring(L, n)
#define LUA_TOUSERDATA(L, n, t) lua_touserdata(L, n)
#endif


//�ڲ�����
int __RandInt(lua_State *formulaL);
int __RandIntD(lua_State *formulaL);
int __RandIndex(lua_State *formulaL);
int lua_gettimeofday(lua_State *formulaL);

//ջ�Զ��ͷ�
struct LuaStackAutoPopup
{
	lua_State*    mBackupLS;
	int            mPos;
	LuaStackAutoPopup( lua_State* vpSL )
	{
		mPos    = lua_gettop( vpSL );
		mBackupLS    = vpSL;
	}

	void Popup( )
	{
		lua_settop( mBackupLS,mPos );
		mBackupLS    = NULL;
	}

	~LuaStackAutoPopup( )
	{
		if( mBackupLS )
			lua_settop( mBackupLS,mPos );
	}
};

template<typename T>
inline void lua_readvalue(lua_State *scriptL,const char* key,T& val)
{
	lua_getfield(scriptL,-1,key);
	val = static_cast<T>(LUA_TONUMBER(scriptL,-1));
	lua_pop(scriptL,1);
}

void lua_readvalue(lua_State *scriptL,const char* key,const char *& val);
void lua_readvalue(lua_State *scriptL,const char* key,char *val);

template<typename T>
void lua_readvalue(lua_State *scriptL,const int index,T& val)
{
	lua_rawgeti(scriptL, -1, index);
	val = static_cast<T>(LUA_TONUMBER(scriptL,-1));
	lua_pop(scriptL,1);
}

template<typename T,typename Func>
void lua_readvalue(lua_State *scriptL,const char* key,T& val,Func f)
{
	lua_getfield(scriptL,-1,key);
	f(scriptL, val);
	lua_pop(scriptL,1);
}

void lua_readvalue(lua_State *scriptL,const int index,const char *& val);
void lua_readvalue(lua_State *scriptL,const int index,string& val);
void lua_readvalue(lua_State *scriptL,const int index,char *val);
void lua_readvalue(lua_State *scriptL,const char* key,bool& b);
void lua_readvalue(lua_State *scriptL,const char* key,string& val);

template<typename T>
void lua_readvalue(lua_State *scriptL,const int index,T *ptr)
{
	lua_rawgeti(scriptL, -1, index);	
	int it = lua_gettop(scriptL);
	lua_pushnil(scriptL);
	//ASSERT(lua_type(scriptL,-1) == LUA_TTABLE);
	int i = 0;
	while(lua_next(scriptL, it))
	{
		ptr[i] = (T)LUA_TONUMBER(scriptL, -1);
		lua_pop(scriptL, 1);
		i++;
	}
	lua_pop(scriptL,1);
}

template<typename T>
void lua_readvalue(lua_State *scriptL,const int index,vector<T>& vec)
{
	lua_rawgeti(scriptL, -1, index);	
	lua_getvector(scriptL,vec);	
	lua_pop(scriptL,1);
}

template<typename T>
void lua_readvalue(lua_State *scriptL,const char* key,vector<T>& vec)
{
	lua_getfield(scriptL,-1,key);
	lua_getvector(scriptL,vec);	
	lua_pop(scriptL,1);
}

template<typename T,typename Func>
void lua_readvalue(lua_State *scriptL,const char* key,vector<T>& vec,Func f)
{
	lua_getfield(scriptL,-1,key);
	lua_getvector(scriptL,vec,f);	
	lua_pop(scriptL,1);
}

template<typename T,typename Func>
void lua_readvalue(lua_State *scriptL,const int index,vector<T>& vec,Func f)
{
	lua_rawgeti(scriptL, -1, index);
	lua_getvector(scriptL,vec,f);	
	lua_pop(scriptL,1);
}

void lua_getvector(lua_State *scriptL,vector<string>& vec);

template<typename T>
inline void lua_getvector(lua_State *scriptL,vector<T>& vec)
{
	vec.clear();
	int it_idx = lua_gettop(scriptL);
	lua_pushnil(scriptL);	
	while(lua_next(scriptL,it_idx))
	{
		vec.push_back((T)LUA_TONUMBER(scriptL,-1));
		lua_pop(scriptL,1);
	}
}

template<typename T,typename Func>
inline void lua_getvector(lua_State *scriptL,vector<T>& vec,Func func)
{
	T t;
	vec.clear();
	int it_idx = lua_gettop(scriptL);
	lua_pushnil(scriptL);	
	while(lua_next(scriptL,it_idx))
	{
		//memset(&t,0,sizeof(t));
		func(scriptL,t);
		vec.push_back(t);
		lua_pop(scriptL,1);
	}
}

int LuaGetBit(lua_State* scriptL);
int LuaSetBit(lua_State* scriptL);
int LuaUnSetBit(lua_State* scriptL);


//TODO: FIXME this SetInt16
#define LUA_BINLOG_REG_LIBNAME(BINLOG_T)	\
	{"GetBit",					&LuaGetBit<BINLOG_T>},\
	{"SetBit",					&LuaSetBit<BINLOG_T>},\
	{"UnSetBit",				&LuaUnSetBit<BINLOG_T>},\
	{"GetByte",					&LuaGetByte<BINLOG_T>},\
	{"SetByte",					&LuaSetByte<BINLOG_T>},\
	{"AddByte",					&LuaAddByte<BINLOG_T>},\
	{"SubByte",					&LuaSubByte<BINLOG_T>},\
	{"GetUInt16",				&LuaGetUInt16<BINLOG_T>},\
	{"SetUInt16",				&LuaSetUInt16<BINLOG_T>},\
	{"SetInt16",				&LuaSetInt16<BINLOG_T>},\
	{"AddUInt16",				&LuaAddUInt16<BINLOG_T>},\
	{"SubUInt16",				&LuaSubUInt16<BINLOG_T>},\
	{"GetUInt32",				&LuaGetUInt32<BINLOG_T>},\
	{"SetUInt32",				&LuaSetUInt32<BINLOG_T>},\
	{"AddUInt32",				&LuaAddUInt32<BINLOG_T>},\
	{"SubUInt32",				&LuaSubUInt32<BINLOG_T>},\
	{"GetInt32",				&LuaGetInt32<BINLOG_T>},\
	{"SetInt32",				&LuaSetInt32<BINLOG_T>},\
	{"AddInt32",				&LuaAddInt32<BINLOG_T>},\
	{"SubInt32",				&LuaSubInt32<BINLOG_T>},\
	{"GetDouble",				&LuaGetDouble<BINLOG_T>},\
	{"SetDouble",				&LuaSetDouble<BINLOG_T>},\
	{"AddDouble",				&LuaAddDouble<BINLOG_T>},\
	{"SubDouble",				&LuaSubDouble<BINLOG_T>},\
	{"GetFloat",				&LuaGetFloat<BINLOG_T>},\
	{"SetFloat",				&LuaSetFloat<BINLOG_T>},\
	{"GetStr",					&LuaGetStr<BINLOG_T>},\
	{"SetStr",					&LuaSetStr<BINLOG_T>},\
	{"ToString",				&LuaToString<BINLOG_T>},\
	{"GetUInt32Len",			&LuaGetUInt32Length<BINLOG_T>},\
	{"GetStrLen",				&LuaGetStrLength<BINLOG_T>},\
	{"SetBinlogMaxSize",		&LuaSetBinlogMaxSize<BINLOG_T>}

template<const struct luaL_reg _LIB[]>
int luaopen_lib(lua_State *L)
{
	string str = LUA_TOSTRING(L, -1);
	luaL_register(L, str.c_str(), _LIB);
	return 1;
}

//��lua�Ķ������������guid��ö���
int LuaGetObj(lua_State *L, const char* guid);
//��lua�Ķ����������ö����ִ�ж����е�ĳ������
int LuaGetObjFunc(lua_State *L, const char* guid, const char* func_name);

inline void NewLuaTable(lua_State *L, const char *table, void *ptr, const char *command)
{
	ASSERT(L && table && strlen(table) && ptr && command && strlen(command));

	//���ҵ���table
	lua_getglobal(L, table);
	ASSERT(lua_istable(L, -1));
	//��new����
	lua_getfield(L, -1, "new");
	lua_remove(L, -2);
	//new�ĵ�һ������ self
	lua_getglobal(L, table);
	//new�ĵڶ������� �µ�table
	lua_newtable(L);//����һ����񣬷���ջ��
	lua_pushstring(L, "ptr");//ѹ��key
	lua_pushlightuserdata(L, ptr);
	lua_settable(L,-3);//����key,value�������õ�table����ȥ
	//�ڶ��������㶨���������ˣ��᷵��һ��table
	if(LUA_PCALL(L, 2, 1, 0))
	{
		printf("new table error %s %s", table, command);
		return;
	}
	//�ҵ�Ҫ���õķ���
	lua_getfield(L, -1, command);
	//��new������table������ջ��
	lua_pushvalue(L, lua_gettop(L) - 1);
	//�󹦸��
}

extern int DoOpenMongodb(string connStr,string server_name);
extern int DoUpdateLua(uint32 diff);

#include <shared/lua_helper.h.inl>

#endif
