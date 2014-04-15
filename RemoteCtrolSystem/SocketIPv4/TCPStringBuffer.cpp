#include "TCPStringBuffer.h"


size_t TCPStringBuffer::Size() const throw()
{
    return m_strBuffer.length() + 1;
}

char* TCPStringBuffer::Pointer() throw()
{
    //return m_pPtrToBuffer;
    return const_cast<char *> (m_strBuffer.c_str());
}

const char* TCPStringBuffer::Pointer() const throw()
{
    return m_strBuffer.c_str();
}

void TCPStringBuffer::Prepare() throw()
{
    m_strBuffer.resize(m_stBufferSize-1);
    delete[] m_pPtrToBuffer;
    m_pPtrToBuffer = new char[m_stBufferSize];
    memset(m_pPtrToBuffer, 0, m_stBufferSize);
}

void TCPStringBuffer::Update(size_t) throw()
{
    //把缓存ptrToBuffer的内容更新到buffer中。
    m_strBuffer = m_pPtrToBuffer;
    delete[] m_pPtrToBuffer;
    m_pPtrToBuffer = NULL;
}

TCPStringBuffer::TCPStringBuffer(const string& text) throw()
: m_strBuffer(text)
, m_pPtrToBuffer(NULL)
, m_stBufferSize(DEFAULT_BUFFER_SIZE)
{}

TCPStringBuffer::TCPStringBuffer(size_t tempBufferSize) throw()
: m_pPtrToBuffer(NULL)
, m_stBufferSize(tempBufferSize)
{
    m_strBuffer.resize(m_stBufferSize-1);
}

TCPStringBuffer::~TCPStringBuffer() throw()
{
    delete[] m_pPtrToBuffer;
}

TCPStringBuffer::operator string&() throw()
{
    return m_strBuffer;
}

