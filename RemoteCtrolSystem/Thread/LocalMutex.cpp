#include "LocalMutex.h"

LocalMutex::LocalMutex(void)
{
    InitializeCriticalSectionAndSpinCount(&m_csCriticalSection, 4000);
}

LocalMutex::~LocalMutex(void)
{
    DeleteCriticalSection(&m_csCriticalSection);
}

void LocalMutex::Lock()
{
    EnterCriticalSection(&m_csCriticalSection);
}

void LocalMutex::Unlock()
{
    LeaveCriticalSection(&m_csCriticalSection);
}
