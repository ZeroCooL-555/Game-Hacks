#pragma once
#include <Windows.h>

struct ProcessHandling
{
	DWORD modulebase;
	DWORD ProcID;
	HANDLE Handle;
	HWND msgHandle;
};

template<typename _ret_t> _ret_t ReadMemory(HANDLE phandle, uintptr_t address)
{
	_ret_t ret;
	ReadProcessMemory(phandle, (void*)address, &ret, sizeof(_ret_t), 0);
	return ret;
}

template<typename _ret_t> void WriteMemory(HANDLE phandle, uintptr_t address, _ret_t value)
{
	_ret_t ret = value;
	WriteProcessMemory(phandle, (void*)address, &ret, sizeof(_ret_t), 0);
}

uintptr_t GetModBase(DWORD ProcID, const char* ModuleName);
uintptr_t GetProc(const char* ProcName);
extern ProcessHandling setup;