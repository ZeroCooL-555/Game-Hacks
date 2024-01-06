#include "../header/Menu/menu.hpp"
#include "../header/Overlay/overlay.hpp"

void Menu::SelectCursor(GLFWcursor* Cursor)
{
    /*
    
    @breif: Selects the cursor to be used
    @params: A pointer to an active window, a pointer to the loaded cursor
    @retval: None
    
    */

    if (Cursor != nullptr && Overlay::GLFW_Window != nullptr)
    {
        glfwSetCursor(Overlay::GLFW_Window, Cursor);
    }
}