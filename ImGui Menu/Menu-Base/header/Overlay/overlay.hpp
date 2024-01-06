#pragma once
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <string>

#define TARGET_NAME L" " // Specify Your Desired Target Window Name Here
#define OVERLAY_NAME " " // Specify Your Desired Overlay Name Here


class Overlay
{
public:
	static bool GetTargetDimensions(const wchar_t* WindowName);
	static void SetWindowToTarget(GLFWwindow* window);


	// Define Variable for overlay & target
	static int Twidth;
	static int Theight;

	static GLFWwindow* GLFW_Window; // The overlay window (GLFWwindow type)
	static GLFWwindow* GLFW_Window_debug;
	static HWND hwnd_Window; // The overlay window (HWND type)
	static HWND Twnd; // The Target window
};