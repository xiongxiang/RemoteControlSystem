#include "TCPThreadedServer.h"
#include "trace.h"
#include <iostream>

TCPThreadedServer::TCPThreadedServer(void)
:m_listener(NULL),m_serviceFactory(NULL)
{
	//_trace(L"TCPThreadedServer::TCPThreadedServer\n");
}

TCPThreadedServer::~TCPThreadedServer(void)
{
}

void TCPThreadedServer::Start( TCPServiceFactory& services,TCPSocketAddress::Port port /*= 0*/ ) throw()
{
	//_trace(L"TCPThreadedServer::start\n");
	m_serviceFactory =&services;
	m_port= port;
	m_iClientCounter = 0;
	m_listener = new TCPListen;
	m_listener->m_pThreadedServer = this;
	m_listener->m_bListen = true;
	m_listener->Start();
}

void TCPThreadedServer::Stop() throw()
{
	//_trace(L"TCPThreadedServer::Stop\n");
	m_listener->m_bListen  = false;
	m_listener->WaitForEnd();
	m_listener = NULL;
	m_server.Stop();
	m_serviceFactory = 0;
}

TCPSocketAddress TCPThreadedServer::GetAddress() throw (TCPException)
{
	return m_server.GetAddress();
}

int TCPThreadedServer::ProcessedClients() throw()
{
	int count = 0;
	return count;
}

void TCPListen::Run()
{

	//_trace(L"TCPListen::Run\n");
	TCPConnection* connection;
	TCPSocketAddress clientAddress;
	if (m_pThreadedServer!=0)
	{
		//_trace(L"ListenThread::%d\n",GetThreadID());
		m_pThreadedServer->m_server.Start(m_pThreadedServer->m_port);
		while (m_bListen)
		{
			
			if(m_pThreadedServer->m_server.Wait4Connection(2))
			{
				connection = m_pThreadedServer->m_server.GetConnection(clientAddress);

				TCPService* service = m_pThreadedServer->m_serviceFactory->createService(connection);
				service->Start();
			}
		}
	}
}

//void TCPService::Run()
//{
//	std::cout<<"这是个连接的新的线程，线程ID是："<<GetThreadID()<<std::endl;
//
//}
