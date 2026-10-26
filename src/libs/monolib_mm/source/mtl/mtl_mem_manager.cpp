#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mtl/allocator_wrapper.h"
#include "mtl/mem_allocator.h"
#include "mtl/mem_manager.h"
#include "mtl/null_allocator.h"
#include "types.h"

namespace mtl {
struct MEMIMAGE_HEAD;
struct MemoryInfo1;

AllocatorWrapper::AllocatorWrapper() : m_allocator(nullptr), m_buffer(nullptr), m_capacity(0), unknown18(0) {}

AllocatorWrapper::~AllocatorWrapper() {}

void AllocatorWrapper::init(IMemAllocator *allocator, void *buffer, size_t size, const char *name) {
  m_allocator = allocator;
  m_buffer = buffer;
  m_capacity = size;
  unknown18 = 0;
  m_name = name != nullptr ? name : "no name";
  if (allocator != nullptr) {
    allocator->create(buffer, size, name);
  }
}

const char *AllocatorWrapper::getName() const { return m_name.c_str(); }

void *AllocatorWrapper::allocate(size_t size) {
  if (m_allocator == nullptr) {
    return nullptr;
  }
  void *pointer = m_allocator->allocate(size, 16);
  if (pointer != nullptr) {
    unknown18++;
  }
  return pointer;
}

void *AllocatorWrapper::allocate(size_t size, size_t alignment, const char *file, int line) {
  if (m_allocator == nullptr) {
    return nullptr;
  }
  void *pointer = m_allocator->allocate(size, alignment, file, line);
  if (pointer != nullptr) {
    unknown18++;
  }
  return pointer;
}

void *AllocatorWrapper::allocate_tail(size_t size, size_t alignment, const char *file, int line) {
  if (m_allocator == nullptr) {
    return nullptr;
  }
  void *pointer = m_allocator->allocate_tail(size, alignment, file, line);
  if (pointer != nullptr) {
    unknown18++;
  }
  return pointer;
}

void AllocatorWrapper::deallocate(void *pointer, size_t size) {
  if (pointer != nullptr && m_allocator != nullptr) {
    m_allocator->deallocate(pointer, size);
    unknown18--;
  }
}

void *AllocatorWrapper::reallocate(void *pointer, size_t size) {
  if (m_allocator == nullptr) {
    return nullptr;
  }
  return m_allocator->reallocate(pointer, size);
}

void AllocatorWrapper::log(MemoryInfo *info, bool isDetail) const {
  if (m_allocator != nullptr) {
    m_allocator->log(info, isDetail);
  }
}

void AllocatorWrapper::log_callSTack(void *callStack) const {
  if (m_allocator != nullptr) {
    m_allocator->log_callSTack(callStack);
  }
}

void AllocatorWrapper::checkLeakMemory() {
  if (m_allocator != nullptr) {
    m_allocator->checkLeakMemory();
  }
}

bool AllocatorWrapper::hasMemory(const void *pointer) const {
  if (m_allocator == nullptr) {
    return false;
  }
  return m_allocator->hasMemory(pointer);
}

size_t AllocatorWrapper::getAllocSize(const void *pointer) const {
  if (m_allocator == nullptr) {
    return 0;
  }
  return m_allocator->getAllocSize(pointer);
}

bool AllocatorWrapper::isArea(const void *pointer) const {
  if (m_allocator == nullptr) {
    return false;
  }
  if (pointer < m_buffer) {
    return false;
  }
  return m_capacity + reinterpret_cast<size_t>(m_buffer) > reinterpret_cast<size_t>(pointer);
}

size_t AllocatorWrapper::getCapacity() const { return m_capacity; }

void AllocatorWrapper::memoryInfo(MemoryInfo *info) const {
  if (m_allocator != nullptr) {
    m_allocator->memoryInfo(info);
  }
}

void AllocatorWrapper::getMemImage(MEMIMAGE_HEAD *head) const {
  if (m_allocator != nullptr) {
    m_allocator->getMemImage(head);
  }
}

int AllocatorWrapper::getMemInfo1(MemoryInfo1 *info, u32 num) const {
  if (m_allocator == nullptr) {
    return 0;
  }
  return m_allocator->getMemInfo1(info, num);
}

bool AllocatorWrapper::valid() const {
  if (m_allocator == nullptr) {
    return false;
  }
  return m_allocator->valid();
}

bool AllocatorWrapper::empty() const { return m_allocator == nullptr; }

bool AllocatorWrapper::dummy() const {
  if (m_allocator == nullptr) {
    return true;
  }
  return m_allocator->dummy();
}

void AllocatorWrapper::clear() {}

void NullAllocator::create(void *buffer, size_t size, const char *name) { m_name = name; }

void NullAllocator::destroy() {}

AllocatorType NullAllocator::getType() const { return static_cast<AllocatorType>(0); }

void *NullAllocator::allocate(size_t size, size_t alignment) { return nullptr; }

void *NullAllocator::allocate(size_t size, size_t alignment, const char *file, int line) { return nullptr; }

void *NullAllocator::allocate_tail(size_t size, size_t alignment, const char *file, int line) { return nullptr; }

void NullAllocator::deallocate(void *pointer, size_t size) {}

void *NullAllocator::reallocate(void *pointer, size_t size) { return nullptr; }

void NullAllocator::log(MemoryInfo *info, bool isDetail) const {}

const char *NullAllocator::getName() const { return m_name.c_str(); }

bool NullAllocator::hasMemory(const void *pointer) const { return false; }

size_t NullAllocator::getAllocSize(const void *pointer) const { return 0; }

void NullAllocator::memoryInfo(MemoryInfo *info) const {}

void NullAllocator::getMemImage(MEMIMAGE_HEAD *head) const {}

int NullAllocator::getMemInfo1(MemoryInfo1 *info, u32 num) const { return 0; }

bool NullAllocator::empty() const { return m_name.c_str()[0] == '\0'; }

bool NullAllocator::valid() const { return m_name.c_str()[0] != '\0'; }

bool NullAllocator::dummy() const { return m_name.c_str()[0] != '\0'; }

u32 NullAllocator::getMemSize(const void *pointer) const { return 0; }

} // namespace mtl
