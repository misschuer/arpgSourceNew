#ifndef _PROBABILITY_RAND_H_
#define _PROBABILITY_RAND_H_
#include "comm/common_stl.h"

//���������
template<typename T = int>
class ProbabilityRand
{
public:	
	struct rand_member
	{		
		uint16 probaqbility;
		T values;
	};
	typedef vector<rand_member> RandVec;
	typedef bool (*needDelChoiceFunc)(rand_member* rm,void *param);

	ProbabilityRand():m_total_probaqbility(0)
	{
	}
	~ProbabilityRand()
	{		
	}
public:

	void AddRandPossibility(uint16 probaqbility,T values) //������Ҫ����ĳ�Ա
	{
		//����³�Ա
		m_rand_members.resize(m_rand_members.size()+1);
		typename RandVec::reverse_iterator it = m_rand_members.rbegin();
		it->probaqbility = probaqbility;
		it->values = values;

		//���ʴ��
		m_probaqbility_stub.push_back(probaqbility);
		//�ܸ���ͳ��
		m_total_probaqbility+=probaqbility;
	}

	T Rand(bool is_repeat = true);							//���ݸ��������ֵ,Ĭ�Ͽ��ظ��������
	bool empty() {return m_rand_members.empty();};			//�Ƿ�յ�
	void Reset()											//���ó�Ա����
	{
		m_total_probaqbility = 0;
		for (uint32 i =0;i<m_rand_members.size();i++)
		{
			m_total_probaqbility+=m_probaqbility_stub[i];
			m_rand_members[i]->probaqbility = m_probaqbility_stub[i];
		}
	}
	void clear()
	{		
		m_rand_members.clear();
		m_probaqbility_stub.clear();
		m_total_probaqbility = 0;
	}

	void SetProbaqbility(needDelChoiceFunc delChoiceFunc,void *param)
	{
		for (uint32 i =0;i<m_rand_members.size();i++)
		{
			if(delChoiceFunc(&m_rand_members[i],param))
			{
				m_total_probaqbility -= m_rand_members[i].probaqbility;
				m_rand_members[i].probaqbility = 0;
			}
		}
	}

private:
	uint32 m_total_probaqbility;						//�ܸ���
	RandVec m_rand_members;								//�����Ա
	std::vector<uint16> m_probaqbility_stub;			//���г�Ա�ĸ��ʴ������������
};

//���ݸ��������ֵ,����������������ظ���
template<typename T>
T ProbabilityRand<T>::Rand(bool is_repeat)	
{
	ASSERT(m_rand_members.size());
	//���һ������0~�ܸ���֮��
	uint32 rand_num = urand(0,m_total_probaqbility - 1);
	//�������ж��������һ����Ա�ĵ��� ���ҷ���ֵ
	//��ΪҪ֪����ʱ����ʲô�±�λ�ã������ַ��������᷽��Щ
	for (uint32 i = 0;i<m_rand_members.size();i++)
	{
		if(rand_num < m_rand_members[i].probaqbility)
		{		
			//�����ظ� ������0 �ܸ��ʽ���
			if(!is_repeat)
			{
				m_total_probaqbility -= m_rand_members[i].probaqbility;
				m_rand_members[i].probaqbility=0;
			}
			return m_rand_members[i].values;
		}
		rand_num -= m_rand_members[i].probaqbility;
	}
	//�����û���ؾ��Ǵ�����
	ASSERT(false);
	return T();
}

#endif 

