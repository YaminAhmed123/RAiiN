#include <render_engine.hpp>


void RenderEngine::createRenderpass()
{
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = RenderEngine::swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
}