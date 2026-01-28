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


// valid implementations
void RenderEngine::run()
{
    RenderEngine::initWindow();
    RenderEngine::initVulkan();
    RenderEngine::mainLoop();
    RenderEngine::cleanup();
}

static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto app = reinterpret_cast<RenderEngine*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

void RenderEngine::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    RenderEngine::window = glfwCreateWindow(WIDTH, HEIGHT, "RAiiN Engine", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    glfwSetWindowUserPointer(window, this);
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
    RenderEngine::createCommandPool();
    RenderEngine::createVertexBuffer();
    RenderEngine::createCommandBuffer();
    RenderEngine::createSyncObjects();
}

void RenderEngine::mainLoop()
{
    while (!glfwWindowShouldClose(RenderEngine::window))
    {
        glfwPollEvents();
        RenderEngine::drawFrame();
    }
    vkDeviceWaitIdle(this->device);
}

void RenderEngine::cleanup()
{
    if (vulkanaid::DEBUG_MODE)
    {
        vulkanaid::destroyDebugMessenger(RenderEngine::instance, RenderEngine::debugMessenger);
    }

    cleanUpSwapChain();


    vkDestroyPipeline(device, RenderEngine::graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device, RenderEngine::pipelineLayout, nullptr);
    vkDestroyRenderPass(device, RenderEngine::renderPass, nullptr);

    vkDestroyCommandPool(RenderEngine::device, RenderEngine::commandPool, nullptr);
    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
        vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
        vkDestroyFence(device, inFlightFences[i], nullptr);
    }

    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        for(size_t j = 0; j < swapChainImages.size(); j++)
        {
            vkDestroySemaphore(device, swapChainSemaphores[i].imageAvailableSemaphores[j], nullptr);
        }
    }

    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);
    vkDestroyDevice(RenderEngine::device, nullptr);
    vkDestroySurfaceKHR(RenderEngine::instance, RenderEngine::surface, nullptr);
    vkDestroyInstance(RenderEngine::instance, nullptr);

    glfwDestroyWindow(RenderEngine::window);
    glfwTerminate();
}
