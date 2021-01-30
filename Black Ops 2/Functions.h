#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <math.h>

float ScreenX = GetSystemMetrics(SM_CXSCREEN);
float ScreenY = GetSystemMetrics(SM_CYSCREEN);

HWND Gamewindow;
HDC GameWindowDraw;
HBRUSH EnemyBrush;
HFONT Font;
HPEN SnapLine = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
COLORREF TextCOLOR;

COLORREF Green = RGB(0, 255, 0);
COLORREF Red = RGB(255, 0, 0);
COLORREF Dark_tangerine = RGB(255, 179, 25);
COLORREF Yellow = RGB(255, 255, 0);

DWORD ProcID;
HANDLE Handle;

// Toggles
bool ESP = false;
bool vsat = false;
bool Lines = false;
bool Distance = false;
bool show_hide = false;
bool player_fov = false;

struct Vec4
{
	float x, y, z, w;
};

struct Vec3
{
	float x, y, z;
};

struct Vec2
{
	float x, y;
};

DWORD GetModuleBaseAddress(DWORD ProcID, const wchar_t* Modname)
{
	DWORD modbase = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, ProcID);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);

		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, Modname))
				{
					modbase = (DWORD)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modbase;
}
void DrawFilledRect(int x, int y, int w, int h, int r, int g, int b)
{
	EnemyBrush = CreateSolidBrush(RGB(r, g, b));
	RECT rect = { x,y,x + w, y + h };
	FillRect(GameWindowDraw, &rect, EnemyBrush);
	DeleteObject(EnemyBrush);
}

void DrawBorderBox(int x, int y, int w, int h, int thickness, int r, int g, int b) // Body ESP
{
	DrawFilledRect(x, y, w, thickness, r, g, b);

	DrawFilledRect(x, y, thickness, h, r, g, b);

	DrawFilledRect((x + w), y, thickness, h, r, g, b);

	DrawFilledRect(x, y + h, w + thickness, thickness, r, g, b);
}

bool WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
	Vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;


	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

void DrawLine(int x, int y, HPEN LineColor) // Draws the Snaplines
{
	MoveToEx(GameWindowDraw, (ScreenX / 2), (ScreenY), NULL);
	LineTo(GameWindowDraw, x, y);
	SelectObject(GameWindowDraw, SnapLine);
}

void DrawString(int x, int y, COLORREF color, const char* text)
{
	SetTextAlign(GameWindowDraw, TA_CENTER | TA_NOUPDATECP);

	SetBkColor(GameWindowDraw, RGB(0, 0, 0));
	SetBkMode(GameWindowDraw, TRANSPARENT);

	SetTextColor(GameWindowDraw, color);

	SelectObject(GameWindowDraw, Font);

	TextOutA(GameWindowDraw, x, y, text, strlen(text));
}

float Get3Ddistance(Vec3 LocalPlayerCoords, Vec3 EnemyCoords)
{
	return (float)(sqrt(
		pow(LocalPlayerCoords.x - EnemyCoords.x, 2.0) +
		pow(LocalPlayerCoords.y - EnemyCoords.y, 2.0) +
		pow(LocalPlayerCoords.z - EnemyCoords.z, 2.0))) * 0.0254f;
}

void Toggle()
{
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		ESP = !ESP;
	}
	else
	{
		!ESP;
	}

	if (GetAsyncKeyState(VK_F2) & 1)
	{
		vsat = !vsat;
	}
	else
	{
		!vsat;
	}

	if (GetAsyncKeyState(VK_F3) & 1)
	{
		Lines = !Lines;
	}
	else
	{
		!Lines;
	}

	if (GetAsyncKeyState(VK_F4) & 1)
	{
		Distance = !Distance;
	}
	else
	{
		!Distance;
	}

	if (GetAsyncKeyState(VK_F5) & 1)
	{
		player_fov = !player_fov;
	}
	else
	{
		!player_fov;
	}
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show_hide = !show_hide;

	}
	else
	{
		!show_hide;
		DrawString(80, 270, Dark_tangerine, "Hide/Show (INSERT)");
	}
}

void InGame_Menu()
{
	if (ESP)
	{
		DrawString(80, 300, Green, "ESP (F1): ON");
		if (Lines)
			DrawString(80, 340, Green, "Lines (F3): ON");
		else
			DrawString(80, 340, Red, "Lines (F3): OFF");

		if (Distance)
			DrawString(80, 360, Green, "Distance ESP (F4): ON");
		else
			DrawString(80, 360, Red, "Distance ESP (F4): OFF");
	}
	else
	{
		DrawString(80, 300, Red, "ESP (F1): OFF");
	}

	if (vsat)
	{
		DrawString(80, 320, Green, "VSAT (F2): ON");
	}
	else
	{
		DrawString(80, 320, Red, "VSAT (F2): OFF");
	}

	if (player_fov)
	{
		if (ESP)
			DrawString(80, 380, Green, "120 FOV (F5): ON");
		else
			DrawString(80, 340, Green, "120 FOV (F5): ON");
	}
	else
	{
		if (ESP)
			DrawString(80, 380, Red, "120 FOV (F5): OFF");
		else
			DrawString(80, 340, Red, "120 FOV (F5): OFF");

	}
}
