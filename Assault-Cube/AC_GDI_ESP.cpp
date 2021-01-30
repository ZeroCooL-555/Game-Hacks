#include <iostream>
#include <Windows.h>

// Essential Vars
DWORD entityListStart = 0x0050F4F4;
DWORD viewMatrix = 0x501AE8;
HWND Gamewindow; // Handle to a window
HBRUSH Brush; // Handle to a brush
HDC AC_Desktop; // Allows to draw (HANDLE TO DEVICE CONTEXT)
DWORD amount_of_players;
HPEN SnaplineColor;
float Matrix[16];


//Handle Variables
HANDLE Handle;
DWORD ProcID;

float ScreenX = GetSystemMetrics(SM_CXSCREEN);
float ScreenY = GetSystemMetrics(SM_CYSCREEN);


struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

struct Vec2
{
	float x, y;
};

bool WorldToScreen(Vec3 pos, Vec2 &screen, float matrix[16], int windowWidth, int windowHeight) // 3D to 2D
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vec4 clipCoords;
	clipCoords.x = pos.x*matrix[0] + pos.y*matrix[4] + pos.z*matrix[8] + matrix[12];
	clipCoords.y = pos.x*matrix[1] + pos.y*matrix[5] + pos.z*matrix[9] + matrix[13];
	clipCoords.z = pos.x*matrix[2] + pos.y*matrix[6] + pos.z*matrix[10] + matrix[14];
	clipCoords.w = pos.x*matrix[3] + pos.y*matrix[7] + pos.z*matrix[11] + matrix[15];


	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	//Transform to window coordinates
	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

void DrawFilledRect(int x, int y, int w, int h)
{
	RECT rect = { x, y, x + w, y + h };
	FillRect(AC_Desktop, &rect, Brush);
}

void DrawBorderBox(int x, int y, int w, int h, int thickness)
{

	DrawFilledRect(x, y, w, thickness); // bottom horizontal Line

	DrawFilledRect(x, y, thickness, h); // right vertical Line

	DrawFilledRect((x + w), y, thickness, h); // left vertical Line

	DrawFilledRect(x, y + h, w + thickness, thickness); // Top horizontal line
}

void DrawLine(int x, int y, HPEN LineColor) // Draws the Snaplines
{
	MoveToEx(AC_Desktop, (1024 / 2), (768 / 2), NULL);
	LineTo(AC_Desktop, x, y);
	SnaplineColor = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	SelectObject(AC_Desktop, SnaplineColor);
}


struct Entity
{
	DWORD entityList;
	DWORD Current_Entity;
	Vec3 entPos; // Foot Position
	Vec3 entHeadPos; // Head Position

	void ReadInformation(int player)
	{
		ReadProcessMemory(Handle, (LPVOID)(entityListStart + 0x4), &entityList, sizeof(entityList), 0);
		ReadProcessMemory(Handle, (LPVOID)(entityList + player * 0x4), &Current_Entity, sizeof(Current_Entity), 0);
		ReadProcessMemory(Handle, (LPVOID)(Current_Entity + 0x34), &entPos, sizeof(entPos), 0);
		ReadProcessMemory(Handle, (LPVOID)(Current_Entity + 0x4), &entHeadPos, sizeof(entHeadPos), 0);
	}
}PlayerList[32];

Vec2 vHead;
Vec2 vScreen;

void ESP()
{
	ReadProcessMemory(Handle, (LPVOID)viewMatrix, &Matrix, sizeof(Matrix), 0);
	ReadProcessMemory(Handle, (LPVOID)0x50F500, &amount_of_players, sizeof(amount_of_players), 0);
	for (int i = 0; i < amount_of_players; i++)
	{
		PlayerList[i].ReadInformation(i);


		if (WorldToScreen(PlayerList[i].entPos, vScreen, Matrix, 1024, 768))
		{
			if (WorldToScreen(PlayerList[i].entHeadPos, vHead, Matrix, 1024, 768))
			{
				//Creates the head height
				float head = vHead.y - vScreen.y;
				//Creates Width
				float width = head / 2;
				//Creates Center
				float center = width / -2;
				//Creates Extra area above head
				float extra = head / -5;

				DrawBorderBox(vScreen.x + center, vScreen.y, width, head - 5, 1);
				DrawLine(vScreen.x, vScreen.y, SnaplineColor);
			}
		}
	}
}

int main()
{
	Gamewindow = FindWindowA(0, "AssaultCube");
	GetWindowThreadProcessId(Gamewindow, &ProcID);
	Handle = OpenProcess(PROCESS_ALL_ACCESS, false, ProcID);
	AC_Desktop = GetDC(Gamewindow);
	Brush = CreateSolidBrush(RGB(0, 0, 255));

	while (true)
	{
		ESP();
	}
}
