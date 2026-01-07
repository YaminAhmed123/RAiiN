#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <vulkanaid.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>

#ifdef _WIN32
    #define GLFW_INCLUDE_VULKAN
    #define VK_USE_PLATFORM_WIN32_KHR
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#elif __linux__
    #define GLFW_INCLUDE_VULKAN
    #define VK_USE_PLATFORM_WAYLAND_KHR
    #define GLFW_EXPOSE_NATIVE_X11
    #include <GLFW/glfw3native.h>
#endif



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
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImagesViews;
    VkInstance instance{};
    VkDebugUtilsMessengerEXT debugMessenger{};

    // Queues
    VkQueue graphicsQueue;
    VkQueue presentQueue;

    // graphics
    VkPipelineLayout pipelineLayout;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;



    RenderEngine();
    ~RenderEngine();
    void run();
    void initWindow();
    void initVulkan();
    void createGraphicsPipeline();
    void mainLoop();
    void cleanup();
};

#endif