// TabAccountDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteCtrolSystemServer.h"
#include "TabAccountDlg.h"

#include "AddUserDlg.h"
#include "UserFile.h"

#include <vector>


// TabAccountDlg 对话框

IMPLEMENT_DYNAMIC(TabAccountDlg, CDialog)

TabAccountDlg::TabAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TabAccountDlg::IDD, pParent)
{

}

TabAccountDlg::~TabAccountDlg()
{
}

void TabAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UERS_LIST, m_listUsers);
}


BEGIN_MESSAGE_MAP(TabAccountDlg, CDialog)	
	ON_BN_CLICKED(IDC_BTN_ADD, &TabAccountDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &TabAccountDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DELETE, &TabAccountDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// TabAccountDlg 消息处理程序

BOOL TabAccountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_listUsers.SetExtendedStyle(m_listUsers.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	LVCOLUMN lvcol;
	lvcol.mask = LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_CENTER;
	lvcol.pszText = L"登录名";
	lvcol.iSubItem = 1;  //与表列相关的子表项索引号
	lvcol.cx = 120;

	m_listUsers.InsertColumn(0,&lvcol);
	lvcol.pszText = L"密码";
	m_listUsers.InsertColumn(1,&lvcol);
	lvcol.cx = 84;
	lvcol.pszText = L"权限";
	m_listUsers.InsertColumn(2,&lvcol);

	UpdateListData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void TabAccountDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddUserDlg userDlg;
	userDlg.DoModal();
	UpdateListData();
}

void TabAccountDlg::UpdateListData(void)
{
	;
	CUserFile fileOp;
	std::vector<UserData> userLists =fileOp.GetAllUsers();

	//TRACE(_T("\n用户的数量：%d"),userLists.size());
	/*CString temp;
	temp.Format(_T("\n用户的数量：%d"),userLists.size());
	MessageBox(temp);*/

	m_listUsers.DeleteAllItems();
	std::vector<UserData>::iterator theIter;
	for (theIter = userLists.begin();theIter!=userLists.end();theIter++)
	{
		if (theIter->power!= -1)
		{
			m_listUsers.InsertItem(0,_T(""));
			m_listUsers.SetItemText(0,0,theIter->name);
			//m_listUsers.SetItemText(0,1,theIter->pwd);
			m_listUsers.SetItemText(0,1,_T("***"));
			if (theIter->power == 0)
			{
				m_listUsers.SetItemText(0,2,_T("观看"));
			}
			if (theIter->power == 1)
			{
				m_listUsers.SetItemText(0,2,_T("控制"));
			}
		}
		
	}
}

void TabAccountDlg::OnBnClickedBtnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_listUsers.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		TRACE(_T("No item were selected!\n"));
		AfxMessageBox(_T("请选择要编辑的行！"));
	}
	else
	{
		
		int nItem = m_listUsers.GetNextSelectedItem(pos);
		TCHAR szBuff[1024];
		LVITEM lvi;
		lvi.iItem = nItem;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuff;
		lvi.cchTextMax = 1024;
		m_listUsers.GetItem(&lvi);

		UserData user;
		lstrcpy(user.name,lvi.pszText);

		lvi.iSubItem = 1;
		m_listUsers.GetItem(&lvi);
		lstrcpy(user.pwd,lvi.pszText);

		lvi.iSubItem = 2;
		m_listUsers.GetItem(&lvi);
		if(lstrcmp(lvi.pszText,_T("观看")) == 0)
		{
			user.power = 0;
		}
		else
		{
			user.power = 1;
		}
		/*AfxMessageBox(user.name);
		AfxMessageBox(user.pwd);*/

		CAddUserDlg userDlg;
		userDlg.SetUserData(user);  //设置弹出界面的值
		userDlg.SetStats(userDlg.EDIT);
		userDlg.DoModal();  

		UpdateListData();
		
	}
}

void TabAccountDlg::OnBnClickedBtnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_listUsers.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		TRACE(_T("No item were selected!\n"));
		AfxMessageBox(_T("请选择要删除的行！"));
	}
	else
	{
		
		int nItem = m_listUsers.GetNextSelectedItem(pos);
		TCHAR szBuff[1024];
		LVITEM lvi;
		lvi.iItem = nItem;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuff;
		lvi.cchTextMax = 1024;
		m_listUsers.GetItem(&lvi);

		UserData user;
		lstrcpy(user.name,lvi.pszText);
		lvi.iSubItem = 1;
		m_listUsers.GetItem(&lvi);
		lstrcpy(user.pwd,lvi.pszText);
		CUserFile fileOp;
		fileOp.Delete(user);

		UpdateListData();
	}
}
