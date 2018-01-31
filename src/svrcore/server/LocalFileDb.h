#ifndef _LOCALFILEDB_H_
#define _LOCALFILEDB_H_
//�����ļ��洢�ı������ݿ�
#include "Storage.h"

#define FILEDB_SEP "#LHS#"								//�����ļ��洢ʱ�ķָ��
#define FILEDB_BINLOG_SEP "#BLOG#"					//binlog�ļ��洢ʱ�ķָ��
#define FILEDB_FILENAME_KEYMAP "FILENAME_KEYMAP.txt"	//ÿ���ļ���Ӧ��key�洢�ļ���
#define FILEDB_FILENAME_CURSOR "FILENAME_CURSOR.txt"	//�α��ļ���
#define FILEDB_EXT_NAME ".blg"							//�ļ���׺

class LocalFileDb
{
public:
	typedef std::map<string,string> Map;	
	typedef std::vector<Map> Results;
	typedef std::vector<Map> Values;
	typedef std::map<string, vector<string>> KeyMap;
	typedef std::map<string,bool> SaveMap;

	enum OPT_TYPE
	{
		OPT_TYPE_ADD			= 0,		//���
		OPT_TYPE_DEL			= 1,		//ɾ��
		OPT_TYPE_UPDATE			= 2,		//����
	};
public:
	LocalFileDb(const string& dbpath);
	virtual ~LocalFileDb(void);

	/* �����ļ�����������
	@fname:�ļ���
	@results:���ؽ��������
	@return:true�ɹ���falseʧ��
	*/
	bool Load(const string& fname, Results& results);
	
	/* ���Ǳ����ļ�����
	@fname:�ļ���
	@values:Ҫ�������
	@return:true�ɹ���falseʧ��
	*/
	bool Save(const string& fname, const Values& values);

	/* ����һ���ļ�����
	@fname:�ļ���
	@value:Ҫ��ӵ�����
	@return:true�ɹ���falseʧ��
	*/
	bool Add(const string& fname, const Map& value);

	/* ���һ��binlog����
	@fname:�ļ���
	@opt_type:��������
	@value:Ҫ��ӵ�����
	@return:true�ɹ���falseʧ��
	*/
	bool AddBinlog(const string& fname, const OPT_TYPE &opt_type, const Map& value);

	/* ��ȡbinlog�ļ������з��أ�
	@fname:�ļ���
	@func:�ص�����
	@return:void
	*/
	void ReadBinlog(const string& fname, std::function<void (const OPT_TYPE opt_type, Map& m)> func);

	/* ��ʱ�����ļ��������������ļ� (�ļ��е���������Ч,Ҫ���������ļ��Ѿ�������Ḳ�ǵ�)
	@fname:�ļ���
	@return:true�ɹ���falseʧ��
	*/
	bool Rename(const string &fname);

	/* ɾ��binlog�ļ�
	@fname:�ļ���
	@return:true�ɹ���falseʧ��
	*/
	bool Remove(const string& fname);								

	/* ��map����ת���ɴ洢����
	@fname:�ļ���
	@value:Ҫת����map����
	@content:ת���������
	@return:void
	*/
	void ToString(const string& fname, const Map &value, string& content);

	/* ���ַ�������ת����map����
	@fname:�ļ���
	@content:Ҫת��������
	@value:ת���������
	@return:void
	*/
	void FromString(const string& fname, const string& content, Map &value);	

	//�Ƿ���Ҫ����data true:���� false:������
	bool IsSaveData(const string& fname);
	
	//���keymap���ݴ�
	void GetKeyMapStr(const string& fname, string &str);

	//��map����ת���ɴ洢��
	void ToMapString(const string& fname, const Values& values, string &ret_str);
	//���ַ���ת����Map
	void FromMapString(const string& keymap_str, const string& src_str, Values &values);

	core_obj::Storage* GetStorage(){return m_storage;}
private:
	bool SaveKeyMap();							//����ÿ���ļ���key
	bool LoadKeyMap();							//����ÿ���ļ���key
	void SetSave(const string &fname, bool issave = true);		//���ñ���

	static string GetLocalDataFN(const string &name){return name+"_data"+FILEDB_EXT_NAME;}			//��������ļ�(����ļ��Ĵ��ڷ�ֹ����temp��ʱ��ʧ����)
 	static string GetLocalTempFN(const string &name){return name+"_temp"+FILEDB_EXT_NAME;}			//�����ʱ�����ļ�
 	static string GetLocalBinlogFN(const string &name){return name+"_binlog"+FILEDB_EXT_NAME;}		//���binlog�ļ�
public:
	static string GetWhisperDataFN(const string &name){return name+"_data"+FILEDB_EXT_NAME;}		//��������ļ�

private:
	core_obj::Storage *m_storage;				//�ļ�����ʵ��
	KeyMap m_keymap;							//���ݵ�keys����
	SaveMap m_savemap;							//���ݱ���
};
#endif
