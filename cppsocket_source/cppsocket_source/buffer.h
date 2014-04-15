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

#ifndef CPPSOCKET_BUFFER_H
#define CPPSOCKET_BUFFER_H

#include <sys/types.h>
#include <string>
#include <cppsocket/netint.h>

namespace CPPSocket
{
  /** An interface for a data-transport-buffer.
    * This interface is only for the Socket-Class that must have access to the pointer of the
    * data. Therefore all methods are protected.
    *
    * @author Ralf-Christian Jürgensen
    */
  class Buffer
  {
    friend class Socket;

  protected:
    /// Returns the pointer to the data. (write access)
    virtual char* pointer() throw() = 0;
    /// Returns the pointer to the data. (read access)
    virtual const char* pointer() const throw() = 0;
    /// Returns the buffer size in bytes.
    virtual size_t size() const throw() = 0;
    /// Used by recv() and recvfrom() to prepare buffer before putting data into buffer.
    virtual void prepare() throw() = 0;
    /// Called by recv() and recvfrom() when data is transfered.
    virtual void update(size_t bytes) throw() = 0;

  public:
    virtual ~Buffer() throw() {}
  };
}

#endif
