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

#ifndef CPPSOCKET_ADDRESS_H
#define CPPSOCKET_ADDRESS_H

#include <string>
#include <vector>
#include <netinet/in.h>

#include <cppsocket/exception.h>

namespace CPPSocket
{
  using std::string;

  /** This class simplifies usage of socket addresses.
    * Can also be used for simple lookups.
    *
    * An Address can also be used like a classic sockaddr_in.
    * (Constructor, Assignment and Cast)
    *
    * @author Ralf-Christian Jürgensen
    */
  class Address
  {
  public:
    /// Errorcodes (Without LibC-errorcodes)
    enum ErrorCode
    {
      NO_IP_CODE     = 0x0101, ///< No valid IP address
      OFF_RANGE_CODE = 0x0102  ///< Index out of valid range
    };

    /// Map CPPSocket Port type to system-dependant port type
    typedef in_port_t Port;

    /// Can be used when no IP-address should be specified
    static const string ANY_IP;

    /** Construct address from ip-address or name.
      * If @e lookup == @e true and @e ip is like "xxx.xxx.xxx.xxx",
      * a dns-lookup is made.
      *
      * A lookup is made whenever a name is specified.
      *
      * @param ip IP-Address or Name
      * @param port Portnumber (in hostbyteorder)
      * @param lookup Make a dns-lookup if true
      *
      * @exception Exception An exception is thrown when the lookup fails.
      */
    explicit Address(const string& ip = ANY_IP, Port port = 0, bool lookup = false) throw (Exception);

    /** Construct an address from a classic sockaddr_in.
      * @b No lookup is made.
      *
      * @param address Address that should be copied.
      */
    Address(const sockaddr_in& address) throw();

    /** Cast the Address into sockaddr_in.
      * The first found IP is used to create the sockaddr_in.
      *
      * @return Socket-Address in classic format.
      *
      * @exception Exception An exception is thrown when there are no valid IPs.
      */
    operator sockaddr_in() const throw (Exception);

    /** Assignment of sockaddr_in
      *
      * @param address Address that should be copied.
      */
    void operator=(const sockaddr_in& address) throw();

    /** Make a DNS-Lookup.
      * You must have set a valid IP-Address before calling.
      * The first valid IP-address is used for lookup.
      *
      * @exception Exception An exception is thrown when the lookup fails.
      */
    void lookup() throw (Exception);

    /** Returns the full name of the address.
      */
    const string& getName() const throw();

    /** Returns the number of found name-aliases.
      */
    int getNumAliases() const throw();

    /** Returns the alias name at index (alias[index]).
      *
      * @param index Index of the requested alias name.
      *
      * @exception Exception An exception is thrown when the index if out of valid range (0 - number of aliases)
      */
    const string& getAliasName(size_t index) const throw (Exception);

    /** Returns the number of ip-addresses.
      */
    int getNumIPs() const throw();

    /** Returns the ip-address at index as text. "xxx.xxx.xxx.xxx"
      *
      * @param index Index of the requested ip-address.
      *
      * @exception Exception An exception is thrown when the index if out of valid range (0 - number of ip-addresses)
      */
    string getIPString(size_t index = 0) const throw (Exception);

    /** Returns the port number in hostbyteorder.
      */
    Port getPort() const throw();

  private:
    typedef std::vector<string> StringVector;
    typedef std::vector<in_addr> IPVector;

    /// Name of the Machine
    string name;

    /// An Array of alias names
    StringVector aliases;

    /// An Array of ip-addresses in netbyteorder
    IPVector ipAddresses;

    /// The portnumber in netbyteorder
    Port port;

    /** Make a gethostbyname() lookup.
      *
      * @param ip IP or name.
      *
      * @exception Exception An exception is thrown when the lookup fails.
      */
    void lookup(const string& ip) throw (Exception);
  };
}

#endif
