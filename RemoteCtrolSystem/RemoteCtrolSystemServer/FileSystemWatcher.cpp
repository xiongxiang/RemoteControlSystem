#include "StdAfx.h"
#include "FileSystemWatcher.h"
#include <atlconv.h>
#include <fstream>

using namespace std;

FileSystemWatcher::FileSystemWatcher(char name[20],char ip[20],char path[20] , char dir[MAX_PATH])
{
	hDir = INVALID_HANDLE_VALUE;
	strcpy_s(WatchedDir,dir);
	strcpy_s(m_szName,name);
	strcpy_s(m_szIp,ip);
	strcpy_s(m_szPath,path);
}

FileSystemWatcher::~FileSystemWatcher(void)
{
}

void FileSystemWatcher::Run()
{
	USES_CONVERSION;
	this->hDir = CreateFile(  //调用DirectoryChangeW进行监视前，必须得有相应的文件句柄
		A2T(WatchedDir),
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE|FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		NULL);
	if (INVALID_HANDLE_VALUE == hDir)
	{
		return ;
	}
	char buf[ 2*(sizeof(FILE_NOTIFY_INFORMATION)+MAX_PATH) ];
	FILE_NOTIFY_INFORMATION* pNotify=(FILE_NOTIFY_INFORMATION *)buf;
	DWORD BytesReturned;
	while (true)
	{
		if (ReadDirectoryChangesW(hDir,pNotify,sizeof(buf),true,  //进行监控
			FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_ATTRIBUTES| FILE_NOTIFY_CHANGE_SIZE|
			FILE_NOTIFY_CHANGE_LAST_WRITE| FILE_NOTIFY_CHANGE_LAST_ACCESS|
			FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_SECURITY,
			&BytesReturned,
			NULL,NULL))
		{
			//CString strName1(pNotify->FileName);
			char tmp[MAX_PATH], str1[MAX_PATH], str2[MAX_PATH];
			memset( tmp, 0, sizeof(tmp) );
			WideCharToMultiByte( CP_ACP,0,pNotify->FileName,pNotify->FileNameLength/2,tmp,99,NULL,NULL );
			strcpy( str1, tmp );
			
			if (0!=pNotify->NextEntryOffset)
			{
				PFILE_NOTIFY_INFORMATION p = (PFILE_NOTIFY_INFORMATION)((char*)pNotify+pNotify->NextEntryOffset);
				memset( tmp, 0, sizeof(tmp) );
				WideCharToMultiByte( CP_ACP,0,p->FileName,p->FileNameLength/2,tmp,99,NULL,NULL );
				strcpy( str2, tmp );
			}
			DealFunc(pNotify->Action,str1,str2);
		}
		else
		{
			break;
		}
	}
}


void FileSystemWatcher::DealFunc( DWORD action,char *name1,char* name2 )
{
	char str1[MAX_PATH], str2[MAX_PATH] = "";
	strcpy(str1,WatchedDir);
	strcat(str1,name1);	
	
	if (action == FILE_ACTION_RENAMED_OLD_NAME ) //重命名
	{
		strcpy(str2,WatchedDir);
		strcat(str2,name2);
	}
	WriteToLog(action,str1,str2);
}


void FileSystemWatcher::WriteToLog(int action,char file1[MAX_PATH],char file2[MAX_PATH] )
{
	USES_CONVERSION;
	strlwr(file1);strlwr(m_szPath);
	if (strcmp(m_szPath,file1) == 0)
	{
		return ;
	}

	char result[500] = "";
	char szAction[10] = "";
	switch(action)
	{
	case ADDED:
		strcpy_s(szAction,"[创建]");
		break;
	case REMOVED:
		strcpy_s(szAction,"[删除]");
		break;
	case MODIFIED:
		strcpy_s(szAction,"[修改]");
		break;
	case RENAMED:
		strcpy_s(szAction,"[重命名]");
		break;
	}
	char time[20];
	GetTime(time);
	CFile file;
	file.Open(A2T(m_szPath),CFile::modeCreate | CFile::modeNoTruncate);
	file.Close();
	sprintf_s(result,"%-10s:%-15s -> %-8s %-20s %s\r\n",m_szName,m_szIp,szAction,time,file1);
	fstream os(m_szPath,ios::app|ios::ate|ios::out);
	os.write(result,strlen(result));
	os.close();
}

void FileSystemWatcher::GetTime( char time[] )
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf(time,"%d-%d-%d %d:%d:%d",systime.wYear,
		systime.wMonth,
		systime.wDay,
		systime.wHour,
		systime.wMinute,
		systime.wSecond);
}
