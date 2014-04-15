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

#include <cppsocket/tcpthreadedserver.h>

#ifdef HAVE_LIBPTHREAD

namespace CPPSocket
{
  void TCPThreadedServer::TCPListen::run()
  {
    TCPConnection* connection;
    Address clientAddress;

    if(server != 0)
    {
      server->server.start(server->port);

      while(listen)
      {
        // wait for new connection and set the timeout to 1 sec
        if(server->server.wait4Connection(1))
        {
          connection = server->server.getConnection(clientAddress);

          TCPService* service = server->serviceFactory->createService(connection);
          service->start();

          --(server->counterSemaphore);
          server->clientCounter++;
          ++(server->counterSemaphore);
        }
      }

      server->server.stop();
    }
  }

  TCPThreadedServer::TCPThreadedServer() throw()
    : listener(0)
    , serviceFactory(0)
  {}

  void TCPThreadedServer::start(TCPServiceFactory & services, Address::Port _port) throw()
  {
    serviceFactory = &services;
    port = _port;

    clientCounter = 0;

    listener = new TCPListen;
    listener->server = this;
    listener->listen = true;
    listener->start();
    
//    listener->join();
  }

  void TCPThreadedServer::stop() throw()
  {
    listener->listen = false;
    listener->join();
    listener = 0;

    serviceFactory = 0;
  }

  Address TCPThreadedServer::getAddress() throw (Exception)
  {
    return server.getAddress();
  }

  int TCPThreadedServer::processedClients() throw()
  {
    int count;

    --counterSemaphore;
    count = clientCounter;
    ++counterSemaphore;

    return count;
  }
}

#endif
