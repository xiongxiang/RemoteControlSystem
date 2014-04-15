// LoginDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "LoginDialog.h"
#include <atlconv.h>
#include "ClientMain.h"
#include "..\SocketIPv4\TCPClient.h"

// CLoginDialog 对话框

IMPLEMENT_DYNAMIC(CLoginDialog, CDialog)

CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
: CDialog(CLoginDialog::IDD, pParent)
{

}

CLoginDialog::~CLoginDialog()
{
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PASSWORD_EDIT, m_tbPassword);
	DDX_Control(pDX, IDC_USER_NAME_EDIT, m_tbUserName);
	DDX_Control(pDX, IDC_SERVER_COMBO, m_cmbServerList);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDialog::OnBnClickedButtonLogin)
	ON_CBN_SELCHANGE(IDC_SERVER_COMBO, &CLoginDialog::OnCbnSelchangeServerCombo)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CLoginDialog::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CLoginDialog 消息处理程序

void CLoginDialog::OnBnClickedButtonLogin()
{
	bool IsUserNameEmpty	= true;
	bool IsPassWordEmpty	= true;
	bool IsAccountTrue		= false;
	bool IsbHostEmpty		= true;
	memset(m_pHost,0,sizeof(Host));
	int nIndex = m_cmbServerList.GetCurSel();
	m_tbPassword.GetWindowText(m_szPassword);
	m_tbUserName.GetWindowText(m_szUserName);
	if (nIndex != -1 &&  nIndex != 0)
	{
		CString strCBText;
		m_cmbServerList.GetLBText( nIndex, strCBText);
		m_HostListConfig->ReadHostList(m_vtHostList);
		std::vector<Host>::iterator itHost;
		for(itHost = m_vtHostList.begin();itHost != m_vtHostList.end();++itHost)
		{
			CString szName = CString(itHost->name);
			if (szName == strCBText)
			{
				strcpy(m_pHost->name,itHost->name);
				strcpy(m_pHost->ip,itHost->ip);
				m_pHost->port = itHost->port;
			}
		}
		IsbHostEmpty = false;
	}
	else
	{
		IsbHostEmpty = true;
		return ;
	}
	if (m_szPassword.IsEmpty())
	{
		MessageBox(_T("密码不能为空"));
		IsPassWordEmpty = true;
		return ;
	}
	else
	{
		IsPassWordEmpty = false;
	}
	if (m_szUserName.IsEmpty())
	{
		MessageBox(_T("用户名不能为空！"));
		IsUserNameEmpty  = true;
		return ;
	}
	else
	{
		IsUserNameEmpty = false;
	}

	UserMsg* accountMsg = new UserMsg;
	USES_CONVERSION;
	accountMsg->PacketMsg(W2A(m_szUserName.GetBuffer()),W2A(m_szPassword.GetBuffer()));
	
	int loginResult = ((CClientMain*)GetParent())->InitTcpClien(*m_pHost,accountMsg);
	if (loginResult == 0 || loginResult == 1)
	{
		IsAccountTrue = true;
	}
	else if (loginResult == -1)
	{
		MessageBox(_T("用户名或密码错误！"));
		IsAccountTrue = false;
	}
	else if(loginResult == FORBIDDENIP)
	{
		MessageBox(_T("ip被禁用"));
		IsAccountTrue = false;
	}
	else
	{
		MessageBox(_T("连接错误，请确认服务端是否开启，以及您的网络状况！"));
		IsAccountTrue = false;
	}
	if ((!IsUserNameEmpty)&& (!IsPassWordEmpty)&&(!IsbHostEmpty)&&IsAccountTrue)
	{
		EndDialog(IDC_BUTTON_LOGIN);
	}
	else
	{
		//delete accountMsg;
	}
	//EndDialog(IDC_BUTTON_LOGIN);
}

void CLoginDialog::OnCbnSelchangeServerCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_cmbServerList.GetCurSel();
	CString strCBText;
	CString strAdd = CString("...添加...");
	m_cmbServerList.GetLBText( nIndex, strCBText);
	if (strCBText == strAdd)
	{
		m_cmbServerList.SetCurSel(m_dlgAddIP.DoModal());
		//m_dlgAddIP.DoModal();
	}

}

void CLoginDialog::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(IDC_BUTTON_EXIT);
}

void CLoginDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnBnClickedButtonLogin();
	//CDialog::OnOK();
}

void CLoginDialog::Init( HostListConfig* pHostListConfig,Host* pHost)
{

	m_HostListConfig = pHostListConfig;
	m_dlgAddIP.SetHostList(m_HostListConfig);
	m_pHost = pHost;
}

BOOL CLoginDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_HostListConfig->ReadHostList(m_vtHostList);
	std::vector<Host>::iterator itHost;
	for(itHost = m_vtHostList.begin();itHost != m_vtHostList.end();++itHost)
	{
		CString name = CString(itHost->name);
		m_cmbServerList.AddString((LPCTSTR)name);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

CString CLoginDialog::GetUserName()
{
	return m_szUserName;
}

CString CLoginDialog::GetPassword()
{
	return m_szPassword;
}
