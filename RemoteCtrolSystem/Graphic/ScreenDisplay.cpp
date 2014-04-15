#include "ScreenDisplay.h"


ScreenDisplay::ScreenDisplay(void)
{
	m_hClientDC = NULL;
}

ScreenDisplay::~ScreenDisplay(void)
{
}

bool ScreenDisplay::Initialize( HWND hDisplayWin ,int WinWidth,int WinHeight,int ServerWidth,int ServerHeight)
{
	RECT rcClient;
	GetWindowRect(hDisplayWin,&rcClient);
	int DisplayWidth = rcClient.right - rcClient.left;
	int DisplayHeight = rcClient.bottom - rcClient.top;
	m_ServerWidth   = ServerWidth;
	m_ServerHeight  = ServerHeight; 
	if (!SetDevice(hDisplayWin))
	{
		return false;
	}
	if (!SetSize(DisplayWidth,DisplayHeight))
	{
		return false;
	}
	
 
	m_DisplayWidth  = WinWidth;
	m_DisplayHeight = WinHeight;
	return true;	
}

bool ScreenDisplay::SetDevice( HWND hDisplayWin )
{
	if (NULL == hDisplayWin)
	{
		return false;
	}
	m_hClientWnd = hDisplayWin;
	m_hClientDC = GetDC(hDisplayWin); //获显示窗口的HDC
	m_hMemDC = CreateCompatibleDC(m_hClientDC);
	m_FrameBuffer.Create(m_ServerWidth,m_ServerHeight,24,CXIMAGE_FORMAT_JPG);

	return true;
}

void ScreenDisplay::Display()
{
	
	m_FrameBuffer.Stretch(m_hMemDC,m_WinWidth/2 - m_DisplayWidth/2,m_WinHeight/2	- m_DisplayHeight/2,m_DisplayWidth,m_DisplayHeight);
    BitBlt(m_hClientDC,0,0,m_WinWidth,m_WinHeight,m_hMemDC,0,0,SRCCOPY);
}

void ScreenDisplay::RecvImageMsg( ByteArrayMsg* pMsg )
{
	ImageMsg* pImageMsg = static_cast<ImageMsg*>(pMsg);
	CxImage   msgImage;
	RECT	  rcDisplay = pImageMsg->GetImageRect();

	size_t size2 = pImageMsg->GetImageSize();
	msgImage.Decode((BYTE*)(pImageMsg->GetImageBufferPtr()),pImageMsg->GetImageSize(),CXIMAGE_FORMAT_JPG);
	//msgImage.Stretch(m_hClientDC,ScaleRect(rcDisplay));
	//很诡异的用MixFrom方式将图像保存进CxImage之后图像分块上下颠倒
	m_FrameBuffer.MixFrom(msgImage,rcDisplay.left,m_ServerHeight - rcDisplay.bottom );

	delete pImageMsg;
}

bool ScreenDisplay::SetSize( int width,int height )
{
	if (width <= 0 || height <= 0)
	{
		return false;
	}
	//当显示画布大小改变，刷新背景
	if (m_WinWidth != width ||m_WinHeight != height)
	{
		m_WinWidth  = width;
		m_WinHeight = height;
		m_hBitmap = CreateCompatibleBitmap(m_hClientDC,m_WinWidth,m_WinHeight);
		m_hOldBmp = SelectObject(m_hMemDC,m_hBitmap);
	}
	return true;
}

int ScreenDisplay::GetDisplayWidth()
{
	return m_DisplayWidth;
}

int ScreenDisplay::GetDisplayHeight()
{
	return m_DisplayHeight;
}

CxImage ScreenDisplay::GetDisplayImage()
{
	return m_FrameBuffer;
}

RECT ScreenDisplay::ScaleRect( RECT srcRect )
{
	RECT	DisplayRect;
	//显示画面以显示屏幕画布中央为中心点缩放，这里计算本地左上角起始点
	int		leftBegin	= m_WinWidth/2 - m_DisplayWidth/2;
	int		topBegin	= m_WinHeight/2	- m_DisplayHeight/2;
	//计算传入的矩形在本地显示窗口中的实际矩形位置
	DisplayRect.left	= leftBegin		+ (srcRect.left		* m_DisplayWidth)/m_ServerWidth;
	DisplayRect.right	= leftBegin		+ (srcRect.right	* m_DisplayWidth)/m_ServerWidth;
	DisplayRect.top 	= topBegin		+ (srcRect.top		* m_DisplayHeight)/m_ServerHeight;
	DisplayRect.bottom 	= topBegin		+ (srcRect.bottom	* m_DisplayHeight)/m_ServerHeight;

	return DisplayRect;
}

void ScreenDisplay::SetServerSize( int ServerWidth,int ServerHeight )
{
	m_ServerHeight	= ServerHeight;
	m_ServerWidth	= ServerWidth;
	m_FrameBuffer.Create(m_ServerWidth,m_ServerHeight,24,CXIMAGE_FORMAT_JPG);
}

int ScreenDisplay::GetSeverWidth()
{
	return m_ServerWidth;
}

int ScreenDisplay::GetServerHeight()
{
	return m_ServerHeight;
}

bool ScreenDisplay::ScaleUp()
{
	m_DisplayWidth *= 1.1;
	m_DisplayHeight *= 1.1;
	if(m_DisplayWidth >= m_ServerWidth * 2.0/*m_WinWidth*/)
	{
		m_DisplayWidth = m_ServerWidth * 2.0;
		m_DisplayHeight = m_ServerHeight * 2.0;
		ReflashDC();
		return false;
	}
	else
	{
		ReflashDC();
		return true;
	}
}

bool ScreenDisplay::ScaleDown()
{
	m_DisplayWidth /= 1.25;
	m_DisplayHeight /= 1.25;
	if(m_DisplayWidth <= 480)
	{
		m_DisplayWidth = 480;
		m_DisplayHeight = 360;
		ReflashDC();
		return false;
	}
	else
	{
		ReflashDC();
		return true;
	}
	
}

bool ScreenDisplay::ReflashDC()
{
	//刷新背景
	m_hBitmap = CreateCompatibleBitmap(m_hClientDC,m_WinWidth,m_WinHeight);
	m_hOldBmp = SelectObject(m_hMemDC,m_hBitmap);
	//BitBlt(m_hClientDC,0,0,m_WinWidth,m_WinHeight,m_hMemDC,0,0,SRCCOPY);
	DeleteObject(m_hOldBmp);
	return true;
}

int ScreenDisplay::GetWinWidth()
{
	return m_WinWidth;
}

int ScreenDisplay::GetWinHeigth()
{
	return m_WinHeight;
}

void ScreenDisplay::Scale2LocalSize()
{
	m_DisplayWidth = m_WinWidth;
	m_DisplayHeight = m_WinHeight;
	ReflashDC();
}
