// EnterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EnterDlg.h"
#include "IniFile.h"
#include "RemoteCtrolSystemServerDlg.h"
#include "RemoteCtrolSystemServer.h"

// CEnterDlg 对话框

IMPLEMENT_DYNAMIC(CEnterDlg, CDialog)

CEnterDlg::CEnterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterDlg::IDD, pParent)
{

}

CEnterDlg::~CEnterDlg()
{
}

void CEnterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ET_PWD, m_enterPwd);
}


BEGIN_MESSAGE_MAP(CEnterDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CEnterDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CEnterDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CEnterDlg 消息处理程序

void CEnterDlg::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString enterPwd,pwdInFile;
	m_enterPwd.GetWindowText(enterPwd);
	CIniFile conFile(_T("RemoteConfig.ini"));
	conFile.GetProfileString(_T("admin"),_T("adminPwd"),pwdInFile);
	if (enterPwd.Compare(pwdInFile) == 0)
	{
		OnOK();
		CRemoteCtrolSystemServerDlg dlg;
		((CRemoteCtrolSystemServerApp *)AfxGetApp())->m_pMainWnd = &dlg; //重新设置系统的主界面
		dlg.DoModal();
	}
	else
	{
		MessageBox(_T("密码错误！"));
	}
}

void CEnterDlg::OnBnClickedBtnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
