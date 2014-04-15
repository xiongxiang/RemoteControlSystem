#include "SetupMsg.h"
#include <wchar.h>

SetupMsg::SetupMsg(void)
{
	m_buffer	= new char[13];
	m_size		= 13;
}

SetupMsg::~SetupMsg(void)
{
}

int SetupMsg::GetStatusType()
{
	if (m_buffer == NULL)
	{
		return 0;
	}
	char*	pSetupType = m_buffer + 1;
	int		SetupType;
	memcpy(&SetupType,pSetupType,sizeof(SetupType));
	return SetupType;
}

int SetupMsg::GetValue1()
{
	if (m_buffer == NULL)
	{
		return 0;
	}
	char*	pValue = m_buffer + 5;
	int		Value;
	memcpy(&Value,pValue,sizeof(Value));
	return Value;
}

int SetupMsg::GetValue2()
{
	if (m_buffer == NULL)
	{
		return 0;
	}
	char*	pValue = m_buffer + 9;
	int		Value;
	memcpy(&Value,pValue,sizeof(Value));
	return Value;
}

bool SetupMsg::PacketMsg( int setupType,int value1 ,int value2)
{
	__int8 type = RCS_MSG_SETUP;
	size_t newSize = sizeof(type) + sizeof(setupType) + sizeof(value1)+ sizeof(value2);


	//设置消息数据结构请参考头文件中的注释
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

	memcpy(pCur,&setupType,sizeof(setupType));
	pCur += sizeof(setupType);

	memcpy(pCur,&value1,sizeof(value1));
	pCur += sizeof(value1);

	memcpy(pCur,&value2,sizeof(value2));
	pCur = NULL;

	return true;
}
