#include "GlobalMutex.h"

GlobalMutex::GlobalMutex(const TCHAR *name) throw(TCPException)
{
    m_hMtex = CreateMutex(NULL, false, name);
    if (0 == m_hMtex)
    {
        throw TCPException("GlobalMutex::GlobalMutex","Create Mutex Error");
    }
    if (GetLastError() != ERROR_ALREADY_EXISTS)
    {
        SetAccessToAll(m_hMtex);
    }
}

GlobalMutex::~GlobalMutex(void)
{
    CloseHandle(m_hMtex);
}

void GlobalMutex::Lock()
{
    WaitForSingleObject(m_hMtex, INFINITE);
}

void GlobalMutex::Unlock()
{
    ReleaseMutex(m_hMtex);
}
void GlobalMutex::SetAccessToAll(HANDLE objHandle) throw ()
{
    DWORD errorCode = SetSecurityInfo(objHandle, SE_KERNEL_OBJECT,
        DACL_SECURITY_INFORMATION,
        0,
        0,
        0,
        0);
    if (errorCode != ERROR_SUCCESS)
    {
        throw TCPException("GlobalMutex::SetAccessToAll","SetAccessToAll Error");
    }
}