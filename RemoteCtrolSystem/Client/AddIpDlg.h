#pragma once
#include "resource.h"
#include "..\ClientConfig\HostListConfig.h"
#include "afxwin.h"
#include "afxcmn.h"

// CAddIpDlg 对话框

class CAddIpDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddIpDlg)

public:
	CAddIpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddIpDlg();

	/**
	   @brief:将存有主机信息的HostListConfig指针传给AddIpDlg
	   @Parameter:HostListConfig * hostListConfig
	   @Return:void
	*/
	void SetHostList(HostListConfig* hostListConfig);
	/**
	   @brief:返回当前添加的新的主机信息的主机名
	   @Return:CString
	*/
	CString GetAddName();
// 对话框数据
	enum { IDD = IDD_ADD_IP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	HostListConfig* m_HostListConfig;
	CString m_szHostName;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	
private:
	CIPAddressCtrl	m_HostIP;
	CEdit m_tbHostName;
	CEdit m_tbPort;
};  
