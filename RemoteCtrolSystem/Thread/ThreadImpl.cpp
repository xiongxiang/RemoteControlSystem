#include "ThreadImpl.h"

bool ThreadImpl::CreateThread(
                              ThreadStruct &ts,
                              THREAD_FUNCTION thread_func,
                              size_t cbStackSize,
                              Thread *pThread)
{
    ts.hThread = (HANDLE)::_beginthreadex(NULL,
        (unsigned int)cbStackSize,
        (THREADPROC)thread_func,
        (void*)pThread,
        0,
        (unsigned int*)&ts.dwThreadId);

	//CloseHandle(ts.hThread);
    if (NULL == ts.hThread)
    {
        return false;
    }
    return true;
}

void ThreadImpl::DestroyThread(ThreadStruct &ts)
{
    ts.Cleanup();
}

bool ThreadImpl::WaitForThreadEnd(const ThreadStruct &ts,int iTimeOut)
{
    DWORD dwTO = (DWORD)iTimeOut;
    if (iTimeOut == WAIT_INFINITE)
    {
        dwTO = INFINITE;
    }
    DWORD dwRes = WaitForSingleObject(ts.hThread,dwTO);
    if (dwRes == WAIT_TIMEOUT)
    {
        return false;
    }else
    {
        return true;
    }
}

void ThreadImpl::TerminateThread(const ThreadStruct &ts)
{
    ::TerminateThread(ts.hThread,999999);
}

bool ThreadImpl::IsAlive(const ThreadStruct &ts)
{
    if (NULL == ts.hThread)
    {
        return false;
    }
    DWORD dwRes = WaitForSingleObject(ts.hThread,0);
    if (WAIT_TIMEOUT == dwRes)
    {
        return true;
    }
    else if (WAIT_OBJECT_0 == dwRes || WAIT_FAILED == dwRes)
    {
        return false;
    }
    else
    {
        return false;
    }
}

DWORD ThreadImpl::GetThreadId(const ThreadStruct &ts)
{
    return ts.dwThreadId;
}

void ThreadImpl::Sleep(int iMs)
{
    return ::Sleep(iMs);
}