#include <render_engine.hpp>
#include <iostream>
#include <Vertex.hpp>

#define VERTEX_DATA_SIZE 3

/*
* WARNING: THIS DATA IS JUST A DUMMY
* IN FUTURE VERTEX DATA LIKE THIS WILL BE LOADED FROM 3D MODEL FILES
*/ 

// DUMMY DATA
Vertex vertecies[VERTEX_DATA_SIZE];

void RenderEngine::createVertexBuffer()
{
    // INIT THE DUMMY DATA HERE:
    vertecies[0] = {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}}; // bottom vertex, red color
    vertecies[1] = {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}};  // top right vertex, green color
    vertecies[2] = {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}; // top left vertex, blue color

    // Create Vertex Buffer
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(Vertex) * VERTEX_DATA_SIZE; // size of 3 vertices
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &this->vertexBuffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create vertex buffer!");
    }
}
