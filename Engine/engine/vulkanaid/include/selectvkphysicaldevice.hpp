#ifndef SELECTVKPHYSICALDEVICE_HPP
#define SELECTVKPHYSICALDEVICE_HPP

#include <vulkan/vulkan.h>

/*
* Copyright (c) 2025 CortexR7
* 
* This Header defines a set of function to select the Physicaal devcice
* for the render engine
*/


void selectvkphysicaldevice(VkInstance& instance, VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface);


#endif