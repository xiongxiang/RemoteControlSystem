// Client.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ClientMain.h"
#include "ServerListDlg.h"
#include "..\Message\KeyboardMsg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClientApp 构造

CClientApp::CClientApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_lastTime = GetTickCount();
}


// 唯一的一个 CClientApp 对象

CClientApp theApp;


// CClientApp 初始化

BOOL CClientApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	CClientMain dlg;
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}


	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

//BOOL CClientApp::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	return CWinApp::PreTranslateMessage(pMsg);
//}

BOOL CClientApp::OnIdle(LONG lCount)
{
	// TODO: 在此添加专用代码和/或调用基类


	return CWinApp::OnIdle(lCount);
}

BOOL CClientApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//static float sLastTime = GetTickCount(); 

	if(WM_MOUSEMOVE == pMsg->message)
	{
		DWORD  curTime = GetTickCount();
		if (curTime - m_lastTime > 1000/24)
		{
			CPoint mousePoint;
			GetCursorPos(&mousePoint);
			if (m_oldMousePos != mousePoint)
			{		
				((CClientMain*)m_pMainWnd)->SendMouseMsg(mousePoint.x,mousePoint.y,0);
			}
			m_oldMousePos = mousePoint;
			m_lastTime = curTime;
		}		
	}
	if(pMsg->message >= WM_LBUTTONDOWN && pMsg->message <= WM_MBUTTONDBLCLK )
	{
		CPoint mousePoint;
		GetCursorPos(&mousePoint);
		((CClientMain*)m_pMainWnd)->SendMouseMsg(mousePoint.x,mousePoint.y,pMsg->message);
	}

	if (WM_MOUSEWHEEL == pMsg->message)
	{
		CPoint mousePoint;
		GetCursorPos(&mousePoint);
		((CClientMain*)m_pMainWnd)->SendMouseMsg(mousePoint.x,mousePoint.y,(short)HIWORD(pMsg->wParam));
	}

	if (WM_KEYDOWN==pMsg->message||WM_SYSKEYDOWN == pMsg->message)
	{
		if( GetKeyState(VK_CONTROL) < 0 && 
			GetKeyState(VK_SHIFT) < 0 &&
			GetKeyState(VK_RETURN) < 0)
		{
			if (((CClientMain*)m_pMainWnd)->IsFullScreen())
			{
				((CClientMain*)m_pMainWnd)->EndFullScreen();
			}
			else
			{
				((CClientMain*)m_pMainWnd)->FullScreen();
			}

			return true;
		}
	
		((CClientMain*)m_pMainWnd)->SendKeyboardMsg(pMsg->wParam,RCS_KEY_DOWN);
		if (((CClientMain*)m_pMainWnd)->IsFullScreen())
		{
			return TRUE;
		}
	}
	if (WM_KEYUP==pMsg->message||WM_SYSKEYUP == pMsg->message)
	{
		((CClientMain*)m_pMainWnd)->SendKeyboardMsg(pMsg->wParam,RCS_KEY_UP);
		if (((CClientMain*)m_pMainWnd)->IsFullScreen())
		{
			return TRUE;
		}
	}

	//float  fCurTime = GetTickCount(); 
	//if (fCurTime - sLastTime > 100)
	//{
	//	((CClientMain*)m_pMainWnd)->DealMessage();
	//}
	return CWinApp::PreTranslateMessage(pMsg);
}
