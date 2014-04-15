/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:ScreenDisplay.h
**Latest modified Data:2013-4-3  9:39:09
**Latest Version:v1.0
**Description:
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-3  9:39:09
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
#ifndef __SCREENDISPLAY_H__
#define __SCREENDISPLAY_H__

#ifndef NULL
#define NULL 0 
#endif

#include "..\Message\ImageMsg.h"
#include "..\CxImage\ximage.h"
//#include <windows.h>
class ScreenDisplay
{
public:
	ScreenDisplay(void);
	~ScreenDisplay(void);

	/**
	   @brief:初始化显示类，需要传入显示窗口的句柄，以及显示画布的像素大小
	   @Parameter:HWND hDisplayWin
	   @Parameter:int width
	   @Parameter:int height
	   @Return:bool
	*/
	bool Initialize(HWND hDisplayWin,int WinWidth,int WinHeight,int ServerWidth,int ServerHeight);
	/**
	   @brief:设置显示窗口大小
	   @Parameter:int width
	   @Parameter:int height
	   @Return:bool
	*/
	bool SetSize(int width,int height);
	/**
	   @brief:拷贝缓存，绘制图像
	   @Return:void
	*/
	void Display();
	/**
	   @brief:接收图像消息并解压，会知道缓存中
	   @Parameter:ByteArrayMsg * imageMsg
	   @Return:void
	*/
	void RecvImageMsg(ByteArrayMsg* imageMsg);
	/**
	   @brief:返回显示缓存宽度
	   @Return:int
	*/
	int  GetDisplayWidth();
	/**
	   @brief:返回显示缓存高度
	   @Return:int
	*/
	int  GetDisplayHeight();
	/**
	   @brief:返回远程桌面宽度
	   @Return:int
	*/
	int  GetSeverWidth();
	/**
	   @brief:返回远程桌面高度
	   @Return:int
	*/
	int	 GetServerHeight();
	/**
	   @brief:返回显示窗口宽度（显示窗口大小和显示分辨率不同）
	   @Return:int
	*/
	int  GetWinWidth();
	/**
	   @brief:返回显示窗口高度
	   @Return:int
	*/
	int  GetWinHeigth();
	/**
	   @brief:当远程桌面改变分辨率时，需要调用此函数通知显示类
	   @Parameter:int ServerWidth
	   @Parameter:int ServerHeight
	   @Return:void
	*/
	void SetServerSize(int ServerWidth,int ServerHeight);
	/**
	   @brief:返回当前远程桌面图像的HBitmap
	   @Return:HBITMAP
	*/
	CxImage  GetDisplayImage();
	/**
	   @brief:放大远程桌面图像
	   @Return:bool
	*/
	bool ScaleUp();
	/**
	   @brief:缩小远程桌面图像
	   @Return:bool
	*/
	bool ScaleDown();
	/**
	   @brief:将远程桌面图像缩放到本地分辨率大小
	   @Return:void
	*/
	void Scale2LocalSize();
	/**
	   @brief:将显示窗口图像清空（在放大和缩小显示的时候用到）
	   @Return:bool
	*/
	bool	ReflashDC();
private:	
	/**
	   @brief:配置显示窗口
	   @Parameter:HWND hDisplayWin
	   @Return:bool
	*/
	bool SetDevice(HWND hDisplayWin);
	/**
	   @brief:按远程桌面和当前显示分辨率比例缩放当前需要绘制的图像块的矩形位置
	   @Parameter:RECT srcRect
	   @Return:RECT
	*/
	RECT	ScaleRect(RECT srcRect);
	HWND	m_hClientWnd;
	HDC		m_hClientDC;
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HGDIOBJ m_hOldBmp;
	CxImage	m_FrameBuffer;

	//显示窗口的大小
	int		m_WinWidth;
	int		m_WinHeight;
	//远程桌面的分辨率
	int		m_ServerWidth;
	int		m_ServerHeight;
	//当前要显示的分辨率
	int		m_DisplayWidth;
	int		m_DisplayHeight;
	
};

#endif

