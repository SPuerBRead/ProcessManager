#pragma once
#include "afxwin.h"


// CCreateProecssDialog �Ի���

class CCreateProecssDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateProecssDialog)

public:
	CCreateProecssDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateProecssDialog();
	CString m_path;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
};
