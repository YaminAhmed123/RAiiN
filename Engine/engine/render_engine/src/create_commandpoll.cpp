#include <render_engine.hpp>
#include <findqueuefamilyindices.hpp>
#include <iostream>


void RenderEngine::createCommandPool()
{
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(RenderEngine::physicalDevice, RenderEngine::surface);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(RenderEngine::device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)  // commandPool means RenderEngine::commandPool
    {
        throw std::runtime_error("failed to create command pool!");
    }
}
