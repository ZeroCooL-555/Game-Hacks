#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

uintptr_t GetPID(const wchar_t* procName) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	uintptr_t pID = NULL;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry)) {
		do {
			if (_wcsicmp(entry.szExeFile, procName) == 0) {
				pID = entry.th32ProcessID;
				break;
			}
		} while (Process32Next(snapshot, &entry));
	}
	CloseHandle(snapshot);
	return pID;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t FindPTR(HANDLE hproc, uintptr_t ptr, std::vector<unsigned int>offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hproc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}

template<typename _ret_t> _ret_t ReadMemory(HANDLE phandle, uintptr_t address)
{
	_ret_t ret;
	ReadProcessMemory(phandle, (void*)address, &ret, sizeof(_ret_t), 0);
	return ret;
};

template<typename _ret_t> void WriteMemory(HANDLE phandle, uintptr_t address, _ret_t value)
{
	_ret_t ret = value;
	WriteProcessMemory(phandle, (void*)address, &ret, sizeof(_ret_t), 0);
};
