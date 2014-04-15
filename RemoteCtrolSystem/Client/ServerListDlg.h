#pragma once
#include "afxwin.h"
#include "..\ClientConfig\HostListConfig.h"
#include <vector>

#define SL_HIDE 0
#define SL_UNDOCK 1
#define SL_DOCK_WINDOW 2
#define SL_DOCK_SCREEN 3
// CServerListDlg 对话框

class CServerListDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerListDlg)

public:
	CServerListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServerListDlg();

	/**
	   @brief:返回远程列表的状态，0隐藏，1不停靠，2停靠窗口边缘停靠，3停靠屏幕边缘
	   @Return:int
	*/
	int GetStatus();
	/**
	   @brief:设置远程列表状态，0隐藏，1不停靠，2停靠窗口边缘停靠，3停靠屏幕边缘
	   @Parameter:int status
	   @Return:bool
	*/
	bool SetStatus(int status);
	bool Init(HostListConfig* hostListConfig);
	/**
	   @brief:将保存有主机信息的HostListConfig传给远程列表窗口
	   @Parameter:HostListConfig * hostListConfig
	   @Return:void
	*/
	void SetHostList(HostListConfig* hostListConfig);
	/**
	   @brief:将远程列表停靠主窗口右侧
	   @Return:void
	*/
	void DockWindow();
// 对话框数据
	enum { IDD = IDD_DIALOG_SERVER_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//	virtual BOOL OnInitDialog();
	CToolBar	m_toolbar;
	//CListBox	m_lstServer;
	int			m_Status;//serverList的状态，显示/隐藏/停靠屏幕边缘
	std::vector<Host> m_vtHostList;
	HostListConfig* m_HostListConfig;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnExitSizeMove();
	afx_msg void OnBtnDelete();
	virtual BOOL OnInitDialog();
	CListBox m_lstServer;
};
