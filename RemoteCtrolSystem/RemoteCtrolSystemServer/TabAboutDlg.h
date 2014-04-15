/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   TabAboutDlg.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   
**Create date:  2013/05/03   9:17
**Version:
**Description: 
**
**
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**-------------------------------------------------------------------------
**Modified by:
**Modified date:
**Version:
**Description:
**
**************************************************************************/
#ifndef __TABABOUTDLG_H__
#define __TABABOUTDLG_H__

// TabAboutDlg 对话框

class TabAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(TabAboutDlg)

public:
	TabAboutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TabAboutDlg();

// 对话框数据
	enum { IDD = IDD_TAB_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
#endif//__TABABOUTDLG_H__