#ifndef RE2_VK_BUFFER_H
#define RE2_VK_BUFFER_H

/*
*  Copyright (c) 2026 CortexR7
*
*  This Header file defines a vulkan buffer object.
*  Which can take input data and store it in VRAM.
*/


#include <vulkan/vulkan.h>
#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <VULKAN_PHYSICAL_DEVICE.hpp>

#define DEBUG_ON                    // NOTE: Comment this macro out if u want to disable DEBUG_LOGs for RE2_VK_BUFFER
#include <ETL.hpp>


class RE2_VK_BUFFER{

    private:
    VULKAN_LOGICAL_DEVICE LGD;
    VULKAN_PHYSICAL_DEVICE PHD;
    VkDeviceMemory VERTEX_BUFFER_MEMORY;

    void SETUP_ALLOCATE_MEMORY(VULKAN_LOGICAL_DEVICE LGD,VULKAN_PHYSICAL_DEVICE PHD);
    void WRITE_DATA_TO_MEMORY(void* DATA, size_t SIZE);

    public:
    VkBuffer VERTEX_BUFFER;
    void INIT(void* DATA, size_t SIZE, VULKAN_LOGICAL_DEVICE LGD, VULKAN_PHYSICAL_DEVICE PHD);
    void FREE(VULKAN_LOGICAL_DEVICE LGD);
    void FREE();


    RE2_VK_BUFFER(VULKAN_LOGICAL_DEVICE LGD,VULKAN_PHYSICAL_DEVICE PHD, size_t SIZE, void* DATA);
    ~RE2_VK_BUFFER();

    RE2_VK_BUFFER();
};

#endif
