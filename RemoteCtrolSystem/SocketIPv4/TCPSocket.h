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
#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include "TCPException.h"
#include "SocketAddress.h"
#include "TCPBuffer.h"
#include "../Message/ByteArrayMsg.h"
#include "../Thread/LocalMutex.h"
#include <WinSock2.h>

#pragma warning(disable:4290)

class TCPSocket
{
public:
	typedef SOCKET Descriptor;
	//Error code when exception happened
	enum ErrorCode
	{
		NOT_OPENED_CODE = 0x0001,
		OPENED_CODE     = 0x0002
	};
	enum Protocol
	{
		TCP = SOCK_STREAM,   //  connection-oriented
		UDP = SOCK_DGRAM     //  connectionless
	};
public:
	TCPSocket(void) ;
	TCPSocket(Descriptor sfd);
	/**
	   @brief:Create a specific protocol socket
	   @Parameter:Protocol protocol
	   @Return:
	*/
	explicit TCPSocket(Protocol protocol);
    ~TCPSocket(void);

	/**
	   @brief:Open a socket in specific protocol
	   @Parameter:Protocol protocol
	   @Return:void
	*/
	void Open(Protocol protocol) throw(TCPException);
	/**
	   @brief:Close the socket
	   @Return:void
	*/
	void Close() throw (TCPException); 
	operator Descriptor() throw(){return m_descriptor;}
	/**
	   @brief:If the descriptor is opened?
	   @Return:bool true descriptor opened, or false
	*/
	bool IsOpened() throw(){return m_descriptor!=INVALID_SOCKET;}
	/**
	   @brief:Bind descriptor to sock address addr
	   @Parameter:addr server address 
	   @Return:void
	*/
	void Bind(const sockaddr_in& addr) 
        throw (TCPException);
	/**
	   @brief:Bind descriptor to address addr
	   @Parameter:addr server address 
	   @Return:void
	*/
	void Bind(const TCPSocketAddress& addr) 
        throw(TCPException);
	/**
	   @brief:Connect to the server, with address addr
	   @Parameter:addr  server addr
	   @Return:void
	*/
	void Connect(const sockaddr_in& addr) 
        throw (TCPException);
	/**
	   @brief:Connect to the server, with address addr
	   @Parameter:addr  server address
	   @Return:void
	*/
	void Connect(const TCPSocketAddress& addr) 
        throw (TCPException);
	/**
	   @brief:Send char buffer to another peer end-point,most used in TCP
	   @Parameter:data  buffer to be sent
	   @Parameter:size  buffer size
	   @Parameter:flags  send flag
	   @Return:int
	*/
	int Send(const char* data, size_t size, int flags = 0 )throw (TCPException);
    int Send(const TCPBuffer& data,int flags=0) throw(TCPException);
	/**
	   @brief:Receive data through opening socket,most used in TCP
	   @Parameter:char * data
	   @Parameter:size_t size
	   @Parameter:int flags
	   @Return:int
	*/
	int Recv(char* data, size_t size, int flags = 0) throw (TCPException);
    int Recv(TCPBuffer& data, int flags = 0) throw (TCPException);
    int Recv(ByteArrayMsg &data, int flags = 0)throw (TCPException);
	/**
	   @brief:Send char buffer to addr,most used in TUDP
	   @Parameter:addr the destination address
       @Parameter:data  buffer to be sent
       @Parameter:size  buffer size
       @Parameter:flags  send flag
	   @Return:int
	*/
	int Sendto(const sockaddr_in& addr,
        const char* data, size_t size, int flags = 0) throw (TCPException) ;
    int Sendto(const TCPSocketAddress& addr, 
        const TCPBuffer& data, int flags = 0) throw (TCPException);
	/**
	   @brief:Receive data through opening socket,from the addr,most used in TCP
	   @Parameter:addr  data where come from
	   @Parameter:data  buffer to take receiving data
	   @Parameter:size  buffer size
	   @Parameter:lags
	   @Return:int
	*/
	int Recvfrom(sockaddr_in& addr, char* data, 
        size_t size, int flags = 0) throw (TCPException);
	int Recvfrom(TCPSocketAddress& addr, 
        TCPBuffer& data, int flags = 0) throw (TCPException);

	/**
	   @brief:Waiting for the connection
	   @Parameter:int queuelen
	   @Return:void
	*/
	void Listen(int queuelen) throw (TCPException);
	/**
	   @brief:Accept the connection and take the peer address
	   @Parameter:sockaddr_in & addr
	   @Return:TCPSocket::Descriptor
	*/
	Descriptor Accept(sockaddr_in& addr) 
        throw (TCPException);
	Descriptor Accept(TCPSocketAddress& addr) 
        throw (TCPException);
	/**
	   @brief:Get socket name through descriptor
	   @Return:TCPSocketAddress
	*/
	TCPSocketAddress GetSockName() throw (TCPException);
	/**
	   @brief:Get peer name through the socket descriptor
	   @Return:TCPSocketAddress
	*/
	TCPSocketAddress GetPeerName() throw (TCPException);
	/**
	   @brief:Wait for special things happened,Socket can 
              be read, write or exception
	   @Parameter:bool & read
	   @Parameter:bool & write
	   @Parameter:bool & exception
	   @Parameter:int seconds
	   @Parameter:int useconds
	   @Return:int
	*/
	int Wait(bool& read, bool& write, bool& exception, 
        int seconds = 0, int useconds = 0) throw (TCPException);

	int SetRecvBufLength(int recvlength);
	int SetSendBufLength(int recvlength);

	int SetNodelay(bool delay);

private:
	Descriptor m_descriptor;        // Socket number
    LocalMutex  *m_localmutex;  // Thread safety
};


#endif//__TCPSOCKET_H__