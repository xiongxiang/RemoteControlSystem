// AddUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteCtrolSystemServer.h"
#include "AddUserDlg.h"

#include "UserFile.h"

// CAddUserDlg 对话框

IMPLEMENT_DYNAMIC(CAddUserDlg, CDialog)

CAddUserDlg::CAddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddUserDlg::IDD, pParent)
	, m_stats(0)
{
	lstrcpy(m_user.name,_T(""));
	lstrcpy(m_user.pwd,_T(""));	
	m_user.power = 0;
	m_stats = ADD;
}

CAddUserDlg::~CAddUserDlg()
{
}

void CAddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ET_NAME, m_editName);
}


BEGIN_MESSAGE_MAP(CAddUserDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CAddUserDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CAddUserDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CAddUserDlg 消息处理程序

BOOL CAddUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	SetDlgItemText(IDC_ET_NAME,m_user.name);
	SetDlgItemText(IDC_ET_PWD,m_user.pwd);
	if (m_user.power == 0)
	{
		((CButton *)GetDlgItem(IDC_RD_VIEW))->SetCheck(TRUE);
	}
	else if (m_user.power == 1)
	{
		((CButton *)GetDlgItem(IDC_RD_CONTROL))->SetCheck(TRUE);
	}
	if (m_stats == EDIT)
	{
		((CButton*)GetDlgItem(IDC_ET_NAME))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_ET_PWD))->EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddUserDlg::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (BST_CHECKED==((CButton *)GetDlgItem(IDC_RD_VIEW))->GetCheck()) //观看选择项被选择
	{
		m_user.power = 0;
		TRACE("是观看权限啦\n");
	}
	else  //控制选择项被选择
	{
		m_user.power = 1;
		TRACE("我可以控制哦\n");
	}
	
	if (GetDlgItemText(IDC_ET_NAME,m_user.name,20))
	{
		TRACE(_T("\n%s"),m_user.name);
	}
	if (GetDlgItemText(IDC_ET_PWD,m_user.pwd,15))
	{
		TRACE(_T("\n%s"),m_user.pwd);
	}

	CUserFile fileOp;
	if (m_stats == ADD)  //添加状态下
	{
		fileOp.Add(m_user);
	}
	else  //编辑状态下
	{
		fileOp.Update(m_user);
	}
	
	OnOK();
	//user.power =

}

void CAddUserDlg::OnBnClickedBtnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CAddUserDlg::SetUserData( UserData user )
{
	m_user = user;
}

void CAddUserDlg::SetStats( int stats )
{
	m_stats = stats;
}
