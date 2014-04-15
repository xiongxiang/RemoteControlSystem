/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:MessageData.h
**Latest modified Data:2013-3-29  16:47:01
**Latest Version:v1.0
**Description:用于网络传输的数据的基类
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-3-29  16:47:01
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
#ifndef __MESSAGEDATA_H__
#define __MESSAGEDATA_H__

// Message definition
#define RCS_MSG_IMAGE		1
#define RCS_MSG_MOUSE		2
#define RCS_MSG_KEYBOARD	3
#define RCS_MSG_USER		4
#define RCS_MSG_SETUP		5

class MessageData
{
public:
	MessageData(void);
	virtual ~MessageData(void);

	/**
	   @brief:返回消息类型
	   @Return:unsigned __int8
	*/
	virtual unsigned __int8 GetType() = 0;
	/**
	   @brief:返回实际储存消息的m_buffer
	   @Parameter:void * buffer
	   @Parameter:size_t len
	   @Return:size_t
	*/
	virtual size_t GetBuffer(void* buffer,size_t len) = 0;
	/**
	   @brief:设置消息
	   @Parameter:void * buffer
	   @Parameter:size_t len
	   @Return:size_t
	*/
	virtual size_t SetBuffer(const void* buffer) = 0;
};
#endif


