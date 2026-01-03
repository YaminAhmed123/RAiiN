#include <render_engine.hpp>

/*
* Copyright (c) 2025 CortexR7
*
* This source file implements the core functionalities of the render engine
* the engine is still in alpha stage and is under heavy development
* Constrcutors and destructore left empty for now
*/

RenderEngine::RenderEngine() {}
RenderEngine::~RenderEngine() {}

// static functions
static void initVulkanWithEngineContext(
    VkInstance& instance, 
    VkDebugUtilsMessengerEXT& debugMessenger, 
    VkSurfaceKHR& surface, 
    GLFWwindow* window, 
    VkPhysicalDevice& physicalDevice, 
    VkDevice& device, 
    VkQueue& graphicsQueue, 
    VkQueue& presentQueue, 
    VkSwapchainKHR& swapChain, 
    std::vector<VkImage>& swapChainImages, 
    std::vector<VkImageView>& swapChainImageViews,
    VkFormat& swapChainImageFormat,
    VkExtent2D& swapChainExtent
)
{
    vulkanaid::createVulkanInstance(instance);
    vulkanaid::setupDebugMessenger(instance, debugMessenger);
    vulkanaid::createSurface(instance, surface, window);
    vulkanaid::pickPhysicalDevice(instance, physicalDevice, surface);
    vulkanaid::createLogicalDevice(physicalDevice, device, graphicsQueue, presentQueue, surface);
    vulkanaid::createSwapChain(window, physicalDevice, device, surface, swapChain);
    vulkanaid::getSwapChainImages(device, swapChain, swapChainImages);
    vulkanaid::setSwapChainExtentAndFormat(window, physicalDevice, surface, swapChainExtent, swapChainImageFormat);
    vulkanaid::createSwaapChainImageViews(swapChainImages, swapChainImageViews, swapChainImageFormat, device);
}

static void destroyVkSwapChainImageViewsVector(std::vector<VkImageView>& swapChainImageViews, VkDevice& device)
{
    for(auto imageView : swapChainImageViews)
    {
        vkDestroyImageView(device, imageView, nullptr);
    }
}

// valid implementations
void RenderEngine::run() 
{
    RenderEngine::initWindow();
    RenderEngine::initVulkan();
    RenderEngine::mainLoop();
    RenderEngine::cleanup();
}

void RenderEngine::initWindow() 
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    RenderEngine::window = glfwCreateWindow(WIDTH, HEIGHT, "HATE ENGINE", nullptr, nullptr);
}

void RenderEngine::initVulkan() 
{
    initVulkanWithEngineContext(
        RenderEngine::instance, 
        RenderEngine::debugMessenger, 
        RenderEngine::surface, 
        RenderEngine::window, 
        RenderEngine::physicalDevice, 
        RenderEngine::device, 
        RenderEngine::graphicsQueue, 
        RenderEngine::presentQueue, 
        RenderEngine::swapChain, 
        RenderEngine::swapChainImages, 
        RenderEngine::swapChainImagesViews,
        RenderEngine::swapChainImageFormat,
        RenderEngine::swapChainExtent
    );
}

void RenderEngine::mainLoop() 
{
    while (!glfwWindowShouldClose(RenderEngine::window)) 
    {
        glfwPollEvents();
    }
}

void RenderEngine::cleanup() 
{
    if (vulkanaid::DEBUG_MODE) {
        vulkanaid::destroyDebugMessenger(RenderEngine::instance, RenderEngine::debugMessenger);
    }

    destroyVkSwapChainImageViewsVector(RenderEngine::swapChainImagesViews, RenderEngine::device);
    vkDestroySwapchainKHR(RenderEngine::device, RenderEngine::swapChain, nullptr);
    vkDestroyDevice(RenderEngine::device, nullptr);
    vkDestroySurfaceKHR(RenderEngine::instance, RenderEngine::surface, nullptr);
    vkDestroyInstance(RenderEngine::instance, nullptr);

    glfwDestroyWindow(RenderEngine::window);
    glfwTerminate();
}
