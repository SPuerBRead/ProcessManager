#pragma once


// CSRProcessDialog �Ի���

class CSRProcessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSRProcessDialog)

public:
	CSRProcessDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSRProcessDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Stop_Restart };
#endif
	CString m_Pid;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
