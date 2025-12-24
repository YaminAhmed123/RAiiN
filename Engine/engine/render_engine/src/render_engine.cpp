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
static void initVulkanWithEngineContext(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger, VkSurfaceKHR& surface, GLFWwindow* window, VkPhysicalDevice& physicalDevice, VkDevice& device, VkQueue& graphicsQueue, VkQueue& presentQueue) 
{
    vulkanaid::createVulkanInstance(instance);
    vulkanaid::setupDebugMessenger(instance, debugMessenger);
    vulkanaid::createSurface(instance, surface, window);
    vulkanaid::pickPhysicalDevice(instance, physicalDevice, surface);
    vulkanaid::createLogicalDevice(physicalDevice, device, graphicsQueue, presentQueue, surface);
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
    initVulkanWithEngineContext(RenderEngine::instance, RenderEngine::debugMessenger, RenderEngine::surface, RenderEngine::window, RenderEngine::physicalDevice, RenderEngine::device, RenderEngine::graphicsQueue, RenderEngine::presentQueue);
}

void RenderEngine::mainLoop() 
{
    while (!glfwWindowShouldClose(RenderEngine::window)) {
        glfwPollEvents();
    }
}

void RenderEngine::cleanup() 
{
    if (vulkanaid::DEBUG_MODE) {
        vulkanaid::destroyDebugMessenger(RenderEngine::instance, RenderEngine::debugMessenger);
    }

    vkDestroyDevice(RenderEngine::device, nullptr);
    vkDestroySurfaceKHR(RenderEngine::instance, RenderEngine::surface, nullptr);
    vkDestroyInstance(RenderEngine::instance, nullptr);

    glfwDestroyWindow(RenderEngine::window);
    glfwTerminate();
}
