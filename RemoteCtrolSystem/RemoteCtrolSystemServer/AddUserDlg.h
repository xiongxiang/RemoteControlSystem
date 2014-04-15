#pragma once
#include "afxwin.h"
#include "userfile.h"


// CAddUserDlg 对话框

class CAddUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddUserDlg)

public:
	CAddUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddUserDlg();

// 对话框数据
	enum {ADD,EDIT};
	enum { IDD = IDD_ADD_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();
	CEdit m_editName;
	afx_msg void OnBnClickedBtnCancel();

	/**
	 * @Brief SetUserData 设置用户数据，主要用于编辑状态时，传入数据到界面
	 * @Parameter UserData user  用户数据
	 * @Returns void 
	 * @Remark  
	 **/
	void SetUserData(UserData user);

	/**
	 * @Brief SetStats  设置界面所处的状态
	 * @Parameter int stats ADD表示添加状态、EDIT表示编辑状态
	 * @Returns void
	 * @Remark  这是由于添加和编辑使用的是同一个界面
	 **/
	void SetStats(int stats);
private:
	
	UserData m_user;  //用户数据
	int m_stats; //状态


};
