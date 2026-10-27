#include "ptlib/particle_heap_allocater.h"

#include <new>

#include "mm/mm_std_base.h"
#include "mm_mtl/hash.h"
#include "ptlib/particle_system.h"

namespace ptlib {

using mm::mtl::HeapAllocUtil;

HeapAllocaterManager *HeapAllocaterManager::s_pIns[1];

void HeapAllocaterManager::init() {
  term();
  s_pIns[0] = static_cast<HeapAllocaterManager *>(ParticleManager::sysAlloc(sizeof(HeapAllocaterManager), 0x10, __FILE__, 24));
  if (s_pIns[0] != nullptr) {
    new (s_pIns[0]) HeapAllocaterManager;
    s_pIns[0]->setMemory(s_pIns[0]->unknown1a00, sizeof(s_pIns[0]->unknown1a00));
  }
}

void HeapAllocaterManager::term() {
  if (s_pIns[0] != nullptr) {
    ParticleManager::sysFree(s_pIns[0]);
    s_pIns[0] = nullptr;
  }
}

void HeapAllocaterManager::setMemory(void *buffer, size_t bufferSize) { unknown00.create(buffer, bufferSize, "EfctHeap"); }

HeapAllocaterManager *HeapAllocaterManager::getPtr(HEAP_TYPE type) { return s_pIns[type]; }

HeapAllocaterManager *HeapAllocaterManager::get(HEAP_TYPE type) { return s_pIns[type]; }

void *HeapAllocaterManager::alloc(size_t size, size_t alignment) { return unknown00.allocate(size, alignment); }

void *HeapAllocaterManager::allocD(size_t size, size_t alignment, char *file, unsigned int line) { return unknown00.allocate(size, alignment, file, line); }

void *HeapAllocaterManager::realloc(void *pointer, size_t size, size_t alignment) {
  void *newPointer = unknown00.allocate(size, alignment);
  if (newPointer != nullptr) {
    unknown00.deallocate(pointer);
  }
  return newPointer;
}

void HeapAllocaterManager::dealloc(void *pointer) { unknown00.deallocate(pointer); }

void *HeapAllocaterManager::reallocD(void *pointer, size_t size, size_t alignment, char *file, unsigned int line) {
  void *newPointer = unknown00.allocate(size, alignment, file, line);
  if (newPointer != nullptr) {
    unknown00.deallocate(pointer);
  }
  return newPointer;
}

void HeapAllocaterManager::memoryDump() {}

int HeapAllocaterManager::getBlockNum() { return unknown00.getBlockNum(); }

HeapAllocator::HeapAllocator() { destroy(false); }

HeapAllocator::~HeapAllocator() { destroy(true); }

void HeapAllocator::destroy(bool release) {
  if (m_buffer != nullptr && release) {
    HeapAllocUtil::heap_remove_pool(m_control, m_buffer);
    HeapAllocUtil::heap_destroy(m_control);
#line 170
    MM_ASSERT(m_allocated == 0);
  }
  m_buffer = nullptr;
  m_control = nullptr;
  m_allocated = 0;
  unknown10 = 0;
  m_nameHash = 0;
  m_name.clear();
}

void HeapAllocator::create(void *buffer, size_t bufferSize, const char *name) {
#line 148
  MM_ASSERT(buffer != nullptr);
  MM_ASSERT(bufferSize > 0);
  MM_ASSERT(name != nullptr);
  m_control = HeapAllocUtil::heap_create(&unknown70);
#line 153
  MM_ASSERT(m_control != 0);
  m_buffer = HeapAllocUtil::heap_add_pool(m_control, buffer, bufferSize);
  MM_ASSERT(m_buffer != 0);
  m_name = name;
  m_nameHash = mm::mtl::hashStrCrc(m_name.c_str());
  unknown10 = bufferSize;
  m_allocated = 0;
}

const char *HeapAllocator::getName() const { return m_name.c_str(); }

void *HeapAllocator::allocate(size_t size, size_t alignment) {
#line 194
  MM_ASSERT(m_buffer != 0 && "allocator is not create");
  void *pointer;
  if (alignment > HeapAllocUtil::ALIGN_SIZE) {
    pointer = HeapAllocUtil::heap_memalign(m_control, alignment, size);
  } else {
    pointer = HeapAllocUtil::heap_malloc(m_control, size);
  }
  if (pointer != nullptr) {
    m_allocated++;
  } else {
    efMsg("%d", m_allocated);
#line 206
    MM_ASSERT(0);
  }
  return pointer;
}

void *HeapAllocator::allocate(size_t size, size_t alignment, const char *file, int line) {
#line 217
  MM_ASSERT(m_buffer != nullptr && "allocator is not create");
  void *pointer;
  if (alignment > HeapAllocUtil::ALIGN_SIZE) {
    pointer = HeapAllocUtil::heap_memalign(m_control, alignment, size);
  } else {
    pointer = HeapAllocUtil::heap_malloc(m_control, size);
  }
  if (pointer != nullptr) {
    m_allocated++;
  }
  return pointer;
}

void HeapAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
#line 243
    MM_ASSERT(m_buffer != nullptr && "allocator is not create");
    HeapAllocUtil::heap_free(m_control, pointer);
    m_allocated--;
  }
}

bool HeapAllocator::insideArea(const void *adr) const {
#line 263
  MM_ASSERT(m_buffer != 0 && "allocator is not create");
  return reinterpret_cast<size_t>(m_buffer) < reinterpret_cast<size_t>(adr) && reinterpret_cast<size_t>(adr) < reinterpret_cast<size_t>(m_buffer) + unknown10;
}

bool HeapAllocator::hasMemory(const void *adr) const {
#line 279
  MM_ASSERT(m_buffer != 0 && "allocator is not create");
  return insideArea(adr);
}

size_t HeapAllocator::getBlockSize(const void *adr) const {
  if (adr == nullptr) {
    return 0;
  }
#line 303
  MM_ASSERT(m_buffer != 0 && "allocator is not create");
  MM_ASSERT(hasMemory(adr) && "pointer is not exist!!");
  return HeapAllocUtil::heap_block_size(adr);
}

bool HeapAllocator::valid() const {
  if (m_buffer == nullptr) {
    return true;
  }
  if (HeapAllocUtil::heap_check(m_control) != 0) {
    return false;
  }
  return HeapAllocUtil::heap_check_pool(m_buffer) == 0;
}

void HeapAllocator::traverse(HeapAllocUtil::heap_walker walker, void *user) {
  if (m_buffer != nullptr) {
    HeapAllocUtil::heap_walk_pool(m_buffer, walker, user);
  }
}

unsigned int HeapAllocator::getNameHash() const { return m_nameHash; }

size_t HeapAllocator::getBlockNum() { return m_allocated; }

} // namespace ptlib
