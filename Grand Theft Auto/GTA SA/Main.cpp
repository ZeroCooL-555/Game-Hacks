#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "Process.h"

// Addresses
DWORD MONEY_ADDR = 0x810188;
DWORD Player_HealthAddr = 0x7FC7D8;
DWORD Mega_JumpAddr = 0x5E0C94;

// Offset
DWORD Health_offset = 0x540;

// Initialize Handle
HANDLE handle_proc = 0;



int main()
{
	SetConsoleTitleA("GTA:SA External Mod - ZeroCooL");
	DWORD Process = GetProc(L"gta-sa.exe");
	while (Process == NULL)
	{
		std::cout << "Waiting For Game";
		std::cout << ".";
		Sleep(300);
		std::cout << ".";
		Sleep(300);
		std::cout << ".";
		Sleep(300);
		system("cls");
		Process = GetProc(L"gta-sa.exe");
	}
	uintptr_t ModBase = GetModBase(Process, L"gta-sa.exe");
	handle_proc = OpenProcess(PROCESS_ALL_ACCESS, false, Process);
	if (handle_proc == NULL)
	{
		std::cout << "Failed To obtain Handle..." << std::endl;
		getchar();
		exit(0);
	}
	bool MegaJump_enabled = false;
	bool God_enabled = false;
	bool Money_enabled = false;
	bool update_console = true;
	while (true)
	{
		if (update_console)
		{
			system("cls");
			std::cout << "[INS] - Mega Jump: " << (MegaJump_enabled ? "ON" : "OFF") << std::endl;
			std::cout << "[DEL] - GodMode: " << (God_enabled ? "ON" : "OFF") << std::endl;
			std::cout << "[END] - Give Max Money" << std::endl;
			update_console = false;
		}
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			MegaJump_enabled = !MegaJump_enabled;
			update_console = !update_console;
			if (MegaJump_enabled)
			{
				int ON = 1;
				WriteProcessMemory(handle_proc, (BYTE*)(ModBase + Mega_JumpAddr), &ON, sizeof(ON), 0);
			}
			else
			{
				MegaJump_enabled = false;
				!update_console;
				int OFF = 0;
				WriteProcessMemory(handle_proc, (BYTE*)(ModBase + Mega_JumpAddr), &OFF, sizeof(OFF), 0);
			}
		}
		else if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			God_enabled = !God_enabled;
			update_console = !update_console;
			if (God_enabled)
			{
				float GodVal = 98000;
				int HealthValue;
				ReadProcessMemory(handle_proc, (BYTE*)(ModBase + Player_HealthAddr), &HealthValue, sizeof(HealthValue), 0);
				WriteProcessMemory(handle_proc, (BYTE*)(HealthValue + Health_offset), &GodVal, sizeof(GodVal), 0);
			}
			else
			{
				God_enabled = false;
				!update_console;
				float GodVal = 100;
				int HealthValue;
				ReadProcessMemory(handle_proc, (BYTE*)(ModBase + Player_HealthAddr), &HealthValue, sizeof(HealthValue), 0);
				WriteProcessMemory(handle_proc, (BYTE*)(HealthValue + Health_offset), &GodVal, sizeof(GodVal), 0);
			}
		}
		else if (GetAsyncKeyState(VK_END) & 1)
		{
			Money_enabled = !Money_enabled;
			update_console = !update_console;
			if (Money_enabled)
			{
				int MaxCash = 99999999;
				WriteProcessMemory(handle_proc, (BYTE*)(ModBase + MONEY_ADDR), &MaxCash, sizeof(MaxCash), 0);
			}
		}
		Sleep(2);
	}
	CloseHandle(handle_proc);
	exit(0);
}
