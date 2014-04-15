// TabServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteCtrolSystemServer.h"
#include "TabServerDlg.h"
#include "AddEditIpDlg.h"
#include "ChangeAdminPwd.h"
#include "Config.h"
#include "IpRuleFile.h"

#include <strsafe.h>


// TabServerDlg 对话框

IMPLEMENT_DYNAMIC(TabServerDlg, CDialog)

TabServerDlg::TabServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TabServerDlg::IDD, pParent)
	, m_iConnectPort(0)
{

}

TabServerDlg::~TabServerDlg()
{
}

void TabServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IP_LIST, m_list);
	DDX_Control(pDX, IDC_CB_PWDPROTED, m_cbPwdProtect);
	DDX_Text(pDX, IDC_TB_PORT, m_iConnectPort);
	DDX_Control(pDX, IDC_IP_TEST, m_testIp);
}


BEGIN_MESSAGE_MAP(TabServerDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADDIP, &TabServerDlg::OnBnClickedBtnAddip)
	ON_BN_CLICKED(IDC_CB_PWDPROTED, &TabServerDlg::OnBnClickedCbPwdproted)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &TabServerDlg::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_DELETEIP, &TabServerDlg::OnBnClickedBtnDeleteip)
	ON_BN_CLICKED(IDC_BTN_EDITIP, &TabServerDlg::OnBnClickedBtnEditip)
	ON_BN_CLICKED(IDC_BTN_MOVEUPIP, &TabServerDlg::OnBnClickedBtnMoveupip)
	ON_BN_CLICKED(IDC_BTN_MOVEDOWNIP, &TabServerDlg::OnBnClickedBtnMovedownip)
	ON_BN_CLICKED(IDC_BTN_TESTRULE, &TabServerDlg::OnBnClickedBtnTestrule)
END_MESSAGE_MAP()


// TabServerDlg 消息处理程序

void TabServerDlg::OnBnClickedBtnAddip()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddEditIpDlg addIp;
	addIp.DoModal();
	UpdateIpList();
}

BOOL TabServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	LVCOLUMN lvcol;
	lvcol.mask = LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_CENTER;
	lvcol.pszText = L"起始地址";
	lvcol.iSubItem = 1;  //与表列相关的子表项索引号
	lvcol.cx = 120;

	m_list.InsertColumn(0,&lvcol);
	lvcol.pszText = L"结束地址";
	m_list.InsertColumn(1,&lvcol);
	lvcol.pszText = L"动作";
	lvcol.cx = 70;
	m_list.InsertColumn(2,&lvcol);

	InitStats();

	UpdateIpList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void TabServerDlg::UpdateConfig(void)
{
	//CIniFile iniFile(_T("RemoteConfig.ini"));
	Config config;
	//允许远程控制
	if(BST_CHECKED == ((CButton *)GetDlgItem(IDC_CB_ALLOWCONTROL))->GetCheck())
	{
		config.SetIsAllowControl(TRUE);
		//iniFile.SetProfileInt(_T("sets"),_T("allowControl"),1);
	}
	else
	{
		//iniFile.SetProfileInt(_T("sets"),_T("allowControl"),0);
		config.SetIsAllowControl(FALSE);
	}

	//开机启动
	if(BST_CHECKED == ((CButton *)GetDlgItem(IDC_CB_STARTWINDOWS))->GetCheck())
	{
		config.SetIsAutoRun(TRUE);
		///*iniFile*/.SetProfileInt(_T("sets"),_T("autoRun"),1);
	}
	else
	{
		config.SetIsAutoRun(FALSE);
		//iniFile.SetProfileInt(_T("sets"),_T("autoRun"),0);
	}

	//托盘显示
	if(BST_CHECKED == ((CButton *)GetDlgItem(IDC_CB_SHOWTASK))->GetCheck())
	{
		config.SetIsShowInTask(TRUE);
		//iniFile.SetProfileInt(_T("sets"),_T("showTask"),1);
	}
	else
	{
		//iniFile.SetProfileInt(_T("sets"),_T("showTask"),0);
		config.SetIsShowInTask(FALSE);
	}

	//加密文件
	if(BST_CHECKED == ((CButton *)GetDlgItem(IDC_CB_CODEFILE))->GetCheck())
	{
		config.SetIsEncryptFile(TRUE);
		//iniFile.SetProfileInt(_T("sets"),_T("codingFile"),1);
	}
	else
	{
		config.SetIsEncryptFile(FALSE);
		//iniFile.SetProfileInt(_T("sets"),_T("codingFile"),0);
	}	

	//使用密码保护
	if(BST_CHECKED == ((CButton *)GetDlgItem(IDC_CB_PWDPROTED))->GetCheck())
	{
		config.SetIsUsePwdProtection(TRUE);
		//iniFile.SetProfileInt(_T("admin"),_T("usePwdProtect"),1);
	}
	else
	{
		config.SetIsUsePwdProtection(FALSE);
		//iniFile.SetProfileInt(_T("admin"),_T("usePwdProtect"),0);
	}

	UpdateData(TRUE); //更新变量的值
	config.SetConnectPort(m_iConnectPort);
	//iniFile.SetProfileInt(_T("connection"),_T("mainPort"),m_iConnectPort);
	 
	

}

void TabServerDlg::OnBnClickedCbPwdproted()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_cbPwdProtect.GetCheck() == BST_CHECKED)
	{
		((CButton *)GetDlgItem(IDC_BTN_CHANGE))->EnableWindow(TRUE);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_BTN_CHANGE))->EnableWindow(FALSE);
	}
	
}

void TabServerDlg::InitStats( void )
{
	CFileFind finder;
	CIniFile iniFile(_T("RemoteConfig.ini"));
	BOOL ifFind = finder.FindFile(iniFile.GetFileName());

	if(ifFind)
	{
		//远程控制
		if (iniFile.GetProfileInt(_T("sets"),_T("allowControl")) == 1)
		{
			((CButton *)GetDlgItem(IDC_CB_ALLOWCONTROL))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_CB_ALLOWCONTROL))->SetCheck(FALSE);
		}

		//开机启动
		if(1 == iniFile.GetProfileInt(_T("sets"),_T("autoRun")))
		{
			((CButton *)GetDlgItem(IDC_CB_STARTWINDOWS))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_CB_STARTWINDOWS))->SetCheck(FALSE);
		}

		//托盘显示
		if(1 == iniFile.GetProfileInt(_T("sets"),_T("showTask")))
		{
			((CButton *)GetDlgItem(IDC_CB_SHOWTASK))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_CB_SHOWTASK))->SetCheck(FALSE);
		}

		//加密文件
		if(1 == iniFile.GetProfileInt(_T("sets"),_T("codingFile")))
		{
			((CButton *)GetDlgItem(IDC_CB_CODEFILE))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_CB_CODEFILE))->SetCheck(FALSE);
		}

		//使用密码保护
		if(1 == iniFile.GetProfileInt(_T("admin"),_T("usePwdProtect")))
		{
			((CButton *)GetDlgItem(IDC_CB_PWDPROTED))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_CB_PWDPROTED))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_BTN_CHANGE))->EnableWindow(FALSE);
		}

		m_iConnectPort = iniFile.GetProfileInt(_T("connection"),_T("mainPort"));
		UpdateData(FALSE);
		
	}



}

void TabServerDlg::OnBnClickedBtnChange()
{
	// TODO: 在此添加控件通知处理程序代码
	CChangeAdminPwd changePwdDlg;
	changePwdDlg.DoModal();
}

void TabServerDlg::UpdateIpList(void)
{
	m_list.DeleteAllItems();
	CIpRuleFile ipFile;
	std::vector<IpRule> rules(ipFile.GetAllRules());	

	std::vector<IpRule>::iterator theIter;
	for (theIter = rules.begin();theIter!=rules.end();theIter++)
	{
		int nIndex = m_list.GetItemCount();
		LV_ITEM lvItem;
		lvItem.mask = LVIF_TEXT ; 
		lvItem.iItem = nIndex;     //行数
		lvItem.iSubItem = 0;
		lvItem.pszText = theIter->start;   //第一列
		//在最后一行插入记录值.
		m_list.InsertItem(&lvItem); 
		//插入其它列
		m_list.SetItemText(nIndex,1,theIter->end);
		if (theIter->power == 0)
		{
			m_list.SetItemText(nIndex,2,_T("禁止"));
		}
		if (theIter->power== 1)
		{
			m_list.SetItemText(nIndex,2,_T("允许"));
		}
		
	}

}

void TabServerDlg::OnBnClickedBtnDeleteip()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		TRACE(_T("No item were selected!\n"));
		AfxMessageBox(_T("请选择要删除的行！"));
	}
	else
	{

		int nItem = m_list.GetNextSelectedItem(pos);
		TCHAR szBuff[1024];
		LVITEM lvi;
		lvi.iItem = nItem;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuff;
		lvi.cchTextMax = 1024;
		m_list.GetItem(&lvi);

		IpRule rule;
		lstrcpy(rule.start,lvi.pszText);
		lvi.iSubItem = 1;
		m_list.GetItem(&lvi);
		lstrcpy(rule.end,lvi.pszText);
		CIpRuleFile fileOp;
		fileOp.Delete(rule);

		UpdateIpList();
	}
}

void TabServerDlg::OnBnClickedBtnEditip()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		TRACE(_T("No item were selected!\n"));
		AfxMessageBox(_T("请选择要编辑的行！"));
	}
	else
	{
		
		int nItem = m_list.GetNextSelectedItem(pos);
		TCHAR szBuff[1024];
		LVITEM lvi;
		lvi.iItem = nItem;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuff;
		lvi.cchTextMax = 1024;
		m_list.GetItem(&lvi);

		IpRule rule;
		lstrcpy(rule.start,lvi.pszText);

		lvi.iSubItem = 1;
		m_list.GetItem(&lvi);
		lstrcpy(rule.end,lvi.pszText);

		lvi.iSubItem = 2;
		m_list.GetItem(&lvi);
		if(lstrcmp(lvi.pszText,_T("禁止")) == 0)
		{
			rule.power = 0;
		}
		else
		{
			rule.power = 1;
		}
		/*AfxMessageBox(user.name);
		AfxMessageBox(user.pwd);*/

		CAddEditIpDlg ipDlg;
		ipDlg.SetRule(rule);  //设置弹出界面的值
		ipDlg.SetStats(ipDlg.EDIT);
		ipDlg.DoModal();  
		UpdateIpList();
		
	}
}

void TabServerDlg::OnBnClickedBtnMoveupip()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos =  m_list.GetFirstSelectedItemPosition();
	int selectIndex= m_list.GetNextSelectedItem(pos);   //取得当前行号
	if (selectIndex>=1)
	{
		CIpRuleFile fileOp;
		fileOp.MoveUp(selectIndex);
		//m_list.SetItemPosition(selectIndex,pos - 1);
		UpdateIpList();
		--selectIndex;
	}
	m_list.SetItemState(selectIndex,LVIS_SELECTED,LVIS_SELECTED);
	m_list.EnsureVisible(selectIndex,FALSE);
	m_list.SetFocus();
}

void TabServerDlg::OnBnClickedBtnMovedownip()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos =  m_list.GetFirstSelectedItemPosition();
	int selectIndex= m_list.GetNextSelectedItem(pos);   //取得当前行号
	if (selectIndex < m_list.GetItemCount() - 1)
	{
		CIpRuleFile fileOp;
		fileOp.moveDown(selectIndex);
		UpdateIpList();
		++selectIndex ;
	}
	m_list.SetItemState(selectIndex,LVIS_SELECTED,LVIS_SELECTED);
	m_list.EnsureVisible(selectIndex,FALSE);
	m_list.SetFocus();

}

void TabServerDlg::OnBnClickedBtnTestrule()
{
	// TODO: 在此添加控件通知处理程序代码

	BYTE f0,f1,f2,f3;
	m_testIp.GetAddress(f0,f1,f2,f3);
	TCHAR ipTested[16];
	//CString ipAddrFirst ;
	//ipAddrFirst.Format(_T("%d.%d.%d.%d"),f0,f1,f2,f3);
	//MessageBox(ipAddrFirst);

	StringCbPrintf(ipTested,16*sizeof(TCHAR),_T("%d.%d.%d.%d"),f0,f1,f2,f3);
	CIpRuleFile fileOp;
	int relust = fileOp.GetPowerByIp(ipTested);
	if (relust == 1)
	{
		MessageBox(_T("该Ip地址被允许连接!"));
	}
	else
	{
		MessageBox(_T("该Ip地址被禁止连接!"));
	}
}
