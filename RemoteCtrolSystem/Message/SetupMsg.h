/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:SetupMsg.h
**Latest modified Data:2013-4-7  11:24:43
**Latest Version:v1.0
**Description:
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-7  11:24:43
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
#ifndef __SETUPMSG_H__
#define __SETUPMSG_H__
#include "bytearraymsg.h"
/*SetupMsg是设置消息的类，其中m_buffer储存消息的实际数据
  数据排列方式如下：
  类型		变量名			字节数
  __int8	Type			(1bits)
  int		SetupType		(4bits)
  int		value1			(4bits) 
   int		value2			(4bits) 
*/
#define	RCS_SETUP_MSG_PERMISSION	0x5100	//用户权限，观看还是控制或者是IP被禁用
#define	RCS_SETUP_MSG_PIXEL			0x5200   //屏幕分辨率value1存宽度，value2存高度
#define	RCS_SETUP_MSG_TILE			0x5300   //图像分块设置，value1存横向分割块数，value存纵向分割块数
#define	RCS_SETUP_MSG_IMAGE_QUALITY	0x5400	//图像质量，用Value1表示图像质量
#define	RCS_SETUP_MSG_FRAME			0x5500	//显示帧率，用Value1表示显示帧率
#define	RCS_SETUP_MSG_STOP			0X5600  //暂停显示远程桌面，value1==1时暂停，0时开始传送图像
//用于消息是权限类型时的对应Value1值
// 控制权限的value2中，-1 账号密码错误， 0 只有观看权限  1 控制权相
// IP禁止的value2中，   0 被禁止， 1 允许

#define	RCS_PERMISSION_CONTROL		0x5110	//控制权限
#define	RCS_PERMISSION_IP			0x5130	//禁用IP

class SetupMsg :
	public ByteArrayMsg
{
public:
	SetupMsg(void);
	~SetupMsg(void);

	/**
	   @brief:返回设置消息的类型
	   @Return:int
	*/
	int		GetStatusType();
	/**
	   @brief:返回需要设置的第一个值
	   @Return:int
	*/
	int		GetValue1();
	/**
	   @brief:如果这个设置消息需要第二个值作为补充，返回需要设置的第二个值，否则返回0
	   @Return:int
	*/
	int		GetValue2();
	/**
	   @brief:打包消息value2为扩展值，在需要两个设置值的时候用到
	   @Parameter:int setupType//设置消息的类别请使用预定义的宏RCS_SETUP_MSG_XXX
	   @Parameter:int value1//当设置消息是权限类别的时候，请使用预定义的宏RCS_PERMISSION_XXX填充此值
	   @Parameter:int value2
	   @Return:bool
	*/
	bool	PacketMsg(int setupType,int  value1,int value2 = 0);
};
#endif
