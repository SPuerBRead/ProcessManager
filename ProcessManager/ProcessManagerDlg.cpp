
// ProcessManagerDlg.cpp : 实现文件
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


// CProcessManagerDlg 对话框



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


// CProcessManagerDlg 消息处理程序

BOOL CProcessManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect Process_rect;
	m_ProcessList.GetClientRect(&Process_rect);
	m_ProcessList.SetExtendedStyle(m_ProcessList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ProcessList.InsertColumn(0, "进程名", LVCFMT_LEFT, Process_rect.Width() * 4 / 5, 0);
	m_ProcessList.InsertColumn(1, "进程ID", LVCFMT_LEFT, Process_rect.Width() / 5, 0);
	//m_ProcessList.InsertColumn(2, "状态", LVCFMT_LEFT);
	m_ProcessList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	CRect Dll_rect;
	m_DllList.GetClientRect(&Dll_rect);
	m_DllList.SetExtendedStyle(m_ProcessList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_DllList.InsertColumn(0, "DLL名", LVCFMT_LEFT, Dll_rect.Width() / 4, 0);
	m_DllList.InsertColumn(1, "DLL路径", LVCFMT_LEFT, Dll_rect.Width() * 3 / 4, 0);
	m_DllList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	GetProcessInfo();
	SetTimer(1, 10000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProcessManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CCreateProecssDialog cpd;
	if (cpd.DoModal() == IDOK)
	{
		int Np = m_PInfo.CreateNewProcess(cpd.m_path);
		if (Np == TRUE)
		{
			MessageBox("创建成功");
			GetProcessInfo();
		}
		else
		{
			MessageBox("创建失败");
		}
	}
}


void CProcessManagerDlg::OnBnClickedShutdown()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_ProcessList.GetFirstSelectedItemPosition();
	int index = m_ProcessList.GetNextSelectedItem(pos);
	CString pID = m_ProcessList.GetItemText(index, 1);
	if (pID.IsEmpty())
	{
		MessageBox("请选中一个进程");
	}
	else
	{
		if (m_PInfo.ShutDownProcess(_ttoi(pID)))
		{
			MessageBox("关闭进程成功");
			GetProcessInfo();
		}
		else
		{
			MessageBox("关闭进程失败");
		}
	}
}


void CProcessManagerDlg::OnBnClickedStop() //暂停
{
	// TODO: 在此添加控件通知处理程序代码
	CSRProcessDialog SRD;
	if (SRD.DoModal() == IDOK)
	{
		if (m_PInfo.StopProcess(_ttoi(SRD.m_Pid)))
		{
			MessageBox("暂停进程成功，进程ID为：" + SRD.m_Pid);
		}
		else
		{
			MessageBox("暂停进程失败，进程ID为：" + SRD.m_Pid);
		}
	}
}


void CProcessManagerDlg::OnBnClickedRestart()  //恢复
{
	// TODO: 在此添加控件通知处理程序代码
	CSRProcessDialog SRD;
	if (SRD.DoModal() == IDOK)
	{
		if (m_PInfo.RestartProcess(_ttoi(SRD.m_Pid)))
		{
			MessageBox("恢复进程成功，进程ID为：" + SRD.m_Pid);
		}
		else
		{
			MessageBox("恢复进程成功，进程ID为：" + SRD.m_Pid);
		}
	}
}


void CProcessManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetProcessInfo();
	CDialogEx::OnTimer(nIDEvent);
}
