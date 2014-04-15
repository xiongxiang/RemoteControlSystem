#ifndef CPPSOCKET_ADDRESS_H
#define CPPSOCKET_ADDRESS_H

#include "TCPException.h"
#include <string>
#include <vector>

#include <WinSock2.h>
#include <Windows.h>

#pragma warning(disable:4290)
using std::string;

class TCPSocketAddress
{
public:
	// Error codes (Without LibC-error codes)
	enum ErrorCode
	{
	  NO_IP_CODE          = 0x0101, //  No valid IP address
	  OFF_RANGE_CODE = 0x0102  //  Index out of valid range
	};

    // Map CPPSocket Port type to system-dependent port type
    typedef u_short Port;
    // Can be used when no IP-address should be specified
    static const string ANY_IP;

    /** 
	  * Construct address from ip-address or name.
      * If @e lookup == @e true and @e ip is like "xxx.xxx.xxx.xxx",
      * a DNS-lookup is made.
      *
      * A lookup is made whenever a name is specified.
      *
      * @param ip IP-Address or Name
      * @param port Port number (in host byte order)
      * @param lookup Make a DNS-lookup if true
      *
      * @exception Exception An exception is thrown when the lookup fails.
      */
    explicit TCPSocketAddress(const string& ip = ANY_IP, 
		Port port = 0, bool lookup = false) throw (TCPException);

	/**  
	  * Construct an address from a classic sockaddr_in.
      * @b No lookup is made.
      *
      * @param address Address that should be copied.
      */
    TCPSocketAddress(const sockaddr_in& address) throw();

	/**   
	  * Cast the Address into sockaddr_in.
      * The first found IP is used to create the sockaddr_in.
      *
      * @return Socket-Address in classic format.
      *
      * @exception Exception An exception is thrown when there are no valid IPs.
      */
    operator sockaddr_in() const throw (TCPException);

    /** 
	  * Assignment of sockaddr_in
      *
      * @param address Address that should be copied.
      */
    void operator=(const sockaddr_in& address) throw();

    /** 
	  * Make a DNS-Lookup.
      * You must have set a valid IP-Address before calling.
      * The first valid IP-address is used for lookup.
      *
      * @exception Exception An exception is thrown when the lookup fails.
      */
    void Lookup() throw (TCPException);

    /** 
	 *  Returns the full name of the address.
     */
    const string& GetName() const throw();

    /** 
	 *  Returns the number of found name-aliases(.±ðÃû£©
     */
    int GetNumAliases() const throw();

    /** 
	  * Returns the alias name at index (alias[index]).
      *
      * @param index Index of the requested alias name.
      *
      * @exception Exception An exception is thrown when 
	  *    the index if out of valid range (0 - number of aliases)
      */
    const string& GetAliasName(size_t index) const throw (TCPException);

    /** 
	 * Returns the number of ip-addresses.
     */
    int GetNumIPs() const throw();

    /** 
	  * Returns the ip-address at index as text. "xxx.xxx.xxx.xxx"
      *
      * @param index Index of the requested ip-address.
      *
      * @exception Exception An exception is thrown when the index 
	  *     if out of valid range (0 - number of ip-addresses)
      */
    string GetIPString(size_t index = 0) const throw (TCPException);

    /** Returns the port number in host byte order.
      */
    Port GetPort() const throw();

private:
    
    /** 
	  * Make a gethostbyname() lookup.
      *
      * @param ip IP or name.
      *
      * @exception Exception An exception is thrown when the lookup fails.
      */
    void Lookup(const string& ip) throw (TCPException);

private:
    typedef std::vector<string> StringVector;
    typedef std::vector<in_addr> IPVector;

    // Name of the Machine
    string m_strName;

    // An Array of alias names
    StringVector m_strAliases;

    // An Array of ip-addresses in net byte order
    IPVector m_sreIpAddresses;

    // The port number in net byte order
    Port m_usPort;

};

#endif