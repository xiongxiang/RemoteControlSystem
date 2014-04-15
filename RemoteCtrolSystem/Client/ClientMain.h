#pragma once

#include "LoginDialog.h"
#include "AddIpDlg.h"
#include "ServerListDlg.h"
#include "SetupDlg.h"
#include "DisplayDlg.h"
#include "..\\ClientConfig\HostListConfig.h"
#include "..\\Graphic\ScreenDisplay.h"
#include "..\\Graphic\ScreenShot.h"
#include "..\SocketIPv4\TCPClient.h"
#include "../Thread/LocalMutex.h"
#include "../Thread/AutoLock.h"
#include <queue>
#include <vector>
#include "afxwin.h"
// CClientMain 对话框

class CClientMain : public CDialog
{
	DECLARE_DYNAMIC(CClientMain)

public:
	CClientMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClientMain();


// 对话框数据
	enum { IDD = IDD_CIENT_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	CToolBar		m_MainToolBar;
	CAddIpDlg		m_dlgAddIP;
	CLoginDialog	m_cmbLogin;
	CServerListDlg	m_dlgServerList;
	CSetupDlg		m_dlgSetup;
	CDisplayDlg		m_dlgDisplay;
	CStatic			m_pctDisplay;
	bool			m_IsFullScreen;
	ScreenDisplay	m_ScreenDisplayer;
	int				m_Frame;
	UINT_PTR		m_nTimer;
	HostListConfig	m_HostListConfig;
	TCPClient		m_tcpClien;
	BOOL			m_AltCheck;
	BOOL			m_WinCheck;
	BOOL			m_CtrlCheck;
	BOOL			m_bTcpConect;
	BOOL			m_bCtrlPermission;
	//TcpClient*		m_pTcpClient;
	std::vector<Host>			m_vtHostList;
	std::queue<ByteArrayMsg*>	m_SendQueue;
	std::queue<ByteArrayMsg*>	m_RecvQueue;
	//测试使用
	ScreenShot		m_ScreenShooter;
	LocalMutex m_mLocaMutex;
	
	
	DECLARE_MESSAGE_MAP()
	/**
	   @brief:屏幕截图保存实际调用的函数
	   @Return:void
	*/
	void			OnScreenShot();
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnMove(int x, int y);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	//
	/**
	   @brief:工具栏按钮消息，弹出远程列表
	   @Return:void
	*/
	afx_msg void	OnBtnServerList();
	/**
	   @brief:工具栏按钮消息，弹出设置窗口
	   @Return:void
	*/
	afx_msg void	OnBtnSetup();
	/**
	   @brief:工具栏按钮消息，屏幕截图保存
	   @Return:void
	*/
	afx_msg void	OnBtnScreenShot();
	/**
	   @brief:工具栏按钮消息，全屏显示
	   @Return:void
	*/
	afx_msg void	OnBtnFullScreen();
	/**
	   @brief:工具栏按钮消息，按下工具栏上的alt键
	   @Return:void
	*/
	afx_msg void	OnBtnAlt();
	/**
	   @brief:工具栏按钮消息，按下工具栏上的Ctrl键
	   @Return:void
	*/
	afx_msg void	OnBtnCtrl();
   /**
	   @brief:工具栏按钮消息，按下工具栏上的winkey键
	   @Return:void
	*/
	afx_msg void	OnBtnWin();
	/**
	   @brief:工具栏按钮消息，将显示大小变为本地分辨率大小
	   @Return:void
	*/
	afx_msg void	OnBtnScaleLocalSize();
	/**
	   @brief:工具栏按钮消息，放大显示大小
	   @Return:void
	*/
	afx_msg void	OnBtnScaleUp();
	/**
	   @brief:工具栏按钮消息，缩小显示大小
	   @Return:void
	*/
	afx_msg void	OnBtnScaleDown();
	/**
	   @brief:工具栏按钮消息，给远程主机发送打开任务管理器消息
	   @Return:void
	*/
	afx_msg void	OnBtnTackMgr();
	/**
	   @brief:工具栏按钮消息，用于截屏和显示的定时器回调函数
	   @Parameter:UINT_PTR nIDEvent
	   @Return:void
	*/
	afx_msg void	OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnAddIpMessage(WPARAM wParam, LPARAM lParam);
public:
	/**
	   @brief:初始化Tcp链接，如果返回1表示有控制权限，0表示观看权限，小于0则是无法连接。
	   @Parameter:Host host
	   @Parameter:UserMsg * userMsg
	   @Return:int
	*/
	int InitTcpClien(Host host,UserMsg* userMsg);
		/**
	   @brief:设置每秒显示的帧数
	   @Parameter:int frame
	   @Return:bool
	*/
	bool SetFrame(int frame);
	/**
	   @brief:设置图像质量
	   @Parameter:int quality
	   @Return:bool
	*/
	bool SetImageQuality(int quality);
	/**
	   @brief:发送鼠标消息
	   @Parameter:int x
	   @Parameter:int y
	   @Parameter:int MouseStatus
	   @Return:void
	*/
	void SendMouseMsg(int x,int y,int MouseStatus);
	/**
	   @brief:发送键盘消息
	   @Parameter:int key
	   @Parameter:int status
	   @Return:void
	*/
	void SendKeyboardMsg(int key,int status);
	/**
	   @brief:设置分块块数，会发送改变分块消息给服务端
	   @Parameter:int Horz
	   @Parameter:int Vert
	   @Return:void
	*/
	void SetTileNumber(int Horz,int Vert);
	/**
	   @brief:结束全屏模式
	   @Return:bool
	*/
	bool EndFullScreen();
	/**
	   @brief:开启全屏模式
	   @Return:void
	*/
	void FullScreen();
	/**
	   @brief:返回当前是否是全屏模式
	   @Return:bool
	*/
	bool IsFullScreen();
	/**
	   @brief:处理接收的消息
	   @Return:void
	*/
	void DealMessage();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
public:
	afx_msg void OnDestroy();
};
