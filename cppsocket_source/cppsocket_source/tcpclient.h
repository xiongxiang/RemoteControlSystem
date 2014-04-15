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

#ifndef CPPSOCKET_TCPCLIENT_H
#define CPPSOCKET_TCPCLIENT_H

#include <cppsocket/tcpconnection.h>

namespace CPPSocket
{
  /** This class extends the TCPConnection to a full client.
    * The difference is, that the client can establish a connection.
    *
    * @author Ralf-Christian Jürgensen
    */
  class TCPClient : public TCPConnection
  {
  public:
    /** Connect to server.
      *
      * @param addr Address of the server.
      */
    virtual void connect(const Address& addr) throw (Exception);

    /** Returns client (own) address.
      */
    virtual Address getOwnAddress() throw (Exception);
  };
}

#endif
