#ifndef VULKAN_CMD_HPP
#define VULKAN_CMD_HPP

#include <vulkan/vulkan.h>
#include <VULKAN_QUEUE.hpp>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <WINDOW.hpp>
#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <VULKAN_SWAPCHAIN.hpp>
#include <VULKAN_PIPELINE.hpp>

// utility
#include <RE2_VK_BUFFER.hpp>


#define DEBUG_ON            // NOTE: comment this line out to disable debug logs for "VULKAN_CMD.cpp"
#include <ETL.hpp>



class VULKAN_CMD{
    public:
    VkCommandPool CMD_POOL_GRAPHICS;
    ETL::DYNAMIC_ARRAY<VkCommandBuffer> CMD_BUFFERS_GRAPHICS{1, 1.0f};

    void INIT(VULKAN_PHYSICAL_DEVICE& PH_DEVICE, WINDOW& WIN, VULKAN_LOGICAL_DEVICE& LG_DEVICE, uint8_t FRAMES_IN_FLIGHT);
    void RECORD_CMD_BUFFER_GRAPHICS(VkCommandBuffer& CMD_BUFFER, uint32_t imageIndex, VULKAN_SWAPCHAIN& SWAPCHAIN, VULKAN_PIPELINE& PIPELINE, RE2_VK_BUFFER& VK_BUFFER);
    void FREE(VULKAN_LOGICAL_DEVICE& LG_DEVICE);
};

#endif
