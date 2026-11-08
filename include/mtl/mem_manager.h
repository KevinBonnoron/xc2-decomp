#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "mtl/mem_handlebase_allocator.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;

template <typename T, size_t N> class FixedVector;
} // namespace mtl
} // namespace mm

namespace mtl {
class IMemAllocator;

size_t getMemoryChunkSize(void *pointer);

struct MemoryInfo {
  MemoryInfo() : unknown00(0), unknown08(0), unknown10(0), unknown18(0), unknown20(0), unknown24(0), unknown28(0), unknown30(0), unknown38(0), unknown40(0) {}

  u64 unknown00; // Inferred role: total size; original member name unknown.
  u64 unknown08; // Role and original member name unknown.
  u64 unknown10; // Inferred role: used size; original member name unknown.
  u64 unknown18; // Inferred role: size of the largest free chunk; original member name unknown.
  f32 unknown20; // Inferred role: percentage of used memory; original member name unknown.
  f32 unknown24; // Inferred role: percentage of chunks in use; original member name unknown.
  int unknown28; // Inferred role: allocation count; original member name unknown.
  u64 unknown30; // Inferred role: top address of the region; original member name unknown.
  u64 unknown38; // Inferred role: allocator name; original member name unknown.
  u64 unknown40; // Role and original member name unknown.
};

static_assert(offsetof(MemoryInfo, unknown10) == 0x10, "");
static_assert(offsetof(MemoryInfo, unknown28) == 0x28, "");
static_assert(offsetof(MemoryInfo, unknown30) == 0x30, "");
static_assert(sizeof(MemoryInfo) == 0x48, "");

// Evidence: AssetAllocator<1024>::getMemInfo1 and DlAllocator::getMemInfo1 fill one per allocation, 0x20 bytes apart.
struct MemoryInfo1 {
  u64 unknown00;         // Inferred role: address of the allocation; original member name unknown.
  u64 unknown08;         // Inferred role: size of the allocation; original member name unknown.
  const char *unknown10; // Inferred role: file of the allocation; original member name unknown.
  u32 unknown18;         // Inferred role: line of the allocation; original member name unknown.
};

static_assert(offsetof(MemoryInfo1, unknown10) == 0x10, "");
static_assert(offsetof(MemoryInfo1, unknown18) == 0x18, "");
static_assert(sizeof(MemoryInfo1) == 0x20, "");

// Evidence: AssetAllocator<1024>::getMemImage sets unknown10 to the number of blocks it wrote from 0x18 on, 0x10 bytes
// each, at most the value unknown10 had.
struct MEMIMAGE_HEAD {
  // Inferred role: block of the image; original type name unknown.
  struct unknown001 {
    u64 unknown00; // Inferred role: address of the block; original member name unknown.
    u64 unknown08; // Inferred role: size of the block; original member name unknown.
  };

  u64 unknown00;          // Role and original member name unknown.
  u64 unknown08;          // Role and original member name unknown.
  u64 unknown10;          // Inferred role: capacity of the blocks, then their count; original member name unknown.
  unknown001 unknown18[]; // Inferred role: blocks of the image; original member name unknown.
};

static_assert(offsetof(MEMIMAGE_HEAD, unknown10) == 0x10, "");
static_assert(offsetof(MEMIMAGE_HEAD, unknown18) == 0x18, "");
static_assert(sizeof(MEMIMAGE_HEAD) == 0x18, "");

enum AllocatorType {
  ALLOCATOR_TYPE_PROGRAM = 1,
  ALLOCATOR_TYPE_RESOURCE = 2,
};

class MemManager {
public:
  class Region;

  static void initialize();
  static void terminate();
  static void clear();
  static ALLOC_HANDLE create(const char *name);
  static ALLOC_HANDLE create(void *buffer, size_t size, const char *name, bool);
  static ALLOC_HANDLE create(void *buffer, size_t size, const char *name, bool, AllocatorType type);
  static ALLOC_HANDLE create(ALLOC_HANDLE parent, size_t size, const char *name, bool, const char *file = "no name", int line = 0);
  static ALLOC_HANDLE create(ALLOC_HANDLE parent, size_t size, const char *name, bool, AllocatorType type, size_t alignment, const char *file = "no name", int line = 0);
  static void erase(ALLOC_HANDLE handle);
  static bool valid(const ALLOC_HANDLE &handle, bool);
  static bool valid_section(const ALLOC_HANDLE &handle, bool);
  static mm::mtl::IAllocator *getAllocator(const ALLOC_HANDLE &handle);
  static void *allocate(ALLOC_HANDLE handle, size_t size, size_t alignment, bool isBack, const char *name, int line);
  static void *allocate_section(ALLOC_HANDLE handle, size_t size, size_t alignment, bool isBack, const char *name, int line);
  static void *allocate_tail(ALLOC_HANDLE handle, size_t size, size_t alignment, bool isBack, const char *name, int line);
  static void *allocate_tail_section(ALLOC_HANDLE handle, size_t size, size_t alignment, bool isBack, const char *name, int line);
  static void deallocate(void *pointer, size_t size, bool isBack);
  static void deallocate_section(void *pointer, size_t size, bool isBack);
  static void *reallocate(void *pointer, size_t size, bool isBack);
  static void *reallocate_section(void *pointer, size_t size, bool isBack);
  static size_t maxAllocSize(ALLOC_HANDLE handle);
  static bool isArea(ALLOC_HANDLE handle, const void *pointer);
  static Region *getArea(const ALLOC_HANDLE &handle, const void *pointer);
  static Region *getArea_section(const ALLOC_HANDLE &handle, const void *pointer);
  static Region *getAreaChild(Region *region, const void *pointer);
  static bool hasMemory(const ALLOC_HANDLE &handle, const void *pointer);
  static bool isHandleMemory(void *pointer);
  static ALLOC_HANDLE getHandle(const void *pointer);
  static ALLOC_HANDLE getParent(ALLOC_HANDLE handle);
  static bool isMemParent(ALLOC_HANDLE handle, ALLOC_HANDLE parent);
  static u64 getTopAdr(const ALLOC_HANDLE &handle);
  static size_t getTotalSize(ALLOC_HANDLE handle);
  static size_t getAllocSize(void *pointer);
  static u32 getAllocs(const ALLOC_HANDLE &handle);
  static bool empty(ALLOC_HANDLE handle);
  static void setBlockSize(const ALLOC_HANDLE &handle, size_t blockSize);
  static void setHaltAlloc(ALLOC_HANDLE handle, bool);
  static void setWarnAlloc(ALLOC_HANDLE handle, bool);
  static void setLogAlloc(ALLOC_HANDLE handle, bool);
  static void log(ALLOC_HANDLE handle, bool isDetail, MemoryInfo *info);
  static void log_section(ALLOC_HANDLE handle, bool isDetail, MemoryInfo *info);
  static void log_callSTack(ALLOC_HANDLE handle, void *callStack);
  static void logMemTree(ALLOC_HANDLE handle, MemoryInfo *info, int depth);
  static bool getMemoryInfo(ALLOC_HANDLE handle, MemoryInfo *info);
  static bool getDebInfo(MemoryInfo1 *info, u32 num, ALLOC_HANDLE handle);
  static void getMemImage(ALLOC_HANDLE handle, ALLOC_HANDLE image);
  static const char *getName(ALLOC_HANDLE handle);
  static bool isExistCallStack(ALLOC_HANDLE handle);
  static bool isCollectCallStack();
  static void setCollectCallStack(bool collect);
  static bool isInitialized();
  static void tchk();
  static void *getAllocatorList();
  static IMemAllocator *createAllocator(AllocatorType type);
  static void destroyAllocator(AllocatorType type, IMemAllocator *allocator);

private:
  // The element size comes from FixedVector<HandleRegion, 512> (0x4000 bytes of storage); the members are not decompiled yet.
  struct HandleRegion {
    HandleRegion(const ALLOC_HANDLE &handle, Region *region) : unknown00(handle), unknown08(region) { unknown10.unknown08 = handle; }
    bool operator==(const HandleRegion &other) const { return unknown00 == other.unknown00 && unknown08 == other.unknown08; }

    ALLOC_HANDLE unknown00;           // Inferred role: handle of the region; original member name unknown.
    Region *unknown08;                // Inferred role: region of the handle; original member name unknown.
    MemHandlebaseAllocator unknown10; // Inferred role: allocator handed out for the handle; original member name unknown.
  };

  static_assert(sizeof(HandleRegion) == 0x20, "");

  // Inferred role: slot of the table from region handles to regions; original type name unknown.
  struct unknown002 {
    Region *unknown00; // Inferred role: region of the handle; original member name unknown.
    u32 unknown08;     // Inferred role: key of the handle; original member name unknown.
  };

  // Inferred role: open addressing table from region handles to regions; original type name unknown.
  struct unknown001 {
    // Inferred role: region of the handle, null when the handle is not in the table; original name unknown.
    Region *unknown003(const ALLOC_HANDLE &handle) const {
      if (handle.isValid()) {
        if (unknown2000 != 0) {
          u32 key = handle.unknown00 & unknown2010;
          const unknown002 &slot = unknown00[key % unknown2000];
          if (slot.unknown08 == key) {
            return slot.unknown00;
          }
        }
      }
      return nullptr;
    }

    unknown002 unknown00[512];
    u32 unknown2000; // Inferred role: slot count; original member name unknown.
    u32 unknown2004; // Inferred role: last handle issued; original member name unknown.
    u32 unknown2008; // Inferred role: smallest handle; original member name unknown.
    u32 unknown200c; // Inferred role: largest handle; original member name unknown.
    u32 unknown2010; // Inferred role: mask applied to a handle to get its key; original member name unknown.
  };

  static_assert(sizeof(unknown001) == 0x2018, "");

  static bool s_bInitialize;
  static bool m_collectCallstack;
  static ALLOC_HANDLE s_hLastFree;
  static mm::mtl::FixedVector<HandleRegion, 512> _existHandle;
  static unknown001 s_ptrMap;
};

} // namespace mtl
