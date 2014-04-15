/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:
**Latest modified Data:
**Latest Version:
**Description:
**
**-------------------------------------------------------------------------
**Create by:    xiongxiang
**Create date:
**Version:
**Description:
**
**
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**
**************************************************************************/
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>
#include <string>

using std::exception;
using std::string;


/**
 *  The error often occurs in the socket, so it's necessary to 
 *  deal the error.
 */
class TCPException : public exception 
{
public:
	explicit TCPException (const string & strMsg = "") 
		: m_strMsg(strMsg) {
	}
	TCPException(const string& _method,const string& strMsg,int code = 0)
		:m_strMethod(_method),m_strMsg(strMsg),m_iCode(code)
	{

	}
	virtual ~TCPException() throw () {
	}
	const string& getMethod() const throw() {return m_strMethod;}
	const string& GetMessage() const throw(){return m_strMsg;}
	int getCode() const throw() {return m_iCode;}

	virtual const char * what() const throw () {
		return m_strMsg.c_str();
	}

private:
	string m_strMsg;    // the stored message string
	string m_strMethod;
	int m_iCode;
};

#endif//__EXCEPTION_H__