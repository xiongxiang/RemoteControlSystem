// AddIpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "AddIpDlg.h"
#include <atlconv.h>
#include "LoginDialog.h"

// CAddIpDlg 对话框

IMPLEMENT_DYNAMIC(CAddIpDlg, CDialog)

CAddIpDlg::CAddIpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddIpDlg::IDD, pParent)
{

}

CAddIpDlg::~CAddIpDlg()
{
}

void CAddIpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_HOST, m_HostIP);
	DDX_Control(pDX, IDC_EDIT_HOST_NAME, m_tbHostName);
	DDX_Control(pDX, IDC_EDIT_HOST_PORT, m_tbPort);
}

void CAddIpDlg::SetHostList(HostListConfig* hostListConfig)
{
	m_HostListConfig = hostListConfig;
}

BEGIN_MESSAGE_MAP(CAddIpDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddIpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddIpDlg 消息处理程序

void CAddIpDlg::OnBnClickedOk()
{
	Host tempHost;

	DWORD dwAddress;
	BYTE nField[4];
	int  port;
	int  nIndex = 0;
	char ip[] = "000.000.000.000";
	char name[32] = "\0";
	char cPort[6] = "\0";
	CString csName;
	CString csPort;
	m_tbHostName.GetWindowText(csName);
	m_tbPort.GetWindowText(csPort);
	
	if (!csName.IsEmpty()	&& 
		!csPort.IsEmpty()	&&
		m_HostIP.GetAddress(nField[0],nField[1],nField[2],nField[3])
		)

	{
		WideCharToMultiByte(CP_ACP,0,csName.GetString(),-1,name,32,NULL,NULL);
		strcpy(tempHost.name,name);
		wcstombs(cPort,csPort.GetString(),csPort.GetLength());
		tempHost.port = atoi(cPort);
		int  count = 0;
		sprintf_s(tempHost.ip,sizeof(tempHost.ip),"%d.%d.%d.%d",nField[0],nField[1],nField[2],nField[3]);
		//strcpy(tempHost.ip,ip);	
		m_HostListConfig->AddHost(tempHost);
		nIndex = ((CLoginDialog*)GetParent())->m_cmbServerList.AddString(csName.GetString());
		//m_szHostName = csName;
		//::SendMessage(HWND_BROADCAST,WM_ADDIP,0,0);
	}
	EndDialog(nIndex);
	//EndDialog(0);
}

CString CAddIpDlg::GetAddName()
{
	return m_szHostName;
}
