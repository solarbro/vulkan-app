#pragma once
#include <vkapp_allocator.h>
#include <vulkan/vulkan.h>

namespace vkapp {
class VmemAllocator : public MemoryPool {
  VkDevice m_device;
  VkDeviceMemory m_vkmem;

public:
  VmemAllocator();
  ~VmemAllocator();
  int initialize(VkDevice dev, VkPhysicalDevice phys, size_t size,
                 VkMemoryPropertyFlags flags);
  int finalize();
};
struct BufferSpec {
  VkBufferCreateInfo m_info;

  BufferSpec &init();
};
} // namespace vkapp
