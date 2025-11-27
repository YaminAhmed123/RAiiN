#ifndef VULKANAID_H
#define VULKANAID_H

#include <vulkan/vulkan.h>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkanaid.hpp>

/*
* Copyright (c) 2025 CortexR7
*
* This header defines a set of functions to aid in Vulkan development
* the functions that are in the raii namspace are based on RAII principles
* for all other functions it is advised to be dealt with care.
*/ 

namespace vulkanaid{

    inline bool DEBUG_MODE= true; // define if Vulkan should use Validation Layers or not

    namespace raii{
        // RAII classes and functions to help with Vulkan resource management will go here
    }

    // Other helper functions for Vulkan development will go here
    void createVulkanInstance(VkInstance& instance);
    void setupDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger);
    void createSurface(VkInstance& instance, VkSurfaceKHR& surface, GLFWwindow* window);
    void pickPhysicalDevice(VkInstance& instance, VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface);
    void createLogicalDevice(VkPhysicalDevice& physicalDevice, VkDevice& device, VkQueue& graphicsQueue, VkQueue& presentQueue, VkSurfaceKHR& surface);
    void destroyDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger);
}

#endif 