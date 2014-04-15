// AddIpSL.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "AddIpSL.h"


// CAddIpSL 对话框

IMPLEMENT_DYNAMIC(CAddIpSL, CDialog)

CAddIpSL::CAddIpSL(CWnd* pParent /*=NULL*/)
	: CDialog(CAddIpSL::IDD, pParent)
{

}

CAddIpSL::~CAddIpSL()
{
}

void CAddIpSL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddIpSL, CDialog)
END_MESSAGE_MAP()


// CAddIpSL 消息处理程序
