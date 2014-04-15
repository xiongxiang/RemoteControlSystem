#include "TCPServer.h"
#include "trace.h"

TCPServer::TCPServer(void)
{
}

TCPServer::~TCPServer(void)
{
}

void TCPServer::Start(TCPSocketAddress::Port port /*= 0*/, int queue /*= 5*/ ) throw (TCPException)
{
	//_trace(L"TCPServer::start\n");
	m_socket.Open(TCPSocket::TCP);
	m_socket.Bind(TCPSocketAddress(TCPSocketAddress::ANY_IP,port,false));		
	m_socket.Listen(queue);
}

void TCPServer::Stop() throw (TCPException)
{
	//_trace(L"TCPServer::stop\n");
	m_socket.Close();
}

TCPConnection* TCPServer::GetConnection( TCPSocketAddress& addr ) throw (TCPException)
{
	//_trace(L"TCPServer::getConnection\n");
	return new TCPConnection(m_socket.Accept(addr));
}

bool TCPServer::Wait4Connection( int seconds/*=0*/, int useconds/*=0*/ ) throw (TCPException)
{
	//_trace(L"TCPServer::wait4Connection\n");
	bool read = true;
	bool write = false;
	bool except = false;
	return (bool)(m_socket.Wait(read,write,except,seconds,useconds));
}

TCPSocketAddress TCPServer::GetAddress() throw (TCPException)
{
	return m_socket.GetSockName();
}
