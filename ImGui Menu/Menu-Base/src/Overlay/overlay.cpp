#include "../header/Overlay/overlay.hpp"
#include <dwmapi.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <iostream>

// Init Overlay variables
int Overlay::Theight = 0;
int Overlay::Twidth = 0;
GLFWwindow* Overlay::GLFW_Window = nullptr;
GLFWwindow* Overlay::GLFW_Window_debug = nullptr;
HWND Overlay::hwnd_Window = 0;
HWND Overlay::Twnd = 0;



bool Overlay::GetTargetDimensions(const wchar_t* WindowName)
{
	/*
	@breif: Calculates The Given specified window's dimensions and stores it in a class variable
	@params: The target window to get the dimensions of
	@retval: boolean, if the window is valid the function returns (height,width) of a target window
	*/

	if (WindowName != nullptr)
	{
		RECT rect;
		Overlay::Twnd = FindWindow(NULL, WindowName);
		if (Overlay::Twnd != NULL)
		{
			GetWindowRect(Overlay::Twnd, &rect);
			Overlay::Twidth = rect.right - rect.left;
			Overlay::Theight = rect.bottom - rect.top;

			if (Overlay::Twidth != NULL && Overlay::Theight != NULL)
				return true;
		}
		return false;
	}
	return false;
}


void Overlay::SetWindowToTarget(GLFWwindow* window)
{

	/*
	
	@brief: Moves the overlay window into the target's window area (the overlay will have the target's dimensions also)
	@params: The overlay window pointer
	@retval: None
	
	*/


	do
	{
		int width;
		int height;
		HWND overlay_hwnd = glfwGetWin32Window(window);
		HWND Game_hwnd = FindWindow(NULL, TARGET_NAME);
		RECT rect;

		GetWindowRect(Game_hwnd, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;

		if (Overlay::Theight == height && Overlay::Twidth == width)
		{
			SetWindowPos(overlay_hwnd, NULL, rect.left, rect.top, width, height, 3u);
			MoveWindow(overlay_hwnd, rect.left, rect.top, width, height, true);
			MARGINS margins{ -1, -1, -1, -1 };
			DwmExtendFrameIntoClientArea(overlay_hwnd, &margins);
		}

		Overlay::Theight = height;
		Overlay::Twidth = width;

		Sleep(25);


	} while (window != nullptr);
}