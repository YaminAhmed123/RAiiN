#ifndef CREATELOGICALDEVICE_HPP
#define CREATELOGICALDEVICE_HPP
#include <vulkan/vulkan.h>
#include <findqueuefamilyindices.hpp>

/*
* Copyright (c) 2025 CortexR7
* 
* This header declares a function that creates a logical device with graphics and present capabilities
*/

void createvklogicaldevice(VkPhysicalDevice& physicalDevice, VkDevice& device, VkQueue& graphicsQueue, VkQueue& presentQueue, VkSurfaceKHR& surface);

#endif