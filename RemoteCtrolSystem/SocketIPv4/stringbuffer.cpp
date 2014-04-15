#include "stringbuffer.h"


  size_t StringBuffer::size() const throw()
  {
    return buffer.length() + 1;
  }

  char* StringBuffer::pointer() throw()
  {
    return ptrToBuffer;
  }

  const char* StringBuffer::pointer() const throw()
  {
    return buffer.c_str();
  }

  void StringBuffer::prepare() throw()
  {
    buffer.resize(bufferSize-1);
    delete[] ptrToBuffer;
    ptrToBuffer = new char[bufferSize];
    memset(ptrToBuffer, 0, bufferSize);
  }

  void StringBuffer::update(size_t) throw()
  {
	//把缓存ptrToBuffer的内容更新到buffer中。
    buffer = ptrToBuffer;
    delete[] ptrToBuffer;
    ptrToBuffer = NULL;
  }

  StringBuffer::StringBuffer(const string& text) throw()
    : buffer(text)
    , ptrToBuffer(NULL)
    , bufferSize(DEFAULT_BUFFER_SIZE)
  {}

  StringBuffer::StringBuffer(size_t tempBufferSize) throw()
    : ptrToBuffer(NULL)
    , bufferSize(tempBufferSize)
  {
    buffer.resize(bufferSize-1);
  }

  StringBuffer::~StringBuffer() throw()
  {
    delete[] ptrToBuffer;
  }

  StringBuffer::operator string&() throw()
  {
    return buffer;
  }

