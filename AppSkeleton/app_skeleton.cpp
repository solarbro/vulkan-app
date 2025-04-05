#include "app_skeleton.h"
#include "app_skeleton.h"
#include <iostream>

vkapp::Skeleton::Options::Options()
    : m_gfxHeapSize(1024llu * 1024llu * 1024llu)
{
}

int vkapp::Skeleton::createVkInstance()
{
    // Create Vulkan instance
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanApp::Skeleton";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "VulkanApp";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;

    if (vkCreateInstance(&instanceInfo, nullptr, &m_instance) != VK_SUCCESS)
    {
        std::cerr << "Failed to create Vulkan instance!" << std::endl;
        return kErrorInitializationFailed;
    }

    std::cout << "Vulkan instance created successfully!" << std::endl;
    return 0;
}

vkapp::Skeleton::Skeleton()
    : m_instance(nullptr)
{
}

vkapp::Skeleton::~Skeleton()
{
}

int vkapp::Skeleton::initializeUtil(const Options* option)
{
    std::cout << "## Sample Application: start initializing ##\n";
    const Options defaultOption;
    if (!option)
        option = &defaultOption;
    {
        const int res = createVkInstance();
        if (res != 0) return res;
    }
    return 0;
}

int vkapp::Skeleton::finalizeUtil()
{
    if (m_instance)
        vkDestroyInstance(m_instance, nullptr);
    return 0;
}
