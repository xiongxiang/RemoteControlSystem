#include "ByteArrayMsg.h"
#include <wchar.h>
#include <Windows.h>

ByteArrayMsg::ByteArrayMsg(void)
{
	m_buffer = NULL;
	m_buffer = new char[41];
	m_size = 41;
}

ByteArrayMsg::~ByteArrayMsg(void)
{
	if (NULL != m_buffer)
	{
		delete []m_buffer;
	}
	m_size = 0;
}

unsigned __int8 ByteArrayMsg::GetType()
{
	if(NULL != m_buffer)
	{
		unsigned __int8* pMsgType = (unsigned __int8* )m_buffer;
		return pMsgType[0];
	}
	return 0;
}

size_t ByteArrayMsg::GetBuffer( void* buffer,size_t len )
{
	if (0 == m_size)
	{
		return 0;
	}
	//拷贝buffer
	if (m_size > len)
	{
		int newSize = m_size;
		if (len >0)
		{
			delete []buffer;
		}	
		buffer = new char[newSize];
		memcpy(buffer,m_buffer,newSize);
		return newSize;
	} 
	else
	{
		memcpy(buffer,m_buffer,m_size);
		return m_size;
	}
}

size_t ByteArrayMsg::SetBuffer(const void* buffer)
{
	size_t len = 0;
	size_t* ImageSizePtr = NULL;
	//判断消息的类型，根据消息类型返回相应大小
	if(NULL != buffer)  
	{
		unsigned __int8* pMsgType = (unsigned __int8* )buffer;
		switch(*pMsgType)
		{
		case RCS_MSG_IMAGE:	
			ImageSizePtr = (size_t*)((char*)buffer + sizeof(unsigned __int8) + sizeof(RECT));
			len = sizeof(unsigned __int8) + sizeof(RECT) + sizeof(size_t) +*ImageSizePtr;
			//m_size = len;
			break;
		case RCS_MSG_MOUSE:	
			len = 13;
			//m_size = len;
			break;
		case RCS_MSG_KEYBOARD:
			len = 9;
			//m_size = len;
			break;
		case RCS_MSG_USER:
			len = 41;
			//m_size = len;
			break;
		case RCS_MSG_SETUP:
			len = 13;
			//m_size = len;
			break;
		default:
			break;
		}
	}
	//根据消息数据大小分配空间，并拷贝消息数据
	if (len != m_size || m_buffer == NULL)
	{
		delete []m_buffer;
		m_buffer = new char[len];
		memcpy(m_buffer,buffer,len);
		m_size = len;
		return len;
	}
	else
	{
		memcpy(m_buffer,buffer,len);
		m_size = len;
		return len;
	}
}

char* ByteArrayMsg::GetBufferPtr()
{
	return m_buffer;
}

size_t ByteArrayMsg::GetSize()
{
	return m_size;
}

size_t ByteArrayMsg::GetSize( void* buffer,int nSocketBufferSize )
{
	size_t len = 0;
	size_t* ImageSizePtr = NULL;
	if(NULL != buffer)  
	{
		unsigned __int8* pMsgType = (unsigned __int8* )buffer;
		//根据消息类型返回相应的消息大小，除了图像消息之外，
		//其他消息的大小都是固定的所以可以直接返回给定数值
		switch(*pMsgType)
		{
		case RCS_MSG_IMAGE:	
			//当是图像消息时要保证当前传入的缓冲区指针指向的
			//内存还有足够的空间得到图像消息文件头中的图像大小的数据部分
			//图像消息图像大小用4字节表示，具体消息定义请参考图像消息头文件中的定义
			if (nSocketBufferSize > 21)
			{
				ImageSizePtr = (size_t*)((char*)buffer + sizeof(unsigned __int8) + sizeof(RECT));
				len = sizeof(unsigned __int8) + sizeof(RECT) + sizeof(size_t) + *ImageSizePtr;
			}
			break;
		case RCS_MSG_MOUSE:	
			len = 13;
			break;
		case RCS_MSG_KEYBOARD:
			len = 9;
			break;
		case RCS_MSG_USER:
			len = 41;
			break;
		case RCS_MSG_SETUP:
			len = 13;
			break;
		default:
			break;
		}
	}

	return len;
}
