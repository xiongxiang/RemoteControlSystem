#include "StdAfx.h"
#include "Config.h"

Config::Config(void)
{
	m_DataFile.SetFileName(_T("RemoteConfig.ini"));
}

Config::~Config(void)
{
}

BOOL Config::GetIsAllowControl()
{
	int isAllowControl =  m_DataFile.GetProfileInt(_T("sets"),_T("allowControl"));
	return isAllowControl == 1?TRUE:FALSE;
}

void Config::SetIsAllowControl( BOOL isAllowControl )
{
	if (isAllowControl)
	{
		m_DataFile.SetProfileInt(_T("sets"),_T("allowControl"),1);
	}
	else
	{
		m_DataFile.SetProfileInt(_T("sets"),_T("allowControl"),0);
	}
}

BOOL Config::GetIsAutoRun()
{
	int isAutoRun =  m_DataFile.GetProfileInt(_T("sets"),_T("autoRun"));
	return isAutoRun == 1?TRUE:FALSE;
}

void Config::SetIsAutoRun( BOOL isAutoRun )
{
	if (isAutoRun)
	{
		m_DataFile.SetProfileInt(_T("sets"),_T("autoRun"),1);
	}
	else
	{
		m_DataFile.SetProfileInt(_T("sets"),_T("autoRun"),0);
	}
}

BOOL Config::GetIsShowInTask()
{
	int isShowInTask =  m_DataFile.GetProfileInt(_T("sets"),_T("showTask"));
	return isShowInTask == 1?TRUE:FALSE;
}

void Config::SetIsShowInTask( BOOL isShowInTask )
{
	if (isShowInTask)
	{
		m_DataFile.SetProfileInt(_T("sets"),_T("showTask"),1);
	}
	else
	{
		m_DataFile.SetProfileInt(_T("sets"),_T("showTask"),0);
	}
}

BOOL Config::GetIsEncryptFile()
{
	int isEncryptFile =  m_DataFile.GetProfileInt(_T("sets"),_T("codingFile"));
	return isEncryptFile == 1?TRUE:FALSE;
}

void Config::SetIsEncryptFile( BOOL isEncryptFile )
{
	if (isEncryptFile)
	{
		m_DataFile.SetProfileInt(_T("sets"),_T("codingFile"),1);
	}
	else
	{
		m_DataFile.SetProfileInt(_T("sets"),_T("codingFile"),0);
	}
}

int Config::GetConnectPort()
{
	return m_DataFile.GetProfileInt(_T("connection"),_T("mainPort"));
}

void Config::SetConnectPort( int port )
{
	m_DataFile.SetProfileInt(_T("connection"),_T("mainPort"),port);
}

CString Config::GetAdminLoginPwd()
{
	CString pwd;
	m_DataFile.GetProfileString(_T("admin"),_T("adminPwd"),pwd);
	return pwd;
}

void Config::SetAdminLoginPwd( CString pwd )
{
	m_DataFile.SetProfileString(_T("admin"),_T("adminPwd"),pwd);
}

BOOL Config::GetIsUsePwdProtection()
{
	int isUsePwdProtection =  m_DataFile.GetProfileInt(_T("admin"),_T("usePwdProtect"));
	return isUsePwdProtection == 1?TRUE:FALSE;
}

void Config::SetIsUsePwdProtection( BOOL isUsePwdProtection )
{
	if (isUsePwdProtection)
	{
		m_DataFile.SetProfileInt(_T("admin"),_T("usePwdProtect"),1);
	}
	else
	{
		m_DataFile.SetProfileInt(_T("admin"),_T("usePwdProtect"),0);
	}
}
