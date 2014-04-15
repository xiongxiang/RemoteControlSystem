/************************************************************************/
/* 在使用StringBuffer.pointer()接收数据之前，必须调用prepare函数，
   完了再调用update函数更新数据到StringBuffer中
/* 
/************************************************************************/
#ifndef CPPSOCKET_STRINGBUFFER_H
#define CPPSOCKET_STRINGBUFFER_H

#include "TCPBuffer.h"

  using std::string;

  /** 
    * Buffer for text-transport.    *
    * The size is including the terminating zero.
    */
  class TCPStringBuffer : public TCPBuffer
  {
  public:
    enum { DEFAULT_BUFFER_SIZE = 18 };

    TCPStringBuffer(const string& text) throw();
    TCPStringBuffer(size_t tempBufferSize = DEFAULT_BUFFER_SIZE) throw();
    ~TCPStringBuffer() throw();

    operator string &() throw();
   
	/** 
    * get the buffer size
    * The size is including the terminating zero.
    */
    virtual size_t Size() const throw();

   /** 
    * get the buffer address , point to the char address
    * The size is including the terminating zero.
    */
    virtual char* Pointer() throw();
    virtual const char* Pointer() const throw();

    virtual void Prepare() throw();
    virtual void Update(size_t) throw();

  private:
    
    string  m_strBuffer;         /// Buffered text    
    char*  m_pPtrToBuffer;      /// Pointer to temporary buffer.
    size_t  m_stBufferSize;      /// Size of temporary buffer.
  };

#endif
