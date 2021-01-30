#include <Windows.h>
#include<iostream>
#include "Functions.h"


// Custom Games only
// ===============================================
DWORD vsat_addr = 0x012A0CA4;
DWORD Local_pos_offset = 0x2C;
DWORD LocalBase = 0x2E496518;
DWORD Local_Player_Health = 0x21EF968;
DWORD Player_TeamNum = 0x011497D0;

DWORD EntityList = 0x01DEFC38;
DWORD EntityHealthOffset = 0x1A8;
DWORD EntityLoopDist = 0x8C;
DWORD EntityPosHead = 0x128; // 128 12c 130
DWORD EntityPos = 0x134; // 134 138 13c
DWORD ViewMatrix = 0x01065F40;
DWORD field_of_view = 0x2A430C0;
// ================================================


DWORD moduleBase;

struct EntityINFO
{
	DWORD EntityHealth;
	DWORD entlist;
	DWORD CurrentEnemy;
	Vec3 Position;
	Vec3 HeadPosition;

	void ReadEnemiesData(int enemy)
	{
		ReadProcessMemory(Handle, (LPVOID)(moduleBase + EntityList), &entlist, sizeof(entlist), 0);
		ReadProcessMemory(Handle, (LPVOID)(entlist + enemy * 0x8C), &CurrentEnemy, sizeof(CurrentEnemy), 0);
		ReadProcessMemory(Handle, (Vec3*)(CurrentEnemy + EntityPos), &Position, sizeof(Position), 0);
		ReadProcessMemory(Handle, (Vec3*)(CurrentEnemy + EntityPosHead), &HeadPosition, sizeof(HeadPosition), 0);
		ReadProcessMemory(Handle, (LPVOID)(CurrentEnemy + EntityHealthOffset), &EntityHealth, sizeof(EntityHealth), 0);
	}
}Enemies[64];

struct Local
{
	Vec3 local_pos;
	int Health;
	float FOV;
	int Team;
	
	void ReadLP()
	{
		ReadProcessMemory(Handle, (Vec3*)(LocalBase + Local_pos_offset), &local_pos, sizeof(Vec3), nullptr);
		ReadProcessMemory(Handle, (int*)Local_Player_Health, &Health, sizeof(Health), nullptr);
		ReadProcessMemory(Handle, (int*)Player_TeamNum, &Team, sizeof(Team), nullptr);
	}
}LocalPlayer;

void DrawESP()
{
	float Matrix[16];

	Vec2 vScreen;
	Vec2 vHead;

	ReadProcessMemory(Handle, (float*)ViewMatrix, &Matrix, sizeof(Matrix), 0);

	Toggle();
	if (show_hide)
		InGame_Menu();

	if (ESP)
	{
		for (short int i = 0; i < 64; i++)
		{
			LocalPlayer.ReadLP();
			Enemies[i].ReadEnemiesData(i);
			if (Enemies[i].CurrentEnemy != NULL)
			{
				if (Enemies[i].EntityHealth > 0)
				{
					if (WorldToScreen(Enemies[i].Position, vScreen, Matrix, ScreenX, ScreenY))
					{
						if (WorldToScreen(Enemies[i].HeadPosition, vHead, Matrix, ScreenX, ScreenY))
						{
							float BoxHeight = vHead.y - vScreen.y;
							float width = BoxHeight / 2;
							float center = width / -2;

							if (Distance)
							{
								char dist_display[255];
								sprintf_s(dist_display, sizeof(dist_display), "%i m", (int)(Get3Ddistance(LocalPlayer.local_pos, Enemies[i].Position)));
								DrawString(vScreen.x, vScreen.y, Yellow, dist_display);

							}
							DrawBorderBox(vScreen.x + center, vScreen.y, width, BoxHeight, 2, 255, 0, 0);
							if (Lines)
							{ 
								DrawLine(vScreen.x, vScreen.y, SnapLine); //- Snap Line
							}

							float HealthBar = BoxHeight / 100 * Enemies[i].EntityHealth;

							// Health Bar
							//DrawFilledRect(vScreen.x - center - 1, vScreen.y, -3, BoxHeight, 255, 0, 0);
							DrawFilledRect(vScreen.x - center - 1, vScreen.y, -3, HealthBar, 0, 255, 0);
						}
					}
				}
			}
		}
	}

	if (vsat)
	{
		int VSAT_VALUE_ON = 1;

		for (int i = 0; i < 5; i++)
			WriteProcessMemory(Handle, (LPVOID)(vsat_addr), &VSAT_VALUE_ON, sizeof(VSAT_VALUE_ON), nullptr);
	}
	else
	{
		int VSAT_VALUE_OFF = 0;

		for (int i = 0; i < 5; i++)
			WriteProcessMemory(Handle, (LPVOID)(vsat_addr), &VSAT_VALUE_OFF, sizeof(VSAT_VALUE_OFF), nullptr);
	}

	if (player_fov)
	{
		if (LocalPlayer.Health > 0)
		{
			float fov_val = 120;
			WriteProcessMemory(Handle, (float*)field_of_view, &fov_val, sizeof(fov_val), nullptr);
		}
	}
	else
	{
		float Max_fov = 75;
		WriteProcessMemory(Handle, (float*)field_of_view, &Max_fov, sizeof(Max_fov), nullptr);
	}
}

int main()
{
	SetConsoleTitle(L"Artic - ZeroCoo1");
	Gamewindow = FindWindow(0, L"Call of Duty®: Black Ops II - Multiplayer");

	if (Gamewindow == NULL)
	{
		MessageBoxA(Gamewindow, "Failed To Obtain Game window", 0, 0);
		CloseHandle(Handle);
		exit(0);
	}
	GetWindowThreadProcessId(Gamewindow, &ProcID);
	moduleBase = GetModuleBaseAddress(ProcID, L"t6mp.exe");
	Handle = OpenProcess(PROCESS_ALL_ACCESS, false, ProcID);
	if (Handle == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(Gamewindow, "FAILED TO OPEN PROCESS", 0, 0);
		exit(0);
		CloseHandle(Handle);
	}
	GameWindowDraw = GetDC(Gamewindow);


	while (true)
	{
		DrawESP();
	}
	DeleteObject(GameWindowDraw);
	DeleteObject(SnapLine);
	CloseHandle(Handle);
}
