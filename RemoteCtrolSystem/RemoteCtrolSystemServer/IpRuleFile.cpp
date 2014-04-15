#include "StdAfx.h"
#include "IpRuleFile.h"
#include "IniFile.h"
#include <atlconv.h>

CIpRuleFile::CIpRuleFile(void)
{
	this->m_pszFilePath = _T("IpRule.dat");
	InitFile();
	GetDataFromFile();
}

CIpRuleFile::~CIpRuleFile(void)
{
}

BOOL CIpRuleFile::Add(IpRule &rule )
{	
	if (m_file.Open(m_pszFilePath,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		m_file.SeekToEnd();
		
		/*CIniFile iniFile(_T("RemoteConfig.ini"));
		int ruleCount = iniFile.GetProfileInt(_T("connection"),_T("ruleCount"));
		ruleCount++;
		rule.sort = ruleCount*/;
		m_DataInFile.push_back(rule);
		m_file.Write(&rule,sizeof(IpRule));
		//iniFile.SetProfileInt(_T("connection"),_T("ruleCount"),ruleCount);
		//AfxMessageBox(L"写入完毕");	
	} 
	else
	{
		AfxMessageBox(L"系统异常，请退出后重新启动！");
		return FALSE;
	}	
	m_file.Close();
	return TRUE;
}

BOOL CIpRuleFile::Delete( IpRule &rule )
{
	std::vector<IpRule>::iterator theIter;
	for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter ++)
	{
		if ((lstrcmp(theIter->start ,rule.start) == 0) && (lstrcmp(theIter->end,rule.end) == 0))
		{
			m_DataInFile.erase(theIter);
			break;
		}
	}
	SetDataToFile();
	return TRUE;
}

BOOL CIpRuleFile::Update(IpRule &rule )
{
	std::vector<IpRule>::iterator theIter;
	for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter ++)
	{
		if ((lstrcmp(theIter->start ,rule.start) == 0) && (lstrcmp(theIter->end,rule.end) == 0))
		{
			theIter->power = rule.power;
			break;
		}
	}
	SetDataToFile();
	return TRUE;
}

BOOL CIpRuleFile::IsRuleExsist( const IpRule &rule )
{
	std::vector<IpRule>::iterator theIter;
	for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter ++)
	{
		if ((lstrcmp(theIter->start ,rule.start) == 0) && (lstrcmp(theIter->end,rule.end) == 0))
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CIpRuleFile::GetDataFromFile()
{
	m_DataInFile.clear();
	if (m_file.Open(m_pszFilePath,CFile::modeRead))
	{
		IpRule temp;
		m_file.Seek(0,CFile::begin);
		while(m_file.Read(&temp,sizeof(IpRule)))
		{
			m_DataInFile.push_back(temp);
		}
	}
	m_file.Close();
}

void CIpRuleFile::SetDataToFile()
{
	if (m_file.Open(m_pszFilePath,CFile::modeCreate | CFile::modeWrite))
	{
		std::vector<IpRule>::iterator theIter;
		for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter ++)
		{
			m_file.Write(&(*theIter),sizeof(IpRule));
		}
	}	
	m_file.Close();
}

std::vector<IpRule> CIpRuleFile::GetAllRules()
{
	return m_DataInFile;
}

void CIpRuleFile::InitFile()
{
	m_file.Open(m_pszFilePath,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	m_file.Close();
}

BOOL CIpRuleFile::MoveUp( int index )
{
	if (index!=0)
	{
		std::swap(m_DataInFile[index],m_DataInFile[index-1]);
		SetDataToFile();
	}
	return TRUE;
}

BOOL CIpRuleFile::moveDown( int index )
{
	if (index!=m_DataInFile.size() -1)
	{
		std::swap(m_DataInFile[index],m_DataInFile[index+1]);
		SetDataToFile();
	}
	return TRUE;
}

int CIpRuleFile::CompareIpAddress( LPCTSTR address1,LPCTSTR address2 )
{
	USES_CONVERSION;
	ULONG a = ntohl(inet_addr(CT2CA(address1)));
	ULONG b = ntohl(inet_addr(CT2CA(address2)));
	if (a <b)
	{
		return -1;
	}
	else if (a ==b)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int CIpRuleFile::GetPowerByIp( LPCTSTR address )
{
	std::vector<IpRule>::iterator theIter;
	for (theIter = m_DataInFile.begin();theIter!=m_DataInFile.end();theIter++)
	{
		if ((CompareIpAddress(theIter->start,address)<=0) && (CompareIpAddress(address,theIter->end)<=0))
		{
			return theIter->power;
		}
	}
	return 1;
}
