#pragma once
#include "afxwin.h"
#include "..\Graphic\ScreenDisplay.h"

// CDisplayDlg 对话框

class CDisplayDlg : public CDialog
{
	DECLARE_DYNAMIC(CDisplayDlg)

public:
	CDisplayDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDisplayDlg();

	HWND GetDisplayHwnd();
	/**
	   @brief:设置显示大小及左上角位置，这个函数会改变滚动条范围
	   @Parameter:int x
	   @Parameter:int y
	   @Parameter:int cx
	   @Parameter:int cy
	   @Return:bool
	*/
	bool SetSize(int x,int y,int cx,int cy);
	/**
	   @brief:设置显示窗口显示画面大小
	   @Parameter:int width
	   @Parameter:int height
	   @Return:bool
	*/
	bool SetScreenSize(int width,int height);
	bool Init(int width,int height);
	/**
	   @brief:全屏模式
	   @Return:void
	*/
	void FullScreen();
	/**
	   @brief:结束全屏，采用窗口模式
	   @Return:bool
	*/
	bool EndFullScreen();
	/**
	   @brief:返回当前是否为全屏模式，TRUE为全屏模式，false为窗口模式
	   @Return:bool
	*/
	bool IsFullScreen();
	void SetDisplayer(ScreenDisplay* ScreenDisplayer);
// 对话框数据
	enum { IDD = IDD_DIALOG_DISPLAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CStatic m_pctDisplay;
	int		m_left;
	int		m_top;
	int		m_cx;
	int		m_cy;
	int		m_ScreenWidth;
	int		m_ScreenHeight;
	bool	m_IsFullScreen;
	ScreenDisplay*	m_ScreenDisplayer;
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
};
