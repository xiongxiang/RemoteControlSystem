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
#ifndef __MUTEX_H__
#define __MUTEX_H__

// Synchronized (thread-safe) object that can be locked and unlocked
class Lockable
{
public:
    virtual ~Lockable(void){};

    /**
       @brief:Lock object
       @Return:void
    */
    virtual void Lock()   = 0;
    /**
       @brief:Unlock object
       @Return:void
    */
    virtual void Unlock() = 0;
};


#endif//__MUTEX_H__