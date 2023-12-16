#include <Windows.h>
#include <TlHelp32.h>

uintptr_t GetModBase(DWORD ProcID, const wchar_t* ModuleName)
{
	uintptr_t modbaseAddr = 0;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcID);
	if (hsnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hsnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, ModuleName))
				{
					modbaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hsnap, &modEntry));
		}
	}
	CloseHandle(hsnap);
	return modbaseAddr;
}

DWORD GetProc(const wchar_t* ProcName)
{
	DWORD ProcID = 0;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 ProcEntry;
		ProcEntry.dwSize = sizeof(ProcEntry);
		if (Process32First(hsnap, &ProcEntry))
		{
			do
			{
				if (!_wcsicmp(ProcEntry.szExeFile, ProcName))
				{
					ProcID = ProcEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hsnap, &ProcEntry));
		}
	}
	CloseHandle(hsnap);
	return ProcID;
}
