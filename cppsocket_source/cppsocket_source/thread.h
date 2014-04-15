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

#ifndef CPPSOCKET_THREAD_H
#define CPPSOCKET_THREAD_H

#ifdef HAVE_LIBPTHREAD

#include <map>
#include <pthread.h>
#include <cppsocket/semaphore.h>

namespace CPPSocket
{
  class Thread
  {
  public:
    Thread();
    virtual ~Thread();

    void cancel();
    void kill();

    virtual void start();
    virtual void stop();
    virtual void run() = 0;

    void join();
    static void joinAll();

    void detach();
    
    bool isAlive() const;

    pthread_t getID() const;

    static Thread* currentThread();

    static int activeCount();

    enum State
    {
        STOPPED,    /// Thread is not running
        RUNNING,    /// Thread executes run() function
        STOPPING    /// Thread will stop now!
    };

    State getState() { return state; }

  protected:
    State state;

  private:
    typedef std::map<pthread_t, Thread*> ThreadMap;
    typedef ThreadMap::iterator ThreadMapIterator;
    typedef ThreadMap::value_type ThreadMapType;

    static ThreadMap threads;
    static Semaphore threadsLock;

    pthread_t handle;

    static void add(Thread* thread);
    static void remove(Thread* thread);

    static void* init(void* arg);
  };
}
#endif

#endif
