#include "policed_app.h"
#include "policed_context.h"
#include "policed_script.h"
#include <shared/log_handler.h>
#include <shared/storage_loader.h>

LuaStack *gLuaStack = NULL;
lua_State *L = NULL;
const char *sdir = NULL;

static const struct luaL_reg mylib[] = 
{
	{"outString",			__outString<PolicedApp>},
	{"outDebug",			__outDebug<PolicedApp>},
	{"outError",			__outError<PolicedApp>},

	//�������
	{"randInt",				__RandInt},
	{"randIntD",			__RandIntD},
	{"randIndex",			__RandIndex},

	{"getBit",				&LuaGetBit},
	{"setBit",				&LuaSetBit},
	
	{NULL, NULL} /* sentinel */ 
};

extern const struct luaL_reg LBinLog[] =
{
	LUA_BINLOG_REG_LIBNAME(BinLogObject),
	{NULL, NULL} /* sentinel */ 
};

static const struct luaL_reg mylibname[] = 
{
	{"binLogLib",			luaopen_lib<LBinLog>},
	{NULL, NULL} /* sentinel */ 
};


int scripts_init(const char *_sdir)
{
	int status;    
	char sfile[500];

	/*����һ��ָ��Lua��������ָ�롣*/
	gLuaStack = new LuaStack;
	gLuaStack->init();
	L = gLuaStack->getLuaState();

	if(_sdir != NULL)
		sdir = _sdir;

	/*��������Lua��*/
	luaL_openlibs(L);		
	//�����������װ�ӿ�
	lua_open_objects_manger(L);
	/////////////////////////////////////////////////////////////////
	//			ע��
	////////////////////////////////////////////////////////////////
	for(const luaL_reg *ptr = mylib;ptr->name != NULL;ptr++)
		lua_register(L,ptr->name,ptr->func);
	for (const luaL_reg * lib = mylibname; lib->func; lib++) {
		lua_pushcfunction(L, lib->func);
		lua_pushstring(L, lib->name);
		lua_call(L, 1, 0);
	}
	
	sprintf(sfile,"package.path = package.path .. ';%s/?.lua'",_sdir);
	luaL_dostring(L,sfile);		
	sprintf(sfile,"__SCRIPTS_ROOT__='%s'",_sdir);		/*���ű���·��ע���lua��*/
	luaL_dostring(L,sfile);
	/////////////////////////////
	//		  ���ؽű�
	/////////////////////////////

	/*���ؽű�*/    
	sprintf(sfile, "%s/cow_policed.lua", sdir);
	tea_pinfo("load script %s", sfile);
	if((status = luaL_dofile(L, sfile)))
	{
		tea_perror("����ű� %s ����!", sfile);
		tea_perror("%s!\n", LUA_TOSTRING(L, -1)); /* ע��printf��Ҫ��ӡ������Ϣ�ˣ���Ϊlua�ĳ�����Ϣ�Ѿ������� */
		lua_pop(L, 1);
		scripts_free();
		ASSERT(0);			//�ű�ʧ�ܣ������ˣ�ֱ�ӹҰ�
		return status;
	}

	DoGetConfig();	
	ASSERT(lua_gettop(L) == 0);//��Ҫ�в���
	return 0;
}

int scripts_free()
{
	if(gLuaStack != NULL)
	{
		delete gLuaStack;
		gLuaStack = NULL;
		L = NULL;
	}

	return 0;
}

int scripts_reload()
{
	scripts_free();
	scripts_init(g_Config.script_folder.c_str());
	PolicedApp::g_app->RegSessionOpts();
	return 0;
}

//---------------------------------------------------------------------------------------------/
//��ȡ������Ϣ
int DoGetConfig()
{
	{
		LuaStackAutoPopup autoPopup(L);

		lua_getglobal(L,"config");
		if(!lua_istable(L,-1))
		{
			tea_perror("lua�ű����Ҳ���������Ϣ");
			return -1;
		}
		lua_readvalue(L, "game_code", g_Config.game_code);
		lua_readvalue(L,"external_router_map",			PolicedApp::g_app->m_opts, [](lua_State *scriptL, uint16 &op_code){
			op_code = (uint16)LUA_TOINTEGER(scriptL, -1);
			ASSERT(op_code);
		});
		lua_readvalue(L,"pk_external_router_map",			PolicedApp::g_app->m_pk_opts, [](lua_State *scriptL, uint16 &op_code){
			op_code = (uint16)LUA_TOINTEGER(scriptL, -1);
			ASSERT(op_code);
		});
	}
	{
		LuaStackAutoPopup autoPopup(L);
		lua_getglobal(L,"post_chat");
		g_Config.post_chat = LUA_TOBOOLEAN(L, 1) == TRUE;
	}
	//��ȡƽ̨��Ϸ����
	GetPlatFormGameCode();
	
	return 0;
}

//��ȡƽ̨��������
bool GetPlatFormGameCode()
{
	//����ƽ̨��ȡgame_code
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L,"PlatfromGameCodeTable");
	if(lua_istable(L,-1) && PolicedApp::g_app->m_gameconfig)
	{			
		lua_getfield(L,-1,PolicedApp::g_app->GetPlatformID().c_str());
		if(!lua_isnil(L,-1))
			g_Config.game_code = lua_tostring(L, -1);
		tea_pinfo("load platform gamecode [%s] ", g_Config.game_code.c_str());
		return true;
	}

	return false;
}

//���¶�ȡ�����ļ�
int LuaLoadConfig(lua_State* scriptL)
{
	DoGetConfig();
	return 0;
}

//GM�����KEYת��
int GetGmCommandKey(string &gm_str)
{
	LuaStackAutoPopup autoPopup(L);
	lua_getglobal(L, "GetGmCommandKey");
	lua_pushstring(L, gm_str.c_str());		
	if(LUA_PCALL(L, 1, 1, 0))
	{
		tea_perror("GetGmCommandKey  ERROR");
		return 0;
	}
	return (int)LUA_TONUMBER(L,-1);
}

int GetPlatfromPostType(vector<string> &vec)
{
	LuaStackAutoPopup autoPopup(L);

	lua_getglobal(L,"PlatfromPostTable");
	if(!lua_istable(L,-1))
	{
		tea_perror("PlatfromPostTable not find");
		return -1;
	}

	lua_getfield(L,-1,PolicedApp::g_app->GetPlatformID().c_str());
	if(!lua_istable(L,-1))	
		return 0;
	lua_getvector(L,vec);	
	lua_pop(L,1);

	return 0;
}

int DoGetPostUrl(const string &plat_id, map<uint32,string> &m)
{
	ASSERT(PolicedApp::g_app->m_gameconfig);
	LuaStackAutoPopup autoPopup(L);

	lua_getglobal(L,"PostUrlTable");
	if(!lua_istable(L,-1))
	{
		tea_perror("PostUrlTable not find");
		return -1;
	}
	lua_getfield(L,-1,plat_id.c_str());
	int idx = lua_gettop(L);
	lua_pushnil(L);
	while(lua_next(L, idx) != 0){
		m[LUA_TOINTEGER(L, -2)] = LUA_TOSTRING(L, -1);
		lua_pop(L,1);
	}
	return 0;
}

bool LoadTemplate()
{
	tea_pinfo("\n\n������Ʒ��");
	if(!Load_item_template(L))
	{
		tea_pinfo("\n\n������Ʒ��ʧ��.");
		return false;
	}

	tea_pinfo("\n\n������Ʒ��");
	if(!Load_goods(L))
	{
		tea_pinfo("\n\n������Ʒ��ʧ��.");
		return false;
	}
	return true;
}
