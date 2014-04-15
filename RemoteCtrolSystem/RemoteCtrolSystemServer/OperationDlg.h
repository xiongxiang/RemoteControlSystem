#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "OperationNotes.h"

// COperationDlg 对话框

class COperationDlg : public CDialog
{
	DECLARE_DYNAMIC(COperationDlg)

public:
	COperationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COperationDlg();

// 对话框数据
	enum { IDD = IDD_OPERATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	/**
	 * @Brief SetNameAndType  设置要查询的记录的用户名和记录类型
	 * @Parameter CString name  用户名
	 * @Parameter int type 记录类型
	 * @Returns void
	 * @Remark  
	 **/
	void SetNameAndType(CString name, int type);

private:
	CString m_strName;
	int m_iType;
	OperationNotes m_operation;

	/**
	 * @Brief UpdateList  更新操记录列表
	 * @Returns void
	 * @Remark  
	 **/
	void UpdateList();
public:
	CComboBox m_cbNames;
	CComboBox m_cbTypes;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnClearlog();
	afx_msg void OnCbnSelchangeCbUser();
	afx_msg void OnCbnSelchangeCbType();
	afx_msg void OnBnClickedBtnFlash();
};
