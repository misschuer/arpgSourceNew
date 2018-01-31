#include "LocalFileDb.h"
#include <comm/common_stl.h>
#include <comm/str_util.h>

LocalFileDb::LocalFileDb(const string& dbpath)
{
	m_storage = new core_obj::Storage(nullptr);
	m_storage->Goto(dbpath);
	LoadKeyMap();
}

LocalFileDb::~LocalFileDb(void)
{
	safe_delete(m_storage);
}

//��map����ת���ɴ洢����
void LocalFileDb::ToString(const string& fname, const Map &value, string& content)
{
	auto iter = m_keymap.find(fname);
	if (iter == m_keymap.end())
	{
		//��key������
		vector<string> vec;
		for_each(value.begin(), value.end(), [&](std::pair<string, string> m){
			vec.push_back(m.first);
		});
		m_keymap[fname] = vec;
		//keymap�б仯ֱ�Ӵ�⣬��ô����Ϊkeymap�л��棬�仯Ƶ�ʲ���
		SaveKeyMap();
	}
	else
	{
		if (value.size() > iter->second.size())
		{
			//�������ֶ�,ֻ֧��ĩβ����			
			for_each(value.begin(), value.end(), [&](std::pair<string, string> m){
				auto &vec = iter->second;
				auto it = std::find(vec.begin(), vec.end(), m.first);
				if (it == vec.end())
					vec.push_back(m.first);
			});
			SaveKeyMap();
		}
	}

	iter = m_keymap.find(fname);
	stringstream ss;
	uint32 size = iter->second.size();
	for (uint32 i = 0; i < size; i++)
	{
		//ƴ�ӳ��ַ���
		auto v = value.find(iter->second.at(i));
		if (v != value.end())
			ss << v->second;
		
		if (i < size - 1)
			ss << FILEDB_SEP;
	}
	content = ss.str();
}

//���ַ�������ת����map����
void LocalFileDb::FromString(const string& fname, const string& content, Map &value)
{
	auto iter = m_keymap.find(fname);
	if (iter == m_keymap.end())
		return;

	Tokens token;
	StrSplit(token, content, FILEDB_SEP);
	uint32 size = iter->second.size();
	for (uint32 i = 0; i < size; i++)
		value.insert(make_pair(iter->second.at(i), token.at(i)));
}

//����ÿ���ļ���key
bool LocalFileDb::SaveKeyMap()
{
	if (!m_storage)
		return false;
	stringstream ss;
	for (auto iter = m_keymap.begin(); iter != m_keymap.end(); ++iter)
	{	
		ss << iter->first;
		for (auto it = iter->second.begin(); it < iter->second.end(); ++it)
		{
			ss << " " << *it;
		}
		ss << "\n";
	}
	m_storage->SaveFile(FILEDB_FILENAME_KEYMAP, ss.str());
	return true;
}

//����ÿ���ļ���key
bool LocalFileDb::LoadKeyMap()
{
	if (!m_storage)
		return false;

	m_storage->ReadFile(FILEDB_FILENAME_KEYMAP, [&](string content){
		//���оͲ�������
		if (content.empty())
			return true;
		Tokens token;
		StrSplit(token, content, " ");
		if (token.size() < 2)
			return true;
		string k = token.at(0);
		token.erase(token.begin());
		m_keymap[k] = token;				//�µ����ݸǵ�������
		return true;
	});
	return true;
}

//�����ļ�����������
bool LocalFileDb::Load(const string& fname, Results& results)
{
	if (!m_storage || fname.empty())
		return false;

	m_storage->ReadFile(GetLocalDataFN(fname), [&](string content){
		//���оͲ�������
		if (content.empty())
			return true;

		Map m;
		FromString(fname, content, m);
		results.push_back(m);
		return true;
	});

	return true;
}

//���Ǳ����ļ�����
bool LocalFileDb::Save(const string& fname, const Values& values)
{
	if (!m_storage || values.empty() || fname.empty())
		return false;

	string str;
	ToMapString(fname, values, str);	

	bool ret = m_storage->SaveFile(GetLocalTempFN(fname), str);	
	if(ret)
		SetSave(fname, false);		//�������˰ѱ����־�ó�false
	return ret;
}

//����һ���ļ�����
bool LocalFileDb::Add(const string& fname, const Map& value)
{
	if (!m_storage || value.empty() || fname.empty())
		return false;

	string content;
	ToString(fname, value, content);
	if (content.empty())
		return false;

	m_storage->AddContent(GetLocalDataFN(fname), content);
	return true;
}

//���һ��binlog����
bool LocalFileDb::AddBinlog(const string& fname, const OPT_TYPE &opt_type, const Map& value)
{
	if (!m_storage || value.empty() || fname.empty())
		return false;

	string content;
	ToString(fname, value, content);
	if (content.empty())
		return false;

	stringstream ss;
	ss << time(nullptr) << FILEDB_BINLOG_SEP << opt_type << FILEDB_BINLOG_SEP << content << "\n";	//д��˳���иļǵ�ReadBinlog��ӦҲ�ø�
	m_storage->AddContent(GetLocalBinlogFN(fname), ss.str());
	//���ñ����ʶ
	SetSave(fname);
	return true;
}

//��ȡbinlog�ļ������з��أ�
void LocalFileDb::ReadBinlog(const string& fname, std::function<void (const OPT_TYPE opt_type, Map& m)> func)
{
	if (!m_storage)
		return;

	bool bneedsave = false;
	m_storage->ReadFile(GetLocalBinlogFN(fname), [&](string content){
		//���оͲ�������
		if (content.empty())
			return true;

		Tokens token;
		StrSplit(token, content, FILEDB_BINLOG_SEP);
		if (token.size() < 3)
			return true;

		Map m;
		OPT_TYPE opt_type = (OPT_TYPE)atoi(token.at(1).c_str());
		FromString(fname, token.at(2), m);	
		func(opt_type, m);
		bneedsave = true;
		return true;
	});
	if(bneedsave)
		SetSave(fname);
}

//�ļ�������
bool LocalFileDb::Rename(const string &fname)
{
	if (!m_storage)
		return false;
	
	return m_storage->Rename(GetLocalTempFN(fname), GetLocalDataFN(fname));	
}

//ɾ��һ���ļ�
bool LocalFileDb::Remove(const string& fname)
{
	if (!m_storage)
		return false;

	return m_storage->Remove(GetLocalBinlogFN(fname));
}

//���ñ���
void LocalFileDb::SetSave(const string &fname, bool issave/* = true*/)
{
	m_savemap[fname] = issave;
}

//�Ƿ���Ҫ����data true:���� false:������
bool LocalFileDb::IsSaveData(const string& fname)
{
	return m_savemap[fname];			//�����б仯�ű���
}

//���keymap���ݴ�
void LocalFileDb::GetKeyMapStr(const string& fname, string &str)
{
	auto iter = m_keymap.find(fname);
	if (iter == m_keymap.end())
		return;

	stringstream ss;
	ss << iter->first;
	for (auto it = iter->second.begin(); it < iter->second.end(); ++it)
	{
		ss << " " << *it;
	}
	str = ss.str();
}

//��map����ת���ɴ洢��
void LocalFileDb::ToMapString(const string& fname, const Values& values, string &ret_str)
{
	if(fname.empty() || values.empty())
		return;

	stringstream ss;
	for (auto iter = values.begin(); iter != values.end(); ++iter)
	{
		auto &m = *iter;
		string content;
		ToString(fname, m, content);
		if (content.empty())
			continue;

		ss << content << "\n";
	}
	ret_str = ss.str();
}

//���ַ���ת����Map
void LocalFileDb::FromMapString(const string& keymap_str, const string& src_str, Values &values)
{
	Tokens keymap_token;
	StrSplit(keymap_token, keymap_str, " ");
	if (keymap_token.size() < 2)
		return;

	Tokens map_token;
	StrSplit(map_token, src_str, '\n');	
	for (auto iter = map_token.begin(); iter != map_token.end(); ++iter)
	{
		Map m;
		Tokens token;
		StrSplit(token, *iter, FILEDB_SEP);
		uint32 size = keymap_token.size();
		if (token.size() != size-1)
			continue;
		
		//��0λ��fname�����Դ�1��ʼ
		for (uint32 i = 1; i < size; i++)	
			m.insert(make_pair(keymap_token.at(i), token.at(i-1)));

		if (m.empty())
			continue;
		values.push_back(m);
	}
}


