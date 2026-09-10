#include <VULKAN_PIPELINE.hpp>
#include <RE2_VERTEX.hpp>
#include <cstdint>

static std::vector<VkDynamicState> dynamicStates = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
};

static VkShaderModule CREATE_SHADER_MODULE(SHADER& SHADER, VULKAN_LOGICAL_DEVICE& LOGICAL_DEVICE)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = SHADER.SPIRV_SHADER_CODE.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(SHADER.SPIRV_SHADER_CODE.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(LOGICAL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        DEBUG_LOG("failed to create shader module!");
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

static void INIT_SHADERS_WITH_SLANG2SPIRV(ETL::StaticArray<SHADER>& SHADERS)
{
    SLANG2SPIRV VERTEX_SHADER_COMPILER;
    SLANG2SPIRV FRAGMENT_SHADER_COMPILER;

    VERTEX_SHADER_COMPILER.GEN_VERTEX_SHADER();
    FRAGMENT_SHADER_COMPILER.GEN_FRAGMENT_SHADER();

    SHADERS[0].SPIRV_SHADER_CODE = VERTEX_SHADER_COMPILER.GET_SHADER_CODE_AS_CHAR_VECTOR_VERTEX();
    SHADERS[0].SHADER_OF_TYPE = SHADER_TYPE::VERTEX_SHADER;
    SHADERS[1].SPIRV_SHADER_CODE = FRAGMENT_SHADER_COMPILER.GET_SHADER_CODE_AS_CHAR_VECTOR_FRAGMENT();
    SHADERS[1].SHADER_OF_TYPE = SHADER_TYPE::FRAGMENT_SHADER;
}

static void POPULATE_VERTEX_SHADER_STAGE_CREATE_INFO(VkPipelineShaderStageCreateInfo& vertShaderStageInfo, VkShaderModule& vertexShaderModule)
{
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertexShaderModule;
    vertShaderStageInfo.pName = "main";
}

static void POPULATE_FRAGMENT_SHADER_STAGE_CREATE_INFO(VkPipelineShaderStageCreateInfo& fragShaderStageInfo, VkShaderModule& fragmentShaderModule)
{
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragmentShaderModule;
    fragShaderStageInfo.pName = "main";
}

static void POPULATE_DYNAMIC_STATE_CREATE_INFO(VkPipelineDynamicStateCreateInfo& dynamicState)
{
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();
}

static void POPULATE_VERTEX_INPUT_STATE_CREATE_INFO(VkPipelineVertexInputStateCreateInfo& vertexInputInfo, RE2_V2D_I &vertexInputDesc, RE2_V2D_A& attributesInfoArray)
{
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &vertexInputDesc; // Optional
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributesInfoArray.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributesInfoArray.data(); // Optional
}

static void POPULATE_INPUT_ASSEMBLY_STATE_CREATE_INFO(VkPipelineInputAssemblyStateCreateInfo& inputAssembly)
{
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;
}

static void POPULATE_RASTERIZATION_STATE_CREATE_INFO(VkPipelineRasterizationStateCreateInfo& rasterizer)
{
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f; // Optional
    rasterizer.depthBiasClamp = 0.0f; // Optional
    rasterizer.depthBiasSlopeFactor = 0.0f; // Optional
}

static void POPULATE_MULTISAMPLE_STATE_CREATE_INFO(VkPipelineMultisampleStateCreateInfo& multisampling)
{
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f; // Optional
    multisampling.pSampleMask = nullptr; // Optional
    multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
    multisampling.alphaToOneEnable = VK_FALSE; // Optional
}

static void POPULATE_COLOR_BLEND_ATTACHMENT_STATE(VkPipelineColorBlendAttachmentState& colorBlendAttachment)
{
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional
}

static void POPULATE_COLOR_BLEND_STATE_CREATE_INFO(VkPipelineColorBlendStateCreateInfo& colorBlending, VkPipelineColorBlendAttachmentState* colorBlendAttachment)
{
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f; // Optional
    colorBlending.blendConstants[1] = 0.0f; // Optional
    colorBlending.blendConstants[2] = 0.0f; // Optional
    colorBlending.blendConstants[3] = 0.0f; // Optional
}

static void POPULATE_PIPELINE_LAYOUT_CREATE_INFO(VkPipelineLayoutCreateInfo& pipelineLayoutInfo)
{
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0; // Optional
    pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional
}





// NOTE: helper function for dynamic state configs and settings

static void VIEWPORT_SETTINGS(VkViewport& viewport, VULKAN_SWAPCHAIN& SWAPCHAIN)
{
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(SWAPCHAIN.GET_SWAPCHAIN_RESOLUTION().width);
    viewport.height = static_cast<float>(SWAPCHAIN.GET_SWAPCHAIN_RESOLUTION().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
}

static void SCISSOR_SETTINGS(VkRect2D& scissor, VULKAN_SWAPCHAIN& SWAPCHAIN)
{
    scissor.offset = {0, 0};
    scissor.extent = SWAPCHAIN.GET_SWAPCHAIN_RESOLUTION();
}

static void POPULATE_VIEWPORT_STATE_CREATE_INFO(VkPipelineViewportStateCreateInfo& viewportState, VkViewport* viewport, VkRect2D* scissor)
{
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = scissor;
}




void VULKAN_PIPELINE::INIT_PIPELINE(VULKAN_LOGICAL_DEVICE& LOGICAL_DEVICE, VULKAN_SWAPCHAIN& SWAPCHAIN, VkShaderModule& vertexShaderModule, VkShaderModule& fragmentShaderModule)
{
    INIT_SHADERS_WITH_SLANG2SPIRV(SHADERS);
    DEBUG_LOG("SHADERS COMPILED SUCCESSFULLY !!!");

    vertexShaderModule = CREATE_SHADER_MODULE(SHADERS[0], LOGICAL_DEVICE);
    fragmentShaderModule = CREATE_SHADER_MODULE(SHADERS[1], LOGICAL_DEVICE);
    DEBUG_LOG("SHADER MODULES CREATED SUCCESSFULLY !!!");

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    POPULATE_VERTEX_SHADER_STAGE_CREATE_INFO(vertShaderStageInfo, vertexShaderModule);
    POPULATE_FRAGMENT_SHADER_STAGE_CREATE_INFO(fragShaderStageInfo, fragmentShaderModule);
    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};
    DEBUG_LOG("PIPELINE VERTEX AND FRAGMENT SHADER STAGE CREATE INFOS HAVE BEEN POPULATED SUCCESSFULLY !!!");

    VkPipelineDynamicStateCreateInfo dynamicState{};
    POPULATE_DYNAMIC_STATE_CREATE_INFO(dynamicState);
    DEBUG_LOG("DYNAMIC STATES CREATE INFO HAS BEEN POPULATED SUCCESSFULLY !!!");

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    RE2_V2D_A attributesInfoArray = RE2_VERTEX2D::GET_VERTEX_ATTRIBUTE_DESC_VK();
    RE2_V2D_I vertexInputDesc = RE2_VERTEX2D::GET_VERTEX_INPUT_BINDING_DESC_VK();
    POPULATE_VERTEX_INPUT_STATE_CREATE_INFO(vertexInputInfo, vertexInputDesc, attributesInfoArray);
    DEBUG_LOG("VERTEX INPUT STATE CREATE INFO HAS BEEN POPULATED SUCCESSFULLY !!!");

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    POPULATE_INPUT_ASSEMBLY_STATE_CREATE_INFO(inputAssembly);
    DEBUG_LOG("INPUT ASSEMBLY STATE CREATE INFO HAS BEEN POPULATED SUCCESSFULLY !!!");

    VkViewport viewport{};
    VIEWPORT_SETTINGS(viewport, SWAPCHAIN);
    DEBUG_LOG("VIEWPORT SETTINGS HAVE BEEN SET SUCCESSFULLY !!!");

    VkRect2D scissor{};
    SCISSOR_SETTINGS(scissor, SWAPCHAIN);
    DEBUG_LOG("SCISSOR SETTINGS HAVE BEEN SET SUCCESSFULLY !!!");

    VkPipelineViewportStateCreateInfo viewportState{};
    POPULATE_VIEWPORT_STATE_CREATE_INFO(viewportState, &viewport, &scissor);
    DEBUG_LOG("VIEWPORT STATE CREATE INFO HAS BEEN POPULATED SUCCESSFULLY !!!");

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    POPULATE_RASTERIZATION_STATE_CREATE_INFO(rasterizer);
    DEBUG_LOG("RASTERIZATION STATE CREATE INFO HAS BEEN POPULATED SUCCESSFULLY !!!");

    VkPipelineMultisampleStateCreateInfo multisampling{};
    POPULATE_MULTISAMPLE_STATE_CREATE_INFO(multisampling);
    DEBUG_LOG("MULTISAMPLE STATE CREATE INFO HAS BEEN POPULATED SUCCESSFULLY !!!");

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    POPULATE_COLOR_BLEND_ATTACHMENT_STATE(colorBlendAttachment);
    DEBUG_LOG("COLOR BLEND ATTACHMENT STATE HAS BEEN POPULATED SUCCESSFULLY !!!");

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    POPULATE_COLOR_BLEND_STATE_CREATE_INFO(colorBlending, &colorBlendAttachment);
    DEBUG_LOG("COLOR BLEND STATE CREATE INFO HAS BEEN POPULATED SUCCESSFULLY !!!");

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    POPULATE_PIPELINE_LAYOUT_CREATE_INFO(pipelineLayoutInfo);
    DEBUG_LOG("PIPELINE LAYOUT CREATE INFO HAS BEEN POPULATED SUCCESSFULLY !!!");

    if (vkCreatePipelineLayout(LOGICAL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &pipelineLayoutInfo, nullptr, &PIPELINE_LAYOUT) != VK_SUCCESS)
    {
        DEBUG_LOG("FAILED TO CREATE PIPELINE LAYOUT !!!");
        throw std::runtime_error("failed to create pipeline layout!");
    } else {
        DEBUG_LOG("PIPELINE LAYOUT CREATED SUCCESSFULLY !!!");
    }



    // GRAPHICS PIPELINE CREATION
    VkFormat swapChainImageFormat = SWAPCHAIN.GET_SWAPCHAIN_IMAGE_FORMAT();
    VkPipelineRenderingCreateInfo pipelineRenderingInfo{};
    pipelineRenderingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
    pipelineRenderingInfo.colorAttachmentCount = 1;
    pipelineRenderingInfo.pColorAttachmentFormats = &swapChainImageFormat;
    pipelineRenderingInfo.depthAttachmentFormat   = VK_FORMAT_UNDEFINED;
    pipelineRenderingInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;


    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.pNext = &pipelineRenderingInfo; // NOTE: THIS STRUCTURE ADDS DYNAMIC RENDERING  INFO
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr; // Optional
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = this->PIPELINE_LAYOUT;


    if(vkCreateGraphicsPipelines(LOGICAL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &GRAPHICS_PIPELINE) != VK_SUCCESS)
    {
        DEBUG_LOG("FAILED TO CREATE GRAPHICS PIPELINE !!!");
        throw std::runtime_error("failed to create graphics pipeline!");
    } else {
        DEBUG_LOG("GRAPHICS PIPELINE CREATED SUCCESSFULLY !!!");
    }
}

void VULKAN_PIPELINE::INIT(VULKAN_LOGICAL_DEVICE& LOGICAL_DEVICE, VULKAN_SWAPCHAIN& SWAPCHAIN)
{
    VkShaderModule vertexShaderModule;
    VkShaderModule fragmentShaderModule;
    VULKAN_PIPELINE::INIT_PIPELINE(LOGICAL_DEVICE, SWAPCHAIN, vertexShaderModule, fragmentShaderModule);

    vkDestroyShaderModule(LOGICAL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), vertexShaderModule, nullptr);
    vkDestroyShaderModule(LOGICAL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), fragmentShaderModule, nullptr);
}

void VULKAN_PIPELINE::FREE(VULKAN_LOGICAL_DEVICE& LOGICAL_DEVICE)
{
    vkDestroyPipeline(LOGICAL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), GRAPHICS_PIPELINE, nullptr);
    vkDestroyPipelineLayout(LOGICAL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), PIPELINE_LAYOUT, nullptr);
}
