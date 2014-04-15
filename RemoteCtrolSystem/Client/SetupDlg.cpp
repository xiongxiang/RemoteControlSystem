// SetupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "SetupDlg.h"
#include <shlwapi.h>
#include "ClientMain.h"

// CSetupDlg 对话框

IMPLEMENT_DYNAMIC(CSetupDlg, CDialog)

CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	m_bIsExist = FALSE;
}

CSetupDlg::~CSetupDlg()
{
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_sldImageQuality);
	DDX_Control(pDX, IDC_SLIDER2, m_sldFrame);
	DDX_Control(pDX, IDC_EDIT_IMAGE_QUALITY, m_tbImageQuality);
	DDX_Control(pDX, IDC_EDIT_FRAME, m_tbFrame);
	DDX_Control(pDX, IDC_SLIDER_VERT_TILE, m_sldVertTile);
	DDX_Control(pDX, IDC_SLIDER_HORZ_TILE, m_sldHorzTile);
	DDX_Control(pDX, IDC_EDIT_VERT_TILE, m_tbVertTile);
	DDX_Control(pDX, IDC_EDIT_HOCZ_TILE, m_tbHorzTile);
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SETUP_OK, &CSetupDlg::OnBnClickedButtonSetupOk)
	ON_BN_CLICKED(IDC_BUTTON_SETUP_APPLY, &CSetupDlg::OnBnClickedButtonSetupApply)
	ON_BN_CLICKED(IDC_BUTTON_SETUP_CANCEL, &CSetupDlg::OnBnClickedButtonSetupCancel)

	ON_BN_CLICKED(IDC_BUTTON_IMG_SUB, &CSetupDlg::OnBnClickedButtonImgSub)
	ON_BN_CLICKED(IDC_BUTTON_IMG_ADD, &CSetupDlg::OnBnClickedButtonImgAdd)
	ON_BN_CLICKED(IDC_BUTTON_FRAME_SUB, &CSetupDlg::OnBnClickedButtonFrameSub)
	ON_BN_CLICKED(IDC_BUTTON_FRAME_ADD, &CSetupDlg::OnBnClickedButtonFrameAdd)

	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &CSetupDlg::OnNMReleasedcaptureSlider2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CSetupDlg::OnNMReleasedcaptureSlider1)

	ON_EN_CHANGE(IDC_EDIT_IMAGE_QUALITY, &CSetupDlg::OnEnChangeEditImageQuality)
	ON_EN_CHANGE(IDC_EDIT_FRAME, &CSetupDlg::OnEnChangeEditFrame)
	ON_BN_CLICKED(IDC_VERT_TILE_DOWN, &CSetupDlg::OnBnClickedVertTileDown)
	ON_BN_CLICKED(IDC_BUTTON_VERT_TILE_UP, &CSetupDlg::OnBnClickedButtonVertTileUp)
	ON_BN_CLICKED(IDC_BUTTON_HORZ_TILE_DOWN, &CSetupDlg::OnBnClickedButtonHorzTileDown)
	ON_BN_CLICKED(IDC_BUTTON_HORZ_TILE_UP, &CSetupDlg::OnBnClickedButtonHorzTileUp)
//	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER3, &CSetupDlg::OnNMReleasedcaptureSlider3)
//	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER4, &CSetupDlg::OnNMReleasedcaptureSlider4)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VERT_TILE, &CSetupDlg::OnNMReleasedcaptureSliderVertTile)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_HORZ_TILE, &CSetupDlg::OnNMReleasedcaptureSliderHorzTile)
ON_EN_CHANGE(IDC_EDIT_VERT_TILE, &CSetupDlg::OnEnChangeEditVertTile)
ON_EN_CHANGE(IDC_EDIT_HOCZ_TILE, &CSetupDlg::OnEnChangeEditHoczTile)
END_MESSAGE_MAP()


// CSetupDlg 消息处理程序

void CSetupDlg::OnStnClickedStaticFrame()
{

}

VOID CSetupDlg::SetExit( BOOL IsExist )
{
	m_bIsExist = IsExist;
}

BOOL CSetupDlg::IsExit()
{
	return m_bIsExist;
}

int CSetupDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	m_bIsExist = TRUE;

	
	return 0;
}

void CSetupDlg::OnDestroy()
{
	CDialog::OnDestroy();

	m_bIsExist = FALSE;
}

void CSetupDlg::OnBnClickedButtonSetupOk()
{
	
	//OnOK();
	((CClientMain*)GetParent())->SetFrame(m_nFrame);
	((CClientMain*)GetParent())->SetImageQuality(m_nImageQuality);
	((CClientMain*)GetParent())->SetTileNumber(m_nHorzTile,m_nVertTile);
	EndDialog(1);
}

void CSetupDlg::OnBnClickedButtonSetupApply()
{
	((CClientMain*)GetParent())->SetFrame(m_nFrame);
	((CClientMain*)GetParent())->SetImageQuality(m_nImageQuality);
	((CClientMain*)GetParent())->SetTileNumber(m_nHorzTile,m_nVertTile);
}

void CSetupDlg::OnBnClickedButtonSetupCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	EndDialog(1);
}


void CSetupDlg::OnBnClickedButtonImgSub()
{
	// TODO: 在此添加控件通知处理程序代码
	SetImageQuality(GetImageQuality()-1);
}

void CSetupDlg::OnBnClickedButtonImgAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	
	SetImageQuality(GetImageQuality()+1);
}


void CSetupDlg::OnBnClickedButtonFrameSub()
{	
	SetFrame(GetFrame()-1);
}


void CSetupDlg::OnBnClickedButtonFrameAdd()
{
	
	SetFrame(GetFrame() + 1);
}

void CSetupDlg::OnStnClickedStaticImageQuality()
{

}

BOOL CSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_sldImageQuality.SetRange(10,100);
	m_sldFrame.SetRange(1,24);
	m_sldVertTile.SetRange(10,20);
	m_sldHorzTile.SetRange(10,20);

	m_nFrame = 0;
	m_nImageQuality = 0;
	m_nVertTile = 4;
	m_nHorzTile = 4;
	SetHorzTile(15);
	SetVertTile(15);
	SetImageQuality(100);
	SetFrame(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int CSetupDlg::GetImageQuality()
{
	return m_nImageQuality;
}

int CSetupDlg::GetFrame()
{
	return m_nFrame;
}

bool CSetupDlg::SetImageQuality( int ImageQuality )
{
	if (ImageQuality > 100)
	{
		ImageQuality = 100;
	}
	if (ImageQuality < 10)
	{
		return false;
	}
	if (ImageQuality != m_nImageQuality)
	{
		CString szImageQuality;
		szImageQuality.Format(L"%d",ImageQuality);
		m_nImageQuality = ImageQuality;
		m_sldImageQuality.SetPos(m_nImageQuality);
		m_tbImageQuality.SetWindowText((LPCTSTR)szImageQuality);
	}
	

	return true;
}

bool CSetupDlg::SetFrame( int Frame )
{
	if (Frame > 24)
	{
		Frame = 24;
	}
	if (Frame < 1)
	{
		Frame = 1;
	}
	if (Frame != m_nFrame)
	{
		m_nFrame = Frame;
		CString szFrame;
		szFrame.Format(L"%d",m_nFrame);

		m_sldFrame.SetPos(m_nFrame);
		m_tbFrame.SetWindowText((LPCTSTR)szFrame);
	}


	return true;
}

void CSetupDlg::OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	SetFrame(m_sldFrame.GetPos());
	*pResult = 0;
}

void CSetupDlg::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	SetImageQuality(m_sldImageQuality.GetPos());
	*pResult = 0;
}


void CSetupDlg::OnEnChangeEditImageQuality()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	CString szImageQuality;
	int     nImageQuality;
	m_tbImageQuality.GetWindowText(szImageQuality);
	nImageQuality = StrToInt((LPCTSTR)szImageQuality);

	SetImageQuality(nImageQuality);
}

void CSetupDlg::OnEnChangeEditFrame()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString szFrame;
	int     nFrame;
	m_tbFrame.GetWindowText(szFrame);
	nFrame = StrToInt((LPCTSTR)szFrame);

	SetFrame(nFrame);
}

void CSetupDlg::OnBnClickedVertTileDown()
{
	SetVertTile(m_sldVertTile.GetPos()-1);
}

void CSetupDlg::OnBnClickedButtonVertTileUp()
{
	SetVertTile(m_sldVertTile.GetPos()+1);
}

void CSetupDlg::OnBnClickedButtonHorzTileDown()
{
	SetHorzTile(m_sldHorzTile.GetPos()-1);
}

void CSetupDlg::OnBnClickedButtonHorzTileUp()
{
	SetHorzTile(m_sldHorzTile.GetPos()+1);
}



void CSetupDlg::OnNMReleasedcaptureSliderVertTile(NMHDR *pNMHDR, LRESULT *pResult)
{
	SetVertTile(m_sldVertTile.GetPos());
	*pResult = 0;
}

void CSetupDlg::OnNMReleasedcaptureSliderHorzTile(NMHDR *pNMHDR, LRESULT *pResult)
{
	SetHorzTile(m_sldHorzTile.GetPos());
	*pResult = 0;
}

void CSetupDlg::OnEnChangeEditVertTile()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	CString szVertTile;
	int     nVertTile;
	m_tbVertTile.GetWindowText(szVertTile);
	nVertTile = StrToInt((LPCTSTR)szVertTile);

	SetVertTile(nVertTile);
}

void CSetupDlg::OnEnChangeEditHoczTile()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	CString szHorzTile;
	int     nHorzTile;
	m_tbHorzTile.GetWindowText(szHorzTile);
	nHorzTile = StrToInt((LPCTSTR)szHorzTile);

	SetHorzTile(nHorzTile);
}

bool CSetupDlg::SetVertTile( int nVertTile )
{
	if (nVertTile > 20)
	{
		nVertTile = 20;
		return false;
	}
	if (nVertTile < 10)
	{
		nVertTile = 10;
		return false;
	}
	if (nVertTile != m_nVertTile)
	{
		CString szVertTile;
		szVertTile.Format(L"%d",nVertTile);
		m_nVertTile = nVertTile;
		 m_sldVertTile.SetPos(m_nVertTile);
		m_tbVertTile.SetWindowText((LPCTSTR)szVertTile);
	}
	return true;
}

bool CSetupDlg::SetHorzTile( int nHorzTile )
{
	if (nHorzTile > 20)
	{
		nHorzTile = 20;
		return false;
	}
	if (nHorzTile < 4)
	{
		nHorzTile = 4;
		return false;
	}
	if (nHorzTile != m_nHorzTile)
	{
		CString szHorzTile;
		szHorzTile.Format(L"%d",nHorzTile);
		m_nHorzTile = nHorzTile;
		m_sldHorzTile.SetPos(m_nHorzTile);
		m_tbHorzTile.SetWindowText((LPCTSTR)szHorzTile);
	}
	return true;
}

int CSetupDlg::GetHorzTile()
{
	return m_nHorzTile;
}

int CSetupDlg::GetVertTile()
{
	return m_nVertTile;
}
