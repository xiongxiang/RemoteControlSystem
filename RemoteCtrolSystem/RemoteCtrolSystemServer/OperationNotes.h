/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   OperationNotes.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   
**Create date:  2013/05/03   9:04
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
#ifndef __OPERATIONNOTES_H__
#define __OPERATIONNOTES_H__

#include <vector>

struct Notes{
	CString name;
	CString action;
	CString path;
	CString time;	
};

class OperationNotes
{
public:
	OperationNotes(void);
	~OperationNotes(void);

	std::vector<Notes> GetOperationNotes();

	/**
	 * @Brief GetNotesByName 获取某一用户的所有操作记录
	 * @Parameter CString name  用户账户名
	 * @Returns std::vector<Notes>
	 * @Remark  
	 **/
	std::vector<Notes> GetNotesByName(CString name);

	//************************************
	// Method:    GetNotesByType
	// Parameter: int type 1:表示只获取应用程序打开关闭的记录，2:表示只获取文件操作记录，0:表示全部获取
	// Returns:   std::vector<Notes>
	//************************************
	std::vector<Notes> GetNotesByType(int type);

	/**
	 * @Brief GetNotesByNameAndType 获取用户的一种操作类型的所有记录
	 * @Parameter CString name 用户名
	 * @Parameter int type 操作类型，1:表示只获取应用程序打开关闭的记录，2:表示只获取文件操作记录，0:表示全部获取
	 * @Returns std::vector<Notes> 操作记录结果集
	 * @Remark  
	 **/
	std::vector<Notes> GetNotesByNameAndType(CString name,int type);
	/**
	 * @Brief ClearLogFile 清除操作记录文件的所有记录
	 * @Returns void
	 * @Remark  
	 **/
	void ClearLogFile();

private:
	CStdioFile m_file;
	CString m_strFilePath;
	std::vector<Notes> m_vtNotes;

	void Init();
};
#endif//__OPERATIONNOTES_H__