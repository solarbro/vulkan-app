#pragma once
#include <vulkan/vulkan.h>

namespace vkapp
{
    struct BufferSpec
    {
        VkBufferCreateInfo m_info;

        BufferSpec& init();
    };
}
