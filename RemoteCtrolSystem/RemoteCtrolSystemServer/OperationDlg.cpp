// OperationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OperationDlg.h"
#include "OperationNotes.h"
#include "UserFile.h"


// COperationDlg 对话框

IMPLEMENT_DYNAMIC(COperationDlg, CDialog)

COperationDlg::COperationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COperationDlg::IDD, pParent) ,m_iType(0),m_strName(_T(""))
{

}

COperationDlg::~COperationDlg()
{
}

void COperationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HISTORY, m_list);
	DDX_Control(pDX, IDC_CB_USER, m_cbNames);
	DDX_Control(pDX, IDC_CB_TYPE, m_cbTypes);
}


BEGIN_MESSAGE_MAP(COperationDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CLEARLOG, &COperationDlg::OnBnClickedBtnClearlog)
	ON_CBN_SELCHANGE(IDC_CB_USER, &COperationDlg::OnCbnSelchangeCbUser)
	ON_CBN_SELCHANGE(IDC_CB_TYPE, &COperationDlg::OnCbnSelchangeCbType)
	ON_BN_CLICKED(IDC_BTN_FLASH, &COperationDlg::OnBnClickedBtnFlash)
END_MESSAGE_MAP()


// COperationDlg 消息处理程序

BOOL COperationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CUserFile userfile;
	std::vector<UserData> users = userfile.GetAllUsers();
	std::vector<UserData>::iterator iter;
	for (iter = users.begin();iter!=users.end();iter++)
	{
		m_cbNames.AddString(CString(iter->name));
	}
	
	if (m_strName == _T(""))
	{
		m_cbNames.SetCurSel(0);
	}
	else
	{
		int nIndex = m_cbNames.FindStringExact(0,m_strName);
		m_cbNames.SetCurSel(nIndex);
	}
	m_cbTypes.SetCurSel(m_iType);
	

	m_list.SetExtendedStyle(m_list.GetExtendedStyle()| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	LVCOLUMN lvcol;
	lvcol.mask = LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.pszText = L"操作用户";
	lvcol.iSubItem = 1;  //与表列相关的子表项索引号
	lvcol.cx = 70;

	m_list.InsertColumn(0,&lvcol);
	lvcol.pszText = L"操作类型";
	m_list.InsertColumn(1,&lvcol);
	lvcol.pszText = L"时间";
	lvcol.cx=120;
	m_list.InsertColumn(2,&lvcol);
	lvcol.pszText = L"操作对象";
	lvcol.cx = 380;
	m_list.InsertColumn(3,&lvcol);

	UpdateList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void COperationDlg::SetNameAndType(CString name, int type)
{
	m_strName = name;
	m_iType = type;
}

void COperationDlg::UpdateList()
{
	m_list.DeleteAllItems();
	//m_operation.GetOperationNotes();
	std::vector<Notes> datas = m_operation.GetNotesByNameAndType(m_strName,m_iType);
	std::vector<Notes>::iterator iter;
	for (iter = datas.begin();iter!=datas.end();iter++)
	{
		int nIndex =0;
			/* m_list.GetItemCount();*/
		LV_ITEM lvItem;
		lvItem.mask = LVIF_TEXT ; 
		lvItem.iItem = nIndex;     //行数
		lvItem.iSubItem = 0;
		lvItem.pszText = iter->name.GetBuffer();   //第一列
		//插入行
		m_list.InsertItem(&lvItem); 
		//插入其它列
		m_list.SetItemText(nIndex,1,iter->action);
		m_list.SetItemText(nIndex,2,iter->time);
		m_list.SetItemText(nIndex,3,iter->path);
	}
}

void COperationDlg::OnBnClickedBtnClearlog()
{
	// TODO: 在此添加控件通知处理程序代码
	m_operation.ClearLogFile();
	m_operation.GetOperationNotes();
	UpdateList();
}

void COperationDlg::OnCbnSelchangeCbUser()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cbNames.GetLBText(m_cbNames.GetCurSel(),m_strName);	
	m_iType = m_cbTypes.GetCurSel();

	if (m_strName == _T("选择查询用户"))
	{
		m_strName =_T("");
	}
	UpdateList();
}

void COperationDlg::OnCbnSelchangeCbType()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cbNames.GetLBText(m_cbNames.GetCurSel(),m_strName);	
	m_iType = m_cbTypes.GetCurSel();

	if (m_strName == _T("选择查询用户"))
	{
		m_strName =_T("");
	}
	UpdateList();
}

void COperationDlg::OnBnClickedBtnFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	m_operation.GetOperationNotes();
	UpdateList();
}
