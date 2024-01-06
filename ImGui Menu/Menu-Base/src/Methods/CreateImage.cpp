#include <iostream>
#include "../header/Menu/menu.hpp"



bool Menu::RenderImage(GLuint TextureID, ImVec2 Position, ImVec2 Dimensions, ImageAlignment Alignment)
{

	/*
	
	@brief: Renders a texture
	@params: The ID of a loaded texture, the position, the width and height, alignment (center,left,right) 
	@retval: A boolean value, if successful we return true

	*/


	// Load Texture From Given TextureID

	if (TextureID != 0)
	{
		switch (Alignment)
		{
		case ImageAlignment::Left:
			// Left alignment - No need to add extra space
			break;

		case ImageAlignment::Right:
			// Right alignment - Add space on the left side
			ImGui::SameLine(ImGui::GetContentRegionAvail().x - Dimensions.x);
			break;

		case ImageAlignment::Center:
		default:
			// Center alignment - Add space to center the image
			ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (Dimensions.x / 2));
			break;
		}

		ImGui::SetCursorPos(Position); // Set the x,y position for the image
		ImGui::Image((void*)(intptr_t)TextureID, Dimensions);
		return true;
	}
	else
	{
		std::cerr << "TextureID invalid!" << std::endl;
		return false;
	}
}