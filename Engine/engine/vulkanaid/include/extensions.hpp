#ifndef EXTENSION_HPP
#define EXTENSION_HPP

#include <vector>
#include <vulkan/vulkan.h>

/*
* Copyright (c) 2026 CortexR7
* 
* This header defines device extensions
*/
std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME
};

#endif