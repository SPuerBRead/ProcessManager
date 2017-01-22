
// ProcessManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ProcessInfo.h"


// CProcessManagerDlg �Ի���
class CProcessManagerDlg : public CDialogEx
{
// ����
public:
	CProcessManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
