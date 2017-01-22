
// ProcessManagerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "ProcessInfo.h"


// CProcessManagerDlg 对话框
class CProcessManagerDlg : public CDialogEx
{
// 构造
public:
	CProcessManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//void test();
	CListCtrl m_ProcessList;
	CListCtrl m_DllList;
	void GetProcessInfo();
	CProcessInfo m_PInfo;
	afx_msg void OnNMDblclkkProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedStartprocess();
	afx_msg void OnBnClickedShutdown();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedRestart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
