#pragma once
#include <Windows.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../header/Methods/CreateImage.hpp"


class Menu
{
public:
	void Render(GLFWwindow* window);
	static void ShowMenu(GLFWwindow* window);
	static void HideMenu(GLFWwindow* window);
	static void LoadCustomStyle();
	ImFont* LoadCustomFont(const unsigned char* fontData, int dataSize, float fontSize);
	ImFont* LoadCustomIconPack(const unsigned int* IconData, const size_t dataSize, float IconSize);
	GLFWcursor* LoadCustomCursor(const unsigned char* CursorData, size_t CursorDataSize);
	static void SelectCursor(GLFWcursor* Cursor);
	static bool SelectFont(const char* FontName, ImFont* customfont);
	static void UnloadFont();
	static void CenterText(const char* text);
	bool RenderImage(GLuint TextureID, ImVec2 Position, ImVec2 Dimensions, ImageAlignment Alignment);
	GLuint LoadTextureFromMemory(const unsigned char* Texture, const size_t TextureSize);

	// Define variables to store custom fonts here
	// Example:
	// ImFont* MyCustomFont;

	ImFontConfig icons_config; // Configuration for the to be loaded icons
	
	// Define variables to store icon font here
	// Example: 
	// ImFont* icon_font;


	// Define variables to store custom cursors
	// Example:
	// GLFWcursor* MyCustomCursor;

	// Define variable to store Texture ID's
	// Example:
	// GLuint MyTextureID;
};
