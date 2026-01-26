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
    #define GLFW_EXPOSE_NATIVE_WAYLAND
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
    const uint32_t MAX_FRAMES_IN_FLIGHT = 4;
    int currentFrame = 0;

    // Helper functions that are meant to be used for certain TUs only
    // dont use them outside render_engine src files
    void checkForSwapChainRecreation(VkResult result, int mode); // mode = 0 check for Image acquisition, mode = 1 check for presentation

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
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkInstance instance{};
    VkDebugUtilsMessengerEXT debugMessenger{};

    // Queues
    VkQueue graphicsQueue;
    VkQueue presentQueue;

    // graphics
    VkPipeline graphicsPipeline;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;

    // commnads
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    // sync objects
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<renderFinishedImageSwapChainSemaphore> swapChainSemaphores;
    std::vector<VkFence> inFlightFences;


    // Vulkan Buffer
    VkBuffer vertexBuffer;

    // swapchain recreation members
    bool framebufferResized = false;


    RenderEngine();
    ~RenderEngine();
    void run();
    void initWindow();
    void initVulkan();
    void createGraphicsPipeline();
    void createRenderpass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffer();
    void recordCommandBuffer(VkCommandBuffer& commandBuffer, uint32_t imageIndex);
    void createSyncObjects();
    void createVertexBuffer();
    void drawFrame();
    void recreateSwapChain();
    void cleanUpSwapChain();
    void mainLoop();
    void cleanup();
};

#endif
