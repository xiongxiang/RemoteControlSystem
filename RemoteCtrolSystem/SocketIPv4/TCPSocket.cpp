#include "TCPSocket.h"
#include "trace.h"
#pragma comment(lib,"Ws2_32.lib")

TCPSocket::TCPSocket(void) 
:m_descriptor(INVALID_SOCKET)
{
	m_localmutex = new LocalMutex;
}

TCPSocket::TCPSocket( Descriptor sfd ) 
:m_descriptor(sfd)
{
	m_localmutex = new LocalMutex;
}

TCPSocket::TCPSocket( Protocol protocol )
{
	m_localmutex = new LocalMutex;
	Open(protocol);
}

TCPSocket::~TCPSocket(void)
{
    delete m_localmutex;
	if (IsOpened())
	{
		::closesocket(m_descriptor);
	}	
}


int TCPSocket::Recvfrom( sockaddr_in& addr, 
						char* data, size_t size, int flags /*= 0*/ ) throw (TCPException)
{
	int bytes;

	if(!IsOpened())
	{
		throw TCPException("Socket::recvfrom", "Socket没有打开", 0);
	}
	int SenderAddrSize = sizeof(addr);
	sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&addr);
	bytes = ::recvfrom(m_descriptor, data, size, 
		flags, socketAddress, &SenderAddrSize);
	if (bytes ==  SOCKET_ERROR)
	{
		throw TCPException("Socket::recvfrom","recvFrom函数失败");
	}
	return bytes;
}

int TCPSocket::Recvfrom(TCPSocketAddress& addr, 
						TCPBuffer& data, int flags /* = 0 */) throw (TCPException)
{
	int bytes;
	data.Prepare();
	sockaddr_in address = addr;
	bytes = Recvfrom(address,data.Pointer(),data.Size(),flags);
	addr = address;
	data.Update(bytes);
	return bytes;
}

void TCPSocket::Open( Protocol protocol ) throw (TCPException)
{
	if (IsOpened())
	{
		throw TCPException("Socket::Open","重复打开");
	}
	m_descriptor = socket(AF_INET,protocol,0);
	if (m_descriptor == SOCKET_ERROR)
	{
		throw TCPException("Socket::Open","创建失败",0);
	}
}

void TCPSocket::Close()
{
	if(IsOpened())
	{
		::closesocket(m_descriptor);
		//WSACleanup();
		m_descriptor  = INVALID_SOCKET;
	}
	
}

void TCPSocket::Bind( const sockaddr_in& addr )
{
	int error;
	if (!IsOpened())
	{
		throw TCPException("Socket::bind","Socket没有打开");
	}
	const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);
	error = ::bind(m_descriptor,socketAddress,sizeof(addr));
	if(error == SOCKET_ERROR )
	{
		throw TCPException("Socket::bind","绑定Socket失败",error);
	}
}

void TCPSocket::Bind(const TCPSocketAddress& addr) throw(TCPException)
{
	Bind(static_cast<const sockaddr_in>(addr));
}

void TCPSocket::Connect( const sockaddr_in& addr ) throw(TCPException)
{
	int error;
	if(!IsOpened())
	{
		throw TCPException("Socket::connect", "Socket没有打开");
	}
	const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);
	error = ::connect(m_descriptor, socketAddress, sizeof(addr));
	if (error ==  SOCKET_ERROR)
	{
		//throw TCPException("Socket::connect","Socket连接出错",error);
	}
}

int TCPSocket::Send( const char* data, size_t size, int flags /*= 0 */ )
{
	
    //m_localmutex->Lock();
	int bytes;
	if(!IsOpened())
	{
		throw TCPException("Socket::send", "Socket没有开打", 0);
	}
	bytes = ::send(m_descriptor,data,size,flags);
    return bytes;
}

int TCPSocket::Send( const TCPBuffer& data,int flags/*=0*/ ) throw(TCPException)
{
	return Send(data.Pointer(),data.Size(),flags);
}

int TCPSocket::Sendto( const sockaddr_in& addr, 
					  const char* data, size_t size, int flags /*= 0*/ )
{
	int bytes;

	if(!IsOpened())
	{
		throw TCPException("Socket::sendto", "Socket没有打开", 0);
	}
	const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);
	bytes = ::sendto(m_descriptor, data, size, flags, socketAddress, sizeof(addr));
	if(bytes == SOCKET_ERROR)
	{
		throw TCPException("Socket::sendto", "sendto出错");
	}
	return bytes;
}

int TCPSocket::Sendto( const TCPSocketAddress& addr, 
					  const TCPBuffer& data, int flags /*= 0*/ ) throw (TCPException)
{
	return Sendto(addr,data.Pointer(),data.Size(),flags);
}

int TCPSocket::Recv( char* data, size_t size, int flags /*= 0*/ )
{
	int bytes;

	if(!IsOpened())
	{
		throw TCPException("Socket::recv", "Socket没有打开");
	}
	bytes = ::recv(m_descriptor, data, size, flags);
	//_trace(L"TCPSocket::Recv \n");
	return bytes;
}

int TCPSocket::Recv( TCPBuffer& data, int flags /*= 0*/ ) throw (TCPException)
{
	int bytes = Recv(data.Pointer(),data.Size(),flags);
	return bytes;
}

// FIXME to detect the performers
char buffer[4096];

int TCPSocket::Recv( ByteArrayMsg &data, int flags/* = 0*/ ) throw (TCPException)
{
	int bytes = Recv(buffer,4096,flags);
	data.SetBuffer(buffer);
    return bytes;
}

void TCPSocket::Listen( int queuelen ) throw (TCPException)
{
	int error;

	if(!IsOpened())
	{
		throw TCPException("Socket::listen","Socket未打开");
	}

	error = ::listen(m_descriptor, queuelen);
	if(error == SOCKET_ERROR)
	{
		throw TCPException("Socket::listen","listen函数有错误");
	}
}

TCPSocket::Descriptor TCPSocket::Accept( sockaddr_in& addr ) throw (TCPException)
{
	Descriptor sfd;
	if(!IsOpened())
	{
		throw TCPException("Socket::accept","Socket未打开");
	}

	int addrLen = sizeof(addr);
	sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&addr);
	sfd = ::accept(m_descriptor, socketAddress, &addrLen);
	if(sfd == SOCKET_ERROR)
	{
		int errorCode = WSAGetLastError();
		throw TCPException("Socket::accept","::accept函数发生错误");
	}
	return sfd;
}

TCPSocket::Descriptor TCPSocket::Accept(TCPSocketAddress& addr) throw (TCPException)
{
	Descriptor tempSocket;
	sockaddr_in address = addr;
	tempSocket = Accept(address);
	addr = address;
	return tempSocket;
}

int TCPSocket::Wait( bool& read, bool& write, bool& exception, 
					int seconds /*= 0*/, int useconds /*= 0*/ ) throw (TCPException)
{
	if(!IsOpened())
	{
		throw TCPException("Socket::wait","Socket未打开",NOT_OPENED_CODE);
	}

	struct timeval time;
	time.tv_sec = seconds;
	time.tv_usec = useconds;

	fd_set* readfds = NULL;
	fd_set* writefds = NULL;
	fd_set* exceptfds = NULL;

	if (read)
	{
		readfds = new fd_set;
		FD_ZERO(readfds);
		FD_SET(m_descriptor,readfds);
	}

	if (write)
	{
		writefds = new fd_set;
		FD_ZERO(writefds);
		FD_SET(m_descriptor,writefds);
	}

	if (exceptfds)
	{
		exceptfds = new fd_set;
		FD_ZERO(exceptfds);
		FD_SET(m_descriptor,exceptfds);
	}
	
	int ret = select(m_descriptor+1,readfds,writefds,exceptfds,&time);
	
	if (read)
	{
		//检查m_descriptor在readfds集合中的状态是否发生变化，返回true，表示有变化
		read = (bool)(FD_ISSET(m_descriptor,readfds));
	}

	if(write)
	{
		write = (bool)(FD_ISSET(m_descriptor,writefds));
	}

	if (exception)
	{
		exception = (bool)(FD_ISSET(m_descriptor,exception));
	}
	delete readfds;
	delete writefds;
	delete exceptfds;

	if (ret < 0)
	{
		throw TCPException("Socket::wait","select 发生错误");
	}
	return (ret!=0);
}

void TCPSocket::Connect(const TCPSocketAddress& addr) throw(TCPException)
{
	Connect(static_cast<const sockaddr_in>(addr));
}

TCPSocketAddress TCPSocket::GetSockName() throw (TCPException)
{
	int error;
	if (!IsOpened())
	{
		throw TCPException("Socket::getsockname()","Socket未打开");
	}
	sockaddr_in address;
	int addrLen = sizeof(address);
	sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&address);
	error = ::getsockname(m_descriptor,socketAddress,&addrLen);
	if (error ==  SOCKET_ERROR)
	{
		throw TCPException("Socket::getSockName","getsockname有异常");
	}
	return TCPSocketAddress(address);
}

TCPSocketAddress TCPSocket::GetPeerName() throw (TCPException)
{
	int error;

	if(!IsOpened())
	{
		throw TCPException("Socket::getPeerName","Socket未打开");
	}
	sockaddr_in address;
	int addrLen = sizeof(address);
	sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&address);
	error = ::getpeername(m_descriptor, socketAddress, &addrLen);

	if(error == SOCKET_ERROR)
	{
		throw TCPException("Socket::getPeerName0","getpeername出错");
	}

	return TCPSocketAddress(address);
}

int TCPSocket::SetRecvBufLength(int recvlength)
{
	return (::setsockopt(m_descriptor, SOL_SOCKET, 
		SO_RCVBUF, (char *)&recvlength, sizeof(recvlength)));
}

int TCPSocket::SetSendBufLength(int sendlength)
{
	return (::setsockopt(m_descriptor, SOL_SOCKET, 
		SO_SNDBUF, (char *)&sendlength, sizeof(sendlength)));
}

int TCPSocket::SetNodelay(bool delay)
{
	return ::setsockopt(m_descriptor, IPPROTO_TCP, 
		TCP_NODELAY,(char *)&delay, sizeof(int));
}