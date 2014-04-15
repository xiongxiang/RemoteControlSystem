#include "AutoLock.h"

AutoLock::AutoLock(Lockable * locker):m_locker(locker)
{
    m_locker->Lock();
}

AutoLock::~AutoLock(void)
{
    m_locker->Unlock();
}
