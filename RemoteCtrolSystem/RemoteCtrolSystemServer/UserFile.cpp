#include "StdAfx.h"
#include "UserFile.h"
#include "Config.h"
#include "AES.h"

CUserFile::CUserFile(void)
{
	this->m_pszFilePath = _T("user");
	InitFile();
	GetDataFromFile();
}

CUserFile::~CUserFile(void)
{
}

BOOL CUserFile::InitFile(void)
{
	Config config;
	CString temp;
	if (config.GetIsEncryptFile())
	{
		temp = m_pszFilePath+_T(".crypt");
	}
	else
	{
		temp = m_pszFilePath+_T(".plain");
	}
	if(m_file.Open(temp,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		m_file.Close();
		return TRUE;
	}
	m_file.Close();
	return FALSE;
}


//************************************
// Method:    GetDataFromFile  
// Returns:   void
//************************************
void CUserFile::GetDataFromFile()
{
	m_DataInFile.clear();
	Config config;
	BOOL isEncrypt = config.GetIsEncryptFile();
	if (isEncrypt)
	{
		AES aes;
		char* key = "RemoteCtrolSystem";
		aes.set_key((u1byte*)key,256);
		aes.decrypt(m_pszFilePath);
	}
	if (m_file.Open(m_pszFilePath+_T(".plain"),CFile::modeRead))
	{
		UserData temp;
		m_file.Seek(0,CFile::begin);
		int filelength = m_file.GetLength();
		int n = filelength/sizeof(UserData);
		for (int i = 0;i<n;i++)
		{
			m_file.Read(&temp,sizeof(UserData));
			m_DataInFile.push_back(temp);
		}
	}
	m_file.Close();
	if (isEncrypt)
	{
		DeleteFile(m_pszFilePath+_T(".plain"));
	}	
}

void CUserFile::SetDataToFile()
{
	Config config;
	BOOL isEncrypt = config.GetIsEncryptFile();
	if (isEncrypt)
	{
		AES aes;
		char* key = "RemoteCtrolSystem";
		aes.set_key((u1byte*)key,256);
		aes.decrypt(m_pszFilePath);
	}
	if (m_file.Open(m_pszFilePath+_T(".plain"),CFile::modeCreate | CFile::modeWrite))
	{
		std::vector<UserData>::iterator theIter;
		for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter ++)
		{
			m_file.Write(&(*theIter),sizeof(UserData));
		}
	}	
	m_file.Close();
	if (isEncrypt)
	{
		AES aes;
		char* key = "RemoteCtrolSystem";
		aes.set_key((u1byte*)key,256);
		aes.encrypt(m_pszFilePath);
		DeleteFile(m_pszFilePath+_T(".plain"));
	}
}

BOOL CUserFile::Add( UserData &user )
{
	Config config;
	AES aes;
	char* key = "RemoteCtrolSystem";
	aes.set_key((u1byte*)key,256);
	BOOL isEncrypt = config.GetIsEncryptFile();
	if (isEncrypt)
	{	
		aes.decrypt(m_pszFilePath);
	}
	if (m_file.Open(m_pszFilePath+_T(".plain"),CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		int fileLength = m_file.GetLength();
		int endSeek =(fileLength/sizeof(UserData)) *sizeof(UserData);
		m_file.Seek(endSeek,CFile::begin);
		//m_file.SeekToEnd();
		m_DataInFile.push_back(user);
		m_file.Write(&user,sizeof(UserData));	
	} 
	else
	{		
		return FALSE;
	}	
	m_file.Close();
	if (isEncrypt)
	{
		aes.encrypt(m_pszFilePath);
		DeleteFile(m_pszFilePath+_T(".plain"));
	}
	return TRUE;
}

BOOL CUserFile::Delete( UserData &user )
{
	std::vector<UserData>::iterator theIter;
	for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter ++)
	{
		//if ((lstrcmp(theIter->name ,user.name) == 0)/* && (lstrcmp(theIter->pwd,user.pwd) == 0*/))
		if (lstrcmp(theIter->name ,user.name) == 0)
		{
			m_DataInFile.erase(theIter);
			break;
		}
	}
	SetDataToFile();
	return TRUE;
}

BOOL CUserFile::Update( UserData &user )
{
	std::vector<UserData>::iterator theIter;
	for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter ++)
	{
		//if ((lstrcmp(theIter->name ,user.name) == 0) && (lstrcmp(theIter->pwd,user.pwd) == 0))
		if (lstrcmp(theIter->name ,user.name) == 0)
		{
			theIter->power = user.power;
			break;
		}
	}
	SetDataToFile();
	return TRUE;
}

int CUserFile::GetUserPower( const TCHAR* name,const TCHAR* pwd )
{
	std::vector<UserData>::iterator theIter;
	for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter ++)
	{
		if ((lstrcmp(theIter->name ,name) == 0) && (lstrcmp(theIter->pwd,pwd) == 0))
		{
			return theIter->power;
		}
	}
	return -1;
}

std::vector<UserData> CUserFile::GetAllUsers()
{
	return m_DataInFile;
}
