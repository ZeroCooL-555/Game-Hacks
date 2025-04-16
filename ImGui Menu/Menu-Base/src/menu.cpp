#include <Windows.h>
#include <GL/glew.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../header/Menu/menu.hpp"
#include "../header/Overlay/overlay.hpp"
#include "../header/Logging/logging.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../header/stb_image.h"



#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <iostream>


void Menu::Render(GLFWwindow* window)
{
	/*
	
	@brief: Renders all ImGui Stuff
	@params: A pointer to an active window
	@retval: None

	*/

	ImGuiWindowFlags window_flags = NULL;
	ImGui::Begin("Main", nullptr, window_flags);
	{

		// Render ImGui Stuff here

	}

	ImGui::End();
}


void Menu::ShowMenu(GLFWwindow* window)
{
	// Disable mouse passthrough
	glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, false);

	// Force the cursor to be shown and normal
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// bring our window to foreground
	SetForegroundWindow(Overlay::hwnd_Window);

	// Force windows to show the cursor
	while (ShowCursor(TRUE) < 0);

	// Send mouse event to force mouse update...Works but bad.
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = 0;
	input.mi.dy = 0;
	SendInput(1, &input, sizeof(INPUT));
}

void Menu::HideMenu(GLFWwindow* window)
{
	glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, true);
	HWND prevForegroundWindow = GetForegroundWindow();
	SetForegroundWindow(prevForegroundWindow);
}
