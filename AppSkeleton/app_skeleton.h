#pragma once
#include <vulkan/vulkan.h>

namespace vkapp
{
    constexpr int kErrorInitializationFailed = 1;

    class Skeleton
    {
        VkInstance m_instance;

        int createVkInstance();
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

            Options();
        };

        int initializeUtil(const Options* option = nullptr);
        int finalizeUtil();
    };
}
