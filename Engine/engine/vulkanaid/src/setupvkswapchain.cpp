#include <setupvkswapchain.hpp>

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device, VkSurfaceKHR& surface)
{
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);


    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    details.formats.resize(formatCount);
    if(formatCount != 0){
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }
    

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
    details.presentModes.resize(presentModeCount);
    if(presentModeCount != 0){
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }
    

    return details;
}

bool isSwapChainSuitable(VkPhysicalDevice& device, VkSurfaceKHR& surface)
{
    SwapChainSupportDetails swap_chain_support_details = querySwapChainSupport(device, surface);
    return (!swap_chain_support_details.formats.empty() && !swap_chain_support_details.presentModes.empty());
}