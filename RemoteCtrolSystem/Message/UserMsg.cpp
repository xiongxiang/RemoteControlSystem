#include "UserMsg.h"
#include <wchar.h>

UserMsg::UserMsg(void)
{
	m_buffer	= new char[41];
	m_size		= 41;
}

UserMsg::~UserMsg(void)
{
}

bool UserMsg::GetUsername(char* pUsername)
{
	if (NULL == pUsername || NULL == m_buffer)
	{
		return false;
	}
	memcpy(pUsername,m_buffer+1,20);
	return true;
}

bool UserMsg::GetPassword(char* pPassword)
{
	if (NULL == pPassword || NULL == m_buffer)
	{
		return false;
	}
	memcpy(pPassword,m_buffer+21,20);
	return true;
}

bool UserMsg::PacketMsg( char* username,char* password )
{
	__int8 type = RCS_MSG_USER;
	size_t newSize = sizeof(type) + 20 + 20;


	//用户账户密码消息数据结构请参考头文件中的注释
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

	memcpy(pCur,username,20);
	pCur += 20;

	memcpy(pCur,password,20);
	pCur = NULL;

	return true;
}
