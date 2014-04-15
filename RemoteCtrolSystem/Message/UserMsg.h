/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:UserMsg.h
**Latest modified Data:2013-4-7  11:11:15
**Latest Version:v1.0
**Description:
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-7  11:11:15
**Version:v1.0
**Description:
**
**
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**************************************************************************/
#ifndef __USERMSG_H__
#define __USERMSG_H__
#include "bytearraymsg.h"
/*SetupMsg是设置消息的类，其中m_buffer储存消息的实际数据
  数据排列方式如下：
  类型		变量名			字节数
  __int8	Type			(1bits)
  char*		uesrname		(20bits)
  char*		password			(20bits) 
*/
class UserMsg :
	public ByteArrayMsg
{
public:
	UserMsg(void);
	~UserMsg(void);

	/**
	   @brief:返回用户名，请确定传入的pUsername指向的内存块大小大于20bits
	   @Parameter:char * pUsername
	   @Return:bool
	*/
	bool  GetUsername(char* pUsername);
	/**
	   @brief:返回密码，请确定传入的pPassword指向的内存块大小大于20bits
	   @Parameter:char * pPassword
	   @Return:bool
	*/
	bool  GetPassword(char* pPassword);
	/**
	   @brief:打包消息
	   @Parameter:char * Username
	   @Parameter:char * Password
	   @Return:bool
	*/
	bool  PacketMsg(char* Username,char* Password);
};
#endif

