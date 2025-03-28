#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

namespace core {

    class GameInstance
    {

    public:
        void run();

    private:
        void initVulkan();

        void createInstance();

        void initWindow();

        void mainLoop();

        void cleanup();

    private:
        GLFWwindow* window;

        VkInstance instance;
    };
}