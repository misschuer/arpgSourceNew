#ifndef _GUID_MANAGER_H_
#define _GUID_MANAGER_H_

#include <object/BinLogObject.h>
#include <svrcore-internal.h>
#include <comm/cstr_util.h>

//////////////////////////////////////////////////////////////////////////
//���ж��������ö��
enum EObjectTypePrefix
{
	ObjectTypeNone = ' ',			//��Ч��ǰ׺

	ObjectTypeAccount = 'A',		//�˻���Ϣ
	ObjectTypeGlobalValue = 'G',	//ȫ�ֶ���
	ObjectTypeGroup = 'T',			//���

	ObjectTypeUnit = 'U',			//����
	ObjectTypePlayer = 'p',			//���
	ObjectTypeItemMgr = 'I',		//��Ʒ
	ObjectTypeLimit = 'l',			//��ʱ�����
	ObjectTypeSocial = 's',			//�罻
	ObjectTypeQuest = 'Q',			//����
	ObjectTypeLogical = 'B',		//ҵ���߼�
	ObjectTypeSpell	= 'X',			//����
	ObjectTypeFaction = 'L',		//����
	ObjectTypeFactionData = 'D',	//��������
	ObjectTypeGiftPacks = 'g',		//���
	ObjectTypePKinfo	= 'k',		//���PK��¼	
	ObjectTypeMap					= 'M',			//��ͼ����
	ObjectTypeGridLoot				= 'O',			//��ͼ�ϵ�gridս��Ʒ��Ϣ
	ObjectTypeInstance				= 'C',			//����

	ObjectTypeMapPlayerInfo = 'u',	//�����ͼʵ����Ϣ(Ŀǰ��Ҫ����������б�),ǰ׺���ù��ˣ�������͵��ð�

	//���´�����Ϊ�˽��û��ƣ����Ը�Щ���Ŵ���
	ObjectTypeMapInstance = '#',	//��ͼʵ����id����
	ObjectTypeGMCommand	 = '@',		//GM�������
};

#define SUB_GUID_STR_TO_INT(g) g.substr(1, g.find('.'))

//���ݴ��͵�guidȡ�ö�guid,һ������unit
inline uint32 shortGUID(const char* s)
{
	char c;
	uint32 t;
	if (s == nullptr) {
		return 0;
	}
	sscanf(s,"%c%d.",&c, &t);
	return t;
}

class GuidManager
{
public:
	GuidManager();
	~GuidManager();
public:
	//���ﲻ��������ڴ�Ŷ
	const char* MAKE_NEW_GUID(EObjectTypePrefix prefix,uint32 index,const char *suffix);	

	inline string NewGUID(EObjectTypePrefix prefix,uint32 index,const char *suffix)
	{
		return MAKE_NEW_GUID(prefix,index,suffix);
	}

	inline const char* MAKE_NEW_GUID(EObjectTypePrefix prefix,string suffix = "")
	{
		return MAKE_NEW_GUID(prefix,NewIndex(prefix),suffix.c_str()); 
	}

	static EObjectTypePrefix GetPrefix(const string& str)
	{
		return GetPrefix(str.c_str());
	}

	static EObjectTypePrefix GetPrefix(const char* guid)
	{
		if(guid[0]=='\0')
			return ObjectTypeNone;
		return EObjectTypePrefix(guid[0]);
	}
	
	inline const char* GetSuffixFromGUID(const char* guid)
	{
		char *s = cstr_read_token((char*)guid,'.');
		return s;
	}

	//����GUID�е�����
	inline const char* GetJumpNo(const char* guid);


	static string ReplaceSuffix(const string& guid,EObjectTypePrefix t);

	static string ScenePrefixRegex(const string& guid);

	//
	uint32 NewIndex(EObjectTypePrefix t);

	void LoadMyData();
	void SyncMaxGuid(uint32 player_max);	//ͬ��guid�ۼ����ֵ
	void SetUnitGuid(uint32 unit_id);
public:
	BinLogObject *m_data;		//guid��������

private:
	BinLogObject *m_my_data;
	char m_tmp[128];
};

#endif
