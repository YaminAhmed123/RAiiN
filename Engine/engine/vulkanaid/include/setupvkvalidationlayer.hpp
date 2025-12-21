#ifndef CREATEVALIDATIONLAYER_H
#define CREATEVALIDATIONLAYER_H
#include <vector>
#include <vulkan/vulkan.h>
#include <string>
#include <iostream>
#include <vulkanaid.hpp>

/*
*  Copyright (c) 2025 CortexR7
* 
*  This header defines a set of functions that are getting used to setup validation layers.
*  Please take into account that this header is a depedency of createvkinstance.hpp
*  Modifying this header may introduce issues with the other header.
*/

const std::vector validationLayers = {"VK_LAYER_KHRONOS_validation"};

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

void setupDebugMessengerValidation(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger);

bool validationSupport();

#endif