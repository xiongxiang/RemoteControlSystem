/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   DealConnection.h
**Latest modified Data:  2013/05/03   8:30
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   魏胤
**Create date:  2013/05/03   8:30
**Version:
**Description:  处理与客户端的交互的一个连接对象
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
#ifndef __DEALCONNECTION_H__
#define __DEALCONNECTION_H__

#include "../SocketIPv4/TCPThreadedServer.h"
#include "../SocketIPv4/SocketAddress.h"
#include "../Message/ImageMsg.h"
#include "../Graphic/ScreenShot.h"

#include <queue>

class DealConnection :public TCPService
{
public:
	DealConnection(TCPConnection* _connection) : TCPService(_connection){}
	~DealConnection(void);

protected:
	void Run(); //线程运行函数

};
#endif//__DEALCONNECTION_H__