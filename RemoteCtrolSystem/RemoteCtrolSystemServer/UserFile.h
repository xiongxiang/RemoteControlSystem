/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   CUserFile.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:    魏胤
**Create date:  2013/03/27   14:59
**Version:
**Description:  对文件操作的类，主要实现用户账户的增、删、改、查几个功能，要求
**   用户名的唯一。对文件的操作使用CFile来完成
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
#ifndef __CUserFile_H__
#define __CUserFile_H__

#include <vector>

//用来表示用户数据的结构体
struct UserData 
{
	int power;  //-1表示无效用户、0表示观看权限、1表示控制用户
	TCHAR name[20];
	TCHAR pwd[20];	
};

class CUserFile
{
public:
	CUserFile(void);
	~CUserFile(void);

	/**
	 * @Brief Add 添加一个用户数据到文件中
	 * @Parameter UserData & user 用户数据
	 * @Returns BOOL
	 * @Remark  
	 **/
	BOOL Add(UserData &user);

	/**
	 * @Brief Delete 从文件中删除一个用户数据
	 * @Parameter UserData & user 要删除的用户数据
	 * @Returns BOOL
	 * @Remark  其实这里只有他的用户名和密码是有效的。
	 **/
	BOOL Delete( UserData &user);

	/**1
	 * @Brief Update 更新用户数据
	 * @Parameter UserData & user  用户数据
	 * @Returns BOOL
	 * @Remark  根据用户名来更新数据，只能更改权限
	 **/
	BOOL Update( UserData &user);

	/**
	 * @Brief GetUserPower 获取用户权限
	 * @Parameter const TCHAR * name  用户名
	 * @Parameter const TCHAR * pwd 密码
	 * @Returns int 权限值
	 * @Remark  
	 **/
	int GetUserPower(const TCHAR* name,const TCHAR* pwd);

	/**
	 * @Brief GetAllUsers 获取所有用户数据
	 * @Returns std::vector<UserData>  所有用户数组
	 * @Remark  
	 **/
	std::vector<UserData> GetAllUsers();

private:
	CString m_pszFilePath;  //文件所在路径
	CFile m_file;  //文件对象
	std::vector<UserData> m_DataInFile; //对应于文件中的内容数组

private:
	void GetDataFromFile(); //从文件那里更新数据
	void SetDataToFile();  //更新文件
	BOOL InitFile(void);  //初始化文件
};

#endif//__CUserFile_H__
