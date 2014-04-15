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
#ifndef __GLOBALMUTEX_H__
#define __GLOBALMUTEX_H__

#include "../SocketIPv4/TCPStringBuffer.h"
#include "../SocketIPv4/TCPException.h"
#include "lockable.h"
#include <Windows.h>
#include <AclAPI.h>

#pragma warning(disable:4290)

class GlobalMutex :  public Lockable
{
public:
    /**
       @brief:Create new global mutex
       @Parameter:const TCHAR * name name of the mutex
    */
    GlobalMutex(const TCHAR *name = 0) throw(TCPException);

    /**
       @brief:Delete the  global mutex
       @Parameter:void
       @Return:
    */
    virtual ~GlobalMutex(void);

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
    void SetAccessToAll(HANDLE objHandle);

    HANDLE m_hMtex;     // mutex
};


#endif//__GLOBALMUTEX_H__