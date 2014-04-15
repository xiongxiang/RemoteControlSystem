/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**
**
**                   http://www.electronics.com 
**-------------File Info---------------------------------------------------
**File Name:HostListConfig.h
**Latest modified Data:2013-4-17  11:09:53
**Latest Version:v1.0
**Description:管理配置文件中的远程列表配置信息
**
**-------------------------------------------------------------------------
**Create by:XuWunJun
**Create date:2013-4-17  11:09:53
**Version:v1.0
**Description:管理配置文件中的远程列表配置信息
**
**
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**************************************************************************/
#ifndef __HOSTLISTCONFIG_H__
#define __HOSTLISTCONFIG_H__
#include "..\tinyxml\tinystr.h"
#include "..\tinyxml\tinyxml.h"
#include <vector>


/************************************************************************/
/*        远程列表中，表示远程主机名字，ip以及连接端口的数据结构        */
/************************************************************************/
struct  Host
{
	char name[32];
	char ip[16];
	int  port;
};
class HostListConfig
{
public:
	HostListConfig(void);
	~HostListConfig(void);

	/**
	   @brief:初始化HostListConfig
	   @Parameter:char * FilePath
	   @Return:bool
	*/
	bool Init(char* FilePath);
	/**
	   @brief:读取配置文件中的主机信息，并把主机信息保存到vtHostList中
	   @Parameter:std::vector<Host> & vtHostList
	   @Return:void
	*/
	void ReadHostList(std::vector<Host>& vtHostList);
	/**
	   @brief:添加主机信息到配置文件中
	   @Parameter:Host host
	   @Return:void
	*/
	void AddHost(Host host);
	/**
	   @brief:在配置文件中删除name（主机名）对应的主机信息
	   @Parameter:char * name
	   @Return:void
	*/
	void DeleteHost(char* name);
private:
	TiXmlDocument* m_pDocument;
	TiXmlElement*  m_pRootElement;

};

#endif
