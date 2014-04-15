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

#ifndef CPPSOCKET_SEMAPHORE_H
#define CPPSOCKET_SEMAPHORE_H

#ifdef HAVE_LIBPTHREAD

#include <pthread.h>
#include <cppsocket/exception.h>

namespace CPPSocket
{
  class Semaphore
  {
  public:
    /// init semaphore counter with 0.
    Semaphore() throw (Exception);
    ~Semaphore() throw();

    /// increment semapore counter. => unlock
    int operator++() throw (Exception);
    /// decrement semaphore counter. => lock and block process.
    int operator--() throw (Exception);

    /// decrement semaphore counter. => only locking no blocking.
    int operator-=(int dec) throw (Exception);

    /// current value of semaphore counter.
    operator int() throw (Exception);

 private:
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    void mutexLock() throw (Exception);
    void mutexUnlock() throw (Exception);
    void condWait() throw (Exception);
    void condSignal() throw (Exception);
  };
}

#endif

#endif
