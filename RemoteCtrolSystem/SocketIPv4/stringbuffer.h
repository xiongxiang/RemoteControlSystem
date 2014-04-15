/************************************************************************/
/* 在使用StringBuffer.pointer()接收数据之前，必须调用prepare函数，
   完了再调用update函数更新数据到StringBuffer中
/* 
/************************************************************************/
#ifndef CPPSOCKET_STRINGBUFFER_H
#define CPPSOCKET_STRINGBUFFER_H

#include "buffer.h"

  using std::string;

  /** Buffer for text-transport.    *
    * The size is including the terminating zero.
    */
  class StringBuffer : public Buffer
  {
  public:
    enum { DEFAULT_BUFFER_SIZE = 4096 };

    StringBuffer(const string& text) throw();
    StringBuffer(size_t tempBufferSize = DEFAULT_BUFFER_SIZE) throw();
    ~StringBuffer() throw();

    operator string &() throw();

//   protected:
    virtual size_t size() const throw();
    virtual char* pointer() throw();
    virtual const char* pointer() const throw();
    virtual void prepare() throw();
    virtual void update(size_t) throw();

  private:
    /// Buffered text
    string buffer;
    /// Pointer to temporary buffer.
    char* ptrToBuffer;
    /// Size of temporary buffer.
    size_t bufferSize;
  };

#endif
