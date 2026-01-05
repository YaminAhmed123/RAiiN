#include <render_engine.hpp>
#include <vector>
#include <iostream>
#include <fstream>


// At this part of the static function we have a set of static function 
// that are meant to help develop the createGraphicsPipeline function
static std::vector<char> ShaderLoader(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) 
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    
    return buffer;
}

static VkShaderModule createShaderModule(const std::vector<char>& shaderCode, VkDevice& device)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = shaderCode.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());

    VkShaderModule shaderModule;
    if(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule; 
}
// End of static functions meant to help develop in graphics Pipeline


void RenderEngine::createGraphicsPipeline()
{
    auto vertShaderCode = ShaderLoader("/home/yamin/repos/HATE/SPIR-V/vert.spv");   // absolute path for temporary only
    auto fragShaderCode = ShaderLoader("/home/yamin/repos/HATE/SPIR-V/frag.spv");   // absolute path for temporary only

    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, RenderEngine::device);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, RenderEngine::device);
}
