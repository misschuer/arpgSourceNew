#ifndef _SCENED_CONTEXT_H_
#define _SCENED_CONTEXT_H_

#include "appd_app.h"
#include <object/SharedDef.h>
#include <object/PlayerBase.h>
#include <vector>

class ItemManager;

//��������ʱ������ʱ��
#define  ONLING_TIME     60000

typedef std::map<uint16, uint16> PassiveIndexMap;
typedef std::map<uint16, uint8> SpellLevelMap;
typedef std::list<uint16> SupportSpellList;
typedef std::map<string, int16> SocialMap;

#define EXPIRE_SHIFT 8

//Ӧ�÷��Ự ��������Ϣ
class AppdContext:public PlayerBase,public SvrContext
{
	//��̬
public:
	static AppdContext *FindPlayer(const string &guid);	
	static AppdContext *FindAccount(const string &account);
	typedef UNORDERED_MAP<string, AppdContext*> ContextStrMap;
	static ContextStrMap AccountMaps;

	// ���Ƽ����������ȼ�ά���б�
	typedef std::map<uint8, std::set<string>> RecommendMap;
	static RecommendMap m_recommend;
	
	static int LuaGetAndSendRecommendFriends(lua_State* scriptL);	//��ȡ�Ƽ�����
	static int luaFastGetFactionList(lua_State* scriptL);	//��ȡ�����б�
	static void GetRecommendFriendGuid(vector<string>& ret, const string& guid);
	static void LevelChanged(const string& guid, uint32 prevLevel, uint32 currLevel);
	static void AddNew(const string& guid, uint32 currLevel);
	static void RemoveOld(const string& guid, uint32 prevLevel);

	static int luaSetCultivation(lua_State* scriptL);
	static int luaSetCultivationByIndexValue(lua_State* scriptL);
	static int luaGetCultivation(lua_State* scriptL);
	
public:
	AppdContext(int fd,ContextManager *mgr);
	virtual ~AppdContext();

	//����·��,��ʼ��
	void OpcodeHandlerInitor();
	void InsertPlayerMap();		//��guidΪkeyά��������һ��context��	
	void RemovePlayerMap();

	void Update(uint32 diff);

	bool Login(uint32 fd);
	void Logout();

	void online();
	void offline();

	int OnLevelChanged();

	int OnForceChanged();

	//�������
	double GetMoney(uint16 type);
	void addMoney(uint8 type, uint8 oper_type, double val, const string &trace_id = "", uint32 p1 = 0, uint32 p2 = 0, uint8 item_bind = 0, uint8 item_del = 0);
	bool subMoney(uint8 type, uint8 oper_type, double val, const string &trace_id = "", uint32 p1 = 0, uint32 p2 = 0, uint8 item_bind = 0, uint8 item_del = 0);

	//����Ԫ��������Ϣ
	void SaveGoldLog(const string &account, const string &player_id,  const string &player_name, uint16 money_type, uint16 oper_type,
		double v,double old_value, double new_value, const string &trace_id, uint32 item_id, uint32 count, 
		double unit_price,uint16 item_bind, uint16 item_del, uint32 level, uint32 quest);


	//��ҵ�¼����ʲô
	int DoPlayerLogin();
	//�����������ʲô
	int DoPlayerLogout();
	// �ж��Ƿ�������
	bool isFriend(const string& fguid);

	void OnAddFirstQuest();

protected:
	void Handle_LUA(packet& pkt);

	void Handle_Rank_List_Query(packet& pkt);			//�������а���Ϣ

	void Handle_Char_Remotestore(packet& pkt);			//����ͻ���������Ϣ
	void Handle_Char_Remotestore_Str(packet& pkt);		//����ͻ���������Ϣ

	void Handle_Syns_Mstime(packet& pkt);			//ͬ��ʱ��
public:
	void Call_Operation_Failed(uint16 type,uint16 reason, string data = "");						//����ʧ��
public:
	// ��������indexӳ��
	PassiveIndexMap m_PassiveIndex;
	
	// ���ܶ�Ӧ�ĵȼ�
	SpellLevelMap m_SpellLevel;

	// ���������б�
	SupportSpellList l_supportSpell;

	SocialMap l_socialFriendMap;
	SocialMap l_socialEnemyMap;
	
	// �״ε�¼ͬ����ʼ����
	void firstLoginAndCopySpellInfoToGuidObject(GuidObject* obj);

	void firstLoginAndInitQuestGuidObject();
	
	//������ʱ������Ϣ ����Ӧ�÷��������߼�
	void generateTempSpellLevelInfo(GuidObject* obj);

	//������ʱ��������binlogλ����Ϣ
	void generatePassiveIndexInfo();

	// ���ɸ���������Ϣ
	void mapSupportSpell(uint16 spellId, uint8 spellLv);


	void SetCalculFlag()
	{
		m_isCanRecalcul = true;
	}
private:
	bool m_isCanRecalcul;						//�Ƿ��������
	//���㲢�·�װ��/�������ԡ����ܡ�BUFF
	void SendEquipAttrs();						//ps���������ڲ�ʹ��

	void NewOtherBinlog();
	void NewOtherBinlog(const string new_guid, uint32 flag, std::function<BinLogObject*()> create_fun = nullptr);
	void NewOtherBinlog(EObjectTypePrefix t, uint32 flag, std::function<BinLogObject*()> create_fun = nullptr);
	void CreateOtherBinlog(const string new_guid, uint32 flag, std::function<BinLogObject*()> create_fun = nullptr);

private:
	//Ǯ���
	vector<double> m_all_money;
public:
	static int LuaGetPlayer(lua_State* scriptL);			//ͨ��GUID��ȡ���ʵ��
	static int LuaOfflineOper(lua_State *scriptL);			//����������ң�����ĳЩ��

	static int LuaWriteForgeLog(lua_State* scriptL);		//������־
	static int LuaHTForgeLog(lua_State* scriptL);			//д��̨����������־
	
	static int LuaModifyMoney(lua_State* scriptL);			//�޸Ľ�Ǯ
	static int LuaGetMoney(lua_State* scriptL);			//��ȡ��Ǯ
		
	static int LuaSendAttr(lua_State* scriptL);					//����װ��/�������ԡ����ܡ�BUFF

	static int LuaSendScenedConsumeMoney(lua_State* scriptL);	//ʹ��Ԫ��֪ͨ��������Щʲô
	static int LuaSendLoginHosting(lua_State* scriptL);		//֪ͨ��½���йܵ�¼

	static int LuaGetFD(lua_State* scriptL);	// �ű���ûỰ

	static int LuaGetPassiveIndex(lua_State* scriptL);	//��ʱû�� ��ñ�������id��Ӧ��binlogλ��
	static int LuaUpdatePassive(lua_State* scriptL);	//���±������ܵ���Ϣ
	static int LuaUpdateSlotSpell(lua_State* scriptL);	//���¼��ܲۼ��ܵ���Ϣ
	
	static int LuaActiveDivineSpell(lua_State* scriptL);//����������ܵ���Ϣ

	static int LuaAddSupportSpell(lua_State* scriptL);	//���ӱ�������

	static int LuaGetSpellLevel(lua_State* scriptL);	//��ü���id��Ӧ�ĵȼ�
	static int LuaSetSpellLevel(lua_State* scriptL);	//���ü���id��Ӧ�ĵȼ�

	static int LuaGetSocialFriend(lua_State* scriptL);//��ȡ���� index
	static int LuaSetSocialFriend(lua_State* scriptL);//���ú��� index
	static int LuaGetSocialEnemy(lua_State* scriptL);//��ȡ���� index
	static int LuaSetSocialEnemy(lua_State* scriptL);//���ú��� index

	static int LuaGetDesignatedSkillLevel(lua_State* scriptL);	//���ָ�����ܵȼ�

	static int LuaCheckPlayerIsLogined(lua_State* scriptL);	// �ж�����Ƿ��Ѿ���¼

	static int __LuaAddString(lua_State* scriptL, vector<string> &ret);
};


#endif
