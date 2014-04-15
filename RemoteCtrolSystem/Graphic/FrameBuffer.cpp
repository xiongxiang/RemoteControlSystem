#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(void)
{
	m_buffer = NULL;
}

FrameBuffer::~FrameBuffer(void)
{
	if (NULL != m_buffer)
	{
		delete []m_buffer;
		m_buffer = NULL;
	}
}

char* FrameBuffer::getBuffer()
{
	return m_buffer;
}

bool FrameBuffer::setBuffer( char* src )
{
	if (NULL == src)
	{
		return false;
	}
	m_buffer = src;
	return true;
}

char* FrameBuffer::getBufferPtr( int x,int y )
{
	if (x < m_bufferRect.left || 
		x>m_bufferRect.right || 
		y > m_bufferRect.top || 
		y<m_bufferRect.bottom)
	{
		return NULL;
	}

	int bufferWidth = m_bufferRect.right - m_bufferRect.left;
	return m_buffer + y*bufferWidth + x;
}

bool FrameBuffer::getRectBuffer( char* dst,RECT srcRect )
{
	if (srcRect.left < m_bufferRect.left || 
		srcRect.right >m_bufferRect.right || 
		srcRect.top > m_bufferRect.top || 
		srcRect.bottom < m_bufferRect.bottom)
	{
		return false;
	}

	char* pBegin = getBufferPtr(srcRect.left,srcRect.bottom);
	int bufferWidth = m_bufferRect.right - m_bufferRect.left;
	int rectWidth = srcRect.right - srcRect.left;
	for (int y = srcRect.bottom;y <= srcRect.top;y++)
	{
		memcpy(dst+ rectWidth*y*3,pBegin + y * bufferWidth*3,rectWidth*3);
	}
	return true;
}

bool FrameBuffer::setRectBuffer( char* src,RECT dstRect )
{
	if (dstRect.left < m_bufferRect.left || 
		dstRect.right >m_bufferRect.right || 
		dstRect.top > m_bufferRect.top || 
		dstRect.bottom < m_bufferRect.bottom)
	{
		return false;
	}

	char* pBegin = getBufferPtr(dstRect.left,dstRect.bottom);
	int bufferWidth = m_bufferRect.right - m_bufferRect.left;
	int rectWidth = dstRect.right - dstRect.left;
	for (int y = dstRect.bottom;y <= dstRect.top;y++)
	{
		memcpy(pBegin + y * bufferWidth*3,src + rectWidth*y*3,rectWidth*3);
	}
	return true;
}

int FrameBuffer::getBufferSize()
{
	return (m_bufferRect.right - m_bufferRect.left)*(m_bufferRect.top - m_bufferRect.bottom)*3;
}

bool FrameBuffer::resizeBuffer( RECT newRect )
{
	if (NULL != m_buffer)
	{
		delete []m_buffer;
		m_buffer = NULL;
	}
	m_bufferRect = newRect;
	m_buffer = new char[getBufferSize()];
	return true;
}
