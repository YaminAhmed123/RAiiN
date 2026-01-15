#include <render_engine.hpp>
#include <tools.hpp>
#include <string>
#include <iostream>


void RenderEngine::checkForSwapChainRecreation(VkResult result, int mode)
{
    using namespace tools;
    if(mode == 0)
    {
        if (result == VK_ERROR_OUT_OF_DATE_KHR) 
        {
            LOG("Swapchain out of date, recreating swapchain...");
            this->framebufferResized = false;
            RenderEngine::recreateSwapChain();
            LOG("Swapchain recreated successfully.");
            return;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) 
        {
            throw std::runtime_error("Failed to acquire swap chain image!");
        }
    } else{
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || this->framebufferResized) 
        {
            this->framebufferResized = false;
            LOG("Swapchain out of date or suboptimal, recreating swapchain...");
            RenderEngine::recreateSwapChain();
            LOG("Swapchain recreated successfully.");
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }
    }
}

void RenderEngine::drawFrame()
{
    LOG("Starting Draw Frame...");
    vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX); // this param "UINT64_MAX" effectively disables the timeout

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(this->device, this->swapChain, UINT64_MAX, this->imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
    RenderEngine::checkForSwapChainRecreation(result, 0);
    vkResetFences(device, 1, &inFlightFences[currentFrame]);

    vkResetCommandBuffer(commandBuffers[currentFrame], 0);
    recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;


    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to submit draw command buffer!");
    }



    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    

    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    result = vkQueuePresentKHR(presentQueue, &presentInfo);
    RenderEngine::checkForSwapChainRecreation(result, 1);


    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

    std::string msg =  "Frame: " + std::to_string(currentFrame) + " drawn successfully.";
    LOG(msg);
}
