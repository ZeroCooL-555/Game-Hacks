#include "Game.h"
#include "mem.h"
#include "Hacks.h"
#include "DirectX.h"
#include "menu.h"

Monitor monitor;
ProcessHandling setup;
EntityINFO Enemies[MAX_ENTITIES];
Local LocalPlayer;


void EntityINFO::ReadEnemiesData(int enemy)
{
	Enemies[enemy].entlist = ReadMemory<DWORD>(setup.Handle, (setup.modulebase + ENTITY_LIST));
	Enemies[enemy].CurrentEnemy = ReadMemory<DWORD>(setup.Handle, (Enemies[enemy].entlist + enemy * ENTITY_LOOP));
	Enemies[enemy].Position = ReadMemory<Vec3>(setup.Handle, (Enemies[enemy].CurrentEnemy + ENTITY_POS));
	Enemies[enemy].HeadPosition = ReadMemory<Vec3>(setup.Handle, (Enemies[enemy].CurrentEnemy + ENTITY_HEADPOS));
	Enemies[enemy].EntityHealth = ReadMemory<int>(setup.Handle, (Enemies[enemy].CurrentEnemy + ENTITY_HEALTH_OFF));
}

void Local::ReadLP()
{
	LocalPlayer.local_pos = ReadMemory<Vec3>(setup.Handle, (PLAYERBASE + LOCAL_POS_OFF));
	LocalPlayer.Health = ReadMemory<int>(setup.Handle, (PLAYER_HEALTH));
	LocalPlayer.Team = ReadMemory<int>(setup.Handle, (PLAYER_ITEAMNUM));
}

void Hacks::ESP(bool bESP, bool bCorner, bool bBorder, bool bSnaplines, bool bDistance)
{
	float Matrix[16];
	int LineThickness = 2;
	Vec2 vScreen;
	Vec2 vHead;

		for (auto i = 0; i < MAX_ENTITIES; i++)
		{
			LocalPlayer.ReadLP();
			Enemies[i].ReadEnemiesData(i);
			if (Enemies[i].CurrentEnemy != NULL)
			{
				if (Enemies[i].EntityHealth > 0)
				{
					ReadProcessMemory(setup.Handle, (float*)VIEW_MATRIX, &Matrix, sizeof(Matrix), 0);

					if (WorldToScreen(Enemies[i].Position, vScreen, Matrix, monitor.x, monitor.y))
					{
						if (WorldToScreen(Enemies[i].HeadPosition, vHead, Matrix, monitor.x, monitor.y))
						{

							if (bESP)
							{
								// Calculate ESP
								float BoxHeight = vHead.y - vScreen.y;
								float width = BoxHeight / 2;
								float center = width / -2;
								float HealthBar = BoxHeight / 100 * Enemies[i].EntityHealth;

								if (bCorner)
								{
									DrawCornerBox(vScreen.x + center, vScreen.y, width, BoxHeight, LineThickness, Color::red);

									// Draw HealthBar
									DrawBorderBox((vScreen.x - center - 8), vScreen.y, -1, HealthBar, LineThickness, Color::green);
								}
								if (bBorder)
								{
									// Draw Box ESP
									DrawBorderBox(vScreen.x + center, vScreen.y, width, BoxHeight, LineThickness, Color::red);

									// Draw HealthBar
									DrawBorderBox((vScreen.x - center - 8), vScreen.y, -1, HealthBar, LineThickness, Color::green);
								}

								if (bDistance)
								{
									char dist_display[255];
									sprintf_s(dist_display, sizeof(dist_display), "%i m", (int)(Get3Ddistance(LocalPlayer.local_pos, Enemies[i].Position)));
									DrawString((char*)dist_display, vScreen.x, vScreen.y, Color::yellow, pFontMenu);

								}


								if (bSnaplines)
								{
									DrawLine(vScreen.x, vScreen.y, (monitor.x / 2), monitor.y, LineThickness, Color::cyan);
								}
							}
						}
					}
				}
			}
		}
}

void Hacks::VSAT(bool state)
{
	if (state)
	{

		for (short int i = 0; i < 5; i++)
			WriteMemory<BYTE>(setup.Handle, (VSAT_ADDR), 1);
	}
	else
	{

		for (short int i = 0; i < 5; i++)
			WriteMemory<BYTE>(setup.Handle, (VSAT_ADDR), 0);
	}
}

void Hacks::MAX_FOV(bool state)
{
	if (state)
	{
		if (LocalPlayer.Health > 0)
		{
			WriteMemory<float>(setup.Handle, (FOV_ADDR), 120);
		}
	}
	else
	{
		WriteMemory<float>(setup.Handle, (FOV_ADDR), 90);
	}
}