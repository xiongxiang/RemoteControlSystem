// ServerListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ServerListDlg.h"
#include <math.h>

// CServerListDlg 对话框

IMPLEMENT_DYNAMIC(CServerListDlg, CDialog)

CServerListDlg::CServerListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerListDlg::IDD, pParent)
{
	m_Status =SL_HIDE;
	m_HostListConfig = NULL;
}

CServerListDlg::~CServerListDlg()
{
}

void CServerListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST_SERVER_LIST, m_lstServer);
}


BEGIN_MESSAGE_MAP(CServerListDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_EXITSIZEMOVE()
	ON_COMMAND(ID_BUTTON_SL_DELETE,&CServerListDlg::OnBtnDelete)
	
END_MESSAGE_MAP()

// CServerListDlg 消息处理程序

void CServerListDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	
	// TODO: 在此处添加消息处理程序代码
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	CWnd* pLstServer = GetDlgItem(IDC_LIST_SERVER_LIST);
	
	if (pLstServer != NULL)
	{
		RECT rcList;
	    GetWindowRect(&rcList);
	    rcList.bottom -= (60+rcList.top ) ;  
	    rcList.right       -= (10+rcList.left);
		rcList.top        =10;
		rcList.left       = 5;
	    pLstServer->MoveWindow(&rcList);
	}
	
}

void CServerListDlg::OnExitSizeMove()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnExitSizeMove();
	CWnd* pParent = GetParent();
	RECT rcClient;
		RECT rcServerList;
	GetWindowRect(&rcServerList);
	pParent->GetWindowRect(&rcClient);

	if (abs(rcServerList.top - rcClient.top) < 100 && abs(rcServerList.left - rcClient.right) <100 )
	{
		//DockWindow();
		SetStatus(SL_DOCK_WINDOW);
	}
	/*else if (m_Status == SL_UNDOCK )
	{
		RECT rcScreen;
		
		if (rcServerList.right > )
		{
		} 
		else
		{
		}
	}*/
	else
	{
		SetStatus(SL_UNDOCK);
	}
}

bool CServerListDlg::SetStatus( int status )
{
	m_Status = status;
	std::vector<Host>::iterator itHost;
    switch (m_Status)
    {
    case SL_DOCK_WINDOW:
		ShowWindow(SW_SHOW);
		DockWindow();
		return true;
    	break;
	case SL_HIDE:
		ShowWindow(SW_HIDE);
		return true;
		break;
	case SL_DOCK_SCREEN:
		ShowWindow(SW_SHOW);
		return true;
		break;
	default:
		return false;
		break;
    }

}

int CServerListDlg::GetStatus()
{
	return m_Status;
}

void CServerListDlg::DockWindow()
{
	CWnd* pParent = GetParent();
	RECT rcClient;
	RECT rcServerList;
	GetWindowRect(&rcServerList);

	pParent->GetWindowRect(&rcClient);
	if (m_Status == SL_DOCK_WINDOW)
	{
		rcServerList.top = rcClient.top;
		rcServerList.bottom = rcClient.bottom;
		rcServerList.right = rcClient.right + rcServerList.right - rcServerList.left;
		rcServerList.left   = rcClient.right;

		MoveWindow(&rcServerList,TRUE);
	}
}

void CServerListDlg::SetHostList( HostListConfig* hostListConfig )
{
	m_HostListConfig = hostListConfig;
}

bool CServerListDlg::Init( HostListConfig* hostListConfig )
{
	SetHostList(hostListConfig);
	m_HostListConfig->ReadHostList(m_vtHostList);
	std::vector<Host>::iterator itHost;
	for(itHost = m_vtHostList.begin();itHost != m_vtHostList.end();++itHost)
	{
		CString name = CString(itHost->name);
		//((CListBox*)GetDlgItem(IDC_LIST_SERVER_LIST))->AddString((LPCTSTR)name);
		m_lstServer.AddString((LPCTSTR)name);
	}
	return true;
}

BOOL CServerListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	RECT rcThis;
	GetWindowRect(&rcThis);
	rcThis.bottom -= 30;
	rcThis.left+=5;
	rcThis.right -=10;
	m_lstServer.Create(LBS_HASSTRINGS|WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_BORDER,rcThis,this,IDC_LIST_SERVER_LIST);
	//m_lstServer.CreateEx(WS_EX_CLIENTEDGE,NULL,NULL,LBS_HASSTRINGS|WS_CHILD|WS_VISIBLE|WS_VSCROLL,rcThis,this,IDC_LIST_SERVER_LIST);
	m_toolbar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_ALIGN_BOTTOM|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_toolbar.LoadToolBar(IDR_TOOLBAR2);
	m_toolbar.GetToolBarCtrl().SetBitmapSize(CSize(16,16));
	m_toolbar.GetToolBarCtrl().SetButtonSize(CSize(22,22));
	
		
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CServerListDlg::OnBtnDelete()
{

}
