#include <windows.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "../header/Menu/menu.hpp"


void Menu::CenterText(const char* text) {
	// Calculate the width of the text
	ImVec2 textSize = ImGui::CalcTextSize(text);

	// Get the current window width
	float windowWidth = ImGui::GetWindowSize().x;

	// Calculate the starting x position for centered text
	float textX = (windowWidth - textSize.x) * 0.5f;

	// Set the cursor to the calculated position
	ImGui::SetCursorPosX(textX);

	// Render the text
	ImGui::Text("%s", text);
}