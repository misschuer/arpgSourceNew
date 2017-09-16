#ifndef _MEMORY_DB_H
#define _MEMORY_DB_H
#include <memdb/mem_db.h>
#include <memdb/memdb_index.h>
#include <memdb/memdb_result.h>

template<typename T>
int MemDB_Compare_Handle(void *v1,void *v2, size_t )
{
	T _v1 = *static_cast<T *>(v1);
	T _v2 = *static_cast<T *>(v2);
	if(_v1 < _v2) return -1;
	else if(_v2 < _v1) return 1;
	else return 0;
}

template<>
int MemDB_Compare_Handle<char *>(void *v1,void *v2, size_t _size);

template<typename T>
class MemDB_Result
{
	typedef MemDB_Result<T> THIS_TYPE;
private:
	//���ü���
	class ResultCount
	{
	private:
		size_t count;
	public:
		ResultCount():count(1){}
		~ResultCount(){};
		size_t AddCount(){ return ++count;}
		size_t SubCount(){ return --count;}
		size_t GetCount(){ return count;}
	};

	memdb_result *result_ptr;
	ResultCount  *ref_count;
public:
	explicit  MemDB_Result(memdb_result* ptr)
		:result_ptr(ptr), ref_count(new ResultCount()) {}

	~MemDB_Result()
	{
		sub_ref_count();
	}

	MemDB_Result(const THIS_TYPE &result)
		:result_ptr(result.result_ptr), ref_count(result.ref_count) 
	{
		add_ref_count();
	}
	
	THIS_TYPE & operator=(const THIS_TYPE &result)
	{
		sub_ref_count();
		result_ptr = result.result_ptr;
		ref_count = result.ref_count;
		add_ref_count();
		return *this;
	}

	size_t size()
	{
		return result_ptr->len;
	}

	T * operator[](size_t i)
	{
		ASSERT(i < result_ptr->len);
		return (T *)result_ptr->data[i]; 
	}
private:
	void add_ref_count() { ref_count->AddCount();}
	void sub_ref_count()
	{
		if(ref_count->SubCount() == 0)
		{
			delete ref_count;
			if(result_ptr) memdb_result_free(result_ptr);
		}
	}
};

template<typename T>
class MemDBCondPool
{
private:
	uint8 *m_pool;	//Ԥ�����ڴ�
	size_t m_len;	//�ڴ泤��
	size_t m_offset; //��ʹ��ƫ����
public:
	MemDBCondPool():m_pool(0), m_len(0), m_offset(0)
	{
		m_len = sizeof(T);
		m_pool = (uint8*)malloc(m_len);
		ASSERT(m_pool);
	}

	~MemDBCondPool()
	{
		if(m_pool) free(m_pool);
	}

	void *getMermory(size_t size)
	{
		void *p = 0;
		if(m_len <= size + m_offset && !PoolRealloc()) return p ;
		ASSERT(m_len >  size + m_offset);
		p = (void*)(m_pool + m_offset);
		m_offset += size;
		return p;
		
	}

	void clear()
	{
		m_offset = 0;
	}
private:
	bool PoolRealloc()
	{
		uint8 *p = (uint8*)realloc(m_pool,m_len *2);
		if(p)
		{
			m_len *= 2;
			m_pool = p;
			free(p);
			return true;
		}
		return false;
	}
};

template<typename T>
class MemoryDB
{
public:
	static int default_data_free(void *data)
	{
		T* p = (T*)data;
		delete p;
		return 0;
	}
public:
	MemoryDB(data_free freeptr = MemoryDB<T>::default_data_free)
	{
		memdb_init(&table, sizeof(T), freeptr);
	}
	~MemoryDB()
	{
		memdb_free(table);
	}

	memdb_index * create_index()//���������ṹ
	{
		memdb_index * index = NULL;
		memdb_index_init(&index);
		return index;
	}


	/*
	*	add_index_cell - ��������ֵ
	*	@ index�� �����ṹ
	*	@ offset: �ֶ�ƫ����
	*	@ size: �ֶγ��ȣ��ֶε�sizeof)
	*	@ cmp �� �ֶεıȽϺ���ָ��
	*	@return	: ��Ӻ������ָ��
	*  
	*/
	memdb_index * add_index_cell(memdb_index * index, size_t offset ,size_t size, compare_handle cmp )
	{
		memdb_index_cell *cell = memdb_index_cell_create(offset, size, cmp);
		memdb_index_add_cell(index, cell);
		return index;
	}

	//�������������
	bool add_index(memdb_index * index)
	{
		return __memdb_add_index(table, index) == 0;
	}

	//�ӱ���ɾ������
	bool remove_index(memdb_index * index)
	{
		int r =  __memdb_remove_index(table, index);
		memdb_index_free(index);
		return r == 0;
	}

	//���ݲ������
	void insertDB(T *data)
	{
		memdb_insert(table, (void*) data);
	}

	//�����±��������ݣ��±�Ϊƫ����Ϊ0�� ����Ϊint�ĳ�Ա��
	void insertVector(T *data)
	{
		memdb_insert_vector(table, (void*) data);
	}

	void register_compare_handle(size_t offset, compare_handle cmp)
	{
		memdb_register_compare_handle(table, 1, offset, cmp);
	}

	T* operator[](uint32 i)
	{
		if(i >= table->_vecLen)
			return NULL;
		return (T*)table->_vector[i];
	}
	
	T* operator[](int i)
	{
		if(i < 0 || size_t(i) >= table->_vecLen)
			return NULL;
		return (T*)table->_vector[i];
	}
	
	/*
	*	updateDB - �޸�ֵ
	*	@ data�� ����ָ��
	*	@ offset: �ֶ�ƫ����
	*	@ size: �ֶγ��ȣ��ֶε�sizeof)
	*	@ val �� �ֶ�ֵ
	*  
	*/
	template<typename V>
	void updateDB(T *data, size_t offset ,size_t size, V val)
	{
		ASSERT(sizeof(V) == size);
		if(memdb_offset_exists(table, offset))
		{
			deleteDB(data);
			*((V*)(((uint8*)data) + offset)) = val;
			insertDB(data);
		}
		else
		{
			*((V*)(((uint8*)data) + offset)) = val;
		}
		
	}

	//ɾ������
	void deleteDB(T *data)
	{
		memdb_delete(table, (void*) data);
	}

	/*
	*	add_select_condition - �����������
	*	@ offset: �ֶ�ƫ����
	*	@ size: �ֶγ��ȣ��ֶε�sizeof)
	*	@ val �� �ֶ�ֵ
	*   @ sign : ����
	*/
	template<typename V>
	void add_select_condition( size_t offset ,size_t size, V val, MD_SIGN sign)
	{
		ASSERT(sizeof(V) == size);
		V *t = (V*)condPool.getMermory(size);//�˿��ڴ���memdb�ڲ��ͷ�
		ASSERT(t);
		*t = val;
		__memdb_insert_condition(table, offset,size,(uint8*)t , sign);
	}
	
	void add_select_condition( size_t offset ,size_t size, const char * val, MD_SIGN sign)
	{
		//ASSERT(strlen(val));
		char *t = (char *)condPool.getMermory(strlen(val) + 1);//�˿��ڴ���memdb�ڲ��ͷ�
		ASSERT(t);
		strcpy(t, val);
		__memdb_insert_condition(table, offset,size,(uint8*)t , sign);
	}

	/*
	*	select - ����������
	*	@ offset: �ֶ�ƫ����
	*	@ size: �ֶγ��ȣ��ֶε�sizeof)
	*	@ val �� �ֶ�ֵ
	*   @ sign : ����
	*/
	template<typename V>
	MemDB_Result<T> select(size_t offset ,size_t size, V val, MD_SIGN sign)
	{
		add_select_condition(offset, size, val, sign);
		return select();
	}

	//����
	MemDB_Result<T> select()
	{
		MemDB_Result<T> result(__memdb_select(table));
		condPool.clear();
		return result;
	}

	size_t data_size() const
	{
		return memdb_size(table);
	}
	
	size_t size() const//�������±���ʵ�������Ч����
	{
		return table->_vecSize;
	}

	void clear()
	{
		memdb_empty(table);
	}

private:
	memdb_data *table;
	MemDBCondPool<T> condPool;
	
};


#endif

