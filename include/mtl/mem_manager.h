#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace mtl {

struct MemoryInfo {
  MemoryInfo() : unknown00(0), unknown08(0), unknown10(0), unknown18(0), unknown20(0), unknown28(0), unknown30(0), unknown38(0), unknown40(0) {}

  u64 unknown00; // Inferred role: total size; original member name unknown.
  u64 unknown08; // Role and original member name unknown.
  u64 unknown10; // Inferred role: used size; original member name unknown.
  u64 unknown18; // Role and original member name unknown.
  u64 unknown20; // Role and original member name unknown.
  int unknown28; // Inferred role: allocation count; original member name unknown.
  u64 unknown30; // Role and original member name unknown.
  u64 unknown38; // Role and original member name unknown.
  u64 unknown40; // Role and original member name unknown.
};

static_assert(offsetof(MemoryInfo, unknown10) == 0x10, "");
static_assert(offsetof(MemoryInfo, unknown28) == 0x28, "");
static_assert(offsetof(MemoryInfo, unknown30) == 0x30, "");
static_assert(sizeof(MemoryInfo) == 0x48, "");

enum AllocatorType {
  ALLOCATOR_TYPE_PROGRAM = 1,
  ALLOCATOR_TYPE_RESOURCE = 2,
};

class MemManager {
public:
  static ALLOC_HANDLE create(void *buffer, size_t size, const char *name, bool);
  static ALLOC_HANDLE create(ALLOC_HANDLE parent, size_t size, const char *name, bool, const char *file = "no name", int line = 0);
  static ALLOC_HANDLE create(ALLOC_HANDLE parent, size_t size, const char *name, bool, AllocatorType type, size_t alignment, const char *file = "no name", int line = 0);
  static void erase(ALLOC_HANDLE handle);
  static bool valid(const ALLOC_HANDLE &handle, bool);
  static mm::mtl::IAllocator *getAllocator(const ALLOC_HANDLE &handle);
  static void *allocate(ALLOC_HANDLE handle, size_t size, size_t alignment, bool isBack, const char *name, int line);
  static void deallocate(void *pointer, size_t size, bool isBack);
  static void *reallocate(void *pointer, size_t size, bool isBack);
  static size_t maxAllocSize(ALLOC_HANDLE handle);
  static bool isArea(ALLOC_HANDLE handle, const void *pointer);
  static u64 getTopAdr(const ALLOC_HANDLE &handle);
  static size_t getTotalSize(ALLOC_HANDLE handle);
  static void log(ALLOC_HANDLE handle, bool isDetail, MemoryInfo *info);
  static bool getMemoryInfo(ALLOC_HANDLE handle, MemoryInfo *info);
  static const char *getName(ALLOC_HANDLE handle);
};

} // namespace mtl
