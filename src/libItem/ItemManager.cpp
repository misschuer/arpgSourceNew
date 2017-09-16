#include "ItemManager.h"
#include "Item.h"

ItemManager::ItemManager():m_cur_max_id(0),obj_(nullptr)
{	
}

ItemManager::~ItemManager()
{		
}


void ItemManager::Init(GuidObject *obj)
{
	string owner_guid = obj->GetStr(owner_index);
	obj_ = obj;
	//��ʼ����Ʒ���� ���±�Ū������map
	for (uint32_t i=kItemPosStart;i<obj_->length_uint32();++i)
	{
		string s = obj_->GetStr(i);
		if(s!="")
		{
			Item item;
			//TODO ����from�������Ĵ��� ��־֮��
			if(item.FromString(s))
			{
				//������ƷΨһguid
				char temp[50] = {0};
				sprintf(temp, "%c%s;%d", item_guid_prefix, owner_guid.substr(1).c_str(), item.GetId());
				item.SetGuid(temp);
				//mapά����0
				itemsMap_[i] = item;
			}
				
		}
	}
}

//λ��Խ���� 
int ItemManager::CheckBagAndPos(int bag,int pos)
{
	//TODO �˴�������־
	if(pos>=kMaxBagSize)
		return -1;
	if(bag>=kBagCount)
		return -2;
	if(pos>=GetBagSize(bag))
		return -3;
	return 0;
}

//����λ������Ʒ,�Ҳ������ؿ�
Item* ItemManager::GetByPos(int bag_type,int pos)
{	
	if(CheckBagAndPos(bag_type,pos))
		return NULL;
	//���±���������ʵλ����Ϣ
	int true_pos =  TransformPos(bag_type,pos);
	for (auto iter = itemsMap_.begin(); iter != itemsMap_.end(); ++iter)
	{
		if (true_pos == obj_->GetUInt32(iter->first))
		{
			return &iter->second;
		}
	}
	
	return NULL;
}

//������ƷID����Ʒ
Item* ItemManager::Get(int id)
{
	//��������ID
	for (auto iter = itemsMap_.begin(); iter != itemsMap_.end(); ++iter)
	{
		if (iter->second.GetId() == id)
			return &iter->second;
	}

	return NULL;
}

//������Ʒguid����Ʒ
Item *ItemManager::GetItemByGuid(const string guid)
{
	//��������ID
	for (auto iter = itemsMap_.begin(); iter != itemsMap_.end(); ++iter)
	{
		if (iter->second.GetGuid() == guid)
			return &iter->second;
	}

	return NULL;
}


//����һ����Ʒ����,������ƷID
int ItemManager::Add(const Item& item,int bag,int pos)
{
	//������ʵ�Ǽ�����
	if(CheckBagAndPos(bag,pos))
		return -3;
	//TODO  ����ö�ٻ���Ҫ��һ��
	//��ָ��λ�� �ҿ�λ
	if(pos == -1)
	{
		pos = GetEmptyPos(bag);
		//�Ҳ�����λ �ݰ�
		if(pos==-1)
			return -1;
	}
	else
	{
		//TODOҵ���ϵ�λ�ô�С �Ƿ���Ҫ������ж�?
		//�����������С
		//���λ�ò����ǿյ�
		Item * _item = GetByPos(bag,pos);
		if(_item)
			return -2;
	}
	int binlog_pos = FindBinlogEmptyPos();
	//mapά����
	auto iter = itemsMap_.insert(std::make_pair(binlog_pos, item));
	int id = GetNewID();
	iter.first->second.SetId(id);

	string owner_guid = obj_->GetStr(owner_index);
	//������ƷΨһguid
	char temp[50] = {0};
	sprintf(temp, "%c%s;%d", item_guid_prefix, owner_guid.substr(1).c_str(), id);	
	iter.first->second.SetGuid(temp);

	string s = iter.first->second.ToString();
	int true_pos =  TransformPos(bag,pos);
	
	//���ȥ
	obj_->SetUInt32(binlog_pos,true_pos);
	obj_->SetStr(binlog_pos,s);
	
	// ԭ������id
	return pos;
}

//ɾ����Ʒ,�����Ƿ�ɹ�
bool ItemManager::Del(int id)
{
	//��������ID
	for (auto iter = itemsMap_.begin(); iter != itemsMap_.end(); ++iter)
	{
		if (iter->second.GetId() == id)
		{
			//�±�϶�Ҫɾ������
			obj_->SetUInt32(iter->first,0);
			obj_->SetStr(iter->first,"");

			//mapҪ����ɾ��//mapά����2
			itemsMap_.erase(iter);
			return true;
		}
	}

	return false;
}

void ItemManager::Save(const Item& item, int bag, int pos )
{
	//TODO  ��������λ����û������Ʒ ������������
	//ҵ���ϵ�λ�ô�С �ڴ�ֻ�����Դ���?
	//�����������С
	//ֱ�Ӷ��԰�
	if(CheckBagAndPos(bag,pos))
	{
		ASSERT(false);
		return;
	}
	string s = item.ToString();
	int true_pos =  TransformPos(bag,pos);

	auto iter =  itemsMap_.begin();
	for(;iter!=itemsMap_.end();++iter)
	{
		//����ID�������ܶ����� ������߱�����ID���ж�
		if(iter->second.GetId()==item.GetId())
		{
			obj_->SetUInt32(iter->first,true_pos);
			obj_->SetStr(iter->first,item.ToString());
			//���һ�� ����MAP //mapά����3
			iter->second = item;
			break;
		}
	}
}

//������Ʒ,���ǲ���������
void ItemManager::SavePtr(const Item* item)
{
	auto iter =  itemsMap_.begin();
	for( ;iter != itemsMap_.end(); ++iter)
	{
		//����ID�������ܶ����� ������߱�����ID���ж�
		if(iter->second.GetId() == item->GetId())
		{
			ASSERT(item == &iter->second);		//�������ĵ�ַһ��Ҳ��ͬһ��
			obj_->SetStr(iter->first,item->ToString());		
			break;
		}
	}
}

//ͳ��ָ����Ʒ����
int ItemManager::CountEntey(int entry,int bag)
{
	if(CheckBagAndPos(bag,0))
		return 0;
	int count = 0;

	//����
	for (auto iter = itemsMap_.begin(); iter != itemsMap_.end(); ++iter)
	{
		uint32_t true_pos = obj_->GetUInt32(iter->first);
		if(iter->second.GetEntry() != entry || true_pos/kMaxBagSize != bag)
			continue;
		count += iter->second.GetCount();
	}

	return count;
}

//�۳�ָ��ģ�����Ʒ
int ItemManager::Sub(int entry, int count,int bag)
{
	if(CheckBagAndPos(bag,0))
		ASSERT(false);
	//TODO ��߸���������֤����
	if(CountEntey(entry,bag) < count)
	{
		return -1;
	}

	for (auto iter = itemsMap_.begin(); iter != itemsMap_.end(); ++iter)
	{
		Item &item = iter->second;
		uint32_t true_pos = obj_->GetUInt32(iter->first);
		//��֤��������Ʒentry
		if(item.GetEntry() != entry || true_pos/kMaxBagSize != bag)
			continue;
		//ֻҪ��������
		int cur_count = item.GetCount();
		//������� �ж� �պ� ������
		if(cur_count>count)
		{
			item.SetCount(cur_count-count);
			Save(item, bag,true_pos%kMaxBagSize);
			return 0;
		}
		else if(cur_count==count)
		{
			obj_->SetUInt32(iter->first,0);
			obj_->SetStr(iter->first,"");
			itemsMap_.erase(iter->first);
			return 0;
		}
		else //����Ʒһ��ɾ��
		{
			obj_->SetUInt32(iter->first,0);
			obj_->SetStr(iter->first,"");
			itemsMap_.erase(iter->first);
			count -= item.GetCount();
		}
	}

	return 0;
}

//ͨ��
int ItemManager::GetBinlogIndexBypos(int true_pos)
{
	for (uint32_t i=kItemPosStart;i<obj_->length_uint32();++i)
	{
		int pos = obj_->GetUInt32(i);
		string s = obj_->GetStr(i);
		if(pos == true_pos && s!="")
			return i;
	}
	return -1;
}

//�ƶ���Ʒ
void ItemManager::Move(int id, int to_bag, int to_pos)
{
	if(CheckBagAndPos(to_bag,to_pos))
		ASSERT(false);
	
	//�˴�����ҵ����֤ 
	for (auto iter = itemsMap_.begin(); iter != itemsMap_.end(); ++iter)
	{
		//�ҵ���Ʒ
		if (iter->second.GetId() == id)
		{
			int old_pos = obj_->GetUInt32(iter->first);	//�ȱ����¾ɵ�λ��
			//����Ŀ��λ����û�ж���
			int index = GetBinlogIndexBypos(TransformPos(to_bag, to_pos));
			if (index != -1 && index != iter->first)
			{
				obj_->SetInt32(index, old_pos);
			}
			obj_->SetInt32(iter->first,TransformPos(to_bag, to_pos));
		}
	}
}	

//BINLOG�Ҹ�λ�÷���Ʒ
int ItemManager::FindBinlogEmptyPos()
{
	for (uint32_t i=kItemPosStart;i<obj_->length_uint32();++i)
	{
		string s = obj_->GetStr(i);
		//��������
		if(s=="")
			return i;
	}
	//�������µ�λ�� ����Ҫ��32��ʼ
	return obj_->length_uint32()>=kItemPosStart?obj_->length_uint32():kItemPosStart;
}

//�Ӱ����ڲ��ҿ�λ
int ItemManager::GetEmptyPos(int bag)
{
	//��ô���󡣡��Ȱ������������Ķ��� ȫŪ��������Ȼ���󣬣�һ������λ�á���֪��
	std::set<int> not_empty;
	int min_pos = bag*kMaxBagSize;
	int max_pos = bag*kMaxBagSize+GetBagSize(bag)-1;
	//����������ж�����λ�ü�����
	for(auto iter= itemsMap_.begin();iter!=itemsMap_.end();++iter)
	{
		int pos =obj_->GetUInt32(iter->first); 
		if(pos>=min_pos && pos<=max_pos)
			not_empty.insert(pos-bag*kMaxBagSize);
	}
	//�ҵ�һ����λ
	for(int i = 0;i<GetBagSize(bag);i++)
	{
		if(not_empty.find(i)==not_empty.end())
			return i;
	}

	return -1;
}

//�ұ�������λ��
int ItemManager::GetEmptyCount(int bag)
{
	int count = 0;
	int min_pos = bag*kMaxBagSize;
	int max_pos = bag*kMaxBagSize+GetBagSize(bag)-1;
	//����������ж�����λ�ü�����
	for(auto iter=itemsMap_.begin();iter!=itemsMap_.end();++iter)
	{
		int pos =obj_->GetUInt32(iter->first); 
		if(pos>=min_pos && pos<=max_pos)
			count++;
	}
	return GetBagSize(bag)-count;
}

//������ҵ���С �������ʹ�0��ʼ
int ItemManager::GetBagSize(int bag)
{
	ASSERT(bag<kBagCount);
	return obj_->GetInt16(kBagSizeIndex+bag/2,bag%2);
}
void ItemManager::SetBagSize(int bag,int size)
{
	if (obj_->GetUInt16(kBagSizeIndex+bag/2, bag%2) != size)
		obj_->SetInt16(kBagSizeIndex+bag/2,bag%2,size);
	ASSERT(bag<kBagCount);
}

//��binlog�ڲ����һ���µ�ID TODO 40�����Ժ�ĸ��û��� ���߿�����double
int ItemManager::GetNewID()
{
	if (m_cur_max_id == 0)
		m_cur_max_id = obj_->GetUInt32(kItemIDJumpIndex);

	++m_cur_max_id;	
	obj_->SetUInt32(kItemIDJumpIndex, m_cur_max_id);
	return m_cur_max_id;
}

//����ָ��������������Ʒ
void ItemManager::ForEachBagItem(int bag, std::function<bool (Item*,int)> func)
{
	for (auto iter = itemsMap_.begin(); iter != itemsMap_.end(); ++ iter)
	{
		uint32_t true_pos = obj_->GetUInt32(iter->first);
		if (true_pos/kMaxBagSize != bag)
			continue;
		if (func(&iter->second, true_pos%kMaxBagSize))
			break;
	}
}

//�����Ʒ������guid
const string& ItemManager::GetGuid()
{
	ASSERT(obj_);
	return obj_->GetStr(0);
}

