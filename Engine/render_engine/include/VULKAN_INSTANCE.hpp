#ifndef VULKAN_INSTANCE_HPP
#define VULKAN_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <GLFW_PREPROCESSOR.hpp>

#define DEBUG_ON
#define VALIDATION_LAYER_ON true    // set this to false or true
#include <ETL.hpp>


class VULKAN_INSTANCE{

    private:
    VkInstance INSTANCE{};
    bool DEBUG = VALIDATION_LAYER_ON;
    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    VkDebugUtilsMessengerEXT DEBUG_MESSENGER{};
    void setupDebugMessengerValidation(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger);

    // private helper methods
    std::vector<const char*> getRequiredExtensions();

    public:
    VkInstance& getInstance();
    void INIT_INSTANCE();

    void FREE();
};

#endif
