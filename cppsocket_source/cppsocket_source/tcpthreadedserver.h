/***************************************************************************
 *   CPPSocket - library                                                   *
 *                                                                         *
 *   Copyright (C) 2001 by Ralf-Christian Juergensen                       *
 *                         <rcj@users.sourceforge.net>                     *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This library is distributed in the hope that it will be usefull, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      *
 *   Library General Public License for more details.                      *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston,                *
 *   MA 02111-1307, USA                                                    *
 ***************************************************************************/

#ifndef CPPSOCKET_TCPTHREADEDSERVER_H
#define CPPSOCKET_TCPTHREADEDSERVER_H

#ifdef HAVE_LIBPTHREAD

#include <map>
#include <cppsocket/thread.h>
#include <cppsocket/tcpserver.h>

namespace CPPSocket
{
  class TCPServiceFactory;

  /** A TCP server that runs in an own thread.
    * Additionally for every accepted connection a new thread is created.
    *
    * @b Changelog:
    *   - 27.12.2001 The listen-thread does now starting and stopping of the server-socket.
    *                The 'server' sets only a flag in the thread now.
    *
    * @author Ralf-Christian Jürgensen
    */
  class TCPThreadedServer
  {
  public:
    /// Just initialize
    TCPThreadedServer() throw();

    /** Start listening for connections.
      *
      * @param services The factory, that creates the services.
      * @param port The portnumber where the server should listen on. If 0, the next free number is assigned.
      */
    void start(TCPServiceFactory& services, Address::Port port = 0) throw();

    /// Stop listening.
    void stop() throw();

    /// Return the address of the server.
    Address getAddress() throw(Exception);

    /// Return the number of accepted clients. (Includes all; also the connections that are already terminated.)
    int processedClients() throw();

  protected:
    /** The thread that is listening for new connections.
      *
      * All it's data is within the TCPTreadedServer.
      *
      * @author Ralf-Christian Jürgensen
      */
    friend class TCPListen : public Thread
    {
    public:
      TCPThreadedServer* server;
      bool listen;

      /// This method runs in an own thread.
      void run();
    };

    /// The listen-thread.
    TCPListen* listener;

    /// The listen-server.
    TCPServer server;

    /// The factory that creates new services.
    TCPServiceFactory* serviceFactory;

    /// The port the listener should use.
    Address::Port port;

    Semaphore counterSemaphore;
    /// Counts the number of accepted clients.
    int clientCounter;
  };

  /** Service base class
    *
    * @author Ralf-Christian Jürgensen
    */
  class TCPService : public Thread
  {
  public:
    TCPService(TCPConnection* _connection)  throw() : connection(*_connection) {}
    ~TCPService()  throw() { delete &connection; }

  protected:
    /// The connection that is used by this service.
    TCPConnection& connection;
  };

  /** Baseclass for the service factory.
    * Used by the TCPThreadedServer to create the right services.
    *
    * @author Ralf-Christian Jürgensen
    */
  class TCPServiceFactory
  {
  public:
    virtual ~TCPServiceFactory() throw() {}

    /// Used by TCPListen to create new services.
    virtual TCPService* createService(TCPConnection* connection) throw() = 0;
  };

  /** Template class for an easy creation of new service factories.
    *
    * @author Ralf-Christian Jürgensen
    */
  template<class SERVICE>
  class TCPServiceFactoryTemplate : public TCPServiceFactory
  {
  public:
    virtual TCPService* createService(TCPConnection* connection) throw()
    {
      return new SERVICE(connection);
    }
  };
}

#endif

#endif
