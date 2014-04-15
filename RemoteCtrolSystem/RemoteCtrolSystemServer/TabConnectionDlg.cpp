// TabConnectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TabConnectionDlg.h"
#include "RemoteCtrolSystemServer.h"


// TabConnectionDlg 对话框

IMPLEMENT_DYNAMIC(TabConnectionDlg, CDialog)

TabConnectionDlg::TabConnectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TabConnectionDlg::IDD, pParent)
{

}

TabConnectionDlg::~TabConnectionDlg()
{
}

void TabConnectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONCETION_LIST, m_listConnection);
}


BEGIN_MESSAGE_MAP(TabConnectionDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_BROKEN, &TabConnectionDlg::OnBnClickedBtnBroken)
	ON_BN_CLICKED(IDC_BT_OPERATOR, &TabConnectionDlg::OnBnClickedBtOperator)
END_MESSAGE_MAP()


// TabConnectionDlg 消息处理程序

BOOL TabConnectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_listConnection.SetExtendedStyle(m_listConnection.GetExtendedStyle()| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	LVCOLUMN lvcol;
	lvcol.mask = LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_CENTER;
	lvcol.pszText = L"登录名";
	lvcol.iSubItem = 1;  //与表列相关的子表项索引号
	lvcol.cx = 120;

	m_listConnection.InsertColumn(0,&lvcol);
	lvcol.pszText = L"IP地址";
	m_listConnection.InsertColumn(1,&lvcol);
	lvcol.cx = 70;
	lvcol.pszText = L"权限";
	m_listConnection.InsertColumn(2,&lvcol);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void TabConnectionDlg::AddConnection( ConnectionData data )
{
	m_ConnectionData.push_back(data);
}

void TabConnectionDlg::UpdateList()
{
	m_listConnection.DeleteAllItems();
	std::vector<ConnectionData>::iterator iter;
	for (iter = m_ConnectionData.begin();iter!=m_ConnectionData.end();iter++)
	{
		int nIndex = m_listConnection.GetItemCount();
		LV_ITEM lvItem;
		lvItem.mask = LVIF_TEXT ; 
		lvItem.iItem = nIndex;     //行数
		lvItem.iSubItem = 0;
		lvItem.pszText = _T("");
		//在最后一行插入记录值.
		m_listConnection.InsertItem(&lvItem); 
		m_listConnection.SetItemText(nIndex,0,iter->username);
		//插入其它列
		m_listConnection.SetItemText(nIndex,1,iter->ip);
		if (iter->status == 0)
		{
			m_listConnection.SetItemText(nIndex,2,_T("观看"));
		}
		else
		{
			m_listConnection.SetItemText(nIndex,2,_T("控制"));
		}
	}
}

BOOL TabConnectionDlg::IsUserLogined(CString name)
{
	std::vector<ConnectionData>::iterator iter;
	for (iter = m_ConnectionData.begin();iter!=m_ConnectionData.end();iter++)
	{
		if(iter->username == name)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void TabConnectionDlg::OnBnClickedBtnBroken()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_listConnection.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		TRACE(_T("No item were selected!\n"));
		AfxMessageBox(_T("请选择要断开连接的行！"));
	}
	else
	{

		int nItem = m_listConnection.GetNextSelectedItem(pos);
		m_ConnectionData[nItem].connection->disconnect();
		std::vector<ConnectionData>::iterator iter = m_ConnectionData.begin();
		m_ConnectionData.erase(iter+nItem);
		this->UpdateList();
	}
}

void TabConnectionDlg::DeleteItemByConnection( TCPConnection *connection )
{
	std::vector<ConnectionData>::iterator iter;
	for (iter = m_ConnectionData.begin();iter!=m_ConnectionData.end();iter++)
	{
		if(iter->connection == connection)
		{
			m_ConnectionData.erase(iter);
			this->UpdateList();
			return ;
		}
	}
	
}

void TabConnectionDlg::LoginOutAllUser()
{
	std::vector<ConnectionData>::iterator iter;
	for (iter = m_ConnectionData.begin();iter!=m_ConnectionData.end();iter++)
	{
		iter->connection->disconnect();
	}
	m_ConnectionData.clear();
	this->UpdateList();
}

void TabConnectionDlg::OnBnClickedBtOperator()
{
	// TODO: 在此添加控件通知处理程序代码
	COperationDlg operation;
	POSITION pos = m_listConnection.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		/*TRACE(_T("No item were selected!\n"));
		AfxMessageBox(_T("请选择要断开连接的行！"));*/
		operation.DoModal();
	}
	else
	{
		int nItem = m_listConnection.GetNextSelectedItem(pos);
		TCHAR szBuff[1024];
		LVITEM lvi;
		lvi.iItem = nItem;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuff;
		lvi.cchTextMax = 1024;
		m_listConnection.GetItem(&lvi);

		TCHAR name[20];
		lstrcpy(name,lvi.pszText);
		operation.SetNameAndType(CString(name),0);
		operation.DoModal();
	}
	
}
