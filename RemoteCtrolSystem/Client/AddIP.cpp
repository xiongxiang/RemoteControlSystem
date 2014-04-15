// AddIP.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "AddIP.h"


// CAddIP 对话框

IMPLEMENT_DYNAMIC(CAddIP, CDialog)

CAddIP::CAddIP(CWnd* pParent /*=NULL*/)
	: CDialog(CAddIP::IDD, pParent)
{

}

CAddIP::~CAddIP()
{
}

void CAddIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddIP, CDialog)
	ON_BN_CLICKED(IDOK, &CAddIP::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddIP 消息处理程序

void CAddIP::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
