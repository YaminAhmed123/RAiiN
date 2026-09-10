#include <cstring>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <RE2_VK_BUFFER.hpp>
#include <cstddef>
#include <cstdint>
#include <stdexcept>


void RE2_VK_BUFFER::INIT(void* DATA, size_t SIZE, VULKAN_LOGICAL_DEVICE LGD, VULKAN_PHYSICAL_DEVICE PHD)
{
    this->LGD = LGD;
    this->PHD = PHD;
    VkBufferCreateInfo BUFFER_INFO{};
    BUFFER_INFO.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    BUFFER_INFO.size = SIZE;
    BUFFER_INFO.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    BUFFER_INFO.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &BUFFER_INFO, nullptr, &this->VERTEX_BUFFER) != VK_SUCCESS) {
        DEBUG_ERR("FAILED TO CREATE A VK BUFFER USING THE RE2_VK_BUFFER UTILITY CLASS !!!!");
        throw std::runtime_error("failed to create vertex buffer!");
    }

    this->SETUP_ALLOCATE_MEMORY(this->LGD, this->PHD);
    this->WRITE_DATA_TO_MEMORY(DATA, SIZE);
}

void RE2_VK_BUFFER::FREE(VULKAN_LOGICAL_DEVICE LGD)
{
    vkDestroyBuffer(LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->VERTEX_BUFFER, nullptr);
    vkFreeMemory(LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->VERTEX_BUFFER_MEMORY, nullptr);
}

void RE2_VK_BUFFER::FREE()
{
    vkDestroyBuffer(this->LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->VERTEX_BUFFER, nullptr);
    vkFreeMemory(this->LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->VERTEX_BUFFER_MEMORY, nullptr);
}

RE2_VK_BUFFER::RE2_VK_BUFFER(VULKAN_LOGICAL_DEVICE LGD, VULKAN_PHYSICAL_DEVICE PHD, size_t SIZE, void* DATA)
{
    this->INIT(DATA, SIZE, LGD, PHD);
}

RE2_VK_BUFFER::~RE2_VK_BUFFER(){}

static uint32_t FIND_MEMORY_TYPE(uint32_t TYPE_BITMASK, VkMemoryPropertyFlags PROPERTIES, VULKAN_PHYSICAL_DEVICE PHYSICAL_DEVICE)
{
    VkPhysicalDeviceMemoryProperties MEMORY_PROPS;
    vkGetPhysicalDeviceMemoryProperties(PHYSICAL_DEVICE.GET_VK_HANDLE_TO_DEVICE(), &MEMORY_PROPS);

    for(uint32_t i = 0; i < MEMORY_PROPS.memoryTypeCount; ++i)
    {
        if((TYPE_BITMASK & (1 << i)) && ((MEMORY_PROPS.memoryTypes[i].propertyFlags) & PROPERTIES))
        {
            return i;
        }
    }
    return -1;
}

void RE2_VK_BUFFER::SETUP_ALLOCATE_MEMORY(VULKAN_LOGICAL_DEVICE LGD,VULKAN_PHYSICAL_DEVICE PHD)
{
    VkMemoryRequirements MEMORY_REQUIREMENTS;
    vkGetBufferMemoryRequirements(LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->VERTEX_BUFFER, &MEMORY_REQUIREMENTS);

    VkMemoryAllocateInfo ALLOC_INFO{};
    ALLOC_INFO.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ALLOC_INFO.allocationSize = MEMORY_REQUIREMENTS.size;
    ALLOC_INFO.memoryTypeIndex = FIND_MEMORY_TYPE(
        MEMORY_REQUIREMENTS.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        this->PHD
    );


    if(vkAllocateMemory(LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &ALLOC_INFO, nullptr, &this->VERTEX_BUFFER_MEMORY) != VK_SUCCESS) {
        DEBUG_ERR("THE ALLOCATION OF MEORY FOR THE VERTEX_BUFFER FAILED !!!!! please have a look at:'vkAllocateMemory()' in the RE2_VK_BUFFER.cpp TU");
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    if(vkBindBufferMemory(LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->VERTEX_BUFFER, this->VERTEX_BUFFER_MEMORY, 0) != VK_SUCCESS)
    {
        DEBUG_ERR("BINDING THE BUFFER WITH BUFFER MEMORY FAILED !!!!! please have a look at:'vkBindBufferMemory()' in RE2_VK_BUFFER.cpp TU");
        throw std::runtime_error("Failed to bind Buffer Memory with BUffer.");
    }
}

void RE2_VK_BUFFER::WRITE_DATA_TO_MEMORY(void* DATA, size_t SIZE)
{
    void* MEMORY_DATA;
    vkMapMemory(this->LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->VERTEX_BUFFER_MEMORY, 0, SIZE, 0, &MEMORY_DATA);
    memcpy(MEMORY_DATA, DATA, SIZE);
    vkUnmapMemory(this->LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->VERTEX_BUFFER_MEMORY);
}

RE2_VK_BUFFER::RE2_VK_BUFFER(){}
