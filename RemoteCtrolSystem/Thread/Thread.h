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
#ifndef __THREAD_H__
#define __THREAD_H__

#include "ThreadImpl.h"
#include "../SocketIPv4/TCPException.h"

#include <string>
using std::string;

#define CLASS_UNCOPYABLE(classname) \
	 private: \
	 classname(const classname&); \
	 classname& operator=(const classname&);

class ThreadException : public TCPException
{
public:
	ThreadException(const string &strMsg = ""):TCPException(strMsg){}
};

class ThreadCreateException : public TCPException
{
public:
	ThreadCreateException(const string &strMsg = ""):TCPException(strMsg){}
};

class ThreadImpl;

class Thread {
public:
	static const int     WAIT_INFINITE             = ThreadImpl::WAIT_INFINITE;
	static const int     INVALID_THREAD_ID    = ThreadImpl::INVALID_THREAD_ID;
	static const size_t DEFAULT_STACK_SIZE   = ThreadImpl::DEFAULT_STACK_SIZE;


public:
	explicit Thread(const string & strThreadName = "")
	{
		m_strThreadName = strThreadName;
	}
	virtual ~Thread(){
		if (IsAlive())
		{
			OnLeaking();
		}
	}
protected:
	virtual void Run() {};

	virtual void OnException(const TCPException * pAex)
    {
        throw pAex;
    }
	virtual void OnLeaking() throw () {}
	static int Thread_Function(Thread *pThread)
	{
		try
		{
			pThread->Run();
		}
		catch (const TCPException &ex)
		{
			pThread->OnException(&ex);
			return -1;
		}
		catch (...)
		{
			pThread->OnException(NULL);
			return -1;
		}
		return 0;
	}
public:
	static void Sleep(int iMilliseconds)
	{
		return ThreadImpl::Sleep(iMilliseconds);
	}
	virtual void Start(size_t cbStackSize = DEFAULT_STACK_SIZE){
		bool bRes = ThreadImpl::CreateThread(m_ts, 
			Thread_Function,
			cbStackSize,
			static_cast<Thread *>(this));
		if(!bRes) {
			throw ThreadCreateException("Calling CreateThread failed.");
		}
	}
	virtual bool WaitForEnd(int iTimeout = WAIT_INFINITE) {

		if(!ThreadImpl::IsAlive(m_ts)) {
			return true;
		}

		if(!ThreadImpl::WaitForThreadEnd(m_ts, iTimeout)) {
			return false;
		}

		ThreadImpl::DestroyThread(m_ts);

		return true;
	}
	DWORD GetThreadID() const{
		return ThreadImpl::GetThreadId(m_ts);
	}
	virtual void Terminate() {
		ThreadImpl::TerminateThread(m_ts);
		ThreadImpl::DestroyThread(m_ts);
	}
	virtual bool IsAlive() const {
		return ThreadImpl::IsAlive(m_ts);
	}

protected:
	ThreadImpl::ThreadStruct m_ts;
	string m_strThreadName;

private:
	CLASS_UNCOPYABLE(Thread)
};


#endif//__THREAD_H__