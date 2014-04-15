#include "StdAfx.h"
#include "SystemMonitor.h"
#include <atlconv.h>

SystemMonitor::SystemMonitor( ): isActive(FALSE),appStartMonitor(NULL),appStopMonitor(NULL)
{
	HINSTANCE hMonitor = ::LoadLibrary(L"ApplicationMonitor.dll");
	if(hMonitor == NULL){		
		return ;
	}else{
		appStartMonitor = (_AddApplicatinMonitor)::GetProcAddress(hMonitor,MAKEINTRESOURCEA(1));
		appStopMonitor = (_RemoveApplicationMonitor)::GetProcAddress(hMonitor,MAKEINTRESOURCEA(2));
	}
}

SystemMonitor::~SystemMonitor(void)
{
	std::vector<FileSystemWatcher*>::iterator iter = m_vpFSW.begin();
	for (;iter!=m_vpFSW.end();iter++)
	{
		//(*iter)->Terminate();
		delete *iter;
	}
}

void SystemMonitor::Start()
{
	USES_CONVERSION;
	if (!isActive)
	{
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL,szPath,MAX_PATH);
		CString PathName(szPath);
		CString strDir = PathName.Left(PathName.ReverseFind(_T('\\')) + 1);
		strDir+=m_szFilePath;
		appStartMonitor(m_szName,m_szIp,CT2A(strDir));

		/*TCHAR buf[100];  
		DWORD len=::GetLogicalDriveStrings(sizeof(buf)/sizeof(TCHAR),buf);
		for (TCHAR* s = buf;*s;s+=_tcslen(s)+1)
		{
			if (::GetDriveType(s) == DRIVE_FIXED)
			{
				m_vpFSW.push_back(new FileSystemWatcher(m_szName,m_szIp,CT2A(strDir),T2A(s)));
			}
		}*/
		m_vpFSW.push_back(new FileSystemWatcher(m_szName,m_szIp,CT2A(strDir),"D:\\"));
		m_vpFSW.push_back(new FileSystemWatcher(m_szName,m_szIp,CT2A(strDir),"E:\\"));
		std::vector<FileSystemWatcher*>::iterator iter = m_vpFSW.begin();
		for (;iter!=m_vpFSW.end();iter++)
		{
			(*iter)->Start();
		}
		isActive = TRUE;
	}	
}


void SystemMonitor::SetName(const char name[20] )
{
	strcpy_s(m_szName,name);
}

void SystemMonitor::SetIp(const char *ip)
{
	strcpy_s(m_szIp,ip);
}

BOOL SystemMonitor::isMonitorActive()
{
	return isActive;
}

void SystemMonitor::SetFilePath(const char path[MAX_PATH] )
{
	strcpy_s(m_szFilePath,path);
}

void SystemMonitor::Stop()
{
	if (isActive)
	{
		std::vector<FileSystemWatcher*>::iterator iter = m_vpFSW.begin();
		for (;iter!=m_vpFSW.end();iter++)
		{
			(*iter)->Terminate();
			//delete *iter;
		}
		appStopMonitor();
		isActive = FALSE;
	}	
}
