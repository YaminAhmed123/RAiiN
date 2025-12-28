#ifndef SURFACE_H
#define SURFACE_H
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>


/*
* Copyright (c) 2025 CortexR7
* 
* This header uses perprocessor to select the proper include for the surface
* It only creates a surface for windows or either linux.
*/ 

#ifdef _WIN32
    #define GLFW_INCLUDE_VULKAN
    #define VK_USE_PLATFORM_WIN32_KHR
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#elif __linux__
    #define GLFW_INCLUDE_VULKAN
    #define VK_USE_PLATFORM_WAYLAND_KHR
    #define GLFW_EXPOSE_NATIVE_WAYLAND
    #include <GLFW/glfw3native.h>
#endif

void createvksurface(VkInstance& instance, VkSurfaceKHR& surface, GLFWwindow* window);

#endif