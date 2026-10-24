#include "mm_mtl/internal/heap_allocator.h"

#include "mm/mm_std_base.h"
#include "mm_mtl/hash.h"

namespace mm {
namespace mtl {

HeapAllocator::HeapAllocator() { destroy(false); }

HeapAllocator::~HeapAllocator() { destroy(false); }

void HeapAllocator::destroy(bool release) {
  if (m_buffer != nullptr && release) {
    HeapAllocUtil::heap_remove_pool(m_control, m_buffer);
    HeapAllocUtil::heap_destroy(m_control);
// The assert line of the game: it is the line argument of the assert.
#line 75
    MM_ASSERT(m_allocated == 0);
  }
  m_buffer = nullptr;
  m_control = nullptr;
  m_allocated = 0;
  m_bufferSize = 0;
  m_nameHash = 0;
  m_name.clear();
}

void HeapAllocator::create(void *buffer, size_t bufferSize, const char *name) {
// The assert lines of the game: they are the line arguments of the asserts.
#line 53
  MM_ASSERT(buffer != nullptr);
  MM_ASSERT(bufferSize > 0);
  MM_ASSERT(name != nullptr);
  m_control = HeapAllocUtil::heap_create(&m_controlBuffer);
// The assert line of the game: it is the line argument of the assert.
#line 58
  MM_ASSERT(m_control != 0);
  m_buffer = HeapAllocUtil::heap_add_pool(m_control, buffer, bufferSize);
  MM_ASSERT(m_buffer != 0);
  m_name = name;
  m_nameHash = hashStrCrc(m_name.c_str());
  m_bufferSize = bufferSize;
  m_allocated = 0;
}

const char *HeapAllocator::getName() const { return m_name.c_str(); }

void *HeapAllocator::allocate(size_t size, size_t alignment) {
// The assert line of the game: it is the line argument of the assert.
#line 99
  MM_ASSERT(m_buffer != 0 && "allocator is not create");
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

void *HeapAllocator::allocate(size_t size, size_t alignment, const char *file, int line) {
// The assert line of the game: it is the line argument of the assert.
#line 117
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
// The assert line of the game: it is the line argument of the assert.
#line 143
    MM_ASSERT(m_buffer != nullptr && "allocator is not create");
    HeapAllocUtil::heap_free(m_control, pointer);
    m_allocated--;
  }
}

bool HeapAllocator::insideArea(const void *adr) const {
// The assert line of the game: it is the line argument of the assert.
#line 160
  MM_ASSERT(m_buffer != 0 && "allocator is not create");
  return reinterpret_cast<size_t>(m_buffer) < reinterpret_cast<size_t>(adr) && reinterpret_cast<size_t>(adr) < reinterpret_cast<size_t>(m_buffer) + m_bufferSize;
}

bool HeapAllocator::hasMemory(const void *adr) const {
// The assert line of the game: it is the line argument of the assert.
#line 176
  MM_ASSERT(m_buffer != 0 && "allocator is not create");
  return insideArea(adr);
}

size_t HeapAllocator::getBlockSize(const void *adr) const {
  if (adr == nullptr) {
    return 0;
  }
// The assert lines of the game: they are the line arguments of the asserts.
#line 200
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

} // namespace mtl
} // namespace mm
