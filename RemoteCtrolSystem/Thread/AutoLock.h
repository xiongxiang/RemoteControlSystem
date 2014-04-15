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
#ifndef __AUTOLOCK_H__
#define __AUTOLOCK_H__

#include "Lockable.h"

class AutoLock
{
public:
    AutoLock(Lockable *locker);
    ~AutoLock(void);

private:
    Lockable *m_locker;
};
#endif//__AUTOLOCK_H__