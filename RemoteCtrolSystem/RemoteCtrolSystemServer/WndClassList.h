/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   WndClassList.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   
**Create date:  2013/05/03   9:20
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
#ifndef __WNDCLASSLIST_H__
#define __WNDCLASSLIST_H__

#include "TabConnectionDlg.h"
#include "SystemMonitor.h"

class WndClassList
{
public:
	WndClassList(void);
	~WndClassList(void);

	static TabConnectionDlg* m_connectDlg;
	static SystemMonitor* m_watcher;

};
#endif//__WNDCLASSLIST_H__