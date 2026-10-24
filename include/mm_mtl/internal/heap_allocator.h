#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/internal/heap.h"

namespace mm {
namespace mtl {

class HeapAllocator : public IAllocator {
public:
  HeapAllocator();
  ~HeapAllocator() override;
  void destroy(bool release);
  void create(void *buffer, size_t bufferSize, const char *name);
  const char *getName() const override;
  void *allocate(size_t size, size_t alignment) override;
  void deallocate(void *pointer) override;
  bool insideArea(const void *adr) const;
  bool hasMemory(const void *adr) const;
  size_t getBlockSize(const void *adr) const;
  bool valid() const;
  void traverse(HeapAllocUtil::heap_walker walker, void *user);
  virtual unsigned int getNameHash() const;
  virtual void *allocate(size_t size, size_t alignment, const char *file, int line);

  void *m_buffer;
  size_t unknown10; // Inferred role: buffer size; original member name unknown.
  size_t m_allocated;
  void *m_control;
  FixStr<64> m_name;
  unsigned int m_nameHash;
  HeapAllocUtil::control_t unknown70; // Inferred role: control buffer; original member name unknown.
};

static_assert(offsetof(HeapAllocator, m_buffer) == 0x08, "");
static_assert(offsetof(HeapAllocator, m_name) == 0x28, "");
static_assert(offsetof(HeapAllocator, m_nameHash) == 0x6c, "");
static_assert(offsetof(HeapAllocator, unknown70) == 0x70, "");

} // namespace mtl
} // namespace mm
