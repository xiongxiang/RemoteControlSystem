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

#include <cppsocket/thread.h>

#ifdef HAVE_LIBPTHREAD

#include <signal.h>

#include <iostream>

namespace CPPSocket
{
  Semaphore Thread::threadsLock;

  Thread::ThreadMap Thread::threads;

  Thread::Thread()
    : state(STOPPED)
    , handle(0)
  {}

  Thread::~Thread()
  {
  }

  void Thread::start()
  {
    state = RUNNING;

    pthread_create(&handle, 0, Thread::init, this);
  }

  void Thread::stop()
  {
    join();
  }

  void Thread::cancel()
  {
    pthread_cancel(handle);

    state = STOPPED;
  }

  void Thread::join()
  {
    state = STOPPING;

    int* dummy;

    pthread_join(handle, (void**)&dummy);

    state = STOPPED;
  }

  void Thread::kill()
  {
    if(isAlive())
    {
      pthread_kill(handle, SIGKILL);
      remove(this);
    }
  }

  void Thread::detach()
  {
    pthread_detach(handle);
  }
  
  void Thread::joinAll()
  {
    ThreadMapIterator iter;

    while(threads.size() > 0)
    {
      iter = threads.begin();

      if(iter != threads.end())
      {
        iter->second->join();
      }
    }
  }

  bool Thread::isAlive() const
  {
    pthread_t id = getID();

    ThreadMapIterator iterator = threads.find(id);

    if(iterator != threads.end())
      return true;

    return false;
  }

  pthread_t Thread::getID() const
  {
    return handle;
  }

  int Thread::activeCount()
  {
    return threads.size();
  }

  void* Thread::init(void* arg)
  {
    Thread* thread = reinterpret_cast<Thread*>(arg);

    add(thread);

    thread->run();

    remove(thread);

    delete thread;

    return 0;
  }

  void Thread::add(Thread* thread)
  {
    pthread_t id = thread->getID();

    --threadsLock;

    threads.insert(ThreadMapType(id, thread));

    ++threadsLock;
  }

  void Thread::remove(Thread* thread)
  {
    pthread_t id = thread->getID();
    ThreadMapIterator iter = threads.find(id);

    if( iter != threads.end() )
    {
      --threadsLock;

      threads.erase(iter);

      ++threadsLock;
    }
  }
}

#endif
