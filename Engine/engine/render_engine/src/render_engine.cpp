#include <render_engine.hpp>
#include <iostream>
#include <fstream>
#include <string>

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
static void initVulkanWithEngineMembers(
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

static void destroyVkFramebuffersVector(std::vector<VkFramebuffer>& swapChainFramebuffers, VkDevice& device)
{
    for(auto framebuffer : swapChainFramebuffers)
    {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
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
    initVulkanWithEngineMembers(
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
    RenderEngine::createRenderpass();
    RenderEngine::createGraphicsPipeline();
    RenderEngine::createFramebuffers();
}

void RenderEngine::mainLoop() 
{
    while (!glfwWindowShouldClose(RenderEngine::window)) 
    {
        glfwPollEvents();
        RenderEngine::drawFrame();
    }
}

void RenderEngine::cleanup() 
{
    if (vulkanaid::DEBUG_MODE) 
    {
        vulkanaid::destroyDebugMessenger(RenderEngine::instance, RenderEngine::debugMessenger);
    }

    vkDestroyShaderModule(device, RenderEngine::fragShaderModule, nullptr);
    vkDestroyShaderModule(device, RenderEngine::vertShaderModule, nullptr);
    vkDestroyPipeline(device, RenderEngine::graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device, RenderEngine::pipelineLayout, nullptr);
    destroyVkFramebuffersVector(RenderEngine::swapChainFramebuffers, RenderEngine::device);
    vkDestroyRenderPass(device, RenderEngine::renderPass, nullptr);
    vkDestroyCommandPool(RenderEngine::device, RenderEngine::commandPool, nullptr);
    destroyVkSwapChainImageViewsVector(RenderEngine::swapChainImagesViews, RenderEngine::device);
    vkDestroySwapchainKHR(RenderEngine::device, RenderEngine::swapChain, nullptr);
    vkDestroyDevice(RenderEngine::device, nullptr);
    vkDestroySurfaceKHR(RenderEngine::instance, RenderEngine::surface, nullptr);
    vkDestroyInstance(RenderEngine::instance, nullptr);

    glfwDestroyWindow(RenderEngine::window);
    glfwTerminate();
}
