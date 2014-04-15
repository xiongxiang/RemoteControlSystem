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

#include <cppsocket/address.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace CPPSocket
{
  /// Errormessages in Address. (without libc-messages)
  namespace ErrorMessages
  {
    static const string NO_IP        = "No IP-Address";
    static const string OFF_RANGE    = "Index out of Range";
  }

  /// Methods where an exception can be thrown
  namespace MethodNames
  {
    static const string ADDRESS      = "Address::Address()";
    static const string SOCKADDR_IN  = "Address::sockaddr_in()";
    static const string LOOKUP       = "Address::lookup()";
    static const string GETALIASNAME = "Address::getAliasName()";
    static const string GETIPSTRING  = "Address::getIPString()";
  }

  using namespace ErrorMessages;
  using namespace MethodNames;

  const string Address::ANY_IP = "0.0.0.0";

  Address::Address(const string & ip, Port _port, bool doLookup) throw (Exception)
  {
    in_addr address;

    if(doLookup)
    {
      lookup(ip);
    }
    else
    {
      // Try to convert ip-string to binary ip.
      if(inet_aton(ip.c_str(), &address) == 0)
      {
        // IP is name or not correct... let's see if lookup() can find something :)
        lookup(ip);
      }
      else
      {
        // IP could be converted to binary ip
        ipAddresses.push_back(address);
      }
    }

    port = htons(_port);
  }

  Address::Address(const sockaddr_in & address) throw()
  {
    ipAddresses.push_back(address.sin_addr);

    port = address.sin_port;
  }

  Address::operator sockaddr_in() const throw (Exception)
  {
    if(ipAddresses.empty())
    {
      throw Exception(SOCKADDR_IN, NO_IP, NO_IP_CODE);
    }

    sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = port;
    address.sin_addr = ipAddresses.front();

    return address;
  }

  void Address::operator=(const sockaddr_in & address) throw()
  {
    name = "";
    aliases.clear();

    ipAddresses.clear();
    ipAddresses.push_back(address.sin_addr);

    port = address.sin_port;
  }

  void Address::lookup(const string & ip) throw (Exception)
  {
    hostent * hostinfo = NULL;

    hostinfo = gethostbyname(ip.c_str());

    if(hostinfo == NULL)
    {
      throw HLibCException(LOOKUP);
    }

    name = hostinfo->h_name;

    aliases.clear();
    // save all found aliases in list
    if(hostinfo->h_aliases[0] != NULL)
    {
      for(char ** alias = hostinfo->h_aliases; *alias != NULL; alias++)
      {
        aliases.push_back(*alias);
      }
    }

    ipAddresses.clear();
    // save all found IPs in list
    for(in_addr ** addr = reinterpret_cast<in_addr**>(hostinfo->h_addr_list); *addr != NULL; addr++)
    {
      ipAddresses.push_back(**addr);
    }
  }

  void Address::lookup() throw (Exception)
  {
    hostent * hostinfo = NULL;

    if(ipAddresses.empty())
    {
      throw Exception(LOOKUP, NO_IP, NO_IP_CODE);
    }

    // just using first IP in list
    hostinfo = gethostbyaddr(reinterpret_cast<char*>(&ipAddresses.front()), sizeof(in_addr), AF_INET);

    if(hostinfo == NULL)
    {
        throw HLibCException(LOOKUP);
    }

    name = hostinfo->h_name;

    aliases.clear();

    if(hostinfo->h_aliases[0] != NULL)
    {
      for(char ** alias = hostinfo->h_aliases; *alias != NULL; alias++)
      {
        aliases.push_back(*alias);
      }
    }

    ipAddresses.clear();

    for(in_addr ** addr = reinterpret_cast<in_addr**>(hostinfo->h_addr_list); *addr != NULL; addr++)
    {
      ipAddresses.push_back(**addr);
    }
  }

  const string & Address::getName() const throw()
  {
    return name;
  }

  int Address::getNumAliases() const throw()
  {
    return aliases.size();
  }

  const string & Address::getAliasName(size_t index) const throw (Exception)
  {
    if(index >= aliases.size())
    {
      throw Exception(GETALIASNAME, OFF_RANGE, OFF_RANGE_CODE);
    }

    return aliases[index];
  }

  int Address::getNumIPs() const throw()
  {
    return ipAddresses.size();
  }

  string Address::getIPString(size_t index) const throw (Exception)
  {
    if(index >= ipAddresses.size())
    {
      throw Exception(GETIPSTRING, OFF_RANGE, OFF_RANGE_CODE);
    }

    string ip = inet_ntoa(ipAddresses[index]);

    return ip;
  }

  Address::Port Address::getPort() const throw()
  {
    return ntohs(port);
  }
}
