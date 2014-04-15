#pragma once

#include "Resource.h"
// CChangeAdminPwd 对话框

class CChangeAdminPwd : public CDialog
{
	DECLARE_DYNAMIC(CChangeAdminPwd)

public:
	CChangeAdminPwd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeAdminPwd();

// 对话框数据
	enum { IDD = IDD_CHANGE_PWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnNewpwdok();
	CString m_strNewPwd;  //旧的密码
	CString m_strSurePwd;  //新密码
	afx_msg void OnBnClickedBtnNewpwdcancel();
};
