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
#include <net/packet.h>

list_t svrcore_packet_pool;

void svrcore_init()
{
	INIT_LIST_HEAD(&svrcore_packet_pool);
}

void svrcore_free()
{
	packet_list_free(&svrcore_packet_pool);
}

/*
 *	external_protocol_new_packet - ���ڲ�ͨѶ��������ȡ�����ݰ�
 *	@optcode : �����
 *
 *	@return	:�µ����ݰ�
 *  
 */
packet_ptr external_protocol_new_packet(int optcode)
{
	packet_ptr pkt;
	if(packet_list_pop(&svrcore_packet_pool,&pkt) && packet_init(&pkt)){		
		return NULL;
	}
	packet_clear(pkt);
	pkt->head->optcode = optcode;	
	return pkt;
}

/*
 *	external_protocol_free_packet - �������ݰ�
 *	@pkt : Ҫ���յİ�ָ��
 *
 *	@return	:�µ����ݰ�
 *  
 */
int external_protocol_free_packet(packet_ptr pkt)
{
	if(pkt){
		packet_list_push(&svrcore_packet_pool,pkt);
		//packet_free(pkt);
	}
	return 0;	
}

#endif

