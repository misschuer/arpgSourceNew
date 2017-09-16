#ifndef _ITEM_ITEM_H_
#define _ITEM_ITEM_H_

#include <string>
#include <map>
#include <stdint.h>

using std::string;
#include <functional>
//�� id;entry;count;flag;{k1:v1,k2:v2}
const int kStringMember = 6;

#include <vector>
//��Ʒ��

struct ItemBaseAtt
{
	int key;
	double val;
	int qua;
};

class Item
{
public:
	Item();
	virtual ~Item();

	bool FromString(const string& s);
	string ToString() const;

	int GetId() const{return id_;}
	void SetId(int value){id_ = value;}

	int GetEntry(){return entry_;}
	void SetEntry(int value){entry_ = value;}

	int GetCount(){return count_;}
	void SetCount(int value){count_=value;}

	bool GetBit(int pos);
	void SetBit(int pos);
	void UnSetBit(int pos);

	void SetAttr(const string& key,double values );
	double GetAttr(string key);
	void ClearAttr()
	{//������Զ�
		attrs_.clear();
	}
	//���û�������
	void SetBaseAttr(unsigned int pos,int key,double val,int qua);
	//��ӻ�������
	void AddBaseAttr(int key,double val,int qua);
	//��ջ�������
	void ClearBaseAttr()
	{
		itemBaseAtt_.clear();
	}

	//��������
	void ForEachBaseAttr(std::function<void (int, double)> func);

	void SetGuid(string guid){guid_ = guid;}
	string GetGuid(){return guid_;}
private:

	int id_;
	//ģ��ID
	int entry_;
	//������
	int count_;
	//��־λ
	int flags_;
	//���е���������ʹ�ü�ֵ�Եķ�ʽ������
	std::map<string,double> attrs_;
	//���������б�
	std::vector<ItemBaseAtt> itemBaseAtt_;
	string guid_;	//��Ʒguid "item_guid;id_"
};

#endif
