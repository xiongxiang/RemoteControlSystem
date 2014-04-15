/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   IniFile.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:  魏胤
**Create date:  2013/04/07   9:47
**Version:  1.0
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
#ifndef __INIFILE_H__
#define __INIFILE_H__

class CIniFile
{
public:
	CIniFile(void);
	CIniFile(LPCTSTR szFileName);
	virtual ~CIniFile(void);

public:
	/**
	 * @Brief SetFileName  设置配置文件所在的路径
	 * @Parameter LPCTSTR szFileName 路径
	 * @Returns void
	 * @Remark  
	 **/
	void SetFileName(LPCTSTR szFileName);
	LPCTSTR GetFileName();

public:

	//************************************
	// Method:    SetProfileInt 添加整型的属性值
	// Parameter: LPCTSTR lpszSectionName  段名
	// Parameter: LPCTSTR lpszKeyName 关键字名
	// Parameter: int nKeyValue  值
	// Returns:   BOOL  是否成功
	//************************************
	BOOL SetProfileInt(LPCTSTR lpszSectionName,LPCTSTR lpszKeyName,int nKeyValue);

	//************************************
	// Method:    SetProfileString
	// Parameter: LPCTSTR lpszSectionName
	// Parameter: LPCTSTR lpszKeyName
	// Parameter: LPCTSTR lpszKeyVal
	// Returns:   BOOL
	//************************************
	BOOL SetProfileString(LPCTSTR lpszSectionName,LPCTSTR lpszKeyName,LPCTSTR lpszKeyVal);
	
	/**
	 * @Brief GetProfileSectionNames 获取ini配置文件中的所有段名
	 * @Parameter CStringArray & strArray  保存所有的段名
	 * @Returns DWORD
	 * @Remark  
	 **/
	DWORD GetProfileSectionNames(CStringArray& strArray);

	/**
	 * @Brief GetProfileInt  获取配置文件中的一个int型的项
	 * @Parameter LPCTSTR lpszSectionName  指定的段名
	 * @Parameter LPCTSTR lpszKeyName  指定的关键字名
	 * @Returns int  返回整型的项，若配置文件中没有，则返回0
	 * @Remark  
	 **/
	int GetProfileInt(LPCTSTR lpszSectionName,LPCTSTR lpszKeyName);

	/**
	 * @Brief GetProfileString 获取配置文件中的一个string型的项
	 * @Parameter LPCTSTR lpszSectionName  指定的段名
	 * @Parameter LPCTSTR lpszKeyName 指定的关键字名
	 * @Parameter CString & szKeyValue  保存string的项
	 * @Returns DWORD 
	 * @Remark  
	 **/
	DWORD GetProfileString(LPCTSTR lpszSectionName,LPCTSTR lpszKeyName ,CString& szKeyValue);

	/**
	 * @Brief DeleteSection  删除指定的段
	 * @Parameter LPCTSTR lpszSectionName  要删除的段名
	 * @Returns BOOL  返回是否删除成功
	 * @Remark  
	 **/
	BOOL DeleteSection(LPCTSTR lpszSectionName);

	/**
	 * @Brief DeleteKey 删除指定的项
	 * @Parameter LPCTSTR lpszSectionName  指定的段名
	 * @Parameter LPCTSTR lpszKeyName 指定的项的键值
	 * @Returns BOOL
	 * @Remark  
	 **/
	BOOL DeleteKey(LPCTSTR lpszSectionName,LPCTSTR lpszKeyName);

private:
	CString m_szFileName;  // .//Config.ini,如果该文件不存在，则exe第一次试图Write时将创建该文件
	UINT m_unMaxSection;  //最多支持的section数（256）
	UINT m_unSetionNameMaxSize; //section名称长度，这里设为32（Null-terminated)

	void Init();
};

#endif//__INIFILE_H__