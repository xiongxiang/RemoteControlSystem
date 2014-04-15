/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:MouseMsg.h
**Latest modified Data:2013-4-7  9:35:40
**Latest Version:v1.0
**Description:鼠标消息类
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-7  9:35:40
**Version:v1.0
**Description:鼠标消息类
**
**
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**************************************************************************/
/*MouseMsg是鼠标消息的类，其中m_buffer储存消息的实际数据
  数据排列方式如下：
  类型		变量名			字节数
  __int8	MsgType			(1bits)
  int		x				(4bits)
  int		y				(4bits)
  int		status			(4bits) 

  status的类型有：
  #define RCS_MOUSE_LEFT_UP			0xFFFF
  #define RCS_MOUSE_LEFT_DOWN		0xFFFE
  #define RCS_MOUSE_RIGHT_UP		0xFFFD
  #define RCS_MOUSE_RIGHT_DOWN		0XFFFC
  除以上四个消息之外，鼠标中键滚轮上下移动以status的数值表示
*/
#ifndef __MOUSEMSG_H__
#define __MOUSEMSG_H__
#include "ByteArrayMsg.h"

#define RCS_MOUSE_LEFT_UP		WM_LBUTTONUP
#define RCS_MOUSE_LEFT_DOWN		WM_LBUTTONDOWN
#define RCS_MOUSE_LEFT_DBLCLK	WM_LBUTTONDBLCLK
#define RCS_MOUSE_RIGHT_UP		WM_RBUTTONUP
#define RCS_MOUSE_RIGHT_DOWN	WM_RBUTTONDOWN
#define RCS_MOUSE_RIGHT_DBLCLK	WM_RBUTTONDBLCLK
#define RCS_MOUSE_MINDLE_UP		WM_MBUTTONUP
#define RCS_MOUSE_MINDLE_DOWN	WM_MBUTTONDOWN
#define RCS_MOUSE_MINDLE_DBLCLK	WM_MBUTTONDBLCLK
#define RCS_MOUSE_WHEEL			WM_MOUSEWHEEL


class MouseMsg
	:public ByteArrayMsg
{
public:
	MouseMsg(void);
	~MouseMsg(void);

	/**
	   @brief:返回鼠标坐标的x值，如果m_buffer == NULL返回-1
	   @Return:int
	*/
	int   GetMouseX();
	/**
	   @brief:返回鼠标坐标的y值，如果m_buffer == NULL返回-1
	   @Return:int
	*/
	int   GetMouseY();
	/**
	   @brief:返回鼠标的状态，具体设定请参考类注释，如果m_buffer == NULL返回0
	   @Return:int
	*/
	int   GetMouseStatus();
	/**
	   @brief:打包消息
	   @Parameter:int x
	   @Parameter:int y
	   @Parameter:int status//status如果是滚轮滑动请直接传滑动的数值，
	                         如果是鼠标按键被按下，请使用预定义的宏RCS_MOUSE_XXX_XXX
	   @Return:bool
	*/
	bool  PacketMsg(int x,int y,int status);
};
#endif

