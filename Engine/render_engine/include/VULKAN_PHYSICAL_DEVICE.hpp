#ifndef VULKAN_PHYSICAL_DEVICE_HPP
#define VULKAN_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.h>
#include <WINDOW.hpp>
#include <VULKAN_INSTANCE.hpp>
#include <string>

#define DEBUG_ON
#include <ETL.hpp>

/*
*  Copyright (c) 2025 CortexR7
*
*  This header defines an object that is supposed to Model a Physical device with
*  That  is used for rendering and later there will be an option to get a physical device for genrell purposes
*  Like compute shaders etc.
*
*/

struct VULKAN_PHYSICAL_DEVICE_PRINTABLE_META_DATA{
    std::string apiVersion;
    std::string driverName;
    std::string driverInfo;
    std::string deviceName;

    void PRINT_META_INFO();     // this one caan be used to indepnedetly log the meta data even if DEBUG_ON is not defined
    void PRINT_META_INFO_DBG(); // us this method for DEBUG_LOGGING
};

class VULKAN_PHYSICAL_DEVICE{
    private:
    void INIT_META_DATA();
    VkPhysicalDevice PH_DEVICE = VK_NULL_HANDLE;

    public:
    VULKAN_PHYSICAL_DEVICE_PRINTABLE_META_DATA META_DATA;

    void INIT_DEVICE(WINDOW& WIN, VULKAN_INSTANCE& INSTANCE);
    VkPhysicalDevice GET_VK_HANDLE_TO_DEVICE();
};

#endif
