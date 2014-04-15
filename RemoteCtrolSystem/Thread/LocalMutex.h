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
#ifndef __LOCALMUTEX_H__
#define __LOCALMUTEX_H__

#include "lockable.h"
#include <Windows.h>

class LocalMutex : public Lockable
{
public:
    /**
       @brief:Creates new mutex
       @Return:
    */
    LocalMutex();

    /**
       @brief:Deletes local mutex
       @Parameter:void
       @Return:
    */
    virtual ~LocalMutex(void);

    /**
       @brief:Inherited from lockable
       @Return:void
    */
    virtual void Lock();
    /**
       @brief:Inherited from lockable
       @Return:void
    */
    virtual void Unlock();

private:
    CRITICAL_SECTION m_csCriticalSection; // Windows critical section
};


#endif//__LOCALMUTEX_H__