#include <render_engine.hpp>
#include <iostream>
#include <Vertex.hpp>

// STATIC HELPER FUNCTIONS
uint32_t RenderEngine::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(this->physicalDevice, &memProperties);

    for(uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if(typeFilter & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}




/*
* WARNING: THIS DATA IS JUST A DUMMY
* IN FUTURE VERTEX DATA LIKE THIS WILL BE LOADED FROM 3D MODEL FILES
*/ 

// DUMMY DATA
#define VERTEX_DATA_SIZE 3
Vertex vertecies[VERTEX_DATA_SIZE];

void RenderEngine::createVertexBuffer()
{
    // INIT THE DUMMY DATA HERE:
    vertecies[0] = {{0.0f, -0.5f}, {1.0f, 0.3f, 1.0f}}; // bottom vertex, red color
    vertecies[1] = {{0.5f, 0.5f}, {0.0f, 1.0f, 0.5f}};  // top right vertex, green color
    vertecies[2] = {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}; // top left vertex, blue color
    // END OF DUMMY DATA INIT

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

    
    
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, this->vertexBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(this->device, this->vertexBuffer, this->vertexBufferMemory, 0);


    // COPY VERTEX DATA TO BUFFER MEMORY
    void* data;
    vkMapMemory(this->device, this->vertexBufferMemory, 0, bufferInfo.size, 0, &data);
    memcpy(data, vertecies, (size_t)bufferInfo.size);
    vkUnmapMemory(this->device, this->vertexBufferMemory);
}
