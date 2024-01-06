<p align="center">
    <!-- <a href='https://flamingtext.com/'>Logo Designed with FlamingText.com</a> -->
    <img src="https://github.com/ZeroCooL-555/Game-Hacks/blob/master/Screenshots/ImGui-Project-Banner.png" alt="banner">
</p>


<p align="center">
    <img src="https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg?style=for-the-badge" alt="C++">
    <img src="https://img.shields.io/badge/platform-Windows-0078d7.svg?style=for-the-badge" alt="Windows">
    <img src="https://img.shields.io/badge/arch-x86-red.svg?style=for-the-badge" alt="x86">
    <img src="https://img.shields.io/badge/arch-x64-green.svg?style=for-the-badge" alt="x64">
</p>


## 📖 Project Overview

*A standalone OpenGL ImGui Overlay ready to be integrated into any project.*
<br>
*The goal of this project is mainly to excel the development of game trainer GUI interfaces by providing the starting block (base).*
<br>
*Some common functionality has been added to support e.g (Custom Fonts, Custom Icons, Custom Styles, Custom Images, etc)*


## 🚀 Getting Started

> **⚠️ Prerequisites** <br>
> The project requires some external programs to be installed before attempting to build and compile the project <br>

- [**CMake**](https://cmake.org/download/)
    - Make sure to add *CMake* to system PATH for current user
    - winget command to install CMake: `winget install -e --id Kitware.CMake`
- [**Visual Studio 2022**](https://visualstudio.microsoft.com/)

<br>
<br>

> **⚠️ Note** <br>
> When running the build script an error might occur -> `ERROR: MSB3073` <br> 
> Ignore this error, it does not affect the build process <br>

- Make sure `CMake` is installed and working correctly
- Run `Build.bat` located in the projects root directory
- Now open the project's `.sln` file using *Visual Studio*
- Choose your desired arch and version `x86` or `x64` / `Debug` or `Release`
- Press **CTRL+SHIFT+B** or navigate to `Build -> Build Solution`

<br>

> **⚠️ Note** <br>
> Information on Debug vs Release mode

- **Release**
    - When compiling in release mode an overlay is created over an application requiring a target window name to be specified
- **Debug**
    - Creates a standard ImGui window intended for menu development purposes


## 💎 Project Structure

```
├───Menu-Base
│   ├───header
│   │   ├───Logging
│   │   ├───Menu
│   │   ├───Methods
│   │   ├───Overlay           <----- Specify Target window in here
│   │   └───resources         <----- Define fonts,cursors,etc here
│   │       ├───Cursors
│   │       ├───Fonts
│   │       ├───icons
│   │       └───images
|   |
│   ├───src
│   │   ├───Logging
│   │   ├───Methods           <----- Set Custom ImGui Style in customstyle.cpp
│   │   └───Overlay
|   |   main.cpp              <----- Load fonts,cursors,etc here
|   |   menu.cpp              <----- Write menu render stuff here
```



## ⚡ Examples

<details><summary><b>Custom Fonts</b></summary>

<br>

```cpp

		// Load The Font before the main loop
		Menu Menu;
		Menu.RubikBlack = Menu.LoadCustomFont(RubikBlack, sizeof(RubikBlack), 16.0f);

		// Call In Renderer
		Menu::SelectFont("RobotoMono-Regular", this->RobotoMonoRegular);
		    ImGui::Text("This Text Is Written Using RobotoMono-Regular");
		Menu::UnloadFont(); // Free Loaded Font

```

</details>



<details><summary><b>Custom Icons</b></summary>

<br>

```cpp
        // Load The Icons before the main loop
        Menu Menu;
        Menu.icon_font = Menu.LoadCustomIconPack(font_awesome_data, font_awesome_size, 19.05f);

		// Call In Renderer
		Menu::SelectFont("Awesome Icon Font", this->icon_font);
		    ImGui::Text(ICON_FA_ADDRESS_CARD);
		Menu::UnloadFont(); //  Free icon_font

```


</details>



<details><summary><b>Custom Images</b></summary>

<br>

```cpp

		// Call In Renderer
		this->SomeImage_TexID = Menu::LoadTextureFromMemory(SomeImage, sizeof(SomeImage)); // Generate TextureID for SomeImage
		Menu::RenderImage(this->SomeImage_TexID, ImVec2(PosX, PosY), ImVec2(Width, Height), ImageAlignment::Center); // Render Given Texture

```

</details>




<details><summary><b>Center Text</b></summary>

<br>

```cpp
        // Call In Renderer
        Menu::CenterText("THIS SHOULD BE CENTERED");
```

</details>



<details><summary><b>Custom Style</b></summary>

<br>

```cpp
		// Load Custom Style: Defined in CustomStyle.cpp
		Menu::LoadCustomStyle()
```

</details>

<details><summary><b>Custom Cursor</b></summary>

<br>

```cpp

    // Load The Cursor before the main loop
    Menu Menu;
    Menu.customCursor = Menu.LoadCustomCursor(SomeCursor, sizeof(SomeCursor));

    // Call In Renderer
    Menu::SelectCursor(this->customCursor);

    // Destroy the GLFWcursor object: Called after mainloop in cleanup
    glfwDestroyCursor(Menu.customCursor);

```

</details>

<details><summary><b>Custom Debug</b></summary>

<br>

```cpp
        Debug::DbgPrint("TEST", MSG_TYPE::DBG_OK);
```

</details>

## 📋 Credits

- [Dear ImGui](https://github.com/ocornut/imgui)
- [GLEW](https://github.com/nigels-com/glew)
- [GLFW](https://github.com/glfw/glfw)
- [STB](https://github.com/nothings/stb/tree/master)