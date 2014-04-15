// RemoteCtrolSystemServerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "TabServerDlg.h"
#include "TabAccountDlg.h"
#include "TabConnectionDlg.h"

#include "DealConnection.h"
#include "TabAboutDlg.h"
#include "WndClassList.h"
#include "AES.h"
#include "afxwin.h"

#include "../SocketIPv4/TCPThreadedServer.h"
// CRemoteCtrolSystemServerDlg 对话框
class CRemoteCtrolSystemServerDlg : public CDialog
{
// 构造
public:
	CRemoteCtrolSystemServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REMOTECTROLSYSTEMSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabCtrl;
	TabServerDlg m_tsdServer;
	TabConnectionDlg m_dlgConnection;
	TabAccountDlg m_dlgAcount;
	TabAboutDlg m_dlgAbout;
	
	//CAboutDlg m_dlgAbout;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnOk();

	//************************************
	// Method:    SetAutoRun 设置开机启动项
	// Parameter: BOOL bAutoRun  true表示开机启动，false表示开机不启动
	// Returns:   void
	//************************************
	void SetAutoRun(BOOL bAutoRun);

	afx_msg void OnBnClickedBtnApply();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);

	/**
	 * @Brief AddToTray 添加托盘图标
	 * @Returns void
	 * @Remark  
	 **/
	void AddToTray();

	/**
	 * @Brief DeleteFromTray  删除托盘图标
	 * @Returns void
	 * @Remark  
	 **/
	void DeleteFromTray();

	//************************************
	// Method:    UpdateWindowControl  根据配置文件，更改系统的行为。例如开机启动、允许远程连接等
	// Returns:   void
	//************************************
	void UpdateWindowControl();
	afx_msg void OnBnClickedBtnStartserver();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	TCPThreadedServer m_threadServer;  //使用多线程的TCP服务器
	TCPServiceFactoryTemplate<DealConnection> servicFactory;  //用于创建一个TCP连接对象的工厂
	CButton m_btnStartServer;

private:
	BOOL m_bIsServerStarted;
	SystemMonitor watcher;  //系统监听器，用来监听应用程序的启动和对文件系统的操作
};
