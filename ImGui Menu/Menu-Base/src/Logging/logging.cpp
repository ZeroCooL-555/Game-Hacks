#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "../header/Logging/logging.hpp"
#include "../header/Overlay/overlay.hpp"


std::vector<std::tuple<std::string, MSG_TYPE>> Debug::debugMessages;

void Debug::StartDebugConsole()
{
    ImGui::Begin("Debug Console");
    {

        for (const auto& messageData : debugMessages) {
            const auto& [msg, type] = messageData;

            switch (type) {
            case MSG_TYPE::DBG_INFO:
                ImGui::Text("[INFO] %s", msg.c_str());
                break;
            case MSG_TYPE::DBG_WARN:
                ImGui::Text("[");
                ImGui::SameLine(0, 0);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
                ImGui::Text("WARN");
                ImGui::PopStyleColor();
                ImGui::SameLine(0, 0);
                ImGui::Text("] ");
                ImGui::SameLine(0, 0);
                ImGui::Text("%s", msg.c_str());
                break;
            case MSG_TYPE::DBG_ERROR:
                ImGui::Text("[");
                ImGui::SameLine(0, 0);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                ImGui::Text("ERROR");
                ImGui::PopStyleColor();
                ImGui::SameLine(0, 0);
                ImGui::Text("] ");
                ImGui::SameLine(0, 0);
                ImGui::Text("%s", msg.c_str());
                break;
            case MSG_TYPE::DBG_OK:
                ImGui::Text("[");
                ImGui::SameLine(0, 0);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
                ImGui::Text("OK");
                ImGui::PopStyleColor();
                ImGui::SameLine(0, 0);
                ImGui::Text("] ");
                ImGui::SameLine(0, 0);
                ImGui::Text("%s", msg.c_str());
                break;
            }
        }

        debugMessages.clear();
    }
    ImGui::End();
}

void Debug::DbgPrint(const char* msg, MSG_TYPE type) {
    debugMessages.emplace_back(msg, type);
}

void Debug::ShowDebug(GLFWwindow* window)
{
    glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, false);
}

void Debug::HideDebug(GLFWwindow* window)
{
    glfwSetWindowAttrib(Overlay::GLFW_Window, GLFW_MOUSE_PASSTHROUGH, true);
    HWND prevForegroundWindow = GetForegroundWindow();
    SetForegroundWindow(prevForegroundWindow);
}