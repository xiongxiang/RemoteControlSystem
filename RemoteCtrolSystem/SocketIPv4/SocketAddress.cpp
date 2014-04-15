#include "SocketAddress.h"

//#pragma comment(lib,"wsock32.lib")
const string TCPSocketAddress::ANY_IP = "0.0.0.0";

TCPSocketAddress::TCPSocketAddress(const string & ip, Port _port, bool doLookup) throw (TCPException)
{
	in_addr address;

	if(doLookup)
	{
		Lookup(ip);
	}
	else
	{
		// Try to convert ip-string to binary ip.
		address.S_un.S_addr = inet_addr(ip.c_str());   //这里转换后的是网络字节顺序而已
		                           
		if(address.S_un.S_addr == -1)
		{
			// IP is name or not correct... let's see if lookup() can find something :)
			Lookup(ip);
		}
		else
		{
			// IP could be converted to binary ip
			m_sreIpAddresses.push_back(address);
		}
	}
	//主机字节顺序转成网络字节顺序
	m_usPort = htons(_port);
}


TCPSocketAddress::TCPSocketAddress(const sockaddr_in & address) throw()
{
	m_sreIpAddresses.push_back(address.sin_addr);
	//sin_port里的端口已经是网络字节顺序的了
	m_usPort = address.sin_port;
}

TCPSocketAddress::operator sockaddr_in() const throw (TCPException)
{
	if(m_sreIpAddresses.empty())
	{
		throw TCPException("Address::operator()", " no ip address");
	}

	sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_port = m_usPort;
	address.sin_addr = m_sreIpAddresses.front();

	return address;
}

void TCPSocketAddress::operator=(const sockaddr_in & address) throw()
{
	m_strName = "";
	m_strAliases.clear();

	m_sreIpAddresses.clear();
	m_sreIpAddresses.push_back(address.sin_addr);
	m_usPort = address.sin_port;
}

void TCPSocketAddress::Lookup(const string & ip) throw (TCPException)
{
	hostent * hostinfo = NULL;
	hostinfo = gethostbyname(ip.c_str());

	if(hostinfo == NULL)
	{
		throw TCPException("Address::lookup","gethostbyname return NULL");
	}

	m_strName = hostinfo->h_name;

	m_strAliases.clear();
	// save all found aliases in list
	if(hostinfo->h_aliases[0] != NULL)
	{
		for(char ** alias = hostinfo->h_aliases; *alias != NULL; alias++)
		{
			m_strAliases.push_back(*alias);
		}
	}
	m_sreIpAddresses.clear();
	// save all found IPs in list
	for(in_addr ** addr = reinterpret_cast<in_addr**>(hostinfo->h_addr_list); *addr != NULL; addr++)
	{
		m_sreIpAddresses.push_back(**addr);
	}
}

void TCPSocketAddress::Lookup() throw (TCPException)
{
	hostent * hostinfo = NULL;

	if(m_sreIpAddresses.empty())
	{
		throw TCPException("Address::lookup", "ip address is null");
	}

	// just using first IP in list
	hostinfo = gethostbyaddr(reinterpret_cast<char*>(&m_sreIpAddresses.front()), sizeof(in_addr), AF_INET);

	if(hostinfo == NULL)
	{
		throw TCPException("Address::lookup","gethostbyaddr return NULL");
	}

	m_strName = hostinfo->h_name;

	m_strAliases.clear();

	if(hostinfo->h_aliases[0] != NULL)
	{
		for(char ** alias = hostinfo->h_aliases; *alias != NULL; alias++)
		{
			m_strAliases.push_back(*alias);
		}
	}

	m_sreIpAddresses.clear();

	for(in_addr ** addr = reinterpret_cast<in_addr**>(hostinfo->h_addr_list); *addr != NULL; addr++)
	{
		m_sreIpAddresses.push_back(**addr);
	}
}

const string & TCPSocketAddress::GetName() const throw()
{
	return m_strName;
}

int TCPSocketAddress::GetNumAliases() const throw()
{
	return m_strAliases.size();
}

const string & TCPSocketAddress::GetAliasName(size_t index) const throw (TCPException)
{
	if(index >= m_strAliases.size())
	{
		throw TCPException("Address::getAliasName", "the index is too big");
	}

	return m_strAliases[index];
}

int TCPSocketAddress::GetNumIPs() const throw()
{
	return m_sreIpAddresses.size();
}

string TCPSocketAddress::GetIPString(size_t index) const throw (TCPException)
{
	if(index >= m_sreIpAddresses.size())
	{
		throw TCPException("Address::getIPString", "the index is out of range", OFF_RANGE_CODE);
	}

	string ip = inet_ntoa(m_sreIpAddresses[index]);

	return ip;
}

//返回主机顺序的端口号
TCPSocketAddress::Port TCPSocketAddress::GetPort() const throw()
{
	return ntohs(m_usPort);
}