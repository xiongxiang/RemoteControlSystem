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

#include <cppsocket/semaphore.h>

//#ifdef HAVE_LIBPTHREAD

namespace CPPSocket
{
  Semaphore::Semaphore() throw (Exception)
  {
    int ret;
    ret = pthread_mutex_init(&mutex, 0);
    if(ret < 0)
      throw Exception("Semaphore::Semaphore()", "Can't init mutex", ret);

    ret = pthread_cond_init(&cond, 0);
    if(ret < 0)
      throw Exception("Semaphore::Semaphore()", "Can't init condition", ret);

    value = 0;
  }

  Semaphore::~Semaphore() throw()
  {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
  }

  int Semaphore::operator++() throw (Exception)
  {
    int valueAfterOp;

    mutexLock();
    ++value;
    valueAfterOp = value;
    mutexUnlock();

    condSignal();

    return valueAfterOp;
  }

  int Semaphore::operator--() throw (Exception)
  {
    int valueAfterOp;

    mutexLock();
    while(value < 0)
      condWait();

    --value;
    valueAfterOp = value;
    mutexUnlock();

    return valueAfterOp;
  }

  int Semaphore::operator-=(int dec) throw (Exception)
  {
    int valueAfterOp;

    mutexLock();
    value -= dec;
    valueAfterOp = value;
    mutexUnlock();

    return valueAfterOp;
  }

  Semaphore::operator int() throw (Exception)
  {
    int valueAfterOp;

    mutexLock();
    valueAfterOp = value;
    mutexUnlock();

    return valueAfterOp;
  }

  void Semaphore::mutexLock() throw (Exception)
  {
    int ret;
    //ret = pthread_mutex_lock(&mutex);
    ret = CreateMutex(&mutex, false, NULL);
    if(ret < 0)
      throw Exception("Semaphore::mutexLock()", "Can't lock mutex", ret);
  }

  void Semaphore::mutexUnlock() throw (Exception)
  {
    int ret;
    ret = pthread_mutex_unlock(&mutex);
    if(ret < 0)
      throw Exception("Semaphore::mutexUnlock()", "Can't unlock mutex", ret);
  }

  void Semaphore::condWait() throw (Exception)
  {
    int ret;
    ret = pthread_cond_wait(&cond, &mutex);
    if(ret < 0)
      throw Exception("Semaphore::condWait()", "", ret);
  }

  void Semaphore::condSignal() throw (Exception)
  {
    int ret;
    ret = pthread_cond_signal(&cond);
    if(ret < 0)
      throw Exception("Semaphore::condSignal()", "", ret);
  }
}

#endif
