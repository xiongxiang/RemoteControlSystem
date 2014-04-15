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

#include <cppsocket/tcpconnection.h>
#include <cppsocket/stringbuffer.h>
#include <iostream>

namespace CPPSocket
{
  TCPConnection::TCPConnection(Socket::Descriptor descriptor) throw()
    : socket(descriptor)
    , flags(0)
    , connected(true)
  {}

  TCPConnection::TCPConnection() throw()
    : flags(0)
    , connected(false)
  {}

  void TCPConnection::disconnect() throw (Exception)
  {
    socket.close();
    
    connected = false;
  }

  bool TCPConnection::isConnected() throw ()
  {
    return connected;
  }
 
  void TCPConnection::setConnected(bool _connected) throw()
  {
    connected = _connected;
  }
  
  int TCPConnection::send(const Buffer& data) throw (Exception)
  {
    return socket.send(data, flags);
  }

  int TCPConnection::receive(Buffer& data) throw (Exception)
  {
    return socket.recv(data, flags);
  }

  TCPConnection& TCPConnection::operator<<(const string& text) throw (Exception)
  {
    StringBuffer buffer = text;

    send(buffer);

    return *this;
  }

  void TCPConnection::operator>>(string& text) throw (Exception)
  {
    StringBuffer buffer;

    receive(buffer);

    text = buffer;
  }

  Address TCPConnection::getConnectedAddress() throw (Exception)
  {
    return socket.getpeername();
  }

  void TCPConnection::setFlags(int _flags) throw()
  {
    flags = _flags;
  }
}
