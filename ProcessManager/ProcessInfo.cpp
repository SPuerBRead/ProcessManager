#include "stdafx.h"
#include "ProcessInfo.h"
#include "Windows.h"
#include "tlhelp32.h"
#include "vector"
using namespace std;


CProcessInfo::CProcessInfo()
{
	SeDebugPrivilege();
}


CProcessInfo::~CProcessInfo()
{
}


BOOL CProcessInfo::GetProcess()
{
	m_PorcessPe32.clear();
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL); //创建进程快照
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	PROCESSENTRY32 Pe32 = { 0 };
	Pe32.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRet = Process32First(hSnap, &Pe32); //获取线程句柄
	while (bRet)
	{
		if (Pe32.th32ProcessID != 0)
		{
			m_PorcessPe32.push_back(Pe32);
		}
			bRet = Process32Next(hSnap, &Pe32);
	}
	CloseHandle(hSnap);
	return TRUE;
}


BOOL CProcessInfo::GetDllInfo(int pID)
{
	m_DllMe32.clear();
	MODULEENTRY32 Me32 = { 0 };
	Me32.dwSize = sizeof(MODULEENTRY32);
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
	int a = GetLastError();
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	BOOL bRet = Module32First(hSnap, &Me32);
	while (bRet)
	{
		m_DllMe32.push_back(Me32);
		bRet = Module32Next(hSnap, &Me32);
	}
	CloseHandle(hSnap);
	return TRUE;
}


BOOL CProcessInfo::SeDebugPrivilege()
{
	HANDLE hToken = NULL;
	TOKEN_PRIVILEGES PToken;
	LUID LUIDPrivilegeLUID;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken) || !LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &LUIDPrivilegeLUID))
	{
		return FALSE;
	}	
	PToken.PrivilegeCount = 1;
	PToken.Privileges[0].Luid = LUIDPrivilegeLUID;
	PToken.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &PToken, NULL, NULL, NULL))
	{
		return FALSE;
	}
	return TRUE;
}


int CProcessInfo::CreateNewProcess(CString path)
{
	if (path.IsEmpty())
	{
		return FALSE;
	}
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);
	BOOL bRet = CreateProcess(path, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	if (bRet == FALSE)
	{
		return FALSE;
	}
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return TRUE;
}


int CProcessInfo::ShutDownProcess(int pid)
{
	HANDLE TPH = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if(!TerminateProcess(TPH, 0))
	{
		return FALSE;
	}
	return TRUE;
}


 int CProcessInfo::StopProcess(int Pid)
{
	 HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, Pid);
	 if (hSnap == INVALID_HANDLE_VALUE)
	 {
		 return FALSE;
	 }
	 THREADENTRY32 Te32 = { 0 };
	 Te32.dwSize = sizeof(THREADENTRY32);
	 BOOL bRet = Thread32First(hSnap, &Te32);
	 while (bRet)
	 {
		 if (Te32.th32OwnerProcessID == Pid)
		 {
			 HANDLE hthd = OpenThread(THREAD_ALL_ACCESS, FALSE, Te32.th32ThreadID);
			 SuspendThread(hthd);
			 CloseHandle(hthd);
		 }
		 bRet = Thread32Next(hSnap, &Te32);
	 }
	 return TRUE;
}


 int CProcessInfo::RestartProcess(int Pid)
 {
	 HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, Pid);
	 if (hSnap == INVALID_HANDLE_VALUE)
	 {
		 return FALSE;
	 }
	 THREADENTRY32 Te32 = { 0 };
	 Te32.dwSize = sizeof(THREADENTRY32);
	 BOOL bRet = Thread32First(hSnap, &Te32);
	 while (bRet)
	 {
		 if (Te32.th32OwnerProcessID == Pid)
		 {
			 HANDLE hthd = OpenThread(THREAD_ALL_ACCESS, FALSE, Te32.th32ThreadID);
			 ResumeThread(hthd);
			 CloseHandle(hthd);
		 }
		 bRet = Thread32Next(hSnap, &Te32);
	 }
	 return TRUE;
}
