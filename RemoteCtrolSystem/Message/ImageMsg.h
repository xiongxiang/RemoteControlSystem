/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:ImageMsg.h
**Latest modified Data:2013-4-1  15:59:04
**Latest Version:v1.0
**Description:
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-1  15:59:04
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
#ifndef __IMAGEMSG_H__
#define __IMAGEMSG_H__
#include "bytearraymsg.h"
#include <windows.h>
/*ImageMsg是图像消息的类，其中m_buffer储存消息的实际数据
  数据排列方式如下：
  类型		变量名			字节数
  __int8	MsgType         (1bits)
  RECT		Rect            (16bits)
  size_t	imageSize       (4bits)
  char*		Imagebuffer     (imageSize bits) 
*/
class ImageMsg :
	public ByteArrayMsg
{
public:
	ImageMsg(void);
	~ImageMsg(void);

	/**
	   @brief:返回存储图像的buffer的大小，即整个消息buffer大小减去前面其他信息的大小
	   @Return:size_t
	*/
	size_t GetImageSize();
	/**
	   @brief:返回图像块的矩形区域
	   @Return:RECT
	*/
	RECT  GetImageRect();
	/**
	   @brief:返回图像数据的buffer的指针
	   @Parameter:char * ImageBuffer
	   @Return:bool
	*/
	bool  GetImageBuffer(char* ImageBuffer);
	char* GetImageBufferPtr();
	/**
	   @brief:打包图像消息
	   @Parameter:__int8 type
	   @Parameter:RECT rect
	   @Parameter:size_t ImageSize
	   @Parameter:char * buffer
	   @Return:bool
	*/
	bool  PacketMsg(RECT rect,size_t ImageSize,char* buffer);
};

#endif


