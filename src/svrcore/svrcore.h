/************************************************************************
 * file	:svrcore.h                                                                     
 * desc	:���ļ�������svrcore������ص�ͷ�ļ�
 *		�� ͨѶЭ�� ����ʵ�嶨�� �������Э��
 *
 *
 * author:	linbc
 * date:	20110429
 * version:
 ************************************************************************/
#ifndef _SVRCORE_H_
#define _SVRCORE_H_

#include <svrcore-internal.h>

#ifdef __cplusplus
#  include <shared/util.h>
//#  include <database/DatabaseEnv.h>
#  include <server/svrcore_app.h>
#  include <protocol/WorldPacket.h>
#  include <shared/MemoryDB.h>
#endif

//#include <protocol/external.h>
//#include <protocol/internal.h>


/*
*	svrcore_init - ��ʼ��
*/
void svrcore_init();

/*
*	svrcore_free - �ͷ�
*/
void svrcore_free();

#endif

