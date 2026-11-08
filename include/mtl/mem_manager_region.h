#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace mtl {
class IMemAllocator;
struct MEMIMAGE_HEAD;
struct MemoryInfo1;

class MemManager::Region {
public:
  void initialize(IMemAllocator *allocator, void *buffer, size_t size, const char *name, bool isSection, bool isCritical);
  void destroy();
  void addChild(ALLOC_HANDLE handle);
  void removeChild(ALLOC_HANDLE handle);
  void checkLeakMemory();
  bool hasMemory(const void *pointer) const;
  Region *getArea(const void *pointer);
  bool getMemInfo1(MemoryInfo1 *info, u32 num) const;
  void *allocate(size_t size, bool isBack);
  void *allocate(size_t size, size_t alignment, bool isBack, const char *file, int line);
  void *allocate_tail(size_t size, size_t alignment, bool isBack, const char *file, int line);
  void alloc(size_t size);
  void alloc(size_t size, size_t alignment, const char *file, int line);
  void alloc_tail(size_t size, size_t alignment, const char *file, int line);
  void deallocate(void *pointer, size_t size, bool isBack);
  void *reallocate(void *pointer, size_t size, bool isBack);
  size_t maxAllocSize();
  bool empty() const;
  void memoryInfo(MemoryInfo *info);
  size_t getAllocSize(void *pointer);
  void log_callSTack(void *callStack);
  void log(MemoryInfo *info, bool isDetail);
  void getMemImage(MEMIMAGE_HEAD *head);
  u64 getTopAdr() const;
  u32 getAllocs() const;

  // Inferred role: bits of the flags at 0xb0; original names unknown.
  enum unknown001 {
    UNKNOWN001_UNKNOWN_0 = 1 << 0,
    UNKNOWN001_UNKNOWN_1 = 1 << 1,
    UNKNOWN001_UNKNOWN_3 = 1 << 3,
    UNKNOWN001_UNKNOWN_4 = 1 << 4,
    UNKNOWN001_UNKNOWN_5 = 1 << 5,
    UNKNOWN001_UNKNOWN_6 = 1 << 6,
  };

  IMemAllocator *unknown00; // Inferred role: allocator of the region; original member name unknown.
  void *unknown08;          // Inferred role: start of the memory; original member name unknown.
  size_t unknown10;         // Inferred role: size of the memory; original member name unknown.
  size_t m_allocs;
  mm::mtl::FixStr<64> m_name;
  u8 _64[0x68 - 0x64];
  ALLOC_HANDLE unknown68; // Inferred role: handle of the region; original member name unknown.
  u64 m_topAdr;
  ALLOC_HANDLE m_parent;
  ml::CriticalSectionNC unknown80; // Inferred role: lock of the region; original member name unknown.
  size_t m_blockSize;
  u32 unknownb0;                                   // Inferred role: flags; original member name unknown.
  mm::mtl::FixedList<ALLOC_HANDLE, 128> unknownb4; // Inferred role: handles of the child regions; original member name unknown.
};

static_assert(offsetof(MemManager::Region, m_name) == 0x20, "");
static_assert(offsetof(MemManager::Region, unknown68) == 0x68, "");
static_assert(offsetof(MemManager::Region, m_topAdr) == 0x70, "");
static_assert(offsetof(MemManager::Region, m_parent) == 0x78, "");
static_assert(offsetof(MemManager::Region, unknown80) == 0x80, "");
static_assert(offsetof(MemManager::Region, m_blockSize) == 0xa8, "");
static_assert(offsetof(MemManager::Region, unknownb4) == 0xb4, "");
static_assert(sizeof(MemManager::Region) == 0x548, "");

} // namespace mtl
