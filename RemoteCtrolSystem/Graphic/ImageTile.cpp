#include "ImageTile.h"
#include <stdlib.h>
#include <algorithm>

ImageTile::ImageTile()
{
	m_pImageBits	= NULL;
	m_Rect.bottom	= 0;
	m_Rect.left		= 0;
	m_Rect.right	= 0;
	m_Rect.top		= 0;
}
ImageTile::~ImageTile()
{
	if (NULL != m_pImageBits)
	{
		delete []m_pImageBits;
		m_pImageBits = NULL;
	}
};

bool ImageTile::SetImageTile(char* pScreenImage,RECT screenRect,RECT tileRect)
{
	m_Rect = tileRect;
	int tileWidth  = m_Rect.right - m_Rect.left;
	int tileHeight = m_Rect.bottom - m_Rect.top;
	int screenWidth = screenRect.right - screenRect.left;
	int ScreenHeight = screenRect.bottom - screenRect.top;

	
	if (NULL != m_pImageBits)
	{
		delete []m_pImageBits;
	}
	m_pImageBits = new char[tileHeight*tileWidth*3];
	char* pBitsBegin = pScreenImage +m_Rect.top*screenWidth*3+m_Rect.left*3;

	//逐行拷贝需要传输的图像数据
	
	for (int yIdx = 0; yIdx<tileHeight;yIdx++)
	{
		memcpy(m_pImageBits + yIdx*tileWidth*3,pBitsBegin+yIdx*screenWidth*3,tileWidth*3);
	}

	return true;
}
bool ImageTile::ImageBits(char* dstBuff) const
{
	if (NULL == dstBuff)
	{
		return false;
	}
	int tileWidth  = m_Rect.right - m_Rect.left;
	int tileHeight = m_Rect.bottom - m_Rect.top;
	memcpy(dstBuff,m_pImageBits,tileWidth*tileHeight*3);

	return true;
}
RECT    ImageTile::Rect()
{
	return m_Rect;
}

bool ImageTile::SetImageTileReverse(char* pScreenImage,RECT screenRect,RECT tileRect )
{
	
	RECT	realRect;
	int tileWidth  = tileRect.right		- tileRect.left;
	int tileHeight = tileRect.bottom	- tileRect.top;
	int screenWidth = screenRect.right - screenRect.left;
	int ScreenHeight = screenRect.bottom - screenRect.top;

	if (memcmp(&m_Rect,&tileRect,sizeof(m_Rect)) != 0)
	{	
		m_Rect	= tileRect;
		if (NULL != m_pImageBits)
		{
			delete []m_pImageBits;
		}
		m_pImageBits = new char[tileHeight*tileWidth*3];
	}

	//获取实际存储所需图像的矩形位置
	realRect.top = ScreenHeight - m_Rect.top;
	realRect.bottom = ScreenHeight - m_Rect.bottom;
	realRect.right = m_Rect.right;
	realRect.left = m_Rect.left;

		char* pBitsBegin = pScreenImage +(realRect.top - 1)*screenWidth*3+realRect.left*3;
		//逐行拷贝需要传输的图像数据

		for (int yIdx = 0;yIdx <tileHeight;++yIdx)
		{
			if (pBitsBegin-yIdx*screenWidth*3 < 0 )
			{
				int test;
				test = 0;
			}
			memcpy(m_pImageBits + yIdx*tileWidth*3,pBitsBegin-yIdx*screenWidth*3,tileWidth*3);
		}

		return true;
}

char* ImageTile::GetBitsPtr()
{
	return m_pImageBits;
}

void SwapImageTile(ImageTile& tile1,ImageTile& tile2)
{
	ImageTile tempTile;
	tempTile = tile1;
	tile1 = tile2;
	tile2 = tempTile;
	tempTile.m_pImageBits = NULL;
}