#ifndef VULKANAID_HPP
#define VULKANAID_HPP

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>



/*
* Copyright (c) 2025 CortexR7
*
* This header defines a set of functions to aid in Vulkan development
* the functions that are in the raii namspace are based on RAII principles
* for all other functions it is advised to be dealt with care.
*/ 

namespace vulkanaid{

    inline bool DEBUG_MODE = true; // SET THIS TRUE OR FALSE WILL HAVE EFFECT ON ALL SYSTEMS THAT INCLUDE vulkanaid.hpp

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
