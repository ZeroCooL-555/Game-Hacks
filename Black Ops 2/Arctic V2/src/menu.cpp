#include <Windows.h>
#include "menu.h"
#include "DirectX.h"
#include "Game.h"
#include "Hacks.h"

#define ESP_MENU_ENABLE 1
#define ESP_CORNER_ON 1
#define ESP_CORNER_OFF 0
#define ESP_BORDER_ON 1
#define ESP_BORDER_OFF 0
#define SNAPLINES_ON 1
#define SNAPLINES_OFF 0
#define DISTANCE_ON 1
#define DISTANCE_OFF 0
#define VSAT_ON 1
#define VSAT_OFF 0
#define MAX_FOV_ON 1
#define MAX_FOV_OFF 0
#define CENTER_SCREEN (monitor.x / 2)
#define OPTION_HEIGHT 300

Checks checks;

void menu::Toggles()
{
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		checks.ESP = !checks.ESP;
	}
	else
	{
		!checks.ESP;
	}
	if (GetAsyncKeyState(VK_F4) & 1)
	{
		checks.esp_border = !checks.esp_border;
	}
	else
	{
		!checks.esp_border;
	}
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		checks.esp_corner = !checks.esp_corner;
	}
	else
	{
		!checks.esp_corner;
	}
	if (GetAsyncKeyState(VK_F6) & 1)
	{
		checks.Lines = !checks.Lines;
	}
	else
	{
		!checks.Lines;
	}
	if (GetAsyncKeyState(VK_F7) & 1)
	{
		checks.Distance = !checks.Distance;
	}
	else
	{
		!checks.Distance;
	}
	if (GetAsyncKeyState(VK_F2) & 1)
	{
		checks.vsat = !checks.vsat;
	}
	else
	{
		!checks.vsat;
	}
	if (GetAsyncKeyState(VK_F3) & 1)
	{
		checks.player_fov = !checks.player_fov;
	}
	else
	{
		!checks.player_fov;
	}

	// Not included in menu
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		checks.show_hide = !checks.show_hide;
	}
	else
	{
		!checks.show_hide;
	}
	if (GetAsyncKeyState(VK_END) & 1)
	{
		CloseHack();
	}
}

void menu::D3DMenu()
{

	if (checks.show_hide)
	{

		// Draw Banner
		
		/* ============================================================================= */
		
		// Banner background
		DrawFilledRect(CENTER_SCREEN - 80, OPTION_HEIGHT - 55, 300, 60, Color::black); 


		// Banner Border
		DrawFilledRect(CENTER_SCREEN - 80, OPTION_HEIGHT - 60, 5, 60, Color::gray); // Left
		DrawFilledRect(CENTER_SCREEN - 80, OPTION_HEIGHT - 60, 300, 5, Color::gray); // Top
		DrawFilledRect(CENTER_SCREEN + 215, OPTION_HEIGHT - 60, 5, 60, Color::gray); // Right


		// Banner Text box
		DrawFilledRect(CENTER_SCREEN + 10, OPTION_HEIGHT - 50, 120, 40, Color::black); 
		DrawString("Arctic", CENTER_SCREEN + 50, OPTION_HEIGHT - 45, Color::cyan, pFontBanner);

		/* ============================================================================= */





		// Draw Background

		/* ============================================================================= */
		DrawFilledRect(CENTER_SCREEN - 80, OPTION_HEIGHT - 10, 300, 200, Color::gray); // Border
		DrawFilledRect(CENTER_SCREEN - 75, OPTION_HEIGHT - 5, 290, 190, Color::black); // Background
		/* ============================================================================= */

		// Draw All Menu Options

		/* ================================================================================================================================ */
		if (checks.ESP)
		{
			// Enables Sub-menu
			DrawString("[F1] ESP MENU: ON", CENTER_SCREEN, OPTION_HEIGHT, Color::green, pFontMenu);


			// Draw ESP Sub-menu options
			if (checks.esp_border)
				DrawString("[F4] 2D-ESP: ON", CENTER_SCREEN, OPTION_HEIGHT + 40, Color::green, pFontMenu);
			else
				DrawString("[F4] 2D-ESP: OFF", CENTER_SCREEN, OPTION_HEIGHT + 40, Color::red, pFontMenu);
			if (checks.esp_corner)
				DrawString("[F5] Corner ESP: ON", CENTER_SCREEN, OPTION_HEIGHT + 60, Color::green, pFontMenu);
			else
				DrawString("[F5] Corner ESP: OFF", CENTER_SCREEN, OPTION_HEIGHT + 60, Color::red, pFontMenu);
			if (checks.Lines)
				DrawString("[F6] Lines: ON", CENTER_SCREEN, OPTION_HEIGHT + 80, Color::green, pFontMenu);
			else
				DrawString("[F6] Lines: OFF", CENTER_SCREEN, OPTION_HEIGHT + 80, Color::red, pFontMenu);

			if (checks.Distance)
				DrawString("[F7] Distance: ON", CENTER_SCREEN, OPTION_HEIGHT + 100, Color::green, pFontMenu);
			else
				DrawString("[F7] Distance: OFF", CENTER_SCREEN, OPTION_HEIGHT + 100, Color::red, pFontMenu);
		}
		else
		{
			// Close Sub-menu
			DrawString("[F1] ESP MENU: OFF", CENTER_SCREEN, OPTION_HEIGHT, Color::red, pFontMenu);
		}
	}

	// Draw Misc options
	if (checks.vsat)
	{
		if (checks.ESP)
			DrawString("[F2] VSAT: ON", CENTER_SCREEN, OPTION_HEIGHT + 140, Color::green, pFontMenu);
		else
			DrawString("[F2] VSAT: ON", CENTER_SCREEN, OPTION_HEIGHT + 20, Color::green, pFontMenu);
	}
	else
	{
		if (checks.ESP)
			DrawString("[F2] VSAT: OFF", CENTER_SCREEN, OPTION_HEIGHT + 140, Color::red, pFontMenu);
		else
			DrawString("[F2] VSAT: OFF", CENTER_SCREEN, OPTION_HEIGHT + 20, Color::red, pFontMenu);
	}

	if (checks.player_fov)
	{
		if (checks.ESP)
			DrawString("[F3] 120 FOV: ON", CENTER_SCREEN, OPTION_HEIGHT + 160, Color::green, pFontMenu);
		else
			DrawString("[F3] 120 FOV: ON", CENTER_SCREEN, OPTION_HEIGHT + 40, Color::green, pFontMenu);
	}
	else
	{
		if (checks.ESP)
			DrawString("[F3] 120 FOV: OFF", CENTER_SCREEN, OPTION_HEIGHT + 160, Color::red, pFontMenu);
		else
			DrawString("[F3] 120 FOV: OFF", CENTER_SCREEN, OPTION_HEIGHT + 40, Color::red, pFontMenu);

	}

	/* ================================================================================================================================ */
}

void menu::StartHack()
{
	menu::Toggles();

	if (checks.show_hide)
	{
		menu::D3DMenu();
	}

	// All Toggles for ESP
	if (checks.ESP && checks.Lines)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_OFF, ESP_BORDER_OFF, SNAPLINES_ON, DISTANCE_OFF);
	}
	if (checks.ESP && checks.Distance)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_OFF, ESP_BORDER_OFF, SNAPLINES_OFF, DISTANCE_ON);
	}
	if (checks.ESP && checks.Lines && checks.Distance)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_OFF, ESP_BORDER_OFF, SNAPLINES_ON, DISTANCE_ON);
	}
	if (checks.ESP && checks.esp_border)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_OFF, ESP_BORDER_ON, SNAPLINES_OFF, DISTANCE_OFF);
	}
	if (checks.ESP && checks.esp_corner)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_ON, ESP_BORDER_OFF, SNAPLINES_OFF, DISTANCE_OFF);
	}
	if (checks.ESP && checks.esp_border && checks.Lines)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_OFF, ESP_BORDER_ON, SNAPLINES_ON, DISTANCE_OFF);
	}
	if (checks.ESP && checks.esp_corner && checks.Lines)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_ON, ESP_BORDER_OFF, SNAPLINES_ON, DISTANCE_OFF);
	}
	if (checks.ESP && checks.esp_border && checks.Distance)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_OFF, ESP_BORDER_ON, SNAPLINES_OFF, DISTANCE_ON);
	}
	if (checks.ESP && checks.esp_corner && checks.Distance)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_ON, ESP_BORDER_OFF, SNAPLINES_OFF, DISTANCE_ON);
	}
	if (checks.ESP && checks.esp_border && checks.Lines && checks.Distance)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_OFF, ESP_BORDER_ON, SNAPLINES_ON, DISTANCE_ON);
	}
	if (checks.ESP && checks.esp_corner && checks.Lines && checks.Distance)
	{
		Hacks::ESP(ESP_MENU_ENABLE, ESP_CORNER_ON, ESP_BORDER_OFF, SNAPLINES_ON, DISTANCE_ON);
	}
	
	// Misc options Toggles
	if (checks.vsat)
	{
		Hacks::VSAT(VSAT_ON);
	}
	else
	{
		Hacks::VSAT(VSAT_OFF);
	}
	
	if (checks.player_fov)
	{
		Hacks::MAX_FOV(MAX_FOV_ON);
	}
	else
	{
		Hacks::MAX_FOV(MAX_FOV_OFF);
	}
}