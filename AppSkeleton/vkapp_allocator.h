#pragma once
#include <vector>

namespace vkapp {
enum class FitMethod { kFirstFit, kBestFit, kWorstFit };

class MemoryPool {
  size_t m_poolSize;
  FitMethod m_fit;
  bool m_autoResize;

public:
  MemoryPool();

  size_t allocate(size_t size, size_t align);
  void free(size_t addr);

  int configure(size_t size, bool autoResize);
  inline size_t size() const { return m_poolSize; }
};

} // namespace vkapp