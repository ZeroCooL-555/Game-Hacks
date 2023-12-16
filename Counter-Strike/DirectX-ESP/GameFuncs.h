#include <Windows.h>
#include <TlHelp32.h>


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


uintptr_t GetModBase(DWORD ProcID, char* ModuleName)
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
				if (!_stricmp(modEntry.szModule, ModuleName))
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

uintptr_t GetProc(char* ProcName)
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
				if (!_stricmp(ProcEntry.szExeFile, ProcName))
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

bool WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight) // converts 3D coords to 2D coords
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

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

float Get3Ddistance(Vec3 LocalPlayerCoords, Vec3 EnemyCoords)
{
	return (float)(sqrt(
		pow(LocalPlayerCoords.x - EnemyCoords.x, 2.0) +
		pow(LocalPlayerCoords.y - EnemyCoords.y, 2.0) +
		pow(LocalPlayerCoords.z - EnemyCoords.z, 2.0))) * 0.0254f;
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

	// Recoil Crosshair
	DWORD m_aimPunchAngle = 0x302C;

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

		// Add 12 to esp box height to get box above player head
		entBonePos.z += 12;
	}
}PlayerList[32];

struct me
{
	// Read & Store needed player info

	DWORD Player;
	int Team;
	int Health;
	int Armor;
	float Matrix[16];
	Vec3 Coords;
	Vec3 pAngle;

	void ReadMyINFO()
	{
		ReadProcessMemory(handles.readproc, (LPVOID)(handles.gamemodule + game.LocalPlayer), &Player, sizeof(Player), 0);
		ReadProcessMemory(handles.readproc, (LPINT)(Player + game.m_iTeamNum), &Team, sizeof(Team), 0);
		ReadProcessMemory(handles.readproc, (Vec3*)(Player + game.dw_position), &Coords, sizeof(Coords), 0);
		ReadProcessMemory(handles.readproc, (int*)(Player + game.m_iHealth), &Health, sizeof(Health), 0);
		ReadProcessMemory(handles.readproc, (int*)(Player + game.m_ArmorValue), &Armor, sizeof(Armor), 0);
		ReadProcessMemory(handles.readproc, (PFLOAT)(handles.gamemodule + game.dwViewMatrix), &Matrix, sizeof(Matrix), 0);
		ReadProcessMemory(handles.readproc, (Vec3*)(Player + game.m_aimPunchAngle), &pAngle, sizeof(pAngle), 0);
	}
}Me;
