#include "StdAfx.h"
#include "OperationNotes.h"
#include <locale.h>

OperationNotes::OperationNotes(void)
{
	Init();
}

OperationNotes::~OperationNotes(void)
{
}

void OperationNotes::Init()
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL,szPath,MAX_PATH);
	CString PathName(szPath);
	m_strFilePath = PathName.Left(PathName.ReverseFind(_T('\\')) + 1);
	m_strFilePath += _T("monitor.log");
	GetOperationNotes();
}

std::vector<Notes> OperationNotes::GetOperationNotes()
{
	m_vtNotes.clear();
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定<ctpye.h>中字符处理方式
	if(!m_file.Open(m_strFilePath,CFile::modeRead))
	{
		AfxMessageBox(_T("Open file error!"));
		return m_vtNotes;
	}
	CString strLine;
	while (m_file.ReadString(strLine))
	{
		Notes note;
		//std::string line(strLine.GetBuffer());
		note.name = strLine.Mid(0,10).Trim();
		note.action = strLine.Mid(31,strLine.Find(']',31)-31);
		note.time = strLine.Mid(36,20).Trim();
		note.path  = strLine.Right(strLine.GetLength()-56).Trim();
		m_vtNotes.push_back(note);
	}	
	m_file.Close(); 
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
	return m_vtNotes;
}

std::vector<Notes> OperationNotes::GetNotesByType( int type )
{
	if(0 == type)
	{
		return m_vtNotes;
	}
	else if(1==type)
	{
		std::vector<Notes> tempNotes;
		std::vector<Notes>::iterator iter;
		for (iter = m_vtNotes.begin();iter!=m_vtNotes.end();iter++)
		{
			if (iter->action == CString(_T("启动")) || iter->action ==  CString(_T("关闭")))
			{
				tempNotes.push_back(*iter);
			}
		}
		return tempNotes;
	}
	else
	{
		std::vector<Notes> tempNotes;
		std::vector<Notes>::iterator iter;
		for (iter = m_vtNotes.begin();iter!=m_vtNotes.end();iter++)
		{
			if (!(iter->action == CString(_T("启动")) || iter->action ==  CString(_T("关闭"))))
			{
				tempNotes.push_back(*iter);
			}
		}
		return tempNotes;
	}
}

std::vector<Notes> OperationNotes::GetNotesByName( CString name )
{
	if (name == _T(""))
	{
		return m_vtNotes;
	}
	std::vector<Notes> tempNotes;
	std::vector<Notes>::iterator iter;
	for (iter = m_vtNotes.begin();iter!=m_vtNotes.end();iter++)
	{
		if (iter->name == name)
		{
			tempNotes.push_back(*iter);
		}
	}
	return tempNotes;
}

std::vector<Notes> OperationNotes::GetNotesByNameAndType( CString name,int type )
{
	std::vector<Notes> tempNotes;
	std::vector<Notes>::iterator iter;
	for (iter = m_vtNotes.begin();iter!=m_vtNotes.end();iter++)
	{
		if (name == _T(""))  //如果传入的名字为空
		{
			if (type == 0)
			{
				return m_vtNotes;
			}
			else if (1 == type)
			{
				if (iter->action == CString(_T("启动")) || iter->action ==  CString(_T("关闭")))
				{
					tempNotes.push_back(*iter);
				}
			}
			else
			{
				if (!(iter->action == CString(_T("启动")) || iter->action ==  CString(_T("关闭"))))
				{
					tempNotes.push_back(*iter);
				}
			}
			continue;
		}
		if (iter->name == name) //如果传入的名字为空
		{
			if (type == 0)
			{
				tempNotes.push_back(*iter);
			}
			else if (1 == type)
			{
				if (iter->action == CString(_T("启动")) || iter->action ==  CString(_T("关闭")))
				{
					tempNotes.push_back(*iter);
				}
			}
			else
			{
				if (!(iter->action == CString(_T("启动")) || iter->action ==  CString(_T("关闭"))))
				{
					tempNotes.push_back(*iter);
				}
			}
			
		}
	}
	return tempNotes;
}

void OperationNotes::ClearLogFile()
{
	m_file.Open(m_strFilePath,CFile::modeCreate);
	m_file.Close();
}
