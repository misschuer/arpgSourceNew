#ifndef _LOCALFILEDB_H_
#define _LOCALFILEDB_H_
//基于文件存储的本地数据库
#include "Storage.h"

#define FILEDB_SEP "#LHS#"								//数据文件存储时的分割符
#define FILEDB_BINLOG_SEP "#BLOG#"					//binlog文件存储时的分割符
#define FILEDB_FILENAME_KEYMAP "FILENAME_KEYMAP.txt"	//每个文件对应的key存储文件名
#define FILEDB_FILENAME_CURSOR "FILENAME_CURSOR.txt"	//游标文件名
#define FILEDB_EXT_NAME ".blg"							//文件后缀

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
		OPT_TYPE_ADD			= 0,		//添加
		OPT_TYPE_DEL			= 1,		//删除
		OPT_TYPE_UPDATE			= 2,		//更新
	};
public:
	LocalFileDb(const string& dbpath);
	virtual ~LocalFileDb(void);

	/* 加载文件的所有数据
	@fname:文件名
	@results:加载结果集返回
	@return:true成功，false失败
	*/
	bool Load(const string& fname, Results& results);
	
	/* 覆盖保存文件内容
	@fname:文件名
	@values:要存的数据
	@return:true成功，false失败
	*/
	bool Save(const string& fname, const Values& values);

	/* 增加一条文件数据
	@fname:文件名
	@value:要添加的数据
	@return:true成功，false失败
	*/
	bool Add(const string& fname, const Map& value);

	/* 添加一条binlog操作
	@fname:文件名
	@opt_type:操作类型
	@value:要添加的数据
	@return:true成功，false失败
	*/
	bool AddBinlog(const string& fname, const OPT_TYPE &opt_type, const Map& value);

	/* 读取binlog文件（逐行返回）
	@fname:文件名
	@func:回调函数
	@return:void
	*/
	void ReadBinlog(const string& fname, std::function<void (const OPT_TYPE opt_type, Map& m)> func);

	/* 临时数据文件重命名成数据文件 (文件夹的重命名无效,要重命名的文件已经存在则会覆盖掉)
	@fname:文件名
	@return:true成功，false失败
	*/
	bool Rename(const string &fname);

	/* 删除binlog文件
	@fname:文件名
	@return:true成功，false失败
	*/
	bool Remove(const string& fname);								

	/* 把map数据转换成存储数据
	@fname:文件名
	@value:要转换的map数据
	@content:转换后的数据
	@return:void
	*/
	void ToString(const string& fname, const Map &value, string& content);

	/* 把字符串数据转换成map数据
	@fname:文件名
	@content:要转换的数据
	@value:转换后的数据
	@return:void
	*/
	void FromString(const string& fname, const string& content, Map &value);	

	//是否需要保存data true:保存 false:不保存
	bool IsSaveData(const string& fname);
	
	//获得keymap数据串
	void GetKeyMapStr(const string& fname, string &str);

	//把map数据转换成存储串
	void ToMapString(const string& fname, const Values& values, string &ret_str);
	//把字符串转换成Map
	void FromMapString(const string& keymap_str, const string& src_str, Values &values);

	core_obj::Storage* GetStorage(){return m_storage;}
private:
	bool SaveKeyMap();							//保存每个文件的key
	bool LoadKeyMap();							//加载每个文件的key
	void SetSave(const string &fname, bool issave = true);		//设置保存

	static string GetLocalDataFN(const string &name){return name+"_data"+FILEDB_EXT_NAME;}			//获得数据文件(这个文件的存在防止保存temp的时候失败了)
 	static string GetLocalTempFN(const string &name){return name+"_temp"+FILEDB_EXT_NAME;}			//获得临时数据文件
 	static string GetLocalBinlogFN(const string &name){return name+"_binlog"+FILEDB_EXT_NAME;}		//获得binlog文件
public:
	static string GetWhisperDataFN(const string &name){return name+"_data"+FILEDB_EXT_NAME;}		//获得数据文件

private:
	core_obj::Storage *m_storage;				//文件操作实例
	KeyMap m_keymap;							//数据的keys缓存
	SaveMap m_savemap;							//数据保存
};
#endif
