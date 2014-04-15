// RemoteCtrolSystemServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteCtrolSystemServer.h"
#include "RemoteCtrolSystemServerDlg.h"
#include "WndClassList.h"
#include "IniFile.h"
#include "Config.h"

#define WM_SHOWTASK (WM_USER + 101)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRemoteCtrolSystemServerDlg 对话框


CRemoteCtrolSystemServerDlg::CRemoteCtrolSystemServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteCtrolSystemServerDlg::IDD, pParent),m_bIsServerStarted(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
	{
		MessageBox(_T("Error at WSAStartup()\n"));
	}
}

void CRemoteCtrolSystemServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
	DDX_Control(pDX, IDC_BTN_STARTSERVER, m_btnStartServer);
}

BEGIN_MESSAGE_MAP(CRemoteCtrolSystemServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CRemoteCtrolSystemServerDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BTN_OK, &CRemoteCtrolSystemServerDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CRemoteCtrolSystemServerDlg::OnBnClickedBtnApply)
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_BN_CLICKED(IDC_BTN_STARTSERVER, &CRemoteCtrolSystemServerDlg::OnBnClickedBtnStartserver)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CRemoteCtrolSystemServerDlg 消息处理程序

BOOL CRemoteCtrolSystemServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	TCITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = L"服务";
	m_tabCtrl.InsertItem(0,&item);
	item.pszText = L"连接";
	m_tabCtrl.InsertItem(1,&item);
	item.pszText = L"账号管理";
	m_tabCtrl.InsertItem(2,&item);
	item.pszText = L"关于";
	m_tabCtrl.InsertItem(3,&item);

	//设置选项卡的内容的布局的大小
	CRect rc;
	m_tabCtrl.GetClientRect(&rc);
	rc.top+=30;
	rc.bottom-=8;
	rc.left+=8;
	rc.right -=8;

	//创建四个选项
	m_tsdServer.Create(IDD_TAB_SERVER,&m_tabCtrl);
	m_dlgConnection.Create(IDD_TAB_CONNECTION,&m_tabCtrl);
	m_dlgAcount.Create(IDD_TAB_ACCOUNT,&m_tabCtrl);
	m_dlgAbout.Create(IDD_TAB_ABOUT,&m_tabCtrl);

	m_tsdServer.MoveWindow(&rc);
	m_dlgConnection.MoveWindow(&rc);
	m_dlgAcount.MoveWindow(&rc);
	m_dlgAbout.MoveWindow(&rc);

	m_tsdServer.ShowWindow(SW_SHOW);
	m_dlgAcount.ShowWindow(SW_HIDE);
	m_dlgConnection.ShowWindow(SW_HIDE);
	m_dlgAbout.ShowWindow(SW_HIDE);

	WndClassList::m_connectDlg = &m_dlgConnection;
	//m_tsdServer.SetWindowPos(NULL,10,30,440,240,SWP_SHOWWINDOW);
	//m_tsdServer.ShowWindow(SW_SHOW);
	UpdateWindowControl();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRemoteCtrolSystemServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		/*CAboutDlg dlgAbout;
		dlgAbout.DoModal();*/
	} else if(nID == SC_MINIMIZE)
	{
		CIniFile fileOp(_T("RemoteConfig.ini"));
		if (fileOp.GetProfileInt(_T("sets"),_T("showTask")) == 1)
		{
			AddToTray();
		}
		else
		{
			CDialog::OnSysCommand(nID,lParam);
		}
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRemoteCtrolSystemServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRemoteCtrolSystemServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//选项卡切换处理
void CRemoteCtrolSystemServerDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	switch(m_tabCtrl.GetCurSel())
	{
	case 0:
		{
			m_tsdServer.ShowWindow(SW_SHOW);
			m_dlgConnection.ShowWindow(SW_HIDE);
			m_dlgAcount.ShowWindow(SW_HIDE);
			m_dlgAbout.ShowWindow(SW_HIDE);
			break;
		}
	case 1:
		{
			m_tsdServer.ShowWindow(SW_HIDE);
			m_dlgConnection.ShowWindow(SW_SHOW);
			m_dlgAcount.ShowWindow(SW_HIDE);
			m_dlgAbout.ShowWindow(SW_HIDE);
			break;
		}
	case 2:
		{
			m_tsdServer.ShowWindow(SW_HIDE);
			m_dlgConnection.ShowWindow(SW_HIDE);
			m_dlgAcount.ShowWindow(SW_SHOW);
			m_dlgAbout.ShowWindow(SW_HIDE);
			break;
		}
	case 3:
		m_tsdServer.ShowWindow(SW_HIDE);
		m_dlgConnection.ShowWindow(SW_HIDE);
		m_dlgAcount.ShowWindow(SW_HIDE);
		m_dlgAbout.ShowWindow(SW_SHOW);
		{
			break;
		}
	default:
		break;
	}
	*pResult = 0;
}

void CRemoteCtrolSystemServerDlg::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// 在这里保存配置信息
	m_tsdServer.UpdateConfig();
}

void CRemoteCtrolSystemServerDlg::SetAutoRun(BOOL bAutoRun)
{
	HKEY hKey;
	//注册表路径
	CString strRegPath = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	TCHAR* lpszAppKeyName = _T("RemoteControlServer");
	//获取工程文件完整文件名
	TCHAR m_szAppPath[MAX_PATH];
	DWORD cch = GetModuleFileName(NULL,m_szAppPath,MAX_PATH);
	ASSERT(cch!=0);

	//打开注册表
	if (ERROR_SUCCESS ==RegOpenKeyEx(HKEY_LOCAL_MACHINE,strRegPath,0,KEY_ALL_ACCESS,&hKey))
	{
		if (bAutoRun) //根据条件添加或删除注册表项
		{
			RegSetValueEx(hKey,lpszAppKeyName,0,REG_SZ,(const unsigned char *)m_szAppPath,sizeof(m_szAppPath));
		}
		else
		{
			RegDeleteValue(hKey,lpszAppKeyName);
		}
	}
	RegCloseKey(hKey);
	

}

void CRemoteCtrolSystemServerDlg::OnBnClickedBtnApply()
{
	// TODO: 在此添加控件通知处理程序代码
	m_tsdServer.UpdateConfig();
	this->UpdateWindowControl();
}

LRESULT CRemoteCtrolSystemServerDlg::OnShowTask( WPARAM wParam, LPARAM lParam )
{
	if(wParam != IDR_MAINFRAME)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:                                        // 右键起来时弹出菜单
		{

			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // 得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();                    // 声明一个弹出式菜单
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭"));
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
		{
			this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口
			DeleteFromTray();
		}
		break;
	}
	return 0;
}

void CRemoteCtrolSystemServerDlg::AddToTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	lstrcpy(nid.szTip,_T("计算机远程控制——服务端"));
	Shell_NotifyIcon(NIM_ADD,&nid);
	ShowWindow(SW_HIDE);
}

void CRemoteCtrolSystemServerDlg::DeleteFromTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));		
	Shell_NotifyIcon(NIM_DELETE,&nid);
}

void CRemoteCtrolSystemServerDlg::OnBnClickedBtnStartserver()
{
	// TODO: 在此添加控件通知处理程序代码
	//在这里的是启动服务的相关代码	
	if (m_bIsServerStarted)
	{
		m_threadServer.Stop();  //停止TCP服务
		WndClassList::m_connectDlg->LoginOutAllUser();
		MessageBox(_T("服务已停止"));
		((CButton*)GetDlgItem(IDC_BTN_STARTSERVER))->SetWindowText(_T("启动服务"));
		m_bIsServerStarted = FALSE;
	}
	else
	{
		Config config;
		int serverPort =config.GetConnectPort();
		m_threadServer.Start(servicFactory,serverPort);
		WndClassList::m_watcher = new SystemMonitor;
		MessageBox(_T("服务启动成功"));
		((CButton*)GetDlgItem(IDC_BTN_STARTSERVER))->SetWindowText(_T("停止服务"));
		m_bIsServerStarted = TRUE;
	}
	
}

void CRemoteCtrolSystemServerDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//AfxMessageBox(_T("aaaaaaaaaaa"));
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRemoteCtrolSystemServerDlg::UpdateWindowControl()
{
	Config config;
	if (config.GetIsAllowControl())
	{
		((CButton* )GetDlgItem(IDC_BTN_STARTSERVER))->EnableWindow(TRUE);
	}
	else
	{
        ((CButton* )GetDlgItem(IDC_BTN_STARTSERVER))->EnableWindow(FALSE);
	}

	//判断是否允许开机启动
	if (config.GetIsAutoRun())
	{
		SetAutoRun(TRUE);
	}
	else
	{
		SetAutoRun(FALSE);
	}

	if (config.GetIsEncryptFile())
	{
	
		
		OFSTRUCT ofn;
		if(OpenFile("user.crypt",&ofn,OF_EXIST)==HFILE_ERROR)
		{
			//若不存在
			AES aes;
			char* key = "RemoteCtrolSystem";
			aes.set_key((u1byte*)key,256);
			aes.encrypt(_T("user"));
		}
		if(OpenFile("user.plain",&ofn,OF_EXIST)!=HFILE_ERROR)
		{
			//若存在
			OpenFile("user.plain",&ofn,OF_DELETE);
			//DeleteFile(_T("user.plain"));
		}
	
	}
	else  //配置文件显示，不加密文件
	{

		OFSTRUCT ofn;
		if(OpenFile("user.plain",&ofn,OF_EXIST)==HFILE_ERROR) //打开你又关闭失败，说明文件不存在
		{
			//若不存在
			AES aes;
			char* key = "RemoteCtrolSystem";
			aes.set_key((u1byte*)key,256);
			aes.decrypt(_T("user"));
		}
		if(OpenFile("user.crypt",&ofn,OF_EXIST)!=HFILE_ERROR)
		{
			//若存在
			OpenFile("user.crypt",&ofn,OF_DELETE);
			//DeleteFile(_T("user.crypt"));
		}

	}

}
