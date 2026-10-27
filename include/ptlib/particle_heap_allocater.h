#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/internal/heap.h"
#include "types.h"

namespace ptlib {

class HeapAllocator : public mm::mtl::IAllocator {
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
  void traverse(mm::mtl::HeapAllocUtil::heap_walker walker, void *user);
  virtual unsigned int getNameHash() const;
  virtual void *allocate(size_t size, size_t alignment, const char *file, int line);
  virtual size_t getBlockNum();

  void *m_buffer;
  size_t unknown10; // Inferred role: buffer size; original member name unknown.
  size_t m_allocated;
  void *m_control;
  mm::mtl::FixStr<64> m_name;
  unsigned int m_nameHash;
  mm::mtl::HeapAllocUtil::control_t unknown70; // Inferred role: control buffer; original member name unknown.
};

static_assert(offsetof(HeapAllocator, m_buffer) == 0x08, "");
static_assert(offsetof(HeapAllocator, m_name) == 0x28, "");
static_assert(offsetof(HeapAllocator, m_nameHash) == 0x6c, "");
static_assert(offsetof(HeapAllocator, unknown70) == 0x70, "");

class HeapAllocaterManager {
public:
  enum HEAP_TYPE {
    HEAP_TYPE_UNKNOWN_0,
  };

  static void init();
  static void term();
  static HeapAllocaterManager *getPtr(HEAP_TYPE type);
  static HeapAllocaterManager *get(HEAP_TYPE type);
  void setMemory(void *buffer, size_t bufferSize);
  void *alloc(size_t size, size_t alignment);
  void *allocD(size_t size, size_t alignment, char *file, unsigned int line);
  void *realloc(void *pointer, size_t size, size_t alignment);
  void dealloc(void *pointer);
  void *reallocD(void *pointer, size_t size, size_t alignment, char *file, unsigned int line);
  static void memoryDump();
  int getBlockNum();

  HeapAllocator unknown00; // Inferred role: effect heap allocator; original member name unknown.
  u8 _19f8[0x1a00 - 0x19f8];
  u8 unknown1a00[0x80000]; // Inferred role: memory of the effect heap; original member name unknown.

  static HeapAllocaterManager *s_pIns[1];
};

static_assert(offsetof(HeapAllocaterManager, unknown1a00) == 0x1a00, "");
static_assert(sizeof(HeapAllocaterManager) == 0x81a00, "");

} // namespace ptlib
