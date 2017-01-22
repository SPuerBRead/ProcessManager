
// ProcessManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessManager.h"
#include "ProcessManagerDlg.h"
#include "afxdialogex.h"
#include "CreateProecssDialog.h"
#include "SRProcessDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProcessManagerDlg �Ի���



CProcessManagerDlg::CProcessManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROCESSMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ProcessList);
	DDX_Control(pDX, IDC_LIST3, m_DllList);
}

BEGIN_MESSAGE_MAP(CProcessManagerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CProcessManagerDlg::OnNMDblclkkProcess)
	ON_BN_CLICKED(IDC_StartProcess, &CProcessManagerDlg::OnBnClickedStartprocess)
	ON_BN_CLICKED(IDC_ShutDown, &CProcessManagerDlg::OnBnClickedShutdown)
	ON_BN_CLICKED(IDC_Stop, &CProcessManagerDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_Restart, &CProcessManagerDlg::OnBnClickedRestart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProcessManagerDlg ��Ϣ�������

BOOL CProcessManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect Process_rect;
	m_ProcessList.GetClientRect(&Process_rect);
	m_ProcessList.SetExtendedStyle(m_ProcessList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ProcessList.InsertColumn(0, "������", LVCFMT_LEFT, Process_rect.Width() * 4 / 5, 0);
	m_ProcessList.InsertColumn(1, "����ID", LVCFMT_LEFT, Process_rect.Width() / 5, 0);
	//m_ProcessList.InsertColumn(2, "״̬", LVCFMT_LEFT);
	m_ProcessList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	CRect Dll_rect;
	m_DllList.GetClientRect(&Dll_rect);
	m_DllList.SetExtendedStyle(m_ProcessList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_DllList.InsertColumn(0, "DLL��", LVCFMT_LEFT, Dll_rect.Width() / 4, 0);
	m_DllList.InsertColumn(1, "DLL·��", LVCFMT_LEFT, Dll_rect.Width() * 3 / 4, 0);
	m_DllList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	GetProcessInfo();
	SetTimer(1, 10000, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CProcessManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CProcessManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProcessManagerDlg::GetProcessInfo()
{
	m_ProcessList.DeleteAllItems();
	m_PInfo.GetProcess();
	for (int i = 0; i < m_PInfo.m_PorcessPe32.size(); i++)
	{
		m_ProcessList.InsertItem(i, m_PInfo.m_PorcessPe32[i].szExeFile);
		CString CPID;
		CPID.Format("%d", m_PInfo.m_PorcessPe32[i].th32ProcessID);
		m_ProcessList.SetItemText(i, 1, CPID);
	}
}



void CProcessManagerDlg::OnNMDblclkkProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_DllList.DeleteAllItems();
	int nID = pNMItemActivate->iItem;
	CString pID = m_ProcessList.GetItemText(nID, 1);
	m_PInfo.GetDllInfo(_ttoi(pID));
	for (int i = 0; i < m_PInfo.m_DllMe32.size(); i++)
	{
		m_DllList.InsertItem(i, m_PInfo.m_DllMe32[i].szModule);
		m_DllList.SetItemText(i, 1, m_PInfo.m_DllMe32[i].szExePath);
	}
	*pResult = 0;
}


void CProcessManagerDlg::OnBnClickedStartprocess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCreateProecssDialog cpd;
	if (cpd.DoModal() == IDOK)
	{
		int Np = m_PInfo.CreateNewProcess(cpd.m_path);
		if (Np == TRUE)
		{
			MessageBox("�����ɹ�");
			GetProcessInfo();
		}
		else
		{
			MessageBox("����ʧ��");
		}
	}
}


void CProcessManagerDlg::OnBnClickedShutdown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_ProcessList.GetFirstSelectedItemPosition();
	int index = m_ProcessList.GetNextSelectedItem(pos);
	CString pID = m_ProcessList.GetItemText(index, 1);
	if (pID.IsEmpty())
	{
		MessageBox("��ѡ��һ������");
	}
	else
	{
		if (m_PInfo.ShutDownProcess(_ttoi(pID)))
		{
			MessageBox("�رս��̳ɹ�");
			GetProcessInfo();
		}
		else
		{
			MessageBox("�رս���ʧ��");
		}
	}
}


void CProcessManagerDlg::OnBnClickedStop() //��ͣ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSRProcessDialog SRD;
	if (SRD.DoModal() == IDOK)
	{
		if (m_PInfo.StopProcess(_ttoi(SRD.m_Pid)))
		{
			MessageBox("��ͣ���̳ɹ�������IDΪ��" + SRD.m_Pid);
		}
		else
		{
			MessageBox("��ͣ����ʧ�ܣ�����IDΪ��" + SRD.m_Pid);
		}
	}
}


void CProcessManagerDlg::OnBnClickedRestart()  //�ָ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSRProcessDialog SRD;
	if (SRD.DoModal() == IDOK)
	{
		if (m_PInfo.RestartProcess(_ttoi(SRD.m_Pid)))
		{
			MessageBox("�ָ����̳ɹ�������IDΪ��" + SRD.m_Pid);
		}
		else
		{
			MessageBox("�ָ����̳ɹ�������IDΪ��" + SRD.m_Pid);
		}
	}
}


void CProcessManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetProcessInfo();
	CDialogEx::OnTimer(nIDEvent);
}
