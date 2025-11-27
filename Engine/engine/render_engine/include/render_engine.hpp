#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP


#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkanaid.hpp>


/*
*  Copyright (c) 2025 CortexR7
* 
* This header defines the render_engine itself and all its core functionalities
* the engine is still in alpha stage and is under heavy development
*/

class RenderEngine {
private:
    const int WIDTH = 800;
    const int HEIGHT = 600;

public:
    GLFWwindow* window;

    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkInstance instance{};
    VkDebugUtilsMessengerEXT debugMessenger{};

    // Queues
    VkQueue graphicsQueue;
    VkQueue presentQueue;



    RenderEngine();
    ~RenderEngine();
    void run();
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
};

#endif