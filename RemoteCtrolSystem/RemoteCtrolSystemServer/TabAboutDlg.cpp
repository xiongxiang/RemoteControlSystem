// TabAboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteCtrolSystemServer.h"
#include "TabAboutDlg.h"


// TabAboutDlg 对话框

IMPLEMENT_DYNAMIC(TabAboutDlg, CDialog)

TabAboutDlg::TabAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TabAboutDlg::IDD, pParent)
{

}

TabAboutDlg::~TabAboutDlg()
{
}

void TabAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabAboutDlg, CDialog)
END_MESSAGE_MAP()


// TabAboutDlg 消息处理程序
