// DisplayDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "DisplayDlg.h"
#include  <math.h>

// CDisplayDlg 对话框

IMPLEMENT_DYNAMIC(CDisplayDlg, CDialog)

CDisplayDlg::CDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayDlg::IDD, pParent)
{
	SetScreenSize(1024,768);
	m_IsFullScreen = false;
	m_cx  = 0;
	m_cy  = 0;
	m_ScreenDisplayer = NULL;
}

CDisplayDlg::~CDisplayDlg()
{
}

void CDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_pctDisplay);
}


BEGIN_MESSAGE_MAP(CDisplayDlg, CDialog)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDisplayDlg 消息处理程序

void CDisplayDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int h = 10;   
	SCROLLINFO si;   
	si.cbSize = sizeof(SCROLLINFO);   
	si.fMask = SIF_ALL;   
	GetScrollInfo(SB_HORZ, &si);   
	int nOldPos = si.nPos;   

	switch (nSBCode)   
	{   
	case SB_LINEDOWN:   
		si.nPos = min(si.nPos + h, si.nMax);   
		break;   
	case SB_PAGEDOWN:   
		si.nPos = min(si.nPos + h * 10, si.nMax);   
		break;   
	case SB_LINEUP:   
		si.nPos = max(si.nPos - h, si.nMin);   
		break;   
	case SB_PAGEUP:   
		si.nPos = max(si.nPos - h * 10, si.nMin);   
		break;   
	case SB_THUMBPOSITION:   
	case SB_THUMBTRACK:   
		si.nPos = si.nTrackPos;   
		break;   
	case SB_TOP:   
		si.nPos = si.nMin;   
		break;   
	case SB_BOTTOM:   
		si.nPos = si.nMax;   
		break;   
	}   

	SetScrollInfo(SB_HORZ, &si); 
	GetScrollInfo(SB_HORZ, &si); //重新获取新的位置 
	ScrollWindowEx(nOldPos - si.nPos,0,NULL, NULL, NULL, NULL, SW_ERASE|SW_SCROLLCHILDREN);   
	UpdateWindow();
	//m_ScreenDisplayer->ReflashDC();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDisplayDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int h = 10;   
	SCROLLINFO si;   
	si.cbSize = sizeof(SCROLLINFO);   
	si.fMask = SIF_ALL;   
	GetScrollInfo(SB_VERT, &si);   
	int nOldPos = si.nPos;   

	switch (nSBCode)   
	{   
	case SB_LINEDOWN:   
		si.nPos = min(si.nPos + h, si.nMax);   
		break;   
	case SB_PAGEDOWN:   
		si.nPos = min(si.nPos + h * 10, si.nMax);   
		break;   
	case SB_LINEUP:   
		si.nPos = max(si.nPos - h, si.nMin);   
		break;   
	case SB_PAGEUP:   
		si.nPos = max(si.nPos - h * 10, si.nMin);   
		break;   
	case SB_THUMBPOSITION:   
	case SB_THUMBTRACK:   
		si.nPos = si.nTrackPos;   
		break;   
	case SB_TOP:   
		si.nPos = si.nMin;   
		break;   
	case SB_BOTTOM:   
		si.nPos = si.nMax;   
		break;   
	}   

	SetScrollInfo(SB_VERT, &si); 
	GetScrollInfo(SB_VERT, &si); //重新获取新的位置  


	ScrollWindowEx(0, nOldPos - si.nPos,NULL, NULL, NULL, NULL, SW_ERASE|SW_SCROLLCHILDREN);   
	UpdateWindow();
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	//m_ScreenDisplayer->ReflashDC();
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

bool CDisplayDlg::SetSize( int x,int y,int cx,int cy )
{
	
	
////	if (m_cx != 0 || m_cy != 0)
//	{	
//		ScrollWindowEx(GetScrollPos(SB_HORZ) - (GetScrollPos(SB_HORZ)*(m_ScreenWidth - cx+ 15))/(m_ScreenWidth - m_cx+ 15),
//			GetScrollPos(SB_VERT) - (GetScrollPos(SB_VERT)*(m_ScreenHeight - cy+ 15))/(m_ScreenHeight - m_cy+ 15),NULL, NULL, NULL, NULL, SW_ERASE|SW_SCROLLCHILDREN);    
//		/*SetScrollPos(SB_HORZ,(GetScrollPos(SB_HORZ)*m_cx)/cx);
//		SetScrollPos(SB_VERT,(GetScrollPos(SB_VERT)*m_cy)/cy);*/
//		SetScrollPos(SB_HORZ,(GetScrollPos(SB_HORZ)*(m_ScreenWidth - cx+ 15))/)(m_ScreenWidth - m_cx+ 15);
//		SetScrollPos(SB_VERT,(GetScrollPos(SB_VERT)*(m_ScreenHeight - cy+ 15))/(m_ScreenHeight - m_cy+ 15));
//	}

	if (m_cx != cx || m_cy  != cy)
	{
	ScrollWindowEx(GetScrollPos(SB_HORZ),GetScrollPos(SB_VERT),NULL, NULL, NULL, NULL, SW_ERASE|SW_SCROLLCHILDREN);
	SetScrollPos(SB_HORZ,0);
	SetScrollPos(SB_VERT,0);
	}
	
	/*SCROLLINFO siHorz;   
	SCROLLINFO siVert;
	siHorz.cbSize = sizeof(SCROLLINFO);   
	siHorz.fMask = SIF_ALL; 
	GetScrollInfo(SB_VERT, &siHorz);
	siVert.cbSize = sizeof(SCROLLINFO);   
	siVert.fMask = SIF_ALL; 
	GetScrollInfo(SB_HORZ, &siVert);
	siHorz.nPos = 0;
	siVert.nPos = 0;
	siVert.nPage = cy - (m_ScreenHeight - cy+ 15);
	siHorz.nPage = cx - (m_ScreenWidth - cx+ 15);
	SetScrollInfo(SB_VERT,&siVert);
	SetScrollInfo(SB_HORZ,&siHorz);*/
	//SetScrollRange(SB_VERT,0,m_ScreenHeight - cy+ 15);
	//SetScrollRange(SB_HORZ,0,m_ScreenWidth - cx+ 15);
	
	SCROLLINFO siHorz;   
	SCROLLINFO siVert;
	siVert.cbSize = sizeof (SCROLLINFO);
	siVert.fMask = SIF_RANGE | SIF_PAGE; 
	siVert.nMin = 0 ; 
	siVert.nMax = m_ScreenHeight - cy+ 15; 
	siVert.nPage =  siVert.nMax*(m_ScreenHeight - siVert.nMax)/m_ScreenHeight;
	siVert.nMax = m_ScreenHeight - cy+ 15 + siVert.nPage;
	SetScrollInfo ( SB_VERT, &siVert, TRUE);

	siHorz.cbSize = sizeof (SCROLLINFO);
	siHorz.fMask = SIF_RANGE | SIF_PAGE; 
	siHorz.nMin = 0 ; 
	siHorz.nMax = m_ScreenWidth - cx+ 15; 
	siHorz.nPage = siHorz.nMax*(m_ScreenWidth-siHorz.nMax)/m_ScreenWidth;
	siHorz.nMax = m_ScreenWidth - cx+ 15 + siHorz.nPage; 
	SetScrollInfo ( SB_HORZ, &siHorz, TRUE);
	MoveWindow(x,y,cx,cy);
	m_cx  = cx;
	m_cy  = cy;
	m_left = x;
	m_top = y;
	return true;
}

void CDisplayDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if ( NULL != m_pctDisplay.GetSafeHwnd())
	{
		//m_pctDisplay.SetWindowPos(m_pctDisplay.GetWindow(GW_CHILD),0,0,1024,768,SWP_NOACTIVATE);
		/*SetScrollPos(SB_VERT,GetScrollPos(SB_VERT)*(m_ScreenHeight - cy)/(m_ScreenHeight - m_cy));
		SetScrollPos(SB_VERT,GetScrollPos(SB_HORZ)*(m_ScreenWidth - cx)/(m_ScreenWidth - m_cx));*/
		/*SetScrollPos(SB_HORZ,0);
		SetScrollPos(SB_VERT,0);*/
		/*SetScrollRange(SB_VERT,0,m_ScreenHeight - cy + 15);
		SetScrollRange(SB_HORZ,0,m_ScreenWidth - cx + 15);*/
		
	}	
	//m_cx  = cx;
	//m_cy  = cy;
}

HWND CDisplayDlg::GetDisplayHwnd()
{
	return m_pctDisplay.GetSafeHwnd();
}

bool CDisplayDlg::SetScreenSize( int width,int height )
{
	m_ScreenWidth	= width;
	m_ScreenHeight	= height;
	return true;
}

bool CDisplayDlg::Init( int width,int height )
{
	SetScreenSize(width,height);
	m_IsFullScreen	= false;

	return true;
}

void CDisplayDlg::FullScreen()
{

	m_IsFullScreen  = true;
	MoveWindow(0,0,m_ScreenWidth,m_ScreenHeight);
	ScrollWindowEx(GetScrollPos(SB_HORZ),GetScrollPos(SB_VERT),NULL, NULL, NULL, NULL, SW_ERASE|SW_SCROLLCHILDREN);
	SetScrollPos(SB_HORZ,0);
	SetScrollPos(SB_VERT,0);
	ShowScrollBar(SB_HORZ,FALSE);
	ShowScrollBar(SB_VERT,FALSE);
}

bool CDisplayDlg::EndFullScreen()
{
	m_IsFullScreen = false;
	ShowScrollBar(SB_HORZ,TRUE);
	ShowScrollBar(SB_VERT,TRUE);
	return SetSize(m_left,m_top,m_cx,m_cy);
}

bool CDisplayDlg::IsFullScreen()
{
	return m_IsFullScreen;
}



BOOL CDisplayDlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN==pMsg->message ||pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}


	return CDialog::PreTranslateMessage(pMsg);
}

void CDisplayDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CDisplayDlg::SetDisplayer( ScreenDisplay* ScreenDisplayer )
{
	m_ScreenDisplayer = ScreenDisplayer;
}
