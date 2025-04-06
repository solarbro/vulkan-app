#include "vkapp_allocator.h"

vkapp::MemoryPool::MemoryPool()
    : m_poolSize(0), m_fit(FitMethod::kFirstFit), m_autoResize(false) {}