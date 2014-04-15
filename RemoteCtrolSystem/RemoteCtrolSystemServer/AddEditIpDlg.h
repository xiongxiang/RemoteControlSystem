#pragma once
#include "afxcmn.h"
#include "iprulefile.h"


// CAddEditIpDlg 对话框

class CAddEditIpDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddEditIpDlg)

public:
	CAddEditIpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddEditIpDlg();

	enum {ADD,EDIT};
// 对话框数据
	enum { IDD = IDD_ACCESS_IP_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();

	/**
	 * @Brief SetStats 设置本界面所处于的状态
	 * @Parameter int stats ADD表示是增加规则的状态，EDIT则表示为编辑规则的状态
	 * @Returns void
	 * @Remark   因为在添加规则和修改规则的时候，用到的是同一个界面
	 **/
	void SetStats(int stats);

	/**
	 * @Brief SetRule 设置本界面的规则数据，用于传入要编辑的规则
	 * @Parameter IpRule rule  具体的规则数据
	 * @Returns void
	 * @Remark  
	 **/
	void SetRule(IpRule rule);

	CIPAddressCtrl m_ipStart;  //规则起始ip地址控件变量
	CIPAddressCtrl m_ipEnd;  //规则终止ip地址控件变量
private:
	IpRule m_rule;  //用于表示界面上的规则数据
	int m_stats;  //界面所处于的状态
};
