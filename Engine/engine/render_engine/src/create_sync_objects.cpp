#include <render_engine.hpp>
#include <iostream>


void RenderEngine::createSyncObjects()
{
    this->imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->swapChainSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);


    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) 
    {
        if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {

            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }


    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        swapChainSemaphores[i].imageAvailableSemaphores.resize(swapChainImages.size());

        for(size_t j = 0; j < swapChainImages.size(); j++)
        {
            if(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &swapChainSemaphores[i].imageAvailableSemaphores[j]) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to create swap chain semaphore!");
            }
        }
    }
}
