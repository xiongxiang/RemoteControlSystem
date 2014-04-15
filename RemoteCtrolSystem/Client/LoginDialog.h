#pragma once
#include "afxwin.h"
#include "AddIpDlg.h"
#include "..\ClientConfig\HostListConfig.h"
#include "..\Message\UserMsg.h"
#include <vector>

// CLoginDialog 对话框

class CLoginDialog : public CDialog
{
	DECLARE_DYNAMIC(CLoginDialog)

public:
	CLoginDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDialog();

	void	Init(HostListConfig* pHostListConfig,Host* pHost);
	/**
	   @brief:返回用户名
	   @Return:CString
	*/
	CString GetUserName();
	/**
	   @brief:返回密码
	   @Return:CString
	*/
	CString	GetPassword();

// 对话框数据
	enum { IDD = IDD_LOGIN_DIALOG };

	CAddIpDlg	m_dlgAddIP;
	CComboBox	m_cmbServerList;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CEdit		m_tbPassword;
	CEdit		m_tbUserName;
	CString		m_szUserName; 
	CString		m_szPassword; 
	
	/**
	   @brief:登录按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonLogin();
	/**
	   @brief:选择远程主机下拉列表时
	   @Return:void
	*/
	afx_msg void OnCbnSelchangeServerCombo();
	/**
	   @brief:退出按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonExit();
protected:
	virtual void OnOK();
	Host*						m_pHost;
	HostListConfig*				m_HostListConfig;
	std::vector<Host>			m_vtHostList;
public:
	virtual BOOL OnInitDialog();
};
