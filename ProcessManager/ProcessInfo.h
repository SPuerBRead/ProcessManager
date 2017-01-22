#pragma once
#include "vector"
#include "Tlhelp32.h"
using namespace std;
class CProcessInfo
{
public:
	CProcessInfo();
	~CProcessInfo();
	BOOL GetProcess();
	vector<PROCESSENTRY32>m_PorcessPe32;
	vector<MODULEENTRY32>m_DllMe32;
	BOOL GetDllInfo(int pID);
	BOOL SeDebugPrivilege();
	int CreateNewProcess(CString path);
	int ShutDownProcess(int pid);
	int StopProcess(int Pid);
	int RestartProcess(int Pid);
};

