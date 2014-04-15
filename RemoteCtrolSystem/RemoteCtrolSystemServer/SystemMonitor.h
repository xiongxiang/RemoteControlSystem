/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   SystemMonitor.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   魏胤
**Create date:  2013/05/03   9:10
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
#ifndef __SYSTEMMONITOR_H__
#define __SYSTEMMONITOR_H__

#include "FileSystemWatcher.h"
#include <vector>

class SystemMonitor
{
public:
	typedef void (*_AddApplicatinMonitor)(char *,char * , char *);
	typedef void (*_RemoveApplicationMonitor)();

	SystemMonitor();
	~SystemMonitor(void);

	/**
	 * @Brief SetName 设置当前所监控的用户
	 * @Parameter const char name[20] 用户名
	 * @Returns void
	 * @Remark  
	 **/
	void SetName(const char name[20]);  
	/**
	 * @Brief SetIp 设置当前所监控的用户所在的IP地址
	 * @Parameter const char * ip ip地址
	 * @Returns void
	 * @Remark  
	 **/
	void SetIp(const char *ip);
	/**
	 * @Brief SetFilePath 设置保存监控记录的文件路径
	 * @Parameter const char path[MAX_PATH]  文件所在的路径
	 * @Returns void
	 * @Remark  
	 **/
	void SetFilePath(const char path[MAX_PATH]);

	/**
	 * @Brief Start 启动监控
	 * @Returns void
	 * @Remark  
	 **/
	void Start();
	/**
	 * @Brief Stop 停止监控
	 * @Returns void
	 * @Remark  
	 **/
	void Stop();

	/**
	 * @Brief isMonitorActive 测试当前的监控状态
	 * @Returns BOOL
	 * @Remark  
	 **/
	BOOL isMonitorActive();

private:
	BOOL isActive; //保存当前监控状态
	std::vector<FileSystemWatcher*> m_vpFSW;  //保存对各个文件夹监控的文件监控器
	_AddApplicatinMonitor appStartMonitor;  //应用程序监控所在DLL的启动函数地址
	_RemoveApplicationMonitor appStopMonitor; //应用程序监控所在DLL的停止监控函数地址
	char m_szFilePath[MAX_PATH];  //保存的文件对象
	char m_szName[20],m_szIp[20];
};
#endif//__SYSTEMMONITOR_H__