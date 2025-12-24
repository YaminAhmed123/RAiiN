#ifndef SETUPVKSWAPCHAIN_HPP
#define SETUPVKSWAPCHAIN_HPP
#include <vulkan/vulkan.h>
#include <vector>

/*
* Copyright (c) 2025 CortexR7
* 
* This header is for Swapchain creation
*/



typedef struct {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
} SwapChainSupportDetails;

inline SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device)
{
    SwapChainSupportDetails details;

    return details;
}

#endif