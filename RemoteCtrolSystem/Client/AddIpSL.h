#pragma once


// CAddIpSL 对话框

class CAddIpSL : public CDialog
{
	DECLARE_DYNAMIC(CAddIpSL)

public:
	CAddIpSL(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddIpSL();

// 对话框数据
	enum { IDD = IDD_ADD_IP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
