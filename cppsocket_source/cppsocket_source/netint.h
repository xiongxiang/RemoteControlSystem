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

#ifndef CPPSOCKET_NETINT_H
#define CPPSOCKET_NETINT_H

#include <netinet/in.h>

namespace CPPSocket
{
  /** A 32-Bit int in netbyteorder
    *
    * @author Ralf-Christian Jürgensen
    */
  class NetInt32
  {
  public:
    NetInt32(uint32_t val = 0) throw()
    {
      value = htonl(val);
    }

    uint32_t operator=(uint32_t val) throw()
    {
      value = htonl(val);

      return val;
    }

    operator uint32_t() const throw()
    {
      return ntohl(value);
    }

  private:
    uint32_t value;
  };

  /** A 16-Bit int in netbyteorder
    *
    * @author Ralf-Christian Jürgensen
    */
  class NetInt16
  {
  public:
    NetInt16(uint16_t val = 0) throw()
    {
      value = htons(val);
    }

    uint16_t operator=(uint16_t val) throw()
    {
      value = htons(val);

      return val;
    }

    operator uint16_t() const throw()
    {
      return ntohs(value);
    }

  private:
    uint16_t value;
  };
}
#endif
