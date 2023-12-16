#include "DirectX.h"
#include "GameFuncs.h"
#include <cmath>

IDirect3D9Ex* p_Object = 0;
IDirect3DDevice9Ex* p_Device = 0;
D3DPRESENT_PARAMETERS p_Params;
RECT rc;



int DirectXInit(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(1);

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
		exit(1);

	return 0;
}


int Render()
{

	// Getting game info
	handles.process = GetProc((char*)"csgo.exe");
	handles.gamemodule = GetModBase(handles.process, (char*)"client.dll");
	handles.readproc = OpenProcess(PROCESS_ALL_ACCESS, false, handles.process);
	//End of Game info

	SetConsoleTitleA(".");

	if (tWnd == GetForegroundWindow())
	{
		TCHAR* value = (TCHAR*)tWindowName;

		HWND newhwnd = FindWindow(NULL, value);
		if (newhwnd != NULL) {
			GetWindowRect(newhwnd, &rc);
		}
		else {
			ExitProcess(0);
		}

		p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		p_Device->BeginScene();

		// Render all drawings here

		//Creating Font
		ID3DXFont* pFont;
		D3DXCreateFont(p_Device, 15, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);

		Vec2 vHead;
		Vec2 vScreen;

		// For crosshair
		Vec2 Crosshair2D; // Crosshair recoil position
		int CrosshairSize = 4;
		Vec2 left, right, top, bottom; // used to calculate the crosshair POS

		// Recoil Calculation stuff
		Crosshair2D.x = ScreenX / 2 - (ScreenX / 90 * Me.pAngle.y);
		Crosshair2D.y = ScreenY / 2 + (ScreenY / 90 * Me.pAngle.x);


		// Calculation to form a crosshair like this Ex: +
		left = right = top = bottom = Crosshair2D;

		left.x -= CrosshairSize;
		right.x += CrosshairSize;
		bottom.y += CrosshairSize;
		top.y -= CrosshairSize;
		// End of calculation


		// Draw Left to right  Ex: >-->
		DrawLine(left.x, left.y, right.x, right.y, 2, D3DCOLOR_ARGB(255, 255, 255, 255));

		// Draw Top to bottom Ex: |
		DrawLine(top.x, top.y, bottom.x, bottom.y, 2, D3DCOLOR_ARGB(255, 255, 255, 255));



		for (unsigned int i = 1; i < 32; i++)
		{
			PlayerList[i].ReadentityInfo(i);
			Me.ReadMyINFO();

			if (PlayerList[i].Current_entity != NULL)
			{
				if (PlayerList[i].Current_entity != Me.Player)
				{
					if (!PlayerList[i].Dormant)
					{
						if (PlayerList[i].Health > 0)
						{
							if (Me.Health > 0)
							{
								if (WorldToScreen(PlayerList[i].entPos, vScreen, Me.Matrix, ScreenX, ScreenY))
								{
									if (WorldToScreen(PlayerList[i].entBonePos, vHead, Me.Matrix, ScreenX, ScreenY))
									{

										if (PlayerList[i].Team == Me.Team)
										{
											// Team ESP
											
											// Team SnapLines
											DrawLine(vScreen.x, vScreen.y, (ScreenX / 2), ScreenY, 2, D3DCOLOR_ARGB(255, 0, 255, 0));

											// Team 2D ESP BOX
											DrawEsp2D(vScreen.x, vScreen.y, vHead.x, vHead.y, 2, D3DCOLOR_ARGB(255, 0, 255, 0));
										}
										else
										{
											// Enemy ESP
											
											// Draw SnapLines on Enemies
											DrawLine(vScreen.x, vScreen.y, (ScreenX / 2), ScreenY, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
											

											// Draw 2D ESP BOX
											DrawEsp2D(vScreen.x, vScreen.y, vHead.x, vHead.y, 2, D3DCOLOR_ARGB(255, 255, 0, 0));

										}
									}
								}
							}
						}
					}
				}
			}
		}


		
		p_Device->EndScene();
		p_Device->PresentEx(0, 0, 0, 0, 0);
		return 0;
	}
	CloseHandle(handles.readproc);
}
