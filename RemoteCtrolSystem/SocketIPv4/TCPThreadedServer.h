/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   TCPThreadedServer.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   
**Create date:  2013/04/18   17:18
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
#ifndef __TCPTHREADEDSERVER_H__
#define __TCPTHREADEDSERVER_H__

#include "../Thread/Thread.h"
#include "TCPServer.h"
#include "trace.h"

class TCPServiceFactory;

class TCPThreadedServer
{
	
public:
	TCPThreadedServer(void);
	~TCPThreadedServer(void);

	/**
	   @brief:Start the server
	   @Parameter:TCPServiceFactory & services
	   @Parameter:int port
	   @Return:void
	*/
	void Start(TCPServiceFactory& services,TCPSocketAddress::Port port = 0) throw();
	/// Stop listening.
	void Stop() throw();

	TCPSocketAddress GetAddress() throw (TCPException);
	//  Return the number of accepted clients. (Includes all; 
	// also the connections that are already terminated.)
	int ProcessedClients() throw();
protected:
	 friend class TCPListen;
	 TCPListen*             m_listener;
	 TCPServer              m_server;
	 TCPSocketAddress::Port m_port;
	 TCPServiceFactory*     m_serviceFactory;
	 int                    m_iClientCounter;
};

class TCPService : public Thread
{
public:
	TCPService(TCPConnection* _connection) : connection(*_connection) {}
	~TCPService()  throw() { delete &connection; }

protected:
	/// The connection that is used by this service.
	TCPConnection& connection;
};

class TCPServiceFactory
{
public:
	virtual ~TCPServiceFactory() throw() {}

	/// Used by TCPListen to create new services.
	virtual TCPService* createService(TCPConnection* connection) throw() = 0;
};

template<class SERVICE>
class TCPServiceFactoryTemplate : public TCPServiceFactory
{
public:
	virtual TCPService* createService(TCPConnection* connection) throw()
	{
		//_trace(L"TCPServiceFactoryTemplate::createService\n");
		return new SERVICE(connection);
	}
};


class TCPListen : public Thread
{
public:
	TCPThreadedServer*  m_pThreadedServer;
	bool                m_bListen;

protected:	
	// runs in an own thread.
	void Run();
};
#endif//__TCPTHREADEDSERVER_H__
