#ifndef _SVRCORE_INTERNAL_H_
#define _SVRCORE_INTERNAL_H_

#include <comm/common.h>
#include <net/netstd.h>

#ifdef __cplusplus
#  include <comm/common_stl.h>
#  include <comm/str_util.h>
#  include <comm/timer.h>
//#  include <gtest/gtest.h>
#endif

#if 0
#if PLATFORM == PLATFORM_WINDOWS
#  if defined(TEA_SVRCORE_EXPORTS) 
#    define TEA_SVRCORE_API 				CPPAPI  __declspec(dllexport)
#    define TEA_SVRCORE_SPEC                __declspec(dllexport)
#  else
#    define TEA_SVRCORE_API 				CPPAPI __declspec(dllimport)
#    define TEA_SVRCORE_SPEC                __declspec(dllimport)
#  endif
#else
#  define  TEA_SVRCORE_API					CPPAPI
#  define TEA_SVRCORE_SPEC
#endif
#endif

#  define TEA_SVRCORE_SPEC
#  define  TEA_SVRCORE_API					CPPAPI

#endif


/*
 *	external_protocol_new_packet - ���ڲ�ͨѶ��������ȡ�����ݰ�
 *	@optcode : �����
 *
 *	@return	:�µ����ݰ�
 *  
 */
TEA_SVRCORE_API packet_ptr external_protocol_new_packet(int optcode);

/*
 *	external_protocol_free_packet - �������ݰ�
 *	@pkt : Ҫ���յİ�ָ��
 *
 *	@return	:�µ����ݰ�
 *  
 */
TEA_SVRCORE_API int external_protocol_free_packet(packet *pkt);

#define internal_protocol_new_packet external_protocol_new_packet
#define internal_protocol_free_packet external_protocol_free_packet