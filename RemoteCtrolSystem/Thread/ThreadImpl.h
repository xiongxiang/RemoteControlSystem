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
#ifndef __THREADIMPL_H__
#define __THREADIMPL_H__

#define WIN32_LEAN_AND_MEAN
#include <process.h>
#include <windows.h>

class Thread;

class ThreadImpl
{
public:
	static const int WAIT_INFINITE = -1;
	static const int INVALID_THREAD_ID = 0;
	static const size_t DEFAULT_STACK_SIZE = 0;

public:
	struct ThreadStruct{
		HANDLE hThread;
		UINT   dwThreadId;

		ThreadStruct():hThread(NULL),dwThreadId(INVALID_THREAD_ID){}


		void Cleanup()
		{
			if (hThread!=NULL)
			{
				CloseHandle(hThread);
				hThread = NULL;
			}
		}

		~ThreadStruct(){
			Cleanup();
		}
	};

public:
	typedef int (* THREAD_FUNCTION)(Thread *pParam);
    typedef unsigned int (WINAPI* THREADPROC)(void *pParam);

public:
	/**
	   @brief:Create a new thread
	   @Parameter:ThreadStruct & ts
	   @Parameter:THREAD_FUNCTION thread_func
	   @Parameter:size_t cbStackSize
	   @Parameter:Thread * pThread
	   @Return:bool
	*/
	static bool CreateThread(ThreadStruct &ts,
		THREAD_FUNCTION thread_func,size_t cbStackSize,Thread *pThread);
	/**
	   @brief:Destroy the thread
	   @Parameter:ThreadStruct & ts
	   @Return:void
	*/
	static void DestroyThread(ThreadStruct &ts);
	/**
	   @brief:Wait for the thread
	   @Parameter:const ThreadStruct & ts
	   @Parameter:int iTimeOut
	   @Return:bool
	*/
	static bool WaitForThreadEnd(const ThreadStruct &ts,int iTimeOut);
	/**
	   @brief:Terminate the thread
	   @Parameter:const ThreadStruct & ts
	   @Return:void
	*/
	static void TerminateThread(const ThreadStruct &ts);
	/**
	   @brief:Is the thread still running 
	   @Parameter:const ThreadStruct & ts
	   @Return:bool
	*/
	static bool IsAlive(const ThreadStruct &ts);
	/**
	   @brief:Get the thread ID
	   @Parameter:const ThreadStruct & ts
	   @Return:DWORD
	*/
	static DWORD GetThreadId(const ThreadStruct &ts);
	/**
	   @brief:Sleep some seconds
	   @Parameter:int iMs
	   @Return:void
	*/
	static void Sleep(int iMs);

private:
	ThreadImpl();
	ThreadImpl(const ThreadImpl &) throw();
	void operator=(const ThreadImpl &);
};

#endif//__THREADIMPL_H__