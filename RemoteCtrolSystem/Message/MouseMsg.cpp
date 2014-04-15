#include "MouseMsg.h"
#include <wchar.h>

MouseMsg::MouseMsg(void)
{
	m_buffer	= new char[13];
	m_size		= 13;
}

MouseMsg::~MouseMsg(void)
{
}

int MouseMsg::GetMouseX()
{
	if (m_buffer == NULL)
	{
		return -1;
	}
	char* pX = m_buffer + 1;
	int   x;
	memcpy(&x,pX,sizeof(x));
	return x;
}

int MouseMsg::GetMouseY()
{
	if (m_buffer == NULL)
	{
		return -1;
	}
	char* pY = m_buffer + 5;
	int   y;
	memcpy(&y,pY,sizeof(y));
	return y;
}

int MouseMsg::GetMouseStatus()
{
	if (m_buffer == NULL)
	{
		return 0;
	}
	char* pStatus = m_buffer + 9;
	int   status;
	memcpy(&status,pStatus,sizeof(status));
	return status;
}

bool MouseMsg::PacketMsg( int x,int y,int status )
{
	__int8 type = RCS_MSG_MOUSE;
	size_t newSize = sizeof(type) + sizeof(x) + sizeof(y) + sizeof(status);


	//鼠标消息数据结构请参考头文件中的注释
	//根据消息数据结构，将需要打包的数据拷贝到一个字节数组m_buffer中
	if (m_size < newSize)
	{
		if (m_buffer != NULL)
		{
			delete m_buffer;
		}

		m_buffer = new char[newSize];
		m_size = newSize;
	}
	char* pCur = m_buffer;
	memcpy(pCur,&type,sizeof(type));
	pCur += sizeof(type);

	memcpy(pCur,&x,sizeof(x));
	pCur += sizeof(x);

	memcpy(pCur,&y,sizeof(y));
	pCur += sizeof(y);

	memcpy(pCur,&status,sizeof(status));
	pCur = NULL;

	return true;
}
