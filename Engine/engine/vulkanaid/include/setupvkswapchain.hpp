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


SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device, VkSurfaceKHR& surface);
bool isSwapChainSuitable(VkPhysicalDevice& device, VkSurfaceKHR& surface);

#endif