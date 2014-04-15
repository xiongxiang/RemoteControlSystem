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

#ifndef CPPSOCKET_OPTION_H
#define CPPSOCKET_OPTION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

namespace CPPSocket
{
  /** Interface for all socket options.
    *
    * @author Ralf-Christian Jürgensen
    */
  class Option
  {
    friend class Socket;

  public:
    /// prevent GCC warnings
    virtual ~Option() throw() {}

    /// return option level
    virtual int level() const throw() = 0;
    /// return option id
    virtual int id() const throw()    = 0;

  protected:
    virtual void* pointer() throw()             = 0; ///< write access to the option
    virtual const void* pointer() const throw() = 0; ///< read access to the option
    virtual socklen_t size() const throw()      = 0; ///< option data size in bytes
  };

  /** Template class for easy creation of options.
    *
    * The option can be used like the embedded type.
    * Doesn't work for complex types or pointers.
    *
    * @author Ralf-Christian Jürgensen
    */
  template<int LEVEL, int ID, class TYPE>
  class OptionTemplate : public Option
  {
  public:
    OptionTemplate() throw() {}
    OptionTemplate(const TYPE& val) throw()
      : value(val) {}
    const TYPE& operator=(const TYPE& val) throw() { return value = val; }
    operator TYPE&() throw() { return value; }
    operator const TYPE&() const throw() { return value; }

    virtual int level() const throw()  { return LEVEL; }
    virtual int id() const throw()     { return ID; }

  protected:
    virtual void* pointer() throw()             { return reinterpret_cast<void*>(&value); }
    virtual const void* pointer() const throw() { return reinterpret_cast<const void*>(&value); }
    virtual socklen_t size() const throw()      { return sizeof(TYPE); }

  private:
    TYPE value;
  };

  /// Socketspecific options
  namespace SocketOption
  {
#ifdef SO_KEEPALIVE
    typedef OptionTemplate<SOL_SOCKET, SO_KEEPALIVE, int>    KeepAlive ;
#endif
#ifdef SO_OOBINLINE
    typedef OptionTemplate<SOL_SOCKET, SO_OOBINLINE, int>    OOBInline ;
#endif
#ifdef SO_RCVLOWAT
    typedef OptionTemplate<SOL_SOCKET, SO_RCVLOWAT,  int>    RcvLOWAT  ;
#endif
#ifdef SO_SNDLOWAT
    typedef OptionTemplate<SOL_SOCKET, SO_SNDLOWAT,  int>    SndLOWAT  ;
#endif
#ifdef SO_RCVTIMEO
    typedef OptionTemplate<SOL_SOCKET, SO_RCVTIMEO,  int>    RcvTimeO  ;
#endif
#ifdef SO_SNDTIMEO
    typedef OptionTemplate<SOL_SOCKET, SO_SNDTIMEO,  int>    SndTimeO  ;
#endif
#ifdef SO_BSDCOMPAT
    typedef OptionTemplate<SOL_SOCKET, SO_BSDCOMPAT, int>    BSDCompat ;
#endif
#ifdef SO_PASSCRED
    typedef OptionTemplate<SOL_SOCKET, SO_PASSCRED,  int>    PassCred  ;
#endif
#ifdef SO_DEBUG
    typedef OptionTemplate<SOL_SOCKET, SO_DEBUG,     int>    Debug     ;
#endif
#ifdef SO_REUSEADDR
    typedef OptionTemplate<SOL_SOCKET, SO_REUSEADDR, int>    ReuseAddr ;
#endif
#ifdef SO_TYPE
    typedef OptionTemplate<SOL_SOCKET, SO_TYPE,      int>    Type      ;
#endif
#ifdef SO_DONTROUTE
    typedef OptionTemplate<SOL_SOCKET, SO_DONTROUTE, int>    DontRoute ;
#endif
#ifdef SO_BROADCAST
    typedef OptionTemplate<SOL_SOCKET, SO_BROADCAST, int>    Broadcast ;
#endif
#ifdef SO_SNDBUF
    typedef OptionTemplate<SOL_SOCKET, SO_SNDBUF,    int>    SNDBuf    ;
#endif
#ifdef SO_RCVBUF
    typedef OptionTemplate<SOL_SOCKET, SO_RCVBUF,    int>    RCVBuf    ;
#endif
#ifdef SO_PRIORITY
    typedef OptionTemplate<SOL_SOCKET, SO_PRIORITY,  int>    Priority  ;
#endif
#ifdef SO_ERROR
    typedef OptionTemplate<SOL_SOCKET, SO_ERROR,     int>    Error     ;
#endif
#ifdef SO_LINGER
    typedef OptionTemplate<SOL_SOCKET, SO_LINGER,    linger> Linger    ;
#endif

#ifdef SO_BINDTODEVICE
    // This option uses a c-string as type, so template can't be used.
    class BindToDevice : public Option
    {
    public:
      BindToDevice(const char* device) throw()
      {
        devicename = new char[strlen(device)+1];
        strcpy(devicename, device);
      }

      virtual ~BindToDevice() throw()
      {
        delete[] devicename;
      }

      virtual int level() const throw() { return SOL_SOCKET; }
      virtual int id() const throw()    { return SO_BINDTODEVICE; }

    protected:
      virtual char* pointer() throw()             { return devicename; }
      virtual const char* pointer() const throw() { return devicename; }
      virtual socklen_t size() const throw()      { return strlen(devicename)+1; }

    private:
      char* devicename;
    };
#endif
  }

  /// IP-specific options
  namespace IPOption
  {
#ifdef IP_PKTINFO
     typedef OptionTemplate<SOL_IP, IP_PKTINFO,         in_pktinfo> PaketInfo     ;
#endif
#ifdef IP_OPTIONS
     typedef OptionTemplate<SOL_IP, IP_OPTIONS,         ip_opts>    Options       ;
#endif
#ifdef IP_RECVOPTS
     typedef OptionTemplate<SOL_IP, IP_RECVOPTS,        int>        RecvOpts      ;
#endif
#ifdef IP_RETOPTS
     typedef OptionTemplate<SOL_IP, IP_RETOPTS,         int>        RetOpts       ;
#endif
#ifdef IP_RECVTOS
     typedef OptionTemplate<SOL_IP, IP_RECVTOS,         int>        RecvTOS       ;
#endif
#ifdef IP_RECVTTL
     typedef OptionTemplate<SOL_IP, IP_RECVTTL,         int>        RecvTTL       ;
#endif
#ifdef IP_TOS
     typedef OptionTemplate<SOL_IP, IP_TOS,             int>        TOS           ;
#endif
#ifdef IP_TTL
     typedef OptionTemplate<SOL_IP, IP_TTL,             int>        TTL           ;
#endif
#ifdef IP_ROUTER_ALERT
     typedef OptionTemplate<SOL_IP, IP_ROUTER_ALERT,    int>        RouterAlert   ;
#endif
#ifdef IP_MTU_DISCOVER
     typedef OptionTemplate<SOL_IP, IP_MTU_DISCOVER,    int>        MTUDiscover   ;
#endif
#ifdef IP_MULTICAST_IF
     typedef OptionTemplate<SOL_IP, IP_MULTICAST_IF,    in_addr>    MulticastIF   ;
#endif
#ifdef IP_MULTICAST_TTL
     typedef OptionTemplate<SOL_IP, IP_MULTICAST_TTL,   int>        MulticastTTL  ;
#endif
#ifdef IP_MULTICAST_LOOP
     typedef OptionTemplate<SOL_IP, IP_MULTICAST_LOOP,  int>        MulticastLoop ;
#endif
#ifdef IP_ADD_MEMBERSHIP
     typedef OptionTemplate<SOL_IP, IP_ADD_MEMBERSHIP,  ip_mreq>    AddMembership ;
#endif
#ifdef IP_DROP_MEMBERSHIP
     typedef OptionTemplate<SOL_IP, IP_DROP_MEMBERSHIP, ip_mreq>    DropMembership;
#endif
//    typedef OptionPointerTemplate< SOL_IP, IP_RECVERR, void* > RecvErr;
  }

  /// TCP-specific options
  namespace TCPOption
  {
#ifdef TCP_NODELAY
    typedef OptionTemplate<SOL_TCP, TCP_NODELAY, int> NoDelay;
#endif
#ifdef TCP_MAXSEG
    typedef OptionTemplate<SOL_TCP, TCP_MAXSEG,  int> MaxSeg ;
#endif
#ifdef TCP_CORK
    typedef OptionTemplate<SOL_TCP, TCP_CORK,    int> Cork   ;
#endif
  }
}

#endif
