// SRProcessDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessManager.h"
#include "SRProcessDialog.h"
#include "afxdialogex.h"


// CSRProcessDialog �Ի���

IMPLEMENT_DYNAMIC(CSRProcessDialog, CDialogEx)

CSRProcessDialog::CSRProcessDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Stop_Restart, pParent)
{

}

CSRProcessDialog::~CSRProcessDialog()
{
}

void CSRProcessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Pid);
}


BEGIN_MESSAGE_MAP(CSRProcessDialog, CDialogEx)
END_MESSAGE_MAP()


// CSRProcessDialog ��Ϣ�������
