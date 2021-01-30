#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "GDI.h"

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

struct GameVars
{
	// entity & localplayer
	DWORD entitylist = 0x4DA1F24;
	DWORD LocalPlayer = 0xD8A2BC;

	// FOR ESP
	DWORD dwViewMatrix = 0x4D93824;
	DWORD m_dwBoneMatrix = 0x26A8;
	DWORD dw_position = 0x138;
	DWORD m_bDormant = 0xED;

	// FOR BHOP
	DWORD dwForceJump = 0x524BE84;
	DWORD m_fFlags = 0x104;

	// FOR CHECKS
	DWORD m_iTeamNum = 0xF4;
	DWORD m_iHealth = 0x100;
	DWORD m_bIsScoped = 0x3928;
	DWORD m_ArmorValue = 0xB378;

	// FOR NO FLASH
	DWORD m_flFlashDuration = 0xA420;

	// For FOV
	DWORD m_iFOV = 0x31E4;

	// Sensor Check (GLOW VARIABLE)
	DWORD m_flDetectedByEnemySensorTime = 0x3978;

	// For TriggerBot
	DWORD dwForceAttack = 0x31D3460;
	DWORD m_iCrosshairId = 0xB3E4;

}game;

struct GameHandling
{
	// Necessary variables
	DWORD process;
	uintptr_t gamemodule;
	HANDLE readproc;
}handles;

struct entity
{
	// Read & store All Necessary entity info

	DWORD Current_entity;
	DWORD Bone;
	DWORD PlayerResource;
	Vec3 entPos;
	Vec3 entBonePos;
	int Team;
	int Health;
	bool Dormant;
	int Armor;

	void ReadentityInfo(int player)
	{
		ReadProcessMemory(handles.readproc, (LPVOID)(handles.gamemodule + game.entitylist + player * 0x10), &Current_entity, sizeof(Current_entity), 0);
		ReadProcessMemory(handles.readproc, (Vec3*)(Current_entity + game.dw_position), &entPos, sizeof(entPos), 0);
		ReadProcessMemory(handles.readproc, (DWORD*)(Current_entity + game.m_dwBoneMatrix), &Bone, sizeof(Bone), 0);
		ReadProcessMemory(handles.readproc, (Vec3*)(Bone + 0x30 * 9 + 0x0C), &entBonePos.x, sizeof(entBonePos.x), 0);
		ReadProcessMemory(handles.readproc, (Vec3*)(Bone + 0x30 * 9 + 0x1C), &entBonePos.y, sizeof(entBonePos.y), 0);
		ReadProcessMemory(handles.readproc, (Vec3*)(Bone + 0x30 * 9 + 0x2C), &entBonePos.z, sizeof(entBonePos.z), 0);
		ReadProcessMemory(handles.readproc, (int*)(Current_entity + game.m_iTeamNum), &Team, sizeof(Team), 0);
		ReadProcessMemory(handles.readproc, (int*)(Current_entity + game.m_iHealth), &Health, sizeof(Health), 0);
		ReadProcessMemory(handles.readproc, (int*)(Current_entity + game.m_ArmorValue), &Armor, sizeof(Armor), 0);
		ReadProcessMemory(handles.readproc, (bool*)(Current_entity + game.m_bDormant), &Dormant, sizeof(Dormant), 0);
	}
}PlayerList[64];

struct me
{
	// Read & Store needed player info

	DWORD Player;
	int Team;
	int Health;
	int Armor;
	Vec3 Coords;

	void ReadMyINFO()
	{
		ReadProcessMemory(handles.readproc, (LPVOID)(handles.gamemodule + game.LocalPlayer), &Player, sizeof(Player), 0);
		ReadProcessMemory(handles.readproc, (LPINT)(Player + game.m_iTeamNum), &Team, sizeof(Team), 0);
		ReadProcessMemory(handles.readproc, (Vec3*)(Player + game.dw_position), &Coords, sizeof(Coords), 0);
		ReadProcessMemory(handles.readproc, (int*)(Player + game.m_iHealth), &Health, sizeof(Health), 0);
		ReadProcessMemory(handles.readproc, (int*)(Player + game.m_ArmorValue), &Armor, sizeof(Armor), 0);
	}
}Me;

bool Glow_on = false;
bool bhop_on = false;
bool noflash_on = false;
bool triggerbot = false;
bool enable_esp = false;
bool change_fov_on = false;
bool Toggle_Status = false;
bool change_fov = false;
bool Menu_Refresh = true;

void bhop()
{
	BYTE Force_Jump = 6;
	int Flags;
	DWORD MyPlayer;
	ReadProcessMemory(handles.readproc, (LPVOID)(handles.gamemodule + game.LocalPlayer), &MyPlayer, sizeof(MyPlayer), 0);
	if (MyPlayer == NULL)
	{
		while (MyPlayer == NULL)
		{
			ReadProcessMemory(handles.readproc, (LPVOID)(handles.gamemodule + game.LocalPlayer), &MyPlayer, sizeof(MyPlayer), 0);
		}
	}
	ReadProcessMemory(handles.readproc, (PBYTE)(MyPlayer + game.m_fFlags), &Flags, sizeof(Flags), 0);

	/*
	Flags: 257 = on Ground, 256 = Jumping
	dwForceJump: 4 = on ground, 5 = Jumping, 6 = Reset to 4 to be able to jump again
	*/

	if (GetAsyncKeyState(VK_SPACE) && Flags & (1 << 0))
	{
		WriteProcessMemory(handles.readproc, (PBYTE)(handles.gamemodule + game.dwForceJump), &Force_Jump, sizeof(Force_Jump), 0);
		//Sleep(1);
	}

	/*
	(1 << 0)
	this is a bit compare,
	<< (left shift) Takes two numbers,
	left shifts the bits of the first operand, the second operand decides the number of places to shift.
	*/
}

void NoFlash()
{

	int FlashDuration;
	int noflashVal = 0;
	if (Me.Player == NULL)
	{
		while (Me.Player == NULL)
		{
			ReadProcessMemory(handles.readproc, (LPVOID)(handles.gamemodule + game.LocalPlayer), &Me.Player, sizeof(Me.Player), 0);
		}
	}
	ReadProcessMemory(handles.readproc, (LPINT)(Me.Player + game.m_flFlashDuration), &FlashDuration, sizeof(FlashDuration), 0);
	if (FlashDuration > 0)
	{
		WriteProcessMemory(handles.readproc, (LPINT)(Me.Player + game.m_flFlashDuration), &noflashVal, sizeof(noflashVal), 0);
	}
}

void ChangeFOV()
{
	// Check if scoped
	int Scoped;
	ReadProcessMemory(handles.readproc, (LPINT)(Me.Player + game.m_bIsScoped), &Scoped, sizeof(Scoped), 0);
	int NewFov = 120;
	
	if (Scoped == 1)
	{
		// Do nothing XD
	}
	else
	{
		WriteProcessMemory(handles.readproc, (LPINT)(Me.Player + game.m_iFOV), &NewFov, sizeof(NewFov), 0);
	}
	if (Scoped == 2)
	{
		// Do nothing XD
	}
	else
	{
		WriteProcessMemory(handles.readproc, (LPINT)(Me.Player + game.m_iFOV), &NewFov, sizeof(NewFov), 0);
	}
}

void Glow()
{
	for (unsigned int i = 0; i < 64; i++)
	{
		DWORD entity;
		float Glow_ON = 10000.f;
		ReadProcessMemory(handles.readproc, (LPVOID)(handles.gamemodule + game.entitylist + i * 0x10), &entity, sizeof(entity), nullptr);
		WriteProcessMemory(handles.readproc, (PFLOAT*)(entity + game.m_flDetectedByEnemySensorTime), &Glow_ON, sizeof(Glow_ON), nullptr);
	}
}

void GlowOFF()
{
	for (unsigned int i = 0; i < 64; i++)
	{
		DWORD entity;
		float Glow_OFF = 0;
		ReadProcessMemory(handles.readproc, (LPVOID)(handles.gamemodule + game.entitylist + i * 0x10), &entity, sizeof(entity), nullptr);
		WriteProcessMemory(handles.readproc, (PFLOAT*)(entity + game.m_flDetectedByEnemySensorTime), &Glow_OFF, sizeof(Glow_OFF), nullptr);
	}
}

void TriggerBot()
{
	int attack = 0;
	int crosshairID = 0;
	ReadProcessMemory(handles.readproc, (BYTE*)(Me.Player + game.m_iCrosshairId), &crosshairID, sizeof(crosshairID), nullptr);

	if (crosshairID != 0 && crosshairID < 64)
	{
		attack = 5;
		Sleep(1);
		WriteProcessMemory(handles.readproc, (BYTE*)(handles.gamemodule + game.dwForceAttack), &attack, sizeof(attack), nullptr);
	}
	else
	{
		attack = 4;
		WriteProcessMemory(handles.readproc, (BYTE*)(handles.gamemodule + game.dwForceAttack), &attack, sizeof(attack), nullptr);
	}
}

bool WorldToScreen(Vec3 pos, Vec2 &screen, float matrix[16], int windowWidth, int windowHeight) // converts 3D coords to 2D coords
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vec4 clipCoords;
	clipCoords.x = pos.x*matrix[0] + pos.y*matrix[1] + pos.z*matrix[2] + matrix[3];
	clipCoords.y = pos.x*matrix[4] + pos.y*matrix[5] + pos.z*matrix[6] + matrix[7];
	clipCoords.z = pos.x*matrix[8] + pos.y*matrix[9] + pos.z*matrix[10] + matrix[11];
	clipCoords.w = pos.x*matrix[12] + pos.y*matrix[13] + pos.z*matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f) // if the camera is behind our player don't draw, i think?
		return false;


	Vec3 NDC;
	// Normalize our coords
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	// Convert to window coords (x,y)
	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

void ESP()
{
	Vec2 vHead;
	Vec2 vScreen;

	float Matrix[16]; // [4][4]: 4*4 = 16
	ReadProcessMemory(handles.readproc, (PFLOAT)(handles.gamemodule + game.dwViewMatrix), &Matrix, sizeof(Matrix), 0);

	for (int i = 0; i < 32; i++) // For loop to loop through all the entities
	{
		PlayerList[i].ReadentityInfo(i);
		Me.ReadMyINFO();
		if (PlayerList[i].Current_entity != NULL)
		{
			if (PlayerList[i].Current_entity != Me.Player)
			{
				if (!PlayerList[i].Dormant) // if the players are getting updated by the server
				{
					if (PlayerList[i].Health > 0) // if the entities are not dead
					{
						if (Me.Health > 0)
						{
							if (WorldToScreen(PlayerList[i].entPos, vScreen, Matrix, ScreenX, ScreenY))
							{
								if (WorldToScreen(PlayerList[i].entBonePos, vHead, Matrix, ScreenX, ScreenY))
								{
									//	ESP Box Calculations
									float BoxHeight = vHead.y - vScreen.y; // head position.y - foot position.y
									float width = BoxHeight / 2;
									float center = width / -2;
									float HealthBar = BoxHeight / 100 * PlayerList[i].Health;
									float ArmorBar = BoxHeight / 100 * PlayerList[i].Armor;

									if (PlayerList[i].Team == Me.Team)
									{
										continue;
									}
									else
									{
										// Draws Enemy ESP
										
										// Draw Distance
										char Display_Distance[255];
										sprintf_s(Display_Distance, sizeof(Display_Distance), "%im", (int)(Get3Ddistance(Me.Coords, PlayerList[i].entPos)));
										DrawString(vScreen.x - center - 8, vScreen.y + 2, RGB(255, 179, 25), Display_Distance);

										// Draw Rectangle Box ESP
										DrawBorderBox(vScreen.x + center, vScreen.y, width - 5, BoxHeight - 10, 2, 255, 0, 0);


										// Draw Snap Lines
										DrawLine(vScreen.x, vScreen.y, esp.SnaplinePen);

										// Draw Health Bar
										DrawFilledRect(vScreen.x - center - 8, vScreen.y, - 3, HealthBar, 0, 255, 0); // Draw Green Health Bar over Red Bar

										// Draw Armor Bar
										DrawFilledRect(vScreen.x + center + 8, vScreen.y, - 3, ArmorBar, 255, 255, 255);

									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void DrawToggleStatus()
{
	if (Glow_on)
	{
		DrawString((ScreenX/2), 100, RGB(0, 255, 0), "[F1] GLOW: ON");
	}
	else
	{
		DrawString((ScreenX/2), 100, RGB(255, 0, 0), "[F1] GLOW: OFF");
	}
	if (bhop_on)
	{
		DrawString((ScreenX/2), 120, RGB(0, 255, 0), "[F2] BHOP: ON");
	}
	else
	{
		DrawString((ScreenX/2), 120, RGB(255, 0, 0), "[F2] BHOP: OFF");
	}
	if (noflash_on)
	{
		DrawString((ScreenX/2), 140, RGB(0, 255, 0), "[F3] NOFLASH: ON");
	}
	else
	{
		DrawString((ScreenX/2), 140, RGB(255, 0, 0), "[F3] NOFLASH: OFF");
	}
	if (enable_esp)
	{
		DrawString((ScreenX/2), 160, RGB(0, 255, 0), "[F4] ESP: ON");
	}
	else
	{
		DrawString((ScreenX/2), 160, RGB(255, 0, 0), "[F4] ESP: OFF");
	}
	if (change_fov_on)
	{
		DrawString((ScreenX / 2), 180, RGB(0, 255, 0), "[F6] 120 FOV");
	}
	else
	{
		DrawString((ScreenX / 2), 180, RGB(255, 0, 0), "[F6] 120 FOV");
	}
	if (triggerbot)
	{
		DrawString((ScreenX/2), 200, RGB(0, 255, 0), "[MSB1] TRIGGER: ON");
	}
	else
	{
		DrawString((ScreenX/2), 200, RGB(255, 0, 0), "[MSB1] TRIGGER: OFF");
	}
}

int main()
{
	SetConsoleTitleA("Ice - ZeroC001");
	handles.process = GetProc(L"csgo.exe");
	if (handles.process == NULL)
	{
		std::cout << "Failed to Get Process";
		getchar();
		exit(0);
	}
	handles.gamemodule = GetModBase(handles.process, L"client.dll");
	if (handles.gamemodule == NULL)
	{
		std::cout << "Failed to Get Module 'client.dll'" << std::endl;
		getchar();
		exit(0);
	}
	handles.readproc = OpenProcess(PROCESS_ALL_ACCESS, false, handles.process);
	esp.game = FindWindowA(0, "Counter-Strike: Global Offensive");
	esp.game_window = GetDC(esp.game);

	
	while (handles.process != NULL)
	{
		if (Glow_on)
			Glow();
		if (bhop_on)
			bhop();
		if (noflash_on)
			NoFlash();
		if (triggerbot)
			TriggerBot();
		if (enable_esp)
			ESP();
		if (change_fov_on)
			ChangeFOV();
		if (Toggle_Status)
			DrawToggleStatus();
		

		

		if (Menu_Refresh)
		{
			system("cls");
			std::cout << "[F1] Glow: " << (Glow_on ? "ON" : "OFF") << std::endl;
			std::cout << "[F2] BHOP: " << (bhop_on ? "ON" : "OFF") << std::endl;
			std::cout << "[F3] NOFLASH: " << (noflash_on ? "ON" : "OFF") << std::endl;
			std::cout << "[F4] ESP: " << (enable_esp ? "ON" : "OFF") << std::endl;
			std::cout << "[MSB1] TRIGGER: " << (triggerbot ? "ON" : "OFF") << std::endl;
			std::cout << "[INSERT] Draw Toggle Status" << std::endl;
			Menu_Refresh = false;
		}


		if (GetAsyncKeyState(VK_F1) & 1)
		{
			Glow_on = !Glow_on;
			if (Glow_on)
			{
				Menu_Refresh = !Menu_Refresh;
			}
			else
			{
				!Glow_on;
				Menu_Refresh = !Menu_Refresh;
				GlowOFF();
			}
		}
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			bhop_on = !bhop_on;
			if (bhop_on)
			{
				Menu_Refresh = !Menu_Refresh;
			}
			else
			{
				!bhop_on;
				Menu_Refresh = !Menu_Refresh;
			}
		}
		if (GetAsyncKeyState(VK_F3) & 1)
		{
			noflash_on = !noflash_on;
			if (noflash_on)
			{
				Menu_Refresh = !Menu_Refresh;
			}
			else
			{
				!noflash_on;
				Menu_Refresh = !Menu_Refresh;
			}
		}
		if (GetAsyncKeyState(VK_F4) & 1)
		{
			enable_esp = !enable_esp;
			if (enable_esp)
			{
				Menu_Refresh = !Menu_Refresh;
			}
			else
			{
				!enable_esp;
				Menu_Refresh = !Menu_Refresh;
			}
		}
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			change_fov_on = !change_fov_on;
			if (change_fov_on)
			{
				Menu_Refresh = !Menu_Refresh;
			}
			else
			{
				!change_fov_on;
				Menu_Refresh = !Menu_Refresh;
			}
		}
		if (GetAsyncKeyState(VK_XBUTTON1) & 1)
		{
			triggerbot = !triggerbot;
			if (triggerbot)
			{
				Menu_Refresh = !Menu_Refresh;
			}
			else
			{
				!triggerbot;
				Menu_Refresh = !Menu_Refresh;
			}
		}
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			Toggle_Status = !Toggle_Status;
		}
		else
		{
			!Toggle_Status;
		}
	}
	CloseHandle(handles.readproc);
}
