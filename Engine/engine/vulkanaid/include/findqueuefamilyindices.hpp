#ifndef FINDQUEUEFAMILYINDICES_HPP
#define FINDQUEUEFAMILYINDICES_HPP
#include <optional>
#include <vulkan/vulkan.h>
#include <vector>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR& surface);

#endif