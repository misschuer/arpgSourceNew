#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

//1 ���е���Ʒ������һ�����binlog���档���binlog������Ʒ������
//2 ÿһ����Ʒ��binlog����ռ��һ��int�±��һ��string�±�
//3 ��Ʒ��int�±��һ��λ����Ϣ����102 
//	���102���ջ�ͨ���ӿ�ת�������� ����0����ͨ������λ��13������һ����άλ����Ϣ����Ҫ�������ͻ�����ʾ���Լ�
//4 string�±����Ʒ��������Ϣ
//5.��������һ��item��������ת���Ͳ��������������string��

#include <core_obj/GuidObject.h>

using core_obj::GuidObject;

class Item;

//binlog��owner�±�����,ps:���ﲻ��Ӧ��SharedDef.hͷ�ļ�,��Ϊ���Ƕ�������Ŀ
const int owner_index = 3;
//��Ʒguidǰ׺
const char item_guid_prefix = 'I';

//ÿ����������������
const int kMaxBagSize = 1000;
const int kItemPosStart = 128;

//���ID���ŵ��±�λ��
const int kItemIDJumpIndex = 8;
//�±�9~23 ÿ��16λ�����洢��ǰ������ҵ���С
const int kBagSizeIndex = 9;
//����������
const int kBagCount = 30;

class ItemManager
{
public:
	ItemManager();
	virtual ~ItemManager();
	void Init(GuidObject *obj);

	//����λ������Ʒ,�Ҳ������ؿ�
	Item *GetByPos(int bag_type,int pos);
	//������ƷID����Ʒ
	Item *Get(int id);
	//������Ʒguid����Ʒ
	Item *GetItemByGuid(const string guid);

	//����һ����Ʒ����,������ƷID
	int Add(const Item& item,int bag,int pos=-1);
	//ɾ����Ʒ,�����Ƿ�ɹ�
	bool Del(int id);
	//�۳�ָ��ģ�����Ʒ TODO��������Ĵ������ ������ӿڱȽϺ�����
	int Sub(int entry, int count,int bag);

	//������Ʒ,ע��
	void Save(const Item& item, int bag, int pos);
	//������Ʒ,���ǲ���������
	void SavePtr(const Item* item);
	//�ƶ���Ʒ
	void Move(int id,  int to_bag, int to_pos);	
	

	// ĳ������ͳ��ָ����Ʒ����
	int CountEntey(int entry, int bag, int isBind=-1, int failTime=-1);
	// ���б���ͳ��ָ����Ʒ����
	int CountAllEntey(int entry, int isBind=-1, int failTime=-1);

	//����ʣ���λ
	int GetEmptyCount(int bag);
	//����ʵ�ʴ�С
	int GetBagSize(int bag);
	void SetBagSize(int bag,int size);

	//��binlog�ڲ����һ���µ�ID
	int GetNewID();

	//����ָ��������������Ʒ
	void ForEachBagItem(int bag, std::function<bool (Item*, int)> func);
	//�����Ʒ������guid
	const string& GetGuid();
	//�Ӱ����ڲ��ҿ�λ
	int GetEmptyPos(int bag);
protected:
	int FindBinlogEmptyPos();	
	//��άתһάһ������
	int TransformPos(int bag,int pos){return bag*kMaxBagSize +pos;}

	//ͨ��λ����Ϣ ��binlog���±�λ��
	int GetBinlogIndexBypos(int true_pos);
	//������֤������λ�õĺϷ��� ��ֱ�Ӷ���
    int CheckBagAndPos(int bag,int pos);

private:
	GuidObject *obj_;
	//��������
	std::map<int,Item> itemsMap_;
	//��ǰ����id,��ֹһ���ԼӶ����Ʒʱ�±걻���ķ���ͬ���������ǵ���
	uint32_t m_cur_max_id;
};


#endif
