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

void vulkanaid::setSwapChainExtentAndFormat(GLFWwindow*& window, VkPhysicalDevice& device, VkSurfaceKHR& surface, VkExtent2D& swapChainExtent, VkFormat& format)
{
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkExtent2D extent = chooseSwapExtent(window, swapChainSupport.capabilities);

    swapChainExtent = extent;
    format = surfaceFormat.format;
}

void vulkanaid::createSwaapChainImageViews(std::vector<VkImage>& swapChainImages, std::vector<VkImageView>& swapChainImageViews, VkFormat& swapChainImageFormat, VkDevice& device)
{
    swapChainImageViews.resize(swapChainImages.size());

    for (size_t i = 0; i < swapChainImages.size(); i++) 
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages[i];

        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = swapChainImageFormat;

        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if(vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create image views!");
        }
    }

}
