#include <gtest/gtest.h>
#include "centd_test.h"

#if 0
//////////////////////////////////////////////////////////////////////////
//TODO ������

TEST_F(CentdTest, database_env_test)
{

	ASSERT_TRUE(m_ready);

	QueryResult *result = DBCharacter.Query("select -1 ");
	Field *fields = result->Fetch();
	int32 a = fields[0].GetInt32();

	//�������ݿ������Ƿ�ɹ�
	ASSERT_EQ(a, -1);
	delete result;


	QueryResult *result2 = DBLogin.Query("select -1");
	Field *fields2 = result2->Fetch();
	int32 a2 = fields2[0].GetInt32();

	//�������ݿ������Ƿ�ɹ�
	ASSERT_EQ(a2, -1);	
	delete result2;
	
}

//////////////////////////////////////////////////////////////////
//

#endif