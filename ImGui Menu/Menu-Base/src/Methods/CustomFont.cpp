#include <iostream>
#include "../header/Menu/menu.hpp"


bool Menu::SelectFont(const char* FontName, ImFont* customfont)
{

	/*
	
	@brief: Selects a font to be used
	@params: The name of the font, pointer to the loaded font
	@retval: A boolean value, if successful then we return true

	*/


	if (customfont != nullptr)
	{
		ImGui::PushFont(customfont);
	}
	else
	{

		std::cerr << "Failed To Load Font: " << FontName << std::endl;
		return false;
	}
	
	return true;
}

void Menu::UnloadFont()
{
	ImGui::PopFont();
}