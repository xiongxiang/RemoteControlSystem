/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com  
**-------------File Info---------------------------------------------------
**File Name:FrameBuffer.h
**Latest modified Data:2013-3-28  16:46:02
**Latest Version:v1.0
**Description:帧缓存类，用于保存一帧的屏幕图像，图像以char*形式储存，保存有屏幕图像的矩形区域
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-3-28  16:46:02
**Version:v1.0
**Description:创建FrameBuffer类
**
**
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**************************************************************************/
#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__
#include <windows.h>
class FrameBuffer
{
public:
	FrameBuffer(void);
	~FrameBuffer(void);

	/**
	   @brief:返回帧缓存的指针，char*型,
	              注意：修改返回的char*指向的内容会改变类中的帧缓存
	   @Return:char*
	*/
	char* getBuffer();
	/**
	   @brief:将一个char*数组设置为帧缓存.
	              注意：这个操作将会使帧缓存指针指向src的内存块。不要存入指向在栈中分配的内存块，也不要在外部销毁传入的堆内存块。
	   @Parameter:char * src
	   @Return:bool
	*/
	bool  setBuffer(char* src);
	/**
	   @brief:返回帧缓存中坐标为(x,y)的像素的指针，如果失败，返回NULL
	              注意：修改返回的char*指向的内容会改变类中的帧缓存
	   @Parameter:int x
	   @Parameter:int y
	   @Return:char*
	*/
	char* getBufferPtr(int x,int y);
	/**
	   @brief:获得帧缓存中srcRect指定的矩形的图像，存在dst指向的内存块中，请确定dst指向的内存块足够大
	   @Parameter:char * dst
	   @Parameter:RECT srcRect
	   @Return:bool
	*/
	bool  getRectBuffer(char* dst,RECT srcRect);
	/**
	   @brief:将src指向的图像缓存拷贝到帧缓存指定的dstRect的位置，请确定src指向的图像和dstRect设定的大小一致
	   @Parameter:char * src
	   @Parameter:RECT dstRect
	   @Return:bool
	*/
	bool  setRectBuffer(char* src,RECT dstRect);
	/**
	   @brief:返回储存帧缓存的char数组的大小
	   @Return:int
	*/
	int     getBufferSize();
	/**
	   @brief:重置帧缓存大小
	   @Parameter:RECT newRect
	   @Return:bool
	*/
	bool  resizeBuffer(RECT newRect);
protected:
	char   *m_buffer;
	RECT   m_bufferRect;
};

#endif

