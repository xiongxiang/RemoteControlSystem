/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:KeyboardMsg.h
**Latest modified Data:2013-4-7  10:29:18
**Latest Version:v1.0
**Description:
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-7  10:29:18
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
#ifndef __KEYBOARDMSG_H__
#define __KEYBOARDMSG_H__
#include "ByteArrayMsg.h"
/*MouseMsg是鼠标消息的类，其中m_buffer储存消息的实际数据
  数据排列方式如下：
  类型		变量名			字节数
  __int8	MsgType			(1bits)
  int		key				(4bits)
  int		status			(4bits) 

  status的类型有：
  #define RCS_KEY_UP		0xFFFF
  #define RCS_KEY_DOWN		0xFFFE
  除以上四个消息之外，鼠标中键滚轮上下移动以status的数值表示
*/
#define RCS_KEY_UP		0xFFFF
#define RCS_KEY_DOWN	0xFFFE
#define RCS_KEY_TASKMGR	0xFFFD
class KeyboardMsg :
	public ByteArrayMsg
{
public:
	KeyboardMsg(void);
	~KeyboardMsg(void);

	/**
	   @brief:返回键盘按键对应的ASCII码
	   @Return:int
	*/
	int   GetKey();
	/**
	   @brief:返回键盘的状态按下RCS_KEY_UP或者放开RCS_KEY_DOWN
	   @Return:int
	*/
	int   GetKeyStatus();
	/**
	   @brief:打包消息
	   @Parameter:int key
	   @Parameter:int status
	   @Return:bool
	*/
	bool  PacketMsg(int key,int status);
};

#endif
