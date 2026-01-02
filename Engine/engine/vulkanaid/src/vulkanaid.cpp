#include <vulkanaid.hpp>
#include <createvkinstance.hpp>
#include <setupvkvalidationlayer.hpp>
#include <createvksurface.hpp>
#include <findqueuefamilyindices.hpp>
#include <selectvkphysicaldevice.hpp>
#include <createvklogicaldevice.hpp>
#include <setupvkswapchain.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <optional>



/*
* Copyright (c) 2025 CortexR7
* 
* This source file implements a set of functions to aid in Vulkan development
* This function will be splitted into multiple files in future releases
* The current supports will dependt really heavily until the engine is more mature
*/

void vulkanaid::createVulkanInstance(VkInstance& instance) 
{
    createVkInstance(instance);
}

void vulkanaid::setupDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger) 
{
    setupDebugMessengerValidation(instance, debugMessenger);
}

void vulkanaid::destroyDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger)
{
    if (vulkanaid::DEBUG_MODE) 
    {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
}

void vulkanaid::createSurface(VkInstance& instance, VkSurfaceKHR& surface, GLFWwindow* window) 
{
    createvksurface(instance, surface, window);
}

void vulkanaid::pickPhysicalDevice(VkInstance& instance, VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface) 
{
    selectvkphysicaldevice(instance, physicalDevice, surface);
}

void vulkanaid::createLogicalDevice(VkPhysicalDevice& physicalDevice, VkDevice& device, VkQueue& graphicsQueue, VkQueue& presentQueue, VkSurfaceKHR& surface) 
{
    createvklogicaldevice(physicalDevice, device, graphicsQueue, presentQueue, surface);
}

void vulkanaid::createSwapChain(GLFWwindow*& window, VkPhysicalDevice& device, VkDevice& deviceL, VkSurfaceKHR& surface, VkSwapchainKHR& swapChain)
{
    createVkSwapChain(window, device, deviceL, surface, swapChain);
}

void vulkanaid::getSwapChainImages(VkDevice& device, VkSwapchainKHR& swapChain, std::vector<VkImage>& swapChainImages)
{
    uint32_t imageCount;

    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());
}