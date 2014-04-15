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

#include <cppsocket/stringbuffer.h>

namespace CPPSocket
{
  size_t StringBuffer::size() const throw()
  {
    return buffer.length() + 1;
  }

  char* StringBuffer::pointer() throw()
  {
    return ptrToBuffer;
  }

  const char* StringBuffer::pointer() const throw()
  {
    return buffer.c_str();
  }

  void StringBuffer::prepare() throw()
  {
    buffer.resize(bufferSize-1);

    delete[] ptrToBuffer;

    ptrToBuffer = new char[bufferSize];

    memset(ptrToBuffer, 0, bufferSize);
  }

  void StringBuffer::update(size_t) throw()
  {
    buffer = ptrToBuffer;

    delete[] ptrToBuffer;
    ptrToBuffer = NULL;
  }

  StringBuffer::StringBuffer(const string& text) throw()
    : buffer(text)
    , ptrToBuffer(NULL)
    , bufferSize(DEFAULT_BUFFER_SIZE)
  {}

  StringBuffer::StringBuffer(size_t tempBufferSize) throw()
    : ptrToBuffer(NULL)
    , bufferSize(tempBufferSize)
  {
    buffer.resize(bufferSize-1);
  }

  StringBuffer::~StringBuffer() throw()
  {
    delete[] ptrToBuffer;
  }

  StringBuffer::operator string&() throw()
  {
    return buffer;
  }
}
