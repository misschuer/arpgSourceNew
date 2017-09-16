#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <core_obj/internal.h>

namespace core_obj {

class GuidObject;
class GuidObjectTable;

#define BINLOG_EXT_NAME ".blg"

class Storage
{
public:
	typedef std::function<GuidObject*(string)> CreateFunction;
	typedef std::function<bool(const string &)> ReadFunction;
	Storage(CreateFunction f);
	virtual ~Storage();
protected:
	string work_directory_;		//�洢���ļ���·��
	CreateFunction create_func_;//GuidObject���󴴽�����
public:
	static bool CreatDir(string path);
	static void RemoveDir(string path);
	static bool IsHaveFile(string path);
public:
	bool Goto(string f);	
	
	bool Load(const string& file_name,vector<GuidObject*> &vec);		//����ĳ���ļ���������еĶ���
	bool AddContent(const string &file_name, const string &content);	//׷���ļ�����
	bool ReadFile(const string &file_name, ReadFunction fun);			//��ĳ�ļ�������
	bool Remove(const string& file_name);								//ɾ��һ���ļ�
	void ForEachDir(std::function<void(string , string )>);				//����·���µ������ļ����������ļ��У�
	void GetDirs(const string &dir,std::function<void(const string&)>);	//���·���µ������ļ�������
	bool CopyDirFilse(string& src, string& dst);						//����Դ·���µ������ļ���Ŀ��·��	
	bool CopyAFile(string& src, string& dst);							//�����ļ�
	bool SaveFile(const string& file_name, const string& file_content);	//����һ���ļ���Ӳ��
};

}
#endif
