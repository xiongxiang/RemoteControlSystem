/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:
**Latest modified Data:
**Latest Version:
**Description:
**
**-------------------------------------------------------------------------
**Create by:    xiongxiang
**Create date:
**Version:
**Description:
**
**
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**
**************************************************************************/
#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "TCPSocket.h"
#include "../Thread/LocalMutex.h"
#include "../Thread/AutoLock.h"
#include <queue>

const int DEFAULTBUFSIZE = 1024*600;

class TCPConnection
{
public:	
	TCPConnection();
	virtual ~TCPConnection(void);

	/**
	   @brief:Close the connection 
	   @Return:void
	*/
	virtual void disconnect() throw(TCPException);
	/**
	   @brief:Send buffer to the socket
	   @Parameter:const TCPBuffer & data
	   @Return:int
	*/
	virtual int send (const TCPBuffer& data) throw (TCPException);
    virtual int send (ByteArrayMsg &data)throw (TCPException);
    virtual int send (char *data, int size)throw (TCPException);
    
	/**
	   @brief:Receive data from the socket, and take by  buffer
	   @Parameter:TCPBuffer & buffer
	   @Return:int
	*/
	virtual int receive(TCPBuffer& buffer) throw (TCPException);
    virtual int receive(ByteArrayMsg& buffer) throw (TCPException);
    virtual int receive(char *data, int size) throw (TCPException);

    /**
       @brief:Receiving message and directly push into message queue
       @Parameter:std::queue<ByteArrayMsg * > & msgQueue
       @Return:int
    */
    virtual int receive(std::queue<ByteArrayMsg *> &msgQueue);
    int DealRecvbuffer(char *tmpbuffer, int byte, std::queue<ByteArrayMsg *> &msgQueue);

	virtual TCPConnection& operator<<(const string& text) throw(TCPException);
	virtual void  operator>>(string& text) throw(TCPException);
	/**
	   @brief:Get connection another peer point address
	   @Return:TCPSocketAddress
	*/
	virtual TCPSocketAddress getConnectedAddress() throw (TCPException);

	/**
	    @brief: Is the connection alive?
	    @Return: bool
	 */
	virtual bool IsConnected() throw();
	/**
	    @brief: set the connection flags
	    @Parameter: int flags
	    @Return: void
	 */
	void SetFlags(int flags) throw();
	/**
	    @brief: Get the connection status
	    @Return: int
	 */
	int  GetFlags() throw(){return m_iFlags;}

protected:
	void  SetConnected(bool _connected) throw();
	/**
	   @brief:Create a connection with socket descriptor
	   @Parameter:descriptor  socket handle
	   @Return:
	*/
	TCPConnection(TCPSocket::Descriptor descriptor);

protected:
	TCPSocket m_socket;
	friend class TCPServer;

private:
	int    m_iFlags;               // For the next recv/send
	bool m_bConnected;     // connection mark
	LocalMutex m_mLocaMutex;
};

#endif//__TCPCONNECTION_H__