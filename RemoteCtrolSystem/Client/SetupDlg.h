#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetupDlg 对话框
class CClientMain;

class CSetupDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetupDlg)

public:
	CSetupDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetupDlg();


	/**
	   @brief:返回图像质量，返回的是一个表示百分比的1~100的整数
	   @Return:int
	*/
	int		GetImageQuality();
	/**
	   @brief:返回帧率
	   @Return:int
	*/
	int		GetFrame();
	/**
	   @brief:设置帧率，同时根据帧率同步设置窗口的各个控件
	   @Parameter:int Frame
	   @Return:bool
	*/
	/**
	   @brief:判断是否有窗口打开
	   @Return:BOOL
	*/
	BOOL	IsExit();
		/**
	   @brief:设置图像质量，同时根据图像质量同步设置窗口的各个控件
	   @Parameter:int ImageQuality
	   @Return:bool
	*/
	/**
	   @brief:返回横向分块数
	   @Return:int
	*/
	int		GetHorzTile();
	/**
	   @brief:返回纵向分块数
	   @Return:int
	*/
	int		GetVertTile();
	/**
	   @brief:设置图像质量
	   @Parameter:int ImageQuality
	   @Return:bool
	*/
	bool	SetImageQuality(int ImageQuality);
	/**
	   @brief:设置帧率
	   @Parameter:int Frame
	   @Return:bool
	*/
	bool	SetFrame(int Frame);
	/**
	   @brief:设置垂直分快块数
	   @Parameter:int nVertTile
	   @Return:bool
	*/
	bool	SetVertTile(int nVertTile);
	/**
	   @brief:设置水平分块块数
	   @Parameter:int nHorzTile
	   @Return:bool
	*/
	bool	SetHorzTile(int nHorzTile);
// 对话框数据
	enum { IDD = IDD_DIALOG_SETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	
	VOID		 SetExit(BOOL	IsExist);
private:
	virtual BOOL OnInitDialog();
	/**
	   @brief:确定按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonSetupOk();
	/**
	   @brief:应用按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonSetupApply();
	/**
	   @brief:取消按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonSetupCancel();
	/**
	   @brief:图像质量减少按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonImgSub();
	/**
	   @brief:图像质量增加按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonImgAdd();
	/**
	   @brief:帧率减少按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonFrameSub();
	/**
	   @brief:帧率增加按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonFrameAdd();
	/**
	   @brief:垂直分块块数减少按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedVertTileDown();
	/**
	   @brief:垂直分块块数增加按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonVertTileUp();
	/**
	   @brief:水平分块块数减少按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonHorzTileDown();
	/**
	   @brief:水平分块块数增加按钮
	   @Return:void
	*/
	afx_msg void OnBnClickedButtonHorzTileUp();
	/**
	   @brief:帧率调整进度条
	   @Parameter:NMHDR * pNMHDR
	   @Parameter:LRESULT * pResult
	   @Return:void
	*/
	afx_msg void OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	/**
	   @brief:图像质量调整进度条
	   @Parameter:NMHDR * pNMHDR
	   @Parameter:LRESULT * pResult
	   @Return:void
	*/
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);

	/**
	   @brief:图像质量调整编辑框
	   @Return:void
	*/
	afx_msg void OnEnChangeEditImageQuality();
	/**
	   @brief:帧率调整编辑框
	   @Return:void
	*/
	afx_msg void OnEnChangeEditFrame();
	/**
	   @brief:垂直分块进度条
	   @Parameter:NMHDR * pNMHDR
	   @Parameter:LRESULT * pResult
	   @Return:void
	*/
	afx_msg void OnNMReleasedcaptureSliderVertTile(NMHDR *pNMHDR, LRESULT *pResult);
	/**
	   @brief:水平分块进度条
	   @Parameter:NMHDR * pNMHDR
	   @Parameter:LRESULT * pResult
	   @Return:void
	*/
	afx_msg void OnNMReleasedcaptureSliderHorzTile(NMHDR *pNMHDR, LRESULT *pResult);
	/**
	   @brief:垂直分块编辑框
	   @Return:void
	*/
	afx_msg void OnEnChangeEditVertTile();
	/**
	   @brief:水平分块编辑框
	   @Return:void
	*/
	afx_msg void OnEnChangeEditHoczTile();
	afx_msg void OnStnClickedStaticFrame();
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();	
	afx_msg void OnStnClickedStaticImageQuality();
	
	BOOL		m_bIsExist;
	int			m_nImageQuality;
	int			m_nFrame;
	int			m_nVertTile;
	int			m_nHorzTile;
	CSliderCtrl m_sldImageQuality;
	CSliderCtrl m_sldFrame;
	CSliderCtrl m_sldVertTile;
	CSliderCtrl m_sldHorzTile;
	CEdit m_tbImageQuality;
	CEdit m_tbFrame;
	CEdit m_tbVertTile;
	CEdit m_tbHorzTile;
};
