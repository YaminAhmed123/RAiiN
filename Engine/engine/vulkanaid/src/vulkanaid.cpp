#include <vulkanaid.hpp>
#include <createvkinstance.hpp>
#include <setupvkvalidationlayer.hpp>
#include <createvksurface.hpp>
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


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR& surface) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (presentSupport){
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}



static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR& surface) {
    QueueFamilyIndices indices = findQueueFamilies(device, surface);

    return indices.isComplete();
}




void vulkanaid::createVulkanInstance(VkInstance& instance) {
    createVkInstance(instance);
}

void vulkanaid::setupDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger) {
    setupDebugMessengerValidation(instance, debugMessenger);
}

void vulkanaid::destroyDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger) {
    if (vulkanaid::DEBUG_MODE) {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
}

void vulkanaid::createSurface(VkInstance& instance, VkSurfaceKHR& surface, GLFWwindow* window) {
    createvksurface(instance, surface, window);
}

void vulkanaid::pickPhysicalDevice(VkInstance& instance, VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device, surface)) {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
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
