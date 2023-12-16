#include "Main.h"
#include "Game.h"
#include "mem.h"

int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);

const MARGINS Margin = { 0, 0, Width, Height };

char lWindowName[256] = " ";
HWND hWnd;

char tWindowName[256] = "Call of Duty®: Black Ops II - Multiplayer";
HWND tWnd;

RECT tSize;
MSG Message;


int Get_GameInfo()
{
	// Reading Game Info
	setup.ProcID = GetProc("t6mp.exe");
	setup.Handle = OpenProcess(PROCESS_ALL_ACCESS, false, setup.ProcID);
	setup.modulebase = GetModBase(setup.ProcID, "t6mp.exe");


	if (setup.ProcID == NULL || setup.modulebase == NULL || setup.Handle == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(setup.msgHandle, "Failed To Obtain Handle", 0, 0);
		CloseHandle(setup.Handle);
		return -1;
	}
	else
	{

		// Get Coords
		monitor.x = GetSystemMetrics(SM_CXSCREEN);
		monitor.y = GetSystemMetrics(SM_CYSCREEN);
	}

	return 0;
}

int CloseHack()
{
	// Cleanup
	pFontESP->Release();
	pFontMenu->Release();
	pFontBanner->Release();
	p_Object->Release();
	p_Device->Release();
	CloseHandle(setup.Handle);

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
		Get_GameInfo();
		Render();
		break;

	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &Margin);
		break;

	case WM_DESTROY:
		PostQuitMessage(1);
		return 0;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

	WNDCLASSEX wClass;
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WinProc;
	wClass.lpszClassName = lWindowName;
	wClass.lpszMenuName = lWindowName;
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wClass))
		exit(1);

	tWnd = FindWindow(0, tWindowName);
	if (tWnd)
	{
		GetWindowRect(tWnd, &tSize);
		Width = tSize.right - tSize.left;
		Height = tSize.bottom - tSize.top;
		hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, (TCHAR*)lWindowName, (TCHAR*)lWindowName, WS_POPUP, 1, 1, Width, Height, 0, 0, 0, 0);
		//SetLayeredWindowAttributes(hWnd, 0, 1.0f, LWA_ALPHA);
		//SetLayeredWindowAttributes(hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);

		SetLayeredWindowAttributes(hWnd, NULL, NULL, NULL);

		ShowWindow(hWnd, SW_SHOW);
	}

	DirectXInit(hWnd);

	for (;;)
	{
		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&Message);
			TranslateMessage(&Message);
		}
		Sleep(1);
	}
	return 0;
}



void SetWindowToTarget()
{
	while (true)
	{
		tWnd = FindWindow(0, tWindowName);
		if (tWnd)
		{
			GetWindowRect(tWnd, &tSize);
			Width = tSize.right - tSize.left;
			Height = tSize.bottom - tSize.top;
			DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				tSize.top += 23;
				Height -= 23;
			}
			MoveWindow(hWnd, tSize.left, tSize.top, Width, Height, true);
		}
		else
		{
			char ErrorMsg[125];
			sprintf(ErrorMsg, "Make sure %s is running!", tWindowName);
			MessageBox(0, ErrorMsg, "Error - Cannot find the game!", MB_OK | MB_ICONERROR);
			exit(1);
		}
		Sleep(1);
	}
}
