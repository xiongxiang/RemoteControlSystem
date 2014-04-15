/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:ByteArrayMsg.h
**Latest modified Data:2013-4-1  14:27:19
**Latest Version:v1.0
**Description:
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-1  14:27:19
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
#ifndef __BYTEARRAYMSG_H__
#define __BYTEARRAYMSG_H__

#ifndef NULL
#define NULL 0
#endif

#include "MessageData.h"
class ByteArrayMsg 
		:public MessageData
{
public:
	ByteArrayMsg(void);
	~ByteArrayMsg(void);

	/**
	   @brief:返回消息所属的消息类型
	   @Return:unsigned __int8
	*/
	/**
	   @brief:返回消息类型
	   @Return:unsigned __int8
	*/
	virtual unsigned __int8 GetType() ;
	/**
	   @brief:获取buffer，将消息拷贝到buffer指针指向的内存块中，l
	              en表示buffer指向的内存块的大小。如果len小于消息的大小，
				  将会分配一块新的空间
	   @Parameter:void * buffer
	   @Parameter:size_t len
	   @Return:size_t
	*/
	virtual size_t GetBuffer(void* buffer,size_t len);
	/**
	   @brief:将buffer指向的内存中的消息拷贝到ByteArrayMsg中，
	              使用此函数时要确定传入的buffer指针所指向的缓存中已经完全包含了至少一个消息数据，
				  如果buffer中第一个消息数据不完整，指针将会越界
	   @Parameter:void * buffer
	   @Parameter:size_t len
	   @Return:size_t
	*/
	virtual size_t SetBuffer(const void* buffer);
	/**
	   @brief:返回ByteArrayMsg的buffer的指针，慎重使用，
	              当ByteArrayMsg被销毁之时，这个指针指向的空间将会被释放
	   @Return:char*
	*/
	virtual char* GetBufferPtr();
	/**
	   @brief:返回ByteArrayMsg的buffer大小的字节数
	   @Return:size_t
	*/
	virtual size_t GetSize();
	/**
	   @brief:计算缓冲区中当前buffer的大小，请确定pBuffer指向的是一个消息缓存的第一个字节。
	          ，当消息是图像消息并且nSocketBufferSize小于21字节时，当前缓存区无法完整表示文件头，会返回0
	   @Parameter:void * pBuffer
	   @Parameter:int nSocketBufferSize//表示pBuffer指向的内存块到结尾位置的大小
	   @Return:size_t
	*/
	static  size_t GetSize(void* pBuffer,int nSocketBufferSize);
protected:
	char*	m_buffer;
	size_t	m_size;
};

#endif

