#include <createvksurface.hpp>
#include <iostream>

void createvksurface(VkInstance& instance, VkSurfaceKHR& surface, GLFWwindow* window)
{
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}