// ClientMain.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientMain.h"
#include "..\CxImage\ximage.h"
#include "..\Message\KeyboardMsg.h"
#include "..\Message\SetupMsg.h"
#include "..\Message\UserMsg.h"
#include "..\Message\MouseMsg.h"
#include <map>
#include <atlconv.h>

// CClientMain 对话框

IMPLEMENT_DYNAMIC(CClientMain, CDialog)

CClientMain::CClientMain(CWnd* pParent /*=NULL*/)
	: CDialog(CClientMain::IDD, pParent)
{
	m_IsFullScreen = false;
	m_nTimer = 0;
	m_AltCheck	= TRUE;
	m_WinCheck	= TRUE;
	m_CtrlCheck	= TRUE;
}

CClientMain::~CClientMain()
{
}

void CClientMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_pctDisplay);
}


BEGIN_MESSAGE_MAP(CClientMain, CDialog)
	ON_WM_CREATE()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON_SERVER_LIST,&CClientMain::OnBtnServerList)
	ON_COMMAND(ID_BUTTON_SETUP,&CClientMain::OnBtnSetup)
	ON_COMMAND(ID_BUTTON_SHOT_SCREEN,&CClientMain::OnBtnScreenShot)
	ON_COMMAND(ID_BUTTON_FULL_SCREEN,&CClientMain::OnBtnFullScreen)
	ON_COMMAND(ID_BUTTON_ALT,&CClientMain::OnBtnAlt)
	ON_COMMAND(ID_BUTTON_CTRL,&CClientMain::OnBtnCtrl)
	ON_COMMAND(ID_BUTTON_WINKEY,&CClientMain::OnBtnWin)
	ON_COMMAND(ID_BUTTON_SCALE_UP,&CClientMain::OnBtnScaleUp)
	ON_COMMAND(ID_BUTTON_SCALE_DOWN,&CClientMain::OnBtnScaleDown)
	ON_COMMAND(ID_BUTTON_AUTO_SIZE,&CClientMain::OnBtnScaleLocalSize)
	ON_COMMAND(ID_BUTTON_TASKMGR,&CClientMain::OnBtnTackMgr)
	
	
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_DESTROY()
//	ON_MESSAGE(WM_ADDIP, OnAddIpMessage)
END_MESSAGE_MAP()


// CClientMain 消息处理程序

int CClientMain::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}


void CClientMain::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
    
	if (m_dlgServerList.GetStatus() == SL_DOCK_WINDOW
		&& m_dlgServerList.GetSafeHwnd() != NULL)
	{
		RECT rcClient;
		RECT rcServerList;
		GetWindowRect(&rcClient);
		m_dlgServerList.GetWindowRect(&rcServerList);

		rcServerList.top = rcClient.top;
		rcServerList.bottom = rcClient.bottom;
		rcServerList.right = rcClient.right + rcServerList.right - rcServerList.left;
		rcServerList.left   = rcClient.right;

		m_dlgServerList.MoveWindow(&rcServerList,TRUE);
    }
	RECT rcClient;
	GetWindowRect(&rcClient);
	int ScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	m_ScreenDisplayer.SetSize(ScreenWidth,ScreenHeight);
	m_dlgDisplay.SetSize(rcClient.left + 4,rcClient.top + 54,rcClient.right - rcClient.left - 8,rcClient.bottom - rcClient.top - 58);
	//m_pctDisplay.SetWindowPos(m_pctDisplay.GetWindow(GW_CHILD),0 ,24,ScreenWidth,ScreenHeight,SWP_NOACTIVATE);
	
}
void CClientMain::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (!m_IsFullScreen && m_dlgServerList.GetSafeHwnd() != NULL)
	{
		RECT rcClient;
		RECT rcServerList;
		GetWindowRect(&rcClient);
		m_dlgServerList.GetWindowRect(&rcServerList);

		rcServerList.top = rcClient.top;
		rcServerList.bottom = rcClient.bottom;
		rcServerList.right = rcClient.right + rcServerList.right - rcServerList.left;
		rcServerList.left   = rcClient.right;

		m_dlgServerList.MoveWindow(&rcServerList,TRUE);
	}
	RECT rcClient;
	GetWindowRect(&rcClient);
	int ScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	m_ScreenDisplayer.SetSize(ScreenWidth,ScreenHeight);
	m_dlgDisplay.SetSize(rcClient.left + 4,rcClient.top + 54,rcClient.right - rcClient.left - 8,rcClient.bottom - rcClient.top - 58);
	//m_pctDisplay.SetWindowPos(m_pctDisplay.GetWindow(GW_CHILD),0 ,24,ScreenWidth,ScreenHeight,SWP_NOACTIVATE);
}

void CClientMain::OnBtnServerList()
{
	if (m_dlgServerList.GetStatus() == SL_HIDE)
	{
		m_dlgServerList.SetStatus(SL_DOCK_WINDOW);
	} 
	else if (m_dlgServerList.GetStatus() == SL_DOCK_WINDOW ||
		       m_dlgServerList.GetStatus() == SL_DOCK_SCREEN)
	{
		m_dlgServerList.SetStatus(SL_HIDE);
	}
	else
	{

	}

}

void CClientMain::OnTimer(UINT_PTR nIDEvent)
{

	//m_ScreenShooter.ShotScreenImage(&m_RecvQueue);
	
    DealMessage();
	CDialog::OnTimer(nIDEvent);
}

bool CClientMain::SetFrame(int frame)
{
	if (0!=m_nTimer)
	{
		KillTimer(m_nTimer);
	}
	m_nTimer = SetTimer(1,1000/30,0);
	m_Frame = frame;
	if (m_bTcpConect)
	{
	SetupMsg *FrameMsg = new SetupMsg;
	FrameMsg->PacketMsg(RCS_SETUP_MSG_FRAME,frame);
	m_tcpClien.send(*FrameMsg);
	delete FrameMsg;
	}
	return false;
}

void CClientMain::OnBtnSetup()
{
	m_dlgSetup.ShowWindow(SW_SHOW);
}

void CClientMain::OnBtnScreenShot()
{
	OnScreenShot();
}

void CClientMain::OnScreenShot()
{
	CxImage ScreenImage = m_ScreenDisplayer.GetDisplayImage();
	//if (ScreenImage.CreateFromHBITMAP(m_ScreenDisplayer.GetDisplayImage()))
	{
		ScreenImage.SetJpegQuality(m_dlgSetup.GetImageQuality());
		TCHAR filter[] = _T("(*.bmp)|*.bmp |(*.gif)|*.gif|(*.jpg)|*.jpg|(*.png)|*.png|(*.tif)|*.tif|(*.tga)|*.tga|(*.pcx)|*.pcx|(*.wbmp)|*.wbmp|(*.wmf)|*.wmf|(*.jp2)|*.jp2|(*.jpc)|*.jpc|(*.pgx)|*.pgx|(*.raw)|*.raw||");
		CFileDialog SaveDlg(false,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter);
		if (IDOK == SaveDlg.DoModal())
		{
			CString FilePathName = SaveDlg.GetPathName();
			std::map<int,const wchar_t* const> mapFileExt;//保存所要用到的文件后缀名
			std::map<int,DWORD> mapSaveType;//保存所要的图片保存类型对应的CxImage宏
			mapFileExt.insert(std::make_pair(1,_T(".bmp")));
			mapFileExt.insert(std::make_pair(2,_T(".gif")));
			mapFileExt.insert(std::make_pair(3,_T(".jpg")));
			mapFileExt.insert(std::make_pair(4,_T(".png")));
			mapFileExt.insert(std::make_pair(5,_T(".tif")));
			mapFileExt.insert(std::make_pair(6,_T(".tga")));
			mapFileExt.insert(std::make_pair(7,_T(".pcx")));
			mapFileExt.insert(std::make_pair(8,_T(".wbmp")));
			mapFileExt.insert(std::make_pair(9,_T(".wmf")));
			mapFileExt.insert(std::make_pair(10,_T(".jp2")));
			mapFileExt.insert(std::make_pair(11,_T(".jpc")));
			mapFileExt.insert(std::make_pair(12,_T(".pgx")));
			mapFileExt.insert(std::make_pair(13,_T(".raw")));
	
			mapSaveType.insert(std::make_pair(1,CXIMAGE_FORMAT_BMP));
			mapSaveType.insert(std::make_pair(2,CXIMAGE_FORMAT_GIF));
			mapSaveType.insert(std::make_pair(3,CXIMAGE_FORMAT_JPG));
			mapSaveType.insert(std::make_pair(4,CXIMAGE_FORMAT_PNG));
			mapSaveType.insert(std::make_pair(5,CXIMAGE_FORMAT_TIF));
			mapSaveType.insert(std::make_pair(6,CXIMAGE_FORMAT_TGA));
			mapSaveType.insert(std::make_pair(7,CXIMAGE_FORMAT_PCX));
			mapSaveType.insert(std::make_pair(8,CXIMAGE_FORMAT_WBMP));
			mapSaveType.insert(std::make_pair(9,CXIMAGE_FORMAT_WMF));
			mapSaveType.insert(std::make_pair(10,CXIMAGE_FORMAT_JP2));
			mapSaveType.insert(std::make_pair(11,CXIMAGE_FORMAT_JPC));
			mapSaveType.insert(std::make_pair(12,CXIMAGE_FORMAT_PGX));
			mapSaveType.insert(std::make_pair(13,CXIMAGE_FORMAT_RAW));

			int						nFileExt = SaveDlg.m_ofn.nFilterIndex;
			const wchar_t *const 	tFileExt = mapFileExt[nFileExt];
			DWORD					dwSaveType = mapSaveType[nFileExt];
			if(FilePathName.Right(4) !=tFileExt) 
			{
				FilePathName += tFileExt; 
				ScreenImage.Save(FilePathName.GetString() ,dwSaveType);
			}
		}
	}

}

bool CClientMain::SetImageQuality( int quality )
{
	//return m_ScreenShooter.SetQuality(quality);
	if (m_bTcpConect)
	{
	SetupMsg *ImageQualityMsg = new SetupMsg;
	ImageQualityMsg->PacketMsg(RCS_SETUP_MSG_IMAGE_QUALITY,quality);
	m_tcpClien.send(*ImageQualityMsg);
	delete ImageQualityMsg;
	}
	return true;
}

BOOL CClientMain::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bTcpConect  =FALSE;
	m_MainToolBar.CreateEx(this,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);
	m_MainToolBar.LoadToolBar(IDR_TOOLBAR3);
	m_MainToolBar.GetToolBarCtrl().SetBitmapSize(CSize(16,16));
	m_MainToolBar.GetToolBarCtrl().SetButtonSize(CSize(22,22));

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	ShowWindow(SW_HIDE);
	Host host;
	m_HostListConfig.Init("ClientConfig.xml");
	m_HostListConfig.ReadHostList(m_vtHostList);
	m_cmbLogin.Init(&m_HostListConfig,&host);
	INT_PTR nResponse =m_cmbLogin.DoModal();
	if (nResponse != IDC_BUTTON_LOGIN)
	{
		PostQuitMessage(0);
	}
	else
	{
		m_tcpClien.Start();
		m_bTcpConect = TRUE;
	}
	
	m_dlgServerList.Create(IDD_DIALOG_SERVER_LIST,this);
	m_dlgServerList.Init(&m_HostListConfig);
	m_dlgSetup.Create(IDD_DIALOG_SETUP,this);
	m_dlgDisplay.Create(IDD_DIALOG_DISPLAY,this);

	RECT rcScreen;
	::GetClientRect(::GetDesktopWindow(),&rcScreen);
	int ScreenWidth = rcScreen.right - rcScreen.left;
	int ScreenHeight = rcScreen.bottom - rcScreen.top;
	m_dlgDisplay.Init(ScreenWidth,ScreenHeight);
	m_dlgDisplay.ShowWindow(SW_SHOW);
	m_dlgServerList.SetStatus(SL_HIDE);
	m_ScreenShooter.Init(15,15);
	m_ScreenDisplayer.Initialize(m_dlgDisplay.GetDisplayHwnd(),ScreenWidth,ScreenHeight,1280,800);
	
	
	m_Frame = 10;
	m_dlgSetup.SetFrame(m_Frame);
	SetFrame(m_dlgSetup.GetFrame());

	SetupMsg* TileMsg = new SetupMsg;
	SetupMsg* FrameMsg = new SetupMsg;
	SetupMsg* ImageQualityMsg = new SetupMsg;
	TileMsg->PacketMsg(RCS_SETUP_MSG_TILE,m_dlgSetup.GetHorzTile(),m_dlgSetup.GetVertTile());
	FrameMsg->PacketMsg(RCS_SETUP_MSG_FRAME,m_dlgSetup.GetFrame());
	ImageQualityMsg->PacketMsg(RCS_SETUP_MSG_IMAGE_QUALITY,m_dlgSetup.GetImageQuality());
	AutoLock l(&m_mLocaMutex);
	m_SendQueue.push(TileMsg);
	m_SendQueue.push(FrameMsg);
	m_SendQueue.push(ImageQualityMsg);
	m_dlgDisplay.SetDisplayer(&m_ScreenDisplayer);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CClientMain::OnBtnFullScreen()
{
	//ShowWindow(SW_HIDE);
	FullScreen();
}


BOOL CClientMain::PreTranslateMessage(MSG* pMsg)
{
	return CDialog::PreTranslateMessage(pMsg);
}


void CClientMain::OnOK()
{

	//CDialog::OnOK();
}

void CClientMain::OnBtnScaleUp()
{
	m_ScreenDisplayer.ScaleUp();
}

void CClientMain::OnBtnScaleDown()
{
	m_ScreenDisplayer.ScaleDown();
}

void CClientMain::OnDestroy()
{
	m_tcpClien.Close();
	CDialog::OnDestroy();
}

void CClientMain::SendMouseMsg( int x,int y ,int MouseStatus)
{
	if (m_bTcpConect && m_bCtrlPermission)
	{
		RECT rcDisplay;
		if (m_dlgDisplay.GetSafeHwnd() != NULL)
		{
			m_dlgDisplay.GetWindowRect(&rcDisplay);
			int sbvPos = m_dlgDisplay.GetScrollPos(SB_VERT);
			int sbhPos = m_dlgDisplay.GetScrollPos(SB_HORZ);
			int SeverMouseX = ((x + sbhPos - rcDisplay.left - m_ScreenDisplayer.GetWinWidth()/2 + m_ScreenDisplayer.GetDisplayWidth()/2) * m_ScreenDisplayer.GetSeverWidth()) / m_ScreenDisplayer.GetDisplayWidth() ;
			int SeverMouseY = ((y + sbvPos - rcDisplay.top - m_ScreenDisplayer.GetWinHeigth()/2 + m_ScreenDisplayer.GetDisplayHeight()/2) * m_ScreenDisplayer.GetServerHeight()) / m_ScreenDisplayer.GetDisplayHeight() ;
			if (SeverMouseX <=  m_ScreenDisplayer.GetSeverWidth()&&
				SeverMouseX >= 0 &&
				SeverMouseY <=  m_ScreenDisplayer.GetServerHeight()&&
				SeverMouseY >= 0 )
			{
				//TODO:将计算好的SverMouseX和SeverMouseY打包消息添加到消息队列中
				MouseMsg* pMousePos = new MouseMsg;
				pMousePos->PacketMsg(SeverMouseX,SeverMouseY,MouseStatus);
				m_tcpClien.send(*pMousePos);
				delete pMousePos;
			}
		}
	}
	
	
}

void CClientMain::SetTileNumber( int nHorz,int nVert )
{
	//测试使用
	//m_ScreenShooter.Init(nHorz,nVert);
	//实际使用
	if (m_bTcpConect)
	{
	SetupMsg* pTileMsg = new SetupMsg;
	pTileMsg->PacketMsg(RCS_SETUP_MSG_TILE,nVert,nHorz);
	m_tcpClien.send(*pTileMsg);
	delete pTileMsg;
	}
}

void CClientMain::OnBtnAlt()
{
	m_AltCheck = !m_AltCheck;
	m_MainToolBar.GetToolBarCtrl().CheckButton(m_MainToolBar.GetItemID(3),m_AltCheck);
	if (m_AltCheck)
	{
		SendKeyboardMsg(VK_MENU,RCS_KEY_DOWN);
	}
	else
	{
		SendKeyboardMsg(VK_MENU,RCS_KEY_UP);
	}
}

void CClientMain::OnBtnCtrl()
{
	m_CtrlCheck = !m_CtrlCheck;
	m_MainToolBar.GetToolBarCtrl().CheckButton(m_MainToolBar.GetItemID(5),m_CtrlCheck);
	if (m_CtrlCheck)
	{
		SendKeyboardMsg(VK_CONTROL,RCS_KEY_DOWN);
	}
	else
	{
		SendKeyboardMsg(VK_CONTROL,RCS_KEY_UP);
	}
}

void CClientMain::OnBtnWin()
{
	m_WinCheck = !m_WinCheck;
	m_MainToolBar.GetToolBarCtrl().CheckButton(m_MainToolBar.GetItemID(4),m_WinCheck);
	if (m_WinCheck)
	{
		SendKeyboardMsg(VK_LWIN,RCS_KEY_DOWN);
	}
	else
	{
		SendKeyboardMsg(VK_LWIN,RCS_KEY_UP);
	}
}

int CClientMain::InitTcpClien(Host host,UserMsg* userMsg)
{
	//AutoLock l(&m_mLocaMutex);
	m_mLocaMutex.Lock();
	m_SendQueue.push(userMsg);
	m_mLocaMutex.Unlock();
	int logresult = m_tcpClien.Init(string(host.ip),host.port,m_SendQueue,m_RecvQueue);
	if (logresult != 0 && logresult != 1)
	{
		m_tcpClien.Close();
	}
	if (logresult == 0)
	{
		m_bCtrlPermission = FALSE;
	}
	else
	{
		m_bCtrlPermission = TRUE;
	}
	return logresult;

}

LRESULT CClientMain::OnAddIpMessage( WPARAM wParam, LPARAM lParam )
{
	if(wParam == 0)
	{
		int nIndex = m_cmbLogin.m_cmbServerList.AddString(m_cmbLogin.m_dlgAddIP.GetAddName().GetString());
		m_cmbLogin.m_cmbServerList.SetCurSel(nIndex);
	}

	return 1;
}

void CClientMain::SendKeyboardMsg( int key,int status )
{
	if (m_bTcpConect && m_bCtrlPermission)
	{
		KeyboardMsg* pKeyMsg = new KeyboardMsg;
		pKeyMsg->PacketMsg(key,status);
		m_tcpClien.send(*pKeyMsg);
		delete pKeyMsg;
	}
	
}

void CClientMain::FullScreen()
{
	 m_dlgDisplay.FullScreen();
	 m_ScreenDisplayer.Scale2LocalSize();
}

bool CClientMain::EndFullScreen()
{
	return m_dlgDisplay.EndFullScreen();
}

bool CClientMain::IsFullScreen()
{
	return m_dlgDisplay.IsFullScreen();
}

void CClientMain::DealMessage()
{
	while (!m_RecvQueue.empty())
	{
		ByteArrayMsg* curMessage = m_RecvQueue.front();
		__int8 msgType = curMessage->GetType();

		switch (msgType)
		{
		case RCS_MSG_IMAGE:
			m_ScreenDisplayer.RecvImageMsg(curMessage);
			break;
		case RCS_MSG_SETUP:
			if (((SetupMsg*)curMessage)->GetStatusType() == RCS_SETUP_MSG_PERMISSION)
			{
				if (((SetupMsg*)curMessage)->GetValue1() == RCS_PERMISSION_IP)
				{
					if (((SetupMsg*)curMessage)->GetValue2() == 1)
					{
						m_bCtrlPermission = TRUE;
					}
					else
					{
						m_bCtrlPermission = FALSE;
					}
				}

			}
			if (((SetupMsg*)curMessage)->GetStatusType() == RCS_SETUP_MSG_PIXEL)
			{
				m_ScreenDisplayer.SetServerSize(((SetupMsg*)curMessage)->GetValue1(),((SetupMsg*)curMessage)->GetValue2());
			}
			delete curMessage;
			break;
		default:
			break;
		}
		m_RecvQueue.pop();
	}
	m_ScreenDisplayer.Display();

}

void CClientMain::OnBtnScaleLocalSize()
{
	m_ScreenDisplayer.Scale2LocalSize();
}

void CClientMain::OnBtnTackMgr()
{
	SendKeyboardMsg(RCS_KEY_TASKMGR,RCS_KEY_DOWN);
}

