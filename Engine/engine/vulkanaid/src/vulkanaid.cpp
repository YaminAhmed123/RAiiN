#include <vulkanaid.hpp>
#include <createvkinstance.hpp>
#include <setupvkvalidationlayer.hpp>
#include <createvksurface.hpp>
#include <findqueuefamilyindices.hpp>
#include <selectvkphysicaldevice.hpp>
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
    if (vulkanaid::DEBUG_MODE) {
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

void vulkanaid::createLogicalDevice(VkPhysicalDevice& physicalDevice, VkDevice& device, VkQueue& graphicsQueue, VkQueue& presentQueue, VkSurfaceKHR& surface) {
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    // empoty device features for now
    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if (vulkanaid::DEBUG_MODE) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }    

    if(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS){
        throw std::runtime_error("failed to create a logical Device!");
    } else{
        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }
}
