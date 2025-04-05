#include "app_skeleton.h"
#include "app_skeleton.h"
#include <iostream>
#include <format>

vkapp::Skeleton::Options::Options()
    : m_gfxHeapSize(1024llu * 1024llu * 1024llu)
    , m_device(0) // Use device 0 by default
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

namespace
{
    void deviceSummary(VkPhysicalDevice dev, size_t idx)
    {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(dev, &props);

        std::cout << "Device " << idx << ":\n";
        std::cout << "            Name: " << props.deviceName << "\n";
        std::cout << "     API Version: "
            << VK_VERSION_MAJOR(props.apiVersion) << "."
            << VK_VERSION_MINOR(props.apiVersion) << "."
            << VK_VERSION_PATCH(props.apiVersion) << "\n";
        std::cout << "  Driver Version: " << props.driverVersion << "\n";
        std::cout << "       Vendor ID: " << props.vendorID << "\n";
        std::cout << "       Device ID: " << props.deviceID << "\n";
        std::cout << "     Device Type: ";
        switch (props.deviceType)
        {
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: std::cout << "Integrated GPU\n"; break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   std::cout << "Discrete GPU\n"; break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    std::cout << "Virtual GPU\n"; break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:            std::cout << "CPU\n"; break;
        default:                                     std::cout << "Other\n"; break;
        }

        VkPhysicalDeviceMemoryProperties memProps;
        vkGetPhysicalDeviceMemoryProperties(dev, &memProps);
        std::cout << "    Memory Heaps: " << memProps.memoryHeapCount << "\n";
        for (uint32_t j = 0; j < memProps.memoryHeapCount; ++j)
        {
            std::cout << "          Heap " << j << ": "
                << (memProps.memoryHeaps[j].size / (1024 * 1024)) << " MB\n";
        }

        std::cout << std::endl;
    }
}

int vkapp::Skeleton::enumerateDevices()
{
    uint32_t devCount = 0;
    if (vkEnumeratePhysicalDevices(m_instance, &devCount, nullptr) != VK_SUCCESS)
    {
        std::cerr << "Failed to enumerate physical devices!\n";
        return kErrorInitializationFailed;
    }
    m_devices.resize(devCount);
    vkEnumeratePhysicalDevices(m_instance, &devCount, m_devices.data());
    for (size_t i = 0; i < m_devices.size(); ++i)
        deviceSummary(m_devices[i], i);
    return 0;
}

vkapp::Skeleton::Skeleton()
    : m_instance(nullptr)
    , m_dev(nullptr)
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
    {
        const int res = enumerateDevices();
        if (res != 0) return res;
    }
    if (option->m_device >= m_devices.size())
    {
        std::cerr << std::format("Device {} was selected, but only {} devices were discovered.\n", option->m_device, m_devices.size());
        return kErrorInvalidArg;
    }
    m_dev = m_devices[option->m_device];
    std::cout << "Using device " << option->m_device << std::endl;
    return 0;
}

int vkapp::Skeleton::finalizeUtil()
{
    if (m_instance)
        vkDestroyInstance(m_instance, nullptr);
    return 0;
}
