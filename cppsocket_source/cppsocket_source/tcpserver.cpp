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

#include <cppsocket/tcpserver.h>

#include <sys/time.h>

namespace CPPSocket
{
  void TCPServer::start(Address::Port port, int queue) throw (Exception)
  {
    socket.open(Socket::TCP);

    socket.bind(Address(Address::ANY_IP, port, false));

    socket.listen(queue);
  }

  void TCPServer::stop() throw (Exception)
  {
    socket.close();
  }

  TCPConnection* TCPServer::getConnection(Address& addr) throw (Exception)
  {
    return new TCPConnection(socket.accept(addr));
  }

  bool TCPServer::wait4Connection(int seconds, int useconds) throw (Exception)
  {
    bool read = true;
    bool write = false;
    bool except = false;
    
    return socket.wait(read, write, except, seconds, useconds);
  }

  Address TCPServer::getAddress() throw (Exception)
  {
    return socket.getsockname();
  }
}
