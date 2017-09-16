#ifndef _CHAT_ANALYSIS_H_
#define _CHAT_ANALYSIS_H_

#include <svrcore.h>

#define GM_SING "{GM}"
#define ZB_SING "{ZB}"
#define CHAT_MSG_FILTER_SING "{}"

//���������ַ���
inline void ChatMsgFilter(char *msg)
{	
	uint32 len = strlen(msg);
	if(!len)
		return;
	uint32 end_pos = len - 1;
	if(msg[end_pos] == CHAT_MSG_FILTER_SING[1])
	{
		char * frist = strchr(msg,CHAT_MSG_FILTER_SING[0]);
		if(frist)
		{
			memset(frist,0,sizeof(frist));
		}
	}
}

//���������ַ���
inline void ChatMsgFilter(string &content)
{
	if(content.empty())
		return;
	if(content[content.length()-1] == CHAT_MSG_FILTER_SING[1])
	{
		size_t pos = content.rfind(CHAT_MSG_FILTER_SING[0]);
		if(pos != string::npos)
		{
			content.substr(pos);
		}
	}
}


//��������ʾ
inline void ChatMsgAddSing(char *msg,uint8 falseGMLevel,uint8 girlGMLevel)
{	
	if(falseGMLevel)
	{
		strcat(msg,GM_SING);
	}
	else if(girlGMLevel == 1)
	{
		strcat(msg,ZB_SING);
	}
}

//��������ʾ
inline void ChatMsgAddSing(string &content,uint8 falseGMLevel,uint8 girlGMLevel)
{	
	if(falseGMLevel)
	{
		content.append(GM_SING);
	}
	else if(girlGMLevel == 1)
	{
		content.append(ZB_SING);
	}
}

#endif
