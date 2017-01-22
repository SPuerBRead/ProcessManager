#pragma once


// CSRProcessDialog 对话框

class CSRProcessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSRProcessDialog)

public:
	CSRProcessDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSRProcessDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Stop_Restart };
#endif
	CString m_Pid;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
