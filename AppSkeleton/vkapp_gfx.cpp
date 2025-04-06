#include "vkapp_gfx.h"
#include "vkapp_skeleton.h"
#include <iostream>

vkapp::BufferSpec &vkapp::BufferSpec::init() { return *this; }

vkapp::VmemAllocator::VmemAllocator() : m_device(nullptr), m_vkmem(nullptr) {}

vkapp::VmemAllocator::~VmemAllocator() {}

int vkapp::VmemAllocator::initialize(VkDevice dev, VkPhysicalDevice phys,
                                     size_t size, VkMemoryPropertyFlags flags) {
  // Query memory properties of the physical device
  VkPhysicalDeviceMemoryProperties memProperties = {};
  vkGetPhysicalDeviceMemoryProperties(phys, &memProperties);

  // Find suitable memory type (for this example, we'll use device-local memory)
  uint32_t memoryTypeIndex = UINT32_MAX;
  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
    if ((memProperties.memoryTypes[i].propertyFlags & flags) != 0) {
      memoryTypeIndex = i;
      break;
    }
  }
  if (memoryTypeIndex == UINT32_MAX) {
    std::cerr << "No suitable device-local memory type found!" << std::endl;
    return kErrorMemoryNotFound;
  }

  // Allocate memory
  VkMemoryAllocateInfo allocInfo = {};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = size;
  allocInfo.memoryTypeIndex = memoryTypeIndex;
  if (vkAllocateMemory(dev, &allocInfo, nullptr, &m_vkmem) != VK_SUCCESS) {
    std::cerr << "Failed to allocate Vulkan memory!" << std::endl;
    return kErrorInitializationFailed;
  }
  m_device = dev;

  return 0;
}

int vkapp::VmemAllocator::finalize() {
  if (m_vkmem) {
    vkFreeMemory(m_device, m_vkmem, nullptr);
    m_device = nullptr;
    m_vkmem = nullptr;
  }
  return 0;
}
