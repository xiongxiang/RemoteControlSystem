#pragma once
#include "resource.h"
#include "afxwin.h"

// CEnterDlg 对话框

class CEnterDlg : public CDialog
{
	DECLARE_DYNAMIC(CEnterDlg)

public:
	CEnterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEnterDlg();

// 对话框数据
	enum { IDD = IDD_ENTERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOk();
	CEdit m_enterPwd;  
	afx_msg void OnBnClickedBtnCancel();
};
