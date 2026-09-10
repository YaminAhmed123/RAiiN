#include <RENDER_ENGINE2.hpp>
#include <functional>


void RENDER_ENGINE2::INIT_ENGINE()
{
    VK_INSTANCE.INIT_INSTANCE();
    DEBUG_LOG("Vulkan instance created successfully!");
    MAIN_WINDOW.INIT_WINDOW(this->VK_INSTANCE);
    this->INIT_WINDOW_CALLBACKS();
    DEBUG_LOG("Main window initialized!");
    VKP_DEVICE.INIT_DEVICE(this->MAIN_WINDOW, this->VK_INSTANCE);
    DEBUG_LOG("Vulkan physical device initialized!");
    VKP_DEVICE.META_DATA.PRINT_META_INFO_DBG();
    VKL_DEVICE.INIT(this->VKP_DEVICE, MAIN_WINDOW, this->deviceExtensions, this->validationLayers, false); // ! WARNING ! need to figure out why thE "false" is wrong later
    DEBUG_LOG("Vulkan logical device initialized!");
    VK_SWAPCHAIN.INIT(MAIN_WINDOW, VKP_DEVICE, VKL_DEVICE);
    DEBUG_LOG("Vulkan swapchain initialized!");
    VK_BUFFER.INIT((void*)RE2_DUMMY_VERTEX_DATA.data(), static_cast<size_t>(sizeof(RE2_DUMMY_VERTEX_DATA[0]) * RE2_DUMMY_VERTEX_DATA.size()), this->VKL_DEVICE, this->VKP_DEVICE);
    VK_PIPELINE.INIT(VKL_DEVICE, VK_SWAPCHAIN);
    DEBUG_LOG("Vulkan pipeline initialized!");
    VK_CMD.INIT(VKP_DEVICE, MAIN_WINDOW, VKL_DEVICE, FRAMES_IN_FLIGHT);
    DEBUG_LOG("Vulkan command pool and buffers initialized!");
    VK_SYNC.INIT(this->VKL_DEVICE, this->FRAMES_IN_FLIGHT, this->VK_SWAPCHAIN);
    DEBUG_LOG("Vulkan SYNC objetcs have been initialized !");
}

void RENDER_ENGINE2::RUN_ENGINE()
{
    while (!glfwWindowShouldClose(MAIN_WINDOW.getWindow()))
    {
        glfwPollEvents();
        this->DRAW_FRAME();
    }
}

void RENDER_ENGINE2::DRAW_FRAME(void)
{
    vkWaitForFences(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), 1, &VK_SYNC.FENCES.DATA()[CURRENT_FRAME], VK_TRUE, UINT64_MAX);
    vkResetFences(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), 1, &VK_SYNC.FENCES.DATA()[CURRENT_FRAME]);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(
        VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(),
        VK_SWAPCHAIN.SW_CHAIN,
        UINT64_MAX,
        VK_SYNC.SEMAPHORES_IMAGE_AVAILABLE.DATA()[CURRENT_FRAME],
        VK_NULL_HANDLE,
        &imageIndex
    );

    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        this->RECREATE_SW_CHAIN_SAFELY(this->MAIN_WINDOW.getWidth(), MAIN_WINDOW.getHeight());
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    VK_CMD.RECORD_CMD_BUFFER_GRAPHICS(
        this->VK_CMD.CMD_BUFFERS_GRAPHICS.DATA()[CURRENT_FRAME],
        imageIndex,
        this->VK_SWAPCHAIN,
        this->VK_PIPELINE,
        this->VK_BUFFER
    );

    VkSubmitInfo submitInfo{};
    VkSemaphore waitSemaphores[] = {VK_SYNC.SEMAPHORES_IMAGE_AVAILABLE.DATA()[CURRENT_FRAME]};
    VkSemaphore signalSemaphores[] = {VK_SYNC.SEMAPHORES_RENDER_FINISHED_PER_SW.DATA()[CURRENT_FRAME].SEMAPHORES.DATA()[imageIndex]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &VK_CMD.CMD_BUFFERS_GRAPHICS.DATA()[CURRENT_FRAME];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(VKL_DEVICE.VK_QUEUE.GRAPHICS_QUEUE, 1, &submitInfo, VK_SYNC.FENCES.DATA()[CURRENT_FRAME]) != VK_SUCCESS) {
        DEBUG_LOG("FAILED TO DRAW CMD BUFFER !!!!!");
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkSwapchainKHR swapChains[] = {VK_SWAPCHAIN.SW_CHAIN};
    VkPresentInfoKHR presentInfo{};

    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(VKL_DEVICE.VK_QUEUE.PRESENT_QUEUE, &presentInfo);

    this->CURRENT_FRAME = (this->CURRENT_FRAME + 1) % this->FRAMES_IN_FLIGHT;
}

void RENDER_ENGINE2::FREE_ENGINE()
{
    vkDeviceWaitIdle(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE());
    VK_CMD.FREE(VKL_DEVICE);
    VK_SYNC.FREE(VKL_DEVICE);
    VK_PIPELINE.FREE(VKL_DEVICE);
    VK_BUFFER.FREE();
    VK_SWAPCHAIN.FREE();
    MAIN_WINDOW.FREE(VK_INSTANCE);
    VKL_DEVICE.FREE();
    VK_INSTANCE.FREE();
}

RENDER_ENGINE2::RENDER_ENGINE2()
{
    this->INIT_ENGINE();
}

RENDER_ENGINE2::~RENDER_ENGINE2()
{
    this->FREE_ENGINE();
}

void RENDER_ENGINE2::INIT_WINDOW_CALLBACKS()
{
    DEBUG_LOG("SETTING UP WINDOW CALLBACKS FROM REENDER_ENGINE2");
    this->RECREATE_SW_CHAIN_SAFELY = [&] (int width, int height) -> void {
        VKL_DEVICE.RESUME_AFTER_STALL();
        DEBUG_LOG("RUNNING______AFTER_____________STALL");
        MAIN_WINDOW.setHeight(height);
        MAIN_WINDOW.setWidth(width);
        VK_SWAPCHAIN.RE_INIT(this->MAIN_WINDOW, this->VKP_DEVICE, this->VKL_DEVICE);
        VK_SYNC.RE_INIT(this->VKL_DEVICE, this->FRAMES_IN_FLIGHT,this->VK_SWAPCHAIN);
        DEBUG_LOG("FINSIHED________RECREATING________VK_SYNC_____OBJECTS");
    };
    this->MAIN_WINDOW.FRAMEBUFFER_SIZE_CALLBACK_IMPL = this->RECREATE_SW_CHAIN_SAFELY;
}
