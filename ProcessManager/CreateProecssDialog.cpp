// CreateProecssDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessManager.h"
#include "CreateProecssDialog.h"
#include "afxdialogex.h"


// CCreateProecssDialog �Ի���

IMPLEMENT_DYNAMIC(CCreateProecssDialog, CDialogEx)

CCreateProecssDialog::CCreateProecssDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CreateProcess, pParent)
{

}

CCreateProecssDialog::~CCreateProecssDialog()
{
}

void CCreateProecssDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_path);
}


BEGIN_MESSAGE_MAP(CCreateProecssDialog, CDialogEx)
END_MESSAGE_MAP()


// CCreateProecssDialog ��Ϣ�������
