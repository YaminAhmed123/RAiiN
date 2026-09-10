#include <RE2_VERTEX.hpp>
#include <cstddef>

VkVertexInputBindingDescription RE2_VERTEX2D::GET_VERTEX_INPUT_BINDING_DESC_VK()
{
    VkVertexInputBindingDescription VERTEX_INPUT_DESC{};

    VERTEX_INPUT_DESC.binding = 0;
    VERTEX_INPUT_DESC.stride = sizeof(RE2_VERTEX2D);
    VERTEX_INPUT_DESC.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return VERTEX_INPUT_DESC;
}

std::array<VkVertexInputAttributeDescription, 2> RE2_VERTEX2D::GET_VERTEX_ATTRIBUTE_DESC_VK()
{
    std::array<VkVertexInputAttributeDescription, 2> VERTEX_ATTRIBUTE_DESC = {
        {
            // NOTE: The structure here resolves to a "VkVertexInputAttributeDescription"
            {
                .location = 0,
                .binding = 0,
                .format = VK_FORMAT_R32G32_SFLOAT,
                .offset = offsetof(RE2_VERTEX2D, position),
            },
            {
                .location = 1,
                .binding = 0,
                .format = VK_FORMAT_R32G32B32_SFLOAT,
                .offset = offsetof(RE2_VERTEX2D, rgb),
            }
        }
    };
    return VERTEX_ATTRIBUTE_DESC;
}
