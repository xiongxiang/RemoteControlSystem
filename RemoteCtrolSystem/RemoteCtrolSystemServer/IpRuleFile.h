/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   IpRuleFile.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   
**Create date:  2013/05/03   9:20
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
#ifndef __IPRULEFILE_H__
#define __IPRULEFILE_H__

#include <vector>

//存储IP规则的结构体
struct IpRule 
{
	TCHAR start[16];
	TCHAR end[16];
	int power; //-1表示该规则无效，0表示拒绝，1表示允许
};

class CIpRuleFile
{
public:
	CIpRuleFile(void);
	~CIpRuleFile(void);

public:

	//************************************
	// Method:    Add  添加规则
	// Parameter: IpRule & rule  规则变量
	// Returns:   BOOL
	//************************************
	BOOL Add(IpRule &rule);

	//************************************
	// Method:    Delete 删除规则
	// Parameter: IpRule & rule 要删除的规则变量
	// Returns:   BOOL  删除是否成功，true表示成功
	//************************************
	BOOL Delete( IpRule &rule);

	//************************************
	// Method:    Update
	// Parameter: IpRule & rule
	// Returns:   BOOL
	//************************************
	BOOL Update( IpRule &rule);

	//************************************
	// Method:    IsRuleExsist
	// Parameter: const IpRule & rule
	// Returns:   BOOL
	//************************************
	BOOL IsRuleExsist(const IpRule &rule);

	/**
	 * @Brief GetAllRules 获取文件中的所有规则
	 * @Returns std::vector<IpRule>
	 * @Remark  
	 **/
	std::vector<IpRule> GetAllRules();

	/**
	 * @Brief MoveUp 向上移动指定的规则
	 * @Parameter int index 规则所在位置，从0开始
	 * @Returns BOOL
	 * @Remark  
	 **/
	BOOL MoveUp(int index);

	/**
	 * @Brief moveDown 向下移动指定的规则
	 * @Parameter int index 规则所在的位置
	 * @Returns BOOL
	 * @Remark  
	 **/
	BOOL moveDown(int index);

	/**
	 * @Brief CompareIpAddress  比较两个ip地址的大小
	 * @Parameter LPCTSTR address1 待比较的地址1
	 * @Parameter LPCTSTR address2 待比较的地址2
	 * @Returns int 返回比较结果，-1表示小于、0表示等、1表示大于
	 * @Remark  
	 **/
	int CompareIpAddress(LPCTSTR address1,LPCTSTR address2);

	/**
	 * @Brief GetPowerByIp 获取指定ip地址的权限
	 * @Parameter LPCTSTR address ip地址
	 * @Returns int 返回权限
	 * @Remark  
	 **/
	int GetPowerByIp(LPCTSTR address);
private:
	TCHAR* m_pszFilePath;
	CFile m_file;
	std::vector<IpRule> m_DataInFile; //对应于文件中的内容数组。

	void GetDataFromFile(); //从文件那里更新数据
	void SetDataToFile();  //更新文件
	void InitFile();
};
#endif//__IPRULEFILE_H__