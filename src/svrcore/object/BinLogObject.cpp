#include "BinLogObject.h"

//��ByteArrayת�������ݰ�
void WriteTo(core_obj::ByteArray &self,packet& pkt)
{
	packet_clear(&pkt);
	packet_resize(&pkt,self.length());
	self.position(0);
	pkt.head->optcode = self.readUnsignedShort();	
	packet_write(&pkt,(char*)self.cur_data(),self.length()-sizeof(uint16));
	update_packet_len(&pkt);
}

//��packet���뵽ByteArray
void ReadFrom(core_obj::ByteArray &dst,packet& src)
{
	dst.length(0);
	dst.writeShort(src.head->optcode);
	dst.writeBytes((uint8*)&src.content,src.wpos);
	dst.position(0);
	src.rpos = src.wpos;	
}
