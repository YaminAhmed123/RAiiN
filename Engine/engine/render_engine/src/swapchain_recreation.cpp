#include <render_engine.hpp>
#include <setupvkswapchain.hpp>
#include <vulkanaid.hpp>


void RenderEngine::cleanUpSwapChain()
{
    for (auto framebuffer : swapChainFramebuffers) 
    {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

    for (auto imageView : swapChainImagesViews) 
    {
        vkDestroyImageView(device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(device, swapChain, nullptr);
}

void RenderEngine::recreateSwapChain()
{
    vkDeviceWaitIdle(this->device);

    RenderEngine::cleanUpSwapChain();
    vulkanaid::setSwapChainExtentAndFormat(
        this->window,
        this->physicalDevice,
        this->surface,
        this->swapChainExtent,
        this->swapChainImageFormat
    );
    vulkanaid::createSwapChain(
        this->window,
        this->physicalDevice,
        this->device,
        this->surface,
        this->swapChain
    );
    vulkanaid::getSwapChainImages(
        this->device,
        this->swapChain,
        this->swapChainImages
    );
    vulkanaid::createSwaapChainImageViews(
        this->swapChainImages,
        this->swapChainImagesViews,
        this->swapChainImageFormat,
        this->device
    );
    RenderEngine::createFramebuffers();
}