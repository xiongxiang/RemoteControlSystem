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

#ifndef CPPSOCKET_TCPCONNECTION_H
#define CPPSOCKET_TCPCONNECTION_H

#include <cppsocket/socket.h>

namespace CPPSocket
{
  /** This is the base class for data transfer over TCP.
    * The server creates one when a client has connected.
    * And the client extends this with the ability to connect itself.
    *
    * @b Changelog:
    * - 13.06.2002 added possibility to set send/receive flags
    * - 10.05.2002 operator<<() now returns reference to TCPConnection.
    *
    * @author Ralf-Christian Jürgensen
    */
  class TCPConnection
  {
  public:
    /// Create a closed and uninitialzed connection.
    TCPConnection() throw();

    virtual ~TCPConnection() throw() {}
    
    /// Close connection.
    virtual void disconnect() throw (Exception);

    /** Send data over the connection.
      * No flags are used.
      *
      * @param data Buffer containing the data to be sent.
      * @return Number of sent bytes.
      */
    virtual int send(const Buffer& data) throw (Exception);

    /** Receive data from connection.
      * No flags are used.
      *
      * @param data Buffer to save received data.
      * @return Number of received bytes.
      */
    virtual int receive(Buffer& data) throw (Exception);

    /// Send text.
    virtual TCPConnection& operator<<(const string& text) throw (Exception);

    /** Receive text.
      * The maximum text length is 4 kb.
      */
    virtual void operator>>(string& text) throw (Exception);

    /// Returns address of the connected socket.
    virtual Address getConnectedAddress() throw (Exception);

    /// Returns true if the connection is open.
    virtual bool isConnected() throw();

    /// Set flags to be used on next send or receive.
    void setFlags(int flags) throw();

    /// Get current flags.
    int getFlags() throw() { return flags; }

  protected:
    Socket socket;
    
    void setConnected(bool _connected) throw();
    
    friend class TCPServer;

    /** Create a connection from an opened socket (-descriptor).
      *
      * @param descriptor The descriptor of an open socket.
      */
    TCPConnection(Socket::Descriptor descriptor) throw();
    
  private:
    /// Socket flags for send/receive.
    int flags;
    
    /// Flag for connection status. Abstracts from Socket::isOpened()
    bool connected;
  };
}

#endif
