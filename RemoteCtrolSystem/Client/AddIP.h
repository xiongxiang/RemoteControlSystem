#pragma once


// CAddIP 对话框

class CAddIP : public CDialog
{
	DECLARE_DYNAMIC(CAddIP)

public:
	CAddIP(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddIP();

// 对话框数据
	enum { IDD = IDD_ADD_IP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
