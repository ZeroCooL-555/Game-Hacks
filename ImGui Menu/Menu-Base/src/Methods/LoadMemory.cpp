#include <GL/glew.h>
#include <iostream>
#include "../header/Menu/menu.hpp"
#include "../header/resources/icons/font_awesome.hpp"
#include "../header/Logging/logging.hpp"
#include "../header/stb_image.h"


GLuint Menu::LoadTextureFromMemory(const unsigned char* Texture, const size_t TextureSize) {

	/*

	@brief: The function returns a valid GLuint Texture ID to then be used to render the texture
	@params: byte array of the texture, size of the texture array
	@retval: An ID of the texture

	*/

	// Load image from memory buffer

	if (TextureSize == 0)
	{
		std::cerr << "Failed To Get Texture Size!" << std::endl;
		return -1;
	}

	int width, height, channels;
	unsigned char* image_data = stbi_load_from_memory(Texture, TextureSize, &width, &height, &channels, 4);

	if (!image_data) {
		std::cerr << "Failed to load image" << std::endl;
		return 0;
	}

	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image data into the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	// Free the image data as it's no longer needed
	stbi_image_free(image_data);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return TextureID;
}

ImFont* Menu::LoadCustomIconPack(const unsigned int* IconData, const size_t dataSize, float IconSize)
{
	/*

	@brief: The function loads a given Icon Pack / Icon Font to then be used to render an ICON
	@params: byte array containing the data, the size of the array, the pixel size of the to be loaded icons
	@retval: A pointer to the custom icon pack

	*/


	static const ImWchar icon_ranges[]{ ICON_MIN_FA , ICON_MAX_FA, 0 };
	ImGuiIO& io = ImGui::GetIO();

	this->icons_config.MergeMode = true;
	this->icons_config.PixelSnapH = true;
	this->icons_config.OversampleH = 3;
	this->icons_config.OversampleV = 3;

	ImFont* CustomIcon;
	CustomIcon = io.Fonts->AddFontFromMemoryCompressedTTF(IconData, dataSize, IconSize, &icons_config, icon_ranges);
	if (CustomIcon != nullptr)
	{
		return CustomIcon;
	}
	else
	{
		std::cerr << "Failed To Load Custom Icon Pack!" << std::endl;
	}

	return nullptr;
}

GLFWcursor* Menu::LoadCustomCursor(const unsigned char* CursorData, size_t CursorDataSize) {

	/*

	@brief: The function loads a custom cursor image from a given byte array
	@params: The byte array containing the cursor image, the size of the byte array
	@retval: A pointer to the custom cursor

	*/




	int width, height, channels;
	unsigned char* Cursorbuf = stbi_load_from_memory(CursorData, CursorDataSize, &width, &height, &channels, 4);

	if (!Cursorbuf)
	{
		return nullptr;
	}

	// Create a GLFWimage from the provided data
	GLFWimage cursorImg;
	cursorImg.width = width;
	cursorImg.height = height;
	cursorImg.pixels = Cursorbuf;

	// Create a cursor from the GLFWimage
	GLFWcursor* cursor = glfwCreateCursor(&cursorImg, 0, 0);

	return cursor;
}

ImFont* Menu::LoadCustomFont(const unsigned char* fontData, int dataSize, float fontSize)
{

	/*
	
	@brief: The function loads a custom font from a given byte array
	@params: A byte array containing the font to load, the size of the byte array, the pixel size of the font to be loaded
	@retval: A pointer to the custom font


	*/


	ImGuiIO& io = ImGui::GetIO();

	// Load the custom font from memory
	ImFontConfig customfont_config;
	customfont_config.FontDataOwnedByAtlas = false; // hxxps://github.com/mosra/magnum-integration/issues/42
	ImFont* customFont = io.Fonts->AddFontFromMemoryTTF((void*)fontData, dataSize, fontSize, &customfont_config);

	// Check if the font was loaded successfully
	if (customFont == nullptr) {
		std::cerr << "Failed To Load Font From Memory!" << std::endl;
		return nullptr;
	}

	return customFont;
}