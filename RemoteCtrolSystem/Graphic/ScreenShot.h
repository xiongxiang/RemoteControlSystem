/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:ScreenShot.h
**Latest modified Data:2013-4-3  13:58:53
**Latest Version:v1.0
**Description:
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-3  13:58:53
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
#ifndef __SCREENSHOOT_H__
#define __SCREENSHOOT_H__
#include "ImageTile.h"
#include "../CxImage/ximage.h"
#include "../Message/ImageMsg.h"
#include <queue>

//#define _TEST_ENCODE_TIME_
#ifdef _TEST_ENCODE_TIME_
#include"HiResTimer.h"
#endif
class ScreenShot
{
public:
	ScreenShot(void);
	~ScreenShot(void);
	/**
	   @brief:初始化屏幕图像截取类，传入水平和垂直的分块数
	   @Parameter:int nHorizontalTile
	   @Parameter:int nVericalTile
	   @Return:bool
	*/
	bool  Init(int nHorizontalTile,int nVericalTile);
	/**
	   @brief:截取屏幕图像，压缩分块，打包成图像消息之后将图像消息加入到消息队列中
	   @Parameter:std::queue<ByteArrayMsg * > * pMsgQueue指定要传入的消息队列
	   @Return:bool
	*/
	bool  ShotScreenImage(std::queue<ByteArrayMsg*>* pMsgQueue);//屏幕截图
	/**
	   @brief:设置图像水平和垂直分块块数，在接收到图像分块块数改变之后可以调用这个函数改变
	   @Parameter:int nHorizontal
	   @Parameter:int nVerical
	   @Return:bool
	*/
	bool  SetTileNumber(int nHorizontal,int nVerical);
	/**
	   @brief:设置图像JPEG压缩质量传入1~100的整数，表示压缩百分比
	   @Parameter:int quality
	   @Return:bool
	*/
	bool  SetQuality(int quality);
	/**
	   @brief:返回屏幕宽度
	   @Return:int
	*/
	int	  GetScreenWidth();
	/**
	   @brief:返回屏幕高度
	   @Return:int
	*/
	int	  GetScreenHeight();
	/**
	   @brief:返回图像时候改变
	   @Return:bool
	*/
	bool  IsPixelChange();
private:
	bool		m_IsPixelChange;
	char*		m_pOldScreenBits;
	char*		m_pScreenBits;
	ImageTile*	m_pImageTileArray;
	ImageTile*	m_pOldImageTileArray;
	RECT*		m_pTileRectArray;
	int			m_nTileNumX;
	int			m_nTileNumY;
	int			m_nScreenWidth;
	int			m_nScreenHeight;
	RECT		m_nScreenRect;
	CxImage		m_ScreenImage;
	int			m_ImageQuallity;
	/**
	   @brief:比较前后两帧图像有改变的分块，并将改变的分块发送给客户端
	   @Parameter:std::queue<ByteArrayMsg * > * pMsgQueue
	   @Return:WORD
	*/
	WORD		CompareImg(std::queue<ByteArrayMsg*>* pMsgQueue);//比较分块图像中哪一块图像改变返回16整形，将改变的那一块图像的ID对应的二进制位置1
	/**
	   @brief:将屏幕图像分块
	   @Return:BOOL
	*/
	BOOL		Partition();  
#ifdef _TEST_ENCODE_TIME_
	HiResTimer	m_Timer;
#endif
	//////////////////////
};

#endif           

