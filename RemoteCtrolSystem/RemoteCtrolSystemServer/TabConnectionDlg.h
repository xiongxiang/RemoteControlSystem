/**************************************************************************
**             Guangzhou ZHIYUAN electronics Co.,LTD
**             
**
**                   http://www.embedtools.com  
**-------------File Info---------------------------------------------------
**File Name:   TabConnectionDlg.h
**Latest modified Data:
**Latest Version:
**Description:  
**
**-------------------------------------------------------------------------
**Create by:   
**Create date:  2013/05/03   9:19
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
#ifndef __TABCONNECTIONDLG_H__
#define __TABCONNECTIONDLG_H__

#include "resource.h"
#include "afxcmn.h"
#include "OperationDlg.h"

#include "../SocketIPv4/TcpConnection.h"

#include <iostream>
#include <vector>

class ConnectionData{
public:
	CString ip;
	CString username;
	int status;
	CString logintime;
	TCPConnection* connection;
};

// TabConnectionDlg 对话框

class TabConnectionDlg : public CDialog
{
	DECLARE_DYNAMIC(TabConnectionDlg)

public:
	TabConnectionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TabConnectionDlg();

// 对话框数据
	enum { IDD = IDD_TAB_CONNECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listConnection;
	virtual BOOL OnInitDialog();

	void UpdateList();
	void AddConnection(ConnectionData data);
	BOOL IsUserLogined(CString name);
	void DeleteItemByConnection(TCPConnection *connection);
	void LoginOutAllUser();

private:
	std::vector<ConnectionData> m_ConnectionData;
	//COperationDlg m_operatDlg;
public:
	afx_msg void OnBnClickedBtnBroken();
	afx_msg void OnBnClickedBtOperator();
};
#endif//__TABCONNECTIONDLG_H__