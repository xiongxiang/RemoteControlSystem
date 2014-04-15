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

#ifndef CPPSOCKET_STRINGBUFFER_H
#define CPPSOCKET_STRINGBUFFER_H

#include <cppsocket/buffer.h>

namespace CPPSocket
{
  using std::string;

  /** Buffer for text-transport.
    *
    * The size is including the terminating zero.
    *
    * @author Ralf-Christian Jürgensen
    */
  class StringBuffer : public Buffer
  {
  public:
    enum { DEFAULT_BUFFER_SIZE = 4096 };

    StringBuffer(const string& text) throw();
    StringBuffer(size_t tempBufferSize = DEFAULT_BUFFER_SIZE) throw();
    ~StringBuffer() throw();

    operator string &() throw();

  protected:
    virtual size_t size() const throw();
    virtual char* pointer() throw();
    virtual const char* pointer() const throw();
    virtual void prepare() throw();
    virtual void update(size_t) throw();

  private:
    /// Buffered text
    string buffer;
    /// Pointer to temporary buffer.
    char* ptrToBuffer;
    /// Size of temporary buffer.
    size_t bufferSize;
  };
}

#endif
