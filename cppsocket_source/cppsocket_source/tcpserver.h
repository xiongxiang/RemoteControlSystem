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

#ifndef CPPSOCKET_TCPSERVER_H
#define CPPSOCKET_TCPSERVER_H

#include <cppsocket/tcpconnection.h>

namespace CPPSocket
{
  /** A simple TCP based server.
    *
    * @b Changelog:
    *   - 27.12.2001 added wait4Connection() which uses select()
    *
    * @author Ralf-Christian Jürgensen
    */
  class TCPServer
  {
  public:
    /** Start listening on @e port.
      *
      * @param port Portnumber to listen. When 0, the next free number is assigned.
      * @param queue Maximum of clients that can be in the wait-queue.
      */
    void start(Address::Port port = 0, int queue = 5) throw (Exception);

    /** Stop listening on the socket.
      * All accepted connections are @b not closed.
      */
    void stop() throw (Exception);

    /** Get a new connection.
      * If no connection is available, the methods blocks until a connection arrives.
      * If you don't want this to block your process, use wait4Connection() first.
      *
      * @param addr This out-parameter get the address of the connected client.
      *
      * @return The pointer to the new connection. Delete when not needed anymore.
      */
    TCPConnection* getConnection(Address& addr) throw (Exception);

    /** Wait until a new connection arrives or a timeout occurrs.
      *
      * @param seconds Set full second timeout to n seconds.
      * @param useconds Set microsecond timeout to n microseconds.
      *
      * @return @c true if new connection available, @c false if it timed out.
      */
    bool wait4Connection(int seconds=0, int useconds=0) throw (Exception);

    /// Returns server (own) address. Use when you started the server with port 0, to get the assigned number.
    Address getAddress() throw (Exception);

  protected:
    /// The socket where the server listens for new connections.
    Socket socket;
  };
}

#endif
