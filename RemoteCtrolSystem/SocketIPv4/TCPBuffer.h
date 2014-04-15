#ifndef CPPSOCKET_BUFFER_H
#define CPPSOCKET_BUFFER_H

#include <string>

/**
@brief::An interface for a data-transport-buffer.
 *          This interface is only for the Socket-Class that must have access
 *          to the pointer of the data. Therefore all methods are protected.
 *
 */
  class TCPBuffer
  {
      friend class TCPSocket;
  public:
      virtual ~TCPBuffer() throw() {}

  protected:
    /**
       @brief:Returns the pointer to the data. (write access)
       @Return:char*
    */
    virtual char* Pointer() throw() = 0;

    /**
       @brief:Returns the pointer to the data. (read access)
       @Return:const char*
    */
    virtual const char* Pointer() const throw() = 0;

    /**
       @brief:Returns the buffer size in bytes.
       @Return:size_t
    */
    virtual size_t Size() const throw() = 0;
    /**
       @brief:Used by recv() and recvfrom() to prepare 
              buffer before putting data into buffer.
       @Return:void
    */
    virtual void Prepare() throw() = 0;
    /**
       @brief:Called by recv() and recvfrom() when 
              data is transfered.
       @Parameter:size_t bytes
       @Return:void
    */
    virtual void Update(size_t bytes) throw() = 0;

  };

#endif
