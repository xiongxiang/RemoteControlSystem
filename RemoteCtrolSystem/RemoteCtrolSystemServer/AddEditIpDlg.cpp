// AddEditIpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteCtrolSystemServer.h"
#include "AddEditIpDlg.h"
#include "IpRuleFile.h"

#include <strsafe.h>


// CAddEditIpDlg 对话框

IMPLEMENT_DYNAMIC(CAddEditIpDlg, CDialog)

CAddEditIpDlg::CAddEditIpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddEditIpDlg::IDD, pParent)
	, m_stats(0)
{

	lstrcpy(m_rule.start,_T(""));
	lstrcpy(m_rule.end,_T(""));	
	m_rule.power = 0;
	m_stats = ADD;
}

CAddEditIpDlg::~CAddEditIpDlg()
{
}

void CAddEditIpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IP_START, m_ipStart);
	DDX_Control(pDX, IDC_IP_END, m_ipEnd);
}


BEGIN_MESSAGE_MAP(CAddEditIpDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CAddEditIpDlg::OnBnClickedBtnOk)
END_MESSAGE_MAP()


// CAddEditIpDlg 消息处理程序



BOOL CAddEditIpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*((CButton *)GetDlgItem(IDC_RD_REJECT))->SetCheck(TRUE);
	SetDlgItemText(IDC_ET_NAME,m_user.name);
	SetDlgItemText(IDC_ET_PWD,m_user.pwd);*/

	m_ipStart.SetWindowText(m_rule.start);
	m_ipEnd.SetWindowText(m_rule.end);
	if (m_rule.power == 0)  //规则表示禁止
	{
		((CButton *)GetDlgItem(IDC_RD_REJECT))->SetCheck(TRUE);
	}
	else if (m_rule.power == 1)  //规则表示允许
	{
		((CButton *)GetDlgItem(IDC_RD_ALLOW))->SetCheck(TRUE);
	}

	if (m_stats == EDIT)  //若界面处于编辑状态
	{
		m_ipStart.EnableWindow(FALSE);
		m_ipEnd.EnableWindow (FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddEditIpDlg::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码	
	BYTE f0,f1,f2,f3;
	m_ipStart.GetAddress(f0,f1,f2,f3);
	//CString ipAddrFirst ;
	//ipAddrFirst.Format(_T("%d.%d.%d.%d"),f0,f1,f2,f3);
	//MessageBox(ipAddrFirst);

	StringCbPrintf(m_rule.start,16*sizeof(TCHAR),_T("%d.%d.%d.%d"),f0,f1,f2,f3);
	m_ipEnd.GetAddress(f0,f1,f2,f3);
	if(f0 ==0 && f1 ==0 && f2 ==0 &&f3 ==0) //若终止IP控件内容为空，表示只针对具体某一IP地址
	{
		lstrcpy(m_rule.end,m_rule.start);
	}
	else
	{
		StringCbPrintf(m_rule.end,16*sizeof(TCHAR),_T("%d.%d.%d.%d"),f0,f1,f2,f3);
	}
	
	CIpRuleFile ipFile;
	if(ipFile.CompareIpAddress(m_rule.start,m_rule.end)>0)
	{
		MessageBox(_T("终止IP地址，不能小于起始IP地址！"));
		return ;
	}
	if (BST_CHECKED==((CButton *)GetDlgItem(IDC_RD_REJECT))->GetCheck())
	{
		m_rule.power = 0;
		TRACE("是拒绝权限啦\n");
	}
	else
	{
		m_rule.power = 1;
		TRACE("允许远程控制哦\n");
	}
	
	
	if (m_stats == ADD)  //若为添加状态
	{
		ipFile.Add(m_rule);
	}
	else  //若为编辑状态
	{
		ipFile.Update(m_rule);
	}
	CDialog::OnOK();
}

void CAddEditIpDlg::SetStats( int stats )
{
	this->m_stats = stats;
}

void CAddEditIpDlg::SetRule(IpRule rule )
{
	m_rule = rule;
}

