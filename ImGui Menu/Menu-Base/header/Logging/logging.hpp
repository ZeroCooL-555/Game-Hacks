#include <vector>
#include <tuple>
#include <string>

enum class MSG_TYPE {
    DBG_INFO,
    DBG_ERROR,
    DBG_WARN,
    DBG_OK
};

class Debug {
public:
    static void DbgPrint(const char* msg, MSG_TYPE type);
    static void ShowDebug(GLFWwindow* window);
    static void HideDebug(GLFWwindow* window);
    static void StartDebugConsole();

private:
    static std::vector<std::tuple<std::string, MSG_TYPE>> debugMessages;
};