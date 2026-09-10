#ifndef RENDER_ENGINE_2_HPP
#define RENDER_ENGINE_2_HPP

#include <WINDOW.hpp>
#include <VULKAN_INSTANCE.hpp>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <VULKAN_SWAPCHAIN.hpp>
#include <VULKAN_PIPELINE.hpp>
#include <VULKAN_CMD.hpp>
#include <VULKAN_QUEUE.hpp>
#include <VULKAN_SYNC.hpp>

// utility class
#include <RE2_VERTEX.hpp>
#include <RE2_VK_BUFFER.hpp>


#define DEBUG_ON
#include <ETL.hpp>

/*
*  Copyright (c) 2026 CortexR7
*
*  This header defines the render_engine itself and all its core functionalities
*  the engine is still in alpha stage and is under heavy development.
*  In future the vulkanaid module will probably get merged with the render engine.
*  The render engine uses now a half baked approach where it uses vulkanaid as a vulkan abstraction
*  to create some of the setup while other functionality is getting implemented by the engine itself.
*  This is not ideal and will be changed later.
*  For now I dont know in which direction it will go but it will either remove vulkanaid fully or shift all the logic to vulkanaid over.
*/

class RENDER_ENGINE2{
    private:
    void INIT_ENGINE();
    void INIT_WINDOW_CALLBACKS();
    void FREE_ENGINE();

    std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME
    };

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<RE2_V2D> RE2_DUMMY_VERTEX_DATA = {
        {{-1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}},  // top-left
        {{ 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},  // bottom
        {{ 1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}},  // top-right
    };

    /*  // NOTE: This data was culled away (I think due to backface culling)
        const std::vector<RE2_V2D> RE2_DUMMY_VERTEX_DATA = {
                {{-0.9f, 0.9f}, {0.0f, 0.0f, 1.0f}},
                {{0.9f, 0.9f}, {1.0f, 0.0f, 0.0f}},
                {{0.0f, -0.9f}, {0.0f, 1.0f, 0.0f}}
        };
     */


    public:
    WINDOW MAIN_WINDOW;
    VULKAN_INSTANCE VK_INSTANCE;
    VULKAN_PHYSICAL_DEVICE VKP_DEVICE;
    VULKAN_LOGICAL_DEVICE VKL_DEVICE;
    VULKAN_SWAPCHAIN VK_SWAPCHAIN;
    VULKAN_PIPELINE VK_PIPELINE;
    VULKAN_CMD VK_CMD;
    QUEUE VK_QUEUE;
    VULKAN_SYNC VK_SYNC;
    RE2_VK_BUFFER VK_BUFFER;
    uint8_t FRAMES_IN_FLIGHT = 2;
    uint8_t CURRENT_FRAME = 0;

    std::function<void(int, int)> RECREATE_SW_CHAIN_SAFELY;

    void RUN_ENGINE();
    void DRAW_FRAME(void);


    RENDER_ENGINE2();
    ~RENDER_ENGINE2();
};

#endif
