#pragma once
#include <vulkan/vulkan.h>
#include <vector>

namespace vkapp
{
    constexpr int kErrorInitializationFailed = 1;
    constexpr int kErrorInvalidArg = 2;

    class Skeleton
    {
        VkInstance m_instance;
        std::vector<VkPhysicalDevice> m_devices;
        VkPhysicalDevice m_dev;

        int createVkInstance();
        int enumerateDevices();
    public:
        Skeleton();
        ~Skeleton();
        virtual int initialize() = 0;
        virtual int update() = 0;
        virtual void render() = 0;
        virtual int finalize() = 0;

        struct Options
        {
            size_t m_gfxHeapSize;
            size_t m_device;

            Options();
        };

        int initializeUtil(const Options* option = nullptr);
        int finalizeUtil();
    };
}
