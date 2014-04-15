// ChangeAdminPwd.cpp : 实现文件
//

#include "stdafx.h"
#include "ChangeAdminPwd.h"
#include "Config.h"


// CChangeAdminPwd 对话框

IMPLEMENT_DYNAMIC(CChangeAdminPwd, CDialog)

CChangeAdminPwd::CChangeAdminPwd(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeAdminPwd::IDD, pParent)
	, m_strNewPwd(_T(""))
	, m_strSurePwd(_T(""))
{

}

CChangeAdminPwd::~CChangeAdminPwd()
{
}

void CChangeAdminPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_NEWPWD, m_strNewPwd);
	DDX_Text(pDX, IDC_ED_NEWPWD2, m_strSurePwd);
}


BEGIN_MESSAGE_MAP(CChangeAdminPwd, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEWPWDOK, &CChangeAdminPwd::OnBnClickedBtnNewpwdok)
	ON_BN_CLICKED(IDC_BTN_NEWPWDCANCEL, &CChangeAdminPwd::OnBnClickedBtnNewpwdcancel)
END_MESSAGE_MAP()


// CChangeAdminPwd 消息处理程序

void CChangeAdminPwd::OnBnClickedBtnNewpwdok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Config config;
	if (m_strNewPwd==m_strSurePwd)
	{
		config.SetAdminLoginPwd(m_strSurePwd);  //把新密码写入配置文件中
		//iniFile.SetProfileString(_T("admin"),_T("adminPwd"),m_strNewPwd);
		OnOK();
	}
	else
	{
		AfxMessageBox(_T("两次密码输入不一致，请查证后再提交！"));
	}	
}

void CChangeAdminPwd::OnBnClickedBtnNewpwdcancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
