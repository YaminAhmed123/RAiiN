#ifndef RE2_VERTEX_HEADER
#define RE2_VERTEX_HEADER

/*
*  Copyright (c) 2026 CortexR7
*
*  This Header file defines a set of Vertex types that RE2 "RENDER_ENGINE2" will use
*  to render vertex data.
*/


#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

struct RE2_VERTEX2D{
    glm::vec2 position; // position in a 2D space (technically just two floats)             // attribute 0
    glm::vec3 rgb;      // color in the form of rgb. currently no alpha channel supported.  // attribute 1

    static VkVertexInputBindingDescription GET_VERTEX_INPUT_BINDING_DESC_VK();
    static std::array<VkVertexInputAttributeDescription, 2> GET_VERTEX_ATTRIBUTE_DESC_VK();
};

using RE2_V2D = RE2_VERTEX2D;
using RE2_V2D_A = std::array<VkVertexInputAttributeDescription, 2>;
using RE2_V2D_I = VkVertexInputBindingDescription;

#endif
