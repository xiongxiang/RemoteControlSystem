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

#include <cppsocket/socket.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace CPPSocket
{
  /// Error returncodes of the C API functions.
  namespace ErrorReturnValues
  {
    const int SOCKET_ERROR      = -1;
    const int BIND_ERROR        = -1;
    const int CONNECT_ERROR     = -1;
    const int SEND_ERROR        = -1;
    const int RECV_ERROR        = -1;
    const int LISTEN_ERROR      = -1;
    const int ACCEPT_ERROR      = -1;
    const int GETSOCKNAME_ERROR = -1;
    const int GETPEERNAME_ERROR = -1;
    const int GETSOCKOPT_ERROR  = -1;
    const int SETSOCKOPT_ERROR  = -1;
    const int SHUTDOWN_ERROR    = -1;
  }

  /// Errormessages of the Socket-class (w/o LibC-Errors)
  namespace ErrorMessages
  {
    const string NOT_OPENED  = "Socket not opened yet";
    const string OPENED      = "Socket already opened";
  }

  /// Methodnames that can throw exceptions.
  namespace MethodNames
  {
    const string OPEN        = "Socket::open()";
    const string CLOSE       = "Socket::close()";
    const string BIND        = "Socket::bind()";
    const string CONNECT     = "Socket::connect()";
    const string SEND        = "Socket::send()";
    const string SENDTO      = "Socket::sendto()";
    const string RECV        = "Socket::recv()";
    const string RECVFROM    = "Socket::recvfrom()";
    const string LISTEN      = "Socket::listen()";
    const string ACCEPT      = "Socket::accept()";
    const string GETSOCKNAME = "Socket::getsockname()";
    const string GETPEERNAME = "Socket::getpeername()";
    const string GETSOCKOPT  = "Socket::getsockopt()";
    const string SETSOCKOPT  = "Socket::setsockopt()";
    const string SHUTDOWN    = "Socket::shutdown()";
    const string WAIT        = "Socket::wait()";
  }

  using namespace ErrorReturnValues;
  using namespace ErrorMessages;
  using namespace MethodNames;

  Socket::Socket() throw()
    : descriptor(-1)
  {
  }

  Socket::Socket(int sfd) throw()
    : descriptor(sfd)
  {
  }

  Socket::Socket(Protocol protocol) throw (Exception)
  {
    open(protocol);
  }

  Socket::~Socket() throw()
  {
    if(isOpened())
    {
      ::close(descriptor);
    }
  }

  void Socket::open(Protocol protocol) throw (Exception)
  {
    if(isOpened())
    {
      throw Exception(OPEN, OPENED, OPENED_CODE);
    }

    descriptor = socket(PF_INET, protocol, 0);

    if(descriptor == SOCKET_ERROR)
    {
      throw LibCException(OPEN);
    }
  }

  void Socket::close() throw (Exception)
  {
    if(!isOpened())
    {
      throw Exception(CLOSE, NOT_OPENED, NOT_OPENED_CODE);
    }

    ::close(descriptor);

    descriptor = -1;
  }

  void Socket::bind(const sockaddr_in& addr) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(BIND, NOT_OPENED, NOT_OPENED_CODE);
    }

    const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);

    error = ::bind(descriptor, socketAddress, sizeof(addr));

    if(error == BIND_ERROR)
    {
      throw LibCException(BIND);
    }
  }

  void Socket::bind(const Address& addr) throw (Exception)
  {
    bind(static_cast<const sockaddr_in>(addr));
  }

  void Socket::connect(const sockaddr_in& addr) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(CONNECT, NOT_OPENED, NOT_OPENED_CODE);
    }

    const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);

    error = ::connect(descriptor, socketAddress, sizeof(addr));

    if(error == CONNECT_ERROR)
    {
      throw LibCException(CONNECT);
    }
  }

  void Socket::connect(const Address& addr) throw (Exception)
  {
    connect(static_cast<const sockaddr_in>(addr));
  }

  int Socket::send(const char* data, size_t size, int flags) throw (Exception)
  {
    int bytes;

    if(!isOpened())
    {
      throw Exception(SEND, NOT_OPENED, NOT_OPENED_CODE);
    }

    bytes = ::send(descriptor, data, size, flags);

    if(bytes == SEND_ERROR)
    {
      throw LibCException(SEND);
    }

    return bytes;
  }

  int Socket::sendto(const sockaddr_in& addr, const char* data, size_t size, int flags) throw (Exception)
  {
    int bytes;

    if(!isOpened())
    {
      throw Exception(SENDTO, NOT_OPENED, NOT_OPENED_CODE);
    }

    const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);

    bytes = ::sendto(descriptor, data, size, flags, socketAddress, sizeof(addr));

    if(bytes == SEND_ERROR)
    {
      throw LibCException(SENDTO);
    }

    return bytes;
  }

  int Socket::recv(char* data, size_t size, int flags) throw (Exception)
  {
    int bytes;

    if(!isOpened())
    {
      throw Exception(RECV, NOT_OPENED, NOT_OPENED_CODE);
    }

    bytes = ::recv(descriptor, data, size, flags);

    if(bytes == RECV_ERROR)
    {
      throw LibCException(RECV);
    }

    return bytes;
  }

  int Socket::recvfrom(sockaddr_in& addr, char* data, size_t size, int flags) throw (Exception)
  {
    int bytes;

    if(!isOpened())
    {
      throw Exception(RECVFROM, NOT_OPENED, NOT_OPENED_CODE);
    }

    socklen_t addrLen = sizeof(addr);

    sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&addr);

    bytes = ::recvfrom(descriptor, data, size, flags, socketAddress, &addrLen);

    if(bytes == RECV_ERROR)
    {
      throw LibCException(RECVFROM);
    }

    return bytes;
  }

  int Socket::send(const Buffer& data, int flags) throw (Exception)
  {
    return send(data.pointer(), data.size(), flags);
  }

  int Socket::sendto(const Address& addr, const Buffer& data, int flags) throw (Exception)
  {
    return sendto(addr, data.pointer(), data.size(), flags);
  }

  int Socket::recv(Buffer& data, int flags) throw (Exception)
  {
    int bytes;

    data.prepare();

    bytes = recv(data.pointer(), data.size(), flags);

    data.update(bytes);

    return bytes;
  }

  int Socket::recvfrom(Address& addr, Buffer& data, int flags) throw (Exception)
  {
    int bytes;

    data.prepare();

    sockaddr_in address = addr;

    bytes = recvfrom(address, data.pointer(), data.size(), flags);

    addr = address;

    data.update(bytes);

    return bytes;
  }

  void Socket::listen(int queuelen) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(LISTEN, NOT_OPENED, NOT_OPENED_CODE);
    }

    error = ::listen(descriptor, queuelen);

    if(error == LISTEN_ERROR)
    {
      throw LibCException(LISTEN);
    }
  }

  Socket::Descriptor Socket::accept(sockaddr_in& addr) throw (Exception)
  {
    Descriptor sfd;

    if(!isOpened())
    {
      throw Exception(ACCEPT, NOT_OPENED, NOT_OPENED_CODE);
    }

    socklen_t addrLen = sizeof(addr);

    sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&addr);

    sfd = ::accept(descriptor, socketAddress, &addrLen);

    if(sfd == ACCEPT_ERROR)
    {
      throw LibCException(ACCEPT);
    }

    return sfd;
  }

  Socket::Descriptor Socket::accept(Address& addr) throw (Exception)
  {
    Descriptor tempSocket;

    sockaddr_in address = addr;

    tempSocket = accept(address);

    addr = address;

    return tempSocket;
  }

  Address Socket::getsockname() throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(GETSOCKNAME, NOT_OPENED, NOT_OPENED_CODE);
    }

    sockaddr_in address;
    socklen_t addrLen = sizeof(address);

    sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&address);

    error = ::getsockname(descriptor, socketAddress, &addrLen);

    if(error == GETSOCKNAME_ERROR)
    {
      throw LibCException(GETSOCKNAME);
    }

    return Address(address);
  }

  Address Socket::getpeername() throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(GETPEERNAME, NOT_OPENED, NOT_OPENED_CODE);
    }

    sockaddr_in address;
    socklen_t addrLen = sizeof(address);

    sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&address);

    error = ::getpeername(descriptor, socketAddress, &addrLen);

    if(error == GETPEERNAME_ERROR)
    {
      throw LibCException(GETPEERNAME);
    }

    return Address(address);
  }

  int Socket::getsockopt(Option& option) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(GETSOCKOPT, NOT_OPENED, NOT_OPENED_CODE);
    }

    socklen_t optSize = option.size();

    error = ::getsockopt(descriptor, option.level(), option.id(), option.pointer(), &optSize);

    if(error == GETSOCKOPT_ERROR)
    {
      throw LibCException(GETSOCKOPT);
    }

    return optSize;
  }

  void Socket::setsockopt(const Option& option) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(SETSOCKOPT, NOT_OPENED, NOT_OPENED_CODE);
    }

    error = ::setsockopt(descriptor, option.level(), option.id(), option.pointer(), option.size());

    if(error == SETSOCKOPT_ERROR)
    {
      throw LibCException(SETSOCKOPT);
    }
  }

  void Socket::shutdown(Shutdown how) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(SHUTDOWN, NOT_OPENED, NOT_OPENED_CODE);
    }

    error = ::shutdown(descriptor, how);

    if(error == SHUTDOWN_ERROR)
    {
      throw LibCException(SHUTDOWN);
    }
  }

  bool Socket::wait(bool& read, bool& write, bool& exception, int seconds, int useconds) throw (Exception)
  {
    if(!isOpened())
    {
      throw Exception(WAIT, NOT_OPENED, NOT_OPENED_CODE);
    }

    struct timeval time;
    time.tv_sec  = seconds;
    time.tv_usec = useconds;

    fd_set* readfds = 0;
    fd_set* writefds = 0;
    fd_set* exceptfds = 0;

    if(read)
    {
      readfds = new fd_set;

      FD_ZERO(readfds);
      FD_SET(descriptor, readfds);
    }

    if(write)
    {
      writefds = new fd_set;

      FD_ZERO(writefds);
      FD_SET(descriptor, writefds);
    }

    if(exception)
    {
      exceptfds = new fd_set;

      FD_ZERO(exceptfds);
      FD_SET(descriptor, exceptfds);
    }

    int ret = select(descriptor+1, readfds, writefds, exceptfds, &time);

    if(read)
    {
      read = FD_ISSET(descriptor, readfds);
    }

    if(write)
    {
      write = FD_ISSET(descriptor, writefds);
    }

    if(exception)
    {
      exception = FD_ISSET(descriptor, exceptfds);
    }

    delete readfds;
    delete writefds;
    delete exceptfds;

    if(ret < 0)
    {
      throw LibCException(WAIT);
    }

    return (ret != 0);
  }
}
