/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   FileSystemWatcher.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   魏胤
**Create date:  2013/05/03   8:32
**Version:
**Description:  对某一个文件夹进行监控的线程，包括监控该文件夹下的子文件夹内容
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
#ifndef __FILESYSTEMWATCHER_H__
#define __FILESYSTEMWATCHER_H__

#include "../Thread/Thread.h"

class FileSystemWatcher : public Thread
{
public:
	enum ACTION{ADDED=1, REMOVED=2, MODIFIED=3, RENAMED=4 };
	FileSystemWatcher(char name[20],char ip[20],char path[20] , char dir[MAX_PATH]);
	~FileSystemWatcher(void);	

protected:
	void Run(); //线程函数
	
private:
	/**
	 * @Brief GetTime 获取当前时间
	 * @Parameter char time[] 保存时间的字符数组
	 * @Returns void
	 * @Remark  指对文件进行操作的时间
	 **/
	void GetTime( char time[]); 

	/**
	 * @Brief DealFunc 对相对与监视文件夹的路径进行处理，转换成绝对路径
	 * @Parameter DWORD action 操作动作
	 * @Parameter char * name1 文件或文件夹的相对路径
	 * @Parameter char * name2 文件或文件的相对路径，重名名动作需要这个参数
	 * @Returns void
	 * @Remark  
	 **/
	void DealFunc(DWORD action,char *name1,char* name2);

	/**
	 * @Brief WriteToLog 把本次对文件监控的结果写入日志文件
	 * @Parameter int action 对文件操作的动作，有创建、修改、删除、重命名四种
	 * @Parameter char file1[MAX_PATH] 被操作的文件或文件夹
	 * @Parameter char file2[MAX_PATH] 重命名涉及的新的文件或文件夹
	 * @Returns void
	 * @Remark  
	 **/
	void WriteToLog(int action,char file1[MAX_PATH],char file2[MAX_PATH] );

	char WatchedDir[MAX_PATH];//监视的文件夹
	char m_szName[20],m_szIp[20],m_szPath[MAX_PATH];
	HANDLE hDir;  
};
#endif//__FILESYSTEMWATCHER_H__
