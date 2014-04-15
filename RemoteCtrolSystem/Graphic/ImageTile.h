/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:ImageTile.h
**Latest modified Data:2013-4-3  14:01:22
**Latest Version:v1.0
**Description:
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-3  14:01:22
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
#ifndef __IMAGETILE_H__
#define __IMAGETILE_H__
#include <Windows.h>
class ImageTile
{
public:
	ImageTile(void);
	~ImageTile(void);
    /**
       @brief:交换两个图像分块数据，这个交换将会交换图像分块用于存放图像数据的指针，以及图像分块的矩形位置数据
       @Parameter:ImageTile & tile1
       @Parameter:ImageTile & tile2
       @Return:friend void
    */
    friend void SwapImageTile(ImageTile& tile1,ImageTile& tile2);
	/**
	   @brief:图像分块函数，用于bmp数据图像的分割，注：bmp图像的排列方式从左下角开始，上下颠倒。
	   @Parameter:char * pScreenImage
	   @Parameter:RECT screenRect
	   @Parameter:RECT tileRect
	   @Return:bool
	*/
	bool	SetImageTileReverse(char* pScreenImage,RECT screenRect,RECT tileRect);
	/**
	   @brief:图像分块函数，传入的源数据图像数据按正常方式排列（从上到下，从左到右）
	   @Parameter:char * pScreenImage
	   @Parameter:RECT screenRect
	   @Parameter:RECT tileRect
	   @Return:bool
	*/
	bool	SetImageTile(char* pScreenImage,RECT screenRect,RECT tileRect);
	/**
	   @brief:获取图像数据buffer的指针
	   @Parameter:char * dstBuff
	   @Return:bool
	*/
	bool	ImageBits(char* dstBuff) const;
	/**
	   @brief:返回buffer指针
	   @Return:char*
	*/
	char*	GetBitsPtr();
	/**
	   @brief:返回图像分块的矩形
	   @Return:RECT
	*/
	RECT	Rect();
private:
	RECT	m_Rect;
	char*	m_pImageBits;
};

#endif

