#pragma once
#include <vector>
#include <vkapp_allocator.h>
#include <vkapp_gfx.h>
#include <vulkan/vulkan.h>

namespace vkapp {
constexpr int kErrorInitializationFailed = 1;
constexpr int kErrorInvalidArg = 2;
constexpr int kErrorNoComputeQueue = 3;
constexpr int kErrorMemoryNotFound = 4;

class Skeleton {
  VkInstance m_instance;
  std::vector<VkPhysicalDevice> m_devices;
  VkPhysicalDevice m_physicalDevice;
  VkDevice m_dev;
  uint32_t m_queueIdx;
  VkQueue m_queue;
  VmemAllocator m_deviceMem; // Device-only memory
  VmemAllocator m_sharedMem; // Host-visible memory

  int createVkInstance();
  int enumerateDevices();
  int initializeDevice();

public:
  Skeleton();
  ~Skeleton();
  virtual int initialize() = 0;
  virtual int update() = 0;
  virtual void render() = 0;
  virtual int finalize() = 0;

  struct Options {
    size_t m_gfxHeapSize;
    size_t m_sharedHeadSize;
    size_t m_device;

    Options();
  };

  int initializeUtil(const Options *option = nullptr);
  int finalizeUtil();
};
} // namespace vkapp
