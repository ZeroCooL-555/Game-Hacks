#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../header/Menu/menu.hpp"
#include "../header/Overlay/overlay.hpp"
#include "../header/Logging/logging.hpp"
#include "../header/Menu/Toggles.hpp"
#include <stdio.h>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#include <dwmapi.h>
#endif
#define GL_SILENCE_DEPRECATION
#define IMGUI_ENABLE_FREETYPE // Ensure higher quality font rendering.
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define MENU_KEY VK_INSERT
#define DEBUG_KEY VK_NUMPAD8
#define SHUTDOWN_KEY VK_END



static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}



// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);



    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    if (!Monitor)
        return 0;

    /*
    
    Defining glfwWindowHints() for release use.
    This will make the overlay window suitable for overlaying the menu over a video game
    
    */

#ifdef _DEBUG // If compiling a DEBUG build in VS
    //glfwWindowHint(GLFW_FLOATING, true);
    //glfwWindowHint(GLFW_RESIZABLE, true);
    //glfwWindowHint(GLFW_MAXIMIZED, true);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
    //glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, true);
#else
    glfwWindowHint(GLFW_FLOATING, true);
    glfwWindowHint(GLFW_RESIZABLE, true);
    glfwWindowHint(GLFW_MAXIMIZED, true);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
#ifdef _WIN32
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

#endif // DEBUG


#ifdef _DEBUG
    // Create window with pre-defined width and height for development purposes

    // --------------------------[ Creating The overlay For DEBUG ]-----------------------------------------------

    Overlay::GLFW_Window_debug = glfwCreateWindow(1600, 900, "Dear ImGui GLFW+OpenGL3 Debug", nullptr, nullptr);

    if (Overlay::GLFW_Window_debug == nullptr)
        return 1;

    glfwMakeContextCurrent(Overlay::GLFW_Window_debug);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Set Clear
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Overlay::GLFW_Window_debug, true);
    ImGui_ImplOpenGL3_Init(glsl_version);



    // -----------------------------------------------------------------------------------------------------------

#else
    // Create an overlay over a target process
    
    // --------------------------[ Creating The overlay For RELEASE ]-----------------------------------------------
    

    // Getting Target Window Dimensions
    Overlay::GetTargetDimensions(TARGET_NAME);

    // Creating overlay
    Overlay::GLFW_Window = glfwCreateWindow(Overlay::Twidth, Overlay::Theight, OVERLAY_NAME, nullptr, nullptr);
    Overlay::hwnd_Window = glfwGetWin32Window(Overlay::GLFW_Window);


    if (Overlay::GLFW_Window == nullptr)
        return 1;

    glfwMakeContextCurrent(Overlay::GLFW_Window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Set Clear
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Overlay::GLFW_Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);



    // ----------[ THREAD TO CONSTANTLY RESIZE WINDOW ]----------

    HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Overlay::SetWindowToTarget, Overlay::GLFW_Window, 0, 0);
    if (hThread == NULL)
        return 1;

    // -----------------------------------------------------------


#endif // _DEBUG

#ifdef _DEBUG
    //glfwSetWindowAttrib(window, GLFW_DECORATED, false); // Disables the decorator (top bar with minimize, maximize, X/close functions)
#else
    glfwSetWindowAttrib(Overlay::GLFW_Window, GLFW_DECORATED, false); // Disables the decorator (top bar with minimize, maximize, X/close functions)
#endif
    




    // ----------[ Load Fonts ]----------
    
    


    // ----------[ Load Icons ]----------
    
    


    // ----------[ Load Cursor ]----------







    
    // ----------[ Creating Instance of Menu ]----------
    Menu Menu;



    // ----------[ Main loop ] ----------
    


#ifdef _DEBUG
    while (!glfwWindowShouldClose(Overlay::GLFW_Window_debug))
    {

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // DRAW STUFF HERE
        Menu.Render(Overlay::GLFW_Window_debug);




        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(Overlay::GLFW_Window_debug, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

#ifdef _DEBUG // If compiling a DEBUG build in VS

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w); // use background color

#else
        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w); // disable background color for transparency

#endif

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(Overlay::GLFW_Window_debug);
    }
#else // _DEBUG
    while (!glfwWindowShouldClose(Overlay::GLFW_Window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // DO ALL KEYBOARD EVENT HANDLING HERE


        // Render Main ImGui Window based on boolean
        if (Toggles::bMenuVisible)
            Menu.Render(Overlay::GLFW_Window);

        // Render ImGui Debug Window based on boolean
        if (Toggles::bDebug)
            Debug::StartDebugConsole();


        // Handle Keyboard Presses to view/hide ImGui Main Window
        if (GetAsyncKeyState(MENU_KEY) & 1)
        {
            Toggles::bMenuVisible = !Toggles::bMenuVisible;
            if (Toggles::bMenuVisible)
            {
                Menu.ShowMenu(Overlay::GLFW_Window);
            }
            else
            {
                Menu.HideMenu(Overlay::GLFW_Window);
            }
        }


        // Handle Keyboard Presses to view/hide ImGui Debug Console Window
        if (GetAsyncKeyState(DEBUG_KEY) & 1)
        {
            Toggles::bDebug = !Toggles::bDebug;
            if (Toggles::bDebug)
            {
                Debug::ShowDebug(Overlay::GLFW_Window);
            }
            else
            {
                Debug::HideDebug(Overlay::GLFW_Window);
            }
        }

        // Exit Program Gracefully
        if (GetAsyncKeyState(SHUTDOWN_KEY) & 1)
            glfwSetWindowShouldClose(Overlay::GLFW_Window, true);
        

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(Overlay::GLFW_Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

#ifdef _DEBUG // If compiling a DEBUG build in VS

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w); // use background color

#else
        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w); // disable background color for transparency

#endif

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(Overlay::GLFW_Window);
    }
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(Overlay::GLFW_Window);
#ifdef _DEBUG
    //WaitForSingleObject(hThread, 500);
    //CloseHandle(hThread);
#else
    WaitForSingleObject(hThread, 500);
    CloseHandle(hThread);
#endif // DEBUG
    glfwTerminate();

    return 0;
}