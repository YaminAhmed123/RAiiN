#include <render_engine.hpp>
#include <iostream>


void RenderEngine::createFramebuffers()
{
    RenderEngine::swapChainFramebuffers.resize(RenderEngine::swapChainImagesViews.size());

    for (size_t i = 0; i < RenderEngine::swapChainImagesViews.size(); i++) 
    {
        VkImageView attachments[] = {
            RenderEngine::swapChainImagesViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = RenderEngine::renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = RenderEngine::swapChainExtent.width;
        framebufferInfo.height = RenderEngine::swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(RenderEngine::device, &framebufferInfo, nullptr, &RenderEngine::swapChainFramebuffers[i]) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}
