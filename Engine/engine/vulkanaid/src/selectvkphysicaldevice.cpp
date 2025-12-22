#include <selectvkphysicaldevice.hpp>
#include <vector>
#include <iostream>
#include <optional>
#include <findqueuefamilyindices.hpp>



static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR& surface)
{
    QueueFamilyIndices indices = findQueueFamilies(device, surface);

    return indices.isComplete();
}

void selectvkphysicaldevice(VkInstance& instance, VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find devices with Vulkan support!");
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