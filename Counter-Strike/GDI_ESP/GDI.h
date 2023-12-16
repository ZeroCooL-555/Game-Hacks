#pragma once
#include <windows.h>
#include <iostream>

struct ESP
{
	// Variables For ESP
	HBRUSH Brush;
	HFONT Font;
	HDC game_window;
	HWND game;
	COLORREF TextColor;
	HPEN SnaplinePen = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
}esp;

float ScreenX = GetSystemMetrics(SM_CXSCREEN); // Get Width of screen
float ScreenY = GetSystemMetrics(SM_CYSCREEN); // Get Height of screen

// Structs to store Coords
struct Vec4
{
	float x, y, z, w;
};

// Vec4 stores our clipcoords

struct Vec3
{
	float x, y, z;
};

// Vec3 stores our position

struct Vec2
{
	float x, y;
};

// ESP FUNCTIONS
void DrawFilledRect(int x, int y, int w, int h, int r, int g, int b)
{
	esp.Brush = CreateSolidBrush(RGB(r, g, b));
	RECT rect = { x, y, x + w, y + h };
	FillRect(esp.game_window, &rect, esp.Brush);
	DeleteObject(esp.Brush);
}

void DrawBorderBox(int x, int y, int w, int h, int thickness, int r, int g, int b)
{

	DrawFilledRect(x, y, w, thickness, r, g, b); // bottom horizontal Line

	DrawFilledRect(x, y, thickness, h, r, g, b); // right vertical Line

	DrawFilledRect((x + w), y, thickness, h, r, g, b); // left vertical Line

	DrawFilledRect(x, y + h, w + thickness, thickness, r, g, b); // Top horizontal line
}

void DrawLine(int x, int y, HPEN Pen) // Draws the Snaplines
{
	MoveToEx(esp.game_window, (ScreenX / 2), (ScreenY), NULL);
	LineTo(esp.game_window, x, y);
	SelectObject(esp.game_window, esp.SnaplinePen);
}

void DrawString(int x, int y, COLORREF color, const char* text) // Draws the text on screen
{
	SetTextAlign(esp.game_window, TA_CENTER | TA_NOUPDATECP);

	//TA_NOUPDATECP: The current position is not updated after each text output call.

	SetBkColor(esp.game_window, RGB(0, 0, 0));

	SetBkMode(esp.game_window, TRANSPARENT);

	// TRANSPARENT: Background remains untouched.

	SetTextColor(esp.game_window, color);

	SelectObject(esp.game_window, esp.Font);

	TextOutA(esp.game_window, x, y, text, strlen(text));

	DeleteObject(esp.Font);
}

float Get3Ddistance(Vec3 LocalPlayerCoords, Vec3 EnemyCoords)
{
	return (float)(sqrt(
		pow(LocalPlayerCoords.x - EnemyCoords.x, 2.0) +
		pow(LocalPlayerCoords.y - EnemyCoords.y, 2.0) +
		pow(LocalPlayerCoords.z - EnemyCoords.z, 2.0))) * 0.0254f;
}
