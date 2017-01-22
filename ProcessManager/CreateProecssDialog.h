#pragma once
#include "afxwin.h"


// CCreateProecssDialog 对话框

class CCreateProecssDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateProecssDialog)

public:
	CCreateProecssDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateProecssDialog();
	CString m_path;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
};
