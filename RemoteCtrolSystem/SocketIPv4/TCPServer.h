/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   TCPServer.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   
**Create date:  2013/04/18   17:17
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
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "TCPSocket.h"
#include "TCPException.h"
#include "SocketAddress.h"
#include "TCPConnection.h"

class TCPServer
{
public:
	TCPServer(void);
	~TCPServer(void);

	/**
	    @brief: Starting dealing the connection from the client
	    @Parameter: TCPSocketAddress::Port port
	    @Parameter: int queue
	    @Return: void
	 */
	void Start(TCPSocketAddress::Port port = 0, int queue = 20) throw (TCPException);
	/**
	    @brief: Close a connection
	    @Return: void
	 */
	void Stop() throw (TCPException);  
	/**
	    @brief: Wait for the connection in a single thread
	    @Parameter: int seconds
	    @Parameter: int useconds
	    @Return: bool
	 */
	bool Wait4Connection(int seconds=0, int useconds=0) throw (TCPException);
	/**
	    @brief: Get a connection
	    @Parameter: TCPSocketAddress & addr
	    @Return: TCPConnection*
	 */
	TCPConnection*    GetConnection(TCPSocketAddress& addr) throw (TCPException);
	/**
	    @brief: Get the connected client's address
	    @Return: TCPSocketAddress
	 */
	TCPSocketAddress GetAddress() throw (TCPException);

protected:
	TCPSocket m_socket;
};
#endif//__TCPSERVER_H__
